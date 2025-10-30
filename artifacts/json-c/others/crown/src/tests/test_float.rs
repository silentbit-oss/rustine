use ::libc;
extern "C" {
    
    
    
    
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
}
unsafe fn main_0() -> libc::c_int {
    let mut json: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    json = crate::src::json_object::json_object_new_double(1.0f64);
    printf(
        b"json = %s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(json, (1 as libc::c_int) << 1 as libc::c_int),
    );
    crate::src::json_object::json_object_put(json);
    json = crate::src::json_object::json_object_new_double(-1.0f64);
    printf(
        b"json = %s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(json, (1 as libc::c_int) << 1 as libc::c_int),
    );
    crate::src::json_object::json_object_put(json);
    json = crate::src::json_object::json_object_new_double(1.23f64);
    printf(
        b"json = %s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(json, (1 as libc::c_int) << 1 as libc::c_int),
    );
    crate::src::json_object::json_object_put(json);
    json = crate::src::json_object::json_object_new_double(123456789.0f64);
    printf(
        b"json = %s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(json, (1 as libc::c_int) << 1 as libc::c_int),
    );
    crate::src::json_object::json_object_put(json);
    json = crate::src::json_object::json_object_new_double(123456789.123f64);
    printf(
        b"json = %s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(json, (1 as libc::c_int) << 1 as libc::c_int),
    );
    crate::src::json_object::json_object_put(json);
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
