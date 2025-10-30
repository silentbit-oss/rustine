struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
/*** DEPENDENCIES:
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
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
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


