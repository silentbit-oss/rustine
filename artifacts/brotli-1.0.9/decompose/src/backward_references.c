inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


/*** DEPENDENCIES:
***/


inline static uint16_t CombineLengthCodes(uint16_t inscode, uint16_t copycode, int use_last_distance)
{
  uint16_t bits64 = (uint16_t) ((copycode & 0x7u) | ((inscode & 0x7u) << 3u));
  if ((use_last_distance && (inscode < 8u)) && (copycode < 16u))
  {
    return (copycode < 8u) ? (bits64) : (bits64 | 64u);
  }
  else
  {
    uint32_t offset = 2u * ((copycode >> 3u) + (3u * (inscode >> 3u)));
    offset = ((offset << 5u) + 0x40u) + ((0x520D40u >> offset) & 0xC0u);
    return (uint16_t) (offset | bits64);
  }
}


/*** DEPENDENCIES:
***/


inline static size_t MaxHashTableSize(int quality)
{
  return (quality == 0) ? (1 << 15) : (1 << 17);
}


/*** DEPENDENCIES:
***/


inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


/*** DEPENDENCIES:
***/


inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


/*** DEPENDENCIES:
***/


inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH10(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH10(void)
{
  return 128;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH2(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH2(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH3(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH3(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH4(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH4(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH5(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH5(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static uint16_t *NumH5(void *extra)
{
  return (uint16_t *) extra;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH6(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH6(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH40(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH40(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


static uint32_t *AddrH40(void *extra)
{
  return (uint32_t *) extra;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH41(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH41(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


static uint32_t *AddrH41(void *extra)
{
  return (uint32_t *) extra;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH42(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH42(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


static uint32_t *AddrH42(void *extra)
{
  return (uint32_t *) extra;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthH54(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadH54(void)
{
  return 8;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthHROLLING_FAST(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadHROLLING_FAST(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


static uint32_t HashByteHROLLING_FAST(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


/*** DEPENDENCIES:
***/


inline static size_t HashTypeLengthHROLLING(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


inline static size_t StoreLookaheadHROLLING(void)
{
  return 4;
}


/*** DEPENDENCIES:
***/


static uint32_t HashByteHROLLING(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


/*** DEPENDENCIES:
***/


inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


/*** DEPENDENCIES:
***/


inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


/*** DEPENDENCIES:
extern const double kBrotliLog2Table[256]
----------------------------
***/


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


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


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


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


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


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


inline static uint32_t GetInsertBase(uint16_t inscode)
{
  return kBrotliInsBase[inscode];
}


/*** DEPENDENCIES:
extern const uint32_t kBrotliInsBase[24]
----------------------------
***/


inline static uint32_t GetInsertExtra(uint16_t inscode)
{
  return kBrotliInsExtra[inscode];
}


/*** DEPENDENCIES:
extern const uint32_t kBrotliInsExtra[24]
----------------------------
***/


inline static uint32_t GetCopyBase(uint16_t copycode)
{
  return kBrotliCopyBase[copycode];
}


/*** DEPENDENCIES:
extern const uint32_t kBrotliCopyBase[24]
----------------------------
***/


inline static uint32_t GetCopyExtra(uint16_t copycode)
{
  return kBrotliCopyExtra[copycode];
}


/*** DEPENDENCIES:
extern const uint32_t kBrotliCopyExtra[24]
----------------------------
***/


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


inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
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


inline static uint32_t CommandCopyLenCode(const Command *self)
{
  uint32_t modifier = self->copy_len_ >> 25;
  int32_t delta = (int8_t) ((uint8_t) (modifier | ((modifier & 0x40) << 1)));
  return (uint32_t) (((int32_t) (self->copy_len_ & 0x1FFFFFF)) + delta);
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


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
***/


inline static size_t MaxZopfliLen(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (150) : (325);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t MaxZopfliCandidates(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (1) : (5);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


/*** DEPENDENCIES:
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


inline static void InitBackwardMatch(BackwardMatch *self, size_t dist, size_t len)
{
  self->distance = (uint32_t) dist;
  self->length_and_code = (uint32_t) (len << 5);
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
***/


inline static void InitDictionaryBackwardMatch(BackwardMatch *self, size_t dist, size_t len, size_t len_code)
{
  self->distance = (uint32_t) dist;
  self->length_and_code = (uint32_t) ((len << 5) | ((len == len_code) ? (0) : (len_code)));
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
***/


inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
***/


static void PrepareH10(H10 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t invalid_pos = self->invalid_pos_;
  uint32_t i;
  uint32_t * restrict buckets = self->buckets_;
  (void) data;
  (void) one_shot;
  (void) input_size;
  for (i = 0; i < (1 << 17); i += 1)
  {
    buckets[i] = invalid_pos;
  }

}


/*** DEPENDENCIES:
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static size_t HashMemAllocInBytesH10(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t num_nodes = ((size_t) 1) << params->lgwin;
  if (one_shot && (input_size < num_nodes))
  {
    num_nodes = input_size;
  }
  return ((sizeof(uint32_t)) * (1 << 17)) + ((2 * (sizeof(uint32_t))) * num_nodes);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t LeftChildIndexH10(H10 * restrict self, const size_t pos)
{
  return 2 * (pos & self->window_mask_);
}


/*** DEPENDENCIES:
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static size_t RightChildIndexH10(H10 * restrict self, const size_t pos)
{
  return (2 * (pos & self->window_mask_)) + 1;
}


/*** DEPENDENCIES:
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static size_t HashMemAllocInBytesH2(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void PrepareDistanceCacheH2(H2 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH3(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void PrepareDistanceCacheH3(H3 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH4(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 17);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void PrepareDistanceCacheH4(H4 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH5(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH6(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static uint16_t *HeadH40(void *extra)
{
  return (uint16_t *) (&AddrH40(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint32_t *AddrH40(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
***/


static uint8_t *TinyHashH40(void *extra)
{
  return (uint8_t *) (&HeadH40(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint16_t *HeadH40(void *extra)
{
  return (uint16_t *) (&AddrH40(extra)[1 << 15]);
}


----------------------------
***/


static BankH40 *BanksH40(void *extra)
{
  return (BankH40 *) (&TinyHashH40(extra)[65536]);
}


/*** DEPENDENCIES:
static uint8_t *TinyHashH40(void *extra)
{
  return (uint8_t *) (&HeadH40(extra)[1 << 15]);
}


----------------------------
***/


inline static size_t HashMemAllocInBytesH40(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH40)) * 1);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static uint16_t *HeadH41(void *extra)
{
  return (uint16_t *) (&AddrH41(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint32_t *AddrH41(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
***/


static uint8_t *TinyHashH41(void *extra)
{
  return (uint8_t *) (&HeadH41(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint16_t *HeadH41(void *extra)
{
  return (uint16_t *) (&AddrH41(extra)[1 << 15]);
}


----------------------------
***/


static BankH41 *BanksH41(void *extra)
{
  return (BankH41 *) (&TinyHashH41(extra)[65536]);
}


/*** DEPENDENCIES:
static uint8_t *TinyHashH41(void *extra)
{
  return (uint8_t *) (&HeadH41(extra)[1 << 15]);
}


----------------------------
***/


inline static size_t HashMemAllocInBytesH41(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH41)) * 1);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static uint16_t *HeadH42(void *extra)
{
  return (uint16_t *) (&AddrH42(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint32_t *AddrH42(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
***/


static uint8_t *TinyHashH42(void *extra)
{
  return (uint8_t *) (&HeadH42(extra)[1 << 15]);
}


/*** DEPENDENCIES:
static uint16_t *HeadH42(void *extra)
{
  return (uint16_t *) (&AddrH42(extra)[1 << 15]);
}


----------------------------
***/


static BankH42 *BanksH42(void *extra)
{
  return (BankH42 *) (&TinyHashH42(extra)[65536]);
}


/*** DEPENDENCIES:
static uint8_t *TinyHashH42(void *extra)
{
  return (uint8_t *) (&HeadH42(extra)[1 << 15]);
}


----------------------------
***/


inline static size_t HashMemAllocInBytesH42(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH42)) * 512);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH54(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 20);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static uint32_t HashRollingFunctionInitialHROLLING_FAST(uint32_t state, uint8_t add, uint32_t factor)
{
  return (uint32_t) ((factor * state) + HashByteHROLLING_FAST(add));
}


/*** DEPENDENCIES:
static uint32_t HashByteHROLLING_FAST(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


----------------------------
***/


static uint32_t HashRollingFunctionHROLLING_FAST(uint32_t state, uint8_t add, uint8_t rem, uint32_t factor, uint32_t factor_remove)
{
  return (uint32_t) (((factor * state) + HashByteHROLLING_FAST(add)) - (factor_remove * HashByteHROLLING_FAST(rem)));
}


/*** DEPENDENCIES:
static uint32_t HashByteHROLLING_FAST(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


----------------------------
***/


inline static size_t HashMemAllocInBytesHROLLING_FAST(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return 16777216 * (sizeof(uint32_t));
  (void) params;
  (void) one_shot;
  (void) input_size;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static uint32_t HashRollingFunctionInitialHROLLING(uint32_t state, uint8_t add, uint32_t factor)
{
  return (uint32_t) ((factor * state) + HashByteHROLLING(add));
}


/*** DEPENDENCIES:
static uint32_t HashByteHROLLING(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


----------------------------
***/


static uint32_t HashRollingFunctionHROLLING(uint32_t state, uint8_t add, uint8_t rem, uint32_t factor, uint32_t factor_remove)
{
  return (uint32_t) (((factor * state) + HashByteHROLLING(add)) - (factor_remove * HashByteHROLLING(rem)));
}


/*** DEPENDENCIES:
static uint32_t HashByteHROLLING(uint8_t byte)
{
  return ((uint32_t) byte) + 1u;
}


----------------------------
***/


inline static size_t HashMemAllocInBytesHROLLING(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return 16777216 * (sizeof(uint32_t));
  (void) params;
  (void) one_shot;
  (void) input_size;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void StoreHROLLING(HROLLING * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
***/


inline static void StoreRangeHROLLING(HROLLING * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix_start;
  (void) ix_end;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
***/


inline static void PrepareDistanceCacheHROLLING(HROLLING * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
***/


inline static void HasherInit(Hasher *hasher)
{
  hasher->common.extra = 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void HasherReset(Hasher *hasher)
{
  hasher->common.is_prepared_ = 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void GetLengthCode(size_t insertlen, size_t copylen, int use_last_distance, uint16_t *code)
{
  uint16_t inscode = GetInsertLengthCode(insertlen);
  uint16_t copycode = GetCopyLengthCode(copylen);
  *code = CombineLengthCodes(inscode, copycode, use_last_distance);
}


/*** DEPENDENCIES:
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
inline static uint16_t CombineLengthCodes(uint16_t inscode, uint16_t copycode, int use_last_distance)
{
  uint16_t bits64 = (uint16_t) ((copycode & 0x7u) | ((inscode & 0x7u) << 3u));
  if ((use_last_distance && (inscode < 8u)) && (copycode < 16u))
  {
    return (copycode < 8u) ? (bits64) : (bits64 | 64u);
  }
  else
  {
    uint32_t offset = 2u * ((copycode >> 3u) + (3u * (inscode >> 3u)));
    offset = ((offset << 5u) + 0x40u) + ((0x520D40u >> offset) & 0xC0u);
    return (uint16_t) (offset | bits64);
  }
}


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
***/


inline static void InitInsertCommand(Command *self, size_t insertlen)
{
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = 4 << 25;
  self->dist_extra_ = 0;
  self->dist_prefix_ = 16;
  GetLengthCode(insertlen, 4, 0, &self->cmd_prefix_);
}


/*** DEPENDENCIES:
inline static void GetLengthCode(size_t insertlen, size_t copylen, int use_last_distance, uint16_t *code)
{
  uint16_t inscode = GetInsertLengthCode(insertlen);
  uint16_t copycode = GetCopyLengthCode(copylen);
  *code = CombineLengthCodes(inscode, copycode, use_last_distance);
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


/*** DEPENDENCIES:
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
***/


inline static int ComputeRbBits(const BrotliEncoderParams *params)
{
  return 1 + brotli_max_int(params->lgwin, params->lgblock);
}


/*** DEPENDENCIES:
inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static uint32_t Hash14(const uint8_t *data)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 14);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


inline static size_t BackwardMatchLengthCode(const BackwardMatch *self)
{
  size_t code = self->length_and_code & 31;
  return (code) ? (code) : (BackwardMatchLength(self));
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


----------------------------
***/


static uint32_t HashBytesH10(const uint8_t * restrict data)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 17);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


// hint:  ['matches_idx_ref is a mutable refrence to unsigned int', 'prev_ix_ref is a mutable refrence to size_t', 'node_left_ref is a mutable refrence to size_t', 'node_right_ref is a mutable refrence to size_t', 'best_len_left_ref is a mutable refrence to size_t', 'best_len_right_ref is a mutable refrence to size_t']
void helper_helper_StoreAndFindMatchesH10_1_1(unsigned int * const matches_idx_ref, size_t * const prev_ix_ref, size_t * const node_left_ref, size_t * const node_right_ref, size_t * const best_len_left_ref, size_t * const best_len_right_ref, H10 * const self, const uint8_t * const data, const size_t max_length, size_t * const best_len, BackwardMatch * const matches, const size_t cur_ix_masked, const size_t max_comp_len, const int should_reroot_tree, uint32_t * const forest, const size_t backward, const size_t prev_ix_masked)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t node_left = *node_left_ref;
  size_t node_right = *node_right_ref;
  size_t best_len_left = *best_len_left_ref;
  size_t best_len_right = *best_len_right_ref;
  const size_t cur_len = brotli_min_size_t(best_len_left, best_len_right);
  size_t len;
  ;
  len = cur_len + FindMatchLengthWithLimit(&data[cur_ix_masked + cur_len], &data[prev_ix_masked + cur_len], max_length - cur_len);
  ;
  if ((&matches[matches_idx]) && (len > (*best_len)))
  {
    *best_len = len;
    InitBackwardMatch(matches, backward, len);
    matches_idx += 1;
  }
  if (len >= max_comp_len)
  {
    if (should_reroot_tree)
    {
      forest[node_left] = forest[LeftChildIndexH10(self, prev_ix)];
      forest[node_right] = forest[RightChildIndexH10(self, prev_ix)];
    }
    break;
  }
  if (data[cur_ix_masked + len] > data[prev_ix_masked + len])
  {
    best_len_left = len;
    if (should_reroot_tree)
    {
      forest[node_left] = (uint32_t) prev_ix;
    }
    node_left = RightChildIndexH10(self, prev_ix);
    prev_ix = forest[node_left];
  }
  else
  {
    best_len_right = len;
    if (should_reroot_tree)
    {
      forest[node_right] = (uint32_t) prev_ix;
    }
    node_right = LeftChildIndexH10(self, prev_ix);
    prev_ix = forest[node_right];
  }
  *matches_idx_ref = matches_idx;
  *prev_ix_ref = prev_ix;
  *node_left_ref = node_left;
  *node_right_ref = node_right;
  *best_len_left_ref = best_len_left;
  *best_len_right_ref = best_len_right;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static void InitBackwardMatch(BackwardMatch *self, size_t dist, size_t len)
{
  self->distance = (uint32_t) dist;
  self->length_and_code = (uint32_t) (len << 5);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t LeftChildIndexH10(H10 * restrict self, const size_t pos)
{
  return 2 * (pos & self->window_mask_);
}


----------------------------
inline static size_t RightChildIndexH10(H10 * restrict self, const size_t pos)
{
  return (2 * (pos & self->window_mask_)) + 1;
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
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


// hint:  ['matches_idx_ref is a mutable refrence to unsigned int', 'prev_ix_ref is a mutable refrence to size_t', 'node_left_ref is a mutable refrence to size_t', 'node_right_ref is a mutable refrence to size_t', 'best_len_left_ref is a mutable refrence to size_t', 'best_len_right_ref is a mutable refrence to size_t']
void helper_StoreAndFindMatchesH10_1(unsigned int * const matches_idx_ref, size_t * const prev_ix_ref, size_t * const node_left_ref, size_t * const node_right_ref, size_t * const best_len_left_ref, size_t * const best_len_right_ref, H10 * const self, const uint8_t * const data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const best_len, BackwardMatch * const matches, const size_t cur_ix_masked, const size_t max_comp_len, const int should_reroot_tree, uint32_t * const forest, size_t depth_remaining)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t node_left = *node_left_ref;
  size_t node_right = *node_right_ref;
  size_t best_len_left = *best_len_left_ref;
  size_t best_len_right = *best_len_right_ref;
  const size_t backward = cur_ix - prev_ix;
  const size_t prev_ix_masked = prev_ix & ring_buffer_mask;
  if (((backward == 0) || (backward > max_backward)) || (depth_remaining == 0))
  {
    if (should_reroot_tree)
    {
      forest[node_left] = self->invalid_pos_;
      forest[node_right] = self->invalid_pos_;
    }
    break;
  }
  {
    helper_helper_StoreAndFindMatchesH10_1_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, max_length, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, backward, prev_ix_masked);
  }
  *matches_idx_ref = matches_idx;
  *prev_ix_ref = prev_ix;
  *node_left_ref = node_left;
  *node_right_ref = node_right;
  *best_len_left_ref = best_len_left;
  *best_len_right_ref = best_len_right;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
void helper_helper_StoreAndFindMatchesH10_1_1(unsigned int * const matches_idx_ref, size_t * const prev_ix_ref, size_t * const node_left_ref, size_t * const node_right_ref, size_t * const best_len_left_ref, size_t * const best_len_right_ref, H10 * const self, const uint8_t * const data, const size_t max_length, size_t * const best_len, BackwardMatch * const matches, const size_t cur_ix_masked, const size_t max_comp_len, const int should_reroot_tree, uint32_t * const forest, const size_t backward, const size_t prev_ix_masked)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t node_left = *node_left_ref;
  size_t node_right = *node_right_ref;
  size_t best_len_left = *best_len_left_ref;
  size_t best_len_right = *best_len_right_ref;
  const size_t cur_len = brotli_min_size_t(best_len_left, best_len_right);
  size_t len;
  ;
  len = cur_len + FindMatchLengthWithLimit(&data[cur_ix_masked + cur_len], &data[prev_ix_masked + cur_len], max_length - cur_len);
  ;
  if ((&matches[matches_idx]) && (len > (*best_len)))
  {
    *best_len = len;
    InitBackwardMatch(matches, backward, len);
    matches_idx += 1;
  }
  if (len >= max_comp_len)
  {
    if (should_reroot_tree)
    {
      forest[node_left] = forest[LeftChildIndexH10(self, prev_ix)];
      forest[node_right] = forest[RightChildIndexH10(self, prev_ix)];
    }
    break;
  }
  if (data[cur_ix_masked + len] > data[prev_ix_masked + len])
  {
    best_len_left = len;
    if (should_reroot_tree)
    {
      forest[node_left] = (uint32_t) prev_ix;
    }
    node_left = RightChildIndexH10(self, prev_ix);
    prev_ix = forest[node_left];
  }
  else
  {
    best_len_right = len;
    if (should_reroot_tree)
    {
      forest[node_right] = (uint32_t) prev_ix;
    }
    node_right = LeftChildIndexH10(self, prev_ix);
    prev_ix = forest[node_right];
  }
  *matches_idx_ref = matches_idx;
  *prev_ix_ref = prev_ix;
  *node_left_ref = node_left;
  *node_right_ref = node_right;
  *best_len_left_ref = best_len_left;
  *best_len_right_ref = best_len_right;
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static BackwardMatch *StoreAndFindMatchesH10(H10 * restrict self, const uint8_t * restrict data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const restrict best_len, BackwardMatch * restrict matches)
{
  unsigned int matches_idx = 0;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  const size_t max_comp_len = brotli_min_size_t(max_length, 128);
  const int should_reroot_tree = (!(!(max_length >= 128))) ? (1) : (0);
  const uint32_t key = HashBytesH10(&data[cur_ix_masked]);
  uint32_t * restrict buckets = self->buckets_;
  uint32_t * restrict forest = self->forest_;
  size_t prev_ix = buckets[key];
  size_t node_left = LeftChildIndexH10(self, cur_ix);
  size_t node_right = RightChildIndexH10(self, cur_ix);
  size_t best_len_left = 0;
  size_t best_len_right = 0;
  size_t depth_remaining;
  if (should_reroot_tree)
  {
    buckets[key] = (uint32_t) cur_ix;
  }
  for (depth_remaining = 64;; depth_remaining -= 1)
  {
    helper_StoreAndFindMatchesH10_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, cur_ix, ring_buffer_mask, max_length, max_backward, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, depth_remaining);
  }

  return matches;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
void helper_StoreAndFindMatchesH10_1(unsigned int * const matches_idx_ref, size_t * const prev_ix_ref, size_t * const node_left_ref, size_t * const node_right_ref, size_t * const best_len_left_ref, size_t * const best_len_right_ref, H10 * const self, const uint8_t * const data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const best_len, BackwardMatch * const matches, const size_t cur_ix_masked, const size_t max_comp_len, const int should_reroot_tree, uint32_t * const forest, size_t depth_remaining)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t node_left = *node_left_ref;
  size_t node_right = *node_right_ref;
  size_t best_len_left = *best_len_left_ref;
  size_t best_len_right = *best_len_right_ref;
  const size_t backward = cur_ix - prev_ix;
  const size_t prev_ix_masked = prev_ix & ring_buffer_mask;
  if (((backward == 0) || (backward > max_backward)) || (depth_remaining == 0))
  {
    if (should_reroot_tree)
    {
      forest[node_left] = self->invalid_pos_;
      forest[node_right] = self->invalid_pos_;
    }
    break;
  }
  {
    helper_helper_StoreAndFindMatchesH10_1_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, max_length, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, backward, prev_ix_masked);
  }
  *matches_idx_ref = matches_idx;
  *prev_ix_ref = prev_ix;
  *node_left_ref = node_left;
  *node_right_ref = node_right;
  *best_len_left_ref = best_len_left;
  *best_len_right_ref = best_len_right;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t LeftChildIndexH10(H10 * restrict self, const size_t pos)
{
  return 2 * (pos & self->window_mask_);
}


----------------------------
inline static size_t RightChildIndexH10(H10 * restrict self, const size_t pos)
{
  return (2 * (pos & self->window_mask_)) + 1;
}


----------------------------
static uint32_t HashBytesH10(const uint8_t * restrict data)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 17);
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static void StoreH10(H10 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const size_t max_backward = (self->window_mask_ - 16) + 1;
  StoreAndFindMatchesH10(self, data, ix, mask, 128, max_backward, 0, 0);
}


/*** DEPENDENCIES:
inline static BackwardMatch *StoreAndFindMatchesH10(H10 * restrict self, const uint8_t * restrict data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const restrict best_len, BackwardMatch * restrict matches)
{
  unsigned int matches_idx = 0;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  const size_t max_comp_len = brotli_min_size_t(max_length, 128);
  const int should_reroot_tree = (!(!(max_length >= 128))) ? (1) : (0);
  const uint32_t key = HashBytesH10(&data[cur_ix_masked]);
  uint32_t * restrict buckets = self->buckets_;
  uint32_t * restrict forest = self->forest_;
  size_t prev_ix = buckets[key];
  size_t node_left = LeftChildIndexH10(self, cur_ix);
  size_t node_right = RightChildIndexH10(self, cur_ix);
  size_t best_len_left = 0;
  size_t best_len_right = 0;
  size_t depth_remaining;
  if (should_reroot_tree)
  {
    buckets[key] = (uint32_t) cur_ix;
  }
  for (depth_remaining = 64;; depth_remaining -= 1)
  {
    helper_StoreAndFindMatchesH10_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, cur_ix, ring_buffer_mask, max_length, max_backward, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, depth_remaining);
  }

  return matches;
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static void StoreRangeH10(H10 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i = ix_start;
  size_t j = ix_start;
  if ((ix_start + 63) <= ix_end)
  {
    i = ix_end - 63;
  }
  if ((ix_start + 512) <= i)
  {
    for (; j < i; j += 8)
    {
      StoreH10(self, data, mask, j);
    }

  }
  for (; i < ix_end; i += 1)
  {
    StoreH10(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH10(H10 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const size_t max_backward = (self->window_mask_ - 16) + 1;
  StoreAndFindMatchesH10(self, data, ix, mask, 128, max_backward, 0, 0);
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


static uint32_t HashBytesH2(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint64_t kHashMul64 = (((uint64_t) 0x1E35A7BD) << 32) | 0x1E35A7BD
----------------------------
***/


static void PrepareH2(H2 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 16) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH2(&data[i]);
      if ((1 << 0) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 0); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 16) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 16));
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH2(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
None
----------------------------
***/


inline static void StoreH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH2(&data[ix & mask]);
  if ((1 << 0) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 0) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH2(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH2(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH2(&data[ix & mask]);
  if ((1 << 0) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 0) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


static uint32_t HashBytesH3(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint64_t kHashMul64 = (((uint64_t) 0x1E35A7BD) << 32) | 0x1E35A7BD
----------------------------
***/


static void PrepareH3(H3 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 16) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH3(&data[i]);
      if ((1 << 1) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 1); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 16) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 16));
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH3(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
None
----------------------------
***/


inline static void StoreH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH3(&data[ix & mask]);
  if ((1 << 1) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 1) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH3(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH3(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH3(&data[ix & mask]);
  if ((1 << 1) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 1) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


static uint32_t HashBytesH4(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 17));
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint64_t kHashMul64 = (((uint64_t) 0x1E35A7BD) << 32) | 0x1E35A7BD
----------------------------
***/


static void PrepareH4(H4 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 17) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH4(&data[i]);
      if ((1 << 2) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 2); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 17) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 17));
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH4(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 17));
}


----------------------------
None
----------------------------
***/


inline static void StoreH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH4(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 17) - 1)] = (uint32_t) ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH4(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 17));
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH4(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH4(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 17) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


static uint32_t HashBytesH5(const uint8_t * restrict data, const int shift)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return (uint32_t) (h >> shift);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


static void PrepareH5(H5 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint16_t * restrict num = self->num_;
  size_t partial_prepare_threshold = self->bucket_size_ >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH5(&data[i], self->hash_shift_);
      num[key] = 0;
    }

  }
  else
  {
    memset(num, 0, self->bucket_size_ * (sizeof(num[0])));
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH5(const uint8_t * restrict data, const int shift)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
None
----------------------------
***/


inline static void StoreH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH5(&data[ix & mask], self->hash_shift_);
  const size_t minor_ix = self->num_[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  self->buckets_[offset] = (uint32_t) ix;
  self->num_[key] += 1;
}


/*** DEPENDENCIES:
static uint32_t HashBytesH5(const uint8_t * restrict data, const int shift)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH5(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH5(&data[ix & mask], self->hash_shift_);
  const size_t minor_ix = self->num_[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  self->buckets_[offset] = (uint32_t) ix;
  self->num_[key] += 1;
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH5(H5 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


----------------------------
None
----------------------------
***/


inline static uint32_t HashBytesH6(const uint8_t * restrict data, const uint64_t mask, const int shift)
{
  const uint64_t h = (BrotliUnalignedRead64(data) & mask) * kHashMul64Long;
  return (uint32_t) (h >> shift);
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint64_t kHashMul64Long = (((uint64_t) 0x1FE35A7Bu) << 32) | 0xD3579BD3u
----------------------------
***/


static void PrepareH6(H6 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint16_t * restrict num = self->num_;
  size_t partial_prepare_threshold = self->bucket_size_ >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH6(&data[i], self->hash_mask_, self->hash_shift_);
      num[key] = 0;
    }

  }
  else
  {
    memset(num, 0, self->bucket_size_ * (sizeof(num[0])));
  }
}


/*** DEPENDENCIES:
inline static uint32_t HashBytesH6(const uint8_t * restrict data, const uint64_t mask, const int shift)
{
  const uint64_t h = (BrotliUnalignedRead64(data) & mask) * kHashMul64Long;
  return (uint32_t) (h >> shift);
}


----------------------------
None
----------------------------
***/


inline static void StoreH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const uint32_t key = HashBytesH6(&data[ix & mask], self->hash_mask_, self->hash_shift_);
  const size_t minor_ix = num[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  num[key] += 1;
  buckets[offset] = (uint32_t) ix;
}


/*** DEPENDENCIES:
inline static uint32_t HashBytesH6(const uint8_t * restrict data, const uint64_t mask, const int shift)
{
  const uint64_t h = (BrotliUnalignedRead64(data) & mask) * kHashMul64Long;
  return (uint32_t) (h >> shift);
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH6(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const uint32_t key = HashBytesH6(&data[ix & mask], self->hash_mask_, self->hash_shift_);
  const size_t minor_ix = num[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  num[key] += 1;
  buckets[offset] = (uint32_t) ix;
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH6(H6 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


----------------------------
None
----------------------------
***/


inline static size_t HashBytesH40(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


inline static size_t HashBytesH41(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


inline static size_t HashBytesH42(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


/*** DEPENDENCIES:
static const uint32_t kHashMul32 = 0x1E35A7BD
----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


static uint32_t HashBytesH54(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 7))) * kHashMul64;
  return (uint32_t) (h >> (64 - 20));
}


/*** DEPENDENCIES:
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
static const uint64_t kHashMul64 = (((uint64_t) 0x1E35A7BD) << 32) | 0x1E35A7BD
----------------------------
***/


inline static void PrepareDistanceCacheH54(H54 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void StoreHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
***/


inline static void StoreRangeHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix_start;
  (void) ix_end;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
***/


inline static void PrepareDistanceCacheHROLLING_FAST(HROLLING_FAST * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
***/


static void PrepareHROLLING(HROLLING * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 1)
  {
    self->state = HashRollingFunctionInitialHROLLING(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
static uint32_t HashRollingFunctionInitialHROLLING(uint32_t state, uint8_t add, uint32_t factor)
{
  return (uint32_t) ((factor * state) + HashByteHROLLING(add));
}


----------------------------
***/


inline static void StitchToPreviousBlockHROLLING(HROLLING * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  size_t position_masked;
  size_t available = num_bytes;
  if ((position & (1 - 1)) != 0)
  {
    size_t diff = 1 - (position & (1 - 1));
    available = (diff > available) ? (0) : (available - diff);
    position += diff;
  }
  position_masked = position & ring_buffer_mask;
  if (available > (ring_buffer_mask - position_masked))
  {
    available = ring_buffer_mask - position_masked;
  }
  PrepareHROLLING(self, 0, available, ringbuffer + (position & ring_buffer_mask));
  self->next_ix = position;
  (void) num_bytes;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
static void PrepareHROLLING(HROLLING * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 1)
  {
    self->state = HashRollingFunctionInitialHROLLING(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


----------------------------
***/


inline static size_t HashTypeLengthH35(void)
{
  size_t a = HashTypeLengthH3();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH3(void)
{
  return 8;
}


----------------------------
inline static size_t HashTypeLengthHROLLING_FAST(void)
{
  return 4;
}


----------------------------
***/


inline static size_t StoreLookaheadH35(void)
{
  size_t a = StoreLookaheadH3();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadHROLLING_FAST(void)
{
  return 4;
}


----------------------------
inline static size_t StoreLookaheadH3(void)
{
  return 8;
}


----------------------------
***/


inline static size_t HashTypeLengthH55(void)
{
  size_t a = HashTypeLengthH54();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH54(void)
{
  return 8;
}


----------------------------
inline static size_t HashTypeLengthHROLLING_FAST(void)
{
  return 4;
}


----------------------------
***/


inline static size_t StoreLookaheadH55(void)
{
  size_t a = StoreLookaheadH54();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadHROLLING_FAST(void)
{
  return 4;
}


----------------------------
inline static size_t StoreLookaheadH54(void)
{
  return 8;
}


----------------------------
***/


inline static size_t HashTypeLengthH65(void)
{
  size_t a = HashTypeLengthH6();
  size_t b = HashTypeLengthHROLLING();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH6(void)
{
  return 8;
}


----------------------------
inline static size_t HashTypeLengthHROLLING(void)
{
  return 4;
}


----------------------------
***/


inline static size_t StoreLookaheadH65(void)
{
  size_t a = StoreLookaheadH6();
  size_t b = StoreLookaheadHROLLING();
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH6(void)
{
  return 8;
}


----------------------------
inline static size_t StoreLookaheadHROLLING(void)
{
  return 4;
}


----------------------------
***/


inline static size_t MaxMetablockSize(const BrotliEncoderParams *params)
{
  int bits = brotli_min_int(ComputeRbBits(params), 24);
  return ((size_t) 1) << bits;
}


/*** DEPENDENCIES:
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static int ComputeRbBits(const BrotliEncoderParams *params)
{
  return 1 + brotli_max_int(params->lgwin, params->lgblock);
}


----------------------------
None
----------------------------
***/


inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


/*** DEPENDENCIES:
inline static void GetLengthCode(size_t insertlen, size_t copylen, int use_last_distance, uint16_t *code)
{
  uint16_t inscode = GetInsertLengthCode(insertlen);
  uint16_t copycode = GetCopyLengthCode(copylen);
  *code = CombineLengthCodes(inscode, copycode, use_last_distance);
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


// hint:  ['matches_idx_ref is a mutable refrence to unsigned int']
void helper_FindAllMatchesH10_1(unsigned int * const matches_idx_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, const size_t max_length, const size_t dictionary_distance, const BrotliEncoderParams * const params, BackwardMatch * const matches, const size_t cur_ix_masked, size_t best_len, uint32_t dict_matches[37 + 1])
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t minlen = brotli_max_size_t(4, best_len + 1);
  if (BrotliFindAllStaticDictionaryMatches(dictionary, &data[cur_ix_masked], minlen, max_length, &dict_matches[0]))
  {
    size_t maxlen = brotli_min_size_t(37, max_length);
    size_t l;
    for (l = minlen; l <= maxlen; l += 1)
    {
      uint32_t dict_id = dict_matches[l];
      if (dict_id < kInvalidMatch)
      {
        size_t distance = (dictionary_distance + (dict_id >> 5)) + 1;
        if (distance <= params->dist.max_distance)
        {
          InitDictionaryBackwardMatch(matches, distance, l, dict_id & 31);
          matches_idx += 1;
        }
      }
    }

  }
  *matches_idx_ref = matches_idx;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
inline static void InitDictionaryBackwardMatch(BackwardMatch *self, size_t dist, size_t len, size_t len_code)
{
  self->distance = (uint32_t) dist;
  self->length_and_code = (uint32_t) ((len << 5) | ((len == len_code) ? (0) : (len_code)));
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
int BrotliFindAllStaticDictionaryMatches(const BrotliEncoderDictionary *dictionary, const uint8_t *data, size_t min_length, size_t max_length, uint32_t *matches)
{
  int has_found_match = 0;
  {
    helper_BrotliFindAllStaticDictionaryMatches_4(&has_found_match, dictionary, data, min_length, max_length, matches);
  }
  if ((max_length >= 5) && ((data[0] == ' ') || (data[0] == '.')))
  {
    helper_BrotliFindAllStaticDictionaryMatches_3(&has_found_match, dictionary, data, max_length, matches);
  }
  if (max_length >= 6)
  {
    helper_BrotliFindAllStaticDictionaryMatches_1(&has_found_match, dictionary, data, max_length, matches);
  }
  if (max_length >= 9)
  {
    helper_BrotliFindAllStaticDictionaryMatches_2(&has_found_match, dictionary, data, max_length, matches);
  }
  return has_found_match;
}


----------------------------
static const uint32_t kInvalidMatch = 0xFFFFFFF
----------------------------
None
----------------------------
***/


// hint:  ['matches_idx_ref is a mutable refrence to unsigned int', 'best_len_ref is a mutable refrence to size_t']
void helper_FindAllMatchesH10_2(unsigned int * const matches_idx_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, BackwardMatch * const matches, const size_t cur_ix_masked, size_t i)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = i;
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((data[cur_ix_masked] != data[prev_ix]) || (data[cur_ix_masked + 1] != data[prev_ix + 1]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len > best_len)
    {
      best_len = len;
      InitBackwardMatch(matches, backward, len);
      matches_idx += 1;
    }
  }
  *matches_idx_ref = matches_idx;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
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
inline static void InitBackwardMatch(BackwardMatch *self, size_t dist, size_t len)
{
  self->distance = (uint32_t) dist;
  self->length_and_code = (uint32_t) (len << 5);
}


----------------------------
***/


inline static size_t FindAllMatchesH10(H10 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const BrotliEncoderParams *params, BackwardMatch *matches)
{
  unsigned int matches_idx = 0;
  BackwardMatch * const orig_matches = matches;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t best_len = 1;
  const size_t short_match_max_backward = (params->quality != 11) ? (16) : (64);
  size_t stop = cur_ix - short_match_max_backward;
  uint32_t dict_matches[37 + 1];
  size_t i;
  if (cur_ix < short_match_max_backward)
  {
    stop = 0;
  }
  for (i = cur_ix - 1; (i > stop) && (best_len <= 2); i -= 1)
  {
    helper_FindAllMatchesH10_2(&matches_idx, &best_len, data, ring_buffer_mask, cur_ix, max_length, max_backward, matches, cur_ix_masked, i);
  }

  if (best_len < max_length)
  {
    matches_idx = StoreAndFindMatchesH10(self, data, cur_ix, ring_buffer_mask, max_length, max_backward, &best_len, matches_idx);
  }
  for (i = 0; i <= 37; i += 1)
  {
    dict_matches[i] = kInvalidMatch;
  }

  {
    helper_FindAllMatchesH10_1(&matches_idx, dictionary, data, max_length, dictionary_distance, params, matches, cur_ix_masked, best_len, dict_matches);
  }
  return (size_t) ((&matches[matches_idx]) - orig_matches);
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static BackwardMatch *StoreAndFindMatchesH10(H10 * restrict self, const uint8_t * restrict data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const restrict best_len, BackwardMatch * restrict matches)
{
  unsigned int matches_idx = 0;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  const size_t max_comp_len = brotli_min_size_t(max_length, 128);
  const int should_reroot_tree = (!(!(max_length >= 128))) ? (1) : (0);
  const uint32_t key = HashBytesH10(&data[cur_ix_masked]);
  uint32_t * restrict buckets = self->buckets_;
  uint32_t * restrict forest = self->forest_;
  size_t prev_ix = buckets[key];
  size_t node_left = LeftChildIndexH10(self, cur_ix);
  size_t node_right = RightChildIndexH10(self, cur_ix);
  size_t best_len_left = 0;
  size_t best_len_right = 0;
  size_t depth_remaining;
  if (should_reroot_tree)
  {
    buckets[key] = (uint32_t) cur_ix;
  }
  for (depth_remaining = 64;; depth_remaining -= 1)
  {
    helper_StoreAndFindMatchesH10_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, cur_ix, ring_buffer_mask, max_length, max_backward, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, depth_remaining);
  }

  return matches;
}


----------------------------
void helper_FindAllMatchesH10_1(unsigned int * const matches_idx_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, const size_t max_length, const size_t dictionary_distance, const BrotliEncoderParams * const params, BackwardMatch * const matches, const size_t cur_ix_masked, size_t best_len, uint32_t dict_matches[37 + 1])
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t minlen = brotli_max_size_t(4, best_len + 1);
  if (BrotliFindAllStaticDictionaryMatches(dictionary, &data[cur_ix_masked], minlen, max_length, &dict_matches[0]))
  {
    size_t maxlen = brotli_min_size_t(37, max_length);
    size_t l;
    for (l = minlen; l <= maxlen; l += 1)
    {
      uint32_t dict_id = dict_matches[l];
      if (dict_id < kInvalidMatch)
      {
        size_t distance = (dictionary_distance + (dict_id >> 5)) + 1;
        if (distance <= params->dist.max_distance)
        {
          InitDictionaryBackwardMatch(matches, distance, l, dict_id & 31);
          matches_idx += 1;
        }
      }
    }

  }
  *matches_idx_ref = matches_idx;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
static const uint32_t kInvalidMatch = 0xFFFFFFF
----------------------------
void helper_FindAllMatchesH10_2(unsigned int * const matches_idx_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, BackwardMatch * const matches, const size_t cur_ix_masked, size_t i)
{
  unsigned int matches_idx = *matches_idx_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = i;
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((data[cur_ix_masked] != data[prev_ix]) || (data[cur_ix_masked + 1] != data[prev_ix + 1]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len > best_len)
    {
      best_len = len;
      InitBackwardMatch(matches, backward, len);
      matches_idx += 1;
    }
  }
  *matches_idx_ref = matches_idx;
  *best_len_ref = best_len;
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH5(H5 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH5() - 1)) && (position >= 3))
  {
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static void StoreH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH5(&data[ix & mask], self->hash_shift_);
  const size_t minor_ix = self->num_[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  self->buckets_[offset] = (uint32_t) ix;
  self->num_[key] += 1;
}


----------------------------
inline static size_t HashTypeLengthH5(void)
{
  return 4;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH3(H3 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH3() - 1)) && (position >= 3))
  {
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH3(void)
{
  return 8;
}


----------------------------
inline static void StoreH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH3(&data[ix & mask]);
  if ((1 << 1) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 1) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


inline static void StoreH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH54(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 20) - 1)] = (uint32_t) ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH54(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 7))) * kHashMul64;
  return (uint32_t) (h >> (64 - 20));
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH54(H54 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH54() - 1)) && (position >= 3))
  {
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static void StoreH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH54(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 20) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t HashTypeLengthH54(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH6(H6 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH6() - 1)) && (position >= 3))
  {
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH6(void)
{
  return 8;
}


----------------------------
inline static void StoreH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const uint32_t key = HashBytesH6(&data[ix & mask], self->hash_mask_, self->hash_shift_);
  const size_t minor_ix = num[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  num[key] += 1;
  buckets[offset] = (uint32_t) ix;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH65(H65 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH6(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


/*** DEPENDENCIES:
inline static void StitchToPreviousBlockH6(H6 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH6() - 1)) && (position >= 3))
  {
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockHROLLING(HROLLING * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  size_t position_masked;
  size_t available = num_bytes;
  if ((position & (1 - 1)) != 0)
  {
    size_t diff = 1 - (position & (1 - 1));
    available = (diff > available) ? (0) : (available - diff);
    position += diff;
  }
  position_masked = position & ring_buffer_mask;
  if (available > (ring_buffer_mask - position_masked))
  {
    available = ring_buffer_mask - position_masked;
  }
  PrepareHROLLING(self, 0, available, ringbuffer + (position & ring_buffer_mask));
  self->next_ix = position;
  (void) num_bytes;
}


----------------------------
None
----------------------------
***/


inline static void StoreH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t key = HashBytesH41(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


/*** DEPENDENCIES:
static uint16_t *HeadH41(void *extra)
{
  return (uint16_t *) (&AddrH41(extra)[1 << 15]);
}


----------------------------
static uint8_t *TinyHashH41(void *extra)
{
  return (uint8_t *) (&HeadH41(extra)[1 << 15]);
}


----------------------------
inline static size_t HashBytesH41(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
typedef struct BankH41
{
  SlotH41 slots[1 << 16];
} BankH41
----------------------------
static BankH41 *BanksH41(void *extra)
{
  return (BankH41 *) (&TinyHashH41(extra)[65536]);
}


----------------------------
static uint32_t *AddrH41(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH41(H41 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH41() - 1)) && (position >= 3))
  {
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static void StoreH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t key = HashBytesH41(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
inline static size_t HashTypeLengthH41(void)
{
  return 4;
}


----------------------------
None
----------------------------
***/


static void PrepareHROLLING_FAST(HROLLING_FAST * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 4)
  {
    self->state = HashRollingFunctionInitialHROLLING_FAST(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
static uint32_t HashRollingFunctionInitialHROLLING_FAST(uint32_t state, uint8_t add, uint32_t factor)
{
  return (uint32_t) ((factor * state) + HashByteHROLLING_FAST(add));
}


----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
***/


inline static void StitchToPreviousBlockHROLLING_FAST(HROLLING_FAST * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  size_t position_masked;
  size_t available = num_bytes;
  if ((position & (4 - 1)) != 0)
  {
    size_t diff = 4 - (position & (4 - 1));
    available = (diff > available) ? (0) : (available - diff);
    position += diff;
  }
  position_masked = position & ring_buffer_mask;
  if (available > (ring_buffer_mask - position_masked))
  {
    available = ring_buffer_mask - position_masked;
  }
  PrepareHROLLING_FAST(self, 0, available, ringbuffer + (position & ring_buffer_mask));
  self->next_ix = position;
  (void) num_bytes;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
static void PrepareHROLLING_FAST(HROLLING_FAST * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 4)
  {
    self->state = HashRollingFunctionInitialHROLLING_FAST(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


----------------------------
***/


inline static void StitchToPreviousBlockH35(H35 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH3(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING_FAST(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


/*** DEPENDENCIES:
inline static void StitchToPreviousBlockHROLLING_FAST(HROLLING_FAST * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  size_t position_masked;
  size_t available = num_bytes;
  if ((position & (4 - 1)) != 0)
  {
    size_t diff = 4 - (position & (4 - 1));
    available = (diff > available) ? (0) : (available - diff);
    position += diff;
  }
  position_masked = position & ring_buffer_mask;
  if (available > (ring_buffer_mask - position_masked))
  {
    available = ring_buffer_mask - position_masked;
  }
  PrepareHROLLING_FAST(self, 0, available, ringbuffer + (position & ring_buffer_mask));
  self->next_ix = position;
  (void) num_bytes;
}


----------------------------
inline static void StitchToPreviousBlockH3(H3 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH3() - 1)) && (position >= 3))
  {
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
None
----------------------------
***/


inline static void StoreH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t key = HashBytesH42(&data[ix & mask]);
  const size_t bank = key & (512 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 9) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


/*** DEPENDENCIES:
inline static size_t HashBytesH42(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static uint16_t *HeadH42(void *extra)
{
  return (uint16_t *) (&AddrH42(extra)[1 << 15]);
}


----------------------------
static BankH42 *BanksH42(void *extra)
{
  return (BankH42 *) (&TinyHashH42(extra)[65536]);
}


----------------------------
typedef struct BankH42
{
  SlotH42 slots[1 << 9];
} BankH42
----------------------------
static uint8_t *TinyHashH42(void *extra)
{
  return (uint8_t *) (&HeadH42(extra)[1 << 15]);
}


----------------------------
static uint32_t *AddrH42(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH42(H42 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH42() - 1)) && (position >= 3))
  {
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH42(void)
{
  return 4;
}


----------------------------
inline static void StoreH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t key = HashBytesH42(&data[ix & mask]);
  const size_t bank = key & (512 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 9) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH10(H10 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH10() - 1)) && (position >= 128))
  {
    const size_t i_start = (position - 128) + 1;
    const size_t i_end = brotli_min_size_t(position, i_start + num_bytes);
    size_t i;
    for (i = i_start; i < i_end; i += 1)
    {
      const size_t max_backward = self->window_mask_ - brotli_max_size_t(16 - 1, position - i);
      StoreAndFindMatchesH10(self, ringbuffer, i, ringbuffer_mask, 128, max_backward, 0, 0);
    }

  }
}


/*** DEPENDENCIES:
inline static BackwardMatch *StoreAndFindMatchesH10(H10 * restrict self, const uint8_t * restrict data, const size_t cur_ix, const size_t ring_buffer_mask, const size_t max_length, const size_t max_backward, size_t * const restrict best_len, BackwardMatch * restrict matches)
{
  unsigned int matches_idx = 0;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  const size_t max_comp_len = brotli_min_size_t(max_length, 128);
  const int should_reroot_tree = (!(!(max_length >= 128))) ? (1) : (0);
  const uint32_t key = HashBytesH10(&data[cur_ix_masked]);
  uint32_t * restrict buckets = self->buckets_;
  uint32_t * restrict forest = self->forest_;
  size_t prev_ix = buckets[key];
  size_t node_left = LeftChildIndexH10(self, cur_ix);
  size_t node_right = RightChildIndexH10(self, cur_ix);
  size_t best_len_left = 0;
  size_t best_len_right = 0;
  size_t depth_remaining;
  if (should_reroot_tree)
  {
    buckets[key] = (uint32_t) cur_ix;
  }
  for (depth_remaining = 64;; depth_remaining -= 1)
  {
    helper_StoreAndFindMatchesH10_1(&matches_idx, &prev_ix, &node_left, &node_right, &best_len_left, &best_len_right, self, data, cur_ix, ring_buffer_mask, max_length, max_backward, best_len, matches, cur_ix_masked, max_comp_len, should_reroot_tree, forest, depth_remaining);
  }

  return matches;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t HashTypeLengthH10(void)
{
  return 4;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
***/


inline static void StoreH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t key = HashBytesH40(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


/*** DEPENDENCIES:
static uint16_t *HeadH40(void *extra)
{
  return (uint16_t *) (&AddrH40(extra)[1 << 15]);
}


----------------------------
inline static size_t HashBytesH40(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static BankH40 *BanksH40(void *extra)
{
  return (BankH40 *) (&TinyHashH40(extra)[65536]);
}


----------------------------
static uint8_t *TinyHashH40(void *extra)
{
  return (uint8_t *) (&HeadH40(extra)[1 << 15]);
}


----------------------------
static uint32_t *AddrH40(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
typedef struct BankH40
{
  SlotH40 slots[1 << 16];
} BankH40
----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH40(H40 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH40() - 1)) && (position >= 3))
  {
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH40(void)
{
  return 4;
}


----------------------------
inline static void StoreH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t key = HashBytesH40(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


static void PrepareH54(H54 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 20) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH54(&data[i]);
      if ((1 << 2) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 2); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 20) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 20));
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH54(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 7))) * kHashMul64;
  return (uint32_t) (h >> (64 - 20));
}


----------------------------
None
----------------------------
***/


static void PrepareH40(H40 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH40(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


/*** DEPENDENCIES:
static uint8_t *TinyHashH40(void *extra)
{
  return (uint8_t *) (&HeadH40(extra)[1 << 15]);
}


----------------------------
static uint32_t *AddrH40(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
static uint16_t *HeadH40(void *extra)
{
  return (uint16_t *) (&AddrH40(extra)[1 << 15]);
}


----------------------------
inline static size_t HashBytesH40(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
None
----------------------------
***/


static void PrepareH42(H42 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH42(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


/*** DEPENDENCIES:
inline static size_t HashBytesH42(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static uint16_t *HeadH42(void *extra)
{
  return (uint16_t *) (&AddrH42(extra)[1 << 15]);
}


----------------------------
static uint32_t *AddrH42(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
static uint8_t *TinyHashH42(void *extra)
{
  return (uint8_t *) (&HeadH42(extra)[1 << 15]);
}


----------------------------
None
----------------------------
***/


static void InitializeHROLLING_FAST(HasherCommon *common, HROLLING_FAST * restrict self, const BrotliEncoderParams *params)
{
  size_t i;
  self->state = 0;
  self->next_ix = 0;
  self->factor = kRollingHashMul32HROLLING_FAST;
  self->factor_remove = 1;
  for (i = 0; i < 32; i += 4)
  {
    self->factor_remove *= self->factor;
  }

  self->table = (uint32_t *) common->extra;
  for (i = 0; i < 16777216; i += 1)
  {
    self->table[i] = kInvalidPosHROLLING_FAST;
  }

  (void) params;
}


/*** DEPENDENCIES:
static const uint32_t kInvalidPosHROLLING_FAST = 0xffffffff
----------------------------
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
static const uint32_t kRollingHashMul32HROLLING_FAST = 69069
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
None
----------------------------
***/


static void InitializeH54(HasherCommon *common, H54 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void PrepareH55(H55 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH54(self->params, one_shot, input_size);
    InitializeH54(self->common, &self->ha, self->params);
    InitializeHROLLING_FAST(&self->hb_common, &self->hb, self->params);
  }
  PrepareH54(&self->ha, one_shot, input_size, data);
  PrepareHROLLING_FAST(&self->hb, one_shot, input_size, data);
}


/*** DEPENDENCIES:
static void PrepareH54(H54 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 20) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH54(&data[i]);
      if ((1 << 2) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 2); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 20) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 20));
  }
}


----------------------------
static void InitializeHROLLING_FAST(HasherCommon *common, HROLLING_FAST * restrict self, const BrotliEncoderParams *params)
{
  size_t i;
  self->state = 0;
  self->next_ix = 0;
  self->factor = kRollingHashMul32HROLLING_FAST;
  self->factor_remove = 1;
  for (i = 0; i < 32; i += 4)
  {
    self->factor_remove *= self->factor;
  }

  self->table = (uint32_t *) common->extra;
  for (i = 0; i < 16777216; i += 1)
  {
    self->table[i] = kInvalidPosHROLLING_FAST;
  }

  (void) params;
}


----------------------------
inline static size_t HashMemAllocInBytesH54(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 20);
}


----------------------------
static void InitializeH54(HasherCommon *common, H54 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
static void PrepareHROLLING_FAST(HROLLING_FAST * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 4)
  {
    self->state = HashRollingFunctionInitialHROLLING_FAST(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


----------------------------
None
----------------------------
***/


static void InitializeH3(HasherCommon *common, H3 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void PrepareH35(H35 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH3(self->params, one_shot, input_size);
    InitializeH3(self->common, &self->ha, self->params);
    InitializeHROLLING_FAST(&self->hb_common, &self->hb, self->params);
  }
  PrepareH3(&self->ha, one_shot, input_size, data);
  PrepareHROLLING_FAST(&self->hb, one_shot, input_size, data);
}


/*** DEPENDENCIES:
static void InitializeHROLLING_FAST(HasherCommon *common, HROLLING_FAST * restrict self, const BrotliEncoderParams *params)
{
  size_t i;
  self->state = 0;
  self->next_ix = 0;
  self->factor = kRollingHashMul32HROLLING_FAST;
  self->factor_remove = 1;
  for (i = 0; i < 32; i += 4)
  {
    self->factor_remove *= self->factor;
  }

  self->table = (uint32_t *) common->extra;
  for (i = 0; i < 16777216; i += 1)
  {
    self->table[i] = kInvalidPosHROLLING_FAST;
  }

  (void) params;
}


----------------------------
static void PrepareH3(H3 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 16) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH3(&data[i]);
      if ((1 << 1) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 1); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 16) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 16));
  }
}


----------------------------
inline static size_t HashMemAllocInBytesH3(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


----------------------------
static void PrepareHROLLING_FAST(HROLLING_FAST * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 4)
  {
    self->state = HashRollingFunctionInitialHROLLING_FAST(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


----------------------------
static void InitializeH3(HasherCommon *common, H3 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
None
----------------------------
***/


static void InitializeHROLLING(HasherCommon *common, HROLLING * restrict self, const BrotliEncoderParams *params)
{
  size_t i;
  self->state = 0;
  self->next_ix = 0;
  self->factor = kRollingHashMul32HROLLING;
  self->factor_remove = 1;
  for (i = 0; i < 32; i += 1)
  {
    self->factor_remove *= self->factor;
  }

  self->table = (uint32_t *) common->extra;
  for (i = 0; i < 16777216; i += 1)
  {
    self->table[i] = kInvalidPosHROLLING;
  }

  (void) params;
}


/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
static const uint32_t kInvalidPosHROLLING = 0xffffffff
----------------------------
static const uint32_t kRollingHashMul32HROLLING = 69069
----------------------------
None
----------------------------
***/


static void InitializeH6(HasherCommon *common, H6 * restrict self, const BrotliEncoderParams *params)
{
  self->common_ = common;
  (void) params;
  self->hash_shift_ = 64 - common->params.bucket_bits;
  self->hash_mask_ = (~((uint64_t) 0U)) >> (64 - (8 * common->params.hash_len));
  self->bucket_size_ = ((size_t) 1) << common->params.bucket_bits;
  self->block_bits_ = common->params.block_bits;
  self->block_size_ = ((size_t) 1) << common->params.block_bits;
  self->block_mask_ = (uint32_t) (self->block_size_ - 1);
  self->num_last_distances_to_check_ = common->params.num_last_distances_to_check;
  self->num_ = (uint16_t *) common->extra;
  self->buckets_ = (uint32_t *) (&self->num_[self->bucket_size_]);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void PrepareH65(H65 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH6(self->params, one_shot, input_size);
    InitializeH6(self->common, &self->ha, self->params);
    InitializeHROLLING(&self->hb_common, &self->hb, self->params);
  }
  PrepareH6(&self->ha, one_shot, input_size, data);
  PrepareHROLLING(&self->hb, one_shot, input_size, data);
}


/*** DEPENDENCIES:
static void PrepareHROLLING(HROLLING * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  size_t i;
  if (input_size < 32)
  {
    return;
  }
  self->state = 0;
  for (i = 0; i < 32; i += 1)
  {
    self->state = HashRollingFunctionInitialHROLLING(self->state, data[i], self->factor);
  }

  (void) one_shot;
}


----------------------------
static void PrepareH6(H6 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint16_t * restrict num = self->num_;
  size_t partial_prepare_threshold = self->bucket_size_ >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH6(&data[i], self->hash_mask_, self->hash_shift_);
      num[key] = 0;
    }

  }
  else
  {
    memset(num, 0, self->bucket_size_ * (sizeof(num[0])));
  }
}


----------------------------
static void InitializeHROLLING(HasherCommon *common, HROLLING * restrict self, const BrotliEncoderParams *params)
{
  size_t i;
  self->state = 0;
  self->next_ix = 0;
  self->factor = kRollingHashMul32HROLLING;
  self->factor_remove = 1;
  for (i = 0; i < 32; i += 1)
  {
    self->factor_remove *= self->factor;
  }

  self->table = (uint32_t *) common->extra;
  for (i = 0; i < 16777216; i += 1)
  {
    self->table[i] = kInvalidPosHROLLING;
  }

  (void) params;
}


----------------------------
inline static size_t HashMemAllocInBytesH6(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


----------------------------
static void InitializeH6(HasherCommon *common, H6 * restrict self, const BrotliEncoderParams *params)
{
  self->common_ = common;
  (void) params;
  self->hash_shift_ = 64 - common->params.bucket_bits;
  self->hash_mask_ = (~((uint64_t) 0U)) >> (64 - (8 * common->params.hash_len));
  self->bucket_size_ = ((size_t) 1) << common->params.bucket_bits;
  self->block_bits_ = common->params.block_bits;
  self->block_size_ = ((size_t) 1) << common->params.block_bits;
  self->block_mask_ = (uint32_t) (self->block_size_ - 1);
  self->num_last_distances_to_check_ = common->params.num_last_distances_to_check;
  self->num_ = (uint16_t *) common->extra;
  self->buckets_ = (uint32_t *) (&self->num_[self->bucket_size_]);
}


----------------------------
None
----------------------------
***/


static void PrepareH41(H41 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH41(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


/*** DEPENDENCIES:
static uint8_t *TinyHashH41(void *extra)
{
  return (uint8_t *) (&HeadH41(extra)[1 << 15]);
}


----------------------------
static uint16_t *HeadH41(void *extra)
{
  return (uint16_t *) (&AddrH41(extra)[1 << 15]);
}


----------------------------
inline static size_t HashBytesH41(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static uint32_t *AddrH41(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
None
----------------------------
***/


void helper_HasherSetup_1(Hasher * const hasher, const uint8_t * const data, size_t position, size_t input_size, int one_shot)
{
  switch (hasher->common.params.type)
  {
    case 2:
    {
      PrepareH2(&hasher->privat._H2, one_shot, input_size, data);
      break;
    }

    case 3:
    {
      PrepareH3(&hasher->privat._H3, one_shot, input_size, data);
      break;
    }

    case 4:
    {
      PrepareH4(&hasher->privat._H4, one_shot, input_size, data);
      break;
    }

    case 5:
    {
      PrepareH5(&hasher->privat._H5, one_shot, input_size, data);
      break;
    }

    case 6:
    {
      PrepareH6(&hasher->privat._H6, one_shot, input_size, data);
      break;
    }

    case 40:
    {
      PrepareH40(&hasher->privat._H40, one_shot, input_size, data);
      break;
    }

    case 41:
    {
      PrepareH41(&hasher->privat._H41, one_shot, input_size, data);
      break;
    }

    case 42:
    {
      PrepareH42(&hasher->privat._H42, one_shot, input_size, data);
      break;
    }

    case 54:
    {
      PrepareH54(&hasher->privat._H54, one_shot, input_size, data);
      break;
    }

    case 35:
    {
      PrepareH35(&hasher->privat._H35, one_shot, input_size, data);
      break;
    }

    case 55:
    {
      PrepareH55(&hasher->privat._H55, one_shot, input_size, data);
      break;
    }

    case 65:
    {
      PrepareH65(&hasher->privat._H65, one_shot, input_size, data);
      break;
    }

    case 10:
    {
      PrepareH10(&hasher->privat._H10, one_shot, input_size, data);
      break;
    }

    default:
    {
      break;
    }

  }

  if (position == 0)
  {
    hasher->common.dict_num_lookups = 0;
    hasher->common.dict_num_matches = 0;
  }
  hasher->common.is_prepared_ = 1;
}


/*** DEPENDENCIES:
static void PrepareH54(H54 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 20) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH54(&data[i]);
      if ((1 << 2) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 2); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 20) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 20));
  }
}


----------------------------
static void PrepareH40(H40 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH40(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


----------------------------
static void PrepareH4(H4 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 17) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH4(&data[i]);
      if ((1 << 2) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 2); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 17) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 17));
  }
}


----------------------------
static void PrepareH42(H42 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH42(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


----------------------------
static void PrepareH6(H6 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint16_t * restrict num = self->num_;
  size_t partial_prepare_threshold = self->bucket_size_ >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH6(&data[i], self->hash_mask_, self->hash_shift_);
      num[key] = 0;
    }

  }
  else
  {
    memset(num, 0, self->bucket_size_ * (sizeof(num[0])));
  }
}


----------------------------
static void PrepareH3(H3 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 16) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH3(&data[i]);
      if ((1 << 1) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 1); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 16) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 16));
  }
}


----------------------------
static void PrepareH55(H55 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH54(self->params, one_shot, input_size);
    InitializeH54(self->common, &self->ha, self->params);
    InitializeHROLLING_FAST(&self->hb_common, &self->hb, self->params);
  }
  PrepareH54(&self->ha, one_shot, input_size, data);
  PrepareHROLLING_FAST(&self->hb, one_shot, input_size, data);
}


----------------------------
static void PrepareH35(H35 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH3(self->params, one_shot, input_size);
    InitializeH3(self->common, &self->ha, self->params);
    InitializeHROLLING_FAST(&self->hb_common, &self->hb, self->params);
  }
  PrepareH3(&self->ha, one_shot, input_size, data);
  PrepareHROLLING_FAST(&self->hb, one_shot, input_size, data);
}


----------------------------
static void PrepareH65(H65 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  if (self->fresh)
  {
    self->fresh = 0;
    self->hb_common.extra = ((uint8_t *) self->extra) + HashMemAllocInBytesH6(self->params, one_shot, input_size);
    InitializeH6(self->common, &self->ha, self->params);
    InitializeHROLLING(&self->hb_common, &self->hb, self->params);
  }
  PrepareH6(&self->ha, one_shot, input_size, data);
  PrepareHROLLING(&self->hb, one_shot, input_size, data);
}


----------------------------
static void PrepareH10(H10 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t invalid_pos = self->invalid_pos_;
  uint32_t i;
  uint32_t * restrict buckets = self->buckets_;
  (void) data;
  (void) one_shot;
  (void) input_size;
  for (i = 0; i < (1 << 17); i += 1)
  {
    buckets[i] = invalid_pos;
  }

}


----------------------------
static void PrepareH41(H41 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  size_t partial_prepare_threshold = (1 << 15) >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      size_t bucket = HashBytesH41(&data[i]);
      addr[bucket] = 0xCCCCCCCC;
      head[bucket] = 0xCCCC;
    }

  }
  else
  {
    memset(addr, 0xCC, (sizeof(uint32_t)) * (1 << 15));
    memset(head, 0, (sizeof(uint16_t)) * (1 << 15));
  }
  memset(tiny_hash, 0, (sizeof(uint8_t)) * 65536);
  memset(self->free_slot_idx, 0, sizeof(self->free_slot_idx));
}


----------------------------
static void PrepareH2(H2 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint32_t * restrict buckets = self->buckets_;
  size_t partial_prepare_threshold = (1 << 16) >> 5;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH2(&data[i]);
      if ((1 << 0) == 1)
      {
        buckets[key] = 0;
      }
      else
      {
        uint32_t j;
        for (j = 0; j < (1 << 0); j += 1)
        {
          buckets[(key + (j << 3)) & ((1 << 16) - 1)] = 0;
        }

      }
    }

  }
  else
  {
    memset(buckets, 0, (sizeof(uint32_t)) * (1 << 16));
  }
}


----------------------------
static void PrepareH5(H5 * restrict self, int one_shot, size_t input_size, const uint8_t * restrict data)
{
  uint16_t * restrict num = self->num_;
  size_t partial_prepare_threshold = self->bucket_size_ >> 6;
  if (one_shot && (input_size <= partial_prepare_threshold))
  {
    size_t i;
    for (i = 0; i < input_size; i += 1)
    {
      const uint32_t key = HashBytesH5(&data[i], self->hash_shift_);
      num[key] = 0;
    }

  }
  else
  {
    memset(num, 0, self->bucket_size_ * (sizeof(num[0])));
  }
}


----------------------------
None
----------------------------
***/


static void InitializeH42(HasherCommon *common, H42 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH65(HasherCommon *common, H65 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH2(HasherCommon *common, H2 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH5(HasherCommon *common, H5 * restrict self, const BrotliEncoderParams *params)
{
  self->common_ = common;
  (void) params;
  self->hash_shift_ = 32 - common->params.bucket_bits;
  self->bucket_size_ = ((size_t) 1) << common->params.bucket_bits;
  self->block_size_ = ((size_t) 1) << common->params.block_bits;
  self->block_mask_ = (uint32_t) (self->block_size_ - 1);
  self->num_ = (uint16_t *) common->extra;
  self->buckets_ = (uint32_t *) (&self->num_[self->bucket_size_]);
  self->block_bits_ = common->params.block_bits;
  self->num_last_distances_to_check_ = common->params.num_last_distances_to_check;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH4(HasherCommon *common, H4 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH35(HasherCommon *common, H35 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH10(HasherCommon *common, H10 * restrict self, const BrotliEncoderParams *params)
{
  self->buckets_ = (uint32_t *) common->extra;
  self->forest_ = &self->buckets_[1 << 17];
  self->window_mask_ = (1u << params->lgwin) - 1u;
  self->invalid_pos_ = (uint32_t) (0 - self->window_mask_);
}


/*** DEPENDENCIES:
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
None
----------------------------
***/


static void InitializeH40(HasherCommon *common, H40 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH65(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH6(params, one_shot, input_size) + HashMemAllocInBytesHROLLING(params, one_shot, input_size);
}


/*** DEPENDENCIES:
inline static size_t HashMemAllocInBytesH6(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


----------------------------
inline static size_t HashMemAllocInBytesHROLLING(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return 16777216 * (sizeof(uint32_t));
  (void) params;
  (void) one_shot;
  (void) input_size;
}


----------------------------
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH55(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH54(params, one_shot, input_size) + HashMemAllocInBytesHROLLING_FAST(params, one_shot, input_size);
}


/*** DEPENDENCIES:
inline static size_t HashMemAllocInBytesH54(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 20);
}


----------------------------
inline static size_t HashMemAllocInBytesHROLLING_FAST(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return 16777216 * (sizeof(uint32_t));
  (void) params;
  (void) one_shot;
  (void) input_size;
}


----------------------------
None
----------------------------
***/


inline static size_t HashMemAllocInBytesH35(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH3(params, one_shot, input_size) + HashMemAllocInBytesHROLLING_FAST(params, one_shot, input_size);
}


/*** DEPENDENCIES:
inline static size_t HashMemAllocInBytesH3(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


----------------------------
inline static size_t HashMemAllocInBytesHROLLING_FAST(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return 16777216 * (sizeof(uint32_t));
  (void) params;
  (void) one_shot;
  (void) input_size;
}


----------------------------
None
----------------------------
***/


inline static size_t HasherSize(const BrotliEncoderParams *params, int one_shot, const size_t input_size)
{
  switch (params->hasher.type)
  {
    case 2:
    {
      return HashMemAllocInBytesH2(params, one_shot, input_size);
    }

    case 3:
    {
      return HashMemAllocInBytesH3(params, one_shot, input_size);
    }

    case 4:
    {
      return HashMemAllocInBytesH4(params, one_shot, input_size);
    }

    case 5:
    {
      return HashMemAllocInBytesH5(params, one_shot, input_size);
    }

    case 6:
    {
      return HashMemAllocInBytesH6(params, one_shot, input_size);
    }

    case 40:
    {
      return HashMemAllocInBytesH40(params, one_shot, input_size);
    }

    case 41:
    {
      return HashMemAllocInBytesH41(params, one_shot, input_size);
    }

    case 42:
    {
      return HashMemAllocInBytesH42(params, one_shot, input_size);
    }

    case 54:
    {
      return HashMemAllocInBytesH54(params, one_shot, input_size);
    }

    case 35:
    {
      return HashMemAllocInBytesH35(params, one_shot, input_size);
    }

    case 55:
    {
      return HashMemAllocInBytesH55(params, one_shot, input_size);
    }

    case 65:
    {
      return HashMemAllocInBytesH65(params, one_shot, input_size);
    }

    case 10:
    {
      return HashMemAllocInBytesH10(params, one_shot, input_size);
    }

    default:
    {
      break;
    }

  }

  return 0;
}


/*** DEPENDENCIES:
inline static size_t HashMemAllocInBytesH4(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 17);
}


----------------------------
inline static size_t HashMemAllocInBytesH5(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


----------------------------
inline static size_t HashMemAllocInBytesH10(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t num_nodes = ((size_t) 1) << params->lgwin;
  if (one_shot && (input_size < num_nodes))
  {
    num_nodes = input_size;
  }
  return ((sizeof(uint32_t)) * (1 << 17)) + ((2 * (sizeof(uint32_t))) * num_nodes);
}


----------------------------
inline static size_t HashMemAllocInBytesH54(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 20);
}


----------------------------
inline static size_t HashMemAllocInBytesH42(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH42)) * 512);
}


----------------------------
inline static size_t HashMemAllocInBytesH65(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH6(params, one_shot, input_size) + HashMemAllocInBytesHROLLING(params, one_shot, input_size);
}


----------------------------
inline static size_t HashMemAllocInBytesH6(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  size_t bucket_size = ((size_t) 1) << params->hasher.bucket_bits;
  size_t block_size = ((size_t) 1) << params->hasher.block_bits;
  (void) one_shot;
  (void) input_size;
  return ((sizeof(uint16_t)) * bucket_size) + (((sizeof(uint32_t)) * bucket_size) * block_size);
}


----------------------------
inline static size_t HashMemAllocInBytesH3(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


----------------------------
inline static size_t HashMemAllocInBytesH2(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return (sizeof(uint32_t)) * (1 << 16);
}


----------------------------
inline static size_t HashMemAllocInBytesH55(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH54(params, one_shot, input_size) + HashMemAllocInBytesHROLLING_FAST(params, one_shot, input_size);
}


----------------------------
inline static size_t HashMemAllocInBytesH35(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  return HashMemAllocInBytesH3(params, one_shot, input_size) + HashMemAllocInBytesHROLLING_FAST(params, one_shot, input_size);
}


----------------------------
inline static size_t HashMemAllocInBytesH41(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH41)) * 1);
}


----------------------------
inline static size_t HashMemAllocInBytesH40(const BrotliEncoderParams *params, int one_shot, size_t input_size)
{
  (void) params;
  (void) one_shot;
  (void) input_size;
  return ((((sizeof(uint32_t)) * (1 << 15)) + ((sizeof(uint16_t)) * (1 << 15))) + ((sizeof(uint8_t)) * 65536)) + ((sizeof(BankH40)) * 1);
}


----------------------------
None
----------------------------
***/


inline static void ChooseHasher(const BrotliEncoderParams *params, BrotliHasherParams *hparams)
{
  if (params->quality > 9)
  {
    hparams->type = 10;
  }
  else
    if ((params->quality == 4) && (params->size_hint >= (1 << 20)))
  {
    hparams->type = 54;
  }
  else
    if (params->quality < 5)
  {
    hparams->type = params->quality;
  }
  else
    if (params->lgwin <= 16)
  {
    hparams->type = (params->quality < 7) ? (40) : ((params->quality < 9) ? (41) : (42));
  }
  else
    if ((params->size_hint >= (1 << 20)) && (params->lgwin >= 19))
  {
    hparams->type = 6;
    hparams->block_bits = params->quality - 1;
    hparams->bucket_bits = 15;
    hparams->hash_len = 5;
    hparams->num_last_distances_to_check = (params->quality < 7) ? (4) : ((params->quality < 9) ? (10) : (16));
  }
  else
  {
    hparams->type = 5;
    hparams->block_bits = params->quality - 1;
    hparams->bucket_bits = (params->quality < 7) ? (14) : (15);
    hparams->num_last_distances_to_check = (params->quality < 7) ? (4) : ((params->quality < 9) ? (10) : (16));
  }
  if (params->lgwin > 24)
  {
    if (hparams->type == 3)
    {
      hparams->type = 35;
    }
    if (hparams->type == 54)
    {
      hparams->type = 55;
    }
    if (hparams->type == 6)
    {
      hparams->type = 65;
    }
  }
}


/*** DEPENDENCIES:
typedef struct BrotliHasherParams
{
  int type;
  int bucket_bits;
  int block_bits;
  int hash_len;
  int num_last_distances_to_check;
} BrotliHasherParams
----------------------------
None
----------------------------
***/


static void InitializeH41(HasherCommon *common, H41 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void InitializeH55(HasherCommon *common, H55 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void helper_HasherSetup_2(MemoryManager * const m, Hasher * const hasher, BrotliEncoderParams * const params, size_t input_size, int one_shot)
{
  size_t alloc_size;
  ChooseHasher(params, &params->hasher);
  alloc_size = HasherSize(params, one_shot, input_size);
  hasher->common.extra = (alloc_size > 0) ? ((uint8_t *) BrotliAllocate(m, alloc_size * (sizeof(uint8_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  hasher->common.params = params->hasher;
  switch (hasher->common.params.type)
  {
    case 2:
    {
      InitializeH2(&hasher->common, &hasher->privat._H2, params);
      break;
    }

    case 3:
    {
      InitializeH3(&hasher->common, &hasher->privat._H3, params);
      break;
    }

    case 4:
    {
      InitializeH4(&hasher->common, &hasher->privat._H4, params);
      break;
    }

    case 5:
    {
      InitializeH5(&hasher->common, &hasher->privat._H5, params);
      break;
    }

    case 6:
    {
      InitializeH6(&hasher->common, &hasher->privat._H6, params);
      break;
    }

    case 40:
    {
      InitializeH40(&hasher->common, &hasher->privat._H40, params);
      break;
    }

    case 41:
    {
      InitializeH41(&hasher->common, &hasher->privat._H41, params);
      break;
    }

    case 42:
    {
      InitializeH42(&hasher->common, &hasher->privat._H42, params);
      break;
    }

    case 54:
    {
      InitializeH54(&hasher->common, &hasher->privat._H54, params);
      break;
    }

    case 35:
    {
      InitializeH35(&hasher->common, &hasher->privat._H35, params);
      break;
    }

    case 55:
    {
      InitializeH55(&hasher->common, &hasher->privat._H55, params);
      break;
    }

    case 65:
    {
      InitializeH65(&hasher->common, &hasher->privat._H65, params);
      break;
    }

    case 10:
    {
      InitializeH10(&hasher->common, &hasher->privat._H10, params);
      break;
      ;
    }

    default:
    {
      break;
    }

  }

  HasherReset(hasher);
}


/*** DEPENDENCIES:
static void InitializeH42(HasherCommon *common, H42 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
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
static void InitializeH65(HasherCommon *common, H65 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


----------------------------
static void InitializeH2(HasherCommon *common, H2 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
static void InitializeH5(HasherCommon *common, H5 * restrict self, const BrotliEncoderParams *params)
{
  self->common_ = common;
  (void) params;
  self->hash_shift_ = 32 - common->params.bucket_bits;
  self->bucket_size_ = ((size_t) 1) << common->params.bucket_bits;
  self->block_size_ = ((size_t) 1) << common->params.block_bits;
  self->block_mask_ = (uint32_t) (self->block_size_ - 1);
  self->num_ = (uint16_t *) common->extra;
  self->buckets_ = (uint32_t *) (&self->num_[self->bucket_size_]);
  self->block_bits_ = common->params.block_bits;
  self->num_last_distances_to_check_ = common->params.num_last_distances_to_check;
}


----------------------------
inline static void HasherReset(Hasher *hasher)
{
  hasher->common.is_prepared_ = 0;
}


----------------------------
static void InitializeH4(HasherCommon *common, H4 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
static void InitializeH35(HasherCommon *common, H35 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


----------------------------
static void InitializeH10(HasherCommon *common, H10 * restrict self, const BrotliEncoderParams *params)
{
  self->buckets_ = (uint32_t *) common->extra;
  self->forest_ = &self->buckets_[1 << 17];
  self->window_mask_ = (1u << params->lgwin) - 1u;
  self->invalid_pos_ = (uint32_t) (0 - self->window_mask_);
}


----------------------------
static void InitializeH40(HasherCommon *common, H40 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
}


----------------------------
static void InitializeH54(HasherCommon *common, H54 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
inline static size_t HasherSize(const BrotliEncoderParams *params, int one_shot, const size_t input_size)
{
  switch (params->hasher.type)
  {
    case 2:
    {
      return HashMemAllocInBytesH2(params, one_shot, input_size);
    }

    case 3:
    {
      return HashMemAllocInBytesH3(params, one_shot, input_size);
    }

    case 4:
    {
      return HashMemAllocInBytesH4(params, one_shot, input_size);
    }

    case 5:
    {
      return HashMemAllocInBytesH5(params, one_shot, input_size);
    }

    case 6:
    {
      return HashMemAllocInBytesH6(params, one_shot, input_size);
    }

    case 40:
    {
      return HashMemAllocInBytesH40(params, one_shot, input_size);
    }

    case 41:
    {
      return HashMemAllocInBytesH41(params, one_shot, input_size);
    }

    case 42:
    {
      return HashMemAllocInBytesH42(params, one_shot, input_size);
    }

    case 54:
    {
      return HashMemAllocInBytesH54(params, one_shot, input_size);
    }

    case 35:
    {
      return HashMemAllocInBytesH35(params, one_shot, input_size);
    }

    case 55:
    {
      return HashMemAllocInBytesH55(params, one_shot, input_size);
    }

    case 65:
    {
      return HashMemAllocInBytesH65(params, one_shot, input_size);
    }

    case 10:
    {
      return HashMemAllocInBytesH10(params, one_shot, input_size);
    }

    default:
    {
      break;
    }

  }

  return 0;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void InitializeH6(HasherCommon *common, H6 * restrict self, const BrotliEncoderParams *params)
{
  self->common_ = common;
  (void) params;
  self->hash_shift_ = 64 - common->params.bucket_bits;
  self->hash_mask_ = (~((uint64_t) 0U)) >> (64 - (8 * common->params.hash_len));
  self->bucket_size_ = ((size_t) 1) << common->params.bucket_bits;
  self->block_bits_ = common->params.block_bits;
  self->block_size_ = ((size_t) 1) << common->params.block_bits;
  self->block_mask_ = (uint32_t) (self->block_size_ - 1);
  self->num_last_distances_to_check_ = common->params.num_last_distances_to_check;
  self->num_ = (uint16_t *) common->extra;
  self->buckets_ = (uint32_t *) (&self->num_[self->bucket_size_]);
}


----------------------------
inline static void ChooseHasher(const BrotliEncoderParams *params, BrotliHasherParams *hparams)
{
  if (params->quality > 9)
  {
    hparams->type = 10;
  }
  else
    if ((params->quality == 4) && (params->size_hint >= (1 << 20)))
  {
    hparams->type = 54;
  }
  else
    if (params->quality < 5)
  {
    hparams->type = params->quality;
  }
  else
    if (params->lgwin <= 16)
  {
    hparams->type = (params->quality < 7) ? (40) : ((params->quality < 9) ? (41) : (42));
  }
  else
    if ((params->size_hint >= (1 << 20)) && (params->lgwin >= 19))
  {
    hparams->type = 6;
    hparams->block_bits = params->quality - 1;
    hparams->bucket_bits = 15;
    hparams->hash_len = 5;
    hparams->num_last_distances_to_check = (params->quality < 7) ? (4) : ((params->quality < 9) ? (10) : (16));
  }
  else
  {
    hparams->type = 5;
    hparams->block_bits = params->quality - 1;
    hparams->bucket_bits = (params->quality < 7) ? (14) : (15);
    hparams->num_last_distances_to_check = (params->quality < 7) ? (4) : ((params->quality < 9) ? (10) : (16));
  }
  if (params->lgwin > 24)
  {
    if (hparams->type == 3)
    {
      hparams->type = 35;
    }
    if (hparams->type == 54)
    {
      hparams->type = 55;
    }
    if (hparams->type == 6)
    {
      hparams->type = 65;
    }
  }
}


----------------------------
static void InitializeH41(HasherCommon *common, H41 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->max_hops = ((params->quality > 6) ? (7u) : (8u)) << (params->quality - 4);
}


----------------------------
static void InitializeH55(HasherCommon *common, H55 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  self->extra = common->extra;
  self->hb_common = *self->common;
  self->fresh = 1;
  self->params = params;
}


----------------------------
static void InitializeH3(HasherCommon *common, H3 * restrict self, const BrotliEncoderParams *params)
{
  self->common = common;
  (void) params;
  self->buckets_ = (uint32_t *) common->extra;
}


----------------------------
None
----------------------------
***/


inline static void HasherSetup(MemoryManager *m, Hasher *hasher, BrotliEncoderParams *params, const uint8_t *data, size_t position, size_t input_size, int is_last)
{
  int one_shot = (position == 0) && is_last;
  if (hasher->common.extra == 0)
  {
    helper_HasherSetup_2(m, hasher, params, input_size, one_shot);
  }
  if (!hasher->common.is_prepared_)
  {
    helper_HasherSetup_1(hasher, data, position, input_size, one_shot);
  }
}


/*** DEPENDENCIES:
void helper_HasherSetup_1(Hasher * const hasher, const uint8_t * const data, size_t position, size_t input_size, int one_shot)
{
  switch (hasher->common.params.type)
  {
    case 2:
    {
      PrepareH2(&hasher->privat._H2, one_shot, input_size, data);
      break;
    }

    case 3:
    {
      PrepareH3(&hasher->privat._H3, one_shot, input_size, data);
      break;
    }

    case 4:
    {
      PrepareH4(&hasher->privat._H4, one_shot, input_size, data);
      break;
    }

    case 5:
    {
      PrepareH5(&hasher->privat._H5, one_shot, input_size, data);
      break;
    }

    case 6:
    {
      PrepareH6(&hasher->privat._H6, one_shot, input_size, data);
      break;
    }

    case 40:
    {
      PrepareH40(&hasher->privat._H40, one_shot, input_size, data);
      break;
    }

    case 41:
    {
      PrepareH41(&hasher->privat._H41, one_shot, input_size, data);
      break;
    }

    case 42:
    {
      PrepareH42(&hasher->privat._H42, one_shot, input_size, data);
      break;
    }

    case 54:
    {
      PrepareH54(&hasher->privat._H54, one_shot, input_size, data);
      break;
    }

    case 35:
    {
      PrepareH35(&hasher->privat._H35, one_shot, input_size, data);
      break;
    }

    case 55:
    {
      PrepareH55(&hasher->privat._H55, one_shot, input_size, data);
      break;
    }

    case 65:
    {
      PrepareH65(&hasher->privat._H65, one_shot, input_size, data);
      break;
    }

    case 10:
    {
      PrepareH10(&hasher->privat._H10, one_shot, input_size, data);
      break;
    }

    default:
    {
      break;
    }

  }

  if (position == 0)
  {
    hasher->common.dict_num_lookups = 0;
    hasher->common.dict_num_matches = 0;
  }
  hasher->common.is_prepared_ = 1;
}


----------------------------
void helper_HasherSetup_2(MemoryManager * const m, Hasher * const hasher, BrotliEncoderParams * const params, size_t input_size, int one_shot)
{
  size_t alloc_size;
  ChooseHasher(params, &params->hasher);
  alloc_size = HasherSize(params, one_shot, input_size);
  hasher->common.extra = (alloc_size > 0) ? ((uint8_t *) BrotliAllocate(m, alloc_size * (sizeof(uint8_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  hasher->common.params = params->hasher;
  switch (hasher->common.params.type)
  {
    case 2:
    {
      InitializeH2(&hasher->common, &hasher->privat._H2, params);
      break;
    }

    case 3:
    {
      InitializeH3(&hasher->common, &hasher->privat._H3, params);
      break;
    }

    case 4:
    {
      InitializeH4(&hasher->common, &hasher->privat._H4, params);
      break;
    }

    case 5:
    {
      InitializeH5(&hasher->common, &hasher->privat._H5, params);
      break;
    }

    case 6:
    {
      InitializeH6(&hasher->common, &hasher->privat._H6, params);
      break;
    }

    case 40:
    {
      InitializeH40(&hasher->common, &hasher->privat._H40, params);
      break;
    }

    case 41:
    {
      InitializeH41(&hasher->common, &hasher->privat._H41, params);
      break;
    }

    case 42:
    {
      InitializeH42(&hasher->common, &hasher->privat._H42, params);
      break;
    }

    case 54:
    {
      InitializeH54(&hasher->common, &hasher->privat._H54, params);
      break;
    }

    case 35:
    {
      InitializeH35(&hasher->common, &hasher->privat._H35, params);
      break;
    }

    case 55:
    {
      InitializeH55(&hasher->common, &hasher->privat._H55, params);
      break;
    }

    case 65:
    {
      InitializeH65(&hasher->common, &hasher->privat._H65, params);
      break;
    }

    case 10:
    {
      InitializeH10(&hasher->common, &hasher->privat._H10, params);
      break;
      ;
    }

    default:
    {
      break;
    }

  }

  HasherReset(hasher);
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


inline static void StitchToPreviousBlockH2(H2 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH2() - 1)) && (position >= 3))
  {
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static void StoreH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH2(&data[ix & mask]);
  if ((1 << 0) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 0) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t HashTypeLengthH2(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH4(H4 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH4() - 1)) && (position >= 3))
  {
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


/*** DEPENDENCIES:
inline static void StoreH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH4(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 17) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t HashTypeLengthH4(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


inline static void StitchToPreviousBlockH55(H55 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH54(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING_FAST(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


/*** DEPENDENCIES:
inline static void StitchToPreviousBlockH54(H54 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH54() - 1)) && (position >= 3))
  {
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockHROLLING_FAST(HROLLING_FAST * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  size_t position_masked;
  size_t available = num_bytes;
  if ((position & (4 - 1)) != 0)
  {
    size_t diff = 4 - (position & (4 - 1));
    available = (diff > available) ? (0) : (available - diff);
    position += diff;
  }
  position_masked = position & ring_buffer_mask;
  if (available > (ring_buffer_mask - position_masked))
  {
    available = ring_buffer_mask - position_masked;
  }
  PrepareHROLLING_FAST(self, 0, available, ringbuffer + (position & ring_buffer_mask));
  self->next_ix = position;
  (void) num_bytes;
}


----------------------------
None
----------------------------
***/


inline static void InitOrStitchToPreviousBlock(MemoryManager *m, Hasher *hasher, const uint8_t *data, size_t mask, BrotliEncoderParams *params, size_t position, size_t input_size, int is_last)
{
  HasherSetup(m, hasher, params, data, position, input_size, is_last);
  if (!(!0))
  {
    return;
  }
  switch (hasher->common.params.type)
  {
    case 2:
    {
      StitchToPreviousBlockH2(&hasher->privat._H2, input_size, position, data, mask);
      break;
    }

    case 3:
    {
      StitchToPreviousBlockH3(&hasher->privat._H3, input_size, position, data, mask);
      break;
    }

    case 4:
    {
      StitchToPreviousBlockH4(&hasher->privat._H4, input_size, position, data, mask);
      break;
    }

    case 5:
    {
      StitchToPreviousBlockH5(&hasher->privat._H5, input_size, position, data, mask);
      break;
    }

    case 6:
    {
      StitchToPreviousBlockH6(&hasher->privat._H6, input_size, position, data, mask);
      break;
    }

    case 40:
    {
      StitchToPreviousBlockH40(&hasher->privat._H40, input_size, position, data, mask);
      break;
    }

    case 41:
    {
      StitchToPreviousBlockH41(&hasher->privat._H41, input_size, position, data, mask);
      break;
    }

    case 42:
    {
      StitchToPreviousBlockH42(&hasher->privat._H42, input_size, position, data, mask);
      break;
    }

    case 54:
    {
      StitchToPreviousBlockH54(&hasher->privat._H54, input_size, position, data, mask);
      break;
    }

    case 35:
    {
      StitchToPreviousBlockH35(&hasher->privat._H35, input_size, position, data, mask);
      break;
    }

    case 55:
    {
      StitchToPreviousBlockH55(&hasher->privat._H55, input_size, position, data, mask);
      break;
    }

    case 65:
    {
      StitchToPreviousBlockH65(&hasher->privat._H65, input_size, position, data, mask);
      break;
    }

    case 10:
    {
      StitchToPreviousBlockH10(&hasher->privat._H10, input_size, position, data, mask);
      break;
    }

    default:
    {
      break;
    }

  }

}


/*** DEPENDENCIES:
inline static void StitchToPreviousBlockH5(H5 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH5() - 1)) && (position >= 3))
  {
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH5(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH3(H3 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH3() - 1)) && (position >= 3))
  {
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH3(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH54(H54 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH54() - 1)) && (position >= 3))
  {
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH54(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH65(H65 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH6(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


----------------------------
inline static void StitchToPreviousBlockH41(H41 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH41() - 1)) && (position >= 3))
  {
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH41(self, ringbuffer, ring_buffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH35(H35 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH3(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING_FAST(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


----------------------------
inline static void StitchToPreviousBlockH42(H42 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH42() - 1)) && (position >= 3))
  {
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH42(self, ringbuffer, ring_buffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH10(H10 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH10() - 1)) && (position >= 128))
  {
    const size_t i_start = (position - 128) + 1;
    const size_t i_end = brotli_min_size_t(position, i_start + num_bytes);
    size_t i;
    for (i = i_start; i < i_end; i += 1)
    {
      const size_t max_backward = self->window_mask_ - brotli_max_size_t(16 - 1, position - i);
      StoreAndFindMatchesH10(self, ringbuffer, i, ringbuffer_mask, 128, max_backward, 0, 0);
    }

  }
}


----------------------------
inline static void StitchToPreviousBlockH6(H6 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH6() - 1)) && (position >= 3))
  {
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH6(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH40(H40 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH40() - 1)) && (position >= 3))
  {
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 3);
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 2);
    StoreH40(self, ringbuffer, ring_buffer_mask, position - 1);
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
inline static void HasherSetup(MemoryManager *m, Hasher *hasher, BrotliEncoderParams *params, const uint8_t *data, size_t position, size_t input_size, int is_last)
{
  int one_shot = (position == 0) && is_last;
  if (hasher->common.extra == 0)
  {
    helper_HasherSetup_2(m, hasher, params, input_size, one_shot);
  }
  if (!hasher->common.is_prepared_)
  {
    helper_HasherSetup_1(hasher, data, position, input_size, one_shot);
  }
}


----------------------------
inline static void StitchToPreviousBlockH2(H2 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH2() - 1)) && (position >= 3))
  {
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH2(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH4(H4 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH4() - 1)) && (position >= 3))
  {
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 3);
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 2);
    StoreH4(self, ringbuffer, ringbuffer_mask, position - 1);
  }
}


----------------------------
inline static void StitchToPreviousBlockH55(H55 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ring_buffer_mask)
{
  StitchToPreviousBlockH54(&self->ha, num_bytes, position, ringbuffer, ring_buffer_mask);
  StitchToPreviousBlockHROLLING_FAST(&self->hb, num_bytes, position, ringbuffer, ring_buffer_mask);
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH54(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH54(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 20) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


inline static int TestStaticDictionaryItem(const BrotliEncoderDictionary *dictionary, size_t len, size_t word_idx, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out)
{
  size_t offset;
  size_t matchlen;
  size_t backward;
  size_t score;
  offset = dictionary->words->offsets_by_length[len] + (len * word_idx);
  if (len > max_length)
  {
    return 0;
  }
  matchlen = FindMatchLengthWithLimit(data, &dictionary->words->data[offset], len);
  if (((matchlen + dictionary->cutoffTransformsCount) <= len) || (matchlen == 0))
  {
    return 0;
  }
  {
    size_t cut = len - matchlen;
    size_t transform_id = (cut << 2) + ((size_t) ((dictionary->cutoffTransforms >> (cut * 6)) & 0x3F));
    backward = ((max_backward + 1) + word_idx) + (transform_id << dictionary->words->size_bits_by_length[len]);
  }
  if (backward > max_distance)
  {
    return 0;
  }
  score = BackwardReferenceScore(matchlen, backward);
  if (score < out->score)
  {
    return 0;
  }
  out->len = matchlen;
  out->len_code_delta = ((int) len) - ((int) matchlen);
  out->distance = backward;
  out->score = score;
  return 1;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
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
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
None
----------------------------
***/


inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static uint32_t Hash14(const uint8_t *data)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 14);
}


----------------------------
inline static int TestStaticDictionaryItem(const BrotliEncoderDictionary *dictionary, size_t len, size_t word_idx, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out)
{
  size_t offset;
  size_t matchlen;
  size_t backward;
  size_t score;
  offset = dictionary->words->offsets_by_length[len] + (len * word_idx);
  if (len > max_length)
  {
    return 0;
  }
  matchlen = FindMatchLengthWithLimit(data, &dictionary->words->data[offset], len);
  if (((matchlen + dictionary->cutoffTransformsCount) <= len) || (matchlen == 0))
  {
    return 0;
  }
  {
    size_t cut = len - matchlen;
    size_t transform_id = (cut << 2) + ((size_t) ((dictionary->cutoffTransforms >> (cut * 6)) & 0x3F));
    backward = ((max_backward + 1) + word_idx) + (transform_id << dictionary->words->size_bits_by_length[len]);
  }
  if (backward > max_distance)
  {
    return 0;
  }
  score = BackwardReferenceScore(matchlen, backward);
  if (score < out->score)
  {
    return 0;
  }
  out->len = matchlen;
  out->len_code_delta = ((int) len) - ((int) matchlen);
  out->distance = backward;
  out->score = score;
  return 1;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH54_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 2], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_out_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH54_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 2];
  size_t i;
  for (i = 0; i < (1 << 2); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 20) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 2) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 2); i += 1)
  {
    helper_helper_FindLongestMatchH54_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
void helper_helper_FindLongestMatchH54_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 2], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH54_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH54_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 2) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH54(H54 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH54(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH54_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH54_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH54_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH54(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 7))) * kHashMul64;
  return (uint32_t) (h >> (64 - 20));
}


----------------------------
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_FindLongestMatchH54_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 2];
  size_t i;
  for (i = 0; i < (1 << 2); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 20) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 2) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 2); i += 1)
  {
    helper_helper_FindLongestMatchH54_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
void helper_FindLongestMatchH54_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


----------------------------
void helper_FindLongestMatchH54_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 2) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH54_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH54(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH54()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchH54(H54 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH54(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH54_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH54_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH54_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t HashTypeLengthH54(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH54_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH54_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH54(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH54(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void StoreRangeH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH54(self, data, mask, i);
  }

}


----------------------------
inline static void PrepareDistanceCacheH54(H54 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH54_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH54(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH54()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH54_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H54 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH54() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH54(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH54() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH54(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH54(void)
{
  return 8;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void StoreH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH54(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 20) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH54_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH54(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH54_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH54_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
void helper_helper_CreateBackwardReferencesNH54_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH54_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH54(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH54(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
void helper_helper_CreateBackwardReferencesNH54_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H54 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH54() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH54(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH54() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH54(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void FindLongestMatchH54(H54 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH54(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH54_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH54_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH54_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH54(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H54 *privat = &hasher->privat._H54;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH54()) ? (((position + num_bytes) - StoreLookaheadH54()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH54(privat, dist_cache);
  while ((position + HashTypeLengthH54()) < pos_end)
  {
    helper_CreateBackwardReferencesNH54_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH54(void)
{
  return 8;
}


----------------------------
inline static size_t HashTypeLengthH54(void)
{
  return 8;
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
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
void helper_CreateBackwardReferencesNH54_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H54 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH54(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH54_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH54_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static void PrepareDistanceCacheH54(H54 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH2_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H2 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH2() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH2(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH2() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH2(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH2(void)
{
  return 8;
}


----------------------------
inline static void StoreH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH2(&data[ix & mask]);
  if ((1 << 0) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 0) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH2_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 0], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_out_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH2_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 0];
  size_t i;
  for (i = 0; i < (1 << 0); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 16) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 0) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 0); i += 1)
  {
    helper_helper_FindLongestMatchH2_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
void helper_helper_FindLongestMatchH2_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 0], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH2_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 0) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH2_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH2(H2 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH2(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH2_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 0) == 1)
  {
    helper_FindLongestMatchH2_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH2_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 0) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
static uint32_t HashBytesH2(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_FindLongestMatchH2_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 0];
  size_t i;
  for (i = 0; i < (1 << 0); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 16) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 0) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 0); i += 1)
  {
    helper_helper_FindLongestMatchH2_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
void helper_FindLongestMatchH2_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 0) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_FindLongestMatchH2_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH2_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH2(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH2()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH2(H2 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH2(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH2_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 0) == 1)
  {
    helper_FindLongestMatchH2_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH2_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 0) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
inline static size_t HashTypeLengthH2(void)
{
  return 8;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH2_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH2_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH2(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH2(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void PrepareDistanceCacheH2(H2 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void StoreRangeH2(H2 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH2(self, data, mask, i);
  }

}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH2_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH2(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH2()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH2_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH2(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH2_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH2_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
void helper_helper_CreateBackwardReferencesNH2_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H2 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH2() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH2(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH2() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH2(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void FindLongestMatchH2(H2 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH2(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH2_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 0) == 1)
  {
    helper_FindLongestMatchH2_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH2_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 0) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH2_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH2_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH2(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH2(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH2(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H2 *privat = &hasher->privat._H2;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH2()) ? (((position + num_bytes) - StoreLookaheadH2()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH2(privat, dist_cache);
  while ((position + HashTypeLengthH2()) < pos_end)
  {
    helper_CreateBackwardReferencesNH2_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
inline static void PrepareDistanceCacheH2(H2 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
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
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t HashTypeLengthH2(void)
{
  return 8;
}


----------------------------
inline static size_t StoreLookaheadH2(void)
{
  return 8;
}


----------------------------
void helper_CreateBackwardReferencesNH2_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H2 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH2(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH2_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH2_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH35(H35 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH3(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheHROLLING_FAST(HROLLING_FAST * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
inline static void PrepareDistanceCacheH3(H3 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH3_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 1], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_out_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH3_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 1];
  size_t i;
  for (i = 0; i < (1 << 1); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 16) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 1) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 1); i += 1)
  {
    helper_helper_FindLongestMatchH3_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_FindLongestMatchH3_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 1], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH3_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH3_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 1) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH3(H3 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH3(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH3_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 1) == 1)
  {
    helper_FindLongestMatchH3_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH3_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 1) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


/*** DEPENDENCIES:
static uint32_t HashBytesH3(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 16));
}


----------------------------
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_FindLongestMatchH3_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 1];
  size_t i;
  for (i = 0; i < (1 << 1); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 16) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 1) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 1); i += 1)
  {
    helper_helper_FindLongestMatchH3_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_FindLongestMatchH3_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


----------------------------
void helper_FindLongestMatchH3_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 1) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


void helper_FindLongestMatchHROLLING_FAST_1(HROLLING_FAST * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t pos)
{
  uint32_t code = self->state & ((16777216 * 64) - 1);
  uint8_t rem = data[pos & ring_buffer_mask];
  uint8_t add = data[(pos + 32) & ring_buffer_mask];
  size_t found_ix = kInvalidPosHROLLING_FAST;
  self->state = HashRollingFunctionHROLLING_FAST(self->state, add, rem, self->factor, self->factor_remove);
  if (code < 16777216)
  {
    found_ix = self->table[code];
    self->table[code] = (uint32_t) pos;
    if ((pos == cur_ix) && (found_ix != kInvalidPosHROLLING_FAST))
    {
      size_t backward = (uint32_t) (cur_ix - found_ix);
      if (backward <= max_backward)
      {
        const size_t found_ix_masked = found_ix & ring_buffer_mask;
        const size_t len = FindMatchLengthWithLimit(&data[found_ix_masked], &data[cur_ix_masked], max_length);
        if ((len >= 4) && (len > out->len))
        {
          size_t score = BackwardReferenceScore(len, backward);
          if (score > out->score)
          {
            out->len = len;
            out->distance = backward;
            out->score = score;
            out->len_code_delta = 0;
          }
        }
      }
    }
  }
}


/*** DEPENDENCIES:
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
static const uint32_t kInvalidPosHROLLING_FAST = 0xffffffff
----------------------------
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


----------------------------
static uint32_t HashRollingFunctionHROLLING_FAST(uint32_t state, uint8_t add, uint8_t rem, uint32_t factor, uint32_t factor_remove)
{
  return (uint32_t) (((factor * state) + HashByteHROLLING_FAST(add)) - (factor_remove * HashByteHROLLING_FAST(rem)));
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
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchHROLLING_FAST(HROLLING_FAST * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t pos;
  if ((cur_ix & (4 - 1)) != 0)
  {
    return;
  }
  if (max_length < 32)
  {
    return;
  }
  for (pos = self->next_ix; pos <= cur_ix; pos += 4)
  {
    helper_FindLongestMatchHROLLING_FAST_1(self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, pos);
  }

  self->next_ix = cur_ix + 4;
  (void) dictionary;
  (void) distance_cache;
  (void) dictionary_distance;
  (void) max_distance;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
void helper_FindLongestMatchHROLLING_FAST_1(HROLLING_FAST * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t pos)
{
  uint32_t code = self->state & ((16777216 * 64) - 1);
  uint8_t rem = data[pos & ring_buffer_mask];
  uint8_t add = data[(pos + 32) & ring_buffer_mask];
  size_t found_ix = kInvalidPosHROLLING_FAST;
  self->state = HashRollingFunctionHROLLING_FAST(self->state, add, rem, self->factor, self->factor_remove);
  if (code < 16777216)
  {
    found_ix = self->table[code];
    self->table[code] = (uint32_t) pos;
    if ((pos == cur_ix) && (found_ix != kInvalidPosHROLLING_FAST))
    {
      size_t backward = (uint32_t) (cur_ix - found_ix);
      if (backward <= max_backward)
      {
        const size_t found_ix_masked = found_ix & ring_buffer_mask;
        const size_t len = FindMatchLengthWithLimit(&data[found_ix_masked], &data[cur_ix_masked], max_length);
        if ((len >= 4) && (len > out->len))
        {
          size_t score = BackwardReferenceScore(len, backward);
          if (score > out->score)
          {
            out->len = len;
            out->distance = backward;
            out->score = score;
            out->len_code_delta = 0;
          }
        }
      }
    }
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH35(H35 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH3(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH3(H3 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH3(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH3_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 1) == 1)
  {
    helper_FindLongestMatchH3_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH3_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 1) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchHROLLING_FAST(HROLLING_FAST * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t pos;
  if ((cur_ix & (4 - 1)) != 0)
  {
    return;
  }
  if (max_length < 32)
  {
    return;
  }
  for (pos = self->next_ix; pos <= cur_ix; pos += 4)
  {
    helper_FindLongestMatchHROLLING_FAST_1(self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, pos);
  }

  self->next_ix = cur_ix + 4;
  (void) dictionary;
  (void) distance_cache;
  (void) dictionary_distance;
  (void) max_distance;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
None
----------------------------
***/


inline static void StoreH35(H35 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH3(&self->ha, data, mask, ix);
  StoreHROLLING_FAST(&self->hb, data, mask, ix);
}


/*** DEPENDENCIES:
inline static void StoreH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH3(&data[ix & mask]);
  if ((1 << 1) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 1) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static void StoreHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH35_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H35 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH35() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH35(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH35() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH35(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void StoreH35(H35 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH3(&self->ha, data, mask, ix);
  StoreHROLLING_FAST(&self->hb, data, mask, ix);
}


----------------------------
inline static size_t StoreLookaheadH35(void)
{
  size_t a = StoreLookaheadH3();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH35(H35 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH3(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING_FAST(&self->hb, data, mask, ix_start, ix_end);
}


/*** DEPENDENCIES:
inline static void StoreRangeH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH3(self, data, mask, i);
  }

}


----------------------------
inline static void StoreRangeHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix_start;
  (void) ix_end;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH35_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH35(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH35()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH35(H35 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH3(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
inline static size_t HashTypeLengthH35(void)
{
  size_t a = HashTypeLengthH3();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH35_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH35_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH35(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH35(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH35(H35 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH3(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void StoreRangeH35(H35 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH3(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING_FAST(&self->hb, data, mask, ix_start, ix_end);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_helper_CreateBackwardReferencesNH35_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH35(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH35()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH35_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH35(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH35_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH35_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void FindLongestMatchH35(H35 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH3(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH35_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H35 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH35() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH35(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH35() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH35(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
void helper_helper_CreateBackwardReferencesNH35_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH35_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH35(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH35(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH35(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H35 *privat = &hasher->privat._H35;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH35()) ? (((position + num_bytes) - StoreLookaheadH35()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH35(privat, dist_cache);
  while ((position + HashTypeLengthH35()) < pos_end)
  {
    helper_CreateBackwardReferencesNH35_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH35(H35 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH3(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
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
inline static size_t StoreLookaheadH35(void)
{
  size_t a = StoreLookaheadH3();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
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
typedef const uint8_t *ContextLut
----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
inline static size_t HashTypeLengthH35(void)
{
  size_t a = HashTypeLengthH3();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
void helper_CreateBackwardReferencesNH35_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H35 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH35(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH35_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH35_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH4_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 2], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_out_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH4_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 2];
  size_t i;
  for (i = 0; i < (1 << 2); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 17) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 2) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 2); i += 1)
  {
    helper_helper_FindLongestMatchH4_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_FindLongestMatchH4_3_1(int * const compare_char_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t keys[1 << 2], size_t i)
{
  int compare_char = *compare_char_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t len;
  size_t backward;
  prev_ix = buckets[keys[i]];
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len])
  {
    continue;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    continue;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      best_len = len;
      out->len = len;
      compare_char = data[cur_ix_masked + len];
      best_score = score;
      out->score = score;
      out->distance = backward;
    }
  }
  *compare_char_ref = compare_char;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['compare_char_ref is a mutable refrence to int', 'key_ref is a mutable refrence to size_t', 'best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH4_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 2) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to size_t', 'prev_ix_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH4_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH4(H4 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH4(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH4_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH4_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH4_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
void helper_FindLongestMatchH4_3(int * const compare_char_ref, size_t * const key_out_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t key)
{
  int compare_char = *compare_char_ref;
  size_t key_out = *key_out_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t keys[1 << 2];
  size_t i;
  for (i = 0; i < (1 << 2); i += 1)
  {
    keys[i] = (key + (i << 3)) & ((1 << 17) - 1);
  }

  key_out = keys[(cur_ix & (((1 << 2) - 1) << 3)) >> 3];
  for (i = 0; i < (1 << 2); i += 1)
  {
    helper_helper_FindLongestMatchH4_3_1(&compare_char, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, keys, i);
  }

  *compare_char_ref = compare_char;
  *key_out_ref = key_out;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
static uint32_t HashBytesH4(const uint8_t *data)
{
  const uint64_t h = (BrotliUnalignedRead64(data) << (64 - (8 * 5))) * kHashMul64;
  return (uint32_t) (h >> (64 - 17));
}


----------------------------
void helper_FindLongestMatchH4_1(int * const compare_char_ref, size_t * const key_ref, size_t * const best_score_ref, size_t * const best_len_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, HasherSearchResult * const out, uint32_t * const buckets, const size_t cur_ix_masked, size_t cached_backward)
{
  int compare_char = *compare_char_ref;
  size_t key = *key_ref;
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t prev_ix = *prev_ix_ref;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char == data[prev_ix + best_len])
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      const size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        out->len = len;
        out->distance = cached_backward;
        out->score = score;
        if ((1 << 2) == 1)
        {
          buckets[key] = (uint32_t) cur_ix;
          return;
        }
        else
        {
          best_len = len;
          best_score = score;
          compare_char = data[cur_ix_masked + len];
        }
      }
    }
  }
  *compare_char_ref = compare_char;
  *key_ref = key;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *prev_ix_ref = prev_ix;
}


----------------------------
void helper_FindLongestMatchH4_2(size_t * const key_ref, size_t * const prev_ix_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const buckets, const size_t best_len_in, const size_t cur_ix_masked, int compare_char, size_t best_score)
{
  size_t key = *key_ref;
  size_t prev_ix = *prev_ix_ref;
  size_t backward;
  size_t len;
  prev_ix = buckets[key];
  buckets[key] = (uint32_t) cur_ix;
  backward = cur_ix - prev_ix;
  prev_ix &= (uint32_t) ring_buffer_mask;
  if (compare_char != data[prev_ix + best_len_in])
  {
    return;
  }
  if (__builtin_expect((backward == 0) || (backward > max_backward), 0))
  {
    return;
  }
  len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
  if (len >= 4)
  {
    const size_t score = BackwardReferenceScore(len, backward);
    if (best_score < score)
    {
      out->len = len;
      out->distance = backward;
      out->score = score;
      return;
    }
  }
  *key_ref = key;
  *prev_ix_ref = prev_ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH4_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH4(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH4()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void FindLongestMatchH4(H4 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH4(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH4_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH4_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH4_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
inline static size_t HashTypeLengthH4(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH4_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH4_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH4(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH4(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
void helper_helper_helper_CreateBackwardReferencesNH4_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH4(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH4()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
inline static void PrepareDistanceCacheH4(H4 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void StoreRangeH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH4(self, data, mask, i);
  }

}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH4_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H4 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH4() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH4(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH4() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH4(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH4(void)
{
  return 8;
}


----------------------------
inline static void StoreH4(H4 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH4(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 17) - 1)] = (uint32_t) ix;
  }
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH4_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH4(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH4_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH4_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
void helper_helper_CreateBackwardReferencesNH4_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH4_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH4(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH4(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void FindLongestMatchH4(H4 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH4(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH4_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH4_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH4_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (1 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
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
void helper_helper_CreateBackwardReferencesNH4_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H4 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH4() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH4(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH4() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH4(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH4(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H4 *privat = &hasher->privat._H4;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH4()) ? (((position + num_bytes) - StoreLookaheadH4()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH4(privat, dist_cache);
  while ((position + HashTypeLengthH4()) < pos_end)
  {
    helper_CreateBackwardReferencesNH4_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
inline static void PrepareDistanceCacheH4(H4 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t StoreLookaheadH4(void)
{
  return 8;
}


----------------------------
void helper_CreateBackwardReferencesNH4_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H4 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH4(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH4_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH4_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static size_t HashTypeLengthH4(void)
{
  return 8;
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH41(H41 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 10);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH41(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t key = HashBytesH41(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'backward_ref is a mutable refrence to size_t', 'delta_ref is a mutable refrence to size_t', 'slot_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH41_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH41 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct BankH41
{
  SlotH41 slots[1 << 16];
} BankH41
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH41_2(size_t * const best_score_ref, size_t * const best_len_ref, H41 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH41 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (1 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH41_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH41(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static void StoreH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t key = HashBytesH41(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
void helper_helper_FindLongestMatchH41_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH41 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


----------------------------
typedef struct BankH41
{
  SlotH41 slots[1 << 16];
} BankH41
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH41_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH41(H41 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH41(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 10; i += 1)
  {
    helper_FindLongestMatchH41_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH41_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


/*** DEPENDENCIES:
void helper_FindLongestMatchH41_2(size_t * const best_score_ref, size_t * const best_len_ref, H41 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH41 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (1 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH41_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH41(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
static uint16_t *HeadH41(void *extra)
{
  return (uint16_t *) (&AddrH41(extra)[1 << 15]);
}


----------------------------
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_FindLongestMatchH41_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
static uint8_t *TinyHashH41(void *extra)
{
  return (uint8_t *) (&HeadH41(extra)[1 << 15]);
}


----------------------------
inline static size_t HashBytesH41(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
typedef struct BankH41
{
  SlotH41 slots[1 << 16];
} BankH41
----------------------------
static BankH41 *BanksH41(void *extra)
{
  return (BankH41 *) (&TinyHashH41(extra)[65536]);
}


----------------------------
static uint32_t *AddrH41(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH41_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH41(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH41()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH41(H41 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH41(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 10; i += 1)
  {
    helper_FindLongestMatchH41_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH41_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
inline static size_t HashTypeLengthH41(void)
{
  return 4;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH41_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH41_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH41(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH41(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void PrepareDistanceCacheH41(H41 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 10);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void StoreRangeH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH41(self, data, mask, i);
  }

}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH41_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH41(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH41()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH41_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H41 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH41() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH41(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH41() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH41(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static void StoreH41(H41 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t key = HashBytesH41(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH41(void)
{
  return 4;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH41_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH41(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH41_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH41_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH41_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH41_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH41(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH41(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void FindLongestMatchH41(H41 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH41(self->extra);
  uint16_t * restrict head = HeadH41(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH41(self->extra);
  BankH41 * restrict banks = BanksH41(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH41(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 10; i += 1)
  {
    helper_FindLongestMatchH41_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH41_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
void helper_helper_CreateBackwardReferencesNH41_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H41 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH41() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH41(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH41() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH41(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH41(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H41 *privat = &hasher->privat._H41;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH41()) ? (((position + num_bytes) - StoreLookaheadH41()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH41(privat, dist_cache);
  while ((position + HashTypeLengthH41()) < pos_end)
  {
    helper_CreateBackwardReferencesNH41_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
void helper_CreateBackwardReferencesNH41_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H41 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH41(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH41_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH41_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
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
inline static void PrepareDistanceCacheH41(H41 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 10);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
inline static size_t HashTypeLengthH41(void)
{
  return 4;
}


----------------------------
inline static size_t StoreLookaheadH41(void)
{
  return 4;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH40_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H40 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH40() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH40(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH40() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH40(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static void StoreH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t key = HashBytesH40(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH40(void)
{
  return 4;
}


----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'backward_ref is a mutable refrence to size_t', 'delta_ref is a mutable refrence to size_t', 'slot_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH40_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH40 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


----------------------------
typedef struct BankH40
{
  SlotH40 slots[1 << 16];
} BankH40
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH40_2(size_t * const best_score_ref, size_t * const best_len_ref, H40 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH40 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (1 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH40_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH40(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
typedef struct BankH40
{
  SlotH40 slots[1 << 16];
} BankH40
----------------------------
void helper_helper_FindLongestMatchH40_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH40 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


----------------------------
inline static void StoreH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t key = HashBytesH40(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH40_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH40(H40 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH40(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 4; i += 1)
  {
    helper_FindLongestMatchH40_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH40_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
inline static size_t HashBytesH40(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static uint16_t *HeadH40(void *extra)
{
  return (uint16_t *) (&AddrH40(extra)[1 << 15]);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
static BankH40 *BanksH40(void *extra)
{
  return (BankH40 *) (&TinyHashH40(extra)[65536]);
}


----------------------------
void helper_FindLongestMatchH40_2(size_t * const best_score_ref, size_t * const best_len_ref, H40 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH40 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (1 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH40_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH40(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
static uint8_t *TinyHashH40(void *extra)
{
  return (uint8_t *) (&HeadH40(extra)[1 << 15]);
}


----------------------------
void helper_FindLongestMatchH40_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
static uint32_t *AddrH40(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
typedef struct BankH40
{
  SlotH40 slots[1 << 16];
} BankH40
----------------------------
None
----------------------------
***/


inline static void StoreRangeH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH40(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t key = HashBytesH40(&data[ix & mask]);
  const size_t bank = key & (1 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 16) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH40_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH40(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH40()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH40(void)
{
  return 4;
}


----------------------------
inline static void FindLongestMatchH40(H40 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH40(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 4; i += 1)
  {
    helper_FindLongestMatchH40_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH40_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH40(H40 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 4);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH40_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH40_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH40(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH40(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void StoreRangeH40(H40 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH40(self, data, mask, i);
  }

}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_helper_CreateBackwardReferencesNH40_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH40(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH40()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void PrepareDistanceCacheH40(H40 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 4);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH40_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH40(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH40_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH40_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH40_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H40 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH40() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH40(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH40() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH40(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
inline static void FindLongestMatchH40(H40 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH40(self->extra);
  uint16_t * restrict head = HeadH40(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH40(self->extra);
  BankH40 * restrict banks = BanksH40(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH40(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 4; i += 1)
  {
    helper_FindLongestMatchH40_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH40_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
void helper_helper_CreateBackwardReferencesNH40_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH40_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH40(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH40(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH40(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H40 *privat = &hasher->privat._H40;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH40()) ? (((position + num_bytes) - StoreLookaheadH40()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH40(privat, dist_cache);
  while ((position + HashTypeLengthH40()) < pos_end)
  {
    helper_CreateBackwardReferencesNH40_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
void helper_CreateBackwardReferencesNH40_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H40 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH40(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH40_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH40_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t StoreLookaheadH40(void)
{
  return 4;
}


----------------------------
inline static size_t HashTypeLengthH40(void)
{
  return 4;
}


----------------------------
inline static void PrepareDistanceCacheH40(H40 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 4);
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH42(H42 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 16);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCache(int * restrict distance_cache, const int num_distances)
{
  if (num_distances > 4)
  {
    int last_distance = distance_cache[0];
    distance_cache[4] = last_distance - 1;
    distance_cache[5] = last_distance + 1;
    distance_cache[6] = last_distance - 2;
    distance_cache[7] = last_distance + 2;
    distance_cache[8] = last_distance - 3;
    distance_cache[9] = last_distance + 3;
    if (num_distances > 10)
    {
      int next_last_distance = distance_cache[1];
      distance_cache[10] = next_last_distance - 1;
      distance_cache[11] = next_last_distance + 1;
      distance_cache[12] = next_last_distance - 2;
      distance_cache[13] = next_last_distance + 2;
      distance_cache[14] = next_last_distance - 3;
      distance_cache[15] = next_last_distance + 3;
    }
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH42_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'backward_ref is a mutable refrence to size_t', 'delta_ref is a mutable refrence to size_t', 'slot_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH42_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH42 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


----------------------------
typedef struct BankH42
{
  SlotH42 slots[1 << 9];
} BankH42
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH42_2(size_t * const best_score_ref, size_t * const best_len_ref, H42 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH42 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (512 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH42_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH42(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
typedef struct BankH42
{
  SlotH42 slots[1 << 9];
} BankH42
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_FindLongestMatchH42_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const backward_ref, size_t * const delta_ref, size_t * const slot_ref, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, BankH42 * const banks, const size_t cur_ix_masked, const size_t bank)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t backward = *backward_ref;
  size_t delta = *delta_ref;
  size_t slot = *slot_ref;
  size_t prev_ix;
  size_t last = slot;
  backward += delta;
  if ((backward > max_backward) || (0 && (!delta)))
  {
    break;
  }
  prev_ix = (cur_ix - backward) & ring_buffer_mask;
  slot = banks[bank].slots[last].next;
  delta = banks[bank].slots[last].delta;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *backward_ref = backward;
  *delta_ref = delta;
  *slot_ref = slot;
}


----------------------------
inline static void StoreH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t key = HashBytesH42(&data[ix & mask]);
  const size_t bank = key & (512 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 9) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH42(H42 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH42(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 16; i += 1)
  {
    helper_FindLongestMatchH42_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH42_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
inline static size_t HashBytesH42(const uint8_t * restrict data)
{
  const uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return h >> (32 - 15);
}


----------------------------
static uint16_t *HeadH42(void *extra)
{
  return (uint16_t *) (&AddrH42(extra)[1 << 15]);
}


----------------------------
void helper_FindLongestMatchH42_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint8_t * const tiny_hashes, const size_t cur_ix_masked, size_t i, const uint8_t tiny_hash)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = cur_ix - backward;
  if ((i > 0) && (tiny_hashes[(uint16_t) prev_ix] != tiny_hash))
  {
    continue;
  }
  if ((prev_ix >= cur_ix) || (backward > max_backward))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 2)
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
static BankH42 *BanksH42(void *extra)
{
  return (BankH42 *) (&TinyHashH42(extra)[65536]);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
typedef struct BankH42
{
  SlotH42 slots[1 << 9];
} BankH42
----------------------------
static uint8_t *TinyHashH42(void *extra)
{
  return (uint8_t *) (&HeadH42(extra)[1 << 15]);
}


----------------------------
static uint32_t *AddrH42(void *extra)
{
  return (uint32_t *) extra;
}


----------------------------
void helper_FindLongestMatchH42_2(size_t * const best_score_ref, size_t * const best_len_ref, H42 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint32_t * const addr, uint16_t * const head, BankH42 * const banks, const size_t cur_ix_masked, const size_t key)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t bank = key & (512 - 1);
  size_t backward = 0;
  size_t hops = self->max_hops;
  size_t delta = cur_ix - addr[key];
  size_t slot = head[key];
  while (hops--)
  {
    helper_helper_FindLongestMatchH42_2_1(&best_score, &best_len, &backward, &delta, &slot, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, banks, cur_ix_masked, bank);
  }

  StoreH42(self, data, ring_buffer_mask, cur_ix);
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH42_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH42(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH42()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH42(void)
{
  return 4;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchH42(H42 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH42(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 16; i += 1)
  {
    helper_FindLongestMatchH42_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH42_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH42(self, data, mask, i);
  }

}


/*** DEPENDENCIES:
inline static void StoreH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t key = HashBytesH42(&data[ix & mask]);
  const size_t bank = key & (512 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 9) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH42_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH42_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH42(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH42(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH42(H42 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 16);
}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH42_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH42(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH42()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void StoreRangeH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH42(self, data, mask, i);
  }

}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH42_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H42 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH42() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH42(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH42() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH42(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH42(void)
{
  return 4;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void StoreH42(H42 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hash = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t key = HashBytesH42(&data[ix & mask]);
  const size_t bank = key & (512 - 1);
  const size_t idx = (self->free_slot_idx[bank]++) & ((1 << 9) - 1);
  size_t delta = ix - addr[key];
  tiny_hash[(uint16_t) ix] = (uint8_t) key;
  if (delta > 0xFFFF)
  {
    delta = (0) ? (0) : (0xFFFF);
  }
  banks[bank].slots[idx].delta = (uint16_t) delta;
  banks[bank].slots[idx].next = head[key];
  addr[key] = (uint32_t) ix;
  head[key] = (uint16_t) idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH42_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH42(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH42_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH42_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void FindLongestMatchH42(H42 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict addr = AddrH42(self->extra);
  uint16_t * restrict head = HeadH42(self->extra);
  uint8_t * restrict tiny_hashes = TinyHashH42(self->extra);
  BankH42 * restrict banks = BanksH42(self->extra);
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  const size_t key = HashBytesH42(&data[cur_ix_masked]);
  const uint8_t tiny_hash = (uint8_t) key;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < 16; i += 1)
  {
    helper_FindLongestMatchH42_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, tiny_hashes, cur_ix_masked, i, tiny_hash);
  }

  {
    helper_FindLongestMatchH42_2(&best_score, &best_len, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, addr, head, banks, cur_ix_masked, key);
  }
  if (out->score == min_score)
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH42_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH42_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH42(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH42(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
void helper_helper_CreateBackwardReferencesNH42_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H42 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH42() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH42(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH42() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH42(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH42(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H42 *privat = &hasher->privat._H42;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH42()) ? (((position + num_bytes) - StoreLookaheadH42()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH42(privat, dist_cache);
  while ((position + HashTypeLengthH42()) < pos_end)
  {
    helper_CreateBackwardReferencesNH42_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH42(H42 * restrict self, int * restrict distance_cache)
{
  (void) self;
  PrepareDistanceCache(distance_cache, 16);
}


----------------------------
inline static size_t HashTypeLengthH42(void)
{
  return 4;
}


----------------------------
inline static size_t StoreLookaheadH42(void)
{
  return 4;
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
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
void helper_CreateBackwardReferencesNH42_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H42 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH42(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH42_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH42_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH3_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH3(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH3()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH3(void)
{
  return 8;
}


----------------------------
inline static void FindLongestMatchH3(H3 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH3(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH3_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 1) == 1)
  {
    helper_FindLongestMatchH3_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH3_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 1) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH3_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH3_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH3(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH3(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_helper_CreateBackwardReferencesNH3_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH3(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH3()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void StoreRangeH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH3(self, data, mask, i);
  }

}


----------------------------
inline static void PrepareDistanceCacheH3(H3 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH3_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H3 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH3() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH3(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH3() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH3(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH3(void)
{
  return 8;
}


----------------------------
inline static void StoreH3(H3 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH3(&data[ix & mask]);
  if ((1 << 1) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 1) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 16) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH3_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH3(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH3_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH3_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void helper_helper_CreateBackwardReferencesNH3_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH3_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH3(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH3(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
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
inline static void FindLongestMatchH3(H3 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH3(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH3_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 1) == 1)
  {
    helper_FindLongestMatchH3_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH3_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 1) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH3_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H3 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH3() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH3(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH3() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH3(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH3(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H3 *privat = &hasher->privat._H3;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH3()) ? (((position + num_bytes) - StoreLookaheadH3()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH3(privat, dist_cache);
  while ((position + HashTypeLengthH3()) < pos_end)
  {
    helper_CreateBackwardReferencesNH3_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
void helper_CreateBackwardReferencesNH3_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H3 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH3(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH3_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH3_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static size_t HashTypeLengthH3(void)
{
  return 8;
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
inline static size_t StoreLookaheadH3(void)
{
  return 8;
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
inline static void PrepareDistanceCacheH3(H3 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH6_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H6 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, uint32_t * const bucket)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  size_t prev_ix = bucket[(--i) & self->block_mask_];
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH6_2(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H6 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint16_t * const num, uint32_t * const buckets, const size_t cur_ix_masked)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  const uint32_t key = HashBytesH6(&data[cur_ix_masked], self->hash_mask_, self->hash_shift_);
  uint32_t * restrict bucket = &buckets[key << self->block_bits_];
  const size_t down = (num[key] > self->block_size_) ? (num[key] - self->block_size_) : (0u);
  for (i = num[key]; i > down;)
  {
    helper_helper_FindLongestMatchH6_2_1(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, bucket);
  }

  bucket[num[key] & self->block_mask_] = (uint32_t) cur_ix;
  num[key] += 1;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


/*** DEPENDENCIES:
void helper_helper_FindLongestMatchH6_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H6 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, uint32_t * const bucket)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  size_t prev_ix = bucket[(--i) & self->block_mask_];
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


----------------------------
inline static uint32_t HashBytesH6(const uint8_t * restrict data, const uint64_t mask, const int shift)
{
  const uint64_t h = (BrotliUnalignedRead64(data) & mask) * kHashMul64Long;
  return (uint32_t) (h >> shift);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH6_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t i)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = (size_t) (cur_ix - backward);
  if (prev_ix >= cur_ix)
  {
    continue;
  }
  if (__builtin_expect(backward > max_backward, 0))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if ((len >= 3) || ((len == 2) && (i < 2)))
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH6(H6 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH6_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH6_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_FindLongestMatchH6_2(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H6 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint16_t * const num, uint32_t * const buckets, const size_t cur_ix_masked)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  const uint32_t key = HashBytesH6(&data[cur_ix_masked], self->hash_mask_, self->hash_shift_);
  uint32_t * restrict bucket = &buckets[key << self->block_bits_];
  const size_t down = (num[key] > self->block_size_) ? (num[key] - self->block_size_) : (0u);
  for (i = num[key]; i > down;)
  {
    helper_helper_FindLongestMatchH6_2_1(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, bucket);
  }

  bucket[num[key] & self->block_mask_] = (uint32_t) cur_ix;
  num[key] += 1;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


----------------------------
void helper_FindLongestMatchH6_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t i)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = (size_t) (cur_ix - backward);
  if (prev_ix >= cur_ix)
  {
    continue;
  }
  if (__builtin_expect(backward > max_backward, 0))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if ((len >= 3) || ((len == 2) && (i < 2)))
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH6_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH6(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH6()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH6(void)
{
  return 8;
}


----------------------------
inline static void FindLongestMatchH6(H6 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH6_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH6_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH6_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH6_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH6(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH6(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void StoreRangeH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH6(self, data, mask, i);
  }

}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH6_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH6(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH6()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void PrepareDistanceCacheH6(H6 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH6_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H6 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH6() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH6(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH6() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH6(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH6(void)
{
  return 8;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void StoreH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const uint32_t key = HashBytesH6(&data[ix & mask], self->hash_mask_, self->hash_shift_);
  const size_t minor_ix = num[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  num[key] += 1;
  buckets[offset] = (uint32_t) ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH6_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH6(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH6_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH6_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
void helper_helper_CreateBackwardReferencesNH6_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH6_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH6(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH6(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
void helper_helper_CreateBackwardReferencesNH6_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H6 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH6() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH6(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH6() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH6(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchH6(H6 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH6_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH6_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH6(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H6 *privat = &hasher->privat._H6;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH6()) ? (((position + num_bytes) - StoreLookaheadH6()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH6(privat, dist_cache);
  while ((position + HashTypeLengthH6()) < pos_end)
  {
    helper_CreateBackwardReferencesNH6_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
inline static size_t HashTypeLengthH6(void)
{
  return 8;
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
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static size_t StoreLookaheadH6(void)
{
  return 8;
}


----------------------------
inline static void PrepareDistanceCacheH6(H6 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


----------------------------
void helper_CreateBackwardReferencesNH6_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H6 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH6(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH6_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH6_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
None
----------------------------
***/


void helper_FindLongestMatchHROLLING_1(HROLLING * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t pos)
{
  uint32_t code = self->state & ((16777216 * 64) - 1);
  uint8_t rem = data[pos & ring_buffer_mask];
  uint8_t add = data[(pos + 32) & ring_buffer_mask];
  size_t found_ix = kInvalidPosHROLLING;
  self->state = HashRollingFunctionHROLLING(self->state, add, rem, self->factor, self->factor_remove);
  if (code < 16777216)
  {
    found_ix = self->table[code];
    self->table[code] = (uint32_t) pos;
    if ((pos == cur_ix) && (found_ix != kInvalidPosHROLLING))
    {
      size_t backward = (uint32_t) (cur_ix - found_ix);
      if (backward <= max_backward)
      {
        const size_t found_ix_masked = found_ix & ring_buffer_mask;
        const size_t len = FindMatchLengthWithLimit(&data[found_ix_masked], &data[cur_ix_masked], max_length);
        if ((len >= 4) && (len > out->len))
        {
          size_t score = BackwardReferenceScore(len, backward);
          if (score > out->score)
          {
            out->len = len;
            out->distance = backward;
            out->score = score;
            out->len_code_delta = 0;
          }
        }
      }
    }
  }
}


/*** DEPENDENCIES:
static uint32_t HashRollingFunctionHROLLING(uint32_t state, uint8_t add, uint8_t rem, uint32_t factor, uint32_t factor_remove)
{
  return (uint32_t) (((factor * state) + HashByteHROLLING(add)) - (factor_remove * HashByteHROLLING(rem)));
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
}


----------------------------
static const uint32_t kInvalidPosHROLLING = 0xffffffff
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
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchHROLLING(HROLLING * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t pos;
  if ((cur_ix & (1 - 1)) != 0)
  {
    return;
  }
  if (max_length < 32)
  {
    return;
  }
  for (pos = self->next_ix; pos <= cur_ix; pos += 1)
  {
    helper_FindLongestMatchHROLLING_1(self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, pos);
  }

  self->next_ix = cur_ix + 1;
  (void) dictionary;
  (void) distance_cache;
  (void) dictionary_distance;
  (void) max_distance;
}


/*** DEPENDENCIES:
void helper_FindLongestMatchHROLLING_1(HROLLING * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t pos)
{
  uint32_t code = self->state & ((16777216 * 64) - 1);
  uint8_t rem = data[pos & ring_buffer_mask];
  uint8_t add = data[(pos + 32) & ring_buffer_mask];
  size_t found_ix = kInvalidPosHROLLING;
  self->state = HashRollingFunctionHROLLING(self->state, add, rem, self->factor, self->factor_remove);
  if (code < 16777216)
  {
    found_ix = self->table[code];
    self->table[code] = (uint32_t) pos;
    if ((pos == cur_ix) && (found_ix != kInvalidPosHROLLING))
    {
      size_t backward = (uint32_t) (cur_ix - found_ix);
      if (backward <= max_backward)
      {
        const size_t found_ix_masked = found_ix & ring_buffer_mask;
        const size_t len = FindMatchLengthWithLimit(&data[found_ix_masked], &data[cur_ix_masked], max_length);
        if ((len >= 4) && (len > out->len))
        {
          size_t score = BackwardReferenceScore(len, backward);
          if (score > out->score)
          {
            out->len = len;
            out->distance = backward;
            out->score = score;
            out->len_code_delta = 0;
          }
        }
      }
    }
  }
}


----------------------------
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH65(H65 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH6(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchH6(H6 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH6_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH6_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
inline static void FindLongestMatchHROLLING(HROLLING * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t pos;
  if ((cur_ix & (1 - 1)) != 0)
  {
    return;
  }
  if (max_length < 32)
  {
    return;
  }
  for (pos = self->next_ix; pos <= cur_ix; pos += 1)
  {
    helper_FindLongestMatchHROLLING_1(self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, pos);
  }

  self->next_ix = cur_ix + 1;
  (void) dictionary;
  (void) distance_cache;
  (void) dictionary_distance;
  (void) max_distance;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH65_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH65(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH65()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH65(H65 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH6(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
inline static size_t HashTypeLengthH65(void)
{
  size_t a = HashTypeLengthH6();
  size_t b = HashTypeLengthHROLLING();
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH65(H65 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH6(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING(&self->hb, distance_cache);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH6(H6 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


----------------------------
inline static void PrepareDistanceCacheHROLLING(HROLLING * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH65(H65 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH6(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING(&self->hb, data, mask, ix_start, ix_end);
}


/*** DEPENDENCIES:
inline static void StoreRangeH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH6(self, data, mask, i);
  }

}


----------------------------
inline static void StoreRangeHROLLING(HROLLING * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix_start;
  (void) ix_end;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH65_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH65_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH65(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH65(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
void helper_helper_helper_CreateBackwardReferencesNH65_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH65(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH65()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void PrepareDistanceCacheH65(H65 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH6(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING(&self->hb, distance_cache);
}


----------------------------
inline static void StoreRangeH65(H65 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH6(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING(&self->hb, data, mask, ix_start, ix_end);
}


----------------------------
None
----------------------------
***/


inline static void StoreH65(H65 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH6(&self->ha, data, mask, ix);
  StoreHROLLING(&self->hb, data, mask, ix);
}


/*** DEPENDENCIES:
inline static void StoreHROLLING(HROLLING * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix;
}


----------------------------
inline static void StoreH6(H6 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const uint32_t key = HashBytesH6(&data[ix & mask], self->hash_mask_, self->hash_shift_);
  const size_t minor_ix = num[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  num[key] += 1;
  buckets[offset] = (uint32_t) ix;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH65_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H65 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH65() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH65(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH65() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH65(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void StoreH65(H65 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH6(&self->ha, data, mask, ix);
  StoreHROLLING(&self->hb, data, mask, ix);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH65(void)
{
  size_t a = StoreLookaheadH6();
  size_t b = StoreLookaheadHROLLING();
  return (a > b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH65_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH65(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH65_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH65_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
void helper_helper_CreateBackwardReferencesNH65_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH65_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH65(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH65(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchH65(H65 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH6(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
void helper_helper_CreateBackwardReferencesNH65_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H65 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH65() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH65(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH65() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH65(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH65(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H65 *privat = &hasher->privat._H65;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH65()) ? (((position + num_bytes) - StoreLookaheadH65()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH65(privat, dist_cache);
  while ((position + HashTypeLengthH65()) < pos_end)
  {
    helper_CreateBackwardReferencesNH65_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
inline static size_t HashTypeLengthH65(void)
{
  size_t a = HashTypeLengthH6();
  size_t b = HashTypeLengthHROLLING();
  return (a > b) ? (a) : (b);
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
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
void helper_CreateBackwardReferencesNH65_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H65 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH65(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH65_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH65_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static void PrepareDistanceCacheH65(H65 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH6(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING(&self->hb, distance_cache);
}


----------------------------
inline static size_t StoreLookaheadH65(void)
{
  size_t a = StoreLookaheadH6();
  size_t b = StoreLookaheadHROLLING();
  return (a > b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static void PrepareDistanceCacheH55(H55 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH54(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheHROLLING_FAST(HROLLING_FAST * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
inline static void PrepareDistanceCacheH54(H54 * restrict self, int * restrict distance_cache)
{
  (void) self;
  (void) distance_cache;
}


----------------------------
None
----------------------------
***/


inline static void StoreH55(H55 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH54(&self->ha, data, mask, ix);
  StoreHROLLING_FAST(&self->hb, data, mask, ix);
}


/*** DEPENDENCIES:
inline static void StoreHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix;
}


----------------------------
inline static void StoreH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH54(&data[ix & mask]);
  if ((1 << 2) == 1)
  {
    self->buckets_[key] = (uint32_t) ix;
  }
  else
  {
    const uint32_t off = ix & (((1 << 2) - 1) << 3);
    self->buckets_[(key + off) & ((1 << 20) - 1)] = (uint32_t) ix;
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH55_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H55 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH55() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH55(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH55() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH55(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static void StoreH55(H55 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  StoreH54(&self->ha, data, mask, ix);
  StoreHROLLING_FAST(&self->hb, data, mask, ix);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t StoreLookaheadH55(void)
{
  size_t a = StoreLookaheadH54();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static void StoreRangeH55(H55 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH54(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING_FAST(&self->hb, data, mask, ix_start, ix_end);
}


/*** DEPENDENCIES:
inline static void StoreRangeH54(H54 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH54(self, data, mask, i);
  }

}


----------------------------
inline static void StoreRangeHROLLING_FAST(HROLLING_FAST * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  (void) self;
  (void) data;
  (void) mask;
  (void) ix_start;
  (void) ix_end;
}


----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH55(H55 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH54(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


/*** DEPENDENCIES:
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
inline static void FindLongestMatchHROLLING_FAST(HROLLING_FAST * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t pos;
  if ((cur_ix & (4 - 1)) != 0)
  {
    return;
  }
  if (max_length < 32)
  {
    return;
  }
  for (pos = self->next_ix; pos <= cur_ix; pos += 4)
  {
    helper_FindLongestMatchHROLLING_FAST_1(self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, pos);
  }

  self->next_ix = cur_ix + 4;
  (void) dictionary;
  (void) distance_cache;
  (void) dictionary_distance;
  (void) max_distance;
}


----------------------------
inline static void FindLongestMatchH54(H54 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint32_t * restrict buckets = self->buckets_;
  const size_t best_len_in = out->len;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  int compare_char = data[cur_ix_masked + best_len_in];
  size_t key = HashBytesH54(&data[cur_ix_masked]);
  size_t key_out;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = best_len_in;
  size_t cached_backward = (size_t) distance_cache[0];
  size_t prev_ix = cur_ix - cached_backward;
  out->len_code_delta = 0;
  if (prev_ix < cur_ix)
  {
    helper_FindLongestMatchH54_1(&compare_char, &key, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, out, buckets, cur_ix_masked, cached_backward);
  }
  if ((1 << 2) == 1)
  {
    helper_FindLongestMatchH54_2(&key, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, best_len_in, cur_ix_masked, compare_char, best_score);
  }
  else
  {
    helper_FindLongestMatchH54_3(&compare_char, &key_out, &best_score, &best_len, &prev_ix, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, buckets, cur_ix_masked, key);
  }
  if (0 && (min_score == out->score))
  {
    SearchInStaticDictionary(dictionary, self->common, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 1);
  }
  if ((1 << 2) != 1)
  {
    buckets[key_out] = (uint32_t) cur_ix;
  }
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH55_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH55(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH55()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static size_t HashTypeLengthH55(void)
{
  size_t a = HashTypeLengthH54();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void FindLongestMatchH55(H55 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH54(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH55_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH55_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH55(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH55(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH55(H55 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH54(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void StoreRangeH55(H55 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  StoreRangeH54(&self->ha, data, mask, ix_start, ix_end);
  StoreRangeHROLLING_FAST(&self->hb, data, mask, ix_start, ix_end);
}


----------------------------
void helper_helper_helper_CreateBackwardReferencesNH55_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH55(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH55()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH55_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH55(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH55_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH55_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
void helper_helper_CreateBackwardReferencesNH55_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H55 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH55() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH55(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH55() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH55(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_CreateBackwardReferencesNH55_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH55_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH55(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH55(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void FindLongestMatchH55(H55 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  FindLongestMatchH54(&self->ha, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
  FindLongestMatchHROLLING_FAST(&self->hb, dictionary, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, dictionary_distance, max_distance, out);
}


----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH55(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H55 *privat = &hasher->privat._H55;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH55()) ? (((position + num_bytes) - StoreLookaheadH55()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH55(privat, dist_cache);
  while ((position + HashTypeLengthH55()) < pos_end)
  {
    helper_CreateBackwardReferencesNH55_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH55(H55 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCacheH54(&self->ha, distance_cache);
  PrepareDistanceCacheHROLLING_FAST(&self->hb, distance_cache);
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
void helper_CreateBackwardReferencesNH55_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H55 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH55(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH55_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH55_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
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
typedef const uint8_t *ContextLut
----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
inline static size_t StoreLookaheadH55(void)
{
  size_t a = StoreLookaheadH54();
  size_t b = StoreLookaheadHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t HashTypeLengthH55(void)
{
  size_t a = HashTypeLengthH54();
  size_t b = HashTypeLengthHROLLING_FAST();
  return (a > b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH5_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t i)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = (size_t) (cur_ix - backward);
  if (prev_ix >= cur_ix)
  {
    continue;
  }
  if (__builtin_expect(backward > max_backward, 0))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if ((len >= 3) || ((len == 2) && (i < 2)))
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferencePenaltyUsingLastDistance(size_t distance_short_code)
{
  return ((size_t) 39) + ((0x1CA10 >> (distance_short_code & 0xE)) & 0xE);
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
inline static size_t BackwardReferenceScoreUsingLastDistance(size_t copy_length)
{
  return ((135 * ((size_t) copy_length)) + ((30 * 8) * (sizeof(size_t)))) + 15;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_FindLongestMatchH5_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H5 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, uint32_t * const bucket)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  size_t prev_ix = bucket[(--i) & self->block_mask_];
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static size_t BackwardReferenceScore(size_t copy_length, size_t backward_reference_offset)
{
  return (((30 * 8) * (sizeof(size_t))) + (135 * ((size_t) copy_length))) - (30 * Log2FloorNonZero(backward_reference_offset));
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
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['best_score_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_FindLongestMatchH5_2(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H5 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint16_t * const num, uint32_t * const buckets, const size_t cur_ix_masked)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  const uint32_t key = HashBytesH5(&data[cur_ix_masked], self->hash_shift_);
  uint32_t * restrict bucket = &buckets[key << self->block_bits_];
  const size_t down = (num[key] > self->block_size_) ? (num[key] - self->block_size_) : (0u);
  for (i = num[key]; i > down;)
  {
    helper_helper_FindLongestMatchH5_2_1(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, bucket);
  }

  bucket[num[key] & self->block_mask_] = (uint32_t) cur_ix;
  num[key] += 1;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


/*** DEPENDENCIES:
static uint32_t HashBytesH5(const uint8_t * restrict data, const int shift)
{
  uint32_t h = BrotliUnalignedRead32(data) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_FindLongestMatchH5_2_1(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H5 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, uint32_t * const bucket)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  i -= 1;
  size_t prev_ix = bucket[(--i) & self->block_mask_];
  const size_t backward = cur_ix - prev_ix;
  if (__builtin_expect(backward > max_backward, 0))
  {
    break;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if (len >= 4)
    {
      size_t score = BackwardReferenceScore(len, backward);
      if (best_score < score)
      {
        best_score = score;
        best_len = len;
        out->len = best_len;
        out->distance = backward;
        out->score = best_score;
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


----------------------------
None
----------------------------
***/


inline static void FindLongestMatchH5(H5 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH5_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH5_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


/*** DEPENDENCIES:
inline static void SearchInStaticDictionary(const BrotliEncoderDictionary *dictionary, HasherCommon *common, const uint8_t *data, size_t max_length, size_t max_backward, size_t max_distance, HasherSearchResult *out, int shallow)
{
  size_t key;
  size_t i;
  if (common->dict_num_matches < (common->dict_num_lookups >> 7))
  {
    return;
  }
  key = Hash14(data) << 1;
  for (i = 0; i < ((shallow) ? (1u) : (2u)); i += 1, key += 1)
  {
    common->dict_num_lookups += 1;
    if (dictionary->hash_table_lengths[key] != 0)
    {
      int item_matches = TestStaticDictionaryItem(dictionary, dictionary->hash_table_lengths[key], dictionary->hash_table_words[key], data, max_length, max_backward, max_distance, out);
      if (item_matches)
      {
        common->dict_num_matches += 1;
      }
    }
  }

}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_FindLongestMatchH5_1(size_t * const best_score_ref, size_t * const best_len_ref, const uint8_t * const data, const size_t ring_buffer_mask, const int * const distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, const size_t cur_ix_masked, size_t i)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  const size_t backward = (size_t) distance_cache[i];
  size_t prev_ix = (size_t) (cur_ix - backward);
  if (prev_ix >= cur_ix)
  {
    continue;
  }
  if (__builtin_expect(backward > max_backward, 0))
  {
    continue;
  }
  prev_ix &= ring_buffer_mask;
  if ((((cur_ix_masked + best_len) > ring_buffer_mask) || ((prev_ix + best_len) > ring_buffer_mask)) || (data[cur_ix_masked + best_len] != data[prev_ix + best_len]))
  {
    continue;
  }
  {
    const size_t len = FindMatchLengthWithLimit(&data[prev_ix], &data[cur_ix_masked], max_length);
    if ((len >= 3) || ((len == 2) && (i < 2)))
    {
      size_t score = BackwardReferenceScoreUsingLastDistance(len);
      if (best_score < score)
      {
        if (i != 0)
        {
          score -= BackwardReferencePenaltyUsingLastDistance(i);
        }
        if (best_score < score)
        {
          best_score = score;
          best_len = len;
          out->len = best_len;
          out->distance = backward;
          out->score = best_score;
        }
      }
    }
  }
  *best_score_ref = best_score;
  *best_len_ref = best_len;
}


----------------------------
void helper_FindLongestMatchH5_2(size_t * const best_score_ref, size_t * const best_len_ref, size_t * const i_ref, H5 * const self, const uint8_t * const data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, HasherSearchResult * const out, uint16_t * const num, uint32_t * const buckets, const size_t cur_ix_masked)
{
  size_t best_score = *best_score_ref;
  size_t best_len = *best_len_ref;
  size_t i = *i_ref;
  const uint32_t key = HashBytesH5(&data[cur_ix_masked], self->hash_shift_);
  uint32_t * restrict bucket = &buckets[key << self->block_bits_];
  const size_t down = (num[key] > self->block_size_) ? (num[key] - self->block_size_) : (0u);
  for (i = num[key]; i > down;)
  {
    helper_helper_FindLongestMatchH5_2_1(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, cur_ix_masked, bucket);
  }

  bucket[num[key] & self->block_mask_] = (uint32_t) cur_ix;
  num[key] += 1;
  *best_score_ref = best_score;
  *best_len_ref = best_len;
  *i_ref = i;
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_helper_CreateBackwardReferencesNH5_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH5(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH5()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH5(H5 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH5_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH5_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t HashTypeLengthH5(void)
{
  return 4;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t', 'max_length_ref is a mutable refrence to size_t', 'max_distance_ref is a mutable refrence to size_t', 'dictionary_start_ref is a mutable refrence to size_t', 'sr_ref is a mutable refrence to HasherSearchResult']
void helper_helper_CreateBackwardReferencesNH5_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH5_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH5(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH5(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH5(H5 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t ComputeDistanceCode(size_t distance, size_t max_distance, const int *dist_cache)
{
  if (distance <= max_distance)
  {
    size_t distance_plus_3 = distance + 3;
    size_t offset0 = distance_plus_3 - ((size_t) dist_cache[0]);
    size_t offset1 = distance_plus_3 - ((size_t) dist_cache[1]);
    if (distance == ((size_t) dist_cache[0]))
    {
      return 0;
    }
    else
      if (distance == ((size_t) dist_cache[1]))
    {
      return 1;
    }
    else
      if (offset0 < 7)
    {
      return (0x9750468 >> (4 * offset0)) & 0xF;
    }
    else
      if (offset1 < 7)
    {
      return (0xFDB1ACE >> (4 * offset1)) & 0xF;
    }
    else
      if (distance == ((size_t) dist_cache[2]))
    {
      return 2;
    }
    else
      if (distance == ((size_t) dist_cache[3]))
    {
      return 3;
    }
  }
  return (distance + 16) - 1;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
void helper_helper_helper_CreateBackwardReferencesNH5_1_2_1(size_t * const position_ref, size_t * const insert_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t gap, const size_t kMinScore, size_t max_length, int delayed_backward_references_in_row)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  const size_t cost_diff_lazy = 175;
  HasherSearchResult sr2;
  sr2.len = (params->quality < 5) ? (brotli_min_size_t(sr.len - 1, max_length)) : (0);
  sr2.len_code_delta = 0;
  sr2.distance = 0;
  sr2.score = kMinScore;
  max_distance = brotli_min_size_t(position + 1, max_backward_limit);
  dictionary_start = brotli_min_size_t((position + 1) + position_offset, max_backward_limit);
  FindLongestMatchH5(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position + 1, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr2);
  if (sr2.score >= (sr.score + cost_diff_lazy))
  {
    position += 1;
    insert_length += 1;
    sr = sr2;
    if (((++delayed_backward_references_in_row) < 4) && ((position + HashTypeLengthH5()) < pos_end))
    {
      continue;
    }
  }
  break;
  *position_ref = position;
  *insert_length_ref = insert_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
inline static void StoreRangeH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i;
  for (i = ix_start; i < ix_end; i += 1)
  {
    StoreH5(self, data, mask, i);
  }

}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'insert_length_ref is a mutable refrence to size_t']
void helper_helper_CreateBackwardReferencesNH5_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H5 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH5() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH5(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH5() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH5(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


/*** DEPENDENCIES:
inline static size_t StoreLookaheadH5(void)
{
  return 4;
}


----------------------------
inline static void StoreH5(H5 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix)
{
  const uint32_t key = HashBytesH5(&data[ix & mask], self->hash_shift_);
  const size_t minor_ix = self->num_[key] & self->block_mask_;
  const size_t offset = minor_ix + (key << self->block_bits_);
  self->buckets_[offset] = (uint32_t) ix;
  self->num_[key] += 1;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


// hint:  ['position_ref is a mutable refrence to size_t', 'commands_idx_ref is a mutable refrence to unsigned int', 'insert_length_ref is a mutable refrence to size_t', 'apply_random_heuristics_ref is a mutable refrence to size_t']
void helper_CreateBackwardReferencesNH5_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH5(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH5_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH5_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


/*** DEPENDENCIES:
inline static void FindLongestMatchH5(H5 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const int * restrict distance_cache, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const size_t max_distance, HasherSearchResult * restrict out)
{
  uint16_t * restrict num = self->num_;
  uint32_t * restrict buckets = self->buckets_;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t min_score = out->score;
  size_t best_score = out->score;
  size_t best_len = out->len;
  size_t i;
  out->len = 0;
  out->len_code_delta = 0;
  for (i = 0; i < ((size_t) self->num_last_distances_to_check_); i += 1)
  {
    helper_FindLongestMatchH5_1(&best_score, &best_len, data, ring_buffer_mask, distance_cache, cur_ix, max_length, max_backward, out, cur_ix_masked, i);
  }

  {
    helper_FindLongestMatchH5_2(&best_score, &best_len, &i, self, data, ring_buffer_mask, cur_ix, max_length, max_backward, out, num, buckets, cur_ix_masked);
  }
  if (min_score == out->score)
  {
    SearchInStaticDictionary(dictionary, self->common_, &data[cur_ix_masked], max_length, dictionary_distance, max_distance, out, 0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
void helper_helper_CreateBackwardReferencesNH5_1_2(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, size_t * const max_length_ref, size_t * const max_distance_ref, size_t * const dictionary_start_ref, HasherSearchResult * const sr_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = *max_length_ref;
  size_t max_distance = *max_distance_ref;
  size_t dictionary_start = *dictionary_start_ref;
  HasherSearchResult sr = *sr_ref;
  int delayed_backward_references_in_row = 0;
  max_length -= 1;
  for (;; max_length -= 1)
  {
    helper_helper_helper_CreateBackwardReferencesNH5_1_2_1(&position, &insert_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, privat, max_backward_limit, position_offset, pos_end, gap, kMinScore, max_length, delayed_backward_references_in_row);
  }

  apply_random_heuristics = (position + (2 * sr.len)) + random_heuristics_window_size;
  dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  {
    size_t distance_code = ComputeDistanceCode(sr.distance, dictionary_start + gap, dist_cache);
    if ((sr.distance <= (dictionary_start + gap)) && (distance_code > 0))
    {
      dist_cache[3] = dist_cache[2];
      dist_cache[2] = dist_cache[1];
      dist_cache[1] = dist_cache[0];
      dist_cache[0] = (int) sr.distance;
      PrepareDistanceCacheH5(privat, dist_cache);
    }
    InitCommand(commands, &params->dist, insert_length, sr.len, sr.len_code_delta, distance_code);
    commands_idx += 1;
  }
  *num_literals += insert_length;
  insert_length = 0;
  {
    size_t range_start = position + 2;
    size_t range_end = brotli_min_size_t(position + sr.len, store_end);
    if (sr.distance < (sr.len >> 2))
    {
      range_start = brotli_min_size_t(range_end, brotli_max_size_t(range_start, (position + sr.len) - (sr.distance << 2)));
    }
    StoreRangeH5(privat, ringbuffer, ringbuffer_mask, range_start, range_end);
  }
  position += sr.len;
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
  *max_length_ref = max_length;
  *max_distance_ref = max_distance;
  *dictionary_start_ref = dictionary_start;
  *sr_ref = sr;
}


----------------------------
void helper_helper_CreateBackwardReferencesNH5_1_1(size_t * const position_ref, size_t * const insert_length_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, H5 * const privat, const size_t pos_end, const size_t random_heuristics_window_size, size_t apply_random_heuristics)
{
  size_t position = *position_ref;
  size_t insert_length = *insert_length_ref;
  insert_length += 1;
  position += 1;
  if (position > apply_random_heuristics)
  {
    if (position > (apply_random_heuristics + (4 * random_heuristics_window_size)))
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH5() - 1, 4);
      size_t pos_jump = brotli_min_size_t(position + 16, pos_end - kMargin);
      for (; position < pos_jump; position += 4)
      {
        StoreH5(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 4;
      }

    }
    else
    {
      const size_t kMargin = brotli_max_size_t(StoreLookaheadH5() - 1, 2);
      size_t pos_jump = brotli_min_size_t(position + 8, pos_end - kMargin);
      for (; position < pos_jump; position += 2)
      {
        StoreH5(privat, ringbuffer, ringbuffer_mask, position);
        insert_length += 2;
      }

    }
  }
  *position_ref = position;
  *insert_length_ref = insert_length;
}


----------------------------
typedef struct HasherSearchResult
{
  size_t len;
  size_t distance;
  size_t score;
  int len_code_delta;
} HasherSearchResult
----------------------------
None
----------------------------
***/


static void CreateBackwardReferencesNH5(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H5 *privat = &hasher->privat._H5;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH5()) ? (((position + num_bytes) - StoreLookaheadH5()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH5(privat, dist_cache);
  while ((position + HashTypeLengthH5()) < pos_end)
  {
    helper_CreateBackwardReferencesNH5_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


/*** DEPENDENCIES:
inline static void PrepareDistanceCacheH5(H5 * restrict self, int * restrict distance_cache)
{
  PrepareDistanceCache(distance_cache, self->num_last_distances_to_check_);
}


----------------------------
inline static size_t HashTypeLengthH5(void)
{
  return 4;
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
void helper_CreateBackwardReferencesNH5_1(size_t * const position_ref, unsigned int * const commands_idx_ref, size_t * const insert_length_ref, size_t * const apply_random_heuristics_ref, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, int * const dist_cache, Command * const commands, size_t * const num_literals, H5 * const privat, const size_t max_backward_limit, const size_t position_offset, const size_t pos_end, const size_t store_end, const size_t random_heuristics_window_size, const size_t gap, const size_t kMinScore)
{
  size_t position = *position_ref;
  unsigned int commands_idx = *commands_idx_ref;
  size_t insert_length = *insert_length_ref;
  size_t apply_random_heuristics = *apply_random_heuristics_ref;
  size_t max_length = pos_end - position;
  size_t max_distance = brotli_min_size_t(position, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(position + position_offset, max_backward_limit);
  HasherSearchResult sr;
  sr.len = 0;
  sr.len_code_delta = 0;
  sr.distance = 0;
  sr.score = kMinScore;
  FindLongestMatchH5(privat, &params->dictionary, ringbuffer, ringbuffer_mask, dist_cache, position, max_length, max_distance, dictionary_start + gap, params->dist.max_distance, &sr);
  if (sr.score > kMinScore)
  {
    helper_helper_CreateBackwardReferencesNH5_1_2(&position, &commands_idx, &insert_length, &apply_random_heuristics, &max_length, &max_distance, &dictionary_start, &sr, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }
  else
  {
    helper_helper_CreateBackwardReferencesNH5_1_1(&position, &insert_length, ringbuffer, ringbuffer_mask, privat, pos_end, random_heuristics_window_size, apply_random_heuristics);
  }
  *position_ref = position;
  *commands_idx_ref = commands_idx;
  *insert_length_ref = insert_length;
  *apply_random_heuristics_ref = apply_random_heuristics;
}


----------------------------
inline static size_t StoreLookaheadH5(void)
{
  return 4;
}


----------------------------
inline static size_t LiteralSpreeLengthForSparseSearch(const BrotliEncoderParams *params)
{
  return (params->quality < 9) ? (64) : (512);
}


----------------------------
None
----------------------------
***/


void BrotliCreateBackwardReferences(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  switch (params->hasher.type)
  {
    case 2:
    {
      CreateBackwardReferencesNH2(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 3:
    {
      CreateBackwardReferencesNH3(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 4:
    {
      CreateBackwardReferencesNH4(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 5:
    {
      CreateBackwardReferencesNH5(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 6:
    {
      CreateBackwardReferencesNH6(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 40:
    {
      CreateBackwardReferencesNH40(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 41:
    {
      CreateBackwardReferencesNH41(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 42:
    {
      CreateBackwardReferencesNH42(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 54:
    {
      CreateBackwardReferencesNH54(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 35:
    {
      CreateBackwardReferencesNH35(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 55:
    {
      CreateBackwardReferencesNH55(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 65:
    {
      CreateBackwardReferencesNH65(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    default:
    {
      break;
    }

  }

}


/*** DEPENDENCIES:
static void CreateBackwardReferencesNH54(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H54 *privat = &hasher->privat._H54;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH54()) ? (((position + num_bytes) - StoreLookaheadH54()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH54(privat, dist_cache);
  while ((position + HashTypeLengthH54()) < pos_end)
  {
    helper_CreateBackwardReferencesNH54_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH2(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H2 *privat = &hasher->privat._H2;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH2()) ? (((position + num_bytes) - StoreLookaheadH2()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH2(privat, dist_cache);
  while ((position + HashTypeLengthH2()) < pos_end)
  {
    helper_CreateBackwardReferencesNH2_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH35(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H35 *privat = &hasher->privat._H35;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH35()) ? (((position + num_bytes) - StoreLookaheadH35()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH35(privat, dist_cache);
  while ((position + HashTypeLengthH35()) < pos_end)
  {
    helper_CreateBackwardReferencesNH35_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH4(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H4 *privat = &hasher->privat._H4;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH4()) ? (((position + num_bytes) - StoreLookaheadH4()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH4(privat, dist_cache);
  while ((position + HashTypeLengthH4()) < pos_end)
  {
    helper_CreateBackwardReferencesNH4_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
static void CreateBackwardReferencesNH41(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H41 *privat = &hasher->privat._H41;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH41()) ? (((position + num_bytes) - StoreLookaheadH41()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH41(privat, dist_cache);
  while ((position + HashTypeLengthH41()) < pos_end)
  {
    helper_CreateBackwardReferencesNH41_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
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
static void CreateBackwardReferencesNH40(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H40 *privat = &hasher->privat._H40;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH40()) ? (((position + num_bytes) - StoreLookaheadH40()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH40(privat, dist_cache);
  while ((position + HashTypeLengthH40()) < pos_end)
  {
    helper_CreateBackwardReferencesNH40_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
static void CreateBackwardReferencesNH42(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H42 *privat = &hasher->privat._H42;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH42()) ? (((position + num_bytes) - StoreLookaheadH42()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH42(privat, dist_cache);
  while ((position + HashTypeLengthH42()) < pos_end)
  {
    helper_CreateBackwardReferencesNH42_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH3(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H3 *privat = &hasher->privat._H3;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH3()) ? (((position + num_bytes) - StoreLookaheadH3()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH3(privat, dist_cache);
  while ((position + HashTypeLengthH3()) < pos_end)
  {
    helper_CreateBackwardReferencesNH3_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH6(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H6 *privat = &hasher->privat._H6;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH6()) ? (((position + num_bytes) - StoreLookaheadH6()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH6(privat, dist_cache);
  while ((position + HashTypeLengthH6()) < pos_end)
  {
    helper_CreateBackwardReferencesNH6_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH65(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H65 *privat = &hasher->privat._H65;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH65()) ? (((position + num_bytes) - StoreLookaheadH65()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH65(privat, dist_cache);
  while ((position + HashTypeLengthH65()) < pos_end)
  {
    helper_CreateBackwardReferencesNH65_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH55(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H55 *privat = &hasher->privat._H55;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH55()) ? (((position + num_bytes) - StoreLookaheadH55()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH55(privat, dist_cache);
  while ((position + HashTypeLengthH55()) < pos_end)
  {
    helper_CreateBackwardReferencesNH55_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
static void CreateBackwardReferencesNH5(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  unsigned int commands_idx = 0;
  H5 *privat = &hasher->privat._H5;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t position_offset = params->stream_offset;
  const Command * const orig_commands = commands;
  size_t insert_length = *last_insert_len;
  const size_t pos_end = position + num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH5()) ? (((position + num_bytes) - StoreLookaheadH5()) + 1) : (position);
  const size_t random_heuristics_window_size = LiteralSpreeLengthForSparseSearch(params);
  size_t apply_random_heuristics = position + random_heuristics_window_size;
  const size_t gap = 0;
  const size_t kMinScore = ((30 * 8) * (sizeof(size_t))) + 100;
  (void) literal_context_lut;
  PrepareDistanceCacheH5(privat, dist_cache);
  while ((position + HashTypeLengthH5()) < pos_end)
  {
    helper_CreateBackwardReferencesNH5_1(&position, &commands_idx, &insert_length, &apply_random_heuristics, ringbuffer, ringbuffer_mask, params, dist_cache, commands, num_literals, privat, max_backward_limit, position_offset, pos_end, store_end, random_heuristics_window_size, gap, kMinScore);
  }

  insert_length += pos_end - position;
  *last_insert_len = insert_length;
  *num_commands += (size_t) ((&commands[commands_idx]) - orig_commands);
}


----------------------------
None
----------------------------
***/


inline static void SanitizeParams(BrotliEncoderParams *params)
{
  params->quality = brotli_min_int(11, brotli_max_int(0, params->quality));
  if (params->quality <= 2)
  {
    params->large_window = 0;
  }
  if (params->lgwin < 10)
  {
    params->lgwin = 10;
  }
  else
  {
    int max_lgwin = (params->large_window) ? (30) : (24);
    if (params->lgwin > max_lgwin)
    {
      params->lgwin = max_lgwin;
    }
  }
}


/*** DEPENDENCIES:
inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static int ComputeLgBlock(const BrotliEncoderParams *params)
{
  int lgblock = params->lgblock;
  if ((params->quality == 0) || (params->quality == 1))
  {
    lgblock = params->lgwin;
  }
  else
    if (params->quality < 4)
  {
    lgblock = 14;
  }
  else
    if (lgblock == 0)
  {
    lgblock = 16;
    if ((params->quality >= 9) && (params->lgwin > lgblock))
    {
      lgblock = brotli_min_int(18, params->lgwin);
    }
  }
  else
  {
    lgblock = brotli_min_int(24, brotli_max_int(16, lgblock));
  }
  return lgblock;
}


/*** DEPENDENCIES:
inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
None
----------------------------
***/


inline static void DestroyHasher(MemoryManager *m, Hasher *hasher)
{
  if (hasher->common.extra == 0)
  {
    return;
  }
  {
    BrotliFree(m, hasher->common.extra);
    hasher->common.extra = 0;
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
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
None
----------------------------
***/


