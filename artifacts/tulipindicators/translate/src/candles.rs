use crate::*;
use std::cmp::Ordering;
use std::convert::TryInto;
use std::f64;

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
pub fn tc_result_new() -> Option<Box<TcResult>> {
    Some(Box::new(TcResult {
        progress: 0,
        space: 0,
        count: 0,
        pattern_count: 0,
        hits: None,
    }))
}
pub fn tc_result_free(result: Option<Box<TcResult>>) {
    // In Rust, we don't need to explicitly free memory - Drop trait handles it
    // The Option<Box<TcResult>> will be properly dropped when it goes out of scope
    // The contained Vec<TcHit> in hits will also be automatically dropped
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
pub fn tc_find_candle(name: Option<&str>) -> Option<&'static TcCandleInfo> {
    // Check for None (equivalent to NULL in C)
    let name = name?;

    // We need to keep the lock for the lifetime of the returned reference
    let tc_candles = TC_CANDLES.lock().unwrap();
    
    let mut imin = 0;
    let mut imax = tc_candles.len().checked_sub(2)?; // -2 becomes checked_sub(2) for safety

    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        let candle_name = tc_candles[i].name.as_deref()?; // Get &str from Option<String>

        match name.cmp(candle_name) {
            Ordering::Equal => {
                // Unsafe block needed because we're extending the lifetime
                // This is safe because TC_CANDLES is static and we're keeping the lock
                unsafe {
                    return Some(&*(&tc_candles[i] as *const TcCandleInfo));
                }
            }
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
    if index < result.count && result.hits.as_ref().map_or(false, |hits| index >= 0 && (index as usize) < hits.len()) {
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
    
    // Check if we need to merge with the last hit
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

    // Handle initial allocation or resizing
    match result.hits {
        None => {
            result.space = 2048;
            result.count = 0;
            result.hits = Some(Vec::with_capacity(result.space.try_into().unwrap()));
        },
        Some(ref mut hits) if hits.len() == result.space.try_into().unwrap() => {
            let new_capacity = result.space * 2;
            hits.reserve_exact(new_capacity.try_into().unwrap());
            result.space = new_capacity;
        },
        _ => {}
    }

    // Add the new hit
    if let Some(hits) = result.hits.as_mut() {
        hits.push(hit);
        result.count += 1;
    }

    0
}
pub fn tc_get_info(pattern: Option<tc_set>) -> Option<&'static TcCandleInfo> {
    // Check for NULL equivalent (None)
    let pattern = pattern?;

    let k = pattern & (!(pattern - 1));
    let mut imin = 0;
    let mut imax = (TC_CANDLES.lock().unwrap().len() - 1) as i32; // -1 because Rust uses exclusive upper bounds

    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        let current_pattern = {
            let candles = TC_CANDLES.lock().unwrap();
            candles[i as usize].pattern
        };

        if k == current_pattern {
            // Get a reference to the static data
            let candles = TC_CANDLES.lock().unwrap();
            let info = &candles[i as usize];
            // SAFETY: TC_CANDLES is static, so the reference is valid for 'static
            unsafe { return Some(std::mem::transmute::<_, &'static TcCandleInfo>(info)); }
        } else if k > current_pattern {
            imin = i + 1;
        } else {
            imax = i - 1;
        }
    }

    Option::None
}

pub fn helper_tc_abandoned_baby_bear_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    if i >= 2
        && open[(i - 2) as usize] < close[(i - 2) as usize]
        && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
        && low[(i - 1) as usize] >= high[(i - 2) as usize]
        && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
        && open[i as usize] > close[i as usize]
        && high[i as usize] <= low[(i - 1) as usize]
        && close[i as usize] <= close[(i - 2) as usize]
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 0,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_abandoned_baby_bear_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_abandoned_baby_bull_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if i >= 2
        && open[(i - 2) as usize] > close[(i - 2) as usize]
        && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
        && high[(i - 1) as usize] <= low[(i - 2) as usize]
        && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
        && open[i as usize] < close[i as usize]
        && low[i as usize] >= high[(i - 1) as usize]
        && close[i as usize] >= close[(i - 2) as usize]
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 1,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for idx in 0..period {
        let idx = idx as usize;
        avg_body_sum += (open[idx] - close[idx]).abs();
        avg_total_sum += high[idx] - low[idx];
        i += 1;
    }

    while i < size {
        helper_tc_abandoned_baby_bull_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_big_black_candle_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    if open[i as usize] > close[i as usize] && (open[i as usize] - close[i as usize]).abs() > (options.body_long * avg_body) {
        let hit = TcHit {
            index: i,
            patterns: 1 << 2,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    let mut i = 0;

    for idx in 0..period as usize {
        avg_body_sum += f64::abs(open[idx] - close[idx]);
        avg_total_sum += high[idx] - low[idx];
        i += 1;
    }

    while i < size {
        helper_tc_big_black_candle_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_big_white_candle_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if open[i as usize] < close[i as usize]
        && (open[i as usize] - close[i as usize]).abs() > (options.body_long * avg_body)
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 3,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    for i in 0..period {
        let i_usize = i as usize;
        avg_body_sum += (open[i_usize] - close[i_usize]).abs();
        avg_total_sum += high[i_usize] - low[i_usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_big_white_candle_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_black_marubozu_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> i32 {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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

    if ((open[i as usize] - close[i as usize]).abs() > (options.body_long * avg_body))
        && (upper < (options.wick_none * avg_total))
        && (lower < (options.wick_none * avg_total))
        && (open[i as usize] > close[i as usize])
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
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;

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

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_black_marubozu_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_doji_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if (open[i as usize] - close[i as usize]).abs() < (options.body_none * avg_total) {
        let hit = TcHit {
            index: i,
            patterns: 1 << 5,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_doji_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_dragonfly_doji_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    if ((open[i as usize] - close[i as usize]).abs() < (options.body_none * avg_total))
        && (upper < (options.wick_none * avg_total))
        && (lower > (options.wick_long * avg_body))
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 6,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_dragonfly_doji_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}
pub fn helper_tc_engulfing_bear_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> i32 {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    // These variables are unused in the C code, so we don't need to do anything with them
    let _ = (top, bottom, body, total, upper, lower, avg_body, avg_total);
    
    if i >= 1 
        && open[i as usize] > close[i as usize] 
        && open[(i - 1) as usize] < close[(i - 1) as usize] 
        && close[i as usize] < open[(i - 1) as usize] 
        && open[i as usize] > close[(i - 1) as usize] 
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 7,
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
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
    
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
        helper_tc_engulfing_bear_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }
    
    0
}
pub fn helper_tc_engulfing_bull_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> i32 {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    // Silenced unused variables (equivalent to C's (void) casts)
    let _ = (top, bottom, body, total, upper, lower, avg_body, avg_total);
    
    if i >= 1 
        && open[i as usize] < close[i as usize] 
        && open[(i - 1) as usize] > close[(i - 1) as usize] 
        && close[i as usize] > open[(i - 1) as usize] 
        && open[i as usize] < close[(i - 1) as usize] 
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
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
    
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
        helper_tc_engulfing_bull_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_evening_doji_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if i >= 2
        && open[(i - 2) as usize] < close[(i - 2) as usize]
        && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > (options.body_long * avg_body)
        && (if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        }) >= (if open[(i - 2) as usize] > close[(i - 2) as usize] {
            open[(i - 2) as usize]
        } else {
            close[(i - 2) as usize]
        })
        && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < (options.body_none * avg_total)
        && open[i as usize] > close[i as usize]
        && (if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        }) <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        })
        && close[i as usize] <= close[(i - 2) as usize]
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 9,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period;
    while (i as usize) < size as usize {
        helper_tc_evening_doji_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_evening_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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

    if i >= 2
        && open[(i - 2) as usize] < close[(i - 2) as usize]
        && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
        && (if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        }) >= (if open[(i - 2) as usize] > close[(i - 2) as usize] {
            open[(i - 2) as usize]
        } else {
            close[(i - 2) as usize]
        })
        && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_short * avg_body
        && open[i as usize] > close[i as usize]
        && (if open[i as usize] > close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        }) <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        })
        && close[i as usize] <= close[(i - 2) as usize]
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 10,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    
    for i in 0..period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
    }
    
    let mut i = period;
    while i < size {
        helper_tc_evening_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }
    
    0
}

pub fn helper_tc_four_price_doji_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> Option<i32> {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if ((open[i as usize] - close[i as usize]).abs() < (options.body_none * avg_total))
        && (upper < (options.wick_none * avg_total))
        && (lower < (options.wick_none * avg_total))
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 11,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return Some(r);
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;

    None
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

    for i in 0..period {
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_four_price_doji_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_gravestone_doji_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> Option<i32> {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if ((open[i as usize] - close[i as usize]).abs() < (options.body_none * avg_total))
        && (upper > (options.wick_long * avg_body))
        && (lower < (options.wick_none * avg_total))
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 12,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return Some(r);
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;

    None
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
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        helper_tc_gravestone_doji_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_hammer_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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
        && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
        && upper < options.wick_none * avg_total
        && lower > options.wick_long * avg_body
        && bottom <= low[(i - 1) as usize] + options.near * avg_total
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 13,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
        avg_body_sum += (open[i as usize] - close[i as usize]).abs();
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        helper_tc_hammer_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_hanging_man_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    if i >= 1
        && f64::abs(open[i as usize] - close[i as usize]) < options.body_short * avg_body
        && upper < options.wick_none * avg_total
        && lower > options.wick_long * avg_body
        && bottom >= high[(i - 1) as usize] - options.near * avg_total
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 14,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period {
        let i = i as usize;
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period;
    while i < size {
        helper_tc_hanging_man_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_inverted_hammer_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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
        && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
        && upper > options.wick_long * avg_body
        && lower < options.wick_none * avg_total
        && top <= if open[(i - 1) as usize] < close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        }
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 15,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
        i += 1;
    }

    while i < size {
        helper_tc_inverted_hammer_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_long_legged_doji_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if ((open[i as usize] - close[i as usize]).abs() < (options.body_none * avg_total))
        && (upper > (options.wick_long * avg_body))
        && (lower > (options.wick_long * avg_body))
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 16,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period;
    while i < size {
        helper_tc_long_legged_doji_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_marubozu_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    if ((open[i as usize] - close[i as usize]).abs() > (options.body_long * avg_body))
        && ((high[i as usize] - top) < (options.wick_none * avg_total))
        && ((bottom - low[i as usize]) < (options.wick_none * avg_total))
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 17,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period as usize {
        avg_body_sum += f64::abs(open[i] - close[i]);
        avg_total_sum += high[i] - low[i];
    }

    let mut i = period;
    while i < size {
        helper_tc_marubozu_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_morning_doji_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if i >= 2
        && (open[(i - 2) as usize] > close[(i - 2) as usize])
        && ((open[(i - 2) as usize] - close[(i - 2) as usize]).abs()
            > (options.body_long * avg_body))
        && (if open[(i - 1) as usize] > close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        } <= if open[(i - 2) as usize] < close[(i - 2) as usize] {
            open[(i - 2) as usize]
        } else {
            close[(i - 2) as usize]
        })
        && ((open[(i - 1) as usize] - close[(i - 1) as usize]).abs()
            < (options.body_none * avg_total))
        && (open[i as usize] < close[i as usize])
        && (if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        } >= if open[(i - 1) as usize] > close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        })
        && (close[i as usize] >= close[(i - 2) as usize])
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 18,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    
    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;
    let mut i = 0;

    for idx in 0..period {
        let idx_usize = idx as usize;
        avg_body_sum += (open[idx_usize] - close[idx_usize]).abs();
        avg_total_sum += high[idx_usize] - low[idx_usize];
        i += 1;
    }

    while i < size {
        helper_tc_morning_doji_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_morning_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    // Check the complex condition
    if i >= 2
        && (open[(i - 2) as usize] > close[(i - 2) as usize])
        && ((open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > (options.body_long * avg_body))
        && (if open[(i - 1) as usize] > close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        } <= if open[(i - 2) as usize] < close[(i - 2) as usize] {
            open[(i - 2) as usize]
        } else {
            close[(i - 2) as usize]
        })
        && ((open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < (options.body_short * avg_body))
        && (open[i as usize] < close[i as usize])
        && (if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        } >= if open[(i - 1) as usize] > close[(i - 1) as usize] {
            open[(i - 1) as usize]
        } else {
            close[(i - 1) as usize]
        })
        && (close[i as usize] >= close[(i - 2) as usize])
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 19,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }
    
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    let mut i = 0;
    for idx in 0..period {
        let idx_usize = idx as usize;
        avg_body_sum += f64::abs(open[idx_usize] - close[idx_usize]);
        avg_total_sum += high[idx_usize] - low[idx_usize];
        i += 1;
    }

    while i < size {
        helper_tc_morning_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_shooting_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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

    if i >= 1
        && f64::abs(open[i as usize] - close[i as usize]) < (options.body_short * avg_body)
        && (high[i as usize] - top) > (options.wick_long * avg_body)
        && (bottom - low[i as usize]) < (options.wick_none * avg_total)
        && if open[i as usize] < close[i as usize] {
            open[i as usize]
        } else {
            close[i as usize]
        } >= if open[(i - 1) as usize] > close[(i - 1) as usize] {
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
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_shooting_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}
pub fn helper_tc_spinning_top_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if ((open[i as usize] - close[i as usize]).abs() < (options.body_short * avg_body))
        && (upper > (open[i as usize] - close[i as usize]).abs())
        && (lower > (open[i as usize] - close[i as usize]).abs())
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 21,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return;
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
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
    for idx in 0..period as usize {
        avg_body_sum += f64::abs(open[idx] - close[idx]);
        avg_total_sum += high[idx] - low[idx];
        i += 1;
    }
    
    while i < size {
        helper_tc_spinning_top_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }
    
    0
}
pub fn helper_tc_star_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> Option<i32> {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    let _avg_body = avg_body_sum * div;
    let _avg_total = avg_total_sum * div;

    if (i >= 1) && ((low[i as usize] >= high[(i - 1) as usize]) || (high[i as usize] <= low[(i - 1) as usize])) {
        let hit = TcHit {
            index: i,
            patterns: 1 << 22,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return Some(r);
        }
    }

    avg_body_sum += body;
    avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
    
    None
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
        helper_tc_star_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_three_black_crows_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> i32 {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if i >= 2
        && open[(i - 2) as usize] > close[(i - 2) as usize]
        && open[(i - 1) as usize] > close[(i - 1) as usize]
        && open[i as usize] > close[i as usize]
        && open[(i - 1) as usize]
            < if open[(i - 2) as usize] > close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            }
        && open[(i - 1) as usize]
            > if open[(i - 2) as usize] < close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            }
        && open[i as usize]
            < if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }
        && open[i as usize]
            > if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }
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

    avg_body_sum += body;
    avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;

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

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_three_black_crows_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}

pub fn helper_tc_three_white_soldiers_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> i32 {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;
    
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
    
    // The following variables are unused in the original C code
    let _ = (top, bottom, body, total, upper, lower, avg_body, avg_total);
    
    if i >= 2 
        && open[(i - 2) as usize] < close[(i - 2) as usize]
        && open[(i - 1) as usize] < close[(i - 1) as usize]
        && open[i as usize] < close[i as usize]
        && open[(i - 1) as usize] < {
            let prev_top = if open[(i - 2) as usize] > close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            };
            prev_top
        }
        && open[(i - 1) as usize] > {
            let prev_bottom = if open[(i - 2) as usize] < close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            };
            prev_bottom
        }
        && open[i as usize] < {
            let prev_top = if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            };
            prev_top
        }
        && open[i as usize] > {
            let prev_bottom = if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            };
            prev_bottom
        }
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
    
    avg_body_sum += body;
    avg_body_sum -= f64::abs(open[(i - period) as usize] - close[(i - period) as usize]);
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;
    
    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
    
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
    let mut avg_body_sum = 0.0;
    let mut avg_total_sum = 0.0;

    if period < 1 {
        return 1;
    }
    if size < period {
        return 0;
    }

    for i in 0..period {
        avg_body_sum += f64::abs(open[i as usize] - close[i as usize]);
        avg_total_sum += high[i as usize] - low[i as usize];
    }

    let mut i = period;
    while i < size {
        helper_tc_three_white_soldiers_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}
