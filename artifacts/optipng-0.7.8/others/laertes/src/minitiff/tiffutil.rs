
extern "C" {
    
    
    
    #[no_mangle]
    static mut stderr: * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    fn fprintf(_: * mut crate::src::gifread::gifread::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn free(__ptr: * mut core::ffi::c_void);
    #[no_mangle]
    fn abort() -> !;
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
    #[no_mangle]
    fn memset(_: * mut core::ffi::c_void, _: std::os::raw::c_int, _: std::os::raw::c_ulong)
     -> * mut core::ffi::c_void;
}
pub use crate::src::pngxtern::pngxread::_IO_marker;
pub use crate::src::pngxtern::pngxrpnm::_IO_wide_data;
pub use crate::src::pnmio::pnmout::_IO_codecvt;
pub type size_t = std::os::raw::c_ulong;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
// #[derive(Copy, Clone)]

pub type _IO_FILE = crate::src::gifread::gifread::_IO_FILE;
pub type _IO_lock_t = ();
pub type FILE = crate::src::gifread::gifread::_IO_FILE;
// #[derive(Copy, Clone)]

pub type minitiff_info = crate::src::minitiff::tiffread::minitiff_info;
pub const MINITIFF_PHOTOMETRIC_PALETTE: C2RustUnnamed_0 = 3;
pub const MINITIFF_COMPRESSION_NONE: C2RustUnnamed = 1;
pub type C2RustUnnamed = std::os::raw::c_uint;
pub const MINITIFF_COMPRESSION_LZMA2: C2RustUnnamed = 34925;
pub const MINITIFF_COMPRESSION_JPEG2000: C2RustUnnamed = 34712;
pub const MINITIFF_COMPRESSION_SGI_LOGLUV24: C2RustUnnamed = 34677;
pub const MINITIFF_COMPRESSION_SGI_LOGLUV: C2RustUnnamed = 34676;
pub const MINITIFF_COMPRESSION_JBIG: C2RustUnnamed = 34661;
pub const MINITIFF_COMPRESSION_KODAK_DCS: C2RustUnnamed = 32947;
pub const MINITIFF_COMPRESSION_DEFLATE: C2RustUnnamed = 32946;
pub const MINITIFF_COMPRESSION_PIXARLOG: C2RustUnnamed = 32909;
pub const MINITIFF_COMPRESSION_PIXARFILM: C2RustUnnamed = 32908;
pub const MINITIFF_COMPRESSION_IT8_BL: C2RustUnnamed = 32898;
pub const MINITIFF_COMPRESSION_IT8_HC: C2RustUnnamed = 32897;
pub const MINITIFF_COMPRESSION_IT8_LW: C2RustUnnamed = 32896;
pub const MINITIFF_COMPRESSION_IT8_CT_MP: C2RustUnnamed = 32895;
pub const MINITIFF_COMPRESSION_THUNDERSCAN: C2RustUnnamed = 32809;
pub const MINITIFF_COMPRESSION_PACKBITS: C2RustUnnamed = 32773;
pub const MINITIFF_COMPRESSION_CCITT_RLEW: C2RustUnnamed = 32771;
pub const MINITIFF_COMPRESSION_NEXT_RLE: C2RustUnnamed = 32766;
pub const MINITIFF_COMPRESSION_ITU_T43: C2RustUnnamed = 10;
pub const MINITIFF_COMPRESSION_ITU_T85: C2RustUnnamed = 9;
pub const MINITIFF_COMPRESSION_ADOBE_DEFLATE: C2RustUnnamed = 8;
pub const MINITIFF_COMPRESSION_JPEG: C2RustUnnamed = 7;
pub const MINITIFF_COMPRESSION_OLD_JPEG: C2RustUnnamed = 6;
pub const MINITIFF_COMPRESSION_LZW: C2RustUnnamed = 5;
pub const MINITIFF_COMPRESSION_CCITT_FAX4: C2RustUnnamed = 4;
pub const MINITIFF_COMPRESSION_CCITT_T6: C2RustUnnamed = 4;
pub const MINITIFF_COMPRESSION_CCITT_FAX3: C2RustUnnamed = 3;
pub const MINITIFF_COMPRESSION_CCITT_T4: C2RustUnnamed = 3;
pub const MINITIFF_COMPRESSION_CCITT_RLE: C2RustUnnamed = 2;
pub type C2RustUnnamed_0 = std::os::raw::c_uint;
pub const MINITIFF_PHOTOMETRIC_LOGLUV: C2RustUnnamed_0 = 32845;
pub const MINITIFF_PHOTOMETRIC_LOGL: C2RustUnnamed_0 = 32844;
pub const MINITIFF_PHOTOMETRIC_CFA: C2RustUnnamed_0 = 32803;
pub const MINITIFF_PHOTOMETRIC_ITULAB: C2RustUnnamed_0 = 10;
pub const MINITIFF_PHOTOMETRIC_ICCLAB: C2RustUnnamed_0 = 9;
pub const MINITIFF_PHOTOMETRIC_CIELAB: C2RustUnnamed_0 = 8;
pub const MINITIFF_PHOTOMETRIC_YCBCR: C2RustUnnamed_0 = 6;
pub const MINITIFF_PHOTOMETRIC_SEPARATED: C2RustUnnamed_0 = 5;
pub const MINITIFF_PHOTOMETRIC_MASK: C2RustUnnamed_0 = 4;
pub const MINITIFF_PHOTOMETRIC_RGB: C2RustUnnamed_0 = 2;
pub const MINITIFF_PHOTOMETRIC_MINBLACK: C2RustUnnamed_0 = 1;
pub const MINITIFF_PHOTOMETRIC_MINWHITE: C2RustUnnamed_0 = 0;
/*
 * tiffutil.c
 * General-purpose routines for minitiff.
 *
 * Copyright (C) 2006-2017 Cosmin Truta.
 *
 * minitiff is open-source software, distributed under the zlib license.
 * For conditions of distribution and use, see copyright notice in minitiff.h.
 */
/*
 * Constructor.
 */
#[no_mangle]
pub unsafe extern "C" fn minitiff_init_info(mut info_ptr:
                                                * mut crate::src::minitiff::tiffread::minitiff_info) {
    memset(info_ptr as *mut std::os::raw::c_void, 0 as std::os::raw::c_int,
           ::std::mem::size_of::<minitiff_info>() as std::os::raw::c_ulong);
    (*info_ptr).photometric = -(1 as std::os::raw::c_int) as std::os::raw::c_uint;
}
/*
 * Validator.
 */
#[no_mangle]
pub unsafe extern "C" fn minitiff_validate_info<'a1>(mut info_ptr:
                                                    Option<&'a1 crate::src::minitiff::tiffread::minitiff_info>) {
    if (*((info_ptr).clone()).unwrap()).width == 0 as std::os::raw::c_int as std::os::raw::c_ulong ||
           (*((info_ptr).clone()).unwrap()).height == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        minitiff_error((info_ptr).clone(),
                       b"Invalid image dimensions in TIFF file\x00" as
                           *const u8 as *const std::os::raw::c_char);
    }
    if (*((info_ptr).clone()).unwrap()).bits_per_sample == 0 as std::os::raw::c_int as std::os::raw::c_uint ||
           (*((info_ptr).clone()).unwrap()).samples_per_pixel == 0 as std::os::raw::c_int as std::os::raw::c_uint {
        minitiff_error((info_ptr).clone(),
                       b"Invalid pixel info in TIFF file\x00" as *const u8 as
                           *const std::os::raw::c_char);
    }
    if (*((info_ptr).clone()).unwrap()).strip_offsets.is_null() ||
           (*((info_ptr).clone()).unwrap()).rows_per_strip == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        minitiff_error((info_ptr).clone(),
                       b"Invalid strip info in TIFF file\x00" as *const u8 as
                           *const std::os::raw::c_char);
    }
    if (*((info_ptr).clone()).unwrap()).compression !=
           MINITIFF_COMPRESSION_NONE as std::os::raw::c_int as std::os::raw::c_uint {
        minitiff_error((info_ptr).clone(),
                       b"Unsupported compression method in TIFF file\x00" as
                           *const u8 as *const std::os::raw::c_char);
    }
    if (*((info_ptr).clone()).unwrap()).photometric >=
           MINITIFF_PHOTOMETRIC_PALETTE as std::os::raw::c_int as std::os::raw::c_uint {
        minitiff_error((info_ptr).clone(),
                       b"Unsupported photometric interpretation in TIFF file\x00"
                           as *const u8 as *const std::os::raw::c_char);
    };
}
/*
 * Destructor.
 */
