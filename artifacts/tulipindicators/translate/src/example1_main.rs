use translate::*;
use std::env;
pub fn main() {
    let data_in = [5.0, 8.0, 12.0, 11.0, 9.0, 8.0, 7.0, 10.0, 11.0, 13.0];
    let input_length = data_in.len();
    println!("We have {} bars of input data.", input_length);
    print_array(Some(&data_in), input_length);

    let options = [3.0];
    print!("Our option array is: ");
    print_array(Some(&options), options.len());

    let start = ti_sma_start(Some(&options));
    println!("The start amount is: {}", start);

    let output_length = input_length - start as usize;
    let mut data_out = vec![0.0; output_length];
    println!("The output length is: {}", output_length);

    let all_inputs = [&data_in[..]];
    let mut output_slice = data_out.as_mut_slice();
    let mut all_outputs = [output_slice];

    let error = ti_sma(input_length as i32, Some(&all_inputs), Some(&options), Some(&mut all_outputs));
    assert_eq!(error, 0);

    print!("The output data is: ");
    print_array(Some(&data_out), output_length);
}
