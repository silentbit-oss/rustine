static enum cmd_retval cmd_new_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_find_state *current = &item->shared->current;
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  unsigned int wl_idx = 0;
  struct client *c = cmd_find_client(item, 0, 1);
  int idx = item->target.idx;
  const char *cmd;
  unsigned int cmd_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  const char *tmp;
  unsigned int tmp_idx = 0;
  char **argv;
  unsigned int argv_idx = 0;
  char *cause;
  char *cp;
  unsigned int cp_idx = 0;
  char *cwd;
  unsigned int cwd_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  int argc;
  int detached;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct cmd_find_state fs;
  if (args_has(args, 'a'))
  {
    if ((idx = winlink_shuffle_up(s, wl)) == (-1))
    {
      cmdq_error(item, "no free window indexes");
      return CMD_RETURN_ERROR;
    }
  }
  detached = args_has(args, 'd');
  if (args->argc == 0)
  {
    cmd_idx = options_get_string(s->options, "default-command");
    if (((&cmd[cmd_idx]) != 0) && (cmd[cmd_idx] != '\0'))
    {
      argc = 1;
      argv_idx = (char **) (&(&cmd[cmd_idx]));
    }
    else
    {
      argc = 0;
      argv_idx = 0;
    }
  }
  else
  {
    argc = args->argc;
    argv_idx = args->argv_idx;
  }
  path_idx = 0;
  if ((item->client != 0) && (item->client->session == 0))
  {
    envent_idx = environ_find(item->client->environ, "PATH");
  }
  else
    envent_idx = environ_find(s->environ, "PATH");
  if ((&envent[envent_idx]) != 0)
  {
    path_idx = envent->value;
  }
  if ((tmp_idx = args_get(args, 'c')) != 0)
  {
    cwd_idx = format_single(item, tmp, c, s, 0, 0);
  }
  else
    if ((item->client != 0) && (item->client->session == 0))
  {
    cwd_idx = xstrdup(item->client->cwd_idx);
  }
  else
    cwd_idx = xstrdup(s->cwd_idx);
  if ((tmp_idx = args_get(args, 'n')) != 0)
  {
    name_idx = format_single(item, tmp, c, s, 0, 0);
  }
  else
    name_idx = 0;
  wl_idx = 0;
  if (idx != (-1))
  {
    wl_idx = winlink_find_by_index(&s->windows, idx);
  }
  if (((&wl[wl_idx]) != 0) && args_has(args, 'k'))
  {
    notify_session_window("window-unlinked", s, wl->window);
    wl->flags &= ~((0x1 | 0x2) | 0x4);
    winlink_stack_remove(&s->lastw, wl);
    winlink_remove(&s->windows, wl);
    if ((&wl[wl_idx]) == s->curw)
    {
      detached = 0;
      s->curw = 0;
    }
  }
  if (idx == (-1))
  {
    idx = (-1) - options_get_number(s->options, "base-index");
  }
  wl_idx = session_new(s, name, argc, argv, path, cwd, idx, &cause);
  if ((&wl[wl_idx]) == 0)
  {
    cmdq_error(item, "create window failed: %s", cause);
    free(cause);
    goto error;
  }
  if (!detached)
  {
    session_select(s, wl->idx);
    cmd_find_from_winlink(current, wl, 0);
    server_redraw_session_group(s);
  }
  else
    server_status_session_group(s);
  if (args_has(args, 'P'))
  {
    if ((template_idx = args_get(args, 'F')) == 0)
    {
      template_idx = "#{session_name}:#{window_index}.#{pane_index}";
    }
    cp_idx = format_single(item, template, c, s, wl, 0);
    cmdq_print(item, "%s", cp);
    free(cp);
  }
  cmd_find_from_winlink(&fs, wl, 0);
  hooks_insert(s->hooks, item, &fs, "after-new-window");
  free(name);
  free(cwd);
  return CMD_RETURN_NORMAL;
  error:
  free(name);

  free(cwd);
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
struct winlink *session_new(struct session *s, const char *name, int argc, char **argv, const char *path, const char *cwd, int idx, char **cause)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  u_int hlimit;
  if ((wl_idx = winlink_add(&s->windows, idx)) == 0)
  {
    xasprintf(cause, "index in use: %d", idx);
    return 0;
  }
  wl->session = s;
  shell_idx = options_get_string(s->options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  hlimit = options_get_number(s->options, "history-limit");
  env_idx = environ_for_session(s, 0);
  w_idx = window_create_spawn(name, argc, argv, path, shell, cwd, env, s->tio, s->sx, s->sy, hlimit, cause);
  if ((&w[w_idx]) == 0)
  {
    winlink_remove(&s->windows, wl);
    environ_free(env);
    return 0;
  }
  winlink_set_window(wl, w);
  environ_free(env);
  notify_session_window("window-linked", s, w);
  session_group_synchronize_from(s);
  return wl;
}


