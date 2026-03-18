use crate::*;
use rand::Rng;
use std::alloc::Layout;
use std::alloc::alloc;
use std::assert;
use std::convert::TryInto;

pub fn ti_sma_start(options: Option<&[f64]>) -> Option<i32> {
	println!("\n* ti_sma_start");
    // Check if options is None (equivalent to NULL check in C)
    let options = options?;
    
    // Ensure the slice has at least one element to avoid panic
    if options.is_empty() {
        return None;
    }

    Some(options[0] as i32 - 1)
}

pub fn ti_sma(size: i32, inputs: Option<&[&[f64]]>, options: Option<&[f64]>, outputs: Option<&mut [&mut [f64]]>) -> i32 {
	println!("\n* ti_sma");
    // Check for None options (equivalent to NULL checks in C)
    if inputs.is_none() || options.is_none() || outputs.is_none() {
        return 1;
    }

    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    // Get input and output slices
    let input = inputs[0];
    let output = &mut outputs[0];

    let period = options[0] as i32;
    let mut output_idx = 0;
    let scale = 1.0 / period as f64;

    if period < 1 {
        return 1;
    }

    // Check if size is sufficient
    let start = match ti_sma_start(Some(options)) {
        Some(s) => s,
        None => return 0,
    };

    if size <= start {
        return 0;
    }

    // Calculate initial sum
    let mut sum = 0.0;
    for i in 0..period {
        sum += input[i as usize];
    }

    output[output_idx] = sum * scale;
    output_idx += 1;

    // Calculate rolling sum
    for i in period..size {
        let i_usize = i as usize;
        sum += input[i_usize];
        sum -= input[i_usize - period as usize];
        output[output_idx] = sum * scale;
        output_idx += 1;
    }

    0
}
pub fn ti_sma_stream_free(stream: Option<Box<TiStream>>) {
	println!("\n* ti_sma_stream_free");
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // so no explicit free is needed. The Option wrapper allows for NULL checking.
    // Just let the stream drop naturally if it's Some
}


pub struct Person {
    name: String,
    age: u32,
}

pub fn process_person(name: Option<&str>) -> Option<String> {
    if name.is_none() {
        return None;
    }

    let name = name.unwrap();

    let mut rng = rand::thread_rng();
    let age = rng.gen_range(20..=60);

    let p = Person {
        name: name.to_string(),
        age,
    };

    Some(format!("Person: {}, Age: {}", p.name, p.age))
}

pub fn ti_sma_stream_new(options: &[f64], stream_in: &mut Option<*mut TiStream>) -> i32 {
    let period = options[0] as i32;
    if period < 1 {
        return 1;
    }

    // Calculate the total size needed: size of TiStreamSma + (size of f64 * period)
    let total_size = std::mem::size_of::<TiStreamSma>() + (std::mem::size_of::<f64>() * period as usize);
    
    // Allocate memory using the global allocator
    let layout = Layout::from_size_align(total_size, std::mem::align_of::<TiStreamSma>())
        .expect("Invalid layout");
    
    let ptr = unsafe { alloc(layout) as *mut TiStreamSma };
    if ptr.is_null() {
        return 2;
    }

    // Initialize the stream struct
    unsafe {
        (*ptr).index = 72;
        (*ptr).progress = -ti_sma_start(Some(options)).unwrap();
        (*ptr).period = period;
        (*ptr).per = 1.0 / period as f64;
        (*ptr).sum = 0.0;
        (*ptr).buffer_idx = -1;
    }

    *stream_in = Some(ptr as *mut TiStream);
    0
}
