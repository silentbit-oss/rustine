use crate::*;

pub fn zmod(a: &mut Z, b: &mut Z, c: &Z) {
    let mut tmp_mod = libzahl_tmp_mod.lock().unwrap();
    zdivmod(&mut tmp_mod, a, b, c);
}
