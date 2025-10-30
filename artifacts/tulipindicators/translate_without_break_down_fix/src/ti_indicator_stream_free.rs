use crate::*;
use std::sync::Arc;


pub type TiIndicatorStreamFree = Option<Arc<dyn Fn(TiStream)>>;

