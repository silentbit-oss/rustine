// element in merge of:  tty_keys_callback,tty_keys_next
static void tty_keys_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  if (tty->flags & 0x4)
  {
    while (tty_keys_next(tty))
    {
      ;
    }

  }
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  tty_keys_callback,tty_keys_next
key_code tty_keys_next(struct tty *tty)
{
  struct client *c = tty->client;
  struct timeval tv;
  const char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  size_t size;
  cc_t bspace;
  int delay;
  int expired = 0;
  int n;
  key_code key;
  buf_idx = EVBUFFER_DATA(tty->in);
  len = EVBUFFER_LENGTH(tty->in);
  if (len == 0)
  {
    return 0;
  }
  log_debug("%s: keys are %zu (%.*s)", c->name, len, (int) len, buf);
  switch (tty_keys_device_attributes(tty, buf, len, &size))
  {
    case 0:
    {
      key = 0xfffe00000000ULL;
      goto complete_key;
    }

    case -1:
    {
      break;
    }

    case 1:
    {
      goto partial_key;
    }

  }

  switch (tty_keys_mouse(tty, buf, len, &size))
  {
    case 0:
    {
      key = KEYC_MOUSE;
      goto complete_key;
    }

    case -1:
    {
      break;
    }

    case -2:
    {
      key = KEYC_MOUSE;
      goto discard_key;
    }

    case 1:
    {
      goto partial_key;
    }

  }

  first_key:
  n = tty_keys_next1(tty, buf, len, &key, &size, expired);

  if (n == 0)
  {
    goto complete_key;
  }
  if (n == 1)
  {
    goto partial_key;
  }
  if (buf[buf_idx] == '\033')
  {
    helper_tty_keys_next_1(&size, &n, &key, tty, buf, buf_idx, len, expired);
  }
  if ((buf[buf_idx] == '\033') && (len >= 2))
  {
    key = ((u_char) buf[1 + buf_idx]) | 0x200000000000ULL;
    size = 2;
  }
  else
  {
    key = (u_char) buf[0 + buf_idx];
    size = 1;
  }
  goto complete_key;
  partial_key:
  log_debug("%s: partial key %.*s", c->name, (int) len, buf);

  if (tty->flags & 0x4)
  {
    if (evtimer_initialized(&tty->key_timer) && (!evtimer_pending(&tty->key_timer, 0)))
    {
      expired = 1;
      goto first_key;
    }
    return 0;
  }
  delay = options_get_number(global_options, "escape-time");
  tv.tv_sec = delay / 1000;
  tv.tv_usec = (delay % 1000) * 1000L;
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  evtimer_set(&tty->key_timer, tty_keys_callback, tty);
  evtimer_add(&tty->key_timer, &tv);
  tty->flags |= 0x4;
  return 0;
  complete_key:
  log_debug("%s: complete key %.*s %#llx", c->name, (int) size, buf, key);

  bspace = tty->tio.c_cc[VERASE];
  if ((bspace != _POSIX_VDISABLE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == bspace))
  {
    key = (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL)) | KEYC_BSPACE;
  }
  evbuffer_drain(tty->in, size);
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  tty->flags &= ~0x4;
  if (key == KEYC_FOCUS_OUT)
  {
    tty->client->flags &= ~0x8000;
    return 1;
  }
  else
    if (key == KEYC_FOCUS_IN)
  {
    tty->client->flags |= 0x8000;
    return 1;
  }
  if (key != 0xfffe00000000ULL)
  {
    server_client_handle_key(tty->client, key);
  }
  return 1;
  discard_key:
  log_debug("%s: discard key %.*s %#llx", c->name, (int) size, buf, key);

  evbuffer_drain(tty->in, size);
  return 1;
}


