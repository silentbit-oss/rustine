use crate::*;
use std::os::raw::c_void;pub type MiDeferredFreeFun = 
    extern "C" fn(force: bool, heartbeat: u64, arg: Option<Box<c_void>>);

