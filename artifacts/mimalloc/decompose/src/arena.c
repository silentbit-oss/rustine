size_t mi_arena_min_alignment(void)
{
  return 1UL << (13 + 3);
}


/*** DEPENDENCIES:
***/


mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


/*** DEPENDENCIES:
typedef void *mi_arena_id_t
----------------------------
***/


size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


/*** DEPENDENCIES:
None
----------------------------
***/


mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


/*** DEPENDENCIES:
None
----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
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
***/


inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
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


inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}


/*** DEPENDENCIES:
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
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
***/


static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


/*** DEPENDENCIES:
None
----------------------------
***/


uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


/*** DEPENDENCIES:
static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
None
----------------------------
***/


inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


/*** DEPENDENCIES:
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
***/


static bool mi_arena_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (!arena->memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("!arena->memid.is_pinned", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1648, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1649, __func__));
  const size_t size = mi_size_of_slices(slice_count);
  void * const p = mi_arena_slice_start(arena, slice_index);
  size_t already_committed;
  mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed);
  const bool all_committed = already_committed == slice_count;
  const bool needs_recommit = _mi_os_purge_ex(p, size, all_committed, mi_size_of_slices(already_committed), arena->commit_fun, arena->commit_fun_arg);
  if (needs_recommit)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  else
    if (!all_committed)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  return needs_recommit;
}


/*** DEPENDENCIES:
None
----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
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
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
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
None
----------------------------
***/


inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}


/*** DEPENDENCIES:
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


inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}


/*** DEPENDENCIES:
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


static bool mi_arena_try_purge_range(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  if (mi_bbitmap_try_clearN(arena->slices_free, slice_index, slice_count))
  {
    bool decommitted = mi_arena_purge(arena, slice_index, slice_count);
    (void) decommitted;
    ((!decommitted) || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("!decommitted || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1715, __func__));
    mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
    return 1;
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_arena_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (!arena->memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("!arena->memid.is_pinned", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1648, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1649, __func__));
  const size_t size = mi_size_of_slices(slice_count);
  void * const p = mi_arena_slice_start(arena, slice_index);
  size_t already_committed;
  mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed);
  const bool all_committed = already_committed == slice_count;
  const bool needs_recommit = _mi_os_purge_ex(p, size, all_committed, mi_size_of_slices(already_committed), arena->commit_fun, arena->commit_fun_arg);
  if (needs_recommit)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  else
    if (!all_committed)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  return needs_recommit;
}


----------------------------
inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


static bool mi_arena_try_purge_visitor(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  mi_purge_visit_info_t *vinfo = (mi_purge_visit_info_t *) arg;
  if (mi_arena_try_purge_range(arena, slice_index, slice_count))
  {
    vinfo->any_purged = 1;
    vinfo->all_purged = 1;
  }
  else
    if (slice_count > 1)
  {
    for (size_t i = 0; i < slice_count; i += 1)
    {
      const bool purged = mi_arena_try_purge_range(arena, slice_index + i, 1);
      vinfo->any_purged = vinfo->any_purged || purged;
      vinfo->all_purged = vinfo->all_purged && purged;
    }

  }
  return 1;
}


/*** DEPENDENCIES:
typedef struct mi_purge_visit_info_s
{
  mi_msecs_t now;
  mi_msecs_t delay;
  bool all_purged;
  bool any_purged;
} mi_purge_visit_info_t
----------------------------
static bool mi_arena_try_purge_range(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  if (mi_bbitmap_try_clearN(arena->slices_free, slice_index, slice_count))
  {
    bool decommitted = mi_arena_purge(arena, slice_index, slice_count);
    (void) decommitted;
    ((!decommitted) || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("!decommitted || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1715, __func__));
    mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
    return 1;
  }
  else
  {
    return 0;
  }
}


----------------------------
None
----------------------------
***/


static long mi_arena_purge_delay(void)
{
  return mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static bool mi_arena_try_purge(mi_arena_t *arena, mi_msecs_t now, bool force)
{
  if (arena->memid.is_pinned)
  {
    return 0;
  }
  mi_msecs_t expire = atomic_load_explicit(&arena->purge_expire, memory_order_relaxed);
  if ((!force) && ((expire == 0) || (expire > now)))
  {
    return 0;
  }
  atomic_store_explicit(&arena->purge_expire, (mi_msecs_t) 0, memory_order_release);
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_purges, 1);
  mi_purge_visit_info_t vinfo = {now, mi_arena_purge_delay(), 1, 0};
  _mi_bitmap_forall_setc_ranges(arena->slices_purge, &mi_arena_try_purge_visitor, arena, &vinfo);
  return vinfo.any_purged;
}


/*** DEPENDENCIES:
typedef struct mi_purge_visit_info_s
{
  mi_msecs_t now;
  mi_msecs_t delay;
  bool all_purged;
  bool any_purged;
} mi_purge_visit_info_t
----------------------------
static bool mi_arena_try_purge_visitor(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  mi_purge_visit_info_t *vinfo = (mi_purge_visit_info_t *) arg;
  if (mi_arena_try_purge_range(arena, slice_index, slice_count))
  {
    vinfo->any_purged = 1;
    vinfo->all_purged = 1;
  }
  else
    if (slice_count > 1)
  {
    for (size_t i = 0; i < slice_count; i += 1)
    {
      const bool purged = mi_arena_try_purge_range(arena, slice_index + i, 1);
      vinfo->any_purged = vinfo->any_purged || purged;
      vinfo->all_purged = vinfo->all_purged && purged;
    }

  }
  return 1;
}


----------------------------
typedef int64_t mi_msecs_t
----------------------------
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


----------------------------
static long mi_arena_purge_delay(void)
{
  return mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult);
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


void helper_mi_arenas_try_purge_1(bool force, bool visit_all, mi_subproc_t * const subproc, size_t tseq, const long delay, const mi_msecs_t now, const mi_msecs_t arenas_expire, const size_t max_arena)
{
  if (arenas_expire > now)
  {
    atomic_store_explicit(&subproc->purge_expire, now + (delay / 10), memory_order_release);
  }
  const size_t arena_start = tseq % max_arena;
  size_t max_purge_count = (visit_all) ? (max_arena) : ((max_arena / 4) + 1);
  bool all_visited = 1;
  bool any_purged = 0;
  for (size_t _i = 0; _i < max_arena; _i += 1)
  {
    size_t i = _i + arena_start;
    if (i >= max_arena)
    {
      i -= max_arena;
    }
    mi_arena_t *arena = mi_arena_from_index(subproc, i);
    if (arena != 0)
    {
      if (mi_arena_try_purge(arena, now, force))
      {
        any_purged = 1;
        if (max_purge_count <= 1)
        {
          all_visited = 0;
          break;
        }
        max_purge_count -= 1;
      }
    }
  }

  if (all_visited && (!any_purged))
  {
    atomic_store_explicit(&subproc->purge_expire, 0, memory_order_release);
  }
}


/*** DEPENDENCIES:
static bool mi_arena_try_purge(mi_arena_t *arena, mi_msecs_t now, bool force)
{
  if (arena->memid.is_pinned)
  {
    return 0;
  }
  mi_msecs_t expire = atomic_load_explicit(&arena->purge_expire, memory_order_relaxed);
  if ((!force) && ((expire == 0) || (expire > now)))
  {
    return 0;
  }
  atomic_store_explicit(&arena->purge_expire, (mi_msecs_t) 0, memory_order_release);
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_purges, 1);
  mi_purge_visit_info_t vinfo = {now, mi_arena_purge_delay(), 1, 0};
  _mi_bitmap_forall_setc_ranges(arena->slices_purge, &mi_arena_try_purge_visitor, arena, &vinfo);
  return vinfo.any_purged;
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
typedef int64_t mi_msecs_t
----------------------------
None
----------------------------
***/


static void mi_arenas_try_purge(bool force, bool visit_all, mi_subproc_t *subproc, size_t tseq)
{
  const long delay = mi_arena_purge_delay();
  if (_mi_preloading() || (delay <= 0))
  {
    return;
  }
  const mi_msecs_t now = _mi_clock_now();
  const mi_msecs_t arenas_expire = atomic_load_explicit(&subproc->purge_expire, memory_order_acquire);
  if (((!visit_all) && (!force)) && ((arenas_expire == 0) || (arenas_expire > now)))
  {
    return;
  }
  const size_t max_arena = mi_arenas_get_count(subproc);
  if (max_arena == 0)
  {
    return;
  }
  static mi_atomic_guard_t purge_guard;
  uintptr_t _mi_guard_expected = 0;
  for (bool _mi_guard_once = 1; _mi_guard_once && atomic_compare_exchange_strong_explicit(&purge_guard, &_mi_guard_expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire); atomic_store_explicit(&purge_guard, (uintptr_t) 0, memory_order_release), _mi_guard_once = 0)
  {
    helper_mi_arenas_try_purge_1(force, visit_all, subproc, tseq, delay, now, arenas_expire, max_arena);
  }

}


/*** DEPENDENCIES:
void helper_mi_arenas_try_purge_1(bool force, bool visit_all, mi_subproc_t * const subproc, size_t tseq, const long delay, const mi_msecs_t now, const mi_msecs_t arenas_expire, const size_t max_arena)
{
  if (arenas_expire > now)
  {
    atomic_store_explicit(&subproc->purge_expire, now + (delay / 10), memory_order_release);
  }
  const size_t arena_start = tseq % max_arena;
  size_t max_purge_count = (visit_all) ? (max_arena) : ((max_arena / 4) + 1);
  bool all_visited = 1;
  bool any_purged = 0;
  for (size_t _i = 0; _i < max_arena; _i += 1)
  {
    size_t i = _i + arena_start;
    if (i >= max_arena)
    {
      i -= max_arena;
    }
    mi_arena_t *arena = mi_arena_from_index(subproc, i);
    if (arena != 0)
    {
      if (mi_arena_try_purge(arena, now, force))
      {
        any_purged = 1;
        if (max_purge_count <= 1)
        {
          all_visited = 0;
          break;
        }
        max_purge_count -= 1;
      }
    }
  }

  if (all_visited && (!any_purged))
  {
    atomic_store_explicit(&subproc->purge_expire, 0, memory_order_release);
  }
}


----------------------------
bool _mi_preloading(void)
{
  return os_preloading;
}


----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
mi_msecs_t _mi_clock_now(void)
{
  return _mi_prim_clock_now();
}


----------------------------
typedef int64_t mi_msecs_t
----------------------------
typedef _Atomic uintptr_t mi_atomic_guard_t
----------------------------
static long mi_arena_purge_delay(void)
{
  return mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult);
}


----------------------------
None
----------------------------
***/


void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld)
{
  mi_arenas_try_purge(force_purge, visit_all, tld->subproc, tld->thread_seq);
}


/*** DEPENDENCIES:
static void mi_arenas_try_purge(bool force, bool visit_all, mi_subproc_t *subproc, size_t tseq)
{
  const long delay = mi_arena_purge_delay();
  if (_mi_preloading() || (delay <= 0))
  {
    return;
  }
  const mi_msecs_t now = _mi_clock_now();
  const mi_msecs_t arenas_expire = atomic_load_explicit(&subproc->purge_expire, memory_order_acquire);
  if (((!visit_all) && (!force)) && ((arenas_expire == 0) || (arenas_expire > now)))
  {
    return;
  }
  const size_t max_arena = mi_arenas_get_count(subproc);
  if (max_arena == 0)
  {
    return;
  }
  static mi_atomic_guard_t purge_guard;
  uintptr_t _mi_guard_expected = 0;
  for (bool _mi_guard_once = 1; _mi_guard_once && atomic_compare_exchange_strong_explicit(&purge_guard, &_mi_guard_expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire); atomic_store_explicit(&purge_guard, (uintptr_t) 0, memory_order_release), _mi_guard_once = 0)
  {
    helper_mi_arenas_try_purge_1(force, visit_all, subproc, tseq, delay, now, arenas_expire, max_arena);
  }

}


----------------------------
None
----------------------------
***/


static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_memid_is_os(mi_memid_t memid)
{
  return mi_memkind_is_os(memid.memkind);
}


----------------------------
None
----------------------------
***/


inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


/*** DEPENDENCIES:
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


void helper__mi_arenas_page_free_1(mi_page_t * const page)
{
  mi_arena_t * const arena = page->memid.mem.arena.arena;
  mi_bitmap_clear(arena->pages, page->memid.mem.arena.slice_index);
  if (page->slice_committed > 0)
  {
    (mi_page_full_size(page) >= page->slice_committed) ? ((void) 0) : (_mi_assert_fail("mi_page_full_size(page) >= page->slice_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 855, __func__));
    const size_t total_slices = page->slice_committed / (1UL << (13 + 3));
    (page->memid.mem.arena.slice_count >= total_slices) ? ((void) 0) : (_mi_assert_fail("page->memid.mem.arena.slice_count >= total_slices", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 858, __func__));
    if (total_slices > 0)
    {
      mi_bitmap_setN(arena->slices_committed, page->memid.mem.arena.slice_index, total_slices, 0);
    }
    const size_t extra = page->slice_committed % (1UL << (13 + 3));
    if (extra > 0)
    {
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, extra);
    }
  }
  else
  {
    (mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 870, __func__));
  }
}


/*** DEPENDENCIES:
None
----------------------------
bool mi_bitmap_clear(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_clearN(bitmap, idx, 1);
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
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
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
static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}


----------------------------
None
----------------------------
***/


