use crate::*;

#[derive(Clone)]
pub struct AptxFilterSignal {
    pub buffer: [i32; 2 * 16],
    pub pos: u8,
}

