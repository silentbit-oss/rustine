typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t
/*** DEPENDENCIES:
typedef size_t mi_bfield_t
----------------------------
***/


