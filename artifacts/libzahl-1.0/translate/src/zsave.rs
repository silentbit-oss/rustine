use crate::*;

pub fn zsave(a: &Z, buffer: Option<&mut [u8]>) -> usize {
    let required_size = std::mem::size_of::<i32>() + std::mem::size_of::<usize>() + 
                        if zzero(a) { 0 } else { a.used * std::mem::size_of::<u32>() };

    if let Some(buf) = buffer {
        let mut buf_idx = 0;

        // Write sign
        if buf_idx + std::mem::size_of::<i32>() <= buf.len() {
            buf[buf_idx..buf_idx + std::mem::size_of::<i32>()].copy_from_slice(&a.sign.to_ne_bytes());
            buf_idx += std::mem::size_of::<i32>();
        }

        // Write used
        if buf_idx + std::mem::size_of::<usize>() <= buf.len() {
            buf[buf_idx..buf_idx + std::mem::size_of::<usize>()].copy_from_slice(&a.used.to_ne_bytes());
            buf_idx += std::mem::size_of::<usize>();
        }

        // Write chars if not zero
        if !zzero(a) {
            if let Some(chars) = &a.chars {
                let bytes_needed = a.used * std::mem::size_of::<u32>();
                if buf_idx + bytes_needed <= buf.len() {
                    let src = unsafe {
                        std::slice::from_raw_parts(
                            chars.as_ptr() as *const u8,
                            bytes_needed
                        )
                    };
                    buf[buf_idx..buf_idx + bytes_needed].copy_from_slice(src);
                }
            }
        }
    }

    required_size
}
