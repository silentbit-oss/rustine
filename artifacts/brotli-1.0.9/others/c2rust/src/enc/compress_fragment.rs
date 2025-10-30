use ::libc;
extern "C" {
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
    fn log2(_: libc::c_double) -> libc::c_double;
    static kBrotliLog2Table: [libc::c_double; 256];
    fn BrotliCreateHuffmanTree(
        data: *const uint32_t,
        length: size_t,
        tree_limit: libc::c_int,
        tree: *mut HuffmanTree,
        depth: *mut uint8_t,
    );
    fn BrotliConvertBitDepthsToSymbols(
        depth: *const uint8_t,
        len: size_t,
        bits: *mut uint16_t,
    );
    fn BrotliStoreHuffmanTree(
        depths: *const uint8_t,
        num: size_t,
        tree: *mut HuffmanTree,
        storage_ix: *mut size_t,
        storage: *mut uint8_t,
    );
    fn BrotliBuildAndStoreHuffmanTreeFast(
        m: *mut MemoryManager,
        histogram: *const uint32_t,
        histogram_total: size_t,
        max_bits: size_t,
        depth: *mut uint8_t,
        bits: *mut uint16_t,
        storage_ix: *mut size_t,
        storage: *mut uint8_t,
    );
}
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
pub type __int16_t = libc::c_short;
pub type __uint16_t = libc::c_ushort;
pub type __uint32_t = libc::c_uint;
pub type __uint64_t = libc::c_ulong;
pub type int16_t = __int16_t;
pub type uint8_t = __uint8_t;
pub type uint16_t = __uint16_t;
pub type uint32_t = __uint32_t;
pub type uint64_t = __uint64_t;
pub type brotli_alloc_func = Option::<
    unsafe extern "C" fn(*mut libc::c_void, size_t) -> *mut libc::c_void,
>;
pub type brotli_free_func = Option::<
    unsafe extern "C" fn(*mut libc::c_void, *mut libc::c_void) -> (),
