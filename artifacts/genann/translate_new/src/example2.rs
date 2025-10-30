use rand::Rng;
use std::env;
use std::f64;
use translate_without_break_down::*;

pub fn main() {
    println!("GENANN example 2.");
    println!("Train a small ANN to the XOR function using random search.");

    let mut rng = rand::thread_rng();
    let input = [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]];
    let output = [0.0, 1.0, 1.0, 0.0];

    let mut ann = match genann_init(2, 1, 2, 1) {
        Some(ann) => ann,
        None => return,
    };

    let mut last_err = 1000.0;
    let mut count = 0;
    let mut err;

    loop {
        count += 1;
        if count % 1000 == 0 {
            genann_randomize(&mut ann);
            last_err = 1000.0;
        }

        let mut save = match genann_copy(&ann) {
            Some(save) => save,
            None => break,
        };

        if let Some(weights) = &mut save.weight {
            for w in weights.iter_mut() {
                *w += rng.gen::<f64>() - 0.5;
            }
        }

        err = 0.0;
        if let Some(out) = genann_run(&mut save, &input[0]) {
            err += (out[0] - output[0]).powi(2);
        }
        if let Some(out) = genann_run(&mut save, &input[1]) {
            err += (out[0] - output[1]).powi(2);
        }
        if let Some(out) = genann_run(&mut save, &input[2]) {
            err += (out[0] - output[2]).powi(2);
        }
        if let Some(out) = genann_run(&mut save, &input[3]) {
            err += (out[0] - output[3]).powi(2);
        }

        if err < last_err {
            last_err = err;
        } else {
            ann = save;
        }

        if err <= 0.01 {
            break;
        }
    }

    println!("Finished in {} loops.", count);
    
    if let Some(out) = genann_run(&mut ann, &input[0]) {
        println!("Output for [{}, {}] is {}.", input[0][0], input[0][1], out[0]);
    }
    if let Some(out) = genann_run(&mut ann, &input[1]) {
        println!("Output for [{}, {}] is {}.", input[1][0], input[1][1], out[0]);
    }
    if let Some(out) = genann_run(&mut ann, &input[2]) {
        println!("Output for [{}, {}] is {}.", input[2][0], input[2][1], out[0]);
    }
    if let Some(out) = genann_run(&mut ann, &input[3]) {
        println!("Output for [{}, {}] is {}.", input[3][0], input[3][1], out[0]);
    }
}
