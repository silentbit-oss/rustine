use crate::*;
use lazy_static::lazy_static;
use libc;
use std::f64;
use std::ffi::CStr;
use std::ffi::CString;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::io;
use std::os::fd::AsRawFd;
use std::os::fd::FromRawFd;
use std::os::raw::c_char;
use std::ptr::null_mut;
use std::str::FromStr;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::time::Instant;
static mut buf: [u8; 4096] = [0; 4096]; // Static buffer as in C code

pub fn next_line(fp: &mut File) -> Option<&'static str> {
    let reader = BufReader::new(fp);
    
    for line in reader.lines() {
        let line = line.ok()?;
        unsafe {
            // Copy the line into the static buffer
            let bytes = line.as_bytes();
            if bytes.len() >= 4096 {
                continue; // Skip lines that are too long for our buffer
            }
            buf[..bytes.len()].copy_from_slice(bytes);
            buf[bytes.len()] = b'\0'; // Null-terminate
            
            // Check for comment or empty line
            if buf[0] == b'#' || buf[0] == 10 || buf[0] == 13 {
                continue;
            }
            
            // Convert to str and return
            return std::str::from_utf8(&buf[..bytes.len()]).ok();
        }
    }
    
    None
}

lazy_static! {
    pub static ref LFAILS: AtomicI32 = AtomicI32::new(0);
    pub static ref LTESTS: AtomicI32 = AtomicI32::new(0);
}

