struct static_tree_desc_s
{
  const ct_data *static_tree;
  const intf *extra_bits;
  int extra_base;
  int elems;
  int max_length;
}
/*** DEPENDENCIES:
typedef int intf
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


