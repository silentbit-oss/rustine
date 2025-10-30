use translate::*;
use std::env;
use std::fs::File;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Read;
use std::time::Instant;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("usage: perftest file");
        return Ok(());
    }

    let mut f = std::fs::File::open(&args[1])?;
    let size = f.metadata()?.len() as usize;

    let mut contents = vec![0u8; size + 1];
    let nread = f.read(&mut contents[..size])?;
    if nread != size {
        eprintln!("read {} bytes instead of {}", nread, size);
        return Ok(());
    }
    contents[size] = 0;

    let mut counts = match ht_create() {
        Some(c) => c,
        None => {
            exit_nomem();
            return Ok(());
        }
    };

    let contents_str = unsafe { std::str::from_utf8_unchecked(&contents[..size]) };
    let mut p_idx = 0;
    let chars: Vec<char> = contents_str.chars().collect();

    while p_idx < chars.len() {
        while p_idx < chars.len() && chars[p_idx] <= ' ' {
            p_idx += 1;
        }

        let word_start = p_idx;
        while p_idx < chars.len() && chars[p_idx] > ' ' {
            p_idx += 1;
        }

        if word_start >= p_idx {
            continue;
        }

        let word = &contents_str[word_start..p_idx];
        let word_value = ht_get(&counts, Some(word));
        
        if let Some(pcount) = word_value {
            if let Some(pcount) = pcount.downcast_ref::<i32>() {
                let new_count = pcount + 1;
                let _ = ht_set(&mut counts, Some(word), Some(Box::new(new_count)));
            }
            continue;
        }

        let pcount = Box::new(1);
        if ht_set(&mut counts, Some(word), Some(pcount)).is_none() {
            exit_nomem();
            return Ok(());
        }
    }

    let mut keys = Vec::with_capacity(ht_length(&counts));
    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        if let Some(ref key) = it.key {
            keys.push(key.clone());
        }
    }

    let runs = 10;
    let start = std::time::Instant::now();
    for _ in 0..runs {
        for key in &keys {
            let _ = ht_get(&counts, Some(key));
        }
    }
    let elapsed_ms = start.elapsed().as_millis();

    println!("{} runs getting {} keys: {}ms", runs, ht_length(&counts), elapsed_ms);
    Ok(())
}
