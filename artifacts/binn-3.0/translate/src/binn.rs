use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::alloc::Layout;
use std::mem;
use std::ptr;
use std::convert::TryFrom;
use std::convert::TryInto;
use std::ffi::CStr;
use std::ffi::CString;
use std::cmp::Ordering;
use super::Binn_Struct;
use std::boxed::Box;
use std::os::raw::c_char;

pub type Binn = Option<Box<Binn_Struct>>;

pub fn binn_version() -> &'static str {
    "3.0.0"
}
pub fn binn_create_type(storage_type: i32, data_type_index: i32) -> i32 {
    if data_type_index < 0 {
        return -1;
    }
    if storage_type < 0x00 || storage_type > 0xE0 {
        return -1;
    }
    if data_type_index < 16 {
        return storage_type | data_type_index;
    } else if data_type_index < 4096 {
        let mut storage_type = storage_type | 0x10;
        storage_type <<= 8;
        let data_type_index = data_type_index >> 4;
        storage_type | data_type_index
    } else {
        -1
    }
}
pub fn binn_is_struct(ptr: Option<&u32>) -> bool {
    // Check if ptr is None (equivalent to NULL check in C)
    match ptr {
        None => false,
        Some(p) => *p == 0x1F22B11F,  // Compare the dereferenced value with the magic number
    }
}
pub fn strlen2(str: Option<&str>) -> usize {
    match str {
        None => 0,
        Some(s) => s.len(),
    }
}
pub fn binn_get_ptr_type(ptr: Option<*const u32>) -> i32 {
    match ptr {
        None => 0,
        Some(ptr) => unsafe {
            match *ptr {
                0x1F22B11F => 1,
                _ => 2,
            }
        }
    }
}
pub fn CalcAllocation(needed_size: i32, alloc_size: i32) -> i32 {
    let mut calc_size = alloc_size;
    while calc_size < needed_size {
        calc_size <<= 1;
    }
    calc_size
}
pub fn type_family(type_: i32) -> i32 {
    match type_ {
        0xE0 | 0xE1 | 0xE2 => 0xf7,
        0x21 | 0x41 | 0x61 | 0x81 | 0x20 | 0x40 | 0x60 | 0x80 => 0xf2,
        0x62 | 0x82 | 0xA6 | 0xA7 => 0xf3,
        0xA0 | 0xB001 | 0xB005 | 0xB002 | 0xB003 | 0xB004 => 0xf4,
        0xC0 | 0xD001 | 0xD002 | 0xD003 | 0xD004 => 0xf5,
        0xA4 | 0x83 | 0xA2 | 0xA3 | 0xA1 => 0xf4,
        0x80061 => 0xf6,
        0x00 => 0xf1,
        _ => 0x00,
    }
}
pub fn GetWriteConvertedData(ptype: &mut i32, ppvalue: &mut Option<&mut [u8]>, psize: &mut i32) -> bool {
    let type_ = *ptype;
    
    if ppvalue.is_none() {
        match type_ {
            0x00 | 0x01 | 0x02 => {},
            0xA0 | 0xC0 => {
                if *psize == 0 {
                    // Do nothing, just continue
                }
            },
            _ => return false,
        }
    }

    match type_ {
        0xA4 | 0xA5 | 0xA2 | 0xA1 | 0xA3 => return true,
        0x80061 => {
            if let Some(value) = ppvalue {
                if value.is_empty() || value[0] == 0 {
                    *ptype = 0x02;
                } else {
                    *ptype = 0x01;
                }
            }
        },
        _ => {},
    }

    true
}
pub fn int_type(type_: i32) -> i32 {
    match type_ {
        0x21 | 0x41 | 0x61 | 0x81 => 11,
        0x20 | 0x40 | 0x60 | 0x80 => 22,
        _ => 0,
    }
}
pub fn copy_raw_value(psource: Option<&[u8]>, pdest: Option<&mut [u8]>, data_store: u8) -> bool {
    // Check for None (equivalent to NULL checks in C)
    if psource.is_none() || pdest.is_none() {
        return false;
    }
    
    let psource = psource.unwrap();
    let pdest = pdest.unwrap();
    
    // Ensure we have enough bytes to read/write
    match data_store {
        0x00 => (), // No operation case
        0x20 => {
            if psource.len() >= 1 && pdest.len() >= 1 {
                pdest[0] = psource[0];
            } else {
                return false;
            }
        }
        0x40 => {
            if psource.len() >= 2 && pdest.len() >= 2 {
                let src = psource[0..2].try_into().unwrap();
                let val = i16::from_le_bytes(src);
                pdest[0..2].copy_from_slice(&val.to_le_bytes());
            } else {
                return false;
            }
        }
        0x60 => {
            if psource.len() >= 4 && pdest.len() >= 4 {
                let src = psource[0..4].try_into().unwrap();
                let val = i32::from_le_bytes(src);
                pdest[0..4].copy_from_slice(&val.to_le_bytes());
            } else {
                return false;
            }
        }
        0x80 => {
            if psource.len() >= 8 && pdest.len() >= 8 {
                let src = psource[0..8].try_into().unwrap();
                let val = u64::from_le_bytes(src);
                pdest[0..8].copy_from_slice(&val.to_le_bytes());
            } else {
                return false;
            }
        }
        0xA0 | 0xC0 | 0xE0 => {
            // In Rust, we can't just copy raw pointers safely, so we'll copy the bytes
            // This is a different semantic than C but safer
            let len = psource.len();
            if pdest.len() >= len {
                pdest[..len].copy_from_slice(psource);
            } else {
                return false;
            }
        }
        _ => return false,
    }
    
    true
}
pub fn copy_float_value(
    psource: Option<&mut [u8]>,
    pdest: Option<&mut [u8]>,
    source_type: i32,
    dest_type: i32,
) -> bool {
    // Check for None (equivalent to NULL checks in C)
    if psource.is_none() || pdest.is_none() {
        return false;
    }

    let psource = psource.unwrap();
    let pdest = pdest.unwrap();

    match source_type {
        0x62 => {
            // Convert float to double
            if psource.len() >= std::mem::size_of::<f32>() && pdest.len() >= std::mem::size_of::<f64>() {
                let src_value = f32::from_le_bytes(psource[..4].try_into().unwrap());
                let dest_slice = &mut pdest[..8];
                dest_slice.copy_from_slice(&f64::from(src_value).to_le_bytes());
                true
            } else {
                false
            }
        }
        0x82 => {
            // Convert double to float
            if psource.len() >= std::mem::size_of::<f64>() && pdest.len() >= std::mem::size_of::<f32>() {
                let src_value = f64::from_le_bytes(psource[..8].try_into().unwrap());
                let dest_slice = &mut pdest[..4];
                dest_slice.copy_from_slice(&(src_value as f32).to_le_bytes());
                true
            } else {
                false
            }
        }
        _ => false,
    }
}
pub fn binn_get_type_info(
    long_type: i32,
    pstorage_type: Option<&mut i32>,
    pextra_type: Option<&mut i32>,
) -> BOOL {
    let mut storage_type;
    let mut extra_type;
    let mut retval = 1;
    let mut long_type = long_type;

    loop {
        if long_type < 0 {
            storage_type = -1;
            extra_type = -1;
            retval = 0;
            break;
        } else if long_type <= 0xff {
            storage_type = long_type & 0xE0;
            extra_type = long_type & 0x0F;
            break;
        } else if long_type <= 0xffff {
            storage_type = long_type & 0xE000;
            storage_type >>= 8;
            extra_type = long_type & 0x0FFF;
            extra_type >>= 4;
            break;
        } else if long_type & 0x80000 != 0 {
            long_type &= 0xffff;
            continue;
        } else {
            storage_type = -1;
            extra_type = -1;
            retval = 0;
            break;
        }
    }

    if let Some(pstorage_type) = pstorage_type {
        *pstorage_type = storage_type;
    }
    if let Some(pextra_type) = pextra_type {
        *pextra_type = extra_type;
    }

    retval
}
pub fn check_alloc_functions() {
    lazy_static! {
        pub static ref MALLOC_FN: Mutex<Option<unsafe fn(Layout) -> *mut u8>> = Mutex::new(None);
        pub static ref REALLOC_FN: Mutex<Option<fn(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>>>> = Mutex::new(None);
        pub static ref FREE_FN: Mutex<Option<Box<dyn FnMut(Option<Box<()>>) + Send>>> = Mutex::new(None);
    }

    {
        let mut malloc_fn = MALLOC_FN.lock().unwrap();
        if malloc_fn.is_none() {
            *malloc_fn = Some(std::alloc::alloc);
        }
    }

    {
        let mut realloc_fn = REALLOC_FN.lock().unwrap();
        if realloc_fn.is_none() {
            *realloc_fn = Some(|ptr, size| {
                let layout = Layout::from_size_align(size, std::mem::align_of::<u8>()).unwrap();
                let old_ptr = ptr.map(|b| Box::into_raw(b) as *mut u8).unwrap_or(std::ptr::null_mut());
                let new_ptr = unsafe { std::alloc::realloc(old_ptr, layout, size) };
                if new_ptr.is_null() {
                    None
                } else {
                    Some(unsafe { Box::from_raw(std::slice::from_raw_parts_mut(new_ptr, size)) })
                }
            });
        }
    }

    {
        let mut free_fn = FREE_FN.lock().unwrap();
        if free_fn.is_none() {
            *free_fn = Some(Box::new(|ptr| {
                if let Some(ptr) = ptr {
                    drop(ptr);
                }
            }));
        }
    }
}

pub fn binn_malloc(size: i32) -> Option<*mut u8> {
    check_alloc_functions();
    let layout = match Layout::from_size_align(size as usize, 1) {
        Ok(l) => l,
        Err(_) => return None,
    };
    let malloc_fn = MALLOC_FN.lock().unwrap();
    match *malloc_fn {
        Some(f) => Some(f(layout)),
        None => None,
    }
}
pub fn binn_alloc_item() -> Binn {
    // Allocate memory for the binn struct
    let item_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32);
    
    // Check if allocation succeeded
    if item_ptr.is_none() {
        return None;
    }
    
    // Convert raw pointer to Box and initialize the struct
    let mut item = unsafe { Box::from_raw(item_ptr.unwrap() as *mut Binn_Struct) };
    
    // Initialize all fields to zero (equivalent to memset)
    *item = Binn_Struct {
        header: 0x1F22B11F,
        allocated: 1,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    Some(item)
}

pub fn binn_memdup(src: Option<&[u8]>, size: i32) -> Option<Box<[u8]>> {
    // Check for NULL pointer or invalid size
    if src.is_none() || size <= 0 {
        return None;
    }

    let src = src.unwrap();
    
    // Allocate memory using binn_malloc
    let dest_ptr = binn_malloc(size)?;
    
    // Create a slice from the allocated memory
    let dest_slice = unsafe { std::slice::from_raw_parts_mut(dest_ptr, size as usize) };
    
    // Copy the data from src to dest
    dest_slice.copy_from_slice(src);
    
    // Convert the slice into a Box to manage memory
    Some(unsafe { Box::from_raw(dest_slice as *mut [u8]) })
}
pub fn binn_value(
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
    freefn: Binn_Mem_Free,
) -> Binn {
    // Define a marker function for duplication requests
    fn duplicate_marker(_: Option<Box<()>>) {
        panic!("duplicate_marker function should not be called");
    }
    
    // Define a default free function that uses the global FREE_FN
    fn default_free_fn(ptr: Option<Box<()>>) {
        FREE_FN.lock().unwrap().as_mut().unwrap()(ptr);
    }

    let mut storage_type = 0;
    let item = binn_alloc_item();
    
    if let Some(mut item) = item {
        item.type_ = type_;
        binn_get_type_info(type_, Some(&mut storage_type), None);
        
        match storage_type {
            0x00 => (), // No action needed
            
            0xA0 => {
                let size = if size == 0 {
                    pvalue.map(|v| v.len() as i32 + 1).unwrap_or(0)
                } else {
                    size
                };
                
                if freefn == Some(duplicate_marker) {
                    if let Some(dup) = binn_memdup(pvalue, size) {
                        item.ptr = Some(Box::into_raw(Box::new(dup))).map(|p| unsafe { Box::from_raw(p as *mut ()) });
                        item.freefn = Some(default_free_fn);
                        if storage_type == 0xA0 {
                            item.size = size - 1;
                        } else {
                            item.size = size;
                        }
                    } else {
                        FREE_FN.lock().unwrap().as_mut().unwrap()(Option::None);
                        return Option::None;
                    }
                } else {
                    item.ptr = pvalue.map(|v| Box::into_raw(Box::new(v.to_vec()))).map(|p| unsafe { Box::from_raw(p as *mut ()) });
                    item.freefn = freefn;
                    item.size = size;
                }
            }
            
            0xC0 | 0xE0 => {
                if freefn == Some(duplicate_marker) {
                    if let Some(dup) = binn_memdup(pvalue, size) {
                        item.ptr = Some(Box::into_raw(Box::new(dup))).map(|p| unsafe { Box::from_raw(p as *mut ()) });
                        item.freefn = Some(default_free_fn);
                        item.size = size;
                    } else {
                        FREE_FN.lock().unwrap().as_mut().unwrap()(Option::None);
                        return Option::None;
                    }
                } else {
                    item.ptr = pvalue.map(|v| Box::into_raw(Box::new(v.to_vec()))).map(|p| unsafe { Box::from_raw(p as *mut ()) });
                    item.freefn = freefn;
                    item.size = size;
                }
            }
            
            _ => {
                item.ptr = Some(Box::into_raw(Box::new(&mut item.vint32))).map(|p| unsafe { Box::from_raw(p as *mut ()) });
                copy_raw_value(pvalue, Some(&mut [item.vint8 as u8]), storage_type as u8);
            }
        }
        
        Some(item)
    } else {
        Option::None
    }
}
pub fn binn_get_read_storage(type_: i32) -> i32 {
    match type_ {
        0x80061 | 0x01 | 0x02 => 0x60,
        _ => {
            let mut storage_type = 0;
            binn_get_type_info(type_, Some(&mut storage_type), None);
            storage_type
        }
    }
}
pub fn copy_int_value(
    psource: Option<&[u8]>,
    pdest: Option<&mut [u8]>,
    source_type: i32,
    dest_type: i32,
) -> bool {
    // Check for None inputs (equivalent to NULL checks in C)
    if psource.is_none() || pdest.is_none() {
        return false;
    }
    let psource = psource.unwrap();
    let pdest = pdest.unwrap();

    let mut vuint64: uint64 = 0;
    let mut local_vint64: int64 = 0;  // Renamed from vint64 to avoid shadowing

    // Source type handling
    match source_type {
        0x21 => {
            if psource.len() < 1 {
                return false;
            }
            local_vint64 = psource[0] as i8 as int64;
        }
        0x41 => {
            if psource.len() < 2 {
                return false;
            }
            local_vint64 = i16::from_le_bytes([psource[0], psource[1]]) as int64;
        }
        0x61 => {
            if psource.len() < 4 {
                return false;
            }
            local_vint64 = i32::from_le_bytes([psource[0], psource[1], psource[2], psource[3]]) as int64;
        }
        0x81 => {
            if psource.len() < 8 {
                return false;
            }
            local_vint64 = int64::from_le_bytes([
                psource[0], psource[1], psource[2], psource[3],
                psource[4], psource[5], psource[6], psource[7],
            ]);
        }
        0x20 => {
            if psource.len() < 1 {
                return false;
            }
            vuint64 = psource[0] as uint64;
        }
        0x40 => {
            if psource.len() < 2 {
                return false;
            }
            vuint64 = u16::from_le_bytes([psource[0], psource[1]]) as uint64;
        }
        0x60 => {
            if psource.len() < 4 {
                return false;
            }
            vuint64 = u32::from_le_bytes([psource[0], psource[1], psource[2], psource[3]]) as uint64;
        }
        0x80 => {
            if psource.len() < 8 {
                return false;
            }
            vuint64 = uint64::from_le_bytes([
                psource[0], psource[1], psource[2], psource[3],
                psource[4], psource[5], psource[6], psource[7],
            ]);
        }
        _ => return false,
    }

    // Type conversion checks
    if int_type(source_type) == 22 && int_type(dest_type) == 11 {
        if vuint64 > i64::MAX as uint64 {
            return false;
        }
        local_vint64 = vuint64 as int64;
    } else if int_type(source_type) == 11 && int_type(dest_type) == 22 {
        if local_vint64 < 0 {
            return false;
        }
        vuint64 = local_vint64 as uint64;
    }

    // Destination type handling
    match dest_type {
        0x21 => {
            if let Ok(value) = i8::try_from(local_vint64) {
                if pdest.len() < 1 {
                    return false;
                }
                pdest[0] = value as u8;
            } else {
                return false;
            }
        }
        0x41 => {
            if let Ok(value) = i16::try_from(local_vint64) {
                if pdest.len() < 2 {
                    return false;
                }
                pdest[..2].copy_from_slice(&value.to_le_bytes());
            } else {
                return false;
            }
        }
        0x61 => {
            if let Ok(value) = i32::try_from(local_vint64) {
                if pdest.len() < 4 {
                    return false;
                }
                pdest[..4].copy_from_slice(&value.to_le_bytes());
            } else {
                return false;
            }
        }
        0x81 => {
            if pdest.len() < 8 {
                return false;
            }
            pdest[..8].copy_from_slice(&local_vint64.to_le_bytes());
        }
        0x20 => {
            if let Ok(value) = u8::try_from(vuint64) {
                if pdest.len() < 1 {
                    return false;
                }
                pdest[0] = value;
            } else {
                return false;
            }
        }
        0x40 => {
            if let Ok(value) = u16::try_from(vuint64) {
                if pdest.len() < 2 {
                    return false;
                }
                pdest[..2].copy_from_slice(&value.to_le_bytes());
            } else {
                return false;
            }
        }
        0x60 => {
            if let Ok(value) = u32::try_from(vuint64) {
                if pdest.len() < 4 {
                    return false;
                }
                pdest[..4].copy_from_slice(&value.to_le_bytes());
            } else {
                return false;
            }
        }
        0x80 => {
            if pdest.len() < 8 {
                return false;
            }
            pdest[..8].copy_from_slice(&vuint64.to_le_bytes());
        }
        _ => return false,
    }

    true
}
pub fn copy_value(
    psource: Option<&mut [u8]>,
    pdest: Option<&mut [u8]>,
    source_type: i32,
    dest_type: i32,
    data_store: u8,
) -> bool {
    if type_family(source_type) != type_family(dest_type) {
        return false;
    }
    
    match type_family(source_type) {
        0xf2 if source_type != dest_type => {
            copy_int_value(psource.as_deref(), pdest, source_type, dest_type)
        }
        0xf3 if source_type != dest_type => {
            copy_float_value(psource, pdest, source_type, dest_type)
        }
        _ => {
            copy_raw_value(psource.as_deref(), pdest, data_store)
        }
    }
}
pub fn copy_be32(pdest: &mut u32, psource: &u32) {
    let source = psource.to_be_bytes(); // Convert to big-endian bytes
    let dest = &mut pdest.to_be_bytes(); // Convert to big-endian bytes (mutable)
    
    // Perform the byte swapping
    dest[0] = source[3];
    dest[1] = source[2];
    dest[2] = source[1];
    dest[3] = source[0];
    
    // Convert the bytes back to u32
    *pdest = u32::from_be_bytes(*dest);
}
pub fn copy_be16(pdest: &mut u16, psource: &u16) {
    let source_bytes = psource.to_be_bytes();
    *pdest = u16::from_be_bytes([source_bytes[1], source_bytes[0]]);
}
pub fn copy_be64(pdest: &mut u64, psource: &u64) {
    let source = psource.to_be_bytes();  // Convert to big-endian byte array
    let dest = &mut pdest.to_be_bytes();  // Convert to mutable big-endian byte array
    
    // Copy bytes in reverse order (big-endian to little-endian or vice versa)
    for i in 0..8 {
        dest[i] = source[7 - i];
    }
    
    // Convert the modified bytes back to u64
    *pdest = u64::from_be_bytes(*dest);
}
pub fn IsValidBinnHeader(
    pbuf: Option<&[u8]>,
    ptype: Option<&mut i32>,
    pcount: Option<&mut i32>,
    psize: Option<&mut i32>,
    pheadersize: Option<&mut i32>,
) -> bool {
    // Check for NULL pointer equivalent
    let pbuf = match pbuf {
        Some(buf) => buf,
        None => return false,
    };

    let mut p_idx = 0;
    let mut plimit_idx = 0;
    let mut int32: i32;
    let mut type_: i32;
    let mut size: i32;
    let mut count: i32;

    // Calculate plimit_idx if psize is provided and > 0
    if let Some(ref psize_val) = psize {
        if **psize_val > 0 {
            plimit_idx = p_idx + **psize_val as usize - 1;
        }
    }

    // Check buffer bounds
    if p_idx >= pbuf.len() {
        return false;
    }
    let byte = pbuf[p_idx];
    p_idx += 1;

    // Header validation checks
    if (byte & 0xE0) != 0xE0 {
        return false;
    }
    if byte & 0x10 != 0 {
        return false;
    }

    type_ = byte as i32;
    match type_ {
        0xE0 | 0xE1 | 0xE2 => (),
        _ => return false,
    }

    // Check bounds before reading
    if plimit_idx > 0 && p_idx > plimit_idx {
        return false;
    }

    // Read size field
    if p_idx >= pbuf.len() {
        return false;
    }
    int32 = pbuf[p_idx] as i32;
    if int32 & 0x80 != 0 {
        if p_idx + 4 > pbuf.len() {
            return false;
        }
        if plimit_idx > 0 && p_idx + 4 - 1 > plimit_idx {
            return false;
        }
        let mut temp: u32 = 0;
        copy_be32(&mut temp, &u32::from_be_bytes(pbuf[p_idx..p_idx+4].try_into().unwrap()));
        int32 = (temp & 0x7FFFFFFF) as i32;
        p_idx += 4;
    } else {
        p_idx += 1;
    }
    size = int32;

    // Read count field
    if p_idx >= pbuf.len() {
        return false;
    }
    int32 = pbuf[p_idx] as i32;
    if int32 & 0x80 != 0 {
        if p_idx + 4 > pbuf.len() {
            return false;
        }
        if plimit_idx > 0 && p_idx + 4 - 1 > plimit_idx {
            return false;
        }
        let mut temp: u32 = 0;
        copy_be32(&mut temp, &u32::from_be_bytes(pbuf[p_idx..p_idx+4].try_into().unwrap()));
        int32 = (temp & 0x7FFFFFFF) as i32;
        p_idx += 4;
    } else {
        p_idx += 1;
    }
    count = int32;

    // Final validation
    if size < 3 || count < 0 {
        return false;
    }

    // Update output parameters if provided
    if let Some(ptype_val) = ptype {
        *ptype_val = type_;
    }
    if let Some(pcount_val) = pcount {
        *pcount_val = count;
    }
    if let Some(psize_val) = psize {
        if *psize_val == 0 {
            *psize_val = size;
        }
    }
    if let Some(pheadersize_val) = pheadersize {
        *pheadersize_val = (p_idx) as i32;
    }

    true
}
pub fn GetValue(p: Option<&[u8]>, value: Option<&mut Binn_Struct>) -> BOOL {
    // Check for null input
    if value.is_none() {
        return 0;
    }
    let value = value.unwrap();
    let p = match p {
        Some(slice) => slice,
        None => return 0,
    };

    // Initialize the struct
    *value = Binn_Struct {
        header: 0x1F22B11F,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    let mut p_idx = 0;
    let byte = p[p_idx];
    p_idx += 1;

    let storage_type = byte & 0xE0;
    let data_type = if byte & 0x10 != 0 {
        let mut dt = (byte as i32) << 8;
        dt |= p[p_idx] as i32;
        p_idx += 1;
        dt
    } else {
        byte as i32
    };

    value.type_ = data_type;

    match storage_type {
        0x00 => (), // No action needed
        0x20 => {
            value.vuint8 = p[p_idx];
            value.ptr = Some(Box::new(()));
            p_idx += 1;
        }
        0x40 => {
            let mut v = 0u16;
            copy_be16(&mut v, &(p[p_idx] as u16));
            value.vint16 = v as i16;
            value.ptr = Some(Box::new(()));
        }
        0x60 => {
            let mut v = 0u32;
            copy_be32(&mut v, &(p[p_idx] as u32));
            value.vint32 = v as i32;
            value.ptr = Some(Box::new(()));
        }
        0x80 => {
            let mut v = 0u64;
            copy_be64(&mut v, &(p[p_idx] as u64));
            value.vint64 = v as i64;
            value.ptr = Some(Box::new(()));
        }
        0xA0 | 0xC0 => {
            let mut DataSize = p[p_idx] as i32;
            if DataSize & 0x80 != 0 {
                let mut v = 0u32;
                copy_be32(&mut v, &(p[p_idx] as u32));
                DataSize = (v & 0x7FFFFFFF) as i32;
                p_idx += 4;
            } else {
                p_idx += 1;
            }
            value.size = DataSize;
            value.ptr = Some(Box::new(()));
        }
        0xE0 => {
            let p2 = &p[p_idx..];
            if !IsValidBinnHeader(
                Some(p2),
                None,
                Some(&mut value.count),
                Some(&mut value.size),
                None,
            ) {
                return 0;
            }
            value.ptr = Some(Box::new(()));
        }
        _ => return 0,
    }

    match value.type_ {
        0x01 => {
            value.type_ = 0x80061;
            value.vbool = 1;
            value.ptr = Some(Box::new(()));
        }
        0x02 => {
            value.type_ = 0x80061;
            value.vbool = 0;
            value.ptr = Some(Box::new(()));
        }
        _ => (),
    }

    1
}
pub fn helper_AdvanceDataPos_1<'a>(
    p_idx_ref: &mut u32,
    DataSize_ref: &mut i32,
    p: &'a [u8],
    plimit: *const u8,
) -> Option<&'a [u8]> {
    let mut p_idx = *p_idx_ref;
    let mut DataSize = *DataSize_ref;

    // Check if current position is beyond plimit
    if p.get(p_idx as usize..).is_none() || &p[p_idx as usize] > unsafe { &*plimit } {
        return None;
    }

    // Get DataSize from current position
    DataSize = p[p_idx as usize] as i32;

    if DataSize & 0x80 != 0 {
        // Check if we have enough space for a 32-bit value
        if p_idx as usize + std::mem::size_of::<u32>() > p.len() {
            return None;
        }

        // Convert the slice to a u32 pointer and copy with byte order conversion
        let mut new_size = 0u32;
        copy_be32(
            &mut new_size,
            unsafe { &*(p.as_ptr().add(p_idx as usize) as *const u32) },
        );
        DataSize = (new_size & 0x7FFFFFFF) as i32;
    }

    DataSize -= 1;
    p_idx += DataSize as u32;

    // Update the references
    *p_idx_ref = p_idx;
    *DataSize_ref = DataSize;

    // Return the remaining slice if valid
    if p_idx as usize <= p.len() {
        Some(&p[p_idx as usize..])
    } else {
        None
    }
}
pub fn helper_AdvanceDataPos_2<'a>(
    p_idx_ref: &mut u32,
    DataSize_ref: &mut i32,
    p: &'a [u8],
    plimit: *const u8,
    storage_type: i32,
) -> Option<&'a [u8]> {
    let mut p_idx = *p_idx_ref;
    let mut DataSize = *DataSize_ref;

    // Check if current position exceeds plimit
    if p.get(p_idx as usize..).is_none() || &p[p_idx as usize] > unsafe { &*plimit } {
        return None;
    }

    // Read DataSize from current position
    DataSize = p[p_idx as usize] as i32;

    if DataSize & 0x80 != 0 {
        // Check if we can read 4 bytes
        if p_idx + 4 > p.len() as u32 || unsafe { &p[p_idx as usize + 4] > &*plimit } {
            return None;
        }

        // Read big-endian 32-bit value
        let mut temp: u32 = 0;
        copy_be32(&mut temp, unsafe { &*(p.as_ptr().add(p_idx as usize) as *const u32) });
        DataSize = (temp & 0x7FFFFFFF) as i32;
        p_idx += 4;
    } else {
        p_idx += 1;
    }

    // Advance by DataSize
    p_idx += DataSize as u32;

    // Additional byte for specific storage type
    if storage_type == 0xA0 {
        p_idx += 1;
    }

    // Update references
    *p_idx_ref = p_idx;
    *DataSize_ref = DataSize;

    Some(&p[p_idx as usize..])
}
pub fn AdvanceDataPos<'a>(p: &'a [u8], plimit: *const u8) -> Option<&'a [u8]> {
    let mut p_idx: u32 = 0;
    let mut DataSize: i32 = 0;

    // Check if initial position is beyond plimit
    if p.get(p_idx as usize).map_or(true, |&byte| &byte as *const u8 > plimit) {
        return None;
    }

    let byte = p[p_idx as usize];
    p_idx += 1;
    let storage_type = byte & 0xE0;

    if byte & 0x10 != 0 {
        p_idx += 1;
    }

    match storage_type {
        0x00 => (), // No additional bytes
        0x20 => p_idx += 1,
        0x40 => p_idx += 2,
        0x60 => p_idx += 4,
        0x80 => p_idx += 8,
        0xA0 | 0xC0 => {
            helper_AdvanceDataPos_2(&mut p_idx, &mut DataSize, p, plimit, storage_type as i32)?;
        }
        0xE0 => {
            helper_AdvanceDataPos_1(&mut p_idx, &mut DataSize, p, plimit)?;
        }
        _ => return None,
    }

    // Check if final position is beyond plimit
    if p.get(p_idx as usize).map_or(true, |&byte| &byte as *const u8 > plimit) {
        return None;
    }

    Some(p)
}
pub fn binn_save_header(item: &mut Binn_Struct) -> BOOL {
    if item.pbuf.is_none() {
        return 0;
    }

    // Get a mutable reference to the underlying byte buffer
    let p_buf = item.pbuf.as_mut().unwrap();
    let p = unsafe { &mut *(p_buf.as_mut() as *mut _ as *mut u8) };
    let mut p_idx = 9;

    let mut size = (item.used_size - 9) + 3;

    if item.count > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (item.count as u32) | 0x80000000u32;
        copy_be32(
            unsafe { &mut *((p as *mut u8).offset(p_idx as isize) as *mut _ as *mut u32) },
            &int32,
        );
    } else {
        p_idx -= 1;
        unsafe { *((p as *mut u8).offset(p_idx as isize)) = item.count as u8; }
    }

    if size > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (size as u32) | 0x80000000u32;
        copy_be32(
            unsafe { &mut *((p as *mut u8).offset(p_idx as isize) as *mut _ as *mut u32) },
            &int32,
        );
    } else {
        p_idx -= 1;
        unsafe { *((p as *mut u8).offset(p_idx as isize)) = size as u8; }
    }

    p_idx -= 1;
    unsafe { *((p as *mut u8).offset(p_idx as isize)) = item.type_ as u8; }

    item.ptr = Some(Box::new(unsafe { *((p as *mut u8).offset(p_idx as isize) as *const ()) }));
    item.size = size;
    item.dirty = 0;

    1
}
pub fn binn_ptr(ptr: Option<*mut u32>) -> Option<*mut u32> {
    let mut item: Option<&mut Binn_Struct> = None;
    let item_idx: u32 = 0;

    match binn_get_ptr_type(ptr.map(|p| p as *const u32)) {
        1 => {
            // SAFETY: We assume the pointer is valid when case is 1
            let item_ptr = unsafe { &mut *(ptr? as *mut Binn_Struct) };
            item = Some(item_ptr);
            
            if item.as_ref()?.writable != 0 && item.as_ref()?.dirty != 0 {
                binn_save_header(item.as_mut()?);
            }
            item.as_ref()?.ptr.as_ref().map(|p| Box::as_ref(p) as *const () as *mut u32)
        },
        2 => ptr,
        _ => None,
    }
}
pub fn binn_list_get_value(ptr: Option<&[u8]>, pos: i32, value: Option<&mut Binn_Struct>) -> BOOL {
    // Initialize variables with default values
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
    // Check for NULL pointers (Option::None in Rust)
    if ptr.is_none() || value.is_none() {
        return 0;
    }
    let ptr = ptr.unwrap();
    let value = value.unwrap();

    // Validate Binn header
    if !IsValidBinnHeader(
        Some(ptr),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    // Check type is list (0xE0)
    if type_ != 0xE0 {
        return 0;
    }

    // Check count is valid
    if count == 0 {
        return 0;
    }

    // Check position is within bounds
    if pos <= 0 || pos > count {
        return 0;
    }

    let adjusted_pos = (pos - 1) as usize;
    let base = ptr.as_ptr();
    let plimit = unsafe { base.add(size as usize) };

    // Advance to the desired position
    let mut current_pos = &ptr[header_size as usize..];
    for _ in 0..adjusted_pos {
        match AdvanceDataPos(current_pos, plimit) {
            Some(new_pos) => current_pos = new_pos,
            None => return 0,
        }

        // Check bounds
        if current_pos.is_empty() || current_pos.as_ptr() < base {
            return 0;
        }
    }

    GetValue(Some(current_pos), Some(value))
}
pub fn zero_value(pvalue: Option<&mut [u8]>, type_: i32) {
    let Some(pvalue) = pvalue else {
        return;
    };

    match binn_get_read_storage(type_) {
        0x00 => (), // No operation needed
        0x20 => {
            if pvalue.len() >= 1 {
                pvalue[0] = 0;
            }
        }
        0x40 => {
            if pvalue.len() >= 2 {
                let slice = &mut pvalue[..2];
                slice.copy_from_slice(&0i16.to_ne_bytes());
            }
        }
        0x60 => {
            if pvalue.len() >= 4 {
                let slice = &mut pvalue[..4];
                slice.copy_from_slice(&0i32.to_ne_bytes());
            }
        }
        0x80 => {
            if pvalue.len() >= 8 {
                let slice = &mut pvalue[..8];
                slice.copy_from_slice(&0u64.to_ne_bytes());
            }
        }
        0xA0 | 0xC0 | 0xE0 => {
            if pvalue.len() >= std::mem::size_of::<*const u8>() {
                let null_ptr = std::ptr::null::<u8>();
                let bytes = unsafe { std::mem::transmute::<*const u8, [u8; std::mem::size_of::<*const u8>()]>(null_ptr) };
                let slice = &mut pvalue[..std::mem::size_of::<*const u8>()];
                slice.copy_from_slice(&bytes);
            }
        }
        _ => (), // Unknown storage type, do nothing
    }
}
pub fn binn_list_get(
    ptr: Option<&[u8]>,
    pos: i32,
    type_: i32,
    mut pvalue: Option<&mut [u8]>,
    psize: Option<&mut i32>,
) -> BOOL {
    let storage_type = binn_get_read_storage(type_);
    
    // Check if storage_type is valid and pvalue is None when storage_type != 0
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    // Zero out the pvalue if it exists
    if let Some(pv) = pvalue.as_mut() {
        zero_value(Some(pv), type_);
    }

    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    if binn_list_get_value(ptr, pos, Some(&mut value)) == 0 {
        return 0;
    }

    // Convert the ptr to mutable slice if it exists
    let source_ptr = if let Some(ptr) = value.ptr {
        Some(unsafe { std::slice::from_raw_parts_mut(Box::into_raw(ptr) as *mut u8, value.size as usize) })
    } else {
        None
    };

    if copy_value(
        source_ptr,
        pvalue,
        value.type_,
        type_,
        storage_type as u8,
    ) == false {
        return 0;
    }

    if let Some(size_ptr) = psize {
        *size_ptr = value.size;
    }

    1
}
pub fn read_map_id(pp: &mut &[u8], plimit: usize) -> Option<i32> {
    let p = *pp;
    let mut p_idx = 0;
    
    if p_idx >= p.len() {
        *pp = &p[p.len()..];
        return None;
    }

    let c = p[p_idx];
    p_idx += 1;

    let extra_bytes = if c & 0x80 != 0 {
        let bytes = ((c & 0x60) >> 5) + 1;
        if p_idx + bytes as usize > p.len() || p_idx + bytes as usize > plimit {
            *pp = &p[p.len()..];
            return None;
        }
        bytes
    } else {
        0
    };

    let type_ = c & 0xE0;
    let mut sign = c & 0x10;
    let mut id;

    if (c & 0x80) == 0 {
        sign = c & 0x40;
        id = (c & 0x3F) as i32;
    } else {
        match type_ {
            0x80 => {
                if p_idx + 1 > p.len() {
                    *pp = &p[p.len()..];
                    return None;
                }
                id = ((c & 0x0F) as i32) << 8 | (p[p_idx] as i32);
                p_idx += 1;
            }
            0xA0 => {
                if p_idx + 2 > p.len() {
                    *pp = &p[p.len()..];
                    return None;
                }
                id = ((c & 0x0F) as i32) << 8 | (p[p_idx] as i32);
                p_idx += 1;
                id = (id << 8) | (p[p_idx] as i32);
                p_idx += 1;
            }
            0xC0 => {
                if p_idx + 3 > p.len() {
                    *pp = &p[p.len()..];
                    return None;
                }
                id = ((c & 0x0F) as i32) << 8 | (p[p_idx] as i32);
                p_idx += 1;
                id = (id << 8) | (p[p_idx] as i32);
                p_idx += 1;
                id = (id << 8) | (p[p_idx] as i32);
                p_idx += 1;
            }
            0xE0 => {
                if p_idx + 4 > p.len() {
                    *pp = &p[p.len()..];
                    return None;
                }
                let mut source = 0u32;
                copy_be32(&mut source, &u32::from_be_bytes([
                    p[p_idx], p[p_idx+1], p[p_idx+2], p[p_idx+3]
                ]));
                id = source as i32;
                p_idx += 4;
            }
            _ => {
                *pp = &p[p.len()..];
                return None;
            }
        }
    }

    if sign != 0 {
        id = -id;
    }

    *pp = &p[p_idx..];
    Some(id)
}
pub fn SearchForID(p: &[u8], header_size: usize, size: usize, numitems: usize, id: i32) -> Option<&[u8]> {
    let mut p_idx = 0;
    let base = p.as_ptr();
    let plimit = unsafe { p.as_ptr().add(size - 1) };
    p_idx += header_size;

    for _ in 0..numitems {
        let mut current_slice = &p[p_idx..];
        let int32 = read_map_id(&mut current_slice, plimit as usize);
        
        if current_slice.as_ptr() > plimit {
            break;
        }

        if let Some(found_id) = int32 {
            if found_id == id {
                return Some(p);
            }
        }

        if let Some(new_slice) = AdvanceDataPos(&p[p_idx..], plimit) {
            p_idx = new_slice.as_ptr() as usize - p.as_ptr() as usize;
        } else {
            break;
        }

        if p_idx == 0 || p[p_idx..].as_ptr() < base {
            break;
        }
    }

    Option::None
}
pub fn binn_map_get_value(ptr: Option<&[u8]>, id: i32, value: Option<&mut Binn_Struct>) -> BOOL {
    // Convert ptr to raw pointer for binn_ptr (unsafe required)
    let ptr_idx = match ptr {
        Some(p) => p.as_ptr() as *mut u32,
        None => std::ptr::null_mut(),
    };
    let ptr_idx = binn_ptr(Some(ptr_idx));

    // Check for NULL pointers (Option::None in Rust)
    if ptr.is_none() || value.is_none() {
        return 0;
    }

    let ptr = ptr.unwrap();
    let value = value.unwrap();

    // Declare variables to be filled by IsValidBinnHeader
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    if !IsValidBinnHeader(
        Some(ptr),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    // Check type (0xE1 is map type)
    if type_ != 0xE1 {
        return 0;
    }

    // Check if map is empty
    if count == 0 {
        return 0;
    }

    // Search for the ID in the map
    let p_slice = match SearchForID(ptr, header_size as usize, size as usize, count as usize, id) {
        Some(slice) => slice,
        None => return 0,
    };

    GetValue(Some(p_slice), Some(value))
}
pub fn binn_map_get(
    ptr: Option<&[u8]>,
    id: i32,
    type_: i32,
    mut pvalue: Option<&mut [u8]>,  // Added 'mut' here
    psize: Option<&mut i32>,
) -> BOOL {
    let storage_type = binn_get_read_storage(type_);
    
    // Check if storage_type is valid and pvalue is None when storage_type != 0
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    // Zero out the destination value if pvalue exists
    if let Some(pval) = pvalue.as_mut() {
        zero_value(Some(pval), type_);
    }

    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    // Get the value from the map
    if binn_map_get_value(ptr, id, Some(&mut value)) == 0 {
        return 0;
    }

    // Copy the value if pvalue exists
    if let Some(pval) = pvalue.as_mut() {
        // Convert the raw pointer to a mutable slice
        let source_ptr = value.ptr.map(|p| unsafe {
            let raw_ptr = Box::into_raw(p) as *mut u8;
            std::slice::from_raw_parts_mut(raw_ptr, value.size as usize)
        });
        if !copy_value(source_ptr, Some(pval), value.type_, type_, storage_type as u8) {
            return 0;
        }
    }

    // Set the size if psize exists
    if let Some(size) = psize {
        *size = value.size;
    }

    1
}
pub fn SearchForKey<'a>(
    p: &'a [u8],
    header_size: usize,
    size: usize,
    numitems: i32,
    key: &'a str,
) -> Option<&'a [u8]> {
    let mut p_idx = 0;
    let key_bytes = key.as_bytes();
    let keylen = key_bytes.len();

    // Calculate bounds
    let base_ptr = p.as_ptr();
    let plimit_ptr = unsafe { p.as_ptr().add(size - 1) };

    p_idx += header_size;

    for _ in 0..numitems {
        if p_idx >= p.len() {
            break;
        }

        let len = p[p_idx] as usize;
        p_idx += 1;

        if p_idx >= p.len() {
            break;
        }

        if len > 0 {
            // Compare the current slice with the key (case-insensitive)
            if p_idx + len <= p.len() {
                let current_slice = &p[p_idx..p_idx + len];
                if current_slice.len() == key_bytes.len() {
                    let equal = current_slice.iter().zip(key_bytes.iter()).all(|(&a, &b)| {
                        a.to_ascii_lowercase() == b.to_ascii_lowercase()
                    });
                    if equal {
                        return Some(&p[p_idx - 1..p_idx + len]); // Return including length byte
                    }
                }
            }
            p_idx += len;

            if p_idx >= p.len() {
                break;
            }
        } else if len == keylen {
            return Some(&p[p_idx - 1..p_idx]); // Return the length byte
        }

        // Advance position
        let remaining = &p[p_idx..];
        if let Some(new_p) = AdvanceDataPos(remaining, plimit_ptr) {
            p_idx = new_p.as_ptr() as usize - p.as_ptr() as usize;
        } else {
            break;
        }

        if p_idx == 0 || unsafe { p.as_ptr().add(p_idx) < base_ptr } {
            break;
        }
    }

    None
}
pub fn binn_object_get_value(
    ptr: Option<&[u8]>,
    key: Option<&str>,
    value: Option<&mut Binn_Struct>,
) -> BOOL {
    // Early return if any input is None (equivalent to NULL checks in C)
    if ptr.is_none() || key.is_none() || value.is_none() {
        return 0;
    }
    let ptr = ptr.unwrap();
    let key = key.unwrap();

    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Check valid header
    if !IsValidBinnHeader(
        Some(ptr),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    // Check type
    if type_ != 0xE2 {
        return 0;
    }

    // Check count
    if count == 0 {
        return 0;
    }

    // Search for key
    let p_slice = match SearchForKey(
        ptr,
        header_size as usize,
        size as usize,
        count,
        key,
    ) {
        Some(slice) => slice,
        None => return 0,
    };

    // Get value
    GetValue(Some(p_slice), value)
}
pub fn binn_object_get(
    ptr: Option<&[u8]>,
    key: Option<&str>,
    type_: i32,
    mut pvalue: Option<&mut [u8]>,
    psize: Option<&mut i32>,
) -> BOOL {
    let storage_type = binn_get_read_storage(type_);
    
    // Check if storage_type is valid and pvalue is None when storage_type != 0
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    // Zero out the pvalue if it exists
    if let Some(pv) = pvalue.as_mut() {
        zero_value(Some(pv), type_);
    }

    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    // Get the value from the object
    if binn_object_get_value(ptr, key, Some(&mut value)) == 0 {
        return 0;
    }

    // Copy the value if pvalue exists
    if let Some(pv) = pvalue.as_mut() {
        if !copy_value(
            None, // Changed from value.ptr.as_deref_mut() to None since ptr is Option<Box<()>> which can't be converted to Option<&mut [u8]>
            Some(pv),
            value.type_,
            type_,
            storage_type as u8,
        ) {
            return 0;
        }
    }

    // Update size if psize exists
    if let Some(size) = psize {
        *size = value.size;
    }

    1
}
pub fn binn_is_valid_ex(
    ptr: Option<*mut u8>,
    ptype: Option<&mut i32>,
    pcount: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> bool {
    // Initialize variables
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Get pointer from ptr
    let pbuf = match binn_ptr(ptr.map(|p| p as *mut u32)) {
        Some(p) => p as *mut u8,
        None => return false,
    };

    // Check if pointer is null
    if pbuf.is_null() {
        return false;
    }

    // Get size from psize if provided
    let mut size = match psize.as_ref() {
        Some(s) if **s > 0 => **s,
        _ => 0,
    };

    // Convert pbuf to slice for safe access
    let pbuf_slice = unsafe { std::slice::from_raw_parts(pbuf, size as usize) };

    // Validate header
    if !IsValidBinnHeader(
        Some(pbuf_slice),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return false;
    }

    // Validate size if provided
    if let Some(s) = psize.as_ref() {
        if **s > 0 && size != **s {
            return false;
        }
    }

    // Validate count if provided
    if let Some(c) = pcount.as_ref() {
        if **c > 0 && count != **c {
            return false;
        }
    }

    // Validate type if provided
    if let Some(t) = ptype.as_ref() {
        if **t != 0 && type_ != **t {
            return false;
        }
    }

    // Process data
    let mut p = &pbuf_slice[header_size as usize..];
    let base = pbuf_slice;
    let plimit = &pbuf_slice[size as usize..];

    for _ in 0..count {
        match type_ {
            0xE2 => {
                if p.is_empty() {
                    return false;
                }
                let len = p[0] as usize;
                if p.len() < 1 + len {
                    return false;
                }
                p = &p[1 + len..];
            }
            0xE1 => {
                if read_map_id(&mut p, plimit.as_ptr() as usize).is_none() {
                    return false;
                }
            }
            _ => (),
        }

        if let Some(new_p) = AdvanceDataPos(p, plimit.as_ptr()) {
            p = new_p;
        } else {
            return false;
        }

        if p.is_empty() || p.as_ptr() < base.as_ptr() {
            return false;
        }
    }

    // Update output parameters if needed
    if let Some(t) = ptype {
        if *t == 0 {
            *t = type_;
        }
    }
    if let Some(c) = pcount {
        if *c == 0 {
            *c = count;
        }
    }
    if let Some(s) = psize {
        if *s == 0 {
            *s = size;
        }
    }

    true
}
pub fn atoi64(str: Option<&str>) -> Option<int64> {
    // Check for None (equivalent to NULL check in C)
    let str = str?;

    let mut str_idx = 0;
    let mut retval: int64;
    let mut is_negative = false;

    // Check for negative sign
    if let Some(c) = str.chars().nth(str_idx) {
        if c == '-' {
            is_negative = true;
            str_idx += 1;
        }
    }

    retval = 0;

    // Iterate through remaining characters
    for c in str.chars().skip(str_idx) {
        if !c.is_ascii_digit() {
            return Option::None; // Invalid character encountered
        }
        retval = (10 * retval) + (c.to_digit(10).unwrap() as int64);
    }

    if is_negative {
        retval *= -1;
    }

    Some(retval)
}
pub fn binn_get_write_storage(type_: i32) -> i32 {
    match type_ {
        0xA6 | 0xA7 => 0xA0,
        0x80061 => 0x00,
        _ => {
            let mut storage_type = 0;
            binn_get_type_info(type_, Some(&mut storage_type), None);
            storage_type
        }
    }
}
pub fn binn_is_container(item: Binn) -> BOOL {
    match item {
        None => 0,  // Return 0 if item is None (equivalent to NULL check in C)
        Some(binn) => match binn.type_ {
            0xE0 | 0xE1 | 0xE2 => 1,  // Return 1 for container types
            _ => 0,                   // Return 0 for all other types
        }
    }
}
pub fn binn_create(item: &mut Option<Box<Binn_Struct>>, type_: i32, size: i32, pointer: Option<&mut [u8]>) -> BOOL {
    let mut retval = 0;

    // Check valid type
    match type_ {
        0xE0 | 0xE1 | 0xE2 => (),
        _ => return retval,
    }

    // Check valid parameters
    if item.is_none() || size < 0 {
        return retval;
    }

    let item = item.as_mut().unwrap();

    // Handle size validation
    if size < 3 {
        if pointer.is_some() {
            return retval;
        } else {
            // size remains 0 in this case
        }
    }

    // Initialize the struct (equivalent to memset)
    *item = Box::new(Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    });

    if let Some(ptr) = pointer {
        item.pre_allocated = 1;
        unsafe {
            item.pbuf = Some(Box::from_raw(ptr.as_ptr() as *mut ()));
        }
        item.alloc_size = size;
    } else {
        item.pre_allocated = 0;
        let actual_size = if size == 0 { 256 } else { size };
        
        if let Some(alloc_ptr) = binn_malloc(actual_size) {
            unsafe {
                item.pbuf = Some(Box::from_raw(alloc_ptr as *mut ()));
            }
            item.alloc_size = actual_size;
        } else {
            return retval;
        }
    }

    item.header = 0x1F22B11F;
    item.writable = 1;
    item.used_size = 9;
    item.type_ = type_;
    item.dirty = 1;
    retval = 1;

    retval
}
pub fn binn_new(type_: i32, size: i32, pointer: Option<&mut [u8]>) -> Option<Box<Binn_Struct>> {
    // Allocate memory for the binn struct
    let item_ptr = match binn_malloc(std::mem::size_of::<Binn_Struct>() as i32) {
        Some(ptr) if !ptr.is_null() => ptr as *mut Binn_Struct,
        _ => return None,
    };

    // Create a Box from the raw pointer
    let mut item = unsafe { Box::from_raw(item_ptr) };
    
    // Initialize the struct
    if binn_create(&mut Some(Box::new(*item.clone())), type_, size, pointer) == 0 {
        // If creation fails, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
        return None;
    }

    item.allocated = 1;
    Some(item)
}
pub fn binn_list() -> Option<Box<Binn_Struct>> {
    binn_new(0xE0, 0, None)
}
pub fn binn_map() -> Option<Box<Binn_Struct>> {
    binn_new(0xE1, 0, None)
}

pub fn binn_object() -> Option<Box<Binn_Struct>> {
    binn_new(0xE2, 0, None)
}
pub fn binn_is_valid(
    ptr: Option<*mut u8>,
    mut ptype: Option<&mut i32>,
    mut pcount: Option<&mut i32>,
    mut psize: Option<&mut i32>,
) -> bool {
    if let Some(ptype_ref) = ptype.as_mut() {
        **ptype_ref = 0;
    }
    if let Some(pcount_ref) = pcount.as_mut() {
        **pcount_ref = 0;
    }
    if let Some(psize_ref) = psize.as_mut() {
        **psize_ref = 0;
    }
    binn_is_valid_ex(ptr, ptype, pcount, psize)
}
pub fn binn_list_int8(list: Option<&[u8]>, pos: i32) -> Option<i8> {
    let mut value: i8 = 0;
    let success = binn_list_get(
        list,
        pos,
        0x21,
        Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut i8 as *mut u8, 1) }),
        None,
    );
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_list_int16(list: Option<&[u8]>, pos: i32) -> i16 {
    let mut value: i16 = 0;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut i16 as *mut u8,
            std::mem::size_of::<i16>()
        )
    };
    binn_list_get(list, pos, 0x41, Some(value_slice), None);
    value
}
pub fn binn_list_int32(list: Option<&[u8]>, pos: i32) -> i32 {
    let mut value: i32 = 0;
    binn_list_get(list, pos, 0x61, Some(&mut value.to_ne_bytes()), Option::None);
    value
}
pub fn binn_list_uint8(list: Option<&[u8]>, pos: i32) -> Option<u8> {
    let mut value: u8 = 0;
    let success = binn_list_get(
        list,
        pos,
        0x20,
        Some(&mut [value]), // Pass a mutable slice containing the value
        None,
    );
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_list_uint16(list: Option<&[u8]>, pos: i32) -> Option<u16> {
    let mut value: u16 = 0;
    let success = binn_list_get(
        list,
        pos,
        0x40,
        Some(unsafe {
            std::slice::from_raw_parts_mut(
                &mut value as *mut u16 as *mut u8,
                std::mem::size_of::<u16>(),
            )
        }),
        None,
    );
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_list_uint32(list: Option<&[u8]>, pos: i32) -> u32 {
    let mut value = 0u32;
    let value_bytes = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut u32 as *mut u8,
            std::mem::size_of::<u32>()
        )
    };
    
    binn_list_get(
        list,
        pos,
        0x60,
        Some(value_bytes),
        None
    );
    
    value
}
pub fn binn_list_float(list: Option<&[u8]>, pos: i32) -> f32 {
    let mut value = 0.0f32;
    // SAFETY: We're passing a valid mutable reference to a f32 (which is equivalent to &mut [u8] of size 4)
    // and we know binn_list_get will properly handle the Option-wrapped parameters.
    let value_bytes = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut f32 as *mut u8, std::mem::size_of::<f32>())
    };
    binn_list_get(list, pos, 0x62, Some(value_bytes), None);
    value
}
pub fn binn_list_double(list: Option<&[u8]>, pos: i32) -> f64 {
    let mut value = 0.0;
    let value_ptr = &mut value as *mut f64;
    unsafe {
        let value_slice = std::slice::from_raw_parts_mut(value_ptr as *mut u8, std::mem::size_of::<f64>());
        binn_list_get(list, pos, 0x82, Some(value_slice), None);
    }
    value
}
pub fn binn_list_null(list: Option<&[u8]>, pos: i32) -> BOOL {
    binn_list_get(list, pos, 0x00, None, None)
}
pub fn binn_list_str(list: Option<&[u8]>, pos: i32) -> Option<Vec<u8>> {
    let mut value: Option<Vec<u8>> = None;
    // Create a mutable reference to value that can be passed to binn_list_get
    let pvalue = value.as_mut().map(|v| v.as_mut_slice());
    
    // Call binn_list_get with the appropriate parameters
    let success = binn_list_get(list, pos, 0xA0, pvalue, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_list_blob<'a>(
    list: Option<&'a [u8]>,
    pos: i32,
    psize: Option<&'a mut i32>,
) -> Option<&'a [u8]> {
    let mut value: *const u8 = std::ptr::null();
    let success = binn_list_get(
        list,
        pos,
        0xC0,
        Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut *const u8 as *mut u8, 1) }),
        psize,
    );
    if success != 0 && !value.is_null() {
        unsafe { Some(std::slice::from_raw_parts(value, 0)) }
    } else {
        None
    }
}
pub fn binn_list_list(list: Option<&[u8]>, pos: i32) -> Option<&[u8]> {
    let mut value: Option<&[u8]> = None;
    let mut value_ptr: Option<&mut &[u8]> = None;
    if let Some(ref mut inner) = value {
        value_ptr = Some(inner);
    }
    let mut temp_value: Option<&mut [u8]> = None;
    if let Some(v) = value_ptr {
        unsafe {
            let slice = std::slice::from_raw_parts_mut((*v).as_ptr() as *mut u8, (*v).len());
            temp_value = Some(slice);
        }
    }
    binn_list_get(list, pos, 0xE0, temp_value, None);
    value
}
pub fn binn_list_map(list: Option<&[u8]>, pos: i32) -> Option<&[u8]> {
    let mut value: Option<&mut [u8]> = None;
    let success = binn_list_get(list, pos, 0xE1, value.as_deref_mut(), None);
    
    if success != 0 {
        value.map(|v| &*v)
    } else {
        None
    }
}
pub fn binn_list_object(list: Option<&[u8]>, pos: i32) -> Option<&[u8]> {
    let mut value: Option<&mut [u8]> = None;
    let success = binn_list_get(list, pos, 0xE2, value.as_deref_mut(), None) != 0;
    
    if success {
        value.map(|v| &*v)
    } else {
        None
    }
}
pub fn binn_map_int8(map: Option<&[u8]>, id: i32) -> Option<i8> {
    let mut value: i8 = 0;
    let success = binn_map_get(
        map,
        id,
        0x21,
        Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut i8 as *mut u8, 1) }),
        None,
    );
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_map_int16(map: Option<&[u8]>, id: i32) -> i16 {
    let mut value: i16 = 0;
    // Safe conversion: i16 is 2 bytes, so we create a mutable slice of exactly 2 bytes
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut i16 as *mut u8,
            std::mem::size_of::<i16>()
        )
    };
    
    // Call binn_map_get with the appropriate parameters
    binn_map_get(map, id, 0x41, Some(value_slice), None);
    
    value
}
pub fn binn_map_int32(map: Option<&[u8]>, id: i32) -> i32 {
    let mut value: i32 = 0;
    binn_map_get(map, id, 0x61, Some(&mut value.to_ne_bytes()), None);
    value
}
pub fn binn_map_uint8(map: Option<&[u8]>, id: i32) -> Option<u8> {
    let mut value = 0u8;
    let success = binn_map_get(
        map,
        id,
        0x20,
        Some(&mut [value]),  // Pass as mutable slice
        None,
    );

    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_map_uint16(map: Option<&[u8]>, id: i32) -> u16 {
    let mut value: u16 = 0;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut u16 as *mut u8, std::mem::size_of::<u16>())
    };
    binn_map_get(map, id, 0x40, Some(value_slice), None);
    value
}
pub fn binn_map_uint32(map: Option<&[u8]>, id: i32) -> u32 {
    let mut value = 0u32;
    let value_bytes = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut u32 as *mut u8,
            std::mem::size_of::<u32>()
        )
    };
    
    binn_map_get(
        map,
        id,
        0x60,
        Some(value_bytes),
        None
    );
    
    value
}
pub fn binn_map_float(map: Option<&[u8]>, id: i32) -> f32 {
    let mut value: f32 = 0.0;
    let _ = binn_map_get(map, id, 0x62, Some(unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut f32 as *mut u8, std::mem::size_of::<f32>())
    }), None);
    value
}
pub fn binn_map_double(map: Option<&[u8]>, id: i32) -> f64 {
    let mut value = 0.0;
    // Safe conversion: f64 is 8 bytes, same as double in C
    let value_bytes = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut f64 as *mut u8,
            std::mem::size_of::<f64>()
        )
    };
    
    // We need unsafe here because we're working with raw bytes
    unsafe {
        binn_map_get(
            map,
            id,
            0x82,  // Assuming 0x82 is the type code for double
            Some(value_bytes),
            None,
        );
    }
    
    value
}
pub fn binn_map_null(map: Option<&[u8]>, id: i32) -> BOOL {
    binn_map_get(map, id, 0x00, None, None)
}
pub fn binn_map_str(map: Option<&[u8]>, id: i32) -> Option<&[u8]> {
    let mut value: Option<&[u8]> = None;
    let mut value_slice: &mut [u8] = &mut [];
    binn_map_get(map, id, 0xA0, Some(&mut value_slice), None);
    value
}
pub fn binn_map_blob<'a>(
    map: Option<&'a [u8]>,
    id: i32,
    psize: Option<&'a mut i32>,
) -> Option<&'a [u8]> {
    let mut value_ptr: *const u8 = std::ptr::null();
    let value_ptr_ptr = &mut value_ptr as *mut *const u8;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(value_ptr_ptr as *mut u8, std::mem::size_of::<*const u8>())
    };
    let mut size_val: i32 = 0;
    let success = binn_map_get(map, id, 0xC0, Some(value_slice), Some(&mut size_val));
    
    if let Some(ptr) = psize {
        *ptr = size_val;
    }
    
    if success != 0 && !value_ptr.is_null() {
        Some(unsafe { std::slice::from_raw_parts(value_ptr, size_val as usize) })
    } else {
        None
    }
}
pub fn binn_map_list(map: Option<&[u8]>, id: i32) -> Option<&[u8]> {
    let mut value: Option<&[u8]> = None;
    let mut raw_value: Option<&mut [u8]> = None;
    binn_map_get(map, id, 0xE0, raw_value.as_mut().map(|v| &mut **v), None);
    value = raw_value.map(|v| v as &[u8]);
    value
}
pub fn binn_map_map(map: Option<&[u8]>, id: i32) -> Option<Vec<u8>> {
    let mut size = 0;
    if binn_map_get(map, id, 0xE1, None, Some(&mut size)) == 0 {
        return None;
    }
    let mut buffer = vec![0u8; size as usize];
    let mut length = size;
    if binn_map_get(map, id, 0xE1, Some(&mut buffer), Some(&mut length)) == 0 {
        None
    } else {
        buffer.truncate(length as usize);
        Some(buffer)
    }
}
pub fn binn_map_object(map: Option<&[u8]>, id: i32) -> Option<Vec<u8>> {
    let mut size = 0;
    // First call to get required size
    if binn_map_get(map, id, 0xE2, None, Some(&mut size)) == 0 || size <= 0 {
        return None;
    }

    let mut buffer = vec![0u8; size as usize];
    let mut actual_size = size;
    // Second call to retrieve data into buffer
    if binn_map_get(map, id, 0xE2, Some(&mut buffer), Some(&mut actual_size)) == 0 {
        return None;
    }

    // Adjust buffer to actual size if needed
    if actual_size < size {
        buffer.truncate(actual_size as usize);
    }

    Some(buffer)
}
pub fn binn_object_int8(obj: Option<&[u8]>, key: Option<&str>) -> Option<i8> {
    let mut value: i8 = 0;
    let success = binn_object_get(
        obj,
        key,
        0x21,
        Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut i8 as *mut u8, 1) }),
        None,
    );
    
    if success != 0 {  // Compare with 0 (FALSE) since BOOL is likely i32
        Some(value)
    } else {
        Option::None
    }
}
pub fn binn_object_int16(obj: Option<&[u8]>, key: Option<&str>) -> i16 {
    let mut value: i16 = 0;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(
            &mut value as *mut i16 as *mut u8,
            std::mem::size_of::<i16>(),
        )
    };
    binn_object_get(obj, key, 0x41, Some(value_slice), None);
    value
}
pub fn binn_object_int32(obj: Option<&[u8]>, key: Option<&str>) -> i32 {
    let mut value: i32 = 0;
    binn_object_get(obj, key, 0x61, Some(&mut value.to_ne_bytes()), None);
    value
}
pub fn binn_object_uint8(obj: Option<&[u8]>, key: Option<&str>) -> u8 {
    let mut value: u8 = 0;
    binn_object_get(obj, key, 0x20, Some(&mut [value]), None);
    value
}
pub fn binn_object_uint16(obj: Option<&[u8]>, key: Option<&str>) -> u16 {
    let mut value: u16 = 0;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut u16 as *mut u8, std::mem::size_of::<u16>())
    };
    binn_object_get(obj, key, 0x40, Some(value_slice), None);
    value
}
pub fn binn_object_uint32(obj: Option<&[u8]>, key: Option<&str>) -> u32 {
    let mut value = 0u32;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut u32 as *mut u8, std::mem::size_of::<u32>())
    };
    
    binn_object_get(obj, key, 0x60, Some(value_slice), None);
    value
}
pub fn binn_object_float(obj: Option<&[u8]>, key: Option<&str>) -> f32 {
    let mut value_bytes = 0.0f32.to_ne_bytes();
    
    // Call binn_object_get with the appropriate parameters
    // 0x62 is the type code for float in Binn
    let _ = binn_object_get(
        obj,
        key,
        0x62,
        Some(&mut value_bytes),
        Option::None,
    );

    // Convert the bytes back to float
    f32::from_ne_bytes(value_bytes)
}
pub fn binn_object_double(obj: Option<&[u8]>, key: Option<&str>) -> f64 {
    let mut value = 0.0;
    // 0x82 is the BINN type for double (64-bit floating point)
    binn_object_get(obj, key, 0x82, Some(unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut f64 as *mut u8, std::mem::size_of::<f64>())
    }), None);
    value
}
pub fn binn_object_null(obj: Option<&[u8]>, key: Option<&str>) -> BOOL {
    binn_object_get(obj, key, 0x00, None, None)
}
pub fn binn_object_str(obj: Option<&[u8]>, key: Option<&str>) -> Option<Vec<u8>> {
    let mut value: Option<Vec<u8>> = None;
    let mut value_slice: Option<&mut [u8]> = None;
    
    // Convert the Option<Vec<u8>> to Option<&mut [u8]> for binn_object_get
    if let Some(ref mut v) = value {
        value_slice = Some(v.as_mut_slice());
    }

    let success = binn_object_get(obj, key, 0xA0, value_slice, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_object_blob<'a>(
    obj: Option<&'a [u8]>,
    key: Option<&'a str>,
    psize: Option<&'a mut i32>,
) -> Option<&'a [u8]> {
    let mut value: Option<&'a mut [u8]> = None;
    let success = binn_object_get(
        obj,
        key,
        0xC0,
        value.as_mut().map(|v| v.as_mut()),
        psize,
    );
    
    if success != 0 {
        value.map(|v| v as &[u8])
    } else {
        Option::None
    }
}
pub fn binn_object_list(obj: Option<&[u8]>, key: Option<&str>) -> Option<Vec<u8>> {
    let mut size: i32 = 0;
    if binn_object_get(obj, key, 0xE0, None, Some(&mut size)) != 0 && size >= 0 {
        let mut buffer = vec![0u8; size as usize];
        if binn_object_get(obj, key, 0xE0, Some(&mut buffer), Some(&mut size)) != 0 && size >= 0 {
            buffer.truncate(size as usize);
            Some(buffer)
        } else {
            None
        }
    } else {
        None
    }
}
pub fn binn_object_map<'a>(obj: Option<&'a [u8]>, key: Option<&str>) -> Option<&'a [u8]> {
    let mut value: Option<&'a [u8]> = None;
    let mut value_slice: Option<&mut [u8]> = None;
    let success = binn_object_get(obj, key, 0xE1, value_slice, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_object_object<'a>(obj: Option<&'a [u8]>, key: Option<&str>) -> Option<&'a [u8]> {
    let mut value: Option<&'a [u8]> = None;
    let success = binn_object_get(
        obj,
        key,
        0xE2,
        None,
        None,
    );
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_buf_type(pbuf: Option<&[u8]>) -> i32 {
    let mut type_ = 0; // Using type_ to avoid Rust keyword conflict
    if !IsValidBinnHeader(pbuf, Some(&mut type_), None, None, None) {
        return 0;
    }
    type_
}
pub fn binn_buf_count(pbuf: Option<&[u8]>) -> i32 {
    let mut nitems = 0;
    if !IsValidBinnHeader(pbuf, None, Some(&mut nitems), None, None) {
        return 0;
    }
    nitems
}
pub fn binn_buf_size(pbuf: Option<&[u8]>) -> i32 {
    let mut size = 0;
    if !IsValidBinnHeader(pbuf, None, None, Some(&mut size), None) {
        return 0;
    }
    size
}
pub fn is_integer(p: Option<&str>) -> BOOL {
    // Check for NULL equivalent (None)
    let p = match p {
        Some(s) => s,
        None => return 0,
    };

    // Convert to bytes for character-by-character processing
    let bytes = p.as_bytes();
    let mut p_idx = 0;

    // Check empty string case
    if bytes.is_empty() {
        return 0;
    }

    // Handle optional minus sign
    if bytes[p_idx] == b'-' {
        p_idx += 1;
        // Check if string is just "-"
        if p_idx >= bytes.len() {
            return 0;
        }
    }

    let mut retval = 1;
    // Check remaining characters are all digits
    for &c in &bytes[p_idx..] {
        if !c.is_ascii_digit() {
            retval = 0;
            break;
        }
    }

    retval
}
pub fn is_float(p: Option<&str>) -> BOOL {
    // Check for None (equivalent to NULL check in C)
    let p = match p {
        Some(s) => s,
        None => return 0,
    };

    let mut p_idx = 0;
    let mut retval: BOOL;
    let mut number_found = 0;

    // Check for empty string (equivalent to checking for '\0' at start)
    if p.is_empty() {
        return 0;
    }

    // Handle optional minus sign
    let chars: Vec<char> = p.chars().collect();
    if chars[p_idx] == '-' {
        p_idx += 1;
        // Check if string ends after minus sign
        if p_idx >= chars.len() {
            return 0;
        }
    }

    retval = 1;

    // Iterate through remaining characters
    while p_idx < chars.len() {
        let c = chars[p_idx];
        if c == '.' || c == ',' {
            if number_found == 0 {
                retval = 0;
            }
        } else if c.is_ascii_digit() {
            number_found = 1;
        } else {
            return 0;
        }
        p_idx += 1;
    }

    retval
}
pub fn CheckAllocation(item: &mut Binn_Struct, add_size: i32) -> BOOL {
    if (item.used_size + add_size) > item.alloc_size {
        if item.pre_allocated != 0 {
            return 0;
        }
        let alloc_size = CalcAllocation(item.used_size + add_size, item.alloc_size);
        let realloc_fn = REALLOC_FN.lock().unwrap();
        if let Some(f) = *realloc_fn {
            // Convert the current buffer to the expected type
            let current_buf = if let Some(b) = item.pbuf.take() {
                let ptr = Box::into_raw(b);
                unsafe {
                    Some(Box::from_raw(std::slice::from_raw_parts_mut(ptr as *mut u8, item.alloc_size as usize)))
                }
            } else {
                None
            };
            let new_buf = f(current_buf, alloc_size as usize);
            if new_buf.is_none() {
                return 0;
            }
            // Convert back to the stored type
            item.pbuf = new_buf.map(|b| {
                let ptr = Box::into_raw(b);
                unsafe {
                    Box::from_raw(ptr as *mut ())
                }
            });
            item.alloc_size = alloc_size;
        } else {
            return 0;
        }
    }
    1
}
pub fn compress_int(pstorage_type: &mut i32, ptype: &mut i32, psource: *mut ()) -> *mut () {
    let storage_type = *pstorage_type;
    if storage_type == 0x20 {
        return psource;
    }

    let type_ = *ptype;
    let mut type2 = 0;
    let mut vint: int64 = 0;
    let mut vuint: uint64 = 0;  // Initialize with default value

    match type_ {
        0x81 => {
            vint = unsafe { ptr::read(psource as *const int64) };
            // fall through to loc_signed
        }
        0x61 => {
            vint = unsafe { ptr::read(psource as *const i32) } as int64;
            // fall through to loc_signed
        }
        0x41 => {
            vint = unsafe { ptr::read(psource as *const i16) } as int64;
            // fall through to loc_signed
        }
        0x80 => {
            vuint = unsafe { ptr::read(psource as *const uint64) };
            // fall through to loc_positive
        }
        0x60 => {
            vuint = unsafe { ptr::read(psource as *const u32) } as uint64;
            // fall through to loc_positive
        }
        0x40 => {
            vuint = unsafe { ptr::read(psource as *const u16) } as uint64;
            // fall through to loc_positive
        }
        _ => return psource,
    }

    // loc_signed
    if type_ == 0x81 || type_ == 0x61 || type_ == 0x41 {
        if vint >= 0 {
            vuint = vint as uint64;
            // fall through to loc_positive
        } else {
            if vint >= i8::MIN as int64 {
                type2 = 0x21;
            } else if vint >= i16::MIN as int64 {
                type2 = 0x41;
            } else if vint >= i32::MIN as int64 {
                type2 = 0x61;
            }
            // fall through to loc_exit
            return psource;
        }
    }

    // loc_positive
    if type_ == 0x80 || type_ == 0x60 || type_ == 0x40 || (vint >= 0 && (type_ == 0x81 || type_ == 0x61 || type_ == 0x41)) {
        if vuint <= u8::MAX as uint64 {
            type2 = 0x20;
        } else if vuint <= u16::MAX as uint64 {
            type2 = 0x40;
        } else if vuint <= u32::MAX as uint64 {
            type2 = 0x60;
        }
    }

    // loc_exit
    let pvalue = psource as *mut ();

    if type2 != 0 && type2 != type_ {
        *ptype = type2;
        let storage_type2 = binn_get_write_storage(type2);
        *pstorage_type = storage_type2;
    }

    pvalue
}
pub fn helper_AddValue_1(
    size_ref: &mut i32,
    int32_ref: &mut i32,
    p_idx_ref: &mut u32,
    item: &mut Binn_Struct,
    pvalue: &[u8],
    storage_type: i32,
    p: &mut [u8],
) {
    let mut size = *size_ref;
    let mut int32 = *int32_ref;
    let mut p_idx = *p_idx_ref;

    if size > 127 {
        int32 = (size as u32 | 0x80000000) as i32;
        copy_be32(
            unsafe { &mut *(p.as_mut_ptr() as *mut u32) },
            &(int32 as u32),
        );
        p_idx += 4;
        item.used_size += 4;
    } else {
        p[0] = size as u8;
        p_idx += 1;
        item.used_size += 1;
    }

    p[..size as usize].copy_from_slice(&pvalue[..size as usize]);

    if storage_type == 0xA0 {
        p_idx += size as u32;
        p[size as usize] = 0;
        size += 1;
    }

    item.used_size += size;
    
    *size_ref = size;
    *int32_ref = int32;
    *p_idx_ref = p_idx;
}
pub fn AddValue(item: &mut Binn_Struct, mut type_: i32, pvalue: Option<&[u8]>, mut size: i32) -> BOOL {
    let mut pvalue_idx = 0;
    let mut int32 = 0;
    let mut ArgSize;
    let mut storage_type = 0;
    let mut extra_type = 0;
    
    binn_get_type_info(type_, Some(&mut storage_type), Some(&mut extra_type));
    
    if pvalue.is_none() {
        match storage_type {
            0x00 => {}
            0xC0 | 0xA0 => {
                if size == 0 {
                    // Do nothing
                } else {
                    return 0;
                }
            }
            _ => return 0,
        }
    }

    if (type_family(type_) == 0xf2) && (item.disable_int_compression == 0) {
        let mut st = storage_type;
        let mut ty = type_;
        pvalue_idx = compress_int(&mut st, &mut ty, pvalue_idx as *mut ()) as usize;
        storage_type = st;
        type_ = ty;
    }

    ArgSize = match storage_type {
        0x00 => 0,
        0x20 => 1,
        0x40 => 2,
        0x60 => 4,
        0x80 => 8,
        0xC0 => {
            if size < 0 {
                return 0;
            }
            size + 4
        }
        0xA0 => {
            if size < 0 {
                return 0;
            }
            let actual_size = if size == 0 {
                strlen2(pvalue.and_then(|pv| std::str::from_utf8(pv).ok()))
            } else {
                size as usize
            };
            actual_size as i32 + 5
        }
        0xE0 => {
            if size <= 0 {
                return 0;
            }
            size
        }
        _ => return 0,
    };

    ArgSize += 2;
    if CheckAllocation(item, ArgSize) == 0 {
        return 0;
    }

    let p = item.pbuf.as_mut().unwrap().as_ref() as *const () as *mut u8;
    let mut p_idx = item.used_size as usize;

    if storage_type != 0xE0 {
        if type_ > 255 {
            let type16 = type_ as u16;
            copy_be16(unsafe { &mut *(p.add(p_idx) as *mut u16) }, &type16);
            p_idx += 2;
            item.used_size += 2;
        } else {
            unsafe { *p.add(p_idx) = type_ as u8 };
            p_idx += 1;
            item.used_size += 1;
        }
    }

    match storage_type {
        0x00 => {}
        0x20 => {
            if let Some(pv) = pvalue {
                unsafe { *p.add(p_idx) = pv[0] };
                item.used_size += 1;
            }
        }
        0x40 => {
            if let Some(pv) = pvalue {
                let val = unsafe { *(pv.as_ptr() as *const u16) };
                copy_be16(unsafe { &mut *(p.add(p_idx) as *mut u16) }, &val);
                item.used_size += 2;
            }
        }
        0x60 => {
            if let Some(pv) = pvalue {
                let val = unsafe { *(pv.as_ptr() as *const u32) };
                copy_be32(unsafe { &mut *(p.add(p_idx) as *mut u32) }, &val);
                item.used_size += 4;
            }
        }
        0x80 => {
            if let Some(pv) = pvalue {
                let val = unsafe { *(pv.as_ptr() as *const u64) };
                copy_be64(unsafe { &mut *(p.add(p_idx) as *mut u64) }, &val);
                item.used_size += 8;
            }
        }
        0xC0 | 0xA0 => {
            if let Some(pv) = pvalue {
                helper_AddValue_1(
                    &mut size,
                    &mut int32,
                    &mut (p_idx as u32),
                    item,
                    pv,
                    storage_type,
                    unsafe { std::slice::from_raw_parts_mut(p, item.alloc_size as usize) },
                );
            }
        }
        0xE0 => {
            if let Some(pv) = pvalue {
                unsafe {
                    std::ptr::copy_nonoverlapping(pv.as_ptr(), p.add(p_idx), size as usize);
                }
                item.used_size += size;
            }
        }
        _ => return 0,
    }

    item.dirty = 1;
    1
}
pub fn binn_list_add_raw(item: Binn, type_: i32, pvalue: Option<&[u8]>, size: i32) -> BOOL {
    // Check if item is None or doesn't meet conditions (equivalent to NULL/0 checks in C)
    let mut item = match item {
        Some(item) => item,
        None => return 0,
    };

    // Check conditions from line 3
    if item.type_ != 0xE0 || item.writable == 0 {
        return 0;
    }

    // Call AddValue and check its return value
    if AddValue(&mut item, type_, pvalue, size) == 0 {
        return 0;
    }

    // Increment count and return success
    item.count += 1;
    1
}
pub fn binn_list_add(list: Binn, type_: i32, pvalue: Option<&mut [u8]>, size: i32) -> BOOL {
    let mut type_ = type_;
    let mut pvalue = pvalue;
    let mut size = size;
    
    if !GetWriteConvertedData(&mut type_, &mut pvalue, &mut size) {
        return 0;
    }
    binn_list_add_raw(list, type_, pvalue.as_deref(), size)
}
pub fn binn_map_set_raw(
    item: Option<&mut Binn_Struct>,
    id: i32,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    // Check for NULL item or invalid type/writable status
    let item = match item {
        Some(item) if item.type_ == 0xE1 && item.writable != 0 => item,
        _ => return 0,
    };

    // Search for ID
    let pbuf_slice = unsafe {
        std::slice::from_raw_parts(
            item.pbuf.as_ref().unwrap().as_ref() as *const _ as *const u8,
            item.used_size as usize,
        )
    };
    if SearchForID(pbuf_slice, 9, item.used_size as usize, item.count as usize, id).is_some() {
        return 0;
    }

    // Check allocation
    if CheckAllocation(item, 5) == 0 {
        return 0;
    }

    let base = item.used_size;
    let mut p_idx = base;
    let sign = id < 0;
    let mut id = if sign { -id } else { id };

    // Get mutable raw pointer to buffer
    let buf_ptr = item.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8;

    // Write ID with appropriate encoding
    if id <= 0x3F {
        unsafe {
            *buf_ptr.add(p_idx as usize) = (sign as u8) << 6 | (id as u8);
        }
        p_idx += 1;
    } else if id <= 0xFFF {
        unsafe {
            *buf_ptr.add(p_idx as usize) = 0x80 | ((sign as u8) << 4) | ((id >> 8) as u8 & 0xF);
            *buf_ptr.add((p_idx + 1) as usize) = (id & 0xFF) as u8;
        }
        p_idx += 2;
    } else if id <= 0xFFFFF {
        unsafe {
            *buf_ptr.add(p_idx as usize) = 0xA0 | ((sign as u8) << 4) | ((id >> 16) as u8 & 0xF);
            *buf_ptr.add((p_idx + 1) as usize) = ((id >> 8) & 0xFF) as u8;
            *buf_ptr.add((p_idx + 2) as usize) = (id & 0xFF) as u8;
        }
        p_idx += 3;
    } else if id <= 0xFFFFFFF {
        unsafe {
            *buf_ptr.add(p_idx as usize) = 0xC0 | ((sign as u8) << 4) | ((id >> 24) as u8 & 0xF);
            *buf_ptr.add((p_idx + 1) as usize) = ((id >> 16) & 0xFF) as u8;
            *buf_ptr.add((p_idx + 2) as usize) = ((id >> 8) & 0xFF) as u8;
            *buf_ptr.add((p_idx + 3) as usize) = (id & 0xFF) as u8;
        }
        p_idx += 4;
    } else {
        unsafe {
            *buf_ptr.add(p_idx as usize) = 0xE0;
            if sign {
                id = -id;
            }
            let dest = (buf_ptr as *mut u32).add((p_idx + 1) as usize);
            copy_be32(&mut *dest, &(id as u32));
        }
        p_idx += 5;
    }

    let id_size = p_idx - base;
    item.used_size += id_size;

    if AddValue(item, type_, pvalue, size) == 0 {
        item.used_size -= id_size;
        return 0;
    }

    item.count += 1;
    1
}
pub fn binn_map_set(
    map: Option<&mut Binn_Struct>,
    id: i32,
    type_: i32,
    pvalue: Option<&mut [u8]>,
    size: i32,
) -> BOOL {
    let mut type_mut = type_;
    let mut pvalue_mut = pvalue;
    let mut size_mut = size;
    
    if !GetWriteConvertedData(&mut type_mut, &mut pvalue_mut, &mut size_mut) {
        return 0;
    }
    
    binn_map_set_raw(map, id, type_mut, pvalue_mut.as_deref(), size_mut)
}
pub fn binn_object_set_raw(
    item: Option<&mut Binn_Struct>,
    key: Option<&str>,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    // Check for NULL item or invalid type/writable flag
    let item = match item {
        Some(item) if item.type_ == 0xE2 && item.writable != 0 => item,
        _ => return 0,
    };

    // Check for NULL key
    let key = match key {
        Some(key) => key,
        None => return 0,
    };

    // Check key length
    let int32 = key.len() as i32;
    if int32 > 255 {
        return 0;
    }

    // Search for existing key
    let pbuf_slice = match &item.pbuf {
        Some(_) => unsafe {
            std::slice::from_raw_parts(
                item.pbuf.as_ref().unwrap().as_ref() as *const _ as *const u8,
                item.used_size as usize,
            )
        },
        None => return 0,
    };

    if SearchForKey(pbuf_slice, 9, item.used_size as usize, item.count, key).is_some() {
        return 0;
    }

    // Check allocation
    if CheckAllocation(item, 1 + int32) == 0 {
        return 0;
    }

    // Get mutable access to buffer
    let p = unsafe {
        std::slice::from_raw_parts_mut(
            item.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8,
            item.alloc_size as usize,
        )
    };
    let mut p_idx = item.used_size as usize;

    // Store key length and key
    let len = int32 as u8;
    p[p_idx] = len;
    p_idx += 1;
    p[p_idx..p_idx + int32 as usize].copy_from_slice(key.as_bytes());
    let total_key_size = int32 + 1;

    // Update used size
    item.used_size += total_key_size;

    // Add value
    if AddValue(item, type_, pvalue, size) == 0 {
        item.used_size -= total_key_size;
        return 0;
    }

    item.count += 1;
    1
}
pub fn binn_object_set(
    obj: Option<&mut Binn_Struct>,
    key: Option<&str>,
    mut type_: i32,
    mut pvalue: Option<&mut [u8]>,
    mut size: i32,
) -> BOOL {
    if !GetWriteConvertedData(&mut type_, &mut pvalue, &mut size) {
        return 0;
    }
    binn_object_set_raw(obj, key, type_, pvalue.map(|v| v as &[u8]), size)
}
pub fn binn_create_list(list: &mut Binn) -> BOOL {
    binn_create(list, 0xE0, 0, None)
}
pub fn binn_create_map(map: &mut Binn) -> BOOL {
    binn_create(map, 0xE1, 0, None)
}
pub fn binn_create_object(object: &mut Binn) -> BOOL {
    binn_create(object, 0xE2, 0, None)
}
pub fn binn_free(item: Binn) {
    // Early return if item is None (equivalent to NULL check in C)
    let mut item = match item {
        Some(item) => item,
        None => return,
    };

    // Check writable and pre_allocated conditions
    if item.writable != 0 && item.pre_allocated == 0 {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(item.pbuf.take());
        }
    }

    // Call custom free function if present
    if let Some(freefn) = item.freefn {
        freefn(item.ptr.take());
    }

    // Handle allocated vs non-allocated cases
    if item.allocated != 0 {
        // The Box will be dropped automatically here
    } else {
        // Equivalent to memset(item, 0, sizeof(binn))
        *item = Binn_Struct {
            header: 0x1F22B11F, // Only preserve the header
            writable: 0,
            dirty: 0,
            pbuf: None,
            pre_allocated: 0,
            alloc_size: 0,
            used_size: 0,
            type_: 0,
            ptr: None,
            size: 0,
            count: 0,
            freefn: None,
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
            disable_int_compression: 0,
            allocated: 0,
        };
    }
}
pub fn binn_load(data: Option<*mut u8>, value: Option<&mut Binn_Struct>) -> BOOL {
    // Check for null pointers (represented as None in Rust)
    if data.is_none() || value.is_none() {
        return 0;
    }

    let value = value.unwrap(); // Safe unwrap since we checked for None

    // Equivalent to memset(value, 0, sizeof(binn))
    *value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    value.header = 0x1F22B11F;

    if !binn_is_valid(
        data,
        Some(&mut value.type_),
        Some(&mut value.count),
        Some(&mut value.size),
    ) {
        return 0;
    }

    // Convert the raw pointer to Box to match the expected type
    unsafe {
        value.ptr = Some(Box::from_raw(data.unwrap() as *mut ()));
    }
    1
}
pub fn binn_list_int64(list: Option<&[u8]>, pos: i32) -> int64 {
    let mut value: int64 = 0;
    // 0x81 is the BINN_INT64 type code
    binn_list_get(list, pos, 0x81, Some(&mut value.to_ne_bytes()), None);
    value
}
pub fn binn_list_bool(list: Option<&[u8]>, pos: i32) -> BOOL {
    let mut value: BOOL = 0;
    binn_list_get(list, pos, 0x80061, Some(&mut [value as u8]), None);
    value
}
pub fn binn_map_int64(map: Option<&[u8]>, id: i32) -> int64 {
    let mut value: int64 = 0;
    binn_map_get(map, id, 0x81, Some(&mut value.to_ne_bytes()), None);
    value
}
pub fn binn_map_bool(map: Option<&[u8]>, id: i32) -> BOOL {
    let mut value: i32 = 0;
    binn_map_get(map, id, 0x80061, Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut i32 as *mut u8, 4) }), None);
    value
}
pub fn binn_object_int64(obj: Option<&[u8]>, key: Option<&str>) -> int64 {
    let mut value: int64 = 0;
    binn_object_get(obj, key, 0x81, Some(&mut value.to_ne_bytes()), None);
    value
}
pub fn binn_object_bool(obj: Option<&[u8]>, key: Option<&str>) -> BOOL {
    let mut value: BOOL = 0;
    binn_object_get(obj, key, 0x80061, Some(unsafe { std::slice::from_raw_parts_mut(&mut value as *mut _ as *mut u8, std::mem::size_of::<BOOL>()) }), None);
    value
}
pub fn helper_binn_read_pair_1(
    int32_ref: &mut i32,
    id_ref: &mut i32,
    counter_ref: &mut i32,
    p_idx_ref: &mut u32,
    key_idx_ref: &mut u32,
    len_ref: &mut u8,
    pos: i32,
    type_: u8,
    p: &[u8],
    plimit: &[u8],
    plimit_idx: u32,
    base: &[u8],
    base_idx: u32,
) -> bool {
    let mut int32 = *int32_ref;
    let mut id = *id_ref;
    let mut counter = *counter_ref;
    let mut p_idx = *p_idx_ref;
    let mut key_idx = *key_idx_ref;
    let mut len = *len_ref;

    match type_ {
        0xE1 => {
            if let Some(new_int32) = read_map_id(&mut &p[p_idx as usize..], plimit.len()) {
                int32 = new_int32;
                if p_idx as usize >= plimit.len() {
                    return false;
                }
                id = int32;
            } else {
                return false;
            }
        }
        0xE2 => {
            if p_idx as usize >= p.len() {
                return false;
            }
            len = p[p_idx as usize];
            p_idx += 1;
            if p_idx as usize >= plimit.len() {
                return false;
            }
            key_idx = p_idx;
            p_idx += len as u32;
            if p_idx as usize >= plimit.len() {
                return false;
            }
        }
        _ => {}
    }

    counter += 1;
    if counter == pos {
        // In Rust, we don't use goto - we'll just return early with the values
        *int32_ref = int32;
        *id_ref = id;
        *counter_ref = counter;
        *p_idx_ref = p_idx;
        *key_idx_ref = key_idx;
        *len_ref = len;
        return true;
    }

    if let Some(new_p) = AdvanceDataPos(&p[p_idx as usize..], plimit.as_ptr()) {
        p_idx = new_p.as_ptr() as u32 - p.as_ptr() as u32;
    } else {
        return false;
    }

    if p_idx as usize >= p.len() || p_idx < base_idx {
        return false;
    }

    *int32_ref = int32;
    *id_ref = id;
    *counter_ref = counter;
    *p_idx_ref = p_idx;
    *key_idx_ref = key_idx;
    *len_ref = len;

    true
}
pub fn binn_read_pair(
    expected_type: i32,
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut Binn_Struct>,
) -> BOOL {
    let mut ptr_idx = 0;
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    let mut int32 = 0;
    let mut id = 0;
    let mut counter = 0;
    let mut len = 0u8;
    let mut key_idx = 0u32;

    ptr_idx = binn_ptr(None).unwrap_or(std::ptr::null_mut()) as u32;

    if !IsValidBinnHeader(ptr, Some(&mut type_), Some(&mut count), Some(&mut size), Some(&mut header_size)) {
        return 0;
    }

    if type_ != expected_type || count == 0 || pos < 1 || pos > count {
        return 0;
    }

    let p = ptr.unwrap();
    let base = &p[header_size as usize..];
    let plimit = &p[(header_size as usize + size as usize - 1)..];

    let mut p_idx = header_size as u32;
    let base_idx = 0u32;
    let plimit_idx = 0u32;

    for _ in 0..count {
        helper_binn_read_pair_1(
            &mut int32,
            &mut id,
            &mut counter,
            &mut p_idx,
            &mut key_idx,
            &mut len,
            pos,
            type_ as u8,
            p,
            plimit,
            plimit_idx,
            base,
            base_idx,
        );
    }

    match type_ {
        0xE1 => {
            if let Some(pid) = pid {
                *pid = id;
            }
        }
        0xE2 => {
            if let Some(pkey) = pkey {
                let key = &p[key_idx as usize..(key_idx as usize + len as usize)];
                pkey[..len as usize].copy_from_slice(key);
                if (len as usize) < pkey.len() {
                    pkey[len as usize] = 0;
                }
            }
        }
        _ => (),
    }

    GetValue(Some(p), value)
}
pub fn binn_map_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    value: Option<&mut Binn_Struct>,
) -> BOOL {
    binn_read_pair(0xE1, ptr, pos, pid, None, value)
}
pub fn binn_object_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pkey: Option<&mut [u8]>,
    value: Option<&mut Binn_Struct>,
) -> BOOL {
    binn_read_pair(0xE2, ptr, pos, None, pkey, value)
}
pub fn binn_size(ptr: Option<*const u32>) -> i32 {
    let item_idx = match binn_get_ptr_type(ptr) {
        1 => {
            // Safe because we've checked the ptr_type is 1
            let item = unsafe { &*(ptr.unwrap() as *const Binn_Struct) };
            let mut item = item.clone(); // Clone to get a mutable copy
            if item.writable != 0 && item.dirty != 0 {
                binn_save_header(&mut item);
            }
            item.size
        }
        2 => {
            // Convert raw pointer to slice for binn_buf_size
            let slice = unsafe { std::slice::from_raw_parts(ptr.unwrap() as *const u8, 0) };
            binn_buf_size(Some(slice))
        }
        _ => 0,
    };
    item_idx
}
pub fn binn_set_alloc_functions(
    new_malloc: Option<fn(Layout) -> *mut u8>,
    new_realloc: Option<fn(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>>>,
    new_free: Option<Box<dyn FnMut(Option<Box<()>>) + Send>>,
) {
    *MALLOC_FN.lock().unwrap() = new_malloc;
    *REALLOC_FN.lock().unwrap() = new_realloc;
    *FREE_FN.lock().unwrap() = new_free;
}
pub fn binn_release(item: Binn) -> Option<Box<()>> {
    // Early return if item is None (equivalent to NULL check in C)
    let mut item = item?;
    
    let data_idx = binn_ptr(Some(item.ptr.as_mut()?.as_mut() as *mut _ as *mut u32)).unwrap_or(ptr::null_mut());
    let data = unsafe { Box::from_raw(data_idx.cast::<()>()) };

    // Check if data is after pbuf and needs moving
    if let Some(pbuf) = &item.pbuf {
        let pbuf_ptr = pbuf.as_ref() as *const _ as *mut u32;
        if (data_idx as usize) > (pbuf_ptr as usize) {
            unsafe {
                ptr::copy(
                    data_idx as *const u8,
                    pbuf_ptr as *mut u8,
                    item.size as usize
                );
            }
        }
    }

    if item.allocated != 0 {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
    } else {
        // Zero out the struct and set header
        unsafe {
            ptr::write_bytes(&mut *item, 0, 1);
        }
        item.header = 0x1F22B11F;
    }

    Some(data)
}
pub fn binn_type(ptr: Option<*const u32>) -> i32 {
    let item_idx: u32;
    match binn_get_ptr_type(ptr) {
        1 => {
            // Safe because we've checked the pointer type is 1
            let item = unsafe { &*(ptr.unwrap() as *const Binn_Struct) };
            return item.type_;
        }
        2 => {
            // Convert raw pointer to slice for binn_buf_type
            // Note: This is unsafe and assumes the pointer is valid
            // In a real implementation, you'd need proper length information
            let slice = unsafe { std::slice::from_raw_parts(ptr.unwrap() as *const u8, 0) };
            return binn_buf_type(Some(slice));
        }
        _ => {
            return -1;
        }
    }
}
pub fn binn_count(ptr: Option<*const u32>) -> i32 {
    let item_idx: u32;
    match binn_get_ptr_type(ptr) {
        1 => {
            let item = unsafe { &*(ptr.unwrap() as *const Binn_Struct) };
            return item.count;
        },
        2 => {
            // Convert raw pointer to slice for binn_buf_count
            // Note: This is unsafe and assumes the pointer is valid
            // In real code, you'd need proper length information
            let slice = unsafe { std::slice::from_raw_parts(ptr.unwrap() as *const u8, 0) };
            return binn_buf_count(Some(slice));
        },
        _ => {
            return -1;
        }
    }
}
pub fn binn_list_uint64(list: Option<&[u8]>, pos: i32) -> uint64 {
    let mut value = 0u64;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut u64 as *mut u8, std::mem::size_of::<u64>())
    };
    binn_list_get(list, pos, 0x80, Some(value_slice), None);
    value
}
pub fn binn_map_uint64(map: Option<&[u8]>, id: i32) -> uint64 {
    let mut value = 0u64;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut uint64 as *mut u8, std::mem::size_of::<uint64>())
    };
    binn_map_get(map, id, 0x80, Some(value_slice), None);
    value
}
pub fn binn_object_uint64(obj: Option<&[u8]>, key: Option<&str>) -> uint64 {
    let mut value = 0u64;
    let value_slice = unsafe {
        std::slice::from_raw_parts_mut(&mut value as *mut uint64 as *mut u8, std::mem::size_of::<uint64>())
    };
    binn_object_get(obj, key, 0x80, Some(value_slice), None);
    value
}
pub fn store_value(value: &Binn_Struct) -> Option<&()> {
    unsafe {
        // Copy the value to local_value (equivalent to memcpy)
        if let Some(ref mut local) = local_value {
            **local = value.clone();
        } else {
            local_value = Some(Box::new(value.clone()));
        }

        match binn_get_read_storage(value.type_) {
            0x00 | 0x40 | 0x60 | 0x80 => {
                // Return reference to vint32 field
                local_value.as_ref().map(|v| &v.vint32 as *const _ as *const ())
                    .map(|p| unsafe { &*p })
            }
            _ => value.ptr.as_ref().map(|p| &**p),
        }
    }
}
pub fn binn_list_read<'a>(
    list: Option<&'a [u8]>,
    pos: i32,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    if binn_list_get_value(list, pos, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }

    if let Some(psize) = psize {
        *psize = value.size;
    }

    // Convert the reference to an owned value
    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_map_read<'a>(
    map: Option<&'a [u8]>,
    id: i32,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    if binn_map_get_value(map, id, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }

    if let Some(psize) = psize {
        *psize = value.size;
    }

    // Convert the reference to an owned value
    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_object_read<'a>(
    obj: Option<&'a [u8]>,
    key: Option<&'a str>,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<&'a ()> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    if binn_object_get_value(obj, key, Some(&mut value)) == 0 {
        return None;
    }
    
    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }
    
    if let Some(psize) = psize {
        *psize = value.size;
    }
    
    // Since we can't return a reference to local data, we'll just return None
    // This matches the C behavior when binn_object_get_value fails
    None
}
pub fn binn_map_read_pair<'a>(
    ptr: Option<&'a [u8]>,
    pos: i32,
    pid: Option<&'a mut i32>,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<Box<()>> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    if binn_map_get_pair(ptr, pos, pid, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }

    if let Some(psize) = psize {
        *psize = value.size;
    }

    // Convert the reference to an owned value
    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_object_read_pair<'a>(
    ptr: Option<&'a [u8]>,
    pos: i32,
    pkey: Option<&'a mut [u8]>,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<Box<()>> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    if binn_object_get_pair(ptr, pos, pkey, Some(&mut value)) == 0 {
        return None;
    }
    
    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }
    
    if let Some(psize) = psize {
        *psize = value.size;
    }
    
    // Convert the reference to an owned value
    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_read_next_pair(
    expected_type: i32,
    iter: Option<&mut Binn_Iter_Struct>,
    pid: Option<&mut i32>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut Binn_Struct>,
) -> bool {
    // Check for invalid iterator conditions
    let iter = match iter {
        Some(iter) => iter,
        None => return false,
    };

    if iter.pnext.is_none()
        || iter.pnext.as_ref().unwrap().as_ptr() > iter.plimit.as_ref().unwrap().as_ptr()
        || iter.current > iter.count
        || iter.type_ != expected_type
    {
        return false;
    }

    iter.current += 1;
    if iter.current > iter.count {
        return false;
    }

    // Store p in a local variable to avoid holding the borrow too long
    let p = iter.pnext.as_ref().unwrap().clone();
    let mut p_idx = 0;

    match expected_type {
        0xE1 => {
            let mut p_slice = &p[p_idx..];
            let int32 = match read_map_id(&mut p_slice, iter.plimit.as_ref().unwrap().as_ptr() as usize) {
                Some(val) => val,
                None => return false,
            };

            p_idx = p.len() - p_slice.len();
            if p_idx >= p.len() {
                return false;
            }

            if let Some(pid) = pid {
                *pid = int32;
            }
        }
        0xE2 => {
            let len = p[p_idx] as usize;
            p_idx += 1;

            if p_idx + len > p.len() {
                return false;
            }

            let key = &p[p_idx..p_idx + len];
            p_idx += len;

            if p_idx > p.len() {
                return false;
            }

            if let Some(pkey) = pkey {
                if pkey.len() >= len {
                    pkey[..len].copy_from_slice(key);
                    if pkey.len() > len {
                        pkey[len] = 0;
                    }
                } else {
                    return false;
                }
            }
        }
        _ => return false,
    }

    let new_pnext = match AdvanceDataPos(&p, iter.plimit.as_ref().unwrap().as_ptr()) {
        Some(p) => p.to_vec(),
        None => return false,
    };

    iter.pnext = Some(new_pnext);

    GetValue(Some(&p), value) != 0
}
pub fn binn_map_next(
    iter: Option<&mut Binn_Iter_Struct>,
    pid: Option<&mut i32>,
    value: Option<&mut Binn_Struct>,
) -> bool {
    binn_read_next_pair(0xE1, iter, pid, None, value)
}
pub fn binn_object_next(
    iter: Option<&mut Binn_Iter_Struct>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut Binn_Struct>,
) -> bool {
    binn_read_next_pair(0xE2, iter, None, pkey, value)
}
pub fn binn_copy(old: Option<*mut u32>) -> Binn {
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
    let old_ptr = binn_ptr(old);
    if old_ptr.is_none() {
        return None;
    }

    // Safe conversion from pointer to slice reference
    let old_slice = unsafe { std::slice::from_raw_parts(old_ptr.unwrap() as *const u8, size as usize) };

    if !IsValidBinnHeader(
        Some(old_slice),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return None;
    }

    let item = binn_new(type_, (size - header_size) + 9, None);
    if let Some(mut item) = item {
        let payload_size = size - header_size;
        if payload_size > 0 {
            if let Some(pbuf) = &mut item.pbuf {
                let dest_slice = unsafe {
                    std::slice::from_raw_parts_mut(
                        (pbuf.as_ref() as *const _ as *mut u8).add(9),
                        payload_size as usize,
                    )
                };
                let src_slice = unsafe {
                    std::slice::from_raw_parts(
                        old_ptr.unwrap().add(header_size as usize) as *const u8,
                        payload_size as usize,
                    )
                };
                dest_slice.copy_from_slice(src_slice);
            }
        }
        item.used_size = (9 + size) - header_size;
        item.count = count;
        Some(item)
    } else {
        None
    }
}
pub fn binn_list_add_new(list: Binn, value: Binn) -> BOOL {
    let retval = binn_list_add_value(list.clone(), value.clone());
    
    if let Some(value) = value {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(()) as Box<()>));
        }
    }
    
    retval
}
pub fn binn_map_set_new(map: Option<&mut Binn_Struct>, id: i32, mut value: Option<Box<Binn_Struct>>) -> BOOL {
    let retval = binn_map_set_value(map, id, value.as_deref_mut());
    
    if let Some(value) = value.take() {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
    }
    
    retval
}
pub fn binn_object_set_new(obj: Option<&mut Binn_Struct>, key: Option<&str>, value: Option<Box<Binn_Struct>>) -> BOOL {
    let retval = binn_object_set_value(obj, key, value.as_deref());
    
    if let Some(v) = value {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
    }
    
    retval
}
pub fn binn_open(data: Option<*mut u8>) -> Binn {
    // Allocate memory for the binn struct
    let item_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32);
    if item_ptr.is_none() {
        return None;
    }

    // Create a Box from the raw pointer
    let mut item = unsafe { Box::from_raw(item_ptr.unwrap() as *mut Binn_Struct) };
    
    // Try to load the data into the binn struct
    if binn_load(data, Some(&mut *item)) == 0 {
        // If loading fails, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
        return None;
    }

    item.allocated = 1;
    Some(Box::new(*item))
}
pub fn binn_list_value(ptr: Option<&[u8]>, pos: i32) -> Binn {
    // Allocate memory for a new Binn struct
    let value_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32);
    let mut value = match value_ptr {
        Some(ptr) => unsafe { Box::from_raw(ptr as *mut Binn_Struct) },
        None => return None,
    };

    // Initialize the struct
    value.allocated = 1;

    // Try to get the list value
    if binn_list_get_value(ptr, pos, Some(&mut *value)) == 0 {
        // On failure, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
        return None;
    }

    // Mark as allocated and return
    value.allocated = 1;
    Some(value)
}

