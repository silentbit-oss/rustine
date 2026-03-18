use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

pub fn zdivmod(a: &mut z_t, b: &mut z_t, c: &z_t, d: &z_t) {
    let sign = zsignum(c) * zsignum(d);
    if sign == 0 {
        if zzero(c) {
            if zzero(d) {
                LIBZAHL_ERROR.store(libc::EDOM as i32, Ordering::SeqCst);
                panic!("Division by zero"); // Simulate longjmp with panic
            } else {
                a[0].sign = 0;
                b[0].sign = 0;
            }
        } else {
            LIBZAHL_ERROR.store(libc::EDOM as i32, Ordering::SeqCst);
            panic!("Division by zero"); // Simulate longjmp with panic
        }
        return;
    }

    let cmpmag = zcmpmag(c, d);
    if cmpmag <= 0 {
        if cmpmag == 0 {
            zseti(a, sign as i64);
            b[0].sign = 0;
            return;
        } else {
            if b as *const _ != c as *const _ {
                zset(b, c);
            }
            b[0].sign = 1;
            a[0].sign = 0;
            return;
        }
    }

    let mut c_mut = [Z { sign: c[0].sign, used: c[0].used, alloced: c[0].alloced, chars: c[0].chars.clone() }];
    let mut d_mut = [Z { sign: d[0].sign, used: d[0].used, alloced: d[0].alloced, chars: d[0].chars.clone() }];
    let c_bits = zbits(&mut c_mut);
    let d_bits = zbits(&mut d_mut);
    let mut bit = c_bits - d_bits;

    {
        let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
        zlsh(&mut tmp_d, d, bit);
        tmp_d[0].sign = 1;

        let tmp_d_copy = [Z { sign: tmp_d[0].sign, used: tmp_d[0].used, alloced: tmp_d[0].alloced, chars: tmp_d[0].chars.clone() }];
        if zcmpmag(&tmp_d_copy, c) > 0 {
            zrsh(&mut tmp_d, &tmp_d_copy, 1);
            bit -= 1;
        }
    }

    {
        let mut tmp_a = libzahl_tmp_divmod_a.lock().unwrap();
        tmp_a[0].sign = 0;
    }

    {
        let mut tmp_b = libzahl_tmp_divmod_b.lock().unwrap();
        zabs(&mut tmp_b, c);
    }

    if bit < 32 {
        loop {
            let (should_break, new_bit) = {
                let mut tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
                let tmp_d_copy = [Z { sign: tmp_d[0].sign, used: tmp_d[0].used, alloced: tmp_d[0].alloced, chars: tmp_d[0].chars.clone() }];
                
                let mut tmp_b = libzahl_tmp_divmod_b.lock().unwrap();
                let tmp_b_copy = [Z { sign: tmp_b[0].sign, used: tmp_b[0].used, alloced: tmp_b[0].alloced, chars: tmp_b[0].chars.clone() }];
                
                let mut tmp_a = libzahl_tmp_divmod_a.lock().unwrap();
                let tmp_a_copy = [Z { sign: tmp_a[0].sign, used: tmp_a[0].used, alloced: tmp_a[0].alloced, chars: tmp_a[0].chars.clone() }];

                if zcmpmag(&tmp_d_copy, &tmp_b_copy) <= 0 {
                    zsub(&mut tmp_b, &tmp_b_copy, &tmp_d_copy);
                    zbset(&mut tmp_a, &tmp_a_copy, bit, 1);
                }

                if bit == 0 || zzero(&tmp_b_copy) {
                    (true, bit)
                } else {
                    zrsh(&mut tmp_d, &tmp_d_copy, 1);
                    (false, bit - 1)
                }
            };

            bit = new_bit;
            if should_break {
                break;
            }
        }
    } else {
        {
            let mut tmp_ds = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
            let tmp_d = libzahl_tmp_divmod_d.lock().unwrap();
            let tmp_d_copy = [Z { sign: tmp_d[0].sign, used: tmp_d[0].used, alloced: tmp_d[0].alloced, chars: tmp_d[0].chars.clone() }];
            
            for i in 0..32 {
                zrsh(&mut tmp_ds[i], &tmp_d_copy, i);
            }
        }

        loop {
            let (should_break, new_bit) = {
                let mut tmp_ds = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
                let tmp_ds_copies: Vec<z_t> = tmp_ds.iter().map(|z| [Z { sign: z[0].sign, used: z[0].used, alloced: z[0].alloced, chars: z[0].chars.clone() }]).collect();
                
                let mut tmp_b = libzahl_tmp_divmod_b.lock().unwrap();
                let tmp_b_copy = [Z { sign: tmp_b[0].sign, used: tmp_b[0].used, alloced: tmp_b[0].alloced, chars: tmp_b[0].chars.clone() }];
                
                let mut tmp_a = libzahl_tmp_divmod_a.lock().unwrap();
                let tmp_a_copy = [Z { sign: tmp_a[0].sign, used: tmp_a[0].used, alloced: tmp_a[0].alloced, chars: tmp_a[0].chars.clone() }];

                let mut break_flag = false;
                let mut new_bit = bit;

                for i in 0..32 {
                    if zcmpmag(&tmp_ds_copies[i], &tmp_b_copy) <= 0 {
                        zsub(&mut tmp_b, &tmp_b_copy, &tmp_ds_copies[i]);
                        zbset(&mut tmp_a, &tmp_a_copy, new_bit, 1);
                    }

                    if new_bit == 0 || zzero(&tmp_b_copy) {
                        break_flag = true;
                        break;
                    }
                    new_bit -= 1;
                }

                if !break_flag {
                    for i in (0..=if new_bit < 31 { new_bit } else { 31 }).rev() {
                        zrsh(&mut tmp_ds[i], &tmp_ds_copies[i], 32);
                    }
                }

                (break_flag, new_bit)
            };

            bit = new_bit;
            if should_break {
                break;
            }
        }
    }

    {
        let mut tmp_a = libzahl_tmp_divmod_a.lock().unwrap();
        let mut tmp_b = libzahl_tmp_divmod_b.lock().unwrap();
        zswap(a, &mut tmp_a);
        zswap(b, &mut tmp_b);
    }

    a[0].sign = sign;
}
