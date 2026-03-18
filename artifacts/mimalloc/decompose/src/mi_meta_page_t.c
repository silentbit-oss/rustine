typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
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
None
----------------------------
***/


