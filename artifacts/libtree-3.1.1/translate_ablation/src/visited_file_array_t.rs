use crate::*;
use std::fs::File;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
#[derive(Clone)]
pub struct VisitedFileArrayT {
    pub arr: Option<Vec<VisitedFileT>>,
    pub n: usize,
    pub capacity: usize,
}

