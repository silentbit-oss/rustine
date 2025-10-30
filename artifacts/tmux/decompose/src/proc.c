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


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
***/


void proc_exit(struct tmuxproc *tp)
{
  tp->exit = 1;
}


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
***/


void proc_kill_peer(struct tmuxpeer *peer)
{
  peer->flags |= 0x1;
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
***/


static void proc_signal_cb(int signo, short events, void *arg)
{
  struct tmuxproc *tp = arg;
  tp->signalcb(signo);
}


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
***/


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


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
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


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
static void proc_signal_cb(int signo, short events, void *arg)
{
  struct tmuxproc *tp = arg;
  tp->signalcb(signo);
}


----------------------------
***/


void proc_toggle_log(struct tmuxproc *tp)
{
  log_toggle(tp->name);
}


/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
void log_toggle(const char *name)
{
  if (log_level == 0)
  {
    log_level = 1;
    log_open(name);
    log_debug("log opened");
  }
  else
  {
    log_debug("log closed");
    log_level = 0;
    log_close();
  }
}


----------------------------
***/


void proc_remove_peer(struct tmuxpeer *peer)
{
  log_debug("remove peer %p", peer);
  event_del(&peer->event);
  imsg_clear(&peer->ibuf);
  close(peer->ibuf.fd);
  free(peer);
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
void imsg_clear(struct imsgbuf *ibuf)
{
  int fd;
  msgbuf_clear(&ibuf->w);
  while ((fd = imsg_get_fd(ibuf)) != (-1))
  {
    close(fd);
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


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
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
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
void imsg_init(struct imsgbuf *ibuf, int fd)
{
  msgbuf_init(&ibuf->w);
  memset(&ibuf->r, 0, sizeof(ibuf->r));
  ibuf->fd = fd;
  ibuf->w.fd = fd;
  ibuf->pid = getpid();
  do
  {
    (&ibuf->fds)->tqh_first = 0;
    (&ibuf->fds)->tqh_last = &(&ibuf->fds)->tqh_first;
  }
  while (0);
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
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


/*** DEPENDENCIES:
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
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
void log_open(const char *name)
{
  char *path;
  if (log_level == 0)
  {
    return;
  }
  log_close();
  xasprintf(&path, "tmux-%s-%ld.log", name, (long) getpid());
  log_file = fopen(path, "a");
  free(path);
  if (log_file == 0)
  {
    return;
  }
  setvbuf(log_file, 0, _IOLBF, 0);
  event_set_log_callback(log_event_cb);
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
extern const char *socket_path
----------------------------
void setproctitle(const char *fmt, ...)
{
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


