int mi_version(void)
{
  return 316;
}


/*** DEPENDENCIES:
***/


static void mi_error_default(int err)
{
  (void) err;
  if (err == 14)
  {
    abort();
  }
}


/*** DEPENDENCIES:
***/


static void mi_recurse_exit_prim(void)
{
  recurse = 0;
}


/*** DEPENDENCIES:
static bool recurse = 0
----------------------------
***/


static void mi_recurse_exit(void)
{
  mi_recurse_exit_prim();
}


/*** DEPENDENCIES:
static void mi_recurse_exit_prim(void)
{
  recurse = 0;
}


----------------------------
***/


static bool mi_recurse_enter_prim(void)
{
  if (recurse)
  {
    return 0;
  }
  recurse = 1;
  return 1;
}


/*** DEPENDENCIES:
static bool recurse = 0
----------------------------
***/


static bool mi_recurse_enter(void)
{
  return mi_recurse_enter_prim();
}


/*** DEPENDENCIES:
static bool mi_recurse_enter_prim(void)
{
  if (recurse)
  {
    return 0;
  }
  recurse = 1;
  return 1;
}


----------------------------
***/


static bool mi_option_has_size_in_kib(mi_option_t option)
{
  return (option == mi_option_reserve_os_memory) || (option == mi_option_arena_reserve);
}


/*** DEPENDENCIES:
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
***/


long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 249, __func__));
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 251, __func__));
  return desc->value;
}


/*** DEPENDENCIES:
static mi_option_desc_t mi_options[_mi_option_last] = {{1, MI_OPTION_UNINIT, mi_option_show_errors, "show_errors", 0}, {0, MI_OPTION_UNINIT, mi_option_show_stats, "show_stats", 0}, {0, MI_OPTION_UNINIT, mi_option_verbose, "verbose", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, MI_OPTION_UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, MI_OPTION_UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, MI_OPTION_UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, MI_OPTION_UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, MI_OPTION_UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {1000, MI_OPTION_UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, MI_OPTION_UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, MI_OPTION_UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, MI_OPTION_UNINIT, mi_option_os_tag, "os_tag", 0}, {32, MI_OPTION_UNINIT, mi_option_max_errors, "max_errors", 0}, {32, MI_OPTION_UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, MI_OPTION_UNINIT, mi_option_deprecated_max_segment_reclaim, "deprecated_max_segment_reclaim", 0}, {0, MI_OPTION_UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, MI_OPTION_UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {1, MI_OPTION_UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, MI_OPTION_UNINIT, mi_option_deprecated_purge_extend_delay, "deprecated_purge_extend_delay", "decommit_extend_delay"}, {0, MI_OPTION_UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, MI_OPTION_UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, MI_OPTION_UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, MI_OPTION_UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {10000, MI_OPTION_UNINIT, mi_option_generic_collect, "generic_collect", 0}, {0, MI_OPTION_UNINIT, mi_option_page_reclaim_on_free, "page_reclaim_on_free", "abandoned_reclaim_on_free"}, {2, MI_OPTION_UNINIT, mi_option_page_full_retain, "page_full_retain", 0}, {4, MI_OPTION_UNINIT, mi_option_page_max_candidates, "page_max_candidates", 0}, {0, MI_OPTION_UNINIT, mi_option_max_vabits, "max_vabits", 0}, {0, MI_OPTION_UNINIT, mi_option_pagemap_commit, "pagemap_commit", 0}, {0, MI_OPTION_UNINIT, mi_option_page_commit_on_demand, "page_commit_on_demand", 0}, {-1, MI_OPTION_UNINIT, mi_option_page_max_reclaim, "page_max_reclaim", 0}, {32, MI_OPTION_UNINIT, mi_option_page_cross_thread_max_reclaim, "page_cross_thread_max_reclaim", 0}}
----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
None
----------------------------
***/


void mi_option_set(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 283, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 286, __func__));
  desc->value = value;
  desc->init = MI_OPTION_INITIALIZED;
  if ((desc->option == mi_option_guarded_min) && (_mi_option_get_fast(mi_option_guarded_max) < value))
  {
    mi_option_set(mi_option_guarded_max, value);
  }
  else
    if ((desc->option == mi_option_guarded_max) && (_mi_option_get_fast(mi_option_guarded_min) > value))
  {
    mi_option_set(mi_option_guarded_min, value);
  }
}


