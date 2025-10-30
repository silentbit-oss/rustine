use ::libc;
extern "C" {
    
    
    
    
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    
    
    
    
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor22 { dummy: () }
pub type _IO_lock_t = ();
pub type FILE = crate::src::apps::json_parse::_IO_FILE;
pub type uintptr_t = libc::c_ulong;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor23 { dummy: () }
pub type json_type = libc::c_uint;
pub const json_type_string: json_type = 6;
pub const json_type_array: json_type = 5;
pub const json_type_object: json_type = 4;
pub const json_type_int: json_type = 3;
pub const json_type_double: json_type = 2;
pub const json_type_boolean: json_type = 1;
pub const json_type_null: json_type = 0;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor24 { dummy: () }
pub type lh_equal_fn = unsafe extern "C" fn(
    *const libc::c_void,
    *const libc::c_void,
) -> libc::c_int;
pub type lh_hash_fn = unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong;
pub type lh_entry_free_fn = unsafe extern "C" fn(*mut crate::src::json_object::lh_entry) -> ();
pub type json_c_visit_userfunc = unsafe extern "C" fn(
    *mut crate::src::json_object::json_object,
    libc::c_int,
    *mut crate::src::json_object::json_object,
    *const libc::c_char,
    *mut size_t,
    *mut libc::c_void,
) -> libc::c_int;
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
#[no_mangle]
pub unsafe extern "C" fn json_c_visit(
    mut jso: *mut crate::src::json_object::json_object,
    mut future_flags: libc::c_int,
    mut userfunc: Option::<json_c_visit_userfunc>,
    mut userarg: *mut libc::c_void,
) -> libc::c_int {
    let mut ret: libc::c_int = _json_c_visit(
        jso,
        0 as *mut crate::src::json_object::json_object,
        0 as *const libc::c_char,
        0 as *mut size_t,
        userfunc,
        userarg,
    );
    match ret {
        0 | 7547 | 767 | 7867 => return 0 as libc::c_int,
        _ => return -(1 as libc::c_int),
    };
}
unsafe extern "C" fn _json_c_visit(
    mut jso: *mut crate::src::json_object::json_object,
    mut parent_jso: *mut crate::src::json_object::json_object,
    mut jso_key: *const libc::c_char,
    mut jso_index: *mut size_t,
    mut userfunc: Option::<json_c_visit_userfunc>,
    mut userarg: *mut libc::c_void,
) -> libc::c_int {
    let mut userret: libc::c_int = userfunc
        .expect(
            "non-null function pointer",
        )(jso, 0 as libc::c_int, parent_jso, jso_key, jso_index, userarg);
    match userret {
        0 => {}
        7547 | 767 | 7867 | -1 => return userret,
        _ => {
            fprintf(
                stderr,
                b"ERROR: invalid return value from json_c_visit userfunc: %d\n\0"
                    as *const u8 as *const libc::c_char,
                userret,
            );
            return -(1 as libc::c_int);
        }
    }
    match crate::src::json_object::json_object_get_type(jso) as libc::c_uint {
        0 | 1 | 2 | 3 | 6 => return 0 as libc::c_int,
        4 => {
            let mut key: *mut libc::c_char = 0 as *mut libc::c_char;
            let mut child: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
            let mut entrykey: *mut crate::src::json_object::lh_entry = lh_table_head(crate::src::json_object::json_object_get_object(jso));
            let mut entry_nextkey: *mut crate::src::json_object::lh_entry = 0 as *mut crate::src::json_object::lh_entry;
            while !({
                if !entrykey.is_null() {
                    key = lh_entry_k(entrykey) as *mut libc::c_char;
                    child = lh_entry_v(entrykey) as *mut crate::src::json_object::json_object;
                    entry_nextkey = lh_entry_next(entrykey);
                }
                entrykey
            })
                .is_null()
            {
                userret = _json_c_visit(
                    child,
                    jso,
                    key,
                    0 as *mut size_t,
                    userfunc,
                    userarg,
                );
                if userret == 767 as libc::c_int {
                    break;
                }
                if userret == 7867 as libc::c_int || userret == -(1 as libc::c_int) {
                    return userret;
                }
                if userret != 0 as libc::c_int && userret != 7547 as libc::c_int {
                    fprintf(
                        stderr,
                        b"INTERNAL ERROR: _json_c_visit returned %d\n\0" as *const u8
                            as *const libc::c_char,
                        userret,
                    );
                    return -(1 as libc::c_int);
                }
                entrykey = entry_nextkey;
            }std::intrinsics::assume(({
        if !entrykey.is_null()
                {
                        key = lh_entry_k(entrykey) as *mut libc::c_char;
                        child = lh_entry_v(entrykey) as *mut crate::src::json_object::json_object;
                        entry_nextkey = lh_entry_next(entrykey);
                    }
                entrykey
            }).addr() == 0);
        }
        5 => {
            let mut array_len: size_t = crate::src::json_object::json_object_array_length(jso);
            let mut ii: size_t = 0;
            ii = 0 as libc::c_int as size_t;
            while ii < array_len {
                let mut child_0: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(jso, ii);
                userret = _json_c_visit(
                    child_0,
                    jso,
                    0 as *const libc::c_char,
                    &raw mut ii,
                    userfunc,
                    userarg,
                );
                if userret == 767 as libc::c_int {
                    break;
                }
                if userret == 7867 as libc::c_int || userret == -(1 as libc::c_int) {
                    return userret;
                }
                if userret != 0 as libc::c_int && userret != 7547 as libc::c_int {
                    fprintf(
                        stderr,
                        b"INTERNAL ERROR: _json_c_visit returned %d\n\0" as *const u8
                            as *const libc::c_char,
                        userret,
                    );
                    return -(1 as libc::c_int);
                }
                ii = ii.wrapping_add(1);
                ii;
            }
        }
        _ => {
            fprintf(
                stderr,
                b"INTERNAL ERROR: _json_c_visit found object of unknown type: %d\n\0"
                    as *const u8 as *const libc::c_char,
                crate::src::json_object::json_object_get_type(jso) as libc::c_uint,
            );
            return -(1 as libc::c_int);
        }
    }
    userret = userfunc
        .expect(
            "non-null function pointer",
        )(jso, 0x2 as libc::c_int, parent_jso, jso_key, jso_index, userarg);
    match userret {
        7547 | 767 | 0 => return 0 as libc::c_int,
        7867 | -1 => return userret,
        _ => {
            fprintf(
                stderr,
                b"ERROR: invalid return value from json_c_visit userfunc: %d\n\0"
                    as *const u8 as *const libc::c_char,
                userret,
            );
            return -(1 as libc::c_int);
        }
    };
}
