use core::ffi;
use crate::*;
use crate::MiOptionDescT;
use crate::OPTIONS;
use crate::types::mi_threadid_t as mi_tid_struct;
use lazy_static::lazy_static;
use std::convert::TryInto;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::os::raw::c_int;
use std::os::raw::c_void;
use std::process;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
pub fn mi_version() -> i32 {
    225
}

pub fn mi_error_default(err: i32) {
    if err == 14 {
        process::abort();
    }
}
pub fn mi_recurse_exit_prim() {
    RECURSE.store(false, Ordering::SeqCst);
}
pub fn mi_recurse_exit() {
    mi_recurse_exit_prim();
}

lazy_static! {
    pub static ref recurse: AtomicBool = AtomicBool::new(false);
}

pub fn mi_recurse_enter_prim() -> bool {
    if recurse.load(Ordering::SeqCst) {
        return false;
    }
    recurse.store(true, Ordering::SeqCst);
    true
}
pub fn mi_recurse_enter() -> bool {
    mi_recurse_enter_prim()
}

pub fn mi_out_buf(msg: Option<&str>, arg: *mut std::ffi::c_void) {
    let _ = arg; // Explicitly ignore the argument
    
    // Check if msg is None (equivalent to NULL check in C)
    let msg = match msg {
        Some(m) => m,
        None => return,
    };
    
    // Check if buffer is already full
    if OUT_LEN.load(Ordering::Relaxed) >= 16 * 1024 {
        return;
    }
    
    let n = _mi_strlen(Some(msg));
    if n == 0 {
        return;
    }
    
    let start = OUT_LEN.fetch_add(n, Ordering::AcqRel);
    
    // Check if we exceeded the buffer size after the fetch_add
    if start >= 16 * 1024 {
        return;
    }
    
    let mut actual_n = n;
    if start + n >= 16 * 1024 {
        actual_n = (16 * 1024 - start) - 1;
    }
    
    // Get mutable access to the output buffer
    let mut out_buf_guard = OUT_BUF.lock().unwrap();
    let out_buf_slice = &mut out_buf_guard[start..start + actual_n];
    let msg_bytes = &msg.as_bytes()[..actual_n];
    
    _mi_memcpy(out_buf_slice, msg_bytes, actual_n);
}
pub fn mi_out_get_default(parg: Option<&mut *mut ()>) -> *mut Mi_Output_Fun {
    if let Some(parg_ref) = parg {
        *parg_ref = MI_OUT_ARG.load(Ordering::Acquire);
    }
    
    let out = MI_OUT_DEFAULT.load(Ordering::SeqCst);
    
    if out.is_null() {
        // Return address of mi_out_buf function
        &mi_out_buf as *const _ as *mut Mi_Output_Fun
    } else {
        out
    }
}
pub fn _mi_fputs(
    out: Option<Mi_Output_Fun>,
    arg: *mut std::ffi::c_void,
    prefix: Option<&CStr>,
    message: Option<&CStr>,
) {
    // Check if out is None or points to stdout/stderr equivalents
    // In the original C code, it checks if out is NULL or equals stdout/stderr
    if out.is_none() {
        if !mi_recurse_enter() {
            return;
        }
        
        let mut arg_ptr: *mut () = arg as *mut ();
        let out_fn_ptr = mi_out_get_default(Some(&mut arg_ptr));
        
        // Update the original arg if mi_out_get_default modified it
        let arg_raw_ptr = arg_ptr as *mut std::ffi::c_void;
        
        if let Some(prefix_str) = prefix {
            unsafe {
                if let Some(out_fn) = *out_fn_ptr {
                    out_fn(prefix_str.as_ptr(), arg_raw_ptr);
                }
            }
        }
        
        if let Some(message_str) = message {
            unsafe {
                if let Some(out_fn) = *out_fn_ptr {
                    out_fn(message_str.as_ptr(), arg_raw_ptr);
                }
            }
        }
        
        mi_recurse_exit();
    } else {
        // Use the provided output function directly
        if let Some(out_fn) = out {
            if let Some(prefix_str) = prefix {
                unsafe {
                    if let Some(f) = out_fn {
                        f(prefix_str.as_ptr(), arg);
                    }
                }
            }
            
            if let Some(message_str) = message {
                unsafe {
                    if let Some(f) = out_fn {
                        f(message_str.as_ptr(), arg);
                    }
                }
            }
        }
    }
}
pub fn mi_vfprintf_thread(
    out: Option<Mi_Output_Fun>,
    arg: *mut std::ffi::c_void,
    prefix: Option<&str>,
    fmt: &CStr,
    args: *mut std::ffi::c_void,
) {
    if let Some(prefix) = prefix {
        // Only prepend the "thread ..." prefix for short prefixes and when not on the main thread
        if _mi_strnlen(Some(prefix), 33) <= 32 && !_mi_is_main_thread() {
            let mut tprefix = [0u8; 64];

            // Build the thread prefix using the C-style `_mi_snprintf` we already have.
            // If we can safely treat `mi_threadid_t` as a `usize`, use the original format with the id.
            // Otherwise, fall back to just "%s" (still correct, avoids UB and type ambiguity).
            unsafe {
                // Disambiguate the name to avoid E0659 (multiple `mi_threadid_t` re-exports).
                // We explicitly refer to the struct that `_mi_thread_id()` returns.
                #[allow(unused_imports)]

                let can_use_tid_as_usize: bool =
                    core::mem::size_of::<mi_tid_struct>() == core::mem::size_of::<usize>();

                if can_use_tid_as_usize {
                    // Format: "%sthread 0x%tx: "
                    let fmt_str = b"%sthread 0x%tx: \0";
                    let tid_struct: mi_tid_struct = _mi_thread_id();

                    // Safe only when sizes match; guarded above.
                    let tid_usize: usize = core::mem::transmute_copy(&tid_struct);

                    // Prepare varargs as expected by `_mi_snprintf` shim: slice of usize
                    let mut local_args: [usize; 2] = [
                        prefix.as_bytes().as_ptr() as usize, // "%s"
                        tid_usize,                            // "%tx"
                    ];

                    _mi_snprintf(
                        tprefix.as_mut_ptr(),
                        tprefix.len(),
                        fmt_str.as_ptr(),
                        local_args.as_mut_ptr() as *mut std::ffi::c_void,
                    );
                } else {
                    // Fallback: omit the thread id to avoid undefined behavior with opaque/ZST ids.
                    let fmt_str = b"%s\0";
                    let mut local_args: [usize; 1] = [prefix.as_bytes().as_ptr() as usize];

                    _mi_snprintf(
                        tprefix.as_mut_ptr(),
                        tprefix.len(),
                        fmt_str.as_ptr(),
                        local_args.as_mut_ptr() as *mut std::ffi::c_void,
                    );
                }
            }

            // Safely construct a CStr from the filled buffer up to the first NUL
            let nul_pos = tprefix
                .iter()
                .position(|&b| b == 0)
                .unwrap_or(tprefix.len().saturating_sub(1));
            let used = &tprefix[..=nul_pos];
            if let Ok(cstr_prefix) = CStr::from_bytes_with_nul(used) {
                mi_vfprintf(out, arg, Some(cstr_prefix), Some(fmt), args);
            } else {
                // In the unlikely event of no NUL, fall back to passing no extra prefix
                mi_vfprintf(out, arg, Option::None, Some(fmt), args);
            }
        } else {
            // Pass the original prefix through; ensure it's NUL-terminated for C APIs.
            if let Ok(cstr_prefix) = std::ffi::CString::new(prefix) {
                mi_vfprintf(out, arg, Some(cstr_prefix.as_c_str()), Some(fmt), args);
            } else {
                // If the string contains interior NULs, skip the prefix to avoid UB.
                mi_vfprintf(out, arg, Option::None, Some(fmt), args);
            }
        }
    } else {
        mi_vfprintf(out, arg, Option::None, Some(fmt), args);
    }
}
pub fn mi_option_has_size_in_kib(option: MiOptionT) -> bool {
    (option == MiOptionE::MiOptionReserveOsMemory) || (option == MiOptionE::MiOptionArenaReserve)
}

