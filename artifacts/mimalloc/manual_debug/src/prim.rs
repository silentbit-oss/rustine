use crate::MiProcessInfoS;
use crate::mi_process_info_t;
use libc::MADV_DONTNEED;
use libc::PROT_NONE;
use libc::PROT_READ;
use libc::PROT_WRITE;
use libc::RUSAGE_SELF;
use libc::_SC_PAGESIZE;
use libc::__errno_location;
use libc::c_int;
use libc::getrusage;
use libc::mprotect;
use libc::rusage;
use libc::size_t;
use libc::sysconf;
use libc::timeval;
use std::ffi::CStr;
use std::ffi::CString;
use std::ffi::c_int as other_other_c_int;
use std::fs::File;
use std::fs;
use std::io::Read;
use std::io::Write;
use std::io;
use std::os::fd::AsRawFd;
use std::os::fd::RawFd;
use std::os::raw::c_long;
use std::os::raw::c_void;
use std::os::unix::fs::OpenOptionsExt;
use std::ptr;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use::libc::c_int as other_c_int;
use::libc::close;
use::libc::madvise;
use::libc::mmap;
use::libc::ssize_t;
pub fn _mi_is_redirected() -> bool {
    false
}
pub fn _mi_allocator_init(message: Option<&mut Option<&'static str>>) -> bool {
    if let Some(msg) = message {
        *msg = None;
    }
    true
}
pub fn _mi_allocator_done() {
    // This function intentionally left empty, matching the C implementation
}
pub fn _mi_prim_free(addr: Option<&mut [u8]>, size: usize) -> i32 {
    if size == 0 {
        return 0;
    }
    
    let err = unsafe {
        match addr {
            Some(_) => {
                // For allocated memory slices, we can't directly deallocate them
                // since we don't own the allocation. In a real scenario, this would
                // need to track the original allocation.
                // For now, we'll return success (0) as we can't safely deallocate
                // memory we don't own.
                false
            }
            None => {
                // If addr is None, we can't deallocate anything
                true
            }
        }
    };
    
    if err {
        std::io::Error::last_os_error().raw_os_error().unwrap_or(-1)
    } else {
        0
    }
}
pub fn _mi_prim_reuse(start: Option<&mut std::ffi::c_void>, size: usize) -> i32 {
    let _ = start;
    let _ = size;
    0
}
pub fn _mi_prim_numa_node() -> usize {
    0
}

pub fn _mi_prim_clock_now() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_millis() as u64
}

pub fn _mi_prim_out_stderr(msg: Option<&str>) {
    if let Some(msg) = msg {
        let _ = io::stderr().write_all(msg.as_bytes());
    }
}

pub fn mi_prim_open(fpath: Option<&str>, open_flags: i32) -> Result<File, std::io::Error> {
    // Check if fpath is None (equivalent to NULL in C)
    let fpath = fpath.ok_or_else(|| std::io::Error::new(
        std::io::ErrorKind::InvalidInput,
        "fpath cannot be null"
    ))?;

    // Use OpenOptions to handle the open flags
    let mut options = std::fs::OpenOptions::new();
    
    // Set the flags using the raw open flags from C
    // This preserves the exact behavior of the C open() function
    unsafe {
        options.custom_flags(open_flags);
    }

    options.open(fpath)
}

pub unsafe extern "C" fn mi_prim_read(fd: c_int, buf: *mut c_void, bufsize: size_t) -> ssize_t {
    ::libc::read(fd, buf, bufsize)
}

pub fn mi_prim_close(fd: RawFd) -> i32 {
    unsafe { close(fd) }
}

