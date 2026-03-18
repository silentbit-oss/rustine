static size_t smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size < 2)
  {
    return 0;
  }
  switch (text[1])
  {
    case '\\':

    case '"':

    case '\'':

    case '.':

    case '-':

    case '`':
    {
      bufputc(ob, text[1]);
      return 1;
    }

    default:
    {
      bufputc(ob, '\\');
      return 0;
    }

  }

}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
***/


inline static int word_boundary(uint8_t c)
{
  return ((c == 0) || isspace(c)) || ispunct(c);
}


/*** DEPENDENCIES:
***/


static int smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
  char ent[8];
  if ((*is_open) && (!word_boundary(next_char)))
  {
    return 0;
  }
  if ((!(*is_open)) && (!word_boundary(previous_char)))
  {
    return 0;
  }
  snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? ('r') : ('l'), quote);
  *is_open = !(*is_open);
  bufputs(ob, ent);
  return 1;
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
inline static int word_boundary(uint8_t c)
{
  return ((c == 0) || isspace(c)) || ispunct(c);
}


----------------------------
void bufputs(struct buf *buf, const char *str)
{
  bufput(buf, str, strlen(str));
}


----------------------------
***/


static size_t smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size >= 2)
  {
    uint8_t t1 = tolower(text[1]);
    if (t1 == '\'')
    {
      if (smartypants_quotes(ob, previous_char, (size >= 3) ? (text[2]) : (0), 'd', &smrt->in_dquote))
      {
        return 1;
      }
    }
    if (((((t1 == 's') || (t1 == 't')) || (t1 == 'm')) || (t1 == 'd')) && ((size == 3) || word_boundary(text[2])))
    {
      bufput(ob, "&rsquo;", (sizeof("&rsquo;")) - 1);
      return 0;
    }
    if (size >= 3)
    {
      uint8_t t2 = tolower(text[2]);
      if (((((t1 == 'r') && (t2 == 'e')) || ((t1 == 'l') && (t2 == 'l'))) || ((t1 == 'v') && (t2 == 'e'))) && ((size == 4) || word_boundary(text[3])))
      {
        bufput(ob, "&rsquo;", (sizeof("&rsquo;")) - 1);
        return 0;
      }
    }
  }
  if (smartypants_quotes(ob, previous_char, (size > 0) ? (text[1]) : (0), 's', &smrt->in_squote))
  {
    return 0;
  }
  bufputc(ob, text[0]);
  return 0;
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
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
inline static int word_boundary(uint8_t c)
{
  return ((c == 0) || isspace(c)) || ispunct(c);
}


----------------------------
static int smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
  char ent[8];
  if ((*is_open) && (!word_boundary(next_char)))
  {
    return 0;
  }
  if ((!(*is_open)) && (!word_boundary(previous_char)))
  {
    return 0;
  }
  snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? ('r') : ('l'), quote);
  *is_open = !(*is_open);
  bufputs(ob, ent);
  return 1;
}


----------------------------
***/


static size_t smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (!smartypants_quotes(ob, previous_char, (size > 0) ? (text[1]) : (0), 'd', &smrt->in_dquote))
  {
    bufput(ob, "&quot;", (sizeof("&quot;")) - 1);
  }
  return 0;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
static int smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
  char ent[8];
  if ((*is_open) && (!word_boundary(next_char)))
  {
    return 0;
  }
  if ((!(*is_open)) && (!word_boundary(previous_char)))
  {
    return 0;
  }
  snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? ('r') : ('l'), quote);
  *is_open = !(*is_open);
  bufputs(ob, ent);
  return 1;
}


----------------------------
***/


static size_t smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (word_boundary(previous_char) && (size >= 3))
  {
    if (((text[0] == '1') && (text[1] == '/')) && (text[2] == '2'))
    {
      if ((size == 3) || word_boundary(text[3]))
      {
        bufput(ob, "&frac12;", (sizeof("&frac12;")) - 1);
        return 2;
      }
    }
    if (((text[0] == '1') && (text[1] == '/')) && (text[2] == '4'))
    {
      if (((size == 3) || word_boundary(text[3])) || (((size >= 5) && (tolower(text[3]) == 't')) && (tolower(text[4]) == 'h')))
      {
        bufput(ob, "&frac14;", (sizeof("&frac14;")) - 1);
        return 2;
      }
    }
    if (((text[0] == '3') && (text[1] == '/')) && (text[2] == '4'))
    {
      if (((size == 3) || word_boundary(text[3])) || ((((size >= 6) && (tolower(text[3]) == 't')) && (tolower(text[4]) == 'h')) && (tolower(text[5]) == 's')))
      {
        bufput(ob, "&frac34;", (sizeof("&frac34;")) - 1);
        return 2;
      }
    }
  }
  bufputc(ob, text[0]);
  return 0;
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
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
inline static int word_boundary(uint8_t c)
{
  return ((c == 0) || isspace(c)) || ispunct(c);
}


----------------------------
***/


static size_t smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if ((size >= 2) && (text[1] == '`'))
  {
    if (smartypants_quotes(ob, previous_char, (size >= 3) ? (text[2]) : (0), 'd', &smrt->in_dquote))
    {
      return 1;
    }
  }
  return 0;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
static int smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
  char ent[8];
  if ((*is_open) && (!word_boundary(next_char)))
  {
    return 0;
  }
  if ((!(*is_open)) && (!word_boundary(previous_char)))
  {
    return 0;
  }
  snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? ('r') : ('l'), quote);
  *is_open = !(*is_open);
  bufputs(ob, ent);
  return 1;
}


----------------------------
***/


