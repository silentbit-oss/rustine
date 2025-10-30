// hint:  ['tio_ref is a mutable refrence to ']
int helper_client_main_1(struct termios * const tio_ref, struct termios saved_tio)
{
  struct termios tio = *tio_ref;
  if (tcgetattr(STDIN_FILENO, &saved_tio) != 0)
  {
    fprintf(stderr, "tcgetattr failed: %s\n", strerror(errno));
    return 1;
  }
  cfmakeraw(&tio);
  tio.c_iflag = ICRNL | IXANY;
  tio.c_oflag = OPOST | ONLCR;
  tio.c_cflag = (CREAD | CS8) | HUPCL;
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  cfsetispeed(&tio, cfgetispeed(&saved_tio));
  cfsetospeed(&tio, cfgetospeed(&saved_tio));
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
  *tio_ref = tio;
}


/*** DEPENDENCIES:
***/


static int client_get_lock(char *lockfile)
{
  int lockfd;
  log_debug("lock file is %s", lockfile);
  if ((lockfd = open(lockfile, O_WRONLY | O_CREAT, 0600)) == (-1))
  {
    log_debug("open failed: %s", strerror(errno));
    return -1;
  }
  if (0 == (-1))
  {
    log_debug("flock failed: %s", strerror(errno));
    if (errno != EAGAIN)
    {
      return lockfd;
    }
    while ((0 == (-1)) && (errno == EINTR))
    {
      ;
    }

    close(lockfd);
    return -2;
  }
  log_debug("flock succeeded");
  return lockfd;
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


static void client_write(int fd, const char *data, size_t size)
{
  unsigned int data_idx = 0;
  ssize_t used;
  log_debug("%s: %.*s", __func__, (int) size, data);
  while (size != 0)
  {
    used = write(fd, data, size);
    if (used == (-1))
    {
      if ((errno == EINTR) || (errno == EAGAIN))
      {
        continue;
      }
      break;
    }
    data_idx += used;
    size -= used;
  }

}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


// hint:  ['fd_ref is a mutable refrence to int', 'lockfd_ref is a mutable refrence to int', 'locked_ref is a mutable refrence to int', 'lockfile_idx_ref is a mutable refrence to unsigned int']
int helper_client_connect_1(int * const fd_ref, int * const lockfd_ref, int * const locked_ref, unsigned int * const lockfile_idx_ref, struct event_base * const base, const char * const path, int start_server, char * const lockfile)
{
  int fd = *fd_ref;
  int lockfd = *lockfd_ref;
  int locked = *locked_ref;
  unsigned int lockfile_idx = *lockfile_idx_ref;
  log_debug("connect failed: %s", strerror(errno));
  if ((errno != ECONNREFUSED) && (errno != ENOENT))
  {
    goto failed;
  }
  if (!start_server)
  {
    goto failed;
  }
  close(fd);
  if (!locked)
  {
    xasprintf(&(&lockfile[lockfile_idx]), "%s.lock", path);
    if ((lockfd = client_get_lock(lockfile)) < 0)
    {
      log_debug("didn't get lock (%d)", lockfd);
      free(lockfile);
      lockfile_idx = 0;
      if (lockfd == (-2))
      {
        goto retry;
      }
    }
    log_debug("got lock (%d)", lockfd);
    locked = 1;
    goto retry;
  }
  if (((lockfd >= 0) && (unlink(path) != 0)) && (errno != ENOENT))
  {
    free(lockfile);
    close(lockfd);
    return -1;
  }
  fd = server_start(client_proc, base, lockfd, lockfile);
  *fd_ref = fd;
  *lockfd_ref = lockfd;
  *locked_ref = locked;
  *lockfile_idx_ref = lockfile_idx;
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
static int client_get_lock(char *lockfile)
{
  int lockfd;
  log_debug("lock file is %s", lockfile);
  if ((lockfd = open(lockfile, O_WRONLY | O_CREAT, 0600)) == (-1))
  {
    log_debug("open failed: %s", strerror(errno));
    return -1;
  }
  if (0 == (-1))
  {
    log_debug("flock failed: %s", strerror(errno));
    if (errno != EAGAIN)
    {
      return lockfd;
    }
    while ((0 == (-1)) && (errno == EINTR))
    {
      ;
    }

    close(lockfd);
    return -2;
  }
  log_debug("flock succeeded");
  return lockfd;
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
int server_start(struct tmuxproc *client, struct event_base *base, int lockfd, char *lockfile)
{
  int pair[2];
  struct job *job;
  unsigned int job_idx = 0;
  sigset_t set;
  sigset_t oldset;
  struct client *c;
  unsigned int c_idx = 0;
  char *cause = 0;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pair) != 0)
  {
    fatal("socketpair failed");
  }
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (fork())
  {
    case -1:
    {
      fatal("fork failed");
    }

    case 0:
    {
      break;
    }

    default:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      close(pair[1]);
      return pair[0];
    }

  }

  close(pair[0]);
  if (daemon(1, 0) != 0)
  {
    fatal("daemon failed");
  }
  proc_clear_signals(client, 0);
  if (event_reinit(base) != 0)
  {
    fatalx("event_reinit failed");
  }
  server_proc = proc_start("server");
  proc_set_signals(server_proc, server_signal);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  if (log_get_level() > 1)
  {
    tty_create_log();
  }
  if (0 != 0)
  {
    fatal("pledge failed");
  }
  do
  {
    (&windows)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&all_window_panes)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&clients)->tqh_first = 0;
    (&clients)->tqh_last = &(&clients)->tqh_first;
  }
  while (0);
  do
  {
    (&sessions)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&session_groups)->rbh_root = 0;
  }
  while (0);
  key_bindings_init();
  gettimeofday(&start_time, 0);
  server_fd = server_create_socket(&cause);
  if (server_fd != (-1))
  {
    server_update_socket();
  }
  c_idx = server_client_create(pair[1]);
  if (lockfd >= 0)
  {
    unlink(lockfile);
    free(lockfile);
    close(lockfd);
  }
  if (cause != 0)
  {
    cmdq_append(c, cmdq_get_callback1("server_start_error", server_start_error, cause));
    c->flags |= 0x4;
  }
  start_cfg();
  server_add_accept(0);
  proc_loop(server_proc, server_loop);
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (job->pid != (-1))
    {
      kill(job->pid, SIGTERM);
    }
  }

  status_prompt_save_history();
  exit(0);
}