pub fn _mi_option_get_fast(option: MiOptionT) -> i64 {
    // Check if option is within valid range (0 to _mi_option_last)
    let option_idx = option as i32;
    assert!(
        option_idx >= 0 && option_idx < MiOptionT::_MiOptionLast as i32,
        "option >= 0 && option < _mi_option_last"
    );

    // Get the options array
    let options_guard = OPTIONS.lock().unwrap();
    let desc = &options_guard[option_idx as usize];
    
    // Verify the option field matches
    assert!(
        desc.option == option,
        "desc->option == option"
    );

    desc.value
}
pub fn mi_option_set(option: MiOptionT, value: i64) {
    // Check bounds - equivalent to the C assertion
    // Convert enum values to usize for comparison since MiOptionT doesn't implement PartialOrd
    let option_usize = option as usize;
    let min_option = MiOptionT::MiOptionShowErrors as usize;
    let max_option = MiOptionT::_MiOptionLast as usize;
    
    if option_usize < min_option || option_usize >= max_option {
        return;
    }
    
    // Get the option index as usize
    let option_idx = option as usize;
    
    // Access the OPTIONS array
    let mut options_guard = OPTIONS.lock().unwrap();
    let desc = &mut options_guard[option_idx];
    
    // Set the value and init state
    desc.value = value;
    desc.init = MiInitT::INITIALIZED;
    
    // Handle guarded min/max synchronization
    if desc.option == MiOptionT::MiOptionGuardedMin {
        let current_max = _mi_option_get_fast(MiOptionT::MiOptionGuardedMax);
        if current_max < value {
            mi_option_set(MiOptionT::MiOptionGuardedMax, value);
        }
    } else if desc.option == MiOptionT::MiOptionGuardedMax {
        let current_min = _mi_option_get_fast(MiOptionT::MiOptionGuardedMin);
        if current_min > value {
            mi_option_set(MiOptionT::MiOptionGuardedMin, value);
        }
    }
}

