use crate::*;
use std::sync::Arc;


#[derive(Clone)]
pub struct LfsDirCommitCommit {
    pub lfs: Option<Box<Lfs>>,
    pub commit: Option<Box<LfsCommit>>,
}

