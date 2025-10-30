use std::fs::File;
use crate::*;
use rand::Rng;
use std::time::Duration;
use std::time::Instant;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::ffi::CStr;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;
use std::f64;
use std::io::Write;
use std::os::raw::c_char;

pub fn simple_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    if !options.is_empty() {
        options[0] = period;
    }
}
pub fn fast_slow_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
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
    let _ = ti; // Explicitly ignore the parameter to match C behavior
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
    let _ = ti; // Explicitly ignore the unused parameter
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
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = period + 10.0;
}
pub fn psar_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = 1.0 / period;
    options[1] = options[0] * 10.0;
}
pub fn rmi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn rmta_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = 1.0 - (2.0 / (period + 1.0));
}
pub fn rvi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 10.0; // Use float literal for consistency with f64 type
}
pub fn smi_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = 25.0;
    options[2] = 3.0;
}
pub fn stoch_option_setter(period: f64, options: &mut [f64], ti: bool) {
    if ti {
        options[0] = period;
        options[1] = 3.0;
        options[2] = 4.0;
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
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    options[0] = period;
    options[1] = 3.0;
}
pub fn ultosc_option_setter(period: f64, options: &mut [f64], ti: i32) {
    let _ = ti; // Explicitly ignore the parameter
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

pub fn helper_generate_inputs_1(
    i_ref: &mut i32,
    open: &mut [f64],
    high: &mut [f64],
    low: &mut [f64],
    close: &mut [f64],
    volume: &mut [f64],
) {
    let i = *i_ref as usize;
    let mut rng = rand::thread_rng();
    
    let diff1 = (rng.gen::<f64>() - 0.5 + 0.01) * 2.5;
    let diff2 = (rng.gen::<f64>() - 0.5 + 0.01) * 2.5;
    let diff3 = rng.gen::<f64>() * 0.5;
    let diff4 = rng.gen::<f64>() * 0.5;
    let vol = rng.gen::<f64>() * 10000.0 + 500.0;

    if i > 0 {
        open[i] = open[i - 1] + diff1;
    }
    close[i] = open[i] + diff2;
    high[i] = if open[i] > close[i] {
        open[i] + diff3
    } else {
        close[i] + diff3
    };
    low[i] = if open[i] < close[i] {
        open[i] - diff4
    } else {
        close[i] - diff4
    };
    volume[i] = vol;

    // Assertions
    assert!(open[i] <= high[i]);
    assert!(close[i] <= high[i]);
    assert!(open[i] >= low[i]);
    assert!(close[i] >= low[i]);
    assert!(high[i] >= low[i]);
    assert!(high[i] >= open[i]);
    assert!(high[i] >= close[i]);
    assert!(low[i] <= low[i]);
    assert!(low[i] <= open[i]);
    assert!(low[i] <= close[i]);

    *i_ref = i as i32;
}
pub fn helper_bench_run_1(
    best_e_ref: &mut i32,
    best_p_ref: &mut i32,
    info: &TiIndicatorInfo,
    run_info: &dyn std::any::Any,
    name: &str,
    options: &mut [f64],
    options_setter: Option<fn(f64, &mut [f64], bool)>,
    fun: fn(&dyn std::any::Any, &[f64], i32) -> i32,
) {
    
    let mut best_e = *best_e_ref;
    let mut best_p = *best_p_ref;
    
    print!("Benchmark {:25}-{:16} ", info.name.as_deref().unwrap_or(""), name);
    std::io::stdout().flush().unwrap();

    let mut iterations = 0;
    let start = std::time::Instant::now();

    fun(run_info, &[], 1);

    for _ in 0..1 {
        for period in 4..=150 {
            if let Some(setter) = options_setter {
                let is_same = run_info.downcast_ref::<TiIndicatorInfo>().map_or(false, |ri| std::ptr::eq(info, ri));
                setter(period as f64, options, is_same);
            } else {
                options[0] = period as f64;
            }
            
            let ret = fun(run_info, options, 0);
            if ret != 0 {
                return;
            }
            iterations += 1;
        }
    }

    fun(run_info, &[], 2);
    
    let elapsed = start.elapsed().as_millis() as i32;
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

    *best_e_ref = best_e;
    *best_p_ref = best_p;
}
pub fn generate_inputs() {
    let mut in_lock = IN.lock().unwrap();
    
    // Destructure the array to get mutable references to all parts at once
    let [open, high, low, close, volume] = &mut *in_lock;
    open[0] = 100.0;
    
    let mut rng = rand::thread_rng();
    
    for i in 0..4000 {
        let mut i = i; // Create a mutable copy if needed by helper_generate_inputs_1
        helper_generate_inputs_1(&mut i, open, high, low, close, volume);
    }
    
    volume[0] = 0.0;
}
pub fn ti_setup(info: &TiIndicatorInfo, inputs: &mut [Option<*const [f64]>]) {
    let in_lock = IN.lock().unwrap();
    
    for j in 0..info.inputs as usize {
        let input_name = info.input_names[j].as_ref().expect("input name must exist");
        
        match input_name.as_str() {
            "open" => inputs[j] = Some(&in_lock[0] as *const [f64]),
            "high" => inputs[j] = Some(&in_lock[1] as *const [f64]),
            "low" => inputs[j] = Some(&in_lock[2] as *const [f64]),
            "close" | "real" => inputs[j] = Some(&in_lock[3] as *const [f64]),
            "volume" => inputs[j] = Some(&in_lock[4] as *const [f64]),
            _ => panic!("invalid input name"),
        }
    }
}
pub fn run_ti(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
    static mut INPUTS: [Option<*const [f64]>; 4] = [None; 4];
    static mut OUTPUTS: [Option<*mut [f64]>; 4] = [None; 4];

    match goal {
        0 => unsafe {
            let ind_offset = if let Some(start_fn) = &info.start {
                start_fn(options)
            } else {
                0
            };
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            // Initialize OUTPUTS when needed (goal == 0)
            OUTPUTS = [
                Some(OUT.lock().unwrap()[0].as_mut_ptr() as *mut [f64; 4000]),
                Some(OUT.lock().unwrap()[1].as_mut_ptr() as *mut [f64; 4000]),
                Some(OUT.lock().unwrap()[2].as_mut_ptr() as *mut [f64; 4000]),
                None,
            ];

            let inputs_slice: Vec<&[f64]> = INPUTS.iter()
                .filter_map(|&x| x.map(|ptr| unsafe { &*ptr }))
                .collect();
            let mut outputs_slice: Vec<&mut [f64]> = OUTPUTS.iter()
                .filter_map(|&x| x.map(|ptr| unsafe { &mut *ptr }))
                .collect();

            let ret = (info.indicator)(4000, &inputs_slice, options, &mut outputs_slice);
            if ret != 0 {
                println!("   *ERROR* ({})", ret);
                println!("options:");
                for (i, &opt) in options.iter().enumerate().take(info.options as usize) {
                    println!("{} = {}", i, opt);
                }
                return 1;
            }
        },
        1 => unsafe {
            ti_setup(info, &mut INPUTS);
        },
        2 => {
            // No operation needed for goal == 2
        },
        _ => {
            panic!("Invalid goal value");
        }
    }
    0
}
pub fn run_ti_ref(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
    // Use thread-local storage for the static arrays to avoid unsafe static mut
    thread_local! {
        static INPUTS: std::cell::RefCell<[Option<*const [f64]>; 5]> = std::cell::RefCell::new([None, None, None, None, None]);
        static OUTPUTS: std::cell::RefCell<[Option<*mut f64>; 5]> = std::cell::RefCell::new([
            None, None, None, None, None
        ]);
    }

    match goal {
        0 => {
            // Call the start function if it exists
            let ind_offset = if let Some(start_fn) = &info.start {
                start_fn(options)
            } else {
                0
            };
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            // Initialize outputs with OUTREF
            OUTPUTS.with(|outputs| {
                let mut outputs = outputs.borrow_mut();
                let outref = OUTREF.lock().unwrap();
                outputs[0] = Some(outref[0].as_ptr() as *mut f64);
                outputs[1] = Some(outref[1].as_ptr() as *mut f64);
                outputs[2] = Some(outref[2].as_ptr() as *mut f64);
            });

            // Convert inputs and outputs to slices for the indicator_ref call
            let inputs_slice: &[&[f64]] = &[];
            let mut outputs_slice: Vec<&mut [f64]> = Vec::new();

            OUTPUTS.with(|outputs| {
                let outputs = outputs.borrow();
                for output in outputs.iter() {
                    if let Some(ptr) = output {
                        unsafe {
                            outputs_slice.push(std::slice::from_raw_parts_mut(*ptr, 4000));
                        }
                    }
                }
            });

            let ret = (info.indicator_ref)(4000, inputs_slice, options, &mut outputs_slice);
            if ret != 0 {
                println!("   *ERROR* ({})", ret);
                println!("options:");
                for i in 0..info.options {
                    println!("{} = {}", i, options[i as usize]);
                }
                return 1;
            }
        }
        1 => {
            INPUTS.with(|inputs| {
                let mut inputs = inputs.borrow_mut();
                ti_setup(info, &mut *inputs);
            });
        }
        2 => {}
        _ => {
            panic!("Invalid goal value");
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

    let ind_offset = IND_OFFSET.load(Ordering::SeqCst);
    let end = 4000 - ind_offset;

    for j in 0..info.outputs {
        if remap[j as usize] == -1 {
            continue;
        }

        let out_guard = OUT.lock().unwrap();
        let out_row = &out_guard[j as usize];

        for i in 0..end {
            let idx = ((4000 - 1) - i) - ind_offset;
            let a = out_row[idx as usize];
            let b = compare[j as usize][idx as usize];
            let diff = (a - b).abs();

            if diff > 0.0001 || (!nanok && diff.is_nan()) {
                FAILS.fetch_add(1, Ordering::SeqCst);
                println!("Results disagree.");
                println!("    series         (diff)   ti   {}", what);
                println!("    series {}, {:4} ({}) {:.5} {:.5}", j, i, diff, a, b);
                break;
            }
        }
    }
}
pub fn run_ti_streamall(info: &mut TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
    static mut INPUTS: [Option<*const [f64]>; 5] = [None; 5];
    match goal {
        0 => {
            if let Some(start_fn) = &info.start {
                IND_OFFSET.store(start_fn(options), Ordering::SeqCst);
            }
            let mut stream: Option<Box<TiStream>> = None;
            let sret = (info.stream_new)(Some(options), &mut stream);
            assert!(stream.is_some());
            assert_eq!(sret, 0);

            let inputs_ref = unsafe { &INPUTS };
            let input_vec: Vec<Option<Vec<f64>>> = inputs_ref
                .iter()
                .map(|x| {
                    match x {
                        Some(ptr) => {
                            let slice = unsafe { &**ptr };
                            Some(slice.to_vec())
                        }
                        None => None,
                    }
                })
                .collect();

            let output_vec: Vec<Option<Vec<f64>>> = {
                let outstream = OUTSTREAMALL.lock().unwrap();
                [
                    Some(&outstream[0]),
                    Some(&outstream[1]),
                    Some(&outstream[2]),
                    None,
                    None,
                ]
                .iter()
                .map(|x| x.map(|y| y.to_vec()))
                .collect()
            };
            
            let ret = info.stream_run.as_mut().unwrap()(
                stream.as_ref().unwrap().as_ref().clone(),
                4000,
                Some(input_vec),
                Some(output_vec),
            );
            (info.stream_free)(stream);

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
            ti_setup(info, unsafe { &mut INPUTS });
        }
        2 => {}
        _ => {
            panic!("Invalid goal value");
        }
    }
    0
}
pub fn bench_run_candle(log: Option<&mut dyn Write>, info: &TcCandleInfo) {
    let name = "ti";
    let pattern = info.pattern;
    let mut best_e = 1_000_000_000;
    let mut best_p = -1_000_000_000;
    
    let bestof = BESTOF.load(std::sync::atomic::Ordering::Relaxed);
    for _best in 0..bestof {
        print!("Benchmark {:25}-{:16} ", info.name.as_deref().unwrap_or(""), name);
        std::io::stdout().flush().unwrap();

        let mut iterations = 0;
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();

        let in_lock = IN.lock().unwrap();
        let inputs = [&in_lock[0][..], &in_lock[1][..], &in_lock[2][..], &in_lock[3][..]];
        
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
                let mut outcnd = OUT_CND.lock().unwrap();
                let ret = tc_run(pattern, 4000, &inputs, &config, outcnd.as_mut().unwrap());
                if ret != 0 {
                    return;
                }
                iterations += 1;
            }
        }

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
    let outcnd = tc_result_new().expect("Failed to create new TcResult");
    *OUT_CND.lock().unwrap() = Some(*outcnd);

    // Handle initial logging first
    if let Some(info) = info {
        // Perform initial logging in a separate block to release the borrow
        if let Some(log_ref) = log.as_deref_mut() {
            writeln!(log_ref, ",\n  \"{}\" => array(", info.name.as_deref().unwrap_or("")).unwrap();
            write!(log_ref, "    \"name\" => \"{}\"", info.full_name.as_deref().unwrap_or("")).unwrap();
        }
        
        // Perform the benchmark with a separate mutable borrow
        if let Some(log_ref) = log.as_deref_mut() {
            bench_run_candle(Some(log_ref), info);
        } else {
            bench_run_candle(None, info);
        }
        
        // Clean up
        if let Some(outcnd) = OUT_CND.lock().unwrap().take() {
            tc_result_free(Some(Box::new(outcnd)));
        }
    } else {
        if let Some(outcnd) = OUT_CND.lock().unwrap().take() {
            tc_result_free(Some(Box::new(outcnd)));
        }
    }

    // Handle final logging if log exists
    if let Some(log_ref) = log.as_deref_mut() {
        writeln!(log_ref, "\n  )").unwrap();
    }
    
    println!();
}
pub fn run_ti_stream1(info: &mut TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
    static mut INPUTS: [Option<*const [f64]>; 5] = [None; 5];
    let outputs = [
        OUTSTREAM1.lock().unwrap()[0].as_ptr(),
        OUTSTREAM1.lock().unwrap()[1].as_ptr(),
        OUTSTREAM1.lock().unwrap()[2].as_ptr(),
        OUTSTREAM1.lock().unwrap()[3].as_ptr(),
        OUTSTREAM1.lock().unwrap()[4].as_ptr(),
    ];

    match goal {
        0 => unsafe {
            if let Some(start_fn) = &info.start {
                IND_OFFSET.store(start_fn(options), Ordering::SeqCst);
            }
            let mut ins = [None; 5];
            let mut outs = [None; 5];
            let mut stream = None;
            
            let sret = (info.stream_new)(Some(options), &mut stream);
            assert!(stream.is_some());
            assert_eq!(sret, 0);

            for i in 0..4000 {
                for j in 0..INPUTS.len() {
                    if let Some(ptr) = INPUTS[j] {
                        ins[j] = Some(unsafe { (*ptr).as_ptr().add(i) });
                    }
                }

                let mut k = ti_stream_get_progress(stream.as_ref().unwrap());
                if k < 0 {
                    k = 0;
                }

                for j in 0..outputs.len() {
                    outs[j] = Some(unsafe { outputs[j].add(k as usize) });
                }

                if let Some(stream_run) = &mut info.stream_run {
                    let ret = stream_run(
                        *stream.as_ref().unwrap().clone(),
                        1,
                        Some(ins.iter()
                            .map(|x| x.map(|v| vec![unsafe { *v }]))
                            .collect()),
                        Some(outs.iter()
                            .map(|x| x.map(|v| vec![unsafe { *v }]))
                            .collect()),
                    );

                    if ret != 0 {
                        println!("   *ERROR* ({})", ret);
                        println!("options:");
                        for j in 0..info.options {
                            println!("{} = {}", j, options[j as usize]);
                        }
                        return 1;
                    }
                }
            }

            (info.stream_free)(stream);
        },
        1 => unsafe {
            ti_setup(info, &mut INPUTS[..]);
        },
        2 => {}
        _ => {
            panic!("Invalid goal value");
        }
    }

    0
}
pub fn bench_run(
    log: Option<&mut std::fs::File>,
    info: &TiIndicatorInfo,
    run_info: &dyn std::any::Any,
    fun: RunFun,
    name: &str,
) {
    let mut options = [1.0; 10];
    let mut options_setter: Option<fn(f64, &mut [f64], bool)> = Option::None;

    if let Some(ref indicator_name) = info.name {
        match indicator_name.as_str() {
            "adosc" | "kvo" | "vosc" => {
                options_setter = Some(|period, options, ti| fast_slow_option_setter(period, options, ti as i32));
            }
            "alma" => {
                options_setter = Some(|period, options, ti| alma_option_setter(period, options, ti as i32));
            }
            "apo" | "ppo" => {
                options_setter = Some(|period, options, ti| ppo_option_setter(period, options, ti as i32));
            }
            "bbands" => {
                options_setter = Some(|period, options, ti| bbands_option_setter(period, options, ti as i32));
            }
            "copp" => {
                options_setter = Some(|period, options, ti| copp_option_setter(period, options, ti as i32));
            }
            "kc" => {
                options_setter = Some(|period, options, ti| kc_option_setter(period, options, ti as i32));
            }
            "kst" => {
                options_setter = Some(|period, options, ti| kst_option_setter(period, options, ti as i32));
            }
            "macd" => {
                options_setter = Some(|period, options, ti| macd_option_setter(period, options, ti as i32));
            }
            "mama" => {
                options_setter = Some(|period, options, ti| mama_option_setter(period, options, ti as i32));
            }
            "pfe" => {
                options_setter = Some(|period, options, ti| pfe_option_setter(period, options, ti as i32));
            }
            "posc" => {
                options_setter = Some(|period, options, ti| posc_option_setter(period, options, ti as i32));
            }
            "psar" => {
                options_setter = Some(|period, options, ti| psar_option_setter(period, options, ti as i32));
            }
            "rvi" => {
                options_setter = Some(|period, options, ti| rvi_option_setter(period, options, ti as i32));
            }
            "rmi" => {
                options_setter = Some(|period, options, ti| rmi_option_setter(period, options, ti as i32));
            }
            "rmta" => {
                options_setter = Some(|period, options, ti| rmta_option_setter(period, options, ti as i32));
            }
            "smi" => {
                options_setter = Some(|period, options, ti| smi_option_setter(period, options, ti as i32));
            }
            "stoch" => {
                options_setter = Some(stoch_option_setter);
            }
            "stochrsi" => {
                options_setter = Some(|period, options, ti| stochrsi_option_setter(period, options, ti as i32));
            }
            "ultosc" => {
                options_setter = Some(|period, options, ti| ultosc_option_setter(period, options, ti as i32));
            }
            "vidya" => {
                options_setter = Some(|period, options, ti| vidya_option_setter(period, options, ti as i32));
            }
            _ => (),
        }
    }

    let mut best_e = 1_000_000_000;
    let mut best_p = -1_000_000_000;
    let bestof = BESTOF.load(std::sync::atomic::Ordering::Relaxed);

    // Create context to pass without capture
    let context = (info, fun);

    // Define wrapper function that uses context from run_info
    fn wrapper_fun(
        run_info: &dyn std::any::Any,
        options: &[f64],
        goal: i32,
    ) -> i32 {
        let ctx = run_info.downcast_ref::<(&TiIndicatorInfo, RunFun)>().unwrap();
        let (info, fun) = *ctx;
        fun(info, Some(options), goal)
    }

    // Create function pointer
    let wrapper_ptr: fn(&dyn std::any::Any, &[f64], i32) -> i32 = wrapper_fun;

    for _ in 0..bestof {
        helper_bench_run_1(
            &mut best_e,
            &mut best_p,
            info,
            run_info, // Use the original run_info instead of context
            name,
            &mut options,
            options_setter,
            wrapper_ptr,
        );
    }

    if let Some(log) = log {
        // Using ignore_result to handle potential write errors safely
        let _ = writeln!(
            log,
            ",\n    \"{}\" => array(\"elapsed\" => {}, \"performance\" => {})",
            name, best_e, best_p
        );
    }
}
pub fn bench_indicator(mut log: Option<&mut std::fs::File>, info: Option<&mut TiIndicatorInfo>) {
    // Initialize output arrays with memset equivalent
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
        
        bench_run(log.as_deref_mut(), info, info, |i, o, g| run_ti(i, o.unwrap_or(&[]), g), "ti");

        if info.indicator_ref as usize != 0 {
            bench_run(log.as_deref_mut(), info, info, |i, o, g| run_ti_ref(i, o.unwrap_or(&[]), g), "ti_ref");
            check_outputs(info, "ref", &OUTREF.lock().unwrap());
        }

        if info.stream_new as usize != 0 {
            bench_run(
                log.as_deref_mut(),
                info,
                info,
                |i, o, g| {
                    let mut info_copy = unsafe { std::ptr::read(i as *const _) };
                    let result = run_ti_stream1(&mut info_copy, o.unwrap_or(&[]), g);
                    std::mem::forget(info_copy); // Prevent double-free since we're working with a copy
                    result
                },
                "ti_stream1"
            );
            check_outputs(info, "stream1", &OUTSTREAM1.lock().unwrap());
            
            bench_run(
                log.as_deref_mut(),
                info,
                info,
                |i, o, g| {
                    let mut info_copy = unsafe { std::ptr::read(i as *const _) };
                    let result = run_ti_streamall(&mut info_copy, o.unwrap_or(&[]), g);
                    std::mem::forget(info_copy); // Prevent double-free since we're working with a copy
                    result
                },
                "ti_streamall"
            );
            check_outputs(info, "streamall", &OUTSTREAMALL.lock().unwrap());
        }
    }

    if let Some(ref mut log) = log {
        writeln!(log, "\n  )").unwrap();
    }
    println!();
}
