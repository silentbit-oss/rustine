static unsigned bi_reverse(unsigned code, int len)
{
  register unsigned res = 0;
  do
  {
    res |= code & 1;
    code >>= 1, res <<= 1;
  }
  while ((--len) > 0);
  return res >> 1;
}


/*** DEPENDENCIES:
***/


static void tr_static_init(void)
{
}


/*** DEPENDENCIES:
***/


static void bi_flush(deflate_state *s)
{
  if (s->bi_valid == 16)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = 0;
    s->bi_valid = 0;
  }
  else
    if (s->bi_valid >= 8)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
    s->bi_buf >>= 8;
    s->bi_valid -= 8;
  }
}


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


static void bi_windup(deflate_state *s)
{
  if (s->bi_valid > 8)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
  }
  else
    if (s->bi_valid > 0)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
  }
  s->bi_buf = 0;
  s->bi_valid = 0;
}


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


static void init_block(deflate_state *s)
{
  int n;
  for (n = 0; n < ((256 + 1) + 29); n += 1)
  {
    s->dyn_ltree[n].fc.freq = 0;
  }

  for (n = 0; n < 30; n += 1)
  {
    s->dyn_dtree[n].fc.freq = 0;
  }

  for (n = 0; n < 19; n += 1)
  {
    s->bl_tree[n].fc.freq = 0;
  }

  s->dyn_ltree[256].fc.freq = 1;
  s->opt_len = (s->static_len = 0L);
  s->sym_next = (s->matches = 0);
}


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


static int detect_data_type(deflate_state *s)
{
  unsigned long block_mask = 0xf3ffc07fUL;
  int n;
  for (n = 0; n <= 31; n += 1, block_mask >>= 1)
  {
    if ((block_mask & 1) && (s->dyn_ltree[n].fc.freq != 0))
    {
      return 0;
    }
  }

  if (((s->dyn_ltree[9].fc.freq != 0) || (s->dyn_ltree[10].fc.freq != 0)) || (s->dyn_ltree[13].fc.freq != 0))
  {
    return 1;
  }
  for (n = 32; n < 256; n += 1)
  {
    if (s->dyn_ltree[n].fc.freq != 0)
    {
      return 1;
    }
  }

  return 0;
}


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


void helper_send_all_trees_1(deflate_state * const s, int lcodes)
{
  int len = 5;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) lcodes) - 257;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (lcodes - 257)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_send_all_trees_2(deflate_state * const s, int dcodes)
{
  int len = 5;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) dcodes) - 1;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (dcodes - 1)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_send_all_trees_3(deflate_state * const s, int blcodes)
{
  int len = 4;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) blcodes) - 4;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (blcodes - 4)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper__tr_stored_block_1(deflate_state * const s, int last)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) (0 << 1)) + last;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ((0 << 1) + last)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper__tr_align_1(deflate_state * const s)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) 1) << 1;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (1 << 1)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_send_tree_1_1(deflate_state * const s, int curlen, int count)
{
  do
  {
    {
      int len = s->bl_tree[curlen].dl.len;
      if (s->bi_valid > (((int) 16) - len))
      {
        int val = (int) s->bl_tree[curlen].fc.code;
        s->bi_buf |= ((ush) val) << s->bi_valid;
        {
          {
            s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
          }
          ;
          {
            s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
          }
          ;
        }
        ;
        s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
        s->bi_valid += len - 16;
      }
      else
      {
        s->bi_buf |= ((ush) s->bl_tree[curlen].fc.code) << s->bi_valid;
        s->bi_valid += len;
      }
    }
    ;
  }
  while ((--count) != 0);
}


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


void helper_helper_helper_send_tree_1_2_1(deflate_state * const s)
{
  int len = s->bl_tree[17].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[17].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[17].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_helper_send_tree_1_2_2(deflate_state * const s, int count)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 3;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 3)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_helper_send_tree_1_3_1(deflate_state * const s)
{
  int len = s->bl_tree[18].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[18].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[18].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_helper_send_tree_1_3_2(deflate_state * const s, int count)
{
  int len = 7;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 11;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 11)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_helper_send_tree_1_4_1(deflate_state * const s)
{
  int len = s->bl_tree[16].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[16].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[16].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


void helper_helper_helper_send_tree_1_4_2(deflate_state * const s, int count)
{
  int len = 2;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 3;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 3)) << s->bi_valid;
    s->bi_valid += len;
  }
}


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


// hint:  ['count_ref is a mutable refrence to int']
void helper_helper_helper_send_tree_1_4_3(int * const count_ref, deflate_state * const s, int curlen)
{
  int count = *count_ref;
  {
    int len = s->bl_tree[curlen].dl.len;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) s->bl_tree[curlen].fc.code;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) s->bl_tree[curlen].fc.code) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  count -= 1;
  *count_ref = count;
}


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


void _tr_flush_bits(deflate_state *s)
{
  bi_flush(s);
}


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
static void bi_flush(deflate_state *s)
{
  if (s->bi_valid == 16)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = 0;
    s->bi_valid = 0;
  }
  else
    if (s->bi_valid >= 8)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
    s->bi_buf >>= 8;
    s->bi_valid -= 8;
  }
}


----------------------------
***/


static void pqdownheap(deflate_state *s, ct_data *tree, int k)
{
  int v = s->heap[k];
  int j = k << 1;
  while (j <= s->heap_len)
  {
    if ((j < s->heap_len) && ((tree[s->heap[j + 1]].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[s->heap[j + 1]].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[s->heap[j + 1]] <= s->depth[s->heap[j]]))))
    {
      j += 1;
    }
    if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[v].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[v] <= s->depth[s->heap[j]])))
    {
      break;
    }
    s->heap[k] = s->heap[j];
    k = j;
    j <<= 1;
  }

  s->heap[k] = v;
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static void scan_tree(deflate_state *s, ct_data *tree, int max_code)
{
  int n;
  int prevlen = -1;
  int curlen;
  int nextlen = tree[0].dl.len;
  int count = 0;
  int max_count = 7;
  int min_count = 4;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  tree[max_code + 1].dl.len = (ush) 0xffff;
  for (n = 0; n <= max_code; n += 1)
  {
    curlen = nextlen;
    nextlen = tree[n + 1].dl.len;
    if (((++count) < max_count) && (curlen == nextlen))
    {
      continue;
    }
    else
      if (count < min_count)
    {
      s->bl_tree[curlen].fc.freq += count;
    }
    else
      if (curlen != 0)
    {
      if (curlen != prevlen)
      {
        s->bl_tree[curlen].fc.freq += 1;
      }
      s->bl_tree[16].fc.freq += 1;
    }
    else
      if (count <= 10)
    {
      s->bl_tree[17].fc.freq += 1;
    }
    else
    {
      s->bl_tree[18].fc.freq += 1;
    }
    count = 0;
    prevlen = curlen;
    if (nextlen == 0)
    {
      max_count = 138, min_count = 3;
    }
    else
      if (curlen == nextlen)
    {
      max_count = 6, min_count = 3;
    }
    else
    {
      max_count = 7, min_count = 4;
    }
  }

}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


// hint:  ['h_ref is a mutable refrence to int', 'n_ref is a mutable refrence to int', 'm_ref is a mutable refrence to int']
void helper_gen_bitlen_1(int * const h_ref, int * const n_ref, int * const m_ref, deflate_state * const s, ct_data * const tree, int max_code, int bits)
{
  int h = *h_ref;
  int n = *n_ref;
  int m = *m_ref;
  n = s->bl_count[bits];
  while (n != 0)
  {
    h -= 1;
    m = s->heap[h];
    if (m > max_code)
    {
      continue;
    }
    if (((unsigned) tree[m].dl.len) != ((unsigned) bits))
    {
      ;
      s->opt_len += (((ulg) bits) - tree[m].dl.len) * tree[m].fc.freq;
      tree[m].dl.len = (ush) bits;
    }
    n -= 1;
  }

  *h_ref = h;
  *n_ref = n;
  *m_ref = m;
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


void helper_send_all_trees_4(deflate_state * const s, int rank)
{
  ;
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) s->bl_tree[bl_order[rank]].dl.len;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) s->bl_tree[bl_order[rank]].dl.len) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
}


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
static const uch bl_order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15}
----------------------------
***/


void helper__tr_align_2(deflate_state * const s)
{
  int len = static_ltree[256].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) static_ltree[256].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) static_ltree[256].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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
