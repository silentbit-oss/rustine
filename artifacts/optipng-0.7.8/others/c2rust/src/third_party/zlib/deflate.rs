use ::libc;
extern "C" {
    pub type static_tree_desc_s;
    fn adler32(adler: uLong, buf: *const Bytef, len: uInt) -> uLong;
    fn _tr_init(s: *mut deflate_state);
    fn _tr_flush_block(
        s: *mut deflate_state,
        buf: *mut charf,
        stored_len: ulg,
        last: libc::c_int,
    );
    fn _tr_flush_bits(s: *mut deflate_state);
    fn _tr_align(s: *mut deflate_state);
    fn _tr_stored_block(
        s: *mut deflate_state,
        buf: *mut charf,
        stored_len: ulg,
        last: libc::c_int,
    );
    static _length_code: [uch; 0];
    static _dist_code: [uch; 0];
    static z_errmsg: [*const libc::c_char; 10];
    fn zcalloc(opaque: voidpf, items: libc::c_uint, size: libc::c_uint) -> voidpf;
    fn zcfree(opaque: voidpf, ptr: voidpf);
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
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
pub type charf = libc::c_char;
pub type voidpf = *mut libc::c_void;
pub type alloc_func = Option::<unsafe extern "C" fn(voidpf, uInt, uInt) -> voidpf>;
pub type free_func = Option::<unsafe extern "C" fn(voidpf, voidpf) -> ()>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct internal_state {
    pub strm: z_streamp,
    pub status: libc::c_int,
    pub pending_buf: *mut Bytef,
    pub pending_buf_size: ulg,
    pub pending_out: *mut Bytef,
    pub pending: ulg,
    pub wrap: libc::c_int,
    pub gzhead: gz_headerp,
    pub gzindex: ulg,
    pub method: Byte,
    pub last_flush: libc::c_int,
    pub w_size: uInt,
    pub w_bits: uInt,
    pub w_mask: uInt,
    pub window: *mut Bytef,
    pub window_size: ulg,
    pub prev: *mut Posf,
    pub head: *mut Posf,
    pub ins_h: uInt,
    pub hash_size: uInt,
    pub hash_bits: uInt,
    pub hash_mask: uInt,
    pub hash_shift: uInt,
    pub block_start: libc::c_long,
    pub match_length: uInt,
    pub prev_match: IPos,
    pub match_available: libc::c_int,
    pub strstart: uInt,
    pub match_start: uInt,
    pub lookahead: uInt,
    pub prev_length: uInt,
    pub max_chain_length: uInt,
    pub max_lazy_match: uInt,
    pub level: libc::c_int,
    pub strategy: libc::c_int,
    pub good_match: uInt,
    pub nice_match: libc::c_int,
    pub dyn_ltree: [ct_data_s; 573],
    pub dyn_dtree: [ct_data_s; 61],
    pub bl_tree: [ct_data_s; 39],
    pub l_desc: tree_desc_s,
    pub d_desc: tree_desc_s,
    pub bl_desc: tree_desc_s,
    pub bl_count: [ush; 16],
    pub heap: [libc::c_int; 573],
    pub heap_len: libc::c_int,
    pub heap_max: libc::c_int,
    pub depth: [uch; 573],
    pub sym_buf: *mut uchf,
    pub lit_bufsize: uInt,
    pub sym_next: uInt,
    pub sym_end: uInt,
    pub opt_len: ulg,
    pub static_len: ulg,
    pub matches: uInt,
    pub insert: uInt,
    pub bi_buf: ush,
    pub bi_valid: libc::c_int,
    pub high_water: ulg,
}
pub type ulg = libc::c_ulong;
pub type ush = libc::c_ushort;
pub type uchf = uch;
pub type uch = libc::c_uchar;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct tree_desc_s {
    pub dyn_tree: *mut ct_data,
    pub max_code: libc::c_int,
    pub stat_desc: *const static_tree_desc,
}
pub type static_tree_desc = static_tree_desc_s;
pub type ct_data = ct_data_s;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ct_data_s {
    pub fc: C2RustUnnamed_0,
    pub dl: C2RustUnnamed,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub dad: ush,
    pub len: ush,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_0 {
    pub freq: ush,
    pub code: ush,
}
pub type IPos = libc::c_uint;
pub type Posf = Pos;
pub type Pos = ush;
pub type gz_headerp = *mut gz_header;
pub type gz_header = gz_header_s;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct gz_header_s {
    pub text: libc::c_int,
    pub time: uLong,
    pub xflags: libc::c_int,
    pub os: libc::c_int,
    pub extra: *mut Bytef,
    pub extra_len: uInt,
    pub extra_max: uInt,
    pub name: *mut Bytef,
    pub name_max: uInt,
    pub comment: *mut Bytef,
    pub comm_max: uInt,
    pub hcrc: libc::c_int,
    pub done: libc::c_int,
}
pub type z_streamp = *mut z_stream;
pub type z_stream = z_stream_s;
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
pub type deflate_state = internal_state;
pub const block_done: block_state = 1;
pub type block_state = libc::c_uint;
pub const finish_done: block_state = 3;
pub const finish_started: block_state = 2;
pub const need_more: block_state = 0;
pub type compress_func = Option::<
    unsafe extern "C" fn(*mut deflate_state, libc::c_int) -> block_state,
>;
pub type config = config_s;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct config_s {
    pub good_length: ush,
    pub max_lazy: ush,
    pub nice_length: ush,
    pub max_chain: ush,
    pub func: compress_func,
}
#[no_mangle]
pub static mut deflate_copyright: [libc::c_char; 66] = unsafe {
    *::core::mem::transmute::<
        &[u8; 66],
        &[libc::c_char; 66],
    >(b" deflate 1.3 Copyright 1995-2023 Jean-loup Gailly and Mark Adler \0")
};
static mut configuration_table: [config; 10] = unsafe {
    [
        {
            let mut init = config_s {
                good_length: 0 as libc::c_int as ush,
                max_lazy: 0 as libc::c_int as ush,
                nice_length: 0 as libc::c_int as ush,
                max_chain: 0 as libc::c_int as ush,
                func: Some(
                    deflate_stored
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 4 as libc::c_int as ush,
                max_lazy: 4 as libc::c_int as ush,
                nice_length: 8 as libc::c_int as ush,
                max_chain: 4 as libc::c_int as ush,
                func: Some(
                    deflate_fast
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 4 as libc::c_int as ush,
                max_lazy: 5 as libc::c_int as ush,
                nice_length: 16 as libc::c_int as ush,
                max_chain: 8 as libc::c_int as ush,
                func: Some(
                    deflate_fast
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 4 as libc::c_int as ush,
                max_lazy: 6 as libc::c_int as ush,
                nice_length: 32 as libc::c_int as ush,
                max_chain: 32 as libc::c_int as ush,
                func: Some(
                    deflate_fast
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 4 as libc::c_int as ush,
                max_lazy: 4 as libc::c_int as ush,
                nice_length: 16 as libc::c_int as ush,
                max_chain: 16 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 8 as libc::c_int as ush,
                max_lazy: 16 as libc::c_int as ush,
                nice_length: 32 as libc::c_int as ush,
                max_chain: 32 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 8 as libc::c_int as ush,
                max_lazy: 16 as libc::c_int as ush,
                nice_length: 128 as libc::c_int as ush,
                max_chain: 128 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 8 as libc::c_int as ush,
                max_lazy: 32 as libc::c_int as ush,
                nice_length: 128 as libc::c_int as ush,
                max_chain: 256 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 32 as libc::c_int as ush,
                max_lazy: 128 as libc::c_int as ush,
                nice_length: 258 as libc::c_int as ush,
                max_chain: 1024 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
        {
            let mut init = config_s {
                good_length: 32 as libc::c_int as ush,
                max_lazy: 258 as libc::c_int as ush,
                nice_length: 258 as libc::c_int as ush,
                max_chain: 4096 as libc::c_int as ush,
                func: Some(
                    deflate_slow
                        as unsafe extern "C" fn(
                            *mut deflate_state,
                            libc::c_int,
                        ) -> block_state,
                ),
            };
            init
        },
    ]
};
unsafe extern "C" fn slide_hash(mut s: *mut deflate_state) {
    let mut n: libc::c_uint = 0;
    let mut m: libc::c_uint = 0;
    let mut p: *mut Posf = 0 as *mut Posf;
    let mut wsize: uInt = (*s).w_size;
    n = (*s).hash_size;
    p = &mut *((*s).head).offset(n as isize) as *mut Posf;
    loop {
        p = p.offset(-1);
        m = *p as libc::c_uint;
        *p = (if m >= wsize {
            m.wrapping_sub(wsize)
        } else {
            0 as libc::c_int as libc::c_uint
        }) as Pos;
        n = n.wrapping_sub(1);
        if !(n != 0) {
            break;
        }
    }
    n = wsize;
    p = &mut *((*s).prev).offset(n as isize) as *mut Posf;
    loop {
        p = p.offset(-1);
        m = *p as libc::c_uint;
        *p = (if m >= wsize {
            m.wrapping_sub(wsize)
        } else {
            0 as libc::c_int as libc::c_uint
        }) as Pos;
        n = n.wrapping_sub(1);
        if !(n != 0) {
            break;
        }
    };
}
unsafe extern "C" fn read_buf(
    mut strm: z_streamp,
    mut buf: *mut Bytef,
    mut size: libc::c_uint,
) -> libc::c_uint {
    let mut len: libc::c_uint = (*strm).avail_in;
    if len > size {
        len = size;
    }
    if len == 0 as libc::c_int as libc::c_uint {
        return 0 as libc::c_int as libc::c_uint;
    }
    (*strm)
        .avail_in = ((*strm).avail_in as libc::c_uint).wrapping_sub(len) as uInt as uInt;
    memcpy(
        buf as *mut libc::c_void,
        (*strm).next_in as *const libc::c_void,
        len as libc::c_ulong,
    );
    if (*(*strm).state).wrap == 1 as libc::c_int {
        (*strm).adler = adler32((*strm).adler, buf, len);
    }
    (*strm).next_in = ((*strm).next_in).offset(len as isize);
    (*strm).total_in = ((*strm).total_in).wrapping_add(len as uLong);
    return len;
}
unsafe extern "C" fn fill_window(mut s: *mut deflate_state) {
    let mut n: libc::c_uint = 0;
    let mut more: libc::c_uint = 0;
    let mut wsize: uInt = (*s).w_size;
    loop {
        more = ((*s).window_size)
            .wrapping_sub((*s).lookahead as ulg)
            .wrapping_sub((*s).strstart as ulg) as libc::c_uint;
        if ::core::mem::size_of::<libc::c_int>() as libc::c_ulong
            <= 2 as libc::c_int as libc::c_ulong
        {
            if more == 0 as libc::c_int as libc::c_uint
                && (*s).strstart == 0 as libc::c_int as uInt
                && (*s).lookahead == 0 as libc::c_int as uInt
            {
                more = wsize;
            } else if more == -(1 as libc::c_int) as libc::c_uint {
                more = more.wrapping_sub(1);
                more;
            }
        }
        if (*s).strstart
            >= wsize
                .wrapping_add(
                    ((*s).w_size)
                        .wrapping_sub(
                            (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int)
                                as uInt,
                        ),
                )
        {
            memcpy(
                (*s).window as *mut libc::c_void,
                ((*s).window).offset(wsize as isize) as *const libc::c_void,
                wsize.wrapping_sub(more) as libc::c_ulong,
            );
            (*s).match_start = ((*s).match_start).wrapping_sub(wsize);
            (*s).strstart = ((*s).strstart).wrapping_sub(wsize);
            (*s).block_start -= wsize as libc::c_long;
            if (*s).insert > (*s).strstart {
                (*s).insert = (*s).strstart;
            }
            slide_hash(s);
            more = more.wrapping_add(wsize);
        }
        if (*(*s).strm).avail_in == 0 as libc::c_int as uInt {
            break;
        }
        n = read_buf(
            (*s).strm,
            ((*s).window).offset((*s).strstart as isize).offset((*s).lookahead as isize),
            more,
        );
        (*s)
            .lookahead = ((*s).lookahead as libc::c_uint).wrapping_add(n) as uInt
            as uInt;
        if ((*s).lookahead).wrapping_add((*s).insert) >= 3 as libc::c_int as uInt {
            let mut str: uInt = ((*s).strstart).wrapping_sub((*s).insert);
            (*s).ins_h = *((*s).window).offset(str as isize) as uInt;
            (*s)
                .ins_h = ((*s).ins_h << (*s).hash_shift
                ^ *((*s).window)
                    .offset(str.wrapping_add(1 as libc::c_int as uInt) as isize) as uInt)
                & (*s).hash_mask;
            while (*s).insert != 0 {
                (*s)
                    .ins_h = ((*s).ins_h << (*s).hash_shift
                    ^ *((*s).window)
                        .offset(
                            str
                                .wrapping_add(3 as libc::c_int as uInt)
                                .wrapping_sub(1 as libc::c_int as uInt) as isize,
                        ) as uInt) & (*s).hash_mask;
                *((*s).prev)
                    .offset(
                        (str & (*s).w_mask) as isize,
                    ) = *((*s).head).offset((*s).ins_h as isize);
                *((*s).head).offset((*s).ins_h as isize) = str as Pos;
                str = str.wrapping_add(1);
                str;
                (*s).insert = ((*s).insert).wrapping_sub(1);
                (*s).insert;
                if ((*s).lookahead).wrapping_add((*s).insert) < 3 as libc::c_int as uInt
                {
                    break;
                }
            }
        }
        if !((*s).lookahead
            < (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt
            && (*(*s).strm).avail_in != 0 as libc::c_int as uInt)
        {
            break;
        }
    }
    if (*s).high_water < (*s).window_size {
        let mut curr: ulg = ((*s).strstart as ulg).wrapping_add((*s).lookahead as ulg);
        let mut init: ulg = 0;
        if (*s).high_water < curr {
            init = ((*s).window_size).wrapping_sub(curr);
            if init > 258 as libc::c_int as ulg {
                init = 258 as libc::c_int as ulg;
            }
            memset(
                ((*s).window).offset(curr as isize) as *mut libc::c_void,
                0 as libc::c_int,
                init as libc::c_uint as libc::c_ulong,
            );
            (*s).high_water = curr.wrapping_add(init);
        } else if (*s).high_water < curr.wrapping_add(258 as libc::c_int as ulg) {
            init = curr
                .wrapping_add(258 as libc::c_int as ulg)
                .wrapping_sub((*s).high_water);
            if init > ((*s).window_size).wrapping_sub((*s).high_water) {
                init = ((*s).window_size).wrapping_sub((*s).high_water);
            }
            memset(
                ((*s).window).offset((*s).high_water as isize) as *mut libc::c_void,
                0 as libc::c_int,
                init as libc::c_uint as libc::c_ulong,
            );
            (*s).high_water = ((*s).high_water).wrapping_add(init);
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn deflateInit_(
    mut strm: z_streamp,
    mut level: libc::c_int,
    mut version: *const libc::c_char,
    mut stream_size: libc::c_int,
) -> libc::c_int {
    return deflateInit2_(
        strm,
        level,
        8 as libc::c_int,
        15 as libc::c_int,
        8 as libc::c_int,
        0 as libc::c_int,
        version,
        stream_size,
    );
}
#[no_mangle]
pub unsafe extern "C" fn deflateInit2_(
    mut strm: z_streamp,
    mut level: libc::c_int,
    mut method: libc::c_int,
    mut windowBits: libc::c_int,
    mut memLevel: libc::c_int,
    mut strategy: libc::c_int,
    mut version: *const libc::c_char,
    mut stream_size: libc::c_int,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut wrap: libc::c_int = 1 as libc::c_int;
    static mut my_version: [libc::c_char; 12] = unsafe {
        *::core::mem::transmute::<&[u8; 12], &[libc::c_char; 12]>(b"1.3-optipng\0")
    };
    if version.is_null()
        || *version.offset(0 as libc::c_int as isize) as libc::c_int
            != my_version[0 as libc::c_int as usize] as libc::c_int
        || stream_size as libc::c_ulong
            != ::core::mem::size_of::<z_stream>() as libc::c_ulong
    {
        return -(6 as libc::c_int);
    }
    if strm.is_null() {
        return -(2 as libc::c_int);
    }
    (*strm).msg = 0 as *const libc::c_char;
    if ((*strm).zalloc).is_none() {
        (*strm)
            .zalloc = Some(
            zcalloc as unsafe extern "C" fn(voidpf, libc::c_uint, libc::c_uint) -> voidpf,
        );
        (*strm).opaque = 0 as voidpf;
    }
    if ((*strm).zfree).is_none() {
        (*strm).zfree = Some(zcfree as unsafe extern "C" fn(voidpf, voidpf) -> ());
    }
    if level == -(1 as libc::c_int) {
        level = 6 as libc::c_int;
    }
    if windowBits < 0 as libc::c_int {
        wrap = 0 as libc::c_int;
        if windowBits < -(15 as libc::c_int) {
            return -(2 as libc::c_int);
        }
        windowBits = -windowBits;
    }
    if memLevel < 1 as libc::c_int || memLevel > 9 as libc::c_int
        || method != 8 as libc::c_int || windowBits < 8 as libc::c_int
        || windowBits > 15 as libc::c_int || level < 0 as libc::c_int
        || level > 9 as libc::c_int || strategy < 0 as libc::c_int
        || strategy > 4 as libc::c_int
        || windowBits == 8 as libc::c_int && wrap != 1 as libc::c_int
    {
        return -(2 as libc::c_int);
    }
    if windowBits == 8 as libc::c_int {
        windowBits = 9 as libc::c_int;
    }
    s = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*strm).opaque,
        1 as libc::c_int as uInt,
        ::core::mem::size_of::<deflate_state>() as libc::c_ulong as uInt,
    ) as *mut deflate_state;
    if s.is_null() {
        return -(4 as libc::c_int);
    }
    (*strm).state = s as *mut internal_state;
    (*s).strm = strm;
    (*s).status = 42 as libc::c_int;
    (*s).wrap = wrap;
    (*s).gzhead = 0 as gz_headerp;
    (*s).w_bits = windowBits as uInt;
    (*s).w_size = ((1 as libc::c_int) << (*s).w_bits) as uInt;
    (*s).w_mask = ((*s).w_size).wrapping_sub(1 as libc::c_int as uInt);
    (*s).hash_bits = (memLevel as uInt).wrapping_add(7 as libc::c_int as uInt);
    (*s).hash_size = ((1 as libc::c_int) << (*s).hash_bits) as uInt;
    (*s).hash_mask = ((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt);
    (*s)
        .hash_shift = ((*s).hash_bits)
        .wrapping_add(3 as libc::c_int as uInt)
        .wrapping_sub(1 as libc::c_int as uInt) / 3 as libc::c_int as uInt;
    (*s)
        .window = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*strm).opaque,
        (*s).w_size,
        (2 as libc::c_int as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Byte>() as libc::c_ulong) as uInt,
    ) as *mut Bytef;
    (*s)
        .prev = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*strm).opaque,
        (*s).w_size,
        ::core::mem::size_of::<Pos>() as libc::c_ulong as uInt,
    ) as *mut Posf;
    (*s)
        .head = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*strm).opaque,
        (*s).hash_size,
        ::core::mem::size_of::<Pos>() as libc::c_ulong as uInt,
    ) as *mut Posf;
    (*s).high_water = 0 as libc::c_int as ulg;
    (*s).lit_bufsize = ((1 as libc::c_int) << memLevel + 6 as libc::c_int) as uInt;
    (*s)
        .pending_buf = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )((*strm).opaque, (*s).lit_bufsize, 4 as libc::c_int as uInt) as *mut uchf;
    (*s).pending_buf_size = (*s).lit_bufsize as ulg * 4 as libc::c_int as ulg;
    if ((*s).window).is_null() || ((*s).prev).is_null() || ((*s).head).is_null()
        || ((*s).pending_buf).is_null()
    {
        (*s).status = 666 as libc::c_int;
        (*strm).msg = z_errmsg[(2 as libc::c_int - -(4 as libc::c_int)) as usize];
        deflateEnd(strm);
        return -(4 as libc::c_int);
    }
    (*s).sym_buf = ((*s).pending_buf).offset((*s).lit_bufsize as isize);
    (*s)
        .sym_end = ((*s).lit_bufsize).wrapping_sub(1 as libc::c_int as uInt)
        * 3 as libc::c_int as uInt;
    (*s).level = level;
    (*s).strategy = strategy;
    (*s).method = method as Byte;
    return deflateReset(strm);
}
unsafe extern "C" fn deflateStateCheck(mut strm: z_streamp) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    if strm.is_null() || ((*strm).zalloc).is_none() || ((*strm).zfree).is_none() {
        return 1 as libc::c_int;
    }
    s = (*strm).state;
    if s.is_null() || (*s).strm != strm
        || (*s).status != 42 as libc::c_int && (*s).status != 69 as libc::c_int
            && (*s).status != 73 as libc::c_int && (*s).status != 91 as libc::c_int
            && (*s).status != 103 as libc::c_int && (*s).status != 113 as libc::c_int
            && (*s).status != 666 as libc::c_int
    {
        return 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateSetDictionary(
    mut strm: z_streamp,
    mut dictionary: *const Bytef,
    mut dictLength: uInt,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut str: uInt = 0;
    let mut n: uInt = 0;
    let mut wrap: libc::c_int = 0;
    let mut avail: libc::c_uint = 0;
    let mut next: *const libc::c_uchar = 0 as *const libc::c_uchar;
    if deflateStateCheck(strm) != 0 || dictionary.is_null() {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    wrap = (*s).wrap;
    if wrap == 2 as libc::c_int
        || wrap == 1 as libc::c_int && (*s).status != 42 as libc::c_int
        || (*s).lookahead != 0
    {
        return -(2 as libc::c_int);
    }
    if wrap == 1 as libc::c_int {
        (*strm).adler = adler32((*strm).adler, dictionary, dictLength);
    }
    (*s).wrap = 0 as libc::c_int;
    if dictLength >= (*s).w_size {
        if wrap == 0 as libc::c_int {
            *((*s).head)
                .offset(
                    ((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt) as isize,
                ) = 0 as libc::c_int as Posf;
            memset(
                (*s).head as *mut Bytef as *mut libc::c_void,
                0 as libc::c_int,
                (((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt)
                    as libc::c_ulong)
                    .wrapping_mul(::core::mem::size_of::<Posf>() as libc::c_ulong),
            );
            (*s).strstart = 0 as libc::c_int as uInt;
            (*s).block_start = 0 as libc::c_long;
            (*s).insert = 0 as libc::c_int as uInt;
        }
        dictionary = dictionary.offset(dictLength.wrapping_sub((*s).w_size) as isize);
        dictLength = (*s).w_size;
    }
    avail = (*strm).avail_in;
    next = (*strm).next_in;
    (*strm).avail_in = dictLength;
    (*strm).next_in = dictionary;
    fill_window(s);
    while (*s).lookahead >= 3 as libc::c_int as uInt {
        str = (*s).strstart;
        n = ((*s).lookahead).wrapping_sub((3 as libc::c_int - 1 as libc::c_int) as uInt);
        loop {
            (*s)
                .ins_h = ((*s).ins_h << (*s).hash_shift
                ^ *((*s).window)
                    .offset(
                        str
                            .wrapping_add(3 as libc::c_int as uInt)
                            .wrapping_sub(1 as libc::c_int as uInt) as isize,
                    ) as uInt) & (*s).hash_mask;
            *((*s).prev)
                .offset(
                    (str & (*s).w_mask) as isize,
                ) = *((*s).head).offset((*s).ins_h as isize);
            *((*s).head).offset((*s).ins_h as isize) = str as Pos;
            str = str.wrapping_add(1);
            str;
            n = n.wrapping_sub(1);
            if !(n != 0) {
                break;
            }
        }
        (*s).strstart = str;
        (*s).lookahead = (3 as libc::c_int - 1 as libc::c_int) as uInt;
        fill_window(s);
    }
    (*s).strstart = ((*s).strstart).wrapping_add((*s).lookahead);
    (*s).block_start = (*s).strstart as libc::c_long;
    (*s).insert = (*s).lookahead;
    (*s).lookahead = 0 as libc::c_int as uInt;
    (*s).prev_length = (3 as libc::c_int - 1 as libc::c_int) as uInt;
    (*s).match_length = (*s).prev_length;
    (*s).match_available = 0 as libc::c_int;
    (*strm).next_in = next;
    (*strm).avail_in = avail;
    (*s).wrap = wrap;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateGetDictionary(
    mut strm: z_streamp,
    mut dictionary: *mut Bytef,
    mut dictLength: *mut uInt,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut len: uInt = 0;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    len = ((*s).strstart).wrapping_add((*s).lookahead);
    if len > (*s).w_size {
        len = (*s).w_size;
    }
    if !dictionary.is_null() && len != 0 {
        memcpy(
            dictionary as *mut libc::c_void,
            ((*s).window)
                .offset((*s).strstart as isize)
                .offset((*s).lookahead as isize)
                .offset(-(len as isize)) as *const libc::c_void,
            len as libc::c_ulong,
        );
    }
    if !dictLength.is_null() {
        *dictLength = len;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateResetKeep(mut strm: z_streamp) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    (*strm).total_out = 0 as libc::c_int as uLong;
    (*strm).total_in = (*strm).total_out;
    (*strm).msg = 0 as *const libc::c_char;
    (*strm).data_type = 2 as libc::c_int;
    s = (*strm).state as *mut deflate_state;
    (*s).pending = 0 as libc::c_int as ulg;
    (*s).pending_out = (*s).pending_buf;
    if (*s).wrap < 0 as libc::c_int {
        (*s).wrap = -(*s).wrap;
    }
    (*s).status = 42 as libc::c_int;
    (*strm)
        .adler = adler32(
        0 as libc::c_long as uLong,
        0 as *const Bytef,
        0 as libc::c_int as uInt,
    );
    (*s).last_flush = -(2 as libc::c_int);
    _tr_init(s);
    return 0 as libc::c_int;
}
unsafe extern "C" fn lm_init(mut s: *mut deflate_state) {
    (*s).window_size = 2 as libc::c_long as ulg * (*s).w_size as ulg;
    *((*s).head)
        .offset(
            ((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt) as isize,
        ) = 0 as libc::c_int as Posf;
    memset(
        (*s).head as *mut Bytef as *mut libc::c_void,
        0 as libc::c_int,
        (((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt) as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Posf>() as libc::c_ulong),
    );
    (*s).max_lazy_match = configuration_table[(*s).level as usize].max_lazy as uInt;
    (*s).good_match = configuration_table[(*s).level as usize].good_length as uInt;
    (*s)
        .nice_match = configuration_table[(*s).level as usize].nice_length
        as libc::c_int;
    (*s).max_chain_length = configuration_table[(*s).level as usize].max_chain as uInt;
    (*s).strstart = 0 as libc::c_int as uInt;
    (*s).block_start = 0 as libc::c_long;
    (*s).lookahead = 0 as libc::c_int as uInt;
    (*s).insert = 0 as libc::c_int as uInt;
    (*s).prev_length = (3 as libc::c_int - 1 as libc::c_int) as uInt;
    (*s).match_length = (*s).prev_length;
    (*s).match_available = 0 as libc::c_int;
    (*s).ins_h = 0 as libc::c_int as uInt;
}
#[no_mangle]
pub unsafe extern "C" fn deflateReset(mut strm: z_streamp) -> libc::c_int {
    let mut ret: libc::c_int = 0;
    ret = deflateResetKeep(strm);
    if ret == 0 as libc::c_int {
        lm_init((*strm).state);
    }
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn deflateSetHeader(
    mut strm: z_streamp,
    mut head: gz_headerp,
) -> libc::c_int {
    if deflateStateCheck(strm) != 0 || (*(*strm).state).wrap != 2 as libc::c_int {
        return -(2 as libc::c_int);
    }
    (*(*strm).state).gzhead = head;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflatePending(
    mut strm: z_streamp,
    mut pending: *mut libc::c_uint,
    mut bits: *mut libc::c_int,
) -> libc::c_int {
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    if !pending.is_null() {
        *pending = (*(*strm).state).pending as libc::c_uint;
    }
    if !bits.is_null() {
        *bits = (*(*strm).state).bi_valid;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflatePrime(
    mut strm: z_streamp,
    mut bits: libc::c_int,
    mut value: libc::c_int,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut put: libc::c_int = 0;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    if bits < 0 as libc::c_int || bits > 16 as libc::c_int
        || (*s).sym_buf
            < ((*s).pending_out)
                .offset(
                    (16 as libc::c_int + 7 as libc::c_int >> 3 as libc::c_int) as isize,
                )
    {
        return -(5 as libc::c_int);
    }
    loop {
        put = 16 as libc::c_int - (*s).bi_valid;
        if put > bits {
            put = bits;
        }
        (*s)
            .bi_buf = ((*s).bi_buf as libc::c_int
            | ((value & ((1 as libc::c_int) << put) - 1 as libc::c_int) << (*s).bi_valid)
                as ush as libc::c_int) as ush;
        (*s).bi_valid += put;
        _tr_flush_bits(s);
        value >>= put;
        bits -= put;
        if !(bits != 0) {
            break;
        }
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateParams(
    mut strm: z_streamp,
    mut level: libc::c_int,
    mut strategy: libc::c_int,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut func: compress_func = None;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    if level == -(1 as libc::c_int) {
        level = 6 as libc::c_int;
    }
    if level < 0 as libc::c_int || level > 9 as libc::c_int
        || strategy < 0 as libc::c_int || strategy > 4 as libc::c_int
    {
        return -(2 as libc::c_int);
    }
    func = configuration_table[(*s).level as usize].func;
    if (strategy != (*s).strategy || func != configuration_table[level as usize].func)
        && (*s).last_flush != -(2 as libc::c_int)
    {
        let mut err: libc::c_int = deflate(strm, 5 as libc::c_int);
        if err == -(2 as libc::c_int) {
            return err;
        }
        if (*strm).avail_in != 0
            || (*s).strstart as libc::c_long - (*s).block_start
                + (*s).lookahead as libc::c_long != 0
        {
            return -(5 as libc::c_int);
        }
    }
    if (*s).level != level {
        if (*s).level == 0 as libc::c_int && (*s).matches != 0 as libc::c_int as uInt {
            if (*s).matches == 1 as libc::c_int as uInt {
                slide_hash(s);
            } else {
                *((*s).head)
                    .offset(
                        ((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt) as isize,
                    ) = 0 as libc::c_int as Posf;
                memset(
                    (*s).head as *mut Bytef as *mut libc::c_void,
                    0 as libc::c_int,
                    (((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt)
                        as libc::c_ulong)
                        .wrapping_mul(::core::mem::size_of::<Posf>() as libc::c_ulong),
                );
            }
            (*s).matches = 0 as libc::c_int as uInt;
        }
        (*s).level = level;
        (*s).max_lazy_match = configuration_table[level as usize].max_lazy as uInt;
        (*s).good_match = configuration_table[level as usize].good_length as uInt;
        (*s).nice_match = configuration_table[level as usize].nice_length as libc::c_int;
        (*s).max_chain_length = configuration_table[level as usize].max_chain as uInt;
    }
    (*s).strategy = strategy;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateTune(
    mut strm: z_streamp,
    mut good_length: libc::c_int,
    mut max_lazy: libc::c_int,
    mut nice_length: libc::c_int,
    mut max_chain: libc::c_int,
) -> libc::c_int {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    (*s).good_match = good_length as uInt;
    (*s).max_lazy_match = max_lazy as uInt;
    (*s).nice_match = nice_length;
    (*s).max_chain_length = max_chain as uInt;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn deflateBound(
    mut strm: z_streamp,
    mut sourceLen: uLong,
) -> uLong {
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    let mut fixedlen: uLong = 0;
    let mut storelen: uLong = 0;
    let mut wraplen: uLong = 0;
    fixedlen = sourceLen
        .wrapping_add(sourceLen >> 3 as libc::c_int)
        .wrapping_add(sourceLen >> 8 as libc::c_int)
        .wrapping_add(sourceLen >> 9 as libc::c_int)
        .wrapping_add(4 as libc::c_int as uLong);
    storelen = sourceLen
        .wrapping_add(sourceLen >> 5 as libc::c_int)
        .wrapping_add(sourceLen >> 7 as libc::c_int)
        .wrapping_add(sourceLen >> 11 as libc::c_int)
        .wrapping_add(7 as libc::c_int as uLong);
    if deflateStateCheck(strm) != 0 {
        return (if fixedlen > storelen { fixedlen } else { storelen })
            .wrapping_add(6 as libc::c_int as uLong);
    }
    s = (*strm).state;
    match (*s).wrap {
        0 => {
            wraplen = 0 as libc::c_int as uLong;
        }
        1 => {
            wraplen = (6 as libc::c_int
                + (if (*s).strstart != 0 { 4 as libc::c_int } else { 0 as libc::c_int }))
                as uLong;
        }
        _ => {
            wraplen = 6 as libc::c_int as uLong;
        }
    }
    if (*s).w_bits != 15 as libc::c_int as uInt
        || (*s).hash_bits != (8 as libc::c_int + 7 as libc::c_int) as uInt
    {
        return (if (*s).w_bits <= (*s).hash_bits && (*s).level != 0 {
            fixedlen
        } else {
            storelen
        })
            .wrapping_add(wraplen);
    }
    return sourceLen
        .wrapping_add(sourceLen >> 12 as libc::c_int)
        .wrapping_add(sourceLen >> 14 as libc::c_int)
        .wrapping_add(sourceLen >> 25 as libc::c_int)
        .wrapping_add(13 as libc::c_int as uLong)
        .wrapping_sub(6 as libc::c_int as uLong)
        .wrapping_add(wraplen);
}
unsafe extern "C" fn putShortMSB(mut s: *mut deflate_state, mut b: uInt) {
    let fresh0 = (*s).pending;
    (*s).pending = ((*s).pending).wrapping_add(1);
    *((*s).pending_buf).offset(fresh0 as isize) = (b >> 8 as libc::c_int) as Byte;
    let fresh1 = (*s).pending;
    (*s).pending = ((*s).pending).wrapping_add(1);
    *((*s).pending_buf)
        .offset(fresh1 as isize) = (b & 0xff as libc::c_int as uInt) as Byte;
}
unsafe extern "C" fn flush_pending(mut strm: z_streamp) {
    let mut len: libc::c_uint = 0;
    let mut s: *mut deflate_state = (*strm).state;
    _tr_flush_bits(s);
    len = (*s).pending as libc::c_uint;
    if len > (*strm).avail_out {
        len = (*strm).avail_out;
    }
    if len == 0 as libc::c_int as libc::c_uint {
        return;
    }
    memcpy(
        (*strm).next_out as *mut libc::c_void,
        (*s).pending_out as *const libc::c_void,
        len as libc::c_ulong,
    );
    (*strm).next_out = ((*strm).next_out).offset(len as isize);
    (*s).pending_out = ((*s).pending_out).offset(len as isize);
    (*strm).total_out = ((*strm).total_out).wrapping_add(len as uLong);
    (*strm)
        .avail_out = ((*strm).avail_out as libc::c_uint).wrapping_sub(len) as uInt
        as uInt;
    (*s).pending = ((*s).pending).wrapping_sub(len as ulg);
    if (*s).pending == 0 as libc::c_int as ulg {
        (*s).pending_out = (*s).pending_buf;
    }
}
#[no_mangle]
pub unsafe extern "C" fn deflate(
    mut strm: z_streamp,
    mut flush: libc::c_int,
) -> libc::c_int {
    let mut old_flush: libc::c_int = 0;
    let mut s: *mut deflate_state = 0 as *mut deflate_state;
    if deflateStateCheck(strm) != 0 || flush > 5 as libc::c_int
        || flush < 0 as libc::c_int
    {
        return -(2 as libc::c_int);
    }
    s = (*strm).state;
    if ((*strm).next_out).is_null()
        || (*strm).avail_in != 0 as libc::c_int as uInt && ((*strm).next_in).is_null()
        || (*s).status == 666 as libc::c_int && flush != 4 as libc::c_int
    {
        (*strm).msg = z_errmsg[(2 as libc::c_int - -(2 as libc::c_int)) as usize];
        return -(2 as libc::c_int);
    }
    if (*strm).avail_out == 0 as libc::c_int as uInt {
        (*strm).msg = z_errmsg[(2 as libc::c_int - -(5 as libc::c_int)) as usize];
        return -(5 as libc::c_int);
    }
    old_flush = (*s).last_flush;
    (*s).last_flush = flush;
    if (*s).pending != 0 as libc::c_int as ulg {
        flush_pending(strm);
        if (*strm).avail_out == 0 as libc::c_int as uInt {
            (*s).last_flush = -(1 as libc::c_int);
            return 0 as libc::c_int;
        }
    } else if (*strm).avail_in == 0 as libc::c_int as uInt
        && flush * 2 as libc::c_int
            - (if flush > 4 as libc::c_int {
                9 as libc::c_int
            } else {
                0 as libc::c_int
            })
            <= old_flush * 2 as libc::c_int
                - (if old_flush > 4 as libc::c_int {
                    9 as libc::c_int
                } else {
                    0 as libc::c_int
                }) && flush != 4 as libc::c_int
    {
        (*strm).msg = z_errmsg[(2 as libc::c_int - -(5 as libc::c_int)) as usize];
        return -(5 as libc::c_int);
    }
    if (*s).status == 666 as libc::c_int && (*strm).avail_in != 0 as libc::c_int as uInt
    {
        (*strm).msg = z_errmsg[(2 as libc::c_int - -(5 as libc::c_int)) as usize];
        return -(5 as libc::c_int);
    }
    if (*s).status == 42 as libc::c_int && (*s).wrap == 0 as libc::c_int {
        (*s).status = 113 as libc::c_int;
    }
    if (*s).status == 42 as libc::c_int {
        let mut header: uInt = (8 as libc::c_int as uInt)
            .wrapping_add(
                ((*s).w_bits).wrapping_sub(8 as libc::c_int as uInt) << 4 as libc::c_int,
            ) << 8 as libc::c_int;
        let mut level_flags: uInt = 0;
        if (*s).strategy >= 2 as libc::c_int || (*s).level < 2 as libc::c_int {
            level_flags = 0 as libc::c_int as uInt;
        } else if (*s).level < 6 as libc::c_int {
            level_flags = 1 as libc::c_int as uInt;
        } else if (*s).level == 6 as libc::c_int {
            level_flags = 2 as libc::c_int as uInt;
        } else {
            level_flags = 3 as libc::c_int as uInt;
        }
        header |= level_flags << 6 as libc::c_int;
        if (*s).strstart != 0 as libc::c_int as uInt {
            header |= 0x20 as libc::c_int as uInt;
        }
        header = header
            .wrapping_add(
                (31 as libc::c_int as uInt)
                    .wrapping_sub(header % 31 as libc::c_int as uInt),
            );
        putShortMSB(s, header);
        if (*s).strstart != 0 as libc::c_int as uInt {
            putShortMSB(s, ((*strm).adler >> 16 as libc::c_int) as uInt);
            putShortMSB(s, ((*strm).adler & 0xffff as libc::c_int as uLong) as uInt);
        }
        (*strm)
            .adler = adler32(
            0 as libc::c_long as uLong,
            0 as *const Bytef,
            0 as libc::c_int as uInt,
        );
        (*s).status = 113 as libc::c_int;
        flush_pending(strm);
        if (*s).pending != 0 as libc::c_int as ulg {
            (*s).last_flush = -(1 as libc::c_int);
            return 0 as libc::c_int;
        }
    }
    if (*strm).avail_in != 0 as libc::c_int as uInt
        || (*s).lookahead != 0 as libc::c_int as uInt
        || flush != 0 as libc::c_int && (*s).status != 666 as libc::c_int
    {
        let mut bstate: block_state = need_more;
        bstate = (if (*s).level == 0 as libc::c_int {
            deflate_stored(s, flush) as libc::c_uint
        } else if (*s).strategy == 2 as libc::c_int {
            deflate_huff(s, flush) as libc::c_uint
        } else if (*s).strategy == 3 as libc::c_int {
            deflate_rle(s, flush) as libc::c_uint
        } else {
            (Some(
                ((*configuration_table.as_ptr().offset((*s).level as isize)).func)
                    .expect("non-null function pointer"),
            ))
                .expect("non-null function pointer")(s, flush) as libc::c_uint
        }) as block_state;
        if bstate as libc::c_uint == finish_started as libc::c_int as libc::c_uint
            || bstate as libc::c_uint == finish_done as libc::c_int as libc::c_uint
        {
            (*s).status = 666 as libc::c_int;
        }
        if bstate as libc::c_uint == need_more as libc::c_int as libc::c_uint
            || bstate as libc::c_uint == finish_started as libc::c_int as libc::c_uint
        {
            if (*strm).avail_out == 0 as libc::c_int as uInt {
                (*s).last_flush = -(1 as libc::c_int);
            }
            return 0 as libc::c_int;
        }
        if bstate as libc::c_uint == block_done as libc::c_int as libc::c_uint {
            if flush == 1 as libc::c_int {
                _tr_align(s);
            } else if flush != 5 as libc::c_int {
                _tr_stored_block(
                    s,
                    0 as *mut libc::c_char,
                    0 as libc::c_long as ulg,
                    0 as libc::c_int,
                );
                if flush == 3 as libc::c_int {
                    *((*s).head)
                        .offset(
                            ((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt)
                                as isize,
                        ) = 0 as libc::c_int as Posf;
                    memset(
                        (*s).head as *mut Bytef as *mut libc::c_void,
                        0 as libc::c_int,
                        (((*s).hash_size).wrapping_sub(1 as libc::c_int as uInt)
                            as libc::c_ulong)
                            .wrapping_mul(
                                ::core::mem::size_of::<Posf>() as libc::c_ulong,
                            ),
                    );
                    if (*s).lookahead == 0 as libc::c_int as uInt {
                        (*s).strstart = 0 as libc::c_int as uInt;
                        (*s).block_start = 0 as libc::c_long;
                        (*s).insert = 0 as libc::c_int as uInt;
                    }
                }
            }
            flush_pending(strm);
            if (*strm).avail_out == 0 as libc::c_int as uInt {
                (*s).last_flush = -(1 as libc::c_int);
                return 0 as libc::c_int;
            }
        }
    }
    if flush != 4 as libc::c_int {
        return 0 as libc::c_int;
    }
    if (*s).wrap <= 0 as libc::c_int {
        return 1 as libc::c_int;
    }
    putShortMSB(s, ((*strm).adler >> 16 as libc::c_int) as uInt);
    putShortMSB(s, ((*strm).adler & 0xffff as libc::c_int as uLong) as uInt);
    flush_pending(strm);
    if (*s).wrap > 0 as libc::c_int {
        (*s).wrap = -(*s).wrap;
    }
    return if (*s).pending != 0 as libc::c_int as ulg {
        0 as libc::c_int
    } else {
        1 as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn deflateEnd(mut strm: z_streamp) -> libc::c_int {
    let mut status: libc::c_int = 0;
    if deflateStateCheck(strm) != 0 {
        return -(2 as libc::c_int);
    }
    status = (*(*strm).state).status;
    if !((*(*strm).state).pending_buf).is_null() {
        (Some(((*strm).zfree).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )((*strm).opaque, (*(*strm).state).pending_buf as voidpf);
    }
    if !((*(*strm).state).head).is_null() {
        (Some(((*strm).zfree).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )((*strm).opaque, (*(*strm).state).head as voidpf);
    }
    if !((*(*strm).state).prev).is_null() {
        (Some(((*strm).zfree).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )((*strm).opaque, (*(*strm).state).prev as voidpf);
    }
    if !((*(*strm).state).window).is_null() {
        (Some(((*strm).zfree).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )((*strm).opaque, (*(*strm).state).window as voidpf);
    }
    (Some(((*strm).zfree).expect("non-null function pointer")))
        .expect("non-null function pointer")((*strm).opaque, (*strm).state as voidpf);
    (*strm).state = 0 as *mut internal_state;
    return if status == 113 as libc::c_int {
        -(3 as libc::c_int)
    } else {
        0 as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn deflateCopy(
    mut dest: z_streamp,
    mut source: z_streamp,
) -> libc::c_int {
    let mut ds: *mut deflate_state = 0 as *mut deflate_state;
    let mut ss: *mut deflate_state = 0 as *mut deflate_state;
    if deflateStateCheck(source) != 0 || dest.is_null() {
        return -(2 as libc::c_int);
    }
    ss = (*source).state;
    memcpy(
        dest as voidpf,
        source as voidpf as *const libc::c_void,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong,
    );
    ds = (Some(((*dest).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*dest).opaque,
        1 as libc::c_int as uInt,
        ::core::mem::size_of::<deflate_state>() as libc::c_ulong as uInt,
    ) as *mut deflate_state;
    if ds.is_null() {
        return -(4 as libc::c_int);
    }
    (*dest).state = ds as *mut internal_state;
    memcpy(
        ds as voidpf,
        ss as voidpf as *const libc::c_void,
        ::core::mem::size_of::<deflate_state>() as libc::c_ulong,
    );
    (*ds).strm = dest;
    (*ds)
        .window = (Some(((*dest).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*dest).opaque,
        (*ds).w_size,
        (2 as libc::c_int as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Byte>() as libc::c_ulong) as uInt,
    ) as *mut Bytef;
    (*ds)
        .prev = (Some(((*dest).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*dest).opaque,
        (*ds).w_size,
        ::core::mem::size_of::<Pos>() as libc::c_ulong as uInt,
    ) as *mut Posf;
    (*ds)
        .head = (Some(((*dest).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*dest).opaque,
        (*ds).hash_size,
        ::core::mem::size_of::<Pos>() as libc::c_ulong as uInt,
    ) as *mut Posf;
    (*ds)
        .pending_buf = (Some(((*dest).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )((*dest).opaque, (*ds).lit_bufsize, 4 as libc::c_int as uInt) as *mut uchf;
    if ((*ds).window).is_null() || ((*ds).prev).is_null() || ((*ds).head).is_null()
        || ((*ds).pending_buf).is_null()
    {
        deflateEnd(dest);
        return -(4 as libc::c_int);
    }
    memcpy(
        (*ds).window as *mut libc::c_void,
        (*ss).window as *const libc::c_void,
        (((*ds).w_size * 2 as libc::c_int as uInt) as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Byte>() as libc::c_ulong),
    );
    memcpy(
        (*ds).prev as voidpf,
        (*ss).prev as voidpf as *const libc::c_void,
        ((*ds).w_size as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Pos>() as libc::c_ulong),
    );
    memcpy(
        (*ds).head as voidpf,
        (*ss).head as voidpf as *const libc::c_void,
        ((*ds).hash_size as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<Pos>() as libc::c_ulong),
    );
    memcpy(
        (*ds).pending_buf as *mut libc::c_void,
        (*ss).pending_buf as *const libc::c_void,
        (*ds).pending_buf_size as uInt as libc::c_ulong,
    );
    (*ds)
        .pending_out = ((*ds).pending_buf)
        .offset(
            ((*ss).pending_out).offset_from((*ss).pending_buf) as libc::c_long as isize,
        );
    (*ds).sym_buf = ((*ds).pending_buf).offset((*ds).lit_bufsize as isize);
    (*ds).l_desc.dyn_tree = ((*ds).dyn_ltree).as_mut_ptr();
    (*ds).d_desc.dyn_tree = ((*ds).dyn_dtree).as_mut_ptr();
    (*ds).bl_desc.dyn_tree = ((*ds).bl_tree).as_mut_ptr();
    return 0 as libc::c_int;
}
unsafe extern "C" fn longest_match(
    mut s: *mut deflate_state,
    mut cur_match: IPos,
) -> uInt {
    let mut chain_length: libc::c_uint = (*s).max_chain_length;
    let mut scan: *mut Bytef = ((*s).window).offset((*s).strstart as isize);
    let mut match_0: *mut Bytef = 0 as *mut Bytef;
    let mut len: libc::c_int = 0;
    let mut best_len: libc::c_int = (*s).prev_length as libc::c_int;
    let mut nice_match: libc::c_int = (*s).nice_match;
    let mut limit: IPos = if (*s).strstart
        > ((*s).w_size)
            .wrapping_sub(
                (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt,
            )
    {
        ((*s).strstart)
            .wrapping_sub(
                ((*s).w_size)
                    .wrapping_sub(
                        (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int)
                            as uInt,
                    ),
            )
    } else {
        0 as libc::c_int as libc::c_uint
    };
    let mut prev: *mut Posf = (*s).prev;
    let mut wmask: uInt = (*s).w_mask;
    let mut strend: *mut Bytef = ((*s).window)
        .offset((*s).strstart as isize)
        .offset(258 as libc::c_int as isize);
    let mut scan_end1: Byte = *scan.offset((best_len - 1 as libc::c_int) as isize);
    let mut scan_end: Byte = *scan.offset(best_len as isize);
    if (*s).prev_length >= (*s).good_match {
        chain_length >>= 2 as libc::c_int;
    }
    if nice_match as uInt > (*s).lookahead {
        nice_match = (*s).lookahead as libc::c_int;
    }
    loop {
        match_0 = ((*s).window).offset(cur_match as isize);
        if !(*match_0.offset(best_len as isize) as libc::c_int != scan_end as libc::c_int
            || *match_0.offset((best_len - 1 as libc::c_int) as isize) as libc::c_int
                != scan_end1 as libc::c_int
            || *match_0 as libc::c_int != *scan as libc::c_int
            || {
                match_0 = match_0.offset(1);
                *match_0 as libc::c_int
                    != *scan.offset(1 as libc::c_int as isize) as libc::c_int
            })
        {
            scan = scan.offset(2 as libc::c_int as isize);
            match_0 = match_0.offset(1);
            match_0;
            loop {
                scan = scan.offset(1);
                match_0 = match_0.offset(1);
                if !(*scan as libc::c_int == *match_0 as libc::c_int
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    }
                    && {
                        scan = scan.offset(1);
                        match_0 = match_0.offset(1);
                        *scan as libc::c_int == *match_0 as libc::c_int
                    } && scan < strend)
                {
                    break;
                }
            }
            len = 258 as libc::c_int
                - strend.offset_from(scan) as libc::c_long as libc::c_int;
            scan = strend.offset(-(258 as libc::c_int as isize));
            if len > best_len {
                (*s).match_start = cur_match;
                best_len = len;
                if len >= nice_match {
                    break;
                }
                scan_end1 = *scan.offset((best_len - 1 as libc::c_int) as isize);
                scan_end = *scan.offset(best_len as isize);
            }
        }
        cur_match = *prev.offset((cur_match & wmask) as isize) as IPos;
        if !(cur_match > limit
            && {
                chain_length = chain_length.wrapping_sub(1);
                chain_length != 0 as libc::c_int as libc::c_uint
            })
        {
            break;
        }
    }
    if best_len as uInt <= (*s).lookahead {
        return best_len as uInt;
    }
    return (*s).lookahead;
}
unsafe extern "C" fn deflate_stored(
    mut s: *mut deflate_state,
    mut flush: libc::c_int,
) -> block_state {
    let mut min_block: libc::c_uint = (if ((*s).pending_buf_size)
        .wrapping_sub(5 as libc::c_int as ulg) > (*s).w_size as ulg
    {
        (*s).w_size as ulg
    } else {
        ((*s).pending_buf_size).wrapping_sub(5 as libc::c_int as ulg)
    }) as libc::c_uint;
    let mut len: libc::c_uint = 0;
    let mut left: libc::c_uint = 0;
    let mut have: libc::c_uint = 0;
    let mut last: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    let mut used: libc::c_uint = (*(*s).strm).avail_in;
    loop {
        len = 65535 as libc::c_int as libc::c_uint;
        have = ((*s).bi_valid + 42 as libc::c_int >> 3 as libc::c_int) as libc::c_uint;
        if (*(*s).strm).avail_out < have {
            break;
        }
        have = ((*(*s).strm).avail_out).wrapping_sub(have);
        left = ((*s).strstart as libc::c_long - (*s).block_start) as libc::c_uint;
        if len as ulg > (left as ulg).wrapping_add((*(*s).strm).avail_in as ulg) {
            len = left.wrapping_add((*(*s).strm).avail_in);
        }
        if len > have {
            len = have;
        }
        if len < min_block
            && (len == 0 as libc::c_int as libc::c_uint && flush != 4 as libc::c_int
                || flush == 0 as libc::c_int
                || len != left.wrapping_add((*(*s).strm).avail_in))
        {
            break;
        }
        last = (if flush == 4 as libc::c_int
            && len == left.wrapping_add((*(*s).strm).avail_in)
        {
            1 as libc::c_int
        } else {
            0 as libc::c_int
        }) as libc::c_uint;
        _tr_stored_block(
            s,
            0 as *mut libc::c_char,
            0 as libc::c_long as ulg,
            last as libc::c_int,
        );
        *((*s).pending_buf)
            .offset(
                ((*s).pending).wrapping_sub(4 as libc::c_int as ulg) as isize,
            ) = len as Bytef;
        *((*s).pending_buf)
            .offset(
                ((*s).pending).wrapping_sub(3 as libc::c_int as ulg) as isize,
            ) = (len >> 8 as libc::c_int) as Bytef;
        *((*s).pending_buf)
            .offset(
                ((*s).pending).wrapping_sub(2 as libc::c_int as ulg) as isize,
            ) = !len as Bytef;
        *((*s).pending_buf)
            .offset(
                ((*s).pending).wrapping_sub(1 as libc::c_int as ulg) as isize,
            ) = (!len >> 8 as libc::c_int) as Bytef;
        flush_pending((*s).strm);
        if left != 0 {
            if left > len {
                left = len;
            }
            memcpy(
                (*(*s).strm).next_out as *mut libc::c_void,
                ((*s).window).offset((*s).block_start as isize) as *const libc::c_void,
                left as libc::c_ulong,
            );
            (*(*s).strm).next_out = ((*(*s).strm).next_out).offset(left as isize);
            (*(*s).strm)
                .avail_out = ((*(*s).strm).avail_out as libc::c_uint).wrapping_sub(left)
                as uInt as uInt;
            (*(*s).strm)
                .total_out = ((*(*s).strm).total_out).wrapping_add(left as uLong);
            (*s).block_start += left as libc::c_long;
            len = len.wrapping_sub(left);
        }
        if len != 0 {
            read_buf((*s).strm, (*(*s).strm).next_out, len);
            (*(*s).strm).next_out = ((*(*s).strm).next_out).offset(len as isize);
            (*(*s).strm)
                .avail_out = ((*(*s).strm).avail_out as libc::c_uint).wrapping_sub(len)
                as uInt as uInt;
            (*(*s).strm).total_out = ((*(*s).strm).total_out).wrapping_add(len as uLong);
        }
        if !(last == 0 as libc::c_int as libc::c_uint) {
            break;
        }
    }
    used = used.wrapping_sub((*(*s).strm).avail_in);
    if used != 0 {
        if used >= (*s).w_size {
            (*s).matches = 2 as libc::c_int as uInt;
            memcpy(
                (*s).window as *mut libc::c_void,
                ((*(*s).strm).next_in).offset(-((*s).w_size as isize))
                    as *const libc::c_void,
                (*s).w_size as libc::c_ulong,
            );
            (*s).strstart = (*s).w_size;
            (*s).insert = (*s).strstart;
        } else {
            if ((*s).window_size).wrapping_sub((*s).strstart as ulg) <= used as ulg {
                (*s).strstart = ((*s).strstart).wrapping_sub((*s).w_size);
                memcpy(
                    (*s).window as *mut libc::c_void,
                    ((*s).window).offset((*s).w_size as isize) as *const libc::c_void,
                    (*s).strstart as libc::c_ulong,
                );
                if (*s).matches < 2 as libc::c_int as uInt {
                    (*s).matches = ((*s).matches).wrapping_add(1);
                    (*s).matches;
                }
                if (*s).insert > (*s).strstart {
                    (*s).insert = (*s).strstart;
                }
            }
            memcpy(
                ((*s).window).offset((*s).strstart as isize) as *mut libc::c_void,
                ((*(*s).strm).next_in).offset(-(used as isize)) as *const libc::c_void,
                used as libc::c_ulong,
            );
            (*s)
                .strstart = ((*s).strstart as libc::c_uint).wrapping_add(used) as uInt
                as uInt;
            (*s)
                .insert = ((*s).insert as libc::c_uint)
                .wrapping_add(
                    if used > ((*s).w_size).wrapping_sub((*s).insert) {
                        ((*s).w_size).wrapping_sub((*s).insert)
                    } else {
                        used
                    },
                ) as uInt as uInt;
        }
        (*s).block_start = (*s).strstart as libc::c_long;
    }
    if (*s).high_water < (*s).strstart as ulg {
        (*s).high_water = (*s).strstart as ulg;
    }
    if last != 0 {
        return finish_done;
    }
    if flush != 0 as libc::c_int && flush != 4 as libc::c_int
        && (*(*s).strm).avail_in == 0 as libc::c_int as uInt
        && (*s).strstart as libc::c_long == (*s).block_start
    {
        return block_done;
    }
    have = ((*s).window_size).wrapping_sub((*s).strstart as ulg) as libc::c_uint;
    if (*(*s).strm).avail_in > have && (*s).block_start >= (*s).w_size as libc::c_long {
        (*s).block_start -= (*s).w_size as libc::c_long;
        (*s).strstart = ((*s).strstart).wrapping_sub((*s).w_size);
        memcpy(
            (*s).window as *mut libc::c_void,
            ((*s).window).offset((*s).w_size as isize) as *const libc::c_void,
            (*s).strstart as libc::c_ulong,
        );
        if (*s).matches < 2 as libc::c_int as uInt {
            (*s).matches = ((*s).matches).wrapping_add(1);
            (*s).matches;
        }
        have = have.wrapping_add((*s).w_size);
        if (*s).insert > (*s).strstart {
            (*s).insert = (*s).strstart;
        }
    }
    if have > (*(*s).strm).avail_in {
        have = (*(*s).strm).avail_in;
    }
    if have != 0 {
        read_buf((*s).strm, ((*s).window).offset((*s).strstart as isize), have);
        (*s)
            .strstart = ((*s).strstart as libc::c_uint).wrapping_add(have) as uInt
            as uInt;
        (*s)
            .insert = ((*s).insert as libc::c_uint)
            .wrapping_add(
                if have > ((*s).w_size).wrapping_sub((*s).insert) {
                    ((*s).w_size).wrapping_sub((*s).insert)
                } else {
                    have
                },
            ) as uInt as uInt;
    }
    if (*s).high_water < (*s).strstart as ulg {
        (*s).high_water = (*s).strstart as ulg;
    }
    have = ((*s).bi_valid + 42 as libc::c_int >> 3 as libc::c_int) as libc::c_uint;
    have = (if ((*s).pending_buf_size).wrapping_sub(have as ulg)
        > 65535 as libc::c_int as ulg
    {
        65535 as libc::c_int as ulg
    } else {
        ((*s).pending_buf_size).wrapping_sub(have as ulg)
    }) as libc::c_uint;
    min_block = if have > (*s).w_size { (*s).w_size } else { have };
    left = ((*s).strstart as libc::c_long - (*s).block_start) as libc::c_uint;
    if left >= min_block
        || (left != 0 || flush == 4 as libc::c_int) && flush != 0 as libc::c_int
            && (*(*s).strm).avail_in == 0 as libc::c_int as uInt && left <= have
    {
        len = if left > have { have } else { left };
        last = (if flush == 4 as libc::c_int
            && (*(*s).strm).avail_in == 0 as libc::c_int as uInt && len == left
        {
            1 as libc::c_int
        } else {
            0 as libc::c_int
        }) as libc::c_uint;
        _tr_stored_block(
            s,
            ((*s).window as *mut charf).offset((*s).block_start as isize),
            len as ulg,
            last as libc::c_int,
        );
        (*s).block_start += len as libc::c_long;
        flush_pending((*s).strm);
    }
    return (if last != 0 {
        finish_started as libc::c_int
    } else {
        need_more as libc::c_int
    }) as block_state;
}
unsafe extern "C" fn deflate_fast(
    mut s: *mut deflate_state,
    mut flush: libc::c_int,
) -> block_state {
    let mut hash_head: IPos = 0;
    let mut bflush: libc::c_int = 0;
    loop {
        if (*s).lookahead
            < (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt
        {
            fill_window(s);
            if (*s).lookahead
                < (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt
                && flush == 0 as libc::c_int
            {
                return need_more;
            }
            if (*s).lookahead == 0 as libc::c_int as uInt {
                break;
            }
        }
        hash_head = 0 as libc::c_int as IPos;
        if (*s).lookahead >= 3 as libc::c_int as uInt {
            (*s)
                .ins_h = ((*s).ins_h << (*s).hash_shift
                ^ *((*s).window)
                    .offset(
                        ((*s).strstart)
                            .wrapping_add((3 as libc::c_int - 1 as libc::c_int) as uInt)
                            as isize,
                    ) as uInt) & (*s).hash_mask;
            let ref mut fresh2 = *((*s).prev)
                .offset(((*s).strstart & (*s).w_mask) as isize);
            *fresh2 = *((*s).head).offset((*s).ins_h as isize);
            hash_head = *fresh2 as IPos;
            *((*s).head).offset((*s).ins_h as isize) = (*s).strstart as Pos;
        }
        if hash_head != 0 as libc::c_int as IPos
            && ((*s).strstart).wrapping_sub(hash_head)
                <= ((*s).w_size)
                    .wrapping_sub(
                        (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int)
                            as uInt,
                    )
        {
            (*s).match_length = longest_match(s, hash_head);
        }
        if (*s).match_length >= 3 as libc::c_int as uInt {
            let mut len: uch = ((*s).match_length).wrapping_sub(3 as libc::c_int as uInt)
                as uch;
            let mut dist: ush = ((*s).strstart).wrapping_sub((*s).match_start) as ush;
            let fresh3 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh3 as isize) = dist as uch;
            let fresh4 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf)
                .offset(
                    fresh4 as isize,
                ) = (dist as libc::c_int >> 8 as libc::c_int) as uch;
            let fresh5 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh5 as isize) = len;
            dist = dist.wrapping_sub(1);
            dist;
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq = ((*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq;
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq = ((*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            (*s).lookahead = ((*s).lookahead).wrapping_sub((*s).match_length);
            if (*s).match_length <= (*s).max_lazy_match
                && (*s).lookahead >= 3 as libc::c_int as uInt
            {
                (*s).match_length = ((*s).match_length).wrapping_sub(1);
                (*s).match_length;
                loop {
                    (*s).strstart = ((*s).strstart).wrapping_add(1);
                    (*s).strstart;
                    (*s)
                        .ins_h = ((*s).ins_h << (*s).hash_shift
                        ^ *((*s).window)
                            .offset(
                                ((*s).strstart)
                                    .wrapping_add((3 as libc::c_int - 1 as libc::c_int) as uInt)
                                    as isize,
                            ) as uInt) & (*s).hash_mask;
                    let ref mut fresh6 = *((*s).prev)
                        .offset(((*s).strstart & (*s).w_mask) as isize);
                    *fresh6 = *((*s).head).offset((*s).ins_h as isize);
                    hash_head = *fresh6 as IPos;
                    *((*s).head).offset((*s).ins_h as isize) = (*s).strstart as Pos;
                    (*s).match_length = ((*s).match_length).wrapping_sub(1);
                    if !((*s).match_length != 0 as libc::c_int as uInt) {
                        break;
                    }
                }
                (*s).strstart = ((*s).strstart).wrapping_add(1);
                (*s).strstart;
            } else {
                (*s).strstart = ((*s).strstart).wrapping_add((*s).match_length);
                (*s).match_length = 0 as libc::c_int as uInt;
                (*s).ins_h = *((*s).window).offset((*s).strstart as isize) as uInt;
                (*s)
                    .ins_h = ((*s).ins_h << (*s).hash_shift
                    ^ *((*s).window)
                        .offset(
                            ((*s).strstart).wrapping_add(1 as libc::c_int as uInt)
                                as isize,
                        ) as uInt) & (*s).hash_mask;
            }
        } else {
            let mut cc: uch = *((*s).window).offset((*s).strstart as isize);
            let fresh7 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh7 as isize) = 0 as libc::c_int as uchf;
            let fresh8 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh8 as isize) = 0 as libc::c_int as uchf;
            let fresh9 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh9 as isize) = cc;
            (*s)
                .dyn_ltree[cc as usize]
                .fc
                .freq = ((*s).dyn_ltree[cc as usize].fc.freq).wrapping_add(1);
            (*s).dyn_ltree[cc as usize].fc.freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            (*s).lookahead = ((*s).lookahead).wrapping_sub(1);
            (*s).lookahead;
            (*s).strstart = ((*s).strstart).wrapping_add(1);
            (*s).strstart;
        }
        if bflush != 0 {
            _tr_flush_block(
                s,
                if (*s).block_start >= 0 as libc::c_long {
                    &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                        as *mut Bytef as *mut charf
                } else {
                    0 as *mut charf
                },
                ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
                0 as libc::c_int,
            );
            (*s).block_start = (*s).strstart as libc::c_long;
            flush_pending((*s).strm);
            if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
                return (if 0 as libc::c_int != 0 {
                    finish_started as libc::c_int
                } else {
                    need_more as libc::c_int
                }) as block_state;
            }
        }
    }
    (*s)
        .insert = if (*s).strstart < (3 as libc::c_int - 1 as libc::c_int) as uInt {
        (*s).strstart
    } else {
        (3 as libc::c_int - 1 as libc::c_int) as uInt
    };
    if flush == 4 as libc::c_int {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            1 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 1 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
        return finish_done;
    }
    if (*s).sym_next != 0 {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            0 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 0 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
    }
    return block_done;
}
unsafe extern "C" fn deflate_slow(
    mut s: *mut deflate_state,
    mut flush: libc::c_int,
) -> block_state {
    let mut hash_head: IPos = 0;
    let mut bflush: libc::c_int = 0;
    loop {
        if (*s).lookahead
            < (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt
        {
            fill_window(s);
            if (*s).lookahead
                < (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int) as uInt
                && flush == 0 as libc::c_int
            {
                return need_more;
            }
            if (*s).lookahead == 0 as libc::c_int as uInt {
                break;
            }
        }
        hash_head = 0 as libc::c_int as IPos;
        if (*s).lookahead >= 3 as libc::c_int as uInt {
            (*s)
                .ins_h = ((*s).ins_h << (*s).hash_shift
                ^ *((*s).window)
                    .offset(
                        ((*s).strstart)
                            .wrapping_add((3 as libc::c_int - 1 as libc::c_int) as uInt)
                            as isize,
                    ) as uInt) & (*s).hash_mask;
            let ref mut fresh10 = *((*s).prev)
                .offset(((*s).strstart & (*s).w_mask) as isize);
            *fresh10 = *((*s).head).offset((*s).ins_h as isize);
            hash_head = *fresh10 as IPos;
            *((*s).head).offset((*s).ins_h as isize) = (*s).strstart as Pos;
        }
        (*s).prev_length = (*s).match_length;
        (*s).prev_match = (*s).match_start;
        (*s).match_length = (3 as libc::c_int - 1 as libc::c_int) as uInt;
        if hash_head != 0 as libc::c_int as IPos
            && (*s).prev_length < (*s).max_lazy_match
            && ((*s).strstart).wrapping_sub(hash_head)
                <= ((*s).w_size)
                    .wrapping_sub(
                        (258 as libc::c_int + 3 as libc::c_int + 1 as libc::c_int)
                            as uInt,
                    )
        {
            (*s).match_length = longest_match(s, hash_head);
            if (*s).match_length <= 5 as libc::c_int as uInt
                && (*s).strategy == 1 as libc::c_int
            {
                (*s).match_length = (3 as libc::c_int - 1 as libc::c_int) as uInt;
            }
        }
        if (*s).prev_length >= 3 as libc::c_int as uInt
            && (*s).match_length <= (*s).prev_length
        {
            let mut max_insert: uInt = ((*s).strstart)
                .wrapping_add((*s).lookahead)
                .wrapping_sub(3 as libc::c_int as uInt);
            let mut len: uch = ((*s).prev_length).wrapping_sub(3 as libc::c_int as uInt)
                as uch;
            let mut dist: ush = ((*s).strstart)
                .wrapping_sub(1 as libc::c_int as uInt)
                .wrapping_sub((*s).prev_match) as ush;
            let fresh11 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh11 as isize) = dist as uch;
            let fresh12 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf)
                .offset(
                    fresh12 as isize,
                ) = (dist as libc::c_int >> 8 as libc::c_int) as uch;
            let fresh13 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh13 as isize) = len;
            dist = dist.wrapping_sub(1);
            dist;
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq = ((*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq;
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq = ((*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            (*s)
                .lookahead = ((*s).lookahead)
                .wrapping_sub(((*s).prev_length).wrapping_sub(1 as libc::c_int as uInt));
            (*s).prev_length = ((*s).prev_length).wrapping_sub(2 as libc::c_int as uInt);
            loop {
                (*s).strstart = ((*s).strstart).wrapping_add(1);
                if (*s).strstart <= max_insert {
                    (*s)
                        .ins_h = ((*s).ins_h << (*s).hash_shift
                        ^ *((*s).window)
                            .offset(
                                ((*s).strstart)
                                    .wrapping_add((3 as libc::c_int - 1 as libc::c_int) as uInt)
                                    as isize,
                            ) as uInt) & (*s).hash_mask;
                    let ref mut fresh14 = *((*s).prev)
                        .offset(((*s).strstart & (*s).w_mask) as isize);
                    *fresh14 = *((*s).head).offset((*s).ins_h as isize);
                    hash_head = *fresh14 as IPos;
                    *((*s).head).offset((*s).ins_h as isize) = (*s).strstart as Pos;
                }
                (*s).prev_length = ((*s).prev_length).wrapping_sub(1);
                if !((*s).prev_length != 0 as libc::c_int as uInt) {
                    break;
                }
            }
            (*s).match_available = 0 as libc::c_int;
            (*s).match_length = (3 as libc::c_int - 1 as libc::c_int) as uInt;
            (*s).strstart = ((*s).strstart).wrapping_add(1);
            (*s).strstart;
            if bflush != 0 {
                _tr_flush_block(
                    s,
                    if (*s).block_start >= 0 as libc::c_long {
                        &mut *((*s).window)
                            .offset((*s).block_start as libc::c_uint as isize)
                            as *mut Bytef as *mut charf
                    } else {
                        0 as *mut charf
                    },
                    ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
                    0 as libc::c_int,
                );
                (*s).block_start = (*s).strstart as libc::c_long;
                flush_pending((*s).strm);
                if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
                    return (if 0 as libc::c_int != 0 {
                        finish_started as libc::c_int
                    } else {
                        need_more as libc::c_int
                    }) as block_state;
                }
            }
        } else if (*s).match_available != 0 {
            let mut cc: uch = *((*s).window)
                .offset(((*s).strstart).wrapping_sub(1 as libc::c_int as uInt) as isize);
            let fresh15 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh15 as isize) = 0 as libc::c_int as uchf;
            let fresh16 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh16 as isize) = 0 as libc::c_int as uchf;
            let fresh17 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh17 as isize) = cc;
            (*s)
                .dyn_ltree[cc as usize]
                .fc
                .freq = ((*s).dyn_ltree[cc as usize].fc.freq).wrapping_add(1);
            (*s).dyn_ltree[cc as usize].fc.freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            if bflush != 0 {
                _tr_flush_block(
                    s,
                    if (*s).block_start >= 0 as libc::c_long {
                        &mut *((*s).window)
                            .offset((*s).block_start as libc::c_uint as isize)
                            as *mut Bytef as *mut charf
                    } else {
                        0 as *mut charf
                    },
                    ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
                    0 as libc::c_int,
                );
                (*s).block_start = (*s).strstart as libc::c_long;
                flush_pending((*s).strm);
            }
            (*s).strstart = ((*s).strstart).wrapping_add(1);
            (*s).strstart;
            (*s).lookahead = ((*s).lookahead).wrapping_sub(1);
            (*s).lookahead;
            if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
                return need_more;
            }
        } else {
            (*s).match_available = 1 as libc::c_int;
            (*s).strstart = ((*s).strstart).wrapping_add(1);
            (*s).strstart;
            (*s).lookahead = ((*s).lookahead).wrapping_sub(1);
            (*s).lookahead;
        }
    }
    if (*s).match_available != 0 {
        let mut cc_0: uch = *((*s).window)
            .offset(((*s).strstart).wrapping_sub(1 as libc::c_int as uInt) as isize);
        let fresh18 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh18 as isize) = 0 as libc::c_int as uchf;
        let fresh19 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh19 as isize) = 0 as libc::c_int as uchf;
        let fresh20 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh20 as isize) = cc_0;
        (*s)
            .dyn_ltree[cc_0 as usize]
            .fc
            .freq = ((*s).dyn_ltree[cc_0 as usize].fc.freq).wrapping_add(1);
        (*s).dyn_ltree[cc_0 as usize].fc.freq;
        bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
        (*s).match_available = 0 as libc::c_int;
    }
    (*s)
        .insert = if (*s).strstart < (3 as libc::c_int - 1 as libc::c_int) as uInt {
        (*s).strstart
    } else {
        (3 as libc::c_int - 1 as libc::c_int) as uInt
    };
    if flush == 4 as libc::c_int {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            1 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 1 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
        return finish_done;
    }
    if (*s).sym_next != 0 {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            0 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 0 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
    }
    return block_done;
}
unsafe extern "C" fn deflate_rle(
    mut s: *mut deflate_state,
    mut flush: libc::c_int,
) -> block_state {
    let mut bflush: libc::c_int = 0;
    let mut prev: uInt = 0;
    let mut scan: *mut Bytef = 0 as *mut Bytef;
    let mut strend: *mut Bytef = 0 as *mut Bytef;
    loop {
        if (*s).lookahead <= 258 as libc::c_int as uInt {
            fill_window(s);
            if (*s).lookahead <= 258 as libc::c_int as uInt && flush == 0 as libc::c_int
            {
                return need_more;
            }
            if (*s).lookahead == 0 as libc::c_int as uInt {
                break;
            }
        }
        (*s).match_length = 0 as libc::c_int as uInt;
        if (*s).lookahead >= 3 as libc::c_int as uInt
            && (*s).strstart > 0 as libc::c_int as uInt
        {
            scan = ((*s).window)
                .offset((*s).strstart as isize)
                .offset(-(1 as libc::c_int as isize));
            prev = *scan as uInt;
            scan = scan.offset(1);
            if prev == *scan as uInt
                && {
                    scan = scan.offset(1);
                    prev == *scan as uInt
                }
                && {
                    scan = scan.offset(1);
                    prev == *scan as uInt
                }
            {
                strend = ((*s).window)
                    .offset((*s).strstart as isize)
                    .offset(258 as libc::c_int as isize);
                loop {
                    scan = scan.offset(1);
                    if !(prev == *scan as uInt
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        }
                        && {
                            scan = scan.offset(1);
                            prev == *scan as uInt
                        } && scan < strend)
                    {
                        break;
                    }
                }
                (*s)
                    .match_length = (258 as libc::c_int as uInt)
                    .wrapping_sub(strend.offset_from(scan) as libc::c_long as uInt);
                if (*s).match_length > (*s).lookahead {
                    (*s).match_length = (*s).lookahead;
                }
            }
        }
        if (*s).match_length >= 3 as libc::c_int as uInt {
            let mut len: uch = ((*s).match_length).wrapping_sub(3 as libc::c_int as uInt)
                as uch;
            let mut dist: ush = 1 as libc::c_int as ush;
            let fresh21 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh21 as isize) = dist as uch;
            let fresh22 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf)
                .offset(
                    fresh22 as isize,
                ) = (dist as libc::c_int >> 8 as libc::c_int) as uch;
            let fresh23 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh23 as isize) = len;
            dist = dist.wrapping_sub(1);
            dist;
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq = ((*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_ltree[(*_length_code.as_ptr().offset(len as isize) as libc::c_int
                    + 256 as libc::c_int + 1 as libc::c_int) as usize]
                .fc
                .freq;
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq = ((*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq)
                .wrapping_add(1);
            (*s)
                .dyn_dtree[(if (dist as libc::c_int) < 256 as libc::c_int {
                    *_dist_code.as_ptr().offset(dist as isize) as libc::c_int
                } else {
                    *_dist_code
                        .as_ptr()
                        .offset(
                            (256 as libc::c_int
                                + (dist as libc::c_int >> 7 as libc::c_int)) as isize,
                        ) as libc::c_int
                }) as usize]
                .fc
                .freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            (*s).lookahead = ((*s).lookahead).wrapping_sub((*s).match_length);
            (*s).strstart = ((*s).strstart).wrapping_add((*s).match_length);
            (*s).match_length = 0 as libc::c_int as uInt;
        } else {
            let mut cc: uch = *((*s).window).offset((*s).strstart as isize);
            let fresh24 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh24 as isize) = 0 as libc::c_int as uchf;
            let fresh25 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh25 as isize) = 0 as libc::c_int as uchf;
            let fresh26 = (*s).sym_next;
            (*s).sym_next = ((*s).sym_next).wrapping_add(1);
            *((*s).sym_buf).offset(fresh26 as isize) = cc;
            (*s)
                .dyn_ltree[cc as usize]
                .fc
                .freq = ((*s).dyn_ltree[cc as usize].fc.freq).wrapping_add(1);
            (*s).dyn_ltree[cc as usize].fc.freq;
            bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
            (*s).lookahead = ((*s).lookahead).wrapping_sub(1);
            (*s).lookahead;
            (*s).strstart = ((*s).strstart).wrapping_add(1);
            (*s).strstart;
        }
        if bflush != 0 {
            _tr_flush_block(
                s,
                if (*s).block_start >= 0 as libc::c_long {
                    &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                        as *mut Bytef as *mut charf
                } else {
                    0 as *mut charf
                },
                ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
                0 as libc::c_int,
            );
            (*s).block_start = (*s).strstart as libc::c_long;
            flush_pending((*s).strm);
            if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
                return (if 0 as libc::c_int != 0 {
                    finish_started as libc::c_int
                } else {
                    need_more as libc::c_int
                }) as block_state;
            }
        }
    }
    (*s).insert = 0 as libc::c_int as uInt;
    if flush == 4 as libc::c_int {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            1 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 1 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
        return finish_done;
    }
    if (*s).sym_next != 0 {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            0 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 0 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
    }
    return block_done;
}
unsafe extern "C" fn deflate_huff(
    mut s: *mut deflate_state,
    mut flush: libc::c_int,
) -> block_state {
    let mut bflush: libc::c_int = 0;
    loop {
        if (*s).lookahead == 0 as libc::c_int as uInt {
            fill_window(s);
            if (*s).lookahead == 0 as libc::c_int as uInt {
                if flush == 0 as libc::c_int {
                    return need_more;
                }
                break;
            }
        }
        (*s).match_length = 0 as libc::c_int as uInt;
        let mut cc: uch = *((*s).window).offset((*s).strstart as isize);
        let fresh27 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh27 as isize) = 0 as libc::c_int as uchf;
        let fresh28 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh28 as isize) = 0 as libc::c_int as uchf;
        let fresh29 = (*s).sym_next;
        (*s).sym_next = ((*s).sym_next).wrapping_add(1);
        *((*s).sym_buf).offset(fresh29 as isize) = cc;
        (*s)
            .dyn_ltree[cc as usize]
            .fc
            .freq = ((*s).dyn_ltree[cc as usize].fc.freq).wrapping_add(1);
        (*s).dyn_ltree[cc as usize].fc.freq;
        bflush = ((*s).sym_next == (*s).sym_end) as libc::c_int;
        (*s).lookahead = ((*s).lookahead).wrapping_sub(1);
        (*s).lookahead;
        (*s).strstart = ((*s).strstart).wrapping_add(1);
        (*s).strstart;
        if bflush != 0 {
            _tr_flush_block(
                s,
                if (*s).block_start >= 0 as libc::c_long {
                    &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                        as *mut Bytef as *mut charf
                } else {
                    0 as *mut charf
                },
                ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
                0 as libc::c_int,
            );
            (*s).block_start = (*s).strstart as libc::c_long;
            flush_pending((*s).strm);
            if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
                return (if 0 as libc::c_int != 0 {
                    finish_started as libc::c_int
                } else {
                    need_more as libc::c_int
                }) as block_state;
            }
        }
    }
    (*s).insert = 0 as libc::c_int as uInt;
    if flush == 4 as libc::c_int {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            1 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 1 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
        return finish_done;
    }
    if (*s).sym_next != 0 {
        _tr_flush_block(
            s,
            if (*s).block_start >= 0 as libc::c_long {
                &mut *((*s).window).offset((*s).block_start as libc::c_uint as isize)
                    as *mut Bytef as *mut charf
            } else {
                0 as *mut charf
            },
            ((*s).strstart as libc::c_long - (*s).block_start) as ulg,
            0 as libc::c_int,
        );
        (*s).block_start = (*s).strstart as libc::c_long;
        flush_pending((*s).strm);
        if (*(*s).strm).avail_out == 0 as libc::c_int as uInt {
            return (if 0 as libc::c_int != 0 {
                finish_started as libc::c_int
            } else {
                need_more as libc::c_int
            }) as block_state;
        }
    }
    return block_done;
}
