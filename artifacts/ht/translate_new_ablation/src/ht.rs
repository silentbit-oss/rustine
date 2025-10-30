use crate::*;
use std::any::Any;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::vec::Vec;

pub fn hash_key(key: Option<&str>) -> u64 {
    // Check for NULL pointer equivalent
    if key.is_none() {
        return 0; // Return 0 as a reasonable default for NULL input
    }
    
    let key = key.unwrap();
    let mut hash: u64 = 14695981039346656037;
    
    // Iterate through the string bytes
    for &byte in key.as_bytes() {
        hash ^= byte as u64;
        hash = hash.wrapping_mul(1099511628211);
    }
    
    hash
}


pub struct Ht {
    pub entries: Option<Vec<HtEntry>>,
    pub capacity: usize,
    pub length: usize,
}

pub fn ht_create() -> Option<Ht> {
    let capacity = 16;
    let mut entries = Vec::with_capacity(capacity);
    
    for _ in 0..capacity {
        entries.push(HtEntry {
            key: Option::None,
            value: Option::None,
        });
    }
    
    Some(Ht {
        entries: Some(entries),
        capacity,
        length: 0,
    })
}
pub fn ht_destroy(table: Ht) {
    // No explicit free needed in Rust - memory is automatically managed
    // The `entries` field is an Option<Vec<HtEntry>>, which will be dropped automatically
    // when the struct goes out of scope
}
pub fn ht_length(table: &Ht) -> usize {
    table.length
}
pub fn ht_get<'a>(table: &'a Ht, key: Option<&str>) -> Option<&'a HtEntry> {
    // Check if key is None (equivalent to NULL in C)
    let key = key?;

    // Calculate hash and index
    let hash = hash_key(Some(key));
    let mut index = (hash & (table.capacity as u64 - 1)) as usize;

    // Get entries if they exist
    let entries = table.entries.as_ref()?;

    // Linear probing
    while index < entries.len() {
        let entry = &entries[index];
        
        // Check if entry is occupied
        if let Some(entry_key) = &entry.key {
            // Compare strings safely
            let c_str_key = unsafe { CStr::from_ptr(entry_key.as_ptr()) };
            if c_str_key.to_str().ok()? == key {
                return Some(entry);
            }
        } else {
            // Empty slot found
            return None;
        }

        // Move to next slot
        index += 1;
        if index >= table.capacity {
            index = 0;
        }
    }

    None
}
pub fn ht_iterator(table: &Ht) -> Hti {
    let ptr = table as *const Ht;
    Hti {
        key: Option::None,
        value: Some(Box::new(ptr)),
        _table: Option::None,
        _index: 0,
    }
}
pub fn ht_set_entry(
    entries: &mut [crate::HtEntry],
    capacity: usize,
    key: Option<&str>,
    val: Option<Box<dyn std::any::Any>>,
    plength: &mut Option<usize>,
) -> Option<String> {
    // Reject missing key, as in C if (key == 0) return 0;
    let key = match key {
        Some(k) => k,
        Option::None => return Option::None,
    };

    // Hash and initial probe index (capacity is assumed to be a power of two)
    let hash = hash_key(Some(key));
    let mut index = (hash & (capacity as u64 - 1)) as usize;

    // Linear probing search/update
    loop {
        if let Some(stored_key) = &entries[index].key {
            if stored_key == key {
                // Update value in place and return the canonical stored key (C returns the pointer it stores)
                entries[index].value = val;
                return Some(stored_key.clone());
            }
            index += 1;
            if index >= capacity {
                index = 0;
            }
        } else {
            break;
        }
    }

    // If caller passed plength (non-null in C), increment it.
    if let Some(ref mut len) = *plength {
        *len += 1;
    }

    // In C, when plength != 0 they strdup(key). Here we always own a String for storage.
    let owned_key = key.to_string();

    entries[index].key = Some(owned_key.clone());
    entries[index].value = val;

    Some(owned_key)
}
pub fn ht_expand(table: &mut Ht) -> bool {
    let new_capacity = match table.capacity.checked_mul(2) {
        Some(cap) => cap,
        None => return false,
    };

    let mut new_entries = Vec::new();
    if new_entries.try_reserve_exact(new_capacity).is_err() {
        return false;
    }
    for _ in 0..new_capacity {
        new_entries.push(HtEntry {
            key: None,
            value: None,
        });
    }

    let old_entries = table.entries.take();
    if let Some(old_entries) = old_entries {
        for mut entry in old_entries.into_iter() {
            if entry.key.is_some() {
                let key = entry.key.take();
                let val = entry.value.take();
                ht_set_entry(
                    &mut new_entries,
                    new_capacity,
                    key.as_deref(),
                    val,
                    &mut None,
                );
            }
        }
    }

    table.entries = Some(new_entries);
    table.capacity = new_capacity;
    true
}
pub fn ht_set(
    table: &mut Ht,
    key: Option<&str>,
    val: Option<Box<dyn Any>>,
) -> Option<String> {
    // Equivalent to C's assert(value != 0)
    let val_box = match val {
        Some(v) => v,
        None => return None,
    };

    if table.length >= (table.capacity / 2) {
        if !ht_expand(table) {
            return None;
        }
    }

    ht_set_entry(
        table.entries.as_mut()?,
        table.capacity,
        key,
        Some(val_box),
        &mut Some(table.length),
    )
}
pub fn ht_next(it: &mut Hti) -> bool {
    // Get a mutable reference to the table, return false if it's None
    let table = match &mut it._table {
        Some(t) => t,
        None => return false,
    };

    // Get a mutable reference to the entries vector, return false if it's None
    let entries = match &mut table.entries {
        Some(e) => e,
        None => return false,
    };

    // Iterate through the entries starting from current index
    while it._index < table.capacity {
        let i = it._index;
        it._index += 1;

        // Check if the current entry has a key
        if let Some(entry) = entries.get_mut(i) {
            if entry.key.is_some() {
                // Update the iterator's key and value by taking ownership
                it.key = entry.key.clone();  // String can be cloned
                it.value = entry.value.take();  // Take the value without cloning
                return true;
            }
        }
    }

    false
}
