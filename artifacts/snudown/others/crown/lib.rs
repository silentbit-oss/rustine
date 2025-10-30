#![allow(dead_code)]
#![allow(mutable_transmutes)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(unused_assignments)]
#![allow(unused_mut)]
#![feature(c_variadic)]
#![feature(extern_types)]
#![feature(label_break_value)]
#![feature(core_intrinsics)]

extern crate libc;
pub mod src {
pub mod autolink;
pub mod buffer;
pub mod houdini_href_e;
pub mod houdini_html_e;
pub mod html;
pub mod html_smartypants;
pub mod markdown;
pub mod siphash;
pub mod snudown;
pub mod stack;
} // mod src
