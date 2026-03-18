use std::any::Any;
use std::boxed::Box;
use std::env;
use std::ffi::CStr;
use std::io::BufRead;
use std::io;
use translate_new::*;
pub fn main() {
    // Build some sample items (keys are Option<String> per translated types)
    let items = [
        Item { key: Some("foo".to_string()),  value: 10  },
        Item { key: Some("bar".to_string()),  value: 42  },
        Item { key: Some("bazz".to_string()), value: 36  },
        Item { key: Some("buzz".to_string()), value: 7   },
        Item { key: Some("bob".to_string()),  value: 11  },
        Item { key: Some("jane".to_string()), value: 100 },
        Item { key: Some("x".to_string()),    value: 200 },
    ];
    let num_items = items.len();

    // Create table (translated API returns Option<Ht>)
    let mut table = ht_create();
    if table.is_none() {
        exit_nomem();
    }

    // Insert: ht_set expects (&mut Ht, Option<&str>, Option<Box<dyn Any>>)
    for i in 0..num_items {
        let key_opt: Option<&str> = items[i].key.as_deref();
        let val_box = Some(Box::new(items[i].value) as Box<dyn std::any::Any>);
        if ht_set(table.as_mut().unwrap(), key_opt, val_box).is_none() {
            exit_nomem();
        }
    }

    // Dump table contents
    let table_ref = table.as_ref().unwrap();
    if let Some(ref entries) = table_ref.entries {
        for (i, entry) in entries.iter().enumerate() {
            if let Some(ref key_str) = entry.key {
                // value is Option<Box<dyn Any>>; downcast to i32 for display
                let shown_val = entry
                    .value
                    .as_ref()
                    .and_then(|b| b.as_ref().downcast_ref::<i32>())
                    .copied();
                match shown_val {
                    Some(v) => println!("index {}: key {}, value {}", i, key_str, v),
                    None => println!("index {}: key {}, value <non-i32>", i, key_str),
                }
            } else {
                println!("index {}: empty", i);
            }
        }
    } else {
        println!("hash table has no buckets (entries = None)");
    }
}
