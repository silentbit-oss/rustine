static void cmd_show_options_print(struct cmd *self, struct cmdq_item *item, struct options_entry *o, int idx)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *escaped;
  u_int size;
  u_int i;
  if (idx != (-1))
  {
    xasprintf(&(&tmp[tmp_idx]), "%s[%d]", options_name(o), idx);
    name_idx = &tmp[tmp_idx];
  }
  else
  {
    if (options_array_size(o, &size) != (-1))
    {
      for (i = 0; i < size; i += 1)
      {
        if (options_array_get(o, i) == 0)
        {
          continue;
        }
        cmd_show_options_print(self, item, o, i);
      }

      return;
    }
    tmp_idx = 0;
    name_idx = options_name(o);
  }
  value_idx = options_tostring(o, idx, 0);
  if (args_has(self->args, 'v'))
  {
    cmdq_print(item, "%s", value);
  }
  else
    if (options_isstring(o))
  {
    utf8_stravis(&escaped, value, ((0x01 | 0x08) | 0x10) | 0x200);
    cmdq_print(item, "%s \"%s\"", name, escaped);
    free(escaped);
  }
  else
    cmdq_print(item, "%s %s", name, value);
  free(tmp);
}


/*** DEPENDENCIES:
int utf8_stravis(char **dst, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  buf_idx = xreallocarray(0, 4, strlen(src) + 1);
  len = utf8_strvis(buf, src, strlen(src), flag);
  *dst = xrealloc(buf, len + 1);
  return len;
}


----------------------------
const char *options_array_get(struct options_entry *o, u_int idx)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return 0;
  }
  if (idx >= o->arraysize)
  {
    return 0;
  }
  return o->array[idx];
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
const char *options_tostring(struct options_entry *o, int idx, int numeric)
{
  static char s[1024];
  const char *tmp;
  unsigned int tmp_idx = 0;
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    if (idx == (-1))
    {
      return 0;
    }
    if ((((u_int) idx) >= o->arraysize) || (o->array[idx] == 0))
    {
      return "";
    }
    return o->array[idx];
  }
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE))
  {
    return style_tostring(&o->style);
  }
  if ((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE)))
  {
    helper_options_tostring_1(&tmp_idx, o, numeric, s, tmp);
  }
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    return o->string;
  }
  return 0;
}


----------------------------
int options_array_size(struct options_entry *o, u_int *size)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (size != 0)
  {
    *size = o->arraysize;
  }
  return 0;
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
const char *options_name(struct options_entry *o)
{
  return o->name;
}


----------------------------
None
----------------------------
int options_isstring(struct options_entry *o)
{
  if (o->tableentry == 0)
  {
    return 1;
  }
  return ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)) || ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY));
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


static enum cmd_retval cmd_show_options_all(struct cmd *self, struct cmdq_item *item, struct options *oo)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  u_int size;
  u_int idx;
  o_idx = options_first(oo);
  while ((&o[o_idx]) != 0)
  {
    oe_idx = options_table_entry(o);
    if (((&oe[oe_idx]) != 0) && (oe->style != 0))
    {
      o_idx = options_next(o_idx);
      continue;
    }
    if (options_array_size(o, &size) == (-1))
    {
      cmd_show_options_print(self, item, o, -1);
    }
    else
    {
      for (idx = 0; idx < size; idx += 1)
      {
        if (options_array_get(o, idx) == 0)
        {
          continue;
        }
        cmd_show_options_print(self, item, o, idx);
      }

    }
    o_idx = options_next(o_idx);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct options_entry *options_next(struct options_entry *o)
{
  return options_tree_RB_NEXT(o);
}


----------------------------
const char *options_array_get(struct options_entry *o, u_int idx)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return 0;
  }
  if (idx >= o->arraysize)
  {
    return 0;
  }
  return o->array[idx];
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
int options_array_size(struct options_entry *o, u_int *size)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (size != 0)
  {
    *size = o->arraysize;
  }
  return 0;
}


----------------------------
struct options_entry *options_first(struct options *oo)
{
  return options_tree_RB_MINMAX(&oo->tree, -1);
}


----------------------------
None
----------------------------
static void cmd_show_options_print(struct cmd *self, struct cmdq_item *item, struct options_entry *o, int idx)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *escaped;
  u_int size;
  u_int i;
  if (idx != (-1))
  {
    xasprintf(&(&tmp[tmp_idx]), "%s[%d]", options_name(o), idx);
    name_idx = &tmp[tmp_idx];
  }
  else
  {
    if (options_array_size(o, &size) != (-1))
    {
      for (i = 0; i < size; i += 1)
      {
        if (options_array_get(o, i) == 0)
        {
          continue;
        }
        cmd_show_options_print(self, item, o, i);
      }

      return;
    }
    tmp_idx = 0;
    name_idx = options_name(o);
  }
  value_idx = options_tostring(o, idx, 0);
  if (args_has(self->args, 'v'))
  {
    cmdq_print(item, "%s", value);
  }
  else
    if (options_isstring(o))
  {
    utf8_stravis(&escaped, value, ((0x01 | 0x08) | 0x10) | 0x200);
    cmdq_print(item, "%s \"%s\"", name, escaped);
    free(escaped);
  }
  else
    cmdq_print(item, "%s %s", name, value);
  free(tmp);
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_show_options_one(struct cmd *self, struct cmdq_item *item, struct options *oo)
{
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  struct options_entry *o;
  unsigned int o_idx = 0;
  int idx;
  int ambiguous;
  char *name;
  unsigned int name_idx = 0;
  name_idx = format_single(item, args->argv[0], c, s, wl, 0);
  o_idx = options_match_get(oo, name, &idx, 1, &ambiguous);
  if ((&o[o_idx]) == 0)
  {
    if (args_has(args, 'q'))
    {
      free(name);
      return CMD_RETURN_NORMAL;
    }
    if (ambiguous)
    {
      cmdq_error(item, "ambiguous option: %s", name);
      free(name);
      return CMD_RETURN_ERROR;
    }
    if ((name[name_idx] != '@') && (options_match_get(oo, name, &idx, 0, &ambiguous) != 0))
    {
      free(name);
      return CMD_RETURN_NORMAL;
    }
    cmdq_error(item, "unknown option: %s", name);
    free(name);
    return CMD_RETURN_ERROR;
  }
  cmd_show_options_print(self, item, o, idx);
  free(name);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
None
----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
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
struct options_entry *options_match_get(struct options *oo, const char *s, int *idx, int only, int *ambiguous)
{
  char *name;
  unsigned int name_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  name_idx = options_match(s, idx, ambiguous);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  *ambiguous = 0;
  if (only)
  {
    o_idx = options_get_only(oo, name);
  }
  else
    o_idx = options_get(oo, name);
  free(name);
  return o;
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
static void cmd_show_options_print(struct cmd *self, struct cmdq_item *item, struct options_entry *o, int idx)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *escaped;
  u_int size;
  u_int i;
  if (idx != (-1))
  {
    xasprintf(&(&tmp[tmp_idx]), "%s[%d]", options_name(o), idx);
    name_idx = &tmp[tmp_idx];
  }
  else
  {
    if (options_array_size(o, &size) != (-1))
    {
      for (i = 0; i < size; i += 1)
      {
        if (options_array_get(o, i) == 0)
        {
          continue;
        }
        cmd_show_options_print(self, item, o, i);
      }

      return;
    }
    tmp_idx = 0;
    name_idx = options_name(o);
  }
  value_idx = options_tostring(o, idx, 0);
  if (args_has(self->args, 'v'))
  {
    cmdq_print(item, "%s", value);
  }
  else
    if (options_isstring(o))
  {
    utf8_stravis(&escaped, value, ((0x01 | 0x08) | 0x10) | 0x200);
    cmdq_print(item, "%s \"%s\"", name, escaped);
    free(escaped);
  }
  else
    cmdq_print(item, "%s %s", name, value);
  free(tmp);
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


static enum cmd_retval cmd_show_options_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_find_state *fs = &item->target;
  struct options *oo;
  enum options_table_scope scope;
  char *cause;
  int window;
  window = self->entry == (&cmd_show_window_options_entry);
  scope = options_scope_from_flags(args, window, fs, &oo, &cause);
  if (scope == OPTIONS_TABLE_NONE)
  {
    cmdq_error(item, "%s", cause);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  if (args->argc == 0)
  {
    return cmd_show_options_all(self, item, oo);
  }
  else
    return cmd_show_options_one(self, item, oo);
}


/*** DEPENDENCIES:
None
----------------------------
static enum cmd_retval cmd_show_options_all(struct cmd *self, struct cmdq_item *item, struct options *oo)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  u_int size;
  u_int idx;
  o_idx = options_first(oo);
  while ((&o[o_idx]) != 0)
  {
    oe_idx = options_table_entry(o);
    if (((&oe[oe_idx]) != 0) && (oe->style != 0))
    {
      o_idx = options_next(o_idx);
      continue;
    }
    if (options_array_size(o, &size) == (-1))
    {
      cmd_show_options_print(self, item, o, -1);
    }
    else
    {
      for (idx = 0; idx < size; idx += 1)
      {
        if (options_array_get(o, idx) == 0)
        {
          continue;
        }
        cmd_show_options_print(self, item, o, idx);
      }

    }
    o_idx = options_next(o_idx);
  }

  return CMD_RETURN_NORMAL;
}


----------------------------
enum options_table_scope options_scope_from_flags(struct args *args, int window, struct cmd_find_state *fs, struct options **oo, char **cause)
{
  struct session *s = fs->s;
  struct winlink *wl = fs->wl;
  const char *target = args_get(args, 't');
  if (args_has(args, 's'))
  {
    *oo = global_options;
    return OPTIONS_TABLE_SERVER;
  }
  if (window || args_has(args, 'w'))
  {
    if (args_has(args, 'g'))
    {
      *oo = global_w_options;
      return OPTIONS_TABLE_WINDOW;
    }
    if (wl == 0)
    {
      if (target != 0)
      {
        xasprintf(cause, "no such window: %s", target);
      }
      else
        xasprintf(cause, "no current window");
      return OPTIONS_TABLE_NONE;
    }
    *oo = wl->window->options;
    return OPTIONS_TABLE_WINDOW;
  }
  else
  {
    if (args_has(args, 'g'))
    {
      *oo = global_s_options;
      return OPTIONS_TABLE_SESSION;
    }
    if (s == 0)
    {
      if (target != 0)
      {
        xasprintf(cause, "no such session: %s", target);
      }
      else
        xasprintf(cause, "no current session");
      return OPTIONS_TABLE_NONE;
    }
    *oo = s->options;
    return OPTIONS_TABLE_SESSION;
  }
}


----------------------------
static enum cmd_retval cmd_show_options_one(struct cmd *self, struct cmdq_item *item, struct options *oo)
{
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  struct options_entry *o;
  unsigned int o_idx = 0;
  int idx;
  int ambiguous;
  char *name;
  unsigned int name_idx = 0;
  name_idx = format_single(item, args->argv[0], c, s, wl, 0);
  o_idx = options_match_get(oo, name, &idx, 1, &ambiguous);
  if ((&o[o_idx]) == 0)
  {
    if (args_has(args, 'q'))
    {
      free(name);
      return CMD_RETURN_NORMAL;
    }
    if (ambiguous)
    {
      cmdq_error(item, "ambiguous option: %s", name);
      free(name);
      return CMD_RETURN_ERROR;
    }
    if ((name[name_idx] != '@') && (options_match_get(oo, name, &idx, 0, &ambiguous) != 0))
    {
      free(name);
      return CMD_RETURN_NORMAL;
    }
    cmdq_error(item, "unknown option: %s", name);
    free(name);
    return CMD_RETURN_ERROR;
  }
  cmd_show_options_print(self, item, o, idx);
  free(name);
  return CMD_RETURN_NORMAL;
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
enum options_table_scope
{
  OPTIONS_TABLE_NONE,
  OPTIONS_TABLE_SERVER,
  OPTIONS_TABLE_SESSION,
  OPTIONS_TABLE_WINDOW
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
extern const struct cmd_entry cmd_show_window_options_entry
----------------------------
None
----------------------------
None
----------------------------
***/


