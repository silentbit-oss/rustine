use crate::*;
use lazy_static::lazy_static;
use std::process;
use std::sync::atomic::Ordering;pub fn zmodpow(a: &mut z_t, b: &mut z_t, c: &mut z_t, d: &mut z_t) {
    if zsignum(c) <= 0 {
        if zzero(c) {
            if zzero(b) {
                LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
                process::exit(1); // Simulate longjmp behavior
            } else if zzero(d) {
                LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
                process::exit(1);
            }
            zsetu(a, 1);
        } else if zzero(b) || zzero(d) {
            LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
            process::exit(1);
        } else {
            a[0].sign = 0;
        }
        return;
    } else if zzero(d) {
        LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
        process::exit(1);
    } else if zzero(b) {
        a[0].sign = 0;
        return;
    }

    let bits = zbits(c);
    let n = bits >> 5;

    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zmod(&mut *tmp_pow_b, b, d);
    }

    {
        let mut tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        zset(&mut *tmp_pow_c, c);
    }

    {
        let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
        zset(&mut *tmp_pow_d, d);
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
                let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
                let mut tmp_a = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
                zset(&mut tmp_a, a);
                zmodmul(a, &mut tmp_a, &mut *tmp_pow_b, &mut *tmp_pow_d);
            }

            {
                let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
                let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                let mut tmp_b = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
                zset(&mut tmp_b, &*tmp_pow_b);
                zmodsqr(&mut *tmp_pow_b, &mut tmp_b, &mut *tmp_pow_d);
            }
        }
    }

    let x = {
        let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        tmp_pow_c[0].chars.as_ref().unwrap()[n]
    };

    let mut remaining_x = x;
    while remaining_x != 0 {
        if remaining_x & 1 != 0 {
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
            let mut tmp_a = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zset(&mut tmp_a, a);
            zmodmul(a, &mut tmp_a, &mut *tmp_pow_b, &mut *tmp_pow_d);
        }

        {
            let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp_b = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zset(&mut tmp_b, &*tmp_pow_b);
            zmodsqr(&mut *tmp_pow_b, &mut tmp_b, &mut *tmp_pow_d);
        }

        remaining_x >>= 1;
    }
}

// Constants
const EDOM: i32 = 33; // Domain error code