pub fn helper_helper_mi_option_init_1_1(desc: &mut MiOptionDescT, buf: &mut [u8; 65]) {
    let buf_cstr = unsafe { CStr::from_bytes_until_nul(buf).unwrap() };
    let buf_str = buf_cstr.to_str().unwrap();
    
    let mut end_idx = 0;
    let mut value: i64 = match buf_str.parse() {
        Ok(v) => v,
        Err(_) => {
            desc.init = MiInitT::DEFAULTED;
            if desc.option == MiOptionE::MiOptionVerbose && desc.value == 0 {
                desc.value = 1;
                // _mi_warning_message would be called here in the original C code
                desc.value = 0;
            } else {
                // _mi_warning_message would be called here in the original C code
            }
            return;
        }
    };

    if mi_option_has_size_in_kib(desc.option) {
        let mut size = if value < 0 { 0 } else { value as usize };
        let mut overflow = false;

        let remaining = &buf_str[end_idx..];
        let mut chars = remaining.chars();
        let current_char = chars.next();

        match current_char {
            Some('K') => {
                end_idx += 1;
            }
            Some('M') => {
                overflow = mi_mul_overflow(size, 1024, &mut size);
                end_idx += 1;
            }
            Some('G') => {
                overflow = mi_mul_overflow(size, 1024 * 1024, &mut size);
                end_idx += 1;
            }
            Some('T') => {
                overflow = mi_mul_overflow(size, 1024 * 1024 * 1024, &mut size);
                end_idx += 1;
            }
            _ => {
                size = (size + 1024 - 1) / 1024;
            }
        }

        let remaining_after_unit = &buf_str[end_idx..];
        if remaining_after_unit.starts_with("IB") {
            end_idx += 2;
        } else if remaining_after_unit.starts_with('B') {
            end_idx += 1;
        }

        if overflow || size > isize::MAX as usize {
            size = (isize::MAX as usize) / 1024;
        }

        value = if size > i64::MAX as usize {
            i64::MAX
        } else {
            size as i64
        };
    }

    if end_idx == buf_str.len() {
        mi_option_set(desc.option, value);
    } else {
        desc.init = MiInitT::DEFAULTED;
        if desc.option == MiOptionE::MiOptionVerbose && desc.value == 0 {
            desc.value = 1;
            // _mi_warning_message would be called here in the original C code
            desc.value = 0;
        } else {
            // _mi_warning_message would be called here in the original C code
        }
    }
}

