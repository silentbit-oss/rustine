static size_t input_split2(u_int c, u_char *dst)
{
  if (c > 0x7f)
  {
    dst[0] = (c >> 6) | 0xc0;
    dst[1] = (c & 0x3f) | 0x80;
    return 2;
  }
  dst[0] = c;
  return 1;
}


/*** DEPENDENCIES:
***/


static void input_key_mouse(struct window_pane *wp, struct mouse_event *m)
{
  struct screen *s = wp->screen;
  int mode = s->mode;
  char buf[40];
  size_t len;
  u_int x;
  u_int y;
  if ((mode & ((0x20 | 0x40) | 0x1000)) == 0)
  {
    return;
  }
  if (!window_pane_visible(wp))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  if ((m->b & 32) && ((mode & (0x40 | 0x1000)) == 0))
  {
    return;
  }
  if (m->sgr_type != ' ')
  {
    if (((m->sgr_b & 32) && ((m->sgr_b & 3) == 3)) && ((~mode) & 0x1000))
    {
      return;
    }
  }
  else
  {
    if ((((m->b & 32) && ((m->b & 3) == 3)) && ((m->lb & 3) == 3)) && ((~mode) & 0x1000))
    {
      return;
    }
  }
  if ((m->sgr_type != ' ') && (s->mode & 0x200))
  {
    len = xsnprintf(buf, sizeof(buf), "\033[<%u;%u;%u%c", m->sgr_b, x + 1, y + 1, m->sgr_type);
  }
  else
    if (s->mode & 0x100)
  {
    if (((m->b > (0x7ff - 32)) || (x > (0x7ff - 33))) || (y > (0x7ff - 33)))
    {
      return;
    }
    len = xsnprintf(buf, sizeof(buf), "\033[M");
    len += input_split2(m->b + 32, &buf[len]);
    len += input_split2(x + 33, &buf[len]);
    len += input_split2(y + 33, &buf[len]);
  }
  else
  {
    if (m->b > 223)
    {
      return;
    }
    len = xsnprintf(buf, sizeof(buf), "\033[M");
    buf[len] = m->b + 32;
    len += 1;
    buf[len] = x + 33;
    len += 1;
    buf[len] = y + 33;
    len += 1;
  }
  log_debug("writing mouse %.*s to %%%u", (int) len, buf, wp->id);
  bufferevent_write(wp->event, buf, len);
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
static size_t input_split2(u_int c, u_char *dst)
{
  if (c > 0x7f)
  {
    dst[0] = (c >> 6) | 0xc0;
    dst[1] = (c & 0x3f) | 0x80;
    return 2;
  }
  dst[0] = c;
  return 1;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
}


----------------------------
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
None
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


void input_key(struct window_pane *wp, key_code key, struct mouse_event *m)
{
  const struct input_key_ent *ike;
  unsigned int ike_idx = 0;
  u_int i;
  size_t dlen;
  char *out;
  unsigned int out_idx = 0;
  key_code justkey;
  struct utf8_data ud;
  log_debug("writing key 0x%llx (%s) to %%%u", key, key_string_lookup_key(key), wp->id);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    if (((m != 0) && (m->wp != (-1))) && (((u_int) m->wp) == wp->id))
    {
      input_key_mouse(wp, m);
    }
    return;
  }
  justkey = key & (~(0x1000000000000ULL | 0x200000000000ULL));
  if (justkey <= 0x7f)
  {
    if (key & 0x200000000000ULL)
    {
      bufferevent_write(wp->event, "\033", 1);
    }
    ud.data[0] = justkey;
    bufferevent_write(wp->event, &ud.data[0], 1);
    return;
  }
  if ((justkey > 0x7f) && (justkey < 0x000010000000ULL))
  {
    if (utf8_split(justkey, &ud) != UTF8_DONE)
    {
      return;
    }
    if (key & 0x200000000000ULL)
    {
      bufferevent_write(wp->event, "\033", 1);
    }
    bufferevent_write(wp->event, ud.data, ud.size);
    return;
  }
  if (options_get_number(wp->window->options, "xterm-keys"))
  {
    if ((out_idx = xterm_keys_lookup(key)) != 0)
    {
      bufferevent_write(wp->event, out, strlen(out));
      free(out);
      return;
    }
  }
  key &= ~0x1000000000000ULL;
  for (i = 0; i < ((sizeof(input_keys)) / (sizeof(input_keys[0]))); i += 1)
  {
    ike_idx = &input_keys[i];
    if ((ike->flags & 0x1) && (!(wp->screen->mode & 0x8)))
    {
      continue;
    }
    if ((ike->flags & 0x2) && (!(wp->screen->mode & 0x4)))
    {
      continue;
    }
    if ((key & 0x200000000000ULL) && ((ike->key | 0x200000000000ULL) == key))
    {
      break;
    }
    if (ike->key == key)
    {
      break;
    }
  }

  if (i == ((sizeof(input_keys)) / (sizeof(input_keys[0]))))
  {
    log_debug("key 0x%llx missing", key);
    return;
  }
  dlen = strlen(ike->data);
  log_debug("found key 0x%llx: \"%s\"", key, ike->data);
  if (key & 0x200000000000ULL)
  {
    bufferevent_write(wp->event, "\033", 1);
  }
  bufferevent_write(wp->event, ike->data, dlen);
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
static const struct input_key_ent input_keys[] = {{KEYC_BSPACE, "\177", 0}, {KEYC_PASTE_START, "\033[200~", 0}, {KEYC_PASTE_END, "\033[201~", 0}, {KEYC_F1, "\033OP", 0}, {KEYC_F2, "\033OQ", 0}, {KEYC_F3, "\033OR", 0}, {KEYC_F4, "\033OS", 0}, {KEYC_F5, "\033[15~", 0}, {KEYC_F6, "\033[17~", 0}, {KEYC_F7, "\033[18~", 0}, {KEYC_F8, "\033[19~", 0}, {KEYC_F9, "\033[20~", 0}, {KEYC_F10, "\033[21~", 0}, {KEYC_F11, "\033[23~", 0}, {KEYC_F12, "\033[24~", 0}, {KEYC_F1 | 0x800000000000ULL, "\033[25~", 0}, {KEYC_F2 | 0x800000000000ULL, "\033[26~", 0}, {KEYC_F3 | 0x800000000000ULL, "\033[28~", 0}, {KEYC_F4 | 0x800000000000ULL, "\033[29~", 0}, {KEYC_F5 | 0x800000000000ULL, "\033[31~", 0}, {KEYC_F6 | 0x800000000000ULL, "\033[32~", 0}, {KEYC_F7 | 0x800000000000ULL, "\033[33~", 0}, {KEYC_F8 | 0x800000000000ULL, "\033[34~", 0}, {KEYC_IC, "\033[2~", 0}, {KEYC_DC, "\033[3~", 0}, {KEYC_HOME, "\033[1~", 0}, {KEYC_END, "\033[4~", 0}, {KEYC_NPAGE, "\033[6~", 0}, {KEYC_PPAGE, "\033[5~", 0}, {KEYC_BTAB, "\033[Z", 0}, {KEYC_UP | 0x400000000000ULL, "\033[A", 0x2}, {KEYC_DOWN | 0x400000000000ULL, "\033[B", 0x2}, {KEYC_RIGHT | 0x400000000000ULL, "\033[C", 0x2}, {KEYC_LEFT | 0x400000000000ULL, "\033[D", 0x2}, {KEYC_UP, "\033OA", 0x2}, {KEYC_DOWN, "\033OB", 0x2}, {KEYC_RIGHT, "\033OC", 0x2}, {KEYC_LEFT, "\033OD", 0x2}, {KEYC_UP | 0x400000000000ULL, "\033OA", 0}, {KEYC_DOWN | 0x400000000000ULL, "\033OB", 0}, {KEYC_RIGHT | 0x400000000000ULL, "\033OC", 0}, {KEYC_LEFT | 0x400000000000ULL, "\033OD", 0}, {KEYC_UP, "\033[A", 0}, {KEYC_DOWN, "\033[B", 0}, {KEYC_RIGHT, "\033[C", 0}, {KEYC_LEFT, "\033[D", 0}, {KEYC_KP_SLASH, "\033Oo", 0x1}, {KEYC_KP_STAR, "\033Oj", 0x1}, {KEYC_KP_MINUS, "\033Om", 0x1}, {KEYC_KP_SEVEN, "\033Ow", 0x1}, {KEYC_KP_EIGHT, "\033Ox", 0x1}, {KEYC_KP_NINE, "\033Oy", 0x1}, {KEYC_KP_PLUS, "\033Ok", 0x1}, {KEYC_KP_FOUR, "\033Ot", 0x1}, {KEYC_KP_FIVE, "\033Ou", 0x1}, {KEYC_KP_SIX, "\033Ov", 0x1}, {KEYC_KP_ONE, "\033Oq", 0x1}, {KEYC_KP_TWO, "\033Or", 0x1}, {KEYC_KP_THREE, "\033Os", 0x1}, {KEYC_KP_ENTER, "\033OM", 0x1}, {KEYC_KP_ZERO, "\033Op", 0x1}, {KEYC_KP_PERIOD, "\033On", 0x1}, {KEYC_KP_SLASH, "/", 0}, {KEYC_KP_STAR, "*", 0}, {KEYC_KP_MINUS, "-", 0}, {KEYC_KP_SEVEN, "7", 0}, {KEYC_KP_EIGHT, "8", 0}, {KEYC_KP_NINE, "9", 0}, {KEYC_KP_PLUS, "+", 0}, {KEYC_KP_FOUR, "4", 0}, {KEYC_KP_FIVE, "5", 0}, {KEYC_KP_SIX, "6", 0}, {KEYC_KP_ONE, "1", 0}, {KEYC_KP_TWO, "2", 0}, {KEYC_KP_THREE, "3", 0}, {KEYC_KP_ENTER, "\n", 0}, {KEYC_KP_ZERO, "0", 0}, {KEYC_KP_PERIOD, ".", 0}}
----------------------------
typedef unsigned long long key_code
----------------------------
struct input_key_ent
{
  key_code key;
  const char *data;
  int flags;
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
static void input_key_mouse(struct window_pane *wp, struct mouse_event *m)
{
  struct screen *s = wp->screen;
  int mode = s->mode;
  char buf[40];
  size_t len;
  u_int x;
  u_int y;
  if ((mode & ((0x20 | 0x40) | 0x1000)) == 0)
  {
    return;
  }
  if (!window_pane_visible(wp))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  if ((m->b & 32) && ((mode & (0x40 | 0x1000)) == 0))
  {
    return;
  }
  if (m->sgr_type != ' ')
  {
    if (((m->sgr_b & 32) && ((m->sgr_b & 3) == 3)) && ((~mode) & 0x1000))
    {
      return;
    }
  }
  else
  {
    if ((((m->b & 32) && ((m->b & 3) == 3)) && ((m->lb & 3) == 3)) && ((~mode) & 0x1000))
    {
      return;
    }
  }
  if ((m->sgr_type != ' ') && (s->mode & 0x200))
  {
    len = xsnprintf(buf, sizeof(buf), "\033[<%u;%u;%u%c", m->sgr_b, x + 1, y + 1, m->sgr_type);
  }
  else
    if (s->mode & 0x100)
  {
    if (((m->b > (0x7ff - 32)) || (x > (0x7ff - 33))) || (y > (0x7ff - 33)))
    {
      return;
    }
    len = xsnprintf(buf, sizeof(buf), "\033[M");
    len += input_split2(m->b + 32, &buf[len]);
    len += input_split2(x + 33, &buf[len]);
    len += input_split2(y + 33, &buf[len]);
  }
  else
  {
    if (m->b > 223)
    {
      return;
    }
    len = xsnprintf(buf, sizeof(buf), "\033[M");
    buf[len] = m->b + 32;
    len += 1;
    buf[len] = x + 33;
    len += 1;
    buf[len] = y + 33;
    len += 1;
  }
  log_debug("writing mouse %.*s to %%%u", (int) len, buf, wp->id);
  bufferevent_write(wp->event, buf, len);
}


----------------------------
char *xterm_keys_lookup(key_code key)
{
  const struct xterm_keys_entry *entry;
  unsigned int entry_idx = 0;
  u_int i;
  key_code modifiers;
  char *out;
  unsigned int out_idx = 0;
  modifiers = 1;
  if (key & 0x800000000000ULL)
  {
    modifiers += 1;
  }
  if (key & 0x200000000000ULL)
  {
    modifiers += 2;
  }
  if (key & 0x400000000000ULL)
  {
    modifiers += 4;
  }
  if (modifiers == 1)
  {
    return 0;
  }
  if ((key & (0x200000000000ULL | 0x1000000000000ULL)) == 0x200000000000ULL)
  {
    return 0;
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))); i += 1)
  {
    entry_idx = &xterm_keys_table[i];
    if (key == entry->key)
    {
      break;
    }
  }

  if (i == ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))))
  {
    return 0;
  }
  out_idx = xstrdup(entry->template);
  out[strcspn(out, "_") + out_idx] = '0' + modifiers;
  return out;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
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


----------------------------
None
----------------------------
***/


