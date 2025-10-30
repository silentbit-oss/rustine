use crate::*;

pub type NcursesOutcSp = Option<Box<dyn FnMut(Option<Box<Screen>>, i32) -> i32>>;

