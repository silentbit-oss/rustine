use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum BufErrorT {
    BUF_OK = 0,
    BUF_ENOMEM = -1,
    BUF_EINVALIDIDX = -2,
}

