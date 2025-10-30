void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


/*** DEPENDENCIES:
***/


char *cmd_stringify_argv(int argc, char **argv)
{
  char *buf;
  unsigned int buf_idx = 0;
  int i;
  size_t len;
  if (argc == 0)
  {
    return xstrdup("");
  }
  len = 0;
  buf_idx = 0;
  for (i = 0; i < argc; i += 1)
  {
    len += strlen(argv[i]) + 1;
    buf_idx = xrealloc(buf_idx, len);
    if (i == 0)
    {
      buf[buf_idx] = '\0';
    }
    else
      strlcat(buf, " ", len);
    strlcat(buf, argv[i], len);
  }

  return buf;
}


/*** DEPENDENCIES:
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
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


int cmd_pack_argv(int argc, char **argv, char *buf, size_t len)
{
  unsigned int buf_idx = 0;
  size_t arglen;
  int i;
  if (argc == 0)
  {
    return 0;
  }
  buf[buf_idx] = '\0';
  for (i = 0; i < argc; i += 1)
  {
    if (strlcpy(buf, argv[i], len) >= len)
    {
      return -1;
    }
    arglen = strlen(argv[i]) + 1;
    buf_idx += arglen;
    len -= arglen;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


// hint:  ['buf_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'replaced_ref is a mutable refrence to int', 'quoted_ref is a mutable refrence to int', 'len_ref is a mutable refrence to size_t']
void helper_helper_cmd_template_replace_1_1(unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int * const replaced_ref, int * const quoted_ref, size_t * const len_ref, const char * const s, int idx, char * const buf, const char * const ptr, const char * const cp, const char quote[])
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int replaced = *replaced_ref;
  int quoted = *quoted_ref;
  size_t len = *len_ref;
  if (((ptr[ptr_idx] < '1') || (ptr[ptr_idx] > '9')) || ((ptr[ptr_idx] - '0') != idx))
  {
    if ((ptr[ptr_idx] != '%') || replaced)
    {
      break;
    }
    replaced = 1;
  }
  ptr_idx += 1;
  quoted = ptr[ptr_idx] == '%';
  if (quoted)
  {
    ptr_idx += 1;
  }
  buf_idx = xrealloc(buf_idx, (len + (strlen(s) * 3)) + 1);
  for (cp_idx = s; cp[cp_idx] != '\0'; cp_idx += 1)
  {
    if (quoted && (strchr(quote, *(&cp[cp_idx])) != 0))
    {
      buf[len + buf_idx] = '\\';
      len += 1;
    }
    if (quoted && (cp[cp_idx] == ';'))
    {
      buf[len + buf_idx] = '\\';
      len += 1;
      buf[len + buf_idx] = '\\';
      len += 1;
    }
    buf[len + buf_idx] = cp[cp_idx];
    len += 1;
  }

  buf[len + buf_idx] = '\0';
  continue;
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *replaced_ref = replaced;
  *quoted_ref = quoted;
  *len_ref = len;
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


char **cmd_copy_argv(int argc, char **argv)
{
  char **new_argv;
  unsigned int new_argv_idx = 0;
  int i;
  if (argc == 0)
  {
    return 0;
  }
  new_argv_idx = xcalloc(argc + 1, sizeof(*new_argv_idx));
  for (i = 0; i < argc; i += 1)
  {
    if (argv[i] != 0)
    {
      new_argv[i + new_argv_idx] = xstrdup(argv[i]);
    }
  }

  return new_argv;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['entry_idx_ref is a mutable refrence to unsigned int', 'ambiguous_ref is a mutable refrence to int']
void helper_cmd_parse_1(unsigned int * const entry_idx_ref, int * const ambiguous_ref, char ** const argv, const struct cmd_entry ** const entryp, unsigned int entryp_idx, const struct cmd_entry * const entry)
{
  unsigned int entry_idx = *entry_idx_ref;
  int ambiguous = *ambiguous_ref;
  if ((entryp[entryp_idx]->alias != 0) && (strcmp(entryp[entryp_idx]->alias, argv[0]) == 0))
  {
    ambiguous = 0;
    entry_idx = entryp[entryp_idx];
    break;
  }
  if (strncmp(entryp[entryp_idx]->name, argv[0], strlen(argv[0])) != 0)
  {
    continue;
  }
  if ((&entry[entry_idx]) != 0)
  {
    ambiguous = 1;
  }
  entry_idx = entryp[entryp_idx];
  if (strcmp(entry->name, argv[0]) == 0)
  {
    break;
  }
  *entry_idx_ref = entry_idx;
  *ambiguous_ref = ambiguous;
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['ch_ref is a mutable refrence to char', 'buf_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'replaced_ref is a mutable refrence to int', 'quoted_ref is a mutable refrence to int', 'len_ref is a mutable refrence to size_t']
void helper_cmd_template_replace_1(char * const ch_ref, unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int * const replaced_ref, int * const quoted_ref, size_t * const len_ref, const char * const s, int idx, char * const buf, const char * const ptr, const char * const cp, const char quote[])
{
  char ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int replaced = *replaced_ref;
  int quoted = *quoted_ref;
  size_t len = *len_ref;
  switch (ch = *((&ptr[ptr_idx])++))
  {
    case '%':
    {
      helper_helper_cmd_template_replace_1_1(&buf_idx, &ptr_idx, &cp_idx, &replaced, &quoted, &len, s, idx, buf, ptr, cp, quote);
    }

  }

  buf_idx = xrealloc(buf_idx, len + 2);
  buf[len + buf_idx] = ch;
  len += 1;
  buf[len + buf_idx] = '\0';
  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *replaced_ref = replaced;
  *quoted_ref = quoted;
  *len_ref = len;
}


/*** DEPENDENCIES:
void helper_helper_cmd_template_replace_1_1(unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int * const replaced_ref, int * const quoted_ref, size_t * const len_ref, const char * const s, int idx, char * const buf, const char * const ptr, const char * const cp, const char quote[])
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int replaced = *replaced_ref;
  int quoted = *quoted_ref;
  size_t len = *len_ref;
  if (((ptr[ptr_idx] < '1') || (ptr[ptr_idx] > '9')) || ((ptr[ptr_idx] - '0') != idx))
  {
    if ((ptr[ptr_idx] != '%') || replaced)
    {
      break;
    }
    replaced = 1;
  }
  ptr_idx += 1;
  quoted = ptr[ptr_idx] == '%';
  if (quoted)
  {
    ptr_idx += 1;
  }
  buf_idx = xrealloc(buf_idx, (len + (strlen(s) * 3)) + 1);
  for (cp_idx = s; cp[cp_idx] != '\0'; cp_idx += 1)
  {
    if (quoted && (strchr(quote, *(&cp[cp_idx])) != 0))
    {
      buf[len + buf_idx] = '\\';
      len += 1;
    }
    if (quoted && (cp[cp_idx] == ';'))
    {
      buf[len + buf_idx] = '\\';
      len += 1;
      buf[len + buf_idx] = '\\';
      len += 1;
    }
    buf[len + buf_idx] = cp[cp_idx];
    len += 1;
  }

  buf[len + buf_idx] = '\0';
  continue;
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *replaced_ref = replaced;
  *quoted_ref = quoted;
  *len_ref = len;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


struct winlink *cmd_mouse_window(struct mouse_event *m, struct session **sp)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  if (((!m->valid) || (m->s == (-1))) || (m->w == (-1)))
  {
    return 0;
  }
  if ((s_idx = session_find_by_id(m->s_idx)) == 0)
  {
    return 0;
  }
  if ((w_idx = window_find_by_id(m->w_idx)) == 0)
  {
    return 0;
  }
  if (sp != 0)
  {
    *sp = &s[s_idx];
  }
  return winlink_find_by_window(&s->windows, w);
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
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct session *session_find_by_id(u_int id)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->id == id)
    {
      return s;
    }
  }

  return 0;
}


----------------------------
struct winlink *winlink_find_by_window(struct winlinks *wwl, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window == w)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
struct window *window_find_by_id(u_int id)
{
  struct window w;
  w.id = id;
  return windows_RB_FIND(&windows, &w);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
}


----------------------------
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
int window_has_pane(struct window *w, struct window_pane *wp)
{
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    if ((&wp1[wp1_idx]) == wp)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
struct winlink *cmd_mouse_window(struct mouse_event *m, struct session **sp)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  if (((!m->valid) || (m->s == (-1))) || (m->w == (-1)))
  {
    return 0;
  }
  if ((s_idx = session_find_by_id(m->s_idx)) == 0)
  {
    return 0;
  }
  if ((w_idx = window_find_by_id(m->w_idx)) == 0)
  {
    return 0;
  }
  if (sp != 0)
  {
    *sp = &s[s_idx];
  }
  return winlink_find_by_window(&s->windows, w);
}


----------------------------
None
----------------------------
***/


