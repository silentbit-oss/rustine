//! Shared test utilities
//! Copyright (C) 2018-2021  Pali Rohár <pali.rohar@gmail.com>
//! Rust translation (C) 2026

#[macro_export]
macro_rules! ASSERT {
    ($cond:expr, $msg:expr) => {
        assert!($cond, $msg);
    };
}

#[macro_export]
macro_rules! PASS {
    ($msg:expr) => {
        println!("✅ {} passed", $msg);
    };
}
