use crate::*;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum LfsStatus {
    OkRelocated = 1,
    OkDropped = 2,
    OkOrphaned = 3,
}

