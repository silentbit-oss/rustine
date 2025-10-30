static enum cmd_retval cmd_rename_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  char *newname;
  unsigned int newname_idx = 0;
  newname_idx = format_single(item, args->argv[0], c, s, wl, 0);
  window_set_name(wl->window, newname);
  options_set_number(wl->window->options, "automatic-rename", 0);
  server_status_window(wl->window);
  free(newname);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void server_status_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (session_has(s, w))
    {
      server_status_session(s);
    }
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
void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
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


