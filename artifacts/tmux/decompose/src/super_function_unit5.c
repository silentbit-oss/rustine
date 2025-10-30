// element in merge of:  mode_tree_free_items,mode_tree_free_item
static void mode_tree_free_items(struct mode_tree_list *mtl)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *mti1;
  unsigned int mti1_idx = 0;
  for (mti_idx = mtl->tqh_first; ((&mti[mti_idx]) != 0) && ((mti1_idx = mti->entry.tqe_next, 1)); mti_idx = &mti1[mti1_idx])
  {
    do
    {
      if (mti->entry.tqe_next != 0)
      {
        mti->entry.tqe_next->entry.tqe_prev = mti->entry.tqe_prev;
      }
      else
        mtl->tqh_last = mti->entry.tqe_prev;
      *mti->entry.tqe_prev = mti->entry.tqe_next;
      ;
      ;
    }
    while (0);
    mode_tree_free_item(mti);
  }

}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  mode_tree_free_items,mode_tree_free_item
static void mode_tree_free_item(struct mode_tree_item *mti)
{
  mode_tree_free_items(&mti->children);
  free((void *) mti->name);
  free((void *) mti->text);
  free(mti);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


