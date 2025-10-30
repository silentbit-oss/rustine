use crate::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum KmPointClassification {
    POINT_BEHIND_PLANE = -1,
    POINT_ON_PLANE = 0,
    POINT_INFRONT_OF_PLANE = 1,
}

