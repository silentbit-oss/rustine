// element in merge of:  screen_title_entry,screen_titles,screen
struct screen_title_entry
{
  char *text;
  struct 
  {
    struct screen_title_entry *tqe_next;
    struct screen_title_entry **tqe_prev;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  screen_title_entry,screen_titles,screen
struct screen_titles
{
  struct screen_title_entry *tqh_first;
  struct screen_title_entry **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  screen_title_entry,screen_titles,screen
struct screen
{
  char *title;
  struct screen_titles *titles;
  struct grid *grid;
  u_int cx;
  u_int cy;
  u_int cstyle;
  char *ccolour;
  u_int rupper;
  u_int rlower;
  int mode;
  bitstr_t *tabs;
  struct screen_sel sel;
}
/*** DEPENDENCIES:
typedef unsigned char bitstr_t
----------------------------
None
----------------------------
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


