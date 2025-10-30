use ::libc;
extern "C" {
    
    
    
    
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    static mut stdout: *mut FILE;
    fn fflush(__stream: *mut FILE) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
pub type size_t = libc::c_ulong;
pub type __int32_t = libc::c_int;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor29 { dummy: () }
pub type _IO_lock_t = ();
pub type FILE = crate::src::apps::json_parse::_IO_FILE;
pub type int32_t = __int32_t;
pub type uintptr_t = libc::c_ulong;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor30 { dummy: () }
pub type json_bool = libc::c_int;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor31 { dummy: () }
pub type lh_equal_fn = unsafe extern "C" fn(
    *const libc::c_void,
    *const libc::c_void,
) -> libc::c_int;
pub type lh_hash_fn = unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong;
pub type lh_entry_free_fn = unsafe extern "C" fn(*mut crate::src::json_object::lh_entry) -> ();
#[inline]
unsafe extern "C" fn lh_table_head(mut t: *const crate::src::json_object::lh_table) -> *mut crate::src::json_object::lh_entry {
    return (*t).head;
}
#[inline]
unsafe extern "C" fn lh_entry_k(mut e: *const crate::src::json_object::lh_entry) -> *mut libc::c_void {
    return (*e).k as uintptr_t as *mut libc::c_void;
}
#[inline]
unsafe extern "C" fn lh_entry_v(mut e: *const crate::src::json_object::lh_entry) -> *mut libc::c_void {
    return (*e).v as uintptr_t as *mut libc::c_void;
}
#[inline]
unsafe extern "C" fn lh_entry_next(mut e: *const crate::src::json_object::lh_entry) -> *mut crate::src::json_object::lh_entry {
    return (*e).next;
}
unsafe extern "C" fn sort_fn(
    mut j1: *const libc::c_void,
    mut j2: *const libc::c_void,
) -> libc::c_int {
    let mut jso1: *const *mut crate::src::json_object::json_object = 0 as *const *mut crate::src::json_object::json_object;
    let mut jso2: *const *mut crate::src::json_object::json_object = 0 as *const *mut crate::src::json_object::json_object;
    let mut i1: libc::c_int = 0;
    let mut i2: libc::c_int = 0;
    jso1 = j1 as *const *mut crate::src::json_object::json_object;
    jso2 = j2 as *const *mut crate::src::json_object::json_object;
    if (*jso1).is_null() && (*jso2).is_null() {
        return 0 as libc::c_int;
    }
    if (*jso1).is_null() {std::intrinsics::assume((*jso1).addr() == 0);
        return -(1 as libc::c_int);
    }
    if (*jso2).is_null() {std::intrinsics::assume((*jso2).addr() == 0);
        return 1 as libc::c_int;
    }
    i1 = crate::src::json_object::json_object_get_int(*jso1);
    i2 = crate::src::json_object::json_object_get_int(*jso2);
    return i1 - i2;
}
#[no_mangle]
pub unsafe extern "C" fn make_array() -> *mut crate::src::json_object::json_object {
    let mut my_array: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    my_array = crate::src::json_object::json_object_new_array();
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(1 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(2 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(3 as libc::c_int));
    crate::src::json_object::json_object_array_put_idx(
        my_array,
        4 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(5 as libc::c_int),
    );
    crate::src::json_object::json_object_array_put_idx(
        my_array,
        3 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(4 as libc::c_int),
    );
    crate::src::json_object::json_object_array_put_idx(
        my_array,
        6 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(7 as libc::c_int),
    );
    return my_array;
}
#[no_mangle]
pub unsafe extern "C" fn test_array_del_idx() {
    let mut rc: libc::c_int = 0;
    let mut ii: size_t = 0;
    let mut orig_array_len: size_t = 0;
    let mut my_array: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    my_array = make_array();
    orig_array_len = crate::src::json_object::json_object_array_length(my_array);
    printf(b"my_array=\n\0" as *const u8 as *const libc::c_char);
    ii = 0 as libc::c_int as size_t;
    while ii < crate::src::json_object::json_object_array_length(my_array) {
        let mut obj: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(my_array, ii);
        printf(
            b"\t[%d]=%s\n\0" as *const u8 as *const libc::c_char,
            ii as libc::c_int,
            crate::src::json_object::json_object_to_json_string(obj),
        );
        ii = ii.wrapping_add(1);
        ii;
    }
    printf(
        b"my_array.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    ii = 0 as libc::c_int as size_t;
    while ii < orig_array_len {
        rc = crate::src::json_object::json_object_array_del_idx(
            my_array,
            0 as libc::c_int as size_t,
            1 as libc::c_int as size_t,
        );
        printf(
            b"after del_idx(0,1)=%d, my_array.to_string()=%s\n\0" as *const u8
                as *const libc::c_char,
            rc,
            crate::src::json_object::json_object_to_json_string(my_array),
        );
        ii = ii.wrapping_add(1);
        ii;
    }
    rc = crate::src::json_object::json_object_array_del_idx(
        my_array,
        0 as libc::c_int as size_t,
        1 as libc::c_int as size_t,
    );
    printf(
        b"after del_idx(0,1)=%d, my_array.to_string()=%s\n\0" as *const u8
            as *const libc::c_char,
        rc,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_put(my_array);
    my_array = make_array();
    rc = crate::src::json_object::json_object_array_del_idx(my_array, 0 as libc::c_int as size_t, orig_array_len);
    printf(
        b"after del_idx(0,%d)=%d, my_array.to_string()=%s\n\0" as *const u8
            as *const libc::c_char,
        orig_array_len as libc::c_int,
        rc,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_put(my_array);
    my_array = make_array();
    rc = crate::src::json_object::json_object_array_del_idx(
        my_array,
        0 as libc::c_int as size_t,
        orig_array_len.wrapping_add(1 as libc::c_int as size_t),
    );
    printf(
        b"after del_idx(0,%d)=%d, my_array.to_string()=%s\n\0" as *const u8
            as *const libc::c_char,
        orig_array_len.wrapping_add(1 as libc::c_int as size_t) as libc::c_int,
        rc,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_put(my_array);
    my_array = make_array();
    rc = crate::src::json_object::json_object_array_del_idx(
        my_array,
        0 as libc::c_int as size_t,
        orig_array_len.wrapping_sub(1 as libc::c_int as size_t),
    );
    printf(
        b"after del_idx(0,%d)=%d, my_array.to_string()=%s\n\0" as *const u8
            as *const libc::c_char,
        orig_array_len.wrapping_sub(1 as libc::c_int as size_t) as libc::c_int,
        rc,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_array_add(
        my_array,
        crate::src::json_object::json_object_new_string(b"s1\0" as *const u8 as *const libc::c_char),
    );
    crate::src::json_object::json_object_array_add(
        my_array,
        crate::src::json_object::json_object_new_string(b"s2\0" as *const u8 as *const libc::c_char),
    );
    crate::src::json_object::json_object_array_add(
        my_array,
        crate::src::json_object::json_object_new_string(b"s3\0" as *const u8 as *const libc::c_char),
    );
    printf(
        b"after adding more entries, my_array.to_string()=%s\n\0" as *const u8
            as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_put(my_array);
}
#[no_mangle]
pub unsafe extern "C" fn test_array_list_expand_internal() {
    let mut rc: libc::c_int = 0;
    let mut ii: size_t = 0;
    let mut idx: size_t = 0;
    let mut my_array: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    my_array = make_array();
    printf(b"my_array=\n\0" as *const u8 as *const libc::c_char);
    ii = 0 as libc::c_int as size_t;
    while ii < crate::src::json_object::json_object_array_length(my_array) {
        let mut obj: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(my_array, ii);
        printf(
            b"\t[%d]=%s\n\0" as *const u8 as *const libc::c_char,
            ii as libc::c_int,
            crate::src::json_object::json_object_to_json_string(obj),
        );
        ii = ii.wrapping_add(1);
        ii;
    }
    printf(
        b"my_array.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    rc = crate::src::json_object::json_object_array_put_idx(
        my_array,
        5 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(6 as libc::c_int),
    );
    printf(b"put_idx(5,6)=%d\n\0" as *const u8 as *const libc::c_char, rc);
    idx = (32 as libc::c_int * 2 as libc::c_int - 1 as libc::c_int) as size_t;
    rc = crate::src::json_object::json_object_array_put_idx(my_array, idx, crate::src::json_object::json_object_new_int(0 as libc::c_int));
    printf(
        b"put_idx(%d,0)=%d\n\0" as *const u8 as *const libc::c_char,
        idx as libc::c_int,
        rc,
    );
    idx = (32 as libc::c_int * 2 as libc::c_int * 2 as libc::c_int + 1 as libc::c_int)
        as size_t;
    rc = crate::src::json_object::json_object_array_put_idx(my_array, idx, crate::src::json_object::json_object_new_int(0 as libc::c_int));
    printf(
        b"put_idx(%d,0)=%d\n\0" as *const u8 as *const libc::c_char,
        idx as libc::c_int,
        rc,
    );
    idx = 18446744073709551615 as libc::c_ulong;
    let mut tmp: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_int(10 as libc::c_int);
    rc = crate::src::json_object::json_object_array_put_idx(my_array, idx, tmp);
    printf(b"put_idx(SIZE_T_MAX,0)=%d\n\0" as *const u8 as *const libc::c_char, rc);
    if rc == -(1 as libc::c_int) {
        crate::src::json_object::json_object_put(tmp);
    }
    crate::src::json_object::json_object_put(my_array);
}
#[no_mangle]
pub unsafe extern "C" fn test_array_insert_idx() {
    let mut my_array: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut jo1: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    my_array = crate::src::json_object::json_object_new_array();
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(1 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(2 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(5 as libc::c_int));
    crate::src::json_object::json_object_array_insert_idx(
        my_array,
        2 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(4 as libc::c_int),
    );
    jo1 = crate::src::json_tokener::json_tokener_parse(b"[1, 2, 4, 5]\0" as *const u8 as *const libc::c_char);
    if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
        __assert_fail(
            b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                as *const u8 as *const libc::c_char,
            205 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 33],
                &[libc::c_char; 33],
            >(b"void test_array_insert_idx(void)\0"))
                .as_ptr(),
        );
    }
    'c_4070: {
        if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
            __assert_fail(
                b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                    as *const u8 as *const libc::c_char,
                205 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 33],
                    &[libc::c_char; 33],
                >(b"void test_array_insert_idx(void)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(jo1);
    crate::src::json_object::json_object_array_insert_idx(
        my_array,
        2 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(3 as libc::c_int),
    );
    jo1 = crate::src::json_tokener::json_tokener_parse(b"[1, 2, 3, 4, 5]\0" as *const u8 as *const libc::c_char);
    if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
        __assert_fail(
            b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                as *const u8 as *const libc::c_char,
            211 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 33],
                &[libc::c_char; 33],
            >(b"void test_array_insert_idx(void)\0"))
                .as_ptr(),
        );
    }
    'c_4000: {
        if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
            __assert_fail(
                b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                    as *const u8 as *const libc::c_char,
                211 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 33],
                    &[libc::c_char; 33],
                >(b"void test_array_insert_idx(void)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(jo1);
    crate::src::json_object::json_object_array_insert_idx(
        my_array,
        5 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(6 as libc::c_int),
    );
    jo1 = crate::src::json_tokener::json_tokener_parse(
        b"[1, 2, 3, 4, 5, 6]\0" as *const u8 as *const libc::c_char,
    );
    if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
        __assert_fail(
            b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                as *const u8 as *const libc::c_char,
            217 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 33],
                &[libc::c_char; 33],
            >(b"void test_array_insert_idx(void)\0"))
                .as_ptr(),
        );
    }
    'c_3930: {
        if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
            __assert_fail(
                b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                    as *const u8 as *const libc::c_char,
                217 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 33],
                    &[libc::c_char; 33],
                >(b"void test_array_insert_idx(void)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(jo1);
    crate::src::json_object::json_object_array_insert_idx(
        my_array,
        7 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(8 as libc::c_int),
    );
    jo1 = crate::src::json_tokener::json_tokener_parse(
        b"[1, 2, 3, 4, 5, 6, null, 8]\0" as *const u8 as *const libc::c_char,
    );
    if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
        __assert_fail(
            b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                as *const u8 as *const libc::c_char,
            222 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 33],
                &[libc::c_char; 33],
            >(b"void test_array_insert_idx(void)\0"))
                .as_ptr(),
        );
    }
    'c_3855: {
        if 1 as libc::c_int == crate::src::json_object::json_object_equal(my_array, jo1) {} else {
            __assert_fail(
                b"1 == json_object_equal(my_array, jo1)\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test1.c\0"
                    as *const u8 as *const libc::c_char,
                222 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 33],
                    &[libc::c_char; 33],
                >(b"void test_array_insert_idx(void)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(jo1);
    crate::src::json_object::json_object_put(my_array);
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut my_string: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut my_int: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut my_null: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut my_object: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut my_array: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut i: size_t = 0;
    my_string = crate::src::json_object::json_object_new_string(b"\t\0" as *const u8 as *const libc::c_char);
    printf(
        b"my_string=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_string(my_string),
    );
    printf(
        b"my_string.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_string),
    );
    crate::src::json_object::json_object_put(my_string);
    my_string = crate::src::json_object::json_object_new_string(b"\\\0" as *const u8 as *const libc::c_char);
    printf(
        b"my_string=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_string(my_string),
    );
    printf(
        b"my_string.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_string),
    );
    crate::src::json_object::json_object_put(my_string);
    my_string = crate::src::json_object::json_object_new_string(b"/\0" as *const u8 as *const libc::c_char);
    printf(
        b"my_string=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_string(my_string),
    );
    printf(
        b"my_string.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_string),
    );
    printf(
        b"my_string.to_string(NOSLASHESCAPE)=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(my_string, (1 as libc::c_int) << 4 as libc::c_int),
    );
    crate::src::json_object::json_object_put(my_string);
    my_string = crate::src::json_object::json_object_new_string(
        b"/foo/bar/baz\0" as *const u8 as *const libc::c_char,
    );
    printf(
        b"my_string=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_string(my_string),
    );
    printf(
        b"my_string.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_string),
    );
    printf(
        b"my_string.to_string(NOSLASHESCAPE)=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(my_string, (1 as libc::c_int) << 4 as libc::c_int),
    );
    crate::src::json_object::json_object_put(my_string);
    my_string = crate::src::json_object::json_object_new_string(b"foo\0" as *const u8 as *const libc::c_char);
    printf(
        b"my_string=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_string(my_string),
    );
    printf(
        b"my_string.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_string),
    );
    my_int = crate::src::json_object::json_object_new_int(9 as libc::c_int);
    printf(
        b"my_int=%d\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_get_int(my_int),
    );
    printf(
        b"my_int.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_int),
    );
    my_null = crate::src::json_object::json_object_new_null();
    printf(
        b"my_null.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_null),
    );
    my_array = crate::src::json_object::json_object_new_array();
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(1 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(2 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(3 as libc::c_int));
    crate::src::json_object::json_object_array_put_idx(
        my_array,
        4 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(5 as libc::c_int),
    );
    printf(b"my_array=\n\0" as *const u8 as *const libc::c_char);
    i = 0 as libc::c_int as size_t;
    while i < crate::src::json_object::json_object_array_length(my_array) {
        let mut obj: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(my_array, i);
        printf(
            b"\t[%d]=%s\n\0" as *const u8 as *const libc::c_char,
            i as libc::c_int,
            crate::src::json_object::json_object_to_json_string(obj),
        );
        i = i.wrapping_add(1);
        i;
    }
    printf(
        b"my_array.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_put(my_array);
    test_array_insert_idx();
    test_array_del_idx();
    test_array_list_expand_internal();
    my_array = crate::src::json_object::json_object_new_array_ext(5 as libc::c_int);
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(3 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(1 as libc::c_int));
    crate::src::json_object::json_object_array_add(my_array, crate::src::json_object::json_object_new_int(2 as libc::c_int));
    crate::src::json_object::json_object_array_put_idx(
        my_array,
        4 as libc::c_int as size_t,
        crate::src::json_object::json_object_new_int(0 as libc::c_int),
    );
    printf(b"my_array=\n\0" as *const u8 as *const libc::c_char);
    i = 0 as libc::c_int as size_t;
    while i < crate::src::json_object::json_object_array_length(my_array) {
        let mut obj_0: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(my_array, i);
        printf(
            b"\t[%d]=%s\n\0" as *const u8 as *const libc::c_char,
            i as libc::c_int,
            crate::src::json_object::json_object_to_json_string(obj_0),
        );
        i = i.wrapping_add(1);
        i;
    }
    printf(
        b"my_array.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    crate::src::json_object::json_object_array_sort(
        my_array,
        Some(
            sort_fn
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
    );
    printf(b"my_array=\n\0" as *const u8 as *const libc::c_char);
    i = 0 as libc::c_int as size_t;
    while i < crate::src::json_object::json_object_array_length(my_array) {
        let mut obj_1: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(my_array, i);
        printf(
            b"\t[%d]=%s\n\0" as *const u8 as *const libc::c_char,
            i as libc::c_int,
            crate::src::json_object::json_object_to_json_string(obj_1),
        );
        i = i.wrapping_add(1);
        i;
    }
    printf(
        b"my_array.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_array),
    );
    let mut one: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_int(1 as libc::c_int);
    let mut result: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_bsearch(
        one,
        my_array,
        Some(
            sort_fn
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
    );
    printf(
        b"find json_object(1) in my_array successfully: %s\n\0" as *const u8
            as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(result),
    );
    crate::src::json_object::json_object_put(one);
    my_object = crate::src::json_object::json_object_new_object();
    let mut rc: libc::c_int = crate::src::json_object::json_object_object_add(
        my_object,
        b"abc\0" as *const u8 as *const libc::c_char,
        my_object,
    );
    if rc != -(1 as libc::c_int) {
        printf(
            b"ERROR: able to successfully add object to itself!\n\0" as *const u8
                as *const libc::c_char,
        );
        fflush(stdout);
    }
    crate::src::json_object::json_object_object_add(
        my_object,
        b"abc\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_new_int(12 as libc::c_int),
    );
    crate::src::json_object::json_object_object_add(
        my_object,
        b"foo\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_new_string(b"bar\0" as *const u8 as *const libc::c_char),
    );
    crate::src::json_object::json_object_object_add(
        my_object,
        b"bool0\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_new_boolean(0 as libc::c_int),
    );
    crate::src::json_object::json_object_object_add(
        my_object,
        b"bool1\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_new_boolean(1 as libc::c_int),
    );
    crate::src::json_object::json_object_object_add(
        my_object,
        b"baz\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_new_string(b"bang\0" as *const u8 as *const libc::c_char),
    );
    let mut baz_obj: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_string(
        b"fark\0" as *const u8 as *const libc::c_char,
    );
    crate::src::json_object::json_object_get(baz_obj);
    crate::src::json_object::json_object_object_add(
        my_object,
        b"baz\0" as *const u8 as *const libc::c_char,
        baz_obj,
    );
    crate::src::json_object::json_object_object_del(my_object, b"baz\0" as *const u8 as *const libc::c_char);
    printf(
        b"baz_obj.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(baz_obj),
    );
    crate::src::json_object::json_object_put(baz_obj);
    printf(b"my_object=\n\0" as *const u8 as *const libc::c_char);
    let mut key: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut val: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut entrykey: *mut crate::src::json_object::lh_entry = lh_table_head(crate::src::json_object::json_object_get_object(my_object));
    let mut entry_nextkey: *mut crate::src::json_object::lh_entry = 0 as *mut crate::src::json_object::lh_entry;
    while !({
        if !entrykey.is_null() {
            key = lh_entry_k(entrykey) as *mut libc::c_char;
            val = lh_entry_v(entrykey) as *mut crate::src::json_object::json_object;
            entry_nextkey = lh_entry_next(entrykey);
        }
        entrykey
    })
        .is_null()
    {
        printf(
            b"\t%s: %s\n\0" as *const u8 as *const libc::c_char,
            key,
            crate::src::json_object::json_object_to_json_string(val),
        );
        entrykey = entry_nextkey;
    }std::intrinsics::assume(({
        if !entrykey.is_null()
                {
                        key = lh_entry_k(entrykey) as *mut libc::c_char;
                        val = lh_entry_v(entrykey) as *mut crate::src::json_object::json_object;
                        entry_nextkey = lh_entry_next(entrykey);
                    }
                entrykey
            }).addr() == 0);
    let mut empty_array: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_array();
    let mut empty_obj: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_object();
    crate::src::json_object::json_object_object_add(
        my_object,
        b"empty_array\0" as *const u8 as *const libc::c_char,
        empty_array,
    );
    crate::src::json_object::json_object_object_add(
        my_object,
        b"empty_obj\0" as *const u8 as *const libc::c_char,
        empty_obj,
    );
    printf(
        b"my_object.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string(my_object),
    );
    crate::src::json_object::json_object_put(my_array);
    my_array = crate::src::json_object::json_object_new_array_ext(
        -(2147483647 as libc::c_int) - 1 as libc::c_int + 1 as libc::c_int,
    );
    if !my_array.is_null() {
        printf(
            b"ERROR: able to allocate an array of negative size!\n\0" as *const u8
                as *const libc::c_char,
        );
        fflush(stdout);
        crate::src::json_object::json_object_put(my_array);
        my_array = 0 as *mut crate::src::json_object::json_object;
    }else { std::intrinsics::assume((my_array).addr() == 0); }
    crate::src::json_object::json_object_put(my_string);
    crate::src::json_object::json_object_put(my_int);
    crate::src::json_object::json_object_put(my_null);
    crate::src::json_object::json_object_put(my_object);
    crate::src::json_object::json_object_put(my_array);
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in &raw mut ::std::env::args() {
        args.push(
            (::std::ffi::CString::new(arg))
                .expect("Failed to convert argument into CString.")
                .into_raw(),
        );
    }
    args.push(::core::ptr::null_mut());
    unsafe {
        ::std::process::exit(
            main_0(
                (args.len() - 1) as libc::c_int,
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
