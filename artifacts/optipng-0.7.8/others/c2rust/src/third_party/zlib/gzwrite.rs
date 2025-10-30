use ::libc;
extern "C" {
    pub type internal_state;
    fn vsnprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn close(__fd: libc::c_int) -> libc::c_int;
    fn write(__fd: libc::c_int, __buf: *const libc::c_void, __n: size_t) -> ssize_t;
    fn deflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn deflateEnd(strm: z_streamp) -> libc::c_int;
    fn deflateReset(strm: z_streamp) -> libc::c_int;
    fn deflateParams(
        strm: z_streamp,
        level: libc::c_int,
        strategy: libc::c_int,
    ) -> libc::c_int;
    fn deflateInit2_(
        strm: z_streamp,
        level: libc::c_int,
        method: libc::c_int,
        windowBits: libc::c_int,
        memLevel: libc::c_int,
        strategy: libc::c_int,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
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
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn strerror(_: libc::c_int) -> *mut libc::c_char;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn __errno_location() -> *mut libc::c_int;
    fn gz_error(_: gz_statep, _: libc::c_int, _: *const libc::c_char);
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
pub type __gnuc_va_list = __builtin_va_list;
pub type __off64_t = libc::c_long;
pub type __ssize_t = libc::c_long;
pub type va_list = __gnuc_va_list;
pub type off64_t = __off64_t;
pub type ssize_t = __ssize_t;
pub type z_size_t = size_t;
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
pub type voidpc = *const libc::c_void;
pub type voidpf = *mut libc::c_void;
pub type alloc_func = Option::<unsafe extern "C" fn(voidpf, uInt, uInt) -> voidpf>;
pub type free_func = Option::<unsafe extern "C" fn(voidpf, voidpf) -> ()>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct z_stream_s {
    pub next_in: *const Bytef,
    pub avail_in: uInt,
    pub total_in: uLong,
    pub next_out: *mut Bytef,
    pub avail_out: uInt,
    pub total_out: uLong,
    pub msg: *const libc::c_char,
    pub state: *mut internal_state,
    pub zalloc: alloc_func,
    pub zfree: free_func,
    pub opaque: voidpf,
    pub data_type: libc::c_int,
    pub adler: uLong,
    pub reserved: uLong,
}
pub type z_stream = z_stream_s;
pub type z_streamp = *mut z_stream;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct gzFile_s {
    pub have: libc::c_uint,
    pub next: *mut libc::c_uchar,
    pub pos: off64_t,
}
pub type gzFile = *mut gzFile_s;
pub type gz_statep = *mut gz_state;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct gz_state {
    pub x: gzFile_s,
    pub mode: libc::c_int,
    pub fd: libc::c_int,
    pub path: *mut libc::c_char,
    pub size: libc::c_uint,
    pub want: libc::c_uint,
    pub in_0: *mut libc::c_uchar,
    pub out: *mut libc::c_uchar,
    pub direct: libc::c_int,
    pub how: libc::c_int,
    pub start: off64_t,
    pub eof: libc::c_int,
    pub past: libc::c_int,
    pub level: libc::c_int,
    pub strategy: libc::c_int,
    pub reset: libc::c_int,
    pub skip: off64_t,
    pub seek: libc::c_int,
    pub err: libc::c_int,
    pub msg: *mut libc::c_char,
    pub strm: z_stream,
}
unsafe extern "C" fn gz_init(mut state: gz_statep) -> libc::c_int {
    let mut ret: libc::c_int = 0;
    let mut strm: z_streamp = &mut (*state).strm;
    (*state)
        .in_0 = malloc(((*state).want << 1 as libc::c_int) as libc::c_ulong)
        as *mut libc::c_uchar;
    if ((*state).in_0).is_null() {
        gz_error(
            state,
            -(4 as libc::c_int),
            b"out of memory\0" as *const u8 as *const libc::c_char,
        );
        return -(1 as libc::c_int);
    }
    if (*state).direct == 0 {
        (*state).out = malloc((*state).want as libc::c_ulong) as *mut libc::c_uchar;
        if ((*state).out).is_null() {
            free((*state).in_0 as *mut libc::c_void);
            gz_error(
                state,
                -(4 as libc::c_int),
                b"out of memory\0" as *const u8 as *const libc::c_char,
            );
            return -(1 as libc::c_int);
        }
        (*strm).zalloc = None;
        (*strm).zfree = None;
        (*strm).opaque = 0 as voidpf;
        ret = deflateInit2_(
            strm,
            (*state).level,
            8 as libc::c_int,
            15 as libc::c_int + 16 as libc::c_int,
            8 as libc::c_int,
            (*state).strategy,
            b"1.3-optipng\0" as *const u8 as *const libc::c_char,
            ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
        );
        if ret != 0 as libc::c_int {
            free((*state).out as *mut libc::c_void);
            free((*state).in_0 as *mut libc::c_void);
            gz_error(
                state,
                -(4 as libc::c_int),
                b"out of memory\0" as *const u8 as *const libc::c_char,
            );
            return -(1 as libc::c_int);
        }
        (*strm).next_in = 0 as *const Bytef;
    }
    (*state).size = (*state).want;
    if (*state).direct == 0 {
        (*strm).avail_out = (*state).size;
        (*strm).next_out = (*state).out;
        (*state).x.next = (*strm).next_out;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_comp(
    mut state: gz_statep,
    mut flush: libc::c_int,
) -> libc::c_int {
    let mut ret: libc::c_int = 0;
    let mut writ: libc::c_int = 0;
    let mut have: libc::c_uint = 0;
    let mut put: libc::c_uint = 0;
    let mut max: libc::c_uint = (-(1 as libc::c_int) as libc::c_uint >> 2 as libc::c_int)
        .wrapping_add(1 as libc::c_int as libc::c_uint);
    let mut strm: z_streamp = &mut (*state).strm;
    if (*state).size == 0 as libc::c_int as libc::c_uint
        && gz_init(state) == -(1 as libc::c_int)
    {
        return -(1 as libc::c_int);
    }
    if (*state).direct != 0 {
        while (*strm).avail_in != 0 {
            put = if (*strm).avail_in > max { max } else { (*strm).avail_in };
            writ = write(
                (*state).fd,
                (*strm).next_in as *const libc::c_void,
                put as size_t,
            ) as libc::c_int;
            if writ < 0 as libc::c_int {
                gz_error(state, -(1 as libc::c_int), strerror(*__errno_location()));
                return -(1 as libc::c_int);
            }
            (*strm)
                .avail_in = ((*strm).avail_in as libc::c_uint)
                .wrapping_sub(writ as libc::c_uint) as uInt as uInt;
            (*strm).next_in = ((*strm).next_in).offset(writ as isize);
        }
        return 0 as libc::c_int;
    }
    if (*state).reset != 0 {
        if (*strm).avail_in == 0 as libc::c_int as uInt {
            return 0 as libc::c_int;
        }
        deflateReset(strm);
        (*state).reset = 0 as libc::c_int;
    }
    ret = 0 as libc::c_int;
    loop {
        if (*strm).avail_out == 0 as libc::c_int as uInt
            || flush != 0 as libc::c_int
                && (flush != 4 as libc::c_int || ret == 1 as libc::c_int)
        {
            while (*strm).next_out > (*state).x.next {
                put = if ((*strm).next_out).offset_from((*state).x.next) as libc::c_long
                    > max as libc::c_int as libc::c_long
                {
                    max
                } else {
                    ((*strm).next_out).offset_from((*state).x.next) as libc::c_long
                        as libc::c_uint
                };
                writ = write(
                    (*state).fd,
                    (*state).x.next as *const libc::c_void,
                    put as size_t,
                ) as libc::c_int;
                if writ < 0 as libc::c_int {
                    gz_error(state, -(1 as libc::c_int), strerror(*__errno_location()));
                    return -(1 as libc::c_int);
                }
                (*state).x.next = ((*state).x.next).offset(writ as isize);
            }
            if (*strm).avail_out == 0 as libc::c_int as uInt {
                (*strm).avail_out = (*state).size;
                (*strm).next_out = (*state).out;
                (*state).x.next = (*state).out;
            }
        }
        have = (*strm).avail_out;
        ret = deflate(strm, flush);
        if ret == -(2 as libc::c_int) {
            gz_error(
                state,
                -(2 as libc::c_int),
                b"internal error: deflate stream corrupt\0" as *const u8
                    as *const libc::c_char,
            );
            return -(1 as libc::c_int);
        }
        have = have.wrapping_sub((*strm).avail_out);
        if !(have != 0) {
            break;
        }
    }
    if flush == 4 as libc::c_int {
        (*state).reset = 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_zero(mut state: gz_statep, mut len: off64_t) -> libc::c_int {
    let mut first: libc::c_int = 0;
    let mut n: libc::c_uint = 0;
    let mut strm: z_streamp = &mut (*state).strm;
    if (*strm).avail_in != 0 && gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int) {
        return -(1 as libc::c_int);
    }
    first = 1 as libc::c_int;
    while len != 0 {
        n = if ::core::mem::size_of::<libc::c_int>() as libc::c_ulong
            == ::core::mem::size_of::<off64_t>() as libc::c_ulong
            && (*state).size > 2147483647 as libc::c_int as libc::c_uint
            || (*state).size as off64_t > len
        {
            len as libc::c_uint
        } else {
            (*state).size
        };
        if first != 0 {
            memset(
                (*state).in_0 as *mut libc::c_void,
                0 as libc::c_int,
                n as libc::c_ulong,
            );
            first = 0 as libc::c_int;
        }
        (*strm).avail_in = n;
        (*strm).next_in = (*state).in_0;
        (*state).x.pos += n as off64_t;
        if gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int) {
            return -(1 as libc::c_int);
        }
        len -= n as off64_t;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_write(
    mut state: gz_statep,
    mut buf: voidpc,
    mut len: z_size_t,
) -> z_size_t {
    let mut put: z_size_t = len;
    if len == 0 as libc::c_int as z_size_t {
        return 0 as libc::c_int as z_size_t;
    }
    if (*state).size == 0 as libc::c_int as libc::c_uint
        && gz_init(state) == -(1 as libc::c_int)
    {
        return 0 as libc::c_int as z_size_t;
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            return 0 as libc::c_int as z_size_t;
        }
    }
    if len < (*state).size as z_size_t {
        loop {
            let mut have: libc::c_uint = 0;
            let mut copy: libc::c_uint = 0;
            if (*state).strm.avail_in == 0 as libc::c_int as uInt {
                (*state).strm.next_in = (*state).in_0;
            }
            have = ((*state).strm.next_in)
                .offset((*state).strm.avail_in as isize)
                .offset_from((*state).in_0) as libc::c_long as libc::c_uint;
            copy = ((*state).size).wrapping_sub(have);
            if copy as z_size_t > len {
                copy = len as libc::c_uint;
            }
            memcpy(
                ((*state).in_0).offset(have as isize) as *mut libc::c_void,
                buf,
                copy as libc::c_ulong,
            );
            (*state)
                .strm
                .avail_in = ((*state).strm.avail_in as libc::c_uint).wrapping_add(copy)
                as uInt as uInt;
            (*state).x.pos += copy as off64_t;
            buf = (buf as *const libc::c_char).offset(copy as isize) as voidpc;
            len = len.wrapping_sub(copy as z_size_t);
            if len != 0 && gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int) {
                return 0 as libc::c_int as z_size_t;
            }
            if !(len != 0) {
                break;
            }
        }
    } else {
        if (*state).strm.avail_in != 0
            && gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int)
        {
            return 0 as libc::c_int as z_size_t;
        }
        (*state).strm.next_in = buf as *const Bytef;
        loop {
            let mut n: libc::c_uint = -(1 as libc::c_int) as libc::c_uint;
            if n as z_size_t > len {
                n = len as libc::c_uint;
            }
            (*state).strm.avail_in = n;
            (*state).x.pos += n as off64_t;
            if gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int) {
                return 0 as libc::c_int as z_size_t;
            }
            len = len.wrapping_sub(n as z_size_t);
            if !(len != 0) {
                break;
            }
        }
    }
    return put;
}
#[no_mangle]
pub unsafe extern "C" fn gzwrite(
    mut file: gzFile,
    mut buf: voidpc,
    mut len: libc::c_uint,
) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return 0 as libc::c_int;
    }
    state = file as gz_statep;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return 0 as libc::c_int;
    }
    if (len as libc::c_int) < 0 as libc::c_int {
        gz_error(
            state,
            -(3 as libc::c_int),
            b"requested length does not fit in int\0" as *const u8 as *const libc::c_char,
        );
        return 0 as libc::c_int;
    }
    return gz_write(state, buf, len as z_size_t) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzfwrite(
    mut buf: voidpc,
    mut size: z_size_t,
    mut nitems: z_size_t,
    mut file: gzFile,
) -> z_size_t {
    let mut len: z_size_t = 0;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return 0 as libc::c_int as z_size_t;
    }
    state = file as gz_statep;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return 0 as libc::c_int as z_size_t;
    }
    len = nitems * size;
    if size != 0 && len / size != nitems {
        gz_error(
            state,
            -(2 as libc::c_int),
            b"request does not fit in a size_t\0" as *const u8 as *const libc::c_char,
        );
        return 0 as libc::c_int as z_size_t;
    }
    return if len != 0 {
        gz_write(state, buf, len) / size
    } else {
        0 as libc::c_int as z_size_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn gzputc(mut file: gzFile, mut c: libc::c_int) -> libc::c_int {
    let mut have: libc::c_uint = 0;
    let mut buf: [libc::c_uchar; 1] = [0; 1];
    let mut state: gz_statep = 0 as *mut gz_state;
    let mut strm: z_streamp = 0 as *mut z_stream;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    strm = &mut (*state).strm;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return -(1 as libc::c_int);
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            return -(1 as libc::c_int);
        }
    }
    if (*state).size != 0 {
        if (*strm).avail_in == 0 as libc::c_int as uInt {
            (*strm).next_in = (*state).in_0;
        }
        have = ((*strm).next_in)
            .offset((*strm).avail_in as isize)
            .offset_from((*state).in_0) as libc::c_long as libc::c_uint;
        if have < (*state).size {
            *((*state).in_0).offset(have as isize) = c as libc::c_uchar;
            (*strm).avail_in = ((*strm).avail_in).wrapping_add(1);
            (*strm).avail_in;
            (*state).x.pos += 1;
            (*state).x.pos;
            return c & 0xff as libc::c_int;
        }
    }
    buf[0 as libc::c_int as usize] = c as libc::c_uchar;
    if gz_write(state, buf.as_mut_ptr() as voidpc, 1 as libc::c_int as z_size_t)
        != 1 as libc::c_int as z_size_t
    {
        return -(1 as libc::c_int);
    }
    return c & 0xff as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzputs(
    mut file: gzFile,
    mut s: *const libc::c_char,
) -> libc::c_int {
    let mut len: z_size_t = 0;
    let mut put: z_size_t = 0;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return -(1 as libc::c_int);
    }
    len = strlen(s);
    if (len as libc::c_int) < 0 as libc::c_int || len as libc::c_uint as z_size_t != len
    {
        gz_error(
            state,
            -(2 as libc::c_int),
            b"string length does not fit in int\0" as *const u8 as *const libc::c_char,
        );
        return -(1 as libc::c_int);
    }
    put = gz_write(state, s as voidpc, len);
    return if put < len { -(1 as libc::c_int) } else { len as libc::c_int };
}
#[no_mangle]
pub unsafe extern "C" fn gzvprintf(
    mut file: gzFile,
    mut format: *const libc::c_char,
    mut va: ::core::ffi::VaList,
) -> libc::c_int {
    let mut len: libc::c_int = 0;
    let mut left: libc::c_uint = 0;
    let mut next: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut state: gz_statep = 0 as *mut gz_state;
    let mut strm: z_streamp = 0 as *mut z_stream;
    if file.is_null() {
        return -(2 as libc::c_int);
    }
    state = file as gz_statep;
    strm = &mut (*state).strm;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return -(2 as libc::c_int);
    }
    if (*state).size == 0 as libc::c_int as libc::c_uint
        && gz_init(state) == -(1 as libc::c_int)
    {
        return (*state).err;
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            return (*state).err;
        }
    }
    if (*strm).avail_in == 0 as libc::c_int as uInt {
        (*strm).next_in = (*state).in_0;
    }
    next = ((*state).in_0)
        .offset(((*strm).next_in).offset_from((*state).in_0) as libc::c_long as isize)
        .offset((*strm).avail_in as isize) as *mut libc::c_char;
    *next
        .offset(
            ((*state).size).wrapping_sub(1 as libc::c_int as libc::c_uint) as isize,
        ) = 0 as libc::c_int as libc::c_char;
    len = vsnprintf(next, (*state).size as libc::c_ulong, format, va.as_va_list());
    if len == 0 as libc::c_int || len as libc::c_uint >= (*state).size
        || *next
            .offset(
                ((*state).size).wrapping_sub(1 as libc::c_int as libc::c_uint) as isize,
            ) as libc::c_int != 0 as libc::c_int
    {
        return 0 as libc::c_int;
    }
    (*strm)
        .avail_in = ((*strm).avail_in as libc::c_uint).wrapping_add(len as libc::c_uint)
        as uInt as uInt;
    (*state).x.pos += len as off64_t;
    if (*strm).avail_in >= (*state).size {
        left = ((*strm).avail_in).wrapping_sub((*state).size);
        (*strm).avail_in = (*state).size;
        if gz_comp(state, 0 as libc::c_int) == -(1 as libc::c_int) {
            return (*state).err;
        }
        memmove(
            (*state).in_0 as *mut libc::c_void,
            ((*state).in_0).offset((*state).size as isize) as *const libc::c_void,
            left as libc::c_ulong,
        );
        (*strm).next_in = (*state).in_0;
        (*strm).avail_in = left;
    }
    return len;
}
#[no_mangle]
pub unsafe extern "C" fn gzprintf(
    mut file: gzFile,
    mut format: *const libc::c_char,
    mut args: ...
) -> libc::c_int {
    let mut va: ::core::ffi::VaListImpl;
    let mut ret: libc::c_int = 0;
    va = args.clone();
    ret = gzvprintf(file, format, va.as_va_list());
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn gzflush(
    mut file: gzFile,
    mut flush: libc::c_int,
) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(2 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int {
        return -(2 as libc::c_int);
    }
    if flush < 0 as libc::c_int || flush > 4 as libc::c_int {
        return -(2 as libc::c_int);
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            return (*state).err;
        }
    }
    gz_comp(state, flush);
    return (*state).err;
}
#[no_mangle]
pub unsafe extern "C" fn gzsetparams(
    mut file: gzFile,
    mut level: libc::c_int,
    mut strategy: libc::c_int,
) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    let mut strm: z_streamp = 0 as *mut z_stream;
    if file.is_null() {
        return -(2 as libc::c_int);
    }
    state = file as gz_statep;
    strm = &mut (*state).strm;
    if (*state).mode != 31153 as libc::c_int || (*state).err != 0 as libc::c_int
        || (*state).direct != 0
    {
        return -(2 as libc::c_int);
    }
    if level == (*state).level && strategy == (*state).strategy {
        return 0 as libc::c_int;
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            return (*state).err;
        }
    }
    if (*state).size != 0 {
        if (*strm).avail_in != 0
            && gz_comp(state, 5 as libc::c_int) == -(1 as libc::c_int)
        {
            return (*state).err;
        }
        deflateParams(strm, level, strategy);
    }
    (*state).level = level;
    (*state).strategy = strategy;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzclose_w(mut file: gzFile) -> libc::c_int {
    let mut ret: libc::c_int = 0 as libc::c_int;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(2 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 31153 as libc::c_int {
        return -(2 as libc::c_int);
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_zero(state, (*state).skip) == -(1 as libc::c_int) {
            ret = (*state).err;
        }
    }
    if gz_comp(state, 4 as libc::c_int) == -(1 as libc::c_int) {
        ret = (*state).err;
    }
    if (*state).size != 0 {
        if (*state).direct == 0 {
            deflateEnd(&mut (*state).strm);
            free((*state).out as *mut libc::c_void);
        }
        free((*state).in_0 as *mut libc::c_void);
    }
    gz_error(state, 0 as libc::c_int, 0 as *const libc::c_char);
    free((*state).path as *mut libc::c_void);
    if close((*state).fd) == -(1 as libc::c_int) {
        ret = -(1 as libc::c_int);
    }
    free(state as *mut libc::c_void);
    return ret;
}
