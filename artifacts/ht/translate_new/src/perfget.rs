use translate_new::*;
use std::env;
use std::process;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::time::Instant;
use std::time::SystemTime;
use lazy_static::lazy_static;
use std::sync::Mutex;
lazy_static! {
    pub static ref FOUND: Mutex<Option<Box<dyn std::any::Any + Send>>> = Mutex::new(None);
}

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

    let size = f.seek(SeekFrom::End(0))?;
    f.seek(SeekFrom::Start(0))?;

    let mut contents = vec![0; size as usize + 1];
    let nread = f.read(&mut contents[..size as usize])?;

    if nread != size as usize {
        eprintln!("read {} bytes instead of {}", nread, size);
        return Ok(());
    }

    contents[size as usize] = 0;

    let mut counts = match ht_create() {
        Some(ht) => ht,
        None => {
            exit_nomem();
            return Ok(());
        }
    };

    let mut p_idx = 0;
    let contents_str = unsafe { std::str::from_utf8_unchecked(&contents) };
    let mut p = contents_str;

    while p_idx < p.len() {
        while p_idx < p.len() && p.as_bytes()[p_idx] <= b' ' {
            p_idx += 1;
        }

        let word_start = p_idx;
        while p_idx < p.len() && p.as_bytes()[p_idx] > b' ' {
            p_idx += 1;
        }

        let word = &p[word_start..p_idx];
        if p_idx < p.len() {
            // In C, this would null-terminate, but in Rust we just slice
        }

        if let Some(entry) = ht_get(&counts, Some(word)) {
            if let Some(pcount) = entry.value.as_ref().and_then(|v| v.downcast_ref::<i32>()) {
                let pcount = *pcount + 1;
                let new_count = Box::new(pcount);
                if ht_set(&mut counts, Some(word), Some(new_count as Box<dyn std::any::Any>)).is_none() {
                    exit_nomem();
                    return Ok(());
                }
                continue;
            }
        }

        let pcount = Box::new(1);
        if ht_set(&mut counts, Some(word), Some(pcount as Box<dyn std::any::Any>)).is_none() {
            exit_nomem();
            return Ok(());
        }
    }

    let keys_len = ht_length(&counts);
    let mut keys = Vec::with_capacity(keys_len);
    let mut it = ht_iterator(&counts);
    let mut i = 0;
    while ht_next(&mut it) {
        if let Some(key) = &it.key {
            keys.push(key.clone());
            i += 1;
        }
    }

    let runs = 10;
    let start = Instant::now();
    for _run in 0..runs {
        for i in 0..keys_len {
            let key = &keys[i];
            if let Some(entry) = ht_get(&counts, Some(key)) {
                if let Some(entry_value) = entry.value.as_ref() {
                    if let Some(pcount) = entry_value.downcast_ref::<i32>() {
                        *FOUND.lock().unwrap() = Some(Box::new(*pcount) as Box<dyn std::any::Any + Send>);
                    }
                }
            }
        }
    }
    let end = Instant::now();
    let elapsed_ms = (end - start).as_secs_f64() * 1000.0;
    println!("{} runs getting {} keys: {:.03}ms", runs, keys_len, elapsed_ms);

    Ok(())
}
