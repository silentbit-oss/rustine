use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicU32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref G_DEBUG: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref G_PRINT_IN_HEX: AtomicBool = AtomicBool::new(true);
}


lazy_static! {
    pub static ref G_PRINT_IN_RGB: AtomicBool = AtomicBool::new(false);
}


lazy_static! {
    pub static ref G_PRINT_ALL_16_BITS: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref G_LOC_SPECIFIED: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref G_X: AtomicI32 = AtomicI32::new(1);
}


lazy_static! {
    pub static ref G_Y: AtomicI32 = AtomicI32::new(1);
}


lazy_static! {
    pub static ref G_WIDTH: AtomicU32 = AtomicU32::new(0);
}


lazy_static! {
    pub static ref G_HEIGHT: AtomicU32 = AtomicU32::new(0);
}

lazy_static! {
    pub static ref G_WINDOW_ID: std::sync::Mutex<Option<Window>> = std::sync::Mutex::new(Option::<Window>::None);
}

lazy_static! {
    pub static ref G_CROSS_CURSOR: Mutex<Option<Cursor>> = Mutex::new(Option::<Cursor>::None);
}

