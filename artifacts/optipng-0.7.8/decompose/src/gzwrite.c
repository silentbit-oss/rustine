static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int wrap = 1;
  static const char my_version[] = "1.3-optipng";
  if (((version == 0) || (version[0] != my_version[0])) || (stream_size != (sizeof(z_stream))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  if (level == (-1))
  {
    level = 6;
  }
  if (windowBits < 0)
  {
    wrap = 0;
    if (windowBits < (-15))
    {
      return -2;
    }
    windowBits = -windowBits;
  }
  if ((((((((((memLevel < 1) || (memLevel > 9)) || (method != 8)) || (windowBits < 8)) || (windowBits > 15)) || (level < 0)) || (level > 9)) || (strategy < 0)) || (strategy > 4)) || ((windowBits == 8) && (wrap != 1)))
  {
    return -2;
  }
  if (windowBits == 8)
  {
    windowBits = 9;
  }
  s_idx = (deflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(deflate_state));
  if ((&s[s_idx]) == 0)
  {
    return -4;
  }
  strm->state = (struct internal_state *) s;
  s->strm = strm;
  s->status = 42;
  s->wrap = wrap;
  s->gzhead = 0;
  s->w_bits = (uInt) windowBits;
  s->w_size = 1 << s->w_bits;
  s->w_mask = s->w_size - 1;
  s->hash_bits = ((uInt) memLevel) + 7;
  s->hash_size = 1 << s->hash_bits;
  s->hash_mask = s->hash_size - 1;
  s->hash_shift = ((s->hash_bits + 3) - 1) / 3;
  s->window = (Bytef *) (*strm->zalloc)(strm->opaque, s->w_size, 2 * (sizeof(Byte)));
  s->prev = (Posf *) (*strm->zalloc)(strm->opaque, s->w_size, sizeof(Pos));
  s->head = (Posf *) (*strm->zalloc)(strm->opaque, s->hash_size, sizeof(Pos));
  s->high_water = 0;
  s->lit_bufsize = 1 << (memLevel + 6);
  s->pending_buf = (uchf *) (*strm->zalloc)(strm->opaque, s->lit_bufsize, 4);
  s->pending_buf_size = ((ulg) s->lit_bufsize) * 4;
  if ((((s->window == 0) || (s->prev == 0)) || (s->head == 0)) || (s->pending_buf == 0))
  {
    s->status = 666;
    strm->msg = z_errmsg[2 - (-4)];
    deflateEnd(strm);
    return -4;
  }
  s->sym_buf = s->pending_buf + s->lit_bufsize;
  s->sym_end = (s->lit_bufsize - 1) * 3;
  s->level = level;
  s->strategy = strategy;
  s->method = (Byte) method;
  return deflateReset(strm);
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
***/


// hint:  ['state_ref is a mutable refrence to gz_statep', 'ret_ref is a mutable refrence to int', 'writ_ref is a mutable refrence to int', 'have_ref is a mutable refrence to unsigned', 'put_ref is a mutable refrence to unsigned', 'strm_ref is a mutable refrence to z_streamp']
int helper_gz_comp_1(gz_statep * const state_ref, int * const ret_ref, int * const writ_ref, unsigned * const have_ref, unsigned * const put_ref, z_streamp * const strm_ref, int flush, unsigned max)
{
  gz_statep state = *state_ref;
  int ret = *ret_ref;
  int writ = *writ_ref;
  unsigned have = *have_ref;
  unsigned put = *put_ref;
  z_streamp strm = *strm_ref;
  if ((strm->avail_out == 0) || ((flush != 0) && ((flush != 4) || (ret == 1))))
  {
    while (strm->next_out > state->x.next)
    {
      put = ((strm->next_out - state->x.next) > ((int) max)) ? (max) : ((unsigned) (strm->next_out - state->x.next));
      writ = write(state->fd, state->x.next, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      state->x.next += writ;
    }

    if (strm->avail_out == 0)
    {
      strm->avail_out = state->size;
      strm->next_out = state->out;
      state->x.next = state->out;
    }
  }
  have = strm->avail_out;
  ret = deflate(strm, flush);
  if (ret == (-2))
  {
    gz_error(state, -2, "internal error: deflate stream corrupt");
    return -1;
  }
  have -= strm->avail_out;
  *state_ref = state;
  *ret_ref = ret;
  *writ_ref = writ;
  *have_ref = have;
  *put_ref = put;
  *strm_ref = strm;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
int deflate(z_streamp strm, int flush)
{
  int old_flush;
  deflate_state *s;
  unsigned int s_idx = 0;
  if ((deflateStateCheck(strm) || (flush > 5)) || (flush < 0))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((strm->next_out == 0) || ((strm->avail_in != 0) && (strm->next_in == 0))) || ((s->status == 666) && (flush != 4)))
  {
    return strm->msg = z_errmsg[2 - (-2)], -2;
  }
  if (strm->avail_out == 0)
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  old_flush = s->last_flush;
  s->last_flush = flush;
  if (s->pending != 0)
  {
    flush_pending(strm);
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
  else
    if (((strm->avail_in == 0) && (((flush * 2) - ((flush > 4) ? (9) : (0))) <= ((old_flush * 2) - ((old_flush > 4) ? (9) : (0))))) && (flush != 4))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 666) && (strm->avail_in != 0))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 42) && (s->wrap == 0))
  {
    s->status = 113;
  }
  if (s->status == 42)
  {
    helper_deflate_1(&strm, s);
  }
  if (((strm->avail_in != 0) || (s->lookahead != 0)) || ((flush != 0) && (s->status != 666)))
  {
    helper_deflate_2(strm, flush, s);
  }
  if (flush != 4)
  {
    return 0;
  }
  if (s->wrap <= 0)
  {
    return 1;
  }
  {
    putShortMSB(s, (uInt) (strm->adler >> 16));
    putShortMSB(s, (uInt) (strm->adler & 0xffff));
  }
  flush_pending(strm);
  if (s->wrap > 0)
  {
    s->wrap = -s->wrap;
  }
  return (s->pending != 0) ? (0) : (1);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
***/


static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


/*** DEPENDENCIES:
int helper_gz_comp_1(gz_statep * const state_ref, int * const ret_ref, int * const writ_ref, unsigned * const have_ref, unsigned * const put_ref, z_streamp * const strm_ref, int flush, unsigned max)
{
  gz_statep state = *state_ref;
  int ret = *ret_ref;
  int writ = *writ_ref;
  unsigned have = *have_ref;
  unsigned put = *put_ref;
  z_streamp strm = *strm_ref;
  if ((strm->avail_out == 0) || ((flush != 0) && ((flush != 4) || (ret == 1))))
  {
    while (strm->next_out > state->x.next)
    {
      put = ((strm->next_out - state->x.next) > ((int) max)) ? (max) : ((unsigned) (strm->next_out - state->x.next));
      writ = write(state->fd, state->x.next, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      state->x.next += writ;
    }

    if (strm->avail_out == 0)
    {
      strm->avail_out = state->size;
      strm->next_out = state->out;
      state->x.next = state->out;
    }
  }
  have = strm->avail_out;
  ret = deflate(strm, flush);
  if (ret == (-2))
  {
    gz_error(state, -2, "internal error: deflate stream corrupt");
    return -1;
  }
  have -= strm->avail_out;
  *state_ref = state;
  *ret_ref = ret;
  *writ_ref = writ;
  *have_ref = have;
  *put_ref = put;
  *strm_ref = strm;
}


----------------------------
int deflateReset(z_streamp strm)
{
  int ret;
  ret = deflateResetKeep(strm);
  if (ret == 0)
  {
    lm_init(strm->state);
  }
  return ret;
}


----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
***/


static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
***/


int gzvprintf(gzFile file, const char *format, va_list va)
{
  int len;
  unsigned left;
  char *next;
  unsigned int next_idx = 0;
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return state->err;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (strm->avail_in == 0)
  {
    strm->next_in = state->in;
  }
  next_idx = (char *) ((state->in + (strm->next_in - state->in)) + strm->avail_in);
  next[(state->size - 1) + next_idx] = 0;
  len = vsnprintf(next, state->size, format, va);
  if (((len == 0) || (((unsigned) len) >= state->size)) || (next[(state->size - 1) + next_idx] != 0))
  {
    return 0;
  }
  strm->avail_in += (unsigned) len;
  state->x.pos += len;
  if (strm->avail_in >= state->size)
  {
    left = strm->avail_in - state->size;
    strm->avail_in = state->size;
    if (gz_comp(state, 0) == (-1))
    {
      return state->err;
    }
    memmove(state->in, state->in + state->size, left);
    strm->next_in = state->in;
    strm->avail_in = left;
  }
  return len;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef z_stream *z_streamp
----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
***/


int gzprintf(gzFile file, const char *format, ...)
{
  va_list va;
  int ret;
  __builtin_va_start(va);
  ret = gzvprintf(file, format, va);
  ;
  return ret;
}


/*** DEPENDENCIES:
int gzvprintf(gzFile file, const char *format, va_list va)
{
  int len;
  unsigned left;
  char *next;
  unsigned int next_idx = 0;
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return state->err;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (strm->avail_in == 0)
  {
    strm->next_in = state->in;
  }
  next_idx = (char *) ((state->in + (strm->next_in - state->in)) + strm->avail_in);
  next[(state->size - 1) + next_idx] = 0;
  len = vsnprintf(next, state->size, format, va);
  if (((len == 0) || (((unsigned) len) >= state->size)) || (next[(state->size - 1) + next_idx] != 0))
  {
    return 0;
  }
  strm->avail_in += (unsigned) len;
  state->x.pos += len;
  if (strm->avail_in >= state->size)
  {
    left = strm->avail_in - state->size;
    strm->avail_in = state->size;
    if (gz_comp(state, 0) == (-1))
    {
      return state->err;
    }
    memmove(state->in, state->in + state->size, left);
    strm->next_in = state->in;
    strm->avail_in = left;
  }
  return len;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


// hint:  ['state_ref is a mutable refrence to gz_statep', 'len_ref is a mutable refrence to z_size_t']
z_size_t helper_gz_write_1(gz_statep * const state_ref, z_size_t * const len_ref, voidpc buf)
{
  gz_statep state = *state_ref;
  z_size_t len = *len_ref;
  if (state->strm.avail_in && (gz_comp(state, 0) == (-1)))
  {
    return 0;
  }
  state->strm.next_in = (Bytef *) buf;
  do
  {
    unsigned n = (unsigned) (-1);
    if (n > len)
    {
      n = (unsigned) len;
    }
    state->strm.avail_in = n;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return 0;
    }
    len -= n;
  }
  while (len);
  *state_ref = state;
  *len_ref = len;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef void *voidp
----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef const void *voidpc
----------------------------
***/


// hint:  ['state_ref is a mutable refrence to gz_statep', 'buf_ref is a mutable refrence to voidpc', 'len_ref is a mutable refrence to z_size_t']
z_size_t helper_gz_write_2(gz_statep * const state_ref, voidpc * const buf_ref, z_size_t * const len_ref)
{
  gz_statep state = *state_ref;
  voidpc buf = *buf_ref;
  z_size_t len = *len_ref;
  do
  {
    unsigned have;
    unsigned copy;
    if (state->strm.avail_in == 0)
    {
      state->strm.next_in = state->in;
    }
    have = (unsigned) ((state->strm.next_in + state->strm.avail_in) - state->in);
    copy = state->size - have;
    if (copy > len)
    {
      copy = (unsigned) len;
    }
    memcpy(state->in + have, buf, copy);
    state->strm.avail_in += copy;
    state->x.pos += copy;
    buf = ((const char *) buf) + copy;
    len -= copy;
    if (len && (gz_comp(state, 0) == (-1)))
    {
      return 0;
    }
  }
  while (len);
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef void *voidp
----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef const void *voidpc
----------------------------
***/


static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef void *voidp
----------------------------
static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
typedef size_t z_size_t
----------------------------
z_size_t helper_gz_write_1(gz_statep * const state_ref, z_size_t * const len_ref, voidpc buf)
{
  gz_statep state = *state_ref;
  z_size_t len = *len_ref;
  if (state->strm.avail_in && (gz_comp(state, 0) == (-1)))
  {
    return 0;
  }
  state->strm.next_in = (Bytef *) buf;
  do
  {
    unsigned n = (unsigned) (-1);
    if (n > len)
    {
      n = (unsigned) len;
    }
    state->strm.avail_in = n;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return 0;
    }
    len -= n;
  }
  while (len);
  *state_ref = state;
  *len_ref = len;
}


----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
typedef const void *voidpc
----------------------------
z_size_t helper_gz_write_2(gz_statep * const state_ref, voidpc * const buf_ref, z_size_t * const len_ref)
{
  gz_statep state = *state_ref;
  voidpc buf = *buf_ref;
  z_size_t len = *len_ref;
  do
  {
    unsigned have;
    unsigned copy;
    if (state->strm.avail_in == 0)
    {
      state->strm.next_in = state->in;
    }
    have = (unsigned) ((state->strm.next_in + state->strm.avail_in) - state->in);
    copy = state->size - have;
    if (copy > len)
    {
      copy = (unsigned) len;
    }
    memcpy(state->in + have, buf, copy);
    state->strm.avail_in += copy;
    state->x.pos += copy;
    buf = ((const char *) buf) + copy;
    len -= copy;
    if (len && (gz_comp(state, 0) == (-1)))
    {
      return 0;
    }
  }
  while (len);
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
}


----------------------------
***/


int gzwrite(gzFile file, voidpc buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -3, "requested length does not fit in int");
    return 0;
  }
  return (int) gz_write(state, buf, len);
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef void *voidp
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef const void *voidpc
----------------------------
***/


int gzflush(gzFile file, int flush)
{
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((flush < 0) || (flush > 4))
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  (void) gz_comp(state, flush);
  return state->err;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
***/


int gzputs(gzFile file, const char *s)
{
  z_size_t len;
  z_size_t put;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  len = strlen(s);
  if ((((int) len) < 0) || (((unsigned) len) != len))
  {
    gz_error(state, -2, "string length does not fit in int");
    return -1;
  }
  put = gz_write(state, s, len);
  return (put < len) ? (-1) : ((int) len);
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


int gzputc(gzFile file, int c)
{
  unsigned have;
  unsigned char buf[1];
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (state->size)
  {
    if (strm->avail_in == 0)
    {
      strm->next_in = state->in;
    }
    have = (unsigned) ((strm->next_in + strm->avail_in) - state->in);
    if (have < state->size)
    {
      state->in[have] = (unsigned char) c;
      strm->avail_in += 1;
      state->x.pos += 1;
      return c & 0xff;
    }
  }
  buf[0] = (unsigned char) c;
  if (gz_write(state, buf, 1) != 1)
  {
    return -1;
  }
  return c & 0xff;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef z_stream *z_streamp
----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
***/


int gzclose_w(gzFile file)
{
  int ret = 0;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 31153)
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      ret = state->err;
    }
  }
  if (gz_comp(state, 4) == (-1))
  {
    ret = state->err;
  }
  if (state->size)
  {
    if (!state->direct)
    {
      (void) deflateEnd(&state->strm);
      free(state->out);
    }
    free(state->in);
  }
  gz_error(state, 0, 0);
  free(state->path);
  if (close(state->fd) == (-1))
  {
    ret = -1;
  }
  free(state);
  return ret;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
int deflateEnd(z_streamp strm)
{
  int status;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  status = strm->state->status;
  {
    if (strm->state->pending_buf)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->pending_buf);
    }
  }
  ;
  {
    if (strm->state->head)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->head);
    }
  }
  ;
  {
    if (strm->state->prev)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->prev);
    }
  }
  ;
  {
    if (strm->state->window)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->window);
    }
  }
  ;
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  return (status == 113) ? (-3) : (0);
}


