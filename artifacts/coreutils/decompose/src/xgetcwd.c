char *xgetcwd(void)
{
  char *cwd = getcwd(0, 0);
  if ((!cwd) && (errno == ENOMEM))
  {
    xalloc_die();
  }
  return cwd;
}


/*** DEPENDENCIES:
void xalloc_die(void)
{
  error(exit_failure, 0, "%s", gettext("memory exhausted"));
  abort();
}


----------------------------
***/