#[no_mangle]
pub unsafe extern "C" fn minitiff_destroy_info<'a1>(mut info_ptr:
                                                   Option<&'a1 mut crate::src::minitiff::tiffread::minitiff_info>) {
    if !(*(borrow_mut(&mut info_ptr)).unwrap()).strip_offsets.is_null() {
        free((*(borrow_mut(&mut info_ptr)).unwrap()).strip_offsets as *mut std::os::raw::c_void);
    };
}
/*
 * Error handling utility.
 */
unsafe extern "C" fn default_error_handler(mut msg: * const std::os::raw::c_char) {
    fprintf(stderr,
            b"minitiff: error: %s\n\x00" as *const u8 as *const std::os::raw::c_char,
            msg);
    exit(1 as std::os::raw::c_int);
}
/*
 * Error handler.
 */
#[no_mangle]
pub unsafe extern "C" fn minitiff_error<'a1>(mut info_ptr: Option<&'a1 crate::src::minitiff::tiffread::minitiff_info>,
                                        mut msg: * const std::os::raw::c_char) {
    if (*((info_ptr).clone()).unwrap()).error_handler.is_some() {
        (*((info_ptr).clone()).unwrap()).error_handler.expect("non-null function pointer")(msg);
    } else { default_error_handler(msg); }
    abort();
}
/*
 * Warning handling utility.
 */
