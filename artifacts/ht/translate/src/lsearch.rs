use translate::*;
use std::env;
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
    
    let found = linear_search(&items, Some("bob"));
    if found.is_none() {
        return Ok(());
    }
    
    println!("linear_search: value of 'bob' is {}", found.unwrap().value);
    Ok(())
}
