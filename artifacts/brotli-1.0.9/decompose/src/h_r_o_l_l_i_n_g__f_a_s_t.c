typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
/*** DEPENDENCIES:
***/


