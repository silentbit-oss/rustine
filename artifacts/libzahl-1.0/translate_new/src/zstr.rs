use crate::*;
use lazy_static::lazy_static;
use std::io::Write;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

pub fn zstr<'a>(a: &z_t, b: Option<&'a mut [u8]>) -> Option<&'a mut [u8]> {
    let mut b_idx = 0;
    let mut n;
    let mut len: usize = 0;
    let mut overridden = 0u8;
    let neg;

    if zzero(a) {
        let b = match b {
            Some(b) => b,
            None => {
                let mut new_b = vec![0u8; 2];
                b_idx = new_b.as_mut_ptr() as usize;
                unsafe { new_b.set_len(2); }
                return Some(new_b.into_boxed_slice()).map(|b| Box::leak(b));
            }
        };

        b[0 + b_idx] = b'0';
        b[1 + b_idx] = 0;
        return Some(&mut b[b_idx..]);
    }

    n = zstr_length(a, 10);
    let b = match b {
        Some(b) => b,
        None => {
            let mut new_b = vec![0u8; n + 1];
            b_idx = new_b.as_mut_ptr() as usize;
            unsafe { new_b.set_len(n + 1); }
            return Some(new_b.into_boxed_slice()).map(|b| Box::leak(b));
        }
    };

    neg = zsignum(a) < 0;
    zabs(&mut *libzahl_tmp_str_num.lock().unwrap(), a);
    b[0 + b_idx] = b'-';
    b_idx += neg as usize;
    n -= neg as usize;
    n = if n > 9 { n - 9 } else { 0 };

    loop {
        zdivmod(
            &mut *libzahl_tmp_str_num.lock().unwrap(),
            &mut *libzahl_tmp_str_rem.lock().unwrap(),
            &*libzahl_tmp_str_num.lock().unwrap(),
            &*libzahl_const_1e9.lock().unwrap(),
        );

        if !zzero(&*libzahl_tmp_str_num.lock().unwrap()) {
            let rem = if zzero(&*libzahl_tmp_str_rem.lock().unwrap()) {
                0
            } else {
                libzahl_tmp_str_rem.lock().unwrap()[0].chars.as_ref().unwrap()[0] as u64
            };
            let s = format!("{:09}", rem);
            let bytes = s.as_bytes();
            if bytes.len() != 9 {
                panic!("Expected 9 formatted digits, got {}", bytes.len());
            }
            let start = n + b_idx;
            b[start..start + 9].copy_from_slice(bytes);
            b[start + 9] = overridden;
            overridden = b[start];
            n = if n > 9 { n - 9 } else { 0 };
        } else {
            let rem = libzahl_tmp_str_rem.lock().unwrap()[0].chars.as_ref().unwrap()[0] as u64;
            let s = format!("{}", rem);
            let bytes = s.as_bytes();
            len = bytes.len();
            let start = n + b_idx;
            if overridden != 0 {
                let saved_byte = b[start + len];
                b[start..start + len].copy_from_slice(bytes);
                b[start + len] = saved_byte;
            } else {
                b[start..start + len].copy_from_slice(bytes);
                b[start + len] = 0;
            }
            break;
        }
    }

    Some(&mut b[b_idx - neg as usize..])
}
