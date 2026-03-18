use crate::*;

pub fn ti_buffer_new(size: i32) -> Option<Box<TiBuffer>> {
	println!("\n* ti_buffer_new");
    if size <= 0 {
        return None;
    }

    Some(Box::new(TiBuffer {
        size,
        pushes: 0,
        index: 0,
        sum: 0.0,
        vals: vec![0.0; size as usize],
    }))
}
pub fn ti_buffer_free(buffer: TiBuffer) {
	println!("\n* ti_buffer_free");
    // In Rust, memory is automatically managed by the ownership system.
    // When `buffer` goes out of scope here, it will be dropped (freed).
    // No explicit free is needed as the Vec<f64> inside will be automatically deallocated.
}
