use crate::*;
use std::ptr;


pub fn zload(a: &mut z_t, buffer: &[u8]) -> usize {
    let buf = buffer;
    let mut buf_idx = 0;

    // Read sign and used fields from buffer
    unsafe {
        ptr::copy_nonoverlapping(
            buf.as_ptr().add(buf_idx),
            &mut a[0].sign as *mut i32 as *mut u8,
            std::mem::size_of::<i32>(),
        );
        buf_idx += std::mem::size_of::<i32>();

        ptr::copy_nonoverlapping(
            buf.as_ptr().add(buf_idx),
            &mut a[0].used as *mut usize as *mut u8,
            std::mem::size_of::<usize>(),
        );
        buf_idx += std::mem::size_of::<usize>();
    }

    if a[0].sign != 0 {
        if a[0].alloced < a[0].used {
            libzahl_realloc(a, a[0].used);
        }

        let chars_size = a[0].used * std::mem::size_of::<zahl_char_t>();
        a[0].chars = Some(vec![0; a[0].used].into_boxed_slice());
        
        unsafe {
            ptr::copy_nonoverlapping(
                buf.as_ptr().add(buf_idx),
                a[0].chars.as_mut().unwrap().as_mut_ptr() as *mut u8,
                chars_size,
            );
        }
    }

    let base_size = std::mem::size_of::<i32>() + std::mem::size_of::<usize>();
    if zzero(a) {
        base_size
    } else {
        base_size + a[0].used * std::mem::size_of::<zahl_char_t>()
    }
}