static mi_arena_t *mi_arena_from_memid(mi_memid_t memid, size_t *slice_index, size_t *slice_count)
{
  (memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("memid.memkind == MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 138, __func__));
  mi_arena_t *arena = memid.mem.arena.arena;
  if (slice_index)
  {
    *slice_index = memid.mem.arena.slice_index;
  }
  if (slice_count)
  {
    *slice_count = memid.mem.arena.slice_count;
  }
  return arena;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static mi_arena_t *mi_page_arena(mi_page_t *page, size_t *slice_index, size_t *slice_count)
{
  return mi_arena_from_memid(page->memid, slice_index, slice_count);
}


/*** DEPENDENCIES:
static mi_arena_t *mi_arena_from_memid(mi_memid_t memid, size_t *slice_index, size_t *slice_count)
{
  (memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("memid.memkind == MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 138, __func__));
  mi_arena_t *arena = memid.mem.arena.arena;
  if (slice_index)
  {
    *slice_index = memid.mem.arena.slice_index;
  }
  if (slice_count)
  {
    *slice_count = memid.mem.arena.slice_count;
  }
  return arena;
}


----------------------------
None
----------------------------
***/


static void mi_arena_schedule_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  const long delay = mi_arena_purge_delay();
  if ((arena->memid.is_pinned || (delay < 0)) || _mi_preloading())
  {
    return;
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1682, __func__));
  if (delay == 0)
  {
    mi_arena_purge(arena, slice_index, slice_count);
  }
  else
  {
    const mi_msecs_t expire = _mi_clock_now() + delay;
    mi_msecs_t expire0 = 0;
    if (atomic_compare_exchange_strong_explicit(&arena->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire))
    {
      (expire0 == 0) ? ((void) 0) : (_mi_assert_fail("expire0==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1694, __func__));
      atomic_compare_exchange_strong_explicit(&arena->subproc->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
    }
    mi_bitmap_setN(arena->slices_purge, slice_index, slice_count, 0);
  }
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_arena_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (!arena->memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("!arena->memid.is_pinned", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1648, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1649, __func__));
  const size_t size = mi_size_of_slices(slice_count);
  void * const p = mi_arena_slice_start(arena, slice_index);
  size_t already_committed;
  mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed);
  const bool all_committed = already_committed == slice_count;
  const bool needs_recommit = _mi_os_purge_ex(p, size, all_committed, mi_size_of_slices(already_committed), arena->commit_fun, arena->commit_fun_arg);
  if (needs_recommit)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  else
    if (!all_committed)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  return needs_recommit;
}


----------------------------
bool _mi_preloading(void)
{
  return os_preloading;
}


----------------------------
mi_msecs_t _mi_clock_now(void)
{
  return _mi_prim_clock_now();
}


----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
typedef int64_t mi_msecs_t
----------------------------
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
static long mi_arena_purge_delay(void)
{
  return mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult);
}


----------------------------
None
----------------------------
***/


static size_t mi_arena_info_slices(mi_arena_t *arena)
{
  return arena->info_slices;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void helper__mi_arenas_free_1(void * const p, size_t size, mi_memid_t memid)
{
  size_t slice_count;
  size_t slice_index;
  mi_arena_t *arena = mi_arena_from_memid(memid, &slice_index, &slice_count);
  ((size % (1UL << (13 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_ARENA_SLICE_SIZE)==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1009, __func__));
  ((slice_count * (1UL << (13 + 3))) == size) ? ((void) 0) : (_mi_assert_fail("(slice_count*MI_ARENA_SLICE_SIZE)==size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1010, __func__));
  (mi_arena_slice_start(arena, slice_index) <= ((uint8_t *) p)) ? ((void) 0) : (_mi_assert_fail("mi_arena_slice_start(arena,slice_index) <= (uint8_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1011, __func__));
  ((mi_arena_slice_start(arena, slice_index) + mi_size_of_slices(slice_count)) > ((uint8_t *) p)) ? ((void) 0) : (_mi_assert_fail("mi_arena_slice_start(arena,slice_index) + mi_size_of_slices(slice_count) > (uint8_t*)p", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1012, __func__));
  if (arena == 0)
  {
    _mi_error_message(22, "trying to free from an invalid arena: %p, size %zu, memid: 0x%zx\n", p, size, memid);
    return;
  }
  (slice_index < arena->slice_count) ? ((void) 0) : (_mi_assert_fail("slice_index < arena->slice_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1018, __func__));
  (slice_index >= mi_arena_info_slices(arena)) ? ((void) 0) : (_mi_assert_fail("slice_index >= mi_arena_info_slices(arena)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1019, __func__));
  if ((slice_index < mi_arena_info_slices(arena)) || (slice_index > arena->slice_count))
  {
    _mi_error_message(22, "trying to free from an invalid arena block: %p, size %zu, memid: 0x%zx\n", p, size, memid);
    return;
  }
  if (!arena->memid.is_pinned)
  {
    mi_arena_schedule_purge(arena, slice_index, slice_count);
  }
  bool all_inuse = mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
  if (!all_inuse)
  {
    _mi_error_message(11, "trying to free an already freed arena block: %p, size %zu\n", mi_arena_slice_start(arena, slice_index), mi_size_of_slices(slice_count));
    return;
  }
  ;
}


/*** DEPENDENCIES:
None
----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
static size_t mi_arena_info_slices(mi_arena_t *arena)
{
  return arena->info_slices;
}


----------------------------
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


----------------------------
static mi_arena_t *mi_arena_from_memid(mi_memid_t memid, size_t *slice_index, size_t *slice_count)
{
  (memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("memid.memkind == MI_MEM_ARENA", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 138, __func__));
  mi_arena_t *arena = memid.mem.arena.arena;
  if (slice_index)
  {
    *slice_index = memid.mem.arena.slice_index;
  }
  if (slice_count)
  {
    *slice_count = memid.mem.arena.slice_count;
  }
  return arena;
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
static void mi_arena_schedule_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  const long delay = mi_arena_purge_delay();
  if ((arena->memid.is_pinned || (delay < 0)) || _mi_preloading())
  {
    return;
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1682, __func__));
  if (delay == 0)
  {
    mi_arena_purge(arena, slice_index, slice_count);
  }
  else
  {
    const mi_msecs_t expire = _mi_clock_now() + delay;
    mi_msecs_t expire0 = 0;
    if (atomic_compare_exchange_strong_explicit(&arena->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire))
    {
      (expire0 == 0) ? ((void) 0) : (_mi_assert_fail("expire0==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1694, __func__));
      atomic_compare_exchange_strong_explicit(&arena->subproc->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
    }
    mi_bitmap_setN(arena->slices_purge, slice_index, slice_count, 0);
  }
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 172, __func__));
  return bin;
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


----------------------------
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
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
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
None
----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
static mi_arena_t *mi_page_arena(mi_page_t *page, size_t *slice_index, size_t *slice_count)
{
  return mi_arena_from_memid(page->memid, slice_index, slice_count);
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


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
void helper__mi_arenas_page_free_1(mi_page_t * const page)
{
  mi_arena_t * const arena = page->memid.mem.arena.arena;
  mi_bitmap_clear(arena->pages, page->memid.mem.arena.slice_index);
  if (page->slice_committed > 0)
  {
    (mi_page_full_size(page) >= page->slice_committed) ? ((void) 0) : (_mi_assert_fail("mi_page_full_size(page) >= page->slice_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 855, __func__));
    const size_t total_slices = page->slice_committed / (1UL << (13 + 3));
    (page->memid.mem.arena.slice_count >= total_slices) ? ((void) 0) : (_mi_assert_fail("page->memid.mem.arena.slice_count >= total_slices", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 858, __func__));
    if (total_slices > 0)
    {
      mi_bitmap_setN(arena->slices_committed, page->memid.mem.arena.slice_index, total_slices, 0);
    }
    const size_t extra = page->slice_committed % (1UL << (13 + 3));
    if (extra > 0)
    {
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, extra);
    }
  }
  else
  {
    (mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 870, __func__));
  }
}


----------------------------
static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}


----------------------------
None
----------------------------
***/


static mi_bitmap_t *mi_arena_bitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bitmap_t *bitmap = (mi_bitmap_t *) (*base);
  *base = (*base) + mi_bitmap_init(bitmap, slice_count, 1);
  return bitmap;
}


/*** DEPENDENCIES:
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


static size_t mi_arena_info_slices_needed(size_t slice_count, size_t *bitmap_base)
{
  if (slice_count == 0)
  {
    slice_count = 1 << (6 + 3);
  }
  ((slice_count % (1 << (6 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(slice_count % MI_BCHUNK_BITS) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1150, __func__));
  const size_t base_size = _mi_align_up(sizeof(mi_arena_t), (1 << (6 + 3)) / 8);
  const size_t bitmaps_count = 4 + ((73U + 1) + 1);
  const size_t bitmaps_size = (bitmaps_count * mi_bitmap_size(slice_count, 0)) + mi_bbitmap_size(slice_count, 0);
  const size_t size = base_size + bitmaps_size;
  const size_t os_page_size = _mi_os_page_size();
  const size_t info_size = _mi_align_up(size, os_page_size) + _mi_os_secure_guard_page_size();
  const size_t info_slices = mi_slice_count_of_size(info_size);
  if (bitmap_base != 0)
  {
    *bitmap_base = base_size;
  }
  return info_slices;
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
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


static mi_bbitmap_t *mi_arena_bbitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bbitmap_t *bbitmap = (mi_bbitmap_t *) (*base);
  *base = (*base) + mi_bbitmap_init(bbitmap, slice_count, 1);
  return bbitmap;
}


/*** DEPENDENCIES:
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


static bool mi_arenas_add(mi_subproc_t *subproc, mi_arena_t *arena, mi_arena_id_t *arena_id)
{
  (arena != 0) ? ((void) 0) : (_mi_assert_fail("arena != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1116, __func__));
  (arena->slice_count > 0) ? ((void) 0) : (_mi_assert_fail("arena->slice_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1117, __func__));
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  const size_t count = mi_arenas_get_count(subproc);
  size_t i;
  for (i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == 0)
    {
      mi_arena_t *expected = 0;
      if (atomic_compare_exchange_strong_explicit(&subproc->arenas[i], &expected, arena, memory_order_release, memory_order_relaxed))
      {
        if (arena_id != 0)
        {
          *arena_id = arena;
        }
        return 1;
      }
    }
  }

  i = atomic_fetch_add_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
  if (i >= 160)
  {
    atomic_fetch_sub_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
    arena->subproc = 0;
    return 0;
  }
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_count, 1);
  atomic_store_explicit(&subproc->arenas[i], arena, memory_order_release);
  if (arena_id != 0)
  {
    *arena_id = arena;
  }
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
typedef void *mi_arena_id_t
----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount)
{
  mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
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
static bool mi_arenas_add(mi_subproc_t *subproc, mi_arena_t *arena, mi_arena_id_t *arena_id)
{
  (arena != 0) ? ((void) 0) : (_mi_assert_fail("arena != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1116, __func__));
  (arena->slice_count > 0) ? ((void) 0) : (_mi_assert_fail("arena->slice_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1117, __func__));
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  const size_t count = mi_arenas_get_count(subproc);
  size_t i;
  for (i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == 0)
    {
      mi_arena_t *expected = 0;
      if (atomic_compare_exchange_strong_explicit(&subproc->arenas[i], &expected, arena, memory_order_release, memory_order_relaxed))
      {
        if (arena_id != 0)
        {
          *arena_id = arena;
        }
        return 1;
      }
    }
  }

  i = atomic_fetch_add_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
  if (i >= 160)
  {
    atomic_fetch_sub_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
    arena->subproc = 0;
    return 0;
  }
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_count, 1);
  atomic_store_explicit(&subproc->arenas[i], arena, memory_order_release);
  if (arena_id != 0)
  {
    *arena_id = arena;
  }
  return 1;
}


----------------------------
void mi_bbitmap_unsafe_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1482, __func__));
  ((idx + n) <= mi_bbitmap_max_bits(bbitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bbitmap_max_bits(bbitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1483, __func__));
  mi_bchunks_unsafe_setN(&bbitmap->chunks[0], &bbitmap->chunkmap, idx, n);
}


----------------------------
static mi_bbitmap_t *mi_arena_bbitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bbitmap_t *bbitmap = (mi_bbitmap_t *) (*base);
  *base = (*base) + mi_bbitmap_init(bbitmap, slice_count, 1);
  return bbitmap;
}


----------------------------
static size_t mi_arena_info_slices_needed(size_t slice_count, size_t *bitmap_base)
{
  if (slice_count == 0)
  {
    slice_count = 1 << (6 + 3);
  }
  ((slice_count % (1 << (6 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(slice_count % MI_BCHUNK_BITS) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1150, __func__));
  const size_t base_size = _mi_align_up(sizeof(mi_arena_t), (1 << (6 + 3)) / 8);
  const size_t bitmaps_count = 4 + ((73U + 1) + 1);
  const size_t bitmaps_size = (bitmaps_count * mi_bitmap_size(slice_count, 0)) + mi_bbitmap_size(slice_count, 0);
  const size_t size = base_size + bitmaps_size;
  const size_t os_page_size = _mi_os_page_size();
  const size_t info_size = _mi_align_up(size, os_page_size) + _mi_os_secure_guard_page_size();
  const size_t info_slices = mi_slice_count_of_size(info_size);
  if (bitmap_base != 0)
  {
    *bitmap_base = base_size;
  }
  return info_slices;
}


----------------------------
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg)
----------------------------
static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


----------------------------
bool _mi_os_secure_guard_page_set_before(void *addr, mi_memid_t memid)
{
  return _mi_os_secure_guard_page_set_at(((uint8_t *) addr) - _mi_os_secure_guard_page_size(), memid);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
static mi_bitmap_t *mi_arena_bitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bitmap_t *bitmap = (mi_bitmap_t *) (*base);
  *base = (*base) + mi_bitmap_init(bitmap, slice_count, 1);
  return bitmap;
}


----------------------------
None
----------------------------
inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
size_t _mi_os_secure_guard_page_size(void)
{
  return 0;
}


----------------------------
None
----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


----------------------------
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
void mi_bitmap_unsafe_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  (n > 0) ? ((void) 0) : (_mi_assert_fail("n>0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1105, __func__));
  ((idx + n) <= mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("idx + n <= mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1106, __func__));
  mi_bchunks_unsafe_setN(&bitmap->chunks[0], &bitmap->chunkmap, idx, n);
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}


----------------------------
None
----------------------------
***/


static int mi_reserve_os_memory_ex2(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  size = _mi_align_up(size, 1UL << (13 + 3));
  mi_memid_t memid;
  void *start = _mi_os_alloc_aligned(size, 1UL << (13 + 3), commit, allow_large, &memid);
  if (start == 0)
  {
    return 12;
  }
  if (!mi_manage_os_memory_ex2(subproc, start, size, -1, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free_ex(start, size, commit, memid, 0);
    _mi_verbose_message("failed to reserve %zu KiB memory\n", _mi_divide_up(size, 1024));
    return 12;
  }
  _mi_verbose_message("reserved %zu KiB memory%s\n", _mi_divide_up(size, 1024), (memid.is_pinned) ? (" (in large os pages)") : (""));
  return 0;
}


/*** DEPENDENCIES:
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
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
static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
}


----------------------------
typedef void *mi_arena_id_t
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
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
None
----------------------------
***/


int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  return mi_reserve_os_memory_ex2(_mi_subproc(), size, commit, allow_large, exclusive, arena_id);
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
typedef void *mi_arena_id_t
----------------------------
static int mi_reserve_os_memory_ex2(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  size = _mi_align_up(size, 1UL << (13 + 3));
  mi_memid_t memid;
  void *start = _mi_os_alloc_aligned(size, 1UL << (13 + 3), commit, allow_large, &memid);
  if (start == 0)
  {
    return 12;
  }
  if (!mi_manage_os_memory_ex2(subproc, start, size, -1, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free_ex(start, size, commit, memid, 0);
    _mi_verbose_message("failed to reserve %zu KiB memory\n", _mi_divide_up(size, 1024));
    return 12;
  }
  _mi_verbose_message("reserved %zu KiB memory%s\n", _mi_divide_up(size, 1024), (memid.is_pinned) ? (" (in large os pages)") : (""));
  return 0;
}


----------------------------
***/


int mi_reserve_os_memory(size_t size, bool commit, bool allow_large)
{
  return mi_reserve_os_memory_ex(size, commit, allow_large, 0, 0);
}


/*** DEPENDENCIES:
int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  return mi_reserve_os_memory_ex2(_mi_subproc(), size, commit, allow_large, exclusive, arena_id);
}


----------------------------
***/


void helper__mi_arenas_page_abandon_1(mi_page_t * const page, mi_tld_t * const tld)
{
  size_t bin = _mi_bin(mi_page_block_size(page));
  size_t slice_index;
  size_t slice_count;
  mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
  (!mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_singleton(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 894, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 895, __func__));
  ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 896, __func__));
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 897, __func__));
  mi_page_set_abandoned_mapped(page);
  const bool wasclear = mi_bitmap_set(arena->pages_abandoned[bin], slice_index);
  (void) wasclear;
  (wasclear) ? ((void) 0) : (_mi_assert_fail("wasclear", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 901, __func__));
  atomic_fetch_add_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
  __mi_stat_increase(&tld->stats.pages_abandoned, 1);
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_page_set_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 836, __func__));
  atomic_fetch_or_explicit(&page->xthread_id, 0x03UL + 1, memory_order_relaxed);
}


----------------------------
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
static mi_arena_t *mi_page_arena(mi_page_t *page, size_t *slice_index, size_t *slice_count)
{
  return mi_arena_from_memid(page->memid, slice_index, slice_count);
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
bool mi_bitmap_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_setN(bitmap, idx, 1, 0);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
inline static void mi_page_clear_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 841, __func__));
  atomic_fetch_and_explicit(&page->xthread_id, 0x03UL, memory_order_relaxed);
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
inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
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
mi_tld_t *_mi_thread_tld(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return &tld_empty;
  }
  else
  {
    return heap->tld;
  }
}


----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
static mi_arena_t *mi_page_arena(mi_page_t *page, size_t *slice_index, size_t *slice_count)
{
  return mi_arena_from_memid(page->memid, slice_index, slice_count);
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
None
----------------------------
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
}


----------------------------
void mi_bitmap_clear_once_set(mi_bitmap_t *bitmap, size_t idx)
{
  (idx < mi_bitmap_max_bits(bitmap)) ? ((void) 0) : (_mi_assert_fail("idx < mi_bitmap_max_bits(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1370, __func__));
  const size_t chunk_idx = idx / (1 << (6 + 3));
  const size_t cidx = idx % (1 << (6 + 3));
  (chunk_idx < mi_bitmap_chunk_count(bitmap)) ? ((void) 0) : (_mi_assert_fail("chunk_idx < mi_bitmap_chunk_count(bitmap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1373, __func__));
  mi_bchunk_clear_once_set(&bitmap->chunks[chunk_idx], cidx);
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


----------------------------
None
----------------------------
***/


void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 881, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 882, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 883, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 884, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 885, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 886, __func__));
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    helper__mi_arenas_page_abandon_1(page, tld);
  }
  else
  {
    mi_subproc_t *subproc = _mi_subproc();
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        page->prev = 0;
        page->next = subproc->os_abandoned_pages;
        if (page->next != 0)
        {
          page->next->prev = page;
        }
        subproc->os_abandoned_pages = page;
      }

    }
    __mi_stat_increase(&tld->stats.pages_abandoned, 1);
  }
  _mi_page_unown(page);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
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


----------------------------
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
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
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
void helper__mi_arenas_page_abandon_1(mi_page_t * const page, mi_tld_t * const tld)
{
  size_t bin = _mi_bin(mi_page_block_size(page));
  size_t slice_index;
  size_t slice_count;
  mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
  (!mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_singleton(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 894, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 895, __func__));
  ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 896, __func__));
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 897, __func__));
  mi_page_set_abandoned_mapped(page);
  const bool wasclear = mi_bitmap_set(arena->pages_abandoned[bin], slice_index);
  (void) wasclear;
  (wasclear) ? ((void) 0) : (_mi_assert_fail("wasclear", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 901, __func__));
  atomic_fetch_add_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
  __mi_stat_increase(&tld->stats.pages_abandoned, 1);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}


----------------------------
inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


----------------------------
None
----------------------------
***/


int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  if (pages == 0)
  {
    return 0;
  }
  if (numa_node < (-1))
  {
    numa_node = -1;
  }
  if (numa_node >= 0)
  {
    numa_node = numa_node % _mi_os_numa_node_count();
  }
  size_t hsize = 0;
  size_t pages_reserved = 0;
  mi_memid_t memid;
  void *p = _mi_os_alloc_huge_os_pages(pages, numa_node, timeout_msecs, &pages_reserved, &hsize, &memid);
  if ((p == 0) || (pages_reserved == 0))
  {
    _mi_warning_message("failed to reserve %zu GiB huge pages\n", pages);
    return 12;
  }
  _mi_verbose_message("numa node %i: reserved %zu GiB huge pages (of the %zu GiB requested)\n", numa_node, pages_reserved, pages);
  if (!mi_manage_os_memory_ex2(_mi_subproc(), p, hsize, numa_node, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free(p, hsize, memid);
    return 12;
  }
  return 0;
}


/*** DEPENDENCIES:
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


----------------------------
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid, 0);
}


----------------------------
None
----------------------------
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
static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
None
----------------------------
***/


int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs)
{
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}


/*** DEPENDENCIES:
int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  if (pages == 0)
  {
    return 0;
  }
  if (numa_node < (-1))
  {
    numa_node = -1;
  }
  if (numa_node >= 0)
  {
    numa_node = numa_node % _mi_os_numa_node_count();
  }
  size_t hsize = 0;
  size_t pages_reserved = 0;
  mi_memid_t memid;
  void *p = _mi_os_alloc_huge_os_pages(pages, numa_node, timeout_msecs, &pages_reserved, &hsize, &memid);
  if ((p == 0) || (pages_reserved == 0))
  {
    _mi_warning_message("failed to reserve %zu GiB huge pages\n", pages);
    return 12;
  }
  _mi_verbose_message("numa node %i: reserved %zu GiB huge pages (of the %zu GiB requested)\n", numa_node, pages_reserved, pages);
  if (!mi_manage_os_memory_ex2(_mi_subproc(), p, hsize, numa_node, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free(p, hsize, memid);
    return 12;
  }
  return 0;
}


----------------------------
***/


int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs)
{
  if (pages == 0)
  {
    return 0;
  }
  int numa_count = ((numa_nodes > 0) && (numa_nodes <= 2147483647)) ? ((int) numa_nodes) : (_mi_os_numa_node_count());
  if (numa_count <= 0)
  {
    numa_count = 1;
  }
  const size_t pages_per = pages / numa_count;
  const size_t pages_mod = pages % numa_count;
  const size_t timeout_per = (timeout_msecs == 0) ? (0) : ((timeout_msecs / numa_count) + 50);
  for (int numa_node = 0; (numa_node < numa_count) && (pages > 0); numa_node += 1)
  {
    size_t node_pages = pages_per;
    if (((size_t) numa_node) < pages_mod)
    {
      node_pages += 1;
    }
    int err = mi_reserve_huge_os_pages_at(node_pages, numa_node, timeout_per);
    if (err)
    {
      return err;
    }
    if (pages < node_pages)
    {
      pages = 0;
    }
    else
    {
      pages -= node_pages;
    }
  }

  return 0;
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
int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs)
{
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}


----------------------------
***/


