use translate_new::*;
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

    // Using Rust's built-in binary search instead of bsearch
    let found = items.binary_search_by(|item| cmp(item, &key));
    let found_idx = match found {
        Ok(idx) => idx,
        Err(_) => return Err("bsearch: key not found".into()),
    };
    println!("bsearch: value of 'bob' is {}", items[found_idx].value);

    let found = binary_search(&items, num_items, key.key.as_deref());
    let found_idx = match found {
        Some(item) => items.iter().position(|x| x.key == item.key).unwrap(),
        None => return Err("binary_search: key not found".into()),
    };
    println!("binary_search: value of 'bob' is {}", items[found_idx].value);

    Ok(())
}
