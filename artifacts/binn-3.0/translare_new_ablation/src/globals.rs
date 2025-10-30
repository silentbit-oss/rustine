use crate::*;
use lazy_static::lazy_static;
use std::mem::zeroed;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref MALLOC_FN: Mutex<Option<fn(usize) -> Option<Box<dyn std::any::Any>>>> = 
        Mutex::new(None);
}


// Newtype wrapper for our closure to allow implementing Send/Sync
pub struct ReallocFnWrapper(
    pub Box<dyn FnMut(Option<Box<[u8]>>, usize) -> Option<Box<[u8]>> + Send>
);

// Safe to send between threads since we require Send in the inner type
unsafe impl Send for ReallocFnWrapper {}
// Safe to share references between threads since we require Send in the inner type
unsafe impl Sync for ReallocFnWrapper {}

lazy_static::lazy_static! {
    pub static ref REALLOC_FN: Mutex<Option<ReallocFnWrapper>> = Mutex::new(None);
}

// Newtype wrapper for our closure to allow implementing Send/Sync
pub struct FreeFnWrapper(pub Box<dyn FnMut(Option<Box<dyn std::any::Any + Send>>)>);

// SAFETY: We ensure thread-safety by requiring Send in the wrapper
unsafe impl Send for FreeFnWrapper {}
unsafe impl Sync for FreeFnWrapper {}

lazy_static::lazy_static! {
    pub static ref FREE_FN: Mutex<Option<FreeFnWrapper>> = Mutex::new(None);
}


lazy_static! {
    pub static ref MY_DATE: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref MY_CURRENCY: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref TMP: std::sync::Mutex<[u8; 128]> = std::sync::Mutex::new([0; 128]);
}


lazy_static! {
    pub static ref VINT32: AtomicI32 = AtomicI32::new(0);
}

pub type vuint32 = u32;

pub type vint16 = i16;

pub type vuint16 = u16;

pub static mut VINT8: i8 = 0;

pub type vuint8 = u8;

pub static mut vfloat32: f32 = 0.0;

pub static mut vfloat64: f64 = 0.0;

pub static mut vint64: int64 = 0;

pub type vuint64 = uint64;

pub static mut vbool: BOOL = 0;


// Implement Send and Sync for the necessary types
unsafe impl Send for BinnStruct {}
unsafe impl Sync for BinnStruct {}
unsafe impl Send for BinnValue {}
unsafe impl Sync for BinnValue {}

lazy_static! {
    pub static ref LOCAL_VALUE: Mutex<Option<Box<BinnStruct>>> = {
        let empty_binn: BinnStruct = unsafe { zeroed() };
        Mutex::new(Some(Box::new(empty_binn)))
    };
}

