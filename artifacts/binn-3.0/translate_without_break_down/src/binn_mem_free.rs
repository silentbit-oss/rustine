use crate::*;

pub type BinnMemFree = Option<Box<dyn FnMut(Option<Box<()>>)>>;

