use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn zunsetup() {
    if LIBZAHL_SET_UP.load(Ordering::SeqCst) != 0 {
        LIBZAHL_SET_UP.store(0, Ordering::SeqCst);

        // Free all temporary buffers
        let mut free_chars = |var: &Mutex<z_t>| {
            let mut guard = var.lock().unwrap();
            guard[0].chars = None;
        };

        free_chars(&libzahl_tmp_cmp);
        free_chars(&libzahl_tmp_str_num);
        free_chars(&libzahl_tmp_str_mag);
        free_chars(&libzahl_tmp_str_div);
        free_chars(&libzahl_tmp_str_rem);
        free_chars(&libzahl_tmp_gcd_u);
        free_chars(&libzahl_tmp_gcd_v);
        free_chars(&libzahl_tmp_sub);
        free_chars(&libzahl_tmp_modmul);
        free_chars(&LIBZAHL_TMP_DIV);
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
        free_chars(&libzahl_tmp_ptest_d);
        free_chars(&libzahl_tmp_ptest_n1);
        free_chars(&libzahl_tmp_ptest_n4);

        // Free constants
        free_chars(&libzahl_const_1e19);
        free_chars(&libzahl_const_1e9);
        free_chars(&libzahl_const_1);
        free_chars(&libzahl_const_2);
        free_chars(&libzahl_const_4);

        // Free divmod_ds
        {
            let mut guard = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
            for i in 0..32 {
                guard[i][0].chars = None;
            }
        }

        // Free pool
        {
            let mut pool_guard = LIBZAHL_POOL.lock().unwrap();
            let pool_n_guard = &LIBZAHL_POOL_N;
            
            for i in 0..(std::mem::size_of::<usize>() * 8) {
                let count = pool_n_guard[i].load(Ordering::SeqCst);
                for _ in 0..count {
                    pool_guard[i] = None;
                }
                pool_n_guard[i].store(0, Ordering::SeqCst);
                pool_guard[i] = None;
            }
        }
    }
}
