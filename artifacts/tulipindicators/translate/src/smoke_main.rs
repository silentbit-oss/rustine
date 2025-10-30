use translate::*;
use std::env;
use std::time::Duration;
use std::time::Instant;
use std::sync::atomic::Ordering;
pub fn main() {
    println!("TI TEST SUITE");
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{: <16}", "buffer");
        test_buffer();
        let elapsed = start.elapsed().as_millis();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            elapsed);
    }
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{: <16}", "localbuffer");
        test_localbuffer();
        let elapsed = start.elapsed().as_millis();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            elapsed);
    }
    {
        let ts = LTESTS.load(Ordering::Relaxed);
        let fs = LFAILS.load(Ordering::Relaxed);
        let start = Instant::now();
        print!("\t{: <16}", "version");
        test_version();
        let elapsed = start.elapsed().as_millis();
        println!("pass:{:2}   fail:{:2}   {:4}ms", 
            (LTESTS.load(Ordering::Relaxed) - ts) - (LFAILS.load(Ordering::Relaxed) - fs), 
            LFAILS.load(Ordering::Relaxed) - fs, 
            elapsed);
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
                println!("WARNING: no test for {}", ti_indicators[i].name.as_ref().unwrap());
            }
        }
    }

    {
        let tested_cnd = TESTED_CND.lock().unwrap();
        let tc_candles = TC_CANDLES.lock().unwrap();
        for i in 0..26 {
            if tested_cnd[i] == 0 {
                println!("WARNING: no test for {}", tc_candles[i].name.as_ref().unwrap());
            }
        }
    }

    let lfails = LFAILS.load(Ordering::Relaxed);
    let ltests = LTESTS.load(Ordering::Relaxed);
    if lfails == 0 {
        println!("ALL TESTS PASSED ({}/{})", ltests, ltests);
    } else {
        println!("{} TESTS FAILED (of {})", lfails, ltests);
    }

    std::process::exit(if lfails != 0 { 1 } else { 0 });
}
