use translate::*;
use std::fmt;
use std::env;
pub fn main() {
    let items = vec![
        Item { key: Some("foo".to_string()), value: 10 },
        Item { key: Some("bar".to_string()), value: 42 },
        Item { key: Some("bazz".to_string()), value: 36 },
        Item { key: Some("buzz".to_string()), value: 7 },
        Item { key: Some("bob".to_string()), value: 11 },
        Item { key: Some("jane".to_string()), value: 100 },
        Item { key: Some("x".to_string()), value: 200 },
    ];
    let num_items = items.len();

    let mut table = match ht_create() {
        Some(t) => t,
        None => {
            exit_nomem();
            return;
        }
    };

    for i in 0..num_items {
        let item = &items[i];
        let val = Box::new(item.value) as Box<dyn std::any::Any>;
        if ht_set(&mut table, item.key.as_deref(), Some(val)).is_none() {
            exit_nomem();
            return;
        }
    }

    if let Some(entries) = &table.entries {
        for i in 0..table.capacity {
            if let Some(entry) = entries.get(i) {
                if let Some(key) = &entry.key {
                    if let Some(val_ref) = &entry.value {
                        if let Some(val) = val_ref.downcast_ref::<i32>() {
                            println!("index {}: key {}, value {}", i, key, val);
                        }
                    }
                } else {
                    println!("index {}: empty", i);
                }
            }
        }
    }
}
