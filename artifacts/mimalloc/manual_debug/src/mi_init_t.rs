use crate::*;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum MiInitT {
    UNINIT,
    DEFAULTED,
    INITIALIZED,
}

