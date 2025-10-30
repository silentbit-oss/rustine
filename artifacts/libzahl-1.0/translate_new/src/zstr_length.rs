use crate::*;
use lazy_static::lazy_static;

pub fn zstr_length(a: &z_t, radix: u64) -> usize {
    let mut size_total = 1;
    let mut size_temp;

    // Lock and set libzahl_tmp_str_num
    {
        let mut tmp_num = libzahl_tmp_str_num.lock().unwrap();
        zset(&mut *tmp_num, a);
    }

    // Main loop
    loop {
        // Check if libzahl_tmp_str_num is zero
        {
            let tmp_num = libzahl_tmp_str_num.lock().unwrap();
            if zzero(&*tmp_num) {
                break;
            }
        }

        // Set libzahl_tmp_str_mag to radix
        {
            let mut tmp_mag = libzahl_tmp_str_mag.lock().unwrap();
            zsetu(&mut *tmp_mag, radix);
        }

        // Set libzahl_tmp_str_div to libzahl_tmp_str_mag
        {
            let mut tmp_div = libzahl_tmp_str_div.lock().unwrap();
            let tmp_mag = libzahl_tmp_str_mag.lock().unwrap();
            zset(&mut *tmp_div, &*tmp_mag);
        }

        size_temp = 1;

        // Inner loop for magnitude comparison
        loop {
            {
                let tmp_mag = libzahl_tmp_str_mag.lock().unwrap();
                let tmp_num = libzahl_tmp_str_num.lock().unwrap();
                if zcmpmag(&*tmp_mag, &*tmp_num) > 0 {
                    break;
                }
            }

            // Update libzahl_tmp_str_div
            {
                let mut tmp_div = libzahl_tmp_str_div.lock().unwrap();
                let tmp_mag = libzahl_tmp_str_mag.lock().unwrap();
                zset(&mut *tmp_div, &*tmp_mag);
            }

            // Square libzahl_tmp_str_mag
            {
                let mut tmp_mag = libzahl_tmp_str_mag.lock().unwrap();
                let mut tmp = [Z {
                    sign: 0,
                    used: 0,
                    alloced: 0,
                    chars: None,
                }];
                zset(&mut tmp, &*tmp_mag);
                zsqr(&mut *tmp_mag, &mut tmp);
            }

            size_temp <<= 1;
        }

        size_temp >>= 1;
        size_total += size_temp;

        // Division operation
        {
            let mut tmp_num = libzahl_tmp_str_num.lock().unwrap();
            let tmp_div = libzahl_tmp_str_div.lock().unwrap();
            let mut tmp = [Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            }];
            zset(&mut tmp, &*tmp_num);
            zdiv(&mut *tmp_num, &tmp, &*tmp_div);
        }
    }

    // Final adjustment for sign
    size_total + (zsignum(a) < 0) as usize
}
