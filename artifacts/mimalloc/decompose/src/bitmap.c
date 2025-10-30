inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


/*** DEPENDENCIES:
None
----------------------------
***/


bool _mi_bitmap_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *any_zero)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 149, __func__));
  (void) bitmap_fields;
  size_t prev = atomic_fetch_or_explicit(&bitmap[idx], mask, memory_order_acq_rel);
  if (any_zero != 0)
  {
    *any_zero = (prev & mask) != mask;
  }
  return (prev & mask) == 0;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx % (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
None
----------------------------
***/


static size_t mi_bitmap_mask_across(mi_bitmap_index_t bitmap_idx, size_t bitmap_fields, size_t count, size_t *pre_mask, size_t *mid_mask, size_t *post_mask)
{
  (void) bitmap_fields;
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  if (__builtin_expect(!(!((bitidx + count) <= (8 * (1 << 3)))), 1))
  {
    *pre_mask = mi_bitmap_mask_(count, bitidx);
    *mid_mask = 0;
    *post_mask = 0;
    (mi_bitmap_index_field(bitmap_idx) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 330, __func__));
    return 0;
  }
  else
  {
    const size_t pre_bits = (8 * (1 << 3)) - bitidx;
    (pre_bits < count) ? ((void) 0) : (_mi_assert_fail("pre_bits < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 335, __func__));
    *pre_mask = mi_bitmap_mask_(pre_bits, bitidx);
    count -= pre_bits;
    const size_t mid_count = count / (8 * (1 << 3));
    *mid_mask = ~((size_t) 0);
    count %= 8 * (1 << 3);
    *post_mask = (count == 0) ? (0) : (mi_bitmap_mask_(count, 0));
    (((mi_bitmap_index_field(bitmap_idx) + mid_count) + ((count == 0) ? (0) : (1))) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) + mid_count + (count==0 ? 0 : 1) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 342, __func__));
    return mid_count;
  }
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx % (8 * (1 << 3));
}


