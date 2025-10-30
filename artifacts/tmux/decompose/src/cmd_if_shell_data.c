struct cmd_if_shell_data
{
  char *file;
  u_int line;
  char *cmd_if;
  char *cmd_else;
  struct client *client;
  struct cmdq_item *item;
  struct mouse_event mouse;
}
/*** DEPENDENCIES:
struct mouse_event
{
  int valid;
  key_code key;
  int statusat;
  u_int x;
  u_int y;
  u_int b;
  u_int lx;
  u_int ly;
  u_int lb;
  int s;
  int w;
  int wp;
  u_int sgr_type;
  u_int sgr_b;
}
----------------------------
None
----------------------------
***/


