void test_gzio(const char *fname, Byte *uncompr, uLong uncomprLen)
{
  fprintf(stderr, "NO_GZCOMPRESS -- gz* functions cannot compress\n");
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_compress(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  err = compress(compr, &comprLen, (const Bytef *) hello, len);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "compress", err);
      exit(1);
    }
  }
  ;
  strcpy((char *) uncompr, "garbage");
  err = uncompress(uncompr, &uncomprLen, compr, comprLen);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "uncompress", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad uncompress\n");
    exit(1);
  }
  else
  {
    printf("uncompress(): %s\n", (char *) uncompr);
  }
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
----------------------------
int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
{
  return uncompress2(dest, destLen, source, &sourceLen);
}


----------------------------
int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
{
  return compress2(dest, destLen, source, sourceLen, -1);
}


----------------------------
typedef unsigned char Byte
----------------------------
***/


// hint:  ['err_ref is a mutable refrence to int']
void helper_test_dict_inflate_1(int * const err_ref, z_stream d_stream)
{
  int err = *err_ref;
  err = inflate(&d_stream, 0);
  if (err == 1)
  {
    break;
  }
  if (err == 2)
  {
    if (d_stream.adler != dictId)
    {
      fprintf(stderr, "unexpected dictionary");
      exit(1);
    }
    err = inflateSetDictionary(&d_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  }
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate with dict", err);
      exit(1);
    }
  }
  ;
  *err_ref = err;
}


/*** DEPENDENCIES:
int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  unsigned long dictid;
  int ret;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if ((state->wrap != 0) && (state->mode != DICT))
  {
    return -2;
  }
  if (state->mode == DICT)
  {
    dictid = adler32(0L, 0, 0);
    dictid = adler32(dictid, dictionary, dictLength);
    if (dictid != state->check)
    {
      return -3;
    }
  }
  ret = updatewindow(strm, dictionary + dictLength, dictLength);
  if (ret)
  {
    state->mode = MEM;
    return -4;
  }
  state->havedict = 1;
  ;
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
static uLong dictId
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
static const char dictionary[] = "hello"
----------------------------
***/


