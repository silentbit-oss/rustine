
extern "C" {
    pub type __sFILEX;
    
    
    
    
    #[no_mangle]
    static mut __stdinp: * mut crate::lil::__sFILE;
    #[no_mangle]
    static mut __stderrp: * mut crate::lil::__sFILE;
    #[no_mangle]
    fn fgetc(_: * mut crate::lil::__sFILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fgets(_: * mut std::os::raw::c_char, _: std::os::raw::c_int, _: * mut crate::lil::__sFILE)
     -> * mut std::os::raw::c_char;
    #[no_mangle]
    fn fprintf(_: * mut crate::lil::__sFILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn fread(_: * mut core::ffi::c_void, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
             _: * mut crate::lil::__sFILE) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn printf(_: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn sprintf(_: * mut std::os::raw::c_char, _: * const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn pclose(_: * mut crate::lil::__sFILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn popen(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> * mut crate::lil::__sFILE;
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> * mut core::ffi::c_void;
    #[no_mangle]
    fn free(_: * mut core::ffi::c_void);
    #[no_mangle]
    fn realloc(_: * mut core::ffi::c_void, _: std::os::raw::c_ulong) -> * mut core::ffi::c_void;
    #[no_mangle]
    fn memcpy(_: * mut core::ffi::c_void, _: * const core::ffi::c_void, _: std::os::raw::c_ulong)
     -> * mut core::ffi::c_void;
    #[no_mangle]
    fn strlen(_: * const std::os::raw::c_char) -> std::os::raw::c_ulong;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
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
pub type ssize_t = std::os::raw::c_long;
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
static mut running: std::os::raw::c_int = 0; unsafe fn laertes_init_running() {
running = 1 as std::os::raw::c_int;}//;
static mut exit_code: std::os::raw::c_int = 0; unsafe fn laertes_init_exit_code() {
exit_code = 0 as std::os::raw::c_int;}//;
unsafe extern "C" fn do_exit(mut lil: * mut crate::lil::_lil_t, mut val: * mut crate::lil::_lil_value_t) {
    running = 0 as std::os::raw::c_int;
    exit_code = lil_to_integer(val) as std::os::raw::c_int;
}
unsafe extern "C" fn do_system(mut argc: std::os::raw::c_ulong,
                               mut argv: * mut * mut std::os::raw::c_char)
 -> * mut std::os::raw::c_char {
    let mut cmd: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut cmdlen: i32 = 0 as std::os::raw::c_int;
    let mut i: u64 = 0;
    let mut p: * mut crate::lil::__sFILE = 0 as *mut FILE;
    i = 0 as std::os::raw::c_int as size_t;
    while i < argc {
        let mut len: u64 = strlen(*argv.offset(i as isize));
        if i != 0 as std::os::raw::c_int as std::os::raw::c_ulong {
            cmd =
                realloc(cmd as *mut std::os::raw::c_void,
                        (cmdlen + 1 as std::os::raw::c_int) as std::os::raw::c_ulong) as
                    *mut std::os::raw::c_char;
            let mut fresh0 = cmdlen;
            cmdlen = cmdlen + 1;
            *cmd.offset(fresh0 as isize) = ' ' as i32 as std::os::raw::c_char
        }
        cmd =
            realloc(cmd as *mut std::os::raw::c_void,
                    (cmdlen as std::os::raw::c_ulong).wrapping_add(len)) as
                *mut std::os::raw::c_char;
        memcpy(cmd.offset(cmdlen as isize) as *mut std::os::raw::c_void,
               *argv.offset(i as isize) as *const std::os::raw::c_void, len);
        cmdlen =
            (cmdlen as std::os::raw::c_ulong).wrapping_add(len) as std::os::raw::c_int as
                std::os::raw::c_int;
        i = i.wrapping_add(1)
    }
    cmd =
        realloc(cmd as *mut std::os::raw::c_void,
                (cmdlen + 1 as std::os::raw::c_int) as std::os::raw::c_ulong) as
            *mut std::os::raw::c_char;
    *cmd.offset(cmdlen as isize) = 0 as std::os::raw::c_int as std::os::raw::c_char;
    p = popen(cmd, b"r\x00" as *const u8 as *const std::os::raw::c_char);
    free(cmd as *mut std::os::raw::c_void);
    if !p.is_null() {
        let mut retval: * mut i8 = 0 as *mut std::os::raw::c_char;
        let mut size: u64 = 0 as std::os::raw::c_int as size_t;
        let mut buff: [i8; 1024] = [0; 1024];
        let mut bytes: i64 = 0;
        loop  {
            bytes =
                fread(buff.as_mut_ptr() as *mut std::os::raw::c_void,
                      1 as std::os::raw::c_int as std::os::raw::c_ulong,
                      1024 as std::os::raw::c_int as std::os::raw::c_ulong, p) as ssize_t;
            if !(bytes != 0) { break ; }
            retval =
                realloc(retval as *mut std::os::raw::c_void,
                        size.wrapping_add(bytes as std::os::raw::c_ulong)) as
                    *mut std::os::raw::c_char;
            memcpy(retval.offset(size as isize) as *mut std::os::raw::c_void,
                   buff.as_mut_ptr() as *const std::os::raw::c_void,
                   bytes as std::os::raw::c_ulong);
            size =
                (size as std::os::raw::c_ulong).wrapping_add(bytes as std::os::raw::c_ulong)
                    as size_t as size_t
        }
        retval =
            realloc(retval as *mut std::os::raw::c_void,
                    size.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)) as
                *mut std::os::raw::c_char;
        *retval.offset(size as isize) = 0 as std::os::raw::c_int as std::os::raw::c_char;
        pclose(p);
        return retval
    } else { return 0 as *mut std::os::raw::c_char };
}
unsafe extern "C" fn fnc_writechar(mut lil: * mut crate::lil::_lil_t, mut argc: std::os::raw::c_ulong,
                                   mut argv: * mut * mut crate::lil::_lil_value_t)
 -> * mut crate::lil::_lil_value_t {
    if argc == 0 { return 0 as lil_value_t }
    printf(b"%c\x00" as *const u8 as *const std::os::raw::c_char,
           lil_to_integer(*argv.offset(0 as std::os::raw::c_int as isize)) as
               std::os::raw::c_char as std::os::raw::c_int);
    return 0 as lil_value_t;
}
unsafe extern "C" fn fnc_system(mut lil: * mut crate::lil::_lil_t, mut argc: std::os::raw::c_ulong,
                                mut argv: * mut * mut crate::lil::_lil_value_t) -> * mut crate::lil::_lil_value_t {
    let mut sargv: * mut * const i8 =
        malloc((::std::mem::size_of::<*mut std::os::raw::c_char>() as
                    std::os::raw::c_ulong).wrapping_mul(argc.wrapping_add(1 as
                                                                      std::os::raw::c_int
                                                                      as
                                                                      std::os::raw::c_ulong)))
            as *mut *const std::os::raw::c_char;
    let mut r: * mut crate::lil::_lil_value_t = 0 as lil_value_t;
    let mut rv: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut i: u64 = 0;
    if argc == 0 as std::os::raw::c_int as std::os::raw::c_ulong { return 0 as lil_value_t }
    i = 0 as std::os::raw::c_int as size_t;
    while i < argc {
        let ref mut fresh1 = *sargv.offset(i as isize);
        *fresh1 = lil_to_string(*argv.offset(i as isize));
        i = i.wrapping_add(1)
    }
    let ref mut fresh2 = *sargv.offset(argc as isize);
    *fresh2 = 0 as *const std::os::raw::c_char;
    rv = do_system(argc, sargv as *mut *mut std::os::raw::c_char);
    if !rv.is_null() {
        r = lil_alloc_string(rv);
        free(rv as *mut std::os::raw::c_void);
    }
    free(sargv as *mut std::os::raw::c_void);
    return r;
}
unsafe extern "C" fn fnc_readline(mut lil: * mut crate::lil::_lil_t, mut argc: std::os::raw::c_ulong,
                                  mut argv: * mut * mut crate::lil::_lil_value_t) -> * mut crate::lil::_lil_value_t {
    let mut len: u64 = 0 as std::os::raw::c_int as size_t;
    let mut size: u64 = 64 as std::os::raw::c_int as size_t;
    let mut buffer: * mut i8 = malloc(size) as *mut std::os::raw::c_char;
    let mut ch: i8 = 0;
    let mut retval: * mut crate::lil::_lil_value_t = 0 as *mut _lil_value_t;
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
        let mut fresh3 = len;
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
    let mut buffer: [i8; 16384] = [0; 16384];
    let mut lil: * mut crate::lil::_lil_t = lil_new();
    lil_register(lil, b"writechar\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_writechar));
    lil_register(lil, b"system\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_system));
    lil_register(lil, b"readline\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_readline));
    printf(b"Little Interpreted Language Interactive Shell\n\x00" as *const u8
               as *const std::os::raw::c_char);
    lil_callback(lil, 0 as std::os::raw::c_int,
                 core::intrinsics::transmute::<Option<unsafe extern "C"  fn(_: * mut crate::lil::_lil_t,_: * mut crate::lil::_lil_value_t,) -> ()>, Option<unsafe extern "C"  fn() -> ()>>(Some(do_exit)));
    while running != 0 {
        let mut result: * mut crate::lil::_lil_value_t = 0 as *mut _lil_value_t;
        let mut strres: * const i8 = 0 as *const std::os::raw::c_char;
        let mut err_msg: * const i8 = 0 as *const std::os::raw::c_char;
        let mut pos: u64 = 0;
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
        if lil_error(lil, Some(&mut err_msg), Some(&mut pos)) != 0 {
            printf(b"error at %i: %s\n\x00" as *const u8 as
                       *const std::os::raw::c_char, pos as std::os::raw::c_int, err_msg);
        }
    }
    lil_free(lil);
    return exit_code;
}
unsafe extern "C" fn nonint(mut argc: std::os::raw::c_int,
                            mut argv: * mut * const std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut lil: * mut crate::lil::_lil_t = lil_new();
    let mut filename: * const i8 =
        *argv.offset(1 as std::os::raw::c_int as isize);
    let mut err_msg: * const i8 = 0 as *const std::os::raw::c_char;
    let mut pos: u64 = 0;
    let mut arglist: * mut crate::lil::_lil_list_t = lil_alloc_list();
    let mut args: * mut crate::lil::_lil_value_t = 0 as *mut _lil_value_t;
    let mut result: * mut crate::lil::_lil_value_t = 0 as *mut _lil_value_t;
    let mut tmpcode: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut i: i32 = 0;
    lil_register(lil, b"writechar\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_writechar));
    lil_register(lil, b"system\x00" as *const u8 as *const std::os::raw::c_char,
                 Some(fnc_system));
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
    if lil_error(lil, Some(&mut err_msg), Some(&mut pos)) != 0 {
        fprintf(__stderrp,
                b"lil: error at %i: %s\n\x00" as *const u8 as
                    *const std::os::raw::c_char, pos as std::os::raw::c_int, err_msg);
    }
    lil_free(lil);
    return exit_code;
}
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * const std::os::raw::c_char)
 -> std::os::raw::c_int {
    if argc < 2 as std::os::raw::c_int {
        return repl()
    } else { return nonint(argc, argv) };
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
                                        *mut *const std::os::raw::c_char) as i32)
    }
}
use crate::laertes_rt::*;
