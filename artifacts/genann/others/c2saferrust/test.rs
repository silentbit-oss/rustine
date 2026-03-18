







use std::ffi::CString;

use std::println;

use std::ptr;

extern "C" {
    
    #[no_mangle]
    fn fclose(_: *mut FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fopen(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char) -> *mut FILE;
    
    
    
    
    #[no_mangle]
    fn printf(_: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #[no_mangle]
    fn fabs(_: std::os::raw::c_double) -> std::os::raw::c_double;
    #[no_mangle]
    fn clock() -> clock_t;
    #[no_mangle]
    fn srand(_: std::os::raw::c_uint);
}
pub use crate::genann::genann_act_sigmoid;
pub use crate::genann::genann_act_sigmoid_cached;
pub use crate::genann::genann_act_threshold;
pub use crate::genann::genann_copy;
pub use crate::genann::genann_free;
pub use crate::genann::genann_init;
pub use crate::genann::genann_randomize;
pub use crate::genann::genann_read;
pub use crate::genann::genann_run;
pub use crate::genann::genann_train;
pub use crate::genann::genann_write;
pub use crate::genann::__sFILEX;
pub type __int64_t = crate::example3::__int64_t;
pub type __darwin_clock_t = std::os::raw::c_ulong;
pub type __darwin_off_t = crate::example3::__darwin_off_t;
pub type fpos_t = crate::example3::fpos_t;
// #[derive(Copy, Clone)]

pub type __sbuf = crate::example4::__sbuf;
// #[derive(Copy, Clone)]

pub type __sFILE = crate::example4::__sFILE;
pub type FILE = crate::example3::FILE;
pub type genann_actfun = crate::example1::genann_actfun;
// #[derive(Copy, Clone)]

pub type genann = crate::example2::genann;
pub type clock_t = __darwin_clock_t;
static mut lfails: std::os::raw::c_int = 0 as std::os::raw::c_int;
static mut ltests: std::os::raw::c_int = 0 as std::os::raw::c_int;
/*
 * GENANN - Minimal C Artificial Neural Network
 *
 * Copyright (c) 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */
#[no_mangle]
pub fn basic() {
    unsafe {
        let mut ann = genann_init(1, 0, 0, 1);
        ltests += 1;
        if (*ann).total_weights != 2 {
            lfails += 1;
            println!("test.c:37 ({} != {})", (*ann).total_weights, 2);
        }
        
        let mut a: f64 = 0.0;
        *(*ann).weight.offset(0) = 0.0;
        *(*ann).weight.offset(1) = 0.0;
        
        ltests += 1;
        if (0.5 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:44 ({} != {})", 0.5, *genann_run(ann, &a));
        }
        
        a = 1.0;
        ltests += 1;
        if (0.5 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:47 ({} != {})", 0.5, *genann_run(ann, &a));
        }
        
        a = 11.0;
        ltests += 1;
        if (0.5 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:50 ({} != {})", 0.5, *genann_run(ann, &a));
        }
        
        a = 1.0;
        *(*ann).weight.offset(0) = 1.0;
        *(*ann).weight.offset(1) = 1.0;
        
        ltests += 1;
        if (0.5 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:55 ({} != {})", 0.5, *genann_run(ann, &a));
        }
        
        a = 10.0;
        *(*ann).weight.offset(0) = 1.0;
        *(*ann).weight.offset(1) = 1.0;
        
        ltests += 1;
        if (1.0 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:60 ({} != {})", 1.0, *genann_run(ann, &a));
        }
        
        a = -10.0;
        ltests += 1;
        if (0.0 - *genann_run(ann, &a)).abs() > 0.001 {
            lfails += 1;
            println!("test.c:63 ({} != {})", 0.0, *genann_run(ann, &a));
        }
        
        genann_free(ann);
    }
}

#[no_mangle]
pub fn xor() {
    unsafe {
        let mut ann = genann_init(2, 1, 2, 1);
        (*ann).activation_hidden = Some(genann_act_threshold);
        (*ann).activation_output = Some(genann_act_threshold);
        
        ltests += 1;
        if (*ann).total_weights != 9 {
            lfails += 1;
            println!("test.c:74 ({:?} != 9)", (*ann).total_weights);
        }
        
        // First hidden.
        *(*ann).weight.offset(0) = 0.5;
        *(*ann).weight.offset(1) = 1.0;
        *(*ann).weight.offset(2) = 1.0;
        
        // Second hidden.
        *(*ann).weight.offset(3) = 1.0;
        *(*ann).weight.offset(4) = 1.0;
        *(*ann).weight.offset(5) = 1.0;
        
        // Output.
        *(*ann).weight.offset(6) = 0.5;
        *(*ann).weight.offset(7) = 1.0;
        *(*ann).weight.offset(8) = -1.0;
        
        let input: [[f64; 2]; 4] = [
            [0.0, 0.0],
            [0.0, 1.0],
            [1.0, 0.0],
            [1.0, 1.0],
        ];
        
        let output: [f64; 4] = [0.0, 1.0, 1.0, 0.0];
        
        for i in 0..4 {
            ltests += 1;
            let result = *genann_run(ann, input[i].as_ptr());
            if (output[i] - result).abs() > 0.001 {
                lfails += 1;
                println!("test.c:{} ({:?} != {:?})", 95 + i, output[i], result);
            }
        }
        
        genann_free(ann);
    }
}

#[no_mangle]
pub fn backprop() {
    unsafe {
        let mut ann = genann_init(1, 0, 0, 1);
        let input: f64 = 0.5;
        let output: f64 = 1.0;
        
        let first_try = *genann_run(ann, &input);
        genann_train(ann, &input, &output, 0.5);
        let second_try = *genann_run(ann, &input);
        
        ltests += 1;
        if !(f64::abs(first_try - output) > f64::abs(second_try - output)) {
            lfails += 1;
            println!("{}:{} error", "test.c", 114);
        }
        genann_free(ann);
    }
}

#[no_mangle]
pub fn train_and() {
    let input: [[f64; 2]; 4] = [
        [0.0, 0.0],
        [0.0, 1.0],
        [1.0, 0.0],
        [1.0, 1.0],
    ];
    let mut output: [f64; 4] = [
        0.0,
        0.0,
        0.0,
        1.0,
    ];
    
    let ann = unsafe { genann_init(2, 0, 0, 1) };
    
    for _ in 0..50 {
        for j in 0..4 {
            unsafe {
                genann_train(ann, input[j].as_ptr(), &mut output[j], 0.8);
            }
        }
    }
    
    unsafe {
        (*ann).activation_output = Some(genann_act_threshold);
    }
    
    unsafe {
        ltests += 1;
    }

    for (i, &expected) in output.iter().enumerate() {
        let result = unsafe { *genann_run(ann, input[i].as_ptr()) };
        
        unsafe {
            ltests += 1;
        }
        
        if (expected - result).abs() > 0.001 {
            unsafe {
                lfails += 1;
            }
            println!("test.c:{} ({} != {})", 135 + i as i32, expected, result);
        }
    }
    
    unsafe {
        genann_free(ann);
    }
}

#[no_mangle]
pub fn train_or() {
    let input: [[f64; 2]; 4] = [
        [0.0, 0.0],
        [0.0, 1.0],
        [1.0, 0.0],
        [1.0, 1.0],
    ];
    let output: [f64; 4] = [
        0.0,
        1.0,
        1.0,
        1.0,
    ];
    
    let mut ann: *mut genann;
    
    unsafe {
        ann = genann_init(2, 0, 0, 1);
        genann_randomize(ann);
        
        for _ in 0..50 {
            for j in 0..4 {
                genann_train(ann, input[j].as_ptr(), &output[j], 0.8);
            }
        }
        
        (*ann).activation_output = Some(genann_act_threshold);
    }
    
    unsafe {
        ltests += 1;
        if (output[0] - *genann_run(ann, input[0].as_ptr())).abs() > 0.001 {
            lfails += 1;
            println!("test.c:160 ({:?} != {:?})", output[0], *genann_run(ann, input[0].as_ptr()));
        }
        
        ltests += 1;
        if (output[1] - *genann_run(ann, input[1].as_ptr())).abs() > 0.001 {
            lfails += 1;
            println!("test.c:161 ({:?} != {:?})", output[1], *genann_run(ann, input[1].as_ptr()));
        }
        
        ltests += 1;
        if (output[2] - *genann_run(ann, input[2].as_ptr())).abs() > 0.001 {
            lfails += 1;
            println!("test.c:162 ({:?} != {:?})", output[2], *genann_run(ann, input[2].as_ptr()));
        }
        
        ltests += 1;
        if (output[3] - *genann_run(ann, input[3].as_ptr())).abs() > 0.001 {
            lfails += 1;
            println!("test.c:163 ({:?} != {:?})", output[3], *genann_run(ann, input[3].as_ptr()));
        }
        
        genann_free(ann);
    }
}

#[no_mangle]
pub fn train_xor() {
    let input: [[f64; 2]; 4] = [
        [0.0, 0.0],
        [0.0, 1.0],
        [1.0, 0.0],
        [1.0, 1.0],
    ];
    let output: [f64; 4] = [
        0.0,
        1.0,
        1.0,
        0.0,
    ];
    
    unsafe {
        let mut ann = genann_init(2, 1, 2, 1);
        
        for _ in 0..500 {
            for j in 0..4 {
                genann_train(ann, input[j].as_ptr(), &output[j], 3.0);
            }
        }
        
        (*ann).activation_output = Some(genann_act_threshold);
        ltests += 1;

        for (i, &expected) in output.iter().enumerate() {
            ltests += 1;
            let result = *genann_run(ann, input[i].as_ptr());
            if (expected - result).abs() > 0.001 {
                lfails += 1;
                println!("test.c:{} ({} != {})", 186 + i, expected, result);
            }
        }
        
        genann_free(ann);
    }
}

#[no_mangle]
pub unsafe extern "C" fn persist() {
    let mut first: *mut genann =
        genann_init(1000 as std::os::raw::c_int, 5 as std::os::raw::c_int, 50 as std::os::raw::c_int,
                    10 as std::os::raw::c_int);
    let mut out: *mut FILE =
        fopen(b"persist.txt\x00" as *const u8 as *const std::os::raw::c_char,
              b"w\x00" as *const u8 as *const std::os::raw::c_char);
    genann_write(&*first, &mut *(out as *mut std::os::raw::c_void as *mut std::fs::File));
    fclose(out);
    let mut in_0: *mut FILE =
        fopen(b"persist.txt\x00" as *const u8 as *const std::os::raw::c_char,
              b"r\x00" as *const u8 as *const std::os::raw::c_char);
    let mut second: *mut genann = genann_read(in_0);
    fclose(out);
    ltests += 1;
    if (*first).inputs != (*second).inputs {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               208 as std::os::raw::c_int, (*first).inputs, (*second).inputs);
    }
    ltests += 1;
    if (*first).hidden_layers != (*second).hidden_layers {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               209 as std::os::raw::c_int, (*first).hidden_layers,
               (*second).hidden_layers);
    }
    ltests += 1;
    if (*first).hidden != (*second).hidden {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               210 as std::os::raw::c_int, (*first).hidden, (*second).hidden);
    }
    ltests += 1;
    if (*first).outputs != (*second).outputs {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               211 as std::os::raw::c_int, (*first).outputs, (*second).outputs);
    }
    ltests += 1;
    if (*first).total_weights != (*second).total_weights {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               212 as std::os::raw::c_int, (*first).total_weights,
               (*second).total_weights);
    }
    let mut i: std::os::raw::c_int = 0;
    i = 0 as std::os::raw::c_int;
    while i < (*first).total_weights {
        ltests += 1;
        if !(*(*first).weight.offset(i as isize) ==
                 *(*second).weight.offset(i as isize)) {
            lfails += 1;
            printf(b"%s:%d error \n\x00" as *const u8 as *const std::os::raw::c_char,
                   b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
                   216 as std::os::raw::c_int);
        }
        i += 1
    }
    genann_free(first);
    genann_free(second);
}
#[no_mangle]
pub fn copy() {
    unsafe {
        let first = genann_init(1000, 5, 50, 10);
        let first_ref = &*first; // Dereference to get a reference
        let second = genann_copy(first_ref);
        
        ltests += 1;
        if first_ref.inputs != (*second).inputs {
            lfails += 1;
            println!("test.c:229 ({} != {})", first_ref.inputs, (*second).inputs);
        }
        
        ltests += 1;
        if first_ref.hidden_layers != (*second).hidden_layers {
            lfails += 1;
            println!("test.c:230 ({} != {})", first_ref.hidden_layers, (*second).hidden_layers);
        }
        
        ltests += 1;
        if first_ref.hidden != (*second).hidden {
            lfails += 1;
            println!("test.c:231 ({} != {})", first_ref.hidden, (*second).hidden);
        }
        
        ltests += 1;
        if first_ref.outputs != (*second).outputs {
            lfails += 1;
            println!("test.c:232 ({} != {})", first_ref.outputs, (*second).outputs);
        }
        
        ltests += 1;
        if first_ref.total_weights != (*second).total_weights {
            lfails += 1;
            println!("test.c:233 ({} != {})", first_ref.total_weights, (*second).total_weights);
        }
        
        for i in 0..first_ref.total_weights {
            ltests += 1;
            if ( *(*first).weight.offset(i as isize) - *(*second).weight.offset(i as isize) ).abs() > 0.001 {
                lfails += 1;
                println!("test.c:237 ({} != {})", *(*first).weight.offset(i as isize), *(*second).weight.offset(i as isize));
            }
        }
        
        genann_free(first);
        genann_free(second);
    }
}

