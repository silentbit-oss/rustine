use crate::*;
use rand::Rng;

pub fn ti_decay_start(options: Option<&f64>) -> i32 {
    let _ = options;
    0
}
pub struct Person {
    name: String,
    age: u32,
}

pub fn process_person(name: Option<&str>) -> Option<String> {
    let name = name?; // Early return if None using the ? operator

    let mut rng = rand::thread_rng();
    let age = rng.gen_range(20..=60);

    let p = Person {
        name: name.to_string(),
        age,
    };

    Some(format!("Person: {}, Age: {}", p.name, p.age))
}

pub unsafe extern "C" fn ti_sma_stream_run(
    stream_in: *mut TiStream,
    size: i32,
    inputs: *const *const f64,
    outputs: *const *mut f64,
) -> i32 {
    let stream = stream_in as *mut TiStreamSma;
    let mut progress = (*stream).progress;
    let real = *inputs.offset(0);
    let period = (*stream).period;
    let mut sma = *outputs.offset(0);
    let per = (*stream).per;
    let mut sum = (*stream).sum;
    let mut buffer_idx = (*stream).buffer_idx;
    let buffer = (*stream).buffer.as_mut().unwrap();
    
    if progress == (-period + 1) {
        // Do nothing
    } else {
        // Do nothing
    }
    
    let mut i = 0;
    while (progress < 1) && (i < size) {
        buffer_idx = (buffer_idx + 1) % period;
        let value = *real.offset(i as isize) * per;
        buffer[buffer_idx as usize] = value;
        sum += value;
        
        i += 1;
        progress += 1;
    }

    if (i > 0) && (progress == 1) {
        *sma = sum;
        sma = sma.offset(1);
    }
    
    while i < size {
        buffer_idx = (buffer_idx + 1) % period;
        
        let old_value = buffer[buffer_idx as usize];
        let new_value = *real.offset(i as isize) * per;
        
        sum -= old_value;
        buffer[buffer_idx as usize] = new_value;
        sum += new_value;
        
        *sma = sum;
        sma = sma.offset(1);
        
        i += 1;
        progress += 1;
    }

    (*stream).progress = progress;
    (*stream).sum = sum;
    (*stream).buffer_idx = buffer_idx;
    0
}
