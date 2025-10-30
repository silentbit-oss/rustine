
















extern "C" {
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
}
pub type Byte = crate::src::libpng::png::Byte;
pub type uInt = crate::src::libpng::png::uInt;
pub type uLong = crate::src::libpng::png::uLong;
pub type Bytef = crate::src::libpng::png::Bytef;
pub type charf = crate::src::zlib::deflate::charf;
pub type intf = std::os::raw::c_int;
pub type voidpf = crate::src::libpng::png::voidpf;
pub type alloc_func = crate::src::libpng::png::alloc_func;
pub type free_func = crate::src::libpng::png::free_func;
// #[derive(Copy, Clone)]

pub type internal_state = crate::src::zlib::deflate::internal_state;
pub type ulg = crate::src::zlib::deflate::ulg;
pub type ush = crate::src::zlib::deflate::ush;
pub type ushf = crate::src::zlib::deflate::ushf;
pub type uchf = crate::src::zlib::deflate::uchf;
pub type uch = crate::src::zlib::deflate::uch;
// #[derive(Copy, Clone)]

pub type tree_desc_s = crate::src::zlib::deflate::tree_desc_s;
pub type static_tree_desc = crate::src::zlib::deflate::static_tree_desc;
/* The lengths of the bit length codes are sent in order of decreasing
 * probability, to avoid transmitting the lengths for unused bit length codes.
 */
/* ===========================================================================
 * Local data. These are initialized only once.
 */
/* see definition of array dist_code below */
/* GEN_TREES_H */
#[derive(Copy, Clone)]
#[repr(C)]
pub struct static_tree_desc_s {
    pub static_tree: *const ct_data,
    pub extra_bits: *const intf,
    pub extra_base: std::os::raw::c_int,
    pub elems: std::os::raw::c_int,
    pub max_length: std::os::raw::c_int,
}
pub type ct_data = crate::src::zlib::deflate::ct_data;
// #[derive(Copy, Clone)]

pub type ct_data_s = crate::src::zlib::deflate::ct_data_s;
// #[derive(Copy, Clone)]

pub type C2RustUnnamed = crate::src::zlib::deflate::C2RustUnnamed;
// #[derive(Copy, Clone)]

pub type C2RustUnnamed_0 = crate::src::zlib::deflate::C2RustUnnamed_0;
pub type IPos = crate::src::zlib::deflate::IPos;
pub type Posf = crate::src::zlib::deflate::Posf;
pub type Pos = crate::src::zlib::deflate::Pos;
pub type gz_headerp = crate::src::zlib::deflate::gz_headerp;
pub type gz_header = crate::src::zlib::deflate::gz_header;
// #[derive(Copy, Clone)]

pub type gz_header_s = crate::src::zlib::infback::gz_header_s;
pub type z_streamp = crate::src::libpng::png::z_streamp;
pub type z_stream = crate::src::libpng::png::z_stream;
// #[derive(Copy, Clone)]

pub type z_stream_s = crate::src::libpng::pngerror::z_stream_s;
pub type tree_desc = tree_desc_s;
pub type deflate_state = crate::src::zlib::deflate::deflate_state;
/* repeat a zero length 11-138 times  (7 bits of repeat count) */
static mut extra_lbits: [std::os::raw::c_int; 29] =
    [0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     1 as std::os::raw::c_int, 1 as std::os::raw::c_int, 1 as std::os::raw::c_int, 1 as std::os::raw::c_int,
     2 as std::os::raw::c_int, 2 as std::os::raw::c_int, 2 as std::os::raw::c_int, 2 as std::os::raw::c_int,
     3 as std::os::raw::c_int, 3 as std::os::raw::c_int, 3 as std::os::raw::c_int, 3 as std::os::raw::c_int,
     4 as std::os::raw::c_int, 4 as std::os::raw::c_int, 4 as std::os::raw::c_int, 4 as std::os::raw::c_int,
     5 as std::os::raw::c_int, 5 as std::os::raw::c_int, 5 as std::os::raw::c_int, 5 as std::os::raw::c_int,
     0 as std::os::raw::c_int];
static mut extra_dbits: [std::os::raw::c_int; 30] =
    [0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     1 as std::os::raw::c_int, 1 as std::os::raw::c_int, 2 as std::os::raw::c_int, 2 as std::os::raw::c_int,
     3 as std::os::raw::c_int, 3 as std::os::raw::c_int, 4 as std::os::raw::c_int, 4 as std::os::raw::c_int,
     5 as std::os::raw::c_int, 5 as std::os::raw::c_int, 6 as std::os::raw::c_int, 6 as std::os::raw::c_int,
     7 as std::os::raw::c_int, 7 as std::os::raw::c_int, 8 as std::os::raw::c_int, 8 as std::os::raw::c_int,
     9 as std::os::raw::c_int, 9 as std::os::raw::c_int, 10 as std::os::raw::c_int, 10 as std::os::raw::c_int,
     11 as std::os::raw::c_int, 11 as std::os::raw::c_int, 12 as std::os::raw::c_int,
     12 as std::os::raw::c_int, 13 as std::os::raw::c_int, 13 as std::os::raw::c_int];
static mut extra_blbits: [std::os::raw::c_int; 19] =
    [0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
     2 as std::os::raw::c_int, 3 as std::os::raw::c_int, 7 as std::os::raw::c_int];
static mut bl_order: [uch; 19] =
    [16 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 0 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 7 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 6 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 5 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 4 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 3 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 2 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 1 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch];
static mut static_ltree: [ct_data; 288] =
    [{
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 12 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 140 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 76 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 204 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 44 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 172 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 108 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 236 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 28 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 156 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 92 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 220 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 60 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 188 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 124 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 252 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 2 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 130 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 66 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 194 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 34 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 162 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 98 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 226 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 18 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 146 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 82 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 210 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 50 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 178 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 114 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 242 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 10 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 138 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 74 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 202 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 42 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 170 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 106 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 234 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 26 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 154 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 90 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 218 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 58 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 186 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 122 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 250 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 6 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 134 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 70 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 198 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 38 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 166 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 102 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 230 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 22 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 150 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 86 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 214 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 54 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 182 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 118 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 246 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 14 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 142 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 78 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 206 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 46 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 174 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 110 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 238 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 30 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 158 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 94 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 222 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 62 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 190 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 126 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 254 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 1 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 129 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 65 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 193 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 33 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 161 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 97 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 225 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 17 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 145 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 81 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 209 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 49 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 177 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 113 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 241 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 9 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 137 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 73 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 201 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 41 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 169 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 105 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 233 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 25 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 153 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 89 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 217 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 57 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 185 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 121 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 249 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 5 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 133 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 69 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 197 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 37 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 165 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 101 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 229 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 21 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 149 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 85 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 213 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 53 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 181 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 117 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 245 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 13 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 141 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 77 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 205 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 45 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 173 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 109 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 237 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 29 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 157 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 93 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 221 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 61 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 189 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 125 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 253 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 19 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 275 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 147 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 403 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 83 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 339 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 211 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 467 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 51 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 307 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 179 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 435 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 115 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 371 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 243 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 499 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 11 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 267 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 139 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 395 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 75 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 331 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 203 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 459 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 43 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 299 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 171 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 427 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 107 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 363 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 235 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 491 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 27 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 283 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 155 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 411 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 91 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 347 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 219 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 475 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 59 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 315 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 187 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 443 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 123 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 379 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 251 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 507 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 7 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 263 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 135 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 391 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 71 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 327 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 199 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 455 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 39 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 295 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 167 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 423 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 103 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 359 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 231 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 487 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 23 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 279 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 151 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 407 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 87 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 343 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 215 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 471 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 55 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 311 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 183 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 439 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 119 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 375 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 247 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 503 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 15 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 271 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 143 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 399 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 79 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 335 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 207 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 463 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 47 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 303 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 175 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 431 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 111 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 367 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 239 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 495 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 31 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 287 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 159 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 415 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 95 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 351 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 223 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 479 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 63 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 319 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 191 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 447 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 127 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 383 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 255 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 511 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 9 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 0 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 64 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 32 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 96 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 16 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 80 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 48 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 112 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 8 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 72 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 40 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 104 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 24 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 88 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 56 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 120 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 4 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 68 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 36 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 100 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 20 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 84 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 52 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 116 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 7 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 3 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 131 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 67 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 195 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 35 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 163 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 99 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 227 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 8 as std::os::raw::c_int as ush,},};
         init
     }];
static mut static_dtree: [ct_data; 30] =
    [{
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 0 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 16 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 8 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 24 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 4 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 20 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 12 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 28 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 2 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 18 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 10 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 26 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 6 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 22 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 14 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 30 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 1 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 17 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 9 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 25 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 5 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 21 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 13 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 29 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 3 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 19 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 11 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 27 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 7 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     },
     {
         let mut init =
             ct_data_s{fc: C2RustUnnamed_0{freq: 23 as std::os::raw::c_int as ush,},
                       dl: C2RustUnnamed{dad: 5 as std::os::raw::c_int as ush,},};
         init
     }];
#[no_mangle]
pub static mut _dist_code: [uch; 512] =
    [0 as std::os::raw::c_int as uch, 1 as std::os::raw::c_int as uch,
     2 as std::os::raw::c_int as uch, 3 as std::os::raw::c_int as uch,
     4 as std::os::raw::c_int as uch, 4 as std::os::raw::c_int as uch,
     5 as std::os::raw::c_int as uch, 5 as std::os::raw::c_int as uch,
     6 as std::os::raw::c_int as uch, 6 as std::os::raw::c_int as uch,
     6 as std::os::raw::c_int as uch, 6 as std::os::raw::c_int as uch,
     7 as std::os::raw::c_int as uch, 7 as std::os::raw::c_int as uch,
     7 as std::os::raw::c_int as uch, 7 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 8 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 8 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 8 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 8 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 9 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 9 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 9 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 9 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     0 as std::os::raw::c_int as uch, 0 as std::os::raw::c_int as uch,
     16 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 18 as std::os::raw::c_int as uch,
     19 as std::os::raw::c_int as uch, 19 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     28 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch,
     29 as std::os::raw::c_int as uch, 29 as std::os::raw::c_int as uch];
