use crate::*;
use std::clone::Clone;


#[derive(Clone)]
pub struct CompatT {
    pub any: char,
    pub class: u8,
    pub machine: u16,
}