/*** DEPENDENCIES:
long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 249, __func__));
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 251, __func__));
  return desc->value;
}


----------------------------
static mi_option_desc_t mi_options[_mi_option_last] = {{1, MI_OPTION_UNINIT, mi_option_show_errors, "show_errors", 0}, {0, MI_OPTION_UNINIT, mi_option_show_stats, "show_stats", 0}, {0, MI_OPTION_UNINIT, mi_option_verbose, "verbose", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, MI_OPTION_UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, MI_OPTION_UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, MI_OPTION_UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, MI_OPTION_UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, MI_OPTION_UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {1000, MI_OPTION_UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, MI_OPTION_UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, MI_OPTION_UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, MI_OPTION_UNINIT, mi_option_os_tag, "os_tag", 0}, {32, MI_OPTION_UNINIT, mi_option_max_errors, "max_errors", 0}, {32, MI_OPTION_UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, MI_OPTION_UNINIT, mi_option_deprecated_max_segment_reclaim, "deprecated_max_segment_reclaim", 0}, {0, MI_OPTION_UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, MI_OPTION_UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {1, MI_OPTION_UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, MI_OPTION_UNINIT, mi_option_deprecated_purge_extend_delay, "deprecated_purge_extend_delay", "decommit_extend_delay"}, {0, MI_OPTION_UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, MI_OPTION_UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, MI_OPTION_UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, MI_OPTION_UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {10000, MI_OPTION_UNINIT, mi_option_generic_collect, "generic_collect", 0}, {0, MI_OPTION_UNINIT, mi_option_page_reclaim_on_free, "page_reclaim_on_free", "abandoned_reclaim_on_free"}, {2, MI_OPTION_UNINIT, mi_option_page_full_retain, "page_full_retain", 0}, {4, MI_OPTION_UNINIT, mi_option_page_max_candidates, "page_max_candidates", 0}, {0, MI_OPTION_UNINIT, mi_option_max_vabits, "max_vabits", 0}, {0, MI_OPTION_UNINIT, mi_option_pagemap_commit, "pagemap_commit", 0}, {0, MI_OPTION_UNINIT, mi_option_page_commit_on_demand, "page_commit_on_demand", 0}, {-1, MI_OPTION_UNINIT, mi_option_page_max_reclaim, "page_max_reclaim", 0}, {32, MI_OPTION_UNINIT, mi_option_page_cross_thread_max_reclaim, "page_cross_thread_max_reclaim", 0}}
----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
None
----------------------------
***/


static void mi_vfprintf_thread(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  if (((prefix != 0) && (_mi_strnlen(prefix, 33) <= 32)) && (!_mi_is_main_thread()))
  {
    char tprefix[64];
    _mi_snprintf(tprefix, sizeof(tprefix), "%sthread 0x%tx: ", prefix, (uintptr_t) _mi_thread_id());
    mi_vfprintf(out, arg, tprefix, fmt, args);
  }
  else
  {
    mi_vfprintf(out, arg, prefix, fmt, args);
  }
}


/*** DEPENDENCIES:
size_t _mi_strnlen(const char *s, size_t max_len)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while ((s[len] != 0) && (len < max_len))
  {
    len += 1;
  }

  return len;
}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
}


----------------------------
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_show_error_message(const char *fmt, va_list args)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    if (!mi_option_is_enabled(mi_option_show_errors))
    {
      return;
    }
    if ((mi_max_error_count >= 0) && (((long) atomic_fetch_add_explicit(&error_count, (uintptr_t) 1, memory_order_acq_rel)) > mi_max_error_count))
    {
      return;
    }
  }
  mi_vfprintf_thread(0, 0, "mimalloc: error: ", fmt, args);
}


/*** DEPENDENCIES:
static long mi_max_error_count = 16
----------------------------
static void mi_vfprintf_thread(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  if (((prefix != 0) && (_mi_strnlen(prefix, 33) <= 32)) && (!_mi_is_main_thread()))
  {
    char tprefix[64];
    _mi_snprintf(tprefix, sizeof(tprefix), "%sthread 0x%tx: ", prefix, (uintptr_t) _mi_thread_id());
    mi_vfprintf(out, arg, tprefix, fmt, args);
  }
  else
  {
    mi_vfprintf(out, arg, prefix, fmt, args);
  }
}


----------------------------
static _Atomic size_t error_count
----------------------------
None
----------------------------
***/


