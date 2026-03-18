void bufrelease(struct buf *buf)
{
  if (!buf)
  {
    return;
  }
  free(buf->data);
  free(buf);
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


struct buf *bufnew(size_t unit)
{
  struct buf *ret;
  unsigned int ret_idx = 0;
  ret_idx = malloc(sizeof(struct buf));
  if (ret)
  {
    ret->data = 0;
    ret->size = (ret->asize = 0);
    ret->unit = unit;
  }
  return ret;
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


int bufgrow(struct buf *buf, size_t neosz)
{
  size_t neoasz;
  void *neodata;
  unsigned int neodata_idx = 0;
  assert(buf && buf->unit);
  if (neosz > ((1024 * 1024) * 16))
  {
    return BUF_ENOMEM;
  }
  if (buf->asize >= neosz)
  {
    return BUF_OK;
  }
  neoasz = buf->asize + buf->unit;
  while (neoasz < neosz)
  {
    neoasz += buf->unit;
  }

  neodata_idx = realloc(buf->data, neoasz);
  if (!(&neodata[neodata_idx]))
  {
    return BUF_ENOMEM;
  }
  buf->data = &neodata[neodata_idx];
  buf->asize = neoasz;
  return BUF_OK;
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufputc(struct buf *buf, int c)
{
  assert(buf && buf->unit);
  if (((buf->size + 1) > buf->asize) && (bufgrow(buf, buf->size + 1) < 0))
  {
    return;
  }
  buf->data[buf->size] = c;
  buf->size += 1;
}


/*** DEPENDENCIES:
int bufgrow(struct buf *buf, size_t neosz)
{
  size_t neoasz;
  void *neodata;
  unsigned int neodata_idx = 0;
  assert(buf && buf->unit);
  if (neosz > ((1024 * 1024) * 16))
  {
    return BUF_ENOMEM;
  }
  if (buf->asize >= neosz)
  {
    return BUF_OK;
  }
  neoasz = buf->asize + buf->unit;
  while (neoasz < neosz)
  {
    neoasz += buf->unit;
  }

  neodata_idx = realloc(buf->data, neoasz);
  if (!(&neodata[neodata_idx]))
  {
    return BUF_ENOMEM;
  }
  buf->data = &neodata[neodata_idx];
  buf->asize = neoasz;
  return BUF_OK;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufput(struct buf *buf, const void *data, size_t len)
{
  assert(buf && buf->unit);
  if (((buf->size + len) > buf->asize) && (bufgrow(buf, buf->size + len) < 0))
  {
    return;
  }
  memcpy(buf->data + buf->size, data, len);
  buf->size += len;
}


/*** DEPENDENCIES:
int bufgrow(struct buf *buf, size_t neosz)
{
  size_t neoasz;
  void *neodata;
  unsigned int neodata_idx = 0;
  assert(buf && buf->unit);
  if (neosz > ((1024 * 1024) * 16))
  {
    return BUF_ENOMEM;
  }
  if (buf->asize >= neosz)
  {
    return BUF_OK;
  }
  neoasz = buf->asize + buf->unit;
  while (neoasz < neosz)
  {
    neoasz += buf->unit;
  }

  neodata_idx = realloc(buf->data, neoasz);
  if (!(&neodata[neodata_idx]))
  {
    return BUF_ENOMEM;
  }
  buf->data = &neodata[neodata_idx];
  buf->asize = neoasz;
  return BUF_OK;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


int buftruncate(struct buf *buf, size_t size)
{
  if ((buf->size < size) || (size < 0))
  {
    assert(0);
    return BUF_EINVALIDIDX;
  }
  buf->size = size;
  return BUF_OK;
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufputs(struct buf *buf, const char *str)
{
  bufput(buf, str, strlen(str));
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
void bufput(struct buf *buf, const void *data, size_t len)
{
  assert(buf && buf->unit);
  if (((buf->size + len) > buf->asize) && (bufgrow(buf, buf->size + len) < 0))
  {
    return;
  }
  memcpy(buf->data + buf->size, data, len);
  buf->size += len;
}


----------------------------
***/


int bufprefix(const struct buf *buf, const char *prefix)
{
  size_t i;
  assert(buf && buf->unit);
  for (i = 0; i < buf->size; i += 1)
  {
    if (prefix[i] == 0)
    {
      return 0;
    }
    if (buf->data[i] != prefix[i])
    {
      return buf->data[i] - prefix[i];
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufreset(struct buf *buf)
{
  if (!buf)
  {
    return;
  }
  free(buf->data);
  buf->data = 0;
  buf->size = (buf->asize = 0);
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufslurp(struct buf *buf, size_t len)
{
  assert(buf && buf->unit);
  if (len >= buf->size)
  {
    buf->size = 0;
    return;
  }
  buf->size -= len;
  memmove(buf->data, buf->data + len, buf->size);
}


/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


const char *bufcstr(struct buf *buf)
{
  assert(buf && buf->unit);
  if ((buf->size < buf->asize) && (buf->data[buf->size] == 0))
  {
    return (char *) buf->data;
  }
  if (((buf->size + 1) <= buf->asize) || (bufgrow(buf, buf->size + 1) == 0))
  {
    buf->data[buf->size] = 0;
    return (char *) buf->data;
  }
  return 0;
}


/*** DEPENDENCIES:
int bufgrow(struct buf *buf, size_t neosz)
{
  size_t neoasz;
  void *neodata;
  unsigned int neodata_idx = 0;
  assert(buf && buf->unit);
  if (neosz > ((1024 * 1024) * 16))
  {
    return BUF_ENOMEM;
  }
  if (buf->asize >= neosz)
  {
    return BUF_OK;
  }
  neoasz = buf->asize + buf->unit;
  while (neoasz < neosz)
  {
    neoasz += buf->unit;
  }

  neodata_idx = realloc(buf->data, neoasz);
  if (!(&neodata[neodata_idx]))
  {
    return BUF_ENOMEM;
  }
  buf->data = &neodata[neodata_idx];
  buf->asize = neoasz;
  return BUF_OK;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


void bufprintf(struct buf *buf, const char *fmt, ...)
{
  va_list ap;
  int n;
  assert(buf && buf->unit);
  if ((buf->size >= buf->asize) && (bufgrow(buf, buf->size + 1) < 0))
  {
    return;
  }
  __builtin_va_start(ap);
  n = vsnprintf(((char *) buf->data) + buf->size, buf->asize - buf->size, fmt, ap);
  ;
  if (n < 0)
  {
    return;
  }
  if (((size_t) n) >= (buf->asize - buf->size))
  {
    if (bufgrow(buf, (buf->size + n) + 1) < 0)
    {
      return;
    }
    __builtin_va_start(ap);
    n = vsnprintf(((char *) buf->data) + buf->size, buf->asize - buf->size, fmt, ap);
    ;
  }
  if (n < 0)
  {
    return;
  }
  buf->size += n;
}


/*** DEPENDENCIES:
int bufgrow(struct buf *buf, size_t neosz)
{
  size_t neoasz;
  void *neodata;
  unsigned int neodata_idx = 0;
  assert(buf && buf->unit);
  if (neosz > ((1024 * 1024) * 16))
  {
    return BUF_ENOMEM;
  }
  if (buf->asize >= neosz)
  {
    return BUF_OK;
  }
  neoasz = buf->asize + buf->unit;
  while (neoasz < neosz)
  {
    neoasz += buf->unit;
  }

  neodata_idx = realloc(buf->data, neoasz);
  if (!(&neodata[neodata_idx]))
  {
    return BUF_ENOMEM;
  }
  buf->data = &neodata[neodata_idx];
  buf->asize = neoasz;
  return BUF_OK;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


