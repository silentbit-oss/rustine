static void cmd_confirm_before_free(void *data)
{
  struct cmd_confirm_before_data *cdata = data;
  free(cdata->cmd);
  free(cdata);
}


/*** DEPENDENCIES:
struct cmd_confirm_before_data
{
  char *cmd;
}
----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_confirm_before_error(struct cmdq_item *item, void *data)
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


static int cmd_confirm_before_callback(struct client *c, void *data, const char *s, int done)
{
  struct cmd_confirm_before_data *cdata = data;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  if (c->flags & 0x200)
  {
    return 0;
  }
  if ((s == 0) || ((*s) == '\0'))
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  cmdlist_idx = cmd_string_parse(cdata->cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_confirm_before_error", cmd_confirm_before_error, cause);
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
  return 0;
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
struct cmd_confirm_before_data
{
  char *cmd;
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
static enum cmd_retval cmd_confirm_before_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
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


static enum cmd_retval cmd_confirm_before_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_confirm_before_data *cdata;
  unsigned int cdata_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *copy;
  char *new_prompt;
  char *ptr;
  unsigned int ptr_idx = 0;
  const char *prompt;
  unsigned int prompt_idx = 0;
  if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  if ((prompt_idx = args_get(args, 'p')) != 0)
  {
    xasprintf(&new_prompt, "%s ", prompt);
  }
  else
  {
    ptr_idx = (copy = xstrdup(args->argv[0]));
    cmd_idx = strsep(&(&ptr[ptr_idx]), " \t");
    xasprintf(&new_prompt, "Confirm '%s'? (y/n) ", cmd);
    free(copy);
  }
  cdata_idx = xmalloc(sizeof(*cdata_idx));
  cdata->cmd = xstrdup(args->argv[0]);
  status_prompt_set(c, new_prompt, 0, cmd_confirm_before_callback, cmd_confirm_before_free, cdata, 0x1);
  free(new_prompt);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void status_prompt_set(struct client *c, const char *msg, const char *input, prompt_input_cb inputcb, prompt_free_cb freecb, void *data, int flags)
{
  unsigned int input_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *cp;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  if ((&input[input_idx]) == 0)
  {
    input_idx = "";
  }
  if (flags & 0x8)
  {
    tmp_idx = xstrdup(input);
  }
  else
    tmp_idx = format_expand_time(ft, input, t);
  status_message_clear(c);
  status_prompt_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  c->prompt_string = format_expand_time(ft, msg, t);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_inputcb = inputcb;
  c->prompt_freecb = freecb;
  c->prompt_data = data;
  c->prompt_hindex = 0;
  c->prompt_flags = flags;
  c->prompt_mode = PROMPT_ENTRY;
  if ((~flags) & 0x4)
  {
    c->tty.flags |= 0x1 | 0x2;
  }
  c->flags |= 0x10;
  if ((flags & 0x4) && (tmp[tmp_idx] != '\0'))
  {
    xasprintf(&cp, "=%s", tmp);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
  }
  free(tmp);
  format_free(ft);
}


----------------------------
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
struct cmd_confirm_before_data
{
  char *cmd;
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
static int cmd_confirm_before_callback(struct client *c, void *data, const char *s, int done)
{
  struct cmd_confirm_before_data *cdata = data;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  if (c->flags & 0x200)
  {
    return 0;
  }
  if ((s == 0) || ((*s) == '\0'))
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  cmdlist_idx = cmd_string_parse(cdata->cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_confirm_before_error", cmd_confirm_before_error, cause);
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
  return 0;
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
static void cmd_confirm_before_free(void *data)
{
  struct cmd_confirm_before_data *cdata = data;
  free(cdata->cmd);
  free(cdata);
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
None
----------------------------
***/


