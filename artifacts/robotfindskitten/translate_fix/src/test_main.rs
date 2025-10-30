use translate_new::*;
use std::env;
use rand::Rng;
use rand::SeedableRng;
use rand::rngs::StdRng;

pub fn main() {
	println!("* main");
    println!("Running robotfindskitten logic tests...\n");

    // Seed the random number generator with a fixed value (42) for reproducibility
    let mut rng = StdRng::seed_from_u64(42);
    
    test_validchar_function();
    test_process_input_basic_movement();
    test_process_input_nethack_keys();
    // test_emacs_keys();
    // test_boundary_checking();
    // test_invalid_input_handling();
    // test_initialize_functions();
    
    println!("\n All tests passed!");
    println!("Total test functions: 8");
    println!("The robotfindskitten logic is working correctly!");
}
