use ::libc;
extern "C" {
    
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn snprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    
    
    
    
    
    
    
    fn setlocale(
        __category: libc::c_int,
        __locale: *const libc::c_char,
    ) -> *mut libc::c_char;
}
pub type size_t = libc::c_ulong;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut new_obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    setlocale(1 as libc::c_int, b"de_DE\0" as *const u8 as *const libc::c_char);
    let mut buf1: [libc::c_char; 10] = [0; 10];
    let mut buf2: [libc::c_char; 10] = [0; 10];
    snprintf(
        buf1.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong,
        b"%f\0" as *const u8 as *const libc::c_char,
        0.1f64,
    );
    new_obj = crate::src::json_tokener::json_tokener_parse(
        b"[1.2,3.4,123456.78,5.0,2.3e10]\0" as *const u8 as *const libc::c_char,
    );
    snprintf(
        buf2.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong,
        b"%f\0" as *const u8 as *const libc::c_char,
        0.1f64,
    );
    if strcmp(buf1.as_mut_ptr(), buf2.as_mut_ptr()) != 0 as libc::c_int {
        printf(
            b"ERROR: Original locale not restored \"%s\" != \"%s\"\0" as *const u8
                as *const libc::c_char,
            buf1.as_mut_ptr(),
            buf2.as_mut_ptr(),
        );
    }
    setlocale(1 as libc::c_int, b"C\0" as *const u8 as *const libc::c_char);
    printf(b"new_obj.to_string()=[\0" as *const u8 as *const libc::c_char);
    let mut ii: libc::c_uint = 0;
    ii = 0 as libc::c_int as libc::c_uint;
    while (ii as size_t) < crate::src::json_object::json_object_array_length(new_obj) {
        let mut val: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_array_get_idx(new_obj, ii as size_t);
        printf(
            b"%s%.2lf\0" as *const u8 as *const libc::c_char,
            if ii > 0 as libc::c_int as libc::c_uint {
                b",\0" as *const u8 as *const libc::c_char
            } else {
                b"\0" as *const u8 as *const libc::c_char
            },
            crate::src::json_object::json_object_get_double(val),
        );
        ii = ii.wrapping_add(1);
        ii;
    }
    printf(b"]\n\0" as *const u8 as *const libc::c_char);
    printf(
        b"new_obj.to_string()=%s\n\0" as *const u8 as *const libc::c_char,
        crate::src::json_object::json_object_to_json_string_ext(new_obj, (1 as libc::c_int) << 2 as libc::c_int),
    );
    crate::src::json_object::json_object_put(new_obj);
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
