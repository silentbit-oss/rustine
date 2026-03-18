use crate::*;

pub type ZahlCharT = u32;

pub type zahl_char_t = u32;  // Assuming this is the correct type - adjust if needed

#[derive(Debug)]
pub struct Z {
    pub sign: i32,
    pub used: usize,
    pub alloced: usize,
    pub chars: Option<Box<[zahl_char_t]>>,
}

pub type z_t = [Z; 1];

