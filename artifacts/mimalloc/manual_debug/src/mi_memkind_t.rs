use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MiMemkindE {
    MiMemNone,
    MiMemExternal,
    MiMemStatic,
    MiMemOs,
    MiMemOsHuge,
    MiMemOsRemap,
    MiMemArena,
}

pub type MiMemkindT = MiMemkindE;

