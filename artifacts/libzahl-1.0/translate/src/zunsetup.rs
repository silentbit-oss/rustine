use crate::*;

pub fn helper_zunsetup_1(i_ref: &mut usize) {
    let mut i = *i_ref;
    unsafe {
        libzahl_set_up = 0;
    }

    // Free all the temporary Z structs' chars fields
    let mut free_chars = |z: &std::sync::Mutex<Z>| {
        let mut z = z.lock().unwrap();
        z.chars = Option::None;
    };

    free_chars(&LIBZAHL_TMP_CMP);
    free_chars(&LIBZAHL_TMP_STR_NUM);
    free_chars(&libzahl_tmp_str_mag);
    free_chars(&libzahl_tmp_str_div);
    free_chars(&LIBZAHL_TMP_STR_REM);
    free_chars(&libzahl_tmp_gcd_u);
    free_chars(&libzahl_tmp_gcd_v);
    free_chars(&libzahl_tmp_sub);
    free_chars(&LIBZAHL_TMP_MODMUL);
    free_chars(&libzahl_tmp_div);
    free_chars(&libzahl_tmp_mod);
    free_chars(&libzahl_tmp_pow_b);
    free_chars(&libzahl_tmp_pow_c);
    free_chars(&libzahl_tmp_pow_d);
    free_chars(&libzahl_tmp_modsqr);
    free_chars(&libzahl_tmp_divmod_a);
    free_chars(&libzahl_tmp_divmod_b);
    free_chars(&libzahl_tmp_divmod_d);
    free_chars(&LIBZAHL_TMP_PTEST_X);
    free_chars(&libzahl_tmp_ptest_a);
    free_chars(&LIBZAHL_TMP_PTEST_D);
    free_chars(&libzahl_tmp_ptest_n1);
    free_chars(&LIBZAHL_TMP_PTEST_N4);

    // Free constant Z structs' chars fields
    free_chars(&LIBZAHL_CONST_1E19);
    free_chars(&LIBZAHL_CONST_1E9);
    free_chars(&libzahl_const_1);
    free_chars(&LIBZAHL_CONST_2);
    free_chars(&libzahl_const_4);

    // Free divmod_ds array elements
    {
        let mut divmod_ds = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
        for z in divmod_ds.iter_mut() {
            z.chars = Option::None;
        }
    }

    // Free pool elements
    {
        let mut pool_n = LIBZAHL_POOL_N.lock().unwrap();
        let mut pool = LIBZAHL_POOL.lock().unwrap();
        
        for i in 0..pool.len() {
            while pool_n[i] > 0 {
                pool_n[i] -= 1;
                pool[i] = Option::None;
            }
        }
    }

    *i_ref = i;
}
pub fn zunsetup() {
    if unsafe { libzahl_set_up != 0 } {
        let mut i = 0;
        helper_zunsetup_1(&mut i);
    }
}
