static void tty_keys_free1(struct tty_key *tk)
{
  if (tk->next != 0)
  {
    tty_keys_free1(tk->next);
  }
  if (tk->left != 0)
  {
    tty_keys_free1(tk->left);
  }
  if (tk->right != 0)
  {
    tty_keys_free1(tk->right);
  }
  free(tk);
}


/*** DEPENDENCIES:
None
----------------------------
***/


void tty_keys_free(struct tty *tty)
{
  tty_keys_free1(tty->key_tree);
}


/*** DEPENDENCIES:
static void tty_keys_free1(struct tty_key *tk)
{
  if (tk->next != 0)
  {
    tty_keys_free1(tk->next);
  }
  if (tk->left != 0)
  {
    tty_keys_free1(tk->left);
  }
  if (tk->right != 0)
  {
    tty_keys_free1(tk->right);
  }
  free(tk);
}


----------------------------
None
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to u_int', 'x_ref is a mutable refrence to u_int', 'y_ref is a mutable refrence to u_int', 'b_ref is a mutable refrence to u_int', 'ch_ref is a mutable refrence to u_char']
int helper_tty_keys_mouse_1(u_int * const i_ref, u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, u_char * const ch_ref, const char * const buf, size_t len, size_t * const size, struct client * const c)
{
  u_int i = *i_ref;
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  u_char ch = *ch_ref;
  *size = 3;
  for (i = 0; i < 3; i += 1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (i == 0)
    {
      b = ch;
    }
    else
      if (i == 1)
    {
      x = ch;
    }
    else
      y = ch;
  }

  log_debug("%s: mouse input: %.*s", c->name, (int) (*size), buf);
  if (b < 32)
  {
    return -1;
  }
  b -= 32;
  if (x >= 33)
  {
    x -= 33;
  }
  else
    x = 256 - x;
  if (y >= 33)
  {
    y -= 33;
  }
  else
    y = 256 - y;
  *i_ref = i;
  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *ch_ref = ch;
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
None
----------------------------
***/


// hint:  ['x_ref is a mutable refrence to u_int', 'y_ref is a mutable refrence to u_int', 'b_ref is a mutable refrence to u_int', 'sgr_b_ref is a mutable refrence to u_int', 'sgr_type_ref is a mutable refrence to u_char', 'ch_ref is a mutable refrence to u_char']
int helper_tty_keys_mouse_2(u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, u_int * const sgr_b_ref, u_char * const sgr_type_ref, u_char * const ch_ref, const char * const buf, size_t len, size_t * const size, struct client * const c)
{
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  u_int sgr_b = *sgr_b_ref;
  u_char sgr_type = *sgr_type_ref;
  u_char ch = *ch_ref;
  *size = 3;
  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (ch == ';')
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    sgr_b = (10 * sgr_b) + (ch - '0');
  }

  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (ch == ';')
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    x = (10 * x) + (ch - '0');
  }

  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if ((ch == 'M') || (ch == 'm'))
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    y = (10 * y) + (ch - '0');
  }

  log_debug("%s: mouse input (SGR): %.*s", c->name, (int) (*size), buf);
  if ((x < 1) || (y < 1))
  {
    return -1;
  }
  x -= 1;
  y -= 1;
  b = sgr_b;
  sgr_type = ch;
  if (sgr_type == 'm')
  {
    b |= 3;
  }
  if ((sgr_type == 'm') && (sgr_b & 64))
  {
    return -2;
  }
  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *sgr_b_ref = sgr_b;
  *sgr_type_ref = sgr_type;
  *ch_ref = ch;
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
None
----------------------------
***/


