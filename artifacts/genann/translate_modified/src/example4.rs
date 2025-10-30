use crate::*;
use std::io::BufRead;
use std::io;
use std::process;
use std::fs::File;
use std::sync::atomic::Ordering;

pub fn helper_load_data_1(j_ref: &mut i32, in_file: &mut impl io::BufRead, line: &mut String, i: i32) {
    let mut j = *j_ref;
    
    // Get mutable references to the global arrays
    let input = unsafe { INPUT.as_mut().expect("INPUT not initialized") };
    let p = &mut input[(i as usize * 4)..(i as usize * 4 + 4)];
    
    let mut class_lock = CLASS.lock().unwrap();
    let class = class_lock.as_mut().expect("CLASS not initialized");
    let c = &mut class[(i as usize * 3)..(i as usize * 3 + 3)];
    
    // Initialize c array
    c[0] = 0.0;
    c[1] = 0.0;
    c[2] = 0.0;
    
    // Read line
    line.clear();
    if in_file.read_line(line).unwrap() == 0 {
        eprintln!("fgets: {}", io::Error::last_os_error());
        process::exit(1);
    }
    
    // Trim newline and split by commas
    let line = line.trim_end();
    let mut splits = line.split(',');
    
    // Parse first 4 values as floats
    for j in 0..4 {
        if let Some(split) = splits.next() {
            p[j] = split.parse::<f64>().unwrap_or_else(|_| {
                eprintln!("Failed to parse float: {}", split);
                process::exit(1);
            });
        } else {
            eprintln!("Not enough values in line");
            process::exit(1);
        }
    }
    
    // Get the class name
    let split = splits.next().unwrap_or_else(|| {
        eprintln!("Missing class name in line");
        process::exit(1);
    });
    
    // Match class name
    match split {
        s if s == CLASS_NAMES[0] => c[0] = 1.0,
        s if s == CLASS_NAMES[1] => c[1] = 1.0,
        s if s == CLASS_NAMES[2] => c[2] = 1.0,
        _ => {
            eprintln!("Unknown class {}.", split);
            process::exit(1);
        }
    }
    
    *j_ref = j;
}

pub fn load_data() {
    // Open the file
    let in_file = match File::open(*IRIS_DATA) {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Could not open file: {}\nError: {}", *IRIS_DATA, e);
            process::exit(1);
        }
    };

    // Count lines to determine sample count
    let mut samples = 0;
    let mut reader = io::BufReader::new(in_file);
    let mut line = String::new();
    
    loop {
        line.clear();
        match reader.read_line(&mut line) {
            Ok(0) => break, // EOF
            Ok(_) => samples += 1,
            Err(e) => {
                eprintln!("Error reading file: {}", e);
                process::exit(1);
            }
        }
    }

    // Reset file position to beginning
    let in_file = match File::open(*IRIS_DATA) {
        Ok(file) => file,
        Err(e) => {
            eprintln!("Could not reopen file: {}\nError: {}", *IRIS_DATA, e);
            process::exit(1);
        }
    };
    let mut reader = io::BufReader::new(in_file);

    println!("Loading {} data points from {}", samples, *IRIS_DATA);
    
    // Update global samples count
    SAMPLES.store(samples, Ordering::SeqCst);

    // Allocate memory for input and class arrays
    unsafe {
        INPUT = Some(Box::leak(vec![0.0; samples as usize * 4].into_boxed_slice()));
    }
    
    {
        let mut class_lock = CLASS.lock().unwrap();
        *class_lock = Some(vec![0.0; samples as usize * 3].into_boxed_slice());
    }

    // Load data
    let mut j = 0;
    for i in 0..samples {
        helper_load_data_1(&mut j, &mut reader, &mut line, i);
    }
}
