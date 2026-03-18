use crate::*;
use std::mem::ManuallyDrop;
use std::mem::MaybeUninit;
use std::os::raw::c_void;
use std::sync::atomic::AtomicUsize;



pub struct MiHeapAreaExS {
    pub area: MiHeapAreaS,
    pub page: Option<Box<MiPageS>>,
}

pub type MiHeapAreaExT = MiHeapAreaExS;