static struct tty_key *tty_keys_find1(struct tty_key *tk, const char *buf, size_t len, size_t *size)
{
  unsigned int buf_idx = 0;
  unsigned int tk_idx = 0;
  if ((&tk[tk_idx]) == 0)
  {
    return 0;
  }
  if (tk->ch == buf[buf_idx])
  {
    buf_idx += 1;
    len -= 1;
    *size += 1;
    if ((len == 0) || ((tk->next == 0) && (tk->key != 0xfffe00000000ULL)))
    {
      return tk;
    }
    tk_idx = tk_idx->next;
  }
  else
  {
    if (buf[buf_idx] < tk->ch)
    {
      tk_idx = tk_idx->left;
    }
    else
      if (buf[buf_idx] > tk->ch)
    {
      tk_idx = tk_idx->right;
    }
  }
  return tty_keys_find1(tk, buf, len, size);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct tty_key *tty_keys_find(struct tty *tty, const char *buf, size_t len, size_t *size)
{
  *size = 0;
  return tty_keys_find1(tty->key_tree, buf, len, size);
}


/*** DEPENDENCIES:
static struct tty_key *tty_keys_find1(struct tty_key *tk, const char *buf, size_t len, size_t *size)
{
  unsigned int buf_idx = 0;
  unsigned int tk_idx = 0;
  if ((&tk[tk_idx]) == 0)
  {
    return 0;
  }
  if (tk->ch == buf[buf_idx])
  {
    buf_idx += 1;
    len -= 1;
    *size += 1;
    if ((len == 0) || ((tk->next == 0) && (tk->key != 0xfffe00000000ULL)))
    {
      return tk;
    }
    tk_idx = tk_idx->next;
  }
  else
  {
    if (buf[buf_idx] < tk->ch)
    {
      tk_idx = tk_idx->left;
    }
    else
      if (buf[buf_idx] > tk->ch)
    {
      tk_idx = tk_idx->right;
    }
  }
  return tty_keys_find1(tk, buf, len, size);
}


----------------------------
None
----------------------------
***/


// hint:  ['more_ref is a mutable refrence to ', 'i_ref is a mutable refrence to u_int']
int helper_tty_keys_next1_1(enum utf8_state * const more_ref, u_int * const i_ref, const char * const buf, size_t len, key_code * const key, size_t * const size, int expired, struct client * const c, struct utf8_data ud, wchar_t wc)
{
  enum utf8_state more = *more_ref;
  u_int i = *i_ref;
  *size = ud.size;
  if (len < ud.size)
  {
    if (!expired)
    {
      return 1;
    }
    return -1;
  }
  for (i = 1; i < ud.size; i += 1)
  {
    more = utf8_append(&ud, (u_char) buf[i]);
  }

  if (more != UTF8_DONE)
  {
    return -1;
  }
  if (utf8_combine(&ud, &wc) != UTF8_DONE)
  {
    return -1;
  }
  *key = wc;
  log_debug("%s: UTF-8 key %.*s %#llx", c->name, (int) ud.size, buf, *key);
  return 0;
  *more_ref = more;
  *i_ref = i;
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
typedef unsigned long long key_code
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


static int tty_keys_next1(struct tty *tty, const char *buf, size_t len, key_code *key, size_t *size, int expired)
{
  struct client *c = tty->client;
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  struct tty_key *tk1;
  unsigned int tk1_idx = 0;
  struct utf8_data ud;
  enum utf8_state more;
  u_int i;
  wchar_t wc;
  int n;
  log_debug("%s: next key is %zu (%.*s) (expired=%d)", c->name, len, (int) len, buf, expired);
  tk_idx = tty_keys_find(tty, buf, len, size);
  if (((&tk[tk_idx]) != 0) && (tk->key != 0xfffe00000000ULL))
  {
    tk1_idx = &tk[tk_idx];
    do
    {
      log_debug("%s: keys in list: %#llx", c->name, tk1->key);
    }
    while ((tk1_idx = tk1_idx->next) != 0);
    if ((tk->next != 0) && (!expired))
    {
      return 1;
    }
    *key = tk->key;
    return 0;
  }
  n = xterm_keys_find(buf, len, size, key);
  if (n == 0)
  {
    return 0;
  }
  if ((n == 1) && (!expired))
  {
    return 1;
  }
  more = utf8_open(&ud, (u_char) (*buf));
  if (more == UTF8_MORE)
  {
    helper_tty_keys_next1_1(&more, &i, buf, len, key, size, expired, c, ud, wc);
  }
  return -1;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
static struct tty_key *tty_keys_find(struct tty *tty, const char *buf, size_t len, size_t *size)
{
  *size = 0;
  return tty_keys_find1(tty->key_tree, buf, len, size);
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
int xterm_keys_find(const char *buf, size_t len, size_t *size, key_code *key)
{
  const struct xterm_keys_entry *entry;
  unsigned int entry_idx = 0;
  u_int i;
  int matched;
  key_code modifiers;
  for (i = 0; i < ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))); i += 1)
  {
    entry_idx = &xterm_keys_table[i];
    matched = xterm_keys_match(entry->template, buf, len, size, &modifiers);
    if (matched == (-1))
    {
      continue;
    }
    if (matched == 0)
    {
      *key = (entry->key | modifiers) | 0x1000000000000ULL;
    }
    return matched;
  }

  return -1;
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
int helper_tty_keys_next1_1(enum utf8_state * const more_ref, u_int * const i_ref, const char * const buf, size_t len, key_code * const key, size_t * const size, int expired, struct client * const c, struct utf8_data ud, wchar_t wc)
{
  enum utf8_state more = *more_ref;
  u_int i = *i_ref;
  *size = ud.size;
  if (len < ud.size)
  {
    if (!expired)
    {
      return 1;
    }
    return -1;
  }
  for (i = 1; i < ud.size; i += 1)
  {
    more = utf8_append(&ud, (u_char) buf[i]);
  }

  if (more != UTF8_DONE)
  {
    return -1;
  }
  if (utf8_combine(&ud, &wc) != UTF8_DONE)
  {
    return -1;
  }
  *key = wc;
  log_debug("%s: UTF-8 key %.*s %#llx", c->name, (int) ud.size, buf, *key);
  return 0;
  *more_ref = more;
  *i_ref = i;
}


----------------------------
None
----------------------------
***/


// hint:  ['size_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to int', 'key_ref is a mutable refrence to key_code']
void helper_tty_keys_next_1(size_t * const size_ref, int * const n_ref, key_code * const key_ref, struct tty * const tty, const char * const buf, unsigned int buf_idx, size_t len, int expired)
{
  size_t size = *size_ref;
  int n = *n_ref;
  key_code key = *key_ref;
  n = tty_keys_next1(tty, (&buf[buf_idx]) + 1, len - 1, &key, &size, expired);
  if (n == 0)
  {
    if (key & 0x1000000000000ULL)
    {
      key = '\033';
      size = 1;
      goto complete_key;
    }
    key |= 0x200000000000ULL;
    size += 1;
    goto complete_key;
  }
  if (n == 1)
  {
    goto partial_key;
  }
  *size_ref = size;
  *n_ref = n;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
static int tty_keys_next1(struct tty *tty, const char *buf, size_t len, key_code *key, size_t *size, int expired)
{
  struct client *c = tty->client;
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  struct tty_key *tk1;
  unsigned int tk1_idx = 0;
  struct utf8_data ud;
  enum utf8_state more;
  u_int i;
  wchar_t wc;
  int n;
  log_debug("%s: next key is %zu (%.*s) (expired=%d)", c->name, len, (int) len, buf, expired);
  tk_idx = tty_keys_find(tty, buf, len, size);
  if (((&tk[tk_idx]) != 0) && (tk->key != 0xfffe00000000ULL))
  {
    tk1_idx = &tk[tk_idx];
    do
    {
      log_debug("%s: keys in list: %#llx", c->name, tk1->key);
    }
    while ((tk1_idx = tk1_idx->next) != 0);
    if ((tk->next != 0) && (!expired))
    {
      return 1;
    }
    *key = tk->key;
    return 0;
  }
  n = xterm_keys_find(buf, len, size, key);
  if (n == 0)
  {
    return 0;
  }
  if ((n == 1) && (!expired))
  {
    return 1;
  }
  more = utf8_open(&ud, (u_char) (*buf));
  if (more == UTF8_MORE)
  {
    helper_tty_keys_next1_1(&more, &i, buf, len, key, size, expired, c, ud, wc);
  }
  return -1;
}


----------------------------
None
----------------------------
***/


static int tty_keys_mouse(struct tty *tty, const char *buf, size_t len, size_t *size)
{
  struct client *c = tty->client;
  struct mouse_event *m = &tty->mouse;
  u_int i;
  u_int x;
  u_int y;
  u_int b;
  u_int sgr_b;
  u_char sgr_type;
  u_char ch;
  *size = 0;
  x = (y = (b = (sgr_b = 0)));
  sgr_type = ' ';
  if (buf[0] != '\033')
  {
    return -1;
  }
  if (len == 1)
  {
    return 1;
  }
  if (buf[1] != '[')
  {
    return -1;
  }
  if (len == 2)
  {
    return 1;
  }
  if (buf[2] == 'M')
  {
    helper_tty_keys_mouse_1(&i, &x, &y, &b, &ch, buf, len, size, c);
  }
  else
    if (buf[2] == '<')
  {
    helper_tty_keys_mouse_2(&x, &y, &b, &sgr_b, &sgr_type, &ch, buf, len, size, c);
  }
  else
    return -1;
  m->lx = m->x;
  m->x = x;
  m->ly = m->y;
  m->y = y;
  m->lb = m->b;
  m->b = b;
  m->sgr_type = sgr_type;
  m->sgr_b = sgr_b;
  return 0;
}


/*** DEPENDENCIES:
struct mouse_event
{
  int valid;
  key_code key;
  int statusat;
  u_int x;
  u_int y;
  u_int b;
  u_int lx;
  u_int ly;
  u_int lb;
  int s;
  int w;
  int wp;
  u_int sgr_type;
  u_int sgr_b;
}
----------------------------
int helper_tty_keys_mouse_2(u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, u_int * const sgr_b_ref, u_char * const sgr_type_ref, u_char * const ch_ref, const char * const buf, size_t len, size_t * const size, struct client * const c)
{
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  u_int sgr_b = *sgr_b_ref;
  u_char sgr_type = *sgr_type_ref;
  u_char ch = *ch_ref;
  *size = 3;
  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (ch == ';')
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    sgr_b = (10 * sgr_b) + (ch - '0');
  }

  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (ch == ';')
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    x = (10 * x) + (ch - '0');
  }

  while (1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if ((ch == 'M') || (ch == 'm'))
    {
      break;
    }
    if ((ch < '0') || (ch > '9'))
    {
      return -1;
    }
    y = (10 * y) + (ch - '0');
  }

  log_debug("%s: mouse input (SGR): %.*s", c->name, (int) (*size), buf);
  if ((x < 1) || (y < 1))
  {
    return -1;
  }
  x -= 1;
  y -= 1;
  b = sgr_b;
  sgr_type = ch;
  if (sgr_type == 'm')
  {
    b |= 3;
  }
  if ((sgr_type == 'm') && (sgr_b & 64))
  {
    return -2;
  }
  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *sgr_b_ref = sgr_b;
  *sgr_type_ref = sgr_type;
  *ch_ref = ch;
}


----------------------------
int helper_tty_keys_mouse_1(u_int * const i_ref, u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, u_char * const ch_ref, const char * const buf, size_t len, size_t * const size, struct client * const c)
{
  u_int i = *i_ref;
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  u_char ch = *ch_ref;
  *size = 3;
  for (i = 0; i < 3; i += 1)
  {
    if (len <= (*size))
    {
      return 1;
    }
    ch = (u_char) buf[(*size)++];
    if (i == 0)
    {
      b = ch;
    }
    else
      if (i == 1)
    {
      x = ch;
    }
    else
      y = ch;
  }

  log_debug("%s: mouse input: %.*s", c->name, (int) (*size), buf);
  if (b < 32)
  {
    return -1;
  }
  b -= 32;
  if (x >= 33)
  {
    x -= 33;
  }
  else
    x = 256 - x;
  if (y >= 33)
  {
    y -= 33;
  }
  else
    y = 256 - y;
  *i_ref = i;
  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *ch_ref = ch;
}


----------------------------
None
----------------------------
***/


static int tty_keys_device_attributes(struct tty *tty, const char *buf, size_t len, size_t *size)
{
  struct client *c = tty->client;
  u_int i;
  u_int a;
  u_int b;
  char tmp[64];
  char *endptr;
  static const char *types[] = {"VT100", "VT101", "VT102", "VT220", "VT320", "VT420", "Unknown"};
  int type;
  *size = 0;
  if (buf[0] != '\033')
  {
    return -1;
  }
  if (len == 1)
  {
    return 1;
  }
  if (buf[1] != '[')
  {
    return -1;
  }
  if (len == 2)
  {
    return 1;
  }
  if (buf[2] != '?')
  {
    return -1;
  }
  if (len == 3)
  {
    return 1;
  }
  for (i = 0; (i < ((sizeof(tmp)) - 1)) && (buf[3 + i] != 'c'); i += 1)
  {
    if ((3 + i) == len)
    {
      return 1;
    }
    tmp[i] = buf[3 + i];
  }

  if (i == ((sizeof(tmp)) - 1))
  {
    return -1;
  }
  tmp[i] = '\0';
  *size = 4 + i;
  a = strtoul(tmp, &endptr, 10);
  if ((*endptr) == ';')
  {
    b = strtoul(endptr + 1, &endptr, 10);
    if (((*endptr) != '\0') && ((*endptr) != ';'))
    {
      b = 0;
    }
  }
  else
    a = (b = 0);
  type = TTY_UNKNOWN;
  switch (a)
  {
    case 1:
    {
      if (b == 2)
      {
        type = TTY_VT100;
      }
      else
        if (b == 0)
      {
        type = TTY_VT101;
      }
      break;
    }

    case 6:
    {
      type = TTY_VT102;
      break;
    }

    case 62:
    {
      type = TTY_VT220;
      break;
    }

    case 63:
    {
      type = TTY_VT320;
      break;
    }

    case 64:
    {
      type = TTY_VT420;
      break;
    }

  }

  tty_set_type(tty, type);
  log_debug("%s: received DA %.*s (%s)", c->name, (int) (*size), buf, types[type]);
  return 0;
}


/*** DEPENDENCIES:
void tty_set_type(struct tty *tty, int type)
{
  tty->term_type = type;
  if (tty->term_type == TTY_VT420)
  {
    tty_puts(tty, "\033[?69h");
  }
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
None
----------------------------
***/


static void tty_keys_add1(struct tty_key **tkp, const char *s, key_code key)
{
  unsigned int s_idx = 0;
  unsigned int tkp_idx = 0;
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  tk_idx = tkp[tkp_idx];
  if ((&tk[tk_idx]) == 0)
  {
    tk_idx = (tkp[tkp_idx] = xcalloc(1, sizeof(*tk_idx)));
    tk->ch = s[s_idx];
    tk->key = 0xfffe00000000ULL;
  }
  if (s[s_idx] == tk->ch)
  {
    s_idx += 1;
    if (s[s_idx] == '\0')
    {
      tk->key = key;
      return;
    }
    tkp_idx = &tk->next;
  }
  else
  {
    if (s[s_idx] < tk->ch)
    {
      tkp_idx = &tk->left;
    }
    else
      if (s[s_idx] > tk->ch)
    {
      tkp_idx = &tk->right;
    }
  }
  tty_keys_add1(tkp, s, key);
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
void *xcalloc(size_t nmemb, size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((size == 0) || (nmemb == 0))
  {
    fatalx("xcalloc: zero size");
  }
  ptr_idx = calloc(nmemb, size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xcalloc: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return ptr;
}


----------------------------
None
----------------------------
***/


static void tty_keys_add(struct tty *tty, const char *s, key_code key)
{
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  size_t size;
  const char *keystr;
  unsigned int keystr_idx = 0;
  keystr_idx = key_string_lookup_key(key);
  if ((tk_idx = tty_keys_find(tty, s, strlen(s), &size)) == 0)
  {
    log_debug("new key %s: 0x%llx (%s)", s, key, keystr);
    tty_keys_add1(&tty->key_tree, s, key);
  }
  else
  {
    log_debug("replacing key %s: 0x%llx (%s)", s, key, keystr);
    tk->key = key;
  }
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
static struct tty_key *tty_keys_find(struct tty *tty, const char *buf, size_t len, size_t *size)
{
  *size = 0;
  return tty_keys_find1(tty->key_tree, buf, len, size);
}


----------------------------
const char *key_string_lookup_key(key_code key)
{
  static char out[32];
  char tmp[8];
  u_int i;
  struct utf8_data ud;
  size_t off;
  *out = '\0';
  if (key == 0xffff00000000ULL)
  {
    return "None";
  }
  if (key == 0xfffe00000000ULL)
  {
    return "Unknown";
  }
  if (key == KEYC_FOCUS_IN)
  {
    return "FocusIn";
  }
  if (key == KEYC_FOCUS_OUT)
  {
    return "FocusOut";
  }
  if (key == KEYC_PASTE_START)
  {
    return "PasteStart";
  }
  if (key == KEYC_PASTE_END)
  {
    return "PasteEnd";
  }
  if (key == KEYC_MOUSE)
  {
    return "Mouse";
  }
  if (key == KEYC_DRAGGING)
  {
    return "Dragging";
  }
  if (key == KEYC_MOUSEMOVE_PANE)
  {
    return "MouseMovePane";
  }
  if (key == KEYC_MOUSEMOVE_STATUS)
  {
    return "MouseMoveStatus";
  }
  if (key == KEYC_MOUSEMOVE_BORDER)
  {
    return "MouseMoveBorder";
  }
  if ((key >= 0x000020000000ULL) && (key < (0x000020000000ULL + 1000)))
  {
    snprintf(out, sizeof(out), "User%u", (u_int) (key - 0x000020000000ULL));
    return out;
  }
  if ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == 0)
  {
    key = (' ' | 0x400000000000ULL) | (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
  }
  if (key & 0x400000000000ULL)
  {
    strlcat(out, "C-", sizeof(out));
  }
  if (key & 0x200000000000ULL)
  {
    strlcat(out, "M-", sizeof(out));
  }
  if (key & 0x800000000000ULL)
  {
    strlcat(out, "S-", sizeof(out));
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (key == key_string_table[i].key)
    {
      break;
    }
  }

  if (i != ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))))
  {
    strlcat(out, key_string_table[i].string, sizeof(out));
    return out;
  }
  if ((key > 127) && (key < 0x000010000000ULL))
  {
    if (utf8_split(key, &ud) == UTF8_DONE)
    {
      off = strlen(out);
      memcpy(out + off, ud.data, ud.size);
      out[off + ud.size] = '\0';
      return out;
    }
  }
  if ((key == 127) || (key > 255))
  {
    snprintf(out, sizeof(out), "Invalid#%llx", key);
    return out;
  }
  if (key <= 32)
  {
    if ((key == 0) || (key > 26))
    {
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (64 + key));
    }
    else
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (96 + key));
  }
  else
    if ((key >= 32) && (key <= 126))
  {
    tmp[0] = key;
    tmp[1] = '\0';
  }
  else
    if (key >= 128)
  {
    xsnprintf(tmp, sizeof(tmp), "\\%llo", key);
  }
  strlcat(out, tmp, sizeof(out));
  return out;
}


----------------------------
static void tty_keys_add1(struct tty_key **tkp, const char *s, key_code key)
{
  unsigned int s_idx = 0;
  unsigned int tkp_idx = 0;
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  tk_idx = tkp[tkp_idx];
  if ((&tk[tk_idx]) == 0)
  {
    tk_idx = (tkp[tkp_idx] = xcalloc(1, sizeof(*tk_idx)));
    tk->ch = s[s_idx];
    tk->key = 0xfffe00000000ULL;
  }
  if (s[s_idx] == tk->ch)
  {
    s_idx += 1;
    if (s[s_idx] == '\0')
    {
      tk->key = key;
      return;
    }
    tkp_idx = &tk->next;
  }
  else
  {
    if (s[s_idx] < tk->ch)
    {
      tkp_idx = &tk->left;
    }
    else
      if (s[s_idx] > tk->ch)
    {
      tkp_idx = &tk->right;
    }
  }
  tty_keys_add1(tkp, s, key);
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
None
----------------------------
***/


void tty_keys_build(struct tty *tty)
{
  const struct tty_default_key_raw *tdkr;
  unsigned int tdkr_idx = 0;
  const struct tty_default_key_code *tdkc;
  unsigned int tdkc_idx = 0;
  u_int i;
  u_int size;
  const char *s;
  unsigned int s_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (tty->key_tree != 0)
  {
    tty_keys_free(tty);
  }
  tty->key_tree = 0;
  for (i = 0; i < ((sizeof(tty_default_raw_keys)) / (sizeof(tty_default_raw_keys[0]))); i += 1)
  {
    tdkr_idx = &tty_default_raw_keys[i];
    s_idx = tdkr->string;
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkr->key);
    }
  }

