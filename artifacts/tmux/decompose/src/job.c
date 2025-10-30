struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
/*** DEPENDENCIES:
typedef void (*job_complete_cb)(struct job *)
----------------------------
typedef void (*job_update_cb)(struct job *)
----------------------------
typedef void (*job_free_cb)(void *)
----------------------------
***/


void job_free(struct job *job)
{
  log_debug("free job %p: %s", job, job->cmd);
  do
  {
    if (job->entry.le_next != 0)
    {
      job->entry.le_next->entry.le_prev = job->entry.le_prev;
    }
    *job->entry.le_prev = job->entry.le_next;
    ;
    ;
  }
  while (0);
  free(job->cmd);
  if ((job->freecb != 0) && (job->data != 0))
  {
    job->freecb(job->data);
  }
  if (job->pid != (-1))
  {
    kill(job->pid, SIGTERM);
  }
  if (job->event != 0)
  {
    bufferevent_free(job->event);
  }
  if (job->fd != (-1))
  {
    close(job->fd);
  }
  free(job);
}


/*** DEPENDENCIES:
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
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


static void job_read_callback(struct bufferevent *bufev, void *data)
{
  struct job *job = data;
  if (job->updatecb != 0)
  {
    job->updatecb(job);
  }
}


/*** DEPENDENCIES:
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
----------------------------
***/


static void job_write_callback(struct bufferevent *bufev, void *data)
{
  struct job *job = data;
  size_t len = EVBUFFER_LENGTH(EVBUFFER_OUTPUT(job->event));
  log_debug("job write %p: %s, pid %ld, output left %zu", job, job->cmd, (long) job->pid, len);
  if (len == 0)
  {
    shutdown(job->fd, SHUT_WR);
    bufferevent_disable(job->event, EV_WRITE);
  }
}


/*** DEPENDENCIES:
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
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


static void job_error_callback(struct bufferevent *bufev, short events, void *data)
{
  struct job *job = data;
  log_debug("job error %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  if (job->state == JOB_DEAD)
  {
    if (job->completecb != 0)
    {
      job->completecb(job);
    }
    job_free(job);
  }
  else
  {
    bufferevent_disable(job->event, EV_READ);
    job->state = JOB_CLOSED;
  }
}


/*** DEPENDENCIES:
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
----------------------------
void job_free(struct job *job)
{
  log_debug("free job %p: %s", job, job->cmd);
  do
  {
    if (job->entry.le_next != 0)
    {
      job->entry.le_next->entry.le_prev = job->entry.le_prev;
    }
    *job->entry.le_prev = job->entry.le_next;
    ;
    ;
  }
  while (0);
  free(job->cmd);
  if ((job->freecb != 0) && (job->data != 0))
  {
    job->freecb(job->data);
  }
  if (job->pid != (-1))
  {
    kill(job->pid, SIGTERM);
  }
  if (job->event != 0)
  {
    bufferevent_free(job->event);
  }
  if (job->fd != (-1))
  {
    close(job->fd);
  }
  free(job);
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


// hint:  ['nullfd_ref is a mutable refrence to int', 'home_idx_ref is a mutable refrence to unsigned int']
void helper_job_run_1(int * const nullfd_ref, unsigned int * const home_idx_ref, const char * const cmd, const char * const cwd, struct environ * const env, int out[2], const char * const home, sigset_t oldset)
{
  int nullfd = *nullfd_ref;
  unsigned int home_idx = *home_idx_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  if ((cwd == 0) || (chdir(cwd) != 0))
  {
    if (((home_idx = find_home()) == 0) || (chdir(home) != 0))
    {
      chdir("/");
    }
  }
  environ_push(env);
  environ_free(env);
  if (dup2(out[1], STDIN_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if (dup2(out[1], STDOUT_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if ((out[1] != STDIN_FILENO) && (out[1] != STDOUT_FILENO))
  {
    close(out[1]);
  }
  close(out[0]);
  nullfd = open("/dev/null", O_RDWR, 0);
  if (nullfd < 0)
  {
    fatal("open failed");
  }
  if (dup2(nullfd, STDERR_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if (nullfd != STDERR_FILENO)
  {
    close(nullfd);
  }
  closefrom(STDERR_FILENO + 1);
  execl("/bin/sh", "sh", "-c", cmd, (char *) 0);
  fatal("execl failed");
  *nullfd_ref = nullfd;
  *home_idx_ref = home_idx;
}


/*** DEPENDENCIES:
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
void environ_push(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  environ = xcalloc(1, sizeof(*environ));
  for (envent_idx = environ_RB_MINMAX(env, -1); (&envent[envent_idx]) != 0; envent_idx = environ_RB_NEXT(envent_idx))
  {
    if ((envent->value != 0) && ((*envent->name) != '\0'))
    {
      setenv(envent->name, envent->value, 1);
    }
  }

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
None
----------------------------
***/


