struct opng_options
{
  int backup;
  int clobber;
  int debug;
  int fix;
  int force;
  int full;
  int preserve;
  int quiet;
  int simulate;
  int verbose;
  const char *out_name;
  const char *dir_name;
  const char *log_name;
  int interlace;
  int nb;
  int nc;
  int np;
  int nz;
  int optim_level;
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int window_bits;
  int snip;
  int strip_all;
}
/*** DEPENDENCIES:
typedef unsigned int opng_bitset_t
----------------------------
***/


