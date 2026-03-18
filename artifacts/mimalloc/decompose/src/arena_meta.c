static mi_meta_page_t *mi_meta_page_of_ptr(void *p, size_t *block_idx)
{
  mi_meta_page_t *mpage = (mi_meta_page_t *) (((uint8_t *) mi_align_down_ptr(p, 1UL << (13 + 3))) + _mi_os_secure_guard_page_size());
  if (block_idx != 0)
  {
    *block_idx = (((uint8_t *) p) - ((uint8_t *) mpage)) / (1 << (16 - (6 + 3)));
  }
  return mpage;
}


/*** DEPENDENCIES:
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}


----------------------------
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
***/


static void *mi_meta_block_start(mi_meta_page_t *mpage, size_t block_idx)
{
  (_mi_is_aligned(((uint8_t *) mpage) - _mi_os_secure_guard_page_size(), 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned((uint8_t*)mpage - _mi_os_secure_guard_page_size(), MI_META_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 62, __func__));
  (block_idx < ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("block_idx < MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 63, __func__));
  void *p = (((uint8_t *) mpage) - _mi_os_secure_guard_page_size()) + (block_idx * (1 << (16 - (6 + 3))));
  (mpage == mi_meta_page_of_ptr(p, 0)) ? ((void) 0) : (_mi_assert_fail("mpage == mi_meta_page_of_ptr(p,NULL)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 65, __func__));
  return p;
}


/*** DEPENDENCIES:
static mi_meta_page_t *mi_meta_page_of_ptr(void *p, size_t *block_idx)
{
  mi_meta_page_t *mpage = (mi_meta_page_t *) (((uint8_t *) mi_align_down_ptr(p, 1UL << (13 + 3))) + _mi_os_secure_guard_page_size());
  if (block_idx != 0)
  {
    *block_idx = (((uint8_t *) p) - ((uint8_t *) mpage)) / (1 << (16 - (6 + 3)));
  }
  return mpage;
}


----------------------------
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
None
----------------------------
***/


static mi_meta_page_t *mi_meta_page_next(mi_meta_page_t *mpage)
{
  return atomic_load_explicit(&mpage->next, memory_order_acquire);
}


/*** DEPENDENCIES:
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
***/


static mi_meta_page_t *mi_meta_page_zalloc(void)
{
  mi_memid_t memid;
  uint8_t *base = (uint8_t *) _mi_arenas_alloc_aligned(_mi_subproc(), 1UL << (13 + 3), 1UL << (13 + 3), 0, 1, 0 == 0, 0, 0, -1, &memid);
  if (base == 0)
  {
    return 0;
  }
  (_mi_is_aligned(base, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(base,MI_META_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 78, __func__));
  if (!memid.initially_zero)
  {
    _mi_memzero_aligned(base, 1UL << (13 + 3));
  }
  mi_meta_page_t *mpage = (mi_meta_page_t *) (base + _mi_os_secure_guard_page_size());
  mpage->memid = memid;
  mi_bbitmap_init(&mpage->blocks_free, (1UL << (13 + 3)) / (1 << (16 - (6 + 3))), 1);
  const size_t mpage_size = offsetof(mi_meta_page_t, blocks_free) + mi_bbitmap_size((1UL << (13 + 3)) / (1 << (16 - (6 + 3))), 0);
  const size_t info_blocks = _mi_divide_up(mpage_size, 1 << (16 - (6 + 3)));
  const size_t guard_blocks = _mi_divide_up(_mi_os_secure_guard_page_size(), 1 << (16 - (6 + 3)));
  ((info_blocks + (2 * guard_blocks)) < ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("info_blocks + 2*guard_blocks < MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 96, __func__));
  mi_bbitmap_unsafe_setN(&mpage->blocks_free, info_blocks + guard_blocks, (((1UL << (13 + 3)) / (1 << (16 - (6 + 3)))) - info_blocks) - (2 * guard_blocks));
  mi_meta_page_t *old = atomic_load_explicit(&mi_meta_pages, memory_order_acquire);
  do
  {
    atomic_store_explicit(&mpage->next, old, memory_order_release);
  }
  while (!atomic_compare_exchange_weak_explicit(&mi_meta_pages, &old, mpage, memory_order_acq_rel, memory_order_acquire));
  return mpage;
}


/*** DEPENDENCIES:
None
----------------------------
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
static mi_meta_page_t * _Atomic mi_meta_pages = 0
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


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


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
void *_mi_arenas_alloc_aligned(mi_subproc_t *subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (memid != 0) ? ((void) 0) : (_mi_assert_fail("memid != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 482, __func__));
  (size > 0) ? ((void) 0) : (_mi_assert_fail("size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 483, __func__));
  if (((((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (size >= (1 * (1UL << (13 + 3))))) && (size <= ((1 << (6 + 3)) * (1UL << (13 + 3))))) && (alignment <= (1UL << (13 + 3)))) && (align_offset == 0))
  {
    const size_t slice_count = mi_slice_count_of_size(size);
    void *p = mi_arenas_try_alloc(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
    if (p != 0)
    {
      return p;
    }
  }
  void *p = mi_arena_os_alloc_aligned(size, alignment, align_offset, commit, allow_large, req_arena, memid);
  return p;
}


----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
void mi_bbitmap_unsafe_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1482, __func__));
  ((idx + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1483, __func__));
  mi_bchunks_unsafe_setN(&bbitmap->chunks[0], &bbitmap->chunkmap, idx, n);
}


----------------------------
None
----------------------------
***/


void *_mi_meta_zalloc(size_t size, mi_memid_t *pmemid)
{
  (pmemid != 0) ? ((void) 0) : (_mi_assert_fail("pmemid != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 112, __func__));
  size = _mi_align_up(size, 1 << (16 - (6 + 3)));
  if ((size == 0) || (size > (((1 << (6 + 3)) / 8) * (1 << (16 - (6 + 3))))))
  {
    return 0;
  }
  const size_t block_count = _mi_divide_up(size, 1 << (16 - (6 + 3)));
  ((block_count > 0) && (block_count < (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("block_count > 0 && block_count < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 116, __func__));
  mi_meta_page_t *mpage0 = atomic_load_explicit(&mi_meta_pages, memory_order_acquire);
  mi_meta_page_t *mpage = mpage0;
  unsigned int mpage_idx = 0;
  while ((&mpage[mpage_idx]) != 0)
  {
    size_t block_idx;
    if (mi_bbitmap_try_find_and_clearN(&mpage->blocks_free, block_count, 0, &block_idx))
    {
      *pmemid = _mi_memid_create_meta(mpage, block_idx, block_count);
      return mi_meta_block_start(mpage, block_idx);
    }
    else
    {
      mpage_idx = mi_meta_page_next(mpage_idx);
    }
  }

  if (atomic_load_explicit(&mi_meta_pages, memory_order_acquire) != mpage0)
  {
    return _mi_meta_zalloc(size, pmemid);
  }
  mpage_idx = mi_meta_page_zalloc();
  if ((&mpage[mpage_idx]) != 0)
  {
    size_t block_idx;
    if (mi_bbitmap_try_find_and_clearN(&mpage->blocks_free, block_count, 0, &block_idx))
    {
      *pmemid = _mi_memid_create_meta(mpage, block_idx, block_count);
      return mi_meta_block_start(mpage, block_idx);
    }
  }
  return _mi_os_alloc(size, pmemid);
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_bbitmap_try_find_and_clearN(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx)
{
  if (n == 1)
  {
    return mi_bbitmap_try_find_and_clear(bbitmap, tseq, pidx);
  }
  if (n == 8)
  {
    return mi_bbitmap_try_find_and_clear8(bbitmap, tseq, pidx);
  }
  if ((n == 0) || (n > (1 << (6 + 3))))
  {
    return 0;
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bbitmap_try_find_and_clearNX(bbitmap, tseq, n, pidx);
  }
  return mi_bbitmap_try_find_and_clearN_(bbitmap, tseq, n, pidx);
}


----------------------------
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
static mi_meta_page_t * _Atomic mi_meta_pages = 0
----------------------------
static void *mi_meta_block_start(mi_meta_page_t *mpage, size_t block_idx)
{
  (_mi_is_aligned(((uint8_t *) mpage) - _mi_os_secure_guard_page_size(), 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned((uint8_t*)mpage - _mi_os_secure_guard_page_size(), MI_META_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 62, __func__));
  (block_idx < ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("block_idx < MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 63, __func__));
  void *p = (((uint8_t *) mpage) - _mi_os_secure_guard_page_size()) + (block_idx * (1 << (16 - (6 + 3))));
  (mpage == mi_meta_page_of_ptr(p, 0)) ? ((void) 0) : (_mi_assert_fail("mpage == mi_meta_page_of_ptr(p,NULL)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 65, __func__));
  return p;
}


----------------------------
static mi_meta_page_t *mi_meta_page_zalloc(void)
{
  mi_memid_t memid;
  uint8_t *base = (uint8_t *) _mi_arenas_alloc_aligned(_mi_subproc(), 1UL << (13 + 3), 1UL << (13 + 3), 0, 1, 0 == 0, 0, 0, -1, &memid);
  if (base == 0)
  {
    return 0;
  }
  (_mi_is_aligned(base, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(base,MI_META_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 78, __func__));
  if (!memid.initially_zero)
  {
    _mi_memzero_aligned(base, 1UL << (13 + 3));
  }
  mi_meta_page_t *mpage = (mi_meta_page_t *) (base + _mi_os_secure_guard_page_size());
  mpage->memid = memid;
  mi_bbitmap_init(&mpage->blocks_free, (1UL << (13 + 3)) / (1 << (16 - (6 + 3))), 1);
  const size_t mpage_size = offsetof(mi_meta_page_t, blocks_free) + mi_bbitmap_size((1UL << (13 + 3)) / (1 << (16 - (6 + 3))), 0);
  const size_t info_blocks = _mi_divide_up(mpage_size, 1 << (16 - (6 + 3)));
  const size_t guard_blocks = _mi_divide_up(_mi_os_secure_guard_page_size(), 1 << (16 - (6 + 3)));
  ((info_blocks + (2 * guard_blocks)) < ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("info_blocks + 2*guard_blocks < MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 96, __func__));
  mi_bbitmap_unsafe_setN(&mpage->blocks_free, info_blocks + guard_blocks, (((1UL << (13 + 3)) / (1 << (16 - (6 + 3)))) - info_blocks) - (2 * guard_blocks));
  mi_meta_page_t *old = atomic_load_explicit(&mi_meta_pages, memory_order_acquire);
  do
  {
    atomic_store_explicit(&mpage->next, old, memory_order_release);
  }
  while (!atomic_compare_exchange_weak_explicit(&mi_meta_pages, &old, mpage, memory_order_acq_rel, memory_order_acquire));
  return mpage;
}


----------------------------
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
static mi_meta_page_t *mi_meta_page_next(mi_meta_page_t *mpage)
{
  return atomic_load_explicit(&mpage->next, memory_order_acquire);
}


----------------------------
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


----------------------------
void *_mi_os_alloc(size_t size, mi_memid_t *memid)
{
  *memid = _mi_memid_none();
  if (size == 0)
  {
    return 0;
  }
  size = _mi_os_good_alloc_size(size);
  bool os_is_large = 0;
  bool os_is_zero = 0;
  void *p = mi_os_prim_alloc(size, 0, 1, 0, &os_is_large, &os_is_zero);
  if (p == 0)
  {
    return 0;
  }
  *memid = _mi_memid_create_os(p, size, 1, os_is_zero, os_is_large);
  (memid->mem.os.size >= size) ? ((void) 0) : (_mi_assert_fail("memid->mem.os.size >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 358, __func__));
  (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 359, __func__));
  return p;
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


bool _mi_meta_is_meta_page(void *p)
{
  mi_meta_page_t *mpage0 = atomic_load_explicit(&mi_meta_pages, memory_order_acquire);
  mi_meta_page_t *mpage = mpage0;
  unsigned int mpage_idx = 0;
  while ((&mpage[mpage_idx]) != 0)
  {
    if (((void *) mpage) == p)
    {
      return 1;
    }
    mpage_idx = mi_meta_page_next(mpage_idx);
  }

  return 0;
}


/*** DEPENDENCIES:
static mi_meta_page_t *mi_meta_page_next(mi_meta_page_t *mpage)
{
  return atomic_load_explicit(&mpage->next, memory_order_acquire);
}


----------------------------
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
static mi_meta_page_t * _Atomic mi_meta_pages = 0
----------------------------
***/