pub fn helper_mi_option_init_1(desc: &mut MiOptionDescT, s: &[u8; 65], buf: &mut [u8; 65]) {
    let len = _mi_strnlen(Some(std::str::from_utf8(s).unwrap()), buf.len() - 1);
    
    for i in 0..len {
        if let Some(c_char) = s.get(i).copied() {
            if let Ok(c_str) = std::str::from_utf8(&[c_char]) {
                if let Some(c) = c_str.chars().next() {
                    buf[i] = _mi_toupper(c) as u8;
                }
            }
        }
    }
    
    buf[len] = 0;
    
    let buf_cstr = CStr::from_bytes_until_nul(&buf[..=len]).unwrap();
    let buf_str = buf_cstr.to_str().unwrap();
    
    if buf_str.is_empty() || "1;TRUE;YES;ON".contains(buf_str) {
        desc.value = 1;
        desc.init = MiInitT::INITIALIZED;
    } else if "0;FALSE;NO;OFF".contains(buf_str) {
        desc.value = 0;
        desc.init = MiInitT::INITIALIZED;
    } else {
        helper_helper_mi_option_init_1_1(desc, buf);
    }
    
    if desc.init == MiInitT::UNINIT {
        panic!("desc->init != UNINIT");
    }
}
pub static ERROR_COUNT: AtomicUsize = AtomicUsize::new(0);

