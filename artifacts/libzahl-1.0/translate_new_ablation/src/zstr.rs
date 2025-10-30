use crate::*;
use lazy_static::lazy_static;
use std::io::Write;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

pub fn zstr<'a>(a: &z_t, b: Option<&'a mut [u8]>) -> Option<&'a mut [u8]> {
    if zzero(a) {
        if let Some(b_slice) = b {
            if b_slice.len() >= 2 {
                b_slice[0] = b'0';
                b_slice[1] = 0;
                return Some(&mut b_slice[..2]);
            }
        }
        return None;
    }

    let n = zstr_length(a, 10);
    let neg = zsignum(a) < 0;
    let total_len = n + 1;
    
    let b_slice = match b {
        Some(slice) => {
            if slice.len() < total_len {
                return None;
            }
            slice
        }
        None => return None,
    };

    {
        let mut libzahl_tmp_str_num_guard = libzahl_tmp_str_num.lock().unwrap();
        let mut libzahl_tmp_str_rem_guard = libzahl_tmp_str_rem.lock().unwrap();
        let libzahl_const_1e9_guard = libzahl_const_1e9.lock().unwrap();
        
        zabs(&mut *libzahl_tmp_str_num_guard, a);
        
        let mut offset = if neg { 1 } else { 0 };
        if neg {
            b_slice[0] = b'-';
        }
        
        let mut remaining = n - offset;
        let mut overridden: u8 = 0;
        
        loop {
            let tmp_num = [Z {
                sign: libzahl_tmp_str_num_guard[0].sign,
                used: libzahl_tmp_str_num_guard[0].used,
                alloced: libzahl_tmp_str_num_guard[0].alloced,
                chars: libzahl_tmp_str_num_guard[0].chars.as_ref().map(|c| c.clone()),
            }];
            
            zdivmod(
                &mut *libzahl_tmp_str_num_guard,
                &mut *libzahl_tmp_str_rem_guard,
                &tmp_num,
                &*libzahl_const_1e9_guard,
            );
            
            if !zzero(&*libzahl_tmp_str_num_guard) {
                let rem_value = if zzero(&*libzahl_tmp_str_rem_guard) {
                    0
                } else {
                    libzahl_tmp_str_rem_guard[0].chars.as_ref().unwrap()[0] as u64
                };
                
                let chunk_start = remaining.saturating_sub(9);
                let formatted = format!("{:09}", rem_value);
                let bytes = formatted.as_bytes();
                
                if chunk_start + 9 <= b_slice.len() - offset {
                    b_slice[offset + chunk_start..offset + chunk_start + 9].copy_from_slice(bytes);
                }
                
                if remaining > 0 {
                    overridden = b_slice[offset + chunk_start];
                }
                
                remaining = chunk_start;
            } else {
                let rem_value = libzahl_tmp_str_rem_guard[0].chars.as_ref().unwrap()[0] as u64;
                let formatted = format!("{}", rem_value);
                let bytes = formatted.as_bytes();
                let len = bytes.len();
                
                if remaining + len <= b_slice.len() - offset {
                    b_slice[offset + remaining..offset + remaining + len].copy_from_slice(bytes);
                }
                
                if overridden != 0 {
                    b_slice[offset + remaining + len] = overridden;
                }
                
                break;
            }
        }
    }
    
    Some(if neg {
        &mut b_slice[..total_len]
    } else {
        &mut b_slice[..total_len - 1]
    })
}
