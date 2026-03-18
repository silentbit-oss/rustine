void *mi_expand(void *p, size_t newsize)
{
  (void) p;
  (void) newsize;
  return 0;
}


/*** DEPENDENCIES:
***/


inline static size_t mi_popcount(size_t x)
{
  return __builtin_popcountll(x);
}


/*** DEPENDENCIES:
***/


inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}


/*** DEPENDENCIES:
***/


inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}


/*** DEPENDENCIES:
***/


inline static size_t mi_rotr(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x >> rshift) | (x << ((-rshift) & (((1 << 3) * 8) - 1)));
}


/*** DEPENDENCIES:
***/


inline static size_t mi_rotl(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x << rshift) | (x >> ((-rshift) & (((1 << 3) * 8) - 1)));
}


/*** DEPENDENCIES:
***/


inline static uint32_t mi_rotl32(uint32_t x, uint32_t r)
{
  const unsigned int rshift = ((unsigned int) r) & 31;
  return (x << rshift) | (x >> ((-rshift) & 31));
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


inline static size_t _mi_page_map_index(const void *p, size_t *sub_idx)
{
  const size_t u = (size_t) (((uintptr_t) p) / (1UL << (13 + 3)));
  if (sub_idx != 0)
  {
    *sub_idx = u % (1UL << 13);
  }
  return u / (1UL << 13);
}


/*** DEPENDENCIES:
***/


inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


/*** DEPENDENCIES:
***/


inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


/*** DEPENDENCIES:
***/


inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


/*** DEPENDENCIES:
***/


inline static mi_threadid_t __mi_prim_thread_id(void)
{
  return (uintptr_t) __builtin_thread_pointer();
}


/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
***/


inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 88, __func__));
  const size_t diff = ((uint8_t *) p) - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size)) ? (diff & (block_size - 1)) : (diff % block_size);
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


/*** DEPENDENCIES:
None
----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
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
typedef uintptr_t mi_encoded_t
----------------------------
inline static size_t mi_rotl(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x << rshift) | (x >> ((-rshift) & (((1 << 3) * 8) - 1)));
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
inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}


----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
***/


static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  return (ok) ? (bsize - delta) : (0);
}


/*** DEPENDENCIES:
None
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 328, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
}


/*** DEPENDENCIES:
None
----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 88, __func__));
  const size_t diff = ((uint8_t *) p) - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size)) ? (diff & (block_size - 1)) : (diff % block_size);
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  return (ok) ? (bsize - delta) : (0);
}


----------------------------
None
----------------------------
***/


inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}


/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
None
----------------------------
***/


inline static mi_page_flags_t mi_page_flags(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & 0x03UL;
}


/*** DEPENDENCIES:
typedef size_t mi_page_flags_t
----------------------------
inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}


/*** DEPENDENCIES:
inline static mi_page_flags_t mi_page_flags(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & 0x03UL;
}


----------------------------
None
----------------------------
***/


inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
inline static mi_threadid_t __mi_prim_thread_id(void)
{
  return (uintptr_t) __builtin_thread_pointer();
}


----------------------------
None
----------------------------
***/


inline static mi_page_t *mi_validate_ptr_page(const void *p, const char *msg)
{
  ;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_page_t *page = _mi_safe_ptr_page(p);
  if ((p != 0) && (page == 0))
  {
    _mi_error_message(22, "%s: invalid pointer: %p\n", msg, p);
  }
  return page;
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
mi_page_t *_mi_safe_ptr_page(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  if (__builtin_expect(!(!(p >= mi_page_map_max_address)), 0))
  {
    return 0;
  }
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, 0))), 0))
  {
    return 0;
  }
  mi_page_t ** const sub = _mi_page_map[idx];
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}


----------------------------
None
----------------------------
None
----------------------------
***/


inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_page_t * const page = mi_validate_ptr_page(p, msg);
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return 0;
  }
  if (__builtin_expect(!(!(!mi_page_has_interior_pointers(page))), 1))
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
inline static mi_page_t *mi_validate_ptr_page(const void *p, const char *msg)
{
  ;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_page_t *page = _mi_safe_ptr_page(p);
  if ((p != 0) && (page == 0))
  {
    _mi_error_message(22, "%s: invalid pointer: %p\n", msg, p);
  }
  return page;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 457, __func__));
  return (ok) ? (bsize - delta) : (0);
}


----------------------------
inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}


----------------------------
static size_t mi_page_usable_aligned_size_of(const mi_page_t *page, const void *p)
{
  const mi_block_t *block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = ((uint8_t *) p) - ((uint8_t *) block);
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 328, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
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
  const mi_page_t * const page = mi_validate_ptr_page(p, msg);
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return 0;
  }
  if (__builtin_expect(!(!(!mi_page_has_interior_pointers(page))), 1))
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


inline static bool mi_bsf(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = mi_ctz(x), 1)) : (0);
}


/*** DEPENDENCIES:
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}


----------------------------
***/


inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}


/*** DEPENDENCIES:
inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
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
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t
----------------------------
***/


inline static bool mi_memkind_needs_no_free(mi_memkind_t memkind)
{
  return memkind <= MI_MEM_STATIC;
}


/*** DEPENDENCIES:
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t
----------------------------
***/


inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
***/


inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
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
***/


inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 447, __func__));
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
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 447, __func__));
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


inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
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


