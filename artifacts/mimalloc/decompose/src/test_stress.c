static void *atomic_exchange_ptr(volatile void **p, void *newval)
{
  return atomic_exchange((volatile void * *) p, newval);
}


/*** DEPENDENCIES:
***/


static uintptr_t pick(random_t r)
{
  uintptr_t x = *r;
  x ^= x >> 16;
  x *= 0x7feb352dUL;
  x ^= x >> 15;
  x *= 0x846ca68bUL;
  x ^= x >> 16;
  *r = x;
  return x;
}


/*** DEPENDENCIES:
typedef uintptr_t *random_t
----------------------------
***/


static void *thread_entry(void *param)
{
  thread_entry_fun((uintptr_t) param);
  return 0;
}


/*** DEPENDENCIES:
static void (*thread_entry_fun)(intptr_t) = &stress
----------------------------
***/


static bool chance(size_t perc, random_t r)
{
  return (pick(r) % 100) <= perc;
}


/*** DEPENDENCIES:
static uintptr_t pick(random_t r)
{
  uintptr_t x = *r;
  x ^= x >> 16;
  x *= 0x7feb352dUL;
  x ^= x >> 15;
  x *= 0x846ca68bUL;
  x ^= x >> 16;
  *r = x;
  return x;
}


----------------------------
typedef uintptr_t *random_t
----------------------------
***/


