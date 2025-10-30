use ::libc;
extern "C" {
    pub type internal_state;
    fn close(__fd: libc::c_int) -> libc::c_int;
    fn read(__fd: libc::c_int, __buf: *mut libc::c_void, __nbytes: size_t) -> ssize_t;
    fn inflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn inflateEnd(strm: z_streamp) -> libc::c_int;
    fn inflateReset(strm: z_streamp) -> libc::c_int;
    fn inflateInit2_(
        strm: z_streamp,
        windowBits: libc::c_int,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memchr(
        _: *const libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strerror(_: libc::c_int) -> *mut libc::c_char;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn __errno_location() -> *mut libc::c_int;
    fn gz_error(_: gz_statep, _: libc::c_int, _: *const libc::c_char);
}
pub type size_t = libc::c_ulong;
pub type __off64_t = libc::c_long;
pub type __ssize_t = libc::c_long;
pub type off64_t = __off64_t;
pub type ssize_t = __ssize_t;
pub type z_size_t = size_t;
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
pub type voidpf = *mut libc::c_void;
pub type voidp = *mut libc::c_void;
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
unsafe extern "C" fn gz_load(
    mut state: gz_statep,
    mut buf: *mut libc::c_uchar,
    mut len: libc::c_uint,
    mut have: *mut libc::c_uint,
) -> libc::c_int {
    let mut ret: libc::c_int = 0;
    let mut get: libc::c_uint = 0;
    let mut max: libc::c_uint = (-(1 as libc::c_int) as libc::c_uint >> 2 as libc::c_int)
        .wrapping_add(1 as libc::c_int as libc::c_uint);
    *have = 0 as libc::c_int as libc::c_uint;
    loop {
        get = len.wrapping_sub(*have);
        if get > max {
            get = max;
        }
        ret = read(
            (*state).fd,
            buf.offset(*have as isize) as *mut libc::c_void,
            get as size_t,
        ) as libc::c_int;
        if ret <= 0 as libc::c_int {
            break;
        }
        *have = (*have).wrapping_add(ret as libc::c_uint);
        if !(*have < len) {
            break;
        }
    }
    if ret < 0 as libc::c_int {
        gz_error(state, -(1 as libc::c_int), strerror(*__errno_location()));
        return -(1 as libc::c_int);
    }
    if ret == 0 as libc::c_int {
        (*state).eof = 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_avail(mut state: gz_statep) -> libc::c_int {
    let mut got: libc::c_uint = 0;
    let mut strm: z_streamp = &mut (*state).strm;
    if (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int) {
        return -(1 as libc::c_int);
    }
    if (*state).eof == 0 as libc::c_int {
        if (*strm).avail_in != 0 {
            let mut p: *mut libc::c_uchar = (*state).in_0;
            let mut q: *const libc::c_uchar = (*strm).next_in;
            let mut n: libc::c_uint = (*strm).avail_in;
            loop {
                let fresh0 = q;
                q = q.offset(1);
                let fresh1 = p;
                p = p.offset(1);
                *fresh1 = *fresh0;
                n = n.wrapping_sub(1);
                if !(n != 0) {
                    break;
                }
            }
        }
        if gz_load(
            state,
            ((*state).in_0).offset((*strm).avail_in as isize),
            ((*state).size).wrapping_sub((*strm).avail_in),
            &mut got,
        ) == -(1 as libc::c_int)
        {
            return -(1 as libc::c_int);
        }
        (*strm)
            .avail_in = ((*strm).avail_in as libc::c_uint).wrapping_add(got) as uInt
            as uInt;
        (*strm).next_in = (*state).in_0;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_look(mut state: gz_statep) -> libc::c_int {
    let mut strm: z_streamp = &mut (*state).strm;
    if (*state).size == 0 as libc::c_int as libc::c_uint {
        (*state).in_0 = malloc((*state).want as libc::c_ulong) as *mut libc::c_uchar;
        (*state)
            .out = malloc(((*state).want << 1 as libc::c_int) as libc::c_ulong)
            as *mut libc::c_uchar;
        if ((*state).in_0).is_null() || ((*state).out).is_null() {
            free((*state).out as *mut libc::c_void);
            free((*state).in_0 as *mut libc::c_void);
            gz_error(
                state,
                -(4 as libc::c_int),
                b"out of memory\0" as *const u8 as *const libc::c_char,
            );
            return -(1 as libc::c_int);
        }
        (*state).size = (*state).want;
        (*state).strm.zalloc = None;
        (*state).strm.zfree = None;
        (*state).strm.opaque = 0 as voidpf;
        (*state).strm.avail_in = 0 as libc::c_int as uInt;
        (*state).strm.next_in = 0 as *const Bytef;
        if inflateInit2_(
            &mut (*state).strm,
            15 as libc::c_int + 16 as libc::c_int,
            b"1.3-optipng\0" as *const u8 as *const libc::c_char,
            ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
        ) != 0 as libc::c_int
        {
            free((*state).out as *mut libc::c_void);
            free((*state).in_0 as *mut libc::c_void);
            (*state).size = 0 as libc::c_int as libc::c_uint;
            gz_error(
                state,
                -(4 as libc::c_int),
                b"out of memory\0" as *const u8 as *const libc::c_char,
            );
            return -(1 as libc::c_int);
        }
    }
    if (*strm).avail_in < 2 as libc::c_int as uInt {
        if gz_avail(state) == -(1 as libc::c_int) {
            return -(1 as libc::c_int);
        }
        if (*strm).avail_in == 0 as libc::c_int as uInt {
            return 0 as libc::c_int;
        }
    }
    if (*strm).avail_in > 1 as libc::c_int as uInt
        && *((*strm).next_in).offset(0 as libc::c_int as isize) as libc::c_int
            == 31 as libc::c_int
        && *((*strm).next_in).offset(1 as libc::c_int as isize) as libc::c_int
            == 139 as libc::c_int
    {
        inflateReset(strm);
        (*state).how = 2 as libc::c_int;
        (*state).direct = 0 as libc::c_int;
        return 0 as libc::c_int;
    }
    if (*state).direct == 0 as libc::c_int {
        (*strm).avail_in = 0 as libc::c_int as uInt;
        (*state).eof = 1 as libc::c_int;
        (*state).x.have = 0 as libc::c_int as libc::c_uint;
        return 0 as libc::c_int;
    }
    (*state).x.next = (*state).out;
    memcpy(
        (*state).x.next as *mut libc::c_void,
        (*strm).next_in as *const libc::c_void,
        (*strm).avail_in as libc::c_ulong,
    );
    (*state).x.have = (*strm).avail_in;
    (*strm).avail_in = 0 as libc::c_int as uInt;
    (*state).how = 1 as libc::c_int;
    (*state).direct = 1 as libc::c_int;
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_decomp(mut state: gz_statep) -> libc::c_int {
    let mut ret: libc::c_int = 0 as libc::c_int;
    let mut had: libc::c_uint = 0;
    let mut strm: z_streamp = &mut (*state).strm;
    had = (*strm).avail_out;
    loop {
        if (*strm).avail_in == 0 as libc::c_int as uInt
            && gz_avail(state) == -(1 as libc::c_int)
        {
            return -(1 as libc::c_int);
        }
        if (*strm).avail_in == 0 as libc::c_int as uInt {
            gz_error(
                state,
                -(5 as libc::c_int),
                b"unexpected end of file\0" as *const u8 as *const libc::c_char,
            );
            break;
        } else {
            ret = inflate(strm, 0 as libc::c_int);
            if ret == -(2 as libc::c_int) || ret == 2 as libc::c_int {
                gz_error(
                    state,
                    -(2 as libc::c_int),
                    b"internal error: inflate stream corrupt\0" as *const u8
                        as *const libc::c_char,
                );
                return -(1 as libc::c_int);
            }
            if ret == -(4 as libc::c_int) {
                gz_error(
                    state,
                    -(4 as libc::c_int),
                    b"out of memory\0" as *const u8 as *const libc::c_char,
                );
                return -(1 as libc::c_int);
            }
            if ret == -(3 as libc::c_int) {
                gz_error(
                    state,
                    -(3 as libc::c_int),
                    if ((*strm).msg).is_null() {
                        b"compressed data error\0" as *const u8 as *const libc::c_char
                    } else {
                        (*strm).msg
                    },
                );
                return -(1 as libc::c_int);
            }
            if !((*strm).avail_out != 0 && ret != 1 as libc::c_int) {
                break;
            }
        }
    }
    (*state).x.have = had.wrapping_sub((*strm).avail_out);
    (*state).x.next = ((*strm).next_out).offset(-((*state).x.have as isize));
    if ret == 1 as libc::c_int {
        (*state).how = 0 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_fetch(mut state: gz_statep) -> libc::c_int {
    let mut strm: z_streamp = &mut (*state).strm;
    loop {
        match (*state).how {
            0 => {
                if gz_look(state) == -(1 as libc::c_int) {
                    return -(1 as libc::c_int);
                }
                if (*state).how == 0 as libc::c_int {
                    return 0 as libc::c_int;
                }
            }
            1 => {
                if gz_load(
                    state,
                    (*state).out,
                    (*state).size << 1 as libc::c_int,
                    &mut (*state).x.have,
                ) == -(1 as libc::c_int)
                {
                    return -(1 as libc::c_int);
                }
                (*state).x.next = (*state).out;
                return 0 as libc::c_int;
            }
            2 => {
                (*strm).avail_out = (*state).size << 1 as libc::c_int;
                (*strm).next_out = (*state).out;
                if gz_decomp(state) == -(1 as libc::c_int) {
                    return -(1 as libc::c_int);
                }
            }
            _ => {}
        }
        if !((*state).x.have == 0 as libc::c_int as libc::c_uint
            && ((*state).eof == 0 || (*strm).avail_in != 0))
        {
            break;
        }
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_skip(mut state: gz_statep, mut len: off64_t) -> libc::c_int {
    let mut n: libc::c_uint = 0;
    while len != 0 {
        if (*state).x.have != 0 {
            n = if ::core::mem::size_of::<libc::c_int>() as libc::c_ulong
                == ::core::mem::size_of::<off64_t>() as libc::c_ulong
                && (*state).x.have > 2147483647 as libc::c_int as libc::c_uint
                || (*state).x.have as off64_t > len
            {
                len as libc::c_uint
            } else {
                (*state).x.have
            };
            (*state).x.have = ((*state).x.have).wrapping_sub(n);
            (*state).x.next = ((*state).x.next).offset(n as isize);
            (*state).x.pos += n as off64_t;
            len -= n as off64_t;
        } else {
            if (*state).eof != 0 && (*state).strm.avail_in == 0 as libc::c_int as uInt {
                break;
            }
            if gz_fetch(state) == -(1 as libc::c_int) {
                return -(1 as libc::c_int);
            }
        }
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn gz_read(
    mut state: gz_statep,
    mut buf: voidp,
    mut len: z_size_t,
) -> z_size_t {
    let mut got: z_size_t = 0;
    let mut n: libc::c_uint = 0;
    if len == 0 as libc::c_int as z_size_t {
        return 0 as libc::c_int as z_size_t;
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_skip(state, (*state).skip) == -(1 as libc::c_int) {
            return 0 as libc::c_int as z_size_t;
        }
    }
    got = 0 as libc::c_int as z_size_t;
    let mut current_block_34: u64;
    loop {
        n = -(1 as libc::c_int) as libc::c_uint;
        if n as z_size_t > len {
            n = len as libc::c_uint;
        }
        if (*state).x.have != 0 {
            if (*state).x.have < n {
                n = (*state).x.have;
            }
            memcpy(buf, (*state).x.next as *const libc::c_void, n as libc::c_ulong);
            (*state).x.next = ((*state).x.next).offset(n as isize);
            (*state).x.have = ((*state).x.have).wrapping_sub(n);
            current_block_34 = 13550086250199790493;
        } else if (*state).eof != 0 && (*state).strm.avail_in == 0 as libc::c_int as uInt
        {
            (*state).past = 1 as libc::c_int;
            break;
        } else if (*state).how == 0 as libc::c_int
            || n < (*state).size << 1 as libc::c_int
        {
            if gz_fetch(state) == -(1 as libc::c_int) {
                return 0 as libc::c_int as z_size_t;
            }
            current_block_34 = 4906268039856690917;
        } else {
            if (*state).how == 1 as libc::c_int {
                if gz_load(state, buf as *mut libc::c_uchar, n, &mut n)
                    == -(1 as libc::c_int)
                {
                    return 0 as libc::c_int as z_size_t;
                }
            } else {
                (*state).strm.avail_out = n;
                (*state).strm.next_out = buf as *mut libc::c_uchar;
                if gz_decomp(state) == -(1 as libc::c_int) {
                    return 0 as libc::c_int as z_size_t;
                }
                n = (*state).x.have;
                (*state).x.have = 0 as libc::c_int as libc::c_uint;
            }
            current_block_34 = 13550086250199790493;
        }
        match current_block_34 {
            13550086250199790493 => {
                len = len.wrapping_sub(n as z_size_t);
                buf = (buf as *mut libc::c_char).offset(n as isize) as voidp;
                got = got.wrapping_add(n as z_size_t);
                (*state).x.pos += n as off64_t;
            }
            _ => {}
        }
        if !(len != 0) {
            break;
        }
    }
    return got;
}
#[no_mangle]
pub unsafe extern "C" fn gzread(
    mut file: gzFile,
    mut buf: voidp,
    mut len: libc::c_uint,
) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int
        || (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int)
    {
        return -(1 as libc::c_int);
    }
    if (len as libc::c_int) < 0 as libc::c_int {
        gz_error(
            state,
            -(2 as libc::c_int),
            b"request does not fit in an int\0" as *const u8 as *const libc::c_char,
        );
        return -(1 as libc::c_int);
    }
    len = gz_read(state, buf, len as z_size_t) as libc::c_uint;
    if len == 0 as libc::c_int as libc::c_uint && (*state).err != 0 as libc::c_int
        && (*state).err != -(5 as libc::c_int)
    {
        return -(1 as libc::c_int);
    }
    return len as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzfread(
    mut buf: voidp,
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
    if (*state).mode != 7247 as libc::c_int
        || (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int)
    {
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
        gz_read(state, buf, len) / size
    } else {
        0 as libc::c_int as z_size_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn gzgetc(mut file: gzFile) -> libc::c_int {
    let mut buf: [libc::c_uchar; 1] = [0; 1];
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int
        || (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int)
    {
        return -(1 as libc::c_int);
    }
    if (*state).x.have != 0 {
        (*state).x.have = ((*state).x.have).wrapping_sub(1);
        (*state).x.have;
        (*state).x.pos += 1;
        (*state).x.pos;
        let fresh2 = (*state).x.next;
        (*state).x.next = ((*state).x.next).offset(1);
        return *fresh2 as libc::c_int;
    }
    return if gz_read(state, buf.as_mut_ptr() as voidp, 1 as libc::c_int as z_size_t)
        < 1 as libc::c_int as z_size_t
    {
        -(1 as libc::c_int)
    } else {
        buf[0 as libc::c_int as usize] as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn gzgetc_(mut file: gzFile) -> libc::c_int {
    return gzgetc(file);
}
#[no_mangle]
pub unsafe extern "C" fn gzungetc(mut c: libc::c_int, mut file: gzFile) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode == 7247 as libc::c_int && (*state).how == 0 as libc::c_int
        && (*state).x.have == 0 as libc::c_int as libc::c_uint
    {
        gz_look(state);
    }
    if (*state).mode != 7247 as libc::c_int
        || (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int)
    {
        return -(1 as libc::c_int);
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_skip(state, (*state).skip) == -(1 as libc::c_int) {
            return -(1 as libc::c_int);
        }
    }
    if c < 0 as libc::c_int {
        return -(1 as libc::c_int);
    }
    if (*state).x.have == 0 as libc::c_int as libc::c_uint {
        (*state).x.have = 1 as libc::c_int as libc::c_uint;
        (*state)
            .x
            .next = ((*state).out)
            .offset(((*state).size << 1 as libc::c_int) as isize)
            .offset(-(1 as libc::c_int as isize));
        *((*state).x.next).offset(0 as libc::c_int as isize) = c as libc::c_uchar;
        (*state).x.pos -= 1;
        (*state).x.pos;
        (*state).past = 0 as libc::c_int;
        return c;
    }
    if (*state).x.have == (*state).size << 1 as libc::c_int {
        gz_error(
            state,
            -(3 as libc::c_int),
            b"out of room to push characters\0" as *const u8 as *const libc::c_char,
        );
        return -(1 as libc::c_int);
    }
    if (*state).x.next == (*state).out {
        let mut src: *mut libc::c_uchar = ((*state).out)
            .offset((*state).x.have as isize);
        let mut dest: *mut libc::c_uchar = ((*state).out)
            .offset(((*state).size << 1 as libc::c_int) as isize);
        while src > (*state).out {
            src = src.offset(-1);
            dest = dest.offset(-1);
            *dest = *src;
        }
        (*state).x.next = dest;
    }
    (*state).x.have = ((*state).x.have).wrapping_add(1);
    (*state).x.have;
    (*state).x.next = ((*state).x.next).offset(-1);
    (*state).x.next;
    *((*state).x.next).offset(0 as libc::c_int as isize) = c as libc::c_uchar;
    (*state).x.pos -= 1;
    (*state).x.pos;
    (*state).past = 0 as libc::c_int;
    return c;
}
#[no_mangle]
pub unsafe extern "C" fn gzgets(
    mut file: gzFile,
    mut buf: *mut libc::c_char,
    mut len: libc::c_int,
) -> *mut libc::c_char {
    let mut left: libc::c_uint = 0;
    let mut n: libc::c_uint = 0;
    let mut str: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut eol: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() || buf.is_null() || len < 1 as libc::c_int {
        return 0 as *mut libc::c_char;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int
        || (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int)
    {
        return 0 as *mut libc::c_char;
    }
    if (*state).seek != 0 {
        (*state).seek = 0 as libc::c_int;
        if gz_skip(state, (*state).skip) == -(1 as libc::c_int) {
            return 0 as *mut libc::c_char;
        }
    }
    str = buf;
    left = (len as libc::c_uint).wrapping_sub(1 as libc::c_int as libc::c_uint);
    if left != 0 {
        loop {
            if (*state).x.have == 0 as libc::c_int as libc::c_uint
                && gz_fetch(state) == -(1 as libc::c_int)
            {
                return 0 as *mut libc::c_char;
            }
            if (*state).x.have == 0 as libc::c_int as libc::c_uint {
                (*state).past = 1 as libc::c_int;
                break;
            } else {
                n = if (*state).x.have > left { left } else { (*state).x.have };
                eol = memchr(
                    (*state).x.next as *const libc::c_void,
                    '\n' as i32,
                    n as libc::c_ulong,
                ) as *mut libc::c_uchar;
                if !eol.is_null() {
                    n = (eol.offset_from((*state).x.next) as libc::c_long
                        as libc::c_uint)
                        .wrapping_add(1 as libc::c_int as libc::c_uint);
                }
                memcpy(
                    buf as *mut libc::c_void,
                    (*state).x.next as *const libc::c_void,
                    n as libc::c_ulong,
                );
                (*state).x.have = ((*state).x.have).wrapping_sub(n);
                (*state).x.next = ((*state).x.next).offset(n as isize);
                (*state).x.pos += n as off64_t;
                left = left.wrapping_sub(n);
                buf = buf.offset(n as isize);
                if !(left != 0 && eol.is_null()) {
                    break;
                }
            }
        }
    }
    if buf == str {
        return 0 as *mut libc::c_char;
    }
    *buf.offset(0 as libc::c_int as isize) = 0 as libc::c_int as libc::c_char;
    return str;
}
#[no_mangle]
pub unsafe extern "C" fn gzdirect(mut file: gzFile) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return 0 as libc::c_int;
    }
    state = file as gz_statep;
    if (*state).mode == 7247 as libc::c_int && (*state).how == 0 as libc::c_int
        && (*state).x.have == 0 as libc::c_int as libc::c_uint
    {
        gz_look(state);
    }
    return (*state).direct;
}
#[no_mangle]
pub unsafe extern "C" fn gzclose_r(mut file: gzFile) -> libc::c_int {
    let mut ret: libc::c_int = 0;
    let mut err: libc::c_int = 0;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(2 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int {
        return -(2 as libc::c_int);
    }
    if (*state).size != 0 {
        inflateEnd(&mut (*state).strm);
        free((*state).out as *mut libc::c_void);
        free((*state).in_0 as *mut libc::c_void);
    }
    err = if (*state).err == -(5 as libc::c_int) {
        -(5 as libc::c_int)
    } else {
        0 as libc::c_int
    };
    gz_error(state, 0 as libc::c_int, 0 as *const libc::c_char);
    free((*state).path as *mut libc::c_void);
    ret = close((*state).fd);
    free(state as *mut libc::c_void);
    return if ret != 0 { -(1 as libc::c_int) } else { err };
}
