use crate::*;
use lazy_static::lazy_static;
use libc::free;
use libc::strdup;
use std::any::Any;
use std::ffi::CStr;
use std::ffi::CString;
use std::mem;
use std::os::raw::c_char;
use std::os::raw::c_void;
use std::println;
use std::ptr;
use std::str::FromStr;
use std::str;
use std::sync::atomic::AtomicI16;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicI64;
use std::sync::atomic::AtomicI8;
use std::sync::atomic::AtomicU16;
use std::sync::atomic::AtomicU32;
use std::sync::atomic::AtomicU64;
use std::sync::atomic::AtomicU8;
use std::sync::atomic::Ordering;

pub fn stripchr(mainstr: Option<&mut [c_char]>, separator: i32) -> Option<&mut [c_char]> {
    // Check if mainstr is None (equivalent to NULL in C)
    let mainstr = mainstr?;
    
    // Convert separator from i32 to char
    let separator_char = separator as u8 as char;
    
    // Find the first occurrence of the separator character
    let ptr_idx = mainstr.iter().position(|&c| c as u8 as char == separator_char);
    
    // Return None if separator not found (equivalent to ptr == 0 in C)
    let ptr_idx = ptr_idx?;
    
    // Replace the separator with null terminator
    mainstr[ptr_idx] = 0;
    
    // Return the slice starting after the null terminator
    Some(&mut mainstr[ptr_idx + 1..])
}
pub fn test_value_copy() {
    println!("testing binn value copy... ");
    println!("TODO!!!");
}

lazy_static! {
    pub static ref TMP: std::sync::Mutex<[u8; 128]> = std::sync::Mutex::new([0; 128]);
}

pub fn date_to_str(date: u16) -> String {
    let day = (date & 0xf800) >> 11;
    let month = (date & 0x0780) >> 7;
    let year = date & 0x007f;
    
    format!("{:04}-{:02}-{:02}", year + 1900, month, day)
}

pub fn str_to_currency(str: Option<&str>) -> Option<i64> {
    // Check for NULL pointer equivalent
    let str = str?;
    
    // Use the global TMP variable
    let mut tmp_guard = TMP.lock().unwrap();
    let tmp = &mut *tmp_guard;
    
    // Convert string to bytes and copy to tmp buffer
    let bytes = str.as_bytes();
    let copy_len = bytes.len().min(tmp.len() - 1);
    tmp[..copy_len].copy_from_slice(&bytes[..copy_len]);
    tmp[copy_len] = 0; // Ensure null termination
    
    // Convert tmp buffer to string slice for processing
    let c_str = unsafe { CStr::from_bytes_with_nul_unchecked(&tmp[..=copy_len]) };
    let mut str_slice = c_str.to_str().unwrap();
    
    // Find the decimal point
    if let Some(dot_pos) = str_slice.find('.') {
        // Calculate the fractional part length
        let fractional_start = dot_pos + 1;
        let fractional_len = str_slice[fractional_start..].len();
        
        // Remove the decimal point by shifting fractional part left
        let mut bytes = tmp.to_vec();
        bytes.copy_within(fractional_start..fractional_start + fractional_len, dot_pos);
        bytes[dot_pos + fractional_len] = 0;
        
        // Update the string slice
        str_slice = unsafe { CStr::from_bytes_with_nul_unchecked(&bytes) }.to_str().unwrap();
        
        if fractional_len <= 4 {
            // Pad with zeros if needed
            let zeros_needed = 4 - fractional_len;
            let current_len = str_slice.len();
            let end_pos = current_len.min(tmp.len() - 1);
            
            // Append zeros
            for i in 0..zeros_needed {
                if end_pos + i < tmp.len() - 1 {
                    tmp[end_pos + i] = b'0';
                }
            }
            tmp[end_pos + zeros_needed] = 0;
        } else {
            // Truncate to 4 decimal places
            let truncate_pos = dot_pos + 4;
            if truncate_pos < tmp.len() - 1 {
                tmp[truncate_pos] = 0;
            }
        }
    } else {
        // No decimal point found, append "0000"
        let current_len = str_slice.len();
        let end_pos = current_len.min(tmp.len() - 5); // Leave space for "0000" and null terminator
        
        if end_pos + 4 < tmp.len() {
            tmp[end_pos] = b'0';
            tmp[end_pos + 1] = b'0';
            tmp[end_pos + 2] = b'0';
            tmp[end_pos + 3] = b'0';
            tmp[end_pos + 4] = 0;
        }
    }
    
    // Convert the processed string back to &str and call atoi64
    let result_str = unsafe { CStr::from_ptr(tmp.as_ptr() as *const c_char) }
        .to_str()
        .ok()?;
    
    atoi64(Some(result_str))
}
pub fn float_to_currency(value: f64) -> Option<i64> {
    let buf = format!("{:.4}", value); // Equivalent to snprintf with "%.4f" format
    str_to_currency(Some(&buf)) // Convert the formatted string to currency
}
pub fn mul_currency(value1: int64, value2: int64) -> int64 {
    (value1 * value2) / 10000
}
pub fn div_currency(value1: int64, value2: int64) -> int64 {
    (value1 * 10000) / value2
}
pub fn str_to_date(datestr: Option<&str>) -> Option<u16> {
    // Check for NULL pointer equivalent
    let datestr = datestr?;
    
    // Use the global TMP buffer
    let mut tmp_guard = TMP.lock().unwrap();
    let tmp_slice = &mut tmp_guard[..];
    
    // Copy string to tmp buffer (simulating strcpy)
    let bytes_to_copy = std::cmp::min(datestr.len(), tmp_slice.len() - 1);
    tmp_slice[..bytes_to_copy].copy_from_slice(&datestr.as_bytes()[..bytes_to_copy]);
    tmp_slice[bytes_to_copy] = 0; // Null terminate
    
    // Convert tmp buffer to mutable c_char slice for stripchr
    let tmp_slice_mut: &mut [c_char] = unsafe {
        std::slice::from_raw_parts_mut(tmp_slice.as_mut_ptr() as *mut c_char, tmp_slice.len())
    };
    
    // Call stripchr to get next pointer
    let next_ptr = stripchr(Some(tmp_slice_mut), b'-' as i32)?;
    
    // Parse year (first segment) - use the original tmp_slice (u8 slice) for creating CStr
    let year_c_str = unsafe { CStr::from_ptr(tmp_slice.as_ptr() as *const c_char) };
    let year = year_c_str.to_str().ok()?.parse::<i32>().ok()? - 1900;
    
    // Parse month (second segment) - use the pointer returned by stripchr
    let month_c_str = unsafe { CStr::from_ptr(next_ptr.as_ptr() as *const c_char) };
    let month = month_c_str.to_str().ok()?.parse::<i32>().ok()?;
    
    // Get next segment for day
    let day_ptr = stripchr(Some(next_ptr), b'-' as i32)?;
    
    // Parse day (third segment)
    let day_c_str = unsafe { CStr::from_ptr(day_ptr.as_ptr() as *const c_char) };
    let day = day_c_str.to_str().ok()?.parse::<i32>().ok()?;
    
    // Combine into date format
    let date = ((day << 11) | (month << 7)) | year;
    
    Some(date as u16)
}


pub fn currency_to_str(value: int64) -> Option<String> {
    let mut tmp_guard = TMP.lock().unwrap();
    let tmp = &mut *tmp_guard;
    
    // Convert int64 to string, return None if conversion fails
    i64toa(value, tmp, 10)?;
    
    // Find the length of the null-terminated string
    let mut size = 0;
    while size < tmp.len() && tmp[size] != 0 {
        size += 1;
    }
    
    if size > 4 {
        let ptr_idx = size - 4;
        
        // Move the last 4 digits + null terminator one position to the right
        for i in (ptr_idx..=size).rev() {
            tmp[i + 1] = tmp[i];
        }
        
        // Insert decimal point
        tmp[ptr_idx] = b'.';
        size += 1; // Account for the added decimal point
    } else {
        let move_amount = 6 - size; // 2 (for "0.") + 4 digits - size
        
        // Move the existing string to the right
        for i in (0..size).rev() {
            tmp[i + move_amount] = tmp[i];
        }
        
        // Fill the beginning with "0." and zeros
        tmp[0] = b'0';
        tmp[1] = b'.';
        
        for i in 2..move_amount {
            tmp[i] = b'0';
        }
        
        // Ensure null termination
        tmp[size + move_amount] = 0;
        size = size + move_amount;
    }
    
    // Ensure null termination for string conversion
    tmp[size] = 0;
    
    // Convert to String and return as Some
    Some(String::from_utf8_lossy(&tmp[..size]).into_owned())
}

pub fn currency_to_float(value: int64) -> Option<f64> {
    // Call currency_to_str to get the string representation
    let currency_str = currency_to_str(value)?;
    
    // Parse the string into f64, returning None if parsing fails
    f64::from_str(&currency_str).ok()
}

