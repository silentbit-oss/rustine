struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
/*** DEPENDENCIES:
enum window_tree_type
{
  WINDOW_TREE_NONE,
  WINDOW_TREE_SESSION,
  WINDOW_TREE_WINDOW,
  WINDOW_TREE_PANE
}
----------------------------
None
----------------------------
***/