#[no_mangle]
pub static mut _length_code: [uch; 256] =
    [0 as std::os::raw::c_int as uch, 1 as std::os::raw::c_int as uch,
     2 as std::os::raw::c_int as uch, 3 as std::os::raw::c_int as uch,
     4 as std::os::raw::c_int as uch, 5 as std::os::raw::c_int as uch,
     6 as std::os::raw::c_int as uch, 7 as std::os::raw::c_int as uch,
     8 as std::os::raw::c_int as uch, 8 as std::os::raw::c_int as uch,
     9 as std::os::raw::c_int as uch, 9 as std::os::raw::c_int as uch,
     10 as std::os::raw::c_int as uch, 10 as std::os::raw::c_int as uch,
     11 as std::os::raw::c_int as uch, 11 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     12 as std::os::raw::c_int as uch, 12 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     13 as std::os::raw::c_int as uch, 13 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     14 as std::os::raw::c_int as uch, 14 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     15 as std::os::raw::c_int as uch, 15 as std::os::raw::c_int as uch,
     16 as std::os::raw::c_int as uch, 16 as std::os::raw::c_int as uch,
     16 as std::os::raw::c_int as uch, 16 as std::os::raw::c_int as uch,
     16 as std::os::raw::c_int as uch, 16 as std::os::raw::c_int as uch,
     16 as std::os::raw::c_int as uch, 16 as std::os::raw::c_int as uch,
     17 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     17 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     17 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     17 as std::os::raw::c_int as uch, 17 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 18 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 18 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 18 as std::os::raw::c_int as uch,
     18 as std::os::raw::c_int as uch, 18 as std::os::raw::c_int as uch,
     19 as std::os::raw::c_int as uch, 19 as std::os::raw::c_int as uch,
     19 as std::os::raw::c_int as uch, 19 as std::os::raw::c_int as uch,
     19 as std::os::raw::c_int as uch, 19 as std::os::raw::c_int as uch,
     19 as std::os::raw::c_int as uch, 19 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     20 as std::os::raw::c_int as uch, 20 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     21 as std::os::raw::c_int as uch, 21 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     22 as std::os::raw::c_int as uch, 22 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     23 as std::os::raw::c_int as uch, 23 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     24 as std::os::raw::c_int as uch, 24 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     25 as std::os::raw::c_int as uch, 25 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     26 as std::os::raw::c_int as uch, 26 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 27 as std::os::raw::c_int as uch,
     27 as std::os::raw::c_int as uch, 28 as std::os::raw::c_int as uch];
static mut base_length: [std::os::raw::c_int; 29] =
    [0 as std::os::raw::c_int, 1 as std::os::raw::c_int, 2 as std::os::raw::c_int, 3 as std::os::raw::c_int,
     4 as std::os::raw::c_int, 5 as std::os::raw::c_int, 6 as std::os::raw::c_int, 7 as std::os::raw::c_int,
     8 as std::os::raw::c_int, 10 as std::os::raw::c_int, 12 as std::os::raw::c_int,
     14 as std::os::raw::c_int, 16 as std::os::raw::c_int, 20 as std::os::raw::c_int,
     24 as std::os::raw::c_int, 28 as std::os::raw::c_int, 32 as std::os::raw::c_int,
     40 as std::os::raw::c_int, 48 as std::os::raw::c_int, 56 as std::os::raw::c_int,
     64 as std::os::raw::c_int, 80 as std::os::raw::c_int, 96 as std::os::raw::c_int,
     112 as std::os::raw::c_int, 128 as std::os::raw::c_int, 160 as std::os::raw::c_int,
     192 as std::os::raw::c_int, 224 as std::os::raw::c_int, 0 as std::os::raw::c_int];
static mut base_dist: [std::os::raw::c_int; 30] =
    [0 as std::os::raw::c_int, 1 as std::os::raw::c_int, 2 as std::os::raw::c_int, 3 as std::os::raw::c_int,
     4 as std::os::raw::c_int, 6 as std::os::raw::c_int, 8 as std::os::raw::c_int, 12 as std::os::raw::c_int,
     16 as std::os::raw::c_int, 24 as std::os::raw::c_int, 32 as std::os::raw::c_int,
     48 as std::os::raw::c_int, 64 as std::os::raw::c_int, 96 as std::os::raw::c_int,
     128 as std::os::raw::c_int, 192 as std::os::raw::c_int, 256 as std::os::raw::c_int,
     384 as std::os::raw::c_int, 512 as std::os::raw::c_int, 768 as std::os::raw::c_int,
     1024 as std::os::raw::c_int, 1536 as std::os::raw::c_int, 2048 as std::os::raw::c_int,
     3072 as std::os::raw::c_int, 4096 as std::os::raw::c_int, 6144 as std::os::raw::c_int,
     8192 as std::os::raw::c_int, 12288 as std::os::raw::c_int, 16384 as std::os::raw::c_int,
     24576 as std::os::raw::c_int];
/* max bit length for the codes */
static mut static_l_desc: static_tree_desc =
    unsafe {
        {
            let mut init =
                static_tree_desc_s{static_tree: static_ltree.as_ptr(),
                                   extra_bits: extra_lbits.as_ptr(),
                                   extra_base:
                                       256 as std::os::raw::c_int + 1 as std::os::raw::c_int,
                                   elems:
                                       256 as std::os::raw::c_int + 1 as std::os::raw::c_int +
                                           29 as std::os::raw::c_int,
                                   max_length: 15 as std::os::raw::c_int,};
            init
        }
    };
static mut static_d_desc: static_tree_desc =
    unsafe {
        {
            let mut init =
                static_tree_desc_s{static_tree: static_dtree.as_ptr(),
                                   extra_bits: extra_dbits.as_ptr(),
                                   extra_base: 0 as std::os::raw::c_int,
                                   elems: 30 as std::os::raw::c_int,
                                   max_length: 15 as std::os::raw::c_int,};
            init
        }
    };
static mut static_bl_desc: static_tree_desc =
    unsafe {
        {
            let mut init =
                static_tree_desc_s{static_tree: 0 as *const ct_data,
                                   extra_bits: extra_blbits.as_ptr(),
                                   extra_base: 0 as std::os::raw::c_int,
                                   elems: 19 as std::os::raw::c_int,
                                   max_length: 7 as std::os::raw::c_int,};
            init
        }
    };
/* ===========================================================================
 * Local (static) routines in this file.
 */
/* Send a code of the given tree. c and tree must not have side effects */
/* !ZLIB_DEBUG */
/* ===========================================================================
 * Output a short LSB first on the stream.
 * IN assertion: there is enough room in pendingBuf.
 */
/* ===========================================================================
 * Send a value on a given number of bits.
 * IN assertion: length <= 16 and value fits in length bits.
 */
/* !ZLIB_DEBUG */
/* ZLIB_DEBUG */
/* the arguments must not have side effects */
/* ===========================================================================
 * Initialize the various 'constant' tables.
 */
 fn tr_static_init() {
    // Implementation details would go here, based on the context of the original function.
    // Since the original function does not perform any operations, we can leave it empty.
}

/* ===========================================================================
 * Genererate the file trees.h describing the static trees.
 */
/* GEN_TREES_H */
/* ===========================================================================
 * Initialize the tree data structures for a new zlib stream.
 */
#[no_mangle]
pub fn _tr_init(s: &mut deflate_state) {
    tr_static_init();
    s.l_desc.dyn_tree = s.dyn_ltree.as_mut_ptr();
    s.l_desc.stat_desc = unsafe { &static_l_desc };
    s.d_desc.dyn_tree = s.dyn_dtree.as_mut_ptr();
    s.d_desc.stat_desc = unsafe { &static_d_desc };
    s.bl_desc.dyn_tree = s.bl_tree.as_mut_ptr();
    s.bl_desc.stat_desc = unsafe { &static_bl_desc };
    s.bi_buf = 0u16; // Assuming ush is equivalent to u16
    s.bi_valid = 0;
    /* Initialize the first block of the first file: */
    init_block(s);
}

/* ===========================================================================
 * Initialize a new block.
 */
fn init_block(s: &mut deflate_state) {
    let mut n: i32 = 0; // iterates over tree elements
    // Initialize the trees.
    while n < 256 + 1 + 29 {
        s.dyn_ltree[n as usize].fc.freq = 0;
        n += 1;
    }
    n = 0;
    while n < 30 {
        s.dyn_dtree[n as usize].fc.freq = 0;
        n += 1;
    }
    n = 0;
    while n < 19 {
        s.bl_tree[n as usize].fc.freq = 0;
        n += 1;
    }
    s.dyn_ltree[256 as usize].fc.freq = 1;
    s.static_len = 0;
    s.opt_len = s.static_len;
    s.matches = 0;
    s.last_lit = s.matches;
}

/* ===========================================================================
 * Restore the heap property by moving down the tree starting at node k,
 * exchanging a node with the smallest of its two sons if necessary, stopping
 * when the heap property is re-established (each father smaller than its
 * two sons).
 */