pub fn get_array(fp: &mut std::fs::File, s: &mut [f64]) -> Option<i32> {
    // Get the next line from the file
    let line = next_line(fp);
    
    // Check if the line exists and starts with '{'
    if line.is_none() {
        println!("Bad input");
        unsafe {
            crate::globals::LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            if !false {
                crate::globals::LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 85);
            }
        }
        return None;
    }
    let line_str = line.unwrap();
    if line_str.chars().next().unwrap() != '{' {
        println!("Bad input");
        unsafe {
            crate::globals::LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            if !false {
                crate::globals::LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 85);
            }
        }
        return None;
    }

    // Use Rust's split to tokenize the string
    let mut tokens = line_str[1..].split(|c| c == ',' || c == '}' || c == '\r' || c == '\n');
    let mut count = 0;

    for token in tokens {
        let token = token.trim();
        if token.is_empty() {
            continue;
        }
        let value = token.parse::<f64>().unwrap_or(0.0);
        if count < s.len() {
            s[count] = value;
            count += 1;
        } else {
            break;
        }
    }

    Some(count as i32)
}
pub fn compare_arrays(a: &[f64], b: &[f64], size_a: usize, size_b: usize) {
    // Increment tests counter
    LTESTS.fetch_add(1, Ordering::SeqCst);
    
    if size_a != size_b {
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 42, size_a, size_b);
    }
    
    if size_a != size_b {
        println!("Size mismatch.");
        return;
    }
    
    let f = LFAILS.load(Ordering::SeqCst);
    
    for i in 0..size_a {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (a[i] - b[i]).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 50, a[i], b[i]);
        }
    }
    
    if LFAILS.load(Ordering::SeqCst) != f {
        println!("Expected      Got");
        for i in 0..size_a {
            println!("{:8.3} {:8.3}", a[i], b[i]);
        }
    }
}
pub fn test_localbuffer() {
    #[repr(C)]
    struct BufInfo {
        padding: f64,
        zero: [i32; 4],
        offset_a: i32,
        size_a: i32,
        index_a: i32,
        padding_a: i32,
    }

    #[repr(C)]
    struct S {
        buf_info: BufInfo,
        padding: [f64; 5],
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

    // First do-while block
    {
        let buf_info_ptr = &mut stream.buf_info as *mut BufInfo;
        unsafe {
            let offset_a_ptr = &mut (*buf_info_ptr).offset_a as *mut i32;
            let prev_3 = *offset_a_ptr.offset(-3);
            let prev_4 = *offset_a_ptr.offset(-4);
            (*buf_info_ptr).offset_a = prev_3 + prev_4;
            (*buf_info_ptr).size_a = 5;
            (*buf_info_ptr).index_a = -1;
        }
    }

    // Second do-while block (test)
    {
        let buf_info_ptr = &stream.buf_info as *const BufInfo;
        unsafe {
            let buf_info_end_ptr = buf_info_ptr.offset(1) as *const i32;
            let val1 = *buf_info_end_ptr.offset(-3);
            let val2 = *buf_info_end_ptr.offset(-4);
            let sum = val1 + val2;
            LTESTS.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
            if sum != 5 {
                LFAILS.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
                println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 395, sum, 5);
            }
        }
    }

    // Third do-while block (store value)
    {
        let buf_info_ptr = &mut stream.buf_info as *mut BufInfo;
        unsafe {
            let mut idx = (*buf_info_ptr).index_a + 1;
            if idx == (*buf_info_ptr).size_a {
                idx = 0;
            }
            let data_ptr = buf_info_ptr.offset(1) as *mut f64;
            *data_ptr.offset(((*buf_info_ptr).offset_a + idx) as isize) = 100.0;
            (*buf_info_ptr).index_a = idx;
        }
    }

    let get: f64;
    // Fourth do-while block (retrieve value)
    {
        let buf_info_ptr = &stream.buf_info as *const BufInfo;
        unsafe {
            let mut idx = (*buf_info_ptr).index_a + 0;
            while idx >= (*buf_info_ptr).size_a {
                idx -= (*buf_info_ptr).size_a;
            }
            while idx < 0 {
                idx += (*buf_info_ptr).size_a;
            }
            let data_ptr = buf_info_ptr.offset(1) as *const f64;
            get = *data_ptr.offset(((*buf_info_ptr).offset_a + idx) as isize);
        }
    }

    // Fifth do-while block (test retrieved value)
    unsafe {
        LTESTS.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
        if f64::abs(get - 100.0) > 0.001 {
            LFAILS.fetch_add(1, std::sync::atomic::Ordering::SeqCst);
            println!("{}:{} ({:.6} != {:.6})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 400, get, 100.0);
        }
    }
}
pub fn test_ind_name(fp: &mut File, name: Option<&str>, count: i32) {
    // Convert Rust &str to C string for FFI
    let c_name = if let Some(name) = name {
        std::ffi::CString::new(name).unwrap()
    } else {
        return;
    };
    
    let info = unsafe { ti_find_indicator(Some(c_name.to_str().unwrap())) };
    if info.is_none() {
        println!("(WARN) Couldn't find indicator {}", name.unwrap_or(""));
        println!("---------------------------------------------");
        
        // Use the global static buf instead of creating a local one
        let reader = BufReader::new(&mut *fp);
        for line in reader.lines() {
            if let Ok(line) = line {
                if !line.starts_with('{') && !line.starts_with('#') {
                    break;
                }
            }
        }
        return;
    }
    let info = info.unwrap();

    // Calculate index by finding the position in the TI_INDICATORS vector
    let mut ind_num = -1;
    unsafe {
        let indicators_guard = TI_INDICATORS.lock().unwrap();
        for (i, indicator) in indicators_guard.iter().enumerate() {
            if std::ptr::eq(info, indicator) {
                ind_num = i as i32;
                break;
            }
        }
    }
    if ind_num == -1 {
        println!("(WARN) Indicator not found in TI_INDICATORS");
        return;
    }

    if count != 0 {
        unsafe {
            let mut tested_ind_guard = TESTED_IND.lock().unwrap();
            tested_ind_guard[ind_num as usize] = 1;
        }
    }

    let mut options = [0.0; 16];
    let mut o = 0;
    
    // Read and parse options from file
    let mut line = String::new();
    if let Ok(_) = std::io::BufReader::new(&mut *fp).read_line(&mut line) {
        let tokens: Vec<&str> = line.split_whitespace().collect();
        for token in tokens {
            if o < options.len() {
                options[o] = f64::from_str(token).unwrap_or(0.0);
                o += 1;
            }
        }
    }

    // Test 1: Check if number of options matches expected
    unsafe {
        LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
        if o != info.options as usize {
            LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 137, o, info.options);
        }
    }

    let mut inputs: Vec<Vec<f64>> = Vec::new();
    let mut answers: Vec<Vec<f64>> = Vec::new();
    let mut outputs: Vec<Vec<f64>> = Vec::new();
    let mut input_size = 0;

    // Read input arrays
    for _ in 0..info.inputs {
        let mut input_arr = vec![0.0; 1024];
        input_size = get_array(fp, &mut input_arr).unwrap_or(0);
        inputs.push(input_arr);
    }

    let mut answer_size = 0;
    // Read answer arrays and prepare output arrays
    for _ in 0..info.outputs {
        let mut answer_arr = vec![0.0; 1024];
        answer_size = get_array(fp, &mut answer_arr).unwrap_or(0);
        answers.push(answer_arr);
        outputs.push(vec![0.0; 1024]);
    }

    // Convert Vec<Vec<f64>> to slices for FFI
    let input_slices: Vec<&[f64]> = inputs.iter().map(|v| &v[..input_size as usize]).collect();
    
    // Call the indicator function
    let ret = unsafe {
        let mut output_slices: Vec<&mut [f64]> = outputs.iter_mut().map(|v| &mut v[..]).collect();
        (info.indicator)(
            input_size,
            Some(&input_slices),
            Some(&options[..o]),
            Some(&mut output_slices)
        )
    };

    // Test 2: Check if indicator function succeeded
    unsafe {
        LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
        if ret != 0 {
            LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 160);
        }
    }

    let start = unsafe { info.start.as_ref().unwrap()(&options[..o]) };
    let mut output_size = input_size - start;
    if output_size < 0 {
        output_size = 0;
    }

    // Compare results
    for i in 0..info.outputs {
        compare_arrays(
            &answers[i as usize][..answer_size as usize],
            &outputs[i as usize][..output_size as usize],
            answer_size.try_into().unwrap(),
            output_size.try_into().unwrap()
        );
    }

    // Test reference implementation if available
    if !(info.indicator_ref as *const ()).is_null() {
        // Reset outputs
        for output in outputs.iter_mut() {
            output.fill(0.0);
        }

        let ret_ref = unsafe {
            let mut output_slices: Vec<&mut [f64]> = outputs.iter_mut().map(|v| &mut v[..]).collect();
            (info.indicator_ref)(
                input_size,
                Some(&input_slices),
                Some(&options[..o]),
                Some(&mut output_slices)
            )
        };

        // Test 3: Check if reference indicator function succeeded
        unsafe {
            LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
            if ret_ref != 0 {
                LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 176);
            }
        }

        let mut output_size_ref = input_size - start;
        if output_size_ref < 0 {
            output_size_ref = 0;
        }

        // Compare reference results
        for i in 0..info.outputs {
            compare_arrays(
                &answers[i as usize][..answer_size as usize],
                &outputs[i as usize][..output_size_ref as usize],
                answer_size.try_into().unwrap(),
                output_size_ref.try_into().unwrap()
            );
        }
    }

    // Test streaming implementation if available
    if !(info.stream_new as *const ()).is_null() {
        let steps = [1, 2, 3, 4, 5, 7, 13, 100, 1024];
        
        for &step in &steps {
            // Reset outputs
            for output in outputs.iter_mut() {
                output.fill(0.0);
            }

            let mut stream: Option<Box<TiStream>> = None;
            let stream_ret = unsafe {
                (info.stream_new)(Some(&options[..o]), &mut stream)
            };

            // Test 4: Check if stream creation succeeded
            unsafe {
                LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                if stream_ret != 0 {
                    LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 201);
                }
            }

            // Test 5: Check if stream pointer is valid
            unsafe {
                LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                if stream.is_none() {
                    LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 202);
                }
            }

            // Process data in chunks
            let mut bar = 0;
            while bar < input_size {
                let mut ins: Vec<&[f64]> = Vec::new();
                let mut outs: Vec<&mut [f64]> = Vec::new();

                for i in 0..info.inputs {
                    ins.push(&inputs[i as usize][bar as usize..]);
                }

                // Use split_at_mut to create non-overlapping mutable slices
                let mut remaining_outputs = outputs.as_mut_slice();
                for i in 0..info.outputs {
                    let progress = unsafe { ti_stream_get_progress(stream.as_ref().unwrap()) };
                    let safe_progress = if progress < 0 { 0 } else { progress };
                    
                    // Split the remaining outputs to get the current output slice
                    let (current, rest) = remaining_outputs.split_at_mut(1);
                    remaining_outputs = rest;
                    
                    outs.push(&mut current[0][safe_progress as usize..]);
                }

                let mut stride = step;
                if (stride + bar) >= input_size {
                    stride = input_size - bar;
                }

                // Convert Vec to slices for FFI
                let ins_slice: &[&[f64]] = &ins;
                let outs_slice: &mut [&mut [f64]] = &mut outs;

                let stream_run_ret = unsafe {
                    (info.stream_run.as_ref().unwrap())(stream.as_ref().unwrap(), stride, ins_slice, outs_slice)
                };

                // Test 6: Check if stream run succeeded
                unsafe {
                    LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    if stream_run_ret != 0 {
                        LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                        println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 222);
                    }
                }

                bar += stride;
            }

            let final_output_size = input_size - start;
            let final_progress = unsafe { ti_stream_get_progress(stream.as_ref().unwrap()) };

            // Test 7: Check if final progress matches expected output size
            unsafe {
                LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                if final_progress != final_output_size {
                    LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 227, final_progress, final_output_size);
                }
            }

            // Compare streaming results
            for i in 0..info.outputs {
                compare_arrays(
                    &answers[i as usize][..answer_size as usize],
                    &outputs[i as usize][..final_output_size as usize],
                    answer_size.try_into().unwrap(),
                    final_output_size.try_into().unwrap()
                );
            }

            unsafe {
                (info.stream_free.as_ref().unwrap())(*stream.unwrap());
            }
        }
    }
}
pub fn test_candles(fp: &mut std::fs::File, count: i32) {
    
    let mut inputs: [Vec<f64>; 4] = [
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
    ];
    
    let mut input_size = 0;
    for i in 0..4 {
        inputs[i] = vec![0.0; 1024];
        input_size = match get_array(fp, &mut inputs[i]) {
            Some(size) => size,
            None => return,
        };
    }

    let mut config: tc_config::TcConfig = unsafe { std::mem::zeroed() };
    tc_config_set_to_default(&mut config);
    let mut output = tc_result_new();
    if output.is_none() {
        return;
    }
    
    let input_refs: [&[f64]; 4] = [&inputs[0], &inputs[1], &inputs[2], &inputs[3]];
    tc_run((1 << 26) - 1, input_size, &input_refs, &config, &mut *output.as_mut().unwrap());

    // Reset file position to read from beginning of next line
    // Create a new File from the raw file descriptor without consuming the original
    let raw_fd = fp.as_raw_fd();
    let mut reader_file = unsafe { std::fs::File::from_raw_fd(libc::dup(raw_fd)) };
    let mut reader = std::io::BufReader::new(&mut reader_file);
    let mut line = String::new();
    loop {
        line.clear();
        match reader.read_line(&mut line) {
            Ok(0) => break, // EOF
            Ok(_) => {
                if line.is_empty() {
                    continue;
                }
                
                let trimmed_line = line.trim();
                if trimmed_line.is_empty() {
                    continue;
                }
                
                let line_bytes = trimmed_line.as_bytes();
                if (line_bytes[0] != b'!') && ((line_bytes[0] < b'a') || (line_bytes[0] > b'z')) {
                    break;
                }

                let mut tokens = trimmed_line.split_whitespace();
                let mut name_str = match tokens.next() {
                    Some(name) => name,
                    None => continue,
                };

                let mut negate = false;
                if name_str.starts_with('!') {
                    negate = true;
                    name_str = &name_str[1..];
                }

                let info = match tc_find_candle(Some(name_str)) {
                    Some(info) => info,
                    None => {
                        unsafe {
                            crate::globals::LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                            crate::globals::LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                            println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 282);
                        }
                        continue;
                    }
                };

                for num_str in tokens {
                    let pos = match i32::from_str(num_str) {
                        Ok(pos) => pos,
                        Err(_) => continue,
                    };

                    if negate {
                        unsafe {
                            crate::globals::LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                            if (tc_result_at(&*output.as_ref().unwrap(), pos) as u64) & info.pattern != 0 {
                                crate::globals::LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                                println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 290);
                            }
                        }
                    } else {
                        unsafe {
                            crate::globals::LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                            if (tc_result_at(&*output.as_ref().unwrap(), pos) as u64) & info.pattern == 0 {
                                crate::globals::LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                                println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 292);
                            }
                        }
                    }
                }

                unsafe {
                    let tc_candles_ptr = crate::globals::TC_CANDLES.lock().unwrap().as_ptr();
                    let info_ptr = &info as *const TcCandleInfo;
                    let cnd_num = (info_ptr as usize - tc_candles_ptr as usize) / std::mem::size_of::<TcCandleInfo>();
                    
                    if count != 0 {
                        let mut tested_cnd = crate::globals::TESTED_CND.lock().unwrap();
                        tested_cnd[cnd_num] = 1;
                    }
                }
            }
            Err(_) => break,
        }
    }
    
    // Prevent the reader_file from closing the file descriptor since fp still owns it
    std::mem::forget(reader_file);
    tc_result_free(output.map(Box::new));
}
pub fn test(fname: Option<&str>, count: i32) {
    let fname_str = match fname {
        Some(name) => name,
        None => {
            {
                LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                if !false {
                    LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 316);
                }
            }
            return;
        }
    };
    
    println!("{}:", fname_str);
    
    let fp = match File::open(fname_str) {
        Ok(file) => file,
        Err(_) => {
            {
                LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                if !false {
                    LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 316);
                }
            }
            return;
        }
    };
    
    let mut reader = BufReader::new(fp);
    let mut line = String::new();
    
    while let Ok(bytes_read) = reader.read_line(&mut line) {
        if bytes_read == 0 {
            break;
        }
        
        let line_str = line.trim_end();
        if line_str.is_empty() {
            line.clear();
            continue;
        }
        
        if let Some(first_char) = line_str.chars().next() {
            if !first_char.is_ascii_lowercase() {
                {
                    LTESTS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                    if !false {
                        LFAILS.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
                        println!("{}:{} error ", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 326);
                    }
                }
                line.clear();
                continue;
            }
        }
        
        let mut tokens = line_str.split_whitespace();
        let name = tokens.next().unwrap_or("");
        
        if name == "candle" {
            {
                let ts = LTESTS.load(std::sync::atomic::Ordering::Relaxed);
                let fs = LFAILS.load(std::sync::atomic::Ordering::Relaxed);
                let start = Instant::now();
                print!("\t{:<16}", name);
                
                let mut file_clone = reader.get_ref().try_clone().unwrap();
                test_candles(&mut file_clone, count);
                
                let elapsed_ms = start.elapsed().as_millis();
                let tests_diff = LTESTS.load(std::sync::atomic::Ordering::Relaxed) - ts;
                let fails_diff = LFAILS.load(std::sync::atomic::Ordering::Relaxed) - fs;
                println!("pass:{:2}   fail:{:2}   {:4}ms", tests_diff - fails_diff, fails_diff, elapsed_ms);
            }
        } else {
            {
                let ts = LTESTS.load(std::sync::atomic::Ordering::Relaxed);
                let fs = LFAILS.load(std::sync::atomic::Ordering::Relaxed);
                let start = Instant::now();
                print!("\t{:<16}", name);
                
                let mut file_clone = reader.get_ref().try_clone().unwrap();
                test_ind_name(&mut file_clone, Some(name), count);
                
                let elapsed_ms = start.elapsed().as_millis();
                let tests_diff = LTESTS.load(std::sync::atomic::Ordering::Relaxed) - ts;
                let fails_diff = LFAILS.load(std::sync::atomic::Ordering::Relaxed) - fs;
                println!("pass:{:2}   fail:{:2}   {:4}ms", tests_diff - fails_diff, fails_diff, elapsed_ms);
            }
        }
        
        line.clear();
    }
}
pub fn test_buffer() {
    let mut b = ti_buffer_new(3);
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 5.0;
        b.as_mut().unwrap().vals[index] = 5.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 5.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 360, b.as_ref().unwrap().sum, 5.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 5.0;
        b.as_mut().unwrap().vals[index] = 5.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 10.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 361, b.as_ref().unwrap().sum, 10.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 1.0;
        b.as_mut().unwrap().vals[index] = 1.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 11.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 362, b.as_ref().unwrap().sum, 11.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 1.0;
        b.as_mut().unwrap().vals[index] = 1.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 7.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 363, b.as_ref().unwrap().sum, 7.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 3.0;
        b.as_mut().unwrap().vals[index] = 3.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 5.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 364, b.as_ref().unwrap().sum, 5.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 1.0;
        b.as_mut().unwrap().vals[index] = 1.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 5.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 365, b.as_ref().unwrap().sum, 5.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 2.0;
        b.as_mut().unwrap().vals[index] = 2.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 6.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 366, b.as_ref().unwrap().sum, 6.0);
        }
    }
    {
        let index = b.as_ref().unwrap().index as usize;
        if b.as_ref().unwrap().pushes >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().sum -= b.as_ref().unwrap().vals[index];
        }
        b.as_mut().unwrap().sum += 3.0;
        b.as_mut().unwrap().vals[index] = 3.0;
        b.as_mut().unwrap().pushes += 1;
        b.as_mut().unwrap().index = b.as_ref().unwrap().index + 1;
        if b.as_ref().unwrap().index >= b.as_ref().unwrap().size {
            b.as_mut().unwrap().index = 0;
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(b.as_ref().unwrap().sum - 6.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 367, b.as_ref().unwrap().sum, 6.0);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let index = (((b.as_ref().unwrap().index + b.as_ref().unwrap().size) - 1) + 0) % b.as_ref().unwrap().size;
        if f64::abs(b.as_ref().unwrap().vals[index as usize] - 3.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 369, b.as_ref().unwrap().vals[index as usize], 3.0);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let index = (((b.as_ref().unwrap().index + b.as_ref().unwrap().size) - 1) + (-1)) % b.as_ref().unwrap().size;
        if f64::abs(b.as_ref().unwrap().vals[index as usize] - 2.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 370, b.as_ref().unwrap().vals[index as usize], 2.0);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let index = (((b.as_ref().unwrap().index + b.as_ref().unwrap().size) - 1) + (-2)) % b.as_ref().unwrap().size;
        if f64::abs(b.as_ref().unwrap().vals[index as usize] - 1.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 371, b.as_ref().unwrap().vals[index as usize], 1.0);
        }
    }
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let index = (((b.as_ref().unwrap().index + b.as_ref().unwrap().size) - 1) + (-3)) % b.as_ref().unwrap().size;
        if f64::abs(b.as_ref().unwrap().vals[index as usize] - 3.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 372, b.as_ref().unwrap().vals[index as usize], 3.0);
        }
    }
    ti_buffer_free(*b.unwrap());
}
pub fn test_version() {
    unsafe {
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            let version_str = ti_version();
            if version_str != "0.9.2" {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 345);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if ti_build() != 1645649572 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 346);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if ti_indicator_count() != 104 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 347);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            let version_str = tc_version();
            if version_str != "0.9.2" {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 349);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if tc_build() != 1645649572 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 350);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if tc_candle_count() != 26 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 351);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if "0.9.2" != "0.9.2" {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 353);
            }
        }
        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if 1645649572 != 1645649572 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 354, 1645649572, 1645649572);
            }
        }
    }
}
