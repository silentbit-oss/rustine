use std::any::Any;
use std::boxed::Box;
use std::env;
use std::io::BufRead;
use std::io;
use translate_new::*;
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
                let new_count = *pcount + 1;
                let boxed = Box::new(new_count) as Box<dyn Any>;
                if ht_set(&mut counts, Some(word), Some(boxed)).is_none() {
                    exit_nomem();
                    return Ok(());
                }
            }
        } else {
            let pcount = Box::new(1) as Box<dyn Any>;
            if ht_set(&mut counts, Some(word), Some(pcount)).is_none() {
                exit_nomem();
                return Ok(());
            }
        }
    }

    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        if let (Some(key), Some(val)) = (it.key.as_ref(), it.value.as_ref()) {
            if let Some(count) = val.downcast_ref::<i32>() {
                println!("{} {}", key, count);
            }
        }
    }

    println!("{}", ht_length(&counts));
    ht_destroy(counts);
    Ok(())
}