  for (i = 0; i < ((sizeof(tty_default_code_keys)) / (sizeof(tty_default_code_keys[0]))); i += 1)
  {
    tdkc_idx = &tty_default_code_keys[i];
    s_idx = tty_term_string(tty->term, tdkc->code);
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkc->key);
    }
  }

  o_idx = options_get(global_options, "user-keys");
  if (((&o[o_idx]) != 0) && (options_array_size(o, &size) != (-1)))
  {
    for (i = 0; i < size; i += 1)
    {
      value_idx = options_array_get(o, i);
      if ((&value[value_idx]) != 0)
      {
        tty_keys_add(tty, value, 0x000020000000ULL + i);
      }
    }

  }
}


/*** DEPENDENCIES:
struct tty_default_key_code
{
  enum tty_code_code code;
  key_code key;
}
----------------------------
typedef unsigned long long key_code
----------------------------
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
}


----------------------------
const char *options_array_get(struct options_entry *o, u_int idx)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return 0;
  }
  if (idx >= o->arraysize)
  {
    return 0;
  }
  return o->array[idx];
}


----------------------------
static const struct tty_default_key_raw tty_default_raw_keys[] = {{"\033Oo", KEYC_KP_SLASH}, {"\033Oj", KEYC_KP_STAR}, {"\033Om", KEYC_KP_MINUS}, {"\033Ow", KEYC_KP_SEVEN}, {"\033Ox", KEYC_KP_EIGHT}, {"\033Oy", KEYC_KP_NINE}, {"\033Ok", KEYC_KP_PLUS}, {"\033Ot", KEYC_KP_FOUR}, {"\033Ou", KEYC_KP_FIVE}, {"\033Ov", KEYC_KP_SIX}, {"\033Oq", KEYC_KP_ONE}, {"\033Or", KEYC_KP_TWO}, {"\033Os", KEYC_KP_THREE}, {"\033OM", KEYC_KP_ENTER}, {"\033Op", KEYC_KP_ZERO}, {"\033On", KEYC_KP_PERIOD}, {"\033OA", KEYC_UP}, {"\033OB", KEYC_DOWN}, {"\033OC", KEYC_RIGHT}, {"\033OD", KEYC_LEFT}, {"\033[A", KEYC_UP}, {"\033[B", KEYC_DOWN}, {"\033[C", KEYC_RIGHT}, {"\033[D", KEYC_LEFT}, {"\033OH", KEYC_HOME}, {"\033OF", KEYC_END}, {"\033[H", KEYC_HOME}, {"\033[F", KEYC_END}, {"\033Oa", KEYC_UP | 0x400000000000ULL}, {"\033Ob", KEYC_DOWN | 0x400000000000ULL}, {"\033Oc", KEYC_RIGHT | 0x400000000000ULL}, {"\033Od", KEYC_LEFT | 0x400000000000ULL}, {"\033[a", KEYC_UP | 0x800000000000ULL}, {"\033[b", KEYC_DOWN | 0x800000000000ULL}, {"\033[c", KEYC_RIGHT | 0x800000000000ULL}, {"\033[d", KEYC_LEFT | 0x800000000000ULL}, {"\033[11^", KEYC_F1 | 0x400000000000ULL}, {"\033[12^", KEYC_F2 | 0x400000000000ULL}, {"\033[13^", KEYC_F3 | 0x400000000000ULL}, {"\033[14^", KEYC_F4 | 0x400000000000ULL}, {"\033[15^", KEYC_F5 | 0x400000000000ULL}, {"\033[17^", KEYC_F6 | 0x400000000000ULL}, {"\033[18^", KEYC_F7 | 0x400000000000ULL}, {"\033[19^", KEYC_F8 | 0x400000000000ULL}, {"\033[20^", KEYC_F9 | 0x400000000000ULL}, {"\033[21^", KEYC_F10 | 0x400000000000ULL}, {"\033[23^", KEYC_F11 | 0x400000000000ULL}, {"\033[24^", KEYC_F12 | 0x400000000000ULL}, {"\033[2^", KEYC_IC | 0x400000000000ULL}, {"\033[3^", KEYC_DC | 0x400000000000ULL}, {"\033[7^", KEYC_HOME | 0x400000000000ULL}, {"\033[8^", KEYC_END | 0x400000000000ULL}, {"\033[6^", KEYC_NPAGE | 0x400000000000ULL}, {"\033[5^", KEYC_PPAGE | 0x400000000000ULL}, {"\033[11$", KEYC_F1 | 0x800000000000ULL}, {"\033[12$", KEYC_F2 | 0x800000000000ULL}, {"\033[13$", KEYC_F3 | 0x800000000000ULL}, {"\033[14$", KEYC_F4 | 0x800000000000ULL}, {"\033[15$", KEYC_F5 | 0x800000000000ULL}, {"\033[17$", KEYC_F6 | 0x800000000000ULL}, {"\033[18$", KEYC_F7 | 0x800000000000ULL}, {"\033[19$", KEYC_F8 | 0x800000000000ULL}, {"\033[20$", KEYC_F9 | 0x800000000000ULL}, {"\033[21$", KEYC_F10 | 0x800000000000ULL}, {"\033[23$", KEYC_F11 | 0x800000000000ULL}, {"\033[24$", KEYC_F12 | 0x800000000000ULL}, {"\033[2$", KEYC_IC | 0x800000000000ULL}, {"\033[3$", KEYC_DC | 0x800000000000ULL}, {"\033[7$", KEYC_HOME | 0x800000000000ULL}, {"\033[8$", KEYC_END | 0x800000000000ULL}, {"\033[6$", KEYC_NPAGE | 0x800000000000ULL}, {"\033[5$", KEYC_PPAGE | 0x800000000000ULL}, {"\033[11@", (KEYC_F1 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[12@", (KEYC_F2 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[13@", (KEYC_F3 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[14@", (KEYC_F4 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[15@", (KEYC_F5 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[17@", (KEYC_F6 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[18@", (KEYC_F7 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[19@", (KEYC_F8 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[20@", (KEYC_F9 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[21@", (KEYC_F10 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[23@", (KEYC_F11 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[24@", (KEYC_F12 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[2@", (KEYC_IC | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[3@", (KEYC_DC | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[7@", (KEYC_HOME | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[8@", (KEYC_END | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[6@", (KEYC_NPAGE | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[5@", (KEYC_PPAGE | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[I", KEYC_FOCUS_IN}, {"\033[O", KEYC_FOCUS_OUT}, {"\033[200~", KEYC_PASTE_START}, {"\033[201~", KEYC_PASTE_END}}
----------------------------
static void tty_keys_add(struct tty *tty, const char *s, key_code key)
{
  struct tty_key *tk;
  unsigned int tk_idx = 0;
  size_t size;
  const char *keystr;
  unsigned int keystr_idx = 0;
  keystr_idx = key_string_lookup_key(key);
  if ((tk_idx = tty_keys_find(tty, s, strlen(s), &size)) == 0)
  {
    log_debug("new key %s: 0x%llx (%s)", s, key, keystr);
    tty_keys_add1(&tty->key_tree, s, key);
  }
  else
  {
    log_debug("replacing key %s: 0x%llx (%s)", s, key, keystr);
    tk->key = key;
  }
}


----------------------------
void tty_keys_free(struct tty *tty)
{
  tty_keys_free1(tty->key_tree);
}


----------------------------
static const struct tty_default_key_code tty_default_code_keys[] = {{TTYC_KF1, KEYC_F1}, {TTYC_KF2, KEYC_F2}, {TTYC_KF3, KEYC_F3}, {TTYC_KF4, KEYC_F4}, {TTYC_KF5, KEYC_F5}, {TTYC_KF6, KEYC_F6}, {TTYC_KF7, KEYC_F7}, {TTYC_KF8, KEYC_F8}, {TTYC_KF9, KEYC_F9}, {TTYC_KF10, KEYC_F10}, {TTYC_KF11, KEYC_F11}, {TTYC_KF12, KEYC_F12}, {TTYC_KF13, KEYC_F1 | 0x800000000000ULL}, {TTYC_KF14, KEYC_F2 | 0x800000000000ULL}, {TTYC_KF15, KEYC_F3 | 0x800000000000ULL}, {TTYC_KF16, KEYC_F4 | 0x800000000000ULL}, {TTYC_KF17, KEYC_F5 | 0x800000000000ULL}, {TTYC_KF18, KEYC_F6 | 0x800000000000ULL}, {TTYC_KF19, KEYC_F7 | 0x800000000000ULL}, {TTYC_KF20, KEYC_F8 | 0x800000000000ULL}, {TTYC_KF21, KEYC_F9 | 0x800000000000ULL}, {TTYC_KF22, KEYC_F10 | 0x800000000000ULL}, {TTYC_KF23, KEYC_F11 | 0x800000000000ULL}, {TTYC_KF24, KEYC_F12 | 0x800000000000ULL}, {TTYC_KF25, KEYC_F1 | 0x400000000000ULL}, {TTYC_KF26, KEYC_F2 | 0x400000000000ULL}, {TTYC_KF27, KEYC_F3 | 0x400000000000ULL}, {TTYC_KF28, KEYC_F4 | 0x400000000000ULL}, {TTYC_KF29, KEYC_F5 | 0x400000000000ULL}, {TTYC_KF30, KEYC_F6 | 0x400000000000ULL}, {TTYC_KF31, KEYC_F7 | 0x400000000000ULL}, {TTYC_KF32, KEYC_F8 | 0x400000000000ULL}, {TTYC_KF33, KEYC_F9 | 0x400000000000ULL}, {TTYC_KF34, KEYC_F10 | 0x400000000000ULL}, {TTYC_KF35, KEYC_F11 | 0x400000000000ULL}, {TTYC_KF36, KEYC_F12 | 0x400000000000ULL}, {TTYC_KF37, (KEYC_F1 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF38, (KEYC_F2 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF39, (KEYC_F3 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF40, (KEYC_F4 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF41, (KEYC_F5 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF42, (KEYC_F6 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF43, (KEYC_F7 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF44, (KEYC_F8 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF45, (KEYC_F9 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF46, (KEYC_F10 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF47, (KEYC_F11 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF48, (KEYC_F12 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF49, KEYC_F1 | 0x200000000000ULL}, {TTYC_KF50, KEYC_F2 | 0x200000000000ULL}, {TTYC_KF51, KEYC_F3 | 0x200000000000ULL}, {TTYC_KF52, KEYC_F4 | 0x200000000000ULL}, {TTYC_KF53, KEYC_F5 | 0x200000000000ULL}, {TTYC_KF54, KEYC_F6 | 0x200000000000ULL}, {TTYC_KF55, KEYC_F7 | 0x200000000000ULL}, {TTYC_KF56, KEYC_F8 | 0x200000000000ULL}, {TTYC_KF57, KEYC_F9 | 0x200000000000ULL}, {TTYC_KF58, KEYC_F10 | 0x200000000000ULL}, {TTYC_KF59, KEYC_F11 | 0x200000000000ULL}, {TTYC_KF60, KEYC_F12 | 0x200000000000ULL}, {TTYC_KF61, (KEYC_F1 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KF62, (KEYC_F2 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KF63, (KEYC_F3 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KICH1, KEYC_IC}, {TTYC_KDCH1, KEYC_DC}, {TTYC_KHOME, KEYC_HOME}, {TTYC_KEND, KEYC_END}, {TTYC_KNP, KEYC_NPAGE}, {TTYC_KPP, KEYC_PPAGE}, {TTYC_KCBT, KEYC_BTAB}, {TTYC_KCUU1, KEYC_UP}, {TTYC_KCUD1, KEYC_DOWN}, {TTYC_KCUB1, KEYC_LEFT}, {TTYC_KCUF1, KEYC_RIGHT}, {TTYC_KDC2, (KEYC_DC | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC3, (KEYC_DC | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC4, ((KEYC_DC | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC5, (KEYC_DC | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC6, ((KEYC_DC | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC7, ((KEYC_DC | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIND, (KEYC_DOWN | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN2, (KEYC_DOWN | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN3, (KEYC_DOWN | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN4, ((KEYC_DOWN | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN5, (KEYC_DOWN | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN6, ((KEYC_DOWN | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN7, ((KEYC_DOWN | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND2, (KEYC_END | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND3, (KEYC_END | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND4, ((KEYC_END | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND5, (KEYC_END | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND6, ((KEYC_END | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND7, ((KEYC_END | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM2, (KEYC_HOME | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM3, (KEYC_HOME | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM4, ((KEYC_HOME | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM5, (KEYC_HOME | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM6, ((KEYC_HOME | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM7, ((KEYC_HOME | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC2, (KEYC_IC | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC3, (KEYC_IC | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC4, ((KEYC_IC | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC5, (KEYC_IC | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC6, ((KEYC_IC | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC7, ((KEYC_IC | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT2, (KEYC_LEFT | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT3, (KEYC_LEFT | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT4, ((KEYC_LEFT | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT5, (KEYC_LEFT | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT6, ((KEYC_LEFT | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT7, ((KEYC_LEFT | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT2, (KEYC_NPAGE | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT3, (KEYC_NPAGE | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT4, ((KEYC_NPAGE | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT5, (KEYC_NPAGE | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT6, ((KEYC_NPAGE | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT7, ((KEYC_NPAGE | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV2, (KEYC_PPAGE | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV3, (KEYC_PPAGE | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV4, ((KEYC_PPAGE | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV5, (KEYC_PPAGE | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV6, ((KEYC_PPAGE | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV7, ((KEYC_PPAGE | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT2, (KEYC_RIGHT | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT3, (KEYC_RIGHT | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT4, ((KEYC_RIGHT | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT5, (KEYC_RIGHT | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT6, ((KEYC_RIGHT | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT7, ((KEYC_RIGHT | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRI, (KEYC_UP | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP2, (KEYC_UP | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP3, (KEYC_UP | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP4, ((KEYC_UP | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP5, (KEYC_UP | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP6, ((KEYC_UP | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP7, ((KEYC_UP | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}}
----------------------------
int options_array_size(struct options_entry *o, u_int *size)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (size != 0)
  {
    *size = o->arraysize;
  }
  return 0;
}


----------------------------
struct tty_default_key_raw
{
  const char *string;
  key_code key;
}
----------------------------
const char *tty_term_string(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return "";
  }
  if (term->codes[code].type != TTYCODE_STRING)
  {
    fatalx("not a string: %d", code);
  }
  return term->codes[code].value.string;
}


----------------------------
None
----------------------------
None
----------------------------
***/


