static void server_client_free(int fd, short events, void *arg)
{
  struct client *c = arg;
  log_debug("free client %p (%d references)", c, c->references);
  if (!((&c->queue)->tqh_first == 0))
  {
    fatalx("queue not empty");
  }
  if (c->references == 0)
  {
    free((void *) c->name);
    free(c);
  }
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
None
----------------------------
***/


void server_client_unref(struct client *c)
{
  log_debug("unref client %p (%d references)", c, c->references);
  c->references -= 1;
  if (c->references == 0)
  {
    event_once(-1, EV_TIMEOUT, server_client_free, c, 0);
  }
}


/*** DEPENDENCIES:
static void server_client_free(int fd, short events, void *arg)
{
  struct client *c = arg;
  log_debug("free client %p (%d references)", c, c->references);
  if (!((&c->queue)->tqh_first == 0))
  {
    fatalx("queue not empty");
  }
  if (c->references == 0)
  {
    free((void *) c->name);
    free(c);
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


const char *server_client_get_key_table(struct client *c)
{
  struct session *s = c->session;
  const char *name;
  unsigned int name_idx = 0;
  if (s == 0)
  {
    return "root";
  }
  name_idx = options_get_string(s->options, "key-table");
  if (name[name_idx] == '\0')
  {
    return "root";
  }
  return name;
}


/*** DEPENDENCIES:
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


----------------------------
None
----------------------------
***/


static void server_client_click_timer(int fd, short events, void *data)
{
  struct client *c = data;
  c->flags &= ~(0x100000 | 0x200000);
}


/*** DEPENDENCIES:
None
----------------------------
***/


void server_client_clear_identify(struct client *c, struct window_pane *wp)
{
  if ((~c->flags) & 0x100)
  {
    return;
  }
  c->flags &= ~0x100;
  if (c->identify_callback != 0)
  {
    c->identify_callback(c, wp);
  }
  c->tty.flags &= ~(0x2 | 0x1);
  server_redraw_client(c);
}


/*** DEPENDENCIES:
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
None
----------------------------
***/


static void server_client_callback_identify(int fd, short events, void *data)
{
  server_client_clear_identify(data, 0);
}


/*** DEPENDENCIES:
void server_client_clear_identify(struct client *c, struct window_pane *wp)
{
  if ((~c->flags) & 0x100)
  {
    return;
  }
  c->flags &= ~0x100;
  if (c->identify_callback != 0)
  {
    c->identify_callback(c, wp);
  }
  c->tty.flags &= ~(0x2 | 0x1);
  server_redraw_client(c);
}


----------------------------
***/


static void server_client_redraw_timer(int fd, short events, void *data)
{
  log_debug("redraw timer fired");
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


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_1(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if ((b & 3) == 0)
  {
    if (where == PANE)
    {
      key = KEYC_WHEELUP_PANE;
    }
    if (where == STATUS)
    {
      key = KEYC_WHEELUP_STATUS;
    }
    if (where == BORDER)
    {
      key = KEYC_WHEELUP_BORDER;
    }
  }
  else
  {
    if (where == PANE)
    {
      key = KEYC_WHEELDOWN_PANE;
    }
    if (where == STATUS)
    {
      key = KEYC_WHEELDOWN_STATUS;
    }
    if (where == BORDER)
    {
      key = KEYC_WHEELDOWN_BORDER;
    }
  }
  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_3(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_4(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_5(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_6(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


u_int server_client_how_many(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  u_int n;
  n = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && ((~c->flags) & 0x1000))
    {
      n += 1;
    }
  }

  return n;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
None
----------------------------
***/


const char *server_client_get_cwd(struct client *c)
{
  struct session *s;
  unsigned int s_idx = 0;
  if (((c != 0) && (c->session == 0)) && (c->cwd != 0))
  {
    return c->cwd;
  }
  if (((c != 0) && ((s_idx = c->session) != 0)) && (s->cwd != 0))
  {
    return s->cwd;
  }
  return ".";
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
void helper_server_client_check_mouse_7(key_code * const key_ref, struct client * const c, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if (c->tty.mouse_drag_update != 0)
  {
    key = KEYC_DRAGGING;
  }
  else
  {
    switch (b & 3)
    {
      case 0:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG1_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG1_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG1_BORDER;
        }
        break;
      }

      case 1:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG2_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG2_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG2_BORDER;
        }
        break;
      }

      case 2:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG3_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG3_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG3_BORDER;
        }
        break;
      }

    }

  }
  c->tty.mouse_drag_flag = (b & 3) + 1;
  break;
  *key_ref = key;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


static void server_client_check_focus(struct window_pane *wp)
{
  struct client *c;
  unsigned int c_idx = 0;
  int push;
  push = wp->flags & 0x20;
  wp->flags &= ~0x20;
  if (!(wp->base.mode & 0x800))
  {
    return;
  }
  if (wp->window->active != wp)
  {
    goto not_focused;
  }
  if (wp->screen != (&wp->base))
  {
    goto not_focused;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session == 0) || (!(c->flags & 0x8000)))
    {
      continue;
    }
    if (c->session->flags & 0x1)
    {
      continue;
    }
    if (c->session->curw->window == wp->window)
    {
      goto focused;
    }
  }

  not_focused:
  if (push || (wp->flags & 0x4))
  {
    bufferevent_write(wp->event, "\033[O", 3);
  }

  wp->flags &= ~0x4;
  return;
  focused:
  if (push || (!(wp->flags & 0x4)))
  {
    bufferevent_write(wp->event, "\033[I", 3);
  }

  wp->flags |= 0x4;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
None
----------------------------
***/


static void server_client_reset_state(struct client *c)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp = w->active;
  struct window_pane *loop;
  unsigned int loop_idx = 0;
  struct screen *s = wp->screen;
  struct options *oo = c->session->options;
  int lines;
  int mode;
  if (c->flags & (0x2000 | 0x40))
  {
    return;
  }
  tty_region_off(&c->tty);
  tty_margin_off(&c->tty);
  if (status_at_line(c) != 0)
  {
    lines = 0;
  }
  else
    lines = status_line_size(c->session);
  if ((!window_pane_visible(wp)) || ((wp->yoff + s->cy) >= (c->tty.sy - lines)))
  {
    tty_cursor(&c->tty, 0, 0);
  }
  else
    tty_cursor(&c->tty, wp->xoff + s->cx, (lines + wp->yoff) + s->cy);
  mode = s->mode;
  if (options_get_number(oo, "mouse"))
  {
    mode &= ~((0x20 | 0x40) | 0x1000);
    for (loop_idx = (&w->panes)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
    {
      if (loop->screen->mode & 0x1000)
      {
        mode |= 0x1000;
      }
    }

    if ((~mode) & 0x1000)
    {
      mode |= 0x40;
    }
  }
  if (c->prompt_string != 0)
  {
    mode &= ~0x400;
  }
  tty_update_mode(&c->tty, mode, s);
  tty_reset(&c->tty);
}


/*** DEPENDENCIES:
void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
void tty_update_mode(struct tty *tty, int mode, struct screen *s)
{
  int changed;
  if ((s != 0) && (strcmp(s->ccolour, tty->ccolour) != 0))
  {
    tty_force_cursor_colour(tty, s->ccolour);
  }
  if (tty->flags & 0x1)
  {
    mode &= ~0x1;
  }
  changed = mode ^ tty->mode;
  if (changed & 0x80)
  {
    if (tty_term_has(tty->term, TTYC_CVVIS))
    {
      tty_putcode(tty, TTYC_CVVIS);
    }
    else
      tty_putcode(tty, TTYC_CNORM);
    changed |= 0x1;
  }
  if (changed & 0x1)
  {
    if (mode & 0x1)
    {
      tty_putcode(tty, TTYC_CNORM);
    }
    else
      tty_putcode(tty, TTYC_CIVIS);
  }
  if ((s != 0) && (tty->cstyle != s->cstyle))
  {
    if (tty_term_has(tty->term, TTYC_SS))
    {
      if ((s->cstyle == 0) && tty_term_has(tty->term, TTYC_SE))
      {
        tty_putcode(tty, TTYC_SE);
      }
      else
        tty_putcode1(tty, TTYC_SS, s->cstyle);
    }
    tty->cstyle = s->cstyle;
  }
  if (changed & ((0x20 | 0x40) | 0x1000))
  {
    helper_tty_update_mode_1(tty, mode);
  }
  if (changed & 0x400)
  {
    if (mode & 0x400)
    {
      tty_puts(tty, "\033[?2004h");
    }
    else
      tty_puts(tty, "\033[?2004l");
  }
  tty->mode = mode;
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
void tty_region_off(struct tty *tty)
{
  tty_region(tty, 0, tty->sy - 1);
}


----------------------------
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
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
int status_at_line(struct client *c)
{
  struct session *s = c->session;
  if (c->flags & 0x800000)
  {
    return -1;
  }
  if (s->statusat != 1)
  {
    return s->statusat;
  }
  return c->tty.sy - status_line_size(s);
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void server_client_set_title(struct client *c)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *title;
  unsigned int title_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  template_idx = options_get_string(s->options, "set-titles-string");
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  title_idx = format_expand_time(ft, template, time(0));
  if ((c->title == 0) || (strcmp(title, c->title) != 0))
  {
    free(c->title);
    c->title = xstrdup(title);
    tty_set_title(&c->tty, c->title);
  }
  free(title);
  format_free(ft);
}


/*** DEPENDENCIES:
void format_free(struct format_tree *ft)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe1;
  unsigned int fe1_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&ft->tree, -1); ((&fe[fe_idx]) != 0) && ((fe1_idx = format_entry_tree_RB_NEXT(fe), 1)); fe_idx = &fe1[fe1_idx])
  {
    format_entry_tree_RB_REMOVE(&ft->tree, fe);
    free(fe->value);
    free(fe->key);
    free(fe);
  }

  if (ft->client != 0)
  {
    server_client_unref(ft->client);
  }
  free(ft);
}


----------------------------
struct format_tree *format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  if (!event_initialized(&format_job_event))
  {
    evtimer_set(&format_job_event, format_job_timer, 0);
    format_job_timer(-1, 0, 0);
  }
  ft_idx = xcalloc(1, sizeof(*ft_idx));
  do
  {
    (&ft->tree)->rbh_root = 0;
  }
  while (0);
  if (c != 0)
  {
    ft->client = c;
    ft->client->references += 1;
  }
  ft->tag = tag;
  ft->flags = flags;
  format_add(ft, "version", "%s", VERSION);
  format_add_cb(ft, "host", format_cb_host);
  format_add_cb(ft, "host_short", format_cb_host_short);
  format_add_cb(ft, "pid", format_cb_pid);
  format_add(ft, "socket_path", "%s", socket_path);
  format_add_tv(ft, "start_time", &start_time);
  if (item != 0)
  {
    if (item->cmd != 0)
    {
      format_add(ft, "command", "%s", item->cmd->entry->name);
    }
    if ((item->shared != 0) && (item->shared->formats != 0))
    {
      format_merge(ft, item->shared->formats);
    }
  }
  return ft;
}


----------------------------
pub time: Time
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
void tty_set_title(struct tty *tty, const char *title)
{
  if ((!tty_term_has(tty->term, TTYC_TSL)) || (!tty_term_has(tty->term, TTYC_FSL)))
  {
    return;
  }
  tty_putcode(tty, TTYC_TSL);
  tty_puts(tty, title);
  tty_putcode(tty, TTYC_FSL);
}


----------------------------
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


----------------------------
char *format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
  struct tm *tm;
  unsigned int tm_idx = 0;
  char s[2048];
  if ((fmt == 0) || ((*fmt) == '\0'))
  {
    return xstrdup("");
  }
  tm_idx = localtime(&t);
  if (strftime(s, sizeof(s), fmt, tm) == 0)
  {
    return xstrdup("");
  }
  return format_expand(ft, s);
}


----------------------------
void format_defaults(struct format_tree *ft, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  unsigned int wp_idx = 0;
  unsigned int wl_idx = 0;
  unsigned int s_idx = 0;
  if (((c != 0) && ((&s[s_idx]) != 0)) && (c->session != (&s[s_idx])))
  {
    log_debug("%s: session does not match", __func__);
  }
  format_add(ft, "session_format", "%d", (&s[s_idx]) != 0);
  format_add(ft, "window_format", "%d", (&wl[wl_idx]) != 0);
  format_add(ft, "pane_format", "%d", (&wp[wp_idx]) != 0);
  if (((&s[s_idx]) == 0) && (c != 0))
  {
    s_idx = c->session;
  }
  if (((&wl[wl_idx]) == 0) && ((&s[s_idx]) != 0))
  {
    wl_idx = s->curw;
  }
  if (((&wp[wp_idx]) == 0) && ((&wl[wl_idx]) != 0))
  {
    wp_idx = wl->window->active;
  }
  if (c != 0)
  {
    format_defaults_client(ft, c);
  }
  if ((&s[s_idx]) != 0)
  {
    format_defaults_session(ft, s);
  }
  if ((&wl[wl_idx]) != 0)
  {
    format_defaults_winlink(ft, wl);
  }
  if ((&wp[wp_idx]) != 0)
  {
    format_defaults_pane(ft, wp);
  }
}


----------------------------
None
----------------------------
***/


static void server_client_check_redraw(struct client *c)
{
  struct session *s = c->session;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int needed;
  int flags;
  int masked;
  struct timeval tv = {.tv_usec = 1000};
  static struct event ev;
  size_t left;
  if (c->flags & (0x2000 | 0x40))
  {
    return;
  }
  needed = 0;
  if (c->flags & 0x8)
  {
    needed = 1;
  }
  else
  {
    for (wp_idx = (&c->session->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->flags & 0x1)
      {
        needed = 1;
        break;
      }
    }

  }
  if (needed && ((left = EVBUFFER_LENGTH(tty->out)) != 0))
  {
    log_debug("%s: redraw deferred (%zu left)", c->name, left);
    if (!evtimer_initialized(&ev))
    {
      evtimer_set(&ev, server_client_redraw_timer, 0);
    }
    if (!evtimer_pending(&ev, 0))
    {
      log_debug("redraw timer started");
      evtimer_add(&ev, &tv);
    }
    c->flags |= 0x8;
    return;
  }
  else
    if (needed)
  {
    log_debug("%s: redraw needed", c->name);
  }
  if (c->flags & (0x8 | 0x10))
  {
    if (options_get_number(s->options, "set-titles"))
    {
      server_client_set_title(c);
    }
    screen_redraw_update(c);
  }
  flags = tty->flags & ((0x80 | 0x2) | 0x1);
  tty->flags = (tty->flags & (~(0x80 | 0x2))) | 0x1;
  if (c->flags & 0x8)
  {
    tty_update_mode(tty, tty->mode, 0);
    screen_redraw_screen(c, 1, 1, 1);
    c->flags &= ~(0x10 | 0x400);
  }
  else
  {
    for (wp_idx = (&c->session->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->flags & 0x1)
      {
        tty_update_mode(tty, tty->mode, 0);
        screen_redraw_pane(c, wp);
      }
    }

  }
  masked = c->flags & (0x400 | 0x10);
  if (masked != 0)
  {
    tty_update_mode(tty, tty->mode, 0);
  }
  if (masked == 0x400)
  {
    screen_redraw_screen(c, 0, 0, 1);
  }
  else
    if (masked == 0x10)
  {
    screen_redraw_screen(c, 0, 1, 0);
  }
  else
    if (masked != 0)
  {
    screen_redraw_screen(c, 0, 1, 1);
  }
  tty->flags = (tty->flags & (~(0x2 | 0x1))) | flags;
  tty_update_mode(tty, tty->mode, 0);
  c->flags &= ~(((0x8 | 0x400) | 0x10) | 0x80000);
  if (needed)
  {
    c->redraw = EVBUFFER_LENGTH(tty->out);
    log_debug("%s: redraw added %zu bytes", c->name, c->redraw);
  }
}


/*** DEPENDENCIES:
void screen_redraw_pane(struct client *c, struct window_pane *wp)
{
  u_int i;
  u_int yoff;
  if (!window_pane_visible(wp))
  {
    return;
  }
  yoff = wp->yoff;
  if (status_at_line(c) == 0)
  {
    yoff += status_line_size(c->session);
  }
  log_debug("%s: redraw pane %%%u (at %u,%u)", c->name, wp->id, wp->xoff, yoff);
  for (i = 0; i < wp->sy; i += 1)
  {
    tty_draw_pane(&c->tty, wp, i, wp->xoff, yoff);
  }

  tty_reset(&c->tty);
}


----------------------------
void tty_update_mode(struct tty *tty, int mode, struct screen *s)
{
  int changed;
  if ((s != 0) && (strcmp(s->ccolour, tty->ccolour) != 0))
  {
    tty_force_cursor_colour(tty, s->ccolour);
  }
  if (tty->flags & 0x1)
  {
    mode &= ~0x1;
  }
  changed = mode ^ tty->mode;
  if (changed & 0x80)
  {
    if (tty_term_has(tty->term, TTYC_CVVIS))
    {
      tty_putcode(tty, TTYC_CVVIS);
    }
    else
      tty_putcode(tty, TTYC_CNORM);
    changed |= 0x1;
  }
  if (changed & 0x1)
  {
    if (mode & 0x1)
    {
      tty_putcode(tty, TTYC_CNORM);
    }
    else
      tty_putcode(tty, TTYC_CIVIS);
  }
  if ((s != 0) && (tty->cstyle != s->cstyle))
  {
    if (tty_term_has(tty->term, TTYC_SS))
    {
      if ((s->cstyle == 0) && tty_term_has(tty->term, TTYC_SE))
      {
        tty_putcode(tty, TTYC_SE);
      }
      else
        tty_putcode1(tty, TTYC_SS, s->cstyle);
    }
    tty->cstyle = s->cstyle;
  }
  if (changed & ((0x20 | 0x40) | 0x1000))
  {
    helper_tty_update_mode_1(tty, mode);
  }
  if (changed & 0x400)
  {
    if (mode & 0x400)
    {
      tty_puts(tty, "\033[?2004h");
    }
    else
      tty_puts(tty, "\033[?2004l");
  }
  tty->mode = mode;
}


----------------------------
static void server_client_set_title(struct client *c)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *title;
  unsigned int title_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  template_idx = options_get_string(s->options, "set-titles-string");
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  title_idx = format_expand_time(ft, template, time(0));
  if ((c->title == 0) || (strcmp(title, c->title) != 0))
  {
    free(c->title);
    c->title = xstrdup(title);
    tty_set_title(&c->tty, c->title);
  }
  free(title);
  format_free(ft);
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
void screen_redraw_screen(struct client *c, int draw_panes, int draw_status, int draw_borders)
{
  struct options *oo = c->session->options;
  struct tty *tty = &c->tty;
  struct window *w = c->session->curw->window;
  struct options *wo = w->options;
  u_int top;
  u_int lines;
  int position;
  int pane_status;
  if (c->flags & 0x40)
  {
    return;
  }
  if (c->flags & 0x800000)
  {
    lines = 0;
  }
  else
    lines = status_line_size(c->session);
  if ((c->message_string != 0) || (c->prompt_string != 0))
  {
    lines = (lines == 0) ? (1) : (lines);
  }
  position = options_get_number(oo, "status-position");
  if ((lines != 0) && (position == 0))
  {
    top = 1;
  }
  else
    top = 0;
  if (lines == 0)
  {
    draw_status = 0;
  }
  if (draw_borders)
  {
    pane_status = options_get_number(wo, "pane-border-status");
    screen_redraw_draw_borders(c, pane_status, lines, top);
    if (pane_status != 0)
    {
      screen_redraw_draw_pane_status(c, pane_status);
    }
  }
  if (draw_panes)
  {
    screen_redraw_draw_panes(c, lines, top);
  }
  if (draw_status)
  {
    screen_redraw_draw_status(c, lines, top);
  }
  tty_reset(tty);
}


----------------------------
void screen_redraw_update(struct client *c)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct options *wo = w->options;
  int redraw;
  if (c->message_string != 0)
  {
    redraw = status_message_redraw(c);
  }
  else
    if (c->prompt_string != 0)
  {
    redraw = status_prompt_redraw(c);
  }
  else
    redraw = status_redraw(c);
  if (!redraw)
  {
    c->flags &= ~0x10;
  }
  if (options_get_number(wo, "pane-border-status") != 0)
  {
    redraw = 0;
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (screen_redraw_make_pane_status(c, w, wp))
      {
        redraw = 1;
      }
    }

    if (redraw)
    {
      c->flags |= 0x400;
    }
  }
}


----------------------------
static void server_client_redraw_timer(int fd, short events, void *data)
{
  log_debug("redraw timer fired");
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


static void server_client_check_exit(struct client *c)
{
  if (!(c->flags & 0x4))
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stdin_data) != 0)
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stdout_data) != 0)
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stderr_data) != 0)
  {
    return;
  }
  if (c->flags & 0x80)
  {
    notify_client("client-detached", c);
  }
  proc_send(c->peer, MSG_EXIT, -1, &c->retval, sizeof(c->retval));
  c->flags &= ~0x4;
}


/*** DEPENDENCIES:
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


----------------------------
None
----------------------------
None
----------------------------
***/


static int server_client_resize_force(struct window_pane *wp)
{
  struct timeval tv = {.tv_usec = 100000};
  struct winsize ws;
  if (wp->flags & 0x10)
  {
    wp->flags &= ~0x10;
    return 0;
  }
  if ((((wp->sx != wp->osx) || (wp->sy != wp->osy)) || (wp->sx <= 1)) || (wp->sy <= 1))
  {
    return 0;
  }
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = wp->sx;
  ws.ws_row = wp->sy - 1;
  if ((wp->fd != (-1)) && (ioctl(wp->fd, TIOCSWINSZ, &ws) == (-1)))
  {
    fatal("ioctl failed");
  }
  log_debug("%s: %%%u forcing resize", __func__, wp->id);
  evtimer_add(&wp->resize_timer, &tv);
  wp->flags |= 0x10;
  return 1;
}


/*** DEPENDENCIES:
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
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


static void server_client_resize_event(int fd, short events, void *data)
{
  struct window_pane *wp = data;
  struct winsize ws;
  evtimer_del(&wp->resize_timer);
  if (!(wp->flags & 0x8))
  {
    return;
  }
  if (server_client_resize_force(wp))
  {
    return;
  }
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = wp->sx;
  ws.ws_row = wp->sy;
  if ((wp->fd != (-1)) && (ioctl(wp->fd, TIOCSWINSZ, &ws) == (-1)))
  {
    fatal("ioctl failed");
  }
  log_debug("%s: %%%u resize to %u,%u", __func__, wp->id, wp->sx, wp->sy);
  wp->flags &= ~0x8;
  wp->osx = wp->sx;
  wp->osy = wp->sy;
}


/*** DEPENDENCIES:
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
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
static int server_client_resize_force(struct window_pane *wp)
{
  struct timeval tv = {.tv_usec = 100000};
  struct winsize ws;
  if (wp->flags & 0x10)
  {
    wp->flags &= ~0x10;
    return 0;
  }
  if ((((wp->sx != wp->osx) || (wp->sy != wp->osy)) || (wp->sx <= 1)) || (wp->sy <= 1))
  {
    return 0;
  }
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = wp->sx;
  ws.ws_row = wp->sy - 1;
  if ((wp->fd != (-1)) && (ioctl(wp->fd, TIOCSWINSZ, &ws) == (-1)))
  {
    fatal("ioctl failed");
  }
  log_debug("%s: %%%u forcing resize", __func__, wp->id);
  evtimer_add(&wp->resize_timer, &tv);
  wp->flags |= 0x10;
  return 1;
}


----------------------------
None
----------------------------
***/


static void server_client_check_resize(struct window_pane *wp)
{
  struct timeval tv = {.tv_usec = 250000};
  if (!(wp->flags & 0x8))
  {
    return;
  }
  log_debug("%s: %%%u resize to %u,%u", __func__, wp->id, wp->sx, wp->sy);
  if (!event_initialized(&wp->resize_timer))
  {
    evtimer_set(&wp->resize_timer, server_client_resize_event, wp);
  }
  if (!evtimer_pending(&wp->resize_timer, 0))
  {
    server_client_resize_event(-1, 0, wp);
  }
  if ((wp->saved_grid != 0) && evtimer_pending(&wp->resize_timer, 0))
  {
    return;
  }
  evtimer_del(&wp->resize_timer);
  evtimer_add(&wp->resize_timer, &tv);
}


/*** DEPENDENCIES:
static void server_client_resize_event(int fd, short events, void *data)
{
  struct window_pane *wp = data;
  struct winsize ws;
  evtimer_del(&wp->resize_timer);
  if (!(wp->flags & 0x8))
  {
    return;
  }
  if (server_client_resize_force(wp))
  {
    return;
  }
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = wp->sx;
  ws.ws_row = wp->sy;
  if ((wp->fd != (-1)) && (ioctl(wp->fd, TIOCSWINSZ, &ws) == (-1)))
  {
    fatal("ioctl failed");
  }
  log_debug("%s: %%%u resize to %u,%u", __func__, wp->id, wp->sx, wp->sy);
  wp->flags &= ~0x8;
  wp->osx = wp->sx;
  wp->osy = wp->sy;
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


void server_client_loop(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int focus;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    server_client_check_exit(c);
    if (c->session != 0)
    {
      server_client_check_redraw(c);
      server_client_reset_state(c);
    }
  }

  focus = options_get_number(global_options, "focus-events");
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->fd != (-1))
      {
        if (focus)
        {
          server_client_check_focus(wp);
        }
        server_client_check_resize(wp);
      }
      wp->flags &= ~0x1;
    }

    check_window_name(w);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct window *windows_RB_NEXT(struct window *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
static void server_client_check_focus(struct window_pane *wp)
{
  struct client *c;
  unsigned int c_idx = 0;
  int push;
  push = wp->flags & 0x20;
  wp->flags &= ~0x20;
  if (!(wp->base.mode & 0x800))
  {
    return;
  }
  if (wp->window->active != wp)
  {
    goto not_focused;
  }
  if (wp->screen != (&wp->base))
  {
    goto not_focused;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session == 0) || (!(c->flags & 0x8000)))
    {
      continue;
    }
    if (c->session->flags & 0x1)
    {
      continue;
    }
    if (c->session->curw->window == wp->window)
    {
      goto focused;
    }
  }

  not_focused:
  if (push || (wp->flags & 0x4))
  {
    bufferevent_write(wp->event, "\033[O", 3);
  }

  wp->flags &= ~0x4;
  return;
  focused:
  if (push || (!(wp->flags & 0x4)))
  {
    bufferevent_write(wp->event, "\033[I", 3);
  }

  wp->flags |= 0x4;
}


----------------------------
struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}


----------------------------
static void server_client_reset_state(struct client *c)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp = w->active;
  struct window_pane *loop;
  unsigned int loop_idx = 0;
  struct screen *s = wp->screen;
  struct options *oo = c->session->options;
  int lines;
  int mode;
  if (c->flags & (0x2000 | 0x40))
  {
    return;
  }
  tty_region_off(&c->tty);
  tty_margin_off(&c->tty);
  if (status_at_line(c) != 0)
  {
    lines = 0;
  }
  else
    lines = status_line_size(c->session);
  if ((!window_pane_visible(wp)) || ((wp->yoff + s->cy) >= (c->tty.sy - lines)))
  {
    tty_cursor(&c->tty, 0, 0);
  }
  else
    tty_cursor(&c->tty, wp->xoff + s->cx, (lines + wp->yoff) + s->cy);
  mode = s->mode;
  if (options_get_number(oo, "mouse"))
  {
    mode &= ~((0x20 | 0x40) | 0x1000);
    for (loop_idx = (&w->panes)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
    {
      if (loop->screen->mode & 0x1000)
      {
        mode |= 0x1000;
      }
    }

    if ((~mode) & 0x1000)
    {
      mode |= 0x40;
    }
  }
  if (c->prompt_string != 0)
  {
    mode &= ~0x400;
  }
  tty_update_mode(&c->tty, mode, s);
  tty_reset(&c->tty);
}


----------------------------
static void server_client_check_redraw(struct client *c)
{
  struct session *s = c->session;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int needed;
  int flags;
  int masked;
  struct timeval tv = {.tv_usec = 1000};
  static struct event ev;
  size_t left;
  if (c->flags & (0x2000 | 0x40))
  {
    return;
  }
  needed = 0;
  if (c->flags & 0x8)
  {
    needed = 1;
  }
  else
  {
    for (wp_idx = (&c->session->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->flags & 0x1)
      {
        needed = 1;
        break;
      }
    }

  }
  if (needed && ((left = EVBUFFER_LENGTH(tty->out)) != 0))
  {
    log_debug("%s: redraw deferred (%zu left)", c->name, left);
    if (!evtimer_initialized(&ev))
    {
      evtimer_set(&ev, server_client_redraw_timer, 0);
    }
    if (!evtimer_pending(&ev, 0))
    {
      log_debug("redraw timer started");
      evtimer_add(&ev, &tv);
    }
    c->flags |= 0x8;
    return;
  }
  else
    if (needed)
  {
    log_debug("%s: redraw needed", c->name);
  }
  if (c->flags & (0x8 | 0x10))
  {
    if (options_get_number(s->options, "set-titles"))
    {
      server_client_set_title(c);
    }
    screen_redraw_update(c);
  }
  flags = tty->flags & ((0x80 | 0x2) | 0x1);
  tty->flags = (tty->flags & (~(0x80 | 0x2))) | 0x1;
  if (c->flags & 0x8)
  {
    tty_update_mode(tty, tty->mode, 0);
    screen_redraw_screen(c, 1, 1, 1);
    c->flags &= ~(0x10 | 0x400);
  }
  else
  {
    for (wp_idx = (&c->session->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->flags & 0x1)
      {
        tty_update_mode(tty, tty->mode, 0);
        screen_redraw_pane(c, wp);
      }
    }

  }
  masked = c->flags & (0x400 | 0x10);
  if (masked != 0)
  {
    tty_update_mode(tty, tty->mode, 0);
  }
  if (masked == 0x400)
  {
    screen_redraw_screen(c, 0, 0, 1);
  }
  else
    if (masked == 0x10)
  {
    screen_redraw_screen(c, 0, 1, 0);
  }
  else
    if (masked != 0)
  {
    screen_redraw_screen(c, 0, 1, 1);
  }
  tty->flags = (tty->flags & (~(0x2 | 0x1))) | flags;
  tty_update_mode(tty, tty->mode, 0);
  c->flags &= ~(((0x8 | 0x400) | 0x10) | 0x80000);
  if (needed)
  {
    c->redraw = EVBUFFER_LENGTH(tty->out);
    log_debug("%s: redraw added %zu bytes", c->name, c->redraw);
  }
}


----------------------------
static void server_client_check_exit(struct client *c)
{
  if (!(c->flags & 0x4))
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stdin_data) != 0)
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stdout_data) != 0)
  {
    return;
  }
  if (EVBUFFER_LENGTH(c->stderr_data) != 0)
  {
    return;
  }
  if (c->flags & 0x80)
  {
    notify_client("client-detached", c);
  }
  proc_send(c->peer, MSG_EXIT, -1, &c->retval, sizeof(c->retval));
  c->flags &= ~0x4;
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
void check_window_name(struct window *w)
{
  struct timeval tv;
  struct timeval next;
  char *name;
  unsigned int name_idx = 0;
  int left;
  if (w->active == 0)
  {
    return;
  }
  if (!options_get_number(w->options, "automatic-rename"))
  {
    return;
  }
  if ((~w->active->flags) & 0x80)
  {
    log_debug("@%u active pane not changed", w->id);
    return;
  }
  log_debug("@%u active pane changed", w->id);
  gettimeofday(&tv, 0);
  left = name_time_expired(w, &tv);
  if (left != 0)
  {
    if (!event_initialized(&w->name_event))
    {
      evtimer_set(&w->name_event, name_time_callback, w);
    }
    if (!evtimer_pending(&w->name_event, 0))
    {
      log_debug("@%u name timer queued (%d left)", w->id, left);
      timerclear(&next);
      next.tv_usec = left;
      event_add(&w->name_event, &next);
    }
    else
    {
      log_debug("@%u name timer already queued (%d left)", w->id, left);
    }
    return;
  }
  memcpy(&w->name_time, &tv, sizeof(w->name_time));
  if (event_initialized(&w->name_event))
  {
    evtimer_del(&w->name_event);
  }
  w->active->flags &= ~0x80;
  name_idx = format_window_name(w);
  if (strcmp(name, w->name) != 0)
  {
    log_debug("@%u new name %s (was %s)", w->id, name, w->name);
    window_set_name(w, name);
    server_status_window(w);
  }
  else
    log_debug("@%u name not changed (still %s)", w->id, w->name);
  free(name);
}


----------------------------
static void server_client_check_resize(struct window_pane *wp)
{
  struct timeval tv = {.tv_usec = 250000};
  if (!(wp->flags & 0x8))
  {
    return;
  }
  log_debug("%s: %%%u resize to %u,%u", __func__, wp->id, wp->sx, wp->sy);
  if (!event_initialized(&wp->resize_timer))
  {
    evtimer_set(&wp->resize_timer, server_client_resize_event, wp);
  }
  if (!evtimer_pending(&wp->resize_timer, 0))
  {
    server_client_resize_event(-1, 0, wp);
  }
  if ((wp->saved_grid != 0) && evtimer_pending(&wp->resize_timer, 0))
  {
    return;
  }
  evtimer_del(&wp->resize_timer);
  evtimer_add(&wp->resize_timer, &tv);
}


----------------------------
None
----------------------------
***/


// hint:  ['s_idx_ref is a mutable refrence to unsigned int']
void helper_server_client_dispatch_1(unsigned int * const s_idx_ref, struct client * const c, ssize_t datalen, struct session * const s)
{
  unsigned int s_idx = *s_idx_ref;
  if (datalen != 0)
  {
    fatalx("bad MSG_WAKEUP size");
  }
  if (!(c->flags & 0x40))
  {
    break;
  }
  c->flags &= ~0x40;
  if (c->tty.fd == (-1))
  {
    break;
  }
  s_idx = c->session;
  if (gettimeofday(&c->activity_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  tty_start_tty(&c->tty);
  server_redraw_client(c);
  recalculate_sizes();
  if ((&s[s_idx]) != 0)
  {
    session_update_activity(s, &c->activity_time);
  }
  break;
  *s_idx_ref = s_idx;
}


/*** DEPENDENCIES:
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
void recalculate_sizes(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int ssx;
  u_int ssy;
  u_int has;
  u_int limit;
  u_int lines;
  int flag;
  int is_zoomed;
  int forced;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    helper_recalculate_sizes_1(&c_idx, &ssx, &ssy, &lines, s, s_idx, c);
  }

  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    helper_recalculate_sizes_2(&s_idx, &wp_idx, &ssx, &ssy, &has, &limit, &flag, &is_zoomed, &forced, s, w, w_idx, wp);
  }

}


----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
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
void session_update_activity(struct session *s, struct timeval *from)
{
  struct timeval *last = &s->last_activity_time;
  struct timeval tv;
  memcpy(last, &s->activity_time, sizeof(*last));
  if (from == 0)
  {
    gettimeofday(&s->activity_time, 0);
  }
  else
    memcpy(&s->activity_time, from, sizeof(s->activity_time));
  log_debug("session %s activity %lld.%06d (last %lld.%06d)", s->name, (long long) s->activity_time.tv_sec, (int) s->activity_time.tv_usec, (long long) last->tv_sec, (int) last->tv_usec);
  if (evtimer_initialized(&s->lock_timer))
  {
    evtimer_del(&s->lock_timer);
  }
  else
    evtimer_set(&s->lock_timer, session_lock_timer, s);
  if ((~s->flags) & 0x1)
  {
    timerclear(&tv);
    tv.tv_sec = options_get_number(s->options, "lock-after-time");
    if (tv.tv_sec != 0)
    {
      evtimer_add(&s->lock_timer, &tv);
    }
  }
}


----------------------------
void tty_start_tty(struct tty *tty)
{
  struct client *c = tty->client;
  struct termios tio;
  if ((tty->fd != (-1)) && (tcgetattr(tty->fd, &tty->tio) == 0))
  {
    helper_tty_start_tty_1(&tio, tty);
  }
  tty_putcode(tty, TTYC_SMCUP);
  tty_putcode(tty, TTYC_SMKX);
  tty_putcode(tty, TTYC_CLEAR);
  if (tty_acs_needed(tty))
  {
    log_debug("%s: using capabilities for ACS", c->name);
    tty_putcode(tty, TTYC_ENACS);
  }
  else
    log_debug("%s: using UTF-8 for ACS", c->name);
  tty_putcode(tty, TTYC_CNORM);
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_puts(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (options_get_number(global_options, "focus-events"))
    {
      tty->flags |= 0x40;
      tty_puts(tty, "\033[?1004h");
    }
    tty_puts(tty, "\033[c");
  }
  tty->flags |= 0x10;
  tty_invalidate(tty);
  tty_force_cursor_colour(tty, "");
  tty->mouse_drag_flag = 0;
  tty->mouse_drag_update = 0;
  tty->mouse_drag_release = 0;
}


----------------------------
None
----------------------------
***/


static void server_client_dispatch_identify(struct client *c, struct imsg *imsg)
{
  const char *data;
  unsigned int data_idx = 0;
  const char *home;
  unsigned int home_idx = 0;
  size_t datalen;
  int flags;
  char *name;
  unsigned int name_idx = 0;
  if (c->flags & 0x40000)
  {
    fatalx("out-of-order identify message");
  }
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_IDENTIFY_FLAGS:
    {
      if (datalen != (sizeof(flags)))
      {
        fatalx("bad MSG_IDENTIFY_FLAGS size");
      }
      memcpy(&flags, data, sizeof(flags));
      c->flags |= flags;
      log_debug("client %p IDENTIFY_FLAGS %#x", c, flags);
      break;
    }

    case MSG_IDENTIFY_TERM:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_TERM string");
      }
      c->term = xstrdup(data);
      log_debug("client %p IDENTIFY_TERM %s", c, data);
      break;
    }

    case MSG_IDENTIFY_TTYNAME:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_TTYNAME string");
      }
      c->ttyname = xstrdup(data);
      log_debug("client %p IDENTIFY_TTYNAME %s", c, data);
      break;
    }

    case MSG_IDENTIFY_CWD:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_CWD string");
      }
      if (access(data, X_OK) == 0)
      {
        c->cwd = xstrdup(data);
      }
      else
        if ((home_idx = find_home()) != 0)
      {
        c->cwd = xstrdup(home);
      }
      else
        c->cwd = xstrdup("/");
      log_debug("client %p IDENTIFY_CWD %s", c, data);
      break;
    }

    case MSG_IDENTIFY_STDIN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_IDENTIFY_STDIN size");
      }
      c->fd = imsg->fd;
      log_debug("client %p IDENTIFY_STDIN %d", c, imsg->fd);
      break;
    }

    case MSG_IDENTIFY_ENVIRON:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_ENVIRON string");
      }
      if (strchr(data, '=') != 0)
      {
        environ_put(c->environ, data);
      }
      log_debug("client %p IDENTIFY_ENVIRON %s", c, data);
      break;
    }

    case MSG_IDENTIFY_CLIENTPID:
    {
      if (datalen != (sizeof(c->pid)))
      {
        fatalx("bad MSG_IDENTIFY_CLIENTPID size");
      }
      memcpy(&c->pid, data, sizeof(c->pid));
      log_debug("client %p IDENTIFY_CLIENTPID %ld", c, (long) c->pid);
      break;
    }

    default:
    {
      break;
    }

  }

  if (imsg->hdr.type != MSG_IDENTIFY_DONE)
  {
    return;
  }
  c->flags |= 0x40000;
  if ((*c->ttyname) != '\0')
  {
    name_idx = xstrdup(c->ttyname);
  }
  else
    xasprintf(&(&name[name_idx]), "client-%ld", (long) c->pid);
  c->name = &name[name_idx];
  log_debug("client %p name is %s", c, c->name);
  if (c->flags & 0x2000)
  {
    c->stdin_callback = control_callback;
    evbuffer_free(c->stderr_data);
    c->stderr_data = c->stdout_data;
    if (c->flags & 0x4000)
    {
      evbuffer_add_printf(c->stdout_data, "\033P1000p");
    }
    proc_send(c->peer, MSG_STDIN, -1, 0, 0);
    c->tty.fd = -1;
    close(c->fd);
    c->fd = -1;
    return;
  }
  if (c->fd == (-1))
  {
    return;
  }
  if (tty_init(&c->tty, c, c->fd, c->term) != 0)
  {
    close(c->fd);
    c->fd = -1;
    return;
  }
  if (c->flags & 0x10000)
  {
    c->tty.flags |= 0x8;
  }
  if (c->flags & 0x20000)
  {
    c->tty.term_flags |= 0x1;
  }
  tty_resize(&c->tty);
  if (!(c->flags & 0x2000))
  {
    c->flags |= 0x1;
  }
}


