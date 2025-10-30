







use std::convert::TryInto;

use std::os::raw::c_ulong;

pub type size_t = crate::src::gifread::gifread::size_t;
pub type z_size_t = size_t;
pub type Byte = crate::src::libpng::png::Byte;
pub type uInt = crate::src::libpng::png::uInt;
pub type uLong = crate::src::libpng::png::uLong;
pub type Bytef = crate::src::libpng::png::Bytef;
pub type __off_t = crate::src::gifread::gifread::__off_t;
pub type __off64_t = crate::src::gifread::gifread::__off64_t;
pub type off_t = __off_t;
pub type off64_t = __off64_t;
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
/* use NO_DIVIDE if your processor does not do division in hardware --
   try it both ways to see which is faster */
/* ========================================================================= */
#[no_mangle]
pub unsafe extern "C" fn adler32_z(mut adler: uLong, mut buf: *const Bytef,
                                   mut len: z_size_t) -> uLong {
    let mut sum2: u64 = 0;
let mut n: u32 = 0;
/* split Adler-32 into component sums */
sum2 = (adler >> 16) & 0xffff;
adler &= 0xffff;
/* in case user likes doing a byte at a time, keep it fast */
if len == 1 {
    adler = adler.wrapping_add(unsafe { *buf } as u64);
    if adler >= 65521 {
        adler = adler.wrapping_sub(65521);
    }
    sum2 = sum2.wrapping_add(adler);
    if sum2 >= 65521 {
        sum2 = sum2.wrapping_sub(65521);
    }
    return adler | (sum2 << 16);
}
/* initial Adler-32 value (deferred check for len == 1 speed) */
if len == 0 { return 1; }
/* in case short lengths are provided, keep it somewhat fast */
if len < 16 {
    for i in 0..len {
        adler = adler.wrapping_add(unsafe { *buf.add(i as usize) } as u64);
        sum2 = sum2.wrapping_add(adler);
    }
    if adler >= 65521 {
        adler = adler.wrapping_sub(65521);
    }
    sum2 = sum2 % 65521;
    return adler | (sum2 << 16);
}
/* do length NMAX blocks -- requires just one modulo operation */
while len >= 5552 {
    let len = len.wrapping_sub(5552) as z_size_t; // NMAX is divisible by 16
let mut n = (5552 / 16) as u32;

loop {
     let buf_slice = unsafe { std::slice::from_raw_parts(buf, 16) }; // Assuming the buffer length is 16 bytes

for i in 0..8 {
    if i < buf_slice.len() {
        adler = adler.wrapping_add(buf_slice[i] as u64);
        sum2 = sum2.wrapping_add(adler);
    }
}

            while n != 0 {
    adler = adler.wrapping_add(unsafe { *buf.offset((8 + 4 + 1) as isize) as u64 });
    sum2 = sum2.wrapping_add(adler);
    
    adler = adler.wrapping_add(unsafe { *buf.offset((8 + 4 + 2) as isize) as u64 });
    sum2 = sum2.wrapping_add(adler);
    
    adler = adler.wrapping_add(unsafe { *buf.offset((8 + 4 + 2 + 1) as isize) as u64 });
    sum2 = sum2.wrapping_add(adler);
    
    // 16 sums unrolled
    buf = buf.offset(16);
    n = n.wrapping_sub(1);
}

        
}

adler = adler.wrapping_rem(65521);
sum2 = sum2.wrapping_rem(65521);
/*
The variables live at this point are:
(mut adler: u64, mut buf: *const u8, mut len: u64, mut sum2: u64, mut n: u32)
*/

    
}
/* do remaining bytes (less than NMAX, still just one modulo) */
if len != 0 {
    /* avoid modulos if none remaining */
    while len >= 16 {
     len -= 16;

let buf_slice = unsafe { std::slice::from_raw_parts(buf, len as usize) };

for i in 0..8 {
    let value = buf_slice[i];
    adler = adler.wrapping_add(value as u64);
    sum2 = sum2.wrapping_add(adler);
}

 
     adler =
                (adler as
                     std::os::raw::c_ulong).wrapping_add(*buf.offset((8 as std::os::raw::c_int
                                                                  +
                                                                  4 as
                                                                      std::os::raw::c_int
                                                                  +
                                                                  1 as
                                                                      std::os::raw::c_int)
                                                                 as isize) as
                                                     std::os::raw::c_ulong) as uLong
                    as uLong;
            sum2 = sum2.wrapping_add(adler);
            adler =
                (adler as
                     std::os::raw::c_ulong).wrapping_add(*buf.offset((8 as std::os::raw::c_int
                                                                  +
                                                                  4 as
                                                                      std::os::raw::c_int
                                                                  +
                                                                  2 as
                                                                      std::os::raw::c_int)
                                                                 as isize) as
                                                     std::os::raw::c_ulong) as uLong
                    as uLong;
            sum2 = sum2.wrapping_add(adler);
            adler =
                (adler as
                     std::os::raw::c_ulong).wrapping_add(*buf.offset((8 as std::os::raw::c_int
                                                                  +
                                                                  4 as
                                                                      std::os::raw::c_int
                                                                  +
                                                                  2 as
                                                                      std::os::raw::c_int
                                                                  +
                                                                  1 as
                                                                      std::os::raw::c_int)
                                                                 as isize) as
                                                     std::os::raw::c_ulong) as uLong
                    as uLong;
            sum2 = sum2.wrapping_add(adler);
            buf = buf.offset(16 as std::os::raw::c_int as isize)
 
}

while len > 0 {
    len -= 1;
    let byte = unsafe { *buf.add(len as usize) }; // Use unsafe to dereference the raw pointer
    adler = adler.wrapping_add(byte as u64);
    sum2 = sum2.wrapping_add(adler);
}

adler = adler.wrapping_rem(65521);
sum2 = sum2.wrapping_rem(65521);
/*
The variables live at this point are:
(mut adler: u64, mut buf: *const u8, mut len: u64, mut sum2: u64)
*/

    
}
/* return recombined sums */
return adler | (sum2 << 16);

}
/* ========================================================================= */
#[no_mangle]
pub unsafe extern "C" fn adler32(mut adler: uLong, mut buf: *const Bytef,
                                 mut len: uInt) -> uLong {
    return adler32_z(adler, buf, len as z_size_t);
}
/* adler32.c -- compute the Adler-32 checksum of a data stream
 * Copyright (C) 1995-2011, 2016 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */
