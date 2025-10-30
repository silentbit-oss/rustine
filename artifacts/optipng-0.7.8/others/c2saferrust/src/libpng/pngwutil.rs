
















use std::convert::TryInto;

extern "C" {
    
    
    
    #[no_mangle]
    fn memset(_: *mut std::os::raw::c_void, _: std::os::raw::c_int, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
pub use crate::src::libpng::png::png_calculate_crc;
pub use crate::src::libpng::png::png_reset_crc;
pub use crate::src::libpng::png::png_zstream_error;
pub use crate::src::libpng::pngerror::png_app_warning;
pub use crate::src::libpng::pngerror::png_error;
pub use crate::src::libpng::pngerror::png_safecat;
pub use crate::src::libpng::pngerror::png_warning;
pub use crate::src::libpng::pngmem::png_calloc;
pub use crate::src::libpng::pngmem::png_free;
pub use crate::src::libpng::pngmem::png_malloc;
pub use crate::src::libpng::pngwio::png_write_data;
pub use crate::src::libpng::pngwrite::png_write_flush;
pub use crate::src::zlib::deflate::deflate;
pub use crate::src::zlib::deflate::deflateEnd;
pub use crate::src::zlib::deflate::deflateInit2_;
pub use crate::src::zlib::deflate::deflateReset;
pub use crate::src::zlib::deflate::internal_state;
pub type size_t = crate::src::gifread::gifread::size_t;
pub type png_byte = crate::src::libpng::png::png_byte;
pub type png_uint_16 = crate::src::libpng::png::png_uint_16;
pub type png_int_32 = crate::src::libpng::png::png_int_32;
pub type png_uint_32 = crate::src::libpng::png::png_uint_32;
pub type png_size_t = crate::src::libpng::png::png_size_t;
pub type png_alloc_size_t = crate::src::libpng::png::png_alloc_size_t;
pub type png_fixed_point = crate::src::libpng::png::png_fixed_point;
pub type png_voidp = crate::src::libpng::png::png_voidp;
pub type png_bytep = crate::src::libpng::png::png_bytep;
pub type png_const_bytep = crate::src::libpng::png::png_const_bytep;
pub type png_const_uint_16p = crate::src::libpng::pngrutil::png_const_uint_16p;
pub type png_charp = crate::src::libpng::png::png_charp;
pub type png_const_charp = crate::src::libpng::png::png_const_charp;
// #[derive(Copy, Clone)]

pub type png_struct_def = crate::src::libpng::pngerror::png_struct_def;
pub type png_row_infop = crate::src::libpng::png::png_row_infop;
pub type png_row_info = crate::src::libpng::png::png_row_info;
// #[derive(Copy, Clone)]

pub type png_row_info_struct = crate::src::libpng::pngerror::png_row_info_struct;
pub type uInt = crate::src::libpng::png::uInt;
pub type png_unknown_chunk = crate::src::libpng::png::png_unknown_chunk;
// #[derive(Copy, Clone)]

pub type png_unknown_chunk_t = crate::src::libpng::pngerror::png_unknown_chunk_t;
pub type png_write_status_ptr = crate::src::libpng::png::png_write_status_ptr;
pub type png_structp = crate::src::libpng::png::png_structp;
pub type png_struct = crate::src::libpng::png::png_struct;
pub type png_read_status_ptr = crate::src::libpng::png::png_read_status_ptr;
pub type png_color_16 = crate::src::libpng::png::png_color_16;
// #[derive(Copy, Clone)]

pub type png_color_16_struct = crate::src::libpng::pngerror::png_color_16_struct;
pub type png_color_8 = crate::src::libpng::png::png_color_8;
// #[derive(Copy, Clone)]

pub type png_color_8_struct = crate::src::libpng::pngerror::png_color_8_struct;
pub type png_flush_ptr = crate::src::libpng::png::png_flush_ptr;
pub type png_colorp = crate::src::libpng::png::png_colorp;
pub type png_color = crate::src::libpng::png::png_color;
// #[derive(Copy, Clone)]

pub type png_color_struct = crate::src::libpng::pngerror::png_color_struct;
pub type png_compression_bufferp = crate::src::libpng::png::png_compression_bufferp;
// #[derive(Copy, Clone)]

pub type png_compression_buffer = crate::src::libpng::pngerror::png_compression_buffer;
pub type z_stream = crate::src::libpng::png::z_stream;
// #[derive(Copy, Clone)]

pub type z_stream_s = crate::src::libpng::pngerror::z_stream_s;
pub type uLong = crate::src::libpng::png::uLong;
pub type voidpf = crate::src::libpng::png::voidpf;
pub type free_func = crate::src::libpng::png::free_func;
pub type alloc_func = crate::src::libpng::png::alloc_func;
pub type Bytef = crate::src::libpng::png::Bytef;
pub type Byte = crate::src::libpng::png::Byte;
pub type png_rw_ptr = crate::src::libpng::png::png_rw_ptr;
pub type png_error_ptr = crate::src::libpng::png::png_error_ptr;
pub type png_structrp = crate::src::libpng::png::png_structrp;
pub type png_const_structrp = crate::src::libpng::png::png_const_structrp;
pub type png_const_colorp = crate::src::libpng::pngrutil::png_const_colorp;
pub type png_const_color_16p = crate::src::libpng::pngrutil::png_const_color_16p;
pub type png_const_color_8p = crate::src::libpng::pngrutil::png_const_color_8p;
pub type z_streamp = crate::src::libpng::png::z_streamp;
/* pngwutil.c - utilities to write a PNG file
 *
 * Last changed in libpng 1.6.32 [August 24, 2017]
 * Copyright (c) 1998-2002,2004,2006-2017 Glenn Randers-Pehrson
 * (Version 0.96 Copyright (c) 1996, 1997 Andreas Dilger)
 * (Version 0.88 Copyright (c) 1995, 1996 Guy Eric Schalnat, Group 42, Inc.)
 *
 * This code is released under the libpng license.
 * For conditions of distribution and use, see the disclaimer
 * and license in png.h
 */
/* Place a 32-bit number into a buffer in PNG byte order.  We work
 * with unsigned numbers for convenience, although one supported
 * ancillary chunk uses signed (two's complement) numbers.
 */
#[no_mangle]
pub unsafe extern "C" fn png_save_uint_32(mut buf: png_bytep,
                                          mut i: png_uint_32) {
    *buf.offset(0 as std::os::raw::c_int as isize) =
        (i >> 24 as std::os::raw::c_int & 0xff as std::os::raw::c_uint) as png_byte;
    *buf.offset(1 as std::os::raw::c_int as isize) =
        (i >> 16 as std::os::raw::c_int & 0xff as std::os::raw::c_uint) as png_byte;
    *buf.offset(2 as std::os::raw::c_int as isize) =
        (i >> 8 as std::os::raw::c_int & 0xff as std::os::raw::c_uint) as png_byte;
    *buf.offset(3 as std::os::raw::c_int as isize) =
        (i & 0xff as std::os::raw::c_uint) as png_byte;
}
/* Place a 16-bit number into a buffer in PNG byte order.
 * The parameter is declared unsigned int, not png_uint_16,
 * just to avoid potential problems on pre-ANSI C compilers.
 */
#[no_mangle]
pub unsafe extern "C" fn png_save_uint_16(mut buf: png_bytep,
                                          mut i: std::os::raw::c_uint) {
    *buf.offset(0 as std::os::raw::c_int as isize) =
        (i >> 8 as std::os::raw::c_int & 0xff as std::os::raw::c_uint) as png_byte;
    *buf.offset(1 as std::os::raw::c_int as isize) =
        (i & 0xff as std::os::raw::c_uint) as png_byte;
}
/* Simple function to write the signature.  If we have already written
 * the magic bytes of the signature, or more likely, the PNG stream is
 * being embedded into another stream and doesn't need its own signature,
 * we should call png_set_sig_bytes() to tell libpng how many of the
 * bytes have already been written.
 */
#[no_mangle]
pub unsafe extern "C" fn png_write_sig(mut png_ptr: png_structrp) {
    let mut png_signature: [png_byte; 8] =
        [137 as std::os::raw::c_int as png_byte, 80 as std::os::raw::c_int as png_byte,
         78 as std::os::raw::c_int as png_byte, 71 as std::os::raw::c_int as png_byte,
         13 as std::os::raw::c_int as png_byte, 10 as std::os::raw::c_int as png_byte,
         26 as std::os::raw::c_int as png_byte, 10 as std::os::raw::c_int as png_byte];
    /* Inform the I/O callback that the signature is being written */
    (*png_ptr).io_state =
        (0x2 as std::os::raw::c_int | 0x10 as std::os::raw::c_int) as png_uint_32;
    /* Write the rest of the 8 byte signature */
    let png_signature_ptr = png_signature.as_mut_ptr().offset((*png_ptr).sig_bytes as isize);
let png_signature_length = (8 - (*png_ptr).sig_bytes as std::os::raw::c_int) as usize;
let png_signature_slice = std::slice::from_raw_parts_mut(png_signature_ptr as *mut png_byte, png_signature_length);
png_write_data(png_ptr, png_signature_slice, png_signature_length);
    if ((*png_ptr).sig_bytes as std::os::raw::c_int) < 3 as std::os::raw::c_int {
        (*png_ptr).mode |= 0x1000 as std::os::raw::c_uint
    };
}
/* Write the start of a PNG chunk.  The type is the chunk type.
 * The total_length is the sum of the lengths of all the data you will be
 * passing in png_write_chunk_data().
 */
unsafe extern "C" fn png_write_chunk_header(mut png_ptr: png_structrp,
                                            mut chunk_name: png_uint_32,
                                            mut length: png_uint_32) {
    let mut buf: [png_byte; 8] = [0; 8];
    if png_ptr.is_null() { return }
    /* Inform the I/O callback that the chunk header is being written.
    * PNG_IO_CHUNK_HDR requires a single I/O call.
    */
    (*png_ptr).io_state =
        (0x2 as std::os::raw::c_int | 0x20 as std::os::raw::c_int) as png_uint_32;
    /* Write the length and the chunk name */
    png_save_uint_32(buf.as_mut_ptr(), length);
    png_save_uint_32(buf.as_mut_ptr().offset(4 as std::os::raw::c_int as isize),
                     chunk_name);
    let buf_ptr = buf.as_mut_ptr();
let buf_slice = std::slice::from_raw_parts_mut(buf_ptr, 8);
png_write_data(png_ptr, buf_slice, 8);
    /* Put the chunk name into png_ptr->chunk_name */
    (*png_ptr).chunk_name = chunk_name;
    /* Reset the crc and run it over the chunk name */
    png_reset_crc(&mut png_ptr);
    png_calculate_crc(png_ptr,
                      buf.as_mut_ptr().offset(4 as std::os::raw::c_int as isize) as
                          png_const_bytep, 4 as std::os::raw::c_int as png_size_t);
    /* Inform the I/O callback that chunk data will (possibly) be written.
    * PNG_IO_CHUNK_DATA does NOT require a specific number of I/O calls.
    */
    (*png_ptr).io_state =
        (0x2 as std::os::raw::c_int | 0x40 as std::os::raw::c_int) as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk_start(mut png_ptr: png_structrp,
                                               mut chunk_string:
                                                   png_const_bytep,
                                               mut length: png_uint_32) {
    png_write_chunk_header(png_ptr,
                           ((0xff as std::os::raw::c_int &
                                 *chunk_string.offset(0 as std::os::raw::c_int as
                                                          isize) as
                                     std::os::raw::c_int) as png_uint_32) <<
                               24 as std::os::raw::c_int |
                               ((0xff as std::os::raw::c_int &
                                     *chunk_string.offset(1 as std::os::raw::c_int as
                                                              isize) as
                                         std::os::raw::c_int) as png_uint_32) <<
                                   16 as std::os::raw::c_int |
                               ((0xff as std::os::raw::c_int &
                                     *chunk_string.offset(2 as std::os::raw::c_int as
                                                              isize) as
                                         std::os::raw::c_int) as png_uint_32) <<
                                   8 as std::os::raw::c_int |
                               ((0xff as std::os::raw::c_int &
                                     *chunk_string.offset(3 as std::os::raw::c_int as
                                                              isize) as
                                         std::os::raw::c_int) as png_uint_32) <<
                                   0 as std::os::raw::c_int, length);
}
/* Write the data of a PNG chunk started with png_write_chunk_header().
 * Note that multiple calls to this function are allowed, and that the
 * sum of the lengths from these calls *must* add up to the total_length
 * given to png_write_chunk_header().
 */
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk_data(mut png_ptr: png_structrp,
                                              mut data: png_const_bytep,
                                              mut length: png_size_t) {
    /* Write the data, and run the CRC over it */
    if png_ptr.is_null() { return }
    if !data.is_null() && length > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        let length_usize = length as usize;
png_write_data(png_ptr, unsafe { std::slice::from_raw_parts(data, length_usize) }, length_usize);
        /* Update the CRC after writing the data,
       * in case the user I/O routine alters it.
       */
        png_calculate_crc(png_ptr, data, length);
    };
}
/* Finish a chunk started with png_write_chunk_header(). */
#[no_mangle]
pub fn png_write_chunk_end(png_ptr: *mut *mut png_struct_def) {
    let mut buf: [png_byte; 4] = [0; 4];
    if png_ptr.is_null() { return; }
    
    // Inform the I/O callback that the chunk CRC is being written.
    // PNG_IO_CHUNK_CRC requires a single I/O function call.
    unsafe {
        let png_struct = &mut **png_ptr;
        png_struct.io_state = (0x2 | 0x80) as png_uint_32;
        
        // Write the crc in a single operation
        png_save_uint_32(buf.as_mut_ptr(), png_struct.crc);
        png_write_data(png_struct, &buf, 4);
    }
}

/* Write a PNG chunk all at once.  The type is an array of ASCII characters
 * representing the chunk name.  The array must be at least 4 bytes in
 * length, and does not need to be null terminated.  To be safe, pass the
 * pre-defined chunk names here, and if you need a new one, define it
 * where the others are defined.  The length is the length of the data.
 * All the data must be present.  If that is not possible, use the
 * png_write_chunk_start(), png_write_chunk_data(), and png_write_chunk_end()
 * functions instead.
 */
unsafe extern "C" fn png_write_complete_chunk(mut png_ptr: png_structrp,
                                              mut chunk_name: png_uint_32,
                                              mut data: png_const_bytep,
                                              mut length: png_size_t) {
    if png_ptr.is_null() { return }
    /* On 64-bit architectures 'length' may not fit in a png_uint_32. */
    if length > 0x7fffffff as std::os::raw::c_long as png_uint_32 as std::os::raw::c_ulong {
        png_error(png_ptr,
                  b"length exceeds PNG maximum\x00" as *const u8 as
                      *const std::os::raw::c_char);
    }
    png_write_chunk_header(png_ptr, chunk_name, length as png_uint_32);
    png_write_chunk_data(png_ptr, data, length);
    png_write_chunk_end(&mut png_ptr);
}
/* This is the API that calls the internal function above. */
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk(mut png_ptr: png_structrp,
                                         mut chunk_string: png_const_bytep,
                                         mut data: png_const_bytep,
                                         mut length: png_size_t) {
    png_write_complete_chunk(png_ptr,
                             ((0xff as std::os::raw::c_int &
                                   *chunk_string.offset(0 as std::os::raw::c_int as
                                                            isize) as
                                       std::os::raw::c_int) as png_uint_32) <<
                                 24 as std::os::raw::c_int |
                                 ((0xff as std::os::raw::c_int &
                                       *chunk_string.offset(1 as std::os::raw::c_int
                                                                as isize) as
                                           std::os::raw::c_int) as png_uint_32) <<
                                     16 as std::os::raw::c_int |
                                 ((0xff as std::os::raw::c_int &
                                       *chunk_string.offset(2 as std::os::raw::c_int
                                                                as isize) as
                                           std::os::raw::c_int) as png_uint_32) <<
                                     8 as std::os::raw::c_int |
                                 ((0xff as std::os::raw::c_int &
                                       *chunk_string.offset(3 as std::os::raw::c_int
                                                                as isize) as
                                           std::os::raw::c_int) as png_uint_32) <<
                                     0 as std::os::raw::c_int, data, length);
}
/* This is used below to find the size of an image to pass to png_deflate_claim,
 * so it only needs to be accurate if the size is less than 16384 bytes (the
 * point at which a lower LZ window size can be used.)
 */
fn png_image_size(png_ptr: *mut crate::src::libpng::png::png_struct_def) -> png_alloc_size_t {
    /* Only return sizes up to the maximum of a png_uint_32; do this by limiting
    * the width and height used to 15 bits.
    */
    let h: png_uint_32 = unsafe { (*png_ptr).height };
if unsafe { (*png_ptr).rowbytes } < 32768 && h < 32768 {
    if unsafe { (*png_ptr).interlaced } != 0 {
        let w: png_uint_32 = unsafe { (*png_ptr).width };
        let pd: u32 = unsafe { (*png_ptr).pixel_depth as u32 };
        let mut cb_base: png_alloc_size_t = 0;

        for pass in 0..=6 {
            let pw: png_uint_32 = w + (((1 << if pass > 1 { (7 - pass) >> 1 } else { 3 }) - 1 - ((1 & pass) << (3 - (pass + 1) >> 1) & 7)) >> if pass > 1 { (7 - pass) >> 1 } else { 3 });
            if pw > 0 {
                cb_base += if pd >= 8 {
                    (pw as png_size_t * pd as png_size_t) >> 3
                } else {
                    ((pw as png_size_t * pd as png_size_t + 7) >> 3)
                } + 1 * (h as png_alloc_size_t + (((1 << if pass > 2 { (8 - pass) >> 1 } else { 3 }) - 1 - ((1 & !pass) << (3 - (pass >> 1) & 7)) >> if pass > 2 { (8 - pass) >> 1 } else { 3 }) >> if pass > 2 { (8 - pass) >> 1 } else { 3 }) as png_alloc_size_t)
            }
        }
        return cb_base;
    } else {
        return (unsafe { (*png_ptr).rowbytes } + 1) as png_alloc_size_t * h as png_alloc_size_t;
    }
} else {
    return 0xffffffff;
}


}

/* This is the code to hack the first two bytes of the deflate stream (the
    * deflate header) to correct the windowBits value to match the actual data
    * size.  Note that the second argument is the *uncompressed* size but the
    * first argument is the *compressed* data (and it must be deflate
    * compressed.)
    */
fn optimize_cmf(data: &mut [u8], data_size: usize) {
    /* Optimize the CMF field in the zlib stream. The resultant zlib stream is
    * still compliant to the stream specification.
    */
    if data_size <= 16384 {
        /* else windowBits must be 15 */
        let mut z_cmf: u32 = data[0] as u32; /* zlib compression method and flags */
        if z_cmf & 0xf == 8 && z_cmf & 0xf0 <= 0x70 {
            let mut z_cinfo: u32;
            let mut half_z_window_size: u32;
            z_cinfo = z_cmf >> 4;
            half_z_window_size = 1 << (z_cinfo + 7);
            if data_size <= half_z_window_size as usize {
                /* else no change */
                loop {
                    half_z_window_size >>= 1;
                    z_cinfo -= 1;
                    if !(z_cinfo > 0 && data_size <= half_z_window_size as usize) {
                        break;
                    }
                }
                z_cmf = (z_cmf & 0xf) | (z_cinfo << 4);
                data[0] = z_cmf as u8;
                let mut tmp: u32 = (data[1] & 0xe0) as u32;
                tmp += (0x1f - ((z_cmf << 8) + tmp) % 0x1f);
                data[1] = tmp as u8;
            }
        }
    }
}

/* WRITE_OPTIMIZE_CMF */
/* Initialize the compressor for the appropriate type of compression. */
unsafe extern "C" fn png_deflate_claim(mut png_ptr: png_structrp,
                                       mut owner: png_uint_32,
                                       mut data_size: png_alloc_size_t)
 -> std::os::raw::c_int {
    if unsafe { (*png_ptr).zowner } != 0 {
    let mut msg: [std::os::raw::c_char; 64] = [0; 64];
    msg[0] = ((owner >> 24) & 0xff) as std::os::raw::c_char;
    msg[1] = ((owner >> 16) & 0xff) as std::os::raw::c_char;
    msg[2] = ((owner >> 8) & 0xff) as std::os::raw::c_char;
    msg[3] = (owner & 0xff) as std::os::raw::c_char;
    msg[4] = ':' as std::os::raw::c_char;
    msg[5] = ' ' as std::os::raw::c_char;
    msg[6] = ((unsafe { (*png_ptr).zowner } >> 24) & 0xff) as std::os::raw::c_char;
    msg[7] = ((unsafe { (*png_ptr).zowner } >> 16) & 0xff) as std::os::raw::c_char;
    msg[8] = ((unsafe { (*png_ptr).zowner } >> 8) & 0xff) as std::os::raw::c_char;
    msg[9] = (unsafe { (*png_ptr).zowner } & 0xff) as std::os::raw::c_char;

    png_safecat(msg.as_mut_ptr(), std::mem::size_of::<[std::os::raw::c_char; 64]>() as std::os::raw::c_ulong, 10, b" using zstream\x00" as *const u8 as *const std::os::raw::c_char);
    png_warning(png_ptr, msg.as_mut_ptr() as png_const_charp);

    if unsafe { (*png_ptr).zowner } == (73 << 24) | (68 << 16) | (65 << 8) | (84) {
        unsafe { (*png_ptr).zstream.msg = b"in use by IDAT\x00" as *const u8 as *const std::os::raw::c_char; }
        return -2; // zlib return code
    }
    unsafe { (*png_ptr).zowner = 0; }
}

let level = unsafe { (*png_ptr).zlib_level };
let method = unsafe { (*png_ptr).zlib_method };
let mut window_bits = unsafe { (*png_ptr).zlib_window_bits };
let mem_level = unsafe { (*png_ptr).zlib_mem_level };
let mut strategy = 0;
let mut ret = 0;

if owner == (73 << 24) | (68 << 16) | (65 << 8) | (84) {
    if unsafe { (*png_ptr).flags & 0x1 } != 0 {
        strategy = unsafe { (*png_ptr).zlib_strategy };
    } else if unsafe { (*png_ptr).do_filter } != 0x8 {
        strategy = 1;
    } else {
        strategy = 0;
    }
} else {
    strategy = 0;
}

if data_size <= 16384 {
    let mut half_window_size: std::os::raw::c_uint = (1 << (window_bits - 1));
    while data_size.wrapping_add(262) <= half_window_size as u64 {
        half_window_size >>= 1;
        window_bits -= 1;
    }
}

if unsafe { (*png_ptr).flags & 0x2 } != 0 && (unsafe { (*png_ptr).zlib_set_level } != level || unsafe { (*png_ptr).zlib_set_method } != method || unsafe { (*png_ptr).zlib_set_window_bits } != window_bits || unsafe { (*png_ptr).zlib_set_mem_level } != mem_level || unsafe { (*png_ptr).zlib_set_strategy } != strategy) {
    if deflateEnd(&mut unsafe { (*png_ptr).zstream }) != 0 {
        png_warning(png_ptr, b"deflateEnd failed (ignored)\x00" as *const u8 as *const std::os::raw::c_char);
    }
    unsafe { (*png_ptr).flags &= !0x2; }
}

unsafe {
    (*png_ptr).zstream.next_in = std::ptr::null();
    (*png_ptr).zstream.avail_in = 0;
    (*png_ptr).zstream.next_out = std::ptr::null_mut();
    (*png_ptr).zstream.avail_out = 0;
}

if unsafe { (*png_ptr).flags & 0x2 } != 0 {
    ret = deflateReset(&mut unsafe { (*png_ptr).zstream });
} else {
    ret = deflateInit2_(&mut unsafe { (*png_ptr).zstream }, level, method, window_bits, mem_level, strategy, b"1.2.11-optipng\x00" as *const u8 as *const std::os::raw::c_char, std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as std::os::raw::c_int);
    if ret == 0 {
        unsafe { (*png_ptr).flags |= 0x2; }
    }
}

if ret == 0 {
    unsafe { (*png_ptr).zowner = owner; }
} else {
    png_zstream_error(png_ptr, ret);
}
return ret;

}
/* Clean up (or trim) a linked list of compression buffers. */
#[no_mangle]
pub fn png_free_buffer_list(png_ptr: *mut png_struct_def, listp: &mut *mut png_compression_buffer) {
    let mut list = *listp;
    if !list.is_null() {
        *listp = std::ptr::null_mut();
        while !list.is_null() {
            let next = unsafe { (*list).next };
            unsafe { png_free(png_ptr, list as *mut std::ffi::c_void) };
            list = next;
        }
    }
}

/* WRITE_COMPRESSED_TEXT */
/* Write the IHDR chunk, and update the png_struct with the necessary
 * information.  Note that the rest of this code depends upon this
 * information being correct.
 */
#[no_mangle]
pub unsafe extern "C" fn png_write_IHDR(mut png_ptr: png_structrp,
                                        mut width: png_uint_32,
                                        mut height: png_uint_32,
                                        mut bit_depth: std::os::raw::c_int,
                                        mut color_type: std::os::raw::c_int,
                                        mut compression_type: std::os::raw::c_int,
                                        mut filter_type: std::os::raw::c_int,
                                        mut interlace_type: std::os::raw::c_int) {
    let mut buf: [u8; 13] = [0; 13]; // Buffer to store the IHDR info
let mut is_invalid_depth: i32 = 0;

// Check that we have valid input data from the application info
match color_type {
    0 => {
        match bit_depth {
            1 | 2 | 4 | 8 | 16 => {
                unsafe { (*png_ptr).channels = 1 };
            }
            _ => {
                unsafe { png_error(png_ptr, b"Invalid bit depth for grayscale image\x00".as_ptr() as *const i8) };
            }
        }
    }
    2 => {
        is_invalid_depth = (bit_depth != 8) as i32;
        is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16) as i32;
        if is_invalid_depth != 0 {
            unsafe { png_error(png_ptr, b"Invalid bit depth for RGB image\x00".as_ptr() as *const i8) };
        }
        unsafe { (*png_ptr).channels = 3 };
    }
    3 => {
        match bit_depth {
            1 | 2 | 4 | 8 => {
                unsafe { (*png_ptr).channels = 1 };
            }
            _ => {
                unsafe { png_error(png_ptr, b"Invalid bit depth for paletted image\x00".as_ptr() as *const i8) };
            }
        }
    }
    4 => {
        is_invalid_depth = (bit_depth != 8) as i32;
        is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16) as i32;
        if is_invalid_depth != 0 {
            unsafe { png_error(png_ptr, b"Invalid bit depth for grayscale+alpha image\x00".as_ptr() as *const i8) };
        }
        unsafe { (*png_ptr).channels = 2 };
    }
    6 => {
        is_invalid_depth = (bit_depth != 8) as i32;
        is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16) as i32;
        if is_invalid_depth != 0 {
            unsafe { png_error(png_ptr, b"Invalid bit depth for RGBA image\x00".as_ptr() as *const i8) };
        }
        unsafe { (*png_ptr).channels = 4 };
    }
    _ => {
        unsafe { png_error(png_ptr, b"Invalid image color type specified\x00".as_ptr() as *const i8) };
    }
}

