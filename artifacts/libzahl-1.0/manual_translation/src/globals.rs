use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref libzahl_jmp_buf: Mutex<[i32; 6]> = Mutex::new([0; 6]);
}


lazy_static! {
    pub static ref LIBZAHL_SET_UP: std::sync::atomic::AtomicI32 = 
        std::sync::atomic::AtomicI32::new(0);
}


lazy_static! {
    pub static ref LIBZAHL_ERROR: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref LIBZAHL_POOL_N: [AtomicUsize; (std::mem::size_of::<usize>() * 8)] = {
        const SIZE: usize = std::mem::size_of::<usize>() * 8;
        let mut arr: [AtomicUsize; SIZE] = unsafe { std::mem::MaybeUninit::uninit().assume_init() };
        for item in &mut arr[..] {
            *item = AtomicUsize::new(0);
        }
        arr
    };
}


lazy_static! {
    pub static ref LIBZAHL_POOL_ALLOC: Mutex<[usize; (std::mem::size_of::<usize>() * 8)]> =
        Mutex::new([0; (std::mem::size_of::<usize>() * 8)]);
}


lazy_static! {
    pub static ref libzahl_tmp_cmp: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }; 1]);
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
    pub static ref libzahl_tmp_str_div: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_str_rem: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_gcd_u: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_gcd_v: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_sub: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_modmul: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref LIBZAHL_TMP_DIV: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_mod: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }; 1]);
}


lazy_static! {
    pub static ref libzahl_tmp_pow_b: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_pow_c: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_pow_d: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_modsqr: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }; 1]);
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_a: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_b: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_divmod_d: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref LIBZAHL_TMP_PTEST_X: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_a: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_d: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_n1: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_tmp_ptest_n4: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_const_1e19: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_const_1e9: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_const_1: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref libzahl_const_2: std::sync::Mutex<z_t> = 
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }; 1]);
}


lazy_static! {
    pub static ref libzahl_const_4: std::sync::Mutex<z_t> =
        std::sync::Mutex::new([Z {
            sign: 0,
            used: 0,
            alloced: 0,
            chars: None,
        }]);
}


lazy_static! {
    pub static ref LIBZAHL_TMP_DIVMOD_DS: std::sync::Mutex<[z_t; 32]> = std::sync::Mutex::new([
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 1
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 2
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 3
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 4
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 5
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 6
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 7
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 8
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 9
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 10
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 11
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 12
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 13
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 14
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 15
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 16
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 17
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 18
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 19
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 20
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 21
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 22
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 23
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 24
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 25
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 26
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 27
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 28
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 29
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 30
        [Z { sign: 0, used: 0, alloced: 0, chars: None }],  // 31
        [Z { sign: 0, used: 0, alloced: 0, chars: None }]   // 32
    ]);
}

lazy_static! {
    pub static ref LIBZAHL_POOL: Mutex<[Option<Box<[ZahlCharT]>>; (std::mem::size_of::<usize>() * 8)]> = {
        let size = std::mem::size_of::<usize>() * 8;
        let mut arr: [Option<Box<[ZahlCharT]>>; (std::mem::size_of::<usize>() * 8)] = 
            unsafe { std::mem::MaybeUninit::uninit().assume_init() };
        for item in &mut arr {
            *item = None;
        }
        Mutex::new(arr)
    };
}

