use crate::*;
use std::mem;


#[derive(Clone)]
pub struct MiMemidS {
    pub mem: MiMemidUnion,
    pub is_pinned: bool,
    pub initially_committed: bool,
    pub initially_zero: bool,
    pub memkind: MiMemkindT,
}

#[derive(Clone)]
pub enum MiMemidUnion {
    Os(MiMemidOsInfo),
    Arena(MiMemidArenaInfo),
}

