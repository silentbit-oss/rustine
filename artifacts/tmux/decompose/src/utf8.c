static int utf8_width(wchar_t wc)
{
  int width;
  width = wcwidth(wc);
  if ((width < 0) || (width > 0xff))
  {
    log_debug("Unicode %04lx, wcwidth() %d", (long) wc, width);
    if (width < 0)
    {
      return 1;
    }
    return -1;
  }
  return width;
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


enum utf8_state utf8_split(wchar_t wc, struct utf8_data *ud)
{
  char s[MB_LEN_MAX];
  int slen;
  slen = wctomb(s, wc);
  if ((slen <= 0) || (slen > ((int) (sizeof(ud->data)))))
  {
    return UTF8_ERROR;
  }
  memcpy(ud->data, s, slen);
  ud->size = slen;
  ud->width = utf8_width(wc);
  return UTF8_DONE;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
static int utf8_width(wchar_t wc)
{
  int width;
  width = wcwidth(wc);
  if ((width < 0) || (width > 0xff))
  {
    log_debug("Unicode %04lx, wcwidth() %d", (long) wc, width);
    if (width < 0)
    {
      return 1;
    }
    return -1;
  }
  return width;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


char *utf8_tocstr(struct utf8_data *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  dst_idx = 0;
  n = 0;
  for (; src->size != 0; src_idx += 1)
  {
    dst_idx = xreallocarray(dst_idx, n + src->size, 1);
    memcpy((&dst[dst_idx]) + n, src->data, src->size);
    n += src->size;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, 1);
  dst[n + dst_idx] = '\0';
  return dst;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


enum utf8_state utf8_combine(const struct utf8_data *ud, wchar_t *wc)
{
  switch (mbtowc(wc, ud->data, ud->size))
  {
    case -1:
    {
      log_debug("UTF-8 %.*s, mbtowc() %d", (int) ud->size, ud->data, errno);
      mbtowc(0, 0, MB_CUR_MAX);
      return UTF8_ERROR;
    }

    case 0:
    {
      return UTF8_ERROR;
    }

    default:
    {
      return UTF8_DONE;
    }

  }

}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


/*** DEPENDENCIES:
enum utf8_state utf8_combine(const struct utf8_data *ud, wchar_t *wc)
{
  switch (mbtowc(wc, ud->data, ud->size))
  {
    case -1:
    {
      log_debug("UTF-8 %.*s, mbtowc() %d", (int) ud->size, ud->data, errno);
      mbtowc(0, 0, MB_CUR_MAX);
      return UTF8_ERROR;
    }

    case 0:
    {
      return UTF8_ERROR;
    }

    default:
    {
      return UTF8_DONE;
    }

  }

}


----------------------------
void fatalx(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s", msg) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
static int utf8_width(wchar_t wc)
{
  int width;
  width = wcwidth(wc);
  if ((width < 0) || (width > 0xff))
  {
    log_debug("Unicode %04lx, wcwidth() %d", (long) wc, width);
    if (width < 0)
    {
      return 1;
    }
    return -1;
  }
  return width;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
***/


char *utf8_rtrimcstr(const char *s, u_int width)
{
  struct utf8_data *tmp;
  unsigned int tmp_idx = 0;
  struct utf8_data *next;
  unsigned int next_idx = 0;
  struct utf8_data *end;
  unsigned int end_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  u_int at;
  tmp_idx = utf8_fromcstr(s);
  for (end_idx = &tmp[tmp_idx]; end->size != 0; end_idx += 1)
  {
    ;
  }

  if ((&end[end_idx]) == (&tmp[tmp_idx]))
  {
    free(tmp);
    return xstrdup("");
  }
  next_idx = (&end[end_idx]) - 1;
  at = 0;
  for (;;)
  {
    if ((at + next->width) > width)
    {
      next_idx += 1;
      break;
    }
    at += next->width;
    if ((&next[next_idx]) == (&tmp[tmp_idx]))
    {
      break;
    }
    next_idx -= 1;
  }

  out_idx = utf8_tocstr(next);
  free(tmp);
  return out;
}


/*** DEPENDENCIES:
char *utf8_tocstr(struct utf8_data *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  dst_idx = 0;
  n = 0;
  for (; src->size != 0; src_idx += 1)
  {
    dst_idx = xreallocarray(dst_idx, n + src->size, 1);
    memcpy((&dst[dst_idx]) + n, src->data, src->size);
    n += src->size;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, 1);
  dst[n + dst_idx] = '\0';
  return dst;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
***/


char *utf8_trimcstr(const char *s, u_int width)
{
  struct utf8_data *tmp;
  unsigned int tmp_idx = 0;
  struct utf8_data *next;
  unsigned int next_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  u_int at;
  tmp_idx = utf8_fromcstr(s);
  at = 0;
  for (next_idx = &tmp[tmp_idx]; next->size != 0; next_idx += 1)
  {
    if ((at + next->width) > width)
    {
      next->size = 0;
      break;
    }
    at += next->width;
  }

  out_idx = utf8_tocstr(tmp);
  free(tmp);
  return out;
}


/*** DEPENDENCIES:
char *utf8_tocstr(struct utf8_data *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  dst_idx = 0;
  n = 0;
  for (; src->size != 0; src_idx += 1)
  {
    dst_idx = xreallocarray(dst_idx, n + src->size, 1);
    memcpy((&dst[dst_idx]) + n, src->data, src->size);
    n += src->size;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, 1);
  dst[n + dst_idx] = '\0';
  return dst;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
}


----------------------------
***/


void utf8_copy(struct utf8_data *to, const struct utf8_data *from)
{
  u_int i;
  memcpy(to, from, sizeof(*to));
  for (i = to->size; i < (sizeof(to->data)); i += 1)
  {
    to->data[i] = '\0';
  }

}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


int utf8_strvis(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  struct utf8_data ud;
  const char *start;
  unsigned int start_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  size_t i;
  start_idx = &dst[dst_idx];
  end_idx = (&src[src_idx]) + len;
  while ((&src[src_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((++(&src[src_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        for (i = 0; i < ud.size; i += 1)
        {
          dst[dst_idx] = ud.data[i];
          dst_idx += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((&src[src_idx]) < ((&end[end_idx]) - 1))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, src[1 + src_idx]);
    }
    else
      if ((&src[src_idx]) < (&end[end_idx]))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, '\0');
    }
    src_idx += 1;
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


----------------------------
***/


int utf8_stravis(char **dst, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  buf_idx = xreallocarray(0, 4, strlen(src) + 1);
  len = utf8_strvis(buf, src, strlen(src), flag);
  *dst = xrealloc(buf, len + 1);
  return len;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
int utf8_strvis(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  struct utf8_data ud;
  const char *start;
  unsigned int start_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  size_t i;
  start_idx = &dst[dst_idx];
  end_idx = (&src[src_idx]) + len;
  while ((&src[src_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((++(&src[src_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        for (i = 0; i < ud.size; i += 1)
        {
          dst[dst_idx] = ud.data[i];
          dst_idx += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((&src[src_idx]) < ((&end[end_idx]) - 1))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, src[1 + src_idx]);
    }
    else
      if ((&src[src_idx]) < (&end[end_idx]))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, '\0');
    }
    src_idx += 1;
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


int utf8_isvalid(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data ud;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  end_idx = (&s[s_idx]) + strlen(s);
  while ((&s[s_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((++(&s[s_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        continue;
      }
      return 0;
    }
    if ((s[s_idx] < 0x20) || (s[s_idx] > 0x7e))
    {
      return 0;
    }
    s_idx += 1;
  }

  return 1;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


size_t utf8_strlen(const struct utf8_data *s)
{
  size_t i;
  for (i = 0; s[i].size != 0; i += 1)
  {
    ;
  }

  return i;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


u_int utf8_strwidth(const struct utf8_data *s, ssize_t n)
{
  ssize_t i;
  u_int width;
  width = 0;
  for (i = 0; s[i].size != 0; i += 1)
  {
    if ((n != (-1)) && (n == i))
    {
      break;
    }
    width += s[i].width;
  }

  return width;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


char *utf8_sanitize(const char *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  struct utf8_data ud;
  u_int i;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        dst_idx = xreallocarray(dst_idx, n + ud.width, sizeof(*dst_idx));
        for (i = 0; i < ud.width; i += 1)
        {
          dst[n + dst_idx] = '_';
          n += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((src[src_idx] > 0x1f) && (src[src_idx] < 0x7f))
    {
      dst[n + dst_idx] = src[src_idx];
      n += 1;
    }
    else
      dst[n + dst_idx] = '_';
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx] = '\0';
  return dst;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
***/


u_int utf8_cstrwidth(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data tmp;
  u_int width;
  enum utf8_state more;
  width = 0;
  while (s[s_idx] != '\0')
  {
    if ((more = utf8_open(&tmp, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((*(++(&s[s_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&tmp, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        width += tmp.width;
        continue;
      }
      s_idx -= tmp.have;
    }
    if ((s[s_idx] > 0x1f) && (s[s_idx] != 0x7f))
    {
      width += 1;
    }
    s_idx += 1;
  }

  return width;
}


/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


char *utf8_padcstr(const char *s, u_int width)
{
  size_t slen;
  char *out;
  unsigned int out_idx = 0;
  u_int n;
  u_int i;
  n = utf8_cstrwidth(s);
  if (n >= width)
  {
    return xstrdup(s);
  }
  slen = strlen(s);
  out_idx = xmalloc((slen + 1) + (width - n));
  memcpy(out, s, slen);
  for (i = n; i < width; i += 1)
  {
    out[slen + out_idx] = ' ';
    slen += 1;
  }

  out[slen + out_idx] = '\0';
  return out;
}


/*** DEPENDENCIES:
u_int utf8_cstrwidth(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data tmp;
  u_int width;
  enum utf8_state more;
  width = 0;
  while (s[s_idx] != '\0')
  {
    if ((more = utf8_open(&tmp, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((*(++(&s[s_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&tmp, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        width += tmp.width;
        continue;
      }
      s_idx -= tmp.have;
    }
    if ((s[s_idx] > 0x1f) && (s[s_idx] != 0x7f))
    {
      width += 1;
    }
    s_idx += 1;
  }

  return width;
}


----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
***/


