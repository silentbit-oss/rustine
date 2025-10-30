use crate::*;
use std::fs::File;



pub struct BitStream {
    pub handle: Option<File>,
    pub buffer: Int32,
    pub buff_live: Int32,
    pub mode: Char,
}

