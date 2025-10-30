use ::libc;
extern "C" {
    pub type internal_state;
}
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
pub type z_streamp = *mut z_stream;
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
pub type gz_header = gz_header_s;
pub type gz_headerp = *mut gz_header;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct code {
    pub op: libc::c_uchar,
    pub bits: libc::c_uchar,
    pub val: libc::c_ushort,
}
pub type inflate_mode = libc::c_uint;
pub const SYNC: inflate_mode = 16211;
pub const MEM: inflate_mode = 16210;
pub const BAD: inflate_mode = 16209;
pub const DONE: inflate_mode = 16208;
pub const LENGTH: inflate_mode = 16207;
pub const CHECK: inflate_mode = 16206;
pub const LIT: inflate_mode = 16205;
pub const MATCH: inflate_mode = 16204;
pub const DISTEXT: inflate_mode = 16203;
pub const DIST: inflate_mode = 16202;
pub const LENEXT: inflate_mode = 16201;
pub const LEN: inflate_mode = 16200;
pub const LEN_: inflate_mode = 16199;
pub const CODELENS: inflate_mode = 16198;
pub const LENLENS: inflate_mode = 16197;
pub const TABLE: inflate_mode = 16196;
pub const COPY: inflate_mode = 16195;
pub const COPY_: inflate_mode = 16194;
pub const STORED: inflate_mode = 16193;
pub const TYPEDO: inflate_mode = 16192;
pub const TYPE: inflate_mode = 16191;
pub const DICT: inflate_mode = 16190;
pub const DICTID: inflate_mode = 16189;
pub const HCRC: inflate_mode = 16188;
pub const COMMENT: inflate_mode = 16187;
pub const NAME: inflate_mode = 16186;
pub const EXTRA: inflate_mode = 16185;
pub const EXLEN: inflate_mode = 16184;
pub const OS: inflate_mode = 16183;
pub const TIME: inflate_mode = 16182;
pub const FLAGS: inflate_mode = 16181;
pub const HEAD: inflate_mode = 16180;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct inflate_state {
    pub strm: z_streamp,
    pub mode: inflate_mode,
    pub last: libc::c_int,
    pub wrap: libc::c_int,
    pub havedict: libc::c_int,
    pub flags: libc::c_int,
    pub dmax: libc::c_uint,
    pub check: libc::c_ulong,
    pub total: libc::c_ulong,
    pub head: gz_headerp,
    pub wbits: libc::c_uint,
    pub wsize: libc::c_uint,
    pub whave: libc::c_uint,
    pub wnext: libc::c_uint,
    pub window: *mut libc::c_uchar,
    pub hold: libc::c_ulong,
    pub bits: libc::c_uint,
    pub length: libc::c_uint,
    pub offset: libc::c_uint,
    pub extra: libc::c_uint,
    pub lencode: *const code,
    pub distcode: *const code,
    pub lenbits: libc::c_uint,
    pub distbits: libc::c_uint,
    pub ncode: libc::c_uint,
    pub nlen: libc::c_uint,
    pub ndist: libc::c_uint,
    pub have: libc::c_uint,
    pub next: *mut code,
    pub lens: [libc::c_ushort; 320],
    pub work: [libc::c_ushort; 288],
    pub codes: [code; 1444],
    pub sane: libc::c_int,
    pub back: libc::c_int,
    pub was: libc::c_uint,
}
#[no_mangle]
pub unsafe extern "C" fn inflate_fast(mut strm: z_streamp, mut start: libc::c_uint) {
    let mut state: *mut inflate_state = 0 as *mut inflate_state;
    let mut in_0: *const libc::c_uchar = 0 as *const libc::c_uchar;
    let mut last: *const libc::c_uchar = 0 as *const libc::c_uchar;
    let mut out: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut beg: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut end: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut wsize: libc::c_uint = 0;
    let mut whave: libc::c_uint = 0;
    let mut wnext: libc::c_uint = 0;
    let mut window: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut hold: libc::c_ulong = 0;
    let mut bits: libc::c_uint = 0;
    let mut lcode: *const code = 0 as *const code;
    let mut dcode: *const code = 0 as *const code;
    let mut lmask: libc::c_uint = 0;
    let mut dmask: libc::c_uint = 0;
    let mut here: *const code = 0 as *const code;
    let mut op: libc::c_uint = 0;
    let mut len: libc::c_uint = 0;
    let mut dist: libc::c_uint = 0;
    let mut from: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    state = (*strm).state as *mut inflate_state;
    in_0 = (*strm).next_in;
    last = in_0
        .offset(((*strm).avail_in).wrapping_sub(5 as libc::c_int as uInt) as isize);
    out = (*strm).next_out;
    beg = out.offset(-(start.wrapping_sub((*strm).avail_out) as isize));
    end = out
        .offset(((*strm).avail_out).wrapping_sub(257 as libc::c_int as uInt) as isize);
    wsize = (*state).wsize;
    whave = (*state).whave;
    wnext = (*state).wnext;
    window = (*state).window;
    hold = (*state).hold;
    bits = (*state).bits;
    lcode = (*state).lencode;
    dcode = (*state).distcode;
    lmask = ((1 as libc::c_uint) << (*state).lenbits)
        .wrapping_sub(1 as libc::c_int as libc::c_uint);
    dmask = ((1 as libc::c_uint) << (*state).distbits)
        .wrapping_sub(1 as libc::c_int as libc::c_uint);
    let mut current_block_141: u64;
    's_94: loop {
        if bits < 15 as libc::c_int as libc::c_uint {
            let fresh0 = in_0;
            in_0 = in_0.offset(1);
            hold = hold.wrapping_add((*fresh0 as libc::c_ulong) << bits);
            bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
            let fresh1 = in_0;
            in_0 = in_0.offset(1);
            hold = hold.wrapping_add((*fresh1 as libc::c_ulong) << bits);
            bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
        }
        here = lcode.offset((hold & lmask as libc::c_ulong) as isize);
        loop {
            op = (*here).bits as libc::c_uint;
            hold >>= op;
            bits = bits.wrapping_sub(op);
            op = (*here).op as libc::c_uint;
            if op == 0 as libc::c_int as libc::c_uint {
                let fresh2 = out;
                out = out.offset(1);
                *fresh2 = (*here).val as libc::c_uchar;
                current_block_141 = 5689001924483802034;
                break;
            } else if op & 16 as libc::c_int as libc::c_uint != 0 {
                len = (*here).val as libc::c_uint;
                op &= 15 as libc::c_int as libc::c_uint;
                if op != 0 {
                    if bits < op {
                        let fresh3 = in_0;
                        in_0 = in_0.offset(1);
                        hold = hold.wrapping_add((*fresh3 as libc::c_ulong) << bits);
                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                    }
                    len = len
                        .wrapping_add(
                            hold as libc::c_uint
                                & ((1 as libc::c_uint) << op)
                                    .wrapping_sub(1 as libc::c_int as libc::c_uint),
                        );
                    hold >>= op;
                    bits = bits.wrapping_sub(op);
                }
                if bits < 15 as libc::c_int as libc::c_uint {
                    let fresh4 = in_0;
                    in_0 = in_0.offset(1);
                    hold = hold.wrapping_add((*fresh4 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                    let fresh5 = in_0;
                    in_0 = in_0.offset(1);
                    hold = hold.wrapping_add((*fresh5 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                }
                here = dcode.offset((hold & dmask as libc::c_ulong) as isize);
                current_block_141 = 13635769618465359777;
                break;
            } else if op & 64 as libc::c_int as libc::c_uint
                == 0 as libc::c_int as libc::c_uint
            {
                here = lcode
                    .offset((*here).val as libc::c_int as isize)
                    .offset(
                        (hold
                            & ((1 as libc::c_uint) << op)
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                as libc::c_ulong) as isize,
                    );
            } else if op & 32 as libc::c_int as libc::c_uint != 0 {
                current_block_141 = 13505557363059842426;
                break;
            } else {
                current_block_141 = 9180031981464905198;
                break;
            }
        }
        match current_block_141 {
            13635769618465359777 => {
                loop {
                    op = (*here).bits as libc::c_uint;
                    hold >>= op;
                    bits = bits.wrapping_sub(op);
                    op = (*here).op as libc::c_uint;
                    if op & 16 as libc::c_int as libc::c_uint != 0 {
                        dist = (*here).val as libc::c_uint;
                        op &= 15 as libc::c_int as libc::c_uint;
                        if bits < op {
                            let fresh6 = in_0;
                            in_0 = in_0.offset(1);
                            hold = hold.wrapping_add((*fresh6 as libc::c_ulong) << bits);
                            bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                            if bits < op {
                                let fresh7 = in_0;
                                in_0 = in_0.offset(1);
                                hold = hold
                                    .wrapping_add((*fresh7 as libc::c_ulong) << bits);
                                bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                            }
                        }
                        dist = dist
                            .wrapping_add(
                                hold as libc::c_uint
                                    & ((1 as libc::c_uint) << op)
                                        .wrapping_sub(1 as libc::c_int as libc::c_uint),
                            );
                        hold >>= op;
                        bits = bits.wrapping_sub(op);
                        op = out.offset_from(beg) as libc::c_long as libc::c_uint;
                        if dist > op {
                            current_block_141 = 5235537862154438448;
                            break;
                        } else {
                            current_block_141 = 6072622540298447352;
                            break;
                        }
                    } else if op & 64 as libc::c_int as libc::c_uint
                        == 0 as libc::c_int as libc::c_uint
                    {
                        here = dcode
                            .offset((*here).val as libc::c_int as isize)
                            .offset(
                                (hold
                                    & ((1 as libc::c_uint) << op)
                                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                        as libc::c_ulong) as isize,
                            );
                    } else {
                        (*strm)
                            .msg = b"invalid distance code\0" as *const u8
                            as *const libc::c_char as *mut libc::c_char;
                        (*state).mode = BAD;
                        break 's_94;
                    }
                }
                match current_block_141 {
                    6072622540298447352 => {
                        from = out.offset(-(dist as isize));
                        loop {
                            let fresh26 = from;
                            from = from.offset(1);
                            let fresh27 = out;
                            out = out.offset(1);
                            *fresh27 = *fresh26;
                            let fresh28 = from;
                            from = from.offset(1);
                            let fresh29 = out;
                            out = out.offset(1);
                            *fresh29 = *fresh28;
                            let fresh30 = from;
                            from = from.offset(1);
                            let fresh31 = out;
                            out = out.offset(1);
                            *fresh31 = *fresh30;
                            len = len.wrapping_sub(3 as libc::c_int as libc::c_uint);
                            if !(len > 2 as libc::c_int as libc::c_uint) {
                                break;
                            }
                        }
                        if len != 0 {
                            let fresh32 = from;
                            from = from.offset(1);
                            let fresh33 = out;
                            out = out.offset(1);
                            *fresh33 = *fresh32;
                            if len > 1 as libc::c_int as libc::c_uint {
                                let fresh34 = from;
                                from = from.offset(1);
                                let fresh35 = out;
                                out = out.offset(1);
                                *fresh35 = *fresh34;
                            }
                        }
                    }
                    _ => {
                        op = dist.wrapping_sub(op);
                        if op > whave {
                            if (*state).sane != 0 {
                                (*strm)
                                    .msg = b"invalid distance too far back\0" as *const u8
                                    as *const libc::c_char as *mut libc::c_char;
                                (*state).mode = BAD;
                                break;
                            }
                        }
                        from = window;
                        if wnext == 0 as libc::c_int as libc::c_uint {
                            from = from.offset(wsize.wrapping_sub(op) as isize);
                            if op < len {
                                len = len.wrapping_sub(op);
                                loop {
                                    let fresh8 = from;
                                    from = from.offset(1);
                                    let fresh9 = out;
                                    out = out.offset(1);
                                    *fresh9 = *fresh8;
                                    op = op.wrapping_sub(1);
                                    if !(op != 0) {
                                        break;
                                    }
                                }
                                from = out.offset(-(dist as isize));
                            }
                        } else if wnext < op {
                            from = from
                                .offset(
                                    wsize.wrapping_add(wnext).wrapping_sub(op) as isize,
                                );
                            op = op.wrapping_sub(wnext);
                            if op < len {
                                len = len.wrapping_sub(op);
                                loop {
                                    let fresh10 = from;
                                    from = from.offset(1);
                                    let fresh11 = out;
                                    out = out.offset(1);
                                    *fresh11 = *fresh10;
                                    op = op.wrapping_sub(1);
                                    if !(op != 0) {
                                        break;
                                    }
                                }
                                from = window;
                                if wnext < len {
                                    op = wnext;
                                    len = len.wrapping_sub(op);
                                    loop {
                                        let fresh12 = from;
                                        from = from.offset(1);
                                        let fresh13 = out;
                                        out = out.offset(1);
                                        *fresh13 = *fresh12;
                                        op = op.wrapping_sub(1);
                                        if !(op != 0) {
                                            break;
                                        }
                                    }
                                    from = out.offset(-(dist as isize));
                                }
                            }
                        } else {
                            from = from.offset(wnext.wrapping_sub(op) as isize);
                            if op < len {
                                len = len.wrapping_sub(op);
                                loop {
                                    let fresh14 = from;
                                    from = from.offset(1);
                                    let fresh15 = out;
                                    out = out.offset(1);
                                    *fresh15 = *fresh14;
                                    op = op.wrapping_sub(1);
                                    if !(op != 0) {
                                        break;
                                    }
                                }
                                from = out.offset(-(dist as isize));
                            }
                        }
                        while len > 2 as libc::c_int as libc::c_uint {
                            let fresh16 = from;
                            from = from.offset(1);
                            let fresh17 = out;
                            out = out.offset(1);
                            *fresh17 = *fresh16;
                            let fresh18 = from;
                            from = from.offset(1);
                            let fresh19 = out;
                            out = out.offset(1);
                            *fresh19 = *fresh18;
                            let fresh20 = from;
                            from = from.offset(1);
                            let fresh21 = out;
                            out = out.offset(1);
                            *fresh21 = *fresh20;
                            len = len.wrapping_sub(3 as libc::c_int as libc::c_uint);
                        }
                        if len != 0 {
                            let fresh22 = from;
                            from = from.offset(1);
                            let fresh23 = out;
                            out = out.offset(1);
                            *fresh23 = *fresh22;
                            if len > 1 as libc::c_int as libc::c_uint {
                                let fresh24 = from;
                                from = from.offset(1);
                                let fresh25 = out;
                                out = out.offset(1);
                                *fresh25 = *fresh24;
                            }
                        }
                    }
                }
            }
            9180031981464905198 => {
                (*strm)
                    .msg = b"invalid literal/length code\0" as *const u8
                    as *const libc::c_char as *mut libc::c_char;
                (*state).mode = BAD;
                break;
            }
            13505557363059842426 => {
                (*state).mode = TYPE;
                break;
            }
            _ => {}
        }
        if !(in_0 < last && out < end) {
            break;
        }
    }
    len = bits >> 3 as libc::c_int;
    in_0 = in_0.offset(-(len as isize));
    bits = bits.wrapping_sub(len << 3 as libc::c_int);
    hold
        &= ((1 as libc::c_uint) << bits).wrapping_sub(1 as libc::c_int as libc::c_uint)
            as libc::c_ulong;
    (*strm).next_in = in_0;
    (*strm).next_out = out;
    (*strm)
        .avail_in = (if in_0 < last {
        5 as libc::c_int as libc::c_long + last.offset_from(in_0) as libc::c_long
    } else {
        5 as libc::c_int as libc::c_long - in_0.offset_from(last) as libc::c_long
    }) as libc::c_uint;
    (*strm)
        .avail_out = (if out < end {
        257 as libc::c_int as libc::c_long + end.offset_from(out) as libc::c_long
    } else {
        257 as libc::c_int as libc::c_long - out.offset_from(end) as libc::c_long
    }) as libc::c_uint;
    (*state).hold = hold;
    (*state).bits = bits;
}
