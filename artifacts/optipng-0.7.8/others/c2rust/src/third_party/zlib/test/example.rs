use ::libc;
extern "C" {
    pub type internal_state;
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn zlibVersion() -> *const libc::c_char;
    fn deflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn deflateEnd(strm: z_streamp) -> libc::c_int;
    fn inflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn inflateEnd(strm: z_streamp) -> libc::c_int;
    fn deflateSetDictionary(
        strm: z_streamp,
        dictionary_0: *const Bytef,
        dictLength: uInt,
    ) -> libc::c_int;
    fn deflateParams(
        strm: z_streamp,
        level: libc::c_int,
        strategy: libc::c_int,
    ) -> libc::c_int;
    fn inflateSetDictionary(
        strm: z_streamp,
        dictionary_0: *const Bytef,
        dictLength: uInt,
    ) -> libc::c_int;
    fn inflateSync(strm: z_streamp) -> libc::c_int;
    fn zlibCompileFlags() -> uLong;
    fn compress(
        dest: *mut Bytef,
        destLen: *mut uLongf,
        source: *const Bytef,
        sourceLen: uLong,
    ) -> libc::c_int;
    fn uncompress(
        dest: *mut Bytef,
        destLen: *mut uLongf,
        source: *const Bytef,
        sourceLen: uLong,
    ) -> libc::c_int;
    fn deflateInit_(
        strm: z_streamp,
        level: libc::c_int,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
    fn inflateInit_(
        strm: z_streamp,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn strcpy(_: *mut libc::c_char, _: *const libc::c_char) -> *mut libc::c_char;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn exit(_: libc::c_int) -> !;
}
pub type size_t = libc::c_ulong;
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
pub type uLongf = uLong;
pub type voidpf = *mut libc::c_void;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
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
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
static mut hello: [libc::c_char; 14] = unsafe {
    *::core::mem::transmute::<&[u8; 14], &[libc::c_char; 14]>(b"hello, hello!\0")
};
static mut dictionary: [libc::c_char; 6] = unsafe {
    *::core::mem::transmute::<&[u8; 6], &[libc::c_char; 6]>(b"hello\0")
};
static mut dictId: uLong = 0;
static mut zalloc: alloc_func = None;
static mut zfree: free_func = None;
#[no_mangle]
pub unsafe extern "C" fn test_compress(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut err: libc::c_int = 0;
    let mut len: uLong = (strlen(hello.as_ptr()))
        .wrapping_add(1 as libc::c_int as uLong);
    err = compress(compr, &mut comprLen, hello.as_ptr() as *const Bytef, len);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"compress\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    strcpy(
        uncompr as *mut libc::c_char,
        b"garbage\0" as *const u8 as *const libc::c_char,
    );
    err = uncompress(uncompr, &mut uncomprLen, compr, comprLen);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"uncompress\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    if strcmp(uncompr as *mut libc::c_char, hello.as_ptr()) != 0 {
        fprintf(stderr, b"bad uncompress\n\0" as *const u8 as *const libc::c_char);
        exit(1 as libc::c_int);
    } else {
        printf(
            b"uncompress(): %s\n\0" as *const u8 as *const libc::c_char,
            uncompr as *mut libc::c_char,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn test_gzio(
    mut fname: *const libc::c_char,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    fprintf(
        stderr,
        b"NO_GZCOMPRESS -- gz* functions cannot compress\n\0" as *const u8
            as *const libc::c_char,
    );
}
#[no_mangle]
pub unsafe extern "C" fn test_deflate(mut compr: *mut Byte, mut comprLen: uLong) {
    let mut c_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    let mut err: libc::c_int = 0;
    let mut len: uLong = (strlen(hello.as_ptr()))
        .wrapping_add(1 as libc::c_int as uLong);
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err = deflateInit_(
        &mut c_stream,
        -(1 as libc::c_int),
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    c_stream.next_in = hello.as_ptr() as *const libc::c_uchar;
    c_stream.next_out = compr;
    while c_stream.total_in != len && c_stream.total_out < comprLen {
        c_stream.avail_out = 1 as libc::c_int as uInt;
        c_stream.avail_in = c_stream.avail_out;
        err = deflate(&mut c_stream, 0 as libc::c_int);
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"deflate\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    loop {
        c_stream.avail_out = 1 as libc::c_int as uInt;
        err = deflate(&mut c_stream, 4 as libc::c_int);
        if err == 1 as libc::c_int {
            break;
        }
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"deflate\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
}
#[no_mangle]
pub unsafe extern "C" fn test_inflate(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut err: libc::c_int = 0;
    let mut d_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    strcpy(
        uncompr as *mut libc::c_char,
        b"garbage\0" as *const u8 as *const libc::c_char,
    );
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = 0 as libc::c_int as uInt;
    d_stream.next_out = uncompr;
    err = inflateInit_(
        &mut d_stream,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    while d_stream.total_out < uncomprLen && d_stream.total_in < comprLen {
        d_stream.avail_out = 1 as libc::c_int as uInt;
        d_stream.avail_in = d_stream.avail_out;
        err = inflate(&mut d_stream, 0 as libc::c_int);
        if err == 1 as libc::c_int {
            break;
        }
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"inflate\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    if strcmp(uncompr as *mut libc::c_char, hello.as_ptr()) != 0 {
        fprintf(stderr, b"bad inflate\n\0" as *const u8 as *const libc::c_char);
        exit(1 as libc::c_int);
    } else {
        printf(
            b"inflate(): %s\n\0" as *const u8 as *const libc::c_char,
            uncompr as *mut libc::c_char,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn test_large_deflate(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut c_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    let mut err: libc::c_int = 0;
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err = deflateInit_(
        &mut c_stream,
        1 as libc::c_int,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    c_stream.next_out = compr;
    c_stream.avail_out = comprLen as uInt;
    c_stream.next_in = uncompr;
    c_stream.avail_in = uncomprLen as uInt;
    err = deflate(&mut c_stream, 0 as libc::c_int);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflate\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    if c_stream.avail_in != 0 as libc::c_int as uInt {
        fprintf(stderr, b"deflate not greedy\n\0" as *const u8 as *const libc::c_char);
        exit(1 as libc::c_int);
    }
    deflateParams(&mut c_stream, 0 as libc::c_int, 0 as libc::c_int);
    c_stream.next_in = compr;
    c_stream.avail_in = uncomprLen as uInt / 2 as libc::c_int as uInt;
    err = deflate(&mut c_stream, 0 as libc::c_int);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflate\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    deflateParams(&mut c_stream, 9 as libc::c_int, 1 as libc::c_int);
    c_stream.next_in = uncompr;
    c_stream.avail_in = uncomprLen as uInt;
    err = deflate(&mut c_stream, 0 as libc::c_int);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflate\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    err = deflate(&mut c_stream, 4 as libc::c_int);
    if err != 1 as libc::c_int {
        fprintf(
            stderr,
            b"deflate should report Z_STREAM_END\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
}
#[no_mangle]
pub unsafe extern "C" fn test_large_inflate(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut err: libc::c_int = 0;
    let mut d_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    strcpy(
        uncompr as *mut libc::c_char,
        b"garbage\0" as *const u8 as *const libc::c_char,
    );
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = comprLen as uInt;
    err = inflateInit_(
        &mut d_stream,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    loop {
        d_stream.next_out = uncompr;
        d_stream.avail_out = uncomprLen as uInt;
        err = inflate(&mut d_stream, 0 as libc::c_int);
        if err == 1 as libc::c_int {
            break;
        }
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"large inflate\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    if d_stream.total_out
        != (2 as libc::c_int as uLong * uncomprLen)
            .wrapping_add(uncomprLen / 2 as libc::c_int as uLong)
    {
        fprintf(
            stderr,
            b"bad large inflate: %ld\n\0" as *const u8 as *const libc::c_char,
            d_stream.total_out,
        );
        exit(1 as libc::c_int);
    } else {
        printf(b"large_inflate(): OK\n\0" as *const u8 as *const libc::c_char);
    };
}
#[no_mangle]
pub unsafe extern "C" fn test_flush(mut compr: *mut Byte, mut comprLen: *mut uLong) {
    let mut c_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    let mut err: libc::c_int = 0;
    let mut len: uInt = (strlen(hello.as_ptr()) as uInt)
        .wrapping_add(1 as libc::c_int as uInt);
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err = deflateInit_(
        &mut c_stream,
        -(1 as libc::c_int),
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    c_stream.next_in = hello.as_ptr() as *const libc::c_uchar;
    c_stream.next_out = compr;
    c_stream.avail_in = 3 as libc::c_int as uInt;
    c_stream.avail_out = *comprLen as uInt;
    err = deflate(&mut c_stream, 3 as libc::c_int);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflate\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    let ref mut fresh0 = *compr.offset(3 as libc::c_int as isize);
    *fresh0 = (*fresh0).wrapping_add(1);
    *fresh0;
    c_stream.avail_in = len.wrapping_sub(3 as libc::c_int as uInt);
    err = deflate(&mut c_stream, 4 as libc::c_int);
    if err != 1 as libc::c_int {
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"deflate\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    *comprLen = c_stream.total_out;
}
#[no_mangle]
pub unsafe extern "C" fn test_sync(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut err: libc::c_int = 0;
    let mut d_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    strcpy(
        uncompr as *mut libc::c_char,
        b"garbage\0" as *const u8 as *const libc::c_char,
    );
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = 2 as libc::c_int as uInt;
    err = inflateInit_(
        &mut d_stream,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    d_stream.next_out = uncompr;
    d_stream.avail_out = uncomprLen as uInt;
    err = inflate(&mut d_stream, 0 as libc::c_int);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflate\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    d_stream.avail_in = (comprLen as uInt).wrapping_sub(2 as libc::c_int as uInt);
    err = inflateSync(&mut d_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateSync\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    err = inflate(&mut d_stream, 4 as libc::c_int);
    if err != 1 as libc::c_int {
        fprintf(
            stderr,
            b"inflate should report Z_STREAM_END\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    printf(
        b"after inflateSync(): hel%s\n\0" as *const u8 as *const libc::c_char,
        uncompr as *mut libc::c_char,
    );
}
#[no_mangle]
pub unsafe extern "C" fn test_dict_deflate(mut compr: *mut Byte, mut comprLen: uLong) {
    let mut c_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    let mut err: libc::c_int = 0;
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err = deflateInit_(
        &mut c_stream,
        9 as libc::c_int,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    err = deflateSetDictionary(
        &mut c_stream,
        dictionary.as_ptr() as *const Bytef,
        ::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong as libc::c_int
            as uInt,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateSetDictionary\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    dictId = c_stream.adler;
    c_stream.next_out = compr;
    c_stream.avail_out = comprLen as uInt;
    c_stream.next_in = hello.as_ptr() as *const libc::c_uchar;
    c_stream
        .avail_in = (strlen(hello.as_ptr()) as uInt)
        .wrapping_add(1 as libc::c_int as uInt);
    err = deflate(&mut c_stream, 4 as libc::c_int);
    if err != 1 as libc::c_int {
        fprintf(
            stderr,
            b"deflate should report Z_STREAM_END\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"deflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
}
#[no_mangle]
pub unsafe extern "C" fn test_dict_inflate(
    mut compr: *mut Byte,
    mut comprLen: uLong,
    mut uncompr: *mut Byte,
    mut uncomprLen: uLong,
) {
    let mut err: libc::c_int = 0;
    let mut d_stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    strcpy(
        uncompr as *mut libc::c_char,
        b"garbage\0" as *const u8 as *const libc::c_char,
    );
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = comprLen as uInt;
    err = inflateInit_(
        &mut d_stream,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateInit\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    d_stream.next_out = uncompr;
    d_stream.avail_out = uncomprLen as uInt;
    loop {
        err = inflate(&mut d_stream, 0 as libc::c_int);
        if err == 1 as libc::c_int {
            break;
        }
        if err == 2 as libc::c_int {
            if d_stream.adler != dictId {
                fprintf(
                    stderr,
                    b"unexpected dictionary\0" as *const u8 as *const libc::c_char,
                );
                exit(1 as libc::c_int);
            }
            err = inflateSetDictionary(
                &mut d_stream,
                dictionary.as_ptr() as *const Bytef,
                ::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong
                    as libc::c_int as uInt,
            );
        }
        if err != 0 as libc::c_int {
            fprintf(
                stderr,
                b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
                b"inflate with dict\0" as *const u8 as *const libc::c_char,
                err,
            );
            exit(1 as libc::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as libc::c_int {
        fprintf(
            stderr,
            b"%s error: %d\n\0" as *const u8 as *const libc::c_char,
            b"inflateEnd\0" as *const u8 as *const libc::c_char,
            err,
        );
        exit(1 as libc::c_int);
    }
    if strcmp(uncompr as *mut libc::c_char, hello.as_ptr()) != 0 {
        fprintf(
            stderr,
            b"bad inflate with dict\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    } else {
        printf(
            b"inflate with dictionary: %s\n\0" as *const u8 as *const libc::c_char,
            uncompr as *mut libc::c_char,
        );
    };
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut compr: *mut Byte = 0 as *mut Byte;
    let mut uncompr: *mut Byte = 0 as *mut Byte;
    let mut uncomprLen: uLong = 20000 as libc::c_int as uLong;
    let mut comprLen: uLong = 3 as libc::c_int as uLong * uncomprLen;
    static mut myVersion: *const libc::c_char = b"1.3-optipng\0" as *const u8
        as *const libc::c_char;
    if *(zlibVersion()).offset(0 as libc::c_int as isize) as libc::c_int
        != *myVersion.offset(0 as libc::c_int as isize) as libc::c_int
    {
        fprintf(
            stderr,
            b"incompatible zlib version\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    } else if strcmp(zlibVersion(), b"1.3-optipng\0" as *const u8 as *const libc::c_char)
        != 0 as libc::c_int
    {
        fprintf(
            stderr,
            b"warning: different zlib version linked: %s\n\0" as *const u8
                as *const libc::c_char,
            zlibVersion(),
        );
    }
    printf(
        b"zlib version %s = 0x%04x, compile flags = 0x%lx\n\0" as *const u8
            as *const libc::c_char,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        0x130f as libc::c_int,
        zlibCompileFlags(),
    );
    compr = calloc(comprLen as uInt as libc::c_ulong, 1 as libc::c_int as libc::c_ulong)
        as *mut Byte;
    uncompr = calloc(
        uncomprLen as uInt as libc::c_ulong,
        1 as libc::c_int as libc::c_ulong,
    ) as *mut Byte;
    if compr.is_null() || uncompr.is_null() {
        printf(b"out of memory\n\0" as *const u8 as *const libc::c_char);
        exit(1 as libc::c_int);
    }
    test_compress(compr, comprLen, uncompr, uncomprLen);
    test_gzio(
        if argc > 1 as libc::c_int {
            *argv.offset(1 as libc::c_int as isize) as *const libc::c_char
        } else {
            b"foo.gz\0" as *const u8 as *const libc::c_char
        },
        uncompr,
        uncomprLen,
    );
    test_deflate(compr, comprLen);
    test_inflate(compr, comprLen, uncompr, uncomprLen);
    test_large_deflate(compr, comprLen, uncompr, uncomprLen);
    test_large_inflate(compr, comprLen, uncompr, uncomprLen);
    test_flush(compr, &mut comprLen);
    test_sync(compr, comprLen, uncompr, uncomprLen);
    comprLen = 3 as libc::c_int as uLong * uncomprLen;
    test_dict_deflate(compr, comprLen);
    test_dict_inflate(compr, comprLen, uncompr, uncomprLen);
    free(compr as *mut libc::c_void);
    free(uncompr as *mut libc::c_void);
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(
            (::std::ffi::CString::new(arg))
                .expect("Failed to convert argument into CString.")
                .into_raw(),
        );
    }
    args.push(::core::ptr::null_mut());
    unsafe {
        ::std::process::exit(
            main_0(
                (args.len() - 1) as libc::c_int,
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
