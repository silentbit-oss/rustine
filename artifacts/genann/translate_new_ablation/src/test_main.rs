use rand::Rng;
use std::env;
use std::sync::atomic::Ordering;
use std::time::Instant;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use translate_without_break_down::*;
pub fn main() {
    println!("GENANN TEST SUITE");
    rand::thread_rng(); // Equivalent to srand(100) - using thread-local RNG
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "basic");
        basic();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "xor");
        xor();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "backprop");
        backprop();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "train and");
        train_and();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "train or");
        train_or();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "train xor");
        train_xor();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "persist");
        persist();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "copy");
        copy();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{:<14}", "sigmoid");
        sigmoid();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            duration.as_millis());
    }
    
    {
        if LFAILS.load(Ordering::Relaxed) == 0 {
            println!("ALL TESTS PASSED ({}/{})", 
                LTESTS.load(Ordering::Relaxed), 
                LTESTS.load(Ordering::Relaxed));
        } else {
            println!("SOME TESTS FAILED ({}/{})", 
                LTESTS.load(Ordering::Relaxed) - LFAILS.load(Ordering::Relaxed), 
                LTESTS.load(Ordering::Relaxed));
        }
    }
    
    std::process::exit(if LFAILS.load(Ordering::Relaxed) != 0 { 1 } else { 0 });
}
