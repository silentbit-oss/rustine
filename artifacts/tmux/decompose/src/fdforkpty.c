int getptmfd(void)
{
  return 2147483647;
}


/*** DEPENDENCIES:
***/


pid_t fdforkpty(int ptmfd, int *master, char *name, struct termios *tio, struct winsize *ws)
{
  return forkpty(master, name, tio, ws);
}


/*** DEPENDENCIES:
***/


