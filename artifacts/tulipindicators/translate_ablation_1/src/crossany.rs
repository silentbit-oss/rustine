use crate::*;

pub fn ti_crossany_start(options: Option<&f64>) -> i32 {
    let _ = options; // Explicitly ignore the parameter to avoid unused variable warning
    1
}
pub fn ti_crossany(size: i32, inputs: &[&[f64]], options: &[f64], outputs: &mut [&mut [f64]]) -> i32 {
    let a = inputs[0];
    let b = inputs[1];
    let output = &mut outputs[0];
    
    for i in 1..size as usize {
        let cross_condition = ((a[i] > b[i]) && (a[i - 1] <= b[i - 1])) || ((a[i] < b[i]) && (a[i - 1] >= b[i - 1]));
        output[i - 1] = if cross_condition { 1.0 } else { 0.0 };
    }

    0
}
