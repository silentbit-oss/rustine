static bool mi_is_in_main(void *stat)
{
  return (((uint8_t *) stat) >= ((uint8_t *) (&_mi_stats_main))) && (((uint8_t *) stat) < (((uint8_t *) (&_mi_stats_main)) + (sizeof(mi_stats_t))));
}


/*** DEPENDENCIES:
extern mi_stats_t _mi_stats_main
----------------------------
***/


static void mi_stat_update(mi_stat_count_t *stat, int64_t amount)
{
  if (amount == 0)
  {
    return;
  }
  if (__builtin_expect(!(!mi_is_in_main(stat)), 0))
  {
    int64_t current = mi_atomic_addi64_relaxed(&stat->current, amount);
    mi_atomic_maxi64_relaxed(&stat->peak, current + amount);
    if (amount > 0)
    {
      mi_atomic_addi64_relaxed(&stat->total, amount);
    }
  }
  else
  {
    stat->current += amount;
    if (stat->current > stat->peak)
    {
      stat->peak = stat->current;
    }
    if (amount > 0)
    {
      stat->total += amount;
    }
  }
}


/*** DEPENDENCIES:
inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}


----------------------------
inline static void mi_atomic_maxi64_relaxed(volatile int64_t *p, int64_t x)
{
  int64_t current = atomic_load_explicit((int64_t *) p, memory_order_relaxed);
  while ((current < x) && (!atomic_compare_exchange_weak_explicit((int64_t *) p, &current, x, memory_order_release, memory_order_relaxed)))
  {
  }

  ;
}


----------------------------
static bool mi_is_in_main(void *stat)
{
  return (((uint8_t *) stat) >= ((uint8_t *) (&_mi_stats_main))) && (((uint8_t *) stat) < (((uint8_t *) (&_mi_stats_main)) + (sizeof(mi_stats_t))));
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


void _mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
}


/*** DEPENDENCIES:
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
static void mi_stat_update(mi_stat_count_t *stat, int64_t amount)
{
  if (amount == 0)
  {
    return;
  }
  if (__builtin_expect(!(!mi_is_in_main(stat)), 0))
  {
    int64_t current = mi_atomic_addi64_relaxed(&stat->current, amount);
    mi_atomic_maxi64_relaxed(&stat->peak, current + amount);
    if (amount > 0)
    {
      mi_atomic_addi64_relaxed(&stat->total, amount);
    }
  }
  else
  {
    stat->current += amount;
    if (stat->current > stat->peak)
    {
      stat->peak = stat->current;
    }
    if (amount > 0)
    {
      stat->total += amount;
    }
  }
}


----------------------------
***/


void _mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  if (mi_is_in_main(stat))
  {
    mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
  }
  else
  {
    stat->total += amount;
  }
}


/*** DEPENDENCIES:
inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}


----------------------------
static bool mi_is_in_main(void *stat)
{
  return (((uint8_t *) stat) >= ((uint8_t *) (&_mi_stats_main))) && (((uint8_t *) stat) < (((uint8_t *) (&_mi_stats_main)) + (sizeof(mi_stats_t))));
}


----------------------------
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t
----------------------------
***/


void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


/*** DEPENDENCIES:
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
static void mi_stat_update(mi_stat_count_t *stat, int64_t amount)
{
  if (amount == 0)
  {
    return;
  }
  if (__builtin_expect(!(!mi_is_in_main(stat)), 0))
  {
    int64_t current = mi_atomic_addi64_relaxed(&stat->current, amount);
    mi_atomic_maxi64_relaxed(&stat->peak, current + amount);
    if (amount > 0)
    {
      mi_atomic_addi64_relaxed(&stat->total, amount);
    }
  }
  else
  {
    stat->current += amount;
    if (stat->current > stat->peak)
    {
      stat->peak = stat->current;
    }
    if (amount > 0)
    {
      stat->total += amount;
    }
  }
}


----------------------------
***/


mi_msecs_t _mi_clock_now(void)
{
  return _mi_prim_clock_now();
}


/*** DEPENDENCIES:
mi_msecs_t _mi_prim_clock_now(void)
{
  return (mi_msecs_t) clock();
}


----------------------------
***/


static void mi_stat_counter_add_mt(mi_stat_counter_t *stat, const mi_stat_counter_t *src)
{
  if (stat == src)
  {
    return;
  }
  mi_atomic_void_addi64_relaxed(&stat->total, &src->total);
}


/*** DEPENDENCIES:
inline static void mi_atomic_void_addi64_relaxed(volatile int64_t *p, const volatile int64_t *padd)
{
  const int64_t add = atomic_load_explicit((int64_t *) padd, memory_order_relaxed);
  if (add != 0)
  {
    atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
  }
}


----------------------------
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t
----------------------------
***/


static void mi_stat_count_add_mt(mi_stat_count_t *stat, const mi_stat_count_t *src)
{
  if (stat == src)
  {
    return;
  }
  mi_atomic_void_addi64_relaxed(&stat->total, &src->total);
  mi_atomic_void_addi64_relaxed(&stat->current, &src->current);
  mi_atomic_void_addi64_relaxed(&stat->peak, &src->peak);
}


/*** DEPENDENCIES:
inline static void mi_atomic_void_addi64_relaxed(volatile int64_t *p, const volatile int64_t *padd)
{
  const int64_t add = atomic_load_explicit((int64_t *) padd, memory_order_relaxed);
  if (add != 0)
  {
    atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
  }
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


static void mi_stats_add(mi_stats_t *stats, const mi_stats_t *src)
{
  if (stats == src)
  {
    return;
  }
  mi_stat_count_add_mt(&stats->pages, &src->pages);
  mi_stat_count_add_mt(&stats->reserved, &src->reserved);
  mi_stat_count_add_mt(&stats->committed, &src->committed);
  mi_stat_count_add_mt(&stats->reset, &src->reset);
  mi_stat_count_add_mt(&stats->purged, &src->purged);
  mi_stat_count_add_mt(&stats->page_committed, &src->page_committed);
  mi_stat_count_add_mt(&stats->pages_abandoned, &src->pages_abandoned);
  mi_stat_count_add_mt(&stats->threads, &src->threads);
  mi_stat_count_add_mt(&stats->malloc_normal, &src->malloc_normal);
  mi_stat_count_add_mt(&stats->malloc_huge, &src->malloc_huge);
  mi_stat_count_add_mt(&stats->malloc_requested, &src->malloc_requested);
  mi_stat_counter_add_mt(&stats->mmap_calls, &src->mmap_calls);
  mi_stat_counter_add_mt(&stats->commit_calls, &src->commit_calls);
  mi_stat_counter_add_mt(&stats->reset_calls, &src->reset_calls);
  mi_stat_counter_add_mt(&stats->purge_calls, &src->purge_calls);
  mi_stat_counter_add_mt(&stats->arena_count, &src->arena_count);
  mi_stat_counter_add_mt(&stats->malloc_normal_count, &src->malloc_normal_count);
  mi_stat_counter_add_mt(&stats->malloc_huge_count, &src->malloc_huge_count);
  mi_stat_counter_add_mt(&stats->malloc_guarded_count, &src->malloc_guarded_count);
  mi_stat_counter_add_mt(&stats->arena_rollback_count, &src->arena_rollback_count);
  mi_stat_counter_add_mt(&stats->arena_purges, &src->arena_purges);
  mi_stat_counter_add_mt(&stats->pages_extended, &src->pages_extended);
  mi_stat_counter_add_mt(&stats->pages_retire, &src->pages_retire);
  mi_stat_counter_add_mt(&stats->page_searches, &src->page_searches);
  mi_stat_count_add_mt(&stats->segments, &src->segments);
  mi_stat_count_add_mt(&stats->segments_abandoned, &src->segments_abandoned);
  mi_stat_count_add_mt(&stats->segments_cache, &src->segments_cache);
  mi_stat_count_add_mt(&stats->_segments_reserved, &src->_segments_reserved);
  mi_stat_counter_add_mt(&stats->pages_reclaim_on_alloc, &src->pages_reclaim_on_alloc);
  mi_stat_counter_add_mt(&stats->pages_reclaim_on_free, &src->pages_reclaim_on_free);
  mi_stat_counter_add_mt(&stats->pages_reabandon_full, &src->pages_reabandon_full);
  mi_stat_counter_add_mt(&stats->pages_unabandon_busy_wait, &src->pages_unabandon_busy_wait);
  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_stat_count_add_mt(&stats->malloc_bins[i], &src->malloc_bins[i]);
  }

  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_stat_count_add_mt(&stats->page_bins[i], &src->page_bins[i]);
  }

}


/*** DEPENDENCIES:
static void mi_stat_count_add_mt(mi_stat_count_t *stat, const mi_stat_count_t *src)
{
  if (stat == src)
  {
    return;
  }
  mi_atomic_void_addi64_relaxed(&stat->total, &src->total);
  mi_atomic_void_addi64_relaxed(&stat->current, &src->current);
  mi_atomic_void_addi64_relaxed(&stat->peak, &src->peak);
}


----------------------------
static void mi_stat_counter_add_mt(mi_stat_counter_t *stat, const mi_stat_counter_t *src)
{
  if (stat == src)
  {
    return;
  }
  mi_atomic_void_addi64_relaxed(&stat->total, &src->total);
}


----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
***/


