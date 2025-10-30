static void RewindBitPosition(const size_t new_storage_ix, size_t *storage_ix, uint8_t *storage)
{
  const size_t bitpos = new_storage_ix & 7;
  const size_t mask = (1u << bitpos) - 1;
  storage[new_storage_ix >> 3] &= (uint8_t) mask;
  *storage_ix = new_storage_ix;
}


/*** DEPENDENCIES:
***/


inline static int ShouldUseUncompressedMode(const uint8_t *metablock_start, const uint8_t *next_emit, const size_t insertlen, const size_t literal_ratio)
{
  const size_t compressed = (size_t) (next_emit - metablock_start);
  if ((compressed * 50) > insertlen)
  {
    return 0;
  }
  else
  {
    return (!(!(literal_ratio > 980))) ? (1) : (0);
  }
}


/*** DEPENDENCIES:
***/


inline static uint32_t HashBytesAtOffset(uint64_t v, int offset, size_t shift)
{
  ;
  ;
  {
    const uint64_t h = ((v >> (8 * offset)) << 24) * kHashMul32;
    return (uint32_t) (h >> shift);
  }
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
***/


inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


/*** DEPENDENCIES:
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


inline static void EmitLongInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 22594)
  {
    BrotliWriteBits(depth[62], bits[62], storage_ix, storage);
    BrotliWriteBits(14, insertlen - 6210, storage_ix, storage);
    histo[62] += 1;
  }
  else
  {
    BrotliWriteBits(depth[63], bits[63], storage_ix, storage);
    BrotliWriteBits(24, insertlen - 22594, storage_ix, storage);
    histo[63] += 1;
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


inline static void EmitLiterals(const uint8_t *input, const size_t len, const uint8_t depth[256], const uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  size_t j;
  for (j = 0; j < len; j += 1)
  {
    const uint8_t lit = input[j];
    BrotliWriteBits(depth[lit], bits[lit], storage_ix, storage);
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


static void BrotliStoreMetaBlockHeader(size_t len, int is_uncompressed, size_t *storage_ix, uint8_t *storage)
{
  size_t nibbles = 6;
  BrotliWriteBits(1, 0, storage_ix, storage);
  if (len <= (1U << 16))
  {
    nibbles = 4;
  }
  else
    if (len <= (1U << 20))
  {
    nibbles = 5;
  }
  BrotliWriteBits(2, nibbles - 4, storage_ix, storage);
  BrotliWriteBits(nibbles * 4, len - 1, storage_ix, storage);
  BrotliWriteBits(1, (uint64_t) is_uncompressed, storage_ix, storage);
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


static void UpdateBits(size_t n_bits, uint32_t bits, size_t pos, uint8_t *array)
{
  while (n_bits > 0)
  {
    size_t byte_pos = pos >> 3;
    size_t n_unchanged_bits = pos & 7;
    size_t n_changed_bits = brotli_min_size_t(n_bits, 8 - n_unchanged_bits);
    size_t total_bits = n_unchanged_bits + n_changed_bits;
    uint32_t mask = (~((1u << total_bits) - 1u)) | ((1u << n_unchanged_bits) - 1u);
    uint32_t unchanged_bits = array[byte_pos] & mask;
    uint32_t changed_bits = bits & ((1u << n_changed_bits) - 1u);
    array[byte_pos] = (uint8_t) ((changed_bits << n_unchanged_bits) | unchanged_bits);
    n_bits -= n_changed_bits;
    bits >>= n_changed_bits;
    pos += n_changed_bits;
  }

}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static int ShouldMergeBlock(const uint8_t *data, size_t len, const uint8_t *depths)
{
  size_t histo[256] = {0};
  static const size_t kSampleRate = 43;
  size_t i;
  for (i = 0; i < len; i += kSampleRate)
  {
    histo[data[i]] += 1;
  }

  {
    const size_t total = ((len + kSampleRate) - 1) / kSampleRate;
    double r = ((FastLog2(total) + 0.5) * ((double) total)) + 200;
    for (i = 0; i < 256; i += 1)
    {
      r -= ((double) histo[i]) * (depths[i] + FastLog2(histo[i]));
    }

    return (!(!(r >= 0.0))) ? (1) : (0);
  }
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


inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
***/


inline static void EmitInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 6)
  {
    const size_t code = insertlen + 40;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (insertlen < 130)
  {
    const size_t tail = insertlen - 2;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1u;
    const size_t prefix = tail >> nbits;
    const size_t inscode = ((nbits << 1) + prefix) + 42;
    BrotliWriteBits(depth[inscode], bits[inscode], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[inscode] += 1;
  }
  else
    if (insertlen < 2114)
  {
    const size_t tail = insertlen - 66;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 50;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
  {
    BrotliWriteBits(depth[61], bits[61], storage_ix, storage);
    BrotliWriteBits(12, insertlen - 2114, storage_ix, storage);
    histo[61] += 1;
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


inline static void EmitCopyLen(size_t copylen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (copylen < 10)
  {
    BrotliWriteBits(depth[copylen + 14], bits[copylen + 14], storage_ix, storage);
    histo[copylen + 14] += 1;
  }
  else
    if (copylen < 134)
  {
    const size_t tail = copylen - 6;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1u;
    const size_t prefix = tail >> nbits;
    const size_t code = ((nbits << 1) + prefix) + 20;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (copylen < 2118)
  {
    const size_t tail = copylen - 70;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 28;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
  {
    BrotliWriteBits(depth[39], bits[39], storage_ix, storage);
    BrotliWriteBits(24, copylen - 2118, storage_ix, storage);
    histo[39] += 1;
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


inline static void EmitCopyLenLastDistance(size_t copylen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (copylen < 12)
  {
    BrotliWriteBits(depth[copylen - 4], bits[copylen - 4], storage_ix, storage);
    histo[copylen - 4] += 1;
  }
  else
    if (copylen < 72)
  {
    const size_t tail = copylen - 8;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1;
    const size_t prefix = tail >> nbits;
    const size_t code = ((nbits << 1) + prefix) + 4;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (copylen < 136)
  {
    const size_t tail = copylen - 8;
    const size_t code = (tail >> 5) + 30;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(5, tail & 31, storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[code] += 1;
    histo[64] += 1;
  }
  else
    if (copylen < 2120)
  {
    const size_t tail = copylen - 72;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 28;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[code] += 1;
    histo[64] += 1;
  }
  else
  {
    BrotliWriteBits(depth[39], bits[39], storage_ix, storage);
    BrotliWriteBits(24, copylen - 2120, storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[39] += 1;
    histo[64] += 1;
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


inline static void EmitDistance(size_t distance, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  const size_t d = distance + 3;
  const uint32_t nbits = Log2FloorNonZero(d) - 1u;
  const size_t prefix = (d >> nbits) & 1;
  const size_t offset = (2 + prefix) << nbits;
  const size_t distcode = ((2 * (nbits - 1)) + prefix) + 80;
  BrotliWriteBits(depth[distcode], bits[distcode], storage_ix, storage);
  BrotliWriteBits(nbits, d - offset, storage_ix, storage);
  histo[distcode] += 1;
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


static void EmitUncompressedMetaBlock(const uint8_t *begin, const uint8_t *end, const size_t storage_ix_start, size_t *storage_ix, uint8_t *storage)
{
  const size_t len = (size_t) (end - begin);
  RewindBitPosition(storage_ix_start, storage_ix, storage);
  BrotliStoreMetaBlockHeader(len, 1, storage_ix, storage);
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  memcpy(&storage[(*storage_ix) >> 3], begin, len);
  *storage_ix += len << 3;
  storage[(*storage_ix) >> 3] = 0;
}


/*** DEPENDENCIES:
static void BrotliStoreMetaBlockHeader(size_t len, int is_uncompressed, size_t *storage_ix, uint8_t *storage)
{
  size_t nibbles = 6;
  BrotliWriteBits(1, 0, storage_ix, storage);
  if (len <= (1U << 16))
  {
    nibbles = 4;
  }
  else
    if (len <= (1U << 20))
  {
    nibbles = 5;
  }
  BrotliWriteBits(2, nibbles - 4, storage_ix, storage);
  BrotliWriteBits(nibbles * 4, len - 1, storage_ix, storage);
  BrotliWriteBits(1, (uint64_t) is_uncompressed, storage_ix, storage);
}


----------------------------
static void RewindBitPosition(const size_t new_storage_ix, size_t *storage_ix, uint8_t *storage)
{
  const size_t bitpos = new_storage_ix & 7;
  const size_t mask = (1u << bitpos) - 1;
  storage[new_storage_ix >> 3] &= (uint8_t) mask;
  *storage_ix = new_storage_ix;
}


----------------------------
***/


static size_t BuildAndStoreLiteralPrefixCode(MemoryManager *m, const uint8_t *input, const size_t input_size, uint8_t depths[256], uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  uint32_t histogram[256] = {0};
  size_t histogram_total;
  size_t i;
  if (input_size < (1 << 15))
  {
    for (i = 0; i < input_size; i += 1)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = input_size;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 2 * brotli_min_uint32_t(histogram[i], 11u);
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  else
  {
    static const size_t kSampleRate = 29;
    for (i = 0; i < input_size; i += kSampleRate)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = ((input_size + kSampleRate) - 1) / kSampleRate;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 1 + (2 * brotli_min_uint32_t(histogram[i], 11u));
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  BrotliBuildAndStoreHuffmanTreeFast(m, histogram, histogram_total, 8, depths, bits, storage_ix, storage);
  if (!(!0))
  {
    return 0;
  }
  {
    size_t literal_ratio = 0;
    for (i = 0; i < 256; i += 1)
    {
      if (histogram[i])
      {
        literal_ratio += histogram[i] * depths[i];
      }
    }

    return (literal_ratio * 125) / histogram_total;
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
inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


void helper_BuildAndStoreCommandPrefixCode_1(uint8_t depth[128], size_t * const storage_ix, uint8_t * const storage, HuffmanTree tree[129], uint8_t cmd_depth[704])
{
  size_t i;
  memset(cmd_depth, 0, 64);
  memcpy(cmd_depth, depth, 8);
  memcpy(cmd_depth + 64, depth + 8, 8);
  memcpy(cmd_depth + 128, depth + 16, 8);
  memcpy(cmd_depth + 192, depth + 24, 8);
  memcpy(cmd_depth + 384, depth + 32, 8);
  for (i = 0; i < 8; i += 1)
  {
    cmd_depth[128 + (8 * i)] = depth[40 + i];
    cmd_depth[256 + (8 * i)] = depth[48 + i];
    cmd_depth[448 + (8 * i)] = depth[56 + i];
  }

  BrotliStoreHuffmanTree(cmd_depth, 704, tree, storage_ix, storage);
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
***/


static void BuildAndStoreCommandPrefixCode(const uint32_t histogram[128], uint8_t depth[128], uint16_t bits[128], size_t *storage_ix, uint8_t *storage)
{
  HuffmanTree tree[129];
  uint8_t cmd_depth[704] = {0};
  uint16_t cmd_bits[64];
  BrotliCreateHuffmanTree(histogram, 64, 15, tree, depth);
  BrotliCreateHuffmanTree(&histogram[64], 64, 14, tree, &depth[64]);
  memcpy(cmd_depth, depth, 24);
  memcpy(cmd_depth + 24, depth + 40, 8);
  memcpy(cmd_depth + 32, depth + 24, 8);
  memcpy(cmd_depth + 40, depth + 48, 8);
  memcpy(cmd_depth + 48, depth + 32, 8);
  memcpy(cmd_depth + 56, depth + 56, 8);
  BrotliConvertBitDepthsToSymbols(cmd_depth, 64, cmd_bits);
  memcpy(bits, cmd_bits, 48);
  memcpy(bits + 24, cmd_bits + 32, 16);
  memcpy(bits + 32, cmd_bits + 48, 16);
  memcpy(bits + 40, cmd_bits + 24, 16);
  memcpy(bits + 48, cmd_bits + 40, 16);
  memcpy(bits + 56, cmd_bits + 56, 16);
  BrotliConvertBitDepthsToSymbols(&depth[64], 64, &bits[64]);
  {
    helper_BuildAndStoreCommandPrefixCode_1(depth, storage_ix, storage, tree, cmd_depth);
  }
  BrotliStoreHuffmanTree(&depth[64], 64, tree, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree
----------------------------
void helper_BuildAndStoreCommandPrefixCode_1(uint8_t depth[128], size_t * const storage_ix, uint8_t * const storage, HuffmanTree tree[129], uint8_t cmd_depth[704])
{
  size_t i;
  memset(cmd_depth, 0, 64);
  memcpy(cmd_depth, depth, 8);
  memcpy(cmd_depth + 64, depth + 8, 8);
  memcpy(cmd_depth + 128, depth + 16, 8);
  memcpy(cmd_depth + 192, depth + 24, 8);
  memcpy(cmd_depth + 384, depth + 32, 8);
  for (i = 0; i < 8; i += 1)
  {
    cmd_depth[128 + (8 * i)] = depth[40 + i];
    cmd_depth[256 + (8 * i)] = depth[48 + i];
    cmd_depth[448 + (8 * i)] = depth[56 + i];
  }

  BrotliStoreHuffmanTree(cmd_depth, 704, tree, storage_ix, storage);
}


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


// hint:  ['metablock_start_idx_ref is a mutable refrence to unsigned int', 'block_size_ref is a mutable refrence to size_t', 'total_block_size_ref is a mutable refrence to size_t', 'mlen_storage_ix_ref is a mutable refrence to size_t', 'literal_ratio_ref is a mutable refrence to size_t']
void helper_BrotliCompressFragmentFastImpl_1(unsigned int * const metablock_start_idx_ref, size_t * const block_size_ref, size_t * const total_block_size_ref, size_t * const mlen_storage_ix_ref, size_t * const literal_ratio_ref, MemoryManager * const m, const uint8_t * const input, size_t input_size, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, unsigned int input_idx, uint32_t cmd_histo[128], static const size_t kFirstBlockSize, uint8_t lit_depth[256], uint16_t lit_bits[256])
{
  unsigned int metablock_start_idx = *metablock_start_idx_ref;
  size_t block_size = *block_size_ref;
  size_t total_block_size = *total_block_size_ref;
  size_t mlen_storage_ix = *mlen_storage_ix_ref;
  size_t literal_ratio = *literal_ratio_ref;
  metablock_start_idx = &input[input_idx];
  block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  total_block_size = block_size;
  mlen_storage_ix = (*storage_ix) + 3;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, storage_ix, storage);
  goto emit_commands;
  *metablock_start_idx_ref = metablock_start_idx;
  *block_size_ref = block_size;
  *total_block_size_ref = total_block_size;
  *mlen_storage_ix_ref = mlen_storage_ix;
  *literal_ratio_ref = literal_ratio;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static size_t BuildAndStoreLiteralPrefixCode(MemoryManager *m, const uint8_t *input, const size_t input_size, uint8_t depths[256], uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  uint32_t histogram[256] = {0};
  size_t histogram_total;
  size_t i;
  if (input_size < (1 << 15))
  {
    for (i = 0; i < input_size; i += 1)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = input_size;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 2 * brotli_min_uint32_t(histogram[i], 11u);
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  else
  {
    static const size_t kSampleRate = 29;
    for (i = 0; i < input_size; i += kSampleRate)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = ((input_size + kSampleRate) - 1) / kSampleRate;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 1 + (2 * brotli_min_uint32_t(histogram[i], 11u));
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  BrotliBuildAndStoreHuffmanTreeFast(m, histogram, histogram_total, 8, depths, bits, storage_ix, storage);
  if (!(!0))
  {
    return 0;
  }
  {
    size_t literal_ratio = 0;
    for (i = 0; i < 256; i += 1)
    {
      if (histogram[i])
      {
        literal_ratio += histogram[i] * depths[i];
      }
    }

    return (literal_ratio * 125) / histogram_total;
  }
}


----------------------------
static void BuildAndStoreCommandPrefixCode(const uint32_t histogram[128], uint8_t depth[128], uint16_t bits[128], size_t *storage_ix, uint8_t *storage)
{
  HuffmanTree tree[129];
  uint8_t cmd_depth[704] = {0};
  uint16_t cmd_bits[64];
  BrotliCreateHuffmanTree(histogram, 64, 15, tree, depth);
  BrotliCreateHuffmanTree(&histogram[64], 64, 14, tree, &depth[64]);
  memcpy(cmd_depth, depth, 24);
  memcpy(cmd_depth + 24, depth + 40, 8);
  memcpy(cmd_depth + 32, depth + 24, 8);
  memcpy(cmd_depth + 40, depth + 48, 8);
  memcpy(cmd_depth + 48, depth + 32, 8);
  memcpy(cmd_depth + 56, depth + 56, 8);
  BrotliConvertBitDepthsToSymbols(cmd_depth, 64, cmd_bits);
  memcpy(bits, cmd_bits, 48);
  memcpy(bits + 24, cmd_bits + 32, 16);
  memcpy(bits + 32, cmd_bits + 48, 16);
  memcpy(bits + 40, cmd_bits + 24, 16);
  memcpy(bits + 48, cmd_bits + 40, 16);
  memcpy(bits + 56, cmd_bits + 56, 16);
  BrotliConvertBitDepthsToSymbols(&depth[64], 64, &bits[64]);
  {
    helper_BuildAndStoreCommandPrefixCode_1(depth, storage_ix, storage, tree, cmd_depth);
  }
  BrotliStoreHuffmanTree(&depth[64], 64, tree, storage_ix, storage);
}


----------------------------
static void BrotliStoreMetaBlockHeader(size_t len, int is_uncompressed, size_t *storage_ix, uint8_t *storage)
{
  size_t nibbles = 6;
  BrotliWriteBits(1, 0, storage_ix, storage);
  if (len <= (1U << 16))
  {
    nibbles = 4;
  }
  else
    if (len <= (1U << 20))
  {
    nibbles = 5;
  }
  BrotliWriteBits(2, nibbles - 4, storage_ix, storage);
  BrotliWriteBits(nibbles * 4, len - 1, storage_ix, storage);
  BrotliWriteBits(1, (uint64_t) is_uncompressed, storage_ix, storage);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
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


// hint:  ['next_emit_idx_ref is a mutable refrence to unsigned int', 'ip_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_2(unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const base_ip, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = 5 + FindMatchLengthWithLimit((&candidate[candidate_idx]) + 5, (&ip[ip_idx]) + 5, ((size_t) ((&ip_end[ip_end_idx]) - (&ip[ip_idx]))) - 5);
  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    break;
  }
  ip_idx += matched;
  last_distance = (int) (base - (&candidate[candidate_idx]));
  ;
  EmitCopyLen(matched, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  EmitDistance((size_t) last_distance, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    uint64_t input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    uint32_t prev_hash = HashBytesAtOffset(input_bytes, 0, shift);
    uint32_t cur_hash = HashBytesAtOffset(input_bytes, 3, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
    candidate_idx = base_ip + table[cur_hash];
    table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  }
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
inline static uint32_t HashBytesAtOffset(uint64_t v, int offset, size_t shift)
{
  ;
  ;
  {
    const uint64_t h = ((v >> (8 * offset)) << 24) * kHashMul32;
    return (uint32_t) (h >> shift);
  }
}


----------------------------
inline static void EmitDistance(size_t distance, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  const size_t d = distance + 3;
  const uint32_t nbits = Log2FloorNonZero(d) - 1u;
  const size_t prefix = (d >> nbits) & 1;
  const size_t offset = (2 + prefix) << nbits;
  const size_t distcode = ((2 * (nbits - 1)) + prefix) + 80;
  BrotliWriteBits(depth[distcode], bits[distcode], storage_ix, storage);
  BrotliWriteBits(nbits, d - offset, storage_ix, storage);
  histo[distcode] += 1;
}


----------------------------
inline static size_t FindMatchLengthWithLimit(const uint8_t *s1, const uint8_t *s2, size_t limit)
{
  unsigned int s2_idx = 0;
  size_t matched = 0;
  size_t limit2 = (limit >> 3) + 1;
  while (__builtin_expect(!(!(--limit2)), 1))
  {
    if (__builtin_expect(BrotliUnalignedRead64(s2) == BrotliUnalignedRead64(s1 + matched), 0))
    {
      s2_idx += 8;
      matched += 8;
    }
    else
    {
      uint64_t x = BrotliUnalignedRead64(s2) ^ BrotliUnalignedRead64(s1 + matched);
      size_t matching_bits = (size_t) __builtin_ctzll(x);
      matched += matching_bits >> 3;
      return matched;
    }
  }

  limit = (limit & 7) + 1;
  while (--limit)
  {
    if (__builtin_expect(!(!(s1[matched] == (*(&s2[s2_idx])))), 1))
    {
      s2_idx += 1;
      matched += 1;
    }
    else
    {
      return matched;
    }
  }

  return matched;
}


----------------------------
inline static void EmitCopyLen(size_t copylen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (copylen < 10)
  {
    BrotliWriteBits(depth[copylen + 14], bits[copylen + 14], storage_ix, storage);
    histo[copylen + 14] += 1;
  }
  else
    if (copylen < 134)
  {
    const size_t tail = copylen - 6;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1u;
    const size_t prefix = tail >> nbits;
    const size_t code = ((nbits << 1) + prefix) + 20;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (copylen < 2118)
  {
    const size_t tail = copylen - 70;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 28;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
  {
    BrotliWriteBits(depth[39], bits[39], storage_ix, storage);
    BrotliWriteBits(24, copylen - 2118, storage_ix, storage);
    histo[39] += 1;
  }
}


----------------------------
***/


// hint:  ['input_size_ref is a mutable refrence to size_t', 'input_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'ip_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_3(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const uint8_t * const metablock_start, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = 5 + FindMatchLengthWithLimit((&candidate[candidate_idx]) + 5, (&ip[ip_idx]) + 5, ((size_t) ((&ip_end[ip_end_idx]) - (&ip[ip_idx]))) - 5);
  int distance = (int) (base - (&candidate[candidate_idx]));
  size_t insert = (size_t) (base - (&next_emit[next_emit_idx]));
  ip_idx += matched;
  ;
  if (__builtin_expect(!(!(insert < 6210)), 1))
  {
    EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  }
  else
    if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
  {
    EmitUncompressedMetaBlock(metablock_start, base, mlen_storage_ix - 3, storage_ix, storage);
    input_size -= (size_t) (base - (&input[input_idx]));
    input_idx = base;
    next_emit_idx = &input[input_idx];
    goto next_block;
  }
  else
  {
    EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  }
  EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
  if (distance == last_distance)
  {
    BrotliWriteBits(cmd_depth[64], cmd_bits[64], storage_ix, storage);
    cmd_histo[64] += 1;
  }
  else
  {
    EmitDistance((size_t) distance, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
    last_distance = distance;
  }
  EmitCopyLenLastDistance(matched, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    uint64_t input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    uint32_t prev_hash = HashBytesAtOffset(input_bytes, 0, shift);
    uint32_t cur_hash = HashBytesAtOffset(input_bytes, 3, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
    candidate_idx = base_ip + table[cur_hash];
    table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  }
  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


/*** DEPENDENCIES:
inline static void EmitCopyLenLastDistance(size_t copylen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (copylen < 12)
  {
    BrotliWriteBits(depth[copylen - 4], bits[copylen - 4], storage_ix, storage);
    histo[copylen - 4] += 1;
  }
  else
    if (copylen < 72)
  {
    const size_t tail = copylen - 8;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1;
    const size_t prefix = tail >> nbits;
    const size_t code = ((nbits << 1) + prefix) + 4;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (copylen < 136)
  {
    const size_t tail = copylen - 8;
    const size_t code = (tail >> 5) + 30;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(5, tail & 31, storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[code] += 1;
    histo[64] += 1;
  }
  else
    if (copylen < 2120)
  {
    const size_t tail = copylen - 72;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 28;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[code] += 1;
    histo[64] += 1;
  }
  else
  {
    BrotliWriteBits(depth[39], bits[39], storage_ix, storage);
    BrotliWriteBits(24, copylen - 2120, storage_ix, storage);
    BrotliWriteBits(depth[64], bits[64], storage_ix, storage);
    histo[39] += 1;
    histo[64] += 1;
  }
}


----------------------------
inline static void EmitLongInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 22594)
  {
    BrotliWriteBits(depth[62], bits[62], storage_ix, storage);
    BrotliWriteBits(14, insertlen - 6210, storage_ix, storage);
    histo[62] += 1;
  }
  else
  {
    BrotliWriteBits(depth[63], bits[63], storage_ix, storage);
    BrotliWriteBits(24, insertlen - 22594, storage_ix, storage);
    histo[63] += 1;
  }
}


----------------------------
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
inline static uint32_t HashBytesAtOffset(uint64_t v, int offset, size_t shift)
{
  ;
  ;
  {
    const uint64_t h = ((v >> (8 * offset)) << 24) * kHashMul32;
    return (uint32_t) (h >> shift);
  }
}


----------------------------
inline static void EmitLiterals(const uint8_t *input, const size_t len, const uint8_t depth[256], const uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  size_t j;
  for (j = 0; j < len; j += 1)
  {
    const uint8_t lit = input[j];
    BrotliWriteBits(depth[lit], bits[lit], storage_ix, storage);
  }

}


----------------------------
inline static void EmitDistance(size_t distance, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  const size_t d = distance + 3;
  const uint32_t nbits = Log2FloorNonZero(d) - 1u;
  const size_t prefix = (d >> nbits) & 1;
  const size_t offset = (2 + prefix) << nbits;
  const size_t distcode = ((2 * (nbits - 1)) + prefix) + 80;
  BrotliWriteBits(depth[distcode], bits[distcode], storage_ix, storage);
  BrotliWriteBits(nbits, d - offset, storage_ix, storage);
  histo[distcode] += 1;
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
static void EmitUncompressedMetaBlock(const uint8_t *begin, const uint8_t *end, const size_t storage_ix_start, size_t *storage_ix, uint8_t *storage)
{
  const size_t len = (size_t) (end - begin);
  RewindBitPosition(storage_ix_start, storage_ix, storage);
  BrotliStoreMetaBlockHeader(len, 1, storage_ix, storage);
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  memcpy(&storage[(*storage_ix) >> 3], begin, len);
  *storage_ix += len << 3;
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
inline static int ShouldUseUncompressedMode(const uint8_t *metablock_start, const uint8_t *next_emit, const size_t insertlen, const size_t literal_ratio)
{
  const size_t compressed = (size_t) (next_emit - metablock_start);
  if ((compressed * 50) > insertlen)
  {
    return 0;
  }
  else
  {
    return (!(!(literal_ratio > 980))) ? (1) : (0);
  }
}


----------------------------
inline static size_t FindMatchLengthWithLimit(const uint8_t *s1, const uint8_t *s2, size_t limit)
{
  unsigned int s2_idx = 0;
  size_t matched = 0;
  size_t limit2 = (limit >> 3) + 1;
  while (__builtin_expect(!(!(--limit2)), 1))
  {
    if (__builtin_expect(BrotliUnalignedRead64(s2) == BrotliUnalignedRead64(s1 + matched), 0))
    {
      s2_idx += 8;
      matched += 8;
    }
    else
    {
      uint64_t x = BrotliUnalignedRead64(s2) ^ BrotliUnalignedRead64(s1 + matched);
      size_t matching_bits = (size_t) __builtin_ctzll(x);
      matched += matching_bits >> 3;
      return matched;
    }
  }

  limit = (limit & 7) + 1;
  while (--limit)
  {
    if (__builtin_expect(!(!(s1[matched] == (*(&s2[s2_idx])))), 1))
    {
      s2_idx += 1;
      matched += 1;
    }
    else
    {
      return matched;
    }
  }

  return matched;
}


----------------------------
inline static void EmitInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 6)
  {
    const size_t code = insertlen + 40;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (insertlen < 130)
  {
    const size_t tail = insertlen - 2;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1u;
    const size_t prefix = tail >> nbits;
    const size_t inscode = ((nbits << 1) + prefix) + 42;
    BrotliWriteBits(depth[inscode], bits[inscode], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[inscode] += 1;
  }
  else
    if (insertlen < 2114)
  {
    const size_t tail = insertlen - 66;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 50;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
  {
    BrotliWriteBits(depth[61], bits[61], storage_ix, storage);
    BrotliWriteBits(12, insertlen - 2114, storage_ix, storage);
    histo[61] += 1;
  }
}


----------------------------
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_hash_ref is a mutable refrence to uint32_t', 'skip_ref is a mutable refrence to uint32_t', 'next_ip_idx_ref is a mutable refrence to unsigned int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_1(unsigned int * const ip_idx_ref, uint32_t * const next_hash_ref, uint32_t * const skip_ref, unsigned int * const next_ip_idx_ref, unsigned int * const candidate_idx_ref, int * const table, const uint8_t * const base_ip, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, int last_distance, const uint8_t * const next_ip, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = *skip_ref;
  unsigned int next_ip_idx = *next_ip_idx_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  uint32_t hash = next_hash;
  uint32_t bytes_between_hash_lookups = (skip++) >> 5;
  skip += 1;
  ;
  ip_idx = &next_ip[next_ip_idx];
  next_ip_idx = (&ip[ip_idx]) + bytes_between_hash_lookups;
  if (__builtin_expect((&next_ip[next_ip_idx]) > ip_limit, 0))
  {
    goto emit_remainder;
  }
  next_hash = Hash(next_ip, shift);
  candidate_idx = (&ip[ip_idx]) - last_distance;
  if (IsMatch(ip, candidate))
  {
    if (__builtin_expect(!(!((&candidate[candidate_idx]) < (&ip[ip_idx]))), 1))
    {
      table[hash] = (int) ((&ip[ip_idx]) - base_ip);
      break;
    }
  }
  candidate_idx = base_ip + table[hash];
  ;
  ;
  table[hash] = (int) ((&ip[ip_idx]) - base_ip);
  *ip_idx_ref = ip_idx;
  *next_hash_ref = next_hash;
  *skip_ref = skip;
  *next_ip_idx_ref = next_ip_idx;
  *candidate_idx_ref = candidate_idx;
}


/*** DEPENDENCIES:
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
***/


// hint:  ['input_size_ref is a mutable refrence to size_t', 'input_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'ip_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'next_hash_ref is a mutable refrence to uint32_t']
void helper_helper_BrotliCompressFragmentFastImpl_2_1(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, uint32_t * const next_hash_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const uint8_t * const metablock_start, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = 32;
  const uint8_t *next_ip = ip;
  unsigned int next_ip_idx = 0;
  const uint8_t *candidate;
  unsigned int candidate_idx = 0;
  ;
  trawl:
  do
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_1(&ip_idx, &next_hash, &skip, &next_ip_idx, &candidate_idx, table, base_ip, ip, shift, ip_limit, last_distance, next_ip, candidate);
  }
  while (__builtin_expect(!(!(!IsMatch(ip, candidate))), 1));

  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    goto trawl;
  }
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_3(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, &candidate_idx, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, metablock_start, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift, ip_limit, candidate);
  }
  while (IsMatch(ip, candidate))
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_2(&next_emit_idx, &ip_idx, &last_distance, &candidate_idx, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, base_ip, ip, shift, ip_limit, candidate);
  }

  ip_idx += 1;
  next_hash = Hash(ip, shift);
  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *next_hash_ref = next_hash;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_2(unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const base_ip, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = 5 + FindMatchLengthWithLimit((&candidate[candidate_idx]) + 5, (&ip[ip_idx]) + 5, ((size_t) ((&ip_end[ip_end_idx]) - (&ip[ip_idx]))) - 5);
  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    break;
  }
  ip_idx += matched;
  last_distance = (int) (base - (&candidate[candidate_idx]));
  ;
  EmitCopyLen(matched, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  EmitDistance((size_t) last_distance, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    uint64_t input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    uint32_t prev_hash = HashBytesAtOffset(input_bytes, 0, shift);
    uint32_t cur_hash = HashBytesAtOffset(input_bytes, 3, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
    candidate_idx = base_ip + table[cur_hash];
    table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  }
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


----------------------------
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_3(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const uint8_t * const metablock_start, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = 5 + FindMatchLengthWithLimit((&candidate[candidate_idx]) + 5, (&ip[ip_idx]) + 5, ((size_t) ((&ip_end[ip_end_idx]) - (&ip[ip_idx]))) - 5);
  int distance = (int) (base - (&candidate[candidate_idx]));
  size_t insert = (size_t) (base - (&next_emit[next_emit_idx]));
  ip_idx += matched;
  ;
  if (__builtin_expect(!(!(insert < 6210)), 1))
  {
    EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  }
  else
    if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
  {
    EmitUncompressedMetaBlock(metablock_start, base, mlen_storage_ix - 3, storage_ix, storage);
    input_size -= (size_t) (base - (&input[input_idx]));
    input_idx = base;
    next_emit_idx = &input[input_idx];
    goto next_block;
  }
  else
  {
    EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  }
  EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
  if (distance == last_distance)
  {
    BrotliWriteBits(cmd_depth[64], cmd_bits[64], storage_ix, storage);
    cmd_histo[64] += 1;
  }
  else
  {
    EmitDistance((size_t) distance, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
    last_distance = distance;
  }
  EmitCopyLenLastDistance(matched, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    uint64_t input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    uint32_t prev_hash = HashBytesAtOffset(input_bytes, 0, shift);
    uint32_t cur_hash = HashBytesAtOffset(input_bytes, 3, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
    candidate_idx = base_ip + table[cur_hash];
    table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  }
  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


----------------------------
void helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_1(unsigned int * const ip_idx_ref, uint32_t * const next_hash_ref, uint32_t * const skip_ref, unsigned int * const next_ip_idx_ref, unsigned int * const candidate_idx_ref, int * const table, const uint8_t * const base_ip, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, int last_distance, const uint8_t * const next_ip, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = *skip_ref;
  unsigned int next_ip_idx = *next_ip_idx_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  uint32_t hash = next_hash;
  uint32_t bytes_between_hash_lookups = (skip++) >> 5;
  skip += 1;
  ;
  ip_idx = &next_ip[next_ip_idx];
  next_ip_idx = (&ip[ip_idx]) + bytes_between_hash_lookups;
  if (__builtin_expect((&next_ip[next_ip_idx]) > ip_limit, 0))
  {
    goto emit_remainder;
  }
  next_hash = Hash(next_ip, shift);
  candidate_idx = (&ip[ip_idx]) - last_distance;
  if (IsMatch(ip, candidate))
  {
    if (__builtin_expect(!(!((&candidate[candidate_idx]) < (&ip[ip_idx]))), 1))
    {
      table[hash] = (int) ((&ip[ip_idx]) - base_ip);
      break;
    }
  }
  candidate_idx = base_ip + table[hash];
  ;
  ;
  table[hash] = (int) ((&ip[ip_idx]) - base_ip);
  *ip_idx_ref = ip_idx;
  *next_hash_ref = next_hash;
  *skip_ref = skip;
  *next_ip_idx_ref = next_ip_idx;
  *candidate_idx_ref = candidate_idx;
}


----------------------------
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
***/


// hint:  ['input_size_ref is a mutable refrence to size_t', 'input_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'ip_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int']
void helper_BrotliCompressFragmentFastImpl_2(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const size_t kInputMarginBytes, const size_t kMinMatchLen, const uint8_t * const metablock_start, size_t block_size, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  const size_t len_limit = brotli_min_size_t(block_size - kMinMatchLen, input_size - kInputMarginBytes);
  const uint8_t *ip_limit = (&input[input_idx]) + len_limit;
  uint32_t next_hash;
  for (next_hash = Hash(++(&ip[ip_idx]), shift);;)
  {
    helper_helper_BrotliCompressFragmentFastImpl_2_1(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, &next_hash, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, metablock_start, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift, ip_limit);
  }

  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
void helper_helper_BrotliCompressFragmentFastImpl_2_1(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, uint32_t * const next_hash_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const uint8_t * const metablock_start, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = 32;
  const uint8_t *next_ip = ip;
  unsigned int next_ip_idx = 0;
  const uint8_t *candidate;
  unsigned int candidate_idx = 0;
  ;
  trawl:
  do
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_1(&ip_idx, &next_hash, &skip, &next_ip_idx, &candidate_idx, table, base_ip, ip, shift, ip_limit, last_distance, next_ip, candidate);
  }
  while (__builtin_expect(!(!(!IsMatch(ip, candidate))), 1));

  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    goto trawl;
  }
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_3(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, &candidate_idx, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, metablock_start, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift, ip_limit, candidate);
  }
  while (IsMatch(ip, candidate))
  {
    helper_helper_helper_BrotliCompressFragmentFastImpl_2_1_2(&next_emit_idx, &ip_idx, &last_distance, &candidate_idx, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, base_ip, ip, shift, ip_limit, candidate);
  }

  ip_idx += 1;
  next_hash = Hash(ip, shift);
  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
  *next_hash_ref = next_hash;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


inline static void BrotliCompressFragmentFastImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_bits, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  uint32_t cmd_histo[128];
  const uint8_t *ip_end;
  unsigned int ip_end_idx = 0;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  const uint8_t *base_ip = input;
  static const size_t kFirstBlockSize = 3 << 15;
  static const size_t kMergeBlockSize = 1 << 16;
  const size_t kInputMarginBytes = 16;
  const size_t kMinMatchLen = 5;
  const uint8_t *metablock_start = input;
  unsigned int metablock_start_idx = 0;
  size_t block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  size_t total_block_size = block_size;
  size_t mlen_storage_ix = (*storage_ix) + 3;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  size_t literal_ratio;
  const uint8_t *ip;
  unsigned int ip_idx = 0;
  int last_distance;
  const size_t shift = 64u - table_bits;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; (i + 7) < (*cmd_code_numbits); i += 8)
    {
      BrotliWriteBits(8, cmd_code[i >> 3], storage_ix, storage);
    }

  }
  BrotliWriteBits((*cmd_code_numbits) & 7, cmd_code[(*cmd_code_numbits) >> 3], storage_ix, storage);
  emit_commands:
  memcpy(cmd_histo, kCmdHistoSeed, sizeof(kCmdHistoSeed));

  ip_idx = &input[input_idx];
  last_distance = -1;
  ip_end_idx = (&input[input_idx]) + block_size;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_BrotliCompressFragmentFastImpl_2(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, kInputMarginBytes, kMinMatchLen, metablock_start, block_size, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift);
  }
  emit_remainder:
  ;

  input_idx += block_size;
  input_size -= block_size;
  block_size = brotli_min_size_t(input_size, kMergeBlockSize);
  if (((input_size > 0) && ((total_block_size + block_size) <= (1 << 20))) && ShouldMergeBlock(input, block_size, lit_depth))
  {
    ;
    total_block_size += block_size;
    UpdateBits(20, (uint32_t) (total_block_size - 1), mlen_storage_ix, storage);
    goto emit_commands;
  }
  if ((&next_emit[next_emit_idx]) < (&ip_end[ip_end_idx]))
  {
    const size_t insert = (size_t) ((&ip_end[ip_end_idx]) - (&next_emit[next_emit_idx]));
    if (__builtin_expect(!(!(insert < 6210)), 1))
    {
      EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
    else
      if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
    {
      EmitUncompressedMetaBlock(metablock_start, ip_end, mlen_storage_ix - 3, storage_ix, storage);
    }
    else
    {
      EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
  }
  next_emit_idx = &ip_end[ip_end_idx];
  next_block:
  if (input_size > 0)
  {
    helper_BrotliCompressFragmentFastImpl_1(&metablock_start_idx, &block_size, &total_block_size, &mlen_storage_ix, &literal_ratio, m, input, input_size, cmd_depth, cmd_bits, storage_ix, storage, input_idx, cmd_histo, kFirstBlockSize, lit_depth, lit_bits);
  }

  if (!is_last)
  {
    cmd_code[0] = 0;
    *cmd_code_numbits = 0;
    BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code);
  }
}


/*** DEPENDENCIES:
inline static void EmitLongInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 22594)
  {
    BrotliWriteBits(depth[62], bits[62], storage_ix, storage);
    BrotliWriteBits(14, insertlen - 6210, storage_ix, storage);
    histo[62] += 1;
  }
  else
  {
    BrotliWriteBits(depth[63], bits[63], storage_ix, storage);
    BrotliWriteBits(24, insertlen - 22594, storage_ix, storage);
    histo[63] += 1;
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static size_t BuildAndStoreLiteralPrefixCode(MemoryManager *m, const uint8_t *input, const size_t input_size, uint8_t depths[256], uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  uint32_t histogram[256] = {0};
  size_t histogram_total;
  size_t i;
  if (input_size < (1 << 15))
  {
    for (i = 0; i < input_size; i += 1)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = input_size;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 2 * brotli_min_uint32_t(histogram[i], 11u);
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  else
  {
    static const size_t kSampleRate = 29;
    for (i = 0; i < input_size; i += kSampleRate)
    {
      histogram[input[i]] += 1;
    }

    histogram_total = ((input_size + kSampleRate) - 1) / kSampleRate;
    for (i = 0; i < 256; i += 1)
    {
      const uint32_t adjust = 1 + (2 * brotli_min_uint32_t(histogram[i], 11u));
      histogram[i] += adjust;
      histogram_total += adjust;
    }

  }
  BrotliBuildAndStoreHuffmanTreeFast(m, histogram, histogram_total, 8, depths, bits, storage_ix, storage);
  if (!(!0))
  {
    return 0;
  }
  {
    size_t literal_ratio = 0;
    for (i = 0; i < 256; i += 1)
    {
      if (histogram[i])
      {
        literal_ratio += histogram[i] * depths[i];
      }
    }

    return (literal_ratio * 125) / histogram_total;
  }
}


----------------------------
inline static void EmitLiterals(const uint8_t *input, const size_t len, const uint8_t depth[256], const uint16_t bits[256], size_t *storage_ix, uint8_t *storage)
{
  size_t j;
  for (j = 0; j < len; j += 1)
  {
    const uint8_t lit = input[j];
    BrotliWriteBits(depth[lit], bits[lit], storage_ix, storage);
  }

}


----------------------------
static uint32_t kCmdHistoSeed[128] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}
----------------------------
void helper_BrotliCompressFragmentFastImpl_1(unsigned int * const metablock_start_idx_ref, size_t * const block_size_ref, size_t * const total_block_size_ref, size_t * const mlen_storage_ix_ref, size_t * const literal_ratio_ref, MemoryManager * const m, const uint8_t * const input, size_t input_size, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, unsigned int input_idx, uint32_t cmd_histo[128], static const size_t kFirstBlockSize, uint8_t lit_depth[256], uint16_t lit_bits[256])
{
  unsigned int metablock_start_idx = *metablock_start_idx_ref;
  size_t block_size = *block_size_ref;
  size_t total_block_size = *total_block_size_ref;
  size_t mlen_storage_ix = *mlen_storage_ix_ref;
  size_t literal_ratio = *literal_ratio_ref;
  metablock_start_idx = &input[input_idx];
  block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  total_block_size = block_size;
  mlen_storage_ix = (*storage_ix) + 3;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, storage_ix, storage);
  goto emit_commands;
  *metablock_start_idx_ref = metablock_start_idx;
  *block_size_ref = block_size;
  *total_block_size_ref = total_block_size;
  *mlen_storage_ix_ref = mlen_storage_ix;
  *literal_ratio_ref = literal_ratio;
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
static void UpdateBits(size_t n_bits, uint32_t bits, size_t pos, uint8_t *array)
{
  while (n_bits > 0)
  {
    size_t byte_pos = pos >> 3;
    size_t n_unchanged_bits = pos & 7;
    size_t n_changed_bits = brotli_min_size_t(n_bits, 8 - n_unchanged_bits);
    size_t total_bits = n_unchanged_bits + n_changed_bits;
    uint32_t mask = (~((1u << total_bits) - 1u)) | ((1u << n_unchanged_bits) - 1u);
    uint32_t unchanged_bits = array[byte_pos] & mask;
    uint32_t changed_bits = bits & ((1u << n_changed_bits) - 1u);
    array[byte_pos] = (uint8_t) ((changed_bits << n_unchanged_bits) | unchanged_bits);
    n_bits -= n_changed_bits;
    bits >>= n_changed_bits;
    pos += n_changed_bits;
  }

}


----------------------------
static void BrotliStoreMetaBlockHeader(size_t len, int is_uncompressed, size_t *storage_ix, uint8_t *storage)
{
  size_t nibbles = 6;
  BrotliWriteBits(1, 0, storage_ix, storage);
  if (len <= (1U << 16))
  {
    nibbles = 4;
  }
  else
    if (len <= (1U << 20))
  {
    nibbles = 5;
  }
  BrotliWriteBits(2, nibbles - 4, storage_ix, storage);
  BrotliWriteBits(nibbles * 4, len - 1, storage_ix, storage);
  BrotliWriteBits(1, (uint64_t) is_uncompressed, storage_ix, storage);
}


----------------------------
inline static int ShouldUseUncompressedMode(const uint8_t *metablock_start, const uint8_t *next_emit, const size_t insertlen, const size_t literal_ratio)
{
  const size_t compressed = (size_t) (next_emit - metablock_start);
  if ((compressed * 50) > insertlen)
  {
    return 0;
  }
  else
  {
    return (!(!(literal_ratio > 980))) ? (1) : (0);
  }
}


----------------------------
static void EmitUncompressedMetaBlock(const uint8_t *begin, const uint8_t *end, const size_t storage_ix_start, size_t *storage_ix, uint8_t *storage)
{
  const size_t len = (size_t) (end - begin);
  RewindBitPosition(storage_ix_start, storage_ix, storage);
  BrotliStoreMetaBlockHeader(len, 1, storage_ix, storage);
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  memcpy(&storage[(*storage_ix) >> 3], begin, len);
  *storage_ix += len << 3;
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
void helper_BrotliCompressFragmentFastImpl_2(size_t * const input_size_ref, unsigned int * const input_idx_ref, unsigned int * const next_emit_idx_ref, unsigned int * const ip_idx_ref, int * const last_distance_ref, const uint8_t * const input, int * const table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t * const storage_ix, uint8_t * const storage, uint32_t cmd_histo[128], const uint8_t * const ip_end, unsigned int ip_end_idx, const uint8_t * const next_emit, const uint8_t * const base_ip, const size_t kInputMarginBytes, const size_t kMinMatchLen, const uint8_t * const metablock_start, size_t block_size, size_t mlen_storage_ix, uint8_t lit_depth[256], uint16_t lit_bits[256], size_t literal_ratio, const uint8_t * const ip, const size_t shift)
{
  size_t input_size = *input_size_ref;
  unsigned int input_idx = *input_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  unsigned int ip_idx = *ip_idx_ref;
  int last_distance = *last_distance_ref;
  const size_t len_limit = brotli_min_size_t(block_size - kMinMatchLen, input_size - kInputMarginBytes);
  const uint8_t *ip_limit = (&input[input_idx]) + len_limit;
  uint32_t next_hash;
  for (next_hash = Hash(++(&ip[ip_idx]), shift);;)
  {
    helper_helper_BrotliCompressFragmentFastImpl_2_1(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, &next_hash, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, metablock_start, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift, ip_limit);
  }

  *input_size_ref = input_size;
  *input_idx_ref = input_idx;
  *next_emit_idx_ref = next_emit_idx;
  *ip_idx_ref = ip_idx;
  *last_distance_ref = last_distance;
}


----------------------------
static void BuildAndStoreCommandPrefixCode(const uint32_t histogram[128], uint8_t depth[128], uint16_t bits[128], size_t *storage_ix, uint8_t *storage)
{
  HuffmanTree tree[129];
  uint8_t cmd_depth[704] = {0};
  uint16_t cmd_bits[64];
  BrotliCreateHuffmanTree(histogram, 64, 15, tree, depth);
  BrotliCreateHuffmanTree(&histogram[64], 64, 14, tree, &depth[64]);
  memcpy(cmd_depth, depth, 24);
  memcpy(cmd_depth + 24, depth + 40, 8);
  memcpy(cmd_depth + 32, depth + 24, 8);
  memcpy(cmd_depth + 40, depth + 48, 8);
  memcpy(cmd_depth + 48, depth + 32, 8);
  memcpy(cmd_depth + 56, depth + 56, 8);
  BrotliConvertBitDepthsToSymbols(cmd_depth, 64, cmd_bits);
  memcpy(bits, cmd_bits, 48);
  memcpy(bits + 24, cmd_bits + 32, 16);
  memcpy(bits + 32, cmd_bits + 48, 16);
  memcpy(bits + 40, cmd_bits + 24, 16);
  memcpy(bits + 48, cmd_bits + 40, 16);
  memcpy(bits + 56, cmd_bits + 56, 16);
  BrotliConvertBitDepthsToSymbols(&depth[64], 64, &bits[64]);
  {
    helper_BuildAndStoreCommandPrefixCode_1(depth, storage_ix, storage, tree, cmd_depth);
  }
  BrotliStoreHuffmanTree(&depth[64], 64, tree, storage_ix, storage);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void EmitInsertLen(size_t insertlen, const uint8_t depth[128], const uint16_t bits[128], uint32_t histo[128], size_t *storage_ix, uint8_t *storage)
{
  if (insertlen < 6)
  {
    const size_t code = insertlen + 40;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    histo[code] += 1;
  }
  else
    if (insertlen < 130)
  {
    const size_t tail = insertlen - 2;
    const uint32_t nbits = Log2FloorNonZero(tail) - 1u;
    const size_t prefix = tail >> nbits;
    const size_t inscode = ((nbits << 1) + prefix) + 42;
    BrotliWriteBits(depth[inscode], bits[inscode], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (prefix << nbits), storage_ix, storage);
    histo[inscode] += 1;
  }
  else
    if (insertlen < 2114)
  {
    const size_t tail = insertlen - 66;
    const uint32_t nbits = Log2FloorNonZero(tail);
    const size_t code = nbits + 50;
    BrotliWriteBits(depth[code], bits[code], storage_ix, storage);
    BrotliWriteBits(nbits, tail - (((size_t) 1) << nbits), storage_ix, storage);
    histo[code] += 1;
  }
  else
  {
    BrotliWriteBits(depth[61], bits[61], storage_ix, storage);
    BrotliWriteBits(12, insertlen - 2114, storage_ix, storage);
    histo[61] += 1;
  }
}


----------------------------
static int ShouldMergeBlock(const uint8_t *data, size_t len, const uint8_t *depths)
{
  size_t histo[256] = {0};
  static const size_t kSampleRate = 43;
  size_t i;
  for (i = 0; i < len; i += kSampleRate)
  {
    histo[data[i]] += 1;
  }

  {
    const size_t total = ((len + kSampleRate) - 1) / kSampleRate;
    double r = ((FastLog2(total) + 0.5) * ((double) total)) + 200;
    for (i = 0; i < 256; i += 1)
    {
      r -= ((double) histo[i]) * (depths[i] + FastLog2(histo[i]));
    }

    return (!(!(r >= 0.0))) ? (1) : (0);
  }
}


----------------------------
***/


static void BrotliCompressFragmentFastImpl9(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 9, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentFastImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_bits, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  uint32_t cmd_histo[128];
  const uint8_t *ip_end;
  unsigned int ip_end_idx = 0;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  const uint8_t *base_ip = input;
  static const size_t kFirstBlockSize = 3 << 15;
  static const size_t kMergeBlockSize = 1 << 16;
  const size_t kInputMarginBytes = 16;
  const size_t kMinMatchLen = 5;
  const uint8_t *metablock_start = input;
  unsigned int metablock_start_idx = 0;
  size_t block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  size_t total_block_size = block_size;
  size_t mlen_storage_ix = (*storage_ix) + 3;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  size_t literal_ratio;
  const uint8_t *ip;
  unsigned int ip_idx = 0;
  int last_distance;
  const size_t shift = 64u - table_bits;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; (i + 7) < (*cmd_code_numbits); i += 8)
    {
      BrotliWriteBits(8, cmd_code[i >> 3], storage_ix, storage);
    }

  }
  BrotliWriteBits((*cmd_code_numbits) & 7, cmd_code[(*cmd_code_numbits) >> 3], storage_ix, storage);
  emit_commands:
  memcpy(cmd_histo, kCmdHistoSeed, sizeof(kCmdHistoSeed));

  ip_idx = &input[input_idx];
  last_distance = -1;
  ip_end_idx = (&input[input_idx]) + block_size;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_BrotliCompressFragmentFastImpl_2(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, kInputMarginBytes, kMinMatchLen, metablock_start, block_size, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift);
  }
  emit_remainder:
  ;

  input_idx += block_size;
  input_size -= block_size;
  block_size = brotli_min_size_t(input_size, kMergeBlockSize);
  if (((input_size > 0) && ((total_block_size + block_size) <= (1 << 20))) && ShouldMergeBlock(input, block_size, lit_depth))
  {
    ;
    total_block_size += block_size;
    UpdateBits(20, (uint32_t) (total_block_size - 1), mlen_storage_ix, storage);
    goto emit_commands;
  }
  if ((&next_emit[next_emit_idx]) < (&ip_end[ip_end_idx]))
  {
    const size_t insert = (size_t) ((&ip_end[ip_end_idx]) - (&next_emit[next_emit_idx]));
    if (__builtin_expect(!(!(insert < 6210)), 1))
    {
      EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
    else
      if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
    {
      EmitUncompressedMetaBlock(metablock_start, ip_end, mlen_storage_ix - 3, storage_ix, storage);
    }
    else
    {
      EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
  }
  next_emit_idx = &ip_end[ip_end_idx];
  next_block:
  if (input_size > 0)
  {
    helper_BrotliCompressFragmentFastImpl_1(&metablock_start_idx, &block_size, &total_block_size, &mlen_storage_ix, &literal_ratio, m, input, input_size, cmd_depth, cmd_bits, storage_ix, storage, input_idx, cmd_histo, kFirstBlockSize, lit_depth, lit_bits);
  }

  if (!is_last)
  {
    cmd_code[0] = 0;
    *cmd_code_numbits = 0;
    BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code);
  }
}


----------------------------
***/


static void BrotliCompressFragmentFastImpl11(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 11, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentFastImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_bits, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  uint32_t cmd_histo[128];
  const uint8_t *ip_end;
  unsigned int ip_end_idx = 0;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  const uint8_t *base_ip = input;
  static const size_t kFirstBlockSize = 3 << 15;
  static const size_t kMergeBlockSize = 1 << 16;
  const size_t kInputMarginBytes = 16;
  const size_t kMinMatchLen = 5;
  const uint8_t *metablock_start = input;
  unsigned int metablock_start_idx = 0;
  size_t block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  size_t total_block_size = block_size;
  size_t mlen_storage_ix = (*storage_ix) + 3;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  size_t literal_ratio;
  const uint8_t *ip;
  unsigned int ip_idx = 0;
  int last_distance;
  const size_t shift = 64u - table_bits;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; (i + 7) < (*cmd_code_numbits); i += 8)
    {
      BrotliWriteBits(8, cmd_code[i >> 3], storage_ix, storage);
    }

  }
  BrotliWriteBits((*cmd_code_numbits) & 7, cmd_code[(*cmd_code_numbits) >> 3], storage_ix, storage);
  emit_commands:
  memcpy(cmd_histo, kCmdHistoSeed, sizeof(kCmdHistoSeed));

  ip_idx = &input[input_idx];
  last_distance = -1;
  ip_end_idx = (&input[input_idx]) + block_size;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_BrotliCompressFragmentFastImpl_2(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, kInputMarginBytes, kMinMatchLen, metablock_start, block_size, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift);
  }
  emit_remainder:
  ;

  input_idx += block_size;
  input_size -= block_size;
  block_size = brotli_min_size_t(input_size, kMergeBlockSize);
  if (((input_size > 0) && ((total_block_size + block_size) <= (1 << 20))) && ShouldMergeBlock(input, block_size, lit_depth))
  {
    ;
    total_block_size += block_size;
    UpdateBits(20, (uint32_t) (total_block_size - 1), mlen_storage_ix, storage);
    goto emit_commands;
  }
  if ((&next_emit[next_emit_idx]) < (&ip_end[ip_end_idx]))
  {
    const size_t insert = (size_t) ((&ip_end[ip_end_idx]) - (&next_emit[next_emit_idx]));
    if (__builtin_expect(!(!(insert < 6210)), 1))
    {
      EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
    else
      if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
    {
      EmitUncompressedMetaBlock(metablock_start, ip_end, mlen_storage_ix - 3, storage_ix, storage);
    }
    else
    {
      EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
  }
  next_emit_idx = &ip_end[ip_end_idx];
  next_block:
  if (input_size > 0)
  {
    helper_BrotliCompressFragmentFastImpl_1(&metablock_start_idx, &block_size, &total_block_size, &mlen_storage_ix, &literal_ratio, m, input, input_size, cmd_depth, cmd_bits, storage_ix, storage, input_idx, cmd_histo, kFirstBlockSize, lit_depth, lit_bits);
  }

  if (!is_last)
  {
    cmd_code[0] = 0;
    *cmd_code_numbits = 0;
    BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code);
  }
}


----------------------------
***/


static void BrotliCompressFragmentFastImpl13(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 13, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentFastImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_bits, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  uint32_t cmd_histo[128];
  const uint8_t *ip_end;
  unsigned int ip_end_idx = 0;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  const uint8_t *base_ip = input;
  static const size_t kFirstBlockSize = 3 << 15;
  static const size_t kMergeBlockSize = 1 << 16;
  const size_t kInputMarginBytes = 16;
  const size_t kMinMatchLen = 5;
  const uint8_t *metablock_start = input;
  unsigned int metablock_start_idx = 0;
  size_t block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  size_t total_block_size = block_size;
  size_t mlen_storage_ix = (*storage_ix) + 3;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  size_t literal_ratio;
  const uint8_t *ip;
  unsigned int ip_idx = 0;
  int last_distance;
  const size_t shift = 64u - table_bits;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; (i + 7) < (*cmd_code_numbits); i += 8)
    {
      BrotliWriteBits(8, cmd_code[i >> 3], storage_ix, storage);
    }

  }
  BrotliWriteBits((*cmd_code_numbits) & 7, cmd_code[(*cmd_code_numbits) >> 3], storage_ix, storage);
  emit_commands:
  memcpy(cmd_histo, kCmdHistoSeed, sizeof(kCmdHistoSeed));

  ip_idx = &input[input_idx];
  last_distance = -1;
  ip_end_idx = (&input[input_idx]) + block_size;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_BrotliCompressFragmentFastImpl_2(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, kInputMarginBytes, kMinMatchLen, metablock_start, block_size, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift);
  }
  emit_remainder:
  ;

  input_idx += block_size;
  input_size -= block_size;
  block_size = brotli_min_size_t(input_size, kMergeBlockSize);
  if (((input_size > 0) && ((total_block_size + block_size) <= (1 << 20))) && ShouldMergeBlock(input, block_size, lit_depth))
  {
    ;
    total_block_size += block_size;
    UpdateBits(20, (uint32_t) (total_block_size - 1), mlen_storage_ix, storage);
    goto emit_commands;
  }
  if ((&next_emit[next_emit_idx]) < (&ip_end[ip_end_idx]))
  {
    const size_t insert = (size_t) ((&ip_end[ip_end_idx]) - (&next_emit[next_emit_idx]));
    if (__builtin_expect(!(!(insert < 6210)), 1))
    {
      EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
    else
      if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
    {
      EmitUncompressedMetaBlock(metablock_start, ip_end, mlen_storage_ix - 3, storage_ix, storage);
    }
    else
    {
      EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
  }
  next_emit_idx = &ip_end[ip_end_idx];
  next_block:
  if (input_size > 0)
  {
    helper_BrotliCompressFragmentFastImpl_1(&metablock_start_idx, &block_size, &total_block_size, &mlen_storage_ix, &literal_ratio, m, input, input_size, cmd_depth, cmd_bits, storage_ix, storage, input_idx, cmd_histo, kFirstBlockSize, lit_depth, lit_bits);
  }

  if (!is_last)
  {
    cmd_code[0] = 0;
    *cmd_code_numbits = 0;
    BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code);
  }
}


----------------------------
***/


static void BrotliCompressFragmentFastImpl15(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 15, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentFastImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_bits, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  uint32_t cmd_histo[128];
  const uint8_t *ip_end;
  unsigned int ip_end_idx = 0;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  const uint8_t *base_ip = input;
  static const size_t kFirstBlockSize = 3 << 15;
  static const size_t kMergeBlockSize = 1 << 16;
  const size_t kInputMarginBytes = 16;
  const size_t kMinMatchLen = 5;
  const uint8_t *metablock_start = input;
  unsigned int metablock_start_idx = 0;
  size_t block_size = brotli_min_size_t(input_size, kFirstBlockSize);
  size_t total_block_size = block_size;
  size_t mlen_storage_ix = (*storage_ix) + 3;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  size_t literal_ratio;
  const uint8_t *ip;
  unsigned int ip_idx = 0;
  int last_distance;
  const size_t shift = 64u - table_bits;
  BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  literal_ratio = BuildAndStoreLiteralPrefixCode(m, input, block_size, lit_depth, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    size_t i;
    for (i = 0; (i + 7) < (*cmd_code_numbits); i += 8)
    {
      BrotliWriteBits(8, cmd_code[i >> 3], storage_ix, storage);
    }

  }
  BrotliWriteBits((*cmd_code_numbits) & 7, cmd_code[(*cmd_code_numbits) >> 3], storage_ix, storage);
  emit_commands:
  memcpy(cmd_histo, kCmdHistoSeed, sizeof(kCmdHistoSeed));

  ip_idx = &input[input_idx];
  last_distance = -1;
  ip_end_idx = (&input[input_idx]) + block_size;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_BrotliCompressFragmentFastImpl_2(&input_size, &input_idx, &next_emit_idx, &ip_idx, &last_distance, input, table, cmd_depth, cmd_bits, storage_ix, storage, cmd_histo, ip_end, ip_end_idx, next_emit, base_ip, kInputMarginBytes, kMinMatchLen, metablock_start, block_size, mlen_storage_ix, lit_depth, lit_bits, literal_ratio, ip, shift);
  }
  emit_remainder:
  ;

  input_idx += block_size;
  input_size -= block_size;
  block_size = brotli_min_size_t(input_size, kMergeBlockSize);
  if (((input_size > 0) && ((total_block_size + block_size) <= (1 << 20))) && ShouldMergeBlock(input, block_size, lit_depth))
  {
    ;
    total_block_size += block_size;
    UpdateBits(20, (uint32_t) (total_block_size - 1), mlen_storage_ix, storage);
    goto emit_commands;
  }
  if ((&next_emit[next_emit_idx]) < (&ip_end[ip_end_idx]))
  {
    const size_t insert = (size_t) ((&ip_end[ip_end_idx]) - (&next_emit[next_emit_idx]));
    if (__builtin_expect(!(!(insert < 6210)), 1))
    {
      EmitInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
    else
      if (ShouldUseUncompressedMode(metablock_start, next_emit, insert, literal_ratio))
    {
      EmitUncompressedMetaBlock(metablock_start, ip_end, mlen_storage_ix - 3, storage_ix, storage);
    }
    else
    {
      EmitLongInsertLen(insert, cmd_depth, cmd_bits, cmd_histo, storage_ix, storage);
      EmitLiterals(next_emit, insert, lit_depth, lit_bits, storage_ix, storage);
    }
  }
  next_emit_idx = &ip_end[ip_end_idx];
  next_block:
  if (input_size > 0)
  {
    helper_BrotliCompressFragmentFastImpl_1(&metablock_start_idx, &block_size, &total_block_size, &mlen_storage_ix, &literal_ratio, m, input, input_size, cmd_depth, cmd_bits, storage_ix, storage, input_idx, cmd_histo, kFirstBlockSize, lit_depth, lit_bits);
  }

  if (!is_last)
  {
    cmd_code[0] = 0;
    *cmd_code_numbits = 0;
    BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code);
  }
}


----------------------------
***/


void BrotliCompressFragmentFast(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_size, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  if (input_size == 0)
  {
    ;
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
    return;
  }
  switch (table_bits)
  {
    case 9:
    {
      BrotliCompressFragmentFastImpl9(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentFastImpl11(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentFastImpl13(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentFastImpl15(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    default:
    {
      ;
      break;
    }

  }

  if (((*storage_ix) - initial_storage_ix) > (31 + (input_size << 3)))
  {
    EmitUncompressedMetaBlock(input, input + input_size, initial_storage_ix, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


/*** DEPENDENCIES:
static void BrotliCompressFragmentFastImpl13(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 13, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


----------------------------
static void EmitUncompressedMetaBlock(const uint8_t *begin, const uint8_t *end, const size_t storage_ix_start, size_t *storage_ix, uint8_t *storage)
{
  const size_t len = (size_t) (end - begin);
  RewindBitPosition(storage_ix_start, storage_ix, storage);
  BrotliStoreMetaBlockHeader(len, 1, storage_ix, storage);
  *storage_ix = ((*storage_ix) + 7u) & (~7u);
  memcpy(&storage[(*storage_ix) >> 3], begin, len);
  *storage_ix += len << 3;
  storage[(*storage_ix) >> 3] = 0;
}


----------------------------
static void BrotliCompressFragmentFastImpl11(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 11, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void BrotliCompressFragmentFastImpl9(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 9, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentFastImpl15(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  BrotliCompressFragmentFastImpl(m, input, input_size, is_last, table, 15, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
}


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
***/


