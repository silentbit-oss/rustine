#![allow(dead_code)]
#![allow(mutable_transmutes)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(non_upper_case_globals)]
#![allow(unused_assignments)]
#![allow(unused_mut)]
#![feature(extern_types)]
#![feature(label_break_value)]


extern crate libc;
pub mod src {
pub mod ht;
pub mod samples {
pub mod bsearch;
pub mod demo;
pub mod dump;
pub mod lsearch;
pub mod perfget;
pub mod perflbh;
pub mod perfset;
pub mod stats;
} // mod samples
} // mod src
