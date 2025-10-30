use ::libc;
extern "C" {
    fn gzclose_r(file: gzFile) -> libc::c_int;
}
pub type __off64_t = libc::c_long;
pub type off64_t = __off64_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct gzFile_s {
    pub have: libc::c_uint,
    pub next: *mut libc::c_uchar,
    pub pos: off64_t,
}
pub type gzFile = *mut gzFile_s;
#[no_mangle]
pub unsafe extern "C" fn gzclose(mut file: gzFile) -> libc::c_int {
    return gzclose_r(file);
}
