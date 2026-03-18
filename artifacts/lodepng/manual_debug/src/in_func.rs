use crate::*;
use std::os::raw::c_uchar;
use std::os::raw::c_void;


pub type InFunc = Option<unsafe extern "C" fn(*mut c_void, *mut *mut c_uchar) -> u32>;

