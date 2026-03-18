use crate::*;
use lazy_static::lazy_static;
use rand::Rng;
use rand::SeedableRng;
use std::f64;
use std::ffi::c_int;
use std::io::Write;
use std::io;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::Ordering;
use std::time::Duration;
use std::time::Instant;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
pub fn simple_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    if !options.is_empty() {
        options[0] = period;
    }
}
pub fn fast_slow_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to avoid unused variable warning
    options[0] = period;
    options[1] = period + 10.0;
}
pub fn alma_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = 0.5;
    options[2] = 1.0;
}
pub fn bbands_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 1.0;
}
pub fn ce_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn copp_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = 11.0;
    options[1] = 14.0;
    options[2] = period;
}
pub fn kc_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 0.77;
}
pub fn kst_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    for i in 0..4 {
        let value = period + ((period / 4.) * i as f64);
        options[i] = value;
        options[i + 4] = value;
    }
}
pub fn macd_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period + 10.0;
    options[2] = period + 1.0;
}
pub fn mama_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    let _ = period; // Explicitly ignore the parameter
    
    if options.len() >= 2 {
        options[0] = 0.5;
        options[1] = 0.05;
    }
    // If options has fewer than 2 elements, do nothing (safe Rust behavior)
}
pub fn pfe_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    options[0] = period;
    options[1] = 5.0;
}
pub fn posc_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn ppo_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period + 10.0;
}
pub fn psar_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = 1.0 / period;
    options[1] = options[0] * 10.0;
}
pub fn rmi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore unused parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn rmta_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore unused parameter
    options[0] = period;
    options[1] = 1.0 - (2.0 / (period + 1.0));
}
pub fn rvi_option_setter(period: f64, options: &mut [f64], _ti: i32) {
    options[0] = period;
    options[1] = 10.0;
}
pub fn smi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    options[0] = period;
    options[1] = 25.0;
    options[2] = 3.0;
}
pub fn stoch_option_setter(period: f64, options: Option<&mut [f64]>, ti: bool) {
    if ti {
        if let Some(options) = options {
            options[0] = period;
            options[1] = 3.0;
            options[2] = 4.0;
        }
    }
}
pub fn stochrsi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = period;
    options[2] = period;
    options[3] = 1.0;
}
pub fn tsi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn ultosc_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period * 2.0;
    options[2] = period * 4.0;
}
pub fn vidya_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = period + 10.0;
    options[2] = 0.2;
}
pub fn stochrsi_output_adjust(a: f64) -> f64 {
    a * 0.01
}
pub fn generate_inputs() {
    let mut in_data = IN.lock().unwrap();
    
    in_data[0][0] = 100.0;
    let mut rng = rand::rngs::StdRng::seed_from_u64(22); // Equivalent to srand(22)

    for i in 0..4000 {
        let diff1 = (rng.gen::<f64>() - 0.5 + 0.01) * 2.5;
        let diff2 = (rng.gen::<f64>() - 0.5 + 0.01) * 2.5;
        let diff3 = rng.gen::<f64>() * 0.5;
        let diff4 = rng.gen::<f64>() * 0.5;
        let vol = (rng.gen::<f64>() * 10000.0) + 500.0;

        if i > 0 {
            in_data[0][i] = in_data[0][i - 1] + diff1;
        }
        in_data[3][i] = in_data[0][i] + diff2;
        in_data[1][i] = if in_data[0][i] > in_data[3][i] {
            in_data[0][i] + diff3
        } else {
            in_data[3][i] + diff3
        };
        in_data[2][i] = if in_data[0][i] < in_data[3][i] {
            in_data[0][i] - diff4
        } else {
            in_data[3][i] - diff4
        };
        in_data[4][i] = vol;

        // Assertions
        assert!(in_data[0][i] <= in_data[1][i]);
        assert!(in_data[3][i] <= in_data[1][i]);
        assert!(in_data[0][i] >= in_data[2][i]);
        assert!(in_data[3][i] >= in_data[2][i]);
        assert!(in_data[1][i] >= in_data[2][i]);
        assert!(in_data[1][i] >= in_data[0][i]);
        assert!(in_data[1][i] >= in_data[3][i]);
        assert!(in_data[2][i] <= in_data[2][i]);
        assert!(in_data[2][i] <= in_data[0][i]);
        assert!(in_data[2][i] <= in_data[3][i]);
    }

    in_data[4][0] = 0.0;
}
lazy_static! {
    pub static ref IN: Mutex<[[f64; 4000]; 5]> = Mutex::new([[0.0; 4000]; 5]);
}

