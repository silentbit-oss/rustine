use crate::*;
use std::ptr::copy_nonoverlapping as memcpy;
use std::fmt::Write;
use std::ptr;
use std::sync::Mutex;


pub fn helper_zstr_1(
    b_idx_ref: &mut u32,
    n_ref: &mut usize,
    len_ref: &mut usize,
    overridden_ref: &mut char,
    b: &mut [u8],
    buf: &mut [u8; 10],
) {
    let mut b_idx = *b_idx_ref;
    let mut n = *n_ref;
    let mut len = *len_ref;
    let mut overridden = *overridden_ref;

    {
        let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
        let mut libzahl_tmp_str_rem = LIBZAHL_TMP_STR_REM.lock().unwrap();
        let libzahl_const_1e9 = LIBZAHL_CONST_1E9.lock().unwrap();
        let tmp_num = Z {
            sign: libzahl_tmp_str_num.sign,
            used: libzahl_tmp_str_num.used,
            alloced: libzahl_tmp_str_num.alloced,
            chars: libzahl_tmp_str_num.chars.clone(),
        };
        zdivmod(
            &mut libzahl_tmp_str_num,
            &mut libzahl_tmp_str_rem,
            &tmp_num,
            &libzahl_const_1e9,
        );
    }

    let libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
    if !zzero(&libzahl_tmp_str_num) {
        let rem = if zzero(&LIBZAHL_TMP_STR_REM.lock().unwrap()) {
            0
        } else {
            LIBZAHL_TMP_STR_REM.lock().unwrap().chars.as_ref().unwrap()[0]
        };

        let slice = &mut b[b_idx as usize..];
        unsafe {
            let s = &mut slice[n..n+9];
            let formatted = format!("{:09}", rem);
            s.copy_from_slice(&formatted.as_bytes()[..9]);
        }
        slice[n + 9] = overridden as u8;
        overridden = slice[n] as char;
        n = if n > 9 { n - 9 } else { 0 };
    } else {
        let rem = LIBZAHL_TMP_STR_REM.lock().unwrap().chars.as_ref().unwrap()[0];
        let formatted = format!("{}", rem);
        len = formatted.len();
        buf[..len].copy_from_slice(formatted.as_bytes());
        
        if overridden != '\0' {
            buf[len] = b[(n + len) + b_idx as usize];
        }
        
        let src = &buf[..len + 1];
        let dest = &mut b[b_idx as usize + n..];
        unsafe {
            std::ptr::copy_nonoverlapping(src.as_ptr(), dest.as_mut_ptr(), len + 1);
        }
    }

    *b_idx_ref = b_idx;
    *n_ref = n;
    *len_ref = len;
    *overridden_ref = overridden;
}
pub fn zstr<'a>(a: &'a Z, b: Option<&'a mut [u8]>) -> Option<Vec<u8>> {
    let mut b_idx = 0u32; // Changed to u32 to match helper_zstr_1's expectation
    let mut buf = [0u8; 10];
    let mut n;
    let mut len = 0; // Initialized to avoid uninitialized variable warning
    let mut overridden = 0 as char;
    let neg;

    if zzero(a) {
        let b = match b {
            Some(slice) => {
                slice[0 + b_idx as usize] = b'0';
                slice[1 + b_idx as usize] = 0;
                return Some(slice.to_vec());
            },
            Option::None => {
                // Return a new Vec instead of a slice
                return Some(vec![b'0', 0]);
            }
        };
    }

    n = zstr_length(a, 10);
    let b = match b {
        Some(slice) => slice,
        Option::None => {
            // Return a new Vec instead of a slice
            let mut new_buf = vec![0u8; n + 1];
            return Some(new_buf);
        }
    };

    neg = zsignum(a) < 0;
    {
        let mut libzahl_tmp_str_num = LIBZAHL_TMP_STR_NUM.lock().unwrap();
        zabs(&mut *libzahl_tmp_str_num, a);
    }
    
    b[0 + b_idx as usize] = b'-';
    b_idx += neg as u32;
    n -= neg as usize;
    n = if n > 9 { n - 9 } else { 0 };

    loop {
        helper_zstr_1(
            &mut b_idx,
            &mut n,
            &mut len,
            &mut overridden,
            b,
            &mut buf,
        );
    }

    // The loop never exits, so this is unreachable
    // In C this would be reached via longjmp
    Option::None
}
