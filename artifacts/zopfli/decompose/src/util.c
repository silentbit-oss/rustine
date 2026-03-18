void ZopfliInitOptions(ZopfliOptions *options)
{
  options->verbose = 0;
  options->verbose_more = 0;
  options->numiterations = 15;
  options->blocksplitting = 1;
  options->blocksplittinglast = 0;
  options->blocksplittingmax = 15;
}


/*** DEPENDENCIES:
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


