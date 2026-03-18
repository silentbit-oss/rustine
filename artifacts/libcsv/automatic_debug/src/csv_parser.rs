use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc::dealloc;
use std::alloc::realloc;


#[derive(Clone)]
pub struct CsvParser {
    pub pstate: i32,
    pub quoted: i32,
    pub spaces: usize,
    pub entry_buf: Option<Vec<u8>>,
    pub entry_pos: usize,
    pub entry_size: usize,
    pub status: i32,
    pub options: u8,
    pub quote_char: u8,
    pub delim_char: u8,
    pub is_space: Option<fn(u8) -> i32>,
    pub is_term: Option<fn(u8) -> i32>,
    pub blk_size: usize,
    pub malloc_func: fn(usize) -> *mut u8,
    pub realloc_func: fn(*mut u8, usize) -> *mut u8,
    pub free_func: fn(*mut u8),
}

impl Default for CsvParser {
    fn default() -> Self {
	println!("* default");
        Self {
            pstate: 0,
            quoted: 0,
            spaces: 0,
            entry_buf: None,
            entry_pos: 0,
            entry_size: 0,
            status: 0,
            options: 0,
            quote_char: 0,
            delim_char: 0,
            is_space: None,
            is_term: None,
            blk_size: 0,
            malloc_func: |size| unsafe { alloc(Layout::from_size_align(size, 1).unwrap()) },
            realloc_func: |ptr, size| unsafe { realloc(ptr, Layout::from_size_align(size, 1).unwrap(), size) },
            free_func: |ptr| unsafe { dealloc(ptr, Layout::from_size_align(1, 1).unwrap()) },
        }
    }
}

