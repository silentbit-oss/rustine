use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Category {
    Scheme = 0x01,
    Unreserved = 0x02,
    GenDelim = 0x04,
    SubDelim = 0x08,
    PCharSlash = 0x10,
    HexDigit = 0x20,
    Query = 0x40,
    Fragment = 0x200,
    Userinfo = 0x80,
    IPv6Char = 0x100,
}

// Since Rust doesn't allow duplicate discriminant values in enums,
// we provide a workaround using associated constants in an impl block
impl Category {
    pub const QUERY: Self = Self::Query;
    pub const FRAGMENT: Self = Self::Fragment;
}