if compression_type != 0 {
    unsafe { png_warning(png_ptr, b"Invalid compression type specified\x00".as_ptr() as *const i8) };
    compression_type = 0;
}

// Validate filter type
if filter_type != 0 {
    unsafe { png_warning(png_ptr, b"Invalid filter type specified\x00".as_ptr() as *const i8) };
    filter_type = 0;
}

// Validate interlace type
if interlace_type != 0 && interlace_type != 1 {
    unsafe { png_warning(png_ptr, b"Invalid interlace type specified\x00".as_ptr() as *const i8) };
    interlace_type = 1;
}

// Save the relevant information
unsafe {
    (*png_ptr).bit_depth = bit_depth as u8;
    (*png_ptr).color_type = color_type as u8;
    (*png_ptr).interlaced = interlace_type as u8;
    (*png_ptr).compression_type = compression_type as u8;
    (*png_ptr).width = width;
    (*png_ptr).height = height;
    (*png_ptr).pixel_depth = (bit_depth * (*png_ptr).channels as i32) as u8;

    (*png_ptr).rowbytes = if (*png_ptr).pixel_depth as i32 >= 8 {
        (width as usize).wrapping_mul((*png_ptr).pixel_depth as usize >> 3) as u64
    } else {
        (((width as usize).wrapping_mul((*png_ptr).pixel_depth as usize).wrapping_add(7)) >> 3) as u64
    };

    // Set the user info, so any transformations can modify it
    (*png_ptr).usr_width = (*png_ptr).width;
    (*png_ptr).usr_bit_depth = (*png_ptr).bit_depth;
    (*png_ptr).usr_channels = (*png_ptr).channels;

    // Pack the header information into the buffer
    png_save_uint_32(buf.as_mut_ptr(), width);
    png_save_uint_32(buf.as_mut_ptr().offset(4), height);
    buf[8] = bit_depth as u8;
    buf[9] = color_type as u8;
    buf[10] = compression_type as u8;
    buf[11] = filter_type as u8;
    buf[12] = interlace_type as u8;

    // Write the chunk
    png_write_complete_chunk(
        png_ptr,
        (73 << 24) | (72 << 16) | (68 << 8) | 82,
        buf.as_mut_ptr() as *const u8,
        13,
    );
}

    if unsafe { (*png_ptr).do_filter } == 0 {
    if unsafe { (*png_ptr).color_type } == (2 | 1) || unsafe { (*png_ptr).bit_depth } < 8 {
        unsafe { (*png_ptr).do_filter = 0x8 as png_byte };
    } else {
        unsafe { (*png_ptr).do_filter = (0x8 | 0x10 | 0x20 | 0x40 | 0x80) as png_byte };
    }
}
unsafe { (*png_ptr).mode = 0x1 as png_uint_32 };

    /* not READY_FOR_ZTXT */
}
/* Write the palette.  We are careful not to trust png_color to be in the
 * correct order for PNG, so people can redefine it to any convenient
 * structure.
 */
