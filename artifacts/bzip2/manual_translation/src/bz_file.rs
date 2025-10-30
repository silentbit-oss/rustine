use crate::*;
use std::fs::File;



pub struct BzFile {
    pub handle: Option<File>,
    pub buf: [Char; 5000],
    pub bufN: Int32,
    pub writing: Bool,
    pub strm: BzStream,
    pub lastErr: Int32,
    pub initialisedOk: Bool,
}