static void mi_stats_merge_from(mi_stats_t *stats)
{
  if (stats != (&_mi_stats_main))
  {
    mi_stats_add(&_mi_stats_main, stats);
    memset(stats, 0, sizeof(mi_stats_t));
  }
}


/*** DEPENDENCIES:
extern mi_stats_t _mi_stats_main
----------------------------
static void mi_stats_add(mi_stats_t *stats, const mi_stats_t *src)
{
  if (stats == src)
  {
    return;
  }
  mi_stat_count_add_mt(&stats->pages, &src->pages);
  mi_stat_count_add_mt(&stats->reserved, &src->reserved);
  mi_stat_count_add_mt(&stats->committed, &src->committed);
  mi_stat_count_add_mt(&stats->reset, &src->reset);
  mi_stat_count_add_mt(&stats->purged, &src->purged);
  mi_stat_count_add_mt(&stats->page_committed, &src->page_committed);
  mi_stat_count_add_mt(&stats->pages_abandoned, &src->pages_abandoned);
  mi_stat_count_add_mt(&stats->threads, &src->threads);
  mi_stat_count_add_mt(&stats->malloc_normal, &src->malloc_normal);
  mi_stat_count_add_mt(&stats->malloc_huge, &src->malloc_huge);
  mi_stat_count_add_mt(&stats->malloc_requested, &src->malloc_requested);
  mi_stat_counter_add_mt(&stats->mmap_calls, &src->mmap_calls);
  mi_stat_counter_add_mt(&stats->commit_calls, &src->commit_calls);
  mi_stat_counter_add_mt(&stats->reset_calls, &src->reset_calls);
  mi_stat_counter_add_mt(&stats->purge_calls, &src->purge_calls);
  mi_stat_counter_add_mt(&stats->arena_count, &src->arena_count);
  mi_stat_counter_add_mt(&stats->malloc_normal_count, &src->malloc_normal_count);
  mi_stat_counter_add_mt(&stats->malloc_huge_count, &src->malloc_huge_count);
  mi_stat_counter_add_mt(&stats->malloc_guarded_count, &src->malloc_guarded_count);
  mi_stat_counter_add_mt(&stats->arena_rollback_count, &src->arena_rollback_count);
  mi_stat_counter_add_mt(&stats->arena_purges, &src->arena_purges);
  mi_stat_counter_add_mt(&stats->pages_extended, &src->pages_extended);
  mi_stat_counter_add_mt(&stats->pages_retire, &src->pages_retire);
  mi_stat_counter_add_mt(&stats->page_searches, &src->page_searches);
  mi_stat_count_add_mt(&stats->segments, &src->segments);
  mi_stat_count_add_mt(&stats->segments_abandoned, &src->segments_abandoned);
  mi_stat_count_add_mt(&stats->segments_cache, &src->segments_cache);
  mi_stat_count_add_mt(&stats->_segments_reserved, &src->_segments_reserved);
  mi_stat_counter_add_mt(&stats->pages_reclaim_on_alloc, &src->pages_reclaim_on_alloc);
  mi_stat_counter_add_mt(&stats->pages_reclaim_on_free, &src->pages_reclaim_on_free);
  mi_stat_counter_add_mt(&stats->pages_reabandon_full, &src->pages_reabandon_full);
  mi_stat_counter_add_mt(&stats->pages_unabandon_busy_wait, &src->pages_unabandon_busy_wait);
  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_stat_count_add_mt(&stats->malloc_bins[i], &src->malloc_bins[i]);
  }

  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_stat_count_add_mt(&stats->page_bins[i], &src->page_bins[i]);
  }

}


----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
***/


void _mi_stats_done(mi_stats_t *stats)
{
  mi_stats_merge_from(stats);
}


/*** DEPENDENCIES:
static void mi_stats_merge_from(mi_stats_t *stats)
{
  if (stats != (&_mi_stats_main))
  {
    mi_stats_add(&_mi_stats_main, stats);
    memset(stats, 0, sizeof(mi_stats_t));
  }
}


----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
***/


void _mi_stats_merge_thread(mi_tld_t *tld)
{
  mi_stats_merge_from(&tld->stats);
}


/*** DEPENDENCIES:
static void mi_stats_merge_from(mi_stats_t *stats)
{
  if (stats != (&_mi_stats_main))
  {
    mi_stats_add(&_mi_stats_main, stats);
    memset(stats, 0, sizeof(mi_stats_t));
  }
}


----------------------------
None
----------------------------
***/


mi_msecs_t _mi_clock_end(mi_msecs_t start)
{
  mi_msecs_t end = _mi_clock_now();
  return (end - start) - mi_clock_diff;
}


/*** DEPENDENCIES:
mi_msecs_t _mi_clock_now(void)
{
  return _mi_prim_clock_now();
}


----------------------------
static mi_msecs_t mi_clock_diff
----------------------------
typedef int64_t mi_msecs_t
----------------------------
***/


mi_msecs_t _mi_clock_start(void)
{
  if (mi_clock_diff == 0.0)
  {
    mi_msecs_t t0 = _mi_clock_now();
    mi_clock_diff = _mi_clock_now() - t0;
  }
  return _mi_clock_now();
}


/*** DEPENDENCIES:
mi_msecs_t _mi_clock_now(void)
{
  return _mi_prim_clock_now();
}


----------------------------
static mi_msecs_t mi_clock_diff
----------------------------
typedef int64_t mi_msecs_t
----------------------------
***/


static void mi_stat_counter_print_avg(const mi_stat_counter_t *stat, const char *msg, mi_output_fun *out, void *arg)
{
  const int64_t avg_tens = (stat->total == 0) ? (0) : ((stat->total * 10) / stat->total);
  const long avg_whole = (long) (avg_tens / 10);
  const long avg_frac1 = (long) (avg_tens % 10);
  _mi_fprintf(out, arg, "%10s: %5ld.%ld avg\n", msg, avg_whole, avg_frac1);
}


/*** DEPENDENCIES:
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t
----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_buffered_flush(buffered_t *buf)
{
  buf->buf[buf->used] = 0;
  _mi_fputs(buf->out, buf->arg, 0, buf->buf);
  buf->used = 0;
}


/*** DEPENDENCIES:
void _mi_fputs(mi_output_fun *out, void *arg, const char *prefix, const char *message)
{
  unsigned int out_idx = 0;
  if ((((&out[out_idx]) == 0) || (((void *) out) == ((void *) stdout))) || (((void *) out) == ((void *) stderr)))
  {
    if (!mi_recurse_enter())
    {
      return;
    }
    out_idx = mi_out_get_default(&arg);
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
    mi_recurse_exit();
  }
  else
  {
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
  }
}


----------------------------
typedef struct buffered_s
{
  mi_output_fun *out;
  void *arg;
  char *buf;
  size_t used;
  size_t count;
} buffered_t
----------------------------
***/


