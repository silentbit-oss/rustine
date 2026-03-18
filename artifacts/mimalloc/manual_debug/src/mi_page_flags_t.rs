use crate::*;
use std::mem::ManuallyDrop;
use std::mem;


pub union MiPageFlagsS {
    pub full_aligned: u8,
    pub x: ManuallyDrop<MiPageFlagsStruct>,
}

pub struct MiPageFlagsStruct {
    pub in_full: u8,
    pub has_aligned: u8,
}

pub type MiPageFlagsT = MiPageFlagsS;