inline static size_t mi_page_info_size(void)
{
  return _mi_align_up(sizeof(mi_page_t), 16);
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
***/


inline static bool mi_page_is_in_arena(const mi_page_t *page)
{
  return page->memid.memkind == MI_MEM_ARENA;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
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
None
----------------------------
***/


inline static bool mi_page_is_used_at_frac(const mi_page_t *page, uint16_t n)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used) <= frac;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


/*** DEPENDENCIES:
typedef uintptr_t mi_thread_free_t
----------------------------
***/


inline static bool mi_page_try_claim_ownership(mi_page_t *page)
{
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free, 1, memory_order_acq_rel);
  return (old & 1) == 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
***/


inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}


/*** DEPENDENCIES:
inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


----------------------------
***/


inline static void _mi_memset_aligned(void *dst, int val, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1185, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memset(adst, val, n);
}


/*** DEPENDENCIES:
inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


----------------------------
None
----------------------------
***/


inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


/*** DEPENDENCIES:
inline static void _mi_memset_aligned(void *dst, int val, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1185, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memset(adst, val, n);
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


inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


/*** DEPENDENCIES:
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}


----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
None
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
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 501, __func__));
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
None
----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 501, __func__));
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
None
----------------------------
***/


inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
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


inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
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
inline static size_t mi_rotr(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x >> rshift) | (x << ((-rshift) & (((1 << 3) * 8) - 1)));
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


inline static size_t mi_page_size(const mi_page_t *page)
{
  return mi_page_block_size(page) * page->reserved;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}


/*** DEPENDENCIES:
inline static size_t mi_page_size(const mi_page_t *page)
{
  return mi_page_block_size(page) * page->reserved;
}


----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_contains_address(const mi_page_t *page, const void *p)
{
  size_t psize;
  uint8_t *start = mi_page_area(page, &psize);
  return (start <= ((uint8_t *) p)) && (((uint8_t *) p) < (start + psize));
}


/*** DEPENDENCIES:
inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}


----------------------------
None
----------------------------
***/


inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}


/*** DEPENDENCIES:
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
***/


inline static mi_page_t *_mi_checked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  const mi_submap_t sub = _mi_page_map_at(idx);
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}


/*** DEPENDENCIES:
inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}


----------------------------
inline static size_t _mi_page_map_index(const void *p, size_t *sub_idx)
{
  const size_t u = (size_t) (((uintptr_t) p) / (1UL << (13 + 3)));
  if (sub_idx != 0)
  {
    *sub_idx = u % (1UL << 13);
  }
  return u / (1UL << 13);
}


----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
None
----------------------------
***/


inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_page_t *_mi_checked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  const mi_submap_t sub = _mi_page_map_at(idx);
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}


----------------------------
bool mi_is_in_heap_region(const void *p)
{
  return _mi_safe_ptr_page(p) != 0;
}


----------------------------
None
----------------------------
***/


inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_contains_address(page, q);
}


/*** DEPENDENCIES:
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static bool mi_page_contains_address(const mi_page_t *page, const void *p)
{
  size_t psize;
  uint8_t *start = mi_page_area(page, &psize);
  return (start <= ((uint8_t *) p)) && (((uint8_t *) p) < (start + psize));
}


----------------------------
None
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
inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_contains_address(page, q);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
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
None
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
None
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
inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_contains_address(page, q);
}


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
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
***/


inline static void mi_page_flags_set(mi_page_t *page, bool set, mi_page_flags_t newflag)
{
  if (set)
  {
    atomic_fetch_or_explicit(&page->xthread_id, newflag, memory_order_relaxed);
  }
  else
  {
    atomic_fetch_and_explicit(&page->xthread_id, ~newflag, memory_order_relaxed);
  }
}


/*** DEPENDENCIES:
typedef size_t mi_page_flags_t
----------------------------
None
----------------------------
***/


inline static void mi_page_set_has_interior_pointers(mi_page_t *page, bool has_aligned)
{
  mi_page_flags_set(page, has_aligned, 0x02UL);
}


/*** DEPENDENCIES:
inline static void mi_page_flags_set(mi_page_t *page, bool set, mi_page_flags_t newflag)
{
  if (set)
  {
    atomic_fetch_or_explicit(&page->xthread_id, newflag, memory_order_relaxed);
  }
  else
  {
    atomic_fetch_and_explicit(&page->xthread_id, ~newflag, memory_order_relaxed);
  }
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


/*** DEPENDENCIES:
inline static mi_page_flags_t mi_page_flags(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & 0x03UL;
}


----------------------------
None
----------------------------
***/


inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


/*** DEPENDENCIES:
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


inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}


----------------------------
typedef size_t mi_threadid_t
----------------------------
None
----------------------------
***/


inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


/*** DEPENDENCIES:
inline static void mi_page_flags_set(mi_page_t *page, bool set, mi_page_flags_t newflag)
{
  if (set)
  {
    atomic_fetch_or_explicit(&page->xthread_id, newflag, memory_order_relaxed);
  }
  else
  {
    atomic_fetch_and_explicit(&page->xthread_id, ~newflag, memory_order_relaxed);
  }
}


----------------------------
None
----------------------------
***/


inline static bool mi_memid_is_os(mi_memid_t memid)
{
  return mi_memkind_is_os(memid.memkind);
}


/*** DEPENDENCIES:
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}


----------------------------
None
----------------------------
***/


inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}


/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


/*** DEPENDENCIES:
inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}


----------------------------
None
----------------------------
***/


inline static bool mi_memid_needs_no_free(mi_memid_t memid)
{
  return mi_memkind_needs_no_free(memid.memkind);
}


/*** DEPENDENCIES:
inline static bool mi_memkind_needs_no_free(mi_memkind_t memkind)
{
  return memkind <= MI_MEM_STATIC;
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


/*** DEPENDENCIES:
inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}


/*** DEPENDENCIES:
None
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
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t
----------------------------
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
None
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
None
----------------------------
***/


inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
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


inline static void mi_page_set_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 836, __func__));
  atomic_fetch_or_explicit(&page->xthread_id, 0x03UL + 1, memory_order_relaxed);
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}


/*** DEPENDENCIES:
inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}


----------------------------
None
----------------------------
***/


inline static void mi_page_clear_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 841, __func__));
  atomic_fetch_and_explicit(&page->xthread_id, 0x03UL, memory_order_relaxed);
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}


----------------------------
None
----------------------------
***/


inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
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
None
----------------------------
***/


inline static bool _mi_page_unown(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 894, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 895, __func__));
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    (mi_tf_is_owned(tf_old)) ? ((void) 0) : (_mi_assert_fail("mi_tf_is_owned(tf_old)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 899, __func__));
    while (__builtin_expect(!(!(mi_tf_block(tf_old) != 0)), 0))
    {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page))
      {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page, 0);
        return 1;
      }
      tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    }

    (mi_tf_block(tf_old) == 0) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(tf_old)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 909, __func__));
    tf_new = mi_tf_create(0, 0);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *stats_tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 808, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 809, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 810, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 811, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 812, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 813, __func__));
  if (stats_tld != 0)
  {
    __mi_stat_decrease(&stats_tld->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease(&stats_tld->stats.pages, 1);
  }
  else
  {
    __mi_stat_decrease_mt(&_mi_subproc()->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease_mt(&_mi_subproc()->stats.pages, 1);
  }
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t * const arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 830, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 831, __func__));
    (mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 832, __func__));
    (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 833, __func__));
  }
  _mi_page_map_unregister(page);
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    helper__mi_arenas_page_free_1(page);
  }
  _mi_arenas_free(page, mi_page_full_size(page), page->memid);
}


----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
void _mi_arenas_page_unabandon(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 947, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 948, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 949, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 950, __func__));
  if (mi_page_is_abandoned_mapped(page))
  {
    (page->memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind==MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 953, __func__));
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 960, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 961, __func__));
    mi_bitmap_clear_once_set(arena->pages_abandoned[bin], slice_index);
    mi_page_clear_abandoned_mapped(page);
    atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
  }
  else
  {
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      mi_subproc_t *subproc = _mi_subproc();
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        if (page->prev != 0)
        {
          page->prev->next = page->next;
        }
        if (page->next != 0)
        {
          page->next->prev = page->prev;
        }
        if (subproc->os_abandoned_pages == page)
        {
          subproc->os_abandoned_pages = page->next;
        }
        page->next = 0;
        page->prev = 0;
      }

    }
  }
}


----------------------------
None
----------------------------
***/


inline static mi_memid_t _mi_memid_create_meta(void *mpage, size_t block_idx, size_t block_count)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_META);
  memid.mem.meta.meta_page = mpage;
  memid.mem.meta.block_index = (uint32_t) block_idx;
  memid.mem.meta.block_count = (uint32_t) block_count;
  memid.initially_committed = 1;
  memid.initially_zero = 1;
  memid.is_pinned = 1;
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
None
----------------------------
***/


inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1178, __func__));
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


static void mi_stat_free(const mi_page_t *page, const mi_block_t *block)
{
  (void) block;
  mi_heap_t * const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize);
    __mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], 1);
  }
  else
  {
    const size_t bpsize = mi_page_block_size(page);
    __mi_stat_decrease(&heap->tld->stats.malloc_huge, bpsize);
  }
}


/*** DEPENDENCIES:
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
mi_heap_t *mi_heap_get_default(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  unsigned int heap_idx = 0;
  if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
  {
    mi_thread_init();
    heap_idx = mi_prim_get_default_heap();
  }
  return heap;
}


----------------------------
None
----------------------------
***/


inline static void mi_free_block_local(mi_page_t *page, mi_block_t *block, bool track_stats, bool check_full)
{
  if (__builtin_expect(!(!mi_check_is_double_free(page, block)), 0))
  {
    return;
  }
  mi_check_padding(page, block);
  if (track_stats)
  {
    mi_stat_free(page, block);
  }
  memset(block, 0xDF, mi_page_block_size(page));
  if (track_stats)
  {
    ;
  }
  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!(!((--page->used) == 0)), 0))
  {
    _mi_page_retire(page);
  }
  else
    if (__builtin_expect(!(!(check_full && mi_page_is_in_full(page))), 0))
  {
    _mi_page_unfull(page);
  }
}


