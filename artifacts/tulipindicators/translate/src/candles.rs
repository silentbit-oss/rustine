use crate::*;
use std::cmp::Ordering;
use std::f64;
use std::mem;
use lazy_static::lazy_static;
use std::sync::Mutex;
use rand::Rng;

pub fn tc_version() -> &'static str {
    "0.9.2"
}
pub fn tc_build() -> i64 {
    1645649572
}
pub fn tc_candle_count() -> i32 {
    26
}
pub fn tc_config_default() -> &'static TcConfig {
    static DEFAULT_CONFIG: TcConfig = TcConfig {
        period: 10,
        body_none: 0.05,
        body_short: 0.5,
        body_long: 1.4,
        wick_none: 0.05,
        wick_long: 0.6,
        near: 0.3,
    };
    &DEFAULT_CONFIG
}
pub fn tc_result_new() -> Option<TcResult> {
    Some(TcResult {
        progress: 0,
        space: 0,
        count: 0,
        pattern_count: 0,
        hits: None,
    })
}
pub fn tc_result_free(result: Option<Box<TcResult>>) {
    // In Rust, Box handles deallocation automatically when it goes out of scope
    // No explicit free needed - Rust's ownership system handles memory management
    // The Option wrapper allows for NULL check equivalent
    if result.is_none() {
        return;
    }
    // The Box and its contents (including the Vec inside TcResult) will be dropped here
}
pub fn tc_result_count(result: &TcResult) -> i32 {
    result.count
}
pub fn tc_result_pattern_count(result: &TcResult) -> i32 {
    result.pattern_count
}
pub fn tc_result_at(result: &TcResult, index: i32) -> i32 {
    let mut imin = 0;
    let mut imax = result.count - 1;
    
    if imax == 0 {
        return 0;
    }

    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        assert!(i >= 0);
        assert!(i < result.count);
        
        if let Some(hits) = &result.hits {
            if index == hits[i as usize].index {
                return hits[i as usize].patterns as i32;
            } else if index > hits[i as usize].index {
                imin = i + 1;
            } else {
                imax = i - 1;
            }
        } else {
            return 0;
        }
    }

    0
}
pub fn tc_result_reset(result: &mut TcResult) {
    result.progress = 0;
    result.count = 0;
    result.pattern_count = 0;
}
pub fn tc_find_candle(name: Option<&str>) -> Option<TcCandleInfo> {
    // Check for None (equivalent to NULL check in C)
    let name = name?;
    
    let tc_candles = TC_CANDLES.lock().unwrap();
    let mut imin = 0;
    let mut imax = tc_candles.len().checked_sub(2)?; // -2 becomes len()-2, but checked for safety
    
    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        let candle_name = tc_candles[i].name.as_deref()?; // Get &str from Option<String>
        
        match name.cmp(candle_name) {
            Ordering::Equal => return Some(tc_candles[i].clone()),
            Ordering::Greater => imin = i + 1,
            Ordering::Less => imax = i - 1,
        }
    }
    
    None
}
pub fn tc_config_set_to_default(config: &mut TcConfig) {
    *config = tc_config_default().clone();
}
pub fn tc_result_get(result: &TcResult, index: i32) -> TcHit {
    if index < result.count {
        // Safe to unwrap because we've checked bounds and hits is Some when count > 0
        result.hits.as_ref().unwrap()[index as usize].clone()
    } else {
        TcHit {
            index: 0,
            patterns: 0,
        }
    }
}

pub fn tc_result_add(result: &mut TcResult, hit: TcHit) -> i32 {
    result.pattern_count += 1;
    
    if result.count > 0 {
        if let Some(last_hit) = result.hits.as_ref().and_then(|hits| hits.last()) {
            if last_hit.index == hit.index {
                if let Some(hits) = result.hits.as_mut() {
                    hits.last_mut().unwrap().patterns |= hit.patterns;
                }
                return 0;
            }
        }
    }

    if result.space == 0 {
        result.space = 2048;
        result.count = 0;
        result.hits = Some(Vec::with_capacity(result.space as usize));
    } else if result.space == result.count {
        result.space *= 2;
        if let Some(hits) = &mut result.hits {
            hits.reserve(result.space as usize);
        } else {
            return 2;
        }
    }

    if let Some(hits) = &mut result.hits {
        hits.push(hit);
        result.count += 1;
        0
    } else {
        2
    }
}
pub fn tc_get_info(pattern: Option<tc_set>) -> Option<&'static TcCandleInfo> {
    // Check for NULL equivalent (None)
    let pattern = pattern?;

    let k = pattern & (!(pattern - 1));
    let mut imin = 0;
    let mut imax = (TC_CANDLES.lock().unwrap().len() - 1) as i32; // -1 because Rust uses 0-based indexing

    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        let tc_candles = TC_CANDLES.lock().unwrap();
        
        // Safe comparison since we're working with u64 (tc_set)
        match k.cmp(&tc_candles[i as usize].pattern) {
            std::cmp::Ordering::Equal => {
                // Get a raw pointer to the element and convert it to a static reference
                // This is safe because TC_CANDLES is static and won't move
                let ptr = &tc_candles[i as usize] as *const TcCandleInfo;
                return Some(unsafe { &*ptr });
            }
            std::cmp::Ordering::Greater => {
                imin = i + 1;
            }
            std::cmp::Ordering::Less => {
                imax = i - 1;
            }
        }
    }

    None
}

