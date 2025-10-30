use crate::*;

pub type OutFunc = Option<Box<dyn FnMut(&mut dyn std::any::Any, &mut [u8], u32) -> i32>>;

