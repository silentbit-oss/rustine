static enum cmd_retval cmd_bind_key_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  char *cause;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  key_code key;
  const char *tablename;
  unsigned int tablename_idx = 0;
  key = key_string_lookup_string(args->argv[0]);
  if ((key == 0xffff00000000ULL) || (key == 0xfffe00000000ULL))
  {
    cmdq_error(item, "unknown key: %s", args->argv[0]);
    return CMD_RETURN_ERROR;
  }
  if (args_has(args, 'T'))
  {
    tablename_idx = args_get(args, 'T');
  }
  else
    if (args_has(args, 'n'))
  {
    tablename_idx = "root";
  }
  else
    tablename_idx = "prefix";
  cmdlist_idx = cmd_list_parse(args->argc - 1, args->argv + 1, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    cmdq_error(item, "%s", cause);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  key_bindings_add(tablename, key, args_has(args, 'r'), cmdlist);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
key_code key_string_lookup_string(const char *string)
{
  unsigned int string_idx = 0;
  static const char *other = "!#()+,-.0123456789:;<=>?'\r\t";
  key_code key;
  u_int u;
  key_code modifiers;
  struct utf8_data ud;
  u_int i;
  enum utf8_state more;
  wchar_t wc;
  if (strcasecmp(string, "None") == 0)
  {
    return 0xffff00000000ULL;
  }
  if ((string[0 + string_idx] == '0') && (string[1 + string_idx] == 'x'))
  {
    if (sscanf((&string[string_idx]) + 2, "%x", &u) != 1)
    {
      return 0xfffe00000000ULL;
    }
    if (u > 0x1fffff)
    {
      return 0xfffe00000000ULL;
    }
    return u;
  }
  modifiers = 0;
  if ((string[0 + string_idx] == '^') && (string[1 + string_idx] != '\0'))
  {
    modifiers |= 0x400000000000ULL;
    string_idx += 1;
  }
  modifiers |= key_string_get_modifiers(&(&string[string_idx]));
  if (((&string[string_idx]) == 0) || (string[0 + string_idx] == '\0'))
  {
    return 0xfffe00000000ULL;
  }
  if ((string[1 + string_idx] == '\0') && (((u_char) string[0 + string_idx]) <= 127))
  {
    key = (u_char) string[0 + string_idx];
    if ((key < 32) || (key == 127))
    {
      return 0xfffe00000000ULL;
    }
  }
  else
  {
    helper_key_string_lookup_string_1(&key, &i, &more, string, string_idx, modifiers, ud, wc);
  }
  if (((key < 0x000010000000ULL) && (modifiers & 0x400000000000ULL)) && (!strchr(other, key)))
  {
    if ((key >= 97) && (key <= 122))
    {
      key -= 96;
    }
    else
      if ((key >= 64) && (key <= 95))
    {
      key -= 64;
    }
    else
      if (key == 32)
    {
      key = 0;
    }
    else
      if (key == 63)
    {
      key = KEYC_BSPACE;
    }
    else
      return 0xfffe00000000ULL;
    modifiers &= ~0x400000000000ULL;
  }
  return key | modifiers;
}


----------------------------
typedef unsigned long long key_code
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
struct cmd_list *cmd_list_parse(int argc, char **argv, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  int i;
  int lastsplit;
  size_t arglen;
  size_t new_argc;
  char **copy_argv;
  unsigned int copy_argv_idx = 0;
  char **new_argv;
  unsigned int new_argv_idx = 0;
  copy_argv_idx = cmd_copy_argv(argc, argv);
  cmdlist_idx = xcalloc(1, sizeof(*cmdlist_idx));
  cmdlist->references = 1;
  do
  {
    (&cmdlist->list)->tqh_first = 0;
    (&cmdlist->list)->tqh_last = &(&cmdlist->list)->tqh_first;
  }
  while (0);
  lastsplit = 0;
  for (i = 0; i < argc; i += 1)
  {
    helper_cmd_list_parse_1(&cmd_idx, &i, &lastsplit, &arglen, &new_argc, &copy_argv_idx, &new_argv_idx, file, line, cause, cmdlist, cmd, copy_argv, new_argv);
  }

  if (lastsplit != argc)
  {
    cmd_idx = cmd_parse(argc - lastsplit, (&copy_argv[copy_argv_idx]) + lastsplit, file, line, cause);
    if ((&cmd[cmd_idx]) == 0)
    {
      goto bad;
    }
    do
    {
      cmd->qentry.tqe_next = 0;
      cmd->qentry.tqe_prev = (&cmdlist->list)->tqh_last;
      *(&cmdlist->list)->tqh_last = &cmd[cmd_idx];
      (&cmdlist->list)->tqh_last = &cmd->qentry.tqe_next;
    }
    while (0);
  }
  cmd_free_argv(argc, copy_argv);
  return cmdlist;
  bad:
  cmd_list_free(cmdlist);

  cmd_free_argv(argc, copy_argv);
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
void key_bindings_add(const char *name, key_code key, int repeat, struct cmd_list *cmdlist)
{
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding bd_find;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  table_idx = key_bindings_get_table(name, 1);
  bd_find.key = key & (~0x1000000000000ULL);
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) != 0)
  {
    key_bindings_RB_REMOVE(&table->key_bindings, bd);
    cmd_list_free(bd->cmdlist);
    free(bd);
  }
  bd_idx = xcalloc(1, sizeof(*bd_idx));
  bd->key = key;
  key_bindings_RB_INSERT(&table->key_bindings, bd);
  if (repeat)
  {
    bd->flags |= 0x1;
  }
  bd->cmdlist = cmdlist;
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