pub fn tc_abandoned_baby_bear(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let idx = i as usize;
        let prev_idx = (i - 1) as usize;
        let prev_prev_idx = (i - 2) as usize;
        let period_idx = (i - period) as usize;

        let top = if open[idx] > close[idx] {
            open[idx]
        } else {
            close[idx]
        };
        let bottom = if open[idx] < close[idx] {
            open[idx]
        } else {
            close[idx]
        };
        let body = (open[idx] - close[idx]).abs();
        let total = high[idx] - low[idx];
        let upper = high[idx] - top;
        let lower = bottom - low[idx];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 2
            && open[prev_prev_idx] < close[prev_prev_idx]
            && (open[prev_prev_idx] - close[prev_prev_idx]).abs() > (options.body_long * avg_body)
            && low[prev_idx] >= high[prev_prev_idx]
            && (open[prev_idx] - close[prev_idx]).abs() < (options.body_none * avg_total)
            && open[idx] > close[idx]
            && high[idx] <= low[prev_idx]
            && close[idx] <= close[prev_prev_idx]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 0,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= (open[period_idx] - close[period_idx]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[period_idx] - low[period_idx];
        i += 1;
    }

    0
}

pub fn tc_abandoned_baby_bull(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    let mut i = 0;

    // Initial period calculation
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    // Main loop
    while i < size {
        let idx = i as usize;
        let top = if open[idx] > close[idx] {
            open[idx]
        } else {
            close[idx]
        };
        let bottom = if open[idx] < close[idx] {
            open[idx]
        } else {
            close[idx]
        };
        let body = (open[idx] - close[idx]).abs();
        let total = high[idx] - low[idx];
        let upper = high[idx] - top;
        let lower = bottom - low[idx];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        // Check conditions for abandoned baby bull pattern
        if i >= 2
            && open[idx - 2] > close[idx - 2]
            && (open[idx - 2] - close[idx - 2]).abs() > options.body_long * avg_body
            && high[idx - 1] <= low[idx - 2]
            && (open[idx - 1] - close[idx - 1]).abs() < options.body_none * avg_total
            && open[idx] < close[idx]
            && low[idx] >= high[idx - 1]
            && close[idx] >= close[idx - 2]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 1,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        let prev_period_idx = (i - period) as usize;
        avg_body_sum += body;
        avg_body_sum -= (open[prev_period_idx] - close[prev_period_idx]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[prev_period_idx] - low[prev_period_idx];

        i += 1;
    }

    0
}

pub fn tc_big_black_candle(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    // Initial window calculation
    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        let current = i as usize;
        let prev_period = (i - period) as usize;

        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = f64::abs(open[current] - close[current]);
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if open[current] > close[current] && body > (options.body_long * avg_body) {
            let hit = TcHit {
                index: i,
                patterns: 1 << 2,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[prev_period] - close[prev_period]);
        avg_total_sum += total;
        avg_total_sum -= high[prev_period] - low[prev_period];

        i += 1;
    }

    0
}

pub fn tc_big_white_candle(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = f64::abs(open[i as usize] - close[i as usize]);
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if open[i as usize] < close[i as usize] 
            && f64::abs(open[i as usize] - close[i as usize]) > (options.body_long * avg_body) 
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 3,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}
pub fn tc_black_marubozu(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];

        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = f64::abs(open_i - close_i);
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (f64::abs(open_i - close_i) > (options.body_long * avg_body))
            && ((high_i - top) < (options.wick_none * avg_total))
            && ((bottom - low_i) < (options.wick_none * avg_total))
            && (open_i > close_i)
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 4,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_doji(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    // Calculate initial sums for the first period elements
    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period as usize;
    while i < size as usize {
        let top = if open[i] > close[i] { open[i] } else { close[i] };
        let bottom = if open[i] < close[i] { open[i] } else { close[i] };
        let body = f64::abs(open[i] - close[i]);
        let total = high[i] - low[i];
        let upper = high[i] - top;
        let lower = bottom - low[i];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if f64::abs(open[i] - close[i]) < (options.body_none * avg_total) {
            let hit = TcHit {
                index: i as i32,
                patterns: 1 << 5,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[i - period as usize] - close[i - period as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[i - period as usize] - low[i - period as usize];

        i += 1;
    }

    0
}

pub fn tc_dragonfly_doji(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = (open[i as usize] - close[i as usize]).abs();
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if ((body < (options.body_none * avg_total))
            && (upper < (options.wick_none * avg_total)))
            && (lower > (options.wick_long * avg_body))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 6,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}
pub fn tc_engulfing_bear(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period as usize;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if (size as usize) < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i] - close[i]).abs();
        avg_total_sum += high[i] - low[i];
        i += 1;
    }

    while i < size as usize {
        let top = if open[i] > close[i] { open[i] } else { close[i] };
        let bottom = if open[i] < close[i] { open[i] } else { close[i] };
        let body = (open[i] - close[i]).abs();
        let total = high[i] - low[i];
        let upper = high[i] - top;
        let lower = bottom - low[i];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 1
            && open[i] > close[i]
            && open[i - 1] < close[i - 1]
            && close[i] < open[i - 1]
            && open[i] > close[i - 1]
        {
            let hit = TcHit {
                index: i as i32,
                patterns: 1 << 7,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= (open[i - period] - close[i - period]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[i - period] - low[i - period];
        i += 1;
    }

    0
}

pub fn tc_engulfing_bull(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];

        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = f64::abs(open_i - close_i);
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 1
            && open_i < close_i
            && open[(i - 1) as usize] > close[(i - 1) as usize]
            && close_i > open[(i - 1) as usize]
            && open_i < close[(i - 1) as usize]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 8,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_evening_doji_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];

        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = f64::abs(open_i - close_i);
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 2
            && open[(i - 2) as usize] < close[(i - 2) as usize]
            && f64::abs(open[(i - 2) as usize] - close[(i - 2) as usize])
                > (options.body_long * avg_body)
            && (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }) >= (if open[(i - 2) as usize] > close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            })
            && f64::abs(open[(i - 1) as usize] - close[(i - 1) as usize])
                < (options.body_none * avg_total)
            && open_i > close_i
            && (if open_i > close_i { open_i } else { close_i })
                <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                    open[(i - 1) as usize]
                } else {
                    close[(i - 1) as usize]
                })
            && close_i <= close[(i - 2) as usize]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 9,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_evening_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let current = i as usize;
        let prev1 = (i - 1) as usize;
        let prev2 = (i - 2) as usize;
        let prev_period = (i - period) as usize;

        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = (open[current] - close[current]).abs();
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 2
            && open[prev2] < close[prev2]
            && (open[prev2] - close[prev2]).abs() > (options.body_long * avg_body)
            && (if open[prev1] < close[prev1] {
                open[prev1]
            } else {
                close[prev1]
            }) >= (if open[prev2] > close[prev2] {
                open[prev2]
            } else {
                close[prev2]
            })
            && (open[prev1] - close[prev1]).abs() < (options.body_short * avg_body)
            && open[current] > close[current]
            && (if open[current] > close[current] {
                open[current]
            } else {
                close[current]
            }) <= (if open[prev1] < close[prev1] {
                open[prev1]
            } else {
                close[prev1]
            })
            && close[current] <= close[prev2]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 10,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= (open[prev_period] - close[prev_period]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[prev_period] - low[prev_period];
        i += 1;
    }

    0
}

