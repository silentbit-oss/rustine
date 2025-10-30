use crate::*;

pub type TiIndicatorStreamRun = Option<
    Box<
        dyn FnMut(
            TiStream,
            i32,
            Option<Vec<Option<Vec<f64>>>>,
            Option<Vec<Option<Vec<f64>>>>
        ) -> i32
    >
>;

