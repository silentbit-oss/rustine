use crate::*;
use crate::types::Z;
use crate::types::z_t;
use crate::zcmpmag;
use crate::zdiv;
use crate::zset;
use crate::zsetu;
use crate::zsignum;
use crate::zsqr;
use crate::zzero;
use lazy_static::lazy_static;

lazy_static! {
    pub static ref libzahl_tmp_str_div: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}

lazy_static! {
    pub static ref libzahl_tmp_str_mag: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}

lazy_static! {
    pub static ref libzahl_tmp_str_num: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}

pub fn zstr_length(a: &z_t, radix: u64) -> usize {
    let mut size_total = 1;
    
    {
        let mut libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
        zset(&mut *libzahl_tmp_str_num_guard, a);
    }
    
    loop {
        let libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
        if zzero(&*libzahl_tmp_str_num_guard) {
            break;
        }
        drop(libzahl_tmp_str_num_guard);
        
        {
            let mut libzahl_tmp_str_mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            zsetu(&mut *libzahl_tmp_str_mag_guard, radix);
        }
        
        {
            let mut libzahl_tmp_str_div_guard = libzahl_tmp_str_div.lock().unwrap();
            let libzahl_tmp_str_mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            zset(&mut *libzahl_tmp_str_div_guard, &*libzahl_tmp_str_mag_guard);
        }
        
        let mut size_temp = 1;
        
        loop {
            {
                let mut libzahl_tmp_str_div_guard = libzahl_tmp_str_div.lock().unwrap();
                let libzahl_tmp_str_mag_guard = libzahl_tmp_str_mag.lock().unwrap();
                zset(&mut *libzahl_tmp_str_div_guard, &*libzahl_tmp_str_mag_guard);
            }
            
            {
                let mut libzahl_tmp_str_mag_guard = libzahl_tmp_str_mag.lock().unwrap();
                let mut tmp_mag = [Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                }];
                zset(&mut tmp_mag, &*libzahl_tmp_str_mag_guard);
                zsqr(&mut *libzahl_tmp_str_mag_guard, &mut tmp_mag);
            }
            
            size_temp <<= 1;
            
            let libzahl_tmp_str_mag_guard = libzahl_tmp_str_mag.lock().unwrap();
            let libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
            if zcmpmag(&*libzahl_tmp_str_mag_guard, &*libzahl_tmp_str_num_guard) <= 0 {
                continue;
            } else {
                break;
            }
        }
        
        size_temp >>= 1;
        size_total += size_temp;
        
        {
            let mut libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
            let libzahl_tmp_str_div_guard = libzahl_tmp_str_div.lock().unwrap();
            let mut tmp_num = [Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            }];
            zset(&mut tmp_num, &*libzahl_tmp_str_num_guard);
            zdiv(&mut *libzahl_tmp_str_num_guard, &tmp_num, &*libzahl_tmp_str_div_guard);
        }
    }
    
    let sign = zsignum(a);
    size_total + if sign < 0 { 1 } else { 0 }
}
