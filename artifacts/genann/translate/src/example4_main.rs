use translate::*;
use std::env;
use std::process;
use rand::Rng;
pub fn main() {
    println!("GENANN example 4.");
    println!("Train an ANN on the IRIS dataset using backpropagation.");
    
    // Initialize random number generator
    let mut rng = rand::thread_rng();
    
    load_data();
    
    let mut ann = match genann_init(4, 1, 4, 3) {
        Some(a) => a,
        None => {
            eprintln!("Failed to initialize ANN");
            process::exit(1);
        }
    };
    
    let loops = 5000;
    println!("Training for {} loops over data.", loops);
    
    for _ in 0..loops {
        for j in 0..SAMPLES.load(std::sync::atomic::Ordering::SeqCst) {
            unsafe {
                if let Some(input) = &mut INPUT {
                    let input_slice = &input[j as usize * 4..(j as usize * 4 + 4)];
                    let class_guard = CLASS.lock().unwrap();
                    let class_data = class_guard.as_ref().unwrap();
                    let class_slice = &class_data[j as usize * 3..(j as usize * 3 + 3)];
                    genann_train(&mut ann, input_slice, class_slice, 0.01);
                }
            }
        }
    }
    
    let mut correct = 0;
    for j in 0..SAMPLES.load(std::sync::atomic::Ordering::SeqCst) {
        unsafe {
            if let Some(input) = &mut INPUT {
                let input_slice = &input[j as usize * 4..(j as usize * 4 + 4)];
                let guess = genann_run(&mut ann, input_slice).unwrap();
                let class_guard = CLASS.lock().unwrap();
                let class_data = class_guard.as_ref().unwrap();
                let class_slice = &class_data[j as usize * 3..(j as usize * 3 + 3)];
                
                if class_slice[0] == 1.0 {
                    if guess[0] > guess[1] && guess[0] > guess[2] {
                        correct += 1;
                    }
                } else if class_slice[1] == 1.0 {
                    if guess[1] > guess[0] && guess[1] > guess[2] {
                        correct += 1;
                    }
                } else if class_slice[2] == 1.0 {
                    if guess[2] > guess[0] && guess[2] > guess[1] {
                        correct += 1;
                    }
                } else {
                    println!("Logic error.");
                    process::exit(1);
                }
            }
        }
    }
    
    let samples = SAMPLES.load(std::sync::atomic::Ordering::SeqCst);
    println!("{}/{} correct ({:.1}%).", 
        correct, 
        samples, 
        (correct as f64 / samples as f64) * 100.0
    );
    
    // In Rust, memory is automatically managed, so no explicit free is needed
    // The Genann will be dropped when it goes out of scope
}