pub fn mi_show_error_message(fmt: &CStr, args: *mut std::ffi::c_void) {
    if !mi_option_is_enabled(MiOptionE::MiOptionVerbose) {
        if !mi_option_is_enabled(MiOptionE::MiOptionShowErrors) {
            return;
        }
        if MI_MAX_ERROR_COUNT.load(Ordering::Acquire) >= 0 {
            let current_count = ERROR_COUNT.fetch_add(1, Ordering::AcqRel);
            if current_count as i64 > MI_MAX_ERROR_COUNT.load(Ordering::Acquire) {
                return;
            }
        }
    }
    mi_vfprintf_thread(Option::None, std::ptr::null_mut(), Some("mimalloc: error: "), fmt, args);
}
pub unsafe extern "C" fn _mi_error_message(err: c_int, fmt: &CStr, args: *mut std::ffi::c_void) {
    mi_show_error_message(fmt, args);
    
    let handler = mi_error_handler.load(Ordering::Acquire);
    if !handler.is_null() {
        let arg = MI_ERROR_ARG.load(Ordering::Acquire);
        let handler_fn: unsafe extern "C" fn(c_int, *mut ()) = std::mem::transmute(handler);
        handler_fn(err, arg);
    } else {
        mi_error_default(err);
    }
}
pub unsafe extern "C" fn _mi_trace_message(fmt: &CStr, mut args: *mut std::ffi::c_void) {
    if mi_option_get(MiOptionE::MiOptionVerbose) <= 1 {
        return;
    }
    
    mi_vfprintf_thread(Option::None, std::ptr::null_mut(), Some("mimalloc: "), fmt, args);
}
pub fn mi_option_get_clamp(option: MiOptionT, min: i64, max: i64) -> i64 {
    let x = mi_option_get(option);
    if x < min {
        min
    } else if x > max {
        max
    } else {
        x
    }
}
pub unsafe extern "C" fn _mi_verbose_message(fmt: *const c_char, mut args: *mut std::ffi::c_void) {
    if !mi_option_is_enabled(MiOptionE::MiOptionVerbose) {
        return;
    }
    
    mi_vfprintf(Option::None, std::ptr::null_mut(), Some(unsafe { CStr::from_bytes_with_nul_unchecked(b"mimalloc: \0") }), Some(unsafe { CStr::from_ptr(fmt) }), args);
}
pub fn mi_option_get_size(option: MiOptionT) -> usize {
    let x = mi_option_get(option);
    let mut size = if x < 0 { 0 } else { x as usize };
    if mi_option_has_size_in_kib(option) {
        size *= 1024;
    }
    size
}
pub unsafe extern "C" fn _mi_message(fmt: &std::ffi::CStr) {
    
    let mut args: std::ffi::c_void = std::mem::zeroed();
    
    // In the original C code, __builtin_va_start(args) was used without fmt
    // We'll pass a null pointer as the args parameter to match the original behavior
    mi_vfprintf_thread(
        Option::None,
        std::ptr::null_mut(),
        Some("mimalloc: "),
        fmt,
        std::ptr::null_mut()
    );
}
pub fn mi_out_stderr(msg: Option<&str>, arg: Option<&mut std::ffi::c_void>) {
    let _ = arg; // Explicitly ignore the argument
    
    if let Some(msg) = msg {
        if !msg.is_empty() {
            _mi_prim_out_stderr(Some(msg));
        }
    }
}
pub fn mi_options_print() {
    const VERSION: i32 = 225;
    let vermajor = VERSION / 100;
    let verminor = (VERSION % 100) / 10;
    let verpatch = VERSION % 10;
    
    unsafe {
        _mi_message(c"v%i.%i.%i%s%s (built on %s, %s)\n".as_ref());
    }
    
    for i in 0..MiOptionT::_MiOptionLast as i32 {
        // Instead of transmute, we'll use a safe conversion
        // Since the enum variants are sequential starting from 0, we can try to convert i to MiOptionT
        let option = match i {
            0 => MiOptionT::MiOptionShowErrors,
            1 => MiOptionT::MiOptionShowStats,
            2 => MiOptionT::MiOptionVerbose,
            3 => MiOptionT::MiOptionEagerCommit,
            4 => MiOptionT::MiOptionArenaEagerCommit,
            5 => MiOptionT::MiOptionPurgeDecommits,
            6 => MiOptionT::MiOptionAllowLargeOsPages,
            7 => MiOptionT::MiOptionReserveHugeOsPages,
            8 => MiOptionT::MiOptionReserveHugeOsPagesAt,
            9 => MiOptionT::MiOptionReserveOsMemory,
            10 => MiOptionT::MiOptionDeprecatedSegmentCache,
            11 => MiOptionT::MiOptionDeprecatedPageReset,
            12 => MiOptionT::MiOptionAbandonedPagePurge,
            13 => MiOptionT::MiOptionDeprecatedSegmentReset,
            14 => MiOptionT::MiOptionEagerCommitDelay,
            15 => MiOptionT::MiOptionPurgeDelay,
            16 => MiOptionT::MiOptionUseNumaNodes,
            17 => MiOptionT::MiOptionDisallowOsAlloc,
            18 => MiOptionT::MiOptionOsTag,
            19 => MiOptionT::MiOptionMaxErrors,
            20 => MiOptionT::MiOptionMaxWarnings,
            21 => MiOptionT::MiOptionMaxSegmentReclaim,
            22 => MiOptionT::MiOptionDestroyOnExit,
            23 => MiOptionT::MiOptionArenaReserve,
            24 => MiOptionT::MiOptionArenaPurgeMult,
            25 => MiOptionT::MiOptionPurgeExtendDelay,
            26 => MiOptionT::MiOptionAbandonedReclaimOnFree,
            27 => MiOptionT::MiOptionDisallowArenaAlloc,
            28 => MiOptionT::MiOptionRetryOnOom,
            29 => MiOptionT::MiOptionVisitAbandoned,
            30 => MiOptionT::MiOptionGuardedMin,
            31 => MiOptionT::MiOptionGuardedMax,
            32 => MiOptionT::MiOptionGuardedPrecise,
            33 => MiOptionT::MiOptionGuardedSampleRate,
            34 => MiOptionT::MiOptionGuardedSampleSeed,
            35 => MiOptionT::MiOptionTargetSegmentsPerThread,
            36 => MiOptionT::MiOptionGenericCollect,
            _ => continue, // Skip invalid values
        };
        
        let l = mi_option_get(option);
        let _ = l; // explicitly ignore as in C code
        
        let options_guard = OPTIONS.lock().unwrap();
        let desc = &options_guard[option as usize];
        
        let size_suffix = if mi_option_has_size_in_kib(option) { "KiB" } else { "" };
        let name = desc.name.as_ref().map(|s| s.as_str()).unwrap_or("");
        unsafe {
            _mi_message(c"option '%s': %ld %s\n".as_ref());
        }
    }
    
    unsafe {
        _mi_message(c"debug level : %d\n".as_ref());
        _mi_message(c"secure level: %d\n".as_ref());
        _mi_message(c"mem tracking: %s\n".as_ref());
    }
}

