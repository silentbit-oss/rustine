use crate::*;
use lazy_static::lazy_static;
use std::process;
use std::sync::atomic::Ordering;pub fn zpow(a: &mut z_t, b: &mut z_t, c: &mut z_t) {
    if zsignum(c) <= 0 {
        if zzero(c) {
            if zzero(b) {
                LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
                panic!("Domain error: 0^0 is undefined");
            }
            zsetu(a, 1);
        } else {
            if zzero(b) {
                LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
                panic!("Domain error: 0^negative is undefined");
            } else {
                a[0].sign = 0;
            }
        }
        return;
    } else if zzero(b) {
        a[0].sign = 0;
        return;
    }

    let bits = zbits(c);
    let n = bits >> 5;

    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zset(&mut tmp_pow_b, b);
    }

    {
        let mut tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        zset(&mut tmp_pow_c, c);
    }

    zsetu(a, 1);

    for i in 0..n {
        let x = {
            let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
            tmp_pow_c[0].chars.as_ref().unwrap()[i]
        };

        for j in (0..32).rev() {
            if x & (1 << j) != 0 {
                let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                let mut tmp_a = [Z {
                    sign: a[0].sign,
                    used: a[0].used,
                    alloced: a[0].alloced,
                    chars: a[0].chars.clone(),
                }];
                zmul(&mut tmp_a, a, &mut tmp_pow_b);
                *a = tmp_a;
            }
            
            {
                let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                let mut tmp = [Z {
                    sign: tmp_pow_b[0].sign,
                    used: tmp_pow_b[0].used,
                    alloced: tmp_pow_b[0].alloced,
                    chars: tmp_pow_b[0].chars.clone(),
                }];
                zsqr(&mut tmp, &mut tmp_pow_b);
                *tmp_pow_b = tmp;
            }
        }
    }

    let mut x = {
        let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        tmp_pow_c[0].chars.as_ref().unwrap()[n]
    };

    while x != 0 {
        if x & 1 != 0 {
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp_a = [Z {
                sign: a[0].sign,
                used: a[0].used,
                alloced: a[0].alloced,
                chars: a[0].chars.clone(),
            }];
            zmul(&mut tmp_a, a, &mut tmp_pow_b);
            *a = tmp_a;
        }
        
        {
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp = [Z {
                sign: tmp_pow_b[0].sign,
                used: tmp_pow_b[0].used,
                alloced: tmp_pow_b[0].alloced,
                chars: tmp_pow_b[0].chars.clone(),
            }];
            zsqr(&mut tmp, &mut tmp_pow_b);
            *tmp_pow_b = tmp;
        }
        x >>= 1;
    }
}

// Constants needed for the error handling
const EDOM: i32 = 33; // Domain error code