static const ct_data static_ltree[((256 + 1) + 29) + 2] = {{{12}, {8}}, {{140}, {8}}, {{76}, {8}}, {{204}, {8}}, {{44}, {8}}, {{172}, {8}}, {{108}, {8}}, {{236}, {8}}, {{28}, {8}}, {{156}, {8}}, {{92}, {8}}, {{220}, {8}}, {{60}, {8}}, {{188}, {8}}, {{124}, {8}}, {{252}, {8}}, {{2}, {8}}, {{130}, {8}}, {{66}, {8}}, {{194}, {8}}, {{34}, {8}}, {{162}, {8}}, {{98}, {8}}, {{226}, {8}}, {{18}, {8}}, {{146}, {8}}, {{82}, {8}}, {{210}, {8}}, {{50}, {8}}, {{178}, {8}}, {{114}, {8}}, {{242}, {8}}, {{10}, {8}}, {{138}, {8}}, {{74}, {8}}, {{202}, {8}}, {{42}, {8}}, {{170}, {8}}, {{106}, {8}}, {{234}, {8}}, {{26}, {8}}, {{154}, {8}}, {{90}, {8}}, {{218}, {8}}, {{58}, {8}}, {{186}, {8}}, {{122}, {8}}, {{250}, {8}}, {{6}, {8}}, {{134}, {8}}, {{70}, {8}}, {{198}, {8}}, {{38}, {8}}, {{166}, {8}}, {{102}, {8}}, {{230}, {8}}, {{22}, {8}}, {{150}, {8}}, {{86}, {8}}, {{214}, {8}}, {{54}, {8}}, {{182}, {8}}, {{118}, {8}}, {{246}, {8}}, {{14}, {8}}, {{142}, {8}}, {{78}, {8}}, {{206}, {8}}, {{46}, {8}}, {{174}, {8}}, {{110}, {8}}, {{238}, {8}}, {{30}, {8}}, {{158}, {8}}, {{94}, {8}}, {{222}, {8}}, {{62}, {8}}, {{190}, {8}}, {{126}, {8}}, {{254}, {8}}, {{1}, {8}}, {{129}, {8}}, {{65}, {8}}, {{193}, {8}}, {{33}, {8}}, {{161}, {8}}, {{97}, {8}}, {{225}, {8}}, {{17}, {8}}, {{145}, {8}}, {{81}, {8}}, {{209}, {8}}, {{49}, {8}}, {{177}, {8}}, {{113}, {8}}, {{241}, {8}}, {{9}, {8}}, {{137}, {8}}, {{73}, {8}}, {{201}, {8}}, {{41}, {8}}, {{169}, {8}}, {{105}, {8}}, {{233}, {8}}, {{25}, {8}}, {{153}, {8}}, {{89}, {8}}, {{217}, {8}}, {{57}, {8}}, {{185}, {8}}, {{121}, {8}}, {{249}, {8}}, {{5}, {8}}, {{133}, {8}}, {{69}, {8}}, {{197}, {8}}, {{37}, {8}}, {{165}, {8}}, {{101}, {8}}, {{229}, {8}}, {{21}, {8}}, {{149}, {8}}, {{85}, {8}}, {{213}, {8}}, {{53}, {8}}, {{181}, {8}}, {{117}, {8}}, {{245}, {8}}, {{13}, {8}}, {{141}, {8}}, {{77}, {8}}, {{205}, {8}}, {{45}, {8}}, {{173}, {8}}, {{109}, {8}}, {{237}, {8}}, {{29}, {8}}, {{157}, {8}}, {{93}, {8}}, {{221}, {8}}, {{61}, {8}}, {{189}, {8}}, {{125}, {8}}, {{253}, {8}}, {{19}, {9}}, {{275}, {9}}, {{147}, {9}}, {{403}, {9}}, {{83}, {9}}, {{339}, {9}}, {{211}, {9}}, {{467}, {9}}, {{51}, {9}}, {{307}, {9}}, {{179}, {9}}, {{435}, {9}}, {{115}, {9}}, {{371}, {9}}, {{243}, {9}}, {{499}, {9}}, {{11}, {9}}, {{267}, {9}}, {{139}, {9}}, {{395}, {9}}, {{75}, {9}}, {{331}, {9}}, {{203}, {9}}, {{459}, {9}}, {{43}, {9}}, {{299}, {9}}, {{171}, {9}}, {{427}, {9}}, {{107}, {9}}, {{363}, {9}}, {{235}, {9}}, {{491}, {9}}, {{27}, {9}}, {{283}, {9}}, {{155}, {9}}, {{411}, {9}}, {{91}, {9}}, {{347}, {9}}, {{219}, {9}}, {{475}, {9}}, {{59}, {9}}, {{315}, {9}}, {{187}, {9}}, {{443}, {9}}, {{123}, {9}}, {{379}, {9}}, {{251}, {9}}, {{507}, {9}}, {{7}, {9}}, {{263}, {9}}, {{135}, {9}}, {{391}, {9}}, {{71}, {9}}, {{327}, {9}}, {{199}, {9}}, {{455}, {9}}, {{39}, {9}}, {{295}, {9}}, {{167}, {9}}, {{423}, {9}}, {{103}, {9}}, {{359}, {9}}, {{231}, {9}}, {{487}, {9}}, {{23}, {9}}, {{279}, {9}}, {{151}, {9}}, {{407}, {9}}, {{87}, {9}}, {{343}, {9}}, {{215}, {9}}, {{471}, {9}}, {{55}, {9}}, {{311}, {9}}, {{183}, {9}}, {{439}, {9}}, {{119}, {9}}, {{375}, {9}}, {{247}, {9}}, {{503}, {9}}, {{15}, {9}}, {{271}, {9}}, {{143}, {9}}, {{399}, {9}}, {{79}, {9}}, {{335}, {9}}, {{207}, {9}}, {{463}, {9}}, {{47}, {9}}, {{303}, {9}}, {{175}, {9}}, {{431}, {9}}, {{111}, {9}}, {{367}, {9}}, {{239}, {9}}, {{495}, {9}}, {{31}, {9}}, {{287}, {9}}, {{159}, {9}}, {{415}, {9}}, {{95}, {9}}, {{351}, {9}}, {{223}, {9}}, {{479}, {9}}, {{63}, {9}}, {{319}, {9}}, {{191}, {9}}, {{447}, {9}}, {{127}, {9}}, {{383}, {9}}, {{255}, {9}}, {{511}, {9}}, {{0}, {7}}, {{64}, {7}}, {{32}, {7}}, {{96}, {7}}, {{16}, {7}}, {{80}, {7}}, {{48}, {7}}, {{112}, {7}}, {{8}, {7}}, {{72}, {7}}, {{40}, {7}}, {{104}, {7}}, {{24}, {7}}, {{88}, {7}}, {{56}, {7}}, {{120}, {7}}, {{4}, {7}}, {{68}, {7}}, {{36}, {7}}, {{100}, {7}}, {{20}, {7}}, {{84}, {7}}, {{52}, {7}}, {{116}, {7}}, {{3}, {8}}, {{131}, {8}}, {{67}, {8}}, {{195}, {8}}, {{35}, {8}}, {{163}, {8}}, {{99}, {8}}, {{227}, {8}}}
----------------------------
***/


void helper_compress_block_1(deflate_state * const s, const ct_data * const ltree)
{
  int len = ltree[256].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) ltree[256].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ltree[256].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


void helper_helper_helper_compress_block_2_1_1(deflate_state * const s, const ct_data * const ltree, int lc)
{
  {
    int len = ltree[lc].dl.len;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) ltree[lc].fc.code;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ltree[lc].fc.code) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  ;
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


void helper_helper_helper_helper_compress_block_2_1_2_1(deflate_state * const s, const ct_data * const ltree, unsigned code)
{
  int len = ltree[(code + 256) + 1].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) ltree[(code + 256) + 1].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ltree[(code + 256) + 1].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


void helper_helper_helper_helper_compress_block_2_1_2_2(deflate_state * const s, const ct_data * const dtree, unsigned code)
{
  int len = dtree[code].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) dtree[code].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) dtree[code].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


// hint:  ['lc_ref is a mutable refrence to int']
void helper_helper_helper_helper_compress_block_2_1_2_3(int * const lc_ref, deflate_state * const s, unsigned code, int extra)
{
  int lc = *lc_ref;
  lc -= base_length[code];
  {
    int len = extra;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) lc;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) lc) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  *lc_ref = lc;
}


/*** DEPENDENCIES:
static const int base_length[29] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 0}
----------------------------
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


// hint:  ['dist_ref is a mutable refrence to unsigned']
void helper_helper_helper_helper_compress_block_2_1_2_4(unsigned * const dist_ref, deflate_state * const s, unsigned code, int extra)
{
  unsigned dist = *dist_ref;
  dist -= (unsigned) base_dist[code];
  {
    int len = extra;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) dist;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) dist) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  *dist_ref = dist;
}


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
static const int base_dist[30] = {0, 1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 256, 384, 512, 768, 1024, 1536, 2048, 3072, 4096, 6144, 8192, 12288, 16384, 24576}
----------------------------
***/


void _tr_init(deflate_state *s)
{
  tr_static_init();
  s->l_desc.dyn_tree = s->dyn_ltree;
  s->l_desc.stat_desc = &static_l_desc;
  s->d_desc.dyn_tree = s->dyn_dtree;
  s->d_desc.stat_desc = &static_d_desc;
  s->bl_desc.dyn_tree = s->bl_tree;
  s->bl_desc.stat_desc = &static_bl_desc;
  s->bi_buf = 0;
  s->bi_valid = 0;
  init_block(s);
}


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
static const static_tree_desc static_bl_desc = {(const ct_data *) 0, extra_blbits, 0, 19, 7}
----------------------------
static void init_block(deflate_state *s)
{
  int n;
  for (n = 0; n < ((256 + 1) + 29); n += 1)
  {
    s->dyn_ltree[n].fc.freq = 0;
  }

  for (n = 0; n < 30; n += 1)
  {
    s->dyn_dtree[n].fc.freq = 0;
  }

  for (n = 0; n < 19; n += 1)
  {
    s->bl_tree[n].fc.freq = 0;
  }

  s->dyn_ltree[256].fc.freq = 1;
  s->opt_len = (s->static_len = 0L);
  s->sym_next = (s->matches = 0);
}


