use std::env;
use std::fs::File;
use std::io::Read;
use std::io;
use std::process::exit;
use std::process;
use translate_without_break_down::*;
pub fn main() {
    println!("GENANN example 3.");
    println!("Load a saved ANN to solve the XOR function.");
    
    let mut saved = match File::open(SAVE_NAME) {
        Ok(file) => file,
        Err(_) => {
            println!("Couldn't open file: {}", SAVE_NAME);
            exit(1);
        }
    };
    
    let mut ann = genann_read(&mut saved);
    if ann.is_none() {
        println!("Error loading ANN from file: {}.", SAVE_NAME);
        exit(1);
    }
    
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    
    if let Some(output) = genann_run(ann.as_ref().unwrap(), &input[0]) {
        if let Some(first_output) = output.first() {
            println!("Output for [{:.1}, {:.1}] is {:.1}.", input[0][0], input[0][1], first_output);
        }
    }
    
    if let Some(output) = genann_run(ann.as_ref().unwrap(), &input[1]) {
        if let Some(first_output) = output.first() {
            println!("Output for [{:.1}, {:.1}] is {:.1}.", input[1][0], input[1][1], first_output);
        }
    }
    
    if let Some(output) = genann_run(ann.as_ref().unwrap(), &input[2]) {
        if let Some(first_output) = output.first() {
            println!("Output for [{:.1}, {:.1}] is {:.1}.", input[2][0], input[2][1], first_output);
        }
    }
    
    if let Some(output) = genann_run(ann.as_ref().unwrap(), &input[3]) {
        if let Some(first_output) = output.first() {
            println!("Output for [{:.1}, {:.1}] is {:.1}.", input[3][0], input[3][1], first_output);
        }
    }
    
    genann_free(ann.map(Box::new));
}
