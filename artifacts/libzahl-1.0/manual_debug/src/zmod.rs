use crate::*;
use lazy_static::lazy_static;


pub fn zmod(a: &mut z_t, b: &mut z_t, c: &mut z_t) {
    let mut tmp = libzahl_tmp_mod.lock().unwrap();
    zdivmod(&mut tmp, a, b, c);
}
