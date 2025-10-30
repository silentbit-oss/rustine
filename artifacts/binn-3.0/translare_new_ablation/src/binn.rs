use crate::*;
use crate::BOOL;
use crate::BinnIter;
use lazy_static::lazy_static;
use std::any::Any;
use std::boxed::Box;
use std::cmp::Ordering;
use std::convert::TryFrom;
use std::convert::TryInto;
use std::ffi::CStr;
use std::ffi::CString;
use std::mem::MaybeUninit;
use std::mem;
use std::os::raw::c_char;
use std::ptr;
use std::slice;
use std::str::FromStr;
use std::sync::Mutex;

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
        let mut storage_type = storage_type;
        storage_type |= 0x10;
        storage_type <<= 8;
        let data_type_index = data_type_index >> 4;
        storage_type | data_type_index
    } else {
        -1
    }
}
pub fn binn_is_struct(ptr: Option<*mut u32>) -> bool {
    // Check if pointer is None (equivalent to NULL in C)
    let ptr = match ptr {
        Some(p) => p,
        None => return false,
    };

    // Dereference the pointer safely (requires unsafe block)
    unsafe {
        // Check if the value at the pointer matches the magic number
        *ptr == 0x1F22B11F
    }
}
pub fn strlen2(str: Option<&str>) -> usize {
    match str {
        None => 0,
        Some(s) => s.len(),
    }
}
pub fn binn_get_ptr_type(ptr: Option<*mut u8>) -> i32 {
    match ptr {
        None => 0,
        Some(ptr) => unsafe {
            match *(ptr as *const u32) {
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
pub fn GetWriteConvertedData(
    ptype: &mut i32,
    ppvalue: &mut Option<&mut Option<Box<dyn std::any::Any>>>,
    psize: &mut i32,
) -> bool {
    let type_ = *ptype;
    
    if ppvalue.is_none() {
        match type_ {
            0x00 | 0x01 | 0x02 => {}
            0xA0 | 0xC0 => {
                if *psize == 0 {
                    // Do nothing
                } else {
                    return false;
                }
            }
            _ => return false,
        }
    }

    match type_ {
        0xA4 | 0xA5 => return true,
        0xA2 | 0xA1 | 0xA3 => return true,
        0x80061 => {
            if let Some(inner_ppvalue) = ppvalue {
                if let Some(any_box) = inner_ppvalue {
                    if let Some(bool_value) = any_box.downcast_ref::<bool>() {
                        let new_type = if *bool_value { 0x01 } else { 0x02 };
                        *ptype = new_type;
                    }
                }
            }
        }
        _ => {}
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

pub fn copy_raw_value(psource: Option<&mut [u8]>, pdest: Option<&mut [u8]>, data_store: i32) -> bool {
    // Check for None (equivalent to NULL checks in C)
    if psource.is_none() || pdest.is_none() {
        return false;
    }

    let psource = psource.unwrap();
    let pdest = pdest.unwrap();

    // Ensure both slices have at least some capacity
    if psource.is_empty() || pdest.is_empty() {
        return false;
    }

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
                let src = unsafe { ptr::read_unaligned(psource.as_ptr() as *const i16) };
                unsafe { ptr::write_unaligned(pdest.as_mut_ptr() as *mut i16, src) };
            } else {
                return false;
            }
        }
        0x60 => {
            if psource.len() >= 4 && pdest.len() >= 4 {
                let src = unsafe { ptr::read_unaligned(psource.as_ptr() as *const i32) };
                unsafe { ptr::write_unaligned(pdest.as_mut_ptr() as *mut i32, src) };
            } else {
                return false;
            }
        }
        0x80 => {
            if psource.len() >= 8 && pdest.len() >= 8 {
                let src = unsafe { ptr::read_unaligned(psource.as_ptr() as *const u64) };
                unsafe { ptr::write_unaligned(pdest.as_mut_ptr() as *mut u64, src) };
            } else {
                return false;
            }
        }
        0xA0 | 0xC0 | 0xE0 => {
            // For pointer cases, we'll treat it as copying the pointer value itself
            if psource.len() >= std::mem::size_of::<usize>() && pdest.len() >= std::mem::size_of::<usize>() {
                let src = unsafe { ptr::read_unaligned(psource.as_ptr() as *const usize) };
                unsafe { ptr::write_unaligned(pdest.as_mut_ptr() as *mut usize, src) };
            } else {
                return false;
            }
        }
        _ => return false, // Default case returns false
    }

    true
}
pub fn copy_float_value(psource: Option<&mut f32>, pdest: Option<&mut f64>, source_type: i32, _dest_type: i32) -> bool {
    match source_type {
        0x62 => {
            if let (Some(src), Some(dst)) = (psource, pdest) {
                *dst = *src as f64;
                true
            } else {
                false
            }
        },
        0x82 => {
            if let (Some(src), Some(dst)) = (psource, pdest) {
                *dst = *src as f64;
                true
            } else {
                false
            }
        },
        _ => false,
    }
}

pub fn copy_float_value_reverse(psource: Option<&mut f64>, pdest: Option<&mut f32>, source_type: i32, _dest_type: i32) -> bool {
    match source_type {
        0x62 => {
            if let (Some(src), Some(dst)) = (psource, pdest) {
                *dst = *src as f32;
                true
            } else {
                false
            }
        },
        0x82 => {
            if let (Some(src), Some(dst)) = (psource, pdest) {
                *dst = *src as f32;
                true
            } else {
                false
            }
        },
        _ => false,
    }
}

pub struct BinnStruct {
    pub header: i32,
    pub allocated: BOOL,
    pub writable: BOOL,
    pub dirty: BOOL,
    pub pbuf: Option<Box<()>>,
    pub pre_allocated: BOOL,
    pub alloc_size: i32,
    pub used_size: i32,
    pub type_: i32,
    pub ptr: Option<Box<()>>,
    pub size: i32,
    pub count: i32,
    pub freefn: BinnMemFree,
    pub value: BinnValue,
    pub disable_int_compression: BOOL,
}

pub struct BinnValue {
    pub vint8: i8,
    pub vint16: i16,
    pub vint32: i32,
    pub vint64: i64,
    pub vuint8: u8,
    pub vuint16: u16,
    pub vuint32: u32,
    pub vuint64: u64,
    pub vchar: i8,
    pub vuchar: u8,
    pub vshort: i16,
    pub vushort: u16,
    pub vint: i32,
    pub vuint: u32,
    pub vfloat: f32,
    pub vdouble: f64,
    pub vbool: BOOL,
}

pub type binn = Option<Box<BinnStruct>>;

pub fn binn_get_type_info(
    long_type: i32,
    pstorage_type: Option<&mut i32>,
    pextra_type: Option<&mut i32>,
) -> BOOL {
    let mut storage_type;
    let mut extra_type;
    let mut retval = 1;
    let mut current_long_type = long_type;

    loop {
        if current_long_type < 0 {
            storage_type = -1;
            extra_type = -1;
            retval = 0;
            break;
        } else if current_long_type <= 0xff {
            storage_type = current_long_type & 0xE0;
            extra_type = current_long_type & 0x0F;
            break;
        } else if current_long_type <= 0xffff {
            storage_type = current_long_type & 0xE000;
            storage_type >>= 8;
            extra_type = current_long_type & 0x0FFF;
            extra_type >>= 4;
            break;
        } else if current_long_type & 0x80000 != 0 {
            current_long_type &= 0xffff;
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
pub fn zero_value(pvalue: Option<&mut dyn std::any::Any>, type_: i32) {
    if pvalue.is_none() {
        return;
    }
    let pvalue = pvalue.unwrap();

    match binn_get_read_storage(type_) {
        0x00 => (),
        0x20 => {
            if let Some(val) = pvalue.downcast_mut::<i8>() {
                *val = 0;
            }
        },
        0x40 => {
            if let Some(val) = pvalue.downcast_mut::<i16>() {
                *val = 0;
            }
        },
        0x60 => {
            if let Some(val) = pvalue.downcast_mut::<i32>() {
                *val = 0;
            }
        },
        0x80 => {
            if let Some(val) = pvalue.downcast_mut::<u64>() {
                *val = 0;
            }
        },
        0xC0 | 0xA0 | 0xE0 => {
            if let Some(val) = pvalue.downcast_mut::<Option<&mut str>>() {
                *val = None;
            }
        },
        _ => (),
    }
}
pub fn copy_int_value(
    psource: Option<&[u8]>,
    pdest: Option<&mut [u8]>,
    source_type: i32,
    dest_type: i32,
) -> bool {
    // Check for null pointers (represented as None in Rust)
    if psource.is_none() || pdest.is_none() {
        return false;
    }
    let psource = psource.unwrap();
    let pdest = pdest.unwrap();

    let mut vuint64: uint64 = 0;
    let mut local_vint64: int64 = 0;  // Renamed from vint64 to avoid shadowing static

    // Read source value based on source_type
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

    // Handle signed/unsigned conversion if needed
    if (int_type(source_type) == 22) && (int_type(dest_type) == 11) {
        if vuint64 > i64::MAX as uint64 {
            return false;
        }
        local_vint64 = vuint64 as int64;
    } else if (int_type(source_type) == 11) && (int_type(dest_type) == 22) {
        if local_vint64 < 0 {
            return false;
        }
        vuint64 = local_vint64 as uint64;
    }

    // Write to destination based on dest_type
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
    data_store: i32,
) -> bool {
    if type_family(source_type) != type_family(dest_type) {
        return false;
    }

    match type_family(source_type) {
        0xf2 if source_type != dest_type => {
            copy_int_value(psource.as_deref(), pdest, source_type, dest_type)
        }
        0xf3 if source_type != dest_type => {
            // Convert psource and pdest to appropriate float types
            let psource_f32 = psource.and_then(|src| {
                if src.len() >= std::mem::size_of::<f32>() {
                    Some(unsafe { &mut *(src.as_mut_ptr() as *mut f32) })
                } else {
                    None
                }
            });
            let pdest_f64 = pdest.and_then(|dst| {
                if dst.len() >= std::mem::size_of::<f64>() {
                    Some(unsafe { &mut *(dst.as_mut_ptr() as *mut f64) })
                } else {
                    None
                }
            });
            copy_float_value(psource_f32, pdest_f64, source_type, dest_type)
        }
        _ => copy_raw_value(psource, pdest, data_store),
    }
}
pub fn copy_be32(pdest: &mut u32, psource: &u32) {
    let source = psource.to_be_bytes();
    let dest = &mut *pdest;
    *dest = u32::from_be_bytes([source[3], source[2], source[1], source[0]]);
}
pub fn binn_save_header(item: &mut binn) -> BOOL {
    // Check for NULL pointer (Option<Box<BinnStruct>>)
    if item.is_none() {
        return 0;
    }

    // Safely unwrap the item
    let item_inner = item.as_mut().unwrap();
    
    // Get mutable reference to pbuf as u8 slice
    let pbuf_ptr = item_inner.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8;
    let pbuf_slice = unsafe { std::slice::from_raw_parts_mut(pbuf_ptr, item_inner.alloc_size as usize) };
    
    let mut p_idx = 9; // Start index at position 9
    let mut size = (item_inner.used_size - 9) + 3;

    // Handle count > 127 case
    if item_inner.count > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (item_inner.count as u32) | 0x80000000;
        let be_bytes = int32.to_be_bytes();
        pbuf_slice[p_idx..p_idx + 4].copy_from_slice(&be_bytes);
    } else {
        p_idx -= 1;
        pbuf_slice[p_idx] = item_inner.count as u8;
    }

    // Handle size > 127 case
    if size > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (size as u32) | 0x80000000;
        let be_bytes = int32.to_be_bytes();
        pbuf_slice[p_idx..p_idx + 4].copy_from_slice(&be_bytes);
    } else {
        p_idx -= 1;
        pbuf_slice[p_idx] = size as u8;
    }

    p_idx -= 1;
    pbuf_slice[p_idx] = item_inner.type_ as u8;

    // Update item struct fields
    let ptr_addr = pbuf_ptr.wrapping_add(p_idx);
    
    // Create a boxed unit and convert to raw pointer, then store it
    let boxed_unit = Box::new(());
    let raw_ptr = Box::into_raw(boxed_unit);
    // Overwrite the box's content with our pointer address
    unsafe {
        std::ptr::write(raw_ptr as *mut *mut u8, ptr_addr);
    }
    item_inner.ptr = Some(unsafe { Box::from_raw(raw_ptr) });
    
    item_inner.size = size;
    item_inner.dirty = 0;

    1
}
pub fn binn_ptr(ptr: Option<*mut u8>) -> Option<*mut u8> {
    match binn_get_ptr_type(ptr) {
        1 => {
            let item = ptr.map(|p| p as *mut binn);
            unsafe {
                if let Some(item_ptr) = item {
                    if let Some(item_ref) = item_ptr.as_mut() {
                        // Check if writable and dirty first
                        let writable = item_ref.as_ref().map(|b| b.writable != 0).unwrap_or(false);
                        let dirty = item_ref.as_ref().map(|b| b.dirty != 0).unwrap_or(false);
                        
                        if writable && dirty {
                            binn_save_header(item_ref);
                        }
                        
                        // Return the ptr field
                        return item_ref.as_ref().and_then(|b| b.ptr.as_ref().map(|p| p.as_ref() as *const () as *mut u8));
                    }
                }
                None
            }
        }
        2 => ptr,
        _ => None,
    }
}
pub fn copy_be64(pdest: &mut u64, psource: &u64) {
    let source = psource.to_be_bytes(); // Convert to big-endian byte array
    let dest = unsafe { std::slice::from_raw_parts_mut(pdest as *mut u64 as *mut u8, 8) };
    
    // Perform the byte-wise copy with endianness conversion
    for i in 0..8 {
        dest[i] = source[7 - i];
    }
}
pub fn copy_be16(pdest: &mut u16, psource: &u16) {
    let source_bytes = psource.to_be_bytes(); // Get big-endian bytes of source
    
    // Convert destination to bytes and modify directly
    let dest_ptr = pdest as *mut u16 as *mut u8;
    unsafe {
        *dest_ptr.add(0) = source_bytes[1];
        *dest_ptr.add(1) = source_bytes[0];
    }
}
pub fn IsValidBinnHeader(
    pbuf: Option<&[u8]>,
    ptype: Option<&mut i32>,
    pcount: Option<&mut i32>,
    psize: Option<&mut i32>,
    pheadersize: Option<&mut i32>,
) -> bool {
    // Check if pbuf is None (equivalent to NULL check in C)
    let pbuf = match pbuf {
        Some(buf) => buf,
        None => return false,
    };

    let mut p_idx = 0;
    let mut plimit_idx: Option<usize> = None;

    // Set plimit based on psize - use ref to borrow instead of move
    if let Some(ref psize_val) = psize {
        if **psize_val > 0 {
            let size_usize: usize = (**psize_val).try_into().unwrap_or(0);
            if size_usize > 0 && size_usize <= pbuf.len() {
                plimit_idx = Some(size_usize - 1);
            }
        }
    }

    // Check if we have at least 1 byte
    if p_idx >= pbuf.len() {
        return false;
    }

    let byte = pbuf[p_idx];
    p_idx += 1;

    // Check header format
    if (byte & 0xE0) != 0xE0 {
        return false;
    }
    if byte & 0x10 != 0 {
        return false;
    }

    let type_val = byte;

    // Validate type
    match type_val {
        0xE0 | 0xE1 | 0xE2 => (),
        _ => return false,
    }

    // Check plimit
    if let Some(plimit) = plimit_idx {
        if p_idx > plimit {
            return false;
        }
    }

    // Read first int32
    if p_idx >= pbuf.len() {
        return false;
    }

    let mut int32_val = pbuf[p_idx] as i32;
    p_idx += 1;

    if int32_val & 0x80 != 0 {
        // Check if we have enough bytes for 4-byte int
        if let Some(plimit) = plimit_idx {
            if p_idx + 3 > plimit {
                return false;
            }
        }
        if p_idx + 3 >= pbuf.len() {
            return false;
        }

        // Reconstruct the 32-bit value from bytes
        let mut source = 0u32;
        for i in 0..4 {
            source = (source << 8) | pbuf[p_idx + i] as u32;
        }
        
        let mut dest = 0u32;
        copy_be32(&mut dest, &source);
        int32_val = (dest & 0x7FFFFFFF) as i32;
        p_idx += 4;
    }

    let size = int32_val;

    // Check plimit again
    if let Some(plimit) = plimit_idx {
        if p_idx > plimit {
            return false;
        }
    }

    // Read second int32
    if p_idx >= pbuf.len() {
        return false;
    }

    let mut int32_val = pbuf[p_idx] as i32;
    p_idx += 1;

    if int32_val & 0x80 != 0 {
        // Check if we have enough bytes for 4-byte int
        if let Some(plimit) = plimit_idx {
            if p_idx + 3 > plimit {
                return false;
            }
        }
        if p_idx + 3 >= pbuf.len() {
            return false;
        }

        // Reconstruct the 32-bit value from bytes
        let mut source = 0u32;
        for i in 0..4 {
            source = (source << 8) | pbuf[p_idx + i] as u32;
        }
        
        let mut dest = 0u32;
        copy_be32(&mut dest, &source);
        int32_val = (dest & 0x7FFFFFFF) as i32;
        p_idx += 4;
    }

    let count = int32_val;

    // Validate size and count
    if size < 3 || count < 0 {
        return false;
    }

    // Set output parameters
    if let Some(pt) = ptype {
        *pt = type_val as i32;
    }

    if let Some(pc) = pcount {
        *pc = count;
    }

    if let Some(ps) = psize {
        if *ps == 0 {
            *ps = size;
        }
    }

    if let Some(phs) = pheadersize {
        *phs = p_idx as i32;
    }

    true
}
pub fn GetValue(p: Option<&[u8]>, value: Option<&mut binn>) -> BOOL {
    let Some(p) = p else {
        return 0;
    };
    
    let Some(value) = value else {
        return 0;
    };
    
    let Some(value) = value.as_mut() else {
        return 0;
    };

    // Initialize the value struct (equivalent to memset)
    *value = Box::new(BinnStruct {
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
        value: BinnValue {
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
        },
        disable_int_compression: 0,
    });

    let mut p_idx = 0;
    let p2 = p.as_ptr();
    
    if p_idx >= p.len() {
        return 0;
    }
    let byte = p[p_idx];
    p_idx += 1;
    
    let storage_type = byte & 0xE0;
    let data_type = if byte & 0x10 != 0 {
        if p_idx >= p.len() {
            return 0;
        }
        let next_byte = p[p_idx];
        p_idx += 1;
        ((byte as i32) << 8) | (next_byte as i32)
    } else {
        byte as i32
    };
    
    value.type_ = data_type;
    
    match storage_type {
        0x00 => {}
        
        0x20 => {
            if p_idx >= p.len() {
                return 0;
            }
            value.value.vuint8 = p[p_idx];
            value.ptr = Some(Box::new(()));
            p_idx += 1;
        }
        
        0x40 => {
            if p_idx + 1 >= p.len() {
                return 0;
            }
            let source = unsafe { &*((&p[p_idx]) as *const u8 as *const u16) };
            let mut temp: u16 = 0;
            copy_be16(&mut temp, source);
            value.value.vint16 = temp as i16;
            value.ptr = Some(Box::new(()));
            p_idx += 2;
        }
        
        0x60 => {
            if p_idx + 3 >= p.len() {
                return 0;
            }
            let source = unsafe { &*((&p[p_idx]) as *const u8 as *const u32) };
            let mut temp: u32 = 0;
            copy_be32(&mut temp, source);
            value.value.vint32 = temp as i32;
            value.ptr = Some(Box::new(()));
            p_idx += 4;
        }
        
        0x80 => {
            if p_idx + 7 >= p.len() {
                return 0;
            }
            let source = unsafe { &*((&p[p_idx]) as *const u8 as *const u64) };
            let mut temp: u64 = 0;
            copy_be64(&mut temp, source);
            value.value.vint64 = temp as i64;
            value.ptr = Some(Box::new(()));
            p_idx += 8;
        }
        
        0xA0 | 0xC0 => {
            if p_idx >= p.len() {
                return 0;
            }
            let mut DataSize = p[p_idx] as i32;
            
            if DataSize & 0x80 != 0 {
                if p_idx + 3 >= p.len() {
                    return 0;
                }
                let source = unsafe { &*((&p[p_idx]) as *const u8 as *const u32) };
                let mut temp: u32 = 0;
                copy_be32(&mut temp, source);
                DataSize = (temp & 0x7FFFFFFF) as i32;
                p_idx += 4;
            } else {
                p_idx += 1;
            }
            
            value.size = DataSize;
            if p_idx < p.len() {
                value.ptr = Some(Box::new(()));
            }
        }
        
        0xE0 => {
            value.ptr = Some(Box::new(()));
            let mut count = 0;
            let mut size = 0;
            if !IsValidBinnHeader(Some(p), None, Some(&mut count), Some(&mut size), None) {
                return 0;
            }
            value.count = count;
            value.size = size;
        }
        
        _ => return 0,
    }
    
    match value.type_ {
        0x01 => {
            value.type_ = 0x80061;
            value.value.vbool = 1;
            value.ptr = Some(Box::new(()));
        }
        
        0x02 => {
            value.type_ = 0x80061;
            value.value.vbool = 0;
            value.ptr = Some(Box::new(()));
        }
        
        _ => {}
    }
    
    1
}
pub fn AdvanceDataPos(p: &[u8], plimit: usize) -> Option<&[u8]> {
    let mut p_idx = 0;
    
    if p_idx > plimit {
        return Option::None;
    }
    
    if p_idx >= p.len() {
        return Option::None;
    }
    let byte = p[p_idx];
    p_idx += 1;
    
    let storage_type = byte & 0xE0;
    
    if byte & 0x10 != 0 {
        p_idx += 1;
    }
    
    match storage_type {
        0x00 => {},
        
        0x20 => {
            p_idx += 1;
        },
        
        0x40 => {
            p_idx += 2;
        },
        
        0x60 => {
            p_idx += 4;
        },
        
        0x80 => {
            p_idx += 8;
        },
        
        0xA0 | 0xC0 => {
            if p_idx > plimit {
                return Option::None;
            }
            if p_idx >= p.len() {
                return Option::None;
            }
            let mut data_size = p[p_idx] as i32;
            
            if data_size & 0x80 != 0 {
                if p_idx + 3 > plimit {
                    return Option::None;
                }
                if p_idx + 3 >= p.len() {
                    return Option::None;
                }
                let mut temp = 0u32;
                copy_be32(&mut temp, &u32::from_be_bytes([
                    p[p_idx],
                    p[p_idx + 1],
                    p[p_idx + 2],
                    p[p_idx + 3],
                ]));
                data_size = temp as i32;
                data_size &= 0x7FFFFFFF;
                p_idx += 4;
            } else {
                p_idx += 1;
            }
            
            p_idx = (p_idx as i32 + data_size) as usize;
            
            if storage_type == 0xA0 {
                p_idx += 1;
            }
        },
        
        0xE0 => {
            if p_idx > plimit {
                return Option::None;
            }
            if p_idx >= p.len() {
                return Option::None;
            }
            let mut data_size = p[p_idx] as i32;
            
            if data_size & 0x80 != 0 {
                if p_idx + 3 > plimit {
                    return Option::None;
                }
                if p_idx + 3 >= p.len() {
                    return Option::None;
                }
                let mut temp = 0u32;
                copy_be32(&mut temp, &u32::from_be_bytes([
                    p[p_idx],
                    p[p_idx + 1],
                    p[p_idx + 2],
                    p[p_idx + 3],
                ]));
                data_size = temp as i32;
                data_size &= 0x7FFFFFFF;
                p_idx += 4;
            } else {
                p_idx += 1;
                data_size &= 0x7F;
            }
            
            data_size -= 1;
            p_idx = (p_idx as i32 + data_size) as usize;
        },
        
        _ => return Option::None,
    }
    
    if p_idx > plimit {
        Option::None
    } else if p_idx >= p.len() {
        Option::None
    } else {
        Some(&p[p_idx..])
    }
}
pub fn binn_list_get_value(ptr: Option<&[u8]>, pos: i32, value: Option<&mut binn>) -> i32 {
    // Convert the slice to a raw pointer using binn_ptr
    let ptr_raw = match ptr {
        Some(slice) => {
            let ptr = slice.as_ptr() as *mut u8;
            match binn_ptr(Some(ptr)) {
                Some(p) if !p.is_null() => p,
                _ => return 0,
            }
        }
        None => return 0,
    };

    // Check for null pointers
    if value.is_none() {
        return 0;
    }

    let mut type_val = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Create a slice from the pointer for IsValidBinnHeader
    // We need to create a temporary slice for the header validation
    let ptr_slice = unsafe { std::slice::from_raw_parts(ptr_raw, 1) };

    // Validate the Binn header
    if !IsValidBinnHeader(
        Some(ptr_slice),
        Some(&mut type_val),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    // Check if it's a list type
    if type_val != 0xE0 {
        return 0;
    }

    // Check if the list is empty
    if count == 0 {
        return 0;
    }

    // Check if position is valid
    if pos <= 0 || pos > count {
        return 0;
    }

    let adjusted_pos = (pos - 1) as usize;
    let base = ptr_raw as usize;
    let plimit = base + size as usize;

    // Advance to the header position
    let mut current_ptr = unsafe { ptr_raw.add(header_size as usize) };
    let mut current_slice = unsafe { std::slice::from_raw_parts(current_ptr, (plimit - base) as usize) };

    // Advance through the list to the desired position
    for _ in 0..adjusted_pos {
        match AdvanceDataPos(current_slice, plimit) {
            Some(next_slice) => {
                current_slice = next_slice;
                current_ptr = current_slice.as_ptr() as *mut u8;
            }
            None => return 0,
        }
    }

    // Get the value at the current position
    GetValue(Some(current_slice), value) as i32
}
pub fn binn_list_get(
    ptr: Option<&[u8]>,
    pos: i32,
    type_: i32,
    mut pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
    let storage_type = binn_get_read_storage(type_);
    
    // Check if storage_type is valid and pvalue is None when storage_type != 0x00
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    // Zero out the value if pvalue exists
    if let Some(pval) = &mut pvalue {
        zero_value(Some(*pval), type_);
    }

    let mut value = None;
    if binn_list_get_value(ptr, pos, Some(&mut value)) == 0 {
        return 0;
    }

    // Unwrap the value safely
    let value = match value {
        Some(v) => v,
        None => return 0,
    };

    // Copy the value if pvalue exists
    if let Some(pval) = &mut pvalue {
        let pval_u8 = pval.downcast_mut::<Vec<u8>>().unwrap();
        if !copy_value(
            value.ptr.map(|p| unsafe { std::slice::from_raw_parts_mut(p.as_ref() as *const _ as *mut u8, value.size as usize) }),
            Some(pval_u8.as_mut_slice()),
            value.type_,
            type_,
            storage_type,
        ) {
            return 0;
        }
    }

    // Set size if psize exists
    if let Some(size_ptr) = psize {
        *size_ptr = value.size;
    }

    1
}
pub fn read_map_id(pp: &mut &[u8], plimit: &[u8]) -> Option<i32> {
    let data = *pp;
    if data.is_empty() {
        return None;
    }

    let mut p_idx = 0;
    let c = data[p_idx];
    p_idx += 1;

    let extra_bytes;
    if c & 0x80 != 0 {
        extra_bytes = (((c & 0x60) >> 5) + 1) as usize;
        if p_idx + extra_bytes > data.len() || &data[p_idx..p_idx + extra_bytes] > plimit {
            *pp = &data[data.len().min(plimit.len())..];
            return None;
        }
    }

    let type_byte = c & 0xE0;
    let mut sign;
    let mut id;

    if (c & 0x80) == 0 {
        sign = c & 0x40;
        id = (c & 0x3F) as i32;
    } else if type_byte == 0x80 {
        if p_idx + 1 > data.len() || &data[p_idx..p_idx + 1] > plimit {
            *pp = &data[data.len().min(plimit.len())..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        sign = c & 0x10;
    } else if type_byte == 0xA0 {
        if p_idx + 2 > data.len() || &data[p_idx..p_idx + 2] > plimit {
            *pp = &data[data.len().min(plimit.len())..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        sign = c & 0x10;
    } else if type_byte == 0xC0 {
        if p_idx + 3 > data.len() || &data[p_idx..p_idx + 3] > plimit {
            *pp = &data[data.len().min(plimit.len())..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (data[p_idx] as i32);
        p_idx += 1;
        sign = c & 0x10;
    } else if type_byte == 0xE0 {
        if p_idx + 4 > data.len() || &data[p_idx..p_idx + 4] > plimit {
            *pp = &data[data.len().min(plimit.len())..];
            return None;
        }
        let mut source_bytes = [0u8; 4];
        source_bytes.copy_from_slice(&data[p_idx..p_idx + 4]);
        let source_u32 = u32::from_be_bytes(source_bytes);
        id = source_u32 as i32;
        p_idx += 4;
        sign = c & 0x10;
    } else {
        *pp = &data[data.len().min(plimit.len())..];
        return None;
    }

    if sign != 0 {
        id = -id;
    }

    *pp = &data[p_idx..];
    Some(id)
}
pub fn SearchForID(p: &[u8], header_size: usize, size: usize, numitems: usize, id: i32) -> Option<&[u8]> {
    let base = p;
    let plimit = p.get(size - 1..)?;
    
    let mut current_slice = p.get(header_size..)?;
    
    for _ in 0..numitems {
        let mut temp_slice = current_slice;
        let int32 = read_map_id(&mut temp_slice, plimit)?;
        
        if temp_slice.as_ptr() > plimit.as_ptr() {
            break;
        }
        
        if int32 == id {
            return Some(temp_slice);
        }
        
        current_slice = AdvanceDataPos(temp_slice, plimit.as_ptr() as usize)?;
        
        if current_slice.is_empty() || current_slice.as_ptr() < base.as_ptr() {
            break;
        }
    }
    
    None
}
pub fn binn_map_get_value(ptr: Option<&[u8]>, id: i32, value: Option<&mut binn>) -> BOOL {
    let ptr = match ptr {
        Some(p) => p,
        None => return 0,
    };
    
    if value.is_none() {
        return 0;
    }
    
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
    
    if type_ != 0xE1 {
        return 0;
    }
    
    if count == 0 {
        return 0;
    }
    
    let result_p = SearchForID(ptr, header_size as usize, size as usize, count as usize, id);
    
    match result_p {
        Some(p) => GetValue(Some(p), value),
        None => 0,
    }
}
pub fn binn_map_get(
    ptr: Option<&[u8]>,
    id: i32,
    type_: i32,
    mut pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
    let storage_type = binn_get_read_storage(type_);
    
    // Check if storage_type is valid and pvalue is None when storage_type != 0x00
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    // Zero out the value if pvalue exists
    if let Some(ref mut pval) = pvalue {
        zero_value(Some(*pval), type_);
    }

    let mut value = None;
    if binn_map_get_value(ptr, id, Some(&mut value)) == 0 {
        return 0;
    }

    // Unwrap the value for copying
    if let Some(ref mut val) = value {
        if copy_value(
            val.ptr.as_ref().map(|p| unsafe { 
                std::slice::from_raw_parts_mut(p.as_ref() as *const () as *mut u8, val.size as usize) 
            }),
            pvalue.and_then(|v| v.downcast_mut::<Vec<u8>>()).map(|v| &mut v[..]),
            val.type_,
            type_,
            storage_type,
        ) == false {
            return 0;
        }

        // Update size if psize exists
        if let Some(size_ptr) = psize {
            *size_ptr = val.size;
        }
    } else {
        return 0;
    }

    1
}
pub fn SearchForKey<'a>(
    p: Option<&'a [u8]>,
    header_size: usize,
    size: usize,
    numitems: i32,
    key: Option<&str>,
) -> Option<&'a [u8]> {
    let p = p?;
    let key = key?;

    let base = p.as_ptr();
    let plimit = p.as_ptr().wrapping_add(size).wrapping_sub(1);
    let mut current_ptr = p.as_ptr().wrapping_add(header_size);
    let keylen = key.len();
    
    for _ in 0..numitems {
        if current_ptr > plimit || current_ptr < base {
            break;
        }
        
        // Calculate current position in the slice
        let current_pos = current_ptr as usize - base as usize;
        if current_pos >= p.len() {
            break;
        }
        
        // Read the length byte
        let len = p[current_pos] as usize;
        current_ptr = current_ptr.wrapping_add(1);
        
        if current_ptr > plimit || current_ptr < base {
            break;
        }
        
        let current_pos = current_ptr as usize - base as usize;
        
        if len > 0 {
            // Check if we have enough data for the key comparison
            if current_pos + len > p.len() {
                break;
            }
            
            // Compare the slice with the key (case-insensitive)
            let slice = &p[current_pos..current_pos + len];
            if slice.len() == keylen && slice.eq_ignore_ascii_case(key.as_bytes()) {
                current_ptr = current_ptr.wrapping_add(len);
                let result_pos = current_ptr as usize - base as usize;
                if result_pos < p.len() {
                    return Some(&p[result_pos..]);
                }
                break;
            }
            
            current_ptr = current_ptr.wrapping_add(len);
            if current_ptr > plimit || current_ptr < base {
                break;
            }
        } else {
            // Handle zero-length key case - match if key is also zero length
            if keylen == 0 {
                let result_pos = current_ptr as usize - base as usize;
                if result_pos < p.len() {
                    return Some(&p[result_pos..]);
                }
                break;
            }
        }
        
        // Calculate remaining slice for AdvanceDataPos
        let current_pos = current_ptr as usize - base as usize;
        if current_pos >= p.len() {
            break;
        }
        
        let remaining = &p[current_pos..];
        let advanced = AdvanceDataPos(remaining, (plimit as usize).saturating_sub(current_pos));
        
        // Update current_ptr based on the advanced position
        if let Some(advanced_slice) = advanced {
            let advanced_pos = advanced_slice.as_ptr() as usize - base as usize;
            if advanced_pos >= p.len() {
                break;
            }
            
            current_ptr = p.as_ptr().wrapping_add(advanced_pos);
            
            if current_ptr > plimit || current_ptr < base {
                break;
            }
        } else {
            break;
        }
    }
    
    Option::None
}
pub fn binn_object_get_value(ptr: Option<&[u8]>, key: Option<&str>, value: Option<&mut binn>) -> BOOL {
    // Check for null parameters
    if ptr.is_none() || key.is_none() || value.is_none() {
        return 0;
    }
    
    let ptr = ptr.unwrap();
    let key = key.unwrap();
    let value = value.unwrap();
    
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
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
    
    // Check if type is object (0xE2)
    if type_ != 0xE2 {
        return 0;
    }
    
    // Check if count is valid
    if count == 0 {
        return 0;
    }
    
    // Search for the key in the object
    let p_found = SearchForKey(Some(ptr), header_size as usize, size as usize, count, Some(key));
    if p_found.is_none() {
        return 0;
    }
    
    // Get the value
    GetValue(p_found, Some(value))
}
pub fn binn_object_get(
    ptr: Option<&[u8]>,
    key: Option<&str>,
    type_: i32,
    mut pvalue: Option<&mut dyn Any>,
    psize: Option<&mut i32>,
) -> i32 {
    let storage_type = binn_get_read_storage(type_);
    
    if storage_type != 0x00 && pvalue.is_none() {
        return 0;
    }

    if let Some(ref mut pval) = pvalue {
        zero_value(Some(*pval), type_);
    }

    let mut value: Option<Box<BinnStruct>> = None;
    if binn_object_get_value(ptr, key, Some(&mut value)) == 0 {
        return 0;
    }

    let value_ref = match value {
        Some(ref v) => v,
        None => return 0,
    };

    let ptr_slice = value_ref.ptr.as_ref().map(|p| unsafe {
        std::slice::from_raw_parts(Box::as_ref(p) as *const () as *const u8, value_ref.size as usize)
    });

    let dest_slice = pvalue.and_then(|pv| pv.downcast_mut::<Vec<u8>>());

    let copy_success = copy_value(
        ptr_slice.map(|s| unsafe { std::slice::from_raw_parts_mut(s.as_ptr() as *mut u8, s.len()) }),
        dest_slice.map(|v| &mut v[..]),
        value_ref.type_,
        type_,
        storage_type,
    );

    if !copy_success {
        return 0;
    }

    if let Some(size_ptr) = psize {
        *size_ptr = value_ref.size;
    }

    1
}
pub fn binn_is_valid_ex(
    ptr: Option<*mut u8>,
    mut ptype: Option<&mut i32>,
    mut pcount: Option<&mut i32>,
    mut psize: Option<&mut i32>,
) -> bool {
    let pbuf = binn_ptr(ptr);
    if pbuf.is_none() {
        return false;
    }
    let pbuf_ptr = pbuf.unwrap();
    
    // Get size from parameter if provided and > 0
    let size = if let Some(ps) = psize.as_ref() {
        if **ps > 0 { **ps } else { 0 }
    } else {
        0
    };
    
    let mut type_val = 0;
    let mut count_val = 0;
    let mut size_val = 0;
    let mut header_size_val = 0;
    
    // Create mutable references for IsValidBinnHeader
    let mut ptype_mut = Some(&mut type_val);
    let mut pcount_mut = Some(&mut count_val);
    let mut psize_mut = Some(&mut size_val);
    let mut pheadersize_mut = Some(&mut header_size_val);
    
    // Convert raw pointer to slice for safe access
    let pbuf_slice = unsafe { 
        if size > 0 {
            std::slice::from_raw_parts(pbuf_ptr as *const u8, size as usize)
        } else {
            // If size is 0, we can't create a valid slice, use minimal access
            std::slice::from_raw_parts(pbuf_ptr as *const u8, 1)
        }
    };
    
    if !IsValidBinnHeader(
        Some(pbuf_slice),
        ptype_mut,
        pcount_mut,
        psize_mut,
        pheadersize_mut,
    ) {
        return false;
    }
    
    // Check size parameter if provided and > 0
    if let Some(ps) = psize.as_ref() {
        if **ps > 0 && size_val != **ps {
            return false;
        }
    }
    
    // Check count parameter if provided and > 0
    if let Some(pc) = pcount.as_ref() {
        if **pc > 0 && count_val != **pc {
            return false;
        }
    }
    
    // Check type parameter if provided and != 0
    if let Some(pt) = ptype.as_ref() {
        if **pt != 0 && type_val != **pt {
            return false;
        }
    }
    
    // Process each element
    let mut current_pos = header_size_val as usize;
    for _ in 0..count_val {
        if current_pos >= pbuf_slice.len() {
            return false;
        }
        
        let remaining_slice = &pbuf_slice[current_pos..];
        
        match type_val {
            0xE2 => {
                if remaining_slice.is_empty() {
                    return false;
                }
                let len = remaining_slice[0] as usize;
                current_pos += 1;
                if current_pos + len > pbuf_slice.len() {
                    return false;
                }
                current_pos += len;
            }
            0xE1 => {
                let mut slice_ref = remaining_slice;
                if read_map_id(&mut slice_ref, pbuf_slice).is_none() {
                    return false;
                }
                current_pos = pbuf_slice.len() - slice_ref.len();
            }
            _ => {}
        }
        
        // Advance data position
        let advanced = AdvanceDataPos(&pbuf_slice[current_pos..], pbuf_slice.len());
        if advanced.is_none() {
            return false;
        }
        let new_slice = advanced.unwrap();
        let new_pos = pbuf_slice.len() - new_slice.len();
        
        if new_pos > pbuf_slice.len() || new_pos < current_pos {
            return false;
        }
        current_pos = new_pos;
    }
    
    // Update output parameters if they exist and have value 0
    if let Some(pt) = ptype.as_mut() {
        if **pt == 0 {
            **pt = type_val;
        }
    }
    
    if let Some(pc) = pcount.as_mut() {
        if **pc == 0 {
            **pc = count_val;
        }
    }
    
    if let Some(ps) = psize.as_mut() {
        if **ps == 0 {
            **ps = size_val;
        }
    }
    
    true
}
pub fn atoi64(str: Option<&str>) -> Option<int64> {
    // Check for None (equivalent to NULL pointer in C)
    if str.is_none() {
        return None;
    }
    
    let mut str = str.unwrap(); // Safe to unwrap after checking
    let mut retval: int64 = 0;
    let mut is_negative = false;
    
    // Check if the string starts with '-'
    if let Some(first_char) = str.chars().next() {
        if first_char == '-' {
            is_negative = true;
            // Skip the '-' character
            str = &str[1..];
        }
    }
    
    // Iterate through each character in the string
    for c in str.chars() {
        // Convert character to digit
        if let Some(digit) = c.to_digit(10) {
            retval = (10 * retval) + (digit as int64);
        } else {
            // If non-digit character is found, break early (C version would continue)
            break;
        }
    }
    
    // Apply negative sign if needed
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
pub fn binn_is_container(item: binn) -> BOOL {
    // Check if item is None (equivalent to NULL in C)
    if item.is_none() {
        return 0;
    }

    // Unwrap the Option safely
    let item = item.unwrap();

    // Match on the type field (equivalent to switch in C)
    match item.type_ {
        0xE0 | 0xE1 | 0xE2 => 1,  // Return 1 for container types
        _ => 0,                    // Return 0 for all other types
    }
}
pub fn binn_is_valid(
    ptr: Option<*mut u8>,
    mut ptype: Option<&mut i32>,
    mut pcount: Option<&mut i32>,
    mut psize: Option<&mut i32>,
) -> bool {
    // Set default values if the Option references are Some
    if let Some(ref mut pt) = ptype {
        **pt = 0;
    }
    if let Some(ref mut pc) = pcount {
        **pc = 0;
    }
    if let Some(ref mut ps) = psize {
        **ps = 0;
    }

    // Call the extended validation function
    binn_is_valid_ex(ptr, ptype, pcount, psize)
}
pub fn binn_list_int8(list: Option<&[u8]>, pos: i32) -> Option<i8> {
    let mut value: i8 = 0;
    let success = binn_list_get(
        list,
        pos,
        0x21,
        Some(&mut value as &mut dyn std::any::Any),
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
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    binn_list_get(list, pos, 0x41, pvalue, None);
    value
}
pub fn binn_list_int32(list: Option<&[u8]>, pos: i32) -> i32 {
    let mut value = 0;
    binn_list_get(list, pos, 0x61, Some(&mut value), None);
    value
}
pub fn binn_list_uint8(list: Option<&[u8]>, pos: i32) -> Option<u8> {
    let mut value: u8 = 0;
    let success = binn_list_get(
        list,
        pos,
        0x20,
        Some(&mut value as &mut dyn std::any::Any),
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
        Some(&mut value as &mut dyn std::any::Any),
        None,
    );
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_list_uint32(list: Option<&[u8]>, pos: i32) -> u32 {
    let mut value: u32 = 0;
    binn_list_get(list, pos, 0x60, Some(&mut value), None);
    value
}
pub fn binn_list_float(list: Option<&[u8]>, pos: i32) -> f32 {
    let mut value: f32 = 0.0;
    binn_list_get(list, pos, 0x62, Some(&mut value), None);
    value
}
pub fn binn_list_double(list: Option<&[u8]>, pos: i32) -> f64 {
    let mut value: f64 = 0.0;
    binn_list_get(list, pos, 0x82, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_list_null(list: Option<&[u8]>, pos: i32) -> BOOL {
    binn_list_get(list, pos, 0x00, None, None)
}
pub fn binn_list_str(list: Option<&[u8]>, pos: i32) -> Option<String> {
    let mut value: Option<String> = None;
    let success = binn_list_get(
        list,
        pos,
        0xA0,
        Some(&mut value as &mut dyn std::any::Any),
        None,
    );

    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_list_blob(
    list: Option<&[u8]>,
    pos: i32,
    psize: Option<&mut i32>,
) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let success = binn_list_get(
        list,
        pos,
        0xC0,
        Some(&mut value),
        psize,
    );
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_list_list(list: Option<&[u8]>, pos: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let mut raw_value: Option<&mut dyn std::any::Any> = None;
    let success = binn_list_get(
        list,
        pos,
        0xE0,
        Some(&mut raw_value),
        None,
    );
    
    if success != 0 {
        raw_value.map(|v| Box::new(v) as Box<dyn std::any::Any>)
    } else {
        None
    }
}
pub fn binn_list_map(list: Option<&[u8]>, pos: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let pvalue: Option<&mut dyn std::any::Any> = value.as_mut().map(|v| v.as_mut());
    
    let success = binn_list_get(list, pos, 0xE1, pvalue, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_list_object(list: Option<&[u8]>, pos: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let success = binn_list_get(
        list,
        pos,
        0xE2,
        value.as_mut().map(|v| v as &mut dyn std::any::Any),
        None,
    );
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_map_int8(map: Option<&[u8]>, id: i32) -> Option<i8> {
    let mut value: i8 = 0;
    let success = binn_map_get(map, id, 0x21, Some(&mut value as &mut dyn std::any::Any), None);
    
    if success != 0 {
        Some(value)
    } else {
        Option::None
    }
}
pub fn binn_map_int16(map: Option<&[u8]>, id: i32) -> i16 {
    let mut value: i16 = 0;
    let _ = binn_map_get(map, id, 0x41, Some(&mut value), None);
    value
}
pub fn binn_map_int32(map: Option<&[u8]>, id: i32) -> i32 {
    let mut value: i32 = 0;
    binn_map_get(map, id, 0x61, Some(&mut value), None);
    value
}
pub fn binn_map_uint8(map: Option<&[u8]>, id: i32) -> Option<u8> {
    let mut value: u8 = 0;
    let success = binn_map_get(map, id, 0x20, Some(&mut value), None);
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_map_uint16(map: Option<&[u8]>, id: i32) -> u16 {
    let mut value: u16 = 0;
    binn_map_get(map, id, 0x40, Some(&mut value), None);
    value
}
pub fn binn_map_uint32(map: Option<&[u8]>, id: i32) -> u32 {
    let mut value: u32 = 0;
    let _ = binn_map_get(map, id, 0x60, Some(&mut value), None);
    value
}
pub fn binn_map_float(map: Option<&[u8]>, id: i32) -> f32 {
    let mut value: f32 = 0.0;
    binn_map_get(map, id, 0x62, Some(&mut value), None);
    value
}
pub fn binn_map_double(map: Option<&[u8]>, id: i32) -> f64 {
    let mut value: f64 = 0.0;
    binn_map_get(map, id, 0x82, Some(&mut value), None);
    value
}
pub fn binn_map_null(map: Option<&[u8]>, id: i32) -> BOOL {
    binn_map_get(map, id, 0x00, None, None)
}
pub fn binn_map_str(map: Option<&[u8]>, id: i32) -> Option<String> {
    let mut value: Option<String> = None;
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    
    let success = binn_map_get(map, id, 0xA0, pvalue, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_map_blob(
    map: Option<&[u8]>,
    id: i32,
    psize: Option<&mut i32>,
) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let success = binn_map_get(
        map,
        id,
        0xC0,
        Some(&mut value),
        psize,
    );
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_map_list(map: Option<&[u8]>, id: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let pvalue: Option<&mut dyn std::any::Any> = value.as_mut().map(|v| v.as_mut());
    binn_map_get(map, id, 0xE0, pvalue, None);
    value
}
pub fn binn_map_map(map: Option<&[u8]>, id: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let pvalue: Option<&mut dyn std::any::Any> = value.as_mut().map(|v| v.as_mut() as _);
    let success = binn_map_get(map, id, 0xE1, pvalue, None);
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_map_object(map: Option<&[u8]>, id: i32) -> Option<Box<dyn std::any::Any>> {
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let success = binn_map_get(
        map,
        id,
        0xE2,
        value.as_mut().map(|v| v.as_mut() as &mut dyn std::any::Any),
        None,
    );
    
    if success != 0 {
        value
    } else {
        None
    }
}
pub fn binn_object_int8(obj: Option<&[u8]>, key: Option<&str>) -> Option<i8> {
    let mut value: i8 = 0;
    let result = binn_object_get(
        obj,
        key,
        0x21,
        Some(&mut value as &mut dyn std::any::Any),
        None,
    );
    
    if result == 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_object_int16(obj: Option<&[u8]>, key: Option<&str>) -> i16 {
    let mut value: i16 = 0;
    binn_object_get(obj, key, 0x41, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_int32(obj: Option<&[u8]>, key: Option<&str>) -> i32 {
    let mut value = 0;
    binn_object_get(obj, key, 0x61, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint8(obj: Option<&[u8]>, key: Option<&str>) -> u8 {
    let mut value: u8 = 0;
    binn_object_get(obj, key, 0x20, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint16(obj: Option<&[u8]>, key: Option<&str>) -> u16 {
    let mut value: u16 = 0;
    binn_object_get(obj, key, 0x40, Some(&mut value), None);
    value
}
pub fn binn_object_uint32(obj: Option<&[u8]>, key: Option<&str>) -> u32 {
    let mut value: u32 = 0;
    binn_object_get(obj, key, 0x60, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_float(obj: Option<&[u8]>, key: Option<&str>) -> f32 {
    let mut value: f32 = 0.0;
    binn_object_get(obj, key, 0x62, Some(&mut value), None);
    value
}
pub fn binn_object_double(obj: Option<&[u8]>, key: Option<&str>) -> f64 {
    let mut value: f64 = 0.0;
    binn_object_get(obj, key, 0x82, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_null(obj: Option<&[u8]>, key: Option<&str>) -> bool {
    binn_object_get(obj, key, 0x00, None, None) != 0
}
pub fn binn_object_str(obj: Option<&[u8]>, key: Option<&str>) -> Option<String> {
    let mut value: Option<String> = None;
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    
    let result = binn_object_get(obj, key, 0xA0, pvalue, None);
    
    if result == 0 {
        value
    } else {
        None
    }
}
pub fn binn_object_blob(
    obj: Option<&[u8]>,
    key: Option<&str>,
    psize: Option<&mut i32>,
) -> Option<Box<dyn Any>> {
    let mut value: Option<Box<dyn Any>> = None;
    let mut any_value: Option<&mut dyn Any> = None;
    
    if let Some(ref mut boxed) = value {
        any_value = Some(boxed.as_mut());
    }
    
    // Call binn_object_get with the appropriate parameters
    binn_object_get(obj, key, 0xC0, any_value, psize);
    
    value
}
pub fn binn_object_list(obj: Option<&[u8]>, key: Option<&str>) -> Option<Box<dyn Any>> {
    let mut value: Option<Box<dyn Any>> = None;
    let pvalue: Option<&mut dyn Any> = value.as_mut().map(|v| v.as_mut());
    
    binn_object_get(obj, key, 0xE0, pvalue, None);
    value
}
pub fn binn_object_map(obj: Option<&[u8]>, key: Option<&str>) -> Option<Box<dyn Any>> {
    let mut value: Option<Box<dyn Any>> = None;
    let pvalue: Option<&mut dyn Any> = value.as_mut().map(|v| v.as_mut());
    
    // Call binn_object_get with the appropriate parameters
    binn_object_get(obj, key, 0xE1, pvalue, None);
    
    value
}
pub fn binn_object_object(obj: Option<&[u8]>, key: Option<&str>) -> Option<Box<dyn Any>> {
    let mut value: Option<Box<dyn Any>> = None;
    let pvalue: Option<&mut dyn Any> = value.as_mut().map(|v| v.as_mut());
    
    let result = binn_object_get(obj, key, 0xE2, pvalue, None);
    
    if result == 0 {
        value
    } else {
        None
    }
}


pub fn check_alloc_functions() {
    {
        let mut malloc_fn = MALLOC_FN.lock().unwrap();
        if malloc_fn.is_none() {
            *malloc_fn = Some(malloc);
        }
    }
    
    {
        let mut realloc_fn = REALLOC_FN.lock().unwrap();
        if realloc_fn.is_none() {
            *realloc_fn = Some(ReallocFnWrapper(Box::new(realloc)));
        }
    }
    
    {
        let mut free_fn = FREE_FN.lock().unwrap();
        if free_fn.is_none() {
            *free_fn = Some(FreeFnWrapper(Box::new(free)));
        }
    }
}

// Placeholder functions - these would need to be implemented
fn malloc(size: usize) -> Option<Box<dyn std::any::Any>> {
    // Implementation would go here
    None
}

fn realloc(ptr: Option<Box<[u8]>>, new_size: usize) -> Option<Box<[u8]>> {
    // Implementation would go here
    None
}

fn free(_ptr: Option<Box<dyn std::any::Any + Send>>) {
    // Implementation would go here
}
pub fn binn_malloc(size: i32) -> Option<Box<dyn std::any::Any>> {
    check_alloc_functions();
    let malloc_fn = MALLOC_FN.lock().unwrap();
    match *malloc_fn {
        Some(f) => f(size as usize),
        None => None,
    }
}
pub fn binn_memdup(src: Option<&[u8]>, size: i32) -> Option<Box<[u8]>> {
    // Check for NULL pointer or invalid size
    if src.is_none() || size <= 0 {
        return None;
    }
    
    let src_slice = src.unwrap();
    
    // Allocate memory using binn_malloc
    let dest = binn_malloc(size);
    if dest.is_none() {
        return None;
    }
    
    // Convert the Box<dyn Any> to a raw pointer
    let dest_box = dest.unwrap();
    let ptr = Box::into_raw(dest_box) as *mut u8;
    
    // Copy the bytes from source to destination
    unsafe {
        std::ptr::copy_nonoverlapping(src_slice.as_ptr(), ptr, size as usize);
    }
    
    // Convert back to Box<[u8]>
    let slice_ptr = std::ptr::slice_from_raw_parts_mut(ptr, size as usize);
    unsafe { Some(Box::from_raw(slice_ptr)) }
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
    // Check if the input is None (equivalent to NULL pointer in C)
    let Some(mut p) = p else {
        return 0;
    };

    // Handle negative sign
    if p.starts_with('-') {
        // Skip the negative sign by getting the substring after it
        p = &p[1..];
    }

    // Check if string is empty after removing negative sign
    if p.is_empty() {
        return 0;
    }

    // Check if all remaining characters are digits
    for c in p.chars() {
        if !c.is_ascii_digit() {
            return 0;
        }
    }

    1
}
pub fn is_float(p: Option<&str>) -> BOOL {
    // Check for NULL pointer equivalent
    let Some(p_str) = p else {
        return 0;
    };
    
    let mut chars = p_str.chars();
    let mut number_found = 0;
    let mut retval = 1;
    
    // Handle optional minus sign
    let mut first_char = chars.next();
    if first_char == Some('-') {
        first_char = chars.next();
    }
    
    // Check if string is empty after minus sign
    if first_char.is_none() {
        return 0;
    }
    
    // Process the remaining characters
    let mut iter = first_char.into_iter().chain(chars);
    while let Some(c) = iter.next() {
        if c == '.' || c == ',' {
            if number_found == 0 {
                retval = 0;
            }
        } else if c >= '0' && c <= '9' {
            number_found = 1;
        } else {
            return 0;
        }
    }
    
    retval
}
pub fn binn_alloc_item() -> Option<Box<BinnStruct>> {
    let item_ptr = binn_malloc(mem::size_of::<BinnStruct>() as i32)?;
    
    // SAFETY: We just allocated memory for BinnStruct and need to initialize it
    let item = unsafe {
        let mut item_box = item_ptr.downcast::<BinnStruct>().ok()?;
        
        // Initialize all fields to zero
        *item_box = mem::zeroed();
        
        // Set specific fields
        item_box.header = 0x1F22B11F;
        item_box.allocated = 1;
        
        item_box
    };
    
    Some(item)
}
pub fn binn_value(
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
    freefn: Option<Box<dyn FnMut(Option<Box<()>>)>>,
) -> Option<Box<BinnStruct>> {
    let mut storage_type = 0;
    let mut item = binn_alloc_item()?;

    {
        item.type_ = type_;
        binn_get_type_info(type_, Some(&mut storage_type), None);
    }

    match storage_type {
        0x00 => (),

        0xA0 | 0xC0 | 0xE0 => {
            let mut size = size;
            let pvalue = pvalue?;

            if storage_type == 0xA0 && size == 0 {
                let c_str = unsafe { CStr::from_ptr(pvalue.as_ptr() as *const i8) };
                size = c_str.to_bytes().len() as i32 + 1;
            }

            if freefn.is_none() {
                let dup = binn_memdup(Some(pvalue), size)?;
                let holder = Box::new(dup);
                let raw_ptr = Box::into_raw(holder) as *mut ();
                item.ptr = Some(unsafe { Box::from_raw(raw_ptr) });
                item.freefn = Some(Box::new(move |ptr: Option<Box<()>>| {
                    if let Some(ptr) = ptr {
                        let raw_ptr = Box::into_raw(ptr) as *mut Box<[u8]>;
                        unsafe { Box::from_raw(raw_ptr); }
                    }
                }));
                
                if storage_type == 0xA0 {
                    size -= 1;
                }
            } else {
                let vec = pvalue.to_vec();
                let holder = Box::new(vec);
                let raw_ptr = Box::into_raw(holder) as *mut ();
                item.ptr = Some(unsafe { Box::from_raw(raw_ptr) });
                item.freefn = freefn;
            }
            item.size = size;
        }

        _ => {
            item.ptr = None;
            let source_slice = unsafe {
                std::slice::from_raw_parts(pvalue?.as_ptr() as *const u8, pvalue?.len())
            };
            let dest_slice = unsafe {
                std::slice::from_raw_parts_mut(
                    &mut item.value.vint32 as *mut i32 as *mut u8,
                    std::mem::size_of::<i32>(),
                )
            };
            copy_raw_value(
                Some(&mut source_slice.to_owned()),
                Some(&mut dest_slice.to_owned()),
                storage_type,
            );
        }
    }

    Some(item)
}
pub fn compress_int<'a>(
    pstorage_type: &mut i32,
    ptype: &mut i32,
    psource: &'a [u8],
) -> Option<&'a [u8]> {
	println!("\n* compress_int");
    let storage_type = *pstorage_type;
    if storage_type == 0x20 {
        return Some(psource);
    }

    let type_ = *ptype;
    let mut type2 = 0;
    let mut vint: i64 = 0;
    let mut vuint: u64 = 0;

    match type_ {
        0x81 => {
            vint = i64::from_le_bytes(psource[..8].try_into().unwrap());
            // fall through to loc_signed
        }
        0x61 => {
            vint = i32::from_le_bytes(psource[..4].try_into().unwrap()) as i64;
            // fall through to loc_signed
        }
        0x41 => {
            vint = i16::from_le_bytes(psource[..2].try_into().unwrap()) as i64;
            // fall through to loc_signed
        }
        0x80 => {
            vuint = u64::from_le_bytes(psource[..8].try_into().unwrap());
            // fall through to loc_positive
        }
        0x60 => {
            vuint = u32::from_le_bytes(psource[..4].try_into().unwrap()) as u64;
            // fall through to loc_positive
        }
        0x40 => {
            vuint = u16::from_le_bytes(psource[..2].try_into().unwrap()) as u64;
            // fall through to loc_positive
        }
        _ => return None,
    }

    // loc_signed:
    if type_ == 0x81 || type_ == 0x61 || type_ == 0x41 {
        if vint >= 0 {
            vuint = vint as u64;
            // fall through to loc_positive
        } else {
            if vint >= i8::MIN as i64 {
                type2 = 0x21;
            } else if vint >= i16::MIN as i64 {
                type2 = 0x41;
            } else if vint >= i32::MIN as i64 {
                type2 = 0x61;
            }
            // goto loc_exit
            return handle_type_change(pstorage_type, ptype, type2, type_, psource);
        }
    }

    // loc_positive:
    if vuint <= u8::MAX as u64 {
        type2 = 0x20;
    } else if vuint <= u16::MAX as u64 {
        type2 = 0x40;
    } else if vuint <= u32::MAX as u64 {
        type2 = 0x60;
    }

    // loc_exit:
    handle_type_change(pstorage_type, ptype, type2, type_, psource)
}

fn handle_type_change<'a>(
    pstorage_type: &mut i32,
    ptype: &mut i32,
    type2: i32,
    original_type: i32,
    psource: &'a [u8],
) -> Option<&'a [u8]> {
	println!("\n* handle_type_change");
    if type2 != 0 && type2 != original_type {
        *ptype = type2;
        let storage_type2 = binn_get_write_storage(type2);
        *pstorage_type = storage_type2;
    }
    Some(psource)
}


pub fn CheckAllocation(item: &mut binn, add_size: i32) -> BOOL {
    let item_struct = match item {
        Some(boxed) => boxed.as_mut(),
        None => return 0,
    };
    
    if (item_struct.used_size + add_size) > item_struct.alloc_size {
        if item_struct.pre_allocated != 0 {
            return 0;
        }
        
        let alloc_size = CalcAllocation(item_struct.used_size + add_size, item_struct.alloc_size);
        
        let mut realloc_fn_guard = REALLOC_FN.lock().unwrap();
        let realloc_fn = match realloc_fn_guard.as_mut() {
            Some(wrapper) => &mut wrapper.0,
            None => return 0,
        };
        
        // Convert pbuf from Option<Box<()>> to Option<Box<[u8]>>
        let current_buf = item_struct.pbuf.take().map(|b| {
            let ptr = Box::into_raw(b);
            unsafe {
                Box::from_raw(std::slice::from_raw_parts_mut(ptr as *mut u8, item_struct.alloc_size as usize))
            }
        });
        
        let new_buf = realloc_fn(current_buf, alloc_size as usize);
        
        match new_buf {
            Some(buf) => {
                // Convert back from Box<[u8]> to Box<()>
                let boxed_unit: Box<()> = unsafe { Box::from_raw(Box::into_raw(buf) as *mut ()) };
                item_struct.pbuf = Some(boxed_unit);
                item_struct.alloc_size = alloc_size;
                1
            }
            None => {
                // The realloc function failed and the original buffer was consumed.
                // We cannot restore it, so leave pbuf as None.
                0
            }
        }
    } else {
        1
    }
}
pub fn AddValue(
    item: &mut binn,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    let mut int32: i32 = 0;
    let mut ArgSize: i32 = 0;
    let mut storage_type: i32 = 0;
    let mut extra_type: i32 = 0;
    
    binn_get_type_info(type_, Some(&mut storage_type), Some(&mut extra_type));
    
    if pvalue.is_none() {
        match storage_type {
            0x00 => {},
            0xC0 | 0xA0 => {
                if size == 0 {
                    // Allow empty strings/blobs when pvalue is None
                } else {
                    return 0;
                }
            },
            _ => return 0,
        }
    }
    
    let mut compressed_ptr: Option<&[u8]> = None;
    let mut compressed_storage_type = storage_type;
    let mut compressed_type = type_;
    
    if (type_family(type_) == 0xf2) && (item.as_ref().unwrap().disable_int_compression == 0) {
        if let Some(pvalue_data) = pvalue {
            compressed_ptr = compress_int(
                &mut compressed_storage_type,
                &mut compressed_type,
                pvalue_data,
            );
        }
    }
    
    let effective_storage_type = if compressed_ptr.is_some() {
        compressed_storage_type
    } else {
        storage_type
    };
    
    let effective_type = if compressed_ptr.is_some() {
        compressed_type
    } else {
        type_
    };
    
    let effective_pvalue = if compressed_ptr.is_some() {
        compressed_ptr
    } else {
        pvalue
    };
    
    let mut final_size = size;
    match effective_storage_type {
        0x00 => {
            final_size = 0;
            ArgSize = final_size;
        },
        0x20 => {
            final_size = 1;
            ArgSize = final_size;
        },
        0x40 => {
            final_size = 2;
            ArgSize = final_size;
        },
        0x60 => {
            final_size = 4;
            ArgSize = final_size;
        },
        0x80 => {
            final_size = 8;
            ArgSize = final_size;
        },
        0xC0 => {
            if size < 0 {
                return 0;
            }
            ArgSize = size + 4;
        },
        0xA0 => {
            if size < 0 {
                return 0;
            }
            if size == 0 {
                if let Some(pvalue_data) = effective_pvalue {
                    final_size = strlen2(std::str::from_utf8(pvalue_data).ok()) as i32;
                } else {
                    final_size = 0;
                }
            }
            ArgSize = final_size + 5;
        },
        0xE0 => {
            if size <= 0 {
                return 0;
            }
            ArgSize = size;
        },
        _ => return 0,
    }
    
    ArgSize += 2;
    if CheckAllocation(item, ArgSize) == 0 {
        return 0;
    }
    
    let item_ref = item.as_mut().unwrap();
    let pbuf_ptr = item_ref.pbuf.as_ref().unwrap().as_ref() as *const _ as *mut u8;
    let p = unsafe { pbuf_ptr.add(item_ref.used_size as usize) };
    
    if effective_storage_type != 0xE0 {
        if effective_type > 255 {
            let type16 = effective_type as u16;
            let mut p_type = p as *mut u16;
            unsafe {
                copy_be16(&mut *p_type, &type16);
            }
            item_ref.used_size += 2;
        } else {
            unsafe {
                *p = effective_type as u8;
            }
            item_ref.used_size += 1;
        }
    }
    
    match effective_storage_type {
        0x00 => {},
        0x20 => {
            if let Some(pvalue_data) = effective_pvalue {
                unsafe {
                    ptr::copy_nonoverlapping(pvalue_data.as_ptr(), p, 1);
                }
            }
            item_ref.used_size += 1;
        },
        0x40 => {
            if let Some(pvalue_data) = effective_pvalue {
                let mut p_dest = p as *mut u16;
                let p_src = pvalue_data.as_ptr() as *const u16;
                unsafe {
                    copy_be16(&mut *p_dest, &*p_src);
                }
            }
            item_ref.used_size += 2;
        },
        0x60 => {
            if let Some(pvalue_data) = effective_pvalue {
                let mut p_dest = p as *mut u32;
                let p_src = pvalue_data.as_ptr() as *const u32;
                unsafe {
                    copy_be32(&mut *p_dest, &*p_src);
                }
            }
            item_ref.used_size += 4;
        },
        0x80 => {
            if let Some(pvalue_data) = effective_pvalue {
                let mut p_dest = p as *mut u64;
                let p_src = pvalue_data.as_ptr() as *const u64;
                unsafe {
                    copy_be64(&mut *p_dest, &*p_src);
                }
            }
            item_ref.used_size += 8;
        },
        0xC0 | 0xA0 => {
            let mut current_p = p;
            
            if final_size > 127 {
                int32 = final_size | 0x80000000u32 as i32;
                let mut p_int32 = current_p as *mut u32;
                unsafe {
                    copy_be32(&mut *p_int32, &(int32 as u32));
                }
                current_p = unsafe { current_p.add(4) };
                item_ref.used_size += 4;
            } else {
                unsafe {
                    *current_p = final_size as u8;
                }
                current_p = unsafe { current_p.add(1) };
                item_ref.used_size += 1;
            }
            
            if let Some(pvalue_data) = effective_pvalue {
                unsafe {
                    ptr::copy_nonoverlapping(
                        pvalue_data.as_ptr(),
                        current_p,
                        final_size as usize,
                    );
                }
            }
            
            if effective_storage_type == 0xA0 {
                let null_byte_pos = unsafe { current_p.add(final_size as usize) };
                unsafe {
                    *null_byte_pos = 0;
                }
                final_size += 1;
            }
            
            item_ref.used_size += final_size;
        },
        0xE0 => {
            if let Some(pvalue_data) = effective_pvalue {
                unsafe {
                    ptr::copy_nonoverlapping(
                        pvalue_data.as_ptr(),
                        p,
                        size as usize,
                    );
                }
            }
            item_ref.used_size += size;
        },
        _ => return 0,
    }
    
    item_ref.dirty = 1;
    1
}
pub fn binn_list_add_raw(
    item: &mut binn,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    // Check if item is None or doesn't meet conditions (equivalent to NULL/0 checks in C)
    if item.is_none() || 
       item.as_ref().map(|i| i.type_ != 0xE0 || i.writable == 0).unwrap_or(true) {
        return 0;
    }

    // Call AddValue with the same parameters
    if AddValue(item, type_, pvalue, size) == 0 {
        return 0;
    }

    // Increment count if successful
    if let Some(i) = item.as_mut() {
        i.count += 1;
    }

    1
}
pub fn binn_list_add(
    list: &mut binn,
    type_: i32,
    pvalue: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
    let mut converted_type = type_;
    let mut converted_pvalue = pvalue;
    let mut converted_size = size;

    if !GetWriteConvertedData(&mut converted_type, &mut converted_pvalue, &mut converted_size) {
        return 0;
    }

    // Convert pvalue to Option<&[u8]> for binn_list_add_raw
    let raw_pvalue = converted_pvalue.and_then(|v| {
        v.as_ref().and_then(|boxed| {
            boxed.downcast_ref::<Vec<u8>>().map(|v| v.as_slice())
        })
    });

    binn_list_add_raw(list, converted_type, raw_pvalue, converted_size)
}
pub fn binn_map_set_raw(
    item: &mut binn,
    id: i32,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    if item.is_none() {
        return 0;
    }
    let item_ref = item.as_mut().unwrap();
    
    if item_ref.type_ != 0xE1 || item_ref.writable == 0 {
        return 0;
    }

    let pbuf_slice = unsafe {
        std::slice::from_raw_parts(
            item_ref.pbuf.as_ref().unwrap().as_ref() as *const _ as *const u8,
            item_ref.used_size as usize,
        )
    };
    
    if let Some(_) = SearchForID(
        pbuf_slice,
        9,
        item_ref.used_size as usize,
        item_ref.count as usize,
        id,
    ) {
        return 0;
    }

    if CheckAllocation(item, 5) == 0 {
        return 0;
    }

    let item_ref = item.as_mut().unwrap();
    let base_ptr = item_ref.pbuf.as_ref().unwrap().as_ref() as *const _ as *const u8;
    let base_offset = item_ref.used_size as isize;
    let mut p_offset = base_offset;
    let id_size;

    let sign = if id < 0 { 1u8 } else { 0u8 };
    let mut temp_id = id.abs();

    if temp_id <= 0x3F {
        unsafe {
            *((base_ptr as isize + p_offset) as *mut u8) = (sign << 6) | temp_id as u8;
        }
        p_offset += 1;
    } else if temp_id <= 0xFFF {
        unsafe {
            *((base_ptr as isize + p_offset) as *mut u8) =
                0x80 | (sign << 4) | ((temp_id & 0xF00) >> 8) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = (temp_id & 0xFF) as u8;
            p_offset += 1;
        }
    } else if temp_id <= 0xFFFFF {
        unsafe {
            *((base_ptr as isize + p_offset) as *mut u8) =
                0xA0 | (sign << 4) | ((temp_id & 0xF0000) >> 16) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = ((temp_id & 0xFF00) >> 8) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = (temp_id & 0xFF) as u8;
            p_offset += 1;
        }
    } else if temp_id <= 0xFFFFFFF {
        unsafe {
            *((base_ptr as isize + p_offset) as *mut u8) =
                0xC0 | (sign << 4) | ((temp_id & 0xF000000) >> 24) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = ((temp_id & 0xFF0000) >> 16) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = ((temp_id & 0xFF00) >> 8) as u8;
            p_offset += 1;
            *((base_ptr as isize + p_offset) as *mut u8) = (temp_id & 0xFF) as u8;
            p_offset += 1;
        }
    } else {
        unsafe {
            *((base_ptr as isize + p_offset) as *mut u8) = 0xE0;
            p_offset += 1;
            if sign != 0 {
                temp_id = -temp_id;
            }
            let mut dest = ((base_ptr as isize + p_offset) as *mut u32).as_mut().unwrap();
            copy_be32(&mut dest, &(temp_id as u32));
            p_offset += 4;
        }
    }

    id_size = (p_offset - base_offset) as i32;
    item_ref.used_size += id_size;

    // Avoid borrowing conflict by using item directly instead of item_ref
    if AddValue(item, type_, pvalue, size) == 0 {
        let item_ref = item.as_mut().unwrap();
        item_ref.used_size -= id_size;
        return 0;
    }

    let item_ref = item.as_mut().unwrap();
    item_ref.count += 1;
    1
}
pub fn binn_map_set(
    map: &mut binn,
    id: i32,
    type_: i32,
    pvalue: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
    let mut converted_type = type_;
    let mut converted_pvalue = pvalue;
    let mut converted_size = size;
    
    if !GetWriteConvertedData(&mut converted_type, &mut converted_pvalue, &mut converted_size) {
        return 0;
    }
    
    // Convert the pvalue to Option<&[u8]> for binn_map_set_raw
    let raw_pvalue = converted_pvalue.and_then(|v| {
        v.as_ref().map(|boxed| {
            let bytes: &[u8] = unsafe { std::mem::transmute(boxed.as_ref()) };
            bytes
        })
    });
    
    binn_map_set_raw(map, id, converted_type, raw_pvalue, converted_size)
}
pub fn binn_object_set_raw(
    item: &mut binn,
    key: Option<&str>,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
    // Check if item is None or has invalid type/writable flag
    if item.is_none() {
        return 0;
    }
    let item_struct = item.as_mut().unwrap();
    if item_struct.type_ != 0xE2 || item_struct.writable == 0 {
        return 0;
    }

    // Check if key is None
    if key.is_none() {
        return 0;
    }
    let key_str = key.unwrap();

    // Calculate key length
    let int32 = key_str.len();
    if int32 > 255 {
        return 0;
    }

    // Search for existing key
    let pbuf_slice = item_struct.pbuf.as_ref().map(|p| unsafe {
        std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, item_struct.used_size as usize)
    });
    
    let p = SearchForKey(
        pbuf_slice,
        9,
        item_struct.used_size as usize,
        item_struct.count,
        Some(key_str),
    );
    if p.is_some() {
        return 0;
    }

    // Check allocation
    if CheckAllocation(item, 1 + int32 as i32) == 0 {
        return 0;
    }

    // Get mutable reference to item_struct after CheckAllocation
    let item_struct = item.as_mut().unwrap();
    
    // Get pointer to buffer and write key length and data
    let buffer_ptr = item_struct.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8;
    let p_start = unsafe { buffer_ptr.add(item_struct.used_size as usize) };
    
    // Write key length
    unsafe { *p_start = int32 as u8 };
    
    // Write key data
    let p_data = unsafe { p_start.add(1) };
    let key_bytes = key_str.as_bytes();
    unsafe {
        std::ptr::copy_nonoverlapping(key_bytes.as_ptr(), p_data, int32);
    }

    let total_key_size = int32 + 1;
    item_struct.used_size += total_key_size as i32;

    // Store count and used_size temporarily to avoid holding the borrow
    let count = item_struct.count;
    let used_size = item_struct.used_size;

    // Add value - release the borrow on item_struct first
    if AddValue(item, type_, pvalue, size) == 0 {
        // Reborrow to adjust used_size
        let item_struct = item.as_mut().unwrap();
        item_struct.used_size -= total_key_size as i32;
        return 0;
    }

    // Reborrow to update count
    let item_struct = item.as_mut().unwrap();
    item_struct.count = count + 1;
    1
}
pub fn binn_object_set(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    type_: i32,
    pvalue: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
    let mut converted_type = type_;
    let mut converted_pvalue = pvalue;
    let mut converted_size = size;
    
    if !GetWriteConvertedData(&mut converted_type, &mut converted_pvalue, &mut converted_size) {
        return 0;
    }

    // Convert the pvalue to a byte slice if it exists
    let pvalue_bytes = match converted_pvalue {
        Some(ref mut value) => {
            // This is a placeholder - actual conversion would depend on the type
            // In a real implementation, you'd need to properly convert the Any to bytes
            None
        },
        None => None,
    };

    binn_object_set_raw(obj, key, converted_type, pvalue_bytes, converted_size)
}
pub fn binn_create(item: &mut binn, type_: i32, size: i32, pointer: Option<&mut [u8]>) -> BOOL {
    let mut retval = 0;
    
    match type_ {
        0xE0 | 0xE1 | 0xE2 => (),
        _ => return retval,
    }

    if item.is_some() || size < 0 {
        return retval;
    }
    
    let size = if size < 3 {
        if pointer.is_some() {
            return retval;
        } else {
            0
        }
    } else {
        size
    };

    // Initialize the binn struct by replacing with a new empty one
    *item = Some(Box::new(BinnStruct {
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
        value: BinnValue {
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
        },
        disable_int_compression: 0,
    }));

    let item_mut = item.as_mut().unwrap();
    
    if let Some(slice) = pointer {
        item_mut.pre_allocated = 1;
        // Convert the raw pointer to Option<Box<()>> by boxing it
        let boxed_ptr = unsafe { Box::from_raw(slice.as_mut_ptr() as *mut ()) };
        item_mut.pbuf = Some(boxed_ptr);
        item_mut.alloc_size = size;
    } else {
        item_mut.pre_allocated = 0;
        let alloc_size = if size == 0 { 256 } else { size };
        let allocated_ptr = binn_malloc(alloc_size);
        if allocated_ptr.is_none() {
            *item = None;
            return 0;
        }
        // Convert the raw pointer to Option<Box<()>> by re-boxing
        let raw_ptr = Box::into_raw(allocated_ptr.unwrap()) as *mut _ as *mut ();
        let boxed_ptr = unsafe { Box::from_raw(raw_ptr) };
        item_mut.pbuf = Some(boxed_ptr);
        item_mut.alloc_size = alloc_size;
    }

    item_mut.header = 0x1F22B11F;
    item_mut.writable = 1;
    item_mut.used_size = 9;
    item_mut.type_ = type_;
    item_mut.dirty = 1;
    
    1
}
pub fn binn_new(type_: i32, size: i32, pointer: Option<&mut [u8]>) -> Option<Box<BinnStruct>> {
    let item_ptr = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    let mut item: Option<Box<BinnStruct>> = match item_ptr {
        Some(ptr) => {
            // SAFETY: We know binn_malloc returns a pointer to BinnStruct-sized memory
            // and we need to downcast from Box<dyn Any> to Box<BinnStruct>
            let any_box = ptr;
            match any_box.downcast::<BinnStruct>() {
                Ok(boxed_struct) => Some(boxed_struct),
                Err(_) => return None,
            }
        }
        None => return None,
    };
    
    let create_result = {
        let item_ref = &mut item;
        binn_create(item_ref, type_, size, pointer)
    };
    
    if create_result == 0 {
        if let Some(mut item_box) = item {
            if let Ok(mut free_fn_guard) = FREE_FN.lock() {
                if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                    let ptr: Option<Box<dyn std::any::Any + Send>> = Some(Box::new(item_box));
                    (free_fn_wrapper.0)(ptr);
                }
            }
        }
        return None;
    }
    
    if let Some(item_box) = item.as_mut() {
        item_box.allocated = 1;
    }
    
    item
}
pub fn binn_list() -> Option<Box<BinnStruct>> {
    binn_new(0xE0, 0, None)
}
pub fn binn_map() -> Option<Box<BinnStruct>> {
    binn_new(0xE1, 0, None)
}
pub fn binn_object() -> Option<Box<BinnStruct>> {
    binn_new(0xE2, 0, None)
}
pub fn binn_create_list(list: &mut binn) -> BOOL {
    binn_create(list, 0xE0, 0, None)
}
pub fn binn_create_map(map: &mut binn) -> BOOL {
    binn_create(map, 0xE1, 0, None)
}
pub fn binn_create_object(object: &mut binn) -> BOOL {
    binn_create(object, 0xE2, 0, None)
}
pub fn binn_free(item: &mut Option<Box<BinnStruct>>) {
    if item.is_none() {
        return;
    }

    let mut item = item.take().unwrap(); // Take ownership of the Box

    if item.writable != 0 && item.pre_allocated == 0 {
        if let Some(pbuf) = item.pbuf.take() {
            if let Some(free_fn) = FREE_FN.lock().unwrap().as_mut() {
                free_fn.0(Some(Box::new(pbuf) as Box<dyn std::any::Any + Send>));
            }
        }
    }

    if item.freefn.is_some() {
        if let Some(ptr) = item.ptr.take() {
            item.freefn.as_mut().unwrap()(Some(ptr));
        }
    }

    if item.allocated != 0 {
        if let Some(free_fn) = FREE_FN.lock().unwrap().as_mut() {
            free_fn.0(Some(Box::new(item) as Box<dyn std::any::Any + Send>));
        }
    } else {
        // Equivalent to memset(item, 0, sizeof(binn))
        *item = BinnStruct {
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
            value: BinnValue {
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
            },
            disable_int_compression: 0,
        };
    }
}
pub fn binn_load(data: Option<*mut u8>, mut value: Option<&mut BinnStruct>) -> bool {
    // Check for null pointers (represented as None in Rust)
    if data.is_none() || value.is_none() {
        return false;
    }

    // Get mutable reference to value
    let value = value.as_mut().unwrap();

    // Equivalent to memset - zero out the struct
    **value = BinnStruct {
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
        value: BinnValue {
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
        },
        disable_int_compression: 0,
    };

    value.header = 0x1F22B11F;

    // Call binn_is_valid with references to value's fields
    if !binn_is_valid(data, Some(&mut value.type_), Some(&mut value.count), Some(&mut value.size)) {
        return false;
    }

    // Set the pointer field - requires unsafe block for raw pointer operations
    unsafe {
        value.ptr = Some(Box::from_raw(data.unwrap() as *mut ()));
    }

    true
}
pub fn binn_list_int64(list: Option<&[u8]>, pos: i32) -> int64 {
    let mut value: int64 = 0;
    binn_list_get(list, pos, 0x81, Some(&mut value), None);
    value
}
pub fn binn_list_bool(list: Option<&[u8]>, pos: i32) -> BOOL {
    let mut value: BOOL = 0;
    binn_list_get(list, pos, 0x80061, Some(&mut value), None);
    value
}

pub fn binn_map_int64(map: Option<&[u8]>, id: i32) -> int64 {
    let mut value: int64 = 0;
    binn_map_get(map, id, 0x81, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn binn_map_bool(map: Option<&[u8]>, id: i32) -> BOOL {
    let mut value: BOOL = 0;
    binn_map_get(map, id, 0x80061, Some(&mut value), None);
    value
}
pub fn binn_object_int64(obj: Option<&[u8]>, key: Option<&str>) -> int64 {
    let mut value: int64 = 0;
    binn_object_get(obj, key, 0x81, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn binn_object_bool(obj: Option<&[u8]>, key: Option<&str>) -> BOOL {
    let mut value: BOOL = 0;
    binn_object_get(obj, key, 0x80061, Some(&mut value), None);
    value
}
pub fn binn_read_pair(
    expected_type: i32,
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Convert ptr to slice reference for IsValidBinnHeader
    let ptr_slice = match ptr {
        Some(slice) => Some(slice),
        None => return 0,
    };

    if !IsValidBinnHeader(
        ptr_slice,
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    if (((type_ != expected_type) || (count == 0)) || (pos < 1)) || (pos > count) {
        return 0;
    }

    let Some(ptr_data) = ptr else {
        return 0;
    };

    let base = ptr_data.as_ptr() as usize;
    let plimit = base + size as usize - 1;
    let mut p_idx = base + header_size as usize;

    let mut id = 0;
    let mut key_ptr: Option<usize> = None;
    let mut len: u8 = 0;
    let mut counter = 0;

    for _ in 0..count {
        match type_ {
            0xE1 => {
                let mut current_p = unsafe { std::slice::from_raw_parts(p_idx as *const u8, (plimit - p_idx + 1).max(0) as usize) };
                let plimit_ptr = plimit as *const u8;
                
                let Some(int32) = read_map_id(&mut current_p, unsafe { std::slice::from_raw_parts(plimit_ptr, 1) }) else {
                    return 0;
                };
                
                p_idx = current_p.as_ptr() as usize;
                if p_idx > plimit {
                    return 0;
                }
                
                id = int32;
            }
            0xE2 => {
                if p_idx > plimit {
                    return 0;
                }
                
                len = unsafe { *((p_idx as *const u8)) };
                p_idx += 1;
                
                if p_idx > plimit {
                    return 0;
                }
                
                key_ptr = Some(p_idx);
                p_idx += len as usize;
                
                if p_idx > plimit {
                    return 0;
                }
            }
            _ => {}
        }

        counter += 1;
        if counter == pos {
            break;
        }

        let current_p = unsafe { std::slice::from_raw_parts(p_idx as *const u8, (plimit - p_idx + 1).max(0) as usize) };
        let Some(new_p) = AdvanceDataPos(current_p, plimit) else {
            return 0;
        };
        
        p_idx = new_p.as_ptr() as usize;
        if p_idx < base {
            return 0;
        }
    }

    if counter != pos {
        return 0;
    }

    match type_ {
        0xE1 => {
            if let Some(pid_ref) = pid {
                *pid_ref = id;
            }
        }
        0xE2 => {
            if let (Some(pkey_ref), Some(key_ptr_val)) = (pkey, key_ptr) {
                if pkey_ref.len() >= len as usize + 1 {
                    unsafe {
                        std::ptr::copy_nonoverlapping(
                            key_ptr_val as *const u8,
                            pkey_ref.as_mut_ptr(),
                            len as usize,
                        );
                        *pkey_ref.as_mut_ptr().add(len as usize) = 0;
                    }
                }
            }
        }
        _ => {}
    }

    let current_p = unsafe { std::slice::from_raw_parts(p_idx as *const u8, (plimit - p_idx + 1).max(0) as usize) };
    GetValue(Some(current_p), value)
}
pub fn binn_map_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    value: Option<&mut binn>,
) -> BOOL {
    binn_read_pair(0xE1, ptr, pos, pid, None, value)
}
pub fn binn_object_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
    binn_read_pair(0xE2, ptr, pos, None, pkey, value)
}
pub fn binn_size(ptr: Option<*mut u8>) -> i32 {
    match binn_get_ptr_type(ptr) {
        1 => {
            // SAFETY: We know ptr is a valid binn pointer from case 1
            let item_ptr = ptr.unwrap() as *mut BinnStruct;
            let item = unsafe { &mut *item_ptr };
            
            if item.writable != 0 && item.dirty != 0 {
                // Convert to binn type (Option<Box<BinnStruct>>)
                let mut binn_item = Some(Box::new(unsafe { std::ptr::read(item) }));
                binn_save_header(&mut binn_item);
                // Write back the potentially modified item
                unsafe { std::ptr::write(item, *binn_item.unwrap()); }
            }

            item.size
        }
        2 => {
            // For case 2, convert *mut u8 to &[u8] for binn_buf_size
            if let Some(ptr) = ptr {
                // SAFETY: We know this is a valid buffer from case 2
                let slice = unsafe { std::slice::from_raw_parts(ptr, 0) };
                binn_buf_size(Some(slice))
            } else {
                binn_buf_size(None)
            }
        }
        _ => 0,
    }
}

pub fn binn_set_alloc_functions(
    new_malloc: Option<fn(usize) -> Option<Box<dyn std::any::Any>>>,
    new_realloc: Option<Box<dyn FnMut(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>> + Send>>,
    new_free: Option<Box<dyn FnMut(Option<Box<dyn std::any::Any + Send>>)>>,
) {
    if let Some(malloc) = new_malloc {
        *MALLOC_FN.lock().unwrap() = Some(malloc);
    }
    
    if let Some(realloc) = new_realloc {
        *REALLOC_FN.lock().unwrap() = Some(ReallocFnWrapper(realloc));
    }
    
    if let Some(free) = new_free {
        *FREE_FN.lock().unwrap() = Some(FreeFnWrapper(free));
    }
}
pub fn binn_release(item: Option<&mut BinnStruct>) -> Option<*mut u8> {
    let item = match item {
        Some(item) => item,
        None => return None,
    };

    let mut data = binn_ptr(Some(ptr::from_mut(item).cast()));
    
    if let (Some(data_ptr), Some(pbuf)) = (data, item.pbuf.as_ref()) {
        let data_addr = data_ptr as usize;
        let pbuf_ptr = pbuf.as_ref() as *const _ as usize;
        if data_addr > pbuf_ptr {
            let size = item.size as usize;
            unsafe {
                ptr::copy(
                    data_ptr,
                    pbuf.as_ref() as *const _ as *mut u8,
                    size
                );
            }
            data = Some(pbuf.as_ref() as *const _ as *mut u8);
        }
    }

    if item.allocated != 0 {
        if let Some(mut free_fn_guard) = FREE_FN.lock().ok() {
            if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                // Reconstruct the Box<BinnStruct> from the raw pointer
                let raw_ptr = item as *mut BinnStruct;
                let boxed_item = unsafe { Box::from_raw(raw_ptr) };
                (free_fn_wrapper.0)(Some(boxed_item as Box<dyn std::any::Any + Send>));
                return data;
            }
        }
        // If we can't get the free function, leak the item intentionally
        return data;
    } else {
        *item = BinnStruct {
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
            freefn: BinnMemFree::None,
            value: BinnValue {
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
            },
            disable_int_compression: 0,
        };
    }

    data
}

pub fn binn_type(ptr: Option<*mut u8>) -> i32 {
    match binn_get_ptr_type(ptr) {
        1 => {
            // SAFETY: We know ptr is valid for case 1 based on binn_get_ptr_type
            let item_ptr = ptr.unwrap() as *mut binn;
            let item = unsafe { &*item_ptr };
            item.as_ref().map(|b| b.type_).unwrap_or(-1)
        }
        2 => binn_buf_type(unsafe { 
            ptr.map(|p| std::slice::from_raw_parts(p, 0)) 
        }),
        _ => -1,
    }
}
pub fn binn_count(ptr: Option<*mut u8>) -> i32 {
    match binn_get_ptr_type(ptr) {
        1 => {
            // SAFETY: We've verified this is a valid binn pointer through binn_get_ptr_type
            if let Some(p) = ptr {
                // SAFETY: binn_get_ptr_type verified this is a valid binn pointer
                // Cast to the correct type (binn, which is Option<Box<BinnStruct>>)
                let item_ptr = p as *mut binn;
                unsafe {
                    // Use as_ref() to avoid moving out of the raw pointer
                    if let Some(item_box) = (*item_ptr).as_ref() {
                        item_box.count
                    } else {
                        -1
                    }
                }
            } else {
                -1
            }
        }
        2 => {
            // For case 2, we need to convert the raw pointer to a slice for binn_buf_count
            if let Some(p) = ptr {
                // SAFETY: binn_get_ptr_type verified this is a valid buffer pointer
                // We use a dummy length (0) since binn_buf_count will determine the actual length
                let slice = unsafe { std::slice::from_raw_parts(p, 0) };
                binn_buf_count(Some(slice))
            } else {
                binn_buf_count(Option::None)
            }
        }
        _ => -1,
    }
}
pub fn binn_list_uint64(list: Option<&[u8]>, pos: i32) -> uint64 {
    let mut value: uint64 = 0;
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    binn_list_get(list, pos, 0x80, pvalue, None);
    value
}
pub fn binn_map_uint64(map: Option<&[u8]>, id: i32) -> uint64 {
    let mut value: uint64 = 0;
    let _ = binn_map_get(map, id, 0x80, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint64(obj: Option<&[u8]>, key: Option<&str>) -> uint64 {
    let mut value: uint64 = 0;
    binn_object_get(obj, key, 0x80, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn store_value(value: Option<Box<BinnStruct>>) -> Option<Box<()>> {
    // Lock the global LOCAL_VALUE mutex
    let mut local_value_guard = LOCAL_VALUE.lock().unwrap();
    
    if let Some(value) = value {
        // Perform the equivalent of memcpy by dereferencing and assigning first
        **local_value_guard.as_mut().unwrap() = *value;
        
        // Now get the ptr from the stored value
        let original_ptr = local_value_guard.as_ref().unwrap().ptr.clone();

        match binn_get_read_storage(local_value_guard.as_ref().unwrap().type_) {
            0x00 | 0x40 | 0x60 | 0x80 => {
                // Return a pointer to vint32 by taking a reference and converting to raw pointer
                let vint32_ptr = &mut local_value_guard.as_mut().unwrap().value.vint32 as *mut i32;
                Some(unsafe { Box::from_raw(vint32_ptr as *mut ()) })
            }
            _ => original_ptr,
        }
    } else {
        None
    }
}

lazy_static! {
    pub static ref LOCAL_VALUE: Mutex<Option<Box<BinnStruct>>> = {
        let empty_binn: BinnStruct = unsafe { mem::zeroed() };
        Mutex::new(Some(Box::new(empty_binn)))
    };
}
pub fn binn_list_read(
    list: Option<&[u8]>,
    pos: i32,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    if binn_list_get_value(list, pos, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        if let Some(ref value) = value {
            *ptype = value.type_;
        }
    }

    if let Some(psize) = psize {
        if let Some(ref value) = value {
            *psize = value.size;
        }
    }

    store_value(value)
}
pub fn binn_map_read(
    map: Option<&[u8]>,
    id: i32,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    if binn_map_get_value(map, id, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(value) = value {
        if let Some(ptype) = ptype {
            *ptype = value.type_;
        }
        if let Some(psize) = psize {
            *psize = value.size;
        }
        store_value(Some(value))
    } else {
        None
    }
}
pub fn binn_object_read(
    obj: Option<&[u8]>,
    key: Option<&str>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    // Check if we successfully get the value
    if binn_object_get_value(obj, key, Some(&mut value)) == 0 {
        return None;
    }

    // If ptype is provided, set its value
    if let Some(ptype) = ptype {
        if let Some(ref v) = value {
            *ptype = v.type_;
        }
    }

    // If psize is provided, set its value
    if let Some(psize) = psize {
        if let Some(ref v) = value {
            *psize = v.size;
        }
    }

    // Store and return the value
    store_value(value)
}
pub fn binn_map_read_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    if binn_map_get_pair(ptr, pos, pid, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        if let Some(ref value) = value {
            *ptype = value.type_;
        }
    }

    if let Some(psize) = psize {
        if let Some(ref value) = value {
            *psize = value.size;
        }
    }

    store_value(value)
}
pub fn binn_object_read_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pkey: Option<&mut [u8]>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    if binn_object_get_pair(ptr, pos, pkey, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        if let Some(ref value) = value {
            *ptype = value.type_;
        }
    }

    if let Some(psize) = psize {
        if let Some(ref value) = value {
            *psize = value.size;
        }
    }

    store_value(value)
}
pub fn binn_read_next_pair(
    expected_type: i32,
    iter: Option<&mut BinnIter>,
    pid: Option<&mut i32>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
    // Check for invalid iterator conditions
    let iter = match iter {
        Some(iter) => iter,
        None => return 0,
    };

    if iter.pnext.is_none()
        || iter.plimit.is_none()
        || iter.current > iter.count
        || iter.type_ != expected_type
    {
        return 0;
    }

    // Get raw pointer addresses early before any borrows
    let pnext_ptr = iter.pnext.as_ref().unwrap().as_ptr() as usize;
    let plimit_ptr = iter.plimit.as_ref().unwrap().as_ptr() as usize;
    
    if pnext_ptr > plimit_ptr {
        return 0;
    }

    iter.current += 1;
    if iter.current > iter.count {
        return 0;
    }

    // Work with slices but don't hold references across the assignment
    let mut p = iter.pnext.as_ref().unwrap().as_slice();
    let plimit_slice = iter.plimit.as_ref().unwrap().as_slice();
    let mut id = 0;
    let mut key_data: Option<&[u8]> = None;
    let mut len = 0;

    match expected_type {
        0xE1 => {
            let mut p_mut = p;
            let int32 = match read_map_id(&mut p_mut, plimit_slice) {
                Some(val) => val,
                None => return 0,
            };
            
            if p_mut.as_ptr() as usize > plimit_ptr {
                return 0;
            }

            id = int32;
            p = p_mut;
            
            if let Some(pid_ref) = pid {
                *pid_ref = id;
            }
        }
        0xE2 => {
            if p.is_empty() {
                return 0;
            }
            
            len = p[0] as usize;
            p = &p[1..];
            
            if p.len() < len {
                return 0;
            }
            
            key_data = Some(&p[..len]);
            p = &p[len..];
            
            if p.as_ptr() as usize > plimit_ptr {
                return 0;
            }
            
            if let Some(pkey_ref) = pkey {
                if pkey_ref.len() >= len {
                    pkey_ref[..len].copy_from_slice(&p[..len]);
                    if pkey_ref.len() > len {
                        pkey_ref[len] = 0;
                    }
                }
            }
        }
        _ => (),
    }

    let new_pnext = match AdvanceDataPos(p, plimit_slice.len()) {
        Some(new_p) => new_p,
        None => return 0,
    };

    if (new_pnext.as_ptr() as usize) < p.as_ptr() as usize {
        return 0;
    }

    // Create a new vector for the updated position and assign it
    let new_pnext_vec = new_pnext.to_vec();
    
    // Get the result before updating iter.pnext to avoid borrow issues
    let result = GetValue(Some(p), value);
    
    // Now update iter.pnext after we're done using p
    iter.pnext = Some(new_pnext_vec);
    
    result
}
pub fn binn_map_next(iter: Option<&mut BinnIter>, pid: Option<&mut i32>, value: Option<&mut binn>) -> BOOL {
    binn_read_next_pair(0xE1, iter, pid, None, value)
}
pub fn binn_object_next(
    iter: Option<&mut BinnIter>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
    binn_read_next_pair(0xE2, iter, None, pkey, value)
}
pub fn binn_copy(old: Option<&mut binn>) -> Option<Box<BinnStruct>> {
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
    // Get the raw pointer from binn_ptr, handling the Option properly
    let old_ptr_option = binn_ptr(old.and_then(|b| {
        b.as_mut().unwrap().pbuf.as_mut().map(|p| p.as_ref() as *const () as *mut u8)
    }));
    
    // Extract the raw pointer from Option, return None if None
    let old_ptr = match old_ptr_option {
        Some(ptr) => ptr,
        None => return None,
    };
    
    if !IsValidBinnHeader(
        Some(unsafe { std::slice::from_raw_parts(old_ptr as *const u8, size as usize) }),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return None;
    }
    
    let item = binn_new(type_, (size - header_size) + 9, None);
    
    if let Some(mut item_box) = item {
        let item_ref = item_box.as_mut();
        
        // Get the destination pointer from pbuf, handling Option properly
        let dest_ptr = match item_ref.pbuf.as_mut() {
            Some(pbuf) => {
                let base_ptr = pbuf.as_ref() as *const () as *mut u8;
                unsafe { base_ptr.add(9) }
            },
            None => return None,
        };
        
        unsafe {
            ptr::copy_nonoverlapping(
                old_ptr.add(header_size as usize),
                dest_ptr,
                (size - header_size) as usize,
            );
        }
        
        item_ref.used_size = (9 + size) - header_size;
        item_ref.count = count;
        Some(item_box)
    } else {
        None
    }
}

pub fn binn_list_add_new(list: &mut Option<Box<BinnStruct>>, value: &mut Option<Box<BinnStruct>>) -> BOOL {
    let retval = binn_list_add_value(list, value);
    
    if value.is_some() {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            let value_to_free = value.take().map(|v| v as Box<dyn std::any::Any + Send>);
            free_fn.0(value_to_free);
        }
    }
    
    retval
}
pub fn binn_map_set_new(map: &mut binn, id: i32, mut value: Option<Box<BinnStruct>>) -> BOOL {
    let retval;
    {
        let mut value_ref = value.as_mut().map(|v| v.as_mut() as *mut BinnStruct);
        retval = binn_map_set_value(map, id, &mut value);
    }
    
    if let Some(value) = value {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            (free_fn.0)(Some(Box::new(value)));
        }
    }
    
    retval
}

pub fn binn_object_set_new(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: Option<Box<BinnStruct>>,
) -> BOOL {
    let mut value = value;
    let retval = binn_object_set_value(obj, key, &mut value);
    
    if let Some(v) = value {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            (free_fn.0)(Some(Box::new(v)));
        }
    }
    
    retval
}
pub fn binn_open(data: Option<*mut u8>) -> Option<Box<BinnStruct>> {
    // Allocate memory for a new BinnStruct
    let any_box = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    
    // Convert the Box<dyn Any> to Box<BinnStruct> if allocation succeeded
    let mut item = match any_box {
        Some(boxed_any) => {
            match boxed_any.downcast::<BinnStruct>() {
                Ok(boxed) => boxed,
                Err(_) => return None,
            }
        }
        None => return None,
    };
    
    // Try to load data into the BinnStruct
    if !binn_load(data, Some(&mut *item)) {
        // If loading fails, free the allocated memory using the global free function
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn.0(Some(Box::new(item) as Box<dyn std::any::Any + Send>));
        }
        return None;
    }
    
    // Mark the item as allocated and return it
    item.allocated = 1; // BOOL is i32, so use 1 instead of true
    Some(item)
}
pub fn binn_list_value(ptr: Option<&[u8]>, pos: i32) -> Option<Box<BinnStruct>> {
    // Allocate memory for the binn value
    let mut value: binn = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(allocated) => {
            // Convert the Box<dyn Any> to Box<BinnStruct> by reconstructing it
            // This is safe because we know we allocated the correct size for BinnStruct
            let raw_ptr = Box::into_raw(allocated);
            unsafe {
                // Convert the raw pointer to our specific type
                let binn_ptr = raw_ptr as *mut BinnStruct;
                Some(Box::from_raw(binn_ptr))
            }
        }
        None => return None,
    };
    
    // Call binn_list_get_value and check the result
    if binn_list_get_value(ptr, pos, Some(&mut value)) == 0 {
        // If the function fails, free the allocated memory and return None
        if let Some(mut free_fn_guard) = FREE_FN.lock().ok() {
            if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                // Convert back to Box<dyn Any + Send> for the free function
                if let Some(boxed) = value {
                    let any_box: Box<dyn std::any::Any + Send> = Box::new(*boxed);
                    (free_fn_wrapper.0)(Some(any_box));
                }
            }
        }
        return None;
    }
    
    // Get the value back from binn type and set the allocated flag
    if let Some(ref mut boxed_value) = value {
        boxed_value.allocated = 1;
    }
    
    value
}
pub fn binn_map_value(ptr: Option<&[u8]>, id: i32) -> Option<Box<BinnStruct>> {
    // Allocate memory for a new BinnStruct
    let value_ptr = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    let value_box = match value_ptr {
        Some(ptr) => {
            // SAFETY: We know binn_malloc returns a pointer to BinnStruct-sized memory
            unsafe {
                let raw_ptr = Box::into_raw(ptr);
                let cast_ptr = raw_ptr as *mut BinnStruct;
                Box::from_raw(cast_ptr)
            }
        }
        None => return None,
    };

    // Create a mutable reference to the value_box wrapped in Option
    let mut value_opt: Option<Box<BinnStruct>> = Some(value_box);
    let value_ref = &mut value_opt;

    // Call binn_map_get_value and check result
    let result = binn_map_get_value(ptr, id, Some(value_ref));

    if result == 0 {
        // If the function failed, free the allocated memory
        if let Ok(mut free_fn_guard) = FREE_FN.lock() {
            if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                let value_ptr = value_opt.map(|b| b as Box<dyn std::any::Any + Send>);
                (free_fn_wrapper.0)(value_ptr);
            }
        }
        return None;
    }
    
    // Extract the value from the option
    let mut value = value_opt.take().unwrap();
    
    // Set the allocated flag
    value.allocated = 1;
    
    Some(value)
}
pub fn binn_object_value(ptr: Option<&[u8]>, key: Option<&str>) -> Option<Box<BinnStruct>> {
    let mut value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(allocated_ptr) => {
            // SAFETY: We know binn_malloc returns a pointer to BinnStruct-sized memory
            // We need to reconstruct it as a BinnStruct
            let raw_ptr = Box::into_raw(allocated_ptr) as *mut BinnStruct;
            let mut boxed_value = unsafe { Box::from_raw(raw_ptr) };
            
            // Initialize the BinnStruct with default values
            *boxed_value = BinnStruct {
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
                freefn: BinnMemFree::None,
                value: BinnValue {
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
                },
                disable_int_compression: 0,
            };
            
            Some(boxed_value)
        }
        None => return None,
    };

    // Create a mutable reference to the binn value
    let result = binn_object_get_value(ptr, key, Some(&mut value));
    
    if result == 0 {
        if let Some(mut free_fn_guard) = FREE_FN.lock().ok() {
            if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                // Convert the Box<BinnStruct> to Box<dyn Any + Send> for the free function
                let any_ptr: Option<Box<dyn std::any::Any + Send>> = value.map(|v| v as Box<dyn std::any::Any + Send>);
                (free_fn_wrapper.0)(any_ptr);
            }
        }
        return None;
    }

    if let Some(value_ref) = value.as_mut() {
        value_ref.allocated = 1;
    }
    
    value
}
pub fn binn_map_pair(map: Option<&[u8]>, pos: i32, pid: Option<&mut i32>) -> Option<Box<BinnStruct>> {
    let value_ptr = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    let mut value_box = match value_ptr {
        Some(ptr) => ptr,
        None => return None,
    };

    let value_ref: Option<&mut binn> = value_box.downcast_mut::<binn>();
    let mut value = match value_ref {
        Some(v) => v,
        None => {
            if let Some(free_fn) = FREE_FN.lock().unwrap().as_mut() {
                // Cast to Box<dyn Any + Send> to match the expected type
                let send_box: Box<dyn std::any::Any + Send> = unsafe { std::mem::transmute(value_box) };
                (free_fn.0)(Some(send_box));
            }
            return None;
        }
    };

    if binn_read_pair(0xE1, map, pos, pid, None, Some(&mut value)) == 0 {
        if let Some(free_fn) = FREE_FN.lock().unwrap().as_mut() {
            // Cast to Box<dyn Any + Send> to match the expected type
            let send_box: Box<dyn std::any::Any + Send> = unsafe { std::mem::transmute(value_box) };
            (free_fn.0)(Some(send_box));
        }
        return None;
    }

    if let Some(binn_struct) = value.as_mut() {
        binn_struct.allocated = 1;
    }

    value_box.downcast::<BinnStruct>().ok()
}
pub fn binn_object_pair(obj: Option<&[u8]>, pos: i32, pkey: Option<&mut [u8]>) -> Option<Box<BinnStruct>> {
    let mut value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(ptr) => ptr,
        None => return None,
    };
    
    let result = binn_read_pair(0xE2, obj, pos, None, pkey, value.downcast_mut::<binn>());
    
    if result == 0 {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            let send_value = unsafe {
                std::mem::transmute::<Box<dyn std::any::Any>, Box<dyn std::any::Any + Send>>(value)
            };
            (free_fn.0)(Some(send_value));
        }
        return None;
    }
    
    if let Some(binn_option) = value.downcast_mut::<binn>() {
        if let Some(binn_struct) = binn_option.as_mut() {
            binn_struct.allocated = 1;
        }
    }
    
    value.downcast::<BinnStruct>().ok().map(|boxed| boxed)
}
pub fn binn_iter_init(
    iter: Option<&mut BinnIter>,
    ptr: Option<&[u8]>,
    expected_type: i32,
) -> bool {
    // Check for null pointers
    if ptr.is_none() || iter.is_none() {
        return false;
    }
    
    let iter = iter.unwrap();
    let slice = ptr.unwrap();
    let raw_ptr = slice.as_ptr() as *mut u8;
    let ptr_val = match binn_ptr(Some(raw_ptr)) {
        Some(p) => p,
        None => return false,
    };
    
    // Initialize iter with zeros (equivalent to memset)
    *iter = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };
    
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
    // Create a slice from the raw pointer for IsValidBinnHeader
    // We need to pass a slice with sufficient length, but since we don't know the actual size,
    // we use a large enough value (256 bytes should be sufficient for header parsing)
    let header_slice = unsafe { std::slice::from_raw_parts(ptr_val, 256) };
    
    if !IsValidBinnHeader(
        Some(header_slice),
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
    
    // Calculate pointer arithmetic using raw pointers
    let plimit = unsafe { ptr_val.add(size as usize).sub(1) };
    let pnext = unsafe { ptr_val.add(header_size as usize) };
    
    // Store empty vectors since the struct expects Option<Vec<u8>>
    iter.plimit = Some(Vec::new());
    iter.pnext = Some(Vec::new());
    
    iter.count = count;
    iter.current = 0;
    iter.type_ = type_;
    
    true
}
pub fn binn_list_next(iter: Option<&mut BinnIter>, value: Option<&mut binn>) -> BOOL {
    // Check if iter is None or any of the conditions in the complex if statement
    if iter.is_none() {
        return 0;
    }
    let iter = iter.unwrap();
    
    if iter.pnext.is_none() 
        || iter.plimit.is_none() 
        || iter.pnext.as_ref().unwrap().as_ptr() > iter.plimit.as_ref().unwrap().as_ptr()
        || iter.current > iter.count 
        || iter.type_ != 0xE0 
    {
        return 0;
    }

    iter.current += 1;
    if iter.current > iter.count {
        return 0;
    }

    let pnow_ptr = iter.pnext.as_ref().unwrap().as_ptr();
    let plimit_ptr = iter.plimit.as_ref().unwrap().as_ptr();
    
    // Advance the pointer position - convert to slice and call AdvanceDataPos
    let remaining_bytes = (plimit_ptr as usize) - (pnow_ptr as usize);
    let data_slice = unsafe { std::slice::from_raw_parts(pnow_ptr, remaining_bytes) };
    
    let next_slice = AdvanceDataPos(data_slice, plimit_ptr as usize);
    if let Some(next) = next_slice {
        iter.pnext = Some(next.to_vec());
    } else {
        iter.pnext = Option::None;
        return 0;
    }

    // Check if the new pointer is valid
    if let Some(ref next) = iter.pnext {
        if next.as_ptr() < pnow_ptr {
            return 0;
        }
    } else {
        return 0;
    }

    // Get the value from the current position
    let element_size = (iter.pnext.as_ref().unwrap().as_ptr() as usize) - (pnow_ptr as usize);
    let element_slice = unsafe { std::slice::from_raw_parts(pnow_ptr, element_size) };
    
    GetValue(Some(element_slice), value)
}
pub fn binn_list_read_next(
    iter: Option<&mut BinnIter>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value = None;
    
    // Call binn_list_next with mutable references to iter and value
    if binn_list_next(iter, Some(&mut value)) == 0 {
        return None;
    }

    // Unwrap the value safely
    if let Some(value) = value {
        // Update ptype if it's Some
        if let Some(ptype) = ptype {
            *ptype = value.type_;
        }

        // Update psize if it's Some
        if let Some(psize) = psize {
            *psize = value.size;
        }

        // Store the value and return the result
        store_value(Some(value))
    } else {
        None
    }
}
pub fn binn_map_read_next(
    iter: Option<&mut BinnIter>,
    pid: Option<&mut i32>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value: binn = None;
    
    if binn_map_next(iter, pid, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        if let Some(ref value) = value {
            *ptype = value.type_;
        }
    }

    if let Some(psize) = psize {
        if let Some(ref value) = value {
            *psize = value.size;
        }
    }

    store_value(value)
}
pub fn binn_object_read_next(
    iter: Option<&mut BinnIter>,
    pkey: Option<&mut [u8]>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
    let mut value: Option<Box<BinnStruct>> = None;
    
    if binn_object_next(iter, pkey, Some(&mut value)) == 0 {
        return None;
    }

    if let Some(ptype) = ptype {
        if let Some(ref value) = value {
            *ptype = value.type_;
        }
    }

    if let Some(psize) = psize {
        if let Some(ref value) = value {
            *psize = value.size;
        }
    }

    store_value(value)
}
pub fn binn_set_string(item: &mut BinnStruct, str: Option<&CStr>, pfree: BinnMemFree) -> BOOL {
    // Check for NULL pointers (None in Rust)
    if item.ptr.is_some() || str.is_none() {
        return 0;
    }

    let str = str.unwrap();

    // Compare with None directly since we can't compare function pointers
    if pfree.is_none() {
        // Convert CStr to bytes and duplicate
        let bytes = str.to_bytes_with_nul();
        let boxed_bytes = binn_memdup(Some(bytes), (bytes.len()) as i32);
        
        if boxed_bytes.is_none() {
            return 0;
        }
        
        // Convert Box<[u8]> to Box<()>
        let ptr = boxed_bytes.map(|b| unsafe { Box::from_raw(Box::into_raw(b) as *mut ()) });
        item.ptr = ptr;
        
        // Lock the FREE_FN mutex and set the free function
        let mut free_fn_guard = FREE_FN.lock().unwrap();
        if let Some(mut wrapper) = free_fn_guard.take() {
            item.freefn = Some(Box::new(move |ptr: Option<Box<()>>| {
                if let Some(p) = ptr {
                    let raw_ptr = Box::into_raw(p);
                    let b = unsafe { Box::from_raw(raw_ptr as *mut u8) };
                    (wrapper.0)(Some(Box::new(b) as Box<dyn std::any::Any + Send>));
                } else {
                    (wrapper.0)(None);
                }
            }) as Box<dyn FnMut(Option<Box<()>>)>);
        }
    } else {
        // Convert CStr to raw pointer (unsafe but necessary for FFI compatibility)
        let ptr = unsafe { Box::from_raw(str.as_ptr() as *mut ()) };
        item.ptr = Some(ptr);
        item.freefn = pfree;
    }

    item.type_ = 0xA0;
    1
}
pub fn binn_set_blob(
    item: &mut Option<Box<BinnStruct>>,
    ptr: Option<Box<()>>,
    size: i32,
    pfree: BinnMemFree,
) -> BOOL {
    // Check for NULL pointers (represented as None in Rust)
    if item.is_none() || ptr.is_none() {
        return 0;
    }

    // Safe unwrap since we checked for None above
    let item = item.as_mut().unwrap();

    // Compare pfree with -1 cast to BinnMemFree
    if pfree.is_none() {
        // Convert ptr to &[u8] for binn_memdup (assuming ptr points to bytes)
        let ptr_slice = ptr.as_ref().map(|p| unsafe {
            std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, size as usize)
        });
        
        item.ptr = binn_memdup(ptr_slice, size).map(|b| Box::into_raw(b) as *mut u8 as *mut ())
            .map(|ptr| unsafe { Box::from_raw(ptr) });
        if item.ptr.is_none() {
            return 0;
        }
        
        // Lock the FREE_FN mutex and set the freefn
        let mut free_fn_guard = FREE_FN.lock().unwrap();
        if let Some(mut wrapper) = free_fn_guard.take() {
            item.freefn = Some(Box::new(move |ptr| wrapper.0(ptr.map(|p| p as Box<dyn std::any::Any + Send>))));
        }
    } else {
        item.ptr = ptr;
        item.freefn = pfree;
    }

    item.type_ = 0xC0;
    item.size = size;
    1
}
pub fn binn_get_str(value: binn) -> Option<Box<CString>> {
    // Check for NULL pointer (None in Rust)
    let mut value = value?;
    
    let mut buf = [0u8; 128];
    let mut vint: int64 = 0;

    if type_family(value.type_) == 0xf2 {
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { 
                std::slice::from_raw_parts(Box::into_raw(p.clone()) as *const u8, std::mem::size_of::<int64>()) 
            }),
            Some(&mut vint.to_ne_bytes()),
            value.type_,
            0x81,
        ) {
            return None;
        }
        
        let s = format!("{}", vint);
        buf[..s.len()].copy_from_slice(s.as_bytes());
        goto_loc_convert_value(&mut value, &buf, s.len())?;
        return Some(Box::new(CString::new(s + "\0").unwrap()));
    }

    match value.type_ {
        0x62 => {
            value.value.vdouble = value.value.vfloat as f64;
            // Fall through to 0x82 case
        }
        0x82 => {
            let s = format!("{}", value.value.vdouble);
            buf[..s.len()].copy_from_slice(s.as_bytes());
            goto_loc_convert_value(&mut value, &buf, s.len())?;
            return Some(Box::new(CString::new(s + "\0").unwrap()));
        }
        0xA0 => {
            return value.ptr.as_ref().map(|p| {
                Box::new(unsafe { CString::from_raw(Box::into_raw(p.clone()) as *mut i8) })
            });
        }
        0x80061 => {
            let s = if value.value.vbool != 0 { "true" } else { "false" };
            buf[..s.len()].copy_from_slice(s.as_bytes());
            goto_loc_convert_value(&mut value, &buf, s.len())?;
            return Some(Box::new(CString::new(s.to_string() + "\0").unwrap()));
        }
        _ => {}
    }

    None
}

fn goto_loc_convert_value(value: &mut BinnStruct, buf: &[u8], len: usize) -> Option<()> {
    let c_str = CString::new(&buf[..len]).ok()?;
    let boxed_cstr = Box::new(c_str);
    let ptr = Box::into_raw(boxed_cstr) as *mut ();
    
    value.ptr = Some(unsafe { Box::from_raw(ptr) });
    value.freefn = Some(Box::new(|ptr_opt| unsafe {
        if let Some(ptr_box) = ptr_opt {
            let ptr = Box::into_raw(ptr_box) as *mut CString;
            let _ = Box::from_raw(ptr);
        }
    }));
    value.type_ = 0xA0;
    Some(())
}
pub fn binn_list_next_value(iter: Option<&mut BinnIter>) -> Option<Box<BinnStruct>> {
    // Allocate memory for a new BinnStruct using binn_malloc
    let value_ptr = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    
    // Convert the raw pointer to a mutable reference to BinnStruct
    let value = value_ptr.and_then(|mut ptr| {
        ptr.downcast_mut::<BinnStruct>().map(|binn_ref| {
            // Create a new Box from the reference (this is a simplified approach)
            // In a real implementation, we'd need to handle the memory properly
            Box::new(BinnStruct {
                header: binn_ref.header,
                allocated: binn_ref.allocated,
                writable: binn_ref.writable,
                dirty: binn_ref.dirty,
                pbuf: binn_ref.pbuf.take(),
                pre_allocated: binn_ref.pre_allocated,
                alloc_size: binn_ref.alloc_size,
                used_size: binn_ref.used_size,
                type_: binn_ref.type_,
                ptr: binn_ref.ptr.take(),
                size: binn_ref.size,
                count: binn_ref.count,
                freefn: binn_ref.freefn.take(),
                value: BinnValue {
                    vint8: binn_ref.value.vint8,
                    vint16: binn_ref.value.vint16,
                    vint32: binn_ref.value.vint32,
                    vint64: binn_ref.value.vint64,
                    vuint8: binn_ref.value.vuint8,
                    vuint16: binn_ref.value.vuint16,
                    vuint32: binn_ref.value.vuint32,
                    vuint64: binn_ref.value.vuint64,
                    vchar: binn_ref.value.vchar,
                    vuchar: binn_ref.value.vuchar,
                    vshort: binn_ref.value.vshort,
                    vushort: binn_ref.value.vushort,
                    vint: binn_ref.value.vint,
                    vuint: binn_ref.value.vuint,
                    vfloat: binn_ref.value.vfloat,
                    vdouble: binn_ref.value.vdouble,
                    vbool: binn_ref.value.vbool,
                },
                disable_int_compression: binn_ref.disable_int_compression,
            })
        })
    });

    if let Some(mut value_box) = value {
        // Convert Box<BinnStruct> to binn (Option<Box<BinnStruct>>)
        let mut binn_value: binn = Some(value_box);
        
        // Call binn_list_next with mutable references to iter and value
        let result = binn_list_next(iter, Some(&mut binn_value));
        
        if result == 0 {
            // If binn_list_next fails, free the allocated memory using free_fn
            if let Ok(mut free_fn_guard) = FREE_FN.lock() {
                if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                    // Convert binn to the expected type for free_fn
                    let any_box: Box<dyn std::any::Any + Send> = Box::new(binn_value);
                    (free_fn_wrapper.0)(Some(any_box));
                }
            }
            return None;
        }
        
        // Extract the value from the Option and mark it as allocated
        if let Some(mut value_box) = binn_value {
            value_box.allocated = 1;
            Some(value_box)
        } else {
            None
        }
    } else {
        None
    }
}
pub fn binn_map_next_value(iter: Option<&mut BinnIter>, pid: Option<&mut i32>) -> Option<Box<BinnStruct>> {
    let value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(ptr) => ptr,
        None => return None,
    };
    
    let mut value = match value.downcast::<BinnStruct>() {
        Ok(boxed) => boxed,
        Err(_) => return None,
    };
    
    let mut binn_value: binn = Some(value);
    let result = binn_map_next(iter, pid, Some(&mut binn_value));
    
    if result == 0 {
        if let Some(mut free_fn_guard) = FREE_FN.lock().ok() {
            if let Some(free_fn_wrapper) = free_fn_guard.as_mut() {
                (free_fn_wrapper.0)(binn_value.map(|v| v as Box<dyn std::any::Any + Send>));
            }
        }
        return None;
    }
    
    let mut value = binn_value.unwrap();
    value.allocated = 1;
    Some(value)
}
pub fn binn_object_next_value(iter: Option<&mut BinnIter>, pkey: Option<&mut [u8]>) -> Option<binn> {
    let mut value_box = binn_malloc(std::mem::size_of::<BinnStruct>() as i32)?;
    
    let value_ptr = value_box
        .downcast_mut::<BinnStruct>()
        .map(|v| v as *mut BinnStruct)
        .map(|ptr| unsafe { &mut *ptr })?;
    
    // Initialize the allocated memory with default values
    unsafe {
        std::ptr::write(value_ptr, BinnStruct {
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
            value: BinnValue {
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
            },
            disable_int_compression: 0,
        });
    }

    let mut binn_value: binn = Some(unsafe { Box::from_raw(value_ptr) });

    let result = binn_object_next(iter, pkey, Some(&mut binn_value));
    
    if result == 0 {
        if let Some(mut free_fn) = FREE_FN.lock().ok().and_then(|mut guard| guard.take()) {
            // Convert to the expected Send trait object
            let send_value_box: Box<dyn std::any::Any + Send> = unsafe {
                std::mem::transmute(value_box)
            };
            (free_fn.0)(Some(send_value_box));
        }
        return None;
    }
    
    // Extract the Box<BinnStruct> and mark it as allocated
    if let Some(mut value) = binn_value {
        value.allocated = 1;
        Some(Some(value))
    } else {
        None
    }
}
pub fn binn_get_int32(value: Option<&BinnStruct>, pint: Option<&mut i32>) -> BOOL {
    // Check for null pointers (translated to Option checks in Rust)
    if value.is_none() || pint.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pint = pint.unwrap();

    if type_family(value.type_) == 0xf2 {
        return if copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, value.size as usize) }),
            Some(&mut [*pint as u8; 4]),
            value.type_,
            0x61,
        ) {
            1
        } else {
            0
        };
    }

    match value.type_ {
        0x62 => {
            let vfloat = value.value.vfloat as f64;
            if vfloat < i32::MIN as f64 || vfloat > i32::MAX as f64 {
                return 0;
            }
            *pint = if vfloat >= 0.0 {
                (vfloat + 0.5) as i32
            } else {
                let int_part = vfloat as i32;
                if (vfloat - int_part as f64) <= -0.5 {
                    int_part
                } else {
                    (vfloat - 0.5) as i32
                }
            };
        }
        0x82 => {
            let vdouble = value.value.vdouble;
            if vdouble < i32::MIN as f64 || vdouble > i32::MAX as f64 {
                return 0;
            }
            *pint = if vdouble >= 0.0 {
                (vdouble + 0.5) as i32
            } else {
                let int_part = vdouble as i32;
                if (vdouble - int_part as f64) <= -0.5 {
                    int_part
                } else {
                    (vdouble - 0.5) as i32
                }
            };
        }
        0xA0 => {
            let ptr = value.ptr.as_ref().map(|p| unsafe { CStr::from_ptr(p.as_ref() as *const _ as *const i8) });
            if let Some(cstr) = ptr {
                if let Ok(s) = cstr.to_str() {
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
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        }
        0x80061 => {
            *pint = value.value.vbool as i32;
        }
        _ => return 0,
    }

    1
}
pub fn binn_add_value(
    item: &mut binn,
    binn_type: i32,
    id: i32,
    name: Option<&str>,
    type_: i32,
    pvalue: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
    match binn_type {
        0xE0 => binn_list_add(item, type_, pvalue, size),
        0xE1 => binn_map_set(item, id, type_, pvalue, size),
        0xE2 => binn_object_set(item, name, type_, pvalue, size),
        _ => 0,
    }
}

pub fn is_bool_str(str: Option<&str>, pbool: Option<&mut BOOL>) -> BOOL {
    // Check for null pointers (None in Rust)
    if str.is_none() || pbool.is_none() {
        return 0;
    }

    let str = str.unwrap();
    let pbool = pbool.unwrap();

    // Convert &str to CStr for case-insensitive comparison
    let cstr = CStr::from_bytes_with_nul(str.as_bytes()).unwrap_or_default();

    // Helper function for case-insensitive comparison
    fn compare_ignore_case(s1: &CStr, s2: &str) -> bool {
        s1.to_bytes().eq_ignore_ascii_case(s2.as_bytes())
    }

    // Check for true variants
    if compare_ignore_case(&cstr, "true") 
        || compare_ignore_case(&cstr, "yes") 
        || compare_ignore_case(&cstr, "on") {
        *pbool = 1;
        return 1;
    }

    // Check for false variants
    if compare_ignore_case(&cstr, "false") 
        || compare_ignore_case(&cstr, "no") 
        || compare_ignore_case(&cstr, "off") {
        *pbool = 0;
        return 1;
    }

    // Check for numeric values
    if is_integer(Some(str)) != 0 {
        if let Some(vint) = atoi64(Some(str)) {
            *pbool = if vint != 0 { 1 } else { 0 };
            return 1;
        }
    } else if is_float(Some(str)) != 0 {
        // Using Rust's parse instead of atof for safety
        if let Ok(vdouble) = str.parse::<f64>() {
            *pbool = if vdouble != 0.0 { 1 } else { 0 };
            return 1;
        }
    }

    0
}

pub fn binn_get_bool(value: Option<&BinnStruct>, pbool: Option<&mut BOOL>) -> BOOL {
    // Check for null pointers (translated to Option checks)
    if value.is_none() || pbool.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pbool = pbool.unwrap();

    if type_family(value.type_) == 0xf2 {
        let mut vint: int64 = 0;
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, value.size as usize) }),
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
            *pbool = value.value.vbool;
        }
        0x62 => {
            *pbool = if value.value.vfloat != 0.0 { 1 } else { 0 };
        }
        0x82 => {
            *pbool = if value.value.vdouble != 0.0 { 1 } else { 0 };
        }
        0xA0 => {
            let ptr = value.ptr.as_ref().map(|p| unsafe { CStr::from_ptr(p.as_ref() as *const _ as *const c_char) });
            let str = ptr.and_then(|cstr| cstr.to_str().ok());
            return is_bool_str(str, Some(pbool));
        }
        _ => {
            return 0;
        }
    }

    1
}
pub fn binn_get_int64(value: binn, pint: Option<&mut int64>) -> BOOL {
    // Check for null pointers (translated to Option in Rust)
    if value.is_none() || pint.is_none() {
        return 0;
    }

    let value = value.unwrap();
    let pint = pint.unwrap();

    if type_family(value.type_) == 0xf2 {
        return if copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, value.size as usize) }),
            Some(unsafe { std::slice::from_raw_parts_mut(pint as *mut _ as *mut u8, 8) }),
            value.type_,
            0x81,
        ) {
            1
        } else {
            0
        };
    }

    match value.type_ {
        0x62 => {
            let vfloat = value.value.vfloat as f64;
            if vfloat < INT64_MIN as f64 || vfloat > INT64_MAX as f64 {
                return 0;
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
            let vdouble = value.value.vdouble;
            if vdouble < INT64_MIN as f64 || vdouble > INT64_MAX as f64 {
                return 0;
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
            if let Some(ptr) = value.ptr.as_ref() {
                let c_str = unsafe { CStr::from_ptr(ptr.as_ref() as *const _ as *const i8) };
                if let Ok(s) = c_str.to_str() {
                    if is_integer(Some(s)) != 0 {
                        if let Some(val) = atoi64(Some(s)) {
                            *pint = val;
                        } else {
                            return 0;
                        }
                    } else if is_float(Some(s)) != 0 {
                        let float_val = s.parse::<f64>().unwrap_or(0.0);
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
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        }
        0x80061 => {
            *pint = value.value.vbool as int64;
        }
        _ => return 0,
    }

    1
}

const INT64_MIN: int64 = i64::MIN;
const INT64_MAX: int64 = i64::MAX;
pub fn binn_get_double(value: Option<&BinnStruct>, pfloat: Option<&mut f64>) -> bool {
    // Check for null inputs (equivalent to NULL checks in C)
    if value.is_none() || pfloat.is_none() {
        return false;
    }
    let value = value.unwrap();
    let pfloat = pfloat.unwrap();

    let mut vint: i64 = 0;
    if type_family(value.type_) == 0xf2 {
        if !copy_int_value(
            value.ptr.as_ref().map(|p| unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, 8) }),
            Some(&mut vint.to_ne_bytes()),
            value.type_,
            0x81,
        ) {
            return false;
        }
        *pfloat = vint as f64;
        return true;
    }

    match value.type_ {
        0x62 => {
            *pfloat = value.value.vfloat as f64;
        }
        0x82 => {
            *pfloat = value.value.vdouble;
        }
        0xA0 => {
            let ptr_str = unsafe {
                CStr::from_ptr(value.ptr.as_ref().unwrap().as_ref() as *const _ as *const i8)
                    .to_str()
                    .ok()
            };
            if is_integer(ptr_str) == 1 {
                if let Some(num) = atoi64(ptr_str) {
                    *pfloat = num as f64;
                } else {
                    return false;
                }
            } else if is_float(ptr_str) == 1 {
                if let Some(s) = ptr_str {
                    *pfloat = f64::from_str(s).unwrap_or(0.0);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        0x80061 => {
            *pfloat = value.value.vbool as f64;
        }
        _ => return false,
    }

    true
}
