use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::Ordering;
use std::sync::atomic::AtomicPtr;


lazy_static::lazy_static! {
    pub static ref FOUND: AtomicPtr<()> = AtomicPtr::new(std::ptr::null_mut());
}


lazy_static! {
    pub static ref value: Mutex<Option<Box<i32>>> = Mutex::new(None);
}


lazy_static! {
    pub static ref ITEMS: std::sync::Mutex<[Item; 26]> = std::sync::Mutex::new([
        Item { key: Some("aoo".to_string()), value: 0 },
        Item { key: Some("bar".to_string()), value: 1 },
        Item { key: Some("cazz".to_string()), value: 2 },
        Item { key: Some("duzz".to_string()), value: 3 },
        Item { key: Some("eaddle".to_string()), value: 4 },
        Item { key: Some("fche".to_string()), value: 5 },
        Item { key: Some("garf".to_string()), value: 6 },
        Item { key: Some("hache".to_string()), value: 7 },
        Item { key: Some("iya".to_string()), value: 8 },
        Item { key: Some("jay".to_string()), value: 9 },
        Item { key: Some("kay".to_string()), value: 10 },
        Item { key: Some("lell".to_string()), value: 11 },
        Item { key: Some("memm".to_string()), value: 12 },
        Item { key: Some("noo".to_string()), value: 0 },
        Item { key: Some("oar".to_string()), value: 1 },
        Item { key: Some("pazz".to_string()), value: 2 },
        Item { key: Some("quzz".to_string()), value: 3 },
        Item { key: Some("raddle".to_string()), value: 4 },
        Item { key: Some("sche".to_string()), value: 5 },
        Item { key: Some("tarf".to_string()), value: 6 },
        Item { key: Some("uache".to_string()), value: 7 },
        Item { key: Some("vya".to_string()), value: 8 },
        Item { key: Some("way".to_string()), value: 9 },
        Item { key: Some("xay".to_string()), value: 10 },
        Item { key: Some("yell".to_string()), value: 11 },
        Item { key: Some("zemm".to_string()), value: 12 }
    ]);
}