static int cmd_try_alias(int *argc, char ***argv)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  int old_argc = *argc;
  int new_argc;
  char **old_argv = *argv;
  char **new_argv;
  u_int size;
  u_int idx;
  int i;
  size_t wanted;
  const char *s;
  unsigned int s_idx = 0;
  const char *cp = 0;
  unsigned int cp_idx = 0;
  o_idx = options_get_only(global_options, "command-alias");
  if ((((&o[o_idx]) == 0) || (options_array_size(o, &size) == (-1))) || (size == 0))
  {
    return -1;
  }
  wanted = strlen(old_argv[0]);
  for (idx = 0; idx < size; idx += 1)
  {
    s_idx = options_array_get(o, idx);
    if ((&s[s_idx]) == 0)
    {
      continue;
    }
    cp_idx = strchr(s, '=');
    if (((&cp[cp_idx]) == 0) || (((size_t) ((&cp[cp_idx]) - (&s[s_idx]))) != wanted))
    {
      continue;
    }
    if (strncmp(old_argv[0], s, wanted) == 0)
    {
      break;
    }
  }

  if (idx == size)
  {
    return -1;
  }
  if (cmd_string_split((&cp[cp_idx]) + 1, &new_argc, &new_argv) != 0)
  {
    return -1;
  }
  *argc = (new_argc + old_argc) - 1;
  *argv = xcalloc((*argc) + 1, sizeof(*(*argv)));
  for (i = 0; i < new_argc; i += 1)
  {
    (*argv)[i] = xstrdup(new_argv[i]);
  }

  for (i = 1; i < old_argc; i += 1)
  {
    (*argv)[(new_argc + i) - 1] = xstrdup(old_argv[i]);
  }

  log_debug("alias: %s=%s", old_argv[0], (&cp[cp_idx]) + 1);
  for (i = 0; i < (*argc); i += 1)
  {
    log_debug("alias: argv[%d] = %s", i, (*argv)[i]);
  }

  cmd_free_argv(new_argc, new_argv);
  return 0;
}


