use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MkdAutolink {
    MKDA_NOT_AUTOLINK,
    MKDA_NORMAL,
    MKDA_EMAIL,
}