----------------------------
static const static_tree_desc static_l_desc = {static_ltree, extra_lbits, 256 + 1, (256 + 1) + 29, 15}
----------------------------
static const static_tree_desc static_d_desc = {static_dtree, extra_dbits, 0, 30, 15}
----------------------------
static void tr_static_init(void)
{
}


----------------------------
***/


void _tr_stored_block(deflate_state *s, charf *buf, ulg stored_len, int last)
{
  {
    helper__tr_stored_block_1(s, last);
  }
  ;
  bi_windup(s);
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) stored_len) & 0xff));
    }
    ;
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) ((ush) stored_len)) >> 8));
    }
    ;
  }
  ;
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) (~stored_len)) & 0xff));
    }
    ;
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) ((ush) (~stored_len))) >> 8));
    }
    ;
  }
  ;
  if (stored_len)
  {
    memcpy(s->pending_buf + s->pending, (Bytef *) buf, stored_len);
  }
  s->pending += stored_len;
}


/*** DEPENDENCIES:
static void bi_windup(deflate_state *s)
{
  if (s->bi_valid > 8)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
  }
  else
    if (s->bi_valid > 0)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
  }
  s->bi_buf = 0;
  s->bi_valid = 0;
}


----------------------------
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
typedef unsigned long ulg
----------------------------
typedef char charf
----------------------------
void helper__tr_stored_block_1(deflate_state * const s, int last)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) (0 << 1)) + last;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ((0 << 1) + last)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


void _tr_align(deflate_state *s)
{
  {
    helper__tr_align_1(s);
  }
  ;
  {
    helper__tr_align_2(s);
  }
  ;
  bi_flush(s);
}


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
void helper__tr_align_2(deflate_state * const s)
{
  int len = static_ltree[256].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) static_ltree[256].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) static_ltree[256].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
static void bi_flush(deflate_state *s)
{
  if (s->bi_valid == 16)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = 0;
    s->bi_valid = 0;
  }
  else
    if (s->bi_valid >= 8)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
    s->bi_buf >>= 8;
    s->bi_valid -= 8;
  }
}


----------------------------
void helper__tr_align_1(deflate_state * const s)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) 1) << 1;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (1 << 1)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


static void gen_codes(ct_data *tree, int max_code, ushf *bl_count)
{
  ush next_code[15 + 1];
  unsigned code = 0;
  int bits;
  int n;
  for (bits = 1; bits <= 15; bits += 1)
  {
    code = (code + bl_count[bits - 1]) << 1;
    next_code[bits] = (ush) code;
  }

  ;
  ;
  for (n = 0; n <= max_code; n += 1)
  {
    int len = tree[n].dl.len;
    if (len == 0)
    {
      continue;
    }
    tree[n].fc.code = (ush) bi_reverse(next_code[len]++, len);
    ;
  }

}


/*** DEPENDENCIES:
typedef ush ushf
----------------------------
typedef unsigned short ush
----------------------------
static unsigned bi_reverse(unsigned code, int len)
{
  register unsigned res = 0;
  do
  {
    res |= code & 1;
    code >>= 1, res <<= 1;
  }
  while ((--len) > 0);
  return res >> 1;
}


----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to int', 'm_ref is a mutable refrence to int', 'node_ref is a mutable refrence to int']
void helper_build_tree_1(int * const n_ref, int * const m_ref, int * const node_ref, deflate_state * const s, ct_data * const tree)
{
  int n = *n_ref;
  int m = *m_ref;
  int node = *node_ref;
  {
    n = s->heap[1];
    s->heap[1] = s->heap[s->heap_len--];
    pqdownheap(s, tree, 1);
  }
  ;
  m = s->heap[1];
  s->heap[--s->heap_max] = n;
  s->heap[--s->heap_max] = m;
  tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
  s->depth[node] = (uch) (((s->depth[n] >= s->depth[m]) ? (s->depth[n]) : (s->depth[m])) + 1);
  tree[n].dl.dad = (tree[m].dl.dad = (ush) node);
  s->heap[1] = node;
  node += 1;
  pqdownheap(s, tree, 1);
  *n_ref = n;
  *m_ref = m;
  *node_ref = node;
}


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
static void pqdownheap(deflate_state *s, ct_data *tree, int k)
{
  int v = s->heap[k];
  int j = k << 1;
  while (j <= s->heap_len)
  {
    if ((j < s->heap_len) && ((tree[s->heap[j + 1]].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[s->heap[j + 1]].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[s->heap[j + 1]] <= s->depth[s->heap[j]]))))
    {
      j += 1;
    }
    if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[v].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[v] <= s->depth[s->heap[j]])))
    {
      break;
    }
    s->heap[k] = s->heap[j];
    k = j;
    j <<= 1;
  }

  s->heap[k] = v;
}


----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to int', 'bits_ref is a mutable refrence to int', 'xbits_ref is a mutable refrence to int', 'f_ref is a mutable refrence to ush', 'overflow_ref is a mutable refrence to int']
void helper_gen_bitlen_2(int * const n_ref, int * const bits_ref, int * const xbits_ref, ush * const f_ref, int * const overflow_ref, deflate_state * const s, ct_data * const tree, int max_code, const ct_data * const stree, const intf * const extra, int base, int max_length, int h)
{
  int n = *n_ref;
  int bits = *bits_ref;
  int xbits = *xbits_ref;
  ush f = *f_ref;
  int overflow = *overflow_ref;
  n = s->heap[h];
  bits = tree[tree[n].dl.dad].dl.len + 1;
  if (bits > max_length)
  {
    bits = max_length, overflow++;
    overflow += 1;
  }
  tree[n].dl.len = (ush) bits;
  if (n > max_code)
  {
    continue;
  }
  s->bl_count[bits] += 1;
  xbits = 0;
  if (n >= base)
  {
    xbits = extra[n - base];
  }
  f = tree[n].fc.freq;
  s->opt_len += ((ulg) f) * ((unsigned) (bits + xbits));
  if (stree)
  {
    s->static_len += ((ulg) f) * ((unsigned) (stree[n].dl.len + xbits));
  }
  *n_ref = n;
  *bits_ref = bits;
  *xbits_ref = xbits;
  *f_ref = f;
  *overflow_ref = overflow;
}


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
typedef unsigned short ush
----------------------------
typedef int intf
----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static void gen_bitlen(deflate_state *s, tree_desc *desc)
{
  ct_data *tree = desc->dyn_tree;
  int max_code = desc->max_code;
  const ct_data *stree = desc->stat_desc->static_tree;
  const intf *extra = desc->stat_desc->extra_bits;
  int base = desc->stat_desc->extra_base;
  int max_length = desc->stat_desc->max_length;
  int h;
  int n;
  int m;
  int bits;
  int xbits;
  ush f;
  int overflow = 0;
  for (bits = 0; bits <= 15; bits += 1)
  {
    s->bl_count[bits] = 0;
  }

  tree[s->heap[s->heap_max]].dl.len = 0;
  for (h = s->heap_max + 1; h < ((2 * ((256 + 1) + 29)) + 1); h += 1)
  {
    helper_gen_bitlen_2(&n, &bits, &xbits, &f, &overflow, s, tree, max_code, stree, extra, base, max_length, h);
  }

  if (overflow == 0)
  {
    return;
  }
  ;
  do
  {
    bits = max_length - 1;
    while (s->bl_count[bits] == 0)
    {
      bits -= 1;
    }

    s->bl_count[bits] -= 1;
    s->bl_count[bits + 1] += 2;
    s->bl_count[max_length] -= 1;
    overflow -= 2;
  }
  while (overflow > 0);
  for (bits = max_length; bits != 0; bits -= 1)
  {
    helper_gen_bitlen_1(&h, &n, &m, s, tree, max_code, bits);
  }

}


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
void helper_gen_bitlen_1(int * const h_ref, int * const n_ref, int * const m_ref, deflate_state * const s, ct_data * const tree, int max_code, int bits)
{
  int h = *h_ref;
  int n = *n_ref;
  int m = *m_ref;
  n = s->bl_count[bits];
  while (n != 0)
  {
    h -= 1;
    m = s->heap[h];
    if (m > max_code)
    {
      continue;
    }
    if (((unsigned) tree[m].dl.len) != ((unsigned) bits))
    {
      ;
      s->opt_len += (((ulg) bits) - tree[m].dl.len) * tree[m].fc.freq;
      tree[m].dl.len = (ush) bits;
    }
    n -= 1;
  }

  *h_ref = h;
  *n_ref = n;
  *m_ref = m;
}


----------------------------
typedef int intf
----------------------------
void helper_gen_bitlen_2(int * const n_ref, int * const bits_ref, int * const xbits_ref, ush * const f_ref, int * const overflow_ref, deflate_state * const s, ct_data * const tree, int max_code, const ct_data * const stree, const intf * const extra, int base, int max_length, int h)
{
  int n = *n_ref;
  int bits = *bits_ref;
  int xbits = *xbits_ref;
  ush f = *f_ref;
  int overflow = *overflow_ref;
  n = s->heap[h];
  bits = tree[tree[n].dl.dad].dl.len + 1;
  if (bits > max_length)
  {
    bits = max_length, overflow++;
    overflow += 1;
  }
  tree[n].dl.len = (ush) bits;
  if (n > max_code)
  {
    continue;
  }
  s->bl_count[bits] += 1;
  xbits = 0;
  if (n >= base)
  {
    xbits = extra[n - base];
  }
  f = tree[n].fc.freq;
  s->opt_len += ((ulg) f) * ((unsigned) (bits + xbits));
  if (stree)
  {
    s->static_len += ((ulg) f) * ((unsigned) (stree[n].dl.len + xbits));
  }
  *n_ref = n;
  *bits_ref = bits;
  *xbits_ref = xbits;
  *f_ref = f;
  *overflow_ref = overflow;
}


----------------------------
typedef unsigned short ush
----------------------------
typedef struct tree_desc_s
{
  ct_data *dyn_tree;
  int max_code;
  const static_tree_desc *stat_desc;
} tree_desc
----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static void build_tree(deflate_state *s, tree_desc *desc)
{
  ct_data *tree = desc->dyn_tree;
  const ct_data *stree = desc->stat_desc->static_tree;
  int elems = desc->stat_desc->elems;
  int n;
  int m;
  int max_code = -1;
  int node;
  s->heap_len = 0, s->heap_max = (2 * ((256 + 1) + 29)) + 1;
  for (n = 0; n < elems; n += 1)
  {
    if (tree[n].fc.freq != 0)
    {
      s->heap[++s->heap_len] = (max_code = n);
      s->depth[n] = 0;
    }
    else
    {
      tree[n].dl.len = 0;
    }
  }

  while (s->heap_len < 2)
  {
    node = (s->heap[++s->heap_len] = (max_code < 2) ? (++max_code) : (0));
    tree[node].fc.freq = 1;
    s->depth[node] = 0;
    s->opt_len -= 1;
    if (stree)
    {
      s->static_len -= stree[node].dl.len;
    }
  }

  desc->max_code = max_code;
  for (n = s->heap_len / 2; n >= 1; n -= 1)
  {
    pqdownheap(s, tree, n);
  }

  node = elems;
  do
  {
    helper_build_tree_1(&n, &m, &node, s, tree);
  }
  while (s->heap_len >= 2);
  s->heap[--s->heap_max] = s->heap[1];
  gen_bitlen(s, (tree_desc *) desc);
  gen_codes((ct_data *) tree, max_code, s->bl_count);
}


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
static void pqdownheap(deflate_state *s, ct_data *tree, int k)
{
  int v = s->heap[k];
  int j = k << 1;
  while (j <= s->heap_len)
  {
    if ((j < s->heap_len) && ((tree[s->heap[j + 1]].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[s->heap[j + 1]].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[s->heap[j + 1]] <= s->depth[s->heap[j]]))))
    {
      j += 1;
    }
    if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq) || ((tree[v].fc.freq == tree[s->heap[j]].fc.freq) && (s->depth[v] <= s->depth[s->heap[j]])))
    {
      break;
    }
    s->heap[k] = s->heap[j];
    k = j;
    j <<= 1;
  }

  s->heap[k] = v;
}


----------------------------
static void gen_codes(ct_data *tree, int max_code, ushf *bl_count)
{
  ush next_code[15 + 1];
  unsigned code = 0;
  int bits;
  int n;
  for (bits = 1; bits <= 15; bits += 1)
  {
    code = (code + bl_count[bits - 1]) << 1;
    next_code[bits] = (ush) code;
  }

  ;
  ;
  for (n = 0; n <= max_code; n += 1)
  {
    int len = tree[n].dl.len;
    if (len == 0)
    {
      continue;
    }
    tree[n].fc.code = (ush) bi_reverse(next_code[len]++, len);
    ;
  }

}


----------------------------
void helper_build_tree_1(int * const n_ref, int * const m_ref, int * const node_ref, deflate_state * const s, ct_data * const tree)
{
  int n = *n_ref;
  int m = *m_ref;
  int node = *node_ref;
  {
    n = s->heap[1];
    s->heap[1] = s->heap[s->heap_len--];
    pqdownheap(s, tree, 1);
  }
  ;
  m = s->heap[1];
  s->heap[--s->heap_max] = n;
  s->heap[--s->heap_max] = m;
  tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
  s->depth[node] = (uch) (((s->depth[n] >= s->depth[m]) ? (s->depth[n]) : (s->depth[m])) + 1);
  tree[n].dl.dad = (tree[m].dl.dad = (ush) node);
  s->heap[1] = node;
  node += 1;
  pqdownheap(s, tree, 1);
  *n_ref = n;
  *m_ref = m;
  *node_ref = node;
}


----------------------------
static void gen_bitlen(deflate_state *s, tree_desc *desc)
{
  ct_data *tree = desc->dyn_tree;
  int max_code = desc->max_code;
  const ct_data *stree = desc->stat_desc->static_tree;
  const intf *extra = desc->stat_desc->extra_bits;
  int base = desc->stat_desc->extra_base;
  int max_length = desc->stat_desc->max_length;
  int h;
  int n;
  int m;
  int bits;
  int xbits;
  ush f;
  int overflow = 0;
  for (bits = 0; bits <= 15; bits += 1)
  {
    s->bl_count[bits] = 0;
  }

  tree[s->heap[s->heap_max]].dl.len = 0;
  for (h = s->heap_max + 1; h < ((2 * ((256 + 1) + 29)) + 1); h += 1)
  {
    helper_gen_bitlen_2(&n, &bits, &xbits, &f, &overflow, s, tree, max_code, stree, extra, base, max_length, h);
  }

  if (overflow == 0)
  {
    return;
  }
  ;
  do
  {
    bits = max_length - 1;
    while (s->bl_count[bits] == 0)
    {
      bits -= 1;
    }

    s->bl_count[bits] -= 1;
    s->bl_count[bits + 1] += 2;
    s->bl_count[max_length] -= 1;
    overflow -= 2;
  }
  while (overflow > 0);
  for (bits = max_length; bits != 0; bits -= 1)
  {
    helper_gen_bitlen_1(&h, &n, &m, s, tree, max_code, bits);
  }

}


----------------------------
typedef struct tree_desc_s
{
  ct_data *dyn_tree;
  int max_code;
  const static_tree_desc *stat_desc;
} tree_desc
----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static int build_bl_tree(deflate_state *s)
{
  int max_blindex;
  scan_tree(s, (ct_data *) s->dyn_ltree, s->l_desc.max_code);
  scan_tree(s, (ct_data *) s->dyn_dtree, s->d_desc.max_code);
  build_tree(s, (tree_desc *) (&s->bl_desc));
  for (max_blindex = 19 - 1; max_blindex >= 3; max_blindex -= 1)
  {
    if (s->bl_tree[bl_order[max_blindex]].dl.len != 0)
    {
      break;
    }
  }

  s->opt_len += (((3 * (((ulg) max_blindex) + 1)) + 5) + 5) + 4;
  ;
  return max_blindex;
}


/*** DEPENDENCIES:
static void scan_tree(deflate_state *s, ct_data *tree, int max_code)
{
  int n;
  int prevlen = -1;
  int curlen;
  int nextlen = tree[0].dl.len;
  int count = 0;
  int max_count = 7;
  int min_count = 4;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  tree[max_code + 1].dl.len = (ush) 0xffff;
  for (n = 0; n <= max_code; n += 1)
  {
    curlen = nextlen;
    nextlen = tree[n + 1].dl.len;
    if (((++count) < max_count) && (curlen == nextlen))
    {
      continue;
    }
    else
      if (count < min_count)
    {
      s->bl_tree[curlen].fc.freq += count;
    }
    else
      if (curlen != 0)
    {
      if (curlen != prevlen)
      {
        s->bl_tree[curlen].fc.freq += 1;
      }
      s->bl_tree[16].fc.freq += 1;
    }
    else
      if (count <= 10)
    {
      s->bl_tree[17].fc.freq += 1;
    }
    else
    {
      s->bl_tree[18].fc.freq += 1;
    }
    count = 0;
    prevlen = curlen;
    if (nextlen == 0)
    {
      max_count = 138, min_count = 3;
    }
    else
      if (curlen == nextlen)
    {
      max_count = 6, min_count = 3;
    }
    else
    {
      max_count = 7, min_count = 4;
    }
  }

}


----------------------------
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
static const uch bl_order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15}
----------------------------
static void build_tree(deflate_state *s, tree_desc *desc)
{
  ct_data *tree = desc->dyn_tree;
  const ct_data *stree = desc->stat_desc->static_tree;
  int elems = desc->stat_desc->elems;
  int n;
  int m;
  int max_code = -1;
  int node;
  s->heap_len = 0, s->heap_max = (2 * ((256 + 1) + 29)) + 1;
  for (n = 0; n < elems; n += 1)
  {
    if (tree[n].fc.freq != 0)
    {
      s->heap[++s->heap_len] = (max_code = n);
      s->depth[n] = 0;
    }
    else
    {
      tree[n].dl.len = 0;
    }
  }

  while (s->heap_len < 2)
  {
    node = (s->heap[++s->heap_len] = (max_code < 2) ? (++max_code) : (0));
    tree[node].fc.freq = 1;
    s->depth[node] = 0;
    s->opt_len -= 1;
    if (stree)
    {
      s->static_len -= stree[node].dl.len;
    }
  }

  desc->max_code = max_code;
  for (n = s->heap_len / 2; n >= 1; n -= 1)
  {
    pqdownheap(s, tree, n);
  }

  node = elems;
  do
  {
    helper_build_tree_1(&n, &m, &node, s, tree);
  }
  while (s->heap_len >= 2);
  s->heap[--s->heap_max] = s->heap[1];
  gen_bitlen(s, (tree_desc *) desc);
  gen_codes((ct_data *) tree, max_code, s->bl_count);
}


----------------------------
***/


