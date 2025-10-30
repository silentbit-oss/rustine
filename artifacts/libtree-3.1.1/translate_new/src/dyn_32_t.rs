use crate::*;
use std::os::raw::c_int;


#[derive(Clone)]
pub struct Dyn32T {
    pub d_tag: i32,
    pub d_val: u32,
}