/*** DEPENDENCIES:
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
void _mi_page_unfull(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 347, __func__));
  ;
  (mi_page_is_in_full(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_in_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 349, __func__));
  (!mi_page_heap(page)->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!mi_page_heap(page)->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 350, __func__));
  if (!mi_page_is_in_full(page))
  {
    return;
  }
  mi_heap_t *heap = mi_page_heap(page);
  mi_page_queue_t *pqfull = &heap->pages[73U + 1];
  mi_page_set_in_full(page, 0);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  mi_page_set_in_full(page, 1);
  mi_page_queue_enqueue_from_full(pq, pqfull, page);
}


----------------------------
void _mi_page_retire(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 411, __func__));
  ;
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 413, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_t *pq = mi_page_queue_of(page);
  const size_t bsize = mi_page_block_size(page);
  if (__builtin_expect(!(!(!mi_page_queue_is_special(pq))), 1))
  {
    if ((pq->last == page) && (pq->first == page))
    {
      mi_heap_t *heap = mi_page_heap(page);
      __mi_stat_counter_increase(&heap->tld->stats.pages_retire, 1);
      page->retire_expire = (bsize <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8)) ? (16) : (16 / 4);
      (pq >= heap->pages) ? ((void) 0) : (_mi_assert_fail("pq >= heap->pages", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 433, __func__));
      const size_t index = pq - heap->pages;
      ((index < (73U + 1)) && (index < 73U)) ? ((void) 0) : (_mi_assert_fail("index < MI_BIN_FULL && index < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 435, __func__));
      if (index < heap->page_retired_min)
      {
        heap->page_retired_min = index;
      }
      if (index > heap->page_retired_max)
      {
        heap->page_retired_max = index;
      }
      (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 438, __func__));
      return;
    }
  }
  _mi_page_free(page, pq);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
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


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
static void mi_stat_free(const mi_page_t *page, const mi_block_t *block)
{
  (void) block;
  mi_heap_t * const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize);
    __mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], 1);
  }
  else
  {
    const size_t bpsize = mi_page_block_size(page);
    __mi_stat_decrease(&heap->tld->stats.malloc_huge, bpsize);
  }
}


----------------------------
static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


inline static mi_block_t *mi_validate_block_from_ptr(const mi_page_t *page, void *p)
{
  (_mi_page_ptr_unalign(page, p) == ((mi_block_t *) p)) ? ((void) 0) : (_mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 109, __func__));
  (void) page;
  return (mi_block_t *) p;
}


/*** DEPENDENCIES:
None
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 88, __func__));
  const size_t diff = ((uint8_t *) p) - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size)) ? (diff & (block_size - 1)) : (diff % block_size);
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
None
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
None
----------------------------
***/


static void mi_free_generic_local(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 122, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}


----------------------------
inline static mi_block_t *mi_validate_block_from_ptr(const mi_page_t *page, void *p)
{
  (_mi_page_ptr_unalign(page, p) == ((mi_block_t *) p)) ? ((void) 0) : (_mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 109, __func__));
  (void) page;
  return (mi_block_t *) p;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 88, __func__));
  const size_t diff = ((uint8_t *) p) - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size)) ? (diff & (block_size - 1)) : (diff % block_size);
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}


----------------------------
inline static void mi_free_block_local(mi_page_t *page, mi_block_t *block, bool track_stats, bool check_full)
{
  if (__builtin_expect(!(!mi_check_is_double_free(page, block)), 0))
  {
    return;
  }
  mi_check_padding(page, block);
  if (track_stats)
  {
    mi_stat_free(page, block);
  }
  memset(block, 0xDF, mi_page_block_size(page));
  if (track_stats)
  {
    ;
  }
  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!(!((--page->used) == 0)), 0))
  {
    _mi_page_retire(page);
  }
  else
    if (__builtin_expect(!(!(check_full && mi_page_is_in_full(page))), 0))
  {
    _mi_page_unfull(page);
  }
}


----------------------------
None
----------------------------
***/


inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  mi_page_queue_t * const pq = &((mi_heap_t *) heap)->pages[_mi_bin(size)];
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    (pq->block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8)) ? ((void) 0) : (_mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 762, __func__));
  }
  return pq;
}


/*** DEPENDENCIES:
None
----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_queue_len_is_atmost(mi_heap_t *heap, size_t block_size, long atmost)
{
  mi_page_queue_t * const pq = mi_page_queue(heap, block_size);
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 201, __func__));
  return pq->count <= ((size_t) atmost);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  mi_page_queue_t * const pq = &((mi_heap_t *) heap)->pages[_mi_bin(size)];
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    (pq->block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8)) ? ((void) 0) : (_mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 762, __func__));
  }
  return pq;
}


----------------------------
None
----------------------------
***/


static bool mi_page_unown_from_free(mi_page_t *page, mi_block_t *mt_free)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 295, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 296, __func__));
  (mt_free != 0) ? ((void) 0) : (_mi_assert_fail("mt_free != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 297, __func__));
  (page->used > 1) ? ((void) 0) : (_mi_assert_fail("page->used > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 298, __func__));
  mi_thread_free_t tf_expect = mi_tf_create(mt_free, 1);
  mi_thread_free_t tf_new = mi_tf_create(mt_free, 0);
  while (__builtin_expect(!(!(!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_expect, tf_new, memory_order_acq_rel, memory_order_acquire))), 0))
  {
    (mi_tf_is_owned(tf_expect)) ? ((void) 0) : (_mi_assert_fail("mi_tf_is_owned(tf_expect)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 302, __func__));
    while (mi_tf_block(tf_expect) != 0)
    {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page))
      {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page, 0);
        return 1;
      }
      tf_expect = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    }

    (mi_tf_block(tf_expect) == 0) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(tf_expect)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 312, __func__));
    tf_new = mi_tf_create(0, 0);
  }

  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *stats_tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 808, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 809, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 810, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 811, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 812, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 813, __func__));
  if (stats_tld != 0)
  {
    __mi_stat_decrease(&stats_tld->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease(&stats_tld->stats.pages, 1);
  }
  else
  {
    __mi_stat_decrease_mt(&_mi_subproc()->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease_mt(&_mi_subproc()->stats.pages, 1);
  }
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t * const arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 830, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 831, __func__));
    (mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 832, __func__));
    (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 833, __func__));
  }
  _mi_page_map_unregister(page);
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    helper__mi_arenas_page_free_1(page);
  }
  _mi_arenas_free(page, mi_page_full_size(page), page->memid);
}


