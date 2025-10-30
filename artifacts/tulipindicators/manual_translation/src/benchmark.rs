use crate::*;
use rand::Rng;
use rand::SeedableRng;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::Ordering;
use std::f64;
use std::time::Duration;
use std::time::Instant;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::io::Write;

pub fn simple_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* simple_option_setter");
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    if !options.is_empty() {
        options[0] = period;
    }
}
pub fn fast_slow_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* fast_slow_option_setter");
    let _ = ti; // Explicitly ignore the parameter to avoid unused variable warning
    options[0] = period;
    options[1] = period + 10.0;
}
pub fn alma_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* alma_option_setter");
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = 0.5;
    options[2] = 1.0;
}
pub fn bbands_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* bbands_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 1.0;
}
pub fn ce_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* ce_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn copp_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* copp_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = 11.0;
    options[1] = 14.0;
    options[2] = period;
}
pub fn kc_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* kc_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 0.77;
}
pub fn kst_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* kst_option_setter");
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    for i in 0..4 {
        let value = period + ((period / 4.) * i as f64);
        options[i] = value;
        options[i + 4] = value;
    }
}
pub fn macd_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* macd_option_setter");
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period + 10.0;
    options[2] = period + 1.0;
}
pub fn mama_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* mama_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    let _ = period; // Explicitly ignore the parameter
    
    if options.len() >= 2 {
        options[0] = 0.5;
        options[1] = 0.05;
    }
    // If options has fewer than 2 elements, do nothing (safe Rust behavior)
}
pub fn pfe_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* pfe_option_setter");
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    options[0] = period;
    options[1] = 5.0;
}
pub fn posc_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* posc_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn ppo_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* ppo_option_setter");
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period + 10.0;
}
pub fn psar_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* psar_option_setter");
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = 1.0 / period;
    options[1] = options[0] * 10.0;
}
pub fn rmi_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* rmi_option_setter");
    let _ = ti; // Explicitly ignore unused parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn rmta_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* rmta_option_setter");
    let _ = ti; // Explicitly ignore unused parameter
    options[0] = period;
    options[1] = 1.0 - (2.0 / (period + 1.0));
}
pub fn rvi_option_setter(period: f64, options: &mut [f64], _ti: i32) {
	println!("\n* rvi_option_setter");
    options[0] = period;
    options[1] = 10.0;
}
pub fn smi_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* smi_option_setter");
    let _ = ti; // Explicitly ignore the parameter to match C behavior
    options[0] = period;
    options[1] = 25.0;
    options[2] = 3.0;
}
pub fn stoch_option_setter(period: f64, options: Option<&mut [f64]>, ti: bool) {
	println!("\n* stoch_option_setter");
    if ti {
        if let Some(options) = options {
            options[0] = period;
            options[1] = 3.0;
            options[2] = 4.0;
        }
    }
}
pub fn stochrsi_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* stochrsi_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = period;
    options[2] = period;
    options[3] = 1.0;
}
pub fn tsi_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* tsi_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = 3.0;
}
pub fn ultosc_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* ultosc_option_setter");
    let _ = ti; // Explicitly ignore the unused parameter
    options[0] = period;
    options[1] = period * 2.0;
    options[2] = period * 4.0;
}
pub fn vidya_option_setter(period: f64, options: &mut [f64], ti: i32) {
	println!("\n* vidya_option_setter");
    let _ = ti; // Explicitly ignore the parameter
    options[0] = period;
    options[1] = period + 10.0;
    options[2] = 0.2;
}
pub fn stochrsi_output_adjust(a: f64) -> f64 {
	println!("\n* stochrsi_output_adjust");
    a * 0.01
}
pub fn generate_inputs() {
	println!("\n* generate_inputs");
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
	println!("\n* ti_setup");
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
pub fn run_ti_ref(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
	println!("\n* run_ti_ref");
    match goal {
        0 => {
            let ind_offset = info.start.as_ref().map(|f| f(options)).unwrap_or(0);
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            let inputs_ref: &[&[f64]] = &[&[], &[], &[], &[], &[]]; // Empty slices matching the C code's null pointers
            
            let mut outref = OUTREF.lock().unwrap();
            let rows = &mut *outref;
            let (first, rest) = rows.split_at_mut(1);
            let (second, third) = rest.split_at_mut(1);
            let row0 = &mut first[0][..];
            let row1 = &mut second[0][..];
            let row2 = &mut third[0][..];
            let outputs_ref: &mut [&mut [f64]] = &mut [row0, row1, row2];

            let ret = (info.indicator_ref)(4000, Some(inputs_ref), Some(options), Some(outputs_ref));
            if ret != 0 {
                println!("   *ERROR* ({})", ret);
                println!("options:");
                for (i, opt) in options.iter().enumerate().take(info.options as usize) {
                    println!("{} = {}", i, opt);
                }
                return 1;
            }
        }
        1 => {
            // ti_setup would be called here, but since it's a lazy_static, we don't need to do anything
        }
        2 => {
            // No operation needed for goal == 2
        }
        _ => {
            panic!("Invalid goal value");
        }
    }
    0
}

pub fn check_outputs(info: &TiIndicatorInfo, what: &str, compare: &[[f64; 4000]; 3]) {
	println!("\n* check_outputs");
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

pub fn run_ti_streamall(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
	println!("\n* run_ti_streamall");
    static INPUTS: [f64; 5] = [0.0; 5];
    let mut outputs_ref = OUTSTREAMALL.lock().unwrap();
    
    // Create mutable references to each array slice by splitting the array first
    let (output0, rest) = outputs_ref.split_at_mut(1);
    let (output1, output2) = rest.split_at_mut(1);
    let output0 = &mut output0[0][..];
    let output1 = &mut output1[0][..];
    let output2 = &mut output2[0][..];
    let mut outputs = [output0, output1, output2];

    match goal {
        0 => {
            let ind_offset = info.start.as_ref().map(|f| f(options)).unwrap_or(0);
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            let mut stream: Option<Box<TiStream>> = None;
            let sret = (info.stream_new)(Some(options), &mut stream);
            assert!(stream.is_some());
            assert_eq!(sret, 0);

            let stream_ref = stream.as_ref().unwrap();
            let inputs_ref: &[&[f64]] = &[&INPUTS];
            let ret = info.stream_run.as_ref().map(|f| f(stream_ref, 4000, inputs_ref, &mut outputs)).unwrap_or(1);

            if let Some(free_fn) = &info.stream_free {
                free_fn(*stream.unwrap());
            }

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
            // Assuming ti_setup is implemented elsewhere
            // ti_setup(info, &INPUTS);
        }
        2 => {
            // No operation needed for goal == 2
        }
        _ => {
            panic!("Invalid goal value");
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
	println!("\n* bench_candle");
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
pub fn run_ti_stream1(info: &TiIndicatorInfo, options: &[f64], goal: i32) -> i32 {
	println!("\n* run_ti_stream1");
    lazy_static! {
        static ref INPUTS: std::sync::Mutex<[Option<Box<[f64]>>; 5]> = 
            std::sync::Mutex::new([None, None, None, None, None]);
    }

    match goal {
        0 => {
            let ind_offset = info.start.as_ref().map(|f| f(options)).unwrap_or(0);
            IND_OFFSET.store(ind_offset, Ordering::Relaxed);

            let mut stream = None;
            let sret = (info.stream_new)(Some(options), &mut stream);
            assert!(stream.is_some());
            assert_eq!(sret, 0);

            let stream = stream.unwrap();
            for i in 0..4000 {
                let inputs_guard = INPUTS.lock().unwrap();
                let ins: Vec<&[f64]> = inputs_guard.iter()
                    .filter_map(|input| input.as_ref().map(|slice| &slice[i..]))
                    .collect();

                let mut k = ti_stream_get_progress(&stream);
                if k < 0 {
                    k = 0;
                }

                let mut outstream1 = OUTSTREAM1.lock().unwrap();
                // Create mutable references by splitting the array first
                let (out0, rest) = outstream1[0].split_at_mut(k as usize);
                let (out1, rest) = rest.split_at_mut(rest.len());
                let (out2, _) = rest.split_at_mut(rest.len());
                let mut outs: Vec<&mut [f64]> = vec![out0, out1, out2];

                let ret = info.stream_run.as_ref().map(|f| f(&stream, 1, &ins, &mut outs)).unwrap_or(1);
                if ret != 0 {
                    println!("   *ERROR* ({})", ret);
                    println!("options:");
                    for j in 0..info.options {
                        println!("{} = {}", j, options[j as usize]);
                    }
                    return 1;
                }
            }

            if let Some(free_fn) = &info.stream_free {
                free_fn(*stream);
            }
        }
        1 => {
            let mut inputs_guard = INPUTS.lock().unwrap();
            let mut inputs: Vec<Option<&mut [f64]>> = inputs_guard.iter_mut()
                .map(|x| x.as_mut().map(|slice| &mut slice[..]))
                .collect();
            ti_setup(info, &mut inputs);
        }
        2 => {}
        _ => {
            panic!("Invalid goal value");
        }
    }

    0
}
pub fn bench_run(
    log: Option<&mut dyn Write>,
    info: &TiIndicatorInfo,
    run_info: &TiIndicatorInfo,
    fun: RunFun,
    name: &str,
) {
	println!("\n* bench_run");
    let mut options = [1.0; 10];
    let mut options_setter: Option<fn(f64, &mut [f64], i32)> = None;
    let mut options_setter_idx = 0;

    if let Some(ref info_name) = info.name {
        match info_name.as_str() {
            "alma" => options_setter_idx = alma_option_setter as usize,
            "adosc" => options_setter_idx = fast_slow_option_setter as usize,
            "apo" => options_setter_idx = ppo_option_setter as usize,
            "bbands" => options_setter_idx = bbands_option_setter as usize,
            "copp" => options_setter_idx = copp_option_setter as usize,
            "kc" => options_setter_idx = kc_option_setter as usize,
            "kst" => options_setter_idx = kst_option_setter as usize,
            "kvo" => options_setter_idx = fast_slow_option_setter as usize,
            "macd" => options_setter_idx = macd_option_setter as usize,
            "mama" => options_setter_idx = mama_option_setter as usize,
            "pfe" => options_setter_idx = pfe_option_setter as usize,
            "posc" => options_setter_idx = posc_option_setter as usize,
            "ppo" => options_setter_idx = ppo_option_setter as usize,
            "psar" => options_setter_idx = psar_option_setter as usize,
            "rvi" => options_setter_idx = rvi_option_setter as usize,
            "rmi" => options_setter_idx = rmi_option_setter as usize,
            "rmta" => options_setter_idx = rmta_option_setter as usize,
            "smi" => options_setter_idx = smi_option_setter as usize,
            "stoch" => options_setter_idx = stoch_option_setter as usize,
            "stochrsi" => options_setter_idx = stochrsi_option_setter as usize,
            "ultosc" => options_setter_idx = ultosc_option_setter as usize,
            "vidya" => options_setter_idx = vidya_option_setter as usize,
            "vosc" => options_setter_idx = fast_slow_option_setter as usize,
            _ => (),
        }
    }

    let bestof = BESTOF.load(std::sync::atomic::Ordering::Relaxed);
    let mut best_e = 1_000_000_000;
    let mut best_p = -1_000_000_000;

    for _best in 0..bestof {
        print!("Benchmark {:25}-{:16} ", info.name.as_deref().unwrap_or(""), name);
        std::io::stdout().flush().unwrap();

        let mut iterations = 0;
        let start = Instant::now();

        fun(run_info, None, 1);

        for _i in 0..1 {
            for period in 4..=150 {
                if let Some(setter) = options_setter {
                    setter(period as f64, &mut options, (std::ptr::eq(info, run_info)) as i32);
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

        fun(run_info, None, 2);

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
    }

    if let Some(log) = log {
        writeln!(
            log,
            ",\n    \"{}\" => array(\"elapsed\" => {}, \"performance\" => {})",
            name, best_e, best_p
        ).unwrap();
    }
}
pub fn bench_indicator(mut log: Option<&mut dyn Write>, info: Option<&TiIndicatorInfo>) {
	println!("\n* bench_indicator");
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
