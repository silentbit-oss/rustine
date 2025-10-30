struct screen_write_collect_line
{
  struct 
  {
    struct screen_write_collect_item *tqh_first;
    struct screen_write_collect_item **tqh_last;
  } items;
}
/*** DEPENDENCIES:
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
None
----------------------------
***/


