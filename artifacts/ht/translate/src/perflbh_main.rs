use translate::*;
use std::env;
use std::time::Duration;
use std::time::Instant;
use std::any::Any;

pub fn main() {
    let runs = 5000000;
    let items = ITEMS.lock().unwrap();
    let num_items_max = items.len();

    for num_items in 1..num_items_max {
        println!("NUM ITEMS: {}", num_items);
        
        // Linear search benchmark
        let start = Instant::now();
        for item_index in 0..num_items {
            let key = items[item_index].key.as_deref();
            for _ in 0..runs {
                let _found = linear_search(&items[..num_items], key);
            }
        }
        let elapsed = start.elapsed().as_secs_f64() / num_items as f64;
        println!("  linear, {} runs: {:.09}fs", runs, elapsed);

        // Binary search benchmark
        let start = Instant::now();
        for item_index in 0..num_items {
            let key = items[item_index].key.as_deref();
            for _ in 0..runs {
                let _found = binary_search(&items[..num_items], key);
            }
        }
        let elapsed = start.elapsed().as_secs_f64() / num_items as f64;
        println!("  binary, {} runs: {:.09}fs", runs, elapsed);

        // Hash table benchmark
        let mut table = match ht_create() {
            Some(t) => t,
            None => {
                exit_nomem();
                return;
            }
        };

        for item_index in 0..num_items {
            let pn = Box::new(items[item_index].value);
            let key = items[item_index].key.as_deref();
            if ht_set(&mut table, key, Some(pn as Box<dyn Any>)).is_none() {
                exit_nomem();
                return;
            }
        }

        let start = Instant::now();
        for item_index in 0..num_items {
            let key = items[item_index].key.as_deref();
            for _ in 0..runs {
                let _value = ht_get(&table, key);
            }
        }
        let elapsed = start.elapsed().as_secs_f64() / num_items as f64;
        println!("  hash  , {} runs: {:.09}fs", runs, elapsed);
    }
}
