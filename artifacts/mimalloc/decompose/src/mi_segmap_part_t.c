typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
/*** DEPENDENCIES:
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
***/


