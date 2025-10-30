static enum cmd_retval cmd_kill_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct winlink *wl = item->target.wl;
  struct window_pane *loopwp;
  unsigned int loopwp_idx = 0;
  struct window_pane *tmpwp;
  unsigned int tmpwp_idx = 0;
  struct window_pane *wp = item->target.wp;
  if (args_has(self->args, 'a'))
  {
    server_unzoom_window(wl->window);
    for (loopwp_idx = (&wl->window->panes)->tqh_first; ((&loopwp[loopwp_idx]) != 0) && ((tmpwp_idx = loopwp->entry.tqe_next, 1)); loopwp_idx = &tmpwp[tmpwp_idx])
    {
      if ((&loopwp[loopwp_idx]) == wp)
      {
        continue;
      }
      layout_close_pane(loopwp);
      window_remove_pane(wl->window, loopwp);
    }

    server_redraw_window(wl->window);
    return CMD_RETURN_NORMAL;
  }
  server_kill_pane(wp);
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
void layout_close_pane(struct window_pane *wp)
{
  struct window *w = wp->window;
  layout_destroy_cell(w, wp->layout_cell, &w->layout_root);
  if (w->layout_root != 0)
  {
    layout_fix_offsets(w->layout_root);
    layout_fix_panes(w, w->sx, w->sy);
  }
  notify_window("window-layout-changed", w);
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
void window_remove_pane(struct window *w, struct window_pane *wp)
{
  window_lost_pane(w, wp);
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
  window_pane_destroy(wp);
}


----------------------------
void server_kill_pane(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (window_count_panes(w) == 1)
  {
    server_kill_window(w);
    recalculate_sizes();
  }
  else
  {
    server_unzoom_window(w);
    layout_close_pane(wp);
    window_remove_pane(w, wp);
    server_redraw_window(w);
  }
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


