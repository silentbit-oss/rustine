inline static void BrotliWriteBitsPrepareStorage(size_t pos, uint8_t *array)
{
  ;
  ;
  array[pos >> 3] = 0;
}


/*** DEPENDENCIES:
***/


static size_t IndexOf(const uint8_t *v, size_t v_size, uint8_t value)
{
  size_t i = 0;
  for (; i < v_size; i += 1)
  {
    if (v[i] == value)
    {
      return i;
    }
  }

  return i;
}


/*** DEPENDENCIES:
***/


static void MoveToFront(uint8_t *v, size_t index)
{
  uint8_t value = v[index];
  size_t i;
  for (i = index; i != 0; i -= 1)
  {
    v[i] = v[i - 1];
  }

  v[0] = value;
}


/*** DEPENDENCIES:
***/


static void JumpToByteBoundary(size_t *storage_ix, uint8_t *storage)
{
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  storage[(*storage_ix) >> 3] = 0;
}


/*** DEPENDENCIES:
***/


inline static void InitHuffmanTree(HuffmanTree *self, uint32_t count, int16_t left, int16_t right)
{
  self->total_count_ = count;
  self->index_left_ = left;
  self->index_right_or_value_ = right;
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
***/


inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


/*** DEPENDENCIES:
inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}


----------------------------
***/


inline static void StoreStaticCodeLengthCode(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(40, (((uint64_t) 0x0000FFu) << 32) | 0x55555554u, storage_ix, storage);
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


inline static void StoreStaticCommandHuffmanTree(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(56, (((uint64_t) 0x926244U) << 32) | 0x16307003U, storage_ix, storage);
  BrotliWriteBits(3, 0x00000000U, storage_ix, storage);
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


inline static void StoreStaticDistanceHuffmanTree(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(28, 0x0369DC03u, storage_ix, storage);
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


inline static uint32_t BlockLengthPrefixCode(uint32_t len)
{
  uint32_t code = (len >= 177) ? ((len >= 753) ? (20) : (14)) : ((len >= 41) ? (7) : (0));
  code += 1;
  code += 1;
  while ((code < (26 - 1)) && (len >= _kBrotliPrefixCodeRanges[code + 1].offset))
    ++code;

  return code;
}


/*** DEPENDENCIES:
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26]
----------------------------
***/


static void InitBlockTypeCodeCalculator(BlockTypeCodeCalculator *self)
{
  self->last_type = 1;
  self->second_last_type = 0;
}


/*** DEPENDENCIES:
typedef struct BlockTypeCodeCalculator
{
  size_t last_type;
  size_t second_last_type;
} BlockTypeCodeCalculator
----------------------------
***/


inline static size_t NextBlockTypeCode(BlockTypeCodeCalculator *calculator, uint8_t type)
{
  size_t type_code = (type == (calculator->last_type + 1)) ? (1u) : ((type == calculator->second_last_type) ? (0u) : (type + 2u));
  calculator->second_last_type = calculator->last_type;
  calculator->last_type = type;
  return type_code;
}


/*** DEPENDENCIES:
typedef struct BlockTypeCodeCalculator
{
  size_t last_type;
  size_t second_last_type;
} BlockTypeCodeCalculator
----------------------------
***/


static void BrotliEncodeMlen(size_t length, uint64_t *bits, size_t *numbits, uint64_t *nibblesbits)
{
  size_t lg = (length == 1) ? (1) : (Log2FloorNonZero((uint32_t) (length - 1)) + 1);
  size_t mnibbles = ((lg < 16) ? (16) : (lg + 3)) / 4;
  ;
  ;
  ;
  *nibblesbits = mnibbles - 4;
  *numbits = mnibbles * 4;
  *bits = length - 1;
}


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


static void BrotliStoreHuffmanTreeOfHuffmanTreeToBitMask(const int num_codes, const uint8_t *code_length_bitdepth, size_t *storage_ix, uint8_t *storage)
{
  static const uint8_t kStorageOrder[17 + 1] = {1, 2, 3, 4, 0, 5, 17, 6, 16, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  static const uint8_t kHuffmanBitLengthHuffmanCodeSymbols[6] = {0, 7, 3, 2, 1, 15};
  static const uint8_t kHuffmanBitLengthHuffmanCodeBitLengths[6] = {2, 4, 3, 2, 2, 4};
  size_t skip_some = 0;
  size_t codes_to_store = 17 + 1;
  if (num_codes > 1)
  {
    for (; codes_to_store > 0; codes_to_store -= 1)
    {
      if (code_length_bitdepth[kStorageOrder[codes_to_store - 1]] != 0)
      {
        break;
      }
    }

  }
  if ((code_length_bitdepth[kStorageOrder[0]] == 0) && (code_length_bitdepth[kStorageOrder[1]] == 0))
  {
    skip_some = 2;
    if (code_length_bitdepth[kStorageOrder[2]] == 0)
    {
      skip_some = 3;
    }
  }
  BrotliWriteBits(2, skip_some, storage_ix, storage);
  {
    size_t i;
    for (i = skip_some; i < codes_to_store; i += 1)
    {
      size_t l = code_length_bitdepth[kStorageOrder[i]];
      BrotliWriteBits(kHuffmanBitLengthHuffmanCodeBitLengths[l], kHuffmanBitLengthHuffmanCodeSymbols[l], storage_ix, storage);
    }

  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


static void BrotliStoreHuffmanTreeToBitMask(const size_t huffman_tree_size, const uint8_t *huffman_tree, const uint8_t *huffman_tree_extra_bits, const uint8_t *code_length_bitdepth, const uint16_t *code_length_bitdepth_symbols, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t i;
  for (i = 0; i < huffman_tree_size; i += 1)
  {
    size_t ix = huffman_tree[i];
    BrotliWriteBits(code_length_bitdepth[ix], code_length_bitdepth_symbols[ix], storage_ix, storage);
    switch (ix)
    {
      case 16:
      {
        BrotliWriteBits(2, huffman_tree_extra_bits[i], storage_ix, storage);
        break;
      }

      case 17:
      {
        BrotliWriteBits(3, huffman_tree_extra_bits[i], storage_ix, storage);
        break;
      }

    }

  }

}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


static void StoreSimpleHuffmanTree(const uint8_t *depths, size_t symbols[4], size_t num_symbols, size_t max_bits, size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(2, 1, storage_ix, storage);
  BrotliWriteBits(2, num_symbols - 1, storage_ix, storage);
  {
    size_t i;
    for (i = 0; i < num_symbols; i += 1)
    {
      size_t j;
      for (j = i + 1; j < num_symbols; j += 1)
      {
        if (depths[symbols[j]] < depths[symbols[i]])
        {
          {
            size_t __brotli_swap_tmp = symbols[j];
            symbols[j] = symbols[i];
            symbols[i] = __brotli_swap_tmp;
          }
          ;
        }
      }

    }

  }
  if (num_symbols == 2)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
  }
  else
    if (num_symbols == 3)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
  }
  else
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[3], storage_ix, storage);
    BrotliWriteBits(1, (depths[symbols[0]] == 1) ? (1) : (0), storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


inline static int SortHuffmanTree(const HuffmanTree *v0, const HuffmanTree *v1)
{
  return (!(!(v0->total_count_ < v1->total_count_))) ? (1) : (0);
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
***/


void helper_BrotliBuildAndStoreHuffmanTreeFast_2(const size_t max_bits, uint8_t * const depth, size_t * const storage_ix, uint8_t * const storage, size_t count, size_t symbols[4])
{
  size_t i;
  BrotliWriteBits(2, 1, storage_ix, storage);
  BrotliWriteBits(2, count - 1, storage_ix, storage);
  for (i = 0; i < count; i += 1)
  {
    size_t j;
    for (j = i + 1; j < count; j += 1)
    {
      if (depth[symbols[j]] < depth[symbols[i]])
      {
        {
          size_t __brotli_swap_tmp = symbols[j];
          symbols[j] = symbols[i];
          symbols[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  if (count == 2)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
  }
  else
    if (count == 3)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
  }
  else
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[3], storage_ix, storage);
    BrotliWriteBits(1, (depth[symbols[0]] == 1) ? (1) : (0), storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t']
void helper_RunLengthCodeZeros_1(size_t * const i_ref, const size_t in_size, uint32_t * const v, size_t * const out_size, uint32_t * const max_run_length_prefix, uint32_t max_prefix)
{
  size_t i = *i_ref;
  ;
  if (v[i] != 0)
  {
    v[*out_size] = v[i] + (*max_run_length_prefix);
    i += 1;
    *out_size += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < in_size) && (v[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    while (reps != 0)
    {
      if (reps < (2u << max_prefix))
      {
        uint32_t run_length_prefix = Log2FloorNonZero(reps);
        const uint32_t extra_bits = reps - (1u << run_length_prefix);
        v[*out_size] = run_length_prefix + (extra_bits << 9);
        *out_size += 1;
        break;
      }
      else
      {
        const uint32_t extra_bits = (1u << max_prefix) - 1u;
        v[*out_size] = max_prefix + (extra_bits << 9);
        reps -= (2u << max_prefix) - 1u;
        *out_size += 1;
      }
    }

  }
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


// hint:  ['node_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1_1(unsigned int * const node_idx_ref, HuffmanTree * const tree, unsigned int tree_idx, HuffmanTree * const node, HuffmanTree sentinel, int i, int j)
{
  unsigned int node_idx = *node_idx_ref;
  int left;
  int right;
  if (tree[i + tree_idx].total_count_ <= tree[j + tree_idx].total_count_)
  {
    left = i;
    ++i;
  }
  else
  {
    left = j;
    ++j;
  }
  if (tree[i + tree_idx].total_count_ <= tree[j + tree_idx].total_count_)
  {
    right = i;
    ++i;
  }
  else
  {
    right = j;
    ++j;
  }
  node[(-1) + node_idx].total_count_ = tree[left + tree_idx].total_count_ + tree[right + tree_idx].total_count_;
  node[(-1) + node_idx].index_left_ = (int16_t) left;
  node[(-1) + node_idx].index_right_or_value_ = (int16_t) right;
  *((&node[node_idx])++) = sentinel;
  *node_idx_ref = node_idx;
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
***/


inline static void GetBlockLengthPrefixCode(uint32_t len, size_t *code, uint32_t *n_extra, uint32_t *extra)
{
  *code = BlockLengthPrefixCode(len);
  *n_extra = _kBrotliPrefixCodeRanges[*code].nbits;
  *extra = len - _kBrotliPrefixCodeRanges[*code].offset;
}


/*** DEPENDENCIES:
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26]
----------------------------
inline static uint32_t BlockLengthPrefixCode(uint32_t len)
{
  uint32_t code = (len >= 177) ? ((len >= 753) ? (20) : (14)) : ((len >= 41) ? (7) : (0));
  code += 1;
  code += 1;
  while ((code < (26 - 1)) && (len >= _kBrotliPrefixCodeRanges[code + 1].offset))
    ++code;

  return code;
}


----------------------------
***/


static void StoreVarLenUint8(size_t n, size_t *storage_ix, uint8_t *storage)
{
  if (n == 0)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  else
  {
    size_t nbits = Log2FloorNonZero(n);
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(3, nbits, storage_ix, storage);
    BrotliWriteBits(nbits, n - (((size_t) 1) << nbits), storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


static void StoreCompressedMetaBlockHeader(int is_final_block, size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, (uint64_t) is_final_block, storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  if (!is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void BrotliEncodeMlen(size_t length, uint64_t *bits, size_t *numbits, uint64_t *nibblesbits)
{
  size_t lg = (length == 1) ? (1) : (Log2FloorNonZero((uint32_t) (length - 1)) + 1);
  size_t mnibbles = ((lg < 16) ? (16) : (lg + 3)) / 4;
  ;
  ;
  ;
  *nibblesbits = mnibbles - 4;
  *numbits = mnibbles * 4;
  *bits = length - 1;
}


----------------------------
***/


static void BrotliStoreUncompressedMetaBlockHeader(size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, 0, storage_ix, storage);
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  BrotliWriteBits(1, 1, storage_ix, storage);
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void BrotliEncodeMlen(size_t length, uint64_t *bits, size_t *numbits, uint64_t *nibblesbits)
{
  size_t lg = (length == 1) ? (1) : (Log2FloorNonZero((uint32_t) (length - 1)) + 1);
  size_t mnibbles = ((lg < 16) ? (16) : (lg + 3)) / 4;
  ;
  ;
  ;
  *nibblesbits = mnibbles - 4;
  *numbits = mnibbles * 4;
  *bits = length - 1;
}


----------------------------
***/


static void MoveToFrontTransform(const uint32_t * restrict v_in, const size_t v_size, uint32_t *v_out)
{
  size_t i;
  uint8_t mtf[256];
  uint32_t max_value;
  if (v_size == 0)
  {
    return;
  }
  max_value = v_in[0];
  for (i = 1; i < v_size; i += 1)
  {
    if (v_in[i] > max_value)
    {
      max_value = v_in[i];
    }
  }

  ;
  for (i = 0; i <= max_value; i += 1)
  {
    mtf[i] = (uint8_t) i;
  }

  {
    size_t mtf_size = max_value + 1;
    for (i = 0; i < v_size; i += 1)
    {
      size_t index = IndexOf(mtf, mtf_size, (uint8_t) v_in[i]);
      ;
      v_out[i] = (uint32_t) index;
      MoveToFront(mtf, index);
    }

  }
}


/*** DEPENDENCIES:
static void MoveToFront(uint8_t *v, size_t index)
{
  uint8_t value = v[index];
  size_t i;
  for (i = index; i != 0; i -= 1)
  {
    v[i] = v[i - 1];
  }

  v[0] = value;
}


----------------------------
static size_t IndexOf(const uint8_t *v, size_t v_size, uint8_t value)
{
  size_t i = 0;
  for (; i < v_size; i += 1)
  {
    if (v[i] == value)
    {
      return i;
    }
  }

  return i;
}


----------------------------
***/


static void InitBlockEncoder(BlockEncoder *self, size_t histogram_length, size_t num_block_types, const uint8_t *block_types, const uint32_t *block_lengths, const size_t num_blocks)
{
  self->histogram_length_ = histogram_length;
  self->num_block_types_ = num_block_types;
  self->block_types_ = block_types;
  self->block_lengths_ = block_lengths;
  self->num_blocks_ = num_blocks;
  InitBlockTypeCodeCalculator(&self->block_split_code_.type_code_calculator);
  self->block_ix_ = 0;
  self->block_len_ = (num_blocks == 0) ? (0) : (block_lengths[0]);
  self->entropy_ix_ = 0;
  self->depths_ = 0;
  self->bits_ = 0;
}


/*** DEPENDENCIES:
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
static void InitBlockTypeCodeCalculator(BlockTypeCodeCalculator *self)
{
  self->last_type = 1;
  self->second_last_type = 0;
}


----------------------------
***/


inline static void SortHuffmanTreeItems(HuffmanTree *items, const size_t n, HuffmanTreeComparator comparator)
{
  if (n < 13)
  {
    size_t i;
    for (i = 1; i < n; i += 1)
    {
      HuffmanTree tmp = items[i];
      size_t k = i;
      size_t j = i - 1;
      while (comparator(&tmp, &items[j]))
      {
        items[k] = items[j];
        k = j;
        if (!(j--))
        {
          break;
        }
      }

      items[k] = tmp;
    }

    return;
  }
  else
  {
    int g = (n < 57) ? (2) : (0);
    for (; g < 6; g += 1)
    {
      size_t gap = kBrotliShellGaps[g];
      size_t i;
      for (i = gap; i < n; i += 1)
      {
        size_t j = i;
        HuffmanTree tmp = items[i];
        for (; (j >= gap) && comparator(&tmp, &items[j - gap]); j -= gap)
        {
          items[j] = items[j - gap];
        }

        items[j] = tmp;
      }

    }

  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef int (*HuffmanTreeComparator)(const HuffmanTree *, const HuffmanTree *)
----------------------------
extern const size_t kBrotliShellGaps[6]
----------------------------
***/


// hint:  ['node_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1(unsigned int * const node_idx_ref, uint8_t * const depth, HuffmanTree * const tree, unsigned int tree_idx, HuffmanTree * const node)
{
  unsigned int node_idx = *node_idx_ref;
  const int n = (int) ((&node[node_idx]) - (&tree[tree_idx]));
  HuffmanTree sentinel;
  int i = 0;
  int j = n + 1;
  int k;
  SortHuffmanTreeItems(tree, (size_t) n, SortHuffmanTree);
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  node[node_idx] = sentinel;
  node_idx += 1;
  node[node_idx] = sentinel;
  node_idx += 1;
  for (k = n - 1; k > 0; --k)
  {
    helper_helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1_1(&node_idx, tree, tree_idx, node, sentinel, i, j);
  }

  if (BrotliSetDepth((2 * n) - 1, tree, depth, 14))
  {
    break;
  }
  *node_idx_ref = node_idx;
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
inline static int SortHuffmanTree(const HuffmanTree *v0, const HuffmanTree *v1)
{
  return (!(!(v0->total_count_ < v1->total_count_))) ? (1) : (0);
}


----------------------------
inline static void InitHuffmanTree(HuffmanTree *self, uint32_t count, int16_t left, int16_t right)
{
  self->total_count_ = count;
  self->index_left_ = left;
  self->index_right_or_value_ = right;
}


----------------------------
inline static void SortHuffmanTreeItems(HuffmanTree *items, const size_t n, HuffmanTreeComparator comparator)
{
  if (n < 13)
  {
    size_t i;
    for (i = 1; i < n; i += 1)
    {
      HuffmanTree tmp = items[i];
      size_t k = i;
      size_t j = i - 1;
      while (comparator(&tmp, &items[j]))
      {
        items[k] = items[j];
        k = j;
        if (!(j--))
        {
          break;
        }
      }

      items[k] = tmp;
    }

    return;
  }
  else
  {
    int g = (n < 57) ? (2) : (0);
    for (; g < 6; g += 1)
    {
      size_t gap = kBrotliShellGaps[g];
      size_t i;
      for (i = gap; i < n; i += 1)
      {
        size_t j = i;
        HuffmanTree tmp = items[i];
        for (; (j >= gap) && comparator(&tmp, &items[j - gap]); j -= gap)
        {
          items[j] = items[j - gap];
        }

        items[j] = tmp;
      }

    }

  }
}


----------------------------
int BrotliSetDepth(int p0, HuffmanTree *pool, uint8_t *depth, int max_depth)
{
  int stack[16];
  int level = 0;
  int p = p0;
  ;
  stack[0] = -1;
  while (1)
  {
    if (pool[p].index_left_ >= 0)
    {
      level += 1;
      if (level > max_depth)
      {
        return 0;
      }
      stack[level] = pool[p].index_right_or_value_;
      p = pool[p].index_left_;
      continue;
    }
    else
    {
      depth[pool[p].index_right_or_value_] = (uint8_t) level;
    }
    while ((level >= 0) && (stack[level] == (-1)))
      level--;

    level -= 1;
    if (level < 0)
    {
      return 1;
    }
    p = stack[level];
    stack[level] = -1;
  }

}


----------------------------
void helper_helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1_1(unsigned int * const node_idx_ref, HuffmanTree * const tree, unsigned int tree_idx, HuffmanTree * const node, HuffmanTree sentinel, int i, int j)
{
  unsigned int node_idx = *node_idx_ref;
  int left;
  int right;
  if (tree[i + tree_idx].total_count_ <= tree[j + tree_idx].total_count_)
  {
    left = i;
    ++i;
  }
  else
  {
    left = j;
    ++j;
  }
  if (tree[i + tree_idx].total_count_ <= tree[j + tree_idx].total_count_)
  {
    right = i;
    ++i;
  }
  else
  {
    right = j;
    ++j;
  }
  node[(-1) + node_idx].total_count_ = tree[left + tree_idx].total_count_ + tree[right + tree_idx].total_count_;
  node[(-1) + node_idx].index_left_ = (int16_t) left;
  node[(-1) + node_idx].index_right_or_value_ = (int16_t) right;
  *((&node[node_idx])++) = sentinel;
  *node_idx_ref = node_idx;
}


----------------------------
***/


void helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1(const uint32_t * const histogram, uint8_t * const depth, size_t length, HuffmanTree * const tree, unsigned int tree_idx, uint32_t count_limit)
{
  HuffmanTree *node = tree;
  unsigned int node_idx = 0;
  size_t l;
  for (l = length; l != 0;)
  {
    l -= 1;
    if (histogram[l])
    {
      if (__builtin_expect(!(!(histogram[l] >= count_limit)), 1))
      {
        InitHuffmanTree(node, histogram[l], -1, (int16_t) l);
      }
      else
      {
        InitHuffmanTree(node, count_limit, -1, (int16_t) l);
      }
      node_idx += 1;
    }
  }

  {
    helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1(&node_idx, depth, tree, tree_idx, node);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
inline static void InitHuffmanTree(HuffmanTree *self, uint32_t count, int16_t left, int16_t right)
{
  self->total_count_ = count;
  self->index_left_ = left;
  self->index_right_or_value_ = right;
}


----------------------------
void helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1(unsigned int * const node_idx_ref, uint8_t * const depth, HuffmanTree * const tree, unsigned int tree_idx, HuffmanTree * const node)
{
  unsigned int node_idx = *node_idx_ref;
  const int n = (int) ((&node[node_idx]) - (&tree[tree_idx]));
  HuffmanTree sentinel;
  int i = 0;
  int j = n + 1;
  int k;
  SortHuffmanTreeItems(tree, (size_t) n, SortHuffmanTree);
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  node[node_idx] = sentinel;
  node_idx += 1;
  node[node_idx] = sentinel;
  node_idx += 1;
  for (k = n - 1; k > 0; --k)
  {
    helper_helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1_1(&node_idx, tree, tree_idx, node, sentinel, i, j);
  }

  if (BrotliSetDepth((2 * n) - 1, tree, depth, 14))
  {
    break;
  }
  *node_idx_ref = node_idx;
}


----------------------------
***/


void helper_BrotliBuildAndStoreHuffmanTreeFast_3(MemoryManager * const m, const uint32_t * const histogram, uint8_t * const depth, size_t length)
{
  const size_t max_tree_size = (2 * length) + 1;
  HuffmanTree *tree = (max_tree_size > 0) ? ((HuffmanTree *) BrotliAllocate(m, max_tree_size * (sizeof(HuffmanTree)))) : (0);
  unsigned int tree_idx = 0;
  uint32_t count_limit;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (count_limit = 1;; count_limit *= 2)
  {
    helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1(histogram, depth, length, tree, tree_idx, count_limit);
  }

  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
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
void helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1(const uint32_t * const histogram, uint8_t * const depth, size_t length, HuffmanTree * const tree, unsigned int tree_idx, uint32_t count_limit)
{
  HuffmanTree *node = tree;
  unsigned int node_idx = 0;
  size_t l;
  for (l = length; l != 0;)
  {
    l -= 1;
    if (histogram[l])
    {
      if (__builtin_expect(!(!(histogram[l] >= count_limit)), 1))
      {
        InitHuffmanTree(node, histogram[l], -1, (int16_t) l);
      }
      else
      {
        InitHuffmanTree(node, count_limit, -1, (int16_t) l);
      }
      node_idx += 1;
    }
  }

  {
    helper_helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1_1(&node_idx, depth, tree, tree_idx, node);
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
***/


void helper_BrotliBuildAndStoreHuffmanTreeFast_1(uint8_t * const depth, size_t * const storage_ix, uint8_t * const storage, size_t length)
{
  uint8_t previous_value = 8;
  size_t i;
  StoreStaticCodeLengthCode(storage_ix, storage);
  for (i = 0; i < length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    size_t k;
    for (k = i + 1; (k < length) && (depth[k] == value); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (value == 0)
    {
      BrotliWriteBits(kZeroRepsDepth[reps], kZeroRepsBits[reps], storage_ix, storage);
    }
    else
    {
      if (previous_value != value)
      {
        BrotliWriteBits(kCodeLengthDepth[value], kCodeLengthBits[value], storage_ix, storage);
        reps -= 1;
      }
      if (reps < 3)
      {
        while (reps != 0)
        {
          reps -= 1;
          BrotliWriteBits(kCodeLengthDepth[value], kCodeLengthBits[value], storage_ix, storage);
        }

      }
      else
      {
        reps -= 3;
        BrotliWriteBits(kNonZeroRepsDepth[reps], kNonZeroRepsBits[reps], storage_ix, storage);
      }
      previous_value = value;
    }
  }

}


/*** DEPENDENCIES:
static const uint32_t kNonZeroRepsDepth[704] = {6, 6, 6, 6, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}
----------------------------
inline static void StoreStaticCodeLengthCode(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(40, (((uint64_t) 0x0000FFu) << 32) | 0x55555554u, storage_ix, storage);
}


----------------------------
static const uint32_t kZeroRepsDepth[704] = {0, 4, 8, 7, 7, 7, 7, 7, 7, 7, 7, 11, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28}
----------------------------
static const uint64_t kNonZeroRepsBits[704] = {0x0000000b, 0x0000001b, 0x0000002b, 0x0000003b, 0x000002cb, 0x000006cb, 0x00000acb, 0x00000ecb, 0x000002db, 0x000006db, 0x00000adb, 0x00000edb, 0x000002eb, 0x000006eb, 0x00000aeb, 0x00000eeb, 0x000002fb, 0x000006fb, 0x00000afb, 0x00000efb, 0x0000b2cb, 0x0001b2cb, 0x0002b2cb, 0x0003b2cb, 0x0000b6cb, 0x0001b6cb, 0x0002b6cb, 0x0003b6cb, 0x0000bacb, 0x0001bacb, 0x0002bacb, 0x0003bacb, 0x0000becb, 0x0001becb, 0x0002becb, 0x0003becb, 0x0000b2db, 0x0001b2db, 0x0002b2db, 0x0003b2db, 0x0000b6db, 0x0001b6db, 0x0002b6db, 0x0003b6db, 0x0000badb, 0x0001badb, 0x0002badb, 0x0003badb, 0x0000bedb, 0x0001bedb, 0x0002bedb, 0x0003bedb, 0x0000b2eb, 0x0001b2eb, 0x0002b2eb, 0x0003b2eb, 0x0000b6eb, 0x0001b6eb, 0x0002b6eb, 0x0003b6eb, 0x0000baeb, 0x0001baeb, 0x0002baeb, 0x0003baeb, 0x0000beeb, 0x0001beeb, 0x0002beeb, 0x0003beeb, 0x0000b2fb, 0x0001b2fb, 0x0002b2fb, 0x0003b2fb, 0x0000b6fb, 0x0001b6fb, 0x0002b6fb, 0x0003b6fb, 0x0000bafb, 0x0001bafb, 0x0002bafb, 0x0003bafb, 0x0000befb, 0x0001befb, 0x0002befb, 0x0003befb, 0x002cb2cb, 0x006cb2cb, 0x00acb2cb, 0x00ecb2cb, 0x002db2cb, 0x006db2cb, 0x00adb2cb, 0x00edb2cb, 0x002eb2cb, 0x006eb2cb, 0x00aeb2cb, 0x00eeb2cb, 0x002fb2cb, 0x006fb2cb, 0x00afb2cb, 0x00efb2cb, 0x002cb6cb, 0x006cb6cb, 0x00acb6cb, 0x00ecb6cb, 0x002db6cb, 0x006db6cb, 0x00adb6cb, 0x00edb6cb, 0x002eb6cb, 0x006eb6cb, 0x00aeb6cb, 0x00eeb6cb, 0x002fb6cb, 0x006fb6cb, 0x00afb6cb, 0x00efb6cb, 0x002cbacb, 0x006cbacb, 0x00acbacb, 0x00ecbacb, 0x002dbacb, 0x006dbacb, 0x00adbacb, 0x00edbacb, 0x002ebacb, 0x006ebacb, 0x00aebacb, 0x00eebacb, 0x002fbacb, 0x006fbacb, 0x00afbacb, 0x00efbacb, 0x002cbecb, 0x006cbecb, 0x00acbecb, 0x00ecbecb, 0x002dbecb, 0x006dbecb, 0x00adbecb, 0x00edbecb, 0x002ebecb, 0x006ebecb, 0x00aebecb, 0x00eebecb, 0x002fbecb, 0x006fbecb, 0x00afbecb, 0x00efbecb, 0x002cb2db, 0x006cb2db, 0x00acb2db, 0x00ecb2db, 0x002db2db, 0x006db2db, 0x00adb2db, 0x00edb2db, 0x002eb2db, 0x006eb2db, 0x00aeb2db, 0x00eeb2db, 0x002fb2db, 0x006fb2db, 0x00afb2db, 0x00efb2db, 0x002cb6db, 0x006cb6db, 0x00acb6db, 0x00ecb6db, 0x002db6db, 0x006db6db, 0x00adb6db, 0x00edb6db, 0x002eb6db, 0x006eb6db, 0x00aeb6db, 0x00eeb6db, 0x002fb6db, 0x006fb6db, 0x00afb6db, 0x00efb6db, 0x002cbadb, 0x006cbadb, 0x00acbadb, 0x00ecbadb, 0x002dbadb, 0x006dbadb, 0x00adbadb, 0x00edbadb, 0x002ebadb, 0x006ebadb, 0x00aebadb, 0x00eebadb, 0x002fbadb, 0x006fbadb, 0x00afbadb, 0x00efbadb, 0x002cbedb, 0x006cbedb, 0x00acbedb, 0x00ecbedb, 0x002dbedb, 0x006dbedb, 0x00adbedb, 0x00edbedb, 0x002ebedb, 0x006ebedb, 0x00aebedb, 0x00eebedb, 0x002fbedb, 0x006fbedb, 0x00afbedb, 0x00efbedb, 0x002cb2eb, 0x006cb2eb, 0x00acb2eb, 0x00ecb2eb, 0x002db2eb, 0x006db2eb, 0x00adb2eb, 0x00edb2eb, 0x002eb2eb, 0x006eb2eb, 0x00aeb2eb, 0x00eeb2eb, 0x002fb2eb, 0x006fb2eb, 0x00afb2eb, 0x00efb2eb, 0x002cb6eb, 0x006cb6eb, 0x00acb6eb, 0x00ecb6eb, 0x002db6eb, 0x006db6eb, 0x00adb6eb, 0x00edb6eb, 0x002eb6eb, 0x006eb6eb, 0x00aeb6eb, 0x00eeb6eb, 0x002fb6eb, 0x006fb6eb, 0x00afb6eb, 0x00efb6eb, 0x002cbaeb, 0x006cbaeb, 0x00acbaeb, 0x00ecbaeb, 0x002dbaeb, 0x006dbaeb, 0x00adbaeb, 0x00edbaeb, 0x002ebaeb, 0x006ebaeb, 0x00aebaeb, 0x00eebaeb, 0x002fbaeb, 0x006fbaeb, 0x00afbaeb, 0x00efbaeb, 0x002cbeeb, 0x006cbeeb, 0x00acbeeb, 0x00ecbeeb, 0x002dbeeb, 0x006dbeeb, 0x00adbeeb, 0x00edbeeb, 0x002ebeeb, 0x006ebeeb, 0x00aebeeb, 0x00eebeeb, 0x002fbeeb, 0x006fbeeb, 0x00afbeeb, 0x00efbeeb, 0x002cb2fb, 0x006cb2fb, 0x00acb2fb, 0x00ecb2fb, 0x002db2fb, 0x006db2fb, 0x00adb2fb, 0x00edb2fb, 0x002eb2fb, 0x006eb2fb, 0x00aeb2fb, 0x00eeb2fb, 0x002fb2fb, 0x006fb2fb, 0x00afb2fb, 0x00efb2fb, 0x002cb6fb, 0x006cb6fb, 0x00acb6fb, 0x00ecb6fb, 0x002db6fb, 0x006db6fb, 0x00adb6fb, 0x00edb6fb, 0x002eb6fb, 0x006eb6fb, 0x00aeb6fb, 0x00eeb6fb, 0x002fb6fb, 0x006fb6fb, 0x00afb6fb, 0x00efb6fb, 0x002cbafb, 0x006cbafb, 0x00acbafb, 0x00ecbafb, 0x002dbafb, 0x006dbafb, 0x00adbafb, 0x00edbafb, 0x002ebafb, 0x006ebafb, 0x00aebafb, 0x00eebafb, 0x002fbafb, 0x006fbafb, 0x00afbafb, 0x00efbafb, 0x002cbefb, 0x006cbefb, 0x00acbefb, 0x00ecbefb, 0x002dbefb, 0x006dbefb, 0x00adbefb, 0x00edbefb, 0x002ebefb, 0x006ebefb, 0x00aebefb, 0x00eebefb, 0x002fbefb, 0x006fbefb, 0x00afbefb, 0x00efbefb, 0x0b2cb2cb, 0x1b2cb2cb, 0x2b2cb2cb, 0x3b2cb2cb, 0x0b6cb2cb, 0x1b6cb2cb, 0x2b6cb2cb, 0x3b6cb2cb, 0x0bacb2cb, 0x1bacb2cb, 0x2bacb2cb, 0x3bacb2cb, 0x0becb2cb, 0x1becb2cb, 0x2becb2cb, 0x3becb2cb, 0x0b2db2cb, 0x1b2db2cb, 0x2b2db2cb, 0x3b2db2cb, 0x0b6db2cb, 0x1b6db2cb, 0x2b6db2cb, 0x3b6db2cb, 0x0badb2cb, 0x1badb2cb, 0x2badb2cb, 0x3badb2cb, 0x0bedb2cb, 0x1bedb2cb, 0x2bedb2cb, 0x3bedb2cb, 0x0b2eb2cb, 0x1b2eb2cb, 0x2b2eb2cb, 0x3b2eb2cb, 0x0b6eb2cb, 0x1b6eb2cb, 0x2b6eb2cb, 0x3b6eb2cb, 0x0baeb2cb, 0x1baeb2cb, 0x2baeb2cb, 0x3baeb2cb, 0x0beeb2cb, 0x1beeb2cb, 0x2beeb2cb, 0x3beeb2cb, 0x0b2fb2cb, 0x1b2fb2cb, 0x2b2fb2cb, 0x3b2fb2cb, 0x0b6fb2cb, 0x1b6fb2cb, 0x2b6fb2cb, 0x3b6fb2cb, 0x0bafb2cb, 0x1bafb2cb, 0x2bafb2cb, 0x3bafb2cb, 0x0befb2cb, 0x1befb2cb, 0x2befb2cb, 0x3befb2cb, 0x0b2cb6cb, 0x1b2cb6cb, 0x2b2cb6cb, 0x3b2cb6cb, 0x0b6cb6cb, 0x1b6cb6cb, 0x2b6cb6cb, 0x3b6cb6cb, 0x0bacb6cb, 0x1bacb6cb, 0x2bacb6cb, 0x3bacb6cb, 0x0becb6cb, 0x1becb6cb, 0x2becb6cb, 0x3becb6cb, 0x0b2db6cb, 0x1b2db6cb, 0x2b2db6cb, 0x3b2db6cb, 0x0b6db6cb, 0x1b6db6cb, 0x2b6db6cb, 0x3b6db6cb, 0x0badb6cb, 0x1badb6cb, 0x2badb6cb, 0x3badb6cb, 0x0bedb6cb, 0x1bedb6cb, 0x2bedb6cb, 0x3bedb6cb, 0x0b2eb6cb, 0x1b2eb6cb, 0x2b2eb6cb, 0x3b2eb6cb, 0x0b6eb6cb, 0x1b6eb6cb, 0x2b6eb6cb, 0x3b6eb6cb, 0x0baeb6cb, 0x1baeb6cb, 0x2baeb6cb, 0x3baeb6cb, 0x0beeb6cb, 0x1beeb6cb, 0x2beeb6cb, 0x3beeb6cb, 0x0b2fb6cb, 0x1b2fb6cb, 0x2b2fb6cb, 0x3b2fb6cb, 0x0b6fb6cb, 0x1b6fb6cb, 0x2b6fb6cb, 0x3b6fb6cb, 0x0bafb6cb, 0x1bafb6cb, 0x2bafb6cb, 0x3bafb6cb, 0x0befb6cb, 0x1befb6cb, 0x2befb6cb, 0x3befb6cb, 0x0b2cbacb, 0x1b2cbacb, 0x2b2cbacb, 0x3b2cbacb, 0x0b6cbacb, 0x1b6cbacb, 0x2b6cbacb, 0x3b6cbacb, 0x0bacbacb, 0x1bacbacb, 0x2bacbacb, 0x3bacbacb, 0x0becbacb, 0x1becbacb, 0x2becbacb, 0x3becbacb, 0x0b2dbacb, 0x1b2dbacb, 0x2b2dbacb, 0x3b2dbacb, 0x0b6dbacb, 0x1b6dbacb, 0x2b6dbacb, 0x3b6dbacb, 0x0badbacb, 0x1badbacb, 0x2badbacb, 0x3badbacb, 0x0bedbacb, 0x1bedbacb, 0x2bedbacb, 0x3bedbacb, 0x0b2ebacb, 0x1b2ebacb, 0x2b2ebacb, 0x3b2ebacb, 0x0b6ebacb, 0x1b6ebacb, 0x2b6ebacb, 0x3b6ebacb, 0x0baebacb, 0x1baebacb, 0x2baebacb, 0x3baebacb, 0x0beebacb, 0x1beebacb, 0x2beebacb, 0x3beebacb, 0x0b2fbacb, 0x1b2fbacb, 0x2b2fbacb, 0x3b2fbacb, 0x0b6fbacb, 0x1b6fbacb, 0x2b6fbacb, 0x3b6fbacb, 0x0bafbacb, 0x1bafbacb, 0x2bafbacb, 0x3bafbacb, 0x0befbacb, 0x1befbacb, 0x2befbacb, 0x3befbacb, 0x0b2cbecb, 0x1b2cbecb, 0x2b2cbecb, 0x3b2cbecb, 0x0b6cbecb, 0x1b6cbecb, 0x2b6cbecb, 0x3b6cbecb, 0x0bacbecb, 0x1bacbecb, 0x2bacbecb, 0x3bacbecb, 0x0becbecb, 0x1becbecb, 0x2becbecb, 0x3becbecb, 0x0b2dbecb, 0x1b2dbecb, 0x2b2dbecb, 0x3b2dbecb, 0x0b6dbecb, 0x1b6dbecb, 0x2b6dbecb, 0x3b6dbecb, 0x0badbecb, 0x1badbecb, 0x2badbecb, 0x3badbecb, 0x0bedbecb, 0x1bedbecb, 0x2bedbecb, 0x3bedbecb, 0x0b2ebecb, 0x1b2ebecb, 0x2b2ebecb, 0x3b2ebecb, 0x0b6ebecb, 0x1b6ebecb, 0x2b6ebecb, 0x3b6ebecb, 0x0baebecb, 0x1baebecb, 0x2baebecb, 0x3baebecb, 0x0beebecb, 0x1beebecb, 0x2beebecb, 0x3beebecb, 0x0b2fbecb, 0x1b2fbecb, 0x2b2fbecb, 0x3b2fbecb, 0x0b6fbecb, 0x1b6fbecb, 0x2b6fbecb, 0x3b6fbecb, 0x0bafbecb, 0x1bafbecb, 0x2bafbecb, 0x3bafbecb, 0x0befbecb, 0x1befbecb, 0x2befbecb, 0x3befbecb, 0x0b2cb2db, 0x1b2cb2db, 0x2b2cb2db, 0x3b2cb2db, 0x0b6cb2db, 0x1b6cb2db, 0x2b6cb2db, 0x3b6cb2db, 0x0bacb2db, 0x1bacb2db, 0x2bacb2db, 0x3bacb2db, 0x0becb2db, 0x1becb2db, 0x2becb2db, 0x3becb2db, 0x0b2db2db, 0x1b2db2db, 0x2b2db2db, 0x3b2db2db, 0x0b6db2db, 0x1b6db2db, 0x2b6db2db, 0x3b6db2db, 0x0badb2db, 0x1badb2db, 0x2badb2db, 0x3badb2db, 0x0bedb2db, 0x1bedb2db, 0x2bedb2db, 0x3bedb2db, 0x0b2eb2db, 0x1b2eb2db, 0x2b2eb2db, 0x3b2eb2db, 0x0b6eb2db, 0x1b6eb2db, 0x2b6eb2db, 0x3b6eb2db, 0x0baeb2db, 0x1baeb2db, 0x2baeb2db, 0x3baeb2db, 0x0beeb2db, 0x1beeb2db, 0x2beeb2db, 0x3beeb2db, 0x0b2fb2db, 0x1b2fb2db, 0x2b2fb2db, 0x3b2fb2db, 0x0b6fb2db, 0x1b6fb2db, 0x2b6fb2db, 0x3b6fb2db, 0x0bafb2db, 0x1bafb2db, 0x2bafb2db, 0x3bafb2db, 0x0befb2db, 0x1befb2db, 0x2befb2db, 0x3befb2db, 0x0b2cb6db, 0x1b2cb6db, 0x2b2cb6db, 0x3b2cb6db, 0x0b6cb6db, 0x1b6cb6db, 0x2b6cb6db, 0x3b6cb6db, 0x0bacb6db, 0x1bacb6db, 0x2bacb6db, 0x3bacb6db, 0x0becb6db, 0x1becb6db, 0x2becb6db, 0x3becb6db, 0x0b2db6db, 0x1b2db6db, 0x2b2db6db, 0x3b2db6db, 0x0b6db6db, 0x1b6db6db, 0x2b6db6db, 0x3b6db6db, 0x0badb6db, 0x1badb6db, 0x2badb6db, 0x3badb6db, 0x0bedb6db, 0x1bedb6db, 0x2bedb6db, 0x3bedb6db, 0x0b2eb6db, 0x1b2eb6db, 0x2b2eb6db, 0x3b2eb6db, 0x0b6eb6db, 0x1b6eb6db, 0x2b6eb6db, 0x3b6eb6db, 0x0baeb6db, 0x1baeb6db, 0x2baeb6db, 0x3baeb6db}
----------------------------
static const uint32_t kCodeLengthBits[18] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 15, 31, 0, 11, 7}
----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static const uint64_t kZeroRepsBits[704] = {0x00000000, 0x00000000, 0x00000000, 0x00000007, 0x00000017, 0x00000027, 0x00000037, 0x00000047, 0x00000057, 0x00000067, 0x00000077, 0x00000770, 0x00000b87, 0x00001387, 0x00001b87, 0x00002387, 0x00002b87, 0x00003387, 0x00003b87, 0x00000397, 0x00000b97, 0x00001397, 0x00001b97, 0x00002397, 0x00002b97, 0x00003397, 0x00003b97, 0x000003a7, 0x00000ba7, 0x000013a7, 0x00001ba7, 0x000023a7, 0x00002ba7, 0x000033a7, 0x00003ba7, 0x000003b7, 0x00000bb7, 0x000013b7, 0x00001bb7, 0x000023b7, 0x00002bb7, 0x000033b7, 0x00003bb7, 0x000003c7, 0x00000bc7, 0x000013c7, 0x00001bc7, 0x000023c7, 0x00002bc7, 0x000033c7, 0x00003bc7, 0x000003d7, 0x00000bd7, 0x000013d7, 0x00001bd7, 0x000023d7, 0x00002bd7, 0x000033d7, 0x00003bd7, 0x000003e7, 0x00000be7, 0x000013e7, 0x00001be7, 0x000023e7, 0x00002be7, 0x000033e7, 0x00003be7, 0x000003f7, 0x00000bf7, 0x000013f7, 0x00001bf7, 0x000023f7, 0x00002bf7, 0x000033f7, 0x00003bf7, 0x0001c387, 0x0005c387, 0x0009c387, 0x000dc387, 0x0011c387, 0x0015c387, 0x0019c387, 0x001dc387, 0x0001cb87, 0x0005cb87, 0x0009cb87, 0x000dcb87, 0x0011cb87, 0x0015cb87, 0x0019cb87, 0x001dcb87, 0x0001d387, 0x0005d387, 0x0009d387, 0x000dd387, 0x0011d387, 0x0015d387, 0x0019d387, 0x001dd387, 0x0001db87, 0x0005db87, 0x0009db87, 0x000ddb87, 0x0011db87, 0x0015db87, 0x0019db87, 0x001ddb87, 0x0001e387, 0x0005e387, 0x0009e387, 0x000de387, 0x0011e387, 0x0015e387, 0x0019e387, 0x001de387, 0x0001eb87, 0x0005eb87, 0x0009eb87, 0x000deb87, 0x0011eb87, 0x0015eb87, 0x0019eb87, 0x001deb87, 0x0001f387, 0x0005f387, 0x0009f387, 0x000df387, 0x0011f387, 0x0015f387, 0x0019f387, 0x001df387, 0x0001fb87, 0x0005fb87, 0x0009fb87, 0x000dfb87, 0x0011fb87, 0x0015fb87, 0x0019fb87, 0x001dfb87, 0x0001c397, 0x0005c397, 0x0009c397, 0x000dc397, 0x0011c397, 0x0015c397, 0x0019c397, 0x001dc397, 0x0001cb97, 0x0005cb97, 0x0009cb97, 0x000dcb97, 0x0011cb97, 0x0015cb97, 0x0019cb97, 0x001dcb97, 0x0001d397, 0x0005d397, 0x0009d397, 0x000dd397, 0x0011d397, 0x0015d397, 0x0019d397, 0x001dd397, 0x0001db97, 0x0005db97, 0x0009db97, 0x000ddb97, 0x0011db97, 0x0015db97, 0x0019db97, 0x001ddb97, 0x0001e397, 0x0005e397, 0x0009e397, 0x000de397, 0x0011e397, 0x0015e397, 0x0019e397, 0x001de397, 0x0001eb97, 0x0005eb97, 0x0009eb97, 0x000deb97, 0x0011eb97, 0x0015eb97, 0x0019eb97, 0x001deb97, 0x0001f397, 0x0005f397, 0x0009f397, 0x000df397, 0x0011f397, 0x0015f397, 0x0019f397, 0x001df397, 0x0001fb97, 0x0005fb97, 0x0009fb97, 0x000dfb97, 0x0011fb97, 0x0015fb97, 0x0019fb97, 0x001dfb97, 0x0001c3a7, 0x0005c3a7, 0x0009c3a7, 0x000dc3a7, 0x0011c3a7, 0x0015c3a7, 0x0019c3a7, 0x001dc3a7, 0x0001cba7, 0x0005cba7, 0x0009cba7, 0x000dcba7, 0x0011cba7, 0x0015cba7, 0x0019cba7, 0x001dcba7, 0x0001d3a7, 0x0005d3a7, 0x0009d3a7, 0x000dd3a7, 0x0011d3a7, 0x0015d3a7, 0x0019d3a7, 0x001dd3a7, 0x0001dba7, 0x0005dba7, 0x0009dba7, 0x000ddba7, 0x0011dba7, 0x0015dba7, 0x0019dba7, 0x001ddba7, 0x0001e3a7, 0x0005e3a7, 0x0009e3a7, 0x000de3a7, 0x0011e3a7, 0x0015e3a7, 0x0019e3a7, 0x001de3a7, 0x0001eba7, 0x0005eba7, 0x0009eba7, 0x000deba7, 0x0011eba7, 0x0015eba7, 0x0019eba7, 0x001deba7, 0x0001f3a7, 0x0005f3a7, 0x0009f3a7, 0x000df3a7, 0x0011f3a7, 0x0015f3a7, 0x0019f3a7, 0x001df3a7, 0x0001fba7, 0x0005fba7, 0x0009fba7, 0x000dfba7, 0x0011fba7, 0x0015fba7, 0x0019fba7, 0x001dfba7, 0x0001c3b7, 0x0005c3b7, 0x0009c3b7, 0x000dc3b7, 0x0011c3b7, 0x0015c3b7, 0x0019c3b7, 0x001dc3b7, 0x0001cbb7, 0x0005cbb7, 0x0009cbb7, 0x000dcbb7, 0x0011cbb7, 0x0015cbb7, 0x0019cbb7, 0x001dcbb7, 0x0001d3b7, 0x0005d3b7, 0x0009d3b7, 0x000dd3b7, 0x0011d3b7, 0x0015d3b7, 0x0019d3b7, 0x001dd3b7, 0x0001dbb7, 0x0005dbb7, 0x0009dbb7, 0x000ddbb7, 0x0011dbb7, 0x0015dbb7, 0x0019dbb7, 0x001ddbb7, 0x0001e3b7, 0x0005e3b7, 0x0009e3b7, 0x000de3b7, 0x0011e3b7, 0x0015e3b7, 0x0019e3b7, 0x001de3b7, 0x0001ebb7, 0x0005ebb7, 0x0009ebb7, 0x000debb7, 0x0011ebb7, 0x0015ebb7, 0x0019ebb7, 0x001debb7, 0x0001f3b7, 0x0005f3b7, 0x0009f3b7, 0x000df3b7, 0x0011f3b7, 0x0015f3b7, 0x0019f3b7, 0x001df3b7, 0x0001fbb7, 0x0005fbb7, 0x0009fbb7, 0x000dfbb7, 0x0011fbb7, 0x0015fbb7, 0x0019fbb7, 0x001dfbb7, 0x0001c3c7, 0x0005c3c7, 0x0009c3c7, 0x000dc3c7, 0x0011c3c7, 0x0015c3c7, 0x0019c3c7, 0x001dc3c7, 0x0001cbc7, 0x0005cbc7, 0x0009cbc7, 0x000dcbc7, 0x0011cbc7, 0x0015cbc7, 0x0019cbc7, 0x001dcbc7, 0x0001d3c7, 0x0005d3c7, 0x0009d3c7, 0x000dd3c7, 0x0011d3c7, 0x0015d3c7, 0x0019d3c7, 0x001dd3c7, 0x0001dbc7, 0x0005dbc7, 0x0009dbc7, 0x000ddbc7, 0x0011dbc7, 0x0015dbc7, 0x0019dbc7, 0x001ddbc7, 0x0001e3c7, 0x0005e3c7, 0x0009e3c7, 0x000de3c7, 0x0011e3c7, 0x0015e3c7, 0x0019e3c7, 0x001de3c7, 0x0001ebc7, 0x0005ebc7, 0x0009ebc7, 0x000debc7, 0x0011ebc7, 0x0015ebc7, 0x0019ebc7, 0x001debc7, 0x0001f3c7, 0x0005f3c7, 0x0009f3c7, 0x000df3c7, 0x0011f3c7, 0x0015f3c7, 0x0019f3c7, 0x001df3c7, 0x0001fbc7, 0x0005fbc7, 0x0009fbc7, 0x000dfbc7, 0x0011fbc7, 0x0015fbc7, 0x0019fbc7, 0x001dfbc7, 0x0001c3d7, 0x0005c3d7, 0x0009c3d7, 0x000dc3d7, 0x0011c3d7, 0x0015c3d7, 0x0019c3d7, 0x001dc3d7, 0x0001cbd7, 0x0005cbd7, 0x0009cbd7, 0x000dcbd7, 0x0011cbd7, 0x0015cbd7, 0x0019cbd7, 0x001dcbd7, 0x0001d3d7, 0x0005d3d7, 0x0009d3d7, 0x000dd3d7, 0x0011d3d7, 0x0015d3d7, 0x0019d3d7, 0x001dd3d7, 0x0001dbd7, 0x0005dbd7, 0x0009dbd7, 0x000ddbd7, 0x0011dbd7, 0x0015dbd7, 0x0019dbd7, 0x001ddbd7, 0x0001e3d7, 0x0005e3d7, 0x0009e3d7, 0x000de3d7, 0x0011e3d7, 0x0015e3d7, 0x0019e3d7, 0x001de3d7, 0x0001ebd7, 0x0005ebd7, 0x0009ebd7, 0x000debd7, 0x0011ebd7, 0x0015ebd7, 0x0019ebd7, 0x001debd7, 0x0001f3d7, 0x0005f3d7, 0x0009f3d7, 0x000df3d7, 0x0011f3d7, 0x0015f3d7, 0x0019f3d7, 0x001df3d7, 0x0001fbd7, 0x0005fbd7, 0x0009fbd7, 0x000dfbd7, 0x0011fbd7, 0x0015fbd7, 0x0019fbd7, 0x001dfbd7, 0x0001c3e7, 0x0005c3e7, 0x0009c3e7, 0x000dc3e7, 0x0011c3e7, 0x0015c3e7, 0x0019c3e7, 0x001dc3e7, 0x0001cbe7, 0x0005cbe7, 0x0009cbe7, 0x000dcbe7, 0x0011cbe7, 0x0015cbe7, 0x0019cbe7, 0x001dcbe7, 0x0001d3e7, 0x0005d3e7, 0x0009d3e7, 0x000dd3e7, 0x0011d3e7, 0x0015d3e7, 0x0019d3e7, 0x001dd3e7, 0x0001dbe7, 0x0005dbe7, 0x0009dbe7, 0x000ddbe7, 0x0011dbe7, 0x0015dbe7, 0x0019dbe7, 0x001ddbe7, 0x0001e3e7, 0x0005e3e7, 0x0009e3e7, 0x000de3e7, 0x0011e3e7, 0x0015e3e7, 0x0019e3e7, 0x001de3e7, 0x0001ebe7, 0x0005ebe7, 0x0009ebe7, 0x000debe7, 0x0011ebe7, 0x0015ebe7, 0x0019ebe7, 0x001debe7, 0x0001f3e7, 0x0005f3e7, 0x0009f3e7, 0x000df3e7, 0x0011f3e7, 0x0015f3e7, 0x0019f3e7, 0x001df3e7, 0x0001fbe7, 0x0005fbe7, 0x0009fbe7, 0x000dfbe7, 0x0011fbe7, 0x0015fbe7, 0x0019fbe7, 0x001dfbe7, 0x0001c3f7, 0x0005c3f7, 0x0009c3f7, 0x000dc3f7, 0x0011c3f7, 0x0015c3f7, 0x0019c3f7, 0x001dc3f7, 0x0001cbf7, 0x0005cbf7, 0x0009cbf7, 0x000dcbf7, 0x0011cbf7, 0x0015cbf7, 0x0019cbf7, 0x001dcbf7, 0x0001d3f7, 0x0005d3f7, 0x0009d3f7, 0x000dd3f7, 0x0011d3f7, 0x0015d3f7, 0x0019d3f7, 0x001dd3f7, 0x0001dbf7, 0x0005dbf7, 0x0009dbf7, 0x000ddbf7, 0x0011dbf7, 0x0015dbf7, 0x0019dbf7, 0x001ddbf7, 0x0001e3f7, 0x0005e3f7, 0x0009e3f7, 0x000de3f7, 0x0011e3f7, 0x0015e3f7, 0x0019e3f7, 0x001de3f7, 0x0001ebf7, 0x0005ebf7, 0x0009ebf7, 0x000debf7, 0x0011ebf7, 0x0015ebf7, 0x0019ebf7, 0x001debf7, 0x0001f3f7, 0x0005f3f7, 0x0009f3f7, 0x000df3f7, 0x0011f3f7, 0x0015f3f7, 0x0019f3f7, 0x001df3f7, 0x0001fbf7, 0x0005fbf7, 0x0009fbf7, 0x000dfbf7, 0x0011fbf7, 0x0015fbf7, 0x0019fbf7, 0x001dfbf7, 0x00e1c387, 0x02e1c387, 0x04e1c387, 0x06e1c387, 0x08e1c387, 0x0ae1c387, 0x0ce1c387, 0x0ee1c387, 0x00e5c387, 0x02e5c387, 0x04e5c387, 0x06e5c387, 0x08e5c387, 0x0ae5c387, 0x0ce5c387, 0x0ee5c387, 0x00e9c387, 0x02e9c387, 0x04e9c387, 0x06e9c387, 0x08e9c387, 0x0ae9c387, 0x0ce9c387, 0x0ee9c387, 0x00edc387, 0x02edc387, 0x04edc387, 0x06edc387, 0x08edc387, 0x0aedc387, 0x0cedc387, 0x0eedc387, 0x00f1c387, 0x02f1c387, 0x04f1c387, 0x06f1c387, 0x08f1c387, 0x0af1c387, 0x0cf1c387, 0x0ef1c387, 0x00f5c387, 0x02f5c387, 0x04f5c387, 0x06f5c387, 0x08f5c387, 0x0af5c387, 0x0cf5c387, 0x0ef5c387, 0x00f9c387, 0x02f9c387, 0x04f9c387, 0x06f9c387, 0x08f9c387, 0x0af9c387, 0x0cf9c387, 0x0ef9c387, 0x00fdc387, 0x02fdc387, 0x04fdc387, 0x06fdc387, 0x08fdc387, 0x0afdc387, 0x0cfdc387, 0x0efdc387, 0x00e1cb87, 0x02e1cb87, 0x04e1cb87, 0x06e1cb87, 0x08e1cb87, 0x0ae1cb87, 0x0ce1cb87, 0x0ee1cb87, 0x00e5cb87, 0x02e5cb87, 0x04e5cb87, 0x06e5cb87, 0x08e5cb87, 0x0ae5cb87, 0x0ce5cb87, 0x0ee5cb87, 0x00e9cb87, 0x02e9cb87, 0x04e9cb87, 0x06e9cb87, 0x08e9cb87, 0x0ae9cb87, 0x0ce9cb87, 0x0ee9cb87, 0x00edcb87, 0x02edcb87, 0x04edcb87, 0x06edcb87, 0x08edcb87, 0x0aedcb87, 0x0cedcb87, 0x0eedcb87, 0x00f1cb87, 0x02f1cb87, 0x04f1cb87, 0x06f1cb87, 0x08f1cb87, 0x0af1cb87, 0x0cf1cb87, 0x0ef1cb87, 0x00f5cb87, 0x02f5cb87, 0x04f5cb87, 0x06f5cb87, 0x08f5cb87, 0x0af5cb87, 0x0cf5cb87, 0x0ef5cb87, 0x00f9cb87, 0x02f9cb87, 0x04f9cb87, 0x06f9cb87, 0x08f9cb87}
----------------------------
static const uint8_t kCodeLengthDepth[18] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 0, 4, 4}
----------------------------
***/


void BrotliBuildAndStoreHuffmanTreeFast(MemoryManager *m, const uint32_t *histogram, const size_t histogram_total, const size_t max_bits, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t symbols[4] = {0};
  size_t length = 0;
  size_t total = histogram_total;
  while (total != 0)
  {
    if (histogram[length])
    {
      if (count < 4)
      {
        symbols[count] = length;
      }
      count += 1;
      total -= histogram[length];
    }
    length += 1;
  }

  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    depth[symbols[0]] = 0;
    bits[symbols[0]] = 0;
    return;
  }
  memset(depth, 0, length * (sizeof(depth[0])));
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_3(m, histogram, depth, length);
  }
  BrotliConvertBitDepthsToSymbols(depth, length, bits);
  if (count <= 4)
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_2(max_bits, depth, storage_ix, storage, count, symbols);
  }
  else
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_1(depth, storage_ix, storage, length);
  }
}


/*** DEPENDENCIES:
void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits)
{
  uint16_t bl_count[16] = {0};
  uint16_t next_code[16];
  size_t i;
  int code = 0;
  for (i = 0; i < len; i += 1)
  {
    bl_count[depth[i]] += 1;
  }

  bl_count[0] = 0;
  next_code[0] = 0;
  for (i = 1; i < 16; i += 1)
  {
    code = (code + bl_count[i - 1]) << 1;
    next_code[i] = (uint16_t) code;
  }

  for (i = 0; i < len; i += 1)
  {
    if (depth[i])
    {
      bits[i] = BrotliReverseBits(depth[i], next_code[depth[i]]++);
    }
  }

}


----------------------------
void helper_BrotliBuildAndStoreHuffmanTreeFast_2(const size_t max_bits, uint8_t * const depth, size_t * const storage_ix, uint8_t * const storage, size_t count, size_t symbols[4])
{
  size_t i;
  BrotliWriteBits(2, 1, storage_ix, storage);
  BrotliWriteBits(2, count - 1, storage_ix, storage);
  for (i = 0; i < count; i += 1)
  {
    size_t j;
    for (j = i + 1; j < count; j += 1)
    {
      if (depth[symbols[j]] < depth[symbols[i]])
      {
        {
          size_t __brotli_swap_tmp = symbols[j];
          symbols[j] = symbols[i];
          symbols[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  if (count == 2)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
  }
  else
    if (count == 3)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
  }
  else
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[3], storage_ix, storage);
    BrotliWriteBits(1, (depth[symbols[0]] == 1) ? (1) : (0), storage_ix, storage);
  }
}


----------------------------
void helper_BrotliBuildAndStoreHuffmanTreeFast_3(MemoryManager * const m, const uint32_t * const histogram, uint8_t * const depth, size_t length)
{
  const size_t max_tree_size = (2 * length) + 1;
  HuffmanTree *tree = (max_tree_size > 0) ? ((HuffmanTree *) BrotliAllocate(m, max_tree_size * (sizeof(HuffmanTree)))) : (0);
  unsigned int tree_idx = 0;
  uint32_t count_limit;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  for (count_limit = 1;; count_limit *= 2)
  {
    helper_helper_BrotliBuildAndStoreHuffmanTreeFast_3_1(histogram, depth, length, tree, tree_idx, count_limit);
  }

  {
    BrotliFree(m, tree);
    tree_idx = 0;
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
void helper_BrotliBuildAndStoreHuffmanTreeFast_1(uint8_t * const depth, size_t * const storage_ix, uint8_t * const storage, size_t length)
{
  uint8_t previous_value = 8;
  size_t i;
  StoreStaticCodeLengthCode(storage_ix, storage);
  for (i = 0; i < length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    size_t k;
    for (k = i + 1; (k < length) && (depth[k] == value); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (value == 0)
    {
      BrotliWriteBits(kZeroRepsDepth[reps], kZeroRepsBits[reps], storage_ix, storage);
    }
    else
    {
      if (previous_value != value)
      {
        BrotliWriteBits(kCodeLengthDepth[value], kCodeLengthBits[value], storage_ix, storage);
        reps -= 1;
      }
      if (reps < 3)
      {
        while (reps != 0)
        {
          reps -= 1;
          BrotliWriteBits(kCodeLengthDepth[value], kCodeLengthBits[value], storage_ix, storage);
        }

      }
      else
      {
        reps -= 3;
        BrotliWriteBits(kNonZeroRepsDepth[reps], kNonZeroRepsBits[reps], storage_ix, storage);
      }
      previous_value = value;
    }
  }

}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
***/


void BrotliStoreHuffmanTree(const uint8_t *depths, size_t num, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  uint8_t huffman_tree[704];
  uint8_t huffman_tree_extra_bits[704];
  size_t huffman_tree_size = 0;
  uint8_t code_length_bitdepth[17 + 1] = {0};
  uint16_t code_length_bitdepth_symbols[17 + 1];
  uint32_t huffman_tree_histogram[17 + 1] = {0};
  size_t i;
  int num_codes = 0;
  size_t code = 0;
  ;
  BrotliWriteHuffmanTree(depths, num, &huffman_tree_size, huffman_tree, huffman_tree_extra_bits);
  for (i = 0; i < huffman_tree_size; i += 1)
  {
    huffman_tree_histogram[huffman_tree[i]] += 1;
  }

  for (i = 0; i < (17 + 1); i += 1)
  {
    if (huffman_tree_histogram[i])
    {
      if (num_codes == 0)
      {
        code = i;
        num_codes = 1;
      }
      else
        if (num_codes == 1)
      {
        num_codes = 2;
        break;
      }
    }
  }

  BrotliCreateHuffmanTree(huffman_tree_histogram, 17 + 1, 5, tree, code_length_bitdepth);
  BrotliConvertBitDepthsToSymbols(code_length_bitdepth, 17 + 1, code_length_bitdepth_symbols);
  BrotliStoreHuffmanTreeOfHuffmanTreeToBitMask(num_codes, code_length_bitdepth, storage_ix, storage);
  if (num_codes == 1)
  {
    code_length_bitdepth[code] = 0;
  }
  BrotliStoreHuffmanTreeToBitMask(huffman_tree_size, huffman_tree, huffman_tree_extra_bits, code_length_bitdepth, code_length_bitdepth_symbols, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
static void BrotliStoreHuffmanTreeOfHuffmanTreeToBitMask(const int num_codes, const uint8_t *code_length_bitdepth, size_t *storage_ix, uint8_t *storage)
{
  static const uint8_t kStorageOrder[17 + 1] = {1, 2, 3, 4, 0, 5, 17, 6, 16, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  static const uint8_t kHuffmanBitLengthHuffmanCodeSymbols[6] = {0, 7, 3, 2, 1, 15};
  static const uint8_t kHuffmanBitLengthHuffmanCodeBitLengths[6] = {2, 4, 3, 2, 2, 4};
  size_t skip_some = 0;
  size_t codes_to_store = 17 + 1;
  if (num_codes > 1)
  {
    for (; codes_to_store > 0; codes_to_store -= 1)
    {
      if (code_length_bitdepth[kStorageOrder[codes_to_store - 1]] != 0)
      {
        break;
      }
    }

  }
  if ((code_length_bitdepth[kStorageOrder[0]] == 0) && (code_length_bitdepth[kStorageOrder[1]] == 0))
  {
    skip_some = 2;
    if (code_length_bitdepth[kStorageOrder[2]] == 0)
    {
      skip_some = 3;
    }
  }
  BrotliWriteBits(2, skip_some, storage_ix, storage);
  {
    size_t i;
    for (i = skip_some; i < codes_to_store; i += 1)
    {
      size_t l = code_length_bitdepth[kStorageOrder[i]];
      BrotliWriteBits(kHuffmanBitLengthHuffmanCodeBitLengths[l], kHuffmanBitLengthHuffmanCodeSymbols[l], storage_ix, storage);
    }

  }
}


----------------------------
void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits)
{
  uint16_t bl_count[16] = {0};
  uint16_t next_code[16];
  size_t i;
  int code = 0;
  for (i = 0; i < len; i += 1)
  {
    bl_count[depth[i]] += 1;
  }

  bl_count[0] = 0;
  next_code[0] = 0;
  for (i = 1; i < 16; i += 1)
  {
    code = (code + bl_count[i - 1]) << 1;
    next_code[i] = (uint16_t) code;
  }

  for (i = 0; i < len; i += 1)
  {
    if (depth[i])
    {
      bits[i] = BrotliReverseBits(depth[i], next_code[depth[i]]++);
    }
  }

}


----------------------------
static void BrotliStoreHuffmanTreeToBitMask(const size_t huffman_tree_size, const uint8_t *huffman_tree, const uint8_t *huffman_tree_extra_bits, const uint8_t *code_length_bitdepth, const uint16_t *code_length_bitdepth_symbols, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t i;
  for (i = 0; i < huffman_tree_size; i += 1)
  {
    size_t ix = huffman_tree[i];
    BrotliWriteBits(code_length_bitdepth[ix], code_length_bitdepth_symbols[ix], storage_ix, storage);
    switch (ix)
    {
      case 16:
      {
        BrotliWriteBits(2, huffman_tree_extra_bits[i], storage_ix, storage);
        break;
      }

      case 17:
      {
        BrotliWriteBits(3, huffman_tree_extra_bits[i], storage_ix, storage);
        break;
      }

    }

  }

}


----------------------------
void BrotliWriteHuffmanTree(const uint8_t *depth, size_t length, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  uint8_t previous_value = 8;
  size_t i;
  int use_rle_for_non_zero = 0;
  int use_rle_for_zero = 0;
  size_t new_length = length;
  for (i = 0; i < length; i += 1)
  {
    if (depth[(length - i) - 1] == 0)
    {
      new_length -= 1;
    }
    else
    {
      break;
    }
  }

  if (length > 50)
  {
    DecideOverRleUse(depth, new_length, &use_rle_for_non_zero, &use_rle_for_zero);
  }
  for (i = 0; i < new_length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    if (((value != 0) && use_rle_for_non_zero) || ((value == 0) && use_rle_for_zero))
    {
      size_t k;
      for (k = i + 1; (k < new_length) && (depth[k] == value); k += 1)
      {
        reps += 1;
      }

    }
    if (value == 0)
    {
      BrotliWriteHuffmanTreeRepetitionsZeros(reps, tree_size, tree, extra_bits_data);
    }
    else
    {
      BrotliWriteHuffmanTreeRepetitions(previous_value, value, reps, tree_size, tree, extra_bits_data);
      previous_value = value;
    }
    i += reps;
  }

}


----------------------------
void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth)
{
  uint32_t count_limit;
  HuffmanTree sentinel;
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  for (count_limit = 1;; count_limit *= 2)
  {
    helper_BrotliCreateHuffmanTree_1(data, length, tree_limit, tree, depth, count_limit, sentinel);
  }

}


----------------------------
***/


static void BuildHistograms(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, HistogramLiteral *lit_histo, HistogramCommand *cmd_histo, HistogramDistance *dist_histo)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    size_t j;
    HistogramAddCommand(cmd_histo, cmd.cmd_prefix_);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      HistogramAddLiteral(lit_histo, input[pos & mask]);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      HistogramAddDistance(dist_histo, cmd.dist_prefix_ & 0x3FF);
    }
  }

}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
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
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
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
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


inline static void StoreCommandExtra(const Command *cmd, size_t *storage_ix, uint8_t *storage)
{
  uint32_t copylen_code = CommandCopyLenCode(cmd);
  uint16_t inscode = GetInsertLengthCode(cmd->insert_len_);
  uint16_t copycode = GetCopyLengthCode(copylen_code);
  uint32_t insnumextra = GetInsertExtra(inscode);
  uint64_t insextraval = cmd->insert_len_ - GetInsertBase(inscode);
  uint64_t copyextraval = copylen_code - GetCopyBase(copycode);
  uint64_t bits = (copyextraval << insnumextra) | insextraval;
  BrotliWriteBits(insnumextra + GetCopyExtra(copycode), bits, storage_ix, storage);
}


/*** DEPENDENCIES:
inline static uint32_t GetInsertExtra(uint16_t inscode)
{
  return kBrotliInsExtra[inscode];
}


----------------------------
inline static uint32_t GetCopyExtra(uint16_t copycode)
{
  return kBrotliCopyExtra[copycode];
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
inline static uint16_t GetCopyLengthCode(size_t copylen)
{
  if (copylen < 10)
  {
    return (uint16_t) (copylen - 2);
  }
  else
    if (copylen < 134)
  {
    uint32_t nbits = Log2FloorNonZero(copylen - 6) - 1u;
    return (uint16_t) (((nbits << 1) + ((copylen - 6) >> nbits)) + 4);
  }
  else
    if (copylen < 2118)
  {
    return (uint16_t) (Log2FloorNonZero(copylen - 70) + 12);
  }
  else
  {
    return 23u;
  }
}


----------------------------
inline static uint32_t CommandCopyLenCode(const Command *self)
{
  uint32_t modifier = self->copy_len_ >> 25;
  int32_t delta = (int8_t) ((uint8_t) (modifier | ((modifier & 0x40) << 1)));
  return (uint32_t) (((int32_t) (self->copy_len_ & 0x1FFFFFF)) + delta);
}


----------------------------
inline static uint32_t GetInsertBase(uint16_t inscode)
{
  return kBrotliInsBase[inscode];
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
inline static uint16_t GetInsertLengthCode(size_t insertlen)
{
  if (insertlen < 6)
  {
    return (uint16_t) insertlen;
  }
  else
    if (insertlen < 130)
  {
    uint32_t nbits = Log2FloorNonZero(insertlen - 2) - 1u;
    return (uint16_t) (((nbits << 1) + ((insertlen - 2) >> nbits)) + 2);
  }
  else
    if (insertlen < 2114)
  {
    return (uint16_t) (Log2FloorNonZero(insertlen - 66) + 10);
  }
  else
    if (insertlen < 6210)
  {
    return 21u;
  }
  else
    if (insertlen < 22594)
  {
    return 22u;
  }
  else
  {
    return 23u;
  }
}


----------------------------
inline static uint32_t GetCopyBase(uint16_t copycode)
{
  return kBrotliCopyBase[copycode];
}


----------------------------
***/


static void StoreDataWithHuffmanCodes(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, const uint8_t *lit_depth, const uint16_t *lit_bits, const uint8_t *cmd_depth, const uint16_t *cmd_bits, const uint8_t *dist_depth, const uint16_t *dist_bits, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    const size_t cmd_code = cmd.cmd_prefix_;
    size_t j;
    BrotliWriteBits(cmd_depth[cmd_code], cmd_bits[cmd_code], storage_ix, storage);
    StoreCommandExtra(&cmd, storage_ix, storage);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      const uint8_t literal = input[pos & mask];
      BrotliWriteBits(lit_depth[literal], lit_bits[literal], storage_ix, storage);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      const size_t dist_code = cmd.dist_prefix_ & 0x3FF;
      const uint32_t distnumextra = cmd.dist_prefix_ >> 10;
      const uint32_t distextra = cmd.dist_extra_;
      BrotliWriteBits(dist_depth[dist_code], dist_bits[dist_code], storage_ix, storage);
      BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
    }
  }

}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
inline static void StoreCommandExtra(const Command *cmd, size_t *storage_ix, uint8_t *storage)
{
  uint32_t copylen_code = CommandCopyLenCode(cmd);
  uint16_t inscode = GetInsertLengthCode(cmd->insert_len_);
  uint16_t copycode = GetCopyLengthCode(copylen_code);
  uint32_t insnumextra = GetInsertExtra(inscode);
  uint64_t insextraval = cmd->insert_len_ - GetInsertBase(inscode);
  uint64_t copyextraval = copylen_code - GetCopyBase(copycode);
  uint64_t bits = (copyextraval << insnumextra) | insextraval;
  BrotliWriteBits(insnumextra + GetCopyExtra(copycode), bits, storage_ix, storage);
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


void helper_BrotliStoreMetaBlockFast_2(MemoryManager * const m, const uint8_t * const input, size_t start_pos, size_t mask, const Command * const commands, size_t n_commands, size_t * const storage_ix, uint8_t * const storage, uint32_t distance_alphabet_bits)
{
  HistogramLiteral lit_histo;
  HistogramCommand cmd_histo;
  HistogramDistance dist_histo;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  uint8_t cmd_depth[704];
  uint16_t cmd_bits[704];
  uint8_t dist_depth[(16 + 0) + (62U << (0 + 1))];
  uint16_t dist_bits[(16 + 0) + (62U << (0 + 1))];
  HistogramClearLiteral(&lit_histo);
  HistogramClearCommand(&cmd_histo);
  HistogramClearDistance(&dist_histo);
  BuildHistograms(input, start_pos, mask, commands, n_commands, &lit_histo, &cmd_histo, &dist_histo);
  BrotliBuildAndStoreHuffmanTreeFast(m, lit_histo.data_, lit_histo.total_count_, 8, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BrotliBuildAndStoreHuffmanTreeFast(m, cmd_histo.data_, cmd_histo.total_count_, 10, cmd_depth, cmd_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BrotliBuildAndStoreHuffmanTreeFast(m, dist_histo.data_, dist_histo.total_count_, distance_alphabet_bits, dist_depth, dist_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, cmd_depth, cmd_bits, dist_depth, dist_bits, storage_ix, storage);
}


/*** DEPENDENCIES:
static void BuildHistograms(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, HistogramLiteral *lit_histo, HistogramCommand *cmd_histo, HistogramDistance *dist_histo)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    size_t j;
    HistogramAddCommand(cmd_histo, cmd.cmd_prefix_);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      HistogramAddLiteral(lit_histo, input[pos & mask]);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      HistogramAddDistance(dist_histo, cmd.dist_prefix_ & 0x3FF);
    }
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
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
static void StoreDataWithHuffmanCodes(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, const uint8_t *lit_depth, const uint16_t *lit_bits, const uint8_t *cmd_depth, const uint16_t *cmd_bits, const uint8_t *dist_depth, const uint16_t *dist_bits, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    const size_t cmd_code = cmd.cmd_prefix_;
    size_t j;
    BrotliWriteBits(cmd_depth[cmd_code], cmd_bits[cmd_code], storage_ix, storage);
    StoreCommandExtra(&cmd, storage_ix, storage);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      const uint8_t literal = input[pos & mask];
      BrotliWriteBits(lit_depth[literal], lit_bits[literal], storage_ix, storage);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      const size_t dist_code = cmd.dist_prefix_ & 0x3FF;
      const uint32_t distnumextra = cmd.dist_prefix_ >> 10;
      const uint32_t distextra = cmd.dist_extra_;
      BrotliWriteBits(dist_depth[dist_code], dist_bits[dist_code], storage_ix, storage);
      BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
    }
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
void BrotliBuildAndStoreHuffmanTreeFast(MemoryManager *m, const uint32_t *histogram, const size_t histogram_total, const size_t max_bits, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t symbols[4] = {0};
  size_t length = 0;
  size_t total = histogram_total;
  while (total != 0)
  {
    if (histogram[length])
    {
      if (count < 4)
      {
        symbols[count] = length;
      }
      count += 1;
      total -= histogram[length];
    }
    length += 1;
  }

  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    depth[symbols[0]] = 0;
    bits[symbols[0]] = 0;
    return;
  }
  memset(depth, 0, length * (sizeof(depth[0])));
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_3(m, histogram, depth, length);
  }
  BrotliConvertBitDepthsToSymbols(depth, length, bits);
  if (count <= 4)
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_2(max_bits, depth, storage_ix, storage, count, symbols);
  }
  else
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_1(depth, storage_ix, storage, length);
  }
}


----------------------------
***/


// hint:  ['mask_ref is a mutable refrence to size_t']
void helper_BrotliStoreMetaBlockFast_1(size_t * const mask_ref, MemoryManager * const m, const uint8_t * const input, size_t start_pos, const Command * const commands, size_t n_commands, size_t * const storage_ix, uint8_t * const storage)
{
  size_t mask = *mask_ref;
  uint32_t histogram[256] = {0};
  size_t pos = start_pos;
  size_t num_literals = 0;
  size_t i;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      histogram[input[pos & mask]] += 1;
      pos += 1;
    }

    num_literals += cmd.insert_len_;
    pos += CommandCopyLen(&cmd);
  }

  BrotliBuildAndStoreHuffmanTreeFast(m, histogram, num_literals, 8, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  StoreStaticCommandHuffmanTree(storage_ix, storage);
  StoreStaticDistanceHuffmanTree(storage_ix, storage);
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, kStaticCommandCodeDepth, kStaticCommandCodeBits, kStaticDistanceCodeDepth, kStaticDistanceCodeBits, storage_ix, storage);
  *mask_ref = mask;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
static const uint8_t kStaticCommandCodeDepth[704] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11}
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
static void StoreDataWithHuffmanCodes(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, const uint8_t *lit_depth, const uint16_t *lit_bits, const uint8_t *cmd_depth, const uint16_t *cmd_bits, const uint8_t *dist_depth, const uint16_t *dist_bits, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    const size_t cmd_code = cmd.cmd_prefix_;
    size_t j;
    BrotliWriteBits(cmd_depth[cmd_code], cmd_bits[cmd_code], storage_ix, storage);
    StoreCommandExtra(&cmd, storage_ix, storage);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      const uint8_t literal = input[pos & mask];
      BrotliWriteBits(lit_depth[literal], lit_bits[literal], storage_ix, storage);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      const size_t dist_code = cmd.dist_prefix_ & 0x3FF;
      const uint32_t distnumextra = cmd.dist_prefix_ >> 10;
      const uint32_t distextra = cmd.dist_extra_;
      BrotliWriteBits(dist_depth[dist_code], dist_bits[dist_code], storage_ix, storage);
      BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
    }
  }

}


----------------------------
static const uint8_t kStaticDistanceCodeDepth[64] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
----------------------------
inline static void StoreStaticCommandHuffmanTree(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(56, (((uint64_t) 0x926244U) << 32) | 0x16307003U, storage_ix, storage);
  BrotliWriteBits(3, 0x00000000U, storage_ix, storage);
}


----------------------------
static const uint16_t kStaticDistanceCodeBits[64] = {0, 32, 16, 48, 8, 40, 24, 56, 4, 36, 20, 52, 12, 44, 28, 60, 2, 34, 18, 50, 10, 42, 26, 58, 6, 38, 22, 54, 14, 46, 30, 62, 1, 33, 17, 49, 9, 41, 25, 57, 5, 37, 21, 53, 13, 45, 29, 61, 3, 35, 19, 51, 11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63}
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static const uint16_t kStaticCommandCodeBits[704] = {0, 256, 128, 384, 64, 320, 192, 448, 32, 288, 160, 416, 96, 352, 224, 480, 16, 272, 144, 400, 80, 336, 208, 464, 48, 304, 176, 432, 112, 368, 240, 496, 8, 264, 136, 392, 72, 328, 200, 456, 40, 296, 168, 424, 104, 360, 232, 488, 24, 280, 152, 408, 88, 344, 216, 472, 56, 312, 184, 440, 120, 376, 248, 504, 4, 260, 132, 388, 68, 324, 196, 452, 36, 292, 164, 420, 100, 356, 228, 484, 20, 276, 148, 404, 84, 340, 212, 468, 52, 308, 180, 436, 116, 372, 244, 500, 12, 268, 140, 396, 76, 332, 204, 460, 44, 300, 172, 428, 108, 364, 236, 492, 28, 284, 156, 412, 92, 348, 220, 476, 60, 316, 188, 444, 124, 380, 252, 508, 2, 258, 130, 386, 66, 322, 194, 450, 34, 290, 162, 418, 98, 354, 226, 482, 18, 274, 146, 402, 82, 338, 210, 466, 50, 306, 178, 434, 114, 370, 242, 498, 10, 266, 138, 394, 74, 330, 202, 458, 42, 298, 170, 426, 106, 362, 234, 490, 26, 282, 154, 410, 90, 346, 218, 474, 58, 314, 186, 442, 122, 378, 250, 506, 6, 262, 134, 390, 70, 326, 198, 454, 38, 294, 166, 422, 102, 358, 230, 486, 22, 278, 150, 406, 86, 342, 214, 470, 54, 310, 182, 438, 118, 374, 246, 502, 14, 270, 142, 398, 78, 334, 206, 462, 46, 302, 174, 430, 110, 366, 238, 494, 30, 286, 158, 414, 94, 350, 222, 478, 62, 318, 190, 446, 126, 382, 254, 510, 1, 257, 129, 385, 65, 321, 193, 449, 33, 289, 161, 417, 97, 353, 225, 481, 17, 273, 145, 401, 81, 337, 209, 465, 49, 305, 177, 433, 113, 369, 241, 497, 9, 265, 137, 393, 73, 329, 201, 457, 41, 297, 169, 425, 105, 361, 233, 489, 25, 281, 153, 409, 89, 345, 217, 473, 57, 313, 185, 441, 121, 377, 249, 505, 5, 261, 133, 389, 69, 325, 197, 453, 37, 293, 165, 421, 101, 357, 229, 485, 21, 277, 149, 405, 85, 341, 213, 469, 53, 309, 181, 437, 117, 373, 245, 501, 13, 269, 141, 397, 77, 333, 205, 461, 45, 301, 173, 429, 109, 365, 237, 493, 29, 285, 157, 413, 93, 349, 221, 477, 61, 317, 189, 445, 125, 381, 253, 509, 3, 259, 131, 387, 67, 323, 195, 451, 35, 291, 163, 419, 99, 355, 227, 483, 19, 275, 147, 403, 83, 339, 211, 467, 51, 307, 179, 435, 115, 371, 243, 499, 11, 267, 139, 395, 75, 331, 203, 459, 43, 299, 171, 427, 107, 363, 235, 491, 27, 283, 155, 411, 91, 347, 219, 475, 59, 315, 187, 443, 123, 379, 251, 507, 7, 1031, 519, 1543, 263, 1287, 775, 1799, 135, 1159, 647, 1671, 391, 1415, 903, 1927, 71, 1095, 583, 1607, 327, 1351, 839, 1863, 199, 1223, 711, 1735, 455, 1479, 967, 1991, 39, 1063, 551, 1575, 295, 1319, 807, 1831, 167, 1191, 679, 1703, 423, 1447, 935, 1959, 103, 1127, 615, 1639, 359, 1383, 871, 1895, 231, 1255, 743, 1767, 487, 1511, 999, 2023, 23, 1047, 535, 1559, 279, 1303, 791, 1815, 151, 1175, 663, 1687, 407, 1431, 919, 1943, 87, 1111, 599, 1623, 343, 1367, 855, 1879, 215, 1239, 727, 1751, 471, 1495, 983, 2007, 55, 1079, 567, 1591, 311, 1335, 823, 1847, 183, 1207, 695, 1719, 439, 1463, 951, 1975, 119, 1143, 631, 1655, 375, 1399, 887, 1911, 247, 1271, 759, 1783, 503, 1527, 1015, 2039, 15, 1039, 527, 1551, 271, 1295, 783, 1807, 143, 1167, 655, 1679, 399, 1423, 911, 1935, 79, 1103, 591, 1615, 335, 1359, 847, 1871, 207, 1231, 719, 1743, 463, 1487, 975, 1999, 47, 1071, 559, 1583, 303, 1327, 815, 1839, 175, 1199, 687, 1711, 431, 1455, 943, 1967, 111, 1135, 623, 1647, 367, 1391, 879, 1903, 239, 1263, 751, 1775, 495, 1519, 1007, 2031, 31, 1055, 543, 1567, 287, 1311, 799, 1823, 159, 1183, 671, 1695, 415, 1439, 927, 1951, 95, 1119, 607, 1631, 351, 1375, 863, 1887, 223, 1247, 735, 1759, 479, 1503, 991, 2015, 63, 1087, 575, 1599, 319, 1343, 831, 1855, 191, 1215, 703, 1727, 447, 1471, 959, 1983, 127, 1151, 639, 1663, 383, 1407, 895, 1919, 255, 1279, 767, 1791, 511, 1535, 1023, 2047}
----------------------------
inline static void StoreStaticDistanceHuffmanTree(size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(28, 0x0369DC03u, storage_ix, storage);
}


----------------------------
void BrotliBuildAndStoreHuffmanTreeFast(MemoryManager *m, const uint32_t *histogram, const size_t histogram_total, const size_t max_bits, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t symbols[4] = {0};
  size_t length = 0;
  size_t total = histogram_total;
  while (total != 0)
  {
    if (histogram[length])
    {
      if (count < 4)
      {
        symbols[count] = length;
      }
      count += 1;
      total -= histogram[length];
    }
    length += 1;
  }

  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    depth[symbols[0]] = 0;
    bits[symbols[0]] = 0;
    return;
  }
  memset(depth, 0, length * (sizeof(depth[0])));
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_3(m, histogram, depth, length);
  }
  BrotliConvertBitDepthsToSymbols(depth, length, bits);
  if (count <= 4)
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_2(max_bits, depth, storage_ix, storage, count, symbols);
  }
  else
  {
    helper_BrotliBuildAndStoreHuffmanTreeFast_1(depth, storage_ix, storage, length);
  }
}


----------------------------
***/


void BrotliStoreMetaBlockFast(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, int is_last, const BrotliEncoderParams *params, const Command *commands, size_t n_commands, size_t *storage_ix, uint8_t *storage)
{
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  uint32_t distance_alphabet_bits = Log2FloorNonZero(num_distance_symbols - 1) + 1;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  if (n_commands <= 128)
  {
    helper_BrotliStoreMetaBlockFast_1(&mask, m, input, start_pos, commands, n_commands, storage_ix, storage);
  }
  else
  {
    helper_BrotliStoreMetaBlockFast_2(m, input, start_pos, mask, commands, n_commands, storage_ix, storage, distance_alphabet_bits);
  }
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


/*** DEPENDENCIES:
void helper_BrotliStoreMetaBlockFast_2(MemoryManager * const m, const uint8_t * const input, size_t start_pos, size_t mask, const Command * const commands, size_t n_commands, size_t * const storage_ix, uint8_t * const storage, uint32_t distance_alphabet_bits)
{
  HistogramLiteral lit_histo;
  HistogramCommand cmd_histo;
  HistogramDistance dist_histo;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  uint8_t cmd_depth[704];
  uint16_t cmd_bits[704];
  uint8_t dist_depth[(16 + 0) + (62U << (0 + 1))];
  uint16_t dist_bits[(16 + 0) + (62U << (0 + 1))];
  HistogramClearLiteral(&lit_histo);
  HistogramClearCommand(&cmd_histo);
  HistogramClearDistance(&dist_histo);
  BuildHistograms(input, start_pos, mask, commands, n_commands, &lit_histo, &cmd_histo, &dist_histo);
  BrotliBuildAndStoreHuffmanTreeFast(m, lit_histo.data_, lit_histo.total_count_, 8, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BrotliBuildAndStoreHuffmanTreeFast(m, cmd_histo.data_, cmd_histo.total_count_, 10, cmd_depth, cmd_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BrotliBuildAndStoreHuffmanTreeFast(m, dist_histo.data_, dist_histo.total_count_, distance_alphabet_bits, dist_depth, dist_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, cmd_depth, cmd_bits, dist_depth, dist_bits, storage_ix, storage);
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
static void StoreCompressedMetaBlockHeader(int is_final_block, size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, (uint64_t) is_final_block, storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  if (!is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
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
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void JumpToByteBoundary(size_t *storage_ix, uint8_t *storage)
{
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
void helper_BrotliStoreMetaBlockFast_1(size_t * const mask_ref, MemoryManager * const m, const uint8_t * const input, size_t start_pos, const Command * const commands, size_t n_commands, size_t * const storage_ix, uint8_t * const storage)
{
  size_t mask = *mask_ref;
  uint32_t histogram[256] = {0};
  size_t pos = start_pos;
  size_t num_literals = 0;
  size_t i;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      histogram[input[pos & mask]] += 1;
      pos += 1;
    }

    num_literals += cmd.insert_len_;
    pos += CommandCopyLen(&cmd);
  }

  BrotliBuildAndStoreHuffmanTreeFast(m, histogram, num_literals, 8, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  StoreStaticCommandHuffmanTree(storage_ix, storage);
  StoreStaticDistanceHuffmanTree(storage_ix, storage);
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, kStaticCommandCodeDepth, kStaticCommandCodeBits, kStaticDistanceCodeDepth, kStaticDistanceCodeBits, storage_ix, storage);
  *mask_ref = mask;
}


----------------------------
None
----------------------------
***/


static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
void BrotliStoreHuffmanTree(const uint8_t *depths, size_t num, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  uint8_t huffman_tree[704];
  uint8_t huffman_tree_extra_bits[704];
  size_t huffman_tree_size = 0;
  uint8_t code_length_bitdepth[17 + 1] = {0};
  uint16_t code_length_bitdepth_symbols[17 + 1];
  uint32_t huffman_tree_histogram[17 + 1] = {0};
  size_t i;
  int num_codes = 0;
  size_t code = 0;
  ;
  BrotliWriteHuffmanTree(depths, num, &huffman_tree_size, huffman_tree, huffman_tree_extra_bits);
  for (i = 0; i < huffman_tree_size; i += 1)
  {
    huffman_tree_histogram[huffman_tree[i]] += 1;
  }

  for (i = 0; i < (17 + 1); i += 1)
  {
    if (huffman_tree_histogram[i])
    {
      if (num_codes == 0)
      {
        code = i;
        num_codes = 1;
      }
      else
        if (num_codes == 1)
      {
        num_codes = 2;
        break;
      }
    }
  }

  BrotliCreateHuffmanTree(huffman_tree_histogram, 17 + 1, 5, tree, code_length_bitdepth);
  BrotliConvertBitDepthsToSymbols(code_length_bitdepth, 17 + 1, code_length_bitdepth_symbols);
  BrotliStoreHuffmanTreeOfHuffmanTreeToBitMask(num_codes, code_length_bitdepth, storage_ix, storage);
  if (num_codes == 1)
  {
    code_length_bitdepth[code] = 0;
  }
  BrotliStoreHuffmanTreeToBitMask(huffman_tree_size, huffman_tree, huffman_tree_extra_bits, code_length_bitdepth, code_length_bitdepth_symbols, storage_ix, storage);
}


----------------------------
static void StoreSimpleHuffmanTree(const uint8_t *depths, size_t symbols[4], size_t num_symbols, size_t max_bits, size_t *storage_ix, uint8_t *storage)
{
  BrotliWriteBits(2, 1, storage_ix, storage);
  BrotliWriteBits(2, num_symbols - 1, storage_ix, storage);
  {
    size_t i;
    for (i = 0; i < num_symbols; i += 1)
    {
      size_t j;
      for (j = i + 1; j < num_symbols; j += 1)
      {
        if (depths[symbols[j]] < depths[symbols[i]])
        {
          {
            size_t __brotli_swap_tmp = symbols[j];
            symbols[j] = symbols[i];
            symbols[i] = __brotli_swap_tmp;
          }
          ;
        }
      }

    }

  }
  if (num_symbols == 2)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
  }
  else
    if (num_symbols == 3)
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
  }
  else
  {
    BrotliWriteBits(max_bits, symbols[0], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[1], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[2], storage_ix, storage);
    BrotliWriteBits(max_bits, symbols[3], storage_ix, storage);
    BrotliWriteBits(1, (depths[symbols[0]] == 1) ? (1) : (0), storage_ix, storage);
  }
}


----------------------------
void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits)
{
  uint16_t bl_count[16] = {0};
  uint16_t next_code[16];
  size_t i;
  int code = 0;
  for (i = 0; i < len; i += 1)
  {
    bl_count[depth[i]] += 1;
  }

  bl_count[0] = 0;
  next_code[0] = 0;
  for (i = 1; i < 16; i += 1)
  {
    code = (code + bl_count[i - 1]) << 1;
    next_code[i] = (uint16_t) code;
  }

  for (i = 0; i < len; i += 1)
  {
    if (depth[i])
    {
      bits[i] = BrotliReverseBits(depth[i], next_code[depth[i]]++);
    }
  }

}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth)
{
  uint32_t count_limit;
  HuffmanTree sentinel;
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  for (count_limit = 1;; count_limit *= 2)
  {
    helper_BrotliCreateHuffmanTree_1(data, length, tree_limit, tree, depth, count_limit, sentinel);
  }

}


----------------------------
***/


void BrotliStoreMetaBlockTrivial(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, int is_last, const BrotliEncoderParams *params, const Command *commands, size_t n_commands, size_t *storage_ix, uint8_t *storage)
{
  HistogramLiteral lit_histo;
  HistogramCommand cmd_histo;
  HistogramDistance dist_histo;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  uint8_t cmd_depth[704];
  uint16_t cmd_bits[704];
  uint8_t dist_depth[(16 + 0) + (62U << (0 + 1))];
  uint16_t dist_bits[(16 + 0) + (62U << (0 + 1))];
  HuffmanTree *tree;
  unsigned int tree_idx = 0;
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  HistogramClearLiteral(&lit_histo);
  HistogramClearCommand(&cmd_histo);
  HistogramClearDistance(&dist_histo);
  BuildHistograms(input, start_pos, mask, commands, n_commands, &lit_histo, &cmd_histo, &dist_histo);
  BrotliWriteBits(13, 0, storage_ix, storage);
  tree_idx = (((2 * 704) + 1) > 0) ? ((HuffmanTree *) BrotliAllocate(m, ((2 * 704) + 1) * (sizeof(HuffmanTree)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BuildAndStoreHuffmanTree(lit_histo.data_, 256, 256, tree, lit_depth, lit_bits, storage_ix, storage);
  BuildAndStoreHuffmanTree(cmd_histo.data_, 704, 704, tree, cmd_depth, cmd_bits, storage_ix, storage);
  BuildAndStoreHuffmanTree(dist_histo.data_, (16 + 0) + (62U << (0 + 1)), num_distance_symbols, tree, dist_depth, dist_bits, storage_ix, storage);
  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, cmd_depth, cmd_bits, dist_depth, dist_bits, storage_ix, storage);
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
static void BuildHistograms(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, HistogramLiteral *lit_histo, HistogramCommand *cmd_histo, HistogramDistance *dist_histo)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    size_t j;
    HistogramAddCommand(cmd_histo, cmd.cmd_prefix_);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      HistogramAddLiteral(lit_histo, input[pos & mask]);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      HistogramAddDistance(dist_histo, cmd.dist_prefix_ & 0x3FF);
    }
  }

}


----------------------------
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
static void StoreCompressedMetaBlockHeader(int is_final_block, size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, (uint64_t) is_final_block, storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  if (!is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
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
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
static void StoreDataWithHuffmanCodes(const uint8_t *input, size_t start_pos, size_t mask, const Command *commands, size_t n_commands, const uint8_t *lit_depth, const uint16_t *lit_bits, const uint8_t *cmd_depth, const uint16_t *cmd_bits, const uint8_t *dist_depth, const uint16_t *dist_bits, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  for (i = 0; i < n_commands; i += 1)
  {
    const Command cmd = commands[i];
    const size_t cmd_code = cmd.cmd_prefix_;
    size_t j;
    BrotliWriteBits(cmd_depth[cmd_code], cmd_bits[cmd_code], storage_ix, storage);
    StoreCommandExtra(&cmd, storage_ix, storage);
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      const uint8_t literal = input[pos & mask];
      BrotliWriteBits(lit_depth[literal], lit_bits[literal], storage_ix, storage);
      pos += 1;
    }

    pos += CommandCopyLen(&cmd);
    if (CommandCopyLen(&cmd) && (cmd.cmd_prefix_ >= 128))
    {
      const size_t dist_code = cmd.dist_prefix_ & 0x3FF;
      const uint32_t distnumextra = cmd.dist_prefix_ >> 10;
      const uint32_t distextra = cmd.dist_extra_;
      BrotliWriteBits(dist_depth[dist_code], dist_bits[dist_code], storage_ix, storage);
      BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
    }
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
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void JumpToByteBoundary(size_t *storage_ix, uint8_t *storage)
{
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
None
----------------------------
***/


void BrotliStoreUncompressedMetaBlock(int is_final_block, const uint8_t * restrict input, size_t position, size_t mask, size_t len, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t masked_pos = position & mask;
  BrotliStoreUncompressedMetaBlockHeader(len, storage_ix, storage);
  JumpToByteBoundary(storage_ix, storage);
  if ((masked_pos + len) > (mask + 1))
  {
    size_t len1 = (mask + 1) - masked_pos;
    memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len1);
    *storage_ix += len1 << 3;
    len -= len1;
    masked_pos = 0;
  }
  memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len);
  *storage_ix += len << 3;
  BrotliWriteBitsPrepareStorage(*storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    JumpToByteBoundary(storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
inline static void BrotliWriteBitsPrepareStorage(size_t pos, uint8_t *array)
{
  ;
  ;
  array[pos >> 3] = 0;
}


----------------------------
static void BrotliStoreUncompressedMetaBlockHeader(size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, 0, storage_ix, storage);
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  BrotliWriteBits(1, 1, storage_ix, storage);
}


----------------------------
static void JumpToByteBoundary(size_t *storage_ix, uint8_t *storage)
{
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
***/


inline static void InitMetaBlockSplit(MetaBlockSplit *mb)
{
  BrotliInitBlockSplit(&mb->literal_split);
  BrotliInitBlockSplit(&mb->command_split);
  BrotliInitBlockSplit(&mb->distance_split);
  mb->literal_context_map = 0;
  mb->literal_context_map_size = 0;
  mb->distance_context_map = 0;
  mb->distance_context_map_size = 0;
  mb->literal_histograms = 0;
  mb->literal_histograms_size = 0;
  mb->command_histograms = 0;
  mb->command_histograms_size = 0;
  mb->distance_histograms = 0;
  mb->distance_histograms_size = 0;
}


/*** DEPENDENCIES:
void BrotliInitBlockSplit(BlockSplit *self)
{
  self->num_types = 0;
  self->num_blocks = 0;
  self->types = 0;
  self->lengths = 0;
  self->types_alloc_size = 0;
  self->lengths_alloc_size = 0;
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
***/


inline static void DestroyMetaBlockSplit(MemoryManager *m, MetaBlockSplit *mb)
{
  BrotliDestroyBlockSplit(m, &mb->literal_split);
  BrotliDestroyBlockSplit(m, &mb->command_split);
  BrotliDestroyBlockSplit(m, &mb->distance_split);
  {
    BrotliFree(m, mb->literal_context_map);
    mb->literal_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_context_map);
    mb->distance_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->literal_histograms);
    mb->literal_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->command_histograms);
    mb->command_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_histograms);
    mb->distance_histograms = 0;
  }
  ;
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


inline static void StoreBlockSwitch(BlockSplitCode *code, const uint32_t block_len, const uint8_t block_type, int is_first_block, size_t *storage_ix, uint8_t *storage)
{
  size_t typecode = NextBlockTypeCode(&code->type_code_calculator, block_type);
  size_t lencode;
  uint32_t len_nextra;
  uint32_t len_extra;
  if (!is_first_block)
  {
    BrotliWriteBits(code->type_depths[typecode], code->type_bits[typecode], storage_ix, storage);
  }
  GetBlockLengthPrefixCode(block_len, &lencode, &len_nextra, &len_extra);
  BrotliWriteBits(code->length_depths[lencode], code->length_bits[lencode], storage_ix, storage);
  BrotliWriteBits(len_nextra, len_extra, storage_ix, storage);
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
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
typedef struct BlockSplitCode
{
  BlockTypeCodeCalculator type_code_calculator;
  uint8_t type_depths[256 + 2];
  uint16_t type_bits[256 + 2];
  uint8_t length_depths[26];
  uint16_t length_bits[26];
} BlockSplitCode
----------------------------
inline static size_t NextBlockTypeCode(BlockTypeCodeCalculator *calculator, uint8_t type)
{
  size_t type_code = (type == (calculator->last_type + 1)) ? (1u) : ((type == calculator->second_last_type) ? (0u) : (type + 2u));
  calculator->second_last_type = calculator->last_type;
  calculator->last_type = type;
  return type_code;
}


----------------------------
inline static void GetBlockLengthPrefixCode(uint32_t len, size_t *code, uint32_t *n_extra, uint32_t *extra)
{
  *code = BlockLengthPrefixCode(len);
  *n_extra = _kBrotliPrefixCodeRanges[*code].nbits;
  *extra = len - _kBrotliPrefixCodeRanges[*code].offset;
}


----------------------------
***/


static void StoreSymbolWithContext(BlockEncoder *self, size_t symbol, size_t context, const uint32_t *context_map, size_t *storage_ix, uint8_t *storage, const size_t context_bits)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = ((size_t) block_type) << context_bits;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t histo_ix = context_map[self->entropy_ix_ + context];
    size_t ix = (histo_ix * self->histogram_length_) + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
inline static void StoreBlockSwitch(BlockSplitCode *code, const uint32_t block_len, const uint8_t block_type, int is_first_block, size_t *storage_ix, uint8_t *storage)
{
  size_t typecode = NextBlockTypeCode(&code->type_code_calculator, block_type);
  size_t lencode;
  uint32_t len_nextra;
  uint32_t len_extra;
  if (!is_first_block)
  {
    BrotliWriteBits(code->type_depths[typecode], code->type_bits[typecode], storage_ix, storage);
  }
  GetBlockLengthPrefixCode(block_len, &lencode, &len_nextra, &len_extra);
  BrotliWriteBits(code->length_depths[lencode], code->length_bits[lencode], storage_ix, storage);
  BrotliWriteBits(len_nextra, len_extra, storage_ix, storage);
}


----------------------------
***/


static void StoreSymbol(BlockEncoder *self, size_t symbol, size_t *storage_ix, uint8_t *storage)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = block_type * self->histogram_length_;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t ix = self->entropy_ix_ + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
inline static void StoreBlockSwitch(BlockSplitCode *code, const uint32_t block_len, const uint8_t block_type, int is_first_block, size_t *storage_ix, uint8_t *storage)
{
  size_t typecode = NextBlockTypeCode(&code->type_code_calculator, block_type);
  size_t lencode;
  uint32_t len_nextra;
  uint32_t len_extra;
  if (!is_first_block)
  {
    BrotliWriteBits(code->type_depths[typecode], code->type_bits[typecode], storage_ix, storage);
  }
  GetBlockLengthPrefixCode(block_len, &lencode, &len_nextra, &len_extra);
  BrotliWriteBits(code->length_depths[lencode], code->length_bits[lencode], storage_ix, storage);
  BrotliWriteBits(len_nextra, len_extra, storage_ix, storage);
}


----------------------------
***/


// hint:  ['prev_byte_ref is a mutable refrence to uint8_t', 'prev_byte2_ref is a mutable refrence to uint8_t']
void helper_helper_BrotliStoreMetaBlock_1_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, const uint8_t * const input, size_t mask, const MetaBlockSplit * const mb, size_t * const storage_ix, uint8_t * const storage, BlockEncoder distance_enc, size_t pos, const Command cmd)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  prev_byte2 = input[(pos - 2) & mask];
  prev_byte = input[(pos - 1) & mask];
  if (cmd.cmd_prefix_ >= 128)
  {
    size_t dist_code = cmd.dist_prefix_ & 0x3FF;
    uint32_t distnumextra = cmd.dist_prefix_ >> 10;
    uint64_t distextra = cmd.dist_extra_;
    if (mb->distance_context_map_size == 0)
    {
      StoreSymbol(&distance_enc, dist_code, storage_ix, storage);
    }
    else
    {
      size_t context = CommandDistanceContext(&cmd);
      StoreSymbolWithContext(&distance_enc, dist_code, context, mb->distance_context_map, storage_ix, storage, 2);
    }
    BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


/*** DEPENDENCIES:
static void StoreSymbolWithContext(BlockEncoder *self, size_t symbol, size_t context, const uint32_t *context_map, size_t *storage_ix, uint8_t *storage, const size_t context_bits)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = ((size_t) block_type) << context_bits;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t histo_ix = context_map[self->entropy_ix_ + context];
    size_t ix = (histo_ix * self->histogram_length_) + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}


----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
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
static void StoreSymbol(BlockEncoder *self, size_t symbol, size_t *storage_ix, uint8_t *storage)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = block_type * self->histogram_length_;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t ix = self->entropy_ix_ + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
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
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
inline static uint32_t CommandDistanceContext(const Command *self)
{
  uint32_t r = self->cmd_prefix_ >> 6;
  uint32_t c = self->cmd_prefix_ & 7;
  if (((((r == 0) || (r == 2)) || (r == 4)) || (r == 7)) && (c <= 2))
  {
    return c;
  }
  return 3;
}


----------------------------
***/


// hint:  ['prev_byte_ref is a mutable refrence to uint8_t', 'prev_byte2_ref is a mutable refrence to uint8_t', 'pos_ref is a mutable refrence to size_t']
void helper_BrotliStoreMetaBlock_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t * const pos_ref, const uint8_t * const input, size_t mask, const Command * const commands, const MetaBlockSplit * const mb, size_t * const storage_ix, uint8_t * const storage, size_t i, ContextLut literal_context_lut, BlockEncoder literal_enc, BlockEncoder command_enc, BlockEncoder distance_enc)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  size_t pos = *pos_ref;
  const Command cmd = commands[i];
  size_t cmd_code = cmd.cmd_prefix_;
  StoreSymbol(&command_enc, cmd_code, storage_ix, storage);
  StoreCommandExtra(&cmd, storage_ix, storage);
  if (mb->literal_context_map_size == 0)
  {
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      StoreSymbol(&literal_enc, input[pos & mask], storage_ix, storage);
      pos += 1;
    }

  }
  else
  {
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      size_t context = literal_context_lut[prev_byte] | (literal_context_lut + 256)[prev_byte2];
      uint8_t literal = input[pos & mask];
      StoreSymbolWithContext(&literal_enc, literal, context, mb->literal_context_map, storage_ix, storage, 6);
      prev_byte2 = prev_byte;
      prev_byte = literal;
      pos += 1;
    }

  }
  pos += CommandCopyLen(&cmd);
  if (CommandCopyLen(&cmd))
  {
    helper_helper_BrotliStoreMetaBlock_1_1(&prev_byte, &prev_byte2, input, mask, mb, storage_ix, storage, distance_enc, pos, cmd);
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
  *pos_ref = pos;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
static void StoreSymbolWithContext(BlockEncoder *self, size_t symbol, size_t context, const uint32_t *context_map, size_t *storage_ix, uint8_t *storage, const size_t context_bits)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = ((size_t) block_type) << context_bits;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t histo_ix = context_map[self->entropy_ix_ + context];
    size_t ix = (histo_ix * self->histogram_length_) + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}


----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
inline static void StoreCommandExtra(const Command *cmd, size_t *storage_ix, uint8_t *storage)
{
  uint32_t copylen_code = CommandCopyLenCode(cmd);
  uint16_t inscode = GetInsertLengthCode(cmd->insert_len_);
  uint16_t copycode = GetCopyLengthCode(copylen_code);
  uint32_t insnumextra = GetInsertExtra(inscode);
  uint64_t insextraval = cmd->insert_len_ - GetInsertBase(inscode);
  uint64_t copyextraval = copylen_code - GetCopyBase(copycode);
  uint64_t bits = (copyextraval << insnumextra) | insextraval;
  BrotliWriteBits(insnumextra + GetCopyExtra(copycode), bits, storage_ix, storage);
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
void helper_helper_BrotliStoreMetaBlock_1_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, const uint8_t * const input, size_t mask, const MetaBlockSplit * const mb, size_t * const storage_ix, uint8_t * const storage, BlockEncoder distance_enc, size_t pos, const Command cmd)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  prev_byte2 = input[(pos - 2) & mask];
  prev_byte = input[(pos - 1) & mask];
  if (cmd.cmd_prefix_ >= 128)
  {
    size_t dist_code = cmd.dist_prefix_ & 0x3FF;
    uint32_t distnumextra = cmd.dist_prefix_ >> 10;
    uint64_t distextra = cmd.dist_extra_;
    if (mb->distance_context_map_size == 0)
    {
      StoreSymbol(&distance_enc, dist_code, storage_ix, storage);
    }
    else
    {
      size_t context = CommandDistanceContext(&cmd);
      StoreSymbolWithContext(&distance_enc, dist_code, context, mb->distance_context_map, storage_ix, storage, 2);
    }
    BrotliWriteBits(distnumextra, distextra, storage_ix, storage);
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
static void StoreSymbol(BlockEncoder *self, size_t symbol, size_t *storage_ix, uint8_t *storage)
{
  if (self->block_len_ == 0)
  {
    size_t block_ix = ++self->block_ix_;
    uint32_t block_len = self->block_lengths_[block_ix];
    uint8_t block_type = self->block_types_[block_ix];
    self->block_len_ = block_len;
    self->entropy_ix_ = block_type * self->histogram_length_;
    StoreBlockSwitch(&self->block_split_code_, block_len, block_type, 0, storage_ix, storage);
  }
  self->block_len_ -= 1;
  {
    size_t ix = self->entropy_ix_ + symbol;
    BrotliWriteBits(self->depths_[ix], self->bits_[ix], storage_ix, storage);
  }
}


----------------------------
***/


static void StoreTrivialContextMap(size_t num_types, size_t context_bits, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  StoreVarLenUint8(num_types - 1, storage_ix, storage);
  if (num_types > 1)
  {
    size_t repeat_code = context_bits - 1u;
    size_t repeat_bits = (1u << repeat_code) - 1u;
    size_t alphabet_size = num_types + repeat_code;
    uint32_t histogram[256 + 16];
    uint8_t depths[256 + 16];
    uint16_t bits[256 + 16];
    size_t i;
    memset(histogram, 0, alphabet_size * (sizeof(histogram[0])));
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(4, repeat_code - 1, storage_ix, storage);
    histogram[repeat_code] = (uint32_t) num_types;
    histogram[0] = 1;
    for (i = context_bits; i < alphabet_size; i += 1)
    {
      histogram[i] = 1;
    }

    BuildAndStoreHuffmanTree(histogram, alphabet_size, alphabet_size, tree, depths, bits, storage_ix, storage);
    for (i = 0; i < num_types; i += 1)
    {
      size_t code = (i == 0) ? (0) : ((i + context_bits) - 1);
      BrotliWriteBits(depths[code], bits[code], storage_ix, storage);
      BrotliWriteBits(depths[repeat_code], bits[repeat_code], storage_ix, storage);
      BrotliWriteBits(repeat_code, repeat_bits, storage_ix, storage);
    }

    BrotliWriteBits(1, 1, storage_ix, storage);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void StoreVarLenUint8(size_t n, size_t *storage_ix, uint8_t *storage)
{
  if (n == 0)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  else
  {
    size_t nbits = Log2FloorNonZero(n);
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(3, nbits, storage_ix, storage);
    BrotliWriteBits(nbits, n - (((size_t) 1) << nbits), storage_ix, storage);
  }
}


----------------------------
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void BuildAndStoreEntropyCodesDistance(MemoryManager *m, BlockEncoder *self, const HistogramDistance *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
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
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
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
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void RunLengthCodeZeros(const size_t in_size, uint32_t * restrict v, size_t * restrict out_size, uint32_t * restrict max_run_length_prefix)
{
  uint32_t max_reps = 0;
  size_t i;
  uint32_t max_prefix;
  for (i = 0; i < in_size;)
  {
    uint32_t reps = 0;
    for (; (i < in_size) && (v[i] != 0); i += 1)
      ;

    for (; (i < in_size) && (v[i] == 0); i += 1)
    {
      reps += 1;
    }

    max_reps = brotli_max_uint32_t(reps, max_reps);
  }

  max_prefix = (max_reps > 0) ? (Log2FloorNonZero(max_reps)) : (0);
  max_prefix = brotli_min_uint32_t(max_prefix, *max_run_length_prefix);
  *max_run_length_prefix = max_prefix;
  *out_size = 0;
  for (i = 0; i < in_size;)
  {
    helper_RunLengthCodeZeros_1(&i, in_size, v, out_size, max_run_length_prefix, max_prefix);
  }

}


/*** DEPENDENCIES:
inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
void helper_RunLengthCodeZeros_1(size_t * const i_ref, const size_t in_size, uint32_t * const v, size_t * const out_size, uint32_t * const max_run_length_prefix, uint32_t max_prefix)
{
  size_t i = *i_ref;
  ;
  if (v[i] != 0)
  {
    v[*out_size] = v[i] + (*max_run_length_prefix);
    i += 1;
    *out_size += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < in_size) && (v[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    while (reps != 0)
    {
      if (reps < (2u << max_prefix))
      {
        uint32_t run_length_prefix = Log2FloorNonZero(reps);
        const uint32_t extra_bits = reps - (1u << run_length_prefix);
        v[*out_size] = run_length_prefix + (extra_bits << 9);
        *out_size += 1;
        break;
      }
      else
      {
        const uint32_t extra_bits = (1u << max_prefix) - 1u;
        v[*out_size] = max_prefix + (extra_bits << 9);
        reps -= (2u << max_prefix) - 1u;
        *out_size += 1;
      }
    }

  }
  *i_ref = i;
}


----------------------------
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


static void EncodeContextMap(MemoryManager *m, const uint32_t *context_map, size_t context_map_size, size_t num_clusters, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  size_t i;
  uint32_t *rle_symbols;
  unsigned int rle_symbols_idx = 0;
  uint32_t max_run_length_prefix = 6;
  size_t num_rle_symbols = 0;
  uint32_t histogram[256 + 16];
  static const uint32_t kSymbolMask = (1u << 9) - 1u;
  uint8_t depths[256 + 16];
  uint16_t bits[256 + 16];
  StoreVarLenUint8(num_clusters - 1, storage_ix, storage);
  if (num_clusters == 1)
  {
    return;
  }
  rle_symbols_idx = (context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  MoveToFrontTransform(context_map, context_map_size, rle_symbols);
  RunLengthCodeZeros(context_map_size, rle_symbols, &num_rle_symbols, &max_run_length_prefix);
  memset(histogram, 0, sizeof(histogram));
  for (i = 0; i < num_rle_symbols; i += 1)
  {
    histogram[rle_symbols[i + rle_symbols_idx] & kSymbolMask] += 1;
  }

  {
    int use_rle = (!(!(max_run_length_prefix > 0))) ? (1) : (0);
    BrotliWriteBits(1, (uint64_t) use_rle, storage_ix, storage);
    if (use_rle)
    {
      BrotliWriteBits(4, max_run_length_prefix - 1, storage_ix, storage);
    }
  }
  BuildAndStoreHuffmanTree(histogram, num_clusters + max_run_length_prefix, num_clusters + max_run_length_prefix, tree, depths, bits, storage_ix, storage);
  for (i = 0; i < num_rle_symbols; i += 1)
  {
    const uint32_t rle_symbol = rle_symbols[i + rle_symbols_idx] & kSymbolMask;
    const uint32_t extra_bits_val = rle_symbols[i + rle_symbols_idx] >> 9;
    BrotliWriteBits(depths[rle_symbol], bits[rle_symbol], storage_ix, storage);
    if ((rle_symbol > 0) && (rle_symbol <= max_run_length_prefix))
    {
      BrotliWriteBits(rle_symbol, extra_bits_val, storage_ix, storage);
    }
  }

  BrotliWriteBits(1, 1, storage_ix, storage);
  {
    BrotliFree(m, rle_symbols);
    rle_symbols_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
static void MoveToFrontTransform(const uint32_t * restrict v_in, const size_t v_size, uint32_t *v_out)
{
  size_t i;
  uint8_t mtf[256];
  uint32_t max_value;
  if (v_size == 0)
  {
    return;
  }
  max_value = v_in[0];
  for (i = 1; i < v_size; i += 1)
  {
    if (v_in[i] > max_value)
    {
      max_value = v_in[i];
    }
  }

  ;
  for (i = 0; i <= max_value; i += 1)
  {
    mtf[i] = (uint8_t) i;
  }

  {
    size_t mtf_size = max_value + 1;
    for (i = 0; i < v_size; i += 1)
    {
      size_t index = IndexOf(mtf, mtf_size, (uint8_t) v_in[i]);
      ;
      v_out[i] = (uint32_t) index;
      MoveToFront(mtf, index);
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
static void StoreVarLenUint8(size_t n, size_t *storage_ix, uint8_t *storage)
{
  if (n == 0)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  else
  {
    size_t nbits = Log2FloorNonZero(n);
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(3, nbits, storage_ix, storage);
    BrotliWriteBits(nbits, n - (((size_t) 1) << nbits), storage_ix, storage);
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
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void RunLengthCodeZeros(const size_t in_size, uint32_t * restrict v, size_t * restrict out_size, uint32_t * restrict max_run_length_prefix)
{
  uint32_t max_reps = 0;
  size_t i;
  uint32_t max_prefix;
  for (i = 0; i < in_size;)
  {
    uint32_t reps = 0;
    for (; (i < in_size) && (v[i] != 0); i += 1)
      ;

    for (; (i < in_size) && (v[i] == 0); i += 1)
    {
      reps += 1;
    }

    max_reps = brotli_max_uint32_t(reps, max_reps);
  }

  max_prefix = (max_reps > 0) ? (Log2FloorNonZero(max_reps)) : (0);
  max_prefix = brotli_min_uint32_t(max_prefix, *max_run_length_prefix);
  *max_run_length_prefix = max_prefix;
  *out_size = 0;
  for (i = 0; i < in_size;)
  {
    helper_RunLengthCodeZeros_1(&i, in_size, v, out_size, max_run_length_prefix, max_prefix);
  }

}


----------------------------
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void BuildAndStoreEntropyCodesLiteral(MemoryManager *m, BlockEncoder *self, const HistogramLiteral *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
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
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void BuildAndStoreEntropyCodesCommand(MemoryManager *m, BlockEncoder *self, const HistogramCommand *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
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
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void CleanupBlockEncoder(MemoryManager *m, BlockEncoder *self)
{
  {
    BrotliFree(m, self->depths_);
    self->depths_ = 0;
  }
  ;
  {
    BrotliFree(m, self->bits_);
    self->bits_ = 0;
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
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


static void BuildAndStoreBlockSplitCode(const uint8_t *types, const uint32_t *lengths, const size_t num_blocks, const size_t num_types, HuffmanTree *tree, BlockSplitCode *code, size_t *storage_ix, uint8_t *storage)
{
  uint32_t type_histo[256 + 2];
  uint32_t length_histo[26];
  size_t i;
  BlockTypeCodeCalculator type_code_calculator;
  memset(type_histo, 0, (num_types + 2) * (sizeof(type_histo[0])));
  memset(length_histo, 0, sizeof(length_histo));
  InitBlockTypeCodeCalculator(&type_code_calculator);
  for (i = 0; i < num_blocks; i += 1)
  {
    size_t type_code = NextBlockTypeCode(&type_code_calculator, types[i]);
    if (i != 0)
    {
      type_histo[type_code] += 1;
    }
    length_histo[BlockLengthPrefixCode(lengths[i])] += 1;
  }

  StoreVarLenUint8(num_types - 1, storage_ix, storage);
  if (num_types > 1)
  {
    BuildAndStoreHuffmanTree(&type_histo[0], num_types + 2, num_types + 2, tree, &code->type_depths[0], &code->type_bits[0], storage_ix, storage);
    BuildAndStoreHuffmanTree(&length_histo[0], 26, 26, tree, &code->length_depths[0], &code->length_bits[0], storage_ix, storage);
    StoreBlockSwitch(code, lengths[0], types[0], 1, storage_ix, storage);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
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
inline static void StoreBlockSwitch(BlockSplitCode *code, const uint32_t block_len, const uint8_t block_type, int is_first_block, size_t *storage_ix, uint8_t *storage)
{
  size_t typecode = NextBlockTypeCode(&code->type_code_calculator, block_type);
  size_t lencode;
  uint32_t len_nextra;
  uint32_t len_extra;
  if (!is_first_block)
  {
    BrotliWriteBits(code->type_depths[typecode], code->type_bits[typecode], storage_ix, storage);
  }
  GetBlockLengthPrefixCode(block_len, &lencode, &len_nextra, &len_extra);
  BrotliWriteBits(code->length_depths[lencode], code->length_bits[lencode], storage_ix, storage);
  BrotliWriteBits(len_nextra, len_extra, storage_ix, storage);
}


----------------------------
static void StoreVarLenUint8(size_t n, size_t *storage_ix, uint8_t *storage)
{
  if (n == 0)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  else
  {
    size_t nbits = Log2FloorNonZero(n);
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(3, nbits, storage_ix, storage);
    BrotliWriteBits(nbits, n - (((size_t) 1) << nbits), storage_ix, storage);
  }
}


----------------------------
typedef struct BlockSplitCode
{
  BlockTypeCodeCalculator type_code_calculator;
  uint8_t type_depths[256 + 2];
  uint16_t type_bits[256 + 2];
  uint8_t length_depths[26];
  uint16_t length_bits[26];
} BlockSplitCode
----------------------------
inline static uint32_t BlockLengthPrefixCode(uint32_t len)
{
  uint32_t code = (len >= 177) ? ((len >= 753) ? (20) : (14)) : ((len >= 41) ? (7) : (0));
  code += 1;
  code += 1;
  while ((code < (26 - 1)) && (len >= _kBrotliPrefixCodeRanges[code + 1].offset))
    ++code;

  return code;
}


----------------------------
inline static size_t NextBlockTypeCode(BlockTypeCodeCalculator *calculator, uint8_t type)
{
  size_t type_code = (type == (calculator->last_type + 1)) ? (1u) : ((type == calculator->second_last_type) ? (0u) : (type + 2u));
  calculator->second_last_type = calculator->last_type;
  calculator->last_type = type;
  return type_code;
}


----------------------------
static void InitBlockTypeCodeCalculator(BlockTypeCodeCalculator *self)
{
  self->last_type = 1;
  self->second_last_type = 0;
}


----------------------------
typedef struct BlockTypeCodeCalculator
{
  size_t last_type;
  size_t second_last_type;
} BlockTypeCodeCalculator
----------------------------
static void BuildAndStoreHuffmanTree(const uint32_t *histogram, const size_t histogram_length, const size_t alphabet_size, HuffmanTree *tree, uint8_t *depth, uint16_t *bits, size_t *storage_ix, uint8_t *storage)
{
  size_t count = 0;
  size_t s4[4] = {0};
  size_t i;
  size_t max_bits = 0;
  for (i = 0; i < histogram_length; i += 1)
  {
    if (histogram[i])
    {
      if (count < 4)
      {
        s4[count] = i;
      }
      else
        if (count > 4)
      {
        break;
      }
      count += 1;
    }
  }

  {
    size_t max_bits_counter = alphabet_size - 1;
    while (max_bits_counter)
    {
      max_bits_counter >>= 1;
      max_bits += 1;
    }

  }
  if (count <= 1)
  {
    BrotliWriteBits(4, 1, storage_ix, storage);
    BrotliWriteBits(max_bits, s4[0], storage_ix, storage);
    depth[s4[0]] = 0;
    bits[s4[0]] = 0;
    return;
  }
  memset(depth, 0, histogram_length * (sizeof(depth[0])));
  BrotliCreateHuffmanTree(histogram, histogram_length, 15, tree, depth);
  BrotliConvertBitDepthsToSymbols(depth, histogram_length, bits);
  if (count <= 4)
  {
    StoreSimpleHuffmanTree(depth, s4, count, max_bits, storage_ix, storage);
  }
  else
  {
    BrotliStoreHuffmanTree(depth, histogram_length, tree, storage_ix, storage);
  }
}


----------------------------
***/


static void BuildAndStoreBlockSwitchEntropyCodes(BlockEncoder *self, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  BuildAndStoreBlockSplitCode(self->block_types_, self->block_lengths_, self->num_blocks_, self->num_block_types_, tree, &self->block_split_code_, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
static void BuildAndStoreBlockSplitCode(const uint8_t *types, const uint32_t *lengths, const size_t num_blocks, const size_t num_types, HuffmanTree *tree, BlockSplitCode *code, size_t *storage_ix, uint8_t *storage)
{
  uint32_t type_histo[256 + 2];
  uint32_t length_histo[26];
  size_t i;
  BlockTypeCodeCalculator type_code_calculator;
  memset(type_histo, 0, (num_types + 2) * (sizeof(type_histo[0])));
  memset(length_histo, 0, sizeof(length_histo));
  InitBlockTypeCodeCalculator(&type_code_calculator);
  for (i = 0; i < num_blocks; i += 1)
  {
    size_t type_code = NextBlockTypeCode(&type_code_calculator, types[i]);
    if (i != 0)
    {
      type_histo[type_code] += 1;
    }
    length_histo[BlockLengthPrefixCode(lengths[i])] += 1;
  }

  StoreVarLenUint8(num_types - 1, storage_ix, storage);
  if (num_types > 1)
  {
    BuildAndStoreHuffmanTree(&type_histo[0], num_types + 2, num_types + 2, tree, &code->type_depths[0], &code->type_bits[0], storage_ix, storage);
    BuildAndStoreHuffmanTree(&length_histo[0], 26, 26, tree, &code->length_depths[0], &code->length_bits[0], storage_ix, storage);
    StoreBlockSwitch(code, lengths[0], types[0], 1, storage_ix, storage);
  }
}


----------------------------
***/


void BrotliStoreMetaBlock(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, int is_last, const BrotliEncoderParams *params, ContextType literal_context_mode, const Command *commands, size_t n_commands, const MetaBlockSplit *mb, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  uint32_t num_effective_distance_symbols = params->dist.alphabet_size_limit;
  HuffmanTree *tree;
  unsigned int tree_idx = 0;
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  BlockEncoder literal_enc;
  BlockEncoder command_enc;
  BlockEncoder distance_enc;
  const BrotliDistanceParams *dist = &params->dist;
  ;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  tree_idx = (((2 * 704) + 1) > 0) ? ((HuffmanTree *) BrotliAllocate(m, ((2 * 704) + 1) * (sizeof(HuffmanTree)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitBlockEncoder(&literal_enc, 256, mb->literal_split.num_types, mb->literal_split.types, mb->literal_split.lengths, mb->literal_split.num_blocks);
  InitBlockEncoder(&command_enc, 704, mb->command_split.num_types, mb->command_split.types, mb->command_split.lengths, mb->command_split.num_blocks);
  InitBlockEncoder(&distance_enc, num_effective_distance_symbols, mb->distance_split.num_types, mb->distance_split.types, mb->distance_split.lengths, mb->distance_split.num_blocks);
  BuildAndStoreBlockSwitchEntropyCodes(&literal_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&command_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&distance_enc, tree, storage_ix, storage);
  BrotliWriteBits(2, dist->distance_postfix_bits, storage_ix, storage);
  BrotliWriteBits(4, dist->num_direct_distance_codes >> dist->distance_postfix_bits, storage_ix, storage);
  for (i = 0; i < mb->literal_split.num_types; i += 1)
  {
    BrotliWriteBits(2, literal_context_mode, storage_ix, storage);
  }

  if (mb->literal_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->literal_histograms_size, 6, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->literal_context_map, mb->literal_context_map_size, mb->literal_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  if (mb->distance_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->distance_histograms_size, 2, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->distance_context_map, mb->distance_context_map_size, mb->distance_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  BuildAndStoreEntropyCodesLiteral(m, &literal_enc, mb->literal_histograms, mb->literal_histograms_size, 256, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesCommand(m, &command_enc, mb->command_histograms, mb->command_histograms_size, 704, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesDistance(m, &distance_enc, mb->distance_histograms, mb->distance_histograms_size, num_distance_symbols, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
  for (i = 0; i < n_commands; i += 1)
  {
    helper_BrotliStoreMetaBlock_1(&prev_byte, &prev_byte2, &pos, input, mask, commands, mb, storage_ix, storage, i, literal_context_lut, literal_enc, command_enc, distance_enc);
  }

  CleanupBlockEncoder(m, &distance_enc);
  CleanupBlockEncoder(m, &command_enc);
  CleanupBlockEncoder(m, &literal_enc);
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
void helper_BrotliStoreMetaBlock_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t * const pos_ref, const uint8_t * const input, size_t mask, const Command * const commands, const MetaBlockSplit * const mb, size_t * const storage_ix, uint8_t * const storage, size_t i, ContextLut literal_context_lut, BlockEncoder literal_enc, BlockEncoder command_enc, BlockEncoder distance_enc)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  size_t pos = *pos_ref;
  const Command cmd = commands[i];
  size_t cmd_code = cmd.cmd_prefix_;
  StoreSymbol(&command_enc, cmd_code, storage_ix, storage);
  StoreCommandExtra(&cmd, storage_ix, storage);
  if (mb->literal_context_map_size == 0)
  {
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      StoreSymbol(&literal_enc, input[pos & mask], storage_ix, storage);
      pos += 1;
    }

  }
  else
  {
    size_t j;
    for (j = cmd.insert_len_; j != 0; j -= 1)
    {
      size_t context = literal_context_lut[prev_byte] | (literal_context_lut + 256)[prev_byte2];
      uint8_t literal = input[pos & mask];
      StoreSymbolWithContext(&literal_enc, literal, context, mb->literal_context_map, storage_ix, storage, 6);
      prev_byte2 = prev_byte;
      prev_byte = literal;
      pos += 1;
    }

  }
  pos += CommandCopyLen(&cmd);
  if (CommandCopyLen(&cmd))
  {
    helper_helper_BrotliStoreMetaBlock_1_1(&prev_byte, &prev_byte2, input, mask, mb, storage_ix, storage, distance_enc, pos, cmd);
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
  *pos_ref = pos;
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
static void InitBlockEncoder(BlockEncoder *self, size_t histogram_length, size_t num_block_types, const uint8_t *block_types, const uint32_t *block_lengths, const size_t num_blocks)
{
  self->histogram_length_ = histogram_length;
  self->num_block_types_ = num_block_types;
  self->block_types_ = block_types;
  self->block_lengths_ = block_lengths;
  self->num_blocks_ = num_blocks;
  InitBlockTypeCodeCalculator(&self->block_split_code_.type_code_calculator);
  self->block_ix_ = 0;
  self->block_len_ = (num_blocks == 0) ? (0) : (block_lengths[0]);
  self->entropy_ix_ = 0;
  self->depths_ = 0;
  self->bits_ = 0;
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
static void StoreTrivialContextMap(size_t num_types, size_t context_bits, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  StoreVarLenUint8(num_types - 1, storage_ix, storage);
  if (num_types > 1)
  {
    size_t repeat_code = context_bits - 1u;
    size_t repeat_bits = (1u << repeat_code) - 1u;
    size_t alphabet_size = num_types + repeat_code;
    uint32_t histogram[256 + 16];
    uint8_t depths[256 + 16];
    uint16_t bits[256 + 16];
    size_t i;
    memset(histogram, 0, alphabet_size * (sizeof(histogram[0])));
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(4, repeat_code - 1, storage_ix, storage);
    histogram[repeat_code] = (uint32_t) num_types;
    histogram[0] = 1;
    for (i = context_bits; i < alphabet_size; i += 1)
    {
      histogram[i] = 1;
    }

    BuildAndStoreHuffmanTree(histogram, alphabet_size, alphabet_size, tree, depths, bits, storage_ix, storage);
    for (i = 0; i < num_types; i += 1)
    {
      size_t code = (i == 0) ? (0) : ((i + context_bits) - 1);
      BrotliWriteBits(depths[code], bits[code], storage_ix, storage);
      BrotliWriteBits(depths[repeat_code], bits[repeat_code], storage_ix, storage);
      BrotliWriteBits(repeat_code, repeat_bits, storage_ix, storage);
    }

    BrotliWriteBits(1, 1, storage_ix, storage);
  }
}


----------------------------
static void BuildAndStoreEntropyCodesDistance(MemoryManager *m, BlockEncoder *self, const HistogramDistance *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

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
static void EncodeContextMap(MemoryManager *m, const uint32_t *context_map, size_t context_map_size, size_t num_clusters, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  size_t i;
  uint32_t *rle_symbols;
  unsigned int rle_symbols_idx = 0;
  uint32_t max_run_length_prefix = 6;
  size_t num_rle_symbols = 0;
  uint32_t histogram[256 + 16];
  static const uint32_t kSymbolMask = (1u << 9) - 1u;
  uint8_t depths[256 + 16];
  uint16_t bits[256 + 16];
  StoreVarLenUint8(num_clusters - 1, storage_ix, storage);
  if (num_clusters == 1)
  {
    return;
  }
  rle_symbols_idx = (context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  MoveToFrontTransform(context_map, context_map_size, rle_symbols);
  RunLengthCodeZeros(context_map_size, rle_symbols, &num_rle_symbols, &max_run_length_prefix);
  memset(histogram, 0, sizeof(histogram));
  for (i = 0; i < num_rle_symbols; i += 1)
  {
    histogram[rle_symbols[i + rle_symbols_idx] & kSymbolMask] += 1;
  }

  {
    int use_rle = (!(!(max_run_length_prefix > 0))) ? (1) : (0);
    BrotliWriteBits(1, (uint64_t) use_rle, storage_ix, storage);
    if (use_rle)
    {
      BrotliWriteBits(4, max_run_length_prefix - 1, storage_ix, storage);
    }
  }
  BuildAndStoreHuffmanTree(histogram, num_clusters + max_run_length_prefix, num_clusters + max_run_length_prefix, tree, depths, bits, storage_ix, storage);
  for (i = 0; i < num_rle_symbols; i += 1)
  {
    const uint32_t rle_symbol = rle_symbols[i + rle_symbols_idx] & kSymbolMask;
    const uint32_t extra_bits_val = rle_symbols[i + rle_symbols_idx] >> 9;
    BrotliWriteBits(depths[rle_symbol], bits[rle_symbol], storage_ix, storage);
    if ((rle_symbol > 0) && (rle_symbol <= max_run_length_prefix))
    {
      BrotliWriteBits(rle_symbol, extra_bits_val, storage_ix, storage);
    }
  }

  BrotliWriteBits(1, 1, storage_ix, storage);
  {
    BrotliFree(m, rle_symbols);
    rle_symbols_idx = 0;
  }
  ;
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
extern const uint8_t _kBrotliContextLookupTable[2048]
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
static void BuildAndStoreEntropyCodesLiteral(MemoryManager *m, BlockEncoder *self, const HistogramLiteral *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

  }
}


----------------------------
typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
----------------------------
static void StoreCompressedMetaBlockHeader(int is_final_block, size_t length, size_t *storage_ix, uint8_t *storage)
{
  uint64_t lenbits;
  size_t nlenbits;
  uint64_t nibblesbits;
  BrotliWriteBits(1, (uint64_t) is_final_block, storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
  BrotliEncodeMlen(length, &lenbits, &nlenbits, &nibblesbits);
  BrotliWriteBits(2, nibblesbits, storage_ix, storage);
  BrotliWriteBits(nlenbits, lenbits, storage_ix, storage);
  if (!is_final_block)
  {
    BrotliWriteBits(1, 0, storage_ix, storage);
  }
}


----------------------------
static void BuildAndStoreEntropyCodesCommand(MemoryManager *m, BlockEncoder *self, const HistogramCommand *histograms, const size_t histograms_size, const size_t alphabet_size, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  const size_t table_size = histograms_size * self->histogram_length_;
  self->depths_ = (table_size > 0) ? ((uint8_t *) BrotliAllocate(m, table_size * (sizeof(uint8_t)))) : (0);
  self->bits_ = (table_size > 0) ? ((uint16_t *) BrotliAllocate(m, table_size * (sizeof(uint16_t)))) : (0);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; i < histograms_size; i += 1)
    {
      size_t ix = i * self->histogram_length_;
      BuildAndStoreHuffmanTree(&histograms[i].data_[0], self->histogram_length_, alphabet_size, tree, &self->depths_[ix], &self->bits_[ix], storage_ix, storage);
    }

  }
}


----------------------------
static void CleanupBlockEncoder(MemoryManager *m, BlockEncoder *self)
{
  {
    BrotliFree(m, self->depths_);
    self->depths_ = 0;
  }
  ;
  {
    BrotliFree(m, self->bits_);
    self->bits_ = 0;
  }
  ;
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
static void BuildAndStoreBlockSwitchEntropyCodes(BlockEncoder *self, HuffmanTree *tree, size_t *storage_ix, uint8_t *storage)
{
  BuildAndStoreBlockSplitCode(self->block_types_, self->block_lengths_, self->num_blocks_, self->num_block_types_, tree, &self->block_split_code_, storage_ix, storage);
}


----------------------------
static void JumpToByteBoundary(size_t *storage_ix, uint8_t *storage)
{
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
None
----------------------------
***/


