use crate::*;
use std::sync::Mutex;
use std::sync::atomic::AtomicI64;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;



pub struct MiArenaS {
    pub id: i32,
    pub memid: MiMemidS,
    pub start: AtomicPtr<u8>,
    pub block_count: usize,
    pub field_count: usize,
    pub meta_size: usize,
    pub meta_memid: MiMemidS,
    pub numa_node: i32,
    pub exclusive: bool,
    pub is_large: bool,
    pub abandoned_visit_lock: Mutex<()>,
    pub search_idx: AtomicUsize,
    pub purge_expire: AtomicI64,
    pub blocks_dirty: Option<Box<[AtomicUsize]>>,
    pub blocks_committed: Option<Box<[AtomicUsize]>>,
    pub blocks_purge: Option<Box<[AtomicUsize]>>,
    pub blocks_abandoned: Option<Box<[AtomicUsize]>>,
    pub blocks_inuse: [AtomicUsize; 1],
}