pub fn test_virtual_types() {
    let mut list: Option<Box<BinnStruct>> = None;
    let mut ptr: Option<*mut u8> = None;
    let mut storage_type: i32 = 0;
    let mut extra_type: i32 = 0;
    let mut value: BOOL = 0;
    
    print!("testing binn virtual types... ");
    
    assert!(binn_get_type_info(0x80061, Some(&mut storage_type), Some(&mut extra_type)) == 1);
    assert!(storage_type == 0x60);
    assert!(extra_type == 1);
    
    list = binn_list();
    assert!(list.is_some());
    
    {
        let list_ref = &mut list;
        assert!(binn_list_add_bool(list_ref, 1) == 1);
        assert!(binn_list_add_bool(list_ref, 0) == 1);
        assert!(binn_list_add_null(list_ref) == 1);
    }
    
    ptr = binn_ptr(list.as_mut().map(|b| b.as_mut() as *mut _ as *mut u8));
    assert!(ptr.is_some());
    
    let ptr_slice = unsafe { std::slice::from_raw_parts(ptr.unwrap(), 0) };
    assert!(binn_list_get_bool(Some(ptr_slice), 1, Some(&mut value)) == 1);
    assert!(value == 1);
    assert!(binn_list_get_bool(Some(ptr_slice), 2, Some(&mut value)) == 1);
    assert!(value == 0);
    assert!(binn_list_null(Some(ptr_slice), 3) == 1);
    assert!(binn_list_null(Some(ptr_slice), 1) == 0);
    assert!(binn_list_null(Some(ptr_slice), 2) == 0);
    assert!(binn_list_get_bool(Some(ptr_slice), 3, Some(&mut value)) == 0);
    
    binn_free(&mut list);
    println!("OK");
}
pub fn test_value_conversion() {
    let mut value: Option<Box<BinnStruct>>;
    let mut ptr: &str;
    let mut blob: [u8; 64] = *b"test blob\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    let mut pblob: &[u8];
    let mut size: i32;
    let mut vint32: i32 = 0;
    let mut vint64_local: int64 = 0;
    let mut vdouble: f64 = 0.0;
    let mut vbool_local: BOOL = 0;
    
    println!("testing binn value conversion... ");
    
    ptr = "static string";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);
    
    ptr = "transient string";
    value = binn_string(Some(ptr), Some(Box::new(|_| {})));
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    let value_ptr = value_ref.ptr.as_ref().unwrap();
    let value_bytes = unsafe { std::slice::from_raw_parts(value_ptr.as_ref() as *const _ as *const u8, ptr.len()) };
    assert!(value_bytes == ptr.as_bytes());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    ptr = "dynamic allocated string";
    let c_str = std::ffi::CString::new(ptr).unwrap();
    let dup_ptr = unsafe { libc::strdup(c_str.as_ptr()) };
    value = binn_string(Some(unsafe { &std::ffi::CStr::from_ptr(dup_ptr).to_str().unwrap() }), Some(Box::new(|p| {
        if let Some(mut boxed) = p {
            unsafe {
                let _ = Box::from_raw(boxed.as_mut() as *mut _ as *mut c_char);
            }
        }
    })));
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == dup_ptr as *const ());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    size = 64;
    pblob = &blob[..9];
    value = binn_blob(Some(pblob), size, None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xC0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == pblob.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);
    
    size = 64;
    pblob = &blob[..9];
    value = binn_blob(Some(pblob), size, Some(Box::new(|_| {})));
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xC0);
    assert!(value_ref.ptr.is_some());
    let value_ptr = value_ref.ptr.as_ref().unwrap();
    let value_blob = unsafe { std::slice::from_raw_parts(value_ptr.as_ref() as *const _ as *const u8, pblob.len()) };
    assert!(value_blob == pblob);
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    size = 64;
    pblob = &blob[..9];
    let dup_pblob = memdup(Some(pblob), size).unwrap();
    value = binn_blob(Some(&dup_pblob), size, Some(Box::new(|p| {
        if let Some(mut boxed) = p {
            unsafe {
                let _ = Box::from_raw(boxed.as_mut() as *mut _ as *mut u8);
            }
        }
    })));
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xC0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == dup_pblob.as_ptr() as *const ());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    ptr = "123";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == ptr);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == 123);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == 123);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, 123.0, 4));
    value = binn_string(Some(ptr), None);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);
    
    ptr = "-456";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == ptr);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == -456);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == -456);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, -456.0, 4));
    value = binn_string(Some(ptr), None);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);
    
    ptr = "-4.56";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == ptr);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == -4);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == -4);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, -4.56, 4));
    value = binn_string(Some(ptr), None);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ == ptr.as_ptr() as *const ());
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);
    
    ptr = "yes";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == ptr);
    value = binn_string(Some(ptr), None);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    binn_free(&mut value);
    
    ptr = "no";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    binn_free(&mut value);
    
    ptr = "on";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    binn_free(&mut value);
    
    ptr = "off";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    binn_free(&mut value);
    
    ptr = "true";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    binn_free(&mut value);
    
    ptr = "false";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    binn_free(&mut value);
    
    ptr = "1";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    binn_free(&mut value);
    
    ptr = "0";
    value = binn_string(Some(ptr), None);
    assert!(value.is_some());
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    binn_free(&mut value);
    
    value = binn_int32(-345);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x61);
    assert!(value_ref.value.vint32 == -345);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == -345);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == -345);
    value = binn_int32(-345);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, -345.0, 4));
    value = binn_int32(-345);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x61);
    assert!(value_ref.value.vint32 == -345);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "-345");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_int32(0);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x61);
    assert!(value_ref.value.vint32 == 0);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == 0);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == 0);
    value = binn_int32(0);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, 0.0, 4));
    value = binn_int32(0);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x61);
    assert!(value_ref.value.vint32 == 0);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "0");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_int64(-345678);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x81);
    assert!(value_ref.value.vint64 == -345678);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == -345678);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == -345678);
    value = binn_int64(-345678);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, -345678.0, 4));
    value = binn_int64(-345678);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x81);
    assert!(value_ref.value.vint64 == -345678);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "-345678");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_double(-345.678);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x82);
    assert!(value_ref.value.vdouble == -345.678);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == -345);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == -345);
    value = binn_double(-345.678);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, -345.678, 4));
    value = binn_double(-345.678);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x82);
    assert!(value_ref.value.vdouble == -345.678);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "-345.678");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_double(0.0);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x82);
    assert!(value_ref.value.vdouble == 0.0);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == 0);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == 0);
    value = binn_double(0.0);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, 0.0, 4));
    value = binn_double(0.0);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x82);
    assert!(value_ref.value.vdouble == 0.0);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "0");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_bool(0);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x80061);
    assert!(value_ref.value.vbool == 0);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == 0);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == 0);
    value = binn_bool(0);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, 0.0, 4));
    value = binn_bool(0);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 0);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x80061);
    assert!(value_ref.value.vbool == 0);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "false");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    value = binn_bool(1);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x80061);
    assert!(value_ref.value.vbool == 1);
    assert!(value_ref.freefn.is_none());
    assert!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)) == 1);
    assert!(vint32 == 1);
    assert!(binn_get_int64(value.take(), Some(&mut vint64_local)) == 1);
    assert!(vint64_local == 1);
    value = binn_bool(1);
    assert!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)));
    assert!(AlmostEqualFloats(vdouble as f32, 1.0, 4));
    value = binn_bool(1);
    assert!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool_local)) == 1);
    assert!(vbool_local == 1);
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0x80061);
    assert!(value_ref.value.vbool == 1);
    assert!(value_ref.freefn.is_none());
    let result_str = binn_get_str(value.take());
    assert!(result_str.is_some());
    let binding = result_str.unwrap();
    let result_cstr = CStr::from_bytes_with_nul(binding.to_bytes_with_nul()).unwrap();
    assert!(result_cstr.to_str().unwrap() == "true");
    let value_ref = value.as_ref().unwrap();
    assert!(value_ref.type_ == 0xA0);
    assert!(value_ref.ptr.is_some());
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);
    
    println!("OK");
}
// Global variables are defined in dependencies, so we don't redefine them here

