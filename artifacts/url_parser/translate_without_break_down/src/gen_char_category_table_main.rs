use translate_without_break_down::*;
use std::env;
pub fn main() {
    fill(Category::Scheme as u16, Some(ALNUM), Some("+-."));
    fill(Category::Unreserved as u16, Some(ALNUM), Some(UNRESERVED));
    fill(Category::GenDelim as u16, Some(ALNUM), Some(":/?#[]@"));
    fill(Category::SubDelim as u16, Some(ALNUM), Some(SUBDELIM));
    fill(Category::PCharSlash as u16, Some(ALNUM), Some(":@/%"));
    fill(Category::PCharSlash as u16, Some(UNRESERVED), Some(SUBDELIM));
    fill(Category::HexDigit as u16, Some("0123456789"), Some("abcdefABCDEF"));
    fill(Category::Query as u16, Some(ALNUM), Some("/?:@%"));
    fill(Category::Query as u16, Some(UNRESERVED), Some(SUBDELIM));
    fill(Category::Userinfo as u16, Some(ALNUM), Some(":%"));
    fill(Category::Userinfo as u16, Some(UNRESERVED), Some(SUBDELIM));
    fill(Category::IPv6Char as u16, Some("0123456789"), Some("abcdefABCDEF:"));
    print_table();
}
