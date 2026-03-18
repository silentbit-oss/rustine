use crate::*;
use std::ptr;

pub fn zmul(a: &mut z_t, b: &mut z_t, c: &mut z_t) {
    let mut m: usize;
    let mut m2: usize;
    let mut z0: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut z1: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut z2: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut b_high: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut b_low: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut c_high: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    let mut c_low: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    }];
    
    let b_sign = zsignum(b);
    let c_sign = zsignum(c);
    
    if b_sign == 0 || c_sign == 0 {
        a[0].sign = 0;
        return;
    }
    
    m = zbits(b);
    m2 = if ptr::eq(b, c) { m } else { zbits(c) };
    
    if (m + m2) <= 32 {
        while a[0].alloced < 1 {
            libzahl_realloc(a, 1);
        }
        a[0].used = 1;
        a[0].chars.as_mut().unwrap()[0] = b[0].chars.as_ref().unwrap()[0] * c[0].chars.as_ref().unwrap()[0];
        a[0].sign = b_sign * c_sign;
        return;
    }
    
    b[0].sign = 1;
    c[0].sign = 1;
    m = if m > m2 { m } else { m2 };
    m2 = m >> 1;
    
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
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zadd(&mut temp, &b_low, &b_high);
        zadd(&mut b_low, &temp, &[Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
        zfree(&mut temp);
    }
    
    {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zadd(&mut temp, &c_low, &c_high);
        zadd(&mut c_low, &temp, &[Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
        zfree(&mut temp);
    }
    
    zmul(&mut z1, &mut b_low, &mut c_low);
    
    {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zsub(&mut temp, &z1, &z0);
        zsub(&mut z1, &temp, &z2);
        zfree(&mut temp);
    }
    
    {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zlsh(&mut temp, &z1, m2);
        zadd(&mut z1, &temp, &[Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
        zfree(&mut temp);
    }
    
    m2 <<= 1;
    
    {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zlsh(&mut temp, &z2, m2);
        zadd(&mut z2, &temp, &[Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
        zfree(&mut temp);
    }
    
    {
        let mut temp = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zinit(&mut temp);
        zadd(&mut temp, &z2, &z1);
        zadd(a, &temp, &z0);
        zfree(&mut temp);
    }
    
    zfree(&mut z0);
    zfree(&mut z1);
    zfree(&mut z2);
    zfree(&mut b_high);
    zfree(&mut b_low);
    zfree(&mut c_high);
    zfree(&mut c_low);
    
    b[0].sign = b_sign;
    c[0].sign = c_sign;
    a[0].sign = b_sign * c_sign;
}
