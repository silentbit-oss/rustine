use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LodePngFilterStrategy {
    Zero = 0,
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Minsum,
    Entropy,
    BruteForce,
    Predefined,
}

