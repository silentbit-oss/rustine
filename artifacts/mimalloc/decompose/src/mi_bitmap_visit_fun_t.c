typedef bool mi_bitmap_visit_fun_t(mi_bitmap_t *bitmap, size_t chunk_idx, size_t n, size_t *idx, void *arg1, void *arg2)
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


