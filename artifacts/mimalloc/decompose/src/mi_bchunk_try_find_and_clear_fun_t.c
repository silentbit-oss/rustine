typedef bool mi_bchunk_try_find_and_clear_fun_t(mi_bchunk_t *chunk, size_t n, size_t *idx)
/*** DEPENDENCIES:
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
----------------------------
***/


