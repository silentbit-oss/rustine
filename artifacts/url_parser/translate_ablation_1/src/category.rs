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
    Fragment = 0x80,  // Changed from 0x40 to 0x80 to avoid duplicate
    Userinfo = 0x100, // Shifted up to accommodate Fragment change
    IPv6Char = 0x200, // Shifted up to maintain spacing
}

// Since Rust doesn't allow duplicate discriminant values in enums,
// we provide an alternative implementation using associated constants
pub struct CategoryConstants;
impl CategoryConstants {
    pub const SCHEME: u32 = 0x01;
    pub const UNRESERVED: u32 = 0x02;
    pub const GEN_DELIM: u32 = 0x04;
    pub const SUB_DELIM: u32 = 0x08;
    pub const PCHAR_SLASH: u32 = 0x10;
    pub const HEX_DIGIT: u32 = 0x20;
    pub const QUERY: u32 = 0x40;
    pub const FRAGMENT: u32 = 0x40;  // Kept same as original for bit flag compatibility
    pub const USERINFO: u32 = 0x80;
    pub const IPV6_CHAR: u32 = 0x100;
}

