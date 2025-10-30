use crate::*;

#[derive(Clone)]
pub struct Mevent {
    pub id: i16,
    pub x: i32,
    pub y: i32,
    pub z: i32,
    pub bstate: mmask_t,
}

