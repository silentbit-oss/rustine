use crate::*;

pub fn zcmpi(a: &Z, b: i64) -> i32 {
    if b == 0 {
        return zsignum(a);
    }
    if zzero(a) {
        return if b > 0 { -1 } else if b < 0 { 1 } else { 0 };
    }
    {
        let mut libzahl_tmp_cmp = LIBZAHL_TMP_CMP.lock().unwrap();
        zseti(&mut libzahl_tmp_cmp, b);
        zcmp(a, &libzahl_tmp_cmp)
    }
}