pub fn test_int_conversion() {
    println!("testing integer conversion...");
    
    // Test cases for vint8 to various unsigned types
    unsafe { VINT8 = -110; }
    let mut vuint8: vuint8 = 0;
    assert!(copy_int_value(None, None, 0x21, 0x20) == false);
    unsafe { assert!(VINT8 == -110); }
    assert!(vuint8 == 0);

    unsafe { VINT8 = -110; }
    let mut vuint16: vuint16 = 0;
    assert!(copy_int_value(None, None, 0x21, 0x40) == false);
    unsafe { assert!(VINT8 == -110); }
    assert!(vuint16 == 0);

    unsafe { VINT8 = -110; }
    let mut vuint32: vuint32 = 0;
    assert!(copy_int_value(None, None, 0x21, 0x60) == false);
    unsafe { assert!(VINT8 == -110); }
    assert!(vuint32 == 0);

    unsafe { VINT8 = -110; }
    let mut vuint64: vuint64 = 0;
    assert!(copy_int_value(None, None, 0x21, 0x80) == false);
    unsafe { assert!(VINT8 == -110); }
    assert!(vuint64 == 0);

    // Test cases for vint16 to various unsigned types
    let mut vint16: vint16 = -123;
    let mut vuint8: vuint8 = 0;
    assert!(copy_int_value(None, None, 0x41, 0x20) == false);
    assert!(vint16 == -123);
    assert!(vuint8 == 0);

    let mut vint16: vint16 = -123;
    let mut vuint16: vuint16 = 0;
    assert!(copy_int_value(None, None, 0x41, 0x40) == false);
    assert!(vint16 == -123);
    assert!(vuint16 == 0);

    let mut vint16: vint16 = -32000;
    let mut vuint32: vuint32 = 0;
    assert!(copy_int_value(None, None, 0x41, 0x60) == false);
    assert!(vint16 == -32000);
    assert!(vuint32 == 0);

    let mut vint16: vint16 = -32000;
    let mut vuint64: vuint64 = 0;
    assert!(copy_int_value(None, None, 0x41, 0x80) == false);
    assert!(vint16 == -32000);
    assert!(vuint64 == 0);

    // Test cases for vint32 to various unsigned types
    VINT32.store(-123, Ordering::SeqCst);
    let mut vuint8: vuint8 = 0;
    assert!(copy_int_value(None, None, 0x61, 0x20) == false);
    assert!(VINT32.load(Ordering::SeqCst) == -123);
    assert!(vuint8 == 0);

    VINT32.store(-123, Ordering::SeqCst);
    let mut vuint16: vuint16 = 0;
    assert!(copy_int_value(None, None, 0x61, 0x40) == false);
    assert!(VINT32.load(Ordering::SeqCst) == -123);
    assert!(vuint16 == 0);

    VINT32.store(-123, Ordering::SeqCst);
    let mut vuint32: vuint32 = 0;
    assert!(copy_int_value(None, None, 0x61, 0x60) == false);
    assert!(VINT32.load(Ordering::SeqCst) == -123);
    assert!(vuint32 == 0);

    VINT32.store(-123, Ordering::SeqCst);
    let mut vuint64: vuint64 = 0;
    assert!(copy_int_value(None, None, 0x61, 0x80) == false);
    assert!(VINT32.load(Ordering::SeqCst) == -123);
    assert!(vuint64 == 0);

    // Test cases for vint64 to various unsigned types
    unsafe { vint64 = -123; }
    let mut vuint8: vuint8 = 0;
    assert!(copy_int_value(None, None, 0x81, 0x20) == false);
    unsafe { assert!(vint64 == -123); }
    assert!(vuint8 == 0);

    unsafe { vint64 = -123; }
    let mut vuint16: vuint16 = 0;
    assert!(copy_int_value(None, None, 0x81, 0x40) == false);
    unsafe { assert!(vint64 == -123); }
    assert!(vuint16 == 0);

    unsafe { vint64 = -123; }
    let mut vuint32: vuint32 = 0;
    assert!(copy_int_value(None, None, 0x81, 0x60) == false);
    unsafe { assert!(vint64 == -123); }
    assert!(vuint32 == 0);

    unsafe { vint64 = -123; }
    let mut vuint64: vuint64 = 0;
    assert!(copy_int_value(None, None, 0x81, 0x80) == false);
    unsafe { assert!(vint64 == -123); }
    assert!(vuint64 == 0);

    println!("OK");
}
pub fn test_create_object_2(psize: &mut i32) -> Option<CString> {
	println!("\n* test_create_object_2");
    println!("creating object 2...");

    let mut obj = binn_object();
    assert!(obj.is_some());

    assert_eq!(binn_object_set_int32(&mut obj, Some("int32"), -12345), 1);
    assert_eq!(binn_object_set_int16(&mut obj, Some("int16"), -258), 1);
    assert_eq!(binn_object_set_int8(&mut obj, Some("int8"), -120), 1);
    assert_eq!(binn_object_set_int64(&mut obj, Some("int64"), -1234567890123), 1);
    assert_eq!(binn_object_set_uint32(&mut obj, Some("uint32"), 123456), 1);
    assert_eq!(binn_object_set_uint16(&mut obj, Some("uint16"), 60500), 1);
    assert_eq!(binn_object_set_uint8(&mut obj, Some("uint8"), 250), 1);
    assert_eq!(binn_object_set_uint64(&mut obj, Some("uint64"), 1234567890123), 1);
    assert_eq!(binn_object_set_float(&mut obj, Some("float32"), -12.345), 1);
    
    unsafe {
        vfloat32 = -12.345;
        let mut boxed_float = Box::new(vfloat32) as Box<dyn std::any::Any>;
        assert_eq!(binn_object_set(&mut obj, Some("single"), 0x62, Some(&mut Some(boxed_float)), 0), 1);
    }
    
    assert_eq!(binn_object_set_double(&mut obj, Some("float64"), -123456.7895), 1);
    
    unsafe {
        vfloat64 = -123456.7895;
        let mut boxed_double = Box::new(vfloat64) as Box<dyn std::any::Any>;
        assert_eq!(binn_object_set(&mut obj, Some("double"), 0x82, Some(&mut Some(boxed_double)), 0), 1);
    }
    
    assert_eq!(binn_object_set_str(&mut obj, Some("str"), Some("the value")), 1);
    assert_eq!(binn_object_set_bool(&mut obj, Some("bool_true"), 1), 1);
    assert_eq!(binn_object_set_bool(&mut obj, Some("bool_false"), 0), 1);
    assert_eq!(binn_object_set_null(&mut obj, Some("null")), 1);

    let mut list = binn_list();
    assert!(list.is_some());
    assert_eq!(binn_list_add_null(&mut list), 1);
    assert_eq!(binn_list_add_int32(&mut list, 123), 1);
    assert_eq!(binn_list_add_str(&mut list, Some(&mut Some(Box::new("this is a string") as Box<dyn std::any::Any>))), 1);
    
    let list_ptr = unsafe { std::mem::transmute::<_, *mut u8>(list.as_mut().unwrap().as_mut()) };
    assert_eq!(binn_object_set_list(&mut obj, Some("list"), binn_ptr(Some(list_ptr))), 1);

    binn_free(&mut list);
    
    let obj_ptr = unsafe { std::mem::transmute::<_, *mut u8>(obj.as_mut().unwrap().as_mut()) };
    *psize = binn_size(binn_ptr(Some(obj_ptr)));
    unsafe {
        let ptr = binn_ptr(Some(obj_ptr)).unwrap_or(std::ptr::null_mut());
        if ptr.is_null() {
            None
        } else {
            Some(CString::new(std::ffi::CStr::from_ptr(ptr as *const i8).to_bytes()).unwrap())
        }
    }
}
pub fn test_create_object_1(psize: &mut i32) -> Option<*const u8> {
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut list: Option<Box<BinnStruct>> = None;
    
    println!("creating object 1...");
    
    obj = binn_object();
    assert!(obj.is_some());
    
    unsafe {
        VINT32.store(-12345, Ordering::SeqCst);
        let vint32_val = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_set(&mut obj, Some("int32"), 0x61, Some(&mut Some(Box::new(vint32_val) as Box<dyn Any>)), 0) == 1);
        
        let vint16_val: i16 = -258;
        assert!(binn_object_set(&mut obj, Some("int16"), 0x41, Some(&mut Some(Box::new(vint16_val) as Box<dyn Any>)), 0) == 1);
        
        VINT8 = -120;
        assert!(binn_object_set(&mut obj, Some("int8"), 0x21, Some(&mut Some(Box::new(VINT8) as Box<dyn Any>)), 0) == 1);
        
        vint64 = -1234567890123;
        assert!(binn_object_set(&mut obj, Some("int64"), 0x81, Some(&mut Some(Box::new(vint64) as Box<dyn Any>)), 0) == 1);
        
        let vuint32_val: u32 = 123456;
        assert!(binn_object_set(&mut obj, Some("uint32"), 0x60, Some(&mut Some(Box::new(vuint32_val) as Box<dyn Any>)), 0) == 1);
        
        let vuint16_val: u16 = 60500;
        assert!(binn_object_set(&mut obj, Some("uint16"), 0x40, Some(&mut Some(Box::new(vuint16_val) as Box<dyn Any>)), 0) == 1);
        
        let vuint8_val: u8 = 250;
        assert!(binn_object_set(&mut obj, Some("uint8"), 0x20, Some(&mut Some(Box::new(vuint8_val) as Box<dyn Any>)), 0) == 1);
        
        let vuint64_val: u64 = 1234567890123;
        assert!(binn_object_set(&mut obj, Some("uint64"), 0x80, Some(&mut Some(Box::new(vuint64_val) as Box<dyn Any>)), 0) == 1);
        
        vfloat32 = -12.345;
        assert!(binn_object_set(&mut obj, Some("float32"), 0x62, Some(&mut Some(Box::new(vfloat32) as Box<dyn Any>)), 0) == 1);
        
        vfloat32 = -12.345;
        assert!(binn_object_set(&mut obj, Some("single"), 0x62, Some(&mut Some(Box::new(vfloat32) as Box<dyn Any>)), 0) == 1);
        
        vfloat64 = -123456.7895;
        assert!(binn_object_set(&mut obj, Some("float64"), 0x82, Some(&mut Some(Box::new(vfloat64) as Box<dyn Any>)), 0) == 1);
        
        vfloat64 = -123456.7895;
        assert!(binn_object_set(&mut obj, Some("double"), 0x82, Some(&mut Some(Box::new(vfloat64) as Box<dyn Any>)), 0) == 1);
    }
    
    let str_val = "the value";
    assert!(binn_object_set(&mut obj, Some("str"), 0xA0, Some(&mut Some(Box::new(str_val) as Box<dyn Any>)), 0) == 1);
    
    unsafe {
        VINT32.store(1, Ordering::SeqCst);
        let bool_true_val = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_set(&mut obj, Some("bool_true"), 0x80061, Some(&mut Some(Box::new(bool_true_val) as Box<dyn Any>)), 0) == 1);
        
        VINT32.store(0, Ordering::SeqCst);
        let bool_false_val = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_set(&mut obj, Some("bool_false"), 0x80061, Some(&mut Some(Box::new(bool_false_val) as Box<dyn Any>)), 0) == 1);
    }
    
    assert!(binn_object_set(&mut obj, Some("null"), 0x00, None, 0) == 1);
    
    list = binn_list();
    assert!(list.is_some());
    
    assert!(binn_list_add(&mut list, 0x00, None, 0) == 1);
    
    unsafe {
        VINT32.store(123, Ordering::SeqCst);
        let list_int_val = VINT32.load(Ordering::SeqCst);
        assert!(binn_list_add(&mut list, 0x61, Some(&mut Some(Box::new(list_int_val) as Box<dyn Any>)), 0) == 1);
    }
    
    let list_str_val = "this is a string";
    assert!(binn_list_add(&mut list, 0xA0, Some(&mut Some(Box::new(list_str_val) as Box<dyn Any>)), 0) == 1);
    
    let list_ptr = binn_ptr(list.as_mut().map(|b| Box::as_mut(b) as *mut _ as *mut u8));
    let list_size = binn_size(list.as_mut().map(|b| Box::as_mut(b) as *mut _ as *mut u8));
    assert!(binn_object_set(&mut obj, Some("list"), 0xE0, Some(&mut Some(Box::new(list_ptr) as Box<dyn Any>)), list_size) == 1);
    
    binn_free(&mut list);
    list = None;
    
    *psize = binn_size(obj.as_mut().map(|b| Box::as_mut(b) as *mut _ as *mut u8));
    
    // Return Option<*const u8> to match expected type at call site
    binn_ptr(obj.as_mut().map(|b| Box::as_mut(b) as *mut _ as *mut u8)).map(|p| p as *const u8)
}
pub fn test_binn_read(objptr: Option<&[u8]>) {
    let mut listptr: Option<&[u8]> = None;
    let mut ptr: Option<String> = None;
    let mut value: Option<Box<BinnStruct>> = None;
    
    println!("OK\nreading:");
    
    VINT32.store(0, Ordering::SeqCst);
    assert!(binn_object_get(objptr, Some("int32"), 0x61, Some(&mut VINT32.load(Ordering::SeqCst) as &mut dyn Any), None) == 1);
    println!("int32: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == -12345);
    
    let mut vint16: vint16 = 0;
    assert!(binn_object_get(objptr, Some("int16"), 0x41, Some(&mut vint16 as &mut dyn Any), None) == 1);
    println!("int16: {}", vint16);
    assert!(vint16 == -258);
    
    let mut vint8: i8 = 0;
    assert!(binn_object_get(objptr, Some("int8"), 0x21, Some(&mut vint8 as &mut dyn Any), None) == 1);
    println!("int8: {}", vint8);
    assert!(vint8 == -120);
    
    unsafe {
        vint64 = 0;
    }
    assert!(binn_object_get(objptr, Some("int64"), 0x81, Some(unsafe { &mut vint64 } as &mut dyn Any), None) == 1);
    println!("int64: {}", unsafe { vint64 });
    assert!(unsafe { vint64 } == -1234567890123);
    
    let mut vuint32: vuint32 = 0;
    assert!(binn_object_get(objptr, Some("uint32"), 0x60, Some(&mut vuint32 as &mut dyn Any), None) == 1);
    println!("uint32: {}", vuint32);
    assert!(vuint32 == 123456);
    
    let mut vuint16: vuint16 = 0;
    assert!(binn_object_get(objptr, Some("uint16"), 0x40, Some(&mut vuint16 as &mut dyn Any), None) == 1);
    println!("uint16: {}", vuint16);
    assert!(vuint16 == 60500);
    
    let mut vuint8: vuint8 = 0;
    assert!(binn_object_get(objptr, Some("uint8"), 0x20, Some(&mut vuint8 as &mut dyn Any), None) == 1);
    println!("uint8: {}", vuint8);
    assert!(vuint8 == 250);
    
    let mut vuint64: vuint64 = 0;
    assert!(binn_object_get(objptr, Some("uint64"), 0x80, Some(&mut vuint64 as &mut dyn Any), None) == 1);
    println!("uint64: {}", vuint64);
    assert!(vuint64 == 1234567890123);
    
    unsafe {
        vfloat32 = 0.0;
    }
    assert!(binn_object_get(objptr, Some("float32"), 0x62, Some(unsafe { &mut vfloat32 } as &mut dyn Any), None) == 1);
    println!("float32: {}", unsafe { vfloat32 });
    assert!(AlmostEqualFloats(unsafe { vfloat32 }, -12.345, 2));
    
    unsafe {
        vfloat64 = 0.0;
    }
    assert!(binn_object_get(objptr, Some("float64"), 0x82, Some(unsafe { &mut vfloat64 } as &mut dyn Any), None) == 1);
    println!("float64: {}", unsafe { vfloat64 });
    assert!((unsafe { vfloat64 } - (-123456.7895)) < 0.01);
    
    unsafe {
        vfloat32 = 0.0;
    }
    assert!(binn_object_get(objptr, Some("single"), 0x62, Some(unsafe { &mut vfloat32 } as &mut dyn Any), None) == 1);
    println!("single: {}", unsafe { vfloat32 });
    assert!(AlmostEqualFloats(unsafe { vfloat32 }, -12.345, 2));
    
    unsafe {
        vfloat64 = 0.0;
    }
    assert!(binn_object_get(objptr, Some("double"), 0x82, Some(unsafe { &mut vfloat64 } as &mut dyn Any), None) == 1);
    println!("double: {}", unsafe { vfloat64 });
    assert!((unsafe { vfloat64 } - (-123456.7895)) < 0.01);
    
    ptr = None;
    assert!(binn_object_get(objptr, Some("str"), 0xA0, Some(&mut ptr as &mut dyn Any), None) == 1);
    println!("ptr: '{:?}'", ptr);
    assert!(ptr.as_deref() == Some("the value"));
    
    VINT32.store(999, Ordering::SeqCst);
    assert!(binn_object_get(objptr, Some("bool_true"), 0x80061, Some(&mut VINT32.load(Ordering::SeqCst) as &mut dyn Any), None) == 1);
    println!("bool true: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 1);
    
    VINT32.store(999, Ordering::SeqCst);
    assert!(binn_object_get(objptr, Some("bool_false"), 0x80061, Some(&mut VINT32.load(Ordering::SeqCst) as &mut dyn Any), None) == 1);
    println!("bool false: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 0);
    
    VINT32.store(999, Ordering::SeqCst);
    assert!(binn_object_get(objptr, Some("null"), 0x00, Some(&mut VINT32.load(Ordering::SeqCst) as &mut dyn Any), None) == 1);
    println!("null: {}", VINT32.load(Ordering::SeqCst));
    assert!(binn_object_get(objptr, Some("null"), 0x00, None, None) == 1);
    
    assert!(binn_object_get(objptr, Some("list"), 0xE0, Some(&mut listptr as &mut dyn Any), None) == 1);
    println!("obj ptr: {:?}  list ptr: {:?}", objptr, listptr);
    assert!(listptr.is_some());
    assert!(listptr.unwrap().as_ptr() > objptr.unwrap().as_ptr());
    
    VINT32.store(0, Ordering::SeqCst);
    assert!(binn_list_get(listptr, 2, 0x61, Some(&mut VINT32.load(Ordering::SeqCst) as &mut dyn Any), None) == 1);
    println!("int32: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 123);
    
    ptr = None;
    assert!(binn_list_get(listptr, 3, 0xA0, Some(&mut ptr as &mut dyn Any), None) == 1);
    println!("ptr: '{:?}'", ptr);
    assert!(ptr.as_deref() == Some("this is a string"));
    
    VINT32.store(0, Ordering::SeqCst);
    assert!(binn_object_get_int32(objptr, Some("int32"), Some(&mut VINT32.load(Ordering::SeqCst))) == true);
    println!("int32: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == -12345);
    
    vint16 = 0;
    assert!(binn_object_get_int16(objptr, Some("int16"), Some(&mut vint16)) == true);
    println!("int16: {}", vint16);
    assert!(vint16 == -258);
    
    vint8 = 0;
    assert!(binn_object_get_int8(objptr, Some("int8"), Some(&mut vint8)) == true);
    println!("int8: {}", vint8);
    assert!(vint8 == -120);
    
    unsafe {
        vint64 = 0;
    }
    assert!(binn_object_get_int64(objptr, Some("int64"), Some(unsafe { &mut vint64 })) == true);
    println!("int64: {}", unsafe { vint64 });
    assert!(unsafe { vint64 } == -1234567890123);
    
    vuint32 = 0;
    assert!(binn_object_get_uint32(objptr, Some("uint32"), Some(&mut vuint32)) == true);
    println!("uint32: {}", vuint32);
    assert!(vuint32 == 123456);
    
    vuint16 = 0;
    assert!(binn_object_get_uint16(objptr, Some("uint16"), Some(&mut vuint16)) == true);
    println!("uint16: {}", vuint16);
    assert!(vuint16 == 60500);
    
    vuint8 = 0;
    assert!(binn_object_get_uint8(objptr, Some("uint8"), Some(&mut vuint8)) == true);
    println!("uint8: {}", vuint8);
    assert!(vuint8 == 250);
    
    vuint64 = 0;
    assert!(binn_object_get_uint64(objptr, Some("uint64"), Some(&mut vuint64)) == true);
    println!("uint64: {}", vuint64);
    assert!(vuint64 == 1234567890123);
    
    unsafe {
        vfloat32 = 0.0;
    }
    assert!(binn_object_get_float(objptr, Some("float32"), Some(unsafe { &mut vfloat32 })) == true);
    println!("float32: {}", unsafe { vfloat32 });
    assert!(AlmostEqualFloats(unsafe { vfloat32 }, -12.345, 2));
    
    unsafe {
        vfloat64 = 0.0;
    }
    assert!(binn_object_get_double(objptr, Some("float64"), Some(unsafe { &mut vfloat64 })) == true);
    println!("float64: {}", unsafe { vfloat64 });
    assert!(AlmostEqualFloats(unsafe { vfloat32 }, -12.345, 2));
    
    ptr = None;
    assert!(binn_object_get_str(objptr, Some("str"), Some(&mut ptr as &mut dyn Any)) == 1);
    println!("ptr: '{:?}'", ptr);
    assert!(ptr.as_deref() == Some("the value"));
    
    VINT32.store(999, Ordering::SeqCst);
    assert!(binn_object_get_bool(objptr, Some("bool_true"), Some(&mut VINT32.load(Ordering::SeqCst) as &mut BOOL)) == 1);
    println!("bool true: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 1);
    
    VINT32.store(999, Ordering::SeqCst);
    assert!(binn_object_get_bool(objptr, Some("bool_false"), Some(&mut VINT32.load(Ordering::SeqCst) as &mut BOOL)) == 1);
    println!("bool false: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 0);
    
    unsafe {
        vbool = 0;
    }
    assert!(binn_object_null(objptr, Some("null")) == true);
    assert!(binn_object_null(objptr, Some("bool_true")) == false);
    
    assert!(binn_object_get_list(objptr, Some("list"), Some(&mut listptr as &mut dyn Any)) == 1);
    println!("obj ptr: {:?}  list ptr: {:?}", objptr, listptr);
    assert!(listptr.is_some());
    assert!(listptr.unwrap().as_ptr() > objptr.unwrap().as_ptr());
    
    VINT32.store(0, Ordering::SeqCst);
    assert!(binn_list_get_int32(listptr, 2, Some(&mut VINT32.load(Ordering::SeqCst))) != 0);
    println!("int32: {}", VINT32.load(Ordering::SeqCst));
    assert!(VINT32.load(Ordering::SeqCst) == 123);
    
    ptr = None;
    assert!(binn_list_get_str(listptr, 3, Some(&mut ptr as &mut dyn Any)) == 1);
    println!("ptr: '{:?}'", ptr);
    assert!(ptr.as_deref() == Some("this is a string"));
    
    let vint32_val = binn_object_int32(objptr, Some("int32"));
    println!("int32: {}", vint32_val);
    assert!(vint32_val == -12345);
    
    let vint16_val = binn_object_int16(objptr, Some("int16"));
    println!("int16: {}", vint16_val);
    assert!(vint16_val == -258);
    
    let vint8_val = binn_object_int8(objptr, Some("int8")).unwrap();
    println!("int8: {}", vint8_val);
    assert!(vint8_val == -120);
    
    let vint64_val = binn_object_int64(objptr, Some("int64"));
    println!("int64: {}", vint64_val);
    assert!(vint64_val == -1234567890123);
    
    let vuint32_val = binn_object_uint32(objptr, Some("uint32"));
    println!("uint32: {}", vuint32_val);
    assert!(vuint32_val == 123456);
    
    let vuint16_val = binn_object_uint16(objptr, Some("uint16"));
    println!("uint16: {}", vuint16_val);
    assert!(vuint16_val == 60500);
    
    let vuint8_val = binn_object_uint8(objptr, Some("uint8"));
    println!("uint8: {}", vuint8_val);
    assert!(vuint8_val == 250);
    
    let vuint64_val = binn_object_uint64(objptr, Some("uint64"));
    println!("uint64: {}", vuint64_val);
    assert!(vuint64_val == 1234567890123);
    
    let vfloat32_val = binn_object_float(objptr, Some("float32"));
    println!("float32: {}", vfloat32_val);
    assert!(AlmostEqualFloats(vfloat32_val, -12.345, 2));
    
    let vfloat64_val = binn_object_double(objptr, Some("float64"));
    println!("float64: {}", vfloat64_val);
    assert!(AlmostEqualFloats(vfloat32_val, -12.345, 2));
    
    let ptr_val = binn_object_str(objptr, Some("str")).unwrap();
    println!("ptr: '{}'", ptr_val);
    assert!(ptr_val == "the value");
    
    let vint32_bool = binn_object_bool(objptr, Some("bool_true"));
    println!("bool true: {}", vint32_bool);
    assert!(vint32_bool == 1);
    
    let vint32_bool_false = binn_object_bool(objptr, Some("bool_false"));
    println!("bool false: {}", vint32_bool_false);
    assert!(vint32_bool_false == 0);
    
    assert!(binn_object_null(objptr, Some("null")) == true);
    assert!(binn_object_null(objptr, Some("nonull")) == false);
    
    let listptr_val = binn_object_list(objptr, Some("list"));
    println!("obj ptr: {:?}  list ptr: {:?}", objptr, listptr_val);
    assert!(listptr_val.is_some());
    
    let vint32_list = binn_list_int32(listptr, 2);
    println!("int32: {}", vint32_list);
    assert!(vint32_list == 123);
    
    let ptr_list = binn_list_str(listptr, 3).unwrap();
    println!("ptr: '{}'", ptr_list);
    assert!(ptr_list == "this is a string");
    
    assert!(binn_object_get_value(objptr, Some("int32"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vint16 == -12345);
    
    assert!(binn_object_get_value(objptr, Some("int16"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vint16 == -258);
    
    assert!(binn_object_get_value(objptr, Some("int8"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vint8 == -120);
    
    assert!(binn_object_get_value(objptr, Some("int64"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vint64 == -1234567890123);
    
    assert!(binn_object_get_value(objptr, Some("uint32"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vuint32 == 123456);
    
    assert!(binn_object_get_value(objptr, Some("uint16"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vuint16 == 60500);
    
    assert!(binn_object_get_value(objptr, Some("uint8"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vuint8 == 250);
    
    assert!(binn_object_get_value(objptr, Some("uint64"), Some(&mut value)) == 1);
    assert!(value.as_ref().unwrap().value.vuint64 == 1234567890123);
    
    println!("reading... OK");
}
pub fn test_binn_iter(use_int_compression: BOOL) {
    let mut list: Option<Box<BinnStruct>> = None;
    let mut map: Option<Box<BinnStruct>> = None;
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut list2: Option<Box<BinnStruct>> = None;
    let mut copy: Option<Box<BinnStruct>> = None;
    let mut iter: BinnIter = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };
    let mut iter2: BinnIter = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };
    let mut value: Option<Box<BinnStruct>> = None;
    let mut value2: Option<Box<BinnStruct>> = None;
    let blob_size: i32;
    let mut id: i32 = 0;
    let mut id2: i32 = 0;
    let list2size: i32;
    let mut ptr: Option<*mut u8> = None;
    let blob_ptr: *const c_char;
    let mut key: [u8; 256] = [0; 256];
    let mut key2: [u8; 256] = [0; 256];
    
    blob_ptr = b"key\0value\0\0".as_ptr() as *const c_char;
    blob_size = 11;
    
    println!("testing binn sequential read (use_int_compression = {})... ", use_int_compression);
    
    list = binn_list();
    list2 = binn_list();
    map = binn_map();
    obj = binn_object();
    
    assert!(list.is_some());
    assert!(list2.is_some());
    assert!(map.is_some());
    assert!(obj.is_some());
    
    if use_int_compression == 0 {
        if let Some(ref mut list_inner) = list {
            list_inner.disable_int_compression = 1;
        }
        if let Some(ref mut map_inner) = map {
            map_inner.disable_int_compression = 1;
        }
        if let Some(ref mut obj_inner) = obj {
            obj_inner.disable_int_compression = 1;
        }
    }
    
    assert_eq!(binn_list_add_int32(&mut list2, 250), 1);
    assert_eq!(binn_list_add_null(&mut list2), 1);
    let mut s1: Option<Box<dyn std::any::Any>> = Some(Box::new("l1st2"));
    assert_eq!(binn_list_add_str(&mut list2, Some(&mut s1)), 1);
    assert_eq!(binn_list_add_bool(&mut list2, 1), 1);
    list2size = binn_size(list2.as_ref().map(|b| b.as_ref() as *const _ as *mut u8));
    
    assert_eq!(binn_list_add_int8(&mut list, 111), 1);
    assert_eq!(binn_list_add_int32(&mut list, 123456789), 1);
    assert_eq!(binn_list_add_int16(&mut list, -123), 1);
    assert_eq!(binn_list_add_int64(&mut list, 9876543210), 1);
    assert_eq!(binn_list_add_float(&mut list, 1.25), 1);
    assert_eq!(binn_list_add_double(&mut list, 25.987654321), 1);
    assert_eq!(binn_list_add_bool(&mut list, 1), 1);
    assert_eq!(binn_list_add_bool(&mut list, 0), 1);
    assert_eq!(binn_list_add_null(&mut list), 1);
    let mut s2: Option<Box<dyn std::any::Any>> = Some(Box::new("testing..."));
    assert_eq!(binn_list_add_str(&mut list, Some(&mut s2)), 1);
    let mut blob: Option<Box<dyn std::any::Any>> = None;
    assert_eq!(binn_list_add_blob(&mut list, Some(&mut blob), blob_size), 1);
    assert_eq!(binn_list_add_list(&mut list, Some(&mut list2)), 1);
    
    assert_eq!(binn_object_set_int8(&mut obj, Some("a"), 111), 1);
    assert_eq!(binn_object_set_int32(&mut obj, Some("b"), 123456789), 1);
    assert_eq!(binn_object_set_int16(&mut obj, Some("c"), -123), 1);
    assert_eq!(binn_object_set_int64(&mut obj, Some("d"), 9876543210), 1);
    assert_eq!(binn_object_set_float(&mut obj, Some("e"), 1.25), 1);
    assert_eq!(binn_object_set_double(&mut obj, Some("f"), 25.987654321), 1);
    assert_eq!(binn_object_set_bool(&mut obj, Some("g"), 1), 1);
    assert_eq!(binn_object_set_bool(&mut obj, Some("h"), 0), 1);
    assert_eq!(binn_object_set_null(&mut obj, Some("i")), 1);
    assert_eq!(binn_object_set_str(&mut obj, Some("j"), Some("testing...")), 1);
    assert_eq!(binn_object_set_blob(&mut obj, Some("k"), None, blob_size), 1);
    assert_eq!(binn_object_set_list(&mut obj, Some("l"), list2.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 1);
    
    assert_eq!(binn_map_set_int8(&mut map, 55010, 111), 1);
    assert_eq!(binn_map_set_int32(&mut map, 55020, 123456789), 1);
    assert_eq!(binn_map_set_int16(&mut map, 55030, -123), 1);
    assert_eq!(binn_map_set_int64(&mut map, 55040, 9876543210), 1);
    assert_eq!(binn_map_set_float(&mut map, 55050, 1.25), 1);
    assert_eq!(binn_map_set_double(&mut map, 55060, 25.987654321), 1);
    assert_eq!(binn_map_set_bool(&mut map, 55070, 1), 1);
    assert_eq!(binn_map_set_bool(&mut map, 55080, 0), 1);
    assert_eq!(binn_map_set_null(&mut map, 55090), 1);
    let mut s3: Option<Box<dyn std::any::Any>> = Some(Box::new("testing..."));
    assert_eq!(binn_map_set_str(&mut map, 55100, Some(&mut s3)), 1);
    let mut blob2: Option<Box<dyn std::any::Any>> = None;
    assert_eq!(binn_map_set_blob(&mut map, 55110, Some(&mut blob2), blob_size), 1);
    assert_eq!(binn_map_set_list(&mut map, 55120, list2.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 1);
    
    ptr = binn_ptr(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8));
    assert!(ptr.is_some());
    assert!(binn_iter_init(Some(&mut iter), ptr.map(|p| unsafe { std::slice::from_raw_parts(p, 0) }), 0xE0));
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 0);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 1);
    assert_eq!(value.as_ref().unwrap().type_, 0x21);
    assert_eq!(value.as_ref().unwrap().value.vint8, 111);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 2);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x60);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x61);
    }
    assert_eq!(value.as_ref().unwrap().value.vint32, 123456789);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 3);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x21);
        assert_eq!(value.as_ref().unwrap().value.vint8, -123);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x41);
        assert_eq!(value.as_ref().unwrap().value.vint16, -123);
    }
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 4);
    assert_eq!(value.as_ref().unwrap().type_, 0x81);
    assert_eq!(value.as_ref().unwrap().value.vint64, 9876543210);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 5);
    assert_eq!(value.as_ref().unwrap().type_, 0x62);
    assert!(AlmostEqualFloats(value.as_ref().unwrap().value.vfloat, 1.25, 2));
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 6);
    assert_eq!(value.as_ref().unwrap().type_, 0x82);
    assert!((value.as_ref().unwrap().value.vdouble - 25.987654321).abs() < 0.00000001);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 7);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 1);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 8);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 0);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 9);
    assert_eq!(value.as_ref().unwrap().type_, 0x00);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 10);
    assert_eq!(value.as_ref().unwrap().type_, 0xA0);
    let c_str = unsafe { CStr::from_ptr(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const c_char) };
    assert_eq!(c_str.to_str().unwrap(), "testing...");
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 11);
    assert_eq!(value.as_ref().unwrap().type_, 0xC0);
    let v = unsafe { std::ptr::read(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8) };
    let b = unsafe { std::ptr::read(blob_ptr as *const u8) };
    assert_eq!(v, b);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 1);
    assert_eq!(iter.current, 12);
    assert_eq!(value.as_ref().unwrap().type_, 0xE0);
    assert_eq!(value.as_ref().unwrap().size, list2size);
    assert_eq!(value.as_ref().unwrap().count, 4);
    assert!(value.as_ref().unwrap().ptr.is_some());
    let list_ptr = value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8;
    assert_eq!(binn_list_int32(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 1), 250);
    assert_eq!(binn_list_null(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 2), 1);
    let s_ptr = binn_list_str(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 3);
    assert!(s_ptr.is_some());
    let c_str2 = unsafe { CStr::from_ptr(s_ptr.unwrap().as_ptr() as *const c_char) };
    assert_eq!(c_str2.to_str().unwrap(), "l1st2");
    assert_eq!(binn_list_bool(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 4), 1);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 0);
    assert_eq!(binn_list_next(Some(&mut iter), Some(&mut value)), 0);
    
    ptr = binn_ptr(obj.as_ref().map(|b| b.as_ref() as *const _ as *mut u8));
    assert!(ptr.is_some());
    assert!(binn_iter_init(Some(&mut iter), ptr.map(|p| unsafe { std::slice::from_raw_parts(p, 0) }), 0xE2));
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 0);
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 1);
    assert_eq!(value.as_ref().unwrap().type_, 0x21);
    assert_eq!(value.as_ref().unwrap().value.vint8, 111);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "a");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 2);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x60);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x61);
    }
    assert_eq!(value.as_ref().unwrap().value.vint32, 123456789);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "b");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 3);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x21);
        assert_eq!(value.as_ref().unwrap().value.vint8, -123);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x41);
        assert_eq!(value.as_ref().unwrap().value.vint16, -123);
    }
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "c");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 4);
    assert_eq!(value.as_ref().unwrap().type_, 0x81);
    assert_eq!(value.as_ref().unwrap().value.vint64, 9876543210);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "d");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 5);
    assert_eq!(value.as_ref().unwrap().type_, 0x62);
    assert!(AlmostEqualFloats(value.as_ref().unwrap().value.vfloat, 1.25, 2));
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "e");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 6);
    assert_eq!(value.as_ref().unwrap().type_, 0x82);
    assert!((value.as_ref().unwrap().value.vdouble - 25.987654321).abs() < 0.00000001);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "f");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 7);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 1);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "g");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 8);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 0);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "h");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 9);
    assert_eq!(value.as_ref().unwrap().type_, 0x00);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "i");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 10);
    assert_eq!(value.as_ref().unwrap().type_, 0xA0);
    let c_str = unsafe { CStr::from_ptr(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const c_char) };
    assert_eq!(c_str.to_str().unwrap(), "testing...");
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "j");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 11);
    assert_eq!(value.as_ref().unwrap().type_, 0xC0);
    let v = unsafe { std::ptr::read(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8) };
    let b = unsafe { std::ptr::read(blob_ptr as *const u8) };
    assert_eq!(v, b);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "k");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 1);
    assert_eq!(iter.current, 12);
    assert_eq!(value.as_ref().unwrap().type_, 0xE0);
    assert_eq!(value.as_ref().unwrap().size, list2size);
    assert_eq!(value.as_ref().unwrap().count, 4);
    assert!(value.as_ref().unwrap().ptr.is_some());
    let list_ptr = value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8;
    assert_eq!(binn_list_int32(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 1), 250);
    assert_eq!(binn_list_null(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 2), 1);
    let s_ptr = binn_list_str(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 3);
    assert!(s_ptr.is_some());
    let c_str2 = unsafe { CStr::from_ptr(s_ptr.unwrap().as_ptr() as *const c_char) };
    assert_eq!(c_str2.to_str().unwrap(), "l1st2");
    assert_eq!(binn_list_bool(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 4), 1);
    let key_str = unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) };
    assert_eq!(key_str.to_str().unwrap(), "l");
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 0);
    assert_eq!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value)), 0);
    
    ptr = binn_ptr(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8));
    assert!(ptr.is_some());
    assert!(binn_iter_init(Some(&mut iter), ptr.map(|p| unsafe { std::slice::from_raw_parts(p, 0) }), 0xE1));
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 0);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert_eq!(iter.count, 12);
    assert_eq!(iter.current, 1);
    assert_eq!(value.as_ref().unwrap().type_, 0x21);
    assert_eq!(value.as_ref().unwrap().value.vint8, 111);
    assert_eq!(id, 55010);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 2);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x60);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x61);
    }
    assert_eq!(value.as_ref().unwrap().value.vint32, 123456789);
    assert_eq!(id, 55020);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 3);
    if use_int_compression != 0 {
        assert_eq!(value.as_ref().unwrap().type_, 0x21);
        assert_eq!(value.as_ref().unwrap().value.vint8, -123);
    } else {
        assert_eq!(value.as_ref().unwrap().type_, 0x41);
        assert_eq!(value.as_ref().unwrap().value.vint16, -123);
    }
    assert_eq!(id, 55030);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 4);
    assert_eq!(value.as_ref().unwrap().type_, 0x81);
    assert_eq!(value.as_ref().unwrap().value.vint64, 9876543210);
    assert_eq!(id, 55040);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 5);
    assert_eq!(value.as_ref().unwrap().type_, 0x62);
    assert!(AlmostEqualFloats(value.as_ref().unwrap().value.vfloat, 1.25, 2));
    assert_eq!(id, 55050);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 6);
    assert_eq!(value.as_ref().unwrap().type_, 0x82);
    assert!((value.as_ref().unwrap().value.vdouble - 25.987654321).abs() < 0.00000001);
    assert_eq!(id, 55060);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 7);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 1);
    assert_eq!(id, 55070);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 8);
    assert_eq!(value.as_ref().unwrap().type_, 0x80061);
    assert_eq!(value.as_ref().unwrap().value.vbool, 0);
    assert_eq!(id, 55080);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 9);
    assert_eq!(value.as_ref().unwrap().type_, 0x00);
    assert_eq!(id, 55090);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 10);
    assert_eq!(value.as_ref().unwrap().type_, 0xA0);
    let c_str = unsafe { CStr::from_ptr(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const c_char) };
    assert_eq!(c_str.to_str().unwrap(), "testing...");
    assert_eq!(id, 55100);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 11);
    assert_eq!(value.as_ref().unwrap().type_, 0xC0);
    let v = unsafe { std::ptr::read(value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8) };
    let b = unsafe { std::ptr::read(blob_ptr as *const u8) };
    assert_eq!(v, b);
    assert_eq!(id, 55110);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 1);
    assert_eq!(iter.current, 12);
    assert_eq!(value.as_ref().unwrap().type_, 0xE0);
    assert_eq!(value.as_ref().unwrap().size, list2size);
    assert_eq!(value.as_ref().unwrap().count, 4);
    assert!(value.as_ref().unwrap().ptr.is_some());
    let list_ptr = value.as_ref().unwrap().ptr.as_ref().unwrap().as_ref() as *const () as *const u8;
    assert_eq!(binn_list_int32(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 1), 250);
    assert_eq!(binn_list_null(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 2), 1);
    let s_ptr = binn_list_str(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 3);
    assert!(s_ptr.is_some());
    let c_str2 = unsafe { CStr::from_ptr(s_ptr.unwrap().as_ptr() as *const c_char) };
    assert_eq!(c_str2.to_str().unwrap(), "l1st2");
    assert_eq!(binn_list_bool(Some(unsafe { std::slice::from_raw_parts(list_ptr, 0) }), 4), 1);
    assert_eq!(id, 55120);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 0);
    assert_eq!(binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)), 0);
    
    copy = binn_copy(Some(&mut list));
    assert!(copy.is_some());
    assert_eq!(binn_type(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_type(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_count(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_count(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_size(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_size(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert!(binn_iter_init(Some(&mut iter), list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b.as_ref() as *const _ as *const u8, 0) }), 0xE0));
    assert!(binn_iter_init(Some(&mut iter2), copy.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b.as_ref() as *const _ as *const u8, 0) }), 0xE0));
    while binn_list_next(Some(&mut iter), Some(&mut value)) != 0 {
        assert_eq!(binn_list_next(Some(&mut iter2), Some(&mut value2)), 1);
        assert_eq!(value.as_ref().unwrap().type_, value2.as_ref().unwrap().type_);
    }
    
    let mut s4: Option<Box<dyn std::any::Any>> = Some(Box::new("testing..."));
    assert_eq!(binn_list_add_str(&mut copy, Some(&mut s4)), 1);
    assert_eq!(binn_type(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_type(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_count(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_count(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)) + 1);
    assert!(binn_size(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)) > binn_size(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    binn_free(&mut copy);
    
    copy = binn_copy(Some(&mut map));
    assert!(copy.is_some());
    assert_eq!(binn_type(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_type(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_count(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_count(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_size(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_size(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert!(binn_iter_init(Some(&mut iter), map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b.as_ref() as *const _ as *const u8, 0) }), 0xE1));
    assert!(binn_iter_init(Some(&mut iter2), copy.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b.as_ref() as *const _ as *const u8, 0) }), 0xE1));
    while binn_map_next(Some(&mut iter), Some(&mut id), Some(&mut value)) != 0 {
        assert_eq!(binn_map_next(Some(&mut iter2), Some(&mut id2), Some(&mut value2)), 1);
        assert_eq!(id, id2);
        assert_eq!(value.as_ref().unwrap().type_, value2.as_ref().unwrap().type_);
    }
    
    assert_eq!(binn_map_set_int32(&mut copy, 5600, 123), 1);
    assert_eq!(binn_type(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_type(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    assert_eq!(binn_count(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), binn_count(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)) + 1);
    assert!(binn_size(copy.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)) > binn_size(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)));
    binn_free(&mut copy);
}
pub fn test_binn_int_conversion() {
    let mut obj: Option<Box<BinnStruct>> = None;
    let ptr: Option<*mut u8>;
    
    println!("testing binn integer read conversion... ");
    
    obj = binn_object();
    assert!(obj.is_some());
    
    assert_eq!(binn_object_set_int8(&mut obj, Some("int8"), -8), 1);
    assert_eq!(binn_object_set_int16(&mut obj, Some("int16"), -16), 1);
    assert_eq!(binn_object_set_int32(&mut obj, Some("int32"), -32), 1);
    assert_eq!(binn_object_set_int64(&mut obj, Some("int64"), -64), 1);
    assert_eq!(binn_object_set_uint8(&mut obj, Some("uint8"), 111), 1);
    assert_eq!(binn_object_set_uint16(&mut obj, Some("uint16"), 112), 1);
    assert_eq!(binn_object_set_uint32(&mut obj, Some("uint32"), 113), 1);
    assert_eq!(binn_object_set_uint64(&mut obj, Some("uint64"), 114), 1);
    
    ptr = binn_ptr(obj.as_ref().map(|b| Box::as_ref(b) as *const _ as *mut u8));
    
    let ptr_slice = unsafe {
        std::slice::from_raw_parts(ptr.unwrap() as *const u8, 0)
    };
    
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("int8")), Some(-8));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("int16")), Some(-16));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("int32")), Some(-32));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("int64")), Some(-64));
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("int8")), -8);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("int16")), -16);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("int32")), -32);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("int64")), -64);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("int8")), -8);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("int16")), -16);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("int32")), -32);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("int64")), -64);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("int8")), -8);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("int16")), -16);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("int32")), -32);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("int64")), -64);
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("uint8")), Some(111));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("uint16")), Some(112));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("uint32")), Some(113));
    assert_eq!(binn_object_int8(Some(ptr_slice), Some("uint64")), Some(114));
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("uint8")), 111);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("uint16")), 112);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("uint32")), 113);
    assert_eq!(binn_object_int16(Some(ptr_slice), Some("uint64")), 114);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("uint8")), 111);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("uint16")), 112);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("uint32")), 113);
    assert_eq!(binn_object_int32(Some(ptr_slice), Some("uint64")), 114);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("uint8")), 111);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("uint16")), 112);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("uint32")), 113);
    assert_eq!(binn_object_int64(Some(ptr_slice), Some("uint64")), 114);
    
    binn_free(&mut obj);
    println!("OK");
}
pub fn init_udts() {
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut date: u16;
    let mut value: i64;
    let mut ptr: Option<*mut u8>;
    
    println!("testing UDTs...");
    
    assert!(strcmp(Some(date_to_str(str_to_date(Some("1950-08-15")).unwrap()).as_str()), Some("1950-08-15")) == Some(0));
    assert!(strcmp(Some(date_to_str(str_to_date(Some("1900-12-01")).unwrap()).as_str()), Some("1900-12-01")) == Some(0));
    assert!(strcmp(Some(date_to_str(str_to_date(Some("2000-10-31")).unwrap()).as_str()), Some("2000-10-31")) == Some(0));
    assert!(strcmp(Some(date_to_str(str_to_date(Some("2014-03-19")).unwrap()).as_str()), Some("2014-03-19")) == Some(0));
    
    println!("curr={}", currency_to_str(str_to_currency(Some("123.456")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.45")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.4")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("1.2")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.987")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.98")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.9")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.0")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.4567")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.45678")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.456789")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.1234")).unwrap()).unwrap_or_default());
    println!("curr={}", currency_to_str(str_to_currency(Some(".1234")).unwrap()).unwrap_or_default());
    
    assert!(float_to_currency(2.5).unwrap() == 25000);
    assert!(float_to_currency(5.0).unwrap() == 50000);
    assert!(str_to_currency(Some("1.1")).unwrap() == 11000);
    assert!(str_to_currency(Some("12")).unwrap() == 120000);
    assert!(mul_currency(20000, 20000) == 40000);
    assert!(mul_currency(20000, 25000) == 50000);
    assert!(mul_currency(30000, 40000) == 120000);
    assert!(div_currency(80000, 20000) == 40000);
    assert!(div_currency(120000, 40000) == 30000);
    assert!(div_currency(100000, 40000) == 25000);
    
    println!("1.1 * 2.5 = {}", currency_to_str(mul_currency(str_to_currency(Some("1.1")).unwrap(), float_to_currency(2.5).unwrap())).unwrap_or_default());
    println!("12 / 5 = {}", currency_to_str(div_currency(str_to_currency(Some("12")).unwrap(), float_to_currency(5.0).unwrap())).unwrap_or_default());
    
    MY_DATE.store(binn_create_type(0x40, 0x0a), Ordering::SeqCst);
    MY_CURRENCY.store(binn_create_type(0x80, 0x0a), Ordering::SeqCst);
    
    obj = binn_object();
    assert!(obj.is_some());
    
    date = str_to_date(Some("1950-08-15")).unwrap();
    println!(" date 1: {} {}", date, date_to_str(date));
    let mut date_box1 = Some(Box::new(date) as Box<dyn Any>);
    assert!(binn_object_set(&mut obj, Some("date1"), MY_DATE.load(Ordering::SeqCst), Some(&mut date_box1), 0) == 1);
    let mut date_box2 = Some(Box::new(date) as Box<dyn Any>);
    assert!(binn_object_set(&mut obj, Some("date1"), MY_DATE.load(Ordering::SeqCst), Some(&mut date_box2), 0) == 0);
    
    date = str_to_date(Some("1999-12-31")).unwrap();
    println!(" date 2: {} {}", date, date_to_str(date));
    let mut date_box3 = Some(Box::new(date) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("date2"), MY_DATE.load(Ordering::SeqCst), Some(&mut date_box3), 0);
    
    value = str_to_currency(Some("123.456")).unwrap();
    println!(" curr 1: {} {}", value, currency_to_str(value).unwrap_or_default());
    let mut value_box1 = Some(Box::new(value) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("curr1"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut value_box1), 0);
    
    value = str_to_currency(Some("123.45")).unwrap();
    println!(" curr 2: {} {}", value, currency_to_str(value).unwrap_or_default());
    let mut value_box2 = Some(Box::new(value) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("curr2"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut value_box2), 0);
    
    value = str_to_currency(Some("12.5")).unwrap();
    println!(" curr 3: {} {}", value, currency_to_str(value).unwrap_or_default());
    let mut value_box3 = Some(Box::new(value) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("curr3"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut value_box3), 0);
    
    value = str_to_currency(Some("5")).unwrap();
    println!(" curr 4: {} {}", value, currency_to_str(value).unwrap_or_default());
    let mut value_box4 = Some(Box::new(value) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("curr4"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut value_box4), 0);
    
    value = str_to_currency(Some("0.75")).unwrap();
    println!(" curr 5: {} {}", value, currency_to_str(value).unwrap_or_default());
    let mut value_box5 = Some(Box::new(value) as Box<dyn Any>);
    binn_object_set(&mut obj, Some("curr5"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut value_box5), 0);
    
    ptr = binn_ptr(obj.as_mut().map(|b| b.as_mut() as *mut _ as *mut u8));
    let mut temp_date: u16 = 0;
    let mut temp_value: i64 = 0;
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("date1"), MY_DATE.load(Ordering::SeqCst), Some(&mut temp_date as &mut dyn Any), None) == 1);
    println!(" date 1: {} {}", temp_date, date_to_str(temp_date));
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("date2"), MY_DATE.load(Ordering::SeqCst), Some(&mut temp_date as &mut dyn Any), None) == 1);
    println!(" date 2: {} {}", temp_date, date_to_str(temp_date));
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("curr1"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut temp_value as &mut dyn Any), None) == 1);
    println!(" curr 1: {} {}", temp_value, currency_to_str(temp_value).unwrap_or_default());
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("curr2"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut temp_value as &mut dyn Any), None) == 1);
    println!(" curr 2: {} {}", temp_value, currency_to_str(temp_value).unwrap_or_default());
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("curr3"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut temp_value as &mut dyn Any), None) == 1);
    println!(" curr 3: {} {}", temp_value, currency_to_str(temp_value).unwrap_or_default());
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("curr4"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut temp_value as &mut dyn Any), None) == 1);
    println!(" curr 4: {} {}", temp_value, currency_to_str(temp_value).unwrap_or_default());
    
    assert!(binn_object_get(ptr.and_then(|p| Some(unsafe { std::slice::from_raw_parts(p, 0) })), Some("curr5"), MY_CURRENCY.load(Ordering::SeqCst), Some(&mut temp_value as &mut dyn Any), None) == 1);
    println!(" curr 5: {} {}", temp_value, currency_to_str(temp_value).unwrap_or_default());
    
    binn_free(&mut obj);
    println!("testing UDTs... OK");
}

