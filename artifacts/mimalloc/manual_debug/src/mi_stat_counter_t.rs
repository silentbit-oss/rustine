use crate::*;
use std::ffi::c_longlong;


#[derive(Clone)]
pub struct MiStatCounterS {
    pub total: c_longlong,
}