/*** DEPENDENCIES:
void tty_resize(struct tty *tty)
{
  struct client *c = tty->client;
  struct winsize ws;
  u_int sx;
  u_int sy;
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) != (-1))
  {
    sx = ws.ws_col;
    if (sx == 0)
    {
      sx = 80;
    }
    sy = ws.ws_row;
    if (sy == 0)
    {
      sy = 24;
    }
  }
  else
  {
    sx = 80;
    sy = 24;
  }
  log_debug("%s: %s now %ux%u", __func__, c->name, sx, sy);
  tty_set_size(tty, sx, sy);
  tty_invalidate(tty);
}


----------------------------
int tty_init(struct tty *tty, struct client *c, int fd, char *term)
{
  if (!isatty(fd))
  {
    return -1;
  }
  memset(tty, 0, sizeof(*tty));
  if ((term == 0) || ((*term) == '\0'))
  {
    tty->term_name = xstrdup("unknown");
  }
  else
    tty->term_name = xstrdup(term);
  tty->fd = fd;
  tty->client = c;
  tty->cstyle = 0;
  tty->ccolour = xstrdup("");
  tty->flags = 0;
  tty->term_flags = 0;
  tty->term_type = TTY_UNKNOWN;
  return 0;
}


----------------------------
const char *find_home(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  static const char *home;
  unsigned int home_idx = 0;
  if ((&home[home_idx]) != 0)
  {
    return home;
  }
  home_idx = getenv("HOME");
  if (((&home[home_idx]) == 0) || (home[home_idx] == '\0'))
  {
    pw_idx = getpwuid(getuid());
    if ((&pw[pw_idx]) != 0)
    {
      home_idx = pw->pw_dir;
    }
    else
      home_idx = 0;
  }
  return home;
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
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
void control_callback(struct client *c, int closed, void *data)
{
  char *line;
  unsigned int line_idx = 0;
  char *cause;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  if (closed)
  {
    c->flags |= 0x4;
  }
  for (;;)
  {
    line_idx = evbuffer_readln(c->stdin_data, 0, EVBUFFER_EOL_LF);
    if ((&line[line_idx]) == 0)
    {
      break;
    }
    if (line[line_idx] == '\0')
    {
      c->flags |= 0x4;
      break;
    }
    cmdlist_idx = cmd_string_parse(line, 0, 0, &cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      item_idx = cmdq_get_callback1("control_error", control_error, cause);
      cmdq_append(c, item);
    }
    else
    {
      for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
      {
        cmd->flags |= 0x1;
      }

      item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
      cmdq_append(c, item);
      cmd_list_free(cmdlist);
    }
    free(line);
  }

}


----------------------------
None
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
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
void environ_put(struct environ *env, const char *var)
{
  char *name;
  unsigned int name_idx = 0;
  char *value;
  unsigned int value_idx = 0;
  value_idx = strchr(var, '=');
  if ((&value[value_idx]) == 0)
  {
    return;
  }
  value_idx += 1;
  name_idx = xstrdup(var);
  name[strcspn(name, "=") + name_idx] = '\0';
  environ_set(env, name, "%s", value);
  free(name);
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


static enum cmd_retval server_client_command_done(struct cmdq_item *item, void *data)
{
  struct client *c = item->client;
  if ((~c->flags) & 0x80)
  {
    c->flags |= 0x4;
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
None
----------------------------
***/


