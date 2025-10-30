use crate::*;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Write;
use std::io;
use std::str::FromStr;

pub fn run(name: Option<&str>, in_path: Option<&str>, out_path: Option<&str>) {
    // Check for None (equivalent to NULL checks in C)
    let info = match ti_find_indicator(name) {
        Some(i) => i,
        None => {
            eprintln!("(ERROR) Couldn't find indicator {:?}", name);
            return;
        }
    };

    // Open input file
    let fin = match File::open(in_path.unwrap()) {
        Ok(f) => f,
        Err(_) => {
            eprintln!("(ERROR) Couldn't open {:?} for input.", in_path);
            return;
        }
    };

    let mut reader = BufReader::new(fin);
    let line = match next_line(&mut reader) {
        Some(l) => l,
        None => {
            eprintln!("(ERROR) Failed to read line from input file");
            return;
        }
    };

    // Parse options from the first line
    let mut options = [0.0; 16];
    let mut o_idx = 0;
    
    for token in line.split_whitespace() {
        if o_idx >= 16 {
            break;
        }
        options[o_idx] = match f64::from_str(token) {
            Ok(val) => val,
            Err(_) => {
                eprintln!("(ERROR) Failed to parse option: {}", token);
                return;
            }
        };
        o_idx += 1;
    }

    // Validate number of options
    if o_idx != info.options as usize {
        eprintln!(
            "(ERROR) Invalid number of options for {:?}. Expected {}, got {}",
            name, info.options, o_idx
        );
        return;
    }

    // Read input arrays
    let mut inputs: Vec<Vec<f64>> = Vec::with_capacity(info.inputs as usize);
    let mut input_size = 0;
    
    for _ in 0..info.inputs {
        let mut input = vec![0.0; 8192];
        input_size = match get_array(&mut reader, &mut input) {
            Some(size) => size,
            None => {
                eprintln!("(ERROR) Failed to read input array");
                return;
            }
        };
        inputs.push(input);
    }

    // Prepare output arrays
    let mut outputs: Vec<Vec<f64>> = Vec::with_capacity(info.outputs as usize);
    for _ in 0..info.outputs {
        outputs.push(vec![0.0; 8192]);
    }

    // Convert inputs and outputs to slices for the indicator function
    let input_slices: Vec<&[f64]> = inputs.iter().map(|v| v.as_slice()).collect();
    let mut output_slices: Vec<&mut [f64]> = outputs.iter_mut().map(|v| v.as_mut_slice()).collect();

    // Call the indicator function
    let ret = (info.indicator)(
        input_size as i32,
        &input_slices,
        &options[..o_idx],
        &mut output_slices,
    );

    if ret != 0 {
        eprintln!("(ERROR) Return value for {:?} of {}", name, ret);
        return;
    }

    // Open output file
    let mut fout = match File::create(out_path.unwrap()) {
        Ok(f) => f,
        Err(_) => {
            eprintln!("(ERROR) Couldn't open {:?} for output.", out_path);
            return;
        }
    };

    // Calculate output size
    let out_size = match &info.start {
        Some(start_fn) => input_size - start_fn(&options[..o_idx]) as usize,
        None => input_size,
    };

    // Write outputs
    for output in outputs {
        write!(fout, "{{").unwrap();
        for (j, val) in output[..out_size].iter().enumerate() {
            write!(fout, "{}", val).unwrap();
            if j != (out_size - 1) {
                write!(fout, ",").unwrap();
            }
        }
        writeln!(fout, "}}").unwrap();
    }
}
