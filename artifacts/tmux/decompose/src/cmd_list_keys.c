// hint:  ['bd_idx_ref is a mutable refrence to unsigned int', 'key_idx_ref is a mutable refrence to unsigned int', 'repeat_ref is a mutable refrence to int', 'width_ref is a mutable refrence to int', 'tablewidth_ref is a mutable refrence to int', 'keywidth_ref is a mutable refrence to int']
void helper_cmd_list_keys_exec_1(unsigned int * const bd_idx_ref, unsigned int * const key_idx_ref, int * const repeat_ref, int * const width_ref, int * const tablewidth_ref, int * const keywidth_ref, struct key_table * const table, struct key_binding * const bd, const char * const key, const char * const tablename, unsigned int tablename_idx)
{
  unsigned int bd_idx = *bd_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  int repeat = *repeat_ref;
  int width = *width_ref;
  int tablewidth = *tablewidth_ref;
  int keywidth = *keywidth_ref;
  if (((&tablename[tablename_idx]) != 0) && (strcmp(table->name, tablename) != 0))
  {
    continue;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); (&bd[bd_idx]) != 0; bd_idx = key_bindings_RB_NEXT(bd_idx))
  {
    key_idx = key_string_lookup_key(bd->key_idx);
    if (bd->flags & 0x1)
    {
      repeat = 1;
    }
    width = utf8_cstrwidth(table->name);
    if (width > tablewidth)
    {
      tablewidth = width;
    }
    width = utf8_cstrwidth(key);
    if (width > keywidth)
    {
      keywidth = width;
    }
  }

  *bd_idx_ref = bd_idx;
  *key_idx_ref = key_idx;
  *repeat_ref = repeat;
  *width_ref = width;
  *tablewidth_ref = tablewidth;
  *keywidth_ref = keywidth;
}


/*** DEPENDENCIES:
const char *key_string_lookup_key(key_code key)
{
  static char out[32];
  char tmp[8];
  u_int i;
  struct utf8_data ud;
  size_t off;
  *out = '\0';
  if (key == 0xffff00000000ULL)
  {
    return "None";
  }
  if (key == 0xfffe00000000ULL)
  {
    return "Unknown";
  }
  if (key == KEYC_FOCUS_IN)
  {
    return "FocusIn";
  }
  if (key == KEYC_FOCUS_OUT)
  {
    return "FocusOut";
  }
  if (key == KEYC_PASTE_START)
  {
    return "PasteStart";
  }
  if (key == KEYC_PASTE_END)
  {
    return "PasteEnd";
  }
  if (key == KEYC_MOUSE)
  {
    return "Mouse";
  }
  if (key == KEYC_DRAGGING)
  {
    return "Dragging";
  }
  if (key == KEYC_MOUSEMOVE_PANE)
  {
    return "MouseMovePane";
  }
  if (key == KEYC_MOUSEMOVE_STATUS)
  {
    return "MouseMoveStatus";
  }
  if (key == KEYC_MOUSEMOVE_BORDER)
  {
    return "MouseMoveBorder";
  }
  if ((key >= 0x000020000000ULL) && (key < (0x000020000000ULL + 1000)))
  {
    snprintf(out, sizeof(out), "User%u", (u_int) (key - 0x000020000000ULL));
    return out;
  }
  if ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == 0)
  {
    key = (' ' | 0x400000000000ULL) | (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
  }
  if (key & 0x400000000000ULL)
  {
    strlcat(out, "C-", sizeof(out));
  }
  if (key & 0x200000000000ULL)
  {
    strlcat(out, "M-", sizeof(out));
  }
  if (key & 0x800000000000ULL)
  {
    strlcat(out, "S-", sizeof(out));
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (key == key_string_table[i].key)
    {
      break;
    }
  }

  if (i != ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))))
  {
    strlcat(out, key_string_table[i].string, sizeof(out));
    return out;
  }
  if ((key > 127) && (key < 0x000010000000ULL))
  {
    if (utf8_split(key, &ud) == UTF8_DONE)
    {
      off = strlen(out);
      memcpy(out + off, ud.data, ud.size);
      out[off + ud.size] = '\0';
      return out;
    }
  }
  if ((key == 127) || (key > 255))
  {
    snprintf(out, sizeof(out), "Invalid#%llx", key);
    return out;
  }
  if (key <= 32)
  {
    if ((key == 0) || (key > 26))
    {
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (64 + key));
    }
    else
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (96 + key));
  }
  else
    if ((key >= 32) && (key <= 126))
  {
    tmp[0] = key;
    tmp[1] = '\0';
  }
  else
    if (key >= 128)
  {
    xsnprintf(tmp, sizeof(tmp), "\\%llo", key);
  }
  strlcat(out, tmp, sizeof(out));
  return out;
}


----------------------------
u_int utf8_cstrwidth(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data tmp;
  u_int width;
  enum utf8_state more;
  width = 0;
  while (s[s_idx] != '\0')
  {
    if ((more = utf8_open(&tmp, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((*(++(&s[s_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&tmp, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        width += tmp.width;
        continue;
      }
      s_idx -= tmp.have;
    }
    if ((s[s_idx] > 0x1f) && (s[s_idx] != 0x7f))
    {
      width += 1;
    }
    s_idx += 1;
  }

  return width;
}


----------------------------
struct key_binding *key_bindings_RB_MINMAX(struct key_bindings *head, int val)
{
  struct key_binding *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct key_binding *parent = 0;
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
struct key_binding *key_bindings_RB_NEXT(struct key_binding *elm)
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
None
----------------------------
***/


