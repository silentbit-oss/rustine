static void cmd_send_keys_inject(struct client *c, struct cmdq_item *item, key_code key)
{
  struct window_pane *wp = item->target.wp;
  struct session *s = item->target.s;
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding bd_find;
  if ((wp->mode == 0) || (wp->mode->key_table == 0))
  {
    if (options_get_number(wp->window->options, "xterm-keys"))
    {
      key |= 0x1000000000000ULL;
    }
    window_pane_key(wp, 0, s, key, 0);
    return;
  }
  table_idx = key_bindings_get_table(wp->mode->key_table(wp), 1);
  bd_find.key = key & (~0x1000000000000ULL);
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) != 0)
  {
    table->references += 1;
    key_bindings_dispatch(bd, item, c, 0, &item->target);
    key_bindings_unref_table(table);
  }
}


/*** DEPENDENCIES:
void key_bindings_dispatch(struct key_binding *bd, struct cmdq_item *item, struct client *c, struct mouse_event *m, struct cmd_find_state *fs)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  int readonly;
  readonly = 1;
  for (cmd_idx = (&bd->cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    if (!(cmd->entry->flags & 0x2))
    {
      readonly = 0;
    }
  }

  if ((!readonly) && (c->flags & 0x800))
  {
    new_item_idx = cmdq_get_callback1("key_bindings_read_only", key_bindings_read_only, 0);
  }
  else
  {
    new_item_idx = cmdq_get_command(bd->cmdlist, fs, m, 0);
    if (bd->flags & 0x1)
    {
      new_item->shared->flags |= 0x1;
    }
  }
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(c, new_item);
}


----------------------------
struct key_binding *key_bindings_RB_FIND(struct key_bindings *head, struct key_binding *elm)
{
  struct key_binding *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = key_bindings_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
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
void key_bindings_unref_table(struct key_table *table)
{
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding *bd1;
  unsigned int bd1_idx = 0;
  if ((--table->references) != 0)
  {
    return;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); ((&bd[bd_idx]) != 0) && ((bd1_idx = key_bindings_RB_NEXT(bd), 1)); bd_idx = &bd1[bd1_idx])
  {
    key_bindings_RB_REMOVE(&table->key_bindings, bd);
    cmd_list_free(bd->cmdlist);
    free(bd);
  }

  free((void *) table->name);
  free(table);
}


----------------------------
void window_pane_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (m == 0))
  {
    return;
  }
  if (wp->mode != 0)
  {
    wp->modelast = time(0);
    if (wp->mode->key != 0)
    {
      wp->mode->key(wp, c, s, key & (~0x1000000000000ULL), m);
    }
    return;
  }
  if ((wp->fd == (-1)) || (wp->flags & 0x40))
  {
    return;
  }
  input_key(wp, key, m);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    return;
  }
  if (options_get_number(wp->window->options, "synchronize-panes"))
  {
    for (wp2_idx = (&wp->window->panes)->tqh_first; (&wp2[wp2_idx]) != 0; wp2_idx = wp2_idx->entry.tqe_next)
    {
      if (((&wp2[wp2_idx]) == wp) || (wp2->mode != 0))
      {
        continue;
      }
      if ((wp2->fd == (-1)) || (wp2->flags & 0x40))
      {
        continue;
      }
      if (window_pane_visible(wp2))
      {
        input_key(wp2, key, 0);
      }
    }

  }
}


----------------------------
None
----------------------------
***/


