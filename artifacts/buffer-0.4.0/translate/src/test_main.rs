use translate::*;
use std::env;
pub fn main() {
    test_buffer_new();
    test_buffer_new_with_size();
    test_buffer_append();
    test_buffer_append__grow();
    test_buffer_append_n();
    test_buffer_prepend();
    test_buffer_slice();
    test_buffer_slice__range_error();
    test_buffer_slice__end();
    test_buffer_slice__end_overflow();
    test_buffer_equals();
    test_buffer_formatting();
    test_buffer_indexof();
    test_buffer_fill();
    test_buffer_clear();
    test_buffer_trim();
    test_buffer_compact();
    println!("\n  \x1b[32m\u{2713} \x1b[90mok\x1b[0m\n\n");
}
