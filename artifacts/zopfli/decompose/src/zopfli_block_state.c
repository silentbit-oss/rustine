typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
***/