static enum cmd_retval server_client_command_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void cmdq_error(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  va_list ap;
  char *msg;
  unsigned int msg_idx = 0;
  size_t msglen;
  char *tmp;
  unsigned int tmp_idx = 0;
  __builtin_va_start(ap);
  msglen = xvasprintf(&(&msg[msg_idx]), fmt, ap);
  ;
  log_debug("%s: %s", __func__, msg);
  if (c == 0)
  {
    cfg_add_cause("%s:%u: %s", cmd->file, cmd->line, msg);
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      tmp_idx = &msg[msg_idx];
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      msglen = strlen(msg);
    }
    evbuffer_add(c->stderr_data, msg, msglen);
    evbuffer_add(c->stderr_data, "\n", 1);
    server_client_push_stderr(c);
    c->retval = 1;
  }
  else
  {
    msg[msg_idx] = toupper((u_char) msg[msg_idx]);
    status_message_set(c, "%s", msg);
  }
  free(msg);
}


----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
None
----------------------------
***/


static void server_client_dispatch_command(struct client *c, struct imsg *imsg)
{
  struct msg_command_data data;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  unsigned int argv_idx = 0;
  char *cause;
  unsigned int cause_idx = 0;
  if (c->flags & 0x4)
  {
    return;
  }
  if ((imsg->hdr.len - (sizeof(struct imsg_hdr))) < (sizeof(data)))
  {
    fatalx("bad MSG_COMMAND size");
  }
  memcpy(&data, imsg->data, sizeof(data));
  buf_idx = ((char *) imsg->data) + (sizeof(data));
  len = (imsg->hdr.len - (sizeof(struct imsg_hdr))) - (sizeof(data));
  if ((len > 0) && (buf[(len - 1) + buf_idx] != '\0'))
  {
    fatalx("bad MSG_COMMAND string");
  }
  argc = data.argc;
  if (cmd_unpack_argv(buf, len, argc, &(&argv[argv_idx])) != 0)
  {
    cause_idx = xstrdup("command too long");
    goto error;
  }
  if (argc == 0)
  {
    argc = 1;
    argv_idx = xcalloc(1, sizeof(*argv_idx));
    argv[argv_idx] = xstrdup("new-session");
  }
  if ((cmdlist_idx = cmd_list_parse(argc, argv, 0, 0, &(&cause[cause_idx]))) == 0)
  {
    cmd_free_argv(argc, argv);
    goto error;
  }
  cmd_free_argv(argc, argv);
  cmdq_append(c, cmdq_get_command(cmdlist, 0, 0, 0));
  cmdq_append(c, cmdq_get_callback1("server_client_command_done", server_client_command_done, 0));
  cmd_list_free(cmdlist);
  return;
  error:
  cmdq_append(c, cmdq_get_callback1("server_client_command_error", server_client_command_error, cause));

  if ((&cmdlist[cmdlist_idx]) != 0)
  {
    cmd_list_free(cmdlist);
  }
  c->flags |= 0x4;
}


