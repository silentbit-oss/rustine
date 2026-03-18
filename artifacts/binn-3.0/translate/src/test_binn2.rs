use crate::*;
use lazy_static::lazy_static;
use libc::free;
use libc::strdup;
use std::any::Any;
use std::ffi::CStr;
use std::ffi::CString;
use std::ffi::c_void;
use std::mem;
use std::os::raw::c_char;
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
pub fn stripchr(mainstr: Option<&mut [u8]>, separator: u8) -> Option<&mut [u8]> {
    // Check for NULL equivalent (None)
    let mainstr = mainstr?;

    // Find the position of the separator (equivalent to strchr)
    let pos = mainstr.iter().position(|&c| c == separator)?;

    // Split the slice at the separator position
    let (left, right) = mainstr.split_at_mut(pos);
    
    // Null-terminate at the separator position (if needed)
    if !right.is_empty() {
        right[0] = b'\0';
    }

    // Return the left part (up to but not including the separator)
    Some(left)
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
    // Convert Option<&str> to Option<&CStr> for safer handling
    let str_cstr = str.and_then(|s| CStr::from_bytes_with_nul(s.as_bytes()).ok());
    if str_cstr.is_none() {
        return None;
    }
    let str_cstr = str_cstr.unwrap();

    // Check if string is empty (equivalent to line 8-11)
    if str_cstr.to_bytes().is_empty() {
        return Some(0);
    }

    // Copy string to TMP (equivalent to line 12-13)
    let mut tmp_guard = TMP.lock().unwrap();
    let tmp_slice = &mut tmp_guard[..];
    let str_bytes = str_cstr.to_bytes_with_nul();
    if str_bytes.len() > tmp_slice.len() {
        return None; // Buffer would overflow
    }
    tmp_slice[..str_bytes.len()].copy_from_slice(str_bytes);

    // Find decimal point (equivalent to line 14)
    let next_pos = tmp_slice.iter().position(|&c| c == b'.');

    if let Some(next_idx) = next_pos {
        // Handle case with decimal point (lines 15-31)
        let decimal_part_start = next_idx + 1;
        let decimal_part_len = tmp_slice[decimal_part_start..]
            .iter()
            .position(|&c| c == 0)
            .unwrap_or(tmp_slice.len() - decimal_part_start);

        // Store length before mutable operations
        let slice_len = tmp_slice.len();

        // Use split_at_mut to avoid overlapping borrows
        let (left, right) = tmp_slice.split_at_mut(decimal_part_start);
        let decimal_part = &right[..decimal_part_len];
        
        // Move decimal digits left (equivalent to memmove in line 18)
        if next_idx + decimal_part_len < slice_len {
            left[next_idx..next_idx + decimal_part_len].copy_from_slice(decimal_part);
            left[next_idx + decimal_part_len] = 0;
        }

        // Pad with zeros if needed (lines 19-26)
        if decimal_part_len < 4 {
            let zeros_needed = 4 - decimal_part_len;
            let end_pos = next_idx + decimal_part_len;
            if end_pos + zeros_needed < slice_len {
                tmp_slice[end_pos..end_pos + zeros_needed].fill(b'0');
                tmp_slice[end_pos + zeros_needed] = 0;
            }
        } else {
            // Truncate to 4 decimal places (line 30)
            let truncate_pos = next_idx + 4;
            if truncate_pos < slice_len {
                tmp_slice[truncate_pos] = 0;
            }
        }
    } else {
        // No decimal point - append "0000" (line 35)
        let len = tmp_slice.iter().position(|&c| c == 0).unwrap_or(tmp_slice.len());
        if len + 4 < tmp_slice.len() {
            tmp_slice[len..len + 4].copy_from_slice(b"0000");
            tmp_slice[len + 4] = 0;
        }
    }

    // Convert to string and parse (line 37)
    let result_str = unsafe { CStr::from_ptr(tmp_slice.as_ptr() as *const i8) };
    atoi64(result_str.to_str().ok())
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
    // Check for None (equivalent to NULL check in C)
    let datestr = datestr?;

    // Convert the string to bytes for processing
    let datestr_bytes = datestr.as_bytes();
    
    // Use TMP for temporary storage (equivalent to strcpy in C)
    let mut tmp = TMP.lock().unwrap();
    if datestr_bytes.len() >= tmp.len() {
        return Option::None; // Buffer would overflow
    }
    tmp[..datestr_bytes.len()].copy_from_slice(datestr_bytes);
    tmp[datestr_bytes.len()] = 0; // Null-terminate

    // Parse the date components
    let mut parts = datestr.split('-');
    
    let year = parts.next()
        .and_then(|s| s.parse::<i32>().ok())
        .map(|y| y - 1900)
        .unwrap_or(0);
    
    let month = parts.next()
        .and_then(|s| s.parse::<i32>().ok())
        .unwrap_or(0);
    
    let day = parts.next()
        .and_then(|s| s.parse::<i32>().ok())
        .unwrap_or(0);

    // Combine into date format (day << 11 | month << 7 | year)
    let date = ((day << 11) | (month << 7) | year) as u16;
    Some(date)
}


pub fn currency_to_str(value: int64) -> Option<String> {
    // Convert the int64 to a string representation
    let mut tmp = TMP.lock().unwrap();
    let str_slice = i64toa(value, &mut *tmp, 10)?;
    let mut str_bytes = str_slice.to_vec();

    let size = str_bytes.len();
    
    if size > 4 {
        // Handle case where we need to insert a decimal point 4 digits from the end
        let split_pos = size - 4;
        let mut new_str = Vec::with_capacity(size + 1);
        
        // Add part before decimal
        new_str.extend_from_slice(&str_bytes[..split_pos]);
        new_str.push(b'.');
        // Add part after decimal
        new_str.extend_from_slice(&str_bytes[split_pos..]);
        
        str_bytes = new_str;
    } else {
        // Handle case where we need to pad with zeros and add "0."
        let mut new_str = Vec::with_capacity(6); // "0.0000" + null terminator
        
        new_str.push(b'0');
        new_str.push(b'.');
        
        // Add leading zeros
        for _ in 0..(4 - size) {
            new_str.push(b'0');
        }
        
        // Add the actual number
        new_str.extend_from_slice(&str_bytes);
        
        str_bytes = new_str;
    }

    // Convert to String, checking for UTF-8 validity
    String::from_utf8(str_bytes).ok()
}

