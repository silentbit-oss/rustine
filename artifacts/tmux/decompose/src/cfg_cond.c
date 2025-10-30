struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
/*** DEPENDENCIES:
***/


