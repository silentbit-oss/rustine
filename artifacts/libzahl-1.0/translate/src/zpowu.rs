use crate::*;

pub fn zpowu(a: &mut Z, b: &mut Z, c: u64) {
    if c == 0 {
        if zzero(b) {
            // In Rust, we'll use panic instead of longjmp for error handling
            panic!("Domain error: 0^0 is undefined");
        }
        zsetu(a, 1);
        return;
    } else if zzero(b) {
        a.sign = 0;
        return;
    }

    // Use a block to limit the scope of the mutable borrow
    {
        let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
        zset(&mut *tmp_pow_b, b);
    }

    zsetu(a, 1);
    let mut remaining_c = c;

    while remaining_c != 0 {
        // Use nested blocks to manage mutable borrows
        {
            let mut tmp_pow_b = libzahl_tmp_pow_b.lock().unwrap();
            if remaining_c & 1 != 0 {
                let mut tmp = Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                };
                zset(&mut tmp, a);
                zmul(a, &mut tmp, &mut *tmp_pow_b);
            }
            let mut tmp_sqr = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zset(&mut tmp_sqr, &*tmp_pow_b);
            zsqr(&mut *tmp_pow_b, &mut tmp_sqr);
        }
        remaining_c >>= 1;
    }
}
