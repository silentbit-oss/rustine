use crate::*;
use std::mem::size_of;


#[derive(Clone)]
pub struct SnudownRenderopt {
    pub html: HtmlRenderopt,
    pub nofollow: i32,
    pub target: Option<String>,
}

