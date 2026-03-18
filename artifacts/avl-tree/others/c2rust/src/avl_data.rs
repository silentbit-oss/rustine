use ::libc;
extern "C" {
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct mydata {
    pub key: libc::c_int,
}
#[no_mangle]
pub unsafe extern "C" fn makedata(mut key: libc::c_int) -> *mut mydata {
    let mut p: *mut mydata = 0 as *mut mydata;
    p = malloc(::core::mem::size_of::<mydata>() as libc::c_ulong) as *mut mydata;
    if !p.is_null() {
        (*p).key = key;
    }
    return p;
}
#[no_mangle]
pub unsafe extern "C" fn compare_func(
    mut d1: *const libc::c_void,
    mut d2: *const libc::c_void,
) -> libc::c_int {
    let mut p1: *mut mydata = 0 as *mut mydata;
    let mut p2: *mut mydata = 0 as *mut mydata;
    if !d1.is_null() {} else {
        __assert_fail(
            b"d1 != NULL\0" as *const u8 as *const libc::c_char,
            b"avl_data.c\0" as *const u8 as *const libc::c_char,
            26 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 45],
                &[libc::c_char; 45],
            >(b"int compare_func(const void *, const void *)\0"))
                .as_ptr(),
        );
    }
    'c_1715: {
        if !d1.is_null() {} else {
            __assert_fail(
                b"d1 != NULL\0" as *const u8 as *const libc::c_char,
                b"avl_data.c\0" as *const u8 as *const libc::c_char,
                26 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 45],
                    &[libc::c_char; 45],
                >(b"int compare_func(const void *, const void *)\0"))
                    .as_ptr(),
            );
        }
    };
    if !d2.is_null() {} else {
        __assert_fail(
            b"d2 != NULL\0" as *const u8 as *const libc::c_char,
            b"avl_data.c\0" as *const u8 as *const libc::c_char,
            27 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 45],
                &[libc::c_char; 45],
            >(b"int compare_func(const void *, const void *)\0"))
                .as_ptr(),
        );
    }
    'c_1669: {
        if !d2.is_null() {} else {
            __assert_fail(
                b"d2 != NULL\0" as *const u8 as *const libc::c_char,
                b"avl_data.c\0" as *const u8 as *const libc::c_char,
                27 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 45],
                    &[libc::c_char; 45],
                >(b"int compare_func(const void *, const void *)\0"))
                    .as_ptr(),
            );
        }
    };
    p1 = d1 as *mut mydata;
    p2 = d2 as *mut mydata;
    if (*p1).key == (*p2).key {
        return 0 as libc::c_int
    } else if (*p1).key > (*p2).key {
        return 1 as libc::c_int
    } else {
        return -(1 as libc::c_int)
    };
}
#[no_mangle]
pub unsafe extern "C" fn destroy_func(mut d: *mut libc::c_void) {
    let mut p: *mut mydata = 0 as *mut mydata;
    if !d.is_null() {} else {
        __assert_fail(
            b"d != NULL\0" as *const u8 as *const libc::c_char,
            b"avl_data.c\0" as *const u8 as *const libc::c_char,
            43 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 26],
                &[libc::c_char; 26],
            >(b"void destroy_func(void *)\0"))
                .as_ptr(),
        );
    }
    'c_1777: {
        if !d.is_null() {} else {
            __assert_fail(
                b"d != NULL\0" as *const u8 as *const libc::c_char,
                b"avl_data.c\0" as *const u8 as *const libc::c_char,
                43 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 26],
                    &[libc::c_char; 26],
                >(b"void destroy_func(void *)\0"))
                    .as_ptr(),
            );
        }
    };
    p = d as *mut mydata;
    free(p as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn print_func(mut d: *mut libc::c_void) {
    let mut p: *mut mydata = 0 as *mut mydata;
    if !d.is_null() {} else {
        __assert_fail(
            b"d != NULL\0" as *const u8 as *const libc::c_char,
            b"avl_data.c\0" as *const u8 as *const libc::c_char,
            53 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 24],
                &[libc::c_char; 24],
            >(b"void print_func(void *)\0"))
                .as_ptr(),
        );
    }
    'c_1843: {
        if !d.is_null() {} else {
            __assert_fail(
                b"d != NULL\0" as *const u8 as *const libc::c_char,
                b"avl_data.c\0" as *const u8 as *const libc::c_char,
                53 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 24],
                    &[libc::c_char; 24],
                >(b"void print_func(void *)\0"))
                    .as_ptr(),
            );
        }
    };
    p = d as *mut mydata;
    printf(b"%d\0" as *const u8 as *const libc::c_char, (*p).key);
}
#[no_mangle]
pub unsafe extern "C" fn print_char_func(mut d: *mut libc::c_void) {
    let mut p: *mut mydata = 0 as *mut mydata;
    if !d.is_null() {} else {
        __assert_fail(
            b"d != NULL\0" as *const u8 as *const libc::c_char,
            b"avl_data.c\0" as *const u8 as *const libc::c_char,
            63 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 29],
                &[libc::c_char; 29],
            >(b"void print_char_func(void *)\0"))
                .as_ptr(),
        );
    }
    'c_1908: {
        if !d.is_null() {} else {
            __assert_fail(
                b"d != NULL\0" as *const u8 as *const libc::c_char,
                b"avl_data.c\0" as *const u8 as *const libc::c_char,
                63 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 29],
                    &[libc::c_char; 29],
                >(b"void print_char_func(void *)\0"))
                    .as_ptr(),
            );
        }
    };
    p = d as *mut mydata;
    printf(b"%c\0" as *const u8 as *const libc::c_char, (*p).key & 127 as libc::c_int);
}
