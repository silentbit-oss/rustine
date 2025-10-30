use libc::FILE;
use std::fs::File;
use crate::*;
use std::io::BufRead;
use std::io::BufReader;
use std::io::Read;
use std::io::Write;
use std::f64;
use std::io;
use std::str::FromStr;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::ffi::CStr;
use std::path::Path;
use std::os::raw::c_char;

pub fn next_line(fp: &mut impl io::Read) -> Option<&'static str> {
    static mut buf: [u8; 4096] = [0; 4096];
    
    // SAFETY: We ensure single-threaded access to the static buffer
    unsafe {
        let mut reader = io::BufReader::new(fp);
        let mut vec_buf = Vec::new();
        while let Ok(bytes_read) = reader.read_until(b'\n', &mut vec_buf) {
            if bytes_read == 0 {
                return None;
            }
            
            // Copy the read data to our static buffer
            buf[..bytes_read].copy_from_slice(&vec_buf[..bytes_read]);
            
            // Skip lines starting with '#' or empty lines (only newline characters)
            if buf[0] == b'#' || buf[0] == 10 || buf[0] == 13 {
                vec_buf.clear();
                continue;
            }
            
            // Convert to str and remove trailing newline if present
            if let Ok(s) = std::str::from_utf8(&buf[..bytes_read]) {
                return Some(s.trim_end());
            }
            
            vec_buf.clear();
        }
    }
    
    None
}

lazy_static! {
    pub static ref LTESTS: AtomicI32 = AtomicI32::new(0);
    pub static ref LFAILS: AtomicI32 = AtomicI32::new(0);
}

pub fn get_array(fp: &mut impl std::io::Read, s: &mut [f64]) -> Option<usize> {
    let line = next_line(fp)?;
    
    if !line.starts_with('{') {
        println!("Bad input");
        LTESTS.fetch_add(1, Ordering::SeqCst);
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 85);
        return None;
    }

    let mut tokens = line[1..].split(|c| c == ',' || c == '}' || c == '\r' || c == '\n');
    let mut inp_idx = 0;

    for token in tokens {
        if token.is_empty() {
            continue;
        }
        
        if inp_idx >= s.len() {
            break;
        }

        match f64::from_str(token) {
            Ok(num) => {
                s[inp_idx] = num;
                inp_idx += 1;
            }
            Err(_) => return None,
        }
    }

    Some(inp_idx)
}
pub fn compare_arrays(a: &[f64], b: &[f64], size_a: usize, size_b: usize) {
    // Increment ltests and check size mismatch
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if size_a != size_b {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 42, size_a, size_b);
    }

    if size_a != size_b {
        println!("Size mismatch.");
    }

    let f = LFAILS.load(Ordering::SeqCst);
    
    // Compare elements
    for i in 0..size_a {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (a[i] - b[i]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 50, a[i], b[i]);
        }
    }

    // Print comparison if there were new failures
    if LFAILS.load(Ordering::SeqCst) != f {
        println!("Expected      Got");
        for i in 0..size_a {
            println!("{:8.3} {:8.3}", a[i], b[i]);
        }
    }
}
pub fn test_localbuffer() {
    #[repr(C)]
    struct S {
        buf_info: BufInfo,
        padding: [f64; 5],
    }

    #[repr(C)]
    struct BufInfo {
        padding: f64,
        zero: [i32; 4],
        offset_a: i32,
        size_a: i32,
        index_a: i32,
        padding_a: i32,
    }

    let mut stream = S {
        buf_info: BufInfo {
            padding: 0.0,
            zero: [0; 4],
            offset_a: 0,
            size_a: 0,
            index_a: 0,
            padding_a: 0,
        },
        padding: [0.0; 5],
    };

    // First block
    {
        let buf_info = &mut stream.buf_info;
        buf_info.offset_a = buf_info.zero[1] + buf_info.zero[0];
        buf_info.size_a = 5;
        buf_info.index_a = -1;
    }

    // Second block (test)
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let buf_info = &stream.buf_info;
        let sum = buf_info.zero[1] + buf_info.zero[0];
        if sum != 5 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 395, sum, 5);
        }
    }

    // Third block (write)
    {
        let buf_info = &mut stream.buf_info;
        let mut idx = buf_info.index_a + 1;
        if idx == buf_info.size_a {
            idx = 0;
        }
        stream.padding[(buf_info.offset_a + idx) as usize] = 100.0;
        buf_info.index_a = idx;
    }

    // Fourth block (read)
    let get = {
        let buf_info = &stream.buf_info;
        let mut idx = buf_info.index_a;
        
        // Handle wrapping
        let size = buf_info.size_a;
        while idx >= size {
            idx -= size;
        }
        while idx < 0 {
            idx += size;
        }

        stream.padding[(buf_info.offset_a + idx) as usize]
    };

    // Fifth block (test)
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(get - 100.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 400, get, 100.0);
        }
    }
}
pub fn helper_helper_helper_test_ind_name_3_1_1(
    i_ref: &mut i32,
    info: &mut TiIndicatorInfo,
    inputs: &[Option<Vec<f64>>; 16],
    outputs: &mut [Option<Vec<f64>>; 16],
    input_size: i32,
    step: i32,
    stream: &mut TiStream,
    bar: i32,
) {
    let mut i = *i_ref;
    let mut ins: [Option<Vec<f64>>; 16] = Default::default();
    let mut outs: [Option<Vec<f64>>; 16] = Default::default();

    for i in 0..info.inputs {
        if let Some(input) = &inputs[i as usize] {
            ins[i as usize] = Some(input[bar as usize..].to_vec());
        }
    }

    for i in 0..info.outputs {
        let progress = ti_stream_get_progress(stream).max(0);
        if let Some(output) = &outputs[i as usize] {
            outs[i as usize] = Some(output[progress as usize..].to_vec());
        }
    }

    let mut stride = step;
    if (stride + bar) >= input_size {
        stride = input_size - bar;
    }

    let ret = if let Some(stream_run) = &mut info.stream_run {
        // Convert arrays to vectors before passing to stream_run
        let ins_vec: Vec<Option<Vec<f64>>> = ins.into_iter().collect();
        let outs_vec: Vec<Option<Vec<f64>>> = outs.into_iter().collect();
        
        stream_run(
            stream.clone(),
            stride,
            Some(ins_vec),
            Some(outs_vec),
        )
    } else {
        -1
    };

    LTESTS.fetch_add(1, Ordering::SeqCst);
    if ret != 0 {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 222);
    }

    *i_ref = i;
}

