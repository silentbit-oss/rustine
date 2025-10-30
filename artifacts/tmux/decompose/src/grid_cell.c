struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
***/