#[no_mangle]
pub unsafe extern "C" fn png_write_PLTE(mut png_ptr: png_structrp,
                                        mut palette: png_const_colorp,
                                        mut num_pal: png_uint_32) {
    let mut max_palette_length: png_uint_32 = 0;
    let mut i: png_uint_32 = 0;
    let mut pal_ptr: png_const_colorp = 0 as *const png_color;
    let mut buf: [png_byte; 3] = [0; 3];
    max_palette_length =
        if (*png_ptr).color_type as std::os::raw::c_int ==
               2 as std::os::raw::c_int | 1 as std::os::raw::c_int {
            ((1 as std::os::raw::c_int)) << (*png_ptr).bit_depth as std::os::raw::c_int
        } else { 256 as std::os::raw::c_int } as png_uint_32;
    if num_pal == 0 as std::os::raw::c_int as std::os::raw::c_uint ||
           num_pal > max_palette_length {
        if (*png_ptr).color_type as std::os::raw::c_int ==
               2 as std::os::raw::c_int | 1 as std::os::raw::c_int {
            png_error(png_ptr,
                      b"Invalid number of colors in palette\x00" as *const u8
                          as *const std::os::raw::c_char);
        } else {
            png_warning(png_ptr,
                        b"Invalid number of colors in palette\x00" as
                            *const u8 as *const std::os::raw::c_char);
            return
        }
    }
    if (*png_ptr).color_type as std::os::raw::c_int & 2 as std::os::raw::c_int ==
           0 as std::os::raw::c_int {
        png_warning(png_ptr,
                    b"Ignoring request to write a PLTE chunk in grayscale PNG\x00"
                        as *const u8 as *const std::os::raw::c_char);
        return
    }
    (*png_ptr).num_palette = num_pal as png_uint_16;
    png_write_chunk_header(png_ptr,
                           (80 as std::os::raw::c_int as png_uint_32) <<
                               24 as std::os::raw::c_int |
                               (76 as std::os::raw::c_int as png_uint_32) <<
                                   16 as std::os::raw::c_int |
                               (84 as std::os::raw::c_int as png_uint_32) <<
                                   8 as std::os::raw::c_int |
                               (69 as std::os::raw::c_int as png_uint_32) <<
                                   0 as std::os::raw::c_int,
                           num_pal.wrapping_mul(3 as std::os::raw::c_int as
                                                    std::os::raw::c_uint));
    i = 0 as std::os::raw::c_int as png_uint_32;
    pal_ptr = palette;
    while i < num_pal {
        buf[0 as std::os::raw::c_int as usize] = (*pal_ptr).red;
        buf[1 as std::os::raw::c_int as usize] = (*pal_ptr).green;
        buf[2 as std::os::raw::c_int as usize] = (*pal_ptr).blue;
        png_write_chunk_data(png_ptr, buf.as_mut_ptr() as png_const_bytep,
                             3 as std::os::raw::c_int as png_size_t);
        i = i.wrapping_add(1);
        pal_ptr = pal_ptr.offset(1)
    }
    png_write_chunk_end(&mut png_ptr);
    (*png_ptr).mode |= 0x2 as std::os::raw::c_int as std::os::raw::c_uint;
}
/* This is similar to png_text_compress, above, except that it does not require
 * all of the data at once and, instead of buffering the compressed result,
 * writes it as IDAT chunks.  Unlike png_text_compress it *can* png_error out
 * because it calls the write interface.  As a result it does its own error
 * reporting and does not return an error code.  In the event of error it will
 * just call png_error.  The input data length may exceed 32-bits.  The 'flush'
 * parameter is exactly the same as that to deflate, with the following
 * meanings:
 *
 * Z_NO_FLUSH: normal incremental output of compressed data
 * Z_SYNC_FLUSH: do a SYNC_FLUSH, used by png_write_flush
 * Z_FINISH: this is the end of the input, do a Z_FINISH and clean up
 *
 * The routine manages the acquire and release of the png_ptr->zstream by
 * checking and (at the end) clearing png_ptr->zowner; it does some sanity
 * checks on the 'mode' flags while doing this.
 */
