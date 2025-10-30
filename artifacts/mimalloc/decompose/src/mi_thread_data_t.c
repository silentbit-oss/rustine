typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
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
None
----------------------------
***/


