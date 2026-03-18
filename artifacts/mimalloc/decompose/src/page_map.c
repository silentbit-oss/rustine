inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
static _Atomic mi_bfield_t mi_page_map_commit
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void *mi_page_map_max_address
----------------------------
extern _Atomic mi_submap_t *_mi_page_map
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
inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}


----------------------------
None
----------------------------
***/


bool mi_is_in_heap_region(const void *p)
{
  return _mi_safe_ptr_page(p) != 0;
}


/*** DEPENDENCIES:
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
***/


static void mi_page_map_cannot_commit(void)
{
  _mi_warning_message("unable to commit the allocation page-map on-demand\n");
}


/*** DEPENDENCIES:
None
----------------------------
***/


static bool mi_page_map_ensure_committed(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 215, __func__));
  size_t bit_idx;
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, &bit_idx))), 0))
  {
    uint8_t *start = (uint8_t *) (&_mi_page_map[bit_idx * ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)))]);
    if (!_mi_os_commit(start, ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3))) * (sizeof(mi_submap_t)), 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
    atomic_fetch_or_explicit(&mi_page_map_commit, 1UL << bit_idx, memory_order_acq_rel);
  }
  *submap = atomic_load_explicit(&_mi_page_map[idx], memory_order_acquire);
  return 1;
}


/*** DEPENDENCIES:
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
static void mi_page_map_cannot_commit(void)
{
  _mi_warning_message("unable to commit the allocation page-map on-demand\n");
}


----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
static _Atomic mi_bfield_t mi_page_map_commit
----------------------------
inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}


----------------------------
None
----------------------------
***/


static bool mi_page_map_ensure_submap_at(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 313, __func__));
  mi_submap_t sub = 0;
  if (!mi_page_map_ensure_committed(idx, &sub))
  {
    return 0;
  }
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    mi_memid_t memid;
    const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
    sub = (mi_submap_t) _mi_os_zalloc(submap_size, &memid);
    if (sub == 0)
    {
      _mi_warning_message("internal error: unable to extend the page map\n");
      return 0;
    }
    mi_submap_t expect = 0;
    if (!atomic_compare_exchange_strong_explicit(&_mi_page_map[idx], &expect, sub, memory_order_acq_rel, memory_order_acquire))
    {
      _mi_os_free(sub, submap_size, memid);
      sub = expect;
    }
  }
  (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 334, __func__));
  *submap = sub;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid, 0);
}


----------------------------
None
----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
static bool mi_page_map_ensure_committed(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 215, __func__));
  size_t bit_idx;
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, &bit_idx))), 0))
  {
    uint8_t *start = (uint8_t *) (&_mi_page_map[bit_idx * ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)))]);
    if (!_mi_os_commit(start, ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3))) * (sizeof(mi_submap_t)), 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
    atomic_fetch_or_explicit(&mi_page_map_commit, 1UL << bit_idx, memory_order_acq_rel);
  }
  *submap = atomic_load_explicit(&_mi_page_map[idx], memory_order_acquire);
  return 1;
}


----------------------------
void *_mi_os_zalloc(size_t size, mi_memid_t *memid)
{
  void *p = _mi_os_alloc(size, memid);
  return mi_os_ensure_zero(p, size, memid);
}


----------------------------
None
----------------------------
***/


static bool mi_page_map_set_range_prim(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  while (slice_count > 0)
  {
    mi_submap_t sub = 0;
    if (!mi_page_map_ensure_submap_at(idx, &sub))
    {
      return 0;
    }
    ;
    (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 346, __func__));
    while ((slice_count > 0) && (sub_idx < (1UL << 13)))
    {
      sub[sub_idx] = page;
      slice_count -= 1;
      sub_idx += 1;
    }

    idx += 1;
    sub_idx = 0;
  }

  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_page_map_ensure_submap_at(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 313, __func__));
  mi_submap_t sub = 0;
  if (!mi_page_map_ensure_committed(idx, &sub))
  {
    return 0;
  }
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    mi_memid_t memid;
    const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
    sub = (mi_submap_t) _mi_os_zalloc(submap_size, &memid);
    if (sub == 0)
    {
      _mi_warning_message("internal error: unable to extend the page map\n");
      return 0;
    }
    mi_submap_t expect = 0;
    if (!atomic_compare_exchange_strong_explicit(&_mi_page_map[idx], &expect, sub, memory_order_acq_rel, memory_order_acquire))
    {
      _mi_os_free(sub, submap_size, memid);
      sub = expect;
    }
  }
  (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 334, __func__));
  *submap = sub;
  return 1;
}


----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
None
----------------------------
***/


