use crate::*;
use std::ffi::CStr;


pub type Mi_Output_Fun = Option<extern "C" fn(msg: *const i8, arg: *mut std::ffi::c_void)>;

