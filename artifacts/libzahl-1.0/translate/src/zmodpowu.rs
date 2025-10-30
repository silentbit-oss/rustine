use crate::*;
use std::process;

const EDOM: i32 = 33; // Standard value for EDOM in most systems

pub fn zmodpowu(a: &mut Z, b: &mut Z, c: u64, d: &mut Z) {
    if c == 0 {
        if zzero(b) {
            *LIBZAHL_ERROR.lock().unwrap() = EDOM;
            process::abort(); // Replace longjmp with process termination (safe alternative)
        } else if zzero(d) {
            *LIBZAHL_ERROR.lock().unwrap() = EDOM;
            process::abort();
        } else {
            zsetu(a, 1);
        }
        return;
    } else if zzero(d) {
        *LIBZAHL_ERROR.lock().unwrap() = EDOM;
        process::abort();
    } else if zzero(b) {
        a.sign = 0;
        return;
    }

    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zmod(&mut *tmp_pow_b, b, d);
    }

    {
        let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
        zset(&mut *tmp_pow_d, d);
    }

    zsetu(a, 1);

    let mut c = c;
    while c != 0 {
        if c & 1 != 0 {
            let mut tmp_a = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp_a, a);
            
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
            zmodmul(a, &mut tmp_a, &mut *tmp_pow_b, &mut *tmp_pow_d);
        }

        {
            let mut tmp_pow_b_copy = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            {
                let tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
                zset(&mut tmp_pow_b_copy, &*tmp_pow_b);
            }
            
            let mut tmp_pow_d = libzahl_tmp_pow_d.lock().unwrap();
            zmodsqr(&mut *libzahl_tmp_pow_b.lock().unwrap(), &mut tmp_pow_b_copy, &mut *tmp_pow_d);
        }

        c >>= 1;
    }
}
