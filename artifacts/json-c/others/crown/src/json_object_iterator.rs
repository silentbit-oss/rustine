use ::libc;
extern "C" {
    
}
pub type __uint32_t = libc::c_uint;
pub type uint32_t = __uint32_t;
pub type uintptr_t = libc::c_ulong;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor4 { dummy: () }
#[derive(Copy, Clone)]

struct ErasedByPreprocessor5 { dummy: () }
#[derive(Copy, Clone)]

struct ErasedByPreprocessor6 { dummy: () }
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
pub type json_bool = libc::c_int;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor7 { dummy: () }
pub type lh_equal_fn = unsafe extern "C" fn(
    *const libc::c_void,
    *const libc::c_void,
) -> libc::c_int;
pub type lh_hash_fn = unsafe extern "C" fn(*const libc::c_void) -> libc::c_ulong;
pub type lh_entry_free_fn = unsafe extern "C" fn(*mut crate::src::json_object::lh_entry) -> ();
#[derive(Copy, Clone)]
#[repr(C)]
pub struct json_object_iterator {
    pub opaque_: *const libc::c_void,
}
#[inline]
unsafe extern "C" fn lh_table_head(mut t: *const crate::src::json_object::lh_table) -> *mut crate::src::json_object::lh_entry {
    return (*t).head;
}
#[inline]
unsafe extern "C" fn lh_entry_v(mut e: *const crate::src::json_object::lh_entry) -> *mut libc::c_void {
    return (*e).v as uintptr_t as *mut libc::c_void;
}
#[inline]
unsafe extern "C" fn lh_entry_next(mut e: *const crate::src::json_object::lh_entry) -> *mut crate::src::json_object::lh_entry {
    return (*e).next;
}
static mut kObjectEndIterValue: *const libc::c_void = 0 as *const libc::c_void;
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_begin(
    mut obj: *mut crate::src::json_object::json_object,
) -> json_object_iterator {
    let mut iter: json_object_iterator = json_object_iterator {
        opaque_: 0 as *const libc::c_void,
    };
    let mut pTable: *mut crate::src::json_object::lh_table = 0 as *mut crate::src::json_object::lh_table;
    pTable = crate::src::json_object::json_object_get_object(obj);
    iter.opaque_ = lh_table_head(pTable) as *const libc::c_void;
    return iter;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_end(
    mut obj: *const crate::src::json_object::json_object,
) -> json_object_iterator {
    let mut iter: json_object_iterator = json_object_iterator {
        opaque_: 0 as *const libc::c_void,
    };
    iter.opaque_ = kObjectEndIterValue;
    return iter;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_next(mut iter: *mut json_object_iterator) {
    (*iter)
        .opaque_ = lh_entry_next((*iter).opaque_ as *const crate::src::json_object::lh_entry)
        as *const libc::c_void;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_peek_name(
    mut iter: *const json_object_iterator,
) -> *const libc::c_char {
    return (*((*iter).opaque_ as *const crate::src::json_object::lh_entry)).k as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_peek_value(
    mut iter: *const json_object_iterator,
) -> *mut crate::src::json_object::json_object {
    return lh_entry_v((*iter).opaque_ as *const crate::src::json_object::lh_entry) as *mut crate::src::json_object::json_object;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_equal(
    mut iter1: *const json_object_iterator,
    mut iter2: *const json_object_iterator,
) -> json_bool {
    return ((*iter1).opaque_ == (*iter2).opaque_) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn json_object_iter_init_default() -> json_object_iterator {
    let mut iter: json_object_iterator = json_object_iterator {
        opaque_: 0 as *const libc::c_void,
    };
    iter.opaque_ = 0 as *const libc::c_void;
    return iter;
}
