void BrotliInitDistanceParams(BrotliEncoderParams *params, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceParams *dist_params = &params->dist;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  uint32_t max_distance;
  dist_params->distance_postfix_bits = npostfix;
  dist_params->num_direct_distance_codes = ndirect;
  alphabet_size_max = (16 + ndirect) + (24U << (npostfix + 1));
  alphabet_size_limit = alphabet_size_max;
  max_distance = (ndirect + (1U << ((24U + npostfix) + 2))) - (1U << (npostfix + 2));
  if (params->large_window)
  {
    BrotliDistanceCodeLimit limit = BrotliCalculateDistanceCodeLimit(0x7FFFFFFC, npostfix, ndirect);
    alphabet_size_max = (16 + ndirect) + (62U << (npostfix + 1));
    alphabet_size_limit = limit.max_alphabet_size;
    max_distance = limit.max_distance;
  }
  dist_params->alphabet_size_max = alphabet_size_max;
  dist_params->alphabet_size_limit = alphabet_size_limit;
  dist_params->max_distance = max_distance;
}


/*** DEPENDENCIES:
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    helper_BrotliCalculateDistanceCodeLimit_1(&max_distance, &result, npostfix, ndirect);
  }
}


----------------------------
typedef struct BrotliDistanceParams
{
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  size_t max_distance;
} BrotliDistanceParams
----------------------------
typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit
----------------------------
None
----------------------------
***/


