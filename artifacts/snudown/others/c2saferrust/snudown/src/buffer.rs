
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
pub unsafe extern "C" fn bufprefix(mut buf: *const buf,
                                   mut prefix: *const std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut i: size_t = 0;
    i = 0 as std::os::raw::c_int as size_t;
    while i < (*buf).size {
        if *prefix.offset(i as isize) as std::os::raw::c_int == 0 as std::os::raw::c_int {
            return 0 as std::os::raw::c_int
        }
        if *(*buf).data.offset(i as isize) as std::os::raw::c_int !=
               *prefix.offset(i as isize) as std::os::raw::c_int {
            return *(*buf).data.offset(i as isize) as std::os::raw::c_int -
                       *prefix.offset(i as isize) as std::os::raw::c_int
        }
        i = i.wrapping_add(1)
    }
    return 0 as std::os::raw::c_int;
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
pub unsafe extern "C" fn bufnew(mut unit: size_t) -> *mut buf {
    let mut ret: *mut buf = 0 as *mut buf;
    ret = malloc(::std::mem::size_of::<buf>() as std::os::raw::c_ulong) as *mut buf;
    if !ret.is_null() {
        (*ret).data = 0 as *mut uint8_t;
        (*ret).asize = 0 as std::os::raw::c_int as size_t;
        (*ret).size = (*ret).asize;
        (*ret).unit = unit
    }
    return ret;
}
/* bufnullterm: NULL-termination of the string array */
#[no_mangle]
pub unsafe extern "C" fn bufcstr(mut buf: *mut buf) -> *const std::os::raw::c_char {
    if (*buf).size < (*buf).asize &&
           *(*buf).data.offset((*buf).size as isize) as std::os::raw::c_int ==
               0 as std::os::raw::c_int {
        return (*buf).data as *mut std::os::raw::c_char
    }
    if (*buf).size.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) <=
           (*buf).asize ||
           bufgrow(buf,
                   (*buf).size.wrapping_add(1 as std::os::raw::c_int as
                                                std::os::raw::c_ulong)) ==
               0 as std::os::raw::c_int {
        *(*buf).data.offset((*buf).size as isize) =
            0 as std::os::raw::c_int as uint8_t;
        return (*buf).data as *mut std::os::raw::c_char
    }
    return 0 as *const std::os::raw::c_char;
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
pub unsafe extern "C" fn bufputs(mut buf: *mut buf,
                                 mut str: *const std::os::raw::c_char) {
    bufput(buf, str as *const std::os::raw::c_void, strlen(str));
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
pub unsafe extern "C" fn bufreset(mut buf: *mut buf) {
    if buf.is_null() { return }
    free((*buf).data as *mut std::os::raw::c_void);
    (*buf).data = 0 as *mut uint8_t;
    (*buf).asize = 0 as std::os::raw::c_int as size_t;
    (*buf).size = (*buf).asize;
}
/* bufslurp: removes a given number of bytes from the head of the array */
#[no_mangle]
pub unsafe extern "C" fn bufslurp(mut buf: *mut buf, mut len: size_t) {
    if len >= (*buf).size { (*buf).size = 0 as std::os::raw::c_int as size_t; return }
    (*buf).size =
        ((*buf).size as std::os::raw::c_ulong).wrapping_sub(len) as size_t as size_t;
    memmove((*buf).data as *mut std::os::raw::c_void,
            (*buf).data.offset(len as isize) as *const std::os::raw::c_void,
            (*buf).size);
}
/* buftruncate: truncates the buffer at `size` */
/* buftrucate: truncates the buffer at `size` */
#[no_mangle]
pub unsafe extern "C" fn buftruncate(mut buf: *mut buf, mut size: size_t)
 -> std::os::raw::c_int {
    if (*buf).size < size || size < 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        /* bail out in debug mode so we can figure out why this happened */
        return BUF_EINVALIDIDX as std::os::raw::c_int
    }
    (*buf).size = size;
    return BUF_OK as std::os::raw::c_int;
}
