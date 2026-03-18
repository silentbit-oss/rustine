use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum HtmlTag {
    HTML_TAG_NONE = 0,
    HTML_TAG_OPEN = 1,
    HTML_TAG_CLOSE = 2,
}

