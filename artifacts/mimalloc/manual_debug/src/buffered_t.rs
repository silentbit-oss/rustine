use crate::*;
use std::ffi::CStr;


pub type Mi_Output_Fun = Option<extern "C" fn(msg: *const i8, arg: *mut std::ffi::c_void)>;


pub struct BufferedS {
    pub out: Mi_Output_Fun,
    pub arg: Option<Box<std::ffi::c_void>>,
    pub buf: Option<Vec<i8>>,
    pub used: usize,
    pub count: usize,
}

