void *mi_expand(void *p, size_t newsize)
{
  (void) p;
  (void) newsize;
  return 0;
}


/*** DEPENDENCIES:
***/


inline static void mi_atomic_yield(void)
{
}


/*** DEPENDENCIES:
***/


inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add)
{
  return (intptr_t) atomic_fetch_add_explicit((uintptr_t *) p, (uintptr_t) add, memory_order_acq_rel);
}


/*** DEPENDENCIES:
***/


inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}


/*** DEPENDENCIES:
***/


inline static void mi_atomic_void_addi64_relaxed(volatile int64_t *p, const volatile int64_t *padd)
{
  const int64_t add = atomic_load_explicit((int64_t *) padd, memory_order_relaxed);
  if (add != 0)
  {
    atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
  }
}


/*** DEPENDENCIES:
***/


inline static void mi_atomic_maxi64_relaxed(volatile int64_t *p, int64_t x)
{
  int64_t current = atomic_load_explicit((int64_t *) p, memory_order_relaxed);
  while ((current < x) && (!atomic_compare_exchange_weak_explicit((int64_t *) p, &current, x, memory_order_release, memory_order_relaxed)))
  {
  }

  ;
}


/*** DEPENDENCIES:
***/


inline static bool mi_lock_try_acquire(pthread_mutex_t *lock)
{
  return pthread_mutex_trylock(lock) == 0;
}


/*** DEPENDENCIES:
***/


inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


/*** DEPENDENCIES:
***/


inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}


/*** DEPENDENCIES:
***/


inline static void mi_lock_done(pthread_mutex_t *lock)
{
  pthread_mutex_destroy(lock);
}


/*** DEPENDENCIES:
***/


inline static uintptr_t _mi_random_shuffle(uintptr_t x)
{
  if (x == 0)
  {
    x = 17;
  }
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
  return x;
}


/*** DEPENDENCIES:
***/


inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


/*** DEPENDENCIES:
***/


inline static size_t _mi_clamp(size_t sz, size_t min, size_t max)
{
  if (sz < min)
  {
    return min;
  }
  else
    if (sz > max)
  {
    return max;
  }
  else
    return sz;
}


/*** DEPENDENCIES:
***/


inline static bool mi_mem_is_zero(const void *p, size_t size)
{
  for (size_t i = 0; i < size; i += 1)
  {
    if (((uint8_t *) p)[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
***/


inline static bool mi_mul_overflow(size_t count, size_t size, size_t *total)
{
  return __builtin_umulll_overflow(count, size, (unsigned long long *) total);
}


/*** DEPENDENCIES:
***/


inline static uintptr_t mi_rotl(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x << shift) | (x >> (((1 << 3) * 8) - shift)));
}


/*** DEPENDENCIES:
***/


inline static uintptr_t mi_rotr(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x >> shift) | (x << (((1 << 3) * 8) - shift)));
}


/*** DEPENDENCIES:
***/


inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}


/*** DEPENDENCIES:
***/


inline static size_t mi_ctz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_ctzll(x);
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


/*** DEPENDENCIES:
***/


inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


/*** DEPENDENCIES:
***/


inline static mi_threadid_t _mi_prim_thread_id(void)
{
  return (uintptr_t) __builtin_thread_pointer();
}


/*** DEPENDENCIES:
***/


inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static mi_slice_t *mi_slice_first(const mi_slice_t *slice)
{
  mi_slice_t *start = (mi_slice_t *) (((uint8_t *) slice) - slice->slice_offset);
  (start >= _mi_ptr_segment(slice)->slices) ? ((void) 0) : (_mi_assert_fail("start >= _mi_ptr_segment(slice)->slices", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 556, __func__));
  (start->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("start->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 557, __func__));
  ((start + start->slice_count) > slice) ? ((void) 0) : (_mi_assert_fail("start + start->slice_count > slice", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 558, __func__));
  return start;
}


/*** DEPENDENCIES:
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
typedef mi_page_t mi_slice_t
----------------------------
None
----------------------------
***/


inline static mi_page_t *mi_slice_to_page(mi_slice_t *s)
{
  ((s->slice_offset == 0) && (s->slice_count > 0)) ? ((void) 0) : (_mi_assert_fail("s->slice_offset== 0 && s->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 537, __func__));
  return (mi_page_t *) s;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
typedef mi_page_t mi_slice_t
----------------------------
None
----------------------------
***/


inline static mi_page_t *_mi_segment_page_of(const mi_segment_t *segment, const void *p)
{
  (p > ((void *) segment)) ? ((void) 0) : (_mi_assert_fail("p > (void*)segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 564, __func__));
  ptrdiff_t diff = ((uint8_t *) p) - ((uint8_t *) segment);
  ((diff > 0) && (diff <= ((ptrdiff_t) (1UL << (9 + (13 + 3)))))) ? ((void) 0) : (_mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 566, __func__));
  size_t idx = ((size_t) diff) >> (13 + 3);
  (idx <= segment->slice_entries) ? ((void) 0) : (_mi_assert_fail("idx <= segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 568, __func__));
  mi_slice_t *slice0 = (mi_slice_t *) (&segment->slices[idx]);
  mi_slice_t *slice = mi_slice_first(slice0);
  (slice->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("slice->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 571, __func__));
  ((slice >= segment->slices) && (slice < (segment->slices + segment->slice_entries))) ? ((void) 0) : (_mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 572, __func__));
  return mi_slice_to_page(slice);
}


/*** DEPENDENCIES:
inline static mi_page_t *mi_slice_to_page(mi_slice_t *s)
{
  ((s->slice_offset == 0) && (s->slice_count > 0)) ? ((void) 0) : (_mi_assert_fail("s->slice_offset== 0 && s->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 537, __func__));
  return (mi_page_t *) s;
}


----------------------------
typedef mi_page_t mi_slice_t
----------------------------
inline static mi_slice_t *mi_slice_first(const mi_slice_t *slice)
{
  mi_slice_t *start = (mi_slice_t *) (((uint8_t *) slice) - slice->slice_offset);
  (start >= _mi_ptr_segment(slice)->slices) ? ((void) 0) : (_mi_assert_fail("start >= _mi_ptr_segment(slice)->slices", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 556, __func__));
  (start->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("start->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 557, __func__));
  ((start + start->slice_count) > slice) ? ((void) 0) : (_mi_assert_fail("start + start->slice_count > slice", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 558, __func__));
  return start;
}


----------------------------
None
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 59, __func__));
  size_t diff = ((uint8_t *) p) - page->page_start;
  size_t adjust;
  if (__builtin_expect(!(!(page->block_size_shift != 0)), 1))
  {
    adjust = diff & ((((size_t) 1) << page->block_size_shift) - 1);
  }
  else
  {
    adjust = diff % mi_page_block_size(page);
  }
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


inline static mi_encoded_t mi_ptr_encode(const void *null, const void *p, const uintptr_t *keys)
{
  uintptr_t x = (uintptr_t) ((p == 0) ? (null) : (p));
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}


/*** DEPENDENCIES:
inline static uintptr_t mi_rotl(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x << shift) | (x >> (((1 << 3) * 8) - shift)));
}


----------------------------
***/


inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}


/*** DEPENDENCIES:
inline static mi_encoded_t mi_ptr_encode(const void *null, const void *p, const uintptr_t *keys)
{
  uintptr_t x = (uintptr_t) ((p == 0) ? (null) : (p));
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}


----------------------------
***/


inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}


----------------------------
***/


static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  return (ok) ? (bsize - delta) : (0);
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}


----------------------------
None
----------------------------
***/


static size_t mi_page_usable_aligned_size_of(const mi_page_t *page, const void *p)
{
  const mi_block_t *block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = ((uint8_t *) p) - ((uint8_t *) block);
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 315, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  return (ok) ? (bsize - delta) : (0);
}


----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 59, __func__));
  size_t diff = ((uint8_t *) p) - page->page_start;
  size_t adjust;
  if (__builtin_expect(!(!(page->block_size_shift != 0)), 1))
  {
    adjust = diff & ((((size_t) 1) << page->block_size_shift) - 1);
  }
  else
  {
    adjust = diff % mi_page_block_size(page);
  }
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
None
----------------------------
***/


inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}


/*** DEPENDENCIES:
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t
----------------------------
***/


inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 386, __func__));
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


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void *mi_align_up_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_up((uintptr_t) p, alignment);
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 386, __func__));
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
***/


inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 398, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return sz & (~mask);
  }
  else
  {
    return (sz / alignment) * alignment;
  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 398, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return sz & (~mask);
  }
  else
  {
    return (sz / alignment) * alignment;
  }
}


----------------------------
***/


inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1135, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memzero(adst, n);
}


/*** DEPENDENCIES:
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
None
----------------------------
***/


inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}


/*** DEPENDENCIES:
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t
----------------------------
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t
----------------------------
***/


inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


/*** DEPENDENCIES:
inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}


----------------------------
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t
----------------------------
***/


inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 380, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static mi_memid_t _mi_memid_create_os(void *base, size_t size, bool committed, bool is_zero, bool is_large)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_OS);
  memid.mem.os.base = base;
  memid.mem.os.size = size;
  memid.initially_committed = committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_large;
  return memid;
}


/*** DEPENDENCIES:
inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}


----------------------------
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t
----------------------------
***/


inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


inline static mi_segment_t *mi_checked_ptr_segment(const void *p, const char *msg)
{
  (void) msg;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_segment_t * const segment = _mi_ptr_segment(p);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return segment;
  }
  if (__builtin_expect(!(!(!mi_is_in_heap_region(p))), 0))
  {
    if ((((uintptr_t) p) >> 40) != 0x7F)
    {
      _mi_warning_message("%s: pointer might not point to a valid heap region: %p\n(this may still be a valid very large allocation (over 64MiB))\n", msg, p);
      if (__builtin_expect(!(!(_mi_ptr_cookie(segment) == segment->cookie)), 1))
      {
        _mi_warning_message("(yes, the previous pointer %p was valid after all)\n", p);
      }
    }
  }
  if (__builtin_expect(!(!(_mi_ptr_cookie(segment) != segment->cookie)), 0))
  {
    _mi_error_message(22, "%s: pointer does not point to a valid heap space: %p\n", msg, p);
    return 0;
  }
  return segment;
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
}


----------------------------
bool mi_is_in_heap_region(const void *p)
{
  return mi_is_valid_pointer(p);
}


----------------------------
None
----------------------------
None
----------------------------
***/


inline static bool mi_page_has_aligned(const mi_page_t *page)
{
  return page->flags.x.has_aligned;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}


