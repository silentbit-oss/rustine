use std::any::Any;
use std::boxed::Box;
use std::env;
use std::ffi::CStr;
use std::ffi::c_char;
use std::io::BufRead;
use std::io;
use translate_new::*;

pub fn main() {
    let items = [
        Item { key: Some("foo".to_string()), value: 10 },
        Item { key: Some("bar".to_string()), value: 42 },
        Item { key: Some("bazz".to_string()), value: 36 },
        Item { key: Some("buzz".to_string()), value: 7 },
        Item { key: Some("bob".to_string()), value: 11 },
        Item { key: Some("jane".to_string()), value: 100 },
        Item { key: Some("x".to_string()), value: 200 },
    ];
    
    let target_str = "bob";
    
    let found = linear_search(&items, Some(target_str));
    
    if found.is_none() {
        std::process::exit(1);
    }
    
    let found_item = found.unwrap();
    println!("linear_search: value of 'bob' is {}", found_item.value);
}
