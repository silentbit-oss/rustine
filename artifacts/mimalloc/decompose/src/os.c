size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


/*** DEPENDENCIES:
***/


void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size)
{
  (void) try_alignment;
  (void) size;
  return 0;
}


/*** DEPENDENCIES:
***/


size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


/*** DEPENDENCIES:
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
***/


static void *mi_os_page_align_areax(bool conservative, void *addr, size_t size, size_t *newsize)
{
  ((addr != 0) && (size > 0)) ? ((void) 0) : (_mi_assert_fail("addr != NULL && size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 451, __func__));
  if (newsize != 0)
  {
    *newsize = 0;
  }
  if ((size == 0) || (addr == 0))
  {
    return 0;
  }
  void *start = (conservative) ? (_mi_align_up_ptr(addr, _mi_os_page_size())) : (mi_align_down_ptr(addr, _mi_os_page_size()));
  void *end = (conservative) ? (mi_align_down_ptr(((uint8_t *) addr) + size, _mi_os_page_size())) : (_mi_align_up_ptr(((uint8_t *) addr) + size, _mi_os_page_size()));
  ptrdiff_t diff = ((uint8_t *) end) - ((uint8_t *) start);
  if (diff <= 0)
  {
    return 0;
  }
  ((conservative && (((size_t) diff) <= size)) || ((!conservative) && (((size_t) diff) >= size))) ? ((void) 0) : (_mi_assert_fail("(conservative && (size_t)diff <= size) || (!conservative && (size_t)diff >= size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 463, __func__));
  if (newsize != 0)
  {
    *newsize = (size_t) diff;
  }
  return start;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}


----------------------------
inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}


----------------------------
None
----------------------------
***/


static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}


/*** DEPENDENCIES:
static void *mi_os_page_align_areax(bool conservative, void *addr, size_t size, size_t *newsize)
{
  ((addr != 0) && (size > 0)) ? ((void) 0) : (_mi_assert_fail("addr != NULL && size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 451, __func__));
  if (newsize != 0)
  {
    *newsize = 0;
  }
  if ((size == 0) || (addr == 0))
  {
    return 0;
  }
  void *start = (conservative) ? (_mi_align_up_ptr(addr, _mi_os_page_size())) : (mi_align_down_ptr(addr, _mi_os_page_size()));
  void *end = (conservative) ? (mi_align_down_ptr(((uint8_t *) addr) + size, _mi_os_page_size())) : (_mi_align_up_ptr(((uint8_t *) addr) + size, _mi_os_page_size()));
  ptrdiff_t diff = ((uint8_t *) end) - ((uint8_t *) start);
  if (diff <= 0)
  {
    return 0;
  }
  ((conservative && (((size_t) diff) <= size)) || ((!conservative) && (((size_t) diff) >= size))) ? ((void) 0) : (_mi_assert_fail("(conservative && (size_t)diff <= size) || (!conservative && (size_t)diff >= size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 463, __func__));
  if (newsize != 0)
  {
    *newsize = (size_t) diff;
  }
  return start;
}


----------------------------
***/


bool _mi_os_reset(void *addr, size_t size)
{
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  __mi_stat_increase_mt(&_mi_subproc()->stats.reset, csize);
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.reset_calls, 1);
  memset(start, 0, csize);
  int err = _mi_prim_reset(start, csize);
  if (err != 0)
  {
    _mi_warning_message("cannot reset OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  return err == 0;
}


/*** DEPENDENCIES:
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
int _mi_prim_reset(void *start, size_t size)
{
  int err = 0;
  err = unix_madvise(start, size, MADV_DONTNEED);
  return err;
}


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}


----------------------------
None
----------------------------
***/


static bool mi_os_decommit_ex(void *addr, size_t size, bool *needs_recommit, size_t stat_size)
{
  (needs_recommit != 0) ? ((void) 0) : (_mi_assert_fail("needs_recommit!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 506, __func__));
  __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, stat_size);
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  *needs_recommit = 1;
  int err = _mi_prim_decommit(start, csize, needs_recommit);
  if (err != 0)
  {
    _mi_warning_message("cannot decommit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  (err == 0) ? ((void) 0) : (_mi_assert_fail("err == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 520, __func__));
  return err == 0;
}


/*** DEPENDENCIES:
None
----------------------------
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, -((int64_t) amount));
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
int _mi_prim_decommit(void *start, size_t size, bool *needs_recommit)
{
  int err = 0;
  err = unix_madvise(start, size, MADV_DONTNEED);
  *needs_recommit = 1;
  mprotect(start, size, PROT_NONE);
  return err;
}


----------------------------
static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}


----------------------------
None
----------------------------
***/


bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stat_size, mi_commit_fun_t *commit_fun, void *commit_fun_arg)
{
  if (mi_option_get(mi_option_purge_delay) < 0)
  {
    return 0;
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.purge_calls, 1);
  __mi_stat_increase_mt(&_mi_subproc()->stats.purged, size);
  if (commit_fun != 0)
  {
    bool decommitted = (*commit_fun)(0, p, size, 0, commit_fun_arg);
    return decommitted;
  }
  else
    if (mi_option_is_enabled(mi_option_purge_decommits) && (!_mi_preloading()))
  {
    bool needs_recommit = 1;
    mi_os_decommit_ex(p, size, &needs_recommit, stat_size);
    return needs_recommit;
  }
  else
  {
    if (allow_reset)
    {
      _mi_os_reset(p, size);
    }
    return 0;
  }
}


/*** DEPENDENCIES:
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg)
----------------------------
bool _mi_preloading(void)
{
  return os_preloading;
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
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
static bool mi_os_decommit_ex(void *addr, size_t size, bool *needs_recommit, size_t stat_size)
{
  (needs_recommit != 0) ? ((void) 0) : (_mi_assert_fail("needs_recommit!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 506, __func__));
  __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, stat_size);
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  *needs_recommit = 1;
  int err = _mi_prim_decommit(start, csize, needs_recommit);
  if (err != 0)
  {
    _mi_warning_message("cannot decommit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  (err == 0) ? ((void) 0) : (_mi_assert_fail("err == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 520, __func__));
  return err == 0;
}


----------------------------
bool _mi_os_reset(void *addr, size_t size)
{
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  __mi_stat_increase_mt(&_mi_subproc()->stats.reset, csize);
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.reset_calls, 1);
  memset(start, 0, csize);
  int err = _mi_prim_reset(start, csize);
  if (err != 0)
  {
    _mi_warning_message("cannot reset OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  return err == 0;
}


----------------------------
None
----------------------------
***/


size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
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
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
***/


static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


/*** DEPENDENCIES:
None
----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
None
----------------------------
int _mi_prim_free(void *addr, size_t size)
{
  if (size == 0)
  {
    return 0;
  }
  bool err = munmap(addr, size) == (-1);
  return (err) ? (errno) : (0);
}


----------------------------
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, -((int64_t) amount));
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
None
----------------------------
***/


static void mi_os_free_huge_os_pages(void *p, size_t size, mi_subproc_t *subproc)
{
  if ((p == 0) || (size == 0))
  {
    return;
  }
  uint8_t *base = (uint8_t *) p;
  unsigned int base_idx = 0;
  while (size >= ((1024UL * 1024UL) * 1024UL))
  {
    mi_os_prim_free(base, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL, subproc);
    size -= (1024UL * 1024UL) * 1024UL;
    base_idx += (1024UL * 1024UL) * 1024UL;
  }

}


/*** DEPENDENCIES:
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
static void mi_os_free_huge_os_pages(void *p, size_t size, mi_subproc_t *subproc)
{
  if ((p == 0) || (size == 0))
  {
    return;
  }
  uint8_t *base = (uint8_t *) p;
  unsigned int base_idx = 0;
  while (size >= ((1024UL * 1024UL) * 1024UL))
  {
    mi_os_prim_free(base, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL, subproc);
    size -= (1024UL * 1024UL) * 1024UL;
    base_idx += (1024UL * 1024UL) * 1024UL;
  }

}


----------------------------
size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
}


----------------------------
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


----------------------------
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}


----------------------------
None
----------------------------
***/


void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid, 0);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size)
{
  if (is_zero != 0)
  {
    *is_zero = 0;
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.commit_calls, 1);
  size_t csize;
  void *start = mi_os_page_align_areax(0, addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  bool os_is_zero = 0;
  int err = _mi_prim_commit(start, csize, &os_is_zero);
  if (err != 0)
  {
    _mi_warning_message("cannot commit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
    return 0;
  }
  if (os_is_zero && (is_zero != 0))
  {
    *is_zero = 1;
    ;
  }
  __mi_stat_increase_mt(&_mi_subproc()->stats.committed, stat_size);
  return 1;
}


/*** DEPENDENCIES:
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
static void *mi_os_page_align_areax(bool conservative, void *addr, size_t size, size_t *newsize)
{
  ((addr != 0) && (size > 0)) ? ((void) 0) : (_mi_assert_fail("addr != NULL && size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 451, __func__));
  if (newsize != 0)
  {
    *newsize = 0;
  }
  if ((size == 0) || (addr == 0))
  {
    return 0;
  }
  void *start = (conservative) ? (_mi_align_up_ptr(addr, _mi_os_page_size())) : (mi_align_down_ptr(addr, _mi_os_page_size()));
  void *end = (conservative) ? (mi_align_down_ptr(((uint8_t *) addr) + size, _mi_os_page_size())) : (_mi_align_up_ptr(((uint8_t *) addr) + size, _mi_os_page_size()));
  ptrdiff_t diff = ((uint8_t *) end) - ((uint8_t *) start);
  if (diff <= 0)
  {
    return 0;
  }
  ((conservative && (((size_t) diff) <= size)) || ((!conservative) && (((size_t) diff) >= size))) ? ((void) 0) : (_mi_assert_fail("(conservative && (size_t)diff <= size) || (!conservative && (size_t)diff >= size)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 463, __func__));
  if (newsize != 0)
  {
    *newsize = (size_t) diff;
  }
  return start;
}


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
int _mi_prim_commit(void *start, size_t size, bool *is_zero)
{
  *is_zero = 0;
  int err = mprotect(start, size, PROT_READ | PROT_WRITE);
  if (err != 0)
  {
    err = errno;
    unix_mprotect_hint(err);
  }
  return err;
}


----------------------------
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
None
----------------------------
***/


bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


/*** DEPENDENCIES:
bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size)
{
  if (is_zero != 0)
  {
    *is_zero = 0;
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.commit_calls, 1);
  size_t csize;
  void *start = mi_os_page_align_areax(0, addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  bool os_is_zero = 0;
  int err = _mi_prim_commit(start, csize, &os_is_zero);
  if (err != 0)
  {
    _mi_warning_message("cannot commit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
    return 0;
  }
  if (os_is_zero && (is_zero != 0))
  {
    *is_zero = 1;
    ;
  }
  __mi_stat_increase_mt(&_mi_subproc()->stats.committed, stat_size);
  return 1;
}


----------------------------
***/


static void *mi_os_ensure_zero(void *p, size_t size, mi_memid_t *memid)
{
  if ((p == 0) || (size == 0))
  {
    return p;
  }
  if (!memid->initially_committed)
  {
    bool is_zero = 0;
    if (!_mi_os_commit(p, size, &is_zero))
    {
      _mi_os_free(p, size, *memid);
      return 0;
    }
    memid->initially_committed = 1;
  }
  if (memid->initially_zero)
  {
    return p;
  }
  _mi_memzero_aligned(p, size);
  memid->initially_zero = 1;
  return p;
}


/*** DEPENDENCIES:
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid, 0);
}


----------------------------
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
None
----------------------------
***/


bool _mi_os_use_large_page(size_t size, size_t alignment)
{
  if ((mi_os_mem_config.large_page_size == 0) || (!mi_option_is_enabled(mi_option_allow_large_os_pages)))
  {
    return 0;
  }
  return ((size % mi_os_mem_config.large_page_size) == 0) && ((alignment % mi_os_mem_config.large_page_size) == 0);
}


/*** DEPENDENCIES:
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
None
----------------------------
***/


bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


/*** DEPENDENCIES:
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
***/


static void *mi_os_prim_alloc_at(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 233, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 234, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 235, __func__));
  if (size == 0)
  {
    return 0;
  }
  if (!commit)
  {
    allow_large = 0;
  }
  if (try_alignment == 0)
  {
    try_alignment = 1;
  }
  *is_zero = 0;
  void *p = 0;
  int err = _mi_prim_alloc(hint_addr, size, try_alignment, commit, allow_large, is_large, is_zero, &p);
  if (err != 0)
  {
    _mi_warning_message("unable to allocate OS memory (error: %d (0x%x), addr: %p, size: 0x%zx bytes, align: 0x%zx, commit: %d, allow large: %d)\n", err, err, hint_addr, size, try_alignment, commit, allow_large);
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.mmap_calls, 1);
  if (p != 0)
  {
    __mi_stat_increase_mt(&_mi_subproc()->stats.reserved, size);
    if (commit)
    {
      __mi_stat_increase_mt(&_mi_subproc()->stats.committed, size);
    }
  }
  return p;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
None
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
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
int _mi_prim_alloc(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **addr)
{
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/prim/unix/prim.c", 418, __func__));
  (commit || (!allow_large)) ? ((void) 0) : (_mi_assert_fail("commit || !allow_large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/prim/unix/prim.c", 419, __func__));
  (try_alignment > 0) ? ((void) 0) : (_mi_assert_fail("try_alignment > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/prim/unix/prim.c", 420, __func__));
  if (((((hint_addr == 0) && (size >= (8 * (2 * (1024UL * 1024UL))))) && (try_alignment > 1)) && _mi_is_power_of_two(try_alignment)) && (try_alignment < (2 * (1024UL * 1024UL))))
  {
    try_alignment = 2 * (1024UL * 1024UL);
  }
  *is_zero = 1;
  int protect_flags = (commit) ? (PROT_WRITE | PROT_READ) : (PROT_NONE);
  *addr = unix_mmap(hint_addr, size, try_alignment, protect_flags, 0, allow_large, is_large);
  return ((*addr) != 0) ? (0) : (errno);
}


----------------------------
None
----------------------------
***/


static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
}


/*** DEPENDENCIES:
static void *mi_os_prim_alloc_at(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 233, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 234, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 235, __func__));
  if (size == 0)
  {
    return 0;
  }
  if (!commit)
  {
    allow_large = 0;
  }
  if (try_alignment == 0)
  {
    try_alignment = 1;
  }
  *is_zero = 0;
  void *p = 0;
  int err = _mi_prim_alloc(hint_addr, size, try_alignment, commit, allow_large, is_large, is_zero, &p);
  if (err != 0)
  {
    _mi_warning_message("unable to allocate OS memory (error: %d (0x%x), addr: %p, size: 0x%zx bytes, align: 0x%zx, commit: %d, allow large: %d)\n", err, err, hint_addr, size, try_alignment, commit, allow_large);
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.mmap_calls, 1);
  if (p != 0)
  {
    __mi_stat_increase_mt(&_mi_subproc()->stats.reserved, size);
    if (commit)
    {
      __mi_stat_increase_mt(&_mi_subproc()->stats.committed, size);
    }
  }
  return p;
}


----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
}


----------------------------
size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
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
None
----------------------------
***/


void *_mi_os_zalloc(size_t size, mi_memid_t *memid)
{
  void *p = _mi_os_alloc(size, memid);
  return mi_os_ensure_zero(p, size, memid);
}


/*** DEPENDENCIES:
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
static void *mi_os_ensure_zero(void *p, size_t size, mi_memid_t *memid)
{
  if ((p == 0) || (size == 0))
  {
    return p;
  }
  if (!memid->initially_committed)
  {
    bool is_zero = 0;
    if (!_mi_os_commit(p, size, &is_zero))
    {
      _mi_os_free(p, size, *memid);
      return 0;
    }
    memid->initially_committed = 1;
  }
  if (memid->initially_zero)
  {
    return p;
  }
  _mi_memzero_aligned(p, size);
  memid->initially_zero = 1;
  return p;
}


----------------------------
None
----------------------------
***/


bool _mi_os_secure_guard_page_set_at(void *addr, mi_memid_t memid)
{
  if (addr == 0)
  {
    return 1;
  }
  (void) memid;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


bool _mi_os_secure_guard_page_set_before(void *addr, mi_memid_t memid)
{
  return _mi_os_secure_guard_page_set_at(((uint8_t *) addr) - _mi_os_secure_guard_page_size(), memid);
}


/*** DEPENDENCIES:
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
bool _mi_os_secure_guard_page_set_at(void *addr, mi_memid_t memid)
{
  if (addr == 0)
  {
    return 1;
  }
  (void) memid;
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['p_idx_ref is a mutable refrence to unsigned int']
void *helper_helper_mi_os_prim_alloc_aligned_1_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, void * const p, const size_t over_size)
{
  unsigned int p_idx = *p_idx_ref;
  p_idx = mi_os_prim_alloc(over_size, 1, commit, 0, is_large, is_zero);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  void *aligned_p = _mi_align_up_ptr(p, alignment);
  size_t pre_size = ((uint8_t *) aligned_p) - ((uint8_t *) p);
  size_t mid_size = _mi_align_up(size, _mi_os_page_size());
  size_t post_size = (over_size - pre_size) - mid_size;
  (((pre_size < over_size) && (post_size < over_size)) && (mid_size >= size)) ? ((void) 0) : (_mi_assert_fail("pre_size < over_size&& post_size < over_size&& mid_size >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 330, __func__));
  if (pre_size > 0)
  {
    mi_os_prim_free(p, pre_size, (commit) ? (pre_size) : (0), 0);
  }
  if (post_size > 0)
  {
    mi_os_prim_free(((uint8_t *) aligned_p) + mid_size, post_size, (commit) ? (post_size) : (0), 0);
  }
  p_idx = aligned_p;
  *base = aligned_p;
  *p_idx_ref = p_idx;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
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
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


----------------------------
inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}


----------------------------
static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
}


----------------------------
None
----------------------------
***/


// hint:  ['p_idx_ref is a mutable refrence to unsigned int']
void *helper_mi_os_prim_alloc_aligned_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, const bool try_direct_alloc, void * const p)
{
  unsigned int p_idx = *p_idx_ref;
  if (try_direct_alloc)
  {
    _mi_warning_message("unable to allocate aligned OS memory directly, fall back to over-allocation (size: 0x%zx bytes, address: %p, alignment: 0x%zx, commit: %d)\n", size, p, alignment, commit);
  }
  if ((&p[p_idx]) != 0)
  {
    mi_os_prim_free(p, size, (commit) ? (size) : (0), 0);
  }
  if (size >= (SIZE_MAX - alignment))
  {
    return 0;
  }
  const size_t over_size = size + alignment;
  if (!mi_os_mem_config.has_partial_free)
  {
    p_idx = mi_os_prim_alloc(over_size, 1, 0, 0, is_large, is_zero);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
    *base = &p[p_idx];
    p_idx = _mi_align_up_ptr(p_idx, alignment);
    if (commit)
    {
      if (!_mi_os_commit(p, size, 0))
      {
        mi_os_prim_free(*base, over_size, 0, 0);
        return 0;
      }
    }
  }
  else
  {
    helper_helper_mi_os_prim_alloc_aligned_1_1(&p_idx, size, alignment, commit, is_large, is_zero, base, p, over_size);
  }
  *p_idx_ref = p_idx;
}


/*** DEPENDENCIES:
void *helper_helper_mi_os_prim_alloc_aligned_1_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, void * const p, const size_t over_size)
{
  unsigned int p_idx = *p_idx_ref;
  p_idx = mi_os_prim_alloc(over_size, 1, commit, 0, is_large, is_zero);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  void *aligned_p = _mi_align_up_ptr(p, alignment);
  size_t pre_size = ((uint8_t *) aligned_p) - ((uint8_t *) p);
  size_t mid_size = _mi_align_up(size, _mi_os_page_size());
  size_t post_size = (over_size - pre_size) - mid_size;
  (((pre_size < over_size) && (post_size < over_size)) && (mid_size >= size)) ? ((void) 0) : (_mi_assert_fail("pre_size < over_size&& post_size < over_size&& mid_size >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 330, __func__));
  if (pre_size > 0)
  {
    mi_os_prim_free(p, pre_size, (commit) ? (pre_size) : (0), 0);
  }
  if (post_size > 0)
  {
    mi_os_prim_free(((uint8_t *) aligned_p) + mid_size, post_size, (commit) ? (post_size) : (0), 0);
  }
  p_idx = aligned_p;
  *base = aligned_p;
  *p_idx_ref = p_idx;
}


----------------------------
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


----------------------------
inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}


----------------------------
static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
}


----------------------------
None
----------------------------
***/


static void *mi_os_prim_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **base)
{
  ((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)) ? ((void) 0) : (_mi_assert_fail("alignment >= _mi_os_page_size() && ((alignment & (alignment - 1)) == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 269, __func__));
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 270, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 271, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 272, __func__));
  (base != 0) ? ((void) 0) : (_mi_assert_fail("base != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 273, __func__));
  if (!commit)
  {
    allow_large = 0;
  }
  if (!((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)))
  {
    return 0;
  }
  size = _mi_align_up(size, _mi_os_page_size());
  const bool try_direct_alloc = (alignment <= mi_os_mem_config.alloc_granularity) || (alignment > (size / 8));
  void *p = 0;
  unsigned int p_idx = 0;
  if (try_direct_alloc)
  {
    p_idx = mi_os_prim_alloc(size, alignment, commit, allow_large, is_large, is_zero);
  }
  if (((&p[p_idx]) != 0) && ((((uintptr_t) p) % alignment) == 0))
  {
    *base = &p[p_idx];
  }
  else
  {
    helper_mi_os_prim_alloc_aligned_1(&p_idx, size, alignment, commit, is_large, is_zero, base, try_direct_alloc, p);
  }
  (((&p[p_idx]) == 0) || ((((&p[p_idx]) != 0) && ((*base) != 0)) && ((((uintptr_t) p) % alignment) == 0))) ? ((void) 0) : (_mi_assert_fail("p == NULL || (p != NULL && *base != NULL && ((uintptr_t)p % alignment) == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 339, __func__));
  return p;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
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
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
void *helper_mi_os_prim_alloc_aligned_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, const bool try_direct_alloc, void * const p)
{
  unsigned int p_idx = *p_idx_ref;
  if (try_direct_alloc)
  {
    _mi_warning_message("unable to allocate aligned OS memory directly, fall back to over-allocation (size: 0x%zx bytes, address: %p, alignment: 0x%zx, commit: %d)\n", size, p, alignment, commit);
  }
  if ((&p[p_idx]) != 0)
  {
    mi_os_prim_free(p, size, (commit) ? (size) : (0), 0);
  }
  if (size >= (SIZE_MAX - alignment))
  {
    return 0;
  }
  const size_t over_size = size + alignment;
  if (!mi_os_mem_config.has_partial_free)
  {
    p_idx = mi_os_prim_alloc(over_size, 1, 0, 0, is_large, is_zero);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
    *base = &p[p_idx];
    p_idx = _mi_align_up_ptr(p_idx, alignment);
    if (commit)
    {
      if (!_mi_os_commit(p, size, 0))
      {
        mi_os_prim_free(*base, over_size, 0, 0);
        return 0;
      }
    }
  }
  else
  {
    helper_helper_mi_os_prim_alloc_aligned_1_1(&p_idx, size, alignment, commit, is_large, is_zero, base, p, over_size);
  }
  *p_idx_ref = p_idx;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
static void *mi_os_prim_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **base)
{
  ((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)) ? ((void) 0) : (_mi_assert_fail("alignment >= _mi_os_page_size() && ((alignment & (alignment - 1)) == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 269, __func__));
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 270, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 271, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 272, __func__));
  (base != 0) ? ((void) 0) : (_mi_assert_fail("base != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 273, __func__));
  if (!commit)
  {
    allow_large = 0;
  }
  if (!((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)))
  {
    return 0;
  }
  size = _mi_align_up(size, _mi_os_page_size());
  const bool try_direct_alloc = (alignment <= mi_os_mem_config.alloc_granularity) || (alignment > (size / 8));
  void *p = 0;
  unsigned int p_idx = 0;
  if (try_direct_alloc)
  {
    p_idx = mi_os_prim_alloc(size, alignment, commit, allow_large, is_large, is_zero);
  }
  if (((&p[p_idx]) != 0) && ((((uintptr_t) p) % alignment) == 0))
  {
    *base = &p[p_idx];
  }
  else
  {
    helper_mi_os_prim_alloc_aligned_1(&p_idx, size, alignment, commit, is_large, is_zero, base, try_direct_alloc, p);
  }
  (((&p[p_idx]) == 0) || ((((&p[p_idx]) != 0) && ((*base) != 0)) && ((((uintptr_t) p) % alignment) == 0))) ? ((void) 0) : (_mi_assert_fail("p == NULL || (p != NULL && *base != NULL && ((uintptr_t)p % alignment) == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 339, __func__));
  return p;
}


----------------------------
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size)
{
  (void) try_alignment;
  (void) size;
  return 0;
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
size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
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
None
----------------------------
***/


// hint:  ['page_ref is a mutable refrence to size_t', 'all_zero_ref is a mutable refrence to bool']
void helper__mi_os_alloc_huge_os_pages_1(size_t * const page_ref, bool * const all_zero_ref, size_t pages, int numa_node, mi_msecs_t max_msecs, uint8_t * const start, mi_msecs_t start_t)
{
  size_t page = *page_ref;
  bool all_zero = *all_zero_ref;
  bool is_zero = 0;
  void *addr = start + (page * ((1024UL * 1024UL) * 1024UL));
  void *p = 0;
  int err = _mi_prim_alloc_huge_os_pages(addr, (1024UL * 1024UL) * 1024UL, numa_node, &is_zero, &p);
  if (!is_zero)
  {
    all_zero = 0;
  }
  if (err != 0)
  {
    _mi_warning_message("unable to allocate huge OS page (error: %d (0x%x), address: %p, size: %zx bytes)\n", err, err, addr, (1024UL * 1024UL) * 1024UL);
    break;
  }
  if (p != addr)
  {
    if (p != 0)
    {
      _mi_warning_message("could not allocate contiguous huge OS page %zu at %p\n", page, addr);
      mi_os_prim_free(p, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL, 0);
    }
    break;
  }
  page += 1;
  __mi_stat_increase_mt(&_mi_subproc()->stats.committed, (1024UL * 1024UL) * 1024UL);
  __mi_stat_increase_mt(&_mi_subproc()->stats.reserved, (1024UL * 1024UL) * 1024UL);
  if (max_msecs > 0)
  {
    mi_msecs_t elapsed = _mi_clock_end(start_t);
    if (page >= 1)
    {
      mi_msecs_t estimate = (elapsed / (page + 1)) * pages;
      if (estimate > (2 * max_msecs))
      {
        elapsed = max_msecs + 1;
      }
    }
    if (elapsed > max_msecs)
    {
      _mi_warning_message("huge OS page allocation timed out (after allocating %zu page(s))\n", page);
      break;
    }
  }
  *page_ref = page;
  *all_zero_ref = all_zero;
}


/*** DEPENDENCIES:
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
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
typedef int64_t mi_msecs_t
----------------------------
mi_msecs_t _mi_clock_end(mi_msecs_t start)
{
  mi_msecs_t end = _mi_clock_now();
  return (end - start) - mi_clock_diff;
}


----------------------------
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size, mi_subproc_t *subproc)
{
  unsigned int subproc_idx = 0;
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 174, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if ((&subproc[subproc_idx]) == 0)
  {
    subproc_idx = _mi_subproc();
  }
  if (commit_size > 0)
  {
    __mi_stat_decrease_mt(&subproc->stats.committed, commit_size);
  }
  __mi_stat_decrease_mt(&subproc->stats.reserved, size);
}


----------------------------
int _mi_prim_alloc_huge_os_pages(void *hint_addr, size_t size, int numa_node, bool *is_zero, void **addr)
{
  bool is_large = 1;
  *is_zero = 1;
  *addr = unix_mmap(hint_addr, size, 1UL << (13 + 3), PROT_READ | PROT_WRITE, 1, 1, &is_large);
  if ((((*addr) != 0) && (numa_node >= 0)) && (numa_node < (8 * (1 << 3))))
  {
    unsigned long numa_mask = 1UL << numa_node;
    long err = mi_prim_mbind(*addr, size, 1, &numa_mask, 8 * (1 << 3), 0);
    if (err != 0)
    {
      err = errno;
      _mi_warning_message("failed to bind huge (1GiB) pages to numa node %d (error: %d (0x%x))\n", numa_node, err, err);
    }
  }
  return ((*addr) != 0) ? (0) : (errno);
}


----------------------------
None
----------------------------
***/


static uint8_t *mi_os_claim_huge_pages(size_t pages, size_t *total_size)
{
  if (total_size != 0)
  {
    *total_size = 0;
  }
  const size_t size = pages * ((1024UL * 1024UL) * 1024UL);
  uintptr_t start = 0;
  uintptr_t end = 0;
  uintptr_t huge_start = atomic_load_explicit(&mi_huge_start, memory_order_relaxed);
  do
  {
    start = huge_start;
    if (start == 0)
    {
      start = ((uintptr_t) 8) << 40;
    }
    end = start + size;
  }
  while (!atomic_compare_exchange_weak_explicit(&mi_huge_start, &huge_start, end, memory_order_acq_rel, memory_order_acquire));
  if (total_size != 0)
  {
    *total_size = size;
  }
  return (uint8_t *) start;
}


/*** DEPENDENCIES:
static _Atomic uintptr_t mi_huge_start
----------------------------
***/


void *_mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_msecs, size_t *pages_reserved, size_t *psize, mi_memid_t *memid)
{
  *memid = _mi_memid_none();
  if (psize != 0)
  {
    *psize = 0;
  }
  if (pages_reserved != 0)
  {
    *pages_reserved = 0;
  }
  size_t size = 0;
  uint8_t * const start = mi_os_claim_huge_pages(pages, &size);
  if (start == 0)
  {
    return 0;
  }
  mi_msecs_t start_t = _mi_clock_start();
  size_t page = 0;
  bool all_zero = 1;
  while (page < pages)
  {
    helper__mi_os_alloc_huge_os_pages_1(&page, &all_zero, pages, numa_node, max_msecs, start, start_t);
  }

  ((page * ((1024UL * 1024UL) * 1024UL)) <= size) ? ((void) 0) : (_mi_assert_fail("page*MI_HUGE_OS_PAGE_SIZE <= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 727, __func__));
  if (pages_reserved != 0)
  {
    *pages_reserved = page;
  }
  if (psize != 0)
  {
    *psize = page * ((1024UL * 1024UL) * 1024UL);
  }
  if (page != 0)
  {
    (start != 0) ? ((void) 0) : (_mi_assert_fail("start != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 731, __func__));
    *memid = _mi_memid_create_os(start, size, 1, all_zero, 1);
    memid->memkind = MI_MEM_OS_HUGE;
    (memid->is_pinned) ? ((void) 0) : (_mi_assert_fail("memid->is_pinned", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 734, __func__));
  }
  return (page == 0) ? (0) : (start);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
static uint8_t *mi_os_claim_huge_pages(size_t pages, size_t *total_size)
{
  if (total_size != 0)
  {
    *total_size = 0;
  }
  const size_t size = pages * ((1024UL * 1024UL) * 1024UL);
  uintptr_t start = 0;
  uintptr_t end = 0;
  uintptr_t huge_start = atomic_load_explicit(&mi_huge_start, memory_order_relaxed);
  do
  {
    start = huge_start;
    if (start == 0)
    {
      start = ((uintptr_t) 8) << 40;
    }
    end = start + size;
  }
  while (!atomic_compare_exchange_weak_explicit(&mi_huge_start, &huge_start, end, memory_order_acq_rel, memory_order_acquire));
  if (total_size != 0)
  {
    *total_size = size;
  }
  return (uint8_t *) start;
}


----------------------------
mi_msecs_t _mi_clock_start(void)
{
  if (mi_clock_diff == 0.0)
  {
    mi_msecs_t t0 = _mi_clock_now();
    mi_clock_diff = _mi_clock_now() - t0;
  }
  return _mi_clock_now();
}


----------------------------
void helper__mi_os_alloc_huge_os_pages_1(size_t * const page_ref, bool * const all_zero_ref, size_t pages, int numa_node, mi_msecs_t max_msecs, uint8_t * const start, mi_msecs_t start_t)
{
  size_t page = *page_ref;
  bool all_zero = *all_zero_ref;
  bool is_zero = 0;
  void *addr = start + (page * ((1024UL * 1024UL) * 1024UL));
  void *p = 0;
  int err = _mi_prim_alloc_huge_os_pages(addr, (1024UL * 1024UL) * 1024UL, numa_node, &is_zero, &p);
  if (!is_zero)
  {
    all_zero = 0;
  }
  if (err != 0)
  {
    _mi_warning_message("unable to allocate huge OS page (error: %d (0x%x), address: %p, size: %zx bytes)\n", err, err, addr, (1024UL * 1024UL) * 1024UL);
    break;
  }
  if (p != addr)
  {
    if (p != 0)
    {
      _mi_warning_message("could not allocate contiguous huge OS page %zu at %p\n", page, addr);
      mi_os_prim_free(p, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL, 0);
    }
    break;
  }
  page += 1;
  __mi_stat_increase_mt(&_mi_subproc()->stats.committed, (1024UL * 1024UL) * 1024UL);
  __mi_stat_increase_mt(&_mi_subproc()->stats.reserved, (1024UL * 1024UL) * 1024UL);
  if (max_msecs > 0)
  {
    mi_msecs_t elapsed = _mi_clock_end(start_t);
    if (page >= 1)
    {
      mi_msecs_t estimate = (elapsed / (page + 1)) * pages;
      if (estimate > (2 * max_msecs))
      {
        elapsed = max_msecs + 1;
      }
    }
    if (elapsed > max_msecs)
    {
      _mi_warning_message("huge OS page allocation timed out (after allocating %zu page(s))\n", page);
      break;
    }
  }
  *page_ref = page;
  *all_zero_ref = all_zero;
}


----------------------------
typedef int64_t mi_msecs_t
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
None
----------------------------
***/


int _mi_os_numa_node_count(void)
{
  size_t count = atomic_load_explicit(&mi_numa_node_count, memory_order_acquire);
  if (__builtin_expect(!(!(count == 0)), 0))
  {
    long ncount = mi_option_get(mi_option_use_numa_nodes);
    if ((ncount > 0) && (ncount < 2147483647))
    {
      count = (size_t) ncount;
    }
    else
    {
      const size_t n = _mi_prim_numa_node_count();
      if ((n == 0) || (n > 2147483647))
      {
        count = 1;
      }
      else
      {
        count = n;
      }
    }
    atomic_store_explicit(&mi_numa_node_count, count, memory_order_release);
    _mi_verbose_message("using %zd numa regions\n", count);
  }
  ((count > 0) && (count <= 2147483647)) ? ((void) 0) : (_mi_assert_fail("count > 0 && count <= INT_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 776, __func__));
  return (int) count;
}


/*** DEPENDENCIES:
static _Atomic size_t mi_numa_node_count
----------------------------
None
----------------------------
size_t _mi_prim_numa_node_count(void)
{
  char buf[128];
  unsigned node = 0;
  for (node = 0; node < 256; node += 1)
  {
    _mi_snprintf(buf, 127, "/sys/devices/system/node/node%u", node + 1);
    if (mi_prim_access(buf, R_OK) != 0)
    {
      break;
    }
  }

  return node + 1;
}


----------------------------
void _mi_verbose_message(const char *fmt, ...)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    return;
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, "mimalloc: ", fmt, args);
  ;
}


----------------------------
None
----------------------------
***/


void _mi_os_init(void)
{
  _mi_prim_mem_init(&mi_os_mem_config);
}


/*** DEPENDENCIES:
void _mi_prim_mem_init(mi_os_mem_config_t *config)
{
  long psize = sysconf(_SC_PAGESIZE);
  if ((psize > 0) && (((unsigned long) psize) < SIZE_MAX))
  {
    config->page_size = (size_t) psize;
    config->alloc_granularity = (size_t) psize;
    unix_detect_physical_memory(config->page_size, &config->physical_memory_in_kib);
  }
  config->large_page_size = 2 * (1024UL * 1024UL);
  config->has_overcommit = unix_detect_overcommit();
  config->has_partial_free = 1;
  config->has_virtual_reserve = 1;
}


----------------------------
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
***/


static int mi_os_numa_node_get(void)
{
  int numa_count = _mi_os_numa_node_count();
  if (numa_count <= 1)
  {
    return 0;
  }
  const size_t n = _mi_prim_numa_node();
  int numa_node = (n < 2147483647) ? ((int) n) : (0);
  if (numa_node >= numa_count)
  {
    numa_node = numa_node % numa_count;
  }
  return numa_node;
}


/*** DEPENDENCIES:
int _mi_os_numa_node_count(void)
{
  size_t count = atomic_load_explicit(&mi_numa_node_count, memory_order_acquire);
  if (__builtin_expect(!(!(count == 0)), 0))
  {
    long ncount = mi_option_get(mi_option_use_numa_nodes);
    if ((ncount > 0) && (ncount < 2147483647))
    {
      count = (size_t) ncount;
    }
    else
    {
      const size_t n = _mi_prim_numa_node_count();
      if ((n == 0) || (n > 2147483647))
      {
        count = 1;
      }
      else
      {
        count = n;
      }
    }
    atomic_store_explicit(&mi_numa_node_count, count, memory_order_release);
    _mi_verbose_message("using %zd numa regions\n", count);
  }
  ((count > 0) && (count <= 2147483647)) ? ((void) 0) : (_mi_assert_fail("count > 0 && count <= INT_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 776, __func__));
  return (int) count;
}


----------------------------
size_t _mi_prim_numa_node(void)
{
  return 0;
}


----------------------------
***/


int _mi_os_numa_node(void)
{
  if (__builtin_expect(!(!(atomic_load_explicit(&mi_numa_node_count, memory_order_relaxed) == 1)), 1))
  {
    return 0;
  }
  else
  {
    return mi_os_numa_node_get();
  }
}


/*** DEPENDENCIES:
static _Atomic size_t mi_numa_node_count
----------------------------
static int mi_os_numa_node_get(void)
{
  int numa_count = _mi_os_numa_node_count();
  if (numa_count <= 1)
  {
    return 0;
  }
  const size_t n = _mi_prim_numa_node();
  int numa_node = (n < 2147483647) ? ((int) n) : (0);
  if (numa_node >= numa_count)
  {
    numa_node = numa_node % numa_count;
  }
  return numa_node;
}


----------------------------
***/


void _mi_os_reuse(void *addr, size_t size)
{
  size_t csize = 0;
  void * const start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return;
  }
  const int err = _mi_prim_reuse(start, csize);
  if (err != 0)
  {
    _mi_warning_message("cannot reuse OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
}


/*** DEPENDENCIES:
int _mi_prim_reuse(void *start, size_t size)
{
  (void) start;
  (void) size;
  return 0;
}


----------------------------
static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}


----------------------------
None
----------------------------
***/


bool _mi_os_has_virtual_reserve(void)
{
  return mi_os_mem_config.has_virtual_reserve;
}


/*** DEPENDENCIES:
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
***/


bool _mi_os_decommit(void *addr, size_t size)
{
  bool needs_recommit;
  return mi_os_decommit_ex(addr, size, &needs_recommit, size);
}


/*** DEPENDENCIES:
static bool mi_os_decommit_ex(void *addr, size_t size, bool *needs_recommit, size_t stat_size)
{
  (needs_recommit != 0) ? ((void) 0) : (_mi_assert_fail("needs_recommit!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 506, __func__));
  __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, stat_size);
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  *needs_recommit = 1;
  int err = _mi_prim_decommit(start, csize, needs_recommit);
  if (err != 0)
  {
    _mi_warning_message("cannot decommit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  (err == 0) ? ((void) 0) : (_mi_assert_fail("err == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 520, __func__));
  return err == 0;
}


----------------------------
***/


void *_mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t offset, bool commit, bool allow_large, mi_memid_t *memid)
{
  (offset <= size) ? ((void) 0) : (_mi_assert_fail("offset <= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 420, __func__));
  ((alignment % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(alignment % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 421, __func__));
  *memid = _mi_memid_none();
  if (offset == 0)
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
  else
  {
    const size_t extra = _mi_align_up(offset, alignment) - offset;
    const size_t oversize = size + extra;
    void * const start = _mi_os_alloc_aligned(oversize, alignment, commit, allow_large, memid);
    if (start == 0)
    {
      return 0;
    }
    void * const p = ((uint8_t *) start) + extra;
    (_mi_is_aligned(((uint8_t *) p) + offset, alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned((uint8_t*)p + offset, alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 435, __func__));
    if (commit && (extra > _mi_os_page_size()))
    {
      _mi_os_decommit(start, extra);
    }
    return p;
  }
}


/*** DEPENDENCIES:
bool _mi_os_decommit(void *addr, size_t size)
{
  bool needs_recommit;
  return mi_os_decommit_ex(addr, size, &needs_recommit, size);
}


----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
None
----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
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
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
None
----------------------------
***/


size_t _mi_os_virtual_address_bits(void)
{
  const size_t vbits = mi_os_mem_config.virtual_address_bits;
  (vbits <= 48) ? ((void) 0) : (_mi_assert_fail("vbits <= MI_MAX_VABITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 61, __func__));
  return vbits;
}


/*** DEPENDENCIES:
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
None
----------------------------
***/


static bool mi_os_protectx(void *addr, size_t size, bool protect)
{
  size_t csize = 0;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 0;
  }
  int err = _mi_prim_protect(start, csize, protect);
  if (err != 0)
  {
    _mi_warning_message("cannot %s OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", (protect) ? ("protect") : ("unprotect"), err, err, start, csize);
  }
  return err == 0;
}


/*** DEPENDENCIES:
int _mi_prim_protect(void *start, size_t size, bool protect)
{
  int err = mprotect(start, size, (protect) ? (PROT_NONE) : (PROT_READ | PROT_WRITE));
  if (err != 0)
  {
    err = errno;
  }
  unix_mprotect_hint(err);
  return err;
}


----------------------------
static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}


----------------------------
None
----------------------------
***/


bool _mi_os_protect(void *addr, size_t size)
{
  return mi_os_protectx(addr, size, 1);
}


/*** DEPENDENCIES:
static bool mi_os_protectx(void *addr, size_t size, bool protect)
{
  size_t csize = 0;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 0;
  }
  int err = _mi_prim_protect(start, csize, protect);
  if (err != 0)
  {
    _mi_warning_message("cannot %s OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", (protect) ? ("protect") : ("unprotect"), err, err, start, csize);
  }
  return err == 0;
}


----------------------------
***/


bool _mi_os_unprotect(void *addr, size_t size)
{
  return mi_os_protectx(addr, size, 0);
}


/*** DEPENDENCIES:
static bool mi_os_protectx(void *addr, size_t size, bool protect)
{
  size_t csize = 0;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 0;
  }
  int err = _mi_prim_protect(start, csize, protect);
  if (err != 0)
  {
    _mi_warning_message("cannot %s OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", (protect) ? ("protect") : ("unprotect"), err, err, start, csize);
  }
  return err == 0;
}


----------------------------
***/


bool _mi_os_purge(void *p, size_t size)
{
  return _mi_os_purge_ex(p, size, 1, size, 0, 0);
}


/*** DEPENDENCIES:
bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stat_size, mi_commit_fun_t *commit_fun, void *commit_fun_arg)
{
  if (mi_option_get(mi_option_purge_delay) < 0)
  {
    return 0;
  }
  __mi_stat_counter_increase_mt(&_mi_subproc()->stats.purge_calls, 1);
  __mi_stat_increase_mt(&_mi_subproc()->stats.purged, size);
  if (commit_fun != 0)
  {
    bool decommitted = (*commit_fun)(0, p, size, 0, commit_fun_arg);
    return decommitted;
  }
  else
    if (mi_option_is_enabled(mi_option_purge_decommits) && (!_mi_preloading()))
  {
    bool needs_recommit = 1;
    mi_os_decommit_ex(p, size, &needs_recommit, stat_size);
    return needs_recommit;
  }
  else
  {
    if (allow_reset)
    {
      _mi_os_reset(p, size);
    }
    return 0;
  }
}


----------------------------
***/


bool _mi_os_secure_guard_page_reset_at(void *addr, mi_memid_t memid)
{
  if (addr == 0)
  {
    return 1;
  }
  (void) memid;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


size_t _mi_os_guard_page_size(void)
{
  const size_t gsize = _mi_os_page_size();
  (gsize <= ((1UL << (13 + 3)) / 8)) ? ((void) 0) : (_mi_assert_fail("gsize <= (MI_ARENA_SLICE_SIZE/8)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 55, __func__));
  return gsize;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
None
----------------------------
***/


size_t _mi_os_large_page_size(void)
{
  return (mi_os_mem_config.large_page_size != 0) ? (mi_os_mem_config.large_page_size) : (_mi_os_page_size());
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
----------------------------
***/


bool _mi_os_secure_guard_page_reset_before(void *addr, mi_memid_t memid)
{
  return _mi_os_secure_guard_page_reset_at(((uint8_t *) addr) - _mi_os_secure_guard_page_size(), memid);
}


/*** DEPENDENCIES:
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
bool _mi_os_secure_guard_page_reset_at(void *addr, mi_memid_t memid)
{
  if (addr == 0)
  {
    return 1;
  }
  (void) memid;
  return 1;
}


----------------------------
None
----------------------------
***/


