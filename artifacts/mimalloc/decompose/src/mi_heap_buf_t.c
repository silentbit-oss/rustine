typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
/*** DEPENDENCIES:
***/


