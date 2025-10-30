use crate::*;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::time::Duration;


lazy_static! {
    pub static ref NODES: AtomicI32 = AtomicI32::new(10000);
}


lazy_static! {
    pub static ref START_TIME: std::sync::Mutex<Option<Duration>> = std::sync::Mutex::new(None);
}

