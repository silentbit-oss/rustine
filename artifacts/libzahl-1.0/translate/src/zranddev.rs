use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Zranddev {
    FastRandom = 0,
    SecureRandom,
}