/*** DEPENDENCIES:
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  return (ok) ? (bsize - delta) : (0);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static bool mi_page_has_aligned(const mi_page_t *page)
{
  return page->flags.x.has_aligned;
}


----------------------------
inline static mi_segment_t *mi_checked_ptr_segment(const void *p, const char *msg)
{
  (void) msg;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_segment_t * const segment = _mi_ptr_segment(p);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return segment;
  }
  if (__builtin_expect(!(!(!mi_is_in_heap_region(p))), 0))
  {
    if ((((uintptr_t) p) >> 40) != 0x7F)
    {
      _mi_warning_message("%s: pointer might not point to a valid heap region: %p\n(this may still be a valid very large allocation (over 64MiB))\n", msg, p);
      if (__builtin_expect(!(!(_mi_ptr_cookie(segment) == segment->cookie)), 1))
      {
        _mi_warning_message("(yes, the previous pointer %p was valid after all)\n", p);
      }
    }
  }
  if (__builtin_expect(!(!(_mi_ptr_cookie(segment) != segment->cookie)), 0))
  {
    _mi_error_message(22, "%s: pointer does not point to a valid heap space: %p\n", msg, p);
    return 0;
  }
  return segment;
}


----------------------------
static size_t mi_page_usable_aligned_size_of(const mi_page_t *page, const void *p)
{
  const mi_block_t *block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = ((uint8_t *) p) - ((uint8_t *) block);
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 315, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
}


----------------------------
inline static mi_page_t *_mi_segment_page_of(const mi_segment_t *segment, const void *p)
{
  (p > ((void *) segment)) ? ((void) 0) : (_mi_assert_fail("p > (void*)segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 564, __func__));
  ptrdiff_t diff = ((uint8_t *) p) - ((uint8_t *) segment);
  ((diff > 0) && (diff <= ((ptrdiff_t) (1UL << (9 + (13 + 3)))))) ? ((void) 0) : (_mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 566, __func__));
  size_t idx = ((size_t) diff) >> (13 + 3);
  (idx <= segment->slice_entries) ? ((void) 0) : (_mi_assert_fail("idx <= segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 568, __func__));
  mi_slice_t *slice0 = (mi_slice_t *) (&segment->slices[idx]);
  mi_slice_t *slice = mi_slice_first(slice0);
  (slice->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("slice->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 571, __func__));
  ((slice >= segment->slices) && (slice < (segment->slices + segment->slice_entries))) ? ((void) 0) : (_mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 572, __func__));
  return mi_slice_to_page(slice);
}


----------------------------
None
----------------------------
***/


size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


/*** DEPENDENCIES:
inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}


----------------------------
***/


inline static intptr_t mi_atomic_subi(_Atomic intptr_t *p, intptr_t sub)
{
  return (intptr_t) mi_atomic_addi(p, -sub);
}


/*** DEPENDENCIES:
inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add)
{
  return (intptr_t) atomic_fetch_add_explicit((uintptr_t *) p, (uintptr_t) add, memory_order_acq_rel);
}


----------------------------
***/


inline static bool mi_atomic_once(mi_atomic_once_t *once)
{
  if (atomic_load_explicit(once, memory_order_relaxed) != 0)
  {
    return 0;
  }
  uintptr_t expected = 0;
  return atomic_compare_exchange_strong_explicit(once, &expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire);
}


/*** DEPENDENCIES:
typedef _Atomic uintptr_t mi_atomic_once_t
----------------------------
***/


inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
***/


inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 421, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 445, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t mi_segment_size(mi_segment_t *segment)
{
  return segment->segment_slices * (1UL << (13 + 3));
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_page_is_mostly_used(const mi_page_t *page)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used) <= frac;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static void mi_page_set_has_aligned(mi_page_t *page, bool has_aligned)
{
  page->flags.x.has_aligned = has_aligned;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static bool mi_is_in_same_segment(const void *p, const void *q)
{
  return _mi_ptr_segment(p) == _mi_ptr_segment(q);
}


/*** DEPENDENCIES:
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
***/


inline static void mi_commit_mask_create_empty(mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    cm->mask[i] = 0;
  }

}


/*** DEPENDENCIES:
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t
----------------------------
***/


inline static void mi_commit_mask_create_full(mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    cm->mask[i] = ~((size_t) 0);
  }

}


/*** DEPENDENCIES:
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t
----------------------------
***/


inline static bool mi_commit_mask_is_empty(const mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    if (cm->mask[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t
----------------------------
***/


inline static bool mi_commit_mask_is_full(const mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    if (cm->mask[i] != (~((size_t) 0)))
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t
----------------------------
***/


inline static size_t mi_bsr(size_t x)
{
  return (x == 0) ? ((1 << 3) * 8) : ((((1 << 3) * 8) - 1) - mi_clz(x));
}


/*** DEPENDENCIES:
inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}


----------------------------
***/


std_new_handler_t _ZSt15get_new_handlerv(void)
{
  return 0;
}


/*** DEPENDENCIES:
typedef void (*std_new_handler_t)(void)
----------------------------
***/


inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 516, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 518, __func__));
  return heap->pages_free_direct[idx];
}


/*** DEPENDENCIES:
None
----------------------------
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 445, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static mi_encoded_t mi_ptr_encode(const void *null, const void *p, const uintptr_t *keys)
{
  uintptr_t x = (uintptr_t) ((p == 0) ? (null) : (p));
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}


----------------------------
***/


inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


/*** DEPENDENCIES:
inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
}


/*** DEPENDENCIES:
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 631, __func__));
  atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
  if (heap != 0)
  {
    page->heap_tag = heap->tag;
  }
}


/*** DEPENDENCIES:
inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
}


----------------------------
None
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static mi_page_t *_mi_ptr_page(void *p)
{
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 585, __func__));
  return _mi_segment_page_of(_mi_ptr_segment(p), p);
}


/*** DEPENDENCIES:
inline static mi_page_t *_mi_segment_page_of(const mi_segment_t *segment, const void *p)
{
  (p > ((void *) segment)) ? ((void) 0) : (_mi_assert_fail("p > (void*)segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 564, __func__));
  ptrdiff_t diff = ((uint8_t *) p) - ((uint8_t *) segment);
  ((diff > 0) && (diff <= ((ptrdiff_t) (1UL << (9 + (13 + 3)))))) ? ((void) 0) : (_mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 566, __func__));
  size_t idx = ((size_t) diff) >> (13 + 3);
  (idx <= segment->slice_entries) ? ((void) 0) : (_mi_assert_fail("idx <= segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 568, __func__));
  mi_slice_t *slice0 = (mi_slice_t *) (&segment->slices[idx]);
  mi_slice_t *slice = mi_slice_first(slice0);
  (slice->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("slice->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 571, __func__));
  ((slice >= segment->slices) && (slice < (segment->slices + segment->slice_entries))) ? ((void) 0) : (_mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 572, __func__));
  return mi_slice_to_page(slice);
}


----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static mi_slice_t *mi_page_to_slice(mi_page_t *p)
{
  ((p->slice_offset == 0) && (p->slice_count > 0)) ? ((void) 0) : (_mi_assert_fail("p->slice_offset== 0 && p->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (mi_slice_t *) p;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
typedef mi_page_t mi_slice_t
----------------------------
None
----------------------------
***/


inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}