static void mi_buffered_out(const char *msg, void *arg)
{
  buffered_t *buf = (buffered_t *) arg;
  if ((msg == 0) || (buf == 0))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if (buf->used >= buf->count)
    {
      mi_buffered_flush(buf);
    }
    (buf->used < buf->count) ? ((void) 0) : (_mi_assert_fail("buf->used < buf->count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 294, __func__));
    buf->buf[buf->used++] = c;
    if (c == '\n')
    {
      mi_buffered_flush(buf);
    }
  }

  unsigned int src_idx = 0;
}


/*** DEPENDENCIES:
typedef struct buffered_s
{
  mi_output_fun *out;
  void *arg;
  char *buf;
  size_t used;
  size_t count;
} buffered_t
----------------------------
static void mi_buffered_flush(buffered_t *buf)
{
  buf->buf[buf->used] = 0;
  _mi_fputs(buf->out, buf->arg, 0, buf->buf);
  buf->used = 0;
}


----------------------------
None
----------------------------
***/


static void mi_printf_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg, const char *fmt)
{
  char buf[32];
  buf[0] = 0;
  int len = 32;
  const char *suffix = (unit <= 0) ? (" ") : ("B");
  const int64_t base = (unit == 0) ? (1000) : (1024);
  if (unit > 0)
  {
    n *= unit;
  }
  const int64_t pos = (n < 0) ? (-n) : (n);
  if (pos < base)
  {
    if ((n != 1) || (suffix[0] != 'B'))
    {
      _mi_snprintf(buf, len, "%lld   %-3s", (long long) n, (n == 0) ? ("") : (suffix));
    }
  }
  else
  {
    int64_t divider = base;
    const char *magnitude = "K";
    unsigned int magnitude_idx = 0;
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "M";
    }
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "G";
    }
    const int64_t tens = n / (divider / 10);
    const long whole = (long) (tens / 10);
    const long frac1 = (long) (tens % 10);
    char unitdesc[8];
    _mi_snprintf(unitdesc, 8, "%s%s%s", magnitude, (base == 1024) ? ("i") : (""), suffix);
    _mi_snprintf(buf, len, "%ld.%ld %-3s", whole, (frac1 < 0) ? (-frac1) : (frac1), unitdesc);
  }
  _mi_fprintf(out, arg, (fmt == 0) ? ("%12s") : (fmt), buf);
}


/*** DEPENDENCIES:
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


static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
static void mi_printf_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg, const char *fmt)
{
  char buf[32];
  buf[0] = 0;
  int len = 32;
  const char *suffix = (unit <= 0) ? (" ") : ("B");
  const int64_t base = (unit == 0) ? (1000) : (1024);
  if (unit > 0)
  {
    n *= unit;
  }
  const int64_t pos = (n < 0) ? (-n) : (n);
  if (pos < base)
  {
    if ((n != 1) || (suffix[0] != 'B'))
    {
      _mi_snprintf(buf, len, "%lld   %-3s", (long long) n, (n == 0) ? ("") : (suffix));
    }
  }
  else
  {
    int64_t divider = base;
    const char *magnitude = "K";
    unsigned int magnitude_idx = 0;
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "M";
    }
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "G";
    }
    const int64_t tens = n / (divider / 10);
    const long whole = (long) (tens / 10);
    const long frac1 = (long) (tens % 10);
    char unitdesc[8];
    _mi_snprintf(unitdesc, 8, "%s%s%s", magnitude, (base == 1024) ? ("i") : (""), suffix);
    _mi_snprintf(buf, len, "%ld.%ld %-3s", whole, (frac1 < 0) ? (-frac1) : (frac1), unitdesc);
  }
  _mi_fprintf(out, arg, (fmt == 0) ? ("%12s") : (fmt), buf);
}


----------------------------
***/


static void mi_stat_peak_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  mi_print_amount(stat->peak, unit, out, arg);
  _mi_fprintf(out, arg, "\n");
}


/*** DEPENDENCIES:
static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
None
----------------------------
***/


static void mi_stat_counter_print(const mi_stat_counter_t *stat, const char *msg, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  mi_print_amount(stat->total, -1, out, arg);
  _mi_fprintf(out, arg, "\n");
}


/*** DEPENDENCIES:
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t
----------------------------
static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_print_header(mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s: %11s %11s %11s %11s %11s\n", "heap stats", "peak   ", "total   ", "current   ", "block   ", "total#   ");
}


/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_print_count(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  if (unit == 1)
  {
    _mi_fprintf(out, arg, "%12s", " ");
  }
  else
    mi_print_amount(n, 0, out, arg);
}


/*** DEPENDENCIES:
static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_stat_print_ex(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg, const char *notok)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  if (unit != 0)
  {
    if (unit > 0)
    {
      mi_print_amount(stat->peak, unit, out, arg);
      mi_print_amount(stat->total, unit, out, arg);
      mi_print_amount(stat->current, unit, out, arg);
      mi_print_amount(unit, 1, out, arg);
      mi_print_count(stat->total, unit, out, arg);
    }
    else
    {
      mi_print_amount(stat->peak, -1, out, arg);
      mi_print_amount(stat->total, -1, out, arg);
      mi_print_amount(stat->current, -1, out, arg);
      if (unit == (-1))
      {
        _mi_fprintf(out, arg, "%24s", "");
      }
      else
      {
        mi_print_amount(-unit, 1, out, arg);
        mi_print_count(stat->total / (-unit), 0, out, arg);
      }
    }
    if (stat->current != 0)
    {
      _mi_fprintf(out, arg, "  ");
      _mi_fprintf(out, arg, (notok == 0) ? ("not all freed") : (notok));
      _mi_fprintf(out, arg, "\n");
    }
    else
    {
      _mi_fprintf(out, arg, "  ok\n");
    }
  }
  else
  {
    mi_print_amount(stat->peak, 1, out, arg);
    mi_print_amount(stat->total, 1, out, arg);
    _mi_fprintf(out, arg, "%11s", " ");
    mi_print_amount(stat->current, 1, out, arg);
    _mi_fprintf(out, arg, "\n");
  }
}


/*** DEPENDENCIES:
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
static void mi_print_count(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  if (unit == 1)
  {
    _mi_fprintf(out, arg, "%12s", " ");
  }
  else
    mi_print_amount(n, 0, out, arg);
}


----------------------------
None
----------------------------
***/


static void mi_stat_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_stat_print_ex(stat, msg, unit, out, arg, 0);
}


/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
static void mi_stat_print_ex(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg, const char *notok)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  if (unit != 0)
  {
    if (unit > 0)
    {
      mi_print_amount(stat->peak, unit, out, arg);
      mi_print_amount(stat->total, unit, out, arg);
      mi_print_amount(stat->current, unit, out, arg);
      mi_print_amount(unit, 1, out, arg);
      mi_print_count(stat->total, unit, out, arg);
    }
    else
    {
      mi_print_amount(stat->peak, -1, out, arg);
      mi_print_amount(stat->total, -1, out, arg);
      mi_print_amount(stat->current, -1, out, arg);
      if (unit == (-1))
      {
        _mi_fprintf(out, arg, "%24s", "");
      }
      else
      {
        mi_print_amount(-unit, 1, out, arg);
        mi_print_count(stat->total / (-unit), 0, out, arg);
      }
    }
    if (stat->current != 0)
    {
      _mi_fprintf(out, arg, "  ");
      _mi_fprintf(out, arg, (notok == 0) ? ("not all freed") : (notok));
      _mi_fprintf(out, arg, "\n");
    }
    else
    {
      _mi_fprintf(out, arg, "  ok\n");
    }
  }
  else
  {
    mi_print_amount(stat->peak, 1, out, arg);
    mi_print_amount(stat->total, 1, out, arg);
    _mi_fprintf(out, arg, "%11s", " ");
    mi_print_amount(stat->current, 1, out, arg);
    _mi_fprintf(out, arg, "\n");
  }
}


----------------------------
***/


static void mi_stats_print_bins(const mi_stat_count_t *bins, size_t max, const char *fmt, mi_output_fun *out, void *arg)
{
  bool found = 0;
  char buf[64];
  for (size_t i = 0; i <= max; i += 1)
  {
    if (bins[i].total > 0)
    {
      found = 1;
      int64_t unit = _mi_bin_size((uint8_t) i);
      _mi_snprintf(buf, 64, "%s %3lu", fmt, (long) i);
      mi_stat_print(&bins[i], buf, unit, out, arg);
    }
  }

  if (found)
  {
    _mi_fprintf(out, arg, "\n");
    mi_print_header(out, arg);
  }
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
static void mi_stat_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_stat_print_ex(stat, msg, unit, out, arg, 0);
}