----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
void _mi_arenas_page_unabandon(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 947, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 948, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 949, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 950, __func__));
  if (mi_page_is_abandoned_mapped(page))
  {
    (page->memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind==MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 953, __func__));
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 960, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 961, __func__));
    mi_bitmap_clear_once_set(arena->pages_abandoned[bin], slice_index);
    mi_page_clear_abandoned_mapped(page);
    atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
  }
  else
  {
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      mi_subproc_t *subproc = _mi_subproc();
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        if (page->prev != 0)
        {
          page->prev->next = page->next;
        }
        if (page->next != 0)
        {
          page->next->prev = page->prev;
        }
        if (subproc->os_abandoned_pages == page)
        {
          subproc->os_abandoned_pages = page->next;
        }
        page->next = 0;
        page->prev = 0;
      }

    }
  }
}


----------------------------
None
----------------------------
***/


static void mi_free_try_collect_mt(mi_page_t *page, mi_block_t *mt_free)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 206, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 207, __func__));
  _mi_page_free_collect_partly(page, mt_free);
  if (mi_page_is_singleton(page))
  {
    (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 215, __func__));
  }
  if (mi_page_all_free(page))
  {
    _mi_arenas_page_unabandon(page);
    _mi_arenas_page_free(page, 0);
    return;
  }
  if (page->block_size <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8))
  {
    const long reclaim_on_free = _mi_option_get_fast(mi_option_page_reclaim_on_free);
    if (reclaim_on_free >= 0)
    {
      mi_heap_t *heap = mi_prim_get_default_heap();
      unsigned int heap_idx = 0;
      if ((&heap[heap_idx]) != page->heap)
      {
        if (mi_heap_is_initialized(heap))
        {
          heap_idx = _mi_heap_by_tag(heap_idx, page->heap_tag);
        }
      }
      if (((&heap[heap_idx]) != 0) && heap->allow_page_reclaim)
      {
        long max_reclaim = 0;
        if (__builtin_expect(!(!((&heap[heap_idx]) == page->heap)), 1))
        {
          max_reclaim = _mi_option_get_fast((heap->tld->is_in_threadpool) ? (mi_option_page_cross_thread_max_reclaim) : (mi_option_page_max_reclaim));
        }
        else
          if ((((reclaim_on_free == 1) && (!heap->tld->is_in_threadpool)) && (!mi_page_is_used_at_frac(page, 8))) && _mi_arena_memid_is_suitable(page->memid, heap->exclusive_arena))
        {
          max_reclaim = _mi_option_get_fast(mi_option_page_cross_thread_max_reclaim);
        }
        if ((max_reclaim < 0) || mi_page_queue_len_is_atmost(heap, page->block_size, max_reclaim))
        {
          _mi_arenas_page_unabandon(page);
          _mi_heap_page_reclaim(heap, page);
          __mi_stat_counter_increase(&heap->tld->stats.pages_reclaim_on_free, 1);
          return;
        }
      }
    }
  }
  if ((((!mi_page_is_used_at_frac(page, 8)) && (!mi_page_is_abandoned_mapped(page))) && (page->memid.memkind == MI_MEM_ARENA)) && _mi_arenas_page_try_reabandon_to_mapped(page))
  {
    return;
  }
  mi_page_unown_from_free(page, mt_free);
}


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *stats_tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 808, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 809, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 810, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 811, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 812, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 813, __func__));
  if (stats_tld != 0)
  {
    __mi_stat_decrease(&stats_tld->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease(&stats_tld->stats.pages, 1);
  }
  else
  {
    __mi_stat_decrease_mt(&_mi_subproc()->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease_mt(&_mi_subproc()->stats.pages, 1);
  }
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t * const arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 830, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 831, __func__));
    (mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 832, __func__));
    (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 833, __func__));
  }
  _mi_page_map_unregister(page);
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    helper__mi_arenas_page_free_1(page);
  }
  _mi_arenas_free(page, mi_page_full_size(page), page->memid);
}


----------------------------
mi_heap_t *_mi_heap_by_tag(mi_heap_t *heap, uint8_t tag)
{
  if (heap->tag == tag)
  {
    return heap;
  }
  for (mi_heap_t *curr = heap->tld->heaps; (&curr[curr_idx]) != 0; curr_idx = curr_idx->next)
  {
    if (curr->tag == tag)
    {
      return curr;
    }
  }

  unsigned int curr_idx = 0;
  return 0;
}


----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
void _mi_page_free_collect_partly(mi_page_t *page, mi_block_t *head)
{
  if (head == 0)
  {
    return;
  }
  mi_block_t *next = mi_block_next(page, head);
  if (next != 0)
  {
    mi_block_set_next(page, head, 0);
    mi_page_thread_collect_to_local(page, next);
    if ((page->local_free != 0) && (page->free == 0))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  if (page->used == 1)
  {
    (mi_tf_block(atomic_load_explicit(&page->xthread_free, memory_order_relaxed)) == head) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(mi_atomic_load_relaxed(&page->xthread_free)) == head", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 238, __func__));
    (mi_block_next(page, head) == 0) ? ((void) 0) : (_mi_assert_fail("mi_block_next(page,head) == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 239, __func__));
    _mi_page_free_collect(page, 0);
  }
}


----------------------------
void _mi_heap_page_reclaim(mi_heap_t *heap, mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 270, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 271, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 272, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 273, __func__));
  mi_page_set_heap(page, heap);
  _mi_page_free_collect(page, 0);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  mi_page_queue_push_at_end(heap, pq, page);
  ;
}


----------------------------
inline static bool mi_page_is_used_at_frac(const mi_page_t *page, uint16_t n)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used) <= frac;
}