/*** DEPENDENCIES:
struct cmdq_item *cmdq_get_command(struct cmd_list *cmdlist, struct cmd_find_state *current, struct mouse_event *m, int flags)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  struct cmdq_item *first = 0;
  unsigned int first_idx = 0;
  struct cmdq_item *last = 0;
  unsigned int last_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  u_int group = cmdq_next_group();
  char *tmp;
  struct cmdq_shared *shared;
  unsigned int shared_idx = 0;
  shared_idx = xcalloc(1, sizeof(*shared_idx));
  if (current != 0)
  {
    cmd_find_copy_state(&shared->current, current);
  }
  else
    cmd_find_clear_state(&shared->current, 0);
  if (m != 0)
  {
    memcpy(&shared->mouse, m, sizeof(shared->mouse));
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    helper_cmdq_get_command_1(&flags, &item_idx, &first_idx, &last_idx, &group, cmdlist, item, first, last, cmd, cmd_idx, tmp, shared, shared_idx);
  }

  return first;
}


----------------------------
void cmd_list_free(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd *cmd1;
  unsigned int cmd1_idx = 0;
  if ((--cmdlist->references) != 0)
  {
    return;
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; ((&cmd[cmd_idx]) != 0) && ((cmd1_idx = cmd->qentry.tqe_next, 1)); cmd_idx = &cmd1[cmd1_idx])
  {
    do
    {
      if (cmd->qentry.tqe_next != 0)
      {
        cmd->qentry.tqe_next->qentry.tqe_prev = cmd->qentry.tqe_prev;
      }
      else
        (&cmdlist->list)->tqh_last = cmd->qentry.tqe_prev;
      *cmd->qentry.tqe_prev = cmd->qentry.tqe_next;
      ;
      ;
    }
    while (0);
    args_free(cmd->args);
    free(cmd->file);
    free(cmd);
  }

  free(cmdlist);
}


----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


----------------------------
void cmdq_append(struct client *c, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct cmdq_list *queue = cmdq_get(c);
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  do
  {
    next_idx = item->next_idx;
    item->next = 0;
    if (c != 0)
    {
      c->references += 1;
    }
    item->client = c;
    item->queue = queue;
    do
    {
      item->entry.tqe_next = 0;
      item->entry.tqe_prev = queue->tqh_last;
      *queue->tqh_last = &item[item_idx];
      queue->tqh_last = &item->entry.tqe_next;
    }
    while (0);
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


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
static enum cmd_retval server_client_command_done(struct cmdq_item *item, void *data)
{
  struct client *c = item->client;
  if ((~c->flags) & 0x80)
  {
    c->flags |= 0x4;
  }
  return CMD_RETURN_NORMAL;
}


----------------------------
struct msg_command_data
{
  int argc;
}
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
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
struct cmd_list *cmd_list_parse(int argc, char **argv, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  int i;
  int lastsplit;
  size_t arglen;
  size_t new_argc;
  char **copy_argv;
  unsigned int copy_argv_idx = 0;
  char **new_argv;
  unsigned int new_argv_idx = 0;
  copy_argv_idx = cmd_copy_argv(argc, argv);
  cmdlist_idx = xcalloc(1, sizeof(*cmdlist_idx));
  cmdlist->references = 1;
  do
  {
    (&cmdlist->list)->tqh_first = 0;
    (&cmdlist->list)->tqh_last = &(&cmdlist->list)->tqh_first;
  }
  while (0);
  lastsplit = 0;
  for (i = 0; i < argc; i += 1)
  {
    helper_cmd_list_parse_1(&cmd_idx, &i, &lastsplit, &arglen, &new_argc, &copy_argv_idx, &new_argv_idx, file, line, cause, cmdlist, cmd, copy_argv, new_argv);
  }

  if (lastsplit != argc)
  {
    cmd_idx = cmd_parse(argc - lastsplit, (&copy_argv[copy_argv_idx]) + lastsplit, file, line, cause);
    if ((&cmd[cmd_idx]) == 0)
    {
      goto bad;
    }
    do
    {
      cmd->qentry.tqe_next = 0;
      cmd->qentry.tqe_prev = (&cmdlist->list)->tqh_last;
      *(&cmdlist->list)->tqh_last = &cmd[cmd_idx];
      (&cmdlist->list)->tqh_last = &cmd->qentry.tqe_next;
    }
    while (0);
  }
  cmd_free_argv(argc, copy_argv);
  return cmdlist;
  bad:
  cmd_list_free(cmdlist);

  cmd_free_argv(argc, copy_argv);
  return 0;
}


----------------------------
static enum cmd_retval server_client_command_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
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
struct cmdq_item *cmdq_get_callback1(const char *name, cmdq_cb cb, void *data)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  char *tmp;
  xasprintf(&tmp, "callback[%s]", name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_CALLBACK;
  item->group = 0;
  item->flags = 0;
  item->cb = cb;
  item->data = data;
  return item;
}


----------------------------
int cmd_unpack_argv(char *buf, size_t len, int argc, char ***argv)
{
  unsigned int buf_idx = 0;
  int i;
  size_t arglen;
  if (argc == 0)
  {
    return 0;
  }
  *argv = xcalloc(argc, sizeof(*(*argv)));
  buf[(len - 1) + buf_idx] = '\0';
  for (i = 0; i < argc; i += 1)
  {
    if (len == 0)
    {
      cmd_free_argv(argc, *argv);
      return -1;
    }
    arglen = strlen(buf) + 1;
    (*argv)[i] = xstrdup(buf);
    buf_idx += arglen;
    len -= arglen;
  }

  return 0;
}


----------------------------
None
----------------------------
***/


