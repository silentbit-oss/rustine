use translate::*;
use std::env;
pub fn main() -> () {
    println!("\nStarting the unit/regression tests...\n");
    println!("sizeof(binn) = {}\n", std::mem::size_of::<Binn>());
    
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