pub fn binn_map_value(ptr: Option<&[u8]>, id: i32) -> Option<Box<Binn_Struct>> {
    // Allocate memory for the binn struct
    let value_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32);
    if value_ptr.is_none() {
        return None;
    }

    // Create a new Binn_Struct and initialize it
    let mut value = Box::new(Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    });

    // Try to get the value from the map
    if binn_map_get_value(ptr, id, Some(&mut *value)) == 0 {
        // If failed, free the allocated memory and return None
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(None); // Assuming the free function can handle null pointers
        }
        return None;
    }

    value.allocated = 1;
    Some(value)
}
pub fn binn_object_value(ptr: Option<&[u8]>, key: Option<&str>) -> Option<Box<Binn_Struct>> {
    // Allocate memory for the Binn struct
    let mut value = match binn_malloc(std::mem::size_of::<Binn_Struct>() as i32) {
        Some(ptr) => unsafe { Box::from_raw(ptr as *mut Binn_Struct) },
        None => return None,
    };

    // Initialize the struct
    value.allocated = 1;

    // Call binn_object_get_value with mutable reference to the struct
    if binn_object_get_value(ptr, key, Some(&mut *value)) == 0 {
        // If the call fails, free the allocated memory and return None
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
        return None;
    }

    Some(value)
}
pub fn binn_map_pair(map: Option<&[u8]>, pos: i32, pid: Option<&mut i32>) -> Binn {
    // Allocate memory for Binn_Struct
    let value_ptr = match binn_malloc(std::mem::size_of::<Binn_Struct>() as i32) {
        Some(ptr) => ptr,
        None => return None,
    };

    // Create a Box from the raw pointer
    let mut value = unsafe { Box::from_raw(value_ptr as *mut Binn_Struct) };
    
    // Initialize the struct
    value.allocated = 1;
    
    // Call binn_read_pair with the initialized struct
    if binn_read_pair(0xE1, map, pos, pid, None, Some(&mut *value)) == 0 {
        // If read fails, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(None);
        }
        return None;
    }

    // Return the boxed value
    Some(value)
}
pub fn binn_object_pair(obj: Option<&[u8]>, pos: i32, pkey: Option<&mut [u8]>) -> Binn {
    // Allocate memory for Binn_Struct using binn_malloc
    let value_ptr = match binn_malloc(std::mem::size_of::<Binn_Struct>() as i32) {
        Some(ptr) => ptr,
        None => return None,
    };

    // Create a Box from the raw pointer
    let mut value = unsafe { Box::from_raw(value_ptr as *mut Binn_Struct) };
    
    // Initialize the Binn_Struct with default values
    *value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };

    // Convert the Box to a mutable reference for binn_read_pair
    let value_ref = &mut *value;

    if binn_read_pair(0xE2, obj, pos, None, pkey, Some(value_ref)) == 0 {
        // If read fails, free the allocated memory and return None
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(Box::new(())));
        }
        return None;
    }

    // Set allocated flag and return the Binn
    value.allocated = 1;
    Some(value)
}
pub fn binn_iter_init(iter: &mut Binn_Iter, ptr: Option<&[u8]>, expected_type: i32) -> bool {
    // Convert ptr to raw pointer for binn_ptr (FFI compatibility)
    let ptr_idx = binn_ptr(None);
    if ptr.is_none() || iter.is_none() {
        return false;
    }

    // Initialize the iterator by creating a new Binn_Iter_Struct with default values
    *iter = Some(Box::new(Binn_Iter_Struct {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    }));

    let ptr = ptr.unwrap();
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    if !IsValidBinnHeader(
        Some(ptr),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return false;
    }

    if type_ != expected_type {
        return false;
    }

    if let Some(iter_inner) = iter.as_mut() {
        // Convert i32 to usize for slice indexing
        let size_usize = size as usize;
        let header_size_usize = header_size as usize;
        
        // Get slices using proper usize indices
        let limit_slice = &ptr[size_usize..];
        let next_slice = &ptr[header_size_usize..];
        
        iter_inner.plimit = Some(limit_slice.to_vec());
        iter_inner.pnext = Some(next_slice.to_vec());
        iter_inner.count = count;
        iter_inner.current = 0;
        iter_inner.type_ = type_;
    }

    true
}
pub fn binn_list_next(iter: &mut Binn_Iter, value: &mut Binn) -> BOOL {
    // Early return if any of the conditions in the complex check fail
    if iter.is_none() 
        || iter.as_ref().unwrap().pnext.is_none() 
        || iter.as_ref().unwrap().plimit.is_none() 
        || iter.as_ref().unwrap().type_ != 0xE0 
    {
        return 0;
    }

    let iter_inner = iter.as_mut().unwrap();
    
    // Check if pnext is beyond plimit (using slice comparison)
    let pnext_slice = iter_inner.pnext.as_ref().unwrap();
    let plimit_slice = iter_inner.plimit.as_ref().unwrap();
    if pnext_slice.as_ptr() > plimit_slice.as_ptr() 
        || iter_inner.current > iter_inner.count 
    {
        return 0;
    }

    iter_inner.current += 1;
    if iter_inner.current > iter_inner.count {
        return 0;
    }

    // Store the current position before advancing
    let pnow = iter_inner.pnext.as_ref().unwrap().clone();
    let pnow_idx = pnow.as_ptr() as usize;

    // Advance the position
    let new_pnext = AdvanceDataPos(&pnow, plimit_slice.as_ptr()).map(|s| s.to_vec());
    
    // Check if pnext went backwards (invalid advance)
    if let Some(ref new_pnext) = new_pnext {
        if (new_pnext.as_ptr() as usize) < pnow_idx {
            return 0;
        }
    } else {
        return 0; // AdvanceDataPos returned None
    }

    // Update pnext after all checks
    iter_inner.pnext = new_pnext;

    // Get the value - need to convert the Option<Box<Binn_Struct>> to Option<&mut Binn_Struct>
    let value_ref = value.as_mut().map(|b| &mut **b);
    GetValue(Some(&pnow), value_ref)
}
pub fn binn_list_read_next<'a>(
    iter: &'a mut Binn_Iter,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<Box<()>> {
    let mut value = Box::new(Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: Binn_Mem_Free::None,
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
        disable_int_compression: 0,
    });

    if binn_list_next(iter, &mut Some(value.clone())) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        *ptype = value.type_;
    }

    if let Some(psize) = psize {
        *psize = value.size;
    }

    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_map_read_next<'a>(
    iter: Option<&'a mut Binn_Iter_Struct>,
    pid: Option<&'a mut i32>,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<&'a ()> {
    let mut value = Box::new(Binn_Struct {
        header: 0,
        allocated: 0,  // FALSE
        writable: 0,  // FALSE
        dirty: 0,     // FALSE
        pbuf: None,
        pre_allocated: 0,  // FALSE
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        vbool: 0,     // FALSE
        disable_int_compression: 0,  // FALSE
    });

    if !binn_map_next(iter, pid, Some(&mut *value)) {
        return None;
    }

    if let Some(ptype_ref) = ptype {
        *ptype_ref = value.type_;
    }

    if let Some(psize_ref) = psize {
        *psize_ref = value.size;
    }

    // Leak the box to get a static reference, matching the C behavior
    let leaked = Box::leak(value);
    store_value(leaked)
}
pub fn binn_object_read_next<'a>(
    iter: Option<&'a mut Binn_Iter_Struct>,
    pkey: Option<&'a mut [u8]>,
    ptype: Option<&'a mut i32>,
    psize: Option<&'a mut i32>,
) -> Option<Box<()>> {
    let mut value = Binn_Struct {
        header: 0,
        allocated: 0,
        writable: 0,
        dirty: 0,
        pbuf: None,
        pre_allocated: 0,
        alloc_size: 0,
        used_size: 0,
        type_: 0,
        ptr: None,
        size: 0,
        count: 0,
        freefn: None,
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
        disable_int_compression: 0,
    };
    
    if !binn_object_next(iter, pkey, Some(&mut value)) {
        return None;
    }

    if let Some(ptype_ref) = ptype {
        *ptype_ref = value.type_;
    }

    if let Some(psize_ref) = psize {
        *psize_ref = value.size;
    }

    // Convert the reference to an owned Box
    store_value(&value).map(|r| Box::new(*r))
}
pub fn binn_set_string(item: Option<&mut Binn_Struct>, str: Option<&str>, pfree: Binn_Mem_Free) -> BOOL {
    // Check for NULL pointers (translated to Option checks in Rust)
    if item.is_none() || str.is_none() {
        return 0;
    }
    
    let item = item.unwrap();
    let str = str.unwrap();
    
    // Check if pfree is the special marker value (-1 cast to function pointer)
    if pfree.is_none() {
        // Convert string to bytes for binn_memdup
        let bytes = str.as_bytes();
        item.ptr = binn_memdup(Some(bytes), (bytes.len() + 1) as i32)
            .map(|b| Box::into_raw(b) as *mut ())
            .map(|p| unsafe { Box::from_raw(p) });
        
        if item.ptr.is_none() {
            return 0;
        }
        
        // Use a shim function that calls the closure from FREE_FN
        item.freefn = Some(free_fn_shim);
    } else {
        // Convert string to a null-terminated CString and box it
        let cstr = std::ffi::CString::new(str).unwrap();
        let boxed_bytes = Box::new(cstr.into_bytes_with_nul());
        item.ptr = Some(Box::into_raw(boxed_bytes) as *mut ())
            .map(|p| unsafe { Box::from_raw(p) });
        item.freefn = pfree;
    }
    
    item.type_ = 0xA0;
    1
}

