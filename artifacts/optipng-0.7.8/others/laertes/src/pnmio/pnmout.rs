
extern "C" {
    
    pub type _IO_codecvt;
    
    #[no_mangle]
    fn __errno_location() -> * mut std::os::raw::c_int;
    #[no_mangle]
    fn fprintf(_: * mut crate::src::gifread::gifread::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn putc(__c: std::os::raw::c_int, __stream: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fwrite(_: * const core::ffi::c_void, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
              _: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_ulong;
    
    
}
pub use crate::src::pnmio::pnmutil::pnm_is_valid;
pub use crate::src::pngxtern::pngxread::_IO_marker;
pub use crate::src::pngxtern::pngxrpnm::_IO_wide_data;
pub type size_t = std::os::raw::c_ulong;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
// #[derive(Copy, Clone)]

pub type _IO_FILE = crate::src::gifread::gifread::_IO_FILE;
pub type _IO_lock_t = ();
pub type FILE = crate::src::gifread::gifread::_IO_FILE;
pub type C2RustUnnamed = std::os::raw::c_uint;
pub const PNM_P7: C2RustUnnamed = 7;
pub const PNM_P6: C2RustUnnamed = 6;
pub const PNM_P5: C2RustUnnamed = 5;
pub const PNM_P4: C2RustUnnamed = 4;
pub const PNM_P3: C2RustUnnamed = 3;
pub const PNM_P2: C2RustUnnamed = 2;
pub const PNM_P1: C2RustUnnamed = 1;
// #[derive(Copy, Clone)]

pub type pnm_struct = crate::src::pngxtern::pngxrpnm::pnm_struct;
/* *
 * pnmout.c
 * PNM file output.
 *
 * Copyright (C) 2002-2008 Cosmin Truta.
 * This file is part of the pnmio library, distributed under the zlib license.
 * For conditions of distribution and use, see copyright notice in pnmio.h.
 **/
/* *
 * Validates a PNM header structure and writes it to a file stream.
 * Returns 1 on success, 0 on validation failure, or -1 on output failure.
 **/
#[no_mangle]
pub unsafe extern "C" fn pnm_fput_header(mut pnm_ptr: * const crate::src::pngxtern::pngxrpnm::pnm_struct,
                                         mut stream: * mut crate::src::gifread::gifread::_IO_FILE)
 -> std::os::raw::c_int {
    let mut format: u32 = (*pnm_ptr).format;
    let mut depth: u32 = (*pnm_ptr).depth;
    let mut width: u32 = (*pnm_ptr).width;
    let mut height: u32 = (*pnm_ptr).height;
    let mut maxval: u32 = (*pnm_ptr).maxval;
    let mut result: i32 = 0;
    /* validate the info structure */
    if pnm_is_valid(pnm_ptr) == 0 { return 0 as std::os::raw::c_int }
    /* write the PNM file header */
    match format {
        1 | 4 => {
            result =
                fprintf(stream,
                        b"P%c\n%u %u\n\x00" as *const u8 as
                            *const std::os::raw::c_char,
                        format.wrapping_add('0' as i32 as std::os::raw::c_uint),
                        width, height)
        }
        2 | 3 | 5 | 6 => {
            result =
                fprintf(stream,
                        b"P%c\n%u %u\n%u\n\x00" as *const u8 as
                            *const std::os::raw::c_char,
                        format.wrapping_add('0' as i32 as std::os::raw::c_uint),
                        width, height, maxval)
        }
        7 => {
            result =
                fprintf(stream,
                        b"P7\nDEPTH %u\nWIDTH %u\nHEIGHT %u\nMAXVAL %u\nENDHDR\n\x00"
                            as *const u8 as *const std::os::raw::c_char, depth, width,
                        height, maxval)
        }
        _ => {
            *__errno_location() = 22 as std::os::raw::c_int;
            return 0 as std::os::raw::c_int
        }
    }
    /* check the result */
    return if result > 0 as std::os::raw::c_int {
               1 as std::os::raw::c_int
           } else { -(1 as std::os::raw::c_int) };
}
/* *
 * Writes an array of PNM sample values to a file stream.
 * The values are written in the format specified by pnm_ptr->format.
 * The array length is pnm_ptr->depth * pnm_ptr->width * num_rows.
 * The validity check performed on the PNM structure is only partial.
 * Returns 1 on success, 0 on validation failure, or -1 on output failure.
 **/
#[no_mangle]
pub unsafe extern "C" fn pnm_fput_values<'a1>(mut pnm_ptr: Option<&'a1 crate::src::pngxtern::pngxrpnm::pnm_struct>,
                                         mut sample_values:
                                             * const std::os::raw::c_uint,
                                         mut num_rows: std::os::raw::c_uint,
                                         mut stream: * mut crate::src::gifread::gifread::_IO_FILE)
 -> std::os::raw::c_int {
    let mut format: u32 = (*(pnm_ptr).unwrap()).format;
    let mut depth: u32 = (*(pnm_ptr).unwrap()).depth;
    let mut width: u32 = (*(pnm_ptr).unwrap()).width;
    let mut maxval: u32 = (*(pnm_ptr).unwrap()).maxval;
    let mut row_length: u64 =
        (depth as size_t).wrapping_mul(width as size_t);
    let mut num_samples: u64 =
        (num_rows as std::os::raw::c_ulong).wrapping_mul(row_length);
    let mut ch: i32 = 0;
    let mut mask: i32 = 0;
    let mut i: u64 = 0;
    let mut j: u64 = 0;
    /* write the sample values */
    match format {
        1 => {
            j = 0 as std::os::raw::c_int as size_t;
            i = j;
            while i < num_samples {
                if putc((if *sample_values.offset(i as isize) !=
                                0 as std::os::raw::c_int as std::os::raw::c_uint {
                             '0' as i32
                         } else { '1' as i32 }), stream) ==
                       -(1 as std::os::raw::c_int) {
                    break ;
                }
                j = j.wrapping_add(1);
                if j == row_length {
                    j = 0 as std::os::raw::c_int as size_t;
                    if putc('\n' as i32, stream) == -(1 as std::os::raw::c_int) {
                        break ;
                    }
                }
                i = i.wrapping_add(1)
            }
        }
        2 | 3 => {
            j = 0 as std::os::raw::c_int as size_t;
            i = j;
            while i < num_samples {
                j = j.wrapping_add(1);
                if j == row_length { j = 0 as std::os::raw::c_int as size_t }
                if fprintf(stream,
                           (if j == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
                                b"%u\n\x00" as *const u8 as
                                    *const std::os::raw::c_char
                            } else {
                                b"%u \x00" as *const u8 as *const std::os::raw::c_char
                            }), *sample_values.offset(i as isize)) <=
                       0 as std::os::raw::c_int {
                    break ;
                }
                i = i.wrapping_add(1)
            }
        }
        4 => {
            j = 0 as std::os::raw::c_int as size_t;
            i = j;
            while i < num_samples {
                ch = 0 as std::os::raw::c_int;
                mask = 0x80 as std::os::raw::c_int;
                while mask != 0 as std::os::raw::c_int {
                    let mut fresh0 = i;
                    i = i.wrapping_add(1);
                    if *sample_values.offset(fresh0 as isize) ==
                           0 as std::os::raw::c_int as std::os::raw::c_uint {
                        ch |= mask
                    }
                    j = j.wrapping_add(1);
                    if j == row_length {
                        j = 0 as std::os::raw::c_int as size_t;
                        break ;
                    } else { mask >>= 1 as std::os::raw::c_int }
                }
                if putc(ch, stream) == -(1 as std::os::raw::c_int) { break ; }
            }
        }
        5 | 6 | 7 => {
            if maxval <= 0xff as std::os::raw::c_uint {
                /* 1 byte per sample */
                i = 0 as std::os::raw::c_int as size_t;
                while i < num_samples {
                    if putc((*sample_values.offset(i as isize) &
                                 0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                std::os::raw::c_int, stream) == -(1 as std::os::raw::c_int) {
                        break ;
                    }
                    i = i.wrapping_add(1)
                }
            } else if maxval <= 0xffff as std::os::raw::c_uint {
                /* 2 bytes per sample */
                i = 0 as std::os::raw::c_int as size_t;
                while i < num_samples {
                    if putc((*sample_values.offset(i as isize) >>
                                 8 as std::os::raw::c_int &
                                 0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                std::os::raw::c_int, stream) == -(1 as std::os::raw::c_int) ||
                           putc((*sample_values.offset(i as isize) &
                                     0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                    std::os::raw::c_int, stream) ==
                               -(1 as std::os::raw::c_int) {
                        break ;
                    }
                    i = i.wrapping_add(1)
                }
            } else if maxval <= 0xffffffff as std::os::raw::c_uint {
                /* 3 or 4 bytes per sample */
                i = 0 as std::os::raw::c_int as size_t;
                while i < num_samples {
                    if maxval > 0xffffff as std::os::raw::c_uint {
                        if putc((*sample_values.offset(i as isize) >>
                                     24 as std::os::raw::c_int &
                                     0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                    std::os::raw::c_int, stream) ==
                               -(1 as std::os::raw::c_int) {
                            break ;
                        }
                    }
                    if putc((*sample_values.offset(i as isize) >>
                                 16 as std::os::raw::c_int &
                                 0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                std::os::raw::c_int, stream) == -(1 as std::os::raw::c_int) ||
                           putc((*sample_values.offset(i as isize) >>
                                     8 as std::os::raw::c_int &
                                     0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                    std::os::raw::c_int, stream) ==
                               -(1 as std::os::raw::c_int) ||
                           putc((*sample_values.offset(i as isize) &
                                     0xff as std::os::raw::c_int as std::os::raw::c_uint) as
                                    std::os::raw::c_int, stream) ==
                               -(1 as std::os::raw::c_int) {
                        break ;
                    }
                    i = i.wrapping_add(1)
                }
            } else {
                /* maxval > PNM_UINT_MAX */
                *__errno_location() = 22 as std::os::raw::c_int;
                return 0 as std::os::raw::c_int
            }
        }
        _ => {
            *__errno_location() = 22 as std::os::raw::c_int;
            return 0 as std::os::raw::c_int
        }
    }
    /* check the result */
    return if i == num_samples {
               1 as std::os::raw::c_int
           } else { -(1 as std::os::raw::c_int) };
}
/* *
 * Writes an array of sample bytes to a raw PNM file stream.
 * Multi-byte samples are stored in network order, as in the PNM stream.
 * The byte count is sample_size * pnm_ptr->depth * pnm_ptr->width * num_rows.
 * The validity check performed on the PNM structure is only partial.
 * Returns 1 on success, 0 on validation failure, or -1 on output failure.
 **/
#[no_mangle]
pub unsafe extern "C" fn pnm_fput_bytes<'a1>(mut pnm_ptr: Option<&'a1 crate::src::pngxtern::pngxrpnm::pnm_struct>,
                                        mut sample_bytes:
                                            * const std::os::raw::c_uchar,
                                        mut sample_size: std::os::raw::c_ulong,
                                        mut num_rows: std::os::raw::c_uint,
                                        mut stream: * mut crate::src::gifread::gifread::_IO_FILE)
 -> std::os::raw::c_int {
    let mut format: u32 = (*(pnm_ptr).unwrap()).format;
    let mut depth: u32 = (*(pnm_ptr).unwrap()).depth;
    let mut width: u32 = (*(pnm_ptr).unwrap()).width;
    let mut maxval: u32 = (*(pnm_ptr).unwrap()).maxval;
    let mut row_length: u64 =
        (depth as size_t).wrapping_mul(width as size_t);
    let mut num_samples: u64 =
        (num_rows as std::os::raw::c_ulong).wrapping_mul(row_length);
    let mut raw_sample_size: u64 = 0;
    let mut ch: i32 = 0;
    let mut mask: i32 = 0;
    let mut i: u64 = 0;
    let mut j: u64 = 0;
    /* validate the given sample size */
    if maxval <= 0xff as std::os::raw::c_uint {
        raw_sample_size = 1 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffff as std::os::raw::c_uint {
        raw_sample_size = 2 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffffff as std::os::raw::c_uint {
        raw_sample_size = 3 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffffffff as std::os::raw::c_uint {
        raw_sample_size = 4 as std::os::raw::c_int as size_t
    } else {
        /* maxval > PNM_UINT_MAX */
        raw_sample_size = (sample_size == 0) as std::os::raw::c_int as size_t
    }
    if raw_sample_size != sample_size {
        *__errno_location() = 22 as std::os::raw::c_int;
        return 0 as std::os::raw::c_int
    }
    /* write the raw sample bytes */
    match format {
        4 => {
            j = 0 as std::os::raw::c_int as size_t;
            i = j;
            while i < num_samples {
                ch = 0 as std::os::raw::c_int;
                mask = 0x80 as std::os::raw::c_int;
                while mask != 0 as std::os::raw::c_int {
                    let mut fresh1 = i;
                    i = i.wrapping_add(1);
                    if *sample_bytes.offset(fresh1 as isize) as std::os::raw::c_int ==
                           0 as std::os::raw::c_int {
                        ch |= mask
                    }
                    j = j.wrapping_add(1);
                    if j == row_length {
                        j = 0 as std::os::raw::c_int as size_t;
                        break ;
                    } else { mask >>= 1 as std::os::raw::c_int }
                }
                if putc(ch, stream) == -(1 as std::os::raw::c_int) { break ; }
            }
        }
        5 | 6 | 7 => {
            i =
                fwrite(sample_bytes as *const std::os::raw::c_void, sample_size,
                       num_samples, stream)
        }
        _ => {
            *__errno_location() = 22 as std::os::raw::c_int;
            return 0 as std::os::raw::c_int
        }
    }
    /* check the result */
    return if i == num_samples {
               1 as std::os::raw::c_int
           } else { -(1 as std::os::raw::c_int) };
}
use crate::laertes_rt::*;
