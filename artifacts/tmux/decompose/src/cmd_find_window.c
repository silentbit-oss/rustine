static enum cmd_retval cmd_find_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct args *new_args;
  unsigned int new_args_idx = 0;
  struct window_pane *wp = item->target.wp;
  const char *s = args->argv[0];
  char *filter;
  char *argv = {0};
  int C;
  int N;
  int T;
  C = args_has(args, 'C');
  N = args_has(args, 'N');
  T = args_has(args, 'T');
  if (((!C) && (!N)) && (!T))
  {
    C = (N = (T = 1));
  }
  if ((C && N) && T)
  {
    xasprintf(&filter, "#{||:#{C:%s},#{||:#{m:*%s*,#{window_name}},#{m:*%s*,#{pane_title}}}}", s, s, s);
  }
  else
    if (C && N)
  {
    xasprintf(&filter, "#{||:#{C:%s},#{m:*%s*,#{window_name}}}", s, s);
  }
  else
    if (C && T)
  {
    xasprintf(&filter, "#{||:#{C:%s},#{m:*%s*,#{pane_title}}}", s, s);
  }
  else
    if (N && T)
  {
    xasprintf(&filter, "#{||:#{m:*%s*,#{window_name}},#{m:*%s*,#{pane_title}}}", s, s);
  }
  else
    if (C)
  {
    xasprintf(&filter, "#{C:%s}", s);
  }
  else
    if (N)
  {
    xasprintf(&filter, "#{m:*%s*,#{window_name}}", s);
  }
  else
    xasprintf(&filter, "#{m:*%s*,#{pane_title}}", s);
  new_args_idx = args_parse("", 1, &argv);
  args_set(new_args, 'f', filter);
  window_pane_set_mode(wp, &window_tree_mode, &item->target, new_args);
  args_free(new_args);
  free(filter);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct args *args_parse(const char *template, int argc, char **argv)
{
  unsigned int argv_idx = 0;
  struct args *args;
  unsigned int args_idx = 0;
  int opt;
  args_idx = xcalloc(1, sizeof(*args_idx));
  BSDoptreset = 1;
  BSDoptind = 1;
  while ((opt = BSDgetopt(argc, argv, template)) != (-1))
  {
    if (opt < 0)
    {
      continue;
    }
    if ((opt == '?') || (strchr(template, opt) == 0))
    {
      args_free(args);
      return 0;
    }
    args_set(args, opt, BSDoptarg);
  }

  argc -= BSDoptind;
  argv_idx += BSDoptind;
  args->argc = argc;
  args->argv = cmd_copy_argv(argc, argv);
  return args;
}


----------------------------
void args_free(struct args *args)
{
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  struct args_entry *entry1;
  unsigned int entry1_idx = 0;
  cmd_free_argv(args->argc, args->argv);
  for (entry_idx = args_tree_RB_MINMAX(&args->tree, -1); ((&entry[entry_idx]) != 0) && ((entry1_idx = args_tree_RB_NEXT(entry), 1)); entry_idx = &entry1[entry1_idx])
  {
    args_tree_RB_REMOVE(&args->tree, entry);
    free(entry->value);
    free(entry);
  }

  free(args);
}


----------------------------
extern const struct window_mode window_tree_mode
----------------------------
int window_pane_set_mode(struct window_pane *wp, const struct window_mode *mode, struct cmd_find_state *fs, struct args *args)
{
  struct screen *s;
  unsigned int s_idx = 0;
  struct timeval tv = {.tv_sec = 10};
  if (wp->mode != 0)
  {
    return 1;
  }
  wp->mode = mode;
  wp->modelast = time(0);
  evtimer_set(&wp->modetimer, window_pane_mode_timer, wp);
  evtimer_add(&wp->modetimer, &tv);
  if ((s_idx = wp->mode->init(wp, fs, args)) != 0)
  {
    wp->screen = &s[s_idx];
  }
  wp->flags |= 0x1 | 0x80;
  server_status_window(wp->window);
  notify_pane("pane-mode-changed", wp);
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
None
----------------------------
void args_set(struct args *args, u_char ch, const char *value)
{
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) != 0)
  {
    free(entry->value);
    entry->value = 0;
  }
  else
  {
    entry_idx = xcalloc(1, sizeof(*entry_idx));
    entry->flag = ch;
    args_tree_RB_INSERT(&args->tree, entry);
  }
  if (value != 0)
  {
    entry->value = xstrdup(value);
  }
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


