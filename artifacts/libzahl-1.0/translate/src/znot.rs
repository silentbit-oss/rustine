use crate::*;

pub fn znot(a: &mut Z, b: &Z) {
    if zzero(b) {
        a.sign = 0;
        return;
    }

    let mut temp_b = Z {
        sign: b.sign,
        used: b.used,
        alloced: b.alloced,
        chars: match &b.chars {
            Some(chars) => Some(chars.clone()),
            None => None,
        },
    };
    let mut bits = zbits(&mut temp_b);

    {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    }

    a.sign = -zsignum(a);
    
    if let Some(chars) = &mut a.chars {
        for n in (0..a.used).rev() {
            chars[n] = !chars[n];
        }
    }

    bits = bits & (32 - 1);
    if bits != 0 {
        if let Some(chars) = &mut a.chars {
            if a.used > 0 {
                let last = a.used - 1;
                chars[last] &= ((1 as u32) << bits) - 1;
            }
        }
    }

    while a.used > 0 {
        match &a.chars {
            Some(chars) if chars[a.used - 1] == 0 => a.used -= 1,
            _ => break,
        }
    }

    if a.used == 0 {
        a.sign = 0;
    }
}
