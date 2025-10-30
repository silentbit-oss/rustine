void houdini_escape_html0(struct buf *ob, const uint8_t *src, size_t size, int secure)
{
  size_t i = 0;
  size_t org;
  size_t esc = 0;
  bufgrow(ob, (size * 12) / 10);
  while (i < size)
  {
    org = i;
    while ((i < size) && ((esc = HTML_ESCAPE_TABLE[src[i]]) == 0))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    if ((src[i] == '/') && (!secure))
    {
      bufputc(ob, '/');
    }
    else
      if (HTML_ESCAPE_TABLE[src[i]] == 7)
    {
    }
    else
    {
      bufputs(ob, HTML_ESCAPES[esc]);
    }
    i += 1;
  }

}


/*** DEPENDENCIES:
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
void bufputs(struct buf *buf, const char *str)
{
  bufput(buf, str, strlen(str));
}


----------------------------
static const char HTML_ESCAPE_TABLE[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 1, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
static const char *HTML_ESCAPES[] = {"", "&quot;", "&amp;", "&#39;", "&#47;", "&lt;", "&gt;", ""}
----------------------------
***/


void houdini_escape_html(struct buf *ob, const uint8_t *src, size_t size)
{
  houdini_escape_html0(ob, src, size, 1);
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
void houdini_escape_html0(struct buf *ob, const uint8_t *src, size_t size, int secure)
{
  size_t i = 0;
  size_t org;
  size_t esc = 0;
  bufgrow(ob, (size * 12) / 10);
  while (i < size)
  {
    org = i;
    while ((i < size) && ((esc = HTML_ESCAPE_TABLE[src[i]]) == 0))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    if ((src[i] == '/') && (!secure))
    {
      bufputc(ob, '/');
    }
    else
      if (HTML_ESCAPE_TABLE[src[i]] == 7)
    {
    }
    else
    {
      bufputs(ob, HTML_ESCAPES[esc]);
    }
    i += 1;
  }

}


----------------------------
***/