static bool mi_arena_id_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena)
{
  return (arena == req_arena) || ((req_arena == 0) && (!arena->is_exclusive));
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_arena_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena, bool match_numa, int numa_node, bool allow_pinned)
{
  if ((!allow_pinned) && arena->memid.is_pinned)
  {
    return 0;
  }
  if (!mi_arena_id_is_suitable(arena, req_arena))
  {
    return 0;
  }
  if (req_arena == 0)
  {
    const bool numa_suitable = ((numa_node < 0) || (arena->numa_node < 0)) || (arena->numa_node == numa_node);
    if (match_numa)
    {
      if (!numa_suitable)
      {
        return 0;
      }
    }
    else
    {
      if (numa_suitable)
      {
        return 0;
      }
    }
  }
  return 1;
}


/*** DEPENDENCIES:
static bool mi_arena_id_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena)
{
  return (arena == req_arena) || ((req_arena == 0) && (!arena->is_exclusive));
}


----------------------------
None
----------------------------
***/


void *helper_mi_arena_try_alloc_at_1(mi_arena_t * const arena, size_t slice_count, mi_memid_t * const memid, size_t slice_index, void * const p, size_t touched_slices)
{
  const size_t already_committed = mi_bitmap_popcountN(arena->slices_committed, slice_index, slice_count);
  if (already_committed < slice_count)
  {
    bool commit_zero = 0;
    if (!_mi_os_commit_ex(p, mi_size_of_slices(slice_count), &commit_zero, mi_size_of_slices(slice_count - already_committed)))
    {
      mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
      return 0;
    }
    if (commit_zero)
    {
      memid->initially_zero = 1;
    }
    mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, 0);
    if (memid->initially_zero)
    {
      if (!mi_mem_is_zero(p, mi_size_of_slices(slice_count)))
      {
        _mi_error_message(14, "interal error: arena allocation was not zero-initialized!\n");
        memid->initially_zero = 0;
      }
    }
  }
  else
  {
    _mi_os_reuse(p, mi_size_of_slices(slice_count));
    if (_mi_os_has_overcommit() && (touched_slices > 0))
    {
      __mi_stat_increase_mt(&arena->subproc->stats.committed, mi_size_of_slices(touched_slices));
    }
  }
  (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 230, __func__));
  memid->initially_committed = 1;
  if (memid->initially_zero)
  {
    ;
  }
  else
  {
    ;
  }
}


/*** DEPENDENCIES:
None
----------------------------
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


----------------------------
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
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


----------------------------
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


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


static mi_memid_t mi_memid_create_arena(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (slice_index < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_index < UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 125, __func__));
  (slice_count < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_count < UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 126, __func__));
  (slice_count > 0) ? ((void) 0) : (_mi_assert_fail("slice_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 127, __func__));
  (slice_index < arena->slice_count) ? ((void) 0) : (_mi_assert_fail("slice_index < arena->slice_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 128, __func__));
  mi_memid_t memid = _mi_memid_create(MI_MEM_ARENA);
  memid.mem.arena.arena = arena;
  memid.mem.arena.slice_index = (uint32_t) slice_index;
  memid.mem.arena.slice_count = (uint32_t) slice_count;
  return memid;
}


/*** DEPENDENCIES:
None
----------------------------
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


/*** DEPENDENCIES:
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
bool mi_bbitmap_try_find_and_clear(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx)
{
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, 1, pidx, &mi_bchunk_try_find_and_clear_1);
}


----------------------------
bool mi_bbitmap_try_find_and_clear8(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx)
{
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, 8, pidx, &mi_bchunk_try_find_and_clear_8);
}


----------------------------
bool mi_bbitmap_try_find_and_clearNX(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx)
{
  (n <= (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BFIELD_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1723, __func__));
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, n, pidx, &mi_bchunk_try_find_and_clearNX);
}


----------------------------
bool mi_bbitmap_try_find_and_clearN_(mi_bbitmap_t *bbitmap, size_t tseq, size_t n, size_t *pidx)
{
  (n <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("n<=MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.c", 1728, __func__));
  return mi_bbitmap_try_find_and_clear_generic(bbitmap, tseq, n, pidx, &mi_bchunk_try_find_and_clearN_);
}


----------------------------
***/


static void *mi_arena_try_alloc_at(mi_arena_t *arena, size_t slice_count, bool commit, size_t tseq, mi_memid_t *memid)
{
  size_t slice_index;
  if (!mi_bbitmap_try_find_and_clearN(arena->slices_free, slice_count, tseq, &slice_index))
  {
    return 0;
  }
  void *p = mi_arena_slice_start(arena, slice_index);
  *memid = mi_memid_create_arena(arena, slice_index, slice_count);
  memid->is_pinned = arena->memid.is_pinned;
  size_t touched_slices = slice_count;
  if (arena->memid.initially_zero)
  {
    size_t already_dirty = 0;
    memid->initially_zero = mi_bitmap_setN(arena->slices_dirty, slice_index, slice_count, &already_dirty);
    (already_dirty <= touched_slices) ? ((void) 0) : (_mi_assert_fail("already_dirty <= touched_slices", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 186, __func__));
    touched_slices -= already_dirty;
  }
  if (commit)
  {
    helper_mi_arena_try_alloc_at_1(arena, slice_count, memid, slice_index, p, touched_slices);
  }
  else
  {
    memid->initially_committed = mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count);
    if (!memid->initially_committed)
    {
      size_t already_committed_count = 0;
      mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed_count);
      mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, mi_size_of_slices(already_committed_count));
    }
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 253, __func__));
  if (commit)
  {
    (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 254, __func__));
  }
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 255, __func__));
  }
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 256, __func__));
  return p;
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
static mi_memid_t mi_memid_create_arena(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (slice_index < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_index < UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 125, __func__));
  (slice_count < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_count < UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 126, __func__));
  (slice_count > 0) ? ((void) 0) : (_mi_assert_fail("slice_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 127, __func__));
  (slice_index < arena->slice_count) ? ((void) 0) : (_mi_assert_fail("slice_index < arena->slice_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 128, __func__));
  mi_memid_t memid = _mi_memid_create(MI_MEM_ARENA);
  memid.mem.arena.arena = arena;
  memid.mem.arena.slice_index = (uint32_t) slice_index;
  memid.mem.arena.slice_count = (uint32_t) slice_count;
  return memid;
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
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
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
void *helper_mi_arena_try_alloc_at_1(mi_arena_t * const arena, size_t slice_count, mi_memid_t * const memid, size_t slice_index, void * const p, size_t touched_slices)
{
  const size_t already_committed = mi_bitmap_popcountN(arena->slices_committed, slice_index, slice_count);
  if (already_committed < slice_count)
  {
    bool commit_zero = 0;
    if (!_mi_os_commit_ex(p, mi_size_of_slices(slice_count), &commit_zero, mi_size_of_slices(slice_count - already_committed)))
    {
      mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
      return 0;
    }
    if (commit_zero)
    {
      memid->initially_zero = 1;
    }
    mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, 0);
    if (memid->initially_zero)
    {
      if (!mi_mem_is_zero(p, mi_size_of_slices(slice_count)))
      {
        _mi_error_message(14, "interal error: arena allocation was not zero-initialized!\n");
        memid->initially_zero = 0;
      }
    }
  }
  else
  {
    _mi_os_reuse(p, mi_size_of_slices(slice_count));
    if (_mi_os_has_overcommit() && (touched_slices > 0))
    {
      __mi_stat_increase_mt(&arena->subproc->stats.committed, mi_size_of_slices(touched_slices));
    }
  }
  (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 230, __func__));
  memid->initially_committed = 1;
  if (memid->initially_zero)
  {
    ;
  }
  else
  {
    ;
  }
}


----------------------------
None
----------------------------
***/


void *helper_mi_arenas_try_find_free_1(mi_subproc_t * const subproc, size_t slice_count, bool commit, bool allow_large, mi_arena_t * const req_arena, size_t tseq, int numa_node, mi_memid_t * const memid)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (req_arena != 0)
    {
      arena_idx = req_arena;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        if (mi_arena_is_suitable(arena, req_arena, 1, numa_node, allow_large))
        {
          {
            void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
            if (p != 0)
            {
              return p;
            }
          }
        }
      }
    }
  }

}


/*** DEPENDENCIES:
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
static void *mi_arena_try_alloc_at(mi_arena_t *arena, size_t slice_count, bool commit, size_t tseq, mi_memid_t *memid)
{
  size_t slice_index;
  if (!mi_bbitmap_try_find_and_clearN(arena->slices_free, slice_count, tseq, &slice_index))
  {
    return 0;
  }
  void *p = mi_arena_slice_start(arena, slice_index);
  *memid = mi_memid_create_arena(arena, slice_index, slice_count);
  memid->is_pinned = arena->memid.is_pinned;
  size_t touched_slices = slice_count;
  if (arena->memid.initially_zero)
  {
    size_t already_dirty = 0;
    memid->initially_zero = mi_bitmap_setN(arena->slices_dirty, slice_index, slice_count, &already_dirty);
    (already_dirty <= touched_slices) ? ((void) 0) : (_mi_assert_fail("already_dirty <= touched_slices", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 186, __func__));
    touched_slices -= already_dirty;
  }
  if (commit)
  {
    helper_mi_arena_try_alloc_at_1(arena, slice_count, memid, slice_index, p, touched_slices);
  }
  else
  {
    memid->initially_committed = mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count);
    if (!memid->initially_committed)
    {
      size_t already_committed_count = 0;
      mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed_count);
      mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, mi_size_of_slices(already_committed_count));
    }
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 253, __func__));
  if (commit)
  {
    (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 254, __func__));
  }
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 255, __func__));
  }
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 256, __func__));
  return p;
}


----------------------------
inline static bool mi_arena_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena, bool match_numa, int numa_node, bool allow_pinned)
{
  if ((!allow_pinned) && arena->memid.is_pinned)
  {
    return 0;
  }
  if (!mi_arena_id_is_suitable(arena, req_arena))
  {
    return 0;
  }
  if (req_arena == 0)
  {
    const bool numa_suitable = ((numa_node < 0) || (arena->numa_node < 0)) || (arena->numa_node == numa_node);
    if (match_numa)
    {
      if (!numa_suitable)
      {
        return 0;
      }
    }
    else
    {
      if (numa_suitable)
      {
        return 0;
      }
    }
  }
  return 1;
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


void *helper_mi_arenas_try_find_free_2(mi_subproc_t * const subproc, size_t slice_count, bool commit, bool allow_large, mi_arena_t * const req_arena, size_t tseq, int numa_node, mi_memid_t * const memid)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (req_arena != 0)
    {
      arena_idx = req_arena;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        if (mi_arena_is_suitable(arena, req_arena, 0, numa_node, allow_large))
        {
          {
            void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
            if (p != 0)
            {
              return p;
            }
          }
        }
      }
    }
  }

}


/*** DEPENDENCIES:
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
static void *mi_arena_try_alloc_at(mi_arena_t *arena, size_t slice_count, bool commit, size_t tseq, mi_memid_t *memid)
{
  size_t slice_index;
  if (!mi_bbitmap_try_find_and_clearN(arena->slices_free, slice_count, tseq, &slice_index))
  {
    return 0;
  }
  void *p = mi_arena_slice_start(arena, slice_index);
  *memid = mi_memid_create_arena(arena, slice_index, slice_count);
  memid->is_pinned = arena->memid.is_pinned;
  size_t touched_slices = slice_count;
  if (arena->memid.initially_zero)
  {
    size_t already_dirty = 0;
    memid->initially_zero = mi_bitmap_setN(arena->slices_dirty, slice_index, slice_count, &already_dirty);
    (already_dirty <= touched_slices) ? ((void) 0) : (_mi_assert_fail("already_dirty <= touched_slices", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 186, __func__));
    touched_slices -= already_dirty;
  }
  if (commit)
  {
    helper_mi_arena_try_alloc_at_1(arena, slice_count, memid, slice_index, p, touched_slices);
  }
  else
  {
    memid->initially_committed = mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count);
    if (!memid->initially_committed)
    {
      size_t already_committed_count = 0;
      mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed_count);
      mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, mi_size_of_slices(already_committed_count));
    }
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 253, __func__));
  if (commit)
  {
    (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 254, __func__));
  }
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 255, __func__));
  }
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 256, __func__));
  return p;
}


----------------------------
inline static bool mi_arena_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena, bool match_numa, int numa_node, bool allow_pinned)
{
  if ((!allow_pinned) && arena->memid.is_pinned)
  {
    return 0;
  }
  if (!mi_arena_id_is_suitable(arena, req_arena))
  {
    return 0;
  }
  if (req_arena == 0)
  {
    const bool numa_suitable = ((numa_node < 0) || (arena->numa_node < 0)) || (arena->numa_node == numa_node);
    if (match_numa)
    {
      if (!numa_suitable)
      {
        return 0;
      }
    }
    else
    {
      if (numa_suitable)
      {
        return 0;
      }
    }
  }
  return 1;
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


static void *mi_arenas_try_find_free(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= mi_slice_count_of_size((1 << (6 + 3)) * (1UL << (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("slice_count <= mi_slice_count_of_size(MI_ARENA_MAX_OBJ_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 391, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 392, __func__));
  if (alignment > (1UL << (13 + 3)))
  {
    return 0;
  }
  {
    helper_mi_arenas_try_find_free_1(subproc, slice_count, commit, allow_large, req_arena, tseq, numa_node, memid);
  }
  ;
  if (numa_node < 0)
  {
    return 0;
  }
  {
    helper_mi_arenas_try_find_free_2(subproc, slice_count, commit, allow_large, req_arena, tseq, numa_node, memid);
  }
  ;
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
void *helper_mi_arenas_try_find_free_2(mi_subproc_t * const subproc, size_t slice_count, bool commit, bool allow_large, mi_arena_t * const req_arena, size_t tseq, int numa_node, mi_memid_t * const memid)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (req_arena != 0)
    {
      arena_idx = req_arena;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        if (mi_arena_is_suitable(arena, req_arena, 0, numa_node, allow_large))
        {
          {
            void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
            if (p != 0)
            {
              return p;
            }
          }
        }
      }
    }
  }

}


----------------------------
void *helper_mi_arenas_try_find_free_1(mi_subproc_t * const subproc, size_t slice_count, bool commit, bool allow_large, mi_arena_t * const req_arena, size_t tseq, int numa_node, mi_memid_t * const memid)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (req_arena != 0)
    {
      arena_idx = req_arena;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        if (mi_arena_is_suitable(arena, req_arena, 1, numa_node, allow_large))
        {
          {
            void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
            if (p != 0)
            {
              return p;
            }
          }
        }
      }
    }
  }

}


----------------------------
None
----------------------------
***/


static bool mi_arena_reserve(mi_subproc_t *subproc, size_t req_size, bool allow_large, mi_arena_id_t *arena_id)
{
  const size_t arena_count = mi_arenas_get_count(subproc);
  if (arena_count > (160 - 4))
  {
    return 0;
  }
  size_t arena_reserve = mi_option_get_size(mi_option_arena_reserve);
  if (arena_reserve == 0)
  {
    return 0;
  }
  if (!_mi_os_has_virtual_reserve())
  {
    arena_reserve = arena_reserve / 4;
  }
  arena_reserve = _mi_align_up(arena_reserve, 1UL << (13 + 3));
  if ((arena_count >= 1) && (arena_count <= 128))
  {
    const size_t multiplier = ((size_t) 1) << _mi_clamp(arena_count / 4, 0, 16);
    size_t reserve = 0;
    if (!mi_mul_overflow(multiplier, arena_reserve, &reserve))
    {
      arena_reserve = reserve;
    }
  }
  const size_t min_reserve = (1 << (6 + 3)) * (1UL << (13 + 3));
  const size_t max_reserve = ((1 << (6 + 3)) * (1 << (6 + 3))) * (1UL << (13 + 3));
  if (arena_reserve < min_reserve)
  {
    arena_reserve = min_reserve;
  }
  else
    if (arena_reserve > max_reserve)
  {
    arena_reserve = max_reserve;
  }
  if (arena_reserve < req_size)
  {
    return 0;
  }
  bool arena_commit = 0;
  const bool overcommit = _mi_os_has_overcommit();
  if (mi_option_get(mi_option_arena_eager_commit) == 2)
  {
    arena_commit = overcommit;
  }
  else
    if (mi_option_get(mi_option_arena_eager_commit) == 1)
  {
    arena_commit = 1;
  }
  const bool adjust = overcommit && arena_commit;
  if (adjust)
  {
    __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
  }
  int err = mi_reserve_os_memory_ex2(subproc, arena_reserve, arena_commit, allow_large, 0, arena_id);
  if (err != 0)
  {
    if (adjust)
    {
      __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
    }
    const size_t small_arena_reserve = (((1 << 3) * 8) == 32) ? (128 * (1024UL * 1024UL)) : (1 * ((1024UL * 1024UL) * 1024UL));
    if (adjust)
    {
      __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
    }
    if (arena_reserve > small_arena_reserve)
    {
      err = mi_reserve_os_memory_ex(small_arena_reserve, arena_commit, allow_large, 0, arena_id);
      if ((err != 0) && adjust)
      {
        __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
      }
    }
  }
  return err == 0;
}


/*** DEPENDENCIES:
bool _mi_os_has_virtual_reserve(void)
{
  return mi_os_mem_config.has_virtual_reserve;
}


----------------------------
None
----------------------------
int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  return mi_reserve_os_memory_ex2(_mi_subproc(), size, commit, allow_large, exclusive, arena_id);
}


----------------------------
size_t mi_option_get_size(mi_option_t option)
{
  const long x = mi_option_get(option);
  size_t size = (x < 0) ? (0) : ((size_t) x);
  if (mi_option_has_size_in_kib(option))
  {
    size *= 1024UL;
  }
  return size;
}


----------------------------
inline static bool mi_mul_overflow(size_t count, size_t size, size_t *total)
{
  return __builtin_umulll_overflow(count, size, (unsigned long long *) total);
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


----------------------------
void __mi_stat_adjust_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_adjust_mt(stat, (int64_t) amount);
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
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
static int mi_reserve_os_memory_ex2(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  size = _mi_align_up(size, 1UL << (13 + 3));
  mi_memid_t memid;
  void *start = _mi_os_alloc_aligned(size, 1UL << (13 + 3), commit, allow_large, &memid);
  if (start == 0)
  {
    return 12;
  }
  if (!mi_manage_os_memory_ex2(subproc, start, size, -1, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free_ex(start, size, commit, memid, 0);
    _mi_verbose_message("failed to reserve %zu KiB memory\n", _mi_divide_up(size, 1024));
    return 12;
  }
  _mi_verbose_message("reserved %zu KiB memory%s\n", _mi_divide_up(size, 1024), (memid.is_pinned) ? (" (in large os pages)") : (""));
  return 0;
}


----------------------------
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


----------------------------
void __mi_stat_adjust_decrease_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_adjust_mt(stat, -((int64_t) amount));
}


----------------------------
None
----------------------------
***/


