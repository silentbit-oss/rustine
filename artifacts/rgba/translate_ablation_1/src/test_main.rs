use std::env;
use translate_new::*;
pub fn main() {
    test_named();
    test_rgb();
    test_rgba();
    test_hex();
    test_to_string();
    println!("\n  \x1b[32m\u{2713} \x1b[90mok\x1b[0m\n\n");
}