/*** DEPENDENCIES:
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
None
----------------------------
***/


inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1128, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}


/*** DEPENDENCIES:
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
None
----------------------------
***/


inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


/*** DEPENDENCIES:
None
----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
None
----------------------------
***/


inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


/*** DEPENDENCIES:
extern mi_heap_t *_mi_heap_default
----------------------------
None
----------------------------
***/


inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
***/


inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static bool mi_page_has_any_available(const mi_page_t *page)
{
  ((page != 0) && (page->reserved > 0)) ? ((void) 0) : (_mi_assert_fail("page != NULL && page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 662, __func__));
  return (page->used < page->reserved) || (mi_page_thread_free(page) != 0);
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
}


----------------------------
None
----------------------------
***/


inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
}


/*** DEPENDENCIES:
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


inline static mi_thread_free_t mi_tf_make(mi_block_t *block, mi_delayed_t delayed)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((uintptr_t) delayed));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
----------------------------
***/


inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~0x03));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


inline static mi_thread_free_t mi_tf_set_delayed(mi_thread_free_t tf, mi_delayed_t delayed)
{
  return mi_tf_make(mi_tf_block(tf), delayed);
}


/*** DEPENDENCIES:
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~0x03));
}


----------------------------
inline static mi_thread_free_t mi_tf_make(mi_block_t *block, mi_delayed_t delayed)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((uintptr_t) delayed));
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


inline static mi_delayed_t mi_tf_delayed(mi_thread_free_t tf)
{
  return (mi_delayed_t) (tf & 0x03);
}


/*** DEPENDENCIES:
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_segment_t *segment = _mi_ptr_segment(p);
  if (_mi_ptr_segment(q) != segment)
  {
    return 0;
  }
  mi_page_t *page = _mi_segment_page_of(segment, p);
  size_t psize;
  uint8_t *start = _mi_segment_page_start(segment, page, &psize);
  return (start <= ((uint8_t *) q)) && (((uint8_t *) q) < (start + psize));
}


/*** DEPENDENCIES:
inline static mi_page_t *_mi_segment_page_of(const mi_segment_t *segment, const void *p)
{
  (p > ((void *) segment)) ? ((void) 0) : (_mi_assert_fail("p > (void*)segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 564, __func__));
  ptrdiff_t diff = ((uint8_t *) p) - ((uint8_t *) segment);
  ((diff > 0) && (diff <= ((ptrdiff_t) (1UL << (9 + (13 + 3)))))) ? ((void) 0) : (_mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 566, __func__));
  size_t idx = ((size_t) diff) >> (13 + 3);
  (idx <= segment->slice_entries) ? ((void) 0) : (_mi_assert_fail("idx <= segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 568, __func__));
  mi_slice_t *slice0 = (mi_slice_t *) (&segment->slices[idx]);
  mi_slice_t *slice = mi_slice_first(slice0);
  (slice->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("slice->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 571, __func__));
  ((slice >= segment->slices) && (slice < (segment->slices + segment->slice_entries))) ? ((void) 0) : (_mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 572, __func__));
  return mi_slice_to_page(slice);
}


----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
uint8_t *_mi_segment_page_start(const mi_segment_t *segment, const mi_page_t *page, size_t *page_size)
{
  const mi_slice_t *slice = mi_page_to_slice((mi_page_t *) page);
  uint8_t *p = _mi_segment_page_start_from_slice(segment, slice, mi_page_block_size(page), page_size);
  ((mi_page_block_size(page) > 0) || (_mi_ptr_page(p) == page)) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 364, __func__));
  (_mi_ptr_segment(p) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(p) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 365, __func__));
  return p;
}


----------------------------
None
----------------------------
***/


inline static void *mi_ptr_decode(const void *null, const mi_encoded_t x, const uintptr_t *keys)
{
  void *p = (void *) (mi_rotr(x - keys[0], keys[0]) ^ keys[1]);
  return (p == null) ? (0) : (p);
}


/*** DEPENDENCIES:
typedef uintptr_t mi_encoded_t
----------------------------
inline static uintptr_t mi_rotr(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x >> shift) | (x << (((1 << 3) * 8) - shift)));
}


----------------------------
***/


inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static void *mi_ptr_decode(const void *null, const mi_encoded_t x, const uintptr_t *keys)
{
  void *p = (void *) (mi_rotr(x - keys[0], keys[0]) ^ keys[1]);
  return (p == null) ? (0) : (p);
}


----------------------------
***/