#[no_mangle]
pub fn sigmoid() {
    let mut i: f64 = -20.0;
    let max: f64 = 20.0;
    let d: f64 = 0.0001;
    let mut local_ltests = 0;
    let mut local_lfails = 0;

    while i < max {
        local_ltests += 1;
        unsafe {
            if (genann_act_sigmoid(i) - genann_act_sigmoid_cached(i)).abs() > 0.001 {
                local_lfails += 1;
                println!("test.c:251 ({:?} != {:?})", genann_act_sigmoid(i), genann_act_sigmoid_cached(i));
            }
        }
        i += d;
    }
}

unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: *mut *mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    use std::time::Instant;

println!("GENANN TEST SUITE");
let ts = ltests;
let fs = lfails;
let start = Instant::now();
println!("{:<14}", "basic");
basic();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts - (lfails - fs), lfails - fs,
         start.elapsed().as_millis());

let ts_0 = ltests;
let fs_0 = lfails;
let start_0 = Instant::now();
println!("{:<14}", "xor");
xor();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_0 - (lfails - fs_0), lfails - fs_0,
         start_0.elapsed().as_millis());

let ts_1 = ltests;
let fs_1 = lfails;
let start_1 = Instant::now();
println!("{:<14}", "backprop");
backprop();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_1 - (lfails - fs_1), lfails - fs_1,
         start_1.elapsed().as_millis());

