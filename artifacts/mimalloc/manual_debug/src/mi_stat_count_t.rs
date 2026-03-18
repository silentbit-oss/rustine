use crate::*;
use std::ffi::c_longlong;


#[derive(Clone)]
pub struct MiStatCountS {
    pub total: c_longlong,
    pub peak: c_longlong,
    pub current: c_longlong,
}