unsafe extern "C" fn pqdownheap(mut s: *mut deflate_state,
                                mut tree: *mut ct_data, mut k: std::os::raw::c_int) 
 /* node to move down */
 {
    let mut v: std::os::raw::c_int = (*s).heap[k as usize]; /* left son of k */
    let mut j: std::os::raw::c_int = k << 1 as std::os::raw::c_int;
    while j <= (*s).heap_len {
        /* Set j to the smallest of the two sons: */
        if j < (*s).heap_len &&
               (((*tree.offset((*s).heap[(j + 1 as std::os::raw::c_int) as usize] as
                                   isize)).fc.freq as std::os::raw::c_int) <
                    (*tree.offset((*s).heap[j as usize] as isize)).fc.freq as
                        std::os::raw::c_int ||
                    (*tree.offset((*s).heap[(j + 1 as std::os::raw::c_int) as usize]
                                      as isize)).fc.freq as std::os::raw::c_int ==
                        (*tree.offset((*s).heap[j as usize] as isize)).fc.freq
                            as std::os::raw::c_int &&
                        (*s).depth[(*s).heap[(j + 1 as std::os::raw::c_int) as usize]
                                       as usize] as std::os::raw::c_int <=
                            (*s).depth[(*s).heap[j as usize] as usize] as
                                std::os::raw::c_int) {
            j += 1
        }
        /* Exit if v is smaller than both sons */
        if ((*tree.offset(v as isize)).fc.freq as std::os::raw::c_int) <
               (*tree.offset((*s).heap[j as usize] as isize)).fc.freq as
                   std::os::raw::c_int ||
               (*tree.offset(v as isize)).fc.freq as std::os::raw::c_int ==
                   (*tree.offset((*s).heap[j as usize] as isize)).fc.freq as
                       std::os::raw::c_int &&
                   (*s).depth[v as usize] as std::os::raw::c_int <=
                       (*s).depth[(*s).heap[j as usize] as usize] as
                           std::os::raw::c_int {
            break ;
        }
        /* Exchange v with the smallest son */
        (*s).heap[k as usize] = (*s).heap[j as usize];
        k = j;
        /* And continue down the tree, setting j to the left son of k */
        j <<= 1 as std::os::raw::c_int
    }
    (*s).heap[k as usize] = v;
}
/* ===========================================================================
 * Compute the optimal bit lengths for a tree and update the total bit length
 * for the current block.
 * IN assertion: the fields freq and dad are set, heap[heap_max] and
 *    above are the tree nodes sorted by increasing frequency.
 * OUT assertions: the field len is set to the optimal bit length, the
 *     array bl_count contains the frequencies for each bit length.
 *     The length opt_len is updated; static_len is also updated if stree is
 *     not null.
 */
unsafe extern "C" fn gen_bitlen(mut s: *mut deflate_state,
                                mut desc: *mut tree_desc) 
 /* the tree descriptor */
 {
    let mut tree: *mut ct_data = (*desc).dyn_tree; /* heap index */
    let mut max_code: std::os::raw::c_int =
        (*desc).max_code; /* iterate over the tree elements */
    let mut stree: *const ct_data =
        (*(*desc).stat_desc).static_tree; /* bit length */
    let mut extra: *const intf =
        (*(*desc).stat_desc).extra_bits; /* extra bits */
    let mut base: std::os::raw::c_int =
        (*(*desc).stat_desc).extra_base; /* frequency */
    let mut max_length: std::os::raw::c_int =
        (*(*desc).stat_desc).max_length; /* number of elements with bit length too large */
    let mut h: std::os::raw::c_int = 0;
    let mut n: std::os::raw::c_int = 0;
    let mut m: std::os::raw::c_int = 0;
    let mut bits: std::os::raw::c_int = 0;
    let mut xbits: std::os::raw::c_int = 0;
    let mut f: ush = 0;
    let mut overflow: std::os::raw::c_int = 0 as std::os::raw::c_int;
    bits = 0 as std::os::raw::c_int;
    while bits <= 15 as std::os::raw::c_int {
        (*s).bl_count[bits as usize] = 0 as std::os::raw::c_int as ush;
        bits += 1
    }
    /* In a first pass, compute the optimal bit lengths (which may
     * overflow in the case of the bit length tree).
     */
    (*tree.offset((*s).heap[(*s).heap_max as usize] as isize)).dl.len =
        0 as std::os::raw::c_int as ush; /* root of the heap */
    h = (*s).heap_max + 1 as std::os::raw::c_int;
    while h <
              2 as std::os::raw::c_int *
                  (256 as std::os::raw::c_int + 1 as std::os::raw::c_int + 29 as std::os::raw::c_int)
                  + 1 as std::os::raw::c_int {
        n = (*s).heap[h as usize];
        bits =
            (*tree.offset((*tree.offset(n as isize)).dl.dad as isize)).dl.len
                as std::os::raw::c_int + 1 as std::os::raw::c_int;
        if bits > max_length { bits = max_length; overflow += 1 }
        (*tree.offset(n as isize)).dl.len = bits as ush;
        /* We overwrite tree[n].Dad which is no longer needed */
        if !(n > max_code) {
            (*s).bl_count[bits as usize] =
                (*s).bl_count[bits as
                                  usize].wrapping_add(1); /* not a leaf node */
            xbits = 0 as std::os::raw::c_int;
            if n >= base { xbits = *extra.offset((n - base) as isize) }
            f = (*tree.offset(n as isize)).fc.freq;
            (*s).opt_len =
                ((*s).opt_len as
                     std::os::raw::c_ulong).wrapping_add((f as
                                                      ulg).wrapping_mul((bits
                                                                             +
                                                                             xbits)
                                                                            as
                                                                            std::os::raw::c_uint
                                                                            as
                                                                            std::os::raw::c_ulong))
                    as ulg as ulg;
            if !stree.is_null() {
                (*s).static_len =
                    ((*s).static_len as
                         std::os::raw::c_ulong).wrapping_add((f as
                                                          ulg).wrapping_mul(((*stree.offset(n
                                                                                                as
                                                                                                isize)).dl.len
                                                                                 as
                                                                                 std::os::raw::c_int
                                                                                 +
                                                                                 xbits)
                                                                                as
                                                                                std::os::raw::c_uint
                                                                                as
                                                                                std::os::raw::c_ulong))
                        as ulg as ulg
            }
        }
        h += 1
    }
    if overflow == 0 as std::os::raw::c_int { return }
    loop 
         /* This happens for example on obj2 and pic of the Calgary corpus */
         /* Find the first bit length which could increase: */
         {
        bits =
            max_length - 1 as std::os::raw::c_int; /* move one leaf down the tree */
        while (*s).bl_count[bits as usize] as std::os::raw::c_int == 0 as std::os::raw::c_int
              {
            bits -= 1
        } /* move one overflow item as its brother */
        (*s).bl_count[bits as usize] =
            (*s).bl_count[bits as usize].wrapping_sub(1);
        (*s).bl_count[(bits + 1 as std::os::raw::c_int) as usize] =
            ((*s).bl_count[(bits + 1 as std::os::raw::c_int) as usize] as std::os::raw::c_int
                 + 2 as std::os::raw::c_int) as ush;
        (*s).bl_count[max_length as usize] =
            (*s).bl_count[max_length as usize].wrapping_sub(1);
        /* The brother of the overflow item also moves one step up,
         * but this does not affect bl_count[max_length]
         */
        overflow -= 2 as std::os::raw::c_int;
        if !(overflow > 0 as std::os::raw::c_int) { break ; }
    }
    /* Now recompute all bit lengths, scanning in increasing frequency.
     * h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
     * lengths instead of fixing only the wrong ones. This idea is taken
     * from 'ar' written by Haruhiko Okumura.)
     */
    bits = max_length;
    while bits != 0 as std::os::raw::c_int {
        n = (*s).bl_count[bits as usize] as std::os::raw::c_int;
        while n != 0 as std::os::raw::c_int {
            h -= 1;
            m = (*s).heap[h as usize];
            if m > max_code { continue ; }
            if (*tree.offset(m as isize)).dl.len as std::os::raw::c_uint !=
                   bits as std::os::raw::c_uint {
                (*s).opt_len =
                    ((*s).opt_len as
                         std::os::raw::c_ulong).wrapping_add((bits as
                                                          ulg).wrapping_sub((*tree.offset(m
                                                                                              as
                                                                                              isize)).dl.len
                                                                                as
                                                                                std::os::raw::c_ulong).wrapping_mul((*tree.offset(m
                                                                                                                              as
                                                                                                                              isize)).fc.freq
                                                                                                                as
                                                                                                                std::os::raw::c_ulong))
                        as ulg as ulg;
                (*tree.offset(m as isize)).dl.len = bits as ush
            }
            n -= 1
        }
        bits -= 1
    };
}
/* ===========================================================================
 * Generate the codes for a given tree and bit counts (which need not be
 * optimal).
 * IN assertion: the array bl_count contains the bit length statistics for
 * the given tree and the field len is set for all tree elements.
 * OUT assertion: the field code is set for all tree elements of non
 *     zero code length.
 */
fn gen_codes(tree: &mut [ct_data], max_code: i32, bl_count: &mut [ush]) {
    let mut next_code: [ush; 16] = [0; 16]; // next code value for each bit length
    let mut code: u32 = 0; // running code value
    let mut bits: i32 = 1; // bit index
    let mut n: i32 = 0; // code index

    // The distribution counts are first used to generate the code values without bit reversal.
    while bits <= 15 {
        code = code.wrapping_add(bl_count[(bits - 1) as usize] as u32) << 1;
        next_code[bits as usize] = code as ush;
        bits += 1;
    }

    // Check that the bit counts in bl_count are consistent. The last code must be all ones.
    while n <= max_code {
        // Accessing union field requires unsafe block
        let len: i32 = unsafe { tree[n as usize].dl.len.into() }; // Convert u16 to i32
        if len != 0 {
            // Now reverse the bits
            let fresh0 = next_code[len as usize];
            next_code[len as usize] = next_code[len as usize].wrapping_add(1);
            tree[n as usize].fc.code = bi_reverse(fresh0 as u32, len) as ush;
        }
        n += 1;
    }
}

/* ===========================================================================
 * Construct one Huffman tree and assigns the code bit strings and lengths.
 * Update the total bit length for the current block.
 * IN assertion: the field freq is set for all tree elements.
 * OUT assertions: the fields len and code are set to the optimal bit length
 *     and corresponding code. The length opt_len is updated; static_len is
 *     also updated if stree is not null. The field max_code is set.
 */
