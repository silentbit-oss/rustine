use crate::*;

pub fn zgcd(a: &mut Z, b: &Z, c: &Z) {
    let mut shifts = 0;
    let mut i = 0;
    let min;
    let mut uv;
    let mut bit;
    let neg;

    if zcmp(b, c) == 0 {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
        return;
    }

    if zzero(b) {
        if a as *const _ != c as *const _ {
            zset(a, c);
        }
        return;
    }

    if zzero(c) {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
        return;
    }

    {
        let mut u = libzahl_tmp_gcd_u.lock().unwrap();
        let mut v = libzahl_tmp_gcd_v.lock().unwrap();
        zabs(&mut u, b);
        zabs(&mut v, c);
        
        neg = (zsignum(b) < 0) && (zsignum(c) < 0);
        min = if u.used < v.used { u.used } else { v.used };

        'outer: for i in 0..min {
            uv = u.chars.as_ref().unwrap()[i] | v.chars.as_ref().unwrap()[i];
            bit = 1;
            while bit != 0 {
                if (uv & bit) != 0 {
                    break 'outer;
                }
                bit <<= 1;
                shifts += 1;
            }
        }

        for i in i..u.used {
            bit = 1;
            while bit != 0 {
                if (u.chars.as_ref().unwrap()[i] & bit) != 0 {
                    break;
                }
                bit <<= 1;
                shifts += 1;
            }
        }

        for i in i..v.used {
            bit = 1;
            while bit != 0 {
                if (v.chars.as_ref().unwrap()[i] & bit) != 0 {
                    break;
                }
                bit <<= 1;
                shifts += 1;
            }
        }

        let u_clone = Z {
            sign: u.sign,
            used: u.used,
            alloced: u.alloced,
            chars: u.chars.clone(),
        };
        zrsh(&mut u, &u_clone, shifts);
        
        let v_clone = Z {
            sign: v.sign,
            used: v.used,
            alloced: v.alloced,
            chars: v.chars.clone(),
        };
        zrsh(&mut v, &v_clone, shifts);
        
        let lsb_u = zlsb(&u);
        let u_clone = Z {
            sign: u.sign,
            used: u.used,
            alloced: u.alloced,
            chars: u.chars.clone(),
        };
        zrsh(&mut u, &u_clone, lsb_u);

        loop {
            let lsb_v = zlsb(&v);
            let v_clone = Z {
                sign: v.sign,
                used: v.used,
                alloced: v.alloced,
                chars: v.chars.clone(),
            };
            zrsh(&mut v, &v_clone, lsb_v);
            
            if zcmpmag(&u, &v) > 0 {
                zswap(&mut u, &mut v);
            }
            
            let v_clone = Z {
                sign: v.sign,
                used: v.used,
                alloced: v.alloced,
                chars: v.chars.clone(),
            };
            zsub_unsigned(&mut v, &v_clone, &u);
            
            if zzero(&v) {
                break;
            }
        }

        zlsh(a, &u, shifts);
        a.sign = if neg { -1 } else { 1 };
    }
}
