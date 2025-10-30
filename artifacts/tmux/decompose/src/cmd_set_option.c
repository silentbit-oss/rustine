static int cmd_set_option_flag(struct cmdq_item *item, const struct options_table_entry *oe, struct options *oo, const char *value)
{
  int flag;
  if ((value == 0) || ((*value) == '\0'))
  {
    flag = !options_get_number(oo, oe->name);
  }
  else
    if (((strcmp(value, "1") == 0) || (strcasecmp(value, "on") == 0)) || (strcasecmp(value, "yes") == 0))
  {
    flag = 1;
  }
  else
    if (((strcmp(value, "0") == 0) || (strcasecmp(value, "off") == 0)) || (strcasecmp(value, "no") == 0))
  {
    flag = 0;
  }
  else
  {
    cmdq_error(item, "bad value: %s", value);
    return -1;
  }
  options_set_number(oo, oe->name, flag);
  return 0;
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
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
}


----------------------------
None
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
None
----------------------------
***/


static int cmd_set_option_choice(struct cmdq_item *item, const struct options_table_entry *oe, struct options *oo, const char *value)
{
  const char **cp;
  unsigned int cp_idx = 0;
  int n;
  int choice = -1;
  if (value == 0)
  {
    choice = options_get_number(oo, oe->name);
    if (choice < 2)
    {
      choice = !choice;
    }
  }
  else
  {
    n = 0;
    for (cp_idx = oe->choices; cp[cp_idx] != 0; cp_idx += 1)
    {
      if (strcmp(*(&cp[cp_idx]), value) == 0)
      {
        choice = n;
      }
      n += 1;
    }

    if (choice == (-1))
    {
      cmdq_error(item, "unknown value: %s", value);
      return -1;
    }
  }
  options_set_number(oo, oe->name, choice);
  return 0;
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
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
}


----------------------------
None
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
None
----------------------------
***/


// hint:  ['o_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_set_option_exec_1(unsigned int * const o_idx_ref, struct cmdq_item * const item, int append, struct options * const oo, struct options_entry * const parent, struct options_entry * const o, char * const argument, char * const value, unsigned int value_idx, int idx)
{
  unsigned int o_idx = *o_idx_ref;
  if ((&value[value_idx]) == 0)
  {
    cmdq_error(item, "empty value");
    goto fail;
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_empty(oo, options_table_entry(parent));
  }
  if (idx == (-1))
  {
    if (!append)
    {
      options_array_clear(o);
    }
    options_array_assign(o, value);
  }
  else
    if (options_array_set(o, idx, value, append) != 0)
  {
    cmdq_error(item, "invalid index: %s", argument);
    goto fail;
  }
  *o_idx_ref = o_idx;
}


/*** DEPENDENCIES:
void options_array_clear(struct options_entry *o)
{
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    o->arraysize = 0;
  }
}


----------------------------
int options_array_set(struct options_entry *o, u_int idx, const char *value, int append)
{
  char *new;
  unsigned int new_idx = 0;
  u_int i;
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (idx >= 1000)
  {
    return -1;
  }
  if (idx >= o->arraysize)
  {
    o->array = xreallocarray(o->array, idx + 1, sizeof(*o->array));
    for (i = o->arraysize; i < (idx + 1); i += 1)
    {
      o->array[i] = 0;
    }

    o->arraysize = idx + 1;
  }
  new_idx = 0;
  if (value != 0)
  {
    if ((o->array[idx] != 0) && append)
    {
      xasprintf(&(&new[new_idx]), "%s%s", o->array[idx], value);
    }
    else
      new_idx = xstrdup(value);
  }
  free((void *) o->array[idx]);
  o->array[idx] = &new[new_idx];
  return 0;
}


----------------------------
struct options_entry *options_empty(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_add(oo, oe->name);
  o->tableentry = oe;
  return o;
}


----------------------------
void options_array_assign(struct options_entry *o, const char *s)
{
  const char *separator;
  unsigned int separator_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  char *string;
  u_int i;
  separator_idx = o->tableentry->separator_idx;
  if ((&separator[separator_idx]) == 0)
  {
    separator_idx = " ,";
  }
  copy_idx = (string = xstrdup(s));
  while ((next_idx = strsep(&string, separator)) != 0)
  {
    if (next[next_idx] == '\0')
    {
      continue;
    }
    for (i = 0; i < 1000; i += 1)
    {
      if ((i >= o->arraysize) || (o->array[i] == 0))
      {
        break;
      }
    }

    if (i == 1000)
    {
      break;
    }
    options_array_set(o, i, next, 0);
  }

  free(copy);
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
None
----------------------------
***/


