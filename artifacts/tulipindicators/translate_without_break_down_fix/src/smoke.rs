use crate::*;
use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;
use std::f64;
use std::io;
use std::ffi::CStr;
use std::str::FromStr;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
use std::time::Instant;


static mut buf: [u8; 4096] = [0; 4096]; // Static buffer as in C code

pub fn next_line(fp: &mut File) -> Option<&'static str> {
	println!("\n* next_line");
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

pub fn get_array(fp: &mut File, s: &mut [f64]) -> Option<usize> {
	println!("\n* get_array");
    let line = next_line(fp)?;
    let line_cstr = CStr::from_bytes_with_nul(line.as_bytes()).ok()?;
    
    if line_cstr.to_bytes()[0] != b'{' {
        println!("Bad input");
        LTESTS.fetch_add(1, Ordering::SeqCst);
        LFAILS.fetch_add(1, Ordering::SeqCst);
        println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 85);
        return None;
    }

    let mut tokens = line_cstr.to_str().ok()?[1..].split(|c| c == ',' || c == '}' || c == '\r' || c == '\n');
    let mut inp_idx = 0;

    for token in tokens {
        if token.is_empty() {
            continue;
        }
        if inp_idx >= s.len() {
            break;
        }
        s[inp_idx] = f64::from_str(token).ok()?;
        inp_idx += 1;
    }

    Some(inp_idx)
}
pub fn compare_arrays(a: &[f64], b: &[f64], size_a: usize, size_b: usize) {
	println!("\n* compare_arrays");
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
	println!("\n* test_localbuffer");
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

    // First do-while block
    {
        let buf_info = &mut stream.buf_info;
        let offset_ptr = &buf_info.offset_a as *const i32;
        unsafe {
            buf_info.offset_a = *offset_ptr.offset(-3) + *offset_ptr.offset(-4);
        }
        buf_info.size_a = 5;
        buf_info.index_a = -1;
    }

    // Second do-while block (test)
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let buf_info_ptr = &stream.buf_info as *const BufInfo;
        unsafe {
            let val = (*buf_info_ptr.cast::<i32>().offset(-3)) + 
                      (*buf_info_ptr.cast::<i32>().offset(-4));
            if val != 5 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 395, val, 5);
            }
        }
    }

    // Third do-while block (set value)
    let get = {
        let buf_info = &mut stream.buf_info;
        let mut idx = buf_info.index_a + 1;
        if idx == buf_info.size_a {
            idx = 0;
        }

        let padding_ptr = stream.padding.as_mut_ptr();
        unsafe {
            *padding_ptr.offset(buf_info.offset_a as isize + idx as isize) = 100.0;
        }
        buf_info.index_a = idx;

        // Fourth do-while block (get value)
        let mut idx = buf_info.index_a;
        while idx >= buf_info.size_a {
            idx -= buf_info.size_a;
        }
        while idx < 0 {
            idx += buf_info.size_a;
        }

        unsafe {
            let padding_ptr = stream.padding.as_ptr();
            *padding_ptr.offset(buf_info.offset_a as isize + idx as isize)
        }
    };

    // Fifth do-while block (test get value)
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if f64::abs(get - 100.0) > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 400, get, 100.0);
        }
    }
}
pub fn test_ind_name(fp: &mut std::fs::File, name: Option<&str>, count: i32) {
	println!("\n* test_ind_name");
    let info = match ti_find_indicator(name) {
        Some(info) => info,
        None => {
            println!("(WARN) Couldn't find indicator {:?}", name);
            println!("---------------------------------------------");
            
            let mut reader = std::io::BufReader::new(fp);
            let mut buffer = Vec::new();
            loop {
                buffer.clear();
                let bytes_read = reader.read_until(b'\n', &mut buffer).expect("Failed to read line");
                if bytes_read == 0 || (buffer[0] != b'{' && buffer[0] != b'#') {
                    break;
                }
            }
            return;
        }
    };

    let indicators = TI_INDICATORS.lock().unwrap();
    let ind_num = unsafe { (info as *const _ as usize - &indicators[0] as *const _ as usize) / std::mem::size_of::<TiIndicatorInfo>() };
    if count != 0 {
        TESTED_IND.lock().unwrap()[ind_num] = 1;
    }

    let mut options = [0.0; 16];
    let mut o_idx = 0;
    
    // Read and parse options from the next line
    let mut line = String::new();
    std::io::BufReader::new(&mut *fp).read_line(&mut line).expect("Failed to read options line");
    
    for token in line.split_whitespace() {
        if o_idx >= options.len() {
            break;
        }
        if let Ok(num) = token.parse::<f64>() {
            options[o_idx] = num;
            o_idx += 1;
        }
    }

    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (options.len() - o_idx) as i32 != info.options {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 137, (options.len() - o_idx) as i32, info.options);
        }
    }

    let mut inputs: [Vec<f64>; 16] = Default::default();
    let mut answers: [Vec<f64>; 16] = Default::default();
    let mut outputs: [Vec<f64>; 16] = Default::default();
    let mut input_size = 0;

    for i in 0..info.inputs {
        inputs[i as usize] = vec![0.0; 1024];
        input_size = get_array(&mut *fp, &mut inputs[i as usize]).expect("Failed to read input array");
    }

    let mut answer_size = 0;
    for i in 0..info.outputs {
        answers[i as usize] = vec![0.0; 1024];
        outputs[i as usize] = vec![0.0; 1024];
        answer_size = get_array(&mut *fp, &mut answers[i as usize]).expect("Failed to read answer array");
    }

    {
        let input_refs: Vec<&[f64]> = inputs.iter().take(info.inputs as usize).map(|v| v.as_slice()).collect();
        let mut output_refs: Vec<&mut [f64]> = outputs.iter_mut().take(info.outputs as usize).map(|v| v.as_mut_slice()).collect();
        
        let ret = (info.indicator)(
            input_size.try_into().unwrap(),
            Some(&input_refs),
            Some(&options),
            Some(&mut output_refs),
        );

        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if ret != 0 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 160);
            }
        }

        let mut output_size = input_size as i32 - info.start.as_ref().map_or(0, |f| f(&options));
        if output_size < 0 {
            output_size = 0;
        }
        let output_size = output_size as usize;

        for i in 0..info.outputs {
            compare_arrays(
                &answers[i as usize],
                &outputs[i as usize],
                answer_size as usize,
                output_size,
            );
        }
    }

    if !(info.indicator_ref as *const ()).is_null() {
        for i in 0..info.outputs {
            outputs[i as usize].fill(0.0);
        }

        let input_refs: Vec<&[f64]> = inputs.iter().take(info.inputs as usize).map(|v| v.as_slice()).collect();
        let mut output_refs: Vec<&mut [f64]> = outputs.iter_mut().take(info.outputs as usize).map(|v| v.as_mut_slice()).collect();
        
        let ret = (info.indicator_ref)(
            input_size.try_into().unwrap(),
            Some(&input_refs),
            Some(&options),
            Some(&mut output_refs),
        );

        {
            LTESTS.fetch_add(1, Ordering::SeqCst);
            if ret != 0 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 176);
            }
        }

        let mut output_size = input_size as i32 - info.start.as_ref().map_or(0, |f| f(&options));
        if output_size < 0 {
            output_size = 0;
        }
        let output_size = output_size as usize;

        for i in 0..info.outputs {
            compare_arrays(
                &answers[i as usize],
                &outputs[i as usize],
                answer_size as usize,
                output_size,
            );
        }
    }

    if !(info.stream_new as *const ()).is_null() {
        let steps = [1, 2, 3, 4, 5, 7, 13, 100, 1024];
        let step_count = steps.len();

        for step in steps.iter().take(step_count) {
            for i in 0..info.outputs {
                outputs[i as usize].fill(0.0);
            }

            let mut stream = None;
            let stream_ret = (info.stream_new)(Some(&options), &mut stream);

            {
                LTESTS.fetch_add(1, Ordering::SeqCst);
                if stream_ret != 0 {
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 201);
                }
            }

            {
                LTESTS.fetch_add(1, Ordering::SeqCst);
                if stream.is_none() {
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 202);
                }
            }

            if let Some(stream) = &mut stream {
                // Process each bar individually to avoid borrow conflicts
                for bar in (0..input_size).step_by(*step as usize) {
                    let mut ins: Vec<&[f64]> = Vec::new();
                    let mut outs: Vec<&mut [f64]> = Vec::new();

                    for i in 0..info.inputs {
                        ins.push(&inputs[i as usize][bar as usize..]);
                    }

                    // Split the outputs array to get mutable references to each output
                    let mut remaining_outputs = outputs.as_mut_slice();
                    for i in 0..info.outputs {
                        let progress = ti_stream_get_progress(stream).max(0) as usize;
                        let (current, rest) = remaining_outputs.split_at_mut(1);
                        remaining_outputs = rest;
                        
                        let output_slice = &mut current[0][progress..];
                        outs.push(output_slice);
                    }

                    let stride = if (bar + step) >= input_size {
                        input_size - bar
                    } else {
                        *step
                    };

                    if let Some(stream_run) = info.stream_run.as_ref() {
                        let ret = stream_run(stream, stride.try_into().unwrap(), &ins, &mut outs);

                        {
                            LTESTS.fetch_add(1, Ordering::SeqCst);
                            if ret != 0 {
                                LFAILS.fetch_add(1, Ordering::SeqCst);
                                println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 222);
                            }
                        }
                    }
                }

                let mut output_size = input_size as i32 - info.start.as_ref().map_or(0, |f| f(&options));
                if output_size < 0 {
                    output_size = 0;
                }
                let output_size = output_size as usize;

                {
                    LTESTS.fetch_add(1, Ordering::SeqCst);
                    if ti_stream_get_progress(stream) != output_size as i32 {
                        LFAILS.fetch_add(1, Ordering::SeqCst);
                        println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 227, ti_stream_get_progress(stream), output_size);
                    }
                }

                for i in 0..info.outputs {
                    compare_arrays(
                        &answers[i as usize],
                        &outputs[i as usize],
                        answer_size as usize,
                        output_size,
                    );
                }
            }

            if let Some(stream_free) = info.stream_free.as_ref() {
                if let Some(stream_box) = stream.take() {
                    stream_free(*stream_box);
                }
            }
        }
    }
}
pub fn test_candles(fp: &mut std::fs::File, count: i32) {
	println!("\n* test_candles");
    let mut inputs: [Vec<TC_REAL>; 4] = [
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
        Vec::with_capacity(1024),
    ];
    
    let mut input_size = 0;
    for i in 0..4 {
        input_size = get_array(fp, &mut inputs[i]).expect("Failed to read input array");
    }

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
    let mut output = tc_result_new().expect("Failed to create tc_result");

    let input_refs: Vec<&[TC_REAL]> = inputs.iter().map(|v| v.as_slice()).collect();
    tc_run((1 << 26) - 1, input_size as i32, &input_refs, &config, &mut output);

    let reader = std::io::BufReader::new(fp);
    for line in reader.lines() {
        let line_buf = line.expect("Failed to read line");
        if line_buf.is_empty() {
            break;
        }

        let first_char = line_buf.chars().next().unwrap();
        if first_char != '!' && (first_char < 'a' || first_char > 'z') {
            break;
        }

        let mut parts = line_buf.split_whitespace();
        let name_part = parts.next().unwrap();
        
        let (name, negate) = if name_part.starts_with('!') {
            (&name_part[1..], true)
        } else {
            (name_part, false)
        };

        let info = tc_find_candle(Some(name));
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if info.is_none() {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            eprintln!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 282);
            continue;
        }
        let info = info.unwrap();

        for num in parts {
            let pos = num.parse::<i32>().unwrap();
            let result = tc_result_at(&output, pos);
            LTESTS.fetch_add(1, Ordering::SeqCst);

            if negate {
                if (result as u64 & info.pattern) != 0 {
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    eprintln!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 290);
                }
            } else if (result as u64 & info.pattern) == 0 {
                LFAILS.fetch_add(1, Ordering::SeqCst);
                eprintln!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 292);
            }
        }

        let cnd_num = TC_CANDLES.lock().unwrap().iter().position(|x| x.name.as_deref() == Some(name)).unwrap() as i32;
        if count != 0 {
            TESTED_CND.lock().unwrap()[cnd_num as usize] = 1;
        }
    }

    tc_result_free(Some(Box::new(output)));
}
pub fn test(fname: Option<&str>, count: i32) {
	println!("\n* test");
    println!("{}:", fname.unwrap_or(""));
    
    let mut fp = match File::open(fname.unwrap_or("")) {
        Ok(file) => file,
        Err(_) => {
            {
                LTESTS.fetch_add(1, Ordering::SeqCst);
                if true { // Equivalent to !0 in C
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 316);
                }
            }
            return;
        }
    };

    let mut line;
    loop {
        match next_line(&mut fp) {
            Some(l) => line = l,
            None => break,
        };

        if line.chars().next().map_or(false, |c| c < 'a' || c > 'z') {
            {
                LTESTS.fetch_add(1, Ordering::SeqCst);
                if true { // Equivalent to !0 in C
                    LFAILS.fetch_add(1, Ordering::SeqCst);
                    println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 326);
                }
            }
            continue;
        }

        let name = line.split_whitespace().next().unwrap_or("");
        if name == "candle" {
            let ts = LTESTS.load(Ordering::SeqCst);
            let fs = LFAILS.load(Ordering::SeqCst);
            let start = Instant::now();
            print!("\t{:16}", name);
            test_candles(&mut fp, count);
            let elapsed = start.elapsed().as_millis();
            println!("pass:{:2}   fail:{:2}   {:4}ms", 
                     LTESTS.load(Ordering::SeqCst) - ts - (LFAILS.load(Ordering::SeqCst) - fs),
                     LFAILS.load(Ordering::SeqCst) - fs,
                     elapsed);
        } else {
            let ts = LTESTS.load(Ordering::SeqCst);
            let fs = LFAILS.load(Ordering::SeqCst);
            let start = Instant::now();
            print!("\t{:16}", name);
            test_ind_name(&mut fp, Some(name), count);
            let elapsed = start.elapsed().as_millis();
            println!("pass:{:2}   fail:{:2}   {:4}ms", 
                     LTESTS.load(Ordering::SeqCst) - ts - (LFAILS.load(Ordering::SeqCst) - fs),
                     LFAILS.load(Ordering::SeqCst) - fs,
                     elapsed);
        }
    }
}
pub fn test_buffer() {
	println!("\n* test_buffer");
    let mut b = ti_buffer_new(3).expect("Failed to create buffer");
    
    // First operation block
    {
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
    
    // First test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 360, b.sum, 5.0);
        }
    }
    
    // Second operation block
    {
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
    
    // Second test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 10.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 361, b.sum, 10.0);
        }
    }
    
    // Third operation block
    {
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
    
    // Third test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 11.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 362, b.sum, 11.0);
        }
    }
    
    // Fourth operation block
    {
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
    
    // Fourth test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 7.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 363, b.sum, 7.0);
        }
    }
    
    // Fifth operation block
    {
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
    
    // Fifth test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 364, b.sum, 5.0);
        }
    }
    
    // Sixth operation block
    {
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
    
    // Sixth test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 5.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 365, b.sum, 5.0);
        }
    }
    
    // Seventh operation block
    {
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
    
    // Seventh test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 6.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 366, b.sum, 6.0);
        }
    }
    
    // Eighth operation block
    {
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
    
    // Eighth test block
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if (b.sum - 6.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 367, b.sum, 6.0);
        }
    }
    
    // Additional index tests
    {
        let size = b.size as usize;
        let index = b.index as usize;
        
        // Test 1
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let val = b.vals[(index + size - 1) % size];
        if (val - 3.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 369, val, 3.0);
        }
        
        // Test 2
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let val = b.vals[(index + size - 2) % size];
        if (val - 2.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 370, val, 2.0);
        }
        
        // Test 3
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let val = b.vals[(index + size - 3) % size];
        if (val - 1.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 371, val, 1.0);
        }
        
        // Test 4
        LTESTS.fetch_add(1, Ordering::SeqCst);
        let val = b.vals[(index + size - 4) % size];
        if (val - 3.0).abs() > 0.001 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 372, val, 3.0);
        }
    }
    
    ti_buffer_free(*b);
}
pub fn test_version() {
	println!("\n* test_version");
    // First test: ti_version
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_version() != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 345);
        }
    }

    // Second test: ti_build
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_build() != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 346);
        }
    }

    // Third test: ti_indicator_count
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if ti_indicator_count() != 104 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 347);
        }
    }

    // Fourth test: tc_version
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_version() != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 349);
        }
    }

    // Fifth test: tc_build
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_build() != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 350);
        }
    }

    // Sixth test: tc_candle_count
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if tc_candle_count() != 26 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 351);
        }
    }

    // Seventh test: static string comparison
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if "0.9.2" != "0.9.2" {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} error", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 353);
        }
    }

    // Eighth test: static number comparison
    {
        LTESTS.fetch_add(1, Ordering::SeqCst);
        if 1645649572 != 1645649572 {
            LFAILS.fetch_add(1, Ordering::SeqCst);
            println!("{}:{} ({} != {})", "/workdir/C2RustTranslation-main/subjects/tulipindicators/smoke.c", 354, 1645649572, 1645649572);
        }
    }
}
