use ::libc;
extern "C" {
    fn setlocale_null_r_unlocked(
        category: libc::c_int,
        buf: *mut libc::c_char,
        bufsize: size_t,
    ) -> libc::c_int;
    fn setlocale_null_unlocked(category: libc::c_int) -> *const libc::c_char;
}
pub type size_t = libc::c_ulong;
#[no_mangle]
pub unsafe extern "C" fn setlocale_null_r(
    mut category: libc::c_int,
    mut buf: *mut libc::c_char,
    mut bufsize: size_t,
) -> libc::c_int {
    return setlocale_null_r_unlocked(category, buf, bufsize);
}
#[no_mangle]
pub unsafe extern "C" fn setlocale_null(
    mut category: libc::c_int,
) -> *const libc::c_char {
    return setlocale_null_unlocked(category);
}
