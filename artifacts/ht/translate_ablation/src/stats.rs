use crate::*;
use std::cmp::Ordering;
use std::process;


pub fn exit_nomem() {
    eprintln!("out of memory");
    process::exit(1);
}

pub fn get_probe_len(table: &Ht, key: Option<&str>) -> usize {
    // Check if key is None (equivalent to NULL in C)
    let key = match key {
        Some(k) => k,
        None => return 0,
    };

    let hash = hash_key(Some(key));
    let mut index = (hash & (table.capacity as u64 - 1)) as usize;
    let mut probe_len = 0;

    // Check if entries exist and get a reference to them
    if let Some(entries) = &table.entries {
        while let Some(entry) = entries.get(index) {
            // Check if entry.key exists and compare with input key
            if let Some(entry_key) = &entry.key {
                probe_len += 1;
                match key.cmp(entry_key) {
                    Ordering::Equal => return probe_len,
                    _ => (),
                }
            } else {
                break;
            }

            index += 1;
            if index >= table.capacity {
                index = 0;
            }
        }
    }

    probe_len
}
