use crate::*;
use std::cmp::Ordering;
use lazy_static::lazy_static;
use std::sync::Mutex;

pub fn ti_version() -> &'static str {
	println!("\n* ti_version");
    "0.9.2"
}
pub fn ti_build() -> i64 {
	println!("\n* ti_build");
    1645649572
}
pub fn ti_indicator_count() -> i32 {
	println!("\n* ti_indicator_count");
    104
}
pub fn ti_stream_get_progress(stream: &TiStream) -> i32 {
	println!("\n* ti_stream_get_progress");
    stream.progress
}
pub fn ti_find_indicator(name: Option<&str>) -> Option<usize> {
	println!("\n* ti_find_indicator");
    // Check for None (equivalent to NULL in C)
    let name = name?;
    
    println!("FINDDDDDDDING : {}", name);
    // We need to keep the lock guard alive for the lifetime of the returned reference
    // Since we can't do that directly, we'll return the index and then get the reference
    let index = {
        let ti_indicators = TI_INDICATORS.lock().unwrap();
        let mut imin = 0;
        let mut imax = ti_indicators.len(); // -2 as in original C code

        let mut found_index = ti_indicators.iter().position(|p| p.name.as_ref().unwrap() == name);
        //while imax >= imin {
        //    let i = imin + ((imax - imin) / 2);
        //    let indicator_name = match &ti_indicators[i].name {
        //        Some(n) => n,
        //        None => return None, // If name is None, we can't compare
        //    };

        //    match name.cmp(indicator_name.as_str()) {
        //        Ordering::Equal => {
        //            found_index = Some(i);
        //            break;
        //        }
        //        Ordering::Greater => imin = i + 1,
        //        Ordering::Less => imax = i.saturating_sub(1),
        //    }
        //}
        found_index
    };
    
    index
    // Now we can safely return a reference since we're not holding the lock
    //index.map(|i| {
    //    //let ti_indicators = TI_INDICATORS.lock().unwrap();
    //    //unsafe { &*(&ti_indicators[i] as *const TiIndicatorInfo) }, i
    //    i
    //})
}
pub fn ti_stream_run(
    stream: &TiStream,
    size: i32,
    inputs: Option<&[&[f64]]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
	println!("\n* ti_stream_run");
    // Lock the global TI_INDICATORS mutex to safely access the vector
    let indicators = TI_INDICATORS.lock().unwrap();
    
    // Get the indicator at the stream's index
    let indicator = &indicators[stream.index as usize];
    
    // Call the stream_run function pointer for this indicator
    match &indicator.stream_run {
        Some(func) => func(stream, size, inputs.unwrap_or(&[]), outputs.unwrap_or(&mut [])),
        None => 0, // Return 0 or appropriate error code if function is not available
    }
}
pub fn ti_stream_free(stream: TiStream) {
	println!("\n* ti_stream_free");
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
	println!("\n* ti_stream_get_info");
    let indicators = TI_INDICATORS.lock().unwrap();
    let index = stream.index as usize;
    if index < indicators.len() {
        unsafe { Some(&*(&indicators[index] as *const TiIndicatorInfo)) }
    } else {
        None
    }
}
