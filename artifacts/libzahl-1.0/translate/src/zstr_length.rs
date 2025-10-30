use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;

pub fn zstr_length(a: &Z, radix: u64) -> usize {
    let mut size_total = 1;
    let mut size_temp;
    
    // Lock and set libzahl_tmp_str_num
    {
        let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
        zset(&mut *libzahl_tmp_str_num, a);
    }
    
    // Main loop
    loop {
        // Check if we should break
        {
            let libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
            if zzero(&*libzahl_tmp_str_num) {
                break;
            }
        }
        
        // Set magnitude
        {
            let mut mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            zsetu(&mut *mag_guard, radix);
        }
        
        // Set divisor
        {
            let mut div_guard = libzahl_tmp_str_div.lock().unwrap();
            let mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            zset(&mut *div_guard, &*mag_guard);
        }
        
        size_temp = 1;
        
        // Inner loop
        loop {
            let mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            let libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
            
            if zcmpmag(&*mag_guard, &*libzahl_tmp_str_num) <= 0 {
                // Set divisor
                {
                    let mut div_guard = libzahl_tmp_str_div.lock().unwrap();
                    zset(&mut *div_guard, &*mag_guard);
                }
                
                // Square magnitude
                {
                    let mut mag_guard = libzahl_tmp_str_mag.lock().unwrap();
                    let mut tmp = Z {
                        sign: mag_guard.sign,
                        used: mag_guard.used,
                        alloced: mag_guard.alloced,
                        chars: mag_guard.chars.clone(),
                    };
                    zsqr(&mut *mag_guard, &mut tmp);
                }
                
                size_temp <<= 1;
            } else {
                break;
            }
        }
        
        size_temp >>= 1;
        size_total += size_temp;
        
        // Division operation - fixed by splitting into separate operations
        {
            let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
            let div_guard = libzahl_tmp_str_div.lock().unwrap();
            let mut temp = Z {
                sign: libzahl_tmp_str_num.sign,
                used: libzahl_tmp_str_num.used,
                alloced: libzahl_tmp_str_num.alloced,
                chars: libzahl_tmp_str_num.chars.clone(),
            };
            zdiv(&mut temp, &mut *libzahl_tmp_str_num, &*div_guard);
            *libzahl_tmp_str_num = temp;
        }
    }
    
    size_total + (zsignum(a) < 0) as usize
}
