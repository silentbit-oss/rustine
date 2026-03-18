use crate::*;

#[derive(Clone)]
pub struct GzHeader {
    pub text: i32,
    pub time: u64,  // uLong is u64
    pub xflags: i32,
    pub os: i32,
    pub extra: Option<Vec<u8>>,  // Bytef is u8
    pub extra_len: u32,  // uInt is u32
    pub extra_max: u32,  // uInt is u32
    pub name: Option<Vec<u8>>,  // Bytef is u8
    pub name_max: u32,  // uInt is u32
    pub comment: Option<Vec<u8>>,  // Bytef is u8
    pub comm_max: u32,  // uInt is u32
    pub hcrc: i32,
    pub done: i32,
}

