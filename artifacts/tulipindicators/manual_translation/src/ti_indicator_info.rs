use crate::*;
use std::sync::Arc;



pub struct TiIndicatorInfo {
    pub name: Option<String>,
    pub full_name: Option<String>,
    pub start: TiIndicatorStartFunction,
    pub indicator: TiIndicatorFunction,
    pub indicator_ref: TiIndicatorFunction,
    pub type_: i32,
    pub inputs: i32,
    pub options: i32,
    pub outputs: i32,
    pub input_names: [Option<String>; 1],
    pub option_names: [Option<String>; 1],
    pub output_names: [Option<String>; 1],
    pub stream_new: TiIndicatorStreamNew,
    pub stream_run: TiIndicatorStreamRun,
    pub stream_free: TiIndicatorStreamFree,
}