pub fn helper_helper_test_ind_name_3_1(
    i_ref: &mut i32,
    info: &mut TiIndicatorInfo,
    options: &[f64; 16],
    inputs: &[Option<Vec<f64>>; 16],
    answers: &[Option<Vec<f64>>; 16],
    outputs: &mut [Option<Vec<f64>>; 16],
    input_size: i32,
    answer_size: i32,
    steps: &[i32],
    step_i: i32,
) {
    let mut i = *i_ref;
    let step = steps[step_i as usize];
    
    // Initialize outputs with zeros
    for i in 0..info.outputs {
        if let Some(output) = &mut outputs[i as usize] {
            output.fill(0.0);
        }
    }

    let mut stream: Option<Box<TiStream>> = None;
    let stream_ret = (info.stream_new)(Some(options), &mut stream);

    // Test stream_ret == 0
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if stream_ret != 0 {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        let _ = writeln!(&mut std::io::stderr(), "/c2rust_final/subjects/tulipindicators/smoke.c:201 error");
    }

    // Test stream != 0
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if stream.is_none() {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        let _ = writeln!(&mut std::io::stderr(), "/c2rust_final/subjects/tulipindicators/smoke.c:202 error");
    }

    // Process each bar
    for bar in (0..input_size).step_by(step as usize) {
        helper_helper_helper_test_ind_name_3_1_1(
            &mut i,
            info,
            inputs,
            outputs,
            input_size,
            step,
            stream.as_mut().unwrap(),
            bar,
        );
    }

    let mut output_size = input_size - (info.start.as_ref().unwrap())(options);
    if output_size < 0 {
        output_size = 0;
    }

    // Test stream progress
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if ti_stream_get_progress(stream.as_ref().unwrap()) != output_size {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        let _ = writeln!(
            &mut std::io::stderr(),
            "/c2rust_final/subjects/tulipindicators/smoke.c:227 ({} != {})",
            ti_stream_get_progress(stream.as_ref().unwrap()),
            output_size
        );
    }

    // Compare arrays
    for i in 0..info.outputs {
        if let (Some(answer), Some(output)) = (&answers[i as usize], &outputs[i as usize]) {
            compare_arrays(
                answer,
                output,
                answer_size as usize,
                output_size as usize,
            );
        }
    }

    (info.stream_free)(stream);
    *i_ref = i;
}
pub fn helper_test_ind_name_3(
    i_ref: &mut i32,
    info: &mut TiIndicatorInfo,
    options: &[f64; 16],
    inputs: &[Option<Vec<f64>>; 16],
    answers: &[Option<Vec<f64>>; 16],
    outputs: &mut [Option<Vec<f64>>; 16],
    input_size: i32,
    answer_size: i32,
) {
    let mut i = *i_ref;
    let steps = [1, 2, 3, 4, 5, 7, 13, 100, 1024];
    let step_count = steps.len();
    
    for step_i in 0..step_count {
        helper_helper_test_ind_name_3_1(
            &mut i,
            info,
            options,
            inputs,
            answers,
            outputs,
            input_size,
            answer_size,
            &steps,
            step_i as i32,
        );
    }
    
    *i_ref = i;
}
pub fn helper_helper_test_candles_1_1(
    output: &TcResult,
    negate: bool,
    info: &TcCandleInfo,
    num: &str,
) {
    let pos = num.parse::<i32>().unwrap_or(0); // Equivalent to atoi
    
    if negate {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (tc_result_at(output, pos) & info.pattern as i32) != 0 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 290);
        }
    } else {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (tc_result_at(output, pos) & info.pattern as i32) == 0 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 292);
        }
    }
}
pub fn helper_test_candles_1(
    fp: &mut std::fs::File,
    count: i32,
    output: &mut TcResult,
    buf: &mut [u8; 4096],
) {
    let reader = BufReader::new(fp);
    
    for line in reader.lines() {
        let line = match line {
            Ok(l) => l,
            Err(_) => break,
        };

        if line.is_empty() {
            break;
        }

        let mut chars = line.chars();
        let first_char = match chars.next() {
            Some(c) => c,
            None => break,
        };

        if first_char != '!' && !first_char.is_ascii_lowercase() {
            break;
        }

        let mut parts = line.split_whitespace();
        let name = parts.next().unwrap();
        
        let mut name_idx = 0;
        let mut negate = false;
        
        if name.starts_with('!') {
            negate = true;
            name_idx += 1;
        }

        let info = tc_find_candle(Some(&name[name_idx..]));
        
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if info.is_none() {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("/c2rust_final/subjects/tulipindicators/smoke.c:282 error");
        }

        let info = match info {
            Some(i) => i,
            None => continue,
        };

        for num in parts {
            helper_helper_test_candles_1_1(output, negate, info, num);
        }

        let tc_candles = TC_CANDLES.lock().unwrap();
        let cnd_num = (info as *const TcCandleInfo as usize - &*tc_candles as *const _ as usize) 
            / std::mem::size_of::<TcCandleInfo>();

        if count != 0 {
            let mut tested_cnd = TESTED_CND.lock().unwrap();
            tested_cnd[cnd_num] = 1;
        }
    }
}
pub fn test_candles(fp: &mut std::fs::File, count: i32) {
    // Initialize inputs as a Vec of Vec<TC_REAL> (equivalent to double*[])
    let mut inputs: Vec<Vec<TC_REAL>> = vec![Vec::new(); 4];
    let mut input_size = 0;
    
    // Get input arrays from file
    for i in 0..4 {
        inputs[i] = vec![0.0; 1024]; // Allocate space for 1024 TC_REAL values
        input_size = get_array(fp, &mut inputs[i]).expect("Failed to read array from file") as i32;
    }

    // Initialize config
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

    // Create new result
    let mut output = match tc_result_new() {
        Some(res) => res,
        None => return, // Handle allocation failure
    };

    // Prepare input references for tc_run
    let input_refs: Vec<&[TC_REAL]> = inputs.iter().map(|v| v.as_slice()).collect();

    // Run the main function
    tc_run((1 << 26) - 1, input_size, &input_refs, &config, &mut output);

    // Process results in a loop
    let mut buf = [0u8; 4096];
    loop {
        helper_test_candles_1(fp, count, &mut output, &mut buf);
    }

    // Cleanup is automatic in Rust (Vecs and Box will be dropped)
}