// Shim function that calls the closure stored in FREE_FN
fn free_fn_shim(ptr: Option<Box<()>>) {
    let mut free_fn_guard = FREE_FN.lock().unwrap();
    if let Some(ref mut free_fn) = *free_fn_guard {
        free_fn(ptr);
    }
}
pub fn binn_set_blob(
    item: Option<&mut Binn_Struct>,
    ptr: Option<&[u8]>,
    size: i32,
    pfree: Binn_Mem_Free,
) -> BOOL {
    // Check for NULL pointers (Option::None in Rust)
    if item.is_none() || ptr.is_none() {
        return 0;
    }

    let item = item.unwrap(); // Safe unwrap since we checked is_none()
    let ptr = ptr.unwrap();   // Safe unwrap since we checked is_none()

    // Check if pfree is the special value (-1)
    if pfree.is_none() {
        // Use binn_memdup to duplicate the memory
        let duplicated = binn_memdup(Some(ptr), size);
        if duplicated.is_none() {
            return 0;
        }
        let duplicated_val = duplicated.unwrap();
        // Convert the Box<[u8]> to a raw pointer and then to Box<()>
        let raw_ptr = Box::into_raw(duplicated_val) as *mut ();
        unsafe {
            item.ptr = Some(Box::from_raw(raw_ptr));
        }
        // Get the function pointer from FREE_FN
        item.freefn = FREE_FN.lock().unwrap().as_ref().map(|f| {
            // Convert the FnMut to a fn pointer if possible
            unsafe {
                std::mem::transmute::<*const (), fn(Option<Box<()>>)>(f as *const _ as *const ())
            }
        });
    } else {
        // Directly use the provided pointer as *mut ()
        unsafe {
            item.ptr = Some(Box::from_raw(ptr.as_ptr() as *mut ()));
        }
        item.freefn = pfree;
    }

    item.type_ = 0xC0;
    item.size = size;
    1
}
pub fn binn_get_str(value: Binn) -> Option<CString> {
    let mut value = value?; // Early return if None (equivalent to NULL check)
    let mut buf = [0u8; 128];

    if type_family(value.type_) == 0xf2 {
        let mut vint: int64 = 0;
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const () as *const u8, 1) }),
            Some(&mut vint.to_ne_bytes()),
            value.type_,
            0x81,
        ) {
            return None;
        }
        let s = format!("{}", vint);
        if s.len() >= buf.len() {
            return None; // Buffer too small
        }
        buf[..s.len()].copy_from_slice(s.as_bytes());
        goto_loc_convert_value(&mut *value, &buf, s.len())
    } else {
        match value.type_ {
            0x62 => {
                // Convert the float to double and store it, then format as double
                value.vdouble = value.vfloat as f64;
                let s = format!("{}", value.vdouble);
                if s.len() >= buf.len() {
                    return None;
                }
                buf[..s.len()].copy_from_slice(s.as_bytes());
                goto_loc_convert_value(&mut *value, &buf, s.len())
            }
            0x82 => {
                let s = format!("{}", value.vdouble);
                if s.len() >= buf.len() {
                    return None;
                }
                buf[..s.len()].copy_from_slice(s.as_bytes());
                goto_loc_convert_value(&mut *value, &buf, s.len())
            }
            0xA0 => {
                // SAFETY: We trust the C code that ptr points to a valid null-terminated string
                unsafe {
                    let ptr = value.ptr.as_ref()?;
                    Some(CString::from_raw(ptr.as_ref() as *const () as *mut i8))
                }
            }
            0x80061 => {
                let s = if value.vbool != 0 { "true" } else { "false" };
                if s.len() >= buf.len() {
                    return None;
                }
                buf[..s.len()].copy_from_slice(s.as_bytes());
                goto_loc_convert_value(&mut *value, &buf, s.len())
            }
            _ => None,
        }
    }
}

