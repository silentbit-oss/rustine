typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
typedef mi_bchunk_t mi_bchunkmap_t
----------------------------
***/


