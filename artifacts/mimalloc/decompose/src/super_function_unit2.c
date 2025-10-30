// element in merge of:  _mi_warning_message,mi_option_get,mi_option_init,mi_option_is_enabled
void _mi_warning_message(const char *fmt, ...)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    if (!mi_option_is_enabled(mi_option_show_errors))
    {
      return;
    }
    if ((mi_max_warning_count >= 0) && (((long) atomic_fetch_add_explicit(&warning_count, (uintptr_t) 1, memory_order_acq_rel)) > mi_max_warning_count))
    {
      return;
    }
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: warning: ", fmt, args);
  ;
}


/*** DEPENDENCIES:
static long mi_max_warning_count = 16
----------------------------
static _Atomic size_t warning_count
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
None
----------------------------
***/


// element in merge of:  _mi_warning_message,mi_option_get,mi_option_init,mi_option_is_enabled
static void mi_option_init(mi_option_desc_t *desc)
{
  char s[64 + 1];
  char buf[64 + 1];
  _mi_strlcpy(buf, "mimalloc_", sizeof(buf));
  _mi_strlcat(buf, desc->name, sizeof(buf));
  bool found = _mi_getenv(buf, s, sizeof(s));
  if ((!found) && (desc->legacy_name != 0))
  {
    _mi_strlcpy(buf, "mimalloc_", sizeof(buf));
    _mi_strlcat(buf, desc->legacy_name, sizeof(buf));
    found = _mi_getenv(buf, s, sizeof(s));
    if (found)
    {
      _mi_warning_message("environment option \"mimalloc_%s\" is deprecated -- use \"mimalloc_%s\" instead.\n", desc->legacy_name, desc->name);
    }
  }
  if (found)
  {
    helper_mi_option_init_1(desc, s, buf);
  }
  else
    if (!_mi_preloading())
  {
    desc->init = DEFAULTED;
  }
}


/*** DEPENDENCIES:
void helper_mi_option_init_1(mi_option_desc_t * const desc, char s[64 + 1], char buf[64 + 1])
{
  size_t len = _mi_strnlen(s, (sizeof(buf)) - 1);
  for (size_t i = 0; i < len; i += 1)
  {
    buf[i] = _mi_toupper(s[i]);
  }

  buf[len] = 0;
  if ((buf[0] == 0) || (strstr("1;TRUE;YES;ON", buf) != 0))
  {
    desc->value = 1;
    desc->init = INITIALIZED;
  }
  else
    if (strstr("0;FALSE;NO;OFF", buf) != 0)
  {
    desc->value = 0;
    desc->init = INITIALIZED;
  }
  else
  {
    helper_helper_mi_option_init_1_1(desc, buf);
  }
  (desc->init != UNINIT) ? ((void) 0) : (_mi_assert_fail("desc->init != UNINIT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 658, __func__));
}


----------------------------
bool _mi_preloading(void)
{
  return os_preloading;
}


----------------------------
void _mi_strlcpy(char *dest, const char *src, size_t dest_size)
{
  unsigned int src_idx = 0;
  unsigned int dest_idx = 0;
  if ((((&dest[dest_idx]) == 0) || ((&src[src_idx]) == 0)) || (dest_size == 0))
  {
    return;
  }
  while ((src[src_idx] != 0) && (dest_size > 1))
  {
    dest[dest_idx] = src[src_idx];
    src_idx += 1;
    dest_idx += 1;
    dest_size -= 1;
  }

  dest[dest_idx] = 0;
}


----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
void _mi_strlcat(char *dest, const char *src, size_t dest_size)
{
  unsigned int dest_idx = 0;
  if ((((&dest[dest_idx]) == 0) || (src == 0)) || (dest_size == 0))
  {
    return;
  }
  while ((dest[dest_idx] != 0) && (dest_size > 1))
  {
    dest_idx += 1;
    dest_size -= 1;
  }

  _mi_strlcpy(dest, src, dest_size);
}


----------------------------
bool _mi_getenv(const char *name, char *result, size_t result_size)
{
  if (((name == 0) || (result == 0)) || (result_size < 64))
  {
    return 0;
  }
  return _mi_prim_getenv(name, result, result_size);
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_warning_message,mi_option_get,mi_option_init,mi_option_is_enabled
long mi_option_get(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 247, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return 0;
  }
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 250, __func__));
  if (__builtin_expect(!(!(desc->init == UNINIT)), 0))
  {
    mi_option_init(desc);
  }
  return desc->value;
}


/*** DEPENDENCIES:
None
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
  mi_option_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_purge_extend_delay,
  mi_option_abandoned_reclaim_on_free,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_target_segments_per_thread,
  mi_option_generic_collect,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t
----------------------------
static mi_option_desc_t options[_mi_option_last] = {{1, UNINIT, mi_option_show_errors, "show_errors", 0}, {0, UNINIT, mi_option_show_stats, "show_stats", 0}, {0, UNINIT, mi_option_verbose, "verbose", 0}, {1, UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", "abandoned_page_reset"}, {0, UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {10, UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, UNINIT, mi_option_os_tag, "os_tag", 0}, {32, UNINIT, mi_option_max_errors, "max_errors", 0}, {32, UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, UNINIT, mi_option_max_segment_reclaim, "max_segment_reclaim", 0}, {0, UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {10, UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, UNINIT, mi_option_purge_extend_delay, "purge_extend_delay", "decommit_extend_delay"}, {0, UNINIT, mi_option_abandoned_reclaim_on_free, "abandoned_reclaim_on_free", 0}, {0, UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {0, UNINIT, mi_option_target_segments_per_thread, "target_segments_per_thread", 0}, {10000, UNINIT, mi_option_generic_collect, "generic_collect", 0}}
----------------------------
typedef struct mi_option_desc_s
{
  long value;
  mi_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_warning_message,mi_option_get,mi_option_init,mi_option_is_enabled
bool mi_option_is_enabled(mi_option_t option)
{
  return mi_option_get(option) != 0;
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
  mi_option_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_purge_extend_delay,
  mi_option_abandoned_reclaim_on_free,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_target_segments_per_thread,
  mi_option_generic_collect,
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