----------------------------
***/


static int client_connect(struct event_base *base, const char *path, int start_server)
{
  struct sockaddr_un sa;
  size_t size;
  int fd;
  int lockfd = -1;
  int locked = 0;
  char *lockfile = 0;
  unsigned int lockfile_idx = 0;
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  size = strlcpy(sa.sun_path, path, sizeof(sa.sun_path));
  if (size >= (sizeof(sa.sun_path)))
  {
    errno = ENAMETOOLONG;
    return -1;
  }
  log_debug("socket is %s", path);
  retry:
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
  {
    return -1;
  }

  log_debug("trying connect");
  if (connect(fd, (struct sockaddr *) (&sa), sizeof(sa)) == (-1))
  {
    helper_client_connect_1(&fd, &lockfd, &locked, &lockfile_idx, base, path, start_server, lockfile);
  }
  if (locked && (lockfd >= 0))
  {
    free(lockfile);
    close(lockfd);
  }
  setblocking(fd, 0);
  return fd;
  failed:
  if (locked)
  {
    free(lockfile);
    close(lockfd);
  }

  close(fd);
  return -1;
}


/*** DEPENDENCIES:
int helper_client_connect_1(int * const fd_ref, int * const lockfd_ref, int * const locked_ref, unsigned int * const lockfile_idx_ref, struct event_base * const base, const char * const path, int start_server, char * const lockfile)
{
  int fd = *fd_ref;
  int lockfd = *lockfd_ref;
  int locked = *locked_ref;
  unsigned int lockfile_idx = *lockfile_idx_ref;
  log_debug("connect failed: %s", strerror(errno));
  if ((errno != ECONNREFUSED) && (errno != ENOENT))
  {
    goto failed;
  }
  if (!start_server)
  {
    goto failed;
  }
  close(fd);
  if (!locked)
  {
    xasprintf(&(&lockfile[lockfile_idx]), "%s.lock", path);
    if ((lockfd = client_get_lock(lockfile)) < 0)
    {
      log_debug("didn't get lock (%d)", lockfd);
      free(lockfile);
      lockfile_idx = 0;
      if (lockfd == (-2))
      {
        goto retry;
      }
    }
    log_debug("got lock (%d)", lockfd);
    locked = 1;
    goto retry;
  }
  if (((lockfd >= 0) && (unlink(path) != 0)) && (errno != ENOENT))
  {
    free(lockfile);
    close(lockfd);
    return -1;
  }
  fd = server_start(client_proc, base, lockfd, lockfile);
  *fd_ref = fd;
  *lockfd_ref = lockfd;
  *locked_ref = locked;
  *lockfile_idx_ref = lockfile_idx;
}


----------------------------
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


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


static void client_stdin_callback(int fd, short events, void *arg)
{
  struct msg_stdin_data data;
  data.size = read(STDIN_FILENO, data.data, sizeof(data.data));
  if ((data.size < 0) && ((errno == EINTR) || (errno == EAGAIN)))
  {
    return;
  }
  proc_send(client_peer, MSG_STDIN, -1, &data, sizeof(data));
  if (data.size <= 0)
  {
    event_del(&client_stdin);
  }
}


/*** DEPENDENCIES:
static struct event client_stdin
----------------------------
struct msg_stdin_data
{
  ssize_t size;
  char data[1024];
}
----------------------------
None
----------------------------
***/


const char *client_exit_message(void)
{
  static char msg[256];
  switch (client_exitreason)
  {
    case CLIENT_EXIT_NONE:
    {
      break;
    }

    case CLIENT_EXIT_DETACHED:
    {
      if (client_exitsession != 0)
      {
        xsnprintf(msg, sizeof(msg), "detached (from session %s)", client_exitsession);
        return msg;
      }
      return "detached";
    }

    case CLIENT_EXIT_DETACHED_HUP:
    {
      if (client_exitsession != 0)
      {
        xsnprintf(msg, sizeof(msg), "detached and SIGHUP (from session %s)", client_exitsession);
        return msg;
      }
      return "detached and SIGHUP";
    }

    case CLIENT_EXIT_LOST_TTY:
    {
      return "lost tty";
    }

    case CLIENT_EXIT_TERMINATED:
    {
      return "terminated";
    }

    case CLIENT_EXIT_LOST_SERVER:
    {
      return "lost server";
    }

    case CLIENT_EXIT_EXITED:
    {
      return "exited";
    }

    case CLIENT_EXIT_SERVER_EXITED:
    {
      return "server exited";
    }

  }

  return "unknown reason";
}