static void *mi_arenas_try_alloc(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("slice_count <= MI_ARENA_MAX_OBJ_SLICES", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 421, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 422, __func__));
  void *p;
  unsigned int p_idx = 0;
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  if (req_arena != 0)
  {
    return 0;
  }
  if (_mi_preloading())
  {
    return 0;
  }
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (bool _go = (mi_lock_acquire(&subproc->arena_reserve_lock), 1); _go; mi_lock_release(&subproc->arena_reserve_lock), _go = 0)
  {
    if (arena_count == mi_arenas_get_count(subproc))
    {
      mi_arena_id_t arena_id = 0;
      mi_arena_reserve(subproc, mi_size_of_slices(slice_count), allow_large, &arena_id);
    }
    else
    {
    }
  }

  (req_arena == 0) ? ((void) 0) : (_mi_assert_fail("req_arena == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 448, __func__));
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
bool _mi_preloading(void)
{
  return os_preloading;
}


----------------------------
static bool mi_arena_reserve(mi_subproc_t *subproc, size_t req_size, bool allow_large, mi_arena_id_t *arena_id)
{
  const size_t arena_count = mi_arenas_get_count(subproc);
  if (arena_count > (160 - 4))
  {
    return 0;
  }
  size_t arena_reserve = mi_option_get_size(mi_option_arena_reserve);
  if (arena_reserve == 0)
  {
    return 0;
  }
  if (!_mi_os_has_virtual_reserve())
  {
    arena_reserve = arena_reserve / 4;
  }
  arena_reserve = _mi_align_up(arena_reserve, 1UL << (13 + 3));
  if ((arena_count >= 1) && (arena_count <= 128))
  {
    const size_t multiplier = ((size_t) 1) << _mi_clamp(arena_count / 4, 0, 16);
    size_t reserve = 0;
    if (!mi_mul_overflow(multiplier, arena_reserve, &reserve))
    {
      arena_reserve = reserve;
    }
  }
  const size_t min_reserve = (1 << (6 + 3)) * (1UL << (13 + 3));
  const size_t max_reserve = ((1 << (6 + 3)) * (1 << (6 + 3))) * (1UL << (13 + 3));
  if (arena_reserve < min_reserve)
  {
    arena_reserve = min_reserve;
  }
  else
    if (arena_reserve > max_reserve)
  {
    arena_reserve = max_reserve;
  }
  if (arena_reserve < req_size)
  {
    return 0;
  }
  bool arena_commit = 0;
  const bool overcommit = _mi_os_has_overcommit();
  if (mi_option_get(mi_option_arena_eager_commit) == 2)
  {
    arena_commit = overcommit;
  }
  else
    if (mi_option_get(mi_option_arena_eager_commit) == 1)
  {
    arena_commit = 1;
  }
  const bool adjust = overcommit && arena_commit;
  if (adjust)
  {
    __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
  }
  int err = mi_reserve_os_memory_ex2(subproc, arena_reserve, arena_commit, allow_large, 0, arena_id);
  if (err != 0)
  {
    if (adjust)
    {
      __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
    }
    const size_t small_arena_reserve = (((1 << 3) * 8) == 32) ? (128 * (1024UL * 1024UL)) : (1 * ((1024UL * 1024UL) * 1024UL));
    if (adjust)
    {
      __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
    }
    if (arena_reserve > small_arena_reserve)
    {
      err = mi_reserve_os_memory_ex(small_arena_reserve, arena_commit, allow_large, 0, arena_id);
      if ((err != 0) && adjust)
      {
        __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
      }
    }
  }
  return err == 0;
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


----------------------------
inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


----------------------------
static void *mi_arenas_try_find_free(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= mi_slice_count_of_size((1 << (6 + 3)) * (1UL << (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("slice_count <= mi_slice_count_of_size(MI_ARENA_MAX_OBJ_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 391, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 392, __func__));
  if (alignment > (1UL << (13 + 3)))
  {
    return 0;
  }
  {
    helper_mi_arenas_try_find_free_1(subproc, slice_count, commit, allow_large, req_arena, tseq, numa_node, memid);
  }
  ;
  if (numa_node < 0)
  {
    return 0;
  }
  {
    helper_mi_arenas_try_find_free_2(subproc, slice_count, commit, allow_large, req_arena, tseq, numa_node, memid);
  }
  ;
  return 0;
}


----------------------------
None
----------------------------
***/


static void *mi_arena_os_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid)
{
  if (mi_option_is_enabled(mi_option_disallow_os_alloc) || (req_arena_id != _mi_arena_id_none()))
  {
    errno = 12;
    return 0;
  }
  if (align_offset > 0)
  {
    return _mi_os_alloc_aligned_at_offset(size, alignment, align_offset, commit, allow_large, memid);
  }
  else
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
}


/*** DEPENDENCIES:
None
----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
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


----------------------------
typedef void *mi_arena_id_t
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
static void *mi_arenas_try_alloc(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("slice_count <= MI_ARENA_MAX_OBJ_SLICES", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 421, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 422, __func__));
  void *p;
  unsigned int p_idx = 0;
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  if (req_arena != 0)
  {
    return 0;
  }
  if (_mi_preloading())
  {
    return 0;
  }
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (bool _go = (mi_lock_acquire(&subproc->arena_reserve_lock), 1); _go; mi_lock_release(&subproc->arena_reserve_lock), _go = 0)
  {
    if (arena_count == mi_arenas_get_count(subproc))
    {
      mi_arena_id_t arena_id = 0;
      mi_arena_reserve(subproc, mi_size_of_slices(slice_count), allow_large, &arena_id);
    }
    else
    {
    }
  }

  (req_arena == 0) ? ((void) 0) : (_mi_assert_fail("req_arena == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 448, __func__));
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  return 0;
}


----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
static void *mi_arena_os_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid)
{
  if (mi_option_is_enabled(mi_option_disallow_os_alloc) || (req_arena_id != _mi_arena_id_none()))
  {
    errno = 12;
    return 0;
  }
  if (align_offset > 0)
  {
    return _mi_os_alloc_aligned_at_offset(size, alignment, align_offset, commit, allow_large, memid);
  }
  else
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
}


----------------------------
None
----------------------------
***/


void *_mi_arenas_alloc(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  return _mi_arenas_alloc_aligned(subproc, size, 1UL << (13 + 3), 0, commit, allow_large, req_arena, tseq, numa_node, memid);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}


/*** DEPENDENCIES:
typedef void *mi_arena_id_t
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static bool mi_arena_id_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena)
{
  return (arena == req_arena) || ((req_arena == 0) && (!arena->is_exclusive));
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}


----------------------------
mi_tld_t *_mi_thread_tld(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return &tld_empty;
  }
  else
  {
    return heap->tld;
  }
}


----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 881, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 882, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 883, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 884, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 885, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 886, __func__));
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    helper__mi_arenas_page_abandon_1(page, tld);
  }
  else
  {
    mi_subproc_t *subproc = _mi_subproc();
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        page->prev = 0;
        page->next = subproc->os_abandoned_pages;
        if (page->next != 0)
        {
          page->next->prev = page;
        }
        subproc->os_abandoned_pages = page;
      }

    }
    __mi_stat_increase(&tld->stats.pages_abandoned, 1);
  }
  _mi_page_unown(page);
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
void __mi_stat_adjust_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_adjust(stat, -((int64_t) amount));
}


----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
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


static bool mi_arena_try_claim_abandoned(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_abandoned)
{
  mi_page_t * const page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  if (!mi_page_try_claim_ownership(page))
  {
    *keep_abandoned = 1;
    return 0;
  }
  if (heap_tag != page->heap_tag)
  {
    const bool freed = _mi_page_unown(page);
    *keep_abandoned = !freed;
    return 0;
  }
  *keep_abandoned = 0;
  return 1;
}


/*** DEPENDENCIES:
inline static bool mi_page_try_claim_ownership(mi_page_t *page)
{
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free, 1, memory_order_acq_rel);
  return (old & 1) == 0;
}


----------------------------
typedef uint8_t mi_heaptag_t
----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
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


----------------------------
None
----------------------------
***/


static bool mi_arena_has_page(mi_arena_t *arena, mi_page_t *page)
{
  return ((page->memid.memkind == MI_MEM_ARENA) && (page->memid.mem.arena.arena == arena)) && mi_bitmap_is_setN(arena->pages, page->memid.mem.arena.slice_index, 1);
}


/*** DEPENDENCIES:
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
None
----------------------------
***/


mi_page_t *helper_helper_helper_mi_arenas_page_try_find_abandoned_1_1_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa, mi_arena_t * const arena)
{
  {
    if (mi_arena_is_suitable(arena, req_arena, match_numa, any_numa, allow_large))
    {
      {
        size_t slice_index;
        mi_bitmap_t * const bitmap = arena->pages_abandoned[bin];
        if (mi_bitmap_try_find_and_claim(bitmap, tseq, &slice_index, &mi_arena_try_claim_abandoned, arena, heaptag))
        {
          mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
          (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 563, __func__));
          (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 564, __func__));
          (mi_arena_has_page(arena, page)) ? ((void) 0) : (_mi_assert_fail("mi_arena_has_page(arena,page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 565, __func__));
          atomic_fetch_sub_explicit(&subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
          mi_tld_t *tld = _mi_thread_tld();
          __mi_stat_decrease(&tld->stats.pages_abandoned, 1);
          __mi_stat_counter_increase(&tld->stats.pages_reclaim_on_alloc, 1);
          _mi_page_free_collect(page, 0);
          (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 572, __func__));
          ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 573, __func__));
          (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 574, __func__));
          (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 575, __func__));
          (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 576, __func__));
          (_mi_ptr_page(mi_page_start(page)) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 577, __func__));
          (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 578, __func__));
          (!mi_page_is_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 579, __func__));
          return page;
        }
      }
    }
  }
}


/*** DEPENDENCIES:
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
static bool mi_arena_has_page(mi_arena_t *arena, mi_page_t *page)
{
  return ((page->memid.memkind == MI_MEM_ARENA) && (page->memid.mem.arena.arena == arena)) && mi_bitmap_is_setN(arena->pages, page->memid.mem.arena.slice_index, 1);
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
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static bool mi_arena_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena, bool match_numa, int numa_node, bool allow_pinned)
{
  if ((!allow_pinned) && arena->memid.is_pinned)
  {
    return 0;
  }
  if (!mi_arena_id_is_suitable(arena, req_arena))
  {
    return 0;
  }
  if (req_arena == 0)
  {
    const bool numa_suitable = ((numa_node < 0) || (arena->numa_node < 0)) || (arena->numa_node == numa_node);
    if (match_numa)
    {
      if (!numa_suitable)
      {
        return 0;
      }
    }
    else
    {
      if (numa_suitable)
      {
        return 0;
      }
    }
  }
  return 1;
}


----------------------------
None
----------------------------
mi_tld_t *_mi_thread_tld(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return &tld_empty;
  }
  else
  {
    return heap->tld;
  }
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
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
typedef uint8_t mi_heaptag_t
----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
}


----------------------------
static bool mi_arena_try_claim_abandoned(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_abandoned)
{
  mi_page_t * const page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  if (!mi_page_try_claim_ownership(page))
  {
    *keep_abandoned = 1;
    return 0;
  }
  if (heap_tag != page->heap_tag)
  {
    const bool freed = _mi_page_unown(page);
    *keep_abandoned = !freed;
    return 0;
  }
  *keep_abandoned = 0;
  return 1;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
bool mi_bitmap_try_find_and_claim(mi_bitmap_t *bitmap, size_t tseq, size_t *pidx, mi_claim_fun_t *claim, mi_arena_t *arena, mi_heaptag_t heap_tag)
{
  mi_claim_fun_data_t claim_data = {arena, heap_tag};
  return mi_bitmap_find(bitmap, tseq, 1, pidx, &mi_bitmap_try_find_and_claim_visit, (void *) claim, &claim_data);
}


----------------------------
None
----------------------------
***/


mi_page_t *helper_helper_mi_arenas_page_try_find_abandoned_1_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa, const size_t _arena_cycle, size_t _start, size_t _i)
{
  mi_arena_t *arena;
  unsigned int arena_idx = 0;
  if (req_arena != 0)
  {
    arena_idx = req_arena;
    if (_i > 0)
    {
      break;
    }
  }
  else
  {
    size_t _idx;
    if (_i < _arena_cycle)
    {
      _idx = _i + _start;
      if (_idx >= _arena_cycle)
      {
        _idx -= _arena_cycle;
      }
    }
    else
    {
      _idx = _i;
    }
    arena_idx = mi_arena_from_index(subproc, _idx);
  }
  if ((&arena[arena_idx]) != 0)
  {
    helper_helper_helper_mi_arenas_page_try_find_abandoned_1_1_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa, arena);
  }
}


/*** DEPENDENCIES:
typedef uint8_t mi_heaptag_t
----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
mi_page_t *helper_helper_helper_mi_arenas_page_try_find_abandoned_1_1_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa, mi_arena_t * const arena)
{
  {
    if (mi_arena_is_suitable(arena, req_arena, match_numa, any_numa, allow_large))
    {
      {
        size_t slice_index;
        mi_bitmap_t * const bitmap = arena->pages_abandoned[bin];
        if (mi_bitmap_try_find_and_claim(bitmap, tseq, &slice_index, &mi_arena_try_claim_abandoned, arena, heaptag))
        {
          mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
          (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 563, __func__));
          (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 564, __func__));
          (mi_arena_has_page(arena, page)) ? ((void) 0) : (_mi_assert_fail("mi_arena_has_page(arena,page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 565, __func__));
          atomic_fetch_sub_explicit(&subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
          mi_tld_t *tld = _mi_thread_tld();
          __mi_stat_decrease(&tld->stats.pages_abandoned, 1);
          __mi_stat_counter_increase(&tld->stats.pages_reclaim_on_alloc, 1);
          _mi_page_free_collect(page, 0);
          (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 572, __func__));
          ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 573, __func__));
          (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 574, __func__));
          (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 575, __func__));
          (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 576, __func__));
          (_mi_ptr_page(mi_page_start(page)) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 577, __func__));
          (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 578, __func__));
          (!mi_page_is_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 579, __func__));
          return page;
        }
      }
    }
  }
}


----------------------------
None
----------------------------
***/


mi_page_t *helper_mi_arenas_page_try_find_abandoned_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    helper_helper_mi_arenas_page_try_find_abandoned_1_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa, _arena_cycle, _start, _i);
  }

}


/*** DEPENDENCIES:
typedef uint8_t mi_heaptag_t
----------------------------
mi_page_t *helper_helper_mi_arenas_page_try_find_abandoned_1_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa, const size_t _arena_cycle, size_t _start, size_t _i)
{
  mi_arena_t *arena;
  unsigned int arena_idx = 0;
  if (req_arena != 0)
  {
    arena_idx = req_arena;
    if (_i > 0)
    {
      break;
    }
  }
  else
  {
    size_t _idx;
    if (_i < _arena_cycle)
    {
      _idx = _i + _start;
      if (_idx >= _arena_cycle)
      {
        _idx -= _arena_cycle;
      }
    }
    else
    {
      _idx = _i;
    }
    arena_idx = mi_arena_from_index(subproc, _idx);
  }
  if ((&arena[arena_idx]) != 0)
  {
    helper_helper_helper_mi_arenas_page_try_find_abandoned_1_1_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa, arena);
  }
}


----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_arenas_page_try_find_abandoned(mi_subproc_t *subproc, size_t slice_count, size_t block_size, mi_arena_t *req_arena, mi_heaptag_t heaptag, size_t tseq)
{
  (void) slice_count;
  const size_t bin = _mi_bin(block_size);
  (bin < ((73U + 1) + 1)) ? ((void) 0) : (_mi_assert_fail("bin < MI_BIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 542, __func__));
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 545, __func__));
  if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) == 0)
  {
    return 0;
  }
  const bool allow_large = 1;
  const int any_numa = -1;
  const bool match_numa = 1;
  {
    helper_mi_arenas_page_try_find_abandoned_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa);
  }
  ;
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
typedef uint8_t mi_heaptag_t
----------------------------
mi_page_t *helper_mi_arenas_page_try_find_abandoned_1(mi_subproc_t * const subproc, size_t slice_count, size_t block_size, mi_arena_t * const req_arena, mi_heaptag_t heaptag, size_t tseq, const size_t bin, const bool allow_large, const int any_numa, const bool match_numa)
{
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    helper_helper_mi_arenas_page_try_find_abandoned_1_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa, _arena_cycle, _start, _i);
  }

}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
None
----------------------------
***/


