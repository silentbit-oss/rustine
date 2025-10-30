use crate::*;

pub fn zmodmul(a: &mut Z, b: &mut Z, c: &mut Z, d: &mut Z) {
    if std::ptr::eq(a, d) {
        let mut tmp_modmul = LIBZAHL_TMP_MODMUL.lock().unwrap();
        zset(&mut *tmp_modmul, d);
        zmul(a, b, c);
        let tmp = &*tmp_modmul;
        let mut result = Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        };
        zmod(&mut result, a, tmp);
        *a = result;
    } else {
        zmul(a, b, c);
        let tmp_d = d;
        let mut result = Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        };
        zmod(&mut result, a, tmp_d);
        *a = result;
    }
}
