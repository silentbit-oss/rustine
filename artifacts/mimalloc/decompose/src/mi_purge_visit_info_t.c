typedef struct mi_purge_visit_info_s
{
  mi_msecs_t now;
  mi_msecs_t delay;
  bool all_purged;
  bool any_purged;
} mi_purge_visit_info_t
/*** DEPENDENCIES:
typedef int64_t mi_msecs_t
----------------------------
***/


