use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ZopfliFormat {
    Gzip,
    Zlib,
    Deflate,
}

