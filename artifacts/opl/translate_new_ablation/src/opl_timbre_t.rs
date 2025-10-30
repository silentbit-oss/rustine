use crate::*;

#[derive(Clone)]
pub struct OplTimbreT {
    pub modulator_e862: u32,
    pub carrier_e862: u32,
    pub modulator_40: u8,
    pub carrier_40: u8,
    pub feedconn: u8,
    pub finetune: i8,
    pub notenum: u8,
    pub noteoffset: i16,
}

