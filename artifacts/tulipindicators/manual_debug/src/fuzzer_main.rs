use translate_without_break_down::*;
use std::env;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;

pub fn main() {
	println!("\n* main");
    banner();
    
    let args: Vec<String> = env::args().collect();
    if args.len() > 1 {
        let name = args.get(1).map(|s| s.as_str());
        if let Some(ind_info) = ti_find_indicator(name) {
            let ti_indicators = TI_INDICATORS.lock().unwrap();
            stress_indicator(&ti_indicators[ind_info]);
        }
        if let Some(cnd_info) = tc_find_candle(name) {
            stress_candle(&cnd_info);
        }
    } else {
        // Process all indicators
        {
            let indicators = TI_INDICATORS.lock().unwrap();
            for ind_info in indicators.iter() {
                if ind_info.name.is_some() {
                    stress_indicator(ind_info);
                }
            }
        }
        
        // Process all candles
        {
            let candles = TC_CANDLES.lock().unwrap();
            for cnd_info in candles.iter() {
                if cnd_info.name.is_some() {
                    stress_candle(cnd_info);
                }
            }
        }
    }
    
    println!("\r                                                  \rDone");
    let exit_code = if ERRORS_CNT.load(Ordering::SeqCst) > 0 { 1 } else { 0 };
    std::process::exit(exit_code);
}
