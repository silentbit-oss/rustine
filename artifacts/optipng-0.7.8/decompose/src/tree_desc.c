typedef struct tree_desc_s
{
  ct_data *dyn_tree;
  int max_code;
  const static_tree_desc *stat_desc;
} tree_desc
/*** DEPENDENCIES:
typedef struct static_tree_desc_s static_tree_desc
----------------------------
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
----------------------------
***/