----------------------------
long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 249, __func__));
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 251, __func__));
  return desc->value;
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
static bool mi_page_unown_from_free(mi_page_t *page, mi_block_t *mt_free)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 295, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 296, __func__));
  (mt_free != 0) ? ((void) 0) : (_mi_assert_fail("mt_free != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 297, __func__));
  (page->used > 1) ? ((void) 0) : (_mi_assert_fail("page->used > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 298, __func__));
  mi_thread_free_t tf_expect = mi_tf_create(mt_free, 1);
  mi_thread_free_t tf_new = mi_tf_create(mt_free, 0);
  while (__builtin_expect(!(!(!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_expect, tf_new, memory_order_acq_rel, memory_order_acquire))), 0))
  {
    (mi_tf_is_owned(tf_expect)) ? ((void) 0) : (_mi_assert_fail("mi_tf_is_owned(tf_expect)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 302, __func__));
    while (mi_tf_block(tf_expect) != 0)
    {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page))
      {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page, 0);
        return 1;
      }
      tf_expect = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    }

    (mi_tf_block(tf_expect) == 0) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(tf_expect)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 312, __func__));
    tf_new = mi_tf_create(0, 0);
  }

  return 0;
}


----------------------------
void _mi_arenas_page_unabandon(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 947, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 948, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 949, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 950, __func__));
  if (mi_page_is_abandoned_mapped(page))
  {
    (page->memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind==MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 953, __func__));
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 960, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 961, __func__));
    mi_bitmap_clear_once_set(arena->pages_abandoned[bin], slice_index);
    mi_page_clear_abandoned_mapped(page);
    atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
  }
  else
  {
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      mi_subproc_t *subproc = _mi_subproc();
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        if (page->prev != 0)
        {
          page->prev->next = page->next;
        }
        if (page->next != 0)
        {
          page->next->prev = page->prev;
        }
        if (subproc->os_abandoned_pages == page)
        {
          subproc->os_abandoned_pages = page->next;
        }
        page->next = 0;
        page->prev = 0;
      }

    }
  }
}


----------------------------
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 925, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 926, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 927, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 928, __func__));
  (!mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_abandoned_mapped(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 929, __func__));
  (!mi_page_is_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 930, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 931, __func__));
  (!mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_singleton(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 932, __func__));
  if ((mi_page_is_full(page) || mi_page_is_abandoned_mapped(page)) || (page->memid.memkind != MI_MEM_ARENA))
  {
    return 0;
  }
  else
  {
    mi_tld_t *tld = _mi_thread_tld();
    __mi_stat_counter_increase(&tld->stats.pages_reabandon_full, 1);
    __mi_stat_adjust_decrease(&tld->stats.pages_abandoned, 1);
    _mi_arenas_page_abandon(page, tld);
    return 1;
  }
}


----------------------------
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t *request_arena)
{
  if (memid.memkind == MI_MEM_ARENA)
  {
    return mi_arena_id_is_suitable(memid.mem.arena.arena, request_arena);
  }
  else
  {
    return mi_arena_id_is_suitable(0, request_arena);
  }
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static bool mi_page_queue_len_is_atmost(mi_heap_t *heap, size_t block_size, long atmost)
{
  mi_page_queue_t * const pq = mi_page_queue(heap, block_size);
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 201, __func__));
  return pq->count <= ((size_t) atmost);
}


----------------------------
None
----------------------------
***/


inline static void mi_free_block_mt(mi_page_t *page, mi_block_t *block)
{
  mi_stat_free(page, block);
  ;
  size_t dbgsize = mi_usable_size(block);
  if (dbgsize > (1024UL * 1024UL))
  {
    dbgsize = 1024UL * 1024UL;
  }
  _mi_memset_aligned(block, 0xDF, dbgsize);
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    mi_block_set_next(page, block, mi_tf_block(tf_old));
    tf_new = mi_tf_create(block, 1);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  const bool is_owned_now = !mi_tf_is_owned(tf_old);
  if (is_owned_now)
  {
    (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 77, __func__));
    mi_free_try_collect_mt(page, block);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static void mi_free_try_collect_mt(mi_page_t *page, mi_block_t *mt_free)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 206, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 207, __func__));
  _mi_page_free_collect_partly(page, mt_free);
  if (mi_page_is_singleton(page))
  {
    (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 215, __func__));
  }
  if (mi_page_all_free(page))
  {
    _mi_arenas_page_unabandon(page);
    _mi_arenas_page_free(page, 0);
    return;
  }
  if (page->block_size <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8))
  {
    const long reclaim_on_free = _mi_option_get_fast(mi_option_page_reclaim_on_free);
    if (reclaim_on_free >= 0)
    {
      mi_heap_t *heap = mi_prim_get_default_heap();
      unsigned int heap_idx = 0;
      if ((&heap[heap_idx]) != page->heap)
      {
        if (mi_heap_is_initialized(heap))
        {
          heap_idx = _mi_heap_by_tag(heap_idx, page->heap_tag);
        }
      }
      if (((&heap[heap_idx]) != 0) && heap->allow_page_reclaim)
      {
        long max_reclaim = 0;
        if (__builtin_expect(!(!((&heap[heap_idx]) == page->heap)), 1))
        {
          max_reclaim = _mi_option_get_fast((heap->tld->is_in_threadpool) ? (mi_option_page_cross_thread_max_reclaim) : (mi_option_page_max_reclaim));
        }
        else
          if ((((reclaim_on_free == 1) && (!heap->tld->is_in_threadpool)) && (!mi_page_is_used_at_frac(page, 8))) && _mi_arena_memid_is_suitable(page->memid, heap->exclusive_arena))
        {
          max_reclaim = _mi_option_get_fast(mi_option_page_cross_thread_max_reclaim);
        }
        if ((max_reclaim < 0) || mi_page_queue_len_is_atmost(heap, page->block_size, max_reclaim))
        {
          _mi_arenas_page_unabandon(page);
          _mi_heap_page_reclaim(heap, page);
          __mi_stat_counter_increase(&heap->tld->stats.pages_reclaim_on_free, 1);
          return;
        }
      }
    }
  }
  if ((((!mi_page_is_used_at_frac(page, 8)) && (!mi_page_is_abandoned_mapped(page))) && (page->memid.memkind == MI_MEM_ARENA)) && _mi_arenas_page_try_reabandon_to_mapped(page))
  {
    return;
  }
  mi_page_unown_from_free(page, mt_free);
}


