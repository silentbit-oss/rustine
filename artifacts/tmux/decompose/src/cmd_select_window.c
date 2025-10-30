// hint:  ['activity_ref is a mutable refrence to int']
enum cmd_retval helper_cmd_select_window_exec_1(int * const activity_ref, struct cmd * const self, struct cmdq_item * const item, struct cmd_find_state * const current, struct session * const s, int next, int previous)
{
  int activity = *activity_ref;
  activity = args_has(self->args, 'a');
  if (next)
  {
    if (session_next(s, activity) != 0)
    {
      cmdq_error(item, "no next window");
      return CMD_RETURN_ERROR;
    }
  }
  else
    if (previous)
  {
    if (session_previous(s, activity) != 0)
    {
      cmdq_error(item, "no previous window");
      return CMD_RETURN_ERROR;
    }
  }
  else
  {
    if (session_last(s) != 0)
    {
      cmdq_error(item, "no last window");
      return CMD_RETURN_ERROR;
    }
  }
  cmd_find_from_session(current, s, 0);
  server_redraw_session(s);
  hooks_insert(s->hooks, item, current, "after-select-window");
  *activity_ref = activity;
}


/*** DEPENDENCIES:
int session_previous(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_previous(s->curw);
  if (alert)
  {
    wl_idx = session_previous_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    if (alert && ((wl_idx = session_previous_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
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
int session_last(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = (&s->lastw)->tqh_first;
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  if ((&wl[wl_idx]) == s->curw)
  {
    return 1;
  }
  return session_set_current(s, wl);
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
int session_next(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_next(s->curw);
  if (alert)
  {
    wl_idx = session_next_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    if (alert && ((wl_idx = session_next_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
}


----------------------------
void hooks_insert(struct hooks *hooks, struct cmdq_item *item, struct cmd_find_state *fs, const char *fmt, ...)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  va_list ap;
  char *name;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  if (item->flags & 0x4)
  {
    return;
  }
  __builtin_va_start(ap);
  xvasprintf(&name, fmt, ap);
  ;
  hook_idx = hooks_find(hooks, name);
  if ((&hook[hook_idx]) == 0)
  {
    free(name);
    return;
  }
  log_debug("running hook %s (parent %p)", name, item);
  new_item_idx = cmdq_get_command(hook->cmdlist, fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", name);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(0, new_item);
  free(name);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_select_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct cmd_find_state *current = &item->shared->current;
  struct winlink *wl = item->target.wl;
  struct session *s = item->target.s;
  int next;
  int previous;
  int last;
  int activity;
  next = self->entry == (&cmd_next_window_entry);
  if (args_has(self->args, 'n'))
  {
    next = 1;
  }
  previous = self->entry == (&cmd_previous_window_entry);
  if (args_has(self->args, 'p'))
  {
    previous = 1;
  }
  last = self->entry == (&cmd_last_window_entry);
  if (args_has(self->args, 'l'))
  {
    last = 1;
  }
  if ((next || previous) || last)
  {
    helper_cmd_select_window_exec_1(&activity, self, item, current, s, next, previous);
  }
  else
  {
    if (args_has(self->args, 'T') && (wl == s->curw))
    {
      if (session_last(s) != 0)
      {
        cmdq_error(item, "no last window");
        return -1;
      }
      if (current->s == s)
      {
        cmd_find_from_session(current, s, 0);
      }
      server_redraw_session(s);
    }
    else
      if (session_select(s, wl->idx) == 0)
    {
      cmd_find_from_session(current, s, 0);
      server_redraw_session(s);
    }
    hooks_insert(s->hooks, item, current, "after-select-window");
  }
  recalculate_sizes();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
extern const struct cmd_entry cmd_next_window_entry
----------------------------
extern const struct cmd_entry cmd_last_window_entry
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
enum cmd_retval helper_cmd_select_window_exec_1(int * const activity_ref, struct cmd * const self, struct cmdq_item * const item, struct cmd_find_state * const current, struct session * const s, int next, int previous)
{
  int activity = *activity_ref;
  activity = args_has(self->args, 'a');
  if (next)
  {
    if (session_next(s, activity) != 0)
    {
      cmdq_error(item, "no next window");
      return CMD_RETURN_ERROR;
    }
  }
  else
    if (previous)
  {
    if (session_previous(s, activity) != 0)
    {
      cmdq_error(item, "no previous window");
      return CMD_RETURN_ERROR;
    }
  }
  else
  {
    if (session_last(s) != 0)
    {
      cmdq_error(item, "no last window");
      return CMD_RETURN_ERROR;
    }
  }
  cmd_find_from_session(current, s, 0);
  server_redraw_session(s);
  hooks_insert(s->hooks, item, current, "after-select-window");
  *activity_ref = activity;
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
int session_last(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = (&s->lastw)->tqh_first;
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  if ((&wl[wl_idx]) == s->curw)
  {
    return 1;
  }
  return session_set_current(s, wl);
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
extern const struct cmd_entry cmd_previous_window_entry
----------------------------
void hooks_insert(struct hooks *hooks, struct cmdq_item *item, struct cmd_find_state *fs, const char *fmt, ...)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  va_list ap;
  char *name;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  if (item->flags & 0x4)
  {
    return;
  }
  __builtin_va_start(ap);
  xvasprintf(&name, fmt, ap);
  ;
  hook_idx = hooks_find(hooks, name);
  if ((&hook[hook_idx]) == 0)
  {
    free(name);
    return;
  }
  log_debug("running hook %s (parent %p)", name, item);
  new_item_idx = cmdq_get_command(hook->cmdlist, fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", name);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(0, new_item);
  free(name);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