// hint:  ['opt_lenb_ref is a mutable refrence to ulg', 'static_lenb_ref is a mutable refrence to ulg', 'max_blindex_ref is a mutable refrence to int']
void helper__tr_flush_block_1(ulg * const opt_lenb_ref, ulg * const static_lenb_ref, int * const max_blindex_ref, deflate_state * const s)
{
  ulg opt_lenb = *opt_lenb_ref;
  ulg static_lenb = *static_lenb_ref;
  int max_blindex = *max_blindex_ref;
  if (s->strm->data_type == 2)
  {
    s->strm->data_type = detect_data_type(s);
  }
  build_tree(s, (tree_desc *) (&s->l_desc));
  ;
  build_tree(s, (tree_desc *) (&s->d_desc));
  ;
  max_blindex = build_bl_tree(s);
  opt_lenb = ((s->opt_len + 3) + 7) >> 3;
  static_lenb = ((s->static_len + 3) + 7) >> 3;
  ;
  if ((static_lenb <= opt_lenb) || (s->strategy == 4))
  {
    opt_lenb = static_lenb;
  }
  *opt_lenb_ref = opt_lenb;
  *static_lenb_ref = static_lenb;
  *max_blindex_ref = max_blindex;
}


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
static void build_tree(deflate_state *s, tree_desc *desc)
{
  ct_data *tree = desc->dyn_tree;
  const ct_data *stree = desc->stat_desc->static_tree;
  int elems = desc->stat_desc->elems;
  int n;
  int m;
  int max_code = -1;
  int node;
  s->heap_len = 0, s->heap_max = (2 * ((256 + 1) + 29)) + 1;
  for (n = 0; n < elems; n += 1)
  {
    if (tree[n].fc.freq != 0)
    {
      s->heap[++s->heap_len] = (max_code = n);
      s->depth[n] = 0;
    }
    else
    {
      tree[n].dl.len = 0;
    }
  }

  while (s->heap_len < 2)
  {
    node = (s->heap[++s->heap_len] = (max_code < 2) ? (++max_code) : (0));
    tree[node].fc.freq = 1;
    s->depth[node] = 0;
    s->opt_len -= 1;
    if (stree)
    {
      s->static_len -= stree[node].dl.len;
    }
  }

  desc->max_code = max_code;
  for (n = s->heap_len / 2; n >= 1; n -= 1)
  {
    pqdownheap(s, tree, n);
  }

  node = elems;
  do
  {
    helper_build_tree_1(&n, &m, &node, s, tree);
  }
  while (s->heap_len >= 2);
  s->heap[--s->heap_max] = s->heap[1];
  gen_bitlen(s, (tree_desc *) desc);
  gen_codes((ct_data *) tree, max_code, s->bl_count);
}


