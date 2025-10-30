typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
/*** DEPENDENCIES:
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
----------------------------
***/