----------------------------
inline static void _mi_memset_aligned(void *dst, int val, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1185, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memset(adst, val, n);
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}


----------------------------
static void mi_stat_free(const mi_page_t *page, const mi_block_t *block)
{
  (void) block;
  mi_heap_t * const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize);
    __mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], 1);
  }
  else
  {
    const size_t bpsize = mi_page_block_size(page);
    __mi_stat_decrease(&heap->tld->stats.malloc_huge, bpsize);
  }
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
None
----------------------------
***/


static void mi_free_generic_mt(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 130, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, block);
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}


----------------------------
inline static mi_block_t *mi_validate_block_from_ptr(const mi_page_t *page, void *p)
{
  (_mi_page_ptr_unalign(page, p) == ((mi_block_t *) p)) ? ((void) 0) : (_mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 109, __func__));
  (void) page;
  return (mi_block_t *) p;
}


----------------------------
inline static void mi_free_block_mt(mi_page_t *page, mi_block_t *block)
{
  mi_stat_free(page, block);
  ;
  size_t dbgsize = mi_usable_size(block);
  if (dbgsize > (1024UL * 1024UL))
  {
    dbgsize = 1024UL * 1024UL;
  }
  _mi_memset_aligned(block, 0xDF, dbgsize);
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    mi_block_set_next(page, block, mi_tf_block(tf_old));
    tf_new = mi_tf_create(block, 1);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  const bool is_owned_now = !mi_tf_is_owned(tf_old);
  if (is_owned_now)
  {
    (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 77, __func__));
    mi_free_try_collect_mt(page, block);
  }
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 88, __func__));
  const size_t diff = ((uint8_t *) p) - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size)) ? (diff & (block_size - 1)) : (diff % block_size);
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}


----------------------------
None
----------------------------
***/


void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


----------------------------
inline static mi_page_t *mi_validate_ptr_page(const void *p, const char *msg)
{
  ;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_page_t *page = _mi_safe_ptr_page(p);
  if ((p != 0) && (page == 0))
  {
    _mi_error_message(22, "%s: invalid pointer: %p\n", msg, p);
  }
  return page;
}


----------------------------
typedef size_t mi_threadid_t
----------------------------
static void mi_free_generic_mt(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 130, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, block);
}


----------------------------
inline static mi_block_t *mi_validate_block_from_ptr(const mi_page_t *page, void *p)
{
  (_mi_page_ptr_unalign(page, p) == ((mi_block_t *) p)) ? ((void) 0) : (_mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 109, __func__));
  (void) page;
  return (mi_block_t *) p;
}


----------------------------
inline static void mi_free_block_mt(mi_page_t *page, mi_block_t *block)
{
  mi_stat_free(page, block);
  ;
  size_t dbgsize = mi_usable_size(block);
  if (dbgsize > (1024UL * 1024UL))
  {
    dbgsize = 1024UL * 1024UL;
  }
  _mi_memset_aligned(block, 0xDF, dbgsize);
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    mi_block_set_next(page, block, mi_tf_block(tf_old));
    tf_new = mi_tf_create(block, 1);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  const bool is_owned_now = !mi_tf_is_owned(tf_old);
  if (is_owned_now)
  {
    (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 77, __func__));
    mi_free_try_collect_mt(page, block);
  }
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static void mi_free_generic_local(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 122, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


----------------------------
inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}


----------------------------
inline static void mi_free_block_local(mi_page_t *page, mi_block_t *block, bool track_stats, bool check_full)
{
  if (__builtin_expect(!(!mi_check_is_double_free(page, block)), 0))
  {
    return;
  }
  mi_check_padding(page, block);
  if (track_stats)
  {
    mi_stat_free(page, block);
  }
  memset(block, 0xDF, mi_page_block_size(page));
  if (track_stats)
  {
    ;
  }
  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!(!((--page->used) == 0)), 0))
  {
    _mi_page_retire(page);
  }
  else
    if (__builtin_expect(!(!(check_full && mi_page_is_in_full(page))), 0))
  {
    _mi_page_unfull(page);
  }
}


----------------------------
None
----------------------------
***/


inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 547, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 549, __func__));
  return heap->pages_free_direct[idx];
}


/*** DEPENDENCIES:
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
None
----------------------------
None
----------------------------
***/


