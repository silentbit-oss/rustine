use crate::*;

pub fn helper_zsetup_1(i_ref: &mut usize) {
    let mut i = *i_ref;
    
    // Set up flag
    unsafe {
        libzahl_set_up = 1;
    }
    
    // Clear pools
    {
        let mut pool = LIBZAHL_POOL.lock().unwrap();
        for item in pool.iter_mut() {
            *item = Option::None;
        }
    }
    {
        let mut pool_n = LIBZAHL_POOL_N.lock().unwrap();
        pool_n.fill(0);
    }
    {
        let mut pool_alloc = LIBZAHL_POOL_ALLOC.lock().unwrap();
        pool_alloc.fill(0);
    }
    
    // Initialize temporary variables
    zinit(&mut LIBZAHL_TMP_CMP.lock().unwrap());
    zinit(&mut LIBZAHL_TMP_STR_NUM.lock().unwrap());
    zinit(&mut libzahl_tmp_str_mag.lock().unwrap());
    zinit(&mut LIBZAHL_TMP_STR_REM.lock().unwrap());
    zinit(&mut libzahl_tmp_gcd_u.lock().unwrap());
    zinit(&mut libzahl_tmp_gcd_v.lock().unwrap());
    zinit(&mut libzahl_tmp_sub.lock().unwrap());
    zinit(&mut LIBZAHL_TMP_MODMUL.lock().unwrap());
    zinit(&mut libzahl_tmp_div.lock().unwrap());
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
    zinit(&mut LIBZAHL_TMP_PTEST_D.lock().unwrap());
    zinit(&mut libzahl_tmp_ptest_n1.lock().unwrap());
    zinit(&mut LIBZAHL_TMP_PTEST_N4.lock().unwrap());
    
    // Initialize constants
    {
        let mut const_1e19 = LIBZAHL_CONST_1E19.lock().unwrap();
        zinit(&mut const_1e19);
        zsetu(&mut const_1e19, 10000000000000000000);
    }
    {
        let mut const_1e9 = LIBZAHL_CONST_1E9.lock().unwrap();
        zinit(&mut const_1e9);
        zsetu(&mut const_1e9, 1000000000);
    }
    {
        let mut const_1 = libzahl_const_1.lock().unwrap();
        zinit(&mut const_1);
        zsetu(&mut const_1, 1);
    }
    {
        let mut const_2 = LIBZAHL_CONST_2.lock().unwrap();
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
        for item in divmod_ds.iter_mut() {
            zinit(item);
        }
    }
    
    // Update i_ref
    *i_ref = i;
}
pub fn zsetup(env: jmp_buf) {
    unsafe {
        // Copy the contents of env to libzahl_jmp_buf
        libzahl_jmp_buf = env;
        
        // Check if setup is needed
        if libzahl_set_up == 0 {
            let mut i = 0;
            helper_zsetup_1(&mut i);
        }
    }
}