inline static mi_block_t *mi_block_next(const mi_page_t *page, const mi_block_t *block)
{
  mi_block_t *next = mi_block_nextx(page, block, page->keys);
  unsigned int next_idx = 0;
  if (__builtin_expect(!(!(((&next[next_idx]) != 0) && (!mi_is_in_same_page(block, next)))), 0))
  {
    _mi_error_message(14, "corrupted free list entry of size %zub at %p: value 0x%zx\n", mi_page_block_size(page), block, (uintptr_t) next);
    next_idx = 0;
  }
  return next;
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_segment_t *segment = _mi_ptr_segment(p);
  if (_mi_ptr_segment(q) != segment)
  {
    return 0;
  }
  mi_page_t *page = _mi_segment_page_of(segment, p);
  size_t psize;
  uint8_t *start = _mi_segment_page_start(segment, page, &psize);
  return (start <= ((uint8_t *) q)) && (((uint8_t *) q) < (start + psize));
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


inline static mi_thread_free_t mi_tf_set_block(mi_thread_free_t tf, mi_block_t *block)
{
  return mi_tf_make(block, mi_tf_delayed(tf));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static mi_delayed_t mi_tf_delayed(mi_thread_free_t tf)
{
  return (mi_delayed_t) (tf & 0x03);
}


----------------------------
inline static mi_thread_free_t mi_tf_make(mi_block_t *block, mi_delayed_t delayed)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((uintptr_t) delayed));
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


static void mi_free_generic_local(mi_page_t *page, mi_segment_t *segment, void *p)
{
  (void) segment;
  mi_block_t * const block = (mi_page_has_aligned(page)) ? (_mi_page_ptr_unalign(page, p)) : ((mi_block_t *) p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 59, __func__));
  size_t diff = ((uint8_t *) p) - page->page_start;
  size_t adjust;
  if (__builtin_expect(!(!(page->block_size_shift != 0)), 1))
  {
    adjust = diff & ((((size_t) 1) << page->block_size_shift) - 1);
  }
  else
  {
    adjust = diff % mi_page_block_size(page);
  }
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static bool mi_page_has_aligned(const mi_page_t *page)
{
  return page->flags.x.has_aligned;
}


----------------------------
inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}


----------------------------
None
----------------------------
***/


static bool mi_list_contains(const mi_page_t *page, const mi_block_t *list, const mi_block_t *elem)
{
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    if (elem == (&list[list_idx]))
    {
      return 1;
    }
    list_idx = mi_block_next(page, list_idx);
  }

  return 0;
}


/*** DEPENDENCIES:
inline static mi_block_t *mi_block_next(const mi_page_t *page, const mi_block_t *block)
{
  mi_block_t *next = mi_block_nextx(page, block, page->keys);
  unsigned int next_idx = 0;
  if (__builtin_expect(!(!(((&next[next_idx]) != 0) && (!mi_is_in_same_page(block, next)))), 0))
  {
    _mi_error_message(14, "corrupted free list entry of size %zub at %p: value 0x%zx\n", mi_page_block_size(page), block, (uintptr_t) next);
    next_idx = 0;
  }
  return next;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


static bool mi_check_is_double_freex(const mi_page_t *page, const mi_block_t *block)
{
  if ((mi_list_contains(page, page->free, block) || mi_list_contains(page, page->local_free, block)) || mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message(11, "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static bool mi_list_contains(const mi_page_t *page, const mi_block_t *list, const mi_block_t *elem)
{
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    if (elem == (&list[list_idx]))
    {
      return 1;
    }
    list_idx = mi_block_next(page, list_idx);
  }

  return 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
}


----------------------------
***/


inline static bool mi_check_is_double_free(const mi_page_t *page, const mi_block_t *block)
{
  bool is_double_free = 0;
  mi_block_t *n = mi_block_nextx(page, block, page->keys);
  if (((((uintptr_t) n) & ((1 << 3) - 1)) == 0) && ((n == 0) || mi_is_in_same_page(block, n)))
  {
    is_double_free = mi_check_is_double_freex(page, block);
  }
  return is_double_free;
}


/*** DEPENDENCIES:
inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static bool mi_check_is_double_freex(const mi_page_t *page, const mi_block_t *block)
{
  if ((mi_list_contains(page, page->free, block) || mi_list_contains(page, page->local_free, block)) || mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message(11, "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}


----------------------------
inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_segment_t *segment = _mi_ptr_segment(p);
  if (_mi_ptr_segment(q) != segment)
  {
    return 0;
  }
  mi_page_t *page = _mi_segment_page_of(segment, p);
  size_t psize;
  uint8_t *start = _mi_segment_page_start(segment, page, &psize);
  return (start <= ((uint8_t *) q)) && (((uint8_t *) q) < (start + psize));
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
***/


static bool mi_verify_padding(const mi_page_t *page, const mi_block_t *block, size_t *size, size_t *wrong)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = (*wrong = bsize);
  if (!ok)
  {
    return 0;
  }
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 489, __func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = (((uint8_t *) block) + bsize) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    ;
    for (size_t i = 0; i < maxpad; i += 1)
    {
      if (fill[i] != 0xDE)
      {
        *wrong = (bsize - delta) + i;
        ok = 0;
        break;
      }
    }

    ;
  }
  return ok;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}


----------------------------
None
----------------------------
***/


static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
static bool mi_verify_padding(const mi_page_t *page, const mi_block_t *block, size_t *size, size_t *wrong)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = (*wrong = bsize);
  if (!ok)
  {
    return 0;
  }
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 489, __func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = (((uint8_t *) block) + bsize) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    ;
    for (size_t i = 0; i < maxpad; i += 1)
    {
      if (fill[i] != 0xDE)
      {
        *wrong = (bsize - delta) + i;
        ok = 0;
        break;
      }
    }

    ;
  }
  return ok;
}


----------------------------
***/


