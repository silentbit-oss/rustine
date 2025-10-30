void xalloc_die(void)
{
  error(exit_failure, 0, "%s", gettext("memory exhausted"));
  abort();
}


/*** DEPENDENCIES:
extern volatile int exit_failure
----------------------------
***/