/* @(#) $Id$ */
/* ========================================================================= */
 fn adler32_combine_(adler1: u64, adler2: u64, len2: i64) -> u64 {
    let mut sum1: u64 = 0;
    let mut sum2: u64 = 0;
    let mut rem: u32 = 0;

    if len2 < 0 {
        return 0xffffffff;
    }

    let len2 = (len2 % 65521) as u64; // assumes len2 >= 0
    rem = len2 as u32;
    sum1 = adler1 & 0xffff;
    sum2 = (rem as u64).wrapping_mul(sum1) % 65521;
    sum1 = sum1.wrapping_add((adler2 & 0xffff).wrapping_add(65521).wrapping_sub(1));
    sum2 = sum2.wrapping_add(((adler1 >> 16 & 0xffff) as u64).wrapping_add((adler2 >> 16 & 0xffff) as u64).wrapping_add(65521).wrapping_sub(rem as u64));

    if sum1 >= 65521 {
        sum1 -= 65521;
    }
    if sum1 >= 65521 {
        sum1 -= 65521;
    }
    if sum2 >= (65521 << 1) {
        sum2 -= (65521 << 1);
    }
    if sum2 >= 65521 {
        sum2 -= 65521;
    }

    sum1 | (sum2 << 16)
}

/* ========================================================================= */
#[no_mangle]
pub fn adler32_combine(adler1: u64, adler2: u64, len2: i64) -> u64 {
    adler32_combine_(adler1, adler2, len2)
}

#[no_mangle]
pub fn adler32_combine64(adler1: u64, adler2: u64, len2: i64) -> u64 {
    adler32_combine_(adler1, adler2, len2)
}

