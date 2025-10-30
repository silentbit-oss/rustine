// hint:  ['wp_x_idx_ref is a mutable refrence to unsigned int', 'wp_y_idx_ref is a mutable refrence to unsigned int', 'sx_ref is a mutable refrence to u_int', 'sy_ref is a mutable refrence to u_int', 'ex_ref is a mutable refrence to u_int', 'ey_ref is a mutable refrence to u_int']
void helper_cmd_resize_pane_mouse_update_1(unsigned int * const wp_x_idx_ref, unsigned int * const wp_y_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const ex_ref, u_int * const ey_ref, struct window_pane * const loop, unsigned int loop_idx, struct window_pane * const wp_x, struct window_pane * const wp_y, u_int ly, u_int lx)
{
  unsigned int wp_x_idx = *wp_x_idx_ref;
  unsigned int wp_y_idx = *wp_y_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int ex = *ex_ref;
  u_int ey = *ey_ref;
  if (!window_pane_visible(loop))
  {
    continue;
  }
  sx = loop->xoff;
  if (sx != 0)
  {
    sx -= 1;
  }
  ex = loop->xoff + loop->sx;
  sy = loop->yoff;
  if (sy != 0)
  {
    sy -= 1;
  }
  ey = loop->yoff + loop->sy;
  if ((((lx == sx) || (lx == ex)) && ((ly >= sy) && (ly <= ey))) && (((&wp_x[wp_x_idx]) == 0) || (loop->sy > wp_x->sy)))
  {
    wp_x_idx = &loop[loop_idx];
  }
  if ((((ly == sy) || (ly == ey)) && ((lx >= sx) && (lx <= ex))) && (((&wp_y[wp_y_idx]) == 0) || (loop->sx > wp_y->sx)))
  {
    wp_y_idx = &loop[loop_idx];
  }
  *wp_x_idx_ref = wp_x_idx;
  *wp_y_idx_ref = wp_y_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *ex_ref = ex;
  *ey_ref = ey;
}


