inline static mi_bfield_t mi_bfield_zero(void)
{
  return 0;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


inline static mi_bfield_t mi_bfield_one(void)
{
  return 1;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


inline static mi_bfield_t mi_bfield_all_set(void)
{
  return ~((mi_bfield_t) 0);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bsf(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = mi_ctz(x), 1)) : (0);
}


----------------------------
***/


inline static mi_bfield_t mi_bfield_clear_least_bit(mi_bfield_t x)
{
  return x & (x - 1);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


inline static bool mi_bfield_foreach_bit(mi_bfield_t *x, size_t *idx)
{
  const bool found = mi_bfield_find_least_bit(*x, idx);
  *x = mi_bfield_clear_least_bit(*x);
  return found;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_clear_least_bit(mi_bfield_t x)
{
  return x & (x - 1);
}


----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static mi_bfield_t mi_bfield_all_set(void)
{
  return ~((mi_bfield_t) 0);
}


----------------------------
inline static mi_bfield_t mi_bfield_one(void)
{
  return 1;
}


----------------------------
None
----------------------------
***/


bool _mi_bitmap_forall_setc_ranges(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg)
{
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = 0; i < chunkmap_max; i += 1)
  {
    mi_bfield_t cmap_entry = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
    size_t cmap_idx;
    while (mi_bfield_foreach_bit(&cmap_entry, &cmap_idx))
    {
      const size_t chunk_idx = (i * (1 << (3 + 3))) + cmap_idx;
      mi_bchunk_t * const chunk = &bitmap->chunks[chunk_idx];
      for (size_t j = 0; j < ((1 << (6 + 3)) / (1 << (3 + 3))); j += 1)
      {
        const size_t base_idx = (chunk_idx * (1 << (6 + 3))) + (j * (1 << (3 + 3)));
        mi_bfield_t b = atomic_exchange_explicit(&chunk->bfields[j], 0, memory_order_acq_rel);
        const size_t bpopcount = mi_popcount(b);
        size_t rngcount = 0;
        size_t bidx;
        while (mi_bfield_find_least_bit(b, &bidx))
        {
          const size_t rng = mi_ctz(~(b >> bidx));
          rngcount += rng;
          ((rng >= 1) && (rng <= (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("rng>=1 && rng<=MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1433, __func__));
          const size_t idx = base_idx + bidx;
          (((idx % (1 << (3 + 3))) + rng) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("(idx % MI_BFIELD_BITS) + rng <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1435, __func__));
          ((idx / (1 << (6 + 3))) < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("(idx / MI_BCHUNK_BITS) < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1436, __func__));
          if (!visit(idx, rng, arena, arg))
          {
            return 0;
          }
          b = b & (~mi_bfield_mask(rng, bidx));
        }

        (rngcount == bpopcount) ? ((void) 0) : (_mi_assert_fail("rngcount == bpopcount", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1441, __func__));
      }

    }

  }

  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static size_t mi_popcount(size_t x)
{
  return __builtin_popcountll(x);
}


----------------------------
inline static bool mi_bfield_foreach_bit(mi_bfield_t *x, size_t *idx)
{
  const bool found = mi_bfield_find_least_bit(*x, idx);
  *x = mi_bfield_clear_least_bit(*x);
  return found;
}


----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef bool mi_forall_set_fun_t(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg2)
----------------------------
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}


----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_try_clear_mask_of(_Atomic mi_bfield_t *b, mi_bfield_t mask, mi_bfield_t expect, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 169, __func__));
  do
  {
    if ((expect & mask) != mask)
    {
      if (all_clear != 0)
      {
        *all_clear = expect == 0;
      }
      return 0;
    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &expect, expect & (~mask), memory_order_acq_rel, memory_order_acquire));
  if (all_clear != 0)
  {
    *all_clear = (expect & (~mask)) == 0;
  }
  return 1;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_try_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 182, __func__));
  const mi_bfield_t expect = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_atomic_try_clear_mask_of(b, mask, expect, all_clear);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bfield_atomic_try_clear_mask_of(_Atomic mi_bfield_t *b, mi_bfield_t mask, mi_bfield_t expect, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 169, __func__));
  do
  {
    if ((expect & mask) != mask)
    {
      if (all_clear != 0)
      {
        *all_clear = expect == 0;
      }
      return 0;
    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &expect, expect & (~mask), memory_order_acq_rel, memory_order_acquire));
  if (all_clear != 0)
  {
    *all_clear = (expect & (~mask)) == 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static size_t mi_popcount(size_t x)
{
  return __builtin_popcountll(x);
}


----------------------------
***/


inline static bool mi_bfield_atomic_set_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, size_t *already_set)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 133, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old | mask, memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old & mask);
  }
  return (old & mask) == 0;
}


/*** DEPENDENCIES:
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_try_clearNX(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *pmaybe_all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 447, __func__));
  (n <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 448, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (__builtin_expect(!(!((idx + n) <= (1 << (3 + 3)))), 1))
  {
    return mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(n, idx), pmaybe_all_clear);
  }
  else
  {
    const size_t m = (1 << (3 + 3)) - idx;
    (m < n) ? ((void) 0) : (_mi_assert_fail("m < n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 458, __func__));
    (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)) ? ((void) 0) : (_mi_assert_fail("i < MI_BCHUNK_FIELDS - 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 459, __func__));
    bool field1_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), &field1_is_clear))
    {
      return 0;
    }
    ((n - m) > 0) ? ((void) 0) : (_mi_assert_fail("n - m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 463, __func__));
    ((n - m) < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n - m < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 464, __func__));
    bool field2_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i + 1], mi_bfield_mask(n - m, 0), &field2_is_clear))
    {
      mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), 0);
      return 0;
    }
    if (pmaybe_all_clear != 0)
    {
      *pmaybe_all_clear = field1_is_clear && field2_is_clear;
    }
    return 1;
  }
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_set_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, size_t *already_set)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 133, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old | mask, memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old & mask);
  }
  return (old & mask) == 0;
}


----------------------------
inline static bool mi_bfield_atomic_try_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 182, __func__));
  const mi_bfield_t expect = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_atomic_try_clear_mask_of(b, mask, expect, all_clear);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_try_clearX(_Atomic mi_bfield_t *b, bool *all_clear)
{
  mi_bfield_t old = mi_bfield_all_set();
  if (atomic_compare_exchange_strong_explicit(b, &old, mi_bfield_zero(), memory_order_acq_rel, memory_order_acquire))
  {
    if (all_clear != 0)
    {
      *all_clear = 1;
    }
    return 1;
  }
  else
    return 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_all_set(void)
{
  return ~((mi_bfield_t) 0);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static mi_bfield_t mi_bfield_zero(void)
{
  return 0;
}


----------------------------
***/


inline static bool mi_bfield_atomic_setX(_Atomic mi_bfield_t *b, size_t *already_set)
{
  const mi_bfield_t old = atomic_exchange_explicit(b, mi_bfield_all_set(), memory_order_release);
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old);
  }
  return old == 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_all_set(void)
{
  return ~((mi_bfield_t) 0);
}


----------------------------
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


static bool mi_bchunk_try_clearN_(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *pmaybe_all_clear)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 490, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 491, __func__));
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = 1;
  }
  if (n == 0)
  {
    return 1;
  }
  const size_t start_idx = cidx % (1 << (3 + 3));
  const size_t start_field = cidx / (1 << (3 + 3));
  size_t field = start_field;
  size_t m = (1 << (3 + 3)) - start_idx;
  if (m > n)
  {
    m = n;
  }
  ((start_idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("start_idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 501, __func__));
  (start_field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("start_field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 502, __func__));
  const mi_bfield_t mask_start = mi_bfield_mask(m, start_idx);
  bool maybe_all_clear;
  if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[field], mask_start, &maybe_all_clear))
  {
    return 0;
  }
  (m <= n) ? ((void) 0) : (_mi_assert_fail("m <= n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 508, __func__));
  n -= m;
  while (n >= (1 << (3 + 3)))
  {
    field += 1;
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 515, __func__));
    bool field_is_clear;
    if (!mi_bfield_atomic_try_clearX(&chunk->bfields[field], &field_is_clear))
    {
      goto restore;
    }
    maybe_all_clear = maybe_all_clear && field_is_clear;
    n -= 1 << (3 + 3);
  }

  if (n > 0)
  {
    (n < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 524, __func__));
    field += 1;
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 526, __func__));
    const mi_bfield_t mask_end = mi_bfield_mask(n, 0);
    bool field_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[field], mask_end, &field_is_clear))
    {
      goto restore;
    }
    maybe_all_clear = maybe_all_clear && field_is_clear;
  }
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = maybe_all_clear;
  }
  return 1;
  restore:
  (field > start_field) ? ((void) 0) : (_mi_assert_fail("field > start_field", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 538, __func__));

  while (field > start_field)
  {
    field -= 1;
    if (field == start_field)
    {
      mi_bfield_atomic_set_mask(&chunk->bfields[field], mask_start, 0);
    }
    else
    {
      mi_bfield_atomic_setX(&chunk->bfields[field], 0);
    }
  }

  return 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_set_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, size_t *already_set)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 133, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old | mask, memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old & mask);
  }
  return (old & mask) == 0;
}


----------------------------
inline static bool mi_bfield_atomic_try_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 182, __func__));
  const mi_bfield_t expect = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_atomic_try_clear_mask_of(b, mask, expect, all_clear);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_setX(_Atomic mi_bfield_t *b, size_t *already_set)
{
  const mi_bfield_t old = atomic_exchange_explicit(b, mi_bfield_all_set(), memory_order_release);
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old);
  }
  return old == 0;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bfield_atomic_try_clearX(_Atomic mi_bfield_t *b, bool *all_clear)
{
  mi_bfield_t old = mi_bfield_all_set();
  if (atomic_compare_exchange_strong_explicit(b, &old, mi_bfield_zero(), memory_order_acq_rel, memory_order_acquire))
  {
    if (all_clear != 0)
    {
      *all_clear = 1;
    }
    return 1;
  }
  else
    return 0;
}


----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_try_clearN(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *maybe_all_clear)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 553, __func__));
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_try_clearNX(chunk, cidx, n, maybe_all_clear);
  }
  return mi_bchunk_try_clearN_(chunk, cidx, n, maybe_all_clear);
}


/*** DEPENDENCIES:
static bool mi_bchunk_try_clearN_(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *pmaybe_all_clear)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 490, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 491, __func__));
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = 1;
  }
  if (n == 0)
  {
    return 1;
  }
  const size_t start_idx = cidx % (1 << (3 + 3));
  const size_t start_field = cidx / (1 << (3 + 3));
  size_t field = start_field;
  size_t m = (1 << (3 + 3)) - start_idx;
  if (m > n)
  {
    m = n;
  }
  ((start_idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("start_idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 501, __func__));
  (start_field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("start_field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 502, __func__));
  const mi_bfield_t mask_start = mi_bfield_mask(m, start_idx);
  bool maybe_all_clear;
  if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[field], mask_start, &maybe_all_clear))
  {
    return 0;
  }
  (m <= n) ? ((void) 0) : (_mi_assert_fail("m <= n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 508, __func__));
  n -= m;
  while (n >= (1 << (3 + 3)))
  {
    field += 1;
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 515, __func__));
    bool field_is_clear;
    if (!mi_bfield_atomic_try_clearX(&chunk->bfields[field], &field_is_clear))
    {
      goto restore;
    }
    maybe_all_clear = maybe_all_clear && field_is_clear;
    n -= 1 << (3 + 3);
  }

  if (n > 0)
  {
    (n < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 524, __func__));
    field += 1;
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 526, __func__));
    const mi_bfield_t mask_end = mi_bfield_mask(n, 0);
    bool field_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[field], mask_end, &field_is_clear))
    {
      goto restore;
    }
    maybe_all_clear = maybe_all_clear && field_is_clear;
  }
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = maybe_all_clear;
  }
  return 1;
  restore:
  (field > start_field) ? ((void) 0) : (_mi_assert_fail("field > start_field", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 538, __func__));

  while (field > start_field)
  {
    field -= 1;
    if (field == start_field)
    {
      mi_bfield_atomic_set_mask(&chunk->bfields[field], mask_start, 0);
    }
    else
    {
      mi_bfield_atomic_setX(&chunk->bfields[field], 0);
    }
  }

  return 0;
}


----------------------------
inline static bool mi_bchunk_try_clearNX(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *pmaybe_all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 447, __func__));
  (n <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 448, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (__builtin_expect(!(!((idx + n) <= (1 << (3 + 3)))), 1))
  {
    return mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(n, idx), pmaybe_all_clear);
  }
  else
  {
    const size_t m = (1 << (3 + 3)) - idx;
    (m < n) ? ((void) 0) : (_mi_assert_fail("m < n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 458, __func__));
    (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)) ? ((void) 0) : (_mi_assert_fail("i < MI_BCHUNK_FIELDS - 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 459, __func__));
    bool field1_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), &field1_is_clear))
    {
      return 0;
    }
    ((n - m) > 0) ? ((void) 0) : (_mi_assert_fail("n - m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 463, __func__));
    ((n - m) < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n - m < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 464, __func__));
    bool field2_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i + 1], mi_bfield_mask(n - m, 0), &field2_is_clear))
    {
      mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), 0);
      return 0;
    }
    if (pmaybe_all_clear != 0)
    {
      *pmaybe_all_clear = field1_is_clear && field2_is_clear;
    }
    return 1;
  }
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_all_are_clear_relaxed(mi_bchunk_t *chunk)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed) != 0)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
***/


