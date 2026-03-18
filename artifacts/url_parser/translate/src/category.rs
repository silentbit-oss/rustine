use crate::*;

pub struct Category;

impl Category {
    pub const SCHEME: u32 = 0x01;
    pub const UNRESERVED: u32 = 0x02;
    pub const GEN_DELIM: u32 = 0x04;
    pub const SUB_DELIM: u32 = 0x08;
    pub const PCHAR_SLASH: u32 = 0x10;
    pub const HEX_DIGIT: u32 = 0x20;
    pub const QUERY: u32 = 0x40;
    pub const FRAGMENT: u32 = 0x40; // This will be the same as the QUERY value
    pub const USERINFO: u32 = 0x80;
    pub const IPV6_CHAR: u32 = 0x100;
}