----------------------------
static void mi_print_header(mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s: %11s %11s %11s %11s %11s\n", "heap stats", "peak   ", "total   ", "current   ", "block   ", "total#   ");
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
size_t _mi_bin_size(size_t bin)
{
  return _mi_heap_empty.pages[bin].block_size;
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static void mi_stat_total_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  _mi_fprintf(out, arg, "%12s", " ");
  mi_print_amount(stat->total, unit, out, arg);
  _mi_fprintf(out, arg, "\n");
}


/*** DEPENDENCIES:
static void mi_print_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_printf_amount(n, unit, out, arg, 0);
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
None
----------------------------
***/


void mi_process_info(size_t *elapsed_msecs, size_t *user_msecs, size_t *system_msecs, size_t *current_rss, size_t *peak_rss, size_t *current_commit, size_t *peak_commit, size_t *page_faults)
{
  mi_process_info_t pinfo;
  memset(&pinfo, 0, sizeof(pinfo));
  pinfo.elapsed = _mi_clock_end(mi_process_start);
  pinfo.current_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.current), memory_order_relaxed);
  pinfo.peak_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.peak), memory_order_relaxed);
  pinfo.current_rss = pinfo.current_commit;
  pinfo.peak_rss = pinfo.peak_commit;
  pinfo.utime = 0;
  pinfo.stime = 0;
  pinfo.page_faults = 0;
  _mi_prim_process_info(&pinfo);
  if (elapsed_msecs != 0)
  {
    *elapsed_msecs = (pinfo.elapsed < 0) ? (0) : ((pinfo.elapsed < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.elapsed) : (PTRDIFF_MAX));
  }
  if (user_msecs != 0)
  {
    *user_msecs = (pinfo.utime < 0) ? (0) : ((pinfo.utime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.utime) : (PTRDIFF_MAX));
  }
  if (system_msecs != 0)
  {
    *system_msecs = (pinfo.stime < 0) ? (0) : ((pinfo.stime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.stime) : (PTRDIFF_MAX));
  }
  if (current_rss != 0)
  {
    *current_rss = pinfo.current_rss;
  }
  if (peak_rss != 0)
  {
    *peak_rss = pinfo.peak_rss;
  }
  if (current_commit != 0)
  {
    *current_commit = pinfo.current_commit;
  }
  if (peak_commit != 0)
  {
    *peak_commit = pinfo.peak_commit;
  }
  if (page_faults != 0)
  {
    *page_faults = pinfo.page_faults;
  }
}


/*** DEPENDENCIES:
mi_msecs_t _mi_clock_end(mi_msecs_t start)
{
  mi_msecs_t end = _mi_clock_now();
  return (end - start) - mi_clock_diff;
}


----------------------------
void _mi_prim_process_info(mi_process_info_t *pinfo)
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  pinfo->utime = timeval_secs(&rusage.ru_utime);
  pinfo->stime = timeval_secs(&rusage.ru_stime);
  pinfo->page_faults = rusage.ru_majflt;
  pinfo->peak_rss = rusage.ru_maxrss * 1024;
}


----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
typedef struct mi_process_info_s
{
  mi_msecs_t elapsed;
  mi_msecs_t utime;
  mi_msecs_t stime;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
} mi_process_info_t
----------------------------
static mi_msecs_t mi_process_start
----------------------------
***/