static bool mi_arena_commit(mi_arena_t *arena, void *start, size_t size, bool *is_zero, size_t already_committed)
{
  if ((arena != 0) && (arena->commit_fun != 0))
  {
    return (*arena->commit_fun)(1, start, size, is_zero, arena->commit_fun_arg);
  }
  else
    if (already_committed > 0)
  {
    return _mi_os_commit_ex(start, size, is_zero, already_committed);
  }
  else
  {
    return _mi_os_commit(start, size, is_zero);
  }
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
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_arenas_page_alloc_fresh(size_t slice_count, size_t block_size, size_t block_alignment, mi_arena_t *req_arena, int numa_node, bool commit, mi_tld_t *tld)
{
  const bool allow_large = 0 < 2;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t page_alignment = 1UL << (13 + 3);
  mi_memid_t memid = _mi_memid_none();
  mi_page_t *page = 0;
  unsigned int page_idx = 0;
  const size_t alloc_size = mi_size_of_slices(slice_count);
  if (((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (!os_align)) && (slice_count <= (1 << (6 + 3))))
  {
    page_idx = (mi_page_t *) mi_arenas_try_alloc(tld->subproc, slice_count, page_alignment, commit, allow_large, req_arena, tld->thread_seq, numa_node, &memid);
    if ((&page[page_idx]) != 0)
    {
      (mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 605, __func__));
      mi_bitmap_set(memid.mem.arena.arena->pages, memid.mem.arena.slice_index);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    if (os_align)
    {
      (slice_count >= (mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment))) ? ((void) 0) : (_mi_assert_fail("slice_count >= mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 614, __func__));
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, block_alignment, page_alignment, commit, allow_large, req_arena, &memid);
    }
    else
    {
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, page_alignment, 0, commit, allow_large, req_arena, &memid);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 623, __func__));
  ((!os_align) || _mi_is_aligned(((uint8_t *) page) + page_alignment, block_alignment)) ? ((void) 0) : (_mi_assert_fail("!os_align || _mi_is_aligned((uint8_t*)page + page_alignment, block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 624, __func__));
  const size_t page_noguard_size = alloc_size;
  if ((!memid.initially_zero) && memid.initially_committed)
  {
    ;
    _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
  }
  else
    if (memid.initially_committed)
  {
    ;
  }
  if (memid.initially_zero && memid.initially_committed)
  {
    if (!mi_mem_is_zero(page, page_noguard_size))
    {
      _mi_error_message(14, "internal error: page memory was not zero initialized.\n");
      memid.initially_zero = 0;
      _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
    }
  }
  (((3 + 2) * 32) >= mi_page_info_size()) ? ((void) 0) : (_mi_assert_fail("MI_PAGE_INFO_SIZE >= mi_page_info_size()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 654, __func__));
  size_t block_start;
  if (os_align)
  {
    block_start = 1UL << (13 + 3);
  }
  else
    if (_mi_is_power_of_two(block_size) && (block_size <= 1024UL))
  {
    block_start = _mi_align_up(mi_page_info_size(), block_size);
  }
  else
  {
    block_start = mi_page_info_size();
  }
  const size_t reserved = (os_align) ? (1) : ((page_noguard_size - block_start) / block_size);
  ((reserved > 0) && (reserved <= UINT16_MAX)) ? ((void) 0) : (_mi_assert_fail("reserved > 0 && reserved <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 679, __func__));
  size_t commit_size = 0;
  if (!memid.initially_committed)
  {
    commit_size = _mi_align_up(block_start + block_size, 1UL << (13 + 3));
    if (commit_size > page_noguard_size)
    {
      commit_size = page_noguard_size;
    }
    bool is_zero;
    if (__builtin_expect(!(!(!mi_arena_commit(mi_memid_arena(memid), page, commit_size, &is_zero, 0))), 0))
    {
      _mi_arenas_free(page, alloc_size, memid);
      return 0;
    }
    if ((!memid.initially_zero) && (!is_zero))
    {
      _mi_memzero_aligned(page, commit_size);
    }
  }
  page->reserved = (uint16_t) reserved;
  page->page_start = ((uint8_t *) page) + block_start;
  page->block_size = block_size;
  page->slice_committed = commit_size;
  page->memid = memid;
  page->free_is_zero = memid.initially_zero;
  mi_page_try_claim_ownership(page);
  if (__builtin_expect(!(!(!_mi_page_map_register(page))), 0))
  {
    _mi_arenas_free(page, alloc_size, memid);
    return 0;
  }
  __mi_stat_increase(&tld->stats.pages, 1);
  __mi_stat_increase(&tld->stats.page_bins[_mi_page_bin(page)], 1);
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 717, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 718, __func__));
  (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 719, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 720, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 721, __func__));
  return page;
}


/*** DEPENDENCIES:
size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 172, __func__));
  return bin;
}


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
inline static size_t mi_page_info_size(void)
{
  return _mi_align_up(sizeof(mi_page_t), 16);
}


----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
static bool mi_arena_commit(mi_arena_t *arena, void *start, size_t size, bool *is_zero, size_t already_committed)
{
  if ((arena != 0) && (arena->commit_fun != 0))
  {
    return (*arena->commit_fun)(1, start, size, is_zero, arena->commit_fun_arg);
  }
  else
    if (already_committed > 0)
  {
    return _mi_os_commit_ex(start, size, is_zero, already_committed);
  }
  else
  {
    return _mi_os_commit(start, size, is_zero);
  }
}


----------------------------
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
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


----------------------------
inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static bool mi_page_try_claim_ownership(mi_page_t *page)
{
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free, 1, memory_order_acq_rel);
  return (old & 1) == 0;
}


----------------------------
bool mi_bitmap_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_setN(bitmap, idx, 1, 0);
}


----------------------------
None
----------------------------
inline static mi_arena_t *mi_memid_arena(mi_memid_t memid)
{
  return (memid.memkind == MI_MEM_ARENA) ? (memid.mem.arena.arena) : (0);
}


----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
None
----------------------------
static void *mi_arena_os_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid)
{
  if (mi_option_is_enabled(mi_option_disallow_os_alloc) || (req_arena_id != _mi_arena_id_none()))
  {
    errno = 12;
    return 0;
  }
  if (align_offset > 0)
  {
    return _mi_os_alloc_aligned_at_offset(size, alignment, align_offset, commit, allow_large, memid);
  }
  else
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
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


----------------------------
static void *mi_arenas_try_alloc(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("slice_count <= MI_ARENA_MAX_OBJ_SLICES", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 421, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 422, __func__));
  void *p;
  unsigned int p_idx = 0;
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  if (req_arena != 0)
  {
    return 0;
  }
  if (_mi_preloading())
  {
    return 0;
  }
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (bool _go = (mi_lock_acquire(&subproc->arena_reserve_lock), 1); _go; mi_lock_release(&subproc->arena_reserve_lock), _go = 0)
  {
    if (arena_count == mi_arenas_get_count(subproc))
    {
      mi_arena_id_t arena_id = 0;
      mi_arena_reserve(subproc, mi_size_of_slices(slice_count), allow_large, &arena_id);
    }
    else
    {
    }
  }

  (req_arena == 0) ? ((void) 0) : (_mi_assert_fail("req_arena == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 448, __func__));
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  return 0;
}


----------------------------
None
----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
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


static mi_page_t *mi_arenas_page_regular_alloc(mi_heap_t *heap, size_t slice_count, size_t block_size)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  mi_page_t *page = mi_arenas_page_try_find_abandoned(tld->subproc, slice_count, block_size, req_arena, heap->tag, tld->thread_seq);
  unsigned int page_idx = 0;
  if ((&page[page_idx]) != 0)
  {
    return page;
  }
  const long commit_on_demand = mi_option_get(mi_option_page_commit_on_demand);
  const bool commit = ((slice_count <= mi_slice_count_of_size(1UL << (13 + 3))) || ((commit_on_demand == 2) && _mi_os_has_overcommit())) || (commit_on_demand == 0);
  page_idx = mi_arenas_page_alloc_fresh(slice_count, block_size, 1, req_arena, heap->numa_node, commit, tld);
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  ((page->memid.memkind != MI_MEM_ARENA) || (page->memid.mem.arena.slice_count == slice_count)) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind != MI_MEM_ARENA || page->memid.mem.arena.slice_count == slice_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 744, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
}


/*** DEPENDENCIES:
bool _mi_page_init(mi_heap_t *heap, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 673, __func__));
  mi_page_set_heap(page, heap);
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  (void) page_start;
  ;
  ((page_size / mi_page_block_size(page)) < (1L << 16)) ? ((void) 0) : (_mi_assert_fail("page_size / mi_page_block_size(page) < (1L<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 679, __func__));
  (page->reserved > 0) ? ((void) 0) : (_mi_assert_fail("page->reserved > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 680, __func__));
  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
  (page->capacity == 0) ? ((void) 0) : (_mi_assert_fail("page->capacity == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 692, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 693, __func__));
  (page->used == 0) ? ((void) 0) : (_mi_assert_fail("page->used == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 694, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 695, __func__));
  (page->xthread_free == 1) ? ((void) 0) : (_mi_assert_fail("page->xthread_free == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 696, __func__));
  (page->next == 0) ? ((void) 0) : (_mi_assert_fail("page->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 697, __func__));
  (page->prev == 0) ? ((void) 0) : (_mi_assert_fail("page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 698, __func__));
  (page->retire_expire == 0) ? ((void) 0) : (_mi_assert_fail("page->retire_expire == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 699, __func__));
  (!mi_page_has_interior_pointers(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_has_interior_pointers(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 700, __func__));
  (page->keys[0] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[0] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 702, __func__));
  (page->keys[1] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[1] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 703, __func__));
  ;
  if (!mi_page_extend_free(heap, page))
  {
    return 0;
  }
  (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 709, __func__));
  return 1;
}


----------------------------
None
----------------------------
None
----------------------------
static mi_page_t *mi_arenas_page_alloc_fresh(size_t slice_count, size_t block_size, size_t block_alignment, mi_arena_t *req_arena, int numa_node, bool commit, mi_tld_t *tld)
{
  const bool allow_large = 0 < 2;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t page_alignment = 1UL << (13 + 3);
  mi_memid_t memid = _mi_memid_none();
  mi_page_t *page = 0;
  unsigned int page_idx = 0;
  const size_t alloc_size = mi_size_of_slices(slice_count);
  if (((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (!os_align)) && (slice_count <= (1 << (6 + 3))))
  {
    page_idx = (mi_page_t *) mi_arenas_try_alloc(tld->subproc, slice_count, page_alignment, commit, allow_large, req_arena, tld->thread_seq, numa_node, &memid);
    if ((&page[page_idx]) != 0)
    {
      (mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 605, __func__));
      mi_bitmap_set(memid.mem.arena.arena->pages, memid.mem.arena.slice_index);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    if (os_align)
    {
      (slice_count >= (mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment))) ? ((void) 0) : (_mi_assert_fail("slice_count >= mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 614, __func__));
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, block_alignment, page_alignment, commit, allow_large, req_arena, &memid);
    }
    else
    {
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, page_alignment, 0, commit, allow_large, req_arena, &memid);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 623, __func__));
  ((!os_align) || _mi_is_aligned(((uint8_t *) page) + page_alignment, block_alignment)) ? ((void) 0) : (_mi_assert_fail("!os_align || _mi_is_aligned((uint8_t*)page + page_alignment, block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 624, __func__));
  const size_t page_noguard_size = alloc_size;
  if ((!memid.initially_zero) && memid.initially_committed)
  {
    ;
    _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
  }
  else
    if (memid.initially_committed)
  {
    ;
  }
  if (memid.initially_zero && memid.initially_committed)
  {
    if (!mi_mem_is_zero(page, page_noguard_size))
    {
      _mi_error_message(14, "internal error: page memory was not zero initialized.\n");
      memid.initially_zero = 0;
      _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
    }
  }
  (((3 + 2) * 32) >= mi_page_info_size()) ? ((void) 0) : (_mi_assert_fail("MI_PAGE_INFO_SIZE >= mi_page_info_size()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 654, __func__));
  size_t block_start;
  if (os_align)
  {
    block_start = 1UL << (13 + 3);
  }
  else
    if (_mi_is_power_of_two(block_size) && (block_size <= 1024UL))
  {
    block_start = _mi_align_up(mi_page_info_size(), block_size);
  }
  else
  {
    block_start = mi_page_info_size();
  }
  const size_t reserved = (os_align) ? (1) : ((page_noguard_size - block_start) / block_size);
  ((reserved > 0) && (reserved <= UINT16_MAX)) ? ((void) 0) : (_mi_assert_fail("reserved > 0 && reserved <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 679, __func__));
  size_t commit_size = 0;
  if (!memid.initially_committed)
  {
    commit_size = _mi_align_up(block_start + block_size, 1UL << (13 + 3));
    if (commit_size > page_noguard_size)
    {
      commit_size = page_noguard_size;
    }
    bool is_zero;
    if (__builtin_expect(!(!(!mi_arena_commit(mi_memid_arena(memid), page, commit_size, &is_zero, 0))), 0))
    {
      _mi_arenas_free(page, alloc_size, memid);
      return 0;
    }
    if ((!memid.initially_zero) && (!is_zero))
    {
      _mi_memzero_aligned(page, commit_size);
    }
  }
  page->reserved = (uint16_t) reserved;
  page->page_start = ((uint8_t *) page) + block_start;
  page->block_size = block_size;
  page->slice_committed = commit_size;
  page->memid = memid;
  page->free_is_zero = memid.initially_zero;
  mi_page_try_claim_ownership(page);
  if (__builtin_expect(!(!(!_mi_page_map_register(page))), 0))
  {
    _mi_arenas_free(page, alloc_size, memid);
    return 0;
  }
  __mi_stat_increase(&tld->stats.pages, 1);
  __mi_stat_increase(&tld->stats.page_bins[_mi_page_bin(page)], 1);
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 717, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 718, __func__));
  (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 719, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 720, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 721, __func__));
  return page;
}


----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
None
----------------------------
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


----------------------------
static mi_page_t *mi_arenas_page_try_find_abandoned(mi_subproc_t *subproc, size_t slice_count, size_t block_size, mi_arena_t *req_arena, mi_heaptag_t heaptag, size_t tseq)
{
  (void) slice_count;
  const size_t bin = _mi_bin(block_size);
  (bin < ((73U + 1) + 1)) ? ((void) 0) : (_mi_assert_fail("bin < MI_BIN_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 542, __func__));
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 545, __func__));
  if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) == 0)
  {
    return 0;
  }
  const bool allow_large = 1;
  const int any_numa = -1;
  const bool match_numa = 1;
  {
    helper_mi_arenas_page_try_find_abandoned_1(subproc, slice_count, block_size, req_arena, heaptag, tseq, bin, allow_large, any_numa, match_numa);
  }
  ;
  return 0;
}


----------------------------
static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_arenas_page_singleton_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t info_size = (os_align) ? (1UL << (13 + 3)) : (mi_page_info_size());
  const size_t slice_count = mi_slice_count_of_size(info_size + block_size);
  mi_page_t *page = mi_arenas_page_alloc_fresh(slice_count, block_size, block_alignment, req_arena, heap->numa_node, 1, tld);
  if (page == 0)
  {
    return 0;
  }
  (page->reserved == 1) ? ((void) 0) : (_mi_assert_fail("page->reserved == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 768, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
}


/*** DEPENDENCIES:
bool _mi_page_init(mi_heap_t *heap, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 673, __func__));
  mi_page_set_heap(page, heap);
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  (void) page_start;
  ;
  ((page_size / mi_page_block_size(page)) < (1L << 16)) ? ((void) 0) : (_mi_assert_fail("page_size / mi_page_block_size(page) < (1L<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 679, __func__));
  (page->reserved > 0) ? ((void) 0) : (_mi_assert_fail("page->reserved > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 680, __func__));
  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
  (page->capacity == 0) ? ((void) 0) : (_mi_assert_fail("page->capacity == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 692, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 693, __func__));
  (page->used == 0) ? ((void) 0) : (_mi_assert_fail("page->used == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 694, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 695, __func__));
  (page->xthread_free == 1) ? ((void) 0) : (_mi_assert_fail("page->xthread_free == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 696, __func__));
  (page->next == 0) ? ((void) 0) : (_mi_assert_fail("page->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 697, __func__));
  (page->prev == 0) ? ((void) 0) : (_mi_assert_fail("page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 698, __func__));
  (page->retire_expire == 0) ? ((void) 0) : (_mi_assert_fail("page->retire_expire == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 699, __func__));
  (!mi_page_has_interior_pointers(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_has_interior_pointers(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 700, __func__));
  (page->keys[0] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[0] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 702, __func__));
  (page->keys[1] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[1] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 703, __func__));
  ;
  if (!mi_page_extend_free(heap, page))
  {
    return 0;
  }
  (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 709, __func__));
  return 1;
}


----------------------------
None
----------------------------
static mi_page_t *mi_arenas_page_alloc_fresh(size_t slice_count, size_t block_size, size_t block_alignment, mi_arena_t *req_arena, int numa_node, bool commit, mi_tld_t *tld)
{
  const bool allow_large = 0 < 2;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t page_alignment = 1UL << (13 + 3);
  mi_memid_t memid = _mi_memid_none();
  mi_page_t *page = 0;
  unsigned int page_idx = 0;
  const size_t alloc_size = mi_size_of_slices(slice_count);
  if (((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (!os_align)) && (slice_count <= (1 << (6 + 3))))
  {
    page_idx = (mi_page_t *) mi_arenas_try_alloc(tld->subproc, slice_count, page_alignment, commit, allow_large, req_arena, tld->thread_seq, numa_node, &memid);
    if ((&page[page_idx]) != 0)
    {
      (mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 605, __func__));
      mi_bitmap_set(memid.mem.arena.arena->pages, memid.mem.arena.slice_index);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    if (os_align)
    {
      (slice_count >= (mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment))) ? ((void) 0) : (_mi_assert_fail("slice_count >= mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 614, __func__));
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, block_alignment, page_alignment, commit, allow_large, req_arena, &memid);
    }
    else
    {
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, page_alignment, 0, commit, allow_large, req_arena, &memid);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 623, __func__));
  ((!os_align) || _mi_is_aligned(((uint8_t *) page) + page_alignment, block_alignment)) ? ((void) 0) : (_mi_assert_fail("!os_align || _mi_is_aligned((uint8_t*)page + page_alignment, block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 624, __func__));
  const size_t page_noguard_size = alloc_size;
  if ((!memid.initially_zero) && memid.initially_committed)
  {
    ;
    _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
  }
  else
    if (memid.initially_committed)
  {
    ;
  }
  if (memid.initially_zero && memid.initially_committed)
  {
    if (!mi_mem_is_zero(page, page_noguard_size))
    {
      _mi_error_message(14, "internal error: page memory was not zero initialized.\n");
      memid.initially_zero = 0;
      _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
    }
  }
  (((3 + 2) * 32) >= mi_page_info_size()) ? ((void) 0) : (_mi_assert_fail("MI_PAGE_INFO_SIZE >= mi_page_info_size()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 654, __func__));
  size_t block_start;
  if (os_align)
  {
    block_start = 1UL << (13 + 3);
  }
  else
    if (_mi_is_power_of_two(block_size) && (block_size <= 1024UL))
  {
    block_start = _mi_align_up(mi_page_info_size(), block_size);
  }
  else
  {
    block_start = mi_page_info_size();
  }
  const size_t reserved = (os_align) ? (1) : ((page_noguard_size - block_start) / block_size);
  ((reserved > 0) && (reserved <= UINT16_MAX)) ? ((void) 0) : (_mi_assert_fail("reserved > 0 && reserved <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 679, __func__));
  size_t commit_size = 0;
  if (!memid.initially_committed)
  {
    commit_size = _mi_align_up(block_start + block_size, 1UL << (13 + 3));
    if (commit_size > page_noguard_size)
    {
      commit_size = page_noguard_size;
    }
    bool is_zero;
    if (__builtin_expect(!(!(!mi_arena_commit(mi_memid_arena(memid), page, commit_size, &is_zero, 0))), 0))
    {
      _mi_arenas_free(page, alloc_size, memid);
      return 0;
    }
    if ((!memid.initially_zero) && (!is_zero))
    {
      _mi_memzero_aligned(page, commit_size);
    }
  }
  page->reserved = (uint16_t) reserved;
  page->page_start = ((uint8_t *) page) + block_start;
  page->block_size = block_size;
  page->slice_committed = commit_size;
  page->memid = memid;
  page->free_is_zero = memid.initially_zero;
  mi_page_try_claim_ownership(page);
  if (__builtin_expect(!(!(!_mi_page_map_register(page))), 0))
  {
    _mi_arenas_free(page, alloc_size, memid);
    return 0;
  }
  __mi_stat_increase(&tld->stats.pages, 1);
  __mi_stat_increase(&tld->stats.page_bins[_mi_page_bin(page)], 1);
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 717, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 718, __func__));
  (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 719, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 720, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 721, __func__));
  return page;
}


----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
None
----------------------------
inline static size_t mi_page_info_size(void)
{
  return _mi_align_up(sizeof(mi_page_t), 16);
}


----------------------------
static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}


----------------------------
None
----------------------------
***/


mi_page_t *_mi_arenas_page_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_page_t *page;
  unsigned int page_idx = 0;
  if (__builtin_expect(!(!(block_alignment > (1UL << (13 + 3)))), 0))
  {
    (_mi_is_power_of_two(block_alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 781, __func__));
    page_idx = mi_arenas_page_singleton_alloc(heap, block_size, block_alignment);
  }
  else
    if (block_size <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8))
  {
    page_idx = mi_arenas_page_regular_alloc(heap, mi_slice_count_of_size(1 * (1UL << (13 + 3))), block_size);
  }
  else
    if (block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    page_idx = mi_arenas_page_regular_alloc(heap, mi_slice_count_of_size(8 * (1 * (1UL << (13 + 3)))), block_size);
  }
  else
  {
    page_idx = mi_arenas_page_singleton_alloc(heap, block_size, block_alignment);
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 799, __func__));
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 800, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 801, __func__));
  ((block_alignment <= (1UL << (13 + 3))) || _mi_is_aligned(mi_page_start(page), block_alignment)) ? ((void) 0) : (_mi_assert_fail("block_alignment <= MI_PAGE_MAX_OVERALLOC_ALIGN || _mi_is_aligned(mi_page_start(page), block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 802, __func__));
  return page;
}


/*** DEPENDENCIES:
None
----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}


----------------------------
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
static mi_page_t *mi_arenas_page_singleton_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t info_size = (os_align) ? (1UL << (13 + 3)) : (mi_page_info_size());
  const size_t slice_count = mi_slice_count_of_size(info_size + block_size);
  mi_page_t *page = mi_arenas_page_alloc_fresh(slice_count, block_size, block_alignment, req_arena, heap->numa_node, 1, tld);
  if (page == 0)
  {
    return 0;
  }
  (page->reserved == 1) ? ((void) 0) : (_mi_assert_fail("page->reserved == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 768, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
}


----------------------------
static mi_page_t *mi_arenas_page_regular_alloc(mi_heap_t *heap, size_t slice_count, size_t block_size)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  mi_page_t *page = mi_arenas_page_try_find_abandoned(tld->subproc, slice_count, block_size, req_arena, heap->tag, tld->thread_seq);
  unsigned int page_idx = 0;
  if ((&page[page_idx]) != 0)
  {
    return page;
  }
  const long commit_on_demand = mi_option_get(mi_option_page_commit_on_demand);
  const bool commit = ((slice_count <= mi_slice_count_of_size(1UL << (13 + 3))) || ((commit_on_demand == 2) && _mi_os_has_overcommit())) || (commit_on_demand == 0);
  page_idx = mi_arenas_page_alloc_fresh(slice_count, block_size, 1, req_arena, heap->numa_node, commit, tld);
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  ((page->memid.memkind != MI_MEM_ARENA) || (page->memid.mem.arena.slice_count == slice_count)) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind != MI_MEM_ARENA || page->memid.mem.arena.slice_count == slice_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 744, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
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


bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.mem.os.base = start;
  memid.mem.os.size = size;
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_pinned;
  return mi_manage_os_memory_ex2(_mi_subproc(), start, size, numa_node, exclusive, memid, 0, 0, arena_id);
}


/*** DEPENDENCIES:
static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
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


bool mi_manage_os_memory(void *start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node)
{
  return mi_manage_os_memory_ex(start, size, is_committed, is_large, is_zero, numa_node, 0, 0);
}


/*** DEPENDENCIES:
bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.mem.os.base = start;
  memid.mem.os.size = size;
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_pinned;
  return mi_manage_os_memory_ex2(_mi_subproc(), start, size, numa_node, exclusive, memid, 0, 0, arena_id);
}


----------------------------
***/


static size_t mi_arena_used_slices(mi_arena_t *arena)
{
  size_t idx;
  if (mi_bitmap_bsr(arena->pages, &idx))
  {
    mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, idx);
    const size_t page_slice_count = page->memid.mem.arena.slice_count;
    return idx + page_slice_count;
  }
  else
  {
    return mi_arena_info_slices(arena);
  }
}