inline static mi_arena_t *mi_memid_arena(mi_memid_t memid)
{
  return (memid.memkind == MI_MEM_ARENA) ? (memid.mem.arena.arena) : (0);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static size_t mi_page_slice_offset_of(const mi_page_t *page, size_t offset_relative_to_page_start)
{
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}


/*** DEPENDENCIES:
inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 129, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 130, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->tld->thread_id == 0) || (heap->tld->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == tid", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 133, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 147, __func__));
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
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 547, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 549, __func__));
  return heap->pages_free_direct[idx];
}


----------------------------
None
----------------------------
***/


inline extern void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  if (__builtin_expect(!(!(size <= (128 * (sizeof(void *))))), 1))
  {
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 170, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 180, __func__));
    ((heap->tld->thread_id == 0) || (heap->tld->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == _mi_thread_id()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 181, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 183, __func__));
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
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 129, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 130, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->tld->thread_id == 0) || (heap->tld->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == tid", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 133, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 147, __func__));
    ;
  }
  ;
  return p;
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
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 170, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 180, __func__));
    ((heap->tld->thread_id == 0) || (heap->tld->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == _mi_thread_id()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 181, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 183, __func__));
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
  const size_t size = (p == 0) ? (0) : (_mi_usable_size(p, "mi_realloc"));
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 261, __func__));
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
None
----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_page_t * const page = mi_validate_ptr_page(p, msg);
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return 0;
  }
  if (__builtin_expect(!(!(!mi_page_has_interior_pointers(page))), 1))
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
inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}


----------------------------
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
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
  const size_t size = (p == 0) ? (0) : (_mi_usable_size(p, "mi_realloc"));
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 261, __func__));
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
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
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


void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 469, __func__));
  if ((!ok) || ((bsize - delta) >= min_size))
  {
    return;
  }
  (bsize >= min_size) ? ((void) 0) : (_mi_assert_fail("bsize >= min_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 471, __func__));
  if (bsize < min_size)
  {
    return;
  }
  size_t new_delta = bsize - min_size;
  (new_delta < bsize) ? ((void) 0) : (_mi_assert_fail("new_delta < bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 474, __func__));
  mi_padding_t *padding = (mi_padding_t *) (((uint8_t *) block) + bsize);
  ;
  padding->delta = (uint32_t) new_delta;
  ;
}


/*** DEPENDENCIES:
None
----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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


extern void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 1);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


extern void *_mi_page_malloc(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 0);
}


/*** DEPENDENCIES:
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
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
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


inline static size_t mi_page_committed(const mi_page_t *page)
{
  return (page->slice_committed == 0) ? (mi_page_size(page)) : (page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}


/*** DEPENDENCIES:
inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
}


----------------------------
inline static size_t mi_page_size(const mi_page_t *page)
{
  return mi_page_block_size(page) * page->reserved;
}


----------------------------
None
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
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
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
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 129, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 130, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->tld->thread_id == 0) || (heap->tld->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == tid", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 133, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 147, __func__));
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
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 129, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 130, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->tld->thread_id == 0) || (heap->tld->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == tid", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 133, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 147, __func__));
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
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}


----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
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
  const size_t size = (p == 0) ? (0) : (_mi_usable_size(p, "mi_realloc"));
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 261, __func__));
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
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 364, __func__));
  mi_free(p);
}


/*** DEPENDENCIES:
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_page_t * const page = mi_validate_ptr_page(p, msg);
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return 0;
  }
  if (__builtin_expect(!(!(!mi_page_has_interior_pointers(page))), 1))
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
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 371, __func__));
  mi_free_size(p, size);
}


/*** DEPENDENCIES:
void mi_free_size(void *p, size_t size)
{
  ;
  const size_t available = _mi_usable_size(p, "mi_free_size");
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 364, __func__));
  mi_free(p);
}


----------------------------
None
----------------------------
***/


void mi_free_aligned(void *p, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 377, __func__));
  mi_free(p);
}


/*** DEPENDENCIES:
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


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


inline static mi_page_t *_mi_unchecked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  return _mi_page_map_at(idx)[sub_idx];
}


/*** DEPENDENCIES:
inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}


----------------------------
inline static size_t _mi_page_map_index(const void *p, size_t *sub_idx)
{
  const size_t u = (size_t) (((uintptr_t) p) / (1UL << (13 + 3)));
  if (sub_idx != 0)
  {
    *sub_idx = u % (1UL << 13);
  }
  return u / (1UL << 13);
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_has_any_available(const mi_page_t *page)
{
  ((page != 0) && (page->reserved > 0)) ? ((void) 0) : (_mi_assert_fail("page != NULL && page->reserved > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 867, __func__));
  return (page->used < page->reserved) || (mi_page_thread_free(page) != 0);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
None
----------------------------
***/


void _mi_free_generic(mi_page_t *page, bool is_local, void *p)
{
  if (is_local)
  {
    mi_free_generic_local(page, p);
  }
  else
    mi_free_generic_mt(page, p);
}


/*** DEPENDENCIES:
static void mi_free_generic_mt(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 130, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, block);
}


----------------------------
static void mi_free_generic_local(mi_page_t *page, void *p)
{
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 122, __func__));
  mi_block_t * const block = (mi_page_has_interior_pointers(page)) ? (_mi_page_ptr_unalign(page, p)) : (mi_validate_block_from_ptr(page, p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


----------------------------
None
----------------------------
***/


inline static void _mi_page_unown_unconditional(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 879, __func__));
  (mi_page_thread_id(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_id(page)==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 880, __func__));
  const uintptr_t old = atomic_fetch_and_explicit(&page->xthread_free, ~((uintptr_t) 1), memory_order_acq_rel);
  ((old & 1) == 1) ? ((void) 0) : (_mi_assert_fail("(old&1)==1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 882, __func__));
  (void) old;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}


----------------------------
None
----------------------------
***/


