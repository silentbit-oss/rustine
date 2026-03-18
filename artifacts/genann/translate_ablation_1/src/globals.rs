use crate::*;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref LTESTS: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref LFAILS: AtomicI32 = AtomicI32::new(0);
}

pub const SIGMOID_DOM_MIN: f64 = -15.0;

pub const SIGMOID_DOM_MAX: f64 = 15.0;

pub static mut interval: f64 = 0.0;


lazy_static! {
    pub static ref LOOKUP: std::sync::Mutex<[f64; 4096]> = 
        std::sync::Mutex::new([0.0; 4096]);
}

pub const SAVE_NAME: &str = "example/xor.ann";

pub const IRIS_DATA: &str = "example/iris.data";

pub static INPUT: std::sync::Mutex<Option<Box<[f64]>>> = std::sync::Mutex::new(None);


lazy_static! {
    pub static ref CLASS: std::sync::Mutex<Option<Box<[f64]>>> = std::sync::Mutex::new(None);
}

pub static SAMPLES: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);


lazy_static! {
    pub static ref CLASS_NAMES: [&'static str; 3] = [
        "Iris-setosa",
        "Iris-versicolor",
        "Iris-virginica"
    ];
}

