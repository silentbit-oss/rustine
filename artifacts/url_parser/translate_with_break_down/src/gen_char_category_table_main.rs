use std::env;
use translate_new::*;
pub fn main() {
    fill(Category::Scheme as u16, Some(ALNUM), Some(b"+-."));
    fill(Category::Unreserved as u16, Some(ALNUM), Some(UNRESERVED.as_bytes()));
    fill(Category::GenDelim as u16, Some(ALNUM), Some(b":/?#[]@"));
    fill(Category::SubDelim as u16, Some(ALNUM), Some(SUBDELIM.as_bytes()));
    fill(Category::PCharSlash as u16, Some(ALNUM), Some(b":@/%"));
    fill(Category::PCharSlash as u16, Some(UNRESERVED.as_bytes()), Some(SUBDELIM.as_bytes()));
    fill(Category::HexDigit as u16, Some(b"0123456789"), Some(b"abcdefABCDEF"));
    fill(Category::Query as u16, Some(ALNUM), Some(b"/?:@%"));
    fill(Category::Query as u16, Some(UNRESERVED.as_bytes()), Some(SUBDELIM.as_bytes()));
    fill(Category::Userinfo as u16, Some(ALNUM), Some(b":%"));
    fill(Category::Userinfo as u16, Some(UNRESERVED.as_bytes()), Some(SUBDELIM.as_bytes()));
    fill(Category::IPv6Char as u16, Some(b"0123456789"), Some(b"abcdefABCDEF:"));
    print_table();
}
