use crate::*;
use lazy_static::lazy_static;
use std::any::Any;
use std::cmp::Ordering;
use std::convert::TryFrom;
use std::convert::TryInto;
use std::ffi::CStr;
use std::ffi::CString;
use std::mem;
use std::os::raw::c_char;
use std::ptr;
use std::slice;
use std::str::FromStr;
use std::sync::Mutex;

pub fn binn_version() -> &'static str {
	println!("\n* binn_version");
    "3.0.0"
}
pub fn binn_create_type(storage_type: i32, data_type_index: i32) -> i32 {
	println!("\n* binn_create_type");
    if data_type_index < 0 {
        return -1;
    }
    if (storage_type < 0x00) || (storage_type > 0xE0) {
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
pub fn binn_is_struct(ptr: Option<*mut u32>) -> bool {
	println!("\n* binn_is_struct");
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
	println!("\n* strlen2");
    match str {
        None => 0,
        Some(s) => s.len(),
    }
}
pub fn binn_get_ptr_type(ptr: Option<*mut u8>) -> i32 {
	println!("\n* binn_get_ptr_type");
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
	println!("\n* CalcAllocation");
    let mut calc_size = alloc_size;
    while calc_size < needed_size {
        calc_size <<= 1;
    }
    calc_size
}
pub fn type_family(type_: i32) -> i32 {
	println!("\n* type_family");
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
                    if let Some(bool_value) = any_box.downcast_ref::<BOOL>() {
                        let new_type = if *bool_value != 0 { 0x01 } else { 0x02 };
                        *ptype = new_type;
                    } else {
                        return false;
                    }
                }
            }
        }
        _ => {}
    }

    true
}
pub fn int_type(type_: i32) -> i32 {
	println!("\n* int_type");
    match type_ {
        0x21 | 0x41 | 0x61 | 0x81 => 11,
        0x20 | 0x40 | 0x60 | 0x80 => 22,
        _ => 0,
    }
}

