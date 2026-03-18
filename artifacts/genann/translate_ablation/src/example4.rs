use crate::*;
use lazy_static::lazy_static;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Error;
use std::io::ErrorKind;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::process::exit;
use std::str::FromStr;
use std::sync::atomic::Ordering;

pub fn load_data() -> Result<(), Box<dyn std::error::Error>> {
    let in_file = File::open("example/iris.data")?;
    let mut reader = BufReader::new(in_file);
    
    let mut samples = 0;
    for line in reader.by_ref().lines() {
        let line = line?;
        if !line.is_empty() {
            samples += 1;
        }
    }
    
    reader.seek(SeekFrom::Start(0))?;
    println!("Loading {} data points from {}", samples, IRIS_DATA);
    
    let mut input = vec![0.0; samples * 4];
    let mut class = vec![0.0; samples * 3];
    
    for i in 0..samples {
        let p = &mut input[i * 4..(i + 1) * 4];
        let c = &mut class[i * 3..(i + 1) * 3];
        c.fill(0.0);
        
        let mut line = String::new();
        reader.read_line(&mut line)?;
        
        let mut parts = line.trim_end().split(',');
        for j in 0..4 {
            if let Some(split) = parts.next() {
                p[j] = split.parse()?;
            }
        }
        
        if let Some(split) = parts.next() {
            let class_name = split.trim_end();
            if class_name == CLASS_NAMES[0] {
                c[0] = 1.0;
            } else if class_name == CLASS_NAMES[1] {
                c[1] = 1.0;
            } else if class_name == CLASS_NAMES[2] {
                c[2] = 1.0;
            } else {
                println!("Unknown class {}.", class_name);
                return Err("Unknown class".into());
            }
        }
    }
    
    Ok(())
}
