use translate::*;
use std::env;
use std::io;
use std::process;
use std::fs::File;
use std::io::Read;

pub fn main() {
    println!("GENANN example 3.");
    println!("Load a saved ANN to solve the XOR function.");
    
    let mut saved = match File::open(*SAVE_NAME) {
        Ok(file) => file,
        Err(_) => {
            println!("Couldn't open file: {}", *SAVE_NAME);
            process::exit(1);
        }
    };

    let mut ann = match genann_read(&mut saved) {
        Some(ann) => ann,
        None => {
            println!("Error loading ANN from file: {}.", *SAVE_NAME);
            process::exit(1);
        }
    };

    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    
    for i in 0..4 {
        let output = genann_run(&mut ann, &input[i]).unwrap_or(&[0.0]);
        println!("Output for [{:.1}, {:.1}] is {:.1}.", input[i][0], input[i][1], output[0]);
    }

    genann_free(Some(Box::new(ann)));
}