pub fn copy_raw_value(psource: Option<&mut [u8]>, pdest: Option<&mut [u8]>, data_store: i32) -> bool {
	println!("\n* copy_raw_value");
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
	println!("\n* copy_float_value");
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
	println!("\n* copy_float_value_reverse");
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
	println!("\n* binn_get_read_storage");
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
	println!("\n* zero_value");
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
	println!("\n* copy_int_value");
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
	println!("\n* copy_value");
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
    let source = psource.to_ne_bytes();
    let mut dest_bytes = [0u8; 4];
    for i in 0..4 {
        dest_bytes[i] = source[3 - i];
    }
    *pdest = u32::from_ne_bytes(dest_bytes);
}
pub fn binn_save_header(item: &mut binn) -> BOOL {
	println!("\n* binn_save_header");
    // Check for NULL pointer (None in Rust)
    if item.is_none() {
        return 0;
    }

    let item = item.as_mut().unwrap(); // Safe unwrap after None check

    // Calculate initial p_idx and size
    let mut p_idx = 9;
    let mut size = (item.used_size - 9) + 3;

    // Get mutable reference to pbuf as bytes
    let p = item.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8;
    let p = unsafe { std::slice::from_raw_parts_mut(p, item.used_size as usize) };

    // Handle count
    if item.count > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (item.count as u32) | 0x80000000;
        copy_be32(
            unsafe { &mut *(p[p_idx as usize..].as_mut_ptr() as *mut u32) },
            &int32,
        );
    } else {
        p_idx -= 1;
        p[p_idx as usize] = item.count as u8;
    }

    // Handle size
    if size > 127 {
        p_idx -= 4;
        size += 3;
        let int32 = (size as u32) | 0x80000000;
        copy_be32(
            unsafe { &mut *(p[p_idx as usize..].as_mut_ptr() as *mut u32) },
            &int32,
        );
    } else {
        p_idx -= 1;
        p[p_idx as usize] = size as u8;
    }

    // Set type
    p_idx -= 1;
    p[p_idx as usize] = item.type_ as u8;

    // Update item fields
    item.ptr = Some(Box::new(())); // Changed to match the expected Box<()> type
    item.size = size;
    item.dirty = 0;

    1
}
pub fn binn_ptr(ptr: Option<*mut u8>) -> Option<*mut u8> {
	println!("\n* binn_ptr");
    match binn_get_ptr_type(ptr) {
        1 => {
            if let Some(p) = ptr {
                let mut item_val = Some(Box::new(unsafe { std::ptr::read(p as *const BinnStruct) }));
                let needs_save = if let Some(ref b) = item_val {
                    b.writable != 0 && b.dirty != 0
                } else {
                    false
                };
                if needs_save {
                    binn_save_header(&mut item_val);
                }
                item_val.as_ref().and_then(|b| b.ptr.as_ref().map(|p| p.as_ref() as *const _ as *mut u8))
            } else {
                None
            }
        },
        2 => ptr,
        _ => None,
    }
}
pub fn copy_be64(pdest: &mut u64, psource: &u64) {
    let source = psource.to_ne_bytes();
    let mut dest_bytes = [0u8; 8];
    for i in 0..8 {
        dest_bytes[i] = source[7 - i];
    }
    *pdest = u64::from_ne_bytes(dest_bytes);
}
pub fn copy_be16(pdest: &mut u16, psource: &u16) {
    *pdest = psource.swap_bytes();
}
pub fn IsValidBinnHeader(
    pbuf: Option<&[u8]>,
    ptype: Option<&mut i32>,
    pcount: Option<&mut i32>,
    psize: Option<&mut i32>,
    pheadersize: Option<&mut i32>,
) -> bool {
	println!("\n* IsValidBinnHeader");
    // Check for NULL pointer equivalent
    let pbuf = match pbuf {
        Some(buf) => buf,
        None => return false,
    };

    let mut p_idx: usize = 0;
    let plimit_idx = psize.as_ref().and_then(|s| if **s > 0 { Some(p_idx + (**s as usize).saturating_sub(1)) } else { None });

    // Check first byte
    if p_idx >= pbuf.len() {
        return false;
    }
    let byte = pbuf[p_idx];
    p_idx += 1;

    if (byte & 0xE0) != 0xE0 || (byte & 0x10) != 0 {
        return false;
    }

    let type_ = byte;
    match type_ {
        0xE0 | 0xE1 | 0xE2 => (),
        _ => return false,
    }

    // Check bounds
    if let Some(limit) = plimit_idx {
        if p_idx > limit {
            return false;
        }
    }

    // Read size
    if p_idx >= pbuf.len() {
        return false;
    }
    let mut int32 = pbuf[p_idx] as i32;
    p_idx += 1;

    if int32 & 0x80 != 0 {
        if p_idx + 3 >= pbuf.len() {
            return false;
        }
        if let Some(limit) = plimit_idx {
            if p_idx + 3 > limit {
                return false;
            }
        }
        let mut temp = [0u8; 4];
        temp.copy_from_slice(&pbuf[p_idx-1..p_idx+3]);
        int32 = i32::from_be_bytes(temp) & 0x7FFFFFFF;
        p_idx += 3;
    }

    let size = int32;

    // Read count
    if p_idx >= pbuf.len() {
        return false;
    }
    let mut int32 = pbuf[p_idx] as i32;
    p_idx += 1;

    if int32 & 0x80 != 0 {
        if p_idx + 3 >= pbuf.len() {
            return false;
        }
        if let Some(limit) = plimit_idx {
            if p_idx + 3 > limit {
                return false;
            }
        }
        let mut temp = [0u8; 4];
        temp.copy_from_slice(&pbuf[p_idx-1..p_idx+3]);
        int32 = i32::from_be_bytes(temp) & 0x7FFFFFFF;
        p_idx += 3;
    }

    let count = int32;

    // Validate values
    if size < 3 || count < 0 {
        return false;
    }

    // Write output parameters
    if let Some(ptype) = ptype {
        *ptype = type_ as i32;
    }
    if let Some(pcount) = pcount {
        *pcount = count;
    }
    if let Some(psize) = psize {
        if *psize == 0 {
            *psize = size;
        }
    }
    if let Some(pheadersize) = pheadersize {
        *pheadersize = p_idx.try_into().unwrap();
    }

    true
}
pub fn GetValue(p: Option<&[u8]>, value: Option<&mut binn>) -> BOOL {
	println!("\n* GetValue");
    let Some(p) = p else {
        return 0;
    };
    let Some(value) = value else {
        return 0;
    };

    let mut p_idx = 0;
    let mut p2_idx = 0;
    let mut data_type;
    let mut storage_type;
    let mut DataSize: u32 = 0;
    let mut p2: *mut u8 = ptr::null_mut();

    // Initialize value (equivalent to memset)
    *value = Some(Box::new(BinnStruct {
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
    }));

    let value = value.as_mut().unwrap();

    if p_idx >= p.len() {
        return 0;
    }
    let byte = p[p_idx];
    p_idx += 1;

    storage_type = byte & 0xE0;
    if byte & 0x10 != 0 {
        data_type = (byte as i32) << 8;
        if p_idx >= p.len() {
            return 0;
        }
        let byte = p[p_idx];
        p_idx += 1;
        data_type |= byte as i32;
    } else {
        data_type = byte as i32;
    }
    value.type_ = data_type;

    match storage_type {
        0x00 => (),
        0x20 => {
            if p_idx >= p.len() {
                return 0;
            }
            value.value.vuint8 = p[p_idx];
            value.ptr = Some(Box::new(()));
        }
        0x40 => {
            if p_idx + 1 >= p.len() {
                return 0;
            }
            let src = unsafe { &*(p[p_idx..].as_ptr() as *const u16) };
            copy_be16(&mut value.value.vuint16, src);
            value.ptr = Some(Box::new(()));
        }
        0x60 => {
            if p_idx + 3 >= p.len() {
                return 0;
            }
            let src = unsafe { &*(p[p_idx..].as_ptr() as *const u32) };
            copy_be32(&mut value.value.vuint32, src);
            value.ptr = Some(Box::new(()));
        }
        0x80 => {
            if p_idx + 7 >= p.len() {
                return 0;
            }
            let src = unsafe { &*(p[p_idx..].as_ptr() as *const u64) };
            copy_be64(&mut value.value.vuint64, src);
            value.ptr = Some(Box::new(()));
        }
        0xA0 | 0xC0 => {
            if p_idx >= p.len() {
                return 0;
            }
            DataSize = p[p_idx] as u32;
            if DataSize & 0x80 != 0 {
                if p_idx + 3 >= p.len() {
                    return 0;
                }
                let src = unsafe { &*(p[p_idx..].as_ptr() as *const u32) };
                let mut temp = src & 0x7FFFFFFF;
                copy_be32(&mut DataSize, &temp);
                p_idx += 4;
            } else {
                p_idx += 1;
            }
            value.size = DataSize as i32;
            value.ptr = Some(Box::new(()));
        }
        0xE0 => {
            value.ptr = Some(Box::new(()));
            if !IsValidBinnHeader(
                Some(unsafe { std::slice::from_raw_parts(p2.add(p2_idx), 0) }),
                None,
                Some(&mut value.count),
                Some(&mut value.size),
                None,
            ) {
                return 0;
            }
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
        _ => (),
    }

    1
}
pub fn AdvanceDataPos(p: &[u8], plimit: usize) -> Option<&[u8]> {
	println!("\n* AdvanceDataPos");
    let mut p_idx = 0;
    
    // Check initial bounds
    if p_idx >= p.len() || p_idx > plimit {
        return None;
    }

    let byte = p[p_idx];
    p_idx += 1;
    let storage_type = byte & 0xE0;

    if byte & 0x10 != 0 {
        p_idx += 1;
    }

    match storage_type {
        0x00 => (), // No additional processing needed
        0x20 => p_idx += 1,
        0x40 => p_idx += 2,
        0x60 => p_idx += 4,
        0x80 => p_idx += 8,
        0xA0 | 0xC0 => {
            if p_idx >= p.len() || p_idx > plimit {
                return None;
            }

            let mut DataSize = p[p_idx] as i32;
            if DataSize & 0x80 != 0 {
                if p_idx + 4 > p.len() || p_idx + 4 - 1 > plimit {
                    return None;
                }
                let mut temp = 0u32;
                copy_be32(&mut temp, &u32::from_be_bytes([
                    p[p_idx], p[p_idx + 1], p[p_idx + 2], p[p_idx + 3]
                ]));
                DataSize = (temp & 0x7FFFFFFF) as i32;
                p_idx += 4;
            } else {
                p_idx += 1;
            }

            p_idx += DataSize as usize;
            if storage_type == 0xA0 {
                p_idx += 1;
            }
        }
        0xE0 => {
            if p_idx >= p.len() || p_idx > plimit {
                return None;
            }

            let mut DataSize = p[p_idx] as i32;
            if DataSize & 0x80 != 0 {
                if p_idx + 4 > p.len() || p_idx + 4 - 1 > plimit {
                    return None;
                }
                let mut temp = 0u32;
                copy_be32(&mut temp, &u32::from_be_bytes([
                    p[p_idx], p[p_idx + 1], p[p_idx + 2], p[p_idx + 3]
                ]));
                DataSize = (temp & 0x7FFFFFFF) as i32;
                p_idx += 4;
            }
            DataSize -= 1;
            p_idx += DataSize as usize;
        }
        _ => return None,
    }

    // Final bounds check
    if p_idx > p.len() || p_idx > plimit {
        None
    } else {
        Some(&p[p_idx..])
    }
}
pub fn binn_list_get_value(ptr: Option<&[u8]>, pos: i32, value: Option<&mut binn>) -> BOOL {
	println!("\n* binn_list_get_value");
    let ptr_idx = 0;
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Check for null pointers (converted to Option checks in Rust)
    if ptr.is_none() || value.is_none() {
        return 0;
    }
    let ptr = ptr.unwrap();
    let value = value.unwrap();

    // Validate the Binn header
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

    // Check if list is empty
    if count == 0 {
        return 0;
    }

    // Check position is valid
    if pos <= 0 || pos > count {
        return 0;
    }

    let pos = pos - 1; // Convert to 0-based index
    let p = ptr;
    let base = p.as_ptr();
    let plimit = unsafe { base.add(size as usize) };

    let mut p_slice = &p[header_size as usize..];
    
    for _ in 0..pos {
        if let Some(new_p) = AdvanceDataPos(p_slice, plimit as usize) {
            p_slice = new_p;
        } else {
            return 0;
        }

        // Check if we've gone past the beginning or reached null
        if p_slice.is_empty() || p_slice.as_ptr() < base {
            return 0;
        }
    }

    GetValue(Some(p_slice), Some(value))
}
pub fn binn_list_get(
    ptr: Option<&[u8]>,
    pos: i32,
    type_: i32,
    mut pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
	println!("\n* binn_list_get");
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
	println!("\n* read_map_id");
    let mut p_idx = 0;
    let mut c;
    let mut sign;
    let mut type_;
    let mut id = 0;
    let mut extra_bytes;

    // Get current position from pp
    let p = *pp;
    if p.is_empty() {
        return None;
    }
    c = p[p_idx];
    p_idx += 1;

    if c & 0x80 != 0 {
        extra_bytes = ((c & 0x60) >> 5) + 1;
        if p_idx + extra_bytes as usize > p.len() {
            *pp = &p[p.len()..]; // Move pp beyond limit
            return None;
        }
    }

    type_ = c & 0xE0;
    sign = c & 0x10;

    if (c & 0x80) == 0 {
        sign = c & 0x40;
        id = (c & 0x3F) as i32;
    } else if type_ == 0x80 {
        if p_idx + 1 > p.len() {
            *pp = &p[p.len()..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
    } else if type_ == 0xA0 {
        if p_idx + 2 > p.len() {
            *pp = &p[p.len()..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
    } else if type_ == 0xC0 {
        if p_idx + 3 > p.len() {
            *pp = &p[p.len()..];
            return None;
        }
        id = (c & 0x0F) as i32;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
        id = (id << 8) | (p[p_idx] as i32);
        p_idx += 1;
    } else if type_ == 0xE0 {
        if p_idx + 4 > p.len() {
            *pp = &p[p.len()..];
            return None;
        }
        let mut source = 0u32;
        copy_be32(&mut source, &u32::from_be_bytes(p[p_idx..p_idx+4].try_into().unwrap()));
        id = source as i32;
        p_idx += 4;
    } else {
        *pp = &p[p.len()..];
        return None;
    }

    if sign != 0 {
        id = -id;
    }

    *pp = &p[p_idx..];
    Some(id)
}
pub fn SearchForID(p: &[u8], header_size: usize, size: usize, numitems: usize, id: i32) -> Option<&[u8]> {
	println!("\n* SearchForID");
    let mut p_idx = 0;
    let base = &p[p_idx..];
    let plimit = &p[(p_idx + size - 1)..];
    p_idx += header_size;

    for _ in 0..numitems {
        let mut current_slice = &p[p_idx..];
        let int32 = match read_map_id(&mut current_slice, plimit) {
            Some(val) => val,
            None => break,
        };

        if current_slice.as_ptr() > plimit.as_ptr() {
            break;
        }

        if int32 == id {
            return Some(p);
        }

        match AdvanceDataPos(&p[p_idx..], plimit.as_ptr() as usize) {
            Some(new_slice) => {
                p_idx = new_slice.as_ptr() as usize - p.as_ptr() as usize;
            }
            None => break,
        }

        if p_idx == 0 || p[p_idx..].as_ptr() < base.as_ptr() {
            break;
        }
    }

    None
}
pub fn binn_map_get_value(ptr: Option<&[u8]>, id: i32, value: Option<&mut binn>) -> BOOL {
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    if ptr.is_none() || value.is_none() {
        return 0;
    }
    let ptr = ptr.unwrap();
    let value = value.unwrap();

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
    mut pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
	println!("\n* binn_map_get");
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
	println!("\n* SearchForKey");
    // Check for None inputs (equivalent to NULL checks in C)
    let p = p?;
    let key = key?;

    let key_bytes = key.as_bytes();
    let keylen = key_bytes.len();

    let base = p;
    let plimit = &p[size - 1..]; // Rust slices are exclusive, so no need for -1 adjustment

    let mut p_idx = header_size;
    let mut current_p = &p[p_idx..];

    for _ in 0..numitems {
        if current_p.is_empty() {
            break;
        }

        let len = current_p[0] as usize;
        current_p = &current_p[1..];
        p_idx += 1;

        if current_p.as_ptr() > plimit.as_ptr() {
            break;
        }

        if len > 0 {
            if len <= current_p.len() {
                let item_slice = &current_p[..len];
                // Case-insensitive comparison (approximation of strncasecmp)
                if item_slice.len() >= key_bytes.len() {
                    let comparison = item_slice
                        .iter()
                        .zip(key_bytes.iter())
                        .map(|(&a, &b)| a.to_ascii_lowercase().cmp(&b.to_ascii_lowercase()))
                        .find(|&ord| ord != Ordering::Equal)
                        .unwrap_or(Ordering::Equal);

                    if comparison == Ordering::Equal && len == keylen {
                        return Some(&p[p_idx - 1..]); // Return including the length byte
                    }
                }
            }

            p_idx += len;
            current_p = &p[p_idx..];

            if current_p.as_ptr() > plimit.as_ptr() {
                break;
            }
        } else if keylen == 0 {
            return Some(&p[p_idx - 1..]); // Return including the length byte
        }

        if let Some(advanced) = AdvanceDataPos(&p[p_idx..], plimit.as_ptr() as usize) {
            p_idx = unsafe { advanced.as_ptr().offset_from(p.as_ptr()) } as usize;
            current_p = advanced;
        } else {
            break;
        }

        if current_p.is_empty() || current_p.as_ptr() < base.as_ptr() {
            break;
        }
    }

    None
}
pub fn binn_object_get_value(ptr: Option<&[u8]>, key: Option<&str>, value: Option<&mut binn>) -> BOOL {
    let raw_ptr = ptr.map(|p| p.as_ptr() as *mut u8);
    let resolved_ptr = binn_ptr(raw_ptr);
    if resolved_ptr.is_none() || key.is_none() || value.is_none() {
        return 0;
    }

    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    if !IsValidBinnHeader(
        ptr,
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return 0;
    }

    if type_ != 0xE2 {
        return 0;
    }

    if count == 0 {
        return 0;
    }

    let p = ptr.unwrap();
    let p_idx = SearchForKey(
        Some(p),
        header_size as usize,
        size as usize,
        count,
        key,
    );
    if p_idx.is_none() {
        return 0;
    }

    GetValue(p_idx, value)
}
pub fn binn_object_get(
    ptr: Option<&[u8]>,
    key: Option<&str>,
    type_: i32,
    mut pvalue: Option<&mut dyn Any>,
    psize: Option<&mut i32>,
) -> i32 {
	println!("\n* binn_object_get");
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
	println!("\n* binn_is_valid_ex");
    let pbuf = binn_ptr(ptr);
    if pbuf.is_none() {
        return false;
    }
    let pbuf = pbuf.unwrap();

    let mut size = match psize.as_ref() {
        Some(s) if **s > 0 => **s,
        _ => 0,
    };

    let mut type_ = 0;
    let mut count = 0;
    let mut header_size = 0;

    if !IsValidBinnHeader(
        Some(unsafe { std::slice::from_raw_parts(pbuf, size as usize) }),
        ptype.as_deref_mut(),
        pcount.as_deref_mut(),
        psize.as_deref_mut(),
        Some(&mut header_size),
    ) {
        return false;
    }

    if let Some(s) = psize.as_ref() {
        if **s > 0 && size != **s {
            return false;
        }
    }

    if let Some(c) = pcount.as_ref() {
        if **c > 0 && count != **c {
            return false;
        }
    }

    if let Some(t) = ptype.as_ref() {
        if **t != 0 && type_ != **t {
            return false;
        }
    }

    let p = unsafe { std::slice::from_raw_parts(pbuf, size as usize) };
    let base = p.as_ptr();
    let plimit = unsafe { p.as_ptr().add(size as usize) };
    let mut p_idx = header_size as usize;

    for _ in 0..count {
        match type_ {
            0xE2 => {
                let len = p[p_idx] as usize;
                p_idx += 1;
                p_idx += len;
            }
            0xE1 => {
                let mut pp = &p[p_idx..];
                if read_map_id(&mut pp, unsafe {
                    std::slice::from_raw_parts(plimit, (p.len() - p_idx) as usize)
                }).is_none() {
                    return false;
                }
                p_idx = p.len() - pp.len();
            }
            _ => (),
        }

        if let Some(new_pos) = AdvanceDataPos(&p[p_idx..], plimit as usize) {
            p_idx = p.len() - new_pos.len();
        } else {
            return false;
        }

        let current_ptr = unsafe { p.as_ptr().add(p_idx) };
        if current_ptr.is_null() || current_ptr < base {
            return false;
        }
    }

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
	println!("\n* atoi64");
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
            return None; // Invalid character encountered
        }
        retval = (10 * retval) + (c.to_digit(10).unwrap() as int64);
    }
    
    if is_negative {
        retval *= -1;
    }
    
    Some(retval)
}
pub fn binn_get_write_storage(type_: i32) -> i32 {
	println!("\n* binn_get_write_storage");
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
	println!("\n* binn_is_container");
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
	println!("\n* binn_is_valid");
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
	println!("\n* binn_list_int8");
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
	println!("\n* binn_list_int16");
    let mut value: i16 = 0;
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    binn_list_get(list, pos, 0x41, pvalue, None);
    value
}
pub fn binn_list_int32(list: Option<&[u8]>, pos: i32) -> i32 {
	println!("\n* binn_list_int32");
    let mut value = 0;
    binn_list_get(list, pos, 0x61, Some(&mut value), None);
    value
}
pub fn binn_list_uint8(list: Option<&[u8]>, pos: i32) -> Option<u8> {
	println!("\n* binn_list_uint8");
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
	println!("\n* binn_list_uint16");
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
	println!("\n* binn_list_uint32");
    let mut value: u32 = 0;
    binn_list_get(list, pos, 0x60, Some(&mut value), None);
    value
}
pub fn binn_list_float(list: Option<&[u8]>, pos: i32) -> f32 {
	println!("\n* binn_list_float");
    let mut value: f32 = 0.0;
    binn_list_get(list, pos, 0x62, Some(&mut value), None);
    value
}
pub fn binn_list_double(list: Option<&[u8]>, pos: i32) -> f64 {
	println!("\n* binn_list_double");
    let mut value: f64 = 0.0;
    binn_list_get(list, pos, 0x82, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_list_null(list: Option<&[u8]>, pos: i32) -> BOOL {
	println!("\n* binn_list_null");
    binn_list_get(list, pos, 0x00, None, None)
}
pub fn binn_list_str(list: Option<&[u8]>, pos: i32) -> Option<String> {
	println!("\n* binn_list_str");
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
	println!("\n* binn_list_blob");
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
	println!("\n* binn_list_list");
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
	println!("\n* binn_list_map");
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
	println!("\n* binn_list_object");
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
	println!("\n* binn_map_int8");
    let mut value: i8 = 0;
    let success = binn_map_get(map, id, 0x21, Some(&mut value as &mut dyn std::any::Any), None);
    
    if success != 0 {
        Some(value)
    } else {
        Option::None
    }
}
pub fn binn_map_int16(map: Option<&[u8]>, id: i32) -> i16 {
	println!("\n* binn_map_int16");
    let mut value: i16 = 0;
    let _ = binn_map_get(map, id, 0x41, Some(&mut value), None);
    value
}
pub fn binn_map_int32(map: Option<&[u8]>, id: i32) -> i32 {
	println!("\n* binn_map_int32");
    let mut value: i32 = 0;
    binn_map_get(map, id, 0x61, Some(&mut value), None);
    value
}
pub fn binn_map_uint8(map: Option<&[u8]>, id: i32) -> Option<u8> {
	println!("\n* binn_map_uint8");
    let mut value: u8 = 0;
    let success = binn_map_get(map, id, 0x20, Some(&mut value), None);
    
    if success != 0 {
        Some(value)
    } else {
        None
    }
}
pub fn binn_map_uint16(map: Option<&[u8]>, id: i32) -> u16 {
	println!("\n* binn_map_uint16");
    let mut value: u16 = 0;
    binn_map_get(map, id, 0x40, Some(&mut value), None);
    value
}
pub fn binn_map_uint32(map: Option<&[u8]>, id: i32) -> u32 {
	println!("\n* binn_map_uint32");
    let mut value: u32 = 0;
    let _ = binn_map_get(map, id, 0x60, Some(&mut value), None);
    value
}
pub fn binn_map_float(map: Option<&[u8]>, id: i32) -> f32 {
	println!("\n* binn_map_float");
    let mut value: f32 = 0.0;
    binn_map_get(map, id, 0x62, Some(&mut value), None);
    value
}
pub fn binn_map_double(map: Option<&[u8]>, id: i32) -> f64 {
	println!("\n* binn_map_double");
    let mut value: f64 = 0.0;
    binn_map_get(map, id, 0x82, Some(&mut value), None);
    value
}
pub fn binn_map_null(map: Option<&[u8]>, id: i32) -> BOOL {
	println!("\n* binn_map_null");
    binn_map_get(map, id, 0x00, None, None)
}
pub fn binn_map_str(map: Option<&[u8]>, id: i32) -> Option<String> {
	println!("\n* binn_map_str");
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
	println!("\n* binn_map_blob");
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
	println!("\n* binn_map_list");
    let mut value: Option<Box<dyn std::any::Any>> = None;
    let pvalue: Option<&mut dyn std::any::Any> = value.as_mut().map(|v| v.as_mut());
    binn_map_get(map, id, 0xE0, pvalue, None);
    value
}
pub fn binn_map_map(map: Option<&[u8]>, id: i32) -> Option<Box<dyn std::any::Any>> {
	println!("\n* binn_map_map");
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
	println!("\n* binn_map_object");
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
	println!("\n* binn_object_int8");
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
	println!("\n* binn_object_int16");
    let mut value: i16 = 0;
    binn_object_get(obj, key, 0x41, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_int32(obj: Option<&[u8]>, key: Option<&str>) -> i32 {
	println!("\n* binn_object_int32");
    let mut value = 0;
    binn_object_get(obj, key, 0x61, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint8(obj: Option<&[u8]>, key: Option<&str>) -> u8 {
	println!("\n* binn_object_uint8");
    let mut value: u8 = 0;
    binn_object_get(obj, key, 0x20, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint16(obj: Option<&[u8]>, key: Option<&str>) -> u16 {
	println!("\n* binn_object_uint16");
    let mut value: u16 = 0;
    binn_object_get(obj, key, 0x40, Some(&mut value), None);
    value
}
pub fn binn_object_uint32(obj: Option<&[u8]>, key: Option<&str>) -> u32 {
	println!("\n* binn_object_uint32");
    let mut value: u32 = 0;
    binn_object_get(obj, key, 0x60, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_float(obj: Option<&[u8]>, key: Option<&str>) -> f32 {
	println!("\n* binn_object_float");
    let mut value: f32 = 0.0;
    binn_object_get(obj, key, 0x62, Some(&mut value), None);
    value
}
pub fn binn_object_double(obj: Option<&[u8]>, key: Option<&str>) -> f64 {
	println!("\n* binn_object_double");
    let mut value: f64 = 0.0;
    binn_object_get(obj, key, 0x82, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_null(obj: Option<&[u8]>, key: Option<&str>) -> bool {
	println!("\n* binn_object_null");
    binn_object_get(obj, key, 0x00, None, None) != 0
}
pub fn binn_object_str(obj: Option<&[u8]>, key: Option<&str>) -> Option<String> {
	println!("\n* binn_object_str");
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
	println!("\n* binn_object_blob");
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
	println!("\n* binn_object_list");
    let mut value: Option<Box<dyn Any>> = None;
    let pvalue: Option<&mut dyn Any> = value.as_mut().map(|v| v.as_mut());
    
    binn_object_get(obj, key, 0xE0, pvalue, None);
    value
}
pub fn binn_object_map(obj: Option<&[u8]>, key: Option<&str>) -> Option<Box<dyn Any>> {
	println!("\n* binn_object_map");
    let mut value: Option<Box<dyn Any>> = None;
    let pvalue: Option<&mut dyn Any> = value.as_mut().map(|v| v.as_mut());
    
    // Call binn_object_get with the appropriate parameters
    binn_object_get(obj, key, 0xE1, pvalue, None);
    
    value
}
pub fn binn_object_object(obj: Option<&[u8]>, key: Option<&str>) -> Option<Box<dyn Any>> {
	println!("\n* binn_object_object");
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
	println!("\n* check_alloc_functions");
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
    // Allocate a zero-initialized buffer of the requested size
    let buf = vec![0u8; size].into_boxed_slice();
    Some(Box::new(buf))
}

fn realloc(ptr: Option<Box<[u8]>>, new_size: usize) -> Option<Box<[u8]>> {
	println!("\n* realloc");
    // Implementation would go here
    None
}

fn free(ptr: Option<Box<dyn std::any::Any + Send>>) {
    println!("\n* free");
    if let Some(ptr) = ptr {
        drop(ptr);
    }
}
pub fn binn_malloc(size: i32) -> Option<Box<dyn std::any::Any>> {
    println!("\n* binn_malloc");
    if size < 0 {
        return None;
    }
    {
        let malloc_fn_guard = MALLOC_FN.lock().unwrap();
        if malloc_fn_guard.is_none() {
            drop(malloc_fn_guard);
            check_alloc_functions();
        }
    }
    let malloc_fn = MALLOC_FN.lock().unwrap();
    match *malloc_fn {
        Some(f) => f(size as usize),
        None => None,
    }
}
pub fn binn_memdup(src: Option<&[u8]>, size: i32) -> Option<Box<[u8]>> {
	println!("\n* binn_memdup");
    // Check for NULL pointer or invalid size
    if src.is_none() || size <= 0 {
        return Option::None;
    }

    let src = src.unwrap();
    
    // Allocate memory using binn_malloc
    let dest = match binn_malloc(size) {
        Some(alloc) => alloc,
        None => return Option::None,
    };

    // Try to downcast to a boxed byte slice
    if let Ok(mut dest_box) = dest.downcast::<Box<[u8]>>() {
        let dest_slice = &mut *dest_box;
        
        // Ensure the allocated size matches the requested size
        if dest_slice.len() != size as usize {
            return Option::None;
        }

        // Safe because we've checked sizes and have exclusive access
        dest_slice.copy_from_slice(&src[..size as usize]);
        Some(*dest_box)
    } else {
        Option::None
    }
}
pub fn binn_buf_type(pbuf: Option<&[u8]>) -> i32 {
	println!("\n* binn_buf_type");
    let mut type_ = 0; // Using type_ to avoid Rust keyword conflict
    if !IsValidBinnHeader(pbuf, Some(&mut type_), None, None, None) {
        return 0;
    }
    type_
}
pub fn binn_buf_count(pbuf: Option<&[u8]>) -> i32 {
	println!("\n* binn_buf_count");
    let mut nitems = 0;
    if !IsValidBinnHeader(pbuf, None, Some(&mut nitems), None, None) {
        return 0;
    }
    nitems
}
pub fn binn_buf_size(pbuf: Option<&[u8]>) -> i32 {
	println!("\n* binn_buf_size");
    let mut size = 0;
    if !IsValidBinnHeader(pbuf, None, None, Some(&mut size), None) {
        return 0;
    }
    size
}
pub fn is_integer(p: Option<&str>) -> BOOL {
	println!("\n* is_integer");
    // Check for NULL (None in Rust)
    let p = match p {
        Some(s) => s,
        None => return 0,
    };

    let mut p_idx = 0;
    let mut retval: BOOL;

    // Check for empty string
    if p.is_empty() {
        return 0;
    }

    // Handle negative sign
    let chars: Vec<char> = p.chars().collect();
    if chars[p_idx] == '-' {
        p_idx += 1;
        // Check if string ends after '-'
        if p_idx >= chars.len() {
            return 0;
        }
    }

    retval = 1;
    // Check remaining characters are digits
    for i in p_idx..chars.len() {
        if !chars[i].is_ascii_digit() {
            retval = 0;
        }
    }

    retval
}
pub fn is_float(p: Option<&str>) -> BOOL {
	println!("\n* is_float");
    // Check for NULL (None in Rust)
    let p = match p {
        Some(s) => s,
        None => return 0,
    };

    let mut p_idx = 0;
    let mut retval;
    let mut number_found = 0;

    // Convert string to bytes for character-by-character access
    let bytes = p.as_bytes();

    // Check empty string
    if bytes.is_empty() {
        return 0;
    }

    // Handle optional minus sign
    if bytes[p_idx] == b'-' {
        p_idx += 1;
        // Check if string ends after minus
        if p_idx >= bytes.len() {
            return 0;
        }
    }

    retval = 1;

    // Iterate through remaining characters
    while p_idx < bytes.len() {
        let c = bytes[p_idx];
        
        if c == b'.' || c == b',' {
            if number_found == 0 {
                retval = 0;
            }
        } else if c >= b'0' && c <= b'9' {
            number_found = 1;
        } else {
            return 0;
        }

        p_idx += 1;
    }

    retval
}
pub fn binn_alloc_item() -> Option<Box<BinnStruct>> {
	println!("\n* binn_alloc_item");
    // Allocate memory for the binn struct
    let item = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    
    // Convert the allocation to BinnStruct if successful
    let item = match item {
        Some(ptr) => {
            // SAFETY: We know ptr is a valid Box<BinnStruct> because binn_malloc allocated enough space
            let item = unsafe { Box::from_raw(Box::into_raw(ptr) as *mut BinnStruct) };
            
            // Initialize the struct (equivalent to memset + field assignments)
            let mut item = Box::new(BinnStruct {
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
            
            Some(item)
        },
        None => None,
    };
    
    item
}
pub fn binn_value(
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
    freefn: Option<Box<dyn FnMut(Option<Box<()>>)>>,
) -> Option<Box<BinnStruct>> {
	println!("\n* binn_value");
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

pub fn CheckAllocation(item: &mut Option<Box<BinnStruct>>, add_size: i32) -> BOOL {
	println!("\n* CheckAllocation");
    // Early return if item is None
    let item = match item {
        Some(item) => item,
        None => return 0,
    };

    if (item.used_size + add_size) > item.alloc_size {
        if item.pre_allocated != 0 {
            return 0;
        }

        let alloc_size = CalcAllocation(item.used_size + add_size, item.alloc_size);
        
        // Get the current pbuf as a byte slice if it exists
        let current_buf = item.pbuf.as_ref().map(|b| {
            let ptr = b.as_ref() as *const _ as *const u8;
            unsafe { std::slice::from_raw_parts(ptr, item.used_size as usize) }
        });

        // Convert to Box<[u8]> for reallocation
        let current_boxed_slice = current_buf.map(|slice| slice.to_vec().into_boxed_slice());

        // Lock the global realloc function
        let mut realloc_fn_guard = REALLOC_FN.lock().unwrap();
        let realloc_fn = match realloc_fn_guard.as_mut() {
            Some(f) => &mut f.0,
            None => return 0,
        };

        // Perform reallocation
        let new_buf = realloc_fn(current_boxed_slice, alloc_size as usize);

        match new_buf {
            Some(new_buf) => {
                // Update the item's fields
                item.pbuf = Some(Box::new(())); // Placeholder, actual pointer handling would need unsafe
                item.alloc_size = alloc_size;
                1
            }
            None => 0,
        }
    } else {
        1
    }
}
pub fn AddValue(
    item: &mut Option<Box<BinnStruct>>,
    mut type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
	println!("\n* AddValue");
    let mut pvalue_idx = 0;
    let mut ArgSize;
    let mut storage_type = 0;
    let mut extra_type = 0;
    let mut p_idx = 0;

    binn_get_type_info(type_, Some(&mut storage_type), Some(&mut extra_type));

    if pvalue.is_none() {
        match storage_type {
            0x00 => (),
            0xC0 | 0xA0 => {
                if size == 0 {
                    ();
                } else {
                    return 0;
                }
            }
            _ => return 0,
        }
    }

    if (type_family(type_) == 0xF2) && (item.as_ref().unwrap().disable_int_compression == 0) {
        let _ = compress_int(&mut storage_type, &mut type_, &[]);
    }

    match storage_type {
        0x00 => {
            ArgSize = 0;
        }
        0x20 => {
            ArgSize = 1;
        }
        0x40 => {
            ArgSize = 2;
        }
        0x60 => {
            ArgSize = 4;
        }
        0x80 => {
            ArgSize = 8;
        }
        0xC0 => {
            if size < 0 {
                return 0;
            }
            ArgSize = size + 4;
        }
        0xA0 => {
            if size < 0 {
                return 0;
            }
            let actual_size = if size == 0 {
                strlen2(pvalue.and_then(|v| std::str::from_utf8(v).ok()))
            } else {
                size as usize
            };
            ArgSize = actual_size as i32 + 5;
        }
        0xE0 => {
            if size <= 0 {
                return 0;
            }
            ArgSize = size;
        }
        _ => return 0,
    }

    ArgSize += 2;
    if CheckAllocation(item, ArgSize) == 0 {
        return 0;
    }

    let item_ref = item.as_mut().unwrap();
    p_idx = item_ref.used_size as usize;
    let p_ptr = if let Some(pbuf) = &mut item_ref.pbuf {
        pbuf.as_mut() as *mut _ as *mut u8
    } else {
        return 0;
    };

    if storage_type != 0xE0 {
        if type_ > 255 {
            let type16 = type_ as u16;
            copy_be16(
                unsafe { &mut *(p_ptr.add(p_idx) as *mut u16) },
                &type16,
            );
            p_idx += 2;
            item_ref.used_size += 2;
        } else {
            unsafe {
                *(p_ptr.add(p_idx)) = type_ as u8;
            }
            p_idx += 1;
            item_ref.used_size += 1;
        }
    }

    match storage_type {
        0x00 => (),
        0x20 => {
            if let Some(pvalue) = pvalue {
                unsafe {
                    *(p_ptr.add(p_idx)) = pvalue[0];
                }
                item_ref.used_size += 1;
            }
        }
        0x40 => {
            if let Some(pvalue) = pvalue {
                let value = unsafe { &*(pvalue.as_ptr() as *const u16) };
                copy_be16(
                    unsafe { &mut *(p_ptr.add(p_idx) as *mut u16) },
                    value,
                );
                item_ref.used_size += 2;
            }
        }
        0x60 => {
            if let Some(pvalue) = pvalue {
                let value = unsafe { &*(pvalue.as_ptr() as *const u32) };
                copy_be32(
                    unsafe { &mut *(p_ptr.add(p_idx) as *mut u32) },
                    value,
                );
                item_ref.used_size += 4;
            }
        }
        0x80 => {
            if let Some(pvalue) = pvalue {
                let value = unsafe { &*(pvalue.as_ptr() as *const u64) };
                copy_be64(
                    unsafe { &mut *(p_ptr.add(p_idx) as *mut u64) },
                    value,
                );
                item_ref.used_size += 8;
            }
        }
        0xC0 | 0xA0 => {
            if let Some(pvalue) = pvalue {
                let actual_size = if size == 0 {
                    pvalue.len()
                } else {
                    size as usize
                };

                if actual_size > 127 {
                    let value = (actual_size as u32) | 0x80000000;
                    copy_be32(
                        unsafe { &mut *(p_ptr.add(p_idx) as *mut u32) },
                        &value,
                    );
                    p_idx += 4;
                    item_ref.used_size += 4;
                } else {
                    unsafe {
                        *(p_ptr.add(p_idx)) = actual_size as u8;
                    }
                    p_idx += 1;
                    item_ref.used_size += 1;
                }

                unsafe {
                    ptr::copy_nonoverlapping(
                        pvalue.as_ptr(),
                        p_ptr.add(p_idx),
                        actual_size,
                    );
                }

                if storage_type == 0xA0 {
                    p_idx += actual_size;
                    unsafe {
                        *(p_ptr.add(p_idx)) = 0;
                    }
                    item_ref.used_size += 1;
                }

                item_ref.used_size += actual_size as i32;
            }
        }
        0xE0 => {
            if let Some(pvalue) = pvalue {
                unsafe {
                    ptr::copy_nonoverlapping(
                        pvalue.as_ptr(),
                        p_ptr.add(p_idx),
                        size as usize,
                    );
                }
                item_ref.used_size += size;
            }
        }
        _ => return 0,
    }

    item.as_mut().unwrap().dirty = 1;
    1
}
pub fn binn_list_add_raw(
    item: &mut binn,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
	println!("\n* binn_list_add_raw");
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

    // For integer types, we may need to convert the value to bytes.
    let int_bytes: [u8; 4];
    let raw_pvalue = match converted_type {
        0x20 => { // BINT_INT32
            match converted_pvalue {
                Some(mut v) => {
                    match v.as_ref() {
                        Some(boxed) => {
                            if let Some(val) = boxed.downcast_ref::<i32>() {
                                int_bytes = val.to_le_bytes();
                                Some(&int_bytes[..])
                            } else {
                                None
                            }
                        }
                        None => None
                    }
                }
                None => None
            }
        }
        _ => {
            converted_pvalue.and_then(|v| {
                v.as_ref().and_then(|boxed| {
                    boxed.downcast_ref::<Vec<u8>>().map(|v| v.as_slice())
                })
            })
        }
    };

    binn_list_add_raw(list, converted_type, raw_pvalue, converted_size)
}
pub fn binn_map_set_raw(
    item: &mut binn,
    id: i32,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
	println!("\n* binn_map_set_raw");
    // Check for NULL item or invalid type or not writable
    if item.is_none() || item.as_ref().unwrap().type_ != 0xE1 || item.as_ref().unwrap().writable == 0 {
        return 0;
    }

    let pbuf_slice = match &item.as_ref().unwrap().pbuf {
        Some(p) => unsafe { std::slice::from_raw_parts(p.as_ref() as *const _ as *const u8, item.as_ref().unwrap().used_size as usize) },
        None => return 0,
    };

    // Search for ID
    if SearchForID(pbuf_slice, 9, item.as_ref().unwrap().used_size as usize, item.as_ref().unwrap().count as usize, id).is_some() {
        return 0;
    }

    // Check allocation
    if CheckAllocation(item, 5) == 0 {
        return 0;
    }

    let item_ref = item.as_mut().unwrap();
    let base_ptr = match &mut item_ref.pbuf {
        Some(p) => unsafe { (p.as_mut() as *mut _ as *mut u8).add(item_ref.used_size as usize) },
        None => return 0,
    };

    let mut p_idx = 0;
    let mut sign = id < 0;
    let mut id = if sign { -id } else { id };

    unsafe {
        let p = std::slice::from_raw_parts_mut(base_ptr, (item_ref.alloc_size - item_ref.used_size) as usize);

        if id <= 0x3F {
            p[p_idx] = (sign as u8) << 6 | id as u8;
            p_idx += 1;
        } else if id <= 0xFFF {
            p[p_idx] = 0x80 | ((sign as u8) << 4) | ((id & 0xF00) >> 8) as u8;
            p_idx += 1;
            p[p_idx] = (id & 0xFF) as u8;
            p_idx += 1;
        } else if id <= 0xFFFFF {
            p[p_idx] = 0xA0 | ((sign as u8) << 4) | ((id & 0xF0000) >> 16) as u8;
            p_idx += 1;
            p[p_idx] = ((id & 0xFF00) >> 8) as u8;
            p_idx += 1;
            p[p_idx] = (id & 0xFF) as u8;
            p_idx += 1;
        } else if id <= 0xFFFFFFF {
            p[p_idx] = 0xC0 | ((sign as u8) << 4) | ((id & 0xF000000) >> 24) as u8;
            p_idx += 1;
            p[p_idx] = ((id & 0xFF0000) >> 16) as u8;
            p_idx += 1;
            p[p_idx] = ((id & 0xFF00) >> 8) as u8;
            p_idx += 1;
            p[p_idx] = (id & 0xFF) as u8;
            p_idx += 1;
        } else {
            p[p_idx] = 0xE0;
            p_idx += 1;
            if sign {
                id = -id;
            }
            let dest = &mut *(p.as_mut_ptr().add(p_idx) as *mut u32);
            let src = &*(&id as *const i32 as *const u32);
            copy_be32(dest, src);
            p_idx += 4;
        }

        let id_size = p_idx;
        item_ref.used_size += id_size as i32;

        // Release the borrow before calling AddValue
        let result = AddValue(item, type_, pvalue, size);
        if result == 0 {
            item.as_mut().unwrap().used_size -= id_size as i32;
            return 0;
        }

        item.as_mut().unwrap().count += 1;
        1
    }
}
pub fn binn_map_set(
    map: &mut binn,
    id: i32,
    type_: i32,
    pvalue: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
	println!("\n* binn_map_set");
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
    item: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    type_: i32,
    pvalue: Option<&[u8]>,
    size: i32,
) -> BOOL {
	println!("\n* binn_object_set_raw");
    // Check if item is None or has invalid type/writable flag
    if item.is_none() || item.as_ref().unwrap().type_ != 0xE2 || item.as_ref().unwrap().writable == 0 {
        return 0;
    }

    // Check if key is None
    if key.is_none() {
        return 0;
    }
    let key = key.unwrap();

    // Check key length
    let int32 = key.len() as i32;
    if int32 > 255 {
        return 0;
    }

    // Search for key
    let item_ref = item.as_ref().unwrap();
    let p = SearchForKey(
        item_ref.pbuf.as_ref().map(|b| b.as_ref() as *const _ as *const u8).map(|p| unsafe { std::slice::from_raw_parts(p, item_ref.used_size as usize) }),
        9,
        item_ref.used_size as usize,
        item_ref.count,
        Some(key),
    );
    if p.is_some() {
        return 0;
    }

    // Check allocation
    if CheckAllocation(item, 1 + int32) == 0 {
        return 0;
    }

    // Get mutable reference to item
    let item_mut = item.as_mut().unwrap();
    let p_idx = item_mut.used_size;
    let len = int32 as u8;

    // This part would require unsafe in Rust since we're dealing with raw pointers
    unsafe {
        let pbuf_ptr = item_mut.pbuf.as_mut().unwrap().as_mut() as *mut _ as *mut u8;
        ptr::write(pbuf_ptr.add(p_idx as usize), len);
        ptr::copy_nonoverlapping(key.as_ptr(), pbuf_ptr.add(p_idx as usize + 1), int32 as usize);
    }

    let int32 = int32 + 1;
    item_mut.used_size += int32;

    // Store the used_size adjustment value before calling AddValue
    let adjustment = int32;
    if AddValue(item, type_, pvalue, size) == 0 {
        item.as_mut().unwrap().used_size -= adjustment;
        return 0;
    }

    item.as_mut().unwrap().count += 1;
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

    let pvalue_bytes = if converted_type == 0xC0 {
        match converted_pvalue {
            Some(ref mut value) if value.is_some() => {
                let any_obj = value.as_ref().unwrap().as_ref();
                if let Some(bytes) = any_obj.downcast_ref::<Vec<u8>>() {
                    Some(bytes.as_slice())
                } else if let Some(bytes) = any_obj.downcast_ref::<Box<[u8]>>() {
                    Some(bytes.as_ref())
                } else {
                    None
                }
            },
            _ => None,
        }
    } else {
        None
    };

    binn_object_set_raw(obj, key, converted_type, pvalue_bytes, converted_size)
}
pub fn binn_create(item: &mut Option<Box<BinnStruct>>, type_: i32, size: i32, pointer: Option<&mut [u8]>) -> BOOL {
	println!("\n* binn_create");
    let mut retval: BOOL = 0;
    
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
    let mut actual_size = size;
    if size < 3 {
        if pointer.is_some() {
            return retval;
        } else {
            actual_size = 0;
        }
    }

    // Initialize the struct (equivalent to memset)
    *item = Box::new(BinnStruct {
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
    });

    if let Some(_ptr) = pointer {
        item.pre_allocated = 1;
        item.pbuf = Some(Box::new(())); // Simplified representation of pointer assignment
        item.alloc_size = actual_size;
    } else {
        item.pre_allocated = 0;
        let alloc_size = if actual_size == 0 { 256 } else { actual_size };
        let allocated_ptr = binn_malloc(alloc_size);
        if allocated_ptr.is_none() {
            return 0;
        }
        item.pbuf = Some(Box::new(())); // Simplified representation of pointer assignment
        item.alloc_size = alloc_size;
    }

    item.header = 0x1F22B11F;
    item.writable = 1;
    item.used_size = 9;
    item.type_ = type_;
    item.dirty = 1;
    
    1
}
pub fn binn_new(type_: i32, size: i32, pointer: Option<&mut [u8]>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_new");
    let item = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            match alloc.downcast::<BinnStruct>() {
                Ok(boxed) => Some(boxed),
                Err(e) => {
                    if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
                        (free_fn.0)(None);
                    }
                    return None;
                }
            }
        }
        None => return None,
    };

    let mut item = item;
    if binn_create(&mut item, type_, size, pointer) == 0 {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            let to_free = item.map(|b| b as Box<dyn std::any::Any + Send>);
            (free_fn.0)(to_free);
        }
        return None;
    }

    if let Some(item) = &mut item {
        item.allocated = 1;
    }
    item
}

trait IntoSend {
    fn into_send(self) -> Box<dyn std::any::Any + Send>;
}

impl IntoSend for Box<BinnStruct> {
    fn into_send(self) -> Box<dyn std::any::Any + Send> {
	println!("\n* into_send");
        Box::new(self) as Box<dyn std::any::Any + Send>
    }
}
pub fn binn_list() -> Option<Box<BinnStruct>> {
	println!("\n* binn_list");
    binn_new(0xE0, 0, None)
}
pub fn binn_map() -> Option<Box<BinnStruct>> {
	println!("\n* binn_map");
    binn_new(0xE1, 0, None)
}
pub fn binn_object() -> Option<Box<BinnStruct>> {
	println!("\n* binn_object");
    binn_new(0xE2, 0, None)
}
pub fn binn_create_list(list: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_create_list");
    binn_create(list, 0xE0, 0, None)
}
pub fn binn_create_map(map: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_create_map");
    binn_create(map, 0xE1, 0, None)
}
pub fn binn_create_object(object: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_create_object");
    binn_create(object, 0xE2, 0, None)
}
pub fn binn_free(item: &mut Option<Box<BinnStruct>>) {
	println!("\n* binn_free");
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
	println!("\n* binn_load");
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
	println!("\n* binn_list_int64");
    let mut value: int64 = 0;
    binn_list_get(list, pos, 0x81, Some(&mut value), None);
    value
}
pub fn binn_list_bool(list: Option<&[u8]>, pos: i32) -> BOOL {
	println!("\n* binn_list_bool");
    let mut value: BOOL = 0;
    binn_list_get(list, pos, 0x80061, Some(&mut value), None);
    value
}

pub fn binn_map_int64(map: Option<&[u8]>, id: i32) -> int64 {
	println!("\n* binn_map_int64");
    let mut value: int64 = 0;
    binn_map_get(map, id, 0x81, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn binn_map_bool(map: Option<&[u8]>, id: i32) -> BOOL {
	println!("\n* binn_map_bool");
    let mut value: BOOL = 0;
    binn_map_get(map, id, 0x80061, Some(&mut value), None);
    value
}
pub fn binn_object_int64(obj: Option<&[u8]>, key: Option<&str>) -> int64 {
	println!("\n* binn_object_int64");
    let mut value: int64 = 0;
    binn_object_get(obj, key, 0x81, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn binn_object_bool(obj: Option<&[u8]>, key: Option<&str>) -> BOOL {
	println!("\n* binn_object_bool");
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
	println!("\n* binn_read_pair");
    let ptr = match ptr {
        Some(p) => p,
        None => return 0,
    };

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

    if type_ != expected_type || count == 0 || pos < 1 || pos > count {
        return 0;
    }

    let p = ptr;
    let base = p;
    let plimit = &p[(size as usize) - 1..];
    let mut p_idx = header_size as usize;

    let mut id = 0;
    let mut counter = 0;
    let mut key: Option<&[u8]> = None;
    let mut len = 0;

    for _ in 0..count {
        match type_ {
            0xE1 => {
                let mut current_p = &p[p_idx..];
                let int32 = match read_map_id(&mut current_p, plimit) {
                    Some(v) => v,
                    None => return 0,
                };
                p_idx = p.len() - current_p.len();
                if p_idx > plimit.len() {
                    return 0;
                }
                id = int32;
            }
            0xE2 => {
                len = p[p_idx];
                p_idx += 1;
                if p_idx > plimit.len() {
                    return 0;
                }
                let end = p_idx + len as usize;
                key = Some(&p[p_idx..end]);
                p_idx += len as usize;
                if p_idx > plimit.len() {
                    return 0;
                }
            }
            _ => (),
        }

        counter += 1;
        if counter == pos {
            break;
        }

        let remaining = &p[p_idx..];
        let new_pos = match AdvanceDataPos(remaining, plimit.len()) {
            Some(p) => p,
            None => return 0,
        };
        p_idx = p.len() - new_pos.len();
        if p_idx == 0 || p_idx < base.len() {
            return 0;
        }
    }

    if counter != pos {
        return 0;
    }

    match type_ {
        0xE1 => {
            if let Some(pid) = pid {
                *pid = id;
            }
        }
        0xE2 => {
            if let (Some(pkey), Some(key), Some(len)) = (pkey, key, Some(len)) {
                if pkey.len() >= len as usize + 1 {
                    pkey[..len as usize].copy_from_slice(&key[..len as usize]);
                    pkey[len as usize] = 0;
                }
            }
        }
        _ => (),
    }

    GetValue(Some(&p[p_idx..]), value)
}
pub fn binn_map_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pid: Option<&mut i32>,
    value: Option<&mut binn>,
) -> BOOL {
	println!("\n* binn_map_get_pair");
    binn_read_pair(0xE1, ptr, pos, pid, None, value)
}
pub fn binn_object_get_pair(
    ptr: Option<&[u8]>,
    pos: i32,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
	println!("\n* binn_object_get_pair");
    binn_read_pair(0xE2, ptr, pos, None, pkey, value)
}
pub fn binn_size(ptr: Option<*mut u8>) -> i32 {
	println!("\n* binn_size");
    let item_idx: u32;
    match binn_get_ptr_type(ptr) {
        1 => {
            let item = unsafe { Box::from_raw(ptr.unwrap() as *mut BinnStruct) };
            let mut item = Some(Box::new(*item));
            
            let needs_save = {
                let item_ref = item.as_ref().unwrap();
                item_ref.writable != 0 && item_ref.dirty != 0
            };
            
            if needs_save {
                binn_save_header(&mut item);
            }
            
            let size = item.as_ref().unwrap().size;
            Box::into_raw(item.unwrap()); // Prevent double-free
            size
        },
        2 => binn_buf_size(None), // Assuming ptr can be converted to Option<&[u8]>
        _ => 0,
    }
}

pub fn binn_set_alloc_functions(
    new_malloc: Option<fn(usize) -> Option<Box<dyn std::any::Any>>>,
    new_realloc: Option<Box<dyn FnMut(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>> + Send>>,
    new_free: Option<Box<dyn FnMut(Option<Box<dyn std::any::Any + Send>>)>>,
) {
	println!("\n* binn_set_alloc_functions");
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
pub fn binn_release(item: binn) -> Option<Box<()>> {
	println!("\n* binn_release");
    if item.is_none() {
        return None;
    }

    let mut item = item.unwrap();
    let item_ptr = Box::into_raw(item);
    let data_idx = binn_ptr(Some(item_ptr as *mut u8));
    let mut item = unsafe { Box::from_raw(item_ptr) }; // Reconstruct the Box after getting the pointer

    if let Some(data_idx) = data_idx {
        if let Some(pbuf) = item.pbuf.take() { // Use take() to move out of the option
            let pbuf_ptr = Box::into_raw(pbuf) as *mut u8;
            if data_idx > pbuf_ptr {
                unsafe {
                    ptr::copy(
                        data_idx,
                        pbuf_ptr,
                        item.size as usize
                    );
                    item.pbuf = Some(Box::from_raw(pbuf_ptr as *mut ()));
                }
            } else {
                // Put back if we didn't use it
                item.pbuf = Some(unsafe { Box::from_raw(pbuf_ptr as *mut ()) });
            }
        }
    }

    if item.allocated != 0 {
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn.0(Some(Box::new(item)));
        }
    } else {
        unsafe {
            ptr::write_bytes(&mut *item, 0, 1);
        }
        item.header = 0x1F22B11F;
    }

    None
}
pub fn binn_type(ptr: Option<*mut u8>) -> i32 {
	println!("\n* binn_type");
    let item: Option<Box<BinnStruct>>;
    let mut item_idx: u32 = 0;
    
    match binn_get_ptr_type(ptr) {
        1 => {
            item = unsafe { ptr.map(|p| Box::from_raw(p as *mut BinnStruct)) };
            item.as_ref().map(|i| i.type_).unwrap_or(-1)
        }
        2 => binn_buf_type(None), // Assuming ptr can be converted to Option<&[u8]> if needed
        _ => -1,
    }
}
pub fn binn_count(ptr: Option<*mut u8>) -> i32 {
	println!("\n* binn_count");
    let item_idx: u32;
    match binn_get_ptr_type(ptr) {
        1 => {
            let item = unsafe { Box::from_raw(ptr.unwrap() as *mut BinnStruct) };
            let count = item.count;
            Box::into_raw(item); // Prevent the Box from being dropped
            count
        },
        2 => binn_buf_count(None), // Assuming ptr can be converted to Option<&[u8]>
        _ => -1,
    }
}
pub fn binn_list_uint64(list: Option<&[u8]>, pos: i32) -> uint64 {
	println!("\n* binn_list_uint64");
    let mut value: uint64 = 0;
    let pvalue: Option<&mut dyn std::any::Any> = Some(&mut value);
    binn_list_get(list, pos, 0x80, pvalue, None);
    value
}
pub fn binn_map_uint64(map: Option<&[u8]>, id: i32) -> uint64 {
	println!("\n* binn_map_uint64");
    let mut value: uint64 = 0;
    let _ = binn_map_get(map, id, 0x80, Some(&mut value as &mut dyn std::any::Any), None);
    value
}
pub fn binn_object_uint64(obj: Option<&[u8]>, key: Option<&str>) -> uint64 {
	println!("\n* binn_object_uint64");
    let mut value: uint64 = 0;
    binn_object_get(obj, key, 0x80, Some(&mut value as &mut dyn Any), None);
    value
}
pub fn store_value(value: Option<Box<BinnStruct>>) -> Option<Box<()>> {
	println!("\n* store_value");
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
	println!("\n* binn_list_read");
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
	println!("\n* binn_map_read");
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
	println!("\n* binn_object_read");
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
	println!("\n* binn_map_read_pair");
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
	println!("\n* binn_object_read_pair");
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
	println!("\n* binn_read_next_pair");
    // Check for invalid iterator conditions (equivalent to line 10-13)
    let iter = match iter {
        Some(iter) => iter,
        None => return 0,
    };

    if iter.pnext.is_none()
        || iter.pnext.as_ref().unwrap().as_ptr() > iter.plimit.as_ref().unwrap().as_ptr()
        || iter.current > iter.count
        || iter.type_ != expected_type
    {
        return 0;
    }

    iter.current += 1;
    if iter.current > iter.count {
        return 0;
    }

    // Create a temporary copy of pnext to avoid borrowing issues
    let p = iter.pnext.clone().unwrap();
    let mut p_idx = 0;

    match expected_type {
        0xE1 => {
            let mut p_slice = &p[p_idx..];
            let plimit_slice = iter.plimit.as_ref().unwrap();
            let int32 = match read_map_id(&mut p_slice, plimit_slice) {
                Some(id) => id,
                None => return 0,
            };

            p_idx = p.len() - p_slice.len();
            if &p[p_idx..] > plimit_slice {
                return 0;
            }

            if let Some(pid) = pid {
                *pid = int32;
            }
        }
        0xE2 => {
            let len = p[p_idx] as usize;
            p_idx += 1;
            let key = &p[p_idx..p_idx + len];
            p_idx += len;

            if &p[p_idx..] > iter.plimit.as_ref().unwrap() {
                return 0;
            }

            if let Some(pkey) = pkey {
                if pkey.len() >= len {
                    pkey[..len].copy_from_slice(key);
                    if pkey.len() > len {
                        pkey[len] = 0;
                    }
                }
            }
        }
        _ => (),
    }

    let new_pnext = AdvanceDataPos(&p[p_idx..], iter.plimit.as_ref().unwrap().len());
    iter.pnext = new_pnext.map(|slice| slice.to_vec());

    if let Some(pnext) = &iter.pnext {
        if pnext.as_ptr() < p[p_idx..].as_ptr() {
            return 0;
        }
    }

    GetValue(iter.pnext.as_ref().map(|v| v.as_slice()), value)
}
pub fn binn_map_next(iter: Option<&mut BinnIter>, pid: Option<&mut i32>, value: Option<&mut binn>) -> BOOL {
	println!("\n* binn_map_next");
    binn_read_next_pair(0xE1, iter, pid, None, value)
}
pub fn binn_object_next(
    iter: Option<&mut BinnIter>,
    pkey: Option<&mut [u8]>,
    value: Option<&mut binn>,
) -> BOOL {
	println!("\n* binn_object_next");
    binn_read_next_pair(0xE2, iter, None, pkey, value)
}
pub fn binn_copy(mut old: Option<&mut [u8]>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_copy");
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;
    
    let old_ptr = binn_ptr(old.as_mut().map(|x| x.as_mut_ptr()));
    let old_len = old.as_ref().map(|x| x.len()).unwrap_or(0);
    let old_slice = unsafe { slice::from_raw_parts(old_ptr?, old_len) };

    if !IsValidBinnHeader(
        Some(old_slice),
        Some(&mut type_),
        Some(&mut count),
        Some(&mut size),
        Some(&mut header_size),
    ) {
        return Option::None;
    }

    let mut item = binn_new(type_, (size - header_size) + 9, None)?;

    {
        let dest_slice = unsafe {
            slice::from_raw_parts_mut(
                ((item.pbuf.as_mut()? as *mut _ as *mut u8).add(9)) as *mut u8,
                (size - header_size) as usize,
            )
        };
        let src_slice = &old_slice[header_size as usize..(header_size + size) as usize];
        dest_slice.copy_from_slice(src_slice);
    }

    item.used_size = (9 + size) - header_size;
    item.count = count;

    Some(item)
}

pub fn binn_list_add_new(list: &mut Option<Box<BinnStruct>>, value: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_list_add_new");
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
	println!("\n* binn_map_set_new");
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
	println!("\n* binn_object_set_new");
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
	println!("\n* binn_open");
    // Allocate memory for the binn struct
    let mut item = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            // Try to downcast the allocation to our specific type
            match alloc.downcast::<BinnStruct>() {
                Ok(boxed) => Some(boxed),
                Err(_) => None,
            }
        }
        None => return None,
    };

    // Load the data into the binn struct
    if let Some(mut item_ref) = item.as_deref_mut() {
        if !binn_load(data, Some(&mut item_ref)) {
            // If loading fails, free the allocated memory
            if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
                free_fn.0(item.map(|b| b as Box<dyn std::any::Any + Send>));
            }
            return None;
        }
    }

    // Set the allocated flag and return the item
    if let Some(item) = item.as_deref_mut() {
        item.allocated = 1;  // Changed from true to 1 to match BOOL type
    }
    item
}
pub fn binn_list_value(ptr: Option<&[u8]>, pos: i32) -> Option<Box<BinnStruct>> {
	println!("\n* binn_list_value");
    let value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(allocated) => {
            let mut value = Box::new(BinnStruct {
                header: 0,
                allocated: 1,  // TRUE
                writable: 0,   // FALSE
                dirty: 0,     // FALSE
                pbuf: None,
                pre_allocated: 0,  // FALSE
                alloc_size: 0,
                used_size: 0,
                type_: 0,
                ptr: None,
                size: 0,
                count: 0,
                freefn: BinnMemFree::default(),
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
                    vbool: 0,  // FALSE
                },
                disable_int_compression: 0,  // FALSE
            });
            
            let mut boxed_value = Some(value);
            if binn_list_get_value(ptr, pos, Some(&mut boxed_value)) == 0 {  // FALSE
                if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
                    (free_fn.0)(Some(Box::new(boxed_value.unwrap()) as Box<dyn std::any::Any + Send>));
                }
                return None;
            }
            let mut value = boxed_value.unwrap();
            value.allocated = 1;  // TRUE
            Some(value)
        }
        None => None,
    };
    value
}
pub fn binn_map_value(ptr: Option<&[u8]>, id: i32) -> Option<Box<BinnStruct>> {
	println!("\n* binn_map_value");
    // Allocate memory for a new BinnStruct
    let mut value: Option<Box<BinnStruct>> = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            // SAFETY: We know binn_malloc returns a Box<BinnStruct> when successful
            unsafe { alloc.downcast::<BinnStruct>().ok() }
        }
        None => return None,
    };

    // Call binn_map_get_value with the mutable reference to the Option
    if binn_map_get_value(ptr, id, Some(&mut value)) == 0 {
        // If the call fails, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            free_fn.0(value.map(|v| Box::new(v) as Box<dyn std::any::Any + Send>));
        }
        return None;
    }

    // Set the allocated flag and return the value
    if let Some(value) = &mut value {
        value.allocated = 1;
    }
    value
}
pub fn binn_object_value(ptr: Option<&[u8]>, key: Option<&str>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_object_value");
    // Allocate memory for the binn struct
    let mut value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            // SAFETY: We know this was allocated as a BinnStruct
            unsafe { Box::from_raw(Box::into_raw(alloc) as *mut BinnStruct) }
        }
        None => return None,
    };

    // Initialize the struct
    value.allocated = 1; // BOOL true

    // Create an Option<Box<BinnStruct>> to pass to the function
    let mut value_option = Some(value);

    // Try to get the value from the object
    if binn_object_get_value(ptr, key, Some(&mut value_option)) == 0 {
        // Free the allocated memory if getting the value failed
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            (free_fn.0)(Some(Box::new(value_option.unwrap()) as Box<dyn std::any::Any + Send>));
        }
        return None;
    }

    value_option
}
pub fn binn_map_pair(map: Option<&[u8]>, pos: i32, pid: Option<&mut i32>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_map_pair");
    // Allocate memory for the binn struct
    let mut value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            // Try to downcast the allocation to our BinnStruct type
            match alloc.downcast::<BinnStruct>() {
                Ok(boxed) => Some(boxed),
                Err(e) => {
                    // If downcast fails, free the allocation and return None
                    if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
                        let raw_ptr = Box::into_raw(e);
                        let send_ptr = unsafe { Box::from_raw(raw_ptr as *mut (dyn std::any::Any + Send)) };
                        (free_fn.0)(Some(send_ptr));
                    }
                    return Option::None;
                }
            }
        }
        None => return Option::None,
    };

    // Create a mutable reference to the value for binn_read_pair
    let mut boxed_value = value.as_mut().map(|v| v.as_mut());

    // Call binn_read_pair with the allocated value
    if binn_read_pair(0xE1, map, pos, pid, Option::None, Some(&mut value)) == 0 {
        // On failure, free the allocated value and return None
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            let raw_ptr = Box::into_raw(value.unwrap());
            let send_ptr = unsafe { Box::from_raw(raw_ptr as *mut (dyn std::any::Any + Send)) };
            (free_fn.0)(Some(send_ptr));
        }
        return Option::None;
    }

    // On success, mark as allocated and return the value
    if let Some(v) = value.as_mut() {
        v.allocated = 1;
    }
    value
}
pub fn binn_object_pair(obj: Option<&[u8]>, pos: i32, pkey: Option<&mut [u8]>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_object_pair");
    // Allocate memory for the binn struct
    let value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(ptr) => ptr,
        None => return None,
    };

    // Try to downcast the allocated memory to our binn type
    let mut value = match value.downcast::<BinnStruct>() {
        Ok(boxed) => *boxed,
        Err(e) => {
            // If downcast fails, free the memory and return None
            if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
                // Convert the error into a String which implements Send
                let error_str = format!("{:?}", e);
                free_fn.0(Some(Box::new(error_str) as Box<dyn std::any::Any + Send>));
            }
            return None;
        }
    };

    // Initialize the binn struct
    value.allocated = 1;
    
    // Prepare the value as Option<&mut binn> for binn_read_pair
    let mut boxed_value = Box::new(value);
    let mut binn_value: Option<Box<BinnStruct>> = Some(boxed_value);
    let value_ref: Option<&mut Option<Box<BinnStruct>>> = Some(&mut binn_value);
    
    // Call binn_read_pair
    if binn_read_pair(0xE2, obj, pos, None, pkey, value_ref) == 0 {
        // On failure, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            if let Some(val) = binn_value {
                free_fn.0(Some(Box::new(val) as Box<dyn std::any::Any + Send>));
            }
        }
        return None;
    }

    if let Some(mut val) = binn_value {
        val.allocated = 1;
        Some(val)
    } else {
        None
    }
}
pub fn binn_iter_init(
    iter: Option<&mut BinnIter>,
    ptr: Option<&[u8]>,
    expected_type: i32,
) -> bool {
	println!("\n* binn_iter_init");
    let ptr_idx = 0;
    let mut type_ = 0;
    let mut count = 0;
    let mut size = 0;
    let mut header_size = 0;

    // Check for null pointers (translated to Option checks in Rust)
    if ptr.is_none() || iter.is_none() {
        return false;
    }
    let ptr = ptr.unwrap();
    let iter = iter.unwrap();

    // Equivalent of memset - initialize all fields to zero/default
    *iter = BinnIter {
        pnext: None,
        plimit: None,
        type_: 0,
        count: 0,
        current: 0,
    };

    // Call IsValidBinnHeader with mutable references to get output parameters
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

    // Calculate pointer positions (safe Rust version)
    let plimit = ptr.as_ptr().wrapping_add(size as usize).wrapping_sub(1);
    let pnext = ptr.as_ptr().wrapping_add(header_size as usize);

    // Update the iterator fields
    iter.plimit = Some(unsafe { Vec::from_raw_parts(plimit as *mut u8, 1, 1) });
    iter.pnext = Some(unsafe { Vec::from_raw_parts(pnext as *mut u8, 1, 1) });
    iter.count = count;
    iter.current = 0;
    iter.type_ = type_;

    true
}
pub fn binn_list_next(iter: Option<&mut BinnIter>, value: Option<&mut binn>) -> BOOL {
	println!("\n* binn_list_next");
    // Early return if any of the conditions in the complex check fail
    if let Some(iter) = iter {
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

        let pnow = iter.pnext.take().unwrap(); // Take ownership to avoid borrow issues
        let pnow_ptr = pnow.as_ptr();
        let pnow_len = pnow.len();
        
        // Advance the position
        let new_next = AdvanceDataPos(&pnow, pnow_len);
        iter.pnext = new_next.map(|slice| slice.to_vec());

        if let Some(next) = &iter.pnext {
            unsafe {
                if next.as_ptr() < pnow_ptr.add(pnow_len) {
                    return 0;
                }
            }
        }

        GetValue(Some(&pnow), value)
    } else {
        0
    }
}
pub fn binn_list_read_next(
    iter: Option<&mut BinnIter>,
    ptype: Option<&mut i32>,
    psize: Option<&mut i32>,
) -> Option<Box<()>> {
	println!("\n* binn_list_read_next");
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
	println!("\n* binn_map_read_next");
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
	println!("\n* binn_object_read_next");
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
	println!("\n* binn_set_string");
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
	println!("\n* binn_set_blob");
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
	println!("\n* binn_get_str");
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
	println!("\n* goto_loc_convert_value");
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
	println!("\n* binn_list_next_value");
    // Allocate memory for a new BinnStruct
    let mut value: Option<Box<BinnStruct>> = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(alloc) => {
            // Convert to raw pointer first to avoid move issues
            let ptr = Box::into_raw(alloc);
            // Directly cast to BinnStruct since we know the type
            Some(unsafe { Box::from_raw(ptr as *mut BinnStruct) })
        }
        None => return None,
    };

    // Try to get the next value from the list
    if binn_list_next(iter, Some(&mut value)) == 0 {
        // If failed, free the allocated memory and return None
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            if let Some(v) = value {
                let ptr = Box::into_raw(v);
                let boxed = unsafe { Box::from_raw(ptr as *mut (dyn std::any::Any + Send)) };
                (free_fn.0)(Some(boxed));
            }
        }
        return None;
    }

    // Mark the value as allocated and return it
    if let Some(mut v) = value {
        v.allocated = 1;
        Some(v)
    } else {
        None
    }
}
pub fn binn_map_next_value(iter: Option<&mut BinnIter>, pid: Option<&mut i32>) -> Option<binn> {
	println!("\n* binn_map_next_value");
    // Allocate a new binn value
    let value = binn_malloc(std::mem::size_of::<BinnStruct>() as i32);
    let mut value = match value {
        Some(v) => v,
        None => return None,
    };

    // Downcast the Box<dyn Any> to Box<BinnStruct>
    let value = match value.downcast::<BinnStruct>() {
        Ok(v) => v,
        Err(_) => return None,
    };

    // Create a mutable reference to the binn value
    let mut binn_value = Some(Box::new(*value));

    // Call binn_map_next with the mutable references wrapped in Some
    if binn_map_next(iter, pid, Some(&mut binn_value)) == 0 {
        // If the operation failed, free the allocated memory
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            (free_fn.0)(Some(Box::new(binn_value)));
        }
        return None;
    }

    // Set the allocated flag and return the value
    if let Some(b) = &mut binn_value {
        b.allocated = 1;
    }
    Some(binn_value)
}
pub fn binn_object_next_value(
    iter: Option<&mut BinnIter>,
    pkey: Option<&mut [u8]>,
) -> Option<Box<BinnStruct>> {
	println!("\n* binn_object_next_value");
    // Allocate memory for the binn value
    let value = match binn_malloc(std::mem::size_of::<BinnStruct>() as i32) {
        Some(v) => v,
        None => return None,
    };

    // Downcast the Box<dyn Any> to Box<BinnStruct>
    let value = match value.downcast::<BinnStruct>() {
        Ok(v) => v,
        Err(_) => return None,
    };

    // Create a mutable reference to the boxed value
    let mut boxed_value = Some(value);
    let success = binn_object_next(iter, pkey, Some(&mut boxed_value));

    if success == 0 {
        // Free the allocated memory if the operation failed
        if let Some(free_fn) = &mut *FREE_FN.lock().unwrap() {
            (free_fn.0)(Some(boxed_value.unwrap()));
        }
        return None;
    }

    // Take the value from the boxed_value if successful
    if let Some(mut value) = boxed_value {
        value.allocated = 1;
        Some(value)
    } else {
        None
    }
}
pub fn binn_get_int32(value: Option<&BinnStruct>, pint: Option<&mut i32>) -> BOOL {
	println!("\n* binn_get_int32");
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
	println!("\n* binn_add_value");
    match binn_type {
        0xE0 => binn_list_add(item, type_, pvalue, size),
        0xE1 => binn_map_set(item, id, type_, pvalue, size),
        0xE2 => binn_object_set(item, name, type_, pvalue, size),
        _ => 0,
    }
}

pub fn is_bool_str(str: Option<&str>, pbool: Option<&mut BOOL>) -> BOOL {
	println!("\n* is_bool_str");
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
	println!("\n* compare_ignore_case");
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
	println!("\n* binn_get_bool");
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
	println!("\n* binn_get_int64");
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
	println!("\n* binn_get_double");
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
