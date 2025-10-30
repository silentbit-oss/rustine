use ::libc;
extern "C" {
    fn __errno_location() -> *mut libc::c_int;
    
    
    
    
    
    
    
    
    fn memmove(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strdup(_: *const libc::c_char) -> *mut libc::c_char;
    fn strchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strrchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strstr(_: *const libc::c_char, _: *const libc::c_char) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn vasprintf(
        __ptr: *mut *mut libc::c_char,
        __f: *const libc::c_char,
        __arg: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn strtoull(
        _: *const libc::c_char,
        _: *mut *mut libc::c_char,
        _: libc::c_int,
    ) -> libc::c_ulonglong;
    fn free(_: *mut libc::c_void);
}
pub type __builtin_va_list = [crate::src::debug::__va_list_tag; 1];
#[derive(Copy, Clone)]

struct ErasedByPreprocessor10 { dummy: () }
pub type __uint32_t = libc::c_uint;
pub type uint32_t = __uint32_t;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor11 { dummy: () }
#[derive(Copy, Clone)]

struct ErasedByPreprocessor12 { dummy: () }
pub type json_object_delete_fn = unsafe extern "C" fn(
    *mut crate::src::json_object::json_object,
    *mut libc::c_void,
) -> ();
pub type json_object_to_json_string_fn = unsafe extern "C" fn(
    *mut crate::src::json_object::json_object,
    *mut crate::src::apps::json_parse::printbuf,
    libc::c_int,
    libc::c_int,
) -> libc::c_int;
pub type json_type = libc::c_uint;
pub const json_type_string: json_type = 6;
pub const json_type_array: json_type = 5;
pub const json_type_object: json_type = 4;
pub const json_type_int: json_type = 3;
pub const json_type_double: json_type = 2;
pub const json_type_boolean: json_type = 1;
pub const json_type_null: json_type = 0;
pub type size_t = libc::c_ulong;
pub type va_list = __builtin_va_list;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor13 { dummy: () }
pub type json_pointer_array_set_cb = Option::<
    unsafe extern "C" fn(
        *mut crate::src::json_object::json_object,
        size_t,
        *mut crate::src::json_object::json_object,
        *mut libc::c_void,
    ) -> libc::c_int,
>;
unsafe extern "C" fn string_replace_all_occurrences_with_char(
    mut s: *mut libc::c_char,
    mut occur: *const libc::c_char,
    mut repl_char: libc::c_char,
) {
    let mut slen: size_t = strlen(s);
    let mut skip: size_t = (strlen(occur))
        .wrapping_sub(1 as libc::c_int as libc::c_ulong);
    let mut p: *mut libc::c_char = s;
    loop {
        p = strstr(p, occur);
        if p.is_null() {std::intrinsics::assume((p).addr() == 0);
            break;
        }
        *p = repl_char;
        p = p.offset(1);
        p;
        slen = slen.wrapping_sub(skip);
        memmove(
            p as *mut libc::c_void,
            p.offset(skip as isize) as *const libc::c_void,
            slen
                .wrapping_sub(p.offset_from(s) as libc::c_long as size_t)
                .wrapping_add(1 as libc::c_int as size_t),
        );
    };
}
unsafe extern "C" fn is_valid_index(
    mut path: *const libc::c_char,
    mut idx: *mut size_t,
) -> libc::c_int {
    let mut i: size_t = 0;
    let mut len: size_t = strlen(path);
    if len == 1 as libc::c_int as size_t {
        if *path.offset(0 as libc::c_int as isize) as libc::c_int >= '0' as i32
            && *path.offset(0 as libc::c_int as isize) as libc::c_int <= '9' as i32
        {
            *idx = (*path.offset(0 as libc::c_int as isize) as libc::c_int - '0' as i32)
                as size_t;
            return 1 as libc::c_int;
        }
        *__errno_location() = 22 as libc::c_int;
        return 0 as libc::c_int;
    }
    if *path.offset(0 as libc::c_int as isize) as libc::c_int == '0' as i32 {
        *__errno_location() = 22 as libc::c_int;
        return 0 as libc::c_int;
    }
    i = 0 as libc::c_int as size_t;
    while i < len {
        if !(*path.offset(i as isize) as libc::c_int >= '0' as i32
            && *path.offset(i as isize) as libc::c_int <= '9' as i32)
        {
            *__errno_location() = 22 as libc::c_int;
            return 0 as libc::c_int;
        }
        i = i.wrapping_add(1);
        i;
    }
    *idx = strtoull(path, 0 as *mut *mut libc::c_char, 10 as libc::c_int) as size_t;
    return 1 as libc::c_int;
}
unsafe extern "C" fn json_pointer_get_single_path(
    mut obj: *mut crate::src::json_object::json_object,
    mut path: *mut libc::c_char,
    mut value: *mut *mut crate::src::json_object::json_object,
    mut idx: *mut size_t,
) -> libc::c_int {
    if crate::src::json_object::json_object_is_type(obj, json_type_array) != 0 {
        if is_valid_index(path, idx) == 0 {
            return -(1 as libc::c_int);
        }
        if *idx >= crate::src::json_object::json_object_array_length(obj) {
            *__errno_location() = 2 as libc::c_int;
            return -(1 as libc::c_int);
        }
        obj = crate::src::json_object::json_object_array_get_idx(obj, *idx);
        if !obj.is_null() {
            if !value.is_null() {
                *value = obj;
            }else { std::intrinsics::assume((value).addr() == 0); }
            return 0 as libc::c_int;
        }else { std::intrinsics::assume((obj).addr() == 0); }
        *__errno_location() = 2 as libc::c_int;
        return -(1 as libc::c_int);
    }
    string_replace_all_occurrences_with_char(
        path,
        b"~1\0" as *const u8 as *const libc::c_char,
        '/' as i32 as libc::c_char,
    );
    string_replace_all_occurrences_with_char(
        path,
        b"~0\0" as *const u8 as *const libc::c_char,
        '~' as i32 as libc::c_char,
    );
    if crate::src::json_object::json_object_object_get_ex(obj, path, value) == 0 {
        *__errno_location() = 2 as libc::c_int;
        return -(1 as libc::c_int);
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn json_object_array_put_idx_cb(
    mut parent: *mut crate::src::json_object::json_object,
    mut idx: size_t,
    mut value: *mut crate::src::json_object::json_object,
    mut priv_0: *mut libc::c_void,
) -> libc::c_int {
    return crate::src::json_object::json_object_array_put_idx(parent, idx, value);
}
unsafe extern "C" fn json_pointer_set_single_path(
    mut parent: *mut crate::src::json_object::json_object,
    mut path: *const libc::c_char,
    mut value: *mut crate::src::json_object::json_object,
    mut array_set_cb: json_pointer_array_set_cb,
    mut priv_0: *mut libc::c_void,
) -> libc::c_int {
    if crate::src::json_object::json_object_is_type(parent, json_type_array) != 0 {
        let mut idx: size_t = 0;
        if *path.offset(0 as libc::c_int as isize) as libc::c_int == '-' as i32
            && *path.offset(1 as libc::c_int as isize) as libc::c_int == '\0' as i32
        {
            return crate::src::json_object::json_object_array_add(parent, value);
        }
        if is_valid_index(path, &raw mut idx) == 0 {
            return -(1 as libc::c_int);
        }
        return array_set_cb
            .expect("non-null function pointer")(parent, idx, value, priv_0);
    }
    if crate::src::json_object::json_object_is_type(parent, json_type_object) != 0 {
        return crate::src::json_object::json_object_object_add(parent, path, value);
    }
    *__errno_location() = 2 as libc::c_int;
    return -(1 as libc::c_int);
}
unsafe extern "C" fn json_pointer_result_get_recursive(
    mut obj: *mut crate::src::json_object::json_object,
    mut path: *mut libc::c_char,
    mut res: *mut crate::src::json_patch::json_pointer_get_result,
) -> libc::c_int {
    let mut parent_obj: *mut crate::src::json_object::json_object = obj;
    let mut idx: size_t = 0 as libc::c_int as size_t;
    let mut endp: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut rc: libc::c_int = 0;
    if *path.offset(0 as libc::c_int as isize) as libc::c_int != '/' as i32 {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    path = path.offset(1);
    path;
    endp = strchr(path, '/' as i32);
    if !endp.is_null() {
        *endp = '\0' as i32 as libc::c_char;
    }else { std::intrinsics::assume((endp).addr() == 0); }
    rc = json_pointer_get_single_path(obj, path, &raw mut obj, &raw mut idx);
    if rc != 0 {
        return rc;
    }
    if !endp.is_null() {
        *endp = '/' as i32 as libc::c_char;
        return json_pointer_result_get_recursive(obj, endp, res);
    }else { std::intrinsics::assume((endp).addr() == 0); }
    if !res.is_null() {
        (*res).parent = parent_obj;
        (*res).obj = obj;
        if crate::src::json_object::json_object_is_type((*res).parent, json_type_array) != 0 {
            (*res).index_in_parent = idx as uint32_t;
        } else {
            (*res).key_in_parent = path;
        }
    }else { std::intrinsics::assume((res).addr() == 0); }
    return 0 as libc::c_int;
}
unsafe extern "C" fn json_pointer_object_get_recursive(
    mut obj: *mut crate::src::json_object::json_object,
    mut path: *mut libc::c_char,
    mut value: *mut *mut crate::src::json_object::json_object,
) -> libc::c_int {
    let mut res: crate::src::json_patch::json_pointer_get_result = crate::src::json_patch::json_pointer_get_result {
        parent: 0 as *mut crate::src::json_object::json_object,
        obj: 0 as *mut crate::src::json_object::json_object,
        key_in_parent: 0 as *const libc::c_char,
        index_in_parent: 0,
    };
    let mut rc: libc::c_int = 0;
    rc = json_pointer_result_get_recursive(obj, path, &raw mut res);
    if rc != 0 {
        return rc;
    }
    if !value.is_null() {
        *value = res.obj;
    }else { std::intrinsics::assume((value).addr() == 0); }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_get_internal(
    mut obj: *mut crate::src::json_object::json_object,
    mut path: *const libc::c_char,
    mut res: *mut crate::src::json_patch::json_pointer_get_result,
) -> libc::c_int {
    let mut path_copy: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut rc: libc::c_int = 0;
    if obj.is_null() || path.is_null() {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    if *path.offset(0 as libc::c_int as isize) as libc::c_int == '\0' as i32 {
        (*res).parent = 0 as *mut crate::src::json_object::json_object;
        (*res).obj = obj;
        (*res).key_in_parent = 0 as *const libc::c_char;
        (*res).index_in_parent = 4294967295 as libc::c_uint;
        return 0 as libc::c_int;
    }
    path_copy = strdup(path);
    if path_copy.is_null() {std::intrinsics::assume((path_copy).addr() == 0);
        *__errno_location() = 12 as libc::c_int;
        return -(1 as libc::c_int);
    }
    rc = json_pointer_result_get_recursive(obj, path_copy, res);
    if rc == 0 as libc::c_int
        && crate::src::json_object::json_object_is_type((*res).parent, json_type_object) != 0
        && !((*res).key_in_parent).is_null()
    {
        (*res)
            .key_in_parent = path
            .offset(
                ((*res).key_in_parent).offset_from(path_copy) as libc::c_long as isize,
            );
    }
    free(path_copy as *mut libc::c_void);
    return rc;
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_get(
    mut obj: *mut crate::src::json_object::json_object,
    mut path: *const libc::c_char,
    mut res: *mut *mut crate::src::json_object::json_object,
) -> libc::c_int {
    let mut jpres: crate::src::json_patch::json_pointer_get_result = crate::src::json_patch::json_pointer_get_result {
        parent: 0 as *mut crate::src::json_object::json_object,
        obj: 0 as *mut crate::src::json_object::json_object,
        key_in_parent: 0 as *const libc::c_char,
        index_in_parent: 0,
    };
    let mut rc: libc::c_int = 0;
    rc = json_pointer_get_internal(obj, path, &raw mut jpres);
    if rc != 0 {
        return rc;
    }
    if !res.is_null() {
        *res = jpres.obj;
    }else { std::intrinsics::assume((res).addr() == 0); }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_getf(
    mut obj: *mut crate::src::json_object::json_object,
    mut res: *mut *mut crate::src::json_object::json_object,
    mut path_fmt: *const libc::c_char,
    mut args: ...
) -> libc::c_int {
    let mut path_copy: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut rc: libc::c_int = 0 as libc::c_int;
    let mut args_0: ::core::ffi::VaListImpl;
    if obj.is_null() || path_fmt.is_null() {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    args_0 = args.clone();
    rc = vasprintf(&raw mut path_copy, path_fmt, args_0.as_va_list());
    if rc < 0 as libc::c_int {
        return rc;
    }
    if *path_copy.offset(0 as libc::c_int as isize) as libc::c_int == '\0' as i32 {
        if !res.is_null() {
            *res = obj;
        }else { std::intrinsics::assume((res).addr() == 0); }
    } else {
        rc = json_pointer_object_get_recursive(obj, path_copy, res);
    }
    free(path_copy as *mut libc::c_void);
    return rc;
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_set_with_array_cb(
    mut obj: *mut *mut crate::src::json_object::json_object,
    mut path: *const libc::c_char,
    mut value: *mut crate::src::json_object::json_object,
    mut array_set_cb: json_pointer_array_set_cb,
    mut priv_0: *mut libc::c_void,
) -> libc::c_int {
    let mut endp: *const libc::c_char = 0 as *const libc::c_char;
    let mut path_copy: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut set: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut rc: libc::c_int = 0;
    if obj.is_null() || path.is_null() {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    if *path.offset(0 as libc::c_int as isize) as libc::c_int == '\0' as i32 {
        crate::src::json_object::json_object_put(*obj);
        *obj = value;
        return 0 as libc::c_int;
    }
    if *path.offset(0 as libc::c_int as isize) as libc::c_int != '/' as i32 {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    endp = strrchr(path, '/' as i32);
    if endp == path {
        path = path.offset(1);
        path;
        return json_pointer_set_single_path(*obj, path, value, array_set_cb, priv_0);
    }
    path_copy = strdup(path);
    if path_copy.is_null() {std::intrinsics::assume((path_copy).addr() == 0);
        *__errno_location() = 12 as libc::c_int;
        return -(1 as libc::c_int);
    }
    *path_copy
        .offset(
            endp.offset_from(path) as libc::c_long as isize,
        ) = '\0' as i32 as libc::c_char;
    rc = json_pointer_object_get_recursive(*obj, path_copy, &raw mut set);
    free(path_copy as *mut libc::c_void);
    if rc != 0 {
        return rc;
    }
    endp = endp.offset(1);
    endp;
    return json_pointer_set_single_path(set, endp, value, array_set_cb, priv_0);
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_set(
    mut obj: *mut *mut crate::src::json_object::json_object,
    mut path: *const libc::c_char,
    mut value: *mut crate::src::json_object::json_object,
) -> libc::c_int {
    return json_pointer_set_with_array_cb(
        obj,
        path,
        value,
        Some(
            json_object_array_put_idx_cb
                as unsafe extern "C" fn(
                    *mut crate::src::json_object::json_object,
                    size_t,
                    *mut crate::src::json_object::json_object,
                    *mut libc::c_void,
                ) -> libc::c_int,
        ),
        0 as *mut libc::c_void,
    );
}
#[no_mangle]
pub unsafe extern "C" fn json_pointer_setf(
    mut obj: *mut *mut crate::src::json_object::json_object,
    mut value: *mut crate::src::json_object::json_object,
    mut path_fmt: *const libc::c_char,
    mut args: ...
) -> libc::c_int {
    let mut current_block: u64;
    let mut endp: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut path_copy: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut set: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut args_0: ::core::ffi::VaListImpl;
    let mut rc: libc::c_int = 0 as libc::c_int;
    if obj.is_null() || path_fmt.is_null() {
        *__errno_location() = 22 as libc::c_int;
        return -(1 as libc::c_int);
    }
    args_0 = args.clone();
    rc = vasprintf(&raw mut path_copy, path_fmt, args_0.as_va_list());
    if rc < 0 as libc::c_int {
        return rc;
    }
    if *path_copy.offset(0 as libc::c_int as isize) as libc::c_int == '\0' as i32 {
        crate::src::json_object::json_object_put(*obj);
        *obj = value;
    } else if *path_copy.offset(0 as libc::c_int as isize) as libc::c_int != '/' as i32 {
        *__errno_location() = 22 as libc::c_int;
        rc = -(1 as libc::c_int);
    } else {
        endp = strrchr(path_copy, '/' as i32);
        if endp == path_copy {
            set = *obj;
            current_block = 9976989687550632217;
        } else {
            *endp = '\0' as i32 as libc::c_char;
            rc = json_pointer_object_get_recursive(*obj, path_copy, &raw mut set);
            if rc != 0 {
                current_block = 17420774570568838260;
            } else {
                current_block = 9976989687550632217;
            }
        }
        match current_block {
            17420774570568838260 => {}
            _ => {
                endp = endp.offset(1);
                endp;
                rc = json_pointer_set_single_path(
                    set,
                    endp,
                    value,
                    Some(
                        json_object_array_put_idx_cb
                            as unsafe extern "C" fn(
                                *mut crate::src::json_object::json_object,
                                size_t,
                                *mut crate::src::json_object::json_object,
                                *mut libc::c_void,
                            ) -> libc::c_int,
                    ),
                    0 as *mut libc::c_void,
                );
            }
        }
    }
    free(path_copy as *mut libc::c_void);
    return rc;
}
