use crate::*;
use std::fs::File;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
#[derive(Clone)]
pub struct LibtreeStateT {
    pub verbosity: i32,
    pub path: i32,
    pub color: i32,
    pub ld_conf_file: Option<String>,
    pub max_depth: u64,
    pub string_table: StringTableT,
    pub visited: VisitedFileArrayT,
    pub PLATFORM: Option<String>,
    pub LIB: Option<String>,
    pub OSNAME: Option<String>,
    pub OSREL: Option<String>,
    pub rpath_offsets: [usize; 32],
    pub ld_library_path_offset: usize,
    pub default_paths_offset: usize,
    pub ld_so_conf_offset: usize,
    pub found_all_needed: [char; 32],
}

