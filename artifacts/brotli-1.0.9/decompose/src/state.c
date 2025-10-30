void BrotliDecoderStateMetablockBegin(BrotliDecoderStateInternal *s)
{
  s->meta_block_remaining_len = 0;
  s->block_length[0] = 1U << 24;
  s->block_length[1] = 1U << 24;
  s->block_length[2] = 1U << 24;
  s->num_block_types[0] = 1;
  s->num_block_types[1] = 1;
  s->num_block_types[2] = 1;
  s->block_type_rb[0] = 1;
  s->block_type_rb[1] = 0;
  s->block_type_rb[2] = 1;
  s->block_type_rb[3] = 0;
  s->block_type_rb[4] = 1;
  s->block_type_rb[5] = 0;
  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->literal_htree = 0;
  s->dist_context_map_slice = 0;
  s->dist_htree_index = 0;
  s->context_lookup = 0;
  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;
}


/*** DEPENDENCIES:
typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
***/


void BrotliDecoderStateCleanupAfterMetablock(BrotliDecoderStateInternal *s)
{
  {
    s->free_func(s->memory_manager_opaque, s->context_modes);
    s->context_modes = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->context_map);
    s->context_map = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->dist_context_map);
    s->dist_context_map = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->literal_hgroup.htrees);
    s->literal_hgroup.htrees = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->insert_copy_hgroup.htrees);
    s->insert_copy_hgroup.htrees = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->distance_hgroup.htrees);
    s->distance_hgroup.htrees = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
***/


void BrotliDecoderStateCleanup(BrotliDecoderStateInternal *s)
{
  BrotliDecoderStateCleanupAfterMetablock(s);
  {
    s->free_func(s->memory_manager_opaque, s->ringbuffer);
    s->ringbuffer = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->block_type_trees);
    s->block_type_trees = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
----------------------------
void BrotliDecoderStateCleanupAfterMetablock(BrotliDecoderStateInternal *s)
{
  {
    s->free_func(s->memory_manager_opaque, s->context_modes);
    s->context_modes = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->context_map);
    s->context_map = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->dist_context_map);
    s->dist_context_map = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->literal_hgroup.htrees);
    s->literal_hgroup.htrees = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->insert_copy_hgroup.htrees);
    s->insert_copy_hgroup.htrees = 0;
  }
  ;
  {
    s->free_func(s->memory_manager_opaque, s->distance_hgroup.htrees);
    s->distance_hgroup.htrees = 0;
  }
  ;
}


----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
***/


int BrotliDecoderStateInit(BrotliDecoderStateInternal *s, brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  if (!alloc_func)
  {
    s->alloc_func = BrotliDefaultAllocFunc;
    s->free_func = BrotliDefaultFreeFunc;
    s->memory_manager_opaque = 0;
  }
  else
  {
    s->alloc_func = alloc_func;
    s->free_func = free_func;
    s->memory_manager_opaque = opaque;
  }
  s->error_code = 0;
  BrotliInitBitReader(&s->br);
  s->state = BROTLI_STATE_UNINITED;
  s->large_window = 0;
  s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
  s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
  s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
  s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
  s->buffer_length = 0;
  s->loop_counter = 0;
  s->pos = 0;
  s->rb_roundtrips = 0;
  s->partial_pos_out = 0;
  s->block_type_trees = 0;
  s->block_len_trees = 0;
  s->ringbuffer = 0;
  s->ringbuffer_size = 0;
  s->new_ringbuffer_size = 0;
  s->ringbuffer_mask = 0;
  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->dist_context_map_slice = 0;
  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;
  s->is_last_metablock = 0;
  s->is_uncompressed = 0;
  s->is_metadata = 0;
  s->should_wrap_ringbuffer = 0;
  s->canny_ringbuffer_allocation = 1;
  s->window_bits = 0;
  s->max_distance = 0;
  s->dist_rb[0] = 16;
  s->dist_rb[1] = 15;
  s->dist_rb[2] = 11;
  s->dist_rb[3] = 4;
  s->dist_rb_idx = 0;
  s->block_type_trees = 0;
  s->block_len_trees = 0;
  s->mtf_upper_bound = 63;
  s->dictionary = BrotliGetDictionary();
  s->transforms = BrotliGetTransforms();
  return 1;
}


/*** DEPENDENCIES:
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
void BrotliDefaultFreeFunc(void *opaque, void *address)
{
  (void) opaque;
  free(address);
}


----------------------------
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
const BrotliTransforms *BrotliGetTransforms(void)
{
  return &kBrotliTransforms;
}


----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
----------------------------
const BrotliDictionary *BrotliGetDictionary()
{
  return &kBrotliDictionary;
}


----------------------------
void BrotliInitBitReader(BrotliBitReader * const br)
{
  br->val_ = 0;
  br->bit_pos_ = (sizeof(br->val_)) << 3;
}


----------------------------
typedef void *(*brotli_alloc_func)(void *opaque, size_t size)
----------------------------
void *BrotliDefaultAllocFunc(void *opaque, size_t size)
{
  (void) opaque;
  return malloc(size);
}


----------------------------
***/


int BrotliDecoderHuffmanTreeGroupInit(BrotliDecoderStateInternal *s, HuffmanTreeGroup *group, uint32_t alphabet_size_max, uint32_t alphabet_size_limit, uint32_t ntrees)
{
  const size_t max_table_size = alphabet_size_limit + 376;
  const size_t code_size = ((sizeof(HuffmanCode)) * ntrees) * max_table_size;
  const size_t htree_size = (sizeof(HuffmanCode *)) * ntrees;
  HuffmanCode **p = (HuffmanCode **) s->alloc_func(s->memory_manager_opaque, code_size + htree_size);
  group->alphabet_size_max = (uint16_t) alphabet_size_max;
  group->alphabet_size_limit = (uint16_t) alphabet_size_limit;
  group->num_htrees = (uint16_t) ntrees;
  group->htrees = p;
  group->codes = (HuffmanCode *) (&p[ntrees]);
  return !(!p);
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal
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
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


