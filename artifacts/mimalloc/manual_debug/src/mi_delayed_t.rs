use crate::*;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum MiDelayedE {
    MI_USE_DELAYED_FREE = 0,
    MI_DELAYED_FREEING = 1,
    MI_NO_DELAYED_FREE = 2,
    MI_NEVER_DELAYED_FREE = 3,
}

pub type MiDelayedT = MiDelayedE;