// hint:  ['entry_idx_ref is a mutable refrence to unsigned int', 's_idx_ref is a mutable refrence to unsigned int', 'line_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_list_keys_commands_1(unsigned int * const entry_idx_ref, unsigned int * const s_idx_ref, unsigned int * const line_idx_ref, struct cmdq_item * const item, const struct cmd_entry ** const entryp, unsigned int entryp_idx, const struct cmd_entry * const entry, struct format_tree * const ft, const char * const template, const char * const s, char * const line)
{
  unsigned int entry_idx = *entry_idx_ref;
  unsigned int s_idx = *s_idx_ref;
  unsigned int line_idx = *line_idx_ref;
  entry_idx = entryp[entryp_idx];
  format_add(ft, "command_list_name", "%s", entry->name);
  if (entry->alias != 0)
  {
    s_idx = entry->alias;
  }
  else
    s_idx = "";
  format_add(ft, "command_list_alias", "%s", s);
  if (entry->usage != 0)
  {
    s_idx = entry->usage;
  }
  else
    s_idx = "";
  format_add(ft, "command_list_usage", "%s", s);
  line_idx = format_expand(ft, template);
  if (line[line_idx] != '\0')
  {
    cmdq_print(item, "%s", line);
  }
  free(line);
  *entry_idx_ref = entry_idx;
  *s_idx_ref = s_idx;
  *line_idx_ref = line_idx;
}


/*** DEPENDENCIES:
void format_add(struct format_tree *ft, const char *key, const char *fmt, ...)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
  va_list ap;
  fe_idx = xmalloc(sizeof(*fe_idx));
  fe->key = xstrdup(key);
  fe_now_idx = format_entry_tree_RB_INSERT(&ft->tree, fe);
  if ((&fe_now[fe_now_idx]) != 0)
  {
    free(fe->key);
    free(fe);
    free(fe_now->value);
    fe_idx = &fe_now[fe_now_idx];
  }
  fe->cb = 0;
  fe->t = 0;
  __builtin_va_start(ap);
  xvasprintf(&fe->value, fmt, ap);
  ;
}


----------------------------
None
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
None
----------------------------
***/


