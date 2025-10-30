use ::libc;
extern "C" {
    pub type internal_state;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn zcalloc(opaque: voidpf, items: libc::c_uint, size: libc::c_uint) -> voidpf;
    fn zcfree(opaque: voidpf, ptr: voidpf);
    fn inflate_table(
        type_0: codetype,
        lens: *mut libc::c_ushort,
        codes: libc::c_uint,
        table: *mut *mut code,
        bits: *mut libc::c_uint,
        work: *mut libc::c_ushort,
    ) -> libc::c_int;
    fn inflate_fast(strm: z_streamp, start: libc::c_uint);
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
pub type in_func = Option::<
    unsafe extern "C" fn(*mut libc::c_void, *mut *const libc::c_uchar) -> libc::c_uint,
>;
pub type out_func = Option::<
    unsafe extern "C" fn(
        *mut libc::c_void,
        *mut libc::c_uchar,
        libc::c_uint,
    ) -> libc::c_int,
>;
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
pub type codetype = libc::c_uint;
pub const DISTS: codetype = 2;
pub const LENS: codetype = 1;
pub const CODES: codetype = 0;
#[no_mangle]
pub unsafe extern "C" fn inflateBackInit_(
    mut strm: z_streamp,
    mut windowBits: libc::c_int,
    mut window: *mut libc::c_uchar,
    mut version: *const libc::c_char,
    mut stream_size: libc::c_int,
) -> libc::c_int {
    let mut state: *mut inflate_state = 0 as *mut inflate_state;
    if version.is_null()
        || *version.offset(0 as libc::c_int as isize) as libc::c_int
            != (*::core::mem::transmute::<
                &[u8; 12],
                &[libc::c_char; 12],
            >(b"1.3-optipng\0"))[0 as libc::c_int as usize] as libc::c_int
        || stream_size
            != ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int
    {
        return -(6 as libc::c_int);
    }
    if strm.is_null() || window.is_null() || windowBits < 8 as libc::c_int
        || windowBits > 15 as libc::c_int
    {
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
    state = (Some(((*strm).zalloc).expect("non-null function pointer")))
        .expect(
            "non-null function pointer",
        )(
        (*strm).opaque,
        1 as libc::c_int as uInt,
        ::core::mem::size_of::<inflate_state>() as libc::c_ulong as uInt,
    ) as *mut inflate_state;
    if state.is_null() {
        return -(4 as libc::c_int);
    }
    (*strm).state = state as *mut internal_state;
    (*state).dmax = 32768 as libc::c_uint;
    (*state).wbits = windowBits as uInt;
    (*state).wsize = (1 as libc::c_uint) << windowBits;
    (*state).window = window;
    (*state).wnext = 0 as libc::c_int as libc::c_uint;
    (*state).whave = 0 as libc::c_int as libc::c_uint;
    (*state).sane = 1 as libc::c_int;
    return 0 as libc::c_int;
}
unsafe extern "C" fn fixedtables(mut state: *mut inflate_state) {
    static mut lenfix: [code; 512] = [
        {
            let mut init = code {
                op: 96 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 80 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 16 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 115 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 112 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 48 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 192 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 96 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 32 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 160 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 128 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 64 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 224 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 88 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 24 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 144 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 120 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 56 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 208 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 104 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 40 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 176 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 136 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 72 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 240 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 84 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 20 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 227 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 116 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 52 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 200 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 100 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 36 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 168 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 132 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 68 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 232 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 92 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 28 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 152 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 124 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 60 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 216 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 108 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 44 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 184 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 12 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 140 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 76 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 248 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 82 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 18 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 163 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 114 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 50 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 196 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 98 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 34 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 164 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 2 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 130 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 66 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 228 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 90 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 26 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 148 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 122 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 58 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 212 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 106 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 42 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 180 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 138 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 74 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 244 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 86 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 22 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 118 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 54 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 204 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 102 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 38 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 172 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 134 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 70 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 236 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 94 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 30 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 156 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 126 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 62 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 220 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 110 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 46 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 188 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 14 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 142 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 78 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 252 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 96 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 81 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 131 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 113 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 49 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 194 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 97 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 33 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 162 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 1 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 129 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 65 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 226 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 89 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 25 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 146 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 121 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 57 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 210 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 105 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 41 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 178 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 137 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 73 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 242 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 85 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 21 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 258 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 117 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 53 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 202 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 101 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 37 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 170 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 133 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 69 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 234 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 93 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 29 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 154 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 125 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 61 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 218 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 109 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 45 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 186 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 141 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 77 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 250 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 195 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 115 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 198 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 166 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 131 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 230 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 91 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 150 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 123 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 214 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 107 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 182 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 139 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 75 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 246 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 87 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 119 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 55 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 206 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 103 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 39 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 174 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 135 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 71 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 238 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 95 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 158 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 127 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 63 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 222 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 111 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 47 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 190 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 143 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 79 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 254 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 96 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 80 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 16 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 115 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 112 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 48 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 193 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 96 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 32 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 161 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 128 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 64 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 225 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 88 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 24 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 145 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 120 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 56 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 209 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 104 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 40 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 177 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 136 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 72 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 241 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 84 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 20 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 227 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 116 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 52 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 201 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 100 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 36 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 169 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 132 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 68 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 233 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 92 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 28 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 153 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 124 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 60 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 217 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 108 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 44 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 185 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 12 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 140 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 76 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 249 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 82 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 18 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 163 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 114 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 50 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 197 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 98 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 34 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 165 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 2 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 130 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 66 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 229 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 90 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 26 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 149 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 122 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 58 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 213 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 106 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 42 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 181 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 138 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 74 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 245 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 86 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 22 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 118 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 54 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 205 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 102 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 38 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 173 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 134 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 70 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 237 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 94 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 30 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 157 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 126 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 62 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 221 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 110 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 46 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 189 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 14 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 142 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 78 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 253 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 96 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 81 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 131 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 113 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 49 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 195 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 10 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 97 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 33 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 163 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 1 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 129 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 65 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 227 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 6 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 89 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 25 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 147 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 121 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 57 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 211 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 105 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 41 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 179 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 137 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 73 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 243 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 85 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 21 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 258 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 117 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 53 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 203 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 101 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 37 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 171 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 133 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 69 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 235 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 8 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 93 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 29 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 155 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 125 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 61 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 219 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 109 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 45 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 187 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 141 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 77 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 251 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 83 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 195 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 115 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 199 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 35 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 167 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 131 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 231 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 91 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 151 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 67 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 123 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 59 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 215 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 19 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 107 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 43 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 183 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 11 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 139 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 75 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 247 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 87 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 23 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 51 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 119 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 55 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 207 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 103 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 39 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 175 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 135 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 71 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 239 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 95 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 31 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 159 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 99 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 127 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 63 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 223 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 7 as libc::c_int as libc::c_uchar,
                val: 27 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 111 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 47 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 191 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 15 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 143 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 8 as libc::c_int as libc::c_uchar,
                val: 79 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 0 as libc::c_int as libc::c_uchar,
                bits: 9 as libc::c_int as libc::c_uchar,
                val: 255 as libc::c_int as libc::c_ushort,
            };
            init
        },
    ];
    static mut distfix: [code; 32] = [
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 1 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 23 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 257 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 17 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 27 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 4097 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 5 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 25 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 1025 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 65 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 29 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 16385 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 3 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 24 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 513 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 33 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 28 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 8193 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 9 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 26 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 2049 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 22 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 129 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 2 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 23 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 385 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 19 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 25 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 27 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 6145 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 17 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 7 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 25 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 1537 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 21 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 97 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 29 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 24577 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 16 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 4 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 24 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 769 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 20 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 49 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 28 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 12289 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 18 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 13 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 26 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 3073 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 22 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 193 as libc::c_int as libc::c_ushort,
            };
            init
        },
        {
            let mut init = code {
                op: 64 as libc::c_int as libc::c_uchar,
                bits: 5 as libc::c_int as libc::c_uchar,
                val: 0 as libc::c_int as libc::c_ushort,
            };
            init
        },
    ];
    (*state).lencode = lenfix.as_ptr();
    (*state).lenbits = 9 as libc::c_int as libc::c_uint;
    (*state).distcode = distfix.as_ptr();
    (*state).distbits = 5 as libc::c_int as libc::c_uint;
}
#[no_mangle]
pub unsafe extern "C" fn inflateBack(
    mut strm: z_streamp,
    mut in_0: in_func,
    mut in_desc: *mut libc::c_void,
    mut out: out_func,
    mut out_desc: *mut libc::c_void,
) -> libc::c_int {
    let mut state: *mut inflate_state = 0 as *mut inflate_state;
    let mut next: *const libc::c_uchar = 0 as *const libc::c_uchar;
    let mut put: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut have: libc::c_uint = 0;
    let mut left: libc::c_uint = 0;
    let mut hold: libc::c_ulong = 0;
    let mut bits: libc::c_uint = 0;
    let mut copy: libc::c_uint = 0;
    let mut from: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    let mut here: code = code { op: 0, bits: 0, val: 0 };
    let mut last: code = code { op: 0, bits: 0, val: 0 };
    let mut len: libc::c_uint = 0;
    let mut ret: libc::c_int = 0;
    static mut order: [libc::c_ushort; 19] = [
        16 as libc::c_int as libc::c_ushort,
        17 as libc::c_int as libc::c_ushort,
        18 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        8 as libc::c_int as libc::c_ushort,
        7 as libc::c_int as libc::c_ushort,
        9 as libc::c_int as libc::c_ushort,
        6 as libc::c_int as libc::c_ushort,
        10 as libc::c_int as libc::c_ushort,
        5 as libc::c_int as libc::c_ushort,
        11 as libc::c_int as libc::c_ushort,
        4 as libc::c_int as libc::c_ushort,
        12 as libc::c_int as libc::c_ushort,
        3 as libc::c_int as libc::c_ushort,
        13 as libc::c_int as libc::c_ushort,
        2 as libc::c_int as libc::c_ushort,
        14 as libc::c_int as libc::c_ushort,
        1 as libc::c_int as libc::c_ushort,
        15 as libc::c_int as libc::c_ushort,
    ];
    if strm.is_null() || ((*strm).state).is_null() {
        return -(2 as libc::c_int);
    }
    state = (*strm).state as *mut inflate_state;
    (*strm).msg = 0 as *const libc::c_char;
    (*state).mode = TYPE;
    (*state).last = 0 as libc::c_int;
    (*state).whave = 0 as libc::c_int as libc::c_uint;
    next = (*strm).next_in;
    have = if !next.is_null() { (*strm).avail_in } else { 0 as libc::c_int as uInt };
    hold = 0 as libc::c_int as libc::c_ulong;
    bits = 0 as libc::c_int as libc::c_uint;
    put = (*state).window;
    left = (*state).wsize;
    's_69: loop {
        match (*state).mode as libc::c_uint {
            16191 => {
                if (*state).last != 0 {
                    hold >>= bits & 7 as libc::c_int as libc::c_uint;
                    bits = bits.wrapping_sub(bits & 7 as libc::c_int as libc::c_uint);
                    (*state).mode = DONE;
                    continue;
                } else {
                    while bits < 3 as libc::c_int as libc::c_uint {
                        if have == 0 as libc::c_int as libc::c_uint {
                            have = in_0
                                .expect("non-null function pointer")(in_desc, &mut next);
                            if have == 0 as libc::c_int as libc::c_uint {
                                next = 0 as *const libc::c_uchar;
                                ret = -(5 as libc::c_int);
                                break 's_69;
                            }
                        }
                        have = have.wrapping_sub(1);
                        have;
                        let fresh0 = next;
                        next = next.offset(1);
                        hold = hold.wrapping_add((*fresh0 as libc::c_ulong) << bits);
                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                    }
                    (*state)
                        .last = (hold as libc::c_uint
                        & ((1 as libc::c_uint) << 1 as libc::c_int)
                            .wrapping_sub(1 as libc::c_int as libc::c_uint))
                        as libc::c_int;
                    hold >>= 1 as libc::c_int;
                    bits = bits.wrapping_sub(1 as libc::c_int as libc::c_uint);
                    match hold as libc::c_uint
                        & ((1 as libc::c_uint) << 2 as libc::c_int)
                            .wrapping_sub(1 as libc::c_int as libc::c_uint)
                    {
                        0 => {
                            (*state).mode = STORED;
                        }
                        1 => {
                            fixedtables(state);
                            (*state).mode = LEN;
                        }
                        2 => {
                            (*state).mode = TABLE;
                        }
                        3 => {
                            (*strm)
                                .msg = b"invalid block type\0" as *const u8
                                as *const libc::c_char as *mut libc::c_char;
                            (*state).mode = BAD;
                        }
                        _ => {}
                    }
                    hold >>= 2 as libc::c_int;
                    bits = bits.wrapping_sub(2 as libc::c_int as libc::c_uint);
                    continue;
                }
            }
            16193 => {
                hold >>= bits & 7 as libc::c_int as libc::c_uint;
                bits = bits.wrapping_sub(bits & 7 as libc::c_int as libc::c_uint);
                while bits < 32 as libc::c_int as libc::c_uint {
                    if have == 0 as libc::c_int as libc::c_uint {
                        have = in_0
                            .expect("non-null function pointer")(in_desc, &mut next);
                        if have == 0 as libc::c_int as libc::c_uint {
                            next = 0 as *const libc::c_uchar;
                            ret = -(5 as libc::c_int);
                            break 's_69;
                        }
                    }
                    have = have.wrapping_sub(1);
                    have;
                    let fresh1 = next;
                    next = next.offset(1);
                    hold = hold.wrapping_add((*fresh1 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                }
                if hold & 0xffff as libc::c_int as libc::c_ulong
                    != hold >> 16 as libc::c_int ^ 0xffff as libc::c_int as libc::c_ulong
                {
                    (*strm)
                        .msg = b"invalid stored block lengths\0" as *const u8
                        as *const libc::c_char as *mut libc::c_char;
                    (*state).mode = BAD;
                    continue;
                } else {
                    (*state)
                        .length = hold as libc::c_uint
                        & 0xffff as libc::c_int as libc::c_uint;
                    hold = 0 as libc::c_int as libc::c_ulong;
                    bits = 0 as libc::c_int as libc::c_uint;
                    while (*state).length != 0 as libc::c_int as libc::c_uint {
                        copy = (*state).length;
                        if have == 0 as libc::c_int as libc::c_uint {
                            have = in_0
                                .expect("non-null function pointer")(in_desc, &mut next);
                            if have == 0 as libc::c_int as libc::c_uint {
                                next = 0 as *const libc::c_uchar;
                                ret = -(5 as libc::c_int);
                                break 's_69;
                            }
                        }
                        if left == 0 as libc::c_int as libc::c_uint {
                            put = (*state).window;
                            left = (*state).wsize;
                            (*state).whave = left;
                            if out
                                .expect("non-null function pointer")(out_desc, put, left)
                                != 0
                            {
                                ret = -(5 as libc::c_int);
                                break 's_69;
                            }
                        }
                        if copy > have {
                            copy = have;
                        }
                        if copy > left {
                            copy = left;
                        }
                        memcpy(
                            put as *mut libc::c_void,
                            next as *const libc::c_void,
                            copy as libc::c_ulong,
                        );
                        have = have.wrapping_sub(copy);
                        next = next.offset(copy as isize);
                        left = left.wrapping_sub(copy);
                        put = put.offset(copy as isize);
                        (*state).length = ((*state).length).wrapping_sub(copy);
                    }
                    (*state).mode = TYPE;
                    continue;
                }
            }
            16196 => {
                while bits < 14 as libc::c_int as libc::c_uint {
                    if have == 0 as libc::c_int as libc::c_uint {
                        have = in_0
                            .expect("non-null function pointer")(in_desc, &mut next);
                        if have == 0 as libc::c_int as libc::c_uint {
                            next = 0 as *const libc::c_uchar;
                            ret = -(5 as libc::c_int);
                            break 's_69;
                        }
                    }
                    have = have.wrapping_sub(1);
                    have;
                    let fresh2 = next;
                    next = next.offset(1);
                    hold = hold.wrapping_add((*fresh2 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                }
                (*state)
                    .nlen = (hold as libc::c_uint
                    & ((1 as libc::c_uint) << 5 as libc::c_int)
                        .wrapping_sub(1 as libc::c_int as libc::c_uint))
                    .wrapping_add(257 as libc::c_int as libc::c_uint);
                hold >>= 5 as libc::c_int;
                bits = bits.wrapping_sub(5 as libc::c_int as libc::c_uint);
                (*state)
                    .ndist = (hold as libc::c_uint
                    & ((1 as libc::c_uint) << 5 as libc::c_int)
                        .wrapping_sub(1 as libc::c_int as libc::c_uint))
                    .wrapping_add(1 as libc::c_int as libc::c_uint);
                hold >>= 5 as libc::c_int;
                bits = bits.wrapping_sub(5 as libc::c_int as libc::c_uint);
                (*state)
                    .ncode = (hold as libc::c_uint
                    & ((1 as libc::c_uint) << 4 as libc::c_int)
                        .wrapping_sub(1 as libc::c_int as libc::c_uint))
                    .wrapping_add(4 as libc::c_int as libc::c_uint);
                hold >>= 4 as libc::c_int;
                bits = bits.wrapping_sub(4 as libc::c_int as libc::c_uint);
                if (*state).nlen > 286 as libc::c_int as libc::c_uint
                    || (*state).ndist > 30 as libc::c_int as libc::c_uint
                {
                    (*strm)
                        .msg = b"too many length or distance symbols\0" as *const u8
                        as *const libc::c_char as *mut libc::c_char;
                    (*state).mode = BAD;
                    continue;
                } else {
                    (*state).have = 0 as libc::c_int as libc::c_uint;
                    while (*state).have < (*state).ncode {
                        while bits < 3 as libc::c_int as libc::c_uint {
                            if have == 0 as libc::c_int as libc::c_uint {
                                have = in_0
                                    .expect("non-null function pointer")(in_desc, &mut next);
                                if have == 0 as libc::c_int as libc::c_uint {
                                    next = 0 as *const libc::c_uchar;
                                    ret = -(5 as libc::c_int);
                                    break 's_69;
                                }
                            }
                            have = have.wrapping_sub(1);
                            have;
                            let fresh3 = next;
                            next = next.offset(1);
                            hold = hold.wrapping_add((*fresh3 as libc::c_ulong) << bits);
                            bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                        }
                        let fresh4 = (*state).have;
                        (*state).have = ((*state).have).wrapping_add(1);
                        (*state)
                            .lens[order[fresh4 as usize]
                            as usize] = (hold as libc::c_uint
                            & ((1 as libc::c_uint) << 3 as libc::c_int)
                                .wrapping_sub(1 as libc::c_int as libc::c_uint))
                            as libc::c_ushort;
                        hold >>= 3 as libc::c_int;
                        bits = bits.wrapping_sub(3 as libc::c_int as libc::c_uint);
                    }
                    while (*state).have < 19 as libc::c_int as libc::c_uint {
                        let fresh5 = (*state).have;
                        (*state).have = ((*state).have).wrapping_add(1);
                        (*state)
                            .lens[order[fresh5 as usize]
                            as usize] = 0 as libc::c_int as libc::c_ushort;
                    }
                    (*state).next = ((*state).codes).as_mut_ptr();
                    (*state).lencode = (*state).next as *const code;
                    (*state).lenbits = 7 as libc::c_int as libc::c_uint;
                    ret = inflate_table(
                        CODES,
                        ((*state).lens).as_mut_ptr(),
                        19 as libc::c_int as libc::c_uint,
                        &mut (*state).next,
                        &mut (*state).lenbits,
                        ((*state).work).as_mut_ptr(),
                    );
                    if ret != 0 {
                        (*strm)
                            .msg = b"invalid code lengths set\0" as *const u8
                            as *const libc::c_char as *mut libc::c_char;
                        (*state).mode = BAD;
                        continue;
                    } else {
                        (*state).have = 0 as libc::c_int as libc::c_uint;
                        while (*state).have
                            < ((*state).nlen).wrapping_add((*state).ndist)
                        {
                            loop {
                                here = *((*state).lencode)
                                    .offset(
                                        (hold as libc::c_uint
                                            & ((1 as libc::c_uint) << (*state).lenbits)
                                                .wrapping_sub(1 as libc::c_int as libc::c_uint)) as isize,
                                    );
                                if here.bits as libc::c_uint <= bits {
                                    break;
                                }
                                if have == 0 as libc::c_int as libc::c_uint {
                                    have = in_0
                                        .expect("non-null function pointer")(in_desc, &mut next);
                                    if have == 0 as libc::c_int as libc::c_uint {
                                        next = 0 as *const libc::c_uchar;
                                        ret = -(5 as libc::c_int);
                                        break 's_69;
                                    }
                                }
                                have = have.wrapping_sub(1);
                                have;
                                let fresh6 = next;
                                next = next.offset(1);
                                hold = hold
                                    .wrapping_add((*fresh6 as libc::c_ulong) << bits);
                                bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                            }
                            if (here.val as libc::c_int) < 16 as libc::c_int {
                                hold >>= here.bits as libc::c_int;
                                bits = bits.wrapping_sub(here.bits as libc::c_uint);
                                let fresh7 = (*state).have;
                                (*state).have = ((*state).have).wrapping_add(1);
                                (*state).lens[fresh7 as usize] = here.val;
                            } else {
                                if here.val as libc::c_int == 16 as libc::c_int {
                                    while bits
                                        < (here.bits as libc::c_int + 2 as libc::c_int)
                                            as libc::c_uint
                                    {
                                        if have == 0 as libc::c_int as libc::c_uint {
                                            have = in_0
                                                .expect("non-null function pointer")(in_desc, &mut next);
                                            if have == 0 as libc::c_int as libc::c_uint {
                                                next = 0 as *const libc::c_uchar;
                                                ret = -(5 as libc::c_int);
                                                break 's_69;
                                            }
                                        }
                                        have = have.wrapping_sub(1);
                                        have;
                                        let fresh8 = next;
                                        next = next.offset(1);
                                        hold = hold
                                            .wrapping_add((*fresh8 as libc::c_ulong) << bits);
                                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                                    }
                                    hold >>= here.bits as libc::c_int;
                                    bits = bits.wrapping_sub(here.bits as libc::c_uint);
                                    if (*state).have == 0 as libc::c_int as libc::c_uint {
                                        (*strm)
                                            .msg = b"invalid bit length repeat\0" as *const u8
                                            as *const libc::c_char as *mut libc::c_char;
                                        (*state).mode = BAD;
                                        break;
                                    } else {
                                        len = (*state)
                                            .lens[((*state).have)
                                            .wrapping_sub(1 as libc::c_int as libc::c_uint) as usize]
                                            as libc::c_uint;
                                        copy = (3 as libc::c_int as libc::c_uint)
                                            .wrapping_add(
                                                hold as libc::c_uint
                                                    & ((1 as libc::c_uint) << 2 as libc::c_int)
                                                        .wrapping_sub(1 as libc::c_int as libc::c_uint),
                                            );
                                        hold >>= 2 as libc::c_int;
                                        bits = bits.wrapping_sub(2 as libc::c_int as libc::c_uint);
                                    }
                                } else if here.val as libc::c_int == 17 as libc::c_int {
                                    while bits
                                        < (here.bits as libc::c_int + 3 as libc::c_int)
                                            as libc::c_uint
                                    {
                                        if have == 0 as libc::c_int as libc::c_uint {
                                            have = in_0
                                                .expect("non-null function pointer")(in_desc, &mut next);
                                            if have == 0 as libc::c_int as libc::c_uint {
                                                next = 0 as *const libc::c_uchar;
                                                ret = -(5 as libc::c_int);
                                                break 's_69;
                                            }
                                        }
                                        have = have.wrapping_sub(1);
                                        have;
                                        let fresh9 = next;
                                        next = next.offset(1);
                                        hold = hold
                                            .wrapping_add((*fresh9 as libc::c_ulong) << bits);
                                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                                    }
                                    hold >>= here.bits as libc::c_int;
                                    bits = bits.wrapping_sub(here.bits as libc::c_uint);
                                    len = 0 as libc::c_int as libc::c_uint;
                                    copy = (3 as libc::c_int as libc::c_uint)
                                        .wrapping_add(
                                            hold as libc::c_uint
                                                & ((1 as libc::c_uint) << 3 as libc::c_int)
                                                    .wrapping_sub(1 as libc::c_int as libc::c_uint),
                                        );
                                    hold >>= 3 as libc::c_int;
                                    bits = bits.wrapping_sub(3 as libc::c_int as libc::c_uint);
                                } else {
                                    while bits
                                        < (here.bits as libc::c_int + 7 as libc::c_int)
                                            as libc::c_uint
                                    {
                                        if have == 0 as libc::c_int as libc::c_uint {
                                            have = in_0
                                                .expect("non-null function pointer")(in_desc, &mut next);
                                            if have == 0 as libc::c_int as libc::c_uint {
                                                next = 0 as *const libc::c_uchar;
                                                ret = -(5 as libc::c_int);
                                                break 's_69;
                                            }
                                        }
                                        have = have.wrapping_sub(1);
                                        have;
                                        let fresh10 = next;
                                        next = next.offset(1);
                                        hold = hold
                                            .wrapping_add((*fresh10 as libc::c_ulong) << bits);
                                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                                    }
                                    hold >>= here.bits as libc::c_int;
                                    bits = bits.wrapping_sub(here.bits as libc::c_uint);
                                    len = 0 as libc::c_int as libc::c_uint;
                                    copy = (11 as libc::c_int as libc::c_uint)
                                        .wrapping_add(
                                            hold as libc::c_uint
                                                & ((1 as libc::c_uint) << 7 as libc::c_int)
                                                    .wrapping_sub(1 as libc::c_int as libc::c_uint),
                                        );
                                    hold >>= 7 as libc::c_int;
                                    bits = bits.wrapping_sub(7 as libc::c_int as libc::c_uint);
                                }
                                if ((*state).have).wrapping_add(copy)
                                    > ((*state).nlen).wrapping_add((*state).ndist)
                                {
                                    (*strm)
                                        .msg = b"invalid bit length repeat\0" as *const u8
                                        as *const libc::c_char as *mut libc::c_char;
                                    (*state).mode = BAD;
                                    break;
                                } else {
                                    loop {
                                        let fresh11 = copy;
                                        copy = copy.wrapping_sub(1);
                                        if !(fresh11 != 0) {
                                            break;
                                        }
                                        let fresh12 = (*state).have;
                                        (*state).have = ((*state).have).wrapping_add(1);
                                        (*state).lens[fresh12 as usize] = len as libc::c_ushort;
                                    }
                                }
                            }
                        }
                        if (*state).mode as libc::c_uint
                            == BAD as libc::c_int as libc::c_uint
                        {
                            continue;
                        }
                        if (*state).lens[256 as libc::c_int as usize] as libc::c_int
                            == 0 as libc::c_int
                        {
                            (*strm)
                                .msg = b"invalid code -- missing end-of-block\0"
                                as *const u8 as *const libc::c_char as *mut libc::c_char;
                            (*state).mode = BAD;
                            continue;
                        } else {
                            (*state).next = ((*state).codes).as_mut_ptr();
                            (*state).lencode = (*state).next as *const code;
                            (*state).lenbits = 9 as libc::c_int as libc::c_uint;
                            ret = inflate_table(
                                LENS,
                                ((*state).lens).as_mut_ptr(),
                                (*state).nlen,
                                &mut (*state).next,
                                &mut (*state).lenbits,
                                ((*state).work).as_mut_ptr(),
                            );
                            if ret != 0 {
                                (*strm)
                                    .msg = b"invalid literal/lengths set\0" as *const u8
                                    as *const libc::c_char as *mut libc::c_char;
                                (*state).mode = BAD;
                                continue;
                            } else {
                                (*state).distcode = (*state).next as *const code;
                                (*state).distbits = 6 as libc::c_int as libc::c_uint;
                                ret = inflate_table(
                                    DISTS,
                                    ((*state).lens).as_mut_ptr().offset((*state).nlen as isize),
                                    (*state).ndist,
                                    &mut (*state).next,
                                    &mut (*state).distbits,
                                    ((*state).work).as_mut_ptr(),
                                );
                                if ret != 0 {
                                    (*strm)
                                        .msg = b"invalid distances set\0" as *const u8
                                        as *const libc::c_char as *mut libc::c_char;
                                    (*state).mode = BAD;
                                    continue;
                                } else {
                                    (*state).mode = LEN;
                                }
                            }
                        }
                    }
                }
            }
            16200 => {}
            16208 => {
                ret = 1 as libc::c_int;
                break;
            }
            16209 => {
                ret = -(3 as libc::c_int);
                break;
            }
            _ => {
                ret = -(2 as libc::c_int);
                break;
            }
        }
        if have >= 6 as libc::c_int as libc::c_uint
            && left >= 258 as libc::c_int as libc::c_uint
        {
            (*strm).next_out = put;
            (*strm).avail_out = left;
            (*strm).next_in = next;
            (*strm).avail_in = have;
            (*state).hold = hold;
            (*state).bits = bits;
            if (*state).whave < (*state).wsize {
                (*state).whave = ((*state).wsize).wrapping_sub(left);
            }
            inflate_fast(strm, (*state).wsize);
            put = (*strm).next_out;
            left = (*strm).avail_out;
            next = (*strm).next_in;
            have = (*strm).avail_in;
            hold = (*state).hold;
            bits = (*state).bits;
        } else {
            loop {
                here = *((*state).lencode)
                    .offset(
                        (hold as libc::c_uint
                            & ((1 as libc::c_uint) << (*state).lenbits)
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)) as isize,
                    );
                if here.bits as libc::c_uint <= bits {
                    break;
                }
                if have == 0 as libc::c_int as libc::c_uint {
                    have = in_0.expect("non-null function pointer")(in_desc, &mut next);
                    if have == 0 as libc::c_int as libc::c_uint {
                        next = 0 as *const libc::c_uchar;
                        ret = -(5 as libc::c_int);
                        break 's_69;
                    }
                }
                have = have.wrapping_sub(1);
                have;
                let fresh13 = next;
                next = next.offset(1);
                hold = hold.wrapping_add((*fresh13 as libc::c_ulong) << bits);
                bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
            }
            if here.op as libc::c_int != 0
                && here.op as libc::c_int & 0xf0 as libc::c_int == 0 as libc::c_int
            {
                last = here;
                loop {
                    here = *((*state).lencode)
                        .offset(
                            (last.val as libc::c_uint)
                                .wrapping_add(
                                    (hold as libc::c_uint
                                        & ((1 as libc::c_uint)
                                            << last.bits as libc::c_int + last.op as libc::c_int)
                                            .wrapping_sub(1 as libc::c_int as libc::c_uint))
                                        >> last.bits as libc::c_int,
                                ) as isize,
                        );
                    if (last.bits as libc::c_int + here.bits as libc::c_int)
                        as libc::c_uint <= bits
                    {
                        break;
                    }
                    if have == 0 as libc::c_int as libc::c_uint {
                        have = in_0
                            .expect("non-null function pointer")(in_desc, &mut next);
                        if have == 0 as libc::c_int as libc::c_uint {
                            next = 0 as *const libc::c_uchar;
                            ret = -(5 as libc::c_int);
                            break 's_69;
                        }
                    }
                    have = have.wrapping_sub(1);
                    have;
                    let fresh14 = next;
                    next = next.offset(1);
                    hold = hold.wrapping_add((*fresh14 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                }
                hold >>= last.bits as libc::c_int;
                bits = bits.wrapping_sub(last.bits as libc::c_uint);
            }
            hold >>= here.bits as libc::c_int;
            bits = bits.wrapping_sub(here.bits as libc::c_uint);
            (*state).length = here.val as libc::c_uint;
            if here.op as libc::c_int == 0 as libc::c_int {
                if left == 0 as libc::c_int as libc::c_uint {
                    put = (*state).window;
                    left = (*state).wsize;
                    (*state).whave = left;
                    if out.expect("non-null function pointer")(out_desc, put, left) != 0
                    {
                        ret = -(5 as libc::c_int);
                        break;
                    }
                }
                let fresh15 = put;
                put = put.offset(1);
                *fresh15 = (*state).length as libc::c_uchar;
                left = left.wrapping_sub(1);
                left;
                (*state).mode = LEN;
            } else if here.op as libc::c_int & 32 as libc::c_int != 0 {
                (*state).mode = TYPE;
            } else if here.op as libc::c_int & 64 as libc::c_int != 0 {
                (*strm)
                    .msg = b"invalid literal/length code\0" as *const u8
                    as *const libc::c_char as *mut libc::c_char;
                (*state).mode = BAD;
            } else {
                (*state)
                    .extra = here.op as libc::c_uint & 15 as libc::c_int as libc::c_uint;
                if (*state).extra != 0 as libc::c_int as libc::c_uint {
                    while bits < (*state).extra {
                        if have == 0 as libc::c_int as libc::c_uint {
                            have = in_0
                                .expect("non-null function pointer")(in_desc, &mut next);
                            if have == 0 as libc::c_int as libc::c_uint {
                                next = 0 as *const libc::c_uchar;
                                ret = -(5 as libc::c_int);
                                break 's_69;
                            }
                        }
                        have = have.wrapping_sub(1);
                        have;
                        let fresh16 = next;
                        next = next.offset(1);
                        hold = hold.wrapping_add((*fresh16 as libc::c_ulong) << bits);
                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                    }
                    (*state)
                        .length = ((*state).length)
                        .wrapping_add(
                            hold as libc::c_uint
                                & ((1 as libc::c_uint) << (*state).extra)
                                    .wrapping_sub(1 as libc::c_int as libc::c_uint),
                        );
                    hold >>= (*state).extra;
                    bits = bits.wrapping_sub((*state).extra);
                }
                loop {
                    here = *((*state).distcode)
                        .offset(
                            (hold as libc::c_uint
                                & ((1 as libc::c_uint) << (*state).distbits)
                                    .wrapping_sub(1 as libc::c_int as libc::c_uint)) as isize,
                        );
                    if here.bits as libc::c_uint <= bits {
                        break;
                    }
                    if have == 0 as libc::c_int as libc::c_uint {
                        have = in_0
                            .expect("non-null function pointer")(in_desc, &mut next);
                        if have == 0 as libc::c_int as libc::c_uint {
                            next = 0 as *const libc::c_uchar;
                            ret = -(5 as libc::c_int);
                            break 's_69;
                        }
                    }
                    have = have.wrapping_sub(1);
                    have;
                    let fresh17 = next;
                    next = next.offset(1);
                    hold = hold.wrapping_add((*fresh17 as libc::c_ulong) << bits);
                    bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                }
                if here.op as libc::c_int & 0xf0 as libc::c_int == 0 as libc::c_int {
                    last = here;
                    loop {
                        here = *((*state).distcode)
                            .offset(
                                (last.val as libc::c_uint)
                                    .wrapping_add(
                                        (hold as libc::c_uint
                                            & ((1 as libc::c_uint)
                                                << last.bits as libc::c_int + last.op as libc::c_int)
                                                .wrapping_sub(1 as libc::c_int as libc::c_uint))
                                            >> last.bits as libc::c_int,
                                    ) as isize,
                            );
                        if (last.bits as libc::c_int + here.bits as libc::c_int)
                            as libc::c_uint <= bits
                        {
                            break;
                        }
                        if have == 0 as libc::c_int as libc::c_uint {
                            have = in_0
                                .expect("non-null function pointer")(in_desc, &mut next);
                            if have == 0 as libc::c_int as libc::c_uint {
                                next = 0 as *const libc::c_uchar;
                                ret = -(5 as libc::c_int);
                                break 's_69;
                            }
                        }
                        have = have.wrapping_sub(1);
                        have;
                        let fresh18 = next;
                        next = next.offset(1);
                        hold = hold.wrapping_add((*fresh18 as libc::c_ulong) << bits);
                        bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                    }
                    hold >>= last.bits as libc::c_int;
                    bits = bits.wrapping_sub(last.bits as libc::c_uint);
                }
                hold >>= here.bits as libc::c_int;
                bits = bits.wrapping_sub(here.bits as libc::c_uint);
                if here.op as libc::c_int & 64 as libc::c_int != 0 {
                    (*strm)
                        .msg = b"invalid distance code\0" as *const u8
                        as *const libc::c_char as *mut libc::c_char;
                    (*state).mode = BAD;
                } else {
                    (*state).offset = here.val as libc::c_uint;
                    (*state)
                        .extra = here.op as libc::c_uint
                        & 15 as libc::c_int as libc::c_uint;
                    if (*state).extra != 0 as libc::c_int as libc::c_uint {
                        while bits < (*state).extra {
                            if have == 0 as libc::c_int as libc::c_uint {
                                have = in_0
                                    .expect("non-null function pointer")(in_desc, &mut next);
                                if have == 0 as libc::c_int as libc::c_uint {
                                    next = 0 as *const libc::c_uchar;
                                    ret = -(5 as libc::c_int);
                                    break 's_69;
                                }
                            }
                            have = have.wrapping_sub(1);
                            have;
                            let fresh19 = next;
                            next = next.offset(1);
                            hold = hold
                                .wrapping_add((*fresh19 as libc::c_ulong) << bits);
                            bits = bits.wrapping_add(8 as libc::c_int as libc::c_uint);
                        }
                        (*state)
                            .offset = ((*state).offset)
                            .wrapping_add(
                                hold as libc::c_uint
                                    & ((1 as libc::c_uint) << (*state).extra)
                                        .wrapping_sub(1 as libc::c_int as libc::c_uint),
                            );
                        hold >>= (*state).extra;
                        bits = bits.wrapping_sub((*state).extra);
                    }
                    if (*state).offset
                        > ((*state).wsize)
                            .wrapping_sub(
                                (if (*state).whave < (*state).wsize {
                                    left
                                } else {
                                    0 as libc::c_int as libc::c_uint
                                }),
                            )
                    {
                        (*strm)
                            .msg = b"invalid distance too far back\0" as *const u8
                            as *const libc::c_char as *mut libc::c_char;
                        (*state).mode = BAD;
                    } else {
                        loop {
                            if left == 0 as libc::c_int as libc::c_uint {
                                put = (*state).window;
                                left = (*state).wsize;
                                (*state).whave = left;
                                if out
                                    .expect("non-null function pointer")(out_desc, put, left)
                                    != 0
                                {
                                    ret = -(5 as libc::c_int);
                                    break 's_69;
                                }
                            }
                            copy = ((*state).wsize).wrapping_sub((*state).offset);
                            if copy < left {
                                from = put.offset(copy as isize);
                                copy = left.wrapping_sub(copy);
                            } else {
                                from = put.offset(-((*state).offset as isize));
                                copy = left;
                            }
                            if copy > (*state).length {
                                copy = (*state).length;
                            }
                            (*state).length = ((*state).length).wrapping_sub(copy);
                            left = left.wrapping_sub(copy);
                            loop {
                                let fresh20 = from;
                                from = from.offset(1);
                                let fresh21 = put;
                                put = put.offset(1);
                                *fresh21 = *fresh20;
                                copy = copy.wrapping_sub(1);
                                if !(copy != 0) {
                                    break;
                                }
                            }
                            if !((*state).length != 0 as libc::c_int as libc::c_uint) {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if left < (*state).wsize {
        if out
            .expect(
                "non-null function pointer",
            )(out_desc, (*state).window, ((*state).wsize).wrapping_sub(left)) != 0
            && ret == 1 as libc::c_int
        {
            ret = -(5 as libc::c_int);
        }
    }
    (*strm).next_in = next;
    (*strm).avail_in = have;
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn inflateBackEnd(mut strm: z_streamp) -> libc::c_int {
    if strm.is_null() || ((*strm).state).is_null() || ((*strm).zfree).is_none() {
        return -(2 as libc::c_int);
    }
    (Some(((*strm).zfree).expect("non-null function pointer")))
        .expect("non-null function pointer")((*strm).opaque, (*strm).state as voidpf);
    (*strm).state = 0 as *mut internal_state;
    return 0 as libc::c_int;
}
