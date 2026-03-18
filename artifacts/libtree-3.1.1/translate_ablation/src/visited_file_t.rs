use crate::*;
use std::fs::File;
use std::os::linux::raw::dev_t;
use std::os::linux::raw::ino_t;
#[derive(Clone)]
pub struct VisitedFileT {
    pub st_dev: dev_t,
    pub st_ino: ino_t,
}