inline static bool mi_bfield_atomic_clear(_Atomic mi_bfield_t *b, size_t idx, bool *all_clear)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 100, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  mi_bfield_t old = atomic_fetch_and_explicit(b, ~mask, memory_order_acq_rel);
  if (all_clear != 0)
  {
    *all_clear = (old & (~mask)) == 0;
  }
  return (old & mask) == mask;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_clear(mi_bchunk_t *chunk, size_t cidx, bool *all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 359, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  return mi_bfield_atomic_clear(&chunk->bfields[i], idx, all_clear);
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_clear(_Atomic mi_bfield_t *b, size_t idx, bool *all_clear)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 100, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  mi_bfield_t old = atomic_fetch_and_explicit(b, ~mask, memory_order_acq_rel);
  if (all_clear != 0)
  {
    *all_clear = (old & (~mask)) == 0;
  }
  return (old & mask) == mask;
}


----------------------------
None
----------------------------
***/


static void mi_bbitmap_chunkmap_set_max(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  size_t oldmax = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  if (__builtin_expect(!(!(chunk_idx > oldmax)), 0))
  {
    atomic_compare_exchange_strong_explicit(&bbitmap->chunk_max_accessed, &oldmax, chunk_idx, memory_order_relaxed, memory_order_relaxed);
  }
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
***/


inline static bool mi_bfield_atomic_set(_Atomic mi_bfield_t *b, size_t idx)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 91, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  const mi_bfield_t old = atomic_fetch_or_explicit(b, mask, memory_order_acq_rel);
  return (old & mask) == 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_set(_Atomic mi_bfield_t *b, size_t idx)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 91, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  const mi_bfield_t old = atomic_fetch_or_explicit(b, mask, memory_order_acq_rel);
  return (old & mask) == 0;
}


----------------------------
None
----------------------------
***/


static bool mi_bbitmap_chunkmap_try_clear(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1539, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bbitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bbitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  mi_bbitmap_chunkmap_set_max(bbitmap, chunk_idx);
  return 1;
}


/*** DEPENDENCIES:
static void mi_bbitmap_chunkmap_set_max(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  size_t oldmax = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  if (__builtin_expect(!(!(chunk_idx > oldmax)), 0))
  {
    atomic_compare_exchange_strong_explicit(&bbitmap->chunk_max_accessed, &oldmax, chunk_idx, memory_order_relaxed, memory_order_relaxed);
  }
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bchunk_all_are_clear_relaxed(mi_bchunk_t *chunk)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed) != 0)
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
inline static bool mi_bchunk_clear(mi_bchunk_t *chunk, size_t cidx, bool *all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 359, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  return mi_bfield_atomic_clear(&chunk->bfields[i], idx, all_clear);
}


----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


bool mi_bbitmap_try_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1581, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1582, __func__));
  ((idx + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1583, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1587, __func__));
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1588, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    return 0;
  }
  bool maybe_all_clear;
  const bool cleared = mi_bchunk_try_clearN(&bbitmap->chunks[chunk_idx], cidx, n, &maybe_all_clear);
  if (cleared && maybe_all_clear)
  {
    mi_bbitmap_chunkmap_try_clear(bbitmap, chunk_idx);
  }
  return cleared;
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
static bool mi_bbitmap_chunkmap_try_clear(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1539, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bbitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bbitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  mi_bbitmap_chunkmap_set_max(bbitmap, chunk_idx);
  return 1;
}


----------------------------
inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}


----------------------------
inline static bool mi_bchunk_try_clearN(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *maybe_all_clear)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 553, __func__));
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_try_clearNX(chunk, cidx, n, maybe_all_clear);
  }
  return mi_bchunk_try_clearN_(chunk, cidx, n, maybe_all_clear);
}


----------------------------
None
----------------------------
***/


static void mi_bitmap_chunkmap_set(mi_bitmap_t *bitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1016, __func__));
  mi_bchunk_set(&bitmap->chunkmap, chunk_idx, 0);
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_setNX(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 287, __func__));
  ((n > 0) && (n <= (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("n > 0 && n <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 288, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (__builtin_expect(!(!((idx + n) <= (1 << (3 + 3)))), 1))
  {
    return mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(n, idx), already_set);
  }
  else
  {
    const size_t m = (1 << (3 + 3)) - idx;
    (m < n) ? ((void) 0) : (_mi_assert_fail("m < n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 298, __func__));
    (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)) ? ((void) 0) : (_mi_assert_fail("i < MI_BCHUNK_FIELDS - 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 299, __func__));
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 300, __func__));
    size_t already_set1;
    const bool all_set1 = mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), &already_set1);
    ((n - m) > 0) ? ((void) 0) : (_mi_assert_fail("n - m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 303, __func__));
    ((n - m) < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n - m < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 304, __func__));
    size_t already_set2;
    const bool all_set2 = mi_bfield_atomic_set_mask(&chunk->bfields[i + 1], mi_bfield_mask(n - m, 0), &already_set2);
    if (already_set != 0)
    {
      *already_set = already_set1 + already_set2;
    }
    return all_set1 && all_set2;
  }
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_set_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, size_t *already_set)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 133, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old | mask, memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old & mask);
  }
  return (old & mask) == 0;
}


----------------------------
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 143, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old & (~mask), memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (all_clear != 0)
  {
    *all_clear = (old & (~mask)) == 0;
  }
  return (old & mask) == mask;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


static bool mi_bchunk_xsetN_(mi_xset_t set, mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *palready_set, bool *pmaybe_all_clear)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 315, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 316, __func__));
  bool all_transition = 1;
  bool maybe_all_clear = 1;
  size_t total_already_set = 0;
  size_t idx = cidx % (1 << (3 + 3));
  size_t field = cidx / (1 << (3 + 3));
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 325, __func__));
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 326, __func__));
    const mi_bfield_t mask = mi_bfield_mask(m, idx);
    size_t already_set = 0;
    bool all_clear = 0;
    const bool transition = (set) ? (mi_bfield_atomic_set_mask(&chunk->bfields[field], mask, &already_set)) : (mi_bfield_atomic_clear_mask(&chunk->bfields[field], mask, &all_clear));
    ((transition && (already_set == 0)) || ((!transition) && (already_set > 0))) ? ((void) 0) : (_mi_assert_fail("(transition && already_set == 0) || (!transition && already_set > 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 332, __func__));
    all_transition = all_transition && transition;
    total_already_set += already_set;
    maybe_all_clear = maybe_all_clear && all_clear;
    field += 1;
    idx = 0;
    (m <= n) ? ((void) 0) : (_mi_assert_fail("m <= n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 339, __func__));
    n -= m;
  }

  if (palready_set != 0)
  {
    *palready_set = total_already_set;
  }
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = maybe_all_clear;
  }
  return all_transition;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_set_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, size_t *already_set)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 133, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old | mask, memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (already_set != 0)
  {
    *already_set = mi_bfield_popcount(old & mask);
  }
  return (old & mask) == 0;
}


----------------------------
typedef bool mi_xset_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 143, __func__));
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  while (!atomic_compare_exchange_weak_explicit(b, &old, old & (~mask), memory_order_acq_rel, memory_order_acquire))
  {
  }

  ;
  if (all_clear != 0)
  {
    *all_clear = (old & (~mask)) == 0;
  }
  return (old & mask) == mask;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_setN(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 348, __func__));
  if (n == 1)
  {
    return mi_bchunk_set(chunk, cidx, already_set);
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_setNX(chunk, cidx, n, already_set);
  }
  return mi_bchunk_xsetN_(1, chunk, cidx, n, already_set, 0);
}


/*** DEPENDENCIES:
static bool mi_bchunk_xsetN_(mi_xset_t set, mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *palready_set, bool *pmaybe_all_clear)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 315, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 316, __func__));
  bool all_transition = 1;
  bool maybe_all_clear = 1;
  size_t total_already_set = 0;
  size_t idx = cidx % (1 << (3 + 3));
  size_t field = cidx / (1 << (3 + 3));
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 325, __func__));
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 326, __func__));
    const mi_bfield_t mask = mi_bfield_mask(m, idx);
    size_t already_set = 0;
    bool all_clear = 0;
    const bool transition = (set) ? (mi_bfield_atomic_set_mask(&chunk->bfields[field], mask, &already_set)) : (mi_bfield_atomic_clear_mask(&chunk->bfields[field], mask, &all_clear));
    ((transition && (already_set == 0)) || ((!transition) && (already_set > 0))) ? ((void) 0) : (_mi_assert_fail("(transition && already_set == 0) || (!transition && already_set > 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 332, __func__));
    all_transition = all_transition && transition;
    total_already_set += already_set;
    maybe_all_clear = maybe_all_clear && all_clear;
    field += 1;
    idx = 0;
    (m <= n) ? ((void) 0) : (_mi_assert_fail("m <= n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 339, __func__));
    n -= m;
  }

  if (palready_set != 0)
  {
    *palready_set = total_already_set;
  }
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = maybe_all_clear;
  }
  return all_transition;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bchunk_setNX(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 287, __func__));
  ((n > 0) && (n <= (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("n > 0 && n <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 288, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (__builtin_expect(!(!((idx + n) <= (1 << (3 + 3)))), 1))
  {
    return mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(n, idx), already_set);
  }
  else
  {
    const size_t m = (1 << (3 + 3)) - idx;
    (m < n) ? ((void) 0) : (_mi_assert_fail("m < n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 298, __func__));
    (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)) ? ((void) 0) : (_mi_assert_fail("i < MI_BCHUNK_FIELDS - 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 299, __func__));
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 300, __func__));
    size_t already_set1;
    const bool all_set1 = mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), &already_set1);
    ((n - m) > 0) ? ((void) 0) : (_mi_assert_fail("n - m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 303, __func__));
    ((n - m) < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n - m < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 304, __func__));
    size_t already_set2;
    const bool all_set2 = mi_bfield_atomic_set_mask(&chunk->bfields[i + 1], mi_bfield_mask(n - m, 0), &already_set2);
    if (already_set != 0)
    {
      *already_set = already_set1 + already_set2;
    }
    return all_set1 && all_set2;
  }
}


----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
None
----------------------------
***/


bool mi_bitmap_setN(mi_bitmap_t *bitmap, size_t idx, size_t n, size_t *already_set)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1118, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1119, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1123, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1124, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  const bool were_allclear = mi_bchunk_setN(&bitmap->chunks[chunk_idx], cidx, n, already_set);
  mi_bitmap_chunkmap_set(bitmap, chunk_idx);
  return were_allclear;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static bool mi_bchunk_setN(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 348, __func__));
  if (n == 1)
  {
    return mi_bchunk_set(chunk, cidx, already_set);
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_setNX(chunk, cidx, n, already_set);
  }
  return mi_bchunk_xsetN_(1, chunk, cidx, n, already_set, 0);
}


----------------------------
static void mi_bitmap_chunkmap_set(mi_bitmap_t *bitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1016, __func__));
  mi_bchunk_set(&bitmap->chunkmap, chunk_idx, 0);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_clearN(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *maybe_all_clear)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 366, __func__));
  if (n == 1)
  {
    return mi_bchunk_clear(chunk, cidx, maybe_all_clear);
  }
  return mi_bchunk_xsetN_(0, chunk, cidx, n, 0, maybe_all_clear);
}


/*** DEPENDENCIES:
static bool mi_bchunk_xsetN_(mi_xset_t set, mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *palready_set, bool *pmaybe_all_clear)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 315, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 316, __func__));
  bool all_transition = 1;
  bool maybe_all_clear = 1;
  size_t total_already_set = 0;
  size_t idx = cidx % (1 << (3 + 3));
  size_t field = cidx / (1 << (3 + 3));
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 325, __func__));
    (field < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 326, __func__));
    const mi_bfield_t mask = mi_bfield_mask(m, idx);
    size_t already_set = 0;
    bool all_clear = 0;
    const bool transition = (set) ? (mi_bfield_atomic_set_mask(&chunk->bfields[field], mask, &already_set)) : (mi_bfield_atomic_clear_mask(&chunk->bfields[field], mask, &all_clear));
    ((transition && (already_set == 0)) || ((!transition) && (already_set > 0))) ? ((void) 0) : (_mi_assert_fail("(transition && already_set == 0) || (!transition && already_set > 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 332, __func__));
    all_transition = all_transition && transition;
    total_already_set += already_set;
    maybe_all_clear = maybe_all_clear && all_clear;
    field += 1;
    idx = 0;
    (m <= n) ? ((void) 0) : (_mi_assert_fail("m <= n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 339, __func__));
    n -= m;
  }

  if (palready_set != 0)
  {
    *palready_set = total_already_set;
  }
  if (pmaybe_all_clear != 0)
  {
    *pmaybe_all_clear = maybe_all_clear;
  }
  return all_transition;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bchunk_clear(mi_bchunk_t *chunk, size_t cidx, bool *all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 359, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  return mi_bfield_atomic_clear(&chunk->bfields[i], idx, all_clear);
}


----------------------------
None
----------------------------
***/


static bool mi_bitmap_chunkmap_try_clear(mi_bitmap_t *bitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1021, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
inline static bool mi_bchunk_all_are_clear_relaxed(mi_bchunk_t *chunk)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed) != 0)
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
inline static bool mi_bchunk_clear(mi_bchunk_t *chunk, size_t cidx, bool *all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 359, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  return mi_bfield_atomic_clear(&chunk->bfields[i], idx, all_clear);
}


----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


