static enum cmd_retval cmd_join_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_find_state *current = &item->shared->current;
  struct session *dst_s;
  unsigned int dst_s_idx = 0;
  struct winlink *src_wl;
  unsigned int src_wl_idx = 0;
  struct winlink *dst_wl;
  unsigned int dst_wl_idx = 0;
  struct window *src_w;
  unsigned int src_w_idx = 0;
  struct window *dst_w;
  unsigned int dst_w_idx = 0;
  struct window_pane *src_wp;
  unsigned int src_wp_idx = 0;
  struct window_pane *dst_wp;
  unsigned int dst_wp_idx = 0;
  char *cause;
  int size;
  int percentage;
  int dst_idx;
  enum layout_type type;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  int not_same_window;
  if (self->entry == (&cmd_join_pane_entry))
  {
    not_same_window = 1;
  }
  else
    not_same_window = 0;
  dst_s_idx = item->target.s;
  dst_wl_idx = item->target.wl;
  dst_wp_idx = item->target.wp;
  dst_w_idx = dst_wl->window;
  dst_idx = dst_wl->idx;
  server_unzoom_window(dst_w);
  src_wl_idx = item->source.wl;
  src_wp_idx = item->source.wp;
  src_w_idx = src_wl->window;
  server_unzoom_window(src_w);
  if (not_same_window && ((&src_w[src_w_idx]) == (&dst_w[dst_w_idx])))
  {
    cmdq_error(item, "can't join a pane to its own window");
    return CMD_RETURN_ERROR;
  }
  if ((!not_same_window) && ((&src_wp[src_wp_idx]) == (&dst_wp[dst_wp_idx])))
  {
    cmdq_error(item, "source and target panes must be different");
    return CMD_RETURN_ERROR;
  }
  type = LAYOUT_TOPBOTTOM;
  if (args_has(args, 'h'))
  {
    type = LAYOUT_LEFTRIGHT;
  }
  size = -1;
  if (args_has(args, 'l'))
  {
    size = args_strtonum(args, 'l', 0, 2147483647, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "size %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
  }
  else
    if (args_has(args, 'p'))
  {
    percentage = args_strtonum(args, 'p', 0, 100, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "percentage %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    if (type == LAYOUT_TOPBOTTOM)
    {
      size = (dst_wp->sy * percentage) / 100;
    }
    else
      size = (dst_wp->sx * percentage) / 100;
  }
  lc_idx = layout_split_pane(dst_wp, type, size, args_has(args, 'b'), 0);
  if ((&lc[lc_idx]) == 0)
  {
    cmdq_error(item, "create pane failed: pane too small");
    return CMD_RETURN_ERROR;
  }
  layout_close_pane(src_wp);
  window_lost_pane(src_w, src_wp);
  do
  {
    if (src_wp->entry.tqe_next != 0)
    {
      src_wp->entry.tqe_next->entry.tqe_prev = src_wp->entry.tqe_prev;
    }
    else
      (&src_w->panes)->tqh_last = src_wp->entry.tqe_prev;
    *src_wp->entry.tqe_prev = src_wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  src_wp->window = &dst_w[dst_w_idx];
  do
  {
    if ((src_wp->entry.tqe_next = dst_wp->entry.tqe_next) != 0)
    {
      src_wp->entry.tqe_next->entry.tqe_prev = &src_wp->entry.tqe_next;
    }
    else
      (&dst_w->panes)->tqh_last = &src_wp->entry.tqe_next;
    dst_wp->entry.tqe_next = &src_wp[src_wp_idx];
    src_wp->entry.tqe_prev = &dst_wp->entry.tqe_next;
  }
  while (0);
  layout_assign_pane(lc, src_wp);
  recalculate_sizes();
  server_redraw_window(src_w);
  server_redraw_window(dst_w);
  if (!args_has(args, 'd'))
  {
    window_set_active_pane(dst_w, src_wp);
    session_select(dst_s, dst_idx);
    cmd_find_from_session(current, dst_s, 0);
    server_redraw_session(dst_s);
  }
  else
    server_status_session(dst_s);
  if (window_count_panes(src_w) == 0)
  {
    server_kill_window(src_w);
  }
  else
    notify_window("window-layout-changed", src_w);
  notify_window("window-layout-changed", dst_w);
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
extern const struct cmd_entry cmd_join_pane_entry
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
void window_lost_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: @%u pane %%%u", __func__, w->id, wp->id);
  if (wp == marked_pane.wp)
  {
    server_clear_marked();
  }
  if (wp == w->active)
  {
    w->active = w->last;
    w->last = 0;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last;
      if (w->active == 0)
      {
        w->active = wp->entry.tqe_next;
      }
    }
    if (w->active != 0)
    {
      w->active->flags |= 0x80;
      notify_window("window-pane-changed", w);
    }
  }
  else
    if (wp == w->last)
  {
    w->last = 0;
  }
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
void layout_assign_pane(struct layout_cell *lc, struct window_pane *wp)
{
  layout_make_leaf(lc, wp);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
}


----------------------------
u_int window_count_panes(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    n += 1;
  }

  return n;
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
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
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
struct layout_cell *layout_split_pane(struct window_pane *wp, enum layout_type type, int size, int insert_before, int full_size)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  struct layout_cell *lc1;
  unsigned int lc1_idx = 0;
  struct layout_cell *lc2;
  unsigned int lc2_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  u_int size1;
  u_int size2;
  u_int new_size;
  u_int saved_size;
  u_int resize_first = 0;
  if (full_size)
  {
    lc_idx = wp->window->layout_root;
  }
  else
    lc_idx = wp->layout_cell;
  sx = lc->sx;
  sy = lc->sy;
  xoff = lc->xoff;
  yoff = lc->yoff;
  switch (type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      if (sx < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      if (sy < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    default:
    {
      fatalx("bad layout type");
    }

  }

  if (type == LAYOUT_LEFTRIGHT)
  {
    saved_size = sx;
  }
  else
    saved_size = sy;
  if (size < 0)
  {
    size2 = ((saved_size + 1) / 2) - 1;
  }
  else
    if (insert_before)
  {
    size2 = (saved_size - size) - 1;
  }
  else
    size2 = size;
  if (size2 < 2)
  {
    size2 = 2;
  }
  else
    if (size2 > (saved_size - 2))
  {
    size2 = saved_size - 2;
  }
  size1 = (saved_size - 1) - size2;
  if (insert_before)
  {
    new_size = size2;
  }
  else
    new_size = size1;
  if (full_size && (!layout_set_size_check(wp->window, lc, type, new_size)))
  {
    return 0;
  }
  if ((lc->parent != 0) && (lc->parent->type == type))
  {
    helper_layout_split_pane_1(&lcparent_idx, &lcnew_idx, insert_before, lc, lc_idx, lcparent, lcnew);
  }
  else
    if ((full_size && (lc->parent == 0)) && (lc->type == type))
  {
    helper_layout_split_pane_2(&size, &lcnew_idx, &sx, &sy, &resize_first, wp, insert_before, lc, lcnew, new_size, saved_size);
  }
  else
  {
    helper_layout_split_pane_3(&lcparent_idx, &lcnew_idx, wp, type, insert_before, lc, lc_idx, lcparent, lcnew, sx, sy, xoff, yoff);
  }
  if (insert_before)
  {
    lc1_idx = &lcnew[lcnew_idx];
    lc2_idx = &lc[lc_idx];
  }
  else
  {
    lc1_idx = &lc[lc_idx];
    lc2_idx = &lcnew[lcnew_idx];
  }
  if ((!resize_first) && (type == LAYOUT_LEFTRIGHT))
  {
    layout_set_size(lc1, size1, sy, xoff, yoff);
    layout_set_size(lc2, size2, sy, (xoff + lc1->sx) + 1, yoff);
  }
  else
    if ((!resize_first) && (type == LAYOUT_TOPBOTTOM))
  {
    layout_set_size(lc1, sx, size1, xoff, yoff);
    layout_set_size(lc2, sx, size2, xoff, (yoff + lc1->sy) + 1);
  }
  if (full_size)
  {
    if (!resize_first)
    {
      layout_resize_child_cells(wp->window, lc);
    }
    layout_fix_offsets(wp->window->layout_root);
  }
  else
    layout_make_leaf(lc, wp);
  return lcnew;
}


----------------------------
void server_status_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_status_client(c);
    }
  }

}


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
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
void server_redraw_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
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
void server_kill_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *next_s;
  unsigned int next_s_idx = 0;
  struct session *target_s;
  unsigned int target_s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  next_s_idx = sessions_RB_MINMAX(&sessions, -1);
  while ((&next_s[next_s_idx]) != 0)
  {
    s_idx = &next_s[next_s_idx];
    next_s_idx = sessions_RB_NEXT(s);
    if (!session_has(s, w))
    {
      continue;
    }
    server_unzoom_window(w);
    while ((wl_idx = winlink_find_by_window(&s->windows, w)) != 0)
    {
      if (session_detach(s, wl))
      {
        server_destroy_session_group(s);
        break;
      }
      else
        server_redraw_session_group(s);
    }

    if (options_get_number(s->options, "renumber-windows"))
    {
      if ((sg_idx = session_group_contains(s)) != 0)
      {
        for (target_s_idx = (&sg->sessions)->tqh_first; (&target_s[target_s_idx]) != 0; target_s_idx = target_s_idx->gentry.tqe_next)
        {
          session_renumber_windows(target_s);
        }

      }
      else
        session_renumber_windows(s);
    }
  }

  recalculate_sizes();
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


