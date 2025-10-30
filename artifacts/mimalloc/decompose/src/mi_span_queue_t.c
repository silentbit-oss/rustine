typedef struct mi_span_queue_s
{
  mi_slice_t *first;
  mi_slice_t *last;
  size_t slice_count;
} mi_span_queue_t
/*** DEPENDENCIES:
typedef mi_page_t mi_slice_t
----------------------------
***/


