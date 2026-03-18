use crate::*;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::time::Instant;


lazy_static! {
    pub static ref NODES: AtomicI32 = AtomicI32::new(10000);
}


lazy_static! {
    pub static ref START_TIME: std::sync::Mutex<Instant> = std::sync::Mutex::new(Instant::now());
}

