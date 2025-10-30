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
        //let mut aa = a.clone();
        //let mut bb = b.clone();
        sign_a// * zcmpmag(&mut aa, &mut bb)
    }
}
