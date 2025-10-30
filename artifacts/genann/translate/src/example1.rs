use translate::*;
use std::env;
use rand::Rng;

pub fn main() {
    println!("GENANN example 1.");
    println!("Train a small ANN to the XOR function using backpropagation.");
    
    // Initialize random number generator (Rust handles this automatically with thread_rng)
    let mut rng = rand::thread_rng();
    
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 0.0];
    
    let mut ann = match genann_init(2, 1, 2, 1) {
        Some(ann) => ann,
        None => {
            eprintln!("Failed to initialize ANN");
            return;
        }
    };
    
    for _ in 0..500 {
        genann_train(&mut ann, &input[0], &output[0..1], 3.0);
        genann_train(&mut ann, &input[1], &output[1..2], 3.0);
        genann_train(&mut ann, &input[2], &output[2..3], 3.0);
        genann_train(&mut ann, &input[3], &output[3..4], 3.0);
    }
    
    // Print results
    if let Some(result) = genann_run(&mut ann, &input[0]) {
        println!("Output for [{}, {}] is {}.", input[0][0], input[0][1], result[0]);
    }
    if let Some(result) = genann_run(&mut ann, &input[1]) {
        println!("Output for [{}, {}] is {}.", input[1][0], input[1][1], result[0]);
    }
    if let Some(result) = genann_run(&mut ann, &input[2]) {
        println!("Output for [{}, {}] is {}.", input[2][0], input[2][1], result[0]);
    }
    if let Some(result) = genann_run(&mut ann, &input[3]) {
        println!("Output for [{}, {}] is {}.", input[3][0], input[3][1], result[0]);
    }
    
    // No explicit free needed in Rust - ann will be dropped automatically
}
