use crate::*;

#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LfsError {
    Ok = 0,
    Io = -5,
    Corrupt = -84,
    Noent = -2,
    Exist = -17,
    Notdir = -20,
    Isdir = -21,
    Notempty = -39,
    Badf = -9,
    Fbig = -27,
    Inval = -22,
    Nospc = -28,
    Nomem = -12,
    Noattr = -61,
    Nametoolong = -36,
}