/*** DEPENDENCIES:
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


static void cmd_resize_pane_mouse_update(struct client *c, struct mouse_event *m)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *loop;
  unsigned int loop_idx = 0;
  struct window_pane *wp_x;
  unsigned int wp_x_idx = 0;
  struct window_pane *wp_y;
  unsigned int wp_y_idx = 0;
  u_int y;
  u_int ly;
  u_int x;
  u_int lx;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  wl_idx = cmd_mouse_window(m, 0);
  if ((&wl[wl_idx]) == 0)
  {
    c->tty.mouse_drag_update = 0;
    return;
  }
  y = m->y;
  x = m->x;
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  ly = m->ly;
  lx = m->lx;
  if ((m->statusat == 0) && (ly > 0))
  {
    ly -= 1;
  }
  else
    if ((m->statusat > 0) && (ly >= ((u_int) m->statusat)))
  {
    ly = m->statusat - 1;
  }
  wp_x_idx = (wp_y = &wp_y[wp_y_idx + wp_y_idx]);
  for (loop_idx = (&wl->window->panes)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
  {
    helper_cmd_resize_pane_mouse_update_1(&wp_x_idx, &wp_y_idx, &sx, &sy, &ex, &ey, loop, loop_idx, wp_x, wp_y, ly, lx);
  }

  if (((&wp_x[wp_x_idx]) == 0) && ((&wp_y[wp_y_idx]) == 0))
  {
    c->tty.mouse_drag_update = 0;
    return;
  }
  if ((&wp_x[wp_x_idx]) != 0)
  {
    layout_resize_pane(wp_x, LAYOUT_LEFTRIGHT, x - lx, 0);
  }
  if ((&wp_y[wp_y_idx]) != 0)
  {
    layout_resize_pane(wp_y, LAYOUT_TOPBOTTOM, y - ly, 0);
  }
  server_redraw_window(wl->window);
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
void layout_resize_pane(struct window_pane *wp, enum layout_type type, int change, int opposite)
{
  struct window *w = wp->window;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int needed;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    lc_idx = *((struct layout_cells *) lc_idx->entry.tqe_prev)->tqh_last;
  }
  needed = change;
  while (needed != 0)
  {
    if (change > 0)
    {
      size = layout_resize_pane_grow(w, lc, type, needed, opposite);
      needed -= size;
    }
    else
    {
      size = layout_resize_pane_shrink(w, lc, type, needed);
      needed += size;
    }
    if (size == 0)
    {
      break;
    }
  }

  layout_fix_offsets(wp->window->layout_root);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
  notify_window("window-layout-changed", wp->window);
}


----------------------------
struct winlink *cmd_mouse_window(struct mouse_event *m, struct session **sp)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  if (((!m->valid) || (m->s == (-1))) || (m->w == (-1)))
  {
    return 0;
  }
  if ((s_idx = session_find_by_id(m->s_idx)) == 0)
  {
    return 0;
  }
  if ((w_idx = window_find_by_id(m->w_idx)) == 0)
  {
    return 0;
  }
  if (sp != 0)
  {
    *sp = &s[s_idx];
  }
  return winlink_find_by_window(&s->windows, w);
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
void helper_cmd_resize_pane_mouse_update_1(unsigned int * const wp_x_idx_ref, unsigned int * const wp_y_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const ex_ref, u_int * const ey_ref, struct window_pane * const loop, unsigned int loop_idx, struct window_pane * const wp_x, struct window_pane * const wp_y, u_int ly, u_int lx)
{
  unsigned int wp_x_idx = *wp_x_idx_ref;
  unsigned int wp_y_idx = *wp_y_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int ex = *ex_ref;
  u_int ey = *ey_ref;
  if (!window_pane_visible(loop))
  {
    continue;
  }
  sx = loop->xoff;
  if (sx != 0)
  {
    sx -= 1;
  }
  ex = loop->xoff + loop->sx;
  sy = loop->yoff;
  if (sy != 0)
  {
    sy -= 1;
  }
  ey = loop->yoff + loop->sy;
  if ((((lx == sx) || (lx == ex)) && ((ly >= sy) && (ly <= ey))) && (((&wp_x[wp_x_idx]) == 0) || (loop->sy > wp_x->sy)))
  {
    wp_x_idx = &loop[loop_idx];
  }
  if ((((ly == sy) || (ly == ey)) && ((lx >= sx) && (lx <= ex))) && (((&wp_y[wp_y_idx]) == 0) || (loop->sx > wp_y->sx)))
  {
    wp_y_idx = &loop[loop_idx];
  }
  *wp_x_idx_ref = wp_x_idx;
  *wp_y_idx_ref = wp_y_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *ex_ref = ex;
  *ey_ref = ey;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_resize_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmdq_shared *shared = item->shared;
  struct window_pane *wp = item->target.wp;
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct client *c = item->client;
  struct session *s = item->target.s;
  const char *errstr;
  char *cause;
  u_int adjust;
  int x;
  int y;
  if (args_has(args, 'M'))
  {
    if (cmd_mouse_window(&shared->mouse, &s) == 0)
    {
      return CMD_RETURN_NORMAL;
    }
    if ((c == 0) || (c->session != s))
    {
      return CMD_RETURN_NORMAL;
    }
    c->tty.mouse_drag_update = cmd_resize_pane_mouse_update;
    cmd_resize_pane_mouse_update(c, &shared->mouse);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'Z'))
  {
    if (w->flags & 0x1000)
    {
      window_unzoom(w);
    }
    else
      window_zoom(wp);
    server_redraw_window(w);
    server_status_window(w);
    return CMD_RETURN_NORMAL;
  }
  server_unzoom_window(w);
  if (args->argc == 0)
  {
    adjust = 1;
  }
  else
  {
    adjust = strtonum(args->argv[0], 1, 2147483647, &errstr);
    if (errstr != 0)
    {
      cmdq_error(item, "adjustment %s", errstr);
      return CMD_RETURN_ERROR;
    }
  }
  if (args_has(self->args, 'x'))
  {
    x = args_strtonum(self->args, 'x', 2, 2147483647, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "width %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    layout_resize_pane_to(wp, LAYOUT_LEFTRIGHT, x);
  }
  if (args_has(self->args, 'y'))
  {
    y = args_strtonum(self->args, 'y', 2, 2147483647, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "height %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    layout_resize_pane_to(wp, LAYOUT_TOPBOTTOM, y);
  }
  if (args_has(self->args, 'L'))
  {
    layout_resize_pane(wp, LAYOUT_LEFTRIGHT, -adjust, 1);
  }
  else
    if (args_has(self->args, 'R'))
  {
    layout_resize_pane(wp, LAYOUT_LEFTRIGHT, adjust, 1);
  }
  else
    if (args_has(self->args, 'U'))
  {
    layout_resize_pane(wp, LAYOUT_TOPBOTTOM, -adjust, 1);
  }
  else
    if (args_has(self->args, 'D'))
  {
    layout_resize_pane(wp, LAYOUT_TOPBOTTOM, adjust, 1);
  }
  server_redraw_window(wl->window);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
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
struct winlink *cmd_mouse_window(struct mouse_event *m, struct session **sp)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  if (((!m->valid) || (m->s == (-1))) || (m->w == (-1)))
  {
    return 0;
  }
  if ((s_idx = session_find_by_id(m->s_idx)) == 0)
  {
    return 0;
  }
  if ((w_idx = window_find_by_id(m->w_idx)) == 0)
  {
    return 0;
  }
  if (sp != 0)
  {
    *sp = &s[s_idx];
  }
  return winlink_find_by_window(&s->windows, w);
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
static void cmd_resize_pane_mouse_update(struct client *c, struct mouse_event *m)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *loop;
  unsigned int loop_idx = 0;
  struct window_pane *wp_x;
  unsigned int wp_x_idx = 0;
  struct window_pane *wp_y;
  unsigned int wp_y_idx = 0;
  u_int y;
  u_int ly;
  u_int x;
  u_int lx;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  wl_idx = cmd_mouse_window(m, 0);
  if ((&wl[wl_idx]) == 0)
  {
    c->tty.mouse_drag_update = 0;
    return;
  }
  y = m->y;
  x = m->x;
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  ly = m->ly;
  lx = m->lx;
  if ((m->statusat == 0) && (ly > 0))
  {
    ly -= 1;
  }
  else
    if ((m->statusat > 0) && (ly >= ((u_int) m->statusat)))
  {
    ly = m->statusat - 1;
  }
  wp_x_idx = (wp_y = &wp_y[wp_y_idx + wp_y_idx]);
  for (loop_idx = (&wl->window->panes)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
  {
    helper_cmd_resize_pane_mouse_update_1(&wp_x_idx, &wp_y_idx, &sx, &sy, &ex, &ey, loop, loop_idx, wp_x, wp_y, ly, lx);
  }

  if (((&wp_x[wp_x_idx]) == 0) && ((&wp_y[wp_y_idx]) == 0))
  {
    c->tty.mouse_drag_update = 0;
    return;
  }
  if ((&wp_x[wp_x_idx]) != 0)
  {
    layout_resize_pane(wp_x, LAYOUT_LEFTRIGHT, x - lx, 0);
  }
  if ((&wp_y[wp_y_idx]) != 0)
  {
    layout_resize_pane(wp_y, LAYOUT_TOPBOTTOM, y - ly, 0);
  }
  server_redraw_window(wl->window);
}


----------------------------
None
----------------------------
long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp)
{
  long long ll = 0;
  char *ep;
  int error = 0;
  struct errval
  {
    const char *errstr;
    int err;
  } ev[4] = {{0, 0}, {"invalid", EINVAL}, {"too small", ERANGE}, {"too large", ERANGE}};
  ev[0].err = errno;
  errno = 0;
  if (minval > maxval)
  {
    error = 1;
  }
  else
  {
    ll = strtoll(numstr, &ep, 10);
    if ((numstr == ep) || ((*ep) != '\0'))
    {
      error = 1;
    }
    else
      if (((ll == LLONG_MIN) && (errno == ERANGE)) || (ll < minval))
    {
      error = 2;
    }
    else
      if (((ll == LLONG_MAX) && (errno == ERANGE)) || (ll > maxval))
    {
      error = 3;
    }
  }
  if (errstrp != 0)
  {
    *errstrp = ev[error].errstr;
  }
  errno = ev[error].err;
  if (error)
  {
    ll = 0;
  }
  return ll;
}


----------------------------
long long args_strtonum(struct args *args, u_char ch, long long minval, long long maxval, char **cause)
{
  const char *errstr;
  long long ll;
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    *cause = xstrdup("missing");
    return 0;
  }
  ll = strtonum(entry->value, minval, maxval, &errstr);
  if (errstr != 0)
  {
    *cause = xstrdup(errstr);
    return 0;
  }
  *cause = 0;
  return ll;
}


----------------------------
void server_status_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (session_has(s, w))
    {
      server_status_session(s);
    }
  }

}


----------------------------
void layout_resize_pane(struct window_pane *wp, enum layout_type type, int change, int opposite)
{
  struct window *w = wp->window;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int needed;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    lc_idx = *((struct layout_cells *) lc_idx->entry.tqe_prev)->tqh_last;
  }
  needed = change;
  while (needed != 0)
  {
    if (change > 0)
    {
      size = layout_resize_pane_grow(w, lc, type, needed, opposite);
      needed -= size;
    }
    else
    {
      size = layout_resize_pane_shrink(w, lc, type, needed);
      needed += size;
    }
    if (size == 0)
    {
      break;
    }
  }

  layout_fix_offsets(wp->window->layout_root);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
  notify_window("window-layout-changed", wp->window);
}


----------------------------
void layout_resize_pane_to(struct window_pane *wp, enum layout_type type, u_int new_size)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int change;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if (type == LAYOUT_LEFTRIGHT)
  {
    size = lc->sx;
  }
  else
    size = lc->sy;
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    change = size - new_size;
  }
  else
    change = new_size - size;
  layout_resize_pane(wp, type, change, 1);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


