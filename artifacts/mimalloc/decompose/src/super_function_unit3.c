// element in merge of:  _mi_arenas_free,_mi_meta_free
void _mi_meta_free(void *p, size_t size, mi_memid_t memid)
{
  if (p == 0)
  {
    return;
  }
  if (memid.memkind == MI_MEM_META)
  {
    (_mi_divide_up(size, 1 << (16 - (6 + 3))) == memid.mem.meta.block_count) ? ((void) 0) : (_mi_assert_fail("_mi_divide_up(size, MI_META_BLOCK_SIZE) == memid.mem.meta.block_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 153, __func__));
    const size_t block_count = memid.mem.meta.block_count;
    const size_t block_idx = memid.mem.meta.block_index;
    mi_meta_page_t *mpage = (mi_meta_page_t *) memid.mem.meta.meta_page;
    (mi_meta_page_of_ptr(p, 0) == mpage) ? ((void) 0) : (_mi_assert_fail("mi_meta_page_of_ptr(p,NULL) == mpage", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 157, __func__));
    ((block_idx + block_count) <= ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("block_idx + block_count <= MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 158, __func__));
    (mi_bbitmap_is_clearN(&mpage->blocks_free, block_idx, block_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(&mpage->blocks_free, block_idx, block_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 159, __func__));
    _mi_memzero_aligned(mi_meta_block_start(mpage, block_idx), block_count * (1 << (16 - (6 + 3))));
    mi_bbitmap_setN(&mpage->blocks_free, block_idx, block_count);
  }
  else
  {
    _mi_arenas_free(p, size, memid);
  }
}


/*** DEPENDENCIES:
None
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
static void *mi_meta_block_start(mi_meta_page_t *mpage, size_t block_idx)
{
  (_mi_is_aligned(((uint8_t *) mpage) - _mi_os_secure_guard_page_size(), 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned((uint8_t*)mpage - _mi_os_secure_guard_page_size(), MI_META_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 62, __func__));
  (block_idx < ((1UL << (13 + 3)) / (1 << (16 - (6 + 3))))) ? ((void) 0) : (_mi_assert_fail("block_idx < MI_META_BLOCKS_PER_PAGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 63, __func__));
  void *p = (((uint8_t *) mpage) - _mi_os_secure_guard_page_size()) + (block_idx * (1 << (16 - (6 + 3))));
  (mpage == mi_meta_page_of_ptr(p, 0)) ? ((void) 0) : (_mi_assert_fail("mpage == mi_meta_page_of_ptr(p,NULL)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 65, __func__));
  return p;
}


----------------------------
None
----------------------------
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
inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
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
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_arenas_free,_mi_meta_free
void _mi_arenas_free(void *p, size_t size, mi_memid_t memid)
{
  if (p == 0)
  {
    return;
  }
  if (size == 0)
  {
    return;
  }
  ;
  if (mi_memkind_is_os(memid.memkind))
  {
    _mi_os_free(p, size, memid);
  }
  else
    if (memid.memkind == MI_MEM_ARENA)
  {
    helper__mi_arenas_free_1(p, size, memid);
  }
  else
    if (memid.memkind == MI_MEM_META)
  {
    _mi_meta_free(p, size, memid);
  }
  else
  {
    (mi_memid_needs_no_free(memid)) ? ((void) 0) : (_mi_assert_fail("mi_memid_needs_no_free(memid)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 1043, __func__));
  }
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid, 0);
}


----------------------------
None
----------------------------
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


----------------------------
inline static bool mi_memid_needs_no_free(mi_memid_t memid)
{
  return mi_memkind_needs_no_free(memid.memkind);
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