void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 457, __func__));
  if ((!ok) || ((bsize - delta) >= min_size))
  {
    return;
  }
  (bsize >= min_size) ? ((void) 0) : (_mi_assert_fail("bsize >= min_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 459, __func__));
  if (bsize < min_size)
  {
    return;
  }
  size_t new_delta = bsize - min_size;
  (new_delta < bsize) ? ((void) 0) : (_mi_assert_fail("new_delta < bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 462, __func__));
  mi_padding_t *padding = (mi_padding_t *) (((uint8_t *) block) + bsize);
  ;
  padding->delta = (uint32_t) new_delta;
  ;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}


----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
None
----------------------------
***/


static void mi_free_block_delayed_mt(mi_page_t *page, mi_block_t *block)
{
  mi_thread_free_t tfreex;
  bool use_delayed;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    use_delayed = mi_tf_delayed(tfree) == MI_USE_DELAYED_FREE;
    if (__builtin_expect(!(!use_delayed), 0))
    {
      tfreex = mi_tf_set_delayed(tfree, MI_DELAYED_FREEING);
    }
    else
    {
      mi_block_set_next(page, block, mi_tf_block(tfree));
      tfreex = mi_tf_set_block(tfree, block);
    }
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed));
  if (__builtin_expect(!(!use_delayed), 0))
  {
    mi_heap_t * const heap = (mi_heap_t *) atomic_load_explicit(&page->xheap, memory_order_acquire);
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 232, __func__));
    if (heap != 0)
    {
      mi_block_t *dfree = atomic_load_explicit(&heap->thread_delayed_free, memory_order_relaxed);
      do
      {
        mi_block_set_nextx(heap, block, dfree, heap->keys);
      }
      while (!atomic_compare_exchange_weak_explicit(&heap->thread_delayed_free, &dfree, block, memory_order_release, memory_order_relaxed));
    }
    tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    do
    {
      tfreex = tfree;
      (mi_tf_delayed(tfree) == MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_tf_delayed(tfree) == MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 245, __func__));
      tfreex = mi_tf_set_delayed(tfree, MI_NO_DELAYED_FREE);
    }
    while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed));
  }
}


/*** DEPENDENCIES:
inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
}


----------------------------
inline static mi_delayed_t mi_tf_delayed(mi_thread_free_t tf)
{
  return (mi_delayed_t) (tf & 0x03);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
None
----------------------------
inline static mi_thread_free_t mi_tf_set_delayed(mi_thread_free_t tf, mi_delayed_t delayed)
{
  return mi_tf_make(mi_tf_block(tf), delayed);
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static mi_thread_free_t mi_tf_set_block(mi_thread_free_t tf, mi_block_t *block)
{
  return mi_tf_make(block, mi_tf_delayed(tf));
}


----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~0x03));
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
None
----------------------------
***/


inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 131, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 132, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->thread_id == 0) || (heap->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == tid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 135, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 149, __func__));
    ;
  }
  ;
  return p;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 516, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 518, __func__));
  return heap->pages_free_direct[idx];
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
None
----------------------------
***/


inline extern void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  if (__builtin_expect(!(!(size <= (128 * (sizeof(void *))))), 1))
  {
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 172, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 182, __func__));
    ((heap->thread_id == 0) || (heap->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 183, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 185, __func__));
      ;
    }
    ;
    return p;
  }
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 131, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 132, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->thread_id == 0) || (heap->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == tid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 135, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 149, __func__));
    ;
  }
  ;
  return p;
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
None
----------------------------
***/


inline extern void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}


/*** DEPENDENCIES:
inline extern void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  if (__builtin_expect(!(!(size <= (128 * (sizeof(void *))))), 1))
  {
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 172, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 182, __func__));
    ((heap->thread_id == 0) || (heap->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 183, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 185, __func__));
      ;
    }
    ;
    return p;
  }
}


----------------------------
None
----------------------------
***/


inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


/*** DEPENDENCIES:
inline extern void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}


----------------------------
None
----------------------------
***/


void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}


/*** DEPENDENCIES:
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
None
----------------------------
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
None
----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}


----------------------------
None
----------------------------
***/


void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}


/*** DEPENDENCIES:
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}


----------------------------
None
----------------------------
***/


inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
inline static bool mi_mul_overflow(size_t count, size_t size, size_t *total)
{
  return __builtin_umulll_overflow(count, size, (unsigned long long *) total);
}


----------------------------
***/


void *mi_heap_reallocn(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_realloc(heap, p, total);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}


----------------------------
None
----------------------------
***/


void *mi_reallocn(void *p, size_t count, size_t size)
{
  return mi_heap_reallocn(mi_prim_get_default_heap(), p, count, size);
}


/*** DEPENDENCIES:
void *mi_heap_reallocn(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_realloc(heap, p, total);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


extern void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 1);
}


/*** DEPENDENCIES:
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
None
----------------------------
None
----------------------------
***/


char *mi_heap_strdup(mi_heap_t *heap, const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = _mi_strlen(s);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
size_t _mi_strlen(const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while (s[len] != 0)
  {
    len += 1;
  }

  return len;
}


----------------------------
None
----------------------------
***/


char *mi_strdup(const char *s)
{
  return mi_heap_strdup(mi_prim_get_default_heap(), s);
}


/*** DEPENDENCIES:
char *mi_heap_strdup(mi_heap_t *heap, const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = _mi_strlen(s);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


inline extern void *mi_heap_zalloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 1);
}


/*** DEPENDENCIES:
inline extern void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}


----------------------------
None
----------------------------
***/


inline extern void *mi_heap_calloc(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc(heap, total);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
inline extern void *mi_heap_zalloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 1);
}


----------------------------
None
----------------------------
***/


void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


/*** DEPENDENCIES:
inline extern void *mi_heap_calloc(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc(heap, total);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}


/*** DEPENDENCIES:
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


char *mi_heap_strndup(mi_heap_t *heap, const char *s, size_t n)
{
  if (s == 0)
  {
    return 0;
  }
  const size_t len = _mi_strnlen(s, n);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
size_t _mi_strnlen(const char *s, size_t max_len)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while ((s[len] != 0) && (len < max_len))
  {
    len += 1;
  }

  return len;
}


----------------------------
None
----------------------------
***/


char *mi_strndup(const char *s, size_t n)
{
  return mi_heap_strndup(mi_prim_get_default_heap(), s, n);
}


