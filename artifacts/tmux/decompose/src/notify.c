static void notify_hook(struct cmdq_item *item, struct notify_entry *ne)
{
  struct cmd_find_state fs;
  struct hook *hook;
  unsigned int hook_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  struct session *s = ne->session;
  struct window *w = ne->window;
  cmd_find_clear_state(&fs, 0);
  if (cmd_find_empty_state(&ne->fs) || (!cmd_find_valid_state(&ne->fs)))
  {
    cmd_find_from_nothing(&fs, 0);
  }
  else
    cmd_find_copy_state(&fs, &ne->fs);
  hook_idx = hooks_find(hooks_get(fs.s), ne->name);
  if ((&hook[hook_idx]) == 0)
  {
    return;
  }
  log_debug("notify hook %s", ne->name);
  new_item_idx = cmdq_get_command(hook->cmdlist, &fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", ne->name);
  if (s != 0)
  {
    cmdq_format(new_item, "hook_session", "$%u", s->id);
    cmdq_format(new_item, "hook_session_name", "%s", s->name);
  }
  if (w != 0)
  {
    cmdq_format(new_item, "hook_window", "@%u", w->id);
    cmdq_format(new_item, "hook_window_name", "%s", w->name);
  }
  if (ne->pane != (-1))
  {
    cmdq_format(new_item, "hook_pane", "%%%d", ne->pane);
  }
  cmdq_insert_after(item, new_item);
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
int cmd_find_valid_state(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if ((((fs->s == 0) || (fs->wl == 0)) || (fs->w == 0)) || (fs->wp == 0))
  {
    return 0;
  }
  if (!session_alive(fs->s))
  {
    return 0;
  }
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((wl->window == fs->w) && ((&wl[wl_idx]) == fs->wl))
    {
      break;
    }
  }

  if ((&wl[wl_idx]) == 0)
  {
    return 0;
  }
  if (fs->w != fs->wl->window)
  {
    return 0;
  }
  return window_has_pane(fs->w, fs->wp);
}


----------------------------
struct hook *hooks_find(struct hooks *hooks, const char *name)
{
  unsigned int hooks_idx = 0;
  struct hook hook0;
  struct hook *hook;
  unsigned int hook_idx = 0;
  hook0.name = name;
  hook_idx = hooks_tree_RB_FIND(&hooks->tree, &hook0);
  while ((&hook[hook_idx]) == 0)
  {
    hooks_idx = hooks_idx->parent;
    if ((&hooks[hooks_idx]) == 0)
    {
      break;
    }
    hook_idx = hooks_tree_RB_FIND(&hooks->tree, &hook0);
  }

  return hook;
}


----------------------------
int cmd_find_from_nothing(struct cmd_find_state *fs, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = cmd_find_best_session(0, 0, flags);
  if (fs->s == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
int cmd_find_empty_state(struct cmd_find_state *fs)
{
  if ((((fs->s == 0) && (fs->wl == 0)) && (fs->w == 0)) && (fs->wp == 0))
  {
    return 1;
  }
  return 0;
}


----------------------------
void cmd_find_copy_state(struct cmd_find_state *dst, struct cmd_find_state *src)
{
  dst->s = src->s;
  dst->wl = src->wl;
  dst->idx = src->idx;
  dst->w = src->w;
  dst->wp = src->wp;
}


----------------------------
void cmdq_format(struct cmdq_item *item, const char *key, const char *fmt, ...)
{
  struct cmdq_shared *shared = item->shared;
  va_list ap;
  char *value;
  __builtin_va_start(ap);
  xvasprintf(&value, fmt, ap);
  ;
  if (shared->formats == 0)
  {
    shared->formats = format_create(0, 0, 0, 0);
  }
  format_add(shared->formats, key, "%s", value);
  free(value);
}


----------------------------
void cmdq_insert_after(struct cmdq_item *after, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct client *c = after->client;
  struct cmdq_list *queue = after->queue;
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
    if (after->next != 0)
    {
      do
      {
        if ((item->entry.tqe_next = after->next->entry.tqe_next) != 0)
        {
          item->entry.tqe_next->entry.tqe_prev = &item->entry.tqe_next;
        }
        else
          queue->tqh_last = &item->entry.tqe_next;
        after->next->entry.tqe_next = &item[item_idx];
        item->entry.tqe_prev = &after->next->entry.tqe_next;
      }
      while (0);
    }
    else
      do
    {
      if ((item->entry.tqe_next = after->entry.tqe_next) != 0)
      {
        item->entry.tqe_next->entry.tqe_prev = &item->entry.tqe_next;
      }
      else
        queue->tqh_last = &item->entry.tqe_next;
      after->entry.tqe_next = &item[item_idx];
      item->entry.tqe_prev = &after->entry.tqe_next;
    }
    while (0);
    after->next = &item[item_idx];
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


----------------------------
struct hooks *hooks_get(struct session *s)
{
  if (s != 0)
  {
    return s->hooks;
  }
  return global_hooks;
}


----------------------------
struct notify_entry
{
  const char *name;
  struct client *client;
  struct session *session;
  struct window *window;
  int pane;
  struct cmd_find_state fs;
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


void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


/*** DEPENDENCIES:
None
----------------------------
int cmd_find_from_window(struct cmd_find_state *fs, struct window *w, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->w = w;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  if (cmd_find_best_winlink_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
None
----------------------------
***/


void notify_winlink(const char *name, struct winlink *wl)
{
  struct cmd_find_state fs;
  cmd_find_from_winlink(&fs, wl, 0);
  notify_add(name, &fs, 0, wl->session, wl->window, 0);
}


/*** DEPENDENCIES:
None
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
None
----------------------------
***/


void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


/*** DEPENDENCIES:
int cmd_find_from_client(struct cmd_find_state *fs, struct client *c, int flags)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return cmd_find_from_nothing(fs, flags);
  }
  if (c->session != 0)
  {
    cmd_find_from_session(fs, c->session, flags);
    return 0;
  }
  cmd_find_clear_state(fs, flags);
  wp_idx = cmd_find_inside_pane(c);
  if ((&wp[wp_idx]) == 0)
  {
    goto unknown_pane;
  }
  s_idx = cmd_find_try_TMUX(c);
  if ((&s[s_idx]) != 0)
  {
    for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      if (window_has_pane(wl->window, wp))
      {
        break;
      }
    }

    if ((&wl[wl_idx]) != 0)
    {
      fs->s = &s[s_idx];
      fs->wl = s->curw;
      fs->w = fs->wl->window;
      fs->wp = fs->w->active;
      cmd_find_log_state(__func__, fs);
      return 0;
    }
  }
  fs->w = wp->window;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    goto unknown_pane;
  }
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
  unknown_pane:
  s_idx = cmd_find_try_TMUX(c);

  if ((&s[s_idx]) != 0)
  {
    cmd_find_from_session(fs, s, flags);
    return 0;
  }
  return cmd_find_from_nothing(fs, flags);
}


----------------------------
None
----------------------------
None
----------------------------
***/


void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


/*** DEPENDENCIES:
None
----------------------------
int cmd_find_from_session_window(struct cmd_find_state *fs, struct session *s, struct window *w, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->w = w;
  if (cmd_find_best_winlink_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
None
----------------------------
***/


void notify_session(const char *name, struct session *s)
{
  struct cmd_find_state fs;
  if (session_alive(s))
  {
    cmd_find_from_session(&fs, s, 0);
  }
  else
    cmd_find_from_nothing(&fs, 0);
  notify_add(name, &fs, 0, s, 0, 0);
}


/*** DEPENDENCIES:
int cmd_find_from_nothing(struct cmd_find_state *fs, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = cmd_find_best_session(0, 0, flags);
  if (fs->s == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
int session_alive(struct session *s)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if ((&s_loop[s_loop_idx]) == s)
    {
      return 1;
    }
  }

  return 0;
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
None
----------------------------
***/


void notify_input(struct window_pane *wp, struct evbuffer *input)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->flags & 0x2000)
    {
      control_notify_input(c, wp, input);
    }
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_notify_input(struct client *c, struct window_pane *wp, struct evbuffer *input)
{
  u_char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct evbuffer *message;
  unsigned int message_idx = 0;
  u_int i;
  if (c->session == 0)
  {
    return;
  }
  buf_idx = EVBUFFER_DATA(input);
  len = EVBUFFER_LENGTH(input);
  if (winlink_find_by_window(&c->session->windows, wp->window) != 0)
  {
    message_idx = evbuffer_new();
    evbuffer_add_printf(message, "%%output %%%u ", wp->id);
    for (i = 0; i < len; i += 1)
    {
      if ((buf[i + buf_idx] < ' ') || (buf[i + buf_idx] == '\\'))
      {
        evbuffer_add_printf(message, "\\%03o", buf[i + buf_idx]);
      }
      else
        evbuffer_add_printf(message, "%c", buf[i + buf_idx]);
    }

    control_write_buffer(c, message);
    evbuffer_free(message);
  }
}


----------------------------
None
----------------------------
***/