/*** DEPENDENCIES:
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


----------------------------
typedef unsigned long long key_code
----------------------------
void server_client_handle_key(struct client *c, key_code key)
{
  struct mouse_event *m = &c->tty.mouse;
  struct session *s = c->session;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct timeval tv;
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_table *first;
  unsigned int first_idx = 0;
  struct key_binding bd_find;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  int xtimeout;
  int flags;
  struct cmd_find_state fs;
  key_code key0;
  if ((s == 0) || ((c->flags & (0x200 | 0x40)) != 0))
  {
    return;
  }
  w_idx = s->curw->window;
  if (gettimeofday(&c->activity_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  session_update_activity(s, &c->activity_time);
  if (((c->flags & 0x100) && (key >= '0')) && (key <= '9'))
  {
    if (c->flags & 0x800)
    {
      return;
    }
    window_unzoom(w);
    wp_idx = window_pane_at_index(w, key - '0');
    if (((&wp[wp_idx]) != 0) && (!window_pane_visible(wp)))
    {
      wp_idx = 0;
    }
    server_client_clear_identify(c, wp);
    return;
  }
  if (!(c->flags & 0x800))
  {
    status_message_clear(c);
    server_client_clear_identify(c, 0);
  }
  if (c->prompt_string != 0)
  {
    if (c->flags & 0x800)
    {
      return;
    }
    if (status_prompt_key(c, key) == 0)
    {
      return;
    }
  }
  m->valid = 0;
  if (key == KEYC_MOUSE)
  {
    if (c->flags & 0x800)
    {
      return;
    }
    key = server_client_check_mouse(c);
    if (key == 0xfffe00000000ULL)
    {
      return;
    }
    m->valid = 1;
    m->key = key;
    if (key == KEYC_DRAGGING)
    {
      c->tty.mouse_drag_update(c, m);
      return;
    }
  }
  else
    m->valid = 0;
  if ((!(((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))) || (cmd_find_from_mouse(&fs, m, 0) != 0))
  {
    cmd_find_from_session(&fs, s, 0);
  }
  wp_idx = fs.wp_idx;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (!options_get_number(s->options, "mouse")))
  {
    goto forward;
  }
  if ((!(((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))) && server_client_assume_paste(s))
  {
    goto forward;
  }
  if (((server_client_is_default_key_table(c, c->keytable) && ((&wp[wp_idx]) != 0)) && (wp->mode != 0)) && (wp->mode->key_table != 0))
  {
    table_idx = key_bindings_get_table(wp->mode->key_table(wp), 1);
  }
  else
    table_idx = c->keytable;
  first_idx = &table[table_idx];
  retry:
  key0 = key & (~0x1000000000000ULL);

  if (((key0 == ((key_code) options_get_number(s->options, "prefix"))) || (key0 == ((key_code) options_get_number(s->options, "prefix2")))) && (strcmp(table->name, "prefix") != 0))
  {
    server_client_set_key_table(c, "prefix");
    server_status_client(c);
    return;
  }
  flags = c->flags;
  if ((&wp[wp_idx]) == 0)
  {
    log_debug("key table %s (no pane)", table->name);
  }
  else
    log_debug("key table %s (pane %%%u)", table->name, wp->id);
  if (c->flags & 0x20)
  {
    log_debug("currently repeating");
  }
  bd_find.key = key0;
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) != 0)
  {
    helper_server_client_handle_key_1(&tv, &table_idx, &xtimeout, c, m, s, table, bd, fs);
  }
  log_debug("not found in key table %s", table->name);
  if ((!server_client_is_default_key_table(c, table)) || (c->flags & 0x20))
  {
    server_client_set_key_table(c, 0);
    c->flags &= ~0x20;
    server_status_client(c);
    table_idx = c->keytable;
    goto retry;
  }
  if (((&first[first_idx]) != (&table[table_idx])) && ((~flags) & 0x20))
  {
    server_client_set_key_table(c, 0);
    server_status_client(c);
    return;
  }
  forward:
  if (c->flags & 0x800)
  {
    return;
  }

  if ((&wp[wp_idx]) != 0)
  {
    window_pane_key(wp, c, s, key, m);
  }
}


----------------------------
None
----------------------------
long long options_get_number(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  return o->number;
}


----------------------------
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


