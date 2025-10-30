use crate::*;
use std::os::raw::c_int;
use std::os::raw::c_uchar;
use std::os::raw::c_ulong;


#[derive(Clone)]
pub struct XErrorEvent {
    pub type_: c_int,
    pub display: Option<Box<Display>>,
    pub resourceid: XID,
    pub serial: c_ulong,
    pub error_code: c_uchar,
    pub request_code: c_uchar,
    pub minor_code: c_uchar,
}

