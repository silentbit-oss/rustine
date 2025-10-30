typedef struct mi_arena_field_cursor_s
{
  size_t os_list_count;
  size_t start;
  size_t end;
  size_t bitmap_idx;
  mi_subproc_t *subproc;
  bool visit_all;
  bool hold_visit_lock;
} mi_arena_field_cursor_t
/*** DEPENDENCIES:
None
----------------------------
***/