unsafe extern "C" fn default_warning_handler(mut msg: * const std::os::raw::c_char) {
    fprintf(stderr,
            b"minitiff: warning: %s\n\x00" as *const u8 as
                *const std::os::raw::c_char, msg);
}
/*
 * Warning handler.
 */
#[no_mangle]
pub unsafe extern "C" fn minitiff_warning<'a1>(mut info_ptr: Option<&'a1 crate::src::minitiff::tiffread::minitiff_info>,
                                          mut msg: * const std::os::raw::c_char) {
    if (*((info_ptr).clone()).unwrap()).warning_handler.is_some() {
        (*((info_ptr).clone()).unwrap()).warning_handler.expect("non-null function pointer")(msg);
    } else { default_warning_handler(msg); };
}
/*
 * Global constants: TIFF file signature.
 */
#[no_mangle]
pub static mut minitiff_sig_m: [std::os::raw::c_char; 4] =
    [0,0,0,0,]; unsafe fn laertes_init_minitiff_sig_m() {
minitiff_sig_m = [0x4d as std::os::raw::c_int as std::os::raw::c_char, 0x4d as std::os::raw::c_int as std::os::raw::c_char,
     0 as std::os::raw::c_int as std::os::raw::c_char, 0x2a as std::os::raw::c_int as std::os::raw::c_char];}//;
/* "MM\0*" */
#[no_mangle]
pub static mut minitiff_sig_i: [std::os::raw::c_char; 4] =
    [0,0,0,0,]; unsafe fn laertes_init_minitiff_sig_i() {
minitiff_sig_i = [0x49 as std::os::raw::c_int as std::os::raw::c_char, 0x49 as std::os::raw::c_int as std::os::raw::c_char,
     0x2a as std::os::raw::c_int as std::os::raw::c_char, 0 as std::os::raw::c_int as std::os::raw::c_char];}//;
/* "II*\0" */
/*
 * Global constants: BigTIFF file signature.
 */
#[no_mangle]
pub static mut minitiff_sig_bigm: [std::os::raw::c_char; 4] =
    [0,0,0,0,]; unsafe fn laertes_init_minitiff_sig_bigm() {
minitiff_sig_bigm = [0x4d as std::os::raw::c_int as std::os::raw::c_char, 0x4d as std::os::raw::c_int as std::os::raw::c_char,
     0 as std::os::raw::c_int as std::os::raw::c_char, 0x2b as std::os::raw::c_int as std::os::raw::c_char];}//;
/* "MM\0*" */
#[no_mangle]
pub static mut minitiff_sig_bigi: [std::os::raw::c_char; 4] =
    [0,0,0,0,]; unsafe fn laertes_init_minitiff_sig_bigi() {
minitiff_sig_bigi = [0x49 as std::os::raw::c_int as std::os::raw::c_char, 0x49 as std::os::raw::c_int as std::os::raw::c_char,
     0x2b as std::os::raw::c_int as std::os::raw::c_char, 0 as std::os::raw::c_int as std::os::raw::c_char];}//;
use crate::laertes_rt::*;
/* "II*\0" */
