use crate::*;

#[derive(Clone)]
pub struct HuffmanTree {
    pub codes: Option<Vec<u32>>,
    pub lengths: Option<Vec<u32>>,
    pub maxbitlen: u32,
    pub numcodes: u32,
    pub table_len: Option<Vec<u8>>,
    pub table_value: Option<Vec<u16>>,
}