pub fn ti_setup(info: &TiIndicatorInfo, inputs: &mut [Option<&mut [f64]>]) {
    // Get a raw pointer to the static buffer inside the mutex
    let in_ptr = &*IN as *const _ as *const [[f64; 4000]; 5];
    let in_ptr_mut = in_ptr as *mut [[f64; 4000]; 5];
    
    for j in 0..info.inputs as usize {
        let input_name = match &info.input_names[j] {
            Some(name) => name,
            None => {
                assert!(false, "Input name is None");
                return;
            }
        };

        let index = match input_name.as_str() {
            "open" => 0,
            "high" => 1,
            "low" => 2,
            "close" | "real" => 3,
            "volume" => 4,
            _ => {
                assert!(false, "Unknown input name");
                return;
            }
        };
        
        // Create a static reference to the buffer
        let slice = unsafe { &mut (*in_ptr_mut)[index][..] };
        let slice_static: &'static mut [f64] = unsafe { std::mem::transmute(slice) };
        
        inputs[j] = Some(slice_static);
    }
}
lazy_static! {
    pub static ref INPUTS: std::sync::Mutex<[f64; 5]> = std::sync::Mutex::new([0.0; 5]);
}

pub fn run_ti(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
	println!("\n* run_ti");
    let mut out = OUT.lock().unwrap();
    let outputs = [&out[0][..], &out[1][..], &out[2][..]];
    
    match goal {
        0 => {
            let ind_offset = info.start.as_ref().map(|f| f(options)).unwrap_or(0);
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            let inputs = INPUTS.lock().unwrap();
            let inputs_ref = [&inputs[..], &[], &[], &[], &[]];
            
            // Safely create mutable references to each row
            let [row0, row1, row2] = &mut *out;
            let row0 = &mut row0[..];
            let row1 = &mut row1[..];
            let row2 = &mut row2[..];
            let mut outputs_mut = [row0, row1, row2];
            
            let ret = (info.indicator)(4000, Some(&inputs_ref), Some(options), Some(&mut outputs_mut));
            if ret != 0 {
                println!("   *ERROR* ({})", ret);
                println!("options:");
                for (i, opt) in options.iter().enumerate() {
                    println!("{} = {}", i, opt);
                }
                return 1;
            }
        }
        1 => {
            let mut inputs = INPUTS.lock().unwrap();
            let mut inputs_ref = [Some(inputs.as_mut_slice()), None, None, None, None];
            ti_setup(info, &mut inputs_ref);
        }
        2 => {}
        _ => {
            panic!("Invalid goal value");
        }
    }
    0
}
pub fn run_ti_ref(info: *const TiIndicatorInfo, options: &[f64], goal: c_int) -> c_int {
    static mut inputs: [*mut f64; 5] = [std::ptr::null_mut(); 5];
    static mut outputs: [*mut f64; 5] = [std::ptr::null_mut(); 5];

    match goal {
        0 => {
            unsafe {
                // Call the start function through the function pointer
                let start_fn = &(*info).start;
                if let Some(ref start_fn) = *start_fn {
                    let offset = start_fn(options);
                    IND_OFFSET.store(offset, std::sync::atomic::Ordering::Relaxed);
                }
                
                // Initialize outputs array with OUTREF data
                let outref_guard = OUTREF.lock().unwrap();
                outputs[0] = outref_guard[0].as_ptr() as *mut f64;
                outputs[1] = outref_guard[1].as_ptr() as *mut f64;
                outputs[2] = outref_guard[2].as_ptr() as *mut f64;
                outputs[3] = outref_guard[3].as_ptr() as *mut f64;
                outputs[4] = outref_guard[4].as_ptr() as *mut f64;
                
                // Create arrays with longer lifetimes
                let input_slices: [Option<&[f64]>; 5] = [
                    if inputs[0].is_null() { None } else { Some(std::slice::from_raw_parts(inputs[0], 4000)) },
                    if inputs[1].is_null() { None } else { Some(std::slice::from_raw_parts(inputs[1], 4000)) },
                    if inputs[2].is_null() { None } else { Some(std::slice::from_raw_parts(inputs[2], 4000)) },
                    if inputs[3].is_null() { None } else { Some(std::slice::from_raw_parts(inputs[3], 4000)) },
                    if inputs[4].is_null() { None } else { Some(std::slice::from_raw_parts(inputs[4], 4000)) },
                ];
                
                // Convert input_slices into an array of slices (use empty slice for None)
                let inputs_array: [&[f64]; 5] = [
                    input_slices[0].unwrap_or(&[]),
                    input_slices[1].unwrap_or(&[]),
                    input_slices[2].unwrap_or(&[]),
                    input_slices[3].unwrap_or(&[]),
                    input_slices[4].unwrap_or(&[]),
                ];
                
                // Create outputs_array directly without intermediate Option array
                let mut outputs_array: [&mut [f64]; 5] = [
                    if outputs[0].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(outputs[0], 4000) },
                    if outputs[1].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(outputs[1], 4000) },
                    if outputs[2].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(outputs[2], 4000) },
                    if outputs[3].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(outputs[3], 4000) },
                    if outputs[4].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(outputs[4], 4000) },
                ];
                
                // Convert options to Option<&[f64]> as expected by indicator_ref_fn
                let options_slice = if options.is_empty() {
                    Option::None
                } else {
                    Some(options)
                };
                
                // Call the indicator_ref function through the function pointer
                let indicator_ref_fn = (*info).indicator_ref;
                let ret = indicator_ref_fn(4000, Some(&inputs_array), options_slice, Some(&mut outputs_array));
                if ret != 0 {
                    println!("   *ERROR* ({})", ret);
                    println!("options:");
                    if !options.is_empty() {
                        for i in 0..(*info).options {
                            println!("{} = {}", i, options[i as usize]);
                        }
                    }
                    return 1;
                }
            }
        }
        1 => unsafe {
            // Convert inputs array to the format expected by ti_setup
            let mut input_options: [Option<&mut [f64]>; 5] = [
                if inputs[0].is_null() { None } else { Some(std::slice::from_raw_parts_mut(inputs[0], 4000)) },
                if inputs[1].is_null() { None } else { Some(std::slice::from_raw_parts_mut(inputs[1], 4000)) },
                if inputs[2].is_null() { None } else { Some(std::slice::from_raw_parts_mut(inputs[2], 4000)) },
                if inputs[3].is_null() { None } else { Some(std::slice::from_raw_parts_mut(inputs[3], 4000)) },
                if inputs[4].is_null() { None } else { Some(std::slice::from_raw_parts_mut(inputs[4], 4000)) },
            ];
            ti_setup(&*info, &mut input_options);
        },
        2 => {}
        _ => {
            assert!(false, "Invalid goal value");
        }
    }
    0
}

