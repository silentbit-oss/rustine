use crate::*;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;


#[derive(Clone)]
pub struct MiVisitBlocksArgsS {
    pub visit_blocks: bool,
    pub visitor: Option<MiBlockVisitFun>,
    pub arg: Option<Vec<u8>>,
}

pub type MiVisitBlocksArgsT = MiVisitBlocksArgsS;

