use crate::*;
use std::mem::ManuallyDrop;
use std::os::raw::c_void;
use std::sync::atomic::AtomicUsize;


pub struct MiPageS {
    pub slice_count: u32,
    pub slice_offset: u32,
    pub is_committed: u8,
    pub is_zero_init: u8,
    pub is_huge: u8,
    pub capacity: u16,
    pub reserved: u16,
    pub flags: MiPageFlagsT,
    pub free_is_zero: u8,
    pub retire_expire: u8,
    pub free: Option<Box<MiBlockS>>,
    pub local_free: Option<Box<MiBlockS>>,
    pub used: u16,
    pub block_size_shift: u8,
    pub heap_tag: u8,
    pub block_size: usize,
    pub page_start: Option<Vec<u8>>,
    pub keys: [usize; 2],
    pub xthread_free: AtomicUsize,
    pub xheap: AtomicUsize,
    pub next: Option<Box<MiPageS>>,
    pub prev: Option<Box<MiPageS>>,
    pub padding: [Option<Box<c_void>>; 1],
}

