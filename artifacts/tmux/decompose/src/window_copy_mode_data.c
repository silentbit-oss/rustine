struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
/*** DEPENDENCIES:
typedef unsigned char bitstr_t
----------------------------
None
----------------------------
***/