unsafe extern "C" fn build_tree(mut s: *mut deflate_state,
                                mut desc: *mut tree_desc) 
 /* the tree descriptor */
 {
    let mut tree: *mut ct_data =
        (*desc).dyn_tree; /* iterate over heap elements */
    let mut stree: *const ct_data =
        (*(*desc).stat_desc).static_tree; /* largest code with non zero frequency */
    let mut elems: std::os::raw::c_int =
        (*(*desc).stat_desc).elems; /* new node being created */
    let mut n: std::os::raw::c_int = 0;
    let mut m: std::os::raw::c_int = 0;
    let mut max_code: std::os::raw::c_int = -(1 as std::os::raw::c_int);
    let mut node: std::os::raw::c_int = 0;
    /* Construct the initial heap, with least frequent element in
     * heap[SMALLEST]. The sons of heap[n] are heap[2*n] and heap[2*n+1].
     * heap[0] is not used.
     */
    (*s).heap_len = 0 as std::os::raw::c_int;
    (*s).heap_max =
        2 as std::os::raw::c_int *
            (256 as std::os::raw::c_int + 1 as std::os::raw::c_int + 29 as std::os::raw::c_int) +
            1 as std::os::raw::c_int;
    n = 0 as std::os::raw::c_int;
    while n < elems {
        if (*tree.offset(n as isize)).fc.freq as std::os::raw::c_int !=
               0 as std::os::raw::c_int {
            max_code = n;
            (*s).heap_len += 1;
            (*s).heap[(*s).heap_len as usize] = max_code;
            (*s).depth[n as usize] = 0 as std::os::raw::c_int as uch
        } else { (*tree.offset(n as isize)).dl.len = 0 as std::os::raw::c_int as ush }
        n += 1
    }
    /* The pkzip format requires that at least one distance code exists,
     * and that at least one bit should be sent even if there is only one
     * possible code. So to avoid special checks later on we force at least
     * two codes of non zero frequency.
     */
    while (*s).heap_len < 2 as std::os::raw::c_int {
        (*s).heap_len += 1;
        (*s).heap[(*s).heap_len as usize] =
            if max_code < 2 as std::os::raw::c_int {
                max_code += 1;
                max_code
            } else { 0 as std::os::raw::c_int };
        node = (*s).heap[(*s).heap_len as usize];
        (*tree.offset(node as isize)).fc.freq = 1 as std::os::raw::c_int as ush;
        (*s).depth[node as usize] = 0 as std::os::raw::c_int as uch;
        (*s).opt_len = (*s).opt_len.wrapping_sub(1);
        if !stree.is_null() {
            (*s).static_len =
                ((*s).static_len as
                     std::os::raw::c_ulong).wrapping_sub((*stree.offset(node as
                                                                    isize)).dl.len
                                                     as std::os::raw::c_ulong) as ulg
                    as ulg
        }
        /* node is 0 or 1 so it does not have extra bits */
    }
    (*desc).max_code = max_code;
    /* The elements heap[heap_len/2+1 .. heap_len] are leaves of the tree,
     * establish sub-heaps of increasing lengths:
     */
    n = (*s).heap_len / 2 as std::os::raw::c_int;
    while n >= 1 as std::os::raw::c_int { pqdownheap(s, tree, n); n -= 1 }
    /* Construct the Huffman tree by repeatedly combining the least two
     * frequent nodes.
     */
    node = elems; /* next internal node of the tree */
    loop  {
        n = (*s).heap[1 as std::os::raw::c_int as usize];
        let fresh1 = (*s).heap_len;
        (*s).heap_len = (*s).heap_len - 1;
        (*s).heap[1 as std::os::raw::c_int as usize] = (*s).heap[fresh1 as usize];
        pqdownheap(s, tree, 1 as std::os::raw::c_int);
        /* n = node of least frequency */
        m =
            (*s).heap[1 as std::os::raw::c_int as
                          usize]; /* m = node of next least frequency */
        (*s).heap_max -= 1; /* keep the nodes sorted by frequency */
        (*s).heap[(*s).heap_max as usize] = n;
        (*s).heap_max -= 1;
        (*s).heap[(*s).heap_max as usize] = m;
        (*tree.offset(node as isize)).fc.freq =
            ((*tree.offset(n as isize)).fc.freq as std::os::raw::c_int +
                 (*tree.offset(m as isize)).fc.freq as std::os::raw::c_int) as ush;
        (*s).depth[node as usize] =
            ((if (*s).depth[n as usize] as std::os::raw::c_int >=
                     (*s).depth[m as usize] as std::os::raw::c_int {
                  (*s).depth[n as usize] as std::os::raw::c_int
              } else { (*s).depth[m as usize] as std::os::raw::c_int }) +
                 1 as std::os::raw::c_int) as uch;
        let ref mut fresh2 = (*tree.offset(m as isize)).dl.dad;
        *fresh2 = node as ush;
        (*tree.offset(n as isize)).dl.dad = *fresh2;
        let fresh3 = node;
        node = node + 1;
        (*s).heap[1 as std::os::raw::c_int as usize] = fresh3;
        pqdownheap(s, tree, 1 as std::os::raw::c_int);
        if !((*s).heap_len >= 2 as std::os::raw::c_int) { break ; }
    }
    (*s).heap_max -= 1;
    (*s).heap[(*s).heap_max as usize] = (*s).heap[1 as std::os::raw::c_int as usize];
    /* Create a new node father of n and m */
    /* and insert the new node in the heap */
    /* At this point, the fields freq and dad are set. We can now
     * generate the bit lengths.
     */
    gen_bitlen(s, desc);
    /* The field len is now set, we can generate the bit codes */
    let bl_count_ptr = &mut (*s).bl_count;
let tree_slice: &mut [ct_data] = unsafe { std::slice::from_raw_parts_mut(tree, max_code as usize + 1) }; // Convert raw pointer to mutable slice
gen_codes(tree_slice, max_code, bl_count_ptr);
}
/* ===========================================================================
 * Scan a literal or distance tree to determine the frequencies of the codes
 * in the bit length tree.
 */
unsafe extern "C" fn scan_tree(mut s: *mut deflate_state,
                               mut tree: *mut ct_data,
                               mut max_code: std::os::raw::c_int) 
 /* and its largest code of non zero frequency */
 {
    let mut n: std::os::raw::c_int = 0; /* iterates over all tree elements */
    let mut prevlen: std::os::raw::c_int =
        -(1 as std::os::raw::c_int); /* last emitted length */
    let mut curlen: std::os::raw::c_int = 0; /* length of current code */
    let mut nextlen: std::os::raw::c_int =
        (*tree.offset(0 as std::os::raw::c_int as isize)).dl.len as
            std::os::raw::c_int; /* length of next code */
    let mut count: std::os::raw::c_int =
        0 as std::os::raw::c_int; /* repeat count of the current code */
    let mut max_count: std::os::raw::c_int = 7 as std::os::raw::c_int; /* max repeat count */
    let mut min_count: std::os::raw::c_int = 4 as std::os::raw::c_int; /* min repeat count */
    if nextlen == 0 as std::os::raw::c_int {
        max_count = 138 as std::os::raw::c_int; /* guard */
        min_count = 3 as std::os::raw::c_int
    }
    (*tree.offset((max_code + 1 as std::os::raw::c_int) as isize)).dl.len =
        0xffff as std::os::raw::c_int as ush;
    n = 0 as std::os::raw::c_int;
    while n <= max_code {
        curlen = nextlen;
        nextlen =
            (*tree.offset((n + 1 as std::os::raw::c_int) as isize)).dl.len as
                std::os::raw::c_int;
        count += 1;
        if !(count < max_count && curlen == nextlen) {
            if count < min_count {
                (*s).bl_tree[curlen as usize].fc.freq =
                    ((*s).bl_tree[curlen as usize].fc.freq as std::os::raw::c_int +
                         count) as ush
            } else if curlen != 0 as std::os::raw::c_int {
                if curlen != prevlen {
                    (*s).bl_tree[curlen as usize].fc.freq =
                        (*s).bl_tree[curlen as usize].fc.freq.wrapping_add(1)
                }
                (*s).bl_tree[16 as std::os::raw::c_int as usize].fc.freq =
                    (*s).bl_tree[16 as std::os::raw::c_int as
                                     usize].fc.freq.wrapping_add(1)
            } else if count <= 10 as std::os::raw::c_int {
                (*s).bl_tree[17 as std::os::raw::c_int as usize].fc.freq =
                    (*s).bl_tree[17 as std::os::raw::c_int as
                                     usize].fc.freq.wrapping_add(1)
            } else {
                (*s).bl_tree[18 as std::os::raw::c_int as usize].fc.freq =
                    (*s).bl_tree[18 as std::os::raw::c_int as
                                     usize].fc.freq.wrapping_add(1)
            }
            count = 0 as std::os::raw::c_int;
            prevlen = curlen;
            if nextlen == 0 as std::os::raw::c_int {
                max_count = 138 as std::os::raw::c_int;
                min_count = 3 as std::os::raw::c_int
            } else if curlen == nextlen {
                max_count = 6 as std::os::raw::c_int;
                min_count = 3 as std::os::raw::c_int
            } else {
                max_count = 7 as std::os::raw::c_int;
                min_count = 4 as std::os::raw::c_int
            }
        }
        n += 1
    };
}
/* ===========================================================================
 * Send a literal or distance tree in compressed form, using the codes in
 * bl_tree.
 */
