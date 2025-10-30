use crate::*;
use lazy_static::lazy_static;
use std::alloc::Layout;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref MALLOC_FN: std::sync::Mutex<Option<fn(Layout) -> *mut u8>> = 
        std::sync::Mutex::new(None);
}


lazy_static! {
    pub static ref REALLOC_FN: std::sync::Mutex<Option<fn(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>>>> = 
        std::sync::Mutex::new(None);
}

lazy_static! {
    pub static ref FREE_FN: Mutex<Option<Box<dyn FnMut(Option<Box<()>>) + Send>>> = Mutex::new(None);
}


lazy_static! {
    pub static ref MY_DATE: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref MY_CURRENCY: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref TMP: std::sync::Mutex<[u8; 128]> = 
        std::sync::Mutex::new([0u8; 128]);
}


pub static VINT32: AtomicI32 = AtomicI32::new(0);

pub static VUINT32: std::sync::atomic::AtomicU32 = std::sync::atomic::AtomicU32::new(0);


lazy_static! {
    pub static ref VINT16: std::sync::Mutex<i16> = std::sync::Mutex::new(0);
}

pub type vuint16 = u16;

pub static mut VINT8: i8 = 0;

pub type vuint8 = u8;


lazy_static! {
    pub static ref VFLOAT32: std::sync::Mutex<f32> = std::sync::Mutex::new(0.0);
}

pub static VFLOAT64: std::sync::Mutex<f64> = std::sync::Mutex::new(0.0);

pub static mut vint64: int64 = 0;


lazy_static! {
    pub static ref VUINT64: std::sync::Mutex<uint64> = std::sync::Mutex::new(0);
}

pub static mut VBOOL: BOOL = 0;

pub static mut local_value: Binn = None;

