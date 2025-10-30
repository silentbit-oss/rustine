use lazy_static::lazy_static;
use crate::*;
// Move the jmp_buf struct definition outside the extern block
#[repr(C)]
pub struct jmp_buf([u64; 8]); // Typical size for jmp_buf (8 elements)

extern "C" {
    // Declare the extern variable using the now-available jmp_buf type
    pub static mut libzahl_jmp_buf: jmp_buf;
}

extern "C" {
    pub static mut libzahl_set_up: i32;
}

// Original C: extern int libzahl_error
lazy_static::lazy_static! {
    pub static ref LIBZAHL_ERROR: std::sync::Mutex<i32> = std::sync::Mutex::new(0);
}


lazy_static! {
    pub static ref LIBZAHL_POOL_N: std::sync::Mutex<[usize; (std::mem::size_of::<usize>() * 8)]> =
        std::sync::Mutex::new([0; (std::mem::size_of::<usize>() * 8)]);
}


lazy_static! {
    pub static ref LIBZAHL_POOL_ALLOC: std::sync::Mutex<[usize; (std::mem::size_of::<usize>() * 8)]> =
        std::sync::Mutex::new([0; std::mem::size_of::<usize>() * 8]);
}


lazy_static! {
    pub static ref LIBZAHL_TMP_CMP: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: Option::None,
        });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_STR_NUM: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_str_mag: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_str_div: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_STR_REM: std::sync::Mutex<Z> =
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_gcd_u: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_gcd_v: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_sub: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_MODMUL: std::sync::Mutex<Z> =
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_div: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_mod: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_pow_b: std::sync::Mutex<Z> =
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_pow_c: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_pow_d: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_modsqr: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_a: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_b: std::sync::Mutex<Z> =
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_d: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_PTEST_X: std::sync::Mutex<Z> =
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_a: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_PTEST_D: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_n1: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_PTEST_N4: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    });
}


lazy_static! {
    pub static ref LIBZAHL_CONST_1E19: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    });
}


lazy_static! {
    pub static ref LIBZAHL_CONST_1E9: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 1,
        used: 0,
        alloced: 0,
        chars: None,
    });
}


lazy_static! {
    pub static ref libzahl_const_1: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None
    });
}


lazy_static! {
    pub static ref LIBZAHL_CONST_2: std::sync::Mutex<Z> = 
        std::sync::Mutex::new(Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        });
}


lazy_static! {
    pub static ref libzahl_const_4: std::sync::Mutex<Z> = std::sync::Mutex::new(Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: None,
    });
}


lazy_static! {
    pub static ref LIBZAHL_TMP_DIVMOD_DS: std::sync::Mutex<[Z; 32]> =
        std::sync::Mutex::new([
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None },
            Z { sign: 0, used: 0, alloced: 0, chars: None }
        ]);
}

lazy_static! {
    pub static ref LIBZAHL_POOL: std::sync::Mutex<[Option<Box<[ZahlCharT]>>; (std::mem::size_of::<usize>() * 8)]> = {
        // Create an array of None values without requiring Copy
        let mut arr: [Option<Box<[ZahlCharT]>>; (std::mem::size_of::<usize>() * 8)] = 
            unsafe { std::mem::MaybeUninit::uninit().assume_init() };
        for item in &mut arr {
            *item = Option::None;
        }
        std::sync::Mutex::new(arr)
    };
}

