use crate::*;

pub fn zand(a: &mut Z, b: &Z, c: &Z) {
    if zzero(b) || zzero(c) {
        a.sign = 0;
        return;
    }

    let n = if b.used < c.used { b.used } else { c.used };
    let mut found_n = Option::None;

    for i in (0..n).rev() {
        if let (Some(b_chars), Some(c_chars)) = (&b.chars, &c.chars) {
            if (b_chars[i] & c_chars[i]) != 0 {
                found_n = Some(i + 1);
                break;
            }
        }
    }

    let n = match found_n {
        Some(n) => n,
        None => {
            a.sign = 0;
            return;
        }
    };

    a.used = n;

    if std::ptr::eq(a, b) {
        if let (Some(a_chars), Some(c_chars)) = (&mut a.chars, &c.chars) {
            for i in 0..n {
                a_chars[i] &= c_chars[i];
            }
        }
    } else if std::ptr::eq(a, c) {
        if let (Some(a_chars), Some(b_chars)) = (&mut a.chars, &b.chars) {
            for i in 0..n {
                a_chars[i] &= b_chars[i];
            }
        }
    } else {
        if a.alloced < a.used {
            libzahl_realloc(a, a.used);
        }

        if let (Some(a_chars), Some(b_chars), Some(c_chars)) = (&mut a.chars, &b.chars, &c.chars) {
            a_chars[..n].copy_from_slice(&c_chars[..n]);
            for i in 0..n {
                a_chars[i] &= b_chars[i];
            }
        }
    }

    a.sign = (((zsignum(b) > 0) || (zsignum(c) > 0)) as i32) * 2 - 1;
}
