use crate::*;
use std::os::raw;


pub struct XErrorEvent {
    pub type_: raw::c_int,
    pub display: Option<Box<Display>>,
    pub resourceid: XID,
    pub serial: raw::c_ulong,
    pub error_code: raw::c_uchar,
    pub request_code: raw::c_uchar,
    pub minor_code: raw::c_uchar,
}

