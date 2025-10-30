typedef struct mi_memid_arena_info
{
  size_t block_index;
  mi_arena_id_t id;
  bool is_exclusive;
} mi_memid_arena_info_t
/*** DEPENDENCIES:
typedef int mi_arena_id_t
----------------------------
***/


