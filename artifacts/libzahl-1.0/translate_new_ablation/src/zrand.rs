use crate::*;
use lazy_static::lazy_static;
use std::fs::File;
use std::io::Read;
use std::os::unix::io::AsRawFd;
use std::process::abort;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref LIBZAHL_ERROR: AtomicI32 = AtomicI32::new(0);
    pub static ref libzahl_jmp_buf: Mutex<[i32; 6]> = Mutex::new([0; 6]);
}

pub fn zrand_get_random_bits(r: &mut z_t, bits: usize, fd: &mut impl Read) {
    let mut read_total = 0;
    let n;
    let chars = (bits + (32 - 1)) >> 5;
    let mut read_just;
    let mut mask = 1;
    
    {
        if r[0].alloced < chars {
            libzahl_realloc(r, chars);
        }
    }
    
    let buf_ptr = if let Some(ref mut chars_box) = r[0].chars {
        chars_box.as_mut_ptr() as *mut u8
    } else {
        panic!("r->chars is None");
    };
    
    let mut buf = unsafe { std::slice::from_raw_parts_mut(buf_ptr, chars * std::mem::size_of::<zahl_char_t>()) };
    n = buf.len();
    
    while read_total < n {
        read_just = fd.read(&mut buf[read_total..]).unwrap_or_else(|e| {
            LIBZAHL_ERROR.store(e.raw_os_error().unwrap_or(0) as i32, Ordering::SeqCst);
            // In C this would longjmp, but in Rust we panic to simulate non-local goto
            panic!("read error");
        });
        
        if read_just == 0 {
            // EOF reached unexpectedly
            LIBZAHL_ERROR.store(5, Ordering::SeqCst); // EIO equivalent
            panic!("unexpected EOF");
        }
        
        read_total += read_just;
    }
    
    let bits_remaining = bits & (32 - 1);
    mask <<= bits_remaining;
    mask -= 1;
    
    if let Some(ref mut chars_box) = r[0].chars {
        if chars > 0 {
            chars_box[chars - 1] &= mask;
        }
        
        for n in (0..chars).rev() {
            if chars_box[n] != 0 {
                r[0].used = n + 1;
                r[0].sign = 1;
                return;
            }
        }
    }
    
    r[0].sign = 0;
}
pub fn zrand(r: &mut z_t, dev: Zranddev, dist: Zranddist, n: &z_t) {
    let pathname = match dev {
        Zranddev::FAST_RANDOM => "/dev/urandom",
        Zranddev::SECURE_RANDOM => "/dev/random",
    };

    if zzero(n) {
        r[0].sign = 0;
        return;
    }

    let mut file = match File::open(pathname) {
        Ok(file) => file,
        Err(e) => {
            LIBZAHL_ERROR.store(e.raw_os_error().unwrap_or_default(), Ordering::SeqCst);
            // In Rust, we can't use longjmp, so we'll panic instead
            panic!("Failed to open random device: {}", e);
        }
    };

    match dist {
        Zranddist::QUASIUNIFORM => {
            if zsignum(n) < 0 {
                LIBZAHL_ERROR.store(libc::EDOM, Ordering::SeqCst);
                panic!("Domain error: n must be non-negative for QUASIUNIFORM distribution");
            }
            // Create a temporary copy of n instead of cloning
            let mut n_copy = [Z {
                sign: n[0].sign,
                used: n[0].used,
                alloced: n[0].alloced,
                chars: n[0].chars.clone(),
            }];
            let bits = zbits(&mut n_copy);
            zrand_get_random_bits(r, bits, &mut file);
            let libzahl_const_1_guard = libzahl_const_1.lock().unwrap();
            let mut temp = [Z { sign: 0, used: 0, alloced: 0, chars: None }];
            zadd(&mut temp, r, &libzahl_const_1_guard);
            // Create another temporary copy of n
            let mut n_copy_2 = [Z {
                sign: n[0].sign,
                used: n[0].used,
                alloced: n[0].alloced,
                chars: n[0].chars.clone(),
            }];
            zmul(r, &mut temp, &mut n_copy_2);
            zrsh(r, &temp, bits);
        }
        Zranddist::UNIFORM => {
            if zsignum(n) < 0 {
                LIBZAHL_ERROR.store(libc::EDOM, Ordering::SeqCst);
                panic!("Domain error: n must be non-negative for UNIFORM distribution");
            }
            // Create a temporary copy of n instead of cloning
            let mut n_copy = [Z {
                sign: n[0].sign,
                used: n[0].used,
                alloced: n[0].alloced,
                chars: n[0].chars.clone(),
            }];
            let bits = zbits(&mut n_copy);
            loop {
                zrand_get_random_bits(r, bits, &mut file);
                if zcmpmag(r, &n_copy) <= 0 {
                    break;
                }
            }
        }
    }
}
