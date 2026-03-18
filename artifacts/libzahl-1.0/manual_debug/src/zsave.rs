use crate::*;
use std::ptr;


pub fn zsave(a: &z_t, buffer: Option<&mut [u8]>) -> usize {
    let required_size = std::mem::size_of::<i32>() + std::mem::size_of::<usize>() + 
                       if zzero(a) { 0 } else { a[0].used * std::mem::size_of::<zahl_char_t>() };

    if let Some(buf) = buffer {
        if buf.len() < required_size {
            return required_size;
        }

        let mut buf_idx = 0;

        // Write sign
        let sign_slice = &mut buf[buf_idx..buf_idx + std::mem::size_of::<i32>()];
        sign_slice.copy_from_slice(&a[0].sign.to_ne_bytes());
        buf_idx += std::mem::size_of::<i32>();

        // Write used
        let used_slice = &mut buf[buf_idx..buf_idx + std::mem::size_of::<usize>()];
        used_slice.copy_from_slice(&a[0].used.to_ne_bytes());
        buf_idx += std::mem::size_of::<usize>();

        // Write chars if not zero
        if !zzero(a) {
            if let Some(chars) = &a[0].chars {
                let char_bytes = unsafe {
                    std::slice::from_raw_parts(
                        chars.as_ptr() as *const u8,
                        a[0].used * std::mem::size_of::<zahl_char_t>()
                    )
                };
                buf[buf_idx..buf_idx + char_bytes.len()].copy_from_slice(char_bytes);
            }
        }
    }

    required_size
}
