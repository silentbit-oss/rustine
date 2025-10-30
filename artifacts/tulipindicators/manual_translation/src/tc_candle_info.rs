use crate::*;

#[derive(Clone)]
pub struct TcCandleInfo {
    pub name: Option<String>,
    pub full_name: Option<String>,
    pub pattern: tc_set,
    pub candle: TcCandleFunction,
}