----------------------------
struct windows
{
  struct window *rbh_root;
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
void winlink_stack_remove(struct winlink_stack *stack, struct winlink *wl)
{
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  if (wl == 0)
  {
    return;
  }
  for (wl2_idx = stack->tqh_first; (&wl2[wl2_idx]) != 0; wl2_idx = wl2_idx->sentry.tqe_next)
  {
    if ((&wl2[wl2_idx]) == wl)
    {
      do
      {
        if (wl->sentry.tqe_next != 0)
        {
          wl->sentry.tqe_next->sentry.tqe_prev = wl->sentry.tqe_prev;
        }
        else
          stack->tqh_last = wl->sentry.tqe_prev;
        *wl->sentry.tqe_prev = wl->sentry.tqe_next;
        ;
        ;
      }
      while (0);
      return;
    }
  }

}


----------------------------
void cmdq_print(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct window *w;
  unsigned int w_idx = 0;
  va_list ap;
  char *tmp;
  char *msg;
  unsigned int msg_idx = 0;
  __builtin_va_start(ap);
  if (c == 0)
  {
    ;
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      xvasprintf(&tmp, fmt, ap);
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      evbuffer_add(c->stdout_data, msg, strlen(msg));
      free(msg);
    }
    else
      evbuffer_add_vprintf(c->stdout_data, fmt, ap);
    evbuffer_add(c->stdout_data, "\n", 1);
    server_client_push_stdout(c);
  }
  else
  {
    w_idx = c->session->curw->window;
    if (w->active->mode != (&window_copy_mode))
    {
      window_pane_reset_mode(w->active);
      window_pane_set_mode(w->active, &window_copy_mode, 0, 0);
      window_copy_init_for_output(w->active);
    }
    window_copy_vadd(w->active, fmt, ap);
  }
  ;
}


----------------------------
struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


----------------------------
void winlink_remove(struct winlinks *wwl, struct winlink *wl)
{
  struct window *w = wl->window;
  if (w != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&w->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(w, __func__);
  }
  winlinks_RB_REMOVE(wwl, wl);
  free(wl->status_text);
  free(wl);
}


----------------------------
struct client *cmd_find_client(struct cmdq_item *item, const char *target, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  size_t size;
  if (target == 0)
  {
    return cmd_find_current_client(item, quiet);
  }
  copy_idx = xstrdup(target);
  size = strlen(copy);
  if ((size != 0) && (copy[(size - 1) + copy_idx] == ':'))
  {
    copy[(size - 1) + copy_idx] = '\0';
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == 0)
    {
      continue;
    }
    if (strcmp(copy, c->name) == 0)
    {
      break;
    }
    if ((*c->ttyname) == '\0')
    {
      continue;
    }
    if (strcmp(copy, c->ttyname) == 0)
    {
      break;
    }
    if (strncmp(c->ttyname, "/dev/", (sizeof("/dev/")) - 1) != 0)
    {
      continue;
    }
    if (strcmp(copy, (c->ttyname + (sizeof("/dev/"))) - 1) == 0)
    {
      break;
    }
  }

  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "can't find client %s", copy);
  }
  free(copy);
  log_debug("%s: target %s, return %p", __func__, target, c);
  return c;
}


----------------------------
None
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
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
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
None
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
void server_redraw_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_redraw_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      server_redraw_session(s);
    }

  }
}


----------------------------
void server_status_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_status_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      server_status_session(s);
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
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
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
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
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
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


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