fn strcmp(s1: Option<&str>, s2: Option<&str>) -> Option<i32> {
    match (s1, s2) {
        (Some(s1), Some(s2)) => Some(s1.cmp(s2) as i32),
        _ => None,
    }
}

pub fn test_binn2() {
    let mut obj1size: i32 = 0;
    let mut obj2size: i32 = 0;
    
    test_virtual_types();
    test_int_conversion();
    test_binn_int_conversion();
    test_value_conversion();
    test_value_copy();
    init_udts();
    
    let obj1ptr_opt = test_create_object_1(&mut obj1size);
    let obj2ptr = unsafe { test_create_object_2(&mut obj2size) };
    
    // Handle the Option return from test_create_object_1
    let obj1ptr = obj1ptr_opt.expect("test_create_object_1 returned None");
    assert!(!obj1ptr.is_null());
    assert!(obj2ptr.is_some());  // Check that obj2ptr is Some variant
    
    println!("obj1size={} obj2size={}", obj1size, obj2size);
    assert_eq!(obj1size, obj2size);
    
    let obj1slice = unsafe { std::slice::from_raw_parts(obj1ptr as *const u8, obj1size as usize) };
    test_binn_read(Some(obj1slice));
    test_binn_iter(0);
    test_binn_iter(1);
}
