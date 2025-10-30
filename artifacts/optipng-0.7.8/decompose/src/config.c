typedef struct config_s
{
  ush good_length;
  ush max_lazy;
  ush nice_length;
  ush max_chain;
  compress_func func;
} config
/*** DEPENDENCIES:
typedef unsigned short ush
----------------------------
typedef block_state (*compress_func)(deflate_state *s, int flush)
----------------------------
***/


