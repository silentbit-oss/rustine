use crate::*;
use std::mem;


pub fn zload(a: &mut Z, buffer: &[u8]) -> usize {
    let mut buf_idx = 0;

    // Read sign and used fields from buffer
    a.sign = i32::from_ne_bytes(buffer[buf_idx..buf_idx + mem::size_of::<i32>()].try_into().unwrap());
    buf_idx += mem::size_of::<i32>();

    a.used = usize::from_ne_bytes(buffer[buf_idx..buf_idx + mem::size_of::<usize>()].try_into().unwrap());
    buf_idx += mem::size_of::<usize>();

    if a.sign != 0 {
        // Ensure we have enough allocated space
        if a.alloced < a.used {
            libzahl_realloc(a, a.used);
        }

        // Copy the character data if present
        if let Some(chars) = &mut a.chars {
            let char_size = mem::size_of::<u32>();
            let needed_bytes = a.used * char_size;
            let bytes = &buffer[buf_idx..buf_idx + needed_bytes];
            
            // Convert bytes to u32 values and copy
            for (i, chunk) in bytes.chunks_exact(char_size).enumerate() {
                chars[i] = u32::from_ne_bytes(chunk.try_into().unwrap());
            }
            buf_idx += needed_bytes;
        }
    }

    // Calculate total bytes read
    mem::size_of::<i32>() + mem::size_of::<usize>() + if zzero(a) { 0 } else { a.used * mem::size_of::<u32>() }
}