unsafe extern "C" fn send_tree(mut s: *mut deflate_state,
                               mut tree: *mut ct_data,
                               mut max_code: std::os::raw::c_int) 
 /* and its largest code of non zero frequency */
 {
    let mut n: std::os::raw::c_int = 0; /* iterates over all tree elements */
    let mut prevlen: std::os::raw::c_int =
        -(1 as std::os::raw::c_int); /* last emitted length */
    let mut curlen: std::os::raw::c_int = 0; /* length of current code */
    let mut nextlen: std::os::raw::c_int =
        (*tree.offset(0 as std::os::raw::c_int as isize)).dl.len as
            std::os::raw::c_int; /* length of next code */
    let mut count: std::os::raw::c_int =
        0 as std::os::raw::c_int; /* repeat count of the current code */
    let mut max_count: std::os::raw::c_int = 7 as std::os::raw::c_int; /* max repeat count */
    let mut min_count: std::os::raw::c_int = 4 as std::os::raw::c_int; /* min repeat count */
    /* tree[max_code+1].Len = -1; */
    /* guard already set */
    if nextlen == 0 as std::os::raw::c_int {
        max_count = 138 as std::os::raw::c_int;
        min_count = 3 as std::os::raw::c_int
    }
    n = 0 as std::os::raw::c_int;
    let mut n = 0; // Assuming n is initialized appropriately before this loop
while n <= max_code {
    curlen = nextlen;
    nextlen = unsafe { (*tree.offset((n + 1) as isize)).dl.len as i32 }; // Convert u16 to i32
    count += 1;
    if !(count < max_count && curlen == nextlen) {
         if count < min_count {
     loop {
    let len: i32 = unsafe { (*s).bl_tree[curlen as usize].dl.len.into() };
    if unsafe { (*s).bi_valid } > 16 - len {
        let val: i32 = unsafe { (*s).bl_tree[curlen as usize].fc.code.into() };
        unsafe { (*s).bi_buf |= (val as u16) << unsafe { (*s).bi_valid } };
        let pending_index = unsafe { (*s).pending };
        unsafe { *(*s).pending_buf.add(pending_index as usize) = (unsafe { (*s).bi_buf } & 0xff) as u8 };
        unsafe { (*s).pending += 1 };
        let pending_index = unsafe { (*s).pending };
        unsafe { *(*s).pending_buf.add(pending_index as usize) = (unsafe { (*s).bi_buf } >> 8) as u8 };
        unsafe { (*s).pending += 1 };
        unsafe { (*s).bi_buf = (val >> (16 - unsafe { (*s).bi_valid })) as u16 };
        unsafe { (*s).bi_valid += len - 16 };
    } else {
        unsafe { (*s).bi_buf |= (unsafe { (*s).bl_tree[curlen as usize].fc.code }) << unsafe { (*s).bi_valid } };
        unsafe { (*s).bi_valid += len };
    }
    count -= 1;
    if count == 0 { break; }
}


} else if curlen != 0 {
     if curlen != prevlen {
                    let mut len_0: std::os::raw::c_int =
                        (*s).bl_tree[curlen as usize].dl.len as std::os::raw::c_int;
                    if (*s).bi_valid > 16 as std::os::raw::c_int - len_0 {
                        let mut val_0: std::os::raw::c_int =
                            (*s).bl_tree[curlen as usize].fc.code as
                                std::os::raw::c_int;
                        (*s).bi_buf =
                            ((*s).bi_buf as std::os::raw::c_int |
                                 (val_0 as ush as std::os::raw::c_int) <<
                                     (*s).bi_valid) as ush;
                        let fresh6 = (*s).pending;
                        (*s).pending = (*s).pending.wrapping_add(1);
                        *(*s).pending_buf.offset(fresh6 as isize) =
                            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int)
                                as uch;
                        let fresh7 = (*s).pending;
                        (*s).pending = (*s).pending.wrapping_add(1);
                        *(*s).pending_buf.offset(fresh7 as isize) =
                            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int)
                                as uch;
                        (*s).bi_buf =
                            (val_0 as ush as std::os::raw::c_int >>
                                 16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                        (*s).bi_valid += len_0 - 16 as std::os::raw::c_int
                    } else {
                        (*s).bi_buf =
                            ((*s).bi_buf as std::os::raw::c_int |
                                 ((*s).bl_tree[curlen as usize].fc.code as
                                      std::os::raw::c_int) << (*s).bi_valid) as ush;
                        (*s).bi_valid += len_0
                    }
                    count -= 1
                }
                let mut len_1: std::os::raw::c_int =
                    (*s).bl_tree[16 as std::os::raw::c_int as usize].dl.len as
                        std::os::raw::c_int;
                if (*s).bi_valid > 16 as std::os::raw::c_int - len_1 {
                    let mut val_1: std::os::raw::c_int =
                        (*s).bl_tree[16 as std::os::raw::c_int as usize].fc.code as
                            std::os::raw::c_int;
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             (val_1 as ush as std::os::raw::c_int) << (*s).bi_valid)
                            as ush;
                    let fresh8 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh8 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                            uch;
                    let fresh9 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh9 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as
                            uch;
                    (*s).bi_buf =
                        (val_1 as ush as std::os::raw::c_int >>
                             16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                    (*s).bi_valid += len_1 - 16 as std::os::raw::c_int
                } else {
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             ((*s).bl_tree[16 as std::os::raw::c_int as usize].fc.code
                                  as std::os::raw::c_int) << (*s).bi_valid) as ush;
                    (*s).bi_valid += len_1
                }
                let mut len_2: std::os::raw::c_int = 2 as std::os::raw::c_int;
                if (*s).bi_valid > 16 as std::os::raw::c_int - len_2 {
                    let mut val_2: std::os::raw::c_int = count - 3 as std::os::raw::c_int;
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             (val_2 as ush as std::os::raw::c_int) << (*s).bi_valid)
                            as ush;
                    let fresh10 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh10 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                            uch;
                    let fresh11 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh11 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as
                            uch;
                    (*s).bi_buf =
                        (val_2 as ush as std::os::raw::c_int >>
                             16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                    (*s).bi_valid += len_2 - 16 as std::os::raw::c_int
                } else {
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             ((count - 3 as std::os::raw::c_int) as ush as
                                  std::os::raw::c_int) << (*s).bi_valid) as ush;
                    (*s).bi_valid += len_2
                }

} else if count <= 10 {
     let len_3: i32 = unsafe { (*s).bl_tree[17].dl.len as i32 };
if unsafe { (*s).bi_valid } > 16 - len_3 {
    let val_3: i32 = unsafe { (*s).bl_tree[17].fc.code as i32 };
    unsafe {
        (*s).bi_buf |= (val_3 as u16) << (*s).bi_valid;
        *(*s).pending_buf.offset((*s).pending as isize) = ((*s).bi_buf & 0xff) as u8;
        (*s).pending += 1;
        *(*s).pending_buf.offset((*s).pending as isize) = ((*s).bi_buf >> 8) as u8;
        (*s).pending += 1;
        (*s).bi_buf = (val_3 >> (16 - (*s).bi_valid)) as u16;
        (*s).bi_valid += len_3 - 16;
    }
} else {
    unsafe {
        (*s).bi_buf |= (unsafe { (*s).bl_tree[17].fc.code } << (*s).bi_valid) as u16;
        (*s).bi_valid += len_3;
    }
}

let len_4: i32 = 3;
if unsafe { (*s).bi_valid } > 16 - len_4 {
    let val_4: i32 = count - 3;
    unsafe {
        (*s).bi_buf |= (val_4 as u16) << (*s).bi_valid;
        *(*s).pending_buf.offset((*s).pending as isize) = ((*s).bi_buf & 0xff) as u8;
        (*s).pending += 1;
        *(*s).pending_buf.offset((*s).pending as isize) = ((*s).bi_buf >> 8) as u8;
        (*s).pending += 1;
        (*s).bi_buf = (val_4 >> (16 - (*s).bi_valid)) as u16;
        (*s).bi_valid += len_4 - 16;
    }
} else {
    unsafe {
        (*s).bi_buf |= ((count - 3) as u16) << (*s).bi_valid;
        (*s).bi_valid += len_4;
    }
}


} else {
     let len_5: i32 = unsafe { (*s).bl_tree[18].dl.len.into() };
if unsafe { (*s).bi_valid } > 16 - len_5 {
    let val_5: i32 = unsafe { (*s).bl_tree[18].fc.code.into() };
    unsafe {
        (*s).bi_buf |= (val_5 as u16) << (*s).bi_valid;
        let fresh16 = (*s).pending;
        (*s).pending += 1;
        *(*s).pending_buf.offset(fresh16 as isize) = ((*s).bi_buf & 0xff) as u8;
        let fresh17 = (*s).pending;
        (*s).pending += 1;
        *(*s).pending_buf.offset(fresh17 as isize) = ((*s).bi_buf >> 8) as u8;
        (*s).bi_buf = (val_5 >> (16 - (*s).bi_valid)) as u16;
        (*s).bi_valid += len_5 - 16;
    }
} else {
    unsafe {
        (*s).bi_buf |= (unsafe { (*s).bl_tree[18].fc.code } << (*s).bi_valid) as u16;
        (*s).bi_valid += len_5;
    }
}

let len_6: i32 = 7;
if unsafe { (*s).bi_valid } > 16 - len_6 {
    let val_6: i32 = count - 11;
    unsafe {
        (*s).bi_buf |= (val_6 as u16) << (*s).bi_valid;
        let fresh18 = (*s).pending;
        (*s).pending += 1;
        *(*s).pending_buf.offset(fresh18 as isize) = ((*s).bi_buf & 0xff) as u8;
        let fresh19 = (*s).pending;
        (*s).pending += 1;
        *(*s).pending_buf.offset(fresh19 as isize) = ((*s).bi_buf >> 8) as u8;
        (*s).bi_buf = (val_6 >> (16 - (*s).bi_valid)) as u16;
        (*s).bi_valid += len_6 - 16;
    }
} else {
    unsafe {
        (*s).bi_buf |= ((count - 11) as u16) << (*s).bi_valid;
        (*s).bi_valid += len_6;
    }
}


}
count = 0;
prevlen = curlen;
if nextlen == 0 {
    max_count = 138;
    min_count = 3;
} else if curlen == nextlen {
    max_count = 6;
    min_count = 3;
} else {
    max_count = 7;
    min_count = 4;
}
/*
The variables live at this point are:
(mut s: &mut src::zlib::deflate::InternalState, mut prevlen: i32, mut curlen: i32, mut nextlen: i32, mut count: i32, mut max_count: i32, mut min_count: i32)
*/


    }
    n += 1;
}
;
}
/* ===========================================================================
 * Construct the Huffman tree for the bit lengths and return the index in
 * bl_order of the last bit length code to send.
 */
