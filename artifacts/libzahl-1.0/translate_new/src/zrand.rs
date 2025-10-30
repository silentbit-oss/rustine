use crate::*;
use lazy_static::lazy_static;
use std::fs::File;
use std::io::Read;
use std::process::abort;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref LIBZAHL_ERROR: AtomicI32 = AtomicI32::new(0);
    pub static ref libzahl_jmp_buf: Mutex<[i32; 6]> = Mutex::new([0; 6]);
}

pub fn zrand_get_random_bits(r: &mut z_t, bits: usize, fd: &mut impl Read) {
    let chars = (bits + 31) >> 5;
    
    // Ensure allocation is sufficient
    if r[0].alloced < chars {
        libzahl_realloc(r, chars);
    }

    let buf_ptr = r[0].chars.as_mut().unwrap().as_mut_ptr() as *mut u8;
    let mut read_total = 0;
    let mut remaining = chars * std::mem::size_of::<zahl_char_t>();

    unsafe {
        let mut buf_idx = 0;
        while remaining > 0 {
            let buf_slice = std::slice::from_raw_parts_mut(buf_ptr.add(buf_idx), remaining);
            match fd.read(buf_slice) {
                Ok(read_just) => {
                    if read_just == 0 {
                        break; // EOF
                    }
                    read_total += read_just;
                    remaining -= read_just;
                    buf_idx += read_just;
                }
                Err(e) => {
                    LIBZAHL_ERROR.store(e.raw_os_error().unwrap_or(0), Ordering::SeqCst);
                    // In Rust we can't use longjmp, so we panic instead
                    panic!("read error");
                }
            }
        }
    }

    let bits = bits & 31;
    let mask = if bits == 0 {
        0xFFFF_FFFF
    } else {
        (1 << bits) - 1
    };

    if chars > 0 {
        r[0].chars.as_mut().unwrap()[chars - 1] &= mask;
    }

    for n in (0..chars).rev() {
        if r[0].chars.as_ref().unwrap()[n] != 0 {
            r[0].used = n + 1;
            r[0].sign = 1;
            return;
        }
    }

    r[0].sign = 0;
}
pub fn zrand(r: &mut z_t, dev: Zranddev, dist: Zranddist, n: &mut z_t) {
    let pathname = match dev {
        Zranddev::FAST_RANDOM => "/dev/urandom",
        Zranddev::SECURE_RANDOM => "/dev/random",
        _ => abort(),
    };

    if zzero(n) {
        r[0].sign = 0;
        return;
    }

    let mut file = match File::open(pathname) {
        Ok(f) => f,
        Err(e) => {
            LIBZAHL_ERROR.store(e.raw_os_error().unwrap_or(0), Ordering::SeqCst);
            panic!("Failed to open random device");
        }
    };

    match dist {
        Zranddist::QUASIUNIFORM => {
            if zsignum(n) < 0 {
                LIBZAHL_ERROR.store(libc::EDOM, Ordering::SeqCst);
                panic!("Domain error");
            }
            let bits = zbits(n);
            zrand_get_random_bits(r, bits, &mut file);
            
            // Create a temporary copy for zadd
            let mut temp = [Z {
                sign: r[0].sign,
                used: r[0].used,
                alloced: r[0].alloced,
                chars: r[0].chars.clone(),
            }];
            zadd(&mut temp, r, &libzahl_const_1.lock().unwrap());
            
            // Create another temporary for zmul
            let mut temp2 = [Z {
                sign: temp[0].sign,
                used: temp[0].used,
                alloced: temp[0].alloced,
                chars: temp[0].chars.clone(),
            }];
            zmul(r, &mut temp2, n);
            
            // Create a temporary for zrsh to avoid overlapping borrows
            let temp_r = [Z {
                sign: r[0].sign,
                used: r[0].used,
                alloced: r[0].alloced,
                chars: r[0].chars.clone(),
            }];
            zrsh(r, &temp_r, bits);
        }
        Zranddist::UNIFORM => {
            if zsignum(n) < 0 {
                LIBZAHL_ERROR.store(libc::EDOM, Ordering::SeqCst);
                panic!("Domain error");
            }
            let bits = zbits(n);
            loop {
                zrand_get_random_bits(r, bits, &mut file);
                if zcmpmag(r, n) <= 0 {
                    break;
                }
            }
        }
        _ => abort(),
    }
}
