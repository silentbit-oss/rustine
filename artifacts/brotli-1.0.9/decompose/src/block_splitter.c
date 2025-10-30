inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


/*** DEPENDENCIES:
***/


static size_t RemapBlockIdsLiteral(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


/*** DEPENDENCIES:
***/


static size_t RemapBlockIdsCommand(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


/*** DEPENDENCIES:
***/


static size_t RemapBlockIdsDistance(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


/*** DEPENDENCIES:
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t']
void helper_FindBlocksLiteral_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


/*** DEPENDENCIES:
***/


void helper_FindBlocksLiteral_2(const uint8_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


/*** DEPENDENCIES:
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t']
void helper_FindBlocksCommand_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


/*** DEPENDENCIES:
***/


void helper_FindBlocksCommand_2(const uint16_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


/*** DEPENDENCIES:
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t']
void helper_FindBlocksDistance_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


/*** DEPENDENCIES:
***/


void helper_FindBlocksDistance_2(const uint16_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


/*** DEPENDENCIES:
***/


void BrotliInitBlockSplit(BlockSplit *self)
{
  self->num_types = 0;
  self->num_blocks = 0;
  self->types = 0;
  self->lengths = 0;
  self->types_alloc_size = 0;
  self->lengths_alloc_size = 0;
}


/*** DEPENDENCIES:
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
***/


static size_t CountLiterals(const Command *cmds, const size_t num_commands)
{
  size_t total_length = 0;
  size_t i;
  for (i = 0; i < num_commands; i += 1)
  {
    total_length += cmds[i].insert_len_;
  }

  return total_length;
}


/*** DEPENDENCIES:
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


inline static double BitCost(size_t count)
{
  return (count == 0) ? (-2.0) : (FastLog2(count));
}


/*** DEPENDENCIES:
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
***/


static void CopyLiteralsToByteArray(const Command *cmds, const size_t num_commands, const uint8_t *data, const size_t offset, const size_t mask, uint8_t *literals)
{
  size_t pos = 0;
  size_t from_pos = offset & mask;
  size_t i;
  for (i = 0; i < num_commands; i += 1)
  {
    size_t insert_len = cmds[i].insert_len_;
    if ((from_pos + insert_len) > mask)
    {
      size_t head_size = (mask + 1) - from_pos;
      memcpy(literals + pos, data + from_pos, head_size);
      from_pos = 0;
      pos += head_size;
      insert_len -= head_size;
    }
    if (insert_len > 0)
    {
      memcpy(literals + pos, data + from_pos, insert_len);
      pos += insert_len;
    }
    from_pos = ((from_pos + insert_len) + CommandCopyLen(&cmds[i])) & mask;
  }

}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksLiteral_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksCommand_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
***/


// hint:  ['num_blocks_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksDistance_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
***/


void BrotliDestroyBlockSplit(MemoryManager *m, BlockSplit *self)
{
  {
    BrotliFree(m, self->types);
    self->types = 0;
  }
  ;
  {
    BrotliFree(m, self->lengths);
    self->lengths = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


static void RandomSampleDistance(uint32_t *seed, const uint16_t *data, size_t length, size_t stride, HistogramDistance *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorDistance(sample, data + pos, stride);
}


/*** DEPENDENCIES:
inline static void HistogramAddVectorDistance(HistogramDistance *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


static void RefineEntropyCodesDistance(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramDistance *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramDistance sample;
    HistogramClearDistance(&sample);
    RandomSampleDistance(&seed, data, length, stride, &sample);
    HistogramAddHistogramDistance(&histograms[iter % num_histograms], &sample);
  }

}


/*** DEPENDENCIES:
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
static void RandomSampleDistance(uint32_t *seed, const uint16_t *data, size_t length, size_t stride, HistogramDistance *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorDistance(sample, data + pos, stride);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
static const size_t kIterMulForRefining = 2
----------------------------
static const size_t kMinItersForRefining = 100
----------------------------
inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
***/


void helper_helper_SplitByteVectorDistance_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_helper_SplitByteVectorDistance_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_SplitByteVectorDistance_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorDistance_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorDistance_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_helper_SplitByteVectorDistance_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
void helper_helper_SplitByteVectorDistance_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
***/


static void InitialEntropyCodesDistance(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramDistance *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsDistance(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorDistance(&histograms[i], data + pos, stride);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddVectorDistance(HistogramDistance *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
inline static void ClearHistogramsDistance(HistogramDistance *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearDistance(array + i);

}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


static size_t FindBlocksDistance(const uint16_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramDistance *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeDistance();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksDistance_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksDistance_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
void helper_FindBlocksDistance_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


----------------------------
void helper_FindBlocksDistance_2(const uint16_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
inline static double BitCost(size_t count)
{
  return (count == 0) ? (-2.0) : (FastLog2(count));
}


----------------------------
inline static size_t HistogramDataSizeDistance(void)
{
  return 544;
}


----------------------------
***/


// hint:  ['all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksDistance_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramDistance * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramDistance *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, _new_size * (sizeof(HistogramDistance)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramDistance)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


// hint:  ['cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksDistance_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'all_histograms_size_ref is a mutable refrence to size_t', 'all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int', 'cluster_size_size_ref is a mutable refrence to size_t', 'cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int', 'num_clusters_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksDistance_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramDistance * const all_histograms, uint32_t * const cluster_size, HistogramDistance * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearDistance(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddDistance(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostDistance(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineDistance(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksDistance_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksDistance_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void helper_helper_ClusterBlocksDistance_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramDistance * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramDistance *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, _new_size * (sizeof(HistogramDistance)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramDistance)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
double BrotliPopulationCostDistance(const HistogramDistance *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeDistance();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostDistance_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostDistance_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
size_t BrotliHistogramCombineDistance(HistogramDistance *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueDistance(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineDistance_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
void helper_helper_ClusterBlocksDistance_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'new_index_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksDistance_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramDistance * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramDistance histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearDistance(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddDistance(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceDistance(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceDistance(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
double BrotliHistogramBitCostDistanceDistance(const HistogramDistance *histogram, const HistogramDistance *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramDistance tmp = *histogram;
    HistogramAddHistogramDistance(&tmp, candidate);
    return BrotliPopulationCostDistance(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


void helper_ClusterBlocksDistance_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_ClusterBlocksDistance_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


static void ClusterBlocksDistance(MemoryManager *m, const uint16_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramDistance *all_histograms = (all_histograms_capacity > 0) ? ((HistogramDistance *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramDistance)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramDistance *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramDistance *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramDistance)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksDistance_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineDistance(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksDistance_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksDistance_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksDistance_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksDistance_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_ClusterBlocksDistance_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


----------------------------
void helper_ClusterBlocksDistance_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramDistance * const all_histograms, uint32_t * const cluster_size, HistogramDistance * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearDistance(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddDistance(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostDistance(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineDistance(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksDistance_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksDistance_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


----------------------------
void helper_ClusterBlocksDistance_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramDistance * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramDistance histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearDistance(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddDistance(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceDistance(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceDistance(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
void helper_ClusterBlocksDistance_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
size_t BrotliHistogramCombineDistance(HistogramDistance *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueDistance(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineDistance_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_ClusterBlocksDistance_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
***/


static void BuildBlockHistogramsDistance(const uint16_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramDistance *histograms)
{
  size_t i;
  ClearHistogramsDistance(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddDistance(&histograms[block_ids[i]], data[i]);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
inline static void ClearHistogramsDistance(HistogramDistance *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearDistance(array + i);

}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


// hint:  ['num_histograms_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int']
void helper_SplitByteVectorDistance_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint16_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramDistance * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksDistance(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsDistance(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsDistance(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksDistance(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static size_t FindBlocksDistance(const uint16_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramDistance *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeDistance();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksDistance_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksDistance_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


----------------------------
static void ClusterBlocksDistance(MemoryManager *m, const uint16_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramDistance *all_histograms = (all_histograms_capacity > 0) ? ((HistogramDistance *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramDistance)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramDistance *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramDistance *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramDistance)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksDistance_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineDistance(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksDistance_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksDistance_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksDistance_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksDistance_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
static void BuildBlockHistogramsDistance(const uint16_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramDistance *histograms)
{
  size_t i;
  ClearHistogramsDistance(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddDistance(&histograms[block_ids[i]], data[i]);
  }

}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
static size_t RemapBlockIdsDistance(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


static void SplitByteVectorDistance(MemoryManager *m, const uint16_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeDistance();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramDistance *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorDistance_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramDistance *) BrotliAllocate(m, num_histograms * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesDistance(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesDistance(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorDistance_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


/*** DEPENDENCIES:
static const size_t kMinLengthForBlockSplitting = 128
----------------------------
static void RefineEntropyCodesDistance(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramDistance *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramDistance sample;
    HistogramClearDistance(&sample);
    RandomSampleDistance(&seed, data, length, stride, &sample);
    HistogramAddHistogramDistance(&histograms[iter % num_histograms], &sample);
  }

}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void helper_SplitByteVectorDistance_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorDistance_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorDistance_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
static void InitialEntropyCodesDistance(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramDistance *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsDistance(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorDistance(&histograms[i], data + pos, stride);
  }

}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_SplitByteVectorDistance_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint16_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramDistance * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksDistance(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsDistance(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsDistance(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksDistance(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


----------------------------
inline static size_t HistogramDataSizeDistance(void)
{
  return 544;
}


----------------------------
None
----------------------------
***/


void helper_BrotliSplitBlock_3(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const BrotliEncoderParams * const params, BlockSplit * const dist_split)
{
  uint16_t *distance_prefixes = (num_commands > 0) ? ((uint16_t *) BrotliAllocate(m, num_commands * (sizeof(uint16_t)))) : (0);
  unsigned int distance_prefixes_idx = 0;
  size_t j = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      distance_prefixes[j + distance_prefixes_idx] = cmd->dist_prefix_ & 0x3FF;
      j += 1;
    }
  }

  SplitByteVectorDistance(m, distance_prefixes, j, kSymbolsPerDistanceHistogram, kMaxCommandHistograms, kCommandStrideLength, kDistanceBlockSwitchCost, params, dist_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, distance_prefixes);
    distance_prefixes_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static const size_t kMaxCommandHistograms = 50
----------------------------
static void SplitByteVectorDistance(MemoryManager *m, const uint16_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeDistance();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramDistance *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorDistance_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramDistance *) BrotliAllocate(m, num_histograms * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesDistance(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesDistance(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorDistance_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


----------------------------
static const size_t kCommandStrideLength = 40
----------------------------
static const size_t kSymbolsPerDistanceHistogram = 544
----------------------------
static const double kDistanceBlockSwitchCost = 14.6
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


static void RandomSampleCommand(uint32_t *seed, const uint16_t *data, size_t length, size_t stride, HistogramCommand *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorCommand(sample, data + pos, stride);
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static void HistogramAddVectorCommand(HistogramCommand *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


static void RefineEntropyCodesCommand(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramCommand *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramCommand sample;
    HistogramClearCommand(&sample);
    RandomSampleCommand(&seed, data, length, stride, &sample);
    HistogramAddHistogramCommand(&histograms[iter % num_histograms], &sample);
  }

}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
static void RandomSampleCommand(uint32_t *seed, const uint16_t *data, size_t length, size_t stride, HistogramCommand *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorCommand(sample, data + pos, stride);
}


----------------------------
static const size_t kIterMulForRefining = 2
----------------------------
inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
static const size_t kMinItersForRefining = 100
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
***/


static void InitialEntropyCodesCommand(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramCommand *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsCommand(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorCommand(&histograms[i], data + pos, stride);
  }

}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static void ClearHistogramsCommand(HistogramCommand *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearCommand(array + i);

}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
inline static void HistogramAddVectorCommand(HistogramCommand *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
***/


void helper_helper_SplitByteVectorCommand_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_helper_SplitByteVectorCommand_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_SplitByteVectorCommand_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorCommand_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorCommand_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_helper_SplitByteVectorCommand_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
void helper_helper_SplitByteVectorCommand_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'new_index_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksCommand_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramCommand * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramCommand histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearCommand(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddCommand(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceCommand(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceCommand(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
double BrotliHistogramBitCostDistanceCommand(const HistogramCommand *histogram, const HistogramCommand *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramCommand tmp = *histogram;
    HistogramAddHistogramCommand(&tmp, candidate);
    return BrotliPopulationCostCommand(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


void helper_ClusterBlocksCommand_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_ClusterBlocksCommand_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksCommand_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksCommand_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramCommand * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramCommand *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramCommand *) BrotliAllocate(m, _new_size * (sizeof(HistogramCommand)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramCommand)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'all_histograms_size_ref is a mutable refrence to size_t', 'all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int', 'cluster_size_size_ref is a mutable refrence to size_t', 'cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int', 'num_clusters_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksCommand_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramCommand * const all_histograms, uint32_t * const cluster_size, HistogramCommand * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearCommand(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddCommand(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostCommand(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineCommand(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksCommand_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksCommand_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
size_t BrotliHistogramCombineCommand(HistogramCommand *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueCommand(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineCommand_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
void helper_helper_ClusterBlocksCommand_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


----------------------------
double BrotliPopulationCostCommand(const HistogramCommand *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeCommand();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostCommand_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostCommand_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_helper_ClusterBlocksCommand_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramCommand * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramCommand *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramCommand *) BrotliAllocate(m, _new_size * (sizeof(HistogramCommand)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramCommand)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


static void ClusterBlocksCommand(MemoryManager *m, const uint16_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramCommand *all_histograms = (all_histograms_capacity > 0) ? ((HistogramCommand *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramCommand)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramCommand *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramCommand *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramCommand)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksCommand_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineCommand(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksCommand_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksCommand_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksCommand_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksCommand_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
void helper_ClusterBlocksCommand_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


----------------------------
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
size_t BrotliHistogramCombineCommand(HistogramCommand *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueCommand(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineCommand_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
void helper_ClusterBlocksCommand_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramCommand * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramCommand histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearCommand(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddCommand(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceCommand(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceCommand(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


----------------------------
void helper_ClusterBlocksCommand_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
void helper_ClusterBlocksCommand_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_ClusterBlocksCommand_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint16_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramCommand * const all_histograms, uint32_t * const cluster_size, HistogramCommand * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearCommand(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddCommand(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostCommand(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineCommand(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksCommand_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksCommand_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


----------------------------
***/


static void BuildBlockHistogramsCommand(const uint16_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramCommand *histograms)
{
  size_t i;
  ClearHistogramsCommand(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddCommand(&histograms[block_ids[i]], data[i]);
  }

}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
inline static void ClearHistogramsCommand(HistogramCommand *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearCommand(array + i);

}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


static size_t FindBlocksCommand(const uint16_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramCommand *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeCommand();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksCommand_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksCommand_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static size_t HistogramDataSizeCommand(void)
{
  return 704;
}


----------------------------
void helper_FindBlocksCommand_2(const uint16_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
inline static double BitCost(size_t count)
{
  return (count == 0) ? (-2.0) : (FastLog2(count));
}


----------------------------
void helper_FindBlocksCommand_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


----------------------------
***/


// hint:  ['num_histograms_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int']
void helper_SplitByteVectorCommand_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint16_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramCommand * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksCommand(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsCommand(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsCommand(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksCommand(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
static void ClusterBlocksCommand(MemoryManager *m, const uint16_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramCommand *all_histograms = (all_histograms_capacity > 0) ? ((HistogramCommand *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramCommand)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramCommand *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramCommand *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramCommand)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksCommand_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineCommand(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksCommand_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksCommand_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksCommand_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksCommand_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static void BuildBlockHistogramsCommand(const uint16_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramCommand *histograms)
{
  size_t i;
  ClearHistogramsCommand(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddCommand(&histograms[block_ids[i]], data[i]);
  }

}


----------------------------
static size_t RemapBlockIdsCommand(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


----------------------------
static size_t FindBlocksCommand(const uint16_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramCommand *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeCommand();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksCommand_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksCommand_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


static void SplitByteVectorCommand(MemoryManager *m, const uint16_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeCommand();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramCommand *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorCommand_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramCommand *) BrotliAllocate(m, num_histograms * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesCommand(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesCommand(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorCommand_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


/*** DEPENDENCIES:
static const size_t kMinLengthForBlockSplitting = 128
----------------------------
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
static void RefineEntropyCodesCommand(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramCommand *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramCommand sample;
    HistogramClearCommand(&sample);
    RandomSampleCommand(&seed, data, length, stride, &sample);
    HistogramAddHistogramCommand(&histograms[iter % num_histograms], &sample);
  }

}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static void InitialEntropyCodesCommand(const uint16_t *data, size_t length, size_t stride, size_t num_histograms, HistogramCommand *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsCommand(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorCommand(&histograms[i], data + pos, stride);
  }

}


----------------------------
inline static size_t HistogramDataSizeCommand(void)
{
  return 704;
}


----------------------------
void helper_SplitByteVectorCommand_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorCommand_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorCommand_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_SplitByteVectorCommand_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint16_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramCommand * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksCommand(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsCommand(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsCommand(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksCommand(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


----------------------------
None
----------------------------
***/


void helper_BrotliSplitBlock_2(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const BrotliEncoderParams * const params, BlockSplit * const insert_and_copy_split)
{
  uint16_t *insert_and_copy_codes = (num_commands > 0) ? ((uint16_t *) BrotliAllocate(m, num_commands * (sizeof(uint16_t)))) : (0);
  unsigned int insert_and_copy_codes_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    insert_and_copy_codes[i + insert_and_copy_codes_idx] = cmds[i].cmd_prefix_;
  }

  SplitByteVectorCommand(m, insert_and_copy_codes, num_commands, kSymbolsPerCommandHistogram, kMaxCommandHistograms, kCommandStrideLength, kCommandBlockSwitchCost, params, insert_and_copy_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, insert_and_copy_codes);
    insert_and_copy_codes_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
static void SplitByteVectorCommand(MemoryManager *m, const uint16_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeCommand();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramCommand *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorCommand_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramCommand *) BrotliAllocate(m, num_histograms * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesCommand(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesCommand(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorCommand_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static const size_t kMaxCommandHistograms = 50
----------------------------
static const size_t kSymbolsPerCommandHistogram = 530
----------------------------
static const size_t kCommandStrideLength = 40
----------------------------
static const double kCommandBlockSwitchCost = 13.5
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


void helper_ClusterBlocksLiteral_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksLiteral_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int']
void helper_helper_ClusterBlocksLiteral_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramLiteral * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramLiteral *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, _new_size * (sizeof(HistogramLiteral)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramLiteral)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'all_histograms_size_ref is a mutable refrence to size_t', 'all_histograms_capacity_ref is a mutable refrence to size_t', 'all_histograms_idx_ref is a mutable refrence to unsigned int', 'cluster_size_size_ref is a mutable refrence to size_t', 'cluster_size_capacity_ref is a mutable refrence to size_t', 'cluster_size_idx_ref is a mutable refrence to unsigned int', 'num_clusters_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksLiteral_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint8_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramLiteral * const all_histograms, uint32_t * const cluster_size, HistogramLiteral * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearLiteral(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddLiteral(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostLiteral(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineLiteral(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksLiteral_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksLiteral_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
size_t BrotliHistogramCombineLiteral(HistogramLiteral *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueLiteral(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineLiteral_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
double BrotliPopulationCostLiteral(const HistogramLiteral *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeLiteral();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostLiteral_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostLiteral_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void helper_helper_ClusterBlocksLiteral_5_2(size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, MemoryManager * const m, uint32_t * const cluster_size, size_t cluster_size_size, size_t num_new_clusters)
{
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  if (cluster_size_capacity < (cluster_size_size + num_new_clusters))
  {
    size_t _new_size = (cluster_size_capacity == 0) ? (cluster_size_size + num_new_clusters) : (cluster_size_capacity);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (cluster_size_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (cluster_size_capacity != 0))
    {
      memcpy(new_array, cluster_size, cluster_size_capacity * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, cluster_size);
      cluster_size_idx = 0;
    }
    ;
    cluster_size_idx = &new_array[new_array_idx];
    cluster_size_capacity = _new_size;
  }
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
}


----------------------------
void helper_helper_ClusterBlocksLiteral_5_1(size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, MemoryManager * const m, HistogramLiteral * const all_histograms, size_t all_histograms_size, size_t num_new_clusters)
{
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  if (all_histograms_capacity < (all_histograms_size + num_new_clusters))
  {
    size_t _new_size = (all_histograms_capacity == 0) ? (all_histograms_size + num_new_clusters) : (all_histograms_capacity);
    HistogramLiteral *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (all_histograms_size + num_new_clusters))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, _new_size * (sizeof(HistogramLiteral)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (all_histograms_capacity != 0))
    {
      memcpy(new_array, all_histograms, all_histograms_capacity * (sizeof(HistogramLiteral)));
    }
    {
      BrotliFree(m, all_histograms);
      all_histograms_idx = 0;
    }
    ;
    all_histograms_idx = &new_array[new_array_idx];
    all_histograms_capacity = _new_size;
  }
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
}


----------------------------
***/


void helper_ClusterBlocksLiteral_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


// hint:  ['histogram_symbols_idx_ref is a mutable refrence to unsigned int', 'pos_ref is a mutable refrence to size_t', 'new_index_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to size_t']
void helper_ClusterBlocksLiteral_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint8_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramLiteral * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramLiteral histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearLiteral(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddLiteral(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceLiteral(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceLiteral(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
double BrotliHistogramBitCostDistanceLiteral(const HistogramLiteral *histogram, const HistogramLiteral *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramLiteral tmp = *histogram;
    HistogramAddHistogramLiteral(&tmp, candidate);
    return BrotliPopulationCostLiteral(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
***/


static void ClusterBlocksLiteral(MemoryManager *m, const uint8_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramLiteral *all_histograms = (all_histograms_capacity > 0) ? ((HistogramLiteral *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramLiteral)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramLiteral *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramLiteral)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksLiteral_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineLiteral(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksLiteral_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksLiteral_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksLiteral_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksLiteral_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
void helper_ClusterBlocksLiteral_3(const size_t * const num_blocks_ref, size_t * const i_ref, BlockSplit * const split, uint32_t * const histogram_symbols, unsigned int histogram_symbols_idx, uint32_t * const block_lengths, unsigned int block_lengths_idx, uint32_t * const new_index, unsigned int new_index_idx)
{
  const size_t num_blocks = *num_blocks_ref;
  size_t i = *i_ref;
  uint32_t cur_length = 0;
  size_t block_idx = 0;
  uint8_t max_type = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    cur_length += block_lengths[i + block_lengths_idx];
    if (((i + 1) == num_blocks) || (histogram_symbols[i + histogram_symbols_idx] != histogram_symbols[(i + 1) + histogram_symbols_idx]))
    {
      const uint8_t id = (uint8_t) new_index[histogram_symbols[i + histogram_symbols_idx] + new_index_idx];
      split->types[block_idx] = id;
      split->lengths[block_idx] = cur_length;
      max_type = brotli_max_uint8_t(max_type, id);
      cur_length = 0;
      block_idx += 1;
    }
  }

  split->num_blocks = block_idx;
  split->num_types = ((size_t) max_type) + 1;
  *num_blocks_ref = num_blocks;
  *i_ref = i;
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
void helper_ClusterBlocksLiteral_2(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->lengths_alloc_size < num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_ClusterBlocksLiteral_5(unsigned int * const histogram_symbols_idx_ref, size_t * const all_histograms_size_ref, size_t * const all_histograms_capacity_ref, unsigned int * const all_histograms_idx_ref, size_t * const cluster_size_size_ref, size_t * const cluster_size_capacity_ref, unsigned int * const cluster_size_idx_ref, size_t * const num_clusters_ref, unsigned int * const histograms_idx_ref, size_t * const pos_ref, size_t * const i_ref, MemoryManager * const m, const uint8_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramLiteral * const all_histograms, uint32_t * const cluster_size, HistogramLiteral * const histograms, size_t max_num_pairs, HistogramPair * const pairs, uint32_t sizes[64], uint32_t new_clusters[64], uint32_t symbols[64], uint32_t remap[64])
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t all_histograms_size = *all_histograms_size_ref;
  size_t all_histograms_capacity = *all_histograms_capacity_ref;
  unsigned int all_histograms_idx = *all_histograms_idx_ref;
  size_t cluster_size_size = *cluster_size_size_ref;
  size_t cluster_size_capacity = *cluster_size_capacity_ref;
  unsigned int cluster_size_idx = *cluster_size_idx_ref;
  size_t num_clusters = *num_clusters_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  size_t pos = *pos_ref;
  size_t i = *i_ref;
  const size_t num_to_combine = brotli_min_size_t(num_blocks - i, 64);
  size_t num_new_clusters;
  size_t j;
  for (j = 0; j < num_to_combine; j += 1)
  {
    size_t k;
    HistogramClearLiteral(&histograms[j + histograms_idx]);
    for (k = 0; k < block_lengths[(i + j) + block_lengths_idx]; k += 1)
    {
      HistogramAddLiteral(&histograms[j + histograms_idx], data[pos]);
      pos += 1;
    }

    histograms[j + histograms_idx].bit_cost_ = BrotliPopulationCostLiteral(&histograms[j + histograms_idx]);
    new_clusters[j] = (uint32_t) j;
    symbols[j] = (uint32_t) j;
    sizes[j] = 1;
  }

  num_new_clusters = BrotliHistogramCombineLiteral(histograms, sizes, symbols, new_clusters, pairs, num_to_combine, num_to_combine, 64, max_num_pairs);
  {
    helper_helper_ClusterBlocksLiteral_5_1(&all_histograms_capacity, &all_histograms_idx, m, all_histograms, all_histograms_size, num_new_clusters);
  }
  ;
  {
    helper_helper_ClusterBlocksLiteral_5_2(&cluster_size_capacity, &cluster_size_idx, m, cluster_size, cluster_size_size, num_new_clusters);
  }
  ;
  if (!(!0))
  {
    return;
  }
  for (j = 0; j < num_new_clusters; j += 1)
  {
    all_histograms[all_histograms_size + all_histograms_idx] = histograms[new_clusters[j] + histograms_idx];
    all_histograms_size += 1;
    cluster_size[cluster_size_size + cluster_size_idx] = sizes[new_clusters[j]];
    cluster_size_size += 1;
    remap[new_clusters[j]] = (uint32_t) j;
  }

  for (j = 0; j < num_to_combine; j += 1)
  {
    histogram_symbols[(i + j) + histogram_symbols_idx] = ((uint32_t) num_clusters) + remap[symbols[j]];
  }

  num_clusters += num_new_clusters;
  ;
  ;
  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *all_histograms_size_ref = all_histograms_size;
  *all_histograms_capacity_ref = all_histograms_capacity;
  *all_histograms_idx_ref = all_histograms_idx;
  *cluster_size_size_ref = cluster_size_size;
  *cluster_size_capacity_ref = cluster_size_capacity;
  *cluster_size_idx_ref = cluster_size_idx;
  *num_clusters_ref = num_clusters;
  *histograms_idx_ref = histograms_idx;
  *pos_ref = pos;
  *i_ref = i;
}


----------------------------
void helper_ClusterBlocksLiteral_1(MemoryManager * const m, const size_t num_blocks, BlockSplit * const split)
{
  if (split->types_alloc_size < num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < num_blocks)
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
size_t BrotliHistogramCombineLiteral(HistogramLiteral *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueLiteral(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineLiteral_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_ClusterBlocksLiteral_4(unsigned int * const histogram_symbols_idx_ref, size_t * const pos_ref, unsigned int * const new_index_idx_ref, size_t * const i_ref, const uint8_t * const data, const size_t num_blocks, uint32_t * const histogram_symbols, uint32_t * const block_lengths, unsigned int block_lengths_idx, HistogramLiteral * const all_histograms, unsigned int all_histograms_idx, uint32_t * const clusters, unsigned int clusters_idx, size_t num_final_clusters, static const uint32_t kInvalidIndex, uint32_t * const new_index)
{
  unsigned int histogram_symbols_idx = *histogram_symbols_idx_ref;
  size_t pos = *pos_ref;
  unsigned int new_index_idx = *new_index_idx_ref;
  size_t i = *i_ref;
  uint32_t next_index = 0;
  for (i = 0; i < num_blocks; i += 1)
  {
    HistogramLiteral histo;
    size_t j;
    uint32_t best_out;
    double best_bits;
    HistogramClearLiteral(&histo);
    for (j = 0; j < block_lengths[i + block_lengths_idx]; j += 1)
    {
      HistogramAddLiteral(&histo, data[pos]);
      pos += 1;
    }

    best_out = (i == 0) ? (histogram_symbols[0 + histogram_symbols_idx]) : (histogram_symbols[(i - 1) + histogram_symbols_idx]);
    best_bits = BrotliHistogramBitCostDistanceLiteral(&histo, &all_histograms[best_out + all_histograms_idx]);
    for (j = 0; j < num_final_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceLiteral(&histo, &all_histograms[clusters[j + clusters_idx] + all_histograms_idx]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j + clusters_idx];
      }
    }

    histogram_symbols[i + histogram_symbols_idx] = best_out;
    if (new_index[best_out + new_index_idx] == kInvalidIndex)
    {
      new_index[best_out + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  *histogram_symbols_idx_ref = histogram_symbols_idx;
  *pos_ref = pos;
  *new_index_idx_ref = new_index_idx;
  *i_ref = i;
}


----------------------------
***/


static size_t FindBlocksLiteral(const uint8_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramLiteral *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeLiteral();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksLiteral_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksLiteral_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


/*** DEPENDENCIES:
void helper_FindBlocksLiteral_2(const uint8_t * const data, const double block_switch_bitcost, const size_t num_histograms, double * const insert_cost, double * const cost, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen, size_t i)
{
  const size_t byte_ix = i;
  size_t ix = byte_ix * bitmaplen;
  size_t insert_cost_ix = data[byte_ix] * num_histograms;
  double min_cost = 1e99;
  double block_switch_cost = block_switch_bitcost;
  size_t k;
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] += insert_cost[insert_cost_ix + k];
    if (cost[k] < min_cost)
    {
      min_cost = cost[k];
      block_id[byte_ix] = (uint8_t) k;
    }
  }

  if (byte_ix < 2000)
  {
    block_switch_cost *= 0.77 + ((0.07 * ((double) byte_ix)) / 2000);
  }
  for (k = 0; k < num_histograms; k += 1)
  {
    cost[k] -= min_cost;
    if (cost[k] >= block_switch_cost)
    {
      const uint8_t mask = (uint8_t) (1u << (k & 7));
      cost[k] = block_switch_cost;
      ;
      switch_signal[ix + (k >> 3)] |= mask;
    }
  }

}


----------------------------
inline static size_t HistogramDataSizeLiteral(void)
{
  return 256;
}


----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static double BitCost(size_t count)
{
  return (count == 0) ? (-2.0) : (FastLog2(count));
}


----------------------------
void helper_FindBlocksLiteral_1(size_t * const num_blocks_ref, const size_t length, uint8_t * const switch_signal, uint8_t * const block_id, const size_t bitmaplen)
{
  size_t num_blocks = *num_blocks_ref;
  size_t byte_ix = length - 1;
  size_t ix = byte_ix * bitmaplen;
  uint8_t cur_id = block_id[byte_ix];
  while (byte_ix > 0)
  {
    const uint8_t mask = (uint8_t) (1u << (cur_id & 7));
    ;
    byte_ix -= 1;
    ix -= bitmaplen;
    if (switch_signal[ix + (cur_id >> 3)] & mask)
    {
      if (cur_id != block_id[byte_ix])
      {
        cur_id = block_id[byte_ix];
        num_blocks += 1;
      }
    }
    block_id[byte_ix] = cur_id;
  }

  *num_blocks_ref = num_blocks;
}


----------------------------
***/


static void BuildBlockHistogramsLiteral(const uint8_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramLiteral *histograms)
{
  size_t i;
  ClearHistogramsLiteral(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddLiteral(&histograms[block_ids[i]], data[i]);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

}


----------------------------
***/


// hint:  ['num_histograms_ref is a mutable refrence to size_t', 'histograms_idx_ref is a mutable refrence to unsigned int']
void helper_SplitByteVectorLiteral_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint8_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramLiteral * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksLiteral(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsLiteral(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsLiteral(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksLiteral(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static void ClusterBlocksLiteral(MemoryManager *m, const uint8_t *data, const size_t length, const size_t num_blocks, uint8_t *block_ids, BlockSplit *split)
{
  uint32_t *histogram_symbols = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int histogram_symbols_idx = 0;
  uint32_t *block_lengths = (num_blocks > 0) ? ((uint32_t *) BrotliAllocate(m, num_blocks * (sizeof(uint32_t)))) : (0);
  unsigned int block_lengths_idx = 0;
  const size_t expected_num_clusters = (16 * ((num_blocks + 64) - 1)) / 64;
  size_t all_histograms_size = 0;
  size_t all_histograms_capacity = expected_num_clusters;
  HistogramLiteral *all_histograms = (all_histograms_capacity > 0) ? ((HistogramLiteral *) BrotliAllocate(m, all_histograms_capacity * (sizeof(HistogramLiteral)))) : (0);
  unsigned int all_histograms_idx = 0;
  size_t cluster_size_size = 0;
  size_t cluster_size_capacity = expected_num_clusters;
  uint32_t *cluster_size = (cluster_size_capacity > 0) ? ((uint32_t *) BrotliAllocate(m, cluster_size_capacity * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  size_t num_clusters = 0;
  HistogramLiteral *histograms = (brotli_min_size_t(num_blocks, 64) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, brotli_min_size_t(num_blocks, 64) * (sizeof(HistogramLiteral)))) : (0);
  unsigned int histograms_idx = 0;
  size_t max_num_pairs = (64 * 64) / 2;
  size_t pairs_capacity = max_num_pairs + 1;
  HistogramPair *pairs = (pairs_capacity > 0) ? ((HistogramPair *) BrotliAllocate(m, pairs_capacity * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t pos = 0;
  uint32_t *clusters;
  unsigned int clusters_idx = 0;
  size_t num_final_clusters;
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index;
  unsigned int new_index_idx = 0;
  size_t i;
  uint32_t sizes[64] = {0};
  uint32_t new_clusters[64] = {0};
  uint32_t symbols[64] = {0};
  uint32_t remap[64] = {0};
  if (((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  memset(block_lengths, 0, num_blocks * (sizeof(uint32_t)));
  {
    size_t block_idx = 0;
    for (i = 0; i < length; i += 1)
    {
      ;
      block_lengths[block_idx + block_lengths_idx] += 1;
      if (((i + 1) == length) || (block_ids[i] != block_ids[i + 1]))
      {
        block_idx += 1;
      }
    }

    ;
  }
  for (i = 0; i < num_blocks; i += 64)
  {
    helper_ClusterBlocksLiteral_5(&histogram_symbols_idx, &all_histograms_size, &all_histograms_capacity, &all_histograms_idx, &cluster_size_size, &cluster_size_capacity, &cluster_size_idx, &num_clusters, &histograms_idx, &pos, &i, m, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, cluster_size, histograms, max_num_pairs, pairs, sizes, new_clusters, symbols, remap);
  }

  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  if (pairs_capacity < (max_num_pairs + 1))
  {
    {
      BrotliFree(m, pairs);
      pairs_idx = 0;
    }
    ;
    pairs_idx = ((max_num_pairs + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (max_num_pairs + 1) * (sizeof(HistogramPair)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
  }
  clusters_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    clusters[i + clusters_idx] = (uint32_t) i;
  }

  num_final_clusters = BrotliHistogramCombineLiteral(all_histograms, cluster_size, histogram_symbols, clusters, pairs, num_clusters, num_blocks, 256, max_num_pairs);
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  new_index_idx = (num_clusters > 0) ? ((uint32_t *) BrotliAllocate(m, num_clusters * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_clusters; i += 1)
    new_index[i + new_index_idx] = kInvalidIndex;

  pos = 0;
  {
    helper_ClusterBlocksLiteral_4(&histogram_symbols_idx, &pos, &new_index_idx, &i, data, num_blocks, histogram_symbols, block_lengths, block_lengths_idx, all_histograms, all_histograms_idx, clusters, clusters_idx, num_final_clusters, kInvalidIndex, new_index);
  }
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  {
    BrotliFree(m, all_histograms);
    all_histograms_idx = 0;
  }
  ;
  {
    helper_ClusterBlocksLiteral_1(m, num_blocks, split);
  }
  ;
  {
    helper_ClusterBlocksLiteral_2(m, num_blocks, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  {
    helper_ClusterBlocksLiteral_3(&num_blocks, &i, split, histogram_symbols, histogram_symbols_idx, block_lengths, block_lengths_idx, new_index, new_index_idx);
  }
  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  {
    BrotliFree(m, block_lengths);
    block_lengths_idx = 0;
  }
  ;
  {
    BrotliFree(m, histogram_symbols);
    histogram_symbols_idx = 0;
  }
  ;
}


----------------------------
static size_t FindBlocksLiteral(const uint8_t *data, const size_t length, const double block_switch_bitcost, const size_t num_histograms, const HistogramLiteral *histograms, double *insert_cost, double *cost, uint8_t *switch_signal, uint8_t *block_id)
{
  const size_t data_size = HistogramDataSizeLiteral();
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  size_t num_blocks = 1;
  size_t i;
  size_t j;
  ;
  if (num_histograms <= 1)
  {
    for (i = 0; i < length; i += 1)
    {
      block_id[i] = 0;
    }

    return 1;
  }
  memset(insert_cost, 0, ((sizeof(insert_cost[0])) * data_size) * num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    insert_cost[i] = FastLog2((uint32_t) histograms[i].total_count_);
  }

  for (i = data_size; i != 0;)
  {
    i -= 1;
    for (j = 0; j < num_histograms; j += 1)
    {
      insert_cost[(i * num_histograms) + j] = insert_cost[j] - BitCost(histograms[j].data_[i]);
    }

  }

  memset(cost, 0, (sizeof(cost[0])) * num_histograms);
  memset(switch_signal, 0, ((sizeof(switch_signal[0])) * length) * bitmaplen);
  for (i = 0; i < length; i += 1)
  {
    helper_FindBlocksLiteral_2(data, block_switch_bitcost, num_histograms, insert_cost, cost, switch_signal, block_id, bitmaplen, i);
  }

  {
    helper_FindBlocksLiteral_1(&num_blocks, length, switch_signal, block_id, bitmaplen);
  }
  return num_blocks;
}


----------------------------
static void BuildBlockHistogramsLiteral(const uint8_t *data, const size_t length, const uint8_t *block_ids, const size_t num_histograms, HistogramLiteral *histograms)
{
  size_t i;
  ClearHistogramsLiteral(histograms, num_histograms);
  for (i = 0; i < length; i += 1)
  {
    HistogramAddLiteral(&histograms[block_ids[i]], data[i]);
  }

}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static size_t RemapBlockIdsLiteral(uint8_t *block_ids, const size_t length, uint16_t *new_id, const size_t num_histograms)
{
  static const uint16_t kInvalidId = 256;
  uint16_t next_id = 0;
  size_t i;
  for (i = 0; i < num_histograms; i += 1)
  {
    new_id[i] = kInvalidId;
  }

  for (i = 0; i < length; i += 1)
  {
    ;
    if (new_id[block_ids[i]] == kInvalidId)
    {
      new_id[block_ids[i]] = next_id;
      next_id += 1;
    }
  }

  for (i = 0; i < length; i += 1)
  {
    block_ids[i] = (uint8_t) new_id[block_ids[i]];
    ;
  }

  ;
  return next_id;
}


----------------------------
None
----------------------------
***/


static void InitialEntropyCodesLiteral(const uint8_t *data, size_t length, size_t stride, size_t num_histograms, HistogramLiteral *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsLiteral(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorLiteral(&histograms[i], data + pos, stride);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddVectorLiteral(HistogramLiteral *self, const uint8_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

}


----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


static void RandomSampleLiteral(uint32_t *seed, const uint8_t *data, size_t length, size_t stride, HistogramLiteral *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorLiteral(sample, data + pos, stride);
}


/*** DEPENDENCIES:
inline static void HistogramAddVectorLiteral(HistogramLiteral *self, const uint8_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


----------------------------
inline static uint32_t MyRand(uint32_t *seed)
{
  *seed *= 16807U;
  return *seed;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


static void RefineEntropyCodesLiteral(const uint8_t *data, size_t length, size_t stride, size_t num_histograms, HistogramLiteral *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramLiteral sample;
    HistogramClearLiteral(&sample);
    RandomSampleLiteral(&seed, data, length, stride, &sample);
    HistogramAddHistogramLiteral(&histograms[iter % num_histograms], &sample);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
static const size_t kIterMulForRefining = 2
----------------------------
static const size_t kMinItersForRefining = 100
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
static void RandomSampleLiteral(uint32_t *seed, const uint8_t *data, size_t length, size_t stride, HistogramLiteral *sample)
{
  size_t pos = 0;
  if (stride >= length)
  {
    stride = length;
  }
  else
  {
    pos = MyRand(seed) % ((length - stride) + 1);
  }
  HistogramAddVectorLiteral(sample, data + pos, stride);
}


----------------------------
***/


void helper_helper_SplitByteVectorLiteral_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_helper_SplitByteVectorLiteral_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_SplitByteVectorLiteral_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorLiteral_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorLiteral_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_helper_SplitByteVectorLiteral_1_2(MemoryManager * const m, BlockSplit * const split)
{
  if (split->lengths_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (split->num_blocks + 1) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint32_t *) BrotliAllocate(m, _new_size * (sizeof(uint32_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->lengths_alloc_size != 0))
    {
      memcpy(new_array, split->lengths, split->lengths_alloc_size * (sizeof(uint32_t)));
    }
    {
      BrotliFree(m, split->lengths);
      split->lengths = 0;
    }
    ;
    split->lengths = &new_array[new_array_idx];
    split->lengths_alloc_size = _new_size;
  }
}


----------------------------
void helper_helper_SplitByteVectorLiteral_1_1(MemoryManager * const m, BlockSplit * const split)
{
  if (split->types_alloc_size < (split->num_blocks + 1))
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (split->num_blocks + 1) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < (split->num_blocks + 1))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((uint8_t *) BrotliAllocate(m, _new_size * (sizeof(uint8_t)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (split->types_alloc_size != 0))
    {
      memcpy(new_array, split->types, split->types_alloc_size * (sizeof(uint8_t)));
    }
    {
      BrotliFree(m, split->types);
      split->types = 0;
    }
    ;
    split->types = &new_array[new_array_idx];
    split->types_alloc_size = _new_size;
  }
}


----------------------------
***/


static void SplitByteVectorLiteral(MemoryManager *m, const uint8_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeLiteral();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramLiteral *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorLiteral_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramLiteral *) BrotliAllocate(m, num_histograms * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesLiteral(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesLiteral(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorLiteral_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


/*** DEPENDENCIES:
static const size_t kMinLengthForBlockSplitting = 128
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void helper_SplitByteVectorLiteral_2(size_t * const num_histograms_ref, unsigned int * const histograms_idx_ref, MemoryManager * const m, const uint8_t * const data, const size_t length, const double block_switch_cost, const BrotliEncoderParams * const params, BlockSplit * const split, const size_t data_size, HistogramLiteral * const histograms)
{
  size_t num_histograms = *num_histograms_ref;
  unsigned int histograms_idx = *histograms_idx_ref;
  uint8_t *block_ids = (length > 0) ? ((uint8_t *) BrotliAllocate(m, length * (sizeof(uint8_t)))) : (0);
  unsigned int block_ids_idx = 0;
  size_t num_blocks = 0;
  const size_t bitmaplen = (num_histograms + 7) >> 3;
  double *insert_cost = ((data_size * num_histograms) > 0) ? ((double *) BrotliAllocate(m, (data_size * num_histograms) * (sizeof(double)))) : (0);
  unsigned int insert_cost_idx = 0;
  double *cost = (num_histograms > 0) ? ((double *) BrotliAllocate(m, num_histograms * (sizeof(double)))) : (0);
  unsigned int cost_idx = 0;
  uint8_t *switch_signal = ((length * bitmaplen) > 0) ? ((uint8_t *) BrotliAllocate(m, (length * bitmaplen) * (sizeof(uint8_t)))) : (0);
  unsigned int switch_signal_idx = 0;
  uint16_t *new_id = (num_histograms > 0) ? ((uint16_t *) BrotliAllocate(m, num_histograms * (sizeof(uint16_t)))) : (0);
  unsigned int new_id_idx = 0;
  const size_t iters = (params->quality < 11) ? (3) : (10);
  size_t i;
  if ((((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < iters; i += 1)
  {
    num_blocks = FindBlocksLiteral(data, length, block_switch_cost, num_histograms, histograms, insert_cost, cost, switch_signal, block_ids);
    num_histograms = RemapBlockIdsLiteral(block_ids, length, new_id, num_histograms);
    BuildBlockHistogramsLiteral(data, length, block_ids, num_histograms, histograms);
  }

  {
    BrotliFree(m, insert_cost);
    insert_cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, cost);
    cost_idx = 0;
  }
  ;
  {
    BrotliFree(m, switch_signal);
    switch_signal_idx = 0;
  }
  ;
  {
    BrotliFree(m, new_id);
    new_id_idx = 0;
  }
  ;
  {
    BrotliFree(m, histograms);
    histograms_idx = 0;
  }
  ;
  ClusterBlocksLiteral(m, data, length, num_blocks, block_ids, split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, block_ids);
    block_ids_idx = 0;
  }
  ;
  *num_histograms_ref = num_histograms;
  *histograms_idx_ref = histograms_idx;
}


----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static size_t HistogramDataSizeLiteral(void)
{
  return 256;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
static void InitialEntropyCodesLiteral(const uint8_t *data, size_t length, size_t stride, size_t num_histograms, HistogramLiteral *histograms)
{
  uint32_t seed = 7;
  size_t block_length = length / num_histograms;
  size_t i;
  ClearHistogramsLiteral(histograms, num_histograms);
  for (i = 0; i < num_histograms; i += 1)
  {
    size_t pos = (length * i) / num_histograms;
    if (i != 0)
    {
      pos += MyRand(&seed) % block_length;
    }
    if ((pos + stride) >= length)
    {
      pos = (length - stride) - 1;
    }
    HistogramAddVectorLiteral(&histograms[i], data + pos, stride);
  }

}


----------------------------
static void RefineEntropyCodesLiteral(const uint8_t *data, size_t length, size_t stride, size_t num_histograms, HistogramLiteral *histograms)
{
  size_t iters = ((kIterMulForRefining * length) / stride) + kMinItersForRefining;
  uint32_t seed = 7;
  size_t iter;
  iters = (((iters + num_histograms) - 1) / num_histograms) * num_histograms;
  for (iter = 0; iter < iters; iter += 1)
  {
    HistogramLiteral sample;
    HistogramClearLiteral(&sample);
    RandomSampleLiteral(&seed, data, length, stride, &sample);
    HistogramAddHistogramLiteral(&histograms[iter % num_histograms], &sample);
  }

}


----------------------------
void helper_SplitByteVectorLiteral_1(MemoryManager * const m, const size_t length, BlockSplit * const split)
{
  {
    helper_helper_SplitByteVectorLiteral_1_1(m, split);
  }
  ;
  {
    helper_helper_SplitByteVectorLiteral_1_2(m, split);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_types = 1;
  split->types[split->num_blocks] = 0;
  split->lengths[split->num_blocks] = (uint32_t) length;
  split->num_blocks += 1;
  return;
}


----------------------------
None
----------------------------
***/


void helper_BrotliSplitBlock_1(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const uint8_t * const data, const size_t pos, const size_t mask, const BrotliEncoderParams * const params, BlockSplit * const literal_split)
{
  size_t literals_count = CountLiterals(cmds, num_commands);
  uint8_t *literals = (literals_count > 0) ? ((uint8_t *) BrotliAllocate(m, literals_count * (sizeof(uint8_t)))) : (0);
  unsigned int literals_idx = 0;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  CopyLiteralsToByteArray(cmds, num_commands, data, pos, mask, literals);
  SplitByteVectorLiteral(m, literals, literals_count, kSymbolsPerLiteralHistogram, kMaxLiteralHistograms, kLiteralStrideLength, kLiteralBlockSwitchCost, params, literal_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, literals);
    literals_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
static size_t CountLiterals(const Command *cmds, const size_t num_commands)
{
  size_t total_length = 0;
  size_t i;
  for (i = 0; i < num_commands; i += 1)
  {
    total_length += cmds[i].insert_len_;
  }

  return total_length;
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
static const size_t kSymbolsPerLiteralHistogram = 544
----------------------------
static void SplitByteVectorLiteral(MemoryManager *m, const uint8_t *data, const size_t length, const size_t literals_per_histogram, const size_t max_histograms, const size_t sampling_stride_length, const double block_switch_cost, const BrotliEncoderParams *params, BlockSplit *split)
{
  const size_t data_size = HistogramDataSizeLiteral();
  size_t num_histograms = (length / literals_per_histogram) + 1;
  HistogramLiteral *histograms;
  unsigned int histograms_idx = 0;
  if (num_histograms > max_histograms)
  {
    num_histograms = max_histograms;
  }
  if (length == 0)
  {
    split->num_types = 1;
    return;
  }
  else
    if (length < kMinLengthForBlockSplitting)
  {
    helper_SplitByteVectorLiteral_1(m, length, split);
  }
  histograms_idx = (num_histograms > 0) ? ((HistogramLiteral *) BrotliAllocate(m, num_histograms * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitialEntropyCodesLiteral(data, length, sampling_stride_length, num_histograms, histograms);
  RefineEntropyCodesLiteral(data, length, sampling_stride_length, num_histograms, histograms);
  {
    helper_SplitByteVectorLiteral_2(&num_histograms, &histograms_idx, m, data, length, block_switch_cost, params, split, data_size, histograms);
  }
}


----------------------------
static void CopyLiteralsToByteArray(const Command *cmds, const size_t num_commands, const uint8_t *data, const size_t offset, const size_t mask, uint8_t *literals)
{
  size_t pos = 0;
  size_t from_pos = offset & mask;
  size_t i;
  for (i = 0; i < num_commands; i += 1)
  {
    size_t insert_len = cmds[i].insert_len_;
    if ((from_pos + insert_len) > mask)
    {
      size_t head_size = (mask + 1) - from_pos;
      memcpy(literals + pos, data + from_pos, head_size);
      from_pos = 0;
      pos += head_size;
      insert_len -= head_size;
    }
    if (insert_len > 0)
    {
      memcpy(literals + pos, data + from_pos, insert_len);
      pos += insert_len;
    }
    from_pos = ((from_pos + insert_len) + CommandCopyLen(&cmds[i])) & mask;
  }

}


----------------------------
static const size_t kLiteralStrideLength = 70
----------------------------
static const double kLiteralBlockSwitchCost = 28.1
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static const size_t kMaxLiteralHistograms = 100
----------------------------
None
----------------------------
***/


void BrotliSplitBlock(MemoryManager *m, const Command *cmds, const size_t num_commands, const uint8_t *data, const size_t pos, const size_t mask, const BrotliEncoderParams *params, BlockSplit *literal_split, BlockSplit *insert_and_copy_split, BlockSplit *dist_split)
{
  {
    helper_BrotliSplitBlock_1(m, cmds, num_commands, data, pos, mask, params, literal_split);
  }
  {
    helper_BrotliSplitBlock_2(m, cmds, num_commands, params, insert_and_copy_split);
  }
  {
    helper_BrotliSplitBlock_3(m, cmds, num_commands, params, dist_split);
  }
}


/*** DEPENDENCIES:
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
void helper_BrotliSplitBlock_3(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const BrotliEncoderParams * const params, BlockSplit * const dist_split)
{
  uint16_t *distance_prefixes = (num_commands > 0) ? ((uint16_t *) BrotliAllocate(m, num_commands * (sizeof(uint16_t)))) : (0);
  unsigned int distance_prefixes_idx = 0;
  size_t j = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      distance_prefixes[j + distance_prefixes_idx] = cmd->dist_prefix_ & 0x3FF;
      j += 1;
    }
  }

  SplitByteVectorDistance(m, distance_prefixes, j, kSymbolsPerDistanceHistogram, kMaxCommandHistograms, kCommandStrideLength, kDistanceBlockSwitchCost, params, dist_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, distance_prefixes);
    distance_prefixes_idx = 0;
  }
  ;
}


----------------------------
void helper_BrotliSplitBlock_2(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const BrotliEncoderParams * const params, BlockSplit * const insert_and_copy_split)
{
  uint16_t *insert_and_copy_codes = (num_commands > 0) ? ((uint16_t *) BrotliAllocate(m, num_commands * (sizeof(uint16_t)))) : (0);
  unsigned int insert_and_copy_codes_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    insert_and_copy_codes[i + insert_and_copy_codes_idx] = cmds[i].cmd_prefix_;
  }

  SplitByteVectorCommand(m, insert_and_copy_codes, num_commands, kSymbolsPerCommandHistogram, kMaxCommandHistograms, kCommandStrideLength, kCommandBlockSwitchCost, params, insert_and_copy_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, insert_and_copy_codes);
    insert_and_copy_codes_idx = 0;
  }
  ;
}


----------------------------
void helper_BrotliSplitBlock_1(MemoryManager * const m, const Command * const cmds, const size_t num_commands, const uint8_t * const data, const size_t pos, const size_t mask, const BrotliEncoderParams * const params, BlockSplit * const literal_split)
{
  size_t literals_count = CountLiterals(cmds, num_commands);
  uint8_t *literals = (literals_count > 0) ? ((uint8_t *) BrotliAllocate(m, literals_count * (sizeof(uint8_t)))) : (0);
  unsigned int literals_idx = 0;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  CopyLiteralsToByteArray(cmds, num_commands, data, pos, mask, literals);
  SplitByteVectorLiteral(m, literals, literals_count, kSymbolsPerLiteralHistogram, kMaxLiteralHistograms, kLiteralStrideLength, kLiteralBlockSwitchCost, params, literal_split);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, literals);
    literals_idx = 0;
  }
  ;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


