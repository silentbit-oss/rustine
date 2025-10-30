use crate::*;
use std::cmp::Ordering;

pub fn linear_search<'a>(items: &'a [Item], key: Option<&'a str>) -> Option<&'a Item> {
    // Check if key is None (equivalent to NULL in C)
    let key = key?;

    for item in items {
        // Compare keys if both exist
        if let Some(item_key) = &item.key {
            if item_key == key {
                return Some(item);
            }
        }
    }

    None
}
pub fn binary_search<'a>(items: &'a [Item], size: usize, key: Option<&str>) -> Option<&'a Item> {
    // Handle NULL key case (equivalent to None in Rust)
    let key = match key {
        Some(k) => k,
        None => return None,
    };

    let mut low = 0;
    let mut high = size;
    
    while low < high {
        let mid = (low + high) / 2;
        let current_key = match &items[mid].key {
            Some(k) => k,
            None => return None, // Handle case where item's key is None
        };

        match current_key.as_str().cmp(key) {
            std::cmp::Ordering::Equal => return Some(&items[mid]),
            std::cmp::Ordering::Less => low = mid + 1,
            std::cmp::Ordering::Greater => high = mid,
        }
    }

    // Final check for the case where low == high
    if low < size {
        if let Some(current_key) = &items[low].key {
            if current_key.as_str() == key {
                return Some(&items[low]);
            }
        }
    }

    None
}
