static enum cmd_retval cmd_set_environment_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct environ *env;
  unsigned int env_idx = 0;
  const char *name;
  unsigned int name_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  const char *target;
  unsigned int target_idx = 0;
  name_idx = args->argv[0];
  if (name[name_idx] == '\0')
  {
    cmdq_error(item, "empty variable name");
    return CMD_RETURN_ERROR;
  }
  if (strchr(name, '=') != 0)
  {
    cmdq_error(item, "variable name contains =");
    return CMD_RETURN_ERROR;
  }
  if (args->argc < 2)
  {
    value_idx = 0;
  }
  else
    value_idx = args->argv[1];
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
  if (args_has(self->args, 'u'))
  {
    if ((&value[value_idx]) != 0)
    {
      cmdq_error(item, "can't specify a value with -u");
      return CMD_RETURN_ERROR;
    }
    environ_unset(env, name);
  }
  else
    if (args_has(self->args, 'r'))
  {
    if ((&value[value_idx]) != 0)
    {
      cmdq_error(item, "can't specify a value with -r");
      return CMD_RETURN_ERROR;
    }
    environ_clear(env, name);
  }
  else
  {
    if ((&value[value_idx]) == 0)
    {
      cmdq_error(item, "no value specified");
      return CMD_RETURN_ERROR;
    }
    environ_set(env, name, "%s", value);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
void environ_clear(struct environ *env, const char *name)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  if ((envent_idx = environ_find(env, name)) != 0)
  {
    free(envent->value);
    envent->value = 0;
  }
  else
  {
    envent_idx = xmalloc(sizeof(*envent_idx));
    envent->name = xstrdup(name);
    envent->value = 0;
    environ_RB_INSERT(env, envent);
  }
}


----------------------------
void environ_set(struct environ *env, const char *name, const char *fmt, ...)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  va_list ap;
  __builtin_va_start(ap);
  if ((envent_idx = environ_find(env, name)) != 0)
  {
    free(envent->value);
    xvasprintf(&envent->value, fmt, ap);
  }
  else
  {
    envent_idx = xmalloc(sizeof(*envent_idx));
    envent->name = xstrdup(name);
    xvasprintf(&envent->value, fmt, ap);
    environ_RB_INSERT(env, envent);
  }
  ;
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
void environ_unset(struct environ *env, const char *name)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  if ((envent_idx = environ_find(env, name)) == 0)
  {
    return;
  }
  environ_RB_REMOVE(env, envent);
  free(envent->name);
  free(envent->value);
  free(envent);
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