void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


/*** DEPENDENCIES:
static void * _Atomic mi_error_arg
----------------------------
static void mi_error_default(int err)
{
  (void) err;
  if (err == 14)
  {
    abort();
  }
}


----------------------------
static mi_error_fun * volatile mi_error_handler
----------------------------
static void mi_show_error_message(const char *fmt, va_list args)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    if (!mi_option_is_enabled(mi_option_show_errors))
    {
      return;
    }
    if ((mi_max_error_count >= 0) && (((long) atomic_fetch_add_explicit(&error_count, (uintptr_t) 1, memory_order_acq_rel)) > mi_max_error_count))
    {
      return;
    }
  }
  mi_vfprintf_thread(0, 0, "mimalloc: error: ", fmt, args);
}


----------------------------
***/


void _mi_trace_message(const char *fmt, ...)
{
  if (mi_option_get(mi_option_verbose) <= 1)
  {
    return;
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: ", fmt, args);
  ;
}


/*** DEPENDENCIES:
static void mi_vfprintf_thread(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  if (((prefix != 0) && (_mi_strnlen(prefix, 33) <= 32)) && (!_mi_is_main_thread()))
  {
    char tprefix[64];
    _mi_snprintf(tprefix, sizeof(tprefix), "%sthread 0x%tx: ", prefix, (uintptr_t) _mi_thread_id());
    mi_vfprintf(out, arg, tprefix, fmt, args);
  }
  else
  {
    mi_vfprintf(out, arg, prefix, fmt, args);
  }
}


----------------------------
None
----------------------------
***/


void _mi_verbose_message(const char *fmt, ...)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    return;
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, "mimalloc: ", fmt, args);
  ;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


/*** DEPENDENCIES:
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
None
----------------------------
***/


size_t mi_option_get_size(mi_option_t option)
{
  const long x = mi_option_get(option);
  size_t size = (x < 0) ? (0) : ((size_t) x);
  if (mi_option_has_size_in_kib(option))
  {
    size *= 1024UL;
  }
  return size;
}


/*** DEPENDENCIES:
static bool mi_option_has_size_in_kib(mi_option_t option)
{
  return (option == mi_option_reserve_os_memory) || (option == mi_option_arena_reserve);
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
None
----------------------------
***/


void _mi_raw_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, 0, fmt, args);
  ;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void _mi_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: ", fmt, args);
  ;
}


/*** DEPENDENCIES:
static void mi_vfprintf_thread(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  if (((prefix != 0) && (_mi_strnlen(prefix, 33) <= 32)) && (!_mi_is_main_thread()))
  {
    char tprefix[64];
    _mi_snprintf(tprefix, sizeof(tprefix), "%sthread 0x%tx: ", prefix, (uintptr_t) _mi_thread_id());
    mi_vfprintf(out, arg, tprefix, fmt, args);
  }
  else
  {
    mi_vfprintf(out, arg, prefix, fmt, args);
  }
}


----------------------------
***/


static void mi_out_stderr(const char *msg, void *arg)
{
  (void) arg;
  if ((msg != 0) && (msg[0] != 0))
  {
    _mi_prim_out_stderr(msg);
  }
}


/*** DEPENDENCIES:
void _mi_prim_out_stderr(const char *msg)
{
  fputs(msg, stderr);
}


----------------------------
***/


void mi_options_print(void)
{
  const int vermajor = 316 / 100;
  const int verminor = (316 % 100) / 10;
  const int verpatch = 316 % 10;
  _mi_message("v%i.%i.%i%s%s (built on %s, %s)\n", vermajor, verminor, verpatch, "", "", "Dec 15 2025", "19:45:47");
  for (int i = 0; i < _mi_option_last; i += 1)
  {
    mi_option_t option = (mi_option_t) i;
    long l = mi_option_get(option);
    (void) l;
    mi_option_desc_t *desc = &mi_options[option];
    _mi_message("option '%s': %ld %s\n", desc->name, desc->value, (mi_option_has_size_in_kib(option)) ? ("KiB") : (""));
  }

  _mi_message("debug level : %d\n", 2);
  _mi_message("secure level: %d\n", 0);
  _mi_message("mem tracking: %s\n", "none");
}