/*** DEPENDENCIES:
static size_t mi_arena_info_slices(mi_arena_t *arena)
{
  return arena->info_slices;
}


----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
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


----------------------------
None
----------------------------
***/


static int mi_page_commit_usage(mi_page_t *page)
{
  const size_t committed_size = mi_page_committed(page);
  const size_t used_size = page->used * mi_page_block_size(page);
  return (int) ((used_size * 100) / committed_size);
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static size_t mi_page_committed(const mi_page_t *page)
{
  return (page->slice_committed == 0) ? (mi_page_size(page)) : (page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}


----------------------------
None
----------------------------
***/


// hint:  ['bit_set_count_ref is a mutable refrence to size_t', 'bit_of_page_ref is a mutable refrence to long', 'color_ref is a mutable refrence to mi_ansi_color_t', 'c_ref is a mutable refrence to char']
void helper_helper_mi_debug_show_page_bfield_1_1(size_t * const bit_set_count_ref, long * const bit_of_page_ref, mi_ansi_color_t * const color_ref, char * const c_ref, void * const start)
{
  size_t bit_set_count = *bit_set_count_ref;
  long bit_of_page = *bit_of_page_ref;
  mi_ansi_color_t color = *color_ref;
  char c = *c_ref;
  (bit_of_page <= 0) ? ((void) 0) : (_mi_assert_fail("bit_of_page <= 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1407, __func__));
  bit_set_count += 1;
  c = 'p';
  color = MI_GRAY;
  mi_page_t *page = (mi_page_t *) start;
  if (mi_page_is_singleton(page))
  {
    c = 's';
  }
  else
    if (mi_page_is_full(page))
  {
    c = 'f';
  }
  if (!mi_page_is_abandoned(page))
  {
    c = _mi_toupper(c);
  }
  int commit_usage = mi_page_commit_usage(page);
  if (commit_usage < 25)
  {
    color = MI_MAROON;
  }
  else
    if (commit_usage < 50)
  {
    color = MI_ORANGE;
  }
  else
    if (commit_usage < 75)
  {
    color = MI_TEAL;
  }
  else
    color = MI_DARKGREEN;
  bit_of_page = (long) page->memid.mem.arena.slice_count;
  *bit_set_count_ref = bit_set_count;
  *bit_of_page_ref = bit_of_page;
  *color_ref = color;
  *c_ref = c;
}


/*** DEPENDENCIES:
None
----------------------------
char _mi_toupper(char c)
{
  if ((c >= 'a') && (c <= 'z'))
  {
    return (c - 'a') + 'A';
  }
  else
    return c;
}


----------------------------
static int mi_page_commit_usage(mi_page_t *page)
{
  const size_t committed_size = mi_page_committed(page);
  const size_t used_size = page->used * mi_page_block_size(page);
  return (int) ((used_size * 100) / committed_size);
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
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


inline static bool mi_bitmap_is_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_setN(bitmap, idx, 1);
}


/*** DEPENDENCIES:
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
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


inline static bool mi_bbitmap_is_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(1, bbitmap, idx, n);
}


/*** DEPENDENCIES:
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
***/


// hint:  ['color_ref is a mutable refrence to mi_ansi_color_t', 'c_ref is a mutable refrence to char']
void helper_helper_mi_debug_show_page_bfield_1_2(mi_ansi_color_t * const color_ref, char * const c_ref, mi_arena_t * const arena, size_t slice_index, int bit, long bit_of_page, void * const start)
{
  mi_ansi_color_t color = *color_ref;
  char c = *c_ref;
  c = '?';
  if (bit_of_page > 0)
  {
    c = '-';
  }
  else
    if (_mi_meta_is_meta_page(start))
  {
    c = 'm';
    color = MI_GRAY;
  }
  else
    if ((slice_index + bit) < arena->info_slices)
  {
    c = 'i';
    color = MI_GRAY;
  }
  else
    if (mi_bbitmap_is_setN(arena->slices_free, slice_index + bit, 1))
  {
    if (mi_bitmap_is_set(arena->slices_purge, slice_index + bit))
    {
      c = '~';
      color = MI_ORANGE;
    }
    else
      if (mi_bitmap_is_setN(arena->slices_committed, slice_index + bit, 1))
    {
      c = '_';
      color = MI_GRAY;
    }
    else
    {
      c = '.';
      color = MI_GRAY;
    }
  }
  if ((bit == ((1 << (3 + 3)) - 1)) && (bit_of_page > 1))
  {
    c = '>';
  }
  *color_ref = color;
  *c_ref = c;
}


/*** DEPENDENCIES:
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


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
inline static bool mi_bbitmap_is_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(1, bbitmap, idx, n);
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
inline static bool mi_bitmap_is_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_setN(bitmap, idx, 1);
}


----------------------------
None
----------------------------
***/


static void mi_debug_color(char *buf, size_t *k, mi_ansi_color_t color)
{
  *k += _mi_snprintf(buf + (*k), 32, "\x1B[%dm", (int) color);
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
***/


// hint:  ['bit_set_count_ref is a mutable refrence to size_t', 'bit_of_page_ref is a mutable refrence to long', 'color_ref is a mutable refrence to mi_ansi_color_t', 'prev_color_ref is a mutable refrence to mi_ansi_color_t']
void helper_mi_debug_show_page_bfield_1(size_t * const bit_set_count_ref, long * const bit_of_page_ref, mi_ansi_color_t * const color_ref, mi_ansi_color_t * const prev_color_ref, mi_bfield_t field, char * const buf, size_t * const k, mi_arena_t * const arena, size_t slice_index, int bit)
{
  size_t bit_set_count = *bit_set_count_ref;
  long bit_of_page = *bit_of_page_ref;
  mi_ansi_color_t color = *color_ref;
  mi_ansi_color_t prev_color = *prev_color_ref;
  bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
  void *start = mi_arena_slice_start(arena, slice_index + bit);
  char c = ' ';
  if (is_set)
  {
    helper_helper_mi_debug_show_page_bfield_1_1(&bit_set_count, &bit_of_page, &color, &c, start);
  }
  else
  {
    helper_helper_mi_debug_show_page_bfield_1_2(&color, &c, arena, slice_index, bit, bit_of_page, start);
  }
  if (color != prev_color)
  {
    mi_debug_color(buf, k, color);
    prev_color = color;
  }
  buf[*k] = c;
  *k += 1;
  *bit_set_count_ref = bit_set_count;
  *bit_of_page_ref = bit_of_page;
  *color_ref = color;
  *prev_color_ref = prev_color;
}


/*** DEPENDENCIES:
static void mi_debug_color(char *buf, size_t *k, mi_ansi_color_t color)
{
  *k += _mi_snprintf(buf + (*k), 32, "\x1B[%dm", (int) color);
}


----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
void helper_helper_mi_debug_show_page_bfield_1_2(mi_ansi_color_t * const color_ref, char * const c_ref, mi_arena_t * const arena, size_t slice_index, int bit, long bit_of_page, void * const start)
{
  mi_ansi_color_t color = *color_ref;
  char c = *c_ref;
  c = '?';
  if (bit_of_page > 0)
  {
    c = '-';
  }
  else
    if (_mi_meta_is_meta_page(start))
  {
    c = 'm';
    color = MI_GRAY;
  }
  else
    if ((slice_index + bit) < arena->info_slices)
  {
    c = 'i';
    color = MI_GRAY;
  }
  else
    if (mi_bbitmap_is_setN(arena->slices_free, slice_index + bit, 1))
  {
    if (mi_bitmap_is_set(arena->slices_purge, slice_index + bit))
    {
      c = '~';
      color = MI_ORANGE;
    }
    else
      if (mi_bitmap_is_setN(arena->slices_committed, slice_index + bit, 1))
    {
      c = '_';
      color = MI_GRAY;
    }
    else
    {
      c = '.';
      color = MI_GRAY;
    }
  }
  if ((bit == ((1 << (3 + 3)) - 1)) && (bit_of_page > 1))
  {
    c = '>';
  }
  *color_ref = color;
  *c_ref = c;
}


----------------------------
void helper_helper_mi_debug_show_page_bfield_1_1(size_t * const bit_set_count_ref, long * const bit_of_page_ref, mi_ansi_color_t * const color_ref, char * const c_ref, void * const start)
{
  size_t bit_set_count = *bit_set_count_ref;
  long bit_of_page = *bit_of_page_ref;
  mi_ansi_color_t color = *color_ref;
  char c = *c_ref;
  (bit_of_page <= 0) ? ((void) 0) : (_mi_assert_fail("bit_of_page <= 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1407, __func__));
  bit_set_count += 1;
  c = 'p';
  color = MI_GRAY;
  mi_page_t *page = (mi_page_t *) start;
  if (mi_page_is_singleton(page))
  {
    c = 's';
  }
  else
    if (mi_page_is_full(page))
  {
    c = 'f';
  }
  if (!mi_page_is_abandoned(page))
  {
    c = _mi_toupper(c);
  }
  int commit_usage = mi_page_commit_usage(page);
  if (commit_usage < 25)
  {
    color = MI_MAROON;
  }
  else
    if (commit_usage < 50)
  {
    color = MI_ORANGE;
  }
  else
    if (commit_usage < 75)
  {
    color = MI_TEAL;
  }
  else
    color = MI_DARKGREEN;
  bit_of_page = (long) page->memid.mem.arena.slice_count;
  *bit_set_count_ref = bit_set_count;
  *bit_of_page_ref = bit_of_page;
  *color_ref = color;
  *c_ref = c;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


static size_t mi_debug_show_page_bfield(mi_bfield_t field, char *buf, size_t *k, mi_arena_t *arena, size_t slice_index, long *pbit_of_page, mi_ansi_color_t *pcolor_of_page)
{
  size_t bit_set_count = 0;
  long bit_of_page = *pbit_of_page;
  mi_ansi_color_t color = *pcolor_of_page;
  mi_ansi_color_t prev_color = MI_GRAY;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1, bit_of_page -= 1)
  {
    helper_mi_debug_show_page_bfield_1(&bit_set_count, &bit_of_page, &color, &prev_color, field, buf, k, arena, slice_index, bit);
  }

  mi_debug_color(buf, k, MI_GRAY);
  *pbit_of_page = bit_of_page;
  *pcolor_of_page = color;
  return bit_set_count;
}


/*** DEPENDENCIES:
static void mi_debug_color(char *buf, size_t *k, mi_ansi_color_t color)
{
  *k += _mi_snprintf(buf + (*k), 32, "\x1B[%dm", (int) color);
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
void helper_mi_debug_show_page_bfield_1(size_t * const bit_set_count_ref, long * const bit_of_page_ref, mi_ansi_color_t * const color_ref, mi_ansi_color_t * const prev_color_ref, mi_bfield_t field, char * const buf, size_t * const k, mi_arena_t * const arena, size_t slice_index, int bit)
{
  size_t bit_set_count = *bit_set_count_ref;
  long bit_of_page = *bit_of_page_ref;
  mi_ansi_color_t color = *color_ref;
  mi_ansi_color_t prev_color = *prev_color_ref;
  bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
  void *start = mi_arena_slice_start(arena, slice_index + bit);
  char c = ' ';
  if (is_set)
  {
    helper_helper_mi_debug_show_page_bfield_1_1(&bit_set_count, &bit_of_page, &color, &c, start);
  }
  else
  {
    helper_helper_mi_debug_show_page_bfield_1_2(&color, &c, arena, slice_index, bit, bit_of_page, start);
  }
  if (color != prev_color)
  {
    mi_debug_color(buf, k, color);
    prev_color = color;
  }
  buf[*k] = c;
  *k += 1;
  *bit_set_count_ref = bit_set_count;
  *bit_of_page_ref = bit_of_page;
  *color_ref = color;
  *prev_color_ref = prev_color;
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
None
----------------------------
***/


static size_t mi_debug_show_bfield(mi_bfield_t field, char *buf, size_t *k)
{
  unsigned int k_idx = 0;
  size_t bit_set_count = 0;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1)
  {
    bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
    if (is_set)
    {
      bit_set_count += 1;
    }
    buf[k[k_idx]] = (is_set) ? ('x') : ('.');
    k_idx += 1;
  }

  return bit_set_count;
}


/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


// hint:  ['bit_count_ref is a mutable refrence to size_t', 'bit_set_count_ref is a mutable refrence to size_t', 'k_ref is a mutable refrence to size_t']
void helper_helper_mi_debug_show_chunks_1_2(size_t * const bit_count_ref, size_t * const bit_set_count_ref, size_t * const k_ref, size_t slice_count, bool invert, mi_arena_t * const arena, const size_t fields_per_line, char buf[(5 * (1 << (6 + 3))) + 64], mi_bchunk_t * const chunk, long bit_of_page, mi_ansi_color_t color_of_page, size_t j)
{
  size_t bit_count = *bit_count_ref;
  size_t bit_set_count = *bit_set_count_ref;
  size_t k = *k_ref;
  if ((j > 0) && ((j % fields_per_line) == 0))
  {
    _mi_raw_message("  %s\n\x1B[37m", buf);
    _mi_memzero(buf, sizeof(buf));
    _mi_memset(buf, ' ', 5);
    k = 5;
  }
  if (bit_count < slice_count)
  {
    mi_bfield_t bfield = chunk->bfields[j];
    if (invert)
    {
      bfield = ~bfield;
    }
    size_t xcount = (arena != 0) ? (mi_debug_show_page_bfield(bfield, buf, &k, arena, bit_count, &bit_of_page, &color_of_page)) : (mi_debug_show_bfield(bfield, buf, &k));
    if (invert)
    {
      xcount = (1 << (3 + 3)) - xcount;
    }
    bit_set_count += xcount;
    buf[k] = ' ';
    k += 1;
  }
  else
  {
    _mi_memset(buf + k, 'o', 1 << (3 + 3));
    k += 1 << (3 + 3);
  }
  bit_count += 1 << (3 + 3);
  *bit_count_ref = bit_count;
  *bit_set_count_ref = bit_set_count;
  *k_ref = k;
}


/*** DEPENDENCIES:
void _mi_raw_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, 0, fmt, args);
  ;
}


----------------------------
inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}


----------------------------
static size_t mi_debug_show_bfield(mi_bfield_t field, char *buf, size_t *k)
{
  unsigned int k_idx = 0;
  size_t bit_set_count = 0;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1)
  {
    bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
    if (is_set)
    {
      bit_set_count += 1;
    }
    buf[k[k_idx]] = (is_set) ? ('x') : ('.');
    k_idx += 1;
  }

  return bit_set_count;
}


----------------------------
static size_t mi_debug_show_page_bfield(mi_bfield_t field, char *buf, size_t *k, mi_arena_t *arena, size_t slice_index, long *pbit_of_page, mi_ansi_color_t *pcolor_of_page)
{
  size_t bit_set_count = 0;
  long bit_of_page = *pbit_of_page;
  mi_ansi_color_t color = *pcolor_of_page;
  mi_ansi_color_t prev_color = MI_GRAY;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1, bit_of_page -= 1)
  {
    helper_mi_debug_show_page_bfield_1(&bit_set_count, &bit_of_page, &color, &prev_color, field, buf, k, arena, slice_index, bit);
  }

  mi_debug_color(buf, k, MI_GRAY);
  *pbit_of_page = bit_of_page;
  *pcolor_of_page = color;
  return bit_set_count;
}


----------------------------
typedef size_t mi_bfield_t
----------------------------
None
----------------------------
***/


// hint:  ['chunk_kind_ref is a mutable refrence to char']
void helper_helper_mi_debug_show_chunks_1_1(char * const chunk_kind_ref, mi_bchunkmap_t * const chunk_bins, size_t i)
{
  char chunk_kind = *chunk_kind_ref;
  switch (mi_bbitmap_debug_get_bin(chunk_bins, i))
  {
    case MI_CBIN_SMALL:
    {
      chunk_kind = 'S';
      break;
    }

    case MI_CBIN_MEDIUM:
    {
      chunk_kind = 'M';
      break;
    }

    case MI_CBIN_LARGE:
    {
      chunk_kind = 'L';
      break;
    }

    case MI_CBIN_OTHER:
    {
      chunk_kind = 'X';
      break;
    }

    default:
    {
      chunk_kind = ' ';
      break;
    }

  }

  *chunk_kind_ref = chunk_kind;
}


/*** DEPENDENCIES:
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


----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
***/


// hint:  ['bit_count_ref is a mutable refrence to size_t', 'bit_set_count_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_mi_debug_show_chunks_1(size_t * const bit_count_ref, size_t * const bit_set_count_ref, size_t * const i_ref, size_t slice_count, size_t chunk_count, mi_bchunk_t * const chunks, mi_bchunkmap_t * const chunk_bins, bool invert, mi_arena_t * const arena, const size_t fields_per_line, const size_t used_slice_count)
{
  size_t bit_count = *bit_count_ref;
  size_t bit_set_count = *bit_set_count_ref;
  size_t i = *i_ref;
  char buf[(5 * (1 << (6 + 3))) + 64];
  _mi_memzero(buf, sizeof(buf));
  if ((bit_count > used_slice_count) && ((i + 2) < chunk_count))
  {
    const size_t diff = (chunk_count - 1) - i;
    bit_count += diff * (1 << (6 + 3));
    _mi_raw_message("  |\n");
    i = chunk_count - 1;
  }
  size_t k = 0;
  mi_bchunk_t *chunk = &chunks[i];
  if (i < 10)
  {
    buf[k] = '0' + ((char) i);
    k += 1;
    buf[k] = ' ';
    k += 1;
    buf[k] = ' ';
    k += 1;
  }
  else
    if (i < 100)
  {
    buf[k] = '0' + ((char) (i / 10));
    k += 1;
    buf[k] = '0' + ((char) (i % 10));
    k += 1;
    buf[k] = ' ';
    k += 1;
  }
  else
    if (i < 1000)
  {
    buf[k] = '0' + ((char) (i / 100));
    k += 1;
    buf[k] = '0' + ((char) ((i % 100) / 10));
    k += 1;
    buf[k] = '0' + ((char) (i % 10));
    k += 1;
  }
  char chunk_kind = ' ';
  if (chunk_bins != 0)
  {
    helper_helper_mi_debug_show_chunks_1_1(&chunk_kind, chunk_bins, i);
  }
  buf[k] = chunk_kind;
  k += 1;
  buf[k] = ' ';
  k += 1;
  long bit_of_page = 0;
  mi_ansi_color_t color_of_page = MI_GRAY;
  for (size_t j = 0; j < ((1 << (6 + 3)) / (1 << (3 + 3))); j += 1)
  {
    helper_helper_mi_debug_show_chunks_1_2(&bit_count, &bit_set_count, &k, slice_count, invert, arena, fields_per_line, buf, chunk, bit_of_page, color_of_page, j);
  }

  _mi_raw_message("  %s\n\x1B[37m", buf);
  *bit_count_ref = bit_count;
  *bit_set_count_ref = bit_set_count;
  *i_ref = i;
}


/*** DEPENDENCIES:
void helper_helper_mi_debug_show_chunks_1_1(char * const chunk_kind_ref, mi_bchunkmap_t * const chunk_bins, size_t i)
{
  char chunk_kind = *chunk_kind_ref;
  switch (mi_bbitmap_debug_get_bin(chunk_bins, i))
  {
    case MI_CBIN_SMALL:
    {
      chunk_kind = 'S';
      break;
    }

    case MI_CBIN_MEDIUM:
    {
      chunk_kind = 'M';
      break;
    }

    case MI_CBIN_LARGE:
    {
      chunk_kind = 'L';
      break;
    }

    case MI_CBIN_OTHER:
    {
      chunk_kind = 'X';
      break;
    }

    default:
    {
      chunk_kind = ' ';
      break;
    }

  }

  *chunk_kind_ref = chunk_kind;
}


----------------------------
void _mi_raw_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, 0, fmt, args);
  ;
}


----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}


----------------------------
void helper_helper_mi_debug_show_chunks_1_2(size_t * const bit_count_ref, size_t * const bit_set_count_ref, size_t * const k_ref, size_t slice_count, bool invert, mi_arena_t * const arena, const size_t fields_per_line, char buf[(5 * (1 << (6 + 3))) + 64], mi_bchunk_t * const chunk, long bit_of_page, mi_ansi_color_t color_of_page, size_t j)
{
  size_t bit_count = *bit_count_ref;
  size_t bit_set_count = *bit_set_count_ref;
  size_t k = *k_ref;
  if ((j > 0) && ((j % fields_per_line) == 0))
  {
    _mi_raw_message("  %s\n\x1B[37m", buf);
    _mi_memzero(buf, sizeof(buf));
    _mi_memset(buf, ' ', 5);
    k = 5;
  }
  if (bit_count < slice_count)
  {
    mi_bfield_t bfield = chunk->bfields[j];
    if (invert)
    {
      bfield = ~bfield;
    }
    size_t xcount = (arena != 0) ? (mi_debug_show_page_bfield(bfield, buf, &k, arena, bit_count, &bit_of_page, &color_of_page)) : (mi_debug_show_bfield(bfield, buf, &k));
    if (invert)
    {
      xcount = (1 << (3 + 3)) - xcount;
    }
    bit_set_count += xcount;
    buf[k] = ' ';
    k += 1;
  }
  else
  {
    _mi_memset(buf + k, 'o', 1 << (3 + 3));
    k += 1 << (3 + 3);
  }
  bit_count += 1 << (3 + 3);
  *bit_count_ref = bit_count;
  *bit_set_count_ref = bit_set_count;
  *k_ref = k;
}


----------------------------
None
----------------------------
***/


static size_t mi_debug_show_chunks(const char *header1, const char *header2, const char *header3, size_t slice_count, size_t chunk_count, mi_bchunk_t *chunks, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  _mi_raw_message("\x1B[37m%s%s%s (use/commit: \x1B[31m0 - 25%%\x1B[33m - 50%%\x1B[36m - 75%%\x1B[32m - 100%%\x1B[0m)\n", header1, header2, header3);
  const size_t fields_per_line = (narrow) ? (2) : (4);
  const size_t used_slice_count = mi_arena_used_slices(arena);
  size_t bit_count = 0;
  size_t bit_set_count = 0;
  for (size_t i = 0; (i < chunk_count) && (bit_count < slice_count); i += 1)
  {
    helper_mi_debug_show_chunks_1(&bit_count, &bit_set_count, &i, slice_count, chunk_count, chunks, chunk_bins, invert, arena, fields_per_line, used_slice_count);
  }

  _mi_raw_message("\x1B[0m  total ('x'): %zu\n", bit_set_count);
  return bit_set_count;
}


/*** DEPENDENCIES:
void _mi_raw_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, 0, fmt, args);
  ;
}


----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
void helper_mi_debug_show_chunks_1(size_t * const bit_count_ref, size_t * const bit_set_count_ref, size_t * const i_ref, size_t slice_count, size_t chunk_count, mi_bchunk_t * const chunks, mi_bchunkmap_t * const chunk_bins, bool invert, mi_arena_t * const arena, const size_t fields_per_line, const size_t used_slice_count)
{
  size_t bit_count = *bit_count_ref;
  size_t bit_set_count = *bit_set_count_ref;
  size_t i = *i_ref;
  char buf[(5 * (1 << (6 + 3))) + 64];
  _mi_memzero(buf, sizeof(buf));
  if ((bit_count > used_slice_count) && ((i + 2) < chunk_count))
  {
    const size_t diff = (chunk_count - 1) - i;
    bit_count += diff * (1 << (6 + 3));
    _mi_raw_message("  |\n");
    i = chunk_count - 1;
  }
  size_t k = 0;
  mi_bchunk_t *chunk = &chunks[i];
  if (i < 10)
  {
    buf[k] = '0' + ((char) i);
    k += 1;
    buf[k] = ' ';
    k += 1;
    buf[k] = ' ';
    k += 1;
  }
  else
    if (i < 100)
  {
    buf[k] = '0' + ((char) (i / 10));
    k += 1;
    buf[k] = '0' + ((char) (i % 10));
    k += 1;
    buf[k] = ' ';
    k += 1;
  }
  else
    if (i < 1000)
  {
    buf[k] = '0' + ((char) (i / 100));
    k += 1;
    buf[k] = '0' + ((char) ((i % 100) / 10));
    k += 1;
    buf[k] = '0' + ((char) (i % 10));
    k += 1;
  }
  char chunk_kind = ' ';
  if (chunk_bins != 0)
  {
    helper_helper_mi_debug_show_chunks_1_1(&chunk_kind, chunk_bins, i);
  }
  buf[k] = chunk_kind;
  k += 1;
  buf[k] = ' ';
  k += 1;
  long bit_of_page = 0;
  mi_ansi_color_t color_of_page = MI_GRAY;
  for (size_t j = 0; j < ((1 << (6 + 3)) / (1 << (3 + 3))); j += 1)
  {
    helper_helper_mi_debug_show_chunks_1_2(&bit_count, &bit_set_count, &k, slice_count, invert, arena, fields_per_line, buf, chunk, bit_of_page, color_of_page, j);
  }

  _mi_raw_message("  %s\n\x1B[37m", buf);
  *bit_count_ref = bit_count;
  *bit_set_count_ref = bit_set_count;
  *i_ref = i;
}


----------------------------
static size_t mi_arena_used_slices(mi_arena_t *arena)
{
  size_t idx;
  if (mi_bitmap_bsr(arena->pages, &idx))
  {
    mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, idx);
    const size_t page_slice_count = page->memid.mem.arena.slice_count;
    return idx + page_slice_count;
  }
  else
  {
    return mi_arena_info_slices(arena);
  }
}


----------------------------
None
----------------------------
***/


static size_t mi_debug_show_bitmap_binned(const char *header1, const char *header2, const char *header3, size_t slice_count, mi_bitmap_t *bitmap, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  return mi_debug_show_chunks(header1, header2, header3, slice_count, mi_bitmap_chunk_count(bitmap), &bitmap->chunks[0], chunk_bins, invert, arena, narrow);
}


/*** DEPENDENCIES:
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}


----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
static size_t mi_debug_show_chunks(const char *header1, const char *header2, const char *header3, size_t slice_count, size_t chunk_count, mi_bchunk_t *chunks, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  _mi_raw_message("\x1B[37m%s%s%s (use/commit: \x1B[31m0 - 25%%\x1B[33m - 50%%\x1B[36m - 75%%\x1B[32m - 100%%\x1B[0m)\n", header1, header2, header3);
  const size_t fields_per_line = (narrow) ? (2) : (4);
  const size_t used_slice_count = mi_arena_used_slices(arena);
  size_t bit_count = 0;
  size_t bit_set_count = 0;
  for (size_t i = 0; (i < chunk_count) && (bit_count < slice_count); i += 1)
  {
    helper_mi_debug_show_chunks_1(&bit_count, &bit_set_count, &i, slice_count, chunk_count, chunks, chunk_bins, invert, arena, fields_per_line, used_slice_count);
  }

  _mi_raw_message("\x1B[0m  total ('x'): %zu\n", bit_set_count);
  return bit_set_count;
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


static void mi_debug_show_arenas_ex(bool show_pages, bool narrow)
{
  mi_subproc_t *subproc = _mi_subproc();
  size_t max_arenas = mi_arenas_get_count(subproc);
  size_t page_total = 0;
  for (size_t i = 0; i < max_arenas; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena == 0)
    {
      break;
    }
    (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1530, __func__));
    _mi_raw_message("arena %zu at %p: %zu slices (%zu MiB)%s, subproc: %p\n", i, arena, arena->slice_count, (size_t) (mi_size_of_slices(arena->slice_count) / (1024UL * 1024UL)), (arena->memid.is_pinned) ? (", pinned") : (""), arena->subproc);
    if (show_pages)
    {
      const char *header1 = "pages (p:page, f:full, s:singleton, P,F,S:not abandoned, i:arena-info, m:meta-data, ~:free-purgable, _:free-committed, .:free-reserved)";
      const char *header2 = (narrow) ? ("\n      ") : (" ");
      const char *header3 = "(chunk bin: S:small, M : medium, L : large, X : other)";
      page_total += mi_debug_show_bitmap_binned(header1, header2, header3, arena->slice_count, arena->pages, arena->slices_free->chunkmap_bins, 0, arena, narrow);
    }
  }

  if (show_pages)
  {
    _mi_raw_message("total pages in arenas: %zu\n", page_total);
  }
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_raw_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, 0, fmt, args);
  ;
}


----------------------------
static size_t mi_debug_show_bitmap_binned(const char *header1, const char *header2, const char *header3, size_t slice_count, mi_bitmap_t *bitmap, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  return mi_debug_show_chunks(header1, header2, header3, slice_count, mi_bitmap_chunk_count(bitmap), &bitmap->chunks[0], chunk_bins, invert, arena, narrow);
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
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


void mi_debug_show_arenas(void)
{
  mi_debug_show_arenas_ex(1, 0);
}


/*** DEPENDENCIES:
static void mi_debug_show_arenas_ex(bool show_pages, bool narrow)
{
  mi_subproc_t *subproc = _mi_subproc();
  size_t max_arenas = mi_arenas_get_count(subproc);
  size_t page_total = 0;
  for (size_t i = 0; i < max_arenas; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena == 0)
    {
      break;
    }
    (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1530, __func__));
    _mi_raw_message("arena %zu at %p: %zu slices (%zu MiB)%s, subproc: %p\n", i, arena, arena->slice_count, (size_t) (mi_size_of_slices(arena->slice_count) / (1024UL * 1024UL)), (arena->memid.is_pinned) ? (", pinned") : (""), arena->subproc);
    if (show_pages)
    {
      const char *header1 = "pages (p:page, f:full, s:singleton, P,F,S:not abandoned, i:arena-info, m:meta-data, ~:free-purgable, _:free-committed, .:free-reserved)";
      const char *header2 = (narrow) ? ("\n      ") : (" ");
      const char *header3 = "(chunk bin: S:small, M : medium, L : large, X : other)";
      page_total += mi_debug_show_bitmap_binned(header1, header2, header3, arena->slice_count, arena->pages, arena->slices_free->chunkmap_bins, 0, arena, narrow);
    }
  }

  if (show_pages)
  {
    _mi_raw_message("total pages in arenas: %zu\n", page_total);
  }
}


----------------------------
***/


void mi_arenas_print(void)
{
  mi_debug_show_arenas();
}


/*** DEPENDENCIES:
void mi_debug_show_arenas(void)
{
  mi_debug_show_arenas_ex(1, 0);
}


----------------------------
***/


static size_t mi_arena_size(mi_arena_t *arena)
{
  return mi_size_of_slices(arena->slice_count);
}


/*** DEPENDENCIES:
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
None
----------------------------
***/


static void mi_arenas_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1085, __func__));
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < arena_count; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena != 0)
    {
      atomic_store_explicit(&subproc->arenas[i], 0, memory_order_release);
      if (mi_memkind_is_os(arena->memid.memkind))
      {
        _mi_os_free_ex(mi_arena_start(arena), mi_arena_size(arena), 1, arena->memid, subproc);
      }
    }
  }

  size_t expected = arena_count;
  atomic_compare_exchange_strong_explicit(&subproc->arena_count, &expected, 0, memory_order_acq_rel, memory_order_acquire);
}


