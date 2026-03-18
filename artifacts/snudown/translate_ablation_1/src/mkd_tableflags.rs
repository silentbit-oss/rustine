use crate::*;

#[derive(Clone, Copy, PartialEq, Eq)]
pub enum MkdTableFlags {
    MKD_TABLE_ALIGN_L = 1,
    MKD_TABLE_ALIGN_R = 2,
    MKD_TABLE_ALIGN_CENTER = 3,
    MKD_TABLE_HEADER = 4,
}

pub const MKD_TABLE_ALIGNMASK: u32 = 3;

