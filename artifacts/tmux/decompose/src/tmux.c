const char *find_home(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  static const char *home;
  unsigned int home_idx = 0;
  if ((&home[home_idx]) != 0)
  {
    return home;
  }
  home_idx = getenv("HOME");
  if (((&home[home_idx]) == 0) || (home[home_idx] == '\0'))
  {
    pw_idx = getpwuid(getuid());
    if ((&pw[pw_idx]) != 0)
    {
      home_idx = pw->pw_dir;
    }
    else
      home_idx = 0;
  }
  return home;
}


/*** DEPENDENCIES:
***/


void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
}


/*** DEPENDENCIES:
***/


int areshell(const char *shell)
{
  const char *progname;
  unsigned int progname_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  if ((ptr_idx = strrchr(shell, '/')) != 0)
  {
    ptr_idx += 1;
  }
  else
    ptr_idx = shell;
  progname_idx = getprogname();
  if (progname[progname_idx] == '-')
  {
    progname_idx += 1;
  }
  if (strcmp(ptr, progname) == 0)
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
const char *getprogname(void)
{
  return "tmux";
}


----------------------------
***/


static void usage(void)
{
  fprintf(stderr, "usage: %s [-2CluvV] [-c shell-command] [-f file] [-L socket-name]\n            [-S socket-path] [command [flags]]\n", getprogname());
  exit(1);
}


/*** DEPENDENCIES:
const char *getprogname(void)
{
  return "tmux";
}


----------------------------
***/


static char *make_label(const char *label, char **cause)
{
  unsigned int label_idx = 0;
  char *base;
  char resolved[PATH_MAX];
  char *path;
  char *s;
  unsigned int s_idx = 0;
  struct stat sb;
  uid_t uid;
  *cause = 0;
  if ((&label[label_idx]) == 0)
  {
    label_idx = "default";
  }
  uid = getuid();
  if (((s_idx = getenv("TMUX_TMPDIR")) != 0) && (s[s_idx] != '\0'))
  {
    xasprintf(&base, "%s/tmux-%ld", s, (long) uid);
  }
  else
    xasprintf(&base, "%s/tmux-%ld", "/tmp/", (long) uid);
  if ((realpath(base, resolved) == 0) && (strlcpy(resolved, base, sizeof(resolved)) >= (sizeof(resolved))))
  {
    errno = ERANGE;
    free(base);
    goto fail;
  }
  if ((mkdir(resolved, S_IRWXU) != 0) && (errno != EEXIST))
  {
    goto fail;
  }
  if (lstat(resolved, &sb) != 0)
  {
    goto fail;
  }
  if (!S_ISDIR(sb.st_mode))
  {
    errno = ENOTDIR;
    goto fail;
  }
  if ((sb.st_uid != uid) || ((sb.st_mode & S_IRWXO) != 0))
  {
    errno = EACCES;
    goto fail;
  }
  xasprintf(&path, "%s/%s", resolved, label);
  return path;
  fail:
  xasprintf(cause, "error creating %s (%s)", resolved, strerror(errno));

  return 0;
}


/*** DEPENDENCIES:
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
***/


static int checkshell(const char *shell)
{
  if ((shell == 0) || ((*shell) != '/'))
  {
    return 0;
  }
  if (areshell(shell))
  {
    return 0;
  }
  if (access(shell, X_OK) != 0)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
int areshell(const char *shell)
{
  const char *progname;
  unsigned int progname_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  if ((ptr_idx = strrchr(shell, '/')) != 0)
  {
    ptr_idx += 1;
  }
  else
    ptr_idx = shell;
  progname_idx = getprogname();
  if (progname[progname_idx] == '-')
  {
    progname_idx += 1;
  }
  if (strcmp(ptr, progname) == 0)
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


static const char *getshell(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  shell_idx = getenv("SHELL");
  if (checkshell(shell))
  {
    return shell;
  }
  pw_idx = getpwuid(getuid());
  if (((&pw[pw_idx]) != 0) && checkshell(pw->pw_shell))
  {
    return pw->pw_shell;
  }
  return "/bin/sh";
}


/*** DEPENDENCIES:
static int checkshell(const char *shell)
{
  if ((shell == 0) || ((*shell) != '/'))
  {
    return 0;
  }
  if (areshell(shell))
  {
    return 0;
  }
  if (access(shell, X_OK) != 0)
  {
    return 0;
  }
  return 1;
}


----------------------------
***/


// hint:  ['path_idx_ref is a mutable refrence to unsigned int', 'label_idx_ref is a mutable refrence to unsigned int', 'flags_ref is a mutable refrence to int']
void helper_main_1(unsigned int * const path_idx_ref, unsigned int * const label_idx_ref, int * const flags_ref, char * const path, char * const label, int opt)
{
  unsigned int path_idx = *path_idx_ref;
  unsigned int label_idx = *label_idx_ref;
  int flags = *flags_ref;
  switch (opt)
  {
    case '2':
    {
      flags |= 0x20000;
      break;
    }

    case 'c':
    {
      shell_command = BSDoptarg;
      break;
    }

    case 'C':
    {
      if (flags & 0x2000)
      {
        flags |= 0x4000;
      }
      else
        flags |= 0x2000;
      break;
    }

    case 'V':
    {
      printf("%s %s\n", getprogname(), VERSION);
      exit(0);
    }

    case 'f':
    {
      set_cfg_file(BSDoptarg);
      break;
    }

    case 'l':
    {
      flags |= 0x2;
      break;
    }

    case 'L':
    {
      free(label);
      label_idx = xstrdup(BSDoptarg);
      break;
    }

    case 'q':
    {
      break;
    }

    case 'S':
    {
      free(path);
      path_idx = xstrdup(BSDoptarg);
      break;
    }

    case 'u':
    {
      flags |= 0x10000;
      break;
    }

    case 'v':
    {
      log_add_level();
      break;
    }

    default:
    {
      usage();
    }

  }

  *path_idx_ref = path_idx;
  *label_idx_ref = label_idx;
  *flags_ref = flags;
}


/*** DEPENDENCIES:
const char *getprogname(void)
{
  return "tmux";
}


----------------------------
void set_cfg_file(const char *path)
{
  free(cfg_file);
  cfg_file = xstrdup(path);
}


----------------------------
extern const char *shell_command
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
extern char *BSDoptarg
----------------------------
void log_add_level(void)
{
  log_level += 1;
}


----------------------------
static void usage(void)
{
  fprintf(stderr, "usage: %s [-2CluvV] [-c shell-command] [-f file] [-L socket-name]\n            [-S socket-path] [command [flags]]\n", getprogname());
  exit(1);
}


----------------------------
***/


int main(int argc, char **argv)
{
  unsigned int argv_idx = 0;
  char *path;
  unsigned int path_idx = 0;
  char *label;
  unsigned int label_idx = 0;
  char *cause;
  char **var;
  unsigned int var_idx = 0;
  char tmp[PATH_MAX];
  const char *s;
  unsigned int s_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  const char *cwd;
  unsigned int cwd_idx = 0;
  int opt;
  int flags;
  int keys;
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  if ((setlocale(LC_CTYPE, "en_US.UTF-8") == 0) && (setlocale(LC_CTYPE, "C.UTF-8") == 0))
  {
    if (setlocale(LC_CTYPE, "") == 0)
    {
      errx(1, "invalid LC_ALL, LC_CTYPE or LANG");
    }
    s_idx = nl_langinfo(CODESET);
    if ((strcasecmp(s, "UTF-8") != 0) && (strcasecmp(s, "UTF8") != 0))
    {
      errx(1, "need UTF-8 locale (LC_CTYPE) but have %s", s);
    }
  }
  setlocale(LC_TIME, "");
  tzset();
  if ((*(*(&argv[argv_idx]))) == '-')
  {
    flags = 0x2;
  }
  else
    flags = 0;
  label_idx = (path = &path[path_idx + path_idx]);
  while ((opt = BSDgetopt(argc, argv, "2c:Cdf:lL:qS:uUVv")) != (-1))
  {
    helper_main_1(&path_idx, &label_idx, &flags, path, label, opt);
  }

  argc -= BSDoptind;
  argv_idx += BSDoptind;
  if ((shell_command != 0) && (argc != 0))
  {
    usage();
  }
  if ((ptm_fd = getptmfd()) == (-1))
  {
    err(1, "getptmfd");
  }
  if (0 != 0)
  {
    err(1, "pledge");
  }
  if (getenv("TMUX") != 0)
  {
    flags |= 0x10000;
  }
  else
  {
    s_idx = getenv("LC_ALL");
    if (((&s[s_idx]) == 0) || (s[s_idx] == '\0'))
    {
      s_idx = getenv("LC_CTYPE");
    }
    if (((&s[s_idx]) == 0) || (s[s_idx] == '\0'))
    {
      s_idx = getenv("LANG");
    }
    if (((&s[s_idx]) == 0) || (s[s_idx] == '\0'))
    {
      s_idx = "";
    }
    if ((strcasestr(s, "UTF-8") != 0) || (strcasestr(s, "UTF8") != 0))
    {
      flags |= 0x10000;
    }
  }
  global_hooks = hooks_create(0);
  global_environ = environ_create();
  for (var_idx = environ; var[var_idx] != 0; var_idx += 1)
  {
    environ_put(global_environ, *(&var[var_idx]));
  }

  if (((cwd_idx = getenv("PWD")) == 0) && ((cwd_idx = getcwd(tmp, sizeof(tmp))) != 0))
  {
    environ_set(global_environ, "PWD", "%s", cwd);
  }
  global_options = options_create(0);
  global_s_options = options_create(0);
  global_w_options = options_create(0);
  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (oe->scope == OPTIONS_TABLE_SERVER)
    {
      options_default(global_options, oe);
    }
    if (oe->scope == OPTIONS_TABLE_SESSION)
    {
      options_default(global_s_options, oe);
    }
    if (oe->scope == OPTIONS_TABLE_WINDOW)
    {
      options_default(global_w_options, oe);
    }
  }

  shell_idx = getshell();
  options_set_string(global_s_options, "default-shell", 0, "%s", shell);
  if (((s_idx = getenv("VISUAL")) != 0) || ((s_idx = getenv("EDITOR")) != 0))
  {
    if (strrchr(s, '/') != 0)
    {
      s_idx = strrchr(s_idx, '/') + 1;
    }
    if (strstr(s, "vi") != 0)
    {
      keys = 1;
    }
    else
      keys = 0;
    options_set_number(global_s_options, "status-keys", keys);
    options_set_number(global_w_options, "mode-keys", keys);
  }
  if (((&path[path_idx]) == 0) && ((&label[label_idx]) == 0))
  {
    s_idx = getenv("TMUX");
    if ((((&s[s_idx]) != 0) && (s[s_idx] != '\0')) && (s[s_idx] != ','))
    {
      path_idx = xstrdup(s);
      path[strcspn(path, ",") + path_idx] = '\0';
    }
  }
  if (((&path[path_idx]) == 0) && ((path_idx = make_label(label, &cause)) == 0))
  {
    if (cause != 0)
    {
      fprintf(stderr, "%s\n", cause);
      free(cause);
    }
    exit(1);
  }
  socket_path = &path[path_idx];
  free(label);
  exit(client_main(osdep_event_init(), argc, argv, flags));
}


/*** DEPENDENCIES:
struct environ *environ_create(void)
{
  struct environ *env;
  unsigned int env_idx = 0;
  env_idx = xcalloc(1, sizeof(*env_idx));
  do
  {
    env->rbh_root = 0;
  }
  while (0);
  return env;
}


----------------------------
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
extern const struct options_table_entry options_table[]
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
struct event_base *osdep_event_init(void)
{
  struct event_base *base;
  unsigned int base_idx = 0;
  setenv("EVENT_NOEPOLL", "1", 1);
  base_idx = event_init();
  unsetenv("EVENT_NOEPOLL");
  return base;
}


----------------------------
int getptmfd(void)
{
  return 2147483647;
}


----------------------------
extern const char *socket_path
----------------------------
void environ_put(struct environ *env, const char *var)
{
  char *name;
  unsigned int name_idx = 0;
  char *value;
  unsigned int value_idx = 0;
  value_idx = strchr(var, '=');
  if ((&value[value_idx]) == 0)
  {
    return;
  }
  value_idx += 1;
  name_idx = xstrdup(var);
  name[strcspn(name, "=") + name_idx] = '\0';
  environ_set(env, name, "%s", value);
  free(name);
}


----------------------------
extern int ptm_fd
----------------------------
extern int BSDoptind
----------------------------
None
----------------------------
void helper_main_1(unsigned int * const path_idx_ref, unsigned int * const label_idx_ref, int * const flags_ref, char * const path, char * const label, int opt)
{
  unsigned int path_idx = *path_idx_ref;
  unsigned int label_idx = *label_idx_ref;
  int flags = *flags_ref;
  switch (opt)
  {
    case '2':
    {
      flags |= 0x20000;
      break;
    }

    case 'c':
    {
      shell_command = BSDoptarg;
      break;
    }

    case 'C':
    {
      if (flags & 0x2000)
      {
        flags |= 0x4000;
      }
      else
        flags |= 0x2000;
      break;
    }

    case 'V':
    {
      printf("%s %s\n", getprogname(), VERSION);
      exit(0);
    }

    case 'f':
    {
      set_cfg_file(BSDoptarg);
      break;
    }

    case 'l':
    {
      flags |= 0x2;
      break;
    }

    case 'L':
    {
      free(label);
      label_idx = xstrdup(BSDoptarg);
      break;
    }

    case 'q':
    {
      break;
    }

    case 'S':
    {
      free(path);
      path_idx = xstrdup(BSDoptarg);
      break;
    }

    case 'u':
    {
      flags |= 0x10000;
      break;
    }

    case 'v':
    {
      log_add_level();
      break;
    }

    default:
    {
      usage();
    }

  }

  *path_idx_ref = path_idx;
  *label_idx_ref = label_idx;
  *flags_ref = flags;
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
int client_main(struct event_base *base, int argc, char **argv, int flags)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct msg_command_data *data;
  unsigned int data_idx = 0;
  int cmdflags;
  int fd;
  int i;
  const char *ttynam;
  unsigned int ttynam_idx = 0;
  const char *cwd;
  unsigned int cwd_idx = 0;
  pid_t ppid;
  enum msgtype msg;
  char *cause;
  char path[PATH_MAX];
  struct termios tio;
  struct termios saved_tio;
  size_t size;
  signal(SIGCHLD, SIG_IGN);
  client_flags = flags;
  cmdflags = 0;
  if (shell_command != 0)
  {
    msg = MSG_SHELL;
    cmdflags = 0x1;
  }
  else
    if (argc == 0)
  {
    msg = MSG_COMMAND;
    cmdflags = 0x1;
  }
  else
  {
    msg = MSG_COMMAND;
    cmdlist_idx = cmd_list_parse(argc, argv, 0, 0, &cause);
    if ((&cmdlist[cmdlist_idx]) != 0)
    {
      for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
      {
        if (cmd->entry->flags & 0x1)
        {
          cmdflags |= 0x1;
        }
      }

      cmd_list_free(cmdlist);
    }
  }
  client_proc = proc_start("client");
  proc_set_signals(client_proc, client_signal);
  fd = client_connect(base, socket_path, cmdflags & 0x1);
  if (fd == (-1))
  {
    if (errno == ECONNREFUSED)
    {
      fprintf(stderr, "no server running on %s\n", socket_path);
    }
    else
    {
      fprintf(stderr, "error connecting to %s (%s)\n", socket_path, strerror(errno));
    }
    return 1;
  }
  client_peer = proc_add_peer(client_proc, fd, client_dispatch, 0);
  if ((((cwd_idx = getenv("PWD")) == 0) && ((cwd_idx = getcwd(path, sizeof(path))) == 0)) && ((cwd_idx = find_home()) == 0))
  {
    cwd_idx = "/";
  }
  if ((ttynam_idx = ttyname(STDIN_FILENO)) == 0)
  {
    ttynam_idx = "";
  }
  if (0 != 0)
  {
    fatal("pledge failed");
  }
  if (ptm_fd != (-1))
  {
    close(ptm_fd);
  }
  options_free(global_options);
  options_free(global_s_options);
  options_free(global_w_options);
  environ_free(global_environ);
  setblocking(STDIN_FILENO, 0);
  event_set(&client_stdin, STDIN_FILENO, EV_READ | EV_PERSIST, client_stdin_callback, 0);
  if (client_flags & 0x4000)
  {
    helper_client_main_1(&tio, saved_tio);
  }
  client_send_identify(ttynam, cwd);
  if (msg == MSG_COMMAND)
  {
    helper_client_main_2(&argc, &data_idx, &i, &size, argv, data, msg);
  }
  else
    if (msg == MSG_SHELL)
  {
    proc_send(client_peer, msg, -1, 0, 0);
  }
  proc_loop(client_proc, 0);
  if (client_exittype == MSG_EXEC)
  {
    if (client_flags & 0x4000)
    {
      tcsetattr(STDOUT_FILENO, TCSAFLUSH, &saved_tio);
    }
    client_exec(client_execshell, client_execcmd);
  }
  if (client_attached)
  {
    if (client_exitreason != CLIENT_EXIT_NONE)
    {
      printf("[%s]\n", client_exit_message());
    }
    ppid = getppid();
    if ((client_exittype == MSG_DETACHKILL) && (ppid > 1))
    {
      kill(ppid, SIGHUP);
    }
  }
  else
    if (client_flags & 0x4000)
  {
    if (client_exitreason != CLIENT_EXIT_NONE)
    {
      printf("%%exit %s\n", client_exit_message());
    }
    else
      printf("%%exit\n");
    printf("\033\\");
    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &saved_tio);
  }
  else
    if (client_exitreason != CLIENT_EXIT_NONE)
  {
    fprintf(stderr, "%s\n", client_exit_message());
  }
  setblocking(STDIN_FILENO, 1);
  return client_exitval;
}


----------------------------
void environ_set(struct environ *env, const char *name, const char *fmt, ...)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  va_list ap;
  __builtin_va_start(ap);
  if ((envent_idx = environ_find(env, name)) != 0)
  {
    free(envent->value);
    xvasprintf(&envent->value, fmt, ap);
  }
  else
  {
    envent_idx = xmalloc(sizeof(*envent_idx));
    envent->name = xstrdup(name);
    xvasprintf(&envent->value, fmt, ap);
    environ_RB_INSERT(env, envent);
  }
  ;
}


----------------------------
extern const char *shell_command
----------------------------
struct hooks *hooks_create(struct hooks *parent)
{
  struct hooks *hooks;
  unsigned int hooks_idx = 0;
  hooks_idx = xcalloc(1, sizeof(*hooks_idx));
  do
  {
    (&hooks->tree)->rbh_root = 0;
  }
  while (0);
  hooks->parent = parent;
  return hooks;
}


----------------------------
static char *make_label(const char *label, char **cause)
{
  unsigned int label_idx = 0;
  char *base;
  char resolved[PATH_MAX];
  char *path;
  char *s;
  unsigned int s_idx = 0;
  struct stat sb;
  uid_t uid;
  *cause = 0;
  if ((&label[label_idx]) == 0)
  {
    label_idx = "default";
  }
  uid = getuid();
  if (((s_idx = getenv("TMUX_TMPDIR")) != 0) && (s[s_idx] != '\0'))
  {
    xasprintf(&base, "%s/tmux-%ld", s, (long) uid);
  }
  else
    xasprintf(&base, "%s/tmux-%ld", "/tmp/", (long) uid);
  if ((realpath(base, resolved) == 0) && (strlcpy(resolved, base, sizeof(resolved)) >= (sizeof(resolved))))
  {
    errno = ERANGE;
    free(base);
    goto fail;
  }
  if ((mkdir(resolved, S_IRWXU) != 0) && (errno != EEXIST))
  {
    goto fail;
  }
  if (lstat(resolved, &sb) != 0)
  {
    goto fail;
  }
  if (!S_ISDIR(sb.st_mode))
  {
    errno = ENOTDIR;
    goto fail;
  }
  if ((sb.st_uid != uid) || ((sb.st_mode & S_IRWXO) != 0))
  {
    errno = EACCES;
    goto fail;
  }
  xasprintf(&path, "%s/%s", resolved, label);
  return path;
  fail:
  xasprintf(cause, "error creating %s (%s)", resolved, strerror(errno));

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
static const char *getshell(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  shell_idx = getenv("SHELL");
  if (checkshell(shell))
  {
    return shell;
  }
  pw_idx = getpwuid(getuid());
  if (((&pw[pw_idx]) != 0) && checkshell(pw->pw_shell))
  {
    return pw->pw_shell;
  }
  return "/bin/sh";
}


----------------------------
int BSDgetopt(int nargc, char * const *nargv, const char *ostr)
{
  static const char *place = "";
  unsigned int place_idx = 0;
  char *oli;
  unsigned int oli_idx = 0;
  if (ostr == 0)
  {
    return -1;
  }
  if (BSDoptreset || (!(*(&place[place_idx]))))
  {
    BSDoptreset = 0;
    if ((BSDoptind >= nargc) || ((*(place_idx = nargv[BSDoptind])) != '-'))
    {
      place_idx = "";
      return -1;
    }
    if (place[1 + place_idx] && ((*(++(&place[place_idx]))) == '-'))
    {
      if (place[1 + place_idx])
      {
        return (int) '?';
      }
      BSDoptind += 1;
      place_idx = "";
      return -1;
    }
  }
  if (((BSDoptopt = (int) (*((&place[place_idx])++))) == ((int) ':')) || (!(oli_idx = strchr(ostr, BSDoptopt))))
  {
    if (BSDoptopt == ((int) '-'))
    {
      return -1;
    }
    if (!(*(&place[place_idx])))
    {
      BSDoptind += 1;
    }
    if (BSDopterr && ((*ostr) != ':'))
    {
      (void) fprintf(stderr, "%s: unknown option -- %c\n", getprogname(), BSDoptopt);
    }
    return (int) '?';
  }
  if ((*(++(&oli[oli_idx]))) != ':')
  {
    BSDoptarg = 0;
    if (!(*(&place[place_idx])))
    {
      BSDoptind += 1;
    }
  }
  else
  {
    if (place[place_idx])
    {
      BSDoptarg = (char *) place;
    }
    else
      if (nargc <= (++BSDoptind))
    {
      place_idx = "";
      if ((*ostr) == ':')
      {
        return (int) ':';
      }
      if (BSDopterr)
      {
        (void) fprintf(stderr, "%s: option requires an argument -- %c\n", getprogname(), BSDoptopt);
      }
      return (int) '?';
    }
    else
      BSDoptarg = nargv[BSDoptind];
    place_idx = "";
    BSDoptind += 1;
  }
  return BSDoptopt;
}


----------------------------
struct options *options_create(struct options *parent)
{
  struct options *oo;
  unsigned int oo_idx = 0;
  oo_idx = xcalloc(1, sizeof(*oo_idx));
  do
  {
    (&oo->tree)->rbh_root = 0;
  }
  while (0);
  oo->parent = parent;
  return oo;
}


----------------------------
static void usage(void)
{
  fprintf(stderr, "usage: %s [-2CluvV] [-c shell-command] [-f file] [-L socket-name]\n            [-S socket-path] [command [flags]]\n", getprogname());
  exit(1);
}


----------------------------
None
----------------------------
***/


