struct input_cell
{
  struct grid_cell cell;
  int set;
  int g0set;
  int g1set;
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
***/


