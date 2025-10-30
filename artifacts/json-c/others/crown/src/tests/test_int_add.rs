use ::libc;
extern "C" {
    
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    
    
    
    
    
    
    
    
}
pub type __int32_t = libc::c_int;
pub type __int64_t = libc::c_long;
pub type __uint64_t = libc::c_ulong;
pub type int32_t = __int32_t;
pub type int64_t = __int64_t;
pub type uint64_t = __uint64_t;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut tmp: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_new_int(123 as libc::c_int);
    crate::src::json_object::json_object_int_inc(tmp, 123 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int(tmp) == 246 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == 246\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            13 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_4049: {
        if crate::src::json_object::json_object_get_int(tmp) == 246 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == 246\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT ADD PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_int(2147483647 as libc::c_int);
    crate::src::json_object::json_object_int_inc(tmp, 100 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            18 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3977: {
        if crate::src::json_object::json_object_get_int(tmp) == 2147483647 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == INT32_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    if crate::src::json_object::json_object_get_int64(tmp)
        == 2147483647 as libc::c_int as int64_t + 100 as libc::c_long
    {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == (int64_t)INT32_MAX + 100L\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            19 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3925: {
        if crate::src::json_object::json_object_get_int64(tmp)
            == 2147483647 as libc::c_int as int64_t + 100 as libc::c_long
        {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == (int64_t)INT32_MAX + 100L\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                19 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT ADD OVERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_int(-(2147483647 as libc::c_int) - 1 as libc::c_int);
    crate::src::json_object::json_object_int_inc(tmp, -(100 as libc::c_int) as int64_t);
    if crate::src::json_object::json_object_get_int(tmp) == -(2147483647 as libc::c_int) - 1 as libc::c_int
    {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == INT32_MIN\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            24 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3843: {
        if crate::src::json_object::json_object_get_int(tmp) == -(2147483647 as libc::c_int) - 1 as libc::c_int
        {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == INT32_MIN\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    if crate::src::json_object::json_object_get_int64(tmp)
        == (-(2147483647 as libc::c_int) - 1 as libc::c_int) as int64_t
            - 100 as libc::c_long
    {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == (int64_t)INT32_MIN - 100L\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            25 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3784: {
        if crate::src::json_object::json_object_get_int64(tmp)
            == (-(2147483647 as libc::c_int) - 1 as libc::c_int) as int64_t
                - 100 as libc::c_long
        {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == (int64_t)INT32_MIN - 100L\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT ADD UNDERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_int64(321321321 as libc::c_int as int64_t);
    crate::src::json_object::json_object_int_inc(tmp, 321321321 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int(tmp) == 642642642 as libc::c_int {} else {
        __assert_fail(
            b"json_object_get_int(tmp) == 642642642\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            30 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3713: {
        if crate::src::json_object::json_object_get_int(tmp) == 642642642 as libc::c_int {} else {
            __assert_fail(
                b"json_object_get_int(tmp) == 642642642\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT64 ADD PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_int64(9223372036854775807 as libc::c_long);
    crate::src::json_object::json_object_int_inc(tmp, 100 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            35 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3641: {
        if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    if crate::src::json_object::json_object_get_uint64(tmp)
        == (9223372036854775807 as libc::c_long as uint64_t)
            .wrapping_add(100 as libc::c_uint as uint64_t)
    {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == (uint64_t)INT64_MAX + 100U\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            36 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3586: {
        if crate::src::json_object::json_object_get_uint64(tmp)
            == (9223372036854775807 as libc::c_long as uint64_t)
                .wrapping_add(100 as libc::c_uint as uint64_t)
        {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == (uint64_t)INT64_MAX + 100U\0"
                    as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                36 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_int_inc(tmp, -(100 as libc::c_int) as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            38 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3532: {
        if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                38 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 9223372036854775807 as libc::c_long as uint64_t
    {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == (uint64_t)INT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            39 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3483: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 9223372036854775807 as libc::c_long as uint64_t
        {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == (uint64_t)INT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    printf(b"INT64 ADD OVERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_int64(
        -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long,
    );
    crate::src::json_object::json_object_int_inc(tmp, -(100 as libc::c_int) as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp)
        == -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
    {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MIN\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            44 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3397: {
        if crate::src::json_object::json_object_get_int64(tmp)
            == -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
        {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MIN\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                44 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_int_inc(tmp, 100 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp)
        != -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
    {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) != INT64_MIN\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            46 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3336: {
        if crate::src::json_object::json_object_get_int64(tmp)
            != -(9223372036854775807 as libc::c_long) - 1 as libc::c_int as libc::c_long
        {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) != INT64_MIN\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                46 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"INT64 ADD UNDERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_uint64(400 as libc::c_int as uint64_t);
    crate::src::json_object::json_object_int_inc(tmp, -(200 as libc::c_int) as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 200 as libc::c_int as int64_t {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == 200\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            52 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3265: {
        if crate::src::json_object::json_object_get_int64(tmp) == 200 as libc::c_int as int64_t {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == 200\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                52 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    if crate::src::json_object::json_object_get_uint64(tmp) == 200 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 200\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            53 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3219: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 200 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 200\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    crate::src::json_object::json_object_int_inc(tmp, 200 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 400 as libc::c_int as int64_t {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == 400\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            55 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3165: {
        if crate::src::json_object::json_object_get_int64(tmp) == 400 as libc::c_int as int64_t {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == 400\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    if crate::src::json_object::json_object_get_uint64(tmp) == 400 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 400\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            56 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3119: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 400 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 400\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                56 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"UINT64 ADD PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_uint64(
        (18446744073709551615 as libc::c_ulong)
            .wrapping_sub(50 as libc::c_int as libc::c_ulong),
    );
    crate::src::json_object::json_object_int_inc(tmp, 100 as libc::c_int as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            61 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_3043: {
        if crate::src::json_object::json_object_get_int64(tmp) == 9223372036854775807 as libc::c_long {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == INT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                61 as libc::c_int as libc::c_uint,
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
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            62 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_2996: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 18446744073709551615 as libc::c_ulong {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == UINT64_MAX\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                62 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"UINT64 ADD OVERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
    tmp = crate::src::json_object::json_object_new_uint64(100 as libc::c_int as uint64_t);
    crate::src::json_object::json_object_int_inc(tmp, -(200 as libc::c_int) as int64_t);
    if crate::src::json_object::json_object_get_int64(tmp) == -(100 as libc::c_int) as int64_t {} else {
        __assert_fail(
            b"json_object_get_int64(tmp) == -100\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            67 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_2918: {
        if crate::src::json_object::json_object_get_int64(tmp) == -(100 as libc::c_int) as int64_t {} else {
            __assert_fail(
                b"json_object_get_int64(tmp) == -100\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
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
    if crate::src::json_object::json_object_get_uint64(tmp) == 0 as libc::c_int as uint64_t {} else {
        __assert_fail(
            b"json_object_get_uint64(tmp) == 0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                as *const u8 as *const libc::c_char,
            68 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 23],
                &[libc::c_char; 23],
            >(b"int main(int, char **)\0"))
                .as_ptr(),
        );
    }
    'c_2866: {
        if crate::src::json_object::json_object_get_uint64(tmp) == 0 as libc::c_int as uint64_t {} else {
            __assert_fail(
                b"json_object_get_uint64(tmp) == 0\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_int_add.c\0"
                    as *const u8 as *const libc::c_char,
                68 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 23],
                    &[libc::c_char; 23],
                >(b"int main(int, char **)\0"))
                    .as_ptr(),
            );
        }
    };
    crate::src::json_object::json_object_put(tmp);
    printf(b"UINT64 ADD UNDERFLOW PASSED\n\0" as *const u8 as *const libc::c_char);
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
