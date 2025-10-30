int gzclose_r(gzFile file)
{
  int ret;
  int err;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 7247)
  {
    return -2;
  }
  if (state->size)
  {
    inflateEnd(&state->strm);
    free(state->out);
    free(state->in);
  }
  err = (state->err == (-5)) ? (-5) : (0);
  gz_error(state, 0, 0);
  free(state->path);
  ret = close(state->fd);
  free(state);
  return (ret) ? (-1) : (err);
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
typedef struct gzFile_s *gzFile
----------------------------
int inflateEnd(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
  }
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  ;
  return 0;
}


----------------------------
***/


static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
  }
  return 0;
}


/*** DEPENDENCIES:
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
***/


static int gz_avail(gz_statep state)
{
  unsigned got;
  z_streamp strm = &state->strm;
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if (state->eof == 0)
  {
    if (strm->avail_in)
    {
      unsigned char *p = state->in;
      unsigned int p_idx = 0;
      const unsigned char *q = strm->next_in;
      unsigned int q_idx = 0;
      unsigned n = strm->avail_in;
      do
      {
        p[p_idx] = q[q_idx];
        q_idx += 1;
        p_idx += 1;
      }
      while (--n);
    }
    if (gz_load(state, state->in + strm->avail_in, state->size - strm->avail_in, &got) == (-1))
    {
      return -1;
    }
    strm->avail_in += got;
    strm->next_in = state->in;
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
static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
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


// hint:  ['state_ref is a mutable refrence to gz_statep']
int helper_gz_look_1(gz_statep * const state_ref)
{
  gz_statep state = *state_ref;
  state->in = (unsigned char *) malloc(state->want);
  state->out = (unsigned char *) malloc(state->want << 1);
  if ((state->in == 0) || (state->out == 0))
  {
    free(state->out);
    free(state->in);
    gz_error(state, -4, "out of memory");
    return -1;
  }
  state->size = state->want;
  state->strm.zalloc = 0;
  state->strm.zfree = 0;
  state->strm.opaque = 0;
  state->strm.avail_in = 0;
  state->strm.next_in = 0;
  if (inflateInit2_(&state->strm, 15 + 16, "1.3-optipng", (int) (sizeof(z_stream))) != 0)
  {
    free(state->out);
    free(state->in);
    state->size = 0;
    gz_error(state, -4, "out of memory");
    return -1;
  }
  *state_ref = state;
}


/*** DEPENDENCIES:
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
int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size)
{
  int ret;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((version == 0) || (version[0] != "1.3-optipng"[0])) || (stream_size != ((int) (sizeof(z_stream)))))
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
  state_idx = (struct inflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(struct inflate_state));
  if ((&state[state_idx]) == 0)
  {
    return -4;
  }
  ;
  strm->state = (struct internal_state *) state;
  state->strm = strm;
  state->window = 0;
  state->mode = HEAD;
  ret = inflateReset2(strm, windowBits);
  if (ret != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state);
    strm->state = 0;
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
typedef gz_state *gz_statep
----------------------------
***/


static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    helper_gz_look_1(&state);
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
}


/*** DEPENDENCIES:
int inflateReset(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  state->wsize = 0;
  state->whave = 0;
  state->wnext = 0;
  return inflateResetKeep(strm);
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
static int gz_avail(gz_statep state)
{
  unsigned got;
  z_streamp strm = &state->strm;
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if (state->eof == 0)
  {
    if (strm->avail_in)
    {
      unsigned char *p = state->in;
      unsigned int p_idx = 0;
      const unsigned char *q = strm->next_in;
      unsigned int q_idx = 0;
      unsigned n = strm->avail_in;
      do
      {
        p[p_idx] = q[q_idx];
        q_idx += 1;
        p_idx += 1;
      }
      while (--n);
    }
    if (gz_load(state, state->in + strm->avail_in, state->size - strm->avail_in, &got) == (-1))
    {
      return -1;
    }
    strm->avail_in += got;
    strm->next_in = state->in;
  }
  return 0;
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
int helper_gz_look_1(gz_statep * const state_ref)
{
  gz_statep state = *state_ref;
  state->in = (unsigned char *) malloc(state->want);
  state->out = (unsigned char *) malloc(state->want << 1);
  if ((state->in == 0) || (state->out == 0))
  {
    free(state->out);
    free(state->in);
    gz_error(state, -4, "out of memory");
    return -1;
  }
  state->size = state->want;
  state->strm.zalloc = 0;
  state->strm.zfree = 0;
  state->strm.opaque = 0;
  state->strm.avail_in = 0;
  state->strm.next_in = 0;
  if (inflateInit2_(&state->strm, 15 + 16, "1.3-optipng", (int) (sizeof(z_stream))) != 0)
  {
    free(state->out);
    free(state->in);
    state->size = 0;
    gz_error(state, -4, "out of memory");
    return -1;
  }
  *state_ref = state;
}


----------------------------
***/


static int gz_decomp(gz_statep state)
{
  int ret = 0;
  unsigned had;
  z_streamp strm = &state->strm;
  had = strm->avail_out;
  do
  {
    if ((strm->avail_in == 0) && (gz_avail(state) == (-1)))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      gz_error(state, -5, "unexpected end of file");
      break;
    }
    ret = inflate(strm, 0);
    if ((ret == (-2)) || (ret == 2))
    {
      gz_error(state, -2, "internal error: inflate stream corrupt");
      return -1;
    }
    if (ret == (-4))
    {
      gz_error(state, -4, "out of memory");
      return -1;
    }
    if (ret == (-3))
    {
      gz_error(state, -3, (strm->msg == 0) ? ("compressed data error") : (strm->msg));
      return -1;
    }
  }
  while (strm->avail_out && (ret != 1));
  state->x.have = had - strm->avail_out;
  state->x.next = strm->next_out - state->x.have;
  if (ret == 1)
  {
    state->how = 0;
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
static int gz_avail(gz_statep state)
{
  unsigned got;
  z_streamp strm = &state->strm;
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if (state->eof == 0)
  {
    if (strm->avail_in)
    {
      unsigned char *p = state->in;
      unsigned int p_idx = 0;
      const unsigned char *q = strm->next_in;
      unsigned int q_idx = 0;
      unsigned n = strm->avail_in;
      do
      {
        p[p_idx] = q[q_idx];
        q_idx += 1;
        p_idx += 1;
      }
      while (--n);
    }
    if (gz_load(state, state->in + strm->avail_in, state->size - strm->avail_in, &got) == (-1))
    {
      return -1;
    }
    strm->avail_in += got;
    strm->next_in = state->in;
  }
  return 0;
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
int inflate(z_streamp strm, int flush)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *next;
  unsigned int next_idx = 0;
  unsigned char *put;
  unsigned int put_idx = 0;
  unsigned have;
  unsigned left;
  unsigned long hold;
  unsigned bits;
  unsigned in;
  unsigned out;
  unsigned copy;
  unsigned char *from;
  unsigned int from_idx = 0;
  code here;
  code last;
  unsigned len;
  int ret;
  static const unsigned short order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  if ((inflateStateCheck(strm) || (strm->next_out == 0)) || ((strm->next_in == 0) && (strm->avail_in != 0)))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->mode == TYPE)
  {
    state->mode = TYPEDO;
  }
  do
  {
    put_idx = strm->next_out;
    left = strm->avail_out;
    next_idx = strm->next_in;
    have = strm->avail_in;
    hold = state->hold;
    bits = state->bits;
  }
  while (0);
  in = have;
  out = left;
  ret = 0;
  for (;;)
  {
    helper_inflate_1(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, &out, &copy, &from_idx, &here, &last, &len, &ret, flush, state, next, put, from, order);
  }

  inf_leave:
  do
  {
    strm->next_out = &put[put_idx];
    strm->avail_out = left;
    strm->next_in = &next[next_idx];
    strm->avail_in = have;
    state->hold = hold;
    state->bits = bits;
  }
  while (0);

  if (state->wsize || (((out != strm->avail_out) && (state->mode < BAD)) && ((state->mode < CHECK) || (flush != 4))))
  {
    if (updatewindow(strm, strm->next_out, out - strm->avail_out))
    {
      state->mode = MEM;
      return -4;
    }
  }
  in -= strm->avail_in;
  out -= strm->avail_out;
  strm->total_in += in;
  strm->total_out += out;
  state->total += out;
  if ((state->wrap & 4) && out)
  {
    strm->adler = (state->check = adler32(state->check, strm->next_out - out, out));
  }
  strm->data_type = ((((int) state->bits) + ((state->last) ? (64) : (0))) + ((state->mode == TYPE) ? (128) : (0))) + (((state->mode == LEN_) || (state->mode == COPY_)) ? (256) : (0));
  if ((((in == 0) && (out == 0)) || (flush == 4)) && (ret == 0))
  {
    ret = -5;
  }
  return ret;
}


----------------------------
***/


static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
      {
        if (gz_look(state) == (-1))
        {
          return -1;
        }
        if (state->how == 0)
        {
          return 0;
        }
        break;
      }

      case 1:
      {
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
        {
          return -1;
        }
        state->x.next = state->out;
        return 0;
      }

      case 2:
      {
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
        {
          return -1;
        }
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
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
static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    helper_gz_look_1(&state);
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
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
static int gz_decomp(gz_statep state)
{
  int ret = 0;
  unsigned had;
  z_streamp strm = &state->strm;
  had = strm->avail_out;
  do
  {
    if ((strm->avail_in == 0) && (gz_avail(state) == (-1)))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      gz_error(state, -5, "unexpected end of file");
      break;
    }
    ret = inflate(strm, 0);
    if ((ret == (-2)) || (ret == 2))
    {
      gz_error(state, -2, "internal error: inflate stream corrupt");
      return -1;
    }
    if (ret == (-4))
    {
      gz_error(state, -4, "out of memory");
      return -1;
    }
    if (ret == (-3))
    {
      gz_error(state, -3, (strm->msg == 0) ? ("compressed data error") : (strm->msg));
      return -1;
    }
  }
  while (strm->avail_out && (ret != 1));
  state->x.have = had - strm->avail_out;
  state->x.next = strm->next_out - state->x.have;
  if (ret == 1)
  {
    state->how = 0;
  }
  return 0;
}


----------------------------
***/


// hint:  ['state_ref is a mutable refrence to gz_statep', 'buf_ref is a mutable refrence to voidp', 'len_ref is a mutable refrence to z_size_t', 'got_ref is a mutable refrence to z_size_t', 'n_ref is a mutable refrence to unsigned']
z_size_t helper_gz_read_1(gz_statep * const state_ref, voidp * const buf_ref, z_size_t * const len_ref, z_size_t * const got_ref, unsigned * const n_ref)
{
  gz_statep state = *state_ref;
  voidp buf = *buf_ref;
  z_size_t len = *len_ref;
  z_size_t got = *got_ref;
  unsigned n = *n_ref;
  n = (unsigned) (-1);
  if (n > len)
  {
    n = (unsigned) len;
  }
  if (state->x.have)
  {
    if (state->x.have < n)
    {
      n = state->x.have;
    }
    memcpy(buf, state->x.next, n);
    state->x.next += n;
    state->x.have -= n;
  }
  else
    if (state->eof && (state->strm.avail_in == 0))
  {
    state->past = 1;
    break;
  }
  else
    if ((state->how == 0) || (n < (state->size << 1)))
  {
    if (gz_fetch(state) == (-1))
    {
      return 0;
    }
    continue;
  }
  else
    if (state->how == 1)
  {
    if (gz_load(state, (unsigned char *) buf, n, &n) == (-1))
    {
      return 0;
    }
  }
  else
  {
    state->strm.avail_out = n;
    state->strm.next_out = (unsigned char *) buf;
    if (gz_decomp(state) == (-1))
    {
      return 0;
    }
    n = state->x.have;
    state->x.have = 0;
  }
  len -= n;
  buf = ((char *) buf) + n;
  got += n;
  state->x.pos += n;
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
  *got_ref = got;
  *n_ref = n;
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
static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
  }
  return 0;
}


