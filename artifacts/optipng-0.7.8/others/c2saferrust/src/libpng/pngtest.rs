

extern "C" {
    
    
    
    #[no_mangle]
    static mut stdout: *mut FILE;
    #[no_mangle]
    fn fprintf(_: *mut FILE, _: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
}
pub use crate::src::pngxtern::pngxread::_IO_marker;
pub use crate::src::pngxtern::pngxrpnm::_IO_wide_data;
pub use crate::src::pnmio::pnmout::_IO_codecvt;
pub type size_t = crate::src::gifread::gifread::size_t;
pub type __off_t = crate::src::gifread::gifread::__off_t;
pub type __off64_t = crate::src::gifread::gifread::__off64_t;
// #[derive(Copy, Clone)]

pub type _IO_FILE = crate::src::libpng::png::_IO_FILE;
pub type _IO_lock_t = crate::src::gifread::gifread::_IO_lock_t;
pub type FILE = crate::src::gifread::gifread::FILE;
/* For DOS */
/* Known chunks that exist in pngtest.png must be supported or pngtest will fail
 * simply as a result of re-ordering them.  This may be fixed in 1.7
 *
 * pngtest allocates a single row buffer for each row and overwrites it,
 * therefore if the write side doesn't support the writing of interlaced images
 * nothing can be done for an interlaced image (and the code below will fail
 * horribly trying to write extra data after writing garbage).
 */
/* else nothing can be done */
fn main_0() -> std::os::raw::c_int {
    println!(" test ignored because libpng was not built with read support");
    /* And skip this test */
    if 10634 < 10600 {
        0
    } else {
        77
    }
}

pub fn main() { let exit_code = main_0();
std::process::exit(exit_code as i32); }
