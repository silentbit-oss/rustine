use ::libc;
extern "C" {
    
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    
    
    
    
    
    
    
    
    
    
    
}
pub type __int32_t = libc::c_int;
pub type __int64_t = libc::c_long;
pub type __uint64_t = libc::c_ulong;
pub type int32_t = __int32_t;
pub type int64_t = __int64_t;
pub type uint64_t = __uint64_t;
pub type json_bool = libc::c_int;
pub type json_type = libc::c_uint;
pub const json_type_string: json_type = 6;
pub const json_type_array: json_type = 5;
pub const json_type_object: json_type = 4;
pub const json_type_int: json_type = 3;
pub const json_type_double: json_type = 2;
pub const json_type_boolean: json_type = 1;
pub const json_type_null: json_type = 0;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut input: *const libc::c_char = b"{\n\t\t\"string_of_digits\": \"123\",\n\t\t\"regular_number\": 222,\n\t\t\"decimal_number\": 99.55,\n\t\t\"boolean_true\": true,\n\t\t\"boolean_false\": false,\n\t\t\"int64_number\": 2147483649,\n\t\t\"negative_number\": -321321321,\n\t\t\"a_null\": null,\n\t\t\"empty_array\": [],\n\t\t\"nonempty_array\": [ 123 ],\n\t\t\"array_with_zero\": [ 0 ],\n\t\t\"empty_object\": {},\n\t\t\"nonempty_object\": { \"a\": 123 },\n\t\t\"nan\": NaN,\n\t}\0"
        as *const u8 as *const libc::c_char;
    let mut new_obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    new_obj = crate::src::json_tokener::json_tokener_parse(input);
    printf(b"Parsed input: %s\n\0" as *const u8 as *const libc::c_char, input);
    printf(
        b"Result is %s\n\0" as *const u8 as *const libc::c_char,
        if new_obj.is_null() {std::intrinsics::assume((new_obj).addr() == 0);
            b"NULL (error!)\0" as *const u8 as *const libc::c_char
        } else {
            b"not NULL\0" as *const u8 as *const libc::c_char
        },
    );
    if new_obj.is_null() {std::intrinsics::assume((new_obj).addr() == 0);
        return 1 as libc::c_int;
    }
    getit(new_obj, b"string_of_digits\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"regular_number\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"decimal_number\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"boolean_true\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"boolean_false\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"int64_number\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"negative_number\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"a_null\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"empty_array\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"nonempty_array\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"array_with_zero\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"empty_object\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"nonempty_object\0" as *const u8 as *const libc::c_char);
    getit(new_obj, b"nan\0" as *const u8 as *const libc::c_char);
    printf(
        b"\n================================\n\0" as *const u8 as *const libc::c_char,
    );
    checktype_header();
    checktype(new_obj, 0 as *const libc::c_char);
    checktype(new_obj, b"string_of_digits\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"regular_number\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"decimal_number\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"boolean_true\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"boolean_false\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"int64_number\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"negative_number\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"a_null\0" as *const u8 as *const libc::c_char);
    checktype(new_obj, b"nan\0" as *const u8 as *const libc::c_char);
    crate::src::json_object::json_object_put(new_obj);
    return 0 as libc::c_int;
}
unsafe extern "C" fn getit(
    mut new_obj: *mut crate::src::json_object::json_object,
    mut field: *const libc::c_char,
) {
    let mut o: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    if crate::src::json_object::json_object_object_get_ex(new_obj, field, &raw mut o) == 0 {
        printf(
            b"Field %s does not exist\n\0" as *const u8 as *const libc::c_char,
            field,
        );
    }
    let mut o_type: json_type = crate::src::json_object::json_object_get_type(o);
    printf(
        b"new_obj.%s json_object_get_type()=%s\n\0" as *const u8 as *const libc::c_char,
        field,
        crate::src::json_util::json_type_to_name(o_type),
    );
    printf(
        b"new_obj.%s json_object_get_int()=%d\n\0" as *const u8 as *const libc::c_char,
        field,
        crate::src::json_object::json_object_get_int(o),
    );
    printf(
        b"new_obj.%s json_object_get_int64()=%ld\n\0" as *const u8
            as *const libc::c_char,
        field,
        crate::src::json_object::json_object_get_int64(o),
    );
    printf(
        b"new_obj.%s json_object_get_uint64()=%lu\n\0" as *const u8
            as *const libc::c_char,
        field,
        crate::src::json_object::json_object_get_uint64(o),
    );
    printf(
        b"new_obj.%s json_object_get_boolean()=%d\n\0" as *const u8
            as *const libc::c_char,
        field,
        crate::src::json_object::json_object_get_boolean(o),
    );
    printf(
        b"new_obj.%s json_object_get_double()=%f\n\0" as *const u8
            as *const libc::c_char,
        field,
        crate::src::json_object::json_object_get_double(o),
    );
}
unsafe extern "C" fn checktype_header() {
    printf(
        b"json_object_is_type: %s,%s,%s,%s,%s,%s,%s\n\0" as *const u8
            as *const libc::c_char,
        crate::src::json_util::json_type_to_name(json_type_null),
        crate::src::json_util::json_type_to_name(json_type_boolean),
        crate::src::json_util::json_type_to_name(json_type_double),
        crate::src::json_util::json_type_to_name(json_type_int),
        crate::src::json_util::json_type_to_name(json_type_object),
        crate::src::json_util::json_type_to_name(json_type_array),
        crate::src::json_util::json_type_to_name(json_type_string),
    );
}
unsafe extern "C" fn checktype(
    mut new_obj: *mut crate::src::json_object::json_object,
    mut field: *const libc::c_char,
) {
    let mut o: *mut crate::src::json_object::json_object = new_obj;
    if !field.is_null() && crate::src::json_object::json_object_object_get_ex(new_obj, field, &raw mut o) == 0 {
        printf(
            b"Field %s does not exist\n\0" as *const u8 as *const libc::c_char,
            field,
        );
    }
    printf(
        b"new_obj%s%-18s: %d,%d,%d,%d,%d,%d,%d\n\0" as *const u8 as *const libc::c_char,
        if !field.is_null() {
            b".\0" as *const u8 as *const libc::c_char
        } else {std::intrinsics::assume((field).addr() == 0);
            b" \0" as *const u8 as *const libc::c_char
        },
        if !field.is_null() { field } else {std::intrinsics::assume((field).addr() == 0); b"\0" as *const u8 as *const libc::c_char },
        crate::src::json_object::json_object_is_type(o, json_type_null),
        crate::src::json_object::json_object_is_type(o, json_type_boolean),
        crate::src::json_object::json_object_is_type(o, json_type_double),
        crate::src::json_object::json_object_is_type(o, json_type_int),
        crate::src::json_object::json_object_is_type(o, json_type_object),
        crate::src::json_object::json_object_is_type(o, json_type_array),
        crate::src::json_object::json_object_is_type(o, json_type_string),
    );
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
