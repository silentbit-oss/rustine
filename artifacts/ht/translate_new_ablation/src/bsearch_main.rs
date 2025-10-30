use std::any::Any;
use std::boxed::Box;
use std::env;
use std::ffi::c_int;
use std::io::BufRead;
use std::io;
use translate_new::*;

pub fn main() -> () {
    unsafe {
        let items = [
            Item { key: Some("bar\0".to_string()), value: 42 },
            Item { key: Some("bazz\0".to_string()), value: 36 },
            Item { key: Some("bob\0".to_string()), value: 11 },
            Item { key: Some("buzz\0".to_string()), value: 7 },
            Item { key: Some("foo\0".to_string()), value: 10 },
            Item { key: Some("jane\0".to_string()), value: 100 },
            Item { key: Some("x\0".to_string()), value: 200 },
        ];
        let num_items = items.len();
        let key = Item { key: Some("bob\0".to_string()), value: 0 };
        
        // Use Rust's built-in binary search instead of C's bsearch
        let found_item = items.binary_search_by_key(&key.key, |item| item.key.clone());
        
        if found_item.is_err() {
            std::process::exit(1);
        }
        
        let index = found_item.unwrap();
        println!("bsearch: value of 'bob' is {}", items[index].value);
        
        // Use linear search instead of lfind
        let mut found_index = None;
        for (i, item) in items.iter().enumerate() {
            if item.key == key.key {
                found_index = Some(i);
                break;
            }
        }
        
        if found_index.is_none() {
            std::process::exit(1);
        }
        
        let found_item = &items[found_index.unwrap()];
        println!("lfind: value of 'bob' is {}", found_item.value);
    }
}
