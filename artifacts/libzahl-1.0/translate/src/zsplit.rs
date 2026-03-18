use crate::*;

pub fn zsplit(high: &mut z_t, low: &mut z_t, a: &z_t, delim: usize) {
    if zzero(a) {
        high[0].sign = 0;
        low[0].sign = 0;
        return;
    }

    // Need to handle the case where high and a are the same reference
    // Rust's borrow checker prevents overlapping mutable borrows, so we need to work around it
    if std::ptr::eq(high, a) {
        ztrunc(low, a, delim);
        zrsh(high, a, delim);
    } else {
        zrsh(high, a, delim);
        ztrunc(low, a, delim);
    }
}