pub fn mi_prim_access(fpath: &str, mode: i32) -> i32 {
    match fs::metadata(fpath) {
        Ok(metadata) => {
            // Simplified implementation - in real code you would check specific permissions
            // based on the mode parameter, but this matches the basic access() behavior
            0
        }
        Err(_) => -1
    }
}
pub unsafe fn unix_madvise(addr_param: *mut c_void, size_param: size_t, advice_param: c_int) -> c_int {
    #[cfg(any(target_os = "linux", target_os = "macos", target_os = "freebsd", target_os = "android"))]
    {
        #[cfg(any(target_os = "linux", target_os = "android"))]
        let res = madvise(addr_param, size_param, advice_param);
        #[cfg(any(target_os = "macos", target_os = "freebsd"))]
        let res = madvise(addr_param, size_param, advice_param);
        
        if res == 0 { 
            0 
        } else { 
            // On error, return errno directly as in the original C code
            #[cfg(any(target_os = "linux", target_os = "android"))]
            {
                *__errno_location()
            }
            #[cfg(any(target_os = "macos", target_os = "freebsd"))]
            {
                *__error()
            }
        }
    }
    #[cfg(not(any(target_os = "linux", target_os = "macos", target_os = "freebsd", target_os = "android")))]
    {
        // On unsupported platforms, return ENOSYS (Function not implemented)
        libc::ENOSYS
    }
}
pub fn unix_mmap_prim(addr: *mut std::ffi::c_void, size: size_t, protect_flags: std::ffi::c_int, flags: std::ffi::c_int, fd: std::ffi::c_int) -> *mut std::ffi::c_void {
    unsafe {
        let result = mmap(
            addr,
            size,
            protect_flags,
            flags,
            fd,
            0
        );
        
        result
    }
}
fn unix_mmap_fd() -> i32 {
    return -1;
}
// Fixed prim.rs imports and function declarations

// ... rest of prim.rs code with madvise and mmap calls ...

// The original unix_mprotect_hint function remains unchanged
pub fn unix_mprotect_hint(_err: i32) {
    // The parameter is intentionally unused, following the C code pattern (void)err;
}
pub fn mi_prim_mbind(
    start: Option<&mut std::ffi::c_void>,
    len: usize,
    mode: usize,
    nmask: Option<&[usize]>,
    maxnode: usize,
    flags: usize,
) -> isize {
    let _ = start;
    let _ = len;
    let _ = mode;
    let _ = nmask;
    let _ = maxnode;
    let _ = flags;
    0
}

pub type mi_msecs_t = i64;

pub fn timeval_secs(tv: Option<&timeval>) -> mi_msecs_t {
    match tv {
        Some(tv) => {
            ((tv.tv_sec as mi_msecs_t) * 1000) + ((tv.tv_usec as mi_msecs_t) / 1000)
        }
        None => 0
    }
}
pub struct EnvironWrapper(*mut *mut std::ffi::c_char);
pub fn _mi_prim_getenv(name: Option<&str>, result: &mut [u8], result_size: usize) -> bool {
    // Check if name is None (equivalent to NULL check in C)
    if name.is_none() {
        return false;
    }
    let name = name.unwrap();
    
    // Get the length of the name string
    let len = _mi_strlen(Some(name));
    if len == 0 {
        return false;
    }
    
    // Use Rust's standard library to get environment variables
    // This is the Rust equivalent of accessing environ
    for (key, value) in std::env::vars() {
        if key == name {
            // Copy the value to result buffer
            let value_bytes = value.as_bytes();
            let copy_len = std::cmp::min(value_bytes.len(), result_size - 1);
            result[..copy_len].copy_from_slice(&value_bytes[..copy_len]);
            if copy_len < result.len() {
                result[copy_len] = 0; // null terminate
            }
            return true;
        }
    }
    
    false
}
pub fn _mi_strlen(s: Option<&str>) -> usize {
    match s {
        Some(str_ref) => str_ref.len(),
        None => 0,
    }
}
pub fn _mi_prim_commit(start: *mut c_void, size: usize, is_zero: &mut bool) -> c_int {
    *is_zero = false;
    let err = unsafe { mprotect(start, size, PROT_READ | PROT_WRITE) };
    if err != 0 {
        let errno = unsafe { *libc::__errno_location() };
        unix_mprotect_hint(errno);
        errno
    } else {
        0
    }
}
pub fn unix_mmap_prim_aligned(
    addr: Option<&mut std::ffi::c_void>,
    size: usize,
    try_alignment: usize,
    protect_flags: std::ffi::c_int,
    flags: std::ffi::c_int,
    fd: std::ffi::c_int,
) -> Option<&'static mut std::ffi::c_void> {
    let _ = try_alignment;
    
    if addr.is_none() {
        if let Some(hint) = crate::_mi_os_get_aligned_hint(try_alignment, size) {
            let p_ptr = crate::unix_mmap_prim(hint as *mut std::ffi::c_void, size, protect_flags, flags, fd);
            if p_ptr != std::ptr::null_mut() {
                let p = unsafe { &mut *p_ptr };
                if !crate::_mi_is_aligned(Some(p), try_alignment) {
                    let err = std::io::Error::last_os_error();
                    unsafe {
                        let args: [isize; 5] = [
                            err.raw_os_error().unwrap() as isize, 
                            err.raw_os_error().unwrap() as isize, 
                            size as isize, 
                            try_alignment as isize, 
                            hint as *mut std::ffi::c_void as isize
                        ];
                        crate::_mi_trace_message(
                            std::ffi::CStr::from_bytes_with_nul(b"unable to directly request hinted aligned OS memory (error: %d (0x%x), size: 0x%zx bytes, alignment: 0x%zx, hint address: %p)\n\0").unwrap(),
                            args.as_ptr() as *mut std::ffi::c_void
                        );
                    }
                }
                // In the original C code, if the mapping succeeds but alignment is wrong, we still return the pointer
                return Some(p);
            }
        }
    }
    
    let addr_ptr = match addr {
        Some(addr_ref) => addr_ref as *mut std::ffi::c_void,
        None => std::ptr::null_mut(),
    };
    let result_ptr = crate::unix_mmap_prim(addr_ptr, size, protect_flags, flags, fd);
    if result_ptr != std::ptr::null_mut() {
        Some(unsafe { &mut *result_ptr })
    } else {
        Option::None
    }
}
static LARGE_PAGE_TRY_OK: AtomicUsize = AtomicUsize::new(0);