#[no_mangle]
pub unsafe extern "C" fn png_compress_IDAT(mut png_ptr: png_structrp,
                                           mut input: png_const_bytep,
                                           mut input_len: png_alloc_size_t,
                                           mut flush: std::os::raw::c_int) {
    if unsafe { (*png_ptr).zowner } != (73u32 << 24) | (68u32 << 16) | (65u32 << 8) | (84u32 << 0) {
    // First time. Ensure we have a temporary buffer for compression and
    // trim the buffer list if it has more than one entry to free memory.
    // If 'WRITE_COMPRESSED_TEXT' is not set the list will never have been
    // created at this point, but the check here is quick and safe.
    if unsafe { (*png_ptr).zbuffer_list }.is_null() {
        let buffer_size = 8 + unsafe { (*png_ptr).zbuffer_size } as usize;
        unsafe {
            let allocated_buffer = png_malloc(png_ptr, buffer_size as u64);
            (*png_ptr).zbuffer_list = allocated_buffer as *mut png_compression_buffer;
            if let Some(ref mut buffer) = (*png_ptr).zbuffer_list.as_mut() {
                (*buffer).next = std::ptr::null_mut();
            }
        }
    } else {
        unsafe {
            png_free_buffer_list(png_ptr, &mut (*(*png_ptr).zbuffer_list).next);
        }
    }
    
    // It is a terminal error if we can't claim the zstream.
    if unsafe { png_deflate_claim(png_ptr, 
        (73u32 << 24) | (68u32 << 16) | (65u32 << 8) | (84u32 << 0),
        png_image_size(png_ptr)) } != 0 {
        unsafe {
            png_error(png_ptr, (*png_ptr).zstream.msg);
        }
    }
    
    // The output state is maintained in png_ptr->zstream, so it must be
    // initialized here after the claim.
    unsafe {
        (*png_ptr).zstream.next_out = (*(*png_ptr).zbuffer_list).output.as_mut_ptr();
        (*png_ptr).zstream.avail_out = (*png_ptr).zbuffer_size;
    }
}

// Now loop reading and writing until all the input is consumed or an error
// terminates the operation. The _out values are maintained across calls to
// this function, but the input must be reset each time.
unsafe {
    (*png_ptr).zstream.next_in = input; // set below
    (*png_ptr).zstream.avail_in = 0;
}

    loop {
    let mut ret: std::os::raw::c_int = 0;
    let mut avail: uInt = -(1 as std::os::raw::c_int) as uInt; // safe because of the check
    if avail as std::os::raw::c_ulong > input_len {
        avail = input_len as uInt;
    }
    
    let png_ptr_ref = unsafe { &mut *png_ptr }; // Dereference the raw pointer
    png_ptr_ref.zstream.avail_in = avail;
    input_len = (input_len as std::os::raw::c_ulong).wrapping_sub(avail as std::os::raw::c_ulong) as png_alloc_size_t;

    ret = deflate(&mut png_ptr_ref.zstream, if input_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong { 0 as std::os::raw::c_int } else { flush });

    input_len = (input_len as std::os::raw::c_ulong).wrapping_add(png_ptr_ref.zstream.avail_in as std::os::raw::c_ulong) as png_alloc_size_t;
    png_ptr_ref.zstream.avail_in = 0 as std::os::raw::c_int as uInt;

    if png_ptr_ref.zstream.avail_out == 0 as std::os::raw::c_int as std::os::raw::c_uint {
        let data: png_bytep = unsafe { (*png_ptr_ref.zbuffer_list).output.as_mut_ptr() };
        let size: uInt = png_ptr_ref.zbuffer_size;

        if png_ptr_ref.mode & 0x4 as std::os::raw::c_uint == 0 as std::os::raw::c_int as std::os::raw::c_uint && png_ptr_ref.compression_type as std::os::raw::c_int == 0 as std::os::raw::c_int {
            optimize_cmf(unsafe { std::slice::from_raw_parts_mut(data, size as usize) }, png_image_size(png_ptr) as usize);
        }

        if size > 0 as std::os::raw::c_int as std::os::raw::c_uint {
            png_write_complete_chunk(png_ptr,
                (73 as std::os::raw::c_int as png_uint_32) << 24 as std::os::raw::c_int |
                (68 as std::os::raw::c_int as png_uint_32) << 16 as std::os::raw::c_int |
                (65 as std::os::raw::c_int as png_uint_32) << 8 as std::os::raw::c_int |
                (84 as std::os::raw::c_int as png_uint_32) << 0 as std::os::raw::c_int,
                data as png_const_bytep,
                size as png_size_t);
        }

        png_ptr_ref.mode |= 0x4 as std::os::raw::c_uint;
        png_ptr_ref.zstream.next_out = data;
        png_ptr_ref.zstream.avail_out = size;

        if ret == 0 as std::os::raw::c_int && flush != 0 as std::os::raw::c_int {
            continue;
        }
    }

    if ret == 0 as std::os::raw::c_int {
        if input_len == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
            if flush == 4 as std::os::raw::c_int {
                png_error(png_ptr, b"Z_OK on Z_FINISH with output space\x00" as *const u8 as *const std::os::raw::c_char);
            }
            return;
        }
    } else if ret == 1 as std::os::raw::c_int && flush == 4 as std::os::raw::c_int {
        let data_0: png_bytep = unsafe { (*png_ptr_ref.zbuffer_list).output.as_mut_ptr() };
        let size_0: uInt = png_ptr_ref.zbuffer_size.wrapping_sub(png_ptr_ref.zstream.avail_out);

        if png_ptr_ref.mode & 0x4 as std::os::raw::c_uint == 0 as std::os::raw::c_int as std::os::raw::c_uint && png_ptr_ref.compression_type as std::os::raw::c_int == 0 as std::os::raw::c_int {
            optimize_cmf(unsafe { std::slice::from_raw_parts_mut(data_0, size_0 as usize) }, png_image_size(png_ptr) as usize);
        }

        if size_0 > 0 as std::os::raw::c_int as std::os::raw::c_uint {
            png_write_complete_chunk(png_ptr,
                (73 as std::os::raw::c_int as png_uint_32) << 24 as std::os::raw::c_int |
                (68 as std::os::raw::c_int as png_uint_32) << 16 as std::os::raw::c_int |
                (65 as std::os::raw::c_int as png_uint_32) << 8 as std::os::raw::c_int |
                (84 as std::os::raw::c_int as png_uint_32) << 0 as std::os::raw::c_int,
                data_0 as png_const_bytep,
                size_0 as png_size_t);
        }

        png_ptr_ref.zstream.avail_out = 0 as std::os::raw::c_int as uInt;
        png_ptr_ref.zstream.next_out = 0 as *mut Bytef;
        png_ptr_ref.mode |= 0x4 as std::os::raw::c_uint | 0x8 as std::os::raw::c_int as std::os::raw::c_uint;
        png_ptr_ref.zowner = 0 as std::os::raw::c_int as png_uint_32;
        return;
    } else {
        png_zstream_error(png_ptr, ret);
        png_error(png_ptr, png_ptr_ref.zstream.msg);
    }
}

}
/* Write an IEND chunk */
#[no_mangle]
pub fn png_write_IEND(png_ptr: *mut *mut png_struct_def) {
    let chunk_type: png_uint_32 = (73u32 << 24) | (69u32 << 16) | (78u32 << 8) | (68u32);
    unsafe {
        png_write_complete_chunk(*png_ptr, chunk_type, std::ptr::null(), 0);
        (**png_ptr).mode |= 0x10;
    }
}