pub fn check_outputs(info: &TiIndicatorInfo, what: &str, compare: &[[f64; 4000]; 3]) {
    let remap = [0, 1, 2, 3, 4];
    let mut nanok = false;
    
    if let Some(name) = &info.name {
        if name == "asin" || name == "acos" {
            nanok = true;
        }
    }

    let ind_offset = IND_OFFSET.load(Ordering::Relaxed);
    let out = OUT.lock().unwrap();

    for j in 0..info.outputs {
        if remap[j as usize] == -1 {
            continue;
        }

        let end = 4000 - ind_offset;
        for i in 0..end {
            let out_idx = ((4000 - 1) - i) - ind_offset;
            let a = out[j as usize][out_idx as usize];
            let b = compare[j as usize][out_idx as usize];
            let diff = (a - b).abs();

            if diff > 0.0001 || (!nanok && diff.is_nan()) {
                FAILS.fetch_add(1, Ordering::Relaxed);
                println!("Results disagree.");
                println!("    series         (diff)   ti   {}", what);
                println!("    series {}, {:4} ({}) {:.5} {:.5}", j, i, diff, a, b);
                break;
            }
        }
    }
}
lazy_static! {
    pub static ref OUTSTREAMALL: Mutex<[[f64; 4000]; 3]> = Mutex::new([[0.0; 4000]; 3]);
}