void test_large_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  for (;;)
  {
    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt) uncomprLen;
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "large inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (d_stream.total_out != ((2 * uncomprLen) + (uncomprLen / 2)))
  {
    fprintf(stderr, "bad large inflate: %ld\n", d_stream.total_out);
    exit(1);
  }
  else
  {
    printf("large_inflate(): OK\n");
  }
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
static free_func zfree = (free_func) 0
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
int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
  return inflateInit2_(strm, 15, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  while ((c_stream.total_in != len) && (c_stream.total_out < comprLen))
  {
    c_stream.avail_in = (c_stream.avail_out = 1);
    err = deflate(&c_stream, 0);
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  for (;;)
  {
    c_stream.avail_out = 1;
    err = deflate(&c_stream, 4);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
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
static free_func zfree = (free_func) 0
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
int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 0;
  d_stream.next_out = uncompr;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  while ((d_stream.total_out < uncomprLen) && (d_stream.total_in < comprLen))
  {
    d_stream.avail_in = (d_stream.avail_out = 1);
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate\n");
    exit(1);
  }
  else
  {
    printf("inflate(): %s\n", (char *) uncompr);
  }
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
----------------------------
static free_func zfree = (free_func) 0
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
int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
  return inflateInit2_(strm, 15, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_large_deflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  if (c_stream.avail_in != 0)
  {
    fprintf(stderr, "deflate not greedy\n");
    exit(1);
  }
  deflateParams(&c_stream, 0, 0);
  c_stream.next_in = compr;
  c_stream.avail_in = ((uInt) uncomprLen) / 2;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  deflateParams(&c_stream, 9, 1);
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
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
static free_func zfree = (free_func) 0
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
int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_sync(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 2;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  err = inflate(&d_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate", err);
      exit(1);
    }
  }
  ;
  d_stream.avail_in = ((uInt) comprLen) - 2;
  err = inflateSync(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateSync", err);
      exit(1);
    }
  }
  ;
  err = inflate(&d_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "inflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  printf("after inflateSync(): hel%s\n", (char *) uncompr);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
static free_func zfree = (free_func) 0
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
int inflateSync(z_streamp strm)
{
  unsigned len;
  int flags;
  unsigned long in;
  unsigned long out;
  unsigned char buf[4];
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if ((strm->avail_in == 0) && (state->bits < 8))
  {
    return -5;
  }
  if (state->mode != SYNC)
  {
    helper_inflateSync_1(&len, buf, state);
  }
  len = syncsearch(&state->have, strm->next_in, strm->avail_in);
  strm->avail_in -= len;
  strm->next_in += len;
  strm->total_in += len;
  if (state->have != 4)
  {
    return -3;
  }
  if (state->flags == (-1))
  {
    state->wrap = 0;
  }
  else
    state->wrap &= ~4;
  flags = state->flags;
  in = strm->total_in;
  out = strm->total_out;
  inflateReset(strm);
  strm->total_in = in;
  strm->total_out = out;
  state->flags = flags;
  state->mode = TYPE;
  return 0;
}


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
int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
  return inflateInit2_(strm, 15, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_dict_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  for (;;)
  {
    helper_test_dict_inflate_1(&err, d_stream);
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate with dict\n");
    exit(1);
  }
  else
  {
    printf("inflate with dictionary: %s\n", (char *) uncompr);
  }
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
----------------------------
static free_func zfree = (free_func) 0
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
void helper_test_dict_inflate_1(int * const err_ref, z_stream d_stream)
{
  int err = *err_ref;
  err = inflate(&d_stream, 0);
  if (err == 1)
  {
    break;
  }
  if (err == 2)
  {
    if (d_stream.adler != dictId)
    {
      fprintf(stderr, "unexpected dictionary");
      exit(1);
    }
    err = inflateSetDictionary(&d_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  }
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate with dict", err);
      exit(1);
    }
  }
  ;
  *err_ref = err;
}


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
int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
  return inflateInit2_(strm, 15, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_flush(Byte *compr, uLong *comprLen)
{
  z_stream c_stream;
  int err;
  uInt len = ((uInt) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  c_stream.avail_in = 3;
  c_stream.avail_out = (uInt) (*comprLen);
  err = deflate(&c_stream, 3);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  compr[3] += 1;
  c_stream.avail_in = len - 3;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
  *comprLen = c_stream.total_out;
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
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
static free_func zfree = (free_func) 0
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
typedef unsigned int uInt
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
int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}


----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


void test_dict_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 9, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  err = deflateSetDictionary(&c_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateSetDictionary", err);
      exit(1);
    }
  }
  ;
  dictId = c_stream.adler;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.avail_in = ((uInt) strlen(hello)) + 1;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


/*** DEPENDENCIES:
static const char hello[] = "hello, hello!"
----------------------------
typedef unsigned long uLong
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
static free_func zfree = (free_func) 0
----------------------------
int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength)
{
  unsigned int dictionary_idx = 0;
  deflate_state *s;
  unsigned int s_idx = 0;
  uInt str;
  uInt n;
  int wrap;
  unsigned avail;
  const unsigned char *next;
  unsigned int next_idx = 0;
  if (deflateStateCheck(strm) || ((&dictionary[dictionary_idx]) == 0))
  {
    return -2;
  }
  s_idx = strm->state;
  wrap = s->wrap;
  if (((wrap == 2) || ((wrap == 1) && (s->status != 42))) || s->lookahead)
  {
    return -2;
  }
  if (wrap == 1)
  {
    strm->adler = adler32(strm->adler, dictionary, dictLength);
  }
  s->wrap = 0;
  if (dictLength >= s->w_size)
  {
    if (wrap == 0)
    {
      do
      {
        s->head[s->hash_size - 1] = 0;
        memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
      }
      while (0);
      s->strstart = 0;
      s->block_start = 0L;
      s->insert = 0;
    }
    dictionary_idx += dictLength - s->w_size;
    dictLength = s->w_size;
  }
  avail = strm->avail_in;
  next_idx = strm->next_in;
  strm->avail_in = dictLength;
  strm->next_in = (const Bytef *) dictionary;
  fill_window(s);
  while (s->lookahead >= 3)
  {
    str = s->strstart;
    n = s->lookahead - (3 - 1);
    do
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[(str + 3) - 1]) & s->hash_mask;
      s->prev[str & s->w_mask] = s->head[s->ins_h];
      s->head[s->ins_h] = (Pos) str;
      str += 1;
    }
    while (--n);
    s->strstart = str;
    s->lookahead = 3 - 1;
    fill_window(s);
  }

  s->strstart += s->lookahead;
  s->block_start = (long) s->strstart;
  s->insert = s->lookahead;
  s->lookahead = 0;
  s->match_length = (s->prev_length = 3 - 1);
  s->match_available = 0;
  strm->next_in = &next[next_idx];
  strm->avail_in = avail;
  s->wrap = wrap;
  return 0;
}


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
static uLong dictId
----------------------------
int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}


----------------------------
static const char dictionary[] = "hello"
----------------------------
static alloc_func zalloc = (alloc_func) 0
----------------------------
typedef unsigned char Byte
----------------------------
***/


int main(int argc, char *argv[])
{
  Byte *compr;
  unsigned int compr_idx = 0;
  Byte *uncompr;
  unsigned int uncompr_idx = 0;
  uLong uncomprLen = 20000;
  uLong comprLen = 3 * uncomprLen;
  static const char *myVersion = "1.3-optipng";
  if (zlibVersion()[0] != myVersion[0])
  {
    fprintf(stderr, "incompatible zlib version\n");
    exit(1);
  }
  else
    if (strcmp(zlibVersion(), "1.3-optipng") != 0)
  {
    fprintf(stderr, "warning: different zlib version linked: %s\n", zlibVersion());
  }
  printf("zlib version %s = 0x%04x, compile flags = 0x%lx\n", "1.3-optipng", 0x130f, zlibCompileFlags());
  compr_idx = (Byte *) calloc((uInt) comprLen, 1);
  uncompr_idx = (Byte *) calloc((uInt) uncomprLen, 1);
  if (((&compr[compr_idx]) == 0) || ((&uncompr[uncompr_idx]) == 0))
  {
    printf("out of memory\n");
    exit(1);
  }
  test_compress(compr, comprLen, uncompr, uncomprLen);
  test_gzio((argc > 1) ? (argv[1]) : ("foo.gz"), uncompr, uncomprLen);
  test_deflate(compr, comprLen);
  test_inflate(compr, comprLen, uncompr, uncomprLen);
  test_large_deflate(compr, comprLen, uncompr, uncomprLen);
  test_large_inflate(compr, comprLen, uncompr, uncomprLen);
  test_flush(compr, &comprLen);
  test_sync(compr, comprLen, uncompr, uncomprLen);
  comprLen = 3 * uncomprLen;
  test_dict_deflate(compr, comprLen);
  test_dict_inflate(compr, comprLen, uncompr, uncomprLen);
  free(compr);
  free(uncompr);
  return 0;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
uLong zlibCompileFlags(void)
{
  uLong flags;
  flags = 0;
  switch ((int) (sizeof(uInt)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1;
      break;
    }

    case 8:
    {
      flags += 2;
      break;
    }

    default:
    {
      flags += 3;
    }

  }

  switch ((int) (sizeof(uLong)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 2;
      break;
    }

    case 8:
    {
      flags += 2 << 2;
      break;
    }

    default:
    {
      flags += 3 << 2;
    }

  }

  switch ((int) (sizeof(voidpf)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 4;
      break;
    }

    case 8:
    {
      flags += 2 << 4;
      break;
    }

    default:
    {
      flags += 3 << 4;
    }

  }

  switch ((int) (sizeof(off_t)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 6;
      break;
    }

    case 8:
    {
      flags += 2 << 6;
      break;
    }

    default:
    {
      flags += 3 << 6;
    }

  }

  flags += 1L << 16;
  flags += 1L << 17;
  return flags;
}


----------------------------
void test_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  while ((c_stream.total_in != len) && (c_stream.total_out < comprLen))
  {
    c_stream.avail_in = (c_stream.avail_out = 1);
    err = deflate(&c_stream, 0);
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  for (;;)
  {
    c_stream.avail_out = 1;
    err = deflate(&c_stream, 4);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


----------------------------
void test_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 0;
  d_stream.next_out = uncompr;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  while ((d_stream.total_out < uncomprLen) && (d_stream.total_in < comprLen))
  {
    d_stream.avail_in = (d_stream.avail_out = 1);
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate\n");
    exit(1);
  }
  else
  {
    printf("inflate(): %s\n", (char *) uncompr);
  }
}


----------------------------
void test_dict_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  for (;;)
  {
    helper_test_dict_inflate_1(&err, d_stream);
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate with dict\n");
    exit(1);
  }
  else
  {
    printf("inflate with dictionary: %s\n", (char *) uncompr);
  }
}


----------------------------
void test_large_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  for (;;)
  {
    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt) uncomprLen;
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "large inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (d_stream.total_out != ((2 * uncomprLen) + (uncomprLen / 2)))
  {
    fprintf(stderr, "bad large inflate: %ld\n", d_stream.total_out);
    exit(1);
  }
  else
  {
    printf("large_inflate(): OK\n");
  }
}


----------------------------
void test_large_deflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  if (c_stream.avail_in != 0)
  {
    fprintf(stderr, "deflate not greedy\n");
    exit(1);
  }
  deflateParams(&c_stream, 0, 0);
  c_stream.next_in = compr;
  c_stream.avail_in = ((uInt) uncomprLen) / 2;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  deflateParams(&c_stream, 9, 1);
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


----------------------------
void test_flush(Byte *compr, uLong *comprLen)
{
  z_stream c_stream;
  int err;
  uInt len = ((uInt) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  c_stream.avail_in = 3;
  c_stream.avail_out = (uInt) (*comprLen);
  err = deflate(&c_stream, 3);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  compr[3] += 1;
  c_stream.avail_in = len - 3;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
  *comprLen = c_stream.total_out;
}


----------------------------
const char *zlibVersion(void)
{
  return "1.3-optipng";
}


----------------------------
void test_compress(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  err = compress(compr, &comprLen, (const Bytef *) hello, len);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "compress", err);
      exit(1);
    }
  }
  ;
  strcpy((char *) uncompr, "garbage");
  err = uncompress(uncompr, &uncomprLen, compr, comprLen);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "uncompress", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad uncompress\n");
    exit(1);
  }
  else
  {
    printf("uncompress(): %s\n", (char *) uncompr);
  }
}


----------------------------
void test_dict_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 9, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  err = deflateSetDictionary(&c_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateSetDictionary", err);
      exit(1);
    }
  }
  ;
  dictId = c_stream.adler;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.avail_in = ((uInt) strlen(hello)) + 1;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}


----------------------------
void test_gzio(const char *fname, Byte *uncompr, uLong uncomprLen)
{
  fprintf(stderr, "NO_GZCOMPRESS -- gz* functions cannot compress\n");
}


----------------------------
void test_sync(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 2;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  err = inflate(&d_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate", err);
      exit(1);
    }
  }
  ;
  d_stream.avail_in = ((uInt) comprLen) - 2;
  err = inflateSync(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateSync", err);
      exit(1);
    }
  }
  ;
  err = inflate(&d_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "inflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  printf("after inflateSync(): hel%s\n", (char *) uncompr);
}


----------------------------
typedef unsigned char Byte
----------------------------
***/


