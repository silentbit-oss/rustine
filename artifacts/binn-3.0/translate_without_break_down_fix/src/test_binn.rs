use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::any::Any;
use std::assert;
use std::assert_eq;
use std::f64;
use std::ffi::CStr;
use std::ffi::CString;
use std::io::Write;
use std::io;
use std::os::raw::c_char;
use std::ptr;
use std::slice;
pub fn memdup(src: Option<&[u8]>, size: usize) -> Option<Box<[u8]>> {
	println!("\n* memdup");
    // Check for NULL pointer or invalid size (equivalent to C checks)
    if src.is_none() || size == 0 {
        return None;
    }

    let src = src.unwrap();
    
    // Allocate memory using Rust's allocator
    let layout = match Layout::array::<u8>(size) {
        Ok(layout) => layout,
        Err(_) => return None, // Allocation failed
    };

    // SAFETY: We've checked size > 0 and layout is valid
    let dest = unsafe { alloc(layout) };
    if dest.is_null() {
        return None;
    }

    // Copy the memory
    unsafe {
        ptr::copy_nonoverlapping(src.as_ptr(), dest, size);
    }

    // Convert the raw pointer into a Box<[u8]> for safe memory management
    Some(unsafe { Box::from_raw(ptr::slice_from_raw_parts_mut(dest, size)) })
}
pub fn return_int64() -> i64 {
	println!("\n* return_int64");
    9223372036854775807
}
pub fn AlmostEqualFloats(A: f32, B: f32, maxUlps: i32) -> bool {
	println!("\n* AlmostEqualFloats");
    // Check the assertion condition (maxUlps must be in valid range)
    assert!((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));

    // Convert floats to their bit representations as i32
    let aInt = A.to_bits() as i32;
    let bInt = B.to_bits() as i32;

    // Handle negative numbers by adjusting their representation
    let aInt = if aInt < 0 {
        (0x80000000u32 as i32).wrapping_sub(aInt)
    } else {
        aInt
    };

    let bInt = if bInt < 0 {
        (0x80000000u32 as i32).wrapping_sub(bInt)
    } else {
        bInt
    };

    // Calculate absolute difference between the integer representations
    let intDiff = (aInt - bInt).abs();

    // Compare against the maximum allowed difference
    intDiff <= maxUlps
}