fn build_bl_tree(s: &mut deflate_state) -> std::os::raw::c_int {
    let mut max_blindex: std::os::raw::c_int = 0; // index of last bit length code of non zero freq

    // Determine the bit length frequencies for literal and distance trees
    unsafe {
        scan_tree(s, s.dyn_ltree.as_mut_ptr(), s.l_desc.max_code);
        scan_tree(s, s.dyn_dtree.as_mut_ptr(), s.d_desc.max_code);
        build_tree(s, &mut s.bl_desc);
    }

    // Determine the number of bit length codes to send. The pkzip format
    // requires that at least 4 bit length codes be sent.
    max_blindex = 19 - 1;
    while max_blindex >= 3 {
        unsafe {
            if s.bl_tree[bl_order[max_blindex as usize] as usize].dl.len != 0 {
                break;
            }
        }
        max_blindex -= 1;
    }

    // Update opt_len to include the bit length tree and counts
    s.opt_len = s.opt_len.wrapping_add(
        (3 * (max_blindex as ulg + 1))
            .wrapping_add(5)
            .wrapping_add(5)
            .wrapping_add(4) as std::os::raw::c_ulong,
    ) as ulg;

    max_blindex
}

/* ===========================================================================
 * Send the header for a block using dynamic Huffman trees: the counts, the
 * lengths of the bit length codes, the literal tree and the distance tree.
 * IN assertion: lcodes >= 257, dcodes >= 1, blcodes >= 4.
 */
unsafe extern "C" fn send_all_trees(mut s: *mut deflate_state,
                                    mut lcodes: std::os::raw::c_int,
                                    mut dcodes: std::os::raw::c_int,
                                    mut blcodes: std::os::raw::c_int) 
 /* number of codes for each tree */
 {
    let mut rank: std::os::raw::c_int = 0; /* index in bl_order */
    let mut len: std::os::raw::c_int = 5 as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len {
        let mut val: std::os::raw::c_int = lcodes - 257 as std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh20 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh20 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh21 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh21 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 ((lcodes - 257 as std::os::raw::c_int) as ush as std::os::raw::c_int) <<
                     (*s).bi_valid) as ush;
        (*s).bi_valid += len
    }
    /* not +255 as stated in appnote.txt */
    let mut len_0: std::os::raw::c_int = 5 as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len_0 {
        let mut val_0: std::os::raw::c_int = dcodes - 1 as std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val_0 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh22 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh22 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh23 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh23 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val_0 as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len_0 - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 ((dcodes - 1 as std::os::raw::c_int) as ush as std::os::raw::c_int) <<
                     (*s).bi_valid) as ush;
        (*s).bi_valid += len_0
    }
    let mut len_1: std::os::raw::c_int = 4 as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len_1 {
        let mut val_1: std::os::raw::c_int = blcodes - 4 as std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val_1 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh24 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh24 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh25 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh25 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val_1 as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len_1 - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 ((blcodes - 4 as std::os::raw::c_int) as ush as std::os::raw::c_int) <<
                     (*s).bi_valid) as ush;
        (*s).bi_valid += len_1
    }
    /* not -3 as stated in appnote.txt */
    rank = 0 as std::os::raw::c_int; /* literal tree */
    while rank < blcodes {
        let mut len_2: std::os::raw::c_int = 3 as std::os::raw::c_int; /* distance tree */
        if (*s).bi_valid > 16 as std::os::raw::c_int - len_2 {
            let mut val_2: std::os::raw::c_int =
                (*s).bl_tree[bl_order[rank as usize] as usize].dl.len as
                    std::os::raw::c_int;
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     (val_2 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
            let fresh26 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh26 as isize) =
                ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
            let fresh27 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh27 as isize) =
                ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
            (*s).bi_buf =
                (val_2 as ush as std::os::raw::c_int >>
                     16 as std::os::raw::c_int - (*s).bi_valid) as ush;
            (*s).bi_valid += len_2 - 16 as std::os::raw::c_int
        } else {
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     ((*s).bl_tree[bl_order[rank as usize] as usize].dl.len as
                          std::os::raw::c_int) << (*s).bi_valid) as ush;
            (*s).bi_valid += len_2
        }
        rank += 1
    }
    send_tree(s, (*s).dyn_ltree.as_mut_ptr() as *mut ct_data,
              lcodes - 1 as std::os::raw::c_int);
    send_tree(s, (*s).dyn_dtree.as_mut_ptr() as *mut ct_data,
              dcodes - 1 as std::os::raw::c_int);
}
/* ===========================================================================
 * Send a stored block
 */