pub fn run_ti_streamall(info: *const TiIndicatorInfo, options: &[f64], goal: c_int) -> c_int {
    static mut INPUTS: [*mut f64; 5] = [std::ptr::null_mut(); 5];
    static mut OUTPUTS: [*mut f64; 5] = [std::ptr::null_mut(); 5];

    match goal {
        0 => {
            // Initialize outputs array with OUTSTREAMALL data
            {
                let outstreamall_guard = OUTSTREAMALL.lock().unwrap();
                unsafe {
                    OUTPUTS[0] = outstreamall_guard[0].as_ptr() as *mut f64;
                    OUTPUTS[1] = outstreamall_guard[1].as_ptr() as *mut f64;
                    OUTPUTS[2] = outstreamall_guard[2].as_ptr() as *mut f64;
                    OUTPUTS[3] = outstreamall_guard[3].as_ptr() as *mut f64;
                    OUTPUTS[4] = outstreamall_guard[4].as_ptr() as *mut f64;
                }
            }
            
            unsafe {
                let start_fn = &(*info).start;
                let options_ptr = if options.is_empty() {
                    std::ptr::null()
                } else {
                    &options[0] as *const f64
                };
                
                if let Some(func) = start_fn {
                    let offset = func(&options[0..(*info).options as usize]);
                    IND_OFFSET.store(offset, std::sync::atomic::Ordering::Relaxed);
                }
                
                let mut stream: Option<Box<TiStream>> = None;
                let stream_new_fn = &(*info).stream_new;
                let options_for_new = if options.is_empty() {
                    None
                } else {
                    Some(&options[0..(*info).options as usize])
                };
                let sret = stream_new_fn(options_for_new, &mut stream);
                
                assert!(stream.is_some(), "Stream should not be null");
                assert!(sret == 0, "Stream creation should return 0");
                
                let stream_run_fn = &(*info).stream_run;
                let stream_ref = stream.as_ref().unwrap();
                
                // Create input slices
                let input_slices: [&[f64]; 5] = [
                    if INPUTS[0].is_null() { &[] } else { std::slice::from_raw_parts(INPUTS[0], 4000) },
                    if INPUTS[1].is_null() { &[] } else { std::slice::from_raw_parts(INPUTS[1], 4000) },
                    if INPUTS[2].is_null() { &[] } else { std::slice::from_raw_parts(INPUTS[2], 4000) },
                    if INPUTS[3].is_null() { &[] } else { std::slice::from_raw_parts(INPUTS[3], 4000) },
                    if INPUTS[4].is_null() { &[] } else { std::slice::from_raw_parts(INPUTS[4], 4000) },
                ];
                
                // Create output slices
                let mut output_slices: [&mut [f64]; 5] = [
                    if OUTPUTS[0].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(OUTPUTS[0], 4000) },
                    if OUTPUTS[1].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(OUTPUTS[1], 4000) },
                    if OUTPUTS[2].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(OUTPUTS[2], 4000) },
                    if OUTPUTS[3].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(OUTPUTS[3], 4000) },
                    if OUTPUTS[4].is_null() { &mut [] } else { std::slice::from_raw_parts_mut(OUTPUTS[4], 4000) },
                ];
                
                let ret = if let Some(run_fn) = stream_run_fn {
                    run_fn(stream_ref, 4000, &input_slices, &mut output_slices)
                } else {
                    panic!("stream_run function is missing");
                };
                
                let stream_free_fn = &(*info).stream_free;
                if let Some(func) = stream_free_fn {
                    if let Some(stream_box) = stream {
                        func(*stream_box)
                    }
                }
                
                if ret != 0 {
                    println!("   *ERROR* ({})", ret);
                    println!("options:");
                    
                    let options_count = (*info).options;
                    for i in 0..options_count {
                        let option_value = options[i as usize];
                        println!("{} = {}", i, option_value);
                    }
                    
                    return 1;
                }
            }
        }
        1 => {
            unsafe {
                // Create an array of Option<&mut [f64]> without requiring Copy
                let mut inputs_slice: [Option<&mut [f64]>; 5] = [
                    Option::None,
                    Option::None,
                    Option::None,
                    Option::None,
                    Option::None,
                ];
                
                for i in 0..5 {
                    if !INPUTS[i].is_null() {
                        inputs_slice[i] = Some(std::slice::from_raw_parts_mut(INPUTS[i], 4000));
                    }
                }
                ti_setup(&*info, &mut inputs_slice);
            }
        }
        2 => {
            // Goal 2 does nothing
        }
        _ => {
            panic!("Invalid goal value: {}", goal);
        }
    }
    
    0
}
pub fn bench_run_candle(log: Option<&mut dyn Write>, info: &TcCandleInfo) {
	println!("\n* bench_run_candle");
    let name = "ti";
    let pattern = info.pattern;
    let mut best_e = 1_000_000_000;
    let mut best_p = -1_000_000_000;
    
    let bestof = BESTOF.load(Ordering::Relaxed);
    for _best in 0..bestof {
        print!("Benchmark {:25}-{:16} ", info.name.as_deref().unwrap_or(""), name);
        std::io::stdout().flush().unwrap();

        let mut iterations = 0;
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();

        // Hold the lock for the entire duration we need the inputs
        let in_lock = IN.lock().unwrap();
        let inputs: [&[TC_REAL]; 4] = [&in_lock[0], &in_lock[1], &in_lock[2], &in_lock[3]];

        let mut config = TcConfig {
            period: 0,
            body_none: 0.0,
            body_short: 0.0,
            body_long: 0.0,
            wick_none: 0.0,
            wick_long: 0.0,
            near: 0.0,
        };
        tc_config_set_to_default(&mut config);

        for _i in 0..1 {
            for period in 4..=150 {
                config.period = period;
                let mut outcnd_guard = OUT_CND.lock().unwrap();
                let mut output = outcnd_guard.as_mut().unwrap(); // Unwrap the Option<TcResult>
                let ret = tc_run(pattern, 4000, &inputs, &config, &mut output);
                if ret != 0 {
                    return;
                }
                iterations += 1;
            }
        }

        // Lock is automatically released when in_lock goes out of scope

        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis()
            .wrapping_sub(start) as i32;

        let performance = if elapsed == 0 {
            0
        } else {
            ((iterations * 4000) / elapsed) / 1000
        };

        if elapsed != 0 {
            println!("\t{:5}ms\t{:5}mfps", elapsed, performance);
        } else {
            println!();
        }

        best_e = if elapsed < best_e { elapsed } else { best_e };
        best_p = if performance > best_p { performance } else { best_p };
    }

    if let Some(log) = log {
        writeln!(
            log,
            ",\n    \"{}\" => array(\"elapsed\" => {}, \"performance\" => {})",
            name, best_e, best_p
        ).unwrap();
    }
}
pub fn bench_candle(mut log: Option<&mut dyn Write>, info: Option<&TcCandleInfo>) {
    // Initialize outcnd using the global OUT_CND
    {
        let mut outcnd_guard = OUT_CND.lock().unwrap();
        *outcnd_guard = tc_result_new();
        assert!(outcnd_guard.is_some());
    }

    if let Some(info) = info {
        // Combine the two log checks into one to avoid multiple mutable borrows
        if let Some(ref mut log) = log {
            writeln!(log, ",\n  \"{}\" => array(", info.name.as_deref().unwrap_or("")).unwrap();
            write!(log, "    \"name\" => \"{}\"", info.full_name.as_deref().unwrap_or("")).unwrap();
        }

        // Use a match statement to handle log with explicit reborrowing
        // This limits the scope of the mutable borrow
        match log {
            Some(ref mut w) => {
                bench_run_candle(Some(&mut **w), info);
            }
            None => {
                bench_run_candle(Option::None, info);
            }
        }

        // Free outcnd
        {
            let mut outcnd_guard = OUT_CND.lock().unwrap();
            tc_result_free(outcnd_guard.take().map(Box::new));
        }
    }

    if let Some(ref mut log) = log {
        writeln!(log, "\n  )").unwrap();
    }

    println!();
}
pub fn run_ti_stream1(info: &TiIndicatorInfo, options: &[f64], goal: c_int) -> c_int {
    static mut inputs: [*mut f64; 5] = [ptr::null_mut(); 5];
    
    if goal == 0 {
        unsafe {
            if let Some(ref start_fn) = info.start {
                // Create a mutable copy of options for the start function
                let mut options_mut = options.to_vec();
                IND_OFFSET.store(start_fn(&mut options_mut), std::sync::atomic::Ordering::Relaxed);
            }
        }
        
        let mut ins: [*const f64; 5] = [ptr::null(); 5];
        let mut outs: [*mut f64; 5] = [ptr::null_mut(); 5];
        let mut stream: Option<Box<TiStream>> = None;
        
        unsafe {
            // Initialize outputs once at the beginning
            let outstream_guard = OUTSTREAM1.lock().unwrap();
            let mut outputs: [*mut f64; 5] = [
                outstream_guard[0].as_ptr() as *mut f64,
                outstream_guard[1].as_ptr() as *mut f64,
                outstream_guard[2].as_ptr() as *mut f64,
                outstream_guard[3].as_ptr() as *mut f64,
                outstream_guard[4].as_ptr() as *mut f64,
            ];
            
            // Create a mutable copy of options for stream_new
            let mut options_mut = options.to_vec();
            let sret = (info.stream_new)(Some(&mut options_mut), &mut stream);
            assert!(stream.is_some());
            assert_eq!(sret, 0);
            
            for i in 0..4000 {
                for j in 0..inputs.len() {
                    if !inputs[j].is_null() {
                        ins[j] = inputs[j].add(i);
                    }
                }
                
                let stream_ref = stream.as_ref().unwrap();
                let mut k = ti_stream_get_progress(stream_ref);
                if k < 0 {
                    k = 0;
                }
                
                for j in 0..outputs.len() {
                    if !outputs[j].is_null() {
                        outs[j] = outputs[j].add(k as usize);
                    }
                }
                
                // Convert arrays to slices of slices for the function call
                let mut input_slices: [&[f64]; 5] = [&[]; 5];
                let mut output_slices: [&mut [f64]; 5] = [&mut [], &mut [], &mut [], &mut [], &mut []];
                
                for j in 0..5 {
                    if !ins[j].is_null() {
                        input_slices[j] = std::slice::from_raw_parts(ins[j], 1);
                    }
                    if !outs[j].is_null() {
                        output_slices[j] = std::slice::from_raw_parts_mut(outs[j], 1);
                    }
                }
                
                if let Some(ref stream_run_fn) = info.stream_run {
                    let ret = stream_run_fn(stream_ref, 1, &input_slices, &mut output_slices);
                    if ret != 0 {
                        println!("   *ERROR* ({})", ret);
                        println!("options:");
                        
                        for j in 0..info.options {
                            println!("{} = {}", j, options[j as usize]);
                        }
                        
                        return 1;
                    }
                } else {
                    panic!("stream_run is None");
                }
            }
            
            if let Some(stream) = stream.take() {
                if let Some(ref stream_free_fn) = info.stream_free {
                    stream_free_fn(*stream);
                }
            }
        }
    } else if goal == 1 {
        let mut input_slices: [Option<&mut [f64]>; 5] = [
            unsafe { if !inputs[0].is_null() { Some(std::slice::from_raw_parts_mut(inputs[0], 4000)) } else { None } },
            unsafe { if !inputs[1].is_null() { Some(std::slice::from_raw_parts_mut(inputs[1], 4000)) } else { None } },
            unsafe { if !inputs[2].is_null() { Some(std::slice::from_raw_parts_mut(inputs[2], 4000)) } else { None } },
            unsafe { if !inputs[3].is_null() { Some(std::slice::from_raw_parts_mut(inputs[3], 4000)) } else { None } },
            unsafe { if !inputs[4].is_null() { Some(std::slice::from_raw_parts_mut(inputs[4], 4000)) } else { None } },
        ];
        
        ti_setup(info, &mut input_slices);
    } else if goal == 2 {
        // No operation needed for goal == 2
    } else {
        panic!("Invalid goal value");
    }
    
    0
}
pub fn bench_run(
    log: Option<&mut &mut dyn std::io::Write>,
    info: &TiIndicatorInfo,
    run_info: &TiIndicatorInfo,
    fun: RunFun,
    name: &str,
) {
    type OptionSetter = fn(f64, &mut [f64], i32);
    
    let mut options = [1.0; 10];
    let mut options_setter: Option<OptionSetter> = None;

    // Handle Option<String> conversion to C string
    if let Some(ref name_str) = info.name {
        let c_name = std::ffi::CString::new(name_str.as_str()).unwrap();
        
        unsafe {
            if libc::strcmp(c_name.as_ptr(), b"alma\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(alma_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"adosc\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(fast_slow_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"apo\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(ppo_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"bbands\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(bbands_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"copp\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(copp_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"kc\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(kc_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"kst\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(kst_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"kvo\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(fast_slow_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"macd\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(macd_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"mama\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(mama_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"pfe\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(pfe_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"posc\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(posc_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"ppo\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(ppo_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"psar\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(psar_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"rvi\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(rvi_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"rmi\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(rmi_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"rmta\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(rmta_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"smi\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(smi_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"stoch\0".as_ptr() as *const i8) == 0 {
                // stoch_option_setter has a different signature, need to handle it differently
                // For now, skip it or use a wrapper
                options_setter = None;
            }
            if libc::strcmp(c_name.as_ptr(), b"stochrsi\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(stochrsi_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"ultosc\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(ultosc_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"vidya\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(vidya_option_setter);
            }
            if libc::strcmp(c_name.as_ptr(), b"vosc\0".as_ptr() as *const i8) == 0 {
                options_setter = Some(fast_slow_option_setter);
            }
        }
    }

    let mut best_e = 1_000_000_000;
    let mut best_p = -1_000_000_000;
    let mut best = 0;

    unsafe {
        while best < BESTOF.load(std::sync::atomic::Ordering::Relaxed) {
            // Handle Option<String> conversion for printing
            let c_name_str = if let Some(ref name_str) = info.name {
                std::ffi::CString::new(name_str.as_str()).unwrap()
            } else {
                std::ffi::CString::new("").unwrap()
            };
            let c_run_name = std::ffi::CString::new(name).unwrap();
            libc::printf(
                b"Benchmark %25s-%-16s \0".as_ptr() as *const i8,
                c_name_str.as_ptr(),
                c_run_name.as_ptr(),
            );

            let mut iterations = 0;
            let start = std::time::Instant::now();

            fun(run_info, Option::<&[f64]>::None, 1);

            for _ in 0..1 {
                for period in 4..=150 {
                    if let Some(setter) = options_setter {
                        setter(
                            period as f64,
                            &mut options,
                            (info as *const _ as *const std::ffi::c_void == run_info as *const _ as *const std::ffi::c_void) as i32,
                        );
                    } else {
                        options[0] = period as f64;
                    }

                    let ret = fun(run_info, Some(&options), 0);
                    if ret != 0 {
                        return;
                    }
                    iterations += 1;
                }
            }

            fun(run_info, Option::<&[f64]>::None, 2);
            let elapsed = start.elapsed().as_millis() as i32;
            let performance = if elapsed == 0 {
                0
            } else {
                ((iterations * 4000) / elapsed) / 1000
            };

            if elapsed != 0 {
                libc::printf(
                    b"\t%5dms\t%5dmfps\n\0".as_ptr() as *const i8,
                    elapsed,
                    performance,
                );
            } else {
                libc::printf(b"\n\0".as_ptr() as *const i8);
            }

            best_e = if elapsed < best_e { elapsed } else { best_e };
            best_p = if performance > best_p { performance } else { best_p };
            best += 1;
        }
    }

    if let Some(log_file) = log {
        unsafe {
            let c_name = std::ffi::CString::new(name).unwrap();
            let c_str = std::ffi::CString::new(format!(
                ",\n    \"{}\" => array(\"elapsed\" => {}, \"performance\" => {})",
                name, best_e, best_p
            ))
            .unwrap();
            libc::fwrite(
                c_str.as_ptr() as *const _,
                1,
                c_str.as_bytes().len(),
                (*log_file) as *mut _ as *mut libc::FILE,
            );
        }
    }
}
pub fn bench_indicator(mut log: Option<&mut dyn Write>, info: Option<&TiIndicatorInfo>) {
    // Initialize output arrays with specific values (equivalent to memset in C)
    {
        let mut out = OUT.lock().unwrap();
        let mut outref = OUTREF.lock().unwrap();
        let mut outstream1 = OUTSTREAM1.lock().unwrap();
        let mut outstreamall = OUTSTREAMALL.lock().unwrap();

        for i in 0..3 {
            out[i].fill(0xF1 as f64);
            outref[i].fill(0xF2 as f64);
            outstream1[i].fill(0xF3 as f64);
            outstreamall[i].fill(0xF4 as f64);
        }
    }

    if let Some(info) = info {
        if let Some(ref mut log) = log {
            writeln!(log, ",\n  \"{}\" => array(", info.name.as_deref().unwrap_or("")).unwrap();
            write!(log, "    \"name\" => \"{}\"", info.full_name.as_deref().unwrap_or("")).unwrap();
        }

        // First bench_run call
        if let Some(ref mut log) = log {
            bench_run(Some(log), info, info, |info, options, goal| run_ti(info, options.unwrap_or(&[]), goal), "ti");
        }

        if info.indicator_ref as usize != 0 {
            if let Some(ref mut log) = log {
                bench_run(Some(log), info, info, |info, options, goal| run_ti_ref(info, options.unwrap_or(&[]), goal), "ti_ref");
            }
            check_outputs(info, "ref", &OUTREF.lock().unwrap());
        }

        if info.stream_new as usize != 0 {
            if let Some(ref mut log) = log {
                bench_run(Some(log), info, info, |info, options, goal| run_ti_stream1(info, options.unwrap_or(&[]), goal), "ti_stream1");
            }
            check_outputs(info, "stream1", &OUTSTREAM1.lock().unwrap());
            
            if let Some(ref mut log) = log {
                bench_run(Some(log), info, info, |info, options, goal| run_ti_streamall(info, options.unwrap_or(&[]), goal), "ti_streamall");
            }
            check_outputs(info, "streamall", &OUTSTREAMALL.lock().unwrap());
        }
    }

    if let Some(ref mut log) = log {
        writeln!(log, "\n  )").unwrap();
    }
    println!();
}
