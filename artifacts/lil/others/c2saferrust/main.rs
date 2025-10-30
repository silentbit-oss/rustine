


use std::ffi::CStr;

use std::convert::TryInto;

extern "C" {
    
    
    
    
    
    #[no_mangle]
    static mut __stdinp: *mut FILE;
    #[no_mangle]
    static mut __stderrp: *mut FILE;
    #[no_mangle]
    fn fgetc(_: *mut FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fgets(_: *mut std::os::raw::c_char, _: std::os::raw::c_int, _: *mut FILE)
     -> *mut std::os::raw::c_char;
    #[no_mangle]
    fn fprintf(_: *mut FILE, _: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn fread(_: *mut std::os::raw::c_void, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
             _: *mut FILE) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn printf(_: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn sprintf(_: *mut std::os::raw::c_char, _: *const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn pclose(_: *mut FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn popen(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char) -> *mut FILE;
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn free(_: *mut std::os::raw::c_void);
    #[no_mangle]
    fn realloc(_: *mut std::os::raw::c_void, _: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn strlen(_: *const std::os::raw::c_char) -> std::os::raw::c_ulong;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
pub use crate::lil::__sFILEX;
pub use crate::lil::lil_alloc_list;
pub use crate::lil::lil_alloc_string;
pub use crate::lil::lil_callback;
pub use crate::lil::lil_error;
pub use crate::lil::lil_free;
pub use crate::lil::lil_free_list;
pub use crate::lil::lil_free_value;
pub use crate::lil::lil_list_append;
pub use crate::lil::lil_list_to_value;
pub use crate::lil::lil_new;
pub use crate::lil::lil_parse;
pub use crate::lil::lil_register;
pub use crate::lil::lil_set_var;
pub use crate::lil::lil_to_integer;
pub use crate::lil::lil_to_string;
pub use crate::lil::_lil_list_t;
pub use crate::lil::_lil_t;
pub use crate::lil::_lil_value_t;
pub use crate::lil::_lil_var_t;
pub use crate::lil::__int64_t;
pub use crate::lil::__darwin_size_t;
pub type __darwin_ssize_t = std::os::raw::c_long;
pub use crate::lil::__darwin_off_t;
pub use crate::lil::size_t;
pub use crate::lil::int64_t;
pub type ssize_t = __darwin_ssize_t;
pub use crate::lil::fpos_t;
// #[derive(Copy, Clone)]

pub use crate::lil::__sbuf;
// #[derive(Copy, Clone)]

pub use crate::lil::__sFILE;
pub use crate::lil::FILE;
pub use crate::lil::lilint_t;
pub use crate::lil::lil_value_t;
pub use crate::lil::lil_var_t;
pub use crate::lil::lil_list_t;
pub use crate::lil::lil_t;
pub use crate::lil::lil_func_proc_t;
pub use crate::lil::lil_callback_proc_t;
/*
 * LIL - Little Interpreted Language
 * Copyright (C) 2010 Kostas Michalopoulos
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * Kostas Michalopoulos <badsector@runtimelegend.com>
 */
static mut running: std::os::raw::c_int = 1 as std::os::raw::c_int;
static mut exit_code: std::os::raw::c_int = 0 as std::os::raw::c_int;
unsafe extern "C" fn do_exit(mut lil: lil_t, mut val: lil_value_t) {
    running = 0 as std::os::raw::c_int;
    exit_code = lil_to_integer(val) as std::os::raw::c_int;
}
fn do_system(argc: usize, argv: *mut *mut std::os::raw::c_char) -> *mut std::os::raw::c_char {
    let mut cmd = String::new();
    let mut i: usize = 0;

    while i < argc {
        let arg = unsafe { std::ffi::CStr::from_ptr(*argv.offset(i as isize)) };
        if i != 0 {
            cmd.push(' ');
        }
        cmd.push_str(arg.to_str().unwrap());
        i += 1;
    }

    let output = std::process::Command::new("sh")
        .arg("-c")
        .arg(cmd)
        .output()
        .expect("Failed to execute command");

    let retval = String::from_utf8(output.stdout).expect("Failed to convert output to String");
    let c_string = std::ffi::CString::new(retval).expect("Failed to create CString");
    c_string.into_raw()
}

unsafe extern "C" fn fnc_writechar(mut lil: lil_t, mut argc: size_t, mut argv: *mut lil_value_t) -> lil_value_t {
    if argc == 0 {
        return 0 as lil_value_t;
    }
    let char_value = lil_to_integer(*argv.offset(0 as std::os::raw::c_int as isize)) as std::os::raw::c_char as std::os::raw::c_int;
    printf(b"%c\x00" as *const u8 as *const std::os::raw::c_char, char_value);
    return 0 as lil_value_t;
}

unsafe extern "C" fn fnc_system(mut lil: lil_t, mut argc: size_t,
                                mut argv: *mut lil_value_t) -> lil_value_t {
    let mut sargv: *mut *const std::os::raw::c_char =
        malloc((::std::mem::size_of::<*mut std::os::raw::c_char>() as
                    std::os::raw::c_ulong).wrapping_mul(argc.wrapping_add(1 as
                                                                      std::os::raw::c_int
                                                                      as
                                                                      std::os::raw::c_ulong)))
            as *mut *const std::os::raw::c_char;
    let mut r: lil_value_t = 0 as lil_value_t;
    let mut rv: *mut std::os::raw::c_char = 0 as *mut std::os::raw::c_char;
    let mut i: size_t = 0;
    if argc == 0 as std::os::raw::c_int as std::os::raw::c_ulong { return 0 as lil_value_t }
    i = 0 as std::os::raw::c_int as size_t;
    while i < argc {
        let ref mut fresh1 = *sargv.offset(i as isize);
        *fresh1 = lil_to_string(*argv.offset(i as isize));
        i = i.wrapping_add(1)
    }
    let ref mut fresh2 = *sargv.offset(argc as isize);
    *fresh2 = 0 as *const std::os::raw::c_char;
    let rv = do_system(argc as usize, sargv as *mut *mut std::os::raw::c_char);
    if !rv.is_null() {
        r = lil_alloc_string(rv);
        free(rv as *mut std::os::raw::c_void);
    }
    free(sargv as *mut std::os::raw::c_void);
    return r;
}
unsafe extern "C" fn fnc_readline(mut lil: lil_t, mut argc: size_t,
                                  mut argv: *mut lil_value_t) -> lil_value_t {
    let mut len: size_t = 0 as std::os::raw::c_int as size_t;
    let mut size: size_t = 64 as std::os::raw::c_int as size_t;
    let mut buffer: *mut std::os::raw::c_char = malloc(size) as *mut std::os::raw::c_char;
    let mut ch: std::os::raw::c_schar = 0;
    let mut retval: lil_value_t = 0 as *mut _lil_value_t;
    loop  {
        ch = fgetc(__stdinp) as std::os::raw::c_schar;
        if ch as std::os::raw::c_int == -(1 as std::os::raw::c_int) { break ; }
        if ch as std::os::raw::c_int == '\r' as i32 { continue ; }
        if ch as std::os::raw::c_int == '\n' as i32 { break ; }
        if len < size {
            size =
                (size as
                     std::os::raw::c_ulong).wrapping_add(64 as std::os::raw::c_int as
                                                     std::os::raw::c_ulong) as size_t
                    as size_t;
            buffer =
                realloc(buffer as *mut std::os::raw::c_void, size) as
                    *mut std::os::raw::c_char
        }
        let fresh3 = len;
        len = len.wrapping_add(1);
        *buffer.offset(fresh3 as isize) = ch as std::os::raw::c_char
    }
    buffer =
        realloc(buffer as *mut std::os::raw::c_void,
                len.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)) as
            *mut std::os::raw::c_char;
    *buffer.offset(len as isize) = 0 as std::os::raw::c_int as std::os::raw::c_char;
    retval = lil_alloc_string(buffer);
    free(buffer as *mut std::os::raw::c_void);
    return retval;
}
unsafe extern "C" fn repl() -> std::os::raw::c_int {
    let mut buffer: [std::os::raw::c_char; 16384] = [0; 16384];
    let mut lil: lil_t = lil_new();
    lil_register(lil, b"writechar\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_writechar as
                          unsafe extern "C" fn(_: lil_t, _: size_t,
                                               _: *mut lil_value_t)
                              -> lil_value_t));
    lil_register(lil, b"system\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_system as
                          unsafe extern "C" fn(_: lil_t, _: size_t,
                                               _: *mut lil_value_t)
                              -> lil_value_t));
    lil_register(lil, b"readline\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_readline as
                          unsafe extern "C" fn(_: lil_t, _: size_t,
                                               _: *mut lil_value_t)
                              -> lil_value_t));
    printf(b"Little Interpreted Language Interactive Shell\n\x00" as *const u8
               as *const std::os::raw::c_char);
    lil_callback(lil, 0 as std::os::raw::c_int,
                 ::std::mem::transmute::<Option<unsafe extern "C" fn(_: lil_t,
                                                                     _:
                                                                         lil_value_t)
                                                    -> ()>,
                                         lil_callback_proc_t>(Some(do_exit as
                                                                       unsafe extern "C" fn(_:
                                                                                                lil_t,
                                                                                            _:
                                                                                                lil_value_t)
                                                                           ->
                                                                               ())));
    while running != 0 {
        let mut result: lil_value_t = 0 as *mut _lil_value_t;
        let mut strres: *const std::os::raw::c_char = 0 as *const std::os::raw::c_char;
        let mut err_msg: *const std::os::raw::c_char = 0 as *const std::os::raw::c_char;
        let mut pos: size_t = 0;
        buffer[0 as std::os::raw::c_int as usize] = 0 as std::os::raw::c_int as std::os::raw::c_char;
        printf(b"# \x00" as *const u8 as *const std::os::raw::c_char);
        if fgets(buffer.as_mut_ptr(), 16384 as std::os::raw::c_int,
                 __stdinp).is_null() {
            break ;
        }
        result =
            lil_parse(lil, buffer.as_mut_ptr(), 0 as std::os::raw::c_int as size_t,
                      0 as std::os::raw::c_int);
        strres = lil_to_string(result);
        if *strres.offset(0 as std::os::raw::c_int as isize) != 0 {
            printf(b"%s\n\x00" as *const u8 as *const std::os::raw::c_char, strres);
        }
        lil_free_value(result);
        if lil_error(lil, &mut err_msg, &mut pos) != 0 {
            printf(b"error at %i: %s\n\x00" as *const u8 as
                       *const std::os::raw::c_char, pos as std::os::raw::c_int, err_msg);
        }
    }
    lil_free(lil);
    return exit_code;
}
unsafe extern "C" fn nonint(mut argc: std::os::raw::c_int,
                            mut argv: *mut *const std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut lil: lil_t = lil_new();
    let mut filename: *const std::os::raw::c_char =
        *argv.offset(1 as std::os::raw::c_int as isize);
    let mut err_msg: *const std::os::raw::c_char = 0 as *const std::os::raw::c_char;
    let mut pos: size_t = 0;
    let mut arglist: *mut _lil_list_t = lil_alloc_list();
    let mut args: lil_value_t = 0 as *mut _lil_value_t;
    let mut result: lil_value_t = 0 as *mut _lil_value_t;
    let mut tmpcode: *mut std::os::raw::c_char = 0 as *mut std::os::raw::c_char;
    let mut i: std::os::raw::c_int = 0;
    lil_register(lil, b"writechar\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_writechar as
                          unsafe extern "C" fn(_: lil_t, _: size_t,
                                               _: *mut lil_value_t)
                              -> lil_value_t));
    lil_register(lil, b"system\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_system as
                          unsafe extern "C" fn(_: lil_t, _: size_t,
                                               _: *mut lil_value_t)
                              -> lil_value_t));
    i = 2 as std::os::raw::c_int;
    while i < argc {
        lil_list_append(arglist, lil_alloc_string(*argv.offset(i as isize)));
        i += 1
    }
    args = lil_list_to_value(arglist, 1 as std::os::raw::c_int);
    lil_free_list(arglist);
    lil_set_var(lil, b"argv\x00" as *const u8 as *const std::os::raw::c_char, args,
                0 as std::os::raw::c_int);
    lil_free_value(args);
    tmpcode =
        malloc(strlen(filename).wrapping_add(256 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong)) as
            *mut std::os::raw::c_char;
    sprintf(tmpcode,
            b"set __lilmain:code__ [read {%s}]\nif [streq $__lilmain:code__ \'\'] {print There is no code in the file or the file does not exist} {eval $__lilmain:code__}\n\x00"
                as *const u8 as *const std::os::raw::c_char, filename);
    result =
        lil_parse(lil, tmpcode, 0 as std::os::raw::c_int as size_t, 1 as std::os::raw::c_int);
    free(tmpcode as *mut std::os::raw::c_void);
    lil_free_value(result);
    if lil_error(lil, &mut err_msg, &mut pos) != 0 {
        fprintf(__stderrp,
                b"lil: error at %i: %s\n\x00" as *const u8 as
                    *const std::os::raw::c_char, pos as std::os::raw::c_int, err_msg);
    }
    lil_free(lil);
    return exit_code;
}
fn main_0(argc: i32, argv: Vec<String>) -> i32 {
    if argc < 2 {
        return unsafe { repl() };
    } else {
        let argv_ptr: Vec<*const std::os::raw::c_char> = argv.iter()
            .map(|s| s.as_ptr() as *const std::os::raw::c_char)
            .collect();
        return unsafe { nonint(argc, argv_ptr.as_ptr() as *mut *const std::os::raw::c_char) };
    }
}

pub fn main() {
    let args: Vec<String> = ::std::env::args().collect();
    let args_c: Vec<std::ffi::CString> = args.iter()
        .map(|arg| ::std::ffi::CString::new(arg.clone()).expect("Failed to convert argument into CString."))
        .collect();
    
    let args_ptr: Vec<*const std::os::raw::c_char> = args_c.iter()
        .map(|cstr| cstr.as_ptr())
        .collect();
    
    // Create a new vector to hold the pointers and add a null pointer at the end
    let mut args_ptr_with_null = args_ptr.clone();
    args_ptr_with_null.push(std::ptr::null());

    // Call the main_0 function with the arguments
    let result = main_0((args.len() - 1) as std::os::raw::c_int, args.clone());
    ::std::process::exit(result as i32);
}

