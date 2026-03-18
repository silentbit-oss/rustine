use crate::*;
use std::mem::size_of;


pub type mi_msecs_t = i64;

#[derive(Clone)]
pub struct MiProcessInfoS {
    pub elapsed: mi_msecs_t,
    pub utime: mi_msecs_t,
    pub stime: mi_msecs_t,
    pub current_rss: usize,
    pub peak_rss: usize,
    pub current_commit: usize,
    pub peak_commit: usize,
    pub page_faults: usize,
}

pub type mi_process_info_t = MiProcessInfoS;

