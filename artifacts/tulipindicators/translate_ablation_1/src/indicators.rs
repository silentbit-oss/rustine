use crate::*;
use lazy_static::lazy_static;
use std::cmp::Ordering;
use std::sync::Mutex;

pub fn ti_version() -> &'static str {
    "0.9.2"
}
pub fn ti_build() -> i64 {
    1645649572
}
pub fn ti_indicator_count() -> i32 {
    104
}
pub fn ti_stream_get_progress(stream: &TiStream) -> i32 {
    stream.progress
}
pub fn ti_find_indicator(name: Option<&str>) -> Option<&'static TiIndicatorInfo> {
    // Check for None (equivalent to NULL in C)
    let name = name?;

    // We need to keep the lock guard alive for the lifetime of the returned reference
    // Since we can't do that directly, we'll return the index and then get the reference
    let index = {
        let ti_indicators = TI_INDICATORS.lock().unwrap();
        let mut imin = 0;
        let mut imax = ti_indicators.len().saturating_sub(2); // -2 as in original C code

        let mut found_index = None;
        while imax >= imin {
            let i = imin + ((imax - imin) / 2);
            let indicator_name = match &ti_indicators[i].name {
                Some(n) => n,
                None => return None, // If name is None, we can't compare
            };

            match name.cmp(indicator_name.as_str()) {
                Ordering::Equal => {
                    found_index = Some(i);
                    break;
                }
                Ordering::Greater => imin = i + 1,
                Ordering::Less => imax = i.saturating_sub(1),
            }
        }
        found_index
    };

    // Now we can safely return a reference since we're not holding the lock
    index.map(|i| {
        let ti_indicators = TI_INDICATORS.lock().unwrap();
        unsafe { &*(&ti_indicators[i] as *const TiIndicatorInfo) }
    })
}
pub fn ti_stream_run(stream: &mut TiStream, size: i32, inputs: &[&[f64]], outputs: &mut [&mut [f64]]) -> i32 {
    let indicator = &TI_INDICATORS.lock().unwrap()[stream.index as usize];
    if let Some(stream_run_fn) = &indicator.stream_run {
        stream_run_fn(stream, size, inputs, outputs)
    } else {
        // Return error code -1 for invalid operation (function pointer not available)
        -1
    }
}
pub fn ti_stream_free(stream: TiStream) {
    // Lock the TI_INDICATORS mutex to safely access the vector
    let indicators = TI_INDICATORS.lock().unwrap();
    
    // Get the indicator info at the stream's index
    let indicator_info = &indicators[stream.index as usize];
    
    // Call the stream_free function for this indicator if it exists
    if let Some(stream_free_fn) = &indicator_info.stream_free {
        stream_free_fn(stream);
    }
}
pub fn ti_stream_get_info(stream: &TiStream) -> Option<&'static TiIndicatorInfo> {
    let indicators = TI_INDICATORS.lock().unwrap();
    let index = stream.index as usize;
    if index < indicators.len() {
        unsafe { Some(&*(&indicators[index] as *const TiIndicatorInfo)) }
    } else {
        None
    }
}