static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
static bool mi_page_map_set_range_prim(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  while (slice_count > 0)
  {
    mi_submap_t sub = 0;
    if (!mi_page_map_ensure_submap_at(idx, &sub))
    {
      return 0;
    }
    ;
    (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 346, __func__));
    while ((slice_count > 0) && (sub_idx < (1UL << 13)))
    {
      sub[sub_idx] = page;
      slice_count -= 1;
      sub_idx += 1;
    }

    idx += 1;
    sub_idx = 0;
  }

  return 1;
}


----------------------------
None
----------------------------
***/


static size_t mi_page_map_get_idx(mi_page_t *page, size_t *sub_idx, size_t *slice_count)
{
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  if (page_size > ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))))
  {
    page_size = ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))) - (1UL << (13 + 3));
  }
  *slice_count = mi_slice_count_of_size(page_size) + ((page_start - ((uint8_t *) page)) / (1UL << (13 + 3)));
  return _mi_page_map_index(page, sub_idx);
}


/*** DEPENDENCIES:
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
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


void _mi_page_map_unregister(mi_page_t *page)
{
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 393, __func__));
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 394, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 395, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}


/*** DEPENDENCIES:
None
----------------------------
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
static size_t mi_page_map_get_idx(mi_page_t *page, size_t *sub_idx, size_t *slice_count)
{
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  if (page_size > ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))))
  {
    page_size = ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))) - (1UL << (13 + 3));
  }
  *slice_count = mi_slice_count_of_size(page_size) + ((page_start - ((uint8_t *) page)) / (1UL << (13 + 3)));
  return _mi_page_map_index(page, sub_idx);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


bool _mi_page_map_init(void)
{
  size_t vbits = (size_t) mi_option_get_clamp(mi_option_max_vabits, 0, (1 << 3) * 8);
  if (vbits == 0)
  {
    vbits = _mi_os_virtual_address_bits();
  }
  (48 >= vbits) ? ((void) 0) : (_mi_assert_fail("MI_MAX_VABITS >= vbits", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 240, __func__));
  mi_page_map_max_address = (void *) ((vbits >= ((1 << 3) * 8)) ? ((SIZE_MAX - (1UL << (13 + 3))) + 1) : (1UL << vbits));
  mi_page_map_count = 1UL << ((vbits - 13) - (13 + 3));
  (mi_page_map_count <= (1UL << ((48 - 13) - (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("mi_page_map_count <= MI_PAGE_MAP_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 243, __func__));
  const size_t os_page_size = _mi_os_page_size();
  const size_t page_map_size = _mi_align_up(mi_page_map_count * (sizeof(mi_page_t **)), os_page_size);
  const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
  const size_t reserve_size = page_map_size + submap_size;
  const bool commit = ((page_map_size <= (64 * 1024UL)) || mi_option_is_enabled(mi_option_pagemap_commit)) || _mi_os_has_overcommit();
  _mi_page_map = (mi_page_t ** *) _mi_os_alloc_aligned(reserve_size, 1, commit, 1, &mi_page_map_memid);
  if (_mi_page_map == 0)
  {
    _mi_error_message(12, "unable to reserve virtual memory for the page map (%zu KiB)\n", page_map_size / 1024UL);
    return 0;
  }
  if (mi_page_map_memid.initially_committed && (!mi_page_map_memid.initially_zero))
  {
    _mi_warning_message("internal: the page map was committed but not zero initialized!\n");
    _mi_memzero_aligned(_mi_page_map, page_map_size);
  }
  atomic_store_explicit(&mi_page_map_commit, (mi_page_map_memid.initially_committed) ? (~0UL) : (0UL), memory_order_release);
  mi_page_t ** const sub0 = (mi_page_t **) (((uint8_t *) _mi_page_map) + page_map_size);
  if (!mi_page_map_memid.initially_committed)
  {
    if (!_mi_os_commit(sub0, submap_size, 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
  }
  if (!mi_page_map_memid.initially_zero)
  {
    _mi_memzero_aligned(sub0, submap_size);
  }
  mi_submap_t nullsub = 0;
  if (!mi_page_map_ensure_committed(0, &nullsub))
  {
    mi_page_map_cannot_commit();
    return 0;
  }
  atomic_store_explicit(&_mi_page_map[0], sub0, memory_order_release);
  (_mi_ptr_page(0) == 0) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(NULL)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 283, __func__));
  return 1;
}


/*** DEPENDENCIES:
static _Atomic mi_bfield_t mi_page_map_commit
----------------------------
static bool mi_page_map_ensure_committed(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 215, __func__));
  size_t bit_idx;
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, &bit_idx))), 0))
  {
    uint8_t *start = (uint8_t *) (&_mi_page_map[bit_idx * ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)))]);
    if (!_mi_os_commit(start, ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3))) * (sizeof(mi_submap_t)), 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
    atomic_fetch_or_explicit(&mi_page_map_commit, 1UL << bit_idx, memory_order_acq_rel);
  }
  *submap = atomic_load_explicit(&_mi_page_map[idx], memory_order_acquire);
  return 1;
}


----------------------------
static void *mi_page_map_max_address
----------------------------
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
static void mi_page_map_cannot_commit(void)
{
  _mi_warning_message("unable to commit the allocation page-map on-demand\n");
}


----------------------------
size_t _mi_os_virtual_address_bits(void)
{
  const size_t vbits = mi_os_mem_config.virtual_address_bits;
  (vbits <= 48) ? ((void) 0) : (_mi_assert_fail("vbits <= MI_MAX_VABITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 61, __func__));
  return vbits;
}


----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


----------------------------
static size_t mi_page_map_count
----------------------------
None
----------------------------
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
void *_mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t *memid)
{
  (void) (&_mi_os_get_aligned_hint);
  *memid = _mi_memid_none();
  if (size == 0)
  {
    return 0;
  }
  size = _mi_os_good_alloc_size(size);
  alignment = _mi_align_up(alignment, _mi_os_page_size());
  bool os_is_large = 0;
  bool os_is_zero = 0;
  void *os_base = 0;
  void *p = mi_os_prim_alloc_aligned(size, alignment, commit, allow_large, &os_is_large, &os_is_zero, &os_base);
  if (p == 0)
  {
    return 0;
  }
  *memid = _mi_memid_create_os(p, size, commit, os_is_zero, os_is_large);
  memid->mem.os.base = os_base;
  memid->mem.os.size += ((uint8_t *) p) - ((uint8_t *) os_base);
  (memid->mem.os.size >= size) ? ((void) 0) : (_mi_assert_fail("memid->mem.os.size >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 381, __func__));
  (_mi_is_aligned(p, alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(p,alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 382, __func__));
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 383, __func__));
  }
  return p;
}


----------------------------
static mi_memid_t mi_page_map_memid
----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
None
----------------------------
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
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


bool _mi_page_map_register(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 379, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 380, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 381, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    if (!_mi_page_map_init())
    {
      return 0;
    }
  }
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 385, __func__));
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  return mi_page_map_set_range(page, idx, sub_idx, slice_count);
}


/*** DEPENDENCIES:
None
----------------------------
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
static size_t mi_page_map_get_idx(mi_page_t *page, size_t *sub_idx, size_t *slice_count)
{
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  if (page_size > ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))))
  {
    page_size = ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))) - (1UL << (13 + 3));
  }
  *slice_count = mi_slice_count_of_size(page_size) + ((page_start - ((uint8_t *) page)) / (1UL << (13 + 3)));
  return _mi_page_map_index(page, sub_idx);
}


----------------------------
bool _mi_page_map_init(void)
{
  size_t vbits = (size_t) mi_option_get_clamp(mi_option_max_vabits, 0, (1 << 3) * 8);
  if (vbits == 0)
  {
    vbits = _mi_os_virtual_address_bits();
  }
  (48 >= vbits) ? ((void) 0) : (_mi_assert_fail("MI_MAX_VABITS >= vbits", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 240, __func__));
  mi_page_map_max_address = (void *) ((vbits >= ((1 << 3) * 8)) ? ((SIZE_MAX - (1UL << (13 + 3))) + 1) : (1UL << vbits));
  mi_page_map_count = 1UL << ((vbits - 13) - (13 + 3));
  (mi_page_map_count <= (1UL << ((48 - 13) - (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("mi_page_map_count <= MI_PAGE_MAP_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 243, __func__));
  const size_t os_page_size = _mi_os_page_size();
  const size_t page_map_size = _mi_align_up(mi_page_map_count * (sizeof(mi_page_t **)), os_page_size);
  const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
  const size_t reserve_size = page_map_size + submap_size;
  const bool commit = ((page_map_size <= (64 * 1024UL)) || mi_option_is_enabled(mi_option_pagemap_commit)) || _mi_os_has_overcommit();
  _mi_page_map = (mi_page_t ** *) _mi_os_alloc_aligned(reserve_size, 1, commit, 1, &mi_page_map_memid);
  if (_mi_page_map == 0)
  {
    _mi_error_message(12, "unable to reserve virtual memory for the page map (%zu KiB)\n", page_map_size / 1024UL);
    return 0;
  }
  if (mi_page_map_memid.initially_committed && (!mi_page_map_memid.initially_zero))
  {
    _mi_warning_message("internal: the page map was committed but not zero initialized!\n");
    _mi_memzero_aligned(_mi_page_map, page_map_size);
  }
  atomic_store_explicit(&mi_page_map_commit, (mi_page_map_memid.initially_committed) ? (~0UL) : (0UL), memory_order_release);
  mi_page_t ** const sub0 = (mi_page_t **) (((uint8_t *) _mi_page_map) + page_map_size);
  if (!mi_page_map_memid.initially_committed)
  {
    if (!_mi_os_commit(sub0, submap_size, 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
  }
  if (!mi_page_map_memid.initially_zero)
  {
    _mi_memzero_aligned(sub0, submap_size);
  }
  mi_submap_t nullsub = 0;
  if (!mi_page_map_ensure_committed(0, &nullsub))
  {
    mi_page_map_cannot_commit();
    return 0;
  }
  atomic_store_explicit(&_mi_page_map[0], sub0, memory_order_release);
  (_mi_ptr_page(0) == 0) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(NULL)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 283, __func__));
  return 1;
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 289, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 290, __func__));
  if (_mi_page_map == 0)
  {
    return;
  }
  for (size_t idx = 1; idx < mi_page_map_count; idx += 1)
  {
    if (mi_page_map_is_committed(idx, 0))
    {
      mi_submap_t sub = _mi_page_map_at(idx);
      if (sub != 0)
      {
        mi_memid_t memid = _mi_memid_create_os(sub, (1UL << 13) * (sizeof(mi_page_t *)), 1, 0, 0);
        _mi_os_free_ex(memid.mem.os.base, memid.mem.os.size, 1, memid, subproc);
        atomic_store_explicit(&_mi_page_map[idx], 0, memory_order_release);
      }
    }
  }

  _mi_os_free_ex(_mi_page_map, mi_page_map_memid.mem.os.size, 1, mi_page_map_memid, subproc);
  _mi_page_map = 0;
  mi_page_map_count = 0;
  mi_page_map_memid = _mi_memid_none();
  mi_page_map_max_address = 0;
  atomic_store_explicit(&mi_page_map_commit, 0, memory_order_release);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
extern _Atomic mi_submap_t *_mi_page_map
----------------------------
inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}


----------------------------
static void *mi_page_map_max_address
----------------------------
typedef mi_page_t **mi_submap_t
----------------------------
static _Atomic mi_bfield_t mi_page_map_commit
----------------------------
inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}


----------------------------
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


----------------------------
void _mi_os_free_ex(void *addr, size_t size, bool still_committed, mi_memid_t memid, mi_subproc_t *subproc)
{
  if (mi_memkind_is_os(memid.memkind))
  {
    size_t csize = memid.mem.os.size;
    if (csize == 0)
    {
      csize = _mi_os_good_alloc_size(size);
    }
    (csize >= size) ? ((void) 0) : (_mi_assert_fail("csize >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 191, __func__));
    size_t commit_size = (still_committed) ? (csize) : (0);
    void *base = addr;
    unsigned int base_idx = 0;
    if (memid.mem.os.base != (&base[base_idx]))
    {
      (memid.mem.os.base <= addr) ? ((void) 0) : (_mi_assert_fail("memid.mem.os.base <= addr", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 196, __func__));
      base_idx = memid.mem.os.base_idx;
      const size_t diff = ((uint8_t *) addr) - ((uint8_t *) memid.mem.os.base);
      if (memid.mem.os.size == 0)
      {
        csize += diff;
      }
      if (still_committed)
      {
        commit_size -= diff;
      }
    }
    if (memid.memkind == MI_MEM_OS_HUGE)
    {
      (memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("memid.is_pinned", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 208, __func__));
      mi_os_free_huge_os_pages(base, csize, subproc);
    }
    else
    {
      mi_os_prim_free(base, csize, (still_committed) ? (commit_size) : (0), subproc);
    }
  }
  else
  {
    (memid.memkind < MI_MEM_OS) ? ((void) 0) : (_mi_assert_fail("memid.memkind < MI_MEM_OS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 217, __func__));
  }
}


----------------------------
static size_t mi_page_map_count
----------------------------
static mi_memid_t mi_page_map_memid
----------------------------
None
----------------------------
***/


void _mi_page_map_unregister_range(void *start, size_t size)
{
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  const size_t slice_count = _mi_divide_up(size, 1UL << (13 + 3));
  size_t sub_idx;
  const uintptr_t idx = _mi_page_map_index(start, &sub_idx);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
extern _Atomic mi_submap_t *_mi_page_map
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
static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}


----------------------------
***/


