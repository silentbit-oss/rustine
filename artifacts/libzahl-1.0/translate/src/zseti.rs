use crate::*;

pub fn zseti(a: &mut Z, b: i64) {
    if b >= 0 {
        zsetu(a, b as u64);
    } else {
        zsetu(a, (-b) as u64);
        a.sign = -1;
    }
}
