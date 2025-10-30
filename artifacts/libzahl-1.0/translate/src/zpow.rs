use crate::*;

const EDOM: i32 = 33; // Standard value for EDOM in most systems

pub fn zpow(a: &mut Z, b: &mut Z, c: &mut Z) {
    if zsignum(c) <= 0 {
        if zzero(c) {
            if zzero(b) {
                // Equivalent to longjmp error handling
                *LIBZAHL_ERROR.lock().unwrap() = EDOM;
                panic!("Domain error: 0^0 is undefined");
            }
            zsetu(a, 1);
        } else if zzero(b) {
            *LIBZAHL_ERROR.lock().unwrap() = EDOM;
            panic!("Domain error: 0^negative is undefined");
        } else {
            a.sign = 0;
        }
        return;
    } else if zzero(b) {
        a.sign = 0;
        return;
    }

    let bits = zbits(c);
    let n = bits >> 5;
    
    // Use blocks to limit mutable borrow scopes
    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zset(&mut *tmp_pow_b, b);
    }
    {
        let mut tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        zset(&mut *tmp_pow_c, c);
    }
    
    zsetu(a, 1);

    for i in 0..n {
        let x = {
            let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
            match &tmp_pow_c.chars {
                Some(chars) => chars[i],
                None => 0,
            }
        };

        for j in (0..32).rev() {
            if (x >> j) & 1 != 0 {
                let mut tmp = Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                };
                {
                    let tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                    zset(&mut tmp, &*tmp_pow_b);
                }
                let mut tmp_result = Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                };
                zset(&mut tmp_result, a);
                let mut tmp_copy = Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                };
                zset(&mut tmp_copy, &tmp_result);
                zmul(&mut tmp_result, &mut tmp_copy, &mut tmp);
                zset(a, &tmp_result);
            }
            {
                let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                let mut tmp = Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                };
                zset(&mut tmp, &*tmp_pow_b);
                zsqr(&mut *tmp_pow_b, &mut tmp);
            }
        }
    }

    let x = {
        let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        match &tmp_pow_c.chars {
            Some(chars) if n < chars.len() => chars[n],
            _ => 0,
        }
    };

    let mut remaining_x = x;
    while remaining_x != 0 {
        if remaining_x & 1 != 0 {
            let mut tmp = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            {
                let tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                zset(&mut tmp, &*tmp_pow_b);
            }
            let mut tmp_result = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp_result, a);
            let mut tmp_copy = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp_copy, &tmp_result);
            zmul(&mut tmp_result, &mut tmp_copy, &mut tmp);
            zset(a, &tmp_result);
        }
        {
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp, &*tmp_pow_b);
            zsqr(&mut *tmp_pow_b, &mut tmp);
        }
        remaining_x >>= 1;
    }
}