/*** DEPENDENCIES:
static const char *client_exitsession
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
static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
----------------------------
***/


static void client_send_identify(const char *ttynam, const char *cwd)
{
  const char *s;
  unsigned int s_idx = 0;
  char **ss;
  unsigned int ss_idx = 0;
  size_t sslen;
  int fd;
  int flags = client_flags;
  pid_t pid;
  proc_send(client_peer, MSG_IDENTIFY_FLAGS, -1, &flags, sizeof(flags));
  if ((s_idx = getenv("TERM")) == 0)
  {
    s_idx = "";
  }
  proc_send(client_peer, MSG_IDENTIFY_TERM, -1, s, strlen(s) + 1);
  proc_send(client_peer, MSG_IDENTIFY_TTYNAME, -1, ttynam, strlen(ttynam) + 1);
  proc_send(client_peer, MSG_IDENTIFY_CWD, -1, cwd, strlen(cwd) + 1);
  if ((fd = dup(STDIN_FILENO)) == (-1))
  {
    fatal("dup failed");
  }
  proc_send(client_peer, MSG_IDENTIFY_STDIN, fd, 0, 0);
  pid = getpid();
  proc_send(client_peer, MSG_IDENTIFY_CLIENTPID, -1, &pid, sizeof(pid));
  for (ss_idx = environ; ss[ss_idx] != 0; ss_idx += 1)
  {
    sslen = strlen(*(&ss[ss_idx])) + 1;
    if (sslen > (16384 - (sizeof(struct imsg_hdr))))
    {
      continue;
    }
    proc_send(client_peer, MSG_IDENTIFY_ENVIRON, -1, *(&ss[ss_idx]), sslen);
  }

  proc_send(client_peer, MSG_IDENTIFY_DONE, -1, 0, 0);
}


/*** DEPENDENCIES:
static int client_flags
----------------------------
None
----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
None
----------------------------
***/


// hint:  ['argc_ref is a mutable refrence to int', 'data_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int', 'size_ref is a mutable refrence to size_t']
int helper_client_main_2(int * const argc_ref, unsigned int * const data_idx_ref, int * const i_ref, size_t * const size_ref, char ** const argv, struct msg_command_data * const data, enum msgtype msg)
{
  int argc = *argc_ref;
  unsigned int data_idx = *data_idx_ref;
  int i = *i_ref;
  size_t size = *size_ref;
  size = 0;
  for (i = 0; i < argc; i += 1)
  {
    size += strlen(argv[i]) + 1;
  }

  if (size > (16384 - (sizeof(*(&data[data_idx])))))
  {
    fprintf(stderr, "command too long\n");
    return 1;
  }
  data_idx = xmalloc((sizeof(*data_idx)) + size);
  data->argc = argc;
  if (cmd_pack_argv(argc, argv, (char *) ((&data[data_idx]) + 1), size) != 0)
  {
    fprintf(stderr, "command too long\n");
    free(data);
    return 1;
  }
  size += sizeof(*(&data[data_idx]));
  if (proc_send(client_peer, msg, -1, data, size) != 0)
  {
    fprintf(stderr, "failed to send command\n");
    free(data);
    return 1;
  }
  free(data);
  *argc_ref = argc;
  *data_idx_ref = data_idx;
  *i_ref = i;
  *size_ref = size;
}


/*** DEPENDENCIES:
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


----------------------------
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
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
struct msg_command_data
{
  int argc;
}
----------------------------
None
----------------------------
***/


static void client_exec(const char *shell, const char *shellcmd)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  char *argv0;
  log_debug("shell %s, command %s", shell, shellcmd);
  ptr_idx = strrchr(shell, '/');
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    name_idx = (&ptr[ptr_idx]) + 1;
  }
  else
    name_idx = shell;
  if (client_flags & 0x2)
  {
    xasprintf(&argv0, "-%s", name);
  }
  else
    xasprintf(&argv0, "%s", name);
  setenv("SHELL", shell, 1);
  proc_clear_signals(client_proc, 1);
  setblocking(STDIN_FILENO, 1);
  setblocking(STDOUT_FILENO, 1);
  setblocking(STDERR_FILENO, 1);
  closefrom(STDERR_FILENO + 1);
  execl(shell, argv0, "-c", shellcmd, (char *) 0);
  fatal("execl failed");
}