/*** DEPENDENCIES:
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
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
int cmd_string_split(const char *s, int *rargc, char ***rargv)
{
  size_t p = 0;
  int ch;
  int argc = 0;
  int append = 0;
  char **argv = 0;
  unsigned int argv_idx = 0;
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *t;
  unsigned int t_idx = 0;
  const char *whitespace;
  unsigned int whitespace_idx = 0;
  const char *equals;
  unsigned int equals_idx = 0;
  size_t len = 0;
  for (;;)
  {
    helper_cmd_string_split_1(&ch, &argc, &append, &argv_idx, &buf_idx, &t_idx, &whitespace_idx, &equals_idx, &len, s, p, argv, buf, t, whitespace, equals);
  }

  done:
  *rargc = argc;

  *rargv = &argv[argv_idx];
  free(buf);
  return 0;
  error:
  if ((&argv[argv_idx]) != 0)
  {
    cmd_free_argv(argc, argv);
  }

  free(buf);
  return -1;
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
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


struct cmd *cmd_parse(int argc, char **argv, const char *file, u_int line, char **cause)
{
  const char *name;
  unsigned int name_idx = 0;
  const struct cmd_entry **entryp;
  unsigned int entryp_idx = 0;
  const struct cmd_entry *entry;
  unsigned int entry_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct args *args;
  unsigned int args_idx = 0;
  char s[1024];
  int ambiguous;
  int allocated = 0;
  *cause = 0;
  if (argc == 0)
  {
    xasprintf(cause, "no command");
    return 0;
  }
  name_idx = argv[0];
  retry:
  ambiguous = 0;

  entry_idx = 0;
  for (entryp_idx = cmd_table; entryp[entryp_idx] != 0; entryp_idx += 1)
  {
    helper_cmd_parse_1(&entry_idx, &ambiguous, argv, entryp, entryp_idx, entry);
  }

  if ((((ambiguous || ((&entry[entry_idx]) == 0)) && (server_proc != 0)) && (!allocated)) && (cmd_try_alias(&argc, &argv) == 0))
  {
    allocated = 1;
    goto retry;
  }
  if (ambiguous)
  {
    goto ambiguous;
  }
  if ((&entry[entry_idx]) == 0)
  {
    xasprintf(cause, "unknown command: %s", name);
    return 0;
  }
  args_idx = args_parse(entry->args_idx.template, argc, argv);
  if ((&args[args_idx]) == 0)
  {
    goto usage;
  }
  if ((entry->args.lower != (-1)) && (args->argc < entry->args.lower))
  {
    goto usage;
  }
  if ((entry->args.upper != (-1)) && (args->argc > entry->args.upper))
  {
    goto usage;
  }
  cmd_idx = xcalloc(1, sizeof(*cmd_idx));
  cmd->entry = &entry[entry_idx];
  cmd->args = &args[args_idx];
  if (file != 0)
  {
    cmd->file = xstrdup(file);
  }
  cmd->line = line;
  if (allocated)
  {
    cmd_free_argv(argc, argv);
  }
  return cmd;
  ambiguous:
  *s = '\0';

  for (entryp_idx = cmd_table; entryp[entryp_idx] != 0; entryp_idx += 1)
  {
    if (strncmp(entryp[entryp_idx]->name, argv[0], strlen(argv[0])) != 0)
    {
      continue;
    }
    if (strlcat(s, entryp[entryp_idx]->name, sizeof(s)) >= (sizeof(s)))
    {
      break;
    }
    if (strlcat(s, ", ", sizeof(s)) >= (sizeof(s)))
    {
      break;
    }
  }

  s[strlen(s) - 2] = '\0';
  xasprintf(cause, "ambiguous command: %s, could be: %s", name, s);
  return 0;
  usage:
  if ((&args[args_idx]) != 0)
  {
    args_free(args);
  }

  xasprintf(cause, "usage: %s %s", entry->name, entry->usage);
  return 0;
}


/*** DEPENDENCIES:
void helper_cmd_parse_1(unsigned int * const entry_idx_ref, int * const ambiguous_ref, char ** const argv, const struct cmd_entry ** const entryp, unsigned int entryp_idx, const struct cmd_entry * const entry)
{
  unsigned int entry_idx = *entry_idx_ref;
  int ambiguous = *ambiguous_ref;
  if ((entryp[entryp_idx]->alias != 0) && (strcmp(entryp[entryp_idx]->alias, argv[0]) == 0))
  {
    ambiguous = 0;
    entry_idx = entryp[entryp_idx];
    break;
  }
  if (strncmp(entryp[entryp_idx]->name, argv[0], strlen(argv[0])) != 0)
  {
    continue;
  }
  if ((&entry[entry_idx]) != 0)
  {
    ambiguous = 1;
  }
  entry_idx = entryp[entryp_idx];
  if (strcmp(entry->name, argv[0]) == 0)
  {
    break;
  }
  *entry_idx_ref = entry_idx;
  *ambiguous_ref = ambiguous;
}


----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
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
extern const struct cmd_entry *cmd_table[]
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
static int cmd_try_alias(int *argc, char ***argv)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  int old_argc = *argc;
  int new_argc;
  char **old_argv = *argv;
  char **new_argv;
  u_int size;
  u_int idx;
  int i;
  size_t wanted;
  const char *s;
  unsigned int s_idx = 0;
  const char *cp = 0;
  unsigned int cp_idx = 0;
  o_idx = options_get_only(global_options, "command-alias");
  if ((((&o[o_idx]) == 0) || (options_array_size(o, &size) == (-1))) || (size == 0))
  {
    return -1;
  }
  wanted = strlen(old_argv[0]);
  for (idx = 0; idx < size; idx += 1)
  {
    s_idx = options_array_get(o, idx);
    if ((&s[s_idx]) == 0)
    {
      continue;
    }
    cp_idx = strchr(s, '=');
    if (((&cp[cp_idx]) == 0) || (((size_t) ((&cp[cp_idx]) - (&s[s_idx]))) != wanted))
    {
      continue;
    }
    if (strncmp(old_argv[0], s, wanted) == 0)
    {
      break;
    }
  }

  if (idx == size)
  {
    return -1;
  }
  if (cmd_string_split((&cp[cp_idx]) + 1, &new_argc, &new_argv) != 0)
  {
    return -1;
  }
  *argc = (new_argc + old_argc) - 1;
  *argv = xcalloc((*argc) + 1, sizeof(*(*argv)));
  for (i = 0; i < new_argc; i += 1)
  {
    (*argv)[i] = xstrdup(new_argv[i]);
  }

  for (i = 1; i < old_argc; i += 1)
  {
    (*argv)[(new_argc + i) - 1] = xstrdup(old_argv[i]);
  }

  log_debug("alias: %s=%s", old_argv[0], (&cp[cp_idx]) + 1);
  for (i = 0; i < (*argc); i += 1)
  {
    log_debug("alias: argv[%d] = %s", i, (*argv)[i]);
  }

  cmd_free_argv(new_argc, new_argv);
  return 0;
}


----------------------------
None
----------------------------
None
----------------------------
***/


