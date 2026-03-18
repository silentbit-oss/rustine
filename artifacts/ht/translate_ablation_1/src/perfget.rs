use std::any::Any;
use std::boxed::Box;
use std::env;
use std::fs::File;
use std::io::BufRead;
use std::io::Read;
use std::io;
use std::time::Instant;
use translate_new::*;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("usage: perftest file");
        return Ok(());
    }

    let mut f = std::fs::File::open(&args[1])?;
    let size = f.metadata()?.len() as i64;
    
    let mut contents = vec![0u8; size as usize + 1];
    let nread = f.read(&mut contents[0..size as usize])?;
    
    if nread != size as usize {
        eprintln!("read {} bytes instead of {}", nread, size);
        return Ok(());
    }
    
    contents[size as usize] = 0;
    
    let mut counts = ht_create();
    if counts.is_none() {
        exit_nomem();
    }
    
    let mut p_ptr = 0;
    while p_ptr < contents.len() && contents[p_ptr] != 0 {
        // Skip whitespace
        while p_ptr < contents.len() && contents[p_ptr] != 0 && contents[p_ptr] <= b' ' {
            p_ptr += 1;
        }
        
        if p_ptr >= contents.len() || contents[p_ptr] == 0 {
            break;
        }
        
        let word_start = p_ptr;
        
        // Find word end
        while p_ptr < contents.len() && contents[p_ptr] != 0 && contents[p_ptr] > b' ' {
            p_ptr += 1;
        }
        
        let word_end = p_ptr;
        
        if word_end < contents.len() && contents[word_end] != 0 {
            contents[word_end] = 0;
        }
        
        let word = &contents[word_start..word_end];
        let word_str = std::str::from_utf8(word).unwrap();
        
        // Use ht_get to get the value and check if it exists
        let entry_value = ht_get(counts.as_ref().unwrap(), Some(word_str));
        if let Some(entry) = entry_value {
            // Use as_ref to get an Option<&Box<dyn Any>>, then try downcasting to &i32
            if let Some(count_ref) = entry.value.as_ref().and_then(|v| v.downcast_ref::<i32>()) {
                // Create a new box with incremented value
                let new_value = Box::new(count_ref + 1) as Box<dyn std::any::Any>;
                // Update the hash table with the new value
                if ht_set(counts.as_mut().unwrap(), Some(word_str), Some(new_value)).is_none() {
                    exit_nomem();
                }
            }
            continue;
        }
        
        let pcount = Box::new(1) as Box<dyn std::any::Any>;
        if ht_set(counts.as_mut().unwrap(), Some(word_str), Some(pcount)).is_none() {
            exit_nomem();
        }
    }
    
    let keys_len = ht_length(counts.as_ref().unwrap());
    let mut keys = Vec::with_capacity(keys_len);
    
    let mut it = ht_iterator(counts.as_ref().unwrap());
    let mut i = 0;
    while ht_next(&mut it) {
        keys.push(it.key.clone());
        i += 1;
    }
    
    let runs = 10;
    let start = std::time::Instant::now();
    
    for _ in 0..runs {
        for j in 0..keys_len {
            let found = ht_get(counts.as_ref().unwrap(), keys[j].as_deref());
        }
    }
    
    let elapsed_ms = start.elapsed().as_secs_f64() * 1000.0;
    println!("{} runs getting {} keys: {:.03}ms", runs, keys_len, elapsed_ms);
    
    Ok(())
}
