use crate::*;
use lazy_static::lazy_static;
use rand::Rng;
use std::f64;
use std::fs::File;
use std::io::Read;
use std::io::Write;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

pub fn sigmoid() {
    let mut i = -20.0;
    const MAX: f64 = 20.0;
    const D: f64 = 0.0001;
    
    // Create a dummy neural network for testing
    let dummy_ann = genann_init(1, 0, 0, 1).expect("Failed to create dummy ann");
    
    while i < MAX {
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            let sigmoid_val = genann_act_sigmoid(&dummy_ann, i);
            let sigmoid_cached_val = genann_act_sigmoid_cached(&dummy_ann, i);
            if f64::abs(sigmoid_val - sigmoid_cached_val) > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                    251,
                    sigmoid_val,
                    sigmoid_cached_val
                );
            }
        }
        i += D;
    }
}

pub fn basic() {
    let mut ann = genann_init(1, 0, 0, 1).expect("Failed to initialize genann");
    let mut a: f64;

    // First test: check total_weights
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ann.total_weights != 2 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 37, ann.total_weights, 2);
        }
    }

    // Initialize weights and test with a=0
    a = 0.0;
    ann.weight.as_mut().unwrap()[0] = 0.0;
    ann.weight.as_mut().unwrap()[1] = 0.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 44, 0.5, output[0]);
        }
    }

    // Test with a=1
    a = 1.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 47, 0.5, output[0]);
        }
    }

    // Test with a=11
    a = 11.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 50, 0.5, output[0]);
        }
    }

    // Change weights and test with a=1
    a = 1.0;
    ann.weight.as_mut().unwrap()[0] = 1.0;
    ann.weight.as_mut().unwrap()[1] = 1.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (0.5 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 55, 0.5, output[0]);
        }
    }

    // Test with a=10
    a = 10.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (1.0 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 60, 1.0, output[0]);
        }
    }

    // Test with a=-10
    a = -10.0;
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let output = genann_run(&mut ann, &[a]).unwrap();
        if (0.0 - output[0]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 63, 0.0, output[0]);
        }
    }

    // Free the ann
    genann_free(Some(Box::new(ann)));
}

pub fn copy() {
    let first = genann_init(1000, 5, 50, 10).expect("Failed to initialize genann");
    let second = genann_copy(&first).expect("Failed to copy genann");

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.inputs != second.inputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 229, first.inputs, second.inputs);
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden_layers != second.hidden_layers {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 230, first.hidden_layers, second.hidden_layers);
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden != second.hidden {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 231, first.hidden, second.hidden);
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.outputs != second.outputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 232, first.outputs, second.outputs);
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.total_weights != second.total_weights {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 233, first.total_weights, second.total_weights);
        }
    }

    if let (Some(first_weights), Some(second_weights)) = (&first.weight, &second.weight) {
        for i in 0..first.total_weights as usize {
            {
                LTESTS.fetch_add(1, Ordering::SeqCst);
                if f64::abs(first_weights[i] - second_weights[i]) > 0.001 {
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 237, first_weights[i], second_weights[i]);
                }
            }
        }
    }

    genann_free(Some(Box::new(first)));
    genann_free(Some(Box::new(second)));
}
pub fn xor() {
    let mut ann = match genann_init(2, 1, 2, 1) {
        Some(ann) => ann,
        None => return,
    };

    ann.activation_hidden = genann::GenannActFun::Threshold;
    ann.activation_output = genann::GenannActFun::Threshold;

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ann.total_weights != 9 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!(
                "{}:{} ({} != {})",
                "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                74,
                ann.total_weights,
                9
            );
        }
    }

    if let Some(ref mut weights) = ann.weight {
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

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if let Some(result) = genann_run(&mut ann, &input[0]) {
            if f64::abs(output[0] - result[0]) > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                    95,
                    output[0],
                    result[0]
                );
            }
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if let Some(result) = genann_run(&mut ann, &input[1]) {
            if f64::abs(output[1] - result[0]) > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                    96,
                    output[1],
                    result[0]
                );
            }
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if let Some(result) = genann_run(&mut ann, &input[2]) {
            if f64::abs(output[2] - result[0]) > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                    97,
                    output[2],
                    result[0]
                );
            }
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if let Some(result) = genann_run(&mut ann, &input[3]) {
            if f64::abs(output[3] - result[0]) > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "{}:{} ({} != {})",
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c",
                    98,
                    output[3],
                    result[0]
                );
            }
        }
    }

    genann_free(Some(Box::new(ann)));
}
pub fn backprop() {
    let mut ann = match genann_init(1, 0, 0, 1) {
        Some(a) => a,
        None => return,
    };

    let input = [0.5];
    let output = [1.0];
    
    let first_try = match genann_run(&mut ann, &input) {
        Some(result) => result[0],
        None => return,
    };

    genann_train(&mut ann, &input, &output, 0.5);

    let second_try = match genann_run(&mut ann, &input) {
        Some(result) => result[0],
        None => return,
    };

    LTESTS.fetch_add(1, Ordering::SeqCst);
    if !(f64::abs(first_try - output[0]) > f64::abs(second_try - output[0])) {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 114);
    }

    genann_free(Some(Box::new(ann)));
}

