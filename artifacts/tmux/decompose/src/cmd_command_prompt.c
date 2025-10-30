static void cmd_command_prompt_free(void *data)
{
  struct cmd_command_prompt_cdata *cdata = data;
  free(cdata->inputs);
  free(cdata->prompts);
  free(cdata->template);
  free(cdata);
}


/*** DEPENDENCIES:
struct cmd_command_prompt_cdata
{
  int flags;
  char *inputs;
  char *next_input;
  char *prompts;
  char *next_prompt;
  char *template;
  int idx;
}
----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_command_prompt_error(struct cmdq_item *item, void *data)
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


static int cmd_command_prompt_callback(struct client *c, void *data, const char *s, int done)
{
  struct cmd_command_prompt_cdata *cdata = data;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  char *new_template;
  unsigned int new_template_idx = 0;
  char *prompt;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *input = 0;
  unsigned int input_idx = 0;
  if (s == 0)
  {
    return 0;
  }
  if (done && (cdata->flags & 0x4))
  {
    return 0;
  }
  new_template_idx = cmd_template_replace(cdata->template, s, cdata->idx);
  if (done)
  {
    free(cdata->template);
    cdata->template = &new_template[new_template_idx];
  }
  if (done && ((ptr_idx = strsep(&cdata->next_prompt, ",")) != 0))
  {
    xasprintf(&prompt, "%s ", ptr);
    input_idx = strsep(&cdata->next_input, ",");
    status_prompt_update(c, prompt, input);
    free(prompt);
    cdata->idx += 1;
    return 1;
  }
  cmdlist_idx = cmd_string_parse(new_template, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_command_prompt_error", cmd_command_prompt_error, cause);
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
  if (!done)
  {
    free(new_template);
  }
  if (c->prompt_inputcb != cmd_command_prompt_callback)
  {
    return 1;
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
static enum cmd_retval cmd_command_prompt_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
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
void status_prompt_update(struct client *c, const char *msg, const char *input)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  tmp_idx = format_expand_time(ft, input, t);
  free(c->prompt_string);
  c->prompt_string = format_expand_time(ft, msg, t);
  free(c->prompt_buffer);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_hindex = 0;
  c->flags |= 0x10;
  free(tmp);
  format_free(ft);
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
struct cmd_command_prompt_cdata
{
  int flags;
  char *inputs;
  char *next_input;
  char *prompts;
  char *next_prompt;
  char *template;
  int idx;
}
----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_command_prompt_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  const char *inputs;
  unsigned int inputs_idx = 0;
  const char *prompts;
  unsigned int prompts_idx = 0;
  struct cmd_command_prompt_cdata *cdata;
  unsigned int cdata_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  char *prompt;
  unsigned int prompt_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *input = 0;
  unsigned int input_idx = 0;
  size_t n;
  if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  if (c->prompt_string != 0)
  {
    return CMD_RETURN_NORMAL;
  }
  cdata_idx = xcalloc(1, sizeof(*cdata_idx));
  cdata->inputs = 0;
  cdata->next_input = 0;
  cdata->prompts = 0;
  cdata->next_prompt = 0;
  cdata->template = 0;
  cdata->idx = 1;
  if (args->argc != 0)
  {
    cdata->template = xstrdup(args->argv[0]);
  }
  else
    cdata->template = xstrdup("%1");
  if ((prompts_idx = args_get(args, 'p')) != 0)
  {
    cdata->prompts = xstrdup(prompts);
  }
  else
    if (args->argc != 0)
  {
    n = strcspn(cdata->template, " ,");
    xasprintf(&cdata->prompts, "(%.*s) ", (int) n, cdata->template);
  }
  else
    cdata->prompts = xstrdup(":");
  cdata->next_prompt = cdata->prompts;
  ptr_idx = strsep(&cdata->next_prompt, ",");
  if ((&prompts[prompts_idx]) == 0)
  {
    prompt_idx = xstrdup(ptr);
  }
  else
    xasprintf(&(&prompt[prompt_idx]), "%s ", ptr);
  if ((inputs_idx = args_get(args, 'I')) != 0)
  {
    cdata->inputs = xstrdup(inputs);
    cdata->next_input = cdata->inputs;
    input_idx = strsep(&cdata->next_input, ",");
  }
  if (args_has(args, '1'))
  {
    cdata->flags |= 0x1;
  }
  else
    if (args_has(args, 'N'))
  {
    cdata->flags |= 0x2;
  }
  else
    if (args_has(args, 'i'))
  {
    cdata->flags |= 0x4;
  }
  status_prompt_set(c, prompt, input, cmd_command_prompt_callback, cmd_command_prompt_free, cdata, cdata->flags);
  free(prompt);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static int cmd_command_prompt_callback(struct client *c, void *data, const char *s, int done)
{
  struct cmd_command_prompt_cdata *cdata = data;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  char *new_template;
  unsigned int new_template_idx = 0;
  char *prompt;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *input = 0;
  unsigned int input_idx = 0;
  if (s == 0)
  {
    return 0;
  }
  if (done && (cdata->flags & 0x4))
  {
    return 0;
  }
  new_template_idx = cmd_template_replace(cdata->template, s, cdata->idx);
  if (done)
  {
    free(cdata->template);
    cdata->template = &new_template[new_template_idx];
  }
  if (done && ((ptr_idx = strsep(&cdata->next_prompt, ",")) != 0))
  {
    xasprintf(&prompt, "%s ", ptr);
    input_idx = strsep(&cdata->next_input, ",");
    status_prompt_update(c, prompt, input);
    free(prompt);
    cdata->idx += 1;
    return 1;
  }
  cmdlist_idx = cmd_string_parse(new_template, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      new_item_idx = cmdq_get_callback1("cmd_command_prompt_error", cmd_command_prompt_error, cause);
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
  if (!done)
  {
    free(new_template);
  }
  if (c->prompt_inputcb != cmd_command_prompt_callback)
  {
    return 1;
  }
  return 0;
}


----------------------------
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
void *xcalloc(size_t nmemb, size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((size == 0) || (nmemb == 0))
  {
    fatalx("xcalloc: zero size");
  }
  ptr_idx = calloc(nmemb, size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xcalloc: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return ptr;
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
struct cmd_command_prompt_cdata
{
  int flags;
  char *inputs;
  char *next_input;
  char *prompts;
  char *next_prompt;
  char *template;
  int idx;
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
static void cmd_command_prompt_free(void *data)
{
  struct cmd_command_prompt_cdata *cdata = data;
  free(cdata->inputs);
  free(cdata->prompts);
  free(cdata->template);
  free(cdata);
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


