struct BrotliDecoderStateStruct
{
  BrotliRunningState state;
  int loop_counter;
  BrotliBitReader br;
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *memory_manager_opaque;
  union 
  {
    uint64_t u64;
    uint8_t u8[8];
  } buffer;
  uint32_t buffer_length;
  int pos;
  int max_backward_distance;
  int max_distance;
  int ringbuffer_size;
  int ringbuffer_mask;
  int dist_rb_idx;
  int dist_rb[4];
  int error_code;
  uint8_t *ringbuffer;
  uint8_t *ringbuffer_end;
  HuffmanCode *htree_command;
  const uint8_t *context_lookup;
  uint8_t *context_map_slice;
  uint8_t *dist_context_map_slice;
  HuffmanTreeGroup literal_hgroup;
  HuffmanTreeGroup insert_copy_hgroup;
  HuffmanTreeGroup distance_hgroup;
  HuffmanCode *block_type_trees;
  HuffmanCode *block_len_trees;
  int trivial_literal_context;
  int distance_context;
  int meta_block_remaining_len;
  uint32_t block_length_index;
  uint32_t block_length[3];
  uint32_t num_block_types[3];
  uint32_t block_type_rb[6];
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t num_dist_htrees;
  uint8_t *dist_context_map;
  HuffmanCode *literal_htree;
  uint8_t dist_htree_index;
  int copy_length;
  int distance_code;
  size_t rb_roundtrips;
  size_t partial_pos_out;
  uint32_t mtf_upper_bound;
  uint32_t mtf[64 + 1];
  BrotliRunningMetablockHeaderState substate_metablock_header;
  BrotliRunningUncompressedState substate_uncompressed;
  BrotliRunningDecodeUint8State substate_decode_uint8;
  BrotliRunningReadBlockLengthState substate_read_block_length;
  unsigned int is_last_metablock : 1;
  unsigned int is_uncompressed : 1;
  unsigned int is_metadata : 1;
  unsigned int should_wrap_ringbuffer : 1;
  unsigned int canny_ringbuffer_allocation : 1;
  unsigned int large_window : 1;
  unsigned int size_nibbles : 8;
  uint32_t window_bits;
  int new_ringbuffer_size;
  uint32_t num_literal_htrees;
  uint8_t *context_map;
  uint8_t *context_modes;
  const BrotliDictionary *dictionary;
  const BrotliTransforms *transforms;
  uint32_t trivial_literal_contexts[8];
  union 
  {
    BrotliMetablockHeaderArena header;
    BrotliMetablockBodyArena body;
  } arena;
}
/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef struct BrotliTransforms
{
  uint16_t prefix_suffix_size;
  const uint8_t *prefix_suffix;
  const uint16_t *prefix_suffix_map;
  uint32_t num_transforms;
  const uint8_t *transforms;
  const uint8_t *params;
  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms
----------------------------
typedef enum 
{
  BROTLI_STATE_METABLOCK_HEADER_NONE,
  BROTLI_STATE_METABLOCK_HEADER_EMPTY,
  BROTLI_STATE_METABLOCK_HEADER_NIBBLES,
  BROTLI_STATE_METABLOCK_HEADER_SIZE,
  BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED,
  BROTLI_STATE_METABLOCK_HEADER_RESERVED,
  BROTLI_STATE_METABLOCK_HEADER_BYTES,
  BROTLI_STATE_METABLOCK_HEADER_METADATA
} BrotliRunningMetablockHeaderState
----------------------------
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
typedef enum 
{
  BROTLI_STATE_UNINITED,
  BROTLI_STATE_LARGE_WINDOW_BITS,
  BROTLI_STATE_INITIALIZE,
  BROTLI_STATE_METABLOCK_BEGIN,
  BROTLI_STATE_METABLOCK_HEADER,
  BROTLI_STATE_METABLOCK_HEADER_2,
  BROTLI_STATE_CONTEXT_MODES,
  BROTLI_STATE_COMMAND_BEGIN,
  BROTLI_STATE_COMMAND_INNER,
  BROTLI_STATE_COMMAND_POST_DECODE_LITERALS,
  BROTLI_STATE_COMMAND_POST_WRAP_COPY,
  BROTLI_STATE_UNCOMPRESSED,
  BROTLI_STATE_METADATA,
  BROTLI_STATE_COMMAND_INNER_WRITE,
  BROTLI_STATE_METABLOCK_DONE,
  BROTLI_STATE_COMMAND_POST_WRITE_1,
  BROTLI_STATE_COMMAND_POST_WRITE_2,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER,
  BROTLI_STATE_HUFFMAN_CODE_0,
  BROTLI_STATE_HUFFMAN_CODE_1,
  BROTLI_STATE_HUFFMAN_CODE_2,
  BROTLI_STATE_HUFFMAN_CODE_3,
  BROTLI_STATE_CONTEXT_MAP_1,
  BROTLI_STATE_CONTEXT_MAP_2,
  BROTLI_STATE_TREE_GROUP,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY,
  BROTLI_STATE_DONE
} BrotliRunningState
----------------------------
typedef struct BrotliDictionary
{
  uint8_t size_bits_by_length[32];
  uint32_t offsets_by_length[32];
  size_t data_size;
  const uint8_t *data;
} BrotliDictionary
----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
typedef struct BrotliMetablockHeaderArena
{
  BrotliRunningTreeGroupState substate_tree_group;
  BrotliRunningContextMapState substate_context_map;
  BrotliRunningHuffmanState substate_huffman;
  uint32_t sub_loop_counter;
  uint32_t repeat_code_len;
  uint32_t prev_code_len;
  uint32_t symbol;
  uint32_t repeat;
  uint32_t space;
  HuffmanCode table[32];
  uint16_t *symbol_lists;
  uint16_t symbols_lists_array[(15 + 1) + 704];
  int next_symbol[32];
  uint8_t code_length_code_lengths[17 + 1];
  uint16_t code_length_histo[16];
  int htree_index;
  HuffmanCode *next;
  uint32_t context_index;
  uint32_t max_run_length_prefix;
  uint32_t code;
  HuffmanCode context_map_table[646];
} BrotliMetablockHeaderArena
----------------------------
typedef void *(*brotli_alloc_func)(void *opaque, size_t size)
----------------------------
typedef enum 
{
  BROTLI_STATE_READ_BLOCK_LENGTH_NONE,
  BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX
} BrotliRunningReadBlockLengthState
----------------------------
typedef struct 
{
  HuffmanCode **htrees;
  HuffmanCode *codes;
  uint16_t alphabet_size_max;
  uint16_t alphabet_size_limit;
  uint16_t num_htrees;
} HuffmanTreeGroup
----------------------------
typedef struct BrotliMetablockBodyArena
{
  uint8_t dist_extra_bits[544];
  uint32_t dist_offset[544];
} BrotliMetablockBodyArena
----------------------------
typedef enum 
{
  BROTLI_STATE_DECODE_UINT8_NONE,
  BROTLI_STATE_DECODE_UINT8_SHORT,
  BROTLI_STATE_DECODE_UINT8_LONG
} BrotliRunningDecodeUint8State
----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
typedef enum 
{
  BROTLI_STATE_UNCOMPRESSED_NONE,
  BROTLI_STATE_UNCOMPRESSED_WRITE
} BrotliRunningUncompressedState
----------------------------
***/


