use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;

pub fn zptest(witness: Option<&mut z_t>, n: &mut z_t, t: i32) -> ZPrimality {
    // Check if n <= 3
    if zcmpu(n, 3) <= 0 {
        if zcmpu(n, 1) <= 0 {
            if let Some(wit) = witness {
                loop {
                    if zcmp(wit, n) != 0 {
                        zset(wit, n);
                    }
                    break;
                }
            }
            return ZPrimality::NONPRIME;
        } else {
            return ZPrimality::PRIME;
        }
    }

    // Check if n is even using zlsb (returns 0 for odd, >0 for even)
    if zlsb(n) > 0 {
        if let Some(wit) = witness {
            loop {
                if zcmp(wit, n) != 0 {
                    zset(wit, n);
                }
                break;
            }
        }
        return ZPrimality::NONPRIME;
    }

    // Initialize temporary variables
    let mut tmp_n1 = libzahl_tmp_ptest_n1.lock().unwrap();
    let mut tmp_n4 = libzahl_tmp_ptest_n4.lock().unwrap();
    let mut tmp_d = libzahl_tmp_ptest_d.lock().unwrap();
    let mut tmp_a = libzahl_tmp_ptest_a.lock().unwrap();
    let mut tmp_x = LIBZAHL_TMP_PTEST_X.lock().unwrap();

    zsub_unsigned(&mut tmp_n1, n, &libzahl_const_1.lock().unwrap());
    zsub_unsigned(&mut tmp_n4, n, &libzahl_const_4.lock().unwrap());
    let r = zlsb(&tmp_n1);
    zrsh(&mut tmp_d, &tmp_n1, r);

    let mut t = t;
    while t > 0 {
        t -= 1;

        zrand(&mut tmp_a, Zranddev::FAST_RANDOM, Zranddist::UNIFORM, &mut tmp_n4);
        // Use tmp_x as temporary storage to avoid borrow conflict
        zset(&mut tmp_x, &tmp_a);
        zadd_unsigned(&mut tmp_a, &tmp_x, &libzahl_const_2.lock().unwrap());
        zmodpow(&mut tmp_x, &mut tmp_a, &mut tmp_d, n);

        if zcmp(&tmp_x, &libzahl_const_1.lock().unwrap()) == 0 ||
           zcmp(&tmp_x, &tmp_n1) == 0 {
            continue;
        }

        let mut i = 1;
        while i < r {
            // Create a temporary variable for the source
            let mut tmp_src = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zset(&mut tmp_src, &tmp_x);
            zsqr(&mut tmp_x, &mut tmp_src);
            
            zset(&mut tmp_src, &tmp_x);
            zmod(&mut tmp_x, &mut tmp_src, n);

            if zcmp(&tmp_x, &libzahl_const_1.lock().unwrap()) == 0 {
                if let Some(wit) = witness {
                    zswap(wit, &mut tmp_a);
                }
                return ZPrimality::NONPRIME;
            }

            if zcmp(&tmp_x, &tmp_n1) == 0 {
                break;
            }

            i += 1;
        }

        if i == r {
            if let Some(wit) = witness {
                zswap(wit, &mut tmp_a);
            }
            return ZPrimality::NONPRIME;
        }
    }

    ZPrimality::PROBABLY_PRIME
}