/*** DEPENDENCIES:
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
void proc_clear_signals(struct tmuxproc *tp, int defaults)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_del(&tp->ev_sighup);
  signal_del(&tp->ev_sigchld);
  signal_del(&tp->ev_sigcont);
  signal_del(&tp->ev_sigterm);
  signal_del(&tp->ev_sigusr1);
  signal_del(&tp->ev_sigusr2);
  signal_del(&tp->ev_sigwinch);
  if (defaults)
  {
    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGCHLD, &sa, 0);
    sigaction(SIGCONT, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGWINCH, &sa, 0);
  }
}


----------------------------
static int client_flags
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


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


static void client_signal(int sig)
{
  struct sigaction sigact;
  int status;
  if (sig == SIGCHLD)
  {
    waitpid(-1, &status, WNOHANG);
  }
  else
    if (!client_attached)
  {
    if (sig == SIGTERM)
    {
      proc_exit(client_proc);
    }
  }
  else
  {
    switch (sig)
    {
      case SIGHUP:
      {
        client_exitreason = CLIENT_EXIT_LOST_TTY;
        client_exitval = 1;
        proc_send(client_peer, MSG_EXITING, -1, 0, 0);
        break;
      }

      case SIGTERM:
      {
        client_exitreason = CLIENT_EXIT_TERMINATED;
        client_exitval = 1;
        proc_send(client_peer, MSG_EXITING, -1, 0, 0);
        break;
      }

      case SIGWINCH:
      {
        proc_send(client_peer, MSG_RESIZE, -1, 0, 0);
        break;
      }

      case SIGCONT:
      {
        memset(&sigact, 0, sizeof(sigact));
        sigemptyset(&sigact.sa_mask);
        sigact.sa_flags = SA_RESTART;
        sigact.sa_handler = SIG_IGN;
        if (sigaction(SIGTSTP, &sigact, 0) != 0)
        {
          fatal("sigaction failed");
        }
        proc_send(client_peer, MSG_WAKEUP, -1, 0, 0);
        break;
      }

    }

  }
}


/*** DEPENDENCIES:
static int client_exitval
----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
static int client_attached
----------------------------
void proc_exit(struct tmuxproc *tp)
{
  tp->exit = 1;
}


----------------------------
static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
----------------------------
None
----------------------------
***/


static void client_dispatch_attached(struct imsg *imsg)
{
  struct sigaction sigact;
  char *data;
  unsigned int data_idx = 0;
  ssize_t datalen;
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_DETACH:

    case MSG_DETACHKILL:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_DETACH string");
      }
      client_exitsession = xstrdup(data);
      client_exittype = imsg->hdr.type;
      if (imsg->hdr.type == MSG_DETACHKILL)
      {
        client_exitreason = CLIENT_EXIT_DETACHED_HUP;
      }
      else
        client_exitreason = CLIENT_EXIT_DETACHED;
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXEC:
    {
      if (((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0')) || ((strlen(data) + 1) == ((size_t) datalen)))
      {
        fatalx("bad MSG_EXEC string");
      }
      client_execcmd = xstrdup(data);
      client_execshell = xstrdup(((&data[data_idx]) + strlen(data)) + 1);
      client_exittype = imsg->hdr.type;
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXIT:
    {
      if ((datalen != 0) && (datalen != (sizeof(int))))
      {
        fatalx("bad MSG_EXIT size");
      }
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      client_exitreason = CLIENT_EXIT_EXITED;
      break;
    }

    case MSG_EXITED:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_EXITED size");
      }
      proc_exit(client_proc);
      break;
    }

    case MSG_SHUTDOWN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_SHUTDOWN size");
      }
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      client_exitreason = CLIENT_EXIT_SERVER_EXITED;
      client_exitval = 1;
      break;
    }

    case MSG_SUSPEND:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_SUSPEND size");
      }
      memset(&sigact, 0, sizeof(sigact));
      sigemptyset(&sigact.sa_mask);
      sigact.sa_flags = SA_RESTART;
      sigact.sa_handler = SIG_DFL;
      if (sigaction(SIGTSTP, &sigact, 0) != 0)
      {
        fatal("sigaction failed");
      }
      kill(getpid(), SIGTSTP);
      break;
    }

    case MSG_LOCK:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_LOCK string");
      }
      system(data);
      proc_send(client_peer, MSG_UNLOCK, -1, 0, 0);
      break;
    }

  }

}


/*** DEPENDENCIES:
static int client_exitval
----------------------------
static const char *client_exitsession
----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
void fatalx(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s", msg) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
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
static const char *client_execcmd
----------------------------
static enum msgtype client_exittype
----------------------------
void proc_exit(struct tmuxproc *tp)
{
  tp->exit = 1;
}


----------------------------
static const char *client_execshell
----------------------------
static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
----------------------------
None
----------------------------
***/


static void client_dispatch_wait(struct imsg *imsg)
{
  char *data;
  unsigned int data_idx = 0;
  ssize_t datalen;
  struct msg_stdout_data stdoutdata;
  struct msg_stderr_data stderrdata;
  int retval;
  static int pledge_applied;
  if (!pledge_applied)
  {
    if (0 != 0)
    {
      fatal("pledge failed");
    }
    pledge_applied = 1;
  }
  ;
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_EXIT:

    case MSG_SHUTDOWN:
    {
      if ((datalen != (sizeof(retval))) && (datalen != 0))
      {
        fatalx("bad MSG_EXIT size");
      }
      if (datalen == (sizeof(retval)))
      {
        memcpy(&retval, data, sizeof(retval));
        client_exitval = retval;
      }
      proc_exit(client_proc);
      break;
    }

    case MSG_READY:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_READY size");
      }
      event_del(&client_stdin);
      client_attached = 1;
      proc_send(client_peer, MSG_RESIZE, -1, 0, 0);
      break;
    }

    case MSG_STDIN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_STDIN size");
      }
      event_add(&client_stdin, 0);
      break;
    }

    case MSG_STDOUT:
    {
      if (datalen != (sizeof(stdoutdata)))
      {
        fatalx("bad MSG_STDOUT size");
      }
      memcpy(&stdoutdata, data, sizeof(stdoutdata));
      client_write(STDOUT_FILENO, stdoutdata.data, stdoutdata.size);
      break;
    }

    case MSG_STDERR:
    {
      if (datalen != (sizeof(stderrdata)))
      {
        fatalx("bad MSG_STDERR size");
      }
      memcpy(&stderrdata, data, sizeof(stderrdata));
      client_write(STDERR_FILENO, stderrdata.data, stderrdata.size);
      break;
    }

    case MSG_VERSION:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_VERSION size");
      }
      fprintf(stderr, "protocol version mismatch (client %d, server %u)\n", 8, imsg->hdr.peerid & 0xff);
      client_exitval = 1;
      proc_exit(client_proc);
      break;
    }

    case MSG_SHELL:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_SHELL string");
      }
      client_exec(data, shell_command);
    }

    case MSG_DETACH:

    case MSG_DETACHKILL:
    {
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXITED:
    {
      proc_exit(client_proc);
      break;
    }

  }

}


