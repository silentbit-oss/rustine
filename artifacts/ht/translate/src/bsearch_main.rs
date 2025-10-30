use translate::*;
use std::env;
use std::cmp::Ordering;

pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let items = [
        Item { key: Some("bar".to_string()), value: 42 },
        Item { key: Some("bazz".to_string()), value: 36 },
        Item { key: Some("bob".to_string()), value: 11 },
        Item { key: Some("buzz".to_string()), value: 7 },
        Item { key: Some("foo".to_string()), value: 10 },
        Item { key: Some("jane".to_string()), value: 100 },
        Item { key: Some("x".to_string()), value: 200 },
    ];
    let num_items = items.len();
    let key = Item { key: Some("bob".to_string()), value: 0 };

    // Using slice::binary_search_by_key which is Rust's equivalent to bsearch
    let found = items.binary_search_by_key(&key.key, |item| item.key.clone());
    let found_idx = match found {
        Ok(idx) => idx,
        Err(_) => {
            eprintln!("bsearch: 'bob' not found");
            return Ok(());
        }
    };
    println!("bsearch: value of 'bob' is {}", items[found_idx].value);

    // Using our custom binary_search function
    let found_item = binary_search(&items, key.key.as_deref());
    match found_item {
        Some(item) => println!("binary_search: value of 'bob' is {}", item.value),
        None => {
            eprintln!("binary_search: 'bob' not found");
            return Ok(());
        }
    }

    Ok(())
}
