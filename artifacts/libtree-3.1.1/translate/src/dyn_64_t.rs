use crate::*;
use std::os::raw::c_longlong;
use std::os::raw::c_ulonglong;


#[derive(Clone)]
pub struct Dyn64T {
    pub d_tag: c_longlong,
    pub d_val: c_ulonglong,
}