// hint:  ['bd_idx_ref is a mutable refrence to unsigned int', 'key_idx_ref is a mutable refrence to unsigned int', 'r_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_list_keys_exec_2(unsigned int * const bd_idx_ref, unsigned int * const key_idx_ref, unsigned int * const r_idx_ref, unsigned int * const cp_idx_ref, struct cmdq_item * const item, struct key_table * const table, struct key_binding * const bd, const char * const key, const char * const tablename, unsigned int tablename_idx, const char * const r, char * const cp, char tmp[1024], int repeat, int tablewidth, int keywidth)
{
  unsigned int bd_idx = *bd_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  unsigned int r_idx = *r_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  if (((&tablename[tablename_idx]) != 0) && (strcmp(table->name, tablename) != 0))
  {
    continue;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); (&bd[bd_idx]) != 0; bd_idx = key_bindings_RB_NEXT(bd_idx))
  {
    key_idx = key_string_lookup_key(bd->key_idx);
    if (!repeat)
    {
      r_idx = "";
    }
    else
      if (bd->flags & 0x1)
    {
      r_idx = "-r ";
    }
    else
      r_idx = "   ";
    xsnprintf(tmp, sizeof(tmp), "%s-T ", r);
    cp_idx = utf8_padcstr(table->name, tablewidth);
    strlcat(tmp, cp, sizeof(tmp));
    strlcat(tmp, " ", sizeof(tmp));
    free(cp);
    cp_idx = utf8_padcstr(key, keywidth);
    strlcat(tmp, cp, sizeof(tmp));
    strlcat(tmp, " ", sizeof(tmp));
    free(cp);
    cp_idx = cmd_list_print(bd->cmdlist);
    strlcat(tmp, cp, sizeof(tmp));
    free(cp);
    cmdq_print(item, "bind-key %s", tmp);
  }

  *bd_idx_ref = bd_idx;
  *key_idx_ref = key_idx;
  *r_idx_ref = r_idx;
  *cp_idx_ref = cp_idx;
}


/*** DEPENDENCIES:
struct key_binding *key_bindings_RB_MINMAX(struct key_bindings *head, int val)
{
  struct key_binding *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct key_binding *parent = 0;
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
const char *key_string_lookup_key(key_code key)
{
  static char out[32];
  char tmp[8];
  u_int i;
  struct utf8_data ud;
  size_t off;
  *out = '\0';
  if (key == 0xffff00000000ULL)
  {
    return "None";
  }
  if (key == 0xfffe00000000ULL)
  {
    return "Unknown";
  }
  if (key == KEYC_FOCUS_IN)
  {
    return "FocusIn";
  }
  if (key == KEYC_FOCUS_OUT)
  {
    return "FocusOut";
  }
  if (key == KEYC_PASTE_START)
  {
    return "PasteStart";
  }
  if (key == KEYC_PASTE_END)
  {
    return "PasteEnd";
  }
  if (key == KEYC_MOUSE)
  {
    return "Mouse";
  }
  if (key == KEYC_DRAGGING)
  {
    return "Dragging";
  }
  if (key == KEYC_MOUSEMOVE_PANE)
  {
    return "MouseMovePane";
  }
  if (key == KEYC_MOUSEMOVE_STATUS)
  {
    return "MouseMoveStatus";
  }
  if (key == KEYC_MOUSEMOVE_BORDER)
  {
    return "MouseMoveBorder";
  }
  if ((key >= 0x000020000000ULL) && (key < (0x000020000000ULL + 1000)))
  {
    snprintf(out, sizeof(out), "User%u", (u_int) (key - 0x000020000000ULL));
    return out;
  }
  if ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == 0)
  {
    key = (' ' | 0x400000000000ULL) | (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
  }
  if (key & 0x400000000000ULL)
  {
    strlcat(out, "C-", sizeof(out));
  }
  if (key & 0x200000000000ULL)
  {
    strlcat(out, "M-", sizeof(out));
  }
  if (key & 0x800000000000ULL)
  {
    strlcat(out, "S-", sizeof(out));
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (key == key_string_table[i].key)
    {
      break;
    }
  }

  if (i != ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))))
  {
    strlcat(out, key_string_table[i].string, sizeof(out));
    return out;
  }
  if ((key > 127) && (key < 0x000010000000ULL))
  {
    if (utf8_split(key, &ud) == UTF8_DONE)
    {
      off = strlen(out);
      memcpy(out + off, ud.data, ud.size);
      out[off + ud.size] = '\0';
      return out;
    }
  }
  if ((key == 127) || (key > 255))
  {
    snprintf(out, sizeof(out), "Invalid#%llx", key);
    return out;
  }
  if (key <= 32)
  {
    if ((key == 0) || (key > 26))
    {
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (64 + key));
    }
    else
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (96 + key));
  }
  else
    if ((key >= 32) && (key <= 126))
  {
    tmp[0] = key;
    tmp[1] = '\0';
  }
  else
    if (key >= 128)
  {
    xsnprintf(tmp, sizeof(tmp), "\\%llo", key);
  }
  strlcat(out, tmp, sizeof(out));
  return out;
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
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
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
char *utf8_padcstr(const char *s, u_int width)
{
  size_t slen;
  char *out;
  unsigned int out_idx = 0;
  u_int n;
  u_int i;
  n = utf8_cstrwidth(s);
  if (n >= width)
  {
    return xstrdup(s);
  }
  slen = strlen(s);
  out_idx = xmalloc((slen + 1) + (width - n));
  memcpy(out, s, slen);
  for (i = n; i < width; i += 1)
  {
    out[slen + out_idx] = ' ';
    slen += 1;
  }

  out[slen + out_idx] = '\0';
  return out;
}


----------------------------
struct key_binding *key_bindings_RB_NEXT(struct key_binding *elm)
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
None
----------------------------
***/