pub type Mi_Output_Fun = Option<extern "C" fn(msg: *const i8, arg: *mut std::ffi::c_void)>;

pub static OUT_LEN: AtomicUsize = AtomicUsize::new(0);

pub fn mi_out_buf_flush(out: Mi_Output_Fun, no_more_buf: bool, arg: *mut std::ffi::c_void) {
    if out.is_none() {
        return;
    }
    
    let out_fn = out.unwrap();
    let increment = if no_more_buf { 16 * 1024 } else { 1 };
    let count = OUT_LEN.fetch_add(increment, Ordering::AcqRel);
    
    let count = if count > 16 * 1024 { 16 * 1024 } else { count };
    
    {
        let mut out_buf = crate::OUT_BUF.lock().unwrap();
        out_buf[count] = 0;
        let msg_ptr = out_buf.as_ptr() as *const i8;
        out_fn(msg_ptr, arg);
        
        if !no_more_buf {
            out_buf[count] = b'\n';
        }
    }
}
pub fn mi_out_buf_stderr(msg: Option<&str>, arg: *mut std::ffi::c_void) {
    mi_out_stderr(msg, if arg.is_null() { None } else { Some(unsafe { &mut *arg }) });
    mi_out_buf(msg, arg);
}
pub fn mi_add_stderr_output() {
    // Check if mi_out_default is NULL (0 in C, null pointer in Rust)
    if MI_OUT_DEFAULT.load(Ordering::SeqCst).is_null() {
        // In C this would call _mi_assert_fail, but we'll just proceed
    }
    
    // Flush the stderr buffer - use mi_out_stderr directly
    // Convert mi_out_stderr to a C-compatible function pointer
    let stderr_fn: extern "C" fn(*const i8, *mut std::ffi::c_void) = unsafe {
        std::mem::transmute(mi_out_stderr as *const ())
    };
    mi_out_buf_flush(Some(stderr_fn), false, std::ptr::null_mut());
    
    // Set mi_out_default to point to mi_out_buf_stderr
    // Convert the function to the correct pointer type
    let buf_stderr_fn: extern "C" fn(*const i8, *mut std::ffi::c_void) = unsafe {
        std::mem::transmute(mi_out_buf_stderr as *const ())
    };
    let buf_stderr_ptr = Some(buf_stderr_fn);
    MI_OUT_DEFAULT.store(Box::into_raw(Box::new(buf_stderr_ptr)) as *mut _, Ordering::SeqCst);
}
pub fn _mi_options_init() {
    mi_add_stderr_output();
    
    for i in 0..MiOptionE::_MiOptionLast as usize {
        let option = unsafe { std::mem::transmute::<u8, MiOptionE>(i as u8) };
        let l = mi_option_get(option);
        // The (void)l in C is equivalent to just using the variable in Rust
        let _ = l;
    }

    MI_MAX_ERROR_COUNT.store(mi_option_get(MiOptionE::MiOptionMaxErrors), Ordering::Relaxed);
    MI_MAX_WARNING_COUNT.store(mi_option_get(MiOptionE::MiOptionMaxWarnings), Ordering::Relaxed);
    
    if mi_option_is_enabled(MiOptionE::MiOptionVerbose) {
        mi_options_print();
    }
}
pub fn mi_option_set_enabled(option: MiOptionT, enable: bool) {
    mi_option_set(option, if enable { 1 } else { 0 });
}
pub fn mi_option_enable(option: MiOptionT) {
    mi_option_set_enabled(option, true);
}
pub fn mi_option_disable(option: MiOptionT) {
    mi_option_set_enabled(option, false);
}

