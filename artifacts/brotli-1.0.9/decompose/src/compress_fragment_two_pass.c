static int ShouldCompress(const uint8_t *input, size_t input_size, size_t num_literals)
{
  double corpus_size = (double) input_size;
  if (((double) num_literals) < (0.98 * corpus_size))
  {
    return 1;
  }
  else
  {
    uint32_t literal_histo[256] = {0};
    const double max_total_bit_cost = ((corpus_size * 8) * 0.98) / 43;
    size_t i;
    for (i = 0; i < input_size; i += 43)
    {
      literal_histo[input[i]] += 1;
    }

    return (!(!(BitsEntropy(literal_histo, 256) < max_total_bit_cost))) ? (1) : (0);
  }
}


/*** DEPENDENCIES:
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


// hint:  ['literals_idx_ref is a mutable refrence to unsigned int']
void helper_StoreCommands_1(unsigned int * const literals_idx_ref, const uint8_t * const literals, const uint32_t * const commands, size_t * const storage_ix, uint8_t * const storage, static const uint32_t kNumExtraBits[128], static const uint32_t kInsertOffset[24], uint8_t lit_depths[256], uint16_t lit_bits[256], uint8_t cmd_depths[128], uint16_t cmd_bits[128], size_t i)
{
  unsigned int literals_idx = *literals_idx_ref;
  const uint32_t cmd = commands[i];
  const uint32_t code = cmd & 0xFF;
  const uint32_t extra = cmd >> 8;
  ;
  BrotliWriteBits(cmd_depths[code], cmd_bits[code], storage_ix, storage);
  BrotliWriteBits(kNumExtraBits[code], extra, storage_ix, storage);
  if (code < 24)
  {
    const uint32_t insert = kInsertOffset[code] + extra;
    uint32_t j;
    for (j = 0; j < insert; j += 1)
    {
      const uint8_t lit = literals[literals_idx];
      BrotliWriteBits(lit_depths[lit], lit_bits[lit], storage_ix, storage);
      literals_idx += 1;
    }

  }
  *literals_idx_ref = literals_idx;
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


// hint:  ['candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_CreateCommands_1_1_2_1(unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, unsigned int ip_idx)
{
  unsigned int candidate_idx = *candidate_idx_ref;
  uint64_t input_bytes;
  uint32_t cur_hash;
  uint32_t prev_hash;
  if (min_match == 4)
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    cur_hash = HashBytesAtOffset(input_bytes, 3, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  else
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 4);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 2);
    cur_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  candidate_idx = base_ip + table[cur_hash];
  table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
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
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_CreateCommands_1_1_2(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = min_match + FindMatchLengthWithLimit((&candidate[candidate_idx]) + min_match, (&ip[ip_idx]) + min_match, ((size_t) (ip_end - (&ip[ip_idx]))) - min_match);
  ip_idx += matched;
  last_distance = (int) (base - (&candidate[candidate_idx]));
  ;
  EmitCopyLen(matched, commands);
  EmitDistance((uint32_t) last_distance, commands);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    helper_helper_helper_helper_CreateCommands_1_1_2_1(&candidate_idx, base_ip, table, min_match, ip, shift, ip_idx);
  }
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_helper_CreateCommands_1_1_2_1(unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, unsigned int ip_idx)
{
  unsigned int candidate_idx = *candidate_idx_ref;
  uint64_t input_bytes;
  uint32_t cur_hash;
  uint32_t prev_hash;
  if (min_match == 4)
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    cur_hash = HashBytesAtOffset(input_bytes, 3, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  else
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 4);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 2);
    cur_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  candidate_idx = base_ip + table[cur_hash];
  table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  *candidate_idx_ref = candidate_idx;
}


----------------------------
***/


