use crate::*;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum KmPointClassification {
    PointBehindPlane = -1,
    PointOnPlane = 0,
    PointInfrontOfPlane = 1,
}