/*** DEPENDENCIES:
char *mi_heap_strndup(mi_heap_t *heap, const char *s, size_t n)
{
  if (s == 0)
  {
    return 0;
  }
  const size_t len = _mi_strnlen(s, n);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


char *mi_heap_realpath(mi_heap_t *heap, const char *fname, char *resolved_name)
{
  if (resolved_name != 0)
  {
    return realpath(fname, resolved_name);
  }
  else
  {
    char *rname = realpath(fname, 0);
    if (rname == 0)
    {
      return 0;
    }
    char *result = mi_heap_strdup(heap, rname);
    mi_cfree(rname);
    return result;
  }
}


/*** DEPENDENCIES:
void mi_cfree(void *p)
{
  if (mi_is_in_heap_region(p))
  {
    mi_free(p);
  }
}


----------------------------
char *mi_heap_strdup(mi_heap_t *heap, const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = _mi_strlen(s);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}


----------------------------
None
----------------------------
***/


char *mi_realpath(const char *fname, char *resolved_name)
{
  return mi_heap_realpath(mi_prim_get_default_heap(), fname, resolved_name);
}


/*** DEPENDENCIES:
char *mi_heap_realpath(mi_heap_t *heap, const char *fname, char *resolved_name)
{
  if (resolved_name != 0)
  {
    return realpath(fname, resolved_name);
  }
  else
  {
    char *rname = realpath(fname, 0);
    if (rname == 0)
    {
      return 0;
    }
    char *result = mi_heap_strdup(heap, rname);
    mi_cfree(rname);
    return result;
  }
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


inline extern void *mi_heap_malloc_small(mi_heap_t *heap, size_t size)
{
  return mi_heap_malloc_small_zero(heap, size, 0);
}


/*** DEPENDENCIES:
inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 131, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 132, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->thread_id == 0) || (heap->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == tid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 135, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 149, __func__));
    ;
  }
  ;
  return p;
}


----------------------------
None
----------------------------
***/


inline extern void *mi_malloc_small(size_t size)
{
  return mi_heap_malloc_small(mi_prim_get_default_heap(), size);
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc_small(mi_heap_t *heap, size_t size)
{
  return mi_heap_malloc_small_zero(heap, size, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_zalloc_small(size_t size)
{
  return mi_heap_malloc_small_zero(mi_prim_get_default_heap(), size, 1);
}


/*** DEPENDENCIES:
inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 131, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 132, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->thread_id == 0) || (heap->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == tid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 135, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 149, __func__));
    ;
  }
  ;
  return p;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_zalloc(size_t size)
{
  return mi_heap_zalloc(mi_prim_get_default_heap(), size);
}


/*** DEPENDENCIES:
inline extern void *mi_heap_zalloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 1);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


extern void *mi_heap_mallocn(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_malloc(heap, total);
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
None
----------------------------
***/


void *mi_mallocn(size_t count, size_t size)
{
  return mi_heap_mallocn(mi_prim_get_default_heap(), count, size);
}


/*** DEPENDENCIES:
extern void *mi_heap_mallocn(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_malloc(heap, total);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_reallocf(mi_heap_t *heap, void *p, size_t newsize)
{
  void *newp = mi_heap_realloc(heap, p, newsize);
  if ((newp == 0) && (p != 0))
  {
    mi_free(p);
  }
  return newp;
}


/*** DEPENDENCIES:
None
----------------------------
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}


----------------------------
None
----------------------------
***/


void *mi_reallocf(void *p, size_t newsize)
{
  return mi_heap_reallocf(mi_prim_get_default_heap(), p, newsize);
}


/*** DEPENDENCIES:
void *mi_heap_reallocf(mi_heap_t *heap, void *p, size_t newsize)
{
  void *newp = mi_heap_realloc(heap, p, newsize);
  if ((newp == 0) && (p != 0))
  {
    mi_free(p);
  }
  return newp;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 1);
}


/*** DEPENDENCIES:
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}


----------------------------
None
----------------------------
***/


void *mi_rezalloc(void *p, size_t newsize)
{
  return mi_heap_rezalloc(mi_prim_get_default_heap(), p, newsize);
}


/*** DEPENDENCIES:
void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 1);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_recalloc(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc(heap, p, total);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 1);
}


----------------------------
None
----------------------------
***/


void *mi_recalloc(void *p, size_t count, size_t size)
{
  return mi_heap_recalloc(mi_prim_get_default_heap(), p, count, size);
}


/*** DEPENDENCIES:
void *mi_heap_recalloc(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc(heap, p, total);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void mi_free_size(void *p, size_t size)
{
  ;
  const size_t available = _mi_usable_size(p, "mi_free_size");
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 352, __func__));
  mi_free(p);
}


/*** DEPENDENCIES:
None
----------------------------
inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}


----------------------------
None
----------------------------
***/


void mi_free_size_aligned(void *p, size_t size, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 359, __func__));
  mi_free_size(p, size);
}


/*** DEPENDENCIES:
void mi_free_size(void *p, size_t size)
{
  ;
  const size_t available = _mi_usable_size(p, "mi_free_size");
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 352, __func__));
  mi_free(p);
}


----------------------------
None
----------------------------
***/


void mi_free_aligned(void *p, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 365, __func__));
  mi_free(p);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static std_new_handler_t mi_get_new_handler(void)
{
  return _ZSt15get_new_handlerv();
}


/*** DEPENDENCIES:
std_new_handler_t _ZSt15get_new_handlerv(void)
{
  return 0;
}


----------------------------
typedef void (*std_new_handler_t)(void)
----------------------------
***/


static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


/*** DEPENDENCIES:
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
static std_new_handler_t mi_get_new_handler(void)
{
  return _ZSt15get_new_handlerv();
}


----------------------------
typedef void (*std_new_handler_t)(void)
----------------------------
***/


