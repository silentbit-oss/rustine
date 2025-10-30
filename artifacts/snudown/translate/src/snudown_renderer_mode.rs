use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SnudownRendererMode {
    RENDERER_USERTEXT = 0,
    RENDERER_WIKI,
    RENDERER_COUNT,
}

impl SnudownRendererMode {
    pub const RENDERER_USERTEXT_VALUE: i32 = 0;
    pub const RENDERER_WIKI_VALUE: i32 = 1;
    pub const RENDERER_COUNT_VALUE: i32 = 2;
}

