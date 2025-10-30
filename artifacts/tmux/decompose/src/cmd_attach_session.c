// hint:  ['c_loop_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_attach_session_1(unsigned int * const c_loop_idx_ref, struct cmdq_item * const item, int dflag, int Eflag, struct client * const c, struct client * const c_loop, struct session * const s, unsigned int s_idx)
{
  unsigned int c_loop_idx = *c_loop_idx_ref;
  if (dflag)
  {
    for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
    {
      if ((c_loop->session != (&s[s_idx])) || (c == (&c_loop[c_loop_idx])))
      {
        continue;
      }
      server_client_detach(c_loop, MSG_DETACH);
    }

  }
  if (!Eflag)
  {
    environ_update(s->options, c->environ, s->environ);
  }
  c->session = &s[s_idx];
  if ((~item->shared->flags) & 0x1)
  {
    server_client_set_key_table(c, 0);
  }
  status_timer_start(c);
  notify_client("client-session-changed", c);
  session_update_activity(s, 0);
  gettimeofday(&s->last_attached_time, 0);
  server_redraw_client(c);
  s->curw->flags &= ~((0x1 | 0x2) | 0x4);
  *c_loop_idx_ref = c_loop_idx;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
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


----------------------------
void environ_update(struct options *oo, struct environ *src, struct environ *dst)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  u_int size;
  u_int idx;
  const char *value;
  unsigned int value_idx = 0;
  o_idx = options_get(oo, "update-environment");
  if (((&o[o_idx]) == 0) || (options_array_size(o, &size) == (-1)))
  {
    return;
  }
  for (idx = 0; idx < size; idx += 1)
  {
    value_idx = options_array_get(o, idx);
    if ((&value[value_idx]) == 0)
    {
      continue;
    }
    if ((envent_idx = environ_find(src, value)) == 0)
    {
      environ_clear(dst, value);
    }
    else
      environ_set(dst, envent->name, "%s", envent->value);
  }

}


----------------------------
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


