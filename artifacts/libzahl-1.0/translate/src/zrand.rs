use crate::*;
use std::io::Read;
use lazy_static::lazy_static;
use std::fs::File;
use std::process::abort;


pub fn zrand_get_random_bits(r: &mut Z, bits: usize, fd: &mut impl Read) {
    let mut read_total = 0;
    let mut n;
    let chars = (bits + (32 - 1)) >> 5;
    let mut read_just;
    let mut mask: ZahlCharT = 1;
    let mut buf_idx;

    // Ensure allocation is sufficient
    if r.alloced < chars {
        libzahl_realloc(r, chars);
    }

    buf_idx = 0;
    let mut buf = vec![0u8; chars * std::mem::size_of::<ZahlCharT>()];
    
    n = chars * std::mem::size_of::<ZahlCharT>();
    while n > 0 {
        read_just = fd.read(&mut buf[buf_idx..buf_idx + n]).unwrap_or_else(|e| {
            let mut libzahl_error = LIBZAHL_ERROR.lock().unwrap();
            *libzahl_error = e.raw_os_error().unwrap_or(0);
            unsafe {
                extern "C" {
                    fn longjmp(env: *mut jmp_buf, val: i32);
                }
                longjmp(&mut libzahl_jmp_buf as *mut _, 1);
            }
            0 // Unreachable
        });

        read_total += read_just;
        n -= read_just;
        buf_idx += read_just;
    }

    // Copy the bytes into the chars array
    if let Some(chars_slice) = &mut r.chars {
        for i in 0..chars {
            let byte_offset = i * std::mem::size_of::<ZahlCharT>();
            let value = ZahlCharT::from_le_bytes([
                buf[byte_offset],
                buf[byte_offset + 1],
                buf[byte_offset + 2],
                buf[byte_offset + 3],
            ]);
            chars_slice[i] = value;
        }
    }

    let bits = bits & (32 - 1);
    mask <<= bits;
    mask -= 1;
    
    if let Some(chars_slice) = &mut r.chars {
        chars_slice[chars - 1] &= mask;
        
        for n in (0..chars).rev() {
            if chars_slice[n] != 0 {
                r.used = n + 1;
                r.sign = 1;
                return;
            }
        }
    }

    r.sign = 0;
}
pub fn zrand(r: &mut Z, dev: Zranddev, dist: Zranddist, n: &mut Z) {
    let pathname = match dev {
        Zranddev::FastRandom => "/dev/urandom",
        Zranddev::SecureRandom => "/dev/random",
        _ => abort(),
    };

    if zzero(n) {
        r.sign = 0;
        return;
    }

    let mut fd = File::open(pathname).unwrap_or_else(|e| {
        let mut libzahl_error = LIBZAHL_ERROR.lock().unwrap();
        *libzahl_error = e.raw_os_error().unwrap_or(0);
        unsafe {
            extern "C" {
                fn longjmp(env: *mut jmp_buf, val: i32);
            }
            longjmp(&mut libzahl_jmp_buf as *mut _, 1);
        }
        unreachable!();
    });

    match dist {
        Zranddist::Quasiuniform => {
            if zsignum(n) < 0 {
                let mut libzahl_error = LIBZAHL_ERROR.lock().unwrap();
                *libzahl_error = 33; // EDOM value
                unsafe {
                    extern "C" {
                        fn longjmp(env: *mut jmp_buf, val: i32);
                    }
                    longjmp(&mut libzahl_jmp_buf as *mut _, 1);
                }
                unreachable!();
            }
            let bits = zbits(n);
            zrand_get_random_bits(r, bits, &mut fd);
            let const_1 = libzahl_const_1.lock().unwrap();
            let mut temp = Z {
                sign: 0,
                used: 0,
                alloced: 0,
                chars: None,
            };
            zadd(&mut temp, r, &const_1);
            zmul(r, &mut temp, n);
            let temp_r = Z {
                sign: r.sign,
                used: r.used,
                alloced: r.alloced,
                chars: r.chars.clone(),
            };
            zrsh(r, &temp_r, bits);
        }
        Zranddist::Uniform => {
            if zsignum(n) < 0 {
                let mut libzahl_error = LIBZAHL_ERROR.lock().unwrap();
                *libzahl_error = 33; // EDOM value
                unsafe {
                    extern "C" {
                        fn longjmp(env: *mut jmp_buf, val: i32);
                    }
                    longjmp(&mut libzahl_jmp_buf as *mut _, 1);
                }
                unreachable!();
            }
            let bits = zbits(n);
            loop {
                zrand_get_random_bits(r, bits, &mut fd);
                if zcmpmag(r, n) <= 0 {
                    break;
                }
            }
        }
        _ => abort(),
    }
}