static void server_client_dispatch_shell(struct client *c)
{
  const char *shell;
  unsigned int shell_idx = 0;
  shell_idx = options_get_string(global_s_options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  proc_send(c->peer, MSG_SHELL, -1, shell, strlen(shell) + 1);
  proc_kill_peer(c->peer);
}


/*** DEPENDENCIES:
None
----------------------------
void proc_kill_peer(struct tmuxpeer *peer)
{
  peer->flags |= 0x1;
}


----------------------------
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


----------------------------
int areshell(const char *shell)
{
  const char *progname;
  unsigned int progname_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  if ((ptr_idx = strrchr(shell, '/')) != 0)
  {
    ptr_idx += 1;
  }
  else
    ptr_idx = shell;
  progname_idx = getprogname();
  if (progname[progname_idx] == '-')
  {
    progname_idx += 1;
  }
  if (strcmp(ptr, progname) == 0)
  {
    return 1;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


/*** DEPENDENCIES:
const char *server_client_get_key_table(struct client *c)
{
  struct session *s = c->session;
  const char *name;
  unsigned int name_idx = 0;
  if (s == 0)
  {
    return "root";
  }
  name_idx = options_get_string(s->options, "key-table");
  if (name[name_idx] == '\0')
  {
    return "root";
  }
  return name;
}


----------------------------
void key_bindings_unref_table(struct key_table *table)
{
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding *bd1;
  unsigned int bd1_idx = 0;
  if ((--table->references) != 0)
  {
    return;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); ((&bd[bd_idx]) != 0) && ((bd1_idx = key_bindings_RB_NEXT(bd), 1)); bd_idx = &bd1[bd1_idx])
  {
    key_bindings_RB_REMOVE(&table->key_bindings, bd);
    cmd_list_free(bd->cmdlist);
    free(bd);
  }

  free((void *) table->name);
  free(table);
}


----------------------------
struct key_table *key_bindings_get_table(const char *name, int create)
{
  struct key_table table_find;
  struct key_table *table;
  unsigned int table_idx = 0;
  table_find.name = name;
  table_idx = key_tables_RB_FIND(&key_tables, &table_find);
  if (((&table[table_idx]) != 0) || (!create))
  {
    return table;
  }
  table_idx = xmalloc(sizeof(*table_idx));
  table->name = xstrdup(name);
  do
  {
    (&table->key_bindings)->rbh_root = 0;
  }
  while (0);
  table->references = 1;
  key_tables_RB_INSERT(&key_tables, table);
  return table;
}


----------------------------
None
----------------------------
***/


static void server_client_repeat_timer(int fd, short events, void *data)
{
  struct client *c = data;
  if (c->flags & 0x20)
  {
    server_client_set_key_table(c, 0);
    c->flags &= ~0x20;
    server_status_client(c);
  }
}


/*** DEPENDENCIES:
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
}


----------------------------
void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


----------------------------
None
----------------------------
***/


void server_client_set_identify(struct client *c, u_int delay)
{
  struct timeval tv;
  tv.tv_sec = delay / 1000;
  tv.tv_usec = (delay % 1000) * 1000L;
  if (event_initialized(&c->identify_timer))
  {
    evtimer_del(&c->identify_timer);
  }
  evtimer_set(&c->identify_timer, server_client_callback_identify, c);
  if (delay != 0)
  {
    evtimer_add(&c->identify_timer, &tv);
  }
  c->flags |= 0x100;
  c->tty.flags |= 0x2 | 0x1;
  server_redraw_client(c);
}


/*** DEPENDENCIES:
static void server_client_callback_identify(int fd, short events, void *data)
{
  server_client_clear_identify(data, 0);
}


----------------------------
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
None
----------------------------
***/


static int server_client_assume_paste(struct session *s)
{
  struct timeval tv;
  int t;
  if ((t = options_get_number(s->options, "assume-paste-time")) == 0)
  {
    return 0;
  }
  do
  {
    (&tv)->tv_sec = (&s->activity_time)->tv_sec - (&s->last_activity_time)->tv_sec;
    (&tv)->tv_usec = (&s->activity_time)->tv_usec - (&s->last_activity_time)->tv_usec;
    if ((&tv)->tv_usec < 0)
    {
      (&tv)->tv_sec -= 1;
      (&tv)->tv_usec += 1000000;
    }
  }
  while (0);
  if ((tv.tv_sec == 0) && (tv.tv_usec < (t * 1000)))
  {
    log_debug("session %s pasting (flag %d)", s->name, !(!(s->flags & 0x2)));
    if (s->flags & 0x2)
    {
      return 1;
    }
    s->flags |= 0x2;
    return 0;
  }
  log_debug("session %s not pasting", s->name);
  s->flags &= ~0x2;
  return 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code']
key_code helper_server_client_check_mouse_9(key_code * const key_ref, struct client * const c, struct mouse_event * const m, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if (c->tty.mouse_drag_release != 0)
  {
    c->tty.mouse_drag_release(c, m);
  }
  c->tty.mouse_drag_update = 0;
  c->tty.mouse_drag_release = 0;
  switch (c->tty.mouse_drag_flag)
  {
    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND1_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND2_BORDER;
      }
      break;
    }

    case 3:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND3_BORDER;
      }
      break;
    }

    default:
    {
      key = KEYC_MOUSE;
      break;
    }

  }

  c->tty.mouse_drag_flag = 0;
  return key;
  *key_ref = key;
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
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


// hint:  ['x_ref is a mutable refrence to u_int', 'y_ref is a mutable refrence to u_int', 'b_ref is a mutable refrence to u_int', 'flag_ref is a mutable refrence to int', 'tv_ref is a mutable refrence to ', 'type_ref is a mutable refrence to ']
void helper_server_client_check_mouse_8(u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, int * const flag_ref, struct timeval * const tv_ref, enum 
{
  NOTYPE,
  MOVE,
  DOWN,
  UP,
  DRAG,
  WHEEL,
  DOUBLE,
  TRIPLE
} * const type_ref, struct client * const c, struct mouse_event * const m)
{
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  int flag = *flag_ref;
  struct timeval tv = *tv_ref;
  enum 
  {
    NOTYPE,
    MOVE,
    DOWN,
    UP,
    DRAG,
    WHEEL,
    DOUBLE,
    TRIPLE
  } type = *type_ref;
  if (c->flags & 0x100000)
  {
    evtimer_del(&c->click_timer);
    c->flags &= ~0x100000;
    if (m->b == c->click_button)
    {
      type = DOUBLE;
      x = m->x, y = m->y, b = m->b;
      log_debug("double-click at %u,%u", x, y);
      flag = 0x200000;
      goto add_timer;
    }
  }
  else
    if (c->flags & 0x200000)
  {
    evtimer_del(&c->click_timer);
    c->flags &= ~0x200000;
    if (m->b == c->click_button)
    {
      type = TRIPLE;
      x = m->x, y = m->y, b = m->b;
      log_debug("triple-click at %u,%u", x, y);
      goto have_event;
    }
  }
  type = DOWN;
  x = m->x, y = m->y, b = m->b;
  log_debug("down at %u,%u", x, y);
  flag = 0x100000;
  add_timer:
  if (300 != 0)
  {
    c->flags |= flag;
    c->click_button = m->b;
    tv.tv_sec = 300 / 1000;
    tv.tv_usec = (300 % 1000) * 1000L;
    evtimer_del(&c->click_timer);
    evtimer_add(&c->click_timer, &tv);
  }

  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *flag_ref = flag;
  *tv_ref = tv;
  *type_ref = type;
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


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'y_ref is a mutable refrence to u_int', 'where_ref is a mutable refrence to ']
key_code helper_server_client_check_mouse_2(unsigned int * const wp_idx_ref, u_int * const y_ref, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} * const where_ref, struct session * const s, struct mouse_event * const m, struct window_pane * const wp, u_int x)
{
  unsigned int wp_idx = *wp_idx_ref;
  u_int y = *y_ref;
  enum 
  {
    NOWHERE,
    PANE,
    STATUS,
    BORDER
  } where = *where_ref;
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  for (wp_idx = (&s->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (((((wp->xoff + wp->sx) == x) && (wp->yoff <= (1 + y))) && ((wp->yoff + wp->sy) >= y)) || ((((wp->yoff + wp->sy) == y) && (wp->xoff <= (1 + x))) && ((wp->xoff + wp->sx) >= x)))
    {
      break;
    }
  }

  if ((&wp[wp_idx]) != 0)
  {
    where = BORDER;
  }
  else
  {
    wp_idx = window_get_active_at(s->curw->window, x, y);
    if ((&wp[wp_idx]) != 0)
    {
      where = PANE;
      log_debug("mouse at %u,%u is on pane %%%u", x, y, wp->id);
    }
  }
  if (where == NOWHERE)
  {
    return 0xfffe00000000ULL;
  }
  m->wp = wp->id;
  m->w = wp->window->id;
  *wp_idx_ref = wp_idx;
  *y_ref = y;
  *where_ref = where;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
struct window_pane *window_get_active_at(struct window *w, u_int x, u_int y)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((x < wp->xoff) || (x > (wp->xoff + wp->sx)))
    {
      continue;
    }
    if ((y < wp->yoff) || (y > (wp->yoff + wp->sy)))
    {
      continue;
    }
    return wp;
  }

  return 0;
}


----------------------------
None
----------------------------
***/


