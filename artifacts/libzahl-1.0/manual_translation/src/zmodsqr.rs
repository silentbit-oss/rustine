use crate::*;
use lazy_static::lazy_static;

pub fn zmodsqr(a: &mut z_t, b: &mut z_t, c: &mut z_t) {
    //if std::ptr::eq(a, c) {
    //    let mut tmp = libzahl_tmp_modsqr.lock().unwrap();
    //    zset(&mut *tmp, c);
    //    zsqr(a, b);
    //    let mut tmp_ref = &*tmp;
    //    zmod(&mut a, &mut b, &mut tmp_ref);
    //} else {
        zsqr(a, b);
        zmod(a, b, c);
    //}
}
