void control_write_buffer(struct client *c, struct evbuffer *buffer)
{
  evbuffer_add_buffer(c->stdout_data, buffer);
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static enum cmd_retval control_error(struct cmdq_item *item, void *data)
{
  struct client *c = item->client;
  char *error = data;
  cmdq_guard(item, "begin", 1);
  control_write(c, "parse error: %s", error);
  cmdq_guard(item, "error", 1);
  free(error);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void cmdq_guard(struct cmdq_item *item, const char *guard, int flags)
{
  struct client *c = item->client;
  if ((c == 0) || (!(c->flags & 0x2000)))
  {
    return;
  }
  evbuffer_add_printf(c->stdout_data, "%%%s %ld %u %d\n", guard, (long) item->time, item->number, flags);
  server_client_push_stdout(c);
}


----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


void control_callback(struct client *c, int closed, void *data)
{
  char *line;
  unsigned int line_idx = 0;
  char *cause;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  if (closed)
  {
    c->flags |= 0x4;
  }
  for (;;)
  {
    line_idx = evbuffer_readln(c->stdin_data, 0, EVBUFFER_EOL_LF);
    if ((&line[line_idx]) == 0)
    {
      break;
    }
    if (line[line_idx] == '\0')
    {
      c->flags |= 0x4;
      break;
    }
    cmdlist_idx = cmd_string_parse(line, 0, 0, &cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      item_idx = cmdq_get_callback1("control_error", control_error, cause);
      cmdq_append(c, item);
    }
    else
    {
      for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
      {
        cmd->flags |= 0x1;
      }

      item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
      cmdq_append(c, item);
      cmd_list_free(cmdlist);
    }
    free(line);
  }

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
void cmdq_append(struct client *c, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct cmdq_list *queue = cmdq_get(c);
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
    do
    {
      item->entry.tqe_next = 0;
      item->entry.tqe_prev = queue->tqh_last;
      *queue->tqh_last = &item[item_idx];
      queue->tqh_last = &item->entry.tqe_next;
    }
    while (0);
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


----------------------------
static enum cmd_retval control_error(struct cmdq_item *item, void *data)
{
  struct client *c = item->client;
  char *error = data;
  cmdq_guard(item, "begin", 1);
  control_write(c, "parse error: %s", error);
  cmdq_guard(item, "error", 1);
  free(error);
  return CMD_RETURN_NORMAL;
}


----------------------------
struct cmdq_item *cmdq_get_callback1(const char *name, cmdq_cb cb, void *data)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  char *tmp;
  xasprintf(&tmp, "callback[%s]", name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_CALLBACK;
  item->group = 0;
  item->flags = 0;
  item->cb = cb;
  item->data = data;
  return item;
}


----------------------------
None
----------------------------
***/


