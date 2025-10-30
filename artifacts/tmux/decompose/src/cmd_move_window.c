static enum cmd_retval cmd_move_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  const char *tflag = args_get(args, 't');
  struct session *src;
  unsigned int src_idx = 0;
  struct session *dst;
  unsigned int dst_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  char *cause;
  int idx;
  int kflag;
  int dflag;
  int sflag;
  if (args_has(args, 'r'))
  {
    if (cmd_find_target(&item->target, item, tflag, CMD_FIND_SESSION, 0x2) != 0)
    {
      return CMD_RETURN_ERROR;
    }
    session_renumber_windows(item->target.s);
    recalculate_sizes();
    server_status_session(item->target.s);
    return CMD_RETURN_NORMAL;
  }
  if (cmd_find_target(&item->target, item, tflag, CMD_FIND_WINDOW, 0x4) != 0)
  {
    return CMD_RETURN_ERROR;
  }
  src_idx = item->source.s;
  dst_idx = item->target.s;
  wl_idx = item->source.wl_idx;
  idx = item->target.idx;
  kflag = args_has(self->args, 'k');
  dflag = args_has(self->args, 'd');
  sflag = args_has(self->args, 's');
  if (args_has(self->args, 'a'))
  {
    if ((idx = winlink_shuffle_up(dst, dst->curw)) == (-1))
    {
      return CMD_RETURN_ERROR;
    }
  }
  if (server_link_window(src, wl, dst, idx, kflag, !dflag, &cause) != 0)
  {
    cmdq_error(item, "can't link window: %s", cause);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  if (self->entry == (&cmd_move_window_entry))
  {
    server_unlink_window(src, wl);
  }
  if ((!sflag) && options_get_number(src->options, "renumber-windows"))
  {
    session_renumber_windows(src);
  }
  recalculate_sizes();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
int server_link_window(struct session *src, struct winlink *srcwl, struct session *dst, int dstidx, int killflag, int selectflag, char **cause)
{
  struct winlink *dstwl;
  unsigned int dstwl_idx = 0;
  struct session_group *srcsg;
  unsigned int srcsg_idx = 0;
  struct session_group *dstsg;
  unsigned int dstsg_idx = 0;
  srcsg_idx = session_group_contains(src);
  dstsg_idx = session_group_contains(dst);
  if ((((src != dst) && ((&srcsg[srcsg_idx]) != 0)) && ((&dstsg[dstsg_idx]) != 0)) && ((&srcsg[srcsg_idx]) == (&dstsg[dstsg_idx])))
  {
    xasprintf(cause, "sessions are grouped");
    return -1;
  }
  dstwl_idx = 0;
  if (dstidx != (-1))
  {
    dstwl_idx = winlink_find_by_index(&dst->windows, dstidx);
  }
  if ((&dstwl[dstwl_idx]) != 0)
  {
    helper_server_link_window_1(&selectflag, srcwl, dst, dstidx, killflag, cause, dstwl, dstwl_idx);
  }
  if (dstidx == (-1))
  {
    dstidx = (-1) - options_get_number(dst->options, "base-index");
  }
  dstwl_idx = session_attach(dst, srcwl->window, dstidx, cause);
  if ((&dstwl[dstwl_idx]) == 0)
  {
    return -1;
  }
  if (selectflag)
  {
    session_select(dst, dstwl->idx);
  }
  server_redraw_session_group(dst);
  return 0;
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
const char *args_get(struct args *args, u_char ch)
{
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    return 0;
  }
  return entry->value;
}


----------------------------
int cmd_find_target(struct cmd_find_state *fs, struct cmdq_item *item, const char *target, enum cmd_find_type type, int flags)
{
  struct mouse_event *m;
  unsigned int m_idx = 0;
  struct cmd_find_state current;
  char *colon;
  unsigned int colon_idx = 0;
  char *period;
  unsigned int period_idx = 0;
  char *copy = 0;
  unsigned int copy_idx = 0;
  const char *session;
  unsigned int session_idx = 0;
  const char *window;
  unsigned int window_idx = 0;
  const char *pane;
  unsigned int pane_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  int window_only = 0;
  int pane_only = 0;
  if (flags & 0x40)
  {
    flags |= 0x2;
  }
  if (type == CMD_FIND_PANE)
  {
    s_idx = "pane";
  }
  else
    if (type == CMD_FIND_WINDOW)
  {
    s_idx = "window";
  }
  else
    if (type == CMD_FIND_SESSION)
  {
    s_idx = "session";
  }
  else
    s_idx = "unknown";
  if (target == 0)
  {
    log_debug("%s: target none, type %s", __func__, s);
  }
  else
    log_debug("%s: target %s, type %s", __func__, target, s);
  log_debug("%s: item %p, flags %#x", __func__, item, flags);
  cmd_find_clear_state(fs, flags);
  if (server_check_marked() && (flags & 0x8))
  {
    fs->current = &marked_pane;
    log_debug("%s: current is marked pane", __func__);
  }
  else
    if (cmd_find_valid_state(&item->shared->current))
  {
    fs->current = &item->shared->current;
    log_debug("%s: current is from queue", __func__);
  }
  else
    if (cmd_find_from_client(&current, item->client, flags) == 0)
  {
    fs->current = &current;
    log_debug("%s: current is from client", __func__);
  }
  else
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "no current target");
    }
    goto error;
  }
  if (!cmd_find_valid_state(fs->current))
  {
    fatalx("invalid current find state");
  }
  if ((target == 0) || ((*target) == '\0'))
  {
    goto current;
  }
  if ((strcmp(target, "=") == 0) || (strcmp(target, "{mouse}") == 0))
  {
    helper_cmd_find_target_2(&m_idx, fs, item, type, flags, m);
  }
  if ((strcmp(target, "~") == 0) || (strcmp(target, "{marked}") == 0))
  {
    if (!server_check_marked())
    {
      if ((~flags) & 0x2)
      {
        cmdq_error(item, "no marked target");
      }
      goto error;
    }
    cmd_find_copy_state(fs, &marked_pane);
    goto found;
  }
  copy_idx = xstrdup(target);
  colon_idx = strchr(copy, ':');
  if ((&colon[colon_idx]) != 0)
  {
    colon[colon_idx] = '\0';
    colon_idx += 1;
  }
  if ((&colon[colon_idx]) == 0)
  {
    period_idx = strchr(copy, '.');
  }
  else
    period_idx = strchr(colon, '.');
  if ((&period[period_idx]) != 0)
  {
    period[period_idx] = '\0';
    period_idx += 1;
  }
  session_idx = (window = &window[window_idx + window_idx]);
  if (((&colon[colon_idx]) != 0) && ((&period[period_idx]) != 0))
  {
    session_idx = &copy[copy_idx];
    window_idx = &colon[colon_idx];
    window_only = 1;
    pane_idx = &period[period_idx];
    pane_only = 1;
  }
  else
    if (((&colon[colon_idx]) != 0) && ((&period[period_idx]) == 0))
  {
    session_idx = &copy[copy_idx];
    window_idx = &colon[colon_idx];
    window_only = 1;
  }
  else
    if (((&colon[colon_idx]) == 0) && ((&period[period_idx]) != 0))
  {
    window_idx = &copy[copy_idx];
    pane_idx = &period[period_idx];
    pane_only = 1;
  }
  else
  {
    helper_cmd_find_target_1(&session_idx, &window_idx, &pane_idx, type, copy, copy_idx);
  }
  if (((&session[session_idx]) != 0) && (session[session_idx] == '='))
  {
    session_idx += 1;
    fs->flags |= 0x10;
  }
  if (((&window[window_idx]) != 0) && (window[window_idx] == '='))
  {
    window_idx += 1;
    fs->flags |= 0x20;
  }
  if (((&session[session_idx]) != 0) && (session[session_idx] == '\0'))
  {
    session_idx = 0;
  }
  if (((&window[window_idx]) != 0) && (window[window_idx] == '\0'))
  {
    window_idx = 0;
  }
  if (((&pane[pane_idx]) != 0) && (pane[pane_idx] == '\0'))
  {
    pane_idx = 0;
  }
  if ((&session[session_idx]) != 0)
  {
    session_idx = cmd_find_map_table(cmd_find_session_table, session_idx);
  }
  if ((&window[window_idx]) != 0)
  {
    window_idx = cmd_find_map_table(cmd_find_window_table, window_idx);
  }
  if ((&pane[pane_idx]) != 0)
  {
    pane_idx = cmd_find_map_table(cmd_find_pane_table, pane_idx);
  }
  log_debug("%s: target %s (flags %#x): session=%s, window=%s, pane=%s", __func__, target, flags, ((&session[session_idx]) == 0) ? ("none") : (session), ((&window[window_idx]) == 0) ? ("none") : (window), ((&pane[pane_idx]) == 0) ? ("none") : (pane));
  if (((&pane[pane_idx]) != 0) && (flags & 0x4))
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "can't specify pane here");
    }
    goto error;
  }
  if ((&session[session_idx]) != 0)
  {
    helper_cmd_find_target_3(fs, session, window, window_idx, pane, pane_idx);
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_window(fs, window, window_only) != 0)
    {
      goto no_window;
    }
    if (cmd_find_get_pane_with_window(fs, pane) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) == 0))
  {
    if (cmd_find_get_window(fs, window, window_only) != 0)
    {
      goto no_window;
    }
    fs->wp = fs->wl->window->active;
    goto found;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_pane(fs, pane, pane_only) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  current:
  cmd_find_copy_state(fs, fs->current);

  if (flags & 0x4)
  {
    fs->idx = -1;
  }
  goto found;
  error:
  fs->current = 0;

  log_debug("%s: error", __func__);
  free(copy);
  if (flags & 0x40)
  {
    return 0;
  }
  return -1;
  found:
  fs->current = 0;

  cmd_find_log_state(__func__, fs);
  free(copy);
  return 0;
  no_session:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find session %s", session);
  }

  goto error;
  no_window:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find window %s", window);
  }

  goto error;
  no_pane:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find pane %s", pane);
  }

  goto error;
}


