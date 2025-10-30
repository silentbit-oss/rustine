static enum cmd_retval cmd_detach_client_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c;
  unsigned int c_idx = 0;
  struct client *cloop;
  unsigned int cloop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  enum msgtype msgtype;
  const char *cmd = args_get(args, 'E');
  if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  if (self->entry == (&cmd_suspend_client_entry))
  {
    server_client_suspend(c);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'P'))
  {
    msgtype = MSG_DETACHKILL;
  }
  else
    msgtype = MSG_DETACH;
  if (args_has(args, 's'))
  {
    s_idx = item->source.s_idx;
    if ((&s[s_idx]) == 0)
    {
      return CMD_RETURN_NORMAL;
    }
    for (cloop_idx = (&clients)->tqh_first; (&cloop[cloop_idx]) != 0; cloop_idx = cloop_idx->entry.tqe_next)
    {
      if (cloop->session == (&s[s_idx]))
      {
        if (cmd != 0)
        {
          server_client_exec(cloop, cmd);
        }
        else
          server_client_detach(cloop, msgtype);
      }
    }

    return CMD_RETURN_STOP;
  }
  if (args_has(args, 'a'))
  {
    for (cloop_idx = (&clients)->tqh_first; (&cloop[cloop_idx]) != 0; cloop_idx = cloop_idx->entry.tqe_next)
    {
      if ((cloop->session != 0) && ((&cloop[cloop_idx]) != (&c[c_idx])))
      {
        if (cmd != 0)
        {
          server_client_exec(cloop, cmd);
        }
        else
          server_client_detach(cloop, msgtype);
      }
    }

    return CMD_RETURN_NORMAL;
  }
  if (cmd != 0)
  {
    server_client_exec(c, cmd);
  }
  else
    server_client_detach(c, msgtype);
  return CMD_RETURN_STOP;
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
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
}
----------------------------
void server_client_exec(struct client *c, const char *cmd)
{
  struct session *s = c->session;
  char *msg;
  unsigned int msg_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  size_t cmdsize;
  size_t shellsize;
  if ((*cmd) == '\0')
  {
    return;
  }
  cmdsize = strlen(cmd) + 1;
  if (s != 0)
  {
    shell_idx = options_get_string(s->options, "default-shell");
  }
  else
    shell_idx = options_get_string(global_s_options, "default-shell");
  shellsize = strlen(shell) + 1;
  msg_idx = xmalloc(cmdsize + shellsize);
  memcpy(msg, cmd, cmdsize);
  memcpy((&msg[msg_idx]) + cmdsize, shell, shellsize);
  proc_send(c->peer, MSG_EXEC, -1, msg, cmdsize + shellsize);
  free(msg);
}


----------------------------
void server_client_suspend(struct client *c)
{
  struct session *s = c->session;
  if ((s == 0) || (c->flags & 0x1000))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  c->flags |= 0x40;
  proc_send(c->peer, MSG_SUSPEND, -1, 0, 0);
}


----------------------------
extern const struct cmd_entry cmd_suspend_client_entry
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