static void free_items(void *p)
{
  if (p != 0)
  {
    uintptr_t *q = (uintptr_t *) p;
    uintptr_t items = q[0] ^ cookie;
    for (uintptr_t i = 0; i < items; i += 1)
    {
      if ((q[i] ^ cookie) != (items - i))
      {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }

  }
  mi_free(p);
}


/*** DEPENDENCIES:
const uintptr_t cookie = 0x1ce4e5b9UL
----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
***/


static void *alloc_items(size_t items, random_t r)
{
  if (chance(1, r))
  {
    if (chance(1, r) && allow_large_objects)
    {
      items *= 10000;
    }
    else
      if (chance(10, r) && allow_large_objects)
    {
      items *= 1000;
    }
    else
      items *= 100;
  }
  if ((items >= 32) && (items <= 40))
  {
    items *= 2;
  }
  if (use_one_size > 0)
  {
    items = use_one_size / (sizeof(uintptr_t));
  }
  if (items == 0)
  {
    items = 1;
  }
  uintptr_t *p = (uintptr_t *) mi_calloc(items, sizeof(uintptr_t));
  if (p != 0)
  {
    for (uintptr_t i = 0; i < items; i += 1)
    {
      assert(p[i] == 0);
      p[i] = (items - i) ^ cookie;
    }

  }
  return p;
}


/*** DEPENDENCIES:
static bool allow_large_objects = 0
----------------------------
static bool chance(size_t perc, random_t r)
{
  return (pick(r) % 100) <= perc;
}


----------------------------
const uintptr_t cookie = 0x1ce4e5b9UL
----------------------------
void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


----------------------------
typedef uintptr_t *random_t
----------------------------
static size_t use_one_size = 0
----------------------------
***/


// hint:  ['allocs_ref is a mutable refrence to size_t', 'retain_ref is a mutable refrence to size_t', 'data_idx_ref is a mutable refrence to unsigned int', 'data_size_ref is a mutable refrence to size_t', 'data_top_ref is a mutable refrence to size_t', 'retain_top_ref is a mutable refrence to size_t', 'data_idx_ref is a mutable refrence to size_t']
void helper_stress_1(size_t * const allocs_ref, size_t * const retain_ref, unsigned int * const data_idx_ref, size_t * const data_size_ref, size_t * const data_top_ref, size_t * const retain_top_ref, size_t * const data_idx_ref, uintptr_t r, const size_t max_item_shift, const size_t max_item_retained_shift, void ** const data, void ** const retained)
{
  size_t allocs = *allocs_ref;
  size_t retain = *retain_ref;
  unsigned int data_idx = *data_idx_ref;
  size_t data_size = *data_size_ref;
  size_t data_top = *data_top_ref;
  size_t retain_top = *retain_top_ref;
  size_t data_idx = *data_idx_ref;
  if ((retain == 0) || (chance(50, &r) && (allocs > 0)))
  {
    allocs -= 1;
    if (data_top >= data_size)
    {
      data_size += 100000;
      data_idx = (void **) mi_realloc(data_idx, data_size * (sizeof(void *)));
    }
    data[data_top + data_idx] = alloc_items(1ULL << (pick(&r) % max_item_shift), &r);
    data_top += 1;
  }
  else
  {
    retained[retain_top] = alloc_items(1ULL << (pick(&r) % max_item_retained_shift), &r);
    retain_top += 1;
    retain -= 1;
  }
  if (chance(66, &r) && (data_top > 0))
  {
    size_t idx = pick(&r) % data_top;
    free_items(data[idx + data_idx]);
    data[idx + data_idx] = 0;
  }
  if (chance(25, &r) && (data_top > 0))
  {
    size_t data_idx = pick(&r) % data_top;
    size_t transfer_idx = pick(&r) % 1000;
    void *p = data[data_idx + data_idx];
    void *q = atomic_exchange_ptr(&transfer[transfer_idx], p);
    data[data_idx + data_idx] = q;
  }
  *allocs_ref = allocs;
  *retain_ref = retain;
  *data_idx_ref = data_idx;
  *data_size_ref = data_size;
  *data_top_ref = data_top;
  *retain_top_ref = retain_top;
  *data_idx_ref = data_idx;
}


/*** DEPENDENCIES:
static void *alloc_items(size_t items, random_t r)
{
  if (chance(1, r))
  {
    if (chance(1, r) && allow_large_objects)
    {
      items *= 10000;
    }
    else
      if (chance(10, r) && allow_large_objects)
    {
      items *= 1000;
    }
    else
      items *= 100;
  }
  if ((items >= 32) && (items <= 40))
  {
    items *= 2;
  }
  if (use_one_size > 0)
  {
    items = use_one_size / (sizeof(uintptr_t));
  }
  if (items == 0)
  {
    items = 1;
  }
  uintptr_t *p = (uintptr_t *) mi_calloc(items, sizeof(uintptr_t));
  if (p != 0)
  {
    for (uintptr_t i = 0; i < items; i += 1)
    {
      assert(p[i] == 0);
      p[i] = (items - i) ^ cookie;
    }

  }
  return p;
}


----------------------------
static void *atomic_exchange_ptr(volatile void **p, void *newval)
{
  return atomic_exchange((volatile void * *) p, newval);
}


----------------------------
static bool chance(size_t perc, random_t r)
{
  return (pick(r) % 100) <= perc;
}


----------------------------
static void free_items(void *p)
{
  if (p != 0)
  {
    uintptr_t *q = (uintptr_t *) p;
    uintptr_t items = q[0] ^ cookie;
    for (uintptr_t i = 0; i < items; i += 1)
    {
      if ((q[i] ^ cookie) != (items - i))
      {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }

  }
  mi_free(p);
}


----------------------------
void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
static uintptr_t pick(random_t r)
{
  uintptr_t x = *r;
  x ^= x >> 16;
  x *= 0x7feb352dUL;
  x ^= x >> 15;
  x *= 0x846ca68bUL;
  x ^= x >> 16;
  *r = x;
  return x;
}


----------------------------
static volatile void *transfer[1000]
----------------------------
***/


static void stress(intptr_t tid)
{
  uintptr_t r = (tid + 1) * 43;
  const size_t max_item_shift = 5;
  const size_t max_item_retained_shift = max_item_shift + 2;
  size_t allocs = (100 * ((size_t) SCALE)) * ((tid % 8) + 1);
  size_t retain = allocs / 2;
  void **data = 0;
  unsigned int data_idx = 0;
  size_t data_size = 0;
  size_t data_top = 0;
  void **retained = (void **) mi_calloc(retain, sizeof(void *));
  size_t retain_top = 0;
  while ((allocs > 0) || (retain > 0))
  {
    helper_stress_1(&allocs, &retain, &data_idx, &data_size, &data_top, &retain_top, &data_idx, r, max_item_shift, max_item_retained_shift, data, retained);
  }

  for (size_t i = 0; i < retain_top; i += 1)
  {
    free_items(retained[i]);
  }

  for (size_t i = 0; i < data_top; i += 1)
  {
    free_items(data[i + data_idx]);
  }

  mi_free(retained);
  mi_free(data);
}


/*** DEPENDENCIES:
static int SCALE = 50
----------------------------
static void free_items(void *p)
{
  if (p != 0)
  {
    uintptr_t *q = (uintptr_t *) p;
    uintptr_t items = q[0] ^ cookie;
    for (uintptr_t i = 0; i < items; i += 1)
    {
      if ((q[i] ^ cookie) != (items - i))
      {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }

  }
  mi_free(p);
}


----------------------------
void helper_stress_1(size_t * const allocs_ref, size_t * const retain_ref, unsigned int * const data_idx_ref, size_t * const data_size_ref, size_t * const data_top_ref, size_t * const retain_top_ref, size_t * const data_idx_ref, uintptr_t r, const size_t max_item_shift, const size_t max_item_retained_shift, void ** const data, void ** const retained)
{
  size_t allocs = *allocs_ref;
  size_t retain = *retain_ref;
  unsigned int data_idx = *data_idx_ref;
  size_t data_size = *data_size_ref;
  size_t data_top = *data_top_ref;
  size_t retain_top = *retain_top_ref;
  size_t data_idx = *data_idx_ref;
  if ((retain == 0) || (chance(50, &r) && (allocs > 0)))
  {
    allocs -= 1;
    if (data_top >= data_size)
    {
      data_size += 100000;
      data_idx = (void **) mi_realloc(data_idx, data_size * (sizeof(void *)));
    }
    data[data_top + data_idx] = alloc_items(1ULL << (pick(&r) % max_item_shift), &r);
    data_top += 1;
  }
  else
  {
    retained[retain_top] = alloc_items(1ULL << (pick(&r) % max_item_retained_shift), &r);
    retain_top += 1;
    retain -= 1;
  }
  if (chance(66, &r) && (data_top > 0))
  {
    size_t idx = pick(&r) % data_top;
    free_items(data[idx + data_idx]);
    data[idx + data_idx] = 0;
  }
  if (chance(25, &r) && (data_top > 0))
  {
    size_t data_idx = pick(&r) % data_top;
    size_t transfer_idx = pick(&r) % 1000;
    void *p = data[data_idx + data_idx];
    void *q = atomic_exchange_ptr(&transfer[transfer_idx], p);
    data[data_idx + data_idx] = q;
  }
  *allocs_ref = allocs;
  *retain_ref = retain;
  *data_idx_ref = data_idx;
  *data_size_ref = data_size;
  *data_top_ref = data_top;
  *retain_top_ref = retain_top;
  *data_idx_ref = data_idx;
}


----------------------------
void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
***/


static void run_os_threads(size_t nthreads, void (*fun)(intptr_t))
{
  thread_entry_fun = fun;
  pthread_t *threads = (pthread_t *) mi_calloc(nthreads, sizeof(pthread_t));
  memset(threads, 0, (sizeof(pthread_t)) * nthreads);
  const size_t start = (main_participates) ? (1) : (0);
  for (size_t i = start; i < nthreads; i += 1)
  {
    pthread_create(&threads[i], 0, &thread_entry, (void *) i);
  }

  if (main_participates)
  {
    fun(0);
  }
  for (size_t i = start; i < nthreads; i += 1)
  {
    pthread_join(threads[i], 0);
  }

  mi_free(threads);
}


/*** DEPENDENCIES:
static bool main_participates = 0
----------------------------
void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
static void *thread_entry(void *param)
{
  thread_entry_fun((uintptr_t) param);
  return 0;
}


----------------------------
static void (*thread_entry_fun)(intptr_t) = &stress
----------------------------
***/


static void test_stress(void)
{
  uintptr_t r = rand();
  for (int n = 0; n < ITER; n += 1)
  {
    run_os_threads(THREADS, &stress);
    for (int i = 0; i < 1000; i += 1)
    {
      if (chance(50, &r) || ((n + 1) == ITER))
      {
        void *p = atomic_exchange_ptr(&transfer[i], 0);
        free_items(p);
      }
    }

    if (((n + 1) % 10) == 0)
    {
      printf("- iterations left: %3d\n", ITER - (n + 1));
      mi_debug_show_arenas();
    }
  }

  for (int i = 0; i < 1000; i += 1)
  {
    void *p = atomic_exchange_ptr(&transfer[i], 0);
    if (p != 0)
    {
      free_items(p);
    }
  }

}


/*** DEPENDENCIES:
static int ITER = 50
----------------------------
static int THREADS = 32
----------------------------
static void *atomic_exchange_ptr(volatile void **p, void *newval)
{
  return atomic_exchange((volatile void * *) p, newval);
}


----------------------------
static bool chance(size_t perc, random_t r)
{
  return (pick(r) % 100) <= perc;
}


----------------------------
static void free_items(void *p)
{
  if (p != 0)
  {
    uintptr_t *q = (uintptr_t *) p;
    uintptr_t items = q[0] ^ cookie;
    for (uintptr_t i = 0; i < items; i += 1)
    {
      if ((q[i] ^ cookie) != (items - i))
      {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }

  }
  mi_free(p);
}


----------------------------
void mi_debug_show_arenas(void)
{
  mi_debug_show_arenas_ex(1, 0);
}


----------------------------
static void run_os_threads(size_t nthreads, void (*fun)(intptr_t))
{
  thread_entry_fun = fun;
  pthread_t *threads = (pthread_t *) mi_calloc(nthreads, sizeof(pthread_t));
  memset(threads, 0, (sizeof(pthread_t)) * nthreads);
  const size_t start = (main_participates) ? (1) : (0);
  for (size_t i = start; i < nthreads; i += 1)
  {
    pthread_create(&threads[i], 0, &thread_entry, (void *) i);
  }

  if (main_participates)
  {
    fun(0);
  }
  for (size_t i = start; i < nthreads; i += 1)
  {
    pthread_join(threads[i], 0);
  }

  mi_free(threads);
}


----------------------------
static void stress(intptr_t tid)
{
  uintptr_t r = (tid + 1) * 43;
  const size_t max_item_shift = 5;
  const size_t max_item_retained_shift = max_item_shift + 2;
  size_t allocs = (100 * ((size_t) SCALE)) * ((tid % 8) + 1);
  size_t retain = allocs / 2;
  void **data = 0;
  unsigned int data_idx = 0;
  size_t data_size = 0;
  size_t data_top = 0;
  void **retained = (void **) mi_calloc(retain, sizeof(void *));
  size_t retain_top = 0;
  while ((allocs > 0) || (retain > 0))
  {
    helper_stress_1(&allocs, &retain, &data_idx, &data_size, &data_top, &retain_top, &data_idx, r, max_item_shift, max_item_retained_shift, data, retained);
  }

  for (size_t i = 0; i < retain_top; i += 1)
  {
    free_items(retained[i]);
  }

  for (size_t i = 0; i < data_top; i += 1)
  {
    free_items(data[i + data_idx]);
  }

  mi_free(retained);
  mi_free(data);
}


----------------------------
static volatile void *transfer[1000]
----------------------------
***/


int main(int argc, char **argv)
{
  if (argc >= 2)
  {
    char *end;
    long n = strtol(argv[1], &end, 10);
    if (n > 0)
    {
      THREADS = n;
    }
  }
  if (argc >= 3)
  {
    char *end;
    long n = strtol(argv[2], &end, 10);
    if (n > 0)
    {
      SCALE = n;
    }
  }
  if (argc >= 4)
  {
    char *end;
    long n = strtol(argv[3], &end, 10);
    if (n > 0)
    {
      ITER = n;
    }
  }
  if (SCALE > 100)
  {
    allow_large_objects = 1;
  }
  printf("Using %d threads with a %d%% load-per-thread and %d iterations %s\n", THREADS, SCALE, ITER, (allow_large_objects) ? ("(allow large objects)") : (""));
  mi_stats_reset();
  srand(0x7feb352d);
  test_stress();
  mi_debug_show_arenas();
  mi_collect(1);
  char *json = mi_stats_get_json(0, 0);
  if (json != 0)
  {
    fputs(json, stderr);
    mi_free(json);
  }
  mi_collect(1);
  mi_stats_print(0);
  return 0;
}


/*** DEPENDENCIES:
static int ITER = 50
----------------------------
static int SCALE = 50
----------------------------
static int THREADS = 32
----------------------------
static bool allow_large_objects = 0
----------------------------
void mi_collect(bool force)
{
  mi_heap_collect(mi_prim_get_default_heap(), force);
}


----------------------------
void mi_debug_show_arenas(void)
{
  mi_debug_show_arenas_ex(1, 0);
}


----------------------------
void mi_free(void *p)
{
  mi_page_t * const page = mi_validate_ptr_page(p, "mi_free");
  if (__builtin_expect(!(!(page == 0)), 0))
  {
    return;
  }
  ((p != 0) && (page != 0)) ? ((void) 0) : (_mi_assert_fail("p!=NULL && page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/free.c", 169, __func__));
  const mi_threadid_t xtid = _mi_prim_thread_id() ^ mi_page_xthread_id(page);
  if (__builtin_expect(!(!(xtid == 0)), 1))
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_local(page, block, 1, 0);
  }
  else
    if (xtid <= 0x03UL)
  {
    mi_free_generic_local(page, p);
  }
  else
    if ((xtid & 0x03UL) == 0)
  {
    mi_block_t * const block = mi_validate_block_from_ptr(page, p);
    mi_free_block_mt(page, block);
  }
  else
  {
    mi_free_generic_mt(page, p);
  }
}


----------------------------
char *mi_stats_get_json(size_t output_size, char *output_buf)
{
  mi_stats_merge();
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
  mi_heap_buf_print_value(&hbuf, "version", 2);
  mi_heap_buf_print_value(&hbuf, "mimalloc_version", 316);
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
  mi_stats_t *stats = &_mi_subproc()->stats;
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

  mi_heap_buf_print(&hbuf, "  ],\n");
  mi_heap_buf_print(&hbuf, "  \"chunk_bins\": [\n");
  for (size_t i = 0; i < MI_CBIN_COUNT; i += 1)
  {
    mi_heap_buf_print_count_cbin(&hbuf, "    ", &stats->chunk_bins[i], (mi_chunkbin_t) i, i != (MI_CBIN_COUNT - 1));
  }

  mi_heap_buf_print(&hbuf, "  ]\n");
  mi_heap_buf_print(&hbuf, "}\n");
  return hbuf.buf;
}


----------------------------
void mi_stats_print(void *out)
{
  mi_stats_print_out((mi_output_fun *) out, 0);
}


----------------------------
void mi_stats_reset(void)
{
  mi_stats_t *stats = mi_get_tld_stats();
  mi_subproc_t *subproc = _mi_subproc();
  if (stats != (&subproc->stats))
  {
    _mi_memzero(stats, sizeof(mi_stats_t));
  }
  _mi_memzero(&subproc->stats, sizeof(mi_stats_t));
  _mi_stats_init();
}


----------------------------
static void test_stress(void)
{
  uintptr_t r = rand();
  for (int n = 0; n < ITER; n += 1)
  {
    run_os_threads(THREADS, &stress);
    for (int i = 0; i < 1000; i += 1)
    {
      if (chance(50, &r) || ((n + 1) == ITER))
      {
        void *p = atomic_exchange_ptr(&transfer[i], 0);
        free_items(p);
      }
    }

    if (((n + 1) % 10) == 0)
    {
      printf("- iterations left: %3d\n", ITER - (n + 1));
      mi_debug_show_arenas();
    }
  }

  for (int i = 0; i < 1000; i += 1)
  {
    void *p = atomic_exchange_ptr(&transfer[i], 0);
    if (p != 0)
    {
      free_items(p);
    }
  }

}


----------------------------
***/


