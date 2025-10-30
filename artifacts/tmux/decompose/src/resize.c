// hint:  ['ssx_ref is a mutable refrence to u_int', 'ssy_ref is a mutable refrence to u_int']
void helper_helper_recalculate_sizes_1_1(u_int * const ssx_ref, u_int * const ssy_ref, struct session * const s, unsigned int s_idx, struct client * const c, u_int lines)
{
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  if (c->flags & 0x40)
  {
    continue;
  }
  if ((c->flags & (0x2000 | 0x400000)) == 0x2000)
  {
    continue;
  }
  if (c->session == (&s[s_idx]))
  {
    if (c->tty.sx < ssx)
    {
      ssx = c->tty.sx;
    }
    c->flags &= ~0x800000;
    if ((lines != 0) && ((lines + 2) > c->tty.sy))
    {
      c->flags |= 0x800000;
    }
    if (((((~c->flags) & 0x800000) && (!(c->flags & 0x2000))) && (c->tty.sy > lines)) && ((c->tty.sy - lines) < ssy))
    {
      ssy = c->tty.sy - lines;
    }
    else
      if (c->tty.sy < ssy)
    {
      ssy = c->tty.sy;
    }
    s->attached += 1;
  }
  *ssx_ref = ssx;
  *ssy_ref = ssy;
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['c_idx_ref is a mutable refrence to unsigned int', 'ssx_ref is a mutable refrence to u_int', 'ssy_ref is a mutable refrence to u_int', 'lines_ref is a mutable refrence to u_int']
void helper_recalculate_sizes_1(unsigned int * const c_idx_ref, u_int * const ssx_ref, u_int * const ssy_ref, u_int * const lines_ref, struct session * const s, unsigned int s_idx, struct client * const c)
{
  unsigned int c_idx = *c_idx_ref;
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  u_int lines = *lines_ref;
  lines = status_line_size(s);
  s->attached = 0;
  ssx = (ssy = 4294967295U);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    helper_helper_recalculate_sizes_1_1(&ssx, &ssy, s, s_idx, c, lines);
  }

  if ((ssx == 4294967295U) || (ssy == 4294967295U))
  {
    s->flags |= 0x1;
    continue;
  }
  s->flags &= ~0x1;
  if ((lines != 0) && (ssy == 0))
  {
    ssy = lines;
  }
  if ((s->sx == ssx) && (s->sy == ssy))
  {
    continue;
  }
  log_debug("session $%u size %u,%u (was %u,%u)", s->id, ssx, ssy, s->sx, s->sy);
  s->sx = ssx;
  s->sy = ssy;
  status_update_saved(s);
  *c_idx_ref = c_idx;
  *ssx_ref = ssx;
  *ssy_ref = ssy;
  *lines_ref = lines;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void helper_helper_recalculate_sizes_1_1(u_int * const ssx_ref, u_int * const ssy_ref, struct session * const s, unsigned int s_idx, struct client * const c, u_int lines)
{
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  if (c->flags & 0x40)
  {
    continue;
  }
  if ((c->flags & (0x2000 | 0x400000)) == 0x2000)
  {
    continue;
  }
  if (c->session == (&s[s_idx]))
  {
    if (c->tty.sx < ssx)
    {
      ssx = c->tty.sx;
    }
    c->flags &= ~0x800000;
    if ((lines != 0) && ((lines + 2) > c->tty.sy))
    {
      c->flags |= 0x800000;
    }
    if (((((~c->flags) & 0x800000) && (!(c->flags & 0x2000))) && (c->tty.sy > lines)) && ((c->tty.sy - lines) < ssy))
    {
      ssy = c->tty.sy - lines;
    }
    else
      if (c->tty.sy < ssy)
    {
      ssy = c->tty.sy;
    }
    s->attached += 1;
  }
  *ssx_ref = ssx;
  *ssy_ref = ssy;
}


----------------------------
void status_update_saved(struct session *s)
{
  if (!options_get_number(s->options, "status"))
  {
    s->statusat = -1;
  }
  else
    if (options_get_number(s->options, "status-position") == 0)
  {
    s->statusat = 0;
  }
  else
    s->statusat = 1;
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


// hint:  ['s_idx_ref is a mutable refrence to unsigned int', 'wp_idx_ref is a mutable refrence to unsigned int', 'ssx_ref is a mutable refrence to u_int', 'ssy_ref is a mutable refrence to u_int', 'has_ref is a mutable refrence to u_int', 'limit_ref is a mutable refrence to u_int', 'flag_ref is a mutable refrence to int', 'is_zoomed_ref is a mutable refrence to int', 'forced_ref is a mutable refrence to int']
void helper_recalculate_sizes_2(unsigned int * const s_idx_ref, unsigned int * const wp_idx_ref, u_int * const ssx_ref, u_int * const ssy_ref, u_int * const has_ref, u_int * const limit_ref, int * const flag_ref, int * const is_zoomed_ref, int * const forced_ref, struct session * const s, struct window * const w, unsigned int w_idx, struct window_pane * const wp)
{
  unsigned int s_idx = *s_idx_ref;
  unsigned int wp_idx = *wp_idx_ref;
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  u_int has = *has_ref;
  u_int limit = *limit_ref;
  int flag = *flag_ref;
  int is_zoomed = *is_zoomed_ref;
  int forced = *forced_ref;
  if (w->active == 0)
  {
    continue;
  }
  flag = options_get_number(w->options, "aggressive-resize");
  ssx = (ssy = 4294967295U);
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->flags & 0x1)
    {
      continue;
    }
    if (flag)
    {
      has = s->curw->window == (&w[w_idx]);
    }
    else
      has = session_has(s, w);
    if (has)
    {
      if (s->sx < ssx)
      {
        ssx = s->sx;
      }
      if (s->sy < ssy)
      {
        ssy = s->sy;
      }
    }
  }

  if ((ssx == 4294967295U) || (ssy == 4294967295U))
  {
    continue;
  }
  forced = 0;
  limit = options_get_number(w->options, "force-width");
  if ((limit >= 2) && (ssx > limit))
  {
    ssx = limit;
    forced |= 0x2000;
  }
  limit = options_get_number(w->options, "force-height");
  if ((limit >= 2) && (ssy > limit))
  {
    ssy = limit;
    forced |= 0x4000;
  }
  if ((w->sx == ssx) && (w->sy == ssy))
  {
    continue;
  }
  log_debug("window @%u size %u,%u (was %u,%u)", w->id, ssx, ssy, w->sx, w->sy);
  w->flags &= ~(0x2000 | 0x4000);
  w->flags |= forced;
  is_zoomed = w->flags & 0x1000;
  if (is_zoomed)
  {
    window_unzoom(w);
  }
  layout_resize(w, ssx, ssy);
  window_resize(w, ssx, ssy);
  if (is_zoomed && window_pane_visible(w->active))
  {
    window_zoom(w->active);
  }
  wp_idx = w->active;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == (&wp[wp_idx]))
    {
      break;
    }
  }

  if (w->active == w->last)
  {
    w->last = 0;
  }
  server_redraw_window(w);
  notify_window("window-layout-changed", w);
  *s_idx_ref = s_idx;
  *wp_idx_ref = wp_idx;
  *ssx_ref = ssx;
  *ssy_ref = ssy;
  *has_ref = has;
  *limit_ref = limit;
  *flag_ref = flag;
  *is_zoomed_ref = is_zoomed;
  *forced_ref = forced;
}


