use ::libc;
extern "C" {
    fn __errno_location() -> *mut libc::c_int;
    fn vsnprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn vasprintf(
        __ptr: *mut *mut libc::c_char,
        __f: *const libc::c_char,
        __arg: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn realloc(_: *mut libc::c_void, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
}
pub type __builtin_va_list = [crate::src::debug::__va_list_tag; 1];
#[derive(Copy, Clone)]

struct ErasedByPreprocessor27 { dummy: () }
pub type __gnuc_va_list = __builtin_va_list;
pub type va_list = __gnuc_va_list;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor28 { dummy: () }
#[no_mangle]
pub unsafe extern "C" fn printbuf_new() -> *mut crate::src::apps::json_parse::printbuf {
    let mut p: *mut crate::src::apps::json_parse::printbuf = 0 as *mut crate::src::apps::json_parse::printbuf;
    p = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<crate::src::apps::json_parse::printbuf>() as libc::c_ulong,
    ) as *mut crate::src::apps::json_parse::printbuf;
    if p.is_null() {std::intrinsics::assume((p).addr() == 0);
        return 0 as *mut crate::src::apps::json_parse::printbuf;
    }
    (*p).size = 32 as libc::c_int;
    (*p).bpos = 0 as libc::c_int;
    (*p).buf = malloc((*p).size as libc::c_ulong) as *mut libc::c_char;
    if ((*p).buf).is_null() {std::intrinsics::assume(((*p).buf).addr() == 0);
        free(p as *mut libc::c_void);
        return 0 as *mut crate::src::apps::json_parse::printbuf;
    }
    *((*p).buf).offset(0 as libc::c_int as isize) = '\0' as i32 as libc::c_char;
    return p;
}
unsafe extern "C" fn printbuf_extend(
    mut p: *mut crate::src::apps::json_parse::printbuf,
    mut min_size: libc::c_int,
) -> libc::c_int {
    let mut t: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut new_size: libc::c_int = 0;
    if (*p).size >= min_size {
        return 0 as libc::c_int;
    }
    if min_size > 2147483647 as libc::c_int - 8 as libc::c_int {
        *__errno_location() = 27 as libc::c_int;
        return -(1 as libc::c_int);
    }
    if (*p).size > 2147483647 as libc::c_int / 2 as libc::c_int {
        new_size = min_size + 8 as libc::c_int;
    } else {
        new_size = (*p).size * 2 as libc::c_int;
        if new_size < min_size + 8 as libc::c_int {
            new_size = min_size + 8 as libc::c_int;
        }
    }
    t = realloc((*p).buf as *mut libc::c_void, new_size as libc::c_ulong)
        as *mut libc::c_char;
    if t.is_null() {std::intrinsics::assume((t).addr() == 0);
        return -(1 as libc::c_int);
    }
    (*p).size = new_size;
    (*p).buf = t;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn printbuf_memappend(
    mut p: *mut crate::src::apps::json_parse::printbuf,
    mut buf: *const libc::c_char,
    mut size: libc::c_int,
) -> libc::c_int {
    if size < 0 as libc::c_int
        || size > 2147483647 as libc::c_int - (*p).bpos - 1 as libc::c_int
    {
        *__errno_location() = 27 as libc::c_int;
        return -(1 as libc::c_int);
    }
    if (*p).size <= (*p).bpos + size + 1 as libc::c_int {
        if {let crown_promoted_local_0 = (*p).bpos + size + 1 as libc::c_int;printbuf_extend(p, crown_promoted_local_0)} < 0 as libc::c_int {
            return -(1 as libc::c_int);
        }
    }
    memcpy(
        ((*p).buf).offset((*p).bpos as isize) as *mut libc::c_void,
        buf as *const libc::c_void,
        size as libc::c_ulong,
    );
    (*p).bpos += size;
    *((*p).buf).offset((*p).bpos as isize) = '\0' as i32 as libc::c_char;
    return size;
}
#[no_mangle]
pub unsafe extern "C" fn printbuf_memset(
    mut pb: *mut crate::src::apps::json_parse::printbuf,
    mut offset: libc::c_int,
    mut charvalue: libc::c_int,
    mut len: libc::c_int,
) -> libc::c_int {
    let mut size_needed: libc::c_int = 0;
    if offset == -(1 as libc::c_int) {
        offset = (*pb).bpos;
    }
    if len < 0 as libc::c_int || offset < -(1 as libc::c_int)
        || len > 2147483647 as libc::c_int - offset
    {
        *__errno_location() = 27 as libc::c_int;
        return -(1 as libc::c_int);
    }
    size_needed = offset + len;
    if (*pb).size < size_needed {
        if printbuf_extend(pb, size_needed) < 0 as libc::c_int {
            return -(1 as libc::c_int);
        }
    }
    if (*pb).bpos < offset {
        memset(
            ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
            '\0' as i32,
            (offset - (*pb).bpos) as libc::c_ulong,
        );
    }
    memset(
        ((*pb).buf).offset(offset as isize) as *mut libc::c_void,
        charvalue,
        len as libc::c_ulong,
    );
    if (*pb).bpos < size_needed {
        (*pb).bpos = size_needed;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn sprintbuf(
    mut p: *mut crate::src::apps::json_parse::printbuf,
    mut msg: *const libc::c_char,
    mut args: ...
) -> libc::c_int {
    let mut ap: ::core::ffi::VaListImpl;
    let mut t: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut size: libc::c_int = 0;
    let mut buf: [libc::c_char; 128] = [0; 128];
    ap = args.clone();
    size = vsnprintf(
        buf.as_mut_ptr(),
        128 as libc::c_int as libc::c_ulong,
        msg,
        ap.as_va_list(),
    );
    if size < 0 as libc::c_int || size > 127 as libc::c_int {
        ap = args.clone();
        size = vasprintf(&raw mut t, msg, ap.as_va_list());
        if size < 0 as libc::c_int {
            return -(1 as libc::c_int);
        }
        size = printbuf_memappend(p, t, size);
        free(t as *mut libc::c_void);
    } else {
        size = printbuf_memappend(p, buf.as_mut_ptr(), size);
    }
    return size;
}
#[no_mangle]
pub unsafe extern "C" fn printbuf_reset(mut p: *mut crate::src::apps::json_parse::printbuf) {
    *((*p).buf).offset(0 as libc::c_int as isize) = '\0' as i32 as libc::c_char;
    (*p).bpos = 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn printbuf_free(mut p: *mut crate::src::apps::json_parse::printbuf) {
    if !p.is_null() {
        free((*p).buf as *mut libc::c_void);
        free(p as *mut libc::c_void);
    }else { std::intrinsics::assume((p).addr() == 0); }
}
