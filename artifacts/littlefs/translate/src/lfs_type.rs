use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LfsType {
    Name = 0x000,
    Reg = 0x001,
    Dir = 0x002,
    From = 0x100,
    Struct = 0x200,
    Inlinestruct = 0x201,
    Ctzstruct = 0x202,
    Userattr = 0x300,
    Splice = 0x400,
    Create = 0x401,
    Delete = 0x4ff,
    Crc = 0x500,
    Fcrc = 0x5ff,
    Tail = 0x600,
    Hardtail = 0x601,
    Globals = 0x700,
    Movestate = 0x7ff,
    Superblock = 0x0ff,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LfsFrom {
    Noop = 0x000,
    Move = 0x101,
    Userattrs = 0x102,
}