static size_t smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (((size >= 3) && (text[1] == '.')) && (text[2] == '.'))
  {
    bufput(ob, "&hellip;", (sizeof("&hellip;")) - 1);
    return 2;
  }
  if (((((size >= 5) && (text[1] == ' ')) && (text[2] == '.')) && (text[3] == ' ')) && (text[4] == '.'))
  {
    bufput(ob, "&hellip;", (sizeof("&hellip;")) - 1);
    return 4;
  }
  bufputc(ob, text[0]);
  return 0;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
***/


static size_t smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (((size >= 3) && (text[1] == '-')) && (text[2] == '-'))
  {
    bufput(ob, "&mdash;", (sizeof("&mdash;")) - 1);
    return 2;
  }
  if ((size >= 2) && (text[1] == '-'))
  {
    bufput(ob, "&ndash;", (sizeof("&ndash;")) - 1);
    return 1;
  }
  bufputc(ob, text[0]);
  return 0;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
***/


static size_t smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  static const char *skip_tags[] = {"pre", "code", "var", "samp", "kbd", "math", "script", "style"};
  static const size_t skip_tags_count = 8;
  size_t tag;
  size_t i = 0;
  while ((i < size) && (text[i] != '>'))
  {
    i += 1;
  }

  for (tag = 0; tag < skip_tags_count; tag += 1)
  {
    if (sdhtml_is_tag(text, size, skip_tags[tag]) == HTML_TAG_OPEN)
    {
      break;
    }
  }

  if (tag < skip_tags_count)
  {
    for (;;)
    {
      while ((i < size) && (text[i] != '<'))
      {
        i += 1;
      }

      if (i == size)
      {
        break;
      }
      if (sdhtml_is_tag(text + i, size - i, skip_tags[tag]) == HTML_TAG_CLOSE)
      {
        break;
      }
      i += 1;
    }

    while ((i < size) && (text[i] != '>'))
    {
      i += 1;
    }

  }
  bufput(ob, text, i + 1);
  return i;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
int sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname)
{
  unsigned int tagname_idx = 0;
  size_t i;
  int closed = 0;
  if ((tag_size < 3) || (tag_data[0] != '<'))
  {
    return HTML_TAG_NONE;
  }
  i = 1;
  if (tag_data[i] == '/')
  {
    closed = 1;
    i += 1;
  }
  for (; i < tag_size; i += 1, tagname_idx += 1)
  {
    if (tagname[tagname_idx] == 0)
    {
      break;
    }
    if (tag_data[i] != tagname[tagname_idx])
    {
      return HTML_TAG_NONE;
    }
  }

  if (i == tag_size)
  {
    return HTML_TAG_NONE;
  }
  if (isspace(tag_data[i]) || (tag_data[i] == '>'))
  {
    return (closed) ? (HTML_TAG_CLOSE) : (HTML_TAG_OPEN);
  }
  return HTML_TAG_NONE;
}


----------------------------
***/


static size_t smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if ((size >= 6) && (memcmp(text, "&quot;", 6) == 0))
  {
    if (smartypants_quotes(ob, previous_char, (size >= 7) ? (text[6]) : (0), 'd', &smrt->in_dquote))
    {
      return 5;
    }
  }
  if ((size >= 4) && (memcmp(text, "&#0;", 4) == 0))
  {
    return 3;
  }
  bufputc(ob, '&');
  return 0;
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
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
static int smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
  char ent[8];
  if ((*is_open) && (!word_boundary(next_char)))
  {
    return 0;
  }
  if ((!(*is_open)) && (!word_boundary(previous_char)))
  {
    return 0;
  }
  snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? ('r') : ('l'), quote);
  *is_open = !(*is_open);
  bufputs(ob, ent);
  return 1;
}


----------------------------
***/


static size_t smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size >= 3)
  {
    uint8_t t1 = tolower(text[1]);
    uint8_t t2 = tolower(text[2]);
    if ((t1 == 'c') && (t2 == ')'))
    {
      bufput(ob, "&copy;", (sizeof("&copy;")) - 1);
      return 2;
    }
    if ((t1 == 'r') && (t2 == ')'))
    {
      bufput(ob, "&reg;", (sizeof("&reg;")) - 1);
      return 2;
    }
    if ((((size >= 4) && (t1 == 't')) && (t2 == 'm')) && (text[3] == ')'))
    {
      bufput(ob, "&trade;", (sizeof("&trade;")) - 1);
      return 3;
    }
  }
  bufputc(ob, text[0]);
  return 0;
}


/*** DEPENDENCIES:
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
***/


void sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size)
{
  size_t i;
  struct smartypants_data smrt = {0, 0};
  if (!text)
  {
    return;
  }
  bufgrow(ob, size);
  for (i = 0; i < size; i += 1)
  {
    size_t org;
    uint8_t action = 0;
    org = i;
    while ((i < size) && ((action = smartypants_cb_chars[text[i]]) == 0))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, text + org, i - org);
    }
    if (i < size)
    {
      i += smartypants_cb_ptrs[(int) action](ob, &smrt, (i) ? (text[i - 1]) : (0), text + i, size - i);
    }
  }

}


/*** DEPENDENCIES:
static size_t (*smartypants_cb_ptrs[])(struct buf *, struct smartypants_data *, uint8_t, const uint8_t *, size_t) = {0, smartypants_cb__dash, smartypants_cb__parens, smartypants_cb__squote, smartypants_cb__dquote, smartypants_cb__amp, smartypants_cb__period, smartypants_cb__number, smartypants_cb__ltag, smartypants_cb__backtick, smartypants_cb__escape}
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
struct smartypants_data
{
  int in_squote;
  int in_dquote;
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
static const uint8_t smartypants_cb_chars[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
----------------------------
***/