static enum cmd_retval cmd_list_keys_commands(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  const struct cmd_entry **entryp;
  unsigned int entryp_idx = 0;
  const struct cmd_entry *entry;
  unsigned int entry_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  if ((template_idx = args_get(args, 'F')) == 0)
  {
    template_idx = "#{command_list_name}#{?command_list_alias, (#{command_list_alias}),} #{command_list_usage}";
  }
  ft_idx = format_create(item->client, item, 0, 0);
  format_defaults(ft, 0, 0, 0, 0);
  for (entryp_idx = cmd_table; entryp[entryp_idx] != 0; entryp_idx += 1)
  {
    helper_cmd_list_keys_commands_1(&entry_idx, &s_idx, &line_idx, item, entryp, entryp_idx, entry, ft, template, s, line);
  }

  format_free(ft);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void format_free(struct format_tree *ft)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe1;
  unsigned int fe1_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&ft->tree, -1); ((&fe[fe_idx]) != 0) && ((fe1_idx = format_entry_tree_RB_NEXT(fe), 1)); fe_idx = &fe1[fe1_idx])
  {
    format_entry_tree_RB_REMOVE(&ft->tree, fe);
    free(fe->value);
    free(fe->key);
    free(fe);
  }

  if (ft->client != 0)
  {
    server_client_unref(ft->client);
  }
  free(ft);
}


