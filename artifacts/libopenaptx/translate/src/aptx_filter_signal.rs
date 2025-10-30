use crate::*;

#[derive(Clone)]
pub struct Aptx_Filter_Signal {
    pub buffer: [i32; 2 * 16],
    pub pos: u8,
}