----------------------------
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
void status_timer_start(struct client *c)
{
  struct session *s = c->session;
  if (event_initialized(&c->status.timer))
  {
    evtimer_del(&c->status.timer);
  }
  else
    evtimer_set(&c->status.timer, status_timer_callback, c);
  if ((s != 0) && options_get_number(s->options, "status"))
  {
    status_timer_callback(-1, 0, c);
  }
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
None
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


// hint:  ['c_loop_idx_ref is a mutable refrence to unsigned int']
enum cmd_retval helper_cmd_attach_session_2(unsigned int * const c_loop_idx_ref, struct cmdq_item * const item, int dflag, int rflag, int Eflag, struct client * const c, struct client * const c_loop, struct session * const s, unsigned int s_idx, char * const cause)
{
  unsigned int c_loop_idx = *c_loop_idx_ref;
  if (server_client_open(c, &cause) != 0)
  {
    cmdq_error(item, "open terminal failed: %s", cause);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  if (rflag)
  {
    c->flags |= 0x800;
  }
  if (dflag)
  {
    for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
    {
      if ((c_loop->session != (&s[s_idx])) || (c == (&c_loop[c_loop_idx])))
      {
        continue;
      }
      server_client_detach(c_loop, MSG_DETACH);
    }

  }
  if (!Eflag)
  {
    environ_update(s->options, c->environ, s->environ);
  }
  c->session = &s[s_idx];
  server_client_set_key_table(c, 0);
  status_timer_start(c);
  notify_client("client-session-changed", c);
  session_update_activity(s, 0);
  gettimeofday(&s->last_attached_time, 0);
  server_redraw_client(c);
  s->curw->flags &= ~((0x1 | 0x2) | 0x4);
  if ((~c->flags) & 0x2000)
  {
    proc_send(c->peer, MSG_READY, -1, 0, 0);
  }
  notify_client("client-attached", c);
  c->flags |= 0x80;
  *c_loop_idx_ref = c_loop_idx;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
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


----------------------------
void environ_update(struct options *oo, struct environ *src, struct environ *dst)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  u_int size;
  u_int idx;
  const char *value;
  unsigned int value_idx = 0;
  o_idx = options_get(oo, "update-environment");
  if (((&o[o_idx]) == 0) || (options_array_size(o, &size) == (-1)))
  {
    return;
  }
  for (idx = 0; idx < size; idx += 1)
  {
    value_idx = options_array_get(o, idx);
    if ((&value[value_idx]) == 0)
    {
      continue;
    }
    if ((envent_idx = environ_find(src, value)) == 0)
    {
      environ_clear(dst, value);
    }
    else
      environ_set(dst, envent->name, "%s", envent->value);
  }

}


----------------------------
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


----------------------------
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void status_timer_start(struct client *c)
{
  struct session *s = c->session;
  if (event_initialized(&c->status.timer))
  {
    evtimer_del(&c->status.timer);
  }
  else
    evtimer_set(&c->status.timer, status_timer_callback, c);
  if ((s != 0) && options_get_number(s->options, "status"))
  {
    status_timer_callback(-1, 0, c);
  }
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
None
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


enum cmd_retval cmd_attach_session(struct cmdq_item *item, const char *tflag, int dflag, int rflag, const char *cflag, int Eflag)
{
  struct cmd_find_state *current = &item->shared->current;
  enum cmd_find_type type;
  int flags;
  struct client *c = item->client;
  struct client *c_loop;
  unsigned int c_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  char *cause;
  if ((&sessions)->rbh_root == 0)
  {
    cmdq_error(item, "no sessions");
    return CMD_RETURN_ERROR;
  }
  if (c == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  if (server_client_check_nested(c))
  {
    cmdq_error(item, "sessions should be nested with care, unset $TMUX to force");
    return CMD_RETURN_ERROR;
  }
  if ((tflag != 0) && (tflag[strcspn(tflag, ":.")] != '\0'))
  {
    type = CMD_FIND_PANE;
    flags = 0;
  }
  else
  {
    type = CMD_FIND_SESSION;
    flags = 0x1;
  }
  if (cmd_find_target(&item->target, item, tflag, type, flags) != 0)
  {
    return CMD_RETURN_ERROR;
  }
  s_idx = item->target.s_idx;
  wl_idx = item->target.wl_idx;
  wp_idx = item->target.wp_idx;
  if ((&wl[wl_idx]) != 0)
  {
    if ((&wp[wp_idx]) != 0)
    {
      window_set_active_pane(wp->window, wp);
    }
    session_set_current(s, wl);
    if ((&wp[wp_idx]) != 0)
    {
      cmd_find_from_winlink_pane(current, wl, wp, 0);
    }
    else
      cmd_find_from_winlink(current, wl, 0);
  }
  if (cflag != 0)
  {
    free((void *) s->cwd);
    s->cwd = format_single(item, cflag, c, s, wl, wp);
  }
  if (c->session != 0)
  {
    helper_cmd_attach_session_1(&c_loop_idx, item, dflag, Eflag, c, c_loop, s, s_idx);
  }
  else
  {
    helper_cmd_attach_session_2(&c_loop_idx, item, dflag, rflag, Eflag, c, c_loop, s, s_idx, cause);
  }
  recalculate_sizes();
  alerts_check_session(s);
  server_update_socket();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void server_update_socket(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  static int last = -1;
  int n;
  int mode;
  struct stat sb;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      n += 1;
      break;
    }
  }

  if (n != last)
  {
    last = n;
    if (stat(socket_path, &sb) != 0)
    {
      return;
    }
    mode = sb.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO);
    if (n != 0)
    {
      if (mode & S_IRUSR)
      {
        mode |= S_IXUSR;
      }
      if (mode & S_IRGRP)
      {
        mode |= S_IXGRP;
      }
      if (mode & S_IROTH)
      {
        mode |= S_IXOTH;
      }
    }
    else
      mode &= ~((S_IXUSR | S_IXGRP) | S_IXOTH);
    chmod(socket_path, mode);
  }
}


----------------------------
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


----------------------------
int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
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
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
}
----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
}


----------------------------
void helper_cmd_attach_session_1(unsigned int * const c_loop_idx_ref, struct cmdq_item * const item, int dflag, int Eflag, struct client * const c, struct client * const c_loop, struct session * const s, unsigned int s_idx)
{
  unsigned int c_loop_idx = *c_loop_idx_ref;
  if (dflag)
  {
    for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
    {
      if ((c_loop->session != (&s[s_idx])) || (c == (&c_loop[c_loop_idx])))
      {
        continue;
      }
      server_client_detach(c_loop, MSG_DETACH);
    }

  }
  if (!Eflag)
  {
    environ_update(s->options, c->environ, s->environ);
  }
  c->session = &s[s_idx];
  if ((~item->shared->flags) & 0x1)
  {
    server_client_set_key_table(c, 0);
  }
  status_timer_start(c);
  notify_client("client-session-changed", c);
  session_update_activity(s, 0);
  gettimeofday(&s->last_attached_time, 0);
  server_redraw_client(c);
  s->curw->flags &= ~((0x1 | 0x2) | 0x4);
  *c_loop_idx_ref = c_loop_idx;
}


