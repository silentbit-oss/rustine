typedef block_state (*compress_func)(deflate_state *s, int flush)
/*** DEPENDENCIES:
typedef struct internal_state
{
  z_streamp strm;
  int status;
  Bytef *pending_buf;
  ulg pending_buf_size;
  Bytef *pending_out;
  ulg pending;
  int wrap;
  gz_headerp gzhead;
  ulg gzindex;
  Byte method;
  int last_flush;
  uInt w_size;
  uInt w_bits;
  uInt w_mask;
  Bytef *window;
  ulg window_size;
  Posf *prev;
  Posf *head;
  uInt ins_h;
  uInt hash_size;
  uInt hash_bits;
  uInt hash_mask;
  uInt hash_shift;
  long block_start;
  uInt match_length;
  IPos prev_match;
  int match_available;
  uInt strstart;
  uInt match_start;
  uInt lookahead;
  uInt prev_length;
  uInt max_chain_length;
  uInt max_lazy_match;
  int level;
  int strategy;
  uInt good_match;
  int nice_match;
  struct ct_data_s dyn_ltree[(2 * ((256 + 1) + 29)) + 1];
  struct ct_data_s dyn_dtree[(2 * 30) + 1];
  struct ct_data_s bl_tree[(2 * 19) + 1];
  struct tree_desc_s l_desc;
  struct tree_desc_s d_desc;
  struct tree_desc_s bl_desc;
  ush bl_count[15 + 1];
  int heap[(2 * ((256 + 1) + 29)) + 1];
  int heap_len;
  int heap_max;
  uch depth[(2 * ((256 + 1) + 29)) + 1];
  uchf *sym_buf;
  uInt lit_bufsize;
  uInt sym_next;
  uInt sym_end;
  ulg opt_len;
  ulg static_len;
  uInt matches;
  uInt insert;
  ush bi_buf;
  int bi_valid;
  ulg high_water;
} deflate_state
----------------------------
***/


