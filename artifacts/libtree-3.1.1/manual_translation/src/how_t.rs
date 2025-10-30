use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum HowT {
    INPUT,
    DIRECT,
    RPATH,
    LD_LIBRARY_PATH,
    RUNPATH,
    LD_SO_CONF,
    DEFAULT,
}

