static mi_segmap_part_t *mi_segment_map_index_of(const mi_segment_t *segment, bool create_on_demand, size_t *idx, size_t *bitidx)
{
  (_mi_ptr_segment(segment + 1) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(segment + 1) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 52, __func__));
  *idx = 0;
  *bitidx = 0;
  if (((uintptr_t) segment) >= ((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  const uintptr_t segindex = ((uintptr_t) segment) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  if (segindex >= ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1))
  {
    return 0;
  }
  mi_segmap_part_t *part = atomic_load_explicit(&mi_segment_map[segindex], memory_order_relaxed);
  unsigned int part_idx = 0;
  if (__builtin_expect(!(!((&part[part_idx]) == 0)), 0))
  {
    if (!create_on_demand)
    {
      return 0;
    }
    mi_memid_t memid;
    part_idx = (mi_segmap_part_t *) _mi_os_zalloc(sizeof(mi_segmap_part_t), &memid);
    if ((&part[part_idx]) == 0)
    {
      return 0;
    }
    part->memid = memid;
    mi_segmap_part_t *expected = 0;
    if (!atomic_compare_exchange_strong_explicit(&mi_segment_map[segindex], &expected, part, memory_order_release, memory_order_relaxed))
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), memid);
      part_idx = expected;
      if ((&part[part_idx]) == 0)
      {
        return 0;
      }
    }
  }
  ((&part[part_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("part != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 74, __func__));
  const uintptr_t offset = ((uintptr_t) segment) % ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  const uintptr_t bitofs = offset / (1UL << (9 + (13 + 3)));
  *idx = bitofs / ((1 << 3) * 8);
  *bitidx = bitofs % ((1 << 3) * 8);
  return part;
}


/*** DEPENDENCIES:
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
None
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
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
void *_mi_os_zalloc(size_t size, mi_memid_t *memid)
{
  void *p = _mi_os_alloc(size, memid);
  return mi_os_ensure_zero(p, size, memid);
}


----------------------------
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid);
}


----------------------------
static mi_segmap_part_t * _Atomic mi_segment_map[(((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1]
----------------------------
None
----------------------------
***/


static mi_segment_t *_mi_segment_of(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  mi_segment_t *segment = _mi_ptr_segment(p);
  size_t index;
  size_t bitidx;
  mi_segmap_part_t *part = mi_segment_map_index_of(segment, 0, &index, &bitidx);
  if (part == 0)
  {
    return 0;
  }
  const uintptr_t mask = atomic_load_explicit(&part->map[index], memory_order_relaxed);
  if (__builtin_expect(!(!((mask & (((uintptr_t) 1) << bitidx)) != 0)), 1))
  {
    bool cookie_ok = _mi_ptr_cookie(segment) == segment->cookie;
    (cookie_ok) ? ((void) 0) : (_mi_assert_fail("cookie_ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 119, __func__));
    (void) cookie_ok;
    return segment;
  }
  return 0;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
}


----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
None
----------------------------
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
static mi_segmap_part_t *mi_segment_map_index_of(const mi_segment_t *segment, bool create_on_demand, size_t *idx, size_t *bitidx)
{
  (_mi_ptr_segment(segment + 1) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(segment + 1) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 52, __func__));
  *idx = 0;
  *bitidx = 0;
  if (((uintptr_t) segment) >= ((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  const uintptr_t segindex = ((uintptr_t) segment) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  if (segindex >= ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1))
  {
    return 0;
  }
  mi_segmap_part_t *part = atomic_load_explicit(&mi_segment_map[segindex], memory_order_relaxed);
  unsigned int part_idx = 0;
  if (__builtin_expect(!(!((&part[part_idx]) == 0)), 0))
  {
    if (!create_on_demand)
    {
      return 0;
    }
    mi_memid_t memid;
    part_idx = (mi_segmap_part_t *) _mi_os_zalloc(sizeof(mi_segmap_part_t), &memid);
    if ((&part[part_idx]) == 0)
    {
      return 0;
    }
    part->memid = memid;
    mi_segmap_part_t *expected = 0;
    if (!atomic_compare_exchange_strong_explicit(&mi_segment_map[segindex], &expected, part, memory_order_release, memory_order_relaxed))
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), memid);
      part_idx = expected;
      if ((&part[part_idx]) == 0)
      {
        return 0;
      }
    }
  }
  ((&part[part_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("part != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 74, __func__));
  const uintptr_t offset = ((uintptr_t) segment) % ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  const uintptr_t bitofs = offset / (1UL << (9 + (13 + 3)));
  *idx = bitofs / ((1 << 3) * 8);
  *bitidx = bitofs % ((1 << 3) * 8);
  return part;
}


----------------------------
None
----------------------------
***/


static bool mi_is_valid_pointer(const void *p)
{
  return _mi_arena_contains(p) || (_mi_segment_of(p) != 0);
}


/*** DEPENDENCIES:
bool _mi_arena_contains(const void *p)
{
  const size_t max_arena = atomic_load_explicit(&mi_arena_count, memory_order_relaxed);
  for (size_t i = 0; i < max_arena; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&mi_arenas[i], memory_order_relaxed);
    if (((arena != 0) && (arena->start <= ((const uint8_t *) p))) && ((arena->start + mi_arena_block_size(arena->block_count)) > ((const uint8_t *) p)))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
static mi_segment_t *_mi_segment_of(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  mi_segment_t *segment = _mi_ptr_segment(p);
  size_t index;
  size_t bitidx;
  mi_segmap_part_t *part = mi_segment_map_index_of(segment, 0, &index, &bitidx);
  if (part == 0)
  {
    return 0;
  }
  const uintptr_t mask = atomic_load_explicit(&part->map[index], memory_order_relaxed);
  if (__builtin_expect(!(!((mask & (((uintptr_t) 1) << bitidx)) != 0)), 1))
  {
    bool cookie_ok = _mi_ptr_cookie(segment) == segment->cookie;
    (cookie_ok) ? ((void) 0) : (_mi_assert_fail("cookie_ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 119, __func__));
    (void) cookie_ok;
    return segment;
  }
  return 0;
}


----------------------------
***/


bool mi_is_in_heap_region(const void *p)
{
  return mi_is_valid_pointer(p);
}


/*** DEPENDENCIES:
static bool mi_is_valid_pointer(const void *p)
{
  return _mi_arena_contains(p) || (_mi_segment_of(p) != 0);
}


----------------------------
***/


void _mi_segment_map_allocated_at(const mi_segment_t *segment)
{
  if (segment->memid.memkind == MI_MEM_ARENA)
  {
    return;
  }
  size_t index;
  size_t bitidx;
  mi_segmap_part_t *part = mi_segment_map_index_of(segment, 1, &index, &bitidx);
  if (part == 0)
  {
    return;
  }
  uintptr_t mask = atomic_load_explicit(&part->map[index], memory_order_relaxed);
  uintptr_t newmask;
  do
  {
    newmask = mask | (((uintptr_t) 1) << bitidx);
  }
  while (!atomic_compare_exchange_weak_explicit(&part->map[index], &mask, newmask, memory_order_release, memory_order_relaxed));
}


/*** DEPENDENCIES:
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
static mi_segmap_part_t *mi_segment_map_index_of(const mi_segment_t *segment, bool create_on_demand, size_t *idx, size_t *bitidx)
{
  (_mi_ptr_segment(segment + 1) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(segment + 1) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 52, __func__));
  *idx = 0;
  *bitidx = 0;
  if (((uintptr_t) segment) >= ((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  const uintptr_t segindex = ((uintptr_t) segment) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  if (segindex >= ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1))
  {
    return 0;
  }
  mi_segmap_part_t *part = atomic_load_explicit(&mi_segment_map[segindex], memory_order_relaxed);
  unsigned int part_idx = 0;
  if (__builtin_expect(!(!((&part[part_idx]) == 0)), 0))
  {
    if (!create_on_demand)
    {
      return 0;
    }
    mi_memid_t memid;
    part_idx = (mi_segmap_part_t *) _mi_os_zalloc(sizeof(mi_segmap_part_t), &memid);
    if ((&part[part_idx]) == 0)
    {
      return 0;
    }
    part->memid = memid;
    mi_segmap_part_t *expected = 0;
    if (!atomic_compare_exchange_strong_explicit(&mi_segment_map[segindex], &expected, part, memory_order_release, memory_order_relaxed))
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), memid);
      part_idx = expected;
      if ((&part[part_idx]) == 0)
      {
        return 0;
      }
    }
  }
  ((&part[part_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("part != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 74, __func__));
  const uintptr_t offset = ((uintptr_t) segment) % ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  const uintptr_t bitofs = offset / (1UL << (9 + (13 + 3)));
  *idx = bitofs / ((1 << 3) * 8);
  *bitidx = bitofs % ((1 << 3) * 8);
  return part;
}


----------------------------
None
----------------------------
***/


void _mi_segment_map_freed_at(const mi_segment_t *segment)
{
  if (segment->memid.memkind == MI_MEM_ARENA)
  {
    return;
  }
  size_t index;
  size_t bitidx;
  mi_segmap_part_t *part = mi_segment_map_index_of(segment, 0, &index, &bitidx);
  if (part == 0)
  {
    return;
  }
  uintptr_t mask = atomic_load_explicit(&part->map[index], memory_order_relaxed);
  uintptr_t newmask;
  do
  {
    newmask = mask & (~(((uintptr_t) 1) << bitidx));
  }
  while (!atomic_compare_exchange_weak_explicit(&part->map[index], &mask, newmask, memory_order_release, memory_order_relaxed));
}


/*** DEPENDENCIES:
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
static mi_segmap_part_t *mi_segment_map_index_of(const mi_segment_t *segment, bool create_on_demand, size_t *idx, size_t *bitidx)
{
  (_mi_ptr_segment(segment + 1) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(segment + 1) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 52, __func__));
  *idx = 0;
  *bitidx = 0;
  if (((uintptr_t) segment) >= ((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  const uintptr_t segindex = ((uintptr_t) segment) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  if (segindex >= ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1))
  {
    return 0;
  }
  mi_segmap_part_t *part = atomic_load_explicit(&mi_segment_map[segindex], memory_order_relaxed);
  unsigned int part_idx = 0;
  if (__builtin_expect(!(!((&part[part_idx]) == 0)), 0))
  {
    if (!create_on_demand)
    {
      return 0;
    }
    mi_memid_t memid;
    part_idx = (mi_segmap_part_t *) _mi_os_zalloc(sizeof(mi_segmap_part_t), &memid);
    if ((&part[part_idx]) == 0)
    {
      return 0;
    }
    part->memid = memid;
    mi_segmap_part_t *expected = 0;
    if (!atomic_compare_exchange_strong_explicit(&mi_segment_map[segindex], &expected, part, memory_order_release, memory_order_relaxed))
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), memid);
      part_idx = expected;
      if ((&part[part_idx]) == 0)
      {
        return 0;
      }
    }
  }
  ((&part[part_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("part != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment-map.c", 74, __func__));
  const uintptr_t offset = ((uintptr_t) segment) % ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))));
  const uintptr_t bitofs = offset / (1UL << (9 + (13 + 3)));
  *idx = bitofs / ((1 << 3) * 8);
  *bitidx = bitofs % ((1 << 3) * 8);
  return part;
}


----------------------------
None
----------------------------
***/


void _mi_segment_map_unsafe_destroy(void)
{
  for (size_t i = 0; i < ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1); i += 1)
  {
    mi_segmap_part_t *part = atomic_exchange_explicit(&mi_segment_map[i], 0, memory_order_relaxed);
    if (part != 0)
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), part->memid);
    }
  }

}


/*** DEPENDENCIES:
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid);
}


----------------------------
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
static mi_segmap_part_t * _Atomic mi_segment_map[(((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1]
----------------------------
***/


