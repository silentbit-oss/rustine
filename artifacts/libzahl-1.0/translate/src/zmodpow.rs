use crate::*;
extern "C" {
    fn longjmp(env: *mut crate::globals::jmp_buf, val: i32) -> !;
}

pub fn zmodpow(a: &mut Z, b: &mut Z, c: &mut Z, d: &mut Z) {
    let mut i: usize;
    let mut j: usize;
    let mut n: usize;
    let mut bits: usize;
    let mut x: ZahlCharT;

    const EDOM: i32 = 33;

    if zsignum(c) <= 0 {
        if zzero(c) {
            if zzero(b) {
                *LIBZAHL_ERROR.lock().unwrap() = EDOM;
                unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
            } else if zzero(d) {
                *LIBZAHL_ERROR.lock().unwrap() = EDOM;
                unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
            }
            zsetu(a, 1);
        } else if zzero(b) || zzero(d) {
            *LIBZAHL_ERROR.lock().unwrap() = EDOM;
            unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
        } else {
            a.sign = 0;
        }
        return;
    } else if zzero(d) {
        *LIBZAHL_ERROR.lock().unwrap() = EDOM;
        unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
    } else if zzero(b) {
        a.sign = 0;
        return;
    }

    bits = zbits(c);
    n = bits >> 5;

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
        {
            let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
            x = tmp_pow_c.chars.as_ref().unwrap()[i];
        }

        for j in (0..32).rev() {
            if x & 1 != 0 {
                let mut tmp_pow_b_guard = libzahl_tmp_pow_b.lock().unwrap();
                let mut tmp_pow_d_guard = libzahl_tmp_pow_d.lock().unwrap();
                let mut temp_a = Z { sign: 0, used: 0, alloced: 0, chars: None };
                zset(&mut temp_a, a);
                zmodmul(a, &mut temp_a, &mut *tmp_pow_b_guard, &mut *tmp_pow_d_guard);
            }
            
            {
                let mut tmp_pow_b_guard = libzahl_tmp_pow_b.lock().unwrap();
                let tmp_pow_d_guard = libzahl_tmp_pow_d.lock().unwrap();
                let mut temp_b = Z { sign: 0, used: 0, alloced: 0, chars: None };
                zset(&mut temp_b, &*tmp_pow_b_guard);
                zmodsqr(&mut *tmp_pow_b_guard, &mut temp_b, &*tmp_pow_d_guard);
            }
            x >>= 1;
        }
    }

    {
        let tmp_pow_c = libzahl_tmp_pow_c.lock().unwrap();
        x = tmp_pow_c.chars.as_ref().unwrap()[n];
    }

    while x != 0 {
        if x & 1 != 0 {
            let mut tmp_pow_b_guard = libzahl_tmp_pow_b.lock().unwrap();
            let mut tmp_pow_d_guard = libzahl_tmp_pow_d.lock().unwrap();
            let mut temp_a = Z { sign: 0, used: 0, alloced: 0, chars: None };
            zset(&mut temp_a, a);
            zmodmul(a, &mut temp_a, &mut *tmp_pow_b_guard, &mut *tmp_pow_d_guard);
        }
        
        {
            let mut tmp_pow_b_guard = libzahl_tmp_pow_b.lock().unwrap();
            let tmp_pow_d_guard = libzahl_tmp_pow_d.lock().unwrap();
            let mut temp_b = Z { sign: 0, used: 0, alloced: 0, chars: None };
            zset(&mut temp_b, &*tmp_pow_b_guard);
            zmodsqr(&mut *tmp_pow_b_guard, &mut temp_b, &*tmp_pow_d_guard);
        }
        x >>= 1;
    }
}
