use crate::*;
use std::process;
use std::cmp::Ordering;


pub fn exit_nomem() {
    eprintln!("out of memory");
    process::exit(1);
}

pub fn get_probe_len(table: &Ht, key: Option<&str>) -> usize {
    let key = match key {
        Some(k) => k,
        None => return 0, // Return 0 if key is None (equivalent to NULL in C)
    };

    let hash = hash_key(Some(key));
    let mut index = (hash & ((table.capacity - 1) as u64)) as usize;
    let mut probe_len = 0;

    if let Some(entries) = &table.entries {
        while let Some(entry) = entries.get(index) {
            if entry.key.is_none() {
                break;
            }
            
            probe_len += 1;
            
            if let Some(entry_key) = &entry.key {
                match key.cmp(entry_key) {
                    Ordering::Equal => return probe_len,
                    _ => (),
                }
            }

            index += 1;
            if index >= table.capacity {
                index = 0;
            }
        }
    }

    probe_len
}