// hint:  ['ud_idx_ref is a mutable refrence to unsigned int', 'uc_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int', 'literal_ref is a mutable refrence to int', 'key_ref is a mutable refrence to key_code']
void helper_cmd_send_keys_exec_1(unsigned int * const ud_idx_ref, unsigned int * const uc_idx_ref, int * const i_ref, int * const literal_ref, key_code * const key_ref, struct cmdq_item * const item, struct args * const args, struct client * const c, struct utf8_data * const ud, struct utf8_data * const uc, wchar_t wc)
{
  unsigned int ud_idx = *ud_idx_ref;
  unsigned int uc_idx = *uc_idx_ref;
  int i = *i_ref;
  int literal = *literal_ref;
  key_code key = *key_ref;
  for (i = 0; i < args->argc; i += 1)
  {
    literal = args_has(args, 'l');
    if (!literal)
    {
      key = key_string_lookup_string(args->argv[i]);
      if ((key != 0xffff00000000ULL) && (key != 0xfffe00000000ULL))
      {
        cmd_send_keys_inject(c, item, key);
      }
      else
        literal = 1;
    }
    if (literal)
    {
      ud_idx = utf8_fromcstr(args->argv[i]);
      for (uc_idx = &ud[ud_idx]; uc->size != 0; uc_idx += 1)
      {
        if (utf8_combine(uc, &wc) != UTF8_DONE)
        {
          continue;
        }
        cmd_send_keys_inject(c, item, wc);
      }

      free(ud);
    }
  }

  *ud_idx_ref = ud_idx;
  *uc_idx_ref = uc_idx;
  *i_ref = i;
  *literal_ref = literal;
  *key_ref = key;
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
enum utf8_state utf8_combine(const struct utf8_data *ud, wchar_t *wc)
{
  switch (mbtowc(wc, ud->data, ud->size))
  {
    case -1:
    {
      log_debug("UTF-8 %.*s, mbtowc() %d", (int) ud->size, ud->data, errno);
      mbtowc(0, 0, MB_CUR_MAX);
      return UTF8_ERROR;
    }

    case 0:
    {
      return UTF8_ERROR;
    }

    default:
    {
      return UTF8_DONE;
    }

  }

}


----------------------------
typedef unsigned long long key_code
----------------------------
static void cmd_send_keys_inject(struct client *c, struct cmdq_item *item, key_code key)
{
  struct window_pane *wp = item->target.wp;
  struct session *s = item->target.s;
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding bd_find;
  if ((wp->mode == 0) || (wp->mode->key_table == 0))
  {
    if (options_get_number(wp->window->options, "xterm-keys"))
    {
      key |= 0x1000000000000ULL;
    }
    window_pane_key(wp, 0, s, key, 0);
    return;
  }
  table_idx = key_bindings_get_table(wp->mode->key_table(wp), 1);
  bd_find.key = key & (~0x1000000000000ULL);
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) != 0)
  {
    table->references += 1;
    key_bindings_dispatch(bd, item, c, 0, &item->target);
    key_bindings_unref_table(table);
  }
}


----------------------------
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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


static enum cmd_retval cmd_send_keys_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct window_pane *wp = item->target.wp;
  unsigned int wp_idx = 0;
  struct session *s = item->target.s;
  struct mouse_event *m = &item->shared->mouse;
  struct utf8_data *ud;
  unsigned int ud_idx = 0;
  struct utf8_data *uc;
  unsigned int uc_idx = 0;
  wchar_t wc;
  int i;
  int literal;
  key_code key;
  u_int np = 1;
  char *cause = 0;
  if (args_has(args, 'N'))
  {
    np = args_strtonum(args, 'N', 1, 4294967295U, &cause);
    if (cause != 0)
    {
      cmdq_error(item, "repeat count %s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    if (args_has(args, 'X') || (args->argc == 0))
    {
      wp->modeprefix = np;
    }
  }
  if (args_has(args, 'X'))
  {
    if ((wp->mode == 0) || (wp->mode->command == 0))
    {
      cmdq_error(item, "not in a mode");
      return CMD_RETURN_ERROR;
    }
    if (!m->valid)
    {
      wp->mode->command(wp, c, s, args, 0);
    }
    else
      wp->mode->command(wp, c, s, args, m);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'M'))
  {
    wp_idx = cmd_mouse_pane(m, &s, 0);
    if ((&wp[wp_idx]) == 0)
    {
      cmdq_error(item, "no mouse target");
      return CMD_RETURN_ERROR;
    }
    window_pane_key(wp, 0, s, m->key, m);
    return CMD_RETURN_NORMAL;
  }
  if (self->entry == (&cmd_send_prefix_entry))
  {
    if (args_has(args, '2'))
    {
      key = options_get_number(s->options, "prefix2");
    }
    else
      key = options_get_number(s->options, "prefix");
    cmd_send_keys_inject(c, item, key);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'R'))
  {
    window_pane_reset_palette(wp);
    input_reset(wp, 1);
  }
  for (; np != 0; np -= 1)
  {
    helper_cmd_send_keys_exec_1(&ud_idx, &uc_idx, &i, &literal, &key, item, args, c, ud, uc, wc);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct mouse_event
{
  int valid;
  key_code key;
  int statusat;
  u_int x;
  u_int y;
  u_int b;
  u_int lx;
  u_int ly;
  u_int lb;
  int s;
  int w;
  int wp;
  u_int sgr_type;
  u_int sgr_b;
}
----------------------------
typedef unsigned long long key_code
----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
void window_pane_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (m == 0))
  {
    return;
  }
  if (wp->mode != 0)
  {
    wp->modelast = time(0);
    if (wp->mode->key != 0)
    {
      wp->mode->key(wp, c, s, key & (~0x1000000000000ULL), m);
    }
    return;
  }
  if ((wp->fd == (-1)) || (wp->flags & 0x40))
  {
    return;
  }
  input_key(wp, key, m);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    return;
  }
  if (options_get_number(wp->window->options, "synchronize-panes"))
  {
    for (wp2_idx = (&wp->window->panes)->tqh_first; (&wp2[wp2_idx]) != 0; wp2_idx = wp2_idx->entry.tqe_next)
    {
      if (((&wp2[wp2_idx]) == wp) || (wp2->mode != 0))
      {
        continue;
      }
      if ((wp2->fd == (-1)) || (wp2->flags & 0x40))
      {
        continue;
      }
      if (window_pane_visible(wp2))
      {
        input_key(wp2, key, 0);
      }
    }

  }
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
void window_pane_reset_palette(struct window_pane *wp)
{
  if (wp->palette == 0)
  {
    return;
  }
  free(wp->palette);
  wp->palette = 0;
  wp->flags |= 0x1;
}


