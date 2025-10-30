use crate::*;

pub fn zcmp(a: &Z, b: &Z) -> i32 {
    let sign_a = zsignum(a);
    let sign_b = zsignum(b);
    
    if sign_a != sign_b {
        return if sign_a < sign_b { -1 } else { 1 };
    }
    
    sign_a * zcmpmag(a, b)
}
