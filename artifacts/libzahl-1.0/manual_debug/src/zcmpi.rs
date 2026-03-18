use crate::*;
use lazy_static::lazy_static;


pub fn zcmpi(a: &z_t, b: i64) -> i32 {
    if b == 0 {
        return zsignum(a);
    }
    if zzero(a) {
        return if b > 0 { -1 } else { (b < 0) as i32 };
    }
    {
        let mut tmp = libzahl_tmp_cmp.lock().unwrap();
        zseti(&mut tmp, b);
    }
    let tmp = libzahl_tmp_cmp.lock().unwrap();
    zcmp(a, &tmp)
}