----------------------------
typedef size_t z_size_t
----------------------------
static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
      {
        if (gz_look(state) == (-1))
        {
          return -1;
        }
        if (state->how == 0)
        {
          return 0;
        }
        break;
      }

      case 1:
      {
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
        {
          return -1;
        }
        state->x.next = state->out;
        return 0;
      }

      case 2:
      {
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
        {
          return -1;
        }
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
  return 0;
}


----------------------------
static int gz_decomp(gz_statep state)
{
  int ret = 0;
  unsigned had;
  z_streamp strm = &state->strm;
  had = strm->avail_out;
  do
  {
    if ((strm->avail_in == 0) && (gz_avail(state) == (-1)))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      gz_error(state, -5, "unexpected end of file");
      break;
    }
    ret = inflate(strm, 0);
    if ((ret == (-2)) || (ret == 2))
    {
      gz_error(state, -2, "internal error: inflate stream corrupt");
      return -1;
    }
    if (ret == (-4))
    {
      gz_error(state, -4, "out of memory");
      return -1;
    }
    if (ret == (-3))
    {
      gz_error(state, -3, (strm->msg == 0) ? ("compressed data error") : (strm->msg));
      return -1;
    }
  }
  while (strm->avail_out && (ret != 1));
  state->x.have = had - strm->avail_out;
  state->x.next = strm->next_out - state->x.have;
  if (ret == 1)
  {
    state->how = 0;
  }
  return 0;
}


