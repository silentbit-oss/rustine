// Internal constants and utilities for libzahl
// Translates internals.h from the C implementation

use crate::z_t;
use std::cell::RefCell;

// Bit manipulation constants
pub const BITS_PER_CHAR: usize = 32;
pub const LB_BITS_PER_CHAR: usize = 5;
pub const ZAHL_CHAR_MAX: u32 = u32::MAX;

// Bit-to-char conversion macros (as functions in Rust)
#[inline]
pub fn FLOOR_BITS_TO_CHARS(bits: usize) -> usize {
    bits >> LB_BITS_PER_CHAR
}

#[inline]
pub fn CEILING_BITS_TO_CHARS(bits: usize) -> usize {
    (bits + (BITS_PER_CHAR - 1)) >> LB_BITS_PER_CHAR
}

#[inline]
pub fn BITS_IN_LAST_CHAR(bits: usize) -> usize {
    bits & (BITS_PER_CHAR - 1)
}

// Thread-local temporary variables for internal calculations
thread_local! {
    pub static libzahl_tmp_cmp: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_str_num: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_str_mag: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_str_div: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_str_rem: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_gcd_u: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_gcd_v: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_sub: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_modmul: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_div: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_mod: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_pow_b: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_pow_c: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_pow_d: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_modsqr: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_divmod_a: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_divmod_b: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_divmod_d: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_ptest_x: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_ptest_a: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_ptest_d: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_ptest_n1: RefCell<z_t> = RefCell::new(z_t::new());
    pub static libzahl_tmp_ptest_n4: RefCell<z_t> = RefCell::new(z_t::new());
}

// Thread-local constants
thread_local! {
    pub static libzahl_const_1e19: RefCell<z_t> = RefCell::new({
        let mut z = z_t::new();
        z.zsetu(10000000000000000000u64);
        z
    });
    pub static libzahl_const_1e9: RefCell<z_t> = RefCell::new({
        let mut z = z_t::new();
        z.zsetu(1000000000u64);
        z
    });
    pub static libzahl_const_1: RefCell<z_t> = RefCell::new({
        let mut z = z_t::new();
        z.zsetu(1);
        z
    });
    pub static libzahl_const_2: RefCell<z_t> = RefCell::new({
        let mut z = z_t::new();
        z.zsetu(2);
        z
    });
    pub static libzahl_const_4: RefCell<z_t> = RefCell::new({
        let mut z = z_t::new();
        z.zsetu(4);
        z
    });
}

// Utility macros as inline functions
#[inline]
pub fn MIN<T: Ord>(a: T, b: T) -> T {
    if a < b { a } else { b }
}

#[inline]
pub fn MAX<T: Ord>(a: T, b: T) -> T {
    if a > b { a } else { b }
}
