use crate::*;

pub fn zset(a: &mut z_t, b: &z_t) {
    if zzero(b) {
        a[0].sign = 0;
    } else {
        if a[0].alloced < b[0].used {
            libzahl_realloc(a, b[0].used);
        }
        a[0].sign = b[0].sign;
        a[0].used = b[0].used;
        
        // Create a new Box with the correct size and copy the elements
        let mut new_chars = vec![0; b[0].used].into_boxed_slice();
        if let Some(ref b_chars) = b[0].chars {
            new_chars.copy_from_slice(&b_chars[..b[0].used]);
        }
        a[0].chars = Some(new_chars);
    }
}
