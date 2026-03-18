// hint:  ['link_end_ref is a mutable refrence to size_t']
void helper_autolink_delim_1(size_t * const link_end_ref, uint8_t * const data)
{
  size_t link_end = *link_end_ref;
  uint8_t c = data[link_end - 1];
  if (c == 0)
  {
    break;
  }
  if (strchr("?!.,", c) != 0)
  {
    link_end -= 1;
  }
  else
    if (c == ';')
  {
    size_t new_end = link_end - 2;
    while ((new_end > 0) && isalpha(data[new_end]))
    {
      new_end -= 1;
    }

    if ((new_end < (link_end - 2)) && (data[new_end] == '&'))
    {
      link_end = new_end;
    }
    else
      link_end--;
    link_end -= 1;
  }
  else
    break;
  *link_end_ref = link_end;
}


/*** DEPENDENCIES:
***/


static size_t autolink_delim(uint8_t *data, size_t link_end, size_t max_rewind, size_t size)
{
  uint8_t cclose;
  uint8_t copen = 0;
  size_t i;
  for (i = 0; i < link_end; i += 1)
  {
    if (data[i] == '<')
    {
      link_end = i;
      break;
    }
  }

  while (link_end > 0)
  {
    helper_autolink_delim_1(&link_end, data);
  }

  if (link_end == 0)
  {
    return 0;
  }
  cclose = data[link_end - 1];
  switch (cclose)
  {
    case '"':
    {
      copen = '"';
      break;
    }

    case '\'':
    {
      copen = '\'';
      break;
    }

    case ')':
    {
      copen = '(';
      break;
    }

    case ']':
    {
      copen = '[';
      break;
    }

    case '}':
    {
      copen = '{';
      break;
    }

  }

  if (copen != 0)
  {
    size_t closing = 0;
    size_t opening = 0;
    size_t i = 0;
    while (i < link_end)
    {
      if (data[i] == copen)
      {
        opening += 1;
      }
      else
        if (data[i] == cclose)
      {
        closing += 1;
      }
      i += 1;
    }

    if (closing != opening)
    {
      link_end -= 1;
    }
  }
  return link_end;
}


/*** DEPENDENCIES:
void helper_autolink_delim_1(size_t * const link_end_ref, uint8_t * const data)
{
  size_t link_end = *link_end_ref;
  uint8_t c = data[link_end - 1];
  if (c == 0)
  {
    break;
  }
  if (strchr("?!.,", c) != 0)
  {
    link_end -= 1;
  }
  else
    if (c == ';')
  {
    size_t new_end = link_end - 2;
    while ((new_end > 0) && isalpha(data[new_end]))
    {
      new_end -= 1;
    }

    if ((new_end < (link_end - 2)) && (data[new_end] == '&'))
    {
      link_end = new_end;
    }
    else
      link_end--;
    link_end -= 1;
  }
  else
    break;
  *link_end_ref = link_end;
}


----------------------------
***/


