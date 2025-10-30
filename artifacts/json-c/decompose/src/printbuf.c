struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
/*** DEPENDENCIES:
***/


void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


/*** DEPENDENCIES:
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


struct printbuf *printbuf_new(void)
{
  struct printbuf *p;
  unsigned int p_idx = 0;
  p_idx = (struct printbuf *) calloc(1, sizeof(struct printbuf));
  if (!(&p[p_idx]))
  {
    return 0;
  }
  p->size = 32;
  p->bpos = 0;
  if (!(p->buf = (char *) malloc(p->size)))
  {
    free(p);
    return 0;
  }
  p->buf[0] = '\0';
  return p;
}


/*** DEPENDENCIES:
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}


/*** DEPENDENCIES:
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


static int printbuf_extend(struct printbuf *p, int min_size)
{
  char *t;
  unsigned int t_idx = 0;
  int new_size;
  if (p->size >= min_size)
  {
    return 0;
  }
  if (min_size > (2147483647 - 8))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size > (2147483647 / 2))
  {
    new_size = min_size + 8;
  }
  else
  {
    new_size = p->size * 2;
    if (new_size < (min_size + 8))
    {
      new_size = min_size + 8;
    }
  }
  if (!(t_idx = (char *) realloc(p->buf, new_size)))
  {
    return -1;
  }
  p->size = new_size;
  p->buf = &t[t_idx];
  return 0;
}


/*** DEPENDENCIES:
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


/*** DEPENDENCIES:
static int printbuf_extend(struct printbuf *p, int min_size)
{
  char *t;
  unsigned int t_idx = 0;
  int new_size;
  if (p->size >= min_size)
  {
    return 0;
  }
  if (min_size > (2147483647 - 8))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size > (2147483647 / 2))
  {
    new_size = min_size + 8;
  }
  else
  {
    new_size = p->size * 2;
    if (new_size < (min_size + 8))
    {
      new_size = min_size + 8;
    }
  }
  if (!(t_idx = (char *) realloc(p->buf, new_size)))
  {
    return -1;
  }
  p->size = new_size;
  p->buf = &t[t_idx];
  return 0;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len)
{
  int size_needed;
  if (offset == (-1))
  {
    offset = pb->bpos;
  }
  if (((len < 0) || (offset < (-1))) || (len > (2147483647 - offset)))
  {
    errno = EFBIG;
    return -1;
  }
  size_needed = offset + len;
  if (pb->size < size_needed)
  {
    if (printbuf_extend(pb, size_needed) < 0)
    {
      return -1;
    }
  }
  if (pb->bpos < offset)
  {
    memset(pb->buf + pb->bpos, '\0', offset - pb->bpos);
  }
  memset(pb->buf + offset, charvalue, len);
  if (pb->bpos < size_needed)
  {
    pb->bpos = size_needed;
  }
  return 0;
}


/*** DEPENDENCIES:
static int printbuf_extend(struct printbuf *p, int min_size)
{
  char *t;
  unsigned int t_idx = 0;
  int new_size;
  if (p->size >= min_size)
  {
    return 0;
  }
  if (min_size > (2147483647 - 8))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size > (2147483647 / 2))
  {
    new_size = min_size + 8;
  }
  else
  {
    new_size = p->size * 2;
    if (new_size < (min_size + 8))
    {
      new_size = min_size + 8;
    }
  }
  if (!(t_idx = (char *) realloc(p->buf, new_size)))
  {
    return -1;
  }
  p->size = new_size;
  p->buf = &t[t_idx];
  return 0;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


int sprintbuf(struct printbuf *p, const char *msg, ...)
{
  va_list ap;
  char *t;
  int size;
  char buf[128];
  __builtin_va_start(ap);
  size = vsnprintf(buf, 128, msg, ap);
  ;
  if ((size < 0) || (size > 127))
  {
    __builtin_va_start(ap);
    if ((size = vasprintf(&t, msg, ap)) < 0)
    {
      ;
      return -1;
    }
    ;
    size = printbuf_memappend(p, t, size);
    free(t);
  }
  else
  {
    size = printbuf_memappend(p, buf, size);
  }
  return size;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


