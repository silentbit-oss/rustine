use translate_new::*;
use std::env;
use std::fmt;

pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let items = [
        Item { key: Some("foo".to_string()), value: 10 },
        Item { key: Some("bar".to_string()), value: 42 },
        Item { key: Some("bazz".to_string()), value: 36 },
        Item { key: Some("buzz".to_string()), value: 7 },
        Item { key: Some("bob".to_string()), value: 11 },
        Item { key: Some("jane".to_string()), value: 100 },
        Item { key: Some("x".to_string()), value: 200 },
    ];
    let num_items = items.len();
    let found = linear_search(&items, Some("bob"));
    
    match found {
        Some(item) => println!("linear_search: value of 'bob' is {}", item.value),
        None => return Err(Box::new(fmt::Error)),
    }
    
    Ok(())
}