/* Write the sBIT chunk */
#[no_mangle]
pub unsafe extern "C" fn png_write_sBIT(mut png_ptr: png_structrp,
                                        mut sbit: png_const_color_8p,
                                        mut color_type: std::os::raw::c_int) {
    let mut buf: [png_byte; 4] = [0; 4];
    let mut size: png_size_t = 0;
    /* Make sure we don't depend upon the order of PNG_COLOR_8 */
    if color_type & 2 as std::os::raw::c_int != 0 as std::os::raw::c_int {
        let mut maxbits: png_byte = 0;
        maxbits =
            if color_type == 2 as std::os::raw::c_int | 1 as std::os::raw::c_int {
                8 as std::os::raw::c_int
            } else { (*png_ptr).usr_bit_depth as std::os::raw::c_int } as png_byte;
        if (*sbit).red as std::os::raw::c_int == 0 as std::os::raw::c_int ||
               (*sbit).red as std::os::raw::c_int > maxbits as std::os::raw::c_int ||
               (*sbit).green as std::os::raw::c_int == 0 as std::os::raw::c_int ||
               (*sbit).green as std::os::raw::c_int > maxbits as std::os::raw::c_int ||
               (*sbit).blue as std::os::raw::c_int == 0 as std::os::raw::c_int ||
               (*sbit).blue as std::os::raw::c_int > maxbits as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Invalid sBIT depth specified\x00" as *const u8 as
                            *const std::os::raw::c_char);
            return
        }
        buf[0 as std::os::raw::c_int as usize] = (*sbit).red;
        buf[1 as std::os::raw::c_int as usize] = (*sbit).green;
        buf[2 as std::os::raw::c_int as usize] = (*sbit).blue;
        size = 3 as std::os::raw::c_int as png_size_t
    } else {
        if (*sbit).gray as std::os::raw::c_int == 0 as std::os::raw::c_int ||
               (*sbit).gray as std::os::raw::c_int >
                   (*png_ptr).usr_bit_depth as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Invalid sBIT depth specified\x00" as *const u8 as
                            *const std::os::raw::c_char);
            return
        }
        buf[0 as std::os::raw::c_int as usize] = (*sbit).gray;
        size = 1 as std::os::raw::c_int as png_size_t
    }
    if color_type & 4 as std::os::raw::c_int != 0 as std::os::raw::c_int {
        if (*sbit).alpha as std::os::raw::c_int == 0 as std::os::raw::c_int ||
               (*sbit).alpha as std::os::raw::c_int >
                   (*png_ptr).usr_bit_depth as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Invalid sBIT depth specified\x00" as *const u8 as
                            *const std::os::raw::c_char);
            return
        }
        let fresh0 = size;
        size = size.wrapping_add(1);
        buf[fresh0 as usize] = (*sbit).alpha
    }
    png_write_complete_chunk(png_ptr,
                             (115 as std::os::raw::c_int as png_uint_32) <<
                                 24 as std::os::raw::c_int |
                                 (66 as std::os::raw::c_int as png_uint_32) <<
                                     16 as std::os::raw::c_int |
                                 (73 as std::os::raw::c_int as png_uint_32) <<
                                     8 as std::os::raw::c_int |
                                 (84 as std::os::raw::c_int as png_uint_32) <<
                                     0 as std::os::raw::c_int,
                             buf.as_mut_ptr() as png_const_bytep, size);
}
/* Write the tRNS chunk */
#[no_mangle]
pub unsafe extern "C" fn png_write_tRNS(mut png_ptr: png_structrp,
                                        mut trans_alpha: png_const_bytep,
                                        mut tran: png_const_color_16p,
                                        mut num_trans: std::os::raw::c_int,
                                        mut color_type: std::os::raw::c_int) {
    let mut buf: [png_byte; 6] = [0; 6];
    if color_type == 2 as std::os::raw::c_int | 1 as std::os::raw::c_int {
        if num_trans <= 0 as std::os::raw::c_int ||
               num_trans > (*png_ptr).num_palette as std::os::raw::c_int {
            png_app_warning(png_ptr,
                            b"Invalid number of transparent colors specified\x00"
                                as *const u8 as *const std::os::raw::c_char);
            return
        }
        /* Write the chunk out as it is */
        png_write_complete_chunk(png_ptr,
                                 (116 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (82 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (78 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (83 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int, trans_alpha,
                                 num_trans as png_size_t);
    } else if color_type == 0 as std::os::raw::c_int {
        /* One 16-bit value */
        if (*tran).gray as std::os::raw::c_int >=
               (1 as std::os::raw::c_int) << (*png_ptr).bit_depth as std::os::raw::c_int {
            png_app_warning(png_ptr,
                            b"Ignoring attempt to write tRNS chunk out-of-range for bit_depth\x00"
                                as *const u8 as *const std::os::raw::c_char);
            return
        }
        png_save_uint_16(buf.as_mut_ptr(), (*tran).gray as std::os::raw::c_uint);
        png_write_complete_chunk(png_ptr,
                                 (116 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (82 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (78 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (83 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int,
                                 buf.as_mut_ptr() as png_const_bytep,
                                 2 as std::os::raw::c_int as png_size_t);
    } else if color_type == 2 as std::os::raw::c_int {
        /* Three 16-bit values */
        png_save_uint_16(buf.as_mut_ptr(), (*tran).red as std::os::raw::c_uint);
        png_save_uint_16(buf.as_mut_ptr().offset(2 as std::os::raw::c_int as isize),
                         (*tran).green as std::os::raw::c_uint);
        png_save_uint_16(buf.as_mut_ptr().offset(4 as std::os::raw::c_int as isize),
                         (*tran).blue as std::os::raw::c_uint);
        if (*png_ptr).bit_depth as std::os::raw::c_int == 8 as std::os::raw::c_int &&
               buf[0 as std::os::raw::c_int as usize] as std::os::raw::c_int |
                   buf[2 as std::os::raw::c_int as usize] as std::os::raw::c_int |
                   buf[4 as std::os::raw::c_int as usize] as std::os::raw::c_int !=
                   0 as std::os::raw::c_int {
            png_app_warning(png_ptr,
                            b"Ignoring attempt to write 16-bit tRNS chunk when bit_depth is 8\x00"
                                as *const u8 as *const std::os::raw::c_char);
            return
        }
        png_write_complete_chunk(png_ptr,
                                 (116 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (82 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (78 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (83 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int,
                                 buf.as_mut_ptr() as png_const_bytep,
                                 6 as std::os::raw::c_int as png_size_t);
    } else {
        png_app_warning(png_ptr,
                        b"Can\'t write tRNS with an alpha channel\x00" as
                            *const u8 as *const std::os::raw::c_char);
    };
}
/* Write the background chunk */
#[no_mangle]
pub unsafe extern "C" fn png_write_bKGD(mut png_ptr: png_structrp,
                                        mut back: png_const_color_16p,
                                        mut color_type: std::os::raw::c_int) {
    let mut buf: [png_byte; 6] = [0; 6];
    if color_type == 2 as std::os::raw::c_int | 1 as std::os::raw::c_int {
        if (*back).index as std::os::raw::c_int >=
               (*png_ptr).num_palette as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Invalid background palette index\x00" as *const u8
                            as *const std::os::raw::c_char);
            return
        }
        buf[0 as std::os::raw::c_int as usize] = (*back).index;
        png_write_complete_chunk(png_ptr,
                                 (98 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (75 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (71 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (68 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int,
                                 buf.as_mut_ptr() as png_const_bytep,
                                 1 as std::os::raw::c_int as png_size_t);
    } else if color_type & 2 as std::os::raw::c_int != 0 as std::os::raw::c_int {
        png_save_uint_16(buf.as_mut_ptr(), (*back).red as std::os::raw::c_uint);
        png_save_uint_16(buf.as_mut_ptr().offset(2 as std::os::raw::c_int as isize),
                         (*back).green as std::os::raw::c_uint);
        png_save_uint_16(buf.as_mut_ptr().offset(4 as std::os::raw::c_int as isize),
                         (*back).blue as std::os::raw::c_uint);
        if (*png_ptr).bit_depth as std::os::raw::c_int == 8 as std::os::raw::c_int &&
               buf[0 as std::os::raw::c_int as usize] as std::os::raw::c_int |
                   buf[2 as std::os::raw::c_int as usize] as std::os::raw::c_int |
                   buf[4 as std::os::raw::c_int as usize] as std::os::raw::c_int !=
                   0 as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8\x00"
                            as *const u8 as *const std::os::raw::c_char);
            return
        }
        png_write_complete_chunk(png_ptr,
                                 (98 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (75 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (71 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (68 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int,
                                 buf.as_mut_ptr() as png_const_bytep,
                                 6 as std::os::raw::c_int as png_size_t);
    } else {
        if (*back).gray as std::os::raw::c_int >=
               (1 as std::os::raw::c_int) << (*png_ptr).bit_depth as std::os::raw::c_int {
            png_warning(png_ptr,
                        b"Ignoring attempt to write bKGD chunk out-of-range for bit_depth\x00"
                            as *const u8 as *const std::os::raw::c_char);
            return
        }
        png_save_uint_16(buf.as_mut_ptr(), (*back).gray as std::os::raw::c_uint);
        png_write_complete_chunk(png_ptr,
                                 (98 as std::os::raw::c_int as png_uint_32) <<
                                     24 as std::os::raw::c_int |
                                     (75 as std::os::raw::c_int as png_uint_32) <<
                                         16 as std::os::raw::c_int |
                                     (71 as std::os::raw::c_int as png_uint_32) <<
                                         8 as std::os::raw::c_int |
                                     (68 as std::os::raw::c_int as png_uint_32) <<
                                         0 as std::os::raw::c_int,
                                 buf.as_mut_ptr() as png_const_bytep,
                                 2 as std::os::raw::c_int as png_size_t);
    };
}
/* Write the histogram */
#[no_mangle]
pub fn png_write_hIST(png_ptr: *mut *mut png_struct_def, hist: &[u16], num_hist: i32) {
    let num_palette = unsafe { (**png_ptr).num_palette as i32 };
    if num_hist > num_palette {
        unsafe {
            png_warning(*png_ptr, b"Invalid number of histogram entries specified\x00" as *const u8 as *const i8);
        }
        return;
    }

    let chunk_type: u32 = (104 << 24) | (73 << 16) | (83 << 8) | 84;
    unsafe {
        png_write_chunk_header(*png_ptr, chunk_type, (num_hist * 2) as u32);
    }

    for &value in hist.iter().take(num_hist as usize) {
        let mut buf = [0u8; 2];
        unsafe {
            png_save_uint_16(buf.as_mut_ptr(), value as u32);
            png_write_chunk_data(*png_ptr, buf.as_ptr(), 2);
        }
    }

    unsafe {
        png_write_chunk_end(png_ptr);
    }
}

/* Initializes the row writing capability of libpng */
#[no_mangle]
pub unsafe extern "C" fn png_write_start_row(mut png_ptr: png_structrp) {
    /* Arrays to facilitate easy interlacing - use pass (0 - 6) as index */
    /* Start of interlace block */
    static mut png_pass_start: [png_byte; 7] =
        [0 as std::os::raw::c_int as png_byte, 4 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte, 2 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte, 1 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte];
    /* Offset to next interlace block */
    static mut png_pass_inc: [png_byte; 7] =
        [8 as std::os::raw::c_int as png_byte, 8 as std::os::raw::c_int as png_byte,
         4 as std::os::raw::c_int as png_byte, 4 as std::os::raw::c_int as png_byte,
         2 as std::os::raw::c_int as png_byte, 2 as std::os::raw::c_int as png_byte,
         1 as std::os::raw::c_int as png_byte];
    /* Start of interlace block in the y direction */
    static mut png_pass_ystart: [png_byte; 7] =
        [0 as std::os::raw::c_int as png_byte, 0 as std::os::raw::c_int as png_byte,
         4 as std::os::raw::c_int as png_byte, 0 as std::os::raw::c_int as png_byte,
         2 as std::os::raw::c_int as png_byte, 0 as std::os::raw::c_int as png_byte,
         1 as std::os::raw::c_int as png_byte];
    /* Offset to next interlace block in the y direction */
    static mut png_pass_yinc: [png_byte; 7] =
        [8 as std::os::raw::c_int as png_byte, 8 as std::os::raw::c_int as png_byte,
         8 as std::os::raw::c_int as png_byte, 4 as std::os::raw::c_int as png_byte,
         4 as std::os::raw::c_int as png_byte, 2 as std::os::raw::c_int as png_byte,
         2 as std::os::raw::c_int as png_byte];
    let mut buf_size: png_alloc_size_t = 0;
    let mut usr_pixel_depth: std::os::raw::c_int = 0;
    let mut filters: png_byte = 0;
    usr_pixel_depth =
        (*png_ptr).usr_channels as std::os::raw::c_int *
            (*png_ptr).usr_bit_depth as std::os::raw::c_int;
    buf_size =
        (if usr_pixel_depth >= 8 as std::os::raw::c_int {
             ((*png_ptr).width as
                  png_size_t).wrapping_mul(usr_pixel_depth as png_size_t >>
                                               3 as std::os::raw::c_int)
         } else {
             (((*png_ptr).width as
                   png_size_t).wrapping_mul(usr_pixel_depth as
                                                png_size_t).wrapping_add(7 as
                                                                             std::os::raw::c_int
                                                                             as
                                                                             std::os::raw::c_ulong))
                 >> 3 as std::os::raw::c_int
         }).wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
    /* 1.5.6: added to allow checking in the row write code. */
    (*png_ptr).transformed_pixel_depth = (*png_ptr).pixel_depth;
    (*png_ptr).maximum_pixel_depth = usr_pixel_depth as png_byte;
    /* Set up row buffer */
    (*png_ptr).row_buf = png_malloc(png_ptr, buf_size) as *mut png_byte;
    *(*png_ptr).row_buf.offset(0 as std::os::raw::c_int as isize) =
        0 as std::os::raw::c_int as png_byte;
    filters = (*png_ptr).do_filter;
    if (*png_ptr).height == 1 as std::os::raw::c_int as std::os::raw::c_uint {
        filters =
            (filters as std::os::raw::c_int &
                 (0xff as std::os::raw::c_int &
                      !(0x20 as std::os::raw::c_int | 0x40 as std::os::raw::c_int |
                            0x80 as std::os::raw::c_int))) as png_byte
    }
    if (*png_ptr).width == 1 as std::os::raw::c_int as std::os::raw::c_uint {
        filters =
            (filters as std::os::raw::c_int &
                 (0xff as std::os::raw::c_int &
                      !(0x10 as std::os::raw::c_int | 0x40 as std::os::raw::c_int |
                            0x80 as std::os::raw::c_int))) as png_byte
    }
    if filters as std::os::raw::c_int == 0 as std::os::raw::c_int {
        filters = 0x8 as std::os::raw::c_int as png_byte
    }
    (*png_ptr).do_filter = filters;
    if filters as std::os::raw::c_int &
           (0x10 as std::os::raw::c_int | 0x20 as std::os::raw::c_int | 0x40 as std::os::raw::c_int |
                0x80 as std::os::raw::c_int) != 0 as std::os::raw::c_int &&
           (*png_ptr).try_row.is_null() {
        let mut num_filters: std::os::raw::c_int = 0 as std::os::raw::c_int;
        (*png_ptr).try_row = png_malloc(png_ptr, buf_size) as *mut png_byte;
        if filters as std::os::raw::c_int & 0x10 as std::os::raw::c_int != 0 {
            num_filters += 1
        }
        if filters as std::os::raw::c_int & 0x20 as std::os::raw::c_int != 0 {
            num_filters += 1
        }
        if filters as std::os::raw::c_int & 0x40 as std::os::raw::c_int != 0 {
            num_filters += 1
        }
        if filters as std::os::raw::c_int & 0x80 as std::os::raw::c_int != 0 {
            num_filters += 1
        }
        if num_filters > 1 as std::os::raw::c_int {
    (*png_ptr).tst_row = png_malloc(png_ptr, buf_size) as *mut png_byte;
}
    }
    /* We only need to keep the previous row if we are using one of the following
    * filters.
    */
    if filters as std::os::raw::c_int &
           (0x40 as std::os::raw::c_int | 0x20 as std::os::raw::c_int | 0x80 as std::os::raw::c_int)
           != 0 as std::os::raw::c_int {
        (*png_ptr).prev_row = png_calloc(png_ptr, buf_size) as png_bytep
    }
    /* WRITE_FILTER */
    /* If interlaced, we need to set up width and height of pass */
    if (*png_ptr).interlaced as std::os::raw::c_int != 0 as std::os::raw::c_int {
        if (*png_ptr).transformations & 0x2 as std::os::raw::c_uint ==
               0 as std::os::raw::c_int as std::os::raw::c_uint {
            (*png_ptr).num_rows =
                (*png_ptr).height.wrapping_add(png_pass_yinc[0 as std::os::raw::c_int
                                                                 as usize] as
                                                   std::os::raw::c_uint).wrapping_sub(1
                                                                                  as
                                                                                  std::os::raw::c_int
                                                                                  as
                                                                                  std::os::raw::c_uint).wrapping_sub(png_pass_ystart[0
                                                                                                                                 as
                                                                                                                                 std::os::raw::c_int
                                                                                                                                 as
                                                                                                                                 usize]
                                                                                                                 as
                                                                                                                 std::os::raw::c_uint).wrapping_div(png_pass_yinc[0
                                                                                                                                                              as
                                                                                                                                                              std::os::raw::c_int
                                                                                                                                                              as
                                                                                                                                                              usize]
                                                                                                                                                as
                                                                                                                                                std::os::raw::c_uint);
            (*png_ptr).usr_width =
                (*png_ptr).width.wrapping_add(png_pass_inc[0 as std::os::raw::c_int as
                                                               usize] as
                                                  std::os::raw::c_uint).wrapping_sub(1
                                                                                 as
                                                                                 std::os::raw::c_int
                                                                                 as
                                                                                 std::os::raw::c_uint).wrapping_sub(png_pass_start[0
                                                                                                                               as
                                                                                                                               std::os::raw::c_int
                                                                                                                               as
                                                                                                                               usize]
                                                                                                                as
                                                                                                                std::os::raw::c_uint).wrapping_div(png_pass_inc[0
                                                                                                                                                            as
                                                                                                                                                            std::os::raw::c_int
                                                                                                                                                            as
                                                                                                                                                            usize]
                                                                                                                                               as
                                                                                                                                               std::os::raw::c_uint)
        } else {
            (*png_ptr).num_rows = (*png_ptr).height;
            (*png_ptr).usr_width = (*png_ptr).width
        }
    } else {
        (*png_ptr).num_rows = (*png_ptr).height;
        (*png_ptr).usr_width = (*png_ptr).width
    };
}
/* Internal use only.  Called when finished processing a row of data. */
#[no_mangle]
pub fn png_write_finish_row(png_ptr: &mut *mut png_struct_def) {
    static png_pass_start: [u8; 7] = [
        0, 4, 0, 2, 0, 1, 0,
    ];
    static png_pass_inc: [u8; 7] = [
        8, 8, 4, 4, 2, 2, 1,
    ];
    static png_pass_ystart: [u8; 7] = [
        0, 0, 4, 0, 2, 0, 1,
    ];
    static png_pass_yinc: [u8; 7] = [
        8, 8, 8, 4, 4, 2, 2,
    ];

    let png_ptr = unsafe { &mut **png_ptr };
    png_ptr.row_number += 1;

    if png_ptr.row_number < png_ptr.num_rows {
        return;
    }

    if png_ptr.interlaced != 0 {
        png_ptr.row_number = 0;
        if png_ptr.transformations & 0x2 != 0 {
            png_ptr.pass += 1;
        } else {
            loop {
                png_ptr.pass += 1;
                if png_ptr.pass >= 7 {
                    break;
                }
                png_ptr.usr_width = (png_ptr.width as u32 + png_pass_inc[png_ptr.pass as usize] as u32 - 1
                    - png_pass_start[png_ptr.pass as usize] as u32) / png_pass_inc[png_ptr.pass as usize] as u32;
                png_ptr.num_rows = (png_ptr.height as u32 + png_pass_yinc[png_ptr.pass as usize] as u32 - 1
                    - png_pass_ystart[png_ptr.pass as usize] as u32) / png_pass_yinc[png_ptr.pass as usize] as u32;

                if png_ptr.transformations & 0x2 != 0 {
                    break;
                }
                if png_ptr.usr_width != 0 && png_ptr.num_rows != 0 {
                    break;
                }
            }
        }

        if png_ptr.pass < 7 {
            if !png_ptr.prev_row.is_null() {
                let prev_row = unsafe { std::slice::from_raw_parts_mut(png_ptr.prev_row, png_ptr.width as usize) };
                for byte in prev_row.iter_mut() {
                    *byte = 0;
                }
            }
            return;
        }
    }

    unsafe {
        png_compress_IDAT(png_ptr, std::ptr::null(), 0, 4);
    }
}

/* Pick out the correct pixels for the interlace pass.
 * The basic idea here is to go through the row with a source
 * pointer and a destination pointer (sp and dp), and copy the
 * correct pixels for the pass.  As the row gets compacted,
 * sp will always be >= dp, so we should never overwrite anything.
 * See the default: case for the easiest code to understand.
 */
#[no_mangle]
pub unsafe extern "C" fn png_do_write_interlace(mut row_info: png_row_infop,
                                                mut row: png_bytep,
                                                mut pass: std::os::raw::c_int) {
    /* Arrays to facilitate easy interlacing - use pass (0 - 6) as index */
    /* Start of interlace block */
    static mut png_pass_start: [png_byte; 7] =
        [0 as std::os::raw::c_int as png_byte, 4 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte, 2 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte, 1 as std::os::raw::c_int as png_byte,
         0 as std::os::raw::c_int as png_byte];
    /* Offset to next interlace block */
    static mut png_pass_inc: [png_byte; 7] =
        [8 as std::os::raw::c_int as png_byte, 8 as std::os::raw::c_int as png_byte,
         4 as std::os::raw::c_int as png_byte, 4 as std::os::raw::c_int as png_byte,
         2 as std::os::raw::c_int as png_byte, 2 as std::os::raw::c_int as png_byte,
         1 as std::os::raw::c_int as png_byte];
    /* We don't have to do anything on the last pass (6) */
    if pass < 6 as std::os::raw::c_int {
        /* Each pixel depth is handled separately */
        /*
The variables live at this point are:
(mut row_info: &mut src::libpng::png::png_row_info_struct, mut row: &mut u8, mut pass: i32)
*/
match unsafe { (*row_info).pixel_depth } {
    1 => {
         let mut sp: png_bytep = 0 as *mut png_byte;
                let mut dp: png_bytep = 0 as *mut png_byte;
                let mut shift: std::os::raw::c_uint = 0;
                let mut d: std::os::raw::c_int = 0;
                let mut value: std::os::raw::c_int = 0;
                let mut i: png_uint_32 = 0;
                let mut row_width: png_uint_32 = (*row_info).width;
                dp = row;
                d = 0 as std::os::raw::c_int;
                shift = 7 as std::os::raw::c_int as std::os::raw::c_uint;
                i = png_pass_start[pass as usize] as png_uint_32;
                while i < row_width {
                    sp =
                        row.offset((i >> 3 as std::os::raw::c_int) as png_size_t as
                                       isize);
                    value =
                        *sp as std::os::raw::c_int >>
                            7 as std::os::raw::c_int -
                                (i & 0x7 as std::os::raw::c_int as std::os::raw::c_uint) as
                                    std::os::raw::c_int & 0x1 as std::os::raw::c_int;
                    d |= value << shift;
                    if shift == 0 as std::os::raw::c_int as std::os::raw::c_uint {
                        shift = 7 as std::os::raw::c_int as std::os::raw::c_uint;
                        let fresh1 = dp;
                        dp = dp.offset(1);
                        *fresh1 = d as png_byte;
                        d = 0 as std::os::raw::c_int
                    } else { shift = shift.wrapping_sub(1) }
                    i =
                        (i as
                             std::os::raw::c_uint).wrapping_add(png_pass_inc[pass as
                                                                         usize]
                                                            as std::os::raw::c_uint)
                            as png_uint_32 as png_uint_32
                }
                if shift != 7 as std::os::raw::c_int as std::os::raw::c_uint {
                    *dp = d as png_byte
                }
            
    }
    2 => {
         let mut sp_0: *const u8;
let mut dp_0: *mut u8 = row;
let mut shift_0: u32 = 6;
let mut d_0: i32 = 0;
let mut value_0: i32 = 0;
let mut i_0: u32 = png_pass_start[pass as usize] as u32;
let row_width_0: u32 = (*row_info).width;

while i_0 < row_width_0 {
    sp_0 = row.offset((i_0 >> 2) as isize);
    value_0 = (*sp_0 as i32 >> ((3 - (i_0 & 0x3)) << 1)) & 0x3;
    d_0 |= value_0 << shift_0;

    if shift_0 == 0 {
        shift_0 = 6;
        let fresh2 = dp_0;
        dp_0 = dp_0.offset(1);
        *fresh2 = d_0 as u8;
        d_0 = 0;
    } else {
        shift_0 = shift_0.wrapping_sub(2);
    }

    i_0 = i_0.wrapping_add(png_pass_inc[pass as usize] as u32);
}

if shift_0 != 6 {
    *dp_0 = d_0 as u8;
}

            
    }
    4 => {
         let mut sp_1: png_bytep = 0 as *mut png_byte;
                let mut dp_1: png_bytep = 0 as *mut png_byte;
                let mut shift_1: std::os::raw::c_uint = 0;
                let mut d_1: std::os::raw::c_int = 0;
                let mut value_1: std::os::raw::c_int = 0;
                let mut i_1: png_uint_32 = 0;
                let mut row_width_1: png_uint_32 = (*row_info).width;
                dp_1 = row;
                shift_1 = 4 as std::os::raw::c_int as std::os::raw::c_uint;
                d_1 = 0 as std::os::raw::c_int;
                i_1 = png_pass_start[pass as usize] as png_uint_32;
                while i_1 < row_width_1 {
                    sp_1 =
                        row.offset((i_1 >> 1 as std::os::raw::c_int) as png_size_t as
                                       isize);
                    value_1 =
                        *sp_1 as std::os::raw::c_int >>
                            ((1 as std::os::raw::c_int -
                                  (i_1 & 0x1 as std::os::raw::c_int as std::os::raw::c_uint)
                                      as std::os::raw::c_int) << 2 as std::os::raw::c_int) &
                            0xf as std::os::raw::c_int;
                    d_1 |= value_1 << shift_1;
                    if shift_1 == 0 as std::os::raw::c_int as std::os::raw::c_uint {
                        shift_1 = 4 as std::os::raw::c_int as std::os::raw::c_uint;
                        let fresh3 = dp_1;
                        dp_1 = dp_1.offset(1);
                        *fresh3 = d_1 as png_byte;
                        d_1 = 0 as std::os::raw::c_int
                    } else {
                        shift_1 =
                            shift_1.wrapping_sub(4 as std::os::raw::c_int as
                                                     std::os::raw::c_uint)
                    }
                    i_1 =
                        (i_1 as
                             std::os::raw::c_uint).wrapping_add(png_pass_inc[pass as
                                                                         usize]
                                                            as std::os::raw::c_uint)
                            as png_uint_32 as png_uint_32
                }
                if shift_1 != 4 as std::os::raw::c_int as std::os::raw::c_uint {
                    *dp_1 = d_1 as png_byte
                }
            
    }
    _ => {
         let mut sp_2: png_bytep = 0 as *mut png_byte;
                let mut dp_2: png_bytep = 0 as *mut png_byte;
                let mut i_2: png_uint_32 = 0;
                let mut row_width_2: png_uint_32 = (*row_info).width;
                let mut pixel_bytes: png_size_t = 0;
                /* Start at the beginning */
                dp_2 = row;
                /* Find out how many bytes each pixel takes up */
                pixel_bytes =
                    ((*row_info).pixel_depth as std::os::raw::c_int >>
                         3 as std::os::raw::c_int) as png_size_t;
                /* Loop through the row, only looking at the pixels that matter */
                i_2 = png_pass_start[pass as usize] as png_uint_32;
                while i_2 < row_width_2 {
                    /* Find out where the original pixel is */
                    sp_2 =
                        row.offset((i_2 as
                                        png_size_t).wrapping_mul(pixel_bytes)
                                       as isize);
                    /* Move the pixel */
                    if dp_2 != sp_2 {
                        memcpy(dp_2 as *mut std::os::raw::c_void,
                               sp_2 as *const std::os::raw::c_void, pixel_bytes);
                    }
                    /* Next pixel */
                    dp_2 = dp_2.offset(pixel_bytes as isize);
                    i_2 =
                        (i_2 as
                             std::os::raw::c_uint).wrapping_add(png_pass_inc[pass as
                                                                         usize]
                                                            as std::os::raw::c_uint)
                            as png_uint_32 as png_uint_32
                }
            
    }
}

/* Set new row width */
unsafe {
    (*row_info).width = (*row_info).width.wrapping_add(png_pass_inc[pass as usize] as u32)
        .wrapping_sub(1)
        .wrapping_sub(png_pass_start[pass as usize] as u32)
        .wrapping_div(png_pass_inc[pass as usize] as u32);

    (*row_info).rowbytes = if (*row_info).pixel_depth >= 8 {
        ((*row_info).width as u64).wrapping_mul((*row_info).pixel_depth as u64 >> 3)
    } else {
        (((*row_info).width as u64).wrapping_mul((*row_info).pixel_depth as u64).wrapping_add(7)) >> 3
    }
}
/*
The variables live at this point are:
(mut row_info: &mut src::libpng::png::png_row_info_struct, mut row: &mut u8, mut pass: i32)
*/

    };
}
unsafe extern "C" fn png_setup_sub_row(mut png_ptr: png_structrp,
                                       bpp: png_uint_32,
                                       row_bytes: png_size_t,
                                       lmins: png_size_t) -> png_size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_size_t = 0;
    let mut sum: png_size_t = 0 as std::os::raw::c_int as png_size_t;
    let mut v: std::os::raw::c_uint = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_size_t;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp as std::os::raw::c_ulong {
        *dp = *rp;
        v = *dp as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        i = i.wrapping_add(1);
        rp = rp.offset(1);
        dp = dp.offset(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    while i < row_bytes {
        *dp =
            (*rp as std::os::raw::c_int - *lp as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                png_byte;
        v = *dp as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        if sum > lmins { break ; }
        i = i.wrapping_add(1);
        rp = rp.offset(1);
        lp = lp.offset(1);
        dp = dp.offset(1)
    }
    return sum;
}
unsafe extern "C" fn png_setup_sub_row_only(mut png_ptr: png_structrp,
                                            bpp: png_uint_32,
                                            row_bytes: png_size_t) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_size_t = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_size_t;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp as std::os::raw::c_ulong {
        *dp = *rp;
        i = i.wrapping_add(1);
        rp = rp.offset(1);
        dp = dp.offset(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    while i < row_bytes {
        *dp =
            (*rp as std::os::raw::c_int - *lp as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                png_byte;
        i = i.wrapping_add(1);
        rp = rp.offset(1);
        lp = lp.offset(1);
        dp = dp.offset(1)
    };
}
unsafe extern "C" fn png_setup_up_row(mut png_ptr: png_structrp,
                                      row_bytes: png_size_t,
                                      lmins: png_size_t) -> png_size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut i: png_size_t = 0;
    let mut sum: png_size_t = 0 as std::os::raw::c_int as png_size_t;
    let mut v: std::os::raw::c_uint = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        2 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_size_t;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    pp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < row_bytes {
        *dp =
            (*rp as std::os::raw::c_int - *pp as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                png_byte;
        v = *dp as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        if sum > lmins { break ; }
        i = i.wrapping_add(1);
        rp = rp.offset(1);
        pp = pp.offset(1);
        dp = dp.offset(1)
    }
    return sum;
}
fn png_setup_up_row_only(png_ptr: *mut png_structrp, row_bytes: png_size_t) {
    let png_ptr = unsafe { &mut **png_ptr };
    let row_bytes_usize: usize = row_bytes.try_into().unwrap();

    let row_buf = unsafe { std::slice::from_raw_parts_mut((*png_ptr).row_buf, row_bytes_usize) };
    let try_row = unsafe { std::slice::from_raw_parts_mut((*png_ptr).try_row, row_bytes_usize) };
    let prev_row = unsafe { std::slice::from_raw_parts_mut((*png_ptr).prev_row, row_bytes_usize) };

    try_row[0] = 2;

    for i in 0..row_bytes_usize {
        try_row[i] = (row_buf[i] as i32 - prev_row[i] as i32 & 0xff) as png_byte;
    }
}

unsafe extern "C" fn png_setup_avg_row(mut png_ptr: png_structrp,
                                       bpp: png_uint_32,
                                       row_bytes: png_size_t,
                                       lmins: png_size_t) -> png_size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_uint_32 = 0;
    let mut sum: png_size_t = 0 as std::os::raw::c_int as png_size_t;
    let mut v: std::os::raw::c_uint = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        3 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_uint_32;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    pp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp {
        let fresh4 = rp;
        rp = rp.offset(1);
        let fresh5 = pp;
        pp = pp.offset(1);
        let fresh6 = dp;
        dp = dp.offset(1);
        *fresh6 =
            (*fresh4 as std::os::raw::c_int -
                 *fresh5 as std::os::raw::c_int / 2 as std::os::raw::c_int &
                 0xff as std::os::raw::c_int) as png_byte;
        v = *fresh6 as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        i = i.wrapping_add(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    while (i as std::os::raw::c_ulong) < row_bytes {
        let fresh7 = rp;
        rp = rp.offset(1);
        let fresh8 = pp;
        pp = pp.offset(1);
        let fresh9 = lp;
        lp = lp.offset(1);
        let fresh10 = dp;
        dp = dp.offset(1);
        *fresh10 =
            (*fresh7 as std::os::raw::c_int -
                 (*fresh8 as std::os::raw::c_int + *fresh9 as std::os::raw::c_int) /
                     2 as std::os::raw::c_int & 0xff as std::os::raw::c_int) as png_byte;
        v = *fresh10 as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        if sum > lmins { break ; }
        i = i.wrapping_add(1)
    }
    return sum;
}
unsafe extern "C" fn png_setup_avg_row_only(mut png_ptr: png_structrp,
                                            bpp: png_uint_32,
                                            row_bytes: png_size_t) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_uint_32 = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        3 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_uint_32;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    pp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp {
        let fresh11 = rp;
        rp = rp.offset(1);
        let fresh12 = pp;
        pp = pp.offset(1);
        let fresh13 = dp;
        dp = dp.offset(1);
        *fresh13 =
            (*fresh11 as std::os::raw::c_int -
                 *fresh12 as std::os::raw::c_int / 2 as std::os::raw::c_int &
                 0xff as std::os::raw::c_int) as png_byte;
        i = i.wrapping_add(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    while (i as std::os::raw::c_ulong) < row_bytes {
        let fresh14 = rp;
        rp = rp.offset(1);
        let fresh15 = pp;
        pp = pp.offset(1);
        let fresh16 = lp;
        lp = lp.offset(1);
        let fresh17 = dp;
        dp = dp.offset(1);
        *fresh17 =
            (*fresh14 as std::os::raw::c_int -
                 (*fresh15 as std::os::raw::c_int + *fresh16 as std::os::raw::c_int) /
                     2 as std::os::raw::c_int & 0xff as std::os::raw::c_int) as png_byte;
        i = i.wrapping_add(1)
    };
}
unsafe extern "C" fn png_setup_paeth_row(mut png_ptr: png_structrp,
                                         bpp: png_uint_32,
                                         row_bytes: png_size_t,
                                         lmins: png_size_t) -> png_size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut cp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_size_t = 0;
    let mut sum: png_size_t = 0 as std::os::raw::c_int as png_size_t;
    let mut v: std::os::raw::c_uint = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        4 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_size_t;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    pp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp as std::os::raw::c_ulong {
        let fresh18 = rp;
        rp = rp.offset(1);
        let fresh19 = pp;
        pp = pp.offset(1);
        let fresh20 = dp;
        dp = dp.offset(1);
        *fresh20 =
            (*fresh18 as std::os::raw::c_int - *fresh19 as std::os::raw::c_int &
                 0xff as std::os::raw::c_int) as png_byte;
        v = *fresh20 as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        i = i.wrapping_add(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    cp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < row_bytes {
        let mut a: std::os::raw::c_int = 0;
        let mut b: std::os::raw::c_int = 0;
        let mut c: std::os::raw::c_int = 0;
        let mut pa: std::os::raw::c_int = 0;
        let mut pb: std::os::raw::c_int = 0;
        let mut pc: std::os::raw::c_int = 0;
        let mut p: std::os::raw::c_int = 0;
        let fresh21 = pp;
        pp = pp.offset(1);
        b = *fresh21 as std::os::raw::c_int;
        let fresh22 = cp;
        cp = cp.offset(1);
        c = *fresh22 as std::os::raw::c_int;
        let fresh23 = lp;
        lp = lp.offset(1);
        a = *fresh23 as std::os::raw::c_int;
        p = b - c;
        pc = a - c;
        pa = if p < 0 as std::os::raw::c_int { -p } else { p };
        pb = if pc < 0 as std::os::raw::c_int { -pc } else { pc };
        pc = if p + pc < 0 as std::os::raw::c_int { -(p + pc) } else { (p) + pc };
        p = if pa <= pb && pa <= pc { a } else if pb <= pc { b } else { c };
        let fresh24 = rp;
        rp = rp.offset(1);
        let fresh25 = dp;
        dp = dp.offset(1);
        *fresh25 =
            (*fresh24 as std::os::raw::c_int - p & 0xff as std::os::raw::c_int) as png_byte;
        v = *fresh25 as std::os::raw::c_uint;
        sum =
            (sum as
                 std::os::raw::c_ulong).wrapping_add(if v <
                                                    128 as std::os::raw::c_int as
                                                        std::os::raw::c_uint {
                                                 v
                                             } else {
                                                 (256 as std::os::raw::c_int as
                                                      std::os::raw::c_uint).wrapping_sub(v)
                                             } as std::os::raw::c_ulong) as png_size_t
                as png_size_t;
        if sum > lmins { break ; }
        i = i.wrapping_add(1)
    }
    return sum;
}
unsafe extern "C" fn png_setup_paeth_row_only(mut png_ptr: png_structrp,
                                              bpp: png_uint_32,
                                              row_bytes: png_size_t) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut cp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_size_t = 0;
    *(*png_ptr).try_row.offset(0 as std::os::raw::c_int as isize) =
        4 as std::os::raw::c_int as png_byte;
    i = 0 as std::os::raw::c_int as png_size_t;
    rp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    dp = (*png_ptr).try_row.offset(1 as std::os::raw::c_int as isize);
    pp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < bpp as std::os::raw::c_ulong {
        let fresh26 = rp;
        rp = rp.offset(1);
        let fresh27 = pp;
        pp = pp.offset(1);
        let fresh28 = dp;
        dp = dp.offset(1);
        *fresh28 =
            (*fresh26 as std::os::raw::c_int - *fresh27 as std::os::raw::c_int &
                 0xff as std::os::raw::c_int) as png_byte;
        i = i.wrapping_add(1)
    }
    lp = (*png_ptr).row_buf.offset(1 as std::os::raw::c_int as isize);
    cp = (*png_ptr).prev_row.offset(1 as std::os::raw::c_int as isize);
    while i < row_bytes {
        let mut a: std::os::raw::c_int = 0;
        let mut b: std::os::raw::c_int = 0;
        let mut c: std::os::raw::c_int = 0;
        let mut pa: std::os::raw::c_int = 0;
        let mut pb: std::os::raw::c_int = 0;
        let mut pc: std::os::raw::c_int = 0;
        let mut p: std::os::raw::c_int = 0;
        let fresh29 = pp;
        pp = pp.offset(1);
        b = *fresh29 as std::os::raw::c_int;
        let fresh30 = cp;
        cp = cp.offset(1);
        c = *fresh30 as std::os::raw::c_int;
        let fresh31 = lp;
        lp = lp.offset(1);
        a = *fresh31 as std::os::raw::c_int;
        p = b - c;
        pc = a - c;
        pa = if p < 0 as std::os::raw::c_int { -p } else { p };
        pb = if pc < 0 as std::os::raw::c_int { -pc } else { pc };
        pc = if p + pc < 0 as std::os::raw::c_int { -(p + pc) } else { (p) + pc };
        p = if pa <= pb && pa <= pc { a } else if pb <= pc { b } else { c };
        let fresh32 = rp;
        rp = rp.offset(1);
        let fresh33 = dp;
        dp = dp.offset(1);
        *fresh33 =
            (*fresh32 as std::os::raw::c_int - p & 0xff as std::os::raw::c_int) as png_byte;
        i = i.wrapping_add(1)
    };
}
/* WRITE_FILTER */
#[no_mangle]
pub unsafe extern "C" fn png_write_find_filter(mut png_ptr: png_structrp,
                                               mut row_info: png_row_infop) {
    let mut filter_to_do: std::os::raw::c_uint = (*png_ptr).do_filter as std::os::raw::c_uint;
    let mut row_buf: png_bytep = 0 as *mut png_byte;
    let mut best_row: png_bytep = 0 as *mut png_byte;
    let mut bpp: png_uint_32 = 0;
    let mut mins: png_size_t = 0;
    let mut row_bytes: png_size_t = (*row_info).rowbytes;
    /* Find out how many bytes offset each pixel is */
    bpp =
        ((*row_info).pixel_depth as std::os::raw::c_int + 7 as std::os::raw::c_int >>
             3 as std::os::raw::c_int) as
            png_uint_32; /* so we can detect potential overflow of the
                               running sum */
    row_buf = (*png_ptr).row_buf;
    mins =
        (-(1 as std::os::raw::c_int) as
             png_size_t).wrapping_sub(256 as std::os::raw::c_int as std::os::raw::c_ulong);
    /* The prediction method we use is to find which method provides the
    * smallest value when summing the absolute values of the distances
    * from zero, using anything >= 128 as negative numbers.  This is known
    * as the "minimum sum of absolute differences" heuristic.  Other
    * heuristics are the "weighted minimum sum of absolute differences"
    * (experimental and can in theory improve compression), and the "zlib
    * predictive" method (not implemented yet), which does test compressions
    * of lines using different filter methods, and then chooses the
    * (series of) filter(s) that give minimum compressed data size (VERY
    * computationally expensive).
    *
    * GRR 980525:  consider also
    *
    *   (1) minimum sum of absolute differences from running average (i.e.,
    *       keep running sum of non-absolute differences & count of bytes)
    *       [track dispersion, too?  restart average if dispersion too large?]
    *
    *  (1b) minimum sum of absolute differences from sliding average, probably
    *       with window size <= deflate window (usually 32K)
    *
    *   (2) minimum sum of squared differences from zero or running average
    *       (i.e., ~ root-mean-square approach)
    */
    /* We don't need to test the 'no filter' case if this is the only filter
    * that has been chosen, as it doesn't actually do anything to the data.
    */
    best_row = (*png_ptr).row_buf;
    if (-(1 as std::os::raw::c_int) as
            png_size_t).wrapping_div(128 as std::os::raw::c_int as std::os::raw::c_ulong) <=
           row_bytes {
        /* Overflow can occur in the calculation, just select the lowest set
       * filter.
       */
        filter_to_do &= (0 as std::os::raw::c_uint).wrapping_sub(filter_to_do)
    } else if filter_to_do & 0x8 as std::os::raw::c_int as std::os::raw::c_uint !=
                  0 as std::os::raw::c_int as std::os::raw::c_uint &&
                  filter_to_do != 0x8 as std::os::raw::c_int as std::os::raw::c_uint {
        /* Overflow not possible and multiple filters in the list, including the
       * 'none' filter.
       */
        let mut rp: png_bytep = 0 as *mut png_byte;
        let mut sum: png_size_t = 0 as std::os::raw::c_int as png_size_t;
        let mut i: png_size_t = 0;
        let mut v: std::os::raw::c_uint = 0;
        i = 0 as std::os::raw::c_int as png_size_t;
        rp = row_buf.offset(1 as std::os::raw::c_int as isize);
        while i < row_bytes {
            v = *rp as std::os::raw::c_uint;
            sum =
                (sum as
                     std::os::raw::c_ulong).wrapping_add(if v <
                                                        128 as std::os::raw::c_int as
                                                            std::os::raw::c_uint {
                                                     v
                                                 } else {
                                                     (256 as std::os::raw::c_int as
                                                          std::os::raw::c_uint).wrapping_sub(v)
                                                 } as std::os::raw::c_ulong) as
                    png_size_t as png_size_t;
            i = i.wrapping_add(1);
            rp = rp.offset(1)
        }
        mins = sum
    }
    /* Sub filter */
    if filter_to_do == 0x10 as std::os::raw::c_int as std::os::raw::c_uint {
        /* It's the only filter so no testing is needed */
        png_setup_sub_row_only(png_ptr, bpp, row_bytes);
        best_row = (*png_ptr).try_row
    } else if filter_to_do & 0x10 as std::os::raw::c_int as std::os::raw::c_uint !=
                  0 as std::os::raw::c_int as std::os::raw::c_uint {
        let mut sum_0: png_size_t = 0;
        let mut lmins: png_size_t = mins;
        sum_0 = png_setup_sub_row(png_ptr, bpp, row_bytes, lmins);
        if sum_0 < mins {
            mins = sum_0;
            best_row = (*png_ptr).try_row;
            if !(*png_ptr).tst_row.is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row
            }
        }
    }
    /* Up filter */
    if filter_to_do == 0x20 as std::os::raw::c_int as std::os::raw::c_uint {
        png_setup_up_row_only(&mut png_ptr, row_bytes);
        best_row = (*png_ptr).try_row
    } else if filter_to_do & 0x20 as std::os::raw::c_int as std::os::raw::c_uint !=
                  0 as std::os::raw::c_int as std::os::raw::c_uint {
        let mut sum_1: png_size_t = 0;
        let mut lmins_0: png_size_t = mins;
        sum_1 = png_setup_up_row(png_ptr, row_bytes, lmins_0);
        if sum_1 < mins {
            mins = sum_1;
            best_row = (*png_ptr).try_row;
            if !(*png_ptr).tst_row.is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row
            }
        }
    }
    /* Avg filter */
    if filter_to_do == 0x40 as std::os::raw::c_int as std::os::raw::c_uint {
        png_setup_avg_row_only(png_ptr, bpp, row_bytes);
        best_row = (*png_ptr).try_row
    } else if filter_to_do & 0x40 as std::os::raw::c_int as std::os::raw::c_uint !=
                  0 as std::os::raw::c_int as std::os::raw::c_uint {
        let mut sum_2: png_size_t = 0;
        let mut lmins_1: png_size_t = mins;
        sum_2 = png_setup_avg_row(png_ptr, bpp, row_bytes, lmins_1);
        if sum_2 < mins {
            mins = sum_2;
            best_row = (*png_ptr).try_row;
            if !(*png_ptr).tst_row.is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row
            }
        }
    }
    /* Paeth filter */
    if filter_to_do == 0x80 {
    png_setup_paeth_row_only(png_ptr, bpp, row_bytes);
    best_row = unsafe { (*png_ptr).try_row };
} else if filter_to_do & 0x80 != 0 {
    let mut sum_3: png_size_t = 0;
    let lmins_2: png_size_t = mins;
    sum_3 = png_setup_paeth_row(png_ptr, bpp, row_bytes, lmins_2);
    if sum_3 < mins {
        best_row = unsafe { (*png_ptr).try_row };
        let tst_row = unsafe { (*png_ptr).tst_row };
        if !tst_row.is_null() {
            unsafe {
                (*png_ptr).try_row = tst_row;
                (*png_ptr).tst_row = best_row;
            }
        }
    }
}

/* Do the actual writing of the filtered row data from the chosen filter. */
png_write_filtered_row(png_ptr, best_row, unsafe { (*row_info).rowbytes } + 1);

    /* WRITE_FILTER */
}
/* This filters the row, chooses which filter to use, if it has not already
 * been specified by the application, and then writes the row out with the
 * chosen filter.
 */
/* Do the actual writing of a previously filtered row. */
unsafe extern "C" fn png_write_filtered_row(mut png_ptr: png_structrp,
                                            mut filtered_row: png_bytep,
                                            mut full_row_length: png_size_t) 
 /*includes filter byte*/
 {
    png_compress_IDAT(png_ptr, filtered_row as png_const_bytep,
                      full_row_length, 0 as std::os::raw::c_int);
    /* Swap the current and previous rows */
    if !(*png_ptr).prev_row.is_null() {
        let mut tptr: png_bytep = 0 as *mut png_byte;
        tptr = (*png_ptr).prev_row;
        (*png_ptr).prev_row = (*png_ptr).row_buf;
        (*png_ptr).row_buf = tptr
    }
    /* WRITE_FILTER */
    /* Finish row - updates counters and flushes zlib if last row */
    png_write_finish_row(&mut png_ptr);
    (*png_ptr).flush_rows = (*png_ptr).flush_rows.wrapping_add(1);
    if (*png_ptr).flush_dist > 0 as std::os::raw::c_int as std::os::raw::c_uint &&
           (*png_ptr).flush_rows >= (*png_ptr).flush_dist {
        png_write_flush(png_ptr);
    };
    /* WRITE_FLUSH */
}
/* WRITE */
