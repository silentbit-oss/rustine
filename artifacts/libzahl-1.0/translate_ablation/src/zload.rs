use crate::*;
use std::ptr;


pub fn zload(a: &mut z_t, buffer: &[u8]) -> usize {
    let mut buf_idx = 0;
    
    // Read sign
    let sign = unsafe {
        ptr::read_unaligned(buffer.as_ptr().add(buf_idx) as *const i32)
    };
    buf_idx += std::mem::size_of::<i32>();
    
    // Read used
    let used = unsafe {
        ptr::read_unaligned(buffer.as_ptr().add(buf_idx) as *const usize)
    };
    buf_idx += std::mem::size_of::<usize>();
    
    a[0].sign = sign;
    a[0].used = used;
    
    if a[0].sign != 0 {
        // Ensure sufficient allocation
        if a[0].alloced < a[0].used {
            libzahl_realloc(a, a[0].used);
        }
        
        // Copy the character data
        let bytes_needed = a[0].used * std::mem::size_of::<zahl_char_t>();
        if let Some(chars) = &mut a[0].chars {
            let slice = chars.as_mut();
            let src_slice = &buffer[buf_idx..buf_idx + bytes_needed];
            slice.copy_from_slice(unsafe {
                std::slice::from_raw_parts(
                    src_slice.as_ptr() as *const zahl_char_t,
                    a[0].used
                )
            });
        }
    }
    
    // Calculate and return total bytes read
    let base_size = std::mem::size_of::<i32>() + std::mem::size_of::<usize>();
    if zzero(a) {
        base_size
    } else {
        base_size + a[0].used * std::mem::size_of::<zahl_char_t>()
    }
}