pub fn helper_test_ind_name_1(
    i_ref: &mut i32,
    info: &TiIndicatorInfo,
    options: &[f64; 16],
    inputs: &[&[f64]; 16],
    answers: &[&[f64]; 16],
    outputs: &mut [&mut [f64]; 16],
    input_size: i32,
    answer_size: i32,
) {
    let mut i = *i_ref;
    let ret = (info.indicator)(input_size, inputs, options, outputs);
    
    // Increment test counter and check for failure
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if ret != 0 {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 160);
    }

    // Calculate output size
    let mut output_size = input_size - (info.start.as_ref().unwrap())(options);
    if output_size < 0 {
        output_size = 0;
    }

    // Compare each output array with corresponding answer
    for i in 0..info.outputs {
        compare_arrays(answers[i as usize], outputs[i as usize], answer_size as usize, output_size as usize);
    }

    *i_ref = i;
}

pub fn helper_test_ind_name_2(
    i_ref: &mut i32,
    info: &TiIndicatorInfo,
    options: &[f64; 16],
    inputs: &[&[f64]; 16],
    answers: &[&[f64]; 16],
    outputs: &mut [&mut [f64]; 16],
    input_size: i32,
    answer_size: i32,
) {
    let mut i = *i_ref;
    
    // Clear outputs
    for output in outputs.iter_mut() {
        output.fill(0.0);
    }

    // Call indicator function
    let ret = (info.indicator_ref)(input_size, inputs, options, outputs);

    // Update test counters
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if ret != 0 {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 176);
    }

    // Calculate output size
    let output_size = if let Some(start_fn) = &info.start {
        let start = start_fn(options);
        (input_size - start).max(0)
    } else {
        0
    };

    // Compare arrays
    for j in 0..info.outputs {
        compare_arrays(
            answers[j as usize],
            outputs[j as usize],
            answer_size as usize,
            output_size as usize,
        );
    }

    *i_ref = i;
}
pub fn test_ind_name(fp: &mut std::fs::File, name: Option<&str>, count: i32) {
    let info = match ti_find_indicator(name) {
        Some(info) => info,
        None => {
            println!("(WARN) Couldn't find indicator {:?}", name);
            println!("---------------------------------------------");
            
            let mut buf = String::with_capacity(4096);
            let mut reader = std::io::BufReader::new(fp);
            while reader.read_line(&mut buf).unwrap() > 0 {
                if !(buf.starts_with('{') || buf.starts_with('#')) {
                    break;
                }
                buf.clear();
            }
            return;
        }
    };

    let ti_indicators = TI_INDICATORS.lock().unwrap();
    let ind_num = (info as *const TiIndicatorInfo as usize - ti_indicators.as_ptr() as usize) / std::mem::size_of::<TiIndicatorInfo>();
    drop(ti_indicators); // Release the lock early

    if count != 0 {
        let mut tested_ind = TESTED_IND.lock().unwrap();
        tested_ind[ind_num] = 1;
    }

    let mut options = [0.0; 16];
    let mut o_idx = 0;
    
    for token in name.unwrap_or("").split_whitespace() {
        if o_idx >= 16 {
            break;
        }
        options[o_idx] = f64::from_str(token).unwrap_or(0.0);
        o_idx += 1;
    }

    // Perform the test
    LTESTS.fetch_add(1, Ordering::SeqCst);
    if o_idx != info.options as usize {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!(
            "{}:{} ({} != {})",
            "/c2rust_final/subjects/tulipindicators/smoke.c",
            137,
            o_idx,
            info.options
        );
    }

    let mut inputs: [Option<Vec<f64>>; 16] = Default::default();
    let mut answers: [Option<Vec<f64>>; 16] = Default::default();
    let mut outputs: [Option<Vec<f64>>; 16] = Default::default();
    let mut input_size = 0;

    for i in 0..info.inputs {
        let mut input = vec![0.0; 1024];
        input_size = get_array(fp, &mut input).expect("Failed to read input array");
        inputs[i as usize] = Some(input);
    }

    let mut answer_size = 0;
    for i in 0..info.outputs {
        let mut answer = vec![0.0; 1024];
        let mut output = vec![0.0; 1024];
        answer_size = get_array(fp, &mut answer).expect("Failed to read answer array");
        answers[i as usize] = Some(answer);
        outputs[i as usize] = Some(output);
    }

    // Prepare slices for helper functions
    let mut input_slices: [&[f64]; 16] = [&[]; 16];
    for i in 0..16 {
        input_slices[i] = inputs[i].as_ref().map(|v| v.as_slice()).unwrap_or(&[]);
    }

    let mut answer_slices: [&[f64]; 16] = [&[]; 16];
    for i in 0..16 {
        answer_slices[i] = answers[i].as_ref().map(|v| v.as_slice()).unwrap_or(&[]);
    }

    let mut i = 0;
    {
        // Create separate arrays for each mutable reference
        let mut dummy0 = [0.0; 0];
        let mut dummy1 = [0.0; 0];
        let mut dummy2 = [0.0; 0];
        let mut dummy3 = [0.0; 0];
        let mut dummy4 = [0.0; 0];
        let mut dummy5 = [0.0; 0];
        let mut dummy6 = [0.0; 0];
        let mut dummy7 = [0.0; 0];
        let mut dummy8 = [0.0; 0];
        let mut dummy9 = [0.0; 0];
        let mut dummy10 = [0.0; 0];
        let mut dummy11 = [0.0; 0];
        let mut dummy12 = [0.0; 0];
        let mut dummy13 = [0.0; 0];
        let mut dummy14 = [0.0; 0];
        let mut dummy15 = [0.0; 0];

        let mut slices: [&mut [f64]; 16] = [
            &mut dummy0,
            &mut dummy1,
            &mut dummy2,
            &mut dummy3,
            &mut dummy4,
            &mut dummy5,
            &mut dummy6,
            &mut dummy7,
            &mut dummy8,
            &mut dummy9,
            &mut dummy10,
            &mut dummy11,
            &mut dummy12,
            &mut dummy13,
            &mut dummy14,
            &mut dummy15,
        ];

        // Replace dummy slices with real slices from outputs where available
        for (idx, item) in outputs.iter_mut().enumerate() {
            if let Some(v) = item {
                slices[idx] = v.as_mut_slice();
            }
        }

        helper_test_ind_name_1(
            &mut i,
            info,
            &options,
            &input_slices,
            &answer_slices,
            &mut slices,
            input_size.try_into().unwrap(),
            answer_size.try_into().unwrap(),
        );

        if info.indicator_ref as usize != 0 {
            helper_test_ind_name_2(
                &mut i,
                info,
                &options,
                &input_slices,
                &answer_slices,
                &mut slices,
                input_size.try_into().unwrap(),
                answer_size.try_into().unwrap(),
            );
        }
    }

    if info.stream_new as usize != 0 {
        // Instead of unsafe casting, we need to get mutable access through the TI_INDICATORS
        let mut ti_indicators = TI_INDICATORS.lock().unwrap();
        let info_mut = &mut ti_indicators[ind_num];
        helper_test_ind_name_3(
            &mut i,
            info_mut,
            &options,
            &inputs,
            &answers,
            &mut outputs,
            input_size.try_into().unwrap(),
            answer_size.try_into().unwrap(),
        );
    }
}

