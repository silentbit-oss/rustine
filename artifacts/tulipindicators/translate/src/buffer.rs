use crate::*;

pub fn ti_buffer_new(size: i32) -> Option<Box<TiBuffer>> {
    if size <= 0 {
        return None;
    }

    Some(Box::new(TiBuffer {
        size,
        pushes: 0,
        index: 0,
        sum: 0.0,
        vals: Vec::with_capacity(size as usize),
    }))
}
pub fn ti_buffer_free(buffer: TiBuffer) {
    // Rust's drop mechanism will automatically free the memory when `buffer` goes out of scope
    // No explicit free needed as `TiBuffer` contains a Vec which manages its own memory
}