struct job *job_run(const char *cmd, struct session *s, const char *cwd, job_update_cb updatecb, job_complete_cb completecb, job_free_cb freecb, void *data, int flags)
{
  struct job *job;
  unsigned int job_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  pid_t pid;
  int nullfd;
  int out[2];
  const char *home;
  unsigned int home_idx = 0;
  sigset_t set;
  sigset_t oldset;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, out) != 0)
  {
    return 0;
  }
  env_idx = environ_for_session(s, !cfg_finished);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (pid = fork())
  {
    case -1:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      environ_free(env);
      close(out[0]);
      close(out[1]);
      return 0;
    }

    case 0:
    {
      helper_job_run_1(&nullfd, &home_idx, cmd, cwd, env, out, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  environ_free(env);
  close(out[1]);
  job_idx = xmalloc(sizeof(*job_idx));
  job->state = JOB_RUNNING;
  job->flags = flags;
  job->cmd = xstrdup(cmd);
  job->pid = pid;
  job->status = 0;
  do
  {
    if ((job->entry.le_next = (&all_jobs)->lh_first) != 0)
    {
      (&all_jobs)->lh_first->entry.le_prev = &job->entry.le_next;
    }
    (&all_jobs)->lh_first = &job[job_idx];
    job->entry.le_prev = &(&all_jobs)->lh_first;
  }
  while (0);
  job->updatecb = updatecb;
  job->completecb = completecb;
  job->freecb = freecb;
  job->data = data;
  job->fd = out[0];
  setblocking(job->fd, 0);
  job->event = bufferevent_new(job->fd, job_read_callback, job_write_callback, job_error_callback, job);
  bufferevent_enable(job->event, EV_READ | EV_WRITE);
  log_debug("run job %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  return job;
}


/*** DEPENDENCIES:
typedef void (*job_update_cb)(struct job *)
----------------------------
static void job_read_callback(struct bufferevent *bufev, void *data)
{
  struct job *job = data;
  if (job->updatecb != 0)
  {
    job->updatecb(job);
  }
}


----------------------------
typedef void (*job_free_cb)(void *)
----------------------------
extern int cfg_finished
----------------------------
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
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
None
----------------------------
static void job_write_callback(struct bufferevent *bufev, void *data)
{
  struct job *job = data;
  size_t len = EVBUFFER_LENGTH(EVBUFFER_OUTPUT(job->event));
  log_debug("job write %p: %s, pid %ld, output left %zu", job, job->cmd, (long) job->pid, len);
  if (len == 0)
  {
    shutdown(job->fd, SHUT_WR);
    bufferevent_disable(job->event, EV_WRITE);
  }
}


----------------------------
static void job_error_callback(struct bufferevent *bufev, short events, void *data)
{
  struct job *job = data;
  log_debug("job error %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  if (job->state == JOB_DEAD)
  {
    if (job->completecb != 0)
    {
      job->completecb(job);
    }
    job_free(job);
  }
  else
  {
    bufferevent_disable(job->event, EV_READ);
    job->state = JOB_CLOSED;
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
typedef void (*job_complete_cb)(struct job *)
----------------------------
struct environ *environ_for_session(struct session *s, int no_TERM)
{
  struct environ *env;
  unsigned int env_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  int idx;
  env_idx = environ_create();
  environ_copy(global_environ, env);
  if (s != 0)
  {
    environ_copy(s->environ, env);
  }
  if (!no_TERM)
  {
    value_idx = options_get_string(global_options, "default-terminal");
    environ_set(env, "TERM", "%s", value);
  }
  if (s != 0)
  {
    idx = s->id;
  }
  else
    idx = -1;
  environ_set(env, "TMUX", "%s,%ld,%d", socket_path, (long) getpid(), idx);
  return env;
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
void helper_job_run_1(int * const nullfd_ref, unsigned int * const home_idx_ref, const char * const cmd, const char * const cwd, struct environ * const env, int out[2], const char * const home, sigset_t oldset)
{
  int nullfd = *nullfd_ref;
  unsigned int home_idx = *home_idx_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  if ((cwd == 0) || (chdir(cwd) != 0))
  {
    if (((home_idx = find_home()) == 0) || (chdir(home) != 0))
    {
      chdir("/");
    }
  }
  environ_push(env);
  environ_free(env);
  if (dup2(out[1], STDIN_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if (dup2(out[1], STDOUT_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if ((out[1] != STDIN_FILENO) && (out[1] != STDOUT_FILENO))
  {
    close(out[1]);
  }
  close(out[0]);
  nullfd = open("/dev/null", O_RDWR, 0);
  if (nullfd < 0)
  {
    fatal("open failed");
  }
  if (dup2(nullfd, STDERR_FILENO) == (-1))
  {
    fatal("dup2 failed");
  }
  if (nullfd != STDERR_FILENO)
  {
    close(nullfd);
  }
  closefrom(STDERR_FILENO + 1);
  execl("/bin/sh", "sh", "-c", cmd, (char *) 0);
  fatal("execl failed");
  *nullfd_ref = nullfd;
  *home_idx_ref = home_idx;
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
extern struct joblist all_jobs
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
None
----------------------------
***/


void job_died(struct job *job, int status)
{
  log_debug("job died %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  job->status = status;
  if (job->state == JOB_CLOSED)
  {
    if (job->completecb != 0)
    {
      job->completecb(job);
    }
    job_free(job);
  }
  else
  {
    job->pid = -1;
    job->state = JOB_DEAD;
  }
}


/*** DEPENDENCIES:
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
----------------------------
void job_free(struct job *job)
{
  log_debug("free job %p: %s", job, job->cmd);
  do
  {
    if (job->entry.le_next != 0)
    {
      job->entry.le_next->entry.le_prev = job->entry.le_prev;
    }
    *job->entry.le_prev = job->entry.le_next;
    ;
    ;
  }
  while (0);
  free(job->cmd);
  if ((job->freecb != 0) && (job->data != 0))
  {
    job->freecb(job->data);
  }
  if (job->pid != (-1))
  {
    kill(job->pid, SIGTERM);
  }
  if (job->event != 0)
  {
    bufferevent_free(job->event);
  }
  if (job->fd != (-1))
  {
    close(job->fd);
  }
  free(job);
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


