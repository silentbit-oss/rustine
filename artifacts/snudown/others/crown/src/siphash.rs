use ::libc;
extern "C" {
    fn __ctype_tolower_loc() -> *mut *const __int32_t;
}
pub type __uint8_t = libc::c_uchar;
pub type __int32_t = libc::c_int;
pub type __uint32_t = libc::c_uint;
pub type __uint64_t = libc::c_ulong;
pub type uint8_t = __uint8_t;
pub type uint32_t = __uint32_t;
pub type uint64_t = __uint64_t;
pub type size_t = libc::c_ulong;
#[inline]
unsafe extern "C" fn tolower(mut __c: libc::c_int) -> libc::c_int {
    return if __c >= -(128 as libc::c_int) && __c < 256 as libc::c_int {
        *(*__ctype_tolower_loc()).offset(__c as isize)
    } else {
        __c
    };
}
#[no_mangle]
pub unsafe extern "C" fn siphash(
    mut in_0: *const uint8_t,
    inlen: size_t,
    mut k: *const uint8_t,
) -> uint64_t {
    let mut hash: uint64_t = 0;
    let mut out: *mut uint8_t = &mut hash as *mut uint64_t as *mut uint8_t;
    let mut v0: uint64_t = 0x736f6d6570736575 as libc::c_ulonglong as uint64_t;
    let mut v1: uint64_t = 0x646f72616e646f6d as libc::c_ulonglong as uint64_t;
    let mut v2: uint64_t = 0x6c7967656e657261 as libc::c_ulonglong as uint64_t;
    let mut v3: uint64_t = 0x7465646279746573 as libc::c_ulonglong as uint64_t;
    let mut k0: uint64_t = *k.offset(0 as libc::c_int as isize) as uint64_t
        | (*k.offset(1 as libc::c_int as isize) as uint64_t) << 8 as libc::c_int
        | (*k.offset(2 as libc::c_int as isize) as uint64_t) << 16 as libc::c_int
        | (*k.offset(3 as libc::c_int as isize) as uint64_t) << 24 as libc::c_int
        | (*k.offset(4 as libc::c_int as isize) as uint64_t) << 32 as libc::c_int
        | (*k.offset(5 as libc::c_int as isize) as uint64_t) << 40 as libc::c_int
        | (*k.offset(6 as libc::c_int as isize) as uint64_t) << 48 as libc::c_int
        | (*k.offset(7 as libc::c_int as isize) as uint64_t) << 56 as libc::c_int;
    let mut k1: uint64_t = *k
        .offset(8 as libc::c_int as isize)
        .offset(0 as libc::c_int as isize) as uint64_t
        | (*k.offset(8 as libc::c_int as isize).offset(1 as libc::c_int as isize)
            as uint64_t) << 8 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(2 as libc::c_int as isize)
            as uint64_t) << 16 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(3 as libc::c_int as isize)
            as uint64_t) << 24 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(4 as libc::c_int as isize)
            as uint64_t) << 32 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(5 as libc::c_int as isize)
            as uint64_t) << 40 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(6 as libc::c_int as isize)
            as uint64_t) << 48 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(7 as libc::c_int as isize)
            as uint64_t) << 56 as libc::c_int;
    let mut m: uint64_t = 0;
    let mut end: *const uint8_t = in_0
        .offset(inlen as isize)
        .offset(
            -(inlen.wrapping_rem(::core::mem::size_of::<uint64_t>() as libc::c_ulong)
                as isize),
        );
    let left: libc::c_int = (inlen & 7 as libc::c_int as size_t) as libc::c_int;
    let mut b: uint64_t = inlen << 56 as libc::c_int;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;
    while in_0 != end {
        m = *in_0.offset(0 as libc::c_int as isize) as uint64_t
            | (*in_0.offset(1 as libc::c_int as isize) as uint64_t) << 8 as libc::c_int
            | (*in_0.offset(2 as libc::c_int as isize) as uint64_t) << 16 as libc::c_int
            | (*in_0.offset(3 as libc::c_int as isize) as uint64_t) << 24 as libc::c_int
            | (*in_0.offset(4 as libc::c_int as isize) as uint64_t) << 32 as libc::c_int
            | (*in_0.offset(5 as libc::c_int as isize) as uint64_t) << 40 as libc::c_int
            | (*in_0.offset(6 as libc::c_int as isize) as uint64_t) << 48 as libc::c_int
            | (*in_0.offset(7 as libc::c_int as isize) as uint64_t) << 56 as libc::c_int;
        v3 ^= m;
        v0 = v0.wrapping_add(v1);
        v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
        v1 ^= v0;
        v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
        v2 = v2.wrapping_add(v3);
        v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
        v3 ^= v2;
        v0 = v0.wrapping_add(v3);
        v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
        v3 ^= v0;
        v2 = v2.wrapping_add(v1);
        v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
        v1 ^= v2;
        v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
        v0 = v0.wrapping_add(v1);
        v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
        v1 ^= v0;
        v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
        v2 = v2.wrapping_add(v3);
        v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
        v3 ^= v2;
        v0 = v0.wrapping_add(v3);
        v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
        v3 ^= v0;
        v2 = v2.wrapping_add(v1);
        v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
        v1 ^= v2;
        v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
        v0 ^= m;
        in_0 = in_0.offset(8 as libc::c_int as isize);
    }
    let mut current_block_47: u64;
    match left {
        7 => {
            b
                |= (*in_0.offset(6 as libc::c_int as isize) as uint64_t)
                    << 48 as libc::c_int;
            current_block_47 = 9261856704109325266;
        }
        6 => {
            current_block_47 = 9261856704109325266;
        }
        5 => {
            current_block_47 = 6997290010865393001;
        }
        4 => {
            current_block_47 = 4624355900562323113;
        }
        3 => {
            current_block_47 = 10598357242847959928;
        }
        2 => {
            current_block_47 = 8737878233858216932;
        }
        1 => {
            current_block_47 = 16060096534408587340;
        }
        0 | _ => {
            current_block_47 = 7427571413727699167;
        }
    }
    match current_block_47 {
        9261856704109325266 => {
            b
                |= (*in_0.offset(5 as libc::c_int as isize) as uint64_t)
                    << 40 as libc::c_int;
            current_block_47 = 6997290010865393001;
        }
        _ => {}
    }
    match current_block_47 {
        6997290010865393001 => {
            b
                |= (*in_0.offset(4 as libc::c_int as isize) as uint64_t)
                    << 32 as libc::c_int;
            current_block_47 = 4624355900562323113;
        }
        _ => {}
    }
    match current_block_47 {
        4624355900562323113 => {
            b
                |= (*in_0.offset(3 as libc::c_int as isize) as uint64_t)
                    << 24 as libc::c_int;
            current_block_47 = 10598357242847959928;
        }
        _ => {}
    }
    match current_block_47 {
        10598357242847959928 => {
            b
                |= (*in_0.offset(2 as libc::c_int as isize) as uint64_t)
                    << 16 as libc::c_int;
            current_block_47 = 8737878233858216932;
        }
        _ => {}
    }
    match current_block_47 {
        8737878233858216932 => {
            b
                |= (*in_0.offset(1 as libc::c_int as isize) as uint64_t)
                    << 8 as libc::c_int;
            current_block_47 = 16060096534408587340;
        }
        _ => {}
    }
    match current_block_47 {
        16060096534408587340 => {
            b |= *in_0.offset(0 as libc::c_int as isize) as uint64_t;
        }
        _ => {}
    }
    v3 ^= b;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 ^= b;
    v2 ^= 0xff as libc::c_int as uint64_t;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    b = v0 ^ v1 ^ v2 ^ v3;
    *out.offset(0 as libc::c_int as isize) = b as uint32_t as uint8_t;
    *out
        .offset(
            1 as libc::c_int as isize,
        ) = (b as uint32_t >> 8 as libc::c_int) as uint8_t;
    *out
        .offset(
            2 as libc::c_int as isize,
        ) = (b as uint32_t >> 16 as libc::c_int) as uint8_t;
    *out
        .offset(
            3 as libc::c_int as isize,
        ) = (b as uint32_t >> 24 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            0 as libc::c_int as isize,
        ) = (b >> 32 as libc::c_int) as uint32_t as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            1 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 8 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            2 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 16 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            3 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 24 as libc::c_int) as uint8_t;
    return hash;
}
#[no_mangle]
pub unsafe extern "C" fn siphash_nocase(
    mut in_0: *const uint8_t,
    inlen: size_t,
    mut k: *const uint8_t,
) -> uint64_t {
    let mut hash: uint64_t = 0;
    let mut out: *mut uint8_t = &mut hash as *mut uint64_t as *mut uint8_t;
    let mut v0: uint64_t = 0x736f6d6570736575 as libc::c_ulonglong as uint64_t;
    let mut v1: uint64_t = 0x646f72616e646f6d as libc::c_ulonglong as uint64_t;
    let mut v2: uint64_t = 0x6c7967656e657261 as libc::c_ulonglong as uint64_t;
    let mut v3: uint64_t = 0x7465646279746573 as libc::c_ulonglong as uint64_t;
    let mut k0: uint64_t = *k.offset(0 as libc::c_int as isize) as uint64_t
        | (*k.offset(1 as libc::c_int as isize) as uint64_t) << 8 as libc::c_int
        | (*k.offset(2 as libc::c_int as isize) as uint64_t) << 16 as libc::c_int
        | (*k.offset(3 as libc::c_int as isize) as uint64_t) << 24 as libc::c_int
        | (*k.offset(4 as libc::c_int as isize) as uint64_t) << 32 as libc::c_int
        | (*k.offset(5 as libc::c_int as isize) as uint64_t) << 40 as libc::c_int
        | (*k.offset(6 as libc::c_int as isize) as uint64_t) << 48 as libc::c_int
        | (*k.offset(7 as libc::c_int as isize) as uint64_t) << 56 as libc::c_int;
    let mut k1: uint64_t = *k
        .offset(8 as libc::c_int as isize)
        .offset(0 as libc::c_int as isize) as uint64_t
        | (*k.offset(8 as libc::c_int as isize).offset(1 as libc::c_int as isize)
            as uint64_t) << 8 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(2 as libc::c_int as isize)
            as uint64_t) << 16 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(3 as libc::c_int as isize)
            as uint64_t) << 24 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(4 as libc::c_int as isize)
            as uint64_t) << 32 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(5 as libc::c_int as isize)
            as uint64_t) << 40 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(6 as libc::c_int as isize)
            as uint64_t) << 48 as libc::c_int
        | (*k.offset(8 as libc::c_int as isize).offset(7 as libc::c_int as isize)
            as uint64_t) << 56 as libc::c_int;
    let mut m: uint64_t = 0;
    let mut end: *const uint8_t = in_0
        .offset(inlen as isize)
        .offset(
            -(inlen.wrapping_rem(::core::mem::size_of::<uint64_t>() as libc::c_ulong)
                as isize),
        );
    let left: libc::c_int = (inlen & 7 as libc::c_int as size_t) as libc::c_int;
    let mut b: uint64_t = inlen << 56 as libc::c_int;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;
    while in_0 != end {
        m = ({
            let mut __res: libc::c_int = 0;
            if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                > 1 as libc::c_int as libc::c_ulong
            {
                if 0 != 0 {
                    let mut __c: libc::c_int = *in_0.offset(0 as libc::c_int as isize)
                        as libc::c_int;
                    __res = (if __c < -(128 as libc::c_int) || __c > 255 as libc::c_int {
                        __c
                    } else {
                        *(*__ctype_tolower_loc()).offset(__c as isize)
                    });
                } else {
                    __res = tolower(
                        *in_0.offset(0 as libc::c_int as isize) as libc::c_int,
                    );
                }
            } else {
                __res = *(*__ctype_tolower_loc())
                    .offset(
                        *in_0.offset(0 as libc::c_int as isize) as libc::c_int as isize,
                    );
            }
            __res
        }) as uint64_t
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(1 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(1 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(1 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 8 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(2 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(2 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(2 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 16 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(3 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(3 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(3 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 24 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(4 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(4 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(4 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 32 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(5 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(5 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(5 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 40 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(6 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(6 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(6 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 48 as libc::c_int
            | (({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *in_0
                            .offset(7 as libc::c_int as isize) as libc::c_int;
                        __res = (if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        });
                    } else {
                        __res = tolower(
                            *in_0.offset(7 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *in_0.offset(7 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint64_t) << 56 as libc::c_int;
        v3 ^= m;
        v0 = v0.wrapping_add(v1);
        v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
        v1 ^= v0;
        v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
        v2 = v2.wrapping_add(v3);
        v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
        v3 ^= v2;
        v0 = v0.wrapping_add(v3);
        v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
        v3 ^= v0;
        v2 = v2.wrapping_add(v1);
        v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
        v1 ^= v2;
        v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
        v0 = v0.wrapping_add(v1);
        v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
        v1 ^= v0;
        v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
        v2 = v2.wrapping_add(v3);
        v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
        v3 ^= v2;
        v0 = v0.wrapping_add(v3);
        v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
        v3 ^= v0;
        v2 = v2.wrapping_add(v1);
        v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
        v1 ^= v2;
        v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
        v0 ^= m;
        in_0 = in_0.offset(8 as libc::c_int as isize);
    }
    let mut current_block_47: u64;
    match left {
        7 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(6 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(6 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(6 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 48 as libc::c_int;
            current_block_47 = 10409017548181334667;
        }
        6 => {
            current_block_47 = 10409017548181334667;
        }
        5 => {
            current_block_47 = 3494945688115535314;
        }
        4 => {
            current_block_47 = 5623321898913267038;
        }
        3 => {
            current_block_47 = 4404456663553854343;
        }
        2 => {
            current_block_47 = 7906537706655321329;
        }
        1 => {
            current_block_47 = 9532432129209566691;
        }
        0 | _ => {
            current_block_47 = 7427571413727699167;
        }
    }
    match current_block_47 {
        10409017548181334667 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(5 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(5 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(5 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 40 as libc::c_int;
            current_block_47 = 3494945688115535314;
        }
        _ => {}
    }
    match current_block_47 {
        3494945688115535314 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(4 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(4 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(4 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 32 as libc::c_int;
            current_block_47 = 5623321898913267038;
        }
        _ => {}
    }
    match current_block_47 {
        5623321898913267038 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(3 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(3 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(3 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 24 as libc::c_int;
            current_block_47 = 4404456663553854343;
        }
        _ => {}
    }
    match current_block_47 {
        4404456663553854343 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(2 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(2 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(2 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 16 as libc::c_int;
            current_block_47 = 7906537706655321329;
        }
        _ => {}
    }
    match current_block_47 {
        7906537706655321329 => {
            b
                |= (({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(1 as libc::c_int as isize) as libc::c_int;
                            __res = (if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            });
                        } else {
                            __res = tolower(
                                *in_0.offset(1 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(1 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t) << 8 as libc::c_int;
            current_block_47 = 9532432129209566691;
        }
        _ => {}
    }
    match current_block_47 {
        9532432129209566691 => {
            b
                |= ({
                    let mut __res: libc::c_int = 0;
                    if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                        > 1 as libc::c_int as libc::c_ulong
                    {
                        if 0 != 0 {
                            let mut __c: libc::c_int = *in_0
                                .offset(0 as libc::c_int as isize) as libc::c_int;
                            __res = if __c < -(128 as libc::c_int)
                                || __c > 255 as libc::c_int
                            {
                                __c
                            } else {
                                *(*__ctype_tolower_loc()).offset(__c as isize)
                            };
                        } else {
                            __res = tolower(
                                *in_0.offset(0 as libc::c_int as isize) as libc::c_int,
                            );
                        }
                    } else {
                        __res = *(*__ctype_tolower_loc())
                            .offset(
                                *in_0.offset(0 as libc::c_int as isize) as libc::c_int
                                    as isize,
                            );
                    }
                    __res
                }) as uint64_t;
        }
        _ => {}
    }
    v3 ^= b;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 ^= b;
    v2 ^= 0xff as libc::c_int as uint64_t;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    v0 = v0.wrapping_add(v1);
    v1 = v1 << 13 as libc::c_int | v1 >> 64 as libc::c_int - 13 as libc::c_int;
    v1 ^= v0;
    v0 = v0 << 32 as libc::c_int | v0 >> 64 as libc::c_int - 32 as libc::c_int;
    v2 = v2.wrapping_add(v3);
    v3 = v3 << 16 as libc::c_int | v3 >> 64 as libc::c_int - 16 as libc::c_int;
    v3 ^= v2;
    v0 = v0.wrapping_add(v3);
    v3 = v3 << 21 as libc::c_int | v3 >> 64 as libc::c_int - 21 as libc::c_int;
    v3 ^= v0;
    v2 = v2.wrapping_add(v1);
    v1 = v1 << 17 as libc::c_int | v1 >> 64 as libc::c_int - 17 as libc::c_int;
    v1 ^= v2;
    v2 = v2 << 32 as libc::c_int | v2 >> 64 as libc::c_int - 32 as libc::c_int;
    b = v0 ^ v1 ^ v2 ^ v3;
    *out.offset(0 as libc::c_int as isize) = b as uint32_t as uint8_t;
    *out
        .offset(
            1 as libc::c_int as isize,
        ) = (b as uint32_t >> 8 as libc::c_int) as uint8_t;
    *out
        .offset(
            2 as libc::c_int as isize,
        ) = (b as uint32_t >> 16 as libc::c_int) as uint8_t;
    *out
        .offset(
            3 as libc::c_int as isize,
        ) = (b as uint32_t >> 24 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            0 as libc::c_int as isize,
        ) = (b >> 32 as libc::c_int) as uint32_t as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            1 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 8 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            2 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 16 as libc::c_int) as uint8_t;
    *out
        .offset(4 as libc::c_int as isize)
        .offset(
            3 as libc::c_int as isize,
        ) = ((b >> 32 as libc::c_int) as uint32_t >> 24 as libc::c_int) as uint8_t;
    return hash;
}