/*** DEPENDENCIES:
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
void _mi_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: ", fmt, args);
  ;
}


----------------------------
static bool mi_option_has_size_in_kib(mi_option_t option)
{
  return (option == mi_option_reserve_os_memory) || (option == mi_option_arena_reserve);
}


----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
static mi_option_desc_t mi_options[_mi_option_last] = {{1, MI_OPTION_UNINIT, mi_option_show_errors, "show_errors", 0}, {0, MI_OPTION_UNINIT, mi_option_show_stats, "show_stats", 0}, {0, MI_OPTION_UNINIT, mi_option_verbose, "verbose", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, MI_OPTION_UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, MI_OPTION_UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, MI_OPTION_UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, MI_OPTION_UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, MI_OPTION_UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {1000, MI_OPTION_UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, MI_OPTION_UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, MI_OPTION_UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, MI_OPTION_UNINIT, mi_option_os_tag, "os_tag", 0}, {32, MI_OPTION_UNINIT, mi_option_max_errors, "max_errors", 0}, {32, MI_OPTION_UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, MI_OPTION_UNINIT, mi_option_deprecated_max_segment_reclaim, "deprecated_max_segment_reclaim", 0}, {0, MI_OPTION_UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, MI_OPTION_UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {1, MI_OPTION_UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, MI_OPTION_UNINIT, mi_option_deprecated_purge_extend_delay, "deprecated_purge_extend_delay", "decommit_extend_delay"}, {0, MI_OPTION_UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, MI_OPTION_UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, MI_OPTION_UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, MI_OPTION_UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {10000, MI_OPTION_UNINIT, mi_option_generic_collect, "generic_collect", 0}, {0, MI_OPTION_UNINIT, mi_option_page_reclaim_on_free, "page_reclaim_on_free", "abandoned_reclaim_on_free"}, {2, MI_OPTION_UNINIT, mi_option_page_full_retain, "page_full_retain", 0}, {4, MI_OPTION_UNINIT, mi_option_page_max_candidates, "page_max_candidates", 0}, {0, MI_OPTION_UNINIT, mi_option_max_vabits, "max_vabits", 0}, {0, MI_OPTION_UNINIT, mi_option_pagemap_commit, "pagemap_commit", 0}, {0, MI_OPTION_UNINIT, mi_option_page_commit_on_demand, "page_commit_on_demand", 0}, {-1, MI_OPTION_UNINIT, mi_option_page_max_reclaim, "page_max_reclaim", 0}, {32, MI_OPTION_UNINIT, mi_option_page_cross_thread_max_reclaim, "page_cross_thread_max_reclaim", 0}}
----------------------------
None
----------------------------
***/


static void mi_out_buf_flush(mi_output_fun *out, bool no_more_buf, void *arg)
{
  if (out == 0)
  {
    return;
  }
  size_t count = atomic_fetch_add_explicit(&out_len, (no_more_buf) ? ((size_t) (16 * 1024)) : (1), memory_order_acq_rel);
  if (count > ((size_t) (16 * 1024)))
  {
    count = (size_t) (16 * 1024);
  }
  mi_output_buffer[count] = 0;
  out(mi_output_buffer, arg);
  if (!no_more_buf)
  {
    mi_output_buffer[count] = '\n';
  }
}


/*** DEPENDENCIES:
static char mi_output_buffer[((size_t) (16 * 1024)) + 1]
----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
static _Atomic size_t out_len
----------------------------
***/


static void mi_out_buf_stderr(const char *msg, void *arg)
{
  mi_out_stderr(msg, arg);
  mi_out_buf(msg, arg);
}


/*** DEPENDENCIES:
static void mi_out_stderr(const char *msg, void *arg)
{
  (void) arg;
  if ((msg != 0) && (msg[0] != 0))
  {
    _mi_prim_out_stderr(msg);
  }
}


----------------------------
None
----------------------------
***/