/*** DEPENDENCIES:
None
----------------------------
static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
static size_t mi_arena_size(mi_arena_t *arena)
{
  return mi_size_of_slices(arena->slice_count);
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
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}


----------------------------
None
----------------------------
***/


void _mi_arenas_unsafe_destroy_all(mi_subproc_t *subproc)
{
  mi_arenas_unsafe_destroy(subproc);
}


/*** DEPENDENCIES:
static void mi_arenas_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1085, __func__));
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < arena_count; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena != 0)
    {
      atomic_store_explicit(&subproc->arenas[i], 0, memory_order_release);
      if (mi_memkind_is_os(arena->memid.memkind))
      {
        _mi_os_free_ex(mi_arena_start(arena), mi_arena_size(arena), 1, arena->memid, subproc);
      }
    }
  }

  size_t expected = arena_count;
  atomic_compare_exchange_strong_explicit(&subproc->arena_count, &expected, 0, memory_order_acq_rel, memory_order_acquire);
}


----------------------------
None
----------------------------
***/


int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t *pages_reserved)
{
  (void) max_secs;
  _mi_warning_message("mi_reserve_huge_os_pages is deprecated: use mi_reserve_huge_os_pages_interleave/at instead\n");
  if (pages_reserved != 0)
  {
    *pages_reserved = 0;
  }
  int err = mi_reserve_huge_os_pages_interleave(pages, 0, (size_t) (max_secs * 1000.0));
  if ((err == 0) && (pages_reserved != 0))
  {
    *pages_reserved = pages;
  }
  return err;
}


