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
/*** DEPENDENCIES:
***/


