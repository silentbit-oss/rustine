struct hashcell_t
{
  struct hashentry_t *e;
  size_t c;
}
/*** DEPENDENCIES:
struct hashentry_t
{
  char *k;
  void *v;
}
----------------------------
***/


