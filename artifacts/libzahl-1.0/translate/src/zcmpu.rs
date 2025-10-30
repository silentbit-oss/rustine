use crate::*;

pub fn zcmpu(a: &Z, b: u64) -> i32 {
    if b == 0 {
        return zsignum(a);
    }
    if zsignum(a) <= 0 {
        return -1;
    }
    {
        let mut libzahl_tmp_cmp = LIBZAHL_TMP_CMP.lock().unwrap();
        zsetu(&mut libzahl_tmp_cmp, b);
    }
    let libzahl_tmp_cmp = LIBZAHL_TMP_CMP.lock().unwrap();
    zcmp(a, &libzahl_tmp_cmp)
}