let ts_2 = ltests;
let fs_2 = lfails;
let start_2 = Instant::now();
println!("{:<14}", "train and");
train_and();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_2 - (lfails - fs_2), lfails - fs_2,
         start_2.elapsed().as_millis());

let ts_3 = ltests;
let fs_3 = lfails;
let start_3 = Instant::now();
println!("{:<14}", "train or");
train_or();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_3 - (lfails - fs_3), lfails - fs_3,
         start_3.elapsed().as_millis());

let ts_4 = ltests;
let fs_4 = lfails;
let start_4 = Instant::now();
println!("{:<14}", "train xor");
train_xor();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_4 - (lfails - fs_4), lfails - fs_4,
         start_4.elapsed().as_millis());

let ts_5 = ltests;
let fs_5 = lfails;
let start_5 = Instant::now();
println!("{:<14}", "persist");
persist();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_5 - (lfails - fs_5), lfails - fs_5,
         start_5.elapsed().as_millis());

let ts_6 = ltests;
let fs_6 = lfails;
let start_6 = Instant::now();
println!("{:<14}", "copy");
copy();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_6 - (lfails - fs_6), lfails - fs_6,
         start_6.elapsed().as_millis());

let ts_7 = ltests;
let fs_7 = lfails;
let start_7 = Instant::now();
println!("{:<14}", "sigmoid");
sigmoid();
println!("pass:{:2}   fail:{:2}   {:4}ms", ltests - ts_7 - (lfails - fs_7), lfails - fs_7,
         start_7.elapsed().as_millis());

    if lfails == 0 as std::os::raw::c_int {
        printf(b"ALL TESTS PASSED (%d/%d)\n\x00" as *const u8 as
                   *const std::os::raw::c_char, ltests, ltests);
    } else {
        printf(b"SOME TESTS FAILED (%d/%d)\n\x00" as *const u8 as
                   *const std::os::raw::c_char, ltests - lfails, ltests);
    }
    return (lfails != 0 as std::os::raw::c_int) as std::os::raw::c_int;
}
pub fn main() {
    let args: Vec<String> = ::std::env::args().collect();
    let argc = args.len() as std::os::raw::c_int;
    let argv: Vec<std::ffi::CString> = args.iter()
        .map(|arg| ::std::ffi::CString::new(arg.clone()).expect("Failed to convert argument into CString."))
        .collect();

    let mut argv_ptr: Vec<*mut std::os::raw::c_char> = argv.iter()
        .map(|cstr| cstr.as_ptr() as *mut std::os::raw::c_char)
        .chain(std::iter::once(std::ptr::null_mut()))
        .collect();

    let argv_ptr_mut: *mut *mut std::os::raw::c_char = argv_ptr.as_mut_ptr();
    
    unsafe {
        ::std::process::exit(main_0(argc, argv_ptr_mut) as i32)
    }
}

