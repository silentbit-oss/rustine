use translate_new::*;
use std::env;
use std::io::BufRead;
use std::io;
use std::any::Any;
use std::boxed::Box;

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
        let word = line?;
        let word = word.trim();

        if let Some(entry) = ht_get(&counts, Some(word)) {
            if let Some(pcount) = entry.value.as_ref().and_then(|v| v.downcast_ref::<i32>()) {
                let new_count = pcount + 1;
                if ht_set(&mut counts, Some(word), Some(Box::new(new_count))).is_none() {
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

    let mut it = ht_iterator(&counts);
    let mut total_probes = 0;
    while ht_next(&mut it) {
        total_probes += get_probe_len(&counts, it.key.as_deref());
    }

    println!(
        "len={} cap={} avgprobe={:.3}",
        ht_length(&counts),
        counts.capacity,
        total_probes as f64 / ht_length(&counts) as f64
    );

    ht_destroy(counts);
    Ok(())
}
