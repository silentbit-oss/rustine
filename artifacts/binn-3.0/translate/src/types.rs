use crate::*;

pub type BOOL = i32;

pub type int64 = i64;

pub type uint64 = u64;

// No need to redefine u16 as it's already a built-in type in Rust

pub type u32 = std::os::raw::c_uint;

// No need to redefine u64 as it's a primitive type in Rust
// The C typedef `unsigned long long int` is equivalent to Rust's u64

