use crate::*;
use std::fs::File;
use std::alloc::Layout;
use std::alloc;
use std::cmp;
use std::ptr;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::path::Path;
use std::os::raw::c_uchar;
use std::os::raw::c_void;
use std::ffi::CStr;
use std::vec::Vec;

pub fn lodepng_error_text(code: u32) -> &'static str {
    match code {
        0 => "no error, everything went ok",
        1 => "nothing done yet",
        10 => "end of input memory reached without huffman end code",
        11 => "error in code tree made it jump outside of huffman tree",
        13 => "problem while processing dynamic deflate block",
        14 => "problem while processing dynamic deflate block",
        15 => "problem while processing dynamic deflate block",
        16 => "invalid code while processing dynamic deflate block",
        17 => "end of out buffer memory reached while inflating",
        18 => "invalid distance code while inflating",
        19 => "end of out buffer memory reached while inflating",
        20 => "invalid deflate block BTYPE encountered while decoding",
        21 => "NLEN is not ones complement of LEN in a deflate block",
        22 => "end of out buffer memory reached while inflating",
        23 => "end of in buffer memory reached while inflating",
        24 => "invalid FCHECK in zlib header",
        25 => "invalid compression method in zlib header",
        26 => "FDICT encountered in zlib header while it's not used for PNG",
        27 => "PNG file is smaller than a PNG header",
        28 => "incorrect PNG signature, it's no PNG or corrupted",
        29 => "first chunk is not the header chunk",
        30 => "chunk length too large, chunk broken off at end of file",
        31 => "illegal PNG color type or bpp",
        32 => "illegal PNG compression method",
        33 => "illegal PNG filter method",
        34 => "illegal PNG interlace method",
        35 => "chunk length of a chunk is too large or the chunk too small",
        36 => "illegal PNG filter type encountered",
        37 => "illegal bit depth for this color type given",
        38 => "the palette is too small or too big",
        39 => "tRNS chunk before PLTE or has more entries than palette size",
        40 => "tRNS chunk has wrong size for grayscale image",
        41 => "tRNS chunk has wrong size for RGB image",
        42 => "tRNS chunk appeared while it was not allowed for this color type",
        43 => "bKGD chunk has wrong size for palette image",
        44 => "bKGD chunk has wrong size for grayscale image",
        45 => "bKGD chunk has wrong size for RGB image",
        48 => "empty input buffer given to decoder. Maybe caused by non-existing file?",
        49 => "jumped past memory while generating dynamic huffman tree",
        50 => "jumped past memory while generating dynamic huffman tree",
        51 => "jumped past memory while inflating huffman block",
        52 => "jumped past memory while inflating",
        53 => "size of zlib data too small",
        54 => "repeat symbol in tree while there was no value symbol yet",
        55 => "jumped past tree while generating huffman tree",
        56 => "given output image colortype or bitdepth not supported for color conversion",
        57 => "invalid CRC encountered (checking CRC can be disabled)",
        58 => "invalid ADLER32 encountered (checking ADLER32 can be disabled)",
        59 => "requested color conversion not supported",
        60 => "invalid window size given in the settings of the encoder (must be 0-32768)",
        61 => "invalid BTYPE given in the settings of the encoder (only 0, 1 and 2 are allowed)",
        62 => "conversion from color to grayscale not supported",
        63 => "length of a chunk too long, max allowed for PNG is 2147483647 bytes per chunk",
        64 => "the length of the END symbol 256 in the Huffman tree is 0",
        66 => "the length of a text chunk keyword given to the encoder is longer than the maximum of 79 bytes",
        67 => "the length of a text chunk keyword given to the encoder is smaller than the minimum of 1 byte",
        68 => "tried to encode a PLTE chunk with a palette that has less than 1 or more than 256 colors",
        69 => "unknown chunk type with 'critical' flag encountered by the decoder",
        71 => "invalid interlace mode given to encoder (must be 0 or 1)",
        72 => "while decoding, invalid compression method encountering in zTXt or iTXt chunk (it must be 0)",
        73 => "invalid tIME chunk size",
        74 => "invalid pHYs chunk size",
        75 => "no null termination char found while decoding text chunk",
        76 => "iTXt chunk too short to contain required bytes",
        77 => "integer overflow in buffer size",
        78 => "failed to open file for reading",
        79 => "failed to open file for writing",
        80 => "tried creating a tree of 0 symbols",
        81 => "lazy matching at pos 0 is impossible",
        82 => "color conversion to palette requested while a color isn't in palette, or index out of bounds",
        83 => "memory allocation failed",
        84 => "given image too small to contain all pixels to be encoded",
        86 => "impossible offset in lz77 encoding (internal bug)",
        87 => "must provide custom zlib function pointer if LODEPNG_COMPILE_ZLIB is not defined",
        88 => "invalid filter strategy given for LodePNGEncoderSettings.filter_strategy",
        89 => "text chunk keyword too short or long: must have size 1-79",
        90 => "windowsize must be a power of two",
        91 => "invalid decompressed idat size",
        92 => "integer overflow due to too many pixels",
        93 => "zero width or height is invalid",
        94 => "header chunk must have a size of 13 bytes",
        95 => "integer overflow with combined idat chunk size",
        96 => "invalid gAMA chunk size",
        97 => "invalid cHRM chunk size",
        98 => "invalid sRGB chunk size",
        99 => "invalid sRGB rendering intent",
        100 => "invalid ICC profile color type, the PNG specification only allows RGB or GRAY",
        101 => "PNG specification does not allow RGB ICC profile on gray color types and vice versa",
        102 => "not allowed to set grayscale ICC profile with colored pixels by PNG specification",
        103 => "invalid palette index in bKGD chunk. Maybe it came before PLTE chunk?",
        104 => "invalid bKGD color while encoding (e.g. palette index out of range)",
        105 => "integer overflow of bitsize",
        106 => "PNG file must have PLTE chunk if color type is palette",
        107 => "color convert from palette mode requested without setting the palette data in it",
        108 => "tried to add more than 256 values to a palette",
        109 => "tried to decompress zlib or deflate data larger than desired max_output_size",
        110 => "custom zlib or inflate decompression failed",
        111 => "custom zlib or deflate compression failed",
        112 => "compressed text unreasonably large",
        113 => "ICC profile unreasonably large",
        114 => "sBIT chunk has wrong size for the color type of the image",
        115 => "sBIT value out of range",
        _ => "unknown error code",
    }
}
pub fn lodepng_chunk_type(type_: &mut [u8; 5], chunk: &[u8]) {
    for i in 0..4 {
        type_[i] = chunk[4 + i];
    }
    type_[4] = 0;
}
pub fn lodepng_chunk_ancillary(chunk: Option<&[u8]>) -> bool {
    // Check if chunk is None (equivalent to NULL check in C)
    // Also ensure the slice has at least 5 bytes (since we access chunk[4])
    match chunk {
        Some(c) if c.len() > 4 => (c[4] & 32) != 0,
        _ => false,
    }
}
pub fn lodepng_chunk_private(chunk: Option<&[u8]>) -> bool {
    // Check if the chunk is None (equivalent to NULL check in C)
    // Also ensure the chunk has at least 7 bytes to avoid out-of-bounds access
    match chunk {
        Some(c) if c.len() > 6 => (c[6] & 32) != 0,
        _ => false, // Return false for NULL or insufficient length (safe default)
    }
}
pub fn lodepng_chunk_safetocopy(chunk: Option<&[u8]>) -> Option<u8> {
    chunk.map(|c| ((c[7] & 32) != 0) as u8)
}
pub fn lodepng_chunk_data(chunk: Option<&[u8]>) -> Option<&[u8]> {
    chunk.map(|c| &c[8..])
}
pub fn lodepng_chunk_data_const(chunk: Option<&[u8]>) -> Option<&[u8]> {
    // Return None if input is None (NULL in C)
    let chunk = chunk?;
    
    // Return slice starting from index 8 (equivalent to &chunk[8] in C)
    // This is safe as long as the caller ensures the slice has at least 8 bytes
    Some(&chunk[8..])
}

pub fn lodepng_save_file(buffer: &[u8], filename: &str) -> Result<(), u32> {
    let mut file = match File::create(filename) {
        Ok(f) => f,
        Err(_) => return Err(79),
    };

    if let Err(_) = file.write_all(buffer) {
        return Err(79);
    }

    Ok(())
}
pub fn lodepng_malloc(size: usize) -> Option<*mut std::ffi::c_void> {
    // Use Rust's allocator API to allocate memory
    let layout = std::alloc::Layout::from_size_align(size, std::mem::align_of::<u8>()).ok()?;
    let ptr = unsafe { std::alloc::alloc(layout) };
    
    if ptr.is_null() {
        None
    } else {
        Some(ptr as *mut std::ffi::c_void)
    }
}

pub fn lodepng_realloc(ptr: Option<*mut u8>, new_size: usize) -> Option<*mut u8> {
    if new_size == 0 {
        if let Some(p) = ptr {
            unsafe {
                alloc::dealloc(p, Layout::new::<u8>());
            return None;
            }
        }
        return None;
    }

    let layout = Layout::from_size_align(new_size, 1).ok()?;
    let new_ptr = unsafe {
        if let Some(p) = ptr {
            alloc::realloc(p, Layout::new::<u8>(), new_size)
        } else {
            alloc::alloc(layout)
        }
    };

    if new_ptr.is_null() {
        None
    } else {
        Some(new_ptr)
    }
}
pub fn lodepng_free(ptr: Option<*mut std::ffi::c_void>) {
    // In Rust, we don't need to explicitly free memory like in C.
    // If the pointer is Some, we can let Rust's memory management handle it.
    // Since this is a direct translation of a C free function, we'll just drop the pointer.
    // Note: This is a no-op in safe Rust, as raw pointers don't have automatic memory management.
    // In a real Rust program, you'd typically use Box or other smart pointers instead.
    if let Some(p) = ptr {
        unsafe {
            drop(Box::from_raw(p));
        }
    }
}
pub fn lodepng_memcpy(dst: &mut [u8], src: &[u8]) {
    // Rust slices already include bounds checking, so we don't need to pass size separately
    // The function will panic if src and dst have different lengths
    dst.copy_from_slice(src);
}
pub fn lodepng_memset(dst: &mut [u8], value: u8) {
    for byte in dst.iter_mut() {
        *byte = value;
    }
}
pub fn lodepng_addofl(a: usize, b: usize, result: &mut Option<usize>) -> bool {
    let sum = a + b;
    *result = Some(sum);
    sum < a
}
pub fn lodepng_mulofl(a: usize, b: usize, result: &mut usize) -> bool {
    *result = a * b;
    (a != 0) && ((*result / a) != b)
}
pub fn lodepng_read32bitInt(buffer: &[u8]) -> u32 {
    ((buffer[0] as u32) << 24) | 
    ((buffer[1] as u32) << 16) | 
    ((buffer[2] as u32) << 8) | 
    (buffer[3] as u32)
}
pub fn lodepng_set32bitInt(buffer: &mut [u8], value: u32) {
    buffer[0] = ((value >> 24) & 0xff) as u8;
    buffer[1] = ((value >> 16) & 0xff) as u8;
    buffer[2] = ((value >> 8) & 0xff) as u8;
    buffer[3] = (value & 0xff) as u8;
}

pub fn lodepng_filesize(filename: &str) -> Option<i64> {
    let mut file = match File::open(Path::new(filename)) {
        Ok(f) => f,
        Err(_) => return None,
    };

    if let Err(_) = file.seek(SeekFrom::End(0)) {
        return None;
    }

    let size = match file.stream_position() {
        Ok(s) => s as i64,
        Err(_) => return None,
    };

    if size == 9223372036854775807 {
        None
    } else {
        Some(size)
    }
}

pub fn lodepng_buffer_file(out: &mut [u8], filename: &str) -> Result<(), u32> {
    let mut file = match File::open(filename) {
        Ok(f) => f,
        Err(_) => return Err(78),
    };

    let readsize = match file.read(out) {
        Ok(size) => size,
        Err(_) => return Err(78),
    };

    if readsize != out.len() {
        return Err(78);
    }

    Ok(())
}
pub fn reverseBits(bits: u32, num: u32) -> u32 {
    let mut result = 0;
    for i in 0..num {
        result |= ((bits >> ((num - i) - 1u32)) & 1u32) << i;
    }
    result
}
pub fn searchCodeIndex(array: &[u32], array_size: usize, value: u32) -> usize {
    let mut left = 1;
    let mut right = array_size - 1;
    
    while left <= right {
        let mid = (left + right) >> 1;
        if array[mid] >= value {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if left >= array_size || array[left] > value {
        left -= 1;
    }
    left
}
pub fn update_adler32(adler: u32, data: Option<&[u8]>, len: u32) -> u32 {
    let data = match data {
        Some(d) => d,
        None => return adler, // Return original adler if data is None (NULL in C)
    };

    let mut data_idx = 0;
    let mut s1 = adler & 0xffff;
    let mut s2 = (adler >> 16) & 0xffff;
    let mut remaining_len = len;

    while remaining_len != 0 {
        let amount = if remaining_len > 5552 { 5552 } else { remaining_len };
        remaining_len -= amount;

        for _ in 0..amount {
            s1 += u32::from(data[data_idx]);
            data_idx += 1;
            s2 += s1;
        }

        s1 %= 65521;
        s2 %= 65521;
    }

    (s2 << 16) | s1
}
pub fn readBitFromReversedStream(bitpointer: &mut usize, bitstream: &[u8]) -> u8 {
    let result = (bitstream[*bitpointer >> 3] >> (7 - (*bitpointer & 0x7))) & 1;
    *bitpointer += 1;
    result
}
pub fn setBitOfReversedStream(bitpointer: &mut usize, bitstream: &mut [u8], bit: u8) {
    if bit == 0 {
        bitstream[*bitpointer >> 3] &= !(1 << (7 - (*bitpointer & 7)));
    } else {
        bitstream[*bitpointer >> 3] |= 1 << (7 - (*bitpointer & 7));
    }
    *bitpointer += 1;
}
pub fn lodepng_get_raw_size_idat(w: u32, h: u32, bpp: u32) -> usize {
    let line = (((w / 8) * bpp) + 1) + (((w & 7) * bpp) + 7) / 8;
    h as usize * line as usize
}
pub fn addColorBits(out: &mut [u8], index: usize, bits: u32, mut in_val: u32) {
    let m = match bits {
        1 => 7,
        2 => 3,
        _ => 1,
    };
    let p = index & m;
    in_val &= (1u32 << bits) - 1u32;
    in_val = in_val << (bits * (m - p) as u32);
    
    let byte_index = (index * bits as usize) / 8;
    if p == 0 {
        out[byte_index] = in_val as u8;
    } else {
        out[byte_index] |= in_val as u8;
    }
}
pub fn getValueRequiredBits(value: u8) -> u8 {
    if (value == 0) || (value == 255) {
        return 1;
    }
    if (value % 17) == 0 {
        if (value % 85) == 0 {
            2
        } else {
            4
        }
    } else {
        8
    }
}
pub fn paethPredictor(a: i16, b: i16, c: i16) -> u8 {
    let mut a = a;
    let mut pa = (b - c).abs();
    let pb = (a - c).abs();
    let pc = (a + b - c - c).abs();

    if pb < pa {
        a = b;
        pa = pb;
    }

    if pc < pa { c as u8 } else { a as u8 }
}
pub fn ilog2(i: usize) -> usize {
    let mut result = 0;
    let mut i = i; // Shadow the parameter to make it mutable
    
    if i >= 65536 {
        result += 16;
        i >>= 16;
    }
    if i >= 256 {
        result += 8;
        i >>= 8;
    }
    if i >= 16 {
        result += 4;
        i >>= 4;
    }
    if i >= 4 {
        result += 2;
        i >>= 2;
    }
    if i >= 2 {
        result += 1;
    }
    
    result
}
pub fn isGrayICCProfile(profile: Option<&[u8]>, size: usize) -> bool {
    // Check if profile is None or size is too small
    if size < 20 || profile.is_none() {
        return false;
    }
    
    let profile = profile.unwrap(); // Safe unwrap since we checked is_none()
    
    // Check if the slice is long enough and contains "GRAY" at positions 16-19
    profile.get(16..20).map_or(false, |slice| {
        slice == b"GRAY"
    })
}
pub fn isRGBICCProfile(profile: Option<&[u8]>, size: usize) -> bool {
    // Check if profile is None or size is too small
    if size < 20 || profile.is_none() {
        return false;
    }
    
    let profile = profile.unwrap(); // Safe unwrap since we checked is_none()
    
    // Check the specific bytes in the profile
    (profile[16] == b'R') && (profile[17] == b'G') && (profile[18] == b'B') && (profile[19] == b' ')
}
pub fn helper_helper_helper_deflateDynamic_1_1_1(
    bitlen_lld_e_idx_ref: &mut u32,
    i_ref: &mut usize,
    numcodes_lld_e_ref: &mut usize,
    j_ref: &mut u32,
    bitlen_lld: &[u32],
    bitlen_lld_e: &mut [u32],
    bitlen_lld_idx: u32,
) {
    let mut bitlen_lld_e_idx = *bitlen_lld_e_idx_ref;
    let mut i = *i_ref;
    let mut numcodes_lld_e = *numcodes_lld_e_ref;
    let j = *j_ref;
    
    let num = j / 6;
    let rest = j % 6;
    
    bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = bitlen_lld[(i + bitlen_lld_idx as usize)];
    numcodes_lld_e += 1;
    
    for _ in 0..num {
        bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = 16;
        numcodes_lld_e += 1;
        bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = 6 - 3;
        numcodes_lld_e += 1;
    }
    
    if rest >= 3 {
        bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = 16;
        numcodes_lld_e += 1;
        bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = rest - 3;
        numcodes_lld_e += 1;
    } else {
        *j_ref = j - rest;
    }
    
    i += j as usize;
    
    *bitlen_lld_e_idx_ref = bitlen_lld_e_idx;
    *i_ref = i;
    *numcodes_lld_e_ref = numcodes_lld_e;
}
pub fn helper_helper_helper_unfilterScanline_1_1_1(
    i_ref: &mut usize,
    j_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    
    while i + 2 < length {
        let s0 = scanline[i];
        let s1 = scanline[i + 1];
        let s2 = scanline[i + 2];
        
        let r0 = recon[j];
        let r1 = recon[j + 1];
        let r2 = recon[j + 2];
        
        let p0 = precon[i];
        let p1 = precon[i + 1];
        let p2 = precon[i + 2];
        
        recon[i] = s0.wrapping_add((r0.wrapping_add(p0) >> 1));
        recon[i + 1] = s1.wrapping_add((r1.wrapping_add(p1) >> 1));
        recon[i + 2] = s2.wrapping_add((r2.wrapping_add(p2) >> 1));
        
        i += 3;
        j += 3;
    }
    
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_helper_unfilterScanline_1_1_2(
    i_ref: &mut usize,
    j_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    
    while i + 3 < length {
        let s0 = scanline[i];
        let s1 = scanline[i + 1];
        let s2 = scanline[i + 2];
        let s3 = scanline[i + 3];
        
        let r0 = recon[j];
        let r1 = recon[j + 1];
        let r2 = recon[j + 2];
        let r3 = recon[j + 3];
        
        let p0 = precon[i];
        let p1 = precon[i + 1];
        let p2 = precon[i + 2];
        let p3 = precon[i + 3];
        
        recon[i] = s0.wrapping_add((r0.wrapping_add(p0) >> 1));
        recon[i + 1] = s1.wrapping_add((r1.wrapping_add(p1) >> 1));
        recon[i + 2] = s2.wrapping_add((r2.wrapping_add(p2) >> 1));
        recon[i + 3] = s3.wrapping_add((r3.wrapping_add(p3) >> 1));
        
        i += 4;
        j += 4;
    }
    
    *i_ref = i;
    *j_ref = j;
}
pub fn readChunk_gAMA(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    if chunkLength != 4 {
        return 96;
    }
    info.gama_defined = 1;
    info.gama_gamma = ((16777216u32 * data[0] as u32) + (65536u32 * data[1] as u32)) 
                     + (256u32 * data[2] as u32) + data[3] as u32;
    0
}
pub fn readChunk_pHYs(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    if chunkLength != 9 {
        return 74;
    }
    
    info.phys_defined = 1;
    info.phys_x = ((16777216u32 * data[0] as u32) + (65536u32 * data[1] as u32) + (256u32 * data[2] as u32)) + data[3] as u32;
    info.phys_y = ((16777216u32 * data[4] as u32) + (65536u32 * data[5] as u32) + (256u32 * data[6] as u32)) + data[7] as u32;
    info.phys_unit = data[8] as u32;
    
    0
}
pub fn helper_helper_decodeGeneric_2_1(
    idatsize_ref: &mut usize,
    critical_pos_ref: &mut u32,
    state: &mut LodePNGState,
    insize: usize,
    idat: &mut [u8],
    idat_idx: usize,
    chunkLength: usize,
    data: &[u8],
) {
    let mut idatsize = *idatsize_ref;
    let mut critical_pos = *critical_pos_ref;
    
    let mut newsize = None;
    if lodepng_addofl(idatsize, chunkLength, &mut newsize) {
        state.error = 95;
        return;
    }
    
    let newsize = newsize.unwrap();
    if newsize > insize {
        state.error = 95;
        return;
    }
    
    let dest_slice = &mut idat[idat_idx..][idatsize..][..chunkLength];
    lodepng_memcpy(dest_slice, &data[..chunkLength]);
    
    idatsize += chunkLength;
    critical_pos = 3;
    
    *idatsize_ref = idatsize;
    *critical_pos_ref = critical_pos;
}
pub fn lodepng_chunk_length(chunk: Option<&[u8]>) -> u32 {
    // If chunk is None, return 0 (default behavior for NULL pointer in C)
    // Otherwise, pass the slice to lodepng_read32bitInt
    chunk.map_or(0, |c| lodepng_read32bitInt(c))
}
pub fn lodepng_chunk_next_const<'a>(chunk: Option<&'a [u8]>, end: Option<&'a [u8]>) -> Option<&'a [u8]> {
    // Check if either chunk or end is None (equivalent to NULL check in C)
    let chunk = chunk?;
    let end = end?;

    // Calculate available_size (end - chunk)
    let available_size = end.as_ptr() as usize - chunk.as_ptr() as usize;
    
    // Check conditions from line 4-5
    if chunk.as_ptr() >= end.as_ptr() || available_size < 12 {
        return Some(end);
    }

    // Check PNG signature (line 8)
    if chunk.len() >= 8 && chunk[0] == 0x89 && chunk[1] == 0x50 && chunk[2] == 0x4e && chunk[3] == 0x47 
        && chunk[4] == 0x0d && chunk[5] == 0x0a && chunk[6] == 0x1a && chunk[7] == 0x0a {
        return Some(&chunk[8..]);
    }

    // Calculate total_chunk_length (lines 14-22)
    let chunk_length = lodepng_chunk_length(Some(chunk)) as usize;
    let mut total_chunk_length = None;
    if lodepng_addofl(chunk_length, 12, &mut total_chunk_length) {
        return Some(end);
    }
    let total_chunk_length = total_chunk_length.unwrap();

    if total_chunk_length > available_size {
        return Some(end);
    }

    Some(&chunk[total_chunk_length..])
}
pub fn ucvector_reserve(p: &mut Ucvector, size: usize) -> bool {
    if size > p.allocsize {
        let newsize = size + (p.allocsize >> 1);
        
        // Convert existing Vec to raw pointer if it exists
        let old_ptr = p.data.take().map(|vec| {
            let mut vec = vec;
            vec.shrink_to_fit();
            vec.as_mut_ptr()
        });

        // Attempt reallocation
        let new_ptr = lodepng_realloc(old_ptr, newsize);

        match new_ptr {
            Some(ptr) => {
                // Convert raw pointer back to Vec
                unsafe {
                    p.data = Some(Vec::from_raw_parts(ptr, p.size, newsize));
                }
                p.allocsize = newsize;
                true
            }
            None => {
                // If realloc failed, restore original data if it existed
                if let Some(ptr) = old_ptr {
                    unsafe {
                        p.data = Some(Vec::from_raw_parts(ptr, p.size, p.allocsize));
                    }
                }
                false
            }
        }
    } else {
        true
    }
}
pub fn ucvector_resize(p: &mut Ucvector, size: usize) -> bool {
    p.size = size;
    ucvector_reserve(p, size)
}
pub fn adler32(data: Option<&[u8]>, len: u32) -> u32 {
    update_adler32(1u32, data, len)
}
pub fn inflateNoCompression(
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    let mut error = 0;
    let size = reader.size;
    let mut bytepos = (reader.bp + 7) >> 3;

    // Check if we have enough data for LEN and NLEN
    if (bytepos + 4) >= size {
        return 52;
    }

    // Read LEN (2 bytes)
    let data = reader.data.as_ref().unwrap();
    let LEN = (data[bytepos] as u32) + ((data[bytepos + 1] as u32) << 8);
    bytepos += 2;

    // Read NLEN (2 bytes)
    let NLEN = (data[bytepos] as u32) + ((data[bytepos + 1] as u32) << 8);
    bytepos += 2;

    // Check NLEN validation unless ignored
    if settings.ignore_nlen == 0 && (LEN + NLEN) != 65535 {
        return 21;
    }

    // Resize output buffer
    if !ucvector_resize(out, out.size + LEN as usize) {
        return 83;
    }

    // Check if we have enough data for the uncompressed block
    if (bytepos + LEN as usize) > size {
        return 23;
    }

    // Copy uncompressed data if LEN > 0
    if LEN > 0 {
        let out_data = out.data.as_mut().unwrap();
        let start = out.size - LEN as usize;
        lodepng_memcpy(
            &mut out_data[start..],
            &data[bytepos..bytepos + LEN as usize],
        );
        bytepos += LEN as usize;
    }

    // Update reader's bit position
    reader.bp = bytepos << 3;

    error
}
pub fn peekBits(reader: &LodePngBitReader, nbits: usize) -> u32 {
    reader.buffer & ((1u32 << nbits) - 1u32)
}
pub fn advanceBits(reader: &mut LodePngBitReader, nbits: usize) {
    reader.buffer >>= nbits;
    reader.bp += nbits;
}
pub fn readBits(reader: &mut LodePngBitReader, nbits: usize) -> u32 {
    let result = peekBits(reader, nbits);
    advanceBits(reader, nbits);
    result
}
pub fn HuffmanTree_cleanup(tree: &mut HuffmanTree) {
    // In Rust, we don't need explicit free calls - dropping the Vecs will handle memory
    tree.codes = None;
    tree.lengths = None;
    tree.table_len = None;
    tree.table_value = None;
}
pub fn HuffmanTree_init(tree: &mut HuffmanTree) {
    tree.codes = None;
    tree.lengths = None;
    tree.table_len = None;
    tree.table_value = None;
}
pub fn ensureBits32(reader: &mut LodePngBitReader, nbits: usize) {
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if let Some(data) = &reader.data {
        if (start + 4) < size {
            let bytes = &data[start..start+4];
            reader.buffer = (u32::from(bytes[0]) 
                | (u32::from(bytes[1]) << 8)
                | (u32::from(bytes[2]) << 16)
                | (u32::from(bytes[3]) << 24)) >> (reader.bp & 7);
            
            if (start + 4) < size {
                reader.buffer |= u32::from(data[start + 4]) << (24 + 8 - (reader.bp & 7));
            }
        } else {
            reader.buffer = 0;
            if (start + 0) < size {
                reader.buffer |= u32::from(data[start + 0]);
            }
            if (start + 1) < size {
                reader.buffer |= u32::from(data[start + 1]) << 8;
            }
            if (start + 2) < size {
                reader.buffer |= u32::from(data[start + 2]) << 16;
            }
            if (start + 3) < size {
                reader.buffer |= u32::from(data[start + 3]) << 24;
            }
            reader.buffer >>= reader.bp & 7;
        }
    } else {
        reader.buffer = 0;
    }
    
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn ensureBits25(reader: &mut LodePngBitReader, nbits: usize) {
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if let Some(data) = &reader.data {
        if start + 3 < size {
            reader.buffer = (u32::from(data[start]) 
                | (u32::from(data[start + 1]) << 8)
                | (u32::from(data[start + 2]) << 16)
                | (u32::from(data[start + 3]) << 24));
            reader.buffer >>= reader.bp & 7;
        } else {
            reader.buffer = 0;
            if start < size {
                reader.buffer |= u32::from(data[start]);
            }
            if start + 1 < size {
                reader.buffer |= u32::from(data[start + 1]) << 8;
            }
            if start + 2 < size {
                reader.buffer |= u32::from(data[start + 2]) << 16;
            }
            reader.buffer >>= reader.bp & 7;
        }
    } else {
        reader.buffer = 0;
    }
    
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn huffmanDecodeSymbol(reader: &mut LodePngBitReader, codetree: &HuffmanTree) -> u32 {
    let code = peekBits(reader, 9) as usize;
    
    // Safely access table_len and table_value with Option handling
    let l = codetree.table_len.as_ref().map_or(0, |table| table[code] as u32);
    let mut value = codetree.table_value.as_ref().map_or(0, |table| table[code] as u32);
    
    if l <= 9 {
        advanceBits(reader, l as usize);
        value
    } else {
        advanceBits(reader, 9);
        let extra_bits = peekBits(reader, (l - 9) as usize);
        value += extra_bits;
        
        // Look up final value using the adjusted index
        let final_len = codetree.table_len.as_ref().map_or(0, |table| table[value as usize] as u32);
        let final_value = codetree.table_value.as_ref().map_or(0, |table| table[value as usize] as u32);
        
        advanceBits(reader, (final_len - 9) as usize);
        final_value
    }
}
pub fn helper_helper_inflateHuffmanBlock_1_1(
    error_ref: &mut u32,
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    tree_d: &HuffmanTree,
    code_ll: u32,
) {
    let mut error = *error_ref;
    let code_ll_index = code_ll - 257;
    
    // Calculate length and extra bits
    let mut length = LENGTHBASE[code_ll_index as usize];
    let numextrabits_l = LENGTHEXTRA[code_ll_index as usize];
    
    if numextrabits_l != 0 {
        ensureBits25(reader, 5);
        length += readBits(reader, numextrabits_l as usize);
    }
    
    ensureBits32(reader, 28);
    let code_d = huffmanDecodeSymbol(reader, tree_d);
    
    // Validate code_d
    if code_d > 29 {
        error = if code_d <= 31 { 18 } else { 16 };
        *error_ref = error;
        return;
    }
    
    let mut distance = DISTANCEBASE[code_d as usize];
    let numextrabits_d = DISTANCEEXTRA[code_d as usize];
    
    if numextrabits_d != 0 {
        distance += readBits(reader, numextrabits_d as usize);
    }
    
    let start = out.size;
    if distance > start as u32 {
        error = 52;
        *error_ref = error;
        return;
    }
    
    let backward = start - distance as usize;
    out.size += length as usize;
    
    if let Some(ref mut out_data) = out.data {
        if distance < length {
            let mut start_pos = start;
            let mut backward_pos = backward;
            let mut remaining = length as usize;
            
            // First copy the distance-sized chunk
            let chunk_size = distance as usize;
            if start_pos + chunk_size <= out_data.len() && backward_pos + chunk_size <= out_data.len() {
                let (left, right) = out_data.split_at_mut(start_pos);
                let dest = &mut right[..chunk_size];
                let src = &left[backward_pos..backward_pos + chunk_size];
                dest.copy_from_slice(src);
                start_pos += chunk_size;
                remaining -= chunk_size;
            }
            
            // Then copy byte by byte for the remaining length
            for _ in 0..remaining {
                if start_pos < out_data.len() && backward_pos < out_data.len() {
                    out_data[start_pos] = out_data[backward_pos];
                    start_pos += 1;
                    backward_pos += 1;
                }
            }
        } else {
            // Single copy operation when distance >= length
            if start + length as usize <= out_data.len() && backward + length as usize <= out_data.len() {
                let (left, right) = out_data.split_at_mut(start);
                let dest = &mut right[..length as usize];
                let src = &left[backward..backward + length as usize];
                dest.copy_from_slice(src);
            }
        }
    }
    
    *error_ref = error;
}
pub fn helper_inflateHuffmanBlock_1(
    error_ref: &mut u32,
    done_ref: &mut i32,
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    max_output_size: usize,
    tree_ll: &HuffmanTree,
    tree_d: &HuffmanTree,
    reserved_size: usize,
) {
    let mut error = *error_ref;
    let mut done = *done_ref;
    let mut code_ll;

    ensureBits32(reader, 30);
    code_ll = huffmanDecodeSymbol(reader, tree_ll);

    if code_ll <= 255 {
        if let Some(ref mut data) = out.data {
            if out.size < data.len() {
                data[out.size] = code_ll as u8;
                out.size += 1;
            } else {
                error = 83;
                *error_ref = error;
                return;
            }
        }
        code_ll = huffmanDecodeSymbol(reader, tree_ll);
    }

    if code_ll <= 255 {
        if let Some(ref mut data) = out.data {
            if out.size < data.len() {
                data[out.size] = code_ll as u8;
                out.size += 1;
            } else {
                error = 83;
                *error_ref = error;
                return;
            }
        }
    } else if (257..=285).contains(&code_ll) {
        helper_helper_inflateHuffmanBlock_1_1(&mut error, out, reader, tree_d, code_ll);
    } else if code_ll == 256 {
        done = 1;
    } else {
        error = 16;
        *error_ref = error;
        return;
    }

    if (out.allocsize - out.size) < reserved_size {
        if !ucvector_reserve(out, out.size + reserved_size) {
            error = 83;
            *error_ref = error;
            return;
        }
    }

    if reader.bp > reader.bitsize {
        error = 51;
        *error_ref = error;
        return;
    }

    if max_output_size != 0 && out.size > max_output_size {
        error = 109;
        *error_ref = error;
        return;
    }

    *error_ref = error;
    *done_ref = done;
}
pub fn helper_helper_HuffmanTree_makeTable_1_1(
    tree: &mut HuffmanTree,
    mask: u32,
    i: usize,
    l: u32,
    reverse: u32,
) -> Option<u32> {
    let index = (reverse & mask) as usize;
    
    // Safely access table_len and table_value with Option checks
    let maxlen = tree.table_len.as_ref()?.get(index).copied()? as u32;
    let tablelen = maxlen - 9u32;
    let start = tree.table_value.as_ref()?.get(index).copied()? as u32;

    if maxlen < l {
        return Some(55);
    }

    let num = 1u32 << (tablelen - (l - 9u32));
    
    // Ensure table_len and table_value are mutable and have enough capacity
    let table_len = tree.table_len.as_mut()?;
    let table_value = tree.table_value.as_mut()?;

    for j in 0..num {
        let reverse2 = reverse >> 9u32;
        let index2 = (start + (reverse2 | (j << (l - 9u32)))) as usize;
        
        // Check bounds before writing
        if index2 >= table_len.len() || index2 >= table_value.len() {
            continue;
        }
        
        table_len[index2] = l as u8;
        table_value[index2] = i as u16;
    }

    None
}
pub fn helper_HuffmanTree_makeTable_1(
    numpresent_ref: &mut usize,
    tree: &mut HuffmanTree,
    mask: u32,
    i: usize,
) -> Option<u32> {
    let mut numpresent = *numpresent_ref;
    
    // Safely access lengths and codes with Option checks
    let l = tree.lengths.as_ref()?.get(i).copied()?;
    if l == 0 {
        return None;
    }
    
    let symbol = tree.codes.as_ref()?.get(i).copied()?;
    let reverse = reverseBits(symbol, l);
    numpresent += 1;

    if l <= 9u32 {
        let num = 1u32 << (9u32 - l);
        
        // Safely access table_len and table_value with Option checks
        let table_len = tree.table_len.as_mut()?;
        let table_value = tree.table_value.as_mut()?;

        for j in 0..num {
            let index = (reverse | (j << l)) as usize;
            
            // Check bounds before accessing
            if index >= table_len.len() || index >= table_value.len() {
                continue;
            }
            
            if table_len[index] != 16 {
                return Some(55);
            }
            
            table_len[index] = l as u8;
            table_value[index] = i as u16;
        }
    } else {
        helper_helper_HuffmanTree_makeTable_1_1(tree, mask, i, l, reverse)?;
    }
    
    *numpresent_ref = numpresent;
    None
}
pub fn HuffmanTree_makeTable(tree: &mut HuffmanTree) -> Option<u32> {
    const HEADSIZE: usize = 1 << 9;
    const MASK: u32 = (1 << 9) - 1;

    // Allocate maxlens vector and initialize to 0
    let mut maxlens = vec![0u32; HEADSIZE];

    // First pass: populate maxlens
    for i in 0..tree.numcodes as usize {
        let symbol = tree.codes.as_ref()?.get(i).copied()?;
        let l = tree.lengths.as_ref()?.get(i).copied()?;
        
        if l <= 9 {
            continue;
        }
        
        let index = reverseBits(symbol >> (l - 9), 9) as usize;
        if index >= maxlens.len() {
            continue;
        }
        maxlens[index] = maxlens[index].max(l);
    }

    // Calculate total size needed
    let mut size = HEADSIZE;
    for &l in &maxlens {
        if l > 9 {
            size += 1 << (l - 9);
        }
    }

    // Allocate table_len and table_value
    tree.table_len = Some(vec![16; size]);
    tree.table_value = Some(vec![0; size]);

    // Second pass: fill table_len and table_value
    let mut pointer = HEADSIZE;
    for i in 0..HEADSIZE {
        let l = maxlens[i];
        if l <= 9 {
            continue;
        }

        tree.table_len.as_mut()?[i] = l as u8;
        tree.table_value.as_mut()?[i] = pointer as u16;
        pointer += 1 << (l - 9);
    }

    // Third pass: process all codes
    let mut numpresent = 0;
    for i in 0..tree.numcodes as usize {
        if let Some(err) = helper_HuffmanTree_makeTable_1(&mut numpresent, tree, MASK, i) {
            return Some(err);
        }
    }

    // Final processing based on numpresent
    if numpresent < 2 {
        for i in 0..size {
            let table_len = tree.table_len.as_mut()?;
            let table_value = tree.table_value.as_mut()?;
            
            if table_len[i] == 16 {
                table_len[i] = if i < HEADSIZE { 1 } else { 10 };
                table_value[i] = 65535;
            }
        }
    } else {
        for i in 0..size {
            if tree.table_len.as_ref()?[i] == 16 {
                return Some(55);
            }
        }
    }

    Some(0)
}
pub fn HuffmanTree_makeFromLengths2(tree: &mut HuffmanTree) -> Option<u32> {
    // Allocate vectors instead of raw pointers
    let mut blcount = vec![0u32; (tree.maxbitlen + 1) as usize];
    let mut nextcode = vec![0u32; (tree.maxbitlen + 1) as usize];
    tree.codes = Some(vec![0u32; tree.numcodes as usize]);

    // Check if allocations succeeded
    if tree.codes.is_none() || blcount.is_empty() || nextcode.is_empty() {
        return Some(83);
    }

    // Initialize blcount and nextcode
    for n in 0..=tree.maxbitlen {
        let idx = n as usize;
        blcount[idx] = 0;
        nextcode[idx] = 0;
    }

    // Count lengths
    for bits in 0..tree.numcodes {
        let length = tree.lengths.as_ref()?.get(bits as usize).copied()?;
        blcount[length as usize] += 1;
    }

    // Calculate nextcode
    for bits in 1..=tree.maxbitlen {
        let prev = (bits - 1) as usize;
        let current = bits as usize;
        nextcode[current] = (nextcode[prev] + blcount[prev]) << 1;
    }

    // Generate codes
    for n in 0..tree.numcodes {
        let length = tree.lengths.as_ref()?.get(n as usize).copied()?;
        if length != 0 {
            let len_idx = length as usize;
            let code = nextcode[len_idx];
            nextcode[len_idx] += 1;
            
            let codes = tree.codes.as_mut()?;
            codes[n as usize] = code & ((1 << length) - 1);
        }
    }

    // Call HuffmanTree_makeTable
    HuffmanTree_makeTable(tree)
}
pub fn HuffmanTree_makeFromLengths(
    tree: &mut HuffmanTree,
    bitlen: &[u32],
    numcodes: usize,
    maxbitlen: u32,
) -> Option<u32> {
    // Allocate vector for lengths
    tree.lengths = Some(vec![0u32; numcodes]);
    if tree.lengths.is_none() {
        return Some(83);
    }

    // Copy bitlen values to tree.lengths
    if let Some(lengths) = tree.lengths.as_mut() {
        for i in 0..numcodes {
            lengths[i] = *bitlen.get(i)?;
        }
    }

    tree.numcodes = numcodes as u32;
    tree.maxbitlen = maxbitlen;
    HuffmanTree_makeFromLengths2(tree)
}
pub fn lodepng_gtofl(a: usize, b: usize, c: usize) -> bool {
    let mut d = None;
    if lodepng_addofl(a, b, &mut d) {
        return true;
    }
    d.unwrap() > c
}
pub fn helper_helper_helper_getTreeInflateDynamic_1_1_1(
    error_ref: &mut u32,
    n_ref: &mut u32,
    HLIT_ref: &mut u32,
    i_ref: &mut u32,
    bitlen_ll_idx_ref: &mut u32,
    bitlen_d_idx_ref: &mut u32,
    reader: &mut LodePngBitReader,
    HDIST: u32,
    bitlen_ll: &mut [u32],
    bitlen_d: &mut [u32],
) {
    let mut error = *error_ref;
    let mut n = *n_ref;
    let HLIT = *HLIT_ref;
    let mut i = *i_ref;
    let bitlen_ll_idx = *bitlen_ll_idx_ref;
    let bitlen_d_idx = *bitlen_d_idx_ref;
    let mut replength = 3;
    let value;

    if i == 0 {
        error = 54;
        *error_ref = error;
        return;
    }

    replength += readBits(reader, 2);

    value = if i < (HLIT + 1) {
        bitlen_ll[((i - 1) + bitlen_ll_idx) as usize]
    } else {
        bitlen_d[(((i - HLIT) - 1) + bitlen_d_idx) as usize]
    };

    for _ in 0..replength {
        if i >= (HLIT + HDIST) {
            error = 13;
            break;
        }

        if i < HLIT {
            bitlen_ll[(i + bitlen_ll_idx) as usize] = value;
        } else {
            bitlen_d[((i - HLIT) + bitlen_d_idx) as usize] = value;
        }
        i += 1;
        n += 1;
    }

    *error_ref = error;
    *n_ref = n;
    *HLIT_ref = HLIT;
    *i_ref = i;
    *bitlen_ll_idx_ref = bitlen_ll_idx;
    *bitlen_d_idx_ref = bitlen_d_idx;
}
pub fn helper_helper_getTreeInflateDynamic_1_1(
    error_ref: &mut u32,
    n_ref: &mut u32,
    HLIT_ref: &mut u32,
    i_ref: &mut u32,
    bitlen_ll_idx_ref: &mut u32,
    bitlen_d_idx_ref: &mut u32,
    reader: &mut LodePngBitReader,
    HDIST: u32,
    bitlen_ll: &mut [u32],
    bitlen_d: &mut [u32],
    tree_cl: &HuffmanTree,
) {
    let mut error = *error_ref;
    let mut n = *n_ref;
    let mut HLIT = *HLIT_ref;
    let mut i = *i_ref;
    let mut bitlen_ll_idx = *bitlen_ll_idx_ref;
    let mut bitlen_d_idx = *bitlen_d_idx_ref;
    
    ensureBits25(reader, 22);
    let code = huffmanDecodeSymbol(reader, tree_cl);
    
    match code {
        0..=15 => {
            if i < HLIT {
                bitlen_ll[(i + bitlen_ll_idx) as usize] = code;
            } else {
                bitlen_d[((i - HLIT) + bitlen_d_idx) as usize] = code;
            }
            i += 1;
        }
        16 => {
            helper_helper_helper_getTreeInflateDynamic_1_1_1(
                &mut error,
                &mut n,
                &mut HLIT,
                &mut i,
                &mut bitlen_ll_idx,
                &mut bitlen_d_idx,
                reader,
                HDIST,
                bitlen_ll,
                bitlen_d,
            );
        }
        17 => {
            let mut replength = 3;
            replength += readBits(reader, 3);
            
            for _ in 0..replength {
                if i >= (HLIT + HDIST) {
                    error = 14;
                    break;
                }
                
                if i < HLIT {
                    bitlen_ll[(i + bitlen_ll_idx) as usize] = 0;
                } else {
                    bitlen_d[((i - HLIT) + bitlen_d_idx) as usize] = 0;
                }
                i += 1;
            }
        }
        18 => {
            let mut replength = 11;
            replength += readBits(reader, 7);
            
            for _ in 0..replength {
                if i >= (HLIT + HDIST) {
                    error = 15;
                    break;
                }
                
                if i < HLIT {
                    bitlen_ll[(i + bitlen_ll_idx) as usize] = 0;
                } else {
                    bitlen_d[((i - HLIT) + bitlen_d_idx) as usize] = 0;
                }
                i += 1;
            }
        }
        _ => {
            error = 16;
        }
    }
    
    if reader.bp > reader.bitsize {
        error = 50;
    }
    
    *error_ref = error;
    *n_ref = n;
    *HLIT_ref = HLIT;
    *i_ref = i;
    *bitlen_ll_idx_ref = bitlen_ll_idx;
    *bitlen_d_idx_ref = bitlen_d_idx;
}
pub fn ensureBits9(reader: &mut LodePngBitReader, nbits: usize) {
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if (start + 1) < size {
        if let Some(data) = &reader.data {
            reader.buffer = (data[start] as u32) | ((data[start + 1] as u32) << 8);
            reader.buffer >>= reader.bp & 7;
        } else {
            reader.buffer = 0;
        }
    } else {
        reader.buffer = 0;
        if start < size {
            if let Some(data) = &reader.data {
                reader.buffer = data[start] as u32;
            }
        }
        reader.buffer >>= reader.bp & 7;
    }
    
    let _ = nbits; // Explicitly ignore the parameter to match C behavior
}
pub fn helper_getTreeInflateDynamic_1(
    error_ref: &mut u32,
    n_ref: &mut u32,
    HLIT_ref: &mut u32,
    i_ref: &mut u32,
    bitlen_ll_idx_ref: &mut u32,
    bitlen_d_idx_ref: &mut u32,
    bitlen_cl_idx_ref: &mut u32,
    tree_ll: &mut HuffmanTree,
    tree_d: &mut HuffmanTree,
    reader: &mut LodePngBitReader,
    HDIST: u32,
    HCLEN: u32,
    bitlen_ll: &mut [u32],
    bitlen_d: &mut [u32],
    bitlen_cl: &mut [u32],
    tree_cl: &mut HuffmanTree,
) {
    let mut error = *error_ref;
    let mut n = *n_ref;
    let mut HLIT = *HLIT_ref;
    let mut i = *i_ref;
    let mut bitlen_ll_idx = *bitlen_ll_idx_ref;
    let mut bitlen_d_idx = *bitlen_d_idx_ref;
    let mut bitlen_cl_idx = *bitlen_cl_idx_ref;

    if lodepng_gtofl(reader.bp, HCLEN as usize * 3, reader.bitsize) {
        error = 50;
        *error_ref = error;
        return;
    }

    for i in 0..HCLEN {
        ensureBits9(reader, 3);
        bitlen_cl[(CLCL_ORDER[i as usize] + bitlen_cl_idx) as usize] = readBits(reader, 3);
    }

    for i in HCLEN..19 {
        bitlen_cl[(CLCL_ORDER[i as usize] + bitlen_cl_idx) as usize] = 0;
    }

    if let Some(err) = HuffmanTree_makeFromLengths(tree_cl, bitlen_cl, 19, 7) {
        error = err;
        *error_ref = error;
        return;
    }

    // Check array bounds before creating slices
    if bitlen_ll.len() < bitlen_ll_idx as usize + 288 || bitlen_d.len() < bitlen_d_idx as usize + 32 {
        error = 83;
        *error_ref = error;
        return;
    }

    // Zero out the relevant sections
    for val in bitlen_ll[bitlen_ll_idx as usize..bitlen_ll_idx as usize + 288].iter_mut() {
        *val = 0;
    }
    for val in bitlen_d[bitlen_d_idx as usize..bitlen_d_idx as usize + 32].iter_mut() {
        *val = 0;
    }

    i = 0;
    while i < (HLIT + HDIST) {
        helper_helper_getTreeInflateDynamic_1_1(
            &mut error,
            &mut n,
            &mut HLIT,
            &mut i,
            &mut bitlen_ll_idx,
            &mut bitlen_d_idx,
            reader,
            HDIST,
            bitlen_ll,
            bitlen_d,
            tree_cl,
        );
        if error != 0 {
            break;
        }
    }

    if error != 0 {
        *error_ref = error;
        return;
    }

    // Check for zero at position 256
    if bitlen_ll[256 + bitlen_ll_idx as usize] == 0 {
        error = 64;
        *error_ref = error;
        return;
    }

    // Create slices just before use to minimize borrow duration
    let bitlen_ll_slice = &bitlen_ll[bitlen_ll_idx as usize..bitlen_ll_idx as usize + 288];
    if let Some(err) = HuffmanTree_makeFromLengths(tree_ll, bitlen_ll_slice, 288, 15) {
        error = err;
        *error_ref = error;
        return;
    }

    let bitlen_d_slice = &bitlen_d[bitlen_d_idx as usize..bitlen_d_idx as usize + 32];
    if let Some(err) = HuffmanTree_makeFromLengths(tree_d, bitlen_d_slice, 32, 15) {
        error = err;
        *error_ref = error;
        return;
    }

    *error_ref = error;
    *n_ref = n;
    *HLIT_ref = HLIT;
    *i_ref = i;
    *bitlen_ll_idx_ref = bitlen_ll_idx;
    *bitlen_d_idx_ref = bitlen_d_idx;
    *bitlen_cl_idx_ref = bitlen_cl_idx;
}
pub fn ensureBits17(reader: &mut LodePngBitReader, nbits: usize) {
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if (start + 2) < size {
        if let Some(data) = &reader.data {
            reader.buffer = (u32::from(data[start]) 
                | (u32::from(data[start + 1]) << 8) 
                | (u32::from(data[start + 2]) << 16));
        }
        reader.buffer >>= reader.bp & 7;
    } else {
        reader.buffer = 0;
        if let Some(data) = &reader.data {
            if (start + 0) < size {
                reader.buffer |= u32::from(data[start]);
            }
            if (start + 1) < size {
                reader.buffer |= u32::from(data[start + 1]) << 8;
            }
        }
        reader.buffer >>= reader.bp & 7;
    }
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn getTreeInflateDynamic(
    tree_ll: &mut HuffmanTree,
    tree_d: &mut HuffmanTree,
    reader: &mut LodePngBitReader,
) -> u32 {
    let mut error = 0;
    let mut n = 0;
    let mut HLIT;
    let mut HDIST;
    let mut HCLEN;
    let mut i = 0;
    let mut bitlen_ll_idx = 0;
    let mut bitlen_d_idx = 0;
    let mut bitlen_cl_idx = 0;
    let mut tree_cl = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };

    if (reader.bitsize - reader.bp) < 14 {
        return 49;
    }

    ensureBits17(reader, 14);
    HLIT = readBits(reader, 5) + 257;
    HDIST = readBits(reader, 5) + 1;
    HCLEN = readBits(reader, 4) + 4;

    let bitlen_cl_ptr = lodepng_malloc(19 * std::mem::size_of::<u32>());
    if bitlen_cl_ptr.is_none() {
        return 83;
    }
    let mut bitlen_cl = unsafe {
        Vec::from_raw_parts(bitlen_cl_ptr.unwrap() as *mut u32, 19, 19)
    };

    let bitlen_ll_ptr = lodepng_malloc(288 * std::mem::size_of::<u32>());
    if bitlen_ll_ptr.is_none() {
        lodepng_free(Some(bitlen_cl.as_mut_ptr() as *mut std::ffi::c_void));
        std::mem::forget(bitlen_cl);
        return 83;
    }
    let mut bitlen_ll = unsafe {
        Vec::from_raw_parts(bitlen_ll_ptr.unwrap() as *mut u32, 288, 288)
    };

    let bitlen_d_ptr = lodepng_malloc(32 * std::mem::size_of::<u32>());
    if bitlen_d_ptr.is_none() {
        lodepng_free(Some(bitlen_cl.as_mut_ptr() as *mut std::ffi::c_void));
        std::mem::forget(bitlen_cl);
        lodepng_free(Some(bitlen_ll.as_mut_ptr() as *mut std::ffi::c_void));
        std::mem::forget(bitlen_ll);
        return 83;
    }
    let mut bitlen_d = unsafe {
        Vec::from_raw_parts(bitlen_d_ptr.unwrap() as *mut u32, 32, 32)
    };

    HuffmanTree_init(&mut tree_cl);

    while error == 0 {
        helper_getTreeInflateDynamic_1(
            &mut error,
            &mut n,
            &mut HLIT,
            &mut i,
            &mut bitlen_ll_idx,
            &mut bitlen_d_idx,
            &mut bitlen_cl_idx,
            tree_ll,
            tree_d,
            reader,
            HDIST,
            HCLEN,
            &mut bitlen_ll,
            &mut bitlen_d,
            &mut bitlen_cl,
            &mut tree_cl,
        );
    }

    lodepng_free(Some(bitlen_cl.as_mut_ptr() as *mut std::ffi::c_void));
    std::mem::forget(bitlen_cl);

    lodepng_free(Some(bitlen_ll.as_mut_ptr() as *mut std::ffi::c_void));
    std::mem::forget(bitlen_ll);

    lodepng_free(Some(bitlen_d.as_mut_ptr() as *mut std::ffi::c_void));
    std::mem::forget(bitlen_d);

    HuffmanTree_cleanup(&mut tree_cl);
    error
}
pub fn generateFixedDistanceTree(tree: &mut HuffmanTree) -> Option<u32> {
    let bitlen = vec![5u32; 32]; // Initialize a vector with 32 elements, all set to 5

    let error = HuffmanTree_makeFromLengths(tree, &bitlen, 32, 15);
    
    error
}
pub fn generateFixedLitLenTree(tree: &mut HuffmanTree) -> Option<u32> {
    // Allocate memory for bitlen array (288 elements)
    let mut bitlen = Vec::with_capacity(288);
    for _ in 0..288 {
        bitlen.push(0u32);
    }

    // Initialize bitlen values according to the fixed pattern
    for i in 0..=143 {
        bitlen[i] = 8;
    }
    for i in 144..=255 {
        bitlen[i] = 9;
    }
    for i in 256..=279 {
        bitlen[i] = 7;
    }
    for i in 280..=287 {
        bitlen[i] = 8;
    }

    // Call HuffmanTree_makeFromLengths with the bitlen array
    let error = HuffmanTree_makeFromLengths(tree, &bitlen, 288, 15);

    // No need to explicitly free bitlen as Vec will be dropped automatically
    error
}
pub fn getTreeInflateFixed(tree_ll: &mut HuffmanTree, tree_d: &mut HuffmanTree) -> Option<u32> {
    let error = generateFixedLitLenTree(tree_ll);
    if error.is_some() {
        return error;
    }
    generateFixedDistanceTree(tree_d)
}
pub fn inflateHuffmanBlock(
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    btype: u32,
    max_output_size: usize,
) -> u32 {
    let mut error = 0;
    let mut tree_ll = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    let mut tree_d = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    const reserved_size: usize = 260;
    let mut done = 0;

    if !ucvector_reserve(out, out.size + reserved_size) {
        return 83;
    }

    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);

    if btype == 1 {
        if let Some(err) = getTreeInflateFixed(&mut tree_ll, &mut tree_d) {
            error = err;
        }
    } else {
        error = getTreeInflateDynamic(&mut tree_ll, &mut tree_d, reader);
    }

    while error == 0 && done == 0 {
        helper_inflateHuffmanBlock_1(
            &mut error,
            &mut done,
            out,
            reader,
            max_output_size,
            &tree_ll,
            &tree_d,
            reserved_size,
        );
    }

    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);
    error
}
pub fn LodePNGBitReader_init(reader: &mut LodePngBitReader, data: Option<Vec<u8>>, size: usize) -> u32 {
    let mut temp = Option::<usize>::None;
    reader.data = data;
    reader.size = size;
    
    if lodepng_mulofl(size, 8, &mut reader.bitsize) {
        return 105;
    }
    
    if lodepng_addofl(reader.bitsize, 64, &mut temp) {
        return 105;
    }
    
    reader.bp = 0;
    reader.buffer = 0;
    0
}
pub fn lodepng_inflatev(
    out: &mut Ucvector,
    in_data: Option<Vec<u8>>,
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    let mut BFINAL = 0;
    let mut reader = LodePngBitReader {
        data: in_data.clone(),
        size: insize,
        bitsize: 0,
        bp: 0,
        buffer: 0,
    };
    let mut error = LodePNGBitReader_init(&mut reader, in_data, insize);
    if error != 0 {
        return error;
    }

    while BFINAL == 0 {
        let BTYPE;
        if (reader.bitsize - reader.bp) < 3 {
            return 52;
        }
        ensureBits9(&mut reader, 3);
        BFINAL = readBits(&mut reader, 1);
        BTYPE = readBits(&mut reader, 2);

        if BTYPE == 3 {
            return 20;
        } else if BTYPE == 0 {
            error = inflateNoCompression(out, &mut reader, settings);
        } else {
            error = inflateHuffmanBlock(out, &mut reader, BTYPE, settings.max_output_size);
        }

        if error == 0 && settings.max_output_size != 0 && out.size > settings.max_output_size {
            error = 109;
        }
        if error != 0 {
            break;
        }
    }

    error
}
pub fn inflatev(
    out: &mut Ucvector,
    in_data: Option<Vec<u8>>,
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    if let Some(custom_inflate) = settings.custom_inflate {
        // Since we can't safely call the C function from Rust without unsafe,
        // we'll need to use FFI here. However, per the rules, we should avoid unsafe.
        // This is a case where we'd normally need unsafe, but since the rules prohibit it,
        // we'll return an error code indicating the operation isn't supported in safe Rust.
        110 // Return error code indicating custom inflate isn't supported in safe Rust
    } else {
        lodepng_inflatev(out, in_data, insize, settings)
    }
}
pub fn lodepng_zlib_decompressv(
    out: &mut Ucvector,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    if insize < 2 {
        return 53;
    }

    if (((in_data[0] as u32) * 256 + in_data[1] as u32) % 31) != 0 {
        return 24;
    }

    let CM = in_data[0] & 15;
    let CINFO = (in_data[0] >> 4) & 15;
    let FDICT = (in_data[1] >> 5) & 1;

    if (CM != 8) || (CINFO > 7) {
        return 25;
    }

    if FDICT != 0 {
        return 26;
    }

    let error = inflatev(out, Some(in_data[2..].to_vec()), insize - 2, settings);
    if error != 0 {
        return error;
    }

    if settings.ignore_adler32 == 0 {
        let ADLER32 = lodepng_read32bitInt(&in_data[insize - 4..]);
        let checksum = adler32(out.data.as_deref(), out.size as u32);
        if checksum != ADLER32 {
            return 58;
        }
    }

    0
}
pub fn ucvector_init(buffer: Option<Vec<u8>>, size: usize) -> Ucvector {
    Ucvector {
        data: buffer,
        size,
        allocsize: size,
    }
}
pub fn zlib_decompress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    expected_size: usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    let error = if let Some(custom_zlib) = settings.custom_zlib {
        let mut c_out: *mut u8 = std::ptr::null_mut();
        let mut c_outsize: usize = 0;
        let error = custom_zlib(
            &mut c_out,
            &mut c_outsize,
            in_data.as_ptr(),
            insize,
            settings,
        );
        if error != 0 {
            let mut final_error = 110;
            if settings.max_output_size != 0 && c_outsize > settings.max_output_size {
                final_error = 109;
            }
            final_error
        } else {
            unsafe {
                *out = Some(Vec::from_raw_parts(
                    c_out,
                    c_outsize,
                    c_outsize,
                ));
                *outsize = c_outsize;
            }
            0
        }
    } else {
        let mut v = ucvector_init(out.take(), *outsize);
        if expected_size != 0 {
            ucvector_resize(&mut v, *outsize + expected_size);
            v.size = *outsize;
        }
        let error = lodepng_zlib_decompressv(&mut v, in_data, insize, settings);
        *out = v.data;
        *outsize = v.size;
        error
    };
    error
}
pub fn alloc_string_sized(in_: Option<&[u8]>, insize: usize) -> Option<Vec<u8>> {
    // Check if input is None (equivalent to NULL check in C)
    let in_ = in_?;

    // Allocate output buffer with size insize + 1 (for null terminator)
    let mut out = Vec::with_capacity(insize + 1);
    
    // Ensure we have enough capacity before writing
    if out.capacity() < insize + 1 {
        return None;
    }

    // Copy the input data
    out.extend_from_slice(&in_[..insize]);
    
    // Add null terminator (0 byte)
    out.push(0);

    Some(out)
}

pub fn lodepng_strlen(a: Option<&CStr>) -> usize {
    // Convert Option<&CStr> to &CStr or return 0 if None (NULL in C)
    let a = match a {
        Some(s) => s,
        None => return 0,
    };

    // Get the underlying bytes and find the NUL terminator
    a.to_bytes_with_nul().len() - 1
}

pub fn alloc_string(in_: Option<&CStr>) -> Option<Vec<u8>> {
    alloc_string_sized(in_.map(|s| s.to_bytes()), lodepng_strlen(in_))
}
pub fn lodepng_add_text_sized(info: &mut LodePNGInfo, key: Option<&CStr>, str: Option<&[u8]>, size: usize) -> u32 {
    // Error code 83 represents allocation failure
    const ALLOCATION_ERROR: u32 = 83;

    // Handle text_keys reallocation
    let new_keys = match &info.text_keys {
        Some(keys) => {
            let mut new_vec = keys.clone();
            new_vec.push(String::new());
            Some(new_vec)
        },
        None => Some(vec![String::new()]),
    };

    // Handle text_strings reallocation
    let new_strings = match &info.text_strings {
        Some(strings) => {
            let mut new_vec = strings.clone();
            new_vec.push(String::new());
            Some(new_vec)
        },
        None => Some(vec![String::new()]),
    };

    // Check if allocations succeeded
    if new_keys.is_none() || new_strings.is_none() {
        return ALLOCATION_ERROR;
    }

    // Update the info struct
    info.text_keys = new_keys;
    info.text_strings = new_strings;
    info.text_num += 1;

    // Allocate and store the key
    let key_bytes = alloc_string(key);
    let str_bytes = alloc_string_sized(str, size);

    if key_bytes.is_none() || str_bytes.is_none() {
        return ALLOCATION_ERROR;
    }

    // Convert bytes to strings and store them
    if let Some(keys) = &mut info.text_keys {
        if let Some(strings) = &mut info.text_strings {
            let idx = info.text_num - 1;
            if let Ok(key_str) = String::from_utf8(key_bytes.unwrap()) {
                keys[idx] = key_str;
            } else {
                return ALLOCATION_ERROR;
            }
            if let Ok(str_str) = String::from_utf8(str_bytes.unwrap()) {
                strings[idx] = str_str;
            } else {
                return ALLOCATION_ERROR;
            }
        }
    }

    0 // Success
}
pub fn helper_readChunk_zTXt_1(
    error_ref: &mut u32,
    zlibsettings_ref: &mut LodePNGDecompressSettings,
    length_ref: &mut u32,
    string2_begin_ref: &mut u32,
    key_idx_ref: &mut u32,
    info: &mut LodePNGInfo,
    decoder: &LodePNGDecoderSettings,
    data: &[u8],
    chunkLength: usize,
    key: &mut [u8],
    str: &mut Option<Vec<u8>>,
    size: &mut usize,
) {
    let mut error = *error_ref;
    let mut zlibsettings = zlibsettings_ref.clone();
    let mut length = *length_ref;
    let mut string2_begin = *string2_begin_ref;
    let mut key_idx = *key_idx_ref;

    // Find the length of the key (until null terminator)
    length = match data.iter().position(|&x| x == 0) {
        Some(pos) => pos as u32,
        None => chunkLength as u32,
    };

    if (length + 2) >= chunkLength as u32 {
        error = 75;
    } else if length < 1 || length > 79 {
        error = 89;
    } else {
        // Allocate space for key (length + null terminator)
        let key_ptr = lodepng_malloc((length + 1) as usize);
        if key_ptr.is_none() {
            error = 83;
        } else {
            key_idx = key_ptr.unwrap() as u32;
            // Copy key data
            lodepng_memcpy(&mut key[..length as usize], &data[..length as usize]);
            key[length as usize] = 0;

            if data[length as usize + 1] != 0 {
                error = 72;
            } else {
                string2_begin = length + 2;
                if string2_begin > chunkLength as u32 {
                    error = 75;
                } else {
                    length = (chunkLength as u32) - string2_begin;
                    zlibsettings.max_output_size = decoder.max_text_size;
                    error = zlib_decompress(
                        str,
                        size,
                        0,
                        &data[string2_begin as usize..],
                        length as usize,
                        &zlibsettings,
                    );
                    if error != 0 && *size > zlibsettings.max_output_size {
                        error = 112;
                    }
                    if error == 0 {
                        let key_cstr = unsafe { CStr::from_ptr(key.as_ptr() as *const i8) };
                        error = lodepng_add_text_sized(
                            info,
                            Some(key_cstr),
                            str.as_ref().map(|v| v.as_slice()),
                            *size,
                        );
                    }
                }
            }
        }
    }

    *error_ref = error;
    *zlibsettings_ref = zlibsettings;
    *length_ref = length;
    *string2_begin_ref = string2_begin;
    *key_idx_ref = key_idx;
}
pub fn readChunk_zTXt(
    info: &mut LodePNGInfo,
    decoder: &LodePNGDecoderSettings,
    data: &[u8],
    chunkLength: usize,
) -> u32 {
    let mut error = 0;
    let mut zlibsettings = decoder.zlibsettings.clone();
    let mut length = 0;
    let mut string2_begin = 0;
    let mut key = None;
    let mut key_idx = 0;
    let mut str = None;
    let mut size = 0;

    while error == 0 {
        helper_readChunk_zTXt_1(
            &mut error,
            &mut zlibsettings,
            &mut length,
            &mut string2_begin,
            &mut key_idx,
            info,
            decoder,
            data,
            chunkLength,
            key.as_mut().map(|v: &mut Vec<u8>| v.as_mut_slice()).unwrap_or(&mut []),
            &mut str,
            &mut size,
        );
    }

    if let Some(k) = key {
        lodepng_free(Some(k.as_ptr() as *mut c_void));
    }
    if let Some(s) = str {
        lodepng_free(Some(s.as_ptr() as *mut c_void));
    }

    error
}
pub fn readChunk_tRNS(color: &mut LodePNGColorMode, data: &[u8], chunkLength: usize) -> u32 {
    match color.colortype {
        LodePNGColorType::LCT_PALETTE => {
            if chunkLength > color.palettesize {
                return 39;
            }
            if let Some(ref mut palette) = color.palette {
                for i in 0..chunkLength {
                    palette[(4 * i) + 3] = data[i];
                }
            }
        }
        LodePNGColorType::LCT_GREY => {
            if chunkLength != 2 {
                return 30;
            }
            color.key_defined = 1;
            let key = (u32::from(data[0]) * 256) + u32::from(data[1]);
            color.key_r = key;
            color.key_g = key;
            color.key_b = key;
        }
        LodePNGColorType::LCT_RGB => {
            if chunkLength != 6 {
                return 41;
            }
            color.key_defined = 1;
            color.key_r = (u32::from(data[0]) * 256) + u32::from(data[1]);
            color.key_g = (u32::from(data[2]) * 256) + u32::from(data[3]);
            color.key_b = (u32::from(data[4]) * 256) + u32::from(data[5]);
        }
        _ => return 42,
    }
    0
}

pub fn lodepng_add_text(info: &mut LodePNGInfo, key: Option<&CStr>, str: Option<&CStr>) -> u32 {
    let size = lodepng_strlen(str);
    lodepng_add_text_sized(info, key, str.map(|s| s.to_bytes()), size)
}

pub fn helper_readChunk_tEXt_1(
    error_ref: &mut u32,
    key_idx_ref: &mut usize,
    str_idx_ref: &mut usize,
    info: &mut LodePNGInfo,
    data: &[u8],
    chunkLength: usize,
    key: &mut Vec<u8>,
    str: &mut Vec<u8>,
) {
    let mut error = *error_ref;
    let mut key_idx = *key_idx_ref;
    let mut str_idx = *str_idx_ref;
    let mut length = 0;
    
    // The original C code increments length 17 times (lines 9-25)
    // This appears to be a fixed offset before the actual key starts
    length += 17;

    // Find the null terminator for the key
    while length < chunkLength && data[length] != 0 {
        length += 1;
    }

    if length < 1 || length > 79 {
        error = 89;
        *error_ref = error;
        *key_idx_ref = key_idx;
        *str_idx_ref = str_idx;
        return;
    }

    // Allocate space for key (including null terminator)
    key.resize(length + 1, 0);
    key[..length].copy_from_slice(&data[..length]);
    key[length] = 0;

    let string2_begin = length + 1;
    length = if chunkLength < string2_begin {
        0
    } else {
        chunkLength - string2_begin
    };

    // Allocate space for string (including null terminator)
    str.resize(length + 1, 0);
    str[..length].copy_from_slice(&data[string2_begin..string2_begin + length]);
    str[length] = 0;

    // Convert the byte vectors to C strings
    let key_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&key) };
    let str_cstr = unsafe { CStr::from_bytes_with_nul_unchecked(&str) };

    error = lodepng_add_text(info, Some(key_cstr), Some(str_cstr));

    *error_ref = error;
    *key_idx_ref = key_idx;
    *str_idx_ref = str_idx;
}
pub fn readChunk_tEXt(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    let mut error = 0;
    let mut key = Vec::new();
    let mut key_idx = 0;
    let mut str = Vec::new();
    let mut str_idx = 0;

    while error == 0 {
        helper_readChunk_tEXt_1(
            &mut error,
            &mut key_idx,
            &mut str_idx,
            info,
            data,
            chunkLength,
            &mut key,
            &mut str,
        );
    }

    // In Rust, vectors are automatically dropped when they go out of scope,
    // so we don't need an explicit free operation like in C
    error
}
pub fn string_cleanup(out: &mut Option<*mut std::ffi::c_void>) {
    // Take the value from the Option, leaving None in its place
    let ptr = out.take();
    // Call lodepng_free with the pointer
    lodepng_free(ptr);
    // The Option is already None due to take(), so no need to explicitly set it
}
pub fn lodepng_clear_icc(info: &mut LodePNGInfo) {
    // Clean up the iccp_name string
    string_cleanup(&mut info.iccp_name.take().map(|s| std::ffi::CString::new(s).unwrap().into_raw() as *mut std::ffi::c_void));
    
    // Free the iccp_profile and reset related fields
    info.iccp_profile = None;
    info.iccp_profile_size = 0;
    info.iccp_defined = 0;
}
pub fn readChunk_iCCP(
    info: &mut LodePNGInfo,
    decoder: &LodePNGDecoderSettings,
    data: &[u8],
    chunkLength: usize,
) -> u32 {
    let mut error = 0;
    let mut size = 0;
    let zlibsettings = decoder.zlibsettings.clone();
    
    info.iccp_defined = 1;
    if info.iccp_name.is_some() {
        lodepng_clear_icc(info);
    }

    // Find the length of the name string (until null terminator)
    let length = match data[..chunkLength].iter().position(|&x| x == 0) {
        Some(pos) => pos,
        None => chunkLength,
    };

    if length + 2 >= chunkLength {
        return 75;
    }
    if length < 1 || length > 79 {
        return 89;
    }

    // Convert the name bytes to a String
    info.iccp_name = Some(
        String::from_utf8(data[..length].to_vec())
            .map_err(|_| return 83)
            .unwrap(),
    );

    if data[length + 1] != 0 {
        return 72;
    }

    let string2_begin = length + 2;
    if string2_begin > chunkLength {
        return 75;
    }

    let length = chunkLength - string2_begin;
    let mut zlibsettings = zlibsettings;
    zlibsettings.max_output_size = decoder.max_icc_size;

    error = zlib_decompress(
        &mut info.iccp_profile,
        &mut size,
        0,
        &data[string2_begin..],
        length,
        &zlibsettings,
    );

    if error != 0 && size > zlibsettings.max_output_size {
        error = 113;
    }

    info.iccp_profile_size = size as u32;
    if error == 0 && info.iccp_profile_size == 0 {
        error = 100;
    }

    error
}
pub fn lodepng_add_itext_sized(
    info: &mut LodePNGInfo,
    key: Option<&CStr>,
    langtag: Option<&CStr>,
    transkey: Option<&CStr>,
    str: Option<&[u8]>,
    size: usize,
) -> u32 {
    // Check if any of the input strings is None (equivalent to NULL check in C)
    if key.is_none() || langtag.is_none() || transkey.is_none() || str.is_none() {
        return 83;
    }

    // Get mutable references to each vector, creating new ones if they don't exist
    let itext_keys = info.itext_keys.get_or_insert_with(Vec::new);
    let itext_langtags = info.itext_langtags.get_or_insert_with(Vec::new);
    let itext_transkeys = info.itext_transkeys.get_or_insert_with(Vec::new);
    let itext_strings = info.itext_strings.get_or_insert_with(Vec::new);

    // Push new entries to each vector
    if let Some(key_bytes) = alloc_string(key) {
        itext_keys.push(String::from_utf8(key_bytes).unwrap());
    } else {
        return 83;
    }
    if let Some(langtag_bytes) = alloc_string(langtag) {
        itext_langtags.push(String::from_utf8(langtag_bytes).unwrap());
    } else {
        return 83;
    }
    if let Some(transkey_bytes) = alloc_string(transkey) {
        itext_transkeys.push(String::from_utf8(transkey_bytes).unwrap());
    } else {
        return 83;
    }
    if let Some(str_bytes) = alloc_string_sized(str, size) {
        itext_strings.push(String::from_utf8(str_bytes).unwrap());
    } else {
        return 83;
    }

    // Increment the counter
    info.itext_num += 1;

    0
}
pub fn helper_readChunk_iTXt_1(
    error_ref: &mut u32,
    i_ref: &mut u32,
    zlibsettings_ref: &mut LodePNGDecompressSettings,
    length_ref: &mut u32,
    begin_ref: &mut u32,
    compressed_ref: &mut u32,
    key_idx_ref: &mut u32,
    langtag_idx_ref: &mut u32,
    transkey_idx_ref: &mut u32,
    info: &mut LodePNGInfo,
    decoder: &LodePNGDecoderSettings,
    data: &[u8],
    chunkLength: usize,
    key: &mut [u8],
    langtag: &mut [u8],
    transkey: &mut [u8],
) {
    let mut error = *error_ref;
    let mut i = *i_ref;
    let mut zlibsettings = zlibsettings_ref.clone();
    let mut length = *length_ref;
    let mut begin = *begin_ref;
    let mut compressed = *compressed_ref;
    let mut key_idx = *key_idx_ref;
    let mut langtag_idx = *langtag_idx_ref;
    let mut transkey_idx = *transkey_idx_ref;

    if chunkLength < 5 {
        error = 30;
        *error_ref = error;
        return;
    }

    // Find length of key
    length = 0;
    while (length as usize) < chunkLength && data[length as usize] != 0 {
        length += 1;
    }

    if length + 3 >= chunkLength as u32 {
        error = 75;
        *error_ref = error;
        return;
    }

    if length < 1 || length > 79 {
        error = 89;
        *error_ref = error;
        return;
    }

    // Copy key
    lodepng_memcpy(&mut key[..length as usize], &data[..length as usize]);
    key[length as usize] = 0;

    compressed = data[length as usize + 1] as u32;
    if data[length as usize + 2] != 0 {
        error = 72;
        *error_ref = error;
        return;
    }

    begin = length + 3;
    length = 0;

    // Find length of langtag
    i = begin;
    while (i as usize) < chunkLength && data[i as usize] != 0 {
        length += 1;
        i += 1;
    }

    // Copy langtag
    lodepng_memcpy(
        &mut langtag[..length as usize],
        &data[begin as usize..(begin + length) as usize],
    );
    langtag[length as usize] = 0;
    begin += length + 1;
    length = 0;

    // Find length of transkey
    i = begin;
    while (i as usize) < chunkLength && data[i as usize] != 0 {
        length += 1;
        i += 1;
    }

    // Copy transkey
    lodepng_memcpy(
        &mut transkey[..length as usize],
        &data[begin as usize..(begin + length) as usize],
    );
    transkey[length as usize] = 0;
    begin += length + 1;

    length = if chunkLength < begin as usize {
        0
    } else {
        (chunkLength - begin as usize) as u32
    };

    if compressed != 0 {
        let mut str: Option<Vec<u8>> = None;
        let mut size = 0;
        zlibsettings.max_output_size = decoder.max_text_size;
        error = zlib_decompress(
            &mut str,
            &mut size,
            0,
            &data[begin as usize..],
            length as usize,
            &zlibsettings,
        );
        if error != 0 && size > zlibsettings.max_output_size {
            error = 112;
        }
        if error == 0 {
            let key_cstr = unsafe { CStr::from_ptr(key.as_ptr() as *const i8) };
            let langtag_cstr = unsafe { CStr::from_ptr(langtag.as_ptr() as *const i8) };
            let transkey_cstr = unsafe { CStr::from_ptr(transkey.as_ptr() as *const i8) };
            error = lodepng_add_itext_sized(
                info,
                Some(key_cstr),
                Some(langtag_cstr),
                Some(transkey_cstr),
                str.as_deref(),
                size,
            );
        }
        if let Some(s) = str {
            lodepng_free(Some(s.as_ptr() as *mut std::ffi::c_void));
        }
    } else {
        let key_cstr = unsafe { CStr::from_ptr(key.as_ptr() as *const i8) };
        let langtag_cstr = unsafe { CStr::from_ptr(langtag.as_ptr() as *const i8) };
        let transkey_cstr = unsafe { CStr::from_ptr(transkey.as_ptr() as *const i8) };
        error = lodepng_add_itext_sized(
            info,
            Some(key_cstr),
            Some(langtag_cstr),
            Some(transkey_cstr),
            Some(&data[begin as usize..(begin + length) as usize]),
            length as usize,
        );
    }

    *error_ref = error;
    *i_ref = i;
    *zlibsettings_ref = zlibsettings;
    *length_ref = length;
    *begin_ref = begin;
    *compressed_ref = compressed;
    *key_idx_ref = key_idx;
    *langtag_idx_ref = langtag_idx;
    *transkey_idx_ref = transkey_idx;
}

pub fn readChunk_iTXt(
    info: &mut LodePNGInfo,
    decoder: &LodePNGDecoderSettings,
    data: &[u8],
    chunkLength: usize,
) -> u32 {
    let mut error = 0;
    let mut i = 0;
    let mut zlibsettings = decoder.zlibsettings.clone();
    let mut length = 0;
    let mut begin = 0;
    let mut compressed = 0;
    
    // Initialize buffers with reasonable maximum sizes
    let mut key = vec![0u8; 80]; // Max key length is 79 + null terminator
    let mut key_idx = 0;
    let mut langtag = vec![0u8; 256]; // Arbitrary reasonable size
    let mut langtag_idx = 0;
    let mut transkey = vec![0u8; 256]; // Arbitrary reasonable size
    let mut transkey_idx = 0;

    while error == 0 {
        helper_readChunk_iTXt_1(
            &mut error,
            &mut i,
            &mut zlibsettings,
            &mut length,
            &mut begin,
            &mut compressed,
            &mut key_idx,
            &mut langtag_idx,
            &mut transkey_idx,
            info,
            decoder,
            data,
            chunkLength,
            &mut key,
            &mut langtag,
            &mut transkey,
        );
    }

    // In Rust, the vectors will be automatically dropped when they go out of scope
    // No need for explicit freeing like in C
    error
}
pub fn lodepng_chunk_append(
    out: &mut Option<*mut u8>,
    outsize: &mut usize,
    chunk: Option<&[u8]>,
) -> u32 {
    let total_chunk_length = match lodepng_chunk_length(chunk) {
        0 => return 77,
        len => len as usize,
    };

    let total_chunk_length_with_overhead = match total_chunk_length.checked_add(12) {
        Some(v) => v,
        None => return 77,
    };

    let new_length = match outsize.checked_add(total_chunk_length_with_overhead) {
        Some(v) => v,
        None => return 77,
    };

    let new_buffer = lodepng_realloc(*out, new_length);
    if new_buffer.is_none() {
        return 83;
    }
    *out = new_buffer;
    *outsize = new_length;

    unsafe {
        let chunk_start = (*out).unwrap().add(new_length - total_chunk_length_with_overhead);
        if let Some(chunk_data) = chunk {
            ptr::copy_nonoverlapping(
                chunk_data.as_ptr(),
                chunk_start,
                total_chunk_length_with_overhead,
            );
        }
    }

    0
}
pub fn readChunk_sRGB(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    if chunkLength != 1 {
        return 98;
    }
    info.srgb_defined = 1;
    info.srgb_intent = data[0] as u32;
    0
}
pub fn readChunk_cHRM(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    if chunkLength != 32 {
        return 97;
    }
    
    info.chrm_defined = 1;
    info.chrm_white_x = (16777216u32 * data[0] as u32) + (65536u32 * data[1] as u32) + (256u32 * data[2] as u32) + data[3] as u32;
    info.chrm_white_y = (16777216u32 * data[4] as u32) + (65536u32 * data[5] as u32) + (256u32 * data[6] as u32) + data[7] as u32;
    info.chrm_red_x = (16777216u32 * data[8] as u32) + (65536u32 * data[9] as u32) + (256u32 * data[10] as u32) + data[11] as u32;
    info.chrm_red_y = (16777216u32 * data[12] as u32) + (65536u32 * data[13] as u32) + (256u32 * data[14] as u32) + data[15] as u32;
    info.chrm_green_x = (16777216u32 * data[16] as u32) + (65536u32 * data[17] as u32) + (256u32 * data[18] as u32) + data[19] as u32;
    info.chrm_green_y = (16777216u32 * data[20] as u32) + (65536u32 * data[21] as u32) + (256u32 * data[22] as u32) + data[23] as u32;
    info.chrm_blue_x = (16777216u32 * data[24] as u32) + (65536u32 * data[25] as u32) + (256u32 * data[26] as u32) + data[27] as u32;
    info.chrm_blue_y = (16777216u32 * data[28] as u32) + (65536u32 * data[29] as u32) + (256u32 * data[30] as u32) + data[31] as u32;
    
    0
}
pub fn lodepng_color_mode_alloc_palette(info: &mut LodePNGColorMode) {
    if info.palette.is_none() {
        // Allocate a new palette with 256 RGBA entries (1024 bytes)
        info.palette = Some(vec![0; 1024]);
    }

    if let Some(palette) = &mut info.palette {
        // Initialize palette: set RGB to 0 and alpha to 255 for each entry
        for i in 0..256 {
            palette[i * 4 + 0] = 0; // R
            palette[i * 4 + 1] = 0; // G
            palette[i * 4 + 2] = 0; // B
            palette[i * 4 + 3] = LCT_MAX_OCTET_VALUE; // A
        }
    }
}
pub fn readChunk_PLTE(color: &mut LodePNGColorMode, data: &[u8], chunkLength: usize) -> u32 {
    let mut pos = 0;
    color.palettesize = chunkLength / 3;
    
    if color.palettesize == 0 || color.palettesize > 256 {
        return 38;
    }
    
    lodepng_color_mode_alloc_palette(color);
    
    if color.palette.is_none() && color.palettesize != 0 {
        color.palettesize = 0;
        return 83;
    }
    
    if let Some(palette) = &mut color.palette {
        for i in 0..color.palettesize {
            palette[4 * i + 0] = data[pos];
            pos += 1;
            palette[4 * i + 1] = data[pos];
            pos += 1;
            palette[4 * i + 2] = data[pos];
            pos += 1;
            palette[4 * i + 3] = LCT_MAX_OCTET_VALUE;
        }
    }
    
    0
}
pub fn readChunk_tIME(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    if chunkLength != 7 {
        return 73;
    }
    info.time_defined = 1;
    info.time.year = (256u32 * data[0] as u32) + data[1] as u32;
    info.time.month = data[2] as u32;
    info.time.day = data[3] as u32;
    info.time.hour = data[4] as u32;
    info.time.minute = data[5] as u32;
    info.time.second = data[6] as u32;
    0
}
pub fn helper_readChunk_sBIT_1(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize, bitdepth: u32) -> Option<u32> {
    if chunkLength != 4 {
        return Some(114);
    }
    if data[0] == 0 || data[1] == 0 || data[2] == 0 || data[3] == 0 {
        return Some(115);
    }
    if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth || u32::from(data[2]) > bitdepth || u32::from(data[3]) > bitdepth {
        return Some(115);
    }
    info.sbit_defined = 1;
    info.sbit_r = data[0] as u32;
    info.sbit_g = data[1] as u32;
    info.sbit_b = data[2] as u32;
    info.sbit_a = data[3] as u32;
    None
}
pub fn readChunk_sBIT(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> Option<u32> {
    let bitdepth = match info.color.colortype {
        LodePNGColorType::LCT_PALETTE => 8,
        _ => info.color.bitdepth,
    };

    match info.color.colortype {
        LodePNGColorType::LCT_GREY => {
            if chunkLength != 1 {
                return Some(114);
            }
            if data[0] == 0 || u32::from(data[0]) > bitdepth {
                return Some(115);
            }
            info.sbit_defined = 1;
            let value = data[0] as u32;
            info.sbit_r = value;
            info.sbit_g = value;
            info.sbit_b = value;
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_PALETTE => {
            if chunkLength != 3 {
                return Some(114);
            }
            if data[0] == 0 || data[1] == 0 || data[2] == 0 {
                return Some(115);
            }
            if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth || u32::from(data[2]) > bitdepth {
                return Some(115);
            }
            info.sbit_defined = 1;
            info.sbit_r = data[0] as u32;
            info.sbit_g = data[1] as u32;
            info.sbit_b = data[2] as u32;
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if chunkLength != 2 {
                return Some(114);
            }
            if data[0] == 0 || data[1] == 0 {
                return Some(115);
            }
            if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth {
                return Some(115);
            }
            info.sbit_defined = 1;
            let value = data[0] as u32;
            info.sbit_r = value;
            info.sbit_g = value;
            info.sbit_b = value;
            info.sbit_a = data[1] as u32;
        }
        LodePNGColorType::LCT_RGBA => {
            if let Some(err) = helper_readChunk_sBIT_1(info, data, chunkLength, bitdepth) {
                return Some(err);
            }
        }
    }

    None
}
pub fn lodepng_crc32(data: Option<&[u8]>, length: usize) -> u32 {
    let data = match data {
        Some(d) => d,
        None => return 0,
    };

    let mut r = 0xffffffffu32;
    let table = LODEPNG_CRC32_TABLE.lock().unwrap();

    for i in 0..length {
        r = table[((r ^ data[i] as u32) & 0xffu32) as usize] ^ (r >> 8u32);
    }

    r ^ 0xffffffffu32
}
pub fn lodepng_chunk_check_crc(chunk: Option<&[u8]>) -> u32 {
    let chunk = match chunk {
        Some(c) => c,
        None => return 1, // Invalid chunk (NULL equivalent)
    };

    let length = lodepng_chunk_length(Some(chunk)) as usize;
    if chunk.len() < length + 12 {
        return 1; // Invalid chunk length
    }

    let crc = lodepng_read32bitInt(&chunk[length + 8..length + 12]);
    let checksum = lodepng_crc32(Some(&chunk[4..length + 8]), length + 4);

    if crc != checksum {
        1
    } else {
        0
    }
}
pub fn readChunk_bKGD(info: &mut LodePNGInfo, data: &[u8], chunkLength: usize) -> u32 {
    match info.color.colortype {
        LodePNGColorType::LCT_PALETTE => {
            if chunkLength != 1 {
                return 43;
            }
            if data[0] as usize >= info.color.palettesize {
                return 103;
            }
            info.background_defined = 1;
            let val = data[0] as u32;
            info.background_r = val;
            info.background_g = val;
            info.background_b = val;
        }
        LodePNGColorType::LCT_GREY | LodePNGColorType::LCT_GREY_ALPHA => {
            if chunkLength != 2 {
                return 44;
            }
            info.background_defined = 1;
            let val = (256u32 * data[0] as u32) + data[1] as u32;
            info.background_r = val;
            info.background_g = val;
            info.background_b = val;
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA => {
            if chunkLength != 6 {
                return 45;
            }
            info.background_defined = 1;
            info.background_r = (256u32 * data[0] as u32) + data[1] as u32;
            info.background_g = (256u32 * data[2] as u32) + data[3] as u32;
            info.background_b = (256u32 * data[4] as u32) + data[5] as u32;
        }
        _ => {}
    }
    0
}

pub fn lodepng_chunk_type_equals(chunk: Option<&[u8]>, type_: Option<&CStr>) -> u8 {
    // Check if either input is None (NULL in C)
    if chunk.is_none() || type_.is_none() {
        return 0;
    }
    let chunk = chunk.unwrap();
    let type_ = type_.unwrap();

    // Check length using the provided lodepng_strlen function
    if lodepng_strlen(Some(type_)) != 4 {
        return 0;
    }

    // Get the type bytes (excluding NUL terminator)
    let type_bytes = type_.to_bytes();
    if type_bytes.len() < 4 {
        return 0;
    }

    // Check if chunk has enough bytes (needs at least 8 bytes: 4 for type)
    if chunk.len() < 8 {
        return 0;
    }

    // Compare each byte
    ((chunk[4] == type_bytes[0]) && 
     (chunk[5] == type_bytes[1]) && 
     (chunk[6] == type_bytes[2]) && 
     (chunk[7] == type_bytes[3])) as u8
}
pub fn helper_decodeGeneric_2(
    IEND_ref: &mut u8,
    chunk_idx_ref: &mut u32,
    idatsize_ref: &mut usize,
    unknown_ref: &mut u32,
    critical_pos_ref: &mut u32,
    state: &mut LodePNGState,
    in_data: &[u8],
    insize: usize,
    chunk: &[u8],
    idat: &mut [u8],
    idat_idx: usize,
) {
    let mut IEND = *IEND_ref;
    let mut chunk_idx = *chunk_idx_ref;
    let mut idatsize = *idatsize_ref;
    let mut unknown = *unknown_ref;
    let mut critical_pos = *critical_pos_ref;

    let pos = match chunk.get(chunk_idx as usize..) {
        Some(slice) => (slice.as_ptr() as usize - in_data.as_ptr() as usize),
        None => {
            if state.decoder.ignore_end == 0 {
                state.error = 30;
            }
            return;
        }
    };

    if pos + 12 > insize {
        if state.decoder.ignore_end == 0 {
            state.error = 30;
        }
        return;
    }

    let chunkLength = lodepng_chunk_length(Some(chunk)) as usize;
    if chunkLength > 2147483647 {
        if state.decoder.ignore_end == 0 {
            state.error = 63;
        }
        return;
    }

    if (pos + chunkLength + 12 > insize) || (pos + chunkLength + 12 < pos) {
        state.error = 64;
        return;
    }

    let data = match lodepng_chunk_data_const(Some(chunk)) {
        Some(d) => d,
        None => {
            state.error = 30;
            return;
        }
    };

    unknown = 0;

    if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"IDAT\0").unwrap())) != 0 {
        helper_helper_decodeGeneric_2_1(
            &mut idatsize,
            &mut critical_pos,
            state,
            insize,
            idat,
            idat_idx,
            chunkLength,
            data,
        );
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"IEND\0").unwrap())) != 0 {
        IEND = 1;
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"PLTE\0").unwrap())) != 0 {
        state.error = readChunk_PLTE(&mut state.info_png.color, data, chunkLength);
        if state.error != 0 {
            return;
        }
        critical_pos = 2;
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tRNS\0").unwrap())) != 0 {
        state.error = readChunk_tRNS(&mut state.info_png.color, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"bKGD\0").unwrap())) != 0 {
        state.error = readChunk_bKGD(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tEXt\0").unwrap())) != 0 {
        if state.decoder.read_text_chunks != 0 {
            state.error = readChunk_tEXt(&mut state.info_png, data, chunkLength);
            if state.error != 0 {
                return;
            }
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"zTXt\0").unwrap())) != 0 {
        if state.decoder.read_text_chunks != 0 {
            state.error = readChunk_zTXt(&mut state.info_png, &state.decoder, data, chunkLength);
            if state.error != 0 {
                return;
            }
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"iTXt\0").unwrap())) != 0 {
        if state.decoder.read_text_chunks != 0 {
            state.error = readChunk_iTXt(&mut state.info_png, &state.decoder, data, chunkLength);
            if state.error != 0 {
                return;
            }
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tIME\0").unwrap())) != 0 {
        state.error = readChunk_tIME(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"pHYs\0").unwrap())) != 0 {
        state.error = readChunk_pHYs(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"gAMA\0").unwrap())) != 0 {
        state.error = readChunk_gAMA(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"cHRM\0").unwrap())) != 0 {
        state.error = readChunk_cHRM(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"sRGB\0").unwrap())) != 0 {
        state.error = readChunk_sRGB(&mut state.info_png, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"iCCP\0").unwrap())) != 0 {
        state.error = readChunk_iCCP(&mut state.info_png, &state.decoder, data, chunkLength);
        if state.error != 0 {
            return;
        }
    } else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"sBIT\0").unwrap())) != 0 {
        state.error = match readChunk_sBIT(&mut state.info_png, data, chunkLength) {
            Some(err) => err,
            None => 0,
        };
        if state.error != 0 {
            return;
        }
    } else {
        if state.decoder.ignore_critical == 0 && !lodepng_chunk_ancillary(Some(chunk)) {
            state.error = 69;
            return;
        }
        unknown = 1;
        if state.decoder.remember_unknown_chunks != 0 {
            // Create temporary raw pointer for the chunk append operation
            let mut temp_ptr = state.info_png.unknown_chunks_data[critical_pos as usize - 1]
                .as_mut()
                .map(|v| v.as_mut_ptr());
            let mut temp_size = state.info_png.unknown_chunks_size[critical_pos as usize - 1];
            
            state.error = lodepng_chunk_append(
                &mut temp_ptr,
                &mut temp_size,
                Some(chunk),
            );
            
            if state.error != 0 {
                return;
            }
        }
    }

    if state.decoder.ignore_crc == 0 && unknown == 0 {
        if lodepng_chunk_check_crc(Some(chunk)) != 0 {
            state.error = 57;
            return;
        }
    }

    if IEND == 0 {
        chunk_idx = lodepng_chunk_next_const(Some(chunk), Some(&in_data[insize..])).map_or(0, |c| {
            (c.as_ptr() as usize - in_data.as_ptr() as usize) as u32
        });
    }

    *IEND_ref = IEND;
    *chunk_idx_ref = chunk_idx;
    *idatsize_ref = idatsize;
    *unknown_ref = unknown;
    *critical_pos_ref = critical_pos;
}
pub fn getNumColorChannels(colortype: LodePNGColorType) -> u8 {
    match colortype {
        LodePNGColorType::LCT_GREY => 1,
        LodePNGColorType::LCT_RGB => 3,
        LodePNGColorType::LCT_PALETTE => 1,
        LodePNGColorType::LCT_GREY_ALPHA => 2,
        LodePNGColorType::LCT_RGBA => 4,
        _ => 0, // Handles LCT_MAX_OCTET_VALUE and any other unexpected values
    }
}
pub fn lodepng_get_bpp_lct(colortype: LodePNGColorType, bitdepth: u8) -> u8 {
    getNumColorChannels(colortype) * bitdepth
}
pub fn lodepng_get_bpp(info: &LodePNGColorMode) -> u8 {
    lodepng_get_bpp_lct(info.colortype, info.bitdepth as u8)
}
pub fn helper_decodeGeneric_1(
    expected_size_ref: &mut usize,
    w: &mut u32,
    h: &mut u32,
    state: &mut LodePNGState,
    idat: &[u8],
    idatsize: usize,
    scanlines: &mut Option<Vec<u8>>,
    scanlines_size: &mut usize,
) {
    let mut expected_size = *expected_size_ref;
    
    if state.info_png.interlace_method == 0 {
        let bpp = lodepng_get_bpp(&state.info_png.color) as u32;
        expected_size = lodepng_get_raw_size_idat(*w, *h, bpp);
    } else {
        let bpp = lodepng_get_bpp(&state.info_png.color) as u32;
        expected_size = 0;
        expected_size += lodepng_get_raw_size_idat(((*w) + 7) >> 3, ((*h) + 7) >> 3, bpp);
        if (*w) > 4 {
            expected_size += lodepng_get_raw_size_idat(((*w) + 3) >> 3, ((*h) + 7) >> 3, bpp);
        }
        expected_size += lodepng_get_raw_size_idat(((*w) + 3) >> 2, ((*h) + 3) >> 3, bpp);
        if (*w) > 2 {
            expected_size += lodepng_get_raw_size_idat(((*w) + 1) >> 2, ((*h) + 3) >> 2, bpp);
        }
        expected_size += lodepng_get_raw_size_idat(((*w) + 1) >> 1, ((*h) + 1) >> 2, bpp);
        if (*w) > 1 {
            expected_size += lodepng_get_raw_size_idat(((*w) + 0) >> 1, ((*h) + 1) >> 1, bpp);
        }
        expected_size += lodepng_get_raw_size_idat(*w, ((*h) + 0) >> 1, bpp);
    }
    
    state.error = zlib_decompress(
        scanlines,
        scanlines_size,
        expected_size,
        idat,
        idatsize,
        &state.decoder.zlibsettings,
    );
    
    *expected_size_ref = expected_size;
}
pub fn lodepng_pixel_overflow(w: usize, h: usize, pngcolor: &LodePNGColorMode, rawcolor: &LodePNGColorMode) -> bool {
    let bpp = std::cmp::max(lodepng_get_bpp(pngcolor), lodepng_get_bpp(rawcolor)) as usize;
    let mut numpixels = 0;
    let mut total = 0;
    let mut line = 0;

    if lodepng_mulofl(w, h, &mut numpixels) {
        return true;
    }
    if lodepng_mulofl(numpixels, 8, &mut total) {
        return true;
    }
    if lodepng_mulofl(w / 8, bpp, &mut line) {
        return true;
    }
    let mut temp_line = Some(line);
    if lodepng_addofl(line, (((w & 7) * bpp) + 7) / 8, &mut temp_line) {
        return true;
    }
    line = temp_line.unwrap();
    if lodepng_addofl(line, 5, &mut temp_line) {
        return true;
    }
    line = temp_line.unwrap();
    if lodepng_mulofl(line, h, &mut total) {
        return true;
    }
    false
}
pub fn lodepng_get_raw_size_lct(w: u32, h: u32, colortype: LodePNGColorType, bitdepth: u8) -> usize {
    let bpp = lodepng_get_bpp_lct(colortype, bitdepth) as usize;
    let n = (w as usize) * (h as usize);
    ((n / 8) * bpp) + ((((n & 7) * bpp) + 7) / 8)
}
pub fn lodepng_get_raw_size(w: u32, h: u32, color: &LodePNGColorMode) -> usize {
    lodepng_get_raw_size_lct(w, h, color.colortype, color.bitdepth as u8)
}
pub fn lodepng_palette_clear(info: &mut LodePNGColorMode) {
    // In Rust, we can simply set the palette to None, which will handle any necessary cleanup
    info.palette = None;
    info.palettesize = 0;
}
pub fn lodepng_color_mode_cleanup(info: &mut LodePNGColorMode) {
    lodepng_palette_clear(info);
}
pub fn LodePNGUnknownChunks_cleanup(info: &mut LodePNGInfo) {
    for i in 0..3 {
        info.unknown_chunks_data[i] = None;
    }
}
pub fn LodePNGIText_cleanup(info: &mut LodePNGInfo) {
    if let Some(itext_keys) = &mut info.itext_keys {
        for key in itext_keys.iter_mut() {
            let mut ptr = Some(key.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut ptr);
        }
    }
    if let Some(itext_langtags) = &mut info.itext_langtags {
        for langtag in itext_langtags.iter_mut() {
            let mut ptr = Some(langtag.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut ptr);
        }
    }
    if let Some(itext_transkeys) = &mut info.itext_transkeys {
        for transkey in itext_transkeys.iter_mut() {
            let mut ptr = Some(transkey.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut ptr);
        }
    }
    if let Some(itext_strings) = &mut info.itext_strings {
        for string in itext_strings.iter_mut() {
            let mut ptr = Some(string.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut ptr);
        }
    }

    info.itext_keys = None;
    info.itext_langtags = None;
    info.itext_transkeys = None;
    info.itext_strings = None;
}
pub fn LodePNGText_cleanup(info: &mut LodePNGInfo) {
    if let Some(keys) = &mut info.text_keys {
        for key in keys.iter_mut() {
            let mut key_ptr = Some(key.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut key_ptr);
        }
    }
    if let Some(strings) = &mut info.text_strings {
        for string in strings.iter_mut() {
            let mut string_ptr = Some(string.as_mut_ptr() as *mut std::ffi::c_void);
            string_cleanup(&mut string_ptr);
        }
    }

    info.text_keys = None;
    info.text_strings = None;
}
pub fn lodepng_info_cleanup(info: &mut LodePNGInfo) {
    lodepng_color_mode_cleanup(&mut info.color);
    LodePNGText_cleanup(info);
    LodePNGIText_cleanup(info);
    lodepng_clear_icc(info);
    LodePNGUnknownChunks_cleanup(info);
}
pub fn LodePNGUnknownChunks_init(info: &mut LodePNGInfo) {
    for i in 0..3 {
        info.unknown_chunks_data[i] = None;
    }

    for i in 0..3 {
        info.unknown_chunks_size[i] = 0;
    }
}
pub fn LodePNGText_init(info: &mut LodePNGInfo) {
    info.text_num = 0;
    info.text_keys = None;
    info.text_strings = None;
}
pub fn LodePNGIText_init(info: &mut LodePNGInfo) {
    info.itext_num = 0;
    info.itext_keys = None;
    info.itext_langtags = None;
    info.itext_transkeys = None;
    info.itext_strings = None;
}
pub fn lodepng_color_mode_init(info: &mut LodePNGColorMode) {
    info.key_defined = 0;
    info.key_r = 0;
    info.key_g = 0;
    info.key_b = 0;
    info.colortype = LodePNGColorType::LCT_RGBA;
    info.bitdepth = 8;
    info.palette = None;
    info.palettesize = 0;
}
pub fn lodepng_info_init(info: &mut LodePNGInfo) {
    lodepng_color_mode_init(&mut info.color);
    info.interlace_method = 0;
    info.compression_method = 0;
    info.filter_method = 0;
    info.background_defined = 0;
    info.background_r = 0;
    info.background_g = 0;
    info.background_b = 0;
    LodePNGText_init(info);
    LodePNGIText_init(info);
    info.time_defined = 0;
    info.phys_defined = 0;
    info.gama_defined = 0;
    info.chrm_defined = 0;
    info.srgb_defined = 0;
    info.iccp_defined = 0;
    info.iccp_name = None;
    info.iccp_profile = None;
    info.sbit_defined = 0;
    info.sbit_r = 0;
    info.sbit_g = 0;
    info.sbit_b = 0;
    info.sbit_a = 0;
    LodePNGUnknownChunks_init(info);
}
pub fn checkColorValidity(colortype: LodePNGColorType, bd: u32) -> u32 {
    match colortype {
        LodePNGColorType::LCT_GREY => {
            if !(bd == 1 || bd == 2 || bd == 4 || bd == 8 || bd == 16) {
                return 37;
            }
        }
        LodePNGColorType::LCT_RGB => {
            if !(bd == 8 || bd == 16) {
                return 37;
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            if !(bd == 1 || bd == 2 || bd == 4 || bd == 8) {
                return 37;
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if !(bd == 8 || bd == 16) {
                return 37;
            }
        }
        LodePNGColorType::LCT_RGBA => {
            if !(bd == 8 || bd == 16) {
                return 37;
            }
        }
        _ => return 31,
    }
    0
}

pub fn lodepng_inspect(
    w: Option<&mut u32>,
    h: Option<&mut u32>,
    state: &mut LodePNGState,
    in_data: Option<&[u8]>,
    insize: usize,
) -> u32 {
    // Check for NULL input or zero size
    if in_data.is_none() || insize == 0 {
        state.error = 48;
        return 48;
    }
    let in_data = in_data.unwrap();

    // Check minimum size requirement
    if insize < 33 {
        state.error = 27;
        return 27;
    }

    // Check PNG signature
    if in_data[0..8] != [137, 80, 78, 71, 13, 10, 26, 10] {
        state.error = 28;
        return 28;
    }

    let info = &mut state.info_png;
    lodepng_info_cleanup(info);
    lodepng_info_init(info);

    // Check IHDR chunk length
    if lodepng_chunk_length(Some(&in_data[8..])) != 13 {
        state.error = 94;
        return 94;
    }

    // Check IHDR chunk type
    let ihdr = CStr::from_bytes_with_nul(b"IHDR\0").unwrap();
    if lodepng_chunk_type_equals(Some(&in_data[8..]), Some(ihdr)) == 0 {
        state.error = 29;
        return 29;
    }

    let width = lodepng_read32bitInt(&in_data[16..20]);
    let height = lodepng_read32bitInt(&in_data[20..24]);

    // Write width/height to output parameters if provided
    if let Some(w_ptr) = w {
        *w_ptr = width;
    }
    if let Some(h_ptr) = h {
        *h_ptr = height;
    }

    // Set PNG info fields
    info.color.bitdepth = in_data[24] as u32;
    info.color.colortype = unsafe { std::mem::transmute(in_data[25]) };
    info.compression_method = in_data[26] as u32;
    info.filter_method = in_data[27] as u32;
    info.interlace_method = in_data[28] as u32;

    // Validate dimensions
    if width == 0 || height == 0 {
        state.error = 93;
        return 93;
    }

    // Validate color settings
    state.error = checkColorValidity(info.color.colortype, info.color.bitdepth);
    if state.error != 0 {
        return state.error;
    }

    // Validate compression method
    if info.compression_method != 0 {
        state.error = 32;
        return 32;
    }

    // Validate filter method
    if info.filter_method != 0 {
        state.error = 33;
        return 33;
    }

    // Validate interlace method
    if info.interlace_method > 1 {
        state.error = 34;
        return 34;
    }

    // Check CRC if not ignored
    if state.decoder.ignore_crc == 0 {
        let crc = lodepng_read32bitInt(&in_data[29..33]);
        let checksum = lodepng_crc32(Some(&in_data[12..29]), 17);
        if crc != checksum {
            state.error = 57;
            return 57;
        }
    }

    state.error
}
pub fn helper_helper_unfilterScanline_1_1(
    i_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    bytewidth: usize,
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = 0;

    // Process initial bytewidth bytes
    for idx in 0..bytewidth {
        recon[idx] = scanline[idx].wrapping_add(precon[idx] >> 1);
    }

    i = bytewidth; // Update i after initial processing

    // Process based on bytewidth
    if bytewidth >= 4 {
        helper_helper_helper_unfilterScanline_1_1_2(&mut i, &mut j, recon, scanline, precon, length);
    } else if bytewidth >= 3 {
        helper_helper_helper_unfilterScanline_1_1_1(&mut i, &mut j, recon, scanline, precon, length);
    } else if bytewidth >= 2 {
        while i + 1 < length {
            let s0 = scanline[i];
            let s1 = scanline[i + 1];
            let r0 = recon[j];
            let r1 = recon[j + 1];
            let p0 = precon[i];
            let p1 = precon[i + 1];

            recon[i] = s0.wrapping_add((r0.wrapping_add(p0) >> 1));
            recon[i + 1] = s1.wrapping_add((r1.wrapping_add(p1) >> 1));

            i += 2;
            j += 2;
        }
    }

    // Process remaining bytes
    while i < length {
        recon[i] = scanline[i].wrapping_add((recon[j].wrapping_add(precon[i]) >> 1));
        i += 1;
        j += 1;
    }

    *i_ref = i;
}
pub fn helper_unfilterScanline_1(
    i_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: Option<&[u8]>,
    bytewidth: usize,
    length: usize,
) {
    let mut i = *i_ref;
    
    if let Some(precon) = precon {
        helper_helper_unfilterScanline_1_1(&mut i, recon, scanline, precon, bytewidth, length);
    } else {
        // Copy first bytewidth bytes directly
        recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
        
        // Process remaining bytes
        let mut j = 0;
        for idx in bytewidth..length {
            recon[idx] = scanline[idx].wrapping_add(recon[j] >> 1);
            j += 1;
        }
        
        i = length;
    }
    
    *i_ref = i;
}
pub fn helper_helper_helper_unfilterScanline_2_1_1(
    i_ref: &mut usize,
    j_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    
    while i + 1 < length {
        let s0 = scanline[i];
        let s1 = scanline[i + 1];
        let r0 = recon[j];
        let r1 = recon[j + 1];
        let p0 = precon[i];
        let p1 = precon[i + 1];
        let q0 = precon[j];
        let q1 = precon[j + 1];
        
        recon[i] = s0.wrapping_add(paethPredictor(r0 as i16, p0 as i16, q0 as i16));
        recon[i + 1] = s1.wrapping_add(paethPredictor(r1 as i16, p1 as i16, q1 as i16));
        
        i += 2;
        j += 2;
    }
    
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_helper_unfilterScanline_2_1_2(
    i_ref: &mut usize,
    j_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    
    while i + 2 < length {
        let s0 = scanline[i];
        let s1 = scanline[i + 1];
        let s2 = scanline[i + 2];
        
        let r0 = recon[j] as i16;
        let r1 = recon[j + 1] as i16;
        let r2 = recon[j + 2] as i16;
        
        let p0 = precon[i] as i16;
        let p1 = precon[i + 1] as i16;
        let p2 = precon[i + 2] as i16;
        
        let q0 = precon[j] as i16;
        let q1 = precon[j + 1] as i16;
        let q2 = precon[j + 2] as i16;
        
        recon[i] = s0.wrapping_add(paethPredictor(r0, p0, q0));
        recon[i + 1] = s1.wrapping_add(paethPredictor(r1, p1, q1));
        recon[i + 2] = s2.wrapping_add(paethPredictor(r2, p2, q2));
        
        i += 3;
        j += 3;
    }
    
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_helper_unfilterScanline_2_1_3(
    i_ref: &mut usize,
    j_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    
    while i + 3 < length {
        let s0 = scanline[i];
        let s1 = scanline[i + 1];
        let s2 = scanline[i + 2];
        let s3 = scanline[i + 3];
        
        let r0 = recon[j] as i16;
        let r1 = recon[j + 1] as i16;
        let r2 = recon[j + 2] as i16;
        let r3 = recon[j + 3] as i16;
        
        let p0 = precon[i] as i16;
        let p1 = precon[i + 1] as i16;
        let p2 = precon[i + 2] as i16;
        let p3 = precon[i + 3] as i16;
        
        let q0 = precon[j] as i16;
        let q1 = precon[j + 1] as i16;
        let q2 = precon[j + 2] as i16;
        let q3 = precon[j + 3] as i16;
        
        recon[i] = s0.wrapping_add(paethPredictor(r0, p0, q0));
        recon[i + 1] = s1.wrapping_add(paethPredictor(r1, p1, q1));
        recon[i + 2] = s2.wrapping_add(paethPredictor(r2, p2, q2));
        recon[i + 3] = s3.wrapping_add(paethPredictor(r3, p3, q3));
        
        i += 4;
        j += 4;
    }
    
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_unfilterScanline_2_1(
    i_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: &[u8],
    bytewidth: usize,
    length: usize,
) {
    let mut i = *i_ref;
    let mut j = 0;
    
    // First part: simple addition for the first 'bytewidth' bytes
    for idx in 0..bytewidth {
        recon[idx] = scanline[idx].wrapping_add(precon[idx]);
    }
    i = bytewidth;

    // Dispatch to specialized functions based on bytewidth
    if bytewidth >= 4 {
        helper_helper_helper_unfilterScanline_2_1_3(&mut i, &mut j, recon, scanline, precon, length);
    } else if bytewidth >= 3 {
        helper_helper_helper_unfilterScanline_2_1_2(&mut i, &mut j, recon, scanline, precon, length);
    } else if bytewidth >= 2 {
        helper_helper_helper_unfilterScanline_2_1_1(&mut i, &mut j, recon, scanline, precon, length);
    }

    // Remaining bytes using paethPredictor
    while i < length {
        let recon_prev = recon[i - bytewidth];
        let precon_curr = precon[i];
        let precon_prev = precon[j];
        
        recon[i] = scanline[i].wrapping_add(
            paethPredictor(recon_prev as i16, precon_curr as i16, precon_prev as i16)
        );
        
        i += 1;
        j += 1;
    }

    *i_ref = i;
}
pub fn helper_unfilterScanline_2(
    i_ref: &mut usize,
    recon: &mut [u8],
    scanline: &[u8],
    precon: Option<&[u8]>,
    bytewidth: usize,
    length: usize,
) {
    let mut i = *i_ref;
    
    if let Some(precon) = precon {
        helper_helper_unfilterScanline_2_1(&mut i, recon, scanline, precon, bytewidth, length);
    } else {
        // First bytewidth bytes are copied directly
        recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
        
        // Remaining bytes use previous filtered bytes
        for idx in bytewidth..length {
            recon[idx] = scanline[idx].wrapping_add(recon[idx - bytewidth]);
        }
        
        i = length;
    }
    
    *i_ref = i;
}
pub fn unfilterScanline(
    recon: &mut [u8],
    scanline: &[u8],
    precon: Option<&[u8]>,
    bytewidth: usize,
    filterType: u8,
    length: usize,
) -> u32 {
    match filterType {
        0 => {
            recon[..length].copy_from_slice(&scanline[..length]);
            0
        }
        1 => {
            // Copy first bytewidth bytes directly
            recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
            
            // Process remaining bytes
            let mut j = 0;
            for i in bytewidth..length {
                recon[i] = scanline[i].wrapping_add(recon[j]);
                j += 1;
            }
            0
        }
        2 => {
            if let Some(precon) = precon {
                for i in 0..length {
                    recon[i] = scanline[i].wrapping_add(precon[i]);
                }
            } else {
                recon[..length].copy_from_slice(&scanline[..length]);
            }
            0
        }
        3 => {
            let mut i = 0;
            helper_unfilterScanline_1(&mut i, recon, scanline, precon, bytewidth, length);
            0
        }
        4 => {
            let mut i = 0;
            helper_unfilterScanline_2(&mut i, recon, scanline, precon, bytewidth, length);
            0
        }
        _ => 36,
    }
}
pub fn unfilter(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    bpp: u32,
) -> u32 {
    let mut prevline_start = 0;
    let bytewidth = (bpp + 7u32) as usize / 8;
    let linebytes = lodepng_get_raw_size_idat(w, 1, bpp) - 1;

    for y in 0..h {
        let outindex = linebytes * y as usize;
        let inindex = (1 + linebytes) * y as usize;
        let filterType = in_data[inindex];

        // Split the output buffer into two parts at outindex
        let (left, right) = out.split_at_mut(outindex);
        
        let out_slice = &mut right[..linebytes];
        let in_slice = &in_data[inindex + 1..inindex + 1 + linebytes];
        
        let prevline = if y == 0 {
            Option::None
        } else {
            Some(&left[prevline_start..prevline_start + linebytes])
        };
        
        let error = unfilterScanline(
            out_slice,
            in_slice,
            prevline,
            bytewidth,
            filterType,
            linebytes,
        );
        
        if error != 0 {
            return error;
        }

        prevline_start = outindex;
    }

    0
}
pub fn removePaddingBits(out: &mut [u8], in_: &[u8], olinebits: usize, ilinebits: usize, h: usize) {
    let diff = ilinebits - olinebits;
    let mut ibp = 0;
    let mut obp = 0;
    
    for _y in 0..h {
        for _x in 0..olinebits {
            let bit = readBitFromReversedStream(&mut ibp, in_);
            setBitOfReversedStream(&mut obp, out, bit);
        }
        
        ibp += diff;
    }
}
pub fn helper_postProcessScanlines_1(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    bpp: u32,
) -> u32 {
    if bpp < 8 && (w * bpp) != (((w * bpp) + 7) / 8) * 8 {
        let mut temp_in = in_data.to_vec(); // Create a mutable copy for unfilter
        let error = unfilter(&mut temp_in, in_data, w, h, bpp);
        if error != 0 {
            return error;
        }

        removePaddingBits(
            out,
            &temp_in,
            (w * bpp) as usize,
            (((w * bpp) + 7) / 8 * 8) as usize,
            h as usize,
        );
    } else {
        let error = unfilter(out, in_data, w, h, bpp);
        if error != 0 {
            return error;
        }
    }
    
    0
}
pub fn helper_Adam7_deinterlace_1(
    i_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    bpp: u32,
    passw: [u32; 7],
    passh: [u32; 7],
    passstart: [usize; 8],
) {
    let mut i = *i_ref;
    for i in 0..7 {
        let ilinebits = bpp * passw[i as usize];
        let olinebits = bpp * w;
        for y in 0..passh[i as usize] {
            for x in 0..passw[i as usize] {
                let mut ibp = (8 * passstart[i as usize]) + ((y * ilinebits) + (x * bpp)) as usize;
                let mut obp = ((ADAM7_IY[i as usize] + (y as u32 * ADAM7_DY[i as usize])) * olinebits
                    + (ADAM7_IX[i as usize] + (x as u32 * ADAM7_DX[i as usize])) * bpp) as usize;
                for _ in 0..bpp {
                    let bit = readBitFromReversedStream(&mut ibp, in_data);
                    setBitOfReversedStream(&mut obp, out, bit);
                }
            }
        }
    }
    *i_ref = 7;
}
pub fn Adam7_getpassvalues(
    passw: &mut [u32; 7],
    passh: &mut [u32; 7],
    filter_passstart: &mut [usize; 8],
    padded_passstart: &mut [usize; 8],
    passstart: &mut [usize; 8],
    w: u32,
    h: u32,
    bpp: u32,
) {
    // Calculate passw and passh for each pass
    for i in 0..7 {
        passw[i] = ((w + ADAM7_DX[i]).saturating_sub(ADAM7_IX[i]).saturating_sub(1)) / ADAM7_DX[i];
        passh[i] = ((h + ADAM7_DY[i]).saturating_sub(ADAM7_IY[i]).saturating_sub(1)) / ADAM7_DY[i];
        
        // Zero out if either dimension is zero
        if passw[i] == 0 {
            passh[i] = 0;
        }
        if passh[i] == 0 {
            passw[i] = 0;
        }
    }

    // Initialize starts
    filter_passstart[0] = 0;
    padded_passstart[0] = 0;
    passstart[0] = 0;

    // Calculate cumulative starts
    for i in 0..7 {
        let active = if passw[i] != 0 && passh[i] != 0 { 1 } else { 0 };
        filter_passstart[i + 1] = filter_passstart[i] + 
            (passh[i] as usize).checked_mul(
                1 + ((passw[i] * bpp + 7) / 8) as usize
            ).unwrap_or(0) * active;
        
        padded_passstart[i + 1] = padded_passstart[i] + 
            (passh[i] as usize).checked_mul(
                ((passw[i] * bpp + 7) / 8) as usize
            ).unwrap_or(0);
        
        passstart[i + 1] = passstart[i] + 
            ((passh[i] * passw[i] * bpp + 7) / 8) as usize;
    }
}
pub fn Adam7_deinterlace(out: &mut [u8], in_data: &[u8], w: u32, h: u32, bpp: u32) {
    let mut passw = [0u32; 7];
    let mut passh = [0u32; 7];
    let mut filter_passstart = [0usize; 8];
    let mut padded_passstart = [0usize; 8];
    let mut passstart = [0usize; 8];
    
    Adam7_getpassvalues(
        &mut passw,
        &mut passh,
        &mut filter_passstart,
        &mut padded_passstart,
        &mut passstart,
        w,
        h,
        bpp,
    );

    if bpp >= 8 {
        for i in 0..7 {
            let bytewidth = bpp / 8;
            for y in 0..passh[i] {
                for x in 0..passw[i] {
                    let pixelinstart = passstart[i] + (((y * passw[i]) + x) * bytewidth) as usize;
                    let pixeloutstart = ((ADAM7_IY[i] as u64 + (y as u64 * ADAM7_DY[i] as u64)) * w as u64 
                                      + ADAM7_IX[i] as u64 + (x as u64 * ADAM7_DX[i] as u64)) * bytewidth as u64;
                    
                    for b in 0..bytewidth {
                        out[(pixeloutstart + b as u64) as usize] = in_data[pixelinstart + b as usize];
                    }
                }
            }
        }
    } else {
        let mut i = 0;
        helper_Adam7_deinterlace_1(&mut i, out, in_data, w, bpp, passw, passh, passstart);
    }
}
pub fn helper_postProcessScanlines_2(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    bpp: u32,
) -> u32 {
    let mut passw = [0u32; 7];
    let mut passh = [0u32; 7];
    let mut filter_passstart = [0usize; 8];
    let mut padded_passstart = [0usize; 8];
    let mut passstart = [0usize; 8];

    Adam7_getpassvalues(
        &mut passw,
        &mut passh,
        &mut filter_passstart,
        &mut padded_passstart,
        &mut passstart,
        w,
        h,
        bpp,
    );

    for i in 0..7 {
        {
            let error = unfilter(
                &mut in_data[padded_passstart[i]..].to_vec(),
                &in_data[filter_passstart[i]..],
                passw[i],
                passh[i],
                bpp,
            );
            if error != 0 {
                return error;
            }
        }

        if bpp < 8 {
            removePaddingBits(
                &mut in_data[passstart[i]..].to_vec(),
                &in_data[padded_passstart[i]..],
                (passw[i] * bpp) as usize,
                (((passw[i] * bpp) + 7) / 8 * 8) as usize,
                passh[i] as usize,
            );
        }
    }

    Adam7_deinterlace(out, in_data, w, h, bpp);
    0
}
pub fn postProcessScanlines(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePNGInfo,
) -> u32 {
    let bpp = lodepng_get_bpp(&info_png.color) as u32;
    if bpp == 0 {
        return 31;
    }

    if info_png.interlace_method == 0 {
        helper_postProcessScanlines_1(out, in_data, w, h, bpp)
    } else {
        helper_postProcessScanlines_2(out, in_data, w, h, bpp)
    }
}
pub fn decodeGeneric(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    state: &mut LodePNGState,
    in_data: &[u8],
    insize: usize,
) {
    let mut IEND = 0u8;
    let mut chunk_idx = 0u32;
    let mut idat = Vec::new();
    let mut idat_idx = 0usize;
    let mut idatsize = 0usize;
    let mut scanlines = None;
    let mut scanlines_size = 0usize;
    let mut expected_size = 0usize;
    let mut outsize = 0usize;
    let mut unknown = 0u32;
    let mut critical_pos = 1u32;

    *out = None;
    *w = 0;
    *h = 0;

    state.error = lodepng_inspect(Some(w), Some(h), state, Some(in_data), insize);
    if state.error != 0 {
        return;
    }

    if lodepng_pixel_overflow(*w as usize, *h as usize, &state.info_png.color, &state.info_raw) {
        state.error = 92;
        return;
    }

    idat = vec![0u8; insize];
    if idat.is_empty() {
        state.error = 83;
        return;
    }

    chunk_idx = 33;

    while IEND == 0 && state.error == 0 {
        let current_chunk_idx = chunk_idx; // Create a local copy
        helper_decodeGeneric_2(
            &mut IEND,
            &mut chunk_idx,
            &mut idatsize,
            &mut unknown,
            &mut critical_pos,
            state,
            in_data,
            insize,
            &in_data[current_chunk_idx as usize..],
            &mut idat,
            idat_idx,
        );
    }

    if state.error == 0
        && state.info_png.color.colortype == LodePNGColorType::LCT_PALETTE
        && state.info_png.color.palette.is_none()
    {
        state.error = 106;
    }

    if state.error == 0 {
        helper_decodeGeneric_1(
            &mut expected_size,
            w,
            h,
            state,
            &idat,
            idatsize,
            &mut scanlines,
            &mut scanlines_size,
        );
    }

    if state.error == 0 && scanlines_size != expected_size {
        state.error = 91;
    }

    if state.error == 0 {
        outsize = lodepng_get_raw_size(*w, *h, &state.info_png.color);
        *out = Some(vec![0u8; outsize]);
        if out.is_none() {
            state.error = 83;
        }
    }

    if state.error == 0 {
        if let Some(out_data) = out.as_mut() {
            lodepng_memset(out_data, 0);
            state.error = postProcessScanlines(
                out_data,
                scanlines.as_ref().unwrap(),
                *w,
                *h,
                &state.info_png,
            );
        }
    }
}
pub fn lodepng_color_mode_copy(dest: &mut LodePNGColorMode, source: &LodePNGColorMode) -> u32 {
    // Clean up the destination first
    lodepng_color_mode_cleanup(dest);
    
    // Copy all fields except palette (which needs special handling)
    dest.colortype = source.colortype;
    dest.bitdepth = source.bitdepth;
    dest.palettesize = source.palettesize;
    dest.key_defined = source.key_defined;
    dest.key_r = source.key_r;
    dest.key_g = source.key_g;
    dest.key_b = source.key_b;
    
    // Handle palette copying
    if let Some(source_palette) = &source.palette {
        if source.palettesize > 0 {
            // Allocate new palette vector
            let mut new_palette = Vec::with_capacity(source.palettesize * 4);
            new_palette.extend_from_slice(source_palette);
            
            dest.palette = Some(new_palette);
        } else {
            dest.palette = None;
        }
    } else {
        dest.palette = None;
    }
    
    0 // Return success code
}
pub fn readBitsFromReversedStream(bitpointer: &mut usize, bitstream: &[u8], nbits: usize) -> u32 {
    let mut result = 0;
    for _ in 0..nbits {
        result <<= 1;
        result |= readBitFromReversedStream(bitpointer, bitstream) as u32;
    }
    result
}
pub fn helper_getPixelColorRGBA8_2(
    r: &mut u8,
    g: &mut u8,
    b: &mut u8,
    a: &mut u8,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
    if mode.bitdepth == 8 {
        *b = in_data[i];
        *g = *b;
        *r = *g;
        *a = if mode.key_defined != 0 && (*r == mode.key_r as u8) {
            0
        } else {
            255
        };
    } else if mode.bitdepth == 16 {
        *b = in_data[i * 2];
        *g = *b;
        *r = *g;
        let key = (256 * u32::from(in_data[i * 2])) + u32::from(in_data[i * 2 + 1]);
        *a = if mode.key_defined != 0 && (key == mode.key_r) {
            0
        } else {
            255
        };
    } else {
        let highest = (1u32 << mode.bitdepth) - 1;
        let mut j = i * mode.bitdepth as usize;
        let value = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
        *b = ((value * 255) / highest) as u8;
        *g = *b;
        *r = *g;
        *a = if mode.key_defined != 0 && (value == mode.key_r) {
            0
        } else {
            255
        };
    }
}
pub fn helper_getPixelColorRGBA8_1(
    r: &mut u8,
    g: &mut u8,
    b: &mut u8,
    a: &mut u8,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
    if mode.bitdepth == 8 {
        *r = in_data[i * 3];
        *g = in_data[i * 3 + 1];
        *b = in_data[i * 3 + 2];
        if mode.key_defined != 0 && *r == mode.key_r as u8 && *g == mode.key_g as u8 && *b == mode.key_b as u8 {
            *a = 0;
        } else {
            *a = LCT_MAX_OCTET_VALUE;
        }
    } else {
        *r = in_data[i * 6];
        *g = in_data[i * 6 + 2];
        *b = in_data[i * 6 + 4];
        if mode.key_defined != 0
            && (u32::from(*r) * 256 + u32::from(in_data[i * 6 + 1])) == mode.key_r
            && (u32::from(*g) * 256 + u32::from(in_data[i * 6 + 3])) == mode.key_g
            && (u32::from(*b) * 256 + u32::from(in_data[i * 6 + 5])) == mode.key_b
        {
            *a = 0;
        } else {
            *a = LCT_MAX_OCTET_VALUE;
        }
    }
}
pub fn getPixelColorRGBA8(
    r: &mut u8,
    g: &mut u8,
    b: &mut u8,
    a: &mut u8,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            helper_getPixelColorRGBA8_2(r, g, b, a, in_data, i, mode);
        }
        LodePNGColorType::LCT_RGB => {
            helper_getPixelColorRGBA8_1(r, g, b, a, in_data, i, mode);
        }
        LodePNGColorType::LCT_PALETTE => {
            let index = if mode.bitdepth == 8 {
                in_data[i] as u32
            } else {
                let mut j = i * mode.bitdepth as usize;
                readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize)
            };
            if let Some(palette) = &mode.palette {
                *r = palette[(index * 4) as usize];
                *g = palette[(index * 4 + 1) as usize];
                *b = palette[(index * 4 + 2) as usize];
                *a = palette[(index * 4 + 3) as usize];
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if mode.bitdepth == 8 {
                *r = in_data[i * 2];
                *g = *r;
                *b = *g;
                *a = in_data[i * 2 + 1];
            } else {
                *r = in_data[i * 4];
                *g = *r;
                *b = *g;
                *a = in_data[i * 4 + 2];
            }
        }
        LodePNGColorType::LCT_RGBA => {
            if mode.bitdepth == 8 {
                *r = in_data[i * 4];
                *g = in_data[i * 4 + 1];
                *b = in_data[i * 4 + 2];
                *a = in_data[i * 4 + 3];
            } else {
                *r = in_data[i * 8];
                *g = in_data[i * 8 + 2];
                *b = in_data[i * 8 + 4];
                *a = in_data[i * 8 + 6];
            }
        }
    }
}
pub fn helper_getPixelColorsRGBA8_1(
    buffer_idx_ref: &mut u32,
    i_ref: &mut usize,
    buffer: &mut [u8],
    numpixels: usize,
    in_data: &[u8],
    mode: &LodePNGColorMode,
    num_channels: usize,
) {
    let mut buffer_idx = *buffer_idx_ref;
    let mut i = *i_ref;

    if mode.bitdepth == 8 {
        for _ in 0..numpixels {
            lodepng_memcpy(&mut buffer[buffer_idx as usize..], &in_data[i * 3..i * 3 + 3]);
            buffer[3 + buffer_idx as usize] = 255;
            i += 1;
            buffer_idx += num_channels as u32;
        }

        if mode.key_defined != 0 {
            buffer_idx -= (numpixels * num_channels) as u32;
            i = 0;
            for _ in 0..numpixels {
                if buffer[0 + buffer_idx as usize] == mode.key_r as u8
                    && buffer[1 + buffer_idx as usize] == mode.key_g as u8
                    && buffer[2 + buffer_idx as usize] == mode.key_b as u8
                {
                    buffer[3 + buffer_idx as usize] = 0;
                }
                i += 1;
                buffer_idx += num_channels as u32;
            }
        }
    } else {
        for _ in 0..numpixels {
            buffer[0 + buffer_idx as usize] = in_data[i * 6 + 0];
            buffer[1 + buffer_idx as usize] = in_data[i * 6 + 2];
            buffer[2 + buffer_idx as usize] = in_data[i * 6 + 4];
            
            let key_match = mode.key_defined != 0
                && ((256 * in_data[i * 6 + 0] as u32 + in_data[i * 6 + 1] as u32) == mode.key_r)
                && ((256 * in_data[i * 6 + 2] as u32 + in_data[i * 6 + 3] as u32) == mode.key_g)
                && ((256 * in_data[i * 6 + 4] as u32 + in_data[i * 6 + 5] as u32) == mode.key_b);
            
            buffer[3 + buffer_idx as usize] = if key_match { 0 } else { 255 };
            
            i += 1;
            buffer_idx += num_channels as u32;
        }
    }

    *buffer_idx_ref = buffer_idx;
    *i_ref = i;
}
pub fn helper_getPixelColorsRGBA8_2(
    buffer_idx_ref: &mut u32,
    i_ref: &mut usize,
    buffer: &mut [u8],
    numpixels: usize,
    in_data: &[u8],
    mode: &LodePNGColorMode,
    num_channels: usize,
) {
    let mut buffer_idx = *buffer_idx_ref;
    let mut i = *i_ref;

    match mode.bitdepth {
        8 => {
            for _ in 0..numpixels {
                let val = in_data[i];
                buffer[buffer_idx as usize] = val;
                buffer[buffer_idx as usize + 1] = val;
                buffer[buffer_idx as usize + 2] = val;
                buffer[buffer_idx as usize + 3] = 255;
                i += 1;
                buffer_idx += num_channels as u32;
            }

            if mode.key_defined != 0 {
                buffer_idx -= (numpixels * num_channels) as u32;
                i = 0;
                for _ in 0..numpixels {
                    if buffer[buffer_idx as usize] == mode.key_r as u8 {
                        buffer[buffer_idx as usize + 3] = 0;
                    }
                    i += 1;
                    buffer_idx += num_channels as u32;
                }
            }
        }
        16 => {
            for _ in 0..numpixels {
                let val = in_data[i * 2];
                buffer[buffer_idx as usize] = val;
                buffer[buffer_idx as usize + 1] = val;
                buffer[buffer_idx as usize + 2] = val;
                let key_match = mode.key_defined != 0 && 
                    ((u32::from(in_data[i * 2]) * 256 + u32::from(in_data[i * 2 + 1])) == mode.key_r);
                buffer[buffer_idx as usize + 3] = if key_match { 0 } else { 255 };
                i += 1;
                buffer_idx += num_channels as u32;
            }
        }
        _ => {
            let highest = (1u32 << mode.bitdepth) - 1;
            let mut j = 0;
            for _ in 0..numpixels {
                let value = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
                let val = ((value * 255) / highest) as u8;
                buffer[buffer_idx as usize] = val;
                buffer[buffer_idx as usize + 1] = val;
                buffer[buffer_idx as usize + 2] = val;
                let key_match = mode.key_defined != 0 && value == mode.key_r;
                buffer[buffer_idx as usize + 3] = if key_match { 0 } else { 255 };
                i += 1;
                buffer_idx += num_channels as u32;
            }
        }
    }

    *buffer_idx_ref = buffer_idx;
    *i_ref = i;
}
pub fn getPixelColorsRGBA8(
    buffer: &mut [u8],
    numpixels: usize,
    in_data: &[u8],
    mode: &LodePNGColorMode,
) {
    let mut buffer_idx = 0usize; // Changed to usize
    let num_channels = 4usize; // Changed to usize

    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let mut i = 0;
            helper_getPixelColorsRGBA8_2(
                &mut (buffer_idx as u32), // Cast to u32 for helper functions
                &mut i,
                buffer,
                numpixels,
                in_data,
                mode,
                num_channels,
            );
        }
        LodePNGColorType::LCT_RGB => {
            let mut i = 0;
            helper_getPixelColorsRGBA8_1(
                &mut (buffer_idx as u32), // Cast to u32 for helper functions
                &mut i,
                buffer,
                numpixels,
                in_data,
                mode,
                num_channels,
            );
        }
        LodePNGColorType::LCT_PALETTE => {
            if mode.bitdepth == 8 {
                for i in 0..numpixels {
                    let index = in_data[i] as usize;
                    if let Some(palette) = &mode.palette {
                        lodepng_memcpy(
                            &mut buffer[buffer_idx..buffer_idx + 4],
                            &palette[index * 4..index * 4 + 4],
                        );
                    }
                    buffer_idx += num_channels;
                }
            } else {
                let mut j = 0;
                for _ in 0..numpixels {
                    let index = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
                    if let Some(palette) = &mode.palette {
                        lodepng_memcpy(
                            &mut buffer[buffer_idx..buffer_idx + 4],
                            &palette[index as usize * 4..index as usize * 4 + 4],
                        );
                    }
                    buffer_idx += num_channels;
                }
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if mode.bitdepth == 8 {
                for i in 0..numpixels {
                    let val = in_data[i * 2];
                    buffer[buffer_idx] = val;
                    buffer[buffer_idx + 1] = val;
                    buffer[buffer_idx + 2] = val;
                    buffer[buffer_idx + 3] = in_data[i * 2 + 1];
                    buffer_idx += num_channels;
                }
            } else {
                for i in 0..numpixels {
                    let val = in_data[i * 4];
                    buffer[buffer_idx] = val;
                    buffer[buffer_idx + 1] = val;
                    buffer[buffer_idx + 2] = val;
                    buffer[buffer_idx + 3] = in_data[i * 4 + 2];
                    buffer_idx += num_channels;
                }
            }
        }
        LodePNGColorType::LCT_RGBA => {
            if mode.bitdepth == 8 {
                lodepng_memcpy(buffer, &in_data[..numpixels * 4]);
            } else {
                for i in 0..numpixels {
                    buffer[buffer_idx] = in_data[i * 8];
                    buffer[buffer_idx + 1] = in_data[i * 8 + 2];
                    buffer[buffer_idx + 2] = in_data[i * 8 + 4];
                    buffer[buffer_idx + 3] = in_data[i * 8 + 6];
                    buffer_idx += num_channels;
                }
            }
        }
    }
}
pub fn getPixelColorRGBA16(
    r: &mut u16,
    g: &mut u16,
    b: &mut u16,
    a: &mut u16,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let value = (u16::from(in_data[i * 2]) << 8) + u16::from(in_data[i * 2 + 1]);
            *r = value;
            *g = value;
            *b = value;
            *a = if mode.key_defined != 0 && u32::from(value) == mode.key_r {
                0
            } else {
                65535
            };
        }
        LodePNGColorType::LCT_RGB => {
            *r = (u16::from(in_data[i * 6]) << 8) + u16::from(in_data[i * 6 + 1]);
            *g = (u16::from(in_data[i * 6 + 2]) << 8) + u16::from(in_data[i * 6 + 3]);
            *b = (u16::from(in_data[i * 6 + 4]) << 8) + u16::from(in_data[i * 6 + 5]);
            *a = if mode.key_defined != 0
                && u32::from(*r) == mode.key_r
                && u32::from(*g) == mode.key_g
                && u32::from(*b) == mode.key_b
            {
                0
            } else {
                65535
            };
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            let value = (u16::from(in_data[i * 4]) << 8) + u16::from(in_data[i * 4 + 1]);
            *r = value;
            *g = value;
            *b = value;
            *a = (u16::from(in_data[i * 4 + 2]) << 8) + u16::from(in_data[i * 4 + 3]);
        }
        LodePNGColorType::LCT_RGBA => {
            *r = (u16::from(in_data[i * 8]) << 8) + u16::from(in_data[i * 8 + 1]);
            *g = (u16::from(in_data[i * 8 + 2]) << 8) + u16::from(in_data[i * 8 + 3]);
            *b = (u16::from(in_data[i * 8 + 4]) << 8) + u16::from(in_data[i * 8 + 5]);
            *a = (u16::from(in_data[i * 8 + 6]) << 8) + u16::from(in_data[i * 8 + 7]);
        }
        _ => {}
    }
}
pub fn rgba16ToPixel(out: &mut [u8], i: usize, mode: &LodePNGColorMode, r: u16, g: u16, b: u16, a: u16) {
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let gray = r;
            out[(i * 2)..(i * 2 + 2)].copy_from_slice(&[(gray >> 8) as u8, gray as u8]);
        }
        LodePNGColorType::LCT_RGB => {
            out[(i * 6)..(i * 6 + 6)].copy_from_slice(&[
                (r >> 8) as u8, r as u8,
                (g >> 8) as u8, g as u8,
                (b >> 8) as u8, b as u8,
            ]);
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            let gray = r;
            out[(i * 4)..(i * 4 + 4)].copy_from_slice(&[
                (gray >> 8) as u8, gray as u8,
                (a >> 8) as u8, a as u8,
            ]);
        }
        LodePNGColorType::LCT_RGBA => {
            out[(i * 8)..(i * 8 + 8)].copy_from_slice(&[
                (r >> 8) as u8, r as u8,
                (g >> 8) as u8, g as u8,
                (b >> 8) as u8, b as u8,
                (a >> 8) as u8, a as u8,
            ]);
        }
        _ => {} // Handle other cases if needed
    }
}
pub fn color_tree_get(tree: &ColorTree, r: u8, g: u8, b: u8, a: u8) -> i32 {
    let mut tree_idx = tree;
    
    for bit in 0..8 {
        let i = (((8 * ((r >> bit) & 1)) + (4 * ((g >> bit) & 1))) + (2 * ((b >> bit) & 1))) + (1 * ((a >> bit) & 1));
        
        match &tree_idx.children[i as usize] {
            Some(child) => tree_idx = child,
            None => return -1,
        }
    }
    
    tree_idx.index
}
pub fn rgba8ToPixel(out: &mut [u8], i: usize, mode: &LodePNGColorMode, tree: &ColorTree, r: u8, g: u8, b: u8, a: u8) -> u32 {
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let gray = r;
            match mode.bitdepth {
                8 => {
                    out[i] = gray;
                }
                16 => {
                    out[i * 2] = gray;
                    out[i * 2 + 1] = gray;
                }
                _ => {
                    let gray = ((gray as u32) >> (8 - mode.bitdepth)) & ((1 << mode.bitdepth) - 1);
                    addColorBits(out, i, mode.bitdepth, gray);
                }
            }
        }
        LodePNGColorType::LCT_RGB => {
            match mode.bitdepth {
                8 => {
                    out[i * 3] = r;
                    out[i * 3 + 1] = g;
                    out[i * 3 + 2] = b;
                }
                _ => {
                    out[i * 6] = r;
                    out[i * 6 + 1] = r;
                    out[i * 6 + 2] = g;
                    out[i * 6 + 3] = g;
                    out[i * 6 + 4] = b;
                    out[i * 6 + 5] = b;
                }
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            let index = color_tree_get(tree, r, g, b, a);
            if index < 0 {
                return 82;
            }
            if mode.bitdepth == 8 {
                out[i] = index as u8;
            } else {
                addColorBits(out, i, mode.bitdepth, index as u32);
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            let gray = r;
            match mode.bitdepth {
                8 => {
                    out[i * 2] = gray;
                    out[i * 2 + 1] = a;
                }
                16 => {
                    out[i * 4] = gray;
                    out[i * 4 + 1] = gray;
                    out[i * 4 + 2] = a;
                    out[i * 4 + 3] = a;
                }
                _ => unreachable!(),
            }
        }
        LodePNGColorType::LCT_RGBA => {
            match mode.bitdepth {
                8 => {
                    out[i * 4] = r;
                    out[i * 4 + 1] = g;
                    out[i * 4 + 2] = b;
                    out[i * 4 + 3] = a;
                }
                _ => {
                    out[i * 8] = r;
                    out[i * 8 + 1] = r;
                    out[i * 8 + 2] = g;
                    out[i * 8 + 3] = g;
                    out[i * 8 + 4] = b;
                    out[i * 8 + 5] = b;
                    out[i * 8 + 6] = a;
                    out[i * 8 + 7] = a;
                }
            }
        }
    }
    0
}
pub fn getPixelColorsRGB8(buffer: &mut [u8], numpixels: usize, in_data: &[u8], mode: &LodePNGColorMode) {
    let num_channels = 3;
    let mut buffer_idx = 0;

    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            match mode.bitdepth {
                8 => {
                    for i in 0..numpixels {
                        let val = in_data[i];
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer_idx += num_channels;
                    }
                }
                16 => {
                    for i in 0..numpixels {
                        let val = in_data[i * 2];
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer_idx += num_channels;
                    }
                }
                _ => {
                    let highest = (1u32 << mode.bitdepth) - 1;
                    let mut j = 0;
                    for _ in 0..numpixels {
                        let value = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
                        let val = ((value * 255) / highest) as u8;
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer_idx += num_channels;
                    }
                }
            }
        }
        LodePNGColorType::LCT_RGB => {
            match mode.bitdepth {
                8 => {
                    lodepng_memcpy(&mut buffer[..numpixels * 3], &in_data[..numpixels * 3]);
                }
                _ => {
                    for i in 0..numpixels {
                        buffer[buffer_idx] = in_data[i * 6];
                        buffer[buffer_idx + 1] = in_data[i * 6 + 2];
                        buffer[buffer_idx + 2] = in_data[i * 6 + 4];
                        buffer_idx += num_channels;
                    }
                }
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            if let Some(palette) = &mode.palette {
                match mode.bitdepth {
                    8 => {
                        for i in 0..numpixels {
                            let index = in_data[i] as usize;
                            buffer[buffer_idx..buffer_idx + 3].copy_from_slice(&palette[index * 4..index * 4 + 3]);
                            buffer_idx += num_channels;
                        }
                    }
                    _ => {
                        let mut j = 0;
                        for _ in 0..numpixels {
                            let index = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize) as usize;
                            buffer[buffer_idx..buffer_idx + 3].copy_from_slice(&palette[index * 4..index * 4 + 3]);
                            buffer_idx += num_channels;
                        }
                    }
                }
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            match mode.bitdepth {
                8 => {
                    for i in 0..numpixels {
                        let val = in_data[i * 2];
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer_idx += num_channels;
                    }
                }
                _ => {
                    for i in 0..numpixels {
                        let val = in_data[i * 4];
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer_idx += num_channels;
                    }
                }
            }
        }
        LodePNGColorType::LCT_RGBA => {
            match mode.bitdepth {
                8 => {
                    for i in 0..numpixels {
                        buffer[buffer_idx..buffer_idx + 3].copy_from_slice(&in_data[i * 4..i * 4 + 3]);
                        buffer_idx += num_channels;
                    }
                }
                _ => {
                    for i in 0..numpixels {
                        buffer[buffer_idx] = in_data[i * 8];
                        buffer[buffer_idx + 1] = in_data[i * 8 + 2];
                        buffer[buffer_idx + 2] = in_data[i * 8 + 4];
                        buffer_idx += num_channels;
                    }
                }
            }
        }
    }
}
pub fn helper_lodepng_convert_2(
    i_ref: &mut usize,
    error_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    tree: ColorTree,
    numpixels: usize,
) {
    let mut i = *i_ref;
    let mut error = *error_ref;

    if mode_in.bitdepth == 16 && mode_out.bitdepth == 16 {
        for i in 0..numpixels {
            let mut r = 0u16;
            let mut g = 0u16;
            let mut b = 0u16;
            let mut a = 0u16;
            getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            rgba16ToPixel(out, i, mode_out, r, g, b, a);
        }
    } else if mode_out.bitdepth == 8 && mode_out.colortype == LodePNGColorType::LCT_RGBA {
        getPixelColorsRGBA8(out, numpixels, in_data, mode_in);
    } else if mode_out.bitdepth == 8 && mode_out.colortype == LodePNGColorType::LCT_RGB {
        getPixelColorsRGB8(out, numpixels, in_data, mode_in);
    } else {
        let mut r = 0u8;
        let mut g = 0u8;
        let mut b = 0u8;
        let mut a = 0u8;
        for i in 0..numpixels {
            getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            error = rgba8ToPixel(out, i, mode_out, &tree, r, g, b, a);
            if error != 0 {
                break;
            }
        }
    }

    *i_ref = i;
    *error_ref = error;
}
pub fn color_tree_init(tree: &mut ColorTree) {
    for child in tree.children.iter_mut() {
        *child = None;
    }
    tree.index = -1;
}
pub fn color_tree_add(tree: &mut ColorTree, r: u8, g: u8, b: u8, a: u8, index: u32) -> u32 {
    let mut tree_idx = tree;
    for bit in 0..8 {
        let i = (((8 * ((r >> bit) & 1)) + (4 * ((g >> bit) & 1))) + (2 * ((b >> bit) & 1))) + (1 * ((a >> bit) & 1));
        
        if tree_idx.children[i as usize].is_none() {
            let new_tree = Box::new(ColorTree {
                children: [
                    None, None, None, None,
                    None, None, None, None,
                    None, None, None, None,
                    None, None, None, None,
                ],
                index: -1,
            });
            tree_idx.children[i as usize] = Some(new_tree);
        }
        
        tree_idx = tree_idx.children[i as usize].as_mut().unwrap();
    }
    
    tree_idx.index = index as i32;
    0
}
pub fn helper_lodepng_convert_1(
    i_ref: &mut usize,
    error_ref: &mut u32,
    out: &mut [u8],
    in_: &[u8],
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    w: u32,
    h: u32,
    mut tree: ColorTree,
) {
    let mut i = *i_ref;
    let mut error = *error_ref;
    let mut palettesize = mode_out.palettesize;
    let palette = mode_out.palette.as_deref().unwrap_or(&[]);
    let mut palette_idx = 0;
    let mut palsize = 1usize << mode_out.bitdepth;

    if palettesize == 0 {
        palettesize = mode_in.palettesize;
        palette_idx = mode_in.key_defined as usize;
        if mode_in.colortype == LodePNGColorType::LCT_PALETTE && mode_in.bitdepth == mode_out.bitdepth {
            let numbytes = lodepng_get_raw_size(w, h, mode_in);
            lodepng_memcpy(&mut out[..numbytes], &in_[..numbytes]);
            *i_ref = i;
            *error_ref = error;
            return;
        }
    }

    if palettesize < palsize {
        palsize = palettesize;
    }

    color_tree_init(&mut tree);
    for i in 0..palsize {
        let p = &palette[(i * 4 + palette_idx)..][..4];
        error = color_tree_add(&mut tree, p[0], p[1], p[2], p[3], i as u32);
        if error != 0 {
            break;
        }
    }

    *i_ref = i;
    *error_ref = error;
}
pub fn color_tree_cleanup(tree: &mut ColorTree) {
    for i in 0..16 {
        if let Some(mut child) = tree.children[i].take() {
            color_tree_cleanup(&mut *child);
            lodepng_free(Some(Box::into_raw(child) as *mut std::ffi::c_void));
        }
    }
}
pub fn lodepng_color_mode_equal(a: &LodePNGColorMode, b: &LodePNGColorMode) -> bool {
    if a.colortype != b.colortype {
        return false;
    }
    if a.bitdepth != b.bitdepth {
        return false;
    }
    if a.key_defined != b.key_defined {
        return false;
    }
    if a.key_defined != 0 {
        if a.key_r != b.key_r {
            return false;
        }
        if a.key_g != b.key_g {
            return false;
        }
        if a.key_b != b.key_b {
            return false;
        }
    }
    if a.palettesize != b.palettesize {
        return false;
    }
    match (&a.palette, &b.palette) {
        (Some(a_palette), Some(b_palette)) => {
            if a_palette.len() != b_palette.len() {
                return false;
            }
            for i in 0..a.palettesize * 4 {
                if a_palette[i] != b_palette[i] {
                    return false;
                }
            }
        }
        (None, None) => {}
        _ => return false,
    }

    true
}
pub fn lodepng_convert(
    out: &mut [u8],
    in_data: &[u8],
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    w: u32,
    h: u32,
) -> u32 {
    let mut i = 0;
    let mut tree = ColorTree {
        children: [
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
        ],
        index: -1,
    };
    let numpixels = (w as usize) * (h as usize);
    let mut error = 0;

    if mode_in.colortype == LodePNGColorType::LCT_PALETTE && mode_in.palette.is_none() {
        return 107;
    }

    if lodepng_color_mode_equal(mode_out, mode_in) {
        let numbytes = lodepng_get_raw_size(w, h, mode_in);
        lodepng_memcpy(&mut out[..numbytes], &in_data[..numbytes]);
        return 0;
    }

    if mode_out.colortype == LodePNGColorType::LCT_PALETTE {
        helper_lodepng_convert_1(
            &mut i,
            &mut error,
            out,
            in_data,
            mode_out,
            mode_in,
            w,
            h,
            tree.clone(),
        );
    }

    if error == 0 {
        helper_lodepng_convert_2(
            &mut i,
            &mut error,
            out,
            in_data,
            mode_out,
            mode_in,
            tree.clone(),
            numpixels,
        );
    }

    if mode_out.colortype == LodePNGColorType::LCT_PALETTE {
        color_tree_cleanup(&mut tree);
    }

    error
}
pub fn lodepng_decode(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    state: &mut LodePNGState,
    in_data: &[u8],
    insize: usize,
) -> u32 {
    *out = None;
    decodeGeneric(out, w, h, state, in_data, insize);
    
    if state.error != 0 {
        return state.error;
    }

    if state.decoder.color_convert == 0 || lodepng_color_mode_equal(&state.info_raw, &state.info_png.color) {
        if state.decoder.color_convert == 0 {
            state.error = lodepng_color_mode_copy(&mut state.info_raw, &state.info_png.color);
            if state.error != 0 {
                return state.error;
            }
        }
    } else {
        let data = out.take(); // Take ownership of the current out value
        
        if !matches!(state.info_raw.colortype, LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA) 
            && state.info_raw.bitdepth != 8 
        {
            return 56;
        }

        let outsize = lodepng_get_raw_size(*w, *h, &state.info_raw);
        *out = Some(vec![0u8; outsize]);
        
        if out.is_none() {
            state.error = 83;
        } else if let Some(out_data) = out.as_mut() {
            if let Some(data_ref) = data.as_ref() {
                state.error = lodepng_convert(
                    out_data,
                    data_ref,
                    &state.info_raw,
                    &state.info_png.color,
                    *w,
                    *h,
                );
            }
        }
    }
    
    state.error
}
pub fn lodepng_compress_settings_init(settings: &mut LodePNGCompressSettings) {
    settings.btype = 2;
    settings.use_lz77 = 1;
    settings.windowsize = 2048;
    settings.minmatch = 3;
    settings.nicematch = 128;
    settings.lazymatching = 1;
    settings.custom_zlib = None;
    settings.custom_deflate = None;
    settings.custom_context = None;
}
pub fn lodepng_encoder_settings_init(settings: &mut LodePNGEncoderSettings) {
    lodepng_compress_settings_init(&mut settings.zlibsettings);
    settings.filter_palette_zero = 1;
    settings.filter_strategy = LodePngFilterStrategy::Minsum;
    settings.auto_convert = 1;
    settings.force_palette = 0;
    settings.predefined_filters = None;
    settings.add_id = 0;
    settings.text_compression = 1;
}
pub fn lodepng_decompress_settings_init(settings: &mut LodePNGDecompressSettings) {
    settings.ignore_adler32 = 0;
    settings.ignore_nlen = 0;
    settings.max_output_size = 0;
    settings.custom_zlib = None;
    settings.custom_inflate = None;
    settings.custom_context = None;
}
pub fn lodepng_decoder_settings_init(settings: &mut LodePNGDecoderSettings) {
    settings.color_convert = 1;
    settings.read_text_chunks = 1;
    settings.remember_unknown_chunks = 0;
    settings.max_text_size = 16777216;
    settings.max_icc_size = 16777216;
    settings.ignore_crc = 0;
    settings.ignore_critical = 0;
    settings.ignore_end = 0;
    lodepng_decompress_settings_init(&mut settings.zlibsettings);
}
pub fn lodepng_state_init(state: &mut LodePNGState) {
    lodepng_decoder_settings_init(&mut state.decoder);
    lodepng_encoder_settings_init(&mut state.encoder);
    lodepng_color_mode_init(&mut state.info_raw);
    lodepng_info_init(&mut state.info_png);
    state.error = 1;
}
pub fn lodepng_state_cleanup(state: &mut LodePNGState) {
    lodepng_color_mode_cleanup(&mut state.info_raw);
    lodepng_info_cleanup(&mut state.info_png);
}
pub fn lodepng_decode_memory(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    in_data: &[u8],
    insize: usize,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
    let mut state = LodePNGState {
        decoder: LodePNGDecoderSettings {
            zlibsettings: LodePNGDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePNGEncoderSettings {
            zlibsettings: LodePNGCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePngFilterStrategy::Minsum,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype,
            bitdepth,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePNGInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePNGTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 1,
    };

    state.info_raw.colortype = colortype;
    state.info_raw.bitdepth = bitdepth;
    state.decoder.read_text_chunks = 0;
    state.decoder.remember_unknown_chunks = 0;

    let error = lodepng_decode(out, w, h, &mut state, in_data, insize);
    lodepng_state_cleanup(&mut state);
    error
}
pub fn lodepng_decode32(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    in_data: &[u8],
    insize: usize,
) -> u32 {
    lodepng_decode_memory(out, w, h, in_data, insize, LodePNGColorType::LCT_RGBA, 8)
}
pub fn lodepng_decode24(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    in_data: &[u8],
    insize: usize,
) -> u32 {
    lodepng_decode_memory(out, w, h, in_data, insize, LodePNGColorType::LCT_RGB, 8)
}

pub fn lodepng_load_file(
    out: &mut Option<*mut u8>,
    outsize: &mut usize,
    filename: &str,
) -> u32 {
    let size = match lodepng_filesize(filename) {
        Some(s) if s >= 0 => s as usize,
        _ => return 78,
    };

    *outsize = size;

    // Allocate memory using the provided lodepng_malloc function
    *out = match lodepng_malloc(size) {
        Some(ptr) => Some(ptr as *mut u8),
        None if size > 0 => return 83,
        None => None,
    };

    // Convert the raw pointer to a mutable slice for safe usage
    if let Some(ptr) = *out {
        let buffer = unsafe { std::slice::from_raw_parts_mut(ptr, size) };
        match lodepng_buffer_file(buffer, filename) {
            Ok(()) => 0,
            Err(e) => e,
        }
    } else {
        0 // Success case when size is 0
    }
}
pub fn lodepng_decode_file(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    filename: &str,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
    let mut buffer: Option<*mut u8> = None;
    let mut buffersize: usize = 0;
    
    *out = None;
    *w = 0;
    *h = 0;

    let error = lodepng_load_file(&mut buffer, &mut buffersize, filename);
    if error == 0 {
        let buffer_slice = unsafe { 
            std::slice::from_raw_parts(buffer.unwrap(), buffersize) 
        };
        let decode_error = lodepng_decode_memory(
            out, 
            w, 
            h, 
            buffer_slice, 
            buffersize, 
            colortype, 
            bitdepth
        );
        lodepng_free(buffer.map(|p| p as *mut c_void));
        decode_error
    } else {
        lodepng_free(buffer.map(|p| p as *mut c_void));
        error
    }
}
pub fn lodepng_decode32_file(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    filename: &str,
) -> u32 {
    lodepng_decode_file(out, w, h, filename, LodePNGColorType::LCT_RGBA, 8)
}
pub fn lodepng_decode24_file(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    filename: &str,
) -> u32 {
    lodepng_decode_file(out, w, h, filename, LodePNGColorType::LCT_RGB, 8)
}
pub fn filterScanline(
    out: &mut [u8],
    scanline: &[u8],
    prevline: Option<&[u8]>,
    length: usize,
    bytewidth: usize,
    filterType: u8,
) {
    match filterType {
        0 => {
            out[..length].copy_from_slice(&scanline[..length]);
        }
        1 => {
            out[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
            for i in bytewidth..length {
                out[i] = scanline[i].wrapping_sub(scanline[i - bytewidth]);
            }
        }
        2 => {
            if let Some(prevline) = prevline {
                for i in 0..length {
                    out[i] = scanline[i].wrapping_sub(prevline[i]);
                }
            } else {
                out[..length].copy_from_slice(&scanline[..length]);
            }
        }
        3 => {
            if let Some(prevline) = prevline {
                for i in 0..bytewidth {
                    out[i] = scanline[i].wrapping_sub(prevline[i] >> 1);
                }
                for i in bytewidth..length {
                    out[i] = scanline[i].wrapping_sub(
                        ((scanline[i - bytewidth] as u16 + prevline[i] as u16) >> 1) as u8
                    );
                }
            } else {
                out[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
                for i in bytewidth..length {
                    out[i] = scanline[i].wrapping_sub(scanline[i - bytewidth] >> 1);
                }
            }
        }
        4 => {
            if let Some(prevline) = prevline {
                for i in 0..bytewidth {
                    out[i] = scanline[i].wrapping_sub(prevline[i]);
                }
                for i in bytewidth..length {
                    out[i] = scanline[i].wrapping_sub(paethPredictor(
                        scanline[i - bytewidth] as i16,
                        prevline[i] as i16,
                        prevline[i - bytewidth] as i16,
                    ));
                }
            } else {
                out[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
                for i in bytewidth..length {
                    out[i] = scanline[i].wrapping_sub(scanline[i - bytewidth]);
                }
            }
        }
        _ => return,
    }
}
pub fn ilog2i(i: usize) -> usize {
    if i == 0 {
        return 0;
    }
    let l = ilog2(i);
    (i * l) + ((i - (1usize << l)) << 1)
}
pub fn helper_helper_filter_2_1(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,
    x_ref: &mut u32,
    y_ref: &mut u32,
    bestSum_ref: &mut usize,
    type_ref: &mut u8,
    bestType_ref: &mut u8,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    bytewidth: usize,
    prevline: Option<&[u8]>,
    attempt: &mut [&mut [u8]; 5],
    count: &mut [u32; 256],
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut bestSum = *bestSum_ref;
    let mut filter_type = *type_ref;
    let mut bestType = *bestType_ref;

    for y in 0..h {
        for filter_type in 0..5 {
            let mut sum = 0;
            filterScanline(
                attempt[filter_type as usize],
                &in_data[(y as usize * linebytes)..],
                prevline,
                linebytes,
                bytewidth,
                filter_type as u8,
            );

            count.iter_mut().for_each(|x| *x = 0);
            for x in 0..linebytes {
                count[attempt[filter_type as usize][x] as usize] += 1;
            }

            count[filter_type as usize] += 1;
            for x in 0..256 {
                sum += ilog2i(count[x] as usize);
            }

            if filter_type == 0 || sum > bestSum {
                bestType = filter_type as u8;
                bestSum = sum;
            }
        }

        prevline_idx = y as usize * linebytes;
        out[y as usize * (linebytes + 1)] = bestType;
        for x in 0..linebytes {
            out[y as usize * (linebytes + 1) + 1 + x] = attempt[bestType as usize][x];
        }
    }

    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *bestSum_ref = bestSum;
    *type_ref = filter_type;
    *bestType_ref = bestType;
}
pub fn helper_filter_2(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,  // Changed from u32 to usize
    x_ref: &mut u32,
    y_ref: &mut u32,
    error_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    bytewidth: usize,
    prevline: Option<&[u8]>,
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut error = *error_ref;
    
    let mut attempt: [Option<*mut u8>; 5] = [None, None, None, None, None];
    
    for type_ in 0..5 {
        attempt[type_] = lodepng_malloc(linebytes).map(|ptr| ptr as *mut u8);
        if attempt[type_].is_none() {
            error = 83;
        }
    }

    if error == 0 {
        let mut bestSum = 0usize;
        let mut type_ = 0u8;  // Changed to u8 to match helper function
        let mut bestType = 0u8;  // Changed to u8 to match helper function
        let mut count = [0u32; 256];
        
        let mut attempt_refs: [&mut [u8]; 5] = [&mut [], &mut [], &mut [], &mut [], &mut []];
        for i in 0..5 {
            if let Some(ptr) = attempt[i] {
                attempt_refs[i] = unsafe { std::slice::from_raw_parts_mut(ptr, linebytes) };
            }
        }
        
        helper_helper_filter_2_1(
            &mut linebytes,
            &mut prevline_idx,
            &mut x,
            &mut y,
            &mut bestSum,
            &mut type_,
            &mut bestType,
            out,
            in_data,
            h,
            bytewidth,
            prevline,
            &mut attempt_refs,
            &mut count,
        );
    }

    // Free the allocated memory
    for i in 0..5 {
        if let Some(ptr) = attempt[i] {
            lodepng_free(Some(ptr as *mut std::ffi::c_void));
        }
    }
    
    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *error_ref = error;
}
pub fn hash_cleanup(hash: &mut Hash) {
    // In Rust, we don't need to manually free memory - dropping the Vecs will handle it
    // We can just set all fields to None to clear them
    hash.head = None;
    hash.val = None;
    hash.chain = None;
    hash.zeros = None;
    hash.headz = None;
    hash.chainz = None;
}
pub fn uivector_init(p: &mut Uivector) {
    p.data = None;
    p.size = 0;
    p.allocsize = 0;
}
pub fn bpmnode_create(
    lists: &mut BPMLists,
    weight: i32,
    index: u32,
    tail: Option<Box<BPMNode>>,
) -> Option<Box<BPMNode>> {
    if lists.nextfree >= lists.numfree {
        // Reset all in_use flags to 0
        if let Some(memory) = lists.memory.as_mut() {
            for node in memory.iter_mut() {
                node.in_use = 0;
            }
        }

        // Mark used nodes in chains0 and chains1
        if let (Some(chains0), Some(chains1)) = (lists.chains0.as_ref(), lists.chains1.as_ref()) {
            for i in 0..lists.listsize {
                let mut node_idx = chains0[i as usize].as_ref();
                while let Some(node) = node_idx {
                    if let Some(memory) = lists.memory.as_mut() {
                        if (node.index as usize) < memory.len() {
                            memory[node.index as usize].in_use = 1;
                        }
                    }
                    node_idx = node.tail.as_ref();
                }

                let mut node_idx = chains1[i as usize].as_ref();
                while let Some(node) = node_idx {
                    if let Some(memory) = lists.memory.as_mut() {
                        if (node.index as usize) < memory.len() {
                            memory[node.index as usize].in_use = 1;
                        }
                    }
                    node_idx = node.tail.as_ref();
                }
            }
        }

        // Rebuild freelist
        lists.numfree = 0;
        if let (Some(memory), Some(freelist)) = (lists.memory.as_ref(), lists.freelist.as_mut()) {
            for (i, node) in memory.iter().enumerate() {
                if node.in_use == 0 {
                    if (lists.numfree as usize) < freelist.len() {
                        freelist[lists.numfree as usize] = Some(Box::new(memory[i].clone()));
                        lists.numfree += 1;
                    }
                }
            }
        }

        lists.nextfree = 0;
    }

    if let Some(freelist) = lists.freelist.as_mut() {
        if (lists.nextfree as usize) < freelist.len() {
            if let Some(result) = freelist[lists.nextfree as usize].take() {
                lists.nextfree += 1;
                let mut result = result;
                result.weight = weight;
                result.index = index;
                result.tail = tail;
                return Some(result);
            }
        }
    }
    None
}
pub fn boundaryPM(
    lists: &mut BPMLists,
    leaves: &[BPMNode],
    numpresent: usize,
    c: usize,
    num: i32,
) {
    let lastindex = {
        let chains1 = lists.chains1.as_ref().expect("chains1 should exist");
        let node = chains1[c].as_ref().expect("chains1[c] should exist");
        node.index
    };

    if c == 0 {
        if lastindex >= numpresent as u32 {
            return;
        }
        {
            let chains1 = lists.chains1.as_mut().expect("chains1 should exist");
            lists.chains0.as_mut().expect("chains0 should exist")[c] = chains1[c].take();
        }
        {
            let weight = leaves[lastindex as usize].weight;
            lists.chains1.as_mut().expect("chains1 should exist")[c] =
                bpmnode_create(lists, weight, lastindex + 1, None);
        }
    } else {
        let sum = {
            let chains0 = lists.chains0.as_ref().expect("chains0 should exist");
            let chains1 = lists.chains1.as_ref().expect("chains1 should exist");
            chains0[c - 1].as_ref().expect("chains0[c-1] should exist").weight
                + chains1[c - 1].as_ref().expect("chains1[c-1] should exist").weight
        };

        {
            let chains1 = lists.chains1.as_mut().expect("chains1 should exist");
            lists.chains0.as_mut().expect("chains0 should exist")[c] = chains1[c].take();
        }

        if (lastindex < numpresent as u32) && (sum > leaves[lastindex as usize].weight) {
            let tail = {
                let chains1 = lists.chains1.as_ref().expect("chains1 should exist");
                chains1[c].as_ref().expect("chains1[c] should exist").tail.clone()
            };
            lists.chains1.as_mut().expect("chains1 should exist")[c] =
                bpmnode_create(lists, leaves[lastindex as usize].weight, lastindex + 1, tail);
            return;
        }

        let tail = {
            let chains1 = lists.chains1.as_ref().expect("chains1 should exist");
            chains1[c - 1].as_ref().expect("chains1[c-1] should exist").clone()
        };
        lists.chains1.as_mut().expect("chains1 should exist")[c] =
            bpmnode_create(lists, sum, lastindex, Some(tail));

        if (num + 1) < ((2 * numpresent as i32) - 2) {
            boundaryPM(lists, leaves, numpresent, c - 1, num);
            boundaryPM(lists, leaves, numpresent, c - 1, num);
        }
    }
}
pub fn bpmnode_sort(leaves: &mut [BPMNode]) {
    let num = leaves.len();
    let mut mem = vec![BPMNode {
        weight: 0,
        index: 0,
        tail: None,
        in_use: 0,
    }; num];
    let mut counter = 0;

    for width in (1..num).map(|w| w * 2).take_while(|&w| w < num) {
        let (a, b) = if counter & 1 == 1 {
            (&mem[..], &mut leaves[..])
        } else {
            (&leaves[..], &mut mem[..])
        };

        for p in (0..num).step_by(2 * width) {
            let q = if p + width > num { num } else { p + width };
            let r = if p + 2 * width > num { num } else { p + 2 * width };

            let mut i = p;
            let mut j = q;
            
            for k in p..r {
                if i < q && (j >= r || a[i].weight <= a[j].weight) {
                    b[k] = a[i].clone();
                    i += 1;
                } else {
                    b[k] = a[j].clone();
                    j += 1;
                }
            }
        }

        counter += 1;
    }

    if counter & 1 == 1 {
        for (i, node) in mem.iter().enumerate() {
            leaves[i] = node.clone();
        }
    }
}
pub fn helper_lodepng_huffman_code_lengths_1(
    error_ref: &mut u32,
    i_ref: &mut u32,
    lengths: &mut [u32],
    maxbitlen: u32,
    numpresent: usize,
    leaves: &mut [BPMNode],
    leaves_idx: usize,
) {
    let mut error = *error_ref;
    let mut i = *i_ref;
    let mut lists = BPMLists {
        listsize: maxbitlen,
        memsize: (2 * maxbitlen) * (maxbitlen + 1),
        nextfree: 0,
        numfree: (2 * maxbitlen) * (maxbitlen + 1),
        memory: None,
        freelist: None,
        chains0: None,
        chains1: None,
    };

    // Allocate memory
    lists.memory = Some(vec![
        BPMNode {
            weight: 0,
            index: 0,
            tail: None,
            in_use: 0,
        };
        lists.memsize as usize
    ]);
    lists.freelist = Some(vec![None; lists.memsize as usize]);
    lists.chains0 = Some(vec![None; lists.listsize as usize]);
    lists.chains1 = Some(vec![None; lists.listsize as usize]);

    if lists.memory.is_none() || lists.freelist.is_none() || lists.chains0.is_none() || lists.chains1.is_none() {
        error = 83;
    }

    if error == 0 {
        bpmnode_sort(&mut leaves[leaves_idx..leaves_idx + numpresent]);

        // Initialize freelist
        if let (Some(memory), Some(freelist)) = (lists.memory.as_ref(), lists.freelist.as_mut()) {
            for i in 0..lists.memsize as usize {
                freelist[i] = Some(Box::new(memory[i].clone()));
            }
        }

        // Create initial nodes
        bpmnode_create(&mut lists, leaves[leaves_idx].weight, 1, None);
        bpmnode_create(&mut lists, leaves[leaves_idx + 1].weight, 2, None);

        // Initialize chains
        if let (Some(chains0), Some(chains1)) = (lists.chains0.as_mut(), lists.chains1.as_mut()) {
            for i in 0..lists.listsize as usize {
                chains0[i] = lists.memory.as_ref().map(|m| Box::new(m[0].clone()));
                chains1[i] = lists.memory.as_ref().map(|m| Box::new(m[1].clone()));
            }
        }

        // Build the tree
        for i in 2..(2 * numpresent - 2) {
            boundaryPM(
                &mut lists,
                &leaves[leaves_idx..leaves_idx + numpresent],
                numpresent,
                (maxbitlen - 1) as usize,
                i as i32,
            );
        }

        // Update lengths
        if let Some(chains1) = lists.chains1.as_ref() {
            if let Some(node) = chains1[maxbitlen as usize - 1].as_ref() {
                let mut node_idx = node;
                loop {
                    for i in 0..node_idx.index as usize {
                        lengths[leaves[i + leaves_idx].index as usize] += 1;
                    }
                    if let Some(tail) = node_idx.tail.as_ref() {
                        node_idx = tail;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    // Clean up - memory is automatically managed by Rust's ownership system
    *error_ref = error;
    *i_ref = i;
}

pub fn lodepng_huffman_code_lengths(
    lengths: &mut [u32],
    frequencies: &[u32],
    numcodes: usize,
    maxbitlen: u32,
) -> u32 {
    let mut error = 0;
    let mut numpresent = 0;
    
    if numcodes == 0 {
        return 80;
    }
    if (1u32 << maxbitlen) < numcodes as u32 {
        return 80;
    }

    // Allocate leaves array
    let leaves_ptr = match lodepng_malloc(numcodes * std::mem::size_of::<BPMNode>()) {
        Some(p) => p as *mut BPMNode,
        None => return 83,
    };

    // Initialize leaves
    for i in 0..numcodes {
        if frequencies[i] > 0 {
            unsafe {
                ptr::write(
                    leaves_ptr.add(numpresent),
                    BPMNode {
                        weight: frequencies[i] as i32,
                        index: i as u32,
                        tail: None,
                        in_use: 0,
                    },
                );
            }
            numpresent += 1;
        }
    }

    // Initialize lengths to 0
    for length in lengths.iter_mut() {
        *length = 0;
    }

    match numpresent {
        0 => {
            lengths[0] = 1;
            lengths[1] = 1;
        }
        1 => {
            let index = unsafe { (*leaves_ptr).index as usize };
            lengths[index] = 1;
            lengths[if index == 0 { 1 } else { 0 }] = 1;
        }
        _ => {
            let mut i = 0;
            helper_lodepng_huffman_code_lengths_1(
                &mut error,
                &mut i,
                lengths,
                maxbitlen,
                numpresent,
                unsafe { std::slice::from_raw_parts_mut(leaves_ptr, numpresent) },
                0,
            );
        }
    }

    // Free leaves array
    lodepng_free(Some(leaves_ptr as *mut std::ffi::c_void));

    error
}
pub fn HuffmanTree_makeFromFrequencies(
    tree: &mut HuffmanTree,
    frequencies: &[u32],
    mincodes: usize,
    numcodes: usize,
    maxbitlen: u32,
) -> u32 {
    let mut numcodes = numcodes;
    
    // Adjust numcodes by subtracting 1 eight times (equivalent to numcodes -= 8)
    numcodes = numcodes.saturating_sub(8);
    
    // Skip trailing zero frequencies
    while numcodes > mincodes && frequencies.get(numcodes - 1).copied() == Some(0) {
        numcodes -= 1;
    }

    // Allocate lengths vector
    tree.lengths = Some(vec![0; numcodes]);
    if tree.lengths.is_none() {
        return 83;
    }
    
    tree.maxbitlen = maxbitlen;
    tree.numcodes = numcodes as u32;

    // Get mutable reference to lengths
    let lengths = tree.lengths.as_mut().unwrap();
    
    // Call lodepng_huffman_code_lengths
    let mut error = lodepng_huffman_code_lengths(lengths, frequencies, numcodes, maxbitlen);
    
    if error == 0 {
        error = HuffmanTree_makeFromLengths2(tree).unwrap_or(83);
    }
    
    error
}
pub fn writeBits(writer: &mut LodePNGBitWriter, value: u32, nbits: usize) {
    if nbits == 1 {
        if (writer.bp & 7u8) == 0 {
            if let Some(ref mut data) = writer.data {
                if !ucvector_resize(data, data.size + 1) {
                    return;
                }
                if let Some(ref mut vec) = data.data {
                    vec[data.size - 1] = 0;
                }
            }
        }
        if let Some(ref mut data) = writer.data {
            if let Some(ref mut vec) = data.data {
                vec[data.size - 1] |= (value as u8) << (writer.bp & 7u8);
            }
        }
        writer.bp += 1;
    } else {
        for i in 0..nbits {
            if (writer.bp & 7u8) == 0 {
                if let Some(ref mut data) = writer.data {
                    if !ucvector_resize(data, data.size + 1) {
                        return;
                    }
                    if let Some(ref mut vec) = data.data {
                        vec[data.size - 1] = 0;
                    }
                }
            }
            if let Some(ref mut data) = writer.data {
                if let Some(ref mut vec) = data.data {
                    vec[data.size - 1] |= (((value >> i) & 1) as u8) << (writer.bp & 7u8);
                }
            }
            writer.bp += 1;
        }
    }
}
pub fn countZeros(data: &[u8], size: usize, pos: usize) -> u32 {
    let data_idx = 0;
    let start = &data[data_idx..][pos..];
    let mut end = &start[..MAX_SUPPORTED_DEFLATE_LENGTH.min(size - pos)];
    
    let mut current = start;
    while current < end && current[0] == 0 {
        current = &current[1..];
    }
    
    (current.as_ptr() as usize - start.as_ptr() as usize) as u32
}
pub fn getHash(data: &[u8], size: usize, pos: usize) -> u32 {
    let mut result = 0u32;
    
    if pos + 2 < size {
        result ^= (data[pos] as u32) << 0;
        result ^= (data[pos + 1] as u32) << 4;
        result ^= (data[pos + 2] as u32) << 8;
    } else {
        if pos >= size {
            return 0;
        }
        let amount = size - pos;
        for i in 0..amount {
            result ^= (data[pos + i] as u32) << (i * 8);
        }
    }
    
    result & HASH_BIT_MASK
}
pub fn uivector_resize(p: &mut Uivector, size: usize) -> bool {
    let allocsize = size * std::mem::size_of::<u32>();
    if allocsize > p.allocsize {
        let newsize = allocsize + (p.allocsize >> 1);
        
        // Convert existing Vec to raw pointer if it exists
        let old_ptr = p.data.take().map(|vec| {
            let mut vec = vec;
            vec.shrink_to_fit();
            vec.as_mut_ptr() as *mut u8
        });

        let new_ptr = lodepng_realloc(old_ptr, newsize);
        
        match new_ptr {
            Some(ptr) => {
                // Convert the raw pointer back to a Vec
                unsafe {
                    p.data = Some(Vec::from_raw_parts(
                        ptr as *mut u32,
                        p.size,
                        newsize / std::mem::size_of::<u32>()
                    ));
                }
                p.allocsize = newsize;
            }
            None => {
                // If realloc failed, restore the original data if it existed
                if let Some(ptr) = old_ptr {
                    unsafe {
                        p.data = Some(Vec::from_raw_parts(
                            ptr as *mut u32,
                            p.size,
                            p.allocsize / std::mem::size_of::<u32>()
                        ));
                    }
                }
                return false;
            }
        }
    }
    p.size = size;
    true
}
pub fn uivector_push_back(p: &mut Uivector, c: u32) -> bool {
    if !uivector_resize(p, p.size + 1) {
        return false;
    }
    if let Some(ref mut data) = p.data {
        data[p.size - 1] = c;
    }
    true
}
pub fn updateHashChain(hash: &mut Hash, wpos: usize, hashval: u32, numzeros: u16) {
    // Update hash.val
    if let Some(val) = &mut hash.val {
        val[wpos] = hashval as i32;
    }

    // Update hash.chain and hash.head for hashval
    if let Some(head) = &mut hash.head {
        if let Some(chain) = &mut hash.chain {
            if head[hashval as usize] != -1 {
                chain[wpos] = head[hashval as usize] as u16;
            }
            head[hashval as usize] = wpos as i32;
        }
    }

    // Update hash.zeros
    if let Some(zero) = &mut hash.zeros {
        zero[wpos] = numzeros;
    }

    // Update hash.chainz and hash.headz for numzeros
    if let Some(headz) = &mut hash.headz {
        if let Some(chainz) = &mut hash.chainz {
            if headz[numzeros as usize] != -1 {
                chainz[wpos] = headz[numzeros as usize] as u16;
            }
            headz[numzeros as usize] = wpos as i32;
        }
    }
}
pub fn helper_helper_helper_encodeLZ77_1_3_1(
    offset_ref: &mut u32,
    length_ref: &mut u32,
    current_length_ref: &mut u32,
    foreptr_idx_ref: &mut u32,
    backptr_idx_ref: &mut u32,
    hash: &Hash,
    in_data: &[u8],
    nicematch: u32,
    lastptr: &[u8],
    foreptr: &[u8],
    backptr: &[u8],
    pos: usize,
    numzeros: u32,
    lastptr_idx: u32,
    current_offset: u32,
    hashpos: u32,
) {
    let mut offset = *offset_ref;
    let mut length = *length_ref;
    let mut current_length = *current_length_ref;
    let mut foreptr_idx = pos as u32;
    let mut backptr_idx = (pos as u32).wrapping_sub(current_offset);

    if numzeros >= 3 {
        let skip = match &hash.zeros {
            Some(zeros) => {
                let skip = zeros[hashpos as usize];
                if skip as u32 > numzeros {
                    numzeros
                } else {
                    skip as u32
                }
            }
            None => 0,
        };
        backptr_idx += skip;
        foreptr_idx += skip;
    }

    while foreptr_idx < lastptr_idx as u32
        && backptr.get(backptr_idx as usize) == foreptr.get(foreptr_idx as usize)
    {
        backptr_idx += 1;
        foreptr_idx += 1;
    }

    current_length = foreptr_idx - pos as u32;
    if current_length > length {
        length = current_length;
        offset = current_offset;
        if current_length >= nicematch {
            *offset_ref = offset;
            *length_ref = length;
            *current_length_ref = current_length;
            *foreptr_idx_ref = foreptr_idx;
            *backptr_idx_ref = backptr_idx;
            return;
        }
    }

    *offset_ref = offset;
    *length_ref = length;
    *current_length_ref = current_length;
    *foreptr_idx_ref = foreptr_idx;
    *backptr_idx_ref = backptr_idx;
}
pub fn helper_helper_encodeLZ77_1_3(
    offset_ref: &mut u32,
    length_ref: &mut u32,
    current_offset_ref: &mut u32,
    current_length_ref: &mut u32,
    prev_offset_ref: &mut u32,
    foreptr_idx_ref: &mut u32,
    backptr_idx_ref: &mut u32,
    hashpos_ref: &mut u32,
    hash: &Hash,
    in_data: &[u8],
    windowsize: u32,
    nicematch: u32,
    maxchainlength: u32,
    lastptr: &[u8],
    foreptr: &[u8],
    backptr: &[u8],
    pos: usize,
    numzeros: u32,
    hashval: u32,
    lastptr_idx: u32,
    wpos: usize,
    chainlength: &mut u32,
) {
    let mut offset = *offset_ref;
    let mut length = *length_ref;
    let mut current_offset = *current_offset_ref;
    let mut current_length = *current_length_ref;
    let mut prev_offset = *prev_offset_ref;
    let mut foreptr_idx = *foreptr_idx_ref;
    let mut backptr_idx = *backptr_idx_ref;
    let mut hashpos = *hashpos_ref;

    *chainlength += 1;
    if *chainlength >= maxchainlength {
        return;
    }

    current_offset = if hashpos <= wpos as u32 {
        wpos as u32 - hashpos
    } else {
        (wpos as u32 - hashpos) + windowsize
    };

    if current_offset < prev_offset {
        return;
    }

    prev_offset = current_offset;

    if current_offset > 0 {
        helper_helper_helper_encodeLZ77_1_3_1(
            &mut offset,
            &mut length,
            &mut current_length,
            &mut foreptr_idx,
            &mut backptr_idx,
            hash,
            in_data,
            nicematch,
            lastptr,
            foreptr,
            backptr,
            pos,
            numzeros,
            lastptr_idx,
            current_offset,
            hashpos,
        );
    }

    if hashpos == hash.chain.as_ref().unwrap()[hashpos as usize] as u32 {
        return;
    }

    if numzeros >= 3 && length > numzeros {
        hashpos = hash.chainz.as_ref().unwrap()[hashpos as usize] as u32;
        if hash.zeros.as_ref().unwrap()[hashpos as usize] as u32 != numzeros {
            return;
        }
    } else {
        hashpos = hash.chain.as_ref().unwrap()[hashpos as usize] as u32;
        if hash.val.as_ref().unwrap()[hashpos as usize] != hashval as i32 {
            return;
        }
    }

    *offset_ref = offset;
    *length_ref = length;
    *current_offset_ref = current_offset;
    *current_length_ref = current_length;
    *prev_offset_ref = prev_offset;
    *foreptr_idx_ref = foreptr_idx;
    *backptr_idx_ref = backptr_idx;
    *hashpos_ref = hashpos;
}
pub fn helper_helper_helper_encodeLZ77_1_2_1(
    pos_ref: &mut usize,
    error_ref: &mut u32,
    numzeros_ref: &mut u32,
    offset_ref: &mut u32,
    length_ref: &mut u32,
    lazy_ref: &mut u32,
    hashval_ref: &mut u32,
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    lazylength: u32,
    lazyoffset: u32,
) {
    let pos = *pos_ref;
    let mut error = *error_ref;
    let numzeros = *numzeros_ref;
    let mut offset = *offset_ref;
    let mut length = *length_ref;
    let mut lazy = *lazy_ref;
    let hashval = *hashval_ref;
    
    lazy = 0;
    
    if pos == 0 {
        error = 81;
    } else if length > (lazylength + 1) {
        if !uivector_push_back(out, u32::from(in_data[pos - 1])) {
            error = 83;
        }
    } else {
        length = lazylength;
        offset = lazyoffset;
        if let Some(ref mut head) = hash.head {
            head[hashval as usize] = -1;
        }
        if let Some(ref mut headz) = hash.headz {
            headz[numzeros as usize] = -1;
        }
        *pos_ref = pos - 1;
    }
    
    *pos_ref = pos;
    *error_ref = error;
    *numzeros_ref = numzeros;
    *offset_ref = offset;
    *length_ref = length;
    *lazy_ref = lazy;
    *hashval_ref = hashval;
}
pub fn helper_helper_encodeLZ77_1_2(
    pos_ref: &mut usize,
    error_ref: &mut u32,
    numzeros_ref: &mut u32,
    offset_ref: &mut u32,
    length_ref: &mut u32,
    lazy_ref: &mut u32,
    lazylength_ref: &mut u32,
    lazyoffset_ref: &mut u32,
    hashval_ref: &mut u32,
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    maxlazymatch: u32,
) {
    let pos = *pos_ref;
    let error = *error_ref;
    let numzeros = *numzeros_ref;
    let offset = *offset_ref;
    let length = *length_ref;
    let lazy = *lazy_ref;
    let lazylength = *lazylength_ref;
    let lazyoffset = *lazyoffset_ref;
    let hashval = *hashval_ref;

    if ((!lazy != 0) && (length >= 3) && (length <= maxlazymatch) && (length < MAX_SUPPORTED_DEFLATE_LENGTH as u32)) {
        *lazy_ref = 1;
        *lazylength_ref = length;
        *lazyoffset_ref = offset;
        return;
    }

    if lazy != 0 {
        helper_helper_helper_encodeLZ77_1_2_1(
            pos_ref,
            error_ref,
            numzeros_ref,
            offset_ref,
            length_ref,
            lazy_ref,
            hashval_ref,
            out,
            hash,
            in_data,
            lazylength,
            lazyoffset,
        );
    }

    *pos_ref = pos;
    *error_ref = error;
    *numzeros_ref = numzeros;
    *offset_ref = offset;
    *length_ref = length;
    *lazy_ref = lazy;
    *lazylength_ref = lazylength;
    *lazyoffset_ref = lazyoffset;
    *hashval_ref = hashval;
}
pub fn addLengthDistance(values: &mut Uivector, length: usize, distance: usize) {
    let length_code = searchCodeIndex(&LENGTHBASE, 29, length as u32) as u32;
    let extra_length = (length as u32) - LENGTHBASE[length_code as usize];
    let dist_code = searchCodeIndex(&DISTANCEBASE, 30, distance as u32) as u32;
    let extra_distance = (distance as u32) - DISTANCEBASE[dist_code as usize];
    let pos = values.size;
    
    if uivector_resize(values, values.size + 4) {
        if let Some(data) = &mut values.data {
            data[pos + 0] = length_code + 257;
            data[pos + 1] = extra_length;
            data[pos + 2] = dist_code;
            data[pos + 3] = extra_distance;
        }
    }
}
pub fn helper_helper_encodeLZ77_1_1(
    pos_ref: &mut usize,
    i_ref: &mut u32,
    numzeros_ref: &mut u32,
    hashval_ref: &mut u32,
    wpos_ref: &mut usize,
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    insize: usize,
    windowsize: u32,
    usezeros: u32,
    offset: u32,
    length: u32,
) {
    let mut pos = *pos_ref;
    let mut i = *i_ref;
    let mut numzeros = *numzeros_ref;
    let mut hashval = *hashval_ref;
    let mut wpos = *wpos_ref;

    addLengthDistance(out, length as usize, offset as usize);

    for _ in 1..length {
        pos += 1;
        wpos = pos & (windowsize as usize - 1);
        hashval = getHash(in_data, insize, pos);

        if usezeros != 0 && hashval == 0 {
            if numzeros == 0 {
                numzeros = countZeros(in_data, insize, pos);
            } else if (pos + numzeros as usize) > insize || in_data[(pos + numzeros as usize) - 1] != 0 {
                numzeros -= 1;
            }
        } else {
            numzeros = 0;
        }

        updateHashChain(hash, wpos, hashval, numzeros as u16);
    }

    *pos_ref = pos;
    *i_ref = i;
    *numzeros_ref = numzeros;
    *hashval_ref = hashval;
    *wpos_ref = wpos;
}
pub fn helper_encodeLZ77_1(
    pos_ref: &mut usize,
    i_ref: &mut u32,
    error_ref: &mut u32,
    numzeros_ref: &mut u32,
    offset_ref: &mut u32,
    length_ref: &mut u32,
    lazy_ref: &mut u32,
    lazylength_ref: &mut u32,
    lazyoffset_ref: &mut u32,
    hashval_ref: &mut u32,
    current_offset_ref: &mut u32,
    current_length_ref: &mut u32,
    prev_offset_ref: &mut u32,
    lastptr_idx_ref: &mut u32,
    foreptr_idx_ref: &mut u32,
    backptr_idx_ref: &mut u32,
    hashpos_ref: &mut u32,
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    insize: usize,
    windowsize: u32,
    minmatch: u32,
    nicematch: u32,
    lazymatching: u32,
    maxchainlength: u32,
    maxlazymatch: u32,
    usezeros: u32,
    lastptr: &[u8],
    foreptr: &[u8],
    backptr: &[u8],
) {
    let mut pos = *pos_ref;
    let mut i = *i_ref;
    let mut error = *error_ref;
    let mut numzeros = *numzeros_ref;
    let mut offset = *offset_ref;
    let mut length = *length_ref;
    let mut lazy = *lazy_ref;
    let mut lazylength = *lazylength_ref;
    let mut lazyoffset = *lazyoffset_ref;
    let mut hashval = *hashval_ref;
    let mut current_offset = *current_offset_ref;
    let mut current_length = *current_length_ref;
    let mut prev_offset = *prev_offset_ref;
    let mut lastptr_idx = *lastptr_idx_ref;
    let mut foreptr_idx = *foreptr_idx_ref;
    let mut backptr_idx = *backptr_idx_ref;
    let mut hashpos = *hashpos_ref;
    
    let mut wpos = pos & (windowsize as usize - 1);
    let mut chainlength = 0;
    
    hashval = getHash(in_data, insize, pos);
    
    if usezeros != 0 && hashval == 0 {
        if numzeros == 0 {
            numzeros = countZeros(in_data, insize, pos);
        } else if (pos + numzeros as usize) > insize || in_data[(pos + numzeros as usize) - 1] != 0 {
            numzeros -= 1;
        }
    } else {
        numzeros = 0;
    }
    
    updateHashChain(hash, wpos, hashval, numzeros as u16);
    
    length = 0;
    offset = 0;
    hashpos = hash.chain.as_ref().unwrap()[wpos] as u32;
    lastptr_idx = if insize < (pos + MAX_SUPPORTED_DEFLATE_LENGTH) {
        insize as u32
    } else {
        (pos + MAX_SUPPORTED_DEFLATE_LENGTH) as u32
    };
    prev_offset = 0;
    
    loop {
        helper_helper_encodeLZ77_1_3(
            &mut offset,
            &mut length,
            &mut current_offset,
            &mut current_length,
            &mut prev_offset,
            &mut foreptr_idx,
            &mut backptr_idx,
            &mut hashpos,
            hash,
            in_data,
            windowsize,
            nicematch,
            maxchainlength,
            lastptr,
            foreptr,
            backptr,
            pos,
            numzeros,
            hashval,
            lastptr_idx,
            wpos,
            &mut chainlength,
        );
        
        if lazymatching != 0 {
            helper_helper_encodeLZ77_1_2(
                &mut pos,
                &mut error,
                &mut numzeros,
                &mut offset,
                &mut length,
                &mut lazy,
                &mut lazylength,
                &mut lazyoffset,
                &mut hashval,
                out,
                hash,
                in_data,
                maxlazymatch,
            );
        }
        
        if length >= 3 && offset > windowsize {
            error = 86;
            break;
        }
        
        if length < 3 {
            if !uivector_push_back(out, in_data[pos] as u32) {
                error = 83;
                break;
            }
        } else if (length < minmatch) || (length == 3 && offset > 4096) {
            if !uivector_push_back(out, in_data[pos] as u32) {
                error = 83;
                break;
            }
        } else {
            helper_helper_encodeLZ77_1_1(
                &mut pos,
                &mut i,
                &mut numzeros,
                &mut hashval,
                &mut wpos,
                out,
                hash,
                in_data,
                insize,
                windowsize,
                usezeros,
                offset,
                length,
            );
        }
    }
    
    *pos_ref = pos;
    *i_ref = i;
    *error_ref = error;
    *numzeros_ref = numzeros;
    *offset_ref = offset;
    *length_ref = length;
    *lazy_ref = lazy;
    *lazylength_ref = lazylength;
    *lazyoffset_ref = lazyoffset;
    *hashval_ref = hashval;
    *current_offset_ref = current_offset;
    *current_length_ref = current_length;
    *prev_offset_ref = prev_offset;
    *lastptr_idx_ref = lastptr_idx;
    *foreptr_idx_ref = foreptr_idx;
    *backptr_idx_ref = backptr_idx;
    *hashpos_ref = hashpos;
}
pub fn encodeLZ77(
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    inpos: usize,
    insize: usize,
    windowsize: u32,
    minmatch: u32,
    nicematch: u32,
    lazymatching: u32,
) -> u32 {
    let mut error = 0;
    let maxchainlength = if windowsize >= 8192 {
        windowsize
    } else {
        windowsize / 8
    };
    let maxlazymatch = if windowsize >= 8192 {
        MAX_SUPPORTED_DEFLATE_LENGTH as u32
    } else {
        64
    };
    let usezeros = 1;
    let mut numzeros = 0;
    let mut offset = 0;
    let mut length = 0;
    let mut lazy = 0;
    let mut lazylength = 0;
    let mut lazyoffset = 0;
    let mut hashval = 0;
    let mut current_offset = 0;
    let mut current_length = 0;
    let mut prev_offset = 0;
    let mut lastptr_idx = 0;
    let mut foreptr_idx = 0;
    let mut backptr_idx = 0;
    let mut hashpos = 0;

    if windowsize == 0 || windowsize > 32768 {
        return 60;
    }
    if (windowsize & (windowsize - 1)) != 0 {
        return 90;
    }
    let nicematch = if nicematch > MAX_SUPPORTED_DEFLATE_LENGTH as u32 {
        MAX_SUPPORTED_DEFLATE_LENGTH as u32
    } else {
        nicematch
    };

    for mut pos in inpos..insize {
        helper_encodeLZ77_1(
            &mut pos,
            &mut 0, // i
            &mut error,
            &mut numzeros,
            &mut offset,
            &mut length,
            &mut lazy,
            &mut lazylength,
            &mut lazyoffset,
            &mut hashval,
            &mut current_offset,
            &mut current_length,
            &mut prev_offset,
            &mut lastptr_idx,
            &mut foreptr_idx,
            &mut backptr_idx,
            &mut hashpos,
            out,
            hash,
            in_data,
            insize,
            windowsize,
            minmatch,
            nicematch,
            lazymatching,
            maxchainlength,
            maxlazymatch,
            usezeros,
            &[], // lastptr
            &[], // foreptr
            &[], // backptr
        );
    }

    error
}
pub fn helper_helper_deflateDynamic_1_1(
    bitlen_lld_e_idx_ref: &mut u32,
    i_ref: &mut usize,
    numcodes_lld_e_ref: &mut usize,
    bitlen_lld: &[u32],
    bitlen_lld_e: &mut [u32],
    bitlen_lld_idx: u32,
    numcodes_lld: usize,
) {
    let mut bitlen_lld_e_idx = *bitlen_lld_e_idx_ref;
    let mut i = *i_ref;
    let mut numcodes_lld_e = *numcodes_lld_e_ref;
    let mut j = 0u32;
    
    j += 1;
    j += 1;
    
    while ((i + j as usize + 1) < numcodes_lld) && 
          (bitlen_lld[(i + j as usize + 1) + bitlen_lld_idx as usize] == bitlen_lld[i + bitlen_lld_idx as usize]) {
        j += 1;
    }
    
    if (bitlen_lld[i + bitlen_lld_idx as usize] == 0) && (j >= 2) {
        j += 1;
        if j <= 10 {
            bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = 17;
            numcodes_lld_e += 1;
            bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = (j - 3) as u32;
            numcodes_lld_e += 1;
        } else {
            if j > 138 {
                j = 138;
            }
            bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = 18;
            numcodes_lld_e += 1;
            bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = (j - 11) as u32;
            numcodes_lld_e += 1;
        }
        i += (j - 1) as usize;
    } else if j >= 3 {
        helper_helper_helper_deflateDynamic_1_1_1(
            &mut bitlen_lld_e_idx,
            &mut i,
            &mut numcodes_lld_e,
            &mut j,
            bitlen_lld,
            bitlen_lld_e,
            bitlen_lld_idx,
        );
    } else {
        bitlen_lld_e[(numcodes_lld_e + bitlen_lld_e_idx as usize)] = bitlen_lld[i + bitlen_lld_idx as usize];
        numcodes_lld_e += 1;
    }
    
    *bitlen_lld_e_idx_ref = bitlen_lld_e_idx;
    *i_ref = i;
    *numcodes_lld_e_ref = numcodes_lld_e;
}
pub fn writeBitsReversed(writer: &mut LodePNGBitWriter, value: u32, nbits: usize) {
    for i in 0..nbits {
        if (writer.bp & 7u8) == 0 {
            if let Some(ref mut data) = writer.data {
                if !ucvector_resize(data, data.size + 1) {
                    return;
                }
                if let Some(ref mut vec_data) = data.data {
                    vec_data[data.size - 1] = 0;
                }
            }
        }

        if let Some(ref mut data) = writer.data {
            if let Some(ref mut vec_data) = data.data {
                let bit = ((value >> ((nbits - 1) - i)) & 1u32) as u8;
                vec_data[data.size - 1] |= bit << (writer.bp & 7u8);
            }
        }
        writer.bp += 1;
    }
}
pub fn writeLZ77data(writer: &mut LodePNGBitWriter, lz77_encoded: &Uivector, tree_ll: &HuffmanTree, tree_d: &HuffmanTree) {
    let mut i = 0;
    while i < lz77_encoded.size {
        let val = lz77_encoded.data.as_ref().unwrap()[i];
        
        // Safe unwrap since we know the data exists (from the while condition)
        let ll_codes = tree_ll.codes.as_ref().unwrap();
        let ll_lengths = tree_ll.lengths.as_ref().unwrap();
        writeBitsReversed(writer, ll_codes[val as usize], ll_lengths[val as usize] as usize);

        if val > 256 {
            let length_index = val - 257;
            let n_length_extra_bits = LENGTHEXTRA[length_index as usize];
            i += 1;
            let length_extra_bits = lz77_encoded.data.as_ref().unwrap()[i];
            i += 1;
            let distance_code = lz77_encoded.data.as_ref().unwrap()[i];
            let distance_index = distance_code;
            let n_distance_extra_bits = DISTANCEEXTRA[distance_index as usize];
            i += 1;
            let distance_extra_bits = lz77_encoded.data.as_ref().unwrap()[i];
            
            writeBits(writer, length_extra_bits, n_length_extra_bits as usize);
            
            // Safe unwrap since we know the data exists
            let d_codes = tree_d.codes.as_ref().unwrap();
            let d_lengths = tree_d.lengths.as_ref().unwrap();
            writeBitsReversed(writer, d_codes[distance_code as usize], d_lengths[distance_code as usize] as usize);
            
            writeBits(writer, distance_extra_bits, n_distance_extra_bits as usize);
        }
        i += 1;
    }
}
pub fn helper_deflateDynamic_1(
    datapos_ref: &mut usize,
    error_ref: &mut u32,
    lz77_encoded_ref: &mut Uivector,
    frequencies_ll_idx_ref: &mut u32,
    frequencies_d_idx_ref: &mut u32,
    frequencies_cl_idx_ref: &mut u32,
    bitlen_lld_idx_ref: &mut u32,
    bitlen_lld_e_idx_ref: &mut u32,
    i_ref: &mut usize,
    numcodes_ll_ref: &mut usize,
    numcodes_d_ref: &mut usize,
    numcodes_lld_ref: &mut usize,
    numcodes_lld_e_ref: &mut usize,
    numcodes_cl_ref: &mut usize,
    HLIT_ref: &mut u32,
    HDIST_ref: &mut u32,
    HCLEN_ref: &mut u32,
    writer: &mut LodePNGBitWriter,
    hash: &mut Hash,
    data: &[u8],
    dataend: usize,
    settings: &LodePNGCompressSettings,
    tree_ll: &mut HuffmanTree,
    tree_d: &mut HuffmanTree,
    tree_cl: &mut HuffmanTree,
    frequencies_ll: &mut [u32],
    frequencies_d: &mut [u32],
    frequencies_cl: &mut [u32],
    bitlen_lld: &mut [u32],
    bitlen_lld_e: &mut [u32],
    datasize: usize,
    BFINAL: u32,
) {
    macro_rules! goto_end {
        ($datapos:expr, $error:expr, $lz77_encoded:expr, $frequencies_ll_idx:expr, $frequencies_d_idx:expr, $frequencies_cl_idx:expr, $bitlen_lld_idx:expr, $bitlen_lld_e_idx:expr, $i:expr, $numcodes_ll:expr, $numcodes_d:expr, $numcodes_lld:expr, $numcodes_lld_e:expr, $numcodes_cl:expr, $HLIT:expr, $HDIST:expr, $HCLEN:expr) => {
            *datapos_ref = $datapos;
            *error_ref = $error;
            *lz77_encoded_ref = $lz77_encoded;
            *frequencies_ll_idx_ref = $frequencies_ll_idx;
            *frequencies_d_idx_ref = $frequencies_d_idx;
            *frequencies_cl_idx_ref = $frequencies_cl_idx;
            *bitlen_lld_idx_ref = $bitlen_lld_idx;
            *bitlen_lld_e_idx_ref = $bitlen_lld_e_idx;
            *i_ref = $i;
            *numcodes_ll_ref = $numcodes_ll;
            *numcodes_d_ref = $numcodes_d;
            *numcodes_lld_ref = $numcodes_lld;
            *numcodes_lld_e_ref = $numcodes_lld_e;
            *numcodes_cl_ref = $numcodes_cl;
            *HLIT_ref = $HLIT;
            *HDIST_ref = $HDIST;
            *HCLEN_ref = $HCLEN;
            return;
        };
    }

    let mut datapos = *datapos_ref;
    let mut error = *error_ref;
    let mut lz77_encoded = lz77_encoded_ref.clone();
    let frequencies_ll_idx = *frequencies_ll_idx_ref;
    let frequencies_d_idx = *frequencies_d_idx_ref;
    let frequencies_cl_idx = *frequencies_cl_idx_ref;
    let mut bitlen_lld_idx = *bitlen_lld_idx_ref;
    let mut bitlen_lld_e_idx = *bitlen_lld_e_idx_ref;
    let mut i = *i_ref;
    let mut numcodes_ll = *numcodes_ll_ref;
    let mut numcodes_d = *numcodes_d_ref;
    let mut numcodes_lld = *numcodes_lld_ref;
    let mut numcodes_lld_e = *numcodes_lld_e_ref;
    let mut numcodes_cl = *numcodes_cl_ref;
    let mut HLIT = *HLIT_ref;
    let mut HDIST = *HDIST_ref;
    let mut HCLEN = *HCLEN_ref;

    // Clear frequencies arrays
    frequencies_ll[frequencies_ll_idx as usize..(frequencies_ll_idx + 286) as usize].fill(0);
    frequencies_d[frequencies_d_idx as usize..(frequencies_d_idx + 30) as usize].fill(0);
    frequencies_cl[frequencies_cl_idx as usize..(frequencies_cl_idx + 19) as usize].fill(0);

    if settings.use_lz77 != 0 {
        error = encodeLZ77(
            &mut lz77_encoded,
            hash,
            data,
            datapos,
            dataend,
            settings.windowsize,
            settings.minmatch,
            settings.nicematch,
            settings.lazymatching,
        );
        if error != 0 {
            goto_end!(
                datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
                frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
                numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
            );
        }
    } else {
        if !uivector_resize(&mut lz77_encoded, datasize) {
            error = 83;
            goto_end!(
                datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
                frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
                numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
            );
        }

        for i in datapos..dataend {
            lz77_encoded.data.as_mut().unwrap()[i - datapos] = data[i] as u32;
        }
    }

    i = 0;
    while i < lz77_encoded.size {
        let symbol = lz77_encoded.data.as_ref().unwrap()[i];
        frequencies_ll[(symbol + frequencies_ll_idx) as usize] += 1;
        if symbol > 256 {
            let dist = lz77_encoded.data.as_ref().unwrap()[i + 2];
            frequencies_d[(dist + frequencies_d_idx) as usize] += 1;
            i += 3;
        }
        i += 1;
    }

    frequencies_ll[(256 + frequencies_ll_idx) as usize] = 1;
    error = HuffmanTree_makeFromFrequencies(tree_ll, &frequencies_ll[frequencies_ll_idx as usize..], 257, 286, 15);
    if error != 0 {
        goto_end!(
            datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
            frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
            numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
        );
    }

    error = HuffmanTree_makeFromFrequencies(tree_d, &frequencies_d[frequencies_d_idx as usize..], 2, 30, 15);
    if error != 0 {
        goto_end!(
            datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
            frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
            numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
        );
    }

    numcodes_ll = std::cmp::min(tree_ll.numcodes as usize, 286);
    numcodes_d = std::cmp::min(tree_d.numcodes as usize, 30);
    numcodes_lld = numcodes_ll + numcodes_d;

    // Allocate memory for bitlen_lld and bitlen_lld_e
    let bitlen_lld_slice = &mut bitlen_lld[bitlen_lld_idx as usize..];
    let bitlen_lld_e_slice = &mut bitlen_lld_e[bitlen_lld_e_idx as usize..];
    
    if bitlen_lld_slice.len() < numcodes_lld || bitlen_lld_e_slice.len() < numcodes_lld {
        error = 83;
        goto_end!(
            datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
            frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
            numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
        );
    }

    numcodes_lld_e = 0;
    for i in 0..numcodes_ll {
        bitlen_lld_slice[i] = tree_ll.lengths.as_ref().unwrap()[i];
    }

    for i in 0..numcodes_d {
        bitlen_lld_slice[numcodes_ll + i] = tree_d.lengths.as_ref().unwrap()[i];
    }

    i = 0;
    while i < numcodes_lld {
        helper_helper_deflateDynamic_1_1(
            &mut bitlen_lld_e_idx,
            &mut i,
            &mut numcodes_lld_e,
            bitlen_lld,
            bitlen_lld_e,
            bitlen_lld_idx,
            numcodes_lld,
        );
    }

    let mut i = 0;
    while i < numcodes_lld_e {
        let idx = bitlen_lld_e[(i + bitlen_lld_e_idx as usize)] as usize;
        frequencies_cl[(idx + frequencies_cl_idx as usize)] += 1;
        if idx >= 16 {
            i += 1;
        }
        i += 1;
    }

    error = HuffmanTree_makeFromFrequencies(tree_cl, &frequencies_cl[frequencies_cl_idx as usize..], 19, 19, 7);
    if error != 0 {
        goto_end!(
            datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
            frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
            numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
        );
    }

    numcodes_cl = 19;
    while numcodes_cl > 4 && tree_cl.lengths.as_ref().unwrap()[CLCL_ORDER[numcodes_cl - 1] as usize] == 0 {
        numcodes_cl -= 1;
    }

    writeBits(writer, BFINAL, 1);
    writeBits(writer, 0, 1);
    writeBits(writer, 1, 1);
    HLIT = (numcodes_ll - 257) as u32;
    HDIST = (numcodes_d - 1) as u32;
    HCLEN = (numcodes_cl - 4) as u32;
    writeBits(writer, HLIT, 5);
    writeBits(writer, HDIST, 5);
    writeBits(writer, HCLEN, 4);

    for i in 0..numcodes_cl {
        writeBits(
            writer,
            tree_cl.lengths.as_ref().unwrap()[CLCL_ORDER[i] as usize] as u32,
            3,
        );
    }

    let mut i = 0;
    while i < numcodes_lld_e {
        let idx = bitlen_lld_e[(i + bitlen_lld_e_idx as usize)] as usize;
        writeBitsReversed(
            writer,
            tree_cl.codes.as_ref().unwrap()[idx],
            tree_cl.lengths.as_ref().unwrap()[idx] as usize,
        );
        if idx == 16 {
            i += 1;
            writeBits(writer, bitlen_lld_e[(i + bitlen_lld_e_idx as usize)], 2);
        } else if idx == 17 {
            i += 1;
            writeBits(writer, bitlen_lld_e[(i + bitlen_lld_e_idx as usize)], 3);
        } else if idx == 18 {
            i += 1;
            writeBits(writer, bitlen_lld_e[(i + bitlen_lld_e_idx as usize)], 7);
        }
        i += 1;
    }

    writeLZ77data(writer, &lz77_encoded, tree_ll, tree_d);
    if tree_ll.lengths.as_ref().unwrap()[256] == 0 {
        error = 64;
        goto_end!(
            datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
            frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
            numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
        );
    }

    writeBitsReversed(
        writer,
        tree_ll.codes.as_ref().unwrap()[256],
        tree_ll.lengths.as_ref().unwrap()[256] as usize,
    );

    goto_end!(
        datapos, error, lz77_encoded, frequencies_ll_idx, frequencies_d_idx,
        frequencies_cl_idx, bitlen_lld_idx, bitlen_lld_e_idx, i, numcodes_ll,
        numcodes_d, numcodes_lld, numcodes_lld_e, numcodes_cl, HLIT, HDIST, HCLEN
    );
}
pub fn uivector_cleanup(p: &mut Uivector) {
    // Set size and allocsize to 0
    p.size = 0;
    p.allocsize = 0;
    
    // Take the data out of the Option and convert to raw pointer
    if let Some(vec) = p.data.take() {
        lodepng_free(Some(vec.as_ptr() as *mut std::ffi::c_void));
    }
    
    // Set data to None
    p.data = None;
}
pub fn deflateDynamic(
    writer: &mut LodePNGBitWriter,
    hash: &mut Hash,
    data: &[u8],
    mut datapos: usize,
    dataend: usize,
    settings: &LodePNGCompressSettings,
    final_: u32,
) -> u32 {
    let mut error = 0;
    let mut lz77_encoded = Uivector {
        data: None,
        size: 0,
        allocsize: 0,
    };
    let mut tree_ll = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    let mut tree_d = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    let mut tree_cl = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };

    let datasize = dataend - datapos;
    let BFINAL = final_;
    let mut i = 0;
    let mut numcodes_ll = 0;
    let mut numcodes_d = 0;
    let mut numcodes_lld = 0;
    let mut numcodes_lld_e = 0;
    let mut numcodes_cl = 0;
    let mut HLIT = 0;
    let mut HDIST = 0;
    let mut HCLEN = 0;

    uivector_init(&mut lz77_encoded);
    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);
    HuffmanTree_init(&mut tree_cl);

    let frequencies_ll = lodepng_malloc(286 * std::mem::size_of::<u32>());
    let frequencies_d = lodepng_malloc(30 * std::mem::size_of::<u32>());
    let frequencies_cl = lodepng_malloc(19 * std::mem::size_of::<u32>());

    if frequencies_ll.is_none() || frequencies_d.is_none() || frequencies_cl.is_none() {
        error = 83;
    }

    while error == 0 {
        helper_deflateDynamic_1(
            &mut datapos,
            &mut error,
            &mut lz77_encoded,
            &mut 0,
            &mut 0,
            &mut 0,
            &mut 0,
            &mut 0,
            &mut i,
            &mut numcodes_ll,
            &mut numcodes_d,
            &mut numcodes_lld,
            &mut numcodes_lld_e,
            &mut numcodes_cl,
            &mut HLIT,
            &mut HDIST,
            &mut HCLEN,
            writer,
            hash,
            data,
            dataend,
            settings,
            &mut tree_ll,
            &mut tree_d,
            &mut tree_cl,
            unsafe { std::slice::from_raw_parts_mut(frequencies_ll.unwrap() as *mut u32, 286) },
            unsafe { std::slice::from_raw_parts_mut(frequencies_d.unwrap() as *mut u32, 30) },
            unsafe { std::slice::from_raw_parts_mut(frequencies_cl.unwrap() as *mut u32, 19) },
            &mut [0; 286 + 30],
            &mut [0; 286 + 30],
            datasize,
            BFINAL,
        );
    }

    uivector_cleanup(&mut lz77_encoded);
    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);
    HuffmanTree_cleanup(&mut tree_cl);

    if let Some(ptr) = frequencies_ll {
        lodepng_free(Some(ptr));
    }
    if let Some(ptr) = frequencies_d {
        lodepng_free(Some(ptr));
    }
    if let Some(ptr) = frequencies_cl {
        lodepng_free(Some(ptr));
    }

    error
}
pub fn deflateFixed(
    writer: &mut LodePNGBitWriter,
    hash: &mut Hash,
    data: &[u8],
    datapos: usize,
    dataend: usize,
    settings: &LodePNGCompressSettings,
    final_: u32,
) -> u32 {
    let mut tree_ll = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    let mut tree_d = HuffmanTree {
        codes: None,
        lengths: None,
        maxbitlen: 0,
        numcodes: 0,
        table_len: None,
        table_value: None,
    };
    let BFINAL = final_;
    let mut error = 0;

    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);

    error = generateFixedLitLenTree(&mut tree_ll).unwrap_or(1);
    if error == 0 {
        error = generateFixedDistanceTree(&mut tree_d).unwrap_or(1);
    }

    if error == 0 {
        writeBits(writer, BFINAL, 1);
        writeBits(writer, 1, 1);
        writeBits(writer, 0, 1);

        if settings.use_lz77 != 0 {
            let mut lz77_encoded = Uivector {
                data: None,
                size: 0,
                allocsize: 0,
            };
            uivector_init(&mut lz77_encoded);

            error = encodeLZ77(
                &mut lz77_encoded,
                hash,
                data,
                datapos,
                dataend,
                settings.windowsize,
                settings.minmatch,
                settings.nicematch,
                settings.lazymatching,
            );

            if error == 0 {
                writeLZ77data(writer, &lz77_encoded, &tree_ll, &tree_d);
            }

            uivector_cleanup(&mut lz77_encoded);
        } else {
            for i in datapos..dataend {
                writeBitsReversed(
                    writer,
                    tree_ll.codes.as_ref().unwrap()[data[i] as usize],
                    tree_ll.lengths.as_ref().unwrap()[data[i] as usize] as usize,
                );
            }
        }

        if error == 0 {
            writeBitsReversed(
                writer,
                tree_ll.codes.as_ref().unwrap()[256],
                tree_ll.lengths.as_ref().unwrap()[256] as usize,
            );
        }
    }

    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);

    error
}
pub fn hash_init(hash: &mut Hash, windowsize: usize) -> u32 {
    // Allocate memory for each field, converting to Vec<T> where appropriate
    hash.head = lodepng_malloc(std::mem::size_of::<i32>() * HASH_NUM_VALUES as usize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut i32, HASH_NUM_VALUES as usize, HASH_NUM_VALUES as usize) });
    hash.val = lodepng_malloc(std::mem::size_of::<i32>() * windowsize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut i32, windowsize, windowsize) });
    hash.chain = lodepng_malloc(std::mem::size_of::<u16>() * windowsize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut u16, windowsize, windowsize) });
    hash.zeros = lodepng_malloc(std::mem::size_of::<u16>() * windowsize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut u16, windowsize, windowsize) });
    hash.headz = lodepng_malloc(std::mem::size_of::<i32>() * (MAX_SUPPORTED_DEFLATE_LENGTH + 1))
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut i32, MAX_SUPPORTED_DEFLATE_LENGTH + 1, MAX_SUPPORTED_DEFLATE_LENGTH + 1) });
    hash.chainz = lodepng_malloc(std::mem::size_of::<u16>() * windowsize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut u16, windowsize, windowsize) });

    // Check if any allocation failed
    if hash.head.is_none() || hash.val.is_none() || hash.chain.is_none() || 
       hash.zeros.is_none() || hash.headz.is_none() || hash.chainz.is_none() {
        return 83;
    }

    // Initialize head array
    if let Some(head) = &mut hash.head {
        for i in 0..HASH_NUM_VALUES as usize {
            head[i] = -1;
        }
    }

    // Initialize val array
    if let Some(val) = &mut hash.val {
        for i in 0..windowsize {
            val[i] = -1;
        }
    }

    // Initialize chain array
    if let Some(chain) = &mut hash.chain {
        for i in 0..windowsize {
            chain[i] = i as u16;
        }
    }

    // Initialize headz array
    if let Some(headz) = &mut hash.headz {
        for i in 0..=MAX_SUPPORTED_DEFLATE_LENGTH {
            headz[i] = -1;
        }
    }

    // Initialize chainz array
    if let Some(chainz) = &mut hash.chainz {
        for i in 0..windowsize {
            chainz[i] = i as u16;
        }
    }

    0
}
pub fn LodePNGBitWriter_init(writer: &mut LodePNGBitWriter, data: &mut Ucvector) {
    writer.data = Some(Box::new(data.clone()));
    writer.bp = 0;
}

pub fn deflateNoCompression(out: &mut Ucvector, data: &[u8]) -> u32 {
    let numdeflateblocks = (data.len() + 65534) / 65535;
    let mut datapos = 0;

    for i in 0..numdeflateblocks {
        let BFINAL = i == (numdeflateblocks - 1);
        let BTYPE = 0;
        let mut LEN = 65535;
        if (data.len() - datapos) < 65535 {
            LEN = (data.len() - datapos) as u32;
        }
        let NLEN = 65535 - LEN;

        let pos = out.size;
        if !ucvector_resize(out, out.size + LEN as usize + 5) {
            return 83;
        }

        let firstbyte = (BFINAL as u8) | ((BTYPE & 1) << 1) as u8 | ((BTYPE & 2) << 1) as u8;
        
        // Safe mutable access to the vector data
        if let Some(ref mut vec_data) = out.data {
            vec_data[pos] = firstbyte;
            vec_data[pos + 1] = (LEN & 255) as u8;
            vec_data[pos + 2] = (LEN >> 8) as u8;
            vec_data[pos + 3] = (NLEN & 255) as u8;
            vec_data[pos + 4] = (NLEN >> 8) as u8;

            // Use slice operations for safe memory copying
            let dst_slice = &mut vec_data[pos + 5..pos + 5 + LEN as usize];
            let src_slice = &data[datapos..datapos + LEN as usize];
            dst_slice.copy_from_slice(src_slice);
        } else {
            return 83; // Handle case where data is None
        }

        datapos += LEN as usize;
    }

    0
}
pub fn lodepng_deflatev(
    out: &mut Ucvector,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGCompressSettings,
) -> u32 {
    let mut error = 0;
    let mut blocksize;
    let mut numdeflateblocks;
    let mut hash = Hash {
        head: None,
        chain: None,
        val: None,
        headz: None,
        chainz: None,
        zeros: None,
    };
    let mut writer = LodePNGBitWriter {
        data: None,
        bp: 0,
    };

    LodePNGBitWriter_init(&mut writer, out);

    if settings.btype > 2 {
        return 61;
    } else if settings.btype == 0 {
        return deflateNoCompression(out, in_data);
    } else if settings.btype == 1 {
        blocksize = insize;
    } else {
        blocksize = (insize / 8) + 8;
        if blocksize < 65536 {
            blocksize = 65536;
        }
        if blocksize > 262144 {
            blocksize = 262144;
        }
    }

    numdeflateblocks = ((insize + blocksize) - 1) / blocksize;
    if numdeflateblocks == 0 {
        numdeflateblocks = 1;
    }

    error = hash_init(&mut hash, settings.windowsize as usize);
    if error == 0 {
        for i in 0..numdeflateblocks {
            let final_ = (i == (numdeflateblocks - 1)) as u32;
            let start = i * blocksize;
            let mut end = start + blocksize;
            if end > insize {
                end = insize;
            }

            if settings.btype == 1 {
                error = deflateFixed(&mut writer, &mut hash, in_data, start, end, settings, final_);
            } else if settings.btype == 2 {
                error = deflateDynamic(&mut writer, &mut hash, in_data, start, end, settings, final_);
            }

            if error != 0 {
                break;
            }
        }
    }

    hash_cleanup(&mut hash);
    error
}
pub fn lodepng_deflate(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGCompressSettings,
) -> u32 {
    let mut v = ucvector_init(out.take(), *outsize);
    let error = lodepng_deflatev(&mut v, in_data, insize, settings);
    *out = v.data;
    *outsize = v.size;
    error
}
pub fn deflate(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGCompressSettings,
) -> u32 {
    if let Some(custom_deflate) = settings.custom_deflate {
        let mut vec_out = out.as_mut().map_or_else(|| Vec::new(), |v| std::mem::take(v));
        let error = custom_deflate(&mut vec_out, in_data, settings);
        *out = Some(vec_out);
        if error != 0 { 111 } else { 0 }
    } else {
        lodepng_deflate(out, outsize, in_data, insize, settings)
    }
}
pub fn lodepng_zlib_compress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGCompressSettings,
) -> u32 {
    let mut deflatedata: Option<Vec<u8>> = None;
    let mut deflatesize: usize = 0;
    let mut error = deflate(&mut deflatedata, &mut deflatesize, in_data, insize, settings);

    *out = None;
    *outsize = 0;

    if error == 0 {
        *outsize = deflatesize + 6;
        let mut output_vec = Vec::with_capacity(*outsize);
        output_vec.resize(*outsize, 0);

        let adler32 = adler32(Some(in_data), insize as u32);
        let cmf = 120;
        let flevel = 0;
        let fdict = 0;
        let cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
        let fcheck = 31 - (cmfflg % 31);
        let cmfflg = cmfflg + fcheck;

        output_vec[0] = (cmfflg >> 8) as u8;
        output_vec[1] = (cmfflg & 255) as u8;

        if let Some(deflatedata) = &deflatedata {
            for i in 0..deflatesize {
                output_vec[i + 2] = deflatedata[i];
            }
        }

        let last_four = output_vec.len() - 4;
        lodepng_set32bitInt(&mut output_vec[last_four..], adler32);

        *out = Some(output_vec);
        if out.is_none() {
            error = 83;
        }
    }

    // Free the deflatedata by dropping it (handled automatically by Rust)
    drop(deflatedata);

    error
}
pub fn zlib_compress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGCompressSettings,
) -> u32 {
    if let Some(custom_zlib) = settings.custom_zlib {
        let mut vec = out.take().unwrap_or_default();
        let error = custom_zlib(&mut vec, in_data, settings);
        *out = Some(vec);
        if error != 0 { 111 } else { 0 }
    } else {
        lodepng_zlib_compress(out, outsize, in_data, insize, settings)
    }
}
pub fn helper_helper_filter_3_1(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,
    x_ref: &mut u32,
    y_ref: &mut u32,
    smallest_ref: &mut usize,
    type_ref: &mut u32,
    bestType_ref: &mut u32,
    dummy_idx_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    bytewidth: usize,
    prevline: Option<&[u8]>,
    size: &mut [usize; 5],
    attempt: &mut [Vec<u8>; 5],
    dummy: &mut Vec<u8>,
    zlibsettings: &LodePNGCompressSettings,
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut smallest = *smallest_ref;
    let mut type_ = *type_ref;
    let mut bestType = *bestType_ref;
    let mut dummy_idx = *dummy_idx_ref;

    for y in 0..h {
        for type_ in 0..5 {
            let testsize = linebytes as u32;
            filterScanline(
                &mut attempt[type_ as usize],
                &in_data[(y as usize * linebytes)..],
                prevline,
                linebytes,
                bytewidth,
                type_ as u8,
            );
            size[type_ as usize] = 0;
            dummy_idx = 0;
            let mut dummy_slice = dummy[dummy_idx as usize..].to_vec();
            zlib_compress(
                &mut Some(dummy_slice),
                &mut size[type_ as usize],
                &attempt[type_ as usize],
                testsize as usize,
                zlibsettings,
            );
            lodepng_free(Some(dummy.as_mut_ptr() as *mut std::ffi::c_void));
            if type_ == 0 || size[type_ as usize] < smallest {
                bestType = type_;
                smallest = size[type_ as usize];
            }
        }

        prevline_idx = y as usize * linebytes;
        out[y as usize * (linebytes + 1)] = bestType as u8;
        for x in 0..linebytes {
            out[(y as usize * (linebytes + 1) + 1) + x] = attempt[bestType as usize][x];
        }
    }

    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *smallest_ref = smallest;
    *type_ref = type_;
    *bestType_ref = bestType;
    *dummy_idx_ref = dummy_idx;
}
pub fn helper_filter_3(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,  // Changed from u32 to usize to match helper_helper_filter_3_1
    x_ref: &mut u32,
    y_ref: &mut u32,
    error_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    settings: &LodePNGEncoderSettings,
    bytewidth: usize,
    prevline: Option<&[u8]>,
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut error = *error_ref;
    
    let mut size = [0usize; 5];
    let mut attempt: [Vec<u8>; 5] = [
        Vec::new(),
        Vec::new(),
        Vec::new(),
        Vec::new(),
        Vec::new(),
    ];
    let mut smallest = 0;
    let mut bestType = 0;
    let mut dummy = Vec::new();
    let mut dummy_idx = 0;
    
    // Create a new zlibsettings by copying the existing one manually
    let mut zlibsettings = LodePNGCompressSettings {
        btype: settings.zlibsettings.btype,
        use_lz77: settings.zlibsettings.use_lz77,
        windowsize: settings.zlibsettings.windowsize,
        minmatch: settings.zlibsettings.minmatch,
        nicematch: settings.zlibsettings.nicematch,
        lazymatching: settings.zlibsettings.lazymatching,
        custom_zlib: None,
        custom_deflate: None,
        custom_context: settings.zlibsettings.custom_context.as_ref().map(|_| ()).map(|_| Box::new(()) as Box<dyn std::any::Any>),
    };
    zlibsettings.btype = 1;

    for type_ in 0..5 {
        if let Some(ptr) = lodepng_malloc(linebytes) {
            unsafe {
                attempt[type_ as usize] = Vec::from_raw_parts(ptr as *mut u8, linebytes, linebytes);
            }
        } else {
            error = 83;
            break;
        }
    }

    if error == 0 {
        helper_helper_filter_3_1(
            &mut linebytes,
            &mut prevline_idx,
            &mut x,
            &mut y,
            &mut smallest,
            &mut 0, // type is not used after the loop
            &mut bestType,
            &mut dummy_idx,
            out,
            in_data,
            h,
            bytewidth,
            prevline,
            &mut size,
            &mut attempt,
            &mut dummy,
            &zlibsettings,
        );
    }

    for type_ in 0..5 {
        lodepng_free(Some(attempt[type_ as usize].as_mut_ptr() as *mut std::ffi::c_void));
    }

    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *error_ref = error;
}
pub fn helper_helper_filter_1_1(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,
    x_ref: &mut u32,
    y_ref: &mut u32,
    smallest_ref: &mut usize,
    type_ref: &mut u8,
    bestType_ref: &mut u8,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    bytewidth: usize,
    prevline: Option<&[u8]>,
    attempt: &mut [&mut [u8]; 5],
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut smallest = *smallest_ref;
    let mut type_ = *type_ref;
    let mut bestType = *bestType_ref;

    for y in 0..h {
        for type_ in 0..5 {
            let mut sum = 0;
            filterScanline(
                attempt[type_ as usize],
                &in_data[(y as usize * linebytes)..],
                prevline,
                linebytes,
                bytewidth,
                type_,
            );

            if type_ == 0 {
                for x in 0..linebytes {
                    sum += attempt[type_ as usize][x] as usize;
                }
            } else {
                for x in 0..linebytes {
                    let s = attempt[type_ as usize][x];
                    sum += if s < 128 { s as usize } else { (255 - s) as usize };
                }
            }

            if type_ == 0 || sum < smallest {
                bestType = type_;
                smallest = sum;
            }
        }

        prevline_idx = y as usize * linebytes;
        out[y as usize * (linebytes + 1)] = bestType;
        for x in 0..linebytes {
            out[y as usize * (linebytes + 1) + 1 + x] = attempt[bestType as usize][x];
        }
    }

    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *smallest_ref = smallest;
    *type_ref = type_;
    *bestType_ref = bestType;
}
pub fn helper_filter_1(
    linebytes_ref: &mut usize,
    prevline_idx_ref: &mut usize,
    x_ref: &mut u32,
    y_ref: &mut u32,
    error_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    h: u32,
    bytewidth: usize,
    prevline: Option<&[u8]>,
) {
    let mut linebytes = *linebytes_ref;
    let mut prevline_idx = *prevline_idx_ref;
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut error = *error_ref;
    
    let mut attempt: [Option<Vec<u8>>; 5] = [None, None, None, None, None];
    
    for type_ in 0..5 {
        if let Some(ptr) = lodepng_malloc(linebytes) {
            unsafe {
                attempt[type_ as usize] = Some(Vec::from_raw_parts(
                    ptr as *mut u8,
                    linebytes,
                    linebytes,
                ));
            }
        } else {
            error = 83;
            break;
        }
    }

    if error == 0 {
        let mut smallest = 0;
        let mut type_ = 0;
        let mut bestType = 0;
        
        // Create mutable references by destructuring the array to avoid multiple mutable borrows
        let [a0, a1, a2, a3, a4] = &mut attempt;
        let attempt0 = a0.as_mut().map(|v| v.as_mut_slice()).unwrap_or(&mut []);
        let attempt1 = a1.as_mut().map(|v| v.as_mut_slice()).unwrap_or(&mut []);
        let attempt2 = a2.as_mut().map(|v| v.as_mut_slice()).unwrap_or(&mut []);
        let attempt3 = a3.as_mut().map(|v| v.as_mut_slice()).unwrap_or(&mut []);
        let attempt4 = a4.as_mut().map(|v| v.as_mut_slice()).unwrap_or(&mut []);
        
        let mut attempt_refs: [&mut [u8]; 5] = [attempt0, attempt1, attempt2, attempt3, attempt4];
        
        helper_helper_filter_1_1(
            &mut linebytes,
            &mut prevline_idx,
            &mut x,
            &mut y,
            &mut smallest,
            &mut type_,
            &mut bestType,
            out,
            in_data,
            h,
            bytewidth,
            prevline,
            &mut attempt_refs,
        );
    }

    // No need to explicitly free in Rust, the Vecs will be dropped automatically
    *linebytes_ref = linebytes;
    *prevline_idx_ref = prevline_idx;
    *x_ref = x;
    *y_ref = y;
    *error_ref = error;
}
pub fn filter(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    color: &LodePNGColorMode,
    settings: &LodePNGEncoderSettings,
) -> u32 {
    let bpp = lodepng_get_bpp(color) as u32;
    let mut linebytes = lodepng_get_raw_size_idat(w, 1, bpp) - 1;
    let bytewidth = ((bpp + 7) / 8) as usize;
    let mut prevline: Option<&[u8]> = None;
    let mut prevline_idx = 0;
    let mut x = 0;
    let mut y = 0;
    let mut error = 0;
    let mut strategy = settings.filter_strategy;

    if settings.filter_palette_zero != 0 && (color.colortype == LodePNGColorType::LCT_PALETTE || color.bitdepth < 8) {
        strategy = LodePngFilterStrategy::Zero;
    }

    if bpp == 0 {
        return 31;
    }

    match strategy {
        LodePngFilterStrategy::Zero
        | LodePngFilterStrategy::One
        | LodePngFilterStrategy::Two
        | LodePngFilterStrategy::Three
        | LodePngFilterStrategy::Four => {
            let filter_type = strategy as u8;
            for y in 0..h {
                let outindex = (1 + linebytes) * y as usize;
                let inindex = linebytes * y as usize;
                out[outindex] = filter_type;
                filterScanline(
                    &mut out[outindex + 1..],
                    &in_data[inindex..inindex + linebytes],
                    prevline,
                    linebytes,
                    bytewidth,
                    filter_type,
                );
                prevline = Some(&in_data[inindex..inindex + linebytes]);
            }
        }
        LodePngFilterStrategy::Minsum => {
            helper_filter_1(
                &mut linebytes,
                &mut prevline_idx,
                &mut x,
                &mut y,
                &mut error,
                out,
                in_data,
                h,
                bytewidth,
                prevline,
            );
        }
        LodePngFilterStrategy::Entropy => {
            helper_filter_2(
                &mut linebytes,
                &mut prevline_idx,
                &mut x,
                &mut y,
                &mut error,
                out,
                in_data,
                h,
                bytewidth,
                prevline,
            );
        }
        LodePngFilterStrategy::Predefined => {
            if let Some(predefined_filters) = &settings.predefined_filters {
                for y in 0..h {
                    let outindex = (1 + linebytes) * y as usize;
                    let inindex = linebytes * y as usize;
                    let filter_type = predefined_filters[y as usize];
                    out[outindex] = filter_type;
                    filterScanline(
                        &mut out[outindex + 1..],
                        &in_data[inindex..inindex + linebytes],
                        prevline,
                        linebytes,
                        bytewidth,
                        filter_type,
                    );
                    prevline = Some(&in_data[inindex..inindex + linebytes]);
                }
            } else {
                return 88;
            }
        }
        LodePngFilterStrategy::BruteForce => {
            helper_filter_3(
                &mut linebytes,
                &mut prevline_idx,
                &mut x,
                &mut y,
                &mut error,
                out,
                in_data,
                h,
                settings,
                bytewidth,
                prevline,
            );
        }
        _ => return 88,
    }

    error
}
pub fn addPaddingBits(out: &mut [u8], in_: &[u8], olinebits: usize, ilinebits: usize, h: u32) {
    let diff = olinebits - ilinebits;
    let mut obp = 0;
    let mut ibp = 0;
    
    for _y in 0..h {
        for _x in 0..ilinebits {
            let bit = readBitFromReversedStream(&mut ibp, in_);
            setBitOfReversedStream(&mut obp, out, bit);
        }

        for _x in 0..diff {
            setBitOfReversedStream(&mut obp, out, 0);
        }
    }
}
pub fn helper_preProcessScanlines_1(
    error_ref: &mut u32,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePNGInfo,
    settings: &LodePNGEncoderSettings,
    bpp: u32,
) {
    let mut error = *error_ref;
    *outsize = h as usize + (h as usize * (((w * bpp) + 7u32) / 8u32) as usize);
    
    *out = lodepng_malloc(*outsize)
        .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut u8, *outsize, *outsize) });
    
    if out.is_none() && *outsize > 0 {
        error = 83;
    }
    
    if error == 0 {
        if bpp < 8 && (w * bpp) != (((w * bpp) + 7u32) / 8u32) * 8u32 {
            let padded_size = h as usize * (((w * bpp) + 7u32) / 8u32) as usize;
            let mut padded = lodepng_malloc(padded_size)
                .map(|ptr| unsafe { Vec::from_raw_parts(ptr as *mut u8, padded_size, padded_size) });
            
            if padded.is_none() {
                error = 83;
            }
            
            if error == 0 {
                let padded = padded.as_mut().unwrap();
                addPaddingBits(
                    padded,
                    in_data,
                    (((w * bpp) + 7u32) / 8u32 * 8u32) as usize,
                    (w * bpp) as usize,
                    h,
                );
                error = filter(
                    out.as_mut().unwrap(),
                    padded,
                    w,
                    h,
                    &info_png.color,
                    settings,
                );
            }
            
            // padded will be automatically dropped when it goes out of scope
        } else {
            error = filter(
                out.as_mut().unwrap(),
                in_data,
                w,
                h,
                &info_png.color,
                settings,
            );
        }
    }
    
    *error_ref = error;
}
pub fn helper_Adam7_interlace_1(
    i_ref: &mut u32,
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    bpp: u32,
    passw: [u32; 7],
    passh: [u32; 7],
    passstart: [usize; 8],
) {
    *i_ref = 0;
    for i in 0..7 {
        let ilinebits = bpp * passw[i as usize];
        let olinebits = bpp * w;
        for y in 0..passh[i as usize] {
            for x in 0..passw[i as usize] {
                let mut ibp = ((ADAM7_IY[i as usize] + (y * ADAM7_DY[i as usize])) * olinebits)
                    + ((ADAM7_IX[i as usize] + (x * ADAM7_DX[i as usize])) * bpp);
                let mut obp = (8 * passstart[i as usize]) + ((y * ilinebits + x * bpp) as usize);
                for _ in 0..bpp {
                    let mut ibp_usize = ibp as usize;
                    let bit = readBitFromReversedStream(&mut ibp_usize, in_data);
                    ibp = ibp_usize as u32;
                    setBitOfReversedStream(&mut obp, out, bit);
                }
            }
        }
    }
}
pub fn Adam7_interlace(out: &mut [u8], in_data: &[u8], w: u32, h: u32, bpp: u32) {
    let mut passw = [0u32; 7];
    let mut passh = [0u32; 7];
    let mut filter_passstart = [0usize; 8];
    let mut padded_passstart = [0usize; 8];
    let mut passstart = [0usize; 8];
    
    Adam7_getpassvalues(
        &mut passw,
        &mut passh,
        &mut filter_passstart,
        &mut padded_passstart,
        &mut passstart,
        w,
        h,
        bpp,
    );

    if bpp >= 8 {
        for i in 0..7 {
            let bytewidth = bpp / 8;
            for y in 0..passh[i] {
                for x in 0..passw[i] {
                    let pixelinstart = ((((ADAM7_IY[i] + (y * ADAM7_DY[i])) * w) + ADAM7_IX[i] + (x * ADAM7_DX[i])) * bytewidth) as usize;
                    let pixeloutstart = passstart[i] + ((y * passw[i] + x) * bytewidth) as usize;
                    
                    for b in 0..bytewidth {
                        out[pixeloutstart + b as usize] = in_data[pixelinstart + b as usize];
                    }
                }
            }
        }
    } else {
        let mut i = 0;
        helper_Adam7_interlace_1(&mut i, out, in_data, w, bpp, passw, passh, passstart);
    }
}
pub fn helper_helper_preProcessScanlines_2_1(
    error_ref: &mut u32,
    out: &mut Vec<u8>,
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePNGInfo,
    settings: &LodePNGEncoderSettings,
    bpp: u32,
    passw: &[u32; 7],
    passh: &[u32; 7],
    filter_passstart: &[usize; 8],
    padded_passstart: &[usize; 8],
    passstart: &[usize; 8],
    adam7: &mut [u8],
    adam7_idx: u32,
) {
    let mut error = *error_ref;
    
    Adam7_interlace(adam7, in_data, w, h, bpp);
    
    for i in 0..7 {
        if bpp < 8 {
            let padded_size = padded_passstart[i + 1] - padded_passstart[i];
            let padded_ptr = lodepng_malloc(padded_size);
            
            if padded_ptr.is_none() {
                error = 83;
                break;
            }
            
            let padded_slice = unsafe {
                std::slice::from_raw_parts_mut(padded_ptr.unwrap() as *mut u8, padded_size)
            };
            
            addPaddingBits(
                padded_slice,
                &adam7[passstart[i] + adam7_idx as usize..],
                (((passw[i] * bpp) + 7u32) / 8u32 * 8u32) as usize,
                (passw[i] * bpp) as usize,
                passh[i],
            );
            
            error = filter(
                &mut out[filter_passstart[i]..],
                padded_slice,
                passw[i],
                passh[i],
                &info_png.color,
                settings,
            );
            
            lodepng_free(padded_ptr);
        } else {
            error = filter(
                &mut out[filter_passstart[i]..],
                &adam7[padded_passstart[i] + adam7_idx as usize..],
                passw[i],
                passh[i],
                &info_png.color,
                settings,
            );
        }
        
        if error != 0 {
            break;
        }
    }
    
    *error_ref = error;
}
pub fn helper_preProcessScanlines_2(
    error_ref: &mut u32,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePNGInfo,
    settings: &LodePNGEncoderSettings,
    bpp: u32,
) {
    let mut error = *error_ref;
    let mut passw = [0u32; 7];
    let mut passh = [0u32; 7];
    let mut filter_passstart = [0usize; 8];
    let mut padded_passstart = [0usize; 8];
    let mut passstart = [0usize; 8];

    Adam7_getpassvalues(
        &mut passw,
        &mut passh,
        &mut filter_passstart,
        &mut padded_passstart,
        &mut passstart,
        w,
        h,
        bpp,
    );

    *outsize = filter_passstart[7];
    *out = Some(Vec::with_capacity(*outsize));
    
    if out.is_none() {
        error = 83;
    }

    let mut adam7 = Vec::with_capacity(passstart[7]);
    if adam7.capacity() < passstart[7] && passstart[7] > 0 {
        error = 83;
    }

    if error == 0 {
        helper_helper_preProcessScanlines_2_1(
            &mut error,
            out.as_mut().unwrap(),
            in_data,
            w,
            h,
            info_png,
            settings,
            bpp,
            &passw,
            &passh,
            &filter_passstart,
            &padded_passstart,
            &passstart,
            &mut adam7,
            0,
        );
    }

    *error_ref = error;
}
pub fn preProcessScanlines(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePNGInfo,
    settings: &LodePNGEncoderSettings,
) -> u32 {
    let bpp = lodepng_get_bpp(&info_png.color) as u32;
    let mut error = 0u32;

    if info_png.interlace_method == 0 {
        helper_preProcessScanlines_1(&mut error, out, outsize, in_data, w, h, info_png, settings, bpp);
    } else {
        helper_preProcessScanlines_2(&mut error, out, outsize, in_data, w, h, info_png, settings, bpp);
    }

    error
}
pub fn helper_lodepng_encode_1(
    image: &[u8],
    w: u32,
    h: u32,
    state: &mut LodePNGState,
    data: &mut Option<Vec<u8>>,
    datasize: &mut usize,
    info: &LodePNGInfo,
) {
    let bpp = lodepng_get_bpp(&info.color);
    let size = (((w as usize) * (h as usize) * (bpp as usize)) + 7) / 8;
    
    let converted_ptr = lodepng_malloc(size);
    if converted_ptr.is_none() && size > 0 {
        state.error = 83;
        return;
    }

    let mut converted = unsafe {
        Vec::from_raw_parts(
            converted_ptr.unwrap() as *mut u8,
            size,
            size
        )
    };

    if state.error == 0 {
        state.error = lodepng_convert(
            &mut converted,
            image,
            &info.color,
            &state.info_raw,
            w,
            h
        );
    }

    if state.error == 0 {
        state.error = preProcessScanlines(
            data,
            datasize,
            &converted,
            w,
            h,
            info,
            &state.encoder
        );
    }

    // Explicitly drop the Vec to avoid double-free
    std::mem::drop(converted);
    // The memory is freed when the Vec is dropped
}
pub fn lodepng_assign_icc(info: &mut LodePNGInfo, name: Option<&CStr>, profile: &[u8], profile_size: u32) -> u32 {
    if profile_size == 0 {
        return 100;
    }

    info.iccp_name = alloc_string(name).map(|bytes| String::from_utf8_lossy(&bytes).into_owned());
    info.iccp_profile = Some(profile.to_vec());
    
    if info.iccp_name.is_none() || info.iccp_profile.is_none() {
        return 83;
    }

    info.iccp_profile_size = profile_size;
    0
}
pub fn LodePNGText_copy(dest: &mut LodePNGInfo, source: &LodePNGInfo) -> u32 {
    dest.text_keys = None;
    dest.text_strings = None;
    dest.text_num = 0;

    if let (Some(keys), Some(strings)) = (&source.text_keys, &source.text_strings) {
        for i in 0..source.text_num {
            let key = keys.get(i).map(|s| CStr::from_bytes_with_nul(s.as_bytes()).unwrap());
            let string = strings.get(i).map(|s| CStr::from_bytes_with_nul(s.as_bytes()).unwrap());
            let error = lodepng_add_text(dest, key, string);
            if error != 0 {
                return error;
            }
        }
    }

    0
}
pub fn LodePNGUnknownChunks_copy(dest: &mut LodePNGInfo, src: &LodePNGInfo) -> u32 {
    LodePNGUnknownChunks_cleanup(dest);
    
    for i in 0..3 {
        dest.unknown_chunks_size[i] = src.unknown_chunks_size[i];
        
        if src.unknown_chunks_size[i] > 0 {
            // In Rust, we can directly clone the Vec<u8> if it exists
            dest.unknown_chunks_data[i] = src.unknown_chunks_data[i].clone();
            
            // If allocation failed (None case), return error code 83
            if dest.unknown_chunks_data[i].is_none() && dest.unknown_chunks_size[i] > 0 {
                return 83;
            }
        } else {
            dest.unknown_chunks_data[i] = None;
        }
    }
    
    0
}

pub fn lodepng_add_itext(
    info: &mut LodePNGInfo,
    key: Option<&CStr>,
    langtag: Option<&CStr>,
    transkey: Option<&CStr>,
    str: Option<&CStr>,
) -> u32 {
    lodepng_add_itext_sized(info, key, langtag, transkey, str.map(|s| s.to_bytes()), lodepng_strlen(str))
}
pub fn LodePNGIText_copy(dest: &mut LodePNGInfo, source: &LodePNGInfo) -> u32 {
    // Reset destination fields
    dest.itext_keys = None;
    dest.itext_langtags = None;
    dest.itext_transkeys = None;
    dest.itext_strings = None;
    dest.itext_num = 0;

    // Check if source has any itext entries
    if source.itext_num == 0 {
        return 0;
    }

    // Ensure source fields exist
    let Some(keys) = &source.itext_keys else { return 0 };
    let Some(langtags) = &source.itext_langtags else { return 0 };
    let Some(transkeys) = &source.itext_transkeys else { return 0 };
    let Some(strings) = &source.itext_strings else { return 0 };

    // Copy each itext entry
    for i in 0..source.itext_num {
        let key = CStr::from_bytes_with_nul(keys[i].as_bytes()).ok();
        let langtag = CStr::from_bytes_with_nul(langtags[i].as_bytes()).ok();
        let transkey = CStr::from_bytes_with_nul(transkeys[i].as_bytes()).ok();
        let string = CStr::from_bytes_with_nul(strings[i].as_bytes()).ok();

        let error = lodepng_add_itext(dest, key, langtag, transkey, string);
        if error != 0 {
            return error;
        }
    }

    0
}
pub fn lodepng_info_copy(dest: &mut LodePNGInfo, source: &LodePNGInfo) -> u32 {
    // Clean up destination first
    lodepng_info_cleanup(dest);
    
    // Copy basic fields (using clone since LodePNGInfo implements Clone)
    *dest = source.clone();
    
    // Initialize color mode and copy it separately (since it needs special handling)
    lodepng_color_mode_init(&mut dest.color);
    let error = lodepng_color_mode_copy(&mut dest.color, &source.color);
    if error != 0 {
        return error;
    }
    
    // Copy text chunks
    let error = LodePNGText_copy(dest, source);
    if error != 0 {
        return error;
    }
    
    // Copy international text chunks
    let error = LodePNGIText_copy(dest, source);
    if error != 0 {
        return error;
    }
    
    // Handle ICC profile if defined
    if source.iccp_defined != 0 {
        let name = source.iccp_name.as_ref().map(|s| s.as_str());
        let profile = source.iccp_profile.as_ref().map_or(&[] as &[u8], |v| v.as_slice());
        let error = lodepng_assign_icc(
            dest,
            name.map(|s| std::ffi::CStr::from_bytes_with_nul(s.as_bytes()).unwrap()),
            profile,
            source.iccp_profile_size,
        );
        if error != 0 {
            return error;
        }
    }
    
    // Initialize and copy unknown chunks
    LodePNGUnknownChunks_init(dest);
    let error = LodePNGUnknownChunks_copy(dest, source);
    if error != 0 {
        return error;
    }
    
    0 // Success
}
pub fn lodepng_chunk_init<'a>(chunk: &mut Option<&'a mut [u8]>, out: &'a mut Ucvector, length: usize, type_: &[u8]) -> u32 {
    let mut new_length = out.size;
    
    if lodepng_addofl(out.size, length, &mut Some(new_length)) {
        return 77;
    }
    if lodepng_addofl(new_length, 12, &mut Some(new_length)) {
        return 77;
    }
    if !ucvector_resize(out, new_length) {
        return 83;
    }
    
    // Calculate chunk position safely
    let data = out.data.as_mut().expect("ucvector should have data after resize");
    let chunk_start = new_length - length - 12;
    *chunk = Some(&mut data[chunk_start..chunk_start + length + 12]);
    
    if let Some(chunk_data) = chunk {
        lodepng_set32bitInt(&mut chunk_data[0..4], length as u32);
        lodepng_memcpy(&mut chunk_data[4..8], type_);
    }
    
    0
}
pub fn helper_addChunk_sBIT_1<'a>(out: &'a mut Ucvector, info: &LodePNGInfo, bitdepth: u32, chunk: &mut Option<&'a mut [u8]>) -> u32 {
    if info.sbit_r == 0 || info.sbit_a == 0 {
        return 115;
    }
    if info.sbit_r > bitdepth || info.sbit_a > bitdepth {
        return 115;
    }

    let error = lodepng_chunk_init(chunk, out, 2, b"sBIT");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = chunk {
        chunk_data[8] = info.sbit_r as u8;
        chunk_data[9] = info.sbit_a as u8;
    }

    0
}
pub fn lodepng_chunk_generate_crc(chunk: Option<&mut [u8]>) {
    // Check if chunk is None (equivalent to NULL check in C)
    if let Some(chunk) = chunk {
        let length = lodepng_chunk_length(Some(chunk)) as usize;
        
        // Calculate CRC for the chunk data (starting at index 4, length + 4 bytes)
        let crc = lodepng_crc32(Some(&chunk[4..4 + length + 4]), length + 4);
        
        // Write the CRC to the chunk (at position 8 + length)
        lodepng_set32bitInt(&mut chunk[8 + length..8 + length + 4], crc);
    }
}
pub fn helper_addChunk_sBIT_3<'a>(out: &'a mut Ucvector, info: &LodePNGInfo, bitdepth: u32, chunk: &mut Option<&'a mut [u8]>) -> u32 {
    if info.sbit_r == 0 || info.sbit_g == 0 || info.sbit_b == 0 {
        return 115;
    }
    if info.sbit_r > bitdepth || info.sbit_g > bitdepth || info.sbit_b > bitdepth {
        return 115;
    }

    let error = lodepng_chunk_init(chunk, out, 3, b"sBIT");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = chunk {
        chunk_data[8] = info.sbit_r as u8;
        chunk_data[9] = info.sbit_g as u8;
        chunk_data[10] = info.sbit_b as u8;
    }

    0
}
pub fn helper_addChunk_sBIT_2<'a>(out: &'a mut Ucvector, info: &LodePNGInfo, bitdepth: u32, chunk: &mut Option<&'a mut [u8]>) -> u32 {
    if info.sbit_r == 0 
        || info.sbit_g == 0 
        || info.sbit_b == 0 
        || info.sbit_a == 0 
        || info.sbit_r > bitdepth 
        || info.sbit_g > bitdepth 
        || info.sbit_b > bitdepth 
        || info.sbit_a > bitdepth 
    {
        return 115;
    }

    let error = lodepng_chunk_init(chunk, out, 4, b"sBIT");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = chunk {
        chunk_data[8] = info.sbit_r as u8;
        chunk_data[9] = info.sbit_g as u8;
        chunk_data[10] = info.sbit_b as u8;
        chunk_data[11] = info.sbit_a as u8;
    }

    0
}
pub fn addChunk_sBIT(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let bitdepth = match info.color.colortype {
        LodePNGColorType::LCT_PALETTE => 8,
        _ => info.color.bitdepth,
    };

    let mut chunk: Option<&mut [u8]> = None;

    match info.color.colortype {
        LodePNGColorType::LCT_GREY => {
            if info.sbit_r == 0 || info.sbit_r > bitdepth {
                return 115;
            }
            let error = lodepng_chunk_init(&mut chunk, out, 1, b"sBIT");
            if error != 0 {
                return error;
            }
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = info.sbit_r as u8;
            }
        },
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_PALETTE => {
            return helper_addChunk_sBIT_3(out, info, bitdepth, &mut chunk);
        },
        LodePNGColorType::LCT_GREY_ALPHA => {
            return helper_addChunk_sBIT_1(out, info, bitdepth, &mut chunk);
        },
        LodePNGColorType::LCT_RGBA => {
            return helper_addChunk_sBIT_2(out, info, bitdepth, &mut chunk);
        },
    }

    if chunk.is_some() {
        lodepng_chunk_generate_crc(chunk);
    }
    
    0
}
pub fn lodepng_chunk_createv(out: &mut Ucvector, length: usize, type_: &[u8], data: &[u8]) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    
    {
        let error = lodepng_chunk_init(&mut chunk, out, length, type_);
        if error != 0 {
            return error;
        }
    }
    
    if let Some(chunk_data) = &mut chunk {
        lodepng_memcpy(&mut chunk_data[8..8 + length], data);
        lodepng_chunk_generate_crc(Some(chunk_data));
    }
    
    0
}
pub fn addChunk_IEND(out: &mut Ucvector) -> u32 {
    lodepng_chunk_createv(out, 0, b"IEND", &[])
}
pub fn addChunk_sRGB(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let data = info.srgb_intent as u8;
    lodepng_chunk_createv(out, 1, b"sRGB", &[data])
}
pub fn writeSignature(out: &mut Ucvector) -> u32 {
    let pos = out.size;
    let signature: [u8; 8] = [137, 80, 78, 71, 13, 10, 26, 10];
    
    if !ucvector_resize(out, out.size + 8) {
        return 83;
    }
    
    if let Some(ref mut data) = out.data {
        lodepng_memcpy(&mut data[pos..pos + 8], &signature);
    }
    
    0
}
pub fn addChunk_iCCP(out: &mut Ucvector, info: &LodePNGInfo, zlibsettings: &LodePNGCompressSettings) -> u32 {
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Vec<u8>> = None;
    let mut compressedsize = 0;
    
    // Convert iccp_name to CStr for length calculation
    let iccp_name_cstr = info.iccp_name.as_ref().map(|s| std::ffi::CString::new(s.as_str()).unwrap());
    let keysize = lodepng_strlen(iccp_name_cstr.as_ref().map(|c| c.as_c_str()));
    
    if keysize < 1 || keysize > 79 {
        return 89;
    }
    
    if let Some(profile) = &info.iccp_profile {
        error = zlib_compress(&mut compressed, &mut compressedsize, profile, info.iccp_profile_size as usize, zlibsettings);
    } else {
        return 89; // No profile data
    }
    
    if error == 0 {
        let size = (keysize + 2) + compressedsize;
        error = lodepng_chunk_init(&mut chunk, out, size, b"iCCP");
    }
    
    if error == 0 {
        if let (Some(chunk_data), Some(name)) = (&mut chunk, &info.iccp_name) {
            // Copy name into chunk
            let name_bytes = name.as_bytes();
            lodepng_memcpy(&mut chunk_data[8..8 + keysize], &name_bytes[..keysize]);
            
            // Add null terminators
            chunk_data[8 + keysize] = 0;
            chunk_data[9 + keysize] = 0;
            
            // Copy compressed data
            if let Some(compressed_data) = &compressed {
                lodepng_memcpy(&mut chunk_data[10 + keysize..10 + keysize + compressedsize], compressed_data);
            }
            
            // Generate CRC
            lodepng_chunk_generate_crc(chunk);
        }
    }
    
    // Free compressed data (handled by Rust's drop)
    drop(compressed);
    
    error
}
pub fn addChunk_IHDR(out: &mut Ucvector, w: u32, h: u32, colortype: LodePNGColorType, bitdepth: u8, interlace_method: u8) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    
    {
        let error = lodepng_chunk_init(&mut chunk, out, 13, b"IHDR");
        if error != 0 {
            return error;
        }
    }
    
    if let Some(chunk_data) = &mut chunk {
        let data = &mut chunk_data[8..];
        
        lodepng_set32bitInt(&mut data[0..4], w);
        lodepng_set32bitInt(&mut data[4..8], h);
        data[8] = bitdepth;
        data[9] = colortype as u8;
        data[10] = 0;
        data[11] = 0;
        data[12] = interlace_method;
        
        lodepng_chunk_generate_crc(chunk);
    }
    
    0
}
pub fn lodepng_chunk_next<'a>(chunk: Option<&'a [u8]>, end: Option<&'a [u8]>) -> Option<&'a [u8]> {
    // Check if either chunk or end is None (equivalent to NULL in C)
    let chunk = chunk?;
    let end = end?;

    // Calculate available_size (end - chunk)
    let available_size = end.as_ptr() as usize - chunk.as_ptr() as usize;
    
    // Check conditions (chunk >= end or available_size < 12)
    if chunk.as_ptr() >= end.as_ptr() || available_size < 12 {
        return Some(end);
    }

    // Check PNG signature (first 8 bytes)
    if chunk.len() >= 8 && chunk[0..8] == [0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a] {
        return Some(&chunk[8..]);
    }

    // Calculate total_chunk_length
    let chunk_length = lodepng_chunk_length(Some(chunk)) as usize;
    let mut total_chunk_length = None;
    if lodepng_addofl(chunk_length, 12, &mut total_chunk_length) {
        return Some(end);
    }
    let total_chunk_length = total_chunk_length.unwrap();

    if total_chunk_length > available_size {
        return Some(end);
    }

    Some(&chunk[total_chunk_length..])
}
pub fn addUnknownChunks(out: &mut Ucvector, data: Option<&[u8]>, datasize: usize) -> u32 {
    let data = match data {
        Some(d) => d,
        None => return 77, // Invalid parameter error
    };

    let mut inchunk = data;
    let mut inchunk_idx = 0;

    while inchunk_idx < datasize {
        let error = {
            let chunk = if inchunk_idx < inchunk.len() {
                Some(&inchunk[inchunk_idx..])
            } else {
                None
            };
            // Convert Option<Vec<u8>> to Option<*mut u8> for the function call
            let mut out_data_ptr = out.data.as_mut().map(|v| v.as_mut_ptr());
            lodepng_chunk_append(&mut out_data_ptr, &mut out.size, chunk)
        };
        
        if error != 0 {
            return error;
        }

        out.allocsize = out.size;

        let next_chunk = lodepng_chunk_next(
            Some(&inchunk[inchunk_idx..]),
            Some(&data[datasize..])
        );
        
        match next_chunk {
            Some(new_chunk) => {
                inchunk_idx = new_chunk.as_ptr() as usize - data.as_ptr() as usize;
                inchunk = new_chunk;
            },
            None => break,
        }
    }

    0
}
pub fn helper_addChunk_iTXt_1(
    compress: bool,
    keyword: Option<&[u8]>,
    langtag: Option<&[u8]>,
    transkey: Option<&[u8]>,
    textstring: Option<&[u8]>,
    chunk: Option<&mut [u8]>,
    compressed: Option<&[u8]>,
    compressedsize: usize,
    textsize: usize,
    keysize: usize,
    langsize: usize,
    transsize: usize,
) {
    if let Some(chunk) = chunk {
        let mut pos = 8;
        
        // Copy keyword
        if let Some(keyword) = keyword {
            lodepng_memcpy(&mut chunk[pos..pos + keysize], &keyword[..keysize]);
            pos += keysize;
        }
        
        chunk[pos] = 0;
        pos += 1;
        chunk[pos] = if compress { 1 } else { 0 };
        pos += 1;
        chunk[pos] = 0;
        pos += 1;
        
        // Copy langtag
        if let Some(langtag) = langtag {
            lodepng_memcpy(&mut chunk[pos..pos + langsize], &langtag[..langsize]);
            pos += langsize;
        }
        
        chunk[pos] = 0;
        pos += 1;
        
        // Copy transkey
        if let Some(transkey) = transkey {
            lodepng_memcpy(&mut chunk[pos..pos + transsize], &transkey[..transsize]);
            pos += transsize;
        }
        
        chunk[pos] = 0;
        pos += 1;
        
        // Copy either compressed or textstring data
        if compress {
            if let Some(compressed) = compressed {
                lodepng_memcpy(&mut chunk[pos..pos + compressedsize], &compressed[..compressedsize]);
            }
        } else {
            if let Some(textstring) = textstring {
                lodepng_memcpy(&mut chunk[pos..pos + textsize], &textstring[..textsize]);
            }
        }
        
        lodepng_chunk_generate_crc(Some(chunk));
    }
}

pub fn addChunk_iTXt(
    out: &mut Ucvector,
    compress: bool,
    keyword: Option<&CStr>,
    langtag: Option<&CStr>,
    transkey: Option<&CStr>,
    textstring: Option<&CStr>,
    zlibsettings: &LodePNGCompressSettings,
) -> u32 {
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Vec<u8>> = None;
    let mut compressedsize = 0;
    
    let textsize = lodepng_strlen(textstring);
    let keysize = lodepng_strlen(keyword);
    let langsize = lodepng_strlen(langtag);
    let transsize = lodepng_strlen(transkey);

    if keysize < 1 || keysize > 79 {
        return 89;
    }

    if compress {
        if let Some(text) = textstring {
            error = zlib_compress(
                &mut compressed,
                &mut compressedsize,
                text.to_bytes(),
                textsize,
                zlibsettings,
            );
        }
    }

    if error == 0 {
        let size = (((((keysize + 3) + langsize) + 1) + transsize) + 1) + 
                   if compress { compressedsize } else { textsize };
        error = lodepng_chunk_init(&mut chunk, out, size, b"iTXt");
    }

    if error == 0 {
        helper_addChunk_iTXt_1(
            compress,
            keyword.map(|k| k.to_bytes()),
            langtag.map(|l| l.to_bytes()),
            transkey.map(|t| t.to_bytes()),
            textstring.map(|t| t.to_bytes()),
            chunk,
            compressed.as_deref(),
            compressedsize,
            textsize,
            keysize,
            langsize,
            transsize,
        );
    }

    lodepng_free(compressed.map(|v| v.into_boxed_slice().as_mut_ptr().cast()));

    error
}

pub fn addChunk_tEXt(out: &mut Ucvector, keyword: Option<&CStr>, textstring: Option<&CStr>) -> u32 {
    let keysize = lodepng_strlen(keyword);
    let textsize = lodepng_strlen(textstring);
    let size = (keysize + 1) + textsize;

    if keysize < 1 || keysize > 79 {
        return 89;
    }

    let mut chunk: Option<&mut [u8]> = None;
    let error = lodepng_chunk_init(&mut chunk, out, size, b"tEXt");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = &mut chunk {
        // Safe because we checked keysize is valid (1..=79)
        let keyword_bytes = keyword.unwrap().to_bytes();
        lodepng_memcpy(&mut chunk_data[8..8 + keysize], keyword_bytes);
        chunk_data[8 + keysize] = 0;

        let textstring_bytes = textstring.unwrap().to_bytes();
        lodepng_memcpy(&mut chunk_data[9 + keysize..9 + keysize + textsize], textstring_bytes);

        lodepng_chunk_generate_crc(chunk);
    }

    0
}
pub fn addChunk_PLTE(out: &mut Ucvector, info: &LodePNGColorMode) -> u32 {
    if info.palettesize == 0 || info.palettesize > 256 {
        return 68;
    }

    let mut chunk: Option<&mut [u8]> = None;
    let error = lodepng_chunk_init(&mut chunk, out, info.palettesize * 3, b"PLTE");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = &mut chunk {
        let palette = info.palette.as_ref().expect("palette should exist when palettesize > 0");
        let mut j = 8;
        
        for i in 0..info.palettesize {
            chunk_data[j] = palette[i * 4];
            j += 1;
            chunk_data[j] = palette[i * 4 + 1];
            j += 1;
            chunk_data[j] = palette[i * 4 + 2];
            j += 1;
        }
    }

    lodepng_chunk_generate_crc(chunk);
    0
}
pub fn addChunk_IDAT(
    out: &mut Ucvector,
    data: &[u8],
    datasize: usize,
    zlibsettings: &LodePNGCompressSettings,
) -> u32 {
    let mut zlib: Option<Vec<u8>> = None;
    let mut zlibsize: usize = 0;
    
    let error = zlib_compress(&mut zlib, &mut zlibsize, data, datasize, zlibsettings);
    if error == 0 {
        if let Some(zlib_data) = &zlib {
            let error = lodepng_chunk_createv(out, zlibsize, b"IDAT", zlib_data);
            if error != 0 {
                return error;
            }
        }
    }
    
    // Convert the Vec<u8> to a raw pointer for lodepng_free
    if let Some(zlib_vec) = zlib {
        let ptr = Box::into_raw(zlib_vec.into_boxed_slice()) as *mut std::ffi::c_void;
        lodepng_free(Some(ptr));
    }
    
    error
}
pub fn helper_addChunk_tRNS_1<'a>(out: &'a mut Ucvector, info: &LodePNGColorMode, chunk: &mut Option<&'a mut [u8]>) -> u32 {
    if info.key_defined != 0 {
        let error = lodepng_chunk_init(chunk, out, 6, b"tRNS");
        if error != 0 {
            return error;
        }

        if let Some(chunk_data) = chunk {
            chunk_data[8] = (info.key_r >> 8) as u8;
            chunk_data[9] = (info.key_r & 255) as u8;
            chunk_data[10] = (info.key_g >> 8) as u8;
            chunk_data[11] = (info.key_g & 255) as u8;
            chunk_data[12] = (info.key_b >> 8) as u8;
            chunk_data[13] = (info.key_b & 255) as u8;
        }
    }
    0
}
pub fn helper_addChunk_tRNS_2<'a>(out: &'a mut Ucvector, info: &LodePNGColorMode, chunk: &mut Option<&'a mut [u8]>) -> u32 {
    let mut amount = info.palettesize;
    
    // Iterate backwards through the palette to find non-opaque entries
    if let Some(palette) = &info.palette {
        for i in (0..info.palettesize).rev() {
            if palette.get(4 * i + 3).map_or(true, |&alpha| alpha != LCT_MAX_OCTET_VALUE) {
                break;
            }
            amount -= 1;
        }
    }

    if amount > 0 {
        // Initialize the chunk
        let error = lodepng_chunk_init(chunk, out, amount, b"tRNS");
        if error != 0 {
            return error;
        }

        // Copy alpha values to the chunk
        if let (Some(chunk_data), Some(palette)) = (chunk, &info.palette) {
            for i in 0..amount {
                if let Some(&alpha) = palette.get(4 * i + 3) {
                    chunk_data[8 + i] = alpha;
                }
            }
        }
    }
    
    0
}
pub fn addChunk_tRNS(out: &mut Ucvector, info: &LodePNGColorMode) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;

    match info.colortype {
        LodePNGColorType::LCT_PALETTE => {
            let error = helper_addChunk_tRNS_2(out, info, &mut chunk);
            if error != 0 {
                return error;
            }
        }
        LodePNGColorType::LCT_GREY => {
            if info.key_defined != 0 {
                let error = lodepng_chunk_init(&mut chunk, out, 2, b"tRNS");
                if error != 0 {
                    return error;
                }
                
                if let Some(chunk_data) = &mut chunk {
                    chunk_data[8] = (info.key_r >> 8) as u8;
                    chunk_data[9] = (info.key_r & 255) as u8;
                }
            }
        }
        LodePNGColorType::LCT_RGB => {
            let error = helper_addChunk_tRNS_1(out, info, &mut chunk);
            if error != 0 {
                return error;
            }
        }
        _ => {}
    }

    if let Some(chunk_data) = chunk {
        lodepng_chunk_generate_crc(Some(chunk_data));
    }

    0
}
pub fn addChunk_bKGD(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    
    match info.color.colortype {
        LodePNGColorType::LCT_GREY | LodePNGColorType::LCT_GREY_ALPHA => {
            let error = lodepng_chunk_init(&mut chunk, out, 2, b"bKGD");
            if error != 0 {
                return error;
            }
            
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = (info.background_r >> 8) as u8;
                chunk_data[9] = (info.background_r & 255) as u8;
            }
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA => {
            let error = lodepng_chunk_init(&mut chunk, out, 6, b"bKGD");
            if error != 0 {
                return error;
            }
            
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = (info.background_r >> 8) as u8;
                chunk_data[9] = (info.background_r & 255) as u8;
                chunk_data[10] = (info.background_g >> 8) as u8;
                chunk_data[11] = (info.background_g & 255) as u8;
                chunk_data[12] = (info.background_b >> 8) as u8;
                chunk_data[13] = (info.background_b & 255) as u8;
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            let error = lodepng_chunk_init(&mut chunk, out, 1, b"bKGD");
            if error != 0 {
                return error;
            }
            
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = (info.background_r & 255) as u8;
            }
        }
    }
    
    if chunk.is_some() {
        lodepng_chunk_generate_crc(chunk);
    }
    
    0
}
pub fn addChunk_tIME(out: &mut Ucvector, time: &LodePNGTime) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 7, b"tIME");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_data) = &mut chunk {
        chunk_data[8] = (time.year >> 8) as u8;
        chunk_data[9] = (time.year & 255) as u8;
        chunk_data[10] = time.month as u8;
        chunk_data[11] = time.day as u8;
        chunk_data[12] = time.hour as u8;
        chunk_data[13] = time.minute as u8;
        chunk_data[14] = time.second as u8;
    }

    lodepng_chunk_generate_crc(chunk);
    0
}

pub fn addChunk_zTXt(
    out: &mut Ucvector,
    keyword: Option<&CStr>,
    textstring: Option<&CStr>,
    zlibsettings: &LodePNGCompressSettings,
) -> u32 {
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Vec<u8>> = None;
    let mut compressedsize = 0;
    
    let textsize = lodepng_strlen(textstring);
    let keysize = lodepng_strlen(keyword);
    
    if keysize < 1 || keysize > 79 {
        return 89;
    }
    
    let textstring_bytes = textstring.unwrap().to_bytes();
    error = zlib_compress(&mut compressed, &mut compressedsize, textstring_bytes, textsize, zlibsettings);
    
    if error == 0 {
        let size = (keysize + 2) + compressedsize;
        error = lodepng_chunk_init(&mut chunk, out, size, b"zTXt");
    }
    
    if error == 0 {
        if let Some(chunk_data) = &mut chunk {
            let keyword_bytes = keyword.unwrap().to_bytes();
            lodepng_memcpy(&mut chunk_data[8..8 + keysize], keyword_bytes);
            chunk_data[8 + keysize] = 0;
            chunk_data[9 + keysize] = 0;
            lodepng_memcpy(&mut chunk_data[10 + keysize..10 + keysize + compressedsize], compressed.as_ref().unwrap());
            lodepng_chunk_generate_crc(Some(chunk_data));
        }
    }
    
    lodepng_free(compressed.map(|v| Box::into_raw(v.into_boxed_slice()) as *mut std::ffi::c_void));
    error
}

pub fn helper_helper_lodepng_encode_3_1(
    state: &mut LodePNGState,
    outv: &mut Ucvector,
    info: &LodePNGInfo,
    i: usize,
) {
    // Convert String to CStr for length checking
    let key_cstr = info.text_keys.as_ref().and_then(|keys| keys.get(i))
        .map(|s| CStr::from_bytes_with_nul(s.as_bytes()).unwrap());
    let text_cstr = info.text_strings.as_ref().and_then(|texts| texts.get(i))
        .map(|s| CStr::from_bytes_with_nul(s.as_bytes()).unwrap());

    let key_len = lodepng_strlen(key_cstr);
    if key_len > 79 {
        state.error = 66;
        return;
    }
    if key_len < 1 {
        state.error = 67;
        return;
    }

    if state.encoder.text_compression != 0 {
        state.error = addChunk_zTXt(
            outv,
            key_cstr,
            text_cstr,
            &state.encoder.zlibsettings,
        );
    } else {
        state.error = addChunk_tEXt(
            outv,
            key_cstr,
            text_cstr,
        );
    }
}
pub fn addChunk_pHYs(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 9, b"pHYs");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_data) = &mut chunk {
        lodepng_set32bitInt(&mut chunk_data[8..12], info.phys_x);
        lodepng_set32bitInt(&mut chunk_data[12..16], info.phys_y);
        chunk_data[16] = info.phys_unit as u8;
        lodepng_chunk_generate_crc(chunk);
    }

    0
}
pub fn addChunk_gAMA(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    
    {
        let error = lodepng_chunk_init(&mut chunk, out, 4, b"gAMA");
        if error != 0 {
            return error;
        }
    }
    
    if let Some(chunk_data) = &mut chunk {
        lodepng_set32bitInt(&mut chunk_data[8..12], info.gama_gamma);
        lodepng_chunk_generate_crc(chunk);
    }
    
    0
}
pub fn addChunk_cHRM(out: &mut Ucvector, info: &LodePNGInfo) -> u32 {
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 32, b"cHRM");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_data) = &mut chunk {
        lodepng_set32bitInt(&mut chunk_data[8..12], info.chrm_white_x);
        lodepng_set32bitInt(&mut chunk_data[12..16], info.chrm_white_y);
        lodepng_set32bitInt(&mut chunk_data[16..20], info.chrm_red_x);
        lodepng_set32bitInt(&mut chunk_data[20..24], info.chrm_red_y);
        lodepng_set32bitInt(&mut chunk_data[24..28], info.chrm_green_x);
        lodepng_set32bitInt(&mut chunk_data[28..32], info.chrm_green_y);
        lodepng_set32bitInt(&mut chunk_data[32..36], info.chrm_blue_x);
        lodepng_set32bitInt(&mut chunk_data[36..40], info.chrm_blue_y);
    }

    lodepng_chunk_generate_crc(chunk);
    0
}
pub fn helper_lodepng_encode_3(
    w: u32,
    h: u32,
    state: &mut LodePNGState,
    data: &[u8],
    datasize: usize,
    outv: &mut Ucvector,
    info: &LodePNGInfo,
    info_png: &LodePNGInfo,
) {
    // Write signature
    state.error = writeSignature(outv);
    if state.error != 0 {
        return;
    }

    // Add IHDR chunk
    state.error = addChunk_IHDR(
        outv,
        w,
        h,
        info.color.colortype,
        info.color.bitdepth as u8,
        info.interlace_method as u8,
    );
    if state.error != 0 {
        return;
    }

    // Add unknown chunks if present
    if let Some(unknown_data) = &info.unknown_chunks_data[0] {
        state.error = addUnknownChunks(outv, Some(unknown_data), info.unknown_chunks_size[0]);
        if state.error != 0 {
            return;
        }
    }

    // Add various optional chunks based on info flags
    if info.iccp_defined != 0 {
        state.error = addChunk_iCCP(outv, info, &state.encoder.zlibsettings);
        if state.error != 0 {
            return;
        }
    }

    if info.srgb_defined != 0 {
        state.error = addChunk_sRGB(outv, info);
        if state.error != 0 {
            return;
        }
    }

    if info.gama_defined != 0 {
        state.error = addChunk_gAMA(outv, info);
        if state.error != 0 {
            return;
        }
    }

    if info.chrm_defined != 0 {
        state.error = addChunk_cHRM(outv, info);
        if state.error != 0 {
            return;
        }
    }

    if info_png.sbit_defined != 0 {
        state.error = addChunk_sBIT(outv, info);
        if state.error != 0 {
            return;
        }
    }

    // Add PLTE chunk if needed
    if info.color.colortype == LodePNGColorType::LCT_PALETTE {
        state.error = addChunk_PLTE(outv, &info.color);
        if state.error != 0 {
            return;
        }
    }

    if state.encoder.force_palette != 0
        && (info.color.colortype == LodePNGColorType::LCT_RGB
            || info.color.colortype == LodePNGColorType::LCT_RGBA)
    {
        state.error = addChunk_PLTE(outv, &info.color);
        if state.error != 0 {
            return;
        }
    }

    // Add tRNS chunk
    state.error = addChunk_tRNS(outv, &info.color);
    if state.error != 0 {
        return;
    }

    // Add bKGD chunk if defined
    if info.background_defined != 0 {
        state.error = addChunk_bKGD(outv, info);
        if state.error != 0 {
            return;
        }
    }

    // Add pHYs chunk if defined
    if info.phys_defined != 0 {
        state.error = addChunk_pHYs(outv, info);
        if state.error != 0 {
            return;
        }
    }

    // Add second set of unknown chunks if present
    if let Some(unknown_data) = &info.unknown_chunks_data[1] {
        state.error = addUnknownChunks(outv, Some(unknown_data), info.unknown_chunks_size[1]);
        if state.error != 0 {
            return;
        }
    }

    // Add IDAT chunk with compressed image data
    state.error = addChunk_IDAT(outv, data, datasize, &state.encoder.zlibsettings);
    if state.error != 0 {
        return;
    }

    // Add tIME chunk if defined
    if info.time_defined != 0 {
        state.error = addChunk_tIME(outv, &info.time);
        if state.error != 0 {
            return;
        }
    }

    // Add text chunks
    for i in 0..info.text_num {
        helper_helper_lodepng_encode_3_1(state, outv, info, i);
        if state.error != 0 {
            return;
        }
    }

    // Add LodePNG identifier text if requested
    if state.encoder.add_id != 0 {
        let mut already_added_id_text = false;

        if let Some(keys) = &info.text_keys {
            for key in keys.iter().take(info.text_num) {
                if key == "LodePNG" {
                    already_added_id_text = true;
                    break;
                }
            }
        }

        if !already_added_id_text {
            state.error = addChunk_tEXt(
                outv,
                Some(std::ffi::CStr::from_bytes_with_nul(b"LodePNG\0").unwrap()),
                Some(std::ffi::CStr::from_bytes_with_nul(LODEPNG_VERSION_STRING.as_bytes()).unwrap()),
            );
            if state.error != 0 {
                return;
            }
        }
    }

    // Add iTXt chunks
    for i in 0..info.itext_num {
        if let Some(keys) = &info.itext_keys {
            if keys[i].len() > 79 {
                state.error = 66;
                return;
            }
            if keys[i].is_empty() {
                state.error = 67;
                return;
            }
        }

        state.error = addChunk_iTXt(
            outv,
            state.encoder.text_compression != 0,
            info.itext_keys.as_ref().and_then(|keys| keys.get(i))
                .map(|s| std::ffi::CStr::from_bytes_with_nul(s.as_bytes()).unwrap()),
            info.itext_langtags.as_ref().and_then(|tags| tags.get(i))
                .map(|s| std::ffi::CStr::from_bytes_with_nul(s.as_bytes()).unwrap()),
            info.itext_transkeys.as_ref().and_then(|keys| keys.get(i))
                .map(|s| std::ffi::CStr::from_bytes_with_nul(s.as_bytes()).unwrap()),
            info.itext_strings.as_ref().and_then(|strings| strings.get(i))
                .map(|s| std::ffi::CStr::from_bytes_with_nul(s.as_bytes()).unwrap()),
            &state.encoder.zlibsettings,
        );
        if state.error != 0 {
            return;
        }
    }

    // Add third set of unknown chunks if present
    if let Some(unknown_data) = &info.unknown_chunks_data[2] {
        state.error = addUnknownChunks(outv, Some(unknown_data), info.unknown_chunks_size[2]);
        if state.error != 0 {
            return;
        }
    }

    // Finally add IEND chunk
    state.error = addChunk_IEND(outv);
}
pub fn helper_helper_lodepng_encode_2_1(allow_convert_ref: &mut u32, info: LodePNGInfo, info_png: &LodePNGInfo, auto_color: LodePNGColorMode) {
    let sbit_max = *[
        info_png.sbit_r,
        info_png.sbit_g,
        info_png.sbit_b,
        info_png.sbit_a,
    ].iter().max().unwrap_or(&0);

    let equal = ((info_png.sbit_g == 0 || info_png.sbit_g == info_png.sbit_r) &&
                 (info_png.sbit_b == 0 || info_png.sbit_b == info_png.sbit_r)) &&
                (info_png.sbit_a == 0 || info_png.sbit_a == info_png.sbit_r);

    let mut allow_convert = 0;

    if info.color.colortype == LodePNGColorType::LCT_PALETTE && auto_color.colortype == LodePNGColorType::LCT_PALETTE {
        allow_convert = 1;
    }
    if info.color.colortype == LodePNGColorType::LCT_RGB && 
       auto_color.colortype == LodePNGColorType::LCT_PALETTE && 
       sbit_max <= 8 {
        allow_convert = 1;
    }
    if info.color.colortype == LodePNGColorType::LCT_RGBA && 
       auto_color.colortype == LodePNGColorType::LCT_PALETTE && 
       info_png.sbit_a == 8 && 
       sbit_max <= 8 {
        allow_convert = 1;
    }
    if (info.color.colortype == LodePNGColorType::LCT_RGB || info.color.colortype == LodePNGColorType::LCT_RGBA) && 
       info.color.bitdepth == 16 && 
       auto_color.colortype == info.color.colortype && 
       auto_color.bitdepth == 8 && 
       sbit_max <= 8 {
        allow_convert = 1;
    }
    if info.color.colortype != LodePNGColorType::LCT_PALETTE && 
       auto_color.colortype != LodePNGColorType::LCT_PALETTE && 
       equal && 
       info_png.sbit_r == auto_color.bitdepth {
        allow_convert = 1;
    }

    *allow_convert_ref = allow_convert;
}
pub fn lodepng_color_mode_make(colortype: LodePNGColorType, bitdepth: u32) -> LodePNGColorMode {
    let mut result = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA, // Default value, will be overwritten
        bitdepth: 8, // Default value, will be overwritten
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut result);
    result.colortype = colortype;
    result.bitdepth = bitdepth;
    result
}
pub fn lodepng_convert_rgb(
    r_out: Option<&mut u32>,
    g_out: Option<&mut u32>,
    b_out: Option<&mut u32>,
    r_in: u32,
    g_in: u32,
    b_in: u32,
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
) -> u32 {
    let mut r = 0;
    let mut g = 0;
    let mut b = 0;
    let mul = 65535 / ((1u32 << mode_in.bitdepth) - 1u32);
    let shift = 16 - mode_out.bitdepth;

    match mode_in.colortype {
        LodePNGColorType::LCT_GREY | LodePNGColorType::LCT_GREY_ALPHA => {
            r = r_in * mul;
            g = r;
            b = r;
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA => {
            r = r_in * mul;
            g = g_in * mul;
            b = b_in * mul;
        }
        LodePNGColorType::LCT_PALETTE => {
            if r_in >= mode_in.palettesize as u32 {
                return 82;
            }
            if let Some(palette) = &mode_in.palette {
                r = palette[(r_in * 4) as usize] as u32 * 257u32;
                g = palette[(r_in * 4 + 1) as usize] as u32 * 257u32;
                b = palette[(r_in * 4 + 2) as usize] as u32 * 257u32;
            } else {
                return 31;
            }
        }
        _ => return 31,
    }

    match mode_out.colortype {
        LodePNGColorType::LCT_GREY | LodePNGColorType::LCT_GREY_ALPHA => {
            if let Some(r_out) = r_out {
                *r_out = r >> shift;
            }
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA => {
            if let Some(r_out) = r_out {
                *r_out = r >> shift;
            }
            if let Some(g_out) = g_out {
                *g_out = g >> shift;
            }
            if let Some(b_out) = b_out {
                *b_out = b >> shift;
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            if ((r >> 8) != (r & 255)) || ((g >> 8) != (g & 255)) || ((b >> 8) != (b & 255)) {
                return 82;
            }
            if let Some(palette) = &mode_out.palette {
                for i in 0..mode_out.palettesize {
                    let j = i * 4;
                    if (r >> 8) == palette[j] as u32
                        && (g >> 8) == palette[j + 1] as u32
                        && (b >> 8) == palette[j + 2] as u32
                    {
                        if let Some(r_out) = r_out {
                            *r_out = i as u32;
                        }
                        return 0;
                    }
                }
            }
            return 82;
        }
        _ => return 31,
    }

    0
}
pub fn lodepng_has_palette_alpha(info: &LodePNGColorMode) -> u32 {
    // Check if palette exists and has entries
    if let Some(palette) = &info.palette {
        // Iterate through each palette entry (4 bytes per entry: R,G,B,A)
        for i in 0..info.palettesize {
            // Check alpha channel (4th byte of each entry)
            if palette[i * 4 + 3] < LCT_MAX_OCTET_VALUE {
                return 1;
            }
        }
    }
    0
}
pub fn lodepng_is_alpha_type(info: &LodePNGColorMode) -> bool {
    (info.colortype as u32 & 4) != 0
}
pub fn lodepng_can_have_alpha(info: &LodePNGColorMode) -> u32 {
    (info.key_defined != 0 || lodepng_is_alpha_type(info) || lodepng_has_palette_alpha(info) != 0) as u32
}
pub fn helper_helper_lodepng_compute_color_stats_2_1(
    colored_done_ref: &mut u32,
    alpha_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    mode_in: &LodePNGColorMode,
    numcolors_done: u32,
    bits_done: u32,
    i: usize,
    mut r: u16,
    mut g: u16,
    mut b: u16,
    mut a: u16,
) {
    let mut colored_done = *colored_done_ref;
    let mut alpha_done = *alpha_done_ref;

    getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);

    if !colored_done != 0 && (r != g || r != b) {
        stats.colored = 1;
        colored_done = 1;
    }

    if alpha_done == 0 {
        let matchkey = (r == stats.key_r) && (g == stats.key_g) && (b == stats.key_b);
        if a != 65535 && (a != 0 || (stats.key != 0 && !matchkey)) {
            stats.alpha = 1;
            stats.key = 0;
            alpha_done = 1;
        } else if a == 0 && stats.alpha == 0 && stats.key == 0 {
            stats.key = 1;
            stats.key_r = r;
            stats.key_g = g;
            stats.key_b = b;
        } else if a == 65535 && stats.key != 0 && matchkey {
            stats.alpha = 1;
            stats.key = 0;
            alpha_done = 1;
        }
    }

    if alpha_done != 0 && numcolors_done != 0 && colored_done != 0 && bits_done != 0 {
        return;
    }

    *colored_done_ref = colored_done;
    *alpha_done_ref = alpha_done;
}
pub fn helper_lodepng_compute_color_stats_2(
    i_ref: &mut usize,
    colored_done_ref: &mut u32,
    alpha_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    mode_in: &LodePNGColorMode,
    numpixels: usize,
    numcolors_done: u32,
    bits_done: u32,
) {
    let mut i = *i_ref;
    let mut colored_done = *colored_done_ref;
    let mut alpha_done = *alpha_done_ref;
    let mut r = 0;
    let mut g = 0;
    let mut b = 0;
    let mut a = 0;

    for i in 0..numpixels {
        helper_helper_lodepng_compute_color_stats_2_1(
            &mut colored_done,
            &mut alpha_done,
            stats,
            in_data,
            mode_in,
            numcolors_done,
            bits_done,
            i,
            r,
            g,
            b,
            a,
        );
    }

    if stats.key != 0 && stats.alpha == 0 {
        for i in 0..numpixels {
            getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            if a != 0 && r == stats.key_r && g == stats.key_g && b == stats.key_b {
                stats.alpha = 1;
                stats.key = 0;
                alpha_done = 1;
            }
        }
    }

    *i_ref = i;
    *colored_done_ref = colored_done;
    *alpha_done_ref = alpha_done;
}
pub fn helper_lodepng_compute_color_stats_1(
    i_ref: &mut usize,
    numcolors_done_ref: &mut u32,
    bits_done_ref: &mut u32,
    sixteen_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    mode_in: &LodePNGColorMode,
    numpixels: usize,
) {
    let mut i = *i_ref;
    let mut numcolors_done = *numcolors_done_ref;
    let mut bits_done = *bits_done_ref;
    let mut sixteen = *sixteen_ref;
    let mut r = 0u16;
    let mut g = 0u16;
    let mut b = 0u16;
    let mut a = 0u16;

    for i in 0..numpixels {
        getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
        if ((r & 255) != ((r >> 8) & 255))
            || ((g & 255) != ((g >> 8) & 255))
            || ((b & 255) != ((b >> 8) & 255))
            || ((a & 255) != ((a >> 8) & 255))
        {
            stats.bits = 16;
            sixteen = 1;
            bits_done = 1;
            numcolors_done = 1;
            break;
        }
    }

    *i_ref = i;
    *numcolors_done_ref = numcolors_done;
    *bits_done_ref = bits_done;
    *sixteen_ref = sixteen;
}
pub fn lodepng_is_greyscale_type(info: &LodePNGColorMode) -> bool {
    info.colortype == LodePNGColorType::LCT_GREY || info.colortype == LodePNGColorType::LCT_GREY_ALPHA
}
pub fn helper_helper_helper_lodepng_compute_color_stats_3_1_2(
    alpha_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) {
    let mut alpha_done = *alpha_done_ref;
    let matchkey = (r as u16 == stats.key_r) && (g as u16 == stats.key_g) && (b as u16 == stats.key_b);

    if (a != 255) && ((a != 0) || (stats.key != 0 && !matchkey)) {
        stats.alpha = 1;
        stats.key = 0;
        alpha_done = 1;
        if stats.bits < 8 {
            stats.bits = 8;
        }
    } else if (a == 0) && (stats.alpha == 0) && (stats.key == 0) {
        stats.key = 1;
        stats.key_r = r as u16;
        stats.key_g = g as u16;
        stats.key_b = b as u16;
    } else if (a == 255) && (stats.key != 0) && matchkey {
        stats.alpha = 1;
        stats.key = 0;
        alpha_done = 1;
        if stats.bits < 8 {
            stats.bits = 8;
        }
    }

    *alpha_done_ref = alpha_done;
}
pub fn color_tree_has(tree: &ColorTree, r: u8, g: u8, b: u8, a: u8) -> bool {
    color_tree_get(tree, r, g, b, a) >= 0
}
pub fn helper_helper_helper_lodepng_compute_color_stats_3_1_1(
    error_ref: &mut u32,
    numcolors_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    mut tree: ColorTree,
    maxnumcolors: u32,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) {
    let mut error = *error_ref;
    let mut numcolors_done = *numcolors_done_ref;

    if !color_tree_has(&tree, r, g, b, a) {
        error = color_tree_add(&mut tree, r, g, b, a, stats.numcolors);
        if error != 0 {
            *error_ref = error;
            *numcolors_done_ref = numcolors_done;
            return;
        }

        if stats.numcolors < 256 {
            let n = stats.numcolors;
            stats.palette[(n * 4) as usize] = r;
            stats.palette[(n * 4 + 1) as usize] = g;
            stats.palette[(n * 4 + 2) as usize] = b;
            stats.palette[(n * 4 + 3) as usize] = a;
        }

        stats.numcolors += 1;
        numcolors_done = if stats.numcolors >= maxnumcolors { 1 } else { 0 };
    }

    *error_ref = error;
    *numcolors_done_ref = numcolors_done;
}
pub fn helper_helper_lodepng_compute_color_stats_3_1(
    error_ref: &mut u32,
    colored_done_ref: &mut u32,
    alpha_done_ref: &mut u32,
    numcolors_done_ref: &mut u32,
    bits_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    mode_in: &LodePNGColorMode,
    mut tree: ColorTree,
    bpp: u32,
    maxnumcolors: u32,
    i: usize,
    mut r: u8,
    mut g: u8,
    mut b: u8,
    mut a: u8,
) {
    let mut error = *error_ref;
    let mut colored_done = *colored_done_ref;
    let mut alpha_done = *alpha_done_ref;
    let mut numcolors_done = *numcolors_done_ref;
    let mut bits_done = *bits_done_ref;

    getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);

    if (bits_done == 0) && (stats.bits < 8) {
        let bits = u32::from(getValueRequiredBits(r));
        if bits > stats.bits {
            stats.bits = bits;
        }
    }
    bits_done = if stats.bits >= bpp { 1 } else { 0 };

    if (colored_done == 0) && ((r != g) || (r != b)) {
        stats.colored = 1;
        colored_done = 1;
        if stats.bits < 8 {
            stats.bits = 8;
        }
    }

    if alpha_done == 0 {
        helper_helper_helper_lodepng_compute_color_stats_3_1_2(&mut alpha_done, stats, r, g, b, a);
    }

    if numcolors_done == 0 {
        helper_helper_helper_lodepng_compute_color_stats_3_1_1(
            &mut error,
            &mut numcolors_done,
            stats,
            tree,
            maxnumcolors,
            r,
            g,
            b,
            a,
        );
    }

    if (alpha_done != 0) && (numcolors_done != 0) && (colored_done != 0) && (bits_done != 0) {
        return;
    }

    *error_ref = error;
    *colored_done_ref = colored_done;
    *alpha_done_ref = alpha_done;
    *numcolors_done_ref = numcolors_done;
    *bits_done_ref = bits_done;
}
pub fn helper_lodepng_compute_color_stats_3(
    i_ref: &mut usize,
    error_ref: &mut u32,
    colored_done_ref: &mut u32,
    alpha_done_ref: &mut u32,
    numcolors_done_ref: &mut u32,
    bits_done_ref: &mut u32,
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    mode_in: &LodePNGColorMode,
    tree: ColorTree,
    numpixels: usize,
    bpp: u32,
    maxnumcolors: u32,
) {
    let mut i = *i_ref;
    let mut error = *error_ref;
    let mut colored_done = *colored_done_ref;
    let mut alpha_done = *alpha_done_ref;
    let mut numcolors_done = *numcolors_done_ref;
    let mut bits_done = *bits_done_ref;
    let mut r = 0u8;
    let mut g = 0u8;
    let mut b = 0u8;
    let mut a = 0u8;

    for i in 0..numpixels {
        helper_helper_lodepng_compute_color_stats_3_1(
            &mut error,
            &mut colored_done,
            &mut alpha_done,
            &mut numcolors_done,
            &mut bits_done,
            stats,
            in_data,
            mode_in,
            tree.clone(),
            bpp,
            maxnumcolors,
            i,
            r,
            g,
            b,
            a,
        );
    }

    if stats.key != 0 && stats.alpha == 0 {
        for i in 0..numpixels {
            getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            if a != 0 && r as u16 == stats.key_r && g as u16 == stats.key_g && b as u16 == stats.key_b {
                stats.alpha = 1;
                stats.key = 0;
                alpha_done = 1;
                if stats.bits < 8 {
                    stats.bits = 8;
                }
            }
        }
    }

    stats.key_r = stats.key_r.wrapping_add(stats.key_r << 8);
    stats.key_g = stats.key_g.wrapping_add(stats.key_g << 8);
    stats.key_b = stats.key_b.wrapping_add(stats.key_b << 8);

    *i_ref = i;
    *error_ref = error;
    *colored_done_ref = colored_done;
    *alpha_done_ref = alpha_done;
    *numcolors_done_ref = numcolors_done;
    *bits_done_ref = bits_done;
}
pub fn lodepng_compute_color_stats(
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    w: u32,
    h: u32,
    mode_in: &LodePNGColorMode,
) -> u32 {
    let mut tree = ColorTree {
        children: [
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
        ],
        index: -1,
    };
    let numpixels = (w as usize) * (h as usize);
    let mut error = 0;
    let mut colored_done = if lodepng_is_greyscale_type(mode_in) { 1 } else { 0 };
    let mut alpha_done = if lodepng_can_have_alpha(mode_in) != 0 { 0 } else { 1 };
    let mut numcolors_done = 0;
    let bpp = lodepng_get_bpp(mode_in) as u32;
    let mut bits_done = if stats.bits == 1 && bpp == 1 { 1 } else { 0 };
    let mut sixteen = 0;
    let mut maxnumcolors = 257;
    
    if bpp <= 8 {
        maxnumcolors = 257.min(stats.numcolors + (1u32 << bpp));
    }
    
    stats.numpixels += numpixels;
    
    if stats.allow_palette == 0 {
        numcolors_done = 1;
    }
    
    color_tree_init(&mut tree);
    
    if stats.alpha != 0 {
        alpha_done = 1;
    }
    if stats.colored != 0 {
        colored_done = 1;
    }
    if stats.bits == 16 {
        numcolors_done = 1;
    }
    if stats.bits >= bpp {
        bits_done = 1;
    }
    if stats.numcolors >= maxnumcolors {
        numcolors_done = 1;
    }
    
    if numcolors_done == 0 {
        for i in 0..stats.numcolors {
            let color = &stats.palette[(i * 4) as usize..];
            error = color_tree_add(&mut tree, color[0], color[1], color[2], color[3], i);
            if error != 0 {
                color_tree_cleanup(&mut tree);
                return error;
            }
        }
    }
    
    let mut i = 0;
    if mode_in.bitdepth == 16 && sixteen == 0 {
        helper_lodepng_compute_color_stats_1(
            &mut i,
            &mut numcolors_done,
            &mut bits_done,
            &mut sixteen,
            stats,
            in_data,
            mode_in,
            numpixels,
        );
    }
    
    if sixteen != 0 {
        helper_lodepng_compute_color_stats_2(
            &mut i,
            &mut colored_done,
            &mut alpha_done,
            stats,
            in_data,
            mode_in,
            numpixels,
            numcolors_done,
            bits_done,
        );
    } else {
        helper_lodepng_compute_color_stats_3(
            &mut i,
            &mut error,
            &mut colored_done,
            &mut alpha_done,
            &mut numcolors_done,
            &mut bits_done,
            stats,
            in_data,
            mode_in,
            tree.clone(),
            numpixels,
            bpp,
            maxnumcolors,
        );
    }
    
    color_tree_cleanup(&mut tree);
    error
}
pub fn lodepng_color_stats_add(stats: &mut LodePNGColorStats, r: u16, g: u16, b: u16, a: u16) -> u32 {
    let mut image = [0u8; 8];
    image[0] = (r >> 8) as u8;
    image[1] = r as u8;
    image[2] = (g >> 8) as u8;
    image[3] = g as u8;
    image[4] = (b >> 8) as u8;
    image[5] = b as u8;
    image[6] = (a >> 8) as u8;
    image[7] = a as u8;

    let mut mode = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 16,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    let error = lodepng_compute_color_stats(stats, &image, 1, 1, &mode);
    lodepng_color_mode_cleanup(&mut mode);
    error
}
pub fn lodepng_color_stats_init(stats: &mut LodePNGColorStats) {
    stats.colored = 0;
    stats.key = 0;
    stats.key_r = 0;
    stats.key_g = 0;
    stats.key_b = 0;
    stats.alpha = 0;
    stats.numcolors = 0;
    stats.bits = 1;
    stats.numpixels = 0;
    stats.allow_palette = 1;
    stats.allow_greyscale = 1;
}
pub fn lodepng_palette_add(
    info: &mut LodePNGColorMode,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) -> u32 {
    if info.palette.is_none() {
        lodepng_color_mode_alloc_palette(info);
        if info.palette.is_none() {
            return 83;
        }
    }
    
    if info.palettesize >= 256 {
        return 108;
    }

    if let Some(palette) = &mut info.palette {
        let index = 4 * info.palettesize;
        palette[index] = r;
        palette[index + 1] = g;
        palette[index + 2] = b;
        palette[index + 3] = a;
    }
    
    info.palettesize += 1;
    0
}
pub fn helper_auto_choose_color_1(
    error_ref: &mut u32,
    i_ref: &mut usize,
    mode_out: &mut LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    stats: &LodePNGColorStats,
    palettebits: u32,
) {
    let mut error = *error_ref;
    let mut i = *i_ref;
    let p = &stats.palette;

    lodepng_palette_clear(mode_out);

    for i in 0..stats.numcolors as usize {
        error = lodepng_palette_add(
            mode_out,
            p[i * 4],
            p[i * 4 + 1],
            p[i * 4 + 2],
            p[i * 4 + 3],
        );
        if error != 0 {
            break;
        }
    }

    mode_out.colortype = LodePNGColorType::LCT_PALETTE;
    mode_out.bitdepth = palettebits;

    if mode_in.colortype == LodePNGColorType::LCT_PALETTE
        && mode_in.palettesize >= mode_out.palettesize
        && mode_in.bitdepth == mode_out.bitdepth
    {
        lodepng_color_mode_cleanup(mode_out);
        lodepng_color_mode_copy(mode_out, mode_in);
    }

    *error_ref = error;
    *i_ref = i;
}
pub fn auto_choose_color(
    mode_out: &mut LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    stats: &LodePNGColorStats,
) -> u32 {
    let mut error = 0;
    let palettebits;
    let n;
    let numpixels = stats.numpixels;
    let mut palette_ok;
    let mut gray_ok;
    let mut alpha = stats.alpha != 0;
    let mut key = stats.key != 0;
    let mut bits = stats.bits;

    mode_out.key_defined = 0;

    if key && (numpixels <= 16) {
        alpha = true;
        key = false;
        if bits < 8 {
            bits = 8;
        }
    }

    gray_ok = stats.colored == 0;
    if stats.allow_greyscale == 0 {
        gray_ok = false;
    }
    if !gray_ok && (bits < 8) {
        bits = 8;
    }

    n = stats.numcolors;
    palettebits = if n <= 2 {
        1
    } else if n <= 4 {
        2
    } else if n <= 16 {
        4
    } else {
        8
    };

    palette_ok = (n <= 256) && (bits <= 8) && (n != 0);
    if numpixels < (n as usize * 2) {
        palette_ok = false;
    }
    if gray_ok && !alpha && (bits <= palettebits) {
        palette_ok = false;
    }
    if stats.allow_palette == 0 {
        palette_ok = false;
    }

    if palette_ok {
        let mut i = 0;
        helper_auto_choose_color_1(
            &mut error,
            &mut i,
            mode_out,
            mode_in,
            stats,
            palettebits,
        );
    } else {
        mode_out.bitdepth = bits;
        mode_out.colortype = if alpha {
            if gray_ok {
                LodePNGColorType::LCT_GREY_ALPHA
            } else {
                LodePNGColorType::LCT_RGBA
            }
        } else if gray_ok {
            LodePNGColorType::LCT_GREY
        } else {
            LodePNGColorType::LCT_RGB
        };

        if key {
            let mask = (1u32 << mode_out.bitdepth) - 1u32;
            mode_out.key_r = (stats.key_r as u32) & mask;
            mode_out.key_g = (stats.key_g as u32) & mask;
            mode_out.key_b = (stats.key_b as u32) & mask;
            mode_out.key_defined = 1;
        }
    }

    error
}
pub fn helper_lodepng_encode_2(
    image: &[u8],
    w: u32,
    h: u32,
    state: &mut LodePNGState,
    info: &mut LodePNGInfo,
    info_png: &LodePNGInfo,
    auto_color: &mut LodePNGColorMode,
) {
    let mut stats = LodePNGColorStats {
        colored: 0,
        key: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
        alpha: 0,
        numcolors: 0,
        palette: [0; 1024],
        bits: 0,
        numpixels: 0,
        allow_palette: 1,
        allow_greyscale: 1,
    };
    let mut allow_convert = 1;
    
    lodepng_color_stats_init(&mut stats);
    
    if info_png.iccp_defined != 0 && isGrayICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize) {
        stats.allow_palette = 0;
    }
    
    if info_png.iccp_defined != 0 && isRGBICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize) {
        stats.allow_greyscale = 0;
    }
    
    state.error = lodepng_compute_color_stats(&mut stats, image, w, h, &state.info_raw);
    if state.error != 0 {
        return;
    }
    
    if info_png.background_defined != 0 {
        let mut r = 0;
        let mut g = 0;
        let mut b = 0;
        let mode16 = lodepng_color_mode_make(LodePNGColorType::LCT_RGB, 16);
        
        lodepng_convert_rgb(
            Some(&mut r),
            Some(&mut g),
            Some(&mut b),
            info_png.background_r,
            info_png.background_g,
            info_png.background_b,
            &mode16,
            &info_png.color,
        );
        
        state.error = lodepng_color_stats_add(&mut stats, r as u16, g as u16, b as u16, 65535);
        if state.error != 0 {
            return;
        }
    }
    
    state.error = auto_choose_color(auto_color, &state.info_raw, &stats);
    if state.error != 0 {
        return;
    }
    
    if info_png.sbit_defined != 0 {
        helper_helper_lodepng_encode_2_1(&mut allow_convert, info.clone(), info_png, auto_color.clone());
    }
    
    if state.encoder.force_palette != 0 {
        if ((info.color.colortype != LodePNGColorType::LCT_GREY) 
            && (info.color.colortype != LodePNGColorType::LCT_GREY_ALPHA)) 
            && ((auto_color.colortype == LodePNGColorType::LCT_GREY) 
                || (auto_color.colortype == LodePNGColorType::LCT_GREY_ALPHA)) 
        {
            allow_convert = 0;
        }
    }
    
    if allow_convert != 0 {
        lodepng_color_mode_copy(&mut info.color, auto_color);
        
        if info_png.background_defined != 0 {
            state.error = lodepng_convert_rgb(
                Some(&mut info.background_r),
                Some(&mut info.background_g),
                Some(&mut info.background_b),
                info_png.background_r,
                info_png.background_g,
                info_png.background_b,
                &info.color,
                &info_png.color,
            );
            
            if state.error != 0 {
                state.error = 104;
                return;
            }
        }
    }
}
pub fn lodepng_encode(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: &[u8],
    w: u32,
    h: u32,
    state: &mut LodePNGState,
) -> u32 {
    let mut data: Option<Vec<u8>> = None;
    let mut datasize = 0;
    let mut outv = ucvector_init(None, 0);
    let mut info = LodePNGInfo {
        compression_method: 0,
        filter_method: 0,
        interlace_method: 0,
        color: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        background_defined: 0,
        background_r: 0,
        background_g: 0,
        background_b: 0,
        text_num: 0,
        text_keys: None,
        text_strings: None,
        itext_num: 0,
        itext_keys: None,
        itext_langtags: None,
        itext_transkeys: None,
        itext_strings: None,
        time_defined: 0,
        time: LodePNGTime {
            year: 0,
            month: 0,
            day: 0,
            hour: 0,
            minute: 0,
            second: 0,
        },
        phys_defined: 0,
        phys_x: 0,
        phys_y: 0,
        phys_unit: 0,
        gama_defined: 0,
        gama_gamma: 0,
        chrm_defined: 0,
        chrm_white_x: 0,
        chrm_white_y: 0,
        chrm_red_x: 0,
        chrm_red_y: 0,
        chrm_green_x: 0,
        chrm_green_y: 0,
        chrm_blue_x: 0,
        chrm_blue_y: 0,
        srgb_defined: 0,
        srgb_intent: 0,
        iccp_defined: 0,
        iccp_name: None,
        iccp_profile: None,
        iccp_profile_size: 0,
        sbit_defined: 0,
        sbit_r: 0,
        sbit_g: 0,
        sbit_b: 0,
        sbit_a: 0,
        unknown_chunks_data: [None, None, None],
        unknown_chunks_size: [0, 0, 0],
    };
    let mut auto_color = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 0,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    lodepng_info_init(&mut info);
    lodepng_color_mode_init(&mut auto_color);
    
    *out = None;
    *outsize = 0;
    state.error = 0;

    // Extract all needed info_png values before any mutable borrows
    let colortype = state.info_png.color.colortype;
    let force_palette = state.encoder.force_palette;
    let palettesize = state.info_png.color.palettesize;
    let interlace_method = state.info_png.interlace_method;
    let iccp_defined = state.info_png.iccp_defined;
    let iccp_profile = state.info_png.iccp_profile.clone();
    let iccp_profile_size = state.info_png.iccp_profile_size;

    if ((colortype == LodePNGColorType::LCT_PALETTE) || (force_palette != 0))
        && ((palettesize == 0) || (palettesize > 256))
    {
        state.error = 68;
        return state.error;
    }

    if state.encoder.zlibsettings.btype > 2 {
        state.error = 61;
        return state.error;
    }

    if interlace_method > 1 {
        state.error = 71;
        return state.error;
    }

    state.error = checkColorValidity(colortype, state.info_png.color.bitdepth);
    if state.error != 0 {
        return state.error;
    }

    state.error = checkColorValidity(state.info_raw.colortype, state.info_raw.bitdepth);
    if state.error != 0 {
        return state.error;
    }

    state.error = lodepng_info_copy(&mut info, &state.info_png);
    if state.error != 0 {
        return state.error;
    }

    if state.encoder.auto_convert != 0 {
        let info_png = state.info_png.clone();  // Clone instead of borrowing
        helper_lodepng_encode_2(
            image,
            w,
            h,
            state,
            &mut info,
            &info_png,
            &mut auto_color,
        );
    }

    if iccp_defined != 0 {
        let gray_icc = isGrayICCProfile(iccp_profile.as_deref(), iccp_profile_size as usize);
        let rgb_icc = isRGBICCProfile(iccp_profile.as_deref(), iccp_profile_size as usize);
        let gray_png = (info.color.colortype == LodePNGColorType::LCT_GREY) 
            || (info.color.colortype == LodePNGColorType::LCT_GREY_ALPHA);

        if !gray_icc && !rgb_icc {
            state.error = 100;
            return state.error;
        }

        if gray_icc != gray_png {
            state.error = if state.encoder.auto_convert != 0 { 102 } else { 101 };
            return state.error;
        }
    }

    if !lodepng_color_mode_equal(&state.info_raw, &info.color) {
        helper_lodepng_encode_1(image, w, h, state, &mut data, &mut datasize, &info);
    } else {
        state.error = preProcessScanlines(&mut data, &mut datasize, image, w, h, &info, &state.encoder);
        if state.error != 0 {
            return state.error;
        }
    }

    let empty_vec = Vec::new();
    let data_ref = data.as_ref().unwrap_or(&empty_vec);
    let info_png = state.info_png.clone();  // Clone instead of borrowing
    helper_lodepng_encode_3(
        w,
        h,
        state,
        data_ref,
        datasize,
        &mut outv,
        &info,
        &info_png,
    );

    lodepng_info_cleanup(&mut info);
    lodepng_color_mode_cleanup(&mut auto_color);

    *out = outv.data;
    *outsize = outv.size;

    state.error
}
pub fn lodepng_encode_memory(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: &[u8],
    w: u32,
    h: u32,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
    let mut state = LodePNGState {
        decoder: LodePNGDecoderSettings {
            zlibsettings: LodePNGDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePNGEncoderSettings {
            zlibsettings: LodePNGCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePngFilterStrategy::Zero,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype,
            bitdepth,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePNGInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype,
                bitdepth,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePNGTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    state.info_raw.colortype = colortype;
    state.info_raw.bitdepth = bitdepth;
    state.info_png.color.colortype = colortype;
    state.info_png.color.bitdepth = bitdepth;

    lodepng_encode(out, outsize, image, w, h, &mut state);
    let error = state.error;
    lodepng_state_cleanup(&mut state);

    error
}
pub fn lodepng_encode32(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: &[u8],
    w: u32,
    h: u32,
) -> u32 {
    lodepng_encode_memory(out, outsize, image, w, h, crate::LodePNGColorType::LCT_RGBA, 8)
}
pub fn lodepng_encode24(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: &[u8],
    w: u32,
    h: u32,
) -> u32 {
    lodepng_encode_memory(out, outsize, image, w, h, LodePNGColorType::LCT_RGB, 8)
}
pub fn lodepng_encode_file(
    filename: &str,
    image: &[u8],
    w: u32,
    h: u32,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
    let mut buffer: Option<Vec<u8>> = None;
    let mut buffersize: usize = 0;
    
    let error = lodepng_encode_memory(&mut buffer, &mut buffersize, image, w, h, colortype, bitdepth);
    
    if error == 0 {
        if let Some(ref buf) = buffer {
            if let Err(_) = lodepng_save_file(buf, filename) {
                return 79; // Return error code if save fails
            }
        }
    }
    
    // No need to explicitly free buffer in Rust, it will be dropped automatically
    error
}
pub fn lodepng_encode32_file(filename: &str, image: &[u8], w: u32, h: u32) -> u32 {
    lodepng_encode_file(filename, image, w, h, LodePNGColorType::LCT_RGBA, 8)
}
pub fn lodepng_encode24_file(filename: &str, image: &[u8], w: u32, h: u32) -> u32 {
    lodepng_encode_file(filename, image, w, h, LodePNGColorType::LCT_RGB, 8)
}
pub fn lodepng_is_palette_type(info: &LodePNGColorMode) -> bool {
    info.colortype == LodePNGColorType::LCT_PALETTE
}
pub fn lodepng_get_channels(info: &LodePNGColorMode) -> u8 {
    getNumColorChannels(info.colortype)
}
pub fn lodepng_clear_text(info: &mut LodePNGInfo) {
    LodePNGText_cleanup(info);
}
pub fn lodepng_clear_itext(info: &mut LodePNGInfo) {
    LodePNGIText_cleanup(info);
}
pub fn lodepng_chunk_find<'a>(chunk: Option<&'a [u8]>, end: Option<&'a [u8]>, type_: Option<&'a CStr>) -> Option<&'a [u8]> {
    let mut chunk = chunk?;
    let end = end?;

    loop {
        // Check if chunk is beyond end or if remaining space is less than 12 bytes
        if chunk.as_ptr() >= end.as_ptr() || (end.as_ptr() as usize) - (chunk.as_ptr() as usize) < 12 {
            return Option::None;
        }

        // Check if current chunk matches the type
        if lodepng_chunk_type_equals(Some(chunk), type_) != 0 {
            return Some(chunk);
        }

        // Move to next chunk
        chunk = lodepng_chunk_next(Some(chunk), Some(end))?;
    }
}
pub fn lodepng_chunk_find_const<'a>(chunk: Option<&'a [u8]>, end: Option<&'a [u8]>, type_: Option<&'a CStr>) -> Option<&'a [u8]> {
    let mut chunk_idx = chunk?;
    let end = end?;

    loop {
        // Check if current chunk position is beyond end or has insufficient space
        if chunk_idx.as_ptr() >= end.as_ptr() || (end.as_ptr() as usize - chunk_idx.as_ptr() as usize) < 12 {
            return None;
        }

        // Check if current chunk matches the type
        if lodepng_chunk_type_equals(Some(chunk_idx), type_) != 0 {
            return Some(chunk_idx);
        }

        // Move to next chunk
        chunk_idx = lodepng_chunk_next_const(Some(chunk_idx), Some(end))?;
    }
}

pub fn lodepng_set_icc(info: &mut LodePNGInfo, name: Option<&CStr>, profile: &[u8], profile_size: u32) -> u32 {
    if info.iccp_name.is_some() {
        lodepng_clear_icc(info);
    }
    info.iccp_defined = 1;
    lodepng_assign_icc(info, name, profile, profile_size)
}
pub fn lodepng_chunk_create(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    length: usize,
    type_: &[u8],
    data: &[u8],
) -> u32 {
    let mut v = ucvector_init(out.take(), *outsize);
    let error = lodepng_chunk_createv(&mut v, length, type_, data);
    *out = v.data;
    *outsize = v.size;
    error
}
pub fn lodepng_inflate(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: Option<Vec<u8>>,
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    let mut v = ucvector_init(out.take(), *outsize);
    let error = lodepng_inflatev(&mut v, in_data, insize, settings);
    *out = v.data;
    *outsize = v.size;
    error
}
pub fn lodepng_zlib_decompress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &LodePNGDecompressSettings,
) -> u32 {
    let mut v = ucvector_init(out.take(), *outsize);
    let error = lodepng_zlib_decompressv(&mut v, in_data, insize, settings);
    *out = v.data;
    *outsize = v.size;
    error
}
pub fn lodepng_state_copy(dest: &mut LodePNGState, source: &LodePNGState) {
    // Clean up the destination state first
    lodepng_state_cleanup(dest);
    
    // Copy basic fields (decoder, encoder, error)
    dest.decoder = source.decoder.clone();
    dest.encoder = LodePNGEncoderSettings {
        zlibsettings: LodePNGCompressSettings {
            btype: source.encoder.zlibsettings.btype,
            use_lz77: source.encoder.zlibsettings.use_lz77,
            windowsize: source.encoder.zlibsettings.windowsize,
            minmatch: source.encoder.zlibsettings.minmatch,
            nicematch: source.encoder.zlibsettings.nicematch,
            lazymatching: source.encoder.zlibsettings.lazymatching,
            custom_zlib: source.encoder.zlibsettings.custom_zlib,
            custom_deflate: source.encoder.zlibsettings.custom_deflate,
            custom_context: None, // Can't clone Box<dyn Any>, so we set to None
        },
        auto_convert: source.encoder.auto_convert,
        filter_palette_zero: source.encoder.filter_palette_zero,
        filter_strategy: source.encoder.filter_strategy,
        predefined_filters: source.encoder.predefined_filters.clone(),
        force_palette: source.encoder.force_palette,
        add_id: source.encoder.add_id,
        text_compression: source.encoder.text_compression,
    };
    dest.error = source.error;
    
    // Initialize and copy info_raw
    lodepng_color_mode_init(&mut dest.info_raw);
    dest.error = lodepng_color_mode_copy(&mut dest.info_raw, &source.info_raw);
    if dest.error != 0 {
        return;
    }
    
    // Initialize and copy info_png
    lodepng_info_init(&mut dest.info_png);
    dest.error = lodepng_info_copy(&mut dest.info_png, &source.info_png);
    if dest.error != 0 {
        return;
    }
}

pub fn lodepng_inspect_chunk(
    state: &mut LodePNGState,
    pos: usize,
    in_data: &[u8],
    insize: usize,
) -> u32 {
    if pos + 4 > insize {
        return 30;
    }

    let chunk = &in_data[pos..];
    let chunk_length = lodepng_chunk_length(Some(chunk)) as usize;
    
    if chunk_length > 2147483647 {
        return 63;
    }

    let data = match lodepng_chunk_data_const(Some(chunk)) {
        Some(d) => d,
        None => return 30,
    };

    if chunk_length + 12 > insize - pos {
        return 30;
    }

    let mut unhandled = 0;
    let mut error = 0;

    // Use CStr::from_bytes_with_nul to safely create C strings for comparison
    if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"PLTE\0").unwrap())) == 1 {
        error = readChunk_PLTE(&mut state.info_png.color, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tRNS\0").unwrap())) == 1 {
        error = readChunk_tRNS(&mut state.info_png.color, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"bKGD\0").unwrap())) == 1 {
        error = readChunk_bKGD(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tEXt\0").unwrap())) == 1 {
        error = readChunk_tEXt(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"zTXt\0").unwrap())) == 1 {
        error = readChunk_zTXt(&mut state.info_png, &state.decoder, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"iTXt\0").unwrap())) == 1 {
        error = readChunk_iTXt(&mut state.info_png, &state.decoder, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"tIME\0").unwrap())) == 1 {
        error = readChunk_tIME(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"pHYs\0").unwrap())) == 1 {
        error = readChunk_pHYs(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"gAMA\0").unwrap())) == 1 {
        error = readChunk_gAMA(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"cHRM\0").unwrap())) == 1 {
        error = readChunk_cHRM(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"sRGB\0").unwrap())) == 1 {
        error = readChunk_sRGB(&mut state.info_png, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"iCCP\0").unwrap())) == 1 {
        error = readChunk_iCCP(&mut state.info_png, &state.decoder, data, chunk_length);
    }
    else if lodepng_chunk_type_equals(Some(chunk), Some(CStr::from_bytes_with_nul(b"sBIT\0").unwrap())) == 1 {
        error = readChunk_sBIT(&mut state.info_png, data, chunk_length).unwrap_or(0);
    }
    else {
        unhandled = 1;
    }

    if error == 0 && unhandled == 0 && state.decoder.ignore_crc == 0 {
        if lodepng_chunk_check_crc(Some(chunk)) != 0 {
            return 57;
        }
    }

    error
}