// hint:  ['candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_CreateCommands_1_1_3_1(unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, unsigned int ip_idx)
{
  unsigned int candidate_idx = *candidate_idx_ref;
  uint64_t input_bytes;
  uint32_t cur_hash;
  uint32_t prev_hash;
  if (min_match == 4)
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    cur_hash = HashBytesAtOffset(input_bytes, 3, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  else
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 4);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 2);
    cur_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  candidate_idx = base_ip + table[cur_hash];
  table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
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
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_CreateCommands_1_1_3(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = min_match + FindMatchLengthWithLimit((&candidate[candidate_idx]) + min_match, (&ip[ip_idx]) + min_match, ((size_t) (ip_end - (&ip[ip_idx]))) - min_match);
  int distance = (int) (base - (&candidate[candidate_idx]));
  int insert = (int) (base - (&next_emit[next_emit_idx]));
  ip_idx += matched;
  ;
  EmitInsertLen((uint32_t) insert, commands);
  memcpy(*literals, next_emit, (size_t) insert);
  *literals += insert;
  if (distance == last_distance)
  {
    *(*commands) = 64;
    *commands += 1;
  }
  else
  {
    EmitDistance((uint32_t) distance, commands);
    last_distance = distance;
  }
  EmitCopyLenLastDistance(matched, commands);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    helper_helper_helper_helper_CreateCommands_1_1_3_1(&candidate_idx, base_ip, table, min_match, ip, shift, ip_idx);
  }
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
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
void helper_helper_helper_helper_CreateCommands_1_1_3_1(unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, unsigned int ip_idx)
{
  unsigned int candidate_idx = *candidate_idx_ref;
  uint64_t input_bytes;
  uint32_t cur_hash;
  uint32_t prev_hash;
  if (min_match == 4)
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 3);
    cur_hash = HashBytesAtOffset(input_bytes, 3, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  else
  {
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 5);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 4);
    prev_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 3);
    input_bytes = BrotliUnalignedRead64((&ip[ip_idx]) - 2);
    cur_hash = HashBytesAtOffset(input_bytes, 2, shift, min_match);
    prev_hash = HashBytesAtOffset(input_bytes, 0, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 2);
    prev_hash = HashBytesAtOffset(input_bytes, 1, shift, min_match);
    table[prev_hash] = (int) (((&ip[ip_idx]) - base_ip) - 1);
  }
  candidate_idx = base_ip + table[cur_hash];
  table[cur_hash] = (int) ((&ip[ip_idx]) - base_ip);
  *candidate_idx_ref = candidate_idx;
}


----------------------------
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_hash_ref is a mutable refrence to uint32_t', 'skip_ref is a mutable refrence to uint32_t', 'next_ip_idx_ref is a mutable refrence to unsigned int', 'candidate_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_CreateCommands_1_1_1(unsigned int * const ip_idx_ref, uint32_t * const next_hash_ref, uint32_t * const skip_ref, unsigned int * const next_ip_idx_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, int last_distance, const uint8_t * const next_ip, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = *skip_ref;
  unsigned int next_ip_idx = *next_ip_idx_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  uint32_t hash = next_hash;
  uint32_t bytes_between_hash_lookups = (skip++) >> 5;
  skip += 1;
  ip_idx = &next_ip[next_ip_idx];
  ;
  next_ip_idx = (&ip[ip_idx]) + bytes_between_hash_lookups;
  if (__builtin_expect((&next_ip[next_ip_idx]) > ip_limit, 0))
  {
    goto emit_remainder;
  }
  next_hash = Hash(next_ip, shift, min_match);
  candidate_idx = (&ip[ip_idx]) - last_distance;
  if (IsMatch(ip, candidate, min_match))
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


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int', 'next_hash_ref is a mutable refrence to uint32_t']
void helper_helper_CreateCommands_1_1(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, uint32_t * const next_hash_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const uint8_t * const ip_limit)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
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
    helper_helper_helper_CreateCommands_1_1_1(&ip_idx, &next_hash, &skip, &next_ip_idx, &candidate_idx, base_ip, table, min_match, ip, shift, ip_limit, last_distance, next_ip, candidate);
  }
  while (__builtin_expect(!(!(!IsMatch(ip, candidate, min_match))), 1));

  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    goto trawl;
  }
  {
    helper_helper_helper_CreateCommands_1_1_3(&ip_idx, &next_emit_idx, &last_distance, &candidate_idx, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, ip_limit, candidate);
  }
  while ((((&ip[ip_idx]) - (&candidate[candidate_idx])) <= ((long) ((((size_t) 1) << 18) - 16))) && IsMatch(ip, candidate, min_match))
  {
    helper_helper_helper_CreateCommands_1_1_2(&ip_idx, &next_emit_idx, &last_distance, &candidate_idx, base_ip, table, min_match, commands, ip, shift, ip_end, ip_limit, candidate);
  }

  ip_idx += 1;
  next_hash = Hash(ip, shift, min_match);
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
  *next_hash_ref = next_hash;
}