pub fn tc_four_price_doji(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = f64::abs(open[i as usize] - close[i as usize]);
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (f64::abs(open[i as usize] - close[i as usize]) < (options.body_none * avg_total))
            && (upper < (options.wick_none * avg_total))
            && (lower < (options.wick_none * avg_total))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 11,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}
pub fn tc_gravestone_doji(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];

        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = f64::abs(open_i - close_i);
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (f64::abs(open_i - close_i) < (options.body_none * avg_total))
            && ((high_i - top) > (options.wick_long * avg_body))
            && ((bottom - low_i) < (options.wick_none * avg_total))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 12,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        let prev_i = i - period;
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[prev_i as usize] - close[prev_i as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[prev_i as usize] - low[prev_i as usize];
        i += 1;
    }

    0
}

pub fn tc_hammer(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = f64::abs(open[i as usize] - close[i as usize]);
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if ((((i >= 1) && (f64::abs(open[i as usize] - close[i as usize]) < (options.body_short * avg_body)))
            && ((high[i as usize] - top) < (options.wick_none * avg_total)))
            && ((bottom - low[i as usize]) > (options.wick_long * avg_body)))
            && ((if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) <= (low[(i - 1) as usize] + (options.near * avg_total)))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 13,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_hanging_man(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = f64::abs(open[i as usize] - close[i as usize]);
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if ((((i >= 1)
            && (f64::abs(open[i as usize] - close[i as usize]) < (options.body_short * avg_body)))
            && ((high[i as usize] - top) < (options.wick_none * avg_total)))
            && ((bottom - low[i as usize]) > (options.wick_long * avg_body)))
            && ((if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) >= (high[(i - 1) as usize] - (options.near * avg_total)))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 14,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_inverted_hammer(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    if period < 1 {
        return 1;
    }
    
    if size < period {
        return 0;
    }
    
    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }
    
    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];
        
        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = (open_i - close_i).abs();
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;
        
        let condition1 = i >= 1;
        let condition2 = body < (options.body_short * avg_body);
        let condition3 = upper > (options.wick_long * avg_body);
        let condition4 = lower < (options.wick_none * avg_total);
        let prev_top = if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        };
        let condition5 = top <= prev_top;
        
        if condition1 && condition2 && condition3 && condition4 && condition5 {
            let hit = TcHit {
                index: i,
                patterns: 1 << 15,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }
        
        avg_body_sum += body;
        avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }
    
    0
}
pub fn tc_long_legged_doji(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    // Initialize sums for the first period elements
    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period;
    while i < size {
        let current = i as usize;
        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = f64::abs(open[current] - close[current]);
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if f64::abs(open[current] - close[current]) < (options.body_none * avg_total)
            && (upper > (options.wick_long * avg_body))
            && (lower > (options.wick_long * avg_body))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 16,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[current - period as usize] - close[current - period as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[current - period as usize] - low[current - period as usize];

        i += 1;
    }

    0
}

pub fn tc_marubozu(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_val = open[i as usize];
        let close_val = close[i as usize];
        let high_val = high[i as usize];
        let low_val = low[i as usize];

        let top = if open_val > close_val { open_val } else { close_val };
        let bottom = if open_val < close_val { open_val } else { close_val };
        let body = f64::abs(open_val - close_val);
        let total = high_val - low_val;
        let upper = high_val - top;
        let lower = bottom - low_val;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (body > (options.body_long * avg_body))
            && (upper < (options.wick_none * avg_total))
            && (lower < (options.wick_none * avg_total))
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 17,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_morning_doji_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let current_open = open[i as usize];
        let current_close = close[i as usize];
        let current_high = high[i as usize];
        let current_low = low[i as usize];

        let top = if current_open > current_close {
            current_open
        } else {
            current_close
        };
        let bottom = if current_open < current_close {
            current_open
        } else {
            current_close
        };
        let body = f64::abs(current_open - current_close);
        let total = current_high - current_low;
        let upper = current_high - top;
        let lower = bottom - current_low;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 2 {
            let prev2_open = open[(i - 2) as usize];
            let prev2_close = close[(i - 2) as usize];
            let prev1_open = open[(i - 1) as usize];
            let prev1_close = close[(i - 1) as usize];

            let prev2_body = f64::abs(prev2_open - prev2_close);
            let prev1_top = if prev1_open > prev1_close {
                prev1_open
            } else {
                prev1_close
            };
            let prev1_bottom = if prev1_open < prev1_close {
                prev1_open
            } else {
                prev1_close
            };
            let prev1_body = f64::abs(prev1_open - prev1_close);

            let condition = (prev2_open > prev2_close)
                && (prev2_body > (options.body_long * avg_body))
                && (prev1_top <= prev1_bottom)
                && (prev1_body < (options.body_none * avg_total))
                && (current_open < current_close)
                && (bottom >= prev1_top)
                && (current_close >= prev2_close);

            if condition {
                let hit = TcHit {
                    index: i,
                    patterns: 1 << 18,
                };
                let r = tc_result_add(output, hit);
                if r != 0 {
                    return r;
                }
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_morning_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    // Initialize sums for the first period elements
    for i in 0..period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        let current = i as usize;
        let prev_1 = (i - 1) as usize;
        let prev_2 = (i - 2) as usize;
        let prev_period = (i - period) as usize;

        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = (open[current] - close[current]).abs();
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        // Check the complex condition
        if i >= 2
            && open[prev_2] > close[prev_2]
            && (open[prev_2] - close[prev_2]).abs() > (options.body_long * avg_body)
            && (if open[prev_1] > close[prev_1] {
                open[prev_1]
            } else {
                close[prev_1]
            }) <= (if open[prev_1 - 1] < close[prev_1 - 1] {
                open[prev_1 - 1]
            } else {
                close[prev_1 - 1]
            })
            && (open[prev_1] - close[prev_1]).abs() < (options.body_short * avg_body)
            && open[current] < close[current]
            && (if open[current] < close[current] {
                open[current]
            } else {
                close[current]
            }) >= (if open[prev_1] > close[prev_1] {
                open[prev_1]
            } else {
                close[prev_1]
            })
            && close[current] >= close[prev_2]
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 19,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= (open[prev_period] - close[prev_period]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[prev_period] - low[prev_period];

        i += 1;
    }

    0
}

pub fn tc_shooting_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }
    
    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }
    
    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = (open[i as usize] - close[i as usize]).abs();
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;
        
        if i >= 1
            && body < (options.body_short * avg_body)
            && upper > (options.wick_long * avg_body)
            && lower < (options.wick_none * avg_total)
            && bottom >= if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 20,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }
        
        avg_body_sum += body;
        avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }
    
    0
}

