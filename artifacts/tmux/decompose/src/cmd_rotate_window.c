// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'wp2_idx_ref is a mutable refrence to unsigned int', 'lc_idx_ref is a mutable refrence to unsigned int', 'sx_ref is a mutable refrence to u_int', 'sy_ref is a mutable refrence to u_int', 'xoff_ref is a mutable refrence to u_int', 'yoff_ref is a mutable refrence to u_int']
void helper_cmd_rotate_window_exec_1(unsigned int * const wp_idx_ref, unsigned int * const wp2_idx_ref, unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const xoff_ref, u_int * const yoff_ref, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const wp, struct window_pane * const wp2, struct layout_cell * const lc)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int wp2_idx = *wp2_idx_ref;
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int xoff = *xoff_ref;
  u_int yoff = *yoff_ref;
  wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  do
  {
    if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
    {
      (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    (&w->panes)->tqh_first = &wp[wp_idx];
    wp->entry.tqe_prev = &(&w->panes)->tqh_first;
  }
  while (0);
  lc_idx = wp->layout_cell;
  xoff = wp->xoff;
  yoff = wp->yoff;
  sx = wp->sx;
  sy = wp->sy;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if ((wp2_idx = wp->entry.tqe_next) == 0)
    {
      break;
    }
    wp->layout_cell = wp2->layout_cell;
    if (wp->layout_cell != 0)
    {
      wp->layout_cell->wp = &wp[wp_idx];
    }
    wp->xoff = wp2->xoff;
    wp->yoff = wp2->yoff;
    window_pane_resize(wp, wp2->sx, wp2->sy);
  }

  wp->layout_cell = &lc[lc_idx];
  if (wp->layout_cell != 0)
  {
    wp->layout_cell->wp = &wp[wp_idx];
  }
  wp->xoff = xoff;
  wp->yoff = yoff;
  window_pane_resize(wp, sx, sy);
  if ((wp_idx = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last) == 0)
  {
    wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
  }
  window_set_active_pane(w, wp);
  cmd_find_from_winlink_pane(current, wl, wp, 0);
  server_redraw_window(w);
  *wp_idx_ref = wp_idx;
  *wp2_idx_ref = wp2_idx;
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *xoff_ref = xoff;
  *yoff_ref = yoff;
}


