struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
----------------------------
***/


