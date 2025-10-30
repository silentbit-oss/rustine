use crate::*;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum LfsWhenceFlags {
    Set = 0,
    Cur = 1,
    End = 2,
}

impl LfsWhenceFlags {
    pub const LFS_SEEK_SET: LfsWhenceFlags = LfsWhenceFlags::Set;
    pub const LFS_SEEK_CUR: LfsWhenceFlags = LfsWhenceFlags::Cur;
    pub const LFS_SEEK_END: LfsWhenceFlags = LfsWhenceFlags::End;
}