extern "C" {
    fn free(ptr: *mut std::ffi::c_void);
}

fn goto_loc_convert_value(value: &mut Binn_Struct, buf: &[u8], len: usize) -> Option<CString> {
    let c_str = CString::new(&buf[..len]).ok()?;
    let c_ptr = c_str.into_raw();
    
    // Store the raw pointer directly after casting to *mut ()
    let ptr = unsafe { std::mem::transmute::<*mut i8, *mut ()>(c_ptr) };
    value.ptr = Some(Box::new(unsafe { *ptr }));
    value.freefn = Some(unsafe { std::mem::transmute(free as *const ()) });
    value.type_ = 0xA0;
    
    // SAFETY: We just created this pointer and know it's valid
    unsafe { Some(CString::from_raw(c_ptr)) }
}
pub fn binn_list_next_value(iter: &mut Binn_Iter) -> Binn {
    // Allocate memory for a new Binn struct
    let value_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32);
    let mut value = match value_ptr {
        Some(ptr) => unsafe { Box::from_raw(ptr as *mut Binn_Struct) },
        None => return None,
    };

    // Initialize the Binn struct
    value.allocated = 1;
    let mut value_box = Some(value);

    // Call binn_list_next with the mutable references
    if binn_list_next(iter, &mut value_box) == 0 {
        // Free the allocated memory if binn_list_next fails
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(value_box.map(|b| unsafe { Box::from_raw(Box::into_raw(Box::new(b)) as *mut ()) }));
        }
        return None;
    }

    // Set allocated flag and return the value
    if let Some(v) = &mut value_box {
        v.allocated = 1;
    }
    value_box
}

