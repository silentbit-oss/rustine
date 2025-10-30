use crate::*;
use lazy_static::lazy_static;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Error;
use std::io::ErrorKind;
use std::str::FromStr;
use std::sync::atomic::Ordering;

pub fn load_data() -> Result<(), Error> {
    // Open the file
    let in_file = File::open(IRIS_DATA)?;
    let mut reader = BufReader::new(in_file);

    // First pass: count samples
    let mut samples = 0;
    let mut line = String::new();
    while reader.read_line(&mut line)? > 0 {
        samples += 1;
        line.clear();
    }

    // Reset file position
    let in_file = File::open(IRIS_DATA)?;
    let mut reader = BufReader::new(in_file);

    println!("Loading {} data points from {}", samples, IRIS_DATA);

    // Allocate memory for input and class
    let input_vec = vec![0.0; samples * 4];
    let class_vec = vec![0.0; samples * 3];

    // Store in global variables
    *INPUT.lock().unwrap() = Some(input_vec.into_boxed_slice());
    *CLASS.lock().unwrap() = Some(class_vec.into_boxed_slice());
    SAMPLES.store(samples.try_into().unwrap(), Ordering::SeqCst);

    // Second pass: read data
    let mut line = String::new();
    for i in 0..samples {
        line.clear();
        if reader.read_line(&mut line)? == 0 {
            return Err(Error::new(ErrorKind::Other, "fgets failed"));
        }

        let parts: Vec<&str> = line.trim_end().split(',').collect();
        if parts.len() != 5 {
            return Err(Error::new(ErrorKind::Other, "Invalid data format"));
        }

        // Get mutable references to input and class
        let mut input_guard = INPUT.lock().unwrap();
        let mut class_guard = CLASS.lock().unwrap();

        let input = input_guard.as_mut().unwrap();
        let class = class_guard.as_mut().unwrap();

        // Parse input features
        for j in 0..4 {
            input[i * 4 + j] = f64::from_str(parts[j]).map_err(|_| {
                Error::new(ErrorKind::InvalidData, "Failed to parse feature value")
            })?;
        }

        // Set class
        match parts[4] {
            name if name == CLASS_NAMES[0] => class[i * 3] = 1.0,
            name if name == CLASS_NAMES[1] => class[i * 3 + 1] = 1.0,
            name if name == CLASS_NAMES[2] => class[i * 3 + 2] = 1.0,
            _ => {
                return Err(Error::new(
                    ErrorKind::InvalidData,
                    format!("Unknown class {}", parts[4]),
                ))
            }
        }
    }

    Ok(())
}