----------------------------
typedef unsigned long ulg
----------------------------
static int build_bl_tree(deflate_state *s)
{
  int max_blindex;
  scan_tree(s, (ct_data *) s->dyn_ltree, s->l_desc.max_code);
  scan_tree(s, (ct_data *) s->dyn_dtree, s->d_desc.max_code);
  build_tree(s, (tree_desc *) (&s->bl_desc));
  for (max_blindex = 19 - 1; max_blindex >= 3; max_blindex -= 1)
  {
    if (s->bl_tree[bl_order[max_blindex]].dl.len != 0)
    {
      break;
    }
  }

  s->opt_len += (((3 * (((ulg) max_blindex) + 1)) + 5) + 5) + 4;
  ;
  return max_blindex;
}


----------------------------
static int detect_data_type(deflate_state *s)
{
  unsigned long block_mask = 0xf3ffc07fUL;
  int n;
  for (n = 0; n <= 31; n += 1, block_mask >>= 1)
  {
    if ((block_mask & 1) && (s->dyn_ltree[n].fc.freq != 0))
    {
      return 0;
    }
  }

  if (((s->dyn_ltree[9].fc.freq != 0) || (s->dyn_ltree[10].fc.freq != 0)) || (s->dyn_ltree[13].fc.freq != 0))
  {
    return 1;
  }
  for (n = 32; n < 256; n += 1)
  {
    if (s->dyn_ltree[n].fc.freq != 0)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
***/


// hint:  ['dist_ref is a mutable refrence to unsigned', 'lc_ref is a mutable refrence to int', 'code_ref is a mutable refrence to unsigned', 'extra_ref is a mutable refrence to int']
void helper_helper_helper_compress_block_2_1_2(unsigned * const dist_ref, int * const lc_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  code = _length_code[lc];
  {
    helper_helper_helper_helper_compress_block_2_1_2_1(s, ltree, code);
  }
  ;
  extra = extra_lbits[code];
  if (extra != 0)
  {
    helper_helper_helper_helper_compress_block_2_1_2_3(&lc, s, code, extra);
  }
  dist -= 1;
  code = (dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)]);
  ;
  {
    helper_helper_helper_helper_compress_block_2_1_2_2(s, dtree, code);
  }
  ;
  extra = extra_dbits[code];
  if (extra != 0)
  {
    helper_helper_helper_helper_compress_block_2_1_2_4(&dist, s, code, extra);
  }
  *dist_ref = dist;
  *lc_ref = lc;
  *code_ref = code;
  *extra_ref = extra;
}


/*** DEPENDENCIES:
extern const uch _dist_code[]
----------------------------
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
static const int extra_lbits[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0}
----------------------------
extern const uch _length_code[]
----------------------------
void helper_helper_helper_helper_compress_block_2_1_2_1(deflate_state * const s, const ct_data * const ltree, unsigned code)
{
  int len = ltree[(code + 256) + 1].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) ltree[(code + 256) + 1].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ltree[(code + 256) + 1].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_helper_helper_helper_compress_block_2_1_2_4(unsigned * const dist_ref, deflate_state * const s, unsigned code, int extra)
{
  unsigned dist = *dist_ref;
  dist -= (unsigned) base_dist[code];
  {
    int len = extra;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) dist;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) dist) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  *dist_ref = dist;
}


----------------------------
void helper_helper_helper_helper_compress_block_2_1_2_3(int * const lc_ref, deflate_state * const s, unsigned code, int extra)
{
  int lc = *lc_ref;
  lc -= base_length[code];
  {
    int len = extra;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) lc;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) lc) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  *lc_ref = lc;
}


----------------------------
void helper_helper_helper_helper_compress_block_2_1_2_2(deflate_state * const s, const ct_data * const dtree, unsigned code)
{
  int len = dtree[code].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) dtree[code].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) dtree[code].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
static const int extra_dbits[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13}
----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


// hint:  ['dist_ref is a mutable refrence to unsigned', 'lc_ref is a mutable refrence to int', 'sx_ref is a mutable refrence to unsigned', 'code_ref is a mutable refrence to unsigned', 'extra_ref is a mutable refrence to int']
void helper_helper_compress_block_2_1(unsigned * const dist_ref, int * const lc_ref, unsigned * const sx_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned sx = *sx_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  dist = s->sym_buf[sx] & 0xff;
  sx += 1;
  dist += ((unsigned) (s->sym_buf[sx] & 0xff)) << 8;
  sx += 1;
  lc = s->sym_buf[sx];
  sx += 1;
  if (dist == 0)
  {
    helper_helper_helper_compress_block_2_1_1(s, ltree, lc);
  }
  else
  {
    helper_helper_helper_compress_block_2_1_2(&dist, &lc, &code, &extra, s, ltree, dtree);
  }
  ;
  *dist_ref = dist;
  *lc_ref = lc;
  *sx_ref = sx;
  *code_ref = code;
  *extra_ref = extra;
}


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
void helper_helper_helper_compress_block_2_1_2(unsigned * const dist_ref, int * const lc_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  code = _length_code[lc];
  {
    helper_helper_helper_helper_compress_block_2_1_2_1(s, ltree, code);
  }
  ;
  extra = extra_lbits[code];
  if (extra != 0)
  {
    helper_helper_helper_helper_compress_block_2_1_2_3(&lc, s, code, extra);
  }
  dist -= 1;
  code = (dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)]);
  ;
  {
    helper_helper_helper_helper_compress_block_2_1_2_2(s, dtree, code);
  }
  ;
  extra = extra_dbits[code];
  if (extra != 0)
  {
    helper_helper_helper_helper_compress_block_2_1_2_4(&dist, s, code, extra);
  }
  *dist_ref = dist;
  *lc_ref = lc;
  *code_ref = code;
  *extra_ref = extra;
}


----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
void helper_helper_helper_compress_block_2_1_1(deflate_state * const s, const ct_data * const ltree, int lc)
{
  {
    int len = ltree[lc].dl.len;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) ltree[lc].fc.code;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ltree[lc].fc.code) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  ;
}


----------------------------
***/


// hint:  ['dist_ref is a mutable refrence to unsigned', 'lc_ref is a mutable refrence to int', 'sx_ref is a mutable refrence to unsigned', 'code_ref is a mutable refrence to unsigned', 'extra_ref is a mutable refrence to int']
void helper_compress_block_2(unsigned * const dist_ref, int * const lc_ref, unsigned * const sx_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned sx = *sx_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  do
  {
    helper_helper_compress_block_2_1(&dist, &lc, &sx, &code, &extra, s, ltree, dtree);
  }
  while (sx < s->sym_next);
  *dist_ref = dist;
  *lc_ref = lc;
  *sx_ref = sx;
  *code_ref = code;
  *extra_ref = extra;
}


