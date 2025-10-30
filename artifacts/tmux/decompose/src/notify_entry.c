struct notify_entry
{
  const char *name;
  struct client *client;
  struct session *session;
  struct window *window;
  int pane;
  struct cmd_find_state fs;
}
/*** DEPENDENCIES:
None
----------------------------
***/


