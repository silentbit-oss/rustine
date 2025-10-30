use crate::*;

pub fn zbits(a: &mut Z) -> usize {
    if zzero(a) {
        return 1;
    }

    let mut i = a.used - 1;
    loop {
        let x = match &a.chars {
            Some(chars) => chars[i],
            None => break,
        };

        if x != 0 {
            a.used = i + 1;
            let mut i = i * 32;
            let mut x = x;
            while x != 0 {
                x >>= 1;
                i += 1;
            }
            return i;
        }

        if i == 0 {
            break;
        }
        i -= 1;
    }

    0 // fallback return, though the C version doesn't have one
}