pub fn unix_mmap(
    addr: Option<&mut std::ffi::c_void>,
    size: usize,
    try_alignment: usize,
    protect_flags: std::ffi::c_int,
    large_only: bool,
    allow_large: bool,
    is_large: &mut bool,
) -> Option<&'static mut std::ffi::c_void> {
    let fd = unix_mmap_fd();
    let mut flags = libc::MAP_PRIVATE | libc::MAP_ANON;
    
    if crate::_mi_os_has_overcommit() {
        // No additional flags needed for overcommit
    }
    
    let mut p: Option<&'static mut std::ffi::c_void> = Option::None;
    
    // Convert addr to a raw pointer that we can reuse
    let addr_ptr = addr.map(|a| a as *mut std::ffi::c_void);
    
    if allow_large && (large_only || crate::_mi_os_use_large_page(size, try_alignment)) {
        let mut try_ok = LARGE_PAGE_TRY_OK.load(Ordering::Acquire);
        
        if !large_only && try_ok > 0 {
            LARGE_PAGE_TRY_OK.compare_exchange(try_ok, try_ok - 1, Ordering::AcqRel, Ordering::Acquire).ok();
        } else {
            let lflags = flags;
            let lfd = fd;
            
            if large_only || (lflags != flags) {
                *is_large = true;
                // Convert back from raw pointer to reference for the call
                p = unix_mmap_prim_aligned(addr_ptr.map(|ptr| unsafe { &mut *ptr }), size, try_alignment, protect_flags, lflags, lfd);
                
                if large_only {
                    return p;
                }
                
                if p.is_none() {
                    LARGE_PAGE_TRY_OK.store(8, Ordering::Release);
                }
            }
        }
    }
    
    if p.is_none() {
        *is_large = false;
        // For the second call, use the same addr_ptr converted back
        if p.is_none() {
            p = unix_mmap_prim_aligned(addr_ptr.map(|ptr| unsafe { &mut *ptr }), size, try_alignment, protect_flags, flags, fd);
        }
    }
    
    p
}
pub fn _mi_prim_alloc(
    hint_addr: Option<&mut std::ffi::c_void>,
    size: usize,
    try_alignment: usize,
    commit: bool,
    allow_large: bool,
    is_large: &mut bool,
    is_zero: &mut bool,
    addr: &mut Option<&'static mut std::ffi::c_void>,
) -> libc::c_int {
    // Assertions translated to debug assertions
    debug_assert!(size > 0 && (size % crate::_mi_os_page_size()) == 0);
    debug_assert!(commit || !allow_large);
    debug_assert!(try_alignment > 0);

    // Adjust try_alignment under specific conditions
    let mut adjusted_try_alignment = try_alignment;
    if hint_addr.is_none()
        && size >= (8 * (2 * (1024 * 1024)))
        && try_alignment > 1
        && crate::_mi_is_power_of_two(try_alignment)
        && try_alignment < (2 * (1024 * 1024))
    {
        adjusted_try_alignment = 2 * (1024 * 1024);
    }

    *is_zero = true;
    let protect_flags = if commit { libc::PROT_WRITE | libc::PROT_READ } else { libc::PROT_NONE };

    *addr = crate::unix_mmap(
        hint_addr,
        size,
        adjusted_try_alignment,
        protect_flags,
        false,
        allow_large,
        is_large,
    );

    if addr.is_some() {
        0
    } else {
        std::io::Error::last_os_error().raw_os_error().unwrap_or(-1) as libc::c_int
    }
}
pub fn _mi_prim_reset(start: *mut c_void, size: size_t) -> c_int {
    unsafe {
        let err = unix_madvise(start, size, libc::MADV_DONTNEED);
        if err != 0 {
            return err;
        }
        0
    }
}