pub fn tc_spinning_top(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let current = i as usize;
        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = f64::abs(open[current] - close[current]);
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (body < (options.body_short * avg_body))
            && (upper > body)
            && (lower > body)
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 21,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        let prev_period = (i - period) as usize;
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[prev_period] - close[prev_period]);
        avg_total_sum += total;
        avg_total_sum -= high[prev_period] - low[prev_period];

        i += 1;
    }

    0
}

pub fn tc_star(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let top = if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let bottom = if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        };
        let body = f64::abs(open[i as usize] - close[i as usize]);
        let total = high[i as usize] - low[i as usize];
        let upper = high[i as usize] - top;
        let lower = bottom - low[i as usize];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if (i >= 1) && ((low[i as usize] >= high[(i - 1) as usize]) || (high[i as usize] <= low[(i - 1) as usize])) {
            let hit = TcHit {
                index: i,
                patterns: 1 << 22,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_three_black_crows(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_i = open[i as usize];
        let close_i = close[i as usize];
        let high_i = high[i as usize];
        let low_i = low[i as usize];

        let top = if open_i > close_i { open_i } else { close_i };
        let bottom = if open_i < close_i { open_i } else { close_i };
        let body = (open_i - close_i).abs();
        let total = high_i - low_i;
        let upper = high_i - top;
        let lower = bottom - low_i;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if i >= 2 {
            let open_i2 = open[(i - 2) as usize];
            let close_i2 = close[(i - 2) as usize];
            let open_i1 = open[(i - 1) as usize];
            let close_i1 = close[(i - 1) as usize];

            let prev_top = if open_i1 > close_i1 { open_i1 } else { close_i1 };
            let prev_bottom = if open_i1 < close_i1 { open_i1 } else { close_i1 };
            let prev_prev_top = if open_i2 > close_i2 { open_i2 } else { close_i2 };
            let prev_prev_bottom = if open_i2 < close_i2 { open_i2 } else { close_i2 };

            if (open_i2 > close_i2)
                && (open_i1 > close_i1)
                && (open_i > close_i)
                && (open_i1 < prev_prev_top)
                && (open_i1 > prev_prev_bottom)
                && (open_i < prev_top)
                && (open_i > prev_bottom)
            {
                let hit = TcHit {
                    index: i,
                    patterns: 1 << 23,
                };
                let r = tc_result_add(output, hit);
                if r != 0 {
                    return r;
                }
            }
        }

        avg_body_sum += body;
        avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}

pub fn tc_three_white_soldiers(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    let mut i = 0;

    // Initial period calculation
    for i in 0..period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        let current = i as usize;
        let prev1 = (i - 1) as usize;
        let prev2 = (i - 2) as usize;
        let prev_period = (i - period) as usize;

        let top = if open[current] > close[current] {
            open[current]
        } else {
            close[current]
        };
        let bottom = if open[current] < close[current] {
            open[current]
        } else {
            close[current]
        };
        let body = (open[current] - close[current]).abs();
        let total = high[current] - low[current];
        let upper = high[current] - top;
        let lower = bottom - low[current];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        // Check the complex condition
        if i >= 2
            && open[prev2] < close[prev2]
            && open[prev1] < close[prev1]
            && open[current] < close[current]
            && open[prev1] < open[prev2].max(close[prev2])
            && open[prev1] > open[prev2].min(close[prev2])
            && open[current] < open[prev1].max(close[prev1])
            && open[current] > open[prev1].min(close[prev1])
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 24,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= (open[prev_period] - close[prev_period]).abs();
        avg_total_sum += total;
        avg_total_sum -= high[prev_period] - low[prev_period];

        i += 1;
    }

    0
}
pub fn tc_white_marubozu(
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    while i < period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        let open_val = open[i as usize];
        let close_val = close[i as usize];
        let high_val = high[i as usize];
        let low_val = low[i as usize];

        let top = if open_val > close_val { open_val } else { close_val };
        let bottom = if open_val < close_val { open_val } else { close_val };
        let body = f64::abs(open_val - close_val);
        let total = high_val - low_val;
        let upper = high_val - top;
        let lower = bottom - low_val;
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        if f64::abs(open_val - close_val) > (options.body_long * avg_body)
            && (high_val - top) < (options.wick_none * avg_total)
            && (bottom - low_val) < (options.wick_none * avg_total)
            && open_val < close_val
        {
            let hit = TcHit {
                index: i,
                patterns: 1 << 25,
            };
            let r = tc_result_add(output, hit);
            if r != 0 {
                return r;
            }
        }

        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
        i += 1;
    }

    0
}
pub fn tc_run(
    patterns: tc_set,
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    tc_result_reset(output);

    // Check if patterns is a single bit flag
    if (patterns & (patterns - 1)) == 0 {
        if patterns == 1 << 0 {
            return tc_abandoned_baby_bear(size, inputs, options, output);
        }
        if patterns == 1 << 1 {
            return tc_abandoned_baby_bull(size, inputs, options, output);
        }
        if patterns == 1 << 2 {
            return tc_big_black_candle(size, inputs, options, output);
        }
        if patterns == 1 << 3 {
            return tc_big_white_candle(size, inputs, options, output);
        }
        if patterns == 1 << 4 {
            return tc_black_marubozu(size, inputs, options, output);
        }
        if patterns == 1 << 5 {
            return tc_doji(size, inputs, options, output);
        }
        if patterns == 1 << 6 {
            return tc_dragonfly_doji(size, inputs, options, output);
        }
        if patterns == 1 << 7 {
            return tc_engulfing_bear(size, inputs, options, output);
        }
        if patterns == 1 << 8 {
            return tc_engulfing_bull(size, inputs, options, output);
        }
        if patterns == 1 << 9 {
            return tc_evening_doji_star(size, inputs, options, output);
        }
        if patterns == 1 << 10 {
            return tc_evening_star(size, inputs, options, output);
        }
        if patterns == 1 << 11 {
            return tc_four_price_doji(size, inputs, options, output);
        }
        if patterns == 1 << 12 {
            return tc_gravestone_doji(size, inputs, options, output);
        }
        if patterns == 1 << 13 {
            return tc_hammer(size, inputs, options, output);
        }
        if patterns == 1 << 14 {
            return tc_hanging_man(size, inputs, options, output);
        }
        if patterns == 1 << 15 {
            return tc_inverted_hammer(size, inputs, options, output);
        }
        if patterns == 1 << 16 {
            return tc_long_legged_doji(size, inputs, options, output);
        }
        if patterns == 1 << 17 {
            return tc_marubozu(size, inputs, options, output);
        }
        if patterns == 1 << 18 {
            return tc_morning_doji_star(size, inputs, options, output);
        }
        if patterns == 1 << 19 {
            return tc_morning_star(size, inputs, options, output);
        }
        if patterns == 1 << 20 {
            return tc_shooting_star(size, inputs, options, output);
        }
        if patterns == 1 << 21 {
            return tc_spinning_top(size, inputs, options, output);
        }
        if patterns == 1 << 22 {
            return tc_star(size, inputs, options, output);
        }
        if patterns == 1 << 23 {
            return tc_three_black_crows(size, inputs, options, output);
        }
        if patterns == 1 << 24 {
            return tc_three_white_soldiers(size, inputs, options, output);
        }
        if patterns == 1 << 25 {
            return tc_white_marubozu(size, inputs, options, output);
        }
    }

    let open = inputs[0];
    let high = inputs[1];
    let low = inputs[2];
    let close = inputs[3];
    let period = options.period;
    let div = 1.0 / period as TC_REAL;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    // Initialize sums for first period elements
    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period as usize;
    while i < size as usize {
        let top = if open[i] > close[i] { open[i] } else { close[i] };
        let bottom = if open[i] < close[i] { open[i] } else { close[i] };
        let body = f64::abs(open[i] - close[i]);
        let total = high[i] - low[i];
        let upper = high[i] - top;
        let lower = bottom - low[i];
        let avg_body = avg_body_sum * div;
        let avg_total = avg_total_sum * div;

        // Check each pattern condition
        macro_rules! check_pattern {
            ($pattern:expr, $condition:expr) => {
                if (patterns & $pattern) != 0 && $condition {
                    let hit = TcHit {
                        index: i as i32,
                        patterns: $pattern,
                    };
                    let r = tc_result_add(output, hit);
                    if r != 0 {
                        return r;
                    }
                }
            };
        }

        // Pattern 0: Abandoned Baby Bear
        check_pattern!(
            1 << 0,
            i >= 2
                && open[i - 2] < close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && low[i - 1] >= high[i - 2]
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_none * avg_total
                && open[i] > close[i]
                && high[i] <= low[i - 1]
                && close[i] <= close[i - 2]
        );

        // Pattern 1: Abandoned Baby Bull
        check_pattern!(
            1 << 1,
            i >= 2
                && open[i - 2] > close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && high[i - 1] <= low[i - 2]
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_none * avg_total
                && open[i] < close[i]
                && low[i] >= high[i - 1]
                && close[i] >= close[i - 2]
        );

        // Pattern 2: Big Black Candle
        check_pattern!(
            1 << 2,
            open[i] > close[i] && f64::abs(open[i] - close[i]) > options.body_long * avg_body
        );

        // Pattern 3: Big White Candle
        check_pattern!(
            1 << 3,
            open[i] < close[i] && f64::abs(open[i] - close[i]) > options.body_long * avg_body
        );

        // Pattern 4: Black Marubozu
        check_pattern!(
            1 << 4,
            f64::abs(open[i] - close[i]) > options.body_long * avg_body
                && upper < options.wick_none * avg_total
                && lower < options.wick_none * avg_total
                && open[i] > close[i]
        );

        // Pattern 5: Doji
        check_pattern!(
            1 << 5,
            f64::abs(open[i] - close[i]) < options.body_none * avg_total
        );

        // Pattern 6: Dragonfly Doji
        check_pattern!(
            1 << 6,
            f64::abs(open[i] - close[i]) < options.body_none * avg_total
                && upper < options.wick_none * avg_total
                && lower > options.wick_long * avg_body
        );

        // Pattern 7: Engulfing Bear
        check_pattern!(
            1 << 7,
            i >= 1
                && open[i] > close[i]
                && open[i - 1] < close[i - 1]
                && close[i] < open[i - 1]
                && open[i] > close[i - 1]
        );

        // Pattern 8: Engulfing Bull
        check_pattern!(
            1 << 8,
            i >= 1
                && open[i] < close[i]
                && open[i - 1] > close[i - 1]
                && close[i] > open[i - 1]
                && open[i] < close[i - 1]
        );

        // Pattern 9: Evening Doji Star
        check_pattern!(
            1 << 9,
            i >= 2
                && open[i - 2] < close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && f64::min(open[i - 1], close[i - 1]) >= f64::max(open[i - 2], close[i - 2])
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_none * avg_total
                && open[i] > close[i]
                && f64::max(open[i], close[i]) <= f64::min(open[i - 1], close[i - 1])
                && close[i] <= close[i - 2]
        );

        // Pattern 10: Evening Star
        check_pattern!(
            1 << 10,
            i >= 2
                && open[i - 2] < close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && f64::min(open[i - 1], close[i - 1]) >= f64::max(open[i - 2], close[i - 2])
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_short * avg_body
                && open[i] > close[i]
                && f64::max(open[i], close[i]) <= f64::min(open[i - 1], close[i - 1])
                && close[i] <= close[i - 2]
        );

        // Pattern 11: Four Price Doji
        check_pattern!(
            1 << 11,
            f64::abs(open[i] - close[i]) < options.body_none * avg_total
                && upper < options.wick_none * avg_total
                && lower < options.wick_none * avg_total
        );

        // Pattern 12: Gravestone Doji
        check_pattern!(
            1 << 12,
            f64::abs(open[i] - close[i]) < options.body_none * avg_total
                && upper > options.wick_long * avg_body
                && lower < options.wick_none * avg_total
        );

        // Pattern 13: Hammer
        check_pattern!(
            1 << 13,
            i >= 1
                && f64::abs(open[i] - close[i]) < options.body_short * avg_body
                && upper < options.wick_none * avg_total
                && lower > options.wick_long * avg_body
                && f64::min(open[i], close[i]) <= low[i - 1] + options.near * avg_total
        );

        // Pattern 14: Hanging Man
        check_pattern!(
            1 << 14,
            i >= 1
                && f64::abs(open[i] - close[i]) < options.body_short * avg_body
                && upper < options.wick_none * avg_total
                && lower > options.wick_long * avg_body
                && f64::min(open[i], close[i]) >= high[i - 1] - options.near * avg_total
        );

        // Pattern 15: Inverted Hammer
        check_pattern!(
            1 << 15,
            i >= 1
                && f64::abs(open[i] - close[i]) < options.body_short * avg_body
                && upper > options.wick_long * avg_body
                && lower < options.wick_none * avg_total
                && f64::max(open[i], close[i]) <= f64::min(open[i - 1], close[i - 1])
        );

        // Pattern 16: Long Legged Doji
        check_pattern!(
            1 << 16,
            f64::abs(open[i] - close[i]) < options.body_none * avg_total
                && upper > options.wick_long * avg_body
                && lower > options.wick_long * avg_body
        );

        // Pattern 17: Marubozu
        check_pattern!(
            1 << 17,
            f64::abs(open[i] - close[i]) > options.body_long * avg_body
                && upper < options.wick_none * avg_total
                && lower < options.wick_none * avg_total
        );

        // Pattern 18: Morning Doji Star
        check_pattern!(
            1 << 18,
            i >= 2
                && open[i - 2] > close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && f64::max(open[i - 1], close[i - 1]) <= f64::min(open[i - 2], close[i - 2])
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_none * avg_total
                && open[i] < close[i]
                && f64::min(open[i], close[i]) >= f64::max(open[i - 1], close[i - 1])
                && close[i] >= close[i - 2]
        );

        // Pattern 19: Morning Star
        check_pattern!(
            1 << 19,
            i >= 2
                && open[i - 2] > close[i - 2]
                && f64::abs(open[i - 2] - close[i - 2]) > options.body_long * avg_body
                && f64::max(open[i - 1], close[i - 1]) <= f64::min(open[i - 2], close[i - 2])
                && f64::abs(open[i - 1] - close[i - 1]) < options.body_short * avg_body
                && open[i] < close[i]
                && f64::min(open[i], close[i]) >= f64::max(open[i - 1], close[i - 1])
                && close[i] >= close[i - 2]
        );

        // Pattern 20: Shooting Star
        check_pattern!(
            1 << 20,
            i >= 1
                && f64::abs(open[i] - close[i]) < options.body_short * avg_body
                && upper > options.wick_long * avg_body
                && lower < options.wick_none * avg_total
                && f64::min(open[i], close[i]) >= f64::max(open[i - 1], close[i - 1])
        );

        // Pattern 21: Spinning Top
        check_pattern!(
            1 << 21,
            f64::abs(open[i] - close[i]) < options.body_short * avg_body
                && upper > f64::abs(open[i] - close[i])
                && lower > f64::abs(open[i] - close[i])
        );

        // Pattern 22: Star
        check_pattern!(
            1 << 22,
            i >= 1 && (low[i] >= high[i - 1] || high[i] <= low[i - 1])
        );

        // Pattern 23: Three Black Crows
        check_pattern!(
            1 << 23,
            i >= 2
                && open[i - 2] > close[i - 2]
                && open[i - 1] > close[i - 1]
                && open[i] > close[i]
                && open[i - 1] < f64::max(open[i - 2], close[i - 2])
                && open[i - 1] > f64::min(open[i - 2], close[i - 2])
                && open[i] < f64::max(open[i - 1], close[i - 1])
                && open[i] > f64::min(open[i - 1], close[i - 1])
        );

        // Pattern 24: Three White Soldiers
        check_pattern!(
            1 << 24,
            i >= 2
                && open[i - 2] < close[i - 2]
                && open[i - 1] < close[i - 1]
                && open[i] < close[i]
                && open[i - 1] < f64::max(open[i - 2], close[i - 2])
                && open[i - 1] > f64::min(open[i - 2], close[i - 2])
                && open[i] < f64::max(open[i - 1], close[i - 1])
                && open[i] > f64::min(open[i - 1], close[i - 1])
        );

        // Pattern 25: White Marubozu
        check_pattern!(
            1 << 25,
            f64::abs(open[i] - close[i]) > options.body_long * avg_body
                && upper < options.wick_none * avg_total
                && lower < options.wick_none * avg_total
                && open[i] < close[i]
        );

        // Update rolling sums
        avg_body_sum += body;
        avg_body_sum -= f64::abs(open[i - period as usize] - close[i - period as usize]);
        avg_total_sum += total;
        avg_total_sum -= high[i - period as usize] - low[i - period as usize];

        i += 1;
    }

    0
}
