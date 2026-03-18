use crate::*;

pub fn zcmp(a: &z_t, b: &z_t) -> i32 {
    let sign_a = zsignum(a);
    let sign_b = zsignum(b);
    
    if sign_a != sign_b {
        if sign_a < sign_b {
            -1
        } else {
            (sign_a > sign_b) as i32
        }
    } else {
        sign_a * zcmpmag(a, b)
    }
}
