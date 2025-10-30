use translate::*;
use std::env;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;

pub fn main() {
    println!("GENANN TEST SUITE");
    // Seed random number generator with fixed value (100)
    let _seed = 100;

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "basic");
        basic();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "xor");
        xor();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "backprop");
        backprop();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "train and");
        train_and();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "train or");
        train_or();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "train xor");
        train_xor();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "persist");
        persist();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "copy");
        copy();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();
        print!("\t{:<14}", "sigmoid");
        sigmoid();
        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            elapsed);
    }

    {
        if LFAILS.load(Ordering::SeqCst) == 0 {
            println!("ALL TESTS PASSED ({}/{})", LTESTS.load(Ordering::SeqCst), LTESTS.load(Ordering::SeqCst));
        } else {
            println!("SOME TESTS FAILED ({}/{})", LTESTS.load(Ordering::SeqCst) - LFAILS.load(Ordering::SeqCst), LTESTS.load(Ordering::SeqCst));
        }
    }

    std::process::exit(if LFAILS.load(Ordering::SeqCst) != 0 { 1 } else { 0 });
}