/*** DEPENDENCIES:
void helper_helper_compress_block_2_1(unsigned * const dist_ref, int * const lc_ref, unsigned * const sx_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned sx = *sx_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  dist = s->sym_buf[sx] & 0xff;
  sx += 1;
  dist += ((unsigned) (s->sym_buf[sx] & 0xff)) << 8;
  sx += 1;
  lc = s->sym_buf[sx];
  sx += 1;
  if (dist == 0)
  {
    helper_helper_helper_compress_block_2_1_1(s, ltree, lc);
  }
  else
  {
    helper_helper_helper_compress_block_2_1_2(&dist, &lc, &code, &extra, s, ltree, dtree);
  }
  ;
  *dist_ref = dist;
  *lc_ref = lc;
  *sx_ref = sx;
  *code_ref = code;
  *extra_ref = extra;
}


----------------------------
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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static void compress_block(deflate_state *s, const ct_data *ltree, const ct_data *dtree)
{
  unsigned dist;
  int lc;
  unsigned sx = 0;
  unsigned code;
  int extra;
  if (s->sym_next != 0)
  {
    helper_compress_block_2(&dist, &lc, &sx, &code, &extra, s, ltree, dtree);
  }
  {
    helper_compress_block_1(s, ltree);
  }
  ;
}


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
void helper_compress_block_1(deflate_state * const s, const ct_data * const ltree)
{
  int len = ltree[256].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) ltree[256].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) ltree[256].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
void helper_compress_block_2(unsigned * const dist_ref, int * const lc_ref, unsigned * const sx_ref, unsigned * const code_ref, int * const extra_ref, deflate_state * const s, const ct_data * const ltree, const ct_data * const dtree)
{
  unsigned dist = *dist_ref;
  int lc = *lc_ref;
  unsigned sx = *sx_ref;
  unsigned code = *code_ref;
  int extra = *extra_ref;
  do
  {
    helper_helper_compress_block_2_1(&dist, &lc, &sx, &code, &extra, s, ltree, dtree);
  }
  while (sx < s->sym_next);
  *dist_ref = dist;
  *lc_ref = lc;
  *sx_ref = sx;
  *code_ref = code;
  *extra_ref = extra;
}


----------------------------
***/


void helper__tr_flush_block_2(deflate_state * const s, int last)
{
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = ((int) (1 << 1)) + last;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ((1 << 1) + last)) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  compress_block(s, (const ct_data *) static_ltree, (const ct_data *) static_dtree);
}


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
static const ct_data static_dtree[30] = {{{0}, {5}}, {{16}, {5}}, {{8}, {5}}, {{24}, {5}}, {{4}, {5}}, {{20}, {5}}, {{12}, {5}}, {{28}, {5}}, {{2}, {5}}, {{18}, {5}}, {{10}, {5}}, {{26}, {5}}, {{6}, {5}}, {{22}, {5}}, {{14}, {5}}, {{30}, {5}}, {{1}, {5}}, {{17}, {5}}, {{9}, {5}}, {{25}, {5}}, {{5}, {5}}, {{21}, {5}}, {{13}, {5}}, {{29}, {5}}, {{3}, {5}}, {{19}, {5}}, {{11}, {5}}, {{27}, {5}}, {{7}, {5}}, {{23}, {5}}}
----------------------------
static const ct_data static_ltree[((256 + 1) + 29) + 2] = {{{12}, {8}}, {{140}, {8}}, {{76}, {8}}, {{204}, {8}}, {{44}, {8}}, {{172}, {8}}, {{108}, {8}}, {{236}, {8}}, {{28}, {8}}, {{156}, {8}}, {{92}, {8}}, {{220}, {8}}, {{60}, {8}}, {{188}, {8}}, {{124}, {8}}, {{252}, {8}}, {{2}, {8}}, {{130}, {8}}, {{66}, {8}}, {{194}, {8}}, {{34}, {8}}, {{162}, {8}}, {{98}, {8}}, {{226}, {8}}, {{18}, {8}}, {{146}, {8}}, {{82}, {8}}, {{210}, {8}}, {{50}, {8}}, {{178}, {8}}, {{114}, {8}}, {{242}, {8}}, {{10}, {8}}, {{138}, {8}}, {{74}, {8}}, {{202}, {8}}, {{42}, {8}}, {{170}, {8}}, {{106}, {8}}, {{234}, {8}}, {{26}, {8}}, {{154}, {8}}, {{90}, {8}}, {{218}, {8}}, {{58}, {8}}, {{186}, {8}}, {{122}, {8}}, {{250}, {8}}, {{6}, {8}}, {{134}, {8}}, {{70}, {8}}, {{198}, {8}}, {{38}, {8}}, {{166}, {8}}, {{102}, {8}}, {{230}, {8}}, {{22}, {8}}, {{150}, {8}}, {{86}, {8}}, {{214}, {8}}, {{54}, {8}}, {{182}, {8}}, {{118}, {8}}, {{246}, {8}}, {{14}, {8}}, {{142}, {8}}, {{78}, {8}}, {{206}, {8}}, {{46}, {8}}, {{174}, {8}}, {{110}, {8}}, {{238}, {8}}, {{30}, {8}}, {{158}, {8}}, {{94}, {8}}, {{222}, {8}}, {{62}, {8}}, {{190}, {8}}, {{126}, {8}}, {{254}, {8}}, {{1}, {8}}, {{129}, {8}}, {{65}, {8}}, {{193}, {8}}, {{33}, {8}}, {{161}, {8}}, {{97}, {8}}, {{225}, {8}}, {{17}, {8}}, {{145}, {8}}, {{81}, {8}}, {{209}, {8}}, {{49}, {8}}, {{177}, {8}}, {{113}, {8}}, {{241}, {8}}, {{9}, {8}}, {{137}, {8}}, {{73}, {8}}, {{201}, {8}}, {{41}, {8}}, {{169}, {8}}, {{105}, {8}}, {{233}, {8}}, {{25}, {8}}, {{153}, {8}}, {{89}, {8}}, {{217}, {8}}, {{57}, {8}}, {{185}, {8}}, {{121}, {8}}, {{249}, {8}}, {{5}, {8}}, {{133}, {8}}, {{69}, {8}}, {{197}, {8}}, {{37}, {8}}, {{165}, {8}}, {{101}, {8}}, {{229}, {8}}, {{21}, {8}}, {{149}, {8}}, {{85}, {8}}, {{213}, {8}}, {{53}, {8}}, {{181}, {8}}, {{117}, {8}}, {{245}, {8}}, {{13}, {8}}, {{141}, {8}}, {{77}, {8}}, {{205}, {8}}, {{45}, {8}}, {{173}, {8}}, {{109}, {8}}, {{237}, {8}}, {{29}, {8}}, {{157}, {8}}, {{93}, {8}}, {{221}, {8}}, {{61}, {8}}, {{189}, {8}}, {{125}, {8}}, {{253}, {8}}, {{19}, {9}}, {{275}, {9}}, {{147}, {9}}, {{403}, {9}}, {{83}, {9}}, {{339}, {9}}, {{211}, {9}}, {{467}, {9}}, {{51}, {9}}, {{307}, {9}}, {{179}, {9}}, {{435}, {9}}, {{115}, {9}}, {{371}, {9}}, {{243}, {9}}, {{499}, {9}}, {{11}, {9}}, {{267}, {9}}, {{139}, {9}}, {{395}, {9}}, {{75}, {9}}, {{331}, {9}}, {{203}, {9}}, {{459}, {9}}, {{43}, {9}}, {{299}, {9}}, {{171}, {9}}, {{427}, {9}}, {{107}, {9}}, {{363}, {9}}, {{235}, {9}}, {{491}, {9}}, {{27}, {9}}, {{283}, {9}}, {{155}, {9}}, {{411}, {9}}, {{91}, {9}}, {{347}, {9}}, {{219}, {9}}, {{475}, {9}}, {{59}, {9}}, {{315}, {9}}, {{187}, {9}}, {{443}, {9}}, {{123}, {9}}, {{379}, {9}}, {{251}, {9}}, {{507}, {9}}, {{7}, {9}}, {{263}, {9}}, {{135}, {9}}, {{391}, {9}}, {{71}, {9}}, {{327}, {9}}, {{199}, {9}}, {{455}, {9}}, {{39}, {9}}, {{295}, {9}}, {{167}, {9}}, {{423}, {9}}, {{103}, {9}}, {{359}, {9}}, {{231}, {9}}, {{487}, {9}}, {{23}, {9}}, {{279}, {9}}, {{151}, {9}}, {{407}, {9}}, {{87}, {9}}, {{343}, {9}}, {{215}, {9}}, {{471}, {9}}, {{55}, {9}}, {{311}, {9}}, {{183}, {9}}, {{439}, {9}}, {{119}, {9}}, {{375}, {9}}, {{247}, {9}}, {{503}, {9}}, {{15}, {9}}, {{271}, {9}}, {{143}, {9}}, {{399}, {9}}, {{79}, {9}}, {{335}, {9}}, {{207}, {9}}, {{463}, {9}}, {{47}, {9}}, {{303}, {9}}, {{175}, {9}}, {{431}, {9}}, {{111}, {9}}, {{367}, {9}}, {{239}, {9}}, {{495}, {9}}, {{31}, {9}}, {{287}, {9}}, {{159}, {9}}, {{415}, {9}}, {{95}, {9}}, {{351}, {9}}, {{223}, {9}}, {{479}, {9}}, {{63}, {9}}, {{319}, {9}}, {{191}, {9}}, {{447}, {9}}, {{127}, {9}}, {{383}, {9}}, {{255}, {9}}, {{511}, {9}}, {{0}, {7}}, {{64}, {7}}, {{32}, {7}}, {{96}, {7}}, {{16}, {7}}, {{80}, {7}}, {{48}, {7}}, {{112}, {7}}, {{8}, {7}}, {{72}, {7}}, {{40}, {7}}, {{104}, {7}}, {{24}, {7}}, {{88}, {7}}, {{56}, {7}}, {{120}, {7}}, {{4}, {7}}, {{68}, {7}}, {{36}, {7}}, {{100}, {7}}, {{20}, {7}}, {{84}, {7}}, {{52}, {7}}, {{116}, {7}}, {{3}, {8}}, {{131}, {8}}, {{67}, {8}}, {{195}, {8}}, {{35}, {8}}, {{163}, {8}}, {{99}, {8}}, {{227}, {8}}}
----------------------------
static void compress_block(deflate_state *s, const ct_data *ltree, const ct_data *dtree)
{
  unsigned dist;
  int lc;
  unsigned sx = 0;
  unsigned code;
  int extra;
  if (s->sym_next != 0)
  {
    helper_compress_block_2(&dist, &lc, &sx, &code, &extra, s, ltree, dtree);
  }
  {
    helper_compress_block_1(s, ltree);
  }
  ;
}