----------------------------
***/


static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
      {
        if (gz_look(state) == (-1))
        {
          return -1;
        }
        if (state->how == 0)
        {
          return 0;
        }
        break;
      }

      case 1:
      {
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
        {
          return -1;
        }
        state->x.next = state->out;
        return 0;
      }

      case 2:
      {
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
        {
          return -1;
        }
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
  return 0;
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
typedef gz_state *gz_statep
----------------------------
***/


static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    helper_gz_read_1(&state, &buf, &len, &got, &n);
  }
  while (len);
  return got;
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
z_size_t helper_gz_read_1(gz_statep * const state_ref, voidp * const buf_ref, z_size_t * const len_ref, z_size_t * const got_ref, unsigned * const n_ref)
{
  gz_statep state = *state_ref;
  voidp buf = *buf_ref;
  z_size_t len = *len_ref;
  z_size_t got = *got_ref;
  unsigned n = *n_ref;
  n = (unsigned) (-1);
  if (n > len)
  {
    n = (unsigned) len;
  }
  if (state->x.have)
  {
    if (state->x.have < n)
    {
      n = state->x.have;
    }
    memcpy(buf, state->x.next, n);
    state->x.next += n;
    state->x.have -= n;
  }
  else
    if (state->eof && (state->strm.avail_in == 0))
  {
    state->past = 1;
    break;
  }
  else
    if ((state->how == 0) || (n < (state->size << 1)))
  {
    if (gz_fetch(state) == (-1))
    {
      return 0;
    }
    continue;
  }
  else
    if (state->how == 1)
  {
    if (gz_load(state, (unsigned char *) buf, n, &n) == (-1))
    {
      return 0;
    }
  }
  else
  {
    state->strm.avail_out = n;
    state->strm.next_out = (unsigned char *) buf;
    if (gz_decomp(state) == (-1))
    {
      return 0;
    }
    n = state->x.have;
    state->x.have = 0;
  }
  len -= n;
  buf = ((char *) buf) + n;
  got += n;
  state->x.pos += n;
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
  *got_ref = got;
  *n_ref = n;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}


