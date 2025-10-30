use crate::binn::binn;
use std::env;
use std::ffi::CString;
use std::os::raw::c_char;
use translate_without_break_down::*;

pub fn main() {
	println!("\n* main");
    println!("\nStarting the unit/regression tests...\n");
    println!("sizeof(binn) = {}\n", std::mem::size_of::<binn>());

    test_binn_version();
    test_endianess();
    test_int64();
    test_floating_point_numbers();
    test1();
    test2(0);
    test2(1);
    test_binn2();
    test3();
    test_invalid_binn();

    println!("\nAll tests pass! :)\n");
}
