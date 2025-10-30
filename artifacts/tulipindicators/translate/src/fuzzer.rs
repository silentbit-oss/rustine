use crate::*;
use std::f64;
use lazy_static::lazy_static;
use std::fmt::Write;

pub fn banner() {
    println!("  ______ _    _ __________________ _____  ");
    println!(" |  ____| |  | |___  /___  /  ____|  __ \\ ");
    println!(" | |__  | |  | |  / /   / /| |__  | |__) |");
    println!(" |  __| | |  | | / /   / / |  __| |  _  / ");
    println!(" | |    | |__| |/ /__ / /__| |____| | \\ \\ ");
    println!(" |_|     \\____//_____/_____|______|_|  \\_\\");
    println!();
    println!("This program tries each indicator with a lot of options.");
    println!("It's good for checking for crashes or assertion failures.");
    println!("Use with a memory tool to check for memory errors in ti.");
    println!();
}
pub fn helper_check_output_1(
    info: &TiIndicatorInfo,
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
    s: i32,
    o: i32,
) {
    let mut max = 0.0;
    let mut min = 0.0;
    
    for i in 0..(size - s) as usize {
        let op = outputs[o as usize][i];
        let in_val = inputs[0][i + s as usize];
        
        max = if in_val > max { in_val } else { max };
        min = if in_val < min { in_val } else { min };
        
        match info.type_ {
            1 => {
                if (op > 4.0 && op > (max * 1.5 + 2.0)) || (op < -4.0 && op < (min * 0.5 - 3.0)) {
                    let mut message = String::new();
                    
                    writeln!(message, "\nInputs:").unwrap();
                    for k in 0..INPUT_SIZE {
                        write!(message, " {}", inputs[0][k]).unwrap();
                    }
                    
                    writeln!(message, "\nOptions:").unwrap();
                    for k in 0..info.options as usize {
                        write!(message, " {}", options[k]).unwrap();
                    }
                    
                    for j in 0..info.outputs as usize {
                        writeln!(message, "\nOutput[{}]:", j).unwrap();
                        for k in 0..INPUT_SIZE {
                            write!(message, " {}", outputs[j][k]).unwrap();
                        }
                    }
                    
                    println!("{}", message);
                    println!("\nERROR Output is out of range for input: input: {} output: {}", in_val, op);
                    ERRORS_CNT.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
                    panic!("Output is out of range");
                }
            }
            _ => {}
        }
    }
}
pub fn check_output(
    info: &TiIndicatorInfo,
    size: i32,
    inputs: &[&[f64]],
    options: &[f64],
    outputs: &mut [&mut [f64]],
) {
    let s = match &info.start {
        Some(f) => f(options),
        None => 0, // Default value when start function is None
    };
    
    for o in 0..info.outputs {
        helper_check_output_1(info, size, inputs, options, outputs, s, o);
    }
}
pub fn helper_helper_stress_indicator_1_1(
    info: &mut TiIndicatorInfo,
    inputs: &[&[f64]],
    outputs: &mut [&mut [f64]],
    options: &[f64],
    s: usize,
) {
    let size = SIZES[s];
    print!(" {}", size);

    let r = (info.indicator)(size as i32, inputs, options, outputs);
    if r == 0 {
        check_output(info, size as i32, inputs, options, outputs);
    }

    if info.indicator_ref as usize != 0 {
        print!(" r");
        let rr = (info.indicator_ref)(size as i32, inputs, options, outputs);
        if rr == 0 {
            check_output(info, size as i32, inputs, options, outputs);
        }
    }

    if info.stream_new as usize != 0 {
        let mut stream: Option<Box<TiStream>> = Option::None;
        let rs = (info.stream_new)(Some(options), &mut stream);
        if rs == 0 && stream.is_some() {
            print!(" s");
            // First check output before mutable borrow
            let rsc = {
                let stream_run = info.stream_run.as_mut().unwrap();
                let stream_clone = stream.as_ref().unwrap().clone();
                stream_run(
                    *stream_clone,
                    size as i32,
                    Some(inputs.iter().map(|&x| Some(x.to_vec())).collect()),
                    Some(outputs.iter_mut().map(|x| Some(x.to_vec())).collect()),
                )
            };
            if rsc == 0 {
                check_output(info, size as i32, inputs, options, outputs);
            }

            for _repeat in 0..5 {
                let stream_run = info.stream_run.as_mut().unwrap();
                let stream_clone = stream.as_ref().unwrap().clone();
                let _ = stream_run(
                    *stream_clone,
                    size as i32,
                    Some(inputs.iter().map(|&x| Some(x.to_vec())).collect()),
                    Some(outputs.iter_mut().map(|x| Some(x.to_vec())).collect()),
                );
            }
            (info.stream_free)(stream);
        }
    }
}
pub fn helper_stress_indicator_1(
    j_ref: &mut i32,
    count_ref: &mut i32,
    info: &mut TiIndicatorInfo,  // Changed from & to &mut
    opt_count: i32,
    inputs: &[&[f64]],
    inputs0: &[&[f64]],
    outputs: &mut [&mut [f64]],
    options_index: &mut [i32],
    options: &mut [f64],
    choices: i32,
    optionsd: &[f64],
    optionsd_idx: usize,
) {
    let mut j = *j_ref;
    let mut count = *count_ref;
    count += 1;

    for j in 0..opt_count {
        options[j as usize] = optionsd[options_index[j as usize] as usize + optionsd_idx];
        print!(" {}", options[j as usize]);
    }

    let rz = (info.indicator)(INPUT_SIZE as i32, inputs0, options, outputs);
    if rz == 0 {
        check_output(info, INPUT_SIZE as i32, inputs0, options, outputs);
    }

    for s in 0..SIZES_COUNT {
        helper_helper_stress_indicator_1_1(info, inputs, outputs, options, s);
    }

    print!("\r                                                                          \r");
    
    j = 0;
    loop {
        options_index[j as usize] = (options_index[j as usize] + 1) % choices;
        if options_index[j as usize] != 0 {
            break;
        }
        j += 1;
    }

    *j_ref = j;
    *count_ref = count;
}
pub fn stress_indicator(info: &mut TiIndicatorInfo) {
    let opt_count = info.options;
    println!(
        "{} ({}) ({} options)",
        info.name.as_deref().unwrap_or(""),
        info.full_name.as_deref().unwrap_or(""),
        opt_count
    );

    let mut inputs: [Option<&[f64]>; 16] = [None; 16];
    let mut inputs0: [Option<&[f64]>; 16] = [None; 16];
    let mut outputs: [Option<*mut f64>; 16] = [None; 16];

    // Lock the mutexes for inputs and outputs
    let dummy_in = DUMMY_IN.lock().unwrap();
    let dummy_in0 = DUMMY_IN0.lock().unwrap();
    let mut dummy_ot = DUMMY_OT.lock().unwrap();

    // First collect all the input references
    for i in 0..16 {
        inputs[i] = if i < info.inputs as usize {
            Some(&*dummy_in)
        } else {
            None
        };
        inputs0[i] = if i < info.inputs as usize {
            Some(&*dummy_in0)
        } else {
            None
        };
    }

    // Get a mutable pointer to the output array
    let ptr = dummy_ot.as_mut_ptr();
    // Handle outputs by storing the raw pointer for each output
    for i in 0..16 {
        outputs[i] = if i < info.outputs as usize {
            Some(ptr)
        } else {
            None
        };
    }

    let mut options_index = [0; 16 + 1];
    let mut options = [0.0; 16];
    let choices;
    let optionsd_idx;

    let optionsd_small = OPTIONSD_SMALL.lock().unwrap();
    let optionsd_large = OPTIONSD_LARGE.lock().unwrap();

    if opt_count <= 4 {
        choices = optionsd_small.len() as i32;
        optionsd_idx = optionsd_small.as_ptr() as usize;
    } else {
        choices = optionsd_large.len() as i32;
        optionsd_idx = optionsd_large.as_ptr() as usize;
    }

    let mut j = 0;
    let mut count = 0;

    loop {
        let inputs_vec: Vec<&[f64]> = inputs.iter().filter_map(|x| *x).collect();
        let inputs0_vec: Vec<&[f64]> = inputs0.iter().filter_map(|x| *x).collect();
        let mut outputs_vec: Vec<&mut [f64]> = Vec::new();
        for i in 0..16 {
            if let Some(ptr) = outputs[i] {
                // Convert raw pointer to mutable slice
                let slice = unsafe { std::slice::from_raw_parts_mut(ptr, 20) };
                outputs_vec.push(slice);
            }
        }

        if opt_count <= 4 {
            helper_stress_indicator_1(
                &mut j,
                &mut count,
                info,
                opt_count,
                &inputs_vec,
                &inputs0_vec,
                &mut outputs_vec,
                &mut options_index,
                &mut options,
                choices,
                &optionsd_small[..],
                optionsd_idx,
            );
        } else {
            helper_stress_indicator_1(
                &mut j,
                &mut count,
                info,
                opt_count,
                &inputs_vec,
                &inputs0_vec,
                &mut outputs_vec,
                &mut options_index,
                &mut options,
                choices,
                &optionsd_large[..],
                optionsd_idx,
            );
        }

        if j > opt_count {
            break;
        }
    }

    assert!(
        0.1 > f64::abs(count as f64 - f64::powi(choices as f64, opt_count))
    );
}
pub fn stress_candle(info: &TcCandleInfo) {
    println!("{} ({})", 
        info.name.as_ref().unwrap_or(&String::new()), 
        info.full_name.as_ref().unwrap_or(&String::new())
    );

    let dummy_in_ref = &*DUMMY_IN.lock().unwrap();
    let dummy_in0_ref = &*DUMMY_IN0.lock().unwrap();
    
    // Convert arrays to slices
    let inputs: [&[f64]; 4] = [dummy_in_ref, dummy_in_ref, dummy_in_ref, dummy_in_ref];
    let inputs0: [&[f64]; 4] = [dummy_in0_ref, dummy_in0_ref, dummy_in0_ref, dummy_in0_ref];
    
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
    
    let mut output = tc_result_new().expect("Failed to create TcResult");
    
    for &size in &SIZES {
        (info.candle)(
            size,
            Some(&inputs[..]),
            &config,
            &mut output
        );
        
        assert!(tc_result_count(&output) <= size);
        assert!(tc_result_pattern_count(&output) <= size);
        
        for i in 0..tc_result_count(&output) {
            let hit = tc_result_get(&output, i);
            assert!(hit.patterns != ((1 << 26) - 1));
            assert!(hit.index >= 0);
            assert!(hit.index < size);
        }
        
        for i in 0..size {
            let patterns = tc_result_at(&output, i);
            assert!(patterns != ((1 << 26) - 1) as i32);
        }
        
        (info.candle)(
            size,
            Some(&inputs0[..]),
            &config,
            &mut output
        );
        
        assert!(tc_result_count(&output) <= size);
        assert!(tc_result_pattern_count(&output) <= size);
    }
    
    tc_result_free(Some(output));
}
