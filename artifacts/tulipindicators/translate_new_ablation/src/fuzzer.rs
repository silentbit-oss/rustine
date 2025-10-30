use crate::*;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::os::raw::c_int;
use std::sync::Mutex;
use std::sync::atomic::Ordering;
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
pub fn check_output(
    info: &TiIndicatorInfo,
    size: i32,
    inputs: Option<&[&[f64]]>,
    options: Option<&[f64]>,
    outputs: Option<&mut [&mut [f64]]>,
) {
    let inputs = inputs.unwrap();
    let options = options.unwrap();
    let outputs = outputs.unwrap();

    let s = info.start.as_ref().map(|f| f(options)).unwrap_or(0);
    for o in 0..info.outputs {
        let mut max = 0.0;
        let mut min = 0.0;
        for i in 0..(size - s) as usize {
            let op = outputs[o as usize][i];
            let in_val = inputs[0][i + s as usize];
            max = if in_val > max { in_val } else { max };
            min = if in_val < min { in_val } else { min };

            match info.type_ {
                1 => {
                    if ((op > 4.0) && (op > ((max * 1.5) + 2.0)))
                        || ((op < -4.0) && (op < ((min * 0.5) - 3.0)))
                    {
                        println!("\nInputs:");
                        for k in 0..INPUT_SIZE {
                            print!(" {}", inputs[0][k]);
                        }

                        println!("\nOptions:");
                        for k in 0..info.options as usize {
                            print!(" {}", options[k]);
                        }

                        for j in 0..info.outputs {
                            println!("\nOutput[{}]:", j);
                            for k in 0..INPUT_SIZE {
                                print!(" {}", outputs[j as usize][k]);
                            }
                        }

                        println!(
                            "\nERROR Output is out of range for input: input: {} output: {}",
                            in_val, op
                        );
                        ERRORS_CNT.fetch_add(1, Ordering::SeqCst);
                        panic!("Output out of range");
                    }
                }
                _ => break,
            }
        }
    }
}
pub fn stress_indicator(info: *const TiIndicatorInfo) {
    let info = unsafe { &*info };
    let opt_count = info.options;
    
    let name = info.name.as_ref().unwrap();
    let full_name = info.full_name.as_ref().unwrap();
    println!("{} ({}) ({} options)", name, full_name, opt_count);
    
    let mut inputs: [*const f64; 16] = [std::ptr::null(); 16];
    let mut inputs0: [*const f64; 16] = [std::ptr::null(); 16];
    let mut outputs: [*mut f64; 16] = [std::ptr::null_mut(); 16];
    
    for i in 0..16 {
        inputs[i] = if i < info.inputs as usize { DUMMY_IN.lock().unwrap().as_ptr() } else { std::ptr::null() };
        inputs0[i] = if i < info.inputs as usize { DUMMY_IN0.lock().unwrap().as_ptr() } else { std::ptr::null() };
        outputs[i] = if i < info.outputs as usize { DUMMY_OT.lock().unwrap().as_ptr() as *mut f64 } else { std::ptr::null_mut() };
    }
    
    // Convert arrays to slices of slices for the function calls
    let dummy_in_guard = DUMMY_IN.lock().unwrap();
    let inputs_slice: &[&[f64]] = &[&dummy_in_guard[..]];
    let dummy_in0_guard = DUMMY_IN0.lock().unwrap();
    let inputs0_slice: &[&[f64]] = &[&dummy_in0_guard[..]];
    let mut dummy_ot_guard = DUMMY_OT.lock().unwrap();
    let mut outputs_slice: &mut [&mut [f64]] = &mut [&mut dummy_ot_guard[..]];
    
    let mut options_index: [c_int; 16] = [0; 16];
    let mut options: [f64; 16] = [0.0; 16];
    
    let (choices, optionsd) = if opt_count <= 4 {
        let choices = (std::mem::size_of_val(&*OPTIONSD_SMALL.lock().unwrap()) / std::mem::size_of::<f64>()) as c_int;
        (choices, OPTIONSD_SMALL.lock().unwrap().as_ptr())
    } else {
        let choices = (std::mem::size_of_val(&*OPTIONSD_LARGE.lock().unwrap()) / std::mem::size_of::<f64>()) as c_int;
        (choices, OPTIONSD_LARGE.lock().unwrap().as_ptr())
    };
    
    let mut count = 0;
    
    loop {
        count += 1;
        
        for j in 0..opt_count {
            let idx = options_index[j as usize] as isize;
            options[j as usize] = unsafe { *optionsd.offset(idx) };
            print!(" {}", options[j as usize]);
        }
        
        let rz = (info.indicator)(INPUT_SIZE as i32, Some(inputs0_slice), Some(&options), Some(&mut outputs_slice));
        if rz == 0 {
            check_output(info, INPUT_SIZE as i32, Some(inputs0_slice), Some(&options), Some(&mut outputs_slice));
        }
        
        for s in 0..SIZES_COUNT {
            let size = SIZES[s];
            print!(" {}", size);
            
            let r = (info.indicator)(size, Some(inputs_slice), Some(&options), Some(&mut outputs_slice));
            if r == 0 {
                check_output(info, size, Some(inputs_slice), Some(&options), Some(&mut outputs_slice));
            }
            
            if !std::ptr::addr_of!(info.indicator_ref).is_null() {
                print!(" r");
                let func = info.indicator_ref;
                let rr = func(size, Some(inputs_slice), Some(&options), Some(&mut outputs_slice));
                if rr == 0 {
                    check_output(info, size, Some(inputs_slice), Some(&options), Some(&mut outputs_slice));
                }
            }
            
            if !std::ptr::addr_of!(info.stream_new).is_null() {
                let mut stream: Option<Box<TiStream>> = None;
                let new_func = info.stream_new;
                let rs = new_func(Some(&options), &mut stream);
                
                if rs == 0 && stream.is_some() {
                    if let Some(run_func) = &info.stream_run {
                        print!(" s");
                        let rsc = run_func(stream.as_ref().unwrap().as_ref(), size, inputs_slice, &mut outputs_slice);
                        if rsc == 0 {
                            check_output(info, size, Some(inputs_slice), Some(&options), Some(&mut outputs_slice));
                        }
                        
                        for _ in 0..5 {
                            let _ = run_func(stream.as_ref().unwrap().as_ref(), size, inputs_slice, &mut outputs_slice);
                        }
                    }
                    
                    if let Some(free_func) = &info.stream_free {
                        let stream_box = stream.unwrap();
                        free_func(*stream_box);
                    }
                }
            }
        }
        
        print!("\r                                                                          \r");
        
        let mut j = 0;
        loop {
            options_index[j] = (options_index[j] + 1) % choices;
            if options_index[j] != 0 {
                break;
            }
            j += 1;
        }
        
        if j > opt_count as usize {
            break;
        }
    }
    
    let expected_count = (choices as f64).powi(opt_count);
    assert!(0.1 > (count as f64 - expected_count).abs());
}
pub fn stress_candle(info: &TcCandleInfo) {
    println!("{} ({})", 
        info.name.as_deref().unwrap_or(""), 
        info.full_name.as_deref().unwrap_or("")
    );

    let dummy_in = DUMMY_IN.lock().unwrap();
    let dummy_in0 = DUMMY_IN0.lock().unwrap();
    
    let inputs = [&dummy_in[..], &dummy_in[..], &dummy_in[..], &dummy_in[..]];
    let inputs0 = [&dummy_in0[..], &dummy_in0[..], &dummy_in0[..], &dummy_in0[..]];
    
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
    
    let mut output = match tc_result_new() {
        Some(res) => res,
        None => return,
    };

    for &size in &SIZES {
        (info.candle)(size, &inputs, &config, &mut output);
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
            assert!(patterns != ((1 << 26) - 1));
        }

        (info.candle)(size, &inputs0, &config, &mut output);
        assert!(tc_result_count(&output) <= size);
        assert!(tc_result_pattern_count(&output) <= size);
    }

    tc_result_free(Some(Box::new(output)));
}
