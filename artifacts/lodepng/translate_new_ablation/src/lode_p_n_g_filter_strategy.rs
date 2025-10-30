use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LodePNGFilterStrategy {
    LFS_ZERO = 0,
    LFS_ONE = 1,
    LFS_TWO = 2,
    LFS_THREE = 3,
    LFS_FOUR = 4,
    LFS_MINSUM,
    LFS_ENTROPY,
    LFS_BRUTE_FORCE,
    LFS_PREDEFINED,
}

