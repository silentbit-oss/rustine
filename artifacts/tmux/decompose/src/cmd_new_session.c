void helper_cmd_new_session_exec_2(struct cmdq_item * const item, struct client * const c, struct session * const s, unsigned int s_idx, int already_attached)
{
  if (!already_attached)
  {
    if ((~c->flags) & 0x2000)
    {
      proc_send(c->peer, MSG_READY, -1, 0, 0);
    }
  }
  else
    if (c->session != 0)
  {
    c->last_session = c->session;
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
}


/*** DEPENDENCIES:
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
None
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


// hint:  ['as_idx_ref is a mutable refrence to unsigned int', 'newname_idx_ref is a mutable refrence to unsigned int', 'retval_ref is a mutable refrence to ']
enum cmd_retval helper_cmd_new_session_exec_1(unsigned int * const as_idx_ref, unsigned int * const newname_idx_ref, enum cmd_retval * const retval_ref, struct cmdq_item * const item, struct args * const args, struct client * const c, char * const newname)
{
  unsigned int as_idx = *as_idx_ref;
  unsigned int newname_idx = *newname_idx_ref;
  enum cmd_retval retval = *retval_ref;
  newname_idx = format_single(item, args_get(args, 's'), c, 0, 0, 0);
  if (!session_check_name(newname))
  {
    cmdq_error(item, "bad session name: %s", newname);
    goto error;
  }
  if ((as_idx = session_find(newname)) != 0)
  {
    if (args_has(args, 'A'))
    {
      retval = cmd_attach_session(item, newname, args_has(args, 'D'), 0, 0, args_has(args, 'E'));
      free(newname);
      return retval;
    }
    cmdq_error(item, "duplicate session: %s", newname);
    goto error;
  }
  *as_idx_ref = as_idx;
  *newname_idx_ref = newname_idx;
  *retval_ref = retval;
}


/*** DEPENDENCIES:
struct session *session_find(const char *name)
{
  struct session s;
  s.name = (char *) name;
  return sessions_RB_FIND(&sessions, &s);
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
int session_check_name(const char *name)
{
  return ((*name) != '\0') && (name[strcspn(name, ":.")] == '\0');
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_new_session_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c = item->client;
  struct session *s;
  unsigned int s_idx = 0;
  struct session *as;
  unsigned int as_idx = 0;
  struct session *groupwith;
  unsigned int groupwith_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  struct termios tio;
  struct termios *tiop;
  unsigned int tiop_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  const char *errstr;
  const char *template;
  unsigned int template_idx = 0;
  const char *group;
  unsigned int group_idx = 0;
  const char *prefix;
  unsigned int prefix_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  const char *cmd;
  unsigned int cmd_idx = 0;
  const char *tmp;
  unsigned int tmp_idx = 0;
  char **argv;
  unsigned int argv_idx = 0;
  char *cause;
  char *cp;
  unsigned int cp_idx = 0;
  char *newname;
  unsigned int newname_idx = 0;
  char *cwd = 0;
  unsigned int cwd_idx = 0;
  int detached;
  int already_attached;
  int idx;
  int argc;
  int is_control = 0;
  u_int sx;
  u_int sy;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct cmd_find_state fs;
  enum cmd_retval retval;
  if (self->entry == (&cmd_has_session_entry))
  {
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 't') && ((args->argc != 0) || args_has(args, 'n')))
  {
    cmdq_error(item, "command or window name given with target");
    return CMD_RETURN_ERROR;
  }
  newname_idx = 0;
  if (args_has(args, 's'))
  {
    helper_cmd_new_session_exec_1(&as_idx, &newname_idx, &retval, item, args, c, newname);
  }
  group_idx = args_get(args, 't');
  if ((&group[group_idx]) != 0)
  {
    groupwith_idx = item->target.s;
    if ((&groupwith[groupwith_idx]) == 0)
    {
      if (!session_check_name(group))
      {
        cmdq_error(item, "bad group name: %s", group);
        goto error;
      }
      sg_idx = session_group_find(group);
    }
    else
      sg_idx = session_group_contains(groupwith);
    if ((&sg[sg_idx]) != 0)
    {
      prefix_idx = sg->name;
    }
    else
      if ((&groupwith[groupwith_idx]) != 0)
    {
      prefix_idx = groupwith->name;
    }
    else
      prefix_idx = &group[group_idx];
  }
  else
  {
    groupwith_idx = 0;
    sg_idx = 0;
    prefix_idx = 0;
  }
  detached = args_has(args, 'd');
  if (c == 0)
  {
    detached = 1;
  }
  else
    if (c->flags & 0x2000)
  {
    is_control = 1;
  }
  already_attached = 0;
  if ((c != 0) && (c->session != 0))
  {
    already_attached = 1;
  }
  if ((tmp_idx = args_get(args, 'c')) != 0)
  {
    cwd_idx = format_single(item, tmp, c, 0, 0, 0);
  }
  else
    if (((c != 0) && (c->session == 0)) && (c->cwd != 0))
  {
    cwd_idx = xstrdup(c->cwd_idx);
  }
  else
    cwd_idx = xstrdup(".");
  if (((!detached) && (!already_attached)) && (c->tty.fd != (-1)))
  {
    if (server_client_check_nested(item->client))
    {
      cmdq_error(item, "sessions should be nested with care, unset $TMUX to force");
      return CMD_RETURN_ERROR;
    }
    if (tcgetattr(c->tty.fd, &tio) != 0)
    {
      fatal("tcgetattr failed");
    }
    tiop_idx = &tio;
  }
  else
    tiop_idx = 0;
  if ((!detached) && (!already_attached))
  {
    if (server_client_open(c, &cause) != 0)
    {
      cmdq_error(item, "open terminal failed: %s", cause);
      free(cause);
      goto error;
    }
  }
  if (!detached)
  {
    sx = c->tty.sx;
    sy = c->tty.sy;
    if (((!is_control) && (sy > 0)) && options_get_number(global_s_options, "status"))
    {
      sy -= 1;
    }
  }
  else
  {
    sx = 80;
    sy = 24;
  }
  if ((is_control || detached) && args_has(args, 'x'))
  {
    sx = strtonum(args_get(args, 'x'), 1, 65535, &errstr);
    if (errstr != 0)
    {
      cmdq_error(item, "width %s", errstr);
      goto error;
    }
  }
  if ((is_control || detached) && args_has(args, 'y'))
  {
    sy = strtonum(args_get(args, 'y'), 1, 65535, &errstr);
    if (errstr != 0)
    {
      cmdq_error(item, "height %s", errstr);
      goto error;
    }
  }
  if (sx == 0)
  {
    sx = 1;
  }
  if (sy == 0)
  {
    sy = 1;
  }
  argc = -1;
  argv_idx = 0;
  if ((!args_has(args, 't')) && (args->argc != 0))
  {
    argc = args->argc;
    argv_idx = args->argv_idx;
  }
  else
    if (((&sg[sg_idx]) == 0) && ((&groupwith[groupwith_idx]) == 0))
  {
    cmd_idx = options_get_string(global_s_options, "default-command");
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
  path_idx = 0;
  if ((c != 0) && (c->session == 0))
  {
    envent_idx = environ_find(c->environ, "PATH");
  }
  else
    envent_idx = environ_find(global_environ, "PATH");
  if ((&envent[envent_idx]) != 0)
  {
    path_idx = envent->value;
  }
  env_idx = environ_create();
  if ((c != 0) && (!args_has(args, 'E')))
  {
    environ_update(global_s_options, c->environ, env);
  }
  idx = (-1) - options_get_number(global_s_options, "base-index");
  s_idx = session_create(prefix, newname, argc, argv, path, cwd, env, tiop, idx, sx, sy, &cause);
  environ_free(env);
  if ((&s[s_idx]) == 0)
  {
    cmdq_error(item, "create session failed: %s", cause);
    free(cause);
    goto error;
  }
  if ((argc >= 0) && ((tmp_idx = args_get(args, 'n')) != 0))
  {
    cp_idx = format_single(item, tmp, c, s, 0, 0);
    w_idx = s->curw->window;
    window_set_name(w, cp);
    options_set_number(w->options, "automatic-rename", 0);
    free(cp);
  }
  if ((&group[group_idx]) != 0)
  {
    if ((&sg[sg_idx]) == 0)
    {
      if ((&groupwith[groupwith_idx]) != 0)
      {
        sg_idx = session_group_new(groupwith->name);
        session_group_add(sg, groupwith);
      }
      else
        sg_idx = session_group_new(group);
    }
    session_group_add(sg, s);
    session_group_synchronize_to(s);
    session_select(s, winlinks_RB_MINMAX(&s->windows, -1)->idx);
  }
  notify_session("session-created", s);
  if (!detached)
  {
    helper_cmd_new_session_exec_2(item, c, s, s_idx, already_attached);
  }
  recalculate_sizes();
  server_update_socket();
  if (cfg_finished)
  {
    cfg_show_causes(s);
  }
  if (args_has(args, 'P'))
  {
    if ((template_idx = args_get(args, 'F')) == 0)
    {
      template_idx = "#{session_name}:";
    }
    cp_idx = format_single(item, template, c, s, 0, 0);
    cmdq_print(item, "%s", cp);
    free(cp);
  }
  if (!detached)
  {
    c->flags |= 0x80;
    cmd_find_from_session(&item->shared->current, s, 0);
  }
  cmd_find_from_session(&fs, s, 0);
  hooks_insert(s->hooks, item, &fs, "after-new-session");
  free(cwd);
  free(newname);
  return CMD_RETURN_NORMAL;
  error:
  free(cwd);

  free(newname);
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
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
struct windows
{
  struct window *rbh_root;
}
----------------------------
extern int cfg_finished
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
void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
}


----------------------------
enum cmd_retval helper_cmd_new_session_exec_1(unsigned int * const as_idx_ref, unsigned int * const newname_idx_ref, enum cmd_retval * const retval_ref, struct cmdq_item * const item, struct args * const args, struct client * const c, char * const newname)
{
  unsigned int as_idx = *as_idx_ref;
  unsigned int newname_idx = *newname_idx_ref;
  enum cmd_retval retval = *retval_ref;
  newname_idx = format_single(item, args_get(args, 's'), c, 0, 0, 0);
  if (!session_check_name(newname))
  {
    cmdq_error(item, "bad session name: %s", newname);
    goto error;
  }
  if ((as_idx = session_find(newname)) != 0)
  {
    if (args_has(args, 'A'))
    {
      retval = cmd_attach_session(item, newname, args_has(args, 'D'), 0, 0, args_has(args, 'E'));
      free(newname);
      return retval;
    }
    cmdq_error(item, "duplicate session: %s", newname);
    goto error;
  }
  *as_idx_ref = as_idx;
  *newname_idx_ref = newname_idx;
  *retval_ref = retval;
}


----------------------------
int session_check_name(const char *name)
{
  return ((*name) != '\0') && (name[strcspn(name, ":.")] == '\0');
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


----------------------------
extern const struct cmd_entry cmd_has_session_entry
----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
void session_group_add(struct session_group *sg, struct session *s)
{
  if (session_group_contains(s) == 0)
  {
    do
    {
      s->gentry.tqe_next = 0;
      s->gentry.tqe_prev = (&sg->sessions)->tqh_last;
      *(&sg->sessions)->tqh_last = s;
      (&sg->sessions)->tqh_last = &s->gentry.tqe_next;
    }
    while (0);
  }
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
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
struct session_group *session_group_contains(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  for (sg_idx = session_groups_RB_MINMAX(&session_groups, -1); (&sg[sg_idx]) != 0; sg_idx = session_groups_RB_NEXT(sg_idx))
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      if ((&s[s_idx]) == target)
      {
        return sg;
      }
    }

  }

  return 0;
}


----------------------------
struct environ *environ_create(void)
{
  struct environ *env;
  unsigned int env_idx = 0;
  env_idx = xcalloc(1, sizeof(*env_idx));
  do
  {
    env->rbh_root = 0;
  }
  while (0);
  return env;
}


----------------------------
void helper_cmd_new_session_exec_2(struct cmdq_item * const item, struct client * const c, struct session * const s, unsigned int s_idx, int already_attached)
{
  if (!already_attached)
  {
    if ((~c->flags) & 0x2000)
    {
      proc_send(c->peer, MSG_READY, -1, 0, 0);
    }
  }
  else
    if (c->session != 0)
  {
    c->last_session = c->session;
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
void session_group_synchronize_to(struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *target;
  unsigned int target_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    return;
  }
  target_idx = 0;
  for (target_idx = (&sg->sessions)->tqh_first; (&target[target_idx]) != 0; target_idx = target_idx->gentry.tqe_next)
  {
    if ((&target[target_idx]) != s)
    {
      break;
    }
  }

  if ((&target[target_idx]) != 0)
  {
    session_group_synchronize1(target, s);
  }
}


----------------------------
void environ_free(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct environ_entry *envent1;
  unsigned int envent1_idx = 0;
  for (envent_idx = environ_RB_MINMAX(env, -1); ((&envent[envent_idx]) != 0) && ((envent1_idx = environ_RB_NEXT(envent), 1)); envent_idx = &envent1[envent1_idx])
  {
    environ_RB_REMOVE(env, envent);
    free(envent->name);
    free(envent->value);
    free(envent);
  }

  free(env);
}


----------------------------
struct winlink *winlinks_RB_MINMAX(struct winlinks *head, int val)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}


----------------------------
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
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
struct session_group *session_group_new(const char *name)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_find(name)) != 0)
  {
    return sg;
  }
  sg_idx = xcalloc(1, sizeof(*sg_idx));
  sg->name = xstrdup(name);
  do
  {
    (&sg->sessions)->tqh_first = 0;
    (&sg->sessions)->tqh_last = &(&sg->sessions)->tqh_first;
  }
  while (0);
  session_groups_RB_INSERT(&session_groups, sg);
  return sg;
}


----------------------------
None
----------------------------
void cfg_show_causes(struct session *s)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int i;
  if ((s == 0) || (cfg_ncauses == 0))
  {
    return;
  }
  wp_idx = s->curw->window->active;
  window_pane_set_mode(wp, &window_copy_mode, 0, 0);
  window_copy_init_for_output(wp);
  for (i = 0; i < cfg_ncauses; i += 1)
  {
    window_copy_add(wp, "%s", cfg_causes[i]);
    free(cfg_causes[i]);
  }

  free(cfg_causes);
  cfg_causes = 0;
  cfg_ncauses = 0;
}


----------------------------
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
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
struct session *session_create(const char *prefix, const char *name, int argc, char **argv, const char *path, const char *cwd, struct environ *env, struct termios *tio, int idx, u_int sx, u_int sy, char **cause)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  s_idx = xcalloc(1, sizeof(*s_idx));
  s->references = 1;
  s->flags = 0;
  s->cwd = xstrdup(cwd);
  s->curw = 0;
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  s->environ = environ_create();
  if (env != 0)
  {
    environ_copy(env, s->environ);
  }
  s->options = options_create(global_s_options);
  s->hooks = hooks_create(global_hooks);
  status_update_saved(s);
  s->tio = 0;
  if (tio != 0)
  {
    s->tio = xmalloc(sizeof(*s->tio));
    memcpy(s->tio, tio, sizeof(*s->tio));
  }
  s->sx = sx;
  s->sy = sy;
  if (name != 0)
  {
    s->name = xstrdup(name);
    s->id = next_session_id;
    next_session_id += 1;
  }
  else
  {
    s->name = 0;
    do
    {
      s->id = next_session_id;
      next_session_id += 1;
      free(s->name);
      if (prefix != 0)
      {
        xasprintf(&s->name, "%s-%u", prefix, s->id);
      }
      else
        xasprintf(&s->name, "%u", s->id);
    }
    while (sessions_RB_FIND(&sessions, s) != 0);
  }
  sessions_RB_INSERT(&sessions, s);
  log_debug("new session %s $%u", s->name, s->id);
  if (gettimeofday(&s->creation_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  session_update_activity(s, &s->creation_time);
  if (argc >= 0)
  {
    wl_idx = session_new(s, 0, argc, argv, path, cwd, idx, cause);
    if ((&wl[wl_idx]) == 0)
    {
      session_destroy(s, __func__);
      return 0;
    }
    session_select(s, (&s->windows)->rbh_root->idx);
  }
  log_debug("session %s created", s->name);
  return s;
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
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
struct session_group *session_group_find(const char *name)
{
  struct session_group sg;
  sg.name = name;
  return session_groups_RB_FIND(&session_groups, &sg);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


