use crate::*;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref MU_TESTS: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);
}


lazy_static! {
    pub static ref MU_FAILS: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);
}


lazy_static! {
    pub static ref PERMUTATION_ERROR: AtomicI32 = AtomicI32::new(0);
}