static int cmd_set_option_set(struct cmd *self, struct cmdq_item *item, struct options *oo, struct options_entry *parent, const char *value)
{
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  struct args *args = self->args;
  int append = args_has(args, 'a');
  struct options_entry *o;
  unsigned int o_idx = 0;
  long long number;
  const char *errstr;
  key_code key;
  oe_idx = options_table_entry(parent);
  if (((value == 0) && (oe->type != OPTIONS_TABLE_FLAG)) && (oe->type != OPTIONS_TABLE_CHOICE))
  {
    cmdq_error(item, "empty value");
    return -1;
  }
  switch (oe->type)
  {
    case OPTIONS_TABLE_STRING:
    {
      options_set_string(oo, oe->name, append, "%s", value);
      return 0;
    }

    case OPTIONS_TABLE_NUMBER:
    {
      number = strtonum(value, oe->minimum, oe->maximum, &errstr);
      if (errstr != 0)
      {
        cmdq_error(item, "value is %s: %s", errstr, value);
        return -1;
      }
      options_set_number(oo, oe->name, number);
      return 0;
    }

    case OPTIONS_TABLE_KEY:
    {
      key = key_string_lookup_string(value);
      if (key == 0xfffe00000000ULL)
      {
        cmdq_error(item, "bad key: %s", value);
        return -1;
      }
      options_set_number(oo, oe->name, key);
      return 0;
    }

    case OPTIONS_TABLE_COLOUR:
    {
      if ((number = colour_fromstring(value)) == (-1))
      {
        cmdq_error(item, "bad colour: %s", value);
        return -1;
      }
      o_idx = options_set_number(oo, oe->name, number);
      options_style_update_new(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_ATTRIBUTES:
    {
      if ((number = attributes_fromstring(value)) == (-1))
      {
        cmdq_error(item, "bad attributes: %s", value);
        return -1;
      }
      o_idx = options_set_number(oo, oe->name, number);
      options_style_update_new(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_FLAG:
    {
      return cmd_set_option_flag(item, oe, oo, value);
    }

    case OPTIONS_TABLE_CHOICE:
    {
      return cmd_set_option_choice(item, oe, oo, value);
    }

    case OPTIONS_TABLE_STYLE:
    {
      o_idx = options_set_style(oo, oe->name, append, value);
      if ((&o[o_idx]) == 0)
      {
        cmdq_error(item, "bad style: %s", value);
        return -1;
      }
      options_style_update_old(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_ARRAY:
    {
      break;
    }

  }

  return -1;
}


/*** DEPENDENCIES:
struct options_entry *options_set_string(struct options *oo, const char *name, int append, const char *fmt, ...)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  va_list ap;
  char *s;
  char *value;
  unsigned int value_idx = 0;
  __builtin_va_start(ap);
  xvasprintf(&s, fmt, ap);
  ;
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    xasprintf(&(&value[value_idx]), "%s%s", o->string, s);
    free(s);
  }
  else
    value_idx = s;
  if (((&o[o_idx]) == 0) && ((*name) == '@'))
  {
    o_idx = options_add(oo, name);
  }
  else
    if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  free(o->string);
  o->string = &value[value_idx];
  return o;
}


----------------------------
void options_style_update_old(struct options *oo, struct options_entry *o)
{
  char newname[128];
  int size;
  size = strrchr(o->name, '-') - o->name;
  xsnprintf(newname, sizeof(newname), "%.*s-bg", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.bg);
  }
  xsnprintf(newname, sizeof(newname), "%.*s-fg", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.fg);
  }
  xsnprintf(newname, sizeof(newname), "%.*s-attr", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.attr);
  }
}


----------------------------
typedef unsigned long long key_code
----------------------------
int colour_fromstring(const char *s)
{
  const char *errstr;
  const char *cp;
  unsigned int cp_idx = 0;
  int n;
  u_char r;
  u_char g;
  u_char b;
  if (((*s) == '#') && (strlen(s) == 7))
  {
    for (cp_idx = s + 1; isxdigit((u_char) cp[cp_idx]); cp_idx += 1)
    {
      ;
    }

    if (cp[cp_idx] != '\0')
    {
      return -1;
    }
    n = sscanf(s + 1, "%2hhx%2hhx%2hhx", &r, &g, &b);
    if (n != 3)
    {
      return -1;
    }
    return colour_join_rgb(r, g, b);
  }
  if (strncasecmp(s, "colour", (sizeof("colour")) - 1) == 0)
  {
    n = strtonum((s + (sizeof("colour"))) - 1, 0, 255, &errstr);
    if (errstr != 0)
    {
      return -1;
    }
    return n | 0x01000000;
  }
  if ((strcasecmp(s, "black") == 0) || (strcmp(s, "0") == 0))
  {
    return 0;
  }
  if ((strcasecmp(s, "red") == 0) || (strcmp(s, "1") == 0))
  {
    return 1;
  }
  if ((strcasecmp(s, "green") == 0) || (strcmp(s, "2") == 0))
  {
    return 2;
  }
  if ((strcasecmp(s, "yellow") == 0) || (strcmp(s, "3") == 0))
  {
    return 3;
  }
  if ((strcasecmp(s, "blue") == 0) || (strcmp(s, "4") == 0))
  {
    return 4;
  }
  if ((strcasecmp(s, "magenta") == 0) || (strcmp(s, "5") == 0))
  {
    return 5;
  }
  if ((strcasecmp(s, "cyan") == 0) || (strcmp(s, "6") == 0))
  {
    return 6;
  }
  if ((strcasecmp(s, "white") == 0) || (strcmp(s, "7") == 0))
  {
    return 7;
  }
  if ((strcasecmp(s, "default") == 0) || (strcmp(s, "8") == 0))
  {
    return 8;
  }
  if ((strcasecmp(s, "brightblack") == 0) || (strcmp(s, "90") == 0))
  {
    return 90;
  }
  if ((strcasecmp(s, "brightred") == 0) || (strcmp(s, "91") == 0))
  {
    return 91;
  }
  if ((strcasecmp(s, "brightgreen") == 0) || (strcmp(s, "92") == 0))
  {
    return 92;
  }
  if ((strcasecmp(s, "brightyellow") == 0) || (strcmp(s, "93") == 0))
  {
    return 93;
  }
  if ((strcasecmp(s, "brightblue") == 0) || (strcmp(s, "94") == 0))
  {
    return 94;
  }
  if ((strcasecmp(s, "brightmagenta") == 0) || (strcmp(s, "95") == 0))
  {
    return 95;
  }
  if ((strcasecmp(s, "brightcyan") == 0) || (strcmp(s, "96") == 0))
  {
    return 96;
  }
  if ((strcasecmp(s, "brightwhite") == 0) || (strcmp(s, "97") == 0))
  {
    return 97;
  }
  return -1;
}


----------------------------
None
----------------------------
long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp)
{
  long long ll = 0;
  char *ep;
  int error = 0;
  struct errval
  {
    const char *errstr;
    int err;
  } ev[4] = {{0, 0}, {"invalid", EINVAL}, {"too small", ERANGE}, {"too large", ERANGE}};
  ev[0].err = errno;
  errno = 0;
  if (minval > maxval)
  {
    error = 1;
  }
  else
  {
    ll = strtoll(numstr, &ep, 10);
    if ((numstr == ep) || ((*ep) != '\0'))
    {
      error = 1;
    }
    else
      if (((ll == LLONG_MIN) && (errno == ERANGE)) || (ll < minval))
    {
      error = 2;
    }
    else
      if (((ll == LLONG_MAX) && (errno == ERANGE)) || (ll > maxval))
    {
      error = 3;
    }
  }
  if (errstrp != 0)
  {
    *errstrp = ev[error].errstr;
  }
  errno = ev[error].err;
  if (error)
  {
    ll = 0;
  }
  return ll;
}


----------------------------
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
None
----------------------------
static int cmd_set_option_choice(struct cmdq_item *item, const struct options_table_entry *oe, struct options *oo, const char *value)
{
  const char **cp;
  unsigned int cp_idx = 0;
  int n;
  int choice = -1;
  if (value == 0)
  {
    choice = options_get_number(oo, oe->name);
    if (choice < 2)
    {
      choice = !choice;
    }
  }
  else
  {
    n = 0;
    for (cp_idx = oe->choices; cp[cp_idx] != 0; cp_idx += 1)
    {
      if (strcmp(*(&cp[cp_idx]), value) == 0)
      {
        choice = n;
      }
      n += 1;
    }

    if (choice == (-1))
    {
      cmdq_error(item, "unknown value: %s", value);
      return -1;
    }
  }
  options_set_number(oo, oe->name, choice);
  return 0;
}


----------------------------
void options_style_update_new(struct options *oo, struct options_entry *o)
{
  const char *newname = o->tableentry->style;
  struct options_entry *new;
  unsigned int new_idx = 0;
  if (newname == 0)
  {
    return;
  }
  new_idx = options_get_only(oo, newname);
  if ((&new[new_idx]) == 0)
  {
    new_idx = options_set_style(oo, newname, 0, "default");
  }
  if (strstr(o->name, "-bg") != 0)
  {
    new->style.bg = o->number;
  }
  else
    if (strstr(o->name, "-fg") != 0)
  {
    new->style.fg = o->number;
  }
  else
    if (strstr(o->name, "-attr") != 0)
  {
    new->style.attr = o->number;
  }
}


----------------------------
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
}


----------------------------
static int cmd_set_option_flag(struct cmdq_item *item, const struct options_table_entry *oe, struct options *oo, const char *value)
{
  int flag;
  if ((value == 0) || ((*value) == '\0'))
  {
    flag = !options_get_number(oo, oe->name);
  }
  else
    if (((strcmp(value, "1") == 0) || (strcasecmp(value, "on") == 0)) || (strcasecmp(value, "yes") == 0))
  {
    flag = 1;
  }
  else
    if (((strcmp(value, "0") == 0) || (strcasecmp(value, "off") == 0)) || (strcasecmp(value, "no") == 0))
  {
    flag = 0;
  }
  else
  {
    cmdq_error(item, "bad value: %s", value);
    return -1;
  }
  options_set_number(oo, oe->name, flag);
  return 0;
}


----------------------------
struct options_entry *options_set_style(struct options *oo, const char *name, int append, const char *value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct grid_cell gc;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    memcpy(&gc, &o->style, sizeof(gc));
  }
  else
    memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (style_parse(&grid_default_cell, &gc, value) == (-1))
  {
    return 0;
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  memcpy(&o->style, &gc, sizeof(o->style));
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
int attributes_fromstring(const char *str)
{
  unsigned int str_idx = 0;
  const char delimiters[] = " ,|";
  int attr;
  size_t end;
  if ((str[str_idx] == '\0') || (strcspn(str, delimiters) == 0))
  {
    return -1;
  }
  if (strchr(delimiters, str[(strlen(str) - 1) + str_idx]) != 0)
  {
    return -1;
  }
  if ((strcasecmp(str, "default") == 0) || (strcasecmp(str, "none") == 0))
  {
    return 0;
  }
  attr = 0;
  do
  {
    end = strcspn(str, delimiters);
    if (((end == 6) && (strncasecmp(str, "bright", end) == 0)) || ((end == 4) && (strncasecmp(str, "bold", end) == 0)))
    {
      attr |= 0x1;
    }
    else
      if ((end == 3) && (strncasecmp(str, "dim", end) == 0))
    {
      attr |= 0x2;
    }
    else
      if ((end == 10) && (strncasecmp(str, "underscore", end) == 0))
    {
      attr |= 0x4;
    }
    else
      if ((end == 5) && (strncasecmp(str, "blink", end) == 0))
    {
      attr |= 0x8;
    }
    else
      if ((end == 7) && (strncasecmp(str, "reverse", end) == 0))
    {
      attr |= 0x10;
    }
    else
      if ((end == 6) && (strncasecmp(str, "hidden", end) == 0))
    {
      attr |= 0x20;
    }
    else
      if ((end == 7) && (strncasecmp(str, "italics", end) == 0))
    {
      attr |= 0x40;
    }
    else
      if ((end == 13) && (strncasecmp(str, "strikethrough", end) == 0))
    {
      attr |= 0x100;
    }
    else
      return -1;
    str_idx += end + strspn(str_idx + end, delimiters);
  }
  while (str[str_idx] != '\0');
  return attr;
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


static enum cmd_retval cmd_set_option_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  int append = args_has(args, 'a');
  struct cmd_find_state *fs = &item->target;
  struct client *c;
  unsigned int c_idx = 0;
  struct client *loop;
  unsigned int loop_idx = 0;
  struct session *s = fs->s;
  unsigned int s_idx = 0;
  struct winlink *wl = fs->wl;
  struct window *w;
  unsigned int w_idx = 0;
  enum options_table_scope scope;
  struct options *oo;
  unsigned int oo_idx = 0;
  struct options_entry *parent;
  unsigned int parent_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  char *argument;
  unsigned int argument_idx = 0;
  char *value = 0;
  unsigned int value_idx = 0;
  char *cause;
  const char *target;
  unsigned int target_idx = 0;
  int window;
  int idx;
  int already;
  int error;
  int ambiguous;
  c_idx = cmd_find_client(item, 0, 1);
  argument_idx = format_single(item, args->argv[0], c, s, wl, 0);
  name_idx = options_match(argument, &idx, &ambiguous);
  if ((&name[name_idx]) == 0)
  {
    if (args_has(args, 'q'))
    {
      goto out;
    }
    if (ambiguous)
    {
      cmdq_error(item, "ambiguous option: %s", argument);
    }
    else
      cmdq_error(item, "invalid option: %s", argument);
    goto fail;
  }
  if (args->argc < 2)
  {
    value_idx = 0;
  }
  else
    if (args_has(args, 'F'))
  {
    value_idx = format_single(item, args->argv[1], c, s, wl, 0);
  }
  else
    value_idx = xstrdup(args->argv[1]);
  if (name[name_idx] == '@')
  {
    window = self->entry == (&cmd_set_window_option_entry);
    scope = options_scope_from_flags(args, window, fs, &(&oo[oo_idx]), &cause);
  }
  else
  {
    if (options_get_only(global_options, name) != 0)
    {
      scope = OPTIONS_TABLE_SERVER;
    }
    else
      if (options_get_only(global_s_options, name) != 0)
    {
      scope = OPTIONS_TABLE_SESSION;
    }
    else
      if (options_get_only(global_w_options, name) != 0)
    {
      scope = OPTIONS_TABLE_WINDOW;
    }
    else
    {
      scope = OPTIONS_TABLE_NONE;
      xasprintf(&cause, "unknown option: %s", argument);
    }
  }
  if (scope == OPTIONS_TABLE_NONE)
  {
    if (args_has(args, 'q'))
    {
      goto out;
    }
    cmdq_error(item, "%s", cause);
    free(cause);
    goto fail;
  }
  if (scope == OPTIONS_TABLE_SERVER)
  {
    oo_idx = global_options;
  }
  else
    if (scope == OPTIONS_TABLE_SESSION)
  {
    if (args_has(self->args, 'g'))
    {
      oo_idx = global_s_options;
    }
    else
      if ((&s[s_idx]) == 0)
    {
      target_idx = args_get(args, 't');
      if ((&target[target_idx]) != 0)
      {
        cmdq_error(item, "no such session: %s", target);
      }
      else
        cmdq_error(item, "no current session");
      goto fail;
    }
    else
      oo_idx = s->options;
  }
  else
    if (scope == OPTIONS_TABLE_WINDOW)
  {
    if (args_has(self->args, 'g'))
    {
      oo_idx = global_w_options;
    }
    else
      if (wl == 0)
    {
      target_idx = args_get(args, 't');
      if ((&target[target_idx]) != 0)
      {
        cmdq_error(item, "no such window: %s", target);
      }
      else
        cmdq_error(item, "no current window");
      goto fail;
    }
    else
      oo_idx = wl->window->options;
  }
  o_idx = options_get_only(oo, name);
  parent_idx = options_get(oo, name);
  if (idx != (-1))
  {
    if ((name[name_idx] == '@') || (options_array_size(parent, 0) == (-1)))
    {
      cmdq_error(item, "not an array: %s", argument);
      goto fail;
    }
  }
  if ((!args_has(args, 'u')) && args_has(args, 'o'))
  {
    if (idx == (-1))
    {
      already = (&o[o_idx]) != 0;
    }
    else
    {
      if ((&o[o_idx]) == 0)
      {
        already = 0;
      }
      else
        already = options_array_get(o, idx) != 0;
    }
    if (already)
    {
      if (args_has(args, 'q'))
      {
        goto out;
      }
      cmdq_error(item, "already set: %s", argument);
      goto fail;
    }
  }
  if (args_has(args, 'u'))
  {
    if ((&o[o_idx]) == 0)
    {
      goto out;
    }
    if (idx == (-1))
    {
      if (name[name_idx] == '@')
      {
        options_remove(o);
      }
      else
        if ((((&oo[oo_idx]) == global_options) || ((&oo[oo_idx]) == global_s_options)) || ((&oo[oo_idx]) == global_w_options))
      {
        options_default(oo, options_table_entry(o));
      }
      else
        options_remove(o);
    }
    else
      options_array_set(o, idx, 0, 0);
  }
  else
    if (name[name_idx] == '@')
  {
    if ((&value[value_idx]) == 0)
    {
      cmdq_error(item, "empty value");
      goto fail;
    }
    options_set_string(oo, name, append, "%s", value);
  }
  else
    if ((idx == (-1)) && (options_array_size(parent, 0) == (-1)))
  {
    error = cmd_set_option_set(self, item, oo, parent, value);
    if (error != 0)
    {
      goto fail;
    }
  }
  else
  {
    helper_cmd_set_option_exec_1(&o_idx, item, append, oo, parent, o, argument, value, value_idx, idx);
  }
  if (strcmp(name, "automatic-rename") == 0)
  {
    for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
    {
      if (w->active == 0)
      {
        continue;
      }
      if (options_get_number(w->options, "automatic-rename"))
      {
        w->active->flags |= 0x80;
      }
    }

  }
  if (strcmp(name, "key-table") == 0)
  {
    for (loop_idx = (&clients)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
    {
      server_client_set_key_table(loop, 0);
    }

  }
  if (strcmp(name, "user-keys") == 0)
  {
    for (loop_idx = (&clients)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
    {
      if (loop->tty.flags & 0x20)
      {
        tty_keys_build(&loop->tty);
      }
    }

  }
  if ((strcmp(name, "status") == 0) || (strcmp(name, "status-interval") == 0))
  {
    status_timer_start_all();
  }
  if (strcmp(name, "monitor-silence") == 0)
  {
    alerts_reset_all();
  }
  if ((strcmp(name, "window-style") == 0) || (strcmp(name, "window-active-style") == 0))
  {
    for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
    {
      w->flags |= 0x8000;
    }

  }
  if (strcmp(name, "pane-border-status") == 0)
  {
    for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
    {
      layout_fix_panes(w, w->sx, w->sy);
    }

  }
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    status_update_saved(s);
  }

  recalculate_sizes();
  for (loop_idx = (&clients)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->entry.tqe_next)
  {
    if (loop->session != 0)
    {
      server_redraw_client(loop);
    }
  }

  out:
  free(argument);

  free(value);
  free(name);
  return CMD_RETURN_NORMAL;
  fail:
  free(argument);

  free(value);
  free(name);
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
struct options_entry *options_set_string(struct options *oo, const char *name, int append, const char *fmt, ...)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  va_list ap;
  char *s;
  char *value;
  unsigned int value_idx = 0;
  __builtin_va_start(ap);
  xvasprintf(&s, fmt, ap);
  ;
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    xasprintf(&(&value[value_idx]), "%s%s", o->string, s);
    free(s);
  }
  else
    value_idx = s;
  if (((&o[o_idx]) == 0) && ((*name) == '@'))
  {
    o_idx = options_add(oo, name);
  }
  else
    if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  free(o->string);
  o->string = &value[value_idx];
  return o;
}


----------------------------
static int cmd_set_option_set(struct cmd *self, struct cmdq_item *item, struct options *oo, struct options_entry *parent, const char *value)
{
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  struct args *args = self->args;
  int append = args_has(args, 'a');
  struct options_entry *o;
  unsigned int o_idx = 0;
  long long number;
  const char *errstr;
  key_code key;
  oe_idx = options_table_entry(parent);
  if (((value == 0) && (oe->type != OPTIONS_TABLE_FLAG)) && (oe->type != OPTIONS_TABLE_CHOICE))
  {
    cmdq_error(item, "empty value");
    return -1;
  }
  switch (oe->type)
  {
    case OPTIONS_TABLE_STRING:
    {
      options_set_string(oo, oe->name, append, "%s", value);
      return 0;
    }

    case OPTIONS_TABLE_NUMBER:
    {
      number = strtonum(value, oe->minimum, oe->maximum, &errstr);
      if (errstr != 0)
      {
        cmdq_error(item, "value is %s: %s", errstr, value);
        return -1;
      }
      options_set_number(oo, oe->name, number);
      return 0;
    }

    case OPTIONS_TABLE_KEY:
    {
      key = key_string_lookup_string(value);
      if (key == 0xfffe00000000ULL)
      {
        cmdq_error(item, "bad key: %s", value);
        return -1;
      }
      options_set_number(oo, oe->name, key);
      return 0;
    }

    case OPTIONS_TABLE_COLOUR:
    {
      if ((number = colour_fromstring(value)) == (-1))
      {
        cmdq_error(item, "bad colour: %s", value);
        return -1;
      }
      o_idx = options_set_number(oo, oe->name, number);
      options_style_update_new(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_ATTRIBUTES:
    {
      if ((number = attributes_fromstring(value)) == (-1))
      {
        cmdq_error(item, "bad attributes: %s", value);
        return -1;
      }
      o_idx = options_set_number(oo, oe->name, number);
      options_style_update_new(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_FLAG:
    {
      return cmd_set_option_flag(item, oe, oo, value);
    }

    case OPTIONS_TABLE_CHOICE:
    {
      return cmd_set_option_choice(item, oe, oo, value);
    }

    case OPTIONS_TABLE_STYLE:
    {
      o_idx = options_set_style(oo, oe->name, append, value);
      if ((&o[o_idx]) == 0)
      {
        cmdq_error(item, "bad style: %s", value);
        return -1;
      }
      options_style_update_old(oo, o);
      return 0;
    }

    case OPTIONS_TABLE_ARRAY:
    {
      break;
    }

  }

  return -1;
}


----------------------------
char *options_match(const char *s, int *idx, int *ambiguous)
{
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  const struct options_table_entry *found;
  unsigned int found_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  size_t namelen;
  name_idx = options_parse(s, idx);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  namelen = strlen(name);
  if (name[name_idx] == '@')
  {
    *ambiguous = 0;
    return name;
  }
  found_idx = 0;
  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (strcmp(oe->name, name) == 0)
    {
      found_idx = &oe[oe_idx];
      break;
    }
    if (strncmp(oe->name, name, namelen) == 0)
    {
      if ((&found[found_idx]) != 0)
      {
        *ambiguous = 1;
        free(name);
        return 0;
      }
      found_idx = &oe[oe_idx];
    }
  }

  free(name);
  if ((&found[found_idx]) == 0)
  {
    *ambiguous = 0;
    return 0;
  }
  return xstrdup(found->name);
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void recalculate_sizes(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int ssx;
  u_int ssy;
  u_int has;
  u_int limit;
  u_int lines;
  int flag;
  int is_zoomed;
  int forced;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    helper_recalculate_sizes_1(&c_idx, &ssx, &ssy, &lines, s, s_idx, c);
  }

  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    helper_recalculate_sizes_2(&s_idx, &wp_idx, &ssx, &ssy, &has, &limit, &flag, &is_zoomed, &forced, s, w, w_idx, wp);
  }

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
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
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
struct options_entry *options_default(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_empty(oo, oe);
  if (oe->type == OPTIONS_TABLE_ARRAY)
  {
    options_array_assign(o, oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STRING)
  {
    o->string = xstrdup(oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STYLE)
  {
    memcpy(&o->style, &grid_default_cell, sizeof(o->style));
    style_parse(&grid_default_cell, &o->style, oe->default_str);
  }
  else
    o->number = oe->default_num;
  return o;
}


----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
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
struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}


----------------------------
void options_remove(struct options_entry *o)
{
  struct options *oo = o->owner;
  u_int i;
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    free((void *) o->string);
  }
  else
    if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    for (i = 0; i < o->arraysize; i += 1)
    {
      free((void *) o->array[i]);
    }

    free(o->array);
  }
  options_tree_RB_REMOVE(&oo->tree, o);
  free(o);
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
void tty_keys_build(struct tty *tty)
{
  const struct tty_default_key_raw *tdkr;
  unsigned int tdkr_idx = 0;
  const struct tty_default_key_code *tdkc;
  unsigned int tdkc_idx = 0;
  u_int i;
  u_int size;
  const char *s;
  unsigned int s_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (tty->key_tree != 0)
  {
    tty_keys_free(tty);
  }
  tty->key_tree = 0;
  for (i = 0; i < ((sizeof(tty_default_raw_keys)) / (sizeof(tty_default_raw_keys[0]))); i += 1)
  {
    tdkr_idx = &tty_default_raw_keys[i];
    s_idx = tdkr->string;
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkr->key);
    }
  }

  for (i = 0; i < ((sizeof(tty_default_code_keys)) / (sizeof(tty_default_code_keys[0]))); i += 1)
  {
    tdkc_idx = &tty_default_code_keys[i];
    s_idx = tty_term_string(tty->term, tdkc->code);
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkc->key);
    }
  }

  o_idx = options_get(global_options, "user-keys");
  if (((&o[o_idx]) != 0) && (options_array_size(o, &size) != (-1)))
  {
    for (i = 0; i < size; i += 1)
    {
      value_idx = options_array_get(o, i);
      if ((&value[value_idx]) != 0)
      {
        tty_keys_add(tty, value, 0x000020000000ULL + i);
      }
    }

  }
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
struct window *windows_RB_NEXT(struct window *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
void helper_cmd_set_option_exec_1(unsigned int * const o_idx_ref, struct cmdq_item * const item, int append, struct options * const oo, struct options_entry * const parent, struct options_entry * const o, char * const argument, char * const value, unsigned int value_idx, int idx)
{
  unsigned int o_idx = *o_idx_ref;
  if ((&value[value_idx]) == 0)
  {
    cmdq_error(item, "empty value");
    goto fail;
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_empty(oo, options_table_entry(parent));
  }
  if (idx == (-1))
  {
    if (!append)
    {
      options_array_clear(o);
    }
    options_array_assign(o, value);
  }
  else
    if (options_array_set(o, idx, value, append) != 0)
  {
    cmdq_error(item, "invalid index: %s", argument);
    goto fail;
  }
  *o_idx_ref = o_idx;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


----------------------------
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
None
----------------------------
int options_array_set(struct options_entry *o, u_int idx, const char *value, int append)
{
  char *new;
  unsigned int new_idx = 0;
  u_int i;
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (idx >= 1000)
  {
    return -1;
  }
  if (idx >= o->arraysize)
  {
    o->array = xreallocarray(o->array, idx + 1, sizeof(*o->array));
    for (i = o->arraysize; i < (idx + 1); i += 1)
    {
      o->array[i] = 0;
    }

    o->arraysize = idx + 1;
  }
  new_idx = 0;
  if (value != 0)
  {
    if ((o->array[idx] != 0) && append)
    {
      xasprintf(&(&new[new_idx]), "%s%s", o->array[idx], value);
    }
    else
      new_idx = xstrdup(value);
  }
  free((void *) o->array[idx]);
  o->array[idx] = &new[new_idx];
  return 0;
}


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
void status_timer_start_all(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    status_timer_start(c);
  }

}


----------------------------
void alerts_reset_all(void)
{
  struct window *w;
  unsigned int w_idx = 0;
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    alerts_reset(w);
  }

}


----------------------------
extern const struct cmd_entry cmd_set_window_option_entry
----------------------------
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}


----------------------------
void status_update_saved(struct session *s)
{
  if (!options_get_number(s->options, "status"))
  {
    s->statusat = -1;
  }
  else
    if (options_get_number(s->options, "status-position") == 0)
  {
    s->statusat = 0;
  }
  else
    s->statusat = 1;
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