----------------------------
extern const struct cmd_entry *cmd_table[]
----------------------------
void helper_cmd_list_keys_commands_1(unsigned int * const entry_idx_ref, unsigned int * const s_idx_ref, unsigned int * const line_idx_ref, struct cmdq_item * const item, const struct cmd_entry ** const entryp, unsigned int entryp_idx, const struct cmd_entry * const entry, struct format_tree * const ft, const char * const template, const char * const s, char * const line)
{
  unsigned int entry_idx = *entry_idx_ref;
  unsigned int s_idx = *s_idx_ref;
  unsigned int line_idx = *line_idx_ref;
  entry_idx = entryp[entryp_idx];
  format_add(ft, "command_list_name", "%s", entry->name);
  if (entry->alias != 0)
  {
    s_idx = entry->alias;
  }
  else
    s_idx = "";
  format_add(ft, "command_list_alias", "%s", s);
  if (entry->usage != 0)
  {
    s_idx = entry->usage;
  }
  else
    s_idx = "";
  format_add(ft, "command_list_usage", "%s", s);
  line_idx = format_expand(ft, template);
  if (line[line_idx] != '\0')
  {
    cmdq_print(item, "%s", line);
  }
  free(line);
  *entry_idx_ref = entry_idx;
  *s_idx_ref = s_idx;
  *line_idx_ref = line_idx;
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
struct format_tree *format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  if (!event_initialized(&format_job_event))
  {
    evtimer_set(&format_job_event, format_job_timer, 0);
    format_job_timer(-1, 0, 0);
  }
  ft_idx = xcalloc(1, sizeof(*ft_idx));
  do
  {
    (&ft->tree)->rbh_root = 0;
  }
  while (0);
  if (c != 0)
  {
    ft->client = c;
    ft->client->references += 1;
  }
  ft->tag = tag;
  ft->flags = flags;
  format_add(ft, "version", "%s", VERSION);
  format_add_cb(ft, "host", format_cb_host);
  format_add_cb(ft, "host_short", format_cb_host_short);
  format_add_cb(ft, "pid", format_cb_pid);
  format_add(ft, "socket_path", "%s", socket_path);
  format_add_tv(ft, "start_time", &start_time);
  if (item != 0)
  {
    if (item->cmd != 0)
    {
      format_add(ft, "command", "%s", item->cmd->entry->name);
    }
    if ((item->shared != 0) && (item->shared->formats != 0))
    {
      format_merge(ft, item->shared->formats);
    }
  }
  return ft;
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
void format_defaults(struct format_tree *ft, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  unsigned int wp_idx = 0;
  unsigned int wl_idx = 0;
  unsigned int s_idx = 0;
  if (((c != 0) && ((&s[s_idx]) != 0)) && (c->session != (&s[s_idx])))
  {
    log_debug("%s: session does not match", __func__);
  }
  format_add(ft, "session_format", "%d", (&s[s_idx]) != 0);
  format_add(ft, "window_format", "%d", (&wl[wl_idx]) != 0);
  format_add(ft, "pane_format", "%d", (&wp[wp_idx]) != 0);
  if (((&s[s_idx]) == 0) && (c != 0))
  {
    s_idx = c->session;
  }
  if (((&wl[wl_idx]) == 0) && ((&s[s_idx]) != 0))
  {
    wl_idx = s->curw;
  }
  if (((&wp[wp_idx]) == 0) && ((&wl[wl_idx]) != 0))
  {
    wp_idx = wl->window->active;
  }
  if (c != 0)
  {
    format_defaults_client(ft, c);
  }
  if ((&s[s_idx]) != 0)
  {
    format_defaults_session(ft, s);
  }
  if ((&wl[wl_idx]) != 0)
  {
    format_defaults_winlink(ft, wl);
  }
  if ((&wp[wp_idx]) != 0)
  {
    format_defaults_pane(ft, wp);
  }
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_list_keys_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  const char *key;
  unsigned int key_idx = 0;
  const char *tablename;
  unsigned int tablename_idx = 0;
  const char *r;
  unsigned int r_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char tmp[1024];
  int repeat;
  int width;
  int tablewidth;
  int keywidth;
  if (self->entry == (&cmd_list_commands_entry))
  {
    return cmd_list_keys_commands(self, item);
  }
  tablename_idx = args_get(args, 'T');
  if (((&tablename[tablename_idx]) != 0) && (key_bindings_get_table(tablename, 0) == 0))
  {
    cmdq_error(item, "table %s doesn't exist", tablename);
    return CMD_RETURN_ERROR;
  }
  repeat = 0;
  tablewidth = (keywidth = 0);
  for (table_idx = key_tables_RB_MINMAX(&key_tables, -1); (&table[table_idx]) != 0; table_idx = key_tables_RB_NEXT(table_idx))
  {
    helper_cmd_list_keys_exec_1(&bd_idx, &key_idx, &repeat, &width, &tablewidth, &keywidth, table, bd, key, tablename, tablename_idx);
  }

  for (table_idx = key_tables_RB_MINMAX(&key_tables, -1); (&table[table_idx]) != 0; table_idx = key_tables_RB_NEXT(table_idx))
  {
    helper_cmd_list_keys_exec_2(&bd_idx, &key_idx, &r_idx, &cp_idx, item, table, bd, key, tablename, tablename_idx, r, cp, tmp, repeat, tablewidth, keywidth);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
static enum cmd_retval cmd_list_keys_commands(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  const struct cmd_entry **entryp;
  unsigned int entryp_idx = 0;
  const struct cmd_entry *entry;
  unsigned int entry_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  if ((template_idx = args_get(args, 'F')) == 0)
  {
    template_idx = "#{command_list_name}#{?command_list_alias, (#{command_list_alias}),} #{command_list_usage}";
  }
  ft_idx = format_create(item->client, item, 0, 0);
  format_defaults(ft, 0, 0, 0, 0);
  for (entryp_idx = cmd_table; entryp[entryp_idx] != 0; entryp_idx += 1)
  {
    helper_cmd_list_keys_commands_1(&entry_idx, &s_idx, &line_idx, item, entryp, entryp_idx, entry, ft, template, s, line);
  }

  format_free(ft);
  return CMD_RETURN_NORMAL;
}


----------------------------
void helper_cmd_list_keys_exec_2(unsigned int * const bd_idx_ref, unsigned int * const key_idx_ref, unsigned int * const r_idx_ref, unsigned int * const cp_idx_ref, struct cmdq_item * const item, struct key_table * const table, struct key_binding * const bd, const char * const key, const char * const tablename, unsigned int tablename_idx, const char * const r, char * const cp, char tmp[1024], int repeat, int tablewidth, int keywidth)
{
  unsigned int bd_idx = *bd_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  unsigned int r_idx = *r_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  if (((&tablename[tablename_idx]) != 0) && (strcmp(table->name, tablename) != 0))
  {
    continue;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); (&bd[bd_idx]) != 0; bd_idx = key_bindings_RB_NEXT(bd_idx))
  {
    key_idx = key_string_lookup_key(bd->key_idx);
    if (!repeat)
    {
      r_idx = "";
    }
    else
      if (bd->flags & 0x1)
    {
      r_idx = "-r ";
    }
    else
      r_idx = "   ";
    xsnprintf(tmp, sizeof(tmp), "%s-T ", r);
    cp_idx = utf8_padcstr(table->name, tablewidth);
    strlcat(tmp, cp, sizeof(tmp));
    strlcat(tmp, " ", sizeof(tmp));
    free(cp);
    cp_idx = utf8_padcstr(key, keywidth);
    strlcat(tmp, cp, sizeof(tmp));
    strlcat(tmp, " ", sizeof(tmp));
    free(cp);
    cp_idx = cmd_list_print(bd->cmdlist);
    strlcat(tmp, cp, sizeof(tmp));
    free(cp);
    cmdq_print(item, "bind-key %s", tmp);
  }

  *bd_idx_ref = bd_idx;
  *key_idx_ref = key_idx;
  *r_idx_ref = r_idx;
  *cp_idx_ref = cp_idx;
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
extern const struct cmd_entry cmd_list_commands_entry
----------------------------
struct key_tables
{
  struct key_table *rbh_root;
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
void helper_cmd_list_keys_exec_1(unsigned int * const bd_idx_ref, unsigned int * const key_idx_ref, int * const repeat_ref, int * const width_ref, int * const tablewidth_ref, int * const keywidth_ref, struct key_table * const table, struct key_binding * const bd, const char * const key, const char * const tablename, unsigned int tablename_idx)
{
  unsigned int bd_idx = *bd_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  int repeat = *repeat_ref;
  int width = *width_ref;
  int tablewidth = *tablewidth_ref;
  int keywidth = *keywidth_ref;
  if (((&tablename[tablename_idx]) != 0) && (strcmp(table->name, tablename) != 0))
  {
    continue;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); (&bd[bd_idx]) != 0; bd_idx = key_bindings_RB_NEXT(bd_idx))
  {
    key_idx = key_string_lookup_key(bd->key_idx);
    if (bd->flags & 0x1)
    {
      repeat = 1;
    }
    width = utf8_cstrwidth(table->name);
    if (width > tablewidth)
    {
      tablewidth = width;
    }
    width = utf8_cstrwidth(key);
    if (width > keywidth)
    {
      keywidth = width;
    }
  }

  *bd_idx_ref = bd_idx;
  *key_idx_ref = key_idx;
  *repeat_ref = repeat;
  *width_ref = width;
  *tablewidth_ref = tablewidth;
  *keywidth_ref = keywidth;
}


----------------------------
None
----------------------------
struct key_table *key_tables_RB_MINMAX(struct key_tables *head, int val)
{
  struct key_table *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct key_table *parent = 0;
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
struct key_table *key_tables_RB_NEXT(struct key_table *elm)
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
None
----------------------------
***/


