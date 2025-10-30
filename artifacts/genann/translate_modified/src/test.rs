use crate::*;
use std::f64;
use std::io;
use std::sync::atomic::Ordering;
use std::fs::File;
use std::io::Read;
use std::io::Write;

pub fn sigmoid() {
    let mut i = -20.0;
    const MAX: f64 = 20.0;
    const D: f64 = 0.0001;
    
    // Create a dummy Genann instance once to use throughout the function
    let dummy_genann = Genann {
        inputs: 0,
        hidden_layers: 0,
        hidden: 0,
        outputs: 0,
        activation_hidden: genann_act_linear,
        activation_output: genann_act_linear,
        total_weights: 0,
        total_neurons: 0,
        output: None,
        delta: None,
        weight: None,
    };

    while i < MAX {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let diff = f64::abs(genann_act_sigmoid(&dummy_genann, i) - genann_act_sigmoid_cached(&dummy_genann, i));
        if diff > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!(
                "{}:{} ({} != {})",
                "/c2rust_final/subjects/genann/test.c",
                251,
                genann_act_sigmoid(&dummy_genann, i),
                genann_act_sigmoid_cached(&dummy_genann, i)
            );
        }
        i += D;
    }
}
pub fn basic() {
    let mut ann = genann_init(1, 0, 0, 1).expect("Failed to initialize genann");
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ann.total_weights != 2 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 37, ann.total_weights, 2);
        }
    }

    let mut a = 0.0;
    {
        ann.weight.as_mut().unwrap()[0] = 0.0;
        ann.weight.as_mut().unwrap()[1] = 0.0;
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 44, 0.5, output[0]);
        }
    }

    a = 1.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 47, 0.5, output[0]);
        }
    }

    a = 11.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 50, 0.5, output[0]);
        }
    }

    a = 1.0;
    {
        ann.weight.as_mut().unwrap()[0] = 1.0;
        ann.weight.as_mut().unwrap()[1] = 1.0;
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 55, 0.5, output[0]);
        }
    }

    a = 10.0;
    {
        ann.weight.as_mut().unwrap()[0] = 1.0;
        ann.weight.as_mut().unwrap()[1] = 1.0;
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (1.0 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 60, 1.0, output[0]);
        }
    }

    a = -10.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let input = [a];
        let output = genann_run(&mut ann, &input).unwrap();
        if (0.0 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/c2rust_final/subjects/genann/test.c", 63, 0.0, output[0]);
        }
    }
}
pub fn copy() {
    let first = genann_init(1000, 5, 50, 10).expect("Failed to initialize genann");
    let second = genann_copy(&first).expect("Failed to copy genann");

    // Test inputs
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.inputs != second.inputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("/c2rust_final/subjects/genann/test.c:229 ({} != {})", first.inputs, second.inputs);
        }
    }

    // Test hidden_layers
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden_layers != second.hidden_layers {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("/c2rust_final/subjects/genann/test.c:230 ({} != {})", first.hidden_layers, second.hidden_layers);
        }
    }

    // Test hidden
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden != second.hidden {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("/c2rust_final/subjects/genann/test.c:231 ({} != {})", first.hidden, second.hidden);
        }
    }

    // Test outputs
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.outputs != second.outputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("/c2rust_final/subjects/genann/test.c:232 ({} != {})", first.outputs, second.outputs);
        }
    }

    // Test total_weights
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.total_weights != second.total_weights {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("/c2rust_final/subjects/genann/test.c:233 ({} != {})", first.total_weights, second.total_weights);
        }
    }

    // Test weights
    if let (Some(first_weights), Some(second_weights)) = (&first.weight, &second.weight) {
        for i in 0..first.total_weights as usize {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if (first_weights[i] - second_weights[i]).abs() > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("/c2rust_final/subjects/genann/test.c:237 ({} != {})", first_weights[i], second_weights[i]);
            }
        }
    }

    // No explicit free needed in Rust, values will be dropped automatically
}
pub fn xor() {
    let mut ann = genann_init(2, 1, 2, 1).expect("Failed to initialize genann");
    ann.activation_hidden = genann_act_threshold;
    ann.activation_output = genann_act_threshold;
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ann.total_weights != 9 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 74, ann.total_weights, 9);
        }
    }
    
    {
        let weights = ann.weight.as_mut().expect("Weights not initialized");
        weights[0] = 0.5;
        weights[1] = 1.0;
        weights[2] = 1.0;
        weights[3] = 1.0;
        weights[4] = 1.0;
        weights[5] = 1.0;
        weights[6] = 0.5;
        weights[7] = 1.0;
        weights[8] = -1.0;
    }
    
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 0.0];
    
    for i in 0..4 {
        let result = genann_run(&mut ann, &input[i]).expect("Failed to run genann");
        let diff = (output[i] - result[0]).abs();
        
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if diff > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 95 + i, output[i], result[0]);
        }
    }
}
pub fn backprop() {
    let mut ann = genann_init(1, 0, 0, 1).expect("Failed to initialize genann");
    let input = [0.5];
    let output = [1.0];
    
    let first_try = {
        let result = genann_run(&mut ann, &input).expect("genann_run failed");
        result[0]
    };
    
    genann_train(&mut ann, &input, &output, 0.5);
    
    let second_try = {
        let result = genann_run(&mut ann, &input).expect("genann_run failed");
        result[0]
    };
    
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if !(f64::abs(first_try - output[0]) > f64::abs(second_try - output[0])) {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/c2rust_final/subjects/genann/test.c", 114);
    }
    
    // genann_free is not needed in Rust as the value will be dropped automatically
}

