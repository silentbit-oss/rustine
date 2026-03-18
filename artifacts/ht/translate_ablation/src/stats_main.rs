use std::any::Any;
use std::boxed::Box;
use std::collections::HashMap;
use std::env;
use std::io::BufRead;
use std::io;
use translate_new::*;
pub fn main() -> io::Result<()> {
    let mut counts = match ht_create() {
        Some(ht) => ht,
        None => {
            exit_nomem();
            return Ok(());
        }
    };
    
    let mut word = String::with_capacity(101);
    
    while io::stdin().read_line(&mut word)? > 0 {
        // Remove trailing newline and whitespace
        let word_clean = word.trim_end();
        
        let value_ptr = ht_get(&counts, Some(word_clean));
        if let Some(entry) = value_ptr {
            if let Some(ref val) = entry.value {
                let cell = val.downcast_ref::<std::cell::Cell<i32>>().unwrap();
                cell.set(cell.get() + 1);
            }
            word.clear();
            continue;
        }
        
        let pcount = Box::new(std::cell::Cell::new(1));
        if ht_set(&mut counts, Some(word_clean), Some(pcount as Box<dyn Any>)).is_none() {
            exit_nomem();
            return Ok(());
        }
        word.clear();
    }

    let mut total_probes: usize = 0;
    let mut it = ht_iterator(&counts);
    while ht_next(&mut it) {
        total_probes += get_probe_len(&counts, it.key.as_deref());
        // Free the value as in original C code
        if let Some(ref val) = it.value {
            let _ = val.downcast_ref::<std::cell::Cell<i32>>();
        }
    }
    
    let len = ht_length(&counts);
    let capacity = counts.capacity;
    let avgprobe = if len > 0 { total_probes as f64 / len as f64 } else { 0.0 };
    
    println!("len={} cap={} avgprobe={:.3}", len, capacity, avgprobe);
    // Ht will be automatically dropped at the end of the function
    
    Ok(())
}
