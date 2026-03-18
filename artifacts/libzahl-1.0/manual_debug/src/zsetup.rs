use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;

pub fn zsetup(env: &[i32; 6]) {
    *libzahl_jmp_buf.lock().unwrap() = *env;
    
    if LIBZAHL_SET_UP.compare_exchange(0, 1, Ordering::SeqCst, Ordering::SeqCst).is_ok() {
        // Initialize pools with zeros
        {
            let mut pool = LIBZAHL_POOL.lock().unwrap();
            for item in pool.iter_mut() {
                *item = None;
            }
        }
        
        {
            for item in LIBZAHL_POOL_N.iter() {
                item.store(0, Ordering::SeqCst);
            }
        }
        
        {
            let mut pool_alloc = LIBZAHL_POOL_ALLOC.lock().unwrap();
            for item in pool_alloc.iter_mut() {
                *item = 0;
            }
        }
        
        // Initialize temporary variables
        zinit(&mut libzahl_tmp_cmp.lock().unwrap());
        zinit(&mut libzahl_tmp_str_num.lock().unwrap());
        zinit(&mut libzahl_tmp_str_mag.lock().unwrap());
        zinit(&mut libzahl_tmp_str_div.lock().unwrap());
        zinit(&mut libzahl_tmp_str_rem.lock().unwrap());
        zinit(&mut libzahl_tmp_gcd_u.lock().unwrap());
        zinit(&mut libzahl_tmp_gcd_v.lock().unwrap());
        zinit(&mut libzahl_tmp_sub.lock().unwrap());
        zinit(&mut libzahl_tmp_modmul.lock().unwrap());
        zinit(&mut LIBZAHL_TMP_DIV.lock().unwrap());
        zinit(&mut libzahl_tmp_mod.lock().unwrap());
        zinit(&mut libzahl_tmp_pow_b.lock().unwrap());
        zinit(&mut libzahl_tmp_pow_c.lock().unwrap());
        zinit(&mut libzahl_tmp_pow_d.lock().unwrap());
        zinit(&mut libzahl_tmp_modsqr.lock().unwrap());
        zinit(&mut libzahl_tmp_divmod_a.lock().unwrap());
        zinit(&mut libzahl_tmp_divmod_b.lock().unwrap());
        zinit(&mut libzahl_tmp_divmod_d.lock().unwrap());
        zinit(&mut LIBZAHL_TMP_PTEST_X.lock().unwrap());
        zinit(&mut libzahl_tmp_ptest_a.lock().unwrap());
        zinit(&mut libzahl_tmp_ptest_d.lock().unwrap());
        zinit(&mut libzahl_tmp_ptest_n1.lock().unwrap());
        zinit(&mut libzahl_tmp_ptest_n4.lock().unwrap());
        
        // Initialize constants
        {
            let mut const_1e19 = libzahl_const_1e19.lock().unwrap();
            zinit(&mut const_1e19);
            zsetu(&mut const_1e19, 10000000000000000000);
        }
        {
            let mut const_1e9 = libzahl_const_1e9.lock().unwrap();
            zinit(&mut const_1e9);
            zsetu(&mut const_1e9, 1000000000);
        }
        {
            let mut const_1 = libzahl_const_1.lock().unwrap();
            zinit(&mut const_1);
            zsetu(&mut const_1, 1);
        }
        {
            let mut const_2 = libzahl_const_2.lock().unwrap();
            zinit(&mut const_2);
            zsetu(&mut const_2, 2);
        }
        {
            let mut const_4 = libzahl_const_4.lock().unwrap();
            zinit(&mut const_4);
            zsetu(&mut const_4, 4);
        }
        
        // Initialize divmod_ds array
        {
            let mut divmod_ds = LIBZAHL_TMP_DIVMOD_DS.lock().unwrap();
            for i in 0..32 {
                zinit(&mut divmod_ds[i]);
            }
        }
    }
}
