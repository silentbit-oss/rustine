use crate::*;

pub fn linear_search<'a>(items: &'a [Item], key: Option<&'a str>) -> Option<&'a Item> {
    let key = key?; // Return None if key is None
    
    for item in items {
        if let Some(item_key) = &item.key {
            if item_key == key {
                return Some(item);
            }
        }
    }
    
    None
}
pub fn binary_search<'a>(items: &'a [Item], key: Option<&'a str>) -> Option<&'a Item> {
    // Handle NULL key case (None in Rust)
    let key = match key {
        Some(k) => k,
        None => return None,
    };

    let mut low = 0;
    let mut high = items.len();
    
    while low < high {
        let mid = (low + high) / 2;
        // Safe unwrap since we're working with valid items
        let item_key = items[mid].key.as_deref().unwrap_or("");
        let c = item_key.cmp(key);
        
        match c {
            std::cmp::Ordering::Equal => return Some(&items[mid]),
            std::cmp::Ordering::Less => low = mid + 1,
            std::cmp::Ordering::Greater => high = mid,
        }
    }

    // Check if we found the item at the low index
    if low < items.len() {
        let item_key = items[low].key.as_deref().unwrap_or("");
        if item_key == key {
            return Some(&items[low]);
        }
    }

    None
}
