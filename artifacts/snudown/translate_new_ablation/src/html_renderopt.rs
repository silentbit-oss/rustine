use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct HtmlRenderopt {
    pub toc_data: TocData,
    pub toc_id_prefix: Option<String>,
    pub flags: u32,
    pub html_element_whitelist: Option<Vec<String>>,
    pub html_attr_whitelist: Option<Vec<String>>,
    pub link_attributes: Option<fn(ob: Buf, url: Buf, self_: Box<dyn std::any::Any>)>,
}

#[derive(Clone)]
pub struct TocData {
    pub header_count: i32,
    pub current_level: i32,
    pub level_offset: i32,
}