/*** DEPENDENCIES:
void cmd_find_from_winlink_pane(struct cmd_find_state *fs, struct winlink *wl, struct window_pane *wp, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
}


----------------------------
void window_pane_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  if ((sx == wp->sx) && (sy == wp->sy))
  {
    return;
  }
  wp->sx = sx;
  wp->sy = sy;
  screen_resize(&wp->base, sx, sy, wp->saved_grid == 0);
  if (wp->mode != 0)
  {
    wp->mode->resize(wp, sx, sy);
  }
  wp->flags |= 0x8;
}


----------------------------
int window_set_active_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: pane %%%u (was %%%u)", __func__, wp->id, w->active->id);
  if (wp == w->active)
  {
    return 0;
  }
  w->last = w->active;
  w->active = wp;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == wp)
    {
      notify_window("window-pane-changed", w);
      return 1;
    }
  }

  w->active->active_point = next_active_point;
  next_active_point += 1;
  w->active->flags |= 0x80;
  notify_window("window-pane-changed", w);
  return 1;
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
None
----------------------------
***/


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'wp2_idx_ref is a mutable refrence to unsigned int', 'lc_idx_ref is a mutable refrence to unsigned int', 'sx_ref is a mutable refrence to u_int', 'sy_ref is a mutable refrence to u_int', 'xoff_ref is a mutable refrence to u_int', 'yoff_ref is a mutable refrence to u_int']
void helper_cmd_rotate_window_exec_2(unsigned int * const wp_idx_ref, unsigned int * const wp2_idx_ref, unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const xoff_ref, u_int * const yoff_ref, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const wp, struct window_pane * const wp2, struct layout_cell * const lc)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int wp2_idx = *wp2_idx_ref;
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int xoff = *xoff_ref;
  u_int yoff = *yoff_ref;
  wp_idx = (&w->panes)->tqh_first;
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  do
  {
    wp->entry.tqe_next = 0;
    wp->entry.tqe_prev = (&w->panes)->tqh_last;
    *(&w->panes)->tqh_last = &wp[wp_idx];
    (&w->panes)->tqh_last = &wp->entry.tqe_next;
  }
  while (0);
  lc_idx = wp->layout_cell;
  xoff = wp->xoff;
  yoff = wp->yoff;
  sx = wp->sx;
  sy = wp->sy;
  for (wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last; (&wp[wp_idx]) != 0; wp_idx = *((struct window_panes *) wp_idx->entry.tqe_prev)->tqh_last)
  {
    if ((wp2_idx = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last) == 0)
    {
      break;
    }
    wp->layout_cell = wp2->layout_cell;
    if (wp->layout_cell != 0)
    {
      wp->layout_cell->wp = &wp[wp_idx];
    }
    wp->xoff = wp2->xoff;
    wp->yoff = wp2->yoff;
    window_pane_resize(wp, wp2->sx, wp2->sy);
  }

  wp->layout_cell = &lc[lc_idx];
  if (wp->layout_cell != 0)
  {
    wp->layout_cell->wp = &wp[wp_idx];
  }
  wp->xoff = xoff;
  wp->yoff = yoff;
  window_pane_resize(wp, sx, sy);
  if ((wp_idx = w->active->entry.tqe_next) == 0)
  {
    wp_idx = (&w->panes)->tqh_first;
  }
  window_set_active_pane(w, wp);
  cmd_find_from_winlink_pane(current, wl, wp, 0);
  server_redraw_window(w);
  *wp_idx_ref = wp_idx;
  *wp2_idx_ref = wp2_idx;
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *xoff_ref = xoff;
  *yoff_ref = yoff;
}


/*** DEPENDENCIES:
void cmd_find_from_winlink_pane(struct cmd_find_state *fs, struct winlink *wl, struct window_pane *wp, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
}


----------------------------
void window_pane_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  if ((sx == wp->sx) && (sy == wp->sy))
  {
    return;
  }
  wp->sx = sx;
  wp->sy = sy;
  screen_resize(&wp->base, sx, sy, wp->saved_grid == 0);
  if (wp->mode != 0)
  {
    wp->mode->resize(wp, sx, sy);
  }
  wp->flags |= 0x8;
}


----------------------------
int window_set_active_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: pane %%%u (was %%%u)", __func__, wp->id, w->active->id);
  if (wp == w->active)
  {
    return 0;
  }
  w->last = w->active;
  w->active = wp;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == wp)
    {
      notify_window("window-pane-changed", w);
      return 1;
    }
  }

  w->active->active_point = next_active_point;
  next_active_point += 1;
  w->active->flags |= 0x80;
  notify_window("window-pane-changed", w);
  return 1;
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
None
----------------------------
***/