pub fn binn_map_next_value(iter: Option<&mut Binn_Iter_Struct>, pid: Option<&mut i32>) -> Option<Box<Binn_Struct>> {
    // Allocate memory for a new Binn_Struct
    let value_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32)?;
    
    // Convert the raw pointer to a mutable reference
    let value = unsafe { &mut *(value_ptr as *mut Binn_Struct) };
    
    // Create a boxed value to manage the memory
    let mut boxed_value = unsafe { Box::from_raw(value) };
    
    // Call binn_map_next with references to the parameters
    if !binn_map_next(iter, pid, Some(&mut boxed_value)) {
        // If the operation fails, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(unsafe { Box::from_raw(Box::into_raw(boxed_value) as *mut ()) }));
        }
        return None;
    }
    
    // Set the allocated flag
    boxed_value.allocated = 1;
    
    Some(boxed_value)
}
pub fn binn_object_next_value(iter: Option<&mut Binn_Iter_Struct>, pkey: Option<&mut [u8]>) -> Option<Box<Binn_Struct>> {
    // Allocate memory for the binn struct
    let value_ptr = binn_malloc(std::mem::size_of::<Binn_Struct>() as i32)?;
    let mut value = unsafe { Box::from_raw(value_ptr as *mut Binn_Struct) };

    // Call binn_object_next with the mutable references
    if !binn_object_next(iter, pkey, Some(&mut value)) {
        // If the operation failed, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn(Some(unsafe { Box::from_raw(value_ptr as *mut ()) }));
        }
        return None;
    }

    value.allocated = 1;
    Some(value)
}
pub fn binn_get_int32(value: Option<&Binn_Struct>, pint: Option<&mut i32>) -> BOOL {
    // Check for null pointers (None in Rust)
    if value.is_none() || pint.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pint = pint.unwrap();

    if type_family(value.type_) == 0xf2 {
        return if copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, std::mem::size_of::<i32>()) }),
            Some(unsafe { std::slice::from_raw_parts_mut(pint as *mut i32 as *mut u8, std::mem::size_of::<i32>()) }),
            value.type_,
            0x61,
        ) { 1 } else { 0 };
    }

    match value.type_ {
        0x62 => {
            if value.vfloat < i32::MIN as f32 || value.vfloat > i32::MAX as f32 {
                return 0;
            }
            *pint = if value.vfloat >= 0.0 {
                (value.vfloat + 0.5) as i32
            } else {
                let int_part = value.vfloat as i32;
                if (value.vfloat - int_part as f32) <= -0.5 {
                    int_part
                } else {
                    (value.vfloat - 0.5) as i32
                }
            };
        }
        0x82 => {
            if value.vdouble < i32::MIN as f64 || value.vdouble > i32::MAX as f64 {
                return 0;
            }
            *pint = if value.vdouble >= 0.0 {
                (value.vdouble + 0.5) as i32
            } else {
                let int_part = value.vdouble as i32;
                if (value.vdouble - int_part as f64) <= -0.5 {
                    int_part
                } else {
                    (value.vdouble - 0.5) as i32
                }
            };
        }
        0xA0 => {
            let ptr_str = unsafe { std::ffi::CStr::from_ptr(value.ptr.as_ref().unwrap().as_ref() as *const _ as *const i8) };
            let s = ptr_str.to_str().unwrap_or("");
            
            if is_integer(Some(s)) != 0 {
                *pint = s.parse::<i32>().unwrap_or(0);
            } else if is_float(Some(s)) != 0 {
                let float_val = s.parse::<f64>().unwrap_or(0.0);
                *pint = if float_val >= 0.0 {
                    (float_val + 0.5) as i32
                } else {
                    let int_part = float_val as i32;
                    if (float_val - int_part as f64) <= -0.5 {
                        int_part
                    } else {
                        (float_val - 0.5) as i32
                    }
                };
            } else {
                return 0;
            }
        }
        0x80061 => {
            *pint = value.vbool as i32;
        }
        _ => {
            return 0;
        }
    }

    1
}
pub fn binn_add_value(
    item: Option<&mut Binn_Struct>,
    binn_type: i32,
    id: i32,
    name: Option<&str>,
    type_: i32,
    pvalue: Option<&mut [u8]>,
    size: i32,
) -> BOOL {
    match binn_type {
        0xE0 => {
            let boxed_item = item.map(|i| Box::new(i.clone()));
            binn_list_add(boxed_item, type_, pvalue, size)
        }
        0xE1 => binn_map_set(item, id, type_, pvalue, size),
        0xE2 => binn_object_set(item, name, type_, pvalue, size),
        _ => 0,
    }
}