/*** DEPENDENCIES:
int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs)
{
  if (pages == 0)
  {
    return 0;
  }
  int numa_count = ((numa_nodes > 0) && (numa_nodes <= 2147483647)) ? ((int) numa_nodes) : (_mi_os_numa_node_count());
  if (numa_count <= 0)
  {
    numa_count = 1;
  }
  const size_t pages_per = pages / numa_count;
  const size_t pages_mod = pages % numa_count;
  const size_t timeout_per = (timeout_msecs == 0) ? (0) : ((timeout_msecs / numa_count) + 50);
  for (int numa_node = 0; (numa_node < numa_count) && (pages > 0); numa_node += 1)
  {
    size_t node_pages = pages_per;
    if (((size_t) numa_node) < pages_mod)
    {
      node_pages += 1;
    }
    int err = mi_reserve_huge_os_pages_at(node_pages, numa_node, timeout_per);
    if (err)
    {
      return err;
    }
    if (pages < node_pages)
    {
      pages = 0;
    }
    else
    {
      pages -= node_pages;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


inline static bool mi_bitmap_is_clear(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_clearN(bitmap, idx, 1);
}


/*** DEPENDENCIES:
inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
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


inline static mi_chunkbin_t mi_chunkbin_dec(mi_chunkbin_t bbin)
{
  (bbin > MI_CBIN_NONE) ? ((void) 0) : (_mi_assert_fail("bbin > MI_CBIN_NONE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/bitmap.h", 239, __func__));
  return (mi_chunkbin_t) (((int) bbin) - 1);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


static bool mi_arena_page_register(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) arg;
  (void) slice_count;
  (slice_count == 1) ? ((void) 0) : (_mi_assert_fail("slice_count == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1889, __func__));
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1891, __func__));
  if (!_mi_page_map_register(page))
  {
    return 0;
  }
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1893, __func__));
  return 1;
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}


----------------------------
None
----------------------------
***/


static bool mi_arena_pages_reregister(mi_arena_t *arena)
{
  return _mi_bitmap_forall_set(arena->pages, &mi_arena_page_register, arena, 0);
}


/*** DEPENDENCIES:
static bool mi_arena_page_register(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) arg;
  (void) slice_count;
  (slice_count == 1) ? ((void) 0) : (_mi_assert_fail("slice_count == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1889, __func__));
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1891, __func__));
  if (!_mi_page_map_register(page))
  {
    return 0;
  }
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1893, __func__));
  return 1;
}


----------------------------
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


----------------------------
None
----------------------------
***/


bool mi_arena_contains(mi_arena_id_t arena_id, const void *p)
{
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  return (mi_arena_start(arena) <= ((const uint8_t *) p)) && ((mi_arena_start(arena) + mi_size_of_slices(arena->slice_count)) > ((const uint8_t *) p));
}


/*** DEPENDENCIES:
typedef void *mi_arena_id_t
----------------------------
static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
None
----------------------------
***/


bool _mi_arenas_contain(const void *p)
{
  mi_subproc_t *subproc = _mi_subproc();
  const size_t max_arena = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < max_arena; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if ((arena != 0) && mi_arena_contains(arena, p))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
bool mi_arena_contains(mi_arena_id_t arena_id, const void *p)
{
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  return (mi_arena_start(arena) <= ((const uint8_t *) p)) && ((mi_arena_start(arena) + mi_size_of_slices(arena->slice_count)) > ((const uint8_t *) p));
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
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


void *mi_arena_area(mi_arena_id_t arena_id, size_t *size)
{
  if (size != 0)
  {
    *size = 0;
  }
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  if (arena == 0)
  {
    return 0;
  }
  if (size != 0)
  {
    *size = mi_size_of_slices(arena->slice_count);
  }
  return mi_arena_start(arena);
}


/*** DEPENDENCIES:
typedef void *mi_arena_id_t
----------------------------
static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}


----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
None
----------------------------
***/


static bool abandoned_page_visit(mi_page_t *page, mi_abandoned_page_visit_info_t *vinfo)
{
  if (page->heap_tag != vinfo->heap_tag)
  {
    return 1;
  }
  mi_heap_area_t area;
  _mi_heap_area_init(&area, page);
  if (!vinfo->visitor(0, &area, 0, area.block_size, vinfo->arg))
  {
    return 0;
  }
  if (vinfo->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&area, page, vinfo->visitor, vinfo->arg);
  }
  else
  {
    return 1;
  }
}


/*** DEPENDENCIES:
void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page)
{
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  area->reserved = page->reserved * bsize;
  area->committed = page->capacity * bsize;
  area->blocks = mi_page_start(page);
  area->used = page->used;
  area->block_size = ubsize;
  area->full_block_size = bsize;
  area->heap_tag = page->heap_tag;
}


----------------------------
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t
----------------------------
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg)
{
  (area != 0) ? ((void) 0) : (_mi_assert_fail("area != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 614, __func__));
  if (area == 0)
  {
    return 1;
  }
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 616, __func__));
  if (page == 0)
  {
    return 1;
  }
  _mi_page_free_collect(page, 1);
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 620, __func__));
  if (page->used == 0)
  {
    return 1;
  }
  size_t psize;
  uint8_t * const pstart = mi_page_area(page, &psize);
  mi_heap_t * const heap = mi_page_heap(page);
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  if (page->capacity == 1)
  {
    ((page->used == 1) && (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("page->used == 1 && page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 631, __func__));
    return visitor(mi_page_heap(page), area, pstart, ubsize, arg);
  }
  (bsize <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("bsize <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 634, __func__));
  if (page->used == page->capacity)
  {
    uint8_t *block = pstart;
    unsigned int block_idx = 0;
    for (size_t i = 0; i < page->capacity; i += 1)
    {
      if (!visitor(heap, area, block, ubsize, arg))
      {
        return 0;
      }
      block_idx += bsize;
    }

    return 1;
  }
  uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)];
  const uintptr_t bmapsize = _mi_divide_up(page->capacity, (1 << 3) * 8);
  memset(free_map, 0, bmapsize * (sizeof(intptr_t)));
  if ((page->capacity % ((1 << 3) * 8)) != 0)
  {
    size_t shift = page->capacity % ((1 << 3) * 8);
    uintptr_t mask = UINTPTR_MAX << shift;
    free_map[bmapsize - 1] = mask;
  }
  uint64_t magic;
  size_t shift;
  mi_get_fast_divisor(bsize, &magic, &shift);
  size_t free_count = 0;
  for (mi_block_t *block = page->free; (&block[block_idx]) != 0; block_idx = mi_block_next(page, block_idx))
  {
    helper__mi_heap_area_visit_blocks_1(&free_count, psize, pstart, bsize, block, free_map, shift, magic, shift, block, block);
  }

  unsigned int block_idx = 0;
  (page->capacity == (free_count + page->used)) ? ((void) 0) : (_mi_assert_fail("page->capacity == (free_count + page->used)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 681, __func__));
  size_t used_count = 0;
  uint8_t *block = pstart;
  unsigned int block_idx = 0;
  for (size_t i = 0; i < bmapsize; i += 1)
  {
    helper__mi_heap_area_visit_blocks_2(&block_idx, &block_idx, &used_count, &block_idx, area, arg, heap, bsize, ubsize, block, i, free_map, block, block, i);
  }

  (page->used == used_count) ? ((void) 0) : (_mi_assert_fail("page->used == used_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 713, __func__));
  return 1;
}


----------------------------
typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t
----------------------------
None
----------------------------
***/


bool mi_manage_memory(void *start, size_t size, bool is_committed, bool is_zero, bool is_pinned, int numa_node, bool exclusive, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.mem.os.base = start;
  memid.mem.os.size = size;
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_pinned;
  return mi_manage_os_memory_ex2(_mi_subproc(), start, size, numa_node, exclusive, memid, commit_fun, commit_fun_arg, arena_id);
}


/*** DEPENDENCIES:
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg)
----------------------------
inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
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
static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
None
----------------------------
***/


static bool abandoned_page_visit_at(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) slice_count;
  mi_abandoned_page_visit_info_t *vinfo = (mi_abandoned_page_visit_info_t *) arg;
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1846, __func__));
  return abandoned_page_visit(page, vinfo);
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}


----------------------------
typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t
----------------------------
uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}


----------------------------
static bool abandoned_page_visit(mi_page_t *page, mi_abandoned_page_visit_info_t *vinfo)
{
  if (page->heap_tag != vinfo->heap_tag)
  {
    return 1;
  }
  mi_heap_area_t area;
  _mi_heap_area_init(&area, page);
  if (!vinfo->visitor(0, &area, 0, area.block_size, vinfo->arg))
  {
    return 0;
  }
  if (vinfo->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&area, page, vinfo->visitor, vinfo->arg);
  }
  else
  {
    return 1;
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['ok_ref is a mutable refrence to bool']
void helper_mi_abandoned_visit_blocks_1(bool * const ok_ref, mi_abandoned_page_visit_info_t visit_info, mi_subproc_t * const subproc)
{
  bool ok = *ok_ref;
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (0 % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (0 != 0)
    {
      arena_idx = 0;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1861, __func__));
        for (size_t bin = 0; ok && (bin < ((73U + 1) + 1)); bin += 1)
        {
          if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) > 0)
          {
            ok = _mi_bitmap_forall_set(arena->pages_abandoned[bin], &abandoned_page_visit_at, arena, &visit_info);
          }
        }

      }
    }
  }

  *ok_ref = ok;
}


/*** DEPENDENCIES:
None
----------------------------
static bool abandoned_page_visit_at(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) slice_count;
  mi_abandoned_page_visit_info_t *vinfo = (mi_abandoned_page_visit_info_t *) arg;
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1846, __func__));
  return abandoned_page_visit(page, vinfo);
}


----------------------------
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


----------------------------
typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t
----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
None
----------------------------
***/


bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg)
{
  mi_abandoned_page_visit_info_t visit_info = {heap_tag, visitor, arg, visit_blocks};
  (void) subproc_id;
  (void) heap_tag;
  (void) visit_blocks;
  (void) visitor;
  (void) arg;
  bool ok = 1;
  mi_subproc_t *subproc = _mi_subproc_from_id(subproc_id);
  {
    helper_mi_abandoned_visit_blocks_1(&ok, visit_info, subproc);
  }
  ;
  if (!ok)
  {
    return 0;
  }
  for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
  {
    for (mi_page_t *page = subproc->os_abandoned_pages; ok && ((&page[page_idx]) != 0); page_idx = page_idx->next)
    {
      ok = abandoned_page_visit(page, &visit_info);
    }

    unsigned int page_idx = 0;
  }

  return ok;
}


/*** DEPENDENCIES:
typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t
----------------------------
typedef void *mi_subproc_id_t
----------------------------
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&subproc_main) : ((mi_subproc_t *) subproc_id);
}


----------------------------
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
void helper_mi_abandoned_visit_blocks_1(bool * const ok_ref, mi_abandoned_page_visit_info_t visit_info, mi_subproc_t * const subproc)
{
  bool ok = *ok_ref;
  const size_t _arena_count = mi_arenas_get_count(subproc);
  const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
  size_t _start = (_arena_cycle <= 1) ? (0) : (0 % _arena_cycle);
  for (size_t _i = 0; _i < _arena_count; _i += 1)
  {
    mi_arena_t *arena;
    unsigned int arena_idx = 0;
    if (0 != 0)
    {
      arena_idx = 0;
      if (_i > 0)
      {
        break;
      }
    }
    else
    {
      size_t _idx;
      if (_i < _arena_cycle)
      {
        _idx = _i + _start;
        if (_idx >= _arena_cycle)
        {
          _idx -= _arena_cycle;
        }
      }
      else
      {
        _idx = _i;
      }
      arena_idx = mi_arena_from_index(subproc, _idx);
    }
    if ((&arena[arena_idx]) != 0)
    {
      {
        (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1861, __func__));
        for (size_t bin = 0; ok && (bin < ((73U + 1) + 1)); bin += 1)
        {
          if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) > 0)
          {
            ok = _mi_bitmap_forall_set(arena->pages_abandoned[bin], &abandoned_page_visit_at, arena, &visit_info);
          }
        }

      }
    }
  }

  *ok_ref = ok;
}


----------------------------
inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


----------------------------
static bool abandoned_page_visit(mi_page_t *page, mi_abandoned_page_visit_info_t *vinfo)
{
  if (page->heap_tag != vinfo->heap_tag)
  {
    return 1;
  }
  mi_heap_area_t area;
  _mi_heap_area_init(&area, page);
  if (!vinfo->visitor(0, &area, 0, area.block_size, vinfo->arg))
  {
    return 0;
  }
  if (vinfo->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&area, page, vinfo->visitor, vinfo->arg);
  }
  else
  {
    return 1;
  }
}


----------------------------
inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


----------------------------
None
----------------------------
***/


bool mi_arena_reload(void *start, size_t size, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((start == 0) || (size == 0))
  {
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  mi_memid_t memid = arena->memid;
  if (memid.memkind != MI_MEM_EXTERNAL)
  {
    _mi_warning_message("can only reload arena's from external memory (%p)\n", arena);
    return 0;
  }
  if (memid.mem.os.base != start)
  {
    _mi_warning_message("the reloaded arena base address differs from the external memory (arena: %p, external: %p)\n", arena, start);
    return 0;
  }
  if (memid.mem.os.size != size)
  {
    _mi_warning_message("the reloaded arena size differs from the external memory (arena size: %zu, external size: %zu)\n", arena->memid.mem.os.size, size);
    return 0;
  }
  if (!arena->is_exclusive)
  {
    _mi_warning_message("the reloaded arena is not exclusive\n");
    return 0;
  }
  arena->is_exclusive = 1;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  arena->subproc = _mi_subproc();
  if (!mi_arenas_add(arena->subproc, arena, arena_id))
  {
    return 0;
  }
  if (!mi_arena_pages_reregister(arena))
  {
    return 0;
  }
  for (size_t bin = 0; bin < ((73U + 1) + 1); bin += 1)
  {
    const size_t count = mi_bitmap_popcount(arena->pages_abandoned[bin]);
    if (count > 0)
    {
      atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_acq_rel);
    }
  }

  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
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


----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


----------------------------
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg)
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
typedef void *mi_arena_id_t
----------------------------
static bool mi_arena_pages_reregister(mi_arena_t *arena)
{
  return _mi_bitmap_forall_set(arena->pages, &mi_arena_page_register, arena, 0);
}


----------------------------
static bool mi_arenas_add(mi_subproc_t *subproc, mi_arena_t *arena, mi_arena_id_t *arena_id)
{
  (arena != 0) ? ((void) 0) : (_mi_assert_fail("arena != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1116, __func__));
  (arena->slice_count > 0) ? ((void) 0) : (_mi_assert_fail("arena->slice_count > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1117, __func__));
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  const size_t count = mi_arenas_get_count(subproc);
  size_t i;
  for (i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == 0)
    {
      mi_arena_t *expected = 0;
      if (atomic_compare_exchange_strong_explicit(&subproc->arenas[i], &expected, arena, memory_order_release, memory_order_relaxed))
      {
        if (arena_id != 0)
        {
          *arena_id = arena;
        }
        return 1;
      }
    }
  }

  i = atomic_fetch_add_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
  if (i >= 160)
  {
    atomic_fetch_sub_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
    arena->subproc = 0;
    return 0;
  }
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_count, 1);
  atomic_store_explicit(&subproc->arenas[i], arena, memory_order_release);
  if (arena_id != 0)
  {
    *arena_id = arena;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


bool mi_arena_unload(mi_arena_id_t arena_id, void **base, size_t *accessed_size, size_t *full_size)
{
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  if (arena == 0)
  {
    return 0;
  }
  else
    if (!arena->is_exclusive)
  {
    _mi_warning_message("cannot unload a non-exclusive arena (id %zu at %p)\n", arena_id, arena);
    return 0;
  }
  else
    if (arena->memid.memkind != MI_MEM_EXTERNAL)
  {
    _mi_warning_message("can only unload managed arena's for external memory (id %zu at %p)\n", arena_id, arena);
    return 0;
  }
  const size_t asize = mi_size_of_slices(mi_arena_used_slices(arena));
  if (base != 0)
  {
    *base = (void *) arena;
  }
  if (full_size != 0)
  {
    *full_size = arena->memid.mem.os.size;
  }
  if (accessed_size != 0)
  {
    *accessed_size = asize;
  }
  mi_subproc_t * const subproc = arena->subproc;
  for (size_t bin = 0; bin < ((73U + 1) + 1); bin += 1)
  {
    const size_t count = mi_bitmap_popcount(arena->pages_abandoned[bin]);
    if (count > 0)
    {
      atomic_fetch_sub_explicit(&subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_acq_rel);
    }
  }

  _mi_page_map_unregister_range(arena, asize);
  const size_t count = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == arena)
    {
      atomic_store_explicit(&subproc->arenas[i], 0, memory_order_release);
      if ((i + 1) == count)
      {
        size_t expected = count;
        atomic_compare_exchange_strong_explicit(&subproc->arena_count, &expected, count - 1, memory_order_acq_rel, memory_order_acquire);
      }
      break;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
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


----------------------------
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


----------------------------
inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}


----------------------------
size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}


----------------------------
mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}


----------------------------
static size_t mi_arena_used_slices(mi_arena_t *arena)
{
  size_t idx;
  if (mi_bitmap_bsr(arena->pages, &idx))
  {
    mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, idx);
    const size_t page_slice_count = page->memid.mem.arena.slice_count;
    return idx + page_slice_count;
  }
  else
  {
    return mi_arena_info_slices(arena);
  }
}


----------------------------
None
----------------------------
***/


