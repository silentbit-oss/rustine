
extern "C" {
    
    #[no_mangle]
    fn fclose(_: * mut crate::example3::__sFILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fopen(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> * mut crate::example3::__sFILE;
    
    
    
    
    #[no_mangle]
    fn printf(_: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #[no_mangle]
    fn fabs(_: std::os::raw::c_double) -> std::os::raw::c_double;
    #[no_mangle]
    fn clock() -> std::os::raw::c_ulong;
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
pub type __int64_t = std::os::raw::c_longlong;
pub type __darwin_clock_t = std::os::raw::c_ulong;
pub type __darwin_off_t = std::os::raw::c_longlong;
pub type fpos_t = std::os::raw::c_longlong;
// #[derive(Copy, Clone)]

pub type __sbuf = crate::example3::__sbuf;
// #[derive(Copy, Clone)]

pub type __sFILE = crate::example3::__sFILE;
pub type FILE = crate::example3::__sFILE;
pub type genann_actfun = Option<unsafe extern "C"  fn(_: std::os::raw::c_double,) -> std::os::raw::c_double>;
// #[derive(Copy, Clone)]

pub type genann = crate::example1::genann;
pub type clock_t = std::os::raw::c_ulong;
static mut lfails: std::os::raw::c_int = 0; unsafe fn laertes_init_lfails() {
lfails = 0 as std::os::raw::c_int;}//;
static mut ltests: std::os::raw::c_int = 0; unsafe fn laertes_init_ltests() {
ltests = 0 as std::os::raw::c_int;}//;
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
pub unsafe extern "C" fn basic() {
    let mut ann: * mut crate::example1::genann =
        genann_init(1 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    ltests += 1;
    if (*ann).total_weights != 2 as std::os::raw::c_int {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               37 as std::os::raw::c_int, (*ann).total_weights, 2 as std::os::raw::c_int);
    }
    let mut a: f64 = 0.;
    a = 0 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(0 as std::os::raw::c_int as isize) =
        0 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(1 as std::os::raw::c_int as isize) =
        0 as std::os::raw::c_int as std::os::raw::c_double;
    ltests += 1;
    if fabs(0.5f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               44 as std::os::raw::c_int, 0.5f64, *genann_run(ann, &mut a));
    }
    a = 1 as std::os::raw::c_int as std::os::raw::c_double;
    ltests += 1;
    if fabs(0.5f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               47 as std::os::raw::c_int, 0.5f64, *genann_run(ann, &mut a));
    }
    a = 11 as std::os::raw::c_int as std::os::raw::c_double;
    ltests += 1;
    if fabs(0.5f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               50 as std::os::raw::c_int, 0.5f64, *genann_run(ann, &mut a));
    }
    a = 1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(0 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(1 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    ltests += 1;
    if fabs(0.5f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               55 as std::os::raw::c_int, 0.5f64, *genann_run(ann, &mut a));
    }
    a = 10 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(0 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(1 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    ltests += 1;
    if fabs(1.0f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               60 as std::os::raw::c_int, 1.0f64, *genann_run(ann, &mut a));
    }
    a = -(10 as std::os::raw::c_int) as std::os::raw::c_double;
    ltests += 1;
    if fabs(0.0f64 - *genann_run(ann, &mut a)) > 0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               63 as std::os::raw::c_int, 0.0f64, *genann_run(ann, &mut a));
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn xor() {
    let mut ann: * mut crate::example1::genann =
        genann_init(2 as std::os::raw::c_int, 1 as std::os::raw::c_int, 2 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    (*ann).activation_hidden =
        Some(genann_act_threshold);
    (*ann).activation_output =
        Some(genann_act_threshold);
    ltests += 1;
    if (*ann).total_weights != 9 as std::os::raw::c_int {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               74 as std::os::raw::c_int, (*ann).total_weights, 9 as std::os::raw::c_int);
    }
    /* First hidden. */
    *(*ann).weight.offset(0 as std::os::raw::c_int as isize) = 0.5f64;
    *(*ann).weight.offset(1 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(2 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    /* Second hidden. */
    *(*ann).weight.offset(3 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(4 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(5 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    /* Output. */
    *(*ann).weight.offset(6 as std::os::raw::c_int as isize) = 0.5f64;
    *(*ann).weight.offset(7 as std::os::raw::c_int as isize) =
        1 as std::os::raw::c_int as std::os::raw::c_double;
    *(*ann).weight.offset(8 as std::os::raw::c_int as isize) =
        -(1 as std::os::raw::c_int) as std::os::raw::c_double;
    let mut input: [[f64; 2]; 4] =
        [[0 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [0 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double]];
    let mut output: [f64; 4] =
        [0 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         0 as std::os::raw::c_int as std::os::raw::c_double];
    ltests += 1;
    if fabs(output[0 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[0 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               95 as std::os::raw::c_int, output[0 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[0 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[1 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[1 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               96 as std::os::raw::c_int, output[1 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[1 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[2 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[2 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               97 as std::os::raw::c_int, output[2 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[2 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[3 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[3 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               98 as std::os::raw::c_int, output[3 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[3 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn backprop() {
    let mut ann: * mut crate::example1::genann =
        genann_init(1 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    let mut input: f64 = 0.;
    let mut output: f64 = 0.;
    input = 0.5f64;
    output = 1 as std::os::raw::c_int as std::os::raw::c_double;
    let mut first_try: f64 = *genann_run(ann, &mut input);
    genann_train(ann, &mut input, &mut output, 0.5f64);
    let mut second_try: f64 = *genann_run(ann, &mut input);
    ltests += 1;
    if !(fabs(first_try - output) > fabs(second_try - output)) {
        lfails += 1;
        printf(b"%s:%d error \n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               114 as std::os::raw::c_int);
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn train_and() {
    let mut input: [[f64; 2]; 4] =
        [[0 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [0 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double]];
    let mut output: [f64; 4] =
        [0 as std::os::raw::c_int as std::os::raw::c_double,
         0 as std::os::raw::c_int as std::os::raw::c_double,
         0 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double];
    let mut ann: * mut crate::example1::genann =
        genann_init(2 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    let mut i: i32 = 0;
    let mut j: i32 = 0;
    i = 0 as std::os::raw::c_int;
    while i < 50 as std::os::raw::c_int {
        j = 0 as std::os::raw::c_int;
        while j < 4 as std::os::raw::c_int {
            genann_train(ann, input[j as usize].as_mut_ptr(),
                         output.as_mut_ptr().offset(j as isize), 0.8f64);
            j += 1
        }
        i += 1
    }
    (*ann).activation_output =
        Some(genann_act_threshold);
    ltests += 1;
    if fabs(output[0 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[0 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               135 as std::os::raw::c_int, output[0 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[0 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[1 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[1 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               136 as std::os::raw::c_int, output[1 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[1 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[2 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[2 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               137 as std::os::raw::c_int, output[2 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[2 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[3 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[3 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               138 as std::os::raw::c_int, output[3 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[3 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn train_or() {
    let mut input: [[f64; 2]; 4] =
        [[0 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [0 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double]];
    let mut output: [f64; 4] =
        [0 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double];
    let mut ann: * mut crate::example1::genann =
        genann_init(2 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    genann_randomize(ann);
    let mut i: i32 = 0;
    let mut j: i32 = 0;
    i = 0 as std::os::raw::c_int;
    while i < 50 as std::os::raw::c_int {
        j = 0 as std::os::raw::c_int;
        while j < 4 as std::os::raw::c_int {
            genann_train(ann, input[j as usize].as_mut_ptr(),
                         output.as_mut_ptr().offset(j as isize), 0.8f64);
            j += 1
        }
        i += 1
    }
    (*ann).activation_output =
        Some(genann_act_threshold);
    ltests += 1;
    if fabs(output[0 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[0 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               160 as std::os::raw::c_int, output[0 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[0 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[1 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[1 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               161 as std::os::raw::c_int, output[1 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[1 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[2 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[2 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               162 as std::os::raw::c_int, output[2 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[2 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[3 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[3 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               163 as std::os::raw::c_int, output[3 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[3 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn train_xor() {
    let mut input: [[f64; 2]; 4] =
        [[0 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [0 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          0 as std::os::raw::c_int as std::os::raw::c_double],
         [1 as std::os::raw::c_int as std::os::raw::c_double,
          1 as std::os::raw::c_int as std::os::raw::c_double]];
    let mut output: [f64; 4] =
        [0 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         1 as std::os::raw::c_int as std::os::raw::c_double,
         0 as std::os::raw::c_int as std::os::raw::c_double];
    let mut ann: * mut crate::example1::genann =
        genann_init(2 as std::os::raw::c_int, 1 as std::os::raw::c_int, 2 as std::os::raw::c_int,
                    1 as std::os::raw::c_int);
    let mut i: i32 = 0;
    let mut j: i32 = 0;
    i = 0 as std::os::raw::c_int;
    while i < 500 as std::os::raw::c_int {
        j = 0 as std::os::raw::c_int;
        while j < 4 as std::os::raw::c_int {
            genann_train(ann, input[j as usize].as_mut_ptr(),
                         output.as_mut_ptr().offset(j as isize),
                         3 as std::os::raw::c_int as std::os::raw::c_double);
            j += 1
        }
        i += 1
        /* printf("%1.2f ", xor_score(ann)); */
    }
    (*ann).activation_output =
        Some(genann_act_threshold);
    ltests += 1;
    if fabs(output[0 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[0 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               186 as std::os::raw::c_int, output[0 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[0 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[1 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[1 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               187 as std::os::raw::c_int, output[1 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[1 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[2 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[2 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               188 as std::os::raw::c_int, output[2 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[2 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    ltests += 1;
    if fabs(output[3 as std::os::raw::c_int as usize] -
                *genann_run(ann,
                            input[3 as std::os::raw::c_int as usize].as_mut_ptr())) >
           0.001f64 {
        lfails += 1;
        printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               189 as std::os::raw::c_int, output[3 as std::os::raw::c_int as usize],
               *genann_run(ann,
                           input[3 as std::os::raw::c_int as usize].as_mut_ptr()));
    }
    genann_free(ann);
}
#[no_mangle]
pub unsafe extern "C" fn persist() {
    let mut first: * mut crate::example1::genann =
        genann_init(1000 as std::os::raw::c_int, 5 as std::os::raw::c_int, 50 as std::os::raw::c_int,
                    10 as std::os::raw::c_int);
    let mut out: * mut crate::example3::__sFILE =
        fopen(b"persist.txt\x00" as *const u8 as *const std::os::raw::c_char,
              b"w\x00" as *const u8 as *const std::os::raw::c_char);
    genann_write(first, out);
    fclose(out);
    let mut in_0: * mut crate::example3::__sFILE =
        fopen(b"persist.txt\x00" as *const u8 as *const std::os::raw::c_char,
              b"r\x00" as *const u8 as *const std::os::raw::c_char);
    let mut second: * mut crate::example1::genann = genann_read(in_0);
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
    let mut i: i32 = 0;
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
pub unsafe extern "C" fn copy() {
    let mut first: * mut crate::example1::genann =
        genann_init(1000 as std::os::raw::c_int, 5 as std::os::raw::c_int, 50 as std::os::raw::c_int,
                    10 as std::os::raw::c_int);
    let mut second: * mut crate::example1::genann = genann_copy(first);
    ltests += 1;
    if (*first).inputs != (*second).inputs {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               229 as std::os::raw::c_int, (*first).inputs, (*second).inputs);
    }
    ltests += 1;
    if (*first).hidden_layers != (*second).hidden_layers {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               230 as std::os::raw::c_int, (*first).hidden_layers,
               (*second).hidden_layers);
    }
    ltests += 1;
    if (*first).hidden != (*second).hidden {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               231 as std::os::raw::c_int, (*first).hidden, (*second).hidden);
    }
    ltests += 1;
    if (*first).outputs != (*second).outputs {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               232 as std::os::raw::c_int, (*first).outputs, (*second).outputs);
    }
    ltests += 1;
    if (*first).total_weights != (*second).total_weights {
        lfails += 1;
        printf(b"%s:%d (%d != %d)\n\x00" as *const u8 as *const std::os::raw::c_char,
               b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
               233 as std::os::raw::c_int, (*first).total_weights,
               (*second).total_weights);
    }
    let mut i: i32 = 0;
    i = 0 as std::os::raw::c_int;
    while i < (*first).total_weights {
        ltests += 1;
        if fabs(*(*first).weight.offset(i as isize) -
                    *(*second).weight.offset(i as isize)) > 0.001f64 {
            lfails += 1;
            printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as
                       *const std::os::raw::c_char,
                   b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
                   237 as std::os::raw::c_int, *(*first).weight.offset(i as isize),
                   *(*second).weight.offset(i as isize));
        }
        i += 1
    }
    genann_free(first);
    genann_free(second);
}
#[no_mangle]
pub unsafe extern "C" fn sigmoid() {
    let mut i: f64 = -(20 as std::os::raw::c_int) as std::os::raw::c_double;
    let max: f64 = 20 as std::os::raw::c_int as std::os::raw::c_double;
    let d: f64 = 0.0001f64;
    while i < max {
        ltests += 1;
        if fabs(genann_act_sigmoid(i) - genann_act_sigmoid_cached(i)) >
               0.001f64 {
            lfails += 1;
            printf(b"%s:%d (%f != %f)\n\x00" as *const u8 as
                       *const std::os::raw::c_char,
                   b"test.c\x00" as *const u8 as *const std::os::raw::c_char,
                   251 as std::os::raw::c_int, genann_act_sigmoid(i),
                   genann_act_sigmoid_cached(i));
        }
        i += d
    };
}
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    printf(b"GENANN TEST SUITE\n\x00" as *const u8 as *const std::os::raw::c_char);
    srand(100 as std::os::raw::c_int as std::os::raw::c_uint);
    let ts: i32 = ltests;
    let fs: i32 = lfails;
    let start: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"basic\x00" as *const u8 as *const std::os::raw::c_char);
    basic();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts - (lfails - fs), lfails - fs,
           clock().wrapping_sub(start).wrapping_mul(1000 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong).wrapping_div(1000000
                                                                                        as
                                                                                        std::os::raw::c_int
                                                                                        as
                                                                                        std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_0: i32 = ltests;
    let fs_0: i32 = lfails;
    let start_0: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"xor\x00" as *const u8 as *const std::os::raw::c_char);
    xor();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_0 - (lfails - fs_0),
           lfails - fs_0,
           clock().wrapping_sub(start_0).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_1: i32 = ltests;
    let fs_1: i32 = lfails;
    let start_1: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"backprop\x00" as *const u8 as *const std::os::raw::c_char);
    backprop();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_1 - (lfails - fs_1),
           lfails - fs_1,
           clock().wrapping_sub(start_1).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_2: i32 = ltests;
    let fs_2: i32 = lfails;
    let start_2: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"train and\x00" as *const u8 as *const std::os::raw::c_char);
    train_and();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_2 - (lfails - fs_2),
           lfails - fs_2,
           clock().wrapping_sub(start_2).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_3: i32 = ltests;
    let fs_3: i32 = lfails;
    let start_3: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"train or\x00" as *const u8 as *const std::os::raw::c_char);
    train_or();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_3 - (lfails - fs_3),
           lfails - fs_3,
           clock().wrapping_sub(start_3).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_4: i32 = ltests;
    let fs_4: i32 = lfails;
    let start_4: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"train xor\x00" as *const u8 as *const std::os::raw::c_char);
    train_xor();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_4 - (lfails - fs_4),
           lfails - fs_4,
           clock().wrapping_sub(start_4).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_5: i32 = ltests;
    let fs_5: i32 = lfails;
    let start_5: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"persist\x00" as *const u8 as *const std::os::raw::c_char);
    persist();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_5 - (lfails - fs_5),
           lfails - fs_5,
           clock().wrapping_sub(start_5).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_6: i32 = ltests;
    let fs_6: i32 = lfails;
    let start_6: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"copy\x00" as *const u8 as *const std::os::raw::c_char);
    copy();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_6 - (lfails - fs_6),
           lfails - fs_6,
           clock().wrapping_sub(start_6).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
    let ts_7: i32 = ltests;
    let fs_7: i32 = lfails;
    let start_7: u64 = clock();
    printf(b"\t%-14s\x00" as *const u8 as *const std::os::raw::c_char,
           b"sigmoid\x00" as *const u8 as *const std::os::raw::c_char);
    sigmoid();
    printf(b"pass:%2d   fail:%2d   %4dms\n\x00" as *const u8 as
               *const std::os::raw::c_char, ltests - ts_7 - (lfails - fs_7),
           lfails - fs_7,
           clock().wrapping_sub(start_7).wrapping_mul(1000 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong).wrapping_div(1000000
                                                                                          as
                                                                                          std::os::raw::c_int
                                                                                          as
                                                                                          std::os::raw::c_ulong)
               as std::os::raw::c_int);
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
    let mut args: Vec<*mut std::os::raw::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(::std::ffi::CString::new(arg).expect("Failed to convert argument into CString.").into_raw());
    };
    args.push(::std::ptr::null_mut());
    unsafe {
        ::std::process::exit(main_0((args.len() - 1) as std::os::raw::c_int,
                                    args.as_mut_ptr() as
                                        *mut *mut std::os::raw::c_char) as i32)
    }
}
use crate::laertes_rt::*;