size_t sd_autolink__email(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags)
{
  size_t link_end;
  size_t rewind;
  int nb = 0;
  int np = 0;
  for (rewind = 0; rewind < max_rewind; rewind += 1)
  {
    uint8_t c = data[(-rewind) - 1];
    if (c == 0)
    {
      break;
    }
    if (isalnum(c))
    {
      continue;
    }
    if (strchr(".+-_", c) != 0)
    {
      continue;
    }
    break;
  }

  if (rewind == 0)
  {
    return 0;
  }
  for (link_end = 0; link_end < size; link_end += 1)
  {
    uint8_t c = data[link_end];
    if (isalnum(c))
    {
      continue;
    }
    if (c == '@')
    {
      nb += 1;
    }
    else
      if ((c == '.') && (link_end < (size - 1)))
    {
      np += 1;
    }
    else
      if ((c != '-') && (c != '_'))
    {
      break;
    }
  }

  if (((link_end < 2) || (nb != 1)) || (np == 0))
  {
    return 0;
  }
  link_end = autolink_delim(data, link_end, max_rewind, size);
  if (link_end == 0)
  {
    return 0;
  }
  bufput(link, data - rewind, link_end + rewind);
  *rewind_p = rewind;
  return link_end;
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
static size_t autolink_delim(uint8_t *data, size_t link_end, size_t max_rewind, size_t size)
{
  uint8_t cclose;
  uint8_t copen = 0;
  size_t i;
  for (i = 0; i < link_end; i += 1)
  {
    if (data[i] == '<')
    {
      link_end = i;
      break;
    }
  }

  while (link_end > 0)
  {
    helper_autolink_delim_1(&link_end, data);
  }

  if (link_end == 0)
  {
    return 0;
  }
  cclose = data[link_end - 1];
  switch (cclose)
  {
    case '"':
    {
      copen = '"';
      break;
    }

    case '\'':
    {
      copen = '\'';
      break;
    }

    case ')':
    {
      copen = '(';
      break;
    }

    case ']':
    {
      copen = '[';
      break;
    }

    case '}':
    {
      copen = '{';
      break;
    }

  }

  if (copen != 0)
  {
    size_t closing = 0;
    size_t opening = 0;
    size_t i = 0;
    while (i < link_end)
    {
      if (data[i] == copen)
      {
        opening += 1;
      }
      else
        if (data[i] == cclose)
      {
        closing += 1;
      }
      i += 1;
    }

    if (closing != opening)
    {
      link_end -= 1;
    }
  }
  return link_end;
}


----------------------------
***/


static size_t check_domain(uint8_t *data, size_t size, int allow_short)
{
  size_t i;
  size_t np = 0;
  if (!isalnum(data[0]))
  {
    return 0;
  }
  for (i = 1; i < (size - 1); i += 1)
  {
    if (data[i] == '.')
    {
      np += 1;
    }
    else
      if ((!isalnum(data[i])) && (data[i] != '-'))
    {
      break;
    }
  }

  if (allow_short)
  {
    return i;
  }
  else
  {
    return (np) ? (i) : (0);
  }
}


/*** DEPENDENCIES:
***/


size_t sd_autolink__www(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags)
{
  size_t link_end;
  if (((max_rewind > 0) && (!ispunct(data[-1]))) && (!isspace(data[-1])))
  {
    return 0;
  }
  if ((size < 4) || (memcmp(data, "www.", strlen("www.")) != 0))
  {
    return 0;
  }
  link_end = check_domain(data, size, 0);
  if (link_end == 0)
  {
    return 0;
  }
  while ((link_end < size) && (!isspace(data[link_end])))
  {
    link_end += 1;
  }

  link_end = autolink_delim(data, link_end, max_rewind, size);
  if (link_end == 0)
  {
    return 0;
  }
  bufput(link, data, link_end);
  *rewind_p = 0;
  return (int) link_end;
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
static size_t autolink_delim(uint8_t *data, size_t link_end, size_t max_rewind, size_t size)
{
  uint8_t cclose;
  uint8_t copen = 0;
  size_t i;
  for (i = 0; i < link_end; i += 1)
  {
    if (data[i] == '<')
    {
      link_end = i;
      break;
    }
  }

  while (link_end > 0)
  {
    helper_autolink_delim_1(&link_end, data);
  }

  if (link_end == 0)
  {
    return 0;
  }
  cclose = data[link_end - 1];
  switch (cclose)
  {
    case '"':
    {
      copen = '"';
      break;
    }

    case '\'':
    {
      copen = '\'';
      break;
    }

    case ')':
    {
      copen = '(';
      break;
    }

    case ']':
    {
      copen = '[';
      break;
    }

    case '}':
    {
      copen = '{';
      break;
    }

  }

  if (copen != 0)
  {
    size_t closing = 0;
    size_t opening = 0;
    size_t i = 0;
    while (i < link_end)
    {
      if (data[i] == copen)
      {
        opening += 1;
      }
      else
        if (data[i] == cclose)
      {
        closing += 1;
      }
      i += 1;
    }

    if (closing != opening)
    {
      link_end -= 1;
    }
  }
  return link_end;
}


----------------------------
static size_t check_domain(uint8_t *data, size_t size, int allow_short)
{
  size_t i;
  size_t np = 0;
  if (!isalnum(data[0]))
  {
    return 0;
  }
  for (i = 1; i < (size - 1); i += 1)
  {
    if (data[i] == '.')
    {
      np += 1;
    }
    else
      if ((!isalnum(data[i])) && (data[i] != '-'))
    {
      break;
    }
  }

  if (allow_short)
  {
    return i;
  }
  else
  {
    return (np) ? (i) : (0);
  }
}


----------------------------
***/


static int check_reddit_autolink_prefix(const uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, char prefix_char)
{
  if (((size < 2) || (max_rewind < 1)) || (data[-1] != prefix_char))
  {
    return 0;
  }
  if (max_rewind > 1)
  {
    const char boundary = data[-2];
    if (boundary == '/')
    {
      return 2;
    }
    else
      if (ispunct(boundary) || isspace(boundary))
    {
      return 1;
    }
    else
      return 0;
  }
  else
    if (max_lookbehind > 2)
  {
    if ((data[-2] == '/') && (data[-3] == '\\'))
    {
      return 0;
    }
  }
  return 1;
}


/*** DEPENDENCIES:
***/


size_t sd_autolink__username(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash)
{
  size_t link_end;
  size_t rewind;
  if (size < 3)
  {
    return 0;
  }
  rewind = check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size, 'u');
  if (!rewind)
  {
    return 0;
  }
  link_end = strlen("/");
  if (((!isalnum(data[link_end])) && (data[link_end] != '_')) && (data[link_end] != '-'))
  {
    return 0;
  }
  link_end += 1;
  while ((link_end < size) && (((isalnum(data[link_end]) || (data[link_end] == '_')) || (data[link_end] == '/')) || (data[link_end] == '-')))
  {
    link_end += 1;
  }

  bufput(link, data - rewind, link_end + rewind);
  *no_slash = rewind == 1;
  *rewind_p = rewind;
  return link_end;
}


/*** DEPENDENCIES:
static int check_reddit_autolink_prefix(const uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, char prefix_char)
{
  if (((size < 2) || (max_rewind < 1)) || (data[-1] != prefix_char))
  {
    return 0;
  }
  if (max_rewind > 1)
  {
    const char boundary = data[-2];
    if (boundary == '/')
    {
      return 2;
    }
    else
      if (ispunct(boundary) || isspace(boundary))
    {
      return 1;
    }
    else
      return 0;
  }
  else
    if (max_lookbehind > 2)
  {
    if ((data[-2] == '/') && (data[-3] == '\\'))
    {
      return 0;
    }
  }
  return 1;
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


// hint:  ['link_end_ref is a mutable refrence to size_t']
size_t helper_sd_autolink__subreddit_1(size_t * const link_end_ref, uint8_t * const data, size_t size)
{
  size_t link_end = *link_end_ref;
  size_t start = link_end;
  int max_length = 24;
  if ((size >= (link_end + 10)) && (strncasecmp(((char *) data) + link_end, "reddit.com", 10) == 0))
  {
    link_end += 10;
    max_length = 10;
  }
  else
  {
    if ((size > (link_end + 2)) && (strncasecmp(((char *) data) + link_end, "t:", 2) == 0))
    {
      link_end += 2;
    }
    if (!isalnum(data[link_end]))
    {
      return 0;
    }
    link_end += 1;
  }
  while ((link_end < size) && (isalnum(data[link_end]) || (data[link_end] == '_')))
  {
    link_end += 1;
  }

  if (((link_end - start) < 2) || ((link_end - start) > max_length))
  {
    return 0;
  }
  *link_end_ref = link_end;
}


/*** DEPENDENCIES:
***/


size_t sd_autolink__subreddit(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash)
{
  size_t link_end;
  size_t rewind;
  int is_allminus = 0;
  rewind = check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size, 'r');
  if (!rewind)
  {
    return 0;
  }
  link_end = strlen("/");
  if ((size >= (link_end + 4)) && (strncasecmp(((char *) data) + link_end, "all-", 4) == 0))
  {
    is_allminus = 1;
  }
  do
  {
    helper_sd_autolink__subreddit_1(&link_end, data, size);
  }
  while (((link_end < size) && ((data[link_end] == '+') || (is_allminus && (data[link_end] == '-')))) && (link_end++));
  if ((link_end < size) && (data[link_end] == '/'))
  {
    while ((link_end < size) && (((isalnum(data[link_end]) || (data[link_end] == '_')) || (data[link_end] == '/')) || (data[link_end] == '-')))
    {
      link_end += 1;
    }

  }
  bufput(link, data - rewind, link_end + rewind);
  *no_slash = rewind == 1;
  *rewind_p = rewind;
  return link_end;
}


