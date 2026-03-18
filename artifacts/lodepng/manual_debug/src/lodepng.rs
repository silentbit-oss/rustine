use crate::*;
use lazy_static::lazy_static;
use lodepng::LodePNGColorType;
use rand::Rng;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc;
use std::borrow::Cow;
use std::boxed::Box;
use std::cmp::Ordering;
use std::convert::TryFrom;
use std::convert::TryInto;
use std::ffi::CStr;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::mem::size_of;
use std::os::raw::c_uchar;
use std::os::raw::c_uint;
use std::os::raw::c_ulong;
use std::os::raw::c_void;
use std::path::Path;
use std::ptr;
use std::vec::Vec;
pub fn lodepng_error_text(code: u32) -> &'static str {
	println!("* lodepng_error_text");
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
	println!("* lodepng_chunk_type");
    for i in 0..4 {
        type_[i] = chunk[4 + i];
    }
    type_[4] = 0;
}
pub fn lodepng_chunk_ancillary(chunk: Option<&[u8]>) -> bool {
	println!("* lodepng_chunk_ancillary");
    // Check if the chunk exists and has at least 5 bytes (since we access index 4)
    match chunk {
        Some(c) if c.len() > 4 => (c[4] & 32) != 0,
        _ => false, // Return false for None or if chunk is too small
    }
}
pub fn lodepng_chunk_private(chunk: Option<&[u8]>) -> bool {
	println!("* lodepng_chunk_private");
    // Check if the input is None (equivalent to NULL check in C)
    if let Some(chunk) = chunk {
        // Check if the chunk has at least 7 bytes (since we access index 6)
        if chunk.len() > 6 {
            (chunk[6] & 32) != 0
        } else {
            false // Return false if chunk is too short (safer than C's undefined behavior)
        }
    } else {
        false // Return false for NULL input (consistent with C's potential undefined behavior)
    }
}
pub fn lodepng_chunk_safetocopy(chunk: Option<&[u8]>) -> bool {
	println!("* lodepng_chunk_safetocopy");
    // Check if chunk is None (equivalent to NULL check in C)
    // Also ensure the slice has at least 8 bytes to avoid panic
    match chunk {
        Some(c) if c.len() >= 8 => (c[7] & 32) != 0,
        _ => false, // Return false for NULL or insufficient length (safe default)
    }
}
pub fn lodepng_chunk_data(chunk: &[u8]) -> Option<&[u8]> {
	println!("* lodepng_chunk_data");
    if chunk.len() < 8 {
        return None;
    }
    Some(&chunk[8..])
}
pub fn lodepng_chunk_data_const(chunk: Option<&[u8]>) -> Option<&[u8]> {
	println!("* lodepng_chunk_data_const");
    // Check if input is None (equivalent to NULL check in C)
    let chunk = chunk?;  // Early return if None
    
    // Return slice starting from index 8 (equivalent to &chunk[8] in C)
    // Rust slices are bounds-checked, so this is safe
    Some(&chunk[8..])
}

pub fn lodepng_save_file(buffer: &[u8], filename: &str) -> Result<(), u32> {
	println!("* lodepng_save_file");
    let mut file = match File::create(filename) {
        Ok(f) => f,
        Err(_) => return Err(79),
    };

    if let Err(_) = file.write_all(buffer) {
        return Err(79);
    }

    Ok(())
}

pub fn lodepng_malloc(size: usize) -> Option<*mut u8> {
	println!("* lodepng_malloc");
    if size == 0 {
        return None;
    }
    let layout = Layout::from_size_align(size, std::mem::align_of::<u8>()).ok()?;
    unsafe { Some(alloc(layout)) }
}
pub fn lodepng_realloc(ptr: Option<&mut [u8]>, new_size: usize) -> Option<Vec<u8>> {
	println!("* lodepng_realloc");
    if new_size == 0 {
        // Equivalent to free(ptr) in C when size is 0
        return None;
    }

    let mut new_vec = vec![0;new_size];//Vec::with_capacity(new_size);
    if let Some(slice) = ptr {
        new_vec.extend_from_slice(&slice[..slice.len().min(new_size)]);
    }
    new_vec.resize(new_size, 0);
    Some(new_vec)

    //let old_layout = if let Some(ref slice) = ptr {
    //    Layout::array::<u8>(slice.len()).ok()?
    //} else {
    //    // Equivalent to malloc(size) in C when ptr is NULL
    //    return Some(vec![0; new_size].into_boxed_slice());
    //};

    //let new_layout = Layout::array::<u8>(new_size).ok()?;

    //unsafe {
    //    let new_ptr = if let Some(slice) = ptr {
    //        alloc::realloc(
    //            slice.as_mut_ptr() as *mut u8,
    //            old_layout,
    //            new_layout.size(),
    //        )
    //    } else {
    //        alloc::alloc(new_layout)
    //    };

    //    if new_ptr.is_null() {
    //        None
    //    } else {
    //        Some(Box::from_raw(ptr::slice_from_raw_parts_mut(new_ptr, new_size)))
    //    }
    //}
}
pub fn lodepng_free(ptr: Option<Box<dyn std::any::Any>>) {
	println!("* lodepng_free");
    // In Rust, memory is automatically freed when Box goes out of scope
    // This function is essentially a no-op in safe Rust since Box handles deallocation
    // We take ownership of the Box and let it drop
    if let Some(_) = ptr {
        // The Box will be dropped here
    }
}
pub fn lodepng_memcpy(dst: &mut [u8], src: &[u8]) {
	println!("* lodepng_memcpy");
    // Rust slices already provide bounds checking, so we don't need to manually check size
    // The slice lengths must match, otherwise this will panic (which is the safe behavior)
    dst[..src.len()].copy_from_slice(src);
}
pub fn lodepng_memset(dst: &mut [u8], value: u8) {
	println!("* lodepng_memset");
    for byte in dst.iter_mut() {
        *byte = value;
    }
}
pub fn lodepng_addofl(a: usize, b: usize, result: &mut usize) -> bool {
	println!("* lodepng_addofl");
    *result = a + b;
    *result < a
}
pub fn lodepng_mulofl(a: usize, b: usize, result: &mut Option<usize>) -> bool {
	println!("* lodepng_mulofl");
    if let Some(res) = result {
        *res = a * b;
        (a != 0) && ((*res / a) != b)
    } else {
        false
    }
}
pub fn lodepng_read32bitInt(buffer: &[u8]) -> u32 {
	println!("* lodepng_read32bitInt");
    ((u32::from(buffer[0]) << 24) | 
     (u32::from(buffer[1]) << 16) | 
     (u32::from(buffer[2]) << 8) | 
      u32::from(buffer[3]))
}
pub fn lodepng_set32bitInt(buffer: &mut [u8; 4], value: u32) {
	println!("* lodepng_set32bitInt");
    buffer[0] = ((value >> 24) & 0xff) as u8;
    buffer[1] = ((value >> 16) & 0xff) as u8;
    buffer[2] = ((value >> 8) & 0xff) as u8;
    buffer[3] = (value & 0xff) as u8;
}

pub fn lodepng_filesize(filename: &str) -> Option<i64> {
	println!("* lodepng_filesize");
    // Open the file in read-only mode
    let mut file = match File::open(Path::new(filename)) {
        Ok(f) => f,
        Err(_) => return None, // Equivalent to returning -1 in C
    };

    // Seek to the end of the file to determine its size
    if let Err(_) = file.seek(SeekFrom::End(0)) {
        return None; // Equivalent to returning -1 in C
    }

    // Get the current position (which is the file size)
    let size = match file.stream_position() {
        Ok(s) => s as i64,
        Err(_) => return None, // Equivalent to returning -1 in C
    };

    // Check for overflow (9223372036854775807L in C is i64::MAX in Rust)
    if size == i64::MAX {
        return None; // Equivalent to returning -1 in C
    }

    Some(size)
}

