use translate::*;
use std::env;
use std::println;
use std::process;

pub fn main() {
    if test_create_destroy() != 0 {
        process::exit(1);
    }
    println!("test_create_destroy passed.");

    if test_register_write_normal() != 0 {
        process::exit(1);
    }
    println!("test_register_write_normal passed.");

    if test_register_write_edge() != 0 {
        process::exit(1);
    }
    println!("test_register_write_edge passed.");

    if test_register_write_illegal() != 0 {
        process::exit(1);
    }
    println!("test_register_write_illegal passed.");

    if test_audio_generation_stress() != 0 {
        process::exit(1);
    }
    println!("test_audio_generation_stress passed.");

    if test_multiple_create_destroy() != 0 {
        process::exit(1);
    }
    println!("test_multiple_create_destroy passed.");

    if test_midi_functions() != 0 {
        process::exit(1);
    }
    println!("test_midi_functions passed.");

    if test_pitch_wheel_bounds() != 0 {
        process::exit(1);
    }
    println!("test_pitch_wheel_bounds passed.");

    if test_clamp_function() != 0 {
        process::exit(1);
    }
    println!("test_clamp_function passed.");

    if test_min_max_macros() != 0 {
        process::exit(1);
    }
    println!("test_min_max_macros passed.");

    println!("All tests passed.");
    process::exit(0);
}
