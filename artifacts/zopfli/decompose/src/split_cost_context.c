typedef struct SplitCostContext
{
  const ZopfliLZ77Store *lz77;
  size_t start;
  size_t end;
} SplitCostContext
/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
***/