pub fn helper_test_1(count: i32, fp: &mut std::fs::File, line: &mut [u8], line_idx: usize) {
    // Check if character is outside 'a'-'z' range
    if line[line_idx] < b'a' || line[line_idx] > b'z' {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 326);
        return;
    }

    // Convert line to CStr for strtok equivalent
    let line_cstr = unsafe { CStr::from_ptr(line.as_ptr() as *const c_char) };
    let name = line_cstr.to_str().unwrap().split_whitespace().next().unwrap();

    if name == "candle" {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();

        print!("\t{:16}", name);
        test_candles(fp, count);

        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!(
            "pass:{:2}   fail:{:2}   {:4}ms",
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs),
            LFAILS.load(Ordering::SeqCst) - fs,
            elapsed
        );
    } else {
        let ts = LTESTS.load(Ordering::SeqCst);
        let fs = LFAILS.load(Ordering::SeqCst);
        let start = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis();

        print!("\t{:16}", name);
        test_ind_name(fp, Some(name), count);

        let elapsed = SystemTime::now()
            .duration_since(UNIX_EPOCH)
            .unwrap()
            .as_millis() - start;
        println!(
            "pass:{:2}   fail:{:2}   {:4}ms",
            (LTESTS.load(Ordering::SeqCst) - ts) - (LFAILS.load(Ordering::SeqCst) - fs),
            LFAILS.load(Ordering::SeqCst) - fs,
            elapsed
        );
    }
}
pub fn test(fname: Option<&str>, count: i32) {
    // Check if fname is None (equivalent to NULL check in C)
    let fname = match fname {
        Some(name) => name,
        None => {
            // Increment test and fail counters (atomic operations)
            LTESTS.fetch_add(1, Ordering::SeqCst);
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 316);
            return;
        }
    };

    println!("{}:", fname);

    // Open the file (Rust's File is similar to C's FILE*)
    let mut fp = match File::open(fname) {
        Ok(file) => file,
        Err(_) => {
            // Increment test and fail counters (atomic operations)
            LTESTS.fetch_add(1, Ordering::SeqCst);
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 316);
            return;
        }
    };

    // Process each line
    while let Some(line) = next_line(&mut fp) {
        let mut line_bytes = line.as_bytes().to_vec();
        let len = line_bytes.len();
        helper_test_1(count, &mut fp, &mut line_bytes, len);
    }

    // File is automatically closed when fp goes out of scope (RAII)
}
pub fn test_buffer() {
    let mut b = ti_buffer_new(3).expect("Failed to create buffer");
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 5.0;
        b.vals[b.index as usize] = 5.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 360, b.sum, 5.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 5.0;
        b.vals[b.index as usize] = 5.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 10.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 361, b.sum, 10.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 1.0;
        b.vals[b.index as usize] = 1.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 11.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 362, b.sum, 11.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 1.0;
        b.vals[b.index as usize] = 1.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 7.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 363, b.sum, 7.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 3.0;
        b.vals[b.index as usize] = 3.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 364, b.sum, 5.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 1.0;
        b.vals[b.index as usize] = 1.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 365, b.sum, 5.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 2.0;
        b.vals[b.index as usize] = 2.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 6.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 366, b.sum, 6.0);
        }
    }
    
    {
        let b = b.as_mut();
        if b.pushes >= b.size {
            b.sum -= b.vals[b.index as usize];
        }
        b.sum += 3.0;
        b.vals[b.index as usize] = 3.0;
        b.pushes += 1;
        b.index += 1;
        if b.index >= b.size {
            b.index = 0;
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        if (b.sum - 6.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 367, b.sum, 6.0);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        let size = b.size as usize;
        let index = b.index as usize;
        let val = b.vals[((index + size - 1) + 0) % size];
        if (val - 3.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 369, val, 3.0);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        let size = b.size as usize;
        let index = b.index as usize;
        let val = b.vals[((index + size - 1) + size - 1) % size];
        if (val - 2.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 370, val, 2.0);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        let size = b.size as usize;
        let index = b.index as usize;
        let val = b.vals[((index + size - 1) + size - 2) % size];
        if (val - 1.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 371, val, 1.0);
        }
    }
    
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let b = b.as_ref();
        let size = b.size as usize;
        let index = b.index as usize;
        let val = b.vals[((index + size - 1) + size - 3) % size];
        if (val - 3.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 372, val, 3.0);
        }
    }
    
    ti_buffer_free(*b);
}
pub fn test_version() {
    // First test: ti_version
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_version() != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 345);
        }
    }

    // Second test: ti_build
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_build() != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 346);
        }
    }

    // Third test: ti_indicator_count
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_indicator_count() != 104 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 347);
        }
    }

    // Fourth test: tc_version
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_version() != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 349);
        }
    }

    // Fifth test: tc_build
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_build() != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 350);
        }
    }

    // Sixth test: tc_candle_count
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_candle_count() != 26 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 351);
        }
    }

    // Seventh test: hardcoded string comparison
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if "0.9.2" != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/c2rust_final/subjects/tulipindicators/smoke.c", 353);
        }
    }

    // Eighth test: hardcoded number comparison
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if 1645649572 != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} ({} != {})", "/c2rust_final/subjects/tulipindicators/smoke.c", 354, 1645649572, 1645649572);
        }
    }
}
