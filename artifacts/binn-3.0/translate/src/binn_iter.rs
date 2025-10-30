use crate::*;

#[derive(Clone)]
pub struct Binn_Iter_Struct {
    pub pnext: Option<Vec<u8>>,
    pub plimit: Option<Vec<u8>>,
    pub type_: i32,
    pub count: i32,
    pub current: i32,
}

pub type Binn_Iter = Option<Box<Binn_Iter_Struct>>;

