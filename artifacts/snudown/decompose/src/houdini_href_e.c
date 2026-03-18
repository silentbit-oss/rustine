void houdini_escape_href(struct buf *ob, const uint8_t *src, size_t size)
{
  static const char hex_chars[] = "0123456789ABCDEF";
  size_t i = 0;
  size_t org;
  char hex_str[3];
  bufgrow(ob, (size * 12) / 10);
  hex_str[0] = '%';
  while (i < size)
  {
    org = i;
    while ((i < size) && (HREF_SAFE[src[i]] == 1))
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
    if (HREF_SAFE[src[i]] == 2)
    {
      i += 1;
      continue;
    }
    switch (src[i])
    {
      case '&':
      {
        bufput(ob, "&amp;", (sizeof("&amp;")) - 1);
        break;
      }

      case '\'':
      {
        bufput(ob, "&#x27;", (sizeof("&#x27;")) - 1);
        break;
      }

      default:
      {
        hex_str[1] = hex_chars[(src[i] >> 4) & 0xF];
        hex_str[2] = hex_chars[src[i] & 0xF];
        bufput(ob, hex_str, 3);
      }

    }

    i += 1;
  }

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
static const char HREF_SAFE[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
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


