use translate::*;
use std::env;
use std::sync::atomic::Ordering;

pub fn main() {
    all_tests();
    let mu_fails = MU_FAILS.load(Ordering::SeqCst);
    let mu_tests = MU_TESTS.load(Ordering::SeqCst);

    if mu_fails > 0 {
        println!("*** {}/{} TESTS FAILED ***", mu_fails, mu_tests);
        std::process::exit(1);
    } else {
        println!("ALL TESTS PASSED");
        std::process::exit(0);
    }
}
