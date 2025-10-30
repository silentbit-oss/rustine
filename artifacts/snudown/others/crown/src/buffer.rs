use ::libc;
extern "C" {
    fn vsnprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn realloc(_: *mut libc::c_void, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memmove(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
}
pub type __builtin_va_list = [__va_list_tag; 1];
#[derive(Copy, Clone)]
#[repr(C)]
pub struct __va_list_tag {
    pub gp_offset: libc::c_uint,
    pub fp_offset: libc::c_uint,
    pub overflow_arg_area: *mut libc::c_void,
    pub reg_save_area: *mut libc::c_void,
}
pub type size_t = libc::c_ulong;
pub type va_list = __builtin_va_list;
pub type __uint8_t = libc::c_uchar;
pub type uint8_t = __uint8_t;
pub type C2RustUnnamed = libc::c_int;
pub const BUF_EINVALIDIDX: C2RustUnnamed = -2;
pub const BUF_ENOMEM: C2RustUnnamed = -1;
pub const BUF_OK: C2RustUnnamed = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct buf {
    pub data: *mut uint8_t,
    pub size: size_t,
    pub asize: size_t,
    pub unit: size_t,
}
#[no_mangle]
pub unsafe extern "C" fn bufprefix(
    mut buf: *const buf,
    mut prefix: *const libc::c_char,
) -> libc::c_int {
    let mut i: size_t = 0;
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            38 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 48],
                &[libc::c_char; 48],
            >(b"int bufprefix(const struct buf *, const char *)\0"))
                .as_ptr(),
        );
    }
    'c_621: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                38 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 48],
                    &[libc::c_char; 48],
                >(b"int bufprefix(const struct buf *, const char *)\0"))
                    .as_ptr(),
            );
        }
    };
    i = 0 as libc::c_int as size_t;
    while i < (*buf).size {
        if *prefix.offset(i as isize) as libc::c_int == 0 as libc::c_int {
            return 0 as libc::c_int;
        }
        if *((*buf).data).offset(i as isize) as libc::c_int
            != *prefix.offset(i as isize) as libc::c_int
        {
            return *((*buf).data).offset(i as isize) as libc::c_int
                - *prefix.offset(i as isize) as libc::c_int;
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn bufgrow(mut buf: *mut buf, mut neosz: size_t) -> libc::c_int {
    let mut neoasz: size_t = 0;
    let mut neodata: *mut libc::c_void = 0 as *mut libc::c_void;
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            58 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 34],
                &[libc::c_char; 34],
            >(b"int bufgrow(struct buf *, size_t)\0"))
                .as_ptr(),
        );
    }
    'c_309: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                58 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 34],
                    &[libc::c_char; 34],
                >(b"int bufgrow(struct buf *, size_t)\0"))
                    .as_ptr(),
            );
        }
    };
    if neosz > (1024 as libc::c_int * 1024 as libc::c_int * 16 as libc::c_int) as size_t
    {
        return BUF_ENOMEM as libc::c_int;
    }
    if (*buf).asize >= neosz {
        return BUF_OK as libc::c_int;
    }
    neoasz = ((*buf).asize).wrapping_add((*buf).unit);
    while neoasz < neosz {
        neoasz = neoasz.wrapping_add((*buf).unit);
    }
    neodata = realloc((*buf).data as *mut libc::c_void, neoasz);
    if neodata.is_null() {std::intrinsics::assume((neodata).addr() == 0);
        return BUF_ENOMEM as libc::c_int;
    }
    (*buf).data = neodata as *mut uint8_t;
    (*buf).asize = neoasz;
    return BUF_OK as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn bufnew(mut unit: size_t) -> *mut buf {
    let mut ret: *mut buf = 0 as *mut buf;
    ret = malloc(::core::mem::size_of::<buf>() as libc::c_ulong) as *mut buf;
    if !ret.is_null() {
        (*ret).data = 0 as *mut uint8_t;
        (*ret).asize = 0 as libc::c_int as size_t;
        (*ret).size = (*ret).asize;
        (*ret).unit = unit;
    }else { std::intrinsics::assume((ret).addr() == 0); }
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn bufcstr(mut buf: *mut buf) -> *const libc::c_char {
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            99 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 34],
                &[libc::c_char; 34],
            >(b"const char *bufcstr(struct buf *)\0"))
                .as_ptr(),
        );
    }
    'c_504: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                99 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 34],
                    &[libc::c_char; 34],
                >(b"const char *bufcstr(struct buf *)\0"))
                    .as_ptr(),
            );
        }
    };
    if (*buf).size < (*buf).asize
        && *((*buf).data).offset((*buf).size as isize) as libc::c_int == 0 as libc::c_int
    {
        return (*buf).data as *mut libc::c_char;
    }
    if ((*buf).size).wrapping_add(1 as libc::c_int as size_t) <= (*buf).asize
        || bufgrow(buf, ((*buf).size).wrapping_add(1 as libc::c_int as size_t))
            == 0 as libc::c_int
    {
        *((*buf).data).offset((*buf).size as isize) = 0 as libc::c_int as uint8_t;
        return (*buf).data as *mut libc::c_char;
    }
    return 0 as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn bufprintf(
    mut buf: *mut buf,
    mut fmt: *const libc::c_char,
    mut args: ...
) {
    let mut ap: ::core::ffi::VaListImpl;
    let mut n: libc::c_int = 0;
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            119 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 48],
                &[libc::c_char; 48],
            >(b"void bufprintf(struct buf *, const char *, ...)\0"))
                .as_ptr(),
        );
    }
    'c_1257: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                119 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 48],
                    &[libc::c_char; 48],
                >(b"void bufprintf(struct buf *, const char *, ...)\0"))
                    .as_ptr(),
            );
        }
    };
    if (*buf).size >= (*buf).asize
        && bufgrow(buf, ((*buf).size).wrapping_add(1 as libc::c_int as size_t))
            < 0 as libc::c_int
    {
        return;
    }
    ap = args.clone();
    n = vsnprintf(
        ((*buf).data as *mut libc::c_char).offset((*buf).size as isize),
        ((*buf).asize).wrapping_sub((*buf).size),
        fmt,
        ap.as_va_list(),
    );
    if n < 0 as libc::c_int {
        return;
    }
    if n as size_t >= ((*buf).asize).wrapping_sub((*buf).size) {
        if bufgrow(
            buf,
            ((*buf).size)
                .wrapping_add(n as size_t)
                .wrapping_add(1 as libc::c_int as size_t),
        ) < 0 as libc::c_int
        {
            return;
        }
        ap = args.clone();
        n = vsnprintf(
            ((*buf).data as *mut libc::c_char).offset((*buf).size as isize),
            ((*buf).asize).wrapping_sub((*buf).size),
            fmt,
            ap.as_va_list(),
        );
    }
    if n < 0 as libc::c_int {
        return;
    }
    (*buf).size = ((*buf).size).wrapping_add(n as size_t);
}
#[no_mangle]
pub unsafe extern "C" fn bufput(
    mut buf: *mut buf,
    mut data: *const libc::c_void,
    mut len: size_t,
) {
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            155 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 48],
                &[libc::c_char; 48],
            >(b"void bufput(struct buf *, const void *, size_t)\0"))
                .as_ptr(),
        );
    }
    'c_732: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                155 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 48],
                    &[libc::c_char; 48],
                >(b"void bufput(struct buf *, const void *, size_t)\0"))
                    .as_ptr(),
            );
        }
    };
    if ((*buf).size).wrapping_add(len) > (*buf).asize
        && bufgrow(buf, ((*buf).size).wrapping_add(len)) < 0 as libc::c_int
    {
        return;
    }
    memcpy(((*buf).data).offset((*buf).size as isize) as *mut libc::c_void, data, len);
    (*buf).size = ((*buf).size).wrapping_add(len);
}
#[no_mangle]
pub unsafe extern "C" fn bufputs(mut buf: *mut buf, mut str: *const libc::c_char) {
    bufput(buf, str as *const libc::c_void, strlen(str));
}
#[no_mangle]
pub unsafe extern "C" fn bufputc(mut buf: *mut buf, mut c: libc::c_int) {
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            176 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 32],
                &[libc::c_char; 32],
            >(b"void bufputc(struct buf *, int)\0"))
                .as_ptr(),
        );
    }
    'c_854: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                176 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 32],
                    &[libc::c_char; 32],
                >(b"void bufputc(struct buf *, int)\0"))
                    .as_ptr(),
            );
        }
    };
    if ((*buf).size).wrapping_add(1 as libc::c_int as size_t) > (*buf).asize
        && bufgrow(buf, ((*buf).size).wrapping_add(1 as libc::c_int as size_t))
            < 0 as libc::c_int
    {
        return;
    }
    *((*buf).data).offset((*buf).size as isize) = c as uint8_t;
    (*buf).size = ((*buf).size).wrapping_add(1 as libc::c_int as size_t);
}
#[no_mangle]
pub unsafe extern "C" fn bufrelease(mut buf: *mut buf) {
    if buf.is_null() {std::intrinsics::assume((buf).addr() == 0);
        return;
    }
    free((*buf).data as *mut libc::c_void);
    free(buf as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn bufreset(mut buf: *mut buf) {
    if buf.is_null() {std::intrinsics::assume((buf).addr() == 0);
        return;
    }
    free((*buf).data as *mut libc::c_void);
    (*buf).data = 0 as *mut uint8_t;
    (*buf).asize = 0 as libc::c_int as size_t;
    (*buf).size = (*buf).asize;
}
#[no_mangle]
pub unsafe extern "C" fn bufslurp(mut buf: *mut buf, mut len: size_t) {
    if !buf.is_null() && (*buf).unit != 0 {} else {
        __assert_fail(
            b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            213 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 36],
                &[libc::c_char; 36],
            >(b"void bufslurp(struct buf *, size_t)\0"))
                .as_ptr(),
        );
    }
    'c_1018: {
        if !buf.is_null() && (*buf).unit != 0 {} else {
            __assert_fail(
                b"buf && buf->unit\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                213 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 36],
                    &[libc::c_char; 36],
                >(b"void bufslurp(struct buf *, size_t)\0"))
                    .as_ptr(),
            );
        }
    };
    if len >= (*buf).size {
        (*buf).size = 0 as libc::c_int as size_t;
        return;
    }
    (*buf).size = ((*buf).size).wrapping_sub(len);
    memmove(
        (*buf).data as *mut libc::c_void,
        ((*buf).data).offset(len as isize) as *const libc::c_void,
        (*buf).size,
    );
}
#[no_mangle]
pub unsafe extern "C" fn buftruncate(
    mut buf: *mut buf,
    mut size: size_t,
) -> libc::c_int {
    if (*buf).size < size || size < 0 as libc::c_int as size_t {
        __assert_fail(
            b"0\0" as *const u8 as *const libc::c_char,
            b"buffer.c\0" as *const u8 as *const libc::c_char,
            230 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 38],
                &[libc::c_char; 38],
            >(b"int buftruncate(struct buf *, size_t)\0"))
                .as_ptr(),
        );
        'c_1318: {
            __assert_fail(
                b"0\0" as *const u8 as *const libc::c_char,
                b"buffer.c\0" as *const u8 as *const libc::c_char,
                230 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 38],
                    &[libc::c_char; 38],
                >(b"int buftruncate(struct buf *, size_t)\0"))
                    .as_ptr(),
            );
        };
        return BUF_EINVALIDIDX as libc::c_int;
    }
    (*buf).size = size;
    return BUF_OK as libc::c_int;
}
