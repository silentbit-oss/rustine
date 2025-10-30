use crate::*;
use lazy_static::lazy_static;

pub fn zgcd(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut shifts = 0;
    let mut i = 0;
    let min;
    let mut uv;
    let mut bit;
    let neg;

    if zcmp(b, c) == 0 {
        if a.as_ptr() != b.as_ptr() {
            zset(a, b);
        }
        return;
    }

    if zzero(b) {
        if a.as_ptr() != c.as_ptr() {
            zset(a, c);
        }
        return;
    }

    if zzero(c) {
        if a.as_ptr() != b.as_ptr() {
            zset(a, b);
        }
        return;
    }

    {
        let mut tmp_u = libzahl_tmp_gcd_u.lock().unwrap();
        let mut tmp_v = libzahl_tmp_gcd_v.lock().unwrap();
        let mut tmp = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
        
        zabs(&mut tmp_u, b);
        zabs(&mut tmp_v, c);
        
        neg = (zsignum(b) < 0) && (zsignum(c) < 0);
        min = if tmp_u[0].used < tmp_v[0].used {
            tmp_u[0].used
        } else {
            tmp_v[0].used
        };

        let mut loop_done = false;
        while i < min && !loop_done {
            uv = tmp_u[0].chars.as_ref().unwrap()[i] | tmp_v[0].chars.as_ref().unwrap()[i];
            bit = 1;
            while bit != 0 {
                if (uv & bit) != 0 {
                    loop_done = true;
                    break;
                }
                bit <<= 1;
                shifts += 1;
            }
            if !loop_done {
                i += 1;
            }
        }

        while i < tmp_u[0].used && !loop_done {
            bit = 1;
            while bit != 0 {
                if (tmp_u[0].chars.as_ref().unwrap()[i] & bit) != 0 {
                    loop_done = true;
                    break;
                }
                bit <<= 1;
                shifts += 1;
            }
            if !loop_done {
                i += 1;
            }
        }

        while i < tmp_v[0].used && !loop_done {
            bit = 1;
            while bit != 0 {
                if (tmp_v[0].chars.as_ref().unwrap()[i] & bit) != 0 {
                    loop_done = true;
                    break;
                }
                bit <<= 1;
                shifts += 1;
            }
            if !loop_done {
                i += 1;
            }
        }

        zset(&mut tmp, &tmp_u);
        zrsh(&mut tmp_u, &tmp, shifts);
        zset(&mut tmp, &tmp_v);
        zrsh(&mut tmp_v, &tmp, shifts);
        
        let lsb = zlsb(&tmp_u);
        zset(&mut tmp, &tmp_u);
        zrsh(&mut tmp_u, &tmp, lsb);

        loop {
            let lsb_v = zlsb(&tmp_v);
            zset(&mut tmp, &tmp_v);
            zrsh(&mut tmp_v, &tmp, lsb_v);
            if zcmpmag(&mut tmp_u, &mut tmp_v) > 0 {
                zswap(&mut tmp_u, &mut tmp_v);
            }
            zset(&mut tmp, &tmp_v);
            zsub_unsigned(&mut tmp_v, &mut tmp, &mut tmp_u);
            if zzero(&tmp_v) {
                break;
            }
        }

        zlsh(a, &tmp_u, shifts);
        a[0].sign = if neg { -1 } else { 1 };
    }
}
