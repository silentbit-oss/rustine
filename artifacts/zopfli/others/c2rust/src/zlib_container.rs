use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn realloc(_: *mut libc::c_void, _: libc::c_ulong) -> *mut libc::c_void;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn ZopfliDeflate(
        options: *const ZopfliOptions,
        btype: libc::c_int,
        final_0: libc::c_int,
        in_0: *const libc::c_uchar,
        insize: size_t,
        bp: *mut libc::c_uchar,
        out: *mut *mut libc::c_uchar,
        outsize: *mut size_t,
    );
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ZopfliOptions {
    pub verbose: libc::c_int,
    pub verbose_more: libc::c_int,
    pub numiterations: libc::c_int,
    pub blocksplitting: libc::c_int,
    pub blocksplittinglast: libc::c_int,
    pub blocksplittingmax: libc::c_int,
}
pub type FILE = _IO_FILE;
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
pub type __off64_t = libc::c_long;
pub type _IO_lock_t = ();
pub type __off_t = libc::c_long;
unsafe extern "C" fn adler32(
    mut data: *const libc::c_uchar,
    mut size: size_t,
) -> libc::c_uint {
    static mut sums_overflow: libc::c_uint = 5550 as libc::c_int as libc::c_uint;
    let mut s1: libc::c_uint = 1 as libc::c_int as libc::c_uint;
    let mut s2: libc::c_uint = (1 as libc::c_int >> 16 as libc::c_int) as libc::c_uint;
    while size > 0 as libc::c_int as size_t {
        let mut amount: size_t = if size > sums_overflow as size_t {
            sums_overflow as size_t
        } else {
            size
        };
        size = size.wrapping_sub(amount);
        while amount > 0 as libc::c_int as size_t {
            let fresh0 = data;
            data = data.offset(1);
            s1 = s1.wrapping_add(*fresh0 as libc::c_uint);
            s2 = s2.wrapping_add(s1);
            amount = amount.wrapping_sub(1);
            amount;
        }
        s1 = s1.wrapping_rem(65521 as libc::c_int as libc::c_uint);
        s2 = s2.wrapping_rem(65521 as libc::c_int as libc::c_uint);
    }
    return s2 << 16 as libc::c_int | s1;
}
#[no_mangle]
pub unsafe extern "C" fn ZopfliZlibCompress(
    mut options: *const ZopfliOptions,
    mut in_0: *const libc::c_uchar,
    mut insize: size_t,
    mut out: *mut *mut libc::c_uchar,
    mut outsize: *mut size_t,
) {
    let mut bitpointer: libc::c_uchar = 0 as libc::c_int as libc::c_uchar;
    let mut checksum: libc::c_uint = adler32(in_0, insize as libc::c_uint as size_t);
    let mut cmf: libc::c_uint = 120 as libc::c_int as libc::c_uint;
    let mut flevel: libc::c_uint = 3 as libc::c_int as libc::c_uint;
    let mut fdict: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    let mut cmfflg: libc::c_uint = (256 as libc::c_int as libc::c_uint)
        .wrapping_mul(cmf)
        .wrapping_add(fdict.wrapping_mul(32 as libc::c_int as libc::c_uint))
        .wrapping_add(flevel.wrapping_mul(64 as libc::c_int as libc::c_uint));
    let mut fcheck: libc::c_uint = (31 as libc::c_int as libc::c_uint)
        .wrapping_sub(cmfflg.wrapping_rem(31 as libc::c_int as libc::c_uint));
    cmfflg = cmfflg.wrapping_add(fcheck);
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = cmfflg.wrapping_div(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = cmfflg.wrapping_rem(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    ZopfliDeflate(
        options,
        2 as libc::c_int,
        1 as libc::c_int,
        in_0,
        insize,
        &mut bitpointer,
        out,
        outsize,
    );
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = (checksum >> 24 as libc::c_int)
        .wrapping_rem(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = (checksum >> 16 as libc::c_int)
        .wrapping_rem(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = (checksum >> 8 as libc::c_int)
        .wrapping_rem(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    if *outsize & (*outsize).wrapping_sub(1 as libc::c_int as size_t) == 0 {
        *out = (if *outsize == 0 as libc::c_int as size_t {
            malloc(::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong)
        } else {
            realloc(
                *out as *mut libc::c_void,
                (*outsize * 2 as libc::c_int as size_t)
                    .wrapping_mul(
                        ::core::mem::size_of::<libc::c_uchar>() as libc::c_ulong,
                    ),
            )
        }) as *mut libc::c_uchar;
    }
    *(*out)
        .offset(
            *outsize as isize,
        ) = checksum.wrapping_rem(256 as libc::c_int as libc::c_uint) as libc::c_uchar;
    *outsize = (*outsize).wrapping_add(1);
    *outsize;
    if (*options).verbose != 0 {
        fprintf(
            stderr,
            b"Original Size: %d, Zlib: %d, Compression: %f%% Removed\n\0" as *const u8
                as *const libc::c_char,
            insize as libc::c_int,
            *outsize as libc::c_int,
            100.0f64 * insize.wrapping_sub(*outsize) as libc::c_double
                / insize as libc::c_double,
        );
    }
}