----------------------------
***/


// hint:  ['count_ref is a mutable refrence to int']
void helper_helper_send_tree_1_4(int * const count_ref, deflate_state * const s, int prevlen, int curlen)
{
  int count = *count_ref;
  if (curlen != prevlen)
  {
    helper_helper_helper_send_tree_1_4_3(&count, s, curlen);
  }
  ;
  {
    helper_helper_helper_send_tree_1_4_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_4_2(s, count);
  }
  ;
  *count_ref = count;
}


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
void helper_helper_helper_send_tree_1_4_3(int * const count_ref, deflate_state * const s, int curlen)
{
  int count = *count_ref;
  {
    int len = s->bl_tree[curlen].dl.len;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) s->bl_tree[curlen].fc.code;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) s->bl_tree[curlen].fc.code) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  count -= 1;
  *count_ref = count;
}


----------------------------
void helper_helper_helper_send_tree_1_4_1(deflate_state * const s)
{
  int len = s->bl_tree[16].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[16].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[16].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_helper_helper_send_tree_1_4_2(deflate_state * const s, int count)
{
  int len = 2;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 3;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 3)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


void helper_helper_send_tree_1_2(deflate_state * const s, int count)
{
  {
    helper_helper_helper_send_tree_1_2_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_2_2(s, count);
  }
  ;
}


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
void helper_helper_helper_send_tree_1_2_1(deflate_state * const s)
{
  int len = s->bl_tree[17].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[17].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[17].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_helper_helper_send_tree_1_2_2(deflate_state * const s, int count)
{
  int len = 3;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 3;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 3)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


void helper_helper_send_tree_1_3(deflate_state * const s, int count)
{
  {
    helper_helper_helper_send_tree_1_3_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_3_2(s, count);
  }
  ;
}


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
void helper_helper_helper_send_tree_1_3_2(deflate_state * const s, int count)
{
  int len = 7;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) count) - 11;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (count - 11)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_helper_helper_send_tree_1_3_1(deflate_state * const s)
{
  int len = s->bl_tree[18].dl.len;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = (int) s->bl_tree[18].fc.code;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) s->bl_tree[18].fc.code) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


// hint:  ['prevlen_ref is a mutable refrence to int', 'curlen_ref is a mutable refrence to int', 'nextlen_ref is a mutable refrence to int', 'count_ref is a mutable refrence to int', 'max_count_ref is a mutable refrence to int', 'min_count_ref is a mutable refrence to int']
void helper_send_tree_1(int * const prevlen_ref, int * const curlen_ref, int * const nextlen_ref, int * const count_ref, int * const max_count_ref, int * const min_count_ref, deflate_state * const s, ct_data * const tree, int n)
{
  int prevlen = *prevlen_ref;
  int curlen = *curlen_ref;
  int nextlen = *nextlen_ref;
  int count = *count_ref;
  int max_count = *max_count_ref;
  int min_count = *min_count_ref;
  curlen = nextlen;
  nextlen = tree[n + 1].dl.len;
  if (((++count) < max_count) && (curlen == nextlen))
  {
    continue;
  }
  else
    if (count < min_count)
  {
    helper_helper_send_tree_1_1(s, curlen, count);
  }
  else
    if (curlen != 0)
  {
    helper_helper_send_tree_1_4(&count, s, prevlen, curlen);
  }
  else
    if (count <= 10)
  {
    helper_helper_send_tree_1_2(s, count);
  }
  else
  {
    helper_helper_send_tree_1_3(s, count);
  }
  count = 0;
  prevlen = curlen;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  else
    if (curlen == nextlen)
  {
    max_count = 6, min_count = 3;
  }
  else
  {
    max_count = 7, min_count = 4;
  }
  *prevlen_ref = prevlen;
  *curlen_ref = curlen;
  *nextlen_ref = nextlen;
  *count_ref = count;
  *max_count_ref = max_count;
  *min_count_ref = min_count;
}


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
void helper_helper_send_tree_1_4(int * const count_ref, deflate_state * const s, int prevlen, int curlen)
{
  int count = *count_ref;
  if (curlen != prevlen)
  {
    helper_helper_helper_send_tree_1_4_3(&count, s, curlen);
  }
  ;
  {
    helper_helper_helper_send_tree_1_4_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_4_2(s, count);
  }
  ;
  *count_ref = count;
}


----------------------------
void helper_helper_send_tree_1_2(deflate_state * const s, int count)
{
  {
    helper_helper_helper_send_tree_1_2_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_2_2(s, count);
  }
  ;
}


----------------------------
void helper_helper_send_tree_1_3(deflate_state * const s, int count)
{
  {
    helper_helper_helper_send_tree_1_3_1(s);
  }
  ;
  {
    helper_helper_helper_send_tree_1_3_2(s, count);
  }
  ;
}


----------------------------
void helper_helper_send_tree_1_1(deflate_state * const s, int curlen, int count)
{
  do
  {
    {
      int len = s->bl_tree[curlen].dl.len;
      if (s->bi_valid > (((int) 16) - len))
      {
        int val = (int) s->bl_tree[curlen].fc.code;
        s->bi_buf |= ((ush) val) << s->bi_valid;
        {
          {
            s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
          }
          ;
          {
            s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
          }
          ;
        }
        ;
        s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
        s->bi_valid += len - 16;
      }
      else
      {
        s->bi_buf |= ((ush) s->bl_tree[curlen].fc.code) << s->bi_valid;
        s->bi_valid += len;
      }
    }
    ;
  }
  while ((--count) != 0);
}


----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


static void send_tree(deflate_state *s, ct_data *tree, int max_code)
{
  int n;
  int prevlen = -1;
  int curlen;
  int nextlen = tree[0].dl.len;
  int count = 0;
  int max_count = 7;
  int min_count = 4;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  for (n = 0; n <= max_code; n += 1)
  {
    helper_send_tree_1(&prevlen, &curlen, &nextlen, &count, &max_count, &min_count, s, tree, n);
  }

}


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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
void helper_send_tree_1(int * const prevlen_ref, int * const curlen_ref, int * const nextlen_ref, int * const count_ref, int * const max_count_ref, int * const min_count_ref, deflate_state * const s, ct_data * const tree, int n)
{
  int prevlen = *prevlen_ref;
  int curlen = *curlen_ref;
  int nextlen = *nextlen_ref;
  int count = *count_ref;
  int max_count = *max_count_ref;
  int min_count = *min_count_ref;
  curlen = nextlen;
  nextlen = tree[n + 1].dl.len;
  if (((++count) < max_count) && (curlen == nextlen))
  {
    continue;
  }
  else
    if (count < min_count)
  {
    helper_helper_send_tree_1_1(s, curlen, count);
  }
  else
    if (curlen != 0)
  {
    helper_helper_send_tree_1_4(&count, s, prevlen, curlen);
  }
  else
    if (count <= 10)
  {
    helper_helper_send_tree_1_2(s, count);
  }
  else
  {
    helper_helper_send_tree_1_3(s, count);
  }
  count = 0;
  prevlen = curlen;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  else
    if (curlen == nextlen)
  {
    max_count = 6, min_count = 3;
  }
  else
  {
    max_count = 7, min_count = 4;
  }
  *prevlen_ref = prevlen;
  *curlen_ref = curlen;
  *nextlen_ref = nextlen;
  *count_ref = count;
  *max_count_ref = max_count;
  *min_count_ref = min_count;
}


----------------------------
***/