/*** DEPENDENCIES:
void helper_helper_helper_CreateCommands_1_1_2(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = min_match + FindMatchLengthWithLimit((&candidate[candidate_idx]) + min_match, (&ip[ip_idx]) + min_match, ((size_t) (ip_end - (&ip[ip_idx]))) - min_match);
  ip_idx += matched;
  last_distance = (int) (base - (&candidate[candidate_idx]));
  ;
  EmitCopyLen(matched, commands);
  EmitDistance((uint32_t) last_distance, commands);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    helper_helper_helper_helper_CreateCommands_1_1_2_1(&candidate_idx, base_ip, table, min_match, ip, shift, ip_idx);
  }
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


----------------------------
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
void helper_helper_helper_CreateCommands_1_1_3(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const uint8_t * const ip_limit, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  const uint8_t *base = ip;
  size_t matched = min_match + FindMatchLengthWithLimit((&candidate[candidate_idx]) + min_match, (&ip[ip_idx]) + min_match, ((size_t) (ip_end - (&ip[ip_idx]))) - min_match);
  int distance = (int) (base - (&candidate[candidate_idx]));
  int insert = (int) (base - (&next_emit[next_emit_idx]));
  ip_idx += matched;
  ;
  EmitInsertLen((uint32_t) insert, commands);
  memcpy(*literals, next_emit, (size_t) insert);
  *literals += insert;
  if (distance == last_distance)
  {
    *(*commands) = 64;
    *commands += 1;
  }
  else
  {
    EmitDistance((uint32_t) distance, commands);
    last_distance = distance;
  }
  EmitCopyLenLastDistance(matched, commands);
  next_emit_idx = &ip[ip_idx];
  if (__builtin_expect((&ip[ip_idx]) >= ip_limit, 0))
  {
    goto emit_remainder;
  }
  {
    helper_helper_helper_helper_CreateCommands_1_1_3_1(&candidate_idx, base_ip, table, min_match, ip, shift, ip_idx);
  }
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
  *candidate_idx_ref = candidate_idx;
}


----------------------------
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
void helper_helper_helper_CreateCommands_1_1_1(unsigned int * const ip_idx_ref, uint32_t * const next_hash_ref, uint32_t * const skip_ref, unsigned int * const next_ip_idx_ref, unsigned int * const candidate_idx_ref, const uint8_t * const base_ip, int * const table, size_t min_match, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_limit, int last_distance, const uint8_t * const next_ip, const uint8_t * const candidate)
{
  unsigned int ip_idx = *ip_idx_ref;
  uint32_t next_hash = *next_hash_ref;
  uint32_t skip = *skip_ref;
  unsigned int next_ip_idx = *next_ip_idx_ref;
  unsigned int candidate_idx = *candidate_idx_ref;
  uint32_t hash = next_hash;
  uint32_t bytes_between_hash_lookups = (skip++) >> 5;
  skip += 1;
  ip_idx = &next_ip[next_ip_idx];
  ;
  next_ip_idx = (&ip[ip_idx]) + bytes_between_hash_lookups;
  if (__builtin_expect((&next_ip[next_ip_idx]) > ip_limit, 0))
  {
    goto emit_remainder;
  }
  next_hash = Hash(next_ip, shift, min_match);
  candidate_idx = (&ip[ip_idx]) - last_distance;
  if (IsMatch(ip, candidate, min_match))
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
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int', 'next_emit_idx_ref is a mutable refrence to unsigned int', 'last_distance_ref is a mutable refrence to int']
void helper_CreateCommands_1(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, const uint8_t * const input, size_t block_size, size_t input_size, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const size_t kInputMarginBytes)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  const size_t len_limit = brotli_min_size_t(block_size - min_match, input_size - kInputMarginBytes);
  const uint8_t *ip_limit = input + len_limit;
  uint32_t next_hash;
  for (next_hash = Hash(++(&ip[ip_idx]), shift, min_match);;)
  {
    helper_helper_CreateCommands_1_1(&ip_idx, &next_emit_idx, &last_distance, &next_hash, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, ip_limit);
  }

  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
void helper_helper_CreateCommands_1_1(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, uint32_t * const next_hash_ref, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const uint8_t * const ip_limit)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
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
    helper_helper_helper_CreateCommands_1_1_1(&ip_idx, &next_hash, &skip, &next_ip_idx, &candidate_idx, base_ip, table, min_match, ip, shift, ip_limit, last_distance, next_ip, candidate);
  }
  while (__builtin_expect(!(!(!IsMatch(ip, candidate, min_match))), 1));

  if (((&ip[ip_idx]) - (&candidate[candidate_idx])) > ((long) ((((size_t) 1) << 18) - 16)))
  {
    goto trawl;
  }
  {
    helper_helper_helper_CreateCommands_1_1_3(&ip_idx, &next_emit_idx, &last_distance, &candidate_idx, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, ip_limit, candidate);
  }
  while ((((&ip[ip_idx]) - (&candidate[candidate_idx])) <= ((long) ((((size_t) 1) << 18) - 16))) && IsMatch(ip, candidate, min_match))
  {
    helper_helper_helper_CreateCommands_1_1_2(&ip_idx, &next_emit_idx, &last_distance, &candidate_idx, base_ip, table, min_match, commands, ip, shift, ip_end, ip_limit, candidate);
  }

  ip_idx += 1;
  next_hash = Hash(ip, shift, min_match);
  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
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


inline static void CreateCommands(const uint8_t *input, size_t block_size, size_t input_size, const uint8_t *base_ip, int *table, size_t table_bits, size_t min_match, uint8_t **literals, uint32_t **commands)
{
  const uint8_t *ip = input;
  unsigned int ip_idx = 0;
  const size_t shift = 64u - table_bits;
  const uint8_t *ip_end = input + block_size;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  int last_distance = -1;
  const size_t kInputMarginBytes = 16;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_CreateCommands_1(&ip_idx, &next_emit_idx, &last_distance, input, block_size, input_size, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, kInputMarginBytes);
  }
  emit_remainder:
  ;

  if ((&next_emit[next_emit_idx]) < ip_end)
  {
    const uint32_t insert = (uint32_t) (ip_end - (&next_emit[next_emit_idx]));
    EmitInsertLen(insert, commands);
    memcpy(*literals, next_emit, insert);
    *literals += insert;
  }
}


/*** DEPENDENCIES:
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
void helper_CreateCommands_1(unsigned int * const ip_idx_ref, unsigned int * const next_emit_idx_ref, int * const last_distance_ref, const uint8_t * const input, size_t block_size, size_t input_size, const uint8_t * const base_ip, int * const table, size_t min_match, uint8_t ** const literals, uint32_t ** const commands, const uint8_t * const ip, const size_t shift, const uint8_t * const ip_end, const uint8_t * const next_emit, const size_t kInputMarginBytes)
{
  unsigned int ip_idx = *ip_idx_ref;
  unsigned int next_emit_idx = *next_emit_idx_ref;
  int last_distance = *last_distance_ref;
  const size_t len_limit = brotli_min_size_t(block_size - min_match, input_size - kInputMarginBytes);
  const uint8_t *ip_limit = input + len_limit;
  uint32_t next_hash;
  for (next_hash = Hash(++(&ip[ip_idx]), shift, min_match);;)
  {
    helper_helper_CreateCommands_1_1(&ip_idx, &next_emit_idx, &last_distance, &next_hash, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, ip_limit);
  }

  *ip_idx_ref = ip_idx;
  *next_emit_idx_ref = next_emit_idx;
  *last_distance_ref = last_distance;
}


----------------------------
***/


