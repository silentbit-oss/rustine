use crate::*;
use lazy_static::lazy_static;

pub fn zmodmul(a: &mut z_t, b: &mut z_t, c: &mut z_t, d: &mut z_t) {
    if a as *const _ == d as *const _ {
        // Need to handle the case where a and d are the same
        let tmp = {
            let mut tmp = libzahl_tmp_modmul.lock().unwrap();
            zset(&mut *tmp, d);
            tmp
        };
        zmul(a, b, c);
        {
            let mut tmp = libzahl_tmp_modmul.lock().unwrap();
            let mut tmp_a = [Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            }];
            zset(&mut tmp_a, a);
            let mut tmp_b = [Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            }];
            zset(&mut tmp_b, &tmp_a);
            zmod(&mut tmp_a, &mut tmp_b, &mut *tmp);
            zset(a, &tmp_a);
        }
    } else {
        zmul(a, b, c);
        let mut tmp_a = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zset(&mut tmp_a, a);
        let mut tmp_b = [Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }];
        zset(&mut tmp_b, &tmp_a);
        zmod(&mut tmp_a, &mut tmp_b, d);
        zset(a, &tmp_a);
    }
}
