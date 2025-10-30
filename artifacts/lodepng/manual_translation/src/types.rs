use crate::*;

pub type z_size_t = usize;

pub type Byte = u8;

pub type uInt = u32;

pub type uLong = u64;

pub type Bytef = u8;

pub type charf = char;

pub type intf = i32;

pub type uIntf = uInt;

pub type uLongf = u32;

pub type voidpc = *const std::ffi::c_void;

pub type voidpf = *mut std::ffi::c_void;

pub type Voidp = Option<Box<()>>;

pub type z_crc_t = u32;

// Assuming z_stream is an extern C type
#[repr(C)]
pub struct z_stream {
    // Add actual fields here if known, or leave empty for opaque type
    _unused: [u8; 0],
}

pub type ZStreamp = Option<Box<z_stream>>;

pub type GzHeaderp = Option<Box<GzHeader>>;

#[derive(Debug)]
pub struct GzHeader {
    pub text: i32,
    pub time: u32,
    pub xflags: i32,
    pub os: i32,
    pub extra: *mut u8,
    pub extra_len: u32,
    pub extra_max: u32,
    pub name: *mut u8,
    pub name_max: u32,
    pub comment: *mut u8,
    pub comment_max: u32,
    pub hcrc: i32,
    pub done: i32,
}

