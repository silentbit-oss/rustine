static enum cmd_retval cmd_display_panes_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
***/


static void cmd_display_panes_callback(struct client *c, struct window_pane *wp)
{
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *template;
  unsigned int template_idx = 0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *expanded;
  char *cause;
  template_idx = c->identify_callback_data;
  if (wp == 0)
  {
    goto out;
  }
  xasprintf(&expanded, "%%%u", wp->id);
  cmd_idx = cmd_template_replace(template, expanded, 1);
  cmdlist_idx = cmd_string_parse(cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_display_panes_error", cmd_display_panes_error, cause);
    }
    else
      new_item_idx = 0;
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
    cmd_list_free(cmdlist);
  }
  if ((&new_item[new_item_idx]) != 0)
  {
    cmdq_append(c, new_item);
  }
  free(cmd);
  free(expanded);
  out:
  free(c->identify_callback_data);

  c->identify_callback_data = 0;
  c->identify_callback = 0;
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
char *cmd_template_replace(const char *template, const char *s, int idx)
{
  char ch;
  char *buf;
  unsigned int buf_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  const char quote[] = "\"\\$";
  int replaced;
  int quoted;
  size_t len;
  if (strchr(template, '%') == 0)
  {
    return xstrdup(template);
  }
  buf_idx = xmalloc(1);
  buf[buf_idx] = '\0';
  len = 0;
  replaced = 0;
  ptr_idx = template;
  while (ptr[ptr_idx] != '\0')
  {
    helper_cmd_template_replace_1(&ch, &buf_idx, &ptr_idx, &cp_idx, &replaced, &quoted, &len, s, idx, buf, ptr, cp, quote);
  }

  return buf;
}


----------------------------
static enum cmd_retval cmd_display_panes_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
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


static enum cmd_retval cmd_display_panes_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  u_int delay;
  char *cause;
  if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  if (c->identify_callback != 0)
  {
    return CMD_RETURN_NORMAL;
  }
  c->identify_callback = cmd_display_panes_callback;
  if (args->argc != 0)
  {
    c->identify_callback_data = xstrdup(args->argv[0]);
  }
  else
    c->identify_callback_data = xstrdup("select-pane -t '%%'");
  s_idx = c->session;
  if (args_has(args, 'd'))
  {
    delay = args_strtonum(args, 'd', 0, 4294967295U, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "delay %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
  }
  else
    delay = options_get_number(s->options, "display-panes-time");
  server_client_set_identify(c, delay);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void server_client_set_identify(struct client *c, u_int delay)
{
  struct timeval tv;
  tv.tv_sec = delay / 1000;
  tv.tv_usec = (delay % 1000) * 1000L;
  if (event_initialized(&c->identify_timer))
  {
    evtimer_del(&c->identify_timer);
  }
  evtimer_set(&c->identify_timer, server_client_callback_identify, c);
  if (delay != 0)
  {
    evtimer_add(&c->identify_timer, &tv);
  }
  c->flags |= 0x100;
  c->tty.flags |= 0x2 | 0x1;
  server_redraw_client(c);
}


----------------------------
static void cmd_display_panes_callback(struct client *c, struct window_pane *wp)
{
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *template;
  unsigned int template_idx = 0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *expanded;
  char *cause;
  template_idx = c->identify_callback_data;
  if (wp == 0)
  {
    goto out;
  }
  xasprintf(&expanded, "%%%u", wp->id);
  cmd_idx = cmd_template_replace(template, expanded, 1);
  cmdlist_idx = cmd_string_parse(cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_display_panes_error", cmd_display_panes_error, cause);
    }
    else
      new_item_idx = 0;
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
    cmd_list_free(cmdlist);
  }
  if ((&new_item[new_item_idx]) != 0)
  {
    cmdq_append(c, new_item);
  }
  free(cmd);
  free(expanded);
  out:
  free(c->identify_callback_data);

  c->identify_callback_data = 0;
  c->identify_callback = 0;
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
long long args_strtonum(struct args *args, u_char ch, long long minval, long long maxval, char **cause)
{
  const char *errstr;
  long long ll;
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    *cause = xstrdup("missing");
    return 0;
  }
  ll = strtonum(entry->value, minval, maxval, &errstr);
  if (errstr != 0)
  {
    *cause = xstrdup(errstr);
    return 0;
  }
  *cause = 0;
  return ll;
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


