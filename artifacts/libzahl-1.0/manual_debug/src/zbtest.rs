use crate::*;

pub fn zbtest(a: &z_t, bit: usize) -> i32 {
    let chars;
    if zzero(a) {
        return 0;
    }
    chars = bit >> 5;
    if chars >= a[0].used {
        return 0;
    }
    let bit = bit & (32 - 1);
    match &a[0].chars {
        Some(chars_array) => ((chars_array[chars] >> bit) & 1) as i32,
        None => 0,
    }
}