----------------------------
static void cmd_send_keys_inject(struct client *c, struct cmdq_item *item, key_code key)
{
  struct window_pane *wp = item->target.wp;
  struct session *s = item->target.s;
  struct key_table *table;
  unsigned int table_idx = 0;
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding bd_find;
  if ((wp->mode == 0) || (wp->mode->key_table == 0))
  {
    if (options_get_number(wp->window->options, "xterm-keys"))
    {
      key |= 0x1000000000000ULL;
    }
    window_pane_key(wp, 0, s, key, 0);
    return;
  }
  table_idx = key_bindings_get_table(wp->mode->key_table(wp), 1);
  bd_find.key = key & (~0x1000000000000ULL);
  bd_idx = key_bindings_RB_FIND(&table->key_bindings, &bd_find);
  if ((&bd[bd_idx]) != 0)
  {
    table->references += 1;
    key_bindings_dispatch(bd, item, c, 0, &item->target);
    key_bindings_unref_table(table);
  }
}


----------------------------
void input_reset(struct window_pane *wp, int clear)
{
  struct input_ctx *ictx = wp->ictx;
  input_reset_cell(ictx);
  if (clear)
  {
    if (wp->mode == 0)
    {
      screen_write_start(&ictx->ctx, wp, &wp->base);
    }
    else
      screen_write_start(&ictx->ctx, 0, &wp->base);
    screen_write_reset(&ictx->ctx);
    screen_write_stop(&ictx->ctx);
  }
  input_clear(ictx);
  ictx->last = -1;
  ictx->state = &input_state_ground;
  ictx->flags = 0;
}


----------------------------
void helper_cmd_send_keys_exec_1(unsigned int * const ud_idx_ref, unsigned int * const uc_idx_ref, int * const i_ref, int * const literal_ref, key_code * const key_ref, struct cmdq_item * const item, struct args * const args, struct client * const c, struct utf8_data * const ud, struct utf8_data * const uc, wchar_t wc)
{
  unsigned int ud_idx = *ud_idx_ref;
  unsigned int uc_idx = *uc_idx_ref;
  int i = *i_ref;
  int literal = *literal_ref;
  key_code key = *key_ref;
  for (i = 0; i < args->argc; i += 1)
  {
    literal = args_has(args, 'l');
    if (!literal)
    {
      key = key_string_lookup_string(args->argv[i]);
      if ((key != 0xffff00000000ULL) && (key != 0xfffe00000000ULL))
      {
        cmd_send_keys_inject(c, item, key);
      }
      else
        literal = 1;
    }
    if (literal)
    {
      ud_idx = utf8_fromcstr(args->argv[i]);
      for (uc_idx = &ud[ud_idx]; uc->size != 0; uc_idx += 1)
      {
        if (utf8_combine(uc, &wc) != UTF8_DONE)
        {
          continue;
        }
        cmd_send_keys_inject(c, item, wc);
      }

      free(ud);
    }
  }

  *ud_idx_ref = ud_idx;
  *uc_idx_ref = uc_idx;
  *i_ref = i;
  *literal_ref = literal;
  *key_ref = key;
}


----------------------------
extern const struct cmd_entry cmd_send_prefix_entry
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


