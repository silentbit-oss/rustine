use crate::*;

pub fn zmul(a: &mut Z, b: &mut Z, c: &mut Z) {
    let b_sign = zsignum(b);
    let c_sign = zsignum(c);
    
    if b_sign == 0 || c_sign == 0 {
        a.sign = 0;
        return;
    }
    
    let m = zbits(b);
    let m2 = if b as *const _ == c as *const _ { m } else { zbits(c) };
    
    if (m + m2) <= 32 {
        if a.alloced < 1 {
            libzahl_realloc(a, 1);
        }
        a.used = 1;
        if let (Some(b_chars), Some(c_chars), Some(a_chars)) = (&b.chars, &c.chars, &mut a.chars) {
            a_chars[0] = b_chars[0] * c_chars[0];
        }
        a.sign = b_sign * c_sign;
        return;
    }
    
    b.sign = 1;
    c.sign = 1;
    
    let m = if m > m2 { m } else { m2 };
    let mut m2 = m >> 1;
    
    let mut z0 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut z1 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut z2 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut b_high = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut b_low = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut c_high = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut c_low = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    
    zinit(&mut z0);
    zinit(&mut z1);
    zinit(&mut z2);
    zinit(&mut b_high);
    zinit(&mut b_low);
    zinit(&mut c_high);
    zinit(&mut c_low);
    
    zsplit(&mut b_high, &mut b_low, b, m2);
    zsplit(&mut c_high, &mut c_low, c, m2);
    
    zmul(&mut z0, &mut b_low, &mut c_low);
    zmul(&mut z2, &mut b_high, &mut c_high);
    
    {
        let mut b_low_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut b_low_val);
        zadd(&mut b_low_val, &b_low, &b_high);
        zadd(&mut b_low, &b_low_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    {
        let mut c_low_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut c_low_val);
        zadd(&mut c_low_val, &c_low, &c_high);
        zadd(&mut c_low, &c_low_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    
    zmul(&mut z1, &mut b_low, &mut c_low);
    {
        let mut z1_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut z1_val);
        zsub(&mut z1_val, &z1, &z0);
        zsub(&mut z1, &z1_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    {
        let mut z1_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut z1_val);
        zsub(&mut z1_val, &z1, &z2);
        zsub(&mut z1, &z1_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    
    {
        let mut z1_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut z1_val);
        zlsh(&mut z1_val, &z1, m2);
        zlsh(&mut z1, &z1_val, 0);
    }
    m2 <<= 1;
    {
        let mut z2_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut z2_val);
        zlsh(&mut z2_val, &z2, m2);
        zlsh(&mut z2, &z2_val, 0);
    }
    
    {
        let mut z2_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut z2_val);
        zadd(&mut z2_val, &z2, &z1);
        zadd(a, &z2_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    {
        let mut a_val = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
        zinit(&mut a_val);
        zadd(&mut a_val, a, &z0);
        zadd(a, &a_val, &Z { sign: 0, used: 0, alloced: 0, chars: Option::None });
    }
    
    zfree(&mut z0);
    zfree(&mut z1);
    zfree(&mut z2);
    zfree(&mut b_high);
    zfree(&mut b_low);
    zfree(&mut c_high);
    zfree(&mut c_low);
    
    b.sign = b_sign;
    c.sign = c_sign;
    a.sign = b_sign * c_sign;
}
