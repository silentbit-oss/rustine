use crate::*;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum ZPrimality {
    Nonprime = 0,
    ProbablyPrime,
    Prime,
}

