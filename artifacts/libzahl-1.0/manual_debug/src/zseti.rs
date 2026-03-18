use crate::*;

pub fn zseti(a: &mut z_t, b: i64) {
    if b >= 0 {
        zsetu(a, b as u64);
    } else {
        zsetu(a, (-b) as u64);
        a[0].sign = -1;
    }
}
