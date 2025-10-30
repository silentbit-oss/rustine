uLong compressBound(uLong sourceLen)
{
  return (((sourceLen + (sourceLen >> 12)) + (sourceLen >> 14)) + (sourceLen >> 25)) + 13;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
***/


int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)
{
  z_stream stream;
  int err;
  const uInt max = (uInt) (-1);
  uLong left;
  left = *destLen;
  *destLen = 0;
  stream.zalloc = (alloc_func) 0;
  stream.zfree = (free_func) 0;
  stream.opaque = (voidpf) 0;
  err = deflateInit_(&stream, level, "1.3-optipng", (int) (sizeof(z_stream)));
  if (err != 0)
  {
    return err;
  }
  stream.next_out = dest;
  stream.avail_out = 0;
  stream.next_in = (const Bytef *) source;
  stream.avail_in = 0;
  do
  {
    if (stream.avail_out == 0)
    {
      stream.avail_out = (left > ((uLong) max)) ? (max) : ((uInt) left);
      left -= stream.avail_out;
    }
    if (stream.avail_in == 0)
    {
      stream.avail_in = (sourceLen > ((uLong) max)) ? (max) : ((uInt) sourceLen);
      sourceLen -= stream.avail_in;
    }
    err = deflate(&stream, (sourceLen) ? (0) : (4));
  }
  while (err == 0);
  *destLen = stream.total_out;
  deflateEnd(&stream);
  return (err == 1) ? (0) : (err);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
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
typedef uLong uLongf
----------------------------
typedef unsigned char Byte
----------------------------
***/


int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
{
  return compress2(dest, destLen, source, sourceLen, -1);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)
{
  z_stream stream;
  int err;
  const uInt max = (uInt) (-1);
  uLong left;
  left = *destLen;
  *destLen = 0;
  stream.zalloc = (alloc_func) 0;
  stream.zfree = (free_func) 0;
  stream.opaque = (voidpf) 0;
  err = deflateInit_(&stream, level, "1.3-optipng", (int) (sizeof(z_stream)));
  if (err != 0)
  {
    return err;
  }
  stream.next_out = dest;
  stream.avail_out = 0;
  stream.next_in = (const Bytef *) source;
  stream.avail_in = 0;
  do
  {
    if (stream.avail_out == 0)
    {
      stream.avail_out = (left > ((uLong) max)) ? (max) : ((uInt) left);
      left -= stream.avail_out;
    }
    if (stream.avail_in == 0)
    {
      stream.avail_in = (sourceLen > ((uLong) max)) ? (max) : ((uInt) sourceLen);
      sourceLen -= stream.avail_in;
    }
    err = deflate(&stream, (sourceLen) ? (0) : (4));
  }
  while (err == 0);
  *destLen = stream.total_out;
  deflateEnd(&stream);
  return (err == 1) ? (0) : (err);
}


----------------------------
typedef Byte Bytef
----------------------------
typedef uLong uLongf
----------------------------
typedef unsigned char Byte
----------------------------
***/


