use rand::Rng;
use std::env;
use std::process::exit;
use translate_without_break_down::*;

pub fn main() {
    println!("GENANN example 4.");
    println!("Train an ANN on the IRIS dataset using backpropagation.");
    
    // Initialize random number generator (no direct srand equivalent in Rust)
    let mut rng = rand::thread_rng();
    
    load_data().expect("Failed to load data");
    
    let mut ann = genann_init(4, 1, 4, 3).expect("Failed to initialize ANN");
    
    let loops = 5000;
    println!("Training for {} loops over data.", loops);
    
    for _ in 0..loops {
        let input_guard = INPUT.lock().unwrap();
        let class_guard = CLASS.lock().unwrap();
        let samples = SAMPLES.load(std::sync::atomic::Ordering::SeqCst);
        
        if let (Some(input), Some(class)) = (&*input_guard, &*class_guard) {
            for j in 0..samples {
                let input_slice = &input[j as usize * 4..(j as usize * 4 + 4)];
                let class_slice = &class[j as usize * 3..(j as usize * 3 + 3)];
                genann_train(&mut ann, input_slice, class_slice, 0.01);
            }
        }
    }
    
    let mut correct = 0;
    let input_guard = INPUT.lock().unwrap();
    let class_guard = CLASS.lock().unwrap();
    let samples = SAMPLES.load(std::sync::atomic::Ordering::SeqCst);
    
    if let (Some(input), Some(class)) = (&*input_guard, &*class_guard) {
        for j in 0..samples {
            let input_slice = &input[j as usize * 4..(j as usize * 4 + 4)];
            let guess = genann_run(&mut ann, input_slice).expect("Failed to run ANN");
            
            if class[j as usize * 3] == 1.0 {
                if guess[0] > guess[1] && guess[0] > guess[2] {
                    correct += 1;
                }
            } else if class[j as usize * 3 + 1] == 1.0 {
                if guess[1] > guess[0] && guess[1] > guess[2] {
                    correct += 1;
                }
            } else if class[j as usize * 3 + 2] == 1.0 {
                if guess[2] > guess[0] && guess[2] > guess[1] {
                    correct += 1;
                }
            } else {
                println!("Logic error.");
                exit(1);
            }
        }
    }
    
    println!(
        "{}/{} correct ({:.1}%).",
        correct,
        samples,
        (correct as f64 / samples as f64) * 100.0
    );
    
    genann_free(Some(Box::new(ann)));
    
    // In Rust, the Mutex guards will be dropped automatically when they go out of scope
    // The lazy_static values will remain for the program lifetime
}