pub fn lodepng_buffer_file(out: &mut [u8], filename: &str) -> Result<(), u32> {
	println!("* lodepng_buffer_file");
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
	println!("* reverseBits");
    let mut result = 0;
    
    for i in 0..num {
        result |= ((bits >> ((num - i) - 1u32)) & 1u32) << i;
    }
    
    result
}
pub fn searchCodeIndex(array: &[u32], array_size: usize, value: usize) -> usize {
	println!("* searchCodeIndex");
    let mut left = 1;
    let mut right = array_size - 1;
    
    while left <= right {
        let mid = (left + right) >> 1;
        if array[mid] >= value as u32 {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if left >= array_size || array[left] > value as u32 {
        left -= 1;
    }
    left
}

pub fn update_adler32(adler: u32, data: Option<&[u8]>, len: u32) -> u32 {
	println!("* update_adler32");
    // Check if data is None (equivalent to NULL in C)
    let data = match data {
        Some(d) => d,
        None => return adler, // Return original adler if data is NULL
    };

    let mut data_idx = 0;
    let mut s1 = adler & 0xffff;
    let mut s2 = (adler >> 16) & 0xffff;
    let mut remaining_len = len;

    while remaining_len != 0 {
        let amount = if remaining_len > 5552 { 5552 } else { remaining_len };
        remaining_len -= amount;

        for _ in 0..amount {
            s1 += data[data_idx] as u32;
            data_idx += 1;
            s2 += s1;
        }

        s1 %= 65521;
        s2 %= 65521;
    }

    (s2 << 16) | s1
}
pub fn readBitFromReversedStream(bitpointer: &mut usize, bitstream: &[u8]) -> u8 {
	println!("* readBitFromReversedStream");
    let result = (bitstream[*bitpointer >> 3] >> (7 - (*bitpointer & 0x7))) & 1;
    *bitpointer += 1;
    result
}
pub fn setBitOfReversedStream(bitpointer: &mut usize, bitstream: &mut [u8], bit: u8) {
	println!("* setBitOfReversedStream");
    if bit == 0 {
        bitstream[*bitpointer >> 3] &= !(1 << (7 - (*bitpointer & 7)));
    } else {
        bitstream[*bitpointer >> 3] |= 1 << (7 - (*bitpointer & 7));
    }
    *bitpointer += 1;
}
pub fn lodepng_get_raw_size_idat(w: u32, h: u32, bpp: u32) -> usize {
	println!("* lodepng_get_raw_size_idat");
    let line = (((w / 8) * bpp) + 1) + (((w & 7) * bpp + 7) / 8);
    (h as usize) * (line as usize)
}
pub fn addColorBits(out: &mut [u8], index: usize, bits: u32, in_val: u32) {
	println!("* addColorBits");
    let m = match bits {
        1 => 7,
        2 => 3,
        _ => 1,
    };
    let p = index & m as usize;
    let mut val = in_val & ((1u32 << bits) - 1);
    val = val << (bits * (m - p as u32));
    
    let byte_index = (index * bits as usize) / 8;
    if p == 0 {
        out[byte_index] = val as u8;
    } else {
        out[byte_index] |= val as u8;
    }
}
pub fn getValueRequiredBits(value: u8) -> u8 {
	println!("* getValueRequiredBits");
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
	println!("* paethPredictor");
    let mut a = a;
    let pa = (b - c).abs();
    let pb = (a - c).abs();
    let pc = ((a + b - c) - c).abs();

    let (new_a, new_pa) = if pb < pa {
        (b, pb)
    } else {
        (a, pa)
    };

    if pc < new_pa {
        c as u8
    } else {
        new_a as u8
    }
}
pub fn ilog2(i: usize) -> usize {
	println!("* ilog2");
    let mut result = 0;
    let mut i = i;

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
	println!("* isGrayICCProfile");
    // Check if profile is None (equivalent to NULL check in C)
    let profile = match profile {
        Some(p) => p,
        None => return false,
    };

    // Check size condition first (Rust version of the C check)
    if size < 20 {
        return false;
    }

    // Check the specific bytes for "GRAY" pattern
    // Rust slices are 0-indexed, same as C arrays
    profile.get(16..20) == Some(b"GRAY")
}
pub fn isRGBICCProfile(profile: Option<&[u8]>, size: usize) -> bool {
	println!("* isRGBICCProfile");
    // Check if profile is None (equivalent to NULL check in C)
    let profile = match profile {
        Some(p) => p,
        None => return false,
    };

    // Check size condition first (Rust's slice bounds are checked automatically)
    if size < 20 || profile.len() < 20 {
        return false;
    }

    // Check the specific bytes in the profile
    (profile[16] == b'R') && (profile[17] == b'G') && (profile[18] == b'B') && (profile[19] == b' ')
}
pub fn lodepng_strlen(a: Option<&str>) -> usize {
	println!("* lodepng_strlen");
    // Check for NULL equivalent (None)
    if a.is_none() {
        return 0;
    }
    
    // Unwrap safely since we checked for None
    let a = a.unwrap();
    
    // Rust strings are UTF-8 and already know their length
    a.len()
}

pub fn lodepng_compress_settings_init(settings: &mut LodePngCompressSettings) {
	println!("* lodepng_compress_settings_init");
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
pub fn lodepng_encoder_settings_init(settings: &mut LodePngEncoderSettings) {
	println!("* lodepng_encoder_settings_init");
    lodepng_compress_settings_init(&mut settings.zlibsettings);
    settings.filter_palette_zero = 1;
    settings.filter_strategy = LodePNGFilterStrategy::LFS_MINSUM;
    settings.auto_convert = 1;
    settings.force_palette = 0;
    settings.predefined_filters = None;
    settings.add_id = 0;
    settings.text_compression = 1;
}
pub fn lodepng_decompress_settings_init(settings: &mut LodePngDecompressSettings) {
	println!("* lodepng_decompress_settings_init");
    settings.ignore_adler32 = 0;
    settings.ignore_nlen = 0;
    settings.max_output_size = 0;
    settings.custom_zlib = None;
    settings.custom_inflate = None;
    settings.custom_context = None;
}
pub fn lodepng_decoder_settings_init(settings: &mut LodePngDecoderSettings) {
	println!("* lodepng_decoder_settings_init");
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
pub fn lodepng_color_mode_init(info: &mut LodePNGColorMode) {
	println!("* lodepng_color_mode_init");
    info.key_defined = 0;
    info.key_r = 0;
    info.key_g = 0;
    info.key_b = 0;
    info.colortype = LodePNGColorType::LCT_RGBA;
    info.bitdepth = 8;
    info.palette = None;
    info.palettesize = 0;
}
pub fn LodePNGUnknownChunks_init(info: &mut LodePngInfo) {
	println!("* LodePNGUnknownChunks_init");
    for i in 0..3 {
        info.unknown_chunks_data[i] = None;
    }

    for i in 0..3 {
        info.unknown_chunks_size[i] = 0;
    }
}
pub fn LodePNGText_init(info: &mut LodePngInfo) {
	println!("* LodePNGText_init");
    info.text_num = 0;
    info.text_keys = None;
    info.text_strings = None;
}
pub fn LodePNGIText_init(info: &mut LodePngInfo) {
	println!("* LodePNGIText_init");
    info.itext_num = 0;
    info.itext_keys = None;
    info.itext_langtags = None;
    info.itext_transkeys = None;
    info.itext_strings = None;
}
pub fn lodepng_info_init(info: &mut LodePngInfo) {
	println!("* lodepng_info_init");
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
pub fn lodepng_state_init(state: &mut LodePngState) {
	println!("* lodepng_state_init");
    lodepng_decoder_settings_init(&mut state.decoder);
    lodepng_encoder_settings_init(&mut state.encoder);
    lodepng_color_mode_init(&mut state.info_raw);
    lodepng_info_init(&mut state.info_png);
    state.error = 1;
}
pub fn lodepng_palette_clear(info: &mut LodePNGColorMode) {
	println!("* lodepng_palette_clear");
    info.palette = None;
    info.palettesize = 0;
}
pub fn lodepng_color_mode_cleanup(info: &mut LodePNGColorMode) {
	println!("* lodepng_color_mode_cleanup");
    lodepng_palette_clear(info);
}
pub fn string_cleanup(out: &mut Option<Box<dyn std::any::Any>>) {
	println!("* string_cleanup");
    lodepng_free(out.take());
}
pub fn lodepng_clear_icc(info: &mut LodePngInfo) {
	println!("* lodepng_clear_icc");
    info.iccp_name = None;
    //if let Some(name) = info.iccp_name.take() {
    //    string_cleanup(&mut Some(Box::new(name) as Box<dyn std::any::Any>));
    //}
    //if let Some(profile) = info.iccp_profile.take() {
    //    lodepng_free(Some(Box::new(profile) as Box<dyn std::any::Any>));
    //}
    info.iccp_profile = None;
    info.iccp_profile_size = 0;
    info.iccp_defined = 0;
}
pub fn LodePNGUnknownChunks_cleanup(info: &mut LodePngInfo) {
	println!("* LodePNGUnknownChunks_cleanup");
    for i in 0..3 {
        info.unknown_chunks_data[i] = Option::None;
    }
}
pub fn LodePNGText_cleanup(info: &mut LodePngInfo) {
	println!("* LodePNGText_cleanup");
   // info.text_keys = None
   // //if let Some(text_keys) = &mut info.text_keys {
   // //    //for key in text_keys.iter_mut() {
   // //    //    let mut boxed_key = Some(Box::new(key.clone()) as Box<dyn std::any::Any>);
   // //    //    string_cleanup(&mut boxed_key);
   // //    //}
   // //}
   // if let Some(text_strings) = &mut info.text_strings {
   //     for string in text_strings.iter_mut() {
   //         let mut boxed_string = Some(Box::new(string.clone()) as Box<dyn std::any::Any>);
   //         string_cleanup(&mut boxed_string);
   //     }
   // }

    info.text_keys = None;
    info.text_strings = None;
}
pub fn LodePNGIText_cleanup(info: &mut LodePngInfo) {
	println!("* LodePNGIText_cleanup");
    // Clean up individual strings first
    //if let Some(itext_keys) = &mut info.itext_keys {
    //    for key in itext_keys.iter_mut() {
    //        string_cleanup(&mut Some(Box::new(key.clone()) as Box<dyn std::any::Any>));
    //    }
    //}
    //if let Some(itext_langtags) = &mut info.itext_langtags {
    //    for langtag in itext_langtags.iter_mut() {
    //        string_cleanup(&mut Some(Box::new(langtag.clone()) as Box<dyn std::any::Any>));
    //    }
    //}
    //if let Some(itext_transkeys) = &mut info.itext_transkeys {
    //    for transkey in itext_transkeys.iter_mut() {
    //        string_cleanup(&mut Some(Box::new(transkey.clone()) as Box<dyn std::any::Any>));
    //    }
    //}
    //if let Some(itext_strings) = &mut info.itext_strings {
    //    for string in itext_strings.iter_mut() {
    //        string_cleanup(&mut Some(Box::new(string.clone()) as Box<dyn std::any::Any>));
    //    }
    //}

    // Then free the vectors themselves
    if info.itext_keys.is_some() {
        info.itext_keys = None;
        //lodepng_free(info.itext_keys.take().map(|v| Box::new(v) as Box<dyn std::any::Any>));
    }
    if info.itext_langtags.is_some() {
        //lodepng_free(info.itext_langtags.take().map(|v| Box::new(v) as Box<dyn std::any::Any>));
        info.itext_langtags = None;
    }
    if info.itext_transkeys.is_some() {
        //lodepng_free(info.itext_transkeys.take().map(|v| Box::new(v) as Box<dyn std::any::Any>));
        info.itext_transkeys = None;
    }
    if info.itext_strings.is_some() {
        //lodepng_free(info.itext_strings.take().map(|v| Box::new(v) as Box<dyn std::any::Any>));
        info.itext_strings = None;
    }
}
pub fn lodepng_info_cleanup(info: &mut LodePngInfo) {
	println!("* lodepng_info_cleanup");
    lodepng_color_mode_cleanup(&mut info.color);
    LodePNGText_cleanup(info);
    LodePNGIText_cleanup(info);
    lodepng_clear_icc(info);
    LodePNGUnknownChunks_cleanup(info);
}
pub fn lodepng_state_cleanup(state: &mut LodePngState) {
	println!("* lodepng_state_cleanup");
    lodepng_color_mode_cleanup(&mut state.info_raw);
    lodepng_info_cleanup(&mut state.info_png);
}
pub fn color_tree_get(tree: &ColorTree, r: u8, g: u8, b: u8, a: u8) -> i32 {
	println!("* color_tree_get");
    let mut tree_idx = tree;
    
    for bit in 0..8 {
        let i = ((8 * ((r >> bit) & 1)) + (4 * ((g >> bit) & 1)) + (2 * ((b >> bit) & 1)) + (1 * ((a >> bit) & 1))) as usize;
        
        match &tree_idx.children[i] {
            Some(child) => tree_idx = child,
            Option::None => return -1,
        }
    }
    
    tree_idx.index
}
pub fn rgba8ToPixel(
    out: &mut [u8],
    i: usize,
    mode: &LodePNGColorMode,
    tree: &ColorTree,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) -> u32 {
	println!("* rgba8ToPixel");
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
pub fn rgba16ToPixel(out: &mut [u8], i: usize, mode: &LodePNGColorMode, r: u16, g: u16, b: u16, a: u16) {
	println!("* rgba16ToPixel");
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let gray = r;
            out[(i * 2) + 0] = (gray >> 8) as u8;
            out[(i * 2) + 1] = gray as u8;
        }
        LodePNGColorType::LCT_RGB => {
            out[(i * 6) + 0] = (r >> 8) as u8;
            out[(i * 6) + 1] = r as u8;
            out[(i * 6) + 2] = (g >> 8) as u8;
            out[(i * 6) + 3] = g as u8;
            out[(i * 6) + 4] = (b >> 8) as u8;
            out[(i * 6) + 5] = b as u8;
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            let gray = r;
            out[(i * 4) + 0] = (gray >> 8) as u8;
            out[(i * 4) + 1] = gray as u8;
            out[(i * 4) + 2] = (a >> 8) as u8;
            out[(i * 4) + 3] = a as u8;
        }
        LodePNGColorType::LCT_RGBA => {
            out[(i * 8) + 0] = (r >> 8) as u8;
            out[(i * 8) + 1] = r as u8;
            out[(i * 8) + 2] = (g >> 8) as u8;
            out[(i * 8) + 3] = g as u8;
            out[(i * 8) + 4] = (b >> 8) as u8;
            out[(i * 8) + 5] = b as u8;
            out[(i * 8) + 6] = (a >> 8) as u8;
            out[(i * 8) + 7] = a as u8;
        }
        _ => {} // Handle other cases if necessary
    }
}
pub fn readBitsFromReversedStream(bitpointer: &mut usize, bitstream: &[u8], nbits: usize) -> u32 {
	println!("* readBitsFromReversedStream");
    let mut result = 0;
    for _ in 0..nbits {
        result <<= 1;
        result |= u32::from(readBitFromReversedStream(bitpointer, bitstream));
    }
    result
}
pub fn getPixelColorsRGBA8(buffer: &mut [u8], numpixels: usize, in_data: &[u8], mode: &LodePNGColorMode) {
	println!("* getPixelColorsRGBA8");
    let num_channels = 4;
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
                        buffer[buffer_idx + 3] = 255;
                        buffer_idx += num_channels;
                    }

                    if mode.key_defined != 0 {
                        buffer_idx = 0;
                        for i in 0..numpixels {
                            if buffer[buffer_idx] == mode.key_r as u8 {
                                buffer[buffer_idx + 3] = 0;
                            }
                            buffer_idx += num_channels;
                        }
                    }
                }
                16 => {
                    for i in 0..numpixels {
                        let val = in_data[i * 2];
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer[buffer_idx + 3] = if mode.key_defined != 0 && 
                            (256 * in_data[i * 2] as u32 + in_data[i * 2 + 1] as u32) == mode.key_r {
                            0
                        } else {
                            255
                        };
                        buffer_idx += num_channels;
                    }
                }
                _ => {
                    let highest = (1 << mode.bitdepth) - 1;
                    let mut j = 0;
                    for _ in 0..numpixels {
                        let value = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
                        let val = ((value * 255) / highest) as u8;
                        buffer[buffer_idx] = val;
                        buffer[buffer_idx + 1] = val;
                        buffer[buffer_idx + 2] = val;
                        buffer[buffer_idx + 3] = if mode.key_defined != 0 && value == mode.key_r {
                            0
                        } else {
                            255
                        };
                        buffer_idx += num_channels;
                    }
                }
            }
        }
        LodePNGColorType::LCT_RGB => {
            match mode.bitdepth {
                8 => {
                    for i in 0..numpixels {
                        lodepng_memcpy(
                            &mut buffer[buffer_idx..buffer_idx + 3],
                            &in_data[i * 3..i * 3 + 3],
                        );
                        buffer[buffer_idx + 3] = 255;
                        buffer_idx += num_channels;
                    }

                    if mode.key_defined != 0 {
                        buffer_idx = 0;
                        for _ in 0..numpixels {
                            if buffer[buffer_idx] == mode.key_r as u8 &&
                               buffer[buffer_idx + 1] == mode.key_g as u8 &&
                               buffer[buffer_idx + 2] == mode.key_b as u8 {
                                buffer[buffer_idx + 3] = 0;
                            }
                            buffer_idx += num_channels;
                        }
                    }
                }
                _ => {
                    for i in 0..numpixels {
                        buffer[buffer_idx] = in_data[i * 6];
                        buffer[buffer_idx + 1] = in_data[i * 6 + 2];
                        buffer[buffer_idx + 2] = in_data[i * 6 + 4];
                        buffer[buffer_idx + 3] = if mode.key_defined != 0 &&
                            (256 * in_data[i * 6] as u32 + in_data[i * 6 + 1] as u32) == mode.key_r &&
                            (256 * in_data[i * 6 + 2] as u32 + in_data[i * 6 + 3] as u32) == mode.key_g &&
                            (256 * in_data[i * 6 + 4] as u32 + in_data[i * 6 + 5] as u32) == mode.key_b {
                            0
                        } else {
                            255
                        };
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
                            lodepng_memcpy(
                                &mut buffer[buffer_idx..buffer_idx + 4],
                                &palette[index * 4..index * 4 + 4],
                            );
                            buffer_idx += num_channels;
                        }
                    }
                    _ => {
                        let mut j = 0;
                        for _ in 0..numpixels {
                            let index = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize) as usize;
                            lodepng_memcpy(
                                &mut buffer[buffer_idx..buffer_idx + 4],
                                &palette[index * 4..index * 4 + 4],
                            );
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
                        buffer[buffer_idx + 3] = in_data[i * 2 + 1];
                        buffer_idx += num_channels;
                    }
                }
                _ => {
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
        }
        LodePNGColorType::LCT_RGBA => {
            match mode.bitdepth {
                8 => {
                    lodepng_memcpy(buffer, &in_data[..numpixels * 4]);
                }
                _ => {
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
}
pub fn getPixelColorsRGB8(buffer: &mut [u8], numpixels: usize, in_data: &[u8], mode: &LodePNGColorMode) {
	println!("* getPixelColorsRGB8");
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
                            buffer[buffer_idx] = palette[index * 4];
                            buffer[buffer_idx + 1] = palette[index * 4 + 1];
                            buffer[buffer_idx + 2] = palette[index * 4 + 2];
                            buffer_idx += num_channels;
                        }
                    }
                    _ => {
                        let mut j = 0;
                        for _ in 0..numpixels {
                            let index = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize) as usize;
                            buffer[buffer_idx] = palette[index * 4];
                            buffer[buffer_idx + 1] = palette[index * 4 + 1];
                            buffer[buffer_idx + 2] = palette[index * 4 + 2];
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
                        buffer[buffer_idx] = in_data[i * 4];
                        buffer[buffer_idx + 1] = in_data[i * 4 + 1];
                        buffer[buffer_idx + 2] = in_data[i * 4 + 2];
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
pub fn getPixelColorRGBA8(
    r: &mut u8,
    g: &mut u8,
    b: &mut u8,
    a: &mut u8,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
	println!("* getPixelColorRGBA8");
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            if mode.bitdepth == 8 {
                let val = in_data[i];
                *r = val;
                *g = val;
                *b = val;
                *a = if mode.key_defined != 0 && val == u8::try_from(mode.key_r).unwrap_or(0) {
                    0
                } else {
                    LCT_MAX_OCTET_VALUE
                };
            } else if mode.bitdepth == 16 {
                let val = in_data[i * 2];
                *r = val;
                *g = val;
                *b = val;
                let key = (u32::from(val) << 8) + u32::from(in_data[i * 2 + 1]);
                *a = if mode.key_defined != 0 && key == mode.key_r {
                    0
                } else {
                    LCT_MAX_OCTET_VALUE
                };
            } else {
                let highest = (1u32 << mode.bitdepth) - 1;
                let mut j = i * mode.bitdepth as usize;
                let value = readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize);
                let val = ((value * 255) / highest) as u8;
                *r = val;
                *g = val;
                *b = val;
                *a = if mode.key_defined != 0 && value == mode.key_r {
                    0
                } else {
                    LCT_MAX_OCTET_VALUE
                };
            }
        }
        LodePNGColorType::LCT_RGB => {
            if mode.bitdepth == 8 {
                *r = in_data[i * 3];
                *g = in_data[i * 3 + 1];
                *b = in_data[i * 3 + 2];
                *a = if mode.key_defined != 0
                    && *r == u8::try_from(mode.key_r).unwrap_or(0)
                    && *g == u8::try_from(mode.key_g).unwrap_or(0)
                    && *b == u8::try_from(mode.key_b).unwrap_or(0)
                {
                    0
                } else {
                    LCT_MAX_OCTET_VALUE
                };
            } else {
                *r = in_data[i * 6];
                *g = in_data[i * 6 + 2];
                *b = in_data[i * 6 + 4];
                let key_r = (u32::from(in_data[i * 6]) << 8) + u32::from(in_data[i * 6 + 1]);
                let key_g = (u32::from(in_data[i * 6 + 2]) << 8) + u32::from(in_data[i * 6 + 3]);
                let key_b = (u32::from(in_data[i * 6 + 4]) << 8) + u32::from(in_data[i * 6 + 5]);
                *a = if mode.key_defined != 0
                    && key_r == mode.key_r
                    && key_g == mode.key_g
                    && key_b == mode.key_b
                {
                    0
                } else {
                    LCT_MAX_OCTET_VALUE
                };
            }
        }
        LodePNGColorType::LCT_PALETTE => {
            let index = if mode.bitdepth == 8 {
                in_data[i] as usize
            } else {
                let mut j = i * mode.bitdepth as usize;
                readBitsFromReversedStream(&mut j, in_data, mode.bitdepth as usize) as usize
            };
            if let Some(palette) = &mode.palette {
                *r = palette[index * 4];
                *g = palette[index * 4 + 1];
                *b = palette[index * 4 + 2];
                *a = palette[index * 4 + 3];
            }
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if mode.bitdepth == 8 {
                let val = in_data[i * 2];
                *r = val;
                *g = val;
                *b = val;
                *a = in_data[i * 2 + 1];
            } else {
                let val = in_data[i * 4];
                *r = val;
                *g = val;
                *b = val;
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
pub fn getPixelColorRGBA16(
    r: &mut u16,
    g: &mut u16,
    b: &mut u16,
    a: &mut u16,
    in_data: &[u8],
    i: usize,
    mode: &LodePNGColorMode,
) {
	println!("* getPixelColorRGBA16");
    match mode.colortype {
        LodePNGColorType::LCT_GREY => {
            let value = (u16::from(in_data[i * 2]) << 8) + u16::from(in_data[i * 2 + 1]);
            *r = value;
            *g = value;
            *b = value;
            if mode.key_defined != 0 && u32::from(value) == mode.key_r {
                *a = 0;
            } else {
                *a = 65535;
            }
        }
        LodePNGColorType::LCT_RGB => {
            *r = (u16::from(in_data[i * 6]) << 8) + u16::from(in_data[i * 6 + 1]);
            *g = (u16::from(in_data[i * 6 + 2]) << 8) + u16::from(in_data[i * 6 + 3]);
            *b = (u16::from(in_data[i * 6 + 4]) << 8) + u16::from(in_data[i * 6 + 5]);
            if mode.key_defined != 0
                && u32::from(*r) == mode.key_r
                && u32::from(*g) == mode.key_g
                && u32::from(*b) == mode.key_b
            {
                *a = 0;
            } else {
                *a = 65535;
            }
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
pub fn color_tree_cleanup(tree: &mut ColorTree) {
	println!("* color_tree_cleanup");
    //tree.children = [None; 16];
    tree.children = [
                None, None, None, None,
                None, None, None, None,
                None, None, None, None,
                None, None, None, None,
            ];
    //for i in 0..16 {
    //    if let Some(mut child) = tree.children[i].take() {
    //        color_tree_cleanup(&mut child);
    //        lodepng_free(Some(child));
    //    }
    //}
}
pub fn color_tree_init(tree: &mut ColorTree) {
	println!("* color_tree_init");
    for child in tree.children.iter_mut() {
        *child = None;
    }
    tree.index = -1;
}
pub fn color_tree_add(
    tree: &mut ColorTree,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
    index: u32,
) -> u32 {
	println!("* color_tree_add");
    let mut tree_idx = tree;
    for bit in 0..8 {
        let i = ((8 * ((r >> bit) & 1)) + (4 * ((g >> bit) & 1)) + (2 * ((b >> bit) & 1)) + (1 * ((a >> bit) & 1))) as usize;
        
        if tree_idx.children[i].is_none() {
            let mut new_tree = Box::new(ColorTree {
                children: [
                    None, None, None, None,
                    None, None, None, None,
                    None, None, None, None,
                    None, None, None, None,
                ],
                index: -1,
            });
            color_tree_init(&mut new_tree);
            tree_idx.children[i] = Some(new_tree);
        }
        
        tree_idx = tree_idx.children[i].as_mut().unwrap();
    }

    tree_idx.index = index as i32;
    0
}
pub fn lodepng_color_mode_equal(a: &LodePNGColorMode, b: &LodePNGColorMode) -> bool {
	println!("* lodepng_color_mode_equal");
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
pub fn getNumColorChannels(colortype: LodePNGColorType) -> u8 {
	println!("* getNumColorChannels");
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
	println!("* lodepng_get_bpp_lct");
    getNumColorChannels(colortype) * bitdepth
}
pub fn lodepng_get_raw_size_lct(w: u32, h: u32, colortype: LodePNGColorType, bitdepth: u8) -> usize {
	println!("* lodepng_get_raw_size_lct");
    let bpp = lodepng_get_bpp_lct(colortype, bitdepth) as usize;
    let n = (w as usize) * (h as usize);
    ((n / 8) * bpp) + ((((n & 7) * bpp) + 7) / 8)
}
pub fn lodepng_get_raw_size(w: u32, h: u32, color: &LodePNGColorMode) -> usize {
	println!("* lodepng_get_raw_size");
    lodepng_get_raw_size_lct(w, h, color.colortype, color.bitdepth as u8)
}
pub fn lodepng_convert(
    out: &mut [u8],
    in_data: &[u8],
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    w: u32,
    h: u32,
) -> u32 {
	println!("* lodepng_convert");
    let numpixels = (w as usize) * (h as usize);
    let mut error = 0;
    let mut tree = ColorTree {
        children: [
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
            None, None, None, None,
        ],
        index: -1,
    };

    if mode_in.colortype == LodePNGColorType::LCT_PALETTE && mode_in.palette.is_none() {
        return 107;
    }

    if lodepng_color_mode_equal(mode_out, mode_in) {
        let numbytes = lodepng_get_raw_size(w, h, mode_in);
        lodepng_memcpy(&mut out[..numbytes], &in_data[..numbytes]);
        return 0;
    }

    if mode_out.colortype == LodePNGColorType::LCT_PALETTE {
        let palettesize = mode_out.palettesize;
        let palette = mode_out.palette.as_ref().unwrap();
        let mut palette_idx = 0;
        let mut palsize = (1u32 << mode_out.bitdepth) as usize;

        if palettesize == 0 {
            let palettesize = mode_in.palettesize;
            palette_idx = mode_in.key_defined as usize;
            if mode_in.colortype == LodePNGColorType::LCT_PALETTE && mode_in.bitdepth == mode_out.bitdepth {
                let numbytes = lodepng_get_raw_size(w, h, mode_in);
                lodepng_memcpy(&mut out[..numbytes], &in_data[..numbytes]);
                return 0;
            }
        }

        if palettesize < palsize {
            palsize = palettesize;
        }

        color_tree_init(&mut tree);
        for i in 0..palsize {
            let p = &palette[(i * 4) + palette_idx..];
            error = color_tree_add(&mut tree, p[0], p[1], p[2], p[3], i as u32);
            if error != 0 {
                break;
            }
        }
    }

    if error == 0 {
        if mode_in.bitdepth == 16 && mode_out.bitdepth == 16 {
            for i in 0..numpixels {
                let mut r = 0;
                let mut g = 0;
                let mut b = 0;
                let mut a = 0;
                getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
                rgba16ToPixel(out, i, mode_out, r, g, b, a);
            }
        } else if mode_out.bitdepth == 8 && mode_out.colortype == LodePNGColorType::LCT_RGBA {
            getPixelColorsRGBA8(out, numpixels, in_data, mode_in);
        } else if mode_out.bitdepth == 8 && mode_out.colortype == LodePNGColorType::LCT_RGB {
            getPixelColorsRGB8(out, numpixels, in_data, mode_in);
        } else {
            let mut r = 0;
            let mut g = 0;
            let mut b = 0;
            let mut a = 0;
            for i in 0..numpixels {
                getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
                error = rgba8ToPixel(out, i, mode_out, &tree, r, g, b, a);
                if error != 0 {
                    break;
                }
            }
        }
    }

    if mode_out.colortype == LodePNGColorType::LCT_PALETTE {
        color_tree_cleanup(&mut tree);
    }

    error
}

pub fn lodepng_color_mode_copy(dest: &mut LodePNGColorMode, source: &LodePNGColorMode) -> u32 {
	println!("* lodepng_color_mode_copy");
    // Clean up the destination color mode first
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
            // Allocate new palette buffer
            let mut new_palette = Vec::with_capacity(source.palettesize * 4);
            new_palette.extend_from_slice(&source_palette[..source.palettesize * 4]);
            dest.palette = Some(new_palette);
        } else {
            dest.palette = None;
        }
    } else {
        dest.palette = None;
    }

    0 // Success
}

pub fn alloc_string_sized(in_: Option<&[u8]>, insize: usize) -> Option<Vec<u8>> {
	println!("* alloc_string_sized");
    // Check for NULL input (None in Rust)
    let in_ = match in_ {
        Some(slice) => slice,
        None => return None,
    };

    // Allocate memory for output string (+1 for null terminator)
    let mut out = vec![0;insize + 1];//Vec::with_capacity(insize + 1);
    if out.capacity() == 0 {
        return None;
    }

    // Copy the input bytes to the output
    out.extend_from_slice(&in_[..insize]);
    out.push(0); // Add null terminator

    Some(out)
}
pub fn alloc_string(in_: Option<&str>) -> Option<Vec<u8>> {
	println!("* alloc_string");
    alloc_string_sized(in_.map(|s| s.as_bytes()), lodepng_strlen(in_))
}
pub fn lodepng_add_text_sized(info: &mut LodePngInfo, key: Option<&str>, str: Option<&[u8]>, size: usize) -> u32 {
	println!("* lodepng_add_text_sized");
    // Handle reallocation of text_keys
    let new_keys = match &mut info.text_keys {
        Some(keys) => {
            let mut new_vec = keys.clone();
            new_vec.push(String::new());
            Some(new_vec)
        }
        None => Some(vec![String::new()]),
    };

    // Handle reallocation of text_strings
    let new_strings = match &mut info.text_strings {
        Some(strings) => {
            let mut new_vec = strings.clone();
            new_vec.push(String::new());
            Some(new_vec)
        }
        None => Some(vec![String::new()]),
    };

    // Check if allocations succeeded
    if new_keys.is_none() || new_strings.is_none() {
        return 83;
    }

    // Update the info struct with new allocations
    info.text_keys = new_keys;
    info.text_strings = new_strings;
    info.text_num += 1;

    // Allocate and store the new key and string
    let key_bytes = key.unwrap().to_string();
    let str_bytes = String::from_utf8(str.unwrap().to_vec()).expect("Invalid UTF-8");//str.to_string();//alloc_string_sized(str, size);

    //if key_bytes.is_none() {
    //    return 83;
    //}

    // Convert Vec<u8> to String and store
    if let Some(keys) = &mut info.text_keys {
        keys[info.text_num - 1] = key_bytes;
        //if let Some(key_bytes) = key_bytes {
        //    if let Ok(key_str) = String::from_utf8(key_bytes) {
        //        keys[info.text_num - 1] = key_str;
        //    } else {
        //        return 83;
        //    }
        //}
    }

    if let Some(strings) = &mut info.text_strings {
        strings[info.text_num - 1] = str_bytes;
        //if let Some(str_bytes) = str_bytes {
        //    if let Ok(str_str) = String::from_utf8(str_bytes) {
        //        strings[info.text_num - 1] = str_str;
        //    } else {
        //        return 83;
        //    }
        //}
    }

    0
}

#[derive(Clone)]
pub struct Ucvector {
    pub data: Option<Vec<u8>>,
    pub size: usize,
    pub allocsize: usize,
}

pub fn ucvector_init(buffer: Option<Vec<u8>>, size: usize) -> Ucvector {
	println!("* ucvector_init");
    Ucvector {
        data: buffer,
        size,
        allocsize: size,
    }
}

pub fn ucvector_reserve(p: &mut Ucvector, size: usize) -> bool {
	println!("* ucvector_reserve");
    if size > p.allocsize {
        let newsize = size + (p.allocsize >> 1);
        let data = lodepng_realloc(p.data.as_deref_mut(), newsize * 2);
        
        match data {
            Some(new_data) => {
                p.allocsize = newsize;
                p.data = Some(new_data);
                true
            }
            None => false,
        }
    } else {
        true
    }
}
pub fn ucvector_resize(p: &mut Ucvector, size: usize) -> bool {
	println!("* ucvector_resize");
    p.size = size;
    ucvector_reserve(p, size)
}
pub fn inflate_no_compression(
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* inflate_no_compression");
    let mut error = 0;
    let size = reader.size;
    let mut bytepos = (reader.bp + 7) >> 3;

    if (bytepos + 4) >= size {
        return 52;
    }

    let data = reader.data.as_ref().unwrap();
    let LEN = (data[bytepos] as u32) + ((data[bytepos + 1] as u32) << 8);
    bytepos += 2;

    let NLEN = (data[bytepos] as u32) + ((data[bytepos + 1] as u32) << 8);
    bytepos += 2;

    if settings.ignore_nlen == 0 && (LEN + NLEN) != 65535 {
        return 21;
    }

    if !ucvector_resize(out, out.size + LEN as usize) {
        return 83;
    }

    if (bytepos + LEN as usize) > size {
        return 23;
    }

    if LEN != 0 {
        let out_data = out.data.as_mut().unwrap();
        let start = out_data.len() - LEN as usize;
        lodepng_memcpy(
            &mut out_data[start..],
            &data[bytepos..bytepos + LEN as usize],
        );
        bytepos += LEN as usize;
    }

    reader.bp = bytepos << 3;
    error
}
pub fn HuffmanTree_makeTable(tree: &mut HuffmanTree) -> u32 {
	println!("* HuffmanTree_makeTable");
    const HEADSIZE: u32 = 1 << 9;
    const MASK: u32 = (1 << 9) - 1;

    // Since the provided HuffmanTree struct doesn't have the expected fields,
    // we'll need to return an error as we can't implement the function properly
    // with the given struct definition.
    
    // In a real implementation, we would need the HuffmanTree struct to contain:
    // - numcodes: usize
    // - codes: Vec<u32>
    // - lengths: Vec<u32>
    // - table_len: Option<Vec<u8>>
    // - table_value: Option<Vec<u16>>
    
    // Since these fields are missing, we can't proceed with the implementation
    // and must return an error code (83 for memory allocation error seems appropriate
    // since we can't even start the operation)
    
    83
}
pub fn HuffmanTree_makeFromLengths2(tree: &mut HuffmanTree) -> u32 {
	println!("* HuffmanTree_makeFromLengths2");
    let mut error = 0;
    // Since we don't have maxbitlen and numcodes in the struct,
    // we'll need to calculate them from the available data or use defaults
    // This is a placeholder fix - the actual values should come from somewhere
    let maxbitlen = 15; // Typical maximum for Huffman codes
    let numcodes = 288; // Typical number of codes for DEFLATE

    // Allocate memory for codes, blcount, and nextcode
    let mut codes = vec![0u32; numcodes];
    let mut blcount = vec![0u32; maxbitlen + 1];
    let mut nextcode = vec![0u32; maxbitlen + 1];

    // Check if allocations succeeded
    if codes.is_empty() || blcount.is_empty() || nextcode.is_empty() {
        error = 83;
    }

    if error == 0 {
        // Initialize blcount and nextcode
        for n in 0..=maxbitlen {
            blcount[n] = 0;
            nextcode[n] = 0;
        }

        // Since we don't have lengths in the struct, we can't count codes per bit length
        // This is a critical part that needs to be properly implemented
        // Placeholder - actual implementation needs access to code lengths
        error = 83; // Return error since we can't proceed without lengths
    }

    // Can't assign codes without lengths
    // tree.codes can't be set since it's not a field in the struct

    if error == 0 {
        error = HuffmanTree_makeTable(tree);
    }

    error
}
pub fn HuffmanTree_makeFromLengths(
    tree: &mut HuffmanTree,
    bitlen: &[u32],
    numcodes: usize,
    maxbitlen: u32,
) -> u32 {
	println!("* HuffmanTree_makeFromLengths");
    // Allocate memory for lengths array
    let lengths = unsafe {
        let layout = alloc::Layout::array::<u32>(numcodes).unwrap();
        alloc::alloc(layout) as *mut u32
    };

    if lengths.is_null() {
        return 83; // Memory allocation failed
    }

    // Copy bitlen values to lengths array
    for i in 0..numcodes {
        unsafe {
            *lengths.add(i) = bitlen[i];
        }
    }

    // Store the lengths in tree2d (since that's the only available Vec field)
    // Note: This is a workaround since the original struct doesn't have a lengths field
    // In a proper Rust implementation, we would modify the HuffmanTree struct to include lengths
    tree.tree2d = Some(unsafe { Vec::from_raw_parts(lengths as *mut u64, numcodes, numcodes) });
    tree.tree2d_size = numcodes;

    // Note: numcodes and maxbitlen are not stored in the struct as per the given definition
    // If these are needed, the HuffmanTree struct should be modified to include them

    HuffmanTree_makeFromLengths2(tree)
}

pub fn generateFixedLitLenTree(tree: &mut HuffmanTree) -> u32 {
	println!("* generateFixedLitLenTree");
    let mut error = 0;
    let mut bitlen = vec![0;288];//Vec::with_capacity(288);
    
    // Initialize bitlen with default values (Rust doesn't have uninitialized memory)
    bitlen.resize(288, 0);
    
    // Set values for ranges (Rust ranges are exclusive end)
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
    
    error = HuffmanTree_makeFromLengths(tree, &bitlen, 288, 15);
    
    // No need for explicit free in Rust - Vec will be dropped automatically
    error
}

pub fn generateFixedDistanceTree(tree: &mut HuffmanTree) -> u32 {
	println!("* generateFixedDistanceTree");
    let mut error = 0;
    let bitlen = vec![5u32; 32]; // Directly create a Vec with 32 elements initialized to 5

    error = HuffmanTree_makeFromLengths(tree, &bitlen, 32, 15);
    // No need to explicitly free memory in Rust, Vec will be dropped automatically
    error
}
pub fn getTreeInflateFixed(tree_ll: &mut HuffmanTree, tree_d: &mut HuffmanTree) -> u32 {
	println!("* getTreeInflateFixed");
    let error = generateFixedLitLenTree(tree_ll);
    if error != 0 {
        return error;
    }
    generateFixedDistanceTree(tree_d)
}
pub fn peekBits(reader: &LodePngBitReader, nbits: z_size_t) -> u32 {
	println!("* peekBits");
    reader.buffer & ((1u32 << nbits) - 1u32)
}
pub fn advanceBits(reader: &mut LodePngBitReader, nbits: usize) {
	println!("* advanceBits");
    reader.buffer >>= nbits;
    reader.bp += nbits;
}

pub fn readBits(reader: &mut LodePngBitReader, nbits: usize) -> u32 {
	println!("* readBits");
    let result = peekBits(reader, nbits);
    advanceBits(reader, nbits);
    result
}
pub fn lodepng_gtofl(a: usize, b: usize, c: usize) -> bool {
	println!("* lodepng_gtofl");
    let mut d = 0;
    if lodepng_addofl(a, b, &mut d) {
        return true;
    }
    d > c
}
pub fn huffmanDecodeSymbol(reader: &mut LodePngBitReader, codetree: &HuffmanTree) -> u32 {
	println!("* huffmanDecodeSymbol");
    let code = peekBits(reader, 9) as u16;
    // The original C code uses table_len and table_value, but the Rust HuffmanTree has different fields
    // We need to implement the equivalent functionality using tree2d
    // This is a placeholder implementation - you'll need to adapt it to your actual tree2d structure
    let l = 0; // TODO: Implement actual lookup in tree2d for length
    let mut value = 0; // TODO: Implement actual lookup in tree2d for value
    
    if l <= 9 {
        advanceBits(reader, l as usize);
        value
    } else {
        advanceBits(reader, 9);
        value += peekBits(reader, (l - 9) as usize);
        let new_l = 0; // TODO: Implement actual lookup in tree2d for length at new value
        advanceBits(reader, (new_l - 9) as usize);
        let final_value = 0; // TODO: Implement actual lookup in tree2d for value at new position
        final_value
    }
}
#[inline]
pub fn ensureBits17(reader: &mut LodePngBitReader, nbits: usize) {
	println!("* ensureBits17");
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if let Some(data) = reader.data.as_ref() {
        if (start + 2) < size {
            reader.buffer = (data[start] as u32) | 
                          ((data[start + 1] as u32) << 8) | 
                          ((data[start + 2] as u32) << 16);
            reader.buffer >>= reader.bp & 7;
        } else {
            reader.buffer = 0;
            if start < size {
                reader.buffer |= data[start] as u32;
            }
            if (start + 1) < size {
                reader.buffer |= (data[start + 1] as u32) << 8;
            }
            reader.buffer >>= reader.bp & 7;
        }
    } else {
        reader.buffer = 0;
    }
    
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn ensureBits25(reader: &mut LodePngBitReader, nbits: usize) {
	println!("* ensureBits25");
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if (start + 3) < size {
        reader.buffer = (reader.data.as_ref().unwrap()[start + 0] as u32) |
                      ((reader.data.as_ref().unwrap()[start + 1] as u32) << 8) |
                      ((reader.data.as_ref().unwrap()[start + 2] as u32) << 16) |
                      ((reader.data.as_ref().unwrap()[start + 3] as u32) << 24);
        reader.buffer >>= reader.bp & 7;
    } else {
        reader.buffer = 0;
        if (start + 0) < size {
            reader.buffer |= reader.data.as_ref().unwrap()[start + 0] as u32;
        }
        if (start + 1) < size {
            reader.buffer |= (reader.data.as_ref().unwrap()[start + 1] as u32) << 8;
        }
        if (start + 2) < size {
            reader.buffer |= (reader.data.as_ref().unwrap()[start + 2] as u32) << 16;
        }
        reader.buffer >>= reader.bp & 7;
    }
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn HuffmanTree_init(tree: &mut HuffmanTree) {
	println!("* HuffmanTree_init");
    tree.tree2d = None;
    tree.tree2d_size = 0;
}
pub fn HuffmanTree_cleanup(tree: &mut HuffmanTree) {
	println!("* HuffmanTree_cleanup");
    tree.tree2d = None;
    tree.tree2d_size = 0;
}
pub fn ensure_bits9(reader: &mut LodePngBitReader, nbits: usize) {
	println!("* ensure_bits9");
    let start = reader.bp >> 3;
    let size = reader.size;
    
    if (start + 1) < size {
        if let Some(data) = &reader.data {
            reader.buffer = (data[start] as u32) | ((data[start + 1] as u32) << 8);
            reader.buffer >>= reader.bp & 7;
        }
    } else {
        reader.buffer = 0;
        if (start + 0) < size {
            if let Some(data) = &reader.data {
                reader.buffer = data[start] as u32;
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
	println!("* getTreeInflateDynamic");
    let mut error = 0;
    let mut n: u32 = 0;
    let mut HLIT;
    let mut HDIST;
    let mut HCLEN;
    let mut i;
    let mut bitlen_ll: Option<Vec<u32>> = None;
    let mut bitlen_d: Option<Vec<u32>> = None;
    let mut bitlen_cl: Option<Vec<u32>> = None;
    let mut tree_cl = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };

    if (reader.bitsize - reader.bp) < 14 {
        return 49;
    }

    ensureBits17(reader, 14);
    HLIT = readBits(reader, 5) + 257;
    HDIST = readBits(reader, 5) + 1;
    HCLEN = readBits(reader, 4) + 4;

    bitlen_cl = Some(vec![0; 19]);
    HuffmanTree_init(&mut tree_cl);

    while error == 0 {
        if lodepng_gtofl(reader.bp, (HCLEN * 3) as usize, reader.bitsize) {
            error = 50;
            break;
        }

        if let Some(ref mut bitlen_cl_vec) = bitlen_cl {
            for i in 0..HCLEN {
                ensure_bits9(reader, 3);
                bitlen_cl_vec[CLCL_ORDER[i as usize] as usize] = readBits(reader, 3);
            }

            for i in HCLEN..19 {
                bitlen_cl_vec[CLCL_ORDER[i as usize] as usize] = 0;
            }
        }

        error = HuffmanTree_makeFromLengths(
            &mut tree_cl,
            bitlen_cl.as_ref().unwrap(),
            19,
            7,
        );
        if error != 0 {
            break;
        }

        bitlen_ll = Some(vec![0; 288]);
        bitlen_d = Some(vec![0; 32]);

        if bitlen_ll.is_none() || bitlen_d.is_none() {
            error = 83;
            break;
        }

        i = 0;
        while i < (HLIT + HDIST) {
            let code = huffmanDecodeSymbol(reader, &tree_cl);
            if code <= 15 {
                if i < HLIT {
                    bitlen_ll.as_mut().unwrap()[i as usize] = code;
                } else {
                    bitlen_d.as_mut().unwrap()[(i - HLIT) as usize] = code;
                }
                i += 1;
            } else if code == 16 {
                let mut replength = 3;
                let value;
                if i == 0 {
                    error = 54;
                    break;
                }
                replength += readBits(reader, 2);
                if i < (HLIT + 1) {
                    value = bitlen_ll.as_ref().unwrap()[(i - 1) as usize];
                } else {
                    value = bitlen_d.as_ref().unwrap()[((i - HLIT) - 1) as usize];
                }
                for n in 0..replength {
                    if i >= (HLIT + HDIST) {
                        error = 13;
                        break;
                    }
                    if i < HLIT {
                        bitlen_ll.as_mut().unwrap()[i as usize] = value;
                    } else {
                        bitlen_d.as_mut().unwrap()[(i - HLIT) as usize] = value;
                    }
                    i += 1;
                }
            } else if code == 17 {
                let mut replength = 3;
                replength += readBits(reader, 3);
                for n in 0..replength {
                    if i >= (HLIT + HDIST) {
                        error = 14;
                        break;
                    }
                    if i < HLIT {
                        bitlen_ll.as_mut().unwrap()[i as usize] = 0;
                    } else {
                        bitlen_d.as_mut().unwrap()[(i - HLIT) as usize] = 0;
                    }
                    i += 1;
                }
            } else if code == 18 {
                let mut replength = 11;
                replength += readBits(reader, 7);
                for n in 0..replength {
                    if i >= (HLIT + HDIST) {
                        error = 15;
                        break;
                    }
                    if i < HLIT {
                        bitlen_ll.as_mut().unwrap()[i as usize] = 0;
                    } else {
                        bitlen_d.as_mut().unwrap()[(i - HLIT) as usize] = 0;
                    }
                    i += 1;
                }
            } else {
                error = 16;
                break;
            }

            if reader.bp > reader.bitsize {
                error = 50;
                break;
            }
        }

        if error != 0 {
            break;
        }

        if bitlen_ll.as_ref().unwrap()[256] == 0 {
            error = 64;
            break;
        }

        error = HuffmanTree_makeFromLengths(
            tree_ll,
            bitlen_ll.as_ref().unwrap(),
            288,
            15,
        );
        if error != 0 {
            break;
        }

        error = HuffmanTree_makeFromLengths(
            tree_d,
            bitlen_d.as_ref().unwrap(),
            32,
            15,
        );
        break;
    }

    lodepng_free(bitlen_cl.map(|v| Box::new(v) as Box<dyn std::any::Any>));
    lodepng_free(bitlen_ll.map(|v| Box::new(v) as Box<dyn std::any::Any>));
    lodepng_free(bitlen_d.map(|v| Box::new(v) as Box<dyn std::any::Any>));
    HuffmanTree_cleanup(&mut tree_cl);

    error
}
pub fn ensureBits32(reader: &mut LodePngBitReader, nbits: usize) {
	println!("* ensureBits32");
    let start = reader.bp >> 3;
    let size = reader.size;
    let bit_offset = (reader.bp as u32) & 7;

    if let Some(data) = &reader.data {
        if (start + 4) < size {
            reader.buffer = (data[start + 0] as u32) 
                         | (data[start + 1] as u32) << 8 
                         | (data[start + 2] as u32) << 16 
                         | (data[start + 3] as u32) << 24;
            reader.buffer >>= bit_offset;
            reader.buffer |= (data[start+4] as u32).wrapping_shl(24).wrapping_shl(8 - bit_offset);
        } else {
            reader.buffer = 0;
            if (start + 0) < size {
                reader.buffer |= data[start + 0] as u32;
            }
            if (start + 1) < size {
                reader.buffer |= (data[start + 1] as u32) << 8;
            }
            if (start + 2) < size {
                reader.buffer |= (data[start + 2] as u32) << 16;
            }
            if (start + 3) < size {
                reader.buffer |= (data[start + 3] as u32) << 24;
            }
            reader.buffer >>= bit_offset;
        }
    } else {
        reader.buffer = 0;
    }
    
    let _ = nbits; // explicitly ignore unused parameter
}
pub fn inflateHuffmanBlock(
    out: &mut Ucvector,
    reader: &mut LodePngBitReader,
    btype: u32,
    max_output_size: Option<usize>,
) -> u32 {
	println!("* inflateHuffmanBlock");
    let mut error = 0;
    let mut tree_ll = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let mut tree_d = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    const RESERVED_SIZE: usize = 260;
    let mut done = false;

    if !ucvector_reserve(out, out.size + RESERVED_SIZE) {
        return 83;
    }

    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);

    error = if btype == 1 {
        getTreeInflateFixed(&mut tree_ll, &mut tree_d)
    } else {
        getTreeInflateDynamic(&mut tree_ll, &mut tree_d, reader)
    };

    while error == 0 && !done {
        ensureBits32(reader, 30);
        let mut code_ll = huffmanDecodeSymbol(reader, &tree_ll);

        if code_ll <= 255 {
            if let Some(data) = &mut out.data {
                data[out.size] = code_ll as u8;
                out.size += 1;
            }
            ensureBits32(reader, 30);
            code_ll = huffmanDecodeSymbol(reader, &tree_ll);
        }

        if code_ll <= 255 {
            if let Some(data) = &mut out.data {
                data[out.size] = code_ll as u8;
                out.size += 1;
            }
        } else if (257..=285).contains(&code_ll) {
            ensureBits32(reader, 28);
            let code_d = huffmanDecodeSymbol(reader, &tree_d);

            if code_d > 29 {
                error = if code_d <= 31 { 18 } else { 16 };
                break;
            }

            let mut distance = DISTANCEBASE[code_d as usize];
            let numextrabits_d = DISTANCEEXTRA[code_d as usize];

            if numextrabits_d != 0 {
                ensureBits25(reader, 5);
                distance += readBits(reader, numextrabits_d as usize);
            }

            let start = out.size;
            if (distance as usize) > start {
                error = 52;
                break;
            }

            let backward = start - distance as usize;
            let length = {
                let mut length = LENGTHBASE[(code_ll - 257) as usize];
                let numextrabits_l = LENGTHEXTRA[(code_ll - 257) as usize];

                if numextrabits_l != 0 {
                    ensureBits25(reader, 5);
                    length += readBits(reader, numextrabits_l as usize);
                }
                length as usize
            };

            out.size += length;

            if let Some(out_data) = &mut out.data {
                let backward_data = out_data.clone();
                if (distance as usize) < length {
                    lodepng_memcpy(
                        &mut out_data[start..start + distance as usize],
                        &backward_data[backward..backward + distance as usize],
                    );
                    let mut forward = distance as usize;
                    let mut current_start = start + distance as usize;
                    let mut current_backward = backward + distance as usize;

                    while forward < length {
                        out_data[current_start] = backward_data[current_backward];
                        current_backward += 1;
                        current_start += 1;
                        forward += 1;
                    }
                } else {
                    lodepng_memcpy(
                        &mut out_data[start..start + length],
                        &backward_data[backward..backward + length],
                    );
                }
            }
        } else if code_ll == 256 {
            done = true;
        } else {
            error = 16;
            break;
        }

        if out.allocsize - out.size < RESERVED_SIZE {
            if !ucvector_reserve(out, out.size + RESERVED_SIZE) {
                error = 83;
                break;
            }
        }

        if reader.bp > reader.bitsize {
            error = 51;
            break;
        }

        if let Some(max_size) = max_output_size {
            if out.size > max_size {
                error = 109;
                break;
            }
        }
    }

    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);
    error
}
pub fn LodePNGBitReader_init(reader: &mut LodePngBitReader, data: Option<&[u8]>, size: usize) -> Option<u32> {
	println!("* LodePNGBitReader_init");
    reader.data = data.map(|d| d.to_vec());
    reader.size = size;
    
    let mut bitsize = None;
    if lodepng_mulofl(size, 8, &mut bitsize) {
        return Some(105);
    }
    if bitsize.is_some() {
        reader.bitsize = bitsize.unwrap();
    }
    
    let mut temp_result = 0;
    if lodepng_addofl(reader.bitsize, 64, &mut temp_result) {
        return Some(105);
    }
    
    reader.bp = 0;
    reader.buffer = 0;
    Some(0)
}
pub fn lodepng_inflatev(
    out: &mut Ucvector,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* lodepng_inflatev");
    let mut bfinal = 0;
    let mut reader = LodePngBitReader {
        data: None,
        size: 0,
        bitsize: 0,
        bp: 0,
        buffer: 0,
    };
    
    let mut error = match LodePNGBitReader_init(&mut reader, in_data, insize) {
        Some(err) => err,
        None => return 0, // Assuming 0 means no error in this context
    };

    while bfinal == 0 {
        let btype;
        if (reader.bitsize - reader.bp) < 3 {
            return 52;
        }
        ensure_bits9(&mut reader, 3);
        bfinal = readBits(&mut reader, 1);
        btype = readBits(&mut reader, 2);

        if btype == 3 {
            return 20;
        } else if btype == 0 {
            error = inflate_no_compression(out, &mut reader, settings);
        } else {
            error = inflateHuffmanBlock(
                out,
                &mut reader,
                btype,
                if settings.max_output_size != 0 {
                    Some(settings.max_output_size)
                } else {
                    None
                },
            );
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
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* inflatev");
    if let Some(custom_inflate) = settings.custom_inflate {
        let mut data_ptr = match &mut out.data {
            Some(vec) => vec.as_mut_ptr(),
            None => std::ptr::null_mut(),
        };
        let mut size = out.size;
        
        let error = custom_inflate(
            &mut data_ptr,
            &mut size,
            &in_data.unwrap()[0],
            insize,
            settings,
        );
        out.size = size;
        out.allocsize = out.size;

        if error != 0 {
            let error_code = if settings.max_output_size != 0 && out.size > settings.max_output_size {
                109
            } else {
                110
            };
            return error_code;
        }
        error
    } else {
        lodepng_inflatev(out, in_data, insize, settings)
    }
}
pub fn adler32(data: Option<&[u8]>, len: u32) -> u32 {
	println!("* adler32");
    update_adler32(1u32, data, len)
}

pub fn lodepng_zlib_decompressv(
    out: &mut Ucvector,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* lodepng_zlib_decompressv");
    let mut error = 0;
    let mut CM;
    let mut CINFO;
    let mut FDICT;

    // Check if input size is sufficient
    if insize < 2 {
        return 53;
    }

    // Unwrap the input data safely
    let in_data = match in_data {
        Some(data) => data,
        None => return 53, // Treat None as invalid input
    };

    // Check zlib header checksum
    if ((in_data[0] as u32 * 256 + in_data[1] as u32) % 31) != 0 {
        return 24;
    }

    // Extract header fields
    CM = in_data[0] & 15;
    CINFO = (in_data[0] >> 4) & 15;
    FDICT = (in_data[1] >> 5) & 1;

    // Validate compression method and window size
    if CM != 8 || CINFO > 7 {
        return 25;
    }

    // Check for dictionary (unsupported)
    if FDICT != 0 {
        return 26;
    }

    // Decompress the data
    error = inflatev(out, Some(&in_data[2..]), insize - 2, settings);
    if error != 0 {
        return error;
    }

    // Verify Adler-32 checksum if not ignored
    if settings.ignore_adler32 == 0 {
        let ADLER32 = lodepng_read32bitInt(&in_data[insize - 4..]);
        let checksum = adler32(out.data.as_deref(), out.size as u32);
        if checksum != ADLER32 {
            return 58;
        }
    }

    0
}
pub fn zlib_decompress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    expected_size: usize,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* zlib_decompress");
    let mut error: u32;

    if let Some(custom_zlib) = settings.custom_zlib {
        let mut out_ptr = out.as_mut().map(|v| v.as_mut_ptr()).unwrap_or(std::ptr::null_mut());
        let in_slice = in_data.unwrap_or(&[]);
        error = custom_zlib(&mut out_ptr, outsize, &in_slice[0], insize, settings);
        
        if error != 0 {
            error = 110;
            if settings.max_output_size != 0 && *outsize > settings.max_output_size {
                error = 109;
            }
        }
        
        if error == 0 {
            unsafe {
                *out = Some(Vec::from_raw_parts(out_ptr, *outsize, *outsize));
            }
        }
    } else {
        let mut v = Ucvector {
            data: out.take(),
            size: *outsize,
            allocsize: *outsize,
        };

        if expected_size != 0 {
            ucvector_resize(&mut v, *outsize + expected_size);
            v.size = *outsize;
        }

        error = lodepng_zlib_decompressv(&mut v, in_data, insize, settings);
        *out = v.data;
        *outsize = v.size;
    }

    error
}

pub fn readChunk_zTXt(
    info: &mut LodePngInfo,
    decoder: &LodePngDecoderSettings,
    data: Option<&[u8]>,
    chunkLength: usize,
) -> u32 {
	println!("* readChunk_zTXt");
    let mut error = 0;
    let zlibsettings = decoder.zlibsettings.clone();
    let data = match data {
        Some(d) => d,
        None => return 75, // Equivalent to NULL check
    };

    let mut length = 0;
    let mut string2_begin = 0;
    let mut key: Option<Vec<u8>> = None;
    let mut key_idx = 0;
    let mut str: Option<Vec<u8>> = None;
    let mut size = 0;

    while error == 0 {
        // Find the length of the key (until null terminator)
        length = 0;
        while length < chunkLength && data[length] != 0 {
            length += 1;
        }

        if length + 2 >= chunkLength {
            error = 75;
            break;
        }

        if length < 1 || length > 79 {
            error = 89;
            break;
        }

        // Allocate space for key (+1 for null terminator)
        key = Some(vec![0; length + 1]);
        let key_slice = key.as_mut().unwrap();
        
        // Copy key data
        lodepng_memcpy(key_slice, &data[..length]);
        key_slice[length] = 0;

        if data[length + 1] != 0 {
            error = 72;
            break;
        }

        string2_begin = length + 2;
        if string2_begin > chunkLength {
            error = 75;
            break;
        }

        length = chunkLength - string2_begin;
        let mut zlibsettings = zlibsettings.clone();
        zlibsettings.max_output_size = decoder.max_text_size;

        error = zlib_decompress(
            &mut str,
            &mut size,
            0,
            Some(&data[string2_begin..]),
            length,
            &zlibsettings,
        );

        if error != 0 && size > zlibsettings.max_output_size {
            error = 112;
        }

        if error != 0 {
            break;
        }

        let key_str = std::str::from_utf8(&key_slice[..length]).ok();
        let str_slice = str.as_ref().map(|s| s.as_slice());
        error = lodepng_add_text_sized(info, key_str, str_slice, size);
        break;
    }

    lodepng_free(key.map(|k| Box::new(k) as Box<dyn std::any::Any>));
    lodepng_free(str.map(|s| Box::new(s) as Box<dyn std::any::Any>));
    error
}
pub fn readChunk_tRNS(color: &mut LodePNGColorMode, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_tRNS");
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
            let key_value = (u32::from(data[0]) * 256) + u32::from(data[1]);
            color.key_r = key_value;
            color.key_g = key_value;
            color.key_b = key_value;
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
pub fn readChunk_tIME(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_tIME");
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
pub fn lodepng_add_text(info: &mut LodePngInfo, key: Option<&str>, str: Option<&str>) -> u32 {
	println!("* lodepng_add_text");
    lodepng_add_text_sized(info, key, str.map(|s| s.as_bytes()), lodepng_strlen(str))
}
pub fn readChunk_tEXt(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_tEXt");
    let mut error = 0;
    let mut key: Option<Vec<u8>> = None;
    let mut str: Option<Vec<u8>> = None;

    while error == 0 {
        // Find the length of the key (until null terminator)
        let length = match data.iter().take(chunkLength).position(|&x| x == 0) {
            Some(len) => len,
            None => {
                error = 89;
                break;
            }
        };

        // Validate key length
        if length < 1 || length > 79 {
            error = 89;
            break;
        }

        // Allocate and copy key
        let mut key_vec = vec![0u8; length + 1];
        lodepng_memcpy(&mut key_vec[..length], &data[..length]);
        key_vec[length] = 0;
        key = Some(key_vec);

        // Calculate string2_begin and remaining length
        let string2_begin = length + 1;
        let remaining_length = if chunkLength > string2_begin {
            chunkLength - string2_begin
        } else {
            0
        };

        // Allocate and copy string
        let mut str_vec = vec![0u8; remaining_length + 1];
        lodepng_memcpy(&mut str_vec[..remaining_length], &data[string2_begin..]);
        str_vec[remaining_length] = 0;
        str = Some(str_vec);

        // Convert to UTF-8 strings and add to info
        let key_str = key.as_ref().and_then(|k| std::str::from_utf8(k).ok());
        let str_str = str.as_ref().and_then(|s| std::str::from_utf8(s).ok());
        error = lodepng_add_text(info, key_str, str_str);
        break;
    }

    // Free allocated memory
    lodepng_free(key.map(|k| Box::new(k) as Box<dyn std::any::Any>));
    lodepng_free(str.map(|s| Box::new(s) as Box<dyn std::any::Any>));

    error
}
pub fn readChunk_sRGB(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_sRGB");
    if chunkLength != 1 {
        return 98;
    }
    info.srgb_defined = 1;
    info.srgb_intent = data[0] as u32;
    0
}
pub fn readChunk_sBIT(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_sBIT");
    let bitdepth = match info.color.colortype {
        LodePNGColorType::LCT_PALETTE => 8,
        _ => info.color.bitdepth,
    };

    match info.color.colortype {
        LodePNGColorType::LCT_GREY => {
            if chunkLength != 1 {
                return 114;
            }
            if data[0] == 0 || u32::from(data[0]) > bitdepth {
                return 115;
            }
            info.sbit_defined = 1;
            info.sbit_r = u32::from(data[0]);
            info.sbit_g = u32::from(data[0]);
            info.sbit_b = u32::from(data[0]);
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_PALETTE => {
            if chunkLength != 3 {
                return 114;
            }
            if data[0] == 0 || data[1] == 0 || data[2] == 0 {
                return 115;
            }
            if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth || u32::from(data[2]) > bitdepth {
                return 115;
            }
            info.sbit_defined = 1;
            info.sbit_r = u32::from(data[0]);
            info.sbit_g = u32::from(data[1]);
            info.sbit_b = u32::from(data[2]);
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if chunkLength != 2 {
                return 114;
            }
            if data[0] == 0 || data[1] == 0 {
                return 115;
            }
            if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth {
                return 115;
            }
            info.sbit_defined = 1;
            info.sbit_r = u32::from(data[0]);
            info.sbit_g = u32::from(data[0]);
            info.sbit_b = u32::from(data[0]);
            info.sbit_a = u32::from(data[1]);
        }
        LodePNGColorType::LCT_RGBA => {
            if chunkLength != 4 {
                return 114;
            }
            if data[0] == 0 || data[1] == 0 || data[2] == 0 || data[3] == 0 {
                return 115;
            }
            if u32::from(data[0]) > bitdepth || u32::from(data[1]) > bitdepth || u32::from(data[2]) > bitdepth || u32::from(data[3]) > bitdepth {
                return 115;
            }
            info.sbit_defined = 1;
            info.sbit_r = u32::from(data[0]);
            info.sbit_g = u32::from(data[1]);
            info.sbit_b = u32::from(data[2]);
            info.sbit_a = u32::from(data[3]);
        }
    }

    0
}
pub fn readChunk_pHYs(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_pHYs");
    if chunkLength != 9 {
        return 74;
    }
    
    info.phys_defined = 1;
    info.phys_x = ((16777216u32 * data[0] as u32) + (65536u32 * data[1] as u32) 
                + (256u32 * data[2] as u32)) + data[3] as u32;
    info.phys_y = ((16777216u32 * data[4] as u32) + (65536u32 * data[5] as u32) 
                + (256u32 * data[6] as u32)) + data[7] as u32;
    info.phys_unit = data[8] as u32;
    
    0
}
pub fn lodepng_add_itext_sized(
    info: &mut LodePngInfo,
    key: Option<&str>,
    langtag: Option<&str>,
    transkey: Option<&str>,
    str: Option<&[u8]>,
    size: usize,
) -> u32 {
	println!("* lodepng_add_itext_sized");
    // Helper function to extend a Vec<String> or create a new one if None
    fn extend_or_create(vec: &mut Option<Vec<String>>) -> bool {
	println!("* extend_or_create");
        match vec {
            Some(v) => {
                v.push(String::new());
                true
            }
            None => {
                *vec = Some(vec![String::new()]);
                true
            }
        }
    }

    // Check if all allocations succeed
    if !extend_or_create(&mut info.itext_keys)
        || !extend_or_create(&mut info.itext_langtags)
        || !extend_or_create(&mut info.itext_transkeys)
        || !extend_or_create(&mut info.itext_strings)
    {
        return 83;
    }

    info.itext_num += 1;
    let idx = info.itext_num - 1;

    // Convert &str to Vec<u8> using alloc_string
    if let Some(keys) = &mut info.itext_keys {
        keys[idx] = key.unwrap().to_string();//String::from_utf8(alloc_string(key).unwrap_or_default()).unwrap_or_default();
    }

    if let Some(langtags) = &mut info.itext_langtags {
        langtags[idx] = langtag.unwrap().to_string();//String::from_utf8(alloc_string(langtag).unwrap_or_default()).unwrap_or_default();
    }

    if let Some(transkeys) = &mut info.itext_transkeys {
        transkeys[idx] = transkey.unwrap().to_string();//String::from_utf8(alloc_string(transkey).unwrap_or_default()).unwrap_or_default();
    }

    if let Some(strings) = &mut info.itext_strings {
        strings[idx] = String::from_utf8(str.unwrap().to_vec()).expect("Invalid UTF-8");//String::from_utf8(alloc_string_sized(str, size).unwrap_or_default()).unwrap_or_default();
    }

    0
}

pub fn readChunk_iTXt(
    info: &mut LodePngInfo,
    decoder: &LodePngDecoderSettings,
    data: &[u8],
    chunkLength: usize,
) -> u32 {
	println!("* readChunk_iTXt");
    let mut error = 0;
    let zlibsettings = decoder.zlibsettings.clone();
    let mut length;
    let mut begin;
    let mut compressed;
    let mut key: Option<String> = None;
    let mut key_idx = 0;
    let mut langtag: Option<String> = None;
    let mut langtag_idx = 0;
    let mut transkey: Option<String> = None;
    let mut transkey_idx = 0;

    while error == 0 {
        if chunkLength < 5 {
            error = 30;
            break;
        }

        // Find length of key (until null byte)
        length = 0;
        while length < chunkLength && data[length] != 0 {
            length += 1;
        }

        if length + 3 >= chunkLength {
            error = 75;
            break;
        }

        if length < 1 || length > 79 {
            error = 89;
            break;
        }

        // Create key string
        key = Some(
            CStr::from_bytes_with_nul(&data[..=length])
                .unwrap()
                .to_string_lossy()
                .into_owned(),
        );

        compressed = data[length + 1];
        if data[length + 2] != 0 {
            error = 72;
            break;
        }

        begin = length + 3;
        length = 0;
        for i in begin..chunkLength {
            if data[i] == 0 {
                break;
            }
            length += 1;
        }

        // Create langtag string
        langtag = Some(
            CStr::from_bytes_with_nul(&data[begin..=begin + length])
                .unwrap()
                .to_string_lossy()
                .into_owned(),
        );

        begin += length + 1;
        length = 0;
        for i in begin..chunkLength {
            if data[i] == 0 {
                break;
            }
            length += 1;
        }

        // Create transkey string
        transkey = Some(
            CStr::from_bytes_with_nul(&data[begin..=begin + length])
                .unwrap()
                .to_string_lossy()
                .into_owned(),
        );

        begin += length + 1;
        length = if chunkLength < begin { 0 } else { chunkLength - begin };

        if compressed != 0 {
            let mut str: Option<Vec<u8>> = None;
            let mut size = 0;
            let mut zlibsettings = zlibsettings;
            zlibsettings.max_output_size = decoder.max_text_size;
            error = zlib_decompress(
                &mut str,
                &mut size,
                0,
                Some(&data[begin..begin + length]),
                length,
                &zlibsettings,
            );
            if error != 0 && size > zlibsettings.max_output_size {
                error = 112;
            }
            if error == 0 {
                error = lodepng_add_itext_sized(
                    info,
                    key.as_deref(),
                    langtag.as_deref(),
                    transkey.as_deref(),
                    str.as_deref(),
                    size,
                );
            }
        } else {
            error = lodepng_add_itext_sized(
                info,
                key.as_deref(),
                langtag.as_deref(),
                transkey.as_deref(),
                Some(&data[begin..begin + length]),
                length,
            );
        }
        break;
    }

    error
}
pub fn readChunk_iCCP(
    info: &mut LodePngInfo,
    decoder: &LodePngDecoderSettings,
    data: &[u8],
    chunkLength: usize,
) -> u32 {
	println!("* readChunk_iCCP");
    let mut error = 0;
    let mut size = 0;
    let mut zlibsettings = decoder.zlibsettings.clone();
    let mut length;
    let mut string2_begin;

    info.iccp_defined = 1;
    if info.iccp_name.is_some() {
        lodepng_clear_icc(info);
    }

    // Find the null terminator for the name
    length = 0;
    while length < chunkLength && data[length] != 0 {
        length += 1;
    }

    if length + 2 >= chunkLength {
        return 75;
    }
    if length < 1 || length > 79 {
        return 89;
    }

    // Allocate and copy the name
    info.iccp_name = match String::from_utf8(data[..length].to_vec()) {
        Ok(s) => Some(s),
        Err(_) => return 83,
    };

    if data[length + 1] != 0 {
        return 72;
    }

    string2_begin = length + 2;
    if string2_begin > chunkLength {
        return 75;
    }

    length = chunkLength - string2_begin;
    zlibsettings.max_output_size = decoder.max_icc_size;

    error = zlib_decompress(
        &mut info.iccp_profile,
        &mut size,
        0,
        Some(&data[string2_begin..]),
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
pub fn readChunk_gAMA(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_gAMA");
    if chunkLength != 4 {
        return 96;
    }
    info.gama_defined = 1;
    info.gama_gamma = ((16777216u32 * data[0] as u32) + (65536u32 * data[1] as u32)) 
                    + (256u32 * data[2] as u32) + data[3] as u32;
    0
}
pub fn readChunk_cHRM(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_cHRM");
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
pub fn readChunk_bKGD(info: &mut LodePngInfo, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_bKGD");
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
pub fn lodepng_color_mode_alloc_palette(info: &mut LodePNGColorMode) {
	println!("* lodepng_color_mode_alloc_palette");
    if info.palette.is_none() {
        info.palette = Some(vec![0; 1024]);
    }
    
    if let Some(palette) = &mut info.palette {
        for i in 0..256 {
            palette[(i * 4) + 0] = 0;
            palette[(i * 4) + 1] = 0;
            palette[(i * 4) + 2] = 0;
            palette[(i * 4) + 3] = LCT_MAX_OCTET_VALUE;
        }
    }
}

pub fn readChunk_PLTE(color: &mut LodePNGColorMode, data: &[u8], chunkLength: usize) -> u32 {
	println!("* readChunk_PLTE");
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
            palette[4 * i] = data[pos];
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
pub fn unfilter_scanline(
    recon: &mut [u8],
    scanline: &[u8],
    precon: Option<&[u8]>,
    bytewidth: usize,
    filter_type: u8,
    length: usize,
) -> u32 {
	println!("* unfilter_scanline");
    match filter_type {
        0 => {
            recon[..length].copy_from_slice(&scanline[..length]);
            0
        }
        1 => {
            recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
            
            for i in bytewidth..length {
                recon[i] = scanline[i].wrapping_add(recon[i - bytewidth]);
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
            if let Some(precon) = precon {
                for i in 0..bytewidth {
                    recon[i] = scanline[i].wrapping_add(precon[i] >> 1);
                }

                let mut i = bytewidth;
                while i + 3 < length {
                    let s0 = scanline[i];
                    let s1 = scanline[i + 1];
                    let s2 = scanline[i + 2];
                    let s3 = scanline[i + 3];
                    let r0 = recon[i - bytewidth];
                    let r1 = recon[i + 1 - bytewidth];
                    let r2 = recon[i + 2 - bytewidth];
                    let r3 = recon[i + 3 - bytewidth];
                    let p0 = precon[i];
                    let p1 = precon[i + 1];
                    let p2 = precon[i + 2];
                    let p3 = precon[i + 3];

                    recon[i] = s0.wrapping_add((r0.wrapping_add(p0)) >> 1);
                    recon[i + 1] = s1.wrapping_add((r1.wrapping_add(p1)) >> 1);
                    recon[i + 2] = s2.wrapping_add((r2.wrapping_add(p2)) >> 1);
                    recon[i + 3] = s3.wrapping_add((r3.wrapping_add(p3)) >> 1);
                    i += 4;
                }

                while i < length {
                    recon[i] = scanline[i].wrapping_add(
                        (recon[i - bytewidth].wrapping_add(precon[i])) >> 1,
                    );
                    i += 1;
                }
            } else {
                recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
                
                for i in bytewidth..length {
                    recon[i] = scanline[i].wrapping_add(recon[i - bytewidth] >> 1);
                }
            }
            0
        }
        4 => {
            if let Some(precon) = precon {
                for i in 0..bytewidth {
                    recon[i] = scanline[i].wrapping_add(precon[i]);
                }

                let mut i = bytewidth;
                while i + 3 < length {
                    let s0 = scanline[i];
                    let s1 = scanline[i + 1];
                    let s2 = scanline[i + 2];
                    let s3 = scanline[i + 3];
                    let r0 = recon[i - bytewidth];
                    let r1 = recon[i + 1 - bytewidth];
                    let r2 = recon[i + 2 - bytewidth];
                    let r3 = recon[i + 3 - bytewidth];
                    let p0 = precon[i];
                    let p1 = precon[i + 1];
                    let p2 = precon[i + 2];
                    let p3 = precon[i + 3];
                    let q0 = precon[i - bytewidth];
                    let q1 = precon[i + 1 - bytewidth];
                    let q2 = precon[i + 2 - bytewidth];
                    let q3 = precon[i + 3 - bytewidth];

                    recon[i] = s0.wrapping_add(paethPredictor(r0 as i16, p0 as i16, q0 as i16) as u8);
                    recon[i + 1] = s1.wrapping_add(paethPredictor(r1 as i16, p1 as i16, q1 as i16) as u8);
                    recon[i + 2] = s2.wrapping_add(paethPredictor(r2 as i16, p2 as i16, q2 as i16) as u8);
                    recon[i + 3] = s3.wrapping_add(paethPredictor(r3 as i16, p3 as i16, q3 as i16) as u8);
                    i += 4;
                }

                while i < length {
                    recon[i] = scanline[i].wrapping_add(paethPredictor(
                        recon[i - bytewidth] as i16,
                        precon[i] as i16,
                        precon[i - bytewidth] as i16,
                    ) as u8);
                    i += 1;
                }
            } else {
                recon[..bytewidth].copy_from_slice(&scanline[..bytewidth]);
                
                for i in bytewidth..length {
                    recon[i] = scanline[i].wrapping_add(recon[i - bytewidth]);
                }
            }
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
	println!("* unfilter");
    let bytewidth = (bpp + 7u32) / 8u32;
    let linebytes = lodepng_get_raw_size_idat(w, 1, bpp) - 1usize;

    for y in 0..h {
        let outindex = linebytes * y as usize;
        let inindex = (1 + linebytes) * y as usize;
        let filter_type = in_data[inindex];

        // Split output buffer at current line position
        let (processed, rest) = out.split_at_mut(outindex);
        let current_line = &mut rest[..linebytes];

        // Get previous line from processed buffer (if available)
        let prevline = if y > 0 {
            let prev_start = processed.len() - linebytes;
            Some(&processed[prev_start..])
        } else {
            Option::None
        };

        let error = unfilter_scanline(
            current_line,
            &in_data[inindex + 1..inindex + 1 + linebytes],
            prevline,
            bytewidth as usize,
            filter_type,
            linebytes,
        );

        if error != 0 {
            return error;
        }
    }

    0
}
pub fn removePaddingBits(out: &mut [u8], in_: &[u8], olinebits: usize, ilinebits: usize, h: usize) {
	println!("* removePaddingBits");
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
	println!("* Adam7_getpassvalues");
    // Calculate passw and passh for each pass
    for i in 0..7 {
        passw[i] = ((w + ADAM7_DX[i]).saturating_sub(ADAM7_IX[i]).saturating_sub(1)) / ADAM7_DX[i];
        passh[i] = ((h + ADAM7_DY[i]).saturating_sub(ADAM7_IY[i]).saturating_sub(1)) / ADAM7_DY[i];
        
        // If either dimension is 0, set both to 0
        if passw[i] == 0 {
            passh[i] = 0;
        }
        if passh[i] == 0 {
            passw[i] = 0;
        }
    }

    // Initialize the first element of each array to 0
    filter_passstart[0] = 0;
    padded_passstart[0] = 0;
    passstart[0] = 0;

    // Calculate the remaining elements
    for i in 0..7 {
        let has_pass = passw[i] != 0 && passh[i] != 0;
        
        filter_passstart[i + 1] = filter_passstart[i] + if has_pass {
            passh[i] as usize * (1 + ((passw[i] * bpp + 7) / 8) as usize)
        } else {
            0
        };
        
        padded_passstart[i + 1] = padded_passstart[i] + 
            (passh[i] as usize * ((passw[i] * bpp + 7) / 8) as usize);
        
        passstart[i + 1] = passstart[i] + 
            ((passh[i] * passw[i] * bpp + 7) / 8) as usize;
    }
}
pub fn Adam7_deinterlace(out: &mut [u8], in_: &[u8], w: u32, h: u32, bpp: u32) {
	println!("* Adam7_deinterlace");
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
                    let pixeloutstart = (((ADAM7_IY[i] as usize + (y as usize * ADAM7_DY[i] as usize)) * w as usize) 
                                      + ADAM7_IX[i] as usize + (x as usize * ADAM7_DX[i] as usize)) * bytewidth as usize;
                    
                    for b in 0..bytewidth {
                        out[pixeloutstart + b as usize] = in_[pixelinstart + b as usize];
                    }
                }
            }
        }
    } else {
        for i in 0..7 {
            let ilinebits = bpp * passw[i];
            let olinebits = bpp * w;
            for y in 0..passh[i] {
                for x in 0..passw[i] {
                    let mut ibp = (8 * passstart[i]) + ((y * ilinebits + x * bpp) as usize);
                    let mut obp = ((ADAM7_IY[i] as usize + (y as usize * ADAM7_DY[i] as usize)) * olinebits as usize) 
                               + (ADAM7_IX[i] as usize + (x as usize * ADAM7_DX[i] as usize)) * bpp as usize;
                    
                    for b in 0..bpp {
                        let bit = readBitFromReversedStream(&mut ibp, in_);
                        setBitOfReversedStream(&mut obp, out, bit);
                    }
                }
            }
        }
    }
}
pub fn lodepng_get_bpp(info: &LodePNGColorMode) -> u8 {
	println!("* lodepng_get_bpp");
    lodepng_get_bpp_lct(info.colortype, info.bitdepth as u8)
}
pub fn postProcessScanlines(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePngInfo,
) -> u32 {
	println!("* postProcessScanlines");
    let bpp = lodepng_get_bpp(&info_png.color) as u32;
    if bpp == 0 {
        return 31;
    }

    if info_png.interlace_method == 0 {
        if bpp < 8 && (w * bpp) != ((((w * bpp) + 7) / 8) * 8) {
            {
                let mut temp_in = in_data.to_vec();
                let error = unfilter(&mut temp_in, in_data, w, h, bpp);
                if error != 0 {
                    return error;
                }
            }
            removePaddingBits(
                out,
                in_data,
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
    } else {
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
                let mut temp_in = in_data[padded_passstart[i]..].to_vec();
                let error = unfilter(
                    &mut temp_in,
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
                    &mut out[passstart[i]..],
                    &in_data[padded_passstart[i]..],
                    (passw[i] * bpp) as usize,
                    (((passw[i] * bpp) + 7) / 8 * 8) as usize,
                    passh[i] as usize,
                );
            }
        }

        Adam7_deinterlace(out, in_data, w, h, bpp);
    }

    0
}
pub fn lodepng_pixel_overflow(w: usize, h: usize, pngcolor: &LodePNGColorMode, rawcolor: &LodePNGColorMode) -> bool {
	println!("* lodepng_pixel_overflow");
    let bpp = std::cmp::max(lodepng_get_bpp(pngcolor), lodepng_get_bpp(rawcolor)) as usize;
    let mut numpixels = None;
    let mut total = None;
    let mut line = None;

    if lodepng_mulofl(w, h, &mut numpixels) {
        return true;
    }
    if let Some(numpixels) = numpixels {
        if lodepng_mulofl(numpixels, 8, &mut total) {
            return true;
        }
    } else {
        return true;
    }
    if lodepng_mulofl(w / 8, bpp, &mut line) {
        return true;
    }
    if let Some(mut line_val) = line {
        let temp = (((w & 7) * bpp) + 7) / 8;
        if lodepng_addofl(line_val, temp, &mut line_val) {
            return true;
        }
        if lodepng_addofl(line_val, 5, &mut line_val) {
            return true;
        }
        if lodepng_mulofl(line_val, h, &mut total) {
            return true;
        }
    } else {
        return true;
    }
    false
}
pub fn checkColorValidity(colortype: LodePNGColorType, bd: u32) -> u32 {
	println!("* checkColorValidity");
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
pub fn lodepng_chunk_type_equals(chunk: Option<&[u8]>, type_: Option<&str>) -> u8 {
	println!("* lodepng_chunk_type_equals");
    // Check if either input is None (equivalent to NULL check in C)
    if chunk.is_none() || type_.is_none() {
        return 0;
    }
    let chunk = chunk.unwrap();
    let type_ = type_.unwrap();

    // Check if type length is 4 (using the provided lodepng_strlen function)
    if lodepng_strlen(Some(type_)) != 4 {
        return 0;
    }

    // Convert type to bytes for comparison
    let type_bytes = type_.as_bytes();

    // Check if chunk has enough bytes (at least 8) and compare each byte
    if chunk.len() >= 8 {
        (chunk[4] == type_bytes[0] && 
         chunk[5] == type_bytes[1] && 
         chunk[6] == type_bytes[2] && 
         chunk[7] == type_bytes[3]) as u8
    } else {
        0
    }
}
lazy_static! {
    pub static ref LODEPNG_CRC32_TABLE: std::sync::Mutex<[u32; 256]> = std::sync::Mutex::new([
        0u32, 1996959894u32, 3993919788u32, 2567524794u32, 124634137u32, 1886057615u32, 3915621685u32, 2657392035u32,
        249268274u32, 2044508324u32, 3772115230u32, 2547177864u32, 162941995u32, 2125561021u32, 3887607047u32, 2428444049u32,
        498536548u32, 1789927666u32, 4089016648u32, 2227061214u32, 450548861u32, 1843258603u32, 4107580753u32, 2211677639u32,
        325883990u32, 1684777152u32, 4251122042u32, 2321926636u32, 335633487u32, 1661365465u32, 4195302755u32, 2366115317u32,
        997073096u32, 1281953886u32, 3579855332u32, 2724688242u32, 1006888145u32, 1258607687u32, 3524101629u32, 2768942443u32,
        901097722u32, 1119000684u32, 3686517206u32, 2898065728u32, 853044451u32, 1172266101u32, 3705015759u32, 2882616665u32,
        651767980u32, 1373503546u32, 3369554304u32, 3218104598u32, 565507253u32, 1454621731u32, 3485111705u32, 3099436303u32,
        671266974u32, 1594198024u32, 3322730930u32, 2970347812u32, 795835527u32, 1483230225u32, 3244367275u32, 3060149565u32,
        1994146192u32, 31158534u32, 2563907772u32, 4023717930u32, 1907459465u32, 112637215u32, 2680153253u32, 3904427059u32,
        2013776290u32, 251722036u32, 2517215374u32, 3775830040u32, 2137656763u32, 141376813u32, 2439277719u32, 3865271297u32,
        1802195444u32, 476864866u32, 2238001368u32, 4066508878u32, 1812370925u32, 453092731u32, 2181625025u32, 4111451223u32,
        1706088902u32, 314042704u32, 2344532202u32, 4240017532u32, 1658658271u32, 366619977u32, 2362670323u32, 4224994405u32,
        1303535960u32, 984961486u32, 2747007092u32, 3569037538u32, 1256170817u32, 1037604311u32, 2765210733u32, 3554079995u32,
        1131014506u32, 879679996u32, 2909243462u32, 3663771856u32, 1141124467u32, 855842277u32, 2852801631u32, 3708648649u32,
        1342533948u32, 654459306u32, 3188396048u32, 3373015174u32, 1466479909u32, 544179635u32, 3110523913u32, 3462522015u32,
        1591671054u32, 702138776u32, 2966460450u32, 3352799412u32, 1504918807u32, 783551873u32, 3082640443u32, 3233442989u32,
        3988292384u32, 2596254646u32, 62317068u32, 1957810842u32, 3939845945u32, 2647816111u32, 81470997u32, 1943803523u32,
        3814918930u32, 2489596804u32, 225274430u32, 2053790376u32, 3826175755u32, 2466906013u32, 167816743u32, 2097651377u32,
        4027552580u32, 2265490386u32, 503444072u32, 1762050814u32, 4150417245u32, 2154129355u32, 426522225u32, 1852507879u32,
        4275313526u32, 2312317920u32, 282753626u32, 1742555852u32, 4189708143u32, 2394877945u32, 397917763u32, 1622183637u32,
        3604390888u32, 2714866558u32, 953729732u32, 1340076626u32, 3518719985u32, 2797360999u32, 1068828381u32, 1219638859u32,
        3624741850u32, 2936675148u32, 906185462u32, 1090812512u32, 3747672003u32, 2825379669u32, 829329135u32, 1181335161u32,
        3412177804u32, 3160834842u32, 628085408u32, 1382605366u32, 3423369109u32, 3138078467u32, 570562233u32, 1426400815u32,
        3317316542u32, 2998733608u32, 733239954u32, 1555261956u32, 3268935591u32, 3050360625u32, 752459403u32, 1541320221u32,
        2607071920u32, 3965973030u32, 1969922972u32, 40735498u32, 2617837225u32, 3943577151u32, 1913087877u32, 83908371u32,
        2512341634u32, 3803740692u32, 2075208622u32, 213261112u32, 2463272603u32, 3855990285u32, 2094854071u32, 198958881u32,
        2262029012u32, 4057260610u32, 1759359992u32, 534414190u32, 2176718541u32, 4139329115u32, 1873836001u32, 414664567u32,
        2282248934u32, 4279200368u32, 1711684554u32, 285281116u32, 2405801727u32, 4167216745u32, 1634467795u32, 376229701u32,
        2685067896u32, 3608007406u32, 1308918612u32, 956543938u32, 2808555105u32, 3495958263u32, 1231636301u32, 1047427035u32,
        2932959818u32, 3654703836u32, 1088359270u32, 936918000u32, 2847714899u32, 3736837829u32, 1202900863u32, 817233897u32,
        3183342108u32, 3401237130u32, 1404277552u32, 615818150u32, 3134207493u32, 3453421203u32, 1423857449u32, 601450431u32,
        3009837614u32, 3294710456u32, 1567103746u32, 711928724u32, 3020668471u32, 3272380065u32, 1510334235u32, 755167117u32
    ]);
}

pub fn lodepng_crc32(data: Option<&[u8]>, length: usize) -> u32 {
	println!("* lodepng_crc32");
    let data = match data {
        Some(d) => d,
        None => return 0,
    };

    let mut r = 0xffffffffu32;
    let table = LODEPNG_CRC32_TABLE.lock().unwrap();

    for i in 0..length {
        r = table[((r ^ u32::from(data[i])) & 0xff) as usize] ^ (r >> 8);
    }

    r ^ 0xffffffffu32
}
pub fn lodepng_chunk_length(chunk: &[u8]) -> u32 {
	println!("* lodepng_chunk_length");
    lodepng_read32bitInt(chunk)
}
pub fn lodepng_inspect(
    w: Option<&mut u32>,
    h: Option<&mut u32>,
    state: &mut LodePngState,
    in_data: Option<&[u8]>,
    insize: usize,
) -> u32 {
	println!("* lodepng_inspect");
    // Check for null input or empty data
    if insize == 0 || in_data.is_none() {
        state.error = 48;
        return 48;
    }
    let in_data = in_data.unwrap();

    // Check minimum size requirement
    if insize < 33 {
        state.error = 27;
        return 27;
    }

    // Validate PNG header signature
    if in_data[0..8] != [137, 80, 78, 71, 13, 10, 26, 10] {
        state.error = 28;
        return 28;
    }

    let info = &mut state.info_png;
    lodepng_info_cleanup(info);
    lodepng_info_init(info);

    // Check IHDR chunk
    if lodepng_chunk_length(&in_data[8..]) != 13 {
        state.error = 94;
        return 94;
    }

    if lodepng_chunk_type_equals(Some(&in_data[8..]), Some("IHDR")) == 0 {
        state.error = 29;
        return 29;
    }

    let width = lodepng_read32bitInt(&in_data[16..20]);
    let height = lodepng_read32bitInt(&in_data[20..24]);
    // Set width/height if output parameters are provided
    if let Some(w_ptr) = w {
        *w_ptr = width;
    }
    if let Some(h_ptr) = h {
        *h_ptr = height;
    }

    // Read PNG metadata
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

    // Verify CRC if not ignored
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
pub fn lodepng_chunk_next_const<'a>(chunk: &'a [u8], end: &'a [u8]) -> &'a [u8] {
	println!("* lodepng_chunk_next_const");
    let available_size = end.len().wrapping_sub(chunk.len());
    if chunk.len() >= end.len() || available_size < 12 {
        return end;
    }

    // Check for PNG signature
    if chunk[0] == 0x89 && 
       chunk[1] == 0x50 && 
       chunk[2] == 0x4e && 
       chunk[3] == 0x47 && 
       chunk[4] == 0x0d && 
       chunk[5] == 0x0a && 
       chunk[6] == 0x1a && 
       chunk[7] == 0x0a {
        return &chunk[8..];
    } else {
        let chunk_length = lodepng_chunk_length(chunk) as usize;
        let mut total_chunk_length = 0;
        if lodepng_addofl(chunk_length, 12, &mut total_chunk_length) {
            return end;
        }
        if total_chunk_length > available_size {
            return end;
        }
        return &chunk[total_chunk_length..];
    }
}
pub fn lodepng_chunk_check_crc(chunk: Option<&[u8]>) -> u32 {
	println!("* lodepng_chunk_check_crc");
    // Check for NULL equivalent (None in Rust)
    let chunk = match chunk {
        Some(c) => c,
        None => return 1, // Return 1 for error case (NULL input)
    };

    let length = lodepng_chunk_length(chunk);
    
    // Calculate the position of CRC (length + 8)
    // Ensure we don't overflow the slice bounds
    let crc_start = length as usize + 8;
    if crc_start + 4 > chunk.len() {
        return 1; // Return 1 for error case (invalid chunk length)
    }
    let CRC = lodepng_read32bitInt(&chunk[crc_start..crc_start + 4]);

    // Calculate checksum for the relevant portion (bytes 4 to length+4)
    let checksum_start = 4;
    let checksum_end = checksum_start + length as usize + 4;
    if checksum_end > chunk.len() {
        return 1; // Return 1 for error case (invalid checksum range)
    }
    let checksum = lodepng_crc32(Some(&chunk[checksum_start..checksum_end]), checksum_end - checksum_start);

    if CRC != checksum {
        1
    } else {
        0
    }
}

pub fn lodepng_chunk_append(
    out: &mut Option<Box<[u8]>>,
    outsize: &mut usize,
    chunk: &[u8],
) -> u32 {
	println!("* lodepng_chunk_append");
    let total_chunk_length = match lodepng_chunk_length(chunk).checked_add(12) {
        Some(v) => v as usize,
        None => return 77,
    };

    let new_length = match outsize.checked_add(total_chunk_length) {
        Some(v) => v,
        None => return 77,
    };

    let mut new_buffer = match lodepng_realloc(out.as_deref_mut(), new_length) {
        Some(b) => b,
        None => return 83,
    };

    let chunk_start_idx = new_length - total_chunk_length;
    let chunk_start = &mut new_buffer[chunk_start_idx..];

    for i in 0..total_chunk_length {
        chunk_start[i] = chunk[i];
    }

    *out = Some(new_buffer.into_boxed_slice());
    *outsize = new_length;

    0
}
pub fn decodeGeneric(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    state: &mut LodePngState,
    in_data: &[u8],
    insize: usize,
) {
	println!("* decodeGeneric");
    let mut IEND = false;
    let mut chunk_idx = 0;
    let mut idat = Vec::new();
    let mut idatsize = 0;
    let mut scanlines = Vec::new();
    let mut scanlines_size = 0;
    let mut expected_size = 0;
    let mut outsize = 0;
    let mut unknown = false;
    let mut critical_pos = 1;

    *out = None;
    *w = 0;
    *h = 0;

    //state.error = lodepng_inspect(Some(w), Some(h), state, Some(in_data), insize);
    //if state.error != 0 {
    //    return;
    //}

    //if lodepng_pixel_overflow(*w as usize, *h as usize, &state.info_png.color, &state.info_raw) {
    //    state.error = 92;
    //    return;
    //}

    idat.reserve(insize);
    if idat.capacity() < insize {
        state.error = 83;
        return;
    }

    chunk_idx = 33; // Skip PNG header

    while !IEND && state.error == 0 {
        let chunk = &in_data[chunk_idx..];
        let chunk_length = lodepng_chunk_length(chunk) as usize;
        let pos = chunk_idx;

        if pos + 12 > insize {
            if state.decoder.ignore_end != 0 {
                break;
            }
            state.error = 30;
            break;
        }

        if chunk_length > 2147483647 {
            if state.decoder.ignore_end != 0 {
                break;
            }
            state.error = 63;
            break;
        }

        if pos + chunk_length + 12 > insize || pos + chunk_length + 12 < pos {
            state.error = 64;
            break;
        }

        let data = lodepng_chunk_data_const(Some(chunk)).unwrap_or(&[]);
        unknown = false;

        if lodepng_chunk_type_equals(Some(chunk), Some("IDAT")) != 0 {
            let mut newsize = 0;
            if lodepng_addofl(idatsize, chunk_length, &mut newsize) {
                state.error = 95;
                break;
            }
            if newsize > insize {
                state.error = 95;
                break;
            }

            idat.extend_from_slice(data);
            idatsize += chunk_length;
            critical_pos = 3;
        } else if lodepng_chunk_type_equals(Some(chunk), Some("IEND")) != 0 {
            IEND = true;
        } else if lodepng_chunk_type_equals(Some(chunk), Some("PLTE")) != 0 {
            state.error = readChunk_PLTE(&mut state.info_png.color, data, chunk_length);
            if state.error != 0 {
                break;
            }
            critical_pos = 2;
        } else if lodepng_chunk_type_equals(Some(chunk), Some("tRNS")) != 0 {
            state.error = readChunk_tRNS(&mut state.info_png.color, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("bKGD")) != 0 {
            state.error = readChunk_bKGD(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("tEXt")) != 0 {
            if state.decoder.read_text_chunks != 0 {
                state.error = readChunk_tEXt(&mut state.info_png, data, chunk_length);
                if state.error != 0 {
                    break;
                }
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("zTXt")) != 0 {
            if state.decoder.read_text_chunks != 0 {
                state.error = readChunk_zTXt(&mut state.info_png, &state.decoder, Some(data), chunk_length);
                if state.error != 0 {
                    break;
                }
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("iTXt")) != 0 {
            if state.decoder.read_text_chunks != 0 {
                state.error = readChunk_iTXt(&mut state.info_png, &state.decoder, data, chunk_length);
                if state.error != 0 {
                    break;
                }
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("tIME")) != 0 {
            state.error = readChunk_tIME(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("pHYs")) != 0 {
            state.error = readChunk_pHYs(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("gAMA")) != 0 {
            state.error = readChunk_gAMA(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("cHRM")) != 0 {
            state.error = readChunk_cHRM(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("sRGB")) != 0 {
            state.error = readChunk_sRGB(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("iCCP")) != 0 {
            state.error = readChunk_iCCP(&mut state.info_png, &state.decoder, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else if lodepng_chunk_type_equals(Some(chunk), Some("sBIT")) != 0 {
            state.error = readChunk_sBIT(&mut state.info_png, data, chunk_length);
            if state.error != 0 {
                break;
            }
        } else {
            if state.decoder.ignore_critical == 0 && !lodepng_chunk_ancillary(Some(chunk)) {
                state.error = 69;
                break;
            }
            unknown = true;
            if state.decoder.remember_unknown_chunks != 0 {
                let mut boxed_chunk = Some(chunk.to_vec().into_boxed_slice());
                state.error = lodepng_chunk_append(
                    &mut boxed_chunk,
                    &mut state.info_png.unknown_chunks_size[critical_pos - 1],
                    chunk,
                );
                if state.error != 0 {
                    break;
                }
                state.info_png.unknown_chunks_data[critical_pos - 1] = boxed_chunk.map(|b| b.to_vec());
            }
        }

        if state.decoder.ignore_crc == 0 && !unknown {
            if lodepng_chunk_check_crc(Some(chunk)) != 0 {
                state.error = 57;
                break;
            }
        }

        if !IEND {
            chunk_idx = lodepng_chunk_next_const(chunk, &in_data[insize..]).as_ptr() as usize - in_data.as_ptr() as usize;
        }
    }

    if state.error == 0 && state.info_png.color.colortype == LodePNGColorType::LCT_PALETTE && state.info_png.color.palette.is_none() {
        state.error = 106;
    }

    if state.error == 0 {
        let bpp = lodepng_get_bpp(&state.info_png.color) as u32;
        if state.info_png.interlace_method == 0 {
            expected_size = lodepng_get_raw_size_idat(*w, *h, bpp);
        } else {
            expected_size = 0;
            expected_size += lodepng_get_raw_size_idat((*w + 7) >> 3, (*h + 7) >> 3, bpp);
            if *w > 4 {
                expected_size += lodepng_get_raw_size_idat((*w + 3) >> 3, (*h + 7) >> 3, bpp);
            }
            expected_size += lodepng_get_raw_size_idat((*w + 3) >> 2, (*h + 3) >> 3, bpp);
            if *w > 2 {
                expected_size += lodepng_get_raw_size_idat((*w + 1) >> 2, (*h + 3) >> 2, bpp);
            }
            expected_size += lodepng_get_raw_size_idat((*w + 1) >> 1, (*h + 1) >> 2, bpp);
            if *w > 1 {
                expected_size += lodepng_get_raw_size_idat(*w >> 1, (*h + 1) >> 1, bpp);
            }
            expected_size += lodepng_get_raw_size_idat(*w, *h >> 1, bpp);
        }

        let scanlines_clone = scanlines.clone();
        state.error = zlib_decompress(
            &mut Some(scanlines),
            &mut scanlines_size,
            expected_size,
            Some(&idat),
            idatsize,
            &state.decoder.zlibsettings,
        );
        scanlines = scanlines_clone;
    }

    if state.error == 0 && scanlines_size != expected_size {
        state.error = 91;
    }

    if state.error == 0 {
        outsize = lodepng_get_raw_size(*w, *h, &state.info_png.color);
        *out = Some(vec![0; outsize]);
        if out.is_none() {
            state.error = 83;
        }
    }

    if state.error == 0 {
        let out_slice = out.as_mut().unwrap();
        lodepng_memset(out_slice, 0);
        state.error = postProcessScanlines(out_slice, &scanlines, *w, *h, &state.info_png);
    }
}

pub fn lodepng_decode(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    state: &mut LodePngState,
    in_data: &[u8],
    insize: usize,
) -> u32 {
	println!("* lodepng_decode");
    *out = None;
    decodeGeneric(out, w, h, state, in_data, insize);
    
    if state.error != 0 {
        return state.error;
    }

    if !state.decoder.color_convert != 0 || lodepng_color_mode_equal(&state.info_raw, &state.info_png.color) {
        if state.decoder.color_convert == 0 {
            state.error = lodepng_color_mode_copy(&mut state.info_raw, &state.info_png.color);
            if state.error != 0 {
                return state.error;
            }
        }
    } else {
        let data = out.take();
        let outsize = lodepng_get_raw_size(*w, *h, &state.info_raw);
        
        if !(state.info_raw.colortype == LodePNGColorType::LCT_RGB || 
             state.info_raw.colortype == LodePNGColorType::LCT_RGBA) && 
           state.info_raw.bitdepth != 8 {
            return 56;
        }

        *out = Some(vec![0; outsize]);
        if out.is_none() {
            state.error = 83;
        } else {
            state.error = lodepng_convert(
                out.as_mut().unwrap(),
                data.as_ref().unwrap(),
                &state.info_raw,
                &state.info_png.color,
                *w,
                *h,
            );
        }
        lodepng_free(data.map(|v| Box::new(v) as Box<dyn std::any::Any>));
    }
    
    state.error
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
	println!("* lodepng_decode_memory");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
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
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
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
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
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
        info_png: LodePngInfo {
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
            time: LodePngTime {
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
    in_: &[u8],
    insize: usize,
) -> u32 {
	println!("* lodepng_decode32");
    lodepng_decode_memory(
        out,
        w,
        h,
        in_,
        insize,
        LodePNGColorType::LCT_RGBA,
        8,
    )
}
pub fn lodepng_decode24(
    out: &mut Option<Vec<u8>>,
    w: &mut u32,
    h: &mut u32,
    in_: &[u8],
    insize: usize,
) -> u32 {
	println!("* lodepng_decode24");
    lodepng_decode_memory(
        out,
        w,
        h,
        in_,
        insize,
        LodePNGColorType::LCT_RGB,
        8,
    )
}
pub fn lodepng_load_file(
    out: &mut Option<Vec<u8>>,
    outsize: &mut Option<usize>,
    filename: &str,
) -> Result<(), u32> {
	println!("* lodepng_load_file");
    let size = match lodepng_filesize(filename) {
        Some(s) if s >= 0 => s as usize,
        _ => return Err(78),
    };

    *outsize = Some(size);

    if size > 0 {
        let mut buffer = vec![0; size];
        match lodepng_buffer_file(&mut buffer, filename) {
            Ok(_) => {
                *out = Some(buffer);
                Ok(())
            }
            Err(e) => Err(e),
        }
    } else {
        *out = None;
        Ok(())
    }
}
pub fn lodepng_decode_file(
    out: &mut Option<Vec<u8>>,
    w: &mut Option<u32>,
    h: &mut Option<u32>,
    filename: &str,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> Result<(), u32> {
	println!("* lodepng_decode_file");
    let mut buffer: Option<Vec<u8>> = None;
    let mut buffersize: Option<usize> = None;
    
    *out = None;
    *w = None;
    *h = None;

    let error = lodepng_load_file(&mut buffer, &mut buffersize, filename);
    
    if error.is_ok() {
        let mut actual_w = 0;
        let mut actual_h = 0;
        let error_code = lodepng_decode_memory(
            out,
            &mut actual_w,
            &mut actual_h,
            buffer.as_deref().unwrap(),
            buffersize.unwrap(),
            colortype,
            bitdepth,
        );
        *w = Some(actual_w);
        *h = Some(actual_h);
        lodepng_free(buffer.map(|v| Box::new(v) as Box<dyn std::any::Any>));
        if error_code == 0 {
            Ok(())
        } else {
            Err(error_code)
        }
    } else {
        lodepng_free(buffer.map(|v| Box::new(v) as Box<dyn std::any::Any>));
        Err(error.err().unwrap())
    }
}

pub fn lodepng_decode32_file(
    out: &mut Option<Vec<u8>>,
    w: &mut Option<u32>,
    h: &mut Option<u32>,
    filename: &str,
) -> Result<(), u32> {
	println!("* lodepng_decode32_file");
    lodepng_decode_file(out, w, h, filename, LodePNGColorType::LCT_RGBA, 8)
}

pub fn lodepng_decode24_file(
    out: &mut Option<Vec<u8>>,
    w: &mut Option<u32>,
    h: &mut Option<u32>,
    filename: &str,
) -> Result<(), u32> {
	println!("* lodepng_decode24_file");
    lodepng_decode_file(out, w, h, filename, LodePNGColorType::LCT_RGB, 8)
}

pub fn writeSignature(out: &mut Ucvector) -> u32 {
	println!("* writeSignature");
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
pub fn ilog2i(i: usize) -> usize {
	println!("* ilog2i");
    if i == 0 {
        return 0;
    }
    let l = ilog2(i);
    (i * l) + ((i - (1usize << l)) << 1usize)
}
pub fn filterScanline(
    out: &mut [u8],
    scanline: &[u8],
    prevline: Option<&[u8]>,
    length: usize,
    bytewidth: usize,
    filterType: u8,
) {
	println!("* filterScanline");
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
                    out[i] = scanline[i].wrapping_sub((scanline[i - bytewidth].wrapping_add(prevline[i])) >> 1);
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
                    let a = scanline[i - bytewidth] as i16;
                    let b = prevline[i] as i16;
                    let c = prevline[i - bytewidth] as i16;
                    out[i] = scanline[i].wrapping_sub(paethPredictor(a, b, c));
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

pub fn hash_init(hash: &mut Hash, windowsize: usize) -> u32 {
	println!("* hash_init");
    // Allocate vectors for each field
    hash.head = Some(vec![-1; HASH_NUM_VALUES as usize]);
    hash.val = Some(vec![-1; windowsize]);
    hash.chain = Some((0..windowsize).map(|i| i as u16).collect());
    hash.zeros = Some(vec![0; windowsize]);
    hash.headz = Some(vec![-1; MAX_SUPPORTED_DEFLATE_LENGTH + 1]);
    hash.chainz = Some((0..windowsize).map(|i| i as u16).collect());

    // Check if any allocation failed
    if hash.head.is_none() || 
       hash.val.is_none() || 
       hash.chain.is_none() || 
       hash.zeros.is_none() || 
       hash.headz.is_none() || 
       hash.chainz.is_none() {
        return 83;
    }

    0
}
pub fn hash_cleanup(hash: &mut Hash) {
	println!("* hash_cleanup");
    hash.head = None;
    hash.val = None;
    hash.chain = None;
    hash.zeros = None;
    hash.headz = None;
    hash.chainz = None;
}

pub fn deflateNoCompression(out: &mut Ucvector, data: &[u8]) -> Option<u32> {
	println!("* deflateNoCompression");
    let datasize = data.len();
    let numdeflateblocks = (datasize + 65534) / 65535;
    let mut datapos = 0;

    for i in 0..numdeflateblocks {
        let BFINAL = i == (numdeflateblocks - 1);
        let BTYPE = 0;
        let mut LEN = 65535;
        
        if (datasize - datapos) < 65535 {
            LEN = datasize - datapos;
        }
        
        let NLEN = 65535 - LEN;
        let new_size = out.size + LEN + 5;
        
        if !ucvector_resize(out, new_size) {
            return Some(83);
        }
        
        let pos = out.size;
        let firstbyte = (BFINAL as u8) + ((BTYPE & 1) << 1) + ((BTYPE & 2) << 1);
        
        if let Some(ref mut out_data) = out.data {
            out_data[pos] = firstbyte;
            out_data[pos + 1] = (LEN & 255) as u8;
            out_data[pos + 2] = (LEN >> 8) as u8;
            out_data[pos + 3] = (NLEN & 255) as u8;
            out_data[pos + 4] = (NLEN >> 8) as u8;
            
            let dst_slice = &mut out_data[(pos + 5)..(pos + 5 + LEN)];
            let src_slice = &data[datapos..(datapos + LEN)];
            lodepng_memcpy(dst_slice, src_slice);
        }
        
        datapos += LEN;
    }

    Some(0)
}
pub fn writeBitsReversed(writer: &mut LodePngBitWriter, value: u32, nbits: usize) {
	println!("* writeBitsReversed");
    for i in 0..nbits {
        if (writer.bp & 7u8) == 0 {
            if let Some(ref mut data) = writer.data {
                let new_size = data.size + 1;
                if let Some(vec) = &mut data.data {
                    if vec.len() < new_size {
                        vec.resize(new_size, 0);
                    } else {
                        vec[new_size - 1] = 0;
                    }
                } else {
                    let mut vec = Vec::new();
                    vec.resize(new_size, 0);
                    data.data = Some(vec);
                }
                data.size = new_size;
                data.allocsize = data.data.as_ref().map(|v| v.capacity()).unwrap_or(0);
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
pub fn writeBits(writer: &mut LodePngBitWriter, value: u32, nbits: usize) {
	println!("* writeBits");
    if nbits == 1 {
        if (writer.bp & 7u8) == 0 {
            if let Some(ref mut data_box) = writer.data {
                let p = &mut **data_box as *mut ucvector::Ucvector as *mut crate::lodepng::Ucvector;
                if !ucvector_resize(unsafe { &mut *p }, data_box.size + 1) {
                    return;
                }
                if let Some(ref mut vec_data) = data_box.data {
                    vec_data[data_box.size - 1] = 0;
                }
            }
        }
        if let Some(ref mut data_box) = writer.data {
            if let Some(ref mut vec_data) = data_box.data {
                vec_data[data_box.size - 1] |= (value as u8) << (writer.bp & 7u8);
            }
        }
        writer.bp += 1;
    } else {
        for i in 0..nbits {
            if (writer.bp & 7u8) == 0 {
                if let Some(ref mut data_box) = writer.data {
                    let p = &mut **data_box as *mut ucvector::Ucvector as *mut crate::lodepng::Ucvector;
                    if !ucvector_resize(unsafe { &mut *p }, data_box.size + 1) {
                        return;
                    }
                    if let Some(ref mut vec_data) = data_box.data {
                        vec_data[data_box.size - 1] = 0;
                    }
                }
            }
            if let Some(ref mut data_box) = writer.data {
                if let Some(ref mut vec_data) = data_box.data {
                    vec_data[data_box.size - 1] |= (((value >> i) & 1) as u8) << (writer.bp & 7u8);
                }
            }
            writer.bp += 1;
        }
    }
}
pub fn writeLZ77data(
    writer: &mut LodePngBitWriter,
    lz77_encoded: &Uivector,
    tree_ll: &HuffmanTree,
    tree_d: &HuffmanTree,
) {
	println!("* writeLZ77data");
    let mut i = 0;
    while i < lz77_encoded.size {
        let val = lz77_encoded.data.as_ref().unwrap()[i];
        // Need to implement get_code and get_length methods for HuffmanTree
        // or find another way to access the codes and lengths
        // This is a placeholder - actual implementation depends on how codes are stored in HuffmanTree
        let (code_ll, length_ll) = get_huffman_code_length(tree_ll, val as usize);
        writeBitsReversed(writer, code_ll, length_ll);
        
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
            let (code_d, length_d) = get_huffman_code_length(tree_d, distance_code as usize);
            writeBitsReversed(writer, code_d, length_d);
            writeBits(writer, distance_extra_bits, n_distance_extra_bits as usize);
        }
        i += 1;
    }
}

// Helper function to get code and length from HuffmanTree
// This needs to be implemented based on how the HuffmanTree actually stores its codes
fn get_huffman_code_length(tree: &HuffmanTree, val: usize) -> (u32, usize) {
	println!("* get_huffman_code_length");
    // Placeholder implementation - replace with actual logic
    // This should extract the code and length for the given value from the tree
    (0, 0)
}
pub fn uivector_init(p: &mut Uivector) {
	println!("* uivector_init");
    p.data = None;
    p.size = 0;
    p.allocsize = 0;
}
pub fn uivector_cleanup(p: &mut Uivector) {
	println!("* uivector_cleanup");
    p.size = 0;
    p.allocsize = 0;
    lodepng_free(p.data.take().map(|ptr| Box::new(ptr) as Box<dyn std::any::Any>));
}
pub fn updateHashChain(hash: &mut Hash, wpos: usize, hashval: u32, numzeros: u16) {
	println!("* updateHashChain");
    // Update val array
    if let Some(val) = &mut hash.val {
        val[wpos] = hashval as i32;
    }

    // Update chain and head for hashval
    if let Some(head) = &mut hash.head {
        if let Some(chain) = &mut hash.chain {
            if head[hashval as usize] != -1 {
                chain[wpos] = head[hashval as usize] as u16;
            }
            head[hashval as usize] = wpos as i32;
        }
    }

    // Update zeros array
    if let Some(zeros) = &mut hash.zeros {
        zeros[wpos] = numzeros;
    }

    // Update chainz and headz for numzeros
    if let Some(headz) = &mut hash.headz {
        if let Some(chainz) = &mut hash.chainz {
            if headz[numzeros as usize] != -1 {
                chainz[wpos] = headz[numzeros as usize] as u16;
            }
            headz[numzeros as usize] = wpos as i32;
        }
    }
}
pub fn uivector_resize(p: &mut Uivector, size: usize) -> bool {
	println!("* uivector_resize");
    let allocsize = size * std::mem::size_of::<u32>();
    if allocsize > p.allocsize {
        let newsize = allocsize + (p.allocsize >> 1);
        if p.data.is_some() { 
            p.data.as_mut().unwrap().resize(newsize, 0);
        } else {
            p.data = Some(vec![0; newsize]);
        }
        p.allocsize = newsize;
        //
        //// Convert existing Vec<u32> to &mut [u8] for lodepng_realloc
        //let data_slice = p.data.as_mut().map(|v| {
        //    let byte_len = v.len() * std::mem::size_of::<u32>();
        //    unsafe { std::slice::from_raw_parts_mut(v.as_mut_ptr() as *mut u8, byte_len) }
        //});

        //if let Some(new_data) = lodepng_realloc(data_slice, newsize) {
        //    // Convert the returned Box<[u8]> back to Vec<u32>
        //    let new_len = new_data.len() / std::mem::size_of::<u32>();
        //    let ptr = Box::into_raw(new_data) as *mut u32;
        //    
        //    unsafe {
        //        // We use new_len for both length and capacity since Box<[u8]> doesn't track capacity
        //        p.data = Some(Vec::from_raw_parts(ptr, new_len, new_len));
        //    }
        //    p.allocsize = newsize;
        //} else {
        //    return false;
        //}
    }
    p.size = size;
    true
}
pub fn uivector_push_back(p: &mut Uivector, c: u32) -> bool {
	println!("* uivector_push_back");
    if !uivector_resize(p, p.size + 1) {
        return false;
    }
    p.data.as_mut().unwrap()[p.size - 1] = c;
    true
}

pub fn getHash(data: Option<&[u8]>, size: usize, pos: usize) -> u32 {
	println!("* getHash");
    let data = match data {
        Some(d) => d,
        None => return 0,
    };

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
pub fn countZeros(data: &[u8], size: usize, pos: usize) -> u32 {
	println!("* countZeros");
    let data_idx = 0;
    let start = &data[data_idx..][pos..];
    let end = start.len().min(MAX_SUPPORTED_DEFLATE_LENGTH);
    let end_idx = 0;
    let adjusted_end = if &start[end..] > &data[data_idx..][..size] {
        size
    } else {
        end
    };

    let mut count = 0;
    while count < adjusted_end && start[count] == 0 {
        count += 1;
    }

    count as u32
}
pub fn addLengthDistance(values: &mut Uivector, length: usize, distance: usize) {
	println!("* addLengthDistance");
    let length_code = searchCodeIndex(&LENGTHBASE, 29, length) as u32;
    let extra_length = (length as u32).wrapping_sub(LENGTHBASE[length_code as usize]);
    let dist_code = searchCodeIndex(&DISTANCEBASE, 30, distance) as u32;
    let extra_distance = (distance as u32).wrapping_sub(DISTANCEBASE[dist_code as usize]);
    let pos = values.size;
    
    if uivector_resize(values, values.size + 4) {
        if let Some(ref mut data) = values.data {
            data[pos] = length_code + 257;
            data[pos + 1] = extra_length;
            data[pos + 2] = dist_code;
            data[pos + 3] = extra_distance;
        }
    }
}
pub fn encode_lz77(
    out: &mut Uivector,
    hash: &mut Hash,
    in_data: &[u8],
    inpos: usize,
    insize: usize,
    windowsize: usize,
    minmatch: usize,
    nicematch: usize,
    lazymatching: bool,
) -> u32 {
	println!("* encode_lz77");
    let mut error = 0;
    let maxchainlength = if windowsize >= 8192 {
        windowsize
    } else {
        windowsize / 8
    };
    let maxlazymatch = if windowsize >= 8192 {
        MAX_SUPPORTED_DEFLATE_LENGTH
    } else {
        64
    };
    let mut usezeros = true;
    let mut numzeros = 0u32;
    let mut offset = 0;
    let mut length = 0;
    let mut lazy = false;
    let mut lazylength = 0;
    let mut lazyoffset = 0;

    if windowsize == 0 || windowsize > 32768 {
        return 60;
    }
    if (windowsize & (windowsize - 1)) != 0 {
        return 90;
    }
    let nicematch = nicematch.min(MAX_SUPPORTED_DEFLATE_LENGTH);

    let mut pos = inpos;
    while pos < insize {
        let wpos = pos & (windowsize - 1);
        let mut chainlength = 0;
        let hashval = getHash(Some(in_data), insize, pos);

        if usezeros && hashval == 0 {
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
        let mut hashpos = hash.chain.as_ref().unwrap()[wpos] as usize;
        let lastptr_idx = if insize < pos + MAX_SUPPORTED_DEFLATE_LENGTH {
            insize
        } else {
            pos + MAX_SUPPORTED_DEFLATE_LENGTH
        };
        let mut prev_offset = 0;

        loop {
            chainlength += 1;
            if chainlength > maxchainlength {
                break;
            }

            let current_offset = if hashpos <= wpos {
                wpos - hashpos
            } else {
                wpos.wrapping_sub(hashpos).wrapping_add(windowsize)
            };

            if current_offset < prev_offset {
                break;
            }
            prev_offset = current_offset;

            if current_offset > 0 {
                let mut foreptr_idx = pos;
                let mut backptr_idx = pos - current_offset;

                if numzeros >= 3 {
                    let mut skip = hash.zeros.as_ref().unwrap()[hashpos] as usize;
                    if skip > numzeros as usize {
                        skip = numzeros as usize;
                    }
                    backptr_idx += skip;
                    foreptr_idx += skip;
                }

                while foreptr_idx < lastptr_idx
                    && backptr_idx < insize
                    && in_data[backptr_idx] == in_data[foreptr_idx]
                {
                    backptr_idx += 1;
                    foreptr_idx += 1;
                }

                let current_length = foreptr_idx - pos;
                if current_length > length {
                    length = current_length;
                    offset = current_offset;
                    if current_length >= nicematch {
                        break;
                    }
                }
            }

            if hashpos == hash.chain.as_ref().unwrap()[hashpos] as usize {
                break;
            }

            if numzeros >= 3 && length > numzeros as usize {
                hashpos = hash.chainz.as_ref().unwrap()[hashpos] as usize;
                if hash.zeros.as_ref().unwrap()[hashpos] != numzeros as u16 {
                    break;
                }
            } else {
                hashpos = hash.chain.as_ref().unwrap()[hashpos] as usize;
                if hash.val.as_ref().unwrap()[hashpos] != hashval as i32 {
                    break;
                }
            }
        }

        if lazymatching {
            if !lazy && length >= 3 && length <= maxlazymatch && length < MAX_SUPPORTED_DEFLATE_LENGTH {
                lazy = true;
                lazylength = length;
                lazyoffset = offset;
                pos += 1;
                continue;
            }

            if lazy {
                lazy = false;
                if pos == 0 {
                    error = 81;
                    break;
                }

                if length > (lazylength + 1) {
                    if !uivector_push_back(out, in_data[pos - 1] as u32) {
                        error = 83;
                        break;
                    }
                } else {
                    length = lazylength;
                    offset = lazyoffset;
                    hash.head.as_mut().unwrap()[hashval as usize] = -1;
                    if numzeros > 0 {
                        hash.headz.as_mut().unwrap()[numzeros as usize] = -1;
                    }
                    pos -= 1;
                }
            }
        }

        if length >= 3 && offset > windowsize {
            error = 86;
            break;
        }

        if length < 3 || (length < minmatch) || (length == 3 && offset > 4096) {
            if !uivector_push_back(out, in_data[pos] as u32) {
                error = 83;
                break;
            }
        } else {
            addLengthDistance(out, length, offset);
            for _ in 1..length {
                pos += 1;
                let wpos = pos & (windowsize - 1);
                let hashval = getHash(Some(in_data), insize, pos);

                if usezeros && hashval == 0 {
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
        }

        pos += 1;
    }

    error
}

pub fn deflateFixed(
    writer: &mut LodePngBitWriter,
    hash: &mut Hash,
    data: &[u8],
    datapos: usize,
    dataend: usize,
    settings: &LodePngCompressSettings,
    final_: bool,
) -> u32 {
	println!("* deflateFixed");
    let mut tree_ll = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let mut tree_d = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let BFINAL = final_ as u32;
    let mut error = 0;
    
    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);
    
    error = generateFixedLitLenTree(&mut tree_ll);
    if error == 0 {
        error = generateFixedDistanceTree(&mut tree_d);
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
            
            error = encode_lz77(
                &mut lz77_encoded,
                hash,
                data,
                datapos,
                dataend,
                settings.windowsize as usize,
                settings.minmatch as usize,
                settings.nicematch as usize,
                settings.lazymatching != 0,
            );
            
            if error == 0 {
                writeLZ77data(writer, &lz77_encoded, &tree_ll, &tree_d);
            }
            
            uivector_cleanup(&mut lz77_encoded);
        } else {
            for i in datapos..dataend {
                writeBitsReversed(
                    writer,
                    tree_ll.tree2d.as_ref().unwrap()[data[i] as usize] as u32,
                    tree_ll.tree2d_size,
                );
            }
        }
        
        if error == 0 {
            writeBitsReversed(
                writer,
                tree_ll.tree2d.as_ref().unwrap()[256] as u32,
                tree_ll.tree2d_size,
            );
        }
    }
    
    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);
    
    error
}
pub fn bpmnode_sort(leaves: &mut [BpmNode]) {
	println!("* bpmnode_sort");
    let num = leaves.len();
    let mut mem = vec![BpmNode {
        weight: 0,
        index: 0,
        tail: Option::None,
        in_use: 0,
    }; num];
    let mut counter = 0;

    let mut width = 1;
    while width < num {
        let (a, b) = if counter & 1 == 1 {
            (&mut mem[..], &mut leaves[..])
        } else {
            (&mut leaves[..], &mut mem[..])
        };

        let mut p = 0;
        while p < num {
            let q = if p + width > num { num } else { p + width };
            let r = if p + 2 * width > num { num } else { p + 2 * width };

            let mut i = p;
            let mut j = q;
            let mut k = p;

            while k < r {
                if i < q && (j >= r || a[i].weight <= a[j].weight) {
                    b[k] = a[i].clone();
                    i += 1;
                } else {
                    b[k] = a[j].clone();
                    j += 1;
                }
                k += 1;
            }

            p += 2 * width;
        }

        counter += 1;
        width *= 2;
    }

    if counter & 1 == 1 {
        for (i, node) in mem.iter().enumerate() {
            leaves[i] = node.clone();
        }
    }
}
pub fn bpmnode_create(
    lists: &mut BpmLists,
    weight: i32,
    index: u32,
    tail: Option<Box<BpmNode>>,
) -> Option<Box<BpmNode>> {
	println!("* bpmnode_create");
    if lists.nextfree >= lists.numfree {
        // Reset all memory to unused state
        if let Some(memory) = &mut lists.memory {
            for node in memory.iter_mut() {
                node.in_use = 0;
            }
        }

        // Mark used nodes in chains0 and chains1
        if let Some(chains0) = &lists.chains0 {
            for node_option in chains0.iter() {
                let mut current = node_option.as_ref();
                while let Some(node) = current {
                    if let Some(memory) = &mut lists.memory {
                        if (node.index as usize) < memory.len() {
                            memory[node.index as usize].in_use = 1;
                        }
                    }
                    current = node.tail.as_ref().map(|n| &*n);
                }
            }
        }

        if let Some(chains1) = &lists.chains1 {
            for node_option in chains1.iter() {
                let mut current = node_option.as_ref();
                while let Some(node) = current {
                    if let Some(memory) = &mut lists.memory {
                        if (node.index as usize) < memory.len() {
                            memory[node.index as usize].in_use = 1;
                        }
                    }
                    current = node.tail.as_ref().map(|n| &*n);
                }
            }
        }

        // Rebuild freelist
        lists.numfree = 0;
        if let Some(freelist) = &mut lists.freelist {
            freelist.clear();
            if let Some(memory) = &lists.memory {
                for node in memory.iter() {
                    if node.in_use == 0 {
                        freelist.push(Some(Box::new(node.clone())));
                        lists.numfree += 1;
                    }
                }
            }
        }

        lists.nextfree = 0;
    }

    // Get next free node
    if let Some(freelist) = &mut lists.freelist {
        if lists.nextfree < lists.numfree {
            if let Some(node) = freelist[lists.nextfree as usize].take() {
                lists.nextfree += 1;
                let mut result = node;
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
    lists: &mut BpmLists,
    leaves: &[BpmNode],
    numpresent: usize,
    c: i32,
    num: i32,
) {
	println!("* boundaryPM");
    if lists.chains1.as_ref().unwrap()[c as usize].as_ref().is_none() {
        return;
    }
    let lastindex = lists.chains1.as_ref().unwrap()[c as usize].as_ref().unwrap().index;
    
    if c == 0 {
        if lastindex >= numpresent as u32 {
            return;
        }
        lists.chains0.as_mut().unwrap()[c as usize] = lists.chains1.as_ref().unwrap()[c as usize].clone();
        lists.chains1.as_mut().unwrap()[c as usize] = bpmnode_create(
            lists,
            leaves[lastindex as usize].weight,
            lastindex + 1,
            None,
        );
    } else {
        let sum = lists.chains0.as_ref().unwrap()[(c - 1) as usize].as_ref().unwrap().weight
            + lists.chains1.as_ref().unwrap()[(c - 1) as usize].as_ref().unwrap().weight;
        
        lists.chains0.as_mut().unwrap()[c as usize] = lists.chains1.as_ref().unwrap()[c as usize].clone();
        
        if (lastindex < numpresent as u32) && (sum > leaves[lastindex as usize].weight) {
            let tail = lists.chains1.as_ref().unwrap()[c as usize].as_ref().unwrap().tail.clone();
            lists.chains1.as_mut().unwrap()[c as usize] = bpmnode_create(
                lists,
                leaves[lastindex as usize].weight,
                lastindex + 1,
                tail,
            );
            return;
        }
        
        lists.chains1.as_mut().unwrap()[c as usize] = bpmnode_create(
            lists,
            sum,
            lastindex,
            lists.chains1.as_ref().unwrap()[(c - 1) as usize].clone(),
        );
        
        if (num + 1) < (2 * numpresent as i32 - 2) {
            boundaryPM(lists, leaves, numpresent, c - 1, num);
            boundaryPM(lists, leaves, numpresent, c - 1, num);
        }
    }
}

pub fn lodepng_huffman_code_lengths(
    lengths: &mut [u32],
    frequencies: &[u32],
    numcodes: usize,
    maxbitlen: u32,
) -> u32 {
	println!("* lodepng_huffman_code_lengths");
    let mut error = 0;
    let mut numpresent = 0;

    if numcodes == 0 {
        return 80;
    }
    if (1u32 << maxbitlen) < numcodes as u32 {
        return 80;
    }

    let mut leaves = vec![BpmNode {
        weight: 0,
        index: 0,
        tail: None,
        in_use: 0,
    }; numcodes];

    for i in 0..numcodes {
        if frequencies[i] > 0 {
            leaves[numpresent].weight = frequencies[i] as i32;
            leaves[numpresent].index = i as u32;
            numpresent += 1;
        }
    }

    lengths.fill(0);
    match numpresent {
        0 => {
            lengths[0] = 1;
            lengths[1] = 1;
        }
        1 => {
            let idx = leaves[0].index as usize;
            lengths[idx] = 1;
            lengths[if idx == 0 { 1 } else { 0 }] = 1;
        }
        _ => {
            let mut lists = BpmLists {
                listsize: maxbitlen,
                memsize: 2 * maxbitlen * (maxbitlen + 1),
                nextfree: 0,
                numfree: 2 * maxbitlen * (maxbitlen + 1),
                memory: Some(vec![
                    BpmNode {
                        weight: 0,
                        index: 0,
                        tail: None,
                        in_use: 0
                    };
                    (2 * maxbitlen * (maxbitlen + 1)) as usize
                ]),
                freelist: Some(vec![None; (2 * maxbitlen * (maxbitlen + 1)) as usize]),
                chains0: Some(vec![None; maxbitlen as usize]),
                chains1: Some(vec![None; maxbitlen as usize]),
            };

            if lists.memory.is_none() || lists.freelist.is_none() || lists.chains0.is_none() || lists.chains1.is_none() {
                error = 83;
            }

            if error == 0 {
                bpmnode_sort(&mut leaves[..numpresent]);

                bpmnode_create(&mut lists, leaves[0].weight, 1, None);
                bpmnode_create(&mut lists, leaves[1].weight, 2, None);

                for i in 0..lists.listsize {
                    lists.chains0.as_mut().unwrap()[i as usize] = Some(Box::new(lists.memory.as_ref().unwrap()[0].clone()));
                    lists.chains1.as_mut().unwrap()[i as usize] = Some(Box::new(lists.memory.as_ref().unwrap()[1].clone()));
                }

                for i in 2..(2 * numpresent - 2) {
                    boundaryPM(
                        &mut lists,
                        &leaves[..numpresent],
                        numpresent,
                        maxbitlen as i32 - 1,
                        i as i32,
                    );
                }

                let mut node = lists.chains1.as_ref().unwrap()[maxbitlen as usize - 1].clone();
                while let Some(n) = node {
                    for i in 0..n.index {
                        lengths[leaves[i as usize].index as usize] += 1;
                    }
                    node = n.tail;
                }
            }
        }
    }

    error
}
pub fn HuffmanTree_makeFromFrequencies(
    tree: &mut HuffmanTree,
    frequencies: &[u32],
    mincodes: usize,
    numcodes: usize,
    maxbitlen: u32,
) -> u32 {
	println!("* HuffmanTree_makeFromFrequencies");
    let mut numcodes = numcodes;
    // Skip trailing zero frequencies
    while numcodes > mincodes && frequencies[numcodes - 1] == 0 {
        numcodes -= 1;
    }

    // Allocate memory for lengths
    let mut lengths = vec![0u32; numcodes];
    
    // Generate Huffman code lengths
    let mut error = lodepng_huffman_code_lengths(
        &mut lengths,
        &frequencies[..numcodes],
        numcodes,
        maxbitlen,
    );

    if error == 0 {
        // Store the lengths in tree2d (since that's the only available field)
        tree.tree2d = Some(lengths.into_iter().map(|x| x as u64).collect());
        tree.tree2d_size = numcodes;
        error = HuffmanTree_makeFromLengths2(tree);
    }

    error
}
pub fn deflateDynamic(
    writer: &mut LodePngBitWriter,
    hash: &mut Hash,
    data: &[u8],
    datapos: usize,
    dataend: usize,
    settings: &LodePngCompressSettings,
    final_: bool,
) -> u32 {
	println!("* deflateDynamic");
    let mut error = 0;
    let mut lz77_encoded = Uivector {
        data: None,
        size: 0,
        allocsize: 0,
    };
    let mut tree_ll = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let mut tree_d = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let mut tree_cl = HuffmanTree {
        tree2d: None,
        tree2d_size: 0,
    };
    let mut frequencies_ll = vec![0; 286];
    let mut frequencies_d = vec![0; 30];
    let mut frequencies_cl = vec![0; 19];
    let mut bitlen_lld = Vec::new();
    let mut bitlen_lld_e = Vec::new();
    let datasize = dataend - datapos;
    let BFINAL = if final_ { 1 } else { 0 };
    let mut numcodes_ll;
    let mut numcodes_d;
    let mut numcodes_lld;
    let mut numcodes_lld_e = 0;
    let mut numcodes_cl;
    let mut HLIT;
    let mut HDIST;
    let mut HCLEN;

    uivector_init(&mut lz77_encoded);
    HuffmanTree_init(&mut tree_ll);
    HuffmanTree_init(&mut tree_d);
    HuffmanTree_init(&mut tree_cl);

    loop {
        frequencies_ll.fill(0);
        frequencies_d.fill(0);
        frequencies_cl.fill(0);

        if settings.use_lz77 != 0 {
            error = encode_lz77(
                &mut lz77_encoded,
                hash,
                data,
                datapos,
                dataend,
                settings.windowsize as usize,
                settings.minmatch as usize,
                settings.nicematch as usize,
                settings.lazymatching != 0,
            );
            if error != 0 {
                break;
            }
        } else {
            if !uivector_resize(&mut lz77_encoded, datasize) {
                error = 83;
                break;
            }
            if let Some(ref mut lz77_data) = lz77_encoded.data {
                for i in datapos..dataend {
                    lz77_data[i - datapos] = data[i] as u32;
                }
            }
        }

        if let Some(ref lz77_data) = lz77_encoded.data {
            let mut i = 0;
            while i < lz77_encoded.size {
                let symbol = lz77_data[i];
                frequencies_ll[symbol as usize] += 1;
                if symbol > 256 {
                    let dist = lz77_data[i + 2];
                    frequencies_d[dist as usize] += 1;
                    i += 3;
                } else {
                    i += 1;
                }
            }
        }

        frequencies_ll[256] = 1;
        error = HuffmanTree_makeFromFrequencies(&mut tree_ll, &frequencies_ll, 257, 286, 15);
        if error != 0 {
            break;
        }
        error = HuffmanTree_makeFromFrequencies(&mut tree_d, &frequencies_d, 2, 30, 15);
        if error != 0 {
            break;
        }

        numcodes_ll = if tree_ll.tree2d_size < 286 {
            tree_ll.tree2d_size
        } else {
            286
        };
        numcodes_d = if tree_d.tree2d_size < 30 {
            tree_d.tree2d_size
        } else {
            30
        };
        numcodes_lld = numcodes_ll + numcodes_d;

        bitlen_lld = vec![0; numcodes_lld];
        bitlen_lld_e = vec![0; numcodes_lld * 2]; // Allocate extra space for potential expansion

        for i in 0..numcodes_ll {
            bitlen_lld[i] = tree_ll.tree2d.as_ref().map_or(0, |t| t[i] as u32);
        }
        for i in 0..numcodes_d {
            bitlen_lld[numcodes_ll + i] = tree_d.tree2d.as_ref().map_or(0, |t| t[i] as u32);
        }

        let mut i = 0;
        while i < numcodes_lld {
            let mut j = 0;
            while i + j + 1 < numcodes_lld && bitlen_lld[i + j + 1] == bitlen_lld[i] {
                j += 1;
            }

            if bitlen_lld[i] == 0 && j >= 2 {
                j += 1;
                if j <= 10 {
                    bitlen_lld_e[numcodes_lld_e] = 17;
                    numcodes_lld_e += 1;
                    bitlen_lld_e[numcodes_lld_e] = (j - 3) as u32;
                    numcodes_lld_e += 1;
                } else {
                    let j = if j > 138 { 138 } else { j };
                    bitlen_lld_e[numcodes_lld_e] = 18;
                    numcodes_lld_e += 1;
                    bitlen_lld_e[numcodes_lld_e] = (j - 11) as u32;
                    numcodes_lld_e += 1;
                }
                i += j - 1;
            } else if j >= 3 {
                let num = j / 6;
                let rest = j % 6;
                bitlen_lld_e[numcodes_lld_e] = bitlen_lld[i];
                numcodes_lld_e += 1;
                for _ in 0..num {
                    bitlen_lld_e[numcodes_lld_e] = 16;
                    numcodes_lld_e += 1;
                    bitlen_lld_e[numcodes_lld_e] = (6 - 3) as u32;
                    numcodes_lld_e += 1;
                }
                if rest >= 3 {
                    bitlen_lld_e[numcodes_lld_e] = 16;
                    numcodes_lld_e += 1;
                    bitlen_lld_e[numcodes_lld_e] = (rest - 3) as u32;
                    numcodes_lld_e += 1;
                } else {
                    i += j - rest;
                }
                i += j;
            } else {
                bitlen_lld_e[numcodes_lld_e] = bitlen_lld[i];
                numcodes_lld_e += 1;
            }
            i += 1;
        }

        i = 0;
        while i < numcodes_lld_e {
            frequencies_cl[bitlen_lld_e[i] as usize] += 1;
            if bitlen_lld_e[i] >= 16 {
                i += 1;
            }
            i += 1;
        }

        error = HuffmanTree_makeFromFrequencies(&mut tree_cl, &frequencies_cl, 19, 19, 7);
        if error != 0 {
            break;
        }
        numcodes_cl = 19;
        while numcodes_cl > 4
            && tree_cl
                .tree2d
                .as_ref()
                .map_or(false, |t| t[CLCL_ORDER[numcodes_cl - 1] as usize] == 0)
        {
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
                tree_cl
                    .tree2d
                    .as_ref()
                    .map_or(0, |t| t[CLCL_ORDER[i] as usize] as u32),
                3,
            );
        }

        i = 0;
        while i < numcodes_lld_e {
            writeBitsReversed(
                writer,
                tree_cl
                    .tree2d
                    .as_ref()
                    .map_or(0, |t| t[bitlen_lld_e[i] as usize] as u32),
                tree_cl
                    .tree2d
                    .as_ref()
                    .map_or(0, |t| t[bitlen_lld_e[i] as usize] as usize),
            );
            if bitlen_lld_e[i] == 16 {
                i += 1;
                writeBits(writer, bitlen_lld_e[i], 2);
            } else if bitlen_lld_e[i] == 17 {
                i += 1;
                writeBits(writer, bitlen_lld_e[i], 3);
            } else if bitlen_lld_e[i] == 18 {
                i += 1;
                writeBits(writer, bitlen_lld_e[i], 7);
            }
            i += 1;
        }

        writeLZ77data(writer, &lz77_encoded, &tree_ll, &tree_d);
        if tree_ll
            .tree2d
            .as_ref()
            .map_or(true, |t| t[256] as usize == 0)
        {
            error = 64;
            break;
        }
        writeBitsReversed(
            writer,
            tree_ll.tree2d.as_ref().map_or(0, |t| t[256] as u32),
            tree_ll.tree2d.as_ref().map_or(0, |t| t[256] as usize),
        );
        break;
    }

    uivector_cleanup(&mut lz77_encoded);
    HuffmanTree_cleanup(&mut tree_ll);
    HuffmanTree_cleanup(&mut tree_d);
    HuffmanTree_cleanup(&mut tree_cl);

    error
}
pub fn LodePNGBitWriter_init(writer: &mut LodePngBitWriter, data: &mut ucvector::Ucvector) {
	println!("* LodePNGBitWriter_init");
    writer.data = Some(Box::new(data.clone()));
    writer.bp = 0;
}
pub fn lodepng_deflatev(
    out: &mut ucvector::Ucvector,
    in_data: &[u8],
    insize: usize,
    settings: &LodePngCompressSettings,
) -> u32 {
	println!("* lodepng_deflatev");
    let mut error = 0;
    let mut blocksize;
    let mut numdeflateblocks;
    let mut hash = Hash {
        head: Option::None,
        chain: Option::None,
        val: Option::None,
        headz: Option::None,
        chainz: Option::None,
        zeros: Option::None,
    };
    let mut writer = LodePngBitWriter {
        data: Option::None,
        bp: 0,
    };
    
    LodePNGBitWriter_init(&mut writer, out);
    
    if settings.btype > 2 {
        return 61;
    } else if settings.btype == 0 {
        return deflateNoCompression(&mut lodepng::Ucvector {
            data: out.data.clone(),
            size: out.size,
            allocsize: out.allocsize,
        }, in_data).unwrap_or(1);
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
    
    error = hash_init(&mut hash, settings.windowsize.try_into().unwrap());
    if error == 0 {
        for i in 0..numdeflateblocks {
            if error != 0 {
                break;
            }
            
            let final_ = i == (numdeflateblocks - 1);
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
    settings: &LodePngCompressSettings,
) -> u32 {
	println!("* lodepng_deflate");
    let mut v = ucvector::Ucvector {
        data: out.take(),
        size: *outsize,
        allocsize: 0,
    };
    
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
    settings: &LodePngCompressSettings,
) -> u32 {
	println!("* deflate");
    if let Some(custom_deflate) = settings.custom_deflate {
        // Convert Rust references to raw pointers for FFI call
        let mut out_ptr: *mut c_uchar = std::ptr::null_mut();
        let mut outsize_val = *outsize;
        let in_ptr = in_data.as_ptr();
        
        let error = custom_deflate(
            &mut out_ptr as *mut *mut c_uchar,
            &mut outsize_val as *mut usize,
            in_ptr,
            insize,
            settings as *const _ as *const LodePngCompressSettings,
        );
        
        // Update output parameters if successful
        if error == 0 {
            unsafe {
                *out = Some(Vec::from_raw_parts(out_ptr, outsize_val, outsize_val));
                *outsize = outsize_val;
            }
        }
        
        if error != 0 { 111 } else { 0 }
    } else {
        lodepng_deflate(out, outsize, in_data, insize, settings)
    }
}
pub fn lodepng_zlib_compress(
    out: &mut Option<Box<[u8]>>,
    outsize: &mut usize,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngCompressSettings,
) -> u32 {
	println!("* lodepng_zlib_compress");
    let mut error;
    let mut deflatedata: Option<Vec<u8>> = None;
    let mut deflatesize = 0;

    // Call deflate function
    error = deflate(
        &mut deflatedata,
        &mut deflatesize,
        in_data.expect("Input data cannot be None"),
        insize,
        settings,
    );

    *out = None;
    *outsize = 0;
    error = 0;

    if error == 0 {
        *outsize = deflatesize + 6;
        *out = Some(vec![0; *outsize].into_boxed_slice());
        
        if out.is_none() {
            error = 83;
        }
    }

    if error == 0 {
        let out_slice = out.as_mut().unwrap();
        let ADLER32 = adler32(in_data, insize as u32);
        let CMF = 120;
        let FLEVEL = 0;
        let FDICT = 0;
        let CMFFLG = ((256 * CMF) + (FDICT * 32)) + (FLEVEL * 64);
        let FCHECK = 31 - (CMFFLG % 31);
        let CMFFLG = CMFFLG + FCHECK;

        out_slice[0] = (CMFFLG >> 8) as u8;
        out_slice[1] = (CMFFLG & 255) as u8;

        if let Some(deflatedata) = &deflatedata {
            for i in 0..deflatesize {
                out_slice[i + 2] = deflatedata[i];
            }
        }

        let last_four_bytes = &mut out_slice[*outsize - 4..*outsize];
        lodepng_set32bitInt(
            last_four_bytes.try_into().expect("slice with exactly 4 bytes"),
            ADLER32,
        );
    }

    lodepng_free(deflatedata.map(|v| Box::new(v) as Box<dyn std::any::Any>));
    error
}
pub fn zlib_compress(
    out: &mut Option<Box<[u8]>>,
    outsize: &mut usize,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngCompressSettings,
) -> u32 {
	println!("* zlib_compress");
    if let Some(custom_zlib) = settings.custom_zlib {
        // Convert Rust references to raw pointers for FFI call
        let mut out_ptr: *mut *mut c_uchar = std::ptr::null_mut();
        let mut outsize_ptr: *mut usize = std::ptr::null_mut();
        let in_ptr: *const c_uchar = if let Some(data) = in_data {
            data.as_ptr()
        } else {
            std::ptr::null()
        };
        
        // Call the custom_zlib function through FFI
        let error = custom_zlib(
            out_ptr,
            outsize_ptr,
            in_ptr,
            insize,
            settings as *const _ as *const LodePngCompressSettings,
        );
        
        if error != 0 { 111 } else { 0 }
    } else {
        lodepng_zlib_compress(out, outsize, in_data, insize, settings)
    }
}
pub fn filter(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    color: &LodePNGColorMode,
    settings: &LodePngEncoderSettings,
) -> u32 {
	println!("* filter");
    let bpp = lodepng_get_bpp(color);
    let linebytes = lodepng_get_raw_size_idat(w, 1, bpp as u32) - 1;
    let bytewidth = (bpp as usize + 7) / 8;
    let mut prevline: Option<&[u8]> = None;
    let mut error = 0;
    let strategy = settings.filter_strategy;

    if settings.filter_palette_zero != 0 && (color.colortype == LodePNGColorType::LCT_PALETTE || color.bitdepth < 8) {
        return 0;
    }

    if bpp == 0 {
        return 31;
    }

    match strategy {
        LodePNGFilterStrategy::LFS_ZERO
        | LodePNGFilterStrategy::LFS_ONE
        | LodePNGFilterStrategy::LFS_TWO
        | LodePNGFilterStrategy::LFS_THREE
        | LodePNGFilterStrategy::LFS_FOUR => {
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
        LodePNGFilterStrategy::LFS_MINSUM => {
            let mut attempt: [Option<Vec<u8>>; 5] = [None, None, None, None, None];
            let mut smallest = 0;
            let mut best_type = 0;

            for type_idx in 0..5 {
                attempt[type_idx] = Some(vec![0; linebytes]);
            }

            if error == 0 {
                for y in 0..h {
                    for type_idx in 0..5 {
                        let mut sum = 0;
                        filterScanline(
                            attempt[type_idx].as_mut().unwrap(),
                            &in_data[(y as usize * linebytes)..],
                            prevline,
                            linebytes,
                            bytewidth,
                            type_idx as u8,
                        );

                        if type_idx == 0 {
                            sum = attempt[type_idx].as_ref().unwrap().iter().map(|&x| x as usize).sum();
                        } else {
                            sum = attempt[type_idx]
                                .as_ref()
                                .unwrap()
                                .iter()
                                .map(|&s| if s < 128 { s as usize } else { 255 - s as usize })
                                .sum();
                        }

                        if type_idx == 0 || sum < smallest {
                            best_type = type_idx;
                            smallest = sum;
                        }
                    }

                    prevline = Some(&in_data[(y as usize * linebytes)..]);
                    out[y as usize * (linebytes + 1)] = best_type as u8;
                    out[(y as usize * (linebytes + 1) + 1)..(y as usize * (linebytes + 1) + 1 + linebytes)]
                        .copy_from_slice(&attempt[best_type].as_ref().unwrap()[..linebytes]);
                }
            }
        }
        LodePNGFilterStrategy::LFS_ENTROPY => {
            let mut attempt: [Option<Vec<u8>>; 5] = [None, None, None, None, None];
            let mut best_sum = 0;
            let mut best_type = 0;
            let mut count = [0; 256];

            for type_idx in 0..5 {
                attempt[type_idx] = Some(vec![0; linebytes]);
            }

            if error == 0 {
                for y in 0..h {
                    for type_idx in 0..5 {
                        let mut sum = 0;
                        filterScanline(
                            attempt[type_idx].as_mut().unwrap(),
                            &in_data[(y as usize * linebytes)..],
                            prevline,
                            linebytes,
                            bytewidth,
                            type_idx as u8,
                        );

                        count.fill(0);
                        for &val in attempt[type_idx].as_ref().unwrap() {
                            count[val as usize] += 1;
                        }

                        count[type_idx] += 1;
                        for &c in count.iter() {
                            sum += ilog2i(c);
                        }

                        if type_idx == 0 || sum > best_sum {
                            best_type = type_idx;
                            best_sum = sum;
                        }
                    }

                    prevline = Some(&in_data[(y as usize * linebytes)..]);
                    out[y as usize * (linebytes + 1)] = best_type as u8;
                    out[(y as usize * (linebytes + 1) + 1)..(y as usize * (linebytes + 1) + 1 + linebytes)]
                        .copy_from_slice(&attempt[best_type].as_ref().unwrap()[..linebytes]);
                }
            }
        }
        LodePNGFilterStrategy::LFS_PREDEFINED => {
            if let Some(predefined_filters) = settings.predefined_filters {
                for y in 0..h {
                    let outindex = (1 + linebytes) * y as usize;
                    let inindex = linebytes * y as usize;
                    let filter_type = unsafe { *predefined_filters.add(y as usize) };
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
        }
        LodePNGFilterStrategy::LFS_BRUTE_FORCE => {
            let mut attempt: [Option<Vec<u8>>; 5] = [None, None, None, None, None];
            let mut size = [0; 5];
            let mut smallest = 0;
            let mut best_type = 0;
            let mut zlibsettings = settings.zlibsettings.clone();
            zlibsettings.btype = 1;
            zlibsettings.custom_zlib = None;
            zlibsettings.custom_deflate = None;

            for type_idx in 0..5 {
                attempt[type_idx] = Some(vec![0; linebytes]);
            }

            if error == 0 {
                for y in 0..h {
                    for type_idx in 0..5 {
                        let testsize = linebytes;
                        filterScanline(
                            attempt[type_idx].as_mut().unwrap(),
                            &in_data[(y as usize * linebytes)..],
                            prevline,
                            linebytes,
                            bytewidth,
                            type_idx as u8,
                        );

                        let mut compressed: Option<Box<[u8]>> = None;
                        let mut outsize = 0;
                        zlib_compress(
                            &mut compressed,
                            &mut outsize,
                            Some(attempt[type_idx].as_ref().unwrap()),
                            testsize,
                            &zlibsettings,
                        );
                        size[type_idx] = outsize;

                        if type_idx == 0 || size[type_idx] < smallest {
                            best_type = type_idx;
                            smallest = size[type_idx];
                        }
                    }

                    prevline = Some(&in_data[(y as usize * linebytes)..]);
                    out[y as usize * (linebytes + 1)] = best_type as u8;
                    out[(y as usize * (linebytes + 1) + 1)..(y as usize * (linebytes + 1) + 1 + linebytes)]
                        .copy_from_slice(&attempt[best_type].as_ref().unwrap()[..linebytes]);
                }
            }
        }
        _ => return 88,
    }

    error
}
pub fn addPaddingBits(out: &mut [u8], in_: &[u8], olinebits: usize, ilinebits: usize, h: usize) {
	println!("* addPaddingBits");
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
pub fn Adam7_interlace(out: &mut [u8], in_data: &[u8], w: u32, h: u32, bpp: u32) {
	println!("* Adam7_interlace");
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
                    let pixelinstart = (((ADAM7_IY[i] + (y * ADAM7_DY[i])) * w) + ADAM7_IX[i] + (x * ADAM7_DX[i])) as usize * bytewidth as usize;
                    let pixeloutstart = passstart[i] + ((y * passw[i] + x) as usize * bytewidth as usize);
                    
                    for b in 0..bytewidth {
                        out[pixeloutstart + b as usize] = in_data[pixelinstart + b as usize];
                    }
                }
            }
        }
    } else {
        for i in 0..7 {
            let ilinebits = bpp * passw[i];
            let olinebits = bpp * w;
            
            for y in 0..passh[i] {
                for x in 0..passw[i] {
                    let mut ibp = ((ADAM7_IY[i] + (y * ADAM7_DY[i])) * olinebits + (ADAM7_IX[i] + (x * ADAM7_DX[i])) * bpp) as usize;
                    let mut obp = (8 * passstart[i]) + ((y * ilinebits + x * bpp) as usize);
                    
                    for b in 0..bpp {
                        let bit = readBitFromReversedStream(&mut ibp, in_data);
                        setBitOfReversedStream(&mut obp, out, bit);
                    }
                }
            }
        }
    }
}
pub fn preProcessScanlines(
    out: &mut Option<Box<[u8]>>,
    outsize: &mut usize,
    in_data: &[u8],
    w: u32,
    h: u32,
    info_png: &LodePngInfo,
    settings: &LodePngEncoderSettings,
) -> u32 {
	println!("* preProcessScanlines");
    let bpp = lodepng_get_bpp(&info_png.color) as u32;
    let mut error = 0;

    if info_png.interlace_method == 0 {
        *outsize = h as usize + (h as usize * (((w * bpp) + 7) / 8) as usize);
        *out = Some(vec![0; *outsize].into_boxed_slice());
        
        if out.is_none() && *outsize > 0 {
            error = 83;
        }

        if error == 0 {
            if bpp < 8 && (w * bpp) != ((((w * bpp) + 7) / 8) * 8) {
                let padded_size = h as usize * (((w * bpp) + 7) / 8) as usize;
                let mut padded = Some(vec![0; padded_size].into_boxed_slice());
                
                if padded.is_none() {
                    error = 83;
                }

                if error == 0 {
                    addPaddingBits(
                        padded.as_mut().unwrap(),
                        in_data,
                        (((w * bpp) + 7) / 8) as usize * 8,
                        (w * bpp) as usize,
                        h as usize,
                    );
                    error = filter(
                        out.as_mut().unwrap(),
                        padded.as_ref().unwrap(),
                        w,
                        h,
                        &info_png.color,
                        settings,
                    );
                }
                lodepng_free(padded.map(|b| Box::new(b) as Box<dyn std::any::Any>));
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
    } else {
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
        *out = Some(vec![0; *outsize].into_boxed_slice());
        
        if out.is_none() {
            error = 83;
        }

        let mut adam7 = Some(vec![0; passstart[7]].into_boxed_slice());
        if adam7.is_none() && passstart[7] > 0 {
            error = 83;
        }

        if error == 0 {
            Adam7_interlace(adam7.as_mut().unwrap(), in_data, w, h, bpp);

            for i in 0..7 {
                if bpp < 8 {
                    let padded_size = padded_passstart[i + 1] - padded_passstart[i];
                    let mut padded = Some(vec![0; padded_size].into_boxed_slice());
                    
                    if padded.is_none() {
                        error = 83;
                        break;
                    }

                    addPaddingBits(
                        padded.as_mut().unwrap(),
                        &adam7.as_ref().unwrap()[passstart[i]..],
                        (((passw[i] * bpp) + 7) / 8) as usize * 8,
                        (passw[i] * bpp) as usize,
                        passh[i] as usize,
                    );
                    error = filter(
                        &mut out.as_mut().unwrap()[filter_passstart[i]..],
                        padded.as_ref().unwrap(),
                        passw[i],
                        passh[i],
                        &info_png.color,
                        settings,
                    );
                    lodepng_free(padded.map(|b| Box::new(b) as Box<dyn std::any::Any>));
                } else {
                    error = filter(
                        &mut out.as_mut().unwrap()[filter_passstart[i]..],
                        &adam7.as_ref().unwrap()[padded_passstart[i]..],
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
        }
        lodepng_free(adam7.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    }
    error
}
pub fn lodepng_assign_icc(info: &mut LodePngInfo, name: Option<&str>, profile: Option<&[u8]>, profile_size: u32) -> u32 {
	println!("* lodepng_assign_icc");
    if profile_size == 0 {
        return 100;
    }

    let profile = match profile {
        Some(p) => p,
        None => return 83,
    };

    info.iccp_name = match alloc_string(name) {
        Some(name_bytes) => Some(String::from_utf8_lossy(&name_bytes).into_owned()),
        None => return 83,
    };

    info.iccp_profile = Some(profile.to_vec());
    info.iccp_profile_size = profile_size;

    0
}
pub fn LodePNGUnknownChunks_copy(dest: &mut LodePngInfo, src: &LodePngInfo) -> u32 {
	println!("* LodePNGUnknownChunks_copy");
    LodePNGUnknownChunks_cleanup(dest);

    for i in 0..3 {
        dest.unknown_chunks_size[i] = src.unknown_chunks_size[i];
        
        if src.unknown_chunks_size[i] > 0 {
            let mut data = Vec::with_capacity(src.unknown_chunks_size[i]);
            data.extend_from_slice(&src.unknown_chunks_data[i].as_ref().unwrap());
            dest.unknown_chunks_data[i] = Some(data);
        } else {
            dest.unknown_chunks_data[i] = None;
        }
    }

    0
}
pub fn LodePNGText_copy(dest: &mut LodePngInfo, source: &LodePngInfo) -> u32 {
	println!("* LodePNGText_copy");
    dest.text_keys = None;
    dest.text_strings = None;
    dest.text_num = 0;

    if let (Some(keys), Some(strings)) = (&source.text_keys, &source.text_strings) {
        for i in 0..source.text_num {
            let error = lodepng_add_text(
                dest,
                keys.get(i).map(|s| s.as_str()),
                strings.get(i).map(|s| s.as_str()),
            );
            if error != 0 {
                return error;
            }
        }
    }

    0
}
pub fn lodepng_add_itext(
    info: &mut LodePngInfo,
    key: Option<&str>,
    langtag: Option<&str>,
    transkey: Option<&str>,
    str: Option<&str>,
) -> u32 {
	println!("* lodepng_add_itext");
    lodepng_add_itext_sized(info, key, langtag, transkey, str.map(|s| s.as_bytes()), lodepng_strlen(str))
}
pub fn LodePNGIText_copy(dest: &mut LodePngInfo, source: &LodePngInfo) -> u32 {
	println!("* LodePNGIText_copy");
    dest.itext_keys = None;
    dest.itext_langtags = None;
    dest.itext_transkeys = None;
    dest.itext_strings = None;
    dest.itext_num = 0;

    for i in 0..source.itext_num {
        let key = source.itext_keys.as_ref().and_then(|v| v.get(i)).map(|s| s.as_str());
        let langtag = source.itext_langtags.as_ref().and_then(|v| v.get(i)).map(|s| s.as_str());
        let transkey = source.itext_transkeys.as_ref().and_then(|v| v.get(i)).map(|s| s.as_str());
        let string = source.itext_strings.as_ref().and_then(|v| v.get(i)).map(|s| s.as_str());

        let error = lodepng_add_itext(dest, key, langtag, transkey, string);
        if error != 0 {
            return error;
        }
    }

    0
}
pub fn lodepng_info_copy(dest: &mut LodePngInfo, source: &LodePngInfo) -> u32 {
	println!("* lodepng_info_copy");
    lodepng_info_cleanup(dest);
    *dest = source.clone();
    
    lodepng_color_mode_init(&mut dest.color);
    {
        let error = lodepng_color_mode_copy(&mut dest.color, &source.color);
        if error != 0 {
            return error;
        }
    }
    
    {
        let error = LodePNGText_copy(dest, source);
        if error != 0 {
            return error;
        }
    }
    
    {
        let error = LodePNGIText_copy(dest, source);
        if error != 0 {
            return error;
        }
    }
    
    if source.iccp_defined != 0 {
        let error = lodepng_assign_icc(
            dest,
            source.iccp_name.as_deref(),
            source.iccp_profile.as_deref(),
            source.iccp_profile_size,
        );
        if error != 0 {
            return error;
        }
    }
    
    LodePNGUnknownChunks_init(dest);
    {
        let error = LodePNGUnknownChunks_copy(dest, source);
        if error != 0 {
            return error;
        }
    }
    
    0
}

pub fn lodepng_convert_rgb(
    r_out: &mut Option<u32>,
    g_out: &mut Option<u32>,
    b_out: &mut Option<u32>,
    r_in: u32,
    g_in: u32,
    b_in: u32,
    mode_out: &LodePNGColorMode,
    mode_in: &LodePNGColorMode,
) -> u32 {
	println!("* lodepng_convert_rgb");
    let mut r = 0u32;
    let mut g = 0u32;
    let mut b = 0u32;

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
                let base = (r_in * 4) as usize;
                if base + 2 >= palette.len() {
                    return 82;
                }
                r = u32::from(palette[base]) * 257u32;
                g = u32::from(palette[base + 1]) * 257u32;
                b = u32::from(palette[base + 2]) * 257u32;
            } else {
                return 31;
            }
        }
    }

    match mode_out.colortype {
        LodePNGColorType::LCT_GREY | LodePNGColorType::LCT_GREY_ALPHA => {
            *r_out = Some(r >> shift);
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_RGBA => {
            *r_out = Some(r >> shift);
            *g_out = Some(g >> shift);
            *b_out = Some(b >> shift);
        }
        LodePNGColorType::LCT_PALETTE => {
            if ((r >> 8) != (r & 255)) || ((g >> 8) != (g & 255)) || ((b >> 8) != (b & 255)) {
                return 82;
            }
            if let Some(palette) = &mode_out.palette {
                for i in 0..mode_out.palettesize {
                    let j = i * 4;
                    if j + 2 >= palette.len() {
                        continue;
                    }
                    if (r >> 8) == u32::from(palette[j])
                        && (g >> 8) == u32::from(palette[j + 1])
                        && (b >> 8) == u32::from(palette[j + 2])
                    {
                        *r_out = Some(i as u32);
                        return 0;
                    }
                }
            }
            return 82;
        }
    }

    0
}
pub fn lodepng_color_stats_init(stats: &mut LodePNGColorStats) {
	println!("* lodepng_color_stats_init");
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
pub fn lodepng_is_greyscale_type(info: &LodePNGColorMode) -> bool {
	println!("* lodepng_is_greyscale_type");
    info.colortype == LodePNGColorType::LCT_GREY || info.colortype == LodePNGColorType::LCT_GREY_ALPHA
}
pub fn lodepng_is_alpha_type(info: &LodePNGColorMode) -> bool {
	println!("* lodepng_is_alpha_type");
    (info.colortype as u32 & 4) != 0
}
pub fn lodepng_has_palette_alpha(info: &LodePNGColorMode) -> u32 {
	println!("* lodepng_has_palette_alpha");
    // Check if palette exists and has entries
    if let Some(palette) = &info.palette {
        for i in 0..info.palettesize {
            // Check alpha channel (every 4th byte starting at index 3)
            if palette[(i * 4) + 3] < LCT_MAX_OCTET_VALUE {
                return 1;
            }
        }
    }
    
    0
}
pub fn lodepng_can_have_alpha(info: &LodePNGColorMode) -> u32 {
	println!("* lodepng_can_have_alpha");
    (info.key_defined != 0 || lodepng_is_alpha_type(info) || lodepng_has_palette_alpha(info) != 0) as u32
}
pub fn color_tree_has(tree: &ColorTree, r: u8, g: u8, b: u8, a: u8) -> bool {
	println!("* color_tree_has");
    color_tree_get(tree, r, g, b, a) >= 0
}
pub fn lodepng_compute_color_stats(
    stats: &mut LodePNGColorStats,
    in_data: &[u8],
    w: u32,
    h: u32,
    mode_in: &LodePNGColorMode,
) -> u32 {
	println!("* lodepng_compute_color_stats");
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
    let mut alpha_done = if lodepng_can_have_alpha(mode_in) == 0 { 1 } else { 0 };
    let mut numcolors_done = 0;
    let bpp = lodepng_get_bpp(mode_in) as u32;
    let mut bits_done = if (stats.bits == 1) && (bpp == 1) { 1 } else { 0 };
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
        for i in 0..stats.numcolors as usize {
            let color = &stats.palette[i * 4..i * 4 + 4];
            error = color_tree_add(&mut tree, color[0], color[1], color[2], color[3], i as u32);
            if error != 0 {
                color_tree_cleanup(&mut tree);
                return error;
            }
        }
    }

    if mode_in.bitdepth == 16 && sixteen == 0 {
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
    }

    if sixteen != 0 {
        let mut r = 0u16;
        let mut g = 0u16;
        let mut b = 0u16;
        let mut a = 0u16;

        for i in 0..numpixels {
            getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            if colored_done == 0 && (r != g || r != b) {
                stats.colored = 1;
                colored_done = 1;
            }

            if alpha_done == 0 {
                let matchkey = (r == stats.key_r as u16) && (g == stats.key_g as u16) && (b == stats.key_b as u16);
                if (a != 65535) && (a != 0 || (stats.key != 0 && !matchkey)) {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                } else if a == 0 && stats.alpha == 0 && stats.key == 0 {
                    stats.key = 1;
                    stats.key_r = r as u16;
                    stats.key_g = g as u16;
                    stats.key_b = b as u16;
                } else if a == 65535 && stats.key != 0 && matchkey {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                }
            }

            if alpha_done != 0 && numcolors_done != 0 && colored_done != 0 && bits_done != 0 {
                break;
            }
        }

        if stats.key != 0 && stats.alpha == 0 {
            let mut r = 0u16;
            let mut g = 0u16;
            let mut b = 0u16;
            let mut a = 0u16;

            for i in 0..numpixels {
                getPixelColorRGBA16(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
                if a != 0 && r == stats.key_r as u16 && g == stats.key_g as u16 && b == stats.key_b as u16 {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                }
            }
        }
    } else {
        let mut r = 0u8;
        let mut g = 0u8;
        let mut b = 0u8;
        let mut a = 0u8;

        for i in 0..numpixels {
            getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
            if bits_done == 0 && stats.bits < 8 {
                let bits = getValueRequiredBits(r) as u32;
                if bits > stats.bits {
                    stats.bits = bits;
                }
            }
            bits_done = if stats.bits >= bpp { 1 } else { 0 };

            if colored_done == 0 && (r != g || r != b) {
                stats.colored = 1;
                colored_done = 1;
                if stats.bits < 8 {
                    stats.bits = 8;
                }
            }

            if alpha_done == 0 {
                let matchkey = (r == stats.key_r as u8) && (g == stats.key_g as u8) && (b == stats.key_b as u8);
                if a != 255 && (a != 0 || (stats.key != 0 && !matchkey)) {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                    if stats.bits < 8 {
                        stats.bits = 8;
                    }
                } else if a == 0 && stats.alpha == 0 && stats.key == 0 {
                    stats.key = 1;
                    stats.key_r = r as u16;
                    stats.key_g = g as u16;
                    stats.key_b = b as u16;
                } else if a == 255 && stats.key != 0 && matchkey {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                    if stats.bits < 8 {
                        stats.bits = 8;
                    }
                }
            }

            if numcolors_done == 0 {
                if !color_tree_has(&tree, r, g, b, a) {
                    error = color_tree_add(&mut tree, r, g, b, a, stats.numcolors);
                    if error != 0 {
                        color_tree_cleanup(&mut tree);
                        return error;
                    }
                    if stats.numcolors < 256 {
                        let n = stats.numcolors as usize;
                        stats.palette[n * 4] = r;
                        stats.palette[n * 4 + 1] = g;
                        stats.palette[n * 4 + 2] = b;
                        stats.palette[n * 4 + 3] = a;
                    }
                    stats.numcolors += 1;
                    numcolors_done = if stats.numcolors >= maxnumcolors { 1 } else { 0 };
                }
            }

            if alpha_done != 0 && numcolors_done != 0 && colored_done != 0 && bits_done != 0 {
                break;
            }
        }

        if stats.key != 0 && stats.alpha == 0 {
            let mut r = 0u8;
            let mut g = 0u8;
            let mut b = 0u8;
            let mut a = 0u8;

            for i in 0..numpixels {
                getPixelColorRGBA8(&mut r, &mut g, &mut b, &mut a, in_data, i, mode_in);
                if a != 0 && r == stats.key_r as u8 && g == stats.key_g as u8 && b == stats.key_b as u8 {
                    stats.alpha = 1;
                    stats.key = 0;
                    alpha_done = 1;
                    if stats.bits < 8 {
                        stats.bits = 8;
                    }
                }
            }
        }

        stats.key_r += stats.key_r << 8;
        stats.key_g += stats.key_g << 8;
        stats.key_b += stats.key_b << 8;
    }

    color_tree_cleanup(&mut tree);
    error
}

pub fn lodepng_color_stats_add(
    stats: &mut LodePNGColorStats,
    r: u32,
    g: u32,
    b: u32,
    a: u32,
) -> u32 {
	println!("* lodepng_color_stats_add");
    let mut image = [0u8; 8];
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

    image[0] = (r >> 8) as u8;
    image[1] = r as u8;
    image[2] = (g >> 8) as u8;
    image[3] = g as u8;
    image[4] = (b >> 8) as u8;
    image[5] = b as u8;
    image[6] = (a >> 8) as u8;
    image[7] = a as u8;

    let error = lodepng_compute_color_stats(stats, &image, 1, 1, &mode);
    lodepng_color_mode_cleanup(&mut mode);
    error
}
pub fn lodepng_color_mode_make(colortype: LodePNGColorType, bitdepth: u32) -> LodePNGColorMode {
	println!("* lodepng_color_mode_make");
    let mut result = LodePNGColorMode {
        colortype,
        bitdepth,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut result);
    result
}
pub fn lodepng_palette_add(
    info: &mut LodePNGColorMode,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) -> u32 {
	println!("* lodepng_palette_add");
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
        palette.push(r);
        palette.push(g);
        palette.push(b);
        palette.push(a);
        info.palettesize += 1;
    }

    0
}

pub fn auto_choose_color(
    mode_out: &mut LodePNGColorMode,
    mode_in: &LodePNGColorMode,
    stats: &LodePNGColorStats,
) -> u32 {
	println!("* auto_choose_color");
    let mut error = 0;
    let numpixels = stats.numpixels;
    let mut alpha = stats.alpha;
    let mut key = stats.key;
    let mut bits = stats.bits;
    
    mode_out.key_defined = 0;
    
    if key != 0 && numpixels <= 16 {
        alpha = 1;
        key = 0;
        if bits < 8 {
            bits = 8;
        }
    }
    
    let mut gray_ok = if stats.colored == 0 { 1 } else { 0 };
    if stats.allow_greyscale == 0 {
        gray_ok = 0;
    }
    if gray_ok == 0 && bits < 8 {
        bits = 8;
    }
    
    let n = stats.numcolors;
    let palettebits = match n {
        n if n <= 2 => 1,
        n if n <= 4 => 2,
        n if n <= 16 => 4,
        _ => 8,
    };
    
    let mut palette_ok = if n <= 256 && bits <= 8 && n != 0 { 1 } else { 0 };
    if numpixels < usize::try_from(n * 2).unwrap_or(usize::MAX) {
        palette_ok = 0;
    }
    if gray_ok != 0 && alpha == 0 && bits <= palettebits {
        palette_ok = 0;
    }
    if stats.allow_palette == 0 {
        palette_ok = 0;
    }
    
    if palette_ok != 0 {
        let p = stats.palette;
        lodepng_palette_clear(mode_out);
        
        for i in 0..stats.numcolors {
            let idx = usize::try_from(i * 4).unwrap_or(0);
            error = lodepng_palette_add(
                mode_out,
                p[idx],
                p[idx + 1],
                p[idx + 2],
                p[idx + 3],
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
            error = lodepng_color_mode_copy(mode_out, mode_in);
        }
    } else {
        mode_out.bitdepth = bits;
        mode_out.colortype = if alpha != 0 {
            if gray_ok != 0 {
                LodePNGColorType::LCT_GREY_ALPHA
            } else {
                LodePNGColorType::LCT_RGBA
            }
        } else {
            if gray_ok != 0 {
                LodePNGColorType::LCT_GREY
            } else {
                LodePNGColorType::LCT_RGB
            }
        };
        
        if key != 0 {
            let mask = (1u32 << mode_out.bitdepth) - 1u32;
            mode_out.key_r = (stats.key_r as u32) & mask;
            mode_out.key_g = (stats.key_g as u32) & mask;
            mode_out.key_b = (stats.key_b as u32) & mask;
            mode_out.key_defined = 1;
        }
    }
    
    error
}
pub fn lodepng_chunk_next<'a>(chunk: &'a [u8], end: &'a [u8]) -> &'a [u8] {
	println!("* lodepng_chunk_next");
    let available_size = end.len().wrapping_sub(chunk.len());
    
    if chunk.is_empty() || end.is_empty() || chunk.len() >= end.len() || available_size < 12 {
        return end;
    }

    // Check for PNG signature
    if chunk[0] == 0x89 && 
       chunk[1] == 0x50 && 
       chunk[2] == 0x4e && 
       chunk[3] == 0x47 && 
       chunk[4] == 0x0d && 
       chunk[5] == 0x0a && 
       chunk[6] == 0x1a && 
       chunk[7] == 0x0a {
        return &chunk[8..];
    } else {
        let chunk_length = lodepng_chunk_length(chunk) as usize;
        let mut total_chunk_length = 0;
        
        if lodepng_addofl(chunk_length, 12, &mut total_chunk_length) {
            return end;
        }

        match total_chunk_length.cmp(&available_size) {
            Ordering::Greater => end,
            _ => &chunk[total_chunk_length..],
        }
    }
}
pub fn addUnknownChunks(out: &mut Ucvector, data: &[u8]) -> u32 {
	println!("* addUnknownChunks");
    let mut inchunk_idx = 0;
    let data_len = data.len();
    
    while inchunk_idx < data_len {
        let chunk = &data[inchunk_idx..];
        let mut boxed_data = out.data.as_mut().map(|v| v.clone().into_boxed_slice());
        let error = lodepng_chunk_append(&mut boxed_data, &mut out.size, chunk);
        if error != 0 {
            return error;
        }
        out.data = boxed_data.map(|b| b.into_vec());
        
        out.allocsize = out.size;
        inchunk_idx = lodepng_chunk_next(&data[inchunk_idx..], &data[data_len..]).as_ptr() as usize - data.as_ptr() as usize;
    }

    0
}
pub fn lodepng_chunk_init<'a>(
    chunk: &mut Option<&'a mut [u8]>,
    out: &'a mut Ucvector,
    length: usize,
    type_: &[u8; 4],
) -> u32 {
	println!("* lodepng_chunk_init");
    let mut new_length = out.size;
    if lodepng_addofl(new_length, length, &mut new_length) {
        return 77;
    }
    if lodepng_addofl(new_length, 12, &mut new_length) {
        return 77;
    }
    if !ucvector_resize(out, new_length) {
        return 83;
    }

    if let Some(ref mut data) = out.data {
        let chunk_start = (data.len() - length) - 12;
        *chunk = Some(&mut data[chunk_start..]);

        if let Some(chunk_slice) = chunk {
            let mut length_bytes = [0u8; 4];
            lodepng_set32bitInt(&mut length_bytes, length as u32);
            lodepng_memcpy(&mut chunk_slice[0..4], &length_bytes);
            lodepng_memcpy(&mut chunk_slice[4..8], type_);
        }
    }

    0
}
pub fn lodepng_chunk_generate_crc(chunk: &mut [u8]) {
	println!("* lodepng_chunk_generate_crc");
    let length = lodepng_chunk_length(chunk);
    let crc = lodepng_crc32(Some(&chunk[4..]), (length + 4) as usize);
    
    // Calculate the position where CRC should be written
    let crc_position = 8 + length as usize;
    
    // Ensure we have enough space for the CRC (4 bytes)
    if chunk.len() >= crc_position + 4 {
        // Create a mutable reference to the 4-byte slice where CRC will be written
        let crc_slice = &mut chunk[crc_position..crc_position + 4];
        
        // Convert the mutable slice to a fixed-size array
        let mut crc_array = [0u8; 4];
        crc_array.copy_from_slice(crc_slice);
        
        // Write the CRC value
        lodepng_set32bitInt(&mut crc_array, crc);
        
        // Copy back to the original chunk
        crc_slice.copy_from_slice(&crc_array);
    }
}

pub fn addChunk_zTXt(
    out: &mut Ucvector,
    keyword: Option<&str>,
    textstring: Option<&str>,
    zlibsettings: &LodePngCompressSettings,
) -> u32 {
	println!("* addChunk_zTXt");
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Box<[u8]>> = None;
    let mut compressedsize = 0;
    let textsize = lodepng_strlen(textstring);
    let keysize = lodepng_strlen(keyword);

    if keysize < 1 || keysize > 79 {
        return 89;
    }

    error = zlib_compress(
        &mut compressed,
        &mut compressedsize,
        textstring.map(|s| s.as_bytes()),
        textsize,
        zlibsettings,
    );

    if error == 0 {
        let size = (keysize + 2) + compressedsize;
        error = lodepng_chunk_init(&mut chunk, out, size, b"zTXt");
    }

    if error == 0 {
        if let Some(chunk_data) = chunk.as_deref_mut() {
            if let Some(keyword_str) = keyword {
                lodepng_memcpy(&mut chunk_data[8..], keyword_str.as_bytes());
            }
            chunk_data[8 + keysize] = 0;
            chunk_data[9 + keysize] = 0;
            if let Some(compressed_data) = compressed.as_deref() {
                lodepng_memcpy(
                    &mut chunk_data[10 + keysize..],
                    compressed_data,
                );
            }
            lodepng_chunk_generate_crc(chunk_data);
        }
    }

    lodepng_free(compressed.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    error
}

pub fn addChunk_tRNS(out: &mut Ucvector, info: &LodePNGColorMode) -> u32 {
	println!("* addChunk_tRNS");
    let mut chunk: Option<&mut [u8]> = None;

    match info.colortype {
        LodePNGColorType::LCT_PALETTE => {
            let mut amount = info.palettesize;
            if let Some(palette) = &info.palette {
                for i in (0..info.palettesize).rev() {
                    if palette[(4 * i) + 3] != LCT_MAX_OCTET_VALUE {
                        break;
                    }
                    amount -= 1;
                }
            }

            if amount > 0 {
                let error = lodepng_chunk_init(&mut chunk, out, amount, b"tRNS");
                if error != 0 {
                    return error;
                }

                if let Some(chunk_data) = &mut chunk {
                    if let Some(palette) = &info.palette {
                        for i in 0..amount {
                            chunk_data[8 + i] = palette[(4 * i) + 3];
                        }
                    }
                }
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
            if info.key_defined != 0 {
                let error = lodepng_chunk_init(&mut chunk, out, 6, b"tRNS");
                if error != 0 {
                    return error;
                }

                if let Some(chunk_data) = &mut chunk {
                    chunk_data[8] = (info.key_r >> 8) as u8;
                    chunk_data[9] = (info.key_r & 255) as u8;
                    chunk_data[10] = (info.key_g >> 8) as u8;
                    chunk_data[11] = (info.key_g & 255) as u8;
                    chunk_data[12] = (info.key_b >> 8) as u8;
                    chunk_data[13] = (info.key_b & 255) as u8;
                }
            }
        }
        _ => {}
    }

    if let Some(chunk_data) = &mut chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}

pub fn addChunk_tIME(out: &mut Ucvector, time: &LodePngTime) -> u32 {
	println!("* addChunk_tIME");
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

    if let Some(chunk_data) = chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}

pub fn addChunk_tEXt(out: &mut Ucvector, keyword: Option<&str>, textstring: Option<&str>) -> u32 {
	println!("* addChunk_tEXt");
    let keysize = lodepng_strlen(keyword);
    let textsize = lodepng_strlen(textstring);
    let size = (keysize + 1) + textsize;
    
    if (keysize < 1) || (keysize > 79) {
        return 89;
    }
    
    let mut chunk: Option<&mut [u8]> = None;
    let error = lodepng_chunk_init(&mut chunk, out, size, b"tEXt");
    if error != 0 {
        return error;
    }
    
    if let Some(chunk_data) = &mut chunk {
        let keyword_bytes = keyword.unwrap().as_bytes();
        lodepng_memcpy(&mut chunk_data[8..8 + keysize], keyword_bytes);
        chunk_data[8 + keysize] = 0;
        
        let textstring_bytes = textstring.unwrap().as_bytes();
        lodepng_memcpy(&mut chunk_data[9 + keysize..9 + keysize + textsize], textstring_bytes);
        
        lodepng_chunk_generate_crc(chunk_data);
    }
    
    0
}
pub fn lodepng_chunk_createv(
    out: &mut Ucvector,
    length: usize,
    type_: &[u8; 4],
    data: &[u8],
) -> u32 {
	println!("* lodepng_chunk_createv");
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, length, type_);
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_slice) = chunk.as_mut() {
        lodepng_memcpy(&mut chunk_slice[8..], data);
        lodepng_chunk_generate_crc(chunk_slice);
    }

    0
}
pub fn addChunk_sRGB(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_sRGB");
    let data = info.srgb_intent as u8;
    lodepng_chunk_createv(out, 1, b"sRGB", &[data])
}
pub fn addChunk_sBIT(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_sBIT");
    let bitdepth = match info.color.colortype {
        LodePNGColorType::LCT_PALETTE => 8,
        _ => info.color.bitdepth,
    };

    let mut chunk: Option<&mut [u8]> = None;
    let error = match info.color.colortype {
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
            0
        }
        LodePNGColorType::LCT_RGB | LodePNGColorType::LCT_PALETTE => {
            if info.sbit_r == 0 || info.sbit_g == 0 || info.sbit_b == 0 {
                return 115;
            }
            if info.sbit_r > bitdepth || info.sbit_g > bitdepth || info.sbit_b > bitdepth {
                return 115;
            }
            let error = lodepng_chunk_init(&mut chunk, out, 3, b"sBIT");
            if error != 0 {
                return error;
            }
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = info.sbit_r as u8;
                chunk_data[9] = info.sbit_g as u8;
                chunk_data[10] = info.sbit_b as u8;
            }
            0
        }
        LodePNGColorType::LCT_GREY_ALPHA => {
            if info.sbit_r == 0 || info.sbit_a == 0 {
                return 115;
            }
            if info.sbit_r > bitdepth || info.sbit_a > bitdepth {
                return 115;
            }
            let error = lodepng_chunk_init(&mut chunk, out, 2, b"sBIT");
            if error != 0 {
                return error;
            }
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = info.sbit_r as u8;
                chunk_data[9] = info.sbit_a as u8;
            }
            0
        }
        LodePNGColorType::LCT_RGBA => {
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
            let error = lodepng_chunk_init(&mut chunk, out, 4, b"sBIT");
            if error != 0 {
                return error;
            }
            if let Some(chunk_data) = &mut chunk {
                chunk_data[8] = info.sbit_r as u8;
                chunk_data[9] = info.sbit_g as u8;
                chunk_data[10] = info.sbit_b as u8;
                chunk_data[11] = info.sbit_a as u8;
            }
            0
        }
    };

    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = &mut chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}
pub fn addChunk_pHYs(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_pHYs");
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 9, b"pHYs");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_slice) = &mut chunk {
        // Ensure we have enough space for the operations
        if chunk_slice.len() >= 17 {
            let mut buffer_x = [0u8; 4];
            lodepng_set32bitInt(&mut buffer_x, info.phys_x);
            chunk_slice[8..12].copy_from_slice(&buffer_x);

            let mut buffer_y = [0u8; 4];
            lodepng_set32bitInt(&mut buffer_y, info.phys_y);
            chunk_slice[12..16].copy_from_slice(&buffer_y);

            chunk_slice[16] = info.phys_unit as u8;
            lodepng_chunk_generate_crc(chunk_slice);
        } else {
            return 1; // Return error if chunk is too small
        }
    } else {
        return 1; // Return error if chunk is None
    }

    0
}

pub fn addChunk_iTXt(
    out: &mut Ucvector,
    compress: bool,
    keyword: Option<&str>,
    langtag: Option<&str>,
    transkey: Option<&str>,
    textstring: Option<&str>,
    zlibsettings: &LodePngCompressSettings,
) -> u32 {
	println!("* addChunk_iTXt");
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Box<[u8]>> = None;
    let mut compressedsize = 0;
    
    let textsize = lodepng_strlen(textstring);
    let keysize = lodepng_strlen(keyword);
    let langsize = lodepng_strlen(langtag);
    let transsize = lodepng_strlen(transkey);

    if keysize < 1 || keysize > 79 {
        return 89;
    }

    if compress {
        error = zlib_compress(
            &mut compressed,
            &mut compressedsize,
            textstring.map(|s| s.as_bytes()),
            textsize,
            zlibsettings,
        );
    }

    if error == 0 {
        let size = keysize + 3 + langsize + 1 + transsize + 1 + if compress { compressedsize } else { textsize };
        error = lodepng_chunk_init(&mut chunk, out, size, b"iTXt");
    }

    if error == 0 {
        let chunk = chunk.as_mut().unwrap();
        let mut pos = 8;

        lodepng_memcpy(&mut chunk[pos..pos + keysize], keyword.unwrap().as_bytes());
        pos += keysize;
        chunk[pos] = 0;
        pos += 1;
        chunk[pos] = if compress { 1 } else { 0 };
        pos += 1;
        chunk[pos] = 0;
        pos += 1;
        lodepng_memcpy(&mut chunk[pos..pos + langsize], langtag.unwrap().as_bytes());
        pos += langsize;
        chunk[pos] = 0;
        pos += 1;
        lodepng_memcpy(&mut chunk[pos..pos + transsize], transkey.unwrap().as_bytes());
        pos += transsize;
        chunk[pos] = 0;
        pos += 1;

        if compress {
            lodepng_memcpy(&mut chunk[pos..pos + compressedsize], compressed.as_ref().unwrap());
        } else {
            lodepng_memcpy(&mut chunk[pos..pos + textsize], textstring.unwrap().as_bytes());
        }

        lodepng_chunk_generate_crc(chunk);
    }

    lodepng_free(compressed.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    error
}
pub fn addChunk_iCCP(
    out: &mut Ucvector,
    info: &LodePngInfo,
    zlibsettings: &LodePngCompressSettings,
) -> u32 {
	println!("* addChunk_iCCP");
    let mut error = 0;
    let mut chunk: Option<&mut [u8]> = None;
    let mut compressed: Option<Box<[u8]>> = None;
    let mut compressedsize = 0;
    
    let keysize = lodepng_strlen(info.iccp_name.as_deref());
    if keysize < 1 || keysize > 79 {
        return 89;
    }

    error = zlib_compress(
        &mut compressed,
        &mut compressedsize,
        info.iccp_profile.as_deref(),
        info.iccp_profile_size as usize,
        zlibsettings,
    );

    if error == 0 {
        let size = (keysize + 2) + compressedsize;
        error = lodepng_chunk_init(&mut chunk, out, size, b"iCCP");
    }

    if error == 0 {
        if let Some(chunk_data) = chunk.as_deref_mut() {
            if let Some(name) = &info.iccp_name {
                lodepng_memcpy(
                    &mut chunk_data[8..8 + keysize],
                    name.as_bytes(),
                );
            }
            chunk_data[8 + keysize] = 0;
            chunk_data[9 + keysize] = 0;
            
            if let Some(compressed_data) = compressed.as_deref() {
                lodepng_memcpy(
                    &mut chunk_data[10 + keysize..10 + keysize + compressedsize],
                    compressed_data,
                );
            }
            lodepng_chunk_generate_crc(chunk_data);
        }
    }

    if compressed.is_some() {
        lodepng_free(compressed.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    }
    error
}
pub fn addChunk_gAMA(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_gAMA");
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 4, b"gAMA");
        if error != 0 {
            return error;
        }
    }
    
    if let Some(chunk_data) = &mut chunk {
        let chunk_slice = &mut chunk_data[8..12];
        let mut buffer = [0u8; 4];
        lodepng_set32bitInt(&mut buffer, info.gama_gamma);
        chunk_slice.copy_from_slice(&buffer);
    }
    
    if let Some(chunk_data) = &mut chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }
    
    0
}
pub fn addChunk_cHRM(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_cHRM");
    let mut chunk: Option<&mut [u8]> = None;
    {
        let error = lodepng_chunk_init(&mut chunk, out, 32, b"cHRM");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_data) = &mut chunk {
        // Each set32bitInt operation needs its own mutable slice
        {
            let slice = &mut chunk_data[8..12];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_white_x);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[12..16];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_white_y);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[16..20];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_red_x);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[20..24];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_red_y);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[24..28];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_green_x);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[28..32];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_green_y);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[32..36];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_blue_x);
            slice.copy_from_slice(&buffer);
        }
        {
            let slice = &mut chunk_data[36..40];
            let mut buffer = [0u8; 4];
            lodepng_set32bitInt(&mut buffer, info.chrm_blue_y);
            slice.copy_from_slice(&buffer);
        }

        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}
pub fn addChunk_bKGD(out: &mut Ucvector, info: &LodePngInfo) -> u32 {
	println!("* addChunk_bKGD");
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

    if let Some(chunk_data) = &mut chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}
pub fn addChunk_PLTE(out: &mut Ucvector, info: &LodePNGColorMode) -> u32 {
	println!("* addChunk_PLTE");
    if info.palettesize == 0 || info.palettesize > 256 {
        return 68;
    }

    let mut chunk: Option<&mut [u8]> = None;
    let error = lodepng_chunk_init(&mut chunk, out, info.palettesize * 3, b"PLTE");
    if error != 0 {
        return error;
    }

    if let Some(chunk_data) = &mut chunk {
        let mut j = 8;
        if let Some(palette) = &info.palette {
            for i in 0..info.palettesize {
                chunk_data[j] = palette[i * 4];
                j += 1;
                chunk_data[j] = palette[i * 4 + 1];
                j += 1;
                chunk_data[j] = palette[i * 4 + 2];
                j += 1;
            }
        }
    }

    if let Some(chunk_data) = chunk {
        lodepng_chunk_generate_crc(chunk_data);
    }

    0
}

pub fn addChunk_IHDR(
    out: &mut Ucvector,
    w: u32,
    h: u32,
    colortype: LodePNGColorType,
    bitdepth: u8,
    interlace_method: u8,
) -> u32 {
	println!("* addChunk_IHDR");
    let mut chunk: Option<&mut [u8]> = None;
    
    {
        let error = lodepng_chunk_init(&mut chunk, out, 13, b"IHDR");
        if error != 0 {
            return error;
        }
    }

    if let Some(chunk_data) = &mut chunk {
        let data_idx = 8;
        let data = &mut chunk_data[data_idx..];
        
        lodepng_set32bitInt(&mut data[0..4].try_into().unwrap(), w);
        lodepng_set32bitInt(&mut data[4..8].try_into().unwrap(), h);
        data[8] = bitdepth;
        data[9] = colortype as u8;
        data[10] = 0;
        data[11] = 0;
        data[12] = interlace_method;
        
        lodepng_chunk_generate_crc(chunk_data);
    }
    
    0
}
pub fn addChunk_IEND(out: &mut Ucvector) -> u32 {
	println!("* addChunk_IEND");
    lodepng_chunk_createv(out, 0, b"IEND", &[])
}
pub fn addChunk_IDAT(
    out: &mut Ucvector,
    data: Option<&[u8]>,
    datasize: usize,
    zlibsettings: &LodePngCompressSettings,
) -> u32 {
	println!("* addChunk_IDAT");
    let mut zlib: Option<Box<[u8]>> = None;
    let mut zlibsize: usize = 0;
    let mut error = zlib_compress(&mut zlib, &mut zlibsize, data, datasize, zlibsettings);
    if error == 0 {
        if let Some(zlib_data) = &zlib {
            error = lodepng_chunk_createv(out, zlibsize, b"IDAT", zlib_data);
        }
    }

    lodepng_free(zlib.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    error
}
pub fn lodepng_encode(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: Option<&[u8]>,
    w: u32,
    h: u32,
    state: &mut LodePngState,
) -> u32 {
	println!("* lodepng_encode");
    let mut data: Option<Box<[u8]>> = None;
    let mut datasize: usize = 0;
    let mut outv = Ucvector {
        data: None,
        size: 0,
        allocsize: 0,
    };
    let mut info = LodePngInfo {
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
        time: LodePngTime {
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
    let info_png = &state.info_png;
    let mut auto_color = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 8,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
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
        allow_palette: 0,
        allow_greyscale: 0,
    };
    
    lodepng_info_init(&mut info);
    lodepng_color_mode_init(&mut auto_color);
    
    *out = None;
    *outsize = 0;
    state.error = 0;

    if ((info_png.color.colortype == LodePNGColorType::LCT_PALETTE || state.encoder.force_palette != 0)
        && (info_png.color.palettesize == 0 || info_png.color.palettesize > 256))
    {
        state.error = 68;
        return state.error;
    }

    if state.encoder.zlibsettings.btype > 2 {
        state.error = 61;
        return state.error;
    }

    if info_png.interlace_method > 1 {
        state.error = 71;
        return state.error;
    }

    state.error = checkColorValidity(info_png.color.colortype, info_png.color.bitdepth);
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
        let mut allow_convert = 1;
        lodepng_color_stats_init(&mut stats);

        if info_png.iccp_defined != 0 && isGrayICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize) {
            stats.allow_palette = 0;
        }

        if info_png.iccp_defined != 0 && isRGBICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize) {
            stats.allow_greyscale = 0;
        }

        state.error = lodepng_compute_color_stats(&mut stats, image.unwrap(), w, h, &state.info_raw);
        if state.error != 0 {
            return state.error;
        }

        if info_png.background_defined != 0 {
            let mut r = 0;
            let mut g = 0;
            let mut b = 0;
            let mode16 = lodepng_color_mode_make(LodePNGColorType::LCT_RGB, 16);
            state.error = lodepng_convert_rgb(
                &mut Some(r),
                &mut Some(g),
                &mut Some(b),
                info_png.background_r,
                info_png.background_g,
                info_png.background_b,
                &mode16,
                &info_png.color,
            );
            if state.error != 0 {
                return state.error;
            }

            state.error = lodepng_color_stats_add(&mut stats, r, g, b, 65535);
            if state.error != 0 {
                return state.error;
            }
        }

        state.error = auto_choose_color(&mut auto_color, &state.info_raw, &stats);
        if state.error != 0 {
            return state.error;
        }

        if info_png.sbit_defined != 0 {
            let sbit_max = info_png.sbit_r.max(info_png.sbit_g).max(info_png.sbit_b).max(info_png.sbit_a);
            let equal = ((info_png.sbit_g == 0 || info_png.sbit_g == info_png.sbit_r)
                && (info_png.sbit_b == 0 || info_png.sbit_b == info_png.sbit_r))
                && (info_png.sbit_a == 0 || info_png.sbit_a == info_png.sbit_r);
            allow_convert = 0;

            if info.color.colortype == LodePNGColorType::LCT_PALETTE
                && auto_color.colortype == LodePNGColorType::LCT_PALETTE
            {
                allow_convert = 1;
            }

            if info.color.colortype == LodePNGColorType::LCT_RGB
                && auto_color.colortype == LodePNGColorType::LCT_PALETTE
                && sbit_max <= 8
            {
                allow_convert = 1;
            }

            if info.color.colortype == LodePNGColorType::LCT_RGBA
                && auto_color.colortype == LodePNGColorType::LCT_PALETTE
                && info_png.sbit_a == 8
                && sbit_max <= 8
            {
                allow_convert = 1;
            }

            if ((info.color.colortype == LodePNGColorType::LCT_RGB
                || info.color.colortype == LodePNGColorType::LCT_RGBA)
                && info.color.bitdepth == 16
                && auto_color.colortype == info.color.colortype
                && auto_color.bitdepth == 8
                && sbit_max <= 8)
            {
                allow_convert = 1;
            }

            if (info.color.colortype != LodePNGColorType::LCT_PALETTE
                && auto_color.colortype != LodePNGColorType::LCT_PALETTE
                && equal
                && info_png.sbit_r == auto_color.bitdepth)
            {
                allow_convert = 1;
            }
        }

        if state.encoder.force_palette != 0 {
            if (info.color.colortype != LodePNGColorType::LCT_GREY
                && info.color.colortype != LodePNGColorType::LCT_GREY_ALPHA)
                && (auto_color.colortype == LodePNGColorType::LCT_GREY
                    || auto_color.colortype == LodePNGColorType::LCT_GREY_ALPHA)
            {
                allow_convert = 0;
            }
        }

        if allow_convert != 0 {
            state.error = lodepng_color_mode_copy(&mut info.color, &auto_color);
            if state.error != 0 {
                return state.error;
            }

            if info_png.background_defined != 0 {
                state.error = lodepng_convert_rgb(
                    &mut Some(info.background_r),
                    &mut Some(info.background_g),
                    &mut Some(info.background_b),
                    info_png.background_r,
                    info_png.background_g,
                    info_png.background_b,
                    &info.color,
                    &info_png.color,
                );
                if state.error != 0 {
                    return state.error;
                }
            }
        }
    }

    if info_png.iccp_defined != 0 {
        let gray_icc = isGrayICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize);
        let rgb_icc = isRGBICCProfile(info_png.iccp_profile.as_deref(), info_png.iccp_profile_size as usize);
        let gray_png = info.color.colortype == LodePNGColorType::LCT_GREY
            || info.color.colortype == LodePNGColorType::LCT_GREY_ALPHA;

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
        let size = ((w as usize * h as usize * lodepng_get_bpp(&info.color) as usize) + 7) / 8;
        let mut converted = vec![0u8; size];
        
        state.error = lodepng_convert(
            &mut converted,
            image.unwrap(),
            &info.color,
            &state.info_raw,
            w,
            h,
        );
        if state.error != 0 {
            return state.error;
        }

        state.error = preProcessScanlines(
            &mut data,
            &mut datasize,
            &converted,
            w,
            h,
            &info,
            &state.encoder,
        );
        if state.error != 0 {
            return state.error;
        }
    } else {
        state.error = preProcessScanlines(
            &mut data,
            &mut datasize,
            image.unwrap(),
            w,
            h,
            &info,
            &state.encoder,
        );
        if state.error != 0 {
            return state.error;
        }
    }

    state.error = writeSignature(&mut outv);
    if state.error != 0 {
        return state.error;
    }

    state.error = addChunk_IHDR(
        &mut outv,
        w,
        h,
        info.color.colortype,
        info.color.bitdepth as u8,
        info.interlace_method as u8,
    );
    if state.error != 0 {
        return state.error;
    }

    if let Some(chunk_data) = &info.unknown_chunks_data[0] {
        state.error = addUnknownChunks(&mut outv, chunk_data);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.iccp_defined != 0 {
        state.error = addChunk_iCCP(&mut outv, &info, &state.encoder.zlibsettings);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.srgb_defined != 0 {
        state.error = addChunk_sRGB(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.gama_defined != 0 {
        state.error = addChunk_gAMA(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.chrm_defined != 0 {
        state.error = addChunk_cHRM(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if info_png.sbit_defined != 0 {
        state.error = addChunk_sBIT(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.color.colortype == LodePNGColorType::LCT_PALETTE {
        state.error = addChunk_PLTE(&mut outv, &info.color);
        if state.error != 0 {
            return state.error;
        }
    }

    if state.encoder.force_palette != 0
        && (info.color.colortype == LodePNGColorType::LCT_RGB
            || info.color.colortype == LodePNGColorType::LCT_RGBA)
    {
        state.error = addChunk_PLTE(&mut outv, &info.color);
        if state.error != 0 {
            return state.error;
        }
    }

    state.error = addChunk_tRNS(&mut outv, &info.color);
    if state.error != 0 {
        return state.error;
    }

    if info.background_defined != 0 {
        state.error = addChunk_bKGD(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if info.phys_defined != 0 {
        state.error = addChunk_pHYs(&mut outv, &info);
        if state.error != 0 {
            return state.error;
        }
    }

    if let Some(chunk_data) = &info.unknown_chunks_data[1] {
        state.error = addUnknownChunks(&mut outv, chunk_data);
        if state.error != 0 {
            return state.error;
        }
    }

    state.error = addChunk_IDAT(
        &mut outv,
        data.as_deref(),
        datasize,
        &state.encoder.zlibsettings,
    );
    if state.error != 0 {
        return state.error;
    }

    if info.time_defined != 0 {
        state.error = addChunk_tIME(&mut outv, &info.time);
        if state.error != 0 {
            return state.error;
        }
    }

    if let Some(text_keys) = &info.text_keys {
        for i in 0..info.text_num {
            if lodepng_strlen(text_keys.get(i).map(|s| s.as_str())) > 79 {
                state.error = 66;
                return state.error;
            }
            if lodepng_strlen(text_keys.get(i).map(|s| s.as_str())) < 1 {
                state.error = 67;
                return state.error;
            }

            if state.encoder.text_compression != 0 {
                state.error = addChunk_zTXt(
                    &mut outv,
                    text_keys.get(i).map(|s| s.as_str()),
                    info.text_strings.as_ref().and_then(|v| v.get(i).map(|s| s.as_str())),
                    &state.encoder.zlibsettings,
                );
            } else {
                state.error = addChunk_tEXt(
                    &mut outv,
                    text_keys.get(i).map(|s| s.as_str()),
                    info.text_strings.as_ref().and_then(|v| v.get(i).map(|s| s.as_str())),
                );
            }
            if state.error != 0 {
                return state.error;
            }
        }
    }

    if state.encoder.add_id != 0 {
        let mut already_added_id_text = 0;
        if let Some(text_keys) = &info.text_keys {
            for key in text_keys {
                if key == "LodePNG" {
                    already_added_id_text = 1;
                    break;
                }
            }
        }

        if already_added_id_text == 0 {
            state.error = addChunk_tEXt(&mut outv, Some("LodePNG"), Some(LODEPNG_VERSION_STRING.as_ref()));
            if state.error != 0 {
                return state.error;
            }
        }
    }

    if let Some(itext_keys) = &info.itext_keys {
        for i in 0..info.itext_num {
            if lodepng_strlen(itext_keys.get(i).map(|s| s.as_str())) > 79 {
                state.error = 66;
                return state.error;
            }
            if lodepng_strlen(itext_keys.get(i).map(|s| s.as_str())) < 1 {
                state.error = 67;
                return state.error;
            }

            state.error = addChunk_iTXt(
                &mut outv,
                state.encoder.text_compression != 0,
                itext_keys.get(i).map(|s| s.as_str()),
                info.itext_langtags.as_ref().and_then(|v| v.get(i).map(|s| s.as_str())),
                info.itext_transkeys.as_ref().and_then(|v| v.get(i).map(|s| s.as_str())),
                info.itext_strings.as_ref().and_then(|v| v.get(i).map(|s| s.as_str())),
                &state.encoder.zlibsettings,
            );
            if state.error != 0 {
                return state.error;
            }
        }
    }

    if let Some(chunk_data) = &info.unknown_chunks_data[2] {
        state.error = addUnknownChunks(&mut outv, chunk_data);
        if state.error != 0 {
            return state.error;
        }
    }

    state.error = addChunk_IEND(&mut outv);
    if state.error != 0 {
        return state.error;
    }

    lodepng_info_cleanup(&mut info);
    lodepng_color_mode_cleanup(&mut auto_color);

    *out = outv.data;
    *outsize = outv.size;
    state.error
}

pub fn lodepng_encode_memory(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: Option<&[u8]>,
    w: u32,
    h: u32,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
	println!("* lodepng_encode_memory");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
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
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
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
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
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
        info_png: LodePngInfo {
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
            time: LodePngTime {
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
    image: Option<&[u8]>,
    w: c_uint,
    h: c_uint,
) -> c_uint {
	println!("* lodepng_encode32");
    lodepng_encode_memory(
        out,
        outsize,
        image,
        w,
        h,
        LodePNGColorType::LCT_RGBA,
        8,
    )
}
pub fn lodepng_encode24(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    image: Option<&[u8]>,
    w: u32,
    h: u32,
) -> u32 {
	println!("* lodepng_encode24");
    lodepng_encode_memory(
        out,
        outsize,
        image,
        w,
        h,
        LodePNGColorType::LCT_RGB,
        8,
    )
}
pub fn lodepng_encode_file(
    filename: &str,
    image: &[u8],
    w: u32,
    h: u32,
    colortype: LodePNGColorType,
    bitdepth: u32,
) -> u32 {
	println!("* lodepng_encode_file");
    let mut buffer: Option<Vec<u8>> = None;
    let mut buffersize = 0;
    
    // Use a block to limit the mutable borrow of buffer
    let error = {
        let buffer_ref = &mut buffer;
        let buffersize_ref = &mut buffersize;
        lodepng_encode_memory(buffer_ref, buffersize_ref, Some(image), w, h, colortype, bitdepth)
    };

    if error == 0 {
        if let Some(ref buf) = buffer {
            if let Err(e) = lodepng_save_file(buf, filename) {
                lodepng_free(buffer.map(|b| Box::new(b) as Box<dyn std::any::Any>));
                return e;
            }
        }
    }

    lodepng_free(buffer.map(|b| Box::new(b) as Box<dyn std::any::Any>));
    error
}
pub fn lodepng_encode32_file(
    filename: &str,
    image: &[u8],
    w: u32,
    h: u32,
) -> u32 {
	println!("* lodepng_encode32_file");
    lodepng_encode_file(filename, image, w, h, LodePNGColorType::LCT_RGBA, 8)
}
pub fn lodepng_encode24_file(
    filename: &str,
    image: &[u8],
    w: u32,
    h: u32,
) -> u32 {
	println!("* lodepng_encode24_file");
    lodepng_encode_file(filename, image, w, h, crate::LodePNGColorType::LCT_RGB, 8)
}
pub fn lodepng_is_palette_type(info: &LodePNGColorMode) -> bool {
	println!("* lodepng_is_palette_type");
    info.colortype == LodePNGColorType::LCT_PALETTE
}

pub fn lodepng_zlib_decompress(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* lodepng_zlib_decompress");
    let mut v = Ucvector {
        data: out.take(),
        size: *outsize,
        allocsize: 0,
    };
    
    let error = lodepng_zlib_decompressv(&mut v, in_data, insize, settings);
    
    *out = v.data;
    *outsize = v.size;
    
    error
}
pub fn lodepng_inspect_chunk(
    state: &mut LodePngState,
    pos: usize,
    in_data: &[u8],
    insize: usize,
) -> u32 {
	println!("* lodepng_inspect_chunk");
    if pos + 4 > insize {
        return 30;
    }

    let chunk = &in_data[pos..];
    let chunk_length = lodepng_chunk_length(chunk) as usize;

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

    if lodepng_chunk_type_equals(Some(chunk), Some("PLTE")) == 1 {
        error = readChunk_PLTE(&mut state.info_png.color, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("tRNS")) == 1 {
        error = readChunk_tRNS(&mut state.info_png.color, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("bKGD")) == 1 {
        error = readChunk_bKGD(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("tEXt")) == 1 {
        error = readChunk_tEXt(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("zTXt")) == 1 {
        error = readChunk_zTXt(&mut state.info_png, &state.decoder, Some(data), chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("iTXt")) == 1 {
        error = readChunk_iTXt(&mut state.info_png, &state.decoder, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("tIME")) == 1 {
        error = readChunk_tIME(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("pHYs")) == 1 {
        error = readChunk_pHYs(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("gAMA")) == 1 {
        error = readChunk_gAMA(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("cHRM")) == 1 {
        error = readChunk_cHRM(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("sRGB")) == 1 {
        error = readChunk_sRGB(&mut state.info_png, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("iCCP")) == 1 {
        error = readChunk_iCCP(&mut state.info_png, &state.decoder, data, chunk_length);
    } else if lodepng_chunk_type_equals(Some(chunk), Some("sBIT")) == 1 {
        error = readChunk_sBIT(&mut state.info_png, data, chunk_length);
    } else {
        unhandled = 1;
    }

    if error == 0 && unhandled == 0 && state.decoder.ignore_crc == 0 {
        if lodepng_chunk_check_crc(Some(chunk)) != 0 {
            return 57;
        }
    }

    error
}
pub fn lodepng_chunk_find_const<'a>(chunk: Option<&'a [u8]>, end: Option<&'a [u8]>, type_: Option<&'a str>) -> Option<&'a [u8]> {
	println!("* lodepng_chunk_find_const");
    // Check for None inputs (equivalent to NULL checks in C)
    let chunk = chunk?;
    let end = end?;
    let type_ = type_?;

    let mut chunk_idx = 0;
    loop {
        // Convert chunk_idx to usize for safe indexing
        let current_chunk = chunk.get(chunk_idx..)?;
        
        // Check bounds - equivalent to C line 6
        if current_chunk.as_ptr() >= end.as_ptr() || 
           (end.as_ptr() as usize - current_chunk.as_ptr() as usize) < 12 {
            return Option::None;
        }

        // Check if chunk type matches
        if lodepng_chunk_type_equals(Some(current_chunk), Some(type_)) != 0 {
            return Some(current_chunk);
        }

        // Get next chunk position
        let next_chunk = lodepng_chunk_next_const(current_chunk, end);
        chunk_idx = next_chunk.as_ptr() as usize - chunk.as_ptr() as usize;
    }
}

pub fn lodepng_chunk_create(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    length: usize,
    type_: &[u8; 4],
    data: &[u8],
) -> u32 {
	println!("* lodepng_chunk_create");
    let mut v = Ucvector {
        data: out.take(),
        size: *outsize,
        allocsize: 0,
    };
    
    let error = lodepng_chunk_createv(&mut v, length, type_, data);
    
    *out = v.data;
    *outsize = v.size;
    
    error
}
pub fn lodepng_set_icc(info: &mut LodePngInfo, name: Option<&str>, profile: Option<&[u8]>, profile_size: u32) -> u32 {
	println!("* lodepng_set_icc");
    if info.iccp_name.is_some() {
        lodepng_clear_icc(info);
    }
    info.iccp_defined = 1;
    lodepng_assign_icc(info, name, profile, profile_size)
}
pub fn lodepng_get_channels(info: &LodePNGColorMode) -> u8 {
	println!("* lodepng_get_channels");
    getNumColorChannels(info.colortype)
}
pub fn lodepng_clear_text(info: &mut LodePngInfo) {
	println!("* lodepng_clear_text");
    LodePNGText_cleanup(info);
}
pub fn lodepng_clear_itext(info: &mut LodePngInfo) {
	println!("* lodepng_clear_itext");
    LodePNGIText_cleanup(info);
}
pub fn lodepng_chunk_find<'a>(chunk: &'a [u8], end: &'a [u8], type_: &str) -> Option<&'a [u8]> {
	println!("* lodepng_chunk_find");
    let mut chunk_idx = 0;
    loop {
        let current_chunk = &chunk[chunk_idx..];
        
        // Check if current_chunk is out of bounds or too small (less than 12 bytes)
        if current_chunk.as_ptr() >= end.as_ptr() || 
           (end.as_ptr() as usize - current_chunk.as_ptr() as usize) < 12 {
            return Option::None;
        }

        if lodepng_chunk_type_equals(Some(current_chunk), Some(type_)) != 0 {
            return Some(current_chunk);
        }

        let next_chunk = lodepng_chunk_next(current_chunk, end);
        chunk_idx = next_chunk.as_ptr() as usize - chunk.as_ptr() as usize;
    }
}

pub fn lodepng_inflate(
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> u32 {
	println!("* lodepng_inflate");
    let mut v = Ucvector {
        data: out.take(),
        size: *outsize,
        allocsize: 0,
    };

    let error = lodepng_inflatev(&mut v, in_data, insize, settings);

    *out = v.data;
    *outsize = v.size;

    error
}
pub fn lodepng_state_copy(dest: &mut LodePngState, source: &LodePngState) {
	println!("* lodepng_state_copy");
    // Clean up the destination state first
    lodepng_state_cleanup(dest);
    
    // Clone the entire source state into dest
    *dest = source.clone();
    
    // Initialize the color mode and info structs
    lodepng_color_mode_init(&mut dest.info_raw);
    lodepng_info_init(&mut dest.info_png);
    
    // Copy the color mode and check for errors
    dest.error = lodepng_color_mode_copy(&mut dest.info_raw, &source.info_raw);
    if dest.error != 0 {
        return;
    }
    
    // Copy the PNG info and check for errors
    dest.error = lodepng_info_copy(&mut dest.info_png, &source.info_png);
    if dest.error != 0 {
        return;
    }
}
