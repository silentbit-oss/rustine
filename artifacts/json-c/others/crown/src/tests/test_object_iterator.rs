use ::libc;
extern "C" {
    
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    
    
    
    
    
    
    
    
    
    
}
pub type json_bool = libc::c_int;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor43 { dummy: () }
unsafe fn main_0(
    mut atgc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut input: *const libc::c_char = b"{\n\t\t\"string_of_digits\": \"123\",\n\t\t\"regular_number\": 222,\n\t\t\"decimal_number\": 99.55,\n\t\t\"boolean_true\": true,\n\t\t\"boolean_false\": false,\n\t\t\"big_number\": 2147483649,\n\t\t\"a_null\": null,\n\t\t}\0"
        as *const u8 as *const libc::c_char;
    let mut new_obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut it: crate::src::json_object_iterator::json_object_iterator = crate::src::json_object_iterator::json_object_iterator {
        opaque_: 0 as *const libc::c_void,
    };
    let mut itEnd: crate::src::json_object_iterator::json_object_iterator = crate::src::json_object_iterator::json_object_iterator {
        opaque_: 0 as *const libc::c_void,
    };
    it = crate::src::json_object_iterator::json_object_iter_init_default();
    new_obj = crate::src::json_tokener::json_tokener_parse(input);
    it = crate::src::json_object_iterator::json_object_iter_begin(new_obj);
    itEnd = crate::src::json_object_iterator::json_object_iter_end(new_obj);
    while crate::src::json_object_iterator::json_object_iter_equal(&raw mut it, &raw mut itEnd) == 0 {
        printf(
            b"%s\n\0" as *const u8 as *const libc::c_char,
            crate::src::json_object_iterator::json_object_iter_peek_name(&raw mut it),
        );
        printf(
            b"%s\n\0" as *const u8 as *const libc::c_char,
            crate::src::json_object::json_object_to_json_string(crate::src::json_object_iterator::json_object_iter_peek_value(&raw mut it)),
        );
        crate::src::json_object_iterator::json_object_iter_next(&raw mut it);
    }
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