/*** DEPENDENCIES:
size_t helper_sd_autolink__subreddit_1(size_t * const link_end_ref, uint8_t * const data, size_t size)
{
  size_t link_end = *link_end_ref;
  size_t start = link_end;
  int max_length = 24;
  if ((size >= (link_end + 10)) && (strncasecmp(((char *) data) + link_end, "reddit.com", 10) == 0))
  {
    link_end += 10;
    max_length = 10;
  }
  else
  {
    if ((size > (link_end + 2)) && (strncasecmp(((char *) data) + link_end, "t:", 2) == 0))
    {
      link_end += 2;
    }
    if (!isalnum(data[link_end]))
    {
      return 0;
    }
    link_end += 1;
  }
  while ((link_end < size) && (isalnum(data[link_end]) || (data[link_end] == '_')))
  {
    link_end += 1;
  }

  if (((link_end - start) < 2) || ((link_end - start) > max_length))
  {
    return 0;
  }
  *link_end_ref = link_end;
}


----------------------------
static int check_reddit_autolink_prefix(const uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, char prefix_char)
{
  if (((size < 2) || (max_rewind < 1)) || (data[-1] != prefix_char))
  {
    return 0;
  }
  if (max_rewind > 1)
  {
    const char boundary = data[-2];
    if (boundary == '/')
    {
      return 2;
    }
    else
      if (ispunct(boundary) || isspace(boundary))
    {
      return 1;
    }
    else
      return 0;
  }
  else
    if (max_lookbehind > 2)
  {
    if ((data[-2] == '/') && (data[-3] == '\\'))
    {
      return 0;
    }
  }
  return 1;
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


int sd_autolink_issafe(const uint8_t *link, size_t link_len)
{
  static const size_t valid_uris_count = 14;
  static const char *valid_uris[] = {"http://", "https://", "ftp://", "mailto://", "/", "git://", "steam://", "irc://", "news://", "mumble://", "ssh://", "ircs://", "ts3server://", "#"};
  size_t i;
  for (i = 0; i < valid_uris_count; i += 1)
  {
    size_t len = strlen(valid_uris[i]);
    if (((link_len > len) && (strncasecmp((char *) link, valid_uris[i], len) == 0)) && (((isalnum(link[len]) || (link[len] == '#')) || (link[len] == '/')) || (link[len] == '?')))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
***/


