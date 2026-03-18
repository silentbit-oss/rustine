use crate::*;
use std::sync::atomic::AtomicUsize;


pub type MiHeapAreaVisitFun = fn(
    heap: Option<&MiHeapT>,
    area: Option<&MiHeapAreaExT>,
    arg: Option<&mut std::ffi::c_void>,
) -> bool;