----------------------------
typedef size_t z_size_t
----------------------------
***/


int gzgetc(gzFile file)
{
  unsigned char buf[1];
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->x.have)
  {
    state->x.have -= 1;
    state->x.pos += 1;
    return *(state->x.next++);
  }
  return (gz_read(state, buf, 1) < 1) ? (-1) : (buf[0]);
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    helper_gz_read_1(&state, &buf, &len, &got, &n);
  }
  while (len);
  return got;
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
typedef gz_state *gz_statep
----------------------------
***/


int gzgetc_(gzFile file)
{
  return gzgetc(file);
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
int gzgetc(gzFile file)
{
  unsigned char buf[1];
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->x.have)
  {
    state->x.have -= 1;
    state->x.pos += 1;
    return *(state->x.next++);
  }
  return (gz_read(state, buf, 1) < 1) ? (-1) : (buf[0]);
}


----------------------------
***/


// hint:  ['buf_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to unsigned', 'n_ref is a mutable refrence to unsigned', 'eol_idx_ref is a mutable refrence to unsigned int', 'state_ref is a mutable refrence to gz_statep']
char *helper_gzgets_1(unsigned int * const buf_idx_ref, unsigned * const left_ref, unsigned * const n_ref, unsigned int * const eol_idx_ref, gz_statep * const state_ref, char * const buf, unsigned char * const eol)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned left = *left_ref;
  unsigned n = *n_ref;
  unsigned int eol_idx = *eol_idx_ref;
  gz_statep state = *state_ref;
  do
  {
    if ((state->x.have == 0) && (gz_fetch(state) == (-1)))
    {
      return 0;
    }
    if (state->x.have == 0)
    {
      state->past = 1;
      break;
    }
    n = (state->x.have > left) ? (left) : (state->x.have);
    eol_idx = (unsigned char *) memchr(state->x.next, '\n', n);
    if ((&eol[eol_idx]) != 0)
    {
      n = ((unsigned) ((&eol[eol_idx]) - state->x.next)) + 1;
    }
    memcpy(buf, state->x.next, n);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    left -= n;
    buf_idx += n;
  }
  while (left && ((&eol[eol_idx]) == 0));
  *buf_idx_ref = buf_idx;
  *left_ref = left;
  *n_ref = n;
  *eol_idx_ref = eol_idx;
  *state_ref = state;
}


