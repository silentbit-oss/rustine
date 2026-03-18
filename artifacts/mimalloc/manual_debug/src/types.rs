use crate::*;
use std::os::raw::c_ulong;
use std::os::raw::c_void;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub type mi_arena_id_t = i32;


pub type mi_atomic_once_t = AtomicUsize;


pub type mi_atomic_guard_t = AtomicUsize;

pub type mi_ssize_t = i64;


pub type mi_encoded_t = usize;


pub type mi_threadid_t = usize;

pub static MI_THREAD_ID: AtomicUsize = AtomicUsize::new(0);


pub type mi_thread_free_t = c_ulong;

// mi_slice_t is an alias for mi_page_t, but mi_page_t isn't defined in scope.
// Since we can't see the full context, we'll need to either:
// 1. Define mi_page_t if it's missing, or
// 2. Comment out this line if mi_page_t is defined elsewhere but not accessible

// For now, let's comment this out since the error indicates mi_page_t is not in scope
// pub type mi_slice_t = mi_page_t;

// Alternative: If mi_page_t should be available but isn't, we might need to import it
// use crate::mi_page_t; // This assumes mi_page_t is defined in the current crate

// Since we can't see the full context and the error says mi_page_t is not found,
// the safest approach is to comment out this line until mi_page_t is properly defined

pub type mi_msecs_t = i64;


pub type mi_bitmap_field_t = AtomicUsize;

pub type mi_bitmap_t = Option<Box<mi_bitmap_field_t>>;

pub type mi_bitmap_index_t = usize;

