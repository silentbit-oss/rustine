use ::libc;
extern "C" {
    
    
    
    
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
pub type size_t = libc::c_ulong;
pub type __int32_t = libc::c_int;
pub type __int64_t = libc::c_long;
pub type __uint64_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor49 { dummy: () }
pub type _IO_lock_t = ();
pub type FILE = crate::src::apps::json_parse::_IO_FILE;
pub type int32_t = __int32_t;
pub type int64_t = __int64_t;
pub type uint64_t = __uint64_t;
pub type json_bool = libc::c_int;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut tmp: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_int(123 as libc::c_int);
    if crate::src::json_object::json_object_get_int(tmp) == 123 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == 123\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            13 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_5260: {
        if crate::src::json_object::json_object_get_int(tmp) == 123 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == 123\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                13 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_int(tmp, 321 as libc::c_int);
    if crate::src::json_object::json_object_get_int(tmp) == 321 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == 321\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            15 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_5209: {
        if crate::src::json_object::json_object_get_int(tmp) == 321 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == 321\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                15 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    printf(b"INT PASSED\n\0" as *const u8 as *const libc::c_char);
    crate::src::json_object::json_object_set_int64(tmp, 321321321 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 321321321 as libc::c_int as int64_t {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == 321321321\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            18 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_5149: {
        if crate::src::json_object::json_object_get_int64(tmp) == 321321321 as libc::c_int as int64_t {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == 321321321\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                18 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT64 PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_uint64(123 as libc::c_int as uint64_t);
    if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_boolean(tmp) == 1\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            22 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_5086: {
        if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_boolean(tmp) == 1\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                22 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_int(tmp) == 123 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == 123\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            23 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_5041: {
        if crate::src::json_object::json_object_get_int(tmp) == 123 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == 123\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                23 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_int64(tmp) == 123 as libc::c_int as int64_t {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == 123\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            24 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4995: {
        if crate::src::json_object::json_object_get_int64(tmp) == 123 as libc::c_int as int64_t {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == 123\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                24 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 123 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 123\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            25 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4949: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 123 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 123\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                25 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_double(tmp) == 123.000000f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 123.000000\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            26 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4905: {
        if crate::src::json_object::json_object_get_double(tmp) == 123.000000f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 123.000000\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                26 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_uint64(tmp, 321321321 as libc::c_int as uint64_t);
    if crate::src::json_object::json_object_get_uint64(tmp) == 321321321 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 321321321\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            28 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4851: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 321321321 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 321321321\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                28 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_uint64(tmp, 9223372036854775808 as libc::c_ulong);
    if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            30 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4798: {
        if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                30 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 9223372036854775808 as libc::c_ulong {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 9223372036854775808U\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            31 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4753: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 9223372036854775808 as libc::c_ulong {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 9223372036854775808U\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                31 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"UINT64 PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_boolean(1 as libc::c_int);
    if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_boolean(tmp) == 1\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            35 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4692: {
        if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_boolean(tmp) == 1\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                35 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_boolean(tmp, 0 as libc::c_int);
    if crate::src::json_object::json_object_get_boolean(tmp) == 0 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_boolean(tmp) == 0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            37 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4642: {
        if crate::src::json_object::json_object_get_boolean(tmp) == 0 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_boolean(tmp) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                37 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_boolean(tmp, 1 as libc::c_int);
    if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_boolean(tmp) == 1\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            39 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4589: {
        if crate::src::json_object::json_object_get_boolean(tmp) == 1 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_boolean(tmp) == 1\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                39 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"BOOL PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_double(12.34f64);
    if crate::src::json_object::json_object_get_double(tmp) == 12.34f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 12.34\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            43 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4528: {
        if crate::src::json_object::json_object_get_double(tmp) == 12.34f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 12.34\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                43 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_double(tmp, 34.56f64);
    if crate::src::json_object::json_object_get_double(tmp) == 34.56f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 34.56\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            45 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4477: {
        if crate::src::json_object::json_object_get_double(tmp) == 34.56f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 34.56\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                45 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_double(tmp, 6435.34f64);
    if crate::src::json_object::json_object_get_double(tmp) == 6435.34f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 6435.34\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            47 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4426: {
        if crate::src::json_object::json_object_get_double(tmp) == 6435.34f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 6435.34\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                47 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_double(tmp, 2e21f64);
    if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            49 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4374: {
        if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                49 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            50 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4328: {
        if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                50 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 18446744073709551615 as libc::c_ulong {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == UINT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            51 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4282: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 18446744073709551615 as libc::c_ulong {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == UINT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                51 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_double(tmp, -2e21f64);
    if crate::src::json_object::json_object_get_int(tmp) == -(2147483647 as libc::c_int) - 1 as libc::c_int
    {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == INT32_MIN\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            53 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4221: {
        if crate::src::json_object::json_object_get_int(tmp) == -(2147483647 as libc::c_int) - 1 as libc::c_int
        {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == INT32_MIN\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                53 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_int64(tmp)
        == -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
    {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MIN\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            54 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4165: {
        if crate::src::json_object::json_object_get_int64(tmp)
            == -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
        {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MIN\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                54 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 0 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            55 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4117: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 0 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                55 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"DOUBLE PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_string(b"A MID STRING\0" as *const u8 as *const libc::c_char);
    if strcmp(
        crate::src::json_object::json_object_get_string(tmp),
        b"A MID STRING\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_get_string(tmp), MID) == 0\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            63 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4045: {
        if strcmp(
            crate::src::json_object::json_object_get_string(tmp),
            b"A MID STRING\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_get_string(tmp), MID) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                63 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if strcmp(
        crate::src::json_object::json_object_to_json_string(tmp),
        b"\"A MID STRING\"\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_to_json_string(tmp), \"\\\"\" MID \"\\\"\") == 0\0"
                as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            64 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3992: {
        if strcmp(
            crate::src::json_object::json_object_to_json_string(tmp),
            b"\"A MID STRING\"\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_to_json_string(tmp), \"\\\"\" MID \"\\\"\") == 0\0"
                    as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                64 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"SHORT\0" as *const u8 as *const libc::c_char);
    if strcmp(
        crate::src::json_object::json_object_get_string(tmp),
        b"SHORT\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_get_string(tmp), SHORT) == 0\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            66 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3933: {
        if strcmp(
            crate::src::json_object::json_object_get_string(tmp),
            b"SHORT\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_get_string(tmp), SHORT) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                66 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if strcmp(
        crate::src::json_object::json_object_to_json_string(tmp),
        b"\"SHORT\"\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_to_json_string(tmp), \"\\\"\" SHORT \"\\\"\") == 0\0"
                as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            67 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3881: {
        if strcmp(
            crate::src::json_object::json_object_to_json_string(tmp),
            b"\"SHORT\"\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_to_json_string(tmp), \"\\\"\" SHORT \"\\\"\") == 0\0"
                    as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                67 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(
        tmp,
        b"A string longer than 32 chars as to check non local buf codepath\0"
            as *const u8 as *const libc::c_char,
    );
    if strcmp(
        crate::src::json_object::json_object_get_string(tmp),
        b"A string longer than 32 chars as to check non local buf codepath\0"
            as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_get_string(tmp), HUGE) == 0\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            69 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3821: {
        if strcmp(
            crate::src::json_object::json_object_get_string(tmp),
            b"A string longer than 32 chars as to check non local buf codepath\0"
                as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_get_string(tmp), HUGE) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                69 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if strcmp(
        crate::src::json_object::json_object_to_json_string(tmp),
        b"\"A string longer than 32 chars as to check non local buf codepath\"\0"
            as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_to_json_string(tmp), \"\\\"\" HUGE \"\\\"\") == 0\0"
                as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            70 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3767: {
        if strcmp(
            crate::src::json_object::json_object_to_json_string(tmp),
            b"\"A string longer than 32 chars as to check non local buf codepath\"\0"
                as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_to_json_string(tmp), \"\\\"\" HUGE \"\\\"\") == 0\0"
                    as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                70 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"SHORT\0" as *const u8 as *const libc::c_char);
    if strcmp(
        crate::src::json_object::json_object_get_string(tmp),
        b"SHORT\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_get_string(tmp), SHORT) == 0\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            72 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3706: {
        if strcmp(
            crate::src::json_object::json_object_get_string(tmp),
            b"SHORT\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_get_string(tmp), SHORT) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                72 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if strcmp(
        crate::src::json_object::json_object_to_json_string(tmp),
        b"\"SHORT\"\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strcmp(json_object_to_json_string(tmp), \"\\\"\" SHORT \"\\\"\") == 0\0"
                as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            73 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3652: {
        if strcmp(
            crate::src::json_object::json_object_to_json_string(tmp),
            b"\"SHORT\"\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strcmp(json_object_to_json_string(tmp), \"\\\"\" SHORT \"\\\"\") == 0\0"
                    as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                73 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"\0" as *const u8 as *const libc::c_char);
    crate::src::json_object::json_object_set_string(
        tmp,
        b"A string longer than 32 chars as to check non local buf codepath\0"
            as *const u8 as *const libc::c_char,
    );
    crate::src::json_object::json_object_set_string(tmp, b"\0" as *const u8 as *const libc::c_char);
    crate::src::json_object::json_object_set_string(
        tmp,
        b"A string longer than 32 chars as to check non local buf codepath\0"
            as *const u8 as *const libc::c_char,
    );
    crate::src::json_object::json_object_put(tmp);
    printf(b"STRING PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_string(b"STR\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 0.0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            92 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3558: {
        if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 0.0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                92 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"123.123\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 123.123000f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 123.123000\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            94 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3505: {
        if crate::src::json_object::json_object_get_double(tmp) == 123.123000f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 123.123000\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                94 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"12E+3\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 12000.000000f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 12000.000000\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            96 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3452: {
        if crate::src::json_object::json_object_get_double(tmp) == 12000.000000f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 12000.000000\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                96 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"123.123STR\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 0.0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            98 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3399: {
        if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 0.0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                98 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"1.8E+308\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 0.0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            100 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3346: {
        if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 0.0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                100 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_set_string(tmp, b"-1.8E+308\0" as *const u8 as *const libc::c_char);
    if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
        __assert_fail(
            b"json_object_get_double(tmp) == 0.0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            102 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3290: {
        if crate::src::json_object::json_object_get_double(tmp) == 0.0f64 {} else {
            __assert_fail(
                b"json_object_get_double(tmp) == 0.0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                102 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"STRINGTODOUBLE PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_tokener::json_tokener_parse(b"1.234\0" as *const u8 as *const libc::c_char);
    crate::src::json_object::json_object_set_double(tmp, 12.3f64);
    let mut serialized: *const libc::c_char = crate::src::json_object::json_object_to_json_string(tmp);
    fprintf(stderr, b"%s\n\0" as *const u8 as *const libc::c_char, serialized);
    if strncmp(
        serialized,
        b"12.3\0" as *const u8 as *const libc::c_char,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
    {} else {
        __assert_fail(
            b"strncmp(serialized, \"12.3\", 4) == 0\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                as *const u8 as *const libc::c_char,
            110 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3188: {
        if strncmp(
            serialized,
            b"12.3\0" as *const u8 as *const libc::c_char,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        {} else {
            __assert_fail(
                b"strncmp(serialized, \"12.3\", 4) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_set_value.c\0"
                    as *const u8 as *const libc::c_char,
                110 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"PARSE AND SET PASSED\n\0" as *const u8 as *const libc::c_char);
    printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
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
