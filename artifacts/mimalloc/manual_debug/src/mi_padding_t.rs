use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct MiPaddingS {
    pub canary: u32,
    pub delta: u32,
}

pub type MiPaddingT = MiPaddingS;