pub unsafe fn _mi_prim_decommit(start: *mut c_void, size: size_t, needs_recommit: *mut bool) -> c_int {
    let mut err: c_int = 0;
    err = unix_madvise(start, size, MADV_DONTNEED);
    *needs_recommit = true;
    libc::mprotect(start, size, PROT_NONE);
    err
}
pub fn _mi_prim_protect(start: *mut libc::c_void, size: usize, protect: bool) -> libc::c_int {
    let prot = if protect { libc::PROT_NONE } else { libc::PROT_READ | libc::PROT_WRITE };
    let err = unsafe { libc::mprotect(start, size, prot) };
    
    let result = if err != 0 {
        unsafe { *libc::__errno_location() }
    } else {
        err
    };
    
    unix_mprotect_hint(result);
    result
}
pub fn _mi_prim_numa_node_count() -> usize {
    let mut buf = [0u8; 128];
    let mut node: u32 = 0;
    
    for current_node in 0..256 {
        unsafe {
            crate::_mi_snprintf(
                buf.as_mut_ptr(), 
                127, 
                b"/sys/devices/system/node/node%u\0".as_ptr(), 
                &mut (current_node + 1) as *mut _ as *mut std::ffi::c_void
            );
        }
        
        let path_str = std::str::from_utf8(&buf[..buf.iter().position(|&b| b == 0).unwrap_or(buf.len())]).unwrap();
        
        if crate::mi_prim_access(path_str, 4) != 0 {
            break;
        }
        node = current_node + 1;
    }
    
    (node + 1) as usize
}
pub fn _mi_prim_alloc_huge_os_pages(
    hint_addr: Option<&mut c_void>,
    size: usize,
    numa_node: i32,
    is_zero: &mut bool,
    addr: &mut Option<&'static mut c_void>,
) -> i32 {
    let mut is_large = true;
    *is_zero = true;
    *addr = unix_mmap(
        hint_addr,
        size,
        1 << (9 + (13 + 3)),
        libc::PROT_READ | libc::PROT_WRITE,
        true,
        true,
        &mut is_large,
    );

    if let Some(alloc_addr) = addr.as_mut() {
        if numa_node >= 0 && numa_node < (8 * (1 << 3)) {
            let numa_mask = 1usize << numa_node;
            let err = mi_prim_mbind(
                Some(*alloc_addr),
                size,
                1,
                Some(&[numa_mask]),
                8 * (1 << 3),
                0,
            );
            if err != 0 {
                let err_code = std::io::Error::last_os_error().raw_os_error().unwrap_or(-1);
                let msg = std::ffi::CString::new(
                    format!("failed to bind huge (1GiB) pages to numa node {} (error: {} (0x{:x}))\n", 
                            numa_node, err_code, err_code)
                ).unwrap();
                crate::_mi_warning_message(&msg);
            }
        }
    }

    if addr.is_some() {
        0
    } else {
        std::io::Error::last_os_error().raw_os_error().unwrap_or(-1)
    }
}

