use translate::*;
use std::env;
use std::io;
use std::io::BufRead;
pub fn main() -> io::Result<()> {
    let mut counts = match ht_create() {
        Some(c) => c,
        None => {
            exit_nomem();
            return Ok(());
        }
    };

    let stdin = io::stdin();
    for line in stdin.lock().lines() {
        let line = line?;
        for word in line.split_whitespace() {
            if word.len() > 100 {
                continue; // Skip words longer than 100 characters
            }

            if let Some(entry_value) = ht_get(&counts, Some(word)) {
                if let Some(pcount) = entry_value.downcast_ref::<i32>() {
                    let pcount = pcount + 1;
                    if ht_set(&mut counts, Some(word), Some(Box::new(pcount))).is_none() {
                        exit_nomem();
                        return Ok(());
                    }
                }
            } else {
                let pcount = Box::new(1);
                if ht_set(&mut counts, Some(word), Some(pcount)).is_none() {
                    exit_nomem();
                    return Ok(());
                }
            }
        }
    }

    let mut it = ht_iterator(&counts);
    let mut total_probes = 0;
    while ht_next(&mut it) {
        total_probes += get_probe_len(&counts, it.key.as_deref());
        // No explicit free needed - Rust's ownership system handles memory
    }

    println!(
        "len={} cap={} avgprobe={:.3}",
        ht_length(&counts),
        counts.capacity,
        (total_probes as f64) / (ht_length(&counts) as f64)
    );

    // No explicit ht_destroy needed - Rust's ownership system will handle cleanup
    Ok(())
}