static void StoreCommands(MemoryManager *m, const uint8_t *literals, const size_t num_literals, const uint32_t *commands, const size_t num_commands, size_t *storage_ix, uint8_t *storage)
{
  unsigned int literals_idx = 0;
  static const uint32_t kNumExtraBits[128] = {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 12, 14, 24, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24};
  static const uint32_t kInsertOffset[24] = {0, 1, 2, 3, 4, 5, 6, 8, 10, 14, 18, 26, 34, 50, 66, 98, 130, 194, 322, 578, 1090, 2114, 6210, 22594};
  uint8_t lit_depths[256];
  uint16_t lit_bits[256];
  uint32_t lit_histo[256] = {0};
  uint8_t cmd_depths[128] = {0};
  uint16_t cmd_bits[128] = {0};
  uint32_t cmd_histo[128] = {0};
  size_t i;
  for (i = 0; i < num_literals; i += 1)
  {
    lit_histo[literals[i + literals_idx]] += 1;
  }

  BrotliBuildAndStoreHuffmanTreeFast(m, lit_histo, num_literals, 8, lit_depths, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const uint32_t code = commands[i] & 0xFF;
    ;
    cmd_histo[code] += 1;
  }

  cmd_histo[1] += 1;
  cmd_histo[2] += 1;
  cmd_histo[64] += 1;
  cmd_histo[84] += 1;
  BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depths, cmd_bits, storage_ix, storage);
  for (i = 0; i < num_commands; i += 1)
  {
    helper_StoreCommands_1(&literals_idx, literals, commands, storage_ix, storage, kNumExtraBits, kInsertOffset, lit_depths, lit_bits, cmd_depths, cmd_bits, i);
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
void helper_StoreCommands_1(unsigned int * const literals_idx_ref, const uint8_t * const literals, const uint32_t * const commands, size_t * const storage_ix, uint8_t * const storage, static const uint32_t kNumExtraBits[128], static const uint32_t kInsertOffset[24], uint8_t lit_depths[256], uint16_t lit_bits[256], uint8_t cmd_depths[128], uint16_t cmd_bits[128], size_t i)
{
  unsigned int literals_idx = *literals_idx_ref;
  const uint32_t cmd = commands[i];
  const uint32_t code = cmd & 0xFF;
  const uint32_t extra = cmd >> 8;
  ;
  BrotliWriteBits(cmd_depths[code], cmd_bits[code], storage_ix, storage);
  BrotliWriteBits(kNumExtraBits[code], extra, storage_ix, storage);
  if (code < 24)
  {
    const uint32_t insert = kInsertOffset[code] + extra;
    uint32_t j;
    for (j = 0; j < insert; j += 1)
    {
      const uint8_t lit = literals[literals_idx];
      BrotliWriteBits(lit_depths[lit], lit_bits[lit], storage_ix, storage);
      literals_idx += 1;
    }

  }
  *literals_idx_ref = literals_idx;
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
***/


inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


/*** DEPENDENCIES:
static const size_t kCompressFragmentTwoPassBlockSize = 1 << 17
----------------------------
static void StoreCommands(MemoryManager *m, const uint8_t *literals, const size_t num_literals, const uint32_t *commands, const size_t num_commands, size_t *storage_ix, uint8_t *storage)
{
  unsigned int literals_idx = 0;
  static const uint32_t kNumExtraBits[128] = {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 12, 14, 24, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8, 9, 10, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24};
  static const uint32_t kInsertOffset[24] = {0, 1, 2, 3, 4, 5, 6, 8, 10, 14, 18, 26, 34, 50, 66, 98, 130, 194, 322, 578, 1090, 2114, 6210, 22594};
  uint8_t lit_depths[256];
  uint16_t lit_bits[256];
  uint32_t lit_histo[256] = {0};
  uint8_t cmd_depths[128] = {0};
  uint16_t cmd_bits[128] = {0};
  uint32_t cmd_histo[128] = {0};
  size_t i;
  for (i = 0; i < num_literals; i += 1)
  {
    lit_histo[literals[i + literals_idx]] += 1;
  }

  BrotliBuildAndStoreHuffmanTreeFast(m, lit_histo, num_literals, 8, lit_depths, lit_bits, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < num_commands; i += 1)
  {
    const uint32_t code = commands[i] & 0xFF;
    ;
    cmd_histo[code] += 1;
  }

  cmd_histo[1] += 1;
  cmd_histo[2] += 1;
  cmd_histo[64] += 1;
  cmd_histo[84] += 1;
  BuildAndStoreCommandPrefixCode(cmd_histo, cmd_depths, cmd_bits, storage_ix, storage);
  for (i = 0; i < num_commands; i += 1)
  {
    helper_StoreCommands_1(&literals_idx, literals, commands, storage_ix, storage, kNumExtraBits, kInsertOffset, lit_depths, lit_bits, cmd_depths, cmd_bits, i);
  }

}


----------------------------
static int ShouldCompress(const uint8_t *input, size_t input_size, size_t num_literals)
{
  double corpus_size = (double) input_size;
  if (((double) num_literals) < (0.98 * corpus_size))
  {
    return 1;
  }
  else
  {
    uint32_t literal_histo[256] = {0};
    const double max_total_bit_cost = ((corpus_size * 8) * 0.98) / 43;
    size_t i;
    for (i = 0; i < input_size; i += 43)
    {
      literal_histo[input[i]] += 1;
    }

    return (!(!(BitsEntropy(literal_histo, 256) < max_total_bit_cost))) ? (1) : (0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static void CreateCommands(const uint8_t *input, size_t block_size, size_t input_size, const uint8_t *base_ip, int *table, size_t table_bits, size_t min_match, uint8_t **literals, uint32_t **commands)
{
  const uint8_t *ip = input;
  unsigned int ip_idx = 0;
  const size_t shift = 64u - table_bits;
  const uint8_t *ip_end = input + block_size;
  const uint8_t *next_emit = input;
  unsigned int next_emit_idx = 0;
  int last_distance = -1;
  const size_t kInputMarginBytes = 16;
  if (__builtin_expect(!(!(block_size >= kInputMarginBytes)), 1))
  {
    helper_CreateCommands_1(&ip_idx, &next_emit_idx, &last_distance, input, block_size, input_size, base_ip, table, min_match, literals, commands, ip, shift, ip_end, next_emit, kInputMarginBytes);
  }
  emit_remainder:
  ;

  if ((&next_emit[next_emit_idx]) < ip_end)
  {
    const uint32_t insert = (uint32_t) (ip_end - (&next_emit[next_emit_idx]));
    EmitInsertLen(insert, commands);
    memcpy(*literals, next_emit, insert);
    *literals += insert;
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


static void BrotliCompressFragmentTwoPassImpl8(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (8 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 8, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl9(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (9 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 9, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl10(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (10 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 10, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl11(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (11 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 11, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl12(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (12 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 12, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl13(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (13 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 13, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl14(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (14 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 14, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl15(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (15 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 15, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl16(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (16 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 16, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


static void BrotliCompressFragmentTwoPassImpl17(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (17 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 17, min_match, storage_ix, storage);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliCompressFragmentTwoPassImpl(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_bits, size_t min_match, size_t *storage_ix, uint8_t *storage)
{
  unsigned int input_idx = 0;
  const uint8_t *base_ip = input;
  (void) is_last;
  while (input_size > 0)
  {
    size_t block_size = brotli_min_size_t(input_size, kCompressFragmentTwoPassBlockSize);
    uint32_t *commands = command_buf;
    uint8_t *literals = literal_buf;
    size_t num_literals;
    CreateCommands(input, block_size, input_size, base_ip, table, table_bits, min_match, &literals, &commands);
    num_literals = (size_t) (literals - literal_buf);
    if (ShouldCompress(input, block_size, num_literals))
    {
      const size_t num_commands = (size_t) (commands - command_buf);
      BrotliStoreMetaBlockHeader(block_size, 0, storage_ix, storage);
      BrotliWriteBits(13, 0, storage_ix, storage);
      StoreCommands(m, literal_buf, num_literals, command_buf, num_commands, storage_ix, storage);
      if (!(!0))
      {
        return;
      }
    }
    else
    {
      EmitUncompressedMetaBlock(input, block_size, storage_ix, storage);
    }
    input_idx += block_size;
    input_size -= block_size;
  }

}


----------------------------
***/


void BrotliCompressFragmentTwoPass(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_size, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  switch (table_bits)
  {
    case 8:
    {
      BrotliCompressFragmentTwoPassImpl8(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 9:
    {
      BrotliCompressFragmentTwoPassImpl9(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 10:
    {
      BrotliCompressFragmentTwoPassImpl10(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentTwoPassImpl11(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 12:
    {
      BrotliCompressFragmentTwoPassImpl12(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentTwoPassImpl13(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 14:
    {
      BrotliCompressFragmentTwoPassImpl14(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentTwoPassImpl15(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 16:
    {
      BrotliCompressFragmentTwoPassImpl16(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 17:
    {
      BrotliCompressFragmentTwoPassImpl17(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
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
    RewindBitPosition(initial_storage_ix, storage_ix, storage);
    EmitUncompressedMetaBlock(input, input_size, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


/*** DEPENDENCIES:
static void BrotliCompressFragmentTwoPassImpl8(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (8 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 8, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl12(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (12 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 12, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl9(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (9 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 9, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl15(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (15 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 15, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl17(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (17 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 17, min_match, storage_ix, storage);
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
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void RewindBitPosition(const size_t new_storage_ix, size_t *storage_ix, uint8_t *storage)
{
  const size_t bitpos = new_storage_ix & 7;
  const size_t mask = (1u << bitpos) - 1;
  storage[new_storage_ix >> 3] &= (uint8_t) mask;
  *storage_ix = new_storage_ix;
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl10(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (10 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 10, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl11(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (11 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 11, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl13(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (13 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 13, min_match, storage_ix, storage);
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
static void BrotliCompressFragmentTwoPassImpl14(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (14 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 14, min_match, storage_ix, storage);
}


----------------------------
static void BrotliCompressFragmentTwoPassImpl16(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t *storage_ix, uint8_t *storage)
{
  size_t min_match = (16 <= 15) ? (4) : (6);
  BrotliCompressFragmentTwoPassImpl(m, input, input_size, is_last, command_buf, literal_buf, table, 16, min_match, storage_ix, storage);
}


----------------------------
***/