static void mi_add_stderr_output(void)
{
  (mi_out_default == 0) ? ((void) 0) : (_mi_assert_fail("mi_out_default == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 407, __func__));
  if (mi_out_default == 0)
  {
    mi_out_buf_flush(&mi_out_stderr, 0, 0);
    mi_out_default = &mi_out_buf_stderr;
  }
}


/*** DEPENDENCIES:
static void mi_out_stderr(const char *msg, void *arg)
{
  (void) arg;
  if ((msg != 0) && (msg[0] != 0))
  {
    _mi_prim_out_stderr(msg);
  }
}


----------------------------
static void mi_out_buf_stderr(const char *msg, void *arg)
{
  mi_out_stderr(msg, arg);
  mi_out_buf(msg, arg);
}


----------------------------
static void mi_out_buf_flush(mi_output_fun *out, bool no_more_buf, void *arg)
{
  if (out == 0)
  {
    return;
  }
  size_t count = atomic_fetch_add_explicit(&out_len, (no_more_buf) ? ((size_t) (16 * 1024)) : (1), memory_order_acq_rel);
  if (count > ((size_t) (16 * 1024)))
  {
    count = (size_t) (16 * 1024);
  }
  mi_output_buffer[count] = 0;
  out(mi_output_buffer, arg);
  if (!no_more_buf)
  {
    mi_output_buffer[count] = '\n';
  }
}


----------------------------
static mi_output_fun * volatile mi_out_default
----------------------------
None
----------------------------
***/


void _mi_options_init(void)
{
  mi_add_stderr_output();
  for (int i = 0; i < _mi_option_last; i += 1)
  {
    mi_option_t option = (mi_option_t) i;
    long l = mi_option_get(option);
    (void) l;
  }

  mi_max_error_count = mi_option_get(mi_option_max_errors);
  mi_max_warning_count = mi_option_get(mi_option_max_warnings);
  if (mi_option_is_enabled(mi_option_verbose))
  {
    mi_options_print();
  }
}


/*** DEPENDENCIES:
static void mi_add_stderr_output(void)
{
  (mi_out_default == 0) ? ((void) 0) : (_mi_assert_fail("mi_out_default == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 407, __func__));
  if (mi_out_default == 0)
  {
    mi_out_buf_flush(&mi_out_stderr, 0, 0);
    mi_out_default = &mi_out_buf_stderr;
  }
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
static long mi_max_error_count = 16
----------------------------
void mi_options_print(void)
{
  const int vermajor = 316 / 100;
  const int verminor = (316 % 100) / 10;
  const int verpatch = 316 % 10;
  _mi_message("v%i.%i.%i%s%s (built on %s, %s)\n", vermajor, verminor, verpatch, "", "", "Dec 15 2025", "19:45:47");
  for (int i = 0; i < _mi_option_last; i += 1)
  {
    mi_option_t option = (mi_option_t) i;
    long l = mi_option_get(option);
    (void) l;
    mi_option_desc_t *desc = &mi_options[option];
    _mi_message("option '%s': %ld %s\n", desc->name, desc->value, (mi_option_has_size_in_kib(option)) ? ("KiB") : (""));
  }

  _mi_message("debug level : %d\n", 2);
  _mi_message("secure level: %d\n", 0);
  _mi_message("mem tracking: %s\n", "none");
}


----------------------------
static long mi_max_warning_count = 16
----------------------------
None
----------------------------
***/


void mi_option_set_enabled(mi_option_t option, bool enable)
{
  mi_option_set(option, (enable) ? (1) : (0));
}


/*** DEPENDENCIES:
void mi_option_set(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 283, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 286, __func__));
  desc->value = value;
  desc->init = MI_OPTION_INITIALIZED;
  if ((desc->option == mi_option_guarded_min) && (_mi_option_get_fast(mi_option_guarded_max) < value))
  {
    mi_option_set(mi_option_guarded_max, value);
  }
  else
    if ((desc->option == mi_option_guarded_max) && (_mi_option_get_fast(mi_option_guarded_min) > value))
  {
    mi_option_set(mi_option_guarded_min, value);
  }
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
***/


void mi_option_enable(mi_option_t option)
{
  mi_option_set_enabled(option, 1);
}


/*** DEPENDENCIES:
void mi_option_set_enabled(mi_option_t option, bool enable)
{
  mi_option_set(option, (enable) ? (1) : (0));
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
***/


void mi_option_disable(mi_option_t option)
{
  mi_option_set_enabled(option, 0);
}


/*** DEPENDENCIES:
void mi_option_set_enabled(mi_option_t option, bool enable)
{
  mi_option_set(option, (enable) ? (1) : (0));
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
***/


void mi_option_set_default(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 299, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &mi_options[option];
  if (desc->init != MI_OPTION_INITIALIZED)
  {
    desc->value = value;
  }
}


/*** DEPENDENCIES:
static mi_option_desc_t mi_options[_mi_option_last] = {{1, MI_OPTION_UNINIT, mi_option_show_errors, "show_errors", 0}, {0, MI_OPTION_UNINIT, mi_option_show_stats, "show_stats", 0}, {0, MI_OPTION_UNINIT, mi_option_verbose, "verbose", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, MI_OPTION_UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, MI_OPTION_UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, MI_OPTION_UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, MI_OPTION_UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, MI_OPTION_UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {1000, MI_OPTION_UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, MI_OPTION_UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, MI_OPTION_UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, MI_OPTION_UNINIT, mi_option_os_tag, "os_tag", 0}, {32, MI_OPTION_UNINIT, mi_option_max_errors, "max_errors", 0}, {32, MI_OPTION_UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, MI_OPTION_UNINIT, mi_option_deprecated_max_segment_reclaim, "deprecated_max_segment_reclaim", 0}, {0, MI_OPTION_UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, MI_OPTION_UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {1, MI_OPTION_UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, MI_OPTION_UNINIT, mi_option_deprecated_purge_extend_delay, "deprecated_purge_extend_delay", "decommit_extend_delay"}, {0, MI_OPTION_UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, MI_OPTION_UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, MI_OPTION_UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, MI_OPTION_UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {10000, MI_OPTION_UNINIT, mi_option_generic_collect, "generic_collect", 0}, {0, MI_OPTION_UNINIT, mi_option_page_reclaim_on_free, "page_reclaim_on_free", "abandoned_reclaim_on_free"}, {2, MI_OPTION_UNINIT, mi_option_page_full_retain, "page_full_retain", 0}, {4, MI_OPTION_UNINIT, mi_option_page_max_candidates, "page_max_candidates", 0}, {0, MI_OPTION_UNINIT, mi_option_max_vabits, "max_vabits", 0}, {0, MI_OPTION_UNINIT, mi_option_pagemap_commit, "pagemap_commit", 0}, {0, MI_OPTION_UNINIT, mi_option_page_commit_on_demand, "page_commit_on_demand", 0}, {-1, MI_OPTION_UNINIT, mi_option_page_max_reclaim, "page_max_reclaim", 0}, {32, MI_OPTION_UNINIT, mi_option_page_cross_thread_max_reclaim, "page_cross_thread_max_reclaim", 0}}
----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
None
----------------------------
***/


void mi_option_set_enabled_default(mi_option_t option, bool enable)
{
  mi_option_set_default(option, (enable) ? (1) : (0));
}


/*** DEPENDENCIES:
void mi_option_set_default(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 299, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &mi_options[option];
  if (desc->init != MI_OPTION_INITIALIZED)
  {
    desc->value = value;
  }
}


----------------------------
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
***/


void mi_register_error(mi_error_fun *fun, void *arg)
{
  mi_error_handler = fun;
  atomic_store_explicit(&mi_error_arg, arg, memory_order_release);
}


/*** DEPENDENCIES:
static void * _Atomic mi_error_arg
----------------------------
typedef void mi_error_fun(int err, void *arg)
----------------------------
static mi_error_fun * volatile mi_error_handler
----------------------------
***/


void mi_register_output(mi_output_fun *out, void *arg)
{
  mi_out_default = (out == 0) ? (&mi_out_stderr) : (out);
  atomic_store_explicit(&mi_out_arg, arg, memory_order_release);
  if (out != 0)
  {
    mi_out_buf_flush(out, 1, arg);
  }
}


/*** DEPENDENCIES:
static void * _Atomic mi_out_arg
----------------------------
static void mi_out_buf_flush(mi_output_fun *out, bool no_more_buf, void *arg)
{
  if (out == 0)
  {
    return;
  }
  size_t count = atomic_fetch_add_explicit(&out_len, (no_more_buf) ? ((size_t) (16 * 1024)) : (1), memory_order_acq_rel);
  if (count > ((size_t) (16 * 1024)))
  {
    count = (size_t) (16 * 1024);
  }
  mi_output_buffer[count] = 0;
  out(mi_output_buffer, arg);
  if (!no_more_buf)
  {
    mi_output_buffer[count] = '\n';
  }
}


----------------------------
static mi_output_fun * volatile mi_out_default
----------------------------
static void mi_out_stderr(const char *msg, void *arg)
{
  (void) arg;
  if ((msg != 0) && (msg[0] != 0))
  {
    _mi_prim_out_stderr(msg);
  }
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
***/


