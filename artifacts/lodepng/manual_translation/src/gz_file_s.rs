use crate::*;
use std::fs::File;
use std::os::raw::c_uint;


#[derive(Clone)]
pub struct GzFileS {
    pub have: c_uint,
    pub next: Option<Vec<u8>>,
    pub pos: off_t,
}

pub type off_t = i64; // Assuming a typical 64-bit off_t; adjust if needed for your platform

