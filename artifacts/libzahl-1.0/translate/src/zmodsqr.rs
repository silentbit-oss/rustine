use crate::*;

pub fn zmodsqr(a: &mut Z, b: &mut Z, c: &Z) {
    if std::ptr::eq(a, c) {
        let mut tmp_modsqr = libzahl_tmp_modsqr.lock().unwrap();
        zset(&mut tmp_modsqr, c);
        zsqr(a, b);
        let tmp_a = a;
        zmod(tmp_a, b, &tmp_modsqr);
    } else {
        zsqr(a, b);
        let tmp_a = a;
        zmod(tmp_a, b, c);
    }
}
