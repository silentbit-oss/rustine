#![feature(core_intrinsics)]
#![allow(dead_code)]
#![allow(mutable_transmutes)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(unused_assignments)]
#![allow(unused_mut)]
#![feature(register_tool)]
#![register_tool(c2rust)]
#![feature(const_mut_refs, const_fn_fn_ptr_basics)]







pub mod src {
pub mod autolink;
pub mod buffer;
pub mod markdown;
pub mod stack;
} // mod src

