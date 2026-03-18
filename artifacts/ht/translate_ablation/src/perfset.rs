use std::any::Any;
use std::env;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::process;
use std::time::Instant;
use std::time::SystemTime;
use translate_new::*;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("usage: perftest file");
        process::exit(1);
    }

    let mut f = match File::open(&args[1]) {
        Ok(file) => file,
        Err(_) => {
            eprintln!("can't open file: {}", args[1]);
            process::exit(1);
        }
    };

    let size = match f.seek(SeekFrom::End(0)) {
        Ok(size) => size,
        Err(_) => {
            eprintln!("failed to seek to end of file");
            process::exit(1);
        }
    };

    f.seek(SeekFrom::Start(0))?;

    let mut contents = vec![0; size as usize];
    let nread = f.read(&mut contents)?;
    if nread != size as usize {
        eprintln!("read {} bytes instead of {}", nread, size);
        process::exit(1);
    }

    drop(f); // Equivalent to fclose

    let mut counts = match ht_create() {
        Some(table) => table,
        None => exit_nomem(),
    };

    let mut p_idx = 0;
    while p_idx < contents.len() {
        // Skip whitespace
        while p_idx < contents.len() && contents[p_idx] <= b' ' {
            p_idx += 1;
        }

        if p_idx >= contents.len() {
            break;
        }

        let word_start = p_idx;
        while p_idx < contents.len() && contents[p_idx] > b' ' {
            p_idx += 1;
        }

        let word = if p_idx < contents.len() {
            contents[p_idx] = 0;
            &contents[word_start..p_idx]
        } else {
            &contents[word_start..]
        };

        let word_str = std::str::from_utf8(word).ok();

        if let Some(entry) = ht_get(&counts, word_str) {
            if let Some(pcount) = entry.value.as_ref().and_then(|v| v.downcast_ref::<i32>()) {
                let new_count = pcount + 1;
                ht_set(&mut counts, word_str, Some(Box::new(new_count)));
            }
        } else {
            let pcount = Box::new(1);
            if ht_set(&mut counts, word_str, Some(pcount as Box<dyn Any>)).is_none() {
                exit_nomem();
            }
        }
    }

    let mut keys = Vec::with_capacity(ht_length(&counts));
    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        if let Some(ref key) = it.key {
            keys.push(key.clone());
        }
    }

    let mut table = match ht_create() {
        Some(t) => t,
        None => exit_nomem(),
    };

    let test_value = 1;
    let start = Instant::now();
    for key in &keys {
        if ht_set(&mut table, Some(key), Some(Box::new(test_value) as Box<dyn Any>)).is_none() {
            exit_nomem();
        }
    }
    let elapsed_ms = start.elapsed().as_secs_f64() * 1000.0;

    println!("setting {} keys: {:.09}ms", ht_length(&counts), elapsed_ms);
    Ok(())
}

pub fn exit_nomem() -> ! {
    process::exit(1);
}
