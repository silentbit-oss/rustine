// element in merge of:  mi_segment_t,mi_subproc_s,mi_subproc_t
struct mi_subproc_s
{
  _Atomic size_t abandoned_count;
  _Atomic size_t abandoned_os_list_count;
  pthread_mutex_t abandoned_os_lock;
  pthread_mutex_t abandoned_os_visit_lock;
  mi_segment_t *abandoned_os_list;
  mi_segment_t *abandoned_os_list_tail;
  mi_memid_t memid;
}
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


// element in merge of:  mi_segment_t,mi_subproc_s,mi_subproc_t
typedef struct mi_subproc_s mi_subproc_t
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mi_segment_t,mi_subproc_s,mi_subproc_t
typedef struct mi_segment_s
{
  mi_memid_t memid;
  bool allow_decommit;
  bool allow_purge;
  size_t segment_size;
  mi_subproc_t *subproc;
  mi_msecs_t purge_expire;
  mi_commit_mask_t purge_mask;
  mi_commit_mask_t commit_mask;
  struct mi_segment_s *next;
  bool was_reclaimed;
  bool dont_free;
  size_t abandoned;
  size_t abandoned_visits;
  size_t used;
  uintptr_t cookie;
  struct mi_segment_s *abandoned_os_next;
  struct mi_segment_s *abandoned_os_prev;
  size_t segment_slices;
  size_t segment_info_slices;
  mi_segment_kind_t kind;
  size_t slice_entries;
  _Atomic mi_threadid_t thread_id;
  mi_slice_t slices[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) + 1];
} mi_segment_t
/*** DEPENDENCIES:
typedef int64_t mi_msecs_t
----------------------------
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t
----------------------------
typedef mi_page_t mi_slice_t
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
typedef enum mi_segment_kind_e
{
  MI_SEGMENT_NORMAL,
  MI_SEGMENT_HUGE
} mi_segment_kind_t
----------------------------
typedef size_t mi_threadid_t
----------------------------
None
----------------------------
***/


