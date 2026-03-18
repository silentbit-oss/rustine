typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t
/*** DEPENDENCIES:
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
***/