----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
***/


int gzsetparams(gzFile file, int level, int strategy)
{
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if (((state->mode != 31153) || (state->err != 0)) || state->direct)
  {
    return -2;
  }
  if ((level == state->level) && (strategy == state->strategy))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (state->size)
  {
    if (strm->avail_in && (gz_comp(state, 5) == (-1)))
    {
      return state->err;
    }
    deflateParams(strm, level, strategy);
  }
  state->level = level;
  state->strategy = strategy;
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
int deflateParams(z_streamp strm, int level, int strategy)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  compress_func func;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  if (level == (-1))
  {
    level = 6;
  }
  if ((((level < 0) || (level > 9)) || (strategy < 0)) || (strategy > 4))
  {
    return -2;
  }
  func = configuration_table[s->level].func;
  if (((strategy != s->strategy) || (func != configuration_table[level].func)) && (s->last_flush != (-2)))
  {
    int err = deflate(strm, 5);
    if (err == (-2))
    {
      return err;
    }
    if (strm->avail_in || ((s->strstart - s->block_start) + s->lookahead))
    {
      return -5;
    }
  }
  if (s->level != level)
  {
    helper_deflateParams_1(&level, s);
  }
  s->strategy = strategy;
  return 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef z_stream *z_streamp
----------------------------
static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}


----------------------------
***/


z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_write(state, buf, len) / size) : (0);
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef void *voidp
----------------------------
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef const void *voidpc
----------------------------
***/


