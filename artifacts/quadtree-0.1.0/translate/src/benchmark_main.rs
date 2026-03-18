use translate_new::*;
use std::env;
use rand::thread_rng;
pub fn main() {
    // In Rust, we don't need to explicitly seed the RNG as thread_rng() handles it automatically
    bench(mark_insert, Some("insertion"));
}
