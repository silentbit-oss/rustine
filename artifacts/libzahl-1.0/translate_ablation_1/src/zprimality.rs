use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ZPrimality {
    NONPRIME = 0,
    PROBABLY_PRIME,
    PRIME,
}

