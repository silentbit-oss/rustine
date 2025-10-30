use crate::*;
use lazy_static::lazy_static;
use std::process;
use std::sync::atomic::Ordering;pub fn zmodpowu(a: &mut z_t, b: &mut z_t, c: u64, d: &mut z_t) {
    if c == 0 {
        if zzero(b) {
            LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
            process::exit(1); // Simulate longjmp behavior with process exit
        } else if zzero(d) {
            LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
            process::exit(1);
        } else {
            zsetu(a, 1);
        }
        return;
    } else if zzero(d) {
        LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
        process::exit(1);
    } else if zzero(b) {
        a[0].sign = 0;
        return;
    }

    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zmod(&mut tmp_pow_b, b, d);
    }

    {
        let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
        zset(&mut tmp_pow_d, d);
    }

    zsetu(a, 1);

    let mut c = c;
    while c != 0 {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();

        if c & 1 != 0 {
            let mut tmp_a = [Z {
                sign: a[0].sign,
                used: a[0].used,
                alloced: a[0].alloced,
                chars: a[0].chars.clone(),
            }];
            zmodmul(&mut tmp_a, a, &mut tmp_pow_b, &mut tmp_pow_d);
            *a = tmp_a;
        }
        
        let mut tmp_pow_b_copy = [Z {
            sign: tmp_pow_b[0].sign,
            used: tmp_pow_b[0].used,
            alloced: tmp_pow_b[0].alloced,
            chars: tmp_pow_b[0].chars.clone(),
        }];
        zmodsqr(&mut tmp_pow_b_copy, &mut tmp_pow_b, &mut tmp_pow_d);
        *tmp_pow_b = tmp_pow_b_copy;

        c >>= 1;
    }
}

// Constants
const EDOM: i32 = 1; // Placeholder for the actual EDOM value
