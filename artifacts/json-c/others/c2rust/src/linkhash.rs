use ::libc;
extern "C" {
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn json_c_get_random_seed() -> libc::c_int;
}
pub type ptrdiff_t = libc::c_long;
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
pub type __uint16_t = libc::c_ushort;
pub type __uint32_t = libc::c_uint;
pub type uint8_t = __uint8_t;
pub type uint16_t = __uint16_t;
pub type uint32_t = __uint32_t;
pub type uintptr_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct lh_entry {
    pub k: *const libc::c_void,
    pub k_is_constant: libc::c_int,
    pub v: *const libc::c_void,
    pub next: *mut lh_entry,
    pub prev: *mut lh_entry,
}
pub type json_bool = libc::c_int;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct lh_table {
    pub size: libc::c_int,
    pub count: libc::c_int,
    pub head: *mut lh_entry,
    pub tail: *mut lh_entry,
    pub table: *mut lh_entry,
    pub free_fn: Option::<lh_entry_free_fn>,
    pub hash_fn: Option::<lh_hash_fn>,
    pub equal_fn: Option::<lh_equal_fn>,
}
pub type lh_equal_fn = unsafe extern "C" fn(
    *const libc::c_void,
    *const libc::c_void,
) -> libc::c_int;
pub type lh_hash_fn = unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong;
pub type lh_entry_free_fn = unsafe extern "C" fn(*mut lh_entry) -> ();
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub ptr: *const libc::c_void,
    pub i: size_t,
}
#[inline]
unsafe extern "C" fn lh_get_hash(
    mut t: *const lh_table,
    mut k: *const libc::c_void,
) -> libc::c_ulong {
    return ((*t).hash_fn).expect("non-null function pointer")(k);
}
#[inline]
unsafe extern "C" fn lh_entry_v(mut e: *const lh_entry) -> *mut libc::c_void {
    return (*e).v as uintptr_t as *mut libc::c_void;
}
static mut char_hash_fn: Option::<lh_hash_fn> = unsafe {
    Some(lh_char_hash as unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong)
};
#[no_mangle]
pub unsafe extern "C" fn json_global_set_string_hash(h: libc::c_int) -> libc::c_int {
    match h {
        0 => {
            char_hash_fn = Some(
                lh_char_hash
                    as unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong,
            );
        }
        1 => {
            char_hash_fn = Some(
                lh_perllike_str_hash
                    as unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong,
            );
        }
        _ => return -(1 as libc::c_int),
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn lh_ptr_hash(mut k: *const libc::c_void) -> libc::c_ulong {
    return (k as ptrdiff_t as libc::c_ulong).wrapping_mul(0x9e370001 as libc::c_ulong)
        >> 4 as libc::c_int
        & (9223372036854775807 as libc::c_long as libc::c_ulong)
            .wrapping_mul(2 as libc::c_ulong)
            .wrapping_add(1 as libc::c_ulong);
}
#[no_mangle]
pub unsafe extern "C" fn lh_ptr_equal(
    mut k1: *const libc::c_void,
    mut k2: *const libc::c_void,
) -> libc::c_int {
    return (k1 == k2) as libc::c_int;
}
unsafe extern "C" fn hashlittle(
    mut key: *const libc::c_void,
    mut length: size_t,
    mut initval: uint32_t,
) -> uint32_t {
    let mut a: uint32_t = 0;
    let mut b: uint32_t = 0;
    let mut c: uint32_t = 0;
    let mut u: C2RustUnnamed = C2RustUnnamed {
        ptr: 0 as *const libc::c_void,
    };
    c = (0xdeadbeef as libc::c_uint)
        .wrapping_add(length as uint32_t)
        .wrapping_add(initval);
    b = c;
    a = b;
    u.ptr = key;
    if 1 as libc::c_int != 0
        && u.i & 0x3 as libc::c_int as size_t == 0 as libc::c_int as size_t
    {
        let mut k: *const uint32_t = key as *const uint32_t;
        while length > 12 as libc::c_int as size_t {
            a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
            c = c.wrapping_add(*k.offset(2 as libc::c_int as isize));
            a = a.wrapping_sub(c);
            a ^= c << 4 as libc::c_int | c >> 32 as libc::c_int - 4 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 6 as libc::c_int | a >> 32 as libc::c_int - 6 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 8 as libc::c_int | b >> 32 as libc::c_int - 8 as libc::c_int;
            b = b.wrapping_add(a);
            a = a.wrapping_sub(c);
            a ^= c << 16 as libc::c_int | c >> 32 as libc::c_int - 16 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 19 as libc::c_int | a >> 32 as libc::c_int - 19 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 4 as libc::c_int | b >> 32 as libc::c_int - 4 as libc::c_int;
            b = b.wrapping_add(a);
            length = length.wrapping_sub(12 as libc::c_int as size_t);
            k = k.offset(3 as libc::c_int as isize);
        }
        match length {
            12 => {
                c = c.wrapping_add(*k.offset(2 as libc::c_int as isize));
                b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            11 => {
                c = c
                    .wrapping_add(
                        *k.offset(2 as libc::c_int as isize)
                            & 0xffffff as libc::c_int as uint32_t,
                    );
                b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            10 => {
                c = c
                    .wrapping_add(
                        *k.offset(2 as libc::c_int as isize)
                            & 0xffff as libc::c_int as uint32_t,
                    );
                b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            9 => {
                c = c
                    .wrapping_add(
                        *k.offset(2 as libc::c_int as isize)
                            & 0xff as libc::c_int as uint32_t,
                    );
                b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            8 => {
                b = b.wrapping_add(*k.offset(1 as libc::c_int as isize));
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            7 => {
                b = b
                    .wrapping_add(
                        *k.offset(1 as libc::c_int as isize)
                            & 0xffffff as libc::c_int as uint32_t,
                    );
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            6 => {
                b = b
                    .wrapping_add(
                        *k.offset(1 as libc::c_int as isize)
                            & 0xffff as libc::c_int as uint32_t,
                    );
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            5 => {
                b = b
                    .wrapping_add(
                        *k.offset(1 as libc::c_int as isize)
                            & 0xff as libc::c_int as uint32_t,
                    );
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            4 => {
                a = a.wrapping_add(*k.offset(0 as libc::c_int as isize));
            }
            3 => {
                a = a
                    .wrapping_add(
                        *k.offset(0 as libc::c_int as isize)
                            & 0xffffff as libc::c_int as uint32_t,
                    );
            }
            2 => {
                a = a
                    .wrapping_add(
                        *k.offset(0 as libc::c_int as isize)
                            & 0xffff as libc::c_int as uint32_t,
                    );
            }
            1 => {
                a = a
                    .wrapping_add(
                        *k.offset(0 as libc::c_int as isize)
                            & 0xff as libc::c_int as uint32_t,
                    );
            }
            0 => return c,
            _ => {}
        }
    } else if 1 as libc::c_int != 0
        && u.i & 0x1 as libc::c_int as size_t == 0 as libc::c_int as size_t
    {
        let mut k_0: *const uint16_t = key as *const uint16_t;
        let mut k8: *const uint8_t = 0 as *const uint8_t;
        while length > 12 as libc::c_int as size_t {
            a = a
                .wrapping_add(
                    (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                        .wrapping_add(
                            (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                << 16 as libc::c_int,
                        ),
                );
            b = b
                .wrapping_add(
                    (*k_0.offset(2 as libc::c_int as isize) as uint32_t)
                        .wrapping_add(
                            (*k_0.offset(3 as libc::c_int as isize) as uint32_t)
                                << 16 as libc::c_int,
                        ),
                );
            c = c
                .wrapping_add(
                    (*k_0.offset(4 as libc::c_int as isize) as uint32_t)
                        .wrapping_add(
                            (*k_0.offset(5 as libc::c_int as isize) as uint32_t)
                                << 16 as libc::c_int,
                        ),
                );
            a = a.wrapping_sub(c);
            a ^= c << 4 as libc::c_int | c >> 32 as libc::c_int - 4 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 6 as libc::c_int | a >> 32 as libc::c_int - 6 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 8 as libc::c_int | b >> 32 as libc::c_int - 8 as libc::c_int;
            b = b.wrapping_add(a);
            a = a.wrapping_sub(c);
            a ^= c << 16 as libc::c_int | c >> 32 as libc::c_int - 16 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 19 as libc::c_int | a >> 32 as libc::c_int - 19 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 4 as libc::c_int | b >> 32 as libc::c_int - 4 as libc::c_int;
            b = b.wrapping_add(a);
            length = length.wrapping_sub(12 as libc::c_int as size_t);
            k_0 = k_0.offset(6 as libc::c_int as isize);
        }
        k8 = k_0 as *const uint8_t;
        let mut current_block_102: u64;
        match length {
            12 => {
                c = c
                    .wrapping_add(
                        (*k_0.offset(4 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(5 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
                b = b
                    .wrapping_add(
                        (*k_0.offset(2 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(3 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
                a = a
                    .wrapping_add(
                        (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
                current_block_102 = 8062065914618164218;
            }
            11 => {
                c = c
                    .wrapping_add(
                        (*k8.offset(10 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_102 = 11220331375136032509;
            }
            10 => {
                current_block_102 = 11220331375136032509;
            }
            9 => {
                c = c.wrapping_add(*k8.offset(8 as libc::c_int as isize) as uint32_t);
                current_block_102 = 4647193646042868866;
            }
            8 => {
                current_block_102 = 4647193646042868866;
            }
            7 => {
                b = b
                    .wrapping_add(
                        (*k8.offset(6 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_102 = 13394712405657322686;
            }
            6 => {
                current_block_102 = 13394712405657322686;
            }
            5 => {
                b = b.wrapping_add(*k8.offset(4 as libc::c_int as isize) as uint32_t);
                current_block_102 = 8627143394729521319;
            }
            4 => {
                current_block_102 = 8627143394729521319;
            }
            3 => {
                a = a
                    .wrapping_add(
                        (*k8.offset(2 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_102 = 629556595112414427;
            }
            2 => {
                current_block_102 = 629556595112414427;
            }
            1 => {
                a = a.wrapping_add(*k8.offset(0 as libc::c_int as isize) as uint32_t);
                current_block_102 = 8062065914618164218;
            }
            0 => return c,
            _ => {
                current_block_102 = 8062065914618164218;
            }
        }
        match current_block_102 {
            13394712405657322686 => {
                b = b.wrapping_add(*k_0.offset(2 as libc::c_int as isize) as uint32_t);
                a = a
                    .wrapping_add(
                        (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
            }
            4647193646042868866 => {
                b = b
                    .wrapping_add(
                        (*k_0.offset(2 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(3 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
                a = a
                    .wrapping_add(
                        (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
            }
            11220331375136032509 => {
                c = c.wrapping_add(*k_0.offset(4 as libc::c_int as isize) as uint32_t);
                b = b
                    .wrapping_add(
                        (*k_0.offset(2 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(3 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
                a = a
                    .wrapping_add(
                        (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
            }
            8627143394729521319 => {
                a = a
                    .wrapping_add(
                        (*k_0.offset(0 as libc::c_int as isize) as uint32_t)
                            .wrapping_add(
                                (*k_0.offset(1 as libc::c_int as isize) as uint32_t)
                                    << 16 as libc::c_int,
                            ),
                    );
            }
            629556595112414427 => {
                a = a.wrapping_add(*k_0.offset(0 as libc::c_int as isize) as uint32_t);
            }
            _ => {}
        }
    } else {
        let mut k_1: *const uint8_t = key as *const uint8_t;
        while length > 12 as libc::c_int as size_t {
            a = a.wrapping_add(*k_1.offset(0 as libc::c_int as isize) as uint32_t);
            a = a
                .wrapping_add(
                    (*k_1.offset(1 as libc::c_int as isize) as uint32_t)
                        << 8 as libc::c_int,
                );
            a = a
                .wrapping_add(
                    (*k_1.offset(2 as libc::c_int as isize) as uint32_t)
                        << 16 as libc::c_int,
                );
            a = a
                .wrapping_add(
                    (*k_1.offset(3 as libc::c_int as isize) as uint32_t)
                        << 24 as libc::c_int,
                );
            b = b.wrapping_add(*k_1.offset(4 as libc::c_int as isize) as uint32_t);
            b = b
                .wrapping_add(
                    (*k_1.offset(5 as libc::c_int as isize) as uint32_t)
                        << 8 as libc::c_int,
                );
            b = b
                .wrapping_add(
                    (*k_1.offset(6 as libc::c_int as isize) as uint32_t)
                        << 16 as libc::c_int,
                );
            b = b
                .wrapping_add(
                    (*k_1.offset(7 as libc::c_int as isize) as uint32_t)
                        << 24 as libc::c_int,
                );
            c = c.wrapping_add(*k_1.offset(8 as libc::c_int as isize) as uint32_t);
            c = c
                .wrapping_add(
                    (*k_1.offset(9 as libc::c_int as isize) as uint32_t)
                        << 8 as libc::c_int,
                );
            c = c
                .wrapping_add(
                    (*k_1.offset(10 as libc::c_int as isize) as uint32_t)
                        << 16 as libc::c_int,
                );
            c = c
                .wrapping_add(
                    (*k_1.offset(11 as libc::c_int as isize) as uint32_t)
                        << 24 as libc::c_int,
                );
            a = a.wrapping_sub(c);
            a ^= c << 4 as libc::c_int | c >> 32 as libc::c_int - 4 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 6 as libc::c_int | a >> 32 as libc::c_int - 6 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 8 as libc::c_int | b >> 32 as libc::c_int - 8 as libc::c_int;
            b = b.wrapping_add(a);
            a = a.wrapping_sub(c);
            a ^= c << 16 as libc::c_int | c >> 32 as libc::c_int - 16 as libc::c_int;
            c = c.wrapping_add(b);
            b = b.wrapping_sub(a);
            b ^= a << 19 as libc::c_int | a >> 32 as libc::c_int - 19 as libc::c_int;
            a = a.wrapping_add(c);
            c = c.wrapping_sub(b);
            c ^= b << 4 as libc::c_int | b >> 32 as libc::c_int - 4 as libc::c_int;
            b = b.wrapping_add(a);
            length = length.wrapping_sub(12 as libc::c_int as size_t);
            k_1 = k_1.offset(12 as libc::c_int as isize);
        }
        let mut current_block_153: u64;
        match length {
            12 => {
                c = c
                    .wrapping_add(
                        (*k_1.offset(11 as libc::c_int as isize) as uint32_t)
                            << 24 as libc::c_int,
                    );
                current_block_153 = 406518158506369645;
            }
            11 => {
                current_block_153 = 406518158506369645;
            }
            10 => {
                current_block_153 = 7044150670807326711;
            }
            9 => {
                current_block_153 = 17619945261343983063;
            }
            8 => {
                current_block_153 = 1303582255924961092;
            }
            7 => {
                current_block_153 = 2291608877625409219;
            }
            6 => {
                current_block_153 = 15242826882141771083;
            }
            5 => {
                current_block_153 = 4607506367156045854;
            }
            4 => {
                current_block_153 = 9731982635625192303;
            }
            3 => {
                current_block_153 = 18122108123133987599;
            }
            2 => {
                current_block_153 = 6240497624250405364;
            }
            1 => {
                current_block_153 = 6163499581338803661;
            }
            0 => return c,
            _ => {
                current_block_153 = 7728257318064351663;
            }
        }
        match current_block_153 {
            406518158506369645 => {
                c = c
                    .wrapping_add(
                        (*k_1.offset(10 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_153 = 7044150670807326711;
            }
            _ => {}
        }
        match current_block_153 {
            7044150670807326711 => {
                c = c
                    .wrapping_add(
                        (*k_1.offset(9 as libc::c_int as isize) as uint32_t)
                            << 8 as libc::c_int,
                    );
                current_block_153 = 17619945261343983063;
            }
            _ => {}
        }
        match current_block_153 {
            17619945261343983063 => {
                c = c.wrapping_add(*k_1.offset(8 as libc::c_int as isize) as uint32_t);
                current_block_153 = 1303582255924961092;
            }
            _ => {}
        }
        match current_block_153 {
            1303582255924961092 => {
                b = b
                    .wrapping_add(
                        (*k_1.offset(7 as libc::c_int as isize) as uint32_t)
                            << 24 as libc::c_int,
                    );
                current_block_153 = 2291608877625409219;
            }
            _ => {}
        }
        match current_block_153 {
            2291608877625409219 => {
                b = b
                    .wrapping_add(
                        (*k_1.offset(6 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_153 = 15242826882141771083;
            }
            _ => {}
        }
        match current_block_153 {
            15242826882141771083 => {
                b = b
                    .wrapping_add(
                        (*k_1.offset(5 as libc::c_int as isize) as uint32_t)
                            << 8 as libc::c_int,
                    );
                current_block_153 = 4607506367156045854;
            }
            _ => {}
        }
        match current_block_153 {
            4607506367156045854 => {
                b = b.wrapping_add(*k_1.offset(4 as libc::c_int as isize) as uint32_t);
                current_block_153 = 9731982635625192303;
            }
            _ => {}
        }
        match current_block_153 {
            9731982635625192303 => {
                a = a
                    .wrapping_add(
                        (*k_1.offset(3 as libc::c_int as isize) as uint32_t)
                            << 24 as libc::c_int,
                    );
                current_block_153 = 18122108123133987599;
            }
            _ => {}
        }
        match current_block_153 {
            18122108123133987599 => {
                a = a
                    .wrapping_add(
                        (*k_1.offset(2 as libc::c_int as isize) as uint32_t)
                            << 16 as libc::c_int,
                    );
                current_block_153 = 6240497624250405364;
            }
            _ => {}
        }
        match current_block_153 {
            6240497624250405364 => {
                a = a
                    .wrapping_add(
                        (*k_1.offset(1 as libc::c_int as isize) as uint32_t)
                            << 8 as libc::c_int,
                    );
                current_block_153 = 6163499581338803661;
            }
            _ => {}
        }
        match current_block_153 {
            6163499581338803661 => {
                a = a.wrapping_add(*k_1.offset(0 as libc::c_int as isize) as uint32_t);
            }
            _ => {}
        }
    }
    c ^= b;
    c = c
        .wrapping_sub(
            b << 14 as libc::c_int | b >> 32 as libc::c_int - 14 as libc::c_int,
        );
    a ^= c;
    a = a
        .wrapping_sub(
            c << 11 as libc::c_int | c >> 32 as libc::c_int - 11 as libc::c_int,
        );
    b ^= a;
    b = b
        .wrapping_sub(
            a << 25 as libc::c_int | a >> 32 as libc::c_int - 25 as libc::c_int,
        );
    c ^= b;
    c = c
        .wrapping_sub(
            b << 16 as libc::c_int | b >> 32 as libc::c_int - 16 as libc::c_int,
        );
    a ^= c;
    a = a
        .wrapping_sub(c << 4 as libc::c_int | c >> 32 as libc::c_int - 4 as libc::c_int);
    b ^= a;
    b = b
        .wrapping_sub(
            a << 14 as libc::c_int | a >> 32 as libc::c_int - 14 as libc::c_int,
        );
    c ^= b;
    c = c
        .wrapping_sub(
            b << 24 as libc::c_int | b >> 32 as libc::c_int - 24 as libc::c_int,
        );
    return c;
}
unsafe extern "C" fn lh_perllike_str_hash(mut k: *const libc::c_void) -> libc::c_ulong {
    let mut rkey: *const libc::c_char = k as *const libc::c_char;
    let mut hashval: libc::c_uint = 1 as libc::c_int as libc::c_uint;
    while *rkey != 0 {
        let fresh0 = rkey;
        rkey = rkey.offset(1);
        hashval = hashval
            .wrapping_mul(33 as libc::c_int as libc::c_uint)
            .wrapping_add(*fresh0 as libc::c_uint);
    }
    return hashval as libc::c_ulong;
}
unsafe extern "C" fn lh_char_hash(mut k: *const libc::c_void) -> libc::c_ulong {
    static mut random_seed: libc::c_int = -(1 as libc::c_int);
    if random_seed == -(1 as libc::c_int) {
        let mut seed: libc::c_int = 0;
        loop {
            seed = json_c_get_random_seed();
            if !(seed == -(1 as libc::c_int)) {
                break;
            }
        }
        (::core::intrinsics::atomic_cxchg_seqcst_seqcst(
            &mut random_seed,
            -(1 as libc::c_int),
            seed,
        ))
            .0;
    }
    return hashlittle(
        k as *const libc::c_char as *const libc::c_void,
        strlen(k as *const libc::c_char),
        random_seed as uint32_t,
    ) as libc::c_ulong;
}
#[no_mangle]
pub unsafe extern "C" fn lh_char_equal(
    mut k1: *const libc::c_void,
    mut k2: *const libc::c_void,
) -> libc::c_int {
    return (strcmp(k1 as *const libc::c_char, k2 as *const libc::c_char)
        == 0 as libc::c_int) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_new(
    mut size: libc::c_int,
    mut free_fn: Option::<lh_entry_free_fn>,
    mut hash_fn: Option::<lh_hash_fn>,
    mut equal_fn: Option::<lh_equal_fn>,
) -> *mut lh_table {
    let mut i: libc::c_int = 0;
    let mut t: *mut lh_table = 0 as *mut lh_table;
    if size > 0 as libc::c_int {} else {
        __assert_fail(
            b"size > 0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/linkhash.c\0"
                as *const u8 as *const libc::c_char,
            506 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 84],
                &[libc::c_char; 84],
            >(
                b"struct lh_table *lh_table_new(int, lh_entry_free_fn *, lh_hash_fn *, lh_equal_fn *)\0",
            ))
                .as_ptr(),
        );
    }
    'c_4866: {
        if size > 0 as libc::c_int {} else {
            __assert_fail(
                b"size > 0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/linkhash.c\0"
                    as *const u8 as *const libc::c_char,
                506 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 84],
                    &[libc::c_char; 84],
                >(
                    b"struct lh_table *lh_table_new(int, lh_entry_free_fn *, lh_hash_fn *, lh_equal_fn *)\0",
                ))
                    .as_ptr(),
            );
        }
    };
    t = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<lh_table>() as libc::c_ulong,
    ) as *mut lh_table;
    if t.is_null() {
        return 0 as *mut lh_table;
    }
    (*t).count = 0 as libc::c_int;
    (*t).size = size;
    (*t)
        .table = calloc(
        size as libc::c_ulong,
        ::core::mem::size_of::<lh_entry>() as libc::c_ulong,
    ) as *mut lh_entry;
    if ((*t).table).is_null() {
        free(t as *mut libc::c_void);
        return 0 as *mut lh_table;
    }
    (*t).free_fn = free_fn;
    (*t).hash_fn = hash_fn;
    (*t).equal_fn = equal_fn;
    i = 0 as libc::c_int;
    while i < size {
        let ref mut fresh1 = (*((*t).table).offset(i as isize)).k;
        *fresh1 = -(1 as libc::c_int) as *mut libc::c_void;
        i += 1;
        i;
    }
    return t;
}
#[no_mangle]
pub unsafe extern "C" fn lh_kchar_table_new(
    mut size: libc::c_int,
    mut free_fn: Option::<lh_entry_free_fn>,
) -> *mut lh_table {
    return lh_table_new(
        size,
        free_fn,
        char_hash_fn,
        Some(
            lh_char_equal
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
    );
}
#[no_mangle]
pub unsafe extern "C" fn lh_kptr_table_new(
    mut size: libc::c_int,
    mut free_fn: Option::<lh_entry_free_fn>,
) -> *mut lh_table {
    return lh_table_new(
        size,
        free_fn,
        Some(lh_ptr_hash as unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong),
        Some(
            lh_ptr_equal
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
    );
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_resize(
    mut t: *mut lh_table,
    mut new_size: libc::c_int,
) -> libc::c_int {
    let mut new_t: *mut lh_table = 0 as *mut lh_table;
    let mut ent: *mut lh_entry = 0 as *mut lh_entry;
    new_t = lh_table_new(new_size, None, (*t).hash_fn, (*t).equal_fn);
    if new_t.is_null() {
        return -(1 as libc::c_int);
    }
    ent = (*t).head;
    while !ent.is_null() {
        let mut h: libc::c_ulong = lh_get_hash(new_t, (*ent).k);
        let mut opts: libc::c_uint = 0 as libc::c_int as libc::c_uint;
        if (*ent).k_is_constant != 0 {
            opts = ((1 as libc::c_int) << 2 as libc::c_int) as libc::c_uint;
        }
        if lh_table_insert_w_hash(new_t, (*ent).k, (*ent).v, h, opts) != 0 as libc::c_int
        {
            lh_table_free(new_t);
            return -(1 as libc::c_int);
        }
        ent = (*ent).next;
    }
    free((*t).table as *mut libc::c_void);
    (*t).table = (*new_t).table;
    (*t).size = new_size;
    (*t).head = (*new_t).head;
    (*t).tail = (*new_t).tail;
    free(new_t as *mut libc::c_void);
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_free(mut t: *mut lh_table) {
    let mut c: *mut lh_entry = 0 as *mut lh_entry;
    if ((*t).free_fn).is_some() {
        c = (*t).head;
        while !c.is_null() {
            ((*t).free_fn).expect("non-null function pointer")(c);
            c = (*c).next;
        }
    }
    free((*t).table as *mut libc::c_void);
    free(t as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_insert_w_hash(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
    mut v: *const libc::c_void,
    h: libc::c_ulong,
    opts: libc::c_uint,
) -> libc::c_int {
    let mut n: libc::c_ulong = 0;
    if (*t).count as libc::c_double >= (*t).size as libc::c_double * 0.66f64 {
        let mut new_size: libc::c_int = if (*t).size
            > 2147483647 as libc::c_int / 2 as libc::c_int
        {
            2147483647 as libc::c_int
        } else {
            (*t).size * 2 as libc::c_int
        };
        if (*t).size == 2147483647 as libc::c_int
            || lh_table_resize(t, new_size) != 0 as libc::c_int
        {
            return -(1 as libc::c_int);
        }
    }
    n = h.wrapping_rem((*t).size as libc::c_ulong);
    while !((*((*t).table).offset(n as isize)).k
        == -(1 as libc::c_int) as *mut libc::c_void as *const libc::c_void
        || (*((*t).table).offset(n as isize)).k
            == -(2 as libc::c_int) as *mut libc::c_void as *const libc::c_void)
    {
        n = n.wrapping_add(1);
        if n as libc::c_int == (*t).size {
            n = 0 as libc::c_int as libc::c_ulong;
        }
    }
    let ref mut fresh2 = (*((*t).table).offset(n as isize)).k;
    *fresh2 = k;
    (*((*t).table).offset(n as isize))
        .k_is_constant = (opts
        & ((1 as libc::c_int) << 2 as libc::c_int) as libc::c_uint) as libc::c_int;
    let ref mut fresh3 = (*((*t).table).offset(n as isize)).v;
    *fresh3 = v;
    (*t).count += 1;
    (*t).count;
    if ((*t).head).is_null() {
        (*t).tail = &mut *((*t).table).offset(n as isize) as *mut lh_entry;
        (*t).head = (*t).tail;
        let ref mut fresh4 = (*((*t).table).offset(n as isize)).prev;
        *fresh4 = 0 as *mut lh_entry;
        let ref mut fresh5 = (*((*t).table).offset(n as isize)).next;
        *fresh5 = *fresh4;
    } else {
        (*(*t).tail).next = &mut *((*t).table).offset(n as isize) as *mut lh_entry;
        let ref mut fresh6 = (*((*t).table).offset(n as isize)).prev;
        *fresh6 = (*t).tail;
        let ref mut fresh7 = (*((*t).table).offset(n as isize)).next;
        *fresh7 = 0 as *mut lh_entry;
        (*t).tail = &mut *((*t).table).offset(n as isize) as *mut lh_entry;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_insert(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
    mut v: *const libc::c_void,
) -> libc::c_int {
    return lh_table_insert_w_hash(
        t,
        k,
        v,
        lh_get_hash(t, k),
        0 as libc::c_int as libc::c_uint,
    );
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_lookup_entry_w_hash(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
    h: libc::c_ulong,
) -> *mut lh_entry {
    let mut n: libc::c_ulong = h.wrapping_rem((*t).size as libc::c_ulong);
    let mut count: libc::c_int = 0 as libc::c_int;
    while count < (*t).size {
        if (*((*t).table).offset(n as isize)).k
            == -(1 as libc::c_int) as *mut libc::c_void as *const libc::c_void
        {
            return 0 as *mut lh_entry;
        }
        if (*((*t).table).offset(n as isize)).k
            != -(2 as libc::c_int) as *mut libc::c_void as *const libc::c_void
            && ((*t).equal_fn)
                .expect(
                    "non-null function pointer",
                )((*((*t).table).offset(n as isize)).k, k) != 0
        {
            return &mut *((*t).table).offset(n as isize) as *mut lh_entry;
        }
        n = n.wrapping_add(1);
        if n as libc::c_int == (*t).size {
            n = 0 as libc::c_int as libc::c_ulong;
        }
        count += 1;
        count;
    }
    return 0 as *mut lh_entry;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_lookup_entry(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
) -> *mut lh_entry {
    return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_lookup_ex(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
    mut v: *mut *mut libc::c_void,
) -> json_bool {
    let mut e: *mut lh_entry = lh_table_lookup_entry(t, k);
    if !e.is_null() {
        if !v.is_null() {
            *v = lh_entry_v(e);
        }
        return 1 as libc::c_int;
    }
    if !v.is_null() {
        *v = 0 as *mut libc::c_void;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_delete_entry(
    mut t: *mut lh_table,
    mut e: *mut lh_entry,
) -> libc::c_int {
    let mut n: ptrdiff_t = e.offset_from((*t).table) as libc::c_long;
    if n < 0 as libc::c_int as ptrdiff_t {
        return -(2 as libc::c_int);
    }
    if (*((*t).table).offset(n as isize)).k
        == -(1 as libc::c_int) as *mut libc::c_void as *const libc::c_void
        || (*((*t).table).offset(n as isize)).k
            == -(2 as libc::c_int) as *mut libc::c_void as *const libc::c_void
    {
        return -(1 as libc::c_int);
    }
    (*t).count -= 1;
    (*t).count;
    if ((*t).free_fn).is_some() {
        ((*t).free_fn).expect("non-null function pointer")(e);
    }
    let ref mut fresh8 = (*((*t).table).offset(n as isize)).v;
    *fresh8 = 0 as *const libc::c_void;
    let ref mut fresh9 = (*((*t).table).offset(n as isize)).k;
    *fresh9 = -(2 as libc::c_int) as *mut libc::c_void;
    if (*t).tail == &mut *((*t).table).offset(n as isize) as *mut lh_entry
        && (*t).head == &mut *((*t).table).offset(n as isize) as *mut lh_entry
    {
        (*t).tail = 0 as *mut lh_entry;
        (*t).head = (*t).tail;
    } else if (*t).head == &mut *((*t).table).offset(n as isize) as *mut lh_entry {
        (*(*(*t).head).next).prev = 0 as *mut lh_entry;
        (*t).head = (*(*t).head).next;
    } else if (*t).tail == &mut *((*t).table).offset(n as isize) as *mut lh_entry {
        (*(*(*t).tail).prev).next = 0 as *mut lh_entry;
        (*t).tail = (*(*t).tail).prev;
    } else {
        let ref mut fresh10 = (*(*((*t).table).offset(n as isize)).prev).next;
        *fresh10 = (*((*t).table).offset(n as isize)).next;
        let ref mut fresh11 = (*(*((*t).table).offset(n as isize)).next).prev;
        *fresh11 = (*((*t).table).offset(n as isize)).prev;
    }
    let ref mut fresh12 = (*((*t).table).offset(n as isize)).prev;
    *fresh12 = 0 as *mut lh_entry;
    let ref mut fresh13 = (*((*t).table).offset(n as isize)).next;
    *fresh13 = *fresh12;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_delete(
    mut t: *mut lh_table,
    mut k: *const libc::c_void,
) -> libc::c_int {
    let mut e: *mut lh_entry = lh_table_lookup_entry(t, k);
    if e.is_null() {
        return -(1 as libc::c_int);
    }
    return lh_table_delete_entry(t, e);
}
#[no_mangle]
pub unsafe extern "C" fn lh_table_length(mut t: *mut lh_table) -> libc::c_int {
    return (*t).count;
}
