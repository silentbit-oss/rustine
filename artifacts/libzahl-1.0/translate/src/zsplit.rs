use crate::*;

pub fn zsplit(high: &mut Z, low: &mut Z, a: &Z, delim: usize) {
    if zzero(a) {
        high.sign = 0;
        low.sign = 0;
        return;
    }

    if std::ptr::eq(high, a) {
        ztrunc(low, a, delim);
        zrsh(high, a, delim);
    } else {
        zrsh(high, a, delim);
        ztrunc(low, a, delim);
    }
}
