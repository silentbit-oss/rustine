use crate::*;
use std::process::abort;
use std::sync::atomic::Ordering;pub fn zpowu(a: &mut z_t, b: &mut z_t, c: u64) {
    if c == 0 {
        if zzero(b) {
            // In Rust, we can't use longjmp, so we'll set the error and abort
            LIBZAHL_ERROR.store(EDOM, Ordering::SeqCst);
            abort();
        }
        zsetu(a, 1);
        return;
    } else if zzero(b) {
        a[0].sign = 0;
        return;
    }

    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zset(&mut tmp_pow_b, b);
    }

    zsetu(a, 1);

    let mut c = c;
    while c != 0 {
        if c & 1 != 0 {
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
        c >>= 1;
    }
}

// EDOM should be defined somewhere in your code, typically matching the C value
const EDOM: i32 = 33;  // Standard C value for domain error