pub fn AlmostEqualDoubles(a: f64, b: f64) -> bool {
	println!("\n* AlmostEqualDoubles");
    let absDiff = f64::abs(a - b);
    if absDiff < 1.0E-150 {
        return true;
    }

    let absA = f64::abs(a);
    let absB = f64::abs(b);
    let maxAbs = if absA > absB { absA } else { absB };

    if (absDiff / maxAbs) < 1.0E-8 {
        return true;
    }

    writeln!(io::stdout(), "a={} b={}", a, b).unwrap();
    false
}
pub fn binn_list_get_int8(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut i8>,
) -> BOOL {
	println!("\n* binn_list_get_int8");
    binn_list_get(list, pos, 0x21, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_int16(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut i16>,
) -> BOOL {
	println!("\n* binn_list_get_int16");
    binn_list_get(list, pos, 0x41, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_int32(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut i32>) -> BOOL {
	println!("\n* binn_list_get_int32");
    binn_list_get(list, pos, 0x61, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}

pub fn binn_list_get_uint8(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut u8>,
) -> BOOL {
	println!("\n* binn_list_get_uint8");
    binn_list_get(list, pos, 0x20, pvalue.map(|v| v as &mut dyn Any), None)
}
pub fn binn_list_get_uint16(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut u16>,
) -> BOOL {
	println!("\n* binn_list_get_uint16");
    binn_list_get(list, pos, 0x40, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_uint32(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut u32>) -> BOOL {
	println!("\n* binn_list_get_uint32");
    binn_list_get(list, pos, 0x60, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_float(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut f32>) -> BOOL {
	println!("\n* binn_list_get_float");
    binn_list_get(list, pos, 0x62, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_double(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut f64>) -> BOOL {
	println!("\n* binn_list_get_double");
    binn_list_get(list, pos, 0x82, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_str(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_list_get_str");
    binn_list_get(list, pos, 0xA0, pvalue, None)
}
pub fn binn_list_get_blob(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
	println!("\n* binn_list_get_blob");
    binn_list_get(list, pos, 0xC0, pvalue, psize)
}
pub fn binn_list_get_list(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_list_get_list");
    binn_list_get(list, pos, 0xE0, pvalue, None)
}
pub fn binn_list_get_map(
    list: Option<&[u8]>, 
    pos: i32, 
    pvalue: Option<&mut dyn std::any::Any>
) -> BOOL {
	println!("\n* binn_list_get_map");
    binn_list_get(list, pos, 0xE1, pvalue, None)
}
pub fn binn_list_get_object(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_list_get_object");
    binn_list_get(list, pos, 0xE2, pvalue, None)
}
pub fn binn_map_get_int8(
    map: Option<&[u8]>, 
    id: i32, 
    pvalue: Option<&mut i8>
) -> BOOL {
	println!("\n* binn_map_get_int8");
    binn_map_get(map, id, 0x21, pvalue.map(|v| v as &mut dyn std::any::Any), Option::None)
}
pub fn binn_map_get_int16(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut i16>,
) -> BOOL {
	println!("\n* binn_map_get_int16");
    binn_map_get(map, id, 0x41, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_int32(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut i32>,
) -> BOOL {
	println!("\n* binn_map_get_int32");
    binn_map_get(map, id, 0x61, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_uint8(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut u8>,
) -> BOOL {
	println!("\n* binn_map_get_uint8");
    binn_map_get(map, id, 0x20, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_uint16(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut u16>,
) -> BOOL {
	println!("\n* binn_map_get_uint16");
    binn_map_get(map, id, 0x40, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_uint32(map: Option<&[u8]>, id: i32, pvalue: Option<&mut u32>) -> BOOL {
	println!("\n* binn_map_get_uint32");
    binn_map_get(map, id, 0x60, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}

pub fn binn_map_get_float(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut f32>,
) -> BOOL {
	println!("\n* binn_map_get_float");
    binn_map_get(map, id, 0x62, pvalue.map(|v| v as &mut dyn Any), None)
}
pub fn binn_map_get_double(map: Option<&[u8]>, id: i32, pvalue: Option<&mut f64>) -> BOOL {
	println!("\n* binn_map_get_double");
    binn_map_get(map, id, 0x82, pvalue.map(|v| v as &mut dyn std::any::Any), Option::None)
}
pub fn binn_map_get_str(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut Option<String>>,
) -> BOOL {
	println!("\n* binn_map_get_str");
    binn_map_get(map, id, 0xA0, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_blob(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut dyn std::any::Any>,
    psize: Option<&mut i32>,
) -> BOOL {
	println!("\n* binn_map_get_blob");
    binn_map_get(map, id, 0xC0, pvalue, psize)
}
pub fn binn_map_get_list(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_map_get_list");
    binn_map_get(map, id, 0xE0, pvalue, None)
}
pub fn binn_map_get_map(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_map_get_map");
    binn_map_get(map, id, 0xE1, pvalue, None)
}
pub fn binn_map_get_object(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut dyn std::any::Any>,
) -> BOOL {
	println!("\n* binn_map_get_object");
    binn_map_get(map, id, 0xE2, pvalue, None)
}
pub fn binn_object_get_int8(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut i8>,
) -> bool {
	println!("\n* binn_object_get_int8");
    binn_object_get(obj, key, 0x21, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_int16(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut i16>,
) -> bool {
	println!("\n* binn_object_get_int16");
    // Convert pvalue to &mut dyn Any as required by binn_object_get
    let any_pvalue = pvalue.map(|v| v as &mut dyn Any);
    
    // Call binn_object_get with type 0x41 (INT16)
    binn_object_get(obj, key, 0x41, any_pvalue, None) != 0
}
pub fn binn_object_get_int32(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut i32>) -> bool {
	println!("\n* binn_object_get_int32");
    // Convert the bool return to i32 (0 for false, 1 for true) to match C's BOOL type
    binn_object_get(obj, key, 0x61, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_uint8(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut u8>,
) -> bool {
	println!("\n* binn_object_get_uint8");
    // Convert the bool return to i32 for compatibility with binn_object_get
    binn_object_get(obj, key, 0x20, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_uint16(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut u16>,
) -> bool {
	println!("\n* binn_object_get_uint16");
    // The 0x40 corresponds to BINN_UINT16 in the original C code
    binn_object_get(obj, key, 0x40, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_uint32(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut u32>) -> bool {
	println!("\n* binn_object_get_uint32");
    binn_object_get(obj, key, 0x60, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_float(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut f32>) -> bool {
	println!("\n* binn_object_get_float");
    // Convert the bool return to i32 for compatibility with binn_object_get
    let result = binn_object_get(obj, key, 0x62, pvalue.map(|v| v as &mut dyn Any), None);
    result != 0
}

pub fn binn_object_get_double(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut f64>,
) -> bool {
	println!("\n* binn_object_get_double");
    // Convert the bool return to i32 (0 for false, 1 for true)
    binn_object_get(obj, key, 0x82, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_str(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut dyn Any>,
) -> i32 {
	println!("\n* binn_object_get_str");
    binn_object_get(obj, key, 0xA0, pvalue, None)
}
pub fn binn_object_get_blob(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut dyn Any>,
    psize: Option<&mut i32>,
) -> bool {
	println!("\n* binn_object_get_blob");
    // Call binn_object_get with the blob type (0xC0) and convert the result to bool
    binn_object_get(obj, key, 0xC0, pvalue, psize) != 0
}
pub fn binn_object_get_list(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut dyn Any>,
) -> i32 {
	println!("\n* binn_object_get_list");
    binn_object_get(obj, key, 0xE0, pvalue, None)
}
pub fn binn_object_get_map(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut dyn Any>,
) -> i32 {
	println!("\n* binn_object_get_map");
    binn_object_get(obj, key, 0xE1, pvalue, None)
}
pub fn binn_object_get_object(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut dyn Any>) -> bool {
	println!("\n* binn_object_get_object");
    binn_object_get(obj, key, 0xE2, pvalue, None) != 0
}
pub fn test_binn_version() {
	println!("\n* test_binn_version");
    let version = binn_version();
    assert!(!version.is_empty());
    assert_eq!(version, "3.0.0");
}
pub fn i64toa(value: int64, buf: &mut [u8], radix: u32) -> Option<&mut [u8]> {
	println!("\n* i64toa");
    match radix {
        10 => {
            write!(std::io::Cursor::new(&mut *buf), "{}", value).ok()?;
        },
        16 => {
            write!(std::io::Cursor::new(&mut *buf), "{:x}", value).ok()?;
        },
        _ => {
            if !buf.is_empty() {
                buf[0] = 0;
            }
        }
    }
    Some(buf)
}
pub fn pass_int64(a: int64) {
	println!("\n* pass_int64");
    assert!(a == 9223372036854775807);
    assert!(a > 9223372036854775806);
}
pub fn return_passed_int64(a: int64) -> int64 {
	println!("\n* return_passed_int64");
    a
}
pub fn test_invalid_binn() {
	println!("\n* test_invalid_binn");
    let buffers: [[u8; 20]; 36] = [
        [0xE0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x7F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ];

    println!("testing invalid binn buffers...");
    let count = buffers.len();
    for i in 0..count {
        let ptr = buffers[i].as_ptr() as *mut u8;
        let c_str = unsafe { CStr::from_ptr(buffers[i].as_ptr() as *const c_char) };
        let size = c_str.to_bytes().len();
        println!("checking invalid binn #{}   size: {} bytes", i, size);
        
        let mut size_mut = size as i32;
        assert!(!binn_is_valid_ex(Some(ptr), None, None, Some(&mut size_mut)));
    }

    println!("OK");
}
pub fn binn_int8(value: i8) -> Option<Box<BinnStruct>> {
	println!("\n* binn_int8");
    binn_value(0x21, Some(&[value as u8]), 0, None)
}
pub fn binn_int16(value: i16) -> Option<Box<BinnStruct>> {
	println!("\n* binn_int16");
    binn_value(0x41, Some(&value.to_ne_bytes()), 0, None)
}
pub fn binn_int32(value: i32) -> Option<Box<BinnStruct>> {
	println!("\n* binn_int32");
    binn_value(0x61, Some(&value.to_ne_bytes()), 0, None)
}
pub fn binn_uint8(value: u8) -> Option<Box<BinnStruct>> {
	println!("\n* binn_uint8");
    binn_value(0x20, Some(&[value]), 0, None)
}
pub fn binn_uint16(value: u16) -> Option<Box<BinnStruct>> {
	println!("\n* binn_uint16");
    let value_bytes = value.to_le_bytes();
    binn_value(0x40, Some(&value_bytes), 0, None)
}
pub fn binn_uint32(value: u32) -> Option<Box<BinnStruct>> {
	println!("\n* binn_uint32");
    binn_value(0x60, Some(&value.to_ne_bytes()), 0, None)
}
pub fn binn_float(value: f32) -> Option<Box<BinnStruct>> {
	println!("\n* binn_float");
    // Convert the float to bytes for safe handling
    let bytes = value.to_ne_bytes();
    binn_value(0x62, Some(&bytes), 0, None)
}
pub fn binn_double(value: f64) -> Option<Box<BinnStruct>> {
	println!("\n* binn_double");
    // Convert the f64 to bytes to pass to binn_value
    let bytes = value.to_ne_bytes();
    binn_value(0x82, Some(&bytes), 0, None)
}
pub fn binn_null() -> Option<Box<BinnStruct>> {
	println!("\n* binn_null");
    binn_value(0x00, None, 0, None)
}
pub fn binn_list_add_int8(list: &mut Option<Box<BinnStruct>>, value: i8) -> BOOL {
	println!("\n* binn_list_add_int8");
    let mut boxed_value = Box::new(value) as Box<dyn std::any::Any>;
    let mut binding = Some(boxed_value);
    let pvalue = Some(&mut binding);
    binn_list_add(list, 0x21, pvalue, 0)
}
pub fn binn_list_add_int16(list: &mut Option<Box<BinnStruct>>, value: i16) -> BOOL {
	println!("\n* binn_list_add_int16");
    binn_list_add(list, 0x41, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_int32(list: &mut Option<Box<BinnStruct>>, value: i32) -> BOOL {
	println!("\n* binn_list_add_int32");
    binn_list_add(list, 0x61, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_uint8(list: &mut Option<Box<BinnStruct>>, value: u8) -> BOOL {
	println!("\n* binn_list_add_uint8");
    binn_list_add(list, 0x20, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_uint16(list: &mut Option<Box<BinnStruct>>, value: u16) -> BOOL {
	println!("\n* binn_list_add_uint16");
    let mut boxed_value = Box::new(value) as Box<dyn std::any::Any>;
    let mut binding = Some(boxed_value);
    let pvalue = Some(&mut binding);
    binn_list_add(list, 0x40, pvalue, 0)
}
pub fn binn_list_add_uint32(list: &mut Option<Box<BinnStruct>>, value: u32) -> BOOL {
	println!("\n* binn_list_add_uint32");
    binn_list_add(list, 0x60, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_float(list: &mut Option<Box<BinnStruct>>, value: f32) -> BOOL {
	println!("\n* binn_list_add_float");
    binn_list_add(list, 0x62, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_double(list: &mut Option<Box<BinnStruct>>, value: f64) -> BOOL {
	println!("\n* binn_list_add_double");
    binn_list_add(list, 0x82, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_null(list: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_list_add_null");
    binn_list_add(list, 0x00, None, 0)
}
pub fn binn_list_add_str(list: &mut Option<Box<BinnStruct>>, str: Option<&mut Option<Box<dyn std::any::Any>>>) -> BOOL {
	println!("\n* binn_list_add_str");
    binn_list_add(list, 0xA0, str, 0)
}
pub fn binn_list_add_blob(
    list: &mut crate::binn::binn,
    ptr: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
	println!("\n* binn_list_add_blob");
    binn_list_add(list, 0xC0, ptr, size)
}
pub fn binn_map_set_int8(map: &mut Option<Box<BinnStruct>>, id: i32, value: i8) -> BOOL {
	println!("\n* binn_map_set_int8");
    let mut boxed_value = Box::new(value);
    binn_map_set(map, id, 0x21, Some(&mut Some(boxed_value)), 0)
}
pub fn binn_map_set_int16(map: &mut Option<Box<BinnStruct>>, id: i32, value: i16) -> BOOL {
	println!("\n* binn_map_set_int16");
    binn_map_set(map, id, 0x41, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_int32(map: &mut crate::binn::binn, id: i32, value: i32) -> BOOL {
	println!("\n* binn_map_set_int32");
    binn_map_set(map, id, 0x61, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_uint8(map: &mut Option<Box<BinnStruct>>, id: i32, value: u8) -> BOOL {
	println!("\n* binn_map_set_uint8");
    let mut boxed_value = Box::new(value) as Box<dyn std::any::Any>;
    binn_map_set(map, id, 0x20, Some(&mut Some(boxed_value)), 0)
}
pub fn binn_map_set_uint16(map: &mut Option<Box<BinnStruct>>, id: i32, value: u16) -> BOOL {
	println!("\n* binn_map_set_uint16");
    let mut boxed_value = Box::new(value);
    let mut any_value: Option<Box<dyn std::any::Any>> = Some(boxed_value);
    binn_map_set(map, id, 0x40, Some(&mut any_value), 0)
}
pub fn binn_map_set_uint32(map: &mut crate::binn::binn, id: i32, value: u32) -> BOOL {
	println!("\n* binn_map_set_uint32");
    let mut boxed_value = Some(Box::new(value) as Box<dyn std::any::Any>);
    binn_map_set(map, id, 0x60, Some(&mut boxed_value), 0)
}
pub fn binn_map_set_float(map: &mut Option<Box<BinnStruct>>, id: i32, value: f32) -> BOOL {
	println!("\n* binn_map_set_float");
    binn_map_set(map, id, 0x62, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_double(map: &mut Option<Box<BinnStruct>>, id: i32, value: f64) -> BOOL {
	println!("\n* binn_map_set_double");
    binn_map_set(map, id, 0x82, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_null(map: &mut Option<Box<BinnStruct>>, id: i32) -> BOOL {
	println!("\n* binn_map_set_null");
    binn_map_set(map, id, 0x00, Option::None, 0)
}
pub fn binn_map_set_str(map: &mut Option<Box<BinnStruct>>, id: i32, str: Option<&mut Option<Box<dyn std::any::Any>>>) -> BOOL {
    if let Some(Some(str_box)) = str {
        if let Some(s) = str_box.downcast_ref::<String>() {
            if let Ok(c_string) = std::ffi::CString::new(s.as_str()) {
                let bytes = c_string.as_bytes_with_nul();
                return binn_map_set_raw(map, id, 0xA0, Some(bytes), 0);
            }
        }
    }
    0
}
pub fn binn_map_set_blob(
    map: &mut crate::binn::binn,
    id: i32,
    ptr: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
	println!("\n* binn_map_set_blob");
    binn_map_set(map, id, 0xC0, ptr, size)
}
pub fn binn_object_set_int8(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: i8,
) -> BOOL {
	println!("\n* binn_object_set_int8");
    binn_object_set(obj, key, 0x21, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_object_set_int16(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: i16,
) -> BOOL {
	println!("\n* binn_object_set_int16");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x41, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_int32(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: i32,
) -> BOOL {
	println!("\n* binn_object_set_int32");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x61, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_uint8(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: u8,
) -> BOOL {
	println!("\n* binn_object_set_uint8");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x20, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_uint16(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: u16,
) -> BOOL {
	println!("\n* binn_object_set_uint16");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x40, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_uint32(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: u32,
) -> BOOL {
	println!("\n* binn_object_set_uint32");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x60, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_float(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: f32,
) -> BOOL {
	println!("\n* binn_object_set_float");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x62, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_double(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: f64,
) -> BOOL {
	println!("\n* binn_object_set_double");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x82, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_null(obj: &mut Option<Box<BinnStruct>>, key: Option<&str>) -> BOOL {
	println!("\n* binn_object_set_null");
    binn_object_set(obj, key, 0x00, None, 0)
}
pub fn binn_object_set_str(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    str: Option<&str>,
) -> BOOL {
	println!("\n* binn_object_set_str");
    let mut boxed_str = str.map(|s| Box::new(s.to_string()) as Box<dyn std::any::Any>);
    let mut option_boxed_str = boxed_str.map(Some);
    binn_object_set(obj, key, 0xA0, option_boxed_str.as_mut().map(|b| b), 0)
}
pub fn binn_object_set_blob(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    ptr: Option<&mut Option<Box<dyn std::any::Any>>>,
    size: i32,
) -> BOOL {
	println!("\n* binn_object_set_blob");
    binn_object_set(obj, key, 0xC0, ptr, size)
}
pub fn binn_list_get_int64(
    list: Option<&[u8]>,
    pos: i32,
    pvalue: Option<&mut int64>,
) -> BOOL {
	println!("\n* binn_list_get_int64");
    binn_list_get(list, pos, 0x81, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_list_get_bool(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut BOOL>) -> BOOL {
	println!("\n* binn_list_get_bool");
    binn_list_get(list, pos, 0x80061, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_int64(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut int64>,
) -> BOOL {
	println!("\n* binn_map_get_int64");
    binn_map_get(map, id, 0x81, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_bool(map: Option<&[u8]>, id: i32, pvalue: Option<&mut BOOL>) -> BOOL {
	println!("\n* binn_map_get_bool");
    binn_map_get(map, id, 0x80061, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_object_get_int64(
    obj: Option<&[u8]>,
    key: Option<&str>,
    pvalue: Option<&mut int64>,
) -> bool {
	println!("\n* binn_object_get_int64");
    binn_object_get(obj, key, 0x81, pvalue.map(|v| v as &mut dyn Any), None) != 0
}
pub fn binn_object_get_bool(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut BOOL>) -> BOOL {
	println!("\n* binn_object_get_bool");
    binn_object_get(obj, key, 0x80061, pvalue.map(|v| v as &mut dyn Any), None)
}

pub fn test_floating_point_numbers() {
	println!("\n* test_floating_point_numbers");
    let mut buf = [0u8; 256];
    let mut f1: f32;
    let mut d1: f64;

    println!("testing floating point... ");
    f1 = 1.25;
    assert!(f1 == 1.25);
    d1 = 1.25;
    assert!(d1 == 1.25);
    d1 = 0.0;
    d1 = f1 as f64;
    assert!(d1 == 1.25);
    f1 = 0.0;
    f1 = d1 as f32;
    assert!(f1 == 1.25);
    d1 = 1.234;
    assert!(AlmostEqualDoubles(d1, 1.234));
    f1 = d1 as f32;
    assert!(AlmostEqualFloats(f1, 1.234, 2));
    d1 = 1.2345;
    assert!(AlmostEqualDoubles(d1, 1.2345));
    f1 = d1 as f32;
    assert!(AlmostEqualFloats(f1, 1.2345, 2));
    d1 = "1.234".parse::<f64>().unwrap();
    assert!(AlmostEqualDoubles(d1, 1.234));
    f1 = d1 as f32;
    assert!(AlmostEqualFloats(f1, 1.234, 2));
    let formatted = format!("{}", d1);
    unsafe {
        std::ptr::copy_nonoverlapping(formatted.as_ptr(), buf.as_mut_ptr() as *mut u8, formatted.len());
    }
    assert!(buf[0] != 0);
    assert!(formatted == "1.234");
    d1 = "12.34".parse::<f64>().unwrap();
    assert!(d1 == 12.34);
    f1 = d1 as f32;
    assert!(AlmostEqualFloats(f1, 12.34, 2));
    let formatted = format!("{}", d1);
    unsafe {
        std::ptr::copy_nonoverlapping(formatted.as_ptr(), buf.as_mut_ptr() as *mut u8, formatted.len());
    }
    assert!(buf[0] != 0);
    assert!(formatted == "12.34");
    d1 = "1.234e25".parse::<f64>().unwrap();
    assert!(AlmostEqualDoubles(d1, 1.234e25));
    f1 = d1 as f32;
    assert!(AlmostEqualFloats(f1, 1.234e25, 2));
    let formatted = format!("{}", d1);
    unsafe {
        std::ptr::copy_nonoverlapping(formatted.as_ptr(), buf.as_mut_ptr() as *mut u8, formatted.len());
    }
    assert!(buf[0] != 0);
    println!("OK");
}
pub fn binn_int64(value: int64) -> Option<Box<BinnStruct>> {
	println!("\n* binn_int64");
    binn_value(0x81, Some(&value.to_ne_bytes()), 0, None)
}
pub fn binn_bool(value: BOOL) -> Option<Box<BinnStruct>> {
	println!("\n* binn_bool");
    binn_value(0x80061, Some(&value.to_ne_bytes()), 0, None)
}
pub fn binn_string(str: Option<&str>, freefn: Option<Box<dyn FnMut(Option<Box<()>>)>>) -> Option<Box<BinnStruct>> {
	println!("\n* binn_string");
    // Convert the string to bytes if it exists, otherwise pass None
    let str_bytes = str.map(|s| s.as_bytes());
    binn_value(0xA0, str_bytes, 0, freefn)
}
pub fn binn_blob(
    ptr: Option<&[u8]>,
    size: i32,
    freefn: Option<Box<dyn FnMut(Option<Box<()>>)>>,
) -> Option<Box<BinnStruct>> {
	println!("\n* binn_blob");
    binn_value(0xC0, ptr, size, freefn)
}
pub fn binn_list_add_int64(list: &mut Option<Box<BinnStruct>>, value: int64) -> BOOL {
	println!("\n* binn_list_add_int64");
    binn_list_add(list, 0x81, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_list_add_bool(list: &mut Option<Box<BinnStruct>>, value: BOOL) -> BOOL {
    binn_list_add(list, 0x80061, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_int64(map: &mut Option<Box<BinnStruct>>, id: i32, value: i64) -> BOOL {
	println!("\n* binn_map_set_int64");
    binn_map_set(map, id, 0x81, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_bool(map: &mut Option<Box<BinnStruct>>, id: i32, value: BOOL) -> BOOL {
	println!("\n* binn_map_set_bool");
    let mut boxed_value = Some(Box::new(value) as Box<dyn std::any::Any>);
    binn_map_set(map, id, 0x80061, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_int64(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: int64,
) -> BOOL {
	println!("\n* binn_object_set_int64");
    let mut boxed_value = Some(Box::new(value) as Box<dyn std::any::Any>);
    binn_object_set(obj, key, 0x81, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_bool(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: BOOL,
) -> BOOL {
	println!("\n* binn_object_set_bool");
    let mut boxed_value: Option<Box<dyn std::any::Any>> = Some(Box::new(value));
    binn_object_set(obj, key, 0x80061, Some(&mut boxed_value), 0)
}
pub fn binn_list_get_uint64(list: Option<&[u8]>, pos: i32, pvalue: Option<&mut uint64>) -> BOOL {
	println!("\n* binn_list_get_uint64");
    binn_list_get(list, pos, 0x80, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_map_get_uint64(
    map: Option<&[u8]>,
    id: i32,
    pvalue: Option<&mut uint64>,
) -> BOOL {
	println!("\n* binn_map_get_uint64");
    binn_map_get(map, id, 0x80, pvalue.map(|v| v as &mut dyn std::any::Any), None)
}
pub fn binn_object_get_uint64(obj: Option<&[u8]>, key: Option<&str>, pvalue: Option<&mut uint64>) -> bool {
	println!("\n* binn_object_get_uint64");
    // Convert the uint64 reference to a mutable Any reference for compatibility with binn_object_get
    let pvalue_any = pvalue.map(|v| v as &mut dyn Any);
    
    // Call binn_object_get with the appropriate type code (0x80 for uint64)
    binn_object_get(obj, key, 0x80, pvalue_any, None) != 0
}


pub fn print_binn(map: Option<Box<BinnStruct>>) {
	println!("\n* print_binn");
    // Get the pointer and size from the binn struct
    let p_idx = binn_ptr(map.as_ref().map(|m| m.ptr.as_ref().map(|p| p.as_ref() as *const _ as *mut u8)).flatten());
    let size = binn_size(map.as_ref().map(|m| m.ptr.as_ref().map(|p| p.as_ref() as *const _ as *mut u8)).flatten());

    // If we have valid pointer and size, print the bytes
    if let (Some(p_idx), Some(size)) = (p_idx, Some(size)) {
        // Convert raw pointer to slice (unsafe required here)
        unsafe {
            let slice = std::slice::from_raw_parts(p_idx as *const u8, size as usize);
            for byte in slice {
                print!("{:02x} ", byte);
            }
        }
    }

    println!(); // Equivalent to puts("") in C
}
pub fn binn_uint64(value: uint64) -> Option<Box<BinnStruct>> {
	println!("\n* binn_uint64");
    // Convert the uint64 value to bytes for safe passing to binn_value
    let value_bytes = value.to_le_bytes();
    binn_value(0x80, Some(&value_bytes), 0, None)
}
pub fn binn_list_add_uint64(list: &mut Option<Box<BinnStruct>>, value: u64) -> BOOL {
	println!("\n* binn_list_add_uint64");
    let mut boxed_value = Some(Box::new(value) as Box<dyn std::any::Any>);
    binn_list_add(list, 0x80, Some(&mut boxed_value), 0)
}
pub fn binn_list_add_list(list: &mut Option<Box<BinnStruct>>, list2: Option<&mut Option<Box<BinnStruct>>>) -> BOOL {
	println!("\n* binn_list_add_list");
    let pvalue = list2.as_ref().and_then(|l| l.as_ref().map(|b| Box::as_ref(b) as *const _ as *mut u8));
    let size = list2.as_ref().map_or(0, |l| {
        let ptr = l.as_ref().map(|b| Box::as_ref(b) as *const _ as *mut u8);
        binn_size(ptr)
    });
    binn_list_add(
        list,
        0xE0,
        pvalue.map(|v| unsafe { &mut *(v as *mut Option<Box<dyn std::any::Any>>) }),
        size,
    )
}
pub fn binn_list_add_map(list: &mut Option<Box<BinnStruct>>, map: Option<*mut u8>) -> BOOL {
	println!("\n* binn_list_add_map");
    let any_ptr = map.map(|p| unsafe {
        std::mem::transmute::<*mut u8, *mut Option<Box<dyn std::any::Any>>>(p)
    });
    let any_ref = any_ptr.map(|p| unsafe { &mut *p });
    binn_list_add(
        list,
        0xE1,
        any_ref,
        binn_size(map)
    )
}
pub fn binn_list_add_object(list: &mut Option<Box<BinnStruct>>, obj: Option<*mut u8>) -> BOOL {
	println!("\n* binn_list_add_object");
    binn_list_add(
        list,
        0xE2,
        Some(&mut Some(Box::new(obj) as Box<dyn std::any::Any>)),
        binn_size(obj)
    )
}
pub fn binn_list_add_value(list: &mut Option<Box<BinnStruct>>, value: &mut Option<Box<BinnStruct>>) -> BOOL {
	println!("\n* binn_list_add_value");
    // First, get the type_ and size from the value.
    let type_ = value.as_ref().unwrap().type_;
    let size = value.as_ref().unwrap().size;

    // Move the value out into a temporary, leaving None in `value`.
    let mut temp = value.take();
    // Convert the temporary to an Option<Box<dyn Any>>
    let mut temp_any: Option<Box<dyn std::any::Any>> = temp.map(|bx| bx as Box<dyn std::any::Any>);

    // Call binn_list_add with a mutable reference to temp_any.
    let result = binn_list_add(
        list,
        type_,
        Some(&mut temp_any),
        size,
    );

    // Convert temp_any back to Option<Box<BinnStruct>>
    temp = if let Some(bx) = temp_any {
        match bx.downcast::<BinnStruct>() {
            Ok(bx) => Some(bx),
            Err(_) => panic!("downcast failed"),
        }
    } else {
        None
    };

    // Put the value back into `value`
    *value = temp;

    result
}
pub fn binn_map_set_uint64(map: &mut Option<Box<BinnStruct>>, id: i32, value: u64) -> BOOL {
	println!("\n* binn_map_set_uint64");
    binn_map_set(map, id, 0x80, Some(&mut Some(Box::new(value))), 0)
}
pub fn binn_map_set_list(
    map: &mut Option<Box<BinnStruct>>,
    id: i32,
    list: Option<*mut u8>,
) -> BOOL {
	println!("\n* binn_map_set_list");
    let ptr = binn_ptr(list);
    binn_map_set(
        map,
        id,
        0xE0,
        ptr.map(|p| unsafe { &mut *(p as *mut Option<Box<dyn std::any::Any>>) }),
        binn_size(list),
    )
}
pub fn binn_map_set_map(
    map: &mut crate::binn::binn,
    id: i32,
    map2: Option<&mut crate::binn::binn>,
) -> BOOL {
	println!("\n* binn_map_set_map");
    // Convert map2 to raw pointer for binn_ptr
    let map2_ptr = match map2 {
        Some(m) => Some(Box::into_raw(Box::new(m)) as *mut u8),
        None => None,
    };

    // Get size of map2
    let size = binn_size(map2_ptr);

    // Call binn_map_set with appropriate parameters
    binn_map_set(
        map,
        id,
        0xE1,
        map2_ptr.map(|p| unsafe { &mut *(p as *mut Option<Box<dyn std::any::Any>>) }),
        size,
    )
}
pub fn binn_map_set_object(
    map: &mut Option<Box<BinnStruct>>,
    id: i32,
    obj: Option<*mut u8>,
) -> BOOL {
	println!("\n* binn_map_set_object");
    binn_map_set(
        map,
        id,
        0xE2,
        obj.map(|ptr| Some(Box::new(ptr) as Box<dyn std::any::Any>)).as_mut(),
        binn_size(obj),
    )
}
pub fn binn_map_set_value(map: &mut crate::binn::binn, id: i32, value: &mut crate::binn::binn) -> BOOL {
	println!("\n* binn_map_set_value");
    let type_ = value.as_ref().map(|v| v.type_).unwrap_or(0);
    let ptr = binn_ptr(value.as_mut().and_then(|v| v.ptr.as_mut().map(|p| p as *mut _ as *mut u8)));
    let size = binn_size(ptr);
    binn_map_set(
        map,
        id,
        type_,
        value.as_mut().and_then(|v| {
            v.ptr.as_mut().map(|p| {
                let any_ptr = p as *mut _ as *mut dyn std::any::Any;
                unsafe { &mut *(any_ptr as *mut Option<Box<dyn std::any::Any>>) }
            })
        }),
        size,
    )
}
pub fn binn_object_set_uint64(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: uint64,
) -> BOOL {
	println!("\n* binn_object_set_uint64");
    let mut boxed_value = Some(Box::new(value) as Box<dyn std::any::Any>);
    binn_object_set(obj, key, 0x80, Some(&mut boxed_value), 0)
}
pub fn binn_object_set_list(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    list: Option<*mut u8>,
) -> BOOL {
	println!("\n* binn_object_set_list");
    let mut value: Option<Box<dyn std::any::Any>> = if let Some(ptr) = list {
        Some(Box::new(ptr) as Box<dyn std::any::Any>)
    } else {
        None
    };
    
    binn_object_set(
        obj,
        key,
        0xE0,
        Some(&mut value),
        binn_size(list),
    )
}
pub fn binn_object_set_map(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    map: Option<*mut u8>,
) -> BOOL {
	println!("\n* binn_object_set_map");
    let mut ptr = binn_ptr(map);
    let mut boxed_ptr: Option<Box<dyn std::any::Any>> = ptr.map(|p| Box::new(p) as Box<dyn std::any::Any>);
    binn_object_set(
        obj,
        key,
        0xE1,
        Some(&mut boxed_ptr),
        binn_size(map),
    )
}
pub fn binn_object_set_object(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    obj2: Option<*mut u8>,
) -> BOOL {
	println!("\n* binn_object_set_object");
    let mut boxed: Option<Box<dyn std::any::Any>> = obj2.map(|p| unsafe { Box::from_raw(p) as Box<dyn std::any::Any> });
    binn_object_set(
        obj,
        key,
        0xE2,
        Some(&mut boxed),
        binn_size(obj2),
    )
}
pub fn binn_object_set_value(
    obj: &mut Option<Box<BinnStruct>>,
    key: Option<&str>,
    value: &mut Option<Box<BinnStruct>>,
) -> BOOL {
	println!("\n* binn_object_set_value");
    let type_ = value.as_ref().map_or(0, |v| v.type_);
    let size = value.as_ref().map_or(0, |v| v.size);
    
    // Move the value into a temporary Option<Box<dyn Any>>
    let mut temp_any: Option<Box<dyn std::any::Any>> = value.take().map(|b| b as Box<dyn std::any::Any>);
    
    // Prepare pvalue argument as Option<&mut Option<Box<dyn Any>>>
    let pvalue_arg = if temp_any.is_some() {
        Some(&mut temp_any)
    } else {
        None
    };
    
    let result = binn_object_set(
        obj,
        key,
        type_,
        pvalue_arg,
        size
    );
    
    // Restore the original value by downcasting
    *value = if let Some(any) = temp_any {
        if let Ok(b) = any.downcast::<BinnStruct>() {
            Some(b)
        } else {
            // Should not happen since we only put BinnStruct in
            None
        }
    } else {
        None
    };
    
    result
}

pub fn test_int64() {
	println!("\n* test_int64");
    let mut i64: int64;
    let mut buf = [0u8; 64];
    
    println!("testing int64... ");
    
    pass_int64(9223372036854775807);
    
    i64 = return_int64();
    assert_eq!(i64, 9223372036854775807);
    
    i64toa(i64, &mut buf, 10).expect("i64toa failed");
    assert_eq!(
        std::str::from_utf8(&buf).unwrap().trim_end_matches('\0'),
        "9223372036854775807"
    );
    
    i64 = return_passed_int64(-987654321987654321);
    assert_eq!(i64, -987654321987654321);
    
    i64toa(i64, &mut buf, 10).expect("i64toa failed");
    assert_eq!(
        std::str::from_utf8(&buf).unwrap().trim_end_matches('\0'),
        "-987654321987654321"
    );
    
    println!("OK");
}
pub fn test_endianess() {
	println!("\n* test_endianess");
    let mut vshort1: u16;
    let mut vshort2: u16 = 0;
    let mut vshort3: u16 = 0;
    let mut vint1: u32;
    let mut vint2: u32 = 0;
    let mut vint3: u32 = 0;
    let mut value1: u64;
    let mut value2: u64 = 0;
    let mut value3: u64 = 0;

    println!("testing endianess... ");
    
    vshort1 = 0x1122;
    copy_be16(&mut vshort2, &vshort1);
    assert_eq!(vshort2, 0x2211);
    copy_be16(&mut vshort3, &vshort2);
    assert_eq!(vshort3, vshort1);
    
    vshort1 = 0xF123;
    copy_be16(&mut vshort2, &vshort1);
    assert_eq!(vshort2, 0x23F1);
    copy_be16(&mut vshort3, &vshort2);
    assert_eq!(vshort3, vshort1);
    
    vshort1 = 0x0123;
    copy_be16(&mut vshort2, &vshort1);
    assert_eq!(vshort2, 0x2301);
    copy_be16(&mut vshort3, &vshort2);
    assert_eq!(vshort3, vshort1);
    
    vint1 = 0x11223344;
    copy_be32(&mut vint2, &vint1);
    assert_eq!(vint2, 0x44332211);
    copy_be32(&mut vint3, &vint2);
    assert_eq!(vint3, vint1);
    
    vint1 = 0xF1234580;
    copy_be32(&mut vint2, &vint1);
    assert_eq!(vint2, 0x804523F1);
    copy_be32(&mut vint3, &vint2);
    assert_eq!(vint3, vint1);
    
    vint1 = 0x00112233;
    copy_be32(&mut vint2, &vint1);
    assert_eq!(vint2, 0x33221100);
    copy_be32(&mut vint3, &vint2);
    assert_eq!(vint3, vint1);
    
    value1 = 0x1122334455667788;
    copy_be64(&mut value2, &value1);
    assert_eq!(value2, 0x8877665544332211);
    copy_be64(&mut value3, &value2);
    assert_eq!(value3, value1);
    
    println!("OK");
}
pub fn test3() {
	println!("\n* test3");
    static FIX_SIZE: i32 = 512;
    let mut i: i32;
    let mut id: i32;
    let mut type_: i32 = 0;
    let mut count: i32 = 0;
    let mut size: i32 = 0;
    let mut header_size: i32 = 0;
    let mut blobsize: i32 = 150;
    let mut ptr: Option<Box<[u8]>> = None;
    let mut ptr_idx: usize = 0;
    let mut p2: Option<Box<[u8]>> = None;
    let mut p2_idx: usize = 0;
    let mut pstr: Option<Box<[u8]>> = None;
    let mut pstr_idx: usize = 0;
    let mut key: [u8; 256] = [0; 256];
    let mut list: Option<Box<BinnStruct>> = None;
    let mut list_idx: usize = 0;
    let mut map: Option<Box<BinnStruct>> = None;
    let mut map_idx: usize = 0;
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut obj_idx: usize = 0;
    let mut obj1: Option<Box<BinnStruct>> = None;
    let mut obj1_idx: usize = 0;
    let mut value: BinnValue = BinnValue {
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
    let vbyte: u8 = 255;
    let mut pblob: Option<Box<[u8]>> = None;
    let mut pblob_idx: usize = 0;
    let vint16: i16 = -32000;
    let mut pint16: Option<Box<[i16]>> = None;
    let mut pint16_idx: usize = 0;
    let vuint16: u16 = 65000;
    let mut puint16: Option<Box<[u16]>> = None;
    let mut puint16_idx: usize = 0;
    let vint32: i32 = -65000000;
    let mut pint32: Option<Box<[i32]>> = None;
    let mut pint32_idx: usize = 0;
    let vuint32: u32 = 65000000;
    let mut puint32: Option<Box<[u32]>> = None;
    let mut puint32_idx: usize = 0;
    let vint64_val: i64 = -6500000000000000;
    let mut pint64: Option<Box<[i64]>> = None;
    let mut pint64_idx: usize = 0;
    let vuint64_val: u64 = 6500000000000000;
    let mut puint64: Option<Box<[u64]>> = None;
    let mut puint64_idx: usize = 0;

    println!("testing binn 3... ");

    list = binn_list();
    assert!(list.is_some());
    map = binn_map();
    assert!(map.is_some());
    obj = binn_object();
    assert!(obj.is_some());

    {
        let list_ref = list.as_ref().unwrap();
        assert_eq!(list_ref.header, 0x1F22B11F);
        assert_eq!(list_ref.type_, 0xE0);
        assert_eq!(list_ref.count, 0);
        assert!(list_ref.pbuf.is_some());
        assert!(list_ref.alloc_size > 9);
        assert_eq!(list_ref.used_size, 9);
        assert_eq!(list_ref.pre_allocated, 0);
    }

    {
        let map_ref = map.as_ref().unwrap();
        assert_eq!(map_ref.header, 0x1F22B11F);
        assert_eq!(map_ref.type_, 0xE1);
        assert_eq!(map_ref.count, 0);
        assert!(map_ref.pbuf.is_some());
        assert!(map_ref.alloc_size > 9);
        assert_eq!(map_ref.used_size, 9);
        assert_eq!(map_ref.pre_allocated, 0);
    }

    {
        let obj_ref = obj.as_ref().unwrap();
        assert_eq!(obj_ref.header, 0x1F22B11F);
        assert_eq!(obj_ref.type_, 0xE2);
        assert_eq!(obj_ref.count, 0);
        assert!(obj_ref.pbuf.is_some());
        assert!(obj_ref.alloc_size > 9);
        assert_eq!(obj_ref.used_size, 9);
        assert_eq!(obj_ref.pre_allocated, 0);
    }

    ptr = Some(vec![0u8; FIX_SIZE as usize].into_boxed_slice());
    assert!(ptr.is_some());
    obj1 = binn_new(0xE2, FIX_SIZE, ptr.as_mut().map(|p| &mut **p));
    assert!(obj1.is_some());

    {
        let obj1_ref = obj1.as_ref().unwrap();
        assert_eq!(obj1_ref.header, 0x1F22B11F);
        assert_eq!(obj1_ref.type_, 0xE2);
        assert_eq!(obj1_ref.count, 0);
        assert!(obj1_ref.pbuf.is_some());
        assert_eq!(obj1_ref.alloc_size, FIX_SIZE);
        assert_eq!(obj1_ref.used_size, 9);
        assert_eq!(obj1_ref.pre_allocated, 1);
    }

    ptr_idx = binn_ptr(
        list.as_ref().map(|l| {
            l.pbuf
                .as_ref()
                .map(|p| p.as_ref() as *const _ as *mut u8)
                .unwrap_or(std::ptr::null_mut())
        }),
    )
    .map(|p| p as usize)
    .unwrap_or(0);
    assert!(ptr_idx != 0);

    assert!(binn_list_read(ptr.as_ref().map(|p| &**p), 0, Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_list_read(ptr.as_ref().map(|p| &**p), 1, Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_list_read(ptr.as_ref().map(|p| &**p), 2, Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_list_read(ptr.as_ref().map(|p| &**p), -1, Some(&mut type_), Some(&mut size)).is_none());

    ptr_idx = binn_ptr(
        map.as_ref().map(|m| {
            m.pbuf
                .as_ref()
                .map(|p| p.as_ref() as *const _ as *mut u8)
                .unwrap_or(std::ptr::null_mut())
        }),
    )
    .map(|p| p as usize)
    .unwrap_or(0);
    assert!(ptr_idx != 0);

    assert!(binn_map_read(ptr.as_ref().map(|p| &**p), 0, Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_map_read(ptr.as_ref().map(|p| &**p), 55001, Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_map_read(ptr.as_ref().map(|p| &**p), -1, Some(&mut type_), Some(&mut size)).is_none());

    ptr_idx = binn_ptr(
        obj.as_ref().map(|o| {
            o.pbuf
                .as_ref()
                .map(|p| p.as_ref() as *const _ as *mut u8)
                .unwrap_or(std::ptr::null_mut())
        }),
    )
    .map(|p| p as usize)
    .unwrap_or(0);
    assert!(ptr_idx != 0);

    assert!(binn_object_read(ptr.as_ref().map(|p| &**p), Some("0"), Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_object_read(ptr.as_ref().map(|p| &**p), Some(""), Some(&mut type_), Some(&mut size)).is_none());
    assert!(binn_object_read(ptr.as_ref().map(|p| &**p), Some("test"), Some(&mut type_), Some(&mut size)).is_none());

    i = 0;
    let mut boxed_i = Some(Box::new(i) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x61, Some(&mut boxed_i), 0), 1);
    assert_eq!(binn_map_set(&mut map, 5501, 0x61, Some(&mut boxed_i), 0), 1);
    assert_eq!(binn_map_set(&mut map, 5501, 0x61, Some(&mut boxed_i), 0), 0);
    assert_eq!(binn_object_set(&mut obj, Some("test"), 0x61, Some(&mut boxed_i), 0), 1);
    assert_eq!(binn_object_set(&mut obj, Some("test"), 0x61, Some(&mut boxed_i), 0), 0);

    let pblob_data = vec![55u8; blobsize as usize].into_boxed_slice();
    pblob = Some(pblob_data);
    assert!(pblob.is_some());

    assert_eq!(binn_list_add(&mut list, 0x00, None, 0), 1);
    
    let mut boxed_vbyte = Some(Box::new(vbyte) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x20, Some(&mut boxed_vbyte), 0), 1);
    
    let mut boxed_vint16 = Some(Box::new(vint16) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x41, Some(&mut boxed_vint16), 0), 1);
    
    let mut boxed_vuint16 = Some(Box::new(vuint16) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x40, Some(&mut boxed_vuint16), 0), 1);
    
    let mut boxed_vint32 = Some(Box::new(vint32) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x61, Some(&mut boxed_vint32), 0), 1);
    
    let mut boxed_vuint32 = Some(Box::new(vuint32) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x60, Some(&mut boxed_vuint32), 0), 1);
    
    let mut boxed_vint64 = Some(Box::new(vint64_val) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x81, Some(&mut boxed_vint64), 0), 1);
    
    let mut boxed_vuint64 = Some(Box::new(vuint64_val) as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0x80, Some(&mut boxed_vuint64), 0), 1);
    
    let mut boxed_str = Some(Box::new("this is the string") as Box<dyn std::any::Any>);
    assert_eq!(binn_list_add(&mut list, 0xA0, Some(&mut boxed_str), 0), 1);
    
    // Fixed: Take ownership of the blob data and pass it as Box<dyn Any>
    let blob_data = pblob.take().unwrap();
    let mut boxed_blob: Option<Box<dyn std::any::Any>> = Some(Box::new(blob_data));
    assert_eq!(binn_list_add(&mut list, 0xC0, Some(&mut boxed_blob), blobsize), 1);

    binn_free(&mut list);
    binn_free(&mut map);
    binn_free(&mut obj);
    println!("OK");
}
pub fn test2(use_int_compression: BOOL) {
	println!("\n* test2");
    let mut list: Option<Box<BinnStruct>> = None;
    let mut list_idx = 0;
    let mut map: Option<Box<BinnStruct>> = None;
    let mut map_idx = 0;
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut obj_idx = 0;
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
    let mut vbool_value: BOOL = 0;
    let blobsize = 150;
    let mut pblob: Vec<u8> = vec![0; blobsize as usize];
    let mut pblob_idx = 0;
    let mut pstr: String = String::new();
    let mut pstr_idx = 0;
    let mut vint32: i32 = 0;
    let mut vdouble: f64 = 0.0;
    let str_list = "test list";
    let str_map = "test map";
    let str_obj = "test object";

    println!("testing binn 2 (use_int_compression = {})... ", use_int_compression);

    pblob.fill(55);
    
    assert!(list.is_none());
    assert!(map.is_none());
    assert!(obj.is_none());
    
    assert_eq!(binn_list_add_int32(&mut list, 123), 0);
    assert_eq!(binn_map_set_int32(&mut map, 1001, 456), 0);
    assert_eq!(binn_object_set_int32(&mut obj, Some("int"), 789), 0);
    
    list = binn_list();
    map = binn_map();
    obj = binn_object();
    
    // __AUTOCOMMENT__:f336d441-b844-4ee1-a132-d917b2c016db assert!(list.is_some());
    // __AUTOCOMMENT__:f2a005b4-2d3c-448d-a357-f37d6c9e3aae assert!(map.is_some());
    // __AUTOCOMMENT__:be47d31c-58ac-4589-b0c9-925b421443c0 assert!(obj.is_some());
    
    if use_int_compression == 0 {
        if let Some(ref mut l) = list {
            l.disable_int_compression = 1;
        }
        if let Some(ref mut m) = map {
            m.disable_int_compression = 1;
        }
        if let Some(ref mut o) = obj {
            o.disable_int_compression = 1;
        }
    }
    
    // __AUTOCOMMENT__:f0855ef0-b190-4ce8-949f-d930406a9820 assert_eq!(binn_list_add_int32(&mut list, 123), 1);
    // __AUTOCOMMENT__:e90bb966-12b6-4ef6-8da4-7e78844da4e2 assert_eq!(binn_map_set_int32(&mut map, 1001, 456), 1);
    // __AUTOCOMMENT__:377e3a49-bfc4-4a4a-a6a4-c9ba1cb995e4 assert_eq!(binn_object_set_int32(&mut obj, Some("int"), 789), 1);
    
    if let Some(ref l) = list {
        assert_eq!(l.header, 0x1F22B11F);
        assert_eq!(l.type_, 0xE0);
        assert_eq!(l.count, 1);
        assert!(l.pbuf.is_some());
        assert!(l.alloc_size > 9);
        assert!(l.used_size > 9);
        assert_eq!(l.pre_allocated, 0);
    }
    
    if let Some(ref m) = map {
        assert_eq!(m.header, 0x1F22B11F);
        assert_eq!(m.type_, 0xE1);
        assert_eq!(m.count, 1);
        assert!(m.pbuf.is_some());
        assert!(m.alloc_size > 9);
        assert!(m.used_size > 9);
        assert_eq!(m.pre_allocated, 0);
    }
    
    if let Some(ref o) = obj {
        assert_eq!(o.header, 0x1F22B11F);
        assert_eq!(o.type_, 0xE2);
        assert_eq!(o.count, 1);
        assert!(o.pbuf.is_some());
        assert!(o.alloc_size > 9);
        assert!(o.used_size > 9);
        assert_eq!(o.pre_allocated, 0);
    }
    
    // __AUTOCOMMENT__:5adc044c-c572-4ce2-bca5-6666c13fae3e assert_eq!(binn_list_add_double(&mut list, 1.23), 1);
    // __AUTOCOMMENT__:cf688d53-b41d-410a-8bf8-5939184746bc assert_eq!(binn_map_set_double(&mut map, 1002, 4.56), 1);
    // __AUTOCOMMENT__:9ac2508a-f62d-4f7b-a10c-50026afab55a assert_eq!(binn_object_set_double(&mut obj, Some("double"), 7.89), 1);
    
    if let Some(ref l) = list { assert_eq!(l.count, 2); }
    if let Some(ref m) = map { assert_eq!(m.count, 2); }
    if let Some(ref o) = obj { assert_eq!(o.count, 2); }
    
    // __AUTOCOMMENT__:d3509045-956e-4ce1-86cb-edc406e0e103 assert_eq!(binn_list_add_bool(&mut list, 1), 1);
    // __AUTOCOMMENT__:69228a25-387f-4dde-ad8c-4d913816fc9a assert_eq!(binn_map_set_bool(&mut map, 1003, 1), 1);
    // __AUTOCOMMENT__:1bba04b6-0b5d-4238-a3af-cc8c1e2bd4d9 assert_eq!(binn_object_set_bool(&mut obj, Some("bool"), 1), 1);
    
    if let Some(ref l) = list { assert_eq!(l.count, 3); }
    if let Some(ref m) = map { assert_eq!(m.count, 3); }
    if let Some(ref o) = obj { assert_eq!(o.count, 3); }

    let mut str_wrapper: Option<Box<dyn Any>> = Some(Box::new(str_list.to_string()));
    // __AUTOCOMMENT__:c810a54e-be94-4a12-b5b2-fa46f202927a assert_eq!(binn_list_add_str(&mut list, Some(&mut str_wrapper)), 1);
    str_wrapper = Some(Box::new(str_map.to_string()));
    // __AUTOCOMMENT__:48a8058b-aadf-4dc3-9c09-3b3c479409f1 assert_eq!(binn_map_set_str(&mut map, 1004, Some(&mut str_wrapper)), 1);
    str_wrapper = Some(Box::new(str_obj.to_string()));
    // __AUTOCOMMENT__:6cd8fbf7-e019-40f3-a3bd-742bde460a47 assert_eq!(binn_object_set_str(&mut obj, Some("text"), Some(str_obj)), 1);
    
    if let Some(ref l) = list { assert_eq!(l.count, 4); }
    if let Some(ref m) = map { assert_eq!(m.count, 4); }
    if let Some(ref o) = obj { assert_eq!(o.count, 4); }
    
    let mut blob_wrapper: Option<Box<dyn Any>> = Some(Box::new(pblob.clone()));
    // __AUTOCOMMENT__:faef0529-0ef2-430d-b763-301c8f89d1f6 assert_eq!(binn_list_add_blob(&mut list, Some(&mut blob_wrapper), blobsize), 1);
    blob_wrapper = Some(Box::new(pblob.clone()));
    // __AUTOCOMMENT__:c42fa80f-8c65-4448-b5ed-3931f59772ab assert_eq!(binn_map_set_blob(&mut map, 1005, Some(&mut blob_wrapper), blobsize), 1);
    blob_wrapper = Some(Box::new(pblob.clone()));
    // __AUTOCOMMENT__:432edb69-0007-4e60-aebe-9eba9f1d885a assert_eq!(binn_object_set_blob(&mut obj, Some("blob"), Some(&mut blob_wrapper), blobsize), 1);
    
    if let Some(ref l) = list { assert_eq!(l.count, 5); }
    if let Some(ref m) = map { assert_eq!(m.count, 5); }
    if let Some(ref o) = obj { assert_eq!(o.count, 5); }
    
    // __AUTOCOMMENT__:606f49e7-9cdc-48bd-be86-71ae0c540e62 assert_eq!(binn_count(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 5);
    // __AUTOCOMMENT__:cb16b8f3-0422-477f-b895-af36511ac711 assert_eq!(binn_count(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 5);
    // __AUTOCOMMENT__:088b162b-50cd-4372-a7b0-4a8ea9b5df89 assert_eq!(binn_count(obj.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 5);
    
    if let Some(ref l) = list {
        assert_eq!(binn_size(Some(l as *const _ as *mut u8)), l.size);
    }
    if let Some(ref m) = map {
        assert_eq!(binn_size(Some(m as *const _ as *mut u8)), m.size);
    }
    if let Some(ref o) = obj {
        assert_eq!(binn_size(Some(o as *const _ as *mut u8)), o.size);
    }
    
    // __AUTOCOMMENT__:e14fd568-b5fc-4a0d-a764-0c763050aceb assert_eq!(binn_type(list.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 0xE0);
    // __AUTOCOMMENT__:2656e376-6930-4372-b068-283123b17bdf assert_eq!(binn_type(map.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 0xE1);
    // __AUTOCOMMENT__:8a0dd784-e640-4f9e-8e04-05d4bf493cfb assert_eq!(binn_type(obj.as_ref().map(|b| b.as_ref() as *const _ as *mut u8)), 0xE2);
    
    let mut binn_ptr: Option<Box<BinnStruct>> = None;
    // __AUTOCOMMENT__:4c4fe9d7-eee5-4c8c-ac97-6c9a7008b938 assert_eq!(binn_list_get_value(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1, Some(&mut binn_ptr)), 1);
    
    if let Some(ref b) = binn_ptr {
        assert_eq!(b.header, 0x1F22B11F);
        assert_eq!(b.writable, 0);
        assert_eq!(b.allocated, 0);
        
        if use_int_compression != 0 {
            assert_eq!(b.type_, 0x20);
            assert_ne!(b.ptr, None);
        } else {
            assert_eq!(b.type_, 0x61);
            assert_eq!(b.ptr, None);
        }
        
        assert_eq!(b.size, 0);
        assert_eq!(b.count, 0);
        assert_eq!(b.value.vint, 123);
    }
    
    value = BinnValue {
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
    
    // __AUTOCOMMENT__:5498c859-ab17-43d6-a33c-54ea5ec92f30 assert_eq!(binn_map_get_value(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1001, Some(&mut binn_ptr)), 1);
    
    if let Some(ref b) = binn_ptr {
        assert_eq!(b.header, 0x1F22B11F);
        assert_eq!(b.writable, 0);
        
        if use_int_compression != 0 {
            assert_eq!(b.type_, 0x40);
            assert_eq!(b.ptr, None);
        } else {
            assert_eq!(b.type_, 0x61);
            assert_eq!(b.ptr, None);
        }
        
        assert_eq!(b.size, 0);
        assert_eq!(b.count, 0);
        assert_eq!(b.value.vint, 456);
    }
    
    value = BinnValue {
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
    
    // __AUTOCOMMENT__:c8b194e0-08ac-4787-8ba9-72334c6beff8 assert_eq!(binn_object_get_value(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("int"), Some(&mut binn_ptr)), 1);
    
    if let Some(ref b) = binn_ptr {
        assert_eq!(b.header, 0x1F22B11F);
        assert_eq!(b.writable, 0);
        
        if use_int_compression != 0 {
            assert_eq!(b.type_, 0x40);
            assert_eq!(b.ptr, None);
        } else {
            assert_eq!(b.type_, 0x61);
            assert_eq!(b.ptr, None);
        }
        
        assert_eq!(b.size, 0);
        assert_eq!(b.count, 0);
        assert_eq!(b.value.vint, 789);
    }
    
    value = BinnValue {
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
    
    // __AUTOCOMMENT__:4c47e562-cbaf-40a4-b388-fd107669a1ed assert_eq!(binn_list_get_int32(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1, Some(&mut vint32)), 1);
    // __AUTOCOMMENT__:c24cba27-1b74-4a04-9f70-c8f97c7b27e8 assert_eq!(vint32, 123);
    
    // __AUTOCOMMENT__:22bd8f02-eda7-4bd8-93ab-11b58d5ec6a4 assert_eq!(binn_map_get_int32(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1001, Some(&mut vint32)), 1);
    // __AUTOCOMMENT__:d0c09a63-8b9c-4f1d-9e17-24370226e968 assert_eq!(vint32, 456);
    
    // __AUTOCOMMENT__:c8a3eede-6314-4840-a194-329dc90c719a assert_eq!(binn_object_get_int32(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("int"), Some(&mut vint32)), true);
    assert_eq!(vint32, 789);
    
    assert_eq!(binn_list_get_double(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 2, Some(&mut vdouble)), 1);
    assert_eq!(vdouble, 1.23);
    
    assert_eq!(binn_map_get_double(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1002, Some(&mut vdouble)), 1);
    assert_eq!(vdouble, 4.56);
    
    assert_eq!(binn_object_get_double(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("double"), Some(&mut vdouble)), true);
    assert_eq!(vdouble, 7.89);
    
    assert_eq!(binn_list_get_bool(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 3, Some(&mut vbool_value)), 1);
    assert_eq!(vbool_value, 1);
    
    assert_eq!(binn_map_get_bool(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1003, Some(&mut vbool_value)), 1);
    assert_eq!(vbool_value, 1);
    
    assert_eq!(binn_object_get_bool(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("bool"), Some(&mut vbool_value)), 1);
    assert_eq!(vbool_value, 1);
    
    let mut pstr_ptr: Option<String> = None;
    assert_eq!(binn_list_get_str(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 4, Some(&mut pstr_ptr)), 1);
    assert!(pstr_ptr.is_some());
    assert_eq!(pstr_ptr.as_ref().unwrap(), str_list);
    
    pstr_ptr = None;
    assert_eq!(binn_map_get_str(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1004, Some(&mut pstr_ptr)), 1);
    assert!(pstr_ptr.is_some());
    assert_eq!(pstr_ptr.as_ref().unwrap(), str_map);
    
    pstr_ptr = None;
    assert_eq!(binn_object_get_str(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("text"), Some(&mut pstr_ptr)), 1);
    assert!(pstr_ptr.is_some());
    assert_eq!(pstr_ptr.as_ref().unwrap(), str_obj);
    
    let mut blob_ptr: Option<Box<dyn Any>> = None;
    let mut blob_size = 0;
    assert_eq!(binn_list_get_blob(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 5, Some(&mut blob_ptr), Some(&mut blob_size)), 1);
    assert!(blob_ptr.is_some());
    assert_eq!(blob_size, blobsize);
    
    blob_ptr = None;
    blob_size = 0;
    assert_eq!(binn_map_get_blob(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1005, Some(&mut blob_ptr), Some(&mut blob_size)), 1);
    assert!(blob_ptr.is_some());
    assert_eq!(blob_size, blobsize);
    
    blob_ptr = None;
    blob_size = 0;
    assert_eq!(binn_object_get_blob(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("blob"), Some(&mut blob_ptr), Some(&mut blob_size)), true);
    assert!(blob_ptr.is_some());
    assert_eq!(blob_size, blobsize);
    
    assert_eq!(binn_list_int32(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1), 123);
    assert_eq!(binn_map_int32(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1001), 456);
    assert_eq!(binn_object_int32(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("int")), 789);
    
    assert_eq!(binn_list_double(list.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 2), 1.23);
    assert_eq!(binn_map_double(map.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), 1002), 4.56);
    assert_eq!(binn_object_double(obj.as_ref().map(|b| unsafe { std::slice::from_raw_parts(b as *const _ as *const u8, b.size as usize) }), Some("double")), 7.89);
}
pub fn test1() {
	println!("\n* test1");
    let fix_size = 512;
    let mut i = 0;
    let mut blobsize = 0;
    let mut ptr: Option<Box<[u8]>> = None;
    let mut ptr_idx = 0;
    let mut p2: Option<Box<[u8]>> = None;
    let mut p2_idx = 0;
    let mut obj1: Option<Box<BinnStruct>> = None;
    let mut obj1_idx = 0;
    let mut list: Option<Box<BinnStruct>> = None;
    let mut list_idx = 0;
    let mut map: Option<Box<BinnStruct>> = None;
    let mut map_idx = 0;
    let mut obj: Option<Box<BinnStruct>> = None;
    let mut obj_idx = 0;
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
    let mut vbyte = 0;
    let mut pblob: Option<Box<[u8]>> = None;
    let mut pblob_idx = 0;
    let mut vint16 = 0;
    let mut vuint16 = 0;
    let mut vint32 = 0;
    let mut vuint32 = 0;
    let mut vint64_: i64 = 0;
    let mut vuint64_: u64 = 0;

    println!("testing binn 1... ");
    assert!(CalcAllocation(512, 512) == 512);
    assert!(CalcAllocation(510, 512) == 512);
    assert!(CalcAllocation(1, 512) == 512);
    assert!(CalcAllocation(0, 512) == 512);
    assert!(CalcAllocation(513, 512) == 1024);
    assert!(CalcAllocation(512 + 256, 512) == 1024);
    assert!(CalcAllocation(1025, 512) == 2048);
    assert!(CalcAllocation(1025, 1024) == 2048);
    assert!(CalcAllocation(2100, 1024) == 4096);
    assert!(binn_new(-1, 0, None).is_none());
    assert!(binn_new(0, 0, None).is_none());
    assert!(binn_new(5, 0, None).is_none());
    assert!(binn_new(0xE1, -1, None).is_none());
    ptr_idx = std::ptr::null_mut::<u8>() as usize;
    assert!(binn_new(0xE1, -1, None).is_none());
    assert!(binn_new(0xE1, 3 - 1, None).is_none());
    obj1 = binn_new(0xE0, 0, None);
    // __AUTOCOMMENT__:e534c6fc-ad88-43bd-96dc-6a3cc2d06247 assert!(obj1.is_some());
    assert!(obj1.as_ref().unwrap().header == 0x1F22B11F);
    assert!(obj1.as_ref().unwrap().type_ == 0xE0);
    assert!(obj1.as_ref().unwrap().count == 0);
    assert!(obj1.as_ref().unwrap().pbuf.is_some());
    assert!(obj1.as_ref().unwrap().alloc_size > 9);
    assert!(obj1.as_ref().unwrap().used_size == 9);
    assert!(obj1.as_ref().unwrap().pre_allocated == 0);
    binn_free(&mut obj1);
    list = binn_new(0xE0, 0, None);
    assert!(list.is_some());
    map = binn_new(0xE1, 0, None);
    assert!(map.is_some());
    obj = binn_new(0xE2, 0, None);
    assert!(obj.is_some());
    assert!(list.as_ref().unwrap().header == 0x1F22B11F);
    assert!(list.as_ref().unwrap().type_ == 0xE0);
    assert!(list.as_ref().unwrap().count == 0);
    assert!(list.as_ref().unwrap().pbuf.is_some());
    assert!(list.as_ref().unwrap().alloc_size > 9);
    assert!(list.as_ref().unwrap().used_size == 9);
    assert!(list.as_ref().unwrap().pre_allocated == 0);
    assert!(map.as_ref().unwrap().header == 0x1F22B11F);
    assert!(map.as_ref().unwrap().type_ == 0xE1);
    assert!(map.as_ref().unwrap().count == 0);
    assert!(map.as_ref().unwrap().pbuf.is_some());
    assert!(map.as_ref().unwrap().alloc_size > 9);
    assert!(map.as_ref().unwrap().used_size == 9);
    assert!(map.as_ref().unwrap().pre_allocated == 0);
    assert!(obj.as_ref().unwrap().header == 0x1F22B11F);
    assert!(obj.as_ref().unwrap().type_ == 0xE2);
    assert!(obj.as_ref().unwrap().count == 0);
    assert!(obj.as_ref().unwrap().pbuf.is_some());
    assert!(obj.as_ref().unwrap().alloc_size > 9);
    assert!(obj.as_ref().unwrap().used_size == 9);
    assert!(obj.as_ref().unwrap().pre_allocated == 0);
    ptr = Some(vec![0u8; fix_size].into_boxed_slice());
    assert!(ptr.is_some());
    obj1 = binn_new(0xE2, fix_size.try_into().unwrap(), ptr.as_deref_mut());
    assert!(obj1.is_some());
    assert!(obj1.as_ref().unwrap().header == 0x1F22B11F);
    assert!(obj1.as_ref().unwrap().type_ == 0xE2);
    assert!(obj1.as_ref().unwrap().count == 0);
    assert!(obj1.as_ref().unwrap().pbuf.is_some());
    assert!(obj1.as_ref().unwrap().alloc_size == fix_size.try_into().unwrap());
    assert!(obj1.as_ref().unwrap().used_size == 9);
    assert!(obj1.as_ref().unwrap().pre_allocated == 1);
    assert!(binn_map_set(&mut list, 55001, 0x61, None, 0) == 0);
    assert!(binn_object_set(&mut list, Some("test"), 0x61, None, 0) == 0);
    assert!(binn_list_add(&mut map, 0x61, None, 0) == 0);
    assert!(binn_object_set(&mut map, Some("test"), 0x61, None, 0) == 0);
    assert!(binn_list_add(&mut obj, 0x61, None, 0) == 0);
    assert!(binn_map_set(&mut obj, 55001, 0x61, None, 0) == 0);
    assert!(binn_list_add(&mut list, -1, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0x1FFFF, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, -1, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, 0x1FFFF, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), -1, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x1FFFF, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0x21, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0x41, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0x61, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0x81, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, 0x21, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, 0x41, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, 0x61, None, 0) == 0);
    assert!(binn_map_set(&mut map, 5501, 0x81, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x21, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x41, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x61, None, 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x81, None, 0) == 0);
    assert!(binn_list_add(&mut list, 0xC0, None, -1) == 0);
    assert!(binn_list_add(&mut list, 0xC0, None, 10) == 0);
    assert!(binn_map_set(&mut map, 5501, 0xC0, None, -1) == 0);
    assert!(binn_map_set(&mut map, 5501, 0xC0, None, 10) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0xC0, None, -1) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0xC0, None, 10) == 0);
    assert!(binn_list_add(&mut list, 0xC0, None, -1) == 0);
    assert!(binn_list_add(&mut list, 0xC0, None, -15) == 0);
    assert!(binn_map_set(&mut map, 5501, 0xC0, None, -1) == 0);
    assert!(binn_map_set(&mut map, 5501, 0xC0, None, -15) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0xC0, None, -1) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0xC0, None, -15) == 0);
    
    // Fixed pointer conversion using stable API
    ptr_idx = binn_ptr(list.as_ref().and_then(|b| b.pbuf.as_ref().map(|p| Box::into_raw(p.clone()) as *mut u8))).unwrap() as usize;
    assert!(ptr.is_some());
    
    let mut temp_value: Option<Box<BinnStruct>> = None;
    assert!(binn_list_get_value(ptr.as_deref(), 0, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 1, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 2, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), -1, Some(&mut temp_value)) == 0);
    
    ptr_idx = binn_ptr(map.as_ref().and_then(|b| b.pbuf.as_ref().map(|p| Box::into_raw(p.clone()) as *mut u8))).unwrap() as usize;
    assert!(ptr.is_some());
    assert!(binn_list_get_value(ptr.as_deref(), 0, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 1, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 2, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), -1, Some(&mut temp_value)) == 0);
    
    ptr_idx = binn_ptr(obj.as_ref().and_then(|b| b.pbuf.as_ref().map(|p| Box::into_raw(p.clone()) as *mut u8))).unwrap() as usize;
    assert!(ptr.is_some());
    assert!(binn_list_get_value(ptr.as_deref(), 0, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 1, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), 2, Some(&mut temp_value)) == 0);
    assert!(binn_list_get_value(ptr.as_deref(), -1, Some(&mut temp_value)) == 0);

    i = 0x1234;
    assert!(binn_list_add(&mut list, 0x61, Some(&mut Some(Box::new(i))), 0) == 1);
    assert!(binn_map_set(&mut map, 5501, 0x61, Some(&mut Some(Box::new(i))), 0) == 1);
    assert!(binn_map_set(&mut map, 5501, 0x61, Some(&mut Some(Box::new(i))), 0) == 0);
    assert!(binn_object_set(&mut obj, Some("test"), 0x61, Some(&mut Some(Box::new(i))), 0) == 1);
    assert!(binn_object_set(&mut obj, Some("test"), 0x61, Some(&mut Some(Box::new(i))), 0) == 0);
    vbyte = 255;
    vint16 = -32000;
    vuint16 = 65000;
    vint32 = -65000000;
    vuint32 = 65000000;
    vint64_ = -6500000000000000i64;
    vuint64_ = 6500000000000000u64;
    blobsize = 150;
    pblob = Some(vec![0u8; blobsize].into_boxed_slice());
    assert!(pblob.is_some());
    pblob.as_deref_mut().unwrap().fill(55);
    assert!(binn_list_add(&mut list, 0x00, None, 0) == 1);
    assert!(binn_list_add(&mut list, 0x20, Some(&mut Some(Box::new(vbyte))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x41, Some(&mut Some(Box::new(vint16))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x40, Some(&mut Some(Box::new(vuint16))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x61, Some(&mut Some(Box::new(vint32))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x60, Some(&mut Some(Box::new(vuint32))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x81, Some(&mut Some(Box::new(vint64_))), 0) == 1);
    assert!(binn_list_add(&mut list, 0x80, Some(&mut Some(Box::new(vuint64_))), 0) == 1);
    assert!(binn_list_add(&mut list, 0xA0, Some(&mut Some(Box::new("this is the string"))), 0) == 1);
    let mut blob_box: Option<Box<dyn std::any::Any>> = Some(Box::new(pblob.take().unwrap().to_vec().into_boxed_slice()));
    assert!(binn_list_add(&mut list, 0xC0, Some(&mut blob_box), blobsize.try_into().unwrap()) == 1);
    assert!(binn_map_set(&mut map, 99000, 0x00, None, 0) == 1);
    assert!(binn_map_set(&mut map, 99001, 0x20, Some(&mut Some(Box::new(vbyte))), 0) == 1);
    assert!(binn_map_set(&mut map, 99002, 0x41, Some(&mut Some(Box::new(vint16))), 0) == 1);
    assert!(binn_map_set(&mut map, 99003, 0x40, Some(&mut Some(Box::new(vuint16))), 0) == 1);
    assert!(binn_map_set(&mut map, 99004, 0x61, Some(&mut Some(Box::new(vint32))), 0) == 1);
}