void helper_helper_BlockSplitterFinishBlockDistance_1_1(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


void helper_helper_BlockSplitterFinishBlockDistance_1_2(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms, HistogramDistance combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


void helper_BlockSplitterFinishBlockDistance_1(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramDistance combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramDistance(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockDistance_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockDistance_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
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
void helper_helper_BlockSplitterFinishBlockDistance_1_1(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
void helper_helper_BlockSplitterFinishBlockDistance_1_2(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms, HistogramDistance combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
}


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
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
***/


static void BlockSplitterFinishBlockDistance(BlockSplitterDistance *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramDistance *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockDistance_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
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
void helper_BlockSplitterFinishBlockDistance_1(BlockSplitterDistance * const self, BlockSplit * const split, double * const last_entropy, HistogramDistance * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramDistance combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramDistance(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockDistance_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockDistance_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
***/


void helper_InitContextBlockSplitter_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


void helper_InitContextBlockSplitter_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


static void InitContextBlockSplitter(MemoryManager *m, ContextBlockSplitter *self, size_t alphabet_size, size_t num_contexts, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramLiteral **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types;
  ;
  self->alphabet_size_ = alphabet_size;
  self->num_contexts_ = num_contexts;
  self->max_block_types_ = 256 / num_contexts;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  max_num_types = brotli_min_size_t(max_num_blocks, self->max_block_types_ + 1);
  {
    helper_InitContextBlockSplitter_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitContextBlockSplitter_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_blocks = max_num_blocks;
  if (!(!0))
  {
    return;
  }
  ;
  *histograms_size = max_num_types * num_contexts;
  *histograms = ((*histograms_size) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramLiteral)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsLiteral(&self->histograms_[0], num_contexts);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


/*** DEPENDENCIES:
void helper_InitContextBlockSplitter_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

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
void helper_InitContextBlockSplitter_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void helper_InitBlockSplitterLiteral_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


void helper_InitBlockSplitterLiteral_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


static void InitBlockSplitterLiteral(MemoryManager *m, BlockSplitterLiteral *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramLiteral **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterLiteral_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterLiteral_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramLiteral)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearLiteral(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
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
void helper_InitBlockSplitterLiteral_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void helper_InitBlockSplitterLiteral_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static void MapStaticContexts(MemoryManager *m, size_t num_contexts, const uint32_t *static_context_map, MetaBlockSplit *mb)
{
  size_t i;
  ;
  mb->literal_context_map_size = mb->literal_split.num_types << 6;
  mb->literal_context_map = (mb->literal_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->literal_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < mb->literal_split.num_types; i += 1)
  {
    uint32_t offset = (uint32_t) (i * num_contexts);
    size_t j;
    for (j = 0; j < (1u << 6); j += 1)
    {
      mb->literal_context_map[(i << 6) + j] = offset + static_context_map[j];
    }

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
typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
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
***/


void helper_helper_BlockSplitterFinishBlockLiteral_1_2(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, HistogramLiteral combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
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
***/


void helper_helper_BlockSplitterFinishBlockLiteral_1_1(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
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
***/


void helper_BlockSplitterFinishBlockLiteral_1(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramLiteral combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramLiteral(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockLiteral_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockLiteral_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
}


/*** DEPENDENCIES:
void helper_helper_BlockSplitterFinishBlockLiteral_1_2(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, HistogramLiteral combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
}


----------------------------
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
void helper_helper_BlockSplitterFinishBlockLiteral_1_1(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
***/


static void BlockSplitterFinishBlockLiteral(BlockSplitterLiteral *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockLiteral_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
  }
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void helper_BlockSplitterFinishBlockLiteral_1(BlockSplitterLiteral * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramLiteral combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramLiteral(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockLiteral_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockLiteral_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
}


----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
***/


void helper_helper_BlockSplitterFinishBlockCommand_1_1(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
***/


void helper_helper_BlockSplitterFinishBlockCommand_1_2(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms, HistogramCommand combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
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
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
***/


void helper_BlockSplitterFinishBlockCommand_1(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramCommand combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramCommand(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockCommand_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockCommand_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
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
void helper_helper_BlockSplitterFinishBlockCommand_1_1(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms, double entropy)
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = (uint8_t) split->num_types;
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = entropy;
  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += 1;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
}


----------------------------
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
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
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
void helper_helper_BlockSplitterFinishBlockCommand_1_2(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms, HistogramCommand combined_histo[2], double combined_entropy[2])
{
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  histograms[self->last_histogram_ix_[0]] = combined_histo[1];
  last_entropy[1] = last_entropy[0];
  last_entropy[0] = combined_entropy[1];
  self->num_blocks_ += 1;
  self->block_size_ = 0;
  HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
}


----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
***/


static void BlockSplitterFinishBlockCommand(BlockSplitterCommand *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramCommand *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockCommand_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
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
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
void helper_BlockSplitterFinishBlockCommand_1(BlockSplitterCommand * const self, BlockSplit * const split, double * const last_entropy, HistogramCommand * const histograms)
{
  double entropy = BitsEntropy(histograms[self->curr_histogram_ix_].data_, self->alphabet_size_);
  HistogramCommand combined_histo[2];
  double combined_entropy[2];
  double diff[2];
  size_t j;
  for (j = 0; j < 2; j += 1)
  {
    size_t last_histogram_ix = self->last_histogram_ix_[j];
    combined_histo[j] = histograms[self->curr_histogram_ix_];
    HistogramAddHistogramCommand(&combined_histo[j], &histograms[last_histogram_ix]);
    combined_entropy[j] = BitsEntropy(&combined_histo[j].data_[0], self->alphabet_size_);
    diff[j] = (combined_entropy[j] - entropy) - last_entropy[j];
  }

  if (((split->num_types < 256) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_BlockSplitterFinishBlockCommand_1_1(self, split, last_entropy, histograms, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_BlockSplitterFinishBlockCommand_1_2(self, split, last_entropy, histograms, combined_histo, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    histograms[self->last_histogram_ix_[0]] = combined_histo[0];
    last_entropy[0] = combined_entropy[0];
    if (split->num_types == 1)
    {
      last_entropy[1] = last_entropy[0];
    }
    self->block_size_ = 0;
    HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
}


----------------------------
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
***/


// hint:  ['num_contexts_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_ContextBlockSplitterFinishBlock_2_1(const size_t * const num_contexts_ref, size_t * const i_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, double entropy[13])
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i = *i_ref;
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = split->num_types * num_contexts;
  for (i = 0; i < num_contexts; i += 1)
  {
    last_entropy[num_contexts + i] = last_entropy[i];
    last_entropy[i] = entropy[i];
  }

  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += num_contexts;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    ClearHistogramsLiteral(&self->histograms_[self->curr_histogram_ix_], self->num_contexts_);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
  *num_contexts_ref = num_contexts;
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

}


----------------------------
***/


// hint:  ['num_contexts_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_ContextBlockSplitterFinishBlock_2_2(const size_t * const num_contexts_ref, size_t * const i_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, HistogramLiteral * const combined_histo, unsigned int combined_histo_idx, double combined_entropy[2 * 13])
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i = *i_ref;
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  for (i = 0; i < num_contexts; i += 1)
  {
    histograms[self->last_histogram_ix_[0] + i] = combined_histo[(num_contexts + i) + combined_histo_idx];
    last_entropy[num_contexts + i] = last_entropy[i];
    last_entropy[i] = combined_entropy[num_contexts + i];
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_ + i]);
  }

  self->num_blocks_ += 1;
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
  *num_contexts_ref = num_contexts;
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


// hint:  ['num_contexts_ref is a mutable refrence to size_t']
void helper_ContextBlockSplitterFinishBlock_2(const size_t * const num_contexts_ref, ContextBlockSplitter * const self, MemoryManager * const m, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  const size_t num_contexts = *num_contexts_ref;
  double entropy[13];
  HistogramLiteral *combined_histo = ((2 * num_contexts) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (2 * num_contexts) * (sizeof(HistogramLiteral)))) : (0);
  unsigned int combined_histo_idx = 0;
  double combined_entropy[2 * 13];
  double diff[2] = {0.0};
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_contexts; i += 1)
  {
    size_t curr_histo_ix = self->curr_histogram_ix_ + i;
    size_t j;
    entropy[i] = BitsEntropy(histograms[curr_histo_ix].data_, self->alphabet_size_);
    for (j = 0; j < 2; j += 1)
    {
      size_t jx = (j * num_contexts) + i;
      size_t last_histogram_ix = self->last_histogram_ix_[j] + i;
      combined_histo[jx + combined_histo_idx] = histograms[curr_histo_ix];
      HistogramAddHistogramLiteral(&combined_histo[jx + combined_histo_idx], &histograms[last_histogram_ix]);
      combined_entropy[jx] = BitsEntropy(&combined_histo[jx + combined_histo_idx].data_[0], self->alphabet_size_);
      diff[j] += (combined_entropy[jx] - entropy[i]) - last_entropy[jx];
    }

  }

  if (((split->num_types < self->max_block_types_) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_ContextBlockSplitterFinishBlock_2_1(&num_contexts, &i, self, split, last_entropy, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_ContextBlockSplitterFinishBlock_2_2(&num_contexts, &i, self, split, last_entropy, histograms, combined_histo, combined_histo_idx, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    for (i = 0; i < num_contexts; i += 1)
    {
      histograms[self->last_histogram_ix_[0] + i] = combined_histo[i + combined_histo_idx];
      last_entropy[i] = combined_entropy[i];
      if (split->num_types == 1)
      {
        last_entropy[num_contexts + i] = last_entropy[i];
      }
      HistogramClearLiteral(&histograms[self->curr_histogram_ix_ + i]);
    }

    self->block_size_ = 0;
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
  {
    BrotliFree(m, combined_histo);
    combined_histo_idx = 0;
  }
  ;
  *num_contexts_ref = num_contexts;
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
void helper_helper_ContextBlockSplitterFinishBlock_2_1(const size_t * const num_contexts_ref, size_t * const i_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, double entropy[13])
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i = *i_ref;
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = (uint8_t) split->num_types;
  self->last_histogram_ix_[1] = self->last_histogram_ix_[0];
  self->last_histogram_ix_[0] = split->num_types * num_contexts;
  for (i = 0; i < num_contexts; i += 1)
  {
    last_entropy[num_contexts + i] = last_entropy[i];
    last_entropy[i] = entropy[i];
  }

  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += num_contexts;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    ClearHistogramsLiteral(&self->histograms_[self->curr_histogram_ix_], self->num_contexts_);
  }
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
  *num_contexts_ref = num_contexts;
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
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
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
void helper_helper_ContextBlockSplitterFinishBlock_2_2(const size_t * const num_contexts_ref, size_t * const i_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms, HistogramLiteral * const combined_histo, unsigned int combined_histo_idx, double combined_entropy[2 * 13])
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i = *i_ref;
  split->lengths[self->num_blocks_] = (uint32_t) self->block_size_;
  split->types[self->num_blocks_] = split->types[self->num_blocks_ - 2];
  {
    size_t __brotli_swap_tmp = self->last_histogram_ix_[0];
    self->last_histogram_ix_[0] = self->last_histogram_ix_[1];
    self->last_histogram_ix_[1] = __brotli_swap_tmp;
  }
  ;
  for (i = 0; i < num_contexts; i += 1)
  {
    histograms[self->last_histogram_ix_[0] + i] = combined_histo[(num_contexts + i) + combined_histo_idx];
    last_entropy[num_contexts + i] = last_entropy[i];
    last_entropy[i] = combined_entropy[num_contexts + i];
    HistogramClearLiteral(&histograms[self->curr_histogram_ix_ + i]);
  }

  self->num_blocks_ += 1;
  self->block_size_ = 0;
  self->merge_last_count_ = 0;
  self->target_block_size_ = self->min_block_size_;
  *num_contexts_ref = num_contexts;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['num_contexts_ref is a mutable refrence to size_t']
void helper_ContextBlockSplitterFinishBlock_1(const size_t * const num_contexts_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i;
  split->lengths[0] = (uint32_t) self->block_size_;
  split->types[0] = 0;
  for (i = 0; i < num_contexts; i += 1)
  {
    last_entropy[i] = BitsEntropy(histograms[i].data_, self->alphabet_size_);
    last_entropy[num_contexts + i] = last_entropy[i];
  }

  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += num_contexts;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    ClearHistogramsLiteral(&self->histograms_[self->curr_histogram_ix_], self->num_contexts_);
  }
  self->block_size_ = 0;
  *num_contexts_ref = num_contexts;
}


/*** DEPENDENCIES:
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
***/


static void ContextBlockSplitterFinishBlock(ContextBlockSplitter *self, MemoryManager *m, int is_final)
{
  BlockSplit *split = self->split_;
  const size_t num_contexts = self->num_contexts_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  if (self->block_size_ < self->min_block_size_)
  {
    self->block_size_ = self->min_block_size_;
  }
  if (self->num_blocks_ == 0)
  {
    helper_ContextBlockSplitterFinishBlock_1(&num_contexts, self, split, last_entropy, histograms);
  }
  else
    if (self->block_size_ > 0)
  {
    helper_ContextBlockSplitterFinishBlock_2(&num_contexts, self, m, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types * num_contexts;
    split->num_blocks = self->num_blocks_;
  }
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_ContextBlockSplitterFinishBlock_2(const size_t * const num_contexts_ref, ContextBlockSplitter * const self, MemoryManager * const m, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  const size_t num_contexts = *num_contexts_ref;
  double entropy[13];
  HistogramLiteral *combined_histo = ((2 * num_contexts) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (2 * num_contexts) * (sizeof(HistogramLiteral)))) : (0);
  unsigned int combined_histo_idx = 0;
  double combined_entropy[2 * 13];
  double diff[2] = {0.0};
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < num_contexts; i += 1)
  {
    size_t curr_histo_ix = self->curr_histogram_ix_ + i;
    size_t j;
    entropy[i] = BitsEntropy(histograms[curr_histo_ix].data_, self->alphabet_size_);
    for (j = 0; j < 2; j += 1)
    {
      size_t jx = (j * num_contexts) + i;
      size_t last_histogram_ix = self->last_histogram_ix_[j] + i;
      combined_histo[jx + combined_histo_idx] = histograms[curr_histo_ix];
      HistogramAddHistogramLiteral(&combined_histo[jx + combined_histo_idx], &histograms[last_histogram_ix]);
      combined_entropy[jx] = BitsEntropy(&combined_histo[jx + combined_histo_idx].data_[0], self->alphabet_size_);
      diff[j] += (combined_entropy[jx] - entropy[i]) - last_entropy[jx];
    }

  }

  if (((split->num_types < self->max_block_types_) && (diff[0] > self->split_threshold_)) && (diff[1] > self->split_threshold_))
  {
    helper_helper_ContextBlockSplitterFinishBlock_2_1(&num_contexts, &i, self, split, last_entropy, entropy);
  }
  else
    if (diff[1] < (diff[0] - 20.0))
  {
    helper_helper_ContextBlockSplitterFinishBlock_2_2(&num_contexts, &i, self, split, last_entropy, histograms, combined_histo, combined_histo_idx, combined_entropy);
  }
  else
  {
    split->lengths[self->num_blocks_ - 1] += (uint32_t) self->block_size_;
    for (i = 0; i < num_contexts; i += 1)
    {
      histograms[self->last_histogram_ix_[0] + i] = combined_histo[i + combined_histo_idx];
      last_entropy[i] = combined_entropy[i];
      if (split->num_types == 1)
      {
        last_entropy[num_contexts + i] = last_entropy[i];
      }
      HistogramClearLiteral(&histograms[self->curr_histogram_ix_ + i]);
    }

    self->block_size_ = 0;
    if ((++self->merge_last_count_) > 1)
    {
      self->target_block_size_ += self->min_block_size_;
    }
  }
  {
    BrotliFree(m, combined_histo);
    combined_histo_idx = 0;
  }
  ;
  *num_contexts_ref = num_contexts;
}


----------------------------
void helper_ContextBlockSplitterFinishBlock_1(const size_t * const num_contexts_ref, ContextBlockSplitter * const self, BlockSplit * const split, double * const last_entropy, HistogramLiteral * const histograms)
{
  const size_t num_contexts = *num_contexts_ref;
  size_t i;
  split->lengths[0] = (uint32_t) self->block_size_;
  split->types[0] = 0;
  for (i = 0; i < num_contexts; i += 1)
  {
    last_entropy[i] = BitsEntropy(histograms[i].data_, self->alphabet_size_);
    last_entropy[num_contexts + i] = last_entropy[i];
  }

  self->num_blocks_ += 1;
  split->num_types += 1;
  self->curr_histogram_ix_ += num_contexts;
  if (self->curr_histogram_ix_ < (*self->histograms_size_))
  {
    ClearHistogramsLiteral(&self->histograms_[self->curr_histogram_ix_], self->num_contexts_);
  }
  self->block_size_ = 0;
  *num_contexts_ref = num_contexts;
}


----------------------------
***/


void helper_InitBlockSplitterDistance_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


void helper_InitBlockSplitterDistance_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


static void InitBlockSplitterDistance(MemoryManager *m, BlockSplitterDistance *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramDistance **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterDistance_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterDistance_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramDistance *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramDistance)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearDistance(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


/*** DEPENDENCIES:
void helper_InitBlockSplitterDistance_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
void helper_InitBlockSplitterDistance_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
***/


void helper_InitBlockSplitterCommand_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


void helper_InitBlockSplitterCommand_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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


static void InitBlockSplitterCommand(MemoryManager *m, BlockSplitterCommand *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramCommand **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterCommand_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterCommand_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramCommand *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramCommand)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearCommand(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
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
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
void helper_InitBlockSplitterCommand_2(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->lengths_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->lengths_alloc_size == 0) ? (max_num_blocks) : (split->lengths_alloc_size);
    uint32_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
void helper_InitBlockSplitterCommand_1(MemoryManager * const m, BlockSplit * const split, size_t max_num_blocks)
{
  if (split->types_alloc_size < max_num_blocks)
  {
    size_t _new_size = (split->types_alloc_size == 0) ? (max_num_blocks) : (split->types_alloc_size);
    uint8_t *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < max_num_blocks)
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
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static void BlockSplitterAddSymbolCommand(BlockSplitterCommand *self, size_t symbol)
{
  HistogramAddCommand(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockCommand(self, 0);
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
static void BlockSplitterFinishBlockCommand(BlockSplitterCommand *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramCommand *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockCommand_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
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
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


static void BlockSplitterAddSymbolLiteral(BlockSplitterLiteral *self, size_t symbol)
{
  HistogramAddLiteral(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockLiteral(self, 0);
  }
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
static void BlockSplitterFinishBlockLiteral(BlockSplitterLiteral *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockLiteral_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
  }
}


----------------------------
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


static void ContextBlockSplitterAddSymbol(ContextBlockSplitter *self, MemoryManager *m, size_t symbol, size_t context)
{
  HistogramAddLiteral(&self->histograms_[self->curr_histogram_ix_ + context], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    ContextBlockSplitterFinishBlock(self, m, 0);
    if (!(!0))
    {
      return;
    }
  }
}


/*** DEPENDENCIES:
static void ContextBlockSplitterFinishBlock(ContextBlockSplitter *self, MemoryManager *m, int is_final)
{
  BlockSplit *split = self->split_;
  const size_t num_contexts = self->num_contexts_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  if (self->block_size_ < self->min_block_size_)
  {
    self->block_size_ = self->min_block_size_;
  }
  if (self->num_blocks_ == 0)
  {
    helper_ContextBlockSplitterFinishBlock_1(&num_contexts, self, split, last_entropy, histograms);
  }
  else
    if (self->block_size_ > 0)
  {
    helper_ContextBlockSplitterFinishBlock_2(&num_contexts, self, m, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types * num_contexts;
    split->num_blocks = self->num_blocks_;
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static void BlockSplitterAddSymbolDistance(BlockSplitterDistance *self, size_t symbol)
{
  HistogramAddDistance(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockDistance(self, 0);
  }
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
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
static void BlockSplitterFinishBlockDistance(BlockSplitterDistance *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramDistance *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockDistance_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
  }
}


----------------------------
***/


// hint:  ['pos_ref is a mutable refrence to size_t', 'prev_byte_ref is a mutable refrence to uint8_t', 'prev_byte2_ref is a mutable refrence to uint8_t']
void helper_BrotliBuildMetaBlockGreedyInternal_1(size_t * const pos_ref, uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, MemoryManager * const m, const uint8_t * const ringbuffer, size_t mask, ContextLut literal_context_lut, const size_t num_contexts, const uint32_t * const static_context_map, const Command * const commands, union 
{
  BlockSplitterLiteral plain;
  ContextBlockSplitter ctx;
} lit_blocks, BlockSplitterCommand cmd_blocks, BlockSplitterDistance dist_blocks, size_t i)
{
  size_t pos = *pos_ref;
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  const Command cmd = commands[i];
  size_t j;
  BlockSplitterAddSymbolCommand(&cmd_blocks, cmd.cmd_prefix_);
  for (j = cmd.insert_len_; j != 0; j -= 1)
  {
    uint8_t literal = ringbuffer[pos & mask];
    if (num_contexts == 1)
    {
      BlockSplitterAddSymbolLiteral(&lit_blocks.plain, literal);
    }
    else
    {
      size_t context = literal_context_lut[prev_byte] | (literal_context_lut + 256)[prev_byte2];
      ContextBlockSplitterAddSymbol(&lit_blocks.ctx, m, literal, static_context_map[context]);
      if (!(!0))
      {
        return;
      }
    }
    prev_byte2 = prev_byte;
    prev_byte = literal;
    pos += 1;
  }

  pos += CommandCopyLen(&cmd);
  if (CommandCopyLen(&cmd))
  {
    prev_byte2 = ringbuffer[(pos - 2) & mask];
    prev_byte = ringbuffer[(pos - 1) & mask];
    if (cmd.cmd_prefix_ >= 128)
    {
      BlockSplitterAddSymbolDistance(&dist_blocks, cmd.dist_prefix_ & 0x3FF);
    }
  }
  *pos_ref = pos;
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


/*** DEPENDENCIES:
static void BlockSplitterAddSymbolCommand(BlockSplitterCommand *self, size_t symbol)
{
  HistogramAddCommand(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockCommand(self, 0);
  }
}


----------------------------
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
static void BlockSplitterAddSymbolLiteral(BlockSplitterLiteral *self, size_t symbol)
{
  HistogramAddLiteral(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockLiteral(self, 0);
  }
}


----------------------------
static void ContextBlockSplitterAddSymbol(ContextBlockSplitter *self, MemoryManager *m, size_t symbol, size_t context)
{
  HistogramAddLiteral(&self->histograms_[self->curr_histogram_ix_ + context], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    ContextBlockSplitterFinishBlock(self, m, 0);
    if (!(!0))
    {
      return;
    }
  }
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void BlockSplitterAddSymbolDistance(BlockSplitterDistance *self, size_t symbol)
{
  HistogramAddDistance(&self->histograms_[self->curr_histogram_ix_], symbol);
  self->block_size_ += 1;
  if (self->block_size_ == self->target_block_size_)
  {
    BlockSplitterFinishBlockDistance(self, 0);
  }
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
----------------------------
***/


inline static void BrotliBuildMetaBlockGreedyInternal(MemoryManager *m, const uint8_t *ringbuffer, size_t pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, ContextLut literal_context_lut, const size_t num_contexts, const uint32_t *static_context_map, const Command *commands, size_t n_commands, MetaBlockSplit *mb)
{
  union 
  {
    BlockSplitterLiteral plain;
    ContextBlockSplitter ctx;
  } lit_blocks;
  BlockSplitterCommand cmd_blocks;
  BlockSplitterDistance dist_blocks;
  size_t num_literals = 0;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    num_literals += commands[i].insert_len_;
  }

  if (num_contexts == 1)
  {
    InitBlockSplitterLiteral(m, &lit_blocks.plain, 256, 512, 400.0, num_literals, &mb->literal_split, &mb->literal_histograms, &mb->literal_histograms_size);
  }
  else
  {
    InitContextBlockSplitter(m, &lit_blocks.ctx, 256, num_contexts, 512, 400.0, num_literals, &mb->literal_split, &mb->literal_histograms, &mb->literal_histograms_size);
  }
  if (!(!0))
  {
    return;
  }
  InitBlockSplitterCommand(m, &cmd_blocks, 704, 1024, 500.0, n_commands, &mb->command_split, &mb->command_histograms, &mb->command_histograms_size);
  if (!(!0))
  {
    return;
  }
  InitBlockSplitterDistance(m, &dist_blocks, 64, 512, 100.0, n_commands, &mb->distance_split, &mb->distance_histograms, &mb->distance_histograms_size);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < n_commands; i += 1)
  {
    helper_BrotliBuildMetaBlockGreedyInternal_1(&pos, &prev_byte, &prev_byte2, m, ringbuffer, mask, literal_context_lut, num_contexts, static_context_map, commands, lit_blocks, cmd_blocks, dist_blocks, i);
  }

  if (num_contexts == 1)
  {
    BlockSplitterFinishBlockLiteral(&lit_blocks.plain, 1);
  }
  else
  {
    ContextBlockSplitterFinishBlock(&lit_blocks.ctx, m, 1);
    if (!(!0))
    {
      return;
    }
  }
  BlockSplitterFinishBlockCommand(&cmd_blocks, 1);
  BlockSplitterFinishBlockDistance(&dist_blocks, 1);
  if (num_contexts > 1)
  {
    MapStaticContexts(m, num_contexts, static_context_map, mb);
  }
}


/*** DEPENDENCIES:
static void BlockSplitterFinishBlockDistance(BlockSplitterDistance *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramDistance *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearDistance(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockDistance_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
  }
}


----------------------------
typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
----------------------------
static void InitContextBlockSplitter(MemoryManager *m, ContextBlockSplitter *self, size_t alphabet_size, size_t num_contexts, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramLiteral **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types;
  ;
  self->alphabet_size_ = alphabet_size;
  self->num_contexts_ = num_contexts;
  self->max_block_types_ = 256 / num_contexts;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  max_num_types = brotli_min_size_t(max_num_blocks, self->max_block_types_ + 1);
  {
    helper_InitContextBlockSplitter_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitContextBlockSplitter_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  split->num_blocks = max_num_blocks;
  if (!(!0))
  {
    return;
  }
  ;
  *histograms_size = max_num_types * num_contexts;
  *histograms = ((*histograms_size) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramLiteral)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsLiteral(&self->histograms_[0], num_contexts);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
static void InitBlockSplitterLiteral(MemoryManager *m, BlockSplitterLiteral *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramLiteral **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterLiteral_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterLiteral_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramLiteral *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramLiteral)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearLiteral(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


----------------------------
typedef struct BlockSplitterDistance
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramDistance *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterDistance
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
----------------------------
static void MapStaticContexts(MemoryManager *m, size_t num_contexts, const uint32_t *static_context_map, MetaBlockSplit *mb)
{
  size_t i;
  ;
  mb->literal_context_map_size = mb->literal_split.num_types << 6;
  mb->literal_context_map = (mb->literal_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->literal_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < mb->literal_split.num_types; i += 1)
  {
    uint32_t offset = (uint32_t) (i * num_contexts);
    size_t j;
    for (j = 0; j < (1u << 6); j += 1)
    {
      mb->literal_context_map[(i << 6) + j] = offset + static_context_map[j];
    }

  }

}


----------------------------
static void BlockSplitterFinishBlockLiteral(BlockSplitterLiteral *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearLiteral(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockLiteral_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
  }
}


----------------------------
static void BlockSplitterFinishBlockCommand(BlockSplitterCommand *self, int is_final)
{
  BlockSplit *split = self->split_;
  double *last_entropy = self->last_entropy_;
  HistogramCommand *histograms = self->histograms_;
  self->block_size_ = brotli_max_size_t(self->block_size_, self->min_block_size_);
  if (self->num_blocks_ == 0)
  {
    split->lengths[0] = (uint32_t) self->block_size_;
    split->types[0] = 0;
    last_entropy[0] = BitsEntropy(histograms[0].data_, self->alphabet_size_);
    last_entropy[1] = last_entropy[0];
    self->num_blocks_ += 1;
    split->num_types += 1;
    self->curr_histogram_ix_ += 1;
    if (self->curr_histogram_ix_ < (*self->histograms_size_))
    {
      HistogramClearCommand(&histograms[self->curr_histogram_ix_]);
    }
    self->block_size_ = 0;
  }
  else
    if (self->block_size_ > 0)
  {
    helper_BlockSplitterFinishBlockCommand_1(self, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types;
    split->num_blocks = self->num_blocks_;
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
typedef struct BlockSplitterLiteral
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterLiteral
----------------------------
static void ContextBlockSplitterFinishBlock(ContextBlockSplitter *self, MemoryManager *m, int is_final)
{
  BlockSplit *split = self->split_;
  const size_t num_contexts = self->num_contexts_;
  double *last_entropy = self->last_entropy_;
  HistogramLiteral *histograms = self->histograms_;
  if (self->block_size_ < self->min_block_size_)
  {
    self->block_size_ = self->min_block_size_;
  }
  if (self->num_blocks_ == 0)
  {
    helper_ContextBlockSplitterFinishBlock_1(&num_contexts, self, split, last_entropy, histograms);
  }
  else
    if (self->block_size_ > 0)
  {
    helper_ContextBlockSplitterFinishBlock_2(&num_contexts, self, m, split, last_entropy, histograms);
  }
  if (is_final)
  {
    *self->histograms_size_ = split->num_types * num_contexts;
    split->num_blocks = self->num_blocks_;
  }
}


----------------------------
static void InitBlockSplitterDistance(MemoryManager *m, BlockSplitterDistance *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramDistance **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterDistance_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterDistance_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramDistance *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramDistance)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearDistance(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


----------------------------
static void InitBlockSplitterCommand(MemoryManager *m, BlockSplitterCommand *self, size_t alphabet_size, size_t min_block_size, double split_threshold, size_t num_symbols, BlockSplit *split, HistogramCommand **histograms, size_t *histograms_size)
{
  size_t max_num_blocks = (num_symbols / min_block_size) + 1;
  size_t max_num_types = brotli_min_size_t(max_num_blocks, 256 + 1);
  self->alphabet_size_ = alphabet_size;
  self->min_block_size_ = min_block_size;
  self->split_threshold_ = split_threshold;
  self->num_blocks_ = 0;
  self->split_ = split;
  self->histograms_size_ = histograms_size;
  self->target_block_size_ = min_block_size;
  self->block_size_ = 0;
  self->curr_histogram_ix_ = 0;
  self->merge_last_count_ = 0;
  {
    helper_InitBlockSplitterCommand_1(m, split, max_num_blocks);
  }
  ;
  {
    helper_InitBlockSplitterCommand_2(m, split, max_num_blocks);
  }
  ;
  if (!(!0))
  {
    return;
  }
  self->split_->num_blocks = max_num_blocks;
  ;
  *histograms_size = max_num_types;
  *histograms = ((*histograms_size) > 0) ? ((HistogramCommand *) BrotliAllocate(m, (*histograms_size) * (sizeof(HistogramCommand)))) : (0);
  self->histograms_ = *histograms;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  HistogramClearCommand(&self->histograms_[0]);
  self->last_histogram_ix_[0] = (self->last_histogram_ix_[1] = 0);
}


----------------------------
typedef struct BlockSplitterCommand
{
  size_t alphabet_size_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramCommand *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2];
  size_t merge_last_count_;
} BlockSplitterCommand
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void helper_BrotliBuildMetaBlockGreedyInternal_1(size_t * const pos_ref, uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, MemoryManager * const m, const uint8_t * const ringbuffer, size_t mask, ContextLut literal_context_lut, const size_t num_contexts, const uint32_t * const static_context_map, const Command * const commands, union 
{
  BlockSplitterLiteral plain;
  ContextBlockSplitter ctx;
} lit_blocks, BlockSplitterCommand cmd_blocks, BlockSplitterDistance dist_blocks, size_t i)
{
  size_t pos = *pos_ref;
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  const Command cmd = commands[i];
  size_t j;
  BlockSplitterAddSymbolCommand(&cmd_blocks, cmd.cmd_prefix_);
  for (j = cmd.insert_len_; j != 0; j -= 1)
  {
    uint8_t literal = ringbuffer[pos & mask];
    if (num_contexts == 1)
    {
      BlockSplitterAddSymbolLiteral(&lit_blocks.plain, literal);
    }
    else
    {
      size_t context = literal_context_lut[prev_byte] | (literal_context_lut + 256)[prev_byte2];
      ContextBlockSplitterAddSymbol(&lit_blocks.ctx, m, literal, static_context_map[context]);
      if (!(!0))
      {
        return;
      }
    }
    prev_byte2 = prev_byte;
    prev_byte = literal;
    pos += 1;
  }

  pos += CommandCopyLen(&cmd);
  if (CommandCopyLen(&cmd))
  {
    prev_byte2 = ringbuffer[(pos - 2) & mask];
    prev_byte = ringbuffer[(pos - 1) & mask];
    if (cmd.cmd_prefix_ >= 128)
    {
      BlockSplitterAddSymbolDistance(&dist_blocks, cmd.dist_prefix_ & 0x3FF);
    }
  }
  *pos_ref = pos;
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


----------------------------
***/


void BrotliBuildMetaBlockGreedy(MemoryManager *m, const uint8_t *ringbuffer, size_t pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, ContextLut literal_context_lut, size_t num_contexts, const uint32_t *static_context_map, const Command *commands, size_t n_commands, MetaBlockSplit *mb)
{
  if (num_contexts == 1)
  {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_lut, 1, 0, commands, n_commands, mb);
  }
  else
  {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_lut, num_contexts, static_context_map, commands, n_commands, mb);
  }
}


/*** DEPENDENCIES:
inline static void BrotliBuildMetaBlockGreedyInternal(MemoryManager *m, const uint8_t *ringbuffer, size_t pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, ContextLut literal_context_lut, const size_t num_contexts, const uint32_t *static_context_map, const Command *commands, size_t n_commands, MetaBlockSplit *mb)
{
  union 
  {
    BlockSplitterLiteral plain;
    ContextBlockSplitter ctx;
  } lit_blocks;
  BlockSplitterCommand cmd_blocks;
  BlockSplitterDistance dist_blocks;
  size_t num_literals = 0;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    num_literals += commands[i].insert_len_;
  }

  if (num_contexts == 1)
  {
    InitBlockSplitterLiteral(m, &lit_blocks.plain, 256, 512, 400.0, num_literals, &mb->literal_split, &mb->literal_histograms, &mb->literal_histograms_size);
  }
  else
  {
    InitContextBlockSplitter(m, &lit_blocks.ctx, 256, num_contexts, 512, 400.0, num_literals, &mb->literal_split, &mb->literal_histograms, &mb->literal_histograms_size);
  }
  if (!(!0))
  {
    return;
  }
  InitBlockSplitterCommand(m, &cmd_blocks, 704, 1024, 500.0, n_commands, &mb->command_split, &mb->command_histograms, &mb->command_histograms_size);
  if (!(!0))
  {
    return;
  }
  InitBlockSplitterDistance(m, &dist_blocks, 64, 512, 100.0, n_commands, &mb->distance_split, &mb->distance_histograms, &mb->distance_histograms_size);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < n_commands; i += 1)
  {
    helper_BrotliBuildMetaBlockGreedyInternal_1(&pos, &prev_byte, &prev_byte2, m, ringbuffer, mask, literal_context_lut, num_contexts, static_context_map, commands, lit_blocks, cmd_blocks, dist_blocks, i);
  }

  if (num_contexts == 1)
  {
    BlockSplitterFinishBlockLiteral(&lit_blocks.plain, 1);
  }
  else
  {
    ContextBlockSplitterFinishBlock(&lit_blocks.ctx, m, 1);
    if (!(!0))
    {
      return;
    }
  }
  BlockSplitterFinishBlockCommand(&cmd_blocks, 1);
  BlockSplitterFinishBlockDistance(&dist_blocks, 1);
  if (num_contexts > 1)
  {
    MapStaticContexts(m, num_contexts, static_context_map, mb);
  }
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
typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static int ComputeDistanceCost(const Command *cmds, size_t num_commands, const BrotliDistanceParams *orig_params, const BrotliDistanceParams *new_params, double *cost)
{
  size_t i;
  int equal_params = 0;
  uint16_t dist_prefix;
  uint32_t dist_extra;
  double extra_bits = 0.0;
  HistogramDistance histo;
  HistogramClearDistance(&histo);
  if ((orig_params->distance_postfix_bits == new_params->distance_postfix_bits) && (orig_params->num_direct_distance_codes == new_params->num_direct_distance_codes))
  {
    equal_params = 1;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      if (equal_params)
      {
        dist_prefix = cmd->dist_prefix_;
      }
      else
      {
        uint32_t distance = CommandRestoreDistanceCode(cmd, orig_params);
        if (distance > new_params->max_distance)
        {
          return 0;
        }
        PrefixEncodeCopyDistance(distance, new_params->num_direct_distance_codes, new_params->distance_postfix_bits, &dist_prefix, &dist_extra);
      }
      HistogramAddDistance(&histo, dist_prefix & 0x3FF);
      extra_bits += dist_prefix >> 10;
    }
  }

  *cost = BrotliPopulationCostDistance(&histo) + extra_bits;
  return 1;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct BrotliDistanceParams
{
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  size_t max_distance;
} BrotliDistanceParams
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
inline static uint32_t CommandRestoreDistanceCode(const Command *self, const BrotliDistanceParams *dist)
{
  if ((self->dist_prefix_ & 0x3FFu) < (16 + dist->num_direct_distance_codes))
  {
    return self->dist_prefix_ & 0x3FFu;
  }
  else
  {
    uint32_t dcode = self->dist_prefix_ & 0x3FFu;
    uint32_t nbits = self->dist_prefix_ >> 10;
    uint32_t extra = self->dist_extra_;
    uint32_t postfix_mask = (1U << dist->distance_postfix_bits) - 1U;
    uint32_t hcode = ((dcode - dist->num_direct_distance_codes) - 16) >> dist->distance_postfix_bits;
    uint32_t lcode = ((dcode - dist->num_direct_distance_codes) - 16) & postfix_mask;
    uint32_t offset = ((2U + (hcode & 1U)) << nbits) - 4U;
    return ((((offset + extra) << dist->distance_postfix_bits) + lcode) + dist->num_direct_distance_codes) + 16;
  }
}


----------------------------
inline static void PrefixEncodeCopyDistance(size_t distance_code, size_t num_direct_codes, size_t postfix_bits, uint16_t *code, uint32_t *extra_bits)
{
  if (distance_code < (16 + num_direct_codes))
  {
    *code = (uint16_t) distance_code;
    *extra_bits = 0;
    return;
  }
  else
  {
    size_t dist = (((size_t) 1) << (postfix_bits + 2u)) + ((distance_code - 16) - num_direct_codes);
    size_t bucket = Log2FloorNonZero(dist) - 1;
    size_t postfix_mask = (1u << postfix_bits) - 1;
    size_t postfix = dist & postfix_mask;
    size_t prefix = (dist >> bucket) & 1;
    size_t offset = (2 + prefix) << bucket;
    size_t nbits = bucket - postfix_bits;
    *code = (uint16_t) ((nbits << 10) | (((16 + num_direct_codes) + (((2 * (nbits - 1)) + prefix) << postfix_bits)) + postfix));
    *extra_bits = (uint32_t) ((dist - offset) >> postfix_bits);
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
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


static void RecomputeDistancePrefixes(Command *cmds, size_t num_commands, const BrotliDistanceParams *orig_params, const BrotliDistanceParams *new_params)
{
  size_t i;
  if ((orig_params->distance_postfix_bits == new_params->distance_postfix_bits) && (orig_params->num_direct_distance_codes == new_params->num_direct_distance_codes))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      PrefixEncodeCopyDistance(CommandRestoreDistanceCode(cmd, orig_params), new_params->num_direct_distance_codes, new_params->distance_postfix_bits, &cmd->dist_prefix_, &cmd->dist_extra_);
    }
  }

}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
typedef struct BrotliDistanceParams
{
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  size_t max_distance;
} BrotliDistanceParams
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
inline static uint32_t CommandRestoreDistanceCode(const Command *self, const BrotliDistanceParams *dist)
{
  if ((self->dist_prefix_ & 0x3FFu) < (16 + dist->num_direct_distance_codes))
  {
    return self->dist_prefix_ & 0x3FFu;
  }
  else
  {
    uint32_t dcode = self->dist_prefix_ & 0x3FFu;
    uint32_t nbits = self->dist_prefix_ >> 10;
    uint32_t extra = self->dist_extra_;
    uint32_t postfix_mask = (1U << dist->distance_postfix_bits) - 1U;
    uint32_t hcode = ((dcode - dist->num_direct_distance_codes) - 16) >> dist->distance_postfix_bits;
    uint32_t lcode = ((dcode - dist->num_direct_distance_codes) - 16) & postfix_mask;
    uint32_t offset = ((2U + (hcode & 1U)) << nbits) - 4U;
    return ((((offset + extra) << dist->distance_postfix_bits) + lcode) + dist->num_direct_distance_codes) + 16;
  }
}


----------------------------
inline static void PrefixEncodeCopyDistance(size_t distance_code, size_t num_direct_codes, size_t postfix_bits, uint16_t *code, uint32_t *extra_bits)
{
  if (distance_code < (16 + num_direct_codes))
  {
    *code = (uint16_t) distance_code;
    *extra_bits = 0;
    return;
  }
  else
  {
    size_t dist = (((size_t) 1) << (postfix_bits + 2u)) + ((distance_code - 16) - num_direct_codes);
    size_t bucket = Log2FloorNonZero(dist) - 1;
    size_t postfix_mask = (1u << postfix_bits) - 1;
    size_t postfix = dist & postfix_mask;
    size_t prefix = (dist >> bucket) & 1;
    size_t offset = (2 + prefix) << bucket;
    size_t nbits = bucket - postfix_bits;
    *code = (uint16_t) ((nbits << 10) | (((16 + num_direct_codes) + (((2 * (nbits - 1)) + prefix) << postfix_bits)) + postfix));
    *extra_bits = (uint32_t) ((dist - offset) >> postfix_bits);
  }
}


----------------------------
***/


// hint:  ['ndirect_msb_ref is a mutable refrence to uint32_t', 'check_orig_ref is a mutable refrence to int', 'best_dist_cost_ref is a mutable refrence to double']
void helper_BrotliBuildMetaBlock_1(uint32_t * const ndirect_msb_ref, int * const check_orig_ref, double * const best_dist_cost_ref, BrotliEncoderParams * const params, Command * const cmds, size_t num_commands, uint32_t npostfix, BrotliEncoderParams orig_params, BrotliEncoderParams new_params)
{
  uint32_t ndirect_msb = *ndirect_msb_ref;
  int check_orig = *check_orig_ref;
  double best_dist_cost = *best_dist_cost_ref;
  for (; ndirect_msb < 16; ndirect_msb += 1)
  {
    uint32_t ndirect = ndirect_msb << npostfix;
    int skip;
    double dist_cost;
    BrotliInitDistanceParams(&new_params, npostfix, ndirect);
    if ((npostfix == orig_params.dist.distance_postfix_bits) && (ndirect == orig_params.dist.num_direct_distance_codes))
    {
      check_orig = 0;
    }
    skip = !ComputeDistanceCost(cmds, num_commands, &orig_params.dist, &new_params.dist, &dist_cost);
    if (skip || (dist_cost > best_dist_cost))
    {
      break;
    }
    best_dist_cost = dist_cost;
    params->dist = new_params.dist;
  }

  if (ndirect_msb > 0)
  {
    ndirect_msb -= 1;
  }
  ndirect_msb /= 2;
  *ndirect_msb_ref = ndirect_msb;
  *check_orig_ref = check_orig;
  *best_dist_cost_ref = best_dist_cost;
}


/*** DEPENDENCIES:
void BrotliInitDistanceParams(BrotliEncoderParams *params, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceParams *dist_params = &params->dist;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  uint32_t max_distance;
  dist_params->distance_postfix_bits = npostfix;
  dist_params->num_direct_distance_codes = ndirect;
  alphabet_size_max = (16 + ndirect) + (24U << (npostfix + 1));
  alphabet_size_limit = alphabet_size_max;
  max_distance = (ndirect + (1U << ((24U + npostfix) + 2))) - (1U << (npostfix + 2));
  if (params->large_window)
  {
    BrotliDistanceCodeLimit limit = BrotliCalculateDistanceCodeLimit(0x7FFFFFFC, npostfix, ndirect);
    alphabet_size_max = (16 + ndirect) + (62U << (npostfix + 1));
    alphabet_size_limit = limit.max_alphabet_size;
    max_distance = limit.max_distance;
  }
  dist_params->alphabet_size_max = alphabet_size_max;
  dist_params->alphabet_size_limit = alphabet_size_limit;
  dist_params->max_distance = max_distance;
}


----------------------------
static int ComputeDistanceCost(const Command *cmds, size_t num_commands, const BrotliDistanceParams *orig_params, const BrotliDistanceParams *new_params, double *cost)
{
  size_t i;
  int equal_params = 0;
  uint16_t dist_prefix;
  uint32_t dist_extra;
  double extra_bits = 0.0;
  HistogramDistance histo;
  HistogramClearDistance(&histo);
  if ((orig_params->distance_postfix_bits == new_params->distance_postfix_bits) && (orig_params->num_direct_distance_codes == new_params->num_direct_distance_codes))
  {
    equal_params = 1;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      if (equal_params)
      {
        dist_prefix = cmd->dist_prefix_;
      }
      else
      {
        uint32_t distance = CommandRestoreDistanceCode(cmd, orig_params);
        if (distance > new_params->max_distance)
        {
          return 0;
        }
        PrefixEncodeCopyDistance(distance, new_params->num_direct_distance_codes, new_params->distance_postfix_bits, &dist_prefix, &dist_extra);
      }
      HistogramAddDistance(&histo, dist_prefix & 0x3FF);
      extra_bits += dist_prefix >> 10;
    }
  }

  *cost = BrotliPopulationCostDistance(&histo) + extra_bits;
  return 1;
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
None
----------------------------
***/


void BrotliBuildMetaBlock(MemoryManager *m, const uint8_t *ringbuffer, const size_t pos, const size_t mask, BrotliEncoderParams *params, uint8_t prev_byte, uint8_t prev_byte2, Command *cmds, size_t num_commands, ContextType literal_context_mode, MetaBlockSplit *mb)
{
  static const size_t kMaxNumberOfHistograms = 256;
  HistogramDistance *distance_histograms;
  unsigned int distance_histograms_idx = 0;
  HistogramLiteral *literal_histograms;
  unsigned int literal_histograms_idx = 0;
  ContextType *literal_context_modes = 0;
  unsigned int literal_context_modes_idx = 0;
  size_t literal_histograms_size;
  size_t distance_histograms_size;
  size_t i;
  size_t literal_context_multiplier = 1;
  uint32_t npostfix;
  uint32_t ndirect_msb = 0;
  int check_orig = 1;
  double best_dist_cost = 1e99;
  BrotliEncoderParams orig_params = *params;
  BrotliEncoderParams new_params = *params;
  for (npostfix = 0; npostfix <= 3; npostfix += 1)
  {
    helper_BrotliBuildMetaBlock_1(&ndirect_msb, &check_orig, &best_dist_cost, params, cmds, num_commands, npostfix, orig_params, new_params);
  }

  if (check_orig)
  {
    double dist_cost;
    ComputeDistanceCost(cmds, num_commands, &orig_params.dist, &orig_params.dist, &dist_cost);
    if (dist_cost < best_dist_cost)
    {
      params->dist = orig_params.dist;
    }
  }
  RecomputeDistancePrefixes(cmds, num_commands, &orig_params.dist, &params->dist);
  BrotliSplitBlock(m, cmds, num_commands, ringbuffer, pos, mask, params, &mb->literal_split, &mb->command_split, &mb->distance_split);
  if (!(!0))
  {
    return;
  }
  if (!params->disable_literal_context_modeling)
  {
    literal_context_multiplier = 1 << 6;
    literal_context_modes_idx = (mb->literal_split.num_types > 0) ? ((ContextType *) BrotliAllocate(m, mb->literal_split.num_types * (sizeof(ContextType)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
    for (i = 0; i < mb->literal_split.num_types; i += 1)
    {
      literal_context_modes[i + literal_context_modes_idx] = literal_context_mode;
    }

  }
  literal_histograms_size = mb->literal_split.num_types * literal_context_multiplier;
  literal_histograms_idx = (literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsLiteral(literal_histograms, literal_histograms_size);
  distance_histograms_size = mb->distance_split.num_types << 2;
  distance_histograms_idx = (distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsDistance(distance_histograms, distance_histograms_size);
  ;
  mb->command_histograms_size = mb->command_split.num_types;
  mb->command_histograms = (mb->command_histograms_size > 0) ? ((HistogramCommand *) BrotliAllocate(m, mb->command_histograms_size * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsCommand(mb->command_histograms, mb->command_histograms_size);
  BrotliBuildHistogramsWithContext(cmds, num_commands, &mb->literal_split, &mb->command_split, &mb->distance_split, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_modes, literal_histograms, mb->command_histograms, distance_histograms);
  {
    BrotliFree(m, literal_context_modes);
    literal_context_modes_idx = 0;
  }
  ;
  ;
  mb->literal_context_map_size = mb->literal_split.num_types << 6;
  mb->literal_context_map = (mb->literal_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->literal_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->literal_histograms_size = mb->literal_context_map_size;
  mb->literal_histograms = (mb->literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, mb->literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsLiteral(m, literal_histograms, literal_histograms_size, kMaxNumberOfHistograms, mb->literal_histograms, &mb->literal_histograms_size, mb->literal_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, literal_histograms);
    literal_histograms_idx = 0;
  }
  ;
  if (params->disable_literal_context_modeling)
  {
    for (i = mb->literal_split.num_types; i != 0;)
    {
      size_t j = 0;
      i -= 1;
      for (; j < (1 << 6); j += 1)
      {
        mb->literal_context_map[(i << 6) + j] = mb->literal_context_map[i];
      }

    }

  }
  ;
  mb->distance_context_map_size = mb->distance_split.num_types << 2;
  mb->distance_context_map = (mb->distance_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->distance_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->distance_histograms_size = mb->distance_context_map_size;
  mb->distance_histograms = (mb->distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, mb->distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsDistance(m, distance_histograms, mb->distance_context_map_size, kMaxNumberOfHistograms, mb->distance_histograms, &mb->distance_histograms_size, mb->distance_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, distance_histograms);
    distance_histograms_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
inline static void ClearHistogramsDistance(HistogramDistance *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearDistance(array + i);

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
static int ComputeDistanceCost(const Command *cmds, size_t num_commands, const BrotliDistanceParams *orig_params, const BrotliDistanceParams *new_params, double *cost)
{
  size_t i;
  int equal_params = 0;
  uint16_t dist_prefix;
  uint32_t dist_extra;
  double extra_bits = 0.0;
  HistogramDistance histo;
  HistogramClearDistance(&histo);
  if ((orig_params->distance_postfix_bits == new_params->distance_postfix_bits) && (orig_params->num_direct_distance_codes == new_params->num_direct_distance_codes))
  {
    equal_params = 1;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      if (equal_params)
      {
        dist_prefix = cmd->dist_prefix_;
      }
      else
      {
        uint32_t distance = CommandRestoreDistanceCode(cmd, orig_params);
        if (distance > new_params->max_distance)
        {
          return 0;
        }
        PrefixEncodeCopyDistance(distance, new_params->num_direct_distance_codes, new_params->distance_postfix_bits, &dist_prefix, &dist_extra);
      }
      HistogramAddDistance(&histo, dist_prefix & 0x3FF);
      extra_bits += dist_prefix >> 10;
    }
  }

  *cost = BrotliPopulationCostDistance(&histo) + extra_bits;
  return 1;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
void BrotliBuildHistogramsWithContext(const Command *cmds, const size_t num_commands, const BlockSplit *literal_split, const BlockSplit *insert_and_copy_split, const BlockSplit *dist_split, const uint8_t *ringbuffer, size_t start_pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, const ContextType *context_modes, HistogramLiteral *literal_histograms, HistogramCommand *insert_and_copy_histograms, HistogramDistance *copy_dist_histograms)
{
  size_t pos = start_pos;
  BlockSplitIterator literal_it;
  BlockSplitIterator insert_and_copy_it;
  BlockSplitIterator dist_it;
  size_t i;
  InitBlockSplitIterator(&literal_it, literal_split);
  InitBlockSplitIterator(&insert_and_copy_it, insert_and_copy_split);
  InitBlockSplitIterator(&dist_it, dist_split);
  for (i = 0; i < num_commands; i += 1)
  {
    helper_BrotliBuildHistogramsWithContext_1(&prev_byte, &prev_byte2, &pos, cmds, ringbuffer, mask, context_modes, literal_histograms, insert_and_copy_histograms, copy_dist_histograms, literal_it, insert_and_copy_it, dist_it, i);
  }

}


----------------------------
void BrotliClusterHistogramsDistance(MemoryManager *m, const HistogramDistance *in, const size_t in_size, size_t max_histograms, HistogramDistance *out, size_t *out_size, uint32_t *histogram_symbols)
{
  uint32_t *cluster_size = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  uint32_t *clusters = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int clusters_idx = 0;
  size_t num_clusters = 0;
  const size_t max_input_histograms = 64;
  size_t pairs_capacity = (max_input_histograms * max_input_histograms) / 2;
  HistogramPair *pairs = ((pairs_capacity + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (pairs_capacity + 1) * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t i;
  if ((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < in_size; i += 1)
  {
    cluster_size[i + cluster_size_idx] = 1;
  }

  for (i = 0; i < in_size; i += 1)
  {
    out[i] = in[i];
    out[i].bit_cost_ = BrotliPopulationCostDistance(&in[i]);
    histogram_symbols[i] = (uint32_t) i;
  }

  for (i = 0; i < in_size; i += max_input_histograms)
  {
    size_t num_to_combine = brotli_min_size_t(in_size - i, max_input_histograms);
    size_t num_new_clusters;
    size_t j;
    for (j = 0; j < num_to_combine; j += 1)
    {
      clusters[(num_clusters + j) + clusters_idx] = (uint32_t) (i + j);
    }

    num_new_clusters = BrotliHistogramCombineDistance(out, cluster_size, &histogram_symbols[i], &clusters[num_clusters + clusters_idx], pairs, num_to_combine, num_to_combine, max_histograms, pairs_capacity);
    num_clusters += num_new_clusters;
  }

  {
    helper_BrotliClusterHistogramsDistance_1(&num_clusters, &pairs_capacity, &pairs_idx, m, in_size, max_histograms, out, histogram_symbols, cluster_size, clusters, pairs);
  }
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
  BrotliHistogramRemapDistance(in, in_size, clusters, num_clusters, out, histogram_symbols);
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  *out_size = BrotliHistogramReindexDistance(m, out, histogram_symbols, in_size);
  if (!(!0))
  {
    return;
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
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
static void RecomputeDistancePrefixes(Command *cmds, size_t num_commands, const BrotliDistanceParams *orig_params, const BrotliDistanceParams *new_params)
{
  size_t i;
  if ((orig_params->distance_postfix_bits == new_params->distance_postfix_bits) && (orig_params->num_direct_distance_codes == new_params->num_direct_distance_codes))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    Command *cmd = &cmds[i];
    if (CommandCopyLen(cmd) && (cmd->cmd_prefix_ >= 128))
    {
      PrefixEncodeCopyDistance(CommandRestoreDistanceCode(cmd, orig_params), new_params->num_direct_distance_codes, new_params->distance_postfix_bits, &cmd->dist_prefix_, &cmd->dist_extra_);
    }
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


----------------------------
inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

}


----------------------------
inline static void ClearHistogramsCommand(HistogramCommand *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearCommand(array + i);

}


----------------------------
void helper_BrotliBuildMetaBlock_1(uint32_t * const ndirect_msb_ref, int * const check_orig_ref, double * const best_dist_cost_ref, BrotliEncoderParams * const params, Command * const cmds, size_t num_commands, uint32_t npostfix, BrotliEncoderParams orig_params, BrotliEncoderParams new_params)
{
  uint32_t ndirect_msb = *ndirect_msb_ref;
  int check_orig = *check_orig_ref;
  double best_dist_cost = *best_dist_cost_ref;
  for (; ndirect_msb < 16; ndirect_msb += 1)
  {
    uint32_t ndirect = ndirect_msb << npostfix;
    int skip;
    double dist_cost;
    BrotliInitDistanceParams(&new_params, npostfix, ndirect);
    if ((npostfix == orig_params.dist.distance_postfix_bits) && (ndirect == orig_params.dist.num_direct_distance_codes))
    {
      check_orig = 0;
    }
    skip = !ComputeDistanceCost(cmds, num_commands, &orig_params.dist, &new_params.dist, &dist_cost);
    if (skip || (dist_cost > best_dist_cost))
    {
      break;
    }
    best_dist_cost = dist_cost;
    params->dist = new_params.dist;
  }

  if (ndirect_msb > 0)
  {
    ndirect_msb -= 1;
  }
  ndirect_msb /= 2;
  *ndirect_msb_ref = ndirect_msb;
  *check_orig_ref = check_orig;
  *best_dist_cost_ref = best_dist_cost;
}


----------------------------
void BrotliClusterHistogramsLiteral(MemoryManager *m, const HistogramLiteral *in, const size_t in_size, size_t max_histograms, HistogramLiteral *out, size_t *out_size, uint32_t *histogram_symbols)
{
  uint32_t *cluster_size = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  uint32_t *clusters = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int clusters_idx = 0;
  size_t num_clusters = 0;
  const size_t max_input_histograms = 64;
  size_t pairs_capacity = (max_input_histograms * max_input_histograms) / 2;
  HistogramPair *pairs = ((pairs_capacity + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (pairs_capacity + 1) * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t i;
  if ((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < in_size; i += 1)
  {
    cluster_size[i + cluster_size_idx] = 1;
  }

  for (i = 0; i < in_size; i += 1)
  {
    out[i] = in[i];
    out[i].bit_cost_ = BrotliPopulationCostLiteral(&in[i]);
    histogram_symbols[i] = (uint32_t) i;
  }

  for (i = 0; i < in_size; i += max_input_histograms)
  {
    size_t num_to_combine = brotli_min_size_t(in_size - i, max_input_histograms);
    size_t num_new_clusters;
    size_t j;
    for (j = 0; j < num_to_combine; j += 1)
    {
      clusters[(num_clusters + j) + clusters_idx] = (uint32_t) (i + j);
    }

    num_new_clusters = BrotliHistogramCombineLiteral(out, cluster_size, &histogram_symbols[i], &clusters[num_clusters + clusters_idx], pairs, num_to_combine, num_to_combine, max_histograms, pairs_capacity);
    num_clusters += num_new_clusters;
  }

  {
    helper_BrotliClusterHistogramsLiteral_1(&num_clusters, &pairs_capacity, &pairs_idx, m, in_size, max_histograms, out, histogram_symbols, cluster_size, clusters, pairs);
  }
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
  BrotliHistogramRemapLiteral(in, in_size, clusters, num_clusters, out, histogram_symbols);
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  *out_size = BrotliHistogramReindexLiteral(m, out, histogram_symbols, in_size);
  if (!(!0))
  {
    return;
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
None
----------------------------
***/


void BrotliOptimizeHistograms(uint32_t num_distance_codes, MetaBlockSplit *mb)
{
  uint8_t good_for_rle[704];
  size_t i;
  for (i = 0; i < mb->literal_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(256, mb->literal_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->command_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(704, mb->command_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->distance_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(num_distance_codes, mb->distance_histograms[i].data_, good_for_rle);
  }

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
typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
----------------------------
void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t *counts, uint8_t *good_for_rle)
{
  size_t nonzero_count = 0;
  size_t stride;
  size_t limit;
  size_t sum;
  const size_t streak_limit = 1240;
  size_t i;
  for (i = 0; i < length; i += 1)
  {
    if (counts[i])
    {
      nonzero_count += 1;
    }
  }

  if (nonzero_count < 16)
  {
    return;
  }
  while ((length != 0) && (counts[length - 1] == 0))
  {
    length -= 1;
  }

  if (length == 0)
  {
    return;
  }
  {
    helper_BrotliOptimizeHuffmanCountsForRle_2(&i, length, counts);
  }
  memset(good_for_rle, 0, length);
  {
    helper_BrotliOptimizeHuffmanCountsForRle_1(&i, length, counts, good_for_rle);
  }
  stride = 0;
  limit = ((256 * ((counts[0] + counts[1]) + counts[2])) / 3) + 420;
  sum = 0;
  for (i = 0; i <= length; i += 1)
  {
    helper_BrotliOptimizeHuffmanCountsForRle_3(&stride, &limit, &sum, &i, length, counts, good_for_rle, streak_limit);
  }

}


----------------------------
***/