----------------------------
struct sessions
{
  struct session *rbh_root;
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
void alerts_check_session(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    alerts_check_all(wl->window);
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
void cmd_find_from_winlink(struct cmd_find_state *fs, struct winlink *wl, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->w = wl->window;
  fs->wp = wl->window->active;
  cmd_find_log_state(__func__, fs);
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
enum cmd_retval helper_cmd_attach_session_2(unsigned int * const c_loop_idx_ref, struct cmdq_item * const item, int dflag, int rflag, int Eflag, struct client * const c, struct client * const c_loop, struct session * const s, unsigned int s_idx, char * const cause)
{
  unsigned int c_loop_idx = *c_loop_idx_ref;
  if (server_client_open(c, &cause) != 0)
  {
    cmdq_error(item, "open terminal failed: %s", cause);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  if (rflag)
  {
    c->flags |= 0x800;
  }
  if (dflag)
  {
    for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
    {
      if ((c_loop->session != (&s[s_idx])) || (c == (&c_loop[c_loop_idx])))
      {
        continue;
      }
      server_client_detach(c_loop, MSG_DETACH);
    }

  }
  if (!Eflag)
  {
    environ_update(s->options, c->environ, s->environ);
  }
  c->session = &s[s_idx];
  server_client_set_key_table(c, 0);
  status_timer_start(c);
  notify_client("client-session-changed", c);
  session_update_activity(s, 0);
  gettimeofday(&s->last_attached_time, 0);
  server_redraw_client(c);
  s->curw->flags &= ~((0x1 | 0x2) | 0x4);
  if ((~c->flags) & 0x2000)
  {
    proc_send(c->peer, MSG_READY, -1, 0, 0);
  }
  notify_client("client-attached", c);
  c->flags |= 0x80;
  *c_loop_idx_ref = c_loop_idx;
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


static enum cmd_retval cmd_attach_session_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  return cmd_attach_session(item, args_get(args, 't'), args_has(args, 'd'), args_has(args, 'r'), args_get(args, 'c'), args_has(args, 'E'));
}


/*** DEPENDENCIES:
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
enum cmd_retval cmd_attach_session(struct cmdq_item *item, const char *tflag, int dflag, int rflag, const char *cflag, int Eflag)
{
  struct cmd_find_state *current = &item->shared->current;
  enum cmd_find_type type;
  int flags;
  struct client *c = item->client;
  struct client *c_loop;
  unsigned int c_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  char *cause;
  if ((&sessions)->rbh_root == 0)
  {
    cmdq_error(item, "no sessions");
    return CMD_RETURN_ERROR;
  }
  if (c == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  if (server_client_check_nested(c))
  {
    cmdq_error(item, "sessions should be nested with care, unset $TMUX to force");
    return CMD_RETURN_ERROR;
  }
  if ((tflag != 0) && (tflag[strcspn(tflag, ":.")] != '\0'))
  {
    type = CMD_FIND_PANE;
    flags = 0;
  }
  else
  {
    type = CMD_FIND_SESSION;
    flags = 0x1;
  }
  if (cmd_find_target(&item->target, item, tflag, type, flags) != 0)
  {
    return CMD_RETURN_ERROR;
  }
  s_idx = item->target.s_idx;
  wl_idx = item->target.wl_idx;
  wp_idx = item->target.wp_idx;
  if ((&wl[wl_idx]) != 0)
  {
    if ((&wp[wp_idx]) != 0)
    {
      window_set_active_pane(wp->window, wp);
    }
    session_set_current(s, wl);
    if ((&wp[wp_idx]) != 0)
    {
      cmd_find_from_winlink_pane(current, wl, wp, 0);
    }
    else
      cmd_find_from_winlink(current, wl, 0);
  }
  if (cflag != 0)
  {
    free((void *) s->cwd);
    s->cwd = format_single(item, cflag, c, s, wl, wp);
  }
  if (c->session != 0)
  {
    helper_cmd_attach_session_1(&c_loop_idx, item, dflag, Eflag, c, c_loop, s, s_idx);
  }
  else
  {
    helper_cmd_attach_session_2(&c_loop_idx, item, dflag, rflag, Eflag, c, c_loop, s, s_idx, cause);
  }
  recalculate_sizes();
  alerts_check_session(s);
  server_update_socket();
  return CMD_RETURN_NORMAL;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


