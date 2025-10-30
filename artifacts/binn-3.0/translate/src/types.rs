use crate::*;

pub type BOOL = i32;

pub type int64 = i64;

pub type uint64 = u64;

pub type u16 = std::primitive::u16;

pub type u32 = std::os::raw::c_uint;

// u64 is already a primitive type in Rust, no need to redefine
// The C typedef `unsigned long long int` maps directly to Rust's u64

