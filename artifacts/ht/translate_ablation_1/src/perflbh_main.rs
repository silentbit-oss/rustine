use std::any::Any;
use std::env;
use std::io::Read;
use std::io::Seek;
use std::time::Duration;
use std::time::Instant;
use translate_new::*;
pub fn main() {
    let runs = 5000000;
    let num_items_total = {
        let items_guard = ITEMS.lock().unwrap();
        (items_guard.len() / std::mem::size_of::<Item>()) as i32
    };
    
    for num_items in 1..num_items_total {
        println!("NUM ITEMS: {}", num_items);
        
        let start = Instant::now();
        for item_index in 0..num_items {
            let key = {
                let items_guard = ITEMS.lock().unwrap();
                items_guard[item_index as usize].key.clone()
            };
            for _run in 0..runs {
                let items_guard = ITEMS.lock().unwrap();
                let result = linear_search(&items_guard[0..num_items as usize], key.as_deref());
                let mut found_guard = FOUND.lock().unwrap();
                *found_guard = result.map(|item| Box::new(item.value) as Box<dyn Any + Send>);
            }
        }
        
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  linear, {} runs: {:.09}fs", runs, elapsed);
        
        let start = Instant::now();
        for item_index in 0..num_items {
            let key = {
                let items_guard = ITEMS.lock().unwrap();
                items_guard[item_index as usize].key.clone()
            };
            for _run in 0..runs {
                let items_guard = ITEMS.lock().unwrap();
                let result = binary_search(&items_guard[0..num_items as usize], num_items as usize, key.as_deref());
                let mut found_guard = FOUND.lock().unwrap();
                *found_guard = result.map(|item| Box::new(item.value) as Box<dyn Any + Send>);
            }
        }
        
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  binary, {} runs: {:.09}fs", runs, elapsed);
        
        let mut table = ht_create();
        if table.is_none() {
            exit_nomem();
        }
        
        for item_index in 0..num_items {
            let items_guard = ITEMS.lock().unwrap();
            let pn = Box::new(items_guard[item_index as usize].value);
            let p = ht_set(table.as_mut().unwrap(), items_guard[item_index as usize].key.as_deref(), Some(pn));
            if p.is_none() {
                exit_nomem();
            }
        }
        
        let start = Instant::now();
        for item_index in 0..num_items {
            let key = {
                let items_guard = ITEMS.lock().unwrap();
                items_guard[item_index as usize].key.clone()
            };
            for _run in 0..runs {
                let value_ptr = ht_get(table.as_ref().unwrap(), key.as_deref());
                // Store result in global if needed
            }
        }
        
        let end = Instant::now();
        let elapsed = (end - start).as_secs_f64() / num_items as f64;
        println!("  hash  , {} runs: {:.09}fs", runs, elapsed);
    }
}
