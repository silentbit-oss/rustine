struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


