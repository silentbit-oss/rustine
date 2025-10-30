static enum cmd_retval cmd_swap_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct window *src_w;
  unsigned int src_w_idx = 0;
  struct window *dst_w;
  unsigned int dst_w_idx = 0;
  struct window_pane *tmp_wp;
  unsigned int tmp_wp_idx = 0;
  struct window_pane *src_wp;
  unsigned int src_wp_idx = 0;
  struct window_pane *dst_wp;
  unsigned int dst_wp_idx = 0;
  struct layout_cell *src_lc;
  unsigned int src_lc_idx = 0;
  struct layout_cell *dst_lc;
  unsigned int dst_lc_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  dst_w_idx = item->target.wl->window;
  dst_wp_idx = item->target.wp;
  src_w_idx = item->source.wl->window;
  src_wp_idx = item->source.wp;
  server_unzoom_window(dst_w);
  if (args_has(self->args, 'D'))
  {
    src_w_idx = &dst_w[dst_w_idx];
    src_wp_idx = dst_wp->entry.tqe_next;
    if ((&src_wp[src_wp_idx]) == 0)
    {
      src_wp_idx = (&dst_w->panes)->tqh_first;
    }
  }
  else
    if (args_has(self->args, 'U'))
  {
    src_w_idx = &dst_w[dst_w_idx];
    src_wp_idx = *((struct window_panes *) dst_wp->entry.tqe_prev)->tqh_last;
    if ((&src_wp[src_wp_idx]) == 0)
    {
      src_wp_idx = *((struct window_panes *) (&dst_w->panes)->tqh_last)->tqh_last;
    }
  }
  server_unzoom_window(src_w);
  if ((&src_wp[src_wp_idx]) == (&dst_wp[dst_wp_idx]))
  {
    return CMD_RETURN_NORMAL;
  }
  tmp_wp_idx = *((struct window_panes *) dst_wp->entry.tqe_prev)->tqh_last;
  do
  {
    if (dst_wp->entry.tqe_next != 0)
    {
      dst_wp->entry.tqe_next->entry.tqe_prev = dst_wp->entry.tqe_prev;
    }
    else
      (&dst_w->panes)->tqh_last = dst_wp->entry.tqe_prev;
    *dst_wp->entry.tqe_prev = dst_wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  do
  {
    if ((dst_wp->entry.tqe_next = src_wp->entry.tqe_next) != 0)
    {
      dst_wp->entry.tqe_next->entry.tqe_prev = &dst_wp->entry.tqe_next;
    }
    else
      (&src_w->panes)->tqh_last = &dst_wp->entry.tqe_next;
    dst_wp->entry.tqe_prev = src_wp->entry.tqe_prev;
    *dst_wp->entry.tqe_prev = &dst_wp[dst_wp_idx];
    ;
    ;
  }
  while (0);
  if ((&tmp_wp[tmp_wp_idx]) == (&src_wp[src_wp_idx]))
  {
    tmp_wp_idx = &dst_wp[dst_wp_idx];
  }
  if ((&tmp_wp[tmp_wp_idx]) == 0)
  {
    do
    {
      if ((src_wp->entry.tqe_next = (&dst_w->panes)->tqh_first) != 0)
      {
        (&dst_w->panes)->tqh_first->entry.tqe_prev = &src_wp->entry.tqe_next;
      }
      else
        (&dst_w->panes)->tqh_last = &src_wp->entry.tqe_next;
      (&dst_w->panes)->tqh_first = &src_wp[src_wp_idx];
      src_wp->entry.tqe_prev = &(&dst_w->panes)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    if ((src_wp->entry.tqe_next = tmp_wp->entry.tqe_next) != 0)
    {
      src_wp->entry.tqe_next->entry.tqe_prev = &src_wp->entry.tqe_next;
    }
    else
      (&dst_w->panes)->tqh_last = &src_wp->entry.tqe_next;
    tmp_wp->entry.tqe_next = &src_wp[src_wp_idx];
    src_wp->entry.tqe_prev = &tmp_wp->entry.tqe_next;
  }
  while (0);
  src_lc_idx = src_wp->layout_cell;
  dst_lc_idx = dst_wp->layout_cell;
  src_lc->wp = &dst_wp[dst_wp_idx];
  dst_wp->layout_cell = &src_lc[src_lc_idx];
  dst_lc->wp = &src_wp[src_wp_idx];
  src_wp->layout_cell = &dst_lc[dst_lc_idx];
  src_wp->window = &dst_w[dst_w_idx];
  dst_wp->window = &src_w[src_w_idx];
  sx = src_wp->sx;
  sy = src_wp->sy;
  xoff = src_wp->xoff;
  yoff = src_wp->yoff;
  src_wp->xoff = dst_wp->xoff;
  src_wp->yoff = dst_wp->yoff;
  window_pane_resize(src_wp, dst_wp->sx, dst_wp->sy);
  dst_wp->xoff = xoff;
  dst_wp->yoff = yoff;
  window_pane_resize(dst_wp, sx, sy);
  if (!args_has(self->args, 'd'))
  {
    if ((&src_w[src_w_idx]) != (&dst_w[dst_w_idx]))
    {
      window_set_active_pane(src_w, dst_wp);
      window_set_active_pane(dst_w, src_wp);
    }
    else
    {
      tmp_wp_idx = &dst_wp[dst_wp_idx];
      if (!window_pane_visible(tmp_wp))
      {
        tmp_wp_idx = &src_wp[src_wp_idx];
      }
      window_set_active_pane(src_w, tmp_wp);
    }
  }
  else
  {
    if (src_w->active == (&src_wp[src_wp_idx]))
    {
      window_set_active_pane(src_w, dst_wp);
    }
    if (dst_w->active == (&dst_wp[dst_wp_idx]))
    {
      window_set_active_pane(dst_w, src_wp);
    }
  }
  if ((&src_w[src_w_idx]) != (&dst_w[dst_w_idx]))
  {
    if (src_w->last == (&src_wp[src_wp_idx]))
    {
      src_w->last = 0;
    }
    if (dst_w->last == (&dst_wp[dst_wp_idx]))
    {
      dst_w->last = 0;
    }
  }
  server_redraw_window(src_w);
  server_redraw_window(dst_w);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
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
None
----------------------------
***/


