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
    fn BrotliAllocate(m: *mut MemoryManager, n: size_t) -> *mut libc::c_void;
    fn BrotliFree(m: *mut MemoryManager, p: *mut libc::c_void);
    fn BrotliSplitBlock(
        m: *mut MemoryManager,
        cmds: *const Command,
        num_commands: size_t,
        data: *const uint8_t,
        offset: size_t,
        mask: size_t,
        params: *const BrotliEncoderParams,
        literal_split: *mut BlockSplit,
        insert_and_copy_split: *mut BlockSplit,
        dist_split: *mut BlockSplit,
    );
    fn BrotliBuildHistogramsWithContext(
        cmds: *const Command,
        num_commands: size_t,
        literal_split: *const BlockSplit,
        insert_and_copy_split: *const BlockSplit,
        dist_split: *const BlockSplit,
        ringbuffer: *const uint8_t,
        pos: size_t,
        mask: size_t,
        prev_byte: uint8_t,
        prev_byte2: uint8_t,
        context_modes: *const ContextType,
        literal_histograms: *mut HistogramLiteral,
        insert_and_copy_histograms: *mut HistogramCommand,
        copy_dist_histograms: *mut HistogramDistance,
    );
    fn BrotliPopulationCostDistance(_: *const HistogramDistance) -> libc::c_double;
    fn BrotliClusterHistogramsLiteral(
        m: *mut MemoryManager,
        in_0: *const HistogramLiteral,
        in_size: size_t,
        max_histograms: size_t,
        out: *mut HistogramLiteral,
        out_size: *mut size_t,
        histogram_symbols: *mut uint32_t,
    );
    fn BrotliClusterHistogramsDistance(
        m: *mut MemoryManager,
        in_0: *const HistogramDistance,
        in_size: size_t,
        max_histograms: size_t,
        out: *mut HistogramDistance,
        out_size: *mut size_t,
        histogram_symbols: *mut uint32_t,
    );
    fn BrotliOptimizeHuffmanCountsForRle(
        length: size_t,
        counts: *mut uint32_t,
        good_for_rle: *mut uint8_t,
    );
}
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
pub type __uint16_t = libc::c_ushort;
pub type __uint32_t = libc::c_uint;
pub type __uint64_t = libc::c_ulong;
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
pub type ContextType = libc::c_uint;
pub const CONTEXT_SIGNED: ContextType = 3;
pub const CONTEXT_UTF8: ContextType = 2;
pub const CONTEXT_MSB6: ContextType = 1;
pub const CONTEXT_LSB6: ContextType = 0;
pub type ContextLut = *const uint8_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliDistanceCodeLimit {
    pub max_alphabet_size: uint32_t,
    pub max_distance: uint32_t,
}
pub type BrotliEncoderMode = libc::c_uint;
pub const BROTLI_MODE_FONT: BrotliEncoderMode = 2;
pub const BROTLI_MODE_TEXT: BrotliEncoderMode = 1;
pub const BROTLI_MODE_GENERIC: BrotliEncoderMode = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliDictionary {
    pub size_bits_by_length: [uint8_t; 32],
    pub offsets_by_length: [uint32_t; 32],
    pub data_size: size_t,
    pub data: *const uint8_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct DictWord {
    pub len: uint8_t,
    pub transform: uint8_t,
    pub idx: uint16_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliEncoderDictionary {
    pub words: *const BrotliDictionary,
    pub num_transforms: uint32_t,
    pub cutoffTransformsCount: uint32_t,
    pub cutoffTransforms: uint64_t,
    pub hash_table_words: *const uint16_t,
    pub hash_table_lengths: *const uint8_t,
    pub buckets: *const uint16_t,
    pub dict_words: *const DictWord,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliHasherParams {
    pub type_0: libc::c_int,
    pub bucket_bits: libc::c_int,
    pub block_bits: libc::c_int,
    pub hash_len: libc::c_int,
    pub num_last_distances_to_check: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliDistanceParams {
    pub distance_postfix_bits: uint32_t,
    pub num_direct_distance_codes: uint32_t,
    pub alphabet_size_max: uint32_t,
    pub alphabet_size_limit: uint32_t,
    pub max_distance: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliEncoderParams {
    pub mode: BrotliEncoderMode,
    pub quality: libc::c_int,
    pub lgwin: libc::c_int,
    pub lgblock: libc::c_int,
    pub stream_offset: size_t,
    pub size_hint: size_t,
    pub disable_literal_context_modeling: libc::c_int,
    pub large_window: libc::c_int,
    pub hasher: BrotliHasherParams,
    pub dist: BrotliDistanceParams,
    pub dictionary: BrotliEncoderDictionary,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Command {
    pub insert_len_: uint32_t,
    pub copy_len_: uint32_t,
    pub dist_extra_: uint32_t,
    pub cmd_prefix_: uint16_t,
    pub dist_prefix_: uint16_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct MemoryManager {
    pub alloc_func: brotli_alloc_func,
    pub free_func: brotli_free_func,
    pub opaque: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BlockSplit {
    pub num_types: size_t,
    pub num_blocks: size_t,
    pub types: *mut uint8_t,
    pub lengths: *mut uint32_t,
    pub types_alloc_size: size_t,
    pub lengths_alloc_size: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HistogramLiteral {
    pub data_: [uint32_t; 256],
    pub total_count_: size_t,
    pub bit_cost_: libc::c_double,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HistogramCommand {
    pub data_: [uint32_t; 704],
    pub total_count_: size_t,
    pub bit_cost_: libc::c_double,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HistogramDistance {
    pub data_: [uint32_t; 544],
    pub total_count_: size_t,
    pub bit_cost_: libc::c_double,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct MetaBlockSplit {
    pub literal_split: BlockSplit,
    pub command_split: BlockSplit,
    pub distance_split: BlockSplit,
    pub literal_context_map: *mut uint32_t,
    pub literal_context_map_size: size_t,
    pub distance_context_map: *mut uint32_t,
    pub distance_context_map_size: size_t,
    pub literal_histograms: *mut HistogramLiteral,
    pub literal_histograms_size: size_t,
    pub command_histograms: *mut HistogramCommand,
    pub command_histograms_size: size_t,
    pub distance_histograms: *mut HistogramDistance,
    pub distance_histograms_size: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BlockSplitterDistance {
    pub alphabet_size_: size_t,
    pub min_block_size_: size_t,
    pub split_threshold_: libc::c_double,
    pub num_blocks_: size_t,
    pub split_: *mut BlockSplit,
    pub histograms_: *mut HistogramDistance,
    pub histograms_size_: *mut size_t,
    pub target_block_size_: size_t,
    pub block_size_: size_t,
    pub curr_histogram_ix_: size_t,
    pub last_histogram_ix_: [size_t; 2],
    pub last_entropy_: [libc::c_double; 2],
    pub merge_last_count_: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BlockSplitterCommand {
    pub alphabet_size_: size_t,
    pub min_block_size_: size_t,
    pub split_threshold_: libc::c_double,
    pub num_blocks_: size_t,
    pub split_: *mut BlockSplit,
    pub histograms_: *mut HistogramCommand,
    pub histograms_size_: *mut size_t,
    pub target_block_size_: size_t,
    pub block_size_: size_t,
    pub curr_histogram_ix_: size_t,
    pub last_histogram_ix_: [size_t; 2],
    pub last_entropy_: [libc::c_double; 2],
    pub merge_last_count_: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ContextBlockSplitter {
    pub alphabet_size_: size_t,
    pub num_contexts_: size_t,
    pub max_block_types_: size_t,
    pub min_block_size_: size_t,
    pub split_threshold_: libc::c_double,
    pub num_blocks_: size_t,
    pub split_: *mut BlockSplit,
    pub histograms_: *mut HistogramLiteral,
    pub histograms_size_: *mut size_t,
    pub target_block_size_: size_t,
    pub block_size_: size_t,
    pub curr_histogram_ix_: size_t,
    pub last_histogram_ix_: [size_t; 2],
    pub last_entropy_: [libc::c_double; 26],
    pub merge_last_count_: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub plain: BlockSplitterLiteral,
    pub ctx: ContextBlockSplitter,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BlockSplitterLiteral {
    pub alphabet_size_: size_t,
    pub min_block_size_: size_t,
    pub split_threshold_: libc::c_double,
    pub num_blocks_: size_t,
    pub split_: *mut BlockSplit,
    pub histograms_: *mut HistogramLiteral,
    pub histograms_size_: *mut size_t,
    pub target_block_size_: size_t,
    pub block_size_: size_t,
    pub curr_histogram_ix_: size_t,
    pub last_histogram_ix_: [size_t; 2],
    pub last_entropy_: [libc::c_double; 2],
    pub merge_last_count_: size_t,
}
#[inline(always)]
unsafe extern "C" fn brotli_min_size_t(mut a: size_t, mut b: size_t) -> size_t {
    return if a < b { a } else { b };
}
#[inline(always)]
unsafe extern "C" fn brotli_max_size_t(mut a: size_t, mut b: size_t) -> size_t {
    return if a > b { a } else { b };
}
#[inline(always)]
unsafe extern "C" fn BrotliCalculateDistanceCodeLimit(
    mut max_distance: uint32_t,
    mut npostfix: uint32_t,
    mut ndirect: uint32_t,
) -> BrotliDistanceCodeLimit {
    let mut result: BrotliDistanceCodeLimit = BrotliDistanceCodeLimit {
        max_alphabet_size: 0,
        max_distance: 0,
    };
    Some(
        BrotliCalculateDistanceCodeLimit
            as unsafe extern "C" fn(
                uint32_t,
                uint32_t,
                uint32_t,
            ) -> BrotliDistanceCodeLimit,
    );
    if max_distance <= ndirect {
        result
            .max_alphabet_size = max_distance
            .wrapping_add(16 as libc::c_int as uint32_t);
        result.max_distance = max_distance;
        return result;
    } else {
        let mut forbidden_distance: uint32_t = max_distance
            .wrapping_add(1 as libc::c_int as uint32_t);
        let mut offset: uint32_t = forbidden_distance
            .wrapping_sub(ndirect)
            .wrapping_sub(1 as libc::c_int as uint32_t);
        let mut ndistbits: uint32_t = 0 as libc::c_int as uint32_t;
        let mut tmp: uint32_t = 0;
        let mut half: uint32_t = 0;
        let mut group: uint32_t = 0;
        let mut postfix: uint32_t = ((1 as libc::c_uint) << npostfix)
            .wrapping_sub(1 as libc::c_int as libc::c_uint);
        let mut extra: uint32_t = 0;
        let mut start: uint32_t = 0;
        offset = (offset >> npostfix).wrapping_add(4 as libc::c_int as uint32_t);
        tmp = offset / 2 as libc::c_int as uint32_t;
        while tmp != 0 as libc::c_int as uint32_t {
            ndistbits = ndistbits.wrapping_add(1);
            ndistbits;
            tmp = tmp >> 1 as libc::c_int;
        }
        ndistbits = ndistbits.wrapping_sub(1);
        ndistbits;
        half = offset >> ndistbits & 1 as libc::c_int as uint32_t;
        group = ndistbits.wrapping_sub(1 as libc::c_int as uint32_t) << 1 as libc::c_int
            | half;
        if group == 0 as libc::c_int as uint32_t {
            result
                .max_alphabet_size = ndirect.wrapping_add(16 as libc::c_int as uint32_t);
            result.max_distance = ndirect;
            return result;
        }
        group = group.wrapping_sub(1);
        group;
        ndistbits = (group >> 1 as libc::c_int)
            .wrapping_add(1 as libc::c_int as uint32_t);
        extra = ((1 as libc::c_uint) << ndistbits)
            .wrapping_sub(1 as libc::c_int as libc::c_uint);
        start = ((1 as libc::c_uint)
            << ndistbits.wrapping_add(1 as libc::c_int as uint32_t))
            .wrapping_sub(4 as libc::c_int as libc::c_uint);
        start = start.wrapping_add((group & 1 as libc::c_int as uint32_t) << ndistbits);
        result
            .max_alphabet_size = (group << npostfix | postfix)
            .wrapping_add(ndirect)
            .wrapping_add(16 as libc::c_int as uint32_t)
            .wrapping_add(1 as libc::c_int as uint32_t);
        result
            .max_distance = (start.wrapping_add(extra) << npostfix)
            .wrapping_add(postfix)
            .wrapping_add(ndirect)
            .wrapping_add(1 as libc::c_int as uint32_t);
        return result;
    };
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
unsafe extern "C" fn PrefixEncodeCopyDistance(
    mut distance_code: size_t,
    mut num_direct_codes: size_t,
    mut postfix_bits: size_t,
    mut code: *mut uint16_t,
    mut extra_bits: *mut uint32_t,
) {
    if distance_code < (16 as libc::c_int as size_t).wrapping_add(num_direct_codes) {
        *code = distance_code as uint16_t;
        *extra_bits = 0 as libc::c_int as uint32_t;
        return;
    } else {
        let mut dist: size_t = ((1 as libc::c_int as size_t)
            << postfix_bits.wrapping_add(2 as libc::c_uint as size_t))
            .wrapping_add(
                distance_code
                    .wrapping_sub(16 as libc::c_int as size_t)
                    .wrapping_sub(num_direct_codes),
            );
        let mut bucket: size_t = (Log2FloorNonZero(dist))
            .wrapping_sub(1 as libc::c_int as uint32_t) as size_t;
        let mut postfix_mask: size_t = ((1 as libc::c_uint) << postfix_bits)
            .wrapping_sub(1 as libc::c_int as libc::c_uint) as size_t;
        let mut postfix: size_t = dist & postfix_mask;
        let mut prefix: size_t = dist >> bucket & 1 as libc::c_int as size_t;
        let mut offset: size_t = (2 as libc::c_int as size_t).wrapping_add(prefix)
            << bucket;
        let mut nbits: size_t = bucket.wrapping_sub(postfix_bits);
        *code = (nbits << 10 as libc::c_int
            | (16 as libc::c_int as size_t)
                .wrapping_add(num_direct_codes)
                .wrapping_add(
                    (2 as libc::c_int as size_t
                        * nbits.wrapping_sub(1 as libc::c_int as size_t))
                        .wrapping_add(prefix) << postfix_bits,
                )
                .wrapping_add(postfix)) as uint16_t;
        *extra_bits = (dist.wrapping_sub(offset) >> postfix_bits) as uint32_t;
    };
}
#[inline(always)]
unsafe extern "C" fn CommandRestoreDistanceCode(
    mut self_0: *const Command,
    mut dist: *const BrotliDistanceParams,
) -> uint32_t {
    if ((*self_0).dist_prefix_ as libc::c_uint & 0x3ff as libc::c_uint)
        < (16 as libc::c_int as uint32_t).wrapping_add((*dist).num_direct_distance_codes)
    {
        return (*self_0).dist_prefix_ as libc::c_uint & 0x3ff as libc::c_uint
    } else {
        let mut dcode: uint32_t = (*self_0).dist_prefix_ as libc::c_uint
            & 0x3ff as libc::c_uint;
        let mut nbits: uint32_t = ((*self_0).dist_prefix_ as libc::c_int
            >> 10 as libc::c_int) as uint32_t;
        let mut extra: uint32_t = (*self_0).dist_extra_;
        let mut postfix_mask: uint32_t = ((1 as libc::c_uint)
            << (*dist).distance_postfix_bits)
            .wrapping_sub(1 as libc::c_uint);
        let mut hcode: uint32_t = dcode
            .wrapping_sub((*dist).num_direct_distance_codes)
            .wrapping_sub(16 as libc::c_int as uint32_t)
            >> (*dist).distance_postfix_bits;
        let mut lcode: uint32_t = dcode
            .wrapping_sub((*dist).num_direct_distance_codes)
            .wrapping_sub(16 as libc::c_int as uint32_t) & postfix_mask;
        let mut offset: uint32_t = ((2 as libc::c_uint)
            .wrapping_add(hcode & 1 as libc::c_uint) << nbits)
            .wrapping_sub(4 as libc::c_uint);
        return (offset.wrapping_add(extra) << (*dist).distance_postfix_bits)
            .wrapping_add(lcode)
            .wrapping_add((*dist).num_direct_distance_codes)
            .wrapping_add(16 as libc::c_int as uint32_t);
    };
}
#[inline(always)]
unsafe extern "C" fn CommandCopyLen(mut self_0: *const Command) -> uint32_t {
    return (*self_0).copy_len_ & 0x1ffffff as libc::c_int as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn HistogramClearLiteral(mut self_0: *mut HistogramLiteral) {
    memset(
        ((*self_0).data_).as_mut_ptr() as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<[uint32_t; 256]>() as libc::c_ulong,
    );
    (*self_0).total_count_ = 0 as libc::c_int as size_t;
    (*self_0).bit_cost_ = ::core::f64::INFINITY;
}
#[inline(always)]
unsafe extern "C" fn ClearHistogramsLiteral(
    mut array: *mut HistogramLiteral,
    mut length: size_t,
) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < length {
        HistogramClearLiteral(array.offset(i as isize));
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn HistogramAddLiteral(
    mut self_0: *mut HistogramLiteral,
    mut val: size_t,
) {
    (*self_0).data_[val as usize] = ((*self_0).data_[val as usize]).wrapping_add(1);
    (*self_0).data_[val as usize];
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add(1);
    (*self_0).total_count_;
}
#[inline(always)]
unsafe extern "C" fn HistogramAddHistogramLiteral(
    mut self_0: *mut HistogramLiteral,
    mut v: *const HistogramLiteral,
) {
    let mut i: size_t = 0;
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add((*v).total_count_);
    i = 0 as libc::c_int as size_t;
    while i < 256 as libc::c_int as size_t {
        (*self_0)
            .data_[i
            as usize] = ((*self_0).data_[i as usize])
            .wrapping_add((*v).data_[i as usize]);
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn HistogramClearCommand(mut self_0: *mut HistogramCommand) {
    memset(
        ((*self_0).data_).as_mut_ptr() as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<[uint32_t; 704]>() as libc::c_ulong,
    );
    (*self_0).total_count_ = 0 as libc::c_int as size_t;
    (*self_0).bit_cost_ = ::core::f64::INFINITY;
}
#[inline(always)]
unsafe extern "C" fn ClearHistogramsCommand(
    mut array: *mut HistogramCommand,
    mut length: size_t,
) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < length {
        HistogramClearCommand(array.offset(i as isize));
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn HistogramAddCommand(
    mut self_0: *mut HistogramCommand,
    mut val: size_t,
) {
    (*self_0).data_[val as usize] = ((*self_0).data_[val as usize]).wrapping_add(1);
    (*self_0).data_[val as usize];
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add(1);
    (*self_0).total_count_;
}
#[inline(always)]
unsafe extern "C" fn HistogramAddHistogramCommand(
    mut self_0: *mut HistogramCommand,
    mut v: *const HistogramCommand,
) {
    let mut i: size_t = 0;
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add((*v).total_count_);
    i = 0 as libc::c_int as size_t;
    while i < 704 as libc::c_int as size_t {
        (*self_0)
            .data_[i
            as usize] = ((*self_0).data_[i as usize])
            .wrapping_add((*v).data_[i as usize]);
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn HistogramClearDistance(mut self_0: *mut HistogramDistance) {
    memset(
        ((*self_0).data_).as_mut_ptr() as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<[uint32_t; 544]>() as libc::c_ulong,
    );
    (*self_0).total_count_ = 0 as libc::c_int as size_t;
    (*self_0).bit_cost_ = ::core::f64::INFINITY;
}
#[inline(always)]
unsafe extern "C" fn ClearHistogramsDistance(
    mut array: *mut HistogramDistance,
    mut length: size_t,
) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < length {
        HistogramClearDistance(array.offset(i as isize));
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn HistogramAddDistance(
    mut self_0: *mut HistogramDistance,
    mut val: size_t,
) {
    (*self_0).data_[val as usize] = ((*self_0).data_[val as usize]).wrapping_add(1);
    (*self_0).data_[val as usize];
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add(1);
    (*self_0).total_count_;
}
#[inline(always)]
unsafe extern "C" fn HistogramAddHistogramDistance(
    mut self_0: *mut HistogramDistance,
    mut v: *const HistogramDistance,
) {
    let mut i: size_t = 0;
    (*self_0).total_count_ = ((*self_0).total_count_).wrapping_add((*v).total_count_);
    i = 0 as libc::c_int as size_t;
    while i < 544 as libc::c_int as size_t {
        (*self_0)
            .data_[i
            as usize] = ((*self_0).data_[i as usize])
            .wrapping_add((*v).data_[i as usize]);
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn ShannonEntropy(
    mut population: *const uint32_t,
    mut size: size_t,
    mut total: *mut size_t,
) -> libc::c_double {
    let mut current_block: u64;
    let mut sum: size_t = 0 as libc::c_int as size_t;
    let mut retval: libc::c_double = 0 as libc::c_int as libc::c_double;
    let mut population_end: *const uint32_t = population.offset(size as isize);
    let mut p: size_t = 0;
    if size & 1 as libc::c_int as size_t != 0 {
        current_block = 7735674606488043377;
    } else {
        current_block = 12517898123489920830;
    }
    loop {
        match current_block {
            12517898123489920830 => {
                if !(population < population_end) {
                    break;
                }
                let fresh0 = population;
                population = population.offset(1);
                p = *fresh0 as size_t;
                sum = sum.wrapping_add(p);
                retval -= p as libc::c_double * FastLog2(p);
                current_block = 7735674606488043377;
            }
            _ => {
                let fresh1 = population;
                population = population.offset(1);
                p = *fresh1 as size_t;
                sum = sum.wrapping_add(p);
                retval -= p as libc::c_double * FastLog2(p);
                current_block = 12517898123489920830;
            }
        }
    }
    if sum != 0 {
        retval += sum as libc::c_double * FastLog2(sum);
    }
    *total = sum;
    return retval;
}
#[inline(always)]
unsafe extern "C" fn BitsEntropy(
    mut population: *const uint32_t,
    mut size: size_t,
) -> libc::c_double {
    let mut sum: size_t = 0;
    let mut retval: libc::c_double = ShannonEntropy(population, size, &mut sum);
    if retval < sum as libc::c_double {
        retval = sum as libc::c_double;
    }
    return retval;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliInitDistanceParams(
    mut params: *mut BrotliEncoderParams,
    mut npostfix: uint32_t,
    mut ndirect: uint32_t,
) {
    let mut dist_params: *mut BrotliDistanceParams = &mut (*params).dist;
    let mut alphabet_size_max: uint32_t = 0;
    let mut alphabet_size_limit: uint32_t = 0;
    let mut max_distance: uint32_t = 0;
    (*dist_params).distance_postfix_bits = npostfix;
    (*dist_params).num_direct_distance_codes = ndirect;
    alphabet_size_max = (16 as libc::c_int as uint32_t)
        .wrapping_add(ndirect)
        .wrapping_add(
            (24 as libc::c_uint) << npostfix.wrapping_add(1 as libc::c_int as uint32_t),
        );
    alphabet_size_limit = alphabet_size_max;
    max_distance = ndirect
        .wrapping_add(
            (1 as libc::c_uint)
                << (24 as libc::c_uint)
                    .wrapping_add(npostfix)
                    .wrapping_add(2 as libc::c_int as libc::c_uint),
        )
        .wrapping_sub(
            (1 as libc::c_uint) << npostfix.wrapping_add(2 as libc::c_int as uint32_t),
        );
    if (*params).large_window != 0 {
        let mut limit: BrotliDistanceCodeLimit = BrotliCalculateDistanceCodeLimit(
            0x7ffffffc as libc::c_int as uint32_t,
            npostfix,
            ndirect,
        );
        alphabet_size_max = (16 as libc::c_int as uint32_t)
            .wrapping_add(ndirect)
            .wrapping_add(
                (62 as libc::c_uint)
                    << npostfix.wrapping_add(1 as libc::c_int as uint32_t),
            );
        alphabet_size_limit = limit.max_alphabet_size;
        max_distance = limit.max_distance;
    }
    (*dist_params).alphabet_size_max = alphabet_size_max;
    (*dist_params).alphabet_size_limit = alphabet_size_limit;
    (*dist_params).max_distance = max_distance as size_t;
}
unsafe extern "C" fn RecomputeDistancePrefixes(
    mut cmds: *mut Command,
    mut num_commands: size_t,
    mut orig_params: *const BrotliDistanceParams,
    mut new_params: *const BrotliDistanceParams,
) {
    let mut i: size_t = 0;
    if (*orig_params).distance_postfix_bits == (*new_params).distance_postfix_bits
        && (*orig_params).num_direct_distance_codes
            == (*new_params).num_direct_distance_codes
    {
        return;
    }
    i = 0 as libc::c_int as size_t;
    while i < num_commands {
        let mut cmd: *mut Command = &mut *cmds.offset(i as isize) as *mut Command;
        if CommandCopyLen(cmd) != 0
            && (*cmd).cmd_prefix_ as libc::c_int >= 128 as libc::c_int
        {
            PrefixEncodeCopyDistance(
                CommandRestoreDistanceCode(cmd, orig_params) as size_t,
                (*new_params).num_direct_distance_codes as size_t,
                (*new_params).distance_postfix_bits as size_t,
                &mut (*cmd).dist_prefix_,
                &mut (*cmd).dist_extra_,
            );
        }
        i = i.wrapping_add(1);
        i;
    }
}
unsafe extern "C" fn ComputeDistanceCost(
    mut cmds: *const Command,
    mut num_commands: size_t,
    mut orig_params: *const BrotliDistanceParams,
    mut new_params: *const BrotliDistanceParams,
    mut cost: *mut libc::c_double,
) -> libc::c_int {
    let mut i: size_t = 0;
    let mut equal_params: libc::c_int = 0 as libc::c_int;
    let mut dist_prefix: uint16_t = 0;
    let mut dist_extra: uint32_t = 0;
    let mut extra_bits: libc::c_double = 0.0f64;
    let mut histo: HistogramDistance = HistogramDistance {
        data_: [0; 544],
        total_count_: 0,
        bit_cost_: 0.,
    };
    HistogramClearDistance(&mut histo);
    if (*orig_params).distance_postfix_bits == (*new_params).distance_postfix_bits
        && (*orig_params).num_direct_distance_codes
            == (*new_params).num_direct_distance_codes
    {
        equal_params = 1 as libc::c_int;
    }
    i = 0 as libc::c_int as size_t;
    while i < num_commands {
        let mut cmd: *const Command = &*cmds.offset(i as isize) as *const Command;
        if CommandCopyLen(cmd) != 0
            && (*cmd).cmd_prefix_ as libc::c_int >= 128 as libc::c_int
        {
            if equal_params != 0 {
                dist_prefix = (*cmd).dist_prefix_;
            } else {
                let mut distance: uint32_t = CommandRestoreDistanceCode(
                    cmd,
                    orig_params,
                );
                if distance as size_t > (*new_params).max_distance {
                    return 0 as libc::c_int;
                }
                PrefixEncodeCopyDistance(
                    distance as size_t,
                    (*new_params).num_direct_distance_codes as size_t,
                    (*new_params).distance_postfix_bits as size_t,
                    &mut dist_prefix,
                    &mut dist_extra,
                );
            }
            HistogramAddDistance(
                &mut histo,
                (dist_prefix as libc::c_int & 0x3ff as libc::c_int) as size_t,
            );
            extra_bits
                += (dist_prefix as libc::c_int >> 10 as libc::c_int) as libc::c_double;
        }
        i = i.wrapping_add(1);
        i;
    }
    *cost = BrotliPopulationCostDistance(&mut histo) + extra_bits;
    return 1 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliBuildMetaBlock(
    mut m: *mut MemoryManager,
    mut ringbuffer: *const uint8_t,
    pos: size_t,
    mask: size_t,
    mut params: *mut BrotliEncoderParams,
    mut prev_byte: uint8_t,
    mut prev_byte2: uint8_t,
    mut cmds: *mut Command,
    mut num_commands: size_t,
    mut literal_context_mode: ContextType,
    mut mb: *mut MetaBlockSplit,
) {
    static mut kMaxNumberOfHistograms: size_t = 256 as libc::c_int as size_t;
    let mut distance_histograms: *mut HistogramDistance = 0 as *mut HistogramDistance;
    let mut literal_histograms: *mut HistogramLiteral = 0 as *mut HistogramLiteral;
    let mut literal_context_modes: *mut ContextType = 0 as *mut ContextType;
    let mut literal_histograms_size: size_t = 0;
    let mut distance_histograms_size: size_t = 0;
    let mut i: size_t = 0;
    let mut literal_context_multiplier: size_t = 1 as libc::c_int as size_t;
    let mut npostfix: uint32_t = 0;
    let mut ndirect_msb: uint32_t = 0 as libc::c_int as uint32_t;
    let mut check_orig: libc::c_int = 1 as libc::c_int;
    let mut best_dist_cost: libc::c_double = 1e99f64;
    let mut orig_params: BrotliEncoderParams = *params;
    let mut new_params: BrotliEncoderParams = *params;
    npostfix = 0 as libc::c_int as uint32_t;
    while npostfix <= 3 as libc::c_int as uint32_t {
        while ndirect_msb < 16 as libc::c_int as uint32_t {
            let mut ndirect: uint32_t = ndirect_msb << npostfix;
            let mut skip: libc::c_int = 0;
            let mut dist_cost: libc::c_double = 0.;
            BrotliInitDistanceParams(&mut new_params, npostfix, ndirect);
            if npostfix == orig_params.dist.distance_postfix_bits
                && ndirect == orig_params.dist.num_direct_distance_codes
            {
                check_orig = 0 as libc::c_int;
            }
            skip = (ComputeDistanceCost(
                cmds,
                num_commands,
                &mut orig_params.dist,
                &mut new_params.dist,
                &mut dist_cost,
            ) == 0) as libc::c_int;
            if skip != 0 || dist_cost > best_dist_cost {
                break;
            }
            best_dist_cost = dist_cost;
            (*params).dist = new_params.dist;
            ndirect_msb = ndirect_msb.wrapping_add(1);
            ndirect_msb;
        }
        if ndirect_msb > 0 as libc::c_int as uint32_t {
            ndirect_msb = ndirect_msb.wrapping_sub(1);
            ndirect_msb;
        }
        ndirect_msb = ndirect_msb / 2 as libc::c_int as uint32_t;
        npostfix = npostfix.wrapping_add(1);
        npostfix;
    }
    if check_orig != 0 {
        let mut dist_cost_0: libc::c_double = 0.;
        ComputeDistanceCost(
            cmds,
            num_commands,
            &mut orig_params.dist,
            &mut orig_params.dist,
            &mut dist_cost_0,
        );
        if dist_cost_0 < best_dist_cost {
            (*params).dist = orig_params.dist;
        }
    }
    RecomputeDistancePrefixes(
        cmds,
        num_commands,
        &mut orig_params.dist,
        &mut (*params).dist,
    );
    BrotliSplitBlock(
        m,
        cmds,
        num_commands,
        ringbuffer,
        pos,
        mask,
        params,
        &mut (*mb).literal_split,
        &mut (*mb).command_split,
        &mut (*mb).distance_split,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    if (*params).disable_literal_context_modeling == 0 {
        literal_context_multiplier = ((1 as libc::c_int) << 6 as libc::c_int) as size_t;
        literal_context_modes = if (*mb).literal_split.num_types
            > 0 as libc::c_int as size_t
        {
            BrotliAllocate(
                m,
                ((*mb).literal_split.num_types)
                    .wrapping_mul(::core::mem::size_of::<ContextType>() as libc::c_ulong),
            ) as *mut ContextType
        } else {
            0 as *mut ContextType
        };
        if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
            return;
        }
        i = 0 as libc::c_int as size_t;
        while i < (*mb).literal_split.num_types {
            *literal_context_modes.offset(i as isize) = literal_context_mode;
            i = i.wrapping_add(1);
            i;
        }
    }
    literal_histograms_size = (*mb).literal_split.num_types * literal_context_multiplier;
    literal_histograms = if literal_histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            literal_histograms_size
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramLiteral>() as libc::c_ulong,
                ),
        ) as *mut HistogramLiteral
    } else {
        0 as *mut HistogramLiteral
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    ClearHistogramsLiteral(literal_histograms, literal_histograms_size);
    distance_histograms_size = (*mb).distance_split.num_types << 2 as libc::c_int;
    distance_histograms = if distance_histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            distance_histograms_size
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramDistance>() as libc::c_ulong,
                ),
        ) as *mut HistogramDistance
    } else {
        0 as *mut HistogramDistance
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    ClearHistogramsDistance(distance_histograms, distance_histograms_size);
    (*mb).command_histograms_size = (*mb).command_split.num_types;
    (*mb)
        .command_histograms = if (*mb).command_histograms_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).command_histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramCommand>() as libc::c_ulong,
                ),
        ) as *mut HistogramCommand
    } else {
        0 as *mut HistogramCommand
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    ClearHistogramsCommand((*mb).command_histograms, (*mb).command_histograms_size);
    BrotliBuildHistogramsWithContext(
        cmds,
        num_commands,
        &mut (*mb).literal_split,
        &mut (*mb).command_split,
        &mut (*mb).distance_split,
        ringbuffer,
        pos,
        mask,
        prev_byte,
        prev_byte2,
        literal_context_modes,
        literal_histograms,
        (*mb).command_histograms,
        distance_histograms,
    );
    BrotliFree(m, literal_context_modes as *mut libc::c_void);
    literal_context_modes = 0 as *mut ContextType;
    (*mb).literal_context_map_size = (*mb).literal_split.num_types << 6 as libc::c_int;
    (*mb)
        .literal_context_map = if (*mb).literal_context_map_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).literal_context_map_size)
                .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
        ) as *mut uint32_t
    } else {
        0 as *mut uint32_t
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    (*mb).literal_histograms_size = (*mb).literal_context_map_size;
    (*mb)
        .literal_histograms = if (*mb).literal_histograms_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).literal_histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramLiteral>() as libc::c_ulong,
                ),
        ) as *mut HistogramLiteral
    } else {
        0 as *mut HistogramLiteral
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    BrotliClusterHistogramsLiteral(
        m,
        literal_histograms,
        literal_histograms_size,
        kMaxNumberOfHistograms,
        (*mb).literal_histograms,
        &mut (*mb).literal_histograms_size,
        (*mb).literal_context_map,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    BrotliFree(m, literal_histograms as *mut libc::c_void);
    literal_histograms = 0 as *mut HistogramLiteral;
    if (*params).disable_literal_context_modeling != 0 {
        i = (*mb).literal_split.num_types;
        while i != 0 as libc::c_int as size_t {
            let mut j: size_t = 0 as libc::c_int as size_t;
            i = i.wrapping_sub(1);
            i;
            while j < ((1 as libc::c_int) << 6 as libc::c_int) as size_t {
                *((*mb).literal_context_map)
                    .offset(
                        (i << 6 as libc::c_int).wrapping_add(j) as isize,
                    ) = *((*mb).literal_context_map).offset(i as isize);
                j = j.wrapping_add(1);
                j;
            }
        }
    }
    (*mb).distance_context_map_size = (*mb).distance_split.num_types << 2 as libc::c_int;
    (*mb)
        .distance_context_map = if (*mb).distance_context_map_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).distance_context_map_size)
                .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
        ) as *mut uint32_t
    } else {
        0 as *mut uint32_t
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    (*mb).distance_histograms_size = (*mb).distance_context_map_size;
    (*mb)
        .distance_histograms = if (*mb).distance_histograms_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).distance_histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramDistance>() as libc::c_ulong,
                ),
        ) as *mut HistogramDistance
    } else {
        0 as *mut HistogramDistance
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    BrotliClusterHistogramsDistance(
        m,
        distance_histograms,
        (*mb).distance_context_map_size,
        kMaxNumberOfHistograms,
        (*mb).distance_histograms,
        &mut (*mb).distance_histograms_size,
        (*mb).distance_context_map,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    BrotliFree(m, distance_histograms as *mut libc::c_void);
    distance_histograms = 0 as *mut HistogramDistance;
}
unsafe extern "C" fn InitBlockSplitterLiteral(
    mut m: *mut MemoryManager,
    mut self_0: *mut BlockSplitterLiteral,
    mut alphabet_size: size_t,
    mut min_block_size: size_t,
    mut split_threshold: libc::c_double,
    mut num_symbols: size_t,
    mut split: *mut BlockSplit,
    mut histograms: *mut *mut HistogramLiteral,
    mut histograms_size: *mut size_t,
) {
    let mut max_num_blocks: size_t = (num_symbols / min_block_size)
        .wrapping_add(1 as libc::c_int as size_t);
    let mut max_num_types: size_t = brotli_min_size_t(
        max_num_blocks,
        (256 as libc::c_int + 1 as libc::c_int) as size_t,
    );
    (*self_0).alphabet_size_ = alphabet_size;
    (*self_0).min_block_size_ = min_block_size;
    (*self_0).split_threshold_ = split_threshold;
    (*self_0).num_blocks_ = 0 as libc::c_int as size_t;
    (*self_0).split_ = split;
    (*self_0).histograms_size_ = histograms_size;
    (*self_0).target_block_size_ = min_block_size;
    (*self_0).block_size_ = 0 as libc::c_int as size_t;
    (*self_0).curr_histogram_ix_ = 0 as libc::c_int as size_t;
    (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
    if (*split).types_alloc_size < max_num_blocks {
        let mut _new_size: size_t = if (*split).types_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).types_alloc_size
        };
        let mut new_array: *mut uint8_t = 0 as *mut uint8_t;
        while _new_size < max_num_blocks {
            _new_size = _new_size * 2 as libc::c_int as size_t;
        }
        new_array = if _new_size > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            ) as *mut uint8_t
        } else {
            0 as *mut uint8_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).types_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array as *mut libc::c_void,
                (*split).types as *const libc::c_void,
                ((*split).types_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).types as *mut libc::c_void);
        (*split).types = 0 as *mut uint8_t;
        (*split).types = new_array;
        (*split).types_alloc_size = _new_size;
    }
    if (*split).lengths_alloc_size < max_num_blocks {
        let mut _new_size_0: size_t = if (*split).lengths_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).lengths_alloc_size
        };
        let mut new_array_0: *mut uint32_t = 0 as *mut uint32_t;
        while _new_size_0 < max_num_blocks {
            _new_size_0 = _new_size_0 * 2 as libc::c_int as size_t;
        }
        new_array_0 = if _new_size_0 > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size_0
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            ) as *mut uint32_t
        } else {
            0 as *mut uint32_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).lengths_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array_0 as *mut libc::c_void,
                (*split).lengths as *const libc::c_void,
                ((*split).lengths_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).lengths as *mut libc::c_void);
        (*split).lengths = 0 as *mut uint32_t;
        (*split).lengths = new_array_0;
        (*split).lengths_alloc_size = _new_size_0;
    }
    if 0 as libc::c_int != 0 {
        return;
    }
    (*(*self_0).split_).num_blocks = max_num_blocks;
    *histograms_size = max_num_types;
    *histograms = if *histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            (*histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramLiteral>() as libc::c_ulong,
                ),
        ) as *mut HistogramLiteral
    } else {
        0 as *mut HistogramLiteral
    };
    (*self_0).histograms_ = *histograms;
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    HistogramClearLiteral(
        &mut *((*self_0).histograms_).offset(0 as libc::c_int as isize),
    );
    (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = 0 as libc::c_int as size_t;
    (*self_0)
        .last_histogram_ix_[0 as libc::c_int
        as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
}
unsafe extern "C" fn BlockSplitterFinishBlockLiteral(
    mut self_0: *mut BlockSplitterLiteral,
    mut is_final: libc::c_int,
) {
    let mut split: *mut BlockSplit = (*self_0).split_;
    let mut last_entropy: *mut libc::c_double = ((*self_0).last_entropy_).as_mut_ptr();
    let mut histograms: *mut HistogramLiteral = (*self_0).histograms_;
    (*self_0)
        .block_size_ = brotli_max_size_t(
        (*self_0).block_size_,
        (*self_0).min_block_size_,
    );
    if (*self_0).num_blocks_ == 0 as libc::c_int as size_t {
        *((*split).lengths)
            .offset(0 as libc::c_int as isize) = (*self_0).block_size_ as uint32_t;
        *((*split).types)
            .offset(0 as libc::c_int as isize) = 0 as libc::c_int as uint8_t;
        *last_entropy
            .offset(
                0 as libc::c_int as isize,
            ) = BitsEntropy(
            ((*histograms.offset(0 as libc::c_int as isize)).data_).as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        *last_entropy
            .offset(
                1 as libc::c_int as isize,
            ) = *last_entropy.offset(0 as libc::c_int as isize);
        (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
        (*self_0).num_blocks_;
        (*split).num_types = ((*split).num_types).wrapping_add(1);
        (*split).num_types;
        (*self_0).curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
        (*self_0).curr_histogram_ix_;
        if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
            HistogramClearLiteral(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
        }
        (*self_0).block_size_ = 0 as libc::c_int as size_t;
    } else if (*self_0).block_size_ > 0 as libc::c_int as size_t {
        let mut entropy: libc::c_double = BitsEntropy(
            ((*histograms.offset((*self_0).curr_histogram_ix_ as isize)).data_)
                .as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        let mut combined_histo: [HistogramLiteral; 2] = [HistogramLiteral {
            data_: [0; 256],
            total_count_: 0,
            bit_cost_: 0.,
        }; 2];
        let mut combined_entropy: [libc::c_double; 2] = [0.; 2];
        let mut diff: [libc::c_double; 2] = [0.; 2];
        let mut j: size_t = 0;
        j = 0 as libc::c_int as size_t;
        while j < 2 as libc::c_int as size_t {
            let mut last_histogram_ix: size_t = (*self_0).last_histogram_ix_[j as usize];
            combined_histo[j
                as usize] = *histograms.offset((*self_0).curr_histogram_ix_ as isize);
            HistogramAddHistogramLiteral(
                &mut *combined_histo.as_mut_ptr().offset(j as isize),
                &mut *histograms.offset(last_histogram_ix as isize),
            );
            combined_entropy[j
                as usize] = BitsEntropy(
                &mut *((*combined_histo.as_mut_ptr().offset(j as isize)).data_)
                    .as_mut_ptr()
                    .offset(0 as libc::c_int as isize),
                (*self_0).alphabet_size_,
            );
            diff[j
                as usize] = combined_entropy[j as usize] - entropy
                - *last_entropy.offset(j as isize);
            j = j.wrapping_add(1);
            j;
        }
        if (*split).num_types < 256 as libc::c_int as size_t
            && diff[0 as libc::c_int as usize] > (*self_0).split_threshold_
            && diff[1 as libc::c_int as usize] > (*self_0).split_threshold_
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset((*self_0).num_blocks_ as isize) = (*split).num_types as uint8_t;
            (*self_0)
                .last_histogram_ix_[1 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*split).num_types as uint8_t as size_t;
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy.offset(0 as libc::c_int as isize) = entropy;
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*split).num_types = ((*split).num_types).wrapping_add(1);
            (*split).num_types;
            (*self_0)
                .curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
            (*self_0).curr_histogram_ix_;
            if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
                HistogramClearLiteral(
                    &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
                );
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else if diff[1 as libc::c_int as usize]
            < diff[0 as libc::c_int as usize] - 20.0f64
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = *((*split).types)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(2 as libc::c_int as size_t)
                        as isize,
                );
            let mut __brotli_swap_tmp: size_t = (*self_0)
                .last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
            (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = __brotli_swap_tmp;
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[1 as libc::c_int as usize];
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[1 as libc::c_int as usize];
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearLiteral(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else {
            let ref mut fresh2 = *((*split).lengths)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(1 as libc::c_int as size_t)
                        as isize,
                );
            *fresh2 = (*fresh2).wrapping_add((*self_0).block_size_ as uint32_t);
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[0 as libc::c_int as usize];
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[0 as libc::c_int as usize];
            if (*split).num_types == 1 as libc::c_int as size_t {
                *last_entropy
                    .offset(
                        1 as libc::c_int as isize,
                    ) = *last_entropy.offset(0 as libc::c_int as isize);
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearLiteral(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = ((*self_0).merge_last_count_).wrapping_add(1);
            if (*self_0).merge_last_count_ > 1 as libc::c_int as size_t {
                (*self_0)
                    .target_block_size_ = ((*self_0).target_block_size_)
                    .wrapping_add((*self_0).min_block_size_);
            }
        }
    }
    if is_final != 0 {
        *(*self_0).histograms_size_ = (*split).num_types;
        (*split).num_blocks = (*self_0).num_blocks_;
    }
}
unsafe extern "C" fn BlockSplitterAddSymbolLiteral(
    mut self_0: *mut BlockSplitterLiteral,
    mut symbol: size_t,
) {
    HistogramAddLiteral(
        &mut *((*self_0).histograms_).offset((*self_0).curr_histogram_ix_ as isize),
        symbol,
    );
    (*self_0).block_size_ = ((*self_0).block_size_).wrapping_add(1);
    (*self_0).block_size_;
    if (*self_0).block_size_ == (*self_0).target_block_size_ {
        BlockSplitterFinishBlockLiteral(self_0, 0 as libc::c_int);
    }
}
unsafe extern "C" fn InitBlockSplitterCommand(
    mut m: *mut MemoryManager,
    mut self_0: *mut BlockSplitterCommand,
    mut alphabet_size: size_t,
    mut min_block_size: size_t,
    mut split_threshold: libc::c_double,
    mut num_symbols: size_t,
    mut split: *mut BlockSplit,
    mut histograms: *mut *mut HistogramCommand,
    mut histograms_size: *mut size_t,
) {
    let mut max_num_blocks: size_t = (num_symbols / min_block_size)
        .wrapping_add(1 as libc::c_int as size_t);
    let mut max_num_types: size_t = brotli_min_size_t(
        max_num_blocks,
        (256 as libc::c_int + 1 as libc::c_int) as size_t,
    );
    (*self_0).alphabet_size_ = alphabet_size;
    (*self_0).min_block_size_ = min_block_size;
    (*self_0).split_threshold_ = split_threshold;
    (*self_0).num_blocks_ = 0 as libc::c_int as size_t;
    (*self_0).split_ = split;
    (*self_0).histograms_size_ = histograms_size;
    (*self_0).target_block_size_ = min_block_size;
    (*self_0).block_size_ = 0 as libc::c_int as size_t;
    (*self_0).curr_histogram_ix_ = 0 as libc::c_int as size_t;
    (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
    if (*split).types_alloc_size < max_num_blocks {
        let mut _new_size: size_t = if (*split).types_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).types_alloc_size
        };
        let mut new_array: *mut uint8_t = 0 as *mut uint8_t;
        while _new_size < max_num_blocks {
            _new_size = _new_size * 2 as libc::c_int as size_t;
        }
        new_array = if _new_size > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            ) as *mut uint8_t
        } else {
            0 as *mut uint8_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).types_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array as *mut libc::c_void,
                (*split).types as *const libc::c_void,
                ((*split).types_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).types as *mut libc::c_void);
        (*split).types = 0 as *mut uint8_t;
        (*split).types = new_array;
        (*split).types_alloc_size = _new_size;
    }
    if (*split).lengths_alloc_size < max_num_blocks {
        let mut _new_size_0: size_t = if (*split).lengths_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).lengths_alloc_size
        };
        let mut new_array_0: *mut uint32_t = 0 as *mut uint32_t;
        while _new_size_0 < max_num_blocks {
            _new_size_0 = _new_size_0 * 2 as libc::c_int as size_t;
        }
        new_array_0 = if _new_size_0 > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size_0
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            ) as *mut uint32_t
        } else {
            0 as *mut uint32_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).lengths_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array_0 as *mut libc::c_void,
                (*split).lengths as *const libc::c_void,
                ((*split).lengths_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).lengths as *mut libc::c_void);
        (*split).lengths = 0 as *mut uint32_t;
        (*split).lengths = new_array_0;
        (*split).lengths_alloc_size = _new_size_0;
    }
    if 0 as libc::c_int != 0 {
        return;
    }
    (*(*self_0).split_).num_blocks = max_num_blocks;
    *histograms_size = max_num_types;
    *histograms = if *histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            (*histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramCommand>() as libc::c_ulong,
                ),
        ) as *mut HistogramCommand
    } else {
        0 as *mut HistogramCommand
    };
    (*self_0).histograms_ = *histograms;
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    HistogramClearCommand(
        &mut *((*self_0).histograms_).offset(0 as libc::c_int as isize),
    );
    (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = 0 as libc::c_int as size_t;
    (*self_0)
        .last_histogram_ix_[0 as libc::c_int
        as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
}
unsafe extern "C" fn BlockSplitterFinishBlockCommand(
    mut self_0: *mut BlockSplitterCommand,
    mut is_final: libc::c_int,
) {
    let mut split: *mut BlockSplit = (*self_0).split_;
    let mut last_entropy: *mut libc::c_double = ((*self_0).last_entropy_).as_mut_ptr();
    let mut histograms: *mut HistogramCommand = (*self_0).histograms_;
    (*self_0)
        .block_size_ = brotli_max_size_t(
        (*self_0).block_size_,
        (*self_0).min_block_size_,
    );
    if (*self_0).num_blocks_ == 0 as libc::c_int as size_t {
        *((*split).lengths)
            .offset(0 as libc::c_int as isize) = (*self_0).block_size_ as uint32_t;
        *((*split).types)
            .offset(0 as libc::c_int as isize) = 0 as libc::c_int as uint8_t;
        *last_entropy
            .offset(
                0 as libc::c_int as isize,
            ) = BitsEntropy(
            ((*histograms.offset(0 as libc::c_int as isize)).data_).as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        *last_entropy
            .offset(
                1 as libc::c_int as isize,
            ) = *last_entropy.offset(0 as libc::c_int as isize);
        (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
        (*self_0).num_blocks_;
        (*split).num_types = ((*split).num_types).wrapping_add(1);
        (*split).num_types;
        (*self_0).curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
        (*self_0).curr_histogram_ix_;
        if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
            HistogramClearCommand(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
        }
        (*self_0).block_size_ = 0 as libc::c_int as size_t;
    } else if (*self_0).block_size_ > 0 as libc::c_int as size_t {
        let mut entropy: libc::c_double = BitsEntropy(
            ((*histograms.offset((*self_0).curr_histogram_ix_ as isize)).data_)
                .as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        let mut combined_histo: [HistogramCommand; 2] = [HistogramCommand {
            data_: [0; 704],
            total_count_: 0,
            bit_cost_: 0.,
        }; 2];
        let mut combined_entropy: [libc::c_double; 2] = [0.; 2];
        let mut diff: [libc::c_double; 2] = [0.; 2];
        let mut j: size_t = 0;
        j = 0 as libc::c_int as size_t;
        while j < 2 as libc::c_int as size_t {
            let mut last_histogram_ix: size_t = (*self_0).last_histogram_ix_[j as usize];
            combined_histo[j
                as usize] = *histograms.offset((*self_0).curr_histogram_ix_ as isize);
            HistogramAddHistogramCommand(
                &mut *combined_histo.as_mut_ptr().offset(j as isize),
                &mut *histograms.offset(last_histogram_ix as isize),
            );
            combined_entropy[j
                as usize] = BitsEntropy(
                &mut *((*combined_histo.as_mut_ptr().offset(j as isize)).data_)
                    .as_mut_ptr()
                    .offset(0 as libc::c_int as isize),
                (*self_0).alphabet_size_,
            );
            diff[j
                as usize] = combined_entropy[j as usize] - entropy
                - *last_entropy.offset(j as isize);
            j = j.wrapping_add(1);
            j;
        }
        if (*split).num_types < 256 as libc::c_int as size_t
            && diff[0 as libc::c_int as usize] > (*self_0).split_threshold_
            && diff[1 as libc::c_int as usize] > (*self_0).split_threshold_
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset((*self_0).num_blocks_ as isize) = (*split).num_types as uint8_t;
            (*self_0)
                .last_histogram_ix_[1 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*split).num_types as uint8_t as size_t;
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy.offset(0 as libc::c_int as isize) = entropy;
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*split).num_types = ((*split).num_types).wrapping_add(1);
            (*split).num_types;
            (*self_0)
                .curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
            (*self_0).curr_histogram_ix_;
            if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
                HistogramClearCommand(
                    &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
                );
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else if diff[1 as libc::c_int as usize]
            < diff[0 as libc::c_int as usize] - 20.0f64
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = *((*split).types)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(2 as libc::c_int as size_t)
                        as isize,
                );
            let mut __brotli_swap_tmp: size_t = (*self_0)
                .last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
            (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = __brotli_swap_tmp;
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[1 as libc::c_int as usize];
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[1 as libc::c_int as usize];
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearCommand(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else {
            let ref mut fresh3 = *((*split).lengths)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(1 as libc::c_int as size_t)
                        as isize,
                );
            *fresh3 = (*fresh3).wrapping_add((*self_0).block_size_ as uint32_t);
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[0 as libc::c_int as usize];
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[0 as libc::c_int as usize];
            if (*split).num_types == 1 as libc::c_int as size_t {
                *last_entropy
                    .offset(
                        1 as libc::c_int as isize,
                    ) = *last_entropy.offset(0 as libc::c_int as isize);
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearCommand(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = ((*self_0).merge_last_count_).wrapping_add(1);
            if (*self_0).merge_last_count_ > 1 as libc::c_int as size_t {
                (*self_0)
                    .target_block_size_ = ((*self_0).target_block_size_)
                    .wrapping_add((*self_0).min_block_size_);
            }
        }
    }
    if is_final != 0 {
        *(*self_0).histograms_size_ = (*split).num_types;
        (*split).num_blocks = (*self_0).num_blocks_;
    }
}
unsafe extern "C" fn BlockSplitterAddSymbolCommand(
    mut self_0: *mut BlockSplitterCommand,
    mut symbol: size_t,
) {
    HistogramAddCommand(
        &mut *((*self_0).histograms_).offset((*self_0).curr_histogram_ix_ as isize),
        symbol,
    );
    (*self_0).block_size_ = ((*self_0).block_size_).wrapping_add(1);
    (*self_0).block_size_;
    if (*self_0).block_size_ == (*self_0).target_block_size_ {
        BlockSplitterFinishBlockCommand(self_0, 0 as libc::c_int);
    }
}
unsafe extern "C" fn InitBlockSplitterDistance(
    mut m: *mut MemoryManager,
    mut self_0: *mut BlockSplitterDistance,
    mut alphabet_size: size_t,
    mut min_block_size: size_t,
    mut split_threshold: libc::c_double,
    mut num_symbols: size_t,
    mut split: *mut BlockSplit,
    mut histograms: *mut *mut HistogramDistance,
    mut histograms_size: *mut size_t,
) {
    let mut max_num_blocks: size_t = (num_symbols / min_block_size)
        .wrapping_add(1 as libc::c_int as size_t);
    let mut max_num_types: size_t = brotli_min_size_t(
        max_num_blocks,
        (256 as libc::c_int + 1 as libc::c_int) as size_t,
    );
    (*self_0).alphabet_size_ = alphabet_size;
    (*self_0).min_block_size_ = min_block_size;
    (*self_0).split_threshold_ = split_threshold;
    (*self_0).num_blocks_ = 0 as libc::c_int as size_t;
    (*self_0).split_ = split;
    (*self_0).histograms_size_ = histograms_size;
    (*self_0).target_block_size_ = min_block_size;
    (*self_0).block_size_ = 0 as libc::c_int as size_t;
    (*self_0).curr_histogram_ix_ = 0 as libc::c_int as size_t;
    (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
    if (*split).types_alloc_size < max_num_blocks {
        let mut _new_size: size_t = if (*split).types_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).types_alloc_size
        };
        let mut new_array: *mut uint8_t = 0 as *mut uint8_t;
        while _new_size < max_num_blocks {
            _new_size = _new_size * 2 as libc::c_int as size_t;
        }
        new_array = if _new_size > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            ) as *mut uint8_t
        } else {
            0 as *mut uint8_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).types_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array as *mut libc::c_void,
                (*split).types as *const libc::c_void,
                ((*split).types_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).types as *mut libc::c_void);
        (*split).types = 0 as *mut uint8_t;
        (*split).types = new_array;
        (*split).types_alloc_size = _new_size;
    }
    if (*split).lengths_alloc_size < max_num_blocks {
        let mut _new_size_0: size_t = if (*split).lengths_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).lengths_alloc_size
        };
        let mut new_array_0: *mut uint32_t = 0 as *mut uint32_t;
        while _new_size_0 < max_num_blocks {
            _new_size_0 = _new_size_0 * 2 as libc::c_int as size_t;
        }
        new_array_0 = if _new_size_0 > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size_0
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            ) as *mut uint32_t
        } else {
            0 as *mut uint32_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).lengths_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array_0 as *mut libc::c_void,
                (*split).lengths as *const libc::c_void,
                ((*split).lengths_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).lengths as *mut libc::c_void);
        (*split).lengths = 0 as *mut uint32_t;
        (*split).lengths = new_array_0;
        (*split).lengths_alloc_size = _new_size_0;
    }
    if 0 as libc::c_int != 0 {
        return;
    }
    (*(*self_0).split_).num_blocks = max_num_blocks;
    *histograms_size = max_num_types;
    *histograms = if *histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            (*histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramDistance>() as libc::c_ulong,
                ),
        ) as *mut HistogramDistance
    } else {
        0 as *mut HistogramDistance
    };
    (*self_0).histograms_ = *histograms;
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    HistogramClearDistance(
        &mut *((*self_0).histograms_).offset(0 as libc::c_int as isize),
    );
    (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = 0 as libc::c_int as size_t;
    (*self_0)
        .last_histogram_ix_[0 as libc::c_int
        as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
}
unsafe extern "C" fn BlockSplitterFinishBlockDistance(
    mut self_0: *mut BlockSplitterDistance,
    mut is_final: libc::c_int,
) {
    let mut split: *mut BlockSplit = (*self_0).split_;
    let mut last_entropy: *mut libc::c_double = ((*self_0).last_entropy_).as_mut_ptr();
    let mut histograms: *mut HistogramDistance = (*self_0).histograms_;
    (*self_0)
        .block_size_ = brotli_max_size_t(
        (*self_0).block_size_,
        (*self_0).min_block_size_,
    );
    if (*self_0).num_blocks_ == 0 as libc::c_int as size_t {
        *((*split).lengths)
            .offset(0 as libc::c_int as isize) = (*self_0).block_size_ as uint32_t;
        *((*split).types)
            .offset(0 as libc::c_int as isize) = 0 as libc::c_int as uint8_t;
        *last_entropy
            .offset(
                0 as libc::c_int as isize,
            ) = BitsEntropy(
            ((*histograms.offset(0 as libc::c_int as isize)).data_).as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        *last_entropy
            .offset(
                1 as libc::c_int as isize,
            ) = *last_entropy.offset(0 as libc::c_int as isize);
        (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
        (*self_0).num_blocks_;
        (*split).num_types = ((*split).num_types).wrapping_add(1);
        (*split).num_types;
        (*self_0).curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
        (*self_0).curr_histogram_ix_;
        if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
            HistogramClearDistance(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
        }
        (*self_0).block_size_ = 0 as libc::c_int as size_t;
    } else if (*self_0).block_size_ > 0 as libc::c_int as size_t {
        let mut entropy: libc::c_double = BitsEntropy(
            ((*histograms.offset((*self_0).curr_histogram_ix_ as isize)).data_)
                .as_mut_ptr(),
            (*self_0).alphabet_size_,
        );
        let mut combined_histo: [HistogramDistance; 2] = [HistogramDistance {
            data_: [0; 544],
            total_count_: 0,
            bit_cost_: 0.,
        }; 2];
        let mut combined_entropy: [libc::c_double; 2] = [0.; 2];
        let mut diff: [libc::c_double; 2] = [0.; 2];
        let mut j: size_t = 0;
        j = 0 as libc::c_int as size_t;
        while j < 2 as libc::c_int as size_t {
            let mut last_histogram_ix: size_t = (*self_0).last_histogram_ix_[j as usize];
            combined_histo[j
                as usize] = *histograms.offset((*self_0).curr_histogram_ix_ as isize);
            HistogramAddHistogramDistance(
                &mut *combined_histo.as_mut_ptr().offset(j as isize),
                &mut *histograms.offset(last_histogram_ix as isize),
            );
            combined_entropy[j
                as usize] = BitsEntropy(
                &mut *((*combined_histo.as_mut_ptr().offset(j as isize)).data_)
                    .as_mut_ptr()
                    .offset(0 as libc::c_int as isize),
                (*self_0).alphabet_size_,
            );
            diff[j
                as usize] = combined_entropy[j as usize] - entropy
                - *last_entropy.offset(j as isize);
            j = j.wrapping_add(1);
            j;
        }
        if (*split).num_types < 256 as libc::c_int as size_t
            && diff[0 as libc::c_int as usize] > (*self_0).split_threshold_
            && diff[1 as libc::c_int as usize] > (*self_0).split_threshold_
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset((*self_0).num_blocks_ as isize) = (*split).num_types as uint8_t;
            (*self_0)
                .last_histogram_ix_[1 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*split).num_types as uint8_t as size_t;
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy.offset(0 as libc::c_int as isize) = entropy;
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*split).num_types = ((*split).num_types).wrapping_add(1);
            (*split).num_types;
            (*self_0)
                .curr_histogram_ix_ = ((*self_0).curr_histogram_ix_).wrapping_add(1);
            (*self_0).curr_histogram_ix_;
            if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
                HistogramClearDistance(
                    &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
                );
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else if diff[1 as libc::c_int as usize]
            < diff[0 as libc::c_int as usize] - 20.0f64
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = *((*split).types)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(2 as libc::c_int as size_t)
                        as isize,
                );
            let mut __brotli_swap_tmp: size_t = (*self_0)
                .last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
            (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = __brotli_swap_tmp;
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[1 as libc::c_int as usize];
            *last_entropy
                .offset(
                    1 as libc::c_int as isize,
                ) = *last_entropy.offset(0 as libc::c_int as isize);
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[1 as libc::c_int as usize];
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearDistance(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else {
            let ref mut fresh4 = *((*split).lengths)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(1 as libc::c_int as size_t)
                        as isize,
                );
            *fresh4 = (*fresh4).wrapping_add((*self_0).block_size_ as uint32_t);
            *histograms
                .offset(
                    (*self_0).last_histogram_ix_[0 as libc::c_int as usize] as isize,
                ) = combined_histo[0 as libc::c_int as usize];
            *last_entropy
                .offset(
                    0 as libc::c_int as isize,
                ) = combined_entropy[0 as libc::c_int as usize];
            if (*split).num_types == 1 as libc::c_int as size_t {
                *last_entropy
                    .offset(
                        1 as libc::c_int as isize,
                    ) = *last_entropy.offset(0 as libc::c_int as isize);
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            HistogramClearDistance(
                &mut *histograms.offset((*self_0).curr_histogram_ix_ as isize),
            );
            (*self_0).merge_last_count_ = ((*self_0).merge_last_count_).wrapping_add(1);
            if (*self_0).merge_last_count_ > 1 as libc::c_int as size_t {
                (*self_0)
                    .target_block_size_ = ((*self_0).target_block_size_)
                    .wrapping_add((*self_0).min_block_size_);
            }
        }
    }
    if is_final != 0 {
        *(*self_0).histograms_size_ = (*split).num_types;
        (*split).num_blocks = (*self_0).num_blocks_;
    }
}
unsafe extern "C" fn BlockSplitterAddSymbolDistance(
    mut self_0: *mut BlockSplitterDistance,
    mut symbol: size_t,
) {
    HistogramAddDistance(
        &mut *((*self_0).histograms_).offset((*self_0).curr_histogram_ix_ as isize),
        symbol,
    );
    (*self_0).block_size_ = ((*self_0).block_size_).wrapping_add(1);
    (*self_0).block_size_;
    if (*self_0).block_size_ == (*self_0).target_block_size_ {
        BlockSplitterFinishBlockDistance(self_0, 0 as libc::c_int);
    }
}
unsafe extern "C" fn InitContextBlockSplitter(
    mut m: *mut MemoryManager,
    mut self_0: *mut ContextBlockSplitter,
    mut alphabet_size: size_t,
    mut num_contexts: size_t,
    mut min_block_size: size_t,
    mut split_threshold: libc::c_double,
    mut num_symbols: size_t,
    mut split: *mut BlockSplit,
    mut histograms: *mut *mut HistogramLiteral,
    mut histograms_size: *mut size_t,
) {
    let mut max_num_blocks: size_t = (num_symbols / min_block_size)
        .wrapping_add(1 as libc::c_int as size_t);
    let mut max_num_types: size_t = 0;
    (*self_0).alphabet_size_ = alphabet_size;
    (*self_0).num_contexts_ = num_contexts;
    (*self_0).max_block_types_ = 256 as libc::c_int as size_t / num_contexts;
    (*self_0).min_block_size_ = min_block_size;
    (*self_0).split_threshold_ = split_threshold;
    (*self_0).num_blocks_ = 0 as libc::c_int as size_t;
    (*self_0).split_ = split;
    (*self_0).histograms_size_ = histograms_size;
    (*self_0).target_block_size_ = min_block_size;
    (*self_0).block_size_ = 0 as libc::c_int as size_t;
    (*self_0).curr_histogram_ix_ = 0 as libc::c_int as size_t;
    (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
    max_num_types = brotli_min_size_t(
        max_num_blocks,
        ((*self_0).max_block_types_).wrapping_add(1 as libc::c_int as size_t),
    );
    if (*split).types_alloc_size < max_num_blocks {
        let mut _new_size: size_t = if (*split).types_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).types_alloc_size
        };
        let mut new_array: *mut uint8_t = 0 as *mut uint8_t;
        while _new_size < max_num_blocks {
            _new_size = _new_size * 2 as libc::c_int as size_t;
        }
        new_array = if _new_size > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            ) as *mut uint8_t
        } else {
            0 as *mut uint8_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).types_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array as *mut libc::c_void,
                (*split).types as *const libc::c_void,
                ((*split).types_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint8_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).types as *mut libc::c_void);
        (*split).types = 0 as *mut uint8_t;
        (*split).types = new_array;
        (*split).types_alloc_size = _new_size;
    }
    if (*split).lengths_alloc_size < max_num_blocks {
        let mut _new_size_0: size_t = if (*split).lengths_alloc_size
            == 0 as libc::c_int as size_t
        {
            max_num_blocks
        } else {
            (*split).lengths_alloc_size
        };
        let mut new_array_0: *mut uint32_t = 0 as *mut uint32_t;
        while _new_size_0 < max_num_blocks {
            _new_size_0 = _new_size_0 * 2 as libc::c_int as size_t;
        }
        new_array_0 = if _new_size_0 > 0 as libc::c_int as size_t {
            BrotliAllocate(
                m,
                _new_size_0
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            ) as *mut uint32_t
        } else {
            0 as *mut uint32_t
        };
        if 0 as libc::c_int == 0 && 0 as libc::c_int == 0
            && (*split).lengths_alloc_size != 0 as libc::c_int as size_t
        {
            memcpy(
                new_array_0 as *mut libc::c_void,
                (*split).lengths as *const libc::c_void,
                ((*split).lengths_alloc_size)
                    .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
            );
        }
        BrotliFree(m, (*split).lengths as *mut libc::c_void);
        (*split).lengths = 0 as *mut uint32_t;
        (*split).lengths = new_array_0;
        (*split).lengths_alloc_size = _new_size_0;
    }
    if 0 as libc::c_int != 0 {
        return;
    }
    (*split).num_blocks = max_num_blocks;
    if 0 as libc::c_int != 0 {
        return;
    }
    *histograms_size = max_num_types * num_contexts;
    *histograms = if *histograms_size > 0 as libc::c_int as size_t {
        BrotliAllocate(
            m,
            (*histograms_size)
                .wrapping_mul(
                    ::core::mem::size_of::<HistogramLiteral>() as libc::c_ulong,
                ),
        ) as *mut HistogramLiteral
    } else {
        0 as *mut HistogramLiteral
    };
    (*self_0).histograms_ = *histograms;
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    ClearHistogramsLiteral(
        &mut *((*self_0).histograms_).offset(0 as libc::c_int as isize),
        num_contexts,
    );
    (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = 0 as libc::c_int as size_t;
    (*self_0)
        .last_histogram_ix_[0 as libc::c_int
        as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
}
unsafe extern "C" fn ContextBlockSplitterFinishBlock(
    mut self_0: *mut ContextBlockSplitter,
    mut m: *mut MemoryManager,
    mut is_final: libc::c_int,
) {
    let mut split: *mut BlockSplit = (*self_0).split_;
    let num_contexts: size_t = (*self_0).num_contexts_;
    let mut last_entropy: *mut libc::c_double = ((*self_0).last_entropy_).as_mut_ptr();
    let mut histograms: *mut HistogramLiteral = (*self_0).histograms_;
    if (*self_0).block_size_ < (*self_0).min_block_size_ {
        (*self_0).block_size_ = (*self_0).min_block_size_;
    }
    if (*self_0).num_blocks_ == 0 as libc::c_int as size_t {
        let mut i: size_t = 0;
        *((*split).lengths)
            .offset(0 as libc::c_int as isize) = (*self_0).block_size_ as uint32_t;
        *((*split).types)
            .offset(0 as libc::c_int as isize) = 0 as libc::c_int as uint8_t;
        i = 0 as libc::c_int as size_t;
        while i < num_contexts {
            *last_entropy
                .offset(
                    i as isize,
                ) = BitsEntropy(
                ((*histograms.offset(i as isize)).data_).as_mut_ptr(),
                (*self_0).alphabet_size_,
            );
            *last_entropy
                .offset(
                    num_contexts.wrapping_add(i) as isize,
                ) = *last_entropy.offset(i as isize);
            i = i.wrapping_add(1);
            i;
        }
        (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
        (*self_0).num_blocks_;
        (*split).num_types = ((*split).num_types).wrapping_add(1);
        (*split).num_types;
        (*self_0)
            .curr_histogram_ix_ = ((*self_0).curr_histogram_ix_)
            .wrapping_add(num_contexts);
        if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
            ClearHistogramsLiteral(
                &mut *((*self_0).histograms_)
                    .offset((*self_0).curr_histogram_ix_ as isize),
                (*self_0).num_contexts_,
            );
        }
        (*self_0).block_size_ = 0 as libc::c_int as size_t;
    } else if (*self_0).block_size_ > 0 as libc::c_int as size_t {
        let mut entropy: [libc::c_double; 13] = [0.; 13];
        let mut combined_histo: *mut HistogramLiteral = if 2 as libc::c_int as size_t
            * num_contexts > 0 as libc::c_int as size_t
        {
            BrotliAllocate(
                m,
                (2 as libc::c_int as size_t * num_contexts)
                    .wrapping_mul(
                        ::core::mem::size_of::<HistogramLiteral>() as libc::c_ulong,
                    ),
            ) as *mut HistogramLiteral
        } else {
            0 as *mut HistogramLiteral
        };
        let mut combined_entropy: [libc::c_double; 26] = [0.; 26];
        let mut diff: [libc::c_double; 2] = [0.0f64, 0.];
        let mut i_0: size_t = 0;
        if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
            return;
        }
        i_0 = 0 as libc::c_int as size_t;
        while i_0 < num_contexts {
            let mut curr_histo_ix: size_t = ((*self_0).curr_histogram_ix_)
                .wrapping_add(i_0);
            let mut j: size_t = 0;
            entropy[i_0
                as usize] = BitsEntropy(
                ((*histograms.offset(curr_histo_ix as isize)).data_).as_mut_ptr(),
                (*self_0).alphabet_size_,
            );
            j = 0 as libc::c_int as size_t;
            while j < 2 as libc::c_int as size_t {
                let mut jx: size_t = (j * num_contexts).wrapping_add(i_0);
                let mut last_histogram_ix: size_t = ((*self_0)
                    .last_histogram_ix_[j as usize])
                    .wrapping_add(i_0);
                *combined_histo
                    .offset(jx as isize) = *histograms.offset(curr_histo_ix as isize);
                HistogramAddHistogramLiteral(
                    &mut *combined_histo.offset(jx as isize),
                    &mut *histograms.offset(last_histogram_ix as isize),
                );
                combined_entropy[jx
                    as usize] = BitsEntropy(
                    &mut *((*combined_histo.offset(jx as isize)).data_)
                        .as_mut_ptr()
                        .offset(0 as libc::c_int as isize),
                    (*self_0).alphabet_size_,
                );
                diff[j as usize]
                    += combined_entropy[jx as usize] - entropy[i_0 as usize]
                        - *last_entropy.offset(jx as isize);
                j = j.wrapping_add(1);
                j;
            }
            i_0 = i_0.wrapping_add(1);
            i_0;
        }
        if (*split).num_types < (*self_0).max_block_types_
            && diff[0 as libc::c_int as usize] > (*self_0).split_threshold_
            && diff[1 as libc::c_int as usize] > (*self_0).split_threshold_
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset((*self_0).num_blocks_ as isize) = (*split).num_types as uint8_t;
            (*self_0)
                .last_histogram_ix_[1 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*split).num_types * num_contexts;
            i_0 = 0 as libc::c_int as size_t;
            while i_0 < num_contexts {
                *last_entropy
                    .offset(
                        num_contexts.wrapping_add(i_0) as isize,
                    ) = *last_entropy.offset(i_0 as isize);
                *last_entropy.offset(i_0 as isize) = entropy[i_0 as usize];
                i_0 = i_0.wrapping_add(1);
                i_0;
            }
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*split).num_types = ((*split).num_types).wrapping_add(1);
            (*split).num_types;
            (*self_0)
                .curr_histogram_ix_ = ((*self_0).curr_histogram_ix_)
                .wrapping_add(num_contexts);
            if (*self_0).curr_histogram_ix_ < *(*self_0).histograms_size_ {
                ClearHistogramsLiteral(
                    &mut *((*self_0).histograms_)
                        .offset((*self_0).curr_histogram_ix_ as isize),
                    (*self_0).num_contexts_,
                );
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else if diff[1 as libc::c_int as usize]
            < diff[0 as libc::c_int as usize] - 20.0f64
        {
            *((*split).lengths)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = (*self_0).block_size_ as uint32_t;
            *((*split).types)
                .offset(
                    (*self_0).num_blocks_ as isize,
                ) = *((*split).types)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(2 as libc::c_int as size_t)
                        as isize,
                );
            let mut __brotli_swap_tmp: size_t = (*self_0)
                .last_histogram_ix_[0 as libc::c_int as usize];
            (*self_0)
                .last_histogram_ix_[0 as libc::c_int
                as usize] = (*self_0).last_histogram_ix_[1 as libc::c_int as usize];
            (*self_0).last_histogram_ix_[1 as libc::c_int as usize] = __brotli_swap_tmp;
            i_0 = 0 as libc::c_int as size_t;
            while i_0 < num_contexts {
                *histograms
                    .offset(
                        ((*self_0).last_histogram_ix_[0 as libc::c_int as usize])
                            .wrapping_add(i_0) as isize,
                    ) = *combined_histo.offset(num_contexts.wrapping_add(i_0) as isize);
                *last_entropy
                    .offset(
                        num_contexts.wrapping_add(i_0) as isize,
                    ) = *last_entropy.offset(i_0 as isize);
                *last_entropy
                    .offset(
                        i_0 as isize,
                    ) = combined_entropy[num_contexts.wrapping_add(i_0) as usize];
                HistogramClearLiteral(
                    &mut *histograms
                        .offset(
                            ((*self_0).curr_histogram_ix_).wrapping_add(i_0) as isize,
                        ),
                );
                i_0 = i_0.wrapping_add(1);
                i_0;
            }
            (*self_0).num_blocks_ = ((*self_0).num_blocks_).wrapping_add(1);
            (*self_0).num_blocks_;
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = 0 as libc::c_int as size_t;
            (*self_0).target_block_size_ = (*self_0).min_block_size_;
        } else {
            let ref mut fresh5 = *((*split).lengths)
                .offset(
                    ((*self_0).num_blocks_).wrapping_sub(1 as libc::c_int as size_t)
                        as isize,
                );
            *fresh5 = (*fresh5).wrapping_add((*self_0).block_size_ as uint32_t);
            i_0 = 0 as libc::c_int as size_t;
            while i_0 < num_contexts {
                *histograms
                    .offset(
                        ((*self_0).last_histogram_ix_[0 as libc::c_int as usize])
                            .wrapping_add(i_0) as isize,
                    ) = *combined_histo.offset(i_0 as isize);
                *last_entropy.offset(i_0 as isize) = combined_entropy[i_0 as usize];
                if (*split).num_types == 1 as libc::c_int as size_t {
                    *last_entropy
                        .offset(
                            num_contexts.wrapping_add(i_0) as isize,
                        ) = *last_entropy.offset(i_0 as isize);
                }
                HistogramClearLiteral(
                    &mut *histograms
                        .offset(
                            ((*self_0).curr_histogram_ix_).wrapping_add(i_0) as isize,
                        ),
                );
                i_0 = i_0.wrapping_add(1);
                i_0;
            }
            (*self_0).block_size_ = 0 as libc::c_int as size_t;
            (*self_0).merge_last_count_ = ((*self_0).merge_last_count_).wrapping_add(1);
            if (*self_0).merge_last_count_ > 1 as libc::c_int as size_t {
                (*self_0)
                    .target_block_size_ = ((*self_0).target_block_size_)
                    .wrapping_add((*self_0).min_block_size_);
            }
        }
        BrotliFree(m, combined_histo as *mut libc::c_void);
        combined_histo = 0 as *mut HistogramLiteral;
    }
    if is_final != 0 {
        *(*self_0).histograms_size_ = (*split).num_types * num_contexts;
        (*split).num_blocks = (*self_0).num_blocks_;
    }
}
unsafe extern "C" fn ContextBlockSplitterAddSymbol(
    mut self_0: *mut ContextBlockSplitter,
    mut m: *mut MemoryManager,
    mut symbol: size_t,
    mut context: size_t,
) {
    HistogramAddLiteral(
        &mut *((*self_0).histograms_)
            .offset(((*self_0).curr_histogram_ix_).wrapping_add(context) as isize),
        symbol,
    );
    (*self_0).block_size_ = ((*self_0).block_size_).wrapping_add(1);
    (*self_0).block_size_;
    if (*self_0).block_size_ == (*self_0).target_block_size_ {
        ContextBlockSplitterFinishBlock(self_0, m, 0 as libc::c_int);
        if 0 as libc::c_int != 0 {
            return;
        }
    }
}
unsafe extern "C" fn MapStaticContexts(
    mut m: *mut MemoryManager,
    mut num_contexts: size_t,
    mut static_context_map: *const uint32_t,
    mut mb: *mut MetaBlockSplit,
) {
    let mut i: size_t = 0;
    (*mb).literal_context_map_size = (*mb).literal_split.num_types << 6 as libc::c_int;
    (*mb)
        .literal_context_map = if (*mb).literal_context_map_size
        > 0 as libc::c_int as size_t
    {
        BrotliAllocate(
            m,
            ((*mb).literal_context_map_size)
                .wrapping_mul(::core::mem::size_of::<uint32_t>() as libc::c_ulong),
        ) as *mut uint32_t
    } else {
        0 as *mut uint32_t
    };
    if 0 as libc::c_int != 0 || 0 as libc::c_int != 0 {
        return;
    }
    i = 0 as libc::c_int as size_t;
    while i < (*mb).literal_split.num_types {
        let mut offset: uint32_t = (i * num_contexts) as uint32_t;
        let mut j: size_t = 0;
        j = 0 as libc::c_int as size_t;
        while j < ((1 as libc::c_uint) << 6 as libc::c_int) as size_t {
            *((*mb).literal_context_map)
                .offset(
                    (i << 6 as libc::c_int).wrapping_add(j) as isize,
                ) = offset.wrapping_add(*static_context_map.offset(j as isize));
            j = j.wrapping_add(1);
            j;
        }
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn BrotliBuildMetaBlockGreedyInternal(
    mut m: *mut MemoryManager,
    mut ringbuffer: *const uint8_t,
    mut pos: size_t,
    mut mask: size_t,
    mut prev_byte: uint8_t,
    mut prev_byte2: uint8_t,
    mut literal_context_lut: ContextLut,
    num_contexts: size_t,
    mut static_context_map: *const uint32_t,
    mut commands: *const Command,
    mut n_commands: size_t,
    mut mb: *mut MetaBlockSplit,
) {
    let mut lit_blocks: C2RustUnnamed = C2RustUnnamed {
        plain: BlockSplitterLiteral {
            alphabet_size_: 0,
            min_block_size_: 0,
            split_threshold_: 0.,
            num_blocks_: 0,
            split_: 0 as *mut BlockSplit,
            histograms_: 0 as *mut HistogramLiteral,
            histograms_size_: 0 as *mut size_t,
            target_block_size_: 0,
            block_size_: 0,
            curr_histogram_ix_: 0,
            last_histogram_ix_: [0; 2],
            last_entropy_: [0.; 2],
            merge_last_count_: 0,
        },
    };
    let mut cmd_blocks: BlockSplitterCommand = BlockSplitterCommand {
        alphabet_size_: 0,
        min_block_size_: 0,
        split_threshold_: 0.,
        num_blocks_: 0,
        split_: 0 as *mut BlockSplit,
        histograms_: 0 as *mut HistogramCommand,
        histograms_size_: 0 as *mut size_t,
        target_block_size_: 0,
        block_size_: 0,
        curr_histogram_ix_: 0,
        last_histogram_ix_: [0; 2],
        last_entropy_: [0.; 2],
        merge_last_count_: 0,
    };
    let mut dist_blocks: BlockSplitterDistance = BlockSplitterDistance {
        alphabet_size_: 0,
        min_block_size_: 0,
        split_threshold_: 0.,
        num_blocks_: 0,
        split_: 0 as *mut BlockSplit,
        histograms_: 0 as *mut HistogramDistance,
        histograms_size_: 0 as *mut size_t,
        target_block_size_: 0,
        block_size_: 0,
        curr_histogram_ix_: 0,
        last_histogram_ix_: [0; 2],
        last_entropy_: [0.; 2],
        merge_last_count_: 0,
    };
    let mut num_literals: size_t = 0 as libc::c_int as size_t;
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < n_commands {
        num_literals = num_literals
            .wrapping_add((*commands.offset(i as isize)).insert_len_ as size_t);
        i = i.wrapping_add(1);
        i;
    }
    if num_contexts == 1 as libc::c_int as size_t {
        InitBlockSplitterLiteral(
            m,
            &mut lit_blocks.plain,
            256 as libc::c_int as size_t,
            512 as libc::c_int as size_t,
            400.0f64,
            num_literals,
            &mut (*mb).literal_split,
            &mut (*mb).literal_histograms,
            &mut (*mb).literal_histograms_size,
        );
    } else {
        InitContextBlockSplitter(
            m,
            &mut lit_blocks.ctx,
            256 as libc::c_int as size_t,
            num_contexts,
            512 as libc::c_int as size_t,
            400.0f64,
            num_literals,
            &mut (*mb).literal_split,
            &mut (*mb).literal_histograms,
            &mut (*mb).literal_histograms_size,
        );
    }
    if 0 as libc::c_int != 0 {
        return;
    }
    InitBlockSplitterCommand(
        m,
        &mut cmd_blocks,
        704 as libc::c_int as size_t,
        1024 as libc::c_int as size_t,
        500.0f64,
        n_commands,
        &mut (*mb).command_split,
        &mut (*mb).command_histograms,
        &mut (*mb).command_histograms_size,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    InitBlockSplitterDistance(
        m,
        &mut dist_blocks,
        64 as libc::c_int as size_t,
        512 as libc::c_int as size_t,
        100.0f64,
        n_commands,
        &mut (*mb).distance_split,
        &mut (*mb).distance_histograms,
        &mut (*mb).distance_histograms_size,
    );
    if 0 as libc::c_int != 0 {
        return;
    }
    i = 0 as libc::c_int as size_t;
    while i < n_commands {
        let cmd: Command = *commands.offset(i as isize);
        let mut j: size_t = 0;
        BlockSplitterAddSymbolCommand(&mut cmd_blocks, cmd.cmd_prefix_ as size_t);
        j = cmd.insert_len_ as size_t;
        while j != 0 as libc::c_int as size_t {
            let mut literal: uint8_t = *ringbuffer.offset((pos & mask) as isize);
            if num_contexts == 1 as libc::c_int as size_t {
                BlockSplitterAddSymbolLiteral(&mut lit_blocks.plain, literal as size_t);
            } else {
                let mut context: size_t = (*literal_context_lut
                    .offset(prev_byte as isize) as libc::c_int
                    | *literal_context_lut
                        .offset(256 as libc::c_int as isize)
                        .offset(prev_byte2 as isize) as libc::c_int) as size_t;
                ContextBlockSplitterAddSymbol(
                    &mut lit_blocks.ctx,
                    m,
                    literal as size_t,
                    *static_context_map.offset(context as isize) as size_t,
                );
                if 0 as libc::c_int != 0 {
                    return;
                }
            }
            prev_byte2 = prev_byte;
            prev_byte = literal;
            pos = pos.wrapping_add(1);
            pos;
            j = j.wrapping_sub(1);
            j;
        }
        pos = pos.wrapping_add(CommandCopyLen(&cmd) as size_t);
        if CommandCopyLen(&cmd) != 0 {
            prev_byte2 = *ringbuffer
                .offset((pos.wrapping_sub(2 as libc::c_int as size_t) & mask) as isize);
            prev_byte = *ringbuffer
                .offset((pos.wrapping_sub(1 as libc::c_int as size_t) & mask) as isize);
            if cmd.cmd_prefix_ as libc::c_int >= 128 as libc::c_int {
                BlockSplitterAddSymbolDistance(
                    &mut dist_blocks,
                    (cmd.dist_prefix_ as libc::c_int & 0x3ff as libc::c_int) as size_t,
                );
            }
        }
        i = i.wrapping_add(1);
        i;
    }
    if num_contexts == 1 as libc::c_int as size_t {
        BlockSplitterFinishBlockLiteral(&mut lit_blocks.plain, 1 as libc::c_int);
    } else {
        ContextBlockSplitterFinishBlock(&mut lit_blocks.ctx, m, 1 as libc::c_int);
        if 0 as libc::c_int != 0 {
            return;
        }
    }
    BlockSplitterFinishBlockCommand(&mut cmd_blocks, 1 as libc::c_int);
    BlockSplitterFinishBlockDistance(&mut dist_blocks, 1 as libc::c_int);
    if num_contexts > 1 as libc::c_int as size_t {
        MapStaticContexts(m, num_contexts, static_context_map, mb);
    }
}
#[no_mangle]
pub unsafe extern "C" fn BrotliBuildMetaBlockGreedy(
    mut m: *mut MemoryManager,
    mut ringbuffer: *const uint8_t,
    mut pos: size_t,
    mut mask: size_t,
    mut prev_byte: uint8_t,
    mut prev_byte2: uint8_t,
    mut literal_context_lut: ContextLut,
    mut num_contexts: size_t,
    mut static_context_map: *const uint32_t,
    mut commands: *const Command,
    mut n_commands: size_t,
    mut mb: *mut MetaBlockSplit,
) {
    if num_contexts == 1 as libc::c_int as size_t {
        BrotliBuildMetaBlockGreedyInternal(
            m,
            ringbuffer,
            pos,
            mask,
            prev_byte,
            prev_byte2,
            literal_context_lut,
            1 as libc::c_int as size_t,
            0 as *const uint32_t,
            commands,
            n_commands,
            mb,
        );
    } else {
        BrotliBuildMetaBlockGreedyInternal(
            m,
            ringbuffer,
            pos,
            mask,
            prev_byte,
            prev_byte2,
            literal_context_lut,
            num_contexts,
            static_context_map,
            commands,
            n_commands,
            mb,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn BrotliOptimizeHistograms(
    mut num_distance_codes: uint32_t,
    mut mb: *mut MetaBlockSplit,
) {
    let mut good_for_rle: [uint8_t; 704] = [0; 704];
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < (*mb).literal_histograms_size {
        BrotliOptimizeHuffmanCountsForRle(
            256 as libc::c_int as size_t,
            ((*((*mb).literal_histograms).offset(i as isize)).data_).as_mut_ptr(),
            good_for_rle.as_mut_ptr(),
        );
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < (*mb).command_histograms_size {
        BrotliOptimizeHuffmanCountsForRle(
            704 as libc::c_int as size_t,
            ((*((*mb).command_histograms).offset(i as isize)).data_).as_mut_ptr(),
            good_for_rle.as_mut_ptr(),
        );
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < (*mb).distance_histograms_size {
        BrotliOptimizeHuffmanCountsForRle(
            num_distance_codes as size_t,
            ((*((*mb).distance_histograms).offset(i as isize)).data_).as_mut_ptr(),
            good_for_rle.as_mut_ptr(),
        );
        i = i.wrapping_add(1);
        i;
    }
}
