use ::libc;
extern "C" {
    fn arc4random() -> __uint32_t;
}
pub type __uint32_t = libc::c_uint;
#[no_mangle]
pub unsafe extern "C" fn json_c_get_random_seed() -> libc::c_int {
    return arc4random() as libc::c_int;
}
