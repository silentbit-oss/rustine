typedef struct mi_heap_area_ex_s
{
  mi_heap_area_t area;
  mi_page_t *page;
} mi_heap_area_ex_t
/*** DEPENDENCIES:
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t
----------------------------
None
----------------------------
***/