#[no_mangle]
pub unsafe extern "C" fn _tr_stored_block(mut s: *mut deflate_state,
                                          mut buf: *mut charf,
                                          mut stored_len: ulg,
                                          mut last: std::os::raw::c_int) 
 /* one if this is the last block for a file */
 {
    let mut len: std::os::raw::c_int = 3 as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len {
        let mut val: std::os::raw::c_int =
            ((0 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh28 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh28 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh29 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh29 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 ((((0 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last) as ush as
                      std::os::raw::c_int) << (*s).bi_valid) as ush;
        (*s).bi_valid += len
    }
    /* send block type */
    bi_windup(&mut *s); /* align on byte boundary */
    let fresh30 = (*s).pending;
    (*s).pending = (*s).pending.wrapping_add(1);
    *(*s).pending_buf.offset(fresh30 as isize) =
        (stored_len as ush as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
    let fresh31 = (*s).pending;
    (*s).pending = (*s).pending.wrapping_add(1);
    *(*s).pending_buf.offset(fresh31 as isize) =
        (stored_len as ush as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
    let fresh32 = (*s).pending;
    (*s).pending = (*s).pending.wrapping_add(1);
    *(*s).pending_buf.offset(fresh32 as isize) =
        (!stored_len as ush as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
    let fresh33 = (*s).pending;
    (*s).pending = (*s).pending.wrapping_add(1);
    *(*s).pending_buf.offset(fresh33 as isize) =
        (!stored_len as ush as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
    memcpy((*s).pending_buf.offset((*s).pending as isize) as
               *mut std::os::raw::c_void, buf as *mut Bytef as *const std::os::raw::c_void,
           stored_len);
    (*s).pending =
        ((*s).pending as std::os::raw::c_ulong).wrapping_add(stored_len) as ulg as
            ulg;
}
/* ===========================================================================
 * Flush the bits in the bit buffer to pending output (leaves at most 7 bits)
 */
#[no_mangle]
pub fn _tr_flush_bits(s: &mut crate::src::zlib::deflate::deflate_state) {
    bi_flush(s);
}

/* ===========================================================================
 * Send one empty static block to give enough lookahead for inflate.
 * This takes 10 bits, of which 7 may remain in the bit buffer.
 */
#[no_mangle]
pub unsafe extern "C" fn _tr_align(mut s: *mut deflate_state) {
    let mut len: std::os::raw::c_int = 3 as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len {
        let mut val: std::os::raw::c_int = (1 as std::os::raw::c_int) << 1 as std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh34 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh34 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh35 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh35 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (((1 as std::os::raw::c_int) << 1 as std::os::raw::c_int) as ush as
                      std::os::raw::c_int) << (*s).bi_valid) as ush;
        (*s).bi_valid += len
    }
    let mut len_0: std::os::raw::c_int =
        static_ltree[256 as std::os::raw::c_int as usize].dl.len as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len_0 {
        let mut val_0: std::os::raw::c_int =
            static_ltree[256 as std::os::raw::c_int as usize].fc.code as std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val_0 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh36 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh36 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh37 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh37 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val_0 as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len_0 - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (static_ltree[256 as std::os::raw::c_int as usize].fc.code as
                      std::os::raw::c_int) << (*s).bi_valid) as ush;
        (*s).bi_valid += len_0
    }
    bi_flush(&mut *s);
}
/* ===========================================================================
 * Determine the best encoding for the current block: dynamic trees, static
 * trees or store, and write out the encoded block.
 */
#[no_mangle]
pub unsafe extern "C" fn _tr_flush_block(mut s: *mut deflate_state,
                                         mut buf: *mut charf,
                                         mut stored_len: ulg,
                                         mut last: std::os::raw::c_int) 
 /* one if this is the last block for a file */
 {
    let mut opt_lenb: ulg = 0; /* opt_len and static_len in bytes */
    let mut static_lenb: ulg =
        0; /* index of last bit length code of non zero freq */
    let mut max_blindex: std::os::raw::c_int = 0 as std::os::raw::c_int;
    /* Build the Huffman trees unless a stored block is forced */
    if (*s).level > 0 as std::os::raw::c_int {
        /* Check if the file is binary or text */
        if (*(*s).strm).data_type == 2 as std::os::raw::c_int {
    let data_type = detect_data_type(&mut *s);
    (*(*s).strm).data_type = data_type;
}
        /* Construct the literal and distance trees */
        build_tree(s, &mut (*s).l_desc as *mut tree_desc_s as *mut tree_desc);
        build_tree(s, &mut (*s).d_desc as *mut tree_desc_s as *mut tree_desc);
        /* At this point, opt_len and static_len are the total bit lengths of
         * the compressed block data, excluding the tree representations.
         */
        /* Build the bit length tree for the above two trees, and get the index
         * in bl_order of the last bit length code to send.
         */
        let max_blindex = build_bl_tree(&mut *s);
        /* Determine the best encoding. Compute the block lengths in bytes. */
        opt_lenb =
            (*s).opt_len.wrapping_add(3 as std::os::raw::c_int as
                                          std::os::raw::c_ulong).wrapping_add(7 as
                                                                          std::os::raw::c_int
                                                                          as
                                                                          std::os::raw::c_ulong)
                >> 3 as std::os::raw::c_int;
        static_lenb =
            (*s).static_len.wrapping_add(3 as std::os::raw::c_int as
                                             std::os::raw::c_ulong).wrapping_add(7 as
                                                                             std::os::raw::c_int
                                                                             as
                                                                             std::os::raw::c_ulong)
                >> 3 as std::os::raw::c_int;
        if static_lenb <= opt_lenb { opt_lenb = static_lenb }
    } else {
        static_lenb =
            stored_len.wrapping_add(5 as std::os::raw::c_int as std::os::raw::c_ulong);
        opt_lenb = static_lenb
        /* force a stored block */
    }
    if stored_len.wrapping_add(4 as std::os::raw::c_int as std::os::raw::c_ulong) <= opt_lenb
           && !buf.is_null() {
        /* 4: two words for the lengths */
        /* The test buf != NULL is only necessary if LIT_BUFSIZE > WSIZE.
         * Otherwise we can't have processed more than WSIZE input bytes since
         * the last block flush, because compression would have been
         * successful. If LIT_BUFSIZE <= WSIZE, it is never too late to
         * transform a block into a stored block.
         */
        _tr_stored_block(s, buf, stored_len, last);
    } else if (*s).strategy == 4 as std::os::raw::c_int || static_lenb == opt_lenb {
        let mut len: std::os::raw::c_int = 3 as std::os::raw::c_int;
        if (*s).bi_valid > 16 as std::os::raw::c_int - len {
            let mut val: std::os::raw::c_int =
                ((1 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last;
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     (val as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
            let fresh38 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh38 as isize) =
                ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
            let fresh39 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh39 as isize) =
                ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
            (*s).bi_buf =
                (val as ush as std::os::raw::c_int >>
                     16 as std::os::raw::c_int - (*s).bi_valid) as ush;
            (*s).bi_valid += len - 16 as std::os::raw::c_int
        } else {
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     ((((1 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last) as ush
                          as std::os::raw::c_int) << (*s).bi_valid) as ush;
            (*s).bi_valid += len
        }
        compress_block(s, static_ltree.as_ptr(), static_dtree.as_ptr());
    } else {
        let mut len_0: std::os::raw::c_int = 3 as std::os::raw::c_int;
        if (*s).bi_valid > 16 as std::os::raw::c_int - len_0 {
            let mut val_0: std::os::raw::c_int =
                ((2 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last;
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     (val_0 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
            let fresh40 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh40 as isize) =
                ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
            let fresh41 = (*s).pending;
            (*s).pending = (*s).pending.wrapping_add(1);
            *(*s).pending_buf.offset(fresh41 as isize) =
                ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
            (*s).bi_buf =
                (val_0 as ush as std::os::raw::c_int >>
                     16 as std::os::raw::c_int - (*s).bi_valid) as ush;
            (*s).bi_valid += len_0 - 16 as std::os::raw::c_int
        } else {
            (*s).bi_buf =
                ((*s).bi_buf as std::os::raw::c_int |
                     ((((2 as std::os::raw::c_int) << 1 as std::os::raw::c_int) + last) as ush
                          as std::os::raw::c_int) << (*s).bi_valid) as ush;
            (*s).bi_valid += len_0
        }
        send_all_trees(s, (*s).l_desc.max_code + 1 as std::os::raw::c_int,
                       (*s).d_desc.max_code + 1 as std::os::raw::c_int,
                       max_blindex + 1 as std::os::raw::c_int);
        compress_block(s, (*s).dyn_ltree.as_mut_ptr() as *const ct_data,
                       (*s).dyn_dtree.as_mut_ptr() as *const ct_data);
    }
    /* The above check is made mod 2^32, for files larger than 512 MB
     * and uLong implemented on 32 bits.
     */
    init_block(&mut *s);
    if last != 0 { bi_windup(&mut *s); };
}
/* ===========================================================================
 * Save the match info and tally the frequency counts. Return true if
 * the current block must be flushed.
 */
#[no_mangle]
pub unsafe extern "C" fn _tr_tally(mut s: *mut deflate_state,
                                   mut dist: std::os::raw::c_uint,
                                   mut lc: std::os::raw::c_uint) -> std::os::raw::c_int 
 /* match length-MIN_MATCH or unmatched char (if dist==0) */
 {
    *(*s).d_buf.offset((*s).last_lit as isize) = dist as ush;
    let fresh42 = (*s).last_lit;
    (*s).last_lit = (*s).last_lit.wrapping_add(1);
    *(*s).l_buf.offset(fresh42 as isize) = lc as uch;
    if dist == 0 as std::os::raw::c_int as std::os::raw::c_uint {
        /* lc is the unmatched char */
        (*s).dyn_ltree[lc as usize].fc.freq =
            (*s).dyn_ltree[lc as usize].fc.freq.wrapping_add(1)
    } else {
        (*s).matches = (*s).matches.wrapping_add(1);
        /* Here, lc is the match length - MIN_MATCH */
        dist = dist.wrapping_sub(1); /* dist = match distance - 1 */
        (*s).dyn_ltree[(_length_code[lc as usize] as std::os::raw::c_int +
                            256 as std::os::raw::c_int + 1 as std::os::raw::c_int) as
                           usize].fc.freq =
            (*s).dyn_ltree[(_length_code[lc as usize] as std::os::raw::c_int +
                                256 as std::os::raw::c_int + 1 as std::os::raw::c_int) as
                               usize].fc.freq.wrapping_add(1);
        (*s).dyn_dtree[if dist < 256 as std::os::raw::c_int as std::os::raw::c_uint {
                           _dist_code[dist as usize] as std::os::raw::c_int
                       } else {
                           _dist_code[(256 as std::os::raw::c_int as
                                           std::os::raw::c_uint).wrapping_add(dist >>
                                                                          7 as
                                                                              std::os::raw::c_int)
                                          as usize] as std::os::raw::c_int
                       } as usize].fc.freq =
            (*s).dyn_dtree[if dist < 256 as std::os::raw::c_int as std::os::raw::c_uint {
                               _dist_code[dist as usize] as std::os::raw::c_int
                           } else {
                               _dist_code[(256 as std::os::raw::c_int as
                                               std::os::raw::c_uint).wrapping_add(dist
                                                                              >>
                                                                              7
                                                                                  as
                                                                                  std::os::raw::c_int)
                                              as usize] as std::os::raw::c_int
                           } as usize].fc.freq.wrapping_add(1)
    }
    return ((*s).last_lit ==
                (*s).lit_bufsize.wrapping_sub(1 as std::os::raw::c_int as
                                                  std::os::raw::c_uint)) as
               std::os::raw::c_int;
    /* We avoid equality with lit_bufsize because of wraparound at 64K
     * on 16 bit machines and because stored blocks are restricted to
     * 64K-1 bytes.
     */
}
/* ===========================================================================
 * Send the block data compressed using the given Huffman trees
 */
unsafe extern "C" fn compress_block(mut s: *mut deflate_state,
                                    mut ltree: *const ct_data,
                                    mut dtree: *const ct_data) 
 /* distance tree */
 {
    let mut dist: std::os::raw::c_uint = 0; /* distance of matched string */
    let mut lc: std::os::raw::c_int =
        0; /* match length or unmatched char (if dist == 0) */
    let mut lx: std::os::raw::c_uint =
        0 as std::os::raw::c_int as std::os::raw::c_uint; /* running index in l_buf */
    let mut code: std::os::raw::c_uint = 0; /* the code to send */
    let mut extra: std::os::raw::c_int = 0; /* number of extra bits to send */
    if (*s).last_lit != 0 as std::os::raw::c_int as std::os::raw::c_uint {
        loop  {
            let mut dist = unsafe { *(*s).d_buf.offset(lx as isize) } as u32; // literal or match pair ?
let fresh43 = lx;
lx = lx.wrapping_add(1);
lc = unsafe { *(*s).l_buf.offset(fresh43 as isize) } as i32;
if dist == 0 {
     let mut len: std::os::raw::c_int =
                    (*ltree.offset(lc as isize)).dl.len as std::os::raw::c_int;
                if (*s).bi_valid > 16 as std::os::raw::c_int - len {
                    let mut val: std::os::raw::c_int =
                        (*ltree.offset(lc as isize)).fc.code as std::os::raw::c_int;
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             (val as ush as std::os::raw::c_int) << (*s).bi_valid) as
                            ush;
                    let fresh44 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh44 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                            uch;
                    let fresh45 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh45 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as
                            uch;
                    (*s).bi_buf =
                        (val as ush as std::os::raw::c_int >>
                             16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                    (*s).bi_valid += len - 16 as std::os::raw::c_int
                } else {
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             ((*ltree.offset(lc as isize)).fc.code as
                                  std::os::raw::c_int) << (*s).bi_valid) as ush;
                    (*s).bi_valid += len
                }
 
} else {
    /* Here, lc is the match length - MIN_MATCH */
     code = _length_code[lc as usize] as std::os::raw::c_uint;
                let mut len_0: std::os::raw::c_int =
                    (*ltree.offset(code.wrapping_add(256 as std::os::raw::c_int as
                                                         std::os::raw::c_uint).wrapping_add(1
                                                                                        as
                                                                                        std::os::raw::c_int
                                                                                        as
                                                                                        std::os::raw::c_uint)
                                       as isize)).dl.len as std::os::raw::c_int;
                if (*s).bi_valid > 16 as std::os::raw::c_int - len_0 {
                    let mut val_0: std::os::raw::c_int =
                        (*ltree.offset(code.wrapping_add(256 as std::os::raw::c_int as
                                                             std::os::raw::c_uint).wrapping_add(1
                                                                                            as
                                                                                            std::os::raw::c_int
                                                                                            as
                                                                                            std::os::raw::c_uint)
                                           as isize)).fc.code as std::os::raw::c_int;
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             (val_0 as ush as std::os::raw::c_int) << (*s).bi_valid)
                            as ush;
                    let fresh46 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh46 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                            uch;
                    let fresh47 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh47 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as
                            uch;
                    (*s).bi_buf =
                        (val_0 as ush as std::os::raw::c_int >>
                             16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                    (*s).bi_valid += len_0 - 16 as std::os::raw::c_int
                } else {
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             ((*ltree.offset(code.wrapping_add(256 as
                                                                   std::os::raw::c_int
                                                                   as
                                                                   std::os::raw::c_uint).wrapping_add(1
                                                                                                  as
                                                                                                  std::os::raw::c_int
                                                                                                  as
                                                                                                  std::os::raw::c_uint)
                                                 as isize)).fc.code as
                                  std::os::raw::c_int) << (*s).bi_valid) as ush;
                    (*s).bi_valid += len_0
                }
                /* send the length code */
                extra = extra_lbits[code as usize];
                if extra != 0 as std::os::raw::c_int {
                    lc -= base_length[code as usize];
                    let mut len_1: std::os::raw::c_int = extra;
                    if (*s).bi_valid > 16 as std::os::raw::c_int - len_1 {
                        let mut val_1: std::os::raw::c_int = lc;
                        (*s).bi_buf =
                            ((*s).bi_buf as std::os::raw::c_int |
                                 (val_1 as ush as std::os::raw::c_int) <<
                                     (*s).bi_valid) as ush;
                        let fresh48 = (*s).pending;
                        (*s).pending = (*s).pending.wrapping_add(1);
                        *(*s).pending_buf.offset(fresh48 as isize) =
                            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int)
                                as uch;
                        let fresh49 = (*s).pending;
                        (*s).pending = (*s).pending.wrapping_add(1);
                        *(*s).pending_buf.offset(fresh49 as isize) =
                            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int)
                                as uch;
                        (*s).bi_buf =
                            (val_1 as ush as std::os::raw::c_int >>
                                 16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                        (*s).bi_valid += len_1 - 16 as std::os::raw::c_int
                    } else {
                        (*s).bi_buf =
                            ((*s).bi_buf as std::os::raw::c_int |
                                 (lc as ush as std::os::raw::c_int) << (*s).bi_valid)
                                as ush;
                        (*s).bi_valid += len_1
                    }
                    /* send the extra length bits */
                } /* dist is now the match distance - 1 */
                dist = dist.wrapping_sub(1);
                code =
                    if dist < 256 as std::os::raw::c_int as std::os::raw::c_uint {
                        _dist_code[dist as usize] as std::os::raw::c_int
                    } else {
                        _dist_code[(256 as std::os::raw::c_int as
                                        std::os::raw::c_uint).wrapping_add(dist >>
                                                                       7 as
                                                                           std::os::raw::c_int)
                                       as usize] as std::os::raw::c_int
                    } as std::os::raw::c_uint;
                let mut len_2: std::os::raw::c_int =
                    (*dtree.offset(code as isize)).dl.len as std::os::raw::c_int;
                if (*s).bi_valid > 16 as std::os::raw::c_int - len_2 {
                    let mut val_2: std::os::raw::c_int =
                        (*dtree.offset(code as isize)).fc.code as std::os::raw::c_int;
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             (val_2 as ush as std::os::raw::c_int) << (*s).bi_valid)
                            as ush;
                    let fresh50 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh50 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as
                            uch;
                    let fresh51 = (*s).pending;
                    (*s).pending = (*s).pending.wrapping_add(1);
                    *(*s).pending_buf.offset(fresh51 as isize) =
                        ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as
                            uch;
                    (*s).bi_buf =
                        (val_2 as ush as std::os::raw::c_int >>
                             16 as std::os::raw::c_int - (*s).bi_valid) as ush;
                    (*s).bi_valid += len_2 - 16 as std::os::raw::c_int
                } else {
                    (*s).bi_buf =
                        ((*s).bi_buf as std::os::raw::c_int |
                             ((*dtree.offset(code as isize)).fc.code as
                                  std::os::raw::c_int) << (*s).bi_valid) as ush;
                    (*s).bi_valid += len_2
                }
                /* send the distance code */
                extra = extra_dbits[code as usize];
 
     if extra != 0 {
    dist = dist.wrapping_sub(base_dist[code as usize] as u32);
    let len_3: i32 = extra;
    if unsafe { (*s).bi_valid } > 16 - len_3 {
        let val_3: i32 = dist as i32;
        unsafe {
            (*s).bi_buf |= (val_3 as u16) << (*s).bi_valid;
            let fresh52 = (*s).pending;
            (*s).pending += 1;
            *(*s).pending_buf.offset(fresh52 as isize) = ((*s).bi_buf & 0xff) as u8;
            let fresh53 = (*s).pending;
            (*s).pending += 1;
            *(*s).pending_buf.offset(fresh53 as isize) = ((*s).bi_buf >> 8) as u8;
            (*s).bi_buf = (val_3 >> (16 - (*s).bi_valid)) as u16;
            (*s).bi_valid += len_3 - 16;
        }
    } else {
        unsafe {
            (*s).bi_buf |= (dist as u16) << (*s).bi_valid;
            (*s).bi_valid += len_3;
        }
    }
    /* send the extra distance bits */
}

 
}
if !(lx < unsafe { (*s).last_lit }) { break; }

        }
    }
    let mut len_4: std::os::raw::c_int =
        (*ltree.offset(256 as std::os::raw::c_int as isize)).dl.len as std::os::raw::c_int;
    if (*s).bi_valid > 16 as std::os::raw::c_int - len_4 {
        let mut val_4: std::os::raw::c_int =
            (*ltree.offset(256 as std::os::raw::c_int as isize)).fc.code as
                std::os::raw::c_int;
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 (val_4 as ush as std::os::raw::c_int) << (*s).bi_valid) as ush;
        let fresh54 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh54 as isize) =
            ((*s).bi_buf as std::os::raw::c_int & 0xff as std::os::raw::c_int) as uch;
        let fresh55 = (*s).pending;
        (*s).pending = (*s).pending.wrapping_add(1);
        *(*s).pending_buf.offset(fresh55 as isize) =
            ((*s).bi_buf as std::os::raw::c_int >> 8 as std::os::raw::c_int) as uch;
        (*s).bi_buf =
            (val_4 as ush as std::os::raw::c_int >> 16 as std::os::raw::c_int - (*s).bi_valid)
                as ush;
        (*s).bi_valid += len_4 - 16 as std::os::raw::c_int
    } else {
        (*s).bi_buf =
            ((*s).bi_buf as std::os::raw::c_int |
                 ((*ltree.offset(256 as std::os::raw::c_int as isize)).fc.code as
                      std::os::raw::c_int) << (*s).bi_valid) as ush;
        (*s).bi_valid += len_4
    };
}
/* ===========================================================================
 * Check if the data type is TEXT or BINARY, using the following algorithm:
 * - TEXT if the two conditions below are satisfied:
 *    a) There are no non-portable control characters belonging to the
 *       "black list" (0..6, 14..25, 28..31).
 *    b) There is at least one printable character belonging to the
 *       "white list" (9 {TAB}, 10 {LF}, 13 {CR}, 32..255).
 * - BINARY otherwise.
 * - The following partially-portable control characters form a
 *   "gray list" that is ignored in this detection algorithm:
 *   (7 {BEL}, 8 {BS}, 11 {VT}, 12 {FF}, 26 {SUB}, 27 {ESC}).
 * IN assertion: the fields Freq of dyn_ltree are set.
 */
fn detect_data_type(s: &mut crate::src::zlib::deflate::deflate_state) -> i32 {
    let mut black_mask: u64 = 0xf3ffc07f;
    let mut n: i32 = 0;

    // Check for non-textual ("black-listed") bytes.
    while n <= 31 {
        if (black_mask & 1 != 0) && unsafe { s.dyn_ltree[n as usize].fc.freq } != 0 {
            return 0;
        }
        n += 1;
        black_mask >>= 1;
    }

    // Check for textual ("white-listed") bytes.
    if unsafe { s.dyn_ltree[9].fc.freq } != 0 ||
       unsafe { s.dyn_ltree[10].fc.freq } != 0 ||
       unsafe { s.dyn_ltree[13].fc.freq } != 0 {
        return 1;
    }

    n = 32;
    while n < 256 {
        if unsafe { s.dyn_ltree[n as usize].fc.freq } != 0 {
            return 1;
        }
        n += 1;
    }

    // There are no "black-listed" or "white-listed" bytes:
    // this stream either is empty or has tolerated ("gray-listed") bytes only.
    return 0;
}

/* ===========================================================================
 * Reverse the first len bits of a code, using straightforward code (a faster
 * method would use a table)
 * IN assertion: 1 <= len <= 15
 */
 extern "C" fn bi_reverse(mut code: std::os::raw::c_uint, mut len: std::os::raw::c_int)
 -> std::os::raw::c_uint 
 /* its bit length */
 {
    let mut res: std::os::raw::c_uint = 0 as std::os::raw::c_int as std::os::raw::c_uint;
    loop  {
        res |= code & 1 as std::os::raw::c_int as std::os::raw::c_uint;
        code >>= 1 as std::os::raw::c_int;
        res <<= 1 as std::os::raw::c_int;
        len -= 1;
        if !(len > 0 as std::os::raw::c_int) { break ; }
    }
    return res >> 1 as std::os::raw::c_int;
}
/* ===========================================================================
 * Flush the bit buffer, keeping at most 7 bits in it.
 */
fn bi_flush(s: &mut deflate_state) {
    if s.bi_valid == 16 {
        let fresh56 = s.pending;
        s.pending += 1;
        unsafe {
            *s.pending_buf.offset(fresh56 as isize) = (s.bi_buf & 0xff) as uch;
        }
        let fresh57 = s.pending;
        s.pending += 1;
        unsafe {
            *s.pending_buf.offset(fresh57 as isize) = (s.bi_buf >> 8) as uch;
        }
        s.bi_buf = 0;
        s.bi_valid = 0;
    } else if s.bi_valid >= 8 {
        let fresh58 = s.pending;
        s.pending += 1;
        unsafe {
            *s.pending_buf.offset(fresh58 as isize) = s.bi_buf as Byte;
        }
        s.bi_buf = (s.bi_buf >> 8) as ush;
        s.bi_valid -= 8;
    }
}

/* ===========================================================================
 * Flush the bit buffer and align the output on a byte boundary
 */
fn bi_windup(s: &mut deflate_state) {
    if s.bi_valid > 8 {
        s.pending += 1;
        let index = (s.pending - 1) as usize;
        unsafe {
            *s.pending_buf.offset(index as isize) = (s.bi_buf & 0xff) as uch;
        }
        s.pending += 1;
        let index = (s.pending - 1) as usize;
        unsafe {
            *s.pending_buf.offset(index as isize) = (s.bi_buf >> 8) as uch;
        }
    } else if s.bi_valid > 0 {
        s.pending += 1;
        let index = (s.pending - 1) as usize;
        unsafe {
            *s.pending_buf.offset(index as isize) = s.bi_buf as Byte;
        }
    }
    s.bi_buf = 0;
    s.bi_valid = 0;
}

