static char *cmd_show_environment_escape(struct environ_entry *envent)
{
  const char *value = envent->value;
  char c;
  char *out;
  unsigned int out_idx = 0;
  char *ret;
  out_idx = (ret = xmalloc((strlen(value) * 2) + 1));
  while ((c = *(value++)) != '\0')
  {
    if ((((c == '$') || (c == '`')) || (c == '"')) || (c == '\\'))
    {
      out[out_idx] = '\\';
      out_idx += 1;
    }
    out[out_idx] = c;
    out_idx += 1;
  }

  out[out_idx] = '\0';
  return ret;
}


/*** DEPENDENCIES:
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
None
----------------------------
***/


static void cmd_show_environment_print(struct cmd *self, struct cmdq_item *item, struct environ_entry *envent)
{
  char *escaped;
  unsigned int escaped_idx = 0;
  if (!args_has(self->args, 's'))
  {
    if (envent->value != 0)
    {
      cmdq_print(item, "%s=%s", envent->name, envent->value);
    }
    else
      cmdq_print(item, "-%s", envent->name);
    return;
  }
  if (envent->value != 0)
  {
    escaped_idx = cmd_show_environment_escape(envent);
    cmdq_print(item, "%s=\"%s\"; export %s;", envent->name, escaped, envent->name);
    free(escaped);
  }
  else
    cmdq_print(item, "unset %s;", envent->name);
}


/*** DEPENDENCIES:
None
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
static char *cmd_show_environment_escape(struct environ_entry *envent)
{
  const char *value = envent->value;
  char c;
  char *out;
  unsigned int out_idx = 0;
  char *ret;
  out_idx = (ret = xmalloc((strlen(value) * 2) + 1));
  while ((c = *(value++)) != '\0')
  {
    if ((((c == '$') || (c == '`')) || (c == '"')) || (c == '\\'))
    {
      out[out_idx] = '\\';
      out_idx += 1;
    }
    out[out_idx] = c;
    out_idx += 1;
  }

  out[out_idx] = '\0';
  return ret;
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


static enum cmd_retval cmd_show_environment_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct environ *env;
  unsigned int env_idx = 0;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  const char *target;
  unsigned int target_idx = 0;
  if ((target_idx = args_get(args, 't')) != 0)
  {
    if (item->target.s == 0)
    {
      cmdq_error(item, "no such session: %s", target);
      return CMD_RETURN_ERROR;
    }
  }
  if (args_has(self->args, 'g'))
  {
    env_idx = global_environ;
  }
  else
  {
    if (item->target.s == 0)
    {
      target_idx = args_get(args, 't');
      if ((&target[target_idx]) != 0)
      {
        cmdq_error(item, "no such session: %s", target);
      }
      else
        cmdq_error(item, "no current session");
      return CMD_RETURN_ERROR;
    }
    env_idx = item->target.s->environ;
  }
  if (args->argc != 0)
  {
    envent_idx = environ_find(env, args->argv[0]);
    if ((&envent[envent_idx]) == 0)
    {
      cmdq_error(item, "unknown variable: %s", args->argv[0]);
      return CMD_RETURN_ERROR;
    }
    cmd_show_environment_print(self, item, envent);
    return CMD_RETURN_NORMAL;
  }
  envent_idx = environ_first(env);
  while ((&envent[envent_idx]) != 0)
  {
    cmd_show_environment_print(self, item, envent);
    envent_idx = environ_next(envent_idx);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct environ_entry *environ_first(struct environ *env)
{
  return environ_RB_MINMAX(env, -1);
}


----------------------------
static void cmd_show_environment_print(struct cmd *self, struct cmdq_item *item, struct environ_entry *envent)
{
  char *escaped;
  unsigned int escaped_idx = 0;
  if (!args_has(self->args, 's'))
  {
    if (envent->value != 0)
    {
      cmdq_print(item, "%s=%s", envent->name, envent->value);
    }
    else
      cmdq_print(item, "-%s", envent->name);
    return;
  }
  if (envent->value != 0)
  {
    escaped_idx = cmd_show_environment_escape(envent);
    cmdq_print(item, "%s=\"%s\"; export %s;", envent->name, escaped, envent->name);
    free(escaped);
  }
  else
    cmdq_print(item, "unset %s;", envent->name);
}


----------------------------
None
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct environ_entry *environ_next(struct environ_entry *envent)
{
  return environ_RB_NEXT(envent);
}


----------------------------
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
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


