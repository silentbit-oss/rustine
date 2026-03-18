use translate_new::*;
use std::env;
use std::time::Duration;
use std::time::Instant;
use std::any::Any;
pub fn main() {
    let runs = 5_000_000;
    
    for num_items in 1..ITEMS.lock().unwrap().len() {
        println!("NUM ITEMS: {}", num_items);
        
        // Linear search benchmark
        let start = Instant::now();
        {
            let items = ITEMS.lock().unwrap();
            for item_index in 0..num_items {
                let key = items[item_index].key.as_deref();
                for _run in 0..runs {
                    let result = linear_search(&items[..num_items], key).map(|item| Box::new(item.value) as Box<dyn Any + Send>);
                    *FOUND.lock().unwrap() = result;
                }
            }
        }
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  linear, {} runs: {:.09}fs", runs, elapsed);

        // Binary search benchmark
        let start = Instant::now();
        {
            let items = ITEMS.lock().unwrap();
            for item_index in 0..num_items {
                let key = items[item_index].key.as_deref();
                for _run in 0..runs {
                    let result = binary_search(&items[..num_items], num_items, key).map(|item| Box::new(item.value) as Box<dyn Any + Send>);
                    *FOUND.lock().unwrap() = result;
                }
            }
        }
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  binary, {} runs: {:.09}fs", runs, elapsed);

        // Hash table benchmark
        let mut table = match ht_create() {
            Some(t) => t,
            None => {
                exit_nomem();
                return;
            }
        };

        {
            let items = ITEMS.lock().unwrap();
            for item_index in 0..num_items {
                let pn = Box::new(items[item_index].value);
                let key = items[item_index].key.as_deref();
                let p = ht_set(&mut table, key, Some(pn as Box<dyn Any>));
                if p.is_none() {
                    exit_nomem();
                    return;
                }
            }
        }

        let start = Instant::now();
        {
            let items = ITEMS.lock().unwrap();
            for item_index in 0..num_items {
                let key = items[item_index].key.as_deref();
                for _run in 0..runs {
                    unsafe {
                        value = ht_get(&table, key).and_then(|entry| {
                            entry.value.as_ref().and_then(|v| v.downcast_ref::<i32>()).map(|v| Box::new(*v))
                        });
                    }
                }
            }
        }
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  hash  , {} runs: {:.09}fs", runs, elapsed);
    }
}
