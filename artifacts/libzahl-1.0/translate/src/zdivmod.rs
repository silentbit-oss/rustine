use crate::*;

pub fn zdivmod(a: &mut Z, b: &mut Z, c: &Z, d: &Z) {
    extern "C" {
        fn longjmp(env: *mut jmp_buf, val: i32);
    }
    
    const EDOM: i32 = 33; // Domain error code, typically defined in errno.h

    let sign = zsignum(c) * zsignum(d);
    if sign == 0 {
        if zzero(c) {
            if zzero(d) {
                // EDOM error case
                *LIBZAHL_ERROR.lock().unwrap() = EDOM;
                unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
            } else {
                a.sign = 0;
                b.sign = 0;
            }
        } else {
            // EDOM error case
            *LIBZAHL_ERROR.lock().unwrap() = EDOM;
            unsafe { longjmp(&mut libzahl_jmp_buf, 1); }
        }
        return;
    }

    let cmpmag = zcmpmag(c, d);
    if cmpmag <= 0 {
        if cmpmag == 0 {
            zseti(a, sign.into());
            b.sign = 0;
            return;
        } else {
            if !std::ptr::eq(b, c) {
                zset(b, c);
            }
            b.sign = 1;
            a.sign = 0;
            return;
        }
    }

    let mut c_mut = Z { sign: c.sign, used: c.used, alloced: c.alloced, chars: c.chars.clone() };
    let mut d_mut = Z { sign: d.sign, used: d.used, alloced: d.alloced, chars: d.chars.clone() };
    let c_bits = zbits(&mut c_mut);
    let d_bits = zbits(&mut d_mut);
    let mut bit = c_bits - d_bits;

    {
        let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
        zlsh(&mut tmp_d, d, bit);
        tmp_d.sign = 1;

        let tmp_d_copy = Z { sign: tmp_d.sign, used: tmp_d.used, alloced: tmp_d.alloced, chars: tmp_d.chars.clone() };
        if zcmpmag(&tmp_d_copy, c) > 0 {
            zrsh(&mut tmp_d, &tmp_d_copy, 1);
            bit -= 1;
        }
    }

    {
        let mut tmp_a = libzahl_tmp_divmod_a.lock().unwrap();
        tmp_a.sign = 0;
        let mut tmp_b = libzahl_tmp_divmod_b.lock().unwrap();
        zabs(&mut tmp_b, c);

        if bit < 32 {
            loop {
                let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
                let tmp_d_copy = Z { sign: tmp_d.sign, used: tmp_d.used, alloced: tmp_d.alloced, chars: tmp_d.chars.clone() };
                let tmp_b_copy = Z { sign: tmp_b.sign, used: tmp_b.used, alloced: tmp_b.alloced, chars: tmp_b.chars.clone() };
                if zcmpmag(&tmp_d_copy, &tmp_b_copy) <= 0 {
                    zsub(&mut tmp_b, &tmp_b_copy, &tmp_d_copy);
                    let tmp_a_copy = Z { sign: tmp_a.sign, used: tmp_a.used, alloced: tmp_a.alloced, chars: tmp_a.chars.clone() };
                    zbset(&mut tmp_a, &tmp_a_copy, bit, 1);
                }
                drop(tmp_d);

                if bit == 0 || zzero(&tmp_b) {
                    break;
                }
                bit -= 1;

                let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
                let tmp_d_copy = Z { sign: tmp_d.sign, used: tmp_d.used, alloced: tmp_d.alloced, chars: tmp_d.chars.clone() };
                zrsh(&mut tmp_d, &tmp_d_copy, 1);
            }
        } else {
            let mut tmp_ds = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
            for i in 0..32 {
                let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
                let tmp_d_copy = Z { sign: tmp_d.sign, used: tmp_d.used, alloced: tmp_d.alloced, chars: tmp_d.chars.clone() };
                zrsh(&mut tmp_ds[i], &tmp_d_copy, i);
            }

            loop {
                for i in 0..32 {
                    let tmp_b_copy = Z { sign: tmp_b.sign, used: tmp_b.used, alloced: tmp_b.alloced, chars: tmp_b.chars.clone() };
                    if zcmpmag(&tmp_ds[i], &tmp_b_copy) <= 0 {
                        zsub(&mut tmp_b, &tmp_b_copy, &tmp_ds[i]);
                        let tmp_a_copy = Z { sign: tmp_a.sign, used: tmp_a.used, alloced: tmp_a.alloced, chars: tmp_a.chars.clone() };
                        zbset(&mut tmp_a, &tmp_a_copy, bit, 1);
                    }
                    if bit == 0 || zzero(&tmp_b) {
                        break;
                    }
                    bit -= 1;
                }

                if bit == 0 || zzero(&tmp_b) {
                    break;
                }

                let shift = if bit < 31 { bit } else { 31 };
                for i in (0..=shift).rev() {
                    let tmp_ds_copy = Z { sign: tmp_ds[i].sign, used: tmp_ds[i].used, alloced: tmp_ds[i].alloced, chars: tmp_ds[i].chars.clone() };
                    zrsh(&mut tmp_ds[i], &tmp_ds_copy, 32);
                }
            }
        }

        zswap(a, &mut tmp_a);
        zswap(b, &mut tmp_b);
        a.sign = sign;
    }
}
