

extern "C" {
    
    
    
    
    
    
    
}
pub use crate::src::zlib::deflate::deflate;
pub use crate::src::zlib::deflate::deflateEnd;
pub use crate::src::zlib::deflate::deflateInit_;
pub use crate::src::zlib::deflate::internal_state;
pub type Byte = crate::src::libpng::png::Byte;
pub type uInt = crate::src::libpng::png::uInt;
pub type uLong = crate::src::libpng::png::uLong;
pub type Bytef = crate::src::libpng::png::Bytef;
pub type uLongf = uLong;
pub type voidpf = crate::src::libpng::png::voidpf;
pub type alloc_func = crate::src::libpng::png::alloc_func;
pub type free_func = crate::src::libpng::png::free_func;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct z_stream_s {
    pub next_in: *mut Bytef,
    pub avail_in: uInt,
    pub total_in: uLong,
    pub next_out: *mut Bytef,
    pub avail_out: uInt,
    pub total_out: uLong,
    pub msg: *mut std::os::raw::c_char,
    pub state: *mut internal_state,
    pub zalloc: alloc_func,
    pub zfree: free_func,
    pub opaque: voidpf,
    pub data_type: std::os::raw::c_int,
    pub adler: uLong,
    pub reserved: uLong,
}
pub type z_stream = crate::src::libpng::png::z_stream;
pub type z_streamp = crate::src::libpng::png::z_streamp;
/* compress.c -- compress a memory buffer
 * Copyright (C) 1995-2005, 2014, 2016 Jean-loup Gailly, Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
/* @(#) $Id$ */
/* ===========================================================================
     Compresses the source buffer into the destination buffer. The level
   parameter has the same meaning as in deflateInit.  sourceLen is the byte
   length of the source buffer. Upon entry, destLen is the total size of the
   destination buffer, which must be at least 0.1% larger than sourceLen plus
   12 bytes. Upon exit, destLen is the actual size of the compressed buffer.

     compress2 returns Z_OK if success, Z_MEM_ERROR if there was not enough
   memory, Z_BUF_ERROR if there was not enough room in the output buffer,
   Z_STREAM_ERROR if the level parameter is invalid.
*/
#[no_mangle]
pub unsafe extern "C" fn compress2(mut dest: *mut Bytef,
                                   mut destLen: *mut uLongf,
                                   mut source: *const Bytef,
                                   mut sourceLen: uLong,
                                   mut level: std::os::raw::c_int) -> std::os::raw::c_int {
    let mut stream: z_stream =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,};
    let mut err: std::os::raw::c_int = 0;
    let max: uInt = -(1 as std::os::raw::c_int) as uInt;
    let mut left: uLong = 0;
    left = *destLen;
    *destLen = 0 as std::os::raw::c_int as uLongf;
    stream.zalloc = None;
    stream.zfree = None;
    stream.opaque = 0 as voidpf;
    let mut err = deflateInit_(&mut stream, level, "1.2.11-optipng", std::mem::size_of::<z_stream>());
    if err != 0 as std::os::raw::c_int { return err }
    stream.next_out = dest;
    stream.avail_out = 0 as std::os::raw::c_int as uInt;
    stream.next_in = source as *mut Bytef;
    stream.avail_in = 0 as std::os::raw::c_int as uInt;
    loop  {
        if stream.avail_out == 0 as std::os::raw::c_int as std::os::raw::c_uint {
            stream.avail_out =
                if left > max as uLong { max } else { left as uInt };
            left =
                (left as
                     std::os::raw::c_ulong).wrapping_sub(stream.avail_out as
                                                     std::os::raw::c_ulong) as uLong
                    as uLong
        }
        if stream.avail_in == 0 as std::os::raw::c_int as std::os::raw::c_uint {
            stream.avail_in =
                if sourceLen > max as uLong {
                    max
                } else { sourceLen as uInt };
            sourceLen =
                (sourceLen as
                     std::os::raw::c_ulong).wrapping_sub(stream.avail_in as
                                                     std::os::raw::c_ulong) as uLong
                    as uLong
        }
        err =
            deflate(&mut stream,
                    if sourceLen != 0 {
                        0 as std::os::raw::c_int
                    } else { 4 as std::os::raw::c_int });
        if !(err == 0 as std::os::raw::c_int) { break ; }
    }
    *destLen = stream.total_out;
    deflateEnd(&mut stream);
    return if err == 1 as std::os::raw::c_int { 0 as std::os::raw::c_int } else { err };
}
/* ===========================================================================
 */
#[no_mangle]
pub unsafe extern "C" fn compress(mut dest: *mut Bytef,
                                  mut destLen: *mut uLongf,
                                  mut source: *const Bytef,
                                  mut sourceLen: uLong) -> std::os::raw::c_int {
    return compress2(dest, destLen, source, sourceLen, -(1 as std::os::raw::c_int));
}
/* ===========================================================================
     If the default memLevel or windowBits for deflateInit() is changed, then
   this function needs to be updated.
 */
#[no_mangle]
pub fn compressBound(source_len: u64) -> u64 {
    let shifted_12 = source_len >> 12;
    let shifted_14 = source_len >> 14;
    let shifted_25 = source_len >> 25;
    let base = 13;

    source_len.wrapping_add(shifted_12)
              .wrapping_add(shifted_14)
              .wrapping_add(shifted_25)
              .wrapping_add(base)
}

