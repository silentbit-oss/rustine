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
/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