static key_code server_client_check_mouse(struct client *c)
{
  struct session *s = c->session;
  struct mouse_event *m = &c->tty.mouse;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  u_int b;
  int flag;
  key_code key;
  struct timeval tv;
  enum 
  {
    NOTYPE,
    MOVE,
    DOWN,
    UP,
    DRAG,
    WHEEL,
    DOUBLE,
    TRIPLE
  } type;
  enum 
  {
    NOWHERE,
    PANE,
    STATUS,
    BORDER
  } where;
  type = NOTYPE;
  where = NOWHERE;
  log_debug("mouse %02x at %u,%u (last %u,%u) (%d)", m->b, m->x, m->y, m->lx, m->ly, c->tty.mouse_drag_flag);
  if ((((m->sgr_type != ' ') && (m->sgr_b & 32)) && ((m->sgr_b & 3) == 3)) || ((((m->sgr_type == ' ') && (m->b & 32)) && ((m->b & 3) == 3)) && ((m->lb & 3) == 3)))
  {
    type = MOVE;
    x = m->x, y = m->y, b = 0;
    log_debug("move at %u,%u", x, y);
  }
  else
    if (m->b & 32)
  {
    type = DRAG;
    if (c->tty.mouse_drag_flag)
    {
      x = m->x, y = m->y, b = m->b;
      log_debug("drag update at %u,%u", x, y);
    }
    else
    {
      x = m->lx, y = m->ly, b = m->lb;
      log_debug("drag start at %u,%u", x, y);
    }
  }
  else
    if (m->b & 64)
  {
    type = WHEEL;
    x = m->x, y = m->y, b = m->b;
    log_debug("wheel at %u,%u", x, y);
  }
  else
    if ((m->b & 3) == 3)
  {
    type = UP;
    x = m->x, y = m->y, b = m->lb;
    log_debug("up at %u,%u", x, y);
  }
  else
  {
    helper_server_client_check_mouse_8(&x, &y, &b, &flag, &tv, &type, c, m);
  }
  have_event:
  if (type == NOTYPE)
  {
    return 0xfffe00000000ULL;
  }

  m->s = s->id;
  m->statusat = status_at_line(c);
  if ((m->statusat != (-1)) && (y == ((u_int) m->statusat)))
  {
    w_idx = status_get_window_at(c, x);
    if ((&w[w_idx]) == 0)
    {
      return 0xfffe00000000ULL;
    }
    m->w = w->id;
    where = STATUS;
  }
  else
    m->w = -1;
  if (where == NOWHERE)
  {
    helper_server_client_check_mouse_2(&wp_idx, &y, &where, s, m, wp, x);
  }
  else
    m->wp = -1;
  if (((type != DRAG) && (type != WHEEL)) && c->tty.mouse_drag_flag)
  {
    helper_server_client_check_mouse_9(&key, c, m, where);
  }
  key = 0xfffe00000000ULL;
  switch (type)
  {
    case NOTYPE:
    {
      break;
    }

    case MOVE:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEMOVE_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEMOVE_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEMOVE_BORDER;
      }
      break;
    }

    case DRAG:
    {
      helper_server_client_check_mouse_7(&key, c, b, where);
    }

    case WHEEL:
    {
      helper_server_client_check_mouse_1(&key, b, where);
    }

    case UP:
    {
      helper_server_client_check_mouse_3(&key, b, where);
    }

    case DOWN:
    {
      helper_server_client_check_mouse_4(&key, b, where);
    }

    case DOUBLE:
    {
      helper_server_client_check_mouse_5(&key, b, where);
    }

    case TRIPLE:
    {
      helper_server_client_check_mouse_6(&key, b, where);
    }

  }

  if (key == 0xfffe00000000ULL)
  {
    return 0xfffe00000000ULL;
  }
  if (b & 8)
  {
    key |= 0x200000000000ULL;
  }
  if (b & 16)
  {
    key |= 0x400000000000ULL;
  }
  if (b & 4)
  {
    key |= 0x800000000000ULL;
  }
  return key;
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
key_code helper_server_client_check_mouse_9(key_code * const key_ref, struct client * const c, struct mouse_event * const m, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if (c->tty.mouse_drag_release != 0)
  {
    c->tty.mouse_drag_release(c, m);
  }
  c->tty.mouse_drag_update = 0;
  c->tty.mouse_drag_release = 0;
  switch (c->tty.mouse_drag_flag)
  {
    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND1_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND2_BORDER;
      }
      break;
    }

    case 3:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDRAGEND3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDRAGEND3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDRAGEND3_BORDER;
      }
      break;
    }

    default:
    {
      key = KEYC_MOUSE;
      break;
    }

  }

  c->tty.mouse_drag_flag = 0;
  return key;
  *key_ref = key;
}


----------------------------
typedef unsigned long long key_code
----------------------------
void helper_server_client_check_mouse_3(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEUP3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEUP3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEUP3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


----------------------------
void helper_server_client_check_mouse_8(u_int * const x_ref, u_int * const y_ref, u_int * const b_ref, int * const flag_ref, struct timeval * const tv_ref, enum 
{
  NOTYPE,
  MOVE,
  DOWN,
  UP,
  DRAG,
  WHEEL,
  DOUBLE,
  TRIPLE
} * const type_ref, struct client * const c, struct mouse_event * const m)
{
  u_int x = *x_ref;
  u_int y = *y_ref;
  u_int b = *b_ref;
  int flag = *flag_ref;
  struct timeval tv = *tv_ref;
  enum 
  {
    NOTYPE,
    MOVE,
    DOWN,
    UP,
    DRAG,
    WHEEL,
    DOUBLE,
    TRIPLE
  } type = *type_ref;
  if (c->flags & 0x100000)
  {
    evtimer_del(&c->click_timer);
    c->flags &= ~0x100000;
    if (m->b == c->click_button)
    {
      type = DOUBLE;
      x = m->x, y = m->y, b = m->b;
      log_debug("double-click at %u,%u", x, y);
      flag = 0x200000;
      goto add_timer;
    }
  }
  else
    if (c->flags & 0x200000)
  {
    evtimer_del(&c->click_timer);
    c->flags &= ~0x200000;
    if (m->b == c->click_button)
    {
      type = TRIPLE;
      x = m->x, y = m->y, b = m->b;
      log_debug("triple-click at %u,%u", x, y);
      goto have_event;
    }
  }
  type = DOWN;
  x = m->x, y = m->y, b = m->b;
  log_debug("down at %u,%u", x, y);
  flag = 0x100000;
  add_timer:
  if (300 != 0)
  {
    c->flags |= flag;
    c->click_button = m->b;
    tv.tv_sec = 300 / 1000;
    tv.tv_usec = (300 % 1000) * 1000L;
    evtimer_del(&c->click_timer);
    evtimer_add(&c->click_timer, &tv);
  }

  *x_ref = x;
  *y_ref = y;
  *b_ref = b;
  *flag_ref = flag;
  *tv_ref = tv;
  *type_ref = type;
}


----------------------------
key_code helper_server_client_check_mouse_2(unsigned int * const wp_idx_ref, u_int * const y_ref, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} * const where_ref, struct session * const s, struct mouse_event * const m, struct window_pane * const wp, u_int x)
{
  unsigned int wp_idx = *wp_idx_ref;
  u_int y = *y_ref;
  enum 
  {
    NOWHERE,
    PANE,
    STATUS,
    BORDER
  } where = *where_ref;
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  for (wp_idx = (&s->curw->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (((((wp->xoff + wp->sx) == x) && (wp->yoff <= (1 + y))) && ((wp->yoff + wp->sy) >= y)) || ((((wp->yoff + wp->sy) == y) && (wp->xoff <= (1 + x))) && ((wp->xoff + wp->sx) >= x)))
    {
      break;
    }
  }

  if ((&wp[wp_idx]) != 0)
  {
    where = BORDER;
  }
  else
  {
    wp_idx = window_get_active_at(s->curw->window, x, y);
    if ((&wp[wp_idx]) != 0)
    {
      where = PANE;
      log_debug("mouse at %u,%u is on pane %%%u", x, y, wp->id);
    }
  }
  if (where == NOWHERE)
  {
    return 0xfffe00000000ULL;
  }
  m->wp = wp->id;
  m->w = wp->window->id;
  *wp_idx_ref = wp_idx;
  *y_ref = y;
  *where_ref = where;
}


----------------------------
struct window *status_get_window_at(struct client *c, u_int x)
{
  struct session *s = c->session;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct options *oo;
  unsigned int oo_idx = 0;
  const char *sep;
  unsigned int sep_idx = 0;
  size_t seplen;
  x += c->wlmouse;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    oo_idx = wl->window->options;
    sep_idx = options_get_string(oo, "window-status-separator");
    seplen = screen_write_cstrlen("%s", sep);
    if (x < wl->status_width)
    {
      return wl->window;
    }
    x -= wl->status_width + seplen;
  }

  return 0;
}


----------------------------
void helper_server_client_check_mouse_5(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_DOUBLECLICK3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_DOUBLECLICK3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_DOUBLECLICK3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


----------------------------
void helper_server_client_check_mouse_4(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEDOWN3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEDOWN3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEDOWN3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


----------------------------
void helper_server_client_check_mouse_1(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if ((b & 3) == 0)
  {
    if (where == PANE)
    {
      key = KEYC_WHEELUP_PANE;
    }
    if (where == STATUS)
    {
      key = KEYC_WHEELUP_STATUS;
    }
    if (where == BORDER)
    {
      key = KEYC_WHEELUP_BORDER;
    }
  }
  else
  {
    if (where == PANE)
    {
      key = KEYC_WHEELDOWN_PANE;
    }
    if (where == STATUS)
    {
      key = KEYC_WHEELDOWN_STATUS;
    }
    if (where == BORDER)
    {
      key = KEYC_WHEELDOWN_BORDER;
    }
  }
  break;
  *key_ref = key;
}


----------------------------
int status_at_line(struct client *c)
{
  struct session *s = c->session;
  if (c->flags & 0x800000)
  {
    return -1;
  }
  if (s->statusat != 1)
  {
    return s->statusat;
  }
  return c->tty.sy - status_line_size(s);
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
void helper_server_client_check_mouse_6(key_code * const key_ref, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  switch (b & 3)
  {
    case 0:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK1_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK1_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK1_BORDER;
      }
      break;
    }

    case 1:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK2_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK2_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK2_BORDER;
      }
      break;
    }

    case 2:
    {
      if (where == PANE)
      {
        key = KEYC_TRIPLECLICK3_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_TRIPLECLICK3_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_TRIPLECLICK3_BORDER;
      }
      break;
    }

  }

  break;
  *key_ref = key;
}


----------------------------
void helper_server_client_check_mouse_7(key_code * const key_ref, struct client * const c, u_int b, enum 
{
  NOWHERE,
  PANE,
  STATUS,
  BORDER
} where)
{
  key_code key = *key_ref;
  if (c->tty.mouse_drag_update != 0)
  {
    key = KEYC_DRAGGING;
  }
  else
  {
    switch (b & 3)
    {
      case 0:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG1_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG1_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG1_BORDER;
        }
        break;
      }

      case 1:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG2_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG2_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG2_BORDER;
        }
        break;
      }

      case 2:
      {
        if (where == PANE)
        {
          key = KEYC_MOUSEDRAG3_PANE;
        }
        if (where == STATUS)
        {
          key = KEYC_MOUSEDRAG3_STATUS;
        }
        if (where == BORDER)
        {
          key = KEYC_MOUSEDRAG3_BORDER;
        }
        break;
      }

    }

  }
  c->tty.mouse_drag_flag = (b & 3) + 1;
  break;
  *key_ref = key;
}


----------------------------
None
----------------------------
***/


// hint:  ['tv_ref is a mutable refrence to ', 'table_idx_ref is a mutable refrence to unsigned int', 'xtimeout_ref is a mutable refrence to int']
void helper_server_client_handle_key_1(struct timeval * const tv_ref, unsigned int * const table_idx_ref, int * const xtimeout_ref, struct client * const c, struct mouse_event * const m, struct session * const s, struct key_table * const table, struct key_binding * const bd, struct cmd_find_state fs)
{
  struct timeval tv = *tv_ref;
  unsigned int table_idx = *table_idx_ref;
  int xtimeout = *xtimeout_ref;
  if ((c->flags & 0x20) && ((~bd->flags) & 0x1))
  {
    server_client_set_key_table(c, 0);
    c->flags &= ~0x20;
    server_status_client(c);
    table_idx = c->keytable;
    goto retry;
  }
  log_debug("found in key table %s", table->name);
  table->references += 1;
  xtimeout = options_get_number(s->options, "repeat-time");
  if ((xtimeout != 0) && (bd->flags & 0x1))
  {
    c->flags |= 0x20;
    tv.tv_sec = xtimeout / 1000;
    tv.tv_usec = (xtimeout % 1000) * 1000L;
    evtimer_del(&c->repeat_timer);
    evtimer_add(&c->repeat_timer, &tv);
  }
  else
  {
    c->flags &= ~0x20;
    server_client_set_key_table(c, 0);
  }
  server_status_client(c);
  key_bindings_dispatch(bd, 0, c, m, &fs);
  key_bindings_unref_table(table);
  return;
  *tv_ref = tv;
  *table_idx_ref = table_idx;
  *xtimeout_ref = xtimeout;
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
void key_bindings_dispatch(struct key_binding *bd, struct cmdq_item *item, struct client *c, struct mouse_event *m, struct cmd_find_state *fs)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  int readonly;
  readonly = 1;
  for (cmd_idx = (&bd->cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    if (!(cmd->entry->flags & 0x2))
    {
      readonly = 0;
    }
  }

  if ((!readonly) && (c->flags & 0x800))
  {
    new_item_idx = cmdq_get_callback1("key_bindings_read_only", key_bindings_read_only, 0);
  }
  else
  {
    new_item_idx = cmdq_get_command(bd->cmdlist, fs, m, 0);
    if (bd->flags & 0x1)
    {
      new_item->shared->flags |= 0x1;
    }
  }
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(c, new_item);
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
void key_bindings_unref_table(struct key_table *table)
{
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding *bd1;
  unsigned int bd1_idx = 0;
  if ((--table->references) != 0)
  {
    return;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); ((&bd[bd_idx]) != 0) && ((bd1_idx = key_bindings_RB_NEXT(bd), 1)); bd_idx = &bd1[bd1_idx])
  {
    key_bindings_RB_REMOVE(&table->key_bindings, bd);
    cmd_list_free(bd->cmdlist);
    free(bd);
  }

  free((void *) table->name);
  free(table);
}


----------------------------
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
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
void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


----------------------------
None
----------------------------
***/


static int server_client_is_default_key_table(struct client *c, struct key_table *table)
{
  return strcmp(table->name, server_client_get_key_table(c)) == 0;
}


/*** DEPENDENCIES:
const char *server_client_get_key_table(struct client *c)
{
  struct session *s = c->session;
  const char *name;
  unsigned int name_idx = 0;
  if (s == 0)
  {
    return "root";
  }
  name_idx = options_get_string(s->options, "key-table");
  if (name[name_idx] == '\0')
  {
    return "root";
  }
  return name;
}


----------------------------
None
----------------------------
***/


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
struct key_binding *key_bindings_RB_FIND(struct key_bindings *head, struct key_binding *elm)
{
  struct key_binding *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = key_bindings_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


----------------------------
void status_message_clear(struct client *c)
{
  if (c->message_string == 0)
  {
    return;
  }
  free(c->message_string);
  c->message_string = 0;
  if (c->prompt_string == 0)
  {
    c->tty.flags &= ~(0x1 | 0x2);
  }
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


----------------------------
static int server_client_assume_paste(struct session *s)
{
  struct timeval tv;
  int t;
  if ((t = options_get_number(s->options, "assume-paste-time")) == 0)
  {
    return 0;
  }
  do
  {
    (&tv)->tv_sec = (&s->activity_time)->tv_sec - (&s->last_activity_time)->tv_sec;
    (&tv)->tv_usec = (&s->activity_time)->tv_usec - (&s->last_activity_time)->tv_usec;
    if ((&tv)->tv_usec < 0)
    {
      (&tv)->tv_sec -= 1;
      (&tv)->tv_usec += 1000000;
    }
  }
  while (0);
  if ((tv.tv_sec == 0) && (tv.tv_usec < (t * 1000)))
  {
    log_debug("session %s pasting (flag %d)", s->name, !(!(s->flags & 0x2)));
    if (s->flags & 0x2)
    {
      return 1;
    }
    s->flags |= 0x2;
    return 0;
  }
  log_debug("session %s not pasting", s->name);
  s->flags &= ~0x2;
  return 0;
}


----------------------------
void window_pane_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (m == 0))
  {
    return;
  }
  if (wp->mode != 0)
  {
    wp->modelast = time(0);
    if (wp->mode->key != 0)
    {
      wp->mode->key(wp, c, s, key & (~0x1000000000000ULL), m);
    }
    return;
  }
  if ((wp->fd == (-1)) || (wp->flags & 0x40))
  {
    return;
  }
  input_key(wp, key, m);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    return;
  }
  if (options_get_number(wp->window->options, "synchronize-panes"))
  {
    for (wp2_idx = (&wp->window->panes)->tqh_first; (&wp2[wp2_idx]) != 0; wp2_idx = wp2_idx->entry.tqe_next)
    {
      if (((&wp2[wp2_idx]) == wp) || (wp2->mode != 0))
      {
        continue;
      }
      if ((wp2->fd == (-1)) || (wp2->flags & 0x40))
      {
        continue;
      }
      if (window_pane_visible(wp2))
      {
        input_key(wp2, key, 0);
      }
    }

  }
}