pub fn helper_tc_white_marubozu_1(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) -> Option<i32> {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    if (body > (options.body_long * avg_body))
        && (upper < (options.wick_none * avg_total))
        && (lower < (options.wick_none * avg_total))
        && (open[i as usize] < close[i as usize])
    {
        let hit = TcHit {
            index: i,
            patterns: 1 << 25,
        };
        let r = tc_result_add(output, hit);
        if r != 0 {
            return Some(r);
        }
    }

    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;

    None
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
        helper_tc_white_marubozu_1(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }

    0
}
pub fn helper_tc_run_2(
    avg_body_sum_ref: &mut TC_REAL,
    avg_total_sum_ref: &mut TC_REAL,
    i_ref: &mut i32,
    patterns: tc_set,
    options: &TcConfig,
    output: &mut TcResult,
    open: &[TC_REAL],
    high: &[TC_REAL],
    low: &[TC_REAL],
    close: &[TC_REAL],
    period: i32,
    div: TC_REAL,
) {
    let mut avg_body_sum = *avg_body_sum_ref;
    let mut avg_total_sum = *avg_total_sum_ref;
    let mut i = *i_ref;

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

    macro_rules! check_pattern {
        ($pattern:expr, $condition:expr) => {
            if (patterns & $pattern) != 0 && $condition {
                let hit = TcHit {
                    index: i,
                    patterns: $pattern,
                };
                let r = tc_result_add(output, hit);
                if r != 0 {
                    return;
                }
            }
        };
    }

    // Pattern 0
    check_pattern!(
        1 << 0,
        i >= 2
            && open[(i - 2) as usize] < close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && low[(i - 1) as usize] >= high[(i - 2) as usize]
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
            && open[i as usize] > close[i as usize]
            && high[i as usize] <= low[(i - 1) as usize]
            && close[i as usize] <= close[(i - 2) as usize]
    );

    // Pattern 1
    check_pattern!(
        1 << 1,
        i >= 2
            && open[(i - 2) as usize] > close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && high[(i - 1) as usize] <= low[(i - 2) as usize]
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
            && open[i as usize] < close[i as usize]
            && low[i as usize] >= high[(i - 1) as usize]
            && close[i as usize] >= close[(i - 2) as usize]
    );

    // Pattern 2
    check_pattern!(
        1 << 2,
        open[i as usize] > close[i as usize]
            && (open[i as usize] - close[i as usize]).abs() > options.body_long * avg_body
    );

    // Pattern 3
    check_pattern!(
        1 << 3,
        open[i as usize] < close[i as usize]
            && (open[i as usize] - close[i as usize]).abs() > options.body_long * avg_body
    );

    // Pattern 4
    check_pattern!(
        1 << 4,
        (open[i as usize] - close[i as usize]).abs() > options.body_long * avg_body
            && upper < options.wick_none * avg_total
            && lower < options.wick_none * avg_total
            && open[i as usize] > close[i as usize]
    );

    // Pattern 5
    check_pattern!(
        1 << 5,
        (open[i as usize] - close[i as usize]).abs() < options.body_none * avg_total
    );

    // Pattern 6
    check_pattern!(
        1 << 6,
        (open[i as usize] - close[i as usize]).abs() < options.body_none * avg_total
            && upper < options.wick_none * avg_total
            && lower > options.wick_long * avg_body
    );

    // Pattern 7
    check_pattern!(
        1 << 7,
        i >= 1
            && open[i as usize] > close[i as usize]
            && open[(i - 1) as usize] < close[(i - 1) as usize]
            && close[i as usize] < open[(i - 1) as usize]
            && open[i as usize] > close[(i - 1) as usize]
    );

    // Pattern 8
    check_pattern!(
        1 << 8,
        i >= 1
            && open[i as usize] < close[i as usize]
            && open[(i - 1) as usize] > close[(i - 1) as usize]
            && close[i as usize] > open[(i - 1) as usize]
            && open[i as usize] < close[(i - 1) as usize]
    );

    // Pattern 9
    check_pattern!(
        1 << 9,
        i >= 2
            && open[(i - 2) as usize] < close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }) >= (if open[(i - 2) as usize] > close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            })
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
            && open[i as usize] > close[i as usize]
            && (if open[i as usize] > close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
            && close[i as usize] <= close[(i - 2) as usize]
    );

    // Pattern 10
    check_pattern!(
        1 << 10,
        i >= 2
            && open[(i - 2) as usize] < close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }) >= (if open[(i - 2) as usize] > close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            })
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_short * avg_body
            && open[i as usize] > close[i as usize]
            && (if open[i as usize] > close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
            && close[i as usize] <= close[(i - 2) as usize]
    );

    // Pattern 11
    check_pattern!(
        1 << 11,
        (open[i as usize] - close[i as usize]).abs() < options.body_none * avg_total
            && upper < options.wick_none * avg_total
            && lower < options.wick_none * avg_total
    );

    // Pattern 12
    check_pattern!(
        1 << 12,
        (open[i as usize] - close[i as usize]).abs() < options.body_none * avg_total
            && upper > options.wick_long * avg_body
            && lower < options.wick_none * avg_total
    );

    // Pattern 13
    check_pattern!(
        1 << 13,
        i >= 1
            && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
            && upper < options.wick_none * avg_total
            && lower > options.wick_long * avg_body
            && (if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) <= low[(i - 1) as usize] + options.near * avg_total
    );

    // Pattern 14
    check_pattern!(
        1 << 14,
        i >= 1
            && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
            && upper < options.wick_none * avg_total
            && lower > options.wick_long * avg_body
            && (if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) >= high[(i - 1) as usize] - options.near * avg_total
    );

    // Pattern 15
    check_pattern!(
        1 << 15,
        i >= 1
            && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
            && upper > options.wick_long * avg_body
            && lower < options.wick_none * avg_total
            && (if open[i as usize] > close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) <= (if open[(i - 1) as usize] < close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
    );

    // Pattern 16
    check_pattern!(
        1 << 16,
        (open[i as usize] - close[i as usize]).abs() < options.body_none * avg_total
            && upper > options.wick_long * avg_body
            && lower > options.wick_long * avg_body
    );

    // Pattern 17
    check_pattern!(
        1 << 17,
        (open[i as usize] - close[i as usize]).abs() > options.body_long * avg_body
            && upper < options.wick_none * avg_total
            && lower < options.wick_none * avg_total
    );

    // Pattern 18
    check_pattern!(
        1 << 18,
        i >= 2
            && open[(i - 2) as usize] > close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && (if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }) <= (if open[(i - 2) as usize] < close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            })
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_none * avg_total
            && open[i as usize] < close[i as usize]
            && (if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) >= (if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
            && close[i as usize] >= close[(i - 2) as usize]
    );

    // Pattern 19
    check_pattern!(
        1 << 19,
        i >= 2
            && open[(i - 2) as usize] > close[(i - 2) as usize]
            && (open[(i - 2) as usize] - close[(i - 2) as usize]).abs() > options.body_long * avg_body
            && (if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            }) <= (if open[(i - 2) as usize] < close[(i - 2) as usize] {
                open[(i - 2) as usize]
            } else {
                close[(i - 2) as usize]
            })
            && (open[(i - 1) as usize] - close[(i - 1) as usize]).abs() < options.body_short * avg_body
            && open[i as usize] < close[i as usize]
            && (if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) >= (if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
            && close[i as usize] >= close[(i - 2) as usize]
    );

    // Pattern 20
    check_pattern!(
        1 << 20,
        i >= 1
            && (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
            && upper > options.wick_long * avg_body
            && lower < options.wick_none * avg_total
            && (if open[i as usize] < close[i as usize] {
                open[i as usize]
            } else {
                close[i as usize]
            }) >= (if open[(i - 1) as usize] > close[(i - 1) as usize] {
                open[(i - 1) as usize]
            } else {
                close[(i - 1) as usize]
            })
    );

    // Pattern 21
    check_pattern!(
        1 << 21,
        (open[i as usize] - close[i as usize]).abs() < options.body_short * avg_body
            && upper > (open[i as usize] - close[i as usize]).abs()
            && lower > (open[i as usize] - close[i as usize]).abs()
    );

    // Pattern 22
    check_pattern!(
        1 << 22,
        i >= 1 && (low[i as usize] >= high[(i - 1) as usize] || high[i as usize] <= low[(i - 1) as usize])
    );

    // Update the sums and indices
    avg_body_sum += body;
    avg_body_sum -= (open[(i - period) as usize] - close[(i - period) as usize]).abs();
    avg_total_sum += total;
    avg_total_sum -= high[(i - period) as usize] - low[(i - period) as usize];
    i += 1;

    *avg_body_sum_ref = avg_body_sum;
    *avg_total_sum_ref = avg_total_sum;
    *i_ref = i;
}
pub fn helper_helper_tc_run_1_1(
    patterns: tc_set,
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    if patterns == 1 << 0 {
        tc_abandoned_baby_bear(size, inputs, options, output)
    } else if patterns == 1 << 1 {
        tc_abandoned_baby_bull(size, inputs, options, output)
    } else if patterns == 1 << 2 {
        tc_big_black_candle(size, inputs, options, output)
    } else if patterns == 1 << 3 {
        tc_big_white_candle(size, inputs, options, output)
    } else if patterns == 1 << 4 {
        tc_black_marubozu(size, inputs, options, output)
    } else if patterns == 1 << 5 {
        tc_doji(size, inputs, options, output)
    } else if patterns == 1 << 6 {
        tc_dragonfly_doji(size, inputs, options, output)
    } else if patterns == 1 << 7 {
        tc_engulfing_bear(size, inputs, options, output)
    } else if patterns == 1 << 8 {
        tc_engulfing_bull(size, inputs, options, output)
    } else if patterns == 1 << 9 {
        tc_evening_doji_star(size, inputs, options, output)
    } else if patterns == 1 << 10 {
        tc_evening_star(size, inputs, options, output)
    } else if patterns == 1 << 11 {
        tc_four_price_doji(size, inputs, options, output)
    } else if patterns == 1 << 12 {
        tc_gravestone_doji(size, inputs, options, output)
    } else if patterns == 1 << 13 {
        tc_hammer(size, inputs, options, output)
    } else if patterns == 1 << 14 {
        tc_hanging_man(size, inputs, options, output)
    } else if patterns == 1 << 15 {
        tc_inverted_hammer(size, inputs, options, output)
    } else if patterns == 1 << 16 {
        tc_long_legged_doji(size, inputs, options, output)
    } else if patterns == 1 << 17 {
        tc_marubozu(size, inputs, options, output)
    } else if patterns == 1 << 18 {
        tc_morning_doji_star(size, inputs, options, output)
    } else if patterns == 1 << 19 {
        tc_morning_star(size, inputs, options, output)
    } else if patterns == 1 << 20 {
        tc_shooting_star(size, inputs, options, output)
    } else if patterns == 1 << 21 {
        tc_spinning_top(size, inputs, options, output)
    } else if patterns == 1 << 22 {
        tc_star(size, inputs, options, output)
    } else if patterns == 1 << 23 {
        tc_three_black_crows(size, inputs, options, output)
    } else if patterns == 1 << 24 {
        tc_three_white_soldiers(size, inputs, options, output)
    } else if patterns == 1 << 25 {
        tc_white_marubozu(size, inputs, options, output)
    } else {
        panic!("Unknown pattern: {}", patterns) // or return an error code if preferred
    }
}
pub fn helper_tc_run_1(
    patterns: tc_set,
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    if (patterns & (patterns - 1)) == 0 {
        helper_helper_tc_run_1_1(patterns, size, inputs, options, output)
    } else {
        0 // Assuming default return value when condition isn't met, adjust if needed
    }
}

pub fn tc_run(
    patterns: tc_set,
    size: i32,
    inputs: &[&[TC_REAL]],
    options: &TcConfig,
    output: &mut TcResult,
) -> i32 {
    tc_result_reset(output);
    {
        helper_tc_run_1(patterns, size, inputs, options, output);
    }
    
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
    for idx in 0..period {
        avg_body_sum += f64::abs(open[idx as usize] - close[idx as usize]);
        avg_total_sum += high[idx as usize] - low[idx as usize];
        i += 1;
    }
    
    while i < size {
        helper_tc_run_2(
            &mut avg_body_sum,
            &mut avg_total_sum,
            &mut i,
            patterns,
            options,
            output,
            open,
            high,
            low,
            close,
            period,
            div,
        );
    }
    
    0
}
