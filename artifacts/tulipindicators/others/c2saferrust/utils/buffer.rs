

extern "C" {
    
    fn malloc(_: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    
    fn free(_: *mut std::os::raw::c_void);
}
// #[derive(Copy, Clone)]

pub type ti_buffer = crate::indicators::cci::ti_buffer;
/*
 * Tulip Indicators
 * https://tulipindicators.org/
 * Copyright (c) 2010-2018 Tulip Charts LLC
 * Lewis Van Winkle (LV@tulipcharts.org)
 *
 * This file is part of Tulip Indicators.
 *
 * Tulip Indicators is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Tulip Indicators is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tulip Indicators.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#[no_mangle]
pub unsafe extern "C" fn ti_buffer_new(mut size: std::os::raw::c_int)
 -> *mut ti_buffer {
    let s: std::os::raw::c_int =
        ::std::mem::size_of::<ti_buffer>() as std::os::raw::c_ulong as std::os::raw::c_int +
            (size - 1 as std::os::raw::c_int) *
                ::std::mem::size_of::<std::os::raw::c_double>() as std::os::raw::c_ulong as
                    std::os::raw::c_int;
    let mut ret: *mut ti_buffer =
        malloc(s as std::os::raw::c_uint as std::os::raw::c_ulong) as *mut ti_buffer;
    (*ret).size = size;
    (*ret).pushes = 0 as std::os::raw::c_int;
    (*ret).index = 0 as std::os::raw::c_int;
    (*ret).sum = 0 as std::os::raw::c_int as std::os::raw::c_double;
    return ret;
}
#[no_mangle]
pub fn ti_buffer_free(buffer: Box<ti_buffer>) {
    // The Box will automatically free the memory when it goes out of scope
}

