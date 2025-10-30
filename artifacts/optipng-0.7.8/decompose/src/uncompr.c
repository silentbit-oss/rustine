int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen)
{
  unsigned int dest_idx = 0;
  z_stream stream;
  int err;
  const uInt max = (uInt) (-1);
  uLong len;
  uLong left;
  Byte buf[1];
  len = *sourceLen;
  if (*destLen)
  {
    left = *destLen;
    *destLen = 0;
  }
  else
  {
    left = 1;
    dest_idx = buf;
  }
  stream.next_in = (const Bytef *) source;
  stream.avail_in = 0;
  stream.zalloc = (alloc_func) 0;
  stream.zfree = (free_func) 0;
  stream.opaque = (voidpf) 0;
  err = inflateInit_(&stream, "1.3-optipng", (int) (sizeof(z_stream)));
  if (err != 0)
  {
    return err;
  }
  stream.next_out = &dest[dest_idx];
  stream.avail_out = 0;
  do
  {
    if (stream.avail_out == 0)
    {
      stream.avail_out = (left > ((uLong) max)) ? (max) : ((uInt) left);
      left -= stream.avail_out;
    }
    if (stream.avail_in == 0)
    {
      stream.avail_in = (len > ((uLong) max)) ? (max) : ((uInt) len);
      len -= stream.avail_in;
    }
    err = inflate(&stream, 0);
  }
  while (err == 0);
  *sourceLen -= len + stream.avail_in;
  if ((&dest[dest_idx]) != buf)
  {
    *destLen = stream.total_out;
  }
  else
    if (stream.total_out && (err == (-5)))
  {
    left = 1;
  }
  inflateEnd(&stream);
  return (err == 1) ? (0) : ((err == 2) ? (-3) : (((err == (-5)) && (left + stream.avail_out)) ? (-3) : (err)));
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
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
typedef uLong uLongf
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
typedef unsigned char Byte
----------------------------
***/


int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
{
  return uncompress2(dest, destLen, source, &sourceLen);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen)
{
  unsigned int dest_idx = 0;
  z_stream stream;
  int err;
  const uInt max = (uInt) (-1);
  uLong len;
  uLong left;
  Byte buf[1];
  len = *sourceLen;
  if (*destLen)
  {
    left = *destLen;
    *destLen = 0;
  }
  else
  {
    left = 1;
    dest_idx = buf;
  }
  stream.next_in = (const Bytef *) source;
  stream.avail_in = 0;
  stream.zalloc = (alloc_func) 0;
  stream.zfree = (free_func) 0;
  stream.opaque = (voidpf) 0;
  err = inflateInit_(&stream, "1.3-optipng", (int) (sizeof(z_stream)));
  if (err != 0)
  {
    return err;
  }
  stream.next_out = &dest[dest_idx];
  stream.avail_out = 0;
  do
  {
    if (stream.avail_out == 0)
    {
      stream.avail_out = (left > ((uLong) max)) ? (max) : ((uInt) left);
      left -= stream.avail_out;
    }
    if (stream.avail_in == 0)
    {
      stream.avail_in = (len > ((uLong) max)) ? (max) : ((uInt) len);
      len -= stream.avail_in;
    }
    err = inflate(&stream, 0);
  }
  while (err == 0);
  *sourceLen -= len + stream.avail_in;
  if ((&dest[dest_idx]) != buf)
  {
    *destLen = stream.total_out;
  }
  else
    if (stream.total_out && (err == (-5)))
  {
    left = 1;
  }
  inflateEnd(&stream);
  return (err == 1) ? (0) : ((err == 2) ? (-3) : (((err == (-5)) && (left + stream.avail_out)) ? (-3) : (err)));
}


----------------------------
typedef uLong uLongf
----------------------------
typedef unsigned char Byte
----------------------------
***/


