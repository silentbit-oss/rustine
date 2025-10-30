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
            let word_value = ht_get(&counts, Some(word));
            if let Some(v) = word_value {
                if let Some(pcount) = v.downcast_ref::<i32>() {
                    let new_count = pcount + 1;
                    if ht_set(&mut counts, Some(word), Some(Box::new(new_count))).is_none() {
                        exit_nomem();
                        return Ok(());
                    }
                    continue;
                }
            }

            let pcount = Box::new(1);
            if ht_set(&mut counts, Some(word), Some(pcount)).is_none() {
                exit_nomem();
                return Ok(());
            }
        }
    }

    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        if let (Some(ref key), Some(ref val)) = (&it.key, &it.value) {
            if let Some(pcount) = val.downcast_ref::<i32>() {
                println!("{} {}", key, pcount);
            }
        }
    }

    println!("{}", ht_length(&counts));
    ht_destroy(Box::new(counts));
    Ok(())
}