/*** DEPENDENCIES:
static int client_exitval
----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
static int client_attached
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct msg_stdout_data
{
  ssize_t size;
  char data[1024];
}
----------------------------
void fatalx(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s", msg) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
extern const char *shell_command
----------------------------
struct msg_stderr_data
{
  ssize_t size;
  char data[1024];
}
----------------------------
static void client_exec(const char *shell, const char *shellcmd)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  char *argv0;
  log_debug("shell %s, command %s", shell, shellcmd);
  ptr_idx = strrchr(shell, '/');
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    name_idx = (&ptr[ptr_idx]) + 1;
  }
  else
    name_idx = shell;
  if (client_flags & 0x2)
  {
    xasprintf(&argv0, "-%s", name);
  }
  else
    xasprintf(&argv0, "%s", name);
  setenv("SHELL", shell, 1);
  proc_clear_signals(client_proc, 1);
  setblocking(STDIN_FILENO, 1);
  setblocking(STDOUT_FILENO, 1);
  setblocking(STDERR_FILENO, 1);
  closefrom(STDERR_FILENO + 1);
  execl(shell, argv0, "-c", shellcmd, (char *) 0);
  fatal("execl failed");
}


----------------------------
void proc_exit(struct tmuxproc *tp)
{
  tp->exit = 1;
}


----------------------------
static void client_write(int fd, const char *data, size_t size)
{
  unsigned int data_idx = 0;
  ssize_t used;
  log_debug("%s: %.*s", __func__, (int) size, data);
  while (size != 0)
  {
    used = write(fd, data, size);
    if (used == (-1))
    {
      if ((errno == EINTR) || (errno == EAGAIN))
      {
        continue;
      }
      break;
    }
    data_idx += used;
    size -= used;
  }

}


----------------------------
static struct event client_stdin
----------------------------
None
----------------------------
***/


static void client_dispatch(struct imsg *imsg, void *arg)
{
  if (imsg == 0)
  {
    client_exitreason = CLIENT_EXIT_LOST_SERVER;
    client_exitval = 1;
    proc_exit(client_proc);
    return;
  }
  if (client_attached)
  {
    client_dispatch_attached(imsg);
  }
  else
    client_dispatch_wait(imsg);
}