int cmd_unpack_argv(char *buf, size_t len, int argc, char ***argv)
{
  unsigned int buf_idx = 0;
  int i;
  size_t arglen;
  if (argc == 0)
  {
    return 0;
  }
  *argv = xcalloc(argc, sizeof(*(*argv)));
  buf[(len - 1) + buf_idx] = '\0';
  for (i = 0; i < argc; i += 1)
  {
    if (len == 0)
    {
      cmd_free_argv(argc, *argv);
      return -1;
    }
    arglen = strlen(buf) + 1;
    (*argv)[i] = xstrdup(buf);
    buf_idx += arglen;
    len -= arglen;
  }

  return 0;
}


/*** DEPENDENCIES:
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
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
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
***/


int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
void helper_cmd_template_replace_1(char * const ch_ref, unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int * const replaced_ref, int * const quoted_ref, size_t * const len_ref, const char * const s, int idx, char * const buf, const char * const ptr, const char * const cp, const char quote[])
{
  char ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int replaced = *replaced_ref;
  int quoted = *quoted_ref;
  size_t len = *len_ref;
  switch (ch = *((&ptr[ptr_idx])++))
  {
    case '%':
    {
      helper_helper_cmd_template_replace_1_1(&buf_idx, &ptr_idx, &cp_idx, &replaced, &quoted, &len, s, idx, buf, ptr, cp, quote);
    }

  }

  buf_idx = xrealloc(buf_idx, len + 2);
  buf[len + buf_idx] = ch;
  len += 1;
  buf[len + buf_idx] = '\0';
  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *replaced_ref = replaced;
  *quoted_ref = quoted;
  *len_ref = len;
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
***/


char *cmd_print(struct cmd *cmd)
{
  char *out;
  unsigned int out_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  s_idx = args_print(cmd->args);
  if (s[s_idx] != '\0')
  {
    xasprintf(&(&out[out_idx]), "%s %s", cmd->entry->name, s);
  }
  else
    out_idx = xstrdup(cmd->entry->name);
  free(s);
  return out;
}


/*** DEPENDENCIES:
char *args_print(struct args *args)
{
  size_t len;
  char *buf;
  unsigned int buf_idx = 0;
  char *escaped;
  int i;
  int flags;
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  static const char quoted[] = " #\"';$";
  len = 1;
  buf_idx = xcalloc(1, len);
  for (entry_idx = args_tree_RB_MINMAX(&args->tree, -1); (&entry[entry_idx]) != 0; entry_idx = args_tree_RB_NEXT(entry_idx))
  {
    if (entry->value != 0)
    {
      continue;
    }
    if (buf[buf_idx] == '\0')
    {
      args_print_add(&(&buf[buf_idx]), &len, "-");
    }
    args_print_add(&(&buf[buf_idx]), &len, "%c", entry->flag);
  }

  for (entry_idx = args_tree_RB_MINMAX(&args->tree, -1); (&entry[entry_idx]) != 0; entry_idx = args_tree_RB_NEXT(entry_idx))
  {
    helper_args_print_1(&flags, len, buf, buf_idx, escaped, entry, quoted);
  }

  for (i = 0; i < args->argc; i += 1)
  {
    if (buf[buf_idx] != '\0')
    {
      args_print_add(&(&buf[buf_idx]), &len, " ");
    }
    flags = (0x01 | 0x08) | 0x10;
    if (args->argv[i][strcspn(args->argv[i], quoted)] != '\0')
    {
      flags |= 0x200;
    }
    utf8_stravis(&escaped, args->argv[i], flags);
    if (flags & 0x200)
    {
      args_print_add(&(&buf[buf_idx]), &len, "\"%s\"", escaped);
    }
    else
      args_print_add(&(&buf[buf_idx]), &len, "%s", escaped);
    free(escaped);
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
None
----------------------------
***/


