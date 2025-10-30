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


/*** DEPENDENCIES:
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
None
----------------------------
***/


// hint:  ['cmd_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int', 'lastsplit_ref is a mutable refrence to int', 'arglen_ref is a mutable refrence to size_t', 'new_argc_ref is a mutable refrence to size_t', 'copy_argv_idx_ref is a mutable refrence to unsigned int', 'new_argv_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_list_parse_1(unsigned int * const cmd_idx_ref, int * const i_ref, int * const lastsplit_ref, size_t * const arglen_ref, size_t * const new_argc_ref, unsigned int * const copy_argv_idx_ref, unsigned int * const new_argv_idx_ref, const char * const file, u_int line, char ** const cause, struct cmd_list * const cmdlist, struct cmd * const cmd, char ** const copy_argv, char ** const new_argv)
{
  unsigned int cmd_idx = *cmd_idx_ref;
  int i = *i_ref;
  int lastsplit = *lastsplit_ref;
  size_t arglen = *arglen_ref;
  size_t new_argc = *new_argc_ref;
  unsigned int copy_argv_idx = *copy_argv_idx_ref;
  unsigned int new_argv_idx = *new_argv_idx_ref;
  arglen = strlen(copy_argv[i + copy_argv_idx]);
  if ((arglen == 0) || (copy_argv[i + copy_argv_idx][arglen - 1] != ';'))
  {
    continue;
  }
  copy_argv[i + copy_argv_idx][arglen - 1] = '\0';
  if ((arglen > 1) && (copy_argv[i + copy_argv_idx][arglen - 2] == '\\'))
  {
    copy_argv[i + copy_argv_idx][arglen - 2] = ';';
    continue;
  }
  new_argc = i - lastsplit;
  new_argv_idx = (&copy_argv[copy_argv_idx]) + lastsplit;
  if (arglen != 1)
  {
    new_argc += 1;
  }
  cmd_idx = cmd_parse(new_argc, new_argv, file, line, cause);
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
  lastsplit = i + 1;
  *cmd_idx_ref = cmd_idx;
  *i_ref = i;
  *lastsplit_ref = lastsplit;
  *arglen_ref = arglen;
  *new_argc_ref = new_argc;
  *copy_argv_idx_ref = copy_argv_idx;
  *new_argv_idx_ref = new_argv_idx;
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
void helper_cmd_list_parse_1(unsigned int * const cmd_idx_ref, int * const i_ref, int * const lastsplit_ref, size_t * const arglen_ref, size_t * const new_argc_ref, unsigned int * const copy_argv_idx_ref, unsigned int * const new_argv_idx_ref, const char * const file, u_int line, char ** const cause, struct cmd_list * const cmdlist, struct cmd * const cmd, char ** const copy_argv, char ** const new_argv)
{
  unsigned int cmd_idx = *cmd_idx_ref;
  int i = *i_ref;
  int lastsplit = *lastsplit_ref;
  size_t arglen = *arglen_ref;
  size_t new_argc = *new_argc_ref;
  unsigned int copy_argv_idx = *copy_argv_idx_ref;
  unsigned int new_argv_idx = *new_argv_idx_ref;
  arglen = strlen(copy_argv[i + copy_argv_idx]);
  if ((arglen == 0) || (copy_argv[i + copy_argv_idx][arglen - 1] != ';'))
  {
    continue;
  }
  copy_argv[i + copy_argv_idx][arglen - 1] = '\0';
  if ((arglen > 1) && (copy_argv[i + copy_argv_idx][arglen - 2] == '\\'))
  {
    copy_argv[i + copy_argv_idx][arglen - 2] = ';';
    continue;
  }
  new_argc = i - lastsplit;
  new_argv_idx = (&copy_argv[copy_argv_idx]) + lastsplit;
  if (arglen != 1)
  {
    new_argc += 1;
  }
  cmd_idx = cmd_parse(new_argc, new_argv, file, line, cause);
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
  lastsplit = i + 1;
  *cmd_idx_ref = cmd_idx;
  *i_ref = i;
  *lastsplit_ref = lastsplit;
  *arglen_ref = arglen;
  *new_argc_ref = new_argc;
  *copy_argv_idx_ref = copy_argv_idx;
  *new_argv_idx_ref = new_argv_idx;
}


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
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
None
----------------------------
***/


