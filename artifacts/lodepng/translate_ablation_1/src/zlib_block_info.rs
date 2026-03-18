use crate::*;

#[derive(Clone)]
pub struct ZlibBlockInfo {
    pub btype: i32,
    pub compressedbits: usize,
    pub uncompressedbytes: usize,
    pub treebits: usize,
    pub hlit: i32,
    pub hdist: i32,
    pub hclen: i32,
    pub clcl: Option<Vec<i32>>,
    pub clcl_size: usize,
    pub treecodes: Option<Vec<i32>>,
    pub treecodes_size: usize,
    pub litlenlengths: Option<Vec<i32>>,
    pub litlenlengths_size: usize,
    pub distlengths: Option<Vec<i32>>,
    pub distlengths_size: usize,
    pub lz77_lcode: Option<Vec<i32>>,
    pub lz77_dcode: Option<Vec<i32>>,
    pub lz77_lbits: Option<Vec<i32>>,
    pub lz77_dbits: Option<Vec<i32>>,
    pub lz77_lvalue: Option<Vec<i32>>,
    pub lz77_dvalue: Option<Vec<i32>>,
    pub lz77_size: usize,
    pub numlit: usize,
    pub numlen: usize,
}

