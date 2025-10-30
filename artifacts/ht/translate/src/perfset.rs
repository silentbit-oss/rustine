use translate::*;
use std::env;
use std::fs::File;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Read;
use std::time::Instant;
use std::any::Any;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("usage: perftest file");
        return Ok(());
    }

    let mut f = match File::open(&args[1]) {
        Ok(file) => file,
        Err(e) => {
            eprintln!("can't open file: {}: {}", args[1], e);
            return Ok(());
        }
    };

    let size = f.metadata()?.len() as usize;
    f.seek(SeekFrom::Start(0))?;

    let mut contents = vec![0u8; size];
    let nread = f.read(&mut contents)?;
    if nread != size {
        eprintln!("read {} bytes instead of {}", nread, size);
        return Ok(());
    }

    let contents_str = match String::from_utf8(contents) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("invalid UTF-8 sequence: {}", e);
            return Ok(());
        }
    };

    let mut counts = match ht_create() {
        Some(ht) => ht,
        None => {
            exit_nomem();
            return Ok(());
        }
    };

    let mut p_idx = 0;
    let chars: Vec<char> = contents_str.chars().collect();
    while p_idx < chars.len() {
        while p_idx < chars.len() && chars[p_idx].is_whitespace() {
            p_idx += 1;
        }

        if p_idx >= chars.len() {
            break;
        }

        let word_start = p_idx;
        while p_idx < chars.len() && !chars[p_idx].is_whitespace() {
            p_idx += 1;
        }

        let word = &contents_str[word_start..p_idx];
        let val = ht_get(&counts, Some(word));

        if let Some(v) = val {
            if let Some(pcount) = v.downcast_ref::<i32>() {
                let new_count = pcount + 1;
                ht_set(&mut counts, Some(word), Some(Box::new(new_count)))
                    .ok_or("Failed to set value in hash table")?;
            }
            continue;
        }

        let pcount = Box::new(1);
        if ht_set(&mut counts, Some(word), Some(pcount)).is_none() {
            exit_nomem();
            return Ok(());
        }
    }

    let keys_len = ht_length(&counts);
    let mut keys = Vec::with_capacity(keys_len);
    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        if let Some(ref key) = it.key {
            keys.push(key.clone());
        }
    }

    let mut table = match ht_create() {
        Some(ht) => ht,
        None => {
            exit_nomem();
            return Ok(());
        }
    };

    let val = 1;
    let start = Instant::now();
    for key in &keys {
        if ht_set(&mut table, Some(key), Some(Box::new(val))).is_none() {
            exit_nomem();
            return Ok(());
        }
    }

    let elapsed_ms = start.elapsed().as_secs_f64() * 1000.0;
    println!("setting {} keys: {:.09}ms", ht_length(&table), elapsed_ms);

    Ok(())
}