----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_claim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *pany_zero, size_t *already_set)
{
  size_t idx = mi_bitmap_index_field(bitmap_idx);
  size_t pre_mask;
  size_t mid_mask;
  size_t post_mask;
  size_t mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &pre_mask, &mid_mask, &post_mask);
  bool all_zero = 1;
  bool any_zero = 0;
  size_t one_count = 0;
  _Atomic size_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t prev = atomic_fetch_or_explicit(field, pre_mask, memory_order_acq_rel);
  field_idx += 1;
  if ((prev & pre_mask) != 0)
  {
    all_zero = 0;
    one_count += mi_popcount(prev & pre_mask);
  }
  if ((prev & pre_mask) != pre_mask)
  {
    any_zero = 1;
  }
  while ((mid_count--) > 0)
  {
    prev = atomic_fetch_or_explicit(field, mid_mask, memory_order_acq_rel);
    field_idx += 1;
    if ((prev & mid_mask) != 0)
    {
      all_zero = 0;
      one_count += mi_popcount(prev & mid_mask);
    }
    if ((prev & mid_mask) != mid_mask)
    {
      any_zero = 1;
    }
  }

  if (post_mask != 0)
  {
    prev = atomic_fetch_or_explicit(field, post_mask, memory_order_acq_rel);
    if ((prev & post_mask) != 0)
    {
      all_zero = 0;
      one_count += mi_popcount(prev & post_mask);
    }
    if ((prev & post_mask) != post_mask)
    {
      any_zero = 1;
    }
  }
  if (pany_zero != 0)
  {
    *pany_zero = any_zero;
  }
  if (already_set != 0)
  {
    *already_set = one_count;
  }
  ;
  ((all_zero) ? (one_count == 0) : (one_count <= count)) ? ((void) 0) : (_mi_assert_fail("all_zero ? one_count == 0 : one_count <= count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 397, __func__));
  return all_zero;
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
static size_t mi_bitmap_mask_across(mi_bitmap_index_t bitmap_idx, size_t bitmap_fields, size_t count, size_t *pre_mask, size_t *mid_mask, size_t *post_mask)
{
  (void) bitmap_fields;
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  if (__builtin_expect(!(!((bitidx + count) <= (8 * (1 << 3)))), 1))
  {
    *pre_mask = mi_bitmap_mask_(count, bitidx);
    *mid_mask = 0;
    *post_mask = 0;
    (mi_bitmap_index_field(bitmap_idx) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 330, __func__));
    return 0;
  }
  else
  {
    const size_t pre_bits = (8 * (1 << 3)) - bitidx;
    (pre_bits < count) ? ((void) 0) : (_mi_assert_fail("pre_bits < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 335, __func__));
    *pre_mask = mi_bitmap_mask_(pre_bits, bitidx);
    count -= pre_bits;
    const size_t mid_count = count / (8 * (1 << 3));
    *mid_mask = ~((size_t) 0);
    count %= 8 * (1 << 3);
    *post_mask = (count == 0) ? (0) : (mi_bitmap_mask_(count, 0));
    (((mi_bitmap_index_field(bitmap_idx) + mid_count) + ((count == 0) ? (0) : (1))) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) + mid_count + (count==0 ? 0 : 1) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 342, __func__));
    return mid_count;
  }
}


----------------------------
inline static size_t mi_popcount(size_t x)
{
  if (x <= 1)
  {
    return x;
  }
  if (x == SIZE_MAX)
  {
    return (1 << 3) * 8;
  }
  return __builtin_popcountll(x);
}


----------------------------
None
----------------------------
***/


inline bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 45, __func__));
  (count <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 46, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 47, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  if (map == (~((size_t) 0)))
  {
    return 0;
  }
  const size_t mask = mi_bitmap_mask_(count, 0);
  const size_t bitidx_max = (8 * (1 << 3)) - count;
  size_t bitidx = mi_ctz(~map);
  size_t m = mask << bitidx;
  while (bitidx <= bitidx_max)
  {
    const size_t mapm = map & m;
    if (mapm == 0)
    {
      ((m >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(m >> bitidx) == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 67, __func__));
      const size_t newmap = map | m;
      (((newmap ^ map) >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(newmap^map) >> bitidx == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 69, __func__));
      if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
      {
        continue;
      }
      else
      {
        *bitmap_idx = mi_bitmap_index_create(idx, bitidx);
        return 1;
      }
    }
    else
    {
      (mapm != 0) ? ((void) 0) : (_mi_assert_fail("mapm != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 83, __func__));
      const size_t shift = (count == 1) ? (1) : ((((1 << 3) * 8) - mi_clz(mapm)) - bitidx);
      ((shift > 0) && (shift <= count)) ? ((void) 0) : (_mi_assert_fail("shift > 0 && shift <= count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 85, __func__));
      bitidx += shift;
      m <<= shift;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}


----------------------------
inline static mi_bitmap_index_t mi_bitmap_index_create(size_t idx, size_t bitidx)
{
  (bitidx < (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("bitidx < MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 43, __func__));
  return mi_bitmap_index_create_ex(idx, bitidx);
}


----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
inline static size_t mi_ctz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_ctzll(x);
}


----------------------------
typedef _Atomic size_t mi_bitmap_field_t
----------------------------
None
----------------------------
***/


bool _mi_bitmap_try_find_from_claim(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  size_t idx = start_field_idx;
  for (size_t visited = 0; visited < bitmap_fields; visited += 1, idx += 1)
  {
    if (idx >= bitmap_fields)
    {
      idx = 0;
    }
    if (_mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
inline bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 45, __func__));
  (count <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 46, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 47, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  if (map == (~((size_t) 0)))
  {
    return 0;
  }
  const size_t mask = mi_bitmap_mask_(count, 0);
  const size_t bitidx_max = (8 * (1 << 3)) - count;
  size_t bitidx = mi_ctz(~map);
  size_t m = mask << bitidx;
  while (bitidx <= bitidx_max)
  {
    const size_t mapm = map & m;
    if (mapm == 0)
    {
      ((m >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(m >> bitidx) == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 67, __func__));
      const size_t newmap = map | m;
      (((newmap ^ map) >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(newmap^map) >> bitidx == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 69, __func__));
      if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
      {
        continue;
      }
      else
      {
        *bitmap_idx = mi_bitmap_index_create(idx, bitidx);
        return 1;
      }
    }
    else
    {
      (mapm != 0) ? ((void) 0) : (_mi_assert_fail("mapm != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 83, __func__));
      const size_t shift = (count == 1) ? (1) : ((((1 << 3) * 8) - mi_clz(mapm)) - bitidx);
      ((shift > 0) && (shift <= count)) ? ((void) 0) : (_mi_assert_fail("shift > 0 && shift <= count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 85, __func__));
      bitidx += shift;
      m <<= shift;
    }
  }

  return 0;
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


static bool mi_bitmap_try_find_claim_field_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t idx, const size_t count, const size_t retries, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 205, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  const size_t initial = mi_clz(map);
  (initial <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("initial <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 211, __func__));
  if (initial == 0)
  {
    return 0;
  }
  if (initial >= count)
  {
    return _mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx);
  }
  if (_mi_divide_up(count - initial, 8 * (1 << 3)) >= (bitmap_fields - idx))
  {
    return 0;
  }
  size_t found = initial;
  size_t mask = 0;
  while (found < count)
  {
    field_idx += 1;
    map = atomic_load_explicit(field, memory_order_relaxed);
    const size_t mask_bits = ((found + (8 * (1 << 3))) <= count) ? (8 * (1 << 3)) : (count - found);
    ((mask_bits > 0) && (mask_bits <= (8 * (1 << 3)))) ? ((void) 0) : (_mi_assert_fail("mask_bits > 0 && mask_bits <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 223, __func__));
    mask = mi_bitmap_mask_(mask_bits, 0);
    if ((map & mask) != 0)
    {
      return 0;
    }
    found += mask_bits;
  }

  ((&field[field_idx]) < (&bitmap[bitmap_fields])) ? ((void) 0) : (_mi_assert_fail("field < &bitmap[bitmap_fields]", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 228, __func__));
  mi_bitmap_field_t * const final_field = field;
  const size_t final_mask = mask;
  mi_bitmap_field_t * const initial_field = &bitmap[idx];
  const size_t initial_idx = (8 * (1 << 3)) - initial;
  const size_t initial_mask = mi_bitmap_mask_(initial, initial_idx);
  size_t newmap;
  field_idx = initial_field;
  map = atomic_load_explicit(field, memory_order_relaxed);
  do
  {
    newmap = map | initial_mask;
    if ((map & initial_mask) != 0)
    {
      goto rollback;
    }
    ;
  }
  while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  while ((++(&field[field_idx])) < final_field)
  {
    newmap = ~((size_t) 0);
    map = 0;
    if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
    {
      goto rollback;
    }
  }

  ((&field[field_idx]) == final_field) ? ((void) 0) : (_mi_assert_fail("field == final_field", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 255, __func__));
  map = atomic_load_explicit(field, memory_order_relaxed);
  do
  {
    newmap = map | final_mask;
    if ((map & final_mask) != 0)
    {
      goto rollback;
    }
  }
  while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  *bitmap_idx = mi_bitmap_index_create(idx, initial_idx);
  return 1;
  rollback:
  while ((--(&field[field_idx])) > initial_field)
  {
    newmap = 0;
    map = ~((size_t) 0);
    (atomic_load_explicit(field, memory_order_relaxed) == map) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(field) == map", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 272, __func__));
    atomic_store_explicit(field, newmap, memory_order_release);
  }


  if ((&field[field_idx]) == initial_field)
  {
    map = atomic_load_explicit(field, memory_order_relaxed);
    do
    {
      ((map & initial_mask) == initial_mask) ? ((void) 0) : (_mi_assert_fail("(map & initial_mask) == initial_mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 278, __func__));
      newmap = map & (~initial_mask);
    }
    while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  }
  _mi_stat_counter_increase(&_mi_stats_main.arena_rollback_count, 1);
  if (retries <= 2)
  {
    return mi_bitmap_try_find_claim_field_across(bitmap, bitmap_fields, idx, count, retries + 1, bitmap_idx);
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 421, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 45, __func__));
  (count <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 46, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 47, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  if (map == (~((size_t) 0)))
  {
    return 0;
  }
  const size_t mask = mi_bitmap_mask_(count, 0);
  const size_t bitidx_max = (8 * (1 << 3)) - count;
  size_t bitidx = mi_ctz(~map);
  size_t m = mask << bitidx;
  while (bitidx <= bitidx_max)
  {
    const size_t mapm = map & m;
    if (mapm == 0)
    {
      ((m >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(m >> bitidx) == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 67, __func__));
      const size_t newmap = map | m;
      (((newmap ^ map) >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(newmap^map) >> bitidx == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 69, __func__));
      if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
      {
        continue;
      }
      else
      {
        *bitmap_idx = mi_bitmap_index_create(idx, bitidx);
        return 1;
      }
    }
    else
    {
      (mapm != 0) ? ((void) 0) : (_mi_assert_fail("mapm != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 83, __func__));
      const size_t shift = (count == 1) ? (1) : ((((1 << 3) * 8) - mi_clz(mapm)) - bitidx);
      ((shift > 0) && (shift <= count)) ? ((void) 0) : (_mi_assert_fail("shift > 0 && shift <= count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 85, __func__));
      bitidx += shift;
      m <<= shift;
    }
  }

  return 0;
}


----------------------------
inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}


----------------------------
inline static mi_bitmap_index_t mi_bitmap_index_create(size_t idx, size_t bitidx)
{
  (bitidx < (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("bitidx < MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 43, __func__));
  return mi_bitmap_index_create_ex(idx, bitidx);
}


----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
typedef _Atomic size_t mi_bitmap_field_t
----------------------------
void _mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  if (mi_is_in_main(stat))
  {
    mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
  }
  else
  {
    stat->total += amount;
  }
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_try_find_from_claim_across(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 296, __func__));
  if (count <= 2)
  {
    return _mi_bitmap_try_find_from_claim(bitmap, bitmap_fields, start_field_idx, count, bitmap_idx);
  }
  size_t idx = start_field_idx;
  for (size_t visited = 0; visited < bitmap_fields; visited += 1, idx += 1)
  {
    if (idx >= bitmap_fields)
    {
      idx = 0;
    }
    if (mi_bitmap_try_find_claim_field_across(bitmap, bitmap_fields, idx, count, 0, bitmap_idx))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static bool mi_bitmap_try_find_claim_field_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t idx, const size_t count, const size_t retries, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 205, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  const size_t initial = mi_clz(map);
  (initial <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("initial <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 211, __func__));
  if (initial == 0)
  {
    return 0;
  }
  if (initial >= count)
  {
    return _mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx);
  }
  if (_mi_divide_up(count - initial, 8 * (1 << 3)) >= (bitmap_fields - idx))
  {
    return 0;
  }
  size_t found = initial;
  size_t mask = 0;
  while (found < count)
  {
    field_idx += 1;
    map = atomic_load_explicit(field, memory_order_relaxed);
    const size_t mask_bits = ((found + (8 * (1 << 3))) <= count) ? (8 * (1 << 3)) : (count - found);
    ((mask_bits > 0) && (mask_bits <= (8 * (1 << 3)))) ? ((void) 0) : (_mi_assert_fail("mask_bits > 0 && mask_bits <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 223, __func__));
    mask = mi_bitmap_mask_(mask_bits, 0);
    if ((map & mask) != 0)
    {
      return 0;
    }
    found += mask_bits;
  }

  ((&field[field_idx]) < (&bitmap[bitmap_fields])) ? ((void) 0) : (_mi_assert_fail("field < &bitmap[bitmap_fields]", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 228, __func__));
  mi_bitmap_field_t * const final_field = field;
  const size_t final_mask = mask;
  mi_bitmap_field_t * const initial_field = &bitmap[idx];
  const size_t initial_idx = (8 * (1 << 3)) - initial;
  const size_t initial_mask = mi_bitmap_mask_(initial, initial_idx);
  size_t newmap;
  field_idx = initial_field;
  map = atomic_load_explicit(field, memory_order_relaxed);
  do
  {
    newmap = map | initial_mask;
    if ((map & initial_mask) != 0)
    {
      goto rollback;
    }
    ;
  }
  while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  while ((++(&field[field_idx])) < final_field)
  {
    newmap = ~((size_t) 0);
    map = 0;
    if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
    {
      goto rollback;
    }
  }

  ((&field[field_idx]) == final_field) ? ((void) 0) : (_mi_assert_fail("field == final_field", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 255, __func__));
  map = atomic_load_explicit(field, memory_order_relaxed);
  do
  {
    newmap = map | final_mask;
    if ((map & final_mask) != 0)
    {
      goto rollback;
    }
  }
  while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  *bitmap_idx = mi_bitmap_index_create(idx, initial_idx);
  return 1;
  rollback:
  while ((--(&field[field_idx])) > initial_field)
  {
    newmap = 0;
    map = ~((size_t) 0);
    (atomic_load_explicit(field, memory_order_relaxed) == map) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(field) == map", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 272, __func__));
    atomic_store_explicit(field, newmap, memory_order_release);
  }


  if ((&field[field_idx]) == initial_field)
  {
    map = atomic_load_explicit(field, memory_order_relaxed);
    do
    {
      ((map & initial_mask) == initial_mask) ? ((void) 0) : (_mi_assert_fail("(map & initial_mask) == initial_mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 278, __func__));
      newmap = map & (~initial_mask);
    }
    while (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire));
  }
  _mi_stat_counter_increase(&_mi_stats_main.arena_rollback_count, 1);
  if (retries <= 2)
  {
    return mi_bitmap_try_find_claim_field_across(bitmap, bitmap_fields, idx, count, retries + 1, bitmap_idx);
  }
  else
  {
    return 0;
  }
}


----------------------------
bool _mi_bitmap_try_find_from_claim(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  size_t idx = start_field_idx;
  for (size_t visited = 0; visited < bitmap_fields; visited += 1, idx += 1)
  {
    if (idx >= bitmap_fields)
    {
      idx = 0;
    }
    if (_mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
None
----------------------------
***/


static bool mi_bitmap_is_claimedx_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *pany_ones, size_t *already_set)
{
  size_t idx = mi_bitmap_index_field(bitmap_idx);
  size_t pre_mask;
  size_t mid_mask;
  size_t post_mask;
  size_t mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &pre_mask, &mid_mask, &post_mask);
  bool all_ones = 1;
  bool any_ones = 0;
  size_t one_count = 0;
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t prev = atomic_load_explicit(field, memory_order_relaxed);
  field_idx += 1;
  if ((prev & pre_mask) != pre_mask)
  {
    all_ones = 0;
  }
  if ((prev & pre_mask) != 0)
  {
    any_ones = 1;
    one_count += mi_popcount(prev & pre_mask);
  }
  while ((mid_count--) > 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    field_idx += 1;
    if ((prev & mid_mask) != mid_mask)
    {
      all_ones = 0;
    }
    if ((prev & mid_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & mid_mask);
    }
  }

  if (post_mask != 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    if ((prev & post_mask) != post_mask)
    {
      all_ones = 0;
    }
    if ((prev & post_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & post_mask);
    }
  }
  if (pany_ones != 0)
  {
    *pany_ones = any_ones;
  }
  if (already_set != 0)
  {
    *already_set = one_count;
  }
  ((all_ones) ? (one_count == count) : (one_count < count)) ? ((void) 0) : (_mi_assert_fail("all_ones ? one_count == count : one_count < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 429, __func__));
  return all_ones;
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
static size_t mi_bitmap_mask_across(mi_bitmap_index_t bitmap_idx, size_t bitmap_fields, size_t count, size_t *pre_mask, size_t *mid_mask, size_t *post_mask)
{
  (void) bitmap_fields;
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  if (__builtin_expect(!(!((bitidx + count) <= (8 * (1 << 3)))), 1))
  {
    *pre_mask = mi_bitmap_mask_(count, bitidx);
    *mid_mask = 0;
    *post_mask = 0;
    (mi_bitmap_index_field(bitmap_idx) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 330, __func__));
    return 0;
  }
  else
  {
    const size_t pre_bits = (8 * (1 << 3)) - bitidx;
    (pre_bits < count) ? ((void) 0) : (_mi_assert_fail("pre_bits < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 335, __func__));
    *pre_mask = mi_bitmap_mask_(pre_bits, bitidx);
    count -= pre_bits;
    const size_t mid_count = count / (8 * (1 << 3));
    *mid_mask = ~((size_t) 0);
    count %= 8 * (1 << 3);
    *post_mask = (count == 0) ? (0) : (mi_bitmap_mask_(count, 0));
    (((mi_bitmap_index_field(bitmap_idx) + mid_count) + ((count == 0) ? (0) : (1))) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) + mid_count + (count==0 ? 0 : 1) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 342, __func__));
    return mid_count;
  }
}


----------------------------
typedef _Atomic size_t mi_bitmap_field_t
----------------------------
inline static size_t mi_popcount(size_t x)
{
  if (x <= 1)
  {
    return x;
  }
  if (x == SIZE_MAX)
  {
    return (1 << 3) * 8;
  }
  return __builtin_popcountll(x);
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_is_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, size_t *already_set)
{
  return mi_bitmap_is_claimedx_across(bitmap, bitmap_fields, count, bitmap_idx, 0, already_set);
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
static bool mi_bitmap_is_claimedx_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *pany_ones, size_t *already_set)
{
  size_t idx = mi_bitmap_index_field(bitmap_idx);
  size_t pre_mask;
  size_t mid_mask;
  size_t post_mask;
  size_t mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &pre_mask, &mid_mask, &post_mask);
  bool all_ones = 1;
  bool any_ones = 0;
  size_t one_count = 0;
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t prev = atomic_load_explicit(field, memory_order_relaxed);
  field_idx += 1;
  if ((prev & pre_mask) != pre_mask)
  {
    all_ones = 0;
  }
  if ((prev & pre_mask) != 0)
  {
    any_ones = 1;
    one_count += mi_popcount(prev & pre_mask);
  }
  while ((mid_count--) > 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    field_idx += 1;
    if ((prev & mid_mask) != mid_mask)
    {
      all_ones = 0;
    }
    if ((prev & mid_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & mid_mask);
    }
  }

  if (post_mask != 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    if ((prev & post_mask) != post_mask)
    {
      all_ones = 0;
    }
    if ((prev & post_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & post_mask);
    }
  }
  if (pany_ones != 0)
  {
    *pany_ones = any_ones;
  }
  if (already_set != 0)
  {
    *already_set = one_count;
  }
  ((all_ones) ? (one_count == count) : (one_count < count)) ? ((void) 0) : (_mi_assert_fail("all_ones ? one_count == count : one_count < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 429, __func__));
  return all_ones;
}


----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


bool _mi_bitmap_unclaim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  size_t idx = mi_bitmap_index_field(bitmap_idx);
  size_t pre_mask;
  size_t mid_mask;
  size_t post_mask;
  size_t mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &pre_mask, &mid_mask, &post_mask);
  bool all_one = 1;
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t prev = atomic_fetch_and_explicit(field, ~pre_mask, memory_order_acq_rel);
  field_idx += 1;
  if ((prev & pre_mask) != pre_mask)
  {
    all_one = 0;
  }
  while ((mid_count--) > 0)
  {
    prev = atomic_fetch_and_explicit(field, ~mid_mask, memory_order_acq_rel);
    field_idx += 1;
    if ((prev & mid_mask) != mid_mask)
    {
      all_one = 0;
    }
  }

  if (post_mask != 0)
  {
    prev = atomic_fetch_and_explicit(field, ~post_mask, memory_order_acq_rel);
    if ((prev & post_mask) != post_mask)
    {
      all_one = 0;
    }
  }
  return all_one;
}


/*** DEPENDENCIES:
typedef _Atomic size_t mi_bitmap_field_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
static size_t mi_bitmap_mask_across(mi_bitmap_index_t bitmap_idx, size_t bitmap_fields, size_t count, size_t *pre_mask, size_t *mid_mask, size_t *post_mask)
{
  (void) bitmap_fields;
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  if (__builtin_expect(!(!((bitidx + count) <= (8 * (1 << 3)))), 1))
  {
    *pre_mask = mi_bitmap_mask_(count, bitidx);
    *mid_mask = 0;
    *post_mask = 0;
    (mi_bitmap_index_field(bitmap_idx) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 330, __func__));
    return 0;
  }
  else
  {
    const size_t pre_bits = (8 * (1 << 3)) - bitidx;
    (pre_bits < count) ? ((void) 0) : (_mi_assert_fail("pre_bits < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 335, __func__));
    *pre_mask = mi_bitmap_mask_(pre_bits, bitidx);
    count -= pre_bits;
    const size_t mid_count = count / (8 * (1 << 3));
    *mid_mask = ~((size_t) 0);
    count %= 8 * (1 << 3);
    *post_mask = (count == 0) ? (0) : (mi_bitmap_mask_(count, 0));
    (((mi_bitmap_index_field(bitmap_idx) + mid_count) + ((count == 0) ? (0) : (1))) < bitmap_fields) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_index_field(bitmap_idx) + mid_count + (count==0 ? 0 : 1) < bitmap_fields", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 342, __func__));
    return mid_count;
  }
}


----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


bool _mi_bitmap_try_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 173, __func__));
  (void) bitmap_fields;
  size_t expected = atomic_load_explicit(&bitmap[idx], memory_order_relaxed);
  do
  {
    if ((expected & mask) != 0)
    {
      return 0;
    }
  }
  while (!atomic_compare_exchange_strong_explicit(&bitmap[idx], &expected, expected | mask, memory_order_acq_rel, memory_order_acquire));
  ((expected & mask) == 0) ? ((void) 0) : (_mi_assert_fail("(expected & mask) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 179, __func__));
  return 1;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx % (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_unclaim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 136, __func__));
  (void) bitmap_fields;
  const size_t prev = atomic_fetch_and_explicit(&bitmap[idx], ~mask, memory_order_acq_rel);
  return (prev & mask) == mask;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx % (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
None
----------------------------
***/


static bool mi_bitmap_is_claimedx(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *any_ones)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 161, __func__));
  (void) bitmap_fields;
  const size_t field = atomic_load_explicit(&bitmap[idx], memory_order_relaxed);
  if (any_ones != 0)
  {
    *any_ones = (field & mask) != 0;
  }
  return (field & mask) == mask;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx % (8 * (1 << 3));
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
inline static size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx)
{
  return bitmap_idx / (8 * (1 << 3));
}


----------------------------
inline static size_t mi_bitmap_mask_(size_t count, size_t bitidx)
{
  ((count + bitidx) <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count + bitidx <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 29, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 30, __func__));
  if (count >= (8 * (1 << 3)))
  {
    return ~((size_t) 0);
  }
  if (count == 0)
  {
    return 0;
  }
  return ((((size_t) 1) << count) - 1) << bitidx;
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_is_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  return mi_bitmap_is_claimedx(bitmap, bitmap_fields, count, bitmap_idx, 0);
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
static bool mi_bitmap_is_claimedx(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *any_ones)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 161, __func__));
  (void) bitmap_fields;
  const size_t field = atomic_load_explicit(&bitmap[idx], memory_order_relaxed);
  if (any_ones != 0)
  {
    *any_ones = (field & mask) != 0;
  }
  return (field & mask) == mask;
}


----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


bool _mi_bitmap_is_any_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  bool any_ones;
  mi_bitmap_is_claimedx(bitmap, bitmap_fields, count, bitmap_idx, &any_ones);
  return any_ones;
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
static bool mi_bitmap_is_claimedx(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *any_ones)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 161, __func__));
  (void) bitmap_fields;
  const size_t field = atomic_load_explicit(&bitmap[idx], memory_order_relaxed);
  if (any_ones != 0)
  {
    *any_ones = (field & mask) != 0;
  }
  return (field & mask) == mask;
}


----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


bool _mi_bitmap_is_any_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  bool any_ones;
  mi_bitmap_is_claimedx_across(bitmap, bitmap_fields, count, bitmap_idx, &any_ones, 0);
  return any_ones;
}


/*** DEPENDENCIES:
typedef size_t mi_bitmap_index_t
----------------------------
static bool mi_bitmap_is_claimedx_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool *pany_ones, size_t *already_set)
{
  size_t idx = mi_bitmap_index_field(bitmap_idx);
  size_t pre_mask;
  size_t mid_mask;
  size_t post_mask;
  size_t mid_count = mi_bitmap_mask_across(bitmap_idx, bitmap_fields, count, &pre_mask, &mid_mask, &post_mask);
  bool all_ones = 1;
  bool any_ones = 0;
  size_t one_count = 0;
  mi_bitmap_field_t *field = &bitmap[idx];
  unsigned int field_idx = 0;
  size_t prev = atomic_load_explicit(field, memory_order_relaxed);
  field_idx += 1;
  if ((prev & pre_mask) != pre_mask)
  {
    all_ones = 0;
  }
  if ((prev & pre_mask) != 0)
  {
    any_ones = 1;
    one_count += mi_popcount(prev & pre_mask);
  }
  while ((mid_count--) > 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    field_idx += 1;
    if ((prev & mid_mask) != mid_mask)
    {
      all_ones = 0;
    }
    if ((prev & mid_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & mid_mask);
    }
  }

  if (post_mask != 0)
  {
    prev = atomic_load_explicit(field, memory_order_relaxed);
    if ((prev & post_mask) != post_mask)
    {
      all_ones = 0;
    }
    if ((prev & post_mask) != 0)
    {
      any_ones = 1;
      one_count += mi_popcount(prev & post_mask);
    }
  }
  if (pany_ones != 0)
  {
    *pany_ones = any_ones;
  }
  if (already_set != 0)
  {
    *already_set = one_count;
  }
  ((all_ones) ? (one_count == count) : (one_count < count)) ? ((void) 0) : (_mi_assert_fail("all_ones ? one_count == count : one_count < count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 429, __func__));
  return all_ones;
}


----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


bool _mi_bitmap_try_find_from_claim_pred(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_pred_fun_t pred_fun, void *pred_arg, mi_bitmap_index_t *bitmap_idx)
{
  size_t idx = start_field_idx;
  for (size_t visited = 0; visited < bitmap_fields; visited += 1, idx += 1)
  {
    if (idx >= bitmap_fields)
    {
      idx = 0;
    }
    if (_mi_bitmap_try_find_claim_field(bitmap, idx, count, bitmap_idx))
    {
      if ((pred_fun == 0) || pred_fun(*bitmap_idx, pred_arg))
      {
        return 1;
      }
      _mi_bitmap_unclaim(bitmap, bitmap_fields, count, *bitmap_idx);
    }
  }

  return 0;
}


/*** DEPENDENCIES:
inline bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t *bitmap_idx)
{
  (bitmap_idx != 0) ? ((void) 0) : (_mi_assert_fail("bitmap_idx != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 45, __func__));
  (count <= (8 * (1 << 3))) ? ((void) 0) : (_mi_assert_fail("count <= MI_BITMAP_FIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 46, __func__));
  (count > 0) ? ((void) 0) : (_mi_assert_fail("count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 47, __func__));
  mi_bitmap_field_t *field = &bitmap[idx];
  size_t map = atomic_load_explicit(field, memory_order_relaxed);
  if (map == (~((size_t) 0)))
  {
    return 0;
  }
  const size_t mask = mi_bitmap_mask_(count, 0);
  const size_t bitidx_max = (8 * (1 << 3)) - count;
  size_t bitidx = mi_ctz(~map);
  size_t m = mask << bitidx;
  while (bitidx <= bitidx_max)
  {
    const size_t mapm = map & m;
    if (mapm == 0)
    {
      ((m >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(m >> bitidx) == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 67, __func__));
      const size_t newmap = map | m;
      (((newmap ^ map) >> bitidx) == mask) ? ((void) 0) : (_mi_assert_fail("(newmap^map) >> bitidx == mask", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 69, __func__));
      if (!atomic_compare_exchange_strong_explicit(field, &map, newmap, memory_order_acq_rel, memory_order_acquire))
      {
        continue;
      }
      else
      {
        *bitmap_idx = mi_bitmap_index_create(idx, bitidx);
        return 1;
      }
    }
    else
    {
      (mapm != 0) ? ((void) 0) : (_mi_assert_fail("mapm != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 83, __func__));
      const size_t shift = (count == 1) ? (1) : ((((1 << 3) * 8) - mi_clz(mapm)) - bitidx);
      ((shift > 0) && (shift <= count)) ? ((void) 0) : (_mi_assert_fail("shift > 0 && shift <= count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 85, __func__));
      bitidx += shift;
      m <<= shift;
    }
  }

  return 0;
}


----------------------------
bool _mi_bitmap_unclaim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx)
{
  const size_t idx = mi_bitmap_index_field(bitmap_idx);
  const size_t bitidx = mi_bitmap_index_bit_in_field(bitmap_idx);
  const size_t mask = mi_bitmap_mask_(count, bitidx);
  (bitmap_fields > idx) ? ((void) 0) : (_mi_assert_fail("bitmap_fields > idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.c", 136, __func__));
  (void) bitmap_fields;
  const size_t prev = atomic_fetch_and_explicit(&bitmap[idx], ~mask, memory_order_acq_rel);
  return (prev & mask) == mask;
}


----------------------------
typedef size_t mi_bitmap_index_t
----------------------------
typedef bool (*mi_bitmap_pred_fun_t)(mi_bitmap_index_t bitmap_idx, void *pred_arg)
----------------------------
typedef mi_bitmap_field_t *mi_bitmap_t
----------------------------
***/


