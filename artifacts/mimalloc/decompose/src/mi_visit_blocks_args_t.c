typedef struct mi_visit_blocks_args_s
{
  bool visit_blocks;
  mi_block_visit_fun *visitor;
  void *arg;
} mi_visit_blocks_args_t
/*** DEPENDENCIES:
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
***/


