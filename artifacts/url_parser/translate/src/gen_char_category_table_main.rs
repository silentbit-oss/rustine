use translate::*;
use std::env;
// Correct usage of the dependencies
pub fn main() {
    // Fill the character classes with their respective values
    fill(1, Some(ALNUM), Some("+-."));
    fill(2, Some(ALNUM), Some(unreserved));
    fill(3, Some(ALNUM), Some(":/?#[]@"));
    fill(4, Some(ALNUM), Some(subdelim));
    fill(5, Some(ALNUM), Some(":@/%"));
    fill(5, Some(unreserved), Some(subdelim));
    fill(6, Some("0123456789"), Some("abcdefABCDEF"));
    fill(7, Some(ALNUM), Some("/?:@%"));
    fill(7, Some(unreserved), Some(subdelim));
    fill(8, Some(ALNUM), Some(":%"));
    fill(8, Some(unreserved), Some(subdelim));
    fill(9, Some("0123456789"), Some("abcdefABCDEF:"));

    // Print the character category table
    print_table();
}

