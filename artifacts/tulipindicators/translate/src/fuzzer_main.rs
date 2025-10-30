use translate::*;
use std::env;
use std::sync::atomic::Ordering;
pub fn main() -> std::process::ExitCode {
    banner();
    
    let args: Vec<String> = std::env::args().collect();
    if args.len() > 1 {
        let name = args.get(1).map(|s| s.as_str());
        if let Some(ind_info) = ti_find_indicator(name) {
            // Since TI_INDICATORS is a static Mutex, we can find and modify the indicator directly
            let mut ti_indicators = TI_INDICATORS.lock().unwrap();
            if let Some(found) = ti_indicators.iter_mut().find(|i| i.name.as_deref() == name) {
                stress_indicator(found);
            }
        }
        if let Some(cnd_info) = tc_find_candle(name) {
            stress_candle(cnd_info);
        }
    } else {
        {
            let mut ti_indicators = TI_INDICATORS.lock().unwrap();
            for ind_info in ti_indicators.iter_mut() {
                stress_indicator(ind_info);
            }
        }
        {
            let tc_candles = TC_CANDLES.lock().unwrap();
            for cnd_info in tc_candles.iter() {
                stress_candle(cnd_info);
            }
        }
    }
    
    println!("\r                                                  \rDone");
    if ERRORS_CNT.load(Ordering::Relaxed) != 0 {
        std::process::ExitCode::from(1)
    } else {
        std::process::ExitCode::SUCCESS
    }
}