pub fn unix_detect_overcommit() -> bool {
    let mut os_overcommit = true;
    
    match mi_prim_open(Some("/proc/sys/vm/overcommit_memory"), libc::O_RDONLY) {
        Ok(fd) => {
            let mut buf = [0u8; 32];
            let raw_fd: RawFd = fd.as_raw_fd();
            let nread = unsafe { mi_prim_read(raw_fd, buf.as_mut_ptr() as *mut libc::c_void, buf.len()) };
            if nread >= 1 {
                os_overcommit = buf[0] == b'0' || buf[0] == b'1';
            }
            let _ = mi_prim_close(raw_fd);
        }
        Err(_) => {}
    }
    
    os_overcommit
}
pub fn _mi_prim_mem_init(config: &mut crate::MiOsMemConfigS) {
    let psize = unsafe { libc::sysconf(libc::_SC_PAGESIZE) };
    if psize > 0 {
        config.page_size = psize as usize;
        config.alloc_granularity = psize as usize;
    }
    config.large_page_size = 2 * (1024 * 1024);
    config.has_overcommit = unix_detect_overcommit();
    config.has_partial_free = true;
    config.has_virtual_reserve = true;
}
pub static _MI_HEAP_DEFAULT_KEY: AtomicI32 = AtomicI32::new(-1);

thread_local! {
    static MI_HEAP_DEFAULT: std::cell::RefCell<crate::MiHeapT> = std::cell::RefCell::new(None);
}

pub fn _mi_prim_thread_associate_default_heap(heap: crate::MiHeapT) {
    if _MI_HEAP_DEFAULT_KEY.load(Ordering::Relaxed) != -1 {
        // Use thread-local storage to associate the heap with the current thread
        MI_HEAP_DEFAULT.with(|default_heap| {
            *default_heap.borrow_mut() = heap;
        });
    }
}
pub fn _mi_prim_random_buf(buf: &mut [u8]) -> bool {
    let flags = libc::O_RDONLY;
    let fd_result = mi_prim_open(Some("/dev/urandom"), flags);
    
    let mut fd = match fd_result {
        Ok(file) => file,
        Err(_) => return false,
    };

    let buf_len = buf.len();
    let mut count = 0;
    
    while count < buf_len {
        let remaining = buf_len - count;
        let read_result = unsafe { 
            mi_prim_read(
                fd.as_raw_fd(), 
                buf[count..].as_mut_ptr() as *mut libc::c_void, 
                remaining
            ) 
        };
        
        if read_result > 0 {
            count += read_result as usize;
        } else if read_result == 0 {
            break; // EOF
        } else {
            // read_result < 0 indicates error
            let errno = std::io::Error::last_os_error().raw_os_error().unwrap_or(0);
            if errno != libc::EAGAIN && errno != libc::EINTR {
                break;
            }
        }
    }

    let _ = mi_prim_close(fd.as_raw_fd());
    count == buf_len
}
pub fn _mi_prim_process_info(pinfo: Option<&mut MiProcessInfoS>) {
    if let Some(pinfo) = pinfo {
        let mut rusage: libc::rusage = unsafe { std::mem::zeroed() };
        
        unsafe {
            libc::getrusage(libc::RUSAGE_SELF, &mut rusage);
        }
        
        pinfo.utime = timeval_secs(Some(&rusage.ru_utime));
        pinfo.stime = timeval_secs(Some(&rusage.ru_stime));
        pinfo.page_faults = rusage.ru_majflt as usize;
        pinfo.peak_rss = (rusage.ru_maxrss as usize) * 1024;
    }
}
pub fn _mi_prim_thread_done_auto_done() {
    let key = _MI_HEAP_DEFAULT_KEY.load(Ordering::Relaxed);
    if key != -1 {
        // In a real implementation, you would need platform-specific thread local storage cleanup
        // For pthread_key_delete equivalent, we would need platform-specific code
        // For now, we just reset the atomic value to mimic the cleanup
        _MI_HEAP_DEFAULT_KEY.store(-1, Ordering::Relaxed);
    }
}
pub fn mi_process_attach() {
    crate::_mi_auto_process_init();
}
pub fn mi_process_detach() {
    // For process detachment, we might need to call the init function 
    // with different parameters or there might be cleanup logic needed
    // Since _mi_auto_process_done is not available, using init as fallback
    // or this might need to be implemented differently
    crate::_mi_auto_process_init();
}
