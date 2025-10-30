use translate_without_break_down::*;
use std::env;
use std::time::Instant;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;
pub fn main() {
    println!("TI TEST SUITE");

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = Instant::now();
        print!("\t{:16}", "buffer");
        test_buffer();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            LTESTS.load(Ordering::SeqCst) - ts - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            duration.as_millis());
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = Instant::now();
        print!("\t{:16}", "localbuffer");
        test_localbuffer();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            LTESTS.load(Ordering::SeqCst) - ts - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            duration.as_millis());
    }

    {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = Instant::now();
        print!("\t{:16}", "version");
        test_version();
        let duration = start.elapsed();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            LTESTS.load(Ordering::SeqCst) - ts - (LFAILS.load(Ordering::SeqCst) - fs), 
            LFAILS.load(Ordering::SeqCst) - fs, 
            duration.as_millis());
    }

    test(Some("tests/untest.txt"), 0);
    test(Some("tests/atoz.txt"), 1);
    test(Some("tests/extra.txt"), 1);
    test(Some("tests/candles.txt"), 1);

    {
        let tested_ind = TESTED_IND.lock().unwrap();
        let ti_indicators = TI_INDICATORS.lock().unwrap();
        for i in 0..104 {
            if tested_ind[i] == 0 {
                if let Some(name) = &ti_indicators[i].name {
                    println!("WARNING: no test for {}", name);
                }
            }
        }
    }

    {
        let tested_cnd = TESTED_CND.lock().unwrap();
        let tc_candles = TC_CANDLES.lock().unwrap();
        for i in 0..26 {
            if tested_cnd[i] == 0 {
                if let Some(name) = &tc_candles[i].name {
                    println!("WARNING: no test for {}", name);
                }
            }
        }
    }

    let lfails = LFAILS.load(Ordering::SeqCst);
    let ltests = LTESTS.load(Ordering::SeqCst);
    if lfails == 0 {
        println!("ALL TESTS PASSED ({}/{})", ltests, ltests);
    } else {
        println!("{} TESTS FAILED (of {})", lfails, ltests);
    }
}