pub fn is_bool_str(str: Option<&str>, pbool: Option<&mut BOOL>) -> BOOL {
    // Check for null inputs (None in Rust)
    if str.is_none() || pbool.is_none() {
        return 0;
    }

    let str = str.unwrap();
    let pbool = pbool.unwrap();

    // Convert to lowercase for case-insensitive comparison
    let lower_str = str.to_lowercase();

    match lower_str.as_str() {
        "true" | "yes" | "on" => {
            *pbool = 1;
            return 1;
        }
        "false" | "no" | "off" => {
            *pbool = 0;
            return 1;
        }
        _ => (),
    }

    if is_integer(Some(str)) != 0 {
        if let Some(vint) = atoi64(Some(str)) {
            *pbool = if vint != 0 { 1 } else { 0 };
            return 1;
        }
    } else if is_float(Some(str)) != 0 {
        // Safe conversion since we've already checked is_float
        if let Ok(vdouble) = str.parse::<f64>() {
            *pbool = if vdouble != 0.0 { 1 } else { 0 };
            return 1;
        }
    }

    0
}
pub fn binn_get_bool(value: Option<&Binn_Struct>, pbool: Option<&mut BOOL>) -> BOOL {
    // Check for null pointers (None in Rust)
    if value.is_none() || pbool.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pbool = pbool.unwrap();

    if type_family(value.type_) == 0xf2 {
        let mut vint: int64 = 0;
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const () as *const u8, std::mem::size_of::<int64>()) }),
            Some(unsafe { std::slice::from_raw_parts_mut(&mut vint as *mut _ as *mut u8, std::mem::size_of::<int64>()) }),
            value.type_,
            0x81,
        ) {
            return 0;
        }
        *pbool = if vint != 0 { 1 } else { 0 };
        return 1;
    }

    match value.type_ {
        0x80061 => {
            *pbool = value.vbool;
        }
        0x62 => {
            *pbool = if value.vfloat != 0.0 { 1 } else { 0 };
        }
        0x82 => {
            *pbool = if value.vdouble != 0.0 { 1 } else { 0 };
        }
        0xA0 => {
            return is_bool_str(
                value.ptr.as_ref().and_then(|p| unsafe { std::ffi::CStr::from_ptr(p.as_ref() as *const () as *const c_char).to_str().ok() }),
                Some(pbool),
            );
        }
        _ => {
            return 0;
        }
    }

    1
}
pub fn binn_get_int64(value: Option<&Binn_Struct>, pint: Option<&mut int64>) -> bool {
    // Check for null pointers (None in Rust)
    if value.is_none() || pint.is_none() {
        return false;
    }
    let value = value.unwrap();
    let pint = pint.unwrap();

    if type_family(value.type_) == 0xf2 {
        return copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, value.size as usize) }),
            Some(unsafe { std::slice::from_raw_parts_mut(pint as *mut _ as *mut u8, 8) }),
            value.type_,
            0x81,
        );
    }

    match value.type_ {
        0x62 => {
            let vfloat = value.vfloat as f64;
            if vfloat < INT64_MIN as f64 || vfloat > INT64_MAX as f64 {
                return false;
            }
            *pint = if vfloat >= 0.0 {
                (vfloat + 0.5) as int64
            } else {
                let int_part = vfloat as int64;
                if (vfloat - int_part as f64) <= -0.5 {
                    int_part
                } else {
                    (vfloat - 0.5) as int64
                }
            };
        }
        0x82 => {
            let vdouble = value.vdouble;
            if vdouble < INT64_MIN as f64 || vdouble > INT64_MAX as f64 {
                return false;
            }
            *pint = if vdouble >= 0.0 {
                (vdouble + 0.5) as int64
            } else {
                let int_part = vdouble as int64;
                if (vdouble - int_part as f64) <= -0.5 {
                    int_part
                } else {
                    (vdouble - 0.5) as int64
                }
            };
        }
        0xA0 => {
            let ptr = value.ptr.as_ref().map(|p| unsafe { CStr::from_ptr(p.as_ref() as *const _ as *const i8) });
            let s = ptr.and_then(|cstr| cstr.to_str().ok());
            
            if is_integer(s) != 0 {
                if let Some(val) = atoi64(s) {
                    *pint = val;
                } else {
                    return false;
                }
            } else if is_float(s) != 0 {
                let float_val = s.and_then(|s| s.parse::<f64>().ok()).unwrap_or(0.0);
                *pint = if float_val >= 0.0 {
                    (float_val + 0.5) as int64
                } else {
                    let int_part = float_val as int64;
                    if (float_val - int_part as f64) <= -0.5 {
                        int_part
                    } else {
                        (float_val - 0.5) as int64
                    }
                };
            } else {
                return false;
            }
        }
        0x80061 => {
            *pint = value.vbool as int64;
        }
        _ => {
            return false;
        }
    }

    true
}