>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct MemoryManager {
    pub alloc_func: brotli_alloc_func,
    pub free_func: brotli_free_func,
    pub opaque: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HuffmanTree {
    pub total_count_: uint32_t,
    pub index_left_: int16_t,
    pub index_right_or_value_: int16_t,
}
#[inline(always)]
unsafe extern "C" fn BrotliUnalignedRead32(mut p: *const libc::c_void) -> uint32_t {
    return *(p as *const uint32_t);
}
#[inline(always)]
unsafe extern "C" fn BrotliUnalignedRead64(mut p: *const libc::c_void) -> uint64_t {
    return *(p as *const uint64_t);
}
#[inline(always)]
unsafe extern "C" fn BrotliUnalignedWrite64(mut p: *mut libc::c_void, mut v: uint64_t) {
    *(p as *mut uint64_t) = v;
}
#[inline(always)]
unsafe extern "C" fn brotli_min_size_t(mut a: size_t, mut b: size_t) -> size_t {
    return if a < b { a } else { b };
}
#[inline(always)]
unsafe extern "C" fn brotli_min_uint32_t(mut a: uint32_t, mut b: uint32_t) -> uint32_t {
    return if a < b { a } else { b };
}
#[inline(always)]
unsafe extern "C" fn Log2FloorNonZero(mut n: size_t) -> uint32_t {
    return 31 as libc::c_uint ^ (n as uint32_t).leading_zeros() as i32 as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn FastLog2(mut v: size_t) -> libc::c_double {
    if v < 256 as libc::c_int as size_t {
        return kBrotliLog2Table[v as usize];
    }
    return log2(v as libc::c_double);
}
#[inline(always)]
unsafe extern "C" fn FindMatchLengthWithLimit(
    mut s1: *const uint8_t,
    mut s2: *const uint8_t,
    mut limit: size_t,
) -> size_t {
    let mut matched: size_t = 0 as libc::c_int as size_t;
    let mut limit2: size_t = (limit >> 3 as libc::c_int)
        .wrapping_add(1 as libc::c_int as size_t);
    loop {
        limit2 = limit2.wrapping_sub(1);
        if !((limit2 != 0) as libc::c_int as libc::c_long != 0) {
            break;
        }
        if (BrotliUnalignedRead64(s2 as *const libc::c_void)
            == BrotliUnalignedRead64(s1.offset(matched as isize) as *const libc::c_void))
            as libc::c_int as libc::c_long != 0
        {
            s2 = s2.offset(8 as libc::c_int as isize);
            matched = matched.wrapping_add(8 as libc::c_int as size_t);
        } else {
            let mut x: uint64_t = BrotliUnalignedRead64(s2 as *const libc::c_void)
                ^ BrotliUnalignedRead64(
                    s1.offset(matched as isize) as *const libc::c_void,
                );
            let mut matching_bits: size_t = (x as libc::c_ulonglong).trailing_zeros()
                as i32 as size_t;
            matched = matched.wrapping_add(matching_bits >> 3 as libc::c_int);
            return matched;
        }
    }
    limit = (limit & 7 as libc::c_int as size_t)
        .wrapping_add(1 as libc::c_int as size_t);
    loop {
        limit = limit.wrapping_sub(1);
        if !(limit != 0) {
            break;
        }
        if (*s1.offset(matched as isize) as libc::c_int == *s2 as libc::c_int)
            as libc::c_int as libc::c_long != 0
        {
            s2 = s2.offset(1);
            s2;
            matched = matched.wrapping_add(1);
            matched;
        } else {
            return matched
        }
    }
    return matched;
}
#[inline(always)]
unsafe extern "C" fn BrotliWriteBits(
    mut n_bits: size_t,
    mut bits: uint64_t,
    mut pos: *mut size_t,
    mut array: *mut uint8_t,
) {
    let mut p: *mut uint8_t = &mut *array.offset((*pos >> 3 as libc::c_int) as isize)
        as *mut uint8_t;
    let mut v: uint64_t = *p as uint64_t;
    v |= bits << (*pos & 7 as libc::c_int as size_t);
    BrotliUnalignedWrite64(p as *mut libc::c_void, v);
    *pos = (*pos).wrapping_add(n_bits);
}
static mut kHashMul32: uint32_t = 0x1e35a7bd as libc::c_int as uint32_t;
#[inline(always)]
unsafe extern "C" fn Hash(mut p: *const uint8_t, mut shift: size_t) -> uint32_t {
    let h: uint64_t = (BrotliUnalignedRead64(p as *const libc::c_void)
        << 24 as libc::c_int) * kHashMul32 as uint64_t;
    return (h >> shift) as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn HashBytesAtOffset(
    mut v: uint64_t,
    mut offset: libc::c_int,
    mut shift: size_t,
) -> uint32_t {
    let h: uint64_t = (v >> 8 as libc::c_int * offset << 24 as libc::c_int)
        * kHashMul32 as uint64_t;
    return (h >> shift) as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn IsMatch(
    mut p1: *const uint8_t,
    mut p2: *const uint8_t,
) -> libc::c_int {
    return if BrotliUnalignedRead32(p1 as *const libc::c_void)
        == BrotliUnalignedRead32(p2 as *const libc::c_void)
        && *p1.offset(4 as libc::c_int as isize) as libc::c_int
            == *p2.offset(4 as libc::c_int as isize) as libc::c_int
    {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    };
}
unsafe extern "C" fn BuildAndStoreLiteralPrefixCode(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    input_size: size_t,
    mut depths: *mut uint8_t,
    mut bits: *mut uint16_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) -> size_t {
    let mut histogram: [uint32_t; 256] = [
        0 as libc::c_int as uint32_t,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    ];
    let mut histogram_total: size_t = 0;
    let mut i: size_t = 0;
    if input_size < ((1 as libc::c_int) << 15 as libc::c_int) as size_t {
        i = 0 as libc::c_int as size_t;
        while i < input_size {
            histogram[*input.offset(i as isize)
                as usize] = (histogram[*input.offset(i as isize) as usize])
                .wrapping_add(1);
            histogram[*input.offset(i as isize) as usize];
            i = i.wrapping_add(1);
            i;
        }
        histogram_total = input_size;
        i = 0 as libc::c_int as size_t;
        while i < 256 as libc::c_int as size_t {
            let adjust: uint32_t = 2 as libc::c_int as uint32_t
                * brotli_min_uint32_t(histogram[i as usize], 11 as libc::c_uint);
            histogram[i as usize] = (histogram[i as usize]).wrapping_add(adjust);
            histogram_total = histogram_total.wrapping_add(adjust as size_t);
            i = i.wrapping_add(1);
            i;
        }
    } else {
        static mut kSampleRate: size_t = 29 as libc::c_int as size_t;
        i = 0 as libc::c_int as size_t;
        while i < input_size {
            histogram[*input.offset(i as isize)
                as usize] = (histogram[*input.offset(i as isize) as usize])
                .wrapping_add(1);
            histogram[*input.offset(i as isize) as usize];
            i = i.wrapping_add(kSampleRate);
        }
        histogram_total = input_size
            .wrapping_add(kSampleRate)
            .wrapping_sub(1 as libc::c_int as size_t) / kSampleRate;
        i = 0 as libc::c_int as size_t;
        while i < 256 as libc::c_int as size_t {
            let adjust_0: uint32_t = (1 as libc::c_int as uint32_t)
                .wrapping_add(
                    2 as libc::c_int as uint32_t
                        * brotli_min_uint32_t(histogram[i as usize], 11 as libc::c_uint),
                );
            histogram[i as usize] = (histogram[i as usize]).wrapping_add(adjust_0);
            histogram_total = histogram_total.wrapping_add(adjust_0 as size_t);
            i = i.wrapping_add(1);
            i;
        }
    }
    BrotliBuildAndStoreHuffmanTreeFast(
        m,
        histogram.as_mut_ptr(),
        histogram_total,
        8 as libc::c_int as size_t,
        depths,
        bits,
        storage_ix,
        storage,
    );
    if 0 as libc::c_int != 0 {
        return 0 as libc::c_int as size_t;
    }
    let mut literal_ratio: size_t = 0 as libc::c_int as size_t;
    i = 0 as libc::c_int as size_t;
    while i < 256 as libc::c_int as size_t {
        if histogram[i as usize] != 0 {
            literal_ratio = literal_ratio
                .wrapping_add(
                    (histogram[i as usize] * *depths.offset(i as isize) as uint32_t)
                        as size_t,
                );
        }
        i = i.wrapping_add(1);
        i;
    }
    return literal_ratio * 125 as libc::c_int as size_t / histogram_total;
}
unsafe extern "C" fn BuildAndStoreCommandPrefixCode(
    mut histogram: *const uint32_t,
    mut depth: *mut uint8_t,
    mut bits: *mut uint16_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let mut tree: [HuffmanTree; 129] = [HuffmanTree {
        total_count_: 0,
        index_left_: 0,
        index_right_or_value_: 0,
    }; 129];
    let mut cmd_depth: [uint8_t; 704] = [
        0 as libc::c_int as uint8_t,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    ];
    let mut cmd_bits: [uint16_t; 64] = [0; 64];
    BrotliCreateHuffmanTree(
        histogram,
        64 as libc::c_int as size_t,
        15 as libc::c_int,
        tree.as_mut_ptr(),
        depth,
    );
    BrotliCreateHuffmanTree(
        &*histogram.offset(64 as libc::c_int as isize),
        64 as libc::c_int as size_t,
        14 as libc::c_int,
        tree.as_mut_ptr(),
        &mut *depth.offset(64 as libc::c_int as isize),
    );
    memcpy(
        cmd_depth.as_mut_ptr() as *mut libc::c_void,
        depth as *const libc::c_void,
        24 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(24 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(40 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(32 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(24 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(40 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(48 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(48 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(32 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(56 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(56 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    BrotliConvertBitDepthsToSymbols(
        cmd_depth.as_mut_ptr(),
        64 as libc::c_int as size_t,
        cmd_bits.as_mut_ptr(),
    );
    memcpy(
        bits as *mut libc::c_void,
        cmd_bits.as_mut_ptr() as *const libc::c_void,
        48 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        bits.offset(24 as libc::c_int as isize) as *mut libc::c_void,
        cmd_bits.as_mut_ptr().offset(32 as libc::c_int as isize) as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        bits.offset(32 as libc::c_int as isize) as *mut libc::c_void,
        cmd_bits.as_mut_ptr().offset(48 as libc::c_int as isize) as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        bits.offset(40 as libc::c_int as isize) as *mut libc::c_void,
        cmd_bits.as_mut_ptr().offset(24 as libc::c_int as isize) as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        bits.offset(48 as libc::c_int as isize) as *mut libc::c_void,
        cmd_bits.as_mut_ptr().offset(40 as libc::c_int as isize) as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        bits.offset(56 as libc::c_int as isize) as *mut libc::c_void,
        cmd_bits.as_mut_ptr().offset(56 as libc::c_int as isize) as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    BrotliConvertBitDepthsToSymbols(
        &mut *depth.offset(64 as libc::c_int as isize),
        64 as libc::c_int as size_t,
        &mut *bits.offset(64 as libc::c_int as isize),
    );
    let mut i: size_t = 0;
    memset(
        cmd_depth.as_mut_ptr() as *mut libc::c_void,
        0 as libc::c_int,
        64 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr() as *mut libc::c_void,
        depth as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(64 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(8 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(128 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(16 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(192 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(24 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        cmd_depth.as_mut_ptr().offset(384 as libc::c_int as isize) as *mut libc::c_void,
        depth.offset(32 as libc::c_int as isize) as *const libc::c_void,
        8 as libc::c_int as libc::c_ulong,
    );
    i = 0 as libc::c_int as size_t;
    while i < 8 as libc::c_int as size_t {
        cmd_depth[(128 as libc::c_int as size_t)
            .wrapping_add(8 as libc::c_int as size_t * i)
            as usize] = *depth
            .offset((40 as libc::c_int as size_t).wrapping_add(i) as isize);
        cmd_depth[(256 as libc::c_int as size_t)
            .wrapping_add(8 as libc::c_int as size_t * i)
            as usize] = *depth
            .offset((48 as libc::c_int as size_t).wrapping_add(i) as isize);
        cmd_depth[(448 as libc::c_int as size_t)
            .wrapping_add(8 as libc::c_int as size_t * i)
            as usize] = *depth
            .offset((56 as libc::c_int as size_t).wrapping_add(i) as isize);
        i = i.wrapping_add(1);
        i;
    }
    BrotliStoreHuffmanTree(
        cmd_depth.as_mut_ptr(),
        704 as libc::c_int as size_t,
        tree.as_mut_ptr(),
        storage_ix,
        storage,
    );
    BrotliStoreHuffmanTree(
        &mut *depth.offset(64 as libc::c_int as isize),
        64 as libc::c_int as size_t,
        tree.as_mut_ptr(),
        storage_ix,
        storage,
    );
}
#[inline(always)]
unsafe extern "C" fn EmitInsertLen(
    mut insertlen: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut histo: *mut uint32_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    if insertlen < 6 as libc::c_int as size_t {
        let code: size_t = insertlen.wrapping_add(40 as libc::c_int as size_t);
        BrotliWriteBits(
            *depth.offset(code as isize) as size_t,
            *bits.offset(code as isize) as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh0 = *histo.offset(code as isize);
        *fresh0 = (*fresh0).wrapping_add(1);
        *fresh0;
    } else if insertlen < 130 as libc::c_int as size_t {
        let tail: size_t = insertlen.wrapping_sub(2 as libc::c_int as size_t);
        let nbits: uint32_t = (Log2FloorNonZero(tail)).wrapping_sub(1 as libc::c_uint);
        let prefix: size_t = tail >> nbits;
        let inscode: size_t = ((nbits << 1 as libc::c_int) as size_t)
            .wrapping_add(prefix)
            .wrapping_add(42 as libc::c_int as size_t);
        BrotliWriteBits(
            *depth.offset(inscode as isize) as size_t,
            *bits.offset(inscode as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits as size_t,
            tail.wrapping_sub(prefix << nbits),
            storage_ix,
            storage,
        );
        let ref mut fresh1 = *histo.offset(inscode as isize);
        *fresh1 = (*fresh1).wrapping_add(1);
        *fresh1;
    } else if insertlen < 2114 as libc::c_int as size_t {
        let tail_0: size_t = insertlen.wrapping_sub(66 as libc::c_int as size_t);
        let nbits_0: uint32_t = Log2FloorNonZero(tail_0);
        let code_0: size_t = nbits_0.wrapping_add(50 as libc::c_int as uint32_t)
            as size_t;
        BrotliWriteBits(
            *depth.offset(code_0 as isize) as size_t,
            *bits.offset(code_0 as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits_0 as size_t,
            tail_0.wrapping_sub((1 as libc::c_int as size_t) << nbits_0),
            storage_ix,
            storage,
        );
        let ref mut fresh2 = *histo.offset(code_0 as isize);
        *fresh2 = (*fresh2).wrapping_add(1);
        *fresh2;
    } else {
        BrotliWriteBits(
            *depth.offset(61 as libc::c_int as isize) as size_t,
            *bits.offset(61 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            12 as libc::c_int as size_t,
            insertlen.wrapping_sub(2114 as libc::c_int as size_t),
            storage_ix,
            storage,
        );
        let ref mut fresh3 = *histo.offset(61 as libc::c_int as isize);
        *fresh3 = (*fresh3).wrapping_add(1);
        *fresh3;
    };
}
#[inline(always)]
unsafe extern "C" fn EmitLongInsertLen(
    mut insertlen: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut histo: *mut uint32_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    if insertlen < 22594 as libc::c_int as size_t {
        BrotliWriteBits(
            *depth.offset(62 as libc::c_int as isize) as size_t,
            *bits.offset(62 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            14 as libc::c_int as size_t,
            insertlen.wrapping_sub(6210 as libc::c_int as size_t),
            storage_ix,
            storage,
        );
        let ref mut fresh4 = *histo.offset(62 as libc::c_int as isize);
        *fresh4 = (*fresh4).wrapping_add(1);
        *fresh4;
    } else {
        BrotliWriteBits(
            *depth.offset(63 as libc::c_int as isize) as size_t,
            *bits.offset(63 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            24 as libc::c_int as size_t,
            insertlen.wrapping_sub(22594 as libc::c_int as size_t),
            storage_ix,
            storage,
        );
        let ref mut fresh5 = *histo.offset(63 as libc::c_int as isize);
        *fresh5 = (*fresh5).wrapping_add(1);
        *fresh5;
    };
}
#[inline(always)]
unsafe extern "C" fn EmitCopyLen(
    mut copylen: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut histo: *mut uint32_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    if copylen < 10 as libc::c_int as size_t {
        BrotliWriteBits(
            *depth.offset(copylen.wrapping_add(14 as libc::c_int as size_t) as isize)
                as size_t,
            *bits.offset(copylen.wrapping_add(14 as libc::c_int as size_t) as isize)
                as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh6 = *histo
            .offset(copylen.wrapping_add(14 as libc::c_int as size_t) as isize);
        *fresh6 = (*fresh6).wrapping_add(1);
        *fresh6;
    } else if copylen < 134 as libc::c_int as size_t {
        let tail: size_t = copylen.wrapping_sub(6 as libc::c_int as size_t);
        let nbits: uint32_t = (Log2FloorNonZero(tail)).wrapping_sub(1 as libc::c_uint);
        let prefix: size_t = tail >> nbits;
        let code: size_t = ((nbits << 1 as libc::c_int) as size_t)
            .wrapping_add(prefix)
            .wrapping_add(20 as libc::c_int as size_t);
        BrotliWriteBits(
            *depth.offset(code as isize) as size_t,
            *bits.offset(code as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits as size_t,
            tail.wrapping_sub(prefix << nbits),
            storage_ix,
            storage,
        );
        let ref mut fresh7 = *histo.offset(code as isize);
        *fresh7 = (*fresh7).wrapping_add(1);
        *fresh7;
    } else if copylen < 2118 as libc::c_int as size_t {
        let tail_0: size_t = copylen.wrapping_sub(70 as libc::c_int as size_t);
        let nbits_0: uint32_t = Log2FloorNonZero(tail_0);
        let code_0: size_t = nbits_0.wrapping_add(28 as libc::c_int as uint32_t)
            as size_t;
        BrotliWriteBits(
            *depth.offset(code_0 as isize) as size_t,
            *bits.offset(code_0 as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits_0 as size_t,
            tail_0.wrapping_sub((1 as libc::c_int as size_t) << nbits_0),
            storage_ix,
            storage,
        );
        let ref mut fresh8 = *histo.offset(code_0 as isize);
        *fresh8 = (*fresh8).wrapping_add(1);
        *fresh8;
    } else {
        BrotliWriteBits(
            *depth.offset(39 as libc::c_int as isize) as size_t,
            *bits.offset(39 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            24 as libc::c_int as size_t,
            copylen.wrapping_sub(2118 as libc::c_int as size_t),
            storage_ix,
            storage,
        );
        let ref mut fresh9 = *histo.offset(39 as libc::c_int as isize);
        *fresh9 = (*fresh9).wrapping_add(1);
        *fresh9;
    };
}
#[inline(always)]
unsafe extern "C" fn EmitCopyLenLastDistance(
    mut copylen: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut histo: *mut uint32_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    if copylen < 12 as libc::c_int as size_t {
        BrotliWriteBits(
            *depth.offset(copylen.wrapping_sub(4 as libc::c_int as size_t) as isize)
                as size_t,
            *bits.offset(copylen.wrapping_sub(4 as libc::c_int as size_t) as isize)
                as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh10 = *histo
            .offset(copylen.wrapping_sub(4 as libc::c_int as size_t) as isize);
        *fresh10 = (*fresh10).wrapping_add(1);
        *fresh10;
    } else if copylen < 72 as libc::c_int as size_t {
        let tail: size_t = copylen.wrapping_sub(8 as libc::c_int as size_t);
        let nbits: uint32_t = (Log2FloorNonZero(tail))
            .wrapping_sub(1 as libc::c_int as uint32_t);
        let prefix: size_t = tail >> nbits;
        let code: size_t = ((nbits << 1 as libc::c_int) as size_t)
            .wrapping_add(prefix)
            .wrapping_add(4 as libc::c_int as size_t);
        BrotliWriteBits(
            *depth.offset(code as isize) as size_t,
            *bits.offset(code as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits as size_t,
            tail.wrapping_sub(prefix << nbits),
            storage_ix,
            storage,
        );
        let ref mut fresh11 = *histo.offset(code as isize);
        *fresh11 = (*fresh11).wrapping_add(1);
        *fresh11;
    } else if copylen < 136 as libc::c_int as size_t {
        let tail_0: size_t = copylen.wrapping_sub(8 as libc::c_int as size_t);
        let code_0: size_t = (tail_0 >> 5 as libc::c_int)
            .wrapping_add(30 as libc::c_int as size_t);
        BrotliWriteBits(
            *depth.offset(code_0 as isize) as size_t,
            *bits.offset(code_0 as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            5 as libc::c_int as size_t,
            tail_0 & 31 as libc::c_int as size_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            *depth.offset(64 as libc::c_int as isize) as size_t,
            *bits.offset(64 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh12 = *histo.offset(code_0 as isize);
        *fresh12 = (*fresh12).wrapping_add(1);
        *fresh12;
        let ref mut fresh13 = *histo.offset(64 as libc::c_int as isize);
        *fresh13 = (*fresh13).wrapping_add(1);
        *fresh13;
    } else if copylen < 2120 as libc::c_int as size_t {
        let tail_1: size_t = copylen.wrapping_sub(72 as libc::c_int as size_t);
        let nbits_0: uint32_t = Log2FloorNonZero(tail_1);
        let code_1: size_t = nbits_0.wrapping_add(28 as libc::c_int as uint32_t)
            as size_t;
        BrotliWriteBits(
            *depth.offset(code_1 as isize) as size_t,
            *bits.offset(code_1 as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            nbits_0 as size_t,
            tail_1.wrapping_sub((1 as libc::c_int as size_t) << nbits_0),
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            *depth.offset(64 as libc::c_int as isize) as size_t,
            *bits.offset(64 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh14 = *histo.offset(code_1 as isize);
        *fresh14 = (*fresh14).wrapping_add(1);
        *fresh14;
        let ref mut fresh15 = *histo.offset(64 as libc::c_int as isize);
        *fresh15 = (*fresh15).wrapping_add(1);
        *fresh15;
    } else {
        BrotliWriteBits(
            *depth.offset(39 as libc::c_int as isize) as size_t,
            *bits.offset(39 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            24 as libc::c_int as size_t,
            copylen.wrapping_sub(2120 as libc::c_int as size_t),
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            *depth.offset(64 as libc::c_int as isize) as size_t,
            *bits.offset(64 as libc::c_int as isize) as uint64_t,
            storage_ix,
            storage,
        );
        let ref mut fresh16 = *histo.offset(39 as libc::c_int as isize);
        *fresh16 = (*fresh16).wrapping_add(1);
        *fresh16;
        let ref mut fresh17 = *histo.offset(64 as libc::c_int as isize);
        *fresh17 = (*fresh17).wrapping_add(1);
        *fresh17;
    };
}
#[inline(always)]
unsafe extern "C" fn EmitDistance(
    mut distance: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut histo: *mut uint32_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let d: size_t = distance.wrapping_add(3 as libc::c_int as size_t);
    let nbits: uint32_t = (Log2FloorNonZero(d)).wrapping_sub(1 as libc::c_uint);
    let prefix: size_t = d >> nbits & 1 as libc::c_int as size_t;
    let offset: size_t = (2 as libc::c_int as size_t).wrapping_add(prefix) << nbits;
    let distcode: size_t = ((2 as libc::c_int as uint32_t
        * nbits.wrapping_sub(1 as libc::c_int as uint32_t)) as size_t)
        .wrapping_add(prefix)
        .wrapping_add(80 as libc::c_int as size_t);
    BrotliWriteBits(
        *depth.offset(distcode as isize) as size_t,
        *bits.offset(distcode as isize) as uint64_t,
        storage_ix,
        storage,
    );
    BrotliWriteBits(nbits as size_t, d.wrapping_sub(offset), storage_ix, storage);
    let ref mut fresh18 = *histo.offset(distcode as isize);
    *fresh18 = (*fresh18).wrapping_add(1);
    *fresh18;
}
#[inline(always)]
unsafe extern "C" fn EmitLiterals(
    mut input: *const uint8_t,
    len: size_t,
    mut depth: *const uint8_t,
    mut bits: *const uint16_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let mut j: size_t = 0;
    j = 0 as libc::c_int as size_t;
    while j < len {
        let lit: uint8_t = *input.offset(j as isize);
        BrotliWriteBits(
            *depth.offset(lit as isize) as size_t,
            *bits.offset(lit as isize) as uint64_t,
            storage_ix,
            storage,
        );
        j = j.wrapping_add(1);
        j;
    }
}
unsafe extern "C" fn BrotliStoreMetaBlockHeader(
    mut len: size_t,
    mut is_uncompressed: libc::c_int,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let mut nibbles: size_t = 6 as libc::c_int as size_t;
    BrotliWriteBits(
        1 as libc::c_int as size_t,
        0 as libc::c_int as uint64_t,
        storage_ix,
        storage,
    );
    if len <= ((1 as libc::c_uint) << 16 as libc::c_int) as size_t {
        nibbles = 4 as libc::c_int as size_t;
    } else if len <= ((1 as libc::c_uint) << 20 as libc::c_int) as size_t {
        nibbles = 5 as libc::c_int as size_t;
    }
    BrotliWriteBits(
        2 as libc::c_int as size_t,
        nibbles.wrapping_sub(4 as libc::c_int as size_t),
        storage_ix,
        storage,
    );
    BrotliWriteBits(
        nibbles * 4 as libc::c_int as size_t,
        len.wrapping_sub(1 as libc::c_int as size_t),
        storage_ix,
        storage,
    );
    BrotliWriteBits(
        1 as libc::c_int as size_t,
        is_uncompressed as uint64_t,
        storage_ix,
        storage,
    );
}
unsafe extern "C" fn UpdateBits(
    mut n_bits: size_t,
    mut bits: uint32_t,
    mut pos: size_t,
    mut array: *mut uint8_t,
) {
    while n_bits > 0 as libc::c_int as size_t {
        let mut byte_pos: size_t = pos >> 3 as libc::c_int;
        let mut n_unchanged_bits: size_t = pos & 7 as libc::c_int as size_t;
        let mut n_changed_bits: size_t = brotli_min_size_t(
            n_bits,
            (8 as libc::c_int as size_t).wrapping_sub(n_unchanged_bits),
        );
        let mut total_bits: size_t = n_unchanged_bits.wrapping_add(n_changed_bits);
        let mut mask: uint32_t = !((1 as libc::c_uint) << total_bits)
            .wrapping_sub(1 as libc::c_uint)
            | ((1 as libc::c_uint) << n_unchanged_bits).wrapping_sub(1 as libc::c_uint);
        let mut unchanged_bits: uint32_t = *array.offset(byte_pos as isize) as uint32_t
            & mask;
        let mut changed_bits: uint32_t = bits
            & ((1 as libc::c_uint) << n_changed_bits).wrapping_sub(1 as libc::c_uint);
        *array
            .offset(
                byte_pos as isize,
            ) = (changed_bits << n_unchanged_bits | unchanged_bits) as uint8_t;
        n_bits = n_bits.wrapping_sub(n_changed_bits);
        bits >>= n_changed_bits;
        pos = pos.wrapping_add(n_changed_bits);
    }
}
unsafe extern "C" fn RewindBitPosition(
    new_storage_ix: size_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let bitpos: size_t = new_storage_ix & 7 as libc::c_int as size_t;
    let mask: size_t = ((1 as libc::c_uint) << bitpos)
        .wrapping_sub(1 as libc::c_int as libc::c_uint) as size_t;
    let ref mut fresh19 = *storage.offset((new_storage_ix >> 3 as libc::c_int) as isize);
    *fresh19 = (*fresh19 as libc::c_int & mask as uint8_t as libc::c_int) as uint8_t;
    *storage_ix = new_storage_ix;
}
unsafe extern "C" fn ShouldMergeBlock(
    mut data: *const uint8_t,
    mut len: size_t,
    mut depths: *const uint8_t,
) -> libc::c_int {
    let mut histo: [size_t; 256] = [
        0 as libc::c_int as size_t,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    ];
    static mut kSampleRate: size_t = 43 as libc::c_int as size_t;
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < len {
        histo[*data.offset(i as isize)
            as usize] = (histo[*data.offset(i as isize) as usize]).wrapping_add(1);
        histo[*data.offset(i as isize) as usize];
        i = i.wrapping_add(kSampleRate);
    }
    let total: size_t = len
        .wrapping_add(kSampleRate)
        .wrapping_sub(1 as libc::c_int as size_t) / kSampleRate;
    let mut r: libc::c_double = (FastLog2(total) + 0.5f64) * total as libc::c_double
        + 200 as libc::c_int as libc::c_double;
    i = 0 as libc::c_int as size_t;
    while i < 256 as libc::c_int as size_t {
        r
            -= histo[i as usize] as libc::c_double
                * (*depths.offset(i as isize) as libc::c_int as libc::c_double
                    + FastLog2(histo[i as usize]));
        i = i.wrapping_add(1);
        i;
    }
    return if r >= 0.0f64 { 1 as libc::c_int } else { 0 as libc::c_int };
}
#[inline(always)]
unsafe extern "C" fn ShouldUseUncompressedMode(
    mut metablock_start: *const uint8_t,
    mut next_emit: *const uint8_t,
    insertlen: size_t,
    literal_ratio: size_t,
) -> libc::c_int {
    let compressed: size_t = next_emit.offset_from(metablock_start) as libc::c_long
        as size_t;
    if compressed * 50 as libc::c_int as size_t > insertlen {
        return 0 as libc::c_int
    } else {
        return if literal_ratio > 980 as libc::c_int as size_t {
            1 as libc::c_int
        } else {
            0 as libc::c_int
        }
    };
}
unsafe extern "C" fn EmitUncompressedMetaBlock(
    mut begin: *const uint8_t,
    mut end: *const uint8_t,
    storage_ix_start: size_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let len: size_t = end.offset_from(begin) as libc::c_long as size_t;
    RewindBitPosition(storage_ix_start, storage_ix, storage);
    BrotliStoreMetaBlockHeader(len, 1 as libc::c_int, storage_ix, storage);
    *storage_ix = (*storage_ix).wrapping_add(7 as libc::c_uint as size_t)
        & !(7 as libc::c_uint) as size_t;
    memcpy(
        &mut *storage.offset((*storage_ix >> 3 as libc::c_int) as isize) as *mut uint8_t
            as *mut libc::c_void,
        begin as *const libc::c_void,
        len,
    );
    *storage_ix = (*storage_ix).wrapping_add(len << 3 as libc::c_int);
    *storage
        .offset(
            (*storage_ix >> 3 as libc::c_int) as isize,
        ) = 0 as libc::c_int as uint8_t;
}
static mut kCmdHistoSeed: [uint32_t; 128] = [
    0 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    1 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
    0 as libc::c_int as uint32_t,
];
#[inline(always)]
unsafe extern "C" fn BrotliCompressFragmentFastImpl(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut table_bits: size_t,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let mut current_block: u64;
    let mut cmd_histo: [uint32_t; 128] = [0; 128];
    let mut ip_end: *const uint8_t = 0 as *const uint8_t;
    let mut next_emit: *const uint8_t = input;
    let mut base_ip: *const uint8_t = input;
    static mut kFirstBlockSize: size_t = ((3 as libc::c_int) << 15 as libc::c_int)
        as size_t;
    static mut kMergeBlockSize: size_t = ((1 as libc::c_int) << 16 as libc::c_int)
        as size_t;
    let kInputMarginBytes: size_t = 16 as libc::c_int as size_t;
    let kMinMatchLen: size_t = 5 as libc::c_int as size_t;
    let mut metablock_start: *const uint8_t = input;
    let mut block_size: size_t = brotli_min_size_t(input_size, kFirstBlockSize);
    let mut total_block_size: size_t = block_size;
    let mut mlen_storage_ix: size_t = (*storage_ix)
        .wrapping_add(3 as libc::c_int as size_t);
    let mut lit_depth: [uint8_t; 256] = [0; 256];
    let mut lit_bits: [uint16_t; 256] = [0; 256];
    let mut literal_ratio: size_t = 0;
    let mut ip: *const uint8_t = 0 as *const uint8_t;
    let mut last_distance: libc::c_int = 0;
    let shift: size_t = (64 as libc::c_uint as size_t).wrapping_sub(table_bits);
    BrotliStoreMetaBlockHeader(block_size, 0 as libc::c_int, storage_ix, storage);
    BrotliWriteBits(
        13 as libc::c_int as size_t,
        0 as libc::c_int as uint64_t,
        storage_ix,
        storage,
    );
    literal_ratio = BuildAndStoreLiteralPrefixCode(
        m,
        input,
        block_size,
        lit_depth.as_mut_ptr(),
        lit_bits.as_mut_ptr(),
        storage_ix,
        storage,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i.wrapping_add(7 as libc::c_int as size_t) < *cmd_code_numbits {
        BrotliWriteBits(
            8 as libc::c_int as size_t,
            *cmd_code.offset((i >> 3 as libc::c_int) as isize) as uint64_t,
            storage_ix,
            storage,
        );
        i = i.wrapping_add(8 as libc::c_int as size_t);
    }
    BrotliWriteBits(
        *cmd_code_numbits & 7 as libc::c_int as size_t,
        *cmd_code.offset((*cmd_code_numbits >> 3 as libc::c_int) as isize) as uint64_t,
        storage_ix,
        storage,
    );
    loop {
        memcpy(
            cmd_histo.as_mut_ptr() as *mut libc::c_void,
            kCmdHistoSeed.as_mut_ptr() as *const libc::c_void,
            ::core::mem::size_of::<[uint32_t; 128]>() as libc::c_ulong,
        );
        ip = input;
        last_distance = -(1 as libc::c_int);
        ip_end = input.offset(block_size as isize);
        if (block_size >= kInputMarginBytes) as libc::c_int as libc::c_long != 0 {
            let len_limit: size_t = brotli_min_size_t(
                block_size.wrapping_sub(kMinMatchLen),
                input_size.wrapping_sub(kInputMarginBytes),
            );
            let mut ip_limit: *const uint8_t = input.offset(len_limit as isize);
            let mut next_hash: uint32_t = 0;
            ip = ip.offset(1);
            next_hash = Hash(ip, shift);
            's_111: loop {
                let mut skip: uint32_t = 32 as libc::c_int as uint32_t;
                let mut next_ip: *const uint8_t = ip;
                let mut candidate: *const uint8_t = 0 as *const uint8_t;
                loop {
                    let mut hash: uint32_t = next_hash;
                    let fresh20 = skip;
                    skip = skip.wrapping_add(1);
                    let mut bytes_between_hash_lookups: uint32_t = fresh20
                        >> 5 as libc::c_int;
                    ip = next_ip;
                    next_ip = ip.offset(bytes_between_hash_lookups as isize);
                    if (next_ip > ip_limit) as libc::c_int as libc::c_long != 0 {
                        current_block = 2472048668343472511;
                        break 's_111;
                    }
                    next_hash = Hash(next_ip, shift);
                    candidate = ip.offset(-(last_distance as isize));
                    if IsMatch(ip, candidate) != 0 {
                        if (candidate < ip) as libc::c_int as libc::c_long != 0 {
                            *table
                                .offset(
                                    hash as isize,
                                ) = ip.offset_from(base_ip) as libc::c_long as libc::c_int;
                            current_block = 11048769245176032998;
                        } else {
                            current_block = 17500079516916021833;
                        }
                    } else {
                        current_block = 17500079516916021833;
                    }
                    match current_block {
                        17500079516916021833 => {
                            candidate = base_ip
                                .offset(*table.offset(hash as isize) as isize);
                            *table
                                .offset(
                                    hash as isize,
                                ) = ip.offset_from(base_ip) as libc::c_long as libc::c_int;
                            if (IsMatch(ip, candidate) == 0) as libc::c_int
                                as libc::c_long != 0
                            {
                                continue;
                            }
                        }
                        _ => {}
                    }
                    if !(ip.offset_from(candidate) as libc::c_long
                        > ((1 as libc::c_int as size_t) << 18 as libc::c_int)
                            .wrapping_sub(16 as libc::c_int as size_t) as libc::c_long)
                    {
                        break;
                    }
                }
                let mut base: *const uint8_t = ip;
                let mut matched: size_t = (5 as libc::c_int as size_t)
                    .wrapping_add(
                        FindMatchLengthWithLimit(
                            candidate.offset(5 as libc::c_int as isize),
                            ip.offset(5 as libc::c_int as isize),
                            (ip_end.offset_from(ip) as libc::c_long as size_t)
                                .wrapping_sub(5 as libc::c_int as size_t),
                        ),
                    );
                let mut distance: libc::c_int = base.offset_from(candidate)
                    as libc::c_long as libc::c_int;
                let mut insert: size_t = base.offset_from(next_emit) as libc::c_long
                    as size_t;
                ip = ip.offset(matched as isize);
                if (insert < 6210 as libc::c_int as size_t) as libc::c_int
                    as libc::c_long != 0
                {
                    EmitInsertLen(
                        insert,
                        cmd_depth as *const uint8_t,
                        cmd_bits as *const uint16_t,
                        cmd_histo.as_mut_ptr(),
                        storage_ix,
                        storage,
                    );
                } else if ShouldUseUncompressedMode(
                    metablock_start,
                    next_emit,
                    insert,
                    literal_ratio,
                ) != 0
                {
                    EmitUncompressedMetaBlock(
                        metablock_start,
                        base,
                        mlen_storage_ix.wrapping_sub(3 as libc::c_int as size_t),
                        storage_ix,
                        storage,
                    );
                    input_size = input_size
                        .wrapping_sub(base.offset_from(input) as libc::c_long as size_t);
                    input = base;
                    next_emit = input;
                    current_block = 16016704754391128094;
                    break;
                } else {
                    EmitLongInsertLen(
                        insert,
                        cmd_depth as *const uint8_t,
                        cmd_bits as *const uint16_t,
                        cmd_histo.as_mut_ptr(),
                        storage_ix,
                        storage,
                    );
                }
                EmitLiterals(
                    next_emit,
                    insert,
                    lit_depth.as_mut_ptr() as *const uint8_t,
                    lit_bits.as_mut_ptr() as *const uint16_t,
                    storage_ix,
                    storage,
                );
                if distance == last_distance {
                    BrotliWriteBits(
                        *cmd_depth.offset(64 as libc::c_int as isize) as size_t,
                        *cmd_bits.offset(64 as libc::c_int as isize) as uint64_t,
                        storage_ix,
                        storage,
                    );
                    cmd_histo[64 as libc::c_int
                        as usize] = (cmd_histo[64 as libc::c_int as usize])
                        .wrapping_add(1);
                    cmd_histo[64 as libc::c_int as usize];
                } else {
                    EmitDistance(
                        distance as size_t,
                        cmd_depth as *const uint8_t,
                        cmd_bits as *const uint16_t,
                        cmd_histo.as_mut_ptr(),
                        storage_ix,
                        storage,
                    );
                    last_distance = distance;
                }
                EmitCopyLenLastDistance(
                    matched,
                    cmd_depth as *const uint8_t,
                    cmd_bits as *const uint16_t,
                    cmd_histo.as_mut_ptr(),
                    storage_ix,
                    storage,
                );
                next_emit = ip;
                if (ip >= ip_limit) as libc::c_int as libc::c_long != 0 {
                    current_block = 2472048668343472511;
                    break;
                }
                let mut input_bytes: uint64_t = BrotliUnalignedRead64(
                    ip.offset(-(3 as libc::c_int as isize)) as *const libc::c_void,
                );
                let mut prev_hash: uint32_t = HashBytesAtOffset(
                    input_bytes,
                    0 as libc::c_int,
                    shift,
                );
                let mut cur_hash: uint32_t = HashBytesAtOffset(
                    input_bytes,
                    3 as libc::c_int,
                    shift,
                );
                *table
                    .offset(
                        prev_hash as isize,
                    ) = (ip.offset_from(base_ip) as libc::c_long
                    - 3 as libc::c_int as libc::c_long) as libc::c_int;
                prev_hash = HashBytesAtOffset(input_bytes, 1 as libc::c_int, shift);
                *table
                    .offset(
                        prev_hash as isize,
                    ) = (ip.offset_from(base_ip) as libc::c_long
                    - 2 as libc::c_int as libc::c_long) as libc::c_int;
                prev_hash = HashBytesAtOffset(input_bytes, 2 as libc::c_int, shift);
                *table
                    .offset(
                        prev_hash as isize,
                    ) = (ip.offset_from(base_ip) as libc::c_long
                    - 1 as libc::c_int as libc::c_long) as libc::c_int;
                candidate = base_ip.offset(*table.offset(cur_hash as isize) as isize);
                *table
                    .offset(
                        cur_hash as isize,
                    ) = ip.offset_from(base_ip) as libc::c_long as libc::c_int;
                while IsMatch(ip, candidate) != 0 {
                    let mut base_0: *const uint8_t = ip;
                    let mut matched_0: size_t = (5 as libc::c_int as size_t)
                        .wrapping_add(
                            FindMatchLengthWithLimit(
                                candidate.offset(5 as libc::c_int as isize),
                                ip.offset(5 as libc::c_int as isize),
                                (ip_end.offset_from(ip) as libc::c_long as size_t)
                                    .wrapping_sub(5 as libc::c_int as size_t),
                            ),
                        );
                    if ip.offset_from(candidate) as libc::c_long
                        > ((1 as libc::c_int as size_t) << 18 as libc::c_int)
                            .wrapping_sub(16 as libc::c_int as size_t) as libc::c_long
                    {
                        break;
                    }
                    ip = ip.offset(matched_0 as isize);
                    last_distance = base_0.offset_from(candidate) as libc::c_long
                        as libc::c_int;
                    EmitCopyLen(
                        matched_0,
                        cmd_depth as *const uint8_t,
                        cmd_bits as *const uint16_t,
                        cmd_histo.as_mut_ptr(),
                        storage_ix,
                        storage,
                    );
                    EmitDistance(
                        last_distance as size_t,
                        cmd_depth as *const uint8_t,
                        cmd_bits as *const uint16_t,
                        cmd_histo.as_mut_ptr(),
                        storage_ix,
                        storage,
                    );
                    next_emit = ip;
                    if (ip >= ip_limit) as libc::c_int as libc::c_long != 0 {
                        current_block = 2472048668343472511;
                        break 's_111;
                    }
                    let mut input_bytes_0: uint64_t = BrotliUnalignedRead64(
                        ip.offset(-(3 as libc::c_int as isize)) as *const libc::c_void,
                    );
                    let mut prev_hash_0: uint32_t = HashBytesAtOffset(
                        input_bytes_0,
                        0 as libc::c_int,
                        shift,
                    );
                    let mut cur_hash_0: uint32_t = HashBytesAtOffset(
                        input_bytes_0,
                        3 as libc::c_int,
                        shift,
                    );
                    *table
                        .offset(
                            prev_hash_0 as isize,
                        ) = (ip.offset_from(base_ip) as libc::c_long
                        - 3 as libc::c_int as libc::c_long) as libc::c_int;
                    prev_hash_0 = HashBytesAtOffset(
                        input_bytes_0,
                        1 as libc::c_int,
                        shift,
                    );
                    *table
                        .offset(
                            prev_hash_0 as isize,
                        ) = (ip.offset_from(base_ip) as libc::c_long
                        - 2 as libc::c_int as libc::c_long) as libc::c_int;
                    prev_hash_0 = HashBytesAtOffset(
                        input_bytes_0,
                        2 as libc::c_int,
                        shift,
                    );
                    *table
                        .offset(
                            prev_hash_0 as isize,
                        ) = (ip.offset_from(base_ip) as libc::c_long
                        - 1 as libc::c_int as libc::c_long) as libc::c_int;
                    candidate = base_ip
                        .offset(*table.offset(cur_hash_0 as isize) as isize);
                    *table
                        .offset(
                            cur_hash_0 as isize,
                        ) = ip.offset_from(base_ip) as libc::c_long as libc::c_int;
                }
                ip = ip.offset(1);
                next_hash = Hash(ip, shift);
            }
        } else {
            current_block = 2472048668343472511;
        }
        match current_block {
            2472048668343472511 => {
                input = input.offset(block_size as isize);
                input_size = input_size.wrapping_sub(block_size);
                block_size = brotli_min_size_t(input_size, kMergeBlockSize);
                if input_size > 0 as libc::c_int as size_t
                    && total_block_size.wrapping_add(block_size)
                        <= ((1 as libc::c_int) << 20 as libc::c_int) as size_t
                    && ShouldMergeBlock(input, block_size, lit_depth.as_mut_ptr()) != 0
                {
                    total_block_size = total_block_size.wrapping_add(block_size);
                    UpdateBits(
                        20 as libc::c_int as size_t,
                        total_block_size.wrapping_sub(1 as libc::c_int as size_t)
                            as uint32_t,
                        mlen_storage_ix,
                        storage,
                    );
                    continue;
                } else {
                    if next_emit < ip_end {
                        let insert_0: size_t = ip_end.offset_from(next_emit)
                            as libc::c_long as size_t;
                        if (insert_0 < 6210 as libc::c_int as size_t) as libc::c_int
                            as libc::c_long != 0
                        {
                            EmitInsertLen(
                                insert_0,
                                cmd_depth as *const uint8_t,
                                cmd_bits as *const uint16_t,
                                cmd_histo.as_mut_ptr(),
                                storage_ix,
                                storage,
                            );
                            EmitLiterals(
                                next_emit,
                                insert_0,
                                lit_depth.as_mut_ptr() as *const uint8_t,
                                lit_bits.as_mut_ptr() as *const uint16_t,
                                storage_ix,
                                storage,
                            );
                        } else if ShouldUseUncompressedMode(
                            metablock_start,
                            next_emit,
                            insert_0,
                            literal_ratio,
                        ) != 0
                        {
                            EmitUncompressedMetaBlock(
                                metablock_start,
                                ip_end,
                                mlen_storage_ix.wrapping_sub(3 as libc::c_int as size_t),
                                storage_ix,
                                storage,
                            );
                        } else {
                            EmitLongInsertLen(
                                insert_0,
                                cmd_depth as *const uint8_t,
                                cmd_bits as *const uint16_t,
                                cmd_histo.as_mut_ptr(),
                                storage_ix,
                                storage,
                            );
                            EmitLiterals(
                                next_emit,
                                insert_0,
                                lit_depth.as_mut_ptr() as *const uint8_t,
                                lit_bits.as_mut_ptr() as *const uint16_t,
                                storage_ix,
                                storage,
                            );
                        }
                    }
                    next_emit = ip_end;
                }
            }
            _ => {}
        }
        if !(input_size > 0 as libc::c_int as size_t) {
            break;
        }
        metablock_start = input;
        block_size = brotli_min_size_t(input_size, kFirstBlockSize);
        total_block_size = block_size;
        mlen_storage_ix = (*storage_ix).wrapping_add(3 as libc::c_int as size_t);
        BrotliStoreMetaBlockHeader(block_size, 0 as libc::c_int, storage_ix, storage);
        BrotliWriteBits(
            13 as libc::c_int as size_t,
            0 as libc::c_int as uint64_t,
            storage_ix,
            storage,
        );
        literal_ratio = BuildAndStoreLiteralPrefixCode(
            m,
            input,
            block_size,
            lit_depth.as_mut_ptr(),
            lit_bits.as_mut_ptr(),
            storage_ix,
            storage,
        );
        if 0 as libc::c_int != 0 {
            return;
        }
        BuildAndStoreCommandPrefixCode(
            cmd_histo.as_mut_ptr() as *const uint32_t,
            cmd_depth,
            cmd_bits,
            storage_ix,
            storage,
        );
    }
    if is_last == 0 {
        *cmd_code.offset(0 as libc::c_int as isize) = 0 as libc::c_int as uint8_t;
        *cmd_code_numbits = 0 as libc::c_int as size_t;
        BuildAndStoreCommandPrefixCode(
            cmd_histo.as_mut_ptr() as *const uint32_t,
            cmd_depth,
            cmd_bits,
            cmd_code_numbits,
            cmd_code,
        );
    }
}
#[inline(never)]
unsafe extern "C" fn BrotliCompressFragmentFastImpl9(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    BrotliCompressFragmentFastImpl(
        m,
        input,
        input_size,
        is_last,
        table,
        9 as libc::c_int as size_t,
        cmd_depth,
        cmd_bits,
        cmd_code_numbits,
        cmd_code,
        storage_ix,
        storage,
    );
}
#[inline(never)]
unsafe extern "C" fn BrotliCompressFragmentFastImpl15(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    BrotliCompressFragmentFastImpl(
        m,
        input,
        input_size,
        is_last,
        table,
        15 as libc::c_int as size_t,
        cmd_depth,
        cmd_bits,
        cmd_code_numbits,
        cmd_code,
        storage_ix,
        storage,
    );
}
#[inline(never)]
unsafe extern "C" fn BrotliCompressFragmentFastImpl13(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    BrotliCompressFragmentFastImpl(
        m,
        input,
        input_size,
        is_last,
        table,
        13 as libc::c_int as size_t,
        cmd_depth,
        cmd_bits,
        cmd_code_numbits,
        cmd_code,
        storage_ix,
        storage,
    );
}
#[inline(never)]
unsafe extern "C" fn BrotliCompressFragmentFastImpl11(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    BrotliCompressFragmentFastImpl(
        m,
        input,
        input_size,
        is_last,
        table,
        11 as libc::c_int as size_t,
        cmd_depth,
        cmd_bits,
        cmd_code_numbits,
        cmd_code,
        storage_ix,
        storage,
    );
}
#[no_mangle]
pub unsafe extern "C" fn BrotliCompressFragmentFast(
    mut m: *mut MemoryManager,
    mut input: *const uint8_t,
    mut input_size: size_t,
    mut is_last: libc::c_int,
    mut table: *mut libc::c_int,
    mut table_size: size_t,
    mut cmd_depth: *mut uint8_t,
    mut cmd_bits: *mut uint16_t,
    mut cmd_code_numbits: *mut size_t,
    mut cmd_code: *mut uint8_t,
    mut storage_ix: *mut size_t,
    mut storage: *mut uint8_t,
) {
    let initial_storage_ix: size_t = *storage_ix;
    let table_bits: size_t = Log2FloorNonZero(table_size) as size_t;
    if input_size == 0 as libc::c_int as size_t {
        BrotliWriteBits(
            1 as libc::c_int as size_t,
            1 as libc::c_int as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            1 as libc::c_int as size_t,
            1 as libc::c_int as uint64_t,
            storage_ix,
            storage,
        );
        *storage_ix = (*storage_ix).wrapping_add(7 as libc::c_uint as size_t)
            & !(7 as libc::c_uint) as size_t;
        return;
    }
    match table_bits {
        9 => {
            BrotliCompressFragmentFastImpl9(
                m,
                input,
                input_size,
                is_last,
                table,
                cmd_depth,
                cmd_bits,
                cmd_code_numbits,
                cmd_code,
                storage_ix,
                storage,
            );
        }
        11 => {
            BrotliCompressFragmentFastImpl11(
                m,
                input,
                input_size,
                is_last,
                table,
                cmd_depth,
                cmd_bits,
                cmd_code_numbits,
                cmd_code,
                storage_ix,
                storage,
            );
        }
        13 => {
            BrotliCompressFragmentFastImpl13(
                m,
                input,
                input_size,
                is_last,
                table,
                cmd_depth,
                cmd_bits,
                cmd_code_numbits,
                cmd_code,
                storage_ix,
                storage,
            );
        }
        15 => {
            BrotliCompressFragmentFastImpl15(
                m,
                input,
                input_size,
                is_last,
                table,
                cmd_depth,
                cmd_bits,
                cmd_code_numbits,
                cmd_code,
                storage_ix,
                storage,
            );
        }
        _ => {}
    }
    if (*storage_ix).wrapping_sub(initial_storage_ix)
        > (31 as libc::c_int as size_t).wrapping_add(input_size << 3 as libc::c_int)
    {
        EmitUncompressedMetaBlock(
            input,
            input.offset(input_size as isize),
            initial_storage_ix,
            storage_ix,
            storage,
        );
    }
    if is_last != 0 {
        BrotliWriteBits(
            1 as libc::c_int as size_t,
            1 as libc::c_int as uint64_t,
            storage_ix,
            storage,
        );
        BrotliWriteBits(
            1 as libc::c_int as size_t,
            1 as libc::c_int as uint64_t,
            storage_ix,
            storage,
        );
        *storage_ix = (*storage_ix).wrapping_add(7 as libc::c_uint as size_t)
            & !(7 as libc::c_uint) as size_t;
    }
}