size_t sd_autolink__url(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags)
{
  size_t link_end;
  size_t rewind = 0;
  size_t domain_len;
  if (((size < 4) || (data[1] != '/')) || (data[2] != '/'))
  {
    return 0;
  }
  while ((rewind < max_rewind) && isalpha(data[(-rewind) - 1]))
  {
    rewind += 1;
  }

  if (!sd_autolink_issafe(data - rewind, size + rewind))
  {
    return 0;
  }
  link_end = strlen("://");
  domain_len = check_domain(data + link_end, size - link_end, flags & SD_AUTOLINK_SHORT_DOMAINS);
  if (domain_len == 0)
  {
    return 0;
  }
  link_end += domain_len;
  while ((link_end < size) && (!isspace(data[link_end])))
  {
    link_end += 1;
  }

  link_end = autolink_delim(data, link_end, max_rewind, size);
  if (link_end == 0)
  {
    return 0;
  }
  bufput(link, data - rewind, link_end + rewind);
  *rewind_p = rewind;
  return link_end;
}


/*** DEPENDENCIES:
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
static size_t autolink_delim(uint8_t *data, size_t link_end, size_t max_rewind, size_t size)
{
  uint8_t cclose;
  uint8_t copen = 0;
  size_t i;
  for (i = 0; i < link_end; i += 1)
  {
    if (data[i] == '<')
    {
      link_end = i;
      break;
    }
  }

  while (link_end > 0)
  {
    helper_autolink_delim_1(&link_end, data);
  }

  if (link_end == 0)
  {
    return 0;
  }
  cclose = data[link_end - 1];
  switch (cclose)
  {
    case '"':
    {
      copen = '"';
      break;
    }

    case '\'':
    {
      copen = '\'';
      break;
    }

    case ')':
    {
      copen = '(';
      break;
    }

    case ']':
    {
      copen = '[';
      break;
    }

    case '}':
    {
      copen = '{';
      break;
    }

  }

  if (copen != 0)
  {
    size_t closing = 0;
    size_t opening = 0;
    size_t i = 0;
    while (i < link_end)
    {
      if (data[i] == copen)
      {
        opening += 1;
      }
      else
        if (data[i] == cclose)
      {
        closing += 1;
      }
      i += 1;
    }

    if (closing != opening)
    {
      link_end -= 1;
    }
  }
  return link_end;
}


----------------------------
int sd_autolink_issafe(const uint8_t *link, size_t link_len)
{
  static const size_t valid_uris_count = 14;
  static const char *valid_uris[] = {"http://", "https://", "ftp://", "mailto://", "/", "git://", "steam://", "irc://", "news://", "mumble://", "ssh://", "ircs://", "ts3server://", "#"};
  size_t i;
  for (i = 0; i < valid_uris_count; i += 1)
  {
    size_t len = strlen(valid_uris[i]);
    if (((link_len > len) && (strncasecmp((char *) link, valid_uris[i], len) == 0)) && (((isalnum(link[len]) || (link[len] == '#')) || (link[len] == '/')) || (link[len] == '?')))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
static size_t check_domain(uint8_t *data, size_t size, int allow_short)
{
  size_t i;
  size_t np = 0;
  if (!isalnum(data[0]))
  {
    return 0;
  }
  for (i = 1; i < (size - 1); i += 1)
  {
    if (data[i] == '.')
    {
      np += 1;
    }
    else
      if ((!isalnum(data[i])) && (data[i] != '-'))
    {
      break;
    }
  }

  if (allow_short)
  {
    return i;
  }
  else
  {
    return (np) ? (i) : (0);
  }
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