void *mi_heap_try_new(mi_heap_t *heap, size_t size, bool nothrow)
{
  void *p = 0;
  unsigned int p_idx = 0;
  while (((&p[p_idx]) == 0) && mi_try_new_handler(nothrow))
  {
    p_idx = mi_heap_malloc(heap, size);
  }

  return p;
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
None
----------------------------
***/


void *mi_heap_alloc_new(mi_heap_t *heap, size_t size)
{
  void *p = mi_heap_malloc(heap, size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_heap_try_new(heap, size, 0);
  }
  return p;
}


/*** DEPENDENCIES:
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
void *mi_heap_try_new(mi_heap_t *heap, size_t size, bool nothrow)
{
  void *p = 0;
  unsigned int p_idx = 0;
  while (((&p[p_idx]) == 0) && mi_try_new_handler(nothrow))
  {
    p_idx = mi_heap_malloc(heap, size);
  }

  return p;
}


----------------------------
None
----------------------------
***/


void *mi_new(size_t size)
{
  return mi_heap_alloc_new(mi_prim_get_default_heap(), size);
}


/*** DEPENDENCIES:
void *mi_heap_alloc_new(mi_heap_t *heap, size_t size)
{
  void *p = mi_heap_malloc(heap, size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_heap_try_new(heap, size, 0);
  }
  return p;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_new_aligned(size_t size, size_t alignment)
{
  void *p;
  unsigned int p_idx = 0;
  do
  {
    p_idx = mi_malloc_aligned(size, alignment);
  }
  while (((&p[p_idx]) == 0) && mi_try_new_handler(0));
  return p;
}


/*** DEPENDENCIES:
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
***/


static void *mi_try_new(size_t size, bool nothrow)
{
  return mi_heap_try_new(mi_prim_get_default_heap(), size, nothrow);
}


/*** DEPENDENCIES:
void *mi_heap_try_new(mi_heap_t *heap, size_t size, bool nothrow)
{
  void *p = 0;
  unsigned int p_idx = 0;
  while (((&p[p_idx]) == 0) && mi_try_new_handler(nothrow))
  {
    p_idx = mi_heap_malloc(heap, size);
  }

  return p;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_new_nothrow(size_t size)
{
  void *p = mi_malloc(size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_try_new(size, 1);
  }
  return p;
}


/*** DEPENDENCIES:
inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


----------------------------
static void *mi_try_new(size_t size, bool nothrow)
{
  return mi_heap_try_new(mi_prim_get_default_heap(), size, nothrow);
}


----------------------------
***/


void *mi_new_aligned_nothrow(size_t size, size_t alignment)
{
  void *p;
  unsigned int p_idx = 0;
  do
  {
    p_idx = mi_malloc_aligned(size, alignment);
  }
  while (((&p[p_idx]) == 0) && mi_try_new_handler(1));
  return p;
}


/*** DEPENDENCIES:
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
***/


void *mi_heap_alloc_new_n(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (__builtin_expect(!(!mi_count_size_overflow(count, size, &total)), 0))
  {
    mi_try_new_handler(0);
    return 0;
  }
  else
  {
    return mi_heap_alloc_new(heap, total);
  }
}


/*** DEPENDENCIES:
void *mi_heap_alloc_new(mi_heap_t *heap, size_t size)
{
  void *p = mi_heap_malloc(heap, size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_heap_try_new(heap, size, 0);
  }
  return p;
}


----------------------------
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
None
----------------------------
***/


void *mi_new_n(size_t count, size_t size)
{
  return mi_heap_alloc_new_n(mi_prim_get_default_heap(), count, size);
}


/*** DEPENDENCIES:
void *mi_heap_alloc_new_n(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (__builtin_expect(!(!mi_count_size_overflow(count, size, &total)), 0))
  {
    mi_try_new_handler(0);
    return 0;
  }
  else
  {
    return mi_heap_alloc_new(heap, total);
  }
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_new_realloc(void *p, size_t newsize)
{
  void *q;
  unsigned int q_idx = 0;
  do
  {
    q_idx = mi_realloc(p, newsize);
  }
  while (((&q[q_idx]) == 0) && mi_try_new_handler(0));
  return q;
}


/*** DEPENDENCIES:
void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
***/


inline static uint8_t *mi_segment_end(mi_segment_t *segment)
{
  return ((uint8_t *) segment) + mi_segment_size(segment);
}


/*** DEPENDENCIES:
inline static size_t mi_segment_size(mi_segment_t *segment)
{
  return segment->segment_slices * (1UL << (13 + 3));
}


----------------------------
None
----------------------------
***/


void *mi_new_reallocn(void *p, size_t newcount, size_t size)
{
  size_t total;
  if (__builtin_expect(!(!mi_count_size_overflow(newcount, size, &total)), 0))
  {
    mi_try_new_handler(0);
    return 0;
  }
  else
  {
    return mi_new_realloc(p, total);
  }
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_new_realloc(void *p, size_t newsize)
{
  void *q;
  unsigned int q_idx = 0;
  do
  {
    q_idx = mi_realloc(p, newsize);
  }
  while (((&q[q_idx]) == 0) && mi_try_new_handler(0));
  return q;
}


----------------------------
static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}


----------------------------
***/


void _mi_free_generic(mi_segment_t *segment, mi_page_t *page, bool is_local, void *p)
{
  if (is_local)
  {
    mi_free_generic_local(page, segment, p);
  }
  else
    mi_free_generic_mt(page, segment, p);
}


/*** DEPENDENCIES:
None
----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
static void mi_free_generic_local(mi_page_t *page, mi_segment_t *segment, void *p)
{
  (void) segment;
  mi_block_t * const block = (mi_page_has_aligned(page)) ? (_mi_page_ptr_unalign(page, p)) : ((mi_block_t *) p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


----------------------------
None
----------------------------
***/


