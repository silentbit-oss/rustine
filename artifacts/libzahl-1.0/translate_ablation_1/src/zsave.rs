use crate::*;
use std::ptr;


pub fn zsave(a: &z_t, buffer: Option<&mut [u8]>) -> usize {
    let header_size = std::mem::size_of::<i32>() + std::mem::size_of::<usize>();
    
    if let Some(buffer) = buffer {
        let mut buf_idx = 0;
        
        // Copy sign
        let sign_slice = &a[0].sign.to_ne_bytes();
        let sign_len = sign_slice.len();
        if buf_idx + sign_len <= buffer.len() {
            buffer[buf_idx..buf_idx + sign_len].copy_from_slice(sign_slice);
            buf_idx += sign_len;
        }
        
        // Copy used
        let used_slice = &a[0].used.to_ne_bytes();
        let used_len = used_slice.len();
        if buf_idx + used_len <= buffer.len() {
            buffer[buf_idx..buf_idx + used_len].copy_from_slice(used_slice);
            buf_idx += used_len;
        }
        
        // Copy chars if not zero
        if !zzero(a) {
            if let Some(chars) = &a[0].chars {
                let chars_bytes = unsafe {
                    std::slice::from_raw_parts(
                        chars.as_ptr() as *const u8,
                        a[0].used * std::mem::size_of::<zahl_char_t>()
                    )
                };
                if buf_idx + chars_bytes.len() <= buffer.len() {
                    buffer[buf_idx..buf_idx + chars_bytes.len()].copy_from_slice(chars_bytes);
                }
            }
        }
    }
    
    // Calculate total size
    if zzero(a) {
        header_size
    } else {
        header_size + a[0].used * std::mem::size_of::<zahl_char_t>()
    }
}
