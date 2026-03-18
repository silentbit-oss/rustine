use crate::*;
use std::sync::atomic::AtomicUsize;



pub struct MiThreadDataS {
    pub heap: MiHeapT,
    pub tld: MiTldT,
    pub memid: MiMemidS,
}

pub type MiThreadDataT = Option<Box<MiThreadDataS>>;

