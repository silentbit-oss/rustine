use ::libc;
extern "C" {
    pub type internal_state;
    fn snprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
    fn lseek64(
        __fd: libc::c_int,
        __offset: __off64_t,
        __whence: libc::c_int,
    ) -> __off64_t;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn open(__file: *const libc::c_char, __oflag: libc::c_int, _: ...) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type off_t = __off_t;
pub type off64_t = __off64_t;
pub type z_size_t = size_t;
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
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
unsafe extern "C" fn gz_reset(mut state: gz_statep) {
    (*state).x.have = 0 as libc::c_int as libc::c_uint;
    if (*state).mode == 7247 as libc::c_int {
        (*state).eof = 0 as libc::c_int;
        (*state).past = 0 as libc::c_int;
        (*state).how = 0 as libc::c_int;
    } else {
        (*state).reset = 0 as libc::c_int;
    }
    (*state).seek = 0 as libc::c_int;
    gz_error(state, 0 as libc::c_int, 0 as *const libc::c_char);
    (*state).x.pos = 0 as libc::c_int as off64_t;
    (*state).strm.avail_in = 0 as libc::c_int as uInt;
}
unsafe extern "C" fn gz_open(
    mut path: *const libc::c_void,
    mut fd: libc::c_int,
    mut mode: *const libc::c_char,
) -> gzFile {
    let mut state: gz_statep = 0 as *mut gz_state;
    let mut len: z_size_t = 0;
    let mut oflag: libc::c_int = 0;
    let mut cloexec: libc::c_int = 0 as libc::c_int;
    let mut exclusive: libc::c_int = 0 as libc::c_int;
    if path.is_null() {
        return 0 as gzFile;
    }
    state = malloc(::core::mem::size_of::<gz_state>() as libc::c_ulong) as gz_statep;
    if state.is_null() {
        return 0 as gzFile;
    }
    (*state).size = 0 as libc::c_int as libc::c_uint;
    (*state).want = 8192 as libc::c_int as libc::c_uint;
    (*state).msg = 0 as *mut libc::c_char;
    (*state).mode = 0 as libc::c_int;
    (*state).level = -(1 as libc::c_int);
    (*state).strategy = 0 as libc::c_int;
    (*state).direct = 0 as libc::c_int;
    while *mode != 0 {
        if *mode as libc::c_int >= '0' as i32 && *mode as libc::c_int <= '9' as i32 {
            (*state).level = *mode as libc::c_int - '0' as i32;
        } else {
            match *mode as libc::c_int {
                114 => {
                    (*state).mode = 7247 as libc::c_int;
                }
                43 => {
                    free(state as *mut libc::c_void);
                    return 0 as gzFile;
                }
                98 => {}
                101 => {
                    cloexec = 1 as libc::c_int;
                }
                120 => {
                    exclusive = 1 as libc::c_int;
                }
                102 => {
                    (*state).strategy = 1 as libc::c_int;
                }
                104 => {
                    (*state).strategy = 2 as libc::c_int;
                }
                82 => {
                    (*state).strategy = 3 as libc::c_int;
                }
                70 => {
                    (*state).strategy = 4 as libc::c_int;
                }
                84 => {
                    (*state).direct = 1 as libc::c_int;
                }
                _ => {}
            }
        }
        mode = mode.offset(1);
        mode;
    }
    if (*state).mode == 0 as libc::c_int {
        free(state as *mut libc::c_void);
        return 0 as gzFile;
    }
    if (*state).mode == 7247 as libc::c_int {
        if (*state).direct != 0 {
            free(state as *mut libc::c_void);
            return 0 as gzFile;
        }
        (*state).direct = 1 as libc::c_int;
    }
    len = strlen(path as *const libc::c_char);
    (*state)
        .path = malloc(len.wrapping_add(1 as libc::c_int as z_size_t))
        as *mut libc::c_char;
    if ((*state).path).is_null() {
        free(state as *mut libc::c_void);
        return 0 as gzFile;
    }
    snprintf(
        (*state).path,
        len.wrapping_add(1 as libc::c_int as z_size_t),
        b"%s\0" as *const u8 as *const libc::c_char,
        path as *const libc::c_char,
    );
    oflag = 0 as libc::c_int
        | (if cloexec != 0 { 0o2000000 as libc::c_int } else { 0 as libc::c_int })
        | (if (*state).mode == 7247 as libc::c_int {
            0 as libc::c_int
        } else {
            0o1 as libc::c_int | 0o100 as libc::c_int
                | (if exclusive != 0 { 0o200 as libc::c_int } else { 0 as libc::c_int })
                | (if (*state).mode == 31153 as libc::c_int {
                    0o1000 as libc::c_int
                } else {
                    0o2000 as libc::c_int
                })
        });
    (*state)
        .fd = if fd > -(1 as libc::c_int) {
        fd
    } else {
        open(path as *const libc::c_char, oflag, 0o666 as libc::c_int)
    };
    if (*state).fd == -(1 as libc::c_int) {
        free((*state).path as *mut libc::c_void);
        free(state as *mut libc::c_void);
        return 0 as gzFile;
    }
    if (*state).mode == 1 as libc::c_int {
        lseek64((*state).fd, 0 as libc::c_int as __off64_t, 2 as libc::c_int);
        (*state).mode = 31153 as libc::c_int;
    }
    if (*state).mode == 7247 as libc::c_int {
        (*state)
            .start = lseek64(
            (*state).fd,
            0 as libc::c_int as __off64_t,
            1 as libc::c_int,
        );
        if (*state).start == -(1 as libc::c_int) as off64_t {
            (*state).start = 0 as libc::c_int as off64_t;
        }
    }
    gz_reset(state);
    return state as gzFile;
}
#[no_mangle]
pub unsafe extern "C" fn gzopen(
    mut path: *const libc::c_char,
    mut mode: *const libc::c_char,
) -> gzFile {
    return gz_open(path as *const libc::c_void, -(1 as libc::c_int), mode);
}
#[no_mangle]
pub unsafe extern "C" fn gzopen64(
    mut path: *const libc::c_char,
    mut mode: *const libc::c_char,
) -> gzFile {
    return gz_open(path as *const libc::c_void, -(1 as libc::c_int), mode);
}
#[no_mangle]
pub unsafe extern "C" fn gzdopen(
    mut fd: libc::c_int,
    mut mode: *const libc::c_char,
) -> gzFile {
    let mut path: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut gz: gzFile = 0 as *mut gzFile_s;
    if fd == -(1 as libc::c_int)
        || {
            path = malloc(
                (7 as libc::c_int as libc::c_ulong)
                    .wrapping_add(
                        (3 as libc::c_int as libc::c_ulong)
                            .wrapping_mul(
                                ::core::mem::size_of::<libc::c_int>() as libc::c_ulong,
                            ),
                    ),
            ) as *mut libc::c_char;
            path.is_null()
        }
    {
        return 0 as gzFile;
    }
    snprintf(
        path,
        (7 as libc::c_int as libc::c_ulong)
            .wrapping_add(
                (3 as libc::c_int as libc::c_ulong)
                    .wrapping_mul(::core::mem::size_of::<libc::c_int>() as libc::c_ulong),
            ),
        b"<fd:%d>\0" as *const u8 as *const libc::c_char,
        fd,
    );
    gz = gz_open(path as *const libc::c_void, fd, mode);
    free(path as *mut libc::c_void);
    return gz;
}
#[no_mangle]
pub unsafe extern "C" fn gzbuffer(
    mut file: gzFile,
    mut size: libc::c_uint,
) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int);
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return -(1 as libc::c_int);
    }
    if (*state).size != 0 as libc::c_int as libc::c_uint {
        return -(1 as libc::c_int);
    }
    if (size << 1 as libc::c_int) < size {
        return -(1 as libc::c_int);
    }
    if size < 8 as libc::c_int as libc::c_uint {
        size = 8 as libc::c_int as libc::c_uint;
    }
    (*state).want = size;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzrewind(mut file: gzFile) -> libc::c_int {
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
    if lseek64((*state).fd, (*state).start, 0 as libc::c_int)
        == -(1 as libc::c_int) as __off64_t
    {
        return -(1 as libc::c_int);
    }
    gz_reset(state);
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn gzseek64(
    mut file: gzFile,
    mut offset: off64_t,
    mut whence: libc::c_int,
) -> off64_t {
    let mut n: libc::c_uint = 0;
    let mut ret: off64_t = 0;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int) as off64_t;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return -(1 as libc::c_int) as off64_t;
    }
    if (*state).err != 0 as libc::c_int && (*state).err != -(5 as libc::c_int) {
        return -(1 as libc::c_int) as off64_t;
    }
    if whence != 0 as libc::c_int && whence != 1 as libc::c_int {
        return -(1 as libc::c_int) as off64_t;
    }
    if whence == 0 as libc::c_int {
        offset -= (*state).x.pos;
    } else if (*state).seek != 0 {
        offset += (*state).skip;
    }
    (*state).seek = 0 as libc::c_int;
    if (*state).mode == 7247 as libc::c_int && (*state).how == 1 as libc::c_int
        && (*state).x.pos + offset >= 0 as libc::c_int as off64_t
    {
        ret = lseek64(
            (*state).fd,
            offset - (*state).x.have as off64_t,
            1 as libc::c_int,
        );
        if ret == -(1 as libc::c_int) as off64_t {
            return -(1 as libc::c_int) as off64_t;
        }
        (*state).x.have = 0 as libc::c_int as libc::c_uint;
        (*state).eof = 0 as libc::c_int;
        (*state).past = 0 as libc::c_int;
        (*state).seek = 0 as libc::c_int;
        gz_error(state, 0 as libc::c_int, 0 as *const libc::c_char);
        (*state).strm.avail_in = 0 as libc::c_int as uInt;
        (*state).x.pos += offset;
        return (*state).x.pos;
    }
    if offset < 0 as libc::c_int as off64_t {
        if (*state).mode != 7247 as libc::c_int {
            return -(1 as libc::c_int) as off64_t;
        }
        offset += (*state).x.pos;
        if offset < 0 as libc::c_int as off64_t {
            return -(1 as libc::c_int) as off64_t;
        }
        if gzrewind(file) == -(1 as libc::c_int) {
            return -(1 as libc::c_int) as off64_t;
        }
    }
    if (*state).mode == 7247 as libc::c_int {
        n = if ::core::mem::size_of::<libc::c_int>() as libc::c_ulong
            == ::core::mem::size_of::<off64_t>() as libc::c_ulong
            && (*state).x.have > 2147483647 as libc::c_int as libc::c_uint
            || (*state).x.have as off64_t > offset
        {
            offset as libc::c_uint
        } else {
            (*state).x.have
        };
        (*state).x.have = ((*state).x.have).wrapping_sub(n);
        (*state).x.next = ((*state).x.next).offset(n as isize);
        (*state).x.pos += n as off64_t;
        offset -= n as off64_t;
    }
    if offset != 0 {
        (*state).seek = 1 as libc::c_int;
        (*state).skip = offset;
    }
    return (*state).x.pos + offset;
}
#[no_mangle]
pub unsafe extern "C" fn gzseek(
    mut file: gzFile,
    mut offset: off_t,
    mut whence: libc::c_int,
) -> off_t {
    let mut ret: off64_t = 0;
    ret = gzseek64(file, offset, whence);
    return if ret == ret { ret } else { -(1 as libc::c_int) as off_t };
}
#[no_mangle]
pub unsafe extern "C" fn gztell64(mut file: gzFile) -> off64_t {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int) as off64_t;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return -(1 as libc::c_int) as off64_t;
    }
    return (*state).x.pos
        + (if (*state).seek != 0 { (*state).skip } else { 0 as libc::c_int as off64_t });
}
#[no_mangle]
pub unsafe extern "C" fn gztell(mut file: gzFile) -> off_t {
    let mut ret: off64_t = 0;
    ret = gztell64(file);
    return if ret == ret { ret } else { -(1 as libc::c_int) as off_t };
}
#[no_mangle]
pub unsafe extern "C" fn gzoffset64(mut file: gzFile) -> off64_t {
    let mut offset: off64_t = 0;
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return -(1 as libc::c_int) as off64_t;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return -(1 as libc::c_int) as off64_t;
    }
    offset = lseek64((*state).fd, 0 as libc::c_int as __off64_t, 1 as libc::c_int);
    if offset == -(1 as libc::c_int) as off64_t {
        return -(1 as libc::c_int) as off64_t;
    }
    if (*state).mode == 7247 as libc::c_int {
        offset -= (*state).strm.avail_in as off64_t;
    }
    return offset;
}
#[no_mangle]
pub unsafe extern "C" fn gzoffset(mut file: gzFile) -> off_t {
    let mut ret: off64_t = 0;
    ret = gzoffset64(file);
    return if ret == ret { ret } else { -(1 as libc::c_int) as off_t };
}
#[no_mangle]
pub unsafe extern "C" fn gzeof(mut file: gzFile) -> libc::c_int {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return 0 as libc::c_int;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return 0 as libc::c_int;
    }
    return if (*state).mode == 7247 as libc::c_int {
        (*state).past
    } else {
        0 as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn gzerror(
    mut file: gzFile,
    mut errnum: *mut libc::c_int,
) -> *const libc::c_char {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return 0 as *const libc::c_char;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return 0 as *const libc::c_char;
    }
    if !errnum.is_null() {
        *errnum = (*state).err;
    }
    return if (*state).err == -(4 as libc::c_int) {
        b"out of memory\0" as *const u8 as *const libc::c_char
    } else if ((*state).msg).is_null() {
        b"\0" as *const u8 as *const libc::c_char
    } else {
        (*state).msg as *const libc::c_char
    };
}
#[no_mangle]
pub unsafe extern "C" fn gzclearerr(mut file: gzFile) {
    let mut state: gz_statep = 0 as *mut gz_state;
    if file.is_null() {
        return;
    }
    state = file as gz_statep;
    if (*state).mode != 7247 as libc::c_int && (*state).mode != 31153 as libc::c_int {
        return;
    }
    if (*state).mode == 7247 as libc::c_int {
        (*state).eof = 0 as libc::c_int;
        (*state).past = 0 as libc::c_int;
    }
    gz_error(state, 0 as libc::c_int, 0 as *const libc::c_char);
}
#[no_mangle]
pub unsafe extern "C" fn gz_error(
    mut state: gz_statep,
    mut err: libc::c_int,
    mut msg: *const libc::c_char,
) {
    if !((*state).msg).is_null() {
        if (*state).err != -(4 as libc::c_int) {
            free((*state).msg as *mut libc::c_void);
        }
        (*state).msg = 0 as *mut libc::c_char;
    }
    if err != 0 as libc::c_int && err != -(5 as libc::c_int) {
        (*state).x.have = 0 as libc::c_int as libc::c_uint;
    }
    (*state).err = err;
    if msg.is_null() {
        return;
    }
    if err == -(4 as libc::c_int) {
        return;
    }
    (*state)
        .msg = malloc(
        (strlen((*state).path))
            .wrapping_add(strlen(msg))
            .wrapping_add(3 as libc::c_int as libc::c_ulong),
    ) as *mut libc::c_char;
    if ((*state).msg).is_null() {
        (*state).err = -(4 as libc::c_int);
        return;
    }
    snprintf(
        (*state).msg,
        (strlen((*state).path))
            .wrapping_add(strlen(msg))
            .wrapping_add(3 as libc::c_int as libc::c_ulong),
        b"%s%s%s\0" as *const u8 as *const libc::c_char,
        (*state).path,
        b": \0" as *const u8 as *const libc::c_char,
        msg,
    );
}
