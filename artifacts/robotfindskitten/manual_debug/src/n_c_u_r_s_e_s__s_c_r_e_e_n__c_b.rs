use crate::*;
use std::os::raw::c_int;


pub type NcursesScreenCb = Option<Box<dyn FnMut(*mut Screen, *mut std::ffi::c_void) -> c_int>>;

