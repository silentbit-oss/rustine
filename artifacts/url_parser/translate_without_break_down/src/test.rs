use crate::*;
use std::ffi::CStr;


pub fn url_get_protocol(url: Option<&str>) -> Option<String> {
    url_get_scheme(url)
}
pub fn url_get_hash(url: Option<&str>) -> Option<String> {
    url_get_fragment(url)
}
