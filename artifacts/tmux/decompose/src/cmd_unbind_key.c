static enum cmd_retval cmd_unbind_key_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  key_code key;
  const char *tablename;
  unsigned int tablename_idx = 0;
  if (!args_has(args, 'a'))
  {
    if (args->argc != 1)
    {
      cmdq_error(item, "missing key");
      return CMD_RETURN_ERROR;
    }
    key = key_string_lookup_string(args->argv[0]);
    if ((key == 0xffff00000000ULL) || (key == 0xfffe00000000ULL))
    {
      cmdq_error(item, "unknown key: %s", args->argv[0]);
      return CMD_RETURN_ERROR;
    }
  }
  else
  {
    if (args->argc != 0)
    {
      cmdq_error(item, "key given with -a");
      return CMD_RETURN_ERROR;
    }
    key = 0xfffe00000000ULL;
  }
  if (key == 0xfffe00000000ULL)
  {
    tablename_idx = args_get(args, 'T');
    if ((&tablename[tablename_idx]) == 0)
    {
      key_bindings_remove_table("root");
      key_bindings_remove_table("prefix");
      return CMD_RETURN_NORMAL;
    }
    if (key_bindings_get_table(tablename, 0) == 0)
    {
      cmdq_error(item, "table %s doesn't exist", tablename);
      return CMD_RETURN_ERROR;
    }
    key_bindings_remove_table(tablename);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'T'))
  {
    tablename_idx = args_get(args, 'T');
    if (key_bindings_get_table(tablename, 0) == 0)
    {
      cmdq_error(item, "table %s doesn't exist", tablename);
      return CMD_RETURN_ERROR;
    }
  }
  else
    if (args_has(args, 'n'))
  {
    tablename_idx = "root";
  }
  else
    tablename_idx = "prefix";
  key_bindings_remove(tablename, key);
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
struct key_table *key_bindings_get_table(const char *name, int create)
{
  struct key_table table_find;
  struct key_table *table;
  unsigned int table_idx = 0;
  table_find.name = name;
  table_idx = key_tables_RB_FIND(&key_tables, &table_find);
  if (((&table[table_idx]) != 0) || (!create))
  {
    return table;
  }
  table_idx = xmalloc(sizeof(*table_idx));
  table->name = xstrdup(name);
  do
  {
    (&table->key_bindings)->rbh_root = 0;
  }
  while (0);
  table->references = 1;
  key_tables_RB_INSERT(&key_tables, table);
  return table;
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
void key_bindings_remove_table(const char *name)
{
  struct key_table *table;
  unsigned int table_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  table_idx = key_bindings_get_table(name, 0);
  if ((&table[table_idx]) != 0)
  {
    key_tables_RB_REMOVE(&key_tables, table);
    key_bindings_unref_table(table);
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->keytable == (&table[table_idx]))
    {
      server_client_set_key_table(c, 0);
    }
  }

}


----------------------------
void key_bindings_remove(const char *name, key_code key)
{
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding bd_find;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  table_idx = key_bindings_get_table(name, 0);
  if ((&table[table_idx]) == 0)
  {
    return;
  }
  bd_find.key = key & (~0x1000000000000ULL);
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) == 0)
  {
    return;
  }
  key_bindings_RB_REMOVE(&table->key_bindings, bd);
  cmd_list_free(bd->cmdlist);
  free(bd);
  if ((&table->key_bindings)->rbh_root == 0)
  {
    key_tables_RB_REMOVE(&key_tables, table);
    key_bindings_unref_table(table);
  }
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


