

extern "C" {
    #[no_mangle]
    fn __errno_location() -> *mut std::os::raw::c_int;
}
pub type size_t = crate::src::gifread::gifread::size_t;
pub type C2RustUnnamed = std::os::raw::c_uint;
pub const PNM_P7: C2RustUnnamed = 7;
pub const PNM_P6: C2RustUnnamed = 6;
pub const PNM_P5: C2RustUnnamed = 5;
pub const PNM_P4: C2RustUnnamed = 4;
pub const PNM_P3: C2RustUnnamed = 3;
pub const PNM_P2: C2RustUnnamed = 2;
pub const PNM_P1: C2RustUnnamed = 1;
// #[derive(Copy, Clone)]

pub type pnm_struct = crate::src::pnmio::pnmin::pnm_struct;
/* *
 * pnmutil.c
 * PNM utilities.
 *
 * Copyright (C) 2002-2008 Cosmin Truta.
 * This file is part of the pnmio library, distributed under the zlib license.
 * For conditions of distribution and use, see copyright notice in pnmio.h.
 **/
/* *
 * Validates a PNM structure.
 * Returns 1 on success, 0 on failure.
 **/
#[no_mangle]
pub unsafe extern "C" fn pnm_is_valid(mut pnm_ptr: *const pnm_struct)
 -> std::os::raw::c_int {
    let mut format: std::os::raw::c_uint = (*pnm_ptr).format;
    let mut depth: std::os::raw::c_uint = (*pnm_ptr).depth;
    let mut width: std::os::raw::c_uint = (*pnm_ptr).width;
    let mut height: std::os::raw::c_uint = (*pnm_ptr).height;
    let mut maxval: std::os::raw::c_uint = (*pnm_ptr).maxval;
    if depth == 0 as std::os::raw::c_int as std::os::raw::c_uint ||
           width == 0 as std::os::raw::c_int as std::os::raw::c_uint ||
           height == 0 as std::os::raw::c_int as std::os::raw::c_uint ||
           maxval == 0 as std::os::raw::c_int as std::os::raw::c_uint {
        return 0 as std::os::raw::c_int
    }
    match format {
        1 | 4 => {
            /* PBM */
            return if depth == 1 as std::os::raw::c_int as std::os::raw::c_uint &&
                          maxval == 1 as std::os::raw::c_int as std::os::raw::c_uint {
                       1 as std::os::raw::c_int
                   } else { 0 as std::os::raw::c_int }
        }
        2 | 5 => {
            /* PGM */
            return if depth == 1 as std::os::raw::c_int as std::os::raw::c_uint {
                       1 as std::os::raw::c_int
                   } else { 0 as std::os::raw::c_int }
        }
        3 | 6 => {
            /* PPM */
            return if depth == 3 as std::os::raw::c_int as std::os::raw::c_uint {
                       1 as std::os::raw::c_int
                   } else { 0 as std::os::raw::c_int }
        }
        7 => {
            /* PAM */
            return 1 as std::os::raw::c_int
        }
        _ => { return 0 as std::os::raw::c_int }
    };
}
/* *
 * Calculates the size of a raw PNM sample, i.e. the smallest number of
 * bytes required to store a sample value between 0 and pnm_ptr->maxval.
 * The validity check performed on the PNM structure is only partial.
 * Returns the raw sample size on success, or 0 on validation failure.
 **/
#[no_mangle]
pub unsafe extern "C" fn pnm_raw_sample_size(mut pnm_ptr: *const pnm_struct)
 -> size_t {
    let mut maxval: std::os::raw::c_uint = (*pnm_ptr).maxval; /* fall through */
    if maxval == 0 as std::os::raw::c_int as std::os::raw::c_uint {
        *__errno_location() = 22 as std::os::raw::c_int
    }
    if maxval <= 0xff as std::os::raw::c_uint {
        return 1 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffff as std::os::raw::c_uint {
        return 2 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffffff as std::os::raw::c_uint {
        return 3 as std::os::raw::c_int as size_t
    } else if maxval <= 0xffffffff as std::os::raw::c_uint {
        return 4 as std::os::raw::c_int as size_t
    } else {
        /* maxval > PNM_UINT_MAX */
        *__errno_location() = 22 as std::os::raw::c_int;
        return 0 as std::os::raw::c_int as size_t
    };
}
/* *
 * Calculates the number of bytes occupied by an array of PNM samples.
 * The byte count is sample_size * pnm_ptr->depth * pnm_ptr->width * num_rows.
 * The validity check performed on the PNM structure is only partial.
 * Returns the array size on success, or 0 on validation failure.
 **/
#[no_mangle]
pub fn pnm_mem_size(pnm: &pnm_struct, sample_size: usize, num_rows: u32) -> Result<usize, i32> {
    let depth = pnm.depth;
    let width = pnm.width;

    if sample_size == 0 || depth == 0 || width == 0 {
        return Err(22);
    }

    if num_rows as usize > (usize::MAX / sample_size / depth as usize / width as usize) {
        return Err(34);
    }

    Ok(sample_size * depth as usize * width as usize * num_rows as usize)
}

