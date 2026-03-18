use crate::*;
use std::mem;


#[derive(Clone)]
pub struct Mi_Commit_Mask_S {
    pub mask: [usize; ((1usize << (9 + (13 + 3))) / (1usize << (13 + 3))) / ((1 << 3) * 8)],
}

pub type Mi_Commit_Mask_T = Mi_Commit_Mask_S;

