use std::fs::File;
use std::fs::OpenOptions;
use crate::*;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Write;
use std::str::FromStr;

pub fn run(name: Option<&str>, in_: Option<&str>, out: Option<&str>) {
	println!("\n* run");
    // Check for None (equivalent to NULL checks in C)
    let name = match name {
        Some(n) => n,
        None => return,
    };
    let in_ = match in_ {
        Some(i) => i,
        None => return,
    };
    let out = match out {
        Some(o) => o,
        None => return,
    };

    // Find indicator info
    let info = match ti_find_indicator(Some(name)) {
        Some(i) => {
            let ti_indicators = TI_INDICATORS.lock().unwrap();
            unsafe { &*(&ti_indicators[i] as *const TiIndicatorInfo) }
        },
        None => {
            eprintln!("(ERROR) Couldn't find indicator {}", name);
            return;
        }
    };

    // Open input file
    let fin = match File::open(in_) {
        Ok(f) => f,
        Err(_) => {
            eprintln!("(ERROR) Couldn't open {} for input.", in_);
            return;
        }
    };

    // Read first line and parse options
    let mut reader = BufReader::new(fin);
    let mut line = String::new();
    if let Err(_) = reader.read_line(&mut line) {
        eprintln!("(ERROR) Couldn't read from input file.");
        return;
    }

    let mut options = [0.0; 16];
    let mut o_idx = 0;
    for s in line.split_whitespace() {
        if o_idx >= 16 {
            break;
        }
        options[o_idx] = match f64::from_str(s) {
            Ok(val) => val,
            Err(_) => {
                eprintln!("(ERROR) Invalid option value: {}", s);
                return;
            }
        };
        o_idx += 1;
    }

    // Validate number of options
    if o_idx != info.options as usize {
        eprintln!(
            "(ERROR) Invalid number of options for {}. Expected {}, got {}",
            name, info.options, o_idx
        );
        return;
    }

    // Read input arrays
    let mut inputs: Vec<Vec<f64>> = Vec::with_capacity(info.inputs as usize);
    let mut input_size = 0;
    for _ in 0..info.inputs {
        let mut input = vec![0.0; 8192];
        //let file = reader.get_mut();
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

    // Call indicator function
    let ret = (info.indicator)(
        input_size as i32,
        Some(&input_slices),
        Some(&options[..o_idx]),
        Some(&mut output_slices),
    );
    if ret != 0 {
        eprintln!("(ERROR) Return value for {} of {}.", name, ret);
        return;
    }

    // Open output file
    let mut fout = match OpenOptions::new().write(true).create(true).open(out) {
        Ok(f) => f,
        Err(_) => {
            eprintln!("(ERROR) Couldn't open {} for output.", out);
            return;
        }
    };

    // Calculate output size and write results
    let start = match &info.start {
        Some(func) => func(&options[..o_idx]),
        None => 0,
    };
    let out_size = input_size - start as usize;

    for output in outputs.iter().take(info.outputs as usize) {
        write!(fout, "{{").unwrap();
        for j in 0..out_size {
            write!(
                fout,
                "{}{}",
                output[j],
                if j == out_size - 1 { "" } else { "," }
            )
            .unwrap();
        }
        writeln!(fout, "}}").unwrap();
    }
}