static enum cmd_retval cmd_rotate_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct cmd_find_state *current = &item->shared->current;
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  server_unzoom_window(w);
  if (args_has(self->args, 'D'))
  {
    helper_cmd_rotate_window_exec_1(&wp_idx, &wp2_idx, &lc_idx, &sx, &sy, &xoff, &yoff, current, wl, w, wp, wp2, lc);
  }
  else
  {
    helper_cmd_rotate_window_exec_2(&wp_idx, &wp2_idx, &lc_idx, &sx, &sy, &xoff, &yoff, current, wl, w, wp, wp2, lc);
  }
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
void helper_cmd_rotate_window_exec_2(unsigned int * const wp_idx_ref, unsigned int * const wp2_idx_ref, unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const xoff_ref, u_int * const yoff_ref, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const wp, struct window_pane * const wp2, struct layout_cell * const lc)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int wp2_idx = *wp2_idx_ref;
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int xoff = *xoff_ref;
  u_int yoff = *yoff_ref;
  wp_idx = (&w->panes)->tqh_first;
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  do
  {
    wp->entry.tqe_next = 0;
    wp->entry.tqe_prev = (&w->panes)->tqh_last;
    *(&w->panes)->tqh_last = &wp[wp_idx];
    (&w->panes)->tqh_last = &wp->entry.tqe_next;
  }
  while (0);
  lc_idx = wp->layout_cell;
  xoff = wp->xoff;
  yoff = wp->yoff;
  sx = wp->sx;
  sy = wp->sy;
  for (wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last; (&wp[wp_idx]) != 0; wp_idx = *((struct window_panes *) wp_idx->entry.tqe_prev)->tqh_last)
  {
    if ((wp2_idx = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last) == 0)
    {
      break;
    }
    wp->layout_cell = wp2->layout_cell;
    if (wp->layout_cell != 0)
    {
      wp->layout_cell->wp = &wp[wp_idx];
    }
    wp->xoff = wp2->xoff;
    wp->yoff = wp2->yoff;
    window_pane_resize(wp, wp2->sx, wp2->sy);
  }

  wp->layout_cell = &lc[lc_idx];
  if (wp->layout_cell != 0)
  {
    wp->layout_cell->wp = &wp[wp_idx];
  }
  wp->xoff = xoff;
  wp->yoff = yoff;
  window_pane_resize(wp, sx, sy);
  if ((wp_idx = w->active->entry.tqe_next) == 0)
  {
    wp_idx = (&w->panes)->tqh_first;
  }
  window_set_active_pane(w, wp);
  cmd_find_from_winlink_pane(current, wl, wp, 0);
  server_redraw_window(w);
  *wp_idx_ref = wp_idx;
  *wp2_idx_ref = wp2_idx;
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *xoff_ref = xoff;
  *yoff_ref = yoff;
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
void helper_cmd_rotate_window_exec_1(unsigned int * const wp_idx_ref, unsigned int * const wp2_idx_ref, unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const xoff_ref, u_int * const yoff_ref, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const wp, struct window_pane * const wp2, struct layout_cell * const lc)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int wp2_idx = *wp2_idx_ref;
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int xoff = *xoff_ref;
  u_int yoff = *yoff_ref;
  wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  do
  {
    if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
    {
      (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    (&w->panes)->tqh_first = &wp[wp_idx];
    wp->entry.tqe_prev = &(&w->panes)->tqh_first;
  }
  while (0);
  lc_idx = wp->layout_cell;
  xoff = wp->xoff;
  yoff = wp->yoff;
  sx = wp->sx;
  sy = wp->sy;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if ((wp2_idx = wp->entry.tqe_next) == 0)
    {
      break;
    }
    wp->layout_cell = wp2->layout_cell;
    if (wp->layout_cell != 0)
    {
      wp->layout_cell->wp = &wp[wp_idx];
    }
    wp->xoff = wp2->xoff;
    wp->yoff = wp2->yoff;
    window_pane_resize(wp, wp2->sx, wp2->sy);
  }

  wp->layout_cell = &lc[lc_idx];
  if (wp->layout_cell != 0)
  {
    wp->layout_cell->wp = &wp[wp_idx];
  }
  wp->xoff = xoff;
  wp->yoff = yoff;
  window_pane_resize(wp, sx, sy);
  if ((wp_idx = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last) == 0)
  {
    wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
  }
  window_set_active_pane(w, wp);
  cmd_find_from_winlink_pane(current, wl, wp, 0);
  server_redraw_window(w);
  *wp_idx_ref = wp_idx;
  *wp2_idx_ref = wp2_idx;
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *xoff_ref = xoff;
  *yoff_ref = yoff;
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


