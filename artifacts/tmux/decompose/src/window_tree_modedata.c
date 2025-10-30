struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
/*** DEPENDENCIES:
struct mode_tree_data
{
  int dead;
  u_int references;
  int zoomed;
  struct window_pane *wp;
  void *modedata;
  const char **sort_list;
  u_int sort_size;
  u_int sort_type;
  mode_tree_build_cb buildcb;
  mode_tree_draw_cb drawcb;
  mode_tree_search_cb searchcb;
  struct mode_tree_list children;
  struct mode_tree_list saved;
  struct mode_tree_line *line_list;
  u_int line_size;
  u_int depth;
  u_int width;
  u_int height;
  u_int offset;
  u_int current;
  struct screen screen;
  int preview;
  char *search;
  char *filter;
  int no_matches;
}
----------------------------
enum window_tree_type
{
  WINDOW_TREE_NONE,
  WINDOW_TREE_SESSION,
  WINDOW_TREE_WINDOW,
  WINDOW_TREE_PANE
}
----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
None
----------------------------
***/


