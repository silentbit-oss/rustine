use crate::*;
use std::cmp::Ordering;

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
    // Check if name is None (equivalent to NULL in C)
    let name = name?;

    // We need to keep the lock for the entire duration since we're working with the data
    let ti_indicators = TI_INDICATORS.lock().unwrap();
    let mut imin = 0;
    let mut imax = ti_indicators.len().saturating_sub(1); // Only subtract 1 for 0-based index
    
    while imax >= imin {
        let i = imin + ((imax - imin) / 2);
        let indicator = &ti_indicators[i];
        
        match indicator.name.as_deref() {
            Some(indicator_name) => match name.cmp(indicator_name) {
                Ordering::Equal => {
                    // Return a reference to the static data in TI_INDICATORS
                    // This is safe because TI_INDICATORS is a lazy_static and won't be modified
                    return Some(unsafe { &*(indicator as *const _) });
                },
                Ordering::Greater => imin = i + 1,
                Ordering::Less => imax = i.saturating_sub(1),
            },
            None => return None, // If indicator name is None, we can't compare
        }
    }
    
    None
}
pub fn ti_stream_run(
    stream: &mut TiStream,
    size: i32,
    inputs: Option<&[&[f64]]>,
    outputs: Option<&mut [&mut [f64]]>,
) -> i32 {
    // Lock the TI_INDICATORS mutex to safely access the global vector
    let mut ti_indicators = TI_INDICATORS.lock().unwrap();
    
    // Get the indicator info for this stream's index
    let indicator_info = &mut ti_indicators[stream.index as usize];
    
    // Call the stream_run function if it exists, otherwise return an error code
    if let Some(stream_run_fn) = &mut indicator_info.stream_run {
        // Clone the stream to pass by value
        let mut stream_clone = stream.clone();
        
        // Convert inputs to owned vectors
        let inputs_converted = inputs.map(|input_slices| {
            input_slices.iter()
                .map(|slice| Some(slice.to_vec()))
                .collect::<Vec<_>>()
        });
        
        // Prepare temporary output storage
        let mut outputs_temp: Option<Vec<Option<Vec<f64>>>> = None;
        if let Some(output_slices) = &outputs {
            outputs_temp = Some(
                output_slices.iter()
                    .map(|_| Some(vec![0.0; size as usize]))
                    .collect()
            );
        }

        // Clone values before passing to avoid move issues
        let outputs_temp_clone = outputs_temp.clone();
        let stream_clone_for_call = stream_clone.clone();

        // Call the function
        let result = stream_run_fn(
            stream_clone_for_call,
            size,
            inputs_converted,
            outputs_temp_clone,
        );

        // Copy results back to output slices
        if let (Some(outputs_temp), Some(original_outputs)) = (outputs_temp, outputs) {
            for (i, output_vec_option) in outputs_temp.into_iter().enumerate() {
                if let Some(output_vec) = output_vec_option {
                    let len = output_vec.len().min(original_outputs[i].len());
                    original_outputs[i][..len].copy_from_slice(&output_vec[..len]);
                }
            }
        }

        // Update original stream from clone
        *stream = stream_clone;

        result
    } else {
        -1 // Return error code if stream_run is not implemented
    }
}
pub fn ti_stream_free(stream: &mut TiStream) {
    // Lock the TI_INDICATORS mutex to safely access the global vector
    let ti_indicators = TI_INDICATORS.lock().unwrap();
    
    // Get the indicator info for this stream's index
    let indicator_info = &ti_indicators[stream.index as usize];
    
    // Call the stream_free function pointer if it's not null (represented as non-zero in Rust)
    if indicator_info.stream_free as usize != 0 {
        unsafe { (indicator_info.stream_free)(Some(Box::new(stream.clone()))) };
    }
}
pub fn ti_stream_get_info(stream: &TiStream) -> Option<&TiIndicatorInfo> {
    let ti_indicators = TI_INDICATORS.lock().unwrap();
    unsafe { ti_indicators.get(stream.index as usize).map(|x| &*(x as *const _)) }
}