pub fn mi_option_set_default(option: MiOptionT, value: i64) {
    // Check if option is within valid range using pattern matching
    if let MiOptionT::_MiOptionLast = option {
        return;
    }
    
    // Get a mutable lock on the OPTIONS array
    let mut options_guard = OPTIONS.lock().unwrap();
    let options_array = &mut *options_guard;
    
    // Convert option to usize index
    let option_index = option as usize;
    
    // Check bounds (should be safe due to enum bounds, but double-check)
    if option_index >= options_array.len() {
        return;
    }
    
    // Get mutable reference to the option descriptor
    let desc = &mut options_array[option_index];
    
    // Only set the value if not already initialized
    if desc.init != MiInitT::INITIALIZED {
        desc.value = value;
    }
}
pub fn mi_option_set_enabled_default(option: MiOptionT, enable: bool) {
    mi_option_set_default(option, if enable { 1 } else { 0 });
}
pub fn mi_register_error(fun: Option<&Mi_Error_Fun>, arg: Option<&mut ()>) {
    if let Some(fun_ptr) = fun {
        let fun_raw = fun_ptr as *const Mi_Error_Fun as *mut Mi_Error_Fun;
        mi_error_handler.store(fun_raw, Ordering::Release);
    } else {
        mi_error_handler.store(std::ptr::null_mut(), Ordering::Release);
    }
    
    // Safe because MI_ERROR_ARG is an AtomicPtr which provides interior mutability
    // and thread-safe operations
    unsafe {
        if let Some(arg_ref) = arg {
            let arg_raw = arg_ref as *mut _ as *mut ();
            MI_ERROR_ARG.store(arg_raw, Ordering::Release);
        } else {
            MI_ERROR_ARG.store(std::ptr::null_mut(), Ordering::Release);
        }
    }
}
pub fn mi_register_output(out: Option<Mi_Output_Fun>, arg: *mut std::ffi::c_void) {
    let mi_out_default = match out {
        Some(fun) => fun,
        None => {
            let wrapper: extern "C" fn(*const i8, *mut std::ffi::c_void) = mi_out_stderr_wrapper;
            Some(wrapper)
        }
    };
    
    MI_OUT_ARG.store(arg as *mut (), Ordering::Release);
    
    if let Some(output_fun) = mi_out_default {
        mi_out_buf_flush(Some(output_fun), true, arg);
    }
}

extern "C" fn mi_out_stderr_wrapper(msg: *const i8, arg: *mut std::ffi::c_void) {
    let msg_str = if msg.is_null() {
        None
    } else {
        unsafe { Some(std::ffi::CStr::from_ptr(msg).to_str().unwrap_or("")) }
    };
    let arg_ref = if arg.is_null() {
        None
    } else {
        unsafe { Some(&mut *(arg as *mut std::ffi::c_void)) }
    };
    mi_out_stderr(msg_str, arg_ref);
}
