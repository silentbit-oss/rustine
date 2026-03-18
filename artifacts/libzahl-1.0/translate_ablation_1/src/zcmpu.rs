use crate::*;
use lazy_static::lazy_static;


pub fn zcmpu(a: &z_t, b: u64) -> i32 {
    if b == 0 {
        return zsignum(a);
    }
    if zsignum(a) <= 0 {
        return -1;
    }
    {
        let mut tmp = libzahl_tmp_cmp.lock().unwrap();
        zsetu(&mut tmp, b);
    }
    let tmp = libzahl_tmp_cmp.lock().unwrap();
    zcmp(a, &tmp)
}