----------------------------
void session_renumber_windows(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl1;
  unsigned int wl1_idx = 0;
  struct winlink *wl_new;
  unsigned int wl_new_idx = 0;
  struct winlinks old_wins;
  struct winlink_stack old_lastw;
  int new_idx;
  int new_curw_idx;
  memcpy(&old_wins, &s->windows, sizeof(old_wins));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  new_idx = options_get_number(s->options, "base-index");
  new_curw_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl_new_idx = winlink_add(&s->windows, new_idx);
    wl_new->session = s;
    winlink_set_window(wl_new, wl->window);
    wl_new->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
    if ((&wl[wl_idx]) == s->curw)
    {
      new_curw_idx = wl_new->idx;
    }
    new_idx += 1;
  }

  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl_new_idx = winlink_find_by_window(&s->windows, wl->window);
    if ((&wl_new[wl_new_idx]) != 0)
    {
      do
      {
        wl_new->sentry.tqe_next = 0;
        wl_new->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl_new[wl_new_idx];
        (&s->lastw)->tqh_last = &wl_new->sentry.tqe_next;
      }
      while (0);
    }
  }

  s->curw = winlink_find_by_index(&s->windows, new_curw_idx);
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); ((&wl[wl_idx]) != 0) && ((wl1_idx = winlinks_RB_NEXT(wl), 1)); wl_idx = &wl1[wl1_idx])
  {
    winlink_remove(&old_wins, wl);
  }

}


----------------------------
extern const struct cmd_entry cmd_move_window_entry
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void server_unlink_window(struct session *s, struct winlink *wl)
{
  if (session_detach(s, wl))
  {
    server_destroy_session_group(s);
  }
  else
    server_redraw_session_group(s);
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
None
----------------------------
int winlink_shuffle_up(struct session *s, struct winlink *wl)
{
  unsigned int wl_idx = 0;
  int idx;
  int last;
  idx = wl->idx + 1;
  for (last = idx; last < 2147483647; last += 1)
  {
    if (winlink_find_by_index(&s->windows, last) == 0)
    {
      break;
    }
  }

  if (last == 2147483647)
  {
    return -1;
  }
  for (; last > idx; last -= 1)
  {
    wl_idx = winlink_find_by_index(&s->windows, last - 1);
    server_link_window(s, wl, s, last, 0, 0, 0);
    server_unlink_window(s, wl);
  }

  return idx;
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