/*** DEPENDENCIES:
static void client_dispatch_attached(struct imsg *imsg)
{
  struct sigaction sigact;
  char *data;
  unsigned int data_idx = 0;
  ssize_t datalen;
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_DETACH:

    case MSG_DETACHKILL:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_DETACH string");
      }
      client_exitsession = xstrdup(data);
      client_exittype = imsg->hdr.type;
      if (imsg->hdr.type == MSG_DETACHKILL)
      {
        client_exitreason = CLIENT_EXIT_DETACHED_HUP;
      }
      else
        client_exitreason = CLIENT_EXIT_DETACHED;
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXEC:
    {
      if (((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0')) || ((strlen(data) + 1) == ((size_t) datalen)))
      {
        fatalx("bad MSG_EXEC string");
      }
      client_execcmd = xstrdup(data);
      client_execshell = xstrdup(((&data[data_idx]) + strlen(data)) + 1);
      client_exittype = imsg->hdr.type;
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXIT:
    {
      if ((datalen != 0) && (datalen != (sizeof(int))))
      {
        fatalx("bad MSG_EXIT size");
      }
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      client_exitreason = CLIENT_EXIT_EXITED;
      break;
    }

    case MSG_EXITED:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_EXITED size");
      }
      proc_exit(client_proc);
      break;
    }

    case MSG_SHUTDOWN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_SHUTDOWN size");
      }
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      client_exitreason = CLIENT_EXIT_SERVER_EXITED;
      client_exitval = 1;
      break;
    }

    case MSG_SUSPEND:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_SUSPEND size");
      }
      memset(&sigact, 0, sizeof(sigact));
      sigemptyset(&sigact.sa_mask);
      sigact.sa_flags = SA_RESTART;
      sigact.sa_handler = SIG_DFL;
      if (sigaction(SIGTSTP, &sigact, 0) != 0)
      {
        fatal("sigaction failed");
      }
      kill(getpid(), SIGTSTP);
      break;
    }

    case MSG_LOCK:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_LOCK string");
      }
      system(data);
      proc_send(client_peer, MSG_UNLOCK, -1, 0, 0);
      break;
    }

  }

}


----------------------------
static int client_exitval
----------------------------
static int client_attached
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
void proc_exit(struct tmuxproc *tp)
{
  tp->exit = 1;
}


----------------------------
static void client_dispatch_wait(struct imsg *imsg)
{
  char *data;
  unsigned int data_idx = 0;
  ssize_t datalen;
  struct msg_stdout_data stdoutdata;
  struct msg_stderr_data stderrdata;
  int retval;
  static int pledge_applied;
  if (!pledge_applied)
  {
    if (0 != 0)
    {
      fatal("pledge failed");
    }
    pledge_applied = 1;
  }
  ;
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_EXIT:

    case MSG_SHUTDOWN:
    {
      if ((datalen != (sizeof(retval))) && (datalen != 0))
      {
        fatalx("bad MSG_EXIT size");
      }
      if (datalen == (sizeof(retval)))
      {
        memcpy(&retval, data, sizeof(retval));
        client_exitval = retval;
      }
      proc_exit(client_proc);
      break;
    }

    case MSG_READY:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_READY size");
      }
      event_del(&client_stdin);
      client_attached = 1;
      proc_send(client_peer, MSG_RESIZE, -1, 0, 0);
      break;
    }

    case MSG_STDIN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_STDIN size");
      }
      event_add(&client_stdin, 0);
      break;
    }

    case MSG_STDOUT:
    {
      if (datalen != (sizeof(stdoutdata)))
      {
        fatalx("bad MSG_STDOUT size");
      }
      memcpy(&stdoutdata, data, sizeof(stdoutdata));
      client_write(STDOUT_FILENO, stdoutdata.data, stdoutdata.size);
      break;
    }

    case MSG_STDERR:
    {
      if (datalen != (sizeof(stderrdata)))
      {
        fatalx("bad MSG_STDERR size");
      }
      memcpy(&stderrdata, data, sizeof(stderrdata));
      client_write(STDERR_FILENO, stderrdata.data, stderrdata.size);
      break;
    }

    case MSG_VERSION:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_VERSION size");
      }
      fprintf(stderr, "protocol version mismatch (client %d, server %u)\n", 8, imsg->hdr.peerid & 0xff);
      client_exitval = 1;
      proc_exit(client_proc);
      break;
    }

    case MSG_SHELL:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_SHELL string");
      }
      client_exec(data, shell_command);
    }

    case MSG_DETACH:

    case MSG_DETACHKILL:
    {
      proc_send(client_peer, MSG_EXITING, -1, 0, 0);
      break;
    }

    case MSG_EXITED:
    {
      proc_exit(client_proc);
      break;
    }

  }

}


----------------------------
static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
----------------------------
***/


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


