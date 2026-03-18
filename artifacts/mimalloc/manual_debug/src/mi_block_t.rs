use crate::*;
use std::os::raw::c_void;


pub type mi_encoded_t = usize;

#[derive(Clone)]
pub struct MiBlockS {
    pub next: mi_encoded_t,
}