pub fn currency_to_float(value: int64) -> Option<f64> {
    // Call currency_to_str to get the string representation
    let currency_str = currency_to_str(value)?;
    
    // Parse the string into f64, returning None if parsing fails
    f64::from_str(&currency_str).ok()
}

pub fn test_virtual_types() {
    let mut list: Option<Box<BinnStruct>> = None;
    let mut list_idx = 0;
    let mut ptr: Option<&[u8]> = None;
    let mut ptr_idx = 0;
    let mut storage_type = 0;
    let mut extra_type = 0;
    let mut value: BOOL = 0;

    println!("testing binn virtual types... ");

    assert!(binn_get_type_info(0x80061, Some(&mut storage_type), Some(&mut extra_type)) == 1);
    assert!(storage_type == 0x60);
    assert!(extra_type == 1);

    list = binn_list();
    list_idx = 0; // In Rust, we don't need to track indices the same way
    assert!(list.is_some());

    assert!(binn_list_add_bool(&mut list, 1) == 1);
    assert!(binn_list_add_bool(&mut list, 0) == 1);
    assert!(binn_list_add_null(&mut list) == 1);

    // In Rust, we can't directly get a pointer like in C, so we simulate it
    // by converting the list to a byte slice if possible
    if let Some(ref list_box) = list {
        ptr = Some(unsafe {
            std::slice::from_raw_parts(
                list_box.ptr.as_ref().unwrap().as_ref() as *const _ as *const u8,
                list_box.size as usize,
            )
        });
    }
    ptr_idx = 0;
    assert!(ptr.is_some());

    assert!(binn_list_get_bool(ptr, 1, Some(&mut value)) == 1);
    assert!(value == 1);
    assert!(binn_list_get_bool(ptr, 2, Some(&mut value)) == 1);
    assert!(value == 0);
    assert!(binn_list_null(ptr, 3) == 1);
    assert!(binn_list_null(ptr, 1) == 0);
    assert!(binn_list_null(ptr, 2) == 0);
    assert!(binn_list_get_bool(ptr, 3, Some(&mut value)) == 0);

    binn_free(&mut list);
    println!("OK");
}
pub fn test_value_conversion() {
    let mut value: Option<Box<BinnStruct>>;
    let mut value_idx = 0;
    let mut ptr: *const c_char;
    let mut ptr_idx = 0;
    let blob = b"test blob\0";
    let mut pblob: *mut u8;
    let mut pblob_idx = 0;
    let mut size: i32;
    let mut vint32: i32 = 0;
    let mut vdouble: f64 = 0.0;
    unsafe {
        vint64 = 0;
        vbool = 0;
    }

    println!("testing binn value conversion... ");

    // Static string test
    ptr_idx = "static string".as_ptr() as usize;
    ptr = "static string".as_ptr() as *const c_char;
    value = binn_string(Some("static string"), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0xA0);
    assert!(value_ref.ptr.is_some());
    assert_eq!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as usize, ptr_idx);
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);

    // Transient string test
    ptr_idx = "transient string".as_ptr() as usize;
    ptr = "transient string".as_ptr() as *const c_char;
    value = binn_string(Some("transient string"), Some(Box::new(|_| {})));
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0xA0);
    assert!(value_ref.ptr.is_some());
    assert_ne!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as usize, ptr_idx);
    let value_str = unsafe { CStr::from_ptr(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as *const c_char) };
    assert_eq!(value_str.to_str().unwrap(), "transient string");
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);

    // Dynamic allocated string test
    let dyn_str = unsafe { libc::strdup(b"dynamic allocated string\0".as_ptr() as *const c_char) };
    ptr_idx = dyn_str as usize;
    ptr = dyn_str;
    value = binn_string(
        Some(unsafe { CStr::from_ptr(dyn_str).to_str().unwrap() }),
        Some(Box::new(|p| unsafe { libc::free(p.unwrap().as_ref() as *const _ as *mut c_void) })),
    );
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0xA0);
    assert!(value_ref.ptr.is_some());
    assert_eq!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as usize, ptr_idx);
    assert!(value_ref.freefn.is_some());
    binn_free(&mut value);

    // Blob tests (similar pattern as strings)
    size = 64;
    pblob_idx = blob.as_ptr() as usize;
    pblob = blob.as_ptr() as *mut u8;
    value = binn_blob(Some(blob), size, None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0xC0);
    assert!(value_ref.ptr.is_some());
    assert_eq!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as usize, pblob_idx);
    assert!(value_ref.freefn.is_none());
    binn_free(&mut value);

    // Numeric conversion tests
    ptr_idx = "123".as_ptr() as usize;
    ptr = "123".as_ptr() as *const c_char;
    value = binn_string(Some("123"), None);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0xA0);
    assert!(value_ref.ptr.is_some());
    assert_eq!(value_ref.ptr.as_ref().unwrap().as_ref() as *const _ as usize, ptr_idx);
    assert!(value_ref.freefn.is_none());
    unsafe {
        assert_eq!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)), 1);
        assert_eq!(vint32, 123);
    }
    assert_eq!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)), true);
    assert!(AlmostEqualFloats(vdouble as f32, 123.0, 4));
    unsafe {
        assert_eq!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool)), 1);
        assert_eq!(vbool, 1);
    }
    let str_val = binn_get_str(value).unwrap();
    value = None;
    assert_eq!(str_val.to_str().unwrap(), "123");

    // Direct numeric value tests
    value = binn_int32(-345);
    assert!(value.is_some());
    let value_ref = value.as_ref().unwrap();
    assert_eq!(value_ref.type_, 0x61);
    assert_eq!(value_ref.value.vint32, -345);
    assert!(value_ref.freefn.is_none());
    unsafe {
        assert_eq!(binn_get_int32(value.as_ref().map(|v| &**v), Some(&mut vint32)), 1);
        assert_eq!(vint32, -345);
    }
    assert_eq!(binn_get_double(value.as_ref().map(|v| &**v), Some(&mut vdouble)), true);
    assert!(AlmostEqualFloats(vdouble as f32, -345.0, 4));
    unsafe {
        assert_eq!(binn_get_bool(value.as_ref().map(|v| &**v), Some(&mut vbool)), 1);
        assert_eq!(vbool, 1);
    }
    let str_val = binn_get_str(value).unwrap();
    value = None;
    assert_eq!(str_val.to_str().unwrap(), "-345");

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
pub fn test_create_object_1(psize: &mut i32) -> Option<*mut u8> {
    println!("creating object 1...");

    let mut obj = binn_object();
    assert!(obj.is_some());

    // Set various values in the object
    VINT32.store(-12345, Ordering::SeqCst);
    assert!(binn_object_set(&mut obj, Some("int32"), 0x61, None, 0) == 1);

    unsafe {
        obj.as_mut().unwrap().value.vint16 = -258;
        assert!(binn_object_set(&mut obj, Some("int16"), 0x41, None, 0) == 1);

        VINT8 = -120;
        assert!(binn_object_set(&mut obj, Some("int8"), 0x21, None, 0) == 1);

        vint64 = -1234567890123;
        assert!(binn_object_set(&mut obj, Some("int64"), 0x81, None, 0) == 1);

        obj.as_mut().unwrap().value.vuint32 = 123456;
        assert!(binn_object_set(&mut obj, Some("uint32"), 0x60, None, 0) == 1);

        obj.as_mut().unwrap().value.vuint16 = 60500;
        assert!(binn_object_set(&mut obj, Some("uint16"), 0x40, None, 0) == 1);

        obj.as_mut().unwrap().value.vuint8 = 250;
        assert!(binn_object_set(&mut obj, Some("uint8"), 0x20, None, 0) == 1);

        obj.as_mut().unwrap().value.vuint64 = 1234567890123;
        assert!(binn_object_set(&mut obj, Some("uint64"), 0x80, None, 0) == 1);

        vfloat32 = -12.345;
        assert!(binn_object_set(&mut obj, Some("float32"), 0x62, None, 0) == 1);

        vfloat32 = -12.345;
        assert!(binn_object_set(&mut obj, Some("single"), 0x62, None, 0) == 1);

        vfloat64 = -123456.7895;
        assert!(binn_object_set(&mut obj, Some("float64"), 0x82, None, 0) == 1);

        vfloat64 = -123456.7895;
        assert!(binn_object_set(&mut obj, Some("double"), 0x82, None, 0) == 1);
    }

    assert!(binn_object_set(&mut obj, Some("str"), 0xA0, None, 0) == 1);

    VINT32.store(1, Ordering::SeqCst);
    assert!(binn_object_set(&mut obj, Some("bool_true"), 0x80061, None, 0) == 1);

    VINT32.store(0, Ordering::SeqCst);
    assert!(binn_object_set(&mut obj, Some("bool_false"), 0x80061, None, 0) == 1);

    assert!(binn_object_set(&mut obj, Some("null"), 0x00, None, 0) == 1);

    let mut list = binn_list();
    assert!(list.is_some());

    assert!(binn_list_add(&mut list, 0x00, None, 0) == 1);

    VINT32.store(123, Ordering::SeqCst);
    assert!(binn_list_add(&mut list, 0x61, None, 0) == 1);

    assert!(binn_list_add(&mut list, 0xA0, None, 0) == 1);

    assert!(binn_object_set(&mut obj, Some("list"), 0xE0, None, 0) == 1);

    binn_free(&mut list);

    *psize = binn_size(obj.as_ref().map(|x| x.as_ref() as *const _ as *mut u8));
    binn_ptr(obj.map(|x| Box::into_raw(x) as *mut u8))
}
pub fn test_binn_read(objptr: Option<&[u8]>) {
    let mut listptr: Option<&[u8]> = None;
    let mut listptr_idx = 0;
    let mut ptr: Option<String> = None;
    let mut ptr_idx = 0;
    let mut value: Option<Box<BinnStruct>> = None;
    
    println!("OK\nreading:");

    // int32
    {
        let mut vint32 = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_get(objptr, Some("int32"), 0x61, Some(&mut vint32 as &mut dyn Any), None) == 1);
        VINT32.store(vint32, Ordering::SeqCst);
        println!("int32: {}", vint32);
        assert!(vint32 == -12345);
    }

    // int16
    {
        let mut vint16: i16 = 0;
        assert!(binn_object_get(objptr, Some("int16"), 0x41, Some(&mut vint16 as &mut dyn Any), None) == 1);
        println!("int16: {}", vint16);
        assert!(vint16 == -258);
    }

    // int8
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("int8"), 0x21, Some(&mut VINT8 as &mut dyn Any), None) == 1);
            println!("int8: {}", VINT8);
            assert!(VINT8 == -120);
        }
    }

    // int64
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("int64"), 0x81, Some(&mut vint64 as &mut dyn Any), None) == 1);
            println!("int64: {}", vint64);
            assert!(vint64 == -1234567890123);
        }
    }

    // uint32
    {
        let mut vuint32: u32 = 0;
        assert!(binn_object_get(objptr, Some("uint32"), 0x60, Some(&mut vuint32 as &mut dyn Any), None) == 1);
        println!("uint32: {}", vuint32);
        assert!(vuint32 == 123456);
    }

    // uint16
    {
        let mut vuint16: u16 = 0;
        assert!(binn_object_get(objptr, Some("uint16"), 0x40, Some(&mut vuint16 as &mut dyn Any), None) == 1);
        println!("uint16: {}", vuint16);
        assert!(vuint16 == 60500);
    }

    // uint8
    {
        let mut vuint8: u8 = 0;
        assert!(binn_object_get(objptr, Some("uint8"), 0x20, Some(&mut vuint8 as &mut dyn Any), None) == 1);
        println!("uint8: {}", vuint8);
        assert!(vuint8 == 250);
    }

    // uint64
    {
        let mut vuint64: u64 = 0;
        assert!(binn_object_get(objptr, Some("uint64"), 0x80, Some(&mut vuint64 as &mut dyn Any), None) == 1);
        println!("uint64: {}", vuint64);
        assert!(vuint64 == 1234567890123);
    }

    // float32
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("float32"), 0x62, Some(&mut vfloat32 as &mut dyn Any), None) == 1);
            println!("float32: {}", vfloat32);
            assert!(AlmostEqualFloats(vfloat32, -12.345, 2));
        }
    }

    // float64
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("float64"), 0x82, Some(&mut vfloat64 as &mut dyn Any), None) == 1);
            println!("float64: {}", vfloat64);
            assert!((vfloat64 - (-123456.7895)).abs() < 0.01);
        }
    }

    // single (float32 again)
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("single"), 0x62, Some(&mut vfloat32 as &mut dyn Any), None) == 1);
            println!("single: {}", vfloat32);
            assert!(AlmostEqualFloats(vfloat32, -12.345, 2));
        }
    }

    // double (float64 again)
    {
        unsafe {
            assert!(binn_object_get(objptr, Some("double"), 0x82, Some(&mut vfloat64 as &mut dyn Any), None) == 1);
            println!("double: {}", vfloat64);
            assert!((vfloat64 - (-123456.7895)).abs() < 0.01);
        }
    }

    // str
    {
        ptr_idx = 0;
        let mut temp_ptr: Option<String> = None;
        assert!(binn_object_get(objptr, Some("str"), 0xA0, Some(&mut temp_ptr as &mut dyn Any), None) == 1);
        ptr = temp_ptr;
        println!("ptr: '{:?}'", ptr);
        assert!(ptr.as_deref() == Some("the value"));
    }

    // bool_true
    {
        let mut vint32 = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_get(objptr, Some("bool_true"), 0x80061, Some(&mut vint32 as &mut dyn Any), None) == 1);
        VINT32.store(vint32, Ordering::SeqCst);
        println!("bool true: {}", vint32);
        assert!(vint32 == 1);
    }

    // bool_false
    {
        let mut vint32 = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_get(objptr, Some("bool_false"), 0x80061, Some(&mut vint32 as &mut dyn Any), None) == 1);
        VINT32.store(vint32, Ordering::SeqCst);
        println!("bool false: {}", vint32);
        assert!(vint32 == 0);
    }

    // null
    {
        let mut vint32 = VINT32.load(Ordering::SeqCst);
        assert!(binn_object_get(objptr, Some("null"), 0x00, Some(&mut vint32 as &mut dyn Any), None) == 1);
        VINT32.store(vint32, Ordering::SeqCst);
        println!("null: {}", vint32);
        assert!(binn_object_get(objptr, Some("null"), 0x00, None, None) == 1);
    }

    // list
    {
        let mut temp_listptr: Option<&[u8]> = None;
        assert!(binn_object_get(objptr, Some("list"), 0xE0, Some(&mut temp_listptr as &mut dyn Any), None) == 1);
        listptr = temp_listptr;
        println!("obj ptr: {:?}  list ptr: {:?}", objptr, listptr);
        assert!(listptr.is_some());
    }

    // list operations
    if let Some(list) = listptr {
        // int32 from list
        {
            let mut vint32 = VINT32.load(Ordering::SeqCst);
            assert!(binn_list_get(Some(list), 2, 0x61, Some(&mut vint32 as &mut dyn Any), None) == 1);
            VINT32.store(vint32, Ordering::SeqCst);
            println!("int32: {}", vint32);
            assert!(vint32 == 123);
        }

        // str from list
        {
            ptr_idx = 0;
            let mut temp_ptr: Option<String> = None;
            assert!(binn_list_get(Some(list), 3, 0xA0, Some(&mut temp_ptr as &mut dyn Any), None) == 1);
            ptr = temp_ptr;
            println!("ptr: '{:?}'", ptr);
            assert!(ptr.as_deref() == Some("this is a string"));
        }
    }

    println!("reading... OK");
}
pub fn test_binn_iter(use_int_compression: BOOL) {
    let mut list: Option<Box<BinnStruct>> = binn_list();
    let mut list_idx = 0;
    let mut map: Option<Box<BinnStruct>> = binn_map();
    let mut map_idx = 0;
    let mut obj: Option<Box<BinnStruct>> = binn_object();
    let mut obj_idx = 0;
    let mut list2: Option<Box<BinnStruct>> = binn_list();
    let mut list2_idx = 0;
    let mut copy: Option<Box<BinnStruct>> = None;
    let mut copy_idx = 0;
    let mut iter = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };
    let mut iter2 = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };
    let mut value = BinnValue {
        vint8: 0,
        vint16: 0,
        vint32: 0,
        vint64: 0,
        vuint8: 0,
        vuint16: 0,
        vuint32: 0,
        vuint64: 0,
        vchar: 0,
        vuchar: 0,
        vshort: 0,
        vushort: 0,
        vint: 0,
        vuint: 0,
        vfloat: 0.0,
        vdouble: 0.0,
        vbool: 0,
    };
    let mut value2 = BinnValue {
        vint8: 0,
        vint16: 0,
        vint32: 0,
        vint64: 0,
        vuint8: 0,
        vuint16: 0,
        vuint32: 0,
        vuint64: 0,
        vchar: 0,
        vuchar: 0,
        vshort: 0,
        vushort: 0,
        vint: 0,
        vuint: 0,
        vfloat: 0.0,
        vdouble: 0.0,
        vbool: 0,
    };
    let mut blob_size = 0;
    let mut id = 0;
    let mut id2 = 0;
    let mut list2size = 0;
    let mut ptr: Option<*mut u8> = None;
    let mut ptr_idx = 0;
    let mut blob_ptr: Option<*mut u8> = None;
    let mut blob_ptr_idx = 0;
    let mut key = [0; 256];
    let mut key2 = [0; 256];

    blob_ptr_idx = 0;
    blob_size = 11;
    println!("testing binn sequential read (use_int_compression = {})... ", use_int_compression);

    list_idx = 0;
    list2_idx = 0;
    map_idx = 0;
    obj_idx = 0;
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

    assert!(binn_list_add_int32(&mut list2, 250) == 1);
    assert!(binn_list_add_null(&mut list2) == 1);
    assert!(binn_list_add_str(&mut list2, Some(&mut Some(Box::new("l1st2".to_string())))) == 1);
    assert!(binn_list_add_bool(&mut list2, 1) == 1);
    list2size = binn_size(list2.as_ref().map(|x| x as *const _ as *mut u8));
    assert!(binn_list_add_int8(&mut list, 111) == 1);
    assert!(binn_list_add_int32(&mut list, 123456789) == 1);
    assert!(binn_list_add_int16(&mut list, -123) == 1);
    assert!(binn_list_add_int64(&mut list, 9876543210) == 1);
    assert!(binn_list_add_float(&mut list, 1.25) == 1);
    assert!(binn_list_add_double(&mut list, 25.987654321) == 1);
    assert!(binn_list_add_bool(&mut list, 1) == 1);
    assert!(binn_list_add_bool(&mut list, 0) == 1);
    assert!(binn_list_add_null(&mut list) == 1);
    assert!(binn_list_add_str(&mut list, Some(&mut Some(Box::new("testing...".to_string())))) == 1);
    assert!(binn_list_add_blob(&mut list, None, blob_size) == 1);
    assert!(binn_list_add_list(&mut list, Some(&mut list2)) == 1);
    assert!(binn_object_set_int8(&mut obj, Some("a"), 111) == 1);
    assert!(binn_object_set_int32(&mut obj, Some("b"), 123456789) == 1);
    assert!(binn_object_set_int16(&mut obj, Some("c"), -123) == 1);
    assert!(binn_object_set_int64(&mut obj, Some("d"), 9876543210) == 1);
    assert!(binn_object_set_float(&mut obj, Some("e"), 1.25) == 1);
    assert!(binn_object_set_double(&mut obj, Some("f"), 25.987654321) == 1);
    assert!(binn_object_set_bool(&mut obj, Some("g"), 1) == 1);
    assert!(binn_object_set_bool(&mut obj, Some("h"), 0) == 1);
    assert!(binn_object_set_null(&mut obj, Some("i")) == 1);
    assert!(binn_object_set_str(&mut obj, Some("j"), Some("testing...")) == 1);
    assert!(binn_object_set_blob(&mut obj, Some("k"), None, blob_size) == 1);
    assert!(binn_object_set_list(&mut obj, Some("l"), list2.as_ref().map(|x| x as *const _ as *mut u8)) == 1);
    assert!(binn_map_set_int8(&mut map, 55010, 111) == 1);
    assert!(binn_map_set_int32(&mut map, 55020, 123456789) == 1);
    assert!(binn_map_set_int16(&mut map, 55030, -123) == 1);
    assert!(binn_map_set_int64(&mut map, 55040, 9876543210) == 1);
    assert!(binn_map_set_float(&mut map, 55050, 1.25) == 1);
    assert!(binn_map_set_double(&mut map, 55060, 25.987654321) == 1);
    assert!(binn_map_set_bool(&mut map, 55070, 1) == 1);
    assert!(binn_map_set_bool(&mut map, 55080, 0) == 1);
    assert!(binn_map_set_null(&mut map, 55090) == 1);
    assert!(binn_map_set_str(&mut map, 55100, Some(&mut Some(Box::new("testing...".to_string())))) == 1);
    assert!(binn_map_set_blob(&mut map, 55110, None, blob_size) == 1);
    assert!(binn_map_set_list(&mut map, 55120, list2.as_ref().map(|x| x as *const _ as *mut u8)) == 1);

    ptr_idx = 0;
    ptr = binn_ptr(list.as_ref().map(|x| x as *const _ as *mut u8));
    assert!(ptr.is_some());
    assert!(binn_iter_init(Some(&mut iter), ptr.as_ref().map(|x| unsafe { std::slice::from_raw_parts(*x, 0) }), 0xE0));
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert!(iter.count == 12);
    assert!(iter.current == 0);
    
    let mut value_binn = binn_list();
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert!(iter.count == 12);
    assert!(iter.current == 1);
    assert!(value_binn.as_ref().unwrap().type_ == 0x21);
    assert!(value_binn.as_ref().unwrap().value.vint8 == 111);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 2);
    if use_int_compression != 0 {
        assert!(value_binn.as_ref().unwrap().type_ == 0x60);
    } else {
        assert!(value_binn.as_ref().unwrap().type_ == 0x61);
    }
    assert!(value_binn.as_ref().unwrap().value.vint32 == 123456789);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 3);
    if use_int_compression != 0 {
        assert!(value_binn.as_ref().unwrap().type_ == 0x21);
        assert!(value_binn.as_ref().unwrap().value.vint8 == -123);
    } else {
        assert!(value_binn.as_ref().unwrap().type_ == 0x41);
        assert!(value_binn.as_ref().unwrap().value.vint16 == -123);
    }
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 4);
    assert!(value_binn.as_ref().unwrap().type_ == 0x81);
    assert!(value_binn.as_ref().unwrap().value.vint64 == 9876543210);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 5);
    assert!(value_binn.as_ref().unwrap().type_ == 0x62);
    assert!(AlmostEqualFloats(value_binn.as_ref().unwrap().value.vfloat, 1.25, 2));
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 6);
    assert!(value_binn.as_ref().unwrap().type_ == 0x82);
    assert!((value_binn.as_ref().unwrap().value.vdouble - 25.987654321).abs() < 0.00000001);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 7);
    assert!(value_binn.as_ref().unwrap().type_ == 0x80061);
    assert!(value_binn.as_ref().unwrap().value.vbool == 1);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 8);
    assert!(value_binn.as_ref().unwrap().type_ == 0x80061);
    assert!(value_binn.as_ref().unwrap().value.vbool == 0);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 9);
    assert!(value_binn.as_ref().unwrap().type_ == 0x00);
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 10);
    assert!(value_binn.as_ref().unwrap().type_ == 0xA0);
    assert!(unsafe { CStr::from_ptr(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const c_char).unwrap()) }.to_str().unwrap() == "testing...");
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 11);
    assert!(value_binn.as_ref().unwrap().type_ == 0xC0);
    assert!(unsafe { std::ptr::eq(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), blob_ptr.unwrap()) });
    
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 1);
    assert!(iter.current == 12);
    assert!(value_binn.as_ref().unwrap().type_ == 0xE0);
    assert!(value_binn.as_ref().unwrap().size == list2size);
    assert!(value_binn.as_ref().unwrap().count == 4);
    assert!(value_binn.as_ref().unwrap().ptr.is_some());
    assert!(binn_list_int32(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 1) == 250);
    assert!(binn_list_null(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 2) == 1);
    ptr_idx = 0;
    ptr = binn_list_str(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 3).map(|s| s.as_ptr() as *mut u8);
    assert!(ptr.is_some());
    assert!(unsafe { CStr::from_ptr(ptr.unwrap() as *const c_char) }.to_str().unwrap() == "l1st2");
    assert!(binn_list_bool(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 4) == 1);
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 0);
    assert!(binn_list_next(Some(&mut iter), Some(&mut value_binn)) == 0);

    ptr_idx = 0;
    ptr = binn_ptr(obj.as_ref().map(|x| x as *const _ as *mut u8));
    assert!(ptr.is_some());
    assert!(binn_iter_init(Some(&mut iter), ptr.as_ref().map(|x| unsafe { std::slice::from_raw_parts(*x, 0) }), 0xE2));
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert!(iter.count == 12);
    assert!(iter.current == 0);
    
    let mut value_binn = binn_list();
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.pnext.is_some());
    assert!(iter.plimit.is_some());
    assert!(iter.count == 12);
    assert!(iter.current == 1);
    assert!(value_binn.as_ref().unwrap().type_ == 0x21);
    assert!(value_binn.as_ref().unwrap().value.vint8 == 111);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "a");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 2);
    if use_int_compression != 0 {
        assert!(value_binn.as_ref().unwrap().type_ == 0x60);
    } else {
        assert!(value_binn.as_ref().unwrap().type_ == 0x61);
    }
    assert!(value_binn.as_ref().unwrap().value.vint32 == 123456789);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "b");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 3);
    if use_int_compression != 0 {
        assert!(value_binn.as_ref().unwrap().type_ == 0x21);
        assert!(value_binn.as_ref().unwrap().value.vint8 == -123);
    } else {
        assert!(value_binn.as_ref().unwrap().type_ == 0x41);
        assert!(value_binn.as_ref().unwrap().value.vint16 == -123);
    }
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "c");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 4);
    assert!(value_binn.as_ref().unwrap().type_ == 0x81);
    assert!(value_binn.as_ref().unwrap().value.vint64 == 9876543210);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "d");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 5);
    assert!(value_binn.as_ref().unwrap().type_ == 0x62);
    assert!(AlmostEqualFloats(value_binn.as_ref().unwrap().value.vfloat, 1.25, 2));
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "e");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 6);
    assert!(value_binn.as_ref().unwrap().type_ == 0x82);
    assert!((value_binn.as_ref().unwrap().value.vdouble - 25.987654321).abs() < 0.00000001);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "f");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 7);
    assert!(value_binn.as_ref().unwrap().type_ == 0x80061);
    assert!(value_binn.as_ref().unwrap().value.vbool == 1);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "g");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 8);
    assert!(value_binn.as_ref().unwrap().type_ == 0x80061);
    assert!(value_binn.as_ref().unwrap().value.vbool == 0);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "h");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 9);
    assert!(value_binn.as_ref().unwrap().type_ == 0x00);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "i");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 10);
    assert!(value_binn.as_ref().unwrap().type_ == 0xA0);
    assert!(unsafe { CStr::from_ptr(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const c_char).unwrap()) }.to_str().unwrap() == "testing...");
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "j");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 11);
    assert!(value_binn.as_ref().unwrap().type_ == 0xC0);
    assert!(unsafe { std::ptr::eq(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), blob_ptr.unwrap()) });
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "k");
    
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 1);
    assert!(iter.current == 12);
    assert!(value_binn.as_ref().unwrap().type_ == 0xE0);
    assert!(value_binn.as_ref().unwrap().size == list2size);
    assert!(value_binn.as_ref().unwrap().count == 4);
    assert!(value_binn.as_ref().unwrap().ptr.is_some());
    assert!(binn_list_int32(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 1) == 250);
    assert!(binn_list_null(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 2) == 1);
    ptr_idx = 0;
    ptr = binn_list_str(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 3).map(|s| s.as_ptr() as *mut u8);
    assert!(ptr.is_some());
    assert!(unsafe { CStr::from_ptr(ptr.unwrap() as *const c_char) }.to_str().unwrap() == "l1st2");
    assert!(binn_list_bool(Some(unsafe { std::slice::from_raw_parts(value_binn.as_ref().unwrap().ptr.as_ref().map(|p| p as *const _ as *const u8).unwrap(), 0) }), 4) == 1);
    assert!(unsafe { CStr::from_ptr(key.as_ptr() as *const c_char) }.to_str().unwrap() == "l");
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 0);
    assert!(binn_object_next(Some(&mut iter), Some(&mut key), Some(&mut value_binn)) == 0);
    println!("OK");
}
pub fn test_binn_int_conversion() {
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut ptr: Option<&[u8]> = None;
    let mut ptr_idx: *mut u8 = std::ptr::null_mut();

    println!("testing binn integer read conversion... ");

    obj = binn_object();
    assert!(obj.is_some());
    
    {
        assert_eq!(binn_object_set_int8(&mut obj, Some("int8"), -8), 1);
        assert_eq!(binn_object_set_int16(&mut obj, Some("int16"), -16), 1);
        assert_eq!(binn_object_set_int32(&mut obj, Some("int32"), -32), 1);
        assert_eq!(binn_object_set_int64(&mut obj, Some("int64"), -64), 1);
        assert_eq!(binn_object_set_uint8(&mut obj, Some("uint8"), 111), 1);
        assert_eq!(binn_object_set_uint16(&mut obj, Some("uint16"), 112), 1);
        assert_eq!(binn_object_set_uint32(&mut obj, Some("uint32"), 113), 1);
        assert_eq!(binn_object_set_uint64(&mut obj, Some("uint64"), 114), 1);
    }

    ptr_idx = binn_ptr(obj.as_ref().and_then(|b| b.ptr.as_ref().map(|p| p.as_ref() as *const _ as *mut u8))).unwrap_or(std::ptr::null_mut());
    ptr = Some(unsafe { std::slice::from_raw_parts(ptr_idx as *const u8, 0) });

    assert_eq!(binn_object_int8(ptr, Some("int8")), Some(-8));
    assert_eq!(binn_object_int8(ptr, Some("int16")), Some(-16));
    assert_eq!(binn_object_int8(ptr, Some("int32")), Some(-32));
    assert_eq!(binn_object_int8(ptr, Some("int64")), Some(-64));
    assert_eq!(binn_object_int16(ptr, Some("int8")), -8);
    assert_eq!(binn_object_int16(ptr, Some("int16")), -16);
    assert_eq!(binn_object_int16(ptr, Some("int32")), -32);
    assert_eq!(binn_object_int16(ptr, Some("int64")), -64);
    assert_eq!(binn_object_int32(ptr, Some("int8")), -8);
    assert_eq!(binn_object_int32(ptr, Some("int16")), -16);
    assert_eq!(binn_object_int32(ptr, Some("int32")), -32);
    assert_eq!(binn_object_int32(ptr, Some("int64")), -64);
    assert_eq!(binn_object_int64(ptr, Some("int8")), -8);
    assert_eq!(binn_object_int64(ptr, Some("int16")), -16);
    assert_eq!(binn_object_int64(ptr, Some("int32")), -32);
    assert_eq!(binn_object_int64(ptr, Some("int64")), -64);
    assert_eq!(binn_object_int8(ptr, Some("uint8")), Some(111));
    assert_eq!(binn_object_int8(ptr, Some("uint16")), Some(112));
    assert_eq!(binn_object_int8(ptr, Some("uint32")), Some(113));
    assert_eq!(binn_object_int8(ptr, Some("uint64")), Some(114));
    assert_eq!(binn_object_int16(ptr, Some("uint8")), 111);
    assert_eq!(binn_object_int16(ptr, Some("uint16")), 112);
    assert_eq!(binn_object_int16(ptr, Some("uint32")), 113);
    assert_eq!(binn_object_int16(ptr, Some("uint64")), 114);
    assert_eq!(binn_object_int32(ptr, Some("uint8")), 111);
    assert_eq!(binn_object_int32(ptr, Some("uint16")), 112);
    assert_eq!(binn_object_int32(ptr, Some("uint32")), 113);
    assert_eq!(binn_object_int32(ptr, Some("uint64")), 114);
    assert_eq!(binn_object_int64(ptr, Some("uint8")), 111);
    assert_eq!(binn_object_int64(ptr, Some("uint16")), 112);
    assert_eq!(binn_object_int64(ptr, Some("uint32")), 113);
    assert_eq!(binn_object_int64(ptr, Some("uint64")), 114);

    binn_free(&mut obj);
    println!("OK");
}
pub fn init_udts() {
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut obj_idx = 0;
    let mut date: u16;
    let mut value: i64;
    let mut ptr: Option<*mut u8> = None;
    let mut ptr_idx = 0;

    println!("testing UDTs...");

    assert_eq!(
        date_to_str(str_to_date(Some("1950-08-15")).unwrap()),
        "1950-08-15"
    );
    assert_eq!(
        date_to_str(str_to_date(Some("1900-12-01")).unwrap()),
        "1900-12-01"
    );
    assert_eq!(
        date_to_str(str_to_date(Some("2000-10-31")).unwrap()),
        "2000-10-31"
    );
    assert_eq!(
        date_to_str(str_to_date(Some("2014-03-19")).unwrap()),
        "2014-03-19"
    );

    println!("curr={}", currency_to_str(str_to_currency(Some("123.456")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.45")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.4")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("1.2")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.987")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.98")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.9")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.0")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.4567")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.45678")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("123.456789")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some("0.1234")).unwrap()).unwrap());
    println!("curr={}", currency_to_str(str_to_currency(Some(".1234")).unwrap()).unwrap());

    assert_eq!(float_to_currency(2.5).unwrap(), 25000);
    assert_eq!(float_to_currency(5.0).unwrap(), 50000);
    assert_eq!(str_to_currency(Some("1.1")).unwrap(), 11000);
    assert_eq!(str_to_currency(Some("12")).unwrap(), 120000);
    assert_eq!(mul_currency(20000, 20000), 40000);
    assert_eq!(mul_currency(20000, 25000), 50000);
    assert_eq!(mul_currency(30000, 40000), 120000);
    assert_eq!(div_currency(80000, 20000), 40000);
    assert_eq!(div_currency(120000, 40000), 30000);
    assert_eq!(div_currency(100000, 40000), 25000);

    println!(
        "1.1 * 2.5 = {}",
        currency_to_str(mul_currency(
            str_to_currency(Some("1.1")).unwrap(),
            float_to_currency(2.5).unwrap()
        )).unwrap()
    );
    println!(
        "12 / 5 = {}",
        currency_to_str(div_currency(
            str_to_currency(Some("12")).unwrap(),
            float_to_currency(5.0).unwrap()
        )).unwrap()
    );

    MY_DATE.store(binn_create_type(0x40, 0x0a), Ordering::Relaxed);
    MY_CURRENCY.store(binn_create_type(0x80, 0x0a), Ordering::Relaxed);

    obj = binn_object();
    assert!(obj.is_some());

    date = str_to_date(Some("1950-08-15")).unwrap();
    println!(" date 1: {} {}", date, date_to_str(date));
    assert_eq!(
        binn_object_set(&mut obj, Some("date1"), MY_DATE.load(Ordering::Relaxed), None, 0),
        1
    );
    assert_eq!(
        binn_object_set(&mut obj, Some("date1"), MY_DATE.load(Ordering::Relaxed), None, 0),
        0
    );

    date = str_to_date(Some("1999-12-31")).unwrap();
    println!(" date 2: {} {}", date, date_to_str(date));
    binn_object_set(&mut obj, Some("date2"), MY_DATE.load(Ordering::Relaxed), None, 0);

    value = str_to_currency(Some("123.456")).unwrap();
    println!(" curr 1: {} {}", value, currency_to_str(value).unwrap());
    binn_object_set(&mut obj, Some("curr1"), MY_CURRENCY.load(Ordering::Relaxed), None, 0);

    value = str_to_currency(Some("123.45")).unwrap();
    println!(" curr 2: {} {}", value, currency_to_str(value).unwrap());
    binn_object_set(&mut obj, Some("curr2"), MY_CURRENCY.load(Ordering::Relaxed), None, 0);

    value = str_to_currency(Some("12.5")).unwrap();
    println!(" curr 3: {} {}", value, currency_to_str(value).unwrap());
    binn_object_set(&mut obj, Some("curr3"), MY_CURRENCY.load(Ordering::Relaxed), None, 0);

    value = str_to_currency(Some("5")).unwrap();
    println!(" curr 4: {} {}", value, currency_to_str(value).unwrap());
    binn_object_set(&mut obj, Some("curr4"), MY_CURRENCY.load(Ordering::Relaxed), None, 0);

    value = str_to_currency(Some("0.75")).unwrap();
    println!(" curr 5: {} {}", value, currency_to_str(value).unwrap());
    binn_object_set(&mut obj, Some("curr5"), MY_CURRENCY.load(Ordering::Relaxed), None, 0);

    // Fixed complex expressions with proper handling
    let raw_ptr_option = obj.as_ref().and_then(|b| {
        b.ptr.as_ref().map(|p| {
            p.as_ref() as *const () as *mut u8
        })
    });

    ptr_idx = binn_ptr(raw_ptr_option)
        .map(|p| p as usize)
        .unwrap_or(0);

    ptr = raw_ptr_option;

    // Create byte slice from pointer and size for binn_object_get
    let size = obj.as_ref().map(|b| b.size as usize).unwrap_or(0);
    let byte_slice = match ptr {
        Some(p) if size > 0 => unsafe { Some(std::slice::from_raw_parts(p as *const u8, size)) },
        _ => None,
    };

    // Use byte_slice in binn_object_get calls
    assert_eq!(
        binn_object_get(byte_slice, Some("date1"), MY_DATE.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" date 1: {} {}", date, date_to_str(date));
    assert_eq!(
        binn_object_get(byte_slice, Some("date2"), MY_DATE.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" date 2: {} {}", date, date_to_str(date));
    assert_eq!(
        binn_object_get(byte_slice, Some("curr1"), MY_CURRENCY.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" curr 1: {} {}", value, currency_to_str(value).unwrap());
    assert_eq!(
        binn_object_get(byte_slice, Some("curr2"), MY_CURRENCY.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" curr 2: {} {}", value, currency_to_str(value).unwrap());
    assert_eq!(
        binn_object_get(byte_slice, Some("curr3"), MY_CURRENCY.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" curr 3: {} {}", value, currency_to_str(value).unwrap());
    assert_eq!(
        binn_object_get(byte_slice, Some("curr4"), MY_CURRENCY.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" curr 4: {} {}", value, currency_to_str(value).unwrap());
    assert_eq!(
        binn_object_get(byte_slice, Some("curr5"), MY_CURRENCY.load(Ordering::Relaxed), None, None),
        1
    );
    println!(" curr 5: {} {}", value, currency_to_str(value).unwrap());

    binn_free(&mut obj);
    println!("testing UDTs... OK");
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

    let obj1ptr = test_create_object_1(&mut obj1size);
    let obj2ptr = test_create_object_2(&mut obj2size);

    // Convert raw pointers to slices for bounds checking
    if let Some(obj1ptr) = obj1ptr {
        assert!(!obj1ptr.is_null());
    }
    if let Some(obj2ptr) = obj2ptr {
        assert!(!obj2ptr.as_ptr().is_null());
    }

    println!("obj1size={} obj2size={}", obj1size, obj2size);
    assert_eq!(obj1size, obj2size);

    // Convert raw pointer to slice for test_binn_read
    if let Some(obj1ptr) = obj1ptr {
        test_binn_read(Some(unsafe { std::slice::from_raw_parts(obj1ptr, obj1size as usize) }));
    }

    test_binn_iter(0);
    test_binn_iter(1);
}
