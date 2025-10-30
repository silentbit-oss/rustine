use crate::*;
use std::sync::Mutex;

pub type ZahlCharT = u32;

// Define the zahl_char_t type - assuming it's an unsigned integer type (common for bignum implementations)
// If this is incorrect, you'll need to adjust based on the actual C definition
type zahl_char_t = u32;  // or u64, depending on the original C implementation

pub struct Z {
    pub sign: i32,
    pub used: usize,
    pub alloced: usize,
    pub chars: Option<Box<[zahl_char_t]>>,
}

