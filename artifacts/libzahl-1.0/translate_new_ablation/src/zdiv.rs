use crate::*;
use lazy_static::lazy_static;


pub fn zdiv(a: &mut z_t, b: &z_t, c: &z_t) {
    let mut libzahl_tmp_div = LIBZAHL_TMP_DIV.lock().unwrap();
    zdivmod(a, &mut libzahl_tmp_div, b, c);
}
