use crate::*;

pub fn zdiv(a: &mut Z, b: &mut Z, c: &Z) {
    let mut tmp_div = libzahl_tmp_div.lock().unwrap();
    zdivmod(a, &mut tmp_div, b, c);
}