static void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out0, void *arg0)
{
  char buf[256];
  buffered_t buffer = {out0, arg0, 0, 0, 255};
  buffer.buf = buf;
  mi_output_fun *out = &mi_buffered_out;
  void *arg = &buffer;
  mi_print_header(out, arg);
  mi_stats_print_bins(stats->malloc_bins, 73U, "bin", out, arg);
  mi_stat_print(&stats->malloc_normal, "binned", (stats->malloc_normal_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_print(&stats->malloc_huge, "huge", (stats->malloc_huge_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_count_t total = {0, 0, 0};
  mi_stat_count_add_mt(&total, &stats->malloc_normal);
  mi_stat_count_add_mt(&total, &stats->malloc_huge);
  mi_stat_print_ex(&total, "total", 1, out, arg, "");
  mi_stat_total_print(&stats->malloc_requested, "malloc req", 1, out, arg);
  _mi_fprintf(out, arg, "\n");
  mi_stat_print_ex(&stats->reserved, "reserved", 1, out, arg, "");
  mi_stat_print_ex(&stats->committed, "committed", 1, out, arg, "");
  mi_stat_peak_print(&stats->reset, "reset", 1, out, arg);
  mi_stat_peak_print(&stats->purged, "purged", 1, out, arg);
  mi_stat_print_ex(&stats->page_committed, "touched", 1, out, arg, "");
  mi_stat_print(&stats->segments, "segments", -1, out, arg);
  mi_stat_print(&stats->segments_abandoned, "-abandoned", -1, out, arg);
  mi_stat_print(&stats->segments_cache, "-cached", -1, out, arg);
  mi_stat_print(&stats->pages, "pages", -1, out, arg);
  mi_stat_print(&stats->pages_abandoned, "-abandoned", -1, out, arg);
  mi_stat_counter_print(&stats->pages_extended, "-extended", out, arg);
  mi_stat_counter_print(&stats->pages_retire, "-retire", out, arg);
  mi_stat_counter_print(&stats->arena_count, "arenas", out, arg);
  mi_stat_counter_print(&stats->arena_rollback_count, "-rollback", out, arg);
  mi_stat_counter_print(&stats->mmap_calls, "mmaps", out, arg);
  mi_stat_counter_print(&stats->commit_calls, "commits", out, arg);
  mi_stat_counter_print(&stats->reset_calls, "resets", out, arg);
  mi_stat_counter_print(&stats->purge_calls, "purges", out, arg);
  mi_stat_counter_print(&stats->malloc_guarded_count, "guarded", out, arg);
  mi_stat_print(&stats->threads, "threads", -1, out, arg);
  mi_stat_counter_print_avg(&stats->page_searches, "searches", out, arg);
  _mi_fprintf(out, arg, "%10s: %5i\n", "numa nodes", _mi_os_numa_node_count());
  size_t elapsed;
  size_t user_time;
  size_t sys_time;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
  mi_process_info(&elapsed, &user_time, &sys_time, &current_rss, &peak_rss, &current_commit, &peak_commit, &page_faults);
  _mi_fprintf(out, arg, "%10s: %5zu.%03zu s\n", "elapsed", elapsed / 1000, elapsed % 1000);
  _mi_fprintf(out, arg, "%10s: user: %zu.%03zu s, system: %zu.%03zu s, faults: %zu, rss: ", "process", user_time / 1000, user_time % 1000, sys_time / 1000, sys_time % 1000, page_faults);
  mi_printf_amount((int64_t) peak_rss, 1, out, arg, "%s");
  if (peak_commit > 0)
  {
    _mi_fprintf(out, arg, ", commit: ");
    mi_printf_amount((int64_t) peak_commit, 1, out, arg, "%s");
  }
  _mi_fprintf(out, arg, "\n");
}


/*** DEPENDENCIES:
void mi_process_info(size_t *elapsed_msecs, size_t *user_msecs, size_t *system_msecs, size_t *current_rss, size_t *peak_rss, size_t *current_commit, size_t *peak_commit, size_t *page_faults)
{
  mi_process_info_t pinfo;
  memset(&pinfo, 0, sizeof(pinfo));
  pinfo.elapsed = _mi_clock_end(mi_process_start);
  pinfo.current_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.current), memory_order_relaxed);
  pinfo.peak_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.peak), memory_order_relaxed);
  pinfo.current_rss = pinfo.current_commit;
  pinfo.peak_rss = pinfo.peak_commit;
  pinfo.utime = 0;
  pinfo.stime = 0;
  pinfo.page_faults = 0;
  _mi_prim_process_info(&pinfo);
  if (elapsed_msecs != 0)
  {
    *elapsed_msecs = (pinfo.elapsed < 0) ? (0) : ((pinfo.elapsed < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.elapsed) : (PTRDIFF_MAX));
  }
  if (user_msecs != 0)
  {
    *user_msecs = (pinfo.utime < 0) ? (0) : ((pinfo.utime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.utime) : (PTRDIFF_MAX));
  }
  if (system_msecs != 0)
  {
    *system_msecs = (pinfo.stime < 0) ? (0) : ((pinfo.stime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.stime) : (PTRDIFF_MAX));
  }
  if (current_rss != 0)
  {
    *current_rss = pinfo.current_rss;
  }
  if (peak_rss != 0)
  {
    *peak_rss = pinfo.peak_rss;
  }
  if (current_commit != 0)
  {
    *current_commit = pinfo.current_commit;
  }
  if (peak_commit != 0)
  {
    *peak_commit = pinfo.peak_commit;
  }
  if (page_faults != 0)
  {
    *page_faults = pinfo.page_faults;
  }
}


----------------------------
typedef struct buffered_s
{
  mi_output_fun *out;
  void *arg;
  char *buf;
  size_t used;
  size_t count;
} buffered_t
----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
static void mi_stat_total_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  _mi_fprintf(out, arg, "%12s", " ");
  mi_print_amount(stat->total, unit, out, arg);
  _mi_fprintf(out, arg, "\n");
}


----------------------------
static void mi_stat_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  mi_stat_print_ex(stat, msg, unit, out, arg, 0);
}


----------------------------
int _mi_os_numa_node_count(void)
{
  size_t count = atomic_load_explicit(&mi_numa_node_count, memory_order_acquire);
  if (__builtin_expect(!(!(count == 0)), 0))
  {
    long ncount = mi_option_get(mi_option_use_numa_nodes);
    if ((ncount > 0) && (ncount < 2147483647))
    {
      count = (size_t) ncount;
    }
    else
    {
      const size_t n = _mi_prim_numa_node_count();
      if ((n == 0) || (n > 2147483647))
      {
        count = 1;
      }
      else
      {
        count = n;
      }
    }
    atomic_store_explicit(&mi_numa_node_count, count, memory_order_release);
    _mi_verbose_message("using %zd numa regions\n", count);
  }
  ((count > 0) && (count <= 2147483647)) ? ((void) 0) : (_mi_assert_fail("count > 0 && count <= INT_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 749, __func__));
  return (int) count;
}


----------------------------
static void mi_stats_print_bins(const mi_stat_count_t *bins, size_t max, const char *fmt, mi_output_fun *out, void *arg)
{
  bool found = 0;
  char buf[64];
  for (size_t i = 0; i <= max; i += 1)
  {
    if (bins[i].total > 0)
    {
      found = 1;
      int64_t unit = _mi_bin_size((uint8_t) i);
      _mi_snprintf(buf, 64, "%s %3lu", fmt, (long) i);
      mi_stat_print(&bins[i], buf, unit, out, arg);
    }
  }

  if (found)
  {
    _mi_fprintf(out, arg, "\n");
    mi_print_header(out, arg);
  }
}


----------------------------
static void mi_stat_counter_print(const mi_stat_counter_t *stat, const char *msg, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  mi_print_amount(stat->total, -1, out, arg);
  _mi_fprintf(out, arg, "\n");
}


----------------------------
static void mi_print_header(mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s: %11s %11s %11s %11s %11s\n", "heap stats", "peak   ", "total   ", "current   ", "block   ", "total#   ");
}


----------------------------
static void mi_stat_peak_print(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  mi_print_amount(stat->peak, unit, out, arg);
  _mi_fprintf(out, arg, "\n");
}


----------------------------
static void mi_printf_amount(int64_t n, int64_t unit, mi_output_fun *out, void *arg, const char *fmt)
{
  char buf[32];
  buf[0] = 0;
  int len = 32;
  const char *suffix = (unit <= 0) ? (" ") : ("B");
  const int64_t base = (unit == 0) ? (1000) : (1024);
  if (unit > 0)
  {
    n *= unit;
  }
  const int64_t pos = (n < 0) ? (-n) : (n);
  if (pos < base)
  {
    if ((n != 1) || (suffix[0] != 'B'))
    {
      _mi_snprintf(buf, len, "%lld   %-3s", (long long) n, (n == 0) ? ("") : (suffix));
    }
  }
  else
  {
    int64_t divider = base;
    const char *magnitude = "K";
    unsigned int magnitude_idx = 0;
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "M";
    }
    if (pos >= (divider * base))
    {
      divider *= base;
      magnitude_idx = "G";
    }
    const int64_t tens = n / (divider / 10);
    const long whole = (long) (tens / 10);
    const long frac1 = (long) (tens % 10);
    char unitdesc[8];
    _mi_snprintf(unitdesc, 8, "%s%s%s", magnitude, (base == 1024) ? ("i") : (""), suffix);
    _mi_snprintf(buf, len, "%ld.%ld %-3s", whole, (frac1 < 0) ? (-frac1) : (frac1), unitdesc);
  }
  _mi_fprintf(out, arg, (fmt == 0) ? ("%12s") : (fmt), buf);
}


----------------------------
static void mi_buffered_out(const char *msg, void *arg)
{
  buffered_t *buf = (buffered_t *) arg;
  if ((msg == 0) || (buf == 0))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if (buf->used >= buf->count)
    {
      mi_buffered_flush(buf);
    }
    (buf->used < buf->count) ? ((void) 0) : (_mi_assert_fail("buf->used < buf->count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 294, __func__));
    buf->buf[buf->used++] = c;
    if (c == '\n')
    {
      mi_buffered_flush(buf);
    }
  }

  unsigned int src_idx = 0;
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
static void mi_stat_counter_print_avg(const mi_stat_counter_t *stat, const char *msg, mi_output_fun *out, void *arg)
{
  const int64_t avg_tens = (stat->total == 0) ? (0) : ((stat->total * 10) / stat->total);
  const long avg_whole = (long) (avg_tens / 10);
  const long avg_frac1 = (long) (avg_tens % 10);
  _mi_fprintf(out, arg, "%10s: %5ld.%ld avg\n", msg, avg_whole, avg_frac1);
}


----------------------------
static void mi_stat_count_add_mt(mi_stat_count_t *stat, const mi_stat_count_t *src)
{
  if (stat == src)
  {
    return;
  }
  mi_atomic_void_addi64_relaxed(&stat->total, &src->total);
  mi_atomic_void_addi64_relaxed(&stat->current, &src->current);
  mi_atomic_void_addi64_relaxed(&stat->peak, &src->peak);
}


----------------------------
static void mi_stat_print_ex(const mi_stat_count_t *stat, const char *msg, int64_t unit, mi_output_fun *out, void *arg, const char *notok)
{
  _mi_fprintf(out, arg, "%10s:", msg);
  if (unit != 0)
  {
    if (unit > 0)
    {
      mi_print_amount(stat->peak, unit, out, arg);
      mi_print_amount(stat->total, unit, out, arg);
      mi_print_amount(stat->current, unit, out, arg);
      mi_print_amount(unit, 1, out, arg);
      mi_print_count(stat->total, unit, out, arg);
    }
    else
    {
      mi_print_amount(stat->peak, -1, out, arg);
      mi_print_amount(stat->total, -1, out, arg);
      mi_print_amount(stat->current, -1, out, arg);
      if (unit == (-1))
      {
        _mi_fprintf(out, arg, "%24s", "");
      }
      else
      {
        mi_print_amount(-unit, 1, out, arg);
        mi_print_count(stat->total / (-unit), 0, out, arg);
      }
    }
    if (stat->current != 0)
    {
      _mi_fprintf(out, arg, "  ");
      _mi_fprintf(out, arg, (notok == 0) ? ("not all freed") : (notok));
      _mi_fprintf(out, arg, "\n");
    }
    else
    {
      _mi_fprintf(out, arg, "  ok\n");
    }
  }
  else
  {
    mi_print_amount(stat->peak, 1, out, arg);
    mi_print_amount(stat->total, 1, out, arg);
    _mi_fprintf(out, arg, "%11s", " ");
    mi_print_amount(stat->current, 1, out, arg);
    _mi_fprintf(out, arg, "\n");
  }
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


void mi_stats_print_out(mi_output_fun *out, void *arg)
{
  mi_stats_merge_from(mi_stats_get_default());
  _mi_stats_print(&_mi_stats_main, out, arg);
}


/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
static void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out0, void *arg0)
{
  char buf[256];
  buffered_t buffer = {out0, arg0, 0, 0, 255};
  buffer.buf = buf;
  mi_output_fun *out = &mi_buffered_out;
  void *arg = &buffer;
  mi_print_header(out, arg);
  mi_stats_print_bins(stats->malloc_bins, 73U, "bin", out, arg);
  mi_stat_print(&stats->malloc_normal, "binned", (stats->malloc_normal_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_print(&stats->malloc_huge, "huge", (stats->malloc_huge_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_count_t total = {0, 0, 0};
  mi_stat_count_add_mt(&total, &stats->malloc_normal);
  mi_stat_count_add_mt(&total, &stats->malloc_huge);
  mi_stat_print_ex(&total, "total", 1, out, arg, "");
  mi_stat_total_print(&stats->malloc_requested, "malloc req", 1, out, arg);
  _mi_fprintf(out, arg, "\n");
  mi_stat_print_ex(&stats->reserved, "reserved", 1, out, arg, "");
  mi_stat_print_ex(&stats->committed, "committed", 1, out, arg, "");
  mi_stat_peak_print(&stats->reset, "reset", 1, out, arg);
  mi_stat_peak_print(&stats->purged, "purged", 1, out, arg);
  mi_stat_print_ex(&stats->page_committed, "touched", 1, out, arg, "");
  mi_stat_print(&stats->segments, "segments", -1, out, arg);
  mi_stat_print(&stats->segments_abandoned, "-abandoned", -1, out, arg);
  mi_stat_print(&stats->segments_cache, "-cached", -1, out, arg);
  mi_stat_print(&stats->pages, "pages", -1, out, arg);
  mi_stat_print(&stats->pages_abandoned, "-abandoned", -1, out, arg);
  mi_stat_counter_print(&stats->pages_extended, "-extended", out, arg);
  mi_stat_counter_print(&stats->pages_retire, "-retire", out, arg);
  mi_stat_counter_print(&stats->arena_count, "arenas", out, arg);
  mi_stat_counter_print(&stats->arena_rollback_count, "-rollback", out, arg);
  mi_stat_counter_print(&stats->mmap_calls, "mmaps", out, arg);
  mi_stat_counter_print(&stats->commit_calls, "commits", out, arg);
  mi_stat_counter_print(&stats->reset_calls, "resets", out, arg);
  mi_stat_counter_print(&stats->purge_calls, "purges", out, arg);
  mi_stat_counter_print(&stats->malloc_guarded_count, "guarded", out, arg);
  mi_stat_print(&stats->threads, "threads", -1, out, arg);
  mi_stat_counter_print_avg(&stats->page_searches, "searches", out, arg);
  _mi_fprintf(out, arg, "%10s: %5i\n", "numa nodes", _mi_os_numa_node_count());
  size_t elapsed;
  size_t user_time;
  size_t sys_time;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
  mi_process_info(&elapsed, &user_time, &sys_time, &current_rss, &peak_rss, &current_commit, &peak_commit, &page_faults);
  _mi_fprintf(out, arg, "%10s: %5zu.%03zu s\n", "elapsed", elapsed / 1000, elapsed % 1000);
  _mi_fprintf(out, arg, "%10s: user: %zu.%03zu s, system: %zu.%03zu s, faults: %zu, rss: ", "process", user_time / 1000, user_time % 1000, sys_time / 1000, sys_time % 1000, page_faults);
  mi_printf_amount((int64_t) peak_rss, 1, out, arg, "%s");
  if (peak_commit > 0)
  {
    _mi_fprintf(out, arg, ", commit: ");
    mi_printf_amount((int64_t) peak_commit, 1, out, arg, "%s");
  }
  _mi_fprintf(out, arg, "\n");
}


----------------------------
static void mi_stats_merge_from(mi_stats_t *stats)
{
  if (stats != (&_mi_stats_main))
  {
    mi_stats_add(&_mi_stats_main, stats);
    memset(stats, 0, sizeof(mi_stats_t));
  }
}


----------------------------
None
----------------------------
***/


void mi_stats_print(void *out)
{
  mi_stats_print_out((mi_output_fun *) out, 0);
}


/*** DEPENDENCIES:
void mi_stats_print_out(mi_output_fun *out, void *arg)
{
  mi_stats_merge_from(mi_stats_get_default());
  _mi_stats_print(&_mi_stats_main, out, arg);
}


----------------------------
***/


void mi_stats_merge(void)
{
  mi_stats_merge_from(mi_stats_get_default());
}


/*** DEPENDENCIES:
static void mi_stats_merge_from(mi_stats_t *stats)
{
  if (stats != (&_mi_stats_main))
  {
    mi_stats_add(&_mi_stats_main, stats);
    memset(stats, 0, sizeof(mi_stats_t));
  }
}


----------------------------
None
----------------------------
***/


static void mi_stat_adjust(mi_stat_count_t *stat, int64_t amount)
{
  if (amount == 0)
  {
    return;
  }
  if (__builtin_expect(!(!mi_is_in_main(stat)), 0))
  {
    mi_atomic_addi64_relaxed(&stat->current, amount);
    mi_atomic_addi64_relaxed(&stat->total, amount);
  }
  else
  {
    stat->current += amount;
    stat->total += amount;
  }
}


/*** DEPENDENCIES:
inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}


----------------------------
static bool mi_is_in_main(void *stat)
{
  return (((uint8_t *) stat) >= ((uint8_t *) (&_mi_stats_main))) && (((uint8_t *) stat) < (((uint8_t *) (&_mi_stats_main)) + (sizeof(mi_stats_t))));
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


void _mi_stat_adjust_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_adjust(stat, -((int64_t) amount));
}


/*** DEPENDENCIES:
static void mi_stat_adjust(mi_stat_count_t *stat, int64_t amount)
{
  if (amount == 0)
  {
    return;
  }
  if (__builtin_expect(!(!mi_is_in_main(stat)), 0))
  {
    mi_atomic_addi64_relaxed(&stat->current, amount);
    mi_atomic_addi64_relaxed(&stat->total, amount);
  }
  else
  {
    stat->current += amount;
    stat->total += amount;
  }
}


----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


void mi_thread_stats_print_out(mi_output_fun *out, void *arg)
{
  _mi_stats_print(mi_stats_get_default(), out, arg);
}


/*** DEPENDENCIES:
static void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out0, void *arg0)
{
  char buf[256];
  buffered_t buffer = {out0, arg0, 0, 0, 255};
  buffer.buf = buf;
  mi_output_fun *out = &mi_buffered_out;
  void *arg = &buffer;
  mi_print_header(out, arg);
  mi_stats_print_bins(stats->malloc_bins, 73U, "bin", out, arg);
  mi_stat_print(&stats->malloc_normal, "binned", (stats->malloc_normal_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_print(&stats->malloc_huge, "huge", (stats->malloc_huge_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_count_t total = {0, 0, 0};
  mi_stat_count_add_mt(&total, &stats->malloc_normal);
  mi_stat_count_add_mt(&total, &stats->malloc_huge);
  mi_stat_print_ex(&total, "total", 1, out, arg, "");
  mi_stat_total_print(&stats->malloc_requested, "malloc req", 1, out, arg);
  _mi_fprintf(out, arg, "\n");
  mi_stat_print_ex(&stats->reserved, "reserved", 1, out, arg, "");
  mi_stat_print_ex(&stats->committed, "committed", 1, out, arg, "");
  mi_stat_peak_print(&stats->reset, "reset", 1, out, arg);
  mi_stat_peak_print(&stats->purged, "purged", 1, out, arg);
  mi_stat_print_ex(&stats->page_committed, "touched", 1, out, arg, "");
  mi_stat_print(&stats->segments, "segments", -1, out, arg);
  mi_stat_print(&stats->segments_abandoned, "-abandoned", -1, out, arg);
  mi_stat_print(&stats->segments_cache, "-cached", -1, out, arg);
  mi_stat_print(&stats->pages, "pages", -1, out, arg);
  mi_stat_print(&stats->pages_abandoned, "-abandoned", -1, out, arg);
  mi_stat_counter_print(&stats->pages_extended, "-extended", out, arg);
  mi_stat_counter_print(&stats->pages_retire, "-retire", out, arg);
  mi_stat_counter_print(&stats->arena_count, "arenas", out, arg);
  mi_stat_counter_print(&stats->arena_rollback_count, "-rollback", out, arg);
  mi_stat_counter_print(&stats->mmap_calls, "mmaps", out, arg);
  mi_stat_counter_print(&stats->commit_calls, "commits", out, arg);
  mi_stat_counter_print(&stats->reset_calls, "resets", out, arg);
  mi_stat_counter_print(&stats->purge_calls, "purges", out, arg);
  mi_stat_counter_print(&stats->malloc_guarded_count, "guarded", out, arg);
  mi_stat_print(&stats->threads, "threads", -1, out, arg);
  mi_stat_counter_print_avg(&stats->page_searches, "searches", out, arg);
  _mi_fprintf(out, arg, "%10s: %5i\n", "numa nodes", _mi_os_numa_node_count());
  size_t elapsed;
  size_t user_time;
  size_t sys_time;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
  mi_process_info(&elapsed, &user_time, &sys_time, &current_rss, &peak_rss, &current_commit, &peak_commit, &page_faults);
  _mi_fprintf(out, arg, "%10s: %5zu.%03zu s\n", "elapsed", elapsed / 1000, elapsed % 1000);
  _mi_fprintf(out, arg, "%10s: user: %zu.%03zu s, system: %zu.%03zu s, faults: %zu, rss: ", "process", user_time / 1000, user_time % 1000, sys_time / 1000, sys_time % 1000, page_faults);
  mi_printf_amount((int64_t) peak_rss, 1, out, arg, "%s");
  if (peak_commit > 0)
  {
    _mi_fprintf(out, arg, ", commit: ");
    mi_printf_amount((int64_t) peak_commit, 1, out, arg, "%s");
  }
  _mi_fprintf(out, arg, "\n");
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


static bool mi_heap_buf_expand(mi_heap_buf_t *hbuf)
{
  if (hbuf == 0)
  {
    return 0;
  }
  if ((hbuf->buf != 0) && (hbuf->size > 0))
  {
    hbuf->buf[hbuf->size - 1] = 0;
  }
  if ((hbuf->size > (SIZE_MAX / 2)) || (!hbuf->can_realloc))
  {
    return 0;
  }
  const size_t newsize = (hbuf->size == 0) ? (mi_good_size(12 * 1024UL)) : (2 * hbuf->size);
  char * const newbuf = (char *) mi_rezalloc(hbuf->buf, newsize);
  if (newbuf == 0)
  {
    return 0;
  }
  hbuf->buf = newbuf;
  hbuf->size = newsize;
  return 1;
}


/*** DEPENDENCIES:
size_t mi_good_size(size_t size)
{
  if (size <= ((1UL << (3 + (13 + 3))) / 8))
  {
    return _mi_bin_size(mi_bin(size + (sizeof(mi_padding_t))));
  }
  else
  {
    return _mi_align_up(size + (sizeof(mi_padding_t)), _mi_os_page_size());
  }
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
void *mi_rezalloc(void *p, size_t newsize)
{
  return mi_heap_rezalloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
***/


static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


/*** DEPENDENCIES:
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
static bool mi_heap_buf_expand(mi_heap_buf_t *hbuf)
{
  if (hbuf == 0)
  {
    return 0;
  }
  if ((hbuf->buf != 0) && (hbuf->size > 0))
  {
    hbuf->buf[hbuf->size - 1] = 0;
  }
  if ((hbuf->size > (SIZE_MAX / 2)) || (!hbuf->can_realloc))
  {
    return 0;
  }
  const size_t newsize = (hbuf->size == 0) ? (mi_good_size(12 * 1024UL)) : (2 * hbuf->size);
  char * const newbuf = (char *) mi_rezalloc(hbuf->buf, newsize);
  if (newbuf == 0)
  {
    return 0;
  }
  hbuf->buf = newbuf;
  hbuf->size = newsize;
  return 1;
}


----------------------------
None
----------------------------
***/


static void mi_heap_buf_print_value(mi_heap_buf_t *hbuf, const char *name, int64_t val)
{
  char buf[128];
  _mi_snprintf(buf, 128, "  \"%s\": %lld,\n", name, val);
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
***/


static void mi_heap_buf_print_size(mi_heap_buf_t *hbuf, const char *name, size_t val, bool add_comma)
{
  char buf[128];
  _mi_snprintf(buf, 128, "    \"%s\": %zu%s\n", name, val, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
***/


static void mi_heap_buf_print_counter_value(mi_heap_buf_t *hbuf, const char *name, mi_stat_counter_t *stat)
{
  mi_heap_buf_print_value(hbuf, name, stat->total);
}


/*** DEPENDENCIES:
static void mi_heap_buf_print_value(mi_heap_buf_t *hbuf, const char *name, int64_t val)
{
  char buf[128];
  _mi_snprintf(buf, 128, "  \"%s\": %lld,\n", name, val);
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t
----------------------------
***/


void mi_stats_get(size_t stats_size, mi_stats_t *stats)
{
  if ((stats == 0) || (stats_size == 0))
  {
    return;
  }
  _mi_memzero(stats, stats_size);
  const size_t size = (stats_size > (sizeof(mi_stats_t))) ? (sizeof(mi_stats_t)) : (stats_size);
  _mi_memcpy(stats, &_mi_stats_main, size);
  stats->version = 1;
}


/*** DEPENDENCIES:
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
***/


static void mi_heap_buf_print_count(mi_heap_buf_t *hbuf, const char *prefix, mi_stat_count_t *stat, bool add_comma)
{
  char buf[128];
  _mi_snprintf(buf, 128, "%s{ \"total\": %lld, \"peak\": %lld, \"current\": %lld }%s\n", prefix, stat->total, stat->peak, stat->current, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


static void mi_heap_buf_print_count_bin(mi_heap_buf_t *hbuf, const char *prefix, mi_stat_count_t *stat, size_t bin, bool add_comma)
{
  const size_t binsize = _mi_bin_size(bin);
  const size_t pagesize = (binsize <= ((1UL << (13 + 3)) / 8)) ? (1UL << (13 + 3)) : ((binsize <= ((1UL << (3 + (13 + 3))) / 8)) ? (1UL << (3 + (13 + 3))) : (0));
  char buf[128];
  _mi_snprintf(buf, 128, "%s{ \"total\": %lld, \"peak\": %lld, \"current\": %lld, \"block_size\": %zu, \"page_size\": %zu }%s\n", prefix, stat->total, stat->peak, stat->current, binsize, pagesize, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


/*** DEPENDENCIES:
size_t _mi_bin_size(size_t bin)
{
  return _mi_heap_empty.pages[bin].block_size;
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
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


static void mi_heap_buf_print_count_value(mi_heap_buf_t *hbuf, const char *name, mi_stat_count_t *stat)
{
  char buf[128];
  _mi_snprintf(buf, 128, "  \"%s\": ", name);
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
  mi_heap_buf_print_count(hbuf, "", stat, 1);
}


/*** DEPENDENCIES:
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


----------------------------
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
static void mi_heap_buf_print_count(mi_heap_buf_t *hbuf, const char *prefix, mi_stat_count_t *stat, bool add_comma)
{
  char buf[128];
  _mi_snprintf(buf, 128, "%s{ \"total\": %lld, \"peak\": %lld, \"current\": %lld }%s\n", prefix, stat->total, stat->peak, stat->current, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t
----------------------------
***/


char *mi_stats_get_json(size_t output_size, char *output_buf)
{
  mi_heap_buf_t hbuf = {0, 0, 0, 1};
  if ((output_size > 0) && (output_buf != 0))
  {
    _mi_memzero(output_buf, output_size);
    hbuf.buf = output_buf;
    hbuf.size = output_size;
    hbuf.can_realloc = 0;
  }
  else
  {
    if (!mi_heap_buf_expand(&hbuf))
    {
      return 0;
    }
  }
  mi_heap_buf_print(&hbuf, "{\n");
  mi_heap_buf_print_value(&hbuf, "version", 1);
  mi_heap_buf_print_value(&hbuf, "mimalloc_version", 225);
  mi_heap_buf_print(&hbuf, "  \"process\": {\n");
  size_t elapsed;
  size_t user_time;
  size_t sys_time;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
  mi_process_info(&elapsed, &user_time, &sys_time, &current_rss, &peak_rss, &current_commit, &peak_commit, &page_faults);
  mi_heap_buf_print_size(&hbuf, "elapsed_msecs", elapsed, 1);
  mi_heap_buf_print_size(&hbuf, "user_msecs", user_time, 1);
  mi_heap_buf_print_size(&hbuf, "system_msecs", sys_time, 1);
  mi_heap_buf_print_size(&hbuf, "page_faults", page_faults, 1);
  mi_heap_buf_print_size(&hbuf, "rss_current", current_rss, 1);
  mi_heap_buf_print_size(&hbuf, "rss_peak", peak_rss, 1);
  mi_heap_buf_print_size(&hbuf, "commit_current", current_commit, 1);
  mi_heap_buf_print_size(&hbuf, "commit_peak", peak_commit, 0);
  mi_heap_buf_print(&hbuf, "  },\n");
  mi_stats_t *stats = &_mi_stats_main;
  mi_heap_buf_print_count_value(&hbuf, "pages", &stats->pages);
  mi_heap_buf_print_count_value(&hbuf, "reserved", &stats->reserved);
  mi_heap_buf_print_count_value(&hbuf, "committed", &stats->committed);
  mi_heap_buf_print_count_value(&hbuf, "reset", &stats->reset);
  mi_heap_buf_print_count_value(&hbuf, "purged", &stats->purged);
  mi_heap_buf_print_count_value(&hbuf, "page_committed", &stats->page_committed);
  mi_heap_buf_print_count_value(&hbuf, "pages_abandoned", &stats->pages_abandoned);
  mi_heap_buf_print_count_value(&hbuf, "threads", &stats->threads);
  mi_heap_buf_print_count_value(&hbuf, "malloc_normal", &stats->malloc_normal);
  mi_heap_buf_print_count_value(&hbuf, "malloc_huge", &stats->malloc_huge);
  mi_heap_buf_print_count_value(&hbuf, "malloc_requested", &stats->malloc_requested);
  mi_heap_buf_print_counter_value(&hbuf, "mmap_calls", &stats->mmap_calls);
  mi_heap_buf_print_counter_value(&hbuf, "commit_calls", &stats->commit_calls);
  mi_heap_buf_print_counter_value(&hbuf, "reset_calls", &stats->reset_calls);
  mi_heap_buf_print_counter_value(&hbuf, "purge_calls", &stats->purge_calls);
  mi_heap_buf_print_counter_value(&hbuf, "arena_count", &stats->arena_count);
  mi_heap_buf_print_counter_value(&hbuf, "malloc_normal_count", &stats->malloc_normal_count);
  mi_heap_buf_print_counter_value(&hbuf, "malloc_huge_count", &stats->malloc_huge_count);
  mi_heap_buf_print_counter_value(&hbuf, "malloc_guarded_count", &stats->malloc_guarded_count);
  mi_heap_buf_print_counter_value(&hbuf, "arena_rollback_count", &stats->arena_rollback_count);
  mi_heap_buf_print_counter_value(&hbuf, "arena_purges", &stats->arena_purges);
  mi_heap_buf_print_counter_value(&hbuf, "pages_extended", &stats->pages_extended);
  mi_heap_buf_print_counter_value(&hbuf, "pages_retire", &stats->pages_retire);
  mi_heap_buf_print_counter_value(&hbuf, "page_searches", &stats->page_searches);
  mi_heap_buf_print_count_value(&hbuf, "segments", &stats->segments);
  mi_heap_buf_print_count_value(&hbuf, "segments_abandoned", &stats->segments_abandoned);
  mi_heap_buf_print_count_value(&hbuf, "segments_cache", &stats->segments_cache);
  mi_heap_buf_print_count_value(&hbuf, "_segments_reserved", &stats->_segments_reserved);
  mi_heap_buf_print_counter_value(&hbuf, "pages_reclaim_on_alloc", &stats->pages_reclaim_on_alloc);
  mi_heap_buf_print_counter_value(&hbuf, "pages_reclaim_on_free", &stats->pages_reclaim_on_free);
  mi_heap_buf_print_counter_value(&hbuf, "pages_reabandon_full", &stats->pages_reabandon_full);
  mi_heap_buf_print_counter_value(&hbuf, "pages_unabandon_busy_wait", &stats->pages_unabandon_busy_wait);
  mi_heap_buf_print(&hbuf, "  \"malloc_bins\": [\n");
  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_heap_buf_print_count_bin(&hbuf, "    ", &stats->malloc_bins[i], i, i != 73U);
  }

  mi_heap_buf_print(&hbuf, "  ],\n");
  mi_heap_buf_print(&hbuf, "  \"page_bins\": [\n");
  for (size_t i = 0; i <= 73U; i += 1)
  {
    mi_heap_buf_print_count_bin(&hbuf, "    ", &stats->page_bins[i], i, i != 73U);
  }

  mi_heap_buf_print(&hbuf, "  ]\n");
  mi_heap_buf_print(&hbuf, "}\n");
  return hbuf.buf;
}


/*** DEPENDENCIES:
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
static bool mi_heap_buf_expand(mi_heap_buf_t *hbuf)
{
  if (hbuf == 0)
  {
    return 0;
  }
  if ((hbuf->buf != 0) && (hbuf->size > 0))
  {
    hbuf->buf[hbuf->size - 1] = 0;
  }
  if ((hbuf->size > (SIZE_MAX / 2)) || (!hbuf->can_realloc))
  {
    return 0;
  }
  const size_t newsize = (hbuf->size == 0) ? (mi_good_size(12 * 1024UL)) : (2 * hbuf->size);
  char * const newbuf = (char *) mi_rezalloc(hbuf->buf, newsize);
  if (newbuf == 0)
  {
    return 0;
  }
  hbuf->buf = newbuf;
  hbuf->size = newsize;
  return 1;
}


----------------------------
static void mi_heap_buf_print(mi_heap_buf_t *hbuf, const char *msg)
{
  if ((msg == 0) || (hbuf == 0))
  {
    return;
  }
  if (((hbuf->used + 1) >= hbuf->size) && (!hbuf->can_realloc))
  {
    return;
  }
  for (const char *src = msg; src[src_idx] != 0; src_idx += 1)
  {
    char c = src[src_idx];
    if ((hbuf->used + 1) >= hbuf->size)
    {
      if (!mi_heap_buf_expand(hbuf))
      {
        return;
      }
    }
    (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 523, __func__));
    hbuf->buf[hbuf->used++] = c;
  }

  unsigned int src_idx = 0;
  (hbuf->used < hbuf->size) ? ((void) 0) : (_mi_assert_fail("hbuf->used < hbuf->size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/stats.c", 526, __func__));
  hbuf->buf[hbuf->used] = 0;
}


----------------------------
static void mi_heap_buf_print_count_bin(mi_heap_buf_t *hbuf, const char *prefix, mi_stat_count_t *stat, size_t bin, bool add_comma)
{
  const size_t binsize = _mi_bin_size(bin);
  const size_t pagesize = (binsize <= ((1UL << (13 + 3)) / 8)) ? (1UL << (13 + 3)) : ((binsize <= ((1UL << (3 + (13 + 3))) / 8)) ? (1UL << (3 + (13 + 3))) : (0));
  char buf[128];
  _mi_snprintf(buf, 128, "%s{ \"total\": %lld, \"peak\": %lld, \"current\": %lld, \"block_size\": %zu, \"page_size\": %zu }%s\n", prefix, stat->total, stat->peak, stat->current, binsize, pagesize, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


----------------------------
static void mi_heap_buf_print_count_value(mi_heap_buf_t *hbuf, const char *name, mi_stat_count_t *stat)
{
  char buf[128];
  _mi_snprintf(buf, 128, "  \"%s\": ", name);
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
  mi_heap_buf_print_count(hbuf, "", stat, 1);
}


----------------------------
static void mi_heap_buf_print_counter_value(mi_heap_buf_t *hbuf, const char *name, mi_stat_counter_t *stat)
{
  mi_heap_buf_print_value(hbuf, name, stat->total);
}


----------------------------
static void mi_heap_buf_print_size(mi_heap_buf_t *hbuf, const char *name, size_t val, bool add_comma)
{
  char buf[128];
  _mi_snprintf(buf, 128, "    \"%s\": %zu%s\n", name, val, (add_comma) ? (",") : (""));
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


----------------------------
static void mi_heap_buf_print_value(mi_heap_buf_t *hbuf, const char *name, int64_t val)
{
  char buf[128];
  _mi_snprintf(buf, 128, "  \"%s\": %lld,\n", name, val);
  buf[127] = 0;
  mi_heap_buf_print(hbuf, buf);
}


----------------------------
typedef struct mi_heap_buf_s
{
  char *buf;
  size_t size;
  size_t used;
  bool can_realloc;
} mi_heap_buf_t
----------------------------
void mi_process_info(size_t *elapsed_msecs, size_t *user_msecs, size_t *system_msecs, size_t *current_rss, size_t *peak_rss, size_t *current_commit, size_t *peak_commit, size_t *page_faults)
{
  mi_process_info_t pinfo;
  memset(&pinfo, 0, sizeof(pinfo));
  pinfo.elapsed = _mi_clock_end(mi_process_start);
  pinfo.current_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.current), memory_order_relaxed);
  pinfo.peak_commit = (size_t) atomic_load_explicit((int64_t *) (&_mi_stats_main.committed.peak), memory_order_relaxed);
  pinfo.current_rss = pinfo.current_commit;
  pinfo.peak_rss = pinfo.peak_commit;
  pinfo.utime = 0;
  pinfo.stime = 0;
  pinfo.page_faults = 0;
  _mi_prim_process_info(&pinfo);
  if (elapsed_msecs != 0)
  {
    *elapsed_msecs = (pinfo.elapsed < 0) ? (0) : ((pinfo.elapsed < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.elapsed) : (PTRDIFF_MAX));
  }
  if (user_msecs != 0)
  {
    *user_msecs = (pinfo.utime < 0) ? (0) : ((pinfo.utime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.utime) : (PTRDIFF_MAX));
  }
  if (system_msecs != 0)
  {
    *system_msecs = (pinfo.stime < 0) ? (0) : ((pinfo.stime < ((mi_msecs_t) PTRDIFF_MAX)) ? ((size_t) pinfo.stime) : (PTRDIFF_MAX));
  }
  if (current_rss != 0)
  {
    *current_rss = pinfo.current_rss;
  }
  if (peak_rss != 0)
  {
    *peak_rss = pinfo.peak_rss;
  }
  if (current_commit != 0)
  {
    *current_commit = pinfo.current_commit;
  }
  if (peak_commit != 0)
  {
    *peak_commit = pinfo.peak_commit;
  }
  if (page_faults != 0)
  {
    *page_faults = pinfo.page_faults;
  }
}


----------------------------
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
***/


