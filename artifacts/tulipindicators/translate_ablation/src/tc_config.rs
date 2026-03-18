use crate::*;

#[derive(Clone)]
pub struct TcConfig {
    pub period: i32,
    pub body_none: TC_REAL,
    pub body_short: TC_REAL,
    pub body_long: TC_REAL,
    pub wick_none: TC_REAL,
    pub wick_long: TC_REAL,
    pub near: TC_REAL,
}

