use std::env;
use std::fs::File;
use std::io::Read;
use std::io;
use std::process;
use translate_without_break_down::*;
pub fn main() {
    println!("GENANN example 3.");
    println!("Load a saved ANN to solve the XOR function.");

    let saved = File::open(SAVE_NAME);
    let mut saved = match saved {
        Ok(file) => file,
        Err(_) => {
            println!("Couldn't open file: {}", SAVE_NAME);
            process::exit(1);
        }
    };

    let ann = genann_read(&mut saved);
    drop(saved); // Equivalent to fclose in C

    let mut ann = match ann {
        Some(ann) => ann,
        None => {
            println!("Error loading ANN from file: {}.", SAVE_NAME);
            process::exit(1);
        }
    };

    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];

    for i in 0..4 {
        let mut ann_clone = ann.clone();
        let output = genann_run(&mut ann_clone, &input[i]);
        match output {
            Some(out) => {
                println!(
                    "Output for [{:.1}, {:.1}] is {:.1}.",
                    input[i][0], input[i][1], out[0]
                );
            }
            None => {
                println!("Error running ANN for input: [{:.1}, {:.1}]", input[i][0], input[i][1]);
            }
        }
    }

    genann_free(Some(Box::new(ann)));
}
