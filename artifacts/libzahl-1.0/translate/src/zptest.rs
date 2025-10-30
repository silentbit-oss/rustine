use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;

pub enum Zprimality {
    PRIME,
    NONPRIME,
}

pub fn helper_zptest_1(
    i_ref: &mut usize,
    witness: Option<&mut Z>,
    n: &mut Z,
    r: usize,
) -> Zprimality {
    let mut i = *i_ref;
    
    {
        let mut a_guard = libzahl_tmp_ptest_a.lock().unwrap();
        let mut n4_guard = LIBZAHL_TMP_PTEST_N4.lock().unwrap();
        let const2_guard = LIBZAHL_CONST_2.lock().unwrap();
        
        zrand(&mut *a_guard, Zranddev::FastRandom, Zranddist::Uniform, &mut *n4_guard);
        let a_copy = Z {
            sign: a_guard.sign,
            used: a_guard.used,
            alloced: a_guard.alloced,
            chars: a_guard.chars.clone(),
        };
        zadd_unsigned(&mut *a_guard, &a_copy, &*const2_guard);
    }

    {
        let mut x_guard = LIBZAHL_TMP_PTEST_X.lock().unwrap();
        let mut a_guard = libzahl_tmp_ptest_a.lock().unwrap();
        let mut d_guard = LIBZAHL_TMP_PTEST_D.lock().unwrap();
        
        zmodpow(&mut *x_guard, &mut *a_guard, &mut *d_guard, n);
    }

    {
        let x_guard = LIBZAHL_TMP_PTEST_X.lock().unwrap();
        let const1_guard = libzahl_const_1.lock().unwrap();
        let n1_guard = libzahl_tmp_ptest_n1.lock().unwrap();
        
        if zcmp(&*x_guard, &*const1_guard) == 0 || zcmp(&*x_guard, &*n1_guard) == 0 {
            *i_ref = i;
            return Zprimality::PRIME;
        }
    }

    for _ in 1..r {
        {
            let mut x_guard = LIBZAHL_TMP_PTEST_X.lock().unwrap();
            let mut x_copy = Z {
                sign: x_guard.sign,
                used: x_guard.used,
                alloced: x_guard.alloced,
                chars: x_guard.chars.clone(),
            };
            zsqr(&mut *x_guard, &mut x_copy);
            let mut x_copy = Z {
                sign: x_guard.sign,
                used: x_guard.used,
                alloced: x_guard.alloced,
                chars: x_guard.chars.clone(),
            };
            zmod(&mut *x_guard, &mut x_copy, n);
        }

        {
            let x_guard = LIBZAHL_TMP_PTEST_X.lock().unwrap();
            let const1_guard = libzahl_const_1.lock().unwrap();
            
            if zcmp(&*x_guard, &*const1_guard) == 0 {
                if let Some(witness) = witness {
                    let mut a_guard = libzahl_tmp_ptest_a.lock().unwrap();
                    zswap(witness, &mut *a_guard);
                }
                *i_ref = i;
                return Zprimality::NONPRIME;
            }
        }

        {
            let x_guard = LIBZAHL_TMP_PTEST_X.lock().unwrap();
            let n1_guard = libzahl_tmp_ptest_n1.lock().unwrap();
            
            if zcmp(&*x_guard, &*n1_guard) == 0 {
                break;
            }
        }
        i += 1;
    }

    if i == r {
        if let Some(witness) = witness {
            let mut a_guard = libzahl_tmp_ptest_a.lock().unwrap();
            zswap(witness, &mut *a_guard);
        }
        *i_ref = i;
        return Zprimality::NONPRIME;
    }

    *i_ref = i;
    Zprimality::PRIME
}


pub fn zptest(witness: Option<&mut Z>, n: &mut Z, t: i32) -> Zprimality {
    let mut i = 0;
    let mut r;

    // Check if n <= 3
    if zcmpu(n, 3) <= 0 {
        if zcmpu(n, 1) <= 0 {
            if let Some(witness) = witness {
                if !std::ptr::eq(witness, n) {
                    zset(witness, n);
                }
            }
            return Zprimality::NONPRIME;
        } else {
            return Zprimality::PRIME;
        }
    }

    // Check if n is even
    if zeven(n) {
        if let Some(witness) = witness {
            if !std::ptr::eq(witness, n) {
                zset(witness, n);
            }
        }
        return Zprimality::NONPRIME;
    }

    // Perform the primality test
    {
        let mut n1_guard = libzahl_tmp_ptest_n1.lock().unwrap();
        let const1_guard = libzahl_const_1.lock().unwrap();
        zsub_unsigned(&mut *n1_guard, n, &*const1_guard);
    }

    {
        let mut n4_guard = LIBZAHL_TMP_PTEST_N4.lock().unwrap();
        let const4_guard = libzahl_const_4.lock().unwrap();
        zsub_unsigned(&mut *n4_guard, n, &*const4_guard);
    }

    {
        let n1_guard = libzahl_tmp_ptest_n1.lock().unwrap();
        r = zlsb(&*n1_guard);
    }

    {
        let mut d_guard = LIBZAHL_TMP_PTEST_D.lock().unwrap();
        let n1_guard = libzahl_tmp_ptest_n1.lock().unwrap();
        zrsh(&mut *d_guard, &*n1_guard, r);
    }

    let mut remaining_tests = t;
let mut witness_ref = witness;           // Option<&mut Z>

while remaining_tests > 0 {

    let result = helper_zptest_1(&mut i, witness_ref.take(), n, r);

    if matches!(result, Zprimality::NONPRIME) {
        return Zprimality::NONPRIME;
    }
    remaining_tests -= 1;
}

Zprimality::PRIME
}