bool mi_bitmap_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1135, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1136, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1140, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1141, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  bool maybe_all_clear;
  const bool were_allset = mi_bchunk_clearN(&bitmap->chunks[chunk_idx], cidx, n, &maybe_all_clear);
  if (maybe_all_clear)
  {
    mi_bitmap_chunkmap_try_clear(bitmap, chunk_idx);
  }
  return were_allset;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
static bool mi_bitmap_chunkmap_try_clear(mi_bitmap_t *bitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1021, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  return 1;
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bchunk_clearN(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *maybe_all_clear)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 366, __func__));
  if (n == 1)
  {
    return mi_bchunk_clear(chunk, cidx, maybe_all_clear);
  }
  return mi_bchunk_xsetN_(0, chunk, cidx, n, 0, maybe_all_clear);
}


----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_is_set(const mi_bfield_t *b, const size_t idx)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mi_bfield_mask(1, idx)) != 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


inline static bool mi_bfield_atomic_is_clear(const mi_bfield_t *b, const size_t idx)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mi_bfield_mask(1, idx)) == 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


inline static bool mi_bfield_atomic_is_xset(mi_xset_t set, const mi_bfield_t *b, const size_t idx)
{
  if (set)
  {
    return mi_bfield_atomic_is_set(b, idx);
  }
  else
    return mi_bfield_atomic_is_clear(b, idx);
}


/*** DEPENDENCIES:
inline static bool mi_bfield_atomic_is_clear(const mi_bfield_t *b, const size_t idx)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mi_bfield_mask(1, idx)) == 0;
}


----------------------------
inline static bool mi_bfield_atomic_is_set(const mi_bfield_t *b, const size_t idx)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mi_bfield_mask(1, idx)) != 0;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
typedef bool mi_xset_t
----------------------------
***/


inline static bool mi_bfield_atomic_is_set_mask(const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 240, __func__));
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mask) == mask;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_is_clear_mask(const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 247, __func__));
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mask) == 0;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_is_xset_mask(mi_xset_t set, const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 254, __func__));
  if (set)
  {
    return mi_bfield_atomic_is_set_mask(b, mask);
  }
  else
    return mi_bfield_atomic_is_clear_mask(b, mask);
}


/*** DEPENDENCIES:
inline static bool mi_bfield_atomic_is_clear_mask(const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 247, __func__));
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mask) == 0;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
typedef bool mi_xset_t
----------------------------
inline static bool mi_bfield_atomic_is_set_mask(const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 240, __func__));
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mask) == mask;
}


----------------------------
None
----------------------------
***/


static bool mi_bchunk_is_xsetN_(mi_xset_t set, const mi_bchunk_t *chunk, size_t field_idx, size_t idx, size_t n)
{
  ((((field_idx * (1 << (3 + 3))) + idx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("(field_idx*MI_BFIELD_BITS) + idx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 412, __func__));
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 416, __func__));
    (field_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 417, __func__));
    const size_t mask = mi_bfield_mask(m, idx);
    if (!mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[field_idx], mask))
    {
      return 0;
    }
    field_idx += 1;
    idx = 0;
    n -= m;
  }

  return 1;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_is_xset_mask(mi_xset_t set, const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 254, __func__));
  if (set)
  {
    return mi_bfield_atomic_is_set_mask(b, mask);
  }
  else
    return mi_bfield_atomic_is_clear_mask(b, mask);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef bool mi_xset_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_is_xsetN(mi_xset_t set, const mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 432, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 433, __func__));
  if (n == 0)
  {
    return 1;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return mi_bfield_atomic_is_xset(set, &chunk->bfields[i], idx);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_is_xsetN_(set, chunk, i, idx, n);
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_is_xset_mask(mi_xset_t set, const mi_bfield_t *b, mi_bfield_t mask)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 254, __func__));
  if (set)
  {
    return mi_bfield_atomic_is_set_mask(b, mask);
  }
  else
    return mi_bfield_atomic_is_clear_mask(b, mask);
}


----------------------------
typedef bool mi_xset_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
static bool mi_bchunk_is_xsetN_(mi_xset_t set, const mi_bchunk_t *chunk, size_t field_idx, size_t idx, size_t n)
{
  ((((field_idx * (1 << (3 + 3))) + idx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("(field_idx*MI_BFIELD_BITS) + idx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 412, __func__));
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 416, __func__));
    (field_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 417, __func__));
    const size_t mask = mi_bfield_mask(m, idx);
    if (!mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[field_idx], mask))
    {
      return 0;
    }
    field_idx += 1;
    idx = 0;
    n -= m;
  }

  return 1;
}


----------------------------
inline static bool mi_bfield_atomic_is_xset(mi_xset_t set, const mi_bfield_t *b, const size_t idx)
{
  if (set)
  {
    return mi_bfield_atomic_is_set(b, idx);
  }
  else
    return mi_bfield_atomic_is_clear(b, idx);
}


----------------------------
None
----------------------------
***/


bool mi_bbitmap_is_xsetN(mi_xset_t set, mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1602, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1603, __func__));
  ((idx + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1604, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1608, __func__));
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1609, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  return mi_bchunk_is_xsetN(set, &bbitmap->chunks[chunk_idx], cidx, n);
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bchunk_is_xsetN(mi_xset_t set, const mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 432, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 433, __func__));
  if (n == 0)
  {
    return 1;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return mi_bfield_atomic_is_xset(set, &chunk->bfields[i], idx);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_is_xsetN_(set, chunk, i, idx, n);
}


----------------------------
typedef bool mi_xset_t
----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}


----------------------------
None
----------------------------
***/


static void mi_bbitmap_set_chunk_bin(mi_bbitmap_t *bbitmap, size_t chunk_idx, mi_chunkbin_t bin)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1495, __func__));
  for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
  {
    if (ibin == bin)
    {
      const bool was_clear = mi_bchunk_set(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_clear)
      {
        __mi_stat_increase_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
    else
    {
      const bool was_set = mi_bchunk_clear(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_set)
      {
        __mi_stat_decrease_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
  }

}


/*** DEPENDENCIES:
inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, -((int64_t) amount));
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
mi_subproc_t *_mi_subproc(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return _mi_subproc_main();
  }
  else
  {
    return heap->tld->subproc;
  }
}


----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
inline static bool mi_bchunk_clear(mi_bchunk_t *chunk, size_t cidx, bool *all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 359, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  return mi_bfield_atomic_clear(&chunk->bfields[i], idx, all_clear);
}


----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_all_are_set_relaxed(mi_bchunk_t *chunk)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if ((~atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed)) != 0)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
***/


static void mi_bbitmap_chunkmap_set(mi_bbitmap_t *bbitmap, size_t chunk_idx, bool check_all_set)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1527, __func__));
  if (check_all_set)
  {
    if (mi_bchunk_all_are_set_relaxed(&bbitmap->chunks[chunk_idx]))
    {
      mi_bbitmap_set_chunk_bin(bbitmap, chunk_idx, MI_CBIN_NONE);
    }
  }
  mi_bchunk_set(&bbitmap->chunkmap, chunk_idx, 0);
  mi_bbitmap_chunkmap_set_max(bbitmap, chunk_idx);
}


/*** DEPENDENCIES:
inline static bool mi_bchunk_all_are_set_relaxed(mi_bchunk_t *chunk)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if ((~atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed)) != 0)
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
static void mi_bbitmap_chunkmap_set_max(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  size_t oldmax = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  if (__builtin_expect(!(!(chunk_idx > oldmax)), 0))
  {
    atomic_compare_exchange_strong_explicit(&bbitmap->chunk_max_accessed, &oldmax, chunk_idx, memory_order_relaxed, memory_order_relaxed);
  }
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
static void mi_bbitmap_set_chunk_bin(mi_bbitmap_t *bbitmap, size_t chunk_idx, mi_chunkbin_t bin)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1495, __func__));
  for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
  {
    if (ibin == bin)
    {
      const bool was_clear = mi_bchunk_set(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_clear)
      {
        __mi_stat_increase_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
    else
    {
      const bool was_set = mi_bchunk_clear(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_set)
      {
        __mi_stat_decrease_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
  }

}


----------------------------
None
----------------------------
***/


bool mi_bbitmap_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1563, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1564, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1568, __func__));
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1569, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  const bool were_allclear = mi_bchunk_setN(&bbitmap->chunks[chunk_idx], cidx, n, 0);
  mi_bbitmap_chunkmap_set(bbitmap, chunk_idx, 1);
  return were_allclear;
}


/*** DEPENDENCIES:
inline static bool mi_bchunk_setN(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 348, __func__));
  if (n == 1)
  {
    return mi_bchunk_set(chunk, cidx, already_set);
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_setNX(chunk, cidx, n, already_set);
  }
  return mi_bchunk_xsetN_(1, chunk, cidx, n, already_set, 0);
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
static void mi_bbitmap_chunkmap_set(mi_bbitmap_t *bbitmap, size_t chunk_idx, bool check_all_set)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1527, __func__));
  if (check_all_set)
  {
    if (mi_bchunk_all_are_set_relaxed(&bbitmap->chunks[chunk_idx]))
    {
      mi_bbitmap_set_chunk_bin(bbitmap, chunk_idx, MI_CBIN_NONE);
    }
  }
  mi_bchunk_set(&bbitmap->chunkmap, chunk_idx, 0);
  mi_bbitmap_chunkmap_set_max(bbitmap, chunk_idx);
}


----------------------------
None
----------------------------
***/


bool mi_bitmap_is_xsetN(mi_xset_t set, mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1180, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1181, __func__));
  ((idx + n) <= mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1182, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1186, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1187, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  return mi_bchunk_is_xsetN(set, &bitmap->chunks[chunk_idx], cidx, n);
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bchunk_is_xsetN(mi_xset_t set, const mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 432, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 433, __func__));
  if (n == 0)
  {
    return 1;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return mi_bfield_atomic_is_xset(set, &chunk->bfields[i], idx);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_is_xsetN_(set, chunk, i, idx, n);
}


----------------------------
typedef bool mi_xset_t
----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


bool mi_bitmap_clear(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_clearN(bitmap, idx, 1);
}


/*** DEPENDENCIES:
bool mi_bitmap_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1135, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1136, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1140, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1141, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  bool maybe_all_clear;
  const bool were_allset = mi_bchunk_clearN(&bitmap->chunks[chunk_idx], cidx, n, &maybe_all_clear);
  if (maybe_all_clear)
  {
    mi_bitmap_chunkmap_try_clear(bitmap, chunk_idx);
  }
  return were_allset;
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
***/


static void mi_bchunks_unsafe_setN(mi_bchunk_t *chunks, mi_bchunkmap_t *cmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1070, __func__));
  size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  const size_t ccount = _mi_divide_up(n, 1 << (6 + 3));
  mi_bchunk_setN(cmap, chunk_idx, ccount, 0);
  size_t m = (1 << (6 + 3)) - cidx;
  if (m > n)
  {
    m = n;
  }
  mi_bchunk_setN(&chunks[chunk_idx], cidx, m, 0);
  chunk_idx += 1;
  n -= m;
  const size_t mid_chunks = n / (1 << (6 + 3));
  if (mid_chunks > 0)
  {
    _mi_memset(&chunks[chunk_idx], ~0, mid_chunks * ((1 << (6 + 3)) / 8));
    chunk_idx += mid_chunks;
    n -= mid_chunks * (1 << (6 + 3));
  }
  if (n > 0)
  {
    (n < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1097, __func__));
    (chunk_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("chunk_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1098, __func__));
    mi_bchunk_setN(&chunks[chunk_idx], 0, n, 0);
  }
}


/*** DEPENDENCIES:
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bchunk_setN(mi_bchunk_t *chunk, size_t cidx, size_t n, size_t *already_set)
{
  ((n > 0) && (n <= (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("n>0 && n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 348, __func__));
  if (n == 1)
  {
    return mi_bchunk_set(chunk, cidx, already_set);
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_setNX(chunk, cidx, n, already_set);
  }
  return mi_bchunk_xsetN_(1, chunk, cidx, n, already_set, 0);
}


----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
None
----------------------------
***/


void mi_bitmap_unsafe_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1105, __func__));
  ((idx + n) <= mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1106, __func__));
  mi_bchunks_unsafe_setN(&bitmap->chunks[0], &bitmap->chunkmap, idx, n);
}


/*** DEPENDENCIES:
static void mi_bchunks_unsafe_setN(mi_bchunk_t *chunks, mi_bchunkmap_t *cmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1070, __func__));
  size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  const size_t ccount = _mi_divide_up(n, 1 << (6 + 3));
  mi_bchunk_setN(cmap, chunk_idx, ccount, 0);
  size_t m = (1 << (6 + 3)) - cidx;
  if (m > n)
  {
    m = n;
  }
  mi_bchunk_setN(&chunks[chunk_idx], cidx, m, 0);
  chunk_idx += 1;
  n -= m;
  const size_t mid_chunks = n / (1 << (6 + 3));
  if (mid_chunks > 0)
  {
    _mi_memset(&chunks[chunk_idx], ~0, mid_chunks * ((1 << (6 + 3)) / 8));
    chunk_idx += mid_chunks;
    n -= mid_chunks * (1 << (6 + 3));
  }
  if (n > 0)
  {
    (n < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1097, __func__));
    (chunk_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("chunk_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1098, __func__));
    mi_bchunk_setN(&chunks[chunk_idx], 0, n, 0);
  }
}


----------------------------
inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


size_t mi_bitmap_size(size_t bit_count, size_t *pchunk_count)
{
  ((bit_count % (1 << (6 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(bit_count % MI_BCHUNK_BITS) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1041, __func__));
  bit_count = _mi_align_up(bit_count, 1 << (6 + 3));
  (bit_count <= ((1 << (6 + 3)) * (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("bit_count <= MI_BITMAP_MAX_BIT_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1043, __func__));
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1044, __func__));
  const size_t chunk_count = bit_count / (1 << (6 + 3));
  (chunk_count >= 1) ? ((void) 0) : (_mi_assert_fail("chunk_count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1046, __func__));
  const size_t size = offsetof(mi_bitmap_t, chunks) + (chunk_count * ((1 << (6 + 3)) / 8));
  ((size % ((1 << (6 + 3)) / 8)) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_BCHUNK_SIZE) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1048, __func__));
  if (pchunk_count != 0)
  {
    *pchunk_count = chunk_count;
  }
  return size;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return (sz + mask) & (~mask);
  }
  else
  {
    return ((sz + mask) / alignment) * alignment;
  }
}


----------------------------
None
----------------------------
***/


