static enum cmd_retval cmd_set_hook_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct hooks *hooks;
  unsigned int hooks_idx = 0;
  struct hook *hook;
  unsigned int hook_idx = 0;
  char *cause;
  char *tmp;
  unsigned int tmp_idx = 0;
  const char *name;
  unsigned int name_idx = 0;
  const char *cmd;
  unsigned int cmd_idx = 0;
  const char *target;
  unsigned int target_idx = 0;
  if (args_has(args, 'g'))
  {
    hooks_idx = global_hooks;
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
    hooks_idx = item->target.s->hooks_idx;
  }
  if (self->entry == (&cmd_show_hooks_entry))
  {
    hook_idx = hooks_first(hooks);
    while ((&hook[hook_idx]) != 0)
    {
      tmp_idx = cmd_list_print(hook->cmdlist);
      cmdq_print(item, "%s -> %s", hook->name, tmp);
      free(tmp);
      hook_idx = hooks_next(hook_idx);
    }

    return CMD_RETURN_NORMAL;
  }
  name_idx = args->argv[0];
  if (name[name_idx] == '\0')
  {
    cmdq_error(item, "invalid hook name");
    return CMD_RETURN_ERROR;
  }
  if (args->argc < 2)
  {
    cmd_idx = 0;
  }
  else
    cmd_idx = args->argv[1];
  if (args_has(args, 'u'))
  {
    if ((&cmd[cmd_idx]) != 0)
    {
      cmdq_error(item, "command passed to unset hook: %s", name);
      return CMD_RETURN_ERROR;
    }
    hooks_remove(hooks, name);
    return CMD_RETURN_NORMAL;
  }
  if ((&cmd[cmd_idx]) == 0)
  {
    cmdq_error(item, "no command to set hook: %s", name);
    return CMD_RETURN_ERROR;
  }
  cmdlist_idx = cmd_string_parse(cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      cmdq_error(item, "%s", cause);
      free(cause);
    }
    return CMD_RETURN_ERROR;
  }
  hooks_add(hooks, name, cmdlist);
  cmd_list_free(cmdlist);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
}


----------------------------
void cmd_list_free(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd *cmd1;
  unsigned int cmd1_idx = 0;
  if ((--cmdlist->references) != 0)
  {
    return;
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; ((&cmd[cmd_idx]) != 0) && ((cmd1_idx = cmd->qentry.tqe_next, 1)); cmd_idx = &cmd1[cmd1_idx])
  {
    do
    {
      if (cmd->qentry.tqe_next != 0)
      {
        cmd->qentry.tqe_next->qentry.tqe_prev = cmd->qentry.tqe_prev;
      }
      else
        (&cmdlist->list)->tqh_last = cmd->qentry.tqe_prev;
      *cmd->qentry.tqe_prev = cmd->qentry.tqe_next;
      ;
      ;
    }
    while (0);
    args_free(cmd->args);
    free(cmd->file);
    free(cmd);
  }

  free(cmdlist);
}


----------------------------
struct hook *hooks_next(struct hook *hook)
{
  return hooks_tree_RB_NEXT(hook);
}


----------------------------
char *cmd_list_print(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char *this;
  unsigned int this_idx = 0;
  size_t len;
  len = 1;
  buf_idx = xcalloc(1, len);
  for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    this_idx = cmd_print(cmd);
    len += strlen(this) + 3;
    buf_idx = xrealloc(buf_idx, len);
    strlcat(buf, this, len);
    if (cmd->qentry.tqe_next != 0)
    {
      strlcat(buf, " ; ", len);
    }
    free(this);
  }

  return buf;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
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
void hooks_add(struct hooks *hooks, const char *name, struct cmd_list *cmdlist)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  if ((hook_idx = hooks_find1(hooks, name)) != 0)
  {
    hooks_free1(hooks, hook);
  }
  hook_idx = xcalloc(1, sizeof(*hook_idx));
  hook->name = xstrdup(name);
  hook->cmdlist = cmdlist;
  hook->cmdlist->references += 1;
  hooks_tree_RB_INSERT(&hooks->tree, hook);
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
struct hook *hooks_first(struct hooks *hooks)
{
  return hooks_tree_RB_MINMAX(&hooks->tree, -1);
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
extern const struct cmd_entry cmd_show_hooks_entry
----------------------------
void hooks_remove(struct hooks *hooks, const char *name)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  if ((hook_idx = hooks_find1(hooks, name)) != 0)
  {
    hooks_free1(hooks, hook);
  }
}


----------------------------
None
----------------------------
***/


