use ::libc;
extern "C" {
    pub type json_object;
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn __errno_location() -> *mut libc::c_int;
    fn json_object_put(obj: *mut json_object) -> libc::c_int;
    fn json_object_to_json_string(obj: *mut json_object) -> *const libc::c_char;
    fn json_object_object_get(
        obj: *const json_object,
        key: *const libc::c_char,
    ) -> *mut json_object;
    fn json_object_object_get_ex(
        obj: *const json_object,
        key: *const libc::c_char,
        value: *mut *mut json_object,
    ) -> libc::c_int;
    fn json_object_array_length(obj: *const json_object) -> size_t;
    fn json_object_array_get_idx(
        obj: *const json_object,
        idx: size_t,
    ) -> *mut json_object;
    fn json_object_get_string(obj: *mut json_object) -> *const libc::c_char;
    fn json_object_equal(obj1: *mut json_object, obj2: *mut json_object) -> libc::c_int;
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn _json_c_strerror(errno_in: libc::c_int) -> *mut libc::c_char;
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    static mut stdout: *mut FILE;
    static mut stderr: *mut FILE;
    fn fflush(__stream: *mut FILE) -> libc::c_int;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn snprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
    fn exit(_: libc::c_int) -> !;
    fn json_c_version() -> *const libc::c_char;
    fn json_c_version_num() -> libc::c_int;
    fn json_patch_apply(
        copy_from: *mut json_object,
        patch: *mut json_object,
        base: *mut *mut json_object,
        patch_error: *mut json_patch_error,
    ) -> libc::c_int;
    fn json_object_from_file(filename: *const libc::c_char) -> *mut json_object;
}
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type json_bool = libc::c_int;
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct json_patch_error {
    pub errno_code: libc::c_int,
    pub patch_failure_idx: size_t,
    pub errmsg: *const libc::c_char,
}
#[no_mangle]
pub unsafe extern "C" fn test_json_patch_op(mut jo: *mut json_object) {
    let mut comment: *const libc::c_char = json_object_get_string(
        json_object_object_get(jo, b"comment\0" as *const u8 as *const libc::c_char),
    );
    let mut doc: *mut json_object = json_object_object_get(
        jo,
        b"doc\0" as *const u8 as *const libc::c_char,
    );
    let mut patch: *mut json_object = json_object_object_get(
        jo,
        b"patch\0" as *const u8 as *const libc::c_char,
    );
    let mut expected: *mut json_object = 0 as *mut json_object;
    let mut have_expected: json_bool = json_object_object_get_ex(
        jo,
        b"expected\0" as *const u8 as *const libc::c_char,
        &mut expected,
    );
    let mut error: *mut json_object = json_object_object_get(
        jo,
        b"error\0" as *const u8 as *const libc::c_char,
    );
    let mut error_s: *const libc::c_char = json_object_get_string(error);
    let mut res: *mut json_object = 0 as *mut json_object;
    let mut ret: libc::c_int = 0;
    printf(
        b"Testing '%s', doc '%s' patch '%s' : \0" as *const u8 as *const libc::c_char,
        if !comment.is_null() { comment } else { error_s },
        json_object_get_string(doc),
        json_object_get_string(patch),
    );
    if error.is_null() && have_expected == 0 {
        printf(
            b"BAD TEST - no expected or error conditions in test: %s\n\0" as *const u8
                as *const libc::c_char,
            json_object_to_json_string(jo),
        );
        __assert_fail(
            b"0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                as *const u8 as *const libc::c_char,
            37 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 46],
                &[libc::c_char; 46],
            >(b"void test_json_patch_op(struct json_object *)\0"))
                .as_ptr(),
        );
        'c_3572: {
            __assert_fail(
                b"0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                37 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
        };
    }
    fflush(stdout);
    let mut jperr: json_patch_error = json_patch_error {
        errno_code: 0,
        patch_failure_idx: 0,
        errmsg: 0 as *const libc::c_char,
    };
    if !error.is_null() {
        if -(1 as libc::c_int) == json_patch_apply(doc, patch, &mut res, &mut jperr)
        {} else {
            __assert_fail(
                b"-1 == json_patch_apply(doc, patch, &res, &jperr)\0" as *const u8
                    as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                42 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
        }
        'c_3495: {
            if -(1 as libc::c_int) == json_patch_apply(doc, patch, &mut res, &mut jperr)
            {} else {
                __assert_fail(
                    b"-1 == json_patch_apply(doc, patch, &res, &jperr)\0" as *const u8
                        as *const libc::c_char,
                    b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                        as *const u8 as *const libc::c_char,
                    42 as libc::c_int as libc::c_uint,
                    (*::core::mem::transmute::<
                        &[u8; 46],
                        &[libc::c_char; 46],
                    >(b"void test_json_patch_op(struct json_object *)\0"))
                        .as_ptr(),
                );
            }
        };
        if jperr.errno_code != 0 as libc::c_int {} else {
            __assert_fail(
                b"jperr.errno_code != 0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                43 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
        }
        'c_3457: {
            if jperr.errno_code != 0 as libc::c_int {} else {
                __assert_fail(
                    b"jperr.errno_code != 0\0" as *const u8 as *const libc::c_char,
                    b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                        as *const u8 as *const libc::c_char,
                    43 as libc::c_int as libc::c_uint,
                    (*::core::mem::transmute::<
                        &[u8; 46],
                        &[libc::c_char; 46],
                    >(b"void test_json_patch_op(struct json_object *)\0"))
                        .as_ptr(),
                );
            }
        };
        printf(b"OK\n\0" as *const u8 as *const libc::c_char);
        printf(
            b" => json_patch_apply failed as expected: %s at patch idx %zu: %s\n\0"
                as *const u8 as *const libc::c_char,
            _json_c_strerror(jperr.errno_code),
            jperr.patch_failure_idx,
            jperr.errmsg,
        );
        json_object_put(res);
    } else {
        ret = json_patch_apply(doc, patch, &mut res, &mut jperr);
        if ret != 0 {
            fprintf(
                stderr,
                b"json_patch_apply() returned '%d'\n\0" as *const u8
                    as *const libc::c_char,
                ret,
            );
            fprintf(
                stderr,
                b"Expected: %s\n\0" as *const u8 as *const libc::c_char,
                json_object_get_string(expected),
            );
            fprintf(
                stderr,
                b"Got: %s\n\0" as *const u8 as *const libc::c_char,
                if !res.is_null() {
                    json_object_get_string(res)
                } else {
                    b"(null)\0" as *const u8 as *const libc::c_char
                },
            );
            fprintf(
                stderr,
                b"json_patch_apply failed: %s at patch idx %zu: %s\n\0" as *const u8
                    as *const libc::c_char,
                _json_c_strerror(jperr.errno_code),
                jperr.patch_failure_idx,
                jperr.errmsg,
            );
            fflush(stderr);
            __assert_fail(
                b"0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                57 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
            'c_3292: {
                __assert_fail(
                    b"0\0" as *const u8 as *const libc::c_char,
                    b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                        as *const u8 as *const libc::c_char,
                    57 as libc::c_int as libc::c_uint,
                    (*::core::mem::transmute::<
                        &[u8; 46],
                        &[libc::c_char; 46],
                    >(b"void test_json_patch_op(struct json_object *)\0"))
                        .as_ptr(),
                );
            };
        }
        if jperr.errno_code == 0 as libc::c_int {} else {
            __assert_fail(
                b"jperr.errno_code == 0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                60 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
        }
        'c_3244: {
            if jperr.errno_code == 0 as libc::c_int {} else {
                __assert_fail(
                    b"jperr.errno_code == 0\0" as *const u8 as *const libc::c_char,
                    b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                        as *const u8 as *const libc::c_char,
                    60 as libc::c_int as libc::c_uint,
                    (*::core::mem::transmute::<
                        &[u8; 46],
                        &[libc::c_char; 46],
                    >(b"void test_json_patch_op(struct json_object *)\0"))
                        .as_ptr(),
                );
            }
        };
        ret = json_object_equal(expected, res);
        if ret == 0 as libc::c_int {
            fprintf(
                stderr,
                b"json_object_equal() returned '%d'\n\0" as *const u8
                    as *const libc::c_char,
                ret,
            );
            fprintf(
                stderr,
                b"Expected: %s\n\0" as *const u8 as *const libc::c_char,
                json_object_get_string(expected),
            );
            fprintf(
                stderr,
                b"Got: %s\n\0" as *const u8 as *const libc::c_char,
                json_object_get_string(res),
            );
            fflush(stderr);
            __assert_fail(
                b"0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                    as *const u8 as *const libc::c_char,
                67 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 46],
                    &[libc::c_char; 46],
                >(b"void test_json_patch_op(struct json_object *)\0"))
                    .as_ptr(),
            );
            'c_3145: {
                __assert_fail(
                    b"0\0" as *const u8 as *const libc::c_char,
                    b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/tests/test_json_patch.c\0"
                        as *const u8 as *const libc::c_char,
                    67 as libc::c_int as libc::c_uint,
                    (*::core::mem::transmute::<
                        &[u8; 46],
                        &[libc::c_char; 46],
                    >(b"void test_json_patch_op(struct json_object *)\0"))
                        .as_ptr(),
                );
            };
        }
        json_object_put(res);
        res = 0 as *mut json_object;
        printf(b"OK\n\0" as *const u8 as *const libc::c_char);
    };
}
#[no_mangle]
pub unsafe extern "C" fn test_json_patch_using_file(
    mut testdir: *const libc::c_char,
    mut filename: *const libc::c_char,
) {
    let mut full_filename: [libc::c_char; 4096] = [0; 4096];
    snprintf(
        full_filename.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 4096]>() as libc::c_ulong,
        b"%s/%s\0" as *const u8 as *const libc::c_char,
        testdir,
        filename,
    );
    let mut ii: size_t = 0;
    printf(b"Testing using file %s\n\0" as *const u8 as *const libc::c_char, filename);
    let mut jo: *mut json_object = json_object_from_file(full_filename.as_mut_ptr());
    if jo.is_null() {
        fprintf(
            stderr,
            b"FAIL: unable to open %s: %s\n\0" as *const u8 as *const libc::c_char,
            full_filename.as_mut_ptr(),
            _json_c_strerror(*__errno_location()),
        );
        exit(1 as libc::c_int);
    }
    ii = 0 as libc::c_int as size_t;
    while ii < json_object_array_length(jo) {
        let mut jo1: *mut json_object = json_object_array_get_idx(jo, ii);
        test_json_patch_op(jo1);
        ii = ii.wrapping_add(1);
        ii;
    }
    json_object_put(jo);
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut testdir: *const libc::c_char = 0 as *const libc::c_char;
    if argc < 2 as libc::c_int {
        fprintf(
            stderr,
            b"Usage: %s <testdir>\n  <testdir> is the location of input files\n\0"
                as *const u8 as *const libc::c_char,
            *argv.offset(0 as libc::c_int as isize),
        );
        return 1 as libc::c_int;
    }
    testdir = *argv.offset(1 as libc::c_int as isize);
    if strncmp(
        json_c_version(),
        b"0.18.99\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong,
    ) != 0
    {
        printf(
            b"FAIL: Output from json_c_version(): %s does not match %s\0" as *const u8
                as *const libc::c_char,
            json_c_version(),
            b"0.18.99\0" as *const u8 as *const libc::c_char,
        );
        return 1 as libc::c_int;
    }
    if json_c_version_num()
        != (0 as libc::c_int) << 16 as libc::c_int
            | (18 as libc::c_int) << 8 as libc::c_int | 99 as libc::c_int
    {
        printf(
            b"FAIL: Output from json_c_version_num(): %d does not match %d\0"
                as *const u8 as *const libc::c_char,
            json_c_version_num(),
            (0 as libc::c_int) << 16 as libc::c_int
                | (18 as libc::c_int) << 8 as libc::c_int | 99 as libc::c_int,
        );
        return 1 as libc::c_int;
    }
    test_json_patch_using_file(
        testdir,
        b"json_patch_spec_tests.json\0" as *const u8 as *const libc::c_char,
    );
    test_json_patch_using_file(
        testdir,
        b"json_patch_tests.json\0" as *const u8 as *const libc::c_char,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
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
