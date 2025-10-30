use crate::*;
use std::any::Any;


pub struct Ht {
    pub entries: Option<Vec<Ht_Entry>>,
    pub capacity: usize,
    pub length: usize,
}

pub fn hash_key(key: Option<&str>) -> u64 {
    let key = match key {
        Some(k) => k,
        None => return 0, // Default behavior when key is NULL (None)
    };

    let mut hash: u64 = 14695981039346656037;
    for (p_idx, &byte) in key.as_bytes().iter().enumerate() {
        hash ^= byte as u64;
        hash = hash.wrapping_mul(1099511628211);
    }
    
    hash
}
pub fn ht_create() -> Option<Ht> {
    let capacity = 16;
    let mut entries = Vec::with_capacity(capacity);
    for _ in 0..capacity {
        entries.push(Ht_Entry { key: Option::None, value: Option::None });
    }
    
    Some(Ht {
        entries: Some(entries),
        capacity,
        length: 0,
    })
}
pub fn ht_destroy(table: Box<Ht>) {
    if let Some(entries) = table.entries {
        for entry in entries {
            // No explicit free needed - Rust's ownership system will automatically
            // deallocate the String (key) when it goes out of scope
        }
    }
    // No explicit free needed for entries or table - Box will automatically
    // deallocate when it goes out of scope
}
pub fn ht_length(table: &Ht) -> usize {
    table.length
}
pub fn ht_get<'a>(table: &'a Ht, key: Option<&'a str>) -> Option<&'a Box<dyn Any>> {
    let key = match key {
        Some(k) => k,
        None => return Option::None,
    };

    let hash = hash_key(Some(key));
    let mut index = (hash & ((table.capacity - 1) as u64)) as usize;
    
    if let Some(entries) = &table.entries {
        loop {
            let entry = &entries[index];
            if let Some(entry_key) = &entry.key {
                if key == entry_key.as_str() {
                    return entry.value.as_ref();
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
    
    Option::None
}
pub fn ht_iterator(table: &Ht) -> Hti {
    Hti {
        key: Option::None,
        value: Option::None,
        _table: None,  // Changed from cloning to None since we can't clone Ht
        _index: 0,
    }
}
pub fn ht_set_entry(
    entries: &mut [Ht_Entry],
    capacity: usize,
    key: Option<&str>,
    val: Option<Box<dyn std::any::Any>>,
    plength: &mut Option<usize>,
) -> Option<String> {
    let key = match key {
        Some(k) => k,
        None => return Option::None,
    };

    let hash = hash_key(Some(key));
    let mut index = (hash & ((capacity as u64) - 1)) as usize;

    loop {
        if let Some(entry_key) = &entries[index].key {
            if entry_key == key {
                entries[index].value = val;
                return Some(entry_key.clone());
            }
        } else {
            break;
        }

        index += 1;
        if index >= capacity {
            index = 0;
        }
    }

    if let Some(len) = plength {
        *len += 1;
    }

    entries[index].key = Some(key.to_string());
    entries[index].value = val;

    Some(key.to_string())
}
pub fn ht_expand(table: &mut Ht) -> bool {
    let new_capacity = match table.capacity.checked_mul(2) {
        Some(cap) => cap,
        None => return false,
    };

    let mut new_entries = Vec::with_capacity(new_capacity);
    for _ in 0..new_capacity {
        new_entries.push(Ht_Entry { key: Option::None, value: Option::None });
    }

    if let Some(entries) = &mut table.entries {
        for entry in entries.iter_mut() {
            if let Some(key) = &entry.key {
                let entry_val = std::mem::replace(&mut entry.value, Option::None);
                ht_set_entry(
                    &mut new_entries,
                    new_capacity,
                    Some(key.as_str()),
                    entry_val,
                    &mut Option::None,
                );
            }
        }
    }

    table.entries = Some(new_entries);
    table.capacity = new_capacity;
    true
}
pub fn ht_set(table: &mut Ht, key: Option<&str>, val: Option<Box<dyn std::any::Any>>) -> Option<String> {
    // Check if val is None (equivalent to NULL check in C)
    if val.is_none() {
        return Option::None;
    }

    // Check if table needs expansion
    if table.length >= (table.capacity / 2) {
        if !ht_expand(table) {
            return Option::None;
        }
    }

    // Get capacity before mutable borrow of entries
    let capacity = table.capacity;
    
    // Call ht_set_entry with the table's entries and length
    if let Some(entries) = &mut table.entries {
        ht_set_entry(entries, capacity, key, val, &mut Some(table.length))
    } else {
        Option::None
    }
}
pub fn ht_next(it: &mut Hti) -> bool {
    // Get a mutable reference to the table, return false if it's None
    let table = match it._table.as_mut() {
        Some(t) => t,
        None => return false,
    };

    // Get a mutable reference to the entries, return false if it's None
    let entries = match &mut table.entries {
        Some(e) => e,
        None => return false,
    };

    while it._index < table.capacity {
        let i = it._index;
        it._index += 1;

        // Check if the entry exists and has a key, then take the value
        if let Some(entry) = entries.get_mut(i) {
            if entry.key.is_some() {
                it.key = entry.key.clone();
                it.value = entry.value.take();
                return true;
            }
        }
    }

    false
}