/*** DEPENDENCIES:
static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
      {
        if (gz_look(state) == (-1))
        {
          return -1;
        }
        if (state->how == 0)
        {
          return 0;
        }
        break;
      }

      case 1:
      {
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
        {
          return -1;
        }
        state->x.next = state->out;
        return 0;
      }

      case 2:
      {
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
        {
          return -1;
        }
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
  return 0;
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
typedef gz_state *gz_statep
----------------------------
***/


int gzdirect(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  return state->direct;
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    helper_gz_look_1(&state);
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
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
typedef gz_state *gz_statep
----------------------------
***/


char *gzgets(gzFile file, char *buf, int len)
{
  unsigned int buf_idx = 0;
  unsigned left;
  unsigned n;
  char *str;
  unsigned int str_idx = 0;
  unsigned char *eol;
  unsigned int eol_idx = 0;
  gz_statep state;
  if (((file == 0) || ((&buf[buf_idx]) == 0)) || (len < 1))
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  str_idx = &buf[buf_idx];
  left = ((unsigned) len) - 1;
  if (left)
  {
    helper_gzgets_1(&buf_idx, &left, &n, &eol_idx, &state, buf, eol);
  }
  if ((&buf[buf_idx]) == (&str[str_idx]))
  {
    return 0;
  }
  buf[0 + buf_idx] = 0;
  return str;
}


/*** DEPENDENCIES:
char *helper_gzgets_1(unsigned int * const buf_idx_ref, unsigned * const left_ref, unsigned * const n_ref, unsigned int * const eol_idx_ref, gz_statep * const state_ref, char * const buf, unsigned char * const eol)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned left = *left_ref;
  unsigned n = *n_ref;
  unsigned int eol_idx = *eol_idx_ref;
  gz_statep state = *state_ref;
  do
  {
    if ((state->x.have == 0) && (gz_fetch(state) == (-1)))
    {
      return 0;
    }
    if (state->x.have == 0)
    {
      state->past = 1;
      break;
    }
    n = (state->x.have > left) ? (left) : (state->x.have);
    eol_idx = (unsigned char *) memchr(state->x.next, '\n', n);
    if ((&eol[eol_idx]) != 0)
    {
      n = ((unsigned) ((&eol[eol_idx]) - state->x.next)) + 1;
    }
    memcpy(buf, state->x.next, n);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    left -= n;
    buf_idx += n;
  }
  while (left && ((&eol[eol_idx]) == 0));
  *buf_idx_ref = buf_idx;
  *left_ref = left;
  *n_ref = n;
  *eol_idx_ref = eol_idx;
  *state_ref = state;
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
typedef gz_state *gz_statep
----------------------------
static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


int gzread(gzFile file, voidp buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -2, "request does not fit in an int");
    return -1;
  }
  len = (unsigned) gz_read(state, buf, len);
  if (((len == 0) && (state->err != 0)) && (state->err != (-5)))
  {
    return -1;
  }
  return (int) len;
}


/*** DEPENDENCIES:
static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    helper_gz_read_1(&state, &buf, &len, &got, &n);
  }
  while (len);
  return got;
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
typedef struct gzFile_s *gzFile
----------------------------
***/


int gzungetc(int c, gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (c < 0)
  {
    return -1;
  }
  if (state->x.have == 0)
  {
    state->x.have = 1;
    state->x.next = (state->out + (state->size << 1)) - 1;
    state->x.next[0] = (unsigned char) c;
    state->x.pos -= 1;
    state->past = 0;
    return c;
  }
  if (state->x.have == (state->size << 1))
  {
    gz_error(state, -3, "out of room to push characters");
    return -1;
  }
  if (state->x.next == state->out)
  {
    unsigned char *src = state->out + state->x.have;
    unsigned int src_idx = 0;
    unsigned char *dest = state->out + (state->size << 1);
    unsigned int dest_idx = 0;
    while ((&src[src_idx]) > state->out)
    {
      src_idx -= 1;
      dest_idx -= 1;
      dest[dest_idx] = src[src_idx];
    }

    state->x.next = &dest[dest_idx];
  }
  state->x.have += 1;
  state->x.next -= 1;
  state->x.next[0] = (unsigned char) c;
  state->x.pos -= 1;
  state->past = 0;
  return c;
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
static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    helper_gz_look_1(&state);
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_read(state, buf, len) / size) : (0);
}


/*** DEPENDENCIES:
static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    helper_gz_read_1(&state, &buf, &len, &got, &n);
  }
  while (len);
  return got;
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
typedef size_t z_size_t
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


