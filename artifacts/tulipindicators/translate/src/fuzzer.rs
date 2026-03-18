use crate::*;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
use lazy_static::lazy_static;

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
pub fn stress_indicator(info: &TiIndicatorInfo) {
    let opt_count = info.options;
    println!("{} ({}) ({} options)", 
        info.name.as_ref().unwrap_or(&String::new()), 
        info.full_name.as_ref().unwrap_or(&String::new()), 
        opt_count);

    let mut inputs: [Option<Vec<f64>>; 16] = [(); 16].map(|_| None);
    let mut inputs0: [Option<Vec<f64>>; 16] = [(); 16].map(|_| None);
    let mut outputs: [Option<Vec<f64>>; 16] = [(); 16].map(|_| None);

    {
        let dummy_in = DUMMY_IN.lock().unwrap();
        let dummy_in0 = DUMMY_IN0.lock().unwrap();
        let dummy_ot = DUMMY_OT.lock().unwrap();

        for i in 0..16 {
            inputs[i] = if i < info.inputs as usize { Some(dummy_in.to_vec()) } else { None };
            inputs0[i] = if i < info.inputs as usize { Some(dummy_in0.to_vec()) } else { None };
            outputs[i] = if i < info.outputs as usize { Some(dummy_ot.to_vec()) } else { None };
        }
    }

    let mut options_index = [0; 16 + 1];
    let mut options = [0.0; 16];
    
    let (choices, optionsd_vec) = if opt_count <= 4 {
        let optionsd_small = OPTIONSD_SMALL.lock().unwrap();
        (optionsd_small.len(), optionsd_small.to_vec())
    } else {
        let optionsd_large = OPTIONSD_LARGE.lock().unwrap();
        (optionsd_large.len(), optionsd_large.to_vec())
    };
    let optionsd = optionsd_vec.as_slice();

    let mut count = 0;
    let mut j = 0;
    
    loop {
        count += 1;
        
        for j in 0..opt_count as usize {
            options[j] = optionsd[options_index[j]];
            print!(" {}", options[j]);
        }

        let inputs0_refs: Vec<&[f64]> = inputs0.iter().filter_map(|x| x.as_ref().map(|v| v.as_slice())).collect();
        let mut outputs_refs: Vec<&mut [f64]> = outputs.iter_mut().filter_map(|x| x.as_mut().map(|v| v.as_mut_slice())).collect();

        let rz = (info.indicator)(INPUT_SIZE as i32, Some(&inputs0_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
        if rz == 0 {
            check_output(info, INPUT_SIZE as i32, Some(&inputs0_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
        }

        for s in 0..SIZES_COUNT {
            let size = SIZES[s];
            print!(" {}", size);
            
            let inputs_refs: Vec<&[f64]> = inputs.iter().filter_map(|x| x.as_ref().map(|v| v.as_slice())).collect();
            let mut outputs_refs: Vec<&mut [f64]> = outputs.iter_mut().filter_map(|x| x.as_mut().map(|v| v.as_mut_slice())).collect();

            let r = (info.indicator)(size, Some(&inputs_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
            if r == 0 {
                check_output(info, size, Some(&inputs_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
            }

            // Always call indicator_ref if present
            print!(" r");
            let rr = (info.indicator_ref)(size, Some(&inputs_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
            if rr == 0 {
                check_output(info, size, Some(&inputs_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
            }

            // Always call stream_new if present
            let stream_new_fn = info.stream_new;
            let mut stream: Option<Box<TiStream>> = None;
            let rs = stream_new_fn(Some(&options[..opt_count as usize]), &mut stream);
            if rs == 0 && stream.is_some() {
                print!(" s");
                if let Some(stream_run) = info.stream_run.as_deref() {
                    let stream_ref = stream.as_ref().unwrap();
                    
                    let inputs_refs: Vec<&[f64]> = inputs.iter().filter_map(|x| x.as_ref().map(|v| v.as_slice())).collect();
                    let mut outputs_refs: Vec<&mut [f64]> = outputs.iter_mut().filter_map(|x| x.as_mut().map(|v| v.as_mut_slice())).collect();

                    let rsc = stream_run(stream_ref, size, &inputs_refs, &mut outputs_refs[..info.outputs as usize]);
                    if rsc == 0 {
                        check_output(info, size, Some(&inputs_refs), Some(&options[..opt_count as usize]), Some(&mut outputs_refs[..info.outputs as usize]));
                    }

                    for _ in 0..5 {
                        let _ = stream_run(stream_ref, size, &inputs_refs, &mut outputs_refs[..info.outputs as usize]);
                    }
                }

                if let Some(stream_free) = info.stream_free.as_deref() {
                    stream_free(*stream.unwrap());
                }
            }
        }

        print!("\r                                                                          \r");
        
        j = 0;
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

    assert!((count as f64 - (choices as f64).powi(opt_count as i32)).abs() < 0.1);
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
