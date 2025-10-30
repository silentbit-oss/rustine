typedef struct mi_arena_s
{
  mi_arena_id_t id;
  mi_memid_t memid;
  uint8_t * _Atomic start;
  size_t block_count;
  size_t field_count;
  size_t meta_size;
  mi_memid_t meta_memid;
  int numa_node;
  bool exclusive;
  bool is_large;
  pthread_mutex_t abandoned_visit_lock;
  _Atomic size_t search_idx;
  _Atomic mi_msecs_t purge_expire;
  mi_bitmap_field_t *blocks_dirty;
  mi_bitmap_field_t *blocks_committed;
  mi_bitmap_field_t *blocks_purge;
  mi_bitmap_field_t *blocks_abandoned;
  mi_bitmap_field_t blocks_inuse[1];
} mi_arena_t
/*** DEPENDENCIES:
typedef int mi_arena_id_t
----------------------------
typedef _Atomic size_t mi_bitmap_field_t
----------------------------
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t
----------------------------
typedef int64_t mi_msecs_t
----------------------------
***/