pub fn persist() {
    let first = match genann_init(1000, 5, 50, 10) {
        Some(ann) => ann,
        None => {
            eprintln!("Failed to initialize genann");
            return;
        }
    };

    // Write to file
    let mut out = match File::create("persist.txt") {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Failed to create file: {}", e);
            return;
        }
    };
    if let Err(e) = genann_write(&first, &mut out) {
        eprintln!("Failed to write genann: {}", e);
        return;
    }
    drop(out); // Explicitly close the file

    // Read from file
    let mut in_file = match File::open("persist.txt") {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Failed to open file: {}", e);
            return;
        }
    };
    let second = match genann_read(&mut in_file) {
        Some(ann) => ann,
        None => {
            eprintln!("Failed to read genann");
            return;
        }
    };
    drop(in_file); // Explicitly close the file

    // Test comparisons
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.inputs != second.inputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 208, first.inputs, second.inputs);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden_layers != second.hidden_layers {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 209, first.hidden_layers, second.hidden_layers);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden != second.hidden {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 210, first.hidden, second.hidden);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.outputs != second.outputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 211, first.outputs, second.outputs);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.total_weights != second.total_weights {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 212, first.total_weights, second.total_weights);
        }
    }

    if let (Some(first_weights), Some(second_weights)) = (&first.weight, &second.weight) {
        for i in 0..first.total_weights as usize {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if first_weights[i] != second_weights[i] {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/c2rust_final/subjects/genann/test.c", 216);
            }
        }
    }

    // No explicit free needed in Rust - values will be dropped automatically
}

pub fn train_and() {
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 0.0, 0.0, 1.0];
    
    let mut ann = genann_init(2, 0, 0, 1).expect("Failed to initialize genann");
    
    for _ in 0..50 {
        for j in 0..4 {
            genann_train(&mut ann, &input[j], &output[j..j+1], 0.8);
        }
    }
    
    ann.activation_output = genann_act_threshold;
    
    // Test each input case
    for i in 0..4 {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[i]).unwrap()[0];
        if f64::abs(output[i] - result) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!(
                "{}:{} ({} != {})",
                "/c2rust_final/subjects/genann/test.c",
                135 + i,
                output[i],
                result
            );
        }
    }
    
    // No explicit free needed - ann will be dropped automatically
}
pub fn train_xor() {
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 0.0];
    
    let mut ann = match genann_init(2, 1, 2, 1) {
        Some(ann) => ann,
        None => return,
    };

    for _ in 0..500 {
        for j in 0..4 {
            genann_train(&mut ann, &input[j], &output[j..j+1], 3.0);
        }
    }

    ann.activation_output = genann_act_threshold;

    // Test each input/output pair
    for i in 0..4 {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[i]).and_then(|r| r.first().copied());
        if let Some(result) = result {
            if (output[i] - result).abs() > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/c2rust_final/subjects/genann/test.c",
                    186 + i,
                    output[i],
                    result
                );
            }
        }
    }
}
pub fn train_or() {
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 1.0];
    
    let mut ann = genann_init(2, 0, 0, 1).expect("Failed to initialize genann");
    genann_randomize(&mut ann);

    for _ in 0..50 {
        for j in 0..4 {
            genann_train(&mut ann, &input[j], &output[j..j+1], 0.8);
        }
    }

    ann.activation_output = genann_act_threshold;

    // Test cases
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[0]).unwrap()[0];
        if (output[0] - result).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 160, output[0], result);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[1]).unwrap()[0];
        if (output[1] - result).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 161, output[1], result);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[2]).unwrap()[0];
        if (output[2] - result).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 162, output[2], result);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[3]).unwrap()[0];
        if (output[3] - result).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/genann/test.c", 163, output[3], result);
        }
    }
}