pub fn persist() {
    let first = genann_init(1000, 5, 50, 10).expect("Failed to initialize genann");
    
    // Write to file
    let mut out = File::create("persist.txt").expect("Failed to create file");
    genann_write(&first, &mut out).expect("Failed to write genann");
    drop(out); // Explicitly close the file
    
    // Read from file
    let mut in_file = File::open("persist.txt").expect("Failed to open file");
    let second = genann_read(&mut in_file).expect("Failed to read genann");
    drop(in_file); // Explicitly close the file

    // Compare fields
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.inputs != second.inputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 208, first.inputs, second.inputs);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden_layers != second.hidden_layers {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 209, first.hidden_layers, second.hidden_layers);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.hidden != second.hidden {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 210, first.hidden, second.hidden);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.outputs != second.outputs {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 211, first.outputs, second.outputs);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if first.total_weights != second.total_weights {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 212, first.total_weights, second.total_weights);
        }
    }
    
    if let (Some(first_weights), Some(second_weights)) = (&first.weight, &second.weight) {
        for i in 0..first.total_weights as usize {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if first_weights[i] != second_weights[i] {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/genann/test.c", 216);
            }
        }
    }

    genann_free(Some(Box::new(first)));
    genann_free(Some(Box::new(second)));
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

    ann.activation_output = genann::GenannActFun::Threshold;

    // Test each input-output pair
    for i in 0..4 {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[i])
            .and_then(|out| out.first().copied())
            .unwrap_or(0.0);
        if f64::abs(output[i] - result) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!(
                "/workdir/C2RustTranslation-main/subjects/genann/test.c:{} ({} != {})",
                135 + i,
                output[i],
                result
            );
        }
    }

    genann_free(Some(Box::new(ann)));
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

    ann.activation_output = genann::GenannActFun::Threshold;

    // Test each input-output pair
    for i in 0..4 {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[i]);
        if let Some(res) = result {
            if (output[i] - res[0]).abs() > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c:{} ({} != {})",
                    186 + i,
                    output[i],
                    res[0]
                );
            }
        }
    }

    genann_free(Some(Box::new(ann)));
}
pub fn train_or() {
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 1.0];
    
    let mut ann = match genann_init(2, 0, 0, 1) {
        Some(ann) => ann,
        None => return,
    };
    
    genann_randomize(&mut ann);
    
    for _ in 0..50 {
        for j in 0..4 {
            genann_train(&mut ann, &input[j], &output[j..j+1], 0.8);
        }
    }
    
    ann.activation_output = genann::GenannActFun::Threshold;
    
    // Test each input/output pair
    for i in 0..4 {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let result = genann_run(&mut ann, &input[i]);
        if let Some(res) = result {
            if (output[i] - res[0]).abs() > 0.001 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!(
                    "/workdir/C2RustTranslation-main/subjects/genann/test.c:{} ({} != {})",
                    160 + i,
                    output[i],
                    res[0]
                );
            }
        }
    }
    
    genann_free(Some(Box::new(ann)));
}
