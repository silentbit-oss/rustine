use crate::*;

#[derive(Clone)]
pub struct Mi_Error_Fun(pub fn(i32, Option<Box<()>>));

