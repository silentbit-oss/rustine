struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
None
----------------------------
***/