const INT64_MIN: i64 = std::i64::MIN;
const INT64_MAX: i64 = std::i64::MAX;
pub fn binn_get_double(value: Option<&Binn_Struct>, pfloat: Option<&mut f64>) -> BOOL {
    // Check for null pointers (translated to Option checks)
    if value.is_none() || pfloat.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pfloat = pfloat.unwrap();

    let mut vint: int64 = 0;
    if type_family(value.type_) == 0xf2 {
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, value.size as usize) }),
            Some(unsafe { std::slice::from_raw_parts_mut(&mut vint as *mut _ as *mut u8, std::mem::size_of::<int64>()) }),
            value.type_,
            0x81,
        ) {
            return 0;
        }
        *pfloat = vint as f64;
        return 1;
    }

    match value.type_ {
        0x62 => {
            *pfloat = value.vfloat as f64;
        }
        0x82 => {
            *pfloat = value.vdouble;
        }
        0xA0 => {
            let ptr_str = unsafe {
                CStr::from_ptr(value.ptr.as_ref().unwrap().as_ref() as *const _ as *const i8)
                    .to_str()
                    .ok()
            };
            if is_integer(ptr_str) != 0 {
                if let Some(num) = atoi64(ptr_str) {
                    *pfloat = num as f64;
                } else {
                    return 0;
                }
            } else if is_float(ptr_str) != 0 {
                if let Some(s) = ptr_str {
                    *pfloat = s.parse().unwrap_or(0.0);
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        }
        0x80061 => {
            *pfloat = value.vbool as f64;
        }
        _ => {
            return 0;
        }
    }

    1
}