/*** DEPENDENCIES:
int session_has(struct session *s, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->session == s)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
void layout_resize(struct window *w, u_int sx, u_int sy)
{
  struct layout_cell *lc = w->layout_root;
  int xlimit;
  int ylimit;
  int xchange;
  int ychange;
  xchange = sx - w->sx;
  xlimit = layout_resize_check(w, lc, LAYOUT_LEFTRIGHT);
  if ((xchange < 0) && (xchange < (-xlimit)))
  {
    xchange = -xlimit;
  }
  if (xlimit == 0)
  {
    if (sx <= lc->sx)
    {
      xchange = 0;
    }
    else
      xchange = sx - lc->sx;
  }
  if (xchange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_LEFTRIGHT, xchange);
  }
  ychange = sy - w->sy;
  ylimit = layout_resize_check(w, lc, LAYOUT_TOPBOTTOM);
  if ((ychange < 0) && (ychange < (-ylimit)))
  {
    ychange = -ylimit;
  }
  if (ylimit == 0)
  {
    if (sy <= lc->sy)
    {
      ychange = 0;
    }
    else
      ychange = sy - lc->sy;
  }
  if (ychange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_TOPBOTTOM, ychange);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, sx, sy);
}


----------------------------
void window_resize(struct window *w, u_int sx, u_int sy)
{
  w->sx = sx;
  w->sy = sy;
}


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
struct session *sessions_RB_NEXT(struct session *elm)
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
int window_zoom(struct window_pane *wp)
{
  struct window *w = wp->window;
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  if (w->flags & 0x1000)
  {
    return -1;
  }
  if (!window_pane_visible(wp))
  {
    return -1;
  }
  if (window_count_panes(w) == 1)
  {
    return -1;
  }
  if (w->active != wp)
  {
    window_set_active_pane(w, wp);
  }
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    wp1->saved_layout_cell = wp1->layout_cell;
    wp1->layout_cell = 0;
  }

  w->saved_layout_root = w->layout_root;
  layout_init(w, wp);
  w->flags |= 0x1000;
  notify_window("window-layout-changed", w);
  return 0;
}


----------------------------
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

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
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


----------------------------
struct sessions
{
  struct session *rbh_root;
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


/*** DEPENDENCIES:
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
void helper_recalculate_sizes_1(unsigned int * const c_idx_ref, u_int * const ssx_ref, u_int * const ssy_ref, u_int * const lines_ref, struct session * const s, unsigned int s_idx, struct client * const c)
{
  unsigned int c_idx = *c_idx_ref;
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  u_int lines = *lines_ref;
  lines = status_line_size(s);
  s->attached = 0;
  ssx = (ssy = 4294967295U);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    helper_helper_recalculate_sizes_1_1(&ssx, &ssy, s, s_idx, c, lines);
  }

  if ((ssx == 4294967295U) || (ssy == 4294967295U))
  {
    s->flags |= 0x1;
    continue;
  }
  s->flags &= ~0x1;
  if ((lines != 0) && (ssy == 0))
  {
    ssy = lines;
  }
  if ((s->sx == ssx) && (s->sy == ssy))
  {
    continue;
  }
  log_debug("session $%u size %u,%u (was %u,%u)", s->id, ssx, ssy, s->sx, s->sy);
  s->sx = ssx;
  s->sy = ssy;
  status_update_saved(s);
  *c_idx_ref = c_idx;
  *ssx_ref = ssx;
  *ssy_ref = ssy;
  *lines_ref = lines;
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
struct session *sessions_RB_NEXT(struct session *elm)
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
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_recalculate_sizes_2(unsigned int * const s_idx_ref, unsigned int * const wp_idx_ref, u_int * const ssx_ref, u_int * const ssy_ref, u_int * const has_ref, u_int * const limit_ref, int * const flag_ref, int * const is_zoomed_ref, int * const forced_ref, struct session * const s, struct window * const w, unsigned int w_idx, struct window_pane * const wp)
{
  unsigned int s_idx = *s_idx_ref;
  unsigned int wp_idx = *wp_idx_ref;
  u_int ssx = *ssx_ref;
  u_int ssy = *ssy_ref;
  u_int has = *has_ref;
  u_int limit = *limit_ref;
  int flag = *flag_ref;
  int is_zoomed = *is_zoomed_ref;
  int forced = *forced_ref;
  if (w->active == 0)
  {
    continue;
  }
  flag = options_get_number(w->options, "aggressive-resize");
  ssx = (ssy = 4294967295U);
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->flags & 0x1)
    {
      continue;
    }
    if (flag)
    {
      has = s->curw->window == (&w[w_idx]);
    }
    else
      has = session_has(s, w);
    if (has)
    {
      if (s->sx < ssx)
      {
        ssx = s->sx;
      }
      if (s->sy < ssy)
      {
        ssy = s->sy;
      }
    }
  }

  if ((ssx == 4294967295U) || (ssy == 4294967295U))
  {
    continue;
  }
  forced = 0;
  limit = options_get_number(w->options, "force-width");
  if ((limit >= 2) && (ssx > limit))
  {
    ssx = limit;
    forced |= 0x2000;
  }
  limit = options_get_number(w->options, "force-height");
  if ((limit >= 2) && (ssy > limit))
  {
    ssy = limit;
    forced |= 0x4000;
  }
  if ((w->sx == ssx) && (w->sy == ssy))
  {
    continue;
  }
  log_debug("window @%u size %u,%u (was %u,%u)", w->id, ssx, ssy, w->sx, w->sy);
  w->flags &= ~(0x2000 | 0x4000);
  w->flags |= forced;
  is_zoomed = w->flags & 0x1000;
  if (is_zoomed)
  {
    window_unzoom(w);
  }
  layout_resize(w, ssx, ssy);
  window_resize(w, ssx, ssy);
  if (is_zoomed && window_pane_visible(w->active))
  {
    window_zoom(w->active);
  }
  wp_idx = w->active;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == (&wp[wp_idx]))
    {
      break;
    }
  }

  if (w->active == w->last)
  {
    w->last = 0;
  }
  server_redraw_window(w);
  notify_window("window-layout-changed", w);
  *s_idx_ref = s_idx;
  *wp_idx_ref = wp_idx;
  *ssx_ref = ssx;
  *ssy_ref = ssy;
  *has_ref = has;
  *limit_ref = limit;
  *flag_ref = flag;
  *is_zoomed_ref = is_zoomed;
  *forced_ref = forced;
}


----------------------------
None
----------------------------
***/