/*** DEPENDENCIES:
int helper_client_main_2(int * const argc_ref, unsigned int * const data_idx_ref, int * const i_ref, size_t * const size_ref, char ** const argv, struct msg_command_data * const data, enum msgtype msg)
{
  int argc = *argc_ref;
  unsigned int data_idx = *data_idx_ref;
  int i = *i_ref;
  size_t size = *size_ref;
  size = 0;
  for (i = 0; i < argc; i += 1)
  {
    size += strlen(argv[i]) + 1;
  }

  if (size > (16384 - (sizeof(*(&data[data_idx])))))
  {
    fprintf(stderr, "command too long\n");
    return 1;
  }
  data_idx = xmalloc((sizeof(*data_idx)) + size);
  data->argc = argc;
  if (cmd_pack_argv(argc, argv, (char *) ((&data[data_idx]) + 1), size) != 0)
  {
    fprintf(stderr, "command too long\n");
    free(data);
    return 1;
  }
  size += sizeof(*(&data[data_idx]));
  if (proc_send(client_peer, msg, -1, data, size) != 0)
  {
    fprintf(stderr, "failed to send command\n");
    free(data);
    return 1;
  }
  free(data);
  *argc_ref = argc;
  *data_idx_ref = data_idx;
  *i_ref = i;
  *size_ref = size;
}


----------------------------
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
void options_free(struct options *oo)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  for (o_idx = options_tree_RB_MINMAX(&oo->tree, -1); ((&o[o_idx]) != 0) && ((tmp_idx = options_tree_RB_NEXT(o), 1)); o_idx = &tmp[tmp_idx])
  {
    options_remove(o);
  }

  free(oo);
}


----------------------------
None
----------------------------
extern const char *socket_path
----------------------------
static int client_connect(struct event_base *base, const char *path, int start_server)
{
  struct sockaddr_un sa;
  size_t size;
  int fd;
  int lockfd = -1;
  int locked = 0;
  char *lockfile = 0;
  unsigned int lockfile_idx = 0;
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  size = strlcpy(sa.sun_path, path, sizeof(sa.sun_path));
  if (size >= (sizeof(sa.sun_path)))
  {
    errno = ENAMETOOLONG;
    return -1;
  }
  log_debug("socket is %s", path);
  retry:
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
  {
    return -1;
  }

  log_debug("trying connect");
  if (connect(fd, (struct sockaddr *) (&sa), sizeof(sa)) == (-1))
  {
    helper_client_connect_1(&fd, &lockfd, &locked, &lockfile_idx, base, path, start_server, lockfile);
  }
  if (locked && (lockfd >= 0))
  {
    free(lockfile);
    close(lockfd);
  }
  setblocking(fd, 0);
  return fd;
  failed:
  if (locked)
  {
    free(lockfile);
    close(lockfd);
  }

  close(fd);
  return -1;
}


----------------------------
void proc_loop(struct tmuxproc *tp, int (*loopcb)(void))
{
  log_debug("%s loop enter", tp->name);
  do
  {
    event_loop(EVLOOP_ONCE);
  }
  while ((!tp->exit) && ((loopcb == 0) || (!loopcb())));
  log_debug("%s loop exit", tp->name);
}


----------------------------
static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
----------------------------
extern int ptm_fd
----------------------------
static int client_exitval
----------------------------
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


----------------------------
int helper_client_main_1(struct termios * const tio_ref, struct termios saved_tio)
{
  struct termios tio = *tio_ref;
  if (tcgetattr(STDIN_FILENO, &saved_tio) != 0)
  {
    fprintf(stderr, "tcgetattr failed: %s\n", strerror(errno));
    return 1;
  }
  cfmakeraw(&tio);
  tio.c_iflag = ICRNL | IXANY;
  tio.c_oflag = OPOST | ONLCR;
  tio.c_cflag = (CREAD | CS8) | HUPCL;
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  cfsetispeed(&tio, cfgetispeed(&saved_tio));
  cfsetospeed(&tio, cfgetospeed(&saved_tio));
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
  *tio_ref = tio;
}


----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
struct tmuxpeer *proc_add_peer(struct tmuxproc *tp, int fd, void (*dispatchcb)(struct imsg *, void *), void *arg)
{
  struct tmuxpeer *peer;
  unsigned int peer_idx = 0;
  peer_idx = xcalloc(1, sizeof(*peer_idx));
  peer->parent = tp;
  peer->dispatchcb = dispatchcb;
  peer->arg = arg;
  imsg_init(&peer->ibuf, fd);
  event_set(&peer->event, fd, EV_READ, proc_event_cb, peer);
  log_debug("add peer %p: %d (%p)", peer, fd, arg);
  proc_update_event(peer);
  return peer;
}


----------------------------
static void client_send_identify(const char *ttynam, const char *cwd)
{
  const char *s;
  unsigned int s_idx = 0;
  char **ss;
  unsigned int ss_idx = 0;
  size_t sslen;
  int fd;
  int flags = client_flags;
  pid_t pid;
  proc_send(client_peer, MSG_IDENTIFY_FLAGS, -1, &flags, sizeof(flags));
  if ((s_idx = getenv("TERM")) == 0)
  {
    s_idx = "";
  }
  proc_send(client_peer, MSG_IDENTIFY_TERM, -1, s, strlen(s) + 1);
  proc_send(client_peer, MSG_IDENTIFY_TTYNAME, -1, ttynam, strlen(ttynam) + 1);
  proc_send(client_peer, MSG_IDENTIFY_CWD, -1, cwd, strlen(cwd) + 1);
  if ((fd = dup(STDIN_FILENO)) == (-1))
  {
    fatal("dup failed");
  }
  proc_send(client_peer, MSG_IDENTIFY_STDIN, fd, 0, 0);
  pid = getpid();
  proc_send(client_peer, MSG_IDENTIFY_CLIENTPID, -1, &pid, sizeof(pid));
  for (ss_idx = environ; ss[ss_idx] != 0; ss_idx += 1)
  {
    sslen = strlen(*(&ss[ss_idx])) + 1;
    if (sslen > (16384 - (sizeof(struct imsg_hdr))))
    {
      continue;
    }
    proc_send(client_peer, MSG_IDENTIFY_ENVIRON, -1, *(&ss[ss_idx]), sslen);
  }

  proc_send(client_peer, MSG_IDENTIFY_DONE, -1, 0, 0);
}


----------------------------
void proc_set_signals(struct tmuxproc *tp, void (*signalcb)(int))
{
  struct sigaction sa;
  tp->signalcb = signalcb;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_IGN;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_set(&tp->ev_sighup, SIGHUP, proc_signal_cb, tp);
  signal_add(&tp->ev_sighup, 0);
  signal_set(&tp->ev_sigchld, SIGCHLD, proc_signal_cb, tp);
  signal_add(&tp->ev_sigchld, 0);
  signal_set(&tp->ev_sigcont, SIGCONT, proc_signal_cb, tp);
  signal_add(&tp->ev_sigcont, 0);
  signal_set(&tp->ev_sigterm, SIGTERM, proc_signal_cb, tp);
  signal_add(&tp->ev_sigterm, 0);
  signal_set(&tp->ev_sigusr1, SIGUSR1, proc_signal_cb, tp);
  signal_add(&tp->ev_sigusr1, 0);
  signal_set(&tp->ev_sigusr2, SIGUSR2, proc_signal_cb, tp);
  signal_add(&tp->ev_sigusr2, 0);
  signal_set(&tp->ev_sigwinch, SIGWINCH, proc_signal_cb, tp);
  signal_add(&tp->ev_sigwinch, 0);
}


----------------------------
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
}
----------------------------
struct msg_command_data
{
  int argc;
}
----------------------------
static int client_attached
----------------------------
const char *client_exit_message(void)
{
  static char msg[256];
  switch (client_exitreason)
  {
    case CLIENT_EXIT_NONE:
    {
      break;
    }

    case CLIENT_EXIT_DETACHED:
    {
      if (client_exitsession != 0)
      {
        xsnprintf(msg, sizeof(msg), "detached (from session %s)", client_exitsession);
        return msg;
      }
      return "detached";
    }

    case CLIENT_EXIT_DETACHED_HUP:
    {
      if (client_exitsession != 0)
      {
        xsnprintf(msg, sizeof(msg), "detached and SIGHUP (from session %s)", client_exitsession);
        return msg;
      }
      return "detached and SIGHUP";
    }

    case CLIENT_EXIT_LOST_TTY:
    {
      return "lost tty";
    }

    case CLIENT_EXIT_TERMINATED:
    {
      return "terminated";
    }

    case CLIENT_EXIT_LOST_SERVER:
    {
      return "lost server";
    }

    case CLIENT_EXIT_EXITED:
    {
      return "exited";
    }

    case CLIENT_EXIT_SERVER_EXITED:
    {
      return "server exited";
    }

  }

  return "unknown reason";
}


----------------------------
static enum msgtype client_exittype
----------------------------
void environ_free(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct environ_entry *envent1;
  unsigned int envent1_idx = 0;
  for (envent_idx = environ_RB_MINMAX(env, -1); ((&envent[envent_idx]) != 0) && ((envent1_idx = environ_RB_NEXT(envent), 1)); envent_idx = &envent1[envent1_idx])
  {
    environ_RB_REMOVE(env, envent);
    free(envent->name);
    free(envent->value);
    free(envent);
  }

  free(env);
}


----------------------------
static const char *client_execshell
----------------------------
static struct event client_stdin
----------------------------
static const char *client_execcmd
----------------------------
struct tmuxproc *proc_start(const char *name)
{
  struct tmuxproc *tp;
  unsigned int tp_idx = 0;
  struct utsname u;
  log_open(name);
  setproctitle("%s (%s)", name, socket_path);
  if (uname(&u) < 0)
  {
    memset(&u, 0, sizeof(u));
  }
  log_debug("%s started (%ld): version %s, socket %s, protocol %d", name, (long) getpid(), VERSION, socket_path, 8);
  log_debug("on %s %s %s; libevent %s (%s)", u.sysname, u.release, u.version, event_get_version(), event_get_method());
  tp_idx = xcalloc(1, sizeof(*tp_idx));
  tp->name = xstrdup(name);
  return tp;
}


----------------------------
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


----------------------------
static int client_flags
----------------------------
extern const char *shell_command
----------------------------
static void client_dispatch(struct imsg *imsg, void *arg)
{
  if (imsg == 0)
  {
    client_exitreason = CLIENT_EXIT_LOST_SERVER;
    client_exitval = 1;
    proc_exit(client_proc);
    return;
  }
  if (client_attached)
  {
    client_dispatch_attached(imsg);
  }
  else
    client_dispatch_wait(imsg);
}


----------------------------
static void client_stdin_callback(int fd, short events, void *arg)
{
  struct msg_stdin_data data;
  data.size = read(STDIN_FILENO, data.data, sizeof(data.data));
  if ((data.size < 0) && ((errno == EINTR) || (errno == EAGAIN)))
  {
    return;
  }
  proc_send(client_peer, MSG_STDIN, -1, &data, sizeof(data));
  if (data.size <= 0)
  {
    event_del(&client_stdin);
  }
}


----------------------------
static void client_exec(const char *shell, const char *shellcmd)
{
  const char *name;
  unsigned int name_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  char *argv0;
  log_debug("shell %s, command %s", shell, shellcmd);
  ptr_idx = strrchr(shell, '/');
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    name_idx = (&ptr[ptr_idx]) + 1;
  }
  else
    name_idx = shell;
  if (client_flags & 0x2)
  {
    xasprintf(&argv0, "-%s", name);
  }
  else
    xasprintf(&argv0, "%s", name);
  setenv("SHELL", shell, 1);
  proc_clear_signals(client_proc, 1);
  setblocking(STDIN_FILENO, 1);
  setblocking(STDOUT_FILENO, 1);
  setblocking(STDERR_FILENO, 1);
  closefrom(STDERR_FILENO + 1);
  execl(shell, argv0, "-c", shellcmd, (char *) 0);
  fatal("execl failed");
}


----------------------------
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


----------------------------
static void client_signal(int sig)
{
  struct sigaction sigact;
  int status;
  if (sig == SIGCHLD)
  {
    waitpid(-1, &status, WNOHANG);
  }
  else
    if (!client_attached)
  {
    if (sig == SIGTERM)
    {
      proc_exit(client_proc);
    }
  }
  else
  {
    switch (sig)
    {
      case SIGHUP:
      {
        client_exitreason = CLIENT_EXIT_LOST_TTY;
        client_exitval = 1;
        proc_send(client_peer, MSG_EXITING, -1, 0, 0);
        break;
      }

      case SIGTERM:
      {
        client_exitreason = CLIENT_EXIT_TERMINATED;
        client_exitval = 1;
        proc_send(client_peer, MSG_EXITING, -1, 0, 0);
        break;
      }

      case SIGWINCH:
      {
        proc_send(client_peer, MSG_RESIZE, -1, 0, 0);
        break;
      }

      case SIGCONT:
      {
        memset(&sigact, 0, sizeof(sigact));
        sigemptyset(&sigact.sa_mask);
        sigact.sa_flags = SA_RESTART;
        sigact.sa_handler = SIG_IGN;
        if (sigaction(SIGTSTP, &sigact, 0) != 0)
        {
          fatal("sigaction failed");
        }
        proc_send(client_peer, MSG_WAKEUP, -1, 0, 0);
        break;
      }

    }

  }
}


----------------------------
None
----------------------------
***/