----------------------------
void cmd_find_from_session(struct cmd_find_state *fs, struct session *s, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
}


----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
void server_client_clear_identify(struct client *c, struct window_pane *wp)
{
  if ((~c->flags) & 0x100)
  {
    return;
  }
  c->flags &= ~0x100;
  if (c->identify_callback != 0)
  {
    c->identify_callback(c, wp);
  }
  c->tty.flags &= ~(0x2 | 0x1);
  server_redraw_client(c);
}


----------------------------
static key_code server_client_check_mouse(struct client *c)
{
  struct session *s = c->session;
  struct mouse_event *m = &c->tty.mouse;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  u_int b;
  int flag;
  key_code key;
  struct timeval tv;
  enum 
  {
    NOTYPE,
    MOVE,
    DOWN,
    UP,
    DRAG,
    WHEEL,
    DOUBLE,
    TRIPLE
  } type;
  enum 
  {
    NOWHERE,
    PANE,
    STATUS,
    BORDER
  } where;
  type = NOTYPE;
  where = NOWHERE;
  log_debug("mouse %02x at %u,%u (last %u,%u) (%d)", m->b, m->x, m->y, m->lx, m->ly, c->tty.mouse_drag_flag);
  if ((((m->sgr_type != ' ') && (m->sgr_b & 32)) && ((m->sgr_b & 3) == 3)) || ((((m->sgr_type == ' ') && (m->b & 32)) && ((m->b & 3) == 3)) && ((m->lb & 3) == 3)))
  {
    type = MOVE;
    x = m->x, y = m->y, b = 0;
    log_debug("move at %u,%u", x, y);
  }
  else
    if (m->b & 32)
  {
    type = DRAG;
    if (c->tty.mouse_drag_flag)
    {
      x = m->x, y = m->y, b = m->b;
      log_debug("drag update at %u,%u", x, y);
    }
    else
    {
      x = m->lx, y = m->ly, b = m->lb;
      log_debug("drag start at %u,%u", x, y);
    }
  }
  else
    if (m->b & 64)
  {
    type = WHEEL;
    x = m->x, y = m->y, b = m->b;
    log_debug("wheel at %u,%u", x, y);
  }
  else
    if ((m->b & 3) == 3)
  {
    type = UP;
    x = m->x, y = m->y, b = m->lb;
    log_debug("up at %u,%u", x, y);
  }
  else
  {
    helper_server_client_check_mouse_8(&x, &y, &b, &flag, &tv, &type, c, m);
  }
  have_event:
  if (type == NOTYPE)
  {
    return 0xfffe00000000ULL;
  }

  m->s = s->id;
  m->statusat = status_at_line(c);
  if ((m->statusat != (-1)) && (y == ((u_int) m->statusat)))
  {
    w_idx = status_get_window_at(c, x);
    if ((&w[w_idx]) == 0)
    {
      return 0xfffe00000000ULL;
    }
    m->w = w->id;
    where = STATUS;
  }
  else
    m->w = -1;
  if (where == NOWHERE)
  {
    helper_server_client_check_mouse_2(&wp_idx, &y, &where, s, m, wp, x);
  }
  else
    m->wp = -1;
  if (((type != DRAG) && (type != WHEEL)) && c->tty.mouse_drag_flag)
  {
    helper_server_client_check_mouse_9(&key, c, m, where);
  }
  key = 0xfffe00000000ULL;
  switch (type)
  {
    case NOTYPE:
    {
      break;
    }

    case MOVE:
    {
      if (where == PANE)
      {
        key = KEYC_MOUSEMOVE_PANE;
      }
      if (where == STATUS)
      {
        key = KEYC_MOUSEMOVE_STATUS;
      }
      if (where == BORDER)
      {
        key = KEYC_MOUSEMOVE_BORDER;
      }
      break;
    }

    case DRAG:
    {
      helper_server_client_check_mouse_7(&key, c, b, where);
    }

    case WHEEL:
    {
      helper_server_client_check_mouse_1(&key, b, where);
    }

    case UP:
    {
      helper_server_client_check_mouse_3(&key, b, where);
    }

    case DOWN:
    {
      helper_server_client_check_mouse_4(&key, b, where);
    }

    case DOUBLE:
    {
      helper_server_client_check_mouse_5(&key, b, where);
    }

    case TRIPLE:
    {
      helper_server_client_check_mouse_6(&key, b, where);
    }

  }

  if (key == 0xfffe00000000ULL)
  {
    return 0xfffe00000000ULL;
  }
  if (b & 8)
  {
    key |= 0x200000000000ULL;
  }
  if (b & 16)
  {
    key |= 0x400000000000ULL;
  }
  if (b & 4)
  {
    key |= 0x800000000000ULL;
  }
  return key;
}


----------------------------
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
}


----------------------------
struct window_pane *window_pane_at_index(struct window *w, u_int idx)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = options_get_number(w->options, "pane-base-index");
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (n == idx)
    {
      return wp;
    }
    n += 1;
  }

  return 0;
}


----------------------------
void helper_server_client_handle_key_1(struct timeval * const tv_ref, unsigned int * const table_idx_ref, int * const xtimeout_ref, struct client * const c, struct mouse_event * const m, struct session * const s, struct key_table * const table, struct key_binding * const bd, struct cmd_find_state fs)
{
  struct timeval tv = *tv_ref;
  unsigned int table_idx = *table_idx_ref;
  int xtimeout = *xtimeout_ref;
  if ((c->flags & 0x20) && ((~bd->flags) & 0x1))
  {
    server_client_set_key_table(c, 0);
    c->flags &= ~0x20;
    server_status_client(c);
    table_idx = c->keytable;
    goto retry;
  }
  log_debug("found in key table %s", table->name);
  table->references += 1;
  xtimeout = options_get_number(s->options, "repeat-time");
  if ((xtimeout != 0) && (bd->flags & 0x1))
  {
    c->flags |= 0x20;
    tv.tv_sec = xtimeout / 1000;
    tv.tv_usec = (xtimeout % 1000) * 1000L;
    evtimer_del(&c->repeat_timer);
    evtimer_add(&c->repeat_timer, &tv);
  }
  else
  {
    c->flags &= ~0x20;
    server_client_set_key_table(c, 0);
  }
  server_status_client(c);
  key_bindings_dispatch(bd, 0, c, m, &fs);
  key_bindings_unref_table(table);
  return;
  *tv_ref = tv;
  *table_idx_ref = table_idx;
  *xtimeout_ref = xtimeout;
}


----------------------------
typedef unsigned long long key_code
----------------------------
int window_unzoom(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (!(w->flags & 0x1000))
  {
    return -1;
  }
  w->flags &= ~0x1000;
  layout_free(w);
  w->layout_root = w->saved_layout_root;
  w->saved_layout_root = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    wp->layout_cell = wp->saved_layout_cell;
    wp->saved_layout_cell = 0;
  }

  layout_fix_panes(w, w->sx, w->sy);
  notify_window("window-layout-changed", w);
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
void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