static void send_all_trees(deflate_state *s, int lcodes, int dcodes, int blcodes)
{
  int rank;
  ;
  ;
  ;
  {
    helper_send_all_trees_1(s, lcodes);
  }
  ;
  {
    helper_send_all_trees_2(s, dcodes);
  }
  ;
  {
    helper_send_all_trees_3(s, blcodes);
  }
  ;
  for (rank = 0; rank < blcodes; rank += 1)
  {
    helper_send_all_trees_4(s, rank);
  }

  ;
  send_tree(s, (ct_data *) s->dyn_ltree, lcodes - 1);
  ;
  send_tree(s, (ct_data *) s->dyn_dtree, dcodes - 1);
  ;
}


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
static void send_tree(deflate_state *s, ct_data *tree, int max_code)
{
  int n;
  int prevlen = -1;
  int curlen;
  int nextlen = tree[0].dl.len;
  int count = 0;
  int max_count = 7;
  int min_count = 4;
  if (nextlen == 0)
  {
    max_count = 138, min_count = 3;
  }
  for (n = 0; n <= max_code; n += 1)
  {
    helper_send_tree_1(&prevlen, &curlen, &nextlen, &count, &max_count, &min_count, s, tree, n);
  }

}


----------------------------
void helper_send_all_trees_3(deflate_state * const s, int blcodes)
{
  int len = 4;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) blcodes) - 4;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (blcodes - 4)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_send_all_trees_4(deflate_state * const s, int rank)
{
  ;
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = (int) s->bl_tree[bl_order[rank]].dl.len;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) s->bl_tree[bl_order[rank]].dl.len) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
}


----------------------------
void helper_send_all_trees_1(deflate_state * const s, int lcodes)
{
  int len = 5;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) lcodes) - 257;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (lcodes - 257)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
void helper_send_all_trees_2(deflate_state * const s, int dcodes)
{
  int len = 5;
  if (s->bi_valid > (((int) 16) - len))
  {
    int val = ((int) dcodes) - 1;
    s->bi_buf |= ((ush) val) << s->bi_valid;
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
    s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
    s->bi_valid += len - 16;
  }
  else
  {
    s->bi_buf |= ((ush) (dcodes - 1)) << s->bi_valid;
    s->bi_valid += len;
  }
}


----------------------------
***/


void helper__tr_flush_block_3(deflate_state * const s, int last, int max_blindex)
{
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = ((int) (2 << 1)) + last;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ((2 << 1) + last)) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  send_all_trees(s, s->l_desc.max_code + 1, s->d_desc.max_code + 1, max_blindex + 1);
  compress_block(s, (const ct_data *) s->dyn_ltree, (const ct_data *) s->dyn_dtree);
}


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
static void send_all_trees(deflate_state *s, int lcodes, int dcodes, int blcodes)
{
  int rank;
  ;
  ;
  ;
  {
    helper_send_all_trees_1(s, lcodes);
  }
  ;
  {
    helper_send_all_trees_2(s, dcodes);
  }
  ;
  {
    helper_send_all_trees_3(s, blcodes);
  }
  ;
  for (rank = 0; rank < blcodes; rank += 1)
  {
    helper_send_all_trees_4(s, rank);
  }

  ;
  send_tree(s, (ct_data *) s->dyn_ltree, lcodes - 1);
  ;
  send_tree(s, (ct_data *) s->dyn_dtree, dcodes - 1);
  ;
}


----------------------------
static void compress_block(deflate_state *s, const ct_data *ltree, const ct_data *dtree)
{
  unsigned dist;
  int lc;
  unsigned sx = 0;
  unsigned code;
  int extra;
  if (s->sym_next != 0)
  {
    helper_compress_block_2(&dist, &lc, &sx, &code, &extra, s, ltree, dtree);
  }
  {
    helper_compress_block_1(s, ltree);
  }
  ;
}


----------------------------
***/


void _tr_flush_block(deflate_state *s, charf *buf, ulg stored_len, int last)
{
  ulg opt_lenb;
  ulg static_lenb;
  int max_blindex = 0;
  if (s->level > 0)
  {
    helper__tr_flush_block_1(&opt_lenb, &static_lenb, &max_blindex, s);
  }
  else
  {
    ;
    opt_lenb = (static_lenb = stored_len + 5);
  }
  if (((stored_len + 4) <= opt_lenb) && (buf != ((char *) 0)))
  {
    _tr_stored_block(s, buf, stored_len, last);
  }
  else
    if (static_lenb == opt_lenb)
  {
    helper__tr_flush_block_2(s, last);
  }
  else
  {
    helper__tr_flush_block_3(s, last, max_blindex);
  }
  ;
  init_block(s);
  if (last)
  {
    bi_windup(s);
  }
  ;
}


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
void helper__tr_flush_block_1(ulg * const opt_lenb_ref, ulg * const static_lenb_ref, int * const max_blindex_ref, deflate_state * const s)
{
  ulg opt_lenb = *opt_lenb_ref;
  ulg static_lenb = *static_lenb_ref;
  int max_blindex = *max_blindex_ref;
  if (s->strm->data_type == 2)
  {
    s->strm->data_type = detect_data_type(s);
  }
  build_tree(s, (tree_desc *) (&s->l_desc));
  ;
  build_tree(s, (tree_desc *) (&s->d_desc));
  ;
  max_blindex = build_bl_tree(s);
  opt_lenb = ((s->opt_len + 3) + 7) >> 3;
  static_lenb = ((s->static_len + 3) + 7) >> 3;
  ;
  if ((static_lenb <= opt_lenb) || (s->strategy == 4))
  {
    opt_lenb = static_lenb;
  }
  *opt_lenb_ref = opt_lenb;
  *static_lenb_ref = static_lenb;
  *max_blindex_ref = max_blindex;
}


----------------------------
void _tr_stored_block(deflate_state *s, charf *buf, ulg stored_len, int last)
{
  {
    helper__tr_stored_block_1(s, last);
  }
  ;
  bi_windup(s);
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) stored_len) & 0xff));
    }
    ;
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) ((ush) stored_len)) >> 8));
    }
    ;
  }
  ;
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) (~stored_len)) & 0xff));
    }
    ;
    {
      s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) ((ush) (~stored_len))) >> 8));
    }
    ;
  }
  ;
  if (stored_len)
  {
    memcpy(s->pending_buf + s->pending, (Bytef *) buf, stored_len);
  }
  s->pending += stored_len;
}


----------------------------
void helper__tr_flush_block_2(deflate_state * const s, int last)
{
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = ((int) (1 << 1)) + last;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ((1 << 1) + last)) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  compress_block(s, (const ct_data *) static_ltree, (const ct_data *) static_dtree);
}


----------------------------
static void init_block(deflate_state *s)
{
  int n;
  for (n = 0; n < ((256 + 1) + 29); n += 1)
  {
    s->dyn_ltree[n].fc.freq = 0;
  }

  for (n = 0; n < 30; n += 1)
  {
    s->dyn_dtree[n].fc.freq = 0;
  }

  for (n = 0; n < 19; n += 1)
  {
    s->bl_tree[n].fc.freq = 0;
  }

  s->dyn_ltree[256].fc.freq = 1;
  s->opt_len = (s->static_len = 0L);
  s->sym_next = (s->matches = 0);
}


----------------------------
typedef unsigned long ulg
----------------------------
typedef char charf
----------------------------
static void bi_windup(deflate_state *s)
{
  if (s->bi_valid > 8)
  {
    {
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
      }
      ;
      {
        s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
      }
      ;
    }
    ;
  }
  else
    if (s->bi_valid > 0)
  {
    {
      s->pending_buf[s->pending++] = (Bytef) ((Byte) s->bi_buf);
    }
    ;
  }
  s->bi_buf = 0;
  s->bi_valid = 0;
}


----------------------------
void helper__tr_flush_block_3(deflate_state * const s, int last, int max_blindex)
{
  {
    int len = 3;
    if (s->bi_valid > (((int) 16) - len))
    {
      int val = ((int) (2 << 1)) + last;
      s->bi_buf |= ((ush) val) << s->bi_valid;
      {
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (s->bi_buf & 0xff));
        }
        ;
        {
          s->pending_buf[s->pending++] = (Bytef) ((uch) (((ush) s->bi_buf) >> 8));
        }
        ;
      }
      ;
      s->bi_buf = ((ush) val) >> (16 - s->bi_valid);
      s->bi_valid += len - 16;
    }
    else
    {
      s->bi_buf |= ((ush) ((2 << 1) + last)) << s->bi_valid;
      s->bi_valid += len;
    }
  }
  ;
  send_all_trees(s, s->l_desc.max_code + 1, s->d_desc.max_code + 1, max_blindex + 1);
  compress_block(s, (const ct_data *) s->dyn_ltree, (const ct_data *) s->dyn_dtree);
}


----------------------------
***/


int _tr_tally(deflate_state *s, unsigned dist, unsigned lc)
{
  s->sym_buf[s->sym_next++] = (uch) dist;
  s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
  s->sym_buf[s->sym_next++] = (uch) lc;
  if (dist == 0)
  {
    s->dyn_ltree[lc].fc.freq += 1;
  }
  else
  {
    s->matches += 1;
    dist -= 1;
    ;
    s->dyn_ltree[(_length_code[lc] + 256) + 1].fc.freq += 1;
    s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
  }
  return s->sym_next == s->sym_end;
}


/*** DEPENDENCIES:
extern const uch _length_code[]
----------------------------
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
extern const uch _dist_code[]
----------------------------
***/


