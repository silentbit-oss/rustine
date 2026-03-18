use std::assert;
use std::env;
use translate_without_break_down::*;

pub fn main() {
    let data_in = [5.0, 8.0, 12.0, 11.0, 9.0, 8.0, 7.0, 10.0, 11.0, 13.0];
    let input_length = data_in.len();
    println!("We have {} bars of input data.", input_length);
    print_array(Some(&data_in), input_length);

    let options = [3.0];
    println!("Our option array is: ");
    print_array(Some(&options), options.len());

    let start = ti_sma_start(Some(&options)).unwrap();
    println!("The start amount is: {}", start);

    let output_length = input_length - start as usize;
    let mut data_out = vec![0.0; output_length];
    println!("The output length is: {}", output_length);

    let all_inputs = [&data_in[..]];
    let mut all_outputs = [&mut data_out[..]];

    let error = ti_sma(
        input_length as i32,
        Some(&all_inputs),
        Some(&options),
        Some(&mut all_outputs),
    );
    assert!(error == 0);

    println!("The output data is: ");
    print_array(Some(&data_out), output_length);
}