----------------------------
int status_prompt_key(struct client *c, key_code key)
{
  struct options *oo = c->session->options;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  char *cp;
  char word[64];
  char prefix = '=';
  const char *histstr;
  unsigned int histstr_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  const char *ws = 0;
  unsigned int ws_idx = 0;
  u_char ch;
  size_t size;
  size_t n;
  size_t off;
  size_t idx;
  size_t bufsize;
  size_t used;
  struct utf8_data tmp;
  struct utf8_data *first;
  unsigned int first_idx = 0;
  struct utf8_data *last;
  unsigned int last_idx = 0;
  struct utf8_data *ud;
  unsigned int ud_idx = 0;
  int keys;
  size = utf8_strlen(c->prompt_buffer);
  if (c->prompt_flags & 0x2)
  {
    if ((key >= '0') && (key <= '9'))
    {
      goto append_key;
    }
    s_idx = utf8_tocstr(c->prompt_buffer);
    c->prompt_inputcb(c, c->prompt_data, s, 1);
    status_prompt_clear(c);
    free(s);
    return 1;
  }
  keys = options_get_number(c->session->options, "status-keys");
  if (keys == 1)
  {
    switch (status_prompt_translate_key(c, key, &key))
    {
      case 1:
      {
        goto process_key;
      }

      case 2:
      {
        goto append_key;
      }

      default:
      {
        return 0;
      }

    }

  }
  process_key:
  switch (key)
  {
    case KEYC_LEFT:

    case '\002':
    {
      if (c->prompt_index > 0)
      {
        c->prompt_index -= 1;
        break;
      }
      break;
    }

    case KEYC_RIGHT:

    case '\006':
    {
      if (c->prompt_index < size)
      {
        c->prompt_index += 1;
        break;
      }
      break;
    }

    case KEYC_HOME:

    case '\001':
    {
      if (c->prompt_index != 0)
      {
        c->prompt_index = 0;
        break;
      }
      break;
    }

    case KEYC_END:

    case '\005':
    {
      if (c->prompt_index != size)
      {
        c->prompt_index = size;
        break;
      }
      break;
    }

    case '\011':
    {
      helper_status_prompt_key_5(&s_idx, &size, &n, &off, &idx, &used, &first_idx, &last_idx, &ud_idx, c, s, word, first, last, ud);
    }

    case KEYC_BSPACE:

    case '\010':
    {
      if (c->prompt_index != 0)
      {
        if (c->prompt_index == size)
        {
          c->prompt_buffer[--c->prompt_index].size = 0;
        }
        else
        {
          memmove((c->prompt_buffer + c->prompt_index) - 1, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
          c->prompt_index -= 1;
        }
        goto changed;
      }
      break;
    }

    case KEYC_DC:

    case '\004':
    {
      if (c->prompt_index != size)
      {
        memmove(c->prompt_buffer + c->prompt_index, (c->prompt_buffer + c->prompt_index) + 1, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
        goto changed;
      }
      break;
    }

    case '\025':
    {
      c->prompt_buffer[0].size = 0;
      c->prompt_index = 0;
      goto changed;
    }

    case '\013':
    {
      if (c->prompt_index < size)
      {
        c->prompt_buffer[c->prompt_index].size = 0;
        goto changed;
      }
      break;
    }

    case '\027':
    {
      helper_status_prompt_key_3(&ws_idx, &idx, c, oo, ws, size);
    }

    case 'f' | 0x200000000000ULL:
    {
      helper_status_prompt_key_2(&ws_idx, &idx, c, oo, ws, size);
    }

    case 'b' | 0x200000000000ULL:
    {
      helper_status_prompt_key_1(&ws_idx, &idx, c, oo, ws);
    }

    case KEYC_UP:

    case '\020':
    {
      histstr_idx = status_prompt_up_history(&c->prompt_hindex);
      if ((&histstr[histstr_idx]) == 0)
      {
        break;
      }
      free(c->prompt_buffer);
      c->prompt_buffer = utf8_fromcstr(histstr);
      c->prompt_index = utf8_strlen(c->prompt_buffer);
      goto changed;
    }

    case KEYC_DOWN:

    case '\016':
    {
      histstr_idx = status_prompt_down_history(&c->prompt_hindex);
      if ((&histstr[histstr_idx]) == 0)
      {
        break;
      }
      free(c->prompt_buffer);
      c->prompt_buffer = utf8_fromcstr(histstr);
      c->prompt_index = utf8_strlen(c->prompt_buffer);
      goto changed;
    }

    case '\031':
    {
      helper_status_prompt_key_4(&pb_idx, &bufdata_idx, &ch, &size, &n, &idx, &ud_idx, c, pb, bufdata, bufsize, ud);
    }

    case '\024':
    {
      idx = c->prompt_index;
      if (idx < size)
      {
        idx += 1;
      }
      if (idx >= 2)
      {
        utf8_copy(&tmp, &c->prompt_buffer[idx - 2]);
        utf8_copy(&c->prompt_buffer[idx - 2], &c->prompt_buffer[idx - 1]);
        utf8_copy(&c->prompt_buffer[idx - 1], &tmp);
        c->prompt_index = idx;
        goto changed;
      }
      break;
    }

    case '\r':

    case '\n':
    {
      s_idx = utf8_tocstr(c->prompt_buffer);
      if (s[s_idx] != '\0')
      {
        status_prompt_add_history(s);
      }
      if (c->prompt_inputcb(c, c->prompt_data, s, 1) == 0)
      {
        status_prompt_clear(c);
      }
      free(s);
      break;
    }

    case '\033':

    case '\003':

    case '\007':
    {
      if (c->prompt_inputcb(c, c->prompt_data, 0, 1) == 0)
      {
        status_prompt_clear(c);
      }
      break;
    }

    case '\022':
    {
      if (c->prompt_flags & 0x4)
      {
        prefix = '-';
        goto changed;
      }
      break;
    }

    case '\023':
    {
      if (c->prompt_flags & 0x4)
      {
        prefix = '+';
        goto changed;
      }
      break;
    }

    default:
    {
      goto append_key;
    }

  }


  c->flags |= 0x10;
  return 0;
  append_key:
  if ((key <= 0x1f) || (key >= 0x000010000000ULL))
  {
    return 0;
  }

  if (utf8_split(key, &tmp) != UTF8_DONE)
  {
    return 0;
  }
  c->prompt_buffer = xreallocarray(c->prompt_buffer, size + 2, sizeof(*c->prompt_buffer));
  if (c->prompt_index == size)
  {
    utf8_copy(&c->prompt_buffer[c->prompt_index], &tmp);
    c->prompt_index += 1;
    c->prompt_buffer[c->prompt_index].size = 0;
  }
  else
  {
    memmove((c->prompt_buffer + c->prompt_index) + 1, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
    utf8_copy(&c->prompt_buffer[c->prompt_index], &tmp);
    c->prompt_index += 1;
  }
  if (c->prompt_flags & 0x1)
  {
    s_idx = utf8_tocstr(c->prompt_buffer);
    if (strlen(s) != 1)
    {
      status_prompt_clear(c);
    }
    else
      if (c->prompt_inputcb(c, c->prompt_data, s, 1) == 0)
    {
      status_prompt_clear(c);
    }
    free(s);
  }
  changed:
  c->flags |= 0x10;

  if (c->prompt_flags & 0x4)
  {
    s_idx = utf8_tocstr(c->prompt_buffer);
    xasprintf(&cp, "%c%s", prefix, s);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
    free(s);
  }
  return 0;
}


----------------------------
struct key_table *key_bindings_get_table(const char *name, int create)
{
  struct key_table table_find;
  struct key_table *table;
  unsigned int table_idx = 0;
  table_find.name = name;
  table_idx = key_tables_RB_FIND(&key_tables, &table_find);
  if (((&table[table_idx]) != 0) || (!create))
  {
    return table;
  }
  table_idx = xmalloc(sizeof(*table_idx));
  table->name = xstrdup(name);
  do
  {
    (&table->key_bindings)->rbh_root = 0;
  }
  while (0);
  table->references = 1;
  key_tables_RB_INSERT(&key_tables, table);
  return table;
}


----------------------------
int cmd_find_from_mouse(struct cmd_find_state *fs, struct mouse_event *m, int flags)
{
  cmd_find_clear_state(fs, flags);
  if (!m->valid)
  {
    return -1;
  }
  fs->wp = cmd_mouse_pane(m, &fs->s, &fs->wl);
  if (fs->wp == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->w = fs->wl->window;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
static int server_client_is_default_key_table(struct client *c, struct key_table *table)
{
  return strcmp(table->name, server_client_get_key_table(c)) == 0;
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
void session_update_activity(struct session *s, struct timeval *from)
{
  struct timeval *last = &s->last_activity_time;
  struct timeval tv;
  memcpy(last, &s->activity_time, sizeof(*last));
  if (from == 0)
  {
    gettimeofday(&s->activity_time, 0);
  }
  else
    memcpy(&s->activity_time, from, sizeof(s->activity_time));
  log_debug("session %s activity %lld.%06d (last %lld.%06d)", s->name, (long long) s->activity_time.tv_sec, (int) s->activity_time.tv_usec, (long long) last->tv_sec, (int) last->tv_usec);
  if (evtimer_initialized(&s->lock_timer))
  {
    evtimer_del(&s->lock_timer);
  }
  else
    evtimer_set(&s->lock_timer, session_lock_timer, s);
  if ((~s->flags) & 0x1)
  {
    timerclear(&tv);
    tv.tv_sec = options_get_number(s->options, "lock-after-time");
    if (tv.tv_sec != 0)
    {
      evtimer_add(&s->lock_timer, &tv);
    }
  }
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
***/


int server_client_open(struct client *c, char **cause)
{
  if (c->flags & 0x2000)
  {
    return 0;
  }
  if (strcmp(c->ttyname, "/dev/tty") == 0)
  {
    *cause = xstrdup("can't use /dev/tty");
    return -1;
  }
  if (!(c->flags & 0x1))
  {
    *cause = xstrdup("not a terminal");
    return -1;
  }
  if (tty_open(&c->tty, cause) != 0)
  {
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
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
int tty_open(struct tty *tty, char **cause)
{
  tty->term = tty_term_find(tty->term_name, tty->fd, cause);
  if (tty->term == 0)
  {
    tty_close(tty);
    return -1;
  }
  tty->flags |= 0x20;
  tty->flags &= ~(((0x1 | 0x2) | 0x80) | 0x4);
  event_set(&tty->event_in, tty->fd, EV_PERSIST | EV_READ, tty_read_callback, tty);
  tty->in = evbuffer_new();
  event_set(&tty->event_out, tty->fd, EV_WRITE, tty_write_callback, tty);
  tty->out = evbuffer_new();
  evtimer_set(&tty->timer, tty_timer_callback, tty);
  tty_start_tty(tty);
  tty_keys_build(tty);
  return 0;
}


----------------------------
None
----------------------------
***/


void server_client_suspend(struct client *c)
{
  struct session *s = c->session;
  if ((s == 0) || (c->flags & 0x1000))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  c->flags |= 0x40;
  proc_send(c->peer, MSG_SUSPEND, -1, 0, 0);
}


/*** DEPENDENCIES:
void tty_stop_tty(struct tty *tty)
{
  struct winsize ws;
  if (!(tty->flags & 0x10))
  {
    return;
  }
  tty->flags &= ~0x10;
  event_del(&tty->timer);
  tty->flags &= ~0x80;
  event_del(&tty->event_in);
  event_del(&tty->event_out);
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) == (-1))
  {
    return;
  }
  if (tcsetattr(tty->fd, TCSANOW, &tty->tio) == (-1))
  {
    return;
  }
  tty_raw(tty, tty_term_string2(tty->term, TTYC_CSR, 0, ws.ws_row - 1));
  if (tty_acs_needed(tty))
  {
    tty_raw(tty, tty_term_string(tty->term, TTYC_RMACS));
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_SGR0));
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMKX));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CLEAR));
  if (tty_term_has(tty->term, TTYC_SS) && (tty->cstyle != 0))
  {
    if (tty_term_has(tty->term, TTYC_SE))
    {
      tty_raw(tty, tty_term_string(tty->term, TTYC_SE));
    }
    else
      tty_raw(tty, tty_term_string1(tty->term, TTYC_SS, 0));
  }
  if (tty->mode & 0x400)
  {
    tty_raw(tty, "\033[?2004l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_CR));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CNORM));
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_raw(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (tty->flags & 0x40)
    {
      tty->flags &= ~0x40;
      tty_raw(tty, "\033[?1004l");
    }
  }
  if (tty->term_type == TTY_VT420)
  {
    tty_raw(tty, "\033[?69l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMCUP));
  setblocking(tty->fd, 1);
}


----------------------------
None
----------------------------
None
----------------------------
***/


char *server_client_get_path(struct client *c, const char *file)
{
  char *path;
  unsigned int path_idx = 0;
  char resolved[PATH_MAX];
  if ((*file) == '/')
  {
    path_idx = xstrdup(file);
  }
  else
    xasprintf(&(&path[path_idx]), "%s/%s", server_client_get_cwd(c), file);
  if (realpath(path, resolved) == 0)
  {
    return path;
  }
  free(path);
  return xstrdup(resolved);
}


/*** DEPENDENCIES:
const char *server_client_get_cwd(struct client *c)
{
  struct session *s;
  unsigned int s_idx = 0;
  if (((c != 0) && (c->session == 0)) && (c->cwd != 0))
  {
    return c->cwd;
  }
  if (((c != 0) && ((s_idx = c->session) != 0)) && (s->cwd != 0))
  {
    return s->cwd;
  }
  return ".";
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
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
None
----------------------------
***/


void server_client_detach(struct client *c, enum msgtype msgtype)
{
  struct session *s = c->session;
  if ((s == 0) || (c->flags & 0x1000))
  {
    return;
  }
  c->flags |= 0x1000;
  notify_client("client-detached", c);
  proc_send(c->peer, msgtype, -1, s->name, strlen(s->name) + 1);
}


/*** DEPENDENCIES:
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


----------------------------
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
}
----------------------------
None
----------------------------
None
----------------------------
***/


void server_client_exec(struct client *c, const char *cmd)
{
  struct session *s = c->session;
  char *msg;
  unsigned int msg_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  size_t cmdsize;
  size_t shellsize;
  if ((*cmd) == '\0')
  {
    return;
  }
  cmdsize = strlen(cmd) + 1;
  if (s != 0)
  {
    shell_idx = options_get_string(s->options, "default-shell");
  }
  else
    shell_idx = options_get_string(global_s_options, "default-shell");
  shellsize = strlen(shell) + 1;
  msg_idx = xmalloc(cmdsize + shellsize);
  memcpy(msg, cmd, cmdsize);
  memcpy((&msg[msg_idx]) + cmdsize, shell, shellsize);
  proc_send(c->peer, MSG_EXEC, -1, msg, cmdsize + shellsize);
  free(msg);
}


/*** DEPENDENCIES:
None
----------------------------
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
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
None
----------------------------
***/


int server_client_check_nested(struct client *c)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  envent_idx = environ_find(c->environ, "TMUX");
  if (((&envent[envent_idx]) == 0) || ((*envent->value) == '\0'))
  {
    return 0;
  }
  for (wp_idx = window_pane_tree_RB_MINMAX(&all_window_panes, -1); (&wp[wp_idx]) != 0; wp_idx = window_pane_tree_RB_NEXT(wp_idx))
  {
    if (strcmp(wp->tty, c->ttyname) == 0)
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct window_pane *window_pane_tree_RB_MINMAX(struct window_pane_tree *head, int val)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->tree_entry.rbe_right;
  }

  return parent;
}


----------------------------
struct window_pane *window_pane_tree_RB_NEXT(struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  if (elm->tree_entry.rbe_right)
  {
    elm_idx = elm_idx->tree_entry.rbe_right;
    while (elm->tree_entry.rbe_left)
    {
      elm_idx = elm_idx->tree_entry.rbe_left;
    }

  }
  else
  {
    if (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_left))
    {
      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
    else
    {
      while (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_right))
      {
        elm_idx = elm_idx->tree_entry.rbe_parent;
      }

      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
None
----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
None
----------------------------
***/


