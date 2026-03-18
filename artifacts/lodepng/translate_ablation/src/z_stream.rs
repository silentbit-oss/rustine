use crate::*;
use std::os::raw::c_void;


pub struct InternalState; // Opaque type for internal state

pub struct ZStream {
    pub next_in: Option<Box<Bytef>>,
    pub avail_in: uInt,
    pub total_in: uLong,
    pub next_out: Option<Box<Bytef>>,
    pub avail_out: uInt,
    pub total_out: uLong,
    pub msg: Option<Box<i8>>,
    pub state: Option<Box<InternalState>>,
    pub zalloc: AllocFunc,
    pub zfree: FreeFunc,
    pub opaque: voidpf,
    pub data_type: i32,
    pub adler: uLong,
    pub reserved: uLong,
}

pub type Bytef = u8;
pub type uInt = u32;
pub type uLong = u64;
pub type AllocFunc = fn(opaque: voidpf, items: uInt, size: uInt) -> voidpf;
pub type voidpf = *mut c_void;
pub type FreeFunc = Option<Box<dyn Fn(voidpf, voidpf)>>;

