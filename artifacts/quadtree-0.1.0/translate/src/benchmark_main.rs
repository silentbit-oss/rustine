use translate::*;
use std::env;
use rand::thread_rng;
pub fn main() {
    let _ = thread_rng(); // Equivalent to srand(time(0)) - thread_rng seeds itself
    bench(mark_insert, Some("insertion"));
}
