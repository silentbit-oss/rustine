use ::libc;
use ::c2rust_bitfields;
extern "C" {
    fn BrotliDecoderStateInit(
        s: *mut BrotliDecoderStateInternal,
        alloc_func: brotli_alloc_func,
        free_func: brotli_free_func,
        opaque: *mut libc::c_void,
    ) -> libc::c_int;
    fn BrotliDecoderStateCleanup(s: *mut BrotliDecoderStateInternal);
    fn BrotliDecoderStateMetablockBegin(s: *mut BrotliDecoderStateInternal);
    fn BrotliDecoderStateCleanupAfterMetablock(s: *mut BrotliDecoderStateInternal);
    fn BrotliDecoderHuffmanTreeGroupInit(
        s: *mut BrotliDecoderStateInternal,
        group: *mut HuffmanTreeGroup,
        alphabet_size_max: uint32_t,
        alphabet_size_limit: uint32_t,
        ntrees: uint32_t,
    ) -> libc::c_int;
    static kBrotliBitMask: [uint32_t; 33];
    fn BrotliWarmupBitReader(br: *mut BrotliBitReader) -> libc::c_int;
    fn BrotliSafeReadBits32Slow(
        br: *mut BrotliBitReader,
        n_bits: uint32_t,
        val: *mut uint32_t,
    ) -> libc::c_int;
    fn BrotliBuildCodeLengthsHuffmanTable(
        root_table: *mut HuffmanCode,
        code_lengths: *const uint8_t,
        count: *mut uint16_t,
    );
    fn BrotliBuildHuffmanTable(
        root_table: *mut HuffmanCode,
        root_bits: libc::c_int,
        symbol_lists: *const uint16_t,
        count: *mut uint16_t,
    ) -> uint32_t;
    fn BrotliBuildSimpleHuffmanTable(
        table: *mut HuffmanCode,
        root_bits: libc::c_int,
        symbols: *mut uint16_t,
        num_symbols: uint32_t,
    ) -> uint32_t;
    fn BrotliTransformDictionaryWord(
        dst: *mut uint8_t,
        word: *const uint8_t,
        len: libc::c_int,
        transforms: *const BrotliTransforms,
        transform_idx: libc::c_int,
    ) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
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
    static _kBrotliPrefixCodeRanges: [BrotliPrefixCodeRange; 26];
    static _kBrotliContextLookupTable: [uint8_t; 2048];
}
pub type size_t = libc::c_ulong;
pub type __int8_t = libc::c_schar;
pub type __uint8_t = libc::c_uchar;
pub type __int16_t = libc::c_short;
pub type __uint16_t = libc::c_ushort;
pub type __uint32_t = libc::c_uint;
pub type __uint64_t = libc::c_ulong;
pub type int8_t = __int8_t;
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
#[derive(Copy, Clone, BitfieldStruct)]
#[repr(C)]
pub struct BrotliDecoderStateStruct {
    pub state: BrotliRunningState,
    pub loop_counter: libc::c_int,
    pub br: BrotliBitReader,
    pub alloc_func: brotli_alloc_func,
    pub free_func: brotli_free_func,
    pub memory_manager_opaque: *mut libc::c_void,
    pub buffer: C2RustUnnamed_0,
    pub buffer_length: uint32_t,
    pub pos: libc::c_int,
    pub max_backward_distance: libc::c_int,
    pub max_distance: libc::c_int,
    pub ringbuffer_size: libc::c_int,
    pub ringbuffer_mask: libc::c_int,
    pub dist_rb_idx: libc::c_int,
    pub dist_rb: [libc::c_int; 4],
    pub error_code: libc::c_int,
    pub ringbuffer: *mut uint8_t,
    pub ringbuffer_end: *mut uint8_t,
    pub htree_command: *mut HuffmanCode,
    pub context_lookup: *const uint8_t,
    pub context_map_slice: *mut uint8_t,
    pub dist_context_map_slice: *mut uint8_t,
    pub literal_hgroup: HuffmanTreeGroup,
    pub insert_copy_hgroup: HuffmanTreeGroup,
    pub distance_hgroup: HuffmanTreeGroup,
    pub block_type_trees: *mut HuffmanCode,
    pub block_len_trees: *mut HuffmanCode,
    pub trivial_literal_context: libc::c_int,
    pub distance_context: libc::c_int,
    pub meta_block_remaining_len: libc::c_int,
    pub block_length_index: uint32_t,
    pub block_length: [uint32_t; 3],
    pub num_block_types: [uint32_t; 3],
    pub block_type_rb: [uint32_t; 6],
    pub distance_postfix_bits: uint32_t,
    pub num_direct_distance_codes: uint32_t,
    pub num_dist_htrees: uint32_t,
    pub dist_context_map: *mut uint8_t,
    pub literal_htree: *mut HuffmanCode,
    pub dist_htree_index: uint8_t,
    pub copy_length: libc::c_int,
    pub distance_code: libc::c_int,
    pub rb_roundtrips: size_t,
    pub partial_pos_out: size_t,
    pub mtf_upper_bound: uint32_t,
    pub mtf: [uint32_t; 65],
    pub substate_metablock_header: BrotliRunningMetablockHeaderState,
    pub substate_uncompressed: BrotliRunningUncompressedState,
    pub substate_decode_uint8: BrotliRunningDecodeUint8State,
    pub substate_read_block_length: BrotliRunningReadBlockLengthState,
    #[bitfield(name = "is_last_metablock", ty = "libc::c_uint", bits = "0..=0")]
    #[bitfield(name = "is_uncompressed", ty = "libc::c_uint", bits = "1..=1")]
    #[bitfield(name = "is_metadata", ty = "libc::c_uint", bits = "2..=2")]
    #[bitfield(name = "should_wrap_ringbuffer", ty = "libc::c_uint", bits = "3..=3")]
    #[bitfield(
        name = "canny_ringbuffer_allocation",
        ty = "libc::c_uint",
        bits = "4..=4"
    )]
    #[bitfield(name = "large_window", ty = "libc::c_uint", bits = "5..=5")]
    #[bitfield(name = "size_nibbles", ty = "libc::c_uint", bits = "6..=13")]
    pub is_last_metablock_is_uncompressed_is_metadata_should_wrap_ringbuffer_canny_ringbuffer_allocation_large_window_size_nibbles: [u8; 2],
    #[bitfield(padding)]
    pub c2rust_padding: [u8; 2],
    pub window_bits: uint32_t,
    pub new_ringbuffer_size: libc::c_int,
    pub num_literal_htrees: uint32_t,
    pub context_map: *mut uint8_t,
    pub context_modes: *mut uint8_t,
    pub dictionary: *const BrotliDictionary,
    pub transforms: *const BrotliTransforms,
    pub trivial_literal_contexts: [uint32_t; 8],
    pub arena: C2RustUnnamed,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub header: BrotliMetablockHeaderArena,
    pub body: BrotliMetablockBodyArena,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliMetablockBodyArena {
    pub dist_extra_bits: [uint8_t; 544],
    pub dist_offset: [uint32_t; 544],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliMetablockHeaderArena {
    pub substate_tree_group: BrotliRunningTreeGroupState,
    pub substate_context_map: BrotliRunningContextMapState,
    pub substate_huffman: BrotliRunningHuffmanState,
    pub sub_loop_counter: uint32_t,
    pub repeat_code_len: uint32_t,
    pub prev_code_len: uint32_t,
    pub symbol: uint32_t,
    pub repeat: uint32_t,
    pub space: uint32_t,
    pub table: [HuffmanCode; 32],
    pub symbol_lists: *mut uint16_t,
    pub symbols_lists_array: [uint16_t; 720],
    pub next_symbol: [libc::c_int; 32],
    pub code_length_code_lengths: [uint8_t; 18],
    pub code_length_histo: [uint16_t; 16],
    pub htree_index: libc::c_int,
    pub next: *mut HuffmanCode,
    pub context_index: uint32_t,
    pub max_run_length_prefix: uint32_t,
    pub code: uint32_t,
    pub context_map_table: [HuffmanCode; 646],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HuffmanCode {
    pub bits: uint8_t,
    pub value: uint16_t,
}
pub type BrotliRunningHuffmanState = libc::c_uint;
pub const BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS: BrotliRunningHuffmanState = 5;
pub const BROTLI_STATE_HUFFMAN_COMPLEX: BrotliRunningHuffmanState = 4;
pub const BROTLI_STATE_HUFFMAN_SIMPLE_BUILD: BrotliRunningHuffmanState = 3;
pub const BROTLI_STATE_HUFFMAN_SIMPLE_READ: BrotliRunningHuffmanState = 2;
pub const BROTLI_STATE_HUFFMAN_SIMPLE_SIZE: BrotliRunningHuffmanState = 1;
pub const BROTLI_STATE_HUFFMAN_NONE: BrotliRunningHuffmanState = 0;
pub type BrotliRunningContextMapState = libc::c_uint;
pub const BROTLI_STATE_CONTEXT_MAP_TRANSFORM: BrotliRunningContextMapState = 4;
pub const BROTLI_STATE_CONTEXT_MAP_DECODE: BrotliRunningContextMapState = 3;
pub const BROTLI_STATE_CONTEXT_MAP_HUFFMAN: BrotliRunningContextMapState = 2;
pub const BROTLI_STATE_CONTEXT_MAP_READ_PREFIX: BrotliRunningContextMapState = 1;
pub const BROTLI_STATE_CONTEXT_MAP_NONE: BrotliRunningContextMapState = 0;
pub type BrotliRunningTreeGroupState = libc::c_uint;
pub const BROTLI_STATE_TREE_GROUP_LOOP: BrotliRunningTreeGroupState = 1;
pub const BROTLI_STATE_TREE_GROUP_NONE: BrotliRunningTreeGroupState = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliTransforms {
    pub prefix_suffix_size: uint16_t,
    pub prefix_suffix: *const uint8_t,
    pub prefix_suffix_map: *const uint16_t,
    pub num_transforms: uint32_t,
    pub transforms: *const uint8_t,
    pub params: *const uint8_t,
    pub cutOffTransforms: [int16_t; 10],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliDictionary {
    pub size_bits_by_length: [uint8_t; 32],
    pub offsets_by_length: [uint32_t; 32],
    pub data_size: size_t,
    pub data: *const uint8_t,
}
pub type BrotliRunningReadBlockLengthState = libc::c_uint;
pub const BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX: BrotliRunningReadBlockLengthState = 1;
pub const BROTLI_STATE_READ_BLOCK_LENGTH_NONE: BrotliRunningReadBlockLengthState = 0;
pub type BrotliRunningDecodeUint8State = libc::c_uint;
pub const BROTLI_STATE_DECODE_UINT8_LONG: BrotliRunningDecodeUint8State = 2;
pub const BROTLI_STATE_DECODE_UINT8_SHORT: BrotliRunningDecodeUint8State = 1;
pub const BROTLI_STATE_DECODE_UINT8_NONE: BrotliRunningDecodeUint8State = 0;
pub type BrotliRunningUncompressedState = libc::c_uint;
pub const BROTLI_STATE_UNCOMPRESSED_WRITE: BrotliRunningUncompressedState = 1;
pub const BROTLI_STATE_UNCOMPRESSED_NONE: BrotliRunningUncompressedState = 0;
pub type BrotliRunningMetablockHeaderState = libc::c_uint;
pub const BROTLI_STATE_METABLOCK_HEADER_METADATA: BrotliRunningMetablockHeaderState = 7;
pub const BROTLI_STATE_METABLOCK_HEADER_BYTES: BrotliRunningMetablockHeaderState = 6;
pub const BROTLI_STATE_METABLOCK_HEADER_RESERVED: BrotliRunningMetablockHeaderState = 5;
pub const BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED: BrotliRunningMetablockHeaderState = 4;
pub const BROTLI_STATE_METABLOCK_HEADER_SIZE: BrotliRunningMetablockHeaderState = 3;
pub const BROTLI_STATE_METABLOCK_HEADER_NIBBLES: BrotliRunningMetablockHeaderState = 2;
pub const BROTLI_STATE_METABLOCK_HEADER_EMPTY: BrotliRunningMetablockHeaderState = 1;
pub const BROTLI_STATE_METABLOCK_HEADER_NONE: BrotliRunningMetablockHeaderState = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct HuffmanTreeGroup {
    pub htrees: *mut *mut HuffmanCode,
    pub codes: *mut HuffmanCode,
    pub alphabet_size_max: uint16_t,
    pub alphabet_size_limit: uint16_t,
    pub num_htrees: uint16_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_0 {
    pub u64_0: uint64_t,
    pub u8_0: [uint8_t; 8],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliBitReader {
    pub val_: uint64_t,
    pub bit_pos_: uint32_t,
    pub next_in: *const uint8_t,
    pub avail_in: size_t,
}
pub type BrotliRunningState = libc::c_uint;
pub const BROTLI_STATE_DONE: BrotliRunningState = 26;
pub const BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY: BrotliRunningState = 25;
pub const BROTLI_STATE_TREE_GROUP: BrotliRunningState = 24;
pub const BROTLI_STATE_CONTEXT_MAP_2: BrotliRunningState = 23;
pub const BROTLI_STATE_CONTEXT_MAP_1: BrotliRunningState = 22;
pub const BROTLI_STATE_HUFFMAN_CODE_3: BrotliRunningState = 21;
pub const BROTLI_STATE_HUFFMAN_CODE_2: BrotliRunningState = 20;
pub const BROTLI_STATE_HUFFMAN_CODE_1: BrotliRunningState = 19;
pub const BROTLI_STATE_HUFFMAN_CODE_0: BrotliRunningState = 18;
pub const BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER: BrotliRunningState = 17;
pub const BROTLI_STATE_COMMAND_POST_WRITE_2: BrotliRunningState = 16;
pub const BROTLI_STATE_COMMAND_POST_WRITE_1: BrotliRunningState = 15;
pub const BROTLI_STATE_METABLOCK_DONE: BrotliRunningState = 14;
pub const BROTLI_STATE_COMMAND_INNER_WRITE: BrotliRunningState = 13;
pub const BROTLI_STATE_METADATA: BrotliRunningState = 12;
pub const BROTLI_STATE_UNCOMPRESSED: BrotliRunningState = 11;
pub const BROTLI_STATE_COMMAND_POST_WRAP_COPY: BrotliRunningState = 10;
pub const BROTLI_STATE_COMMAND_POST_DECODE_LITERALS: BrotliRunningState = 9;
pub const BROTLI_STATE_COMMAND_INNER: BrotliRunningState = 8;
pub const BROTLI_STATE_COMMAND_BEGIN: BrotliRunningState = 7;
pub const BROTLI_STATE_CONTEXT_MODES: BrotliRunningState = 6;
pub const BROTLI_STATE_METABLOCK_HEADER_2: BrotliRunningState = 5;
pub const BROTLI_STATE_METABLOCK_HEADER: BrotliRunningState = 4;
pub const BROTLI_STATE_METABLOCK_BEGIN: BrotliRunningState = 3;
pub const BROTLI_STATE_INITIALIZE: BrotliRunningState = 2;
pub const BROTLI_STATE_LARGE_WINDOW_BITS: BrotliRunningState = 1;
pub const BROTLI_STATE_UNINITED: BrotliRunningState = 0;
pub type BrotliDecoderState = BrotliDecoderStateStruct;
pub type BrotliDecoderResult = libc::c_uint;
pub const BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT: BrotliDecoderResult = 3;
pub const BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT: BrotliDecoderResult = 2;
pub const BROTLI_DECODER_RESULT_SUCCESS: BrotliDecoderResult = 1;
pub const BROTLI_DECODER_RESULT_ERROR: BrotliDecoderResult = 0;
pub type BrotliDecoderErrorCode = libc::c_int;
pub const BROTLI_DECODER_ERROR_UNREACHABLE: BrotliDecoderErrorCode = -31;
pub const BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES: BrotliDecoderErrorCode = -30;
pub const BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2: BrotliDecoderErrorCode = -27;
pub const BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1: BrotliDecoderErrorCode = -26;
pub const BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP: BrotliDecoderErrorCode = -25;
pub const BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS: BrotliDecoderErrorCode = -22;
pub const BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES: BrotliDecoderErrorCode = -21;
pub const BROTLI_DECODER_ERROR_INVALID_ARGUMENTS: BrotliDecoderErrorCode = -20;
pub const BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET: BrotliDecoderErrorCode = -19;
pub const BROTLI_DECODER_ERROR_FORMAT_DISTANCE: BrotliDecoderErrorCode = -16;
pub const BROTLI_DECODER_ERROR_FORMAT_PADDING_2: BrotliDecoderErrorCode = -15;
pub const BROTLI_DECODER_ERROR_FORMAT_PADDING_1: BrotliDecoderErrorCode = -14;
pub const BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS: BrotliDecoderErrorCode = -13;
pub const BROTLI_DECODER_ERROR_FORMAT_DICTIONARY: BrotliDecoderErrorCode = -12;
pub const BROTLI_DECODER_ERROR_FORMAT_TRANSFORM: BrotliDecoderErrorCode = -11;
pub const BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2: BrotliDecoderErrorCode = -10;
pub const BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1: BrotliDecoderErrorCode = -9;
pub const BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT: BrotliDecoderErrorCode = -8;
pub const BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE: BrotliDecoderErrorCode = -7;
pub const BROTLI_DECODER_ERROR_FORMAT_CL_SPACE: BrotliDecoderErrorCode = -6;
pub const BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME: BrotliDecoderErrorCode = -5;
pub const BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET: BrotliDecoderErrorCode = -4;
pub const BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE: BrotliDecoderErrorCode = -3;
pub const BROTLI_DECODER_ERROR_FORMAT_RESERVED: BrotliDecoderErrorCode = -2;
pub const BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE: BrotliDecoderErrorCode = -1;
pub const BROTLI_DECODER_NEEDS_MORE_OUTPUT: BrotliDecoderErrorCode = 3;
pub const BROTLI_DECODER_NEEDS_MORE_INPUT: BrotliDecoderErrorCode = 2;
pub const BROTLI_DECODER_SUCCESS: BrotliDecoderErrorCode = 1;
pub const BROTLI_DECODER_NO_ERROR: BrotliDecoderErrorCode = 0;
pub type BrotliDecoderParameter = libc::c_uint;
pub const BROTLI_DECODER_PARAM_LARGE_WINDOW: BrotliDecoderParameter = 1;
pub const BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION: BrotliDecoderParameter = 0;
pub type BrotliDecoderStateInternal = BrotliDecoderStateStruct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliBitReaderState {
    pub val_: uint64_t,
    pub bit_pos_: uint32_t,
    pub next_in: *const uint8_t,
    pub avail_in: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliPrefixCodeRange {
    pub offset: uint16_t,
    pub nbits: uint8_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct CmdLutElement {
    pub insert_len_extra_bits: uint8_t,
    pub copy_len_extra_bits: uint8_t,
    pub distance_code: int8_t,
    pub context: uint8_t,
    pub insert_len_offset: uint16_t,
    pub copy_len_offset: uint16_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct BrotliDistanceCodeLimit {
    pub max_alphabet_size: uint32_t,
    pub max_distance: uint32_t,
}
#[inline(always)]
unsafe extern "C" fn BitMask(mut n: uint32_t) -> uint32_t {
    if 0 != 0 || 0 as libc::c_int != 0 {
        return !((0xffffffff as libc::c_uint) << n)
    } else {
        return kBrotliBitMask[n as usize]
    };
}
#[inline(always)]
unsafe extern "C" fn BrotliBitReaderSaveState(
    from: *mut BrotliBitReader,
    mut to: *mut BrotliBitReaderState,
) {
    (*to).val_ = (*from).val_;
    (*to).bit_pos_ = (*from).bit_pos_;
    (*to).next_in = (*from).next_in;
    (*to).avail_in = (*from).avail_in;
}
#[inline(always)]
unsafe extern "C" fn BrotliBitReaderRestoreState(
    to: *mut BrotliBitReader,
    mut from: *mut BrotliBitReaderState,
) {
    (*to).val_ = (*from).val_;
    (*to).bit_pos_ = (*from).bit_pos_;
    (*to).next_in = (*from).next_in;
    (*to).avail_in = (*from).avail_in;
}
#[inline(always)]
unsafe extern "C" fn BrotliGetAvailableBits(mut br: *const BrotliBitReader) -> uint32_t {
    return ((if 1 as libc::c_int != 0 { 64 as libc::c_int } else { 32 as libc::c_int })
        as uint32_t)
        .wrapping_sub((*br).bit_pos_);
}
#[inline(always)]
unsafe extern "C" fn BrotliGetRemainingBytes(mut br: *mut BrotliBitReader) -> size_t {
    static mut kCap: size_t = (1 as libc::c_int as size_t) << 30 as libc::c_int;
    if (*br).avail_in > kCap {
        return kCap;
    }
    return ((*br).avail_in)
        .wrapping_add((BrotliGetAvailableBits(br) >> 3 as libc::c_int) as size_t);
}
#[inline(always)]
unsafe extern "C" fn BrotliCheckInputAmount(
    br: *mut BrotliBitReader,
    mut num: size_t,
) -> libc::c_int {
    return if (*br).avail_in >= num { 1 as libc::c_int } else { 0 as libc::c_int };
}
#[inline(always)]
unsafe extern "C" fn BrotliFillBitWindow(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
) {
    if 0 as libc::c_int == 0 && 0 != 0 && n_bits <= 8 as libc::c_int as uint32_t {
        if (*br).bit_pos_ >= 56 as libc::c_int as uint32_t {
            (*br).val_ >>= 56 as libc::c_int;
            (*br).bit_pos_ ^= 56 as libc::c_int as uint32_t;
            (*br).val_
                |= BrotliUnalignedRead64((*br).next_in as *const libc::c_void)
                    << 8 as libc::c_int;
            (*br).avail_in = ((*br).avail_in).wrapping_sub(7 as libc::c_int as size_t);
            (*br).next_in = ((*br).next_in).offset(7 as libc::c_int as isize);
        }
    } else if 0 as libc::c_int == 0 && 0 != 0 && n_bits <= 16 as libc::c_int as uint32_t
    {
        if (*br).bit_pos_ >= 48 as libc::c_int as uint32_t {
            (*br).val_ >>= 48 as libc::c_int;
            (*br).bit_pos_ ^= 48 as libc::c_int as uint32_t;
            (*br).val_
                |= BrotliUnalignedRead64((*br).next_in as *const libc::c_void)
                    << 16 as libc::c_int;
            (*br).avail_in = ((*br).avail_in).wrapping_sub(6 as libc::c_int as size_t);
            (*br).next_in = ((*br).next_in).offset(6 as libc::c_int as isize);
        }
    } else if (*br).bit_pos_ >= 32 as libc::c_int as uint32_t {
        (*br).val_ >>= 32 as libc::c_int;
        (*br).bit_pos_ ^= 32 as libc::c_int as uint32_t;
        (*br).val_
            |= (BrotliUnalignedRead32((*br).next_in as *const libc::c_void) as uint64_t)
                << 32 as libc::c_int;
        (*br)
            .avail_in = ((*br).avail_in as libc::c_ulong)
            .wrapping_sub(
                ::core::mem::size_of::<uint64_t>() as libc::c_ulong >> 1 as libc::c_int,
            ) as size_t as size_t;
        (*br)
            .next_in = ((*br).next_in)
            .offset(
                (::core::mem::size_of::<uint64_t>() as libc::c_ulong >> 1 as libc::c_int)
                    as isize,
            );
    }
}
#[inline(always)]
unsafe extern "C" fn BrotliFillBitWindow16(br: *mut BrotliBitReader) {
    BrotliFillBitWindow(br, 17 as libc::c_int as uint32_t);
}
#[inline(always)]
unsafe extern "C" fn BrotliPullByte(br: *mut BrotliBitReader) -> libc::c_int {
    if (*br).avail_in == 0 as libc::c_int as size_t {
        return 0 as libc::c_int;
    }
    (*br).val_ >>= 8 as libc::c_int;
    (*br).val_ |= (*(*br).next_in as uint64_t) << 56 as libc::c_int;
    (*br).bit_pos_ = ((*br).bit_pos_).wrapping_sub(8 as libc::c_int as uint32_t);
    (*br).avail_in = ((*br).avail_in).wrapping_sub(1);
    (*br).avail_in;
    (*br).next_in = ((*br).next_in).offset(1);
    (*br).next_in;
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn BrotliGetBitsUnmasked(br: *mut BrotliBitReader) -> uint64_t {
    return (*br).val_ >> (*br).bit_pos_;
}
#[inline(always)]
unsafe extern "C" fn BrotliGet16BitsUnmasked(br: *mut BrotliBitReader) -> uint32_t {
    BrotliFillBitWindow(br, 16 as libc::c_int as uint32_t);
    return BrotliGetBitsUnmasked(br) as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn BrotliGetBits(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
) -> uint32_t {
    BrotliFillBitWindow(br, n_bits);
    return BrotliGetBitsUnmasked(br) as uint32_t & BitMask(n_bits);
}
#[inline(always)]
unsafe extern "C" fn BrotliSafeGetBits(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) -> libc::c_int {
    while BrotliGetAvailableBits(br) < n_bits {
        if BrotliPullByte(br) == 0 {
            return 0 as libc::c_int;
        }
    }
    *val = BrotliGetBitsUnmasked(br) as uint32_t & BitMask(n_bits);
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn BrotliDropBits(br: *mut BrotliBitReader, mut n_bits: uint32_t) {
    (*br).bit_pos_ = ((*br).bit_pos_).wrapping_add(n_bits);
}
#[inline(always)]
unsafe extern "C" fn BrotliBitReaderUnload(mut br: *mut BrotliBitReader) {
    let mut unused_bytes: uint32_t = BrotliGetAvailableBits(br) >> 3 as libc::c_int;
    let mut unused_bits: uint32_t = unused_bytes << 3 as libc::c_int;
    (*br).avail_in = ((*br).avail_in).wrapping_add(unused_bytes as size_t);
    (*br).next_in = ((*br).next_in).offset(-(unused_bytes as isize));
    if unused_bits as libc::c_ulong
        == (::core::mem::size_of::<uint64_t>() as libc::c_ulong) << 3 as libc::c_int
    {
        (*br).val_ = 0 as libc::c_int as uint64_t;
    } else {
        (*br).val_ <<= unused_bits;
    }
    (*br).bit_pos_ = ((*br).bit_pos_).wrapping_add(unused_bits);
}
#[inline(always)]
unsafe extern "C" fn BrotliTakeBits(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) {
    *val = BrotliGetBitsUnmasked(br) as uint32_t & BitMask(n_bits);
    BrotliDropBits(br, n_bits);
}
#[inline(always)]
unsafe extern "C" fn BrotliReadBits24(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
) -> uint32_t {
    if 1 as libc::c_int != 0 || n_bits <= 16 as libc::c_int as uint32_t {
        let mut val: uint32_t = 0;
        BrotliFillBitWindow(br, n_bits);
        BrotliTakeBits(br, n_bits, &mut val);
        return val;
    } else {
        let mut low_val: uint32_t = 0;
        let mut high_val: uint32_t = 0;
        BrotliFillBitWindow(br, 16 as libc::c_int as uint32_t);
        BrotliTakeBits(br, 16 as libc::c_int as uint32_t, &mut low_val);
        BrotliFillBitWindow(br, 8 as libc::c_int as uint32_t);
        BrotliTakeBits(
            br,
            n_bits.wrapping_sub(16 as libc::c_int as uint32_t),
            &mut high_val,
        );
        return low_val | high_val << 16 as libc::c_int;
    };
}
#[inline(always)]
unsafe extern "C" fn BrotliReadBits32(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
) -> uint32_t {
    if 1 as libc::c_int != 0 || n_bits <= 16 as libc::c_int as uint32_t {
        let mut val: uint32_t = 0;
        BrotliFillBitWindow(br, n_bits);
        BrotliTakeBits(br, n_bits, &mut val);
        return val;
    } else {
        let mut low_val: uint32_t = 0;
        let mut high_val: uint32_t = 0;
        BrotliFillBitWindow(br, 16 as libc::c_int as uint32_t);
        BrotliTakeBits(br, 16 as libc::c_int as uint32_t, &mut low_val);
        BrotliFillBitWindow(br, 16 as libc::c_int as uint32_t);
        BrotliTakeBits(
            br,
            n_bits.wrapping_sub(16 as libc::c_int as uint32_t),
            &mut high_val,
        );
        return low_val | high_val << 16 as libc::c_int;
    };
}
#[inline(always)]
unsafe extern "C" fn BrotliSafeReadBits(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) -> libc::c_int {
    while BrotliGetAvailableBits(br) < n_bits {
        if BrotliPullByte(br) == 0 {
            return 0 as libc::c_int;
        }
    }
    BrotliTakeBits(br, n_bits, val);
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn BrotliSafeReadBits32(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) -> libc::c_int {
    if 1 as libc::c_int != 0 || n_bits <= 24 as libc::c_int as uint32_t {
        while BrotliGetAvailableBits(br) < n_bits {
            if BrotliPullByte(br) == 0 {
                return 0 as libc::c_int;
            }
        }
        BrotliTakeBits(br, n_bits, val);
        return 1 as libc::c_int;
    } else {
        return BrotliSafeReadBits32Slow(br, n_bits, val)
    };
}
#[inline(always)]
unsafe extern "C" fn BrotliJumpToByteBoundary(
    mut br: *mut BrotliBitReader,
) -> libc::c_int {
    let mut pad_bits_count: uint32_t = BrotliGetAvailableBits(br)
        & 0x7 as libc::c_int as uint32_t;
    let mut pad_bits: uint32_t = 0 as libc::c_int as uint32_t;
    if pad_bits_count != 0 as libc::c_int as uint32_t {
        BrotliTakeBits(br, pad_bits_count, &mut pad_bits);
    }
    return if pad_bits == 0 as libc::c_int as uint32_t {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    };
}
#[inline(always)]
unsafe extern "C" fn BrotliCopyBytes(
    mut dest: *mut uint8_t,
    mut br: *mut BrotliBitReader,
    mut num: size_t,
) {
    while BrotliGetAvailableBits(br) >= 8 as libc::c_int as uint32_t
        && num > 0 as libc::c_int as size_t
    {
        *dest = BrotliGetBitsUnmasked(br) as uint8_t;
        BrotliDropBits(br, 8 as libc::c_int as uint32_t);
        dest = dest.offset(1);
        dest;
        num = num.wrapping_sub(1);
        num;
    }
    memcpy(dest as *mut libc::c_void, (*br).next_in as *const libc::c_void, num);
    (*br).avail_in = ((*br).avail_in).wrapping_sub(num);
    (*br).next_in = ((*br).next_in).offset(num as isize);
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
static mut kCmdLut: [CmdLutElement; 704] = [
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: 0 as libc::c_int as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x2 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x3 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x4 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x6 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x8 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x2 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x1 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x3 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x2 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x4 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x5 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x7 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x8 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x9 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xa as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xe as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x12 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1a as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x22 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x32 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x42 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x62 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0xa as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x1 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0xe as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x2 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x12 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x16 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x3 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x1e as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x26 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x4 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x36 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x82 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0xc2 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x142 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x242 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xa as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x442 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xc as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x842 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0xe as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x1842 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x46 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x5 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x66 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x6 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x86 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x7 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0xc6 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x8 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x146 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x9 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x246 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0xa as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x446 as libc::c_int as uint16_t,
        };
        init
    },
    {
        let mut init = CmdLutElement {
            insert_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            copy_len_extra_bits: 0x18 as libc::c_int as uint8_t,
            distance_code: -(1 as libc::c_int) as int8_t,
            context: 0x3 as libc::c_int as uint8_t,
            insert_len_offset: 0x5842 as libc::c_int as uint16_t,
            copy_len_offset: 0x846 as libc::c_int as uint16_t,
        };
        init
    },
];
static mut kRingBufferWriteAheadSlack: uint32_t = 42 as libc::c_int as uint32_t;
static mut kCodeLengthCodeOrder: [uint8_t; 18] = [
    1 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    5 as libc::c_int as uint8_t,
    17 as libc::c_int as uint8_t,
    6 as libc::c_int as uint8_t,
    16 as libc::c_int as uint8_t,
    7 as libc::c_int as uint8_t,
    8 as libc::c_int as uint8_t,
    9 as libc::c_int as uint8_t,
    10 as libc::c_int as uint8_t,
    11 as libc::c_int as uint8_t,
    12 as libc::c_int as uint8_t,
    13 as libc::c_int as uint8_t,
    14 as libc::c_int as uint8_t,
    15 as libc::c_int as uint8_t,
];
static mut kCodeLengthPrefixLength: [uint8_t; 16] = [
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
];
static mut kCodeLengthPrefixValue: [uint8_t; 16] = [
    0 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    1 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    5 as libc::c_int as uint8_t,
];
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderSetParameter(
    mut state: *mut BrotliDecoderStateInternal,
    mut p: BrotliDecoderParameter,
    mut value: uint32_t,
) -> libc::c_int {
    if (*state).state as libc::c_uint
        != BROTLI_STATE_UNINITED as libc::c_int as libc::c_uint
    {
        return 0 as libc::c_int;
    }
    match p as libc::c_uint {
        0 => {
            (*state)
                .set_canny_ringbuffer_allocation(
                    (if value != 0 { 0 as libc::c_int } else { 1 as libc::c_int })
                        as libc::c_uint,
                );
            return 1 as libc::c_int;
        }
        1 => {
            (*state)
                .set_large_window(
                    (if value != 0 { 1 as libc::c_int } else { 0 as libc::c_int })
                        as libc::c_uint,
                );
            return 1 as libc::c_int;
        }
        _ => return 0 as libc::c_int,
    };
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderCreateInstance(
    mut alloc_func: brotli_alloc_func,
    mut free_func: brotli_free_func,
    mut opaque: *mut libc::c_void,
) -> *mut BrotliDecoderState {
    let mut state: *mut BrotliDecoderStateInternal = 0
        as *mut BrotliDecoderStateInternal;
    if alloc_func.is_none() && free_func.is_none() {
        state = malloc(
            ::core::mem::size_of::<BrotliDecoderStateInternal>() as libc::c_ulong,
        ) as *mut BrotliDecoderStateInternal;
    } else if alloc_func.is_some() && free_func.is_some() {
        state = alloc_func
            .expect(
                "non-null function pointer",
            )(
            opaque,
            ::core::mem::size_of::<BrotliDecoderStateInternal>() as libc::c_ulong,
        ) as *mut BrotliDecoderStateInternal;
    }
    if state.is_null() {
        return 0 as *mut BrotliDecoderState;
    }
    if BrotliDecoderStateInit(state, alloc_func, free_func, opaque) == 0 {
        if alloc_func.is_none() && free_func.is_none() {
            free(state as *mut libc::c_void);
        } else if alloc_func.is_some() && free_func.is_some() {
            free_func
                .expect("non-null function pointer")(opaque, state as *mut libc::c_void);
        }
        return 0 as *mut BrotliDecoderState;
    }
    return state;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderDestroyInstance(
    mut state: *mut BrotliDecoderStateInternal,
) {
    if state.is_null() {
        return
    } else {
        let mut free_func: brotli_free_func = (*state).free_func;
        let mut opaque: *mut libc::c_void = (*state).memory_manager_opaque;
        BrotliDecoderStateCleanup(state);
        free_func
            .expect("non-null function pointer")(opaque, state as *mut libc::c_void);
    };
}
#[inline(never)]
unsafe extern "C" fn SaveErrorCode(
    mut s: *mut BrotliDecoderStateInternal,
    mut e: BrotliDecoderErrorCode,
) -> BrotliDecoderResult {
    (*s).error_code = e as libc::c_int;
    match e as libc::c_int {
        1 => return BROTLI_DECODER_RESULT_SUCCESS,
        2 => return BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT,
        3 => return BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT,
        _ => return BROTLI_DECODER_RESULT_ERROR,
    };
}
unsafe extern "C" fn DecodeWindowBits(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
) -> BrotliDecoderErrorCode {
    let mut n: uint32_t = 0;
    let mut large_window: libc::c_int = (*s).large_window() as libc::c_int;
    (*s).set_large_window(0 as libc::c_int as libc::c_uint);
    BrotliTakeBits(br, 1 as libc::c_int as uint32_t, &mut n);
    if n == 0 as libc::c_int as uint32_t {
        (*s).window_bits = 16 as libc::c_int as uint32_t;
        return BROTLI_DECODER_SUCCESS;
    }
    BrotliTakeBits(br, 3 as libc::c_int as uint32_t, &mut n);
    if n != 0 as libc::c_int as uint32_t {
        (*s).window_bits = (17 as libc::c_int as uint32_t).wrapping_add(n);
        return BROTLI_DECODER_SUCCESS;
    }
    BrotliTakeBits(br, 3 as libc::c_int as uint32_t, &mut n);
    if n == 1 as libc::c_int as uint32_t {
        if large_window != 0 {
            BrotliTakeBits(br, 1 as libc::c_int as uint32_t, &mut n);
            if n == 1 as libc::c_int as uint32_t {
                return BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS as libc::c_int
                    as BrotliDecoderErrorCode;
            }
            (*s).set_large_window(1 as libc::c_int as libc::c_uint);
            return BROTLI_DECODER_SUCCESS;
        } else {
            return BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS as libc::c_int
                as BrotliDecoderErrorCode
        }
    }
    if n != 0 as libc::c_int as uint32_t {
        (*s).window_bits = (8 as libc::c_int as uint32_t).wrapping_add(n);
        return BROTLI_DECODER_SUCCESS;
    }
    (*s).window_bits = 17 as libc::c_int as uint32_t;
    return BROTLI_DECODER_SUCCESS;
}
#[inline(always)]
unsafe extern "C" fn memmove16(mut dst: *mut uint8_t, mut src: *mut uint8_t) {
    let mut buffer: [uint32_t; 4] = [0; 4];
    memcpy(
        buffer.as_mut_ptr() as *mut libc::c_void,
        src as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
    memcpy(
        dst as *mut libc::c_void,
        buffer.as_mut_ptr() as *const libc::c_void,
        16 as libc::c_int as libc::c_ulong,
    );
}
#[inline(never)]
unsafe extern "C" fn DecodeVarLenUint8(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
    mut value: *mut uint32_t,
) -> BrotliDecoderErrorCode {
    let mut bits: uint32_t = 0;
    let mut current_block_24: u64;
    match (*s).substate_decode_uint8 as libc::c_uint {
        0 => {
            if (BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits) == 0)
                as libc::c_int as libc::c_long != 0
            {
                return BROTLI_DECODER_NEEDS_MORE_INPUT;
            }
            if bits == 0 as libc::c_int as uint32_t {
                *value = 0 as libc::c_int as uint32_t;
                return BROTLI_DECODER_SUCCESS;
            }
            current_block_24 = 16114959784553087369;
        }
        1 => {
            current_block_24 = 16114959784553087369;
        }
        2 => {
            current_block_24 = 11935880147193711980;
        }
        _ => {
            return BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                as BrotliDecoderErrorCode;
        }
    }
    match current_block_24 {
        16114959784553087369 => {
            if (BrotliSafeReadBits(br, 3 as libc::c_int as uint32_t, &mut bits) == 0)
                as libc::c_int as libc::c_long != 0
            {
                (*s).substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_SHORT;
                return BROTLI_DECODER_NEEDS_MORE_INPUT;
            }
            if bits == 0 as libc::c_int as uint32_t {
                *value = 1 as libc::c_int as uint32_t;
                (*s).substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
                return BROTLI_DECODER_SUCCESS;
            }
            *value = bits;
        }
        _ => {}
    }
    if (BrotliSafeReadBits(br, *value, &mut bits) == 0) as libc::c_int as libc::c_long
        != 0
    {
        (*s).substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_LONG;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    *value = ((1 as libc::c_uint) << *value).wrapping_add(bits);
    (*s).substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
    return BROTLI_DECODER_SUCCESS;
}
#[inline(never)]
unsafe extern "C" fn DecodeMetaBlockLength(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
) -> BrotliDecoderErrorCode {
    let mut bits: uint32_t = 0;
    let mut i: libc::c_int = 0;
    loop {
        's_305: {
            let mut current_block_76: u64;
            match (*s).substate_metablock_header as libc::c_uint {
                0 => {
                    if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits)
                        == 0
                    {
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    (*s)
                        .set_is_last_metablock(
                            (if bits != 0 { 1 as libc::c_int } else { 0 as libc::c_int })
                                as libc::c_uint,
                        );
                    (*s).meta_block_remaining_len = 0 as libc::c_int;
                    (*s).set_is_uncompressed(0 as libc::c_int as libc::c_uint);
                    (*s).set_is_metadata(0 as libc::c_int as libc::c_uint);
                    if (*s).is_last_metablock() == 0 {
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;
                        current_block_76 = 17836213544692497527;
                    } else {
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_EMPTY;
                        current_block_76 = 14791804988756215412;
                    }
                }
                1 => {
                    current_block_76 = 14791804988756215412;
                }
                2 => {
                    current_block_76 = 5316138500539939593;
                }
                3 => {
                    current_block_76 = 8307118956945566857;
                }
                4 => {
                    current_block_76 = 16728379834002806341;
                }
                5 => {
                    if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits)
                        == 0
                    {
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    if bits != 0 as libc::c_int as uint32_t {
                        return BROTLI_DECODER_ERROR_FORMAT_RESERVED as libc::c_int
                            as BrotliDecoderErrorCode;
                    }
                    (*s).substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_BYTES;
                    current_block_76 = 7043617712618060937;
                }
                6 => {
                    current_block_76 = 7043617712618060937;
                }
                7 => {
                    current_block_76 = 3065322521856595317;
                }
                _ => {
                    return BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                        as BrotliDecoderErrorCode;
                }
            }
            match current_block_76 {
                7043617712618060937 => {
                    if BrotliSafeReadBits(br, 2 as libc::c_int as uint32_t, &mut bits)
                        == 0
                    {
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    if bits == 0 as libc::c_int as uint32_t {
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
                        return BROTLI_DECODER_SUCCESS;
                    }
                    (*s).set_size_nibbles(bits as uint8_t as libc::c_uint);
                    (*s)
                        .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_METADATA;
                    current_block_76 = 3065322521856595317;
                }
                14791804988756215412 => {
                    if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits)
                        == 0
                    {
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    if bits != 0 {
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
                        return BROTLI_DECODER_SUCCESS;
                    }
                    (*s)
                        .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;
                    current_block_76 = 5316138500539939593;
                }
                _ => {}
            }
            match current_block_76 {
                3065322521856595317 => {
                    i = (*s).loop_counter;
                    while i < (*s).size_nibbles() as libc::c_int {
                        if BrotliSafeReadBits(
                            br,
                            8 as libc::c_int as uint32_t,
                            &mut bits,
                        ) == 0
                        {
                            (*s).loop_counter = i;
                            return BROTLI_DECODER_NEEDS_MORE_INPUT;
                        }
                        if i + 1 as libc::c_int == (*s).size_nibbles() as libc::c_int
                            && (*s).size_nibbles() as libc::c_int > 1 as libc::c_int
                            && bits == 0 as libc::c_int as uint32_t
                        {
                            return BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE
                                as libc::c_int as BrotliDecoderErrorCode;
                        }
                        (*s).meta_block_remaining_len
                            |= (bits << i * 8 as libc::c_int) as libc::c_int;
                        i += 1;
                        i;
                    }
                    (*s).meta_block_remaining_len += 1;
                    (*s).meta_block_remaining_len;
                    (*s).substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
                    return BROTLI_DECODER_SUCCESS;
                }
                5316138500539939593 => {
                    if BrotliSafeReadBits(br, 2 as libc::c_int as uint32_t, &mut bits)
                        == 0
                    {
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    (*s)
                        .set_size_nibbles(
                            bits.wrapping_add(4 as libc::c_int as uint32_t) as uint8_t
                                as libc::c_uint,
                        );
                    (*s).loop_counter = 0 as libc::c_int;
                    if bits == 3 as libc::c_int as uint32_t {
                        (*s).set_is_metadata(1 as libc::c_int as libc::c_uint);
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_RESERVED;
                        current_block_76 = 17836213544692497527;
                    } else {
                        (*s)
                            .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_SIZE;
                        current_block_76 = 8307118956945566857;
                    }
                }
                _ => {}
            }
            match current_block_76 {
                8307118956945566857 => {
                    i = (*s).loop_counter;
                    while i < (*s).size_nibbles() as libc::c_int {
                        if BrotliSafeReadBits(
                            br,
                            4 as libc::c_int as uint32_t,
                            &mut bits,
                        ) == 0
                        {
                            (*s).loop_counter = i;
                            return BROTLI_DECODER_NEEDS_MORE_INPUT;
                        }
                        if i + 1 as libc::c_int == (*s).size_nibbles() as libc::c_int
                            && (*s).size_nibbles() as libc::c_int > 4 as libc::c_int
                            && bits == 0 as libc::c_int as uint32_t
                        {
                            return BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE
                                as libc::c_int as BrotliDecoderErrorCode;
                        }
                        (*s).meta_block_remaining_len
                            |= (bits << i * 4 as libc::c_int) as libc::c_int;
                        i += 1;
                        i;
                    }
                    (*s)
                        .substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED;
                }
                17836213544692497527 => {
                    break 's_305;
                }
                _ => {}
            }
            if (*s).is_last_metablock() == 0 {
                if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits) == 0 {
                    return BROTLI_DECODER_NEEDS_MORE_INPUT;
                }
                (*s)
                    .set_is_uncompressed(
                        (if bits != 0 { 1 as libc::c_int } else { 0 as libc::c_int })
                            as libc::c_uint,
                    );
            }
            (*s).meta_block_remaining_len += 1;
            (*s).meta_block_remaining_len;
            (*s).substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
            return BROTLI_DECODER_SUCCESS;
        }
    };
}
#[inline(always)]
unsafe extern "C" fn DecodeSymbol(
    mut bits: uint32_t,
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
) -> uint32_t {
    table = table.offset((bits & 0xff as libc::c_int as uint32_t) as isize);
    if (*table).bits as libc::c_uint > 8 as libc::c_uint {
        let mut nbits: uint32_t = ((*table).bits as libc::c_uint)
            .wrapping_sub(8 as libc::c_uint);
        BrotliDropBits(br, 8 as libc::c_uint);
        table = table
            .offset(
                ((*table).value as uint32_t)
                    .wrapping_add(bits >> 8 as libc::c_uint & BitMask(nbits)) as isize,
            );
    }
    BrotliDropBits(br, (*table).bits as uint32_t);
    return (*table).value as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn ReadSymbol(
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
) -> uint32_t {
    return DecodeSymbol(BrotliGet16BitsUnmasked(br), table, br);
}
#[inline(never)]
unsafe extern "C" fn SafeDecodeSymbol(
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
    mut result: *mut uint32_t,
) -> libc::c_int {
    let mut val: uint32_t = 0;
    let mut available_bits: uint32_t = BrotliGetAvailableBits(br);
    if available_bits == 0 as libc::c_int as uint32_t {
        if (*table).bits as libc::c_int == 0 as libc::c_int {
            *result = (*table).value as uint32_t;
            return 1 as libc::c_int;
        }
        return 0 as libc::c_int;
    }
    val = BrotliGetBitsUnmasked(br) as uint32_t;
    table = table.offset((val & 0xff as libc::c_int as uint32_t) as isize);
    if (*table).bits as libc::c_uint <= 8 as libc::c_uint {
        if (*table).bits as uint32_t <= available_bits {
            BrotliDropBits(br, (*table).bits as uint32_t);
            *result = (*table).value as uint32_t;
            return 1 as libc::c_int;
        } else {
            return 0 as libc::c_int
        }
    }
    if available_bits <= 8 as libc::c_uint {
        return 0 as libc::c_int;
    }
    val = (val & BitMask((*table).bits as uint32_t)) >> 8 as libc::c_uint;
    available_bits = (available_bits as libc::c_uint).wrapping_sub(8 as libc::c_uint)
        as uint32_t as uint32_t;
    table = table.offset(((*table).value as uint32_t).wrapping_add(val) as isize);
    if available_bits < (*table).bits as uint32_t {
        return 0 as libc::c_int;
    }
    BrotliDropBits(br, (8 as libc::c_uint).wrapping_add((*table).bits as libc::c_uint));
    *result = (*table).value as uint32_t;
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn SafeReadSymbol(
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
    mut result: *mut uint32_t,
) -> libc::c_int {
    let mut val: uint32_t = 0;
    if (BrotliSafeGetBits(br, 15 as libc::c_int as uint32_t, &mut val) != 0)
        as libc::c_int as libc::c_long != 0
    {
        *result = DecodeSymbol(val, table, br);
        return 1 as libc::c_int;
    }
    return SafeDecodeSymbol(table, br, result);
}
#[inline(always)]
unsafe extern "C" fn PreloadSymbol(
    mut safe: libc::c_int,
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
    mut bits: *mut uint32_t,
    mut value: *mut uint32_t,
) {
    if safe != 0 {
        return;
    }
    table = table.offset(BrotliGetBits(br, 8 as libc::c_uint) as isize);
    *bits = (*table).bits as uint32_t;
    *value = (*table).value as uint32_t;
}
#[inline(always)]
unsafe extern "C" fn ReadPreloadedSymbol(
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
    mut bits: *mut uint32_t,
    mut value: *mut uint32_t,
) -> uint32_t {
    let mut result: uint32_t = *value;
    if (*bits > 8 as libc::c_uint) as libc::c_int as libc::c_long != 0 {
        let mut val: uint32_t = BrotliGet16BitsUnmasked(br);
        let mut ext: *const HuffmanCode = table
            .offset((val & 0xff as libc::c_int as uint32_t) as isize)
            .offset(*value as isize);
        let mut mask: uint32_t = BitMask((*bits).wrapping_sub(8 as libc::c_uint));
        BrotliDropBits(br, 8 as libc::c_uint);
        ext = ext.offset((val >> 8 as libc::c_uint & mask) as isize);
        BrotliDropBits(br, (*ext).bits as uint32_t);
        result = (*ext).value as uint32_t;
    } else {
        BrotliDropBits(br, *bits);
    }
    PreloadSymbol(0 as libc::c_int, table, br, bits, value);
    return result;
}
#[inline(always)]
unsafe extern "C" fn Log2Floor(mut x: uint32_t) -> uint32_t {
    let mut result: uint32_t = 0 as libc::c_int as uint32_t;
    while x != 0 {
        x >>= 1 as libc::c_int;
        result = result.wrapping_add(1);
        result;
    }
    return result;
}
unsafe extern "C" fn ReadSimpleHuffmanSymbols(
    mut alphabet_size_max: uint32_t,
    mut alphabet_size_limit: uint32_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut max_bits: uint32_t = Log2Floor(
        alphabet_size_max.wrapping_sub(1 as libc::c_int as uint32_t),
    );
    let mut i: uint32_t = (*h).sub_loop_counter;
    let mut num_symbols: uint32_t = (*h).symbol;
    while i <= num_symbols {
        let mut v: uint32_t = 0;
        if (BrotliSafeReadBits(br, max_bits, &mut v) == 0) as libc::c_int as libc::c_long
            != 0
        {
            (*h).sub_loop_counter = i;
            (*h).substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_READ;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if v >= alphabet_size_limit {
            return BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET as libc::c_int
                as BrotliDecoderErrorCode;
        }
        (*h).symbols_lists_array[i as usize] = v as uint16_t;
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as uint32_t;
    while i < num_symbols {
        let mut k: uint32_t = i.wrapping_add(1 as libc::c_int as uint32_t);
        while k <= num_symbols {
            if (*h).symbols_lists_array[i as usize] as libc::c_int
                == (*h).symbols_lists_array[k as usize] as libc::c_int
            {
                return BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME as libc::c_int
                    as BrotliDecoderErrorCode;
            }
            k = k.wrapping_add(1);
            k;
        }
        i = i.wrapping_add(1);
        i;
    }
    return BROTLI_DECODER_SUCCESS;
}
#[inline(always)]
unsafe extern "C" fn ProcessSingleCodeLength(
    mut code_len: uint32_t,
    mut symbol: *mut uint32_t,
    mut repeat: *mut uint32_t,
    mut space: *mut uint32_t,
    mut prev_code_len: *mut uint32_t,
    mut symbol_lists: *mut uint16_t,
    mut code_length_histo: *mut uint16_t,
    mut next_symbol: *mut libc::c_int,
) {
    *repeat = 0 as libc::c_int as uint32_t;
    if code_len != 0 as libc::c_int as uint32_t {
        *symbol_lists
            .offset(
                *next_symbol.offset(code_len as isize) as isize,
            ) = *symbol as uint16_t;
        *next_symbol.offset(code_len as isize) = *symbol as libc::c_int;
        *prev_code_len = code_len;
        *space = (*space as libc::c_uint).wrapping_sub(32768 as libc::c_uint >> code_len)
            as uint32_t as uint32_t;
        let ref mut fresh0 = *code_length_histo.offset(code_len as isize);
        *fresh0 = (*fresh0).wrapping_add(1);
        *fresh0;
    }
    *symbol = (*symbol).wrapping_add(1);
    *symbol;
}
#[inline(always)]
unsafe extern "C" fn ProcessRepeatedCodeLength(
    mut code_len: uint32_t,
    mut repeat_delta: uint32_t,
    mut alphabet_size: uint32_t,
    mut symbol: *mut uint32_t,
    mut repeat: *mut uint32_t,
    mut space: *mut uint32_t,
    mut prev_code_len: *mut uint32_t,
    mut repeat_code_len: *mut uint32_t,
    mut symbol_lists: *mut uint16_t,
    mut code_length_histo: *mut uint16_t,
    mut next_symbol: *mut libc::c_int,
) {
    let mut old_repeat: uint32_t = 0;
    let mut extra_bits: uint32_t = 3 as libc::c_int as uint32_t;
    let mut new_len: uint32_t = 0 as libc::c_int as uint32_t;
    if code_len == 16 as libc::c_int as uint32_t {
        new_len = *prev_code_len;
        extra_bits = 2 as libc::c_int as uint32_t;
    }
    if *repeat_code_len != new_len {
        *repeat = 0 as libc::c_int as uint32_t;
        *repeat_code_len = new_len;
    }
    old_repeat = *repeat;
    if *repeat > 0 as libc::c_int as uint32_t {
        *repeat = (*repeat).wrapping_sub(2 as libc::c_int as uint32_t);
        *repeat <<= extra_bits;
    }
    *repeat = (*repeat as libc::c_uint)
        .wrapping_add(repeat_delta.wrapping_add(3 as libc::c_uint)) as uint32_t
        as uint32_t;
    repeat_delta = (*repeat).wrapping_sub(old_repeat);
    if (*symbol).wrapping_add(repeat_delta) > alphabet_size {
        *symbol = alphabet_size;
        *space = 0xfffff as libc::c_int as uint32_t;
        return;
    }
    if *repeat_code_len != 0 as libc::c_int as uint32_t {
        let mut last: libc::c_uint = (*symbol).wrapping_add(repeat_delta);
        let mut next: libc::c_int = *next_symbol.offset(*repeat_code_len as isize);
        loop {
            *symbol_lists.offset(next as isize) = *symbol as uint16_t;
            next = *symbol as libc::c_int;
            *symbol = (*symbol).wrapping_add(1);
            if !(*symbol != last) {
                break;
            }
        }
        *next_symbol.offset(*repeat_code_len as isize) = next;
        *space = (*space)
            .wrapping_sub(
                repeat_delta
                    << (15 as libc::c_int as uint32_t).wrapping_sub(*repeat_code_len),
            );
        *code_length_histo
            .offset(
                *repeat_code_len as isize,
            ) = (*code_length_histo.offset(*repeat_code_len as isize) as uint32_t)
            .wrapping_add(repeat_delta) as uint16_t;
    } else {
        *symbol = (*symbol).wrapping_add(repeat_delta);
    };
}
unsafe extern "C" fn ReadSymbolCodeLengths(
    mut alphabet_size: uint32_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut symbol: uint32_t = (*h).symbol;
    let mut repeat: uint32_t = (*h).repeat;
    let mut space: uint32_t = (*h).space;
    let mut prev_code_len: uint32_t = (*h).prev_code_len;
    let mut repeat_code_len: uint32_t = (*h).repeat_code_len;
    let mut symbol_lists: *mut uint16_t = (*h).symbol_lists;
    let mut code_length_histo: *mut uint16_t = ((*h).code_length_histo).as_mut_ptr();
    let mut next_symbol: *mut libc::c_int = ((*h).next_symbol).as_mut_ptr();
    if BrotliWarmupBitReader(br) == 0 {
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    while symbol < alphabet_size && space > 0 as libc::c_int as uint32_t {
        let mut p: *const HuffmanCode = ((*h).table).as_mut_ptr();
        let mut code_len: uint32_t = 0;
        if BrotliCheckInputAmount(
            br,
            ::core::mem::size_of::<uint64_t>() as libc::c_ulong >> 1 as libc::c_int,
        ) == 0
        {
            (*h).symbol = symbol;
            (*h).repeat = repeat;
            (*h).prev_code_len = prev_code_len;
            (*h).repeat_code_len = repeat_code_len;
            (*h).space = space;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        BrotliFillBitWindow16(br);
        p = p
            .offset(
                (BrotliGetBitsUnmasked(br)
                    & BitMask(5 as libc::c_int as uint32_t) as uint64_t) as isize,
            );
        BrotliDropBits(br, (*p).bits as uint32_t);
        code_len = (*p).value as uint32_t;
        if code_len < 16 as libc::c_int as uint32_t {
            ProcessSingleCodeLength(
                code_len,
                &mut symbol,
                &mut repeat,
                &mut space,
                &mut prev_code_len,
                symbol_lists,
                code_length_histo,
                next_symbol,
            );
        } else {
            let mut extra_bits: uint32_t = (if code_len == 16 as libc::c_int as uint32_t
            {
                2 as libc::c_int
            } else {
                3 as libc::c_int
            }) as uint32_t;
            let mut repeat_delta: uint32_t = BrotliGetBitsUnmasked(br) as uint32_t
                & BitMask(extra_bits);
            BrotliDropBits(br, extra_bits);
            ProcessRepeatedCodeLength(
                code_len,
                repeat_delta,
                alphabet_size,
                &mut symbol,
                &mut repeat,
                &mut space,
                &mut prev_code_len,
                &mut repeat_code_len,
                symbol_lists,
                code_length_histo,
                next_symbol,
            );
        }
    }
    (*h).space = space;
    return BROTLI_DECODER_SUCCESS;
}
unsafe extern "C" fn SafeReadSymbolCodeLengths(
    mut alphabet_size: uint32_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut get_byte: libc::c_int = 0 as libc::c_int;
    while (*h).symbol < alphabet_size && (*h).space > 0 as libc::c_int as uint32_t {
        let mut p: *const HuffmanCode = ((*h).table).as_mut_ptr();
        let mut code_len: uint32_t = 0;
        let mut available_bits: uint32_t = 0;
        let mut bits: uint32_t = 0 as libc::c_int as uint32_t;
        if get_byte != 0 && BrotliPullByte(br) == 0 {
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        get_byte = 0 as libc::c_int;
        available_bits = BrotliGetAvailableBits(br);
        if available_bits != 0 as libc::c_int as uint32_t {
            bits = BrotliGetBitsUnmasked(br) as uint32_t;
        }
        p = p.offset((bits & BitMask(5 as libc::c_int as uint32_t)) as isize);
        if (*p).bits as uint32_t > available_bits {
            get_byte = 1 as libc::c_int;
        } else {
            code_len = (*p).value as uint32_t;
            if code_len < 16 as libc::c_int as uint32_t {
                BrotliDropBits(br, (*p).bits as uint32_t);
                ProcessSingleCodeLength(
                    code_len,
                    &mut (*h).symbol,
                    &mut (*h).repeat,
                    &mut (*h).space,
                    &mut (*h).prev_code_len,
                    (*h).symbol_lists,
                    ((*h).code_length_histo).as_mut_ptr(),
                    ((*h).next_symbol).as_mut_ptr(),
                );
            } else {
                let mut extra_bits: uint32_t = code_len.wrapping_sub(14 as libc::c_uint);
                let mut repeat_delta: uint32_t = bits >> (*p).bits as libc::c_int
                    & BitMask(extra_bits);
                if available_bits < ((*p).bits as uint32_t).wrapping_add(extra_bits) {
                    get_byte = 1 as libc::c_int;
                } else {
                    BrotliDropBits(br, ((*p).bits as uint32_t).wrapping_add(extra_bits));
                    ProcessRepeatedCodeLength(
                        code_len,
                        repeat_delta,
                        alphabet_size,
                        &mut (*h).symbol,
                        &mut (*h).repeat,
                        &mut (*h).space,
                        &mut (*h).prev_code_len,
                        &mut (*h).repeat_code_len,
                        (*h).symbol_lists,
                        ((*h).code_length_histo).as_mut_ptr(),
                        ((*h).next_symbol).as_mut_ptr(),
                    );
                }
            }
        }
    }
    return BROTLI_DECODER_SUCCESS;
}
unsafe extern "C" fn ReadCodeLengthCodeLengths(
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut num_codes: uint32_t = (*h).repeat;
    let mut space: libc::c_uint = (*h).space;
    let mut i: uint32_t = (*h).sub_loop_counter;
    while i < (17 as libc::c_int + 1 as libc::c_int) as uint32_t {
        let code_len_idx: uint8_t = kCodeLengthCodeOrder[i as usize];
        let mut ix: uint32_t = 0;
        let mut v: uint32_t = 0;
        if (BrotliSafeGetBits(br, 4 as libc::c_int as uint32_t, &mut ix) == 0)
            as libc::c_int as libc::c_long != 0
        {
            let mut available_bits: uint32_t = BrotliGetAvailableBits(br);
            if available_bits != 0 as libc::c_int as uint32_t {
                ix = (BrotliGetBitsUnmasked(br) & 0xf as libc::c_int as uint64_t)
                    as uint32_t;
            } else {
                ix = 0 as libc::c_int as uint32_t;
            }
            if kCodeLengthPrefixLength[ix as usize] as uint32_t > available_bits {
                (*h).sub_loop_counter = i;
                (*h).repeat = num_codes;
                (*h).space = space;
                (*h).substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
                return BROTLI_DECODER_NEEDS_MORE_INPUT;
            }
        }
        v = kCodeLengthPrefixValue[ix as usize] as uint32_t;
        BrotliDropBits(br, kCodeLengthPrefixLength[ix as usize] as uint32_t);
        (*h).code_length_code_lengths[code_len_idx as usize] = v as uint8_t;
        if v != 0 as libc::c_int as uint32_t {
            space = space.wrapping_sub(32 as libc::c_uint >> v);
            num_codes = num_codes.wrapping_add(1);
            num_codes;
            (*h)
                .code_length_histo[v
                as usize] = ((*h).code_length_histo[v as usize]).wrapping_add(1);
            (*h).code_length_histo[v as usize];
            if space.wrapping_sub(1 as libc::c_uint) >= 32 as libc::c_uint {
                break;
            }
        }
        i = i.wrapping_add(1);
        i;
    }
    if !(num_codes == 1 as libc::c_int as uint32_t
        || space == 0 as libc::c_int as libc::c_uint)
    {
        return BROTLI_DECODER_ERROR_FORMAT_CL_SPACE as libc::c_int
            as BrotliDecoderErrorCode;
    }
    return BROTLI_DECODER_SUCCESS;
}
unsafe extern "C" fn ReadHuffmanCode(
    mut alphabet_size_max: uint32_t,
    mut alphabet_size_limit: uint32_t,
    mut table: *mut HuffmanCode,
    mut opt_table_size: *mut uint32_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut current_block_67: u64;
    loop {
        match (*h).substate_huffman as libc::c_uint {
            0 => {
                if BrotliSafeReadBits(
                    br,
                    2 as libc::c_int as uint32_t,
                    &mut (*h).sub_loop_counter,
                ) == 0
                {
                    return BROTLI_DECODER_NEEDS_MORE_INPUT;
                }
                if (*h).sub_loop_counter != 1 as libc::c_int as uint32_t {
                    (*h).space = 32 as libc::c_int as uint32_t;
                    (*h).repeat = 0 as libc::c_int as uint32_t;
                    memset(
                        &mut *((*h).code_length_histo)
                            .as_mut_ptr()
                            .offset(0 as libc::c_int as isize) as *mut uint16_t
                            as *mut libc::c_void,
                        0 as libc::c_int,
                        (::core::mem::size_of::<uint16_t>() as libc::c_ulong)
                            .wrapping_mul(
                                (5 as libc::c_int + 1 as libc::c_int) as libc::c_ulong,
                            ),
                    );
                    memset(
                        &mut *((*h).code_length_code_lengths)
                            .as_mut_ptr()
                            .offset(0 as libc::c_int as isize) as *mut uint8_t
                            as *mut libc::c_void,
                        0 as libc::c_int,
                        ::core::mem::size_of::<[uint8_t; 18]>() as libc::c_ulong,
                    );
                    (*h).substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
                    continue;
                } else {
                    current_block_67 = 14009236489294985851;
                }
            }
            1 => {
                current_block_67 = 14009236489294985851;
            }
            2 => {
                current_block_67 = 9099637043220123396;
            }
            3 => {
                current_block_67 = 3706391310672556422;
            }
            4 => {
                let mut i: uint32_t = 0;
                let mut result_0: BrotliDecoderErrorCode = ReadCodeLengthCodeLengths(s);
                if result_0 as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                    return result_0;
                }
                BrotliBuildCodeLengthsHuffmanTable(
                    ((*h).table).as_mut_ptr(),
                    ((*h).code_length_code_lengths).as_mut_ptr(),
                    ((*h).code_length_histo).as_mut_ptr(),
                );
                memset(
                    &mut *((*h).code_length_histo)
                        .as_mut_ptr()
                        .offset(0 as libc::c_int as isize) as *mut uint16_t
                        as *mut libc::c_void,
                    0 as libc::c_int,
                    ::core::mem::size_of::<[uint16_t; 16]>() as libc::c_ulong,
                );
                i = 0 as libc::c_int as uint32_t;
                while i <= 15 as libc::c_int as uint32_t {
                    (*h)
                        .next_symbol[i
                        as usize] = i as libc::c_int
                        - (15 as libc::c_int + 1 as libc::c_int);
                    *((*h).symbol_lists)
                        .offset(
                            (*h).next_symbol[i as usize] as isize,
                        ) = 0xffff as libc::c_int as uint16_t;
                    i = i.wrapping_add(1);
                    i;
                }
                (*h).symbol = 0 as libc::c_int as uint32_t;
                (*h).prev_code_len = 8 as libc::c_int as uint32_t;
                (*h).repeat = 0 as libc::c_int as uint32_t;
                (*h).repeat_code_len = 0 as libc::c_int as uint32_t;
                (*h).space = 32768 as libc::c_int as uint32_t;
                (*h).substate_huffman = BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS;
                current_block_67 = 17598674192687608949;
            }
            5 => {
                current_block_67 = 17598674192687608949;
            }
            _ => {
                return BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                    as BrotliDecoderErrorCode;
            }
        }
        match current_block_67 {
            14009236489294985851 => {
                if BrotliSafeReadBits(br, 2 as libc::c_int as uint32_t, &mut (*h).symbol)
                    == 0
                {
                    (*h).substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_SIZE;
                    return BROTLI_DECODER_NEEDS_MORE_INPUT;
                }
                (*h).sub_loop_counter = 0 as libc::c_int as uint32_t;
                current_block_67 = 9099637043220123396;
            }
            17598674192687608949 => {
                let mut table_size_0: uint32_t = 0;
                let mut result_1: BrotliDecoderErrorCode = ReadSymbolCodeLengths(
                    alphabet_size_limit,
                    s,
                );
                if result_1 as libc::c_int
                    == BROTLI_DECODER_NEEDS_MORE_INPUT as libc::c_int
                {
                    result_1 = SafeReadSymbolCodeLengths(alphabet_size_limit, s);
                }
                if result_1 as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                    return result_1;
                }
                if (*h).space != 0 as libc::c_int as uint32_t {
                    return BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE as libc::c_int
                        as BrotliDecoderErrorCode;
                }
                table_size_0 = BrotliBuildHuffmanTable(
                    table,
                    8 as libc::c_uint as libc::c_int,
                    (*h).symbol_lists,
                    ((*h).code_length_histo).as_mut_ptr(),
                );
                if !opt_table_size.is_null() {
                    *opt_table_size = table_size_0;
                }
                (*h).substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
                return BROTLI_DECODER_SUCCESS;
            }
            _ => {}
        }
        match current_block_67 {
            9099637043220123396 => {
                let mut result: BrotliDecoderErrorCode = ReadSimpleHuffmanSymbols(
                    alphabet_size_max,
                    alphabet_size_limit,
                    s,
                );
                if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                    return result;
                }
            }
            _ => {}
        }
        let mut table_size: uint32_t = 0;
        if (*h).symbol == 3 as libc::c_int as uint32_t {
            let mut bits: uint32_t = 0;
            if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits) == 0 {
                (*h).substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_BUILD;
                return BROTLI_DECODER_NEEDS_MORE_INPUT;
            }
            (*h).symbol = ((*h).symbol).wrapping_add(bits);
        }
        table_size = BrotliBuildSimpleHuffmanTable(
            table,
            8 as libc::c_uint as libc::c_int,
            ((*h).symbols_lists_array).as_mut_ptr(),
            (*h).symbol,
        );
        if !opt_table_size.is_null() {
            *opt_table_size = table_size;
        }
        (*h).substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
    };
}
#[inline(always)]
unsafe extern "C" fn ReadBlockLength(
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
) -> uint32_t {
    let mut code: uint32_t = 0;
    let mut nbits: uint32_t = 0;
    code = ReadSymbol(table, br);
    nbits = _kBrotliPrefixCodeRanges[code as usize].nbits as uint32_t;
    return (_kBrotliPrefixCodeRanges[code as usize].offset as uint32_t)
        .wrapping_add(BrotliReadBits24(br, nbits));
}
#[inline(always)]
unsafe extern "C" fn SafeReadBlockLength(
    mut s: *mut BrotliDecoderStateInternal,
    mut result: *mut uint32_t,
    mut table: *const HuffmanCode,
    mut br: *mut BrotliBitReader,
) -> libc::c_int {
    let mut index: uint32_t = 0;
    if (*s).substate_read_block_length as libc::c_uint
        == BROTLI_STATE_READ_BLOCK_LENGTH_NONE as libc::c_int as libc::c_uint
    {
        if SafeReadSymbol(table, br, &mut index) == 0 {
            return 0 as libc::c_int;
        }
    } else {
        index = (*s).block_length_index;
    }
    let mut bits: uint32_t = 0;
    let mut nbits: uint32_t = _kBrotliPrefixCodeRanges[index as usize].nbits as uint32_t;
    let mut offset: uint32_t = _kBrotliPrefixCodeRanges[index as usize].offset
        as uint32_t;
    if BrotliSafeReadBits(br, nbits, &mut bits) == 0 {
        (*s).block_length_index = index;
        (*s).substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX;
        return 0 as libc::c_int;
    }
    *result = offset.wrapping_add(bits);
    (*s).substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
    return 1 as libc::c_int;
}
#[inline(never)]
unsafe extern "C" fn InverseMoveToFrontTransform(
    mut v: *mut uint8_t,
    mut v_len: uint32_t,
    mut state: *mut BrotliDecoderStateInternal,
) {
    let mut i: uint32_t = 1 as libc::c_int as uint32_t;
    let mut upper_bound: uint32_t = (*state).mtf_upper_bound;
    let mut mtf: *mut uint32_t = &mut *((*state).mtf)
        .as_mut_ptr()
        .offset(1 as libc::c_int as isize) as *mut uint32_t;
    let mut mtf_u8: *mut uint8_t = mtf as *mut uint8_t;
    let b0123: [uint8_t; 4] = [
        0 as libc::c_int as uint8_t,
        1 as libc::c_int as uint8_t,
        2 as libc::c_int as uint8_t,
        3 as libc::c_int as uint8_t,
    ];
    let mut pattern: uint32_t = 0;
    memcpy(
        &mut pattern as *mut uint32_t as *mut libc::c_void,
        &b0123 as *const [uint8_t; 4] as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    );
    *mtf.offset(0 as libc::c_int as isize) = pattern;
    loop {
        pattern = pattern.wrapping_add(0x4040404 as libc::c_int as uint32_t);
        *mtf.offset(i as isize) = pattern;
        i = i.wrapping_add(1);
        i;
        if !(i <= upper_bound) {
            break;
        }
    }
    upper_bound = 0 as libc::c_int as uint32_t;
    i = 0 as libc::c_int as uint32_t;
    while i < v_len {
        let mut index: libc::c_int = *v.offset(i as isize) as libc::c_int;
        let mut value: uint8_t = *mtf_u8.offset(index as isize);
        upper_bound |= *v.offset(i as isize) as uint32_t;
        *v.offset(i as isize) = value;
        *mtf_u8.offset(-(1 as libc::c_int) as isize) = value;
        loop {
            index -= 1;
            index;
            *mtf_u8
                .offset(
                    (index + 1 as libc::c_int) as isize,
                ) = *mtf_u8.offset(index as isize);
            if !(index >= 0 as libc::c_int) {
                break;
            }
        }
        i = i.wrapping_add(1);
        i;
    }
    (*state).mtf_upper_bound = upper_bound >> 2 as libc::c_int;
}
unsafe extern "C" fn HuffmanTreeGroupDecode(
    mut group: *mut HuffmanTreeGroup,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    if (*h).substate_tree_group as libc::c_uint
        != BROTLI_STATE_TREE_GROUP_LOOP as libc::c_int as libc::c_uint
    {
        (*h).next = (*group).codes;
        (*h).htree_index = 0 as libc::c_int;
        (*h).substate_tree_group = BROTLI_STATE_TREE_GROUP_LOOP;
    }
    while (*h).htree_index < (*group).num_htrees as libc::c_int {
        let mut table_size: uint32_t = 0;
        let mut result: BrotliDecoderErrorCode = ReadHuffmanCode(
            (*group).alphabet_size_max as uint32_t,
            (*group).alphabet_size_limit as uint32_t,
            (*h).next,
            &mut table_size,
            s,
        );
        if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
            return result;
        }
        let ref mut fresh1 = *((*group).htrees).offset((*h).htree_index as isize);
        *fresh1 = (*h).next;
        (*h).next = ((*h).next).offset(table_size as isize);
        (*h).htree_index += 1;
        (*h).htree_index;
    }
    (*h).substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
    return BROTLI_DECODER_SUCCESS;
}
unsafe extern "C" fn DecodeContextMap(
    mut context_map_size: uint32_t,
    mut num_htrees: *mut uint32_t,
    mut context_map_arg: *mut *mut uint8_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut result: BrotliDecoderErrorCode = BROTLI_DECODER_SUCCESS;
    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
    let mut current_block_72: u64;
    match (*h).substate_context_map as libc::c_int {
        0 => {
            result = DecodeVarLenUint8(s, br, num_htrees);
            if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                return result;
            }
            *num_htrees = (*num_htrees).wrapping_add(1);
            *num_htrees;
            (*h).context_index = 0 as libc::c_int as uint32_t;
            *context_map_arg = ((*s).alloc_func)
                .expect(
                    "non-null function pointer",
                )((*s).memory_manager_opaque, context_map_size as size_t)
                as *mut uint8_t;
            if (*context_map_arg).is_null() {
                return BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP as libc::c_int
                    as BrotliDecoderErrorCode;
            }
            if *num_htrees <= 1 as libc::c_int as uint32_t {
                memset(
                    *context_map_arg as *mut libc::c_void,
                    0 as libc::c_int,
                    context_map_size as size_t,
                );
                return BROTLI_DECODER_SUCCESS;
            }
            (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_READ_PREFIX;
            current_block_72 = 6218433422003487270;
        }
        1 => {
            current_block_72 = 6218433422003487270;
        }
        2 => {
            current_block_72 = 6128560643697369861;
        }
        3 => {
            current_block_72 = 9350638009254788289;
        }
        4 => {
            current_block_72 = 2412100623285860292;
        }
        _ => {
            return BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                as BrotliDecoderErrorCode;
        }
    }
    match current_block_72 {
        6218433422003487270 => {
            let mut bits: uint32_t = 0;
            if BrotliSafeGetBits(br, 5 as libc::c_int as uint32_t, &mut bits) == 0 {
                return BROTLI_DECODER_NEEDS_MORE_INPUT;
            }
            if bits & 1 as libc::c_int as uint32_t != 0 as libc::c_int as uint32_t {
                (*h)
                    .max_run_length_prefix = (bits >> 1 as libc::c_int)
                    .wrapping_add(1 as libc::c_int as uint32_t);
                BrotliDropBits(br, 5 as libc::c_int as uint32_t);
            } else {
                (*h).max_run_length_prefix = 0 as libc::c_int as uint32_t;
                BrotliDropBits(br, 1 as libc::c_int as uint32_t);
            }
            (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_HUFFMAN;
            current_block_72 = 6128560643697369861;
        }
        _ => {}
    }
    match current_block_72 {
        6128560643697369861 => {
            let mut alphabet_size: uint32_t = (*num_htrees)
                .wrapping_add((*h).max_run_length_prefix);
            result = ReadHuffmanCode(
                alphabet_size,
                alphabet_size,
                ((*h).context_map_table).as_mut_ptr(),
                0 as *mut uint32_t,
                s,
            );
            if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                return result;
            }
            (*h).code = 0xffff as libc::c_int as uint32_t;
            (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_DECODE;
            current_block_72 = 9350638009254788289;
        }
        _ => {}
    }
    match current_block_72 {
        9350638009254788289 => {
            let mut context_index: uint32_t = (*h).context_index;
            let mut max_run_length_prefix: uint32_t = (*h).max_run_length_prefix;
            let mut context_map: *mut uint8_t = *context_map_arg;
            let mut code: uint32_t = (*h).code;
            let mut skip_preamble: libc::c_int = (code
                != 0xffff as libc::c_int as uint32_t) as libc::c_int;
            while context_index < context_map_size || skip_preamble != 0 {
                if skip_preamble == 0 {
                    if SafeReadSymbol(
                        ((*h).context_map_table).as_mut_ptr(),
                        br,
                        &mut code,
                    ) == 0
                    {
                        (*h).code = 0xffff as libc::c_int as uint32_t;
                        (*h).context_index = context_index;
                        return BROTLI_DECODER_NEEDS_MORE_INPUT;
                    }
                    if code == 0 as libc::c_int as uint32_t {
                        let fresh2 = context_index;
                        context_index = context_index.wrapping_add(1);
                        *context_map
                            .offset(fresh2 as isize) = 0 as libc::c_int as uint8_t;
                        continue;
                    } else if code > max_run_length_prefix {
                        let fresh3 = context_index;
                        context_index = context_index.wrapping_add(1);
                        *context_map
                            .offset(
                                fresh3 as isize,
                            ) = code.wrapping_sub(max_run_length_prefix) as uint8_t;
                        continue;
                    }
                } else {
                    skip_preamble = 0 as libc::c_int;
                }
                let mut reps: uint32_t = 0;
                if BrotliSafeReadBits(br, code, &mut reps) == 0 {
                    (*h).code = code;
                    (*h).context_index = context_index;
                    return BROTLI_DECODER_NEEDS_MORE_INPUT;
                }
                reps = (reps as libc::c_uint).wrapping_add((1 as libc::c_uint) << code)
                    as uint32_t as uint32_t;
                if context_index.wrapping_add(reps) > context_map_size {
                    return BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT as libc::c_int
                        as BrotliDecoderErrorCode;
                }
                loop {
                    let fresh4 = context_index;
                    context_index = context_index.wrapping_add(1);
                    *context_map.offset(fresh4 as isize) = 0 as libc::c_int as uint8_t;
                    reps = reps.wrapping_sub(1);
                    if !(reps != 0) {
                        break;
                    }
                }
            }
        }
        _ => {}
    }
    let mut bits_0: uint32_t = 0;
    if BrotliSafeReadBits(br, 1 as libc::c_int as uint32_t, &mut bits_0) == 0 {
        (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_TRANSFORM;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    if bits_0 != 0 as libc::c_int as uint32_t {
        InverseMoveToFrontTransform(*context_map_arg, context_map_size, s);
    }
    (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
    return BROTLI_DECODER_SUCCESS;
}
#[inline(always)]
unsafe extern "C" fn DecodeBlockTypeAndLength(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
    mut tree_type: libc::c_int,
) -> libc::c_int {
    let mut max_block_type: uint32_t = (*s).num_block_types[tree_type as usize];
    let mut type_tree: *const HuffmanCode = &mut *((*s).block_type_trees)
        .offset((tree_type * 632 as libc::c_int) as isize) as *mut HuffmanCode;
    let mut len_tree: *const HuffmanCode = &mut *((*s).block_len_trees)
        .offset((tree_type * 396 as libc::c_int) as isize) as *mut HuffmanCode;
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut ringbuffer: *mut uint32_t = &mut *((*s).block_type_rb)
        .as_mut_ptr()
        .offset((tree_type * 2 as libc::c_int) as isize) as *mut uint32_t;
    let mut block_type: uint32_t = 0;
    if max_block_type <= 1 as libc::c_int as uint32_t {
        return 0 as libc::c_int;
    }
    if safe == 0 {
        block_type = ReadSymbol(type_tree, br);
        (*s).block_length[tree_type as usize] = ReadBlockLength(len_tree, br);
    } else {
        let mut memento: BrotliBitReaderState = BrotliBitReaderState {
            val_: 0,
            bit_pos_: 0,
            next_in: 0 as *const uint8_t,
            avail_in: 0,
        };
        BrotliBitReaderSaveState(br, &mut memento);
        if SafeReadSymbol(type_tree, br, &mut block_type) == 0 {
            return 0 as libc::c_int;
        }
        if SafeReadBlockLength(
            s,
            &mut *((*s).block_length).as_mut_ptr().offset(tree_type as isize),
            len_tree,
            br,
        ) == 0
        {
            (*s).substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
            BrotliBitReaderRestoreState(br, &mut memento);
            return 0 as libc::c_int;
        }
    }
    if block_type == 1 as libc::c_int as uint32_t {
        block_type = (*ringbuffer.offset(1 as libc::c_int as isize))
            .wrapping_add(1 as libc::c_int as uint32_t);
    } else if block_type == 0 as libc::c_int as uint32_t {
        block_type = *ringbuffer.offset(0 as libc::c_int as isize);
    } else {
        block_type = block_type.wrapping_sub(2 as libc::c_int as uint32_t);
    }
    if block_type >= max_block_type {
        block_type = block_type.wrapping_sub(max_block_type);
    }
    *ringbuffer
        .offset(
            0 as libc::c_int as isize,
        ) = *ringbuffer.offset(1 as libc::c_int as isize);
    *ringbuffer.offset(1 as libc::c_int as isize) = block_type;
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn DetectTrivialLiteralBlockTypes(
    mut s: *mut BrotliDecoderStateInternal,
) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < 8 as libc::c_int as size_t {
        (*s).trivial_literal_contexts[i as usize] = 0 as libc::c_int as uint32_t;
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < (*s).num_block_types[0 as libc::c_int as usize] as size_t {
        let mut offset: size_t = i << 6 as libc::c_int;
        let mut error: size_t = 0 as libc::c_int as size_t;
        let mut sample: size_t = *((*s).context_map).offset(offset as isize) as size_t;
        let mut j: size_t = 0;
        j = 0 as libc::c_int as size_t;
        while j < ((1 as libc::c_uint) << 6 as libc::c_int) as size_t {
            if 4 as libc::c_int & 1 as libc::c_int != 0 as libc::c_int {
                let fresh5 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh5) as isize)
                        as size_t ^ sample;
            }
            if 4 as libc::c_int & 2 as libc::c_int != 0 as libc::c_int {
                let fresh6 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh6) as isize)
                        as size_t ^ sample;
                let fresh7 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh7) as isize)
                        as size_t ^ sample;
            }
            if 4 as libc::c_int & 4 as libc::c_int != 0 as libc::c_int {
                let fresh8 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh8) as isize)
                        as size_t ^ sample;
                let fresh9 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh9) as isize)
                        as size_t ^ sample;
                let fresh10 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh10) as isize)
                        as size_t ^ sample;
                let fresh11 = j;
                j = j.wrapping_add(1);
                error
                    |= *((*s).context_map).offset(offset.wrapping_add(fresh11) as isize)
                        as size_t ^ sample;
            }
        }
        if error == 0 as libc::c_int as size_t {
            (*s).trivial_literal_contexts[(i >> 5 as libc::c_int) as usize]
                |= (1 as libc::c_uint) << (i & 31 as libc::c_int as size_t);
        }
        i = i.wrapping_add(1);
        i;
    }
}
#[inline(always)]
unsafe extern "C" fn PrepareLiteralDecoding(mut s: *mut BrotliDecoderStateInternal) {
    let mut context_mode: uint8_t = 0;
    let mut trivial: size_t = 0;
    let mut block_type: uint32_t = (*s).block_type_rb[1 as libc::c_int as usize];
    let mut context_offset: uint32_t = block_type << 6 as libc::c_int;
    (*s).context_map_slice = ((*s).context_map).offset(context_offset as isize);
    trivial = (*s).trivial_literal_contexts[(block_type >> 5 as libc::c_int) as usize]
        as size_t;
    (*s)
        .trivial_literal_context = (trivial
        >> (block_type & 31 as libc::c_int as uint32_t) & 1 as libc::c_int as size_t)
        as libc::c_int;
    (*s)
        .literal_htree = *((*s).literal_hgroup.htrees)
        .offset(*((*s).context_map_slice).offset(0 as libc::c_int as isize) as isize);
    context_mode = (*((*s).context_modes).offset(block_type as isize) as libc::c_int
        & 3 as libc::c_int) as uint8_t;
    (*s)
        .context_lookup = &*_kBrotliContextLookupTable
        .as_ptr()
        .offset(((context_mode as libc::c_int) << 9 as libc::c_int) as isize)
        as *const uint8_t;
}
#[inline(always)]
unsafe extern "C" fn DecodeLiteralBlockSwitchInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    if DecodeBlockTypeAndLength(safe, s, 0 as libc::c_int) == 0 {
        return 0 as libc::c_int;
    }
    PrepareLiteralDecoding(s);
    return 1 as libc::c_int;
}
#[inline(never)]
unsafe extern "C" fn DecodeLiteralBlockSwitch(mut s: *mut BrotliDecoderStateInternal) {
    DecodeLiteralBlockSwitchInternal(0 as libc::c_int, s);
}
#[inline(never)]
unsafe extern "C" fn SafeDecodeLiteralBlockSwitch(
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    return DecodeLiteralBlockSwitchInternal(1 as libc::c_int, s);
}
#[inline(always)]
unsafe extern "C" fn DecodeCommandBlockSwitchInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    if DecodeBlockTypeAndLength(safe, s, 1 as libc::c_int) == 0 {
        return 0 as libc::c_int;
    }
    (*s)
        .htree_command = *((*s).insert_copy_hgroup.htrees)
        .offset((*s).block_type_rb[3 as libc::c_int as usize] as isize);
    return 1 as libc::c_int;
}
#[inline(never)]
unsafe extern "C" fn DecodeCommandBlockSwitch(mut s: *mut BrotliDecoderStateInternal) {
    DecodeCommandBlockSwitchInternal(0 as libc::c_int, s);
}
#[inline(never)]
unsafe extern "C" fn SafeDecodeCommandBlockSwitch(
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    return DecodeCommandBlockSwitchInternal(1 as libc::c_int, s);
}
#[inline(always)]
unsafe extern "C" fn DecodeDistanceBlockSwitchInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    if DecodeBlockTypeAndLength(safe, s, 2 as libc::c_int) == 0 {
        return 0 as libc::c_int;
    }
    (*s)
        .dist_context_map_slice = ((*s).dist_context_map)
        .offset(
            ((*s).block_type_rb[5 as libc::c_int as usize] << 2 as libc::c_int) as isize,
        );
    (*s)
        .dist_htree_index = *((*s).dist_context_map_slice)
        .offset((*s).distance_context as isize);
    return 1 as libc::c_int;
}
#[inline(never)]
unsafe extern "C" fn DecodeDistanceBlockSwitch(mut s: *mut BrotliDecoderStateInternal) {
    DecodeDistanceBlockSwitchInternal(0 as libc::c_int, s);
}
#[inline(never)]
unsafe extern "C" fn SafeDecodeDistanceBlockSwitch(
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    return DecodeDistanceBlockSwitchInternal(1 as libc::c_int, s);
}
unsafe extern "C" fn UnwrittenBytes(
    mut s: *const BrotliDecoderStateInternal,
    mut wrap: libc::c_int,
) -> size_t {
    let mut pos: size_t = if wrap != 0 && (*s).pos > (*s).ringbuffer_size {
        (*s).ringbuffer_size as size_t
    } else {
        (*s).pos as size_t
    };
    let mut partial_pos_rb: size_t = ((*s).rb_roundtrips
        * (*s).ringbuffer_size as size_t)
        .wrapping_add(pos);
    return partial_pos_rb.wrapping_sub((*s).partial_pos_out);
}
#[inline(never)]
unsafe extern "C" fn WriteRingBuffer(
    mut s: *mut BrotliDecoderStateInternal,
    mut available_out: *mut size_t,
    mut next_out: *mut *mut uint8_t,
    mut total_out: *mut size_t,
    mut force: libc::c_int,
) -> BrotliDecoderErrorCode {
    let mut start: *mut uint8_t = ((*s).ringbuffer)
        .offset(((*s).partial_pos_out & (*s).ringbuffer_mask as size_t) as isize);
    let mut to_write: size_t = UnwrittenBytes(s, 1 as libc::c_int);
    let mut num_written: size_t = *available_out;
    if num_written > to_write {
        num_written = to_write;
    }
    if (*s).meta_block_remaining_len < 0 as libc::c_int {
        return BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1 as libc::c_int
            as BrotliDecoderErrorCode;
    }
    if !next_out.is_null() && (*next_out).is_null() {
        *next_out = start;
    } else if !next_out.is_null() {
        memcpy(
            *next_out as *mut libc::c_void,
            start as *const libc::c_void,
            num_written,
        );
        *next_out = (*next_out).offset(num_written as isize);
    }
    *available_out = (*available_out).wrapping_sub(num_written);
    (*s).partial_pos_out = ((*s).partial_pos_out).wrapping_add(num_written);
    if !total_out.is_null() {
        *total_out = (*s).partial_pos_out;
    }
    if num_written < to_write {
        if (*s).ringbuffer_size == (1 as libc::c_int) << (*s).window_bits || force != 0 {
            return BROTLI_DECODER_NEEDS_MORE_OUTPUT
        } else {
            return BROTLI_DECODER_SUCCESS
        }
    }
    if (*s).ringbuffer_size == (1 as libc::c_int) << (*s).window_bits
        && (*s).pos >= (*s).ringbuffer_size
    {
        (*s).pos -= (*s).ringbuffer_size;
        (*s).rb_roundtrips = ((*s).rb_roundtrips).wrapping_add(1);
        (*s).rb_roundtrips;
        (*s)
            .set_should_wrap_ringbuffer(
                (if (*s).pos as size_t != 0 as libc::c_int as size_t {
                    1 as libc::c_int
                } else {
                    0 as libc::c_int
                }) as libc::c_uint,
            );
    }
    return BROTLI_DECODER_SUCCESS;
}
#[inline(never)]
unsafe extern "C" fn WrapRingBuffer(mut s: *mut BrotliDecoderStateInternal) {
    if (*s).should_wrap_ringbuffer() != 0 {
        memcpy(
            (*s).ringbuffer as *mut libc::c_void,
            (*s).ringbuffer_end as *const libc::c_void,
            (*s).pos as size_t,
        );
        (*s).set_should_wrap_ringbuffer(0 as libc::c_int as libc::c_uint);
    }
}
#[inline(never)]
unsafe extern "C" fn BrotliEnsureRingBuffer(
    mut s: *mut BrotliDecoderStateInternal,
) -> libc::c_int {
    let mut old_ringbuffer: *mut uint8_t = (*s).ringbuffer;
    if (*s).ringbuffer_size == (*s).new_ringbuffer_size {
        return 1 as libc::c_int;
    }
    (*s)
        .ringbuffer = ((*s).alloc_func)
        .expect(
            "non-null function pointer",
        )(
        (*s).memory_manager_opaque,
        ((*s).new_ringbuffer_size as size_t)
            .wrapping_add(kRingBufferWriteAheadSlack as size_t),
    ) as *mut uint8_t;
    if ((*s).ringbuffer).is_null() {
        (*s).ringbuffer = old_ringbuffer;
        return 0 as libc::c_int;
    }
    *((*s).ringbuffer)
        .offset(
            ((*s).new_ringbuffer_size - 2 as libc::c_int) as isize,
        ) = 0 as libc::c_int as uint8_t;
    *((*s).ringbuffer)
        .offset(
            ((*s).new_ringbuffer_size - 1 as libc::c_int) as isize,
        ) = 0 as libc::c_int as uint8_t;
    if !old_ringbuffer.is_null() {
        memcpy(
            (*s).ringbuffer as *mut libc::c_void,
            old_ringbuffer as *const libc::c_void,
            (*s).pos as size_t,
        );
        ((*s).free_func)
            .expect(
                "non-null function pointer",
            )((*s).memory_manager_opaque, old_ringbuffer as *mut libc::c_void);
        old_ringbuffer = 0 as *mut uint8_t;
    }
    (*s).ringbuffer_size = (*s).new_ringbuffer_size;
    (*s).ringbuffer_mask = (*s).new_ringbuffer_size - 1 as libc::c_int;
    (*s).ringbuffer_end = ((*s).ringbuffer).offset((*s).ringbuffer_size as isize);
    return 1 as libc::c_int;
}
#[inline(never)]
unsafe extern "C" fn CopyUncompressedBlockToOutput(
    mut available_out: *mut size_t,
    mut next_out: *mut *mut uint8_t,
    mut total_out: *mut size_t,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    if BrotliEnsureRingBuffer(s) == 0 {
        return BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1 as libc::c_int
            as BrotliDecoderErrorCode;
    }
    loop {
        let mut current_block_27: u64;
        match (*s).substate_uncompressed as libc::c_uint {
            0 => {
                let mut nbytes: libc::c_int = BrotliGetRemainingBytes(&mut (*s).br)
                    as libc::c_int;
                if nbytes > (*s).meta_block_remaining_len {
                    nbytes = (*s).meta_block_remaining_len;
                }
                if (*s).pos + nbytes > (*s).ringbuffer_size {
                    nbytes = (*s).ringbuffer_size - (*s).pos;
                }
                BrotliCopyBytes(
                    &mut *((*s).ringbuffer).offset((*s).pos as isize),
                    &mut (*s).br,
                    nbytes as size_t,
                );
                (*s).pos += nbytes;
                (*s).meta_block_remaining_len -= nbytes;
                if (*s).pos < (1 as libc::c_int) << (*s).window_bits {
                    if (*s).meta_block_remaining_len == 0 as libc::c_int {
                        return BROTLI_DECODER_SUCCESS;
                    }
                    return BROTLI_DECODER_NEEDS_MORE_INPUT;
                }
                (*s).substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_WRITE;
                current_block_27 = 7149356873433890176;
            }
            1 => {
                current_block_27 = 7149356873433890176;
            }
            _ => {
                current_block_27 = 11298138898191919651;
            }
        }
        match current_block_27 {
            7149356873433890176 => {
                let mut result: BrotliDecoderErrorCode = BROTLI_DECODER_NO_ERROR;
                result = WriteRingBuffer(
                    s,
                    available_out,
                    next_out,
                    total_out,
                    0 as libc::c_int,
                );
                if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                    return result;
                }
                if (*s).ringbuffer_size == (1 as libc::c_int) << (*s).window_bits {
                    (*s).max_distance = (*s).max_backward_distance;
                }
                (*s).substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
            }
            _ => {}
        }
    };
}
#[inline(never)]
unsafe extern "C" fn BrotliCalculateRingBufferSize(
    mut s: *mut BrotliDecoderStateInternal,
) {
    let mut window_size: libc::c_int = (1 as libc::c_int) << (*s).window_bits;
    let mut new_ringbuffer_size: libc::c_int = window_size;
    let mut min_size: libc::c_int = if (*s).ringbuffer_size != 0 {
        (*s).ringbuffer_size
    } else {
        1024 as libc::c_int
    };
    let mut output_size: libc::c_int = 0;
    if (*s).ringbuffer_size == window_size {
        return;
    }
    if (*s).is_metadata() != 0 {
        return;
    }
    if ((*s).ringbuffer).is_null() {
        output_size = 0 as libc::c_int;
    } else {
        output_size = (*s).pos;
    }
    output_size += (*s).meta_block_remaining_len;
    min_size = if min_size < output_size { output_size } else { min_size };
    if (*s).canny_ringbuffer_allocation() != 0 {
        while new_ringbuffer_size >> 1 as libc::c_int >= min_size {
            new_ringbuffer_size >>= 1 as libc::c_int;
        }
    }
    (*s).new_ringbuffer_size = new_ringbuffer_size;
}
unsafe extern "C" fn ReadContextModes(
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    let mut i: libc::c_int = (*s).loop_counter;
    while i < (*s).num_block_types[0 as libc::c_int as usize] as libc::c_int {
        let mut bits: uint32_t = 0;
        if BrotliSafeReadBits(br, 2 as libc::c_int as uint32_t, &mut bits) == 0 {
            (*s).loop_counter = i;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        *((*s).context_modes).offset(i as isize) = bits as uint8_t;
        i += 1;
        i;
    }
    return BROTLI_DECODER_SUCCESS;
}
#[inline(always)]
unsafe extern "C" fn TakeDistanceFromRingBuffer(mut s: *mut BrotliDecoderStateInternal) {
    let mut offset: libc::c_int = (*s).distance_code - 3 as libc::c_int;
    if (*s).distance_code <= 3 as libc::c_int {
        (*s).distance_context = 1 as libc::c_int >> (*s).distance_code;
        (*s)
            .distance_code = (*s)
            .dist_rb[((*s).dist_rb_idx - offset & 3 as libc::c_int) as usize];
        (*s).dist_rb_idx -= (*s).distance_context;
    } else {
        let mut index_delta: libc::c_int = 3 as libc::c_int;
        let mut delta: libc::c_int = 0;
        let mut base: libc::c_int = (*s).distance_code - 10 as libc::c_int;
        if (*s).distance_code < 10 as libc::c_int {
            base = (*s).distance_code - 4 as libc::c_int;
        } else {
            index_delta = 2 as libc::c_int;
        }
        delta = (0x605142 as libc::c_int >> 4 as libc::c_int * base & 0xf as libc::c_int)
            - 3 as libc::c_int;
        (*s)
            .distance_code = (*s)
            .dist_rb[((*s).dist_rb_idx + index_delta & 0x3 as libc::c_int) as usize]
            + delta;
        if (*s).distance_code <= 0 as libc::c_int {
            (*s).distance_code = 0x7fffffff as libc::c_int;
        }
    };
}
#[inline(always)]
unsafe extern "C" fn SafeReadBits(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) -> libc::c_int {
    if n_bits != 0 as libc::c_int as uint32_t {
        return BrotliSafeReadBits(br, n_bits, val)
    } else {
        *val = 0 as libc::c_int as uint32_t;
        return 1 as libc::c_int;
    };
}
#[inline(always)]
unsafe extern "C" fn SafeReadBits32(
    br: *mut BrotliBitReader,
    mut n_bits: uint32_t,
    mut val: *mut uint32_t,
) -> libc::c_int {
    if n_bits != 0 as libc::c_int as uint32_t {
        return BrotliSafeReadBits32(br, n_bits, val)
    } else {
        *val = 0 as libc::c_int as uint32_t;
        return 1 as libc::c_int;
    };
}
unsafe extern "C" fn CalculateDistanceLut(mut s: *mut BrotliDecoderStateInternal) {
    let mut b: *mut BrotliMetablockBodyArena = &mut (*s).arena.body;
    let mut npostfix: uint32_t = (*s).distance_postfix_bits;
    let mut ndirect: uint32_t = (*s).num_direct_distance_codes;
    let mut alphabet_size_limit: uint32_t = (*s).distance_hgroup.alphabet_size_limit
        as uint32_t;
    let mut postfix: uint32_t = (1 as libc::c_uint) << npostfix;
    let mut j: uint32_t = 0;
    let mut bits: uint32_t = 1 as libc::c_int as uint32_t;
    let mut half: uint32_t = 0 as libc::c_int as uint32_t;
    let mut i: uint32_t = 16 as libc::c_int as uint32_t;
    j = 0 as libc::c_int as uint32_t;
    while j < ndirect {
        (*b).dist_extra_bits[i as usize] = 0 as libc::c_int as uint8_t;
        (*b).dist_offset[i as usize] = j.wrapping_add(1 as libc::c_int as uint32_t);
        i = i.wrapping_add(1);
        i;
        j = j.wrapping_add(1);
        j;
    }
    while i < alphabet_size_limit {
        let mut base: uint32_t = ndirect
            .wrapping_add(
                ((2 as libc::c_int as uint32_t).wrapping_add(half) << bits)
                    .wrapping_sub(4 as libc::c_int as uint32_t) << npostfix,
            )
            .wrapping_add(1 as libc::c_int as uint32_t);
        j = 0 as libc::c_int as uint32_t;
        while j < postfix {
            (*b).dist_extra_bits[i as usize] = bits as uint8_t;
            (*b).dist_offset[i as usize] = base.wrapping_add(j);
            i = i.wrapping_add(1);
            i;
            j = j.wrapping_add(1);
            j;
        }
        bits = bits.wrapping_add(half);
        half = half ^ 1 as libc::c_int as uint32_t;
    }
}
#[inline(always)]
unsafe extern "C" fn ReadDistanceInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
) -> libc::c_int {
    let mut b: *mut BrotliMetablockBodyArena = &mut (*s).arena.body;
    let mut code: uint32_t = 0;
    let mut bits: uint32_t = 0;
    let mut memento: BrotliBitReaderState = BrotliBitReaderState {
        val_: 0,
        bit_pos_: 0,
        next_in: 0 as *const uint8_t,
        avail_in: 0,
    };
    let mut distance_tree: *mut HuffmanCode = *((*s).distance_hgroup.htrees)
        .offset((*s).dist_htree_index as isize);
    if safe == 0 {
        code = ReadSymbol(distance_tree, br);
    } else {
        BrotliBitReaderSaveState(br, &mut memento);
        if SafeReadSymbol(distance_tree, br, &mut code) == 0 {
            return 0 as libc::c_int;
        }
    }
    (*s)
        .block_length[2 as libc::c_int
        as usize] = ((*s).block_length[2 as libc::c_int as usize]).wrapping_sub(1);
    (*s).block_length[2 as libc::c_int as usize];
    (*s).distance_context = 0 as libc::c_int;
    if code & !(0xf as libc::c_uint) == 0 as libc::c_int as libc::c_uint {
        (*s).distance_code = code as libc::c_int;
        TakeDistanceFromRingBuffer(s);
        return 1 as libc::c_int;
    }
    if safe == 0 {
        bits = BrotliReadBits32(br, (*b).dist_extra_bits[code as usize] as uint32_t);
    } else if SafeReadBits32(
        br,
        (*b).dist_extra_bits[code as usize] as uint32_t,
        &mut bits,
    ) == 0
    {
        (*s)
            .block_length[2 as libc::c_int
            as usize] = ((*s).block_length[2 as libc::c_int as usize]).wrapping_add(1);
        (*s).block_length[2 as libc::c_int as usize];
        BrotliBitReaderRestoreState(br, &mut memento);
        return 0 as libc::c_int;
    }
    (*s)
        .distance_code = ((*b).dist_offset[code as usize])
        .wrapping_add(bits << (*s).distance_postfix_bits) as libc::c_int;
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn ReadDistance(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
) {
    ReadDistanceInternal(0 as libc::c_int, s, br);
}
#[inline(always)]
unsafe extern "C" fn SafeReadDistance(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
) -> libc::c_int {
    return ReadDistanceInternal(1 as libc::c_int, s, br);
}
#[inline(always)]
unsafe extern "C" fn ReadCommandInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
    mut insert_length: *mut libc::c_int,
) -> libc::c_int {
    let mut cmd_code: uint32_t = 0;
    let mut insert_len_extra: uint32_t = 0 as libc::c_int as uint32_t;
    let mut copy_length: uint32_t = 0;
    let mut v: CmdLutElement = CmdLutElement {
        insert_len_extra_bits: 0,
        copy_len_extra_bits: 0,
        distance_code: 0,
        context: 0,
        insert_len_offset: 0,
        copy_len_offset: 0,
    };
    let mut memento: BrotliBitReaderState = BrotliBitReaderState {
        val_: 0,
        bit_pos_: 0,
        next_in: 0 as *const uint8_t,
        avail_in: 0,
    };
    if safe == 0 {
        cmd_code = ReadSymbol((*s).htree_command, br);
    } else {
        BrotliBitReaderSaveState(br, &mut memento);
        if SafeReadSymbol((*s).htree_command, br, &mut cmd_code) == 0 {
            return 0 as libc::c_int;
        }
    }
    v = kCmdLut[cmd_code as usize];
    (*s).distance_code = v.distance_code as libc::c_int;
    (*s).distance_context = v.context as libc::c_int;
    (*s)
        .dist_htree_index = *((*s).dist_context_map_slice)
        .offset((*s).distance_context as isize);
    *insert_length = v.insert_len_offset as libc::c_int;
    if safe == 0 {
        if (v.insert_len_extra_bits as libc::c_int != 0 as libc::c_int) as libc::c_int
            as libc::c_long != 0
        {
            insert_len_extra = BrotliReadBits24(br, v.insert_len_extra_bits as uint32_t);
        }
        copy_length = BrotliReadBits24(br, v.copy_len_extra_bits as uint32_t);
    } else if SafeReadBits(
        br,
        v.insert_len_extra_bits as uint32_t,
        &mut insert_len_extra,
    ) == 0 || SafeReadBits(br, v.copy_len_extra_bits as uint32_t, &mut copy_length) == 0
    {
        BrotliBitReaderRestoreState(br, &mut memento);
        return 0 as libc::c_int;
    }
    (*s).copy_length = copy_length as libc::c_int + v.copy_len_offset as libc::c_int;
    (*s)
        .block_length[1 as libc::c_int
        as usize] = ((*s).block_length[1 as libc::c_int as usize]).wrapping_sub(1);
    (*s).block_length[1 as libc::c_int as usize];
    *insert_length += insert_len_extra as libc::c_int;
    return 1 as libc::c_int;
}
#[inline(always)]
unsafe extern "C" fn ReadCommand(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
    mut insert_length: *mut libc::c_int,
) {
    ReadCommandInternal(0 as libc::c_int, s, br, insert_length);
}
#[inline(always)]
unsafe extern "C" fn SafeReadCommand(
    mut s: *mut BrotliDecoderStateInternal,
    mut br: *mut BrotliBitReader,
    mut insert_length: *mut libc::c_int,
) -> libc::c_int {
    return ReadCommandInternal(1 as libc::c_int, s, br, insert_length);
}
#[inline(always)]
unsafe extern "C" fn CheckInputAmount(
    mut safe: libc::c_int,
    br: *mut BrotliBitReader,
    mut num: size_t,
) -> libc::c_int {
    if safe != 0 {
        return 1 as libc::c_int;
    }
    return BrotliCheckInputAmount(br, num);
}
#[inline(always)]
unsafe extern "C" fn ProcessCommandsInternal(
    mut safe: libc::c_int,
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    let mut current_block: u64;
    let mut pos: libc::c_int = (*s).pos;
    let mut i: libc::c_int = (*s).loop_counter;
    let mut result: BrotliDecoderErrorCode = BROTLI_DECODER_SUCCESS;
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    if CheckInputAmount(safe, br, 28 as libc::c_int as size_t) == 0 {
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    } else {
        if safe == 0 {
            BrotliWarmupBitReader(br);
        }
        if (*s).state as libc::c_uint
            == BROTLI_STATE_COMMAND_BEGIN as libc::c_int as libc::c_uint
        {
            current_block = 13574048789939633379;
        } else if (*s).state as libc::c_uint
            == BROTLI_STATE_COMMAND_INNER as libc::c_int as libc::c_uint
        {
            current_block = 11270806590051122936;
        } else if (*s).state as libc::c_uint
            == BROTLI_STATE_COMMAND_POST_DECODE_LITERALS as libc::c_int as libc::c_uint
        {
            current_block = 15970878894474247115;
        } else if (*s).state as libc::c_uint
            == BROTLI_STATE_COMMAND_POST_WRAP_COPY as libc::c_int as libc::c_uint
        {
            current_block = 8953117030348968745;
        } else {
            return BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                as BrotliDecoderErrorCode
        }
        '_CommandBegin: loop {
            match current_block {
                15970878894474247115 => {
                    if safe != 0 {
                        (*s).state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
                    }
                    if (*s).distance_code >= 0 as libc::c_int {
                        (*s)
                            .distance_context = if (*s).distance_code != 0 {
                            0 as libc::c_int
                        } else {
                            1 as libc::c_int
                        };
                        (*s).dist_rb_idx -= 1;
                        (*s).dist_rb_idx;
                        (*s)
                            .distance_code = (*s)
                            .dist_rb[((*s).dist_rb_idx & 3 as libc::c_int) as usize];
                    } else {
                        if ((*s).block_length[2 as libc::c_int as usize]
                            == 0 as libc::c_int as uint32_t) as libc::c_int
                            as libc::c_long != 0
                        {
                            if safe != 0 {
                                if SafeDecodeDistanceBlockSwitch(s) == 0 {
                                    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                    break;
                                }
                            } else {
                                DecodeDistanceBlockSwitch(s);
                            }
                        }
                        if safe != 0 {
                            if SafeReadDistance(s, br) == 0 {
                                result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                break;
                            }
                        } else {
                            ReadDistance(s, br);
                        }
                    }
                    if (*s).max_distance != (*s).max_backward_distance {
                        (*s)
                            .max_distance = if pos < (*s).max_backward_distance {
                            pos
                        } else {
                            (*s).max_backward_distance
                        };
                    }
                    i = (*s).copy_length;
                    if (*s).distance_code > (*s).max_distance {
                        if (*s).distance_code > 0x7ffffffc as libc::c_int {
                            return BROTLI_DECODER_ERROR_FORMAT_DISTANCE as libc::c_int
                                as BrotliDecoderErrorCode;
                        }
                        if i >= 4 as libc::c_int && i <= 24 as libc::c_int {
                            let mut address: libc::c_int = (*s).distance_code
                                - (*s).max_distance - 1 as libc::c_int;
                            let mut words: *const BrotliDictionary = (*s).dictionary;
                            let mut transforms: *const BrotliTransforms = (*s)
                                .transforms;
                            let mut offset: libc::c_int = (*(*s).dictionary)
                                .offsets_by_length[i as usize] as libc::c_int;
                            let mut shift: uint32_t = (*(*s).dictionary)
                                .size_bits_by_length[i as usize] as uint32_t;
                            let mut mask: libc::c_int = BitMask(shift) as libc::c_int;
                            let mut word_idx: libc::c_int = address & mask;
                            let mut transform_idx: libc::c_int = address >> shift;
                            (*s).dist_rb_idx += (*s).distance_context;
                            offset += word_idx * i;
                            if ((*words).data).is_null() as libc::c_int as libc::c_long
                                != 0
                            {
                                return BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET
                                    as libc::c_int as BrotliDecoderErrorCode;
                            }
                            if transform_idx
                                < (*transforms).num_transforms as libc::c_int
                            {
                                let mut word: *const uint8_t = &*((*words).data)
                                    .offset(offset as isize) as *const uint8_t;
                                let mut len: libc::c_int = i;
                                if transform_idx
                                    == (*transforms).cutOffTransforms[0 as libc::c_int as usize]
                                        as libc::c_int
                                {
                                    memcpy(
                                        &mut *((*s).ringbuffer).offset(pos as isize) as *mut uint8_t
                                            as *mut libc::c_void,
                                        word as *const libc::c_void,
                                        len as size_t,
                                    );
                                } else {
                                    len = BrotliTransformDictionaryWord(
                                        &mut *((*s).ringbuffer).offset(pos as isize),
                                        word,
                                        len,
                                        transforms,
                                        transform_idx,
                                    );
                                }
                                pos += len;
                                (*s).meta_block_remaining_len -= len;
                                if pos >= (*s).ringbuffer_size {
                                    (*s).state = BROTLI_STATE_COMMAND_POST_WRITE_1;
                                    break;
                                }
                            } else {
                                return BROTLI_DECODER_ERROR_FORMAT_TRANSFORM as libc::c_int
                                    as BrotliDecoderErrorCode
                            }
                        } else {
                            return BROTLI_DECODER_ERROR_FORMAT_DICTIONARY as libc::c_int
                                as BrotliDecoderErrorCode
                        }
                    } else {
                        let mut src_start: libc::c_int = pos - (*s).distance_code
                            & (*s).ringbuffer_mask;
                        let mut copy_dst: *mut uint8_t = &mut *((*s).ringbuffer)
                            .offset(pos as isize) as *mut uint8_t;
                        let mut copy_src: *mut uint8_t = &mut *((*s).ringbuffer)
                            .offset(src_start as isize) as *mut uint8_t;
                        let mut dst_end: libc::c_int = pos + i;
                        let mut src_end: libc::c_int = src_start + i;
                        (*s)
                            .dist_rb[((*s).dist_rb_idx & 3 as libc::c_int)
                            as usize] = (*s).distance_code;
                        (*s).dist_rb_idx += 1;
                        (*s).dist_rb_idx;
                        (*s).meta_block_remaining_len -= i;
                        memmove16(copy_dst, copy_src);
                        if src_end > pos && dst_end > src_start {
                            current_block = 8953117030348968745;
                            continue;
                        } else {
                            if dst_end >= (*s).ringbuffer_size
                                || src_end >= (*s).ringbuffer_size
                            {
                                current_block = 8953117030348968745;
                                continue;
                            }
                            pos += i;
                            if i > 16 as libc::c_int {
                                if i > 32 as libc::c_int {
                                    memcpy(
                                        copy_dst.offset(16 as libc::c_int as isize)
                                            as *mut libc::c_void,
                                        copy_src.offset(16 as libc::c_int as isize)
                                            as *const libc::c_void,
                                        (i - 16 as libc::c_int) as size_t,
                                    );
                                } else {
                                    memmove16(
                                        copy_dst.offset(16 as libc::c_int as isize),
                                        copy_src.offset(16 as libc::c_int as isize),
                                    );
                                }
                            }
                        }
                    }
                    if !((*s).meta_block_remaining_len <= 0 as libc::c_int) {
                        current_block = 13574048789939633379;
                        continue;
                    }
                    (*s).state = BROTLI_STATE_METABLOCK_DONE;
                    break;
                }
                13574048789939633379 => {
                    if safe != 0 {
                        (*s).state = BROTLI_STATE_COMMAND_BEGIN;
                    }
                    if CheckInputAmount(safe, br, 28 as libc::c_int as size_t) == 0 {
                        (*s).state = BROTLI_STATE_COMMAND_BEGIN;
                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                        break;
                    } else if ((*s).block_length[1 as libc::c_int as usize]
                        == 0 as libc::c_int as uint32_t) as libc::c_int as libc::c_long
                        != 0
                    {
                        if safe != 0 {
                            if !(SafeDecodeCommandBlockSwitch(s) == 0) {
                                current_block = 13574048789939633379;
                                continue;
                            }
                            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                            break;
                        } else {
                            DecodeCommandBlockSwitch(s);
                            current_block = 13574048789939633379;
                        }
                    } else {
                        if safe != 0 {
                            if SafeReadCommand(s, br, &mut i) == 0 {
                                result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                break;
                            }
                        } else {
                            ReadCommand(s, br, &mut i);
                        }
                        if i == 0 as libc::c_int {
                            current_block = 15970878894474247115;
                            continue;
                        }
                        (*s).meta_block_remaining_len -= i;
                        current_block = 11270806590051122936;
                    }
                }
                8953117030348968745 => {
                    let mut wrap_guard: libc::c_int = (*s).ringbuffer_size - pos;
                    loop {
                        i -= 1;
                        if !(i >= 0 as libc::c_int) {
                            break;
                        }
                        *((*s).ringbuffer)
                            .offset(
                                pos as isize,
                            ) = *((*s).ringbuffer)
                            .offset(
                                (pos - (*s).distance_code & (*s).ringbuffer_mask) as isize,
                            );
                        pos += 1;
                        pos;
                        wrap_guard -= 1;
                        if !((wrap_guard == 0 as libc::c_int) as libc::c_int
                            as libc::c_long != 0)
                        {
                            continue;
                        }
                        (*s).state = BROTLI_STATE_COMMAND_POST_WRITE_2;
                        break '_CommandBegin;
                    }
                    if !((*s).meta_block_remaining_len <= 0 as libc::c_int) {
                        current_block = 13574048789939633379;
                        continue;
                    }
                    (*s).state = BROTLI_STATE_METABLOCK_DONE;
                    break;
                }
                _ => {
                    if safe != 0 {
                        (*s).state = BROTLI_STATE_COMMAND_INNER;
                    }
                    if (*s).trivial_literal_context != 0 {
                        let mut bits: uint32_t = 0;
                        let mut value: uint32_t = 0;
                        PreloadSymbol(
                            safe,
                            (*s).literal_htree,
                            br,
                            &mut bits,
                            &mut value,
                        );
                        loop {
                            if CheckInputAmount(safe, br, 28 as libc::c_int as size_t)
                                == 0
                            {
                                (*s).state = BROTLI_STATE_COMMAND_INNER;
                                result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                break '_CommandBegin;
                            } else {
                                if ((*s).block_length[0 as libc::c_int as usize]
                                    == 0 as libc::c_int as uint32_t) as libc::c_int
                                    as libc::c_long != 0
                                {
                                    if safe != 0 {
                                        if SafeDecodeLiteralBlockSwitch(s) == 0 {
                                            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                            break '_CommandBegin;
                                        }
                                    } else {
                                        DecodeLiteralBlockSwitch(s);
                                    }
                                    PreloadSymbol(
                                        safe,
                                        (*s).literal_htree,
                                        br,
                                        &mut bits,
                                        &mut value,
                                    );
                                    if (*s).trivial_literal_context == 0 {
                                        current_block = 11270806590051122936;
                                        continue '_CommandBegin;
                                    }
                                }
                                if safe == 0 {
                                    *((*s).ringbuffer)
                                        .offset(
                                            pos as isize,
                                        ) = ReadPreloadedSymbol(
                                        (*s).literal_htree,
                                        br,
                                        &mut bits,
                                        &mut value,
                                    ) as uint8_t;
                                } else {
                                    let mut literal: uint32_t = 0;
                                    if SafeReadSymbol((*s).literal_htree, br, &mut literal) == 0
                                    {
                                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                        break '_CommandBegin;
                                    } else {
                                        *((*s).ringbuffer)
                                            .offset(pos as isize) = literal as uint8_t;
                                    }
                                }
                                (*s)
                                    .block_length[0 as libc::c_int
                                    as usize] = ((*s).block_length[0 as libc::c_int as usize])
                                    .wrapping_sub(1);
                                (*s).block_length[0 as libc::c_int as usize];
                                pos += 1;
                                pos;
                                if (pos == (*s).ringbuffer_size) as libc::c_int
                                    as libc::c_long != 0
                                {
                                    (*s).state = BROTLI_STATE_COMMAND_INNER_WRITE;
                                    i -= 1;
                                    i;
                                    break '_CommandBegin;
                                } else {
                                    i -= 1;
                                    if !(i != 0 as libc::c_int) {
                                        break;
                                    }
                                }
                            }
                        }
                    } else {
                        let mut p1: uint8_t = *((*s).ringbuffer)
                            .offset(
                                (pos - 1 as libc::c_int & (*s).ringbuffer_mask) as isize,
                            );
                        let mut p2: uint8_t = *((*s).ringbuffer)
                            .offset(
                                (pos - 2 as libc::c_int & (*s).ringbuffer_mask) as isize,
                            );
                        loop {
                            let mut hc: *const HuffmanCode = 0 as *const HuffmanCode;
                            let mut context: uint8_t = 0;
                            if CheckInputAmount(safe, br, 28 as libc::c_int as size_t)
                                == 0
                            {
                                (*s).state = BROTLI_STATE_COMMAND_INNER;
                                result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                break '_CommandBegin;
                            } else {
                                if ((*s).block_length[0 as libc::c_int as usize]
                                    == 0 as libc::c_int as uint32_t) as libc::c_int
                                    as libc::c_long != 0
                                {
                                    if safe != 0 {
                                        if SafeDecodeLiteralBlockSwitch(s) == 0 {
                                            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                            break '_CommandBegin;
                                        }
                                    } else {
                                        DecodeLiteralBlockSwitch(s);
                                    }
                                    if (*s).trivial_literal_context != 0 {
                                        current_block = 11270806590051122936;
                                        continue '_CommandBegin;
                                    }
                                }
                                context = (*((*s).context_lookup).offset(p1 as isize)
                                    as libc::c_int
                                    | *((*s).context_lookup)
                                        .offset(256 as libc::c_int as isize)
                                        .offset(p2 as isize) as libc::c_int) as uint8_t;
                                hc = *((*s).literal_hgroup.htrees)
                                    .offset(
                                        *((*s).context_map_slice).offset(context as isize) as isize,
                                    );
                                p2 = p1;
                                if safe == 0 {
                                    p1 = ReadSymbol(hc, br) as uint8_t;
                                } else {
                                    let mut literal_0: uint32_t = 0;
                                    if SafeReadSymbol(hc, br, &mut literal_0) == 0 {
                                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                                        break '_CommandBegin;
                                    } else {
                                        p1 = literal_0 as uint8_t;
                                    }
                                }
                                *((*s).ringbuffer).offset(pos as isize) = p1;
                                (*s)
                                    .block_length[0 as libc::c_int
                                    as usize] = ((*s).block_length[0 as libc::c_int as usize])
                                    .wrapping_sub(1);
                                (*s).block_length[0 as libc::c_int as usize];
                                pos += 1;
                                pos;
                                if (pos == (*s).ringbuffer_size) as libc::c_int
                                    as libc::c_long != 0
                                {
                                    (*s).state = BROTLI_STATE_COMMAND_INNER_WRITE;
                                    i -= 1;
                                    i;
                                    break '_CommandBegin;
                                } else {
                                    i -= 1;
                                    if !(i != 0 as libc::c_int) {
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if !(((*s).meta_block_remaining_len <= 0 as libc::c_int)
                        as libc::c_int as libc::c_long != 0)
                    {
                        current_block = 15970878894474247115;
                        continue;
                    }
                    (*s).state = BROTLI_STATE_METABLOCK_DONE;
                    break;
                }
            }
        }
    }
    (*s).pos = pos;
    (*s).loop_counter = i;
    return result;
}
#[inline(never)]
unsafe extern "C" fn ProcessCommands(
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    return ProcessCommandsInternal(0 as libc::c_int, s);
}
#[inline(never)]
unsafe extern "C" fn SafeProcessCommands(
    mut s: *mut BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    return ProcessCommandsInternal(1 as libc::c_int, s);
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderDecompress(
    mut encoded_size: size_t,
    mut encoded_buffer: *const uint8_t,
    mut decoded_size: *mut size_t,
    mut decoded_buffer: *mut uint8_t,
) -> BrotliDecoderResult {
    let mut s: BrotliDecoderStateInternal = BrotliDecoderStateStruct {
        state: BROTLI_STATE_UNINITED,
        loop_counter: 0,
        br: BrotliBitReader {
            val_: 0,
            bit_pos_: 0,
            next_in: 0 as *const uint8_t,
            avail_in: 0,
        },
        alloc_func: None,
        free_func: None,
        memory_manager_opaque: 0 as *mut libc::c_void,
        buffer: C2RustUnnamed_0 { u64_0: 0 },
        buffer_length: 0,
        pos: 0,
        max_backward_distance: 0,
        max_distance: 0,
        ringbuffer_size: 0,
        ringbuffer_mask: 0,
        dist_rb_idx: 0,
        dist_rb: [0; 4],
        error_code: 0,
        ringbuffer: 0 as *mut uint8_t,
        ringbuffer_end: 0 as *mut uint8_t,
        htree_command: 0 as *mut HuffmanCode,
        context_lookup: 0 as *const uint8_t,
        context_map_slice: 0 as *mut uint8_t,
        dist_context_map_slice: 0 as *mut uint8_t,
        literal_hgroup: HuffmanTreeGroup {
            htrees: 0 as *mut *mut HuffmanCode,
            codes: 0 as *mut HuffmanCode,
            alphabet_size_max: 0,
            alphabet_size_limit: 0,
            num_htrees: 0,
        },
        insert_copy_hgroup: HuffmanTreeGroup {
            htrees: 0 as *mut *mut HuffmanCode,
            codes: 0 as *mut HuffmanCode,
            alphabet_size_max: 0,
            alphabet_size_limit: 0,
            num_htrees: 0,
        },
        distance_hgroup: HuffmanTreeGroup {
            htrees: 0 as *mut *mut HuffmanCode,
            codes: 0 as *mut HuffmanCode,
            alphabet_size_max: 0,
            alphabet_size_limit: 0,
            num_htrees: 0,
        },
        block_type_trees: 0 as *mut HuffmanCode,
        block_len_trees: 0 as *mut HuffmanCode,
        trivial_literal_context: 0,
        distance_context: 0,
        meta_block_remaining_len: 0,
        block_length_index: 0,
        block_length: [0; 3],
        num_block_types: [0; 3],
        block_type_rb: [0; 6],
        distance_postfix_bits: 0,
        num_direct_distance_codes: 0,
        num_dist_htrees: 0,
        dist_context_map: 0 as *mut uint8_t,
        literal_htree: 0 as *mut HuffmanCode,
        dist_htree_index: 0,
        copy_length: 0,
        distance_code: 0,
        rb_roundtrips: 0,
        partial_pos_out: 0,
        mtf_upper_bound: 0,
        mtf: [0; 65],
        substate_metablock_header: BROTLI_STATE_METABLOCK_HEADER_NONE,
        substate_uncompressed: BROTLI_STATE_UNCOMPRESSED_NONE,
        substate_decode_uint8: BROTLI_STATE_DECODE_UINT8_NONE,
        substate_read_block_length: BROTLI_STATE_READ_BLOCK_LENGTH_NONE,
        is_last_metablock_is_uncompressed_is_metadata_should_wrap_ringbuffer_canny_ringbuffer_allocation_large_window_size_nibbles: [0; 2],
        c2rust_padding: [0; 2],
        window_bits: 0,
        new_ringbuffer_size: 0,
        num_literal_htrees: 0,
        context_map: 0 as *mut uint8_t,
        context_modes: 0 as *mut uint8_t,
        dictionary: 0 as *const BrotliDictionary,
        transforms: 0 as *const BrotliTransforms,
        trivial_literal_contexts: [0; 8],
        arena: C2RustUnnamed {
            header: BrotliMetablockHeaderArena {
                substate_tree_group: BROTLI_STATE_TREE_GROUP_NONE,
                substate_context_map: BROTLI_STATE_CONTEXT_MAP_NONE,
                substate_huffman: BROTLI_STATE_HUFFMAN_NONE,
                sub_loop_counter: 0,
                repeat_code_len: 0,
                prev_code_len: 0,
                symbol: 0,
                repeat: 0,
                space: 0,
                table: [HuffmanCode { bits: 0, value: 0 }; 32],
                symbol_lists: 0 as *mut uint16_t,
                symbols_lists_array: [0; 720],
                next_symbol: [0; 32],
                code_length_code_lengths: [0; 18],
                code_length_histo: [0; 16],
                htree_index: 0,
                next: 0 as *mut HuffmanCode,
                context_index: 0,
                max_run_length_prefix: 0,
                code: 0,
                context_map_table: [HuffmanCode { bits: 0, value: 0 }; 646],
            },
        },
    };
    let mut result: BrotliDecoderResult = BROTLI_DECODER_RESULT_ERROR;
    let mut total_out: size_t = 0 as libc::c_int as size_t;
    let mut available_in: size_t = encoded_size;
    let mut next_in: *const uint8_t = encoded_buffer;
    let mut available_out: size_t = *decoded_size;
    let mut next_out: *mut uint8_t = decoded_buffer;
    if BrotliDecoderStateInit(&mut s, None, None, 0 as *mut libc::c_void) == 0 {
        return BROTLI_DECODER_RESULT_ERROR;
    }
    result = BrotliDecoderDecompressStream(
        &mut s,
        &mut available_in,
        &mut next_in,
        &mut available_out,
        &mut next_out,
        &mut total_out,
    );
    *decoded_size = total_out;
    BrotliDecoderStateCleanup(&mut s);
    if result as libc::c_uint
        != BROTLI_DECODER_RESULT_SUCCESS as libc::c_int as libc::c_uint
    {
        result = BROTLI_DECODER_RESULT_ERROR;
    }
    return result;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderDecompressStream(
    mut s: *mut BrotliDecoderStateInternal,
    mut available_in: *mut size_t,
    mut next_in: *mut *const uint8_t,
    mut available_out: *mut size_t,
    mut next_out: *mut *mut uint8_t,
    mut total_out: *mut size_t,
) -> BrotliDecoderResult {
    let mut result: BrotliDecoderErrorCode = BROTLI_DECODER_SUCCESS;
    let mut br: *mut BrotliBitReader = &mut (*s).br;
    if !total_out.is_null() {
        *total_out = (*s).partial_pos_out;
    }
    if (*s).error_code < 0 as libc::c_int {
        return BROTLI_DECODER_RESULT_ERROR;
    }
    if *available_out != 0 && (next_out.is_null() || (*next_out).is_null()) {
        return SaveErrorCode(
            s,
            BROTLI_DECODER_ERROR_INVALID_ARGUMENTS as libc::c_int
                as BrotliDecoderErrorCode,
        );
    }
    if *available_out == 0 {
        next_out = 0 as *mut *mut uint8_t;
    }
    if (*s).buffer_length == 0 as libc::c_int as uint32_t {
        (*br).avail_in = *available_in;
        (*br).next_in = *next_in;
    } else {
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
        (*br)
            .next_in = &mut *((*s).buffer.u8_0)
            .as_mut_ptr()
            .offset(0 as libc::c_int as isize) as *mut uint8_t;
    }
    loop {
        if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
            if result as libc::c_int == BROTLI_DECODER_NEEDS_MORE_INPUT as libc::c_int {
                if !((*s).ringbuffer).is_null() {
                    let mut intermediate_result: BrotliDecoderErrorCode = WriteRingBuffer(
                        s,
                        available_out,
                        next_out,
                        total_out,
                        1 as libc::c_int,
                    );
                    if (intermediate_result as libc::c_int) < 0 as libc::c_int {
                        result = intermediate_result;
                        break;
                    }
                }
                if (*s).buffer_length != 0 as libc::c_int as uint32_t {
                    if (*br).avail_in == 0 as libc::c_int as size_t {
                        (*s).buffer_length = 0 as libc::c_int as uint32_t;
                        result = BROTLI_DECODER_SUCCESS;
                        (*br).avail_in = *available_in;
                        (*br).next_in = *next_in;
                    } else {
                        if !(*available_in != 0 as libc::c_int as size_t) {
                            break;
                        }
                        result = BROTLI_DECODER_SUCCESS;
                        (*s).buffer.u8_0[(*s).buffer_length as usize] = **next_in;
                        (*s).buffer_length = ((*s).buffer_length).wrapping_add(1);
                        (*s).buffer_length;
                        (*br).avail_in = (*s).buffer_length as size_t;
                        *next_in = (*next_in).offset(1);
                        *next_in;
                        *available_in = (*available_in).wrapping_sub(1);
                        *available_in;
                    }
                } else {
                    *next_in = (*br).next_in;
                    *available_in = (*br).avail_in;
                    while *available_in != 0 {
                        (*s).buffer.u8_0[(*s).buffer_length as usize] = **next_in;
                        (*s).buffer_length = ((*s).buffer_length).wrapping_add(1);
                        (*s).buffer_length;
                        *next_in = (*next_in).offset(1);
                        *next_in;
                        *available_in = (*available_in).wrapping_sub(1);
                        *available_in;
                    }
                    break;
                }
            } else {
                if (*s).buffer_length != 0 as libc::c_int as uint32_t {
                    (*s).buffer_length = 0 as libc::c_int as uint32_t;
                } else {
                    BrotliBitReaderUnload(br);
                    *available_in = (*br).avail_in;
                    *next_in = (*br).next_in;
                }
                break;
            }
        } else {
            let mut current_block_175: u64;
            match (*s).state as libc::c_uint {
                0 => {
                    if BrotliWarmupBitReader(br) == 0 {
                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                    } else {
                        result = DecodeWindowBits(s, br);
                        if !(result as libc::c_int
                            != BROTLI_DECODER_SUCCESS as libc::c_int)
                        {
                            if (*s).large_window() != 0 {
                                (*s).state = BROTLI_STATE_LARGE_WINDOW_BITS;
                            } else {
                                (*s).state = BROTLI_STATE_INITIALIZE;
                            }
                        }
                    }
                    current_block_175 = 16718638665978159145;
                }
                1 => {
                    if BrotliSafeReadBits(
                        br,
                        6 as libc::c_int as uint32_t,
                        &mut (*s).window_bits,
                    ) == 0
                    {
                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                        current_block_175 = 16718638665978159145;
                    } else if (*s).window_bits < 10 as libc::c_int as uint32_t
                        || (*s).window_bits > 30 as libc::c_int as uint32_t
                    {
                        result = BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS as libc::c_int
                            as BrotliDecoderErrorCode;
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).state = BROTLI_STATE_INITIALIZE;
                        current_block_175 = 2520131295878969859;
                    }
                }
                2 => {
                    current_block_175 = 2520131295878969859;
                }
                3 => {
                    current_block_175 = 6589414636452177323;
                }
                4 => {
                    current_block_175 = 11944456811575812674;
                }
                17 => {
                    current_block_175 = 12341693363195858590;
                }
                18 => {
                    current_block_175 = 18317355710847767980;
                }
                19 => {
                    current_block_175 = 5023038348526654800;
                }
                20 => {
                    current_block_175 = 6712462580143783635;
                }
                21 => {
                    current_block_175 = 15622658527355336244;
                }
                11 => {
                    result = CopyUncompressedBlockToOutput(
                        available_out,
                        next_out,
                        total_out,
                        s,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).state = BROTLI_STATE_METABLOCK_DONE;
                        current_block_175 = 16718638665978159145;
                    }
                }
                12 => {
                    while (*s).meta_block_remaining_len > 0 as libc::c_int {
                        let mut bits: uint32_t = 0;
                        if BrotliSafeReadBits(
                            br,
                            8 as libc::c_int as uint32_t,
                            &mut bits,
                        ) == 0
                        {
                            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                            break;
                        } else {
                            (*s).meta_block_remaining_len -= 1;
                            (*s).meta_block_remaining_len;
                        }
                    }
                    if result as libc::c_int == BROTLI_DECODER_SUCCESS as libc::c_int {
                        (*s).state = BROTLI_STATE_METABLOCK_DONE;
                    }
                    current_block_175 = 16718638665978159145;
                }
                5 => {
                    let mut bits_0: uint32_t = 0;
                    if BrotliSafeReadBits(br, 6 as libc::c_int as uint32_t, &mut bits_0)
                        == 0
                    {
                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s)
                            .distance_postfix_bits = bits_0
                            & BitMask(2 as libc::c_int as uint32_t);
                        bits_0 >>= 2 as libc::c_int;
                        (*s)
                            .num_direct_distance_codes = bits_0
                            << (*s).distance_postfix_bits;
                        (*s)
                            .context_modes = ((*s).alloc_func)
                            .expect(
                                "non-null function pointer",
                            )(
                            (*s).memory_manager_opaque,
                            (*s).num_block_types[0 as libc::c_int as usize] as size_t,
                        ) as *mut uint8_t;
                        if ((*s).context_modes).is_null() {
                            result = BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES
                                as libc::c_int as BrotliDecoderErrorCode;
                            current_block_175 = 16718638665978159145;
                        } else {
                            (*s).loop_counter = 0 as libc::c_int;
                            (*s).state = BROTLI_STATE_CONTEXT_MODES;
                            current_block_175 = 2334784937562835604;
                        }
                    }
                }
                6 => {
                    current_block_175 = 2334784937562835604;
                }
                22 => {
                    current_block_175 = 451532537293855284;
                }
                23 => {
                    current_block_175 = 13425230902034816933;
                }
                24 => {
                    current_block_175 = 13895078145312174667;
                }
                25 => {
                    current_block_175 = 4423598539606377485;
                }
                7 => {
                    current_block_175 = 12386775860387733485;
                }
                8 => {
                    current_block_175 = 6546859112865444725;
                }
                9 | 10 => {
                    current_block_175 = 4508254836030314814;
                }
                13 => {
                    current_block_175 = 14649248620013606739;
                }
                15 | 16 => {
                    current_block_175 = 14649248620013606739;
                }
                14 => {
                    if (*s).meta_block_remaining_len < 0 as libc::c_int {
                        result = BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2
                            as libc::c_int as BrotliDecoderErrorCode;
                        current_block_175 = 16718638665978159145;
                    } else {
                        BrotliDecoderStateCleanupAfterMetablock(s);
                        if (*s).is_last_metablock() == 0 {
                            (*s).state = BROTLI_STATE_METABLOCK_BEGIN;
                            current_block_175 = 16718638665978159145;
                        } else if BrotliJumpToByteBoundary(br) == 0 {
                            result = BROTLI_DECODER_ERROR_FORMAT_PADDING_2 as libc::c_int
                                as BrotliDecoderErrorCode;
                            current_block_175 = 16718638665978159145;
                        } else {
                            if (*s).buffer_length == 0 as libc::c_int as uint32_t {
                                BrotliBitReaderUnload(br);
                                *available_in = (*br).avail_in;
                                *next_in = (*br).next_in;
                            }
                            (*s).state = BROTLI_STATE_DONE;
                            current_block_175 = 11907235529767869592;
                        }
                    }
                }
                26 => {
                    current_block_175 = 11907235529767869592;
                }
                _ => {
                    current_block_175 = 16718638665978159145;
                }
            }
            match current_block_175 {
                11907235529767869592 => {
                    if !((*s).ringbuffer).is_null() {
                        result = WriteRingBuffer(
                            s,
                            available_out,
                            next_out,
                            total_out,
                            1 as libc::c_int,
                        );
                        if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int
                        {
                            current_block_175 = 16718638665978159145;
                        } else {
                            current_block_175 = 16167632229894708628;
                        }
                    } else {
                        current_block_175 = 16167632229894708628;
                    }
                    match current_block_175 {
                        16718638665978159145 => {}
                        _ => return SaveErrorCode(s, result),
                    }
                }
                14649248620013606739 => {
                    result = WriteRingBuffer(
                        s,
                        available_out,
                        next_out,
                        total_out,
                        0 as libc::c_int,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        WrapRingBuffer(s);
                        if (*s).ringbuffer_size == (1 as libc::c_int) << (*s).window_bits
                        {
                            (*s).max_distance = (*s).max_backward_distance;
                        }
                        if (*s).state as libc::c_uint
                            == BROTLI_STATE_COMMAND_POST_WRITE_1 as libc::c_int
                                as libc::c_uint
                        {
                            if (*s).meta_block_remaining_len == 0 as libc::c_int {
                                (*s).state = BROTLI_STATE_METABLOCK_DONE;
                            } else {
                                (*s).state = BROTLI_STATE_COMMAND_BEGIN;
                            }
                        } else if (*s).state as libc::c_uint
                            == BROTLI_STATE_COMMAND_POST_WRITE_2 as libc::c_int
                                as libc::c_uint
                        {
                            (*s).state = BROTLI_STATE_COMMAND_POST_WRAP_COPY;
                        } else if (*s).loop_counter == 0 as libc::c_int {
                            if (*s).meta_block_remaining_len == 0 as libc::c_int {
                                (*s).state = BROTLI_STATE_METABLOCK_DONE;
                            } else {
                                (*s).state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
                            }
                        } else {
                            (*s).state = BROTLI_STATE_COMMAND_INNER;
                        }
                        current_block_175 = 16718638665978159145;
                    }
                }
                2334784937562835604 => {
                    result = ReadContextModes(s);
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).state = BROTLI_STATE_CONTEXT_MAP_1;
                        current_block_175 = 451532537293855284;
                    }
                }
                2520131295878969859 => {
                    (*s)
                        .max_backward_distance = ((1 as libc::c_int) << (*s).window_bits)
                        - 16 as libc::c_int;
                    (*s)
                        .block_type_trees = ((*s).alloc_func)
                        .expect(
                            "non-null function pointer",
                        )(
                        (*s).memory_manager_opaque,
                        (::core::mem::size_of::<HuffmanCode>() as libc::c_ulong)
                            .wrapping_mul(3 as libc::c_int as libc::c_ulong)
                            .wrapping_mul(
                                (632 as libc::c_int + 396 as libc::c_int) as libc::c_ulong,
                            ),
                    ) as *mut HuffmanCode;
                    if ((*s).block_type_trees).is_null() {
                        result = BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES
                            as libc::c_int as BrotliDecoderErrorCode;
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s)
                            .block_len_trees = ((*s).block_type_trees)
                            .offset((3 as libc::c_int * 632 as libc::c_int) as isize);
                        (*s).state = BROTLI_STATE_METABLOCK_BEGIN;
                        current_block_175 = 6589414636452177323;
                    }
                }
                _ => {}
            }
            match current_block_175 {
                451532537293855284 => {
                    result = DecodeContextMap(
                        (*s).num_block_types[0 as libc::c_int as usize]
                            << 6 as libc::c_int,
                        &mut (*s).num_literal_htrees,
                        &mut (*s).context_map,
                        s,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        DetectTrivialLiteralBlockTypes(s);
                        (*s).state = BROTLI_STATE_CONTEXT_MAP_2;
                        current_block_175 = 13425230902034816933;
                    }
                }
                6589414636452177323 => {
                    BrotliDecoderStateMetablockBegin(s);
                    (*s).state = BROTLI_STATE_METABLOCK_HEADER;
                    current_block_175 = 11944456811575812674;
                }
                _ => {}
            }
            match current_block_175 {
                13425230902034816933 => {
                    let mut npostfix: uint32_t = (*s).distance_postfix_bits;
                    let mut ndirect: uint32_t = (*s).num_direct_distance_codes;
                    let mut distance_alphabet_size_max: uint32_t = (16 as libc::c_int
                        as uint32_t)
                        .wrapping_add(ndirect)
                        .wrapping_add(
                            (24 as libc::c_uint)
                                << npostfix.wrapping_add(1 as libc::c_int as uint32_t),
                        );
                    let mut distance_alphabet_size_limit: uint32_t = distance_alphabet_size_max;
                    let mut allocation_success: libc::c_int = 1 as libc::c_int;
                    if (*s).large_window() != 0 {
                        let mut limit: BrotliDistanceCodeLimit = BrotliCalculateDistanceCodeLimit(
                            0x7ffffffc as libc::c_int as uint32_t,
                            npostfix,
                            ndirect,
                        );
                        distance_alphabet_size_max = (16 as libc::c_int as uint32_t)
                            .wrapping_add(ndirect)
                            .wrapping_add(
                                (62 as libc::c_uint)
                                    << npostfix.wrapping_add(1 as libc::c_int as uint32_t),
                            );
                        distance_alphabet_size_limit = limit.max_alphabet_size;
                    }
                    result = DecodeContextMap(
                        (*s).num_block_types[2 as libc::c_int as usize]
                            << 2 as libc::c_int,
                        &mut (*s).num_dist_htrees,
                        &mut (*s).dist_context_map,
                        s,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        allocation_success
                            &= BrotliDecoderHuffmanTreeGroupInit(
                                s,
                                &mut (*s).literal_hgroup,
                                256 as libc::c_int as uint32_t,
                                256 as libc::c_int as uint32_t,
                                (*s).num_literal_htrees,
                            );
                        allocation_success
                            &= BrotliDecoderHuffmanTreeGroupInit(
                                s,
                                &mut (*s).insert_copy_hgroup,
                                704 as libc::c_int as uint32_t,
                                704 as libc::c_int as uint32_t,
                                (*s).num_block_types[1 as libc::c_int as usize],
                            );
                        allocation_success
                            &= BrotliDecoderHuffmanTreeGroupInit(
                                s,
                                &mut (*s).distance_hgroup,
                                distance_alphabet_size_max,
                                distance_alphabet_size_limit,
                                (*s).num_dist_htrees,
                            );
                        if allocation_success == 0 {
                            return SaveErrorCode(
                                s,
                                BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS as libc::c_int
                                    as BrotliDecoderErrorCode,
                            );
                        }
                        (*s).loop_counter = 0 as libc::c_int;
                        (*s).state = BROTLI_STATE_TREE_GROUP;
                        current_block_175 = 13895078145312174667;
                    }
                }
                11944456811575812674 => {
                    result = DecodeMetaBlockLength(s, br);
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        if (*s).is_metadata() as libc::c_int != 0
                            || (*s).is_uncompressed() as libc::c_int != 0
                        {
                            if BrotliJumpToByteBoundary(br) == 0 {
                                result = BROTLI_DECODER_ERROR_FORMAT_PADDING_1
                                    as libc::c_int as BrotliDecoderErrorCode;
                                current_block_175 = 16718638665978159145;
                            } else {
                                current_block_175 = 12961834331865314435;
                            }
                        } else {
                            current_block_175 = 12961834331865314435;
                        }
                        match current_block_175 {
                            16718638665978159145 => {}
                            _ => {
                                if (*s).is_metadata() != 0 {
                                    (*s).state = BROTLI_STATE_METADATA;
                                    current_block_175 = 16718638665978159145;
                                } else if (*s).meta_block_remaining_len == 0 as libc::c_int
                                {
                                    (*s).state = BROTLI_STATE_METABLOCK_DONE;
                                    current_block_175 = 16718638665978159145;
                                } else {
                                    BrotliCalculateRingBufferSize(s);
                                    if (*s).is_uncompressed() != 0 {
                                        (*s).state = BROTLI_STATE_UNCOMPRESSED;
                                        current_block_175 = 16718638665978159145;
                                    } else {
                                        (*s)
                                            .state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER;
                                        current_block_175 = 12341693363195858590;
                                    }
                                }
                            }
                        }
                    }
                }
                _ => {}
            }
            match current_block_175 {
                13895078145312174667 => {
                    let mut hgroup: *mut HuffmanTreeGroup = 0 as *mut HuffmanTreeGroup;
                    match (*s).loop_counter {
                        0 => {
                            hgroup = &mut (*s).literal_hgroup;
                        }
                        1 => {
                            hgroup = &mut (*s).insert_copy_hgroup;
                        }
                        2 => {
                            hgroup = &mut (*s).distance_hgroup;
                        }
                        _ => {
                            return SaveErrorCode(
                                s,
                                BROTLI_DECODER_ERROR_UNREACHABLE as libc::c_int
                                    as BrotliDecoderErrorCode,
                            );
                        }
                    }
                    result = HuffmanTreeGroupDecode(hgroup, s);
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).loop_counter += 1;
                        (*s).loop_counter;
                        if (*s).loop_counter < 3 as libc::c_int {
                            current_block_175 = 16718638665978159145;
                        } else {
                            (*s).state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY;
                            current_block_175 = 4423598539606377485;
                        }
                    }
                }
                12341693363195858590 => {
                    let mut h: *mut BrotliMetablockHeaderArena = &mut (*s).arena.header;
                    (*s).loop_counter = 0 as libc::c_int;
                    (*h).sub_loop_counter = 0 as libc::c_int as uint32_t;
                    (*h)
                        .symbol_lists = &mut *((*h).symbols_lists_array)
                        .as_mut_ptr()
                        .offset((15 as libc::c_int + 1 as libc::c_int) as isize)
                        as *mut uint16_t;
                    (*h).substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
                    (*h).substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
                    (*h).substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
                    (*s).state = BROTLI_STATE_HUFFMAN_CODE_0;
                    current_block_175 = 18317355710847767980;
                }
                _ => {}
            }
            match current_block_175 {
                4423598539606377485 => {
                    PrepareLiteralDecoding(s);
                    (*s).dist_context_map_slice = (*s).dist_context_map;
                    (*s)
                        .htree_command = *((*s).insert_copy_hgroup.htrees)
                        .offset(0 as libc::c_int as isize);
                    if BrotliEnsureRingBuffer(s) == 0 {
                        result = BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2 as libc::c_int
                            as BrotliDecoderErrorCode;
                        current_block_175 = 16718638665978159145;
                    } else {
                        CalculateDistanceLut(s);
                        (*s).state = BROTLI_STATE_COMMAND_BEGIN;
                        current_block_175 = 12386775860387733485;
                    }
                }
                18317355710847767980 => {
                    if (*s).loop_counter >= 3 as libc::c_int {
                        (*s).state = BROTLI_STATE_METABLOCK_HEADER_2;
                        current_block_175 = 16718638665978159145;
                    } else {
                        result = DecodeVarLenUint8(
                            s,
                            br,
                            &mut *((*s).num_block_types)
                                .as_mut_ptr()
                                .offset((*s).loop_counter as isize),
                        );
                        if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int
                        {
                            current_block_175 = 16718638665978159145;
                        } else {
                            (*s)
                                .num_block_types[(*s).loop_counter
                                as usize] = ((*s)
                                .num_block_types[(*s).loop_counter as usize])
                                .wrapping_add(1);
                            (*s).num_block_types[(*s).loop_counter as usize];
                            if (*s).num_block_types[(*s).loop_counter as usize]
                                < 2 as libc::c_int as uint32_t
                            {
                                (*s).loop_counter += 1;
                                (*s).loop_counter;
                                current_block_175 = 16718638665978159145;
                            } else {
                                (*s).state = BROTLI_STATE_HUFFMAN_CODE_1;
                                current_block_175 = 5023038348526654800;
                            }
                        }
                    }
                }
                _ => {}
            }
            match current_block_175 {
                5023038348526654800 => {
                    let mut alphabet_size: uint32_t = ((*s)
                        .num_block_types[(*s).loop_counter as usize])
                        .wrapping_add(2 as libc::c_int as uint32_t);
                    let mut tree_offset: libc::c_int = (*s).loop_counter
                        * 632 as libc::c_int;
                    result = ReadHuffmanCode(
                        alphabet_size,
                        alphabet_size,
                        &mut *((*s).block_type_trees).offset(tree_offset as isize),
                        0 as *mut uint32_t,
                        s,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).state = BROTLI_STATE_HUFFMAN_CODE_2;
                        current_block_175 = 6712462580143783635;
                    }
                }
                12386775860387733485 => {
                    current_block_175 = 6546859112865444725;
                }
                _ => {}
            }
            match current_block_175 {
                6712462580143783635 => {
                    let mut alphabet_size_0: uint32_t = 26 as libc::c_int as uint32_t;
                    let mut tree_offset_0: libc::c_int = (*s).loop_counter
                        * 396 as libc::c_int;
                    result = ReadHuffmanCode(
                        alphabet_size_0,
                        alphabet_size_0,
                        &mut *((*s).block_len_trees).offset(tree_offset_0 as isize),
                        0 as *mut uint32_t,
                        s,
                    );
                    if result as libc::c_int != BROTLI_DECODER_SUCCESS as libc::c_int {
                        current_block_175 = 16718638665978159145;
                    } else {
                        (*s).state = BROTLI_STATE_HUFFMAN_CODE_3;
                        current_block_175 = 15622658527355336244;
                    }
                }
                6546859112865444725 => {
                    current_block_175 = 4508254836030314814;
                }
                _ => {}
            }
            match current_block_175 {
                4508254836030314814 => {
                    result = ProcessCommands(s);
                    if result as libc::c_int
                        == BROTLI_DECODER_NEEDS_MORE_INPUT as libc::c_int
                    {
                        result = SafeProcessCommands(s);
                    }
                }
                15622658527355336244 => {
                    let mut tree_offset_1: libc::c_int = (*s).loop_counter
                        * 396 as libc::c_int;
                    if SafeReadBlockLength(
                        s,
                        &mut *((*s).block_length)
                            .as_mut_ptr()
                            .offset((*s).loop_counter as isize),
                        &mut *((*s).block_len_trees).offset(tree_offset_1 as isize),
                        br,
                    ) == 0
                    {
                        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
                    } else {
                        (*s).loop_counter += 1;
                        (*s).loop_counter;
                        (*s).state = BROTLI_STATE_HUFFMAN_CODE_0;
                    }
                }
                _ => {}
            }
        }
    }
    return SaveErrorCode(s, result);
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderHasMoreOutput(
    mut s: *const BrotliDecoderStateInternal,
) -> libc::c_int {
    if (*s).error_code < 0 as libc::c_int {
        return 0 as libc::c_int;
    }
    return if !((*s).ringbuffer).is_null()
        && UnwrittenBytes(s, 0 as libc::c_int) != 0 as libc::c_int as size_t
    {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderTakeOutput(
    mut s: *mut BrotliDecoderStateInternal,
    mut size: *mut size_t,
) -> *const uint8_t {
    let mut result: *mut uint8_t = 0 as *mut uint8_t;
    let mut available_out: size_t = if *size != 0 {
        *size
    } else {
        ((1 as libc::c_uint) << 24 as libc::c_int) as size_t
    };
    let mut requested_out: size_t = available_out;
    let mut status: BrotliDecoderErrorCode = BROTLI_DECODER_NO_ERROR;
    if ((*s).ringbuffer).is_null() || (*s).error_code < 0 as libc::c_int {
        *size = 0 as libc::c_int as size_t;
        return 0 as *const uint8_t;
    }
    WrapRingBuffer(s);
    status = WriteRingBuffer(
        s,
        &mut available_out,
        &mut result,
        0 as *mut size_t,
        1 as libc::c_int,
    );
    if status as libc::c_int == BROTLI_DECODER_SUCCESS as libc::c_int
        || status as libc::c_int == BROTLI_DECODER_NEEDS_MORE_OUTPUT as libc::c_int
    {
        *size = requested_out.wrapping_sub(available_out);
    } else {
        if (status as libc::c_int) < 0 as libc::c_int {
            SaveErrorCode(s, status);
        }
        *size = 0 as libc::c_int as size_t;
        result = 0 as *mut uint8_t;
    }
    return result;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderIsUsed(
    mut s: *const BrotliDecoderStateInternal,
) -> libc::c_int {
    return if (*s).state as libc::c_uint
        != BROTLI_STATE_UNINITED as libc::c_int as libc::c_uint
        || BrotliGetAvailableBits(&(*s).br) != 0 as libc::c_int as uint32_t
    {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    };
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderIsFinished(
    mut s: *const BrotliDecoderStateInternal,
) -> libc::c_int {
    return ((if (*s).state as libc::c_uint
        == BROTLI_STATE_DONE as libc::c_int as libc::c_uint
    {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    }) != 0 && BrotliDecoderHasMoreOutput(s) == 0) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderGetErrorCode(
    mut s: *const BrotliDecoderStateInternal,
) -> BrotliDecoderErrorCode {
    return (*s).error_code as BrotliDecoderErrorCode;
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderErrorString(
    mut c: BrotliDecoderErrorCode,
) -> *const libc::c_char {
    match c as libc::c_int {
        0 => return b"NO_ERROR\0" as *const u8 as *const libc::c_char,
        1 => return b"SUCCESS\0" as *const u8 as *const libc::c_char,
        2 => return b"NEEDS_MORE_INPUT\0" as *const u8 as *const libc::c_char,
        3 => return b"NEEDS_MORE_OUTPUT\0" as *const u8 as *const libc::c_char,
        -1 => return b"EXUBERANT_NIBBLE\0" as *const u8 as *const libc::c_char,
        -2 => return b"RESERVED\0" as *const u8 as *const libc::c_char,
        -3 => return b"EXUBERANT_META_NIBBLE\0" as *const u8 as *const libc::c_char,
        -4 => return b"SIMPLE_HUFFMAN_ALPHABET\0" as *const u8 as *const libc::c_char,
        -5 => return b"SIMPLE_HUFFMAN_SAME\0" as *const u8 as *const libc::c_char,
        -6 => return b"CL_SPACE\0" as *const u8 as *const libc::c_char,
        -7 => return b"HUFFMAN_SPACE\0" as *const u8 as *const libc::c_char,
        -8 => return b"CONTEXT_MAP_REPEAT\0" as *const u8 as *const libc::c_char,
        -9 => return b"BLOCK_LENGTH_1\0" as *const u8 as *const libc::c_char,
        -10 => return b"BLOCK_LENGTH_2\0" as *const u8 as *const libc::c_char,
        -11 => return b"TRANSFORM\0" as *const u8 as *const libc::c_char,
        -12 => return b"DICTIONARY\0" as *const u8 as *const libc::c_char,
        -13 => return b"WINDOW_BITS\0" as *const u8 as *const libc::c_char,
        -14 => return b"PADDING_1\0" as *const u8 as *const libc::c_char,
        -15 => return b"PADDING_2\0" as *const u8 as *const libc::c_char,
        -16 => return b"DISTANCE\0" as *const u8 as *const libc::c_char,
        -19 => return b"DICTIONARY_NOT_SET\0" as *const u8 as *const libc::c_char,
        -20 => return b"INVALID_ARGUMENTS\0" as *const u8 as *const libc::c_char,
        -21 => return b"CONTEXT_MODES\0" as *const u8 as *const libc::c_char,
        -22 => return b"TREE_GROUPS\0" as *const u8 as *const libc::c_char,
        -25 => return b"CONTEXT_MAP\0" as *const u8 as *const libc::c_char,
        -26 => return b"RING_BUFFER_1\0" as *const u8 as *const libc::c_char,
        -27 => return b"RING_BUFFER_2\0" as *const u8 as *const libc::c_char,
        -30 => return b"BLOCK_TYPE_TREES\0" as *const u8 as *const libc::c_char,
        -31 => return b"UNREACHABLE\0" as *const u8 as *const libc::c_char,
        _ => return b"INVALID\0" as *const u8 as *const libc::c_char,
    };
}
#[no_mangle]
pub unsafe extern "C" fn BrotliDecoderVersion() -> uint32_t {
    return 0x1000009 as libc::c_int as uint32_t;
}