size_t mi_bitmap_init(mi_bitmap_t *bitmap, size_t bit_count, bool already_zero)
{
  size_t chunk_count;
  const size_t size = mi_bitmap_size(bit_count, &chunk_count);
  if (!already_zero)
  {
    _mi_memzero_aligned(bitmap, size);
  }
  atomic_store_explicit(&bitmap->chunk_count, chunk_count, memory_order_release);
  (atomic_load_explicit(&bitmap->chunk_count, memory_order_relaxed) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(&bitmap->chunk_count) <= MI_BITMAP_MAX_CHUNK_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1063, __func__));
  return size;
}


/*** DEPENDENCIES:
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
size_t mi_bitmap_size(size_t bit_count, size_t *pchunk_count)
{
  ((bit_count % (1 << (6 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(bit_count % MI_BCHUNK_BITS) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1041, __func__));
  bit_count = _mi_align_up(bit_count, 1 << (6 + 3));
  (bit_count <= ((1 << (6 + 3)) * (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("bit_count <= MI_BITMAP_MAX_BIT_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1043, __func__));
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1044, __func__));
  const size_t chunk_count = bit_count / (1 << (6 + 3));
  (chunk_count >= 1) ? ((void) 0) : (_mi_assert_fail("chunk_count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1046, __func__));
  const size_t size = offsetof(mi_bitmap_t, chunks) + (chunk_count * ((1 << (6 + 3)) / 8));
  ((size % ((1 << (6 + 3)) / 8)) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_BCHUNK_SIZE) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1048, __func__));
  if (pchunk_count != 0)
  {
    *pchunk_count = chunk_count;
  }
  return size;
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


size_t mi_bbitmap_size(size_t bit_count, size_t *pchunk_count)
{
  bit_count = _mi_align_up(bit_count, 1 << (6 + 3));
  (bit_count <= ((1 << (6 + 3)) * (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("bit_count <= MI_BITMAP_MAX_BIT_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1458, __func__));
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1459, __func__));
  const size_t chunk_count = bit_count / (1 << (6 + 3));
  (chunk_count >= 1) ? ((void) 0) : (_mi_assert_fail("chunk_count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1461, __func__));
  const size_t size = offsetof(mi_bbitmap_t, chunks) + (chunk_count * ((1 << (6 + 3)) / 8));
  ((size % ((1 << (6 + 3)) / 8)) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_BCHUNK_SIZE) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1463, __func__));
  if (pchunk_count != 0)
  {
    *pchunk_count = chunk_count;
  }
  return size;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return (sz + mask) & (~mask);
  }
  else
  {
    return ((sz + mask) / alignment) * alignment;
  }
}


----------------------------
None
----------------------------
***/


size_t mi_bbitmap_init(mi_bbitmap_t *bbitmap, size_t bit_count, bool already_zero)
{
  size_t chunk_count;
  const size_t size = mi_bbitmap_size(bit_count, &chunk_count);
  if (!already_zero)
  {
    _mi_memzero_aligned(bbitmap, size);
  }
  atomic_store_explicit(&bbitmap->chunk_count, chunk_count, memory_order_release);
  (atomic_load_explicit(&bbitmap->chunk_count, memory_order_relaxed) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(&bbitmap->chunk_count) <= MI_BITMAP_MAX_CHUNK_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1477, __func__));
  return size;
}


/*** DEPENDENCIES:
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
size_t mi_bbitmap_size(size_t bit_count, size_t *pchunk_count)
{
  bit_count = _mi_align_up(bit_count, 1 << (6 + 3));
  (bit_count <= ((1 << (6 + 3)) * (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("bit_count <= MI_BITMAP_MAX_BIT_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1458, __func__));
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1459, __func__));
  const size_t chunk_count = bit_count / (1 << (6 + 3));
  (chunk_count >= 1) ? ((void) 0) : (_mi_assert_fail("chunk_count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1461, __func__));
  const size_t size = offsetof(mi_bbitmap_t, chunks) + (chunk_count * ((1 << (6 + 3)) / 8));
  ((size % ((1 << (6 + 3)) / 8)) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_BCHUNK_SIZE) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1463, __func__));
  if (pchunk_count != 0)
  {
    *pchunk_count = chunk_count;
  }
  return size;
}


----------------------------
None
----------------------------
***/


void mi_bbitmap_unsafe_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1482, __func__));
  ((idx + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1483, __func__));
  mi_bchunks_unsafe_setN(&bbitmap->chunks[0], &bbitmap->chunkmap, idx, n);
}


/*** DEPENDENCIES:
inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
static void mi_bchunks_unsafe_setN(mi_bchunk_t *chunks, mi_bchunkmap_t *cmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1070, __func__));
  size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  const size_t ccount = _mi_divide_up(n, 1 << (6 + 3));
  mi_bchunk_setN(cmap, chunk_idx, ccount, 0);
  size_t m = (1 << (6 + 3)) - cidx;
  if (m > n)
  {
    m = n;
  }
  mi_bchunk_setN(&chunks[chunk_idx], cidx, m, 0);
  chunk_idx += 1;
  n -= m;
  const size_t mid_chunks = n / (1 << (6 + 3));
  if (mid_chunks > 0)
  {
    _mi_memset(&chunks[chunk_idx], ~0, mid_chunks * ((1 << (6 + 3)) / 8));
    chunk_idx += mid_chunks;
    n -= mid_chunks * (1 << (6 + 3));
  }
  if (n > 0)
  {
    (n < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1097, __func__));
    (chunk_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("chunk_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1098, __func__));
    mi_bchunk_setN(&chunks[chunk_idx], 0, n, 0);
  }
}


----------------------------
None
----------------------------
***/


bool mi_bitmap_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_setN(bitmap, idx, 1, 0);
}


/*** DEPENDENCIES:
bool mi_bitmap_setN(mi_bitmap_t *bitmap, size_t idx, size_t n, size_t *already_set)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1118, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1119, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1123, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1124, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  const bool were_allclear = mi_bchunk_setN(&bitmap->chunks[chunk_idx], cidx, n, already_set);
  mi_bitmap_chunkmap_set(bitmap, chunk_idx);
  return were_allclear;
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
***/


inline static void mi_bfield_atomic_clear_once_set(_Atomic mi_bfield_t *b, size_t idx)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 111, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  do
  {
    if (__builtin_expect(!(!((old & mask) == 0)), 0))
    {
      old = atomic_load_explicit(b, memory_order_acquire);
      if ((old & mask) == 0)
      {
        __mi_stat_counter_increase_mt(&_mi_subproc()->stats.pages_unabandon_busy_wait, 1);
      }
      while ((old & mask) == 0)
      {
        mi_atomic_yield();
        old = atomic_load_explicit(b, memory_order_acquire);
      }

    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &old, old & (~mask), memory_order_acq_rel, memory_order_acquire));
  ((old & mask) == mask) ? ((void) 0) : (_mi_assert_fail("(old&mask)==mask", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 126, __func__));
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
mi_subproc_t *_mi_subproc(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return _mi_subproc_main();
  }
  else
  {
    return heap->tld->subproc;
  }
}


----------------------------
inline static void mi_atomic_yield(void)
{
}


----------------------------
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static void mi_bchunk_clear_once_set(mi_bchunk_t *chunk, size_t cidx)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 927, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  mi_bfield_atomic_clear_once_set(&chunk->bfields[i], idx);
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static void mi_bfield_atomic_clear_once_set(_Atomic mi_bfield_t *b, size_t idx)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 111, __func__));
  const mi_bfield_t mask = mi_bfield_mask(1, idx);
  ;
  mi_bfield_t old = atomic_load_explicit(b, memory_order_relaxed);
  do
  {
    if (__builtin_expect(!(!((old & mask) == 0)), 0))
    {
      old = atomic_load_explicit(b, memory_order_acquire);
      if ((old & mask) == 0)
      {
        __mi_stat_counter_increase_mt(&_mi_subproc()->stats.pages_unabandon_busy_wait, 1);
      }
      while ((old & mask) == 0)
      {
        mi_atomic_yield();
        old = atomic_load_explicit(b, memory_order_acquire);
      }

    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &old, old & (~mask), memory_order_acq_rel, memory_order_acquire));
  ((old & mask) == mask) ? ((void) 0) : (_mi_assert_fail("(old&mask)==mask", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 126, __func__));
}


----------------------------
None
----------------------------
***/


