use translate::*;
use std::env;
use std::process;
use rand::Rng;
use std::sync::atomic::Ordering;
pub fn main() {
    // Handle command line arguments
    let args: Vec<String> = std::env::args().collect();
    
    if args.len() == 1 {
        NUM_BOGUS.store(20, Ordering::SeqCst);
    } else {
        let num = args[1].parse::<i32>().unwrap_or_else(|_| {
            println!("Run-time parameter must be between 0 and {}.", MESSAGES.len());
            process::exit(0);
        });

        if num < 0 || num > MESSAGES.len() as i32 {
            println!("Run-time parameter must be between 0 and {}.", MESSAGES.len());
            process::exit(0);
        }

        NUM_BOGUS.store(num, Ordering::SeqCst);
    }

    // Initialize random number generator
    let mut rng = rand::thread_rng();
    let _ = rng.gen::<u32>(); // Equivalent to seeding with time(0)

    // Print escape sequence
    print!("{}{}{}", 27 as char, '(', 'U');

    // Initialize game components
    initialize_ncurses();
    initialize_arrays();
    initialize_robot();
    initialize_kitten();
    initialize_bogus();
    instructions();
    initialize_screen();
    play_game();
}
