




use std::slice;

use std::ffi::CStr;
use std::convert::TryInto;

use std::ptr;
use std::alloc;

extern "C" {
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn realloc(_: *mut std::os::raw::c_void, _: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn free(__ptr: *mut std::os::raw::c_void);
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memmove(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn strlen(_: *const std::os::raw::c_char) -> std::os::raw::c_ulong;
}
pub type size_t = crate::src::autolink::size_t;
pub type __uint8_t = crate::src::autolink::__uint8_t;
pub type uint8_t = crate::src::autolink::uint8_t;
pub type C2RustUnnamed = std::os::raw::c_int;
pub const BUF_EINVALIDIDX: C2RustUnnamed = -2;
pub const BUF_ENOMEM: C2RustUnnamed = -1;
pub const BUF_OK: C2RustUnnamed = 0;
// #[derive(Copy, Clone)]

pub type buf = crate::src::autolink::buf;
//16mb
#[no_mangle]
pub fn bufprefix(buf: &buf, prefix: &CStr) -> i32 {
    let buf_data = unsafe { std::slice::from_raw_parts(buf.data, buf.size.try_into().unwrap()) };
    let prefix_bytes = prefix.to_bytes();

    for (i, &byte) in buf_data.iter().enumerate() {
        if i >= prefix_bytes.len() {
            return 0;
        }
        if byte == 0 {
            return 0;
        }
        if byte != prefix_bytes[i] {
            return byte as i32 - prefix_bytes[i] as i32;
        }
    }
    return 0;
}

/* bufgrow: increasing the allocated size to the given value */
#[no_mangle]
pub unsafe extern "C" fn bufgrow(mut buf: *mut buf, mut neosz: size_t)
 -> std::os::raw::c_int {
    let mut neoasz: size_t = 0;
    let mut neodata: *mut std::os::raw::c_void = 0 as *mut std::os::raw::c_void;
    if neosz >
           (1024 as std::os::raw::c_int * 1024 as std::os::raw::c_int * 16 as std::os::raw::c_int) as
               std::os::raw::c_ulong {
        return BUF_ENOMEM as std::os::raw::c_int
    }
    if (*buf).asize >= neosz { return BUF_OK as std::os::raw::c_int }
    neoasz = (*buf).asize.wrapping_add((*buf).unit);
    while neoasz < neosz {
        neoasz =
            (neoasz as std::os::raw::c_ulong).wrapping_add((*buf).unit) as size_t as
                size_t
    }
    neodata = realloc((*buf).data as *mut std::os::raw::c_void, neoasz);
    if neodata.is_null() { return BUF_ENOMEM as std::os::raw::c_int }
    (*buf).data = neodata as *mut uint8_t;
    (*buf).asize = neoasz;
    return BUF_OK as std::os::raw::c_int;
}
/* bufnew: allocation of a new buffer */
#[no_mangle]
pub fn bufnew(unit: u64) -> *mut buf {
    let mut ret = buf {
        data: std::ptr::null_mut(),
        asize: 0,
        size: 0,
        unit,
    };
    
    // Allocate memory for the Buf instance
    let buf_size = std::mem::size_of::<buf>();
    let buf_ptr = unsafe { std::alloc::alloc(std::alloc::Layout::from_size_align(buf_size, std::mem::align_of::<buf>()).unwrap()) as *mut buf };
    
    if buf_ptr.is_null() {
        return std::ptr::null_mut(); // Allocation failed
    }
    
    // Initialize the allocated memory
    unsafe {
        *buf_ptr = ret;
    }
    
    buf_ptr
}

/* bufnullterm: NULL-termination of the string array */
#[no_mangle]
pub fn bufcstr(mut buf: &mut buf) -> Option<&CStr> {
    if buf.size < buf.asize && unsafe { *buf.data.add(buf.size as usize) } == 0 {
        return Some(unsafe { CStr::from_ptr(buf.data as *const _) });
    }
    if buf.size.wrapping_add(1) <= buf.asize || unsafe { bufgrow(buf, buf.size.wrapping_add(1)) } == 0 {
        unsafe {
            *buf.data.add(buf.size as usize) = 0;
        }
        return Some(unsafe { CStr::from_ptr(buf.data as *const _) });
    }
    None
}

/* bufput: appends raw data to a buffer */
#[no_mangle]
pub unsafe extern "C" fn bufput(mut buf: *mut buf,
                                mut data: *const std::os::raw::c_void,
                                mut len: size_t) {
    if (*buf).size.wrapping_add(len) > (*buf).asize &&
           bufgrow(buf, (*buf).size.wrapping_add(len)) < 0 as std::os::raw::c_int {
        return
    }
    memcpy((*buf).data.offset((*buf).size as isize) as *mut std::os::raw::c_void,
           data, len);
    (*buf).size =
        ((*buf).size as std::os::raw::c_ulong).wrapping_add(len) as size_t as size_t;
}
/* bufputs: appends a NUL-terminated string to a buffer */
#[no_mangle]
pub fn bufputs(buf: &mut buf, str: &str) {
    unsafe {
        bufput(buf, str.as_ptr() as *const std::os::raw::c_void, str.len() as u64);
    }
}

/* bufputc: appends a single uint8_t to a buffer */
#[no_mangle]
pub unsafe extern "C" fn bufputc(mut buf: *mut buf, mut c: std::os::raw::c_int) {
    if (*buf).size.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) >
           (*buf).asize &&
           bufgrow(buf,
                   (*buf).size.wrapping_add(1 as std::os::raw::c_int as
                                                std::os::raw::c_ulong)) <
               0 as std::os::raw::c_int {
        return
    }
    *(*buf).data.offset((*buf).size as isize) = c as uint8_t;
    (*buf).size =
        ((*buf).size as
             std::os::raw::c_ulong).wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
            size_t as size_t;
}
/* bufrelease: decrease the reference count and free the buffer if needed */
#[no_mangle]
pub unsafe extern "C" fn bufrelease(mut buf: *mut buf) {
    if buf.is_null() { return }
    free((*buf).data as *mut std::os::raw::c_void);
    free(buf as *mut std::os::raw::c_void);
}
/* bufreset: frees internal data of the buffer */
#[no_mangle]
pub fn bufreset(mut buf: &mut crate::src::autolink::buf) {
    if buf.data.is_null() { return; }
    let layout = std::alloc::Layout::from_size_align(buf.asize.try_into().unwrap(), std::mem::align_of::<u8>()).unwrap();
    unsafe {
        std::alloc::dealloc(buf.data, layout);
    }
    buf.data = std::ptr::null_mut(); // Set data to null
    buf.asize = 0;
    buf.size = buf.asize;
}

/* bufslurp: removes a given number of bytes from the head of the array */
#[no_mangle]
pub fn bufslurp(buf: &mut crate::src::autolink::buf, len: usize) {
    if len >= buf.size as usize {
        buf.size = 0;
        return;
    }
    buf.size -= len as u64;
    let data_slice = unsafe { std::slice::from_raw_parts_mut(buf.data.add(len), (buf.size as usize) - len) };
    let target_slice = unsafe { std::slice::from_raw_parts_mut(buf.data, buf.size as usize) };
    target_slice.copy_from_slice(data_slice);
}

/* buftruncate: truncates the buffer at `size` */
/* buftrucate: truncates the buffer at `size` */
#[no_mangle]
pub fn buftruncate(mut buf: &mut crate::src::autolink::buf, mut size: u64) -> i32 {
    if buf.size < size || size == u64::MAX {
        // bail out in debug mode so we can figure out why this happened
        return BUF_EINVALIDIDX;
    }
    buf.size = size;
    BUF_OK
}