void mi_bitmap_clear_once_set(mi_bitmap_t *bitmap, size_t idx)
{
  (idx < mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("idx < mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1370, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1373, __func__));
  mi_bchunk_clear_once_set(&bitmap->chunks[chunk_idx], cidx);
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static void mi_bchunk_clear_once_set(mi_bchunk_t *chunk, size_t cidx)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 927, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  mi_bfield_atomic_clear_once_set(&chunk->bfields[i], idx);
}


----------------------------
inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


inline static size_t mi_bfield_atomic_popcount_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_popcount(x & mask);
}


/*** DEPENDENCIES:
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


static size_t mi_bchunk_popcountN_(mi_bchunk_t *chunk, size_t field_idx, size_t idx, size_t n)
{
  ((((field_idx * (1 << (3 + 3))) + idx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("(field_idx*MI_BFIELD_BITS) + idx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 377, __func__));
  size_t count = 0;
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 382, __func__));
    (field_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 383, __func__));
    const size_t mask = mi_bfield_mask(m, idx);
    count += mi_bfield_atomic_popcount_mask(&chunk->bfields[field_idx], mask);
    field_idx += 1;
    idx = 0;
    n -= m;
  }

  return count;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static size_t mi_bfield_atomic_popcount_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_popcount(x & mask);
}


----------------------------
None
----------------------------
***/


inline static size_t mi_bchunk_popcountN(mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 396, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 397, __func__));
  if (n == 0)
  {
    return 0;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return (mi_bfield_atomic_is_set(&chunk->bfields[i], idx)) ? (1) : (0);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_popcount_mask(&chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_popcountN_(chunk, i, idx, n);
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static size_t mi_bfield_atomic_popcount_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_popcount(x & mask);
}


----------------------------
static size_t mi_bchunk_popcountN_(mi_bchunk_t *chunk, size_t field_idx, size_t idx, size_t n)
{
  ((((field_idx * (1 << (3 + 3))) + idx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("(field_idx*MI_BFIELD_BITS) + idx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 377, __func__));
  size_t count = 0;
  while (n > 0)
  {
    size_t m = (1 << (3 + 3)) - idx;
    if (m > n)
    {
      m = n;
    }
    ((idx + m) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx + m <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 382, __func__));
    (field_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("field_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 383, __func__));
    const size_t mask = mi_bfield_mask(m, idx);
    count += mi_bfield_atomic_popcount_mask(&chunk->bfields[field_idx], mask);
    field_idx += 1;
    idx = 0;
    n -= m;
  }

  return count;
}


----------------------------
inline static bool mi_bfield_atomic_is_set(const mi_bfield_t *b, const size_t idx)
{
  const mi_bfield_t x = atomic_load_explicit(b, memory_order_relaxed);
  return (x & mi_bfield_mask(1, idx)) != 0;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
None
----------------------------
***/


size_t mi_bitmap_popcountN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1153, __func__));
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1154, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1158, __func__));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1159, __func__));
  if ((cidx + n) > (1 << (6 + 3)))
  {
    n = (1 << (6 + 3)) - cidx;
  }
  return mi_bchunk_popcountN(&bitmap->chunks[chunk_idx], cidx, n);
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static size_t mi_bchunk_popcountN(mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 396, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 397, __func__));
  if (n == 0)
  {
    return 0;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return (mi_bfield_atomic_is_set(&chunk->bfields[i], idx)) ? (1) : (0);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_popcount_mask(&chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_popcountN_(chunk, i, idx, n);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
None
----------------------------
***/


inline static size_t mi_bfield_clz(mi_bfield_t x)
{
  return mi_clz(x);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}


----------------------------
***/


inline static size_t mi_bfield_ctz(mi_bfield_t x)
{
  return mi_ctz(x);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}


----------------------------
***/


// hint:  ['cidx_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
bool helper_mi_bchunk_try_find_and_clearN__1(size_t * const cidx_ref, size_t * const i_ref, mi_bchunk_t * const chunk, size_t n, size_t * const pidx)
{
  size_t cidx = *cidx_ref;
  size_t i = *i_ref;
  size_t m = n;
  mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
  size_t ones = mi_bfield_clz(~b);
  cidx = (i * (1 << (3 + 3))) + ((1 << (3 + 3)) - ones);
  if (ones >= m)
  {
    m = 0;
  }
  else
  {
    m -= ones;
    size_t j = 1;
    while ((i + j) < ((1 << (6 + 3)) / (1 << (3 + 3))))
    {
      (m > 0) ? ((void) 0) : (_mi_assert_fail("m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 884, __func__));
      b = atomic_load_explicit(&chunk->bfields[i + j], memory_order_relaxed);
      ones = mi_bfield_ctz(~b);
      if (ones >= m)
      {
        m = 0;
        break;
      }
      else
        if (ones == (1 << (3 + 3)))
      {
        j += 1;
        m -= 1 << (3 + 3);
      }
      else
      {
        i = (i + j) - 1;
        (m > 0) ? ((void) 0) : (_mi_assert_fail("m>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 900, __func__));
        break;
      }
    }

  }
  if (m == 0)
  {
    if (mi_bchunk_try_clearN(chunk, cidx, n, 0))
    {
      *pidx = cidx;
      ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 911, __func__));
      (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 912, __func__));
      return 1;
    }
  }
  *cidx_ref = cidx;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static size_t mi_bfield_ctz(mi_bfield_t x)
{
  return mi_ctz(x);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static size_t mi_bfield_clz(mi_bfield_t x)
{
  return mi_clz(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bchunk_try_clearN(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *maybe_all_clear)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 553, __func__));
  if (n <= (1 << (3 + 3)))
  {
    return mi_bchunk_try_clearNX(chunk, cidx, n, maybe_all_clear);
  }
  return mi_bchunk_try_clearN_(chunk, cidx, n, maybe_all_clear);
}


----------------------------
None
----------------------------
***/


static bool mi_bchunk_try_find_and_clearN_(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  if ((n == 0) || (n > (1 << (6 + 3))))
  {
    return 0;
  }
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 863, __func__));
  const size_t skip_count = (n - 1) / (1 << (3 + 3));
  size_t cidx;
  for (size_t i = 0; i < (((1 << (6 + 3)) / (1 << (3 + 3))) - skip_count); i += 1)
  {
    helper_mi_bchunk_try_find_and_clearN__1(&cidx, &i, chunk, n, pidx);
  }

  return 0;
}


/*** DEPENDENCIES:
bool helper_mi_bchunk_try_find_and_clearN__1(size_t * const cidx_ref, size_t * const i_ref, mi_bchunk_t * const chunk, size_t n, size_t * const pidx)
{
  size_t cidx = *cidx_ref;
  size_t i = *i_ref;
  size_t m = n;
  mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
  size_t ones = mi_bfield_clz(~b);
  cidx = (i * (1 << (3 + 3))) + ((1 << (3 + 3)) - ones);
  if (ones >= m)
  {
    m = 0;
  }
  else
  {
    m -= ones;
    size_t j = 1;
    while ((i + j) < ((1 << (6 + 3)) / (1 << (3 + 3))))
    {
      (m > 0) ? ((void) 0) : (_mi_assert_fail("m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 884, __func__));
      b = atomic_load_explicit(&chunk->bfields[i + j], memory_order_relaxed);
      ones = mi_bfield_ctz(~b);
      if (ones >= m)
      {
        m = 0;
        break;
      }
      else
        if (ones == (1 << (3 + 3)))
      {
        j += 1;
        m -= 1 << (3 + 3);
      }
      else
      {
        i = (i + j) - 1;
        (m > 0) ? ((void) 0) : (_mi_assert_fail("m>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 900, __func__));
        break;
      }
    }

  }
  if (m == 0)
  {
    if (mi_bchunk_try_clearN(chunk, cidx, n, 0))
    {
      *pidx = cidx;
      ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 911, __func__));
      (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 912, __func__));
      return 1;
    }
  }
  *cidx_ref = cidx;
  *i_ref = i;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
None
----------------------------
***/


bool helper_helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_chunkbin_t bbin, size_t cmap_idx)
{
  {
    const mi_bfield_t cmap_entry = atomic_load_explicit(&bbitmap->chunkmap.bfields[cmap_idx], memory_order_relaxed);
    const size_t cmap_entry_cycle = (cmap_idx != cmap_acc) ? (1 << (3 + 3)) : (cmap_acc_bits);
    if (cmap_entry == 0)
    {
      continue;
    }
    mi_bfield_t cmap_bins[MI_CBIN_COUNT] = {0};
    cmap_bins[MI_CBIN_NONE] = cmap_entry;
    for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
    {
      const mi_bfield_t cmap_bin = atomic_load_explicit(&bbitmap->chunkmap_bins[ibin].bfields[cmap_idx], memory_order_relaxed);
      cmap_bins[ibin] = cmap_bin & cmap_entry;
      cmap_bins[MI_CBIN_NONE] &= ~cmap_bin;
    }

    (bbin < MI_CBIN_NONE) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_NONE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1664, __func__));
    for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin <= MI_CBIN_NONE; ibin = (ibin == bbin) ? (MI_CBIN_NONE) : (mi_chunkbin_inc(ibin)))
    {
      (ibin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("ibin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1669, __func__));
      const mi_bfield_t cmap_bin = cmap_bins[ibin];
      size_t eidx = 0;
      {
        const size_t _startY = ((uint32_t) tseq) % ((uint32_t) cmap_entry_cycle);
        {
          (_startY <= cmap_entry_cycle) ? ((void) 0) : (_mi_assert_fail("_startY <= cmap_entry_cycle", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          (_startY < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startY < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          (cmap_entry_cycle <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("cmap_entry_cycle <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          mi_bfield_t _cycle_maskY = mi_bfield_mask(cmap_entry_cycle - _startY, _startY);
          size_t _bcountY = mi_bfield_popcount(cmap_bin);
          mi_bfield_t _bY = cmap_bin & _cycle_maskY;
          while (_bcountY > 0)
          {
            _bcountY -= 1;
            if (_bY == 0)
            {
              _bY = cmap_bin & (~_cycle_maskY);
            }
            bool _foundY = mi_bfield_find_least_bit(_bY, &eidx);
            (_foundY) ? ((void) 0) : (_mi_assert_fail("_foundY", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
            (void) _foundY;
            {
              {
                const size_t chunk_idx = (cmap_idx * (1 << (3 + 3))) + eidx;
                mi_bchunk_t *chunk = &bbitmap->chunks[chunk_idx];
                size_t cidx;
                if ((*on_find)(chunk, n, &cidx))
                {
                  if ((cidx == 0) && (ibin == MI_CBIN_NONE))
                  {
                    mi_bbitmap_set_chunk_bin(bbitmap, chunk_idx, bbin);
                  }
                  *pidx = (chunk_idx * (1 << (6 + 3))) + cidx;
                  (((*pidx) + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1688, __func__));
                  return 1;
                }
                else
                {
                  mi_bbitmap_chunkmap_try_clear(bbitmap, chunk_idx);
                }
              }
            }
            _bY = mi_bfield_clear_least_bit(_bY);
          }

        }
        ;
      }
      ;
    }

  }
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}


----------------------------
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
inline static mi_bfield_t mi_bfield_clear_least_bit(mi_bfield_t x)
{
  return x & (x - 1);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
static bool mi_bbitmap_chunkmap_try_clear(mi_bbitmap_t *bbitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1539, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bbitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bbitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bbitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  mi_bbitmap_chunkmap_set_max(bbitmap, chunk_idx);
  return 1;
}


----------------------------
static void mi_bbitmap_set_chunk_bin(mi_bbitmap_t *bbitmap, size_t chunk_idx, mi_chunkbin_t bin)
{
  (chunk_idx < mi_bbitmap_chunk_count(bbitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bbitmap_chunk_count(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1495, __func__));
  for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
  {
    if (ibin == bin)
    {
      const bool was_clear = mi_bchunk_set(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_clear)
      {
        __mi_stat_increase_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
    else
    {
      const bool was_set = mi_bchunk_clear(&bbitmap->chunkmap_bins[ibin], chunk_idx, 0);
      if (was_set)
      {
        __mi_stat_decrease_mt(&_mi_subproc()->stats.chunk_bins[ibin], 1);
      }
    }
  }

}


----------------------------
inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


// hint:  ['_bcountX_ref is a mutable refrence to size_t', '_bX_ref is a mutable refrence to mi_bfield_t']
bool helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1(size_t * const _bcountX_ref, mi_bfield_t * const _bX_ref, mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const mi_chunkbin_t bbin, size_t cmap_idx, mi_bfield_t _cycle_maskX)
{
  size_t _bcountX = *_bcountX_ref;
  mi_bfield_t _bX = *_bX_ref;
  _bcountX -= 1;
  if (_bX == 0)
  {
    _bX = cmap_mask & (~_cycle_maskX);
  }
  bool _foundX = mi_bfield_find_least_bit(_bX, &cmap_idx);
  (_foundX) ? ((void) 0) : (_mi_assert_fail("_foundX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (void) _foundX;
  {
    helper_helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, bbin, cmap_idx);
  }
  _bX = mi_bfield_clear_least_bit(_bX);
  *_bcountX_ref = _bcountX;
  *_bX_ref = _bX;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_clear_least_bit(mi_bfield_t x)
{
  return x & (x - 1);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
bool helper_helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_chunkbin_t bbin, size_t cmap_idx)
{
  {
    const mi_bfield_t cmap_entry = atomic_load_explicit(&bbitmap->chunkmap.bfields[cmap_idx], memory_order_relaxed);
    const size_t cmap_entry_cycle = (cmap_idx != cmap_acc) ? (1 << (3 + 3)) : (cmap_acc_bits);
    if (cmap_entry == 0)
    {
      continue;
    }
    mi_bfield_t cmap_bins[MI_CBIN_COUNT] = {0};
    cmap_bins[MI_CBIN_NONE] = cmap_entry;
    for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
    {
      const mi_bfield_t cmap_bin = atomic_load_explicit(&bbitmap->chunkmap_bins[ibin].bfields[cmap_idx], memory_order_relaxed);
      cmap_bins[ibin] = cmap_bin & cmap_entry;
      cmap_bins[MI_CBIN_NONE] &= ~cmap_bin;
    }

    (bbin < MI_CBIN_NONE) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_NONE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1664, __func__));
    for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin <= MI_CBIN_NONE; ibin = (ibin == bbin) ? (MI_CBIN_NONE) : (mi_chunkbin_inc(ibin)))
    {
      (ibin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("ibin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1669, __func__));
      const mi_bfield_t cmap_bin = cmap_bins[ibin];
      size_t eidx = 0;
      {
        const size_t _startY = ((uint32_t) tseq) % ((uint32_t) cmap_entry_cycle);
        {
          (_startY <= cmap_entry_cycle) ? ((void) 0) : (_mi_assert_fail("_startY <= cmap_entry_cycle", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          (_startY < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startY < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          (cmap_entry_cycle <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("cmap_entry_cycle <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
          mi_bfield_t _cycle_maskY = mi_bfield_mask(cmap_entry_cycle - _startY, _startY);
          size_t _bcountY = mi_bfield_popcount(cmap_bin);
          mi_bfield_t _bY = cmap_bin & _cycle_maskY;
          while (_bcountY > 0)
          {
            _bcountY -= 1;
            if (_bY == 0)
            {
              _bY = cmap_bin & (~_cycle_maskY);
            }
            bool _foundY = mi_bfield_find_least_bit(_bY, &eidx);
            (_foundY) ? ((void) 0) : (_mi_assert_fail("_foundY", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1672, __func__));
            (void) _foundY;
            {
              {
                const size_t chunk_idx = (cmap_idx * (1 << (3 + 3))) + eidx;
                mi_bchunk_t *chunk = &bbitmap->chunks[chunk_idx];
                size_t cidx;
                if ((*on_find)(chunk, n, &cidx))
                {
                  if ((cidx == 0) && (ibin == MI_CBIN_NONE))
                  {
                    mi_bbitmap_set_chunk_bin(bbitmap, chunk_idx, bbin);
                  }
                  *pidx = (chunk_idx * (1 << (6 + 3))) + cidx;
                  (((*pidx) + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1688, __func__));
                  return 1;
                }
                else
                {
                  mi_bbitmap_chunkmap_try_clear(bbitmap, chunk_idx);
                }
              }
            }
            _bY = mi_bfield_clear_least_bit(_bY);
          }

        }
        ;
      }
      ;
    }

  }
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


bool helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const size_t cmap_cycle, const mi_chunkbin_t bbin, size_t cmap_idx, const size_t _startX)
{
  (_startX <= cmap_cycle) ? ((void) 0) : (_mi_assert_fail("_startX <= cmap_cycle", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (_startX < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startX < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (cmap_cycle <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("cmap_cycle <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  mi_bfield_t _cycle_maskX = mi_bfield_mask(cmap_cycle - _startX, _startX);
  size_t _bcountX = mi_bfield_popcount(cmap_mask);
  mi_bfield_t _bX = cmap_mask & _cycle_maskX;
  while (_bcountX > 0)
  {
    helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1(&_bcountX, &_bX, bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, bbin, cmap_idx, _cycle_maskX);
  }

}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
bool helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1(size_t * const _bcountX_ref, mi_bfield_t * const _bX_ref, mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const mi_chunkbin_t bbin, size_t cmap_idx, mi_bfield_t _cycle_maskX)
{
  size_t _bcountX = *_bcountX_ref;
  mi_bfield_t _bX = *_bX_ref;
  _bcountX -= 1;
  if (_bX == 0)
  {
    _bX = cmap_mask & (~_cycle_maskX);
  }
  bool _foundX = mi_bfield_find_least_bit(_bX, &cmap_idx);
  (_foundX) ? ((void) 0) : (_mi_assert_fail("_foundX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (void) _foundX;
  {
    helper_helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, bbin, cmap_idx);
  }
  _bX = mi_bfield_clear_least_bit(_bX);
  *_bcountX_ref = _bcountX;
  *_bX_ref = _bX;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


bool helper_mi_bbitmap_try_find_and_clear_generic_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const size_t cmap_cycle, const mi_chunkbin_t bbin, size_t cmap_idx)
{
  const size_t _startX = ((uint32_t) tseq) % ((uint32_t) cmap_cycle);
  {
    helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx, _startX);
  }
  ;
}


/*** DEPENDENCIES:
bool helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const size_t cmap_cycle, const mi_chunkbin_t bbin, size_t cmap_idx, const size_t _startX)
{
  (_startX <= cmap_cycle) ? ((void) 0) : (_mi_assert_fail("_startX <= cmap_cycle", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (_startX < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startX < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  (cmap_cycle <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("cmap_cycle <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1645, __func__));
  mi_bfield_t _cycle_maskX = mi_bfield_mask(cmap_cycle - _startX, _startX);
  size_t _bcountX = mi_bfield_popcount(cmap_mask);
  mi_bfield_t _bX = cmap_mask & _cycle_maskX;
  while (_bcountX > 0)
  {
    helper_helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1_1(&_bcountX, &_bX, bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, bbin, cmap_idx, _cycle_maskX);
  }

}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
typedef size_t mi_bfield_t
----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
***/


inline static bool mi_bbitmap_try_find_and_clear_generic(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx, mi_bchunk_try_find_and_clear_fun_t *on_find)
{
  const size_t cmap_max_count = _mi_divide_up(mi_bbitmap_chunk_count(bbitmap), 1 << (3 + 3));
  const size_t chunk_acc = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  const size_t cmap_acc = chunk_acc / (1 << (3 + 3));
  const size_t cmap_acc_bits = 1 + (chunk_acc % (1 << (3 + 3)));
  ((1 << (3 + 3)) >= ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("MI_BFIELD_BITS >= MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1639, __func__));
  const mi_bfield_t cmap_mask = mi_bfield_mask(cmap_max_count, 0);
  const size_t cmap_cycle = cmap_acc + 1;
  const mi_chunkbin_t bbin = mi_chunkbin_of(n);
  size_t cmap_idx = 0;
  {
    helper_mi_bbitmap_try_find_and_clear_generic_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx);
  }
  ;
  return 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static mi_chunkbin_t mi_chunkbin_of(size_t slice_count)
{
  if (slice_count == 1)
  {
    return MI_CBIN_SMALL;
  }
  if (slice_count == 8)
  {
    return MI_CBIN_MEDIUM;
  }
  return MI_CBIN_OTHER;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef bool mi_bchunk_try_find_and_clear_fun_t(mi_bchunk_t *chunk, size_t n, size_t *idx)
----------------------------
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
bool helper_mi_bbitmap_try_find_and_clear_generic_1(mi_bbitmap_t * const bbitmap, size_t tseq, size_t n, size_t * const pidx, const size_t cmap_acc, const size_t cmap_acc_bits, const mi_bfield_t cmap_mask, const size_t cmap_cycle, const mi_chunkbin_t bbin, size_t cmap_idx)
{
  const size_t _startX = ((uint32_t) tseq) % ((uint32_t) cmap_cycle);
  {
    helper_helper_mi_bbitmap_try_find_and_clear_generic_1_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx, _startX);
  }
  ;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


bool mi_bbitmap_try_find_and_clearN_(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx)
{
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1728, __func__));
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, n, pidx, &mi_bchunk_try_find_and_clearN_);
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
static bool mi_bchunk_try_find_and_clearN_(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  if ((n == 0) || (n > (1 << (6 + 3))))
  {
    return 0;
  }
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 863, __func__));
  const size_t skip_count = (n - 1) / (1 << (3 + 3));
  size_t cidx;
  for (size_t i = 0; i < (((1 << (6 + 3)) / (1 << (3 + 3))) - skip_count); i += 1)
  {
    helper_mi_bchunk_try_find_and_clearN__1(&cidx, &i, chunk, n, pidx);
  }

  return 0;
}


----------------------------
inline static bool mi_bbitmap_try_find_and_clear_generic(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx, mi_bchunk_try_find_and_clear_fun_t *on_find)
{
  const size_t cmap_max_count = _mi_divide_up(mi_bbitmap_chunk_count(bbitmap), 1 << (3 + 3));
  const size_t chunk_acc = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  const size_t cmap_acc = chunk_acc / (1 << (3 + 3));
  const size_t cmap_acc_bits = 1 + (chunk_acc % (1 << (3 + 3)));
  ((1 << (3 + 3)) >= ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("MI_BFIELD_BITS >= MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1639, __func__));
  const mi_bfield_t cmap_mask = mi_bfield_mask(cmap_max_count, 0);
  const size_t cmap_cycle = cmap_acc + 1;
  const mi_chunkbin_t bbin = mi_chunkbin_of(n);
  size_t cmap_idx = 0;
  {
    helper_mi_bbitmap_try_find_and_clear_generic_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx);
  }
  ;
  return 0;
}


----------------------------
None
----------------------------
***/


bool helper_mi_bchunk_try_find_and_clearNX_1(mi_bchunk_t * const chunk, size_t n, size_t * const pidx, const mi_bfield_t mask, int i)
{
  mi_bfield_t b0 = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
  mi_bfield_t b = b0;
  size_t idx;
  while (mi_bfield_find_least_bit(b, &idx))
  {
    if ((idx + n) > (1 << (3 + 3)))
    {
      break;
    }
    const size_t bmask = mask << idx;
    ((bmask >> idx) == mask) ? ((void) 0) : (_mi_assert_fail("bmask>>idx == mask", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 811, __func__));
    if ((b & bmask) == bmask)
    {
      if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[i], bmask, b0, 0)), 1))
      {
        *pidx = (i * (1 << (3 + 3))) + idx;
        ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 815, __func__));
        (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 816, __func__));
        return 1;
      }
      else
      {
        b = (b0 = atomic_load_explicit(&chunk->bfields[i], memory_order_acquire));
      }
    }
    else
    {
      b = b & (b + (mi_bfield_one() << idx));
    }
  }

  if ((b != 0) && (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)))
  {
    const size_t post = mi_bfield_clz(~b);
    if (post > 0)
    {
      const size_t pre = mi_bfield_ctz(~atomic_load_explicit(&chunk->bfields[i + 1], memory_order_relaxed));
      if ((post + pre) >= n)
      {
        const size_t cidx = (i * (1 << (3 + 3))) + ((1 << (3 + 3)) - post);
        if (mi_bchunk_try_clearNX(chunk, cidx, n, 0))
        {
          *pidx = cidx;
          ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 844, __func__));
          (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 845, __func__));
          return 1;
        }
      }
    }
  }
}


/*** DEPENDENCIES:
inline static bool mi_bchunk_try_clearNX(mi_bchunk_t *chunk, size_t cidx, size_t n, bool *pmaybe_all_clear)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 447, __func__));
  (n <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 448, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (__builtin_expect(!(!((idx + n) <= (1 << (3 + 3)))), 1))
  {
    return mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(n, idx), pmaybe_all_clear);
  }
  else
  {
    const size_t m = (1 << (3 + 3)) - idx;
    (m < n) ? ((void) 0) : (_mi_assert_fail("m < n", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 458, __func__));
    (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)) ? ((void) 0) : (_mi_assert_fail("i < MI_BCHUNK_FIELDS - 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 459, __func__));
    bool field1_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), &field1_is_clear))
    {
      return 0;
    }
    ((n - m) > 0) ? ((void) 0) : (_mi_assert_fail("n - m > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 463, __func__));
    ((n - m) < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n - m < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 464, __func__));
    bool field2_is_clear;
    if (!mi_bfield_atomic_try_clear_mask(&chunk->bfields[i + 1], mi_bfield_mask(n - m, 0), &field2_is_clear))
    {
      mi_bfield_atomic_set_mask(&chunk->bfields[i], mi_bfield_mask(m, idx), 0);
      return 0;
    }
    if (pmaybe_all_clear != 0)
    {
      *pmaybe_all_clear = field1_is_clear && field2_is_clear;
    }
    return 1;
  }
}


----------------------------
inline static size_t mi_bfield_ctz(mi_bfield_t x)
{
  return mi_ctz(x);
}


----------------------------
inline static mi_bfield_t mi_bfield_one(void)
{
  return 1;
}


----------------------------
inline static bool mi_bfield_atomic_try_clear_mask_of(_Atomic mi_bfield_t *b, mi_bfield_t mask, mi_bfield_t expect, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 169, __func__));
  do
  {
    if ((expect & mask) != mask)
    {
      if (all_clear != 0)
      {
        *all_clear = expect == 0;
      }
      return 0;
    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &expect, expect & (~mask), memory_order_acq_rel, memory_order_acquire));
  if (all_clear != 0)
  {
    *all_clear = (expect & (~mask)) == 0;
  }
  return 1;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
inline static size_t mi_bfield_clz(mi_bfield_t x)
{
  return mi_clz(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


static bool mi_bchunk_try_find_and_clearNX(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  if ((n == 0) || (n > (1 << (3 + 3))))
  {
    return 0;
  }
  const mi_bfield_t mask = mi_bfield_mask(n, 0);
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    helper_mi_bchunk_try_find_and_clearNX_1(chunk, n, pidx, mask, i);
  }

  return 0;
}


/*** DEPENDENCIES:
bool helper_mi_bchunk_try_find_and_clearNX_1(mi_bchunk_t * const chunk, size_t n, size_t * const pidx, const mi_bfield_t mask, int i)
{
  mi_bfield_t b0 = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
  mi_bfield_t b = b0;
  size_t idx;
  while (mi_bfield_find_least_bit(b, &idx))
  {
    if ((idx + n) > (1 << (3 + 3)))
    {
      break;
    }
    const size_t bmask = mask << idx;
    ((bmask >> idx) == mask) ? ((void) 0) : (_mi_assert_fail("bmask>>idx == mask", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 811, __func__));
    if ((b & bmask) == bmask)
    {
      if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[i], bmask, b0, 0)), 1))
      {
        *pidx = (i * (1 << (3 + 3))) + idx;
        ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 815, __func__));
        (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 816, __func__));
        return 1;
      }
      else
      {
        b = (b0 = atomic_load_explicit(&chunk->bfields[i], memory_order_acquire));
      }
    }
    else
    {
      b = b & (b + (mi_bfield_one() << idx));
    }
  }

  if ((b != 0) && (i < (((1 << (6 + 3)) / (1 << (3 + 3))) - 1)))
  {
    const size_t post = mi_bfield_clz(~b);
    if (post > 0)
    {
      const size_t pre = mi_bfield_ctz(~atomic_load_explicit(&chunk->bfields[i + 1], memory_order_relaxed));
      if ((post + pre) >= n)
      {
        const size_t cidx = (i * (1 << (3 + 3))) + ((1 << (3 + 3)) - post);
        if (mi_bchunk_try_clearNX(chunk, cidx, n, 0))
        {
          *pidx = cidx;
          ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 844, __func__));
          (((*pidx) + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 845, __func__));
          return 1;
        }
      }
    }
  }
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


bool mi_bbitmap_try_find_and_clearNX(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx)
{
  (n <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1723, __func__));
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, n, pidx, &mi_bchunk_try_find_and_clearNX);
}


/*** DEPENDENCIES:
static bool mi_bchunk_try_find_and_clearNX(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  if ((n == 0) || (n > (1 << (3 + 3))))
  {
    return 0;
  }
  const mi_bfield_t mask = mi_bfield_mask(n, 0);
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    helper_mi_bchunk_try_find_and_clearNX_1(chunk, n, pidx, mask, i);
  }

  return 0;
}


----------------------------
inline static bool mi_bbitmap_try_find_and_clear_generic(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx, mi_bchunk_try_find_and_clear_fun_t *on_find)
{
  const size_t cmap_max_count = _mi_divide_up(mi_bbitmap_chunk_count(bbitmap), 1 << (3 + 3));
  const size_t chunk_acc = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  const size_t cmap_acc = chunk_acc / (1 << (3 + 3));
  const size_t cmap_acc_bits = 1 + (chunk_acc % (1 << (3 + 3)));
  ((1 << (3 + 3)) >= ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("MI_BFIELD_BITS >= MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1639, __func__));
  const mi_bfield_t cmap_mask = mi_bfield_mask(cmap_max_count, 0);
  const size_t cmap_cycle = cmap_acc + 1;
  const mi_chunkbin_t bbin = mi_chunkbin_of(n);
  size_t cmap_idx = 0;
  {
    helper_mi_bbitmap_try_find_and_clear_generic_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx);
  }
  ;
  return 0;
}


----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_try_find_and_clear8_at(mi_bchunk_t *chunk, size_t chunk_idx, size_t *pidx)
{
  const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[chunk_idx], memory_order_relaxed);
  const mi_bfield_t has_set8 = (((~b) - ((~((mi_bfield_t) 0)) / 0xFF)) & (b & (((~((mi_bfield_t) 0)) / 0xFF) << 7))) >> 7;
  size_t idx;
  if (mi_bfield_find_least_bit(has_set8, &idx))
  {
    (idx <= ((1 << (3 + 3)) - 8)) ? ((void) 0) : (_mi_assert_fail("idx <= (MI_BFIELD_BITS - 8)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 689, __func__));
    ((idx % 8) == 0) ? ((void) 0) : (_mi_assert_fail("(idx%8)==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 690, __func__));
    if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[chunk_idx], ((mi_bfield_t) 0xFF) << idx, b, 0)), 1))
    {
      *pidx = (chunk_idx * (1 << (3 + 3))) + idx;
      (((*pidx) + 8) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + 8 <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 693, __func__));
      return 1;
    }
  }
  return 0;
}


/*** DEPENDENCIES:
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bfield_atomic_try_clear_mask_of(_Atomic mi_bfield_t *b, mi_bfield_t mask, mi_bfield_t expect, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 169, __func__));
  do
  {
    if ((expect & mask) != mask)
    {
      if (all_clear != 0)
      {
        *all_clear = expect == 0;
      }
      return 0;
    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &expect, expect & (~mask), memory_order_acq_rel, memory_order_acquire));
  if (all_clear != 0)
  {
    *all_clear = (expect & (~mask)) == 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


static bool mi_bchunk_try_find_and_clear8(mi_bchunk_t *chunk, size_t *pidx)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (mi_bchunk_try_find_and_clear8_at(chunk, i, pidx))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bchunk_try_find_and_clear8_at(mi_bchunk_t *chunk, size_t chunk_idx, size_t *pidx)
{
  const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[chunk_idx], memory_order_relaxed);
  const mi_bfield_t has_set8 = (((~b) - ((~((mi_bfield_t) 0)) / 0xFF)) & (b & (((~((mi_bfield_t) 0)) / 0xFF) << 7))) >> 7;
  size_t idx;
  if (mi_bfield_find_least_bit(has_set8, &idx))
  {
    (idx <= ((1 << (3 + 3)) - 8)) ? ((void) 0) : (_mi_assert_fail("idx <= (MI_BFIELD_BITS - 8)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 689, __func__));
    ((idx % 8) == 0) ? ((void) 0) : (_mi_assert_fail("(idx%8)==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 690, __func__));
    if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[chunk_idx], ((mi_bfield_t) 0xFF) << idx, b, 0)), 1))
    {
      *pidx = (chunk_idx * (1 << (3 + 3))) + idx;
      (((*pidx) + 8) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx + 8 <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 693, __func__));
      return 1;
    }
  }
  return 0;
}


----------------------------
***/


inline static bool mi_bchunk_try_find_and_clear_8(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  (n == 8) ? ((void) 0) : (_mi_assert_fail("n==8", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 739, __func__));
  (void) n;
  return mi_bchunk_try_find_and_clear8(chunk, pidx);
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
static bool mi_bchunk_try_find_and_clear8(mi_bchunk_t *chunk, size_t *pidx)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (mi_bchunk_try_find_and_clear8_at(chunk, i, pidx))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


bool mi_bbitmap_try_find_and_clear8(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx)
{
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, 8, pidx, &mi_bchunk_try_find_and_clear_8);
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bbitmap_try_find_and_clear_generic(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx, mi_bchunk_try_find_and_clear_fun_t *on_find)
{
  const size_t cmap_max_count = _mi_divide_up(mi_bbitmap_chunk_count(bbitmap), 1 << (3 + 3));
  const size_t chunk_acc = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  const size_t cmap_acc = chunk_acc / (1 << (3 + 3));
  const size_t cmap_acc_bits = 1 + (chunk_acc % (1 << (3 + 3)));
  ((1 << (3 + 3)) >= ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("MI_BFIELD_BITS >= MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1639, __func__));
  const mi_bfield_t cmap_mask = mi_bfield_mask(cmap_max_count, 0);
  const size_t cmap_cycle = cmap_acc + 1;
  const mi_chunkbin_t bbin = mi_chunkbin_of(n);
  size_t cmap_idx = 0;
  {
    helper_mi_bbitmap_try_find_and_clear_generic_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx);
  }
  ;
  return 0;
}


----------------------------
inline static bool mi_bchunk_try_find_and_clear_8(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  (n == 8) ? ((void) 0) : (_mi_assert_fail("n==8", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 739, __func__));
  (void) n;
  return mi_bchunk_try_find_and_clear8(chunk, pidx);
}


----------------------------
***/


inline static bool mi_bchunk_try_find_and_clear_at(mi_bchunk_t *chunk, size_t chunk_idx, size_t *pidx)
{
  (chunk_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("chunk_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 578, __func__));
  const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[chunk_idx], memory_order_acquire);
  size_t idx;
  if (mi_bfield_find_least_bit(b, &idx))
  {
    if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[chunk_idx], mi_bfield_mask(1, idx), b, 0)), 1))
    {
      *pidx = (chunk_idx * (1 << (3 + 3))) + idx;
      ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 586, __func__));
      return 1;
    }
  }
  return 0;
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static bool mi_bfield_atomic_try_clear_mask_of(_Atomic mi_bfield_t *b, mi_bfield_t mask, mi_bfield_t expect, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 169, __func__));
  do
  {
    if ((expect & mask) != mask)
    {
      if (all_clear != 0)
      {
        *all_clear = expect == 0;
      }
      return 0;
    }
  }
  while (!atomic_compare_exchange_weak_explicit(b, &expect, expect & (~mask), memory_order_acq_rel, memory_order_acquire));
  if (all_clear != 0)
  {
    *all_clear = (expect & (~mask)) == 0;
  }
  return 1;
}


----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bchunk_try_find_and_clear(mi_bchunk_t *chunk, size_t *pidx)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (mi_bchunk_try_find_and_clear_at(chunk, i, pidx))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static bool mi_bchunk_try_find_and_clear_at(mi_bchunk_t *chunk, size_t chunk_idx, size_t *pidx)
{
  (chunk_idx < ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("chunk_idx < MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 578, __func__));
  const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[chunk_idx], memory_order_acquire);
  size_t idx;
  if (mi_bfield_find_least_bit(b, &idx))
  {
    if (__builtin_expect(!(!mi_bfield_atomic_try_clear_mask_of(&chunk->bfields[chunk_idx], mi_bfield_mask(1, idx), b, 0)), 1))
    {
      *pidx = (chunk_idx * (1 << (3 + 3))) + idx;
      ((*pidx) < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("*pidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 586, __func__));
      return 1;
    }
  }
  return 0;
}


----------------------------
***/


inline static bool mi_bchunk_try_find_and_clear_1(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  (n == 1) ? ((void) 0) : (_mi_assert_fail("n==1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 676, __func__));
  (void) n;
  return mi_bchunk_try_find_and_clear(chunk, pidx);
}


/*** DEPENDENCIES:
inline static bool mi_bchunk_try_find_and_clear(mi_bchunk_t *chunk, size_t *pidx)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (mi_bchunk_try_find_and_clear_at(chunk, i, pidx))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
None
----------------------------
***/


bool mi_bbitmap_try_find_and_clear(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx)
{
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, 1, pidx, &mi_bchunk_try_find_and_clear_1);
}


/*** DEPENDENCIES:
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
inline static bool mi_bbitmap_try_find_and_clear_generic(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx, mi_bchunk_try_find_and_clear_fun_t *on_find)
{
  const size_t cmap_max_count = _mi_divide_up(mi_bbitmap_chunk_count(bbitmap), 1 << (3 + 3));
  const size_t chunk_acc = atomic_load_explicit(&bbitmap->chunk_max_accessed, memory_order_relaxed);
  const size_t cmap_acc = chunk_acc / (1 << (3 + 3));
  const size_t cmap_acc_bits = 1 + (chunk_acc % (1 << (3 + 3)));
  ((1 << (3 + 3)) >= ((1 << (6 + 3)) / (1 << (3 + 3)))) ? ((void) 0) : (_mi_assert_fail("MI_BFIELD_BITS >= MI_BCHUNK_FIELDS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1639, __func__));
  const mi_bfield_t cmap_mask = mi_bfield_mask(cmap_max_count, 0);
  const size_t cmap_cycle = cmap_acc + 1;
  const mi_chunkbin_t bbin = mi_chunkbin_of(n);
  size_t cmap_idx = 0;
  {
    helper_mi_bbitmap_try_find_and_clear_generic_1(bbitmap, tseq, n, pidx, cmap_acc, cmap_acc_bits, cmap_mask, cmap_cycle, bbin, cmap_idx);
  }
  ;
  return 0;
}


----------------------------
inline static bool mi_bchunk_try_find_and_clear_1(mi_bchunk_t *chunk, size_t n, size_t *pidx)
{
  (n == 1) ? ((void) 0) : (_mi_assert_fail("n==1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 676, __func__));
  (void) n;
  return mi_bchunk_try_find_and_clear(chunk, pidx);
}


----------------------------
***/


static bool mi_bitmap_try_find_and_claim_visit(mi_bitmap_t *bitmap, size_t chunk_idx, size_t n, size_t *pidx, void *arg1, void *arg2)
{
  (n == 1) ? ((void) 0) : (_mi_assert_fail("n==1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1289, __func__));
  (void) n;
  mi_claim_fun_t *claim_fun = (mi_claim_fun_t *) arg1;
  mi_claim_fun_data_t *claim_data = (mi_claim_fun_data_t *) arg2;
  size_t cidx;
  if (__builtin_expect(!(!mi_bchunk_try_find_and_clear(&bitmap->chunks[chunk_idx], &cidx)), 1))
  {
    const size_t slice_index = (chunk_idx * (1 << (6 + 3))) + cidx;
    (slice_index < mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("slice_index < mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1295, __func__));
    bool keep_set = 1;
    if ((*claim_fun)(slice_index, claim_data->arena, claim_data->heap_tag, &keep_set))
    {
      (!keep_set) ? ((void) 0) : (_mi_assert_fail("!keep_set", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1299, __func__));
      *pidx = slice_index;
      return 1;
    }
    else
    {
      if (keep_set)
      {
        const bool wasclear = mi_bchunk_set(&bitmap->chunks[chunk_idx], cidx, 0);
        (wasclear) ? ((void) 0) : (_mi_assert_fail("wasclear", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1307, __func__));
        (void) wasclear;
      }
    }
  }
  else
  {
    mi_bitmap_chunkmap_try_clear(bitmap, chunk_idx);
  }
  return 0;
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}


----------------------------
typedef bool mi_claim_fun_t(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_set)
----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
static bool mi_bitmap_chunkmap_try_clear(mi_bitmap_t *bitmap, size_t chunk_idx)
{
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1021, __func__));
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    return 0;
  }
  mi_bchunk_clear(&bitmap->chunkmap, chunk_idx, 0);
  if (!mi_bchunk_all_are_clear_relaxed(&bitmap->chunks[chunk_idx]))
  {
    mi_bchunk_set(&bitmap->chunkmap, chunk_idx, 0);
    return 0;
  }
  return 1;
}


----------------------------
inline static bool mi_bchunk_set(mi_bchunk_t *chunk, size_t cidx, size_t *already_set)
{
  (cidx < (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 274, __func__));
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  const bool was_clear = mi_bfield_atomic_set(&chunk->bfields[i], idx);
  if (already_set != 0)
  {
    *already_set = (was_clear) ? (0) : (1);
  }
  return was_clear;
}


----------------------------
typedef struct mi_claim_fun_data_s
{
  mi_arena_t *arena;
  mi_heaptag_t heap_tag;
} mi_claim_fun_data_t
----------------------------
inline static bool mi_bchunk_try_find_and_clear(mi_bchunk_t *chunk, size_t *pidx)
{
  for (int i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    if (mi_bchunk_try_find_and_clear_at(chunk, i, pidx))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


inline static bool mi_bfield_find_highest_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsr(x, idx);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}


----------------------------
***/


bool helper_mi_bitmap_find_1(mi_bitmap_t * const bitmap, size_t tseq, size_t n, size_t * const pidx, void * const arg1, void * const arg2, size_t i)
{
  const mi_bfield_t cmap_entry = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
  size_t hi;
  if (mi_bfield_find_highest_bit(cmap_entry, &hi))
  {
    size_t eidx = 0;
    {
      const size_t _startY = ((uint32_t) (tseq % 8)) % ((uint32_t) (hi + 1));
      {
        (_startY <= (hi + 1)) ? ((void) 0) : (_mi_assert_fail("_startY <= hi+1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        (_startY < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startY < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        ((hi + 1) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("hi+1 <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        mi_bfield_t _cycle_maskY = mi_bfield_mask((hi + 1) - _startY, _startY);
        size_t _bcountY = mi_bfield_popcount(cmap_entry);
        mi_bfield_t _bY = cmap_entry & _cycle_maskY;
        while (_bcountY > 0)
        {
          _bcountY -= 1;
          if (_bY == 0)
          {
            _bY = cmap_entry & (~_cycle_maskY);
          }
          bool _foundY = mi_bfield_find_least_bit(_bY, &eidx);
          (_foundY) ? ((void) 0) : (_mi_assert_fail("_foundY", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
          (void) _foundY;
          {
            {
              (eidx <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("eidx <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1263, __func__));
              const size_t chunk_idx = (i * (1 << (3 + 3))) + eidx;
              (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1265, __func__));
              if ((*on_find)(bitmap, chunk_idx, n, pidx, arg1, arg2))
              {
                return 1;
              }
            }
          }
          _bY = mi_bfield_clear_least_bit(_bY);
        }

      }
      ;
    }
    ;
  }
}


/*** DEPENDENCIES:
inline static mi_bfield_t mi_bfield_mask(size_t bit_count, size_t shiftl)
{
  (bit_count > 0) ? ((void) 0) : (_mi_assert_fail("bit_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 78, __func__));
  ((bit_count + shiftl) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_count + shiftl <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 79, __func__));
  const mi_bfield_t mask0 = (bit_count < (1 << (3 + 3))) ? ((mi_bfield_one() << bit_count) - 1) : (mi_bfield_all_set());
  return mask0 << shiftl;
}


----------------------------
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
inline static mi_bfield_t mi_bfield_clear_least_bit(mi_bfield_t x)
{
  return x & (x - 1);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bfield_find_highest_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsr(x, idx);
}


----------------------------
inline static bool mi_bfield_find_least_bit(mi_bfield_t x, size_t *idx)
{
  return mi_bsf(x, idx);
}


----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


inline static bool mi_bitmap_find(mi_bitmap_t *bitmap, size_t tseq, size_t n, size_t *pidx, mi_bitmap_visit_fun_t *on_find, void *arg1, void *arg2)
{
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = 0; i < chunkmap_max; i += 1)
  {
    helper_mi_bitmap_find_1(bitmap, tseq, n, pidx, arg1, arg2, i);
  }

  return 0;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
bool helper_mi_bitmap_find_1(mi_bitmap_t * const bitmap, size_t tseq, size_t n, size_t * const pidx, void * const arg1, void * const arg2, size_t i)
{
  const mi_bfield_t cmap_entry = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
  size_t hi;
  if (mi_bfield_find_highest_bit(cmap_entry, &hi))
  {
    size_t eidx = 0;
    {
      const size_t _startY = ((uint32_t) (tseq % 8)) % ((uint32_t) (hi + 1));
      {
        (_startY <= (hi + 1)) ? ((void) 0) : (_mi_assert_fail("_startY <= hi+1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        (_startY < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("_startY < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        ((hi + 1) <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("hi+1 <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
        mi_bfield_t _cycle_maskY = mi_bfield_mask((hi + 1) - _startY, _startY);
        size_t _bcountY = mi_bfield_popcount(cmap_entry);
        mi_bfield_t _bY = cmap_entry & _cycle_maskY;
        while (_bcountY > 0)
        {
          _bcountY -= 1;
          if (_bY == 0)
          {
            _bY = cmap_entry & (~_cycle_maskY);
          }
          bool _foundY = mi_bfield_find_least_bit(_bY, &eidx);
          (_foundY) ? ((void) 0) : (_mi_assert_fail("_foundY", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1261, __func__));
          (void) _foundY;
          {
            {
              (eidx <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("eidx <= MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1263, __func__));
              const size_t chunk_idx = (i * (1 << (3 + 3))) + eidx;
              (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1265, __func__));
              if ((*on_find)(bitmap, chunk_idx, n, pidx, arg1, arg2))
              {
                return 1;
              }
            }
          }
          _bY = mi_bfield_clear_least_bit(_bY);
        }

      }
      ;
    }
    ;
  }
}


----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
typedef bool mi_bitmap_visit_fun_t(mi_bitmap_t *bitmap, size_t chunk_idx, size_t n, size_t *idx, void *arg1, void *arg2)
----------------------------
***/


bool mi_bitmap_try_find_and_claim(mi_bitmap_t *bitmap, size_t tseq, size_t *pidx, mi_claim_fun_t *claim, mi_arena_t *arena, mi_heaptag_t heap_tag)
{
  mi_claim_fun_data_t claim_data = {arena, heap_tag};
  return mi_bitmap_find(bitmap, tseq, 1, pidx, &mi_bitmap_try_find_and_claim_visit, (void *) claim, &claim_data);
}


/*** DEPENDENCIES:
typedef uint8_t mi_heaptag_t
----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
typedef bool mi_claim_fun_t(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_set)
----------------------------
typedef struct mi_claim_fun_data_s
{
  mi_arena_t *arena;
  mi_heaptag_t heap_tag;
} mi_claim_fun_data_t
----------------------------
inline static bool mi_bitmap_find(mi_bitmap_t *bitmap, size_t tseq, size_t n, size_t *pidx, mi_bitmap_visit_fun_t *on_find, void *arg1, void *arg2)
{
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = 0; i < chunkmap_max; i += 1)
  {
    helper_mi_bitmap_find_1(bitmap, tseq, n, pidx, arg1, arg2, i);
  }

  return 0;
}


----------------------------
static bool mi_bitmap_try_find_and_claim_visit(mi_bitmap_t *bitmap, size_t chunk_idx, size_t n, size_t *pidx, void *arg1, void *arg2)
{
  (n == 1) ? ((void) 0) : (_mi_assert_fail("n==1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1289, __func__));
  (void) n;
  mi_claim_fun_t *claim_fun = (mi_claim_fun_t *) arg1;
  mi_claim_fun_data_t *claim_data = (mi_claim_fun_data_t *) arg2;
  size_t cidx;
  if (__builtin_expect(!(!mi_bchunk_try_find_and_clear(&bitmap->chunks[chunk_idx], &cidx)), 1))
  {
    const size_t slice_index = (chunk_idx * (1 << (6 + 3))) + cidx;
    (slice_index < mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("slice_index < mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1295, __func__));
    bool keep_set = 1;
    if ((*claim_fun)(slice_index, claim_data->arena, claim_data->heap_tag, &keep_set))
    {
      (!keep_set) ? ((void) 0) : (_mi_assert_fail("!keep_set", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1299, __func__));
      *pidx = slice_index;
      return 1;
    }
    else
    {
      if (keep_set)
      {
        const bool wasclear = mi_bchunk_set(&bitmap->chunks[chunk_idx], cidx, 0);
        (wasclear) ? ((void) 0) : (_mi_assert_fail("wasclear", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1307, __func__));
        (void) wasclear;
      }
    }
  }
  else
  {
    mi_bitmap_chunkmap_try_clear(bitmap, chunk_idx);
  }
  return 0;
}


----------------------------
None
----------------------------
***/


static bool mi_bchunk_bsr(mi_bchunk_t *chunk, size_t *pidx)
{
  for (size_t i = (1 << (6 + 3)) / (1 << (3 + 3)); i > 0;)
  {
    i -= 1;
    mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
    size_t idx;
    if (mi_bsr(b, &idx))
    {
      *pidx = (i * (1 << (3 + 3))) + idx;
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}


----------------------------
***/


bool mi_bitmap_bsr(mi_bitmap_t *bitmap, size_t *idx)
{
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = chunkmap_max; i > 0;)
  {
    i -= 1;
    mi_bfield_t cmap = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
    size_t cmap_idx;
    if (mi_bsr(cmap, &cmap_idx))
    {
      const size_t chunk_idx = (i * (1 << (3 + 3))) + cmap_idx;
      size_t cidx;
      if (mi_bchunk_bsr(&bitmap->chunks[chunk_idx], &cidx))
      {
        *idx = (chunk_idx * (1 << (6 + 3))) + cidx;
        return 1;
      }
    }
  }

  return 0;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
static bool mi_bchunk_bsr(mi_bchunk_t *chunk, size_t *pidx)
{
  for (size_t i = (1 << (6 + 3)) / (1 << (3 + 3)); i > 0;)
  {
    i -= 1;
    mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
    size_t idx;
    if (mi_bsr(b, &idx))
    {
      *pidx = (i * (1 << (3 + 3))) + idx;
      return 1;
    }
  }

  return 0;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}


----------------------------
***/


mi_chunkbin_t mi_bbitmap_debug_get_bin(const mi_bchunkmap_t *chunkmap_bins, size_t chunk_idx)
{
  for (mi_chunkbin_t ibin = MI_CBIN_SMALL; ibin < MI_CBIN_NONE; ibin = mi_chunkbin_inc(ibin))
  {
    if (mi_bchunk_is_xsetN(1, &chunkmap_bins[ibin], chunk_idx, 1))
    {
      return ibin;
    }
  }

  return MI_CBIN_NONE;
}


/*** DEPENDENCIES:
inline static bool mi_bchunk_is_xsetN(mi_xset_t set, const mi_bchunk_t *chunk, size_t cidx, size_t n)
{
  ((cidx + n) <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("cidx + n <= MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 432, __func__));
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 433, __func__));
  if (n == 0)
  {
    return 1;
  }
  const size_t i = cidx / (1 << (3 + 3));
  const size_t idx = cidx % (1 << (3 + 3));
  if (n == 1)
  {
    return mi_bfield_atomic_is_xset(set, &chunk->bfields[i], idx);
  }
  if ((idx + n) <= (1 << (3 + 3)))
  {
    return mi_bfield_atomic_is_xset_mask(set, &chunk->bfields[i], mi_bfield_mask(n, idx));
  }
  return mi_bchunk_is_xsetN_(set, chunk, i, idx, n);
}


----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}


----------------------------
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t
----------------------------
***/


bool _mi_bitmap_forall_set(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg)
{
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = 0; i < chunkmap_max; i += 1)
  {
    mi_bfield_t cmap_entry = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
    size_t cmap_idx;
    while (mi_bfield_foreach_bit(&cmap_entry, &cmap_idx))
    {
      const size_t chunk_idx = (i * (1 << (3 + 3))) + cmap_idx;
      mi_bchunk_t * const chunk = &bitmap->chunks[chunk_idx];
      for (size_t j = 0; j < ((1 << (6 + 3)) / (1 << (3 + 3))); j += 1)
      {
        const size_t base_idx = (chunk_idx * (1 << (6 + 3))) + (j * (1 << (3 + 3)));
        mi_bfield_t b = atomic_load_explicit(&chunk->bfields[j], memory_order_relaxed);
        size_t bidx;
        while (mi_bfield_foreach_bit(&b, &bidx))
        {
          const size_t idx = base_idx + bidx;
          if (!visit(idx, 1, arena, arg))
          {
            return 0;
          }
        }

      }

    }

  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
inline static bool mi_bfield_foreach_bit(mi_bfield_t *x, size_t *idx)
{
  const bool found = mi_bfield_find_least_bit(*x, idx);
  *x = mi_bfield_clear_least_bit(*x);
  return found;
}


----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef size_t mi_bfield_t
----------------------------
typedef bool mi_forall_set_fun_t(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg2)
----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
None
----------------------------
***/


inline static bool mi_bfield_atomic_try_clear8(_Atomic mi_bfield_t *b, size_t idx, bool *all_clear)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 199, __func__));
  ((idx % 8) == 0) ? ((void) 0) : (_mi_assert_fail("(idx%8)==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 200, __func__));
  const mi_bfield_t mask = ((mi_bfield_t) 0xFF) << idx;
  return mi_bfield_atomic_try_clear_mask(b, mask, all_clear);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bfield_atomic_try_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 182, __func__));
  const mi_bfield_t expect = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_atomic_try_clear_mask_of(b, mask, expect, all_clear);
}


----------------------------
None
----------------------------
***/


static size_t mi_bchunk_popcount(mi_bchunk_t *chunk)
{
  size_t popcount = 0;
  for (size_t i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
    popcount += mi_bfield_popcount(b);
  }

  return popcount;
}


/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static size_t mi_bfield_popcount(mi_bfield_t x)
{
  return mi_popcount(x);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
***/


inline static bool mi_bfield_atomic_try_clear(_Atomic mi_bfield_t *b, size_t idx, bool *all_clear)
{
  (idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 191, __func__));
  const mi_bfield_t mask = mi_bfield_one() << idx;
  return mi_bfield_atomic_try_clear_mask(b, mask, all_clear);
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
inline static bool mi_bfield_atomic_try_clear_mask(_Atomic mi_bfield_t *b, mi_bfield_t mask, bool *all_clear)
{
  (mask != 0) ? ((void) 0) : (_mi_assert_fail("mask != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 182, __func__));
  const mi_bfield_t expect = atomic_load_explicit(b, memory_order_relaxed);
  return mi_bfield_atomic_try_clear_mask_of(b, mask, expect, all_clear);
}


----------------------------
inline static mi_bfield_t mi_bfield_one(void)
{
  return 1;
}


----------------------------
None
----------------------------
***/


size_t mi_bitmap_popcount(mi_bitmap_t *bitmap)
{
  size_t popcount = 0;
  const size_t chunkmap_max = _mi_divide_up(mi_bitmap_chunk_count(bitmap), 1 << (3 + 3));
  for (size_t i = 0; i < chunkmap_max; i += 1)
  {
    mi_bfield_t cmap_entry = atomic_load_explicit(&bitmap->chunkmap.bfields[i], memory_order_relaxed);
    size_t cmap_idx;
    while (mi_bfield_foreach_bit(&cmap_entry, &cmap_idx))
    {
      const size_t chunk_idx = (i * (1 << (3 + 3))) + cmap_idx;
      popcount += mi_bchunk_popcount(&bitmap->chunks[chunk_idx]);
    }

  }

  return popcount;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
static size_t mi_bchunk_popcount(mi_bchunk_t *chunk)
{
  size_t popcount = 0;
  for (size_t i = 0; i < ((1 << (6 + 3)) / (1 << (3 + 3))); i += 1)
  {
    const mi_bfield_t b = atomic_load_explicit(&chunk->bfields[i], memory_order_relaxed);
    popcount += mi_bfield_popcount(b);
  }

  return popcount;
}


----------------------------
inline static bool mi_bfield_foreach_bit(mi_bfield_t *x, size_t *idx)
{
  const bool found = mi_bfield_find_least_bit(*x, idx);
  *x = mi_bfield_clear_least_bit(*x);
  return found;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
***/


