use crate::*;
use std::convert::TryFrom;


#[derive(Clone)]
pub struct MiRandomCxtS {
    pub input: [u32; 16],
    pub output: [u32; 16],
    pub output_available: i32,
    pub weak: bool,
}

pub type MiRandomCtxT = MiRandomCxtS;

