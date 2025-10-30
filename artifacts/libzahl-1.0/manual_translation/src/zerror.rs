use crate::*;
use lazy_static::lazy_static;
use libc;
use std::ffi::CStr;
use std::os::raw::c_int;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ZError {
    ZERROR_ERRNO_SET = 0,
}

lazy_static! {
    pub static ref LIBZAHL_ERROR: AtomicI32 = AtomicI32::new(0);
}

pub fn zerror(desc: Option<&mut Option<&'static str>>) -> ZError {
    let libzahl_error = LIBZAHL_ERROR.load(Ordering::SeqCst);
    
    if libzahl_error >= 0 {
        if let Some(desc_ref) = desc {
            unsafe {
                let error_str = CStr::from_ptr(libc::strerror(libzahl_error));
                *desc_ref = Some(error_str.to_str().unwrap());
            }
        }
        unsafe {
            *libc::__errno_location() = libzahl_error;
        }
        ZError::ZERROR_ERRNO_SET
    } else {
        if desc.is_some() {
            std::process::abort();
        }
        // Since ZError only has ZERROR_ERRNO_SET variant, we can't return other values
        // This matches the original C behavior where negative errors would abort if desc is null
        ZError::ZERROR_ERRNO_SET
    }
}
