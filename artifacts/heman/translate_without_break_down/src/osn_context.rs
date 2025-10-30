use crate::*;

#[derive(Clone)]
pub struct OsnContext {
    pub perm: Option<Vec<i16>>,
    pub perm_grad_index3_d: Option<Vec<i16>>,
}

