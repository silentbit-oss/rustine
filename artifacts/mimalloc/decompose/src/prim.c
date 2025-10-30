bool _mi_is_redirected(void)
{
  return 0;
}


/*** DEPENDENCIES:
***/


bool _mi_allocator_init(const char **message)
{
  if (message != 0)
  {
    *message = 0;
  }
  return 1;
}


/*** DEPENDENCIES:
***/


void _mi_allocator_done(void)
{
}


/*** DEPENDENCIES:
***/


int _mi_prim_free(void *addr, size_t size)
{
  if (size == 0)
  {
    return 0;
  }
  bool err = munmap(addr, size) == (-1);
  return (err) ? (errno) : (0);
}


/*** DEPENDENCIES:
***/


int _mi_prim_reuse(void *start, size_t size)
{
  (void) start;
  (void) size;
  return 0;
}


/*** DEPENDENCIES:
***/


size_t _mi_prim_numa_node(void)
{
  return 0;
}


/*** DEPENDENCIES:
***/


mi_msecs_t _mi_prim_clock_now(void)
{
  return (mi_msecs_t) clock();
}


/*** DEPENDENCIES:
***/


void _mi_prim_out_stderr(const char *msg)
{
  fputs(msg, stderr);
}


/*** DEPENDENCIES:
***/


inline static int mi_prim_open(const char *fpath, int open_flags)
{
  return open(fpath, open_flags);
}


/*** DEPENDENCIES:
***/


inline static ssize_t mi_prim_read(int fd, void *buf, size_t bufsize)
{
  return read(fd, buf, bufsize);
}


/*** DEPENDENCIES:
***/


inline static int mi_prim_close(int fd)
{
  return close(fd);
}


/*** DEPENDENCIES:
***/


inline static int mi_prim_access(const char *fpath, int mode)
{
  return access(fpath, mode);
}


/*** DEPENDENCIES:
***/


static int unix_madvise(void *addr, size_t size, int advice)
{
  int res = madvise(addr, size, advice);
  return (res == 0) ? (0) : (errno);
}


/*** DEPENDENCIES:
***/


static void *unix_mmap_prim(void *addr, size_t size, int protect_flags, int flags, int fd)
{
  void *p = mmap(addr, size, protect_flags, flags, fd, 0);
  return p;
}


/*** DEPENDENCIES:
***/


static int unix_mmap_fd(void)
{
  return -1;
}


/*** DEPENDENCIES:
***/


static void unix_mprotect_hint(int err)
{
  (void) err;
}


/*** DEPENDENCIES:
***/


static long mi_prim_mbind(void *start, unsigned long len, unsigned long mode, const unsigned long *nmask, unsigned long maxnode, unsigned flags)
{
  (void) start;
  (void) len;
  (void) mode;
  (void) nmask;
  (void) maxnode;
  (void) flags;
  return 0;
}


/*** DEPENDENCIES:
***/


static mi_msecs_t timeval_secs(const struct timeval *tv)
{
  return (((mi_msecs_t) tv->tv_sec) * 1000L) + (((mi_msecs_t) tv->tv_usec) / 1000L);
}


/*** DEPENDENCIES:
***/


static char **mi_get_environ(void)
{
  return environ;
}


/*** DEPENDENCIES:
extern char **environ
----------------------------
***/


bool _mi_prim_getenv(const char *name, char *result, size_t result_size)
{
  if (name == 0)
  {
    return 0;
  }
  const size_t len = _mi_strlen(name);
  if (len == 0)
  {
    return 0;
  }
  char **env = mi_get_environ();
  if (env == 0)
  {
    return 0;
  }
  for (int i = 0; (i < 10000) && (env[i] != 0); i += 1)
  {
    const char *s = env[i];
    if ((_mi_strnicmp(name, s, len) == 0) && (s[len] == '='))
    {
      _mi_strlcpy(result, (s + len) + 1, result_size);
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
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
size_t _mi_strlen(const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while (s[len] != 0)
  {
    len += 1;
  }

  return len;
}


----------------------------
int _mi_strnicmp(const char *s, const char *t, size_t n)
{
  unsigned int t_idx = 0;
  unsigned int s_idx = 0;
  if (n == 0)
  {
    return 0;
  }
  for (; ((s[s_idx] != 0) && (t[t_idx] != 0)) && (n > 0); s_idx += 1, t_idx += 1, n -= 1)
  {
    if (_mi_toupper(*(&s[s_idx])) != _mi_toupper(*(&t[t_idx])))
    {
      break;
    }
  }

  return (n == 0) ? (0) : (s[s_idx] - t[t_idx]);
}


----------------------------
static char **mi_get_environ(void)
{
  return environ;
}


----------------------------
***/


int _mi_prim_commit(void *start, size_t size, bool *is_zero)
{
  *is_zero = 0;
  int err = mprotect(start, size, PROT_READ | PROT_WRITE);
  if (err != 0)
  {
    err = errno;
    unix_mprotect_hint(err);
  }
  return err;
}


/*** DEPENDENCIES:
static void unix_mprotect_hint(int err)
{
  (void) err;
}


----------------------------
***/


static void *unix_mmap_prim_aligned(void *addr, size_t size, size_t try_alignment, int protect_flags, int flags, int fd)
{
  (void) try_alignment;
  void *p = 0;
  unsigned int p_idx = 0;
  if (addr == 0)
  {
    void *hint = _mi_os_get_aligned_hint(try_alignment, size);
    if (hint != 0)
    {
      p_idx = unix_mmap_prim(hint, size, protect_flags, flags, fd);
      if (((&p[p_idx]) == MAP_FAILED) || (!_mi_is_aligned(p, try_alignment)))
      {
        int err = errno;
        _mi_trace_message("unable to directly request hinted aligned OS memory (error: %d (0x%x), size: 0x%zx bytes, alignment: 0x%zx, hint address: %p)\n", err, err, size, try_alignment, hint);
      }
      if ((&p[p_idx]) != MAP_FAILED)
      {
        return p;
      }
    }
  }
  p_idx = unix_mmap_prim(addr, size, protect_flags, flags, fd);
  if ((&p[p_idx]) != MAP_FAILED)
  {
    return p;
  }
  return 0;
}


/*** DEPENDENCIES:
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 380, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size)
{
  if ((try_alignment <= 1) || (try_alignment > (1UL << (9 + (13 + 3)))))
  {
    return 0;
  }
  if (mi_os_mem_config.virtual_address_bits < 46)
  {
    return 0;
  }
  size = _mi_align_up(size, 1UL << (9 + (13 + 3)));
  if (size > (1 * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  uintptr_t hint = atomic_fetch_add_explicit(&aligned_base, size, memory_order_acq_rel);
  if ((hint == 0) || (hint > (((uintptr_t) 30) << 40)))
  {
    uintptr_t init = ((uintptr_t) 2) << 40;
    uintptr_t expected = hint + size;
    atomic_compare_exchange_strong_explicit(&aligned_base, &expected, init, memory_order_acq_rel, memory_order_acquire);
    hint = atomic_fetch_add_explicit(&aligned_base, size, memory_order_acq_rel);
  }
  if ((hint % try_alignment) != 0)
  {
    return 0;
  }
  return (void *) hint;
}


----------------------------
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


----------------------------
static void *unix_mmap_prim(void *addr, size_t size, int protect_flags, int flags, int fd)
{
  void *p = mmap(addr, size, protect_flags, flags, fd, 0);
  return p;
}


----------------------------
***/


static void *unix_mmap(void *addr, size_t size, size_t try_alignment, int protect_flags, bool large_only, bool allow_large, bool *is_large)
{
  void *p = 0;
  unsigned int p_idx = 0;
  const int fd = unix_mmap_fd();
  int flags = MAP_PRIVATE | MAP_ANON;
  if (_mi_os_has_overcommit())
  {
    flags |= 0;
  }
  if (allow_large && (large_only || (_mi_os_use_large_page(size, try_alignment) && (mi_option_get(mi_option_allow_large_os_pages) == 1))))
  {
    static _Atomic size_t large_page_try_ok;
    size_t try_ok = atomic_load_explicit(&large_page_try_ok, memory_order_acquire);
    if ((!large_only) && (try_ok > 0))
    {
      atomic_compare_exchange_strong_explicit(&large_page_try_ok, &try_ok, try_ok - 1, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
      int lflags = flags & (~0);
      int lfd = fd;
      {
      }
      if (large_only || (lflags != flags))
      {
        *is_large = 1;
        p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, lflags, lfd);
        if (large_only)
        {
          return p;
        }
        if ((&p[p_idx]) == 0)
        {
          atomic_store_explicit(&large_page_try_ok, (size_t) 8, memory_order_release);
        }
      }
    }
  }
  if ((&p[p_idx]) == 0)
  {
    *is_large = 0;
    p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, flags, fd);
    if ((&p[p_idx]) != 0)
    {
    }
  }
  return p;
}


/*** DEPENDENCIES:
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}


----------------------------
static void *unix_mmap_prim_aligned(void *addr, size_t size, size_t try_alignment, int protect_flags, int flags, int fd)
{
  (void) try_alignment;
  void *p = 0;
  unsigned int p_idx = 0;
  if (addr == 0)
  {
    void *hint = _mi_os_get_aligned_hint(try_alignment, size);
    if (hint != 0)
    {
      p_idx = unix_mmap_prim(hint, size, protect_flags, flags, fd);
      if (((&p[p_idx]) == MAP_FAILED) || (!_mi_is_aligned(p, try_alignment)))
      {
        int err = errno;
        _mi_trace_message("unable to directly request hinted aligned OS memory (error: %d (0x%x), size: 0x%zx bytes, alignment: 0x%zx, hint address: %p)\n", err, err, size, try_alignment, hint);
      }
      if ((&p[p_idx]) != MAP_FAILED)
      {
        return p;
      }
    }
  }
  p_idx = unix_mmap_prim(addr, size, protect_flags, flags, fd);
  if ((&p[p_idx]) != MAP_FAILED)
  {
    return p;
  }
  return 0;
}


----------------------------
static int unix_mmap_fd(void)
{
  return -1;
}


----------------------------
bool _mi_os_use_large_page(size_t size, size_t alignment)
{
  if ((mi_os_mem_config.large_page_size == 0) || (!mi_option_is_enabled(mi_option_allow_large_os_pages)))
  {
    return 0;
  }
  return ((size % mi_os_mem_config.large_page_size) == 0) && ((alignment % mi_os_mem_config.large_page_size) == 0);
}


----------------------------
None
----------------------------
***/


int _mi_prim_alloc(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **addr)
{
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/prim/unix/prim.c", 387, __func__));
  (commit || (!allow_large)) ? ((void) 0) : (_mi_assert_fail("commit || !allow_large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/prim/unix/prim.c", 388, __func__));
  (try_alignment > 0) ? ((void) 0) : (_mi_assert_fail("try_alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/prim/unix/prim.c", 389, __func__));
  if (((((hint_addr == 0) && (size >= (8 * (2 * (1024UL * 1024UL))))) && (try_alignment > 1)) && _mi_is_power_of_two(try_alignment)) && (try_alignment < (2 * (1024UL * 1024UL))))
  {
    try_alignment = 2 * (1024UL * 1024UL);
  }
  *is_zero = 1;
  int protect_flags = (commit) ? (PROT_WRITE | PROT_READ) : (PROT_NONE);
  *addr = unix_mmap(hint_addr, size, try_alignment, protect_flags, 0, allow_large, is_large);
  return ((*addr) != 0) ? (0) : (errno);
}


/*** DEPENDENCIES:
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
static void *unix_mmap(void *addr, size_t size, size_t try_alignment, int protect_flags, bool large_only, bool allow_large, bool *is_large)
{
  void *p = 0;
  unsigned int p_idx = 0;
  const int fd = unix_mmap_fd();
  int flags = MAP_PRIVATE | MAP_ANON;
  if (_mi_os_has_overcommit())
  {
    flags |= 0;
  }
  if (allow_large && (large_only || (_mi_os_use_large_page(size, try_alignment) && (mi_option_get(mi_option_allow_large_os_pages) == 1))))
  {
    static _Atomic size_t large_page_try_ok;
    size_t try_ok = atomic_load_explicit(&large_page_try_ok, memory_order_acquire);
    if ((!large_only) && (try_ok > 0))
    {
      atomic_compare_exchange_strong_explicit(&large_page_try_ok, &try_ok, try_ok - 1, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
      int lflags = flags & (~0);
      int lfd = fd;
      {
      }
      if (large_only || (lflags != flags))
      {
        *is_large = 1;
        p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, lflags, lfd);
        if (large_only)
        {
          return p;
        }
        if ((&p[p_idx]) == 0)
        {
          atomic_store_explicit(&large_page_try_ok, (size_t) 8, memory_order_release);
        }
      }
    }
  }
  if ((&p[p_idx]) == 0)
  {
    *is_large = 0;
    p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, flags, fd);
    if ((&p[p_idx]) != 0)
    {
    }
  }
  return p;
}


----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
None
----------------------------
***/


int _mi_prim_protect(void *start, size_t size, bool protect)
{
  int err = mprotect(start, size, (protect) ? (PROT_NONE) : (PROT_READ | PROT_WRITE));
  if (err != 0)
  {
    err = errno;
  }
  unix_mprotect_hint(err);
  return err;
}


/*** DEPENDENCIES:
static void unix_mprotect_hint(int err)
{
  (void) err;
}


----------------------------
***/


int _mi_prim_decommit(void *start, size_t size, bool *needs_recommit)
{
  int err = 0;
  err = unix_madvise(start, size, MADV_DONTNEED);
  *needs_recommit = 1;
  mprotect(start, size, PROT_NONE);
  return err;
}


/*** DEPENDENCIES:
static int unix_madvise(void *addr, size_t size, int advice)
{
  int res = madvise(addr, size, advice);
  return (res == 0) ? (0) : (errno);
}


----------------------------
***/


size_t _mi_prim_numa_node_count(void)
{
  char buf[128];
  unsigned node = 0;
  for (node = 0; node < 256; node += 1)
  {
    _mi_snprintf(buf, 127, "/sys/devices/system/node/node%u", node + 1);
    if (mi_prim_access(buf, R_OK) != 0)
    {
      break;
    }
  }

  return node + 1;
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
inline static int mi_prim_access(const char *fpath, int mode)
{
  return access(fpath, mode);
}


----------------------------
***/


int _mi_prim_reset(void *start, size_t size)
{
  int err = 0;
  err = unix_madvise(start, size, MADV_DONTNEED);
  return err;
}


/*** DEPENDENCIES:
static int unix_madvise(void *addr, size_t size, int advice)
{
  int res = madvise(addr, size, advice);
  return (res == 0) ? (0) : (errno);
}


----------------------------
***/


bool _mi_prim_random_buf(void *buf, size_t buf_len)
{
  int flags = O_RDONLY;
  int fd = mi_prim_open("/dev/urandom", flags);
  if (fd < 0)
  {
    return 0;
  }
  size_t count = 0;
  while (count < buf_len)
  {
    ssize_t ret = mi_prim_read(fd, ((char *) buf) + count, buf_len - count);
    if (ret <= 0)
    {
      if ((errno != 11) && (errno != EINTR))
      {
        break;
      }
    }
    else
    {
      count += ret;
    }
  }

  mi_prim_close(fd);
  return count == buf_len;
}


/*** DEPENDENCIES:
inline static int mi_prim_close(int fd)
{
  return close(fd);
}


----------------------------
inline static int mi_prim_open(const char *fpath, int open_flags)
{
  return open(fpath, open_flags);
}


----------------------------
inline static ssize_t mi_prim_read(int fd, void *buf, size_t bufsize)
{
  return read(fd, buf, bufsize);
}


----------------------------
***/


void _mi_prim_thread_associate_default_heap(mi_heap_t *heap)
{
  if (_mi_heap_default_key != ((pthread_key_t) (-1)))
  {
    pthread_setspecific(_mi_heap_default_key, heap);
  }
}


/*** DEPENDENCIES:
pthread_key_t _mi_heap_default_key = (pthread_key_t) (-1)
----------------------------
None
----------------------------
***/


int _mi_prim_alloc_huge_os_pages(void *hint_addr, size_t size, int numa_node, bool *is_zero, void **addr)
{
  bool is_large = 1;
  *is_zero = 1;
  *addr = unix_mmap(hint_addr, size, 1UL << (9 + (13 + 3)), PROT_READ | PROT_WRITE, 1, 1, &is_large);
  if ((((*addr) != 0) && (numa_node >= 0)) && (numa_node < (8 * (1 << 3))))
  {
    unsigned long numa_mask = 1UL << numa_node;
    long err = mi_prim_mbind(*addr, size, 1, &numa_mask, 8 * (1 << 3), 0);
    if (err != 0)
    {
      err = errno;
      _mi_warning_message("failed to bind huge (1GiB) pages to numa node %d (error: %d (0x%x))\n", numa_node, err, err);
    }
  }
  return ((*addr) != 0) ? (0) : (errno);
}


/*** DEPENDENCIES:
static void *unix_mmap(void *addr, size_t size, size_t try_alignment, int protect_flags, bool large_only, bool allow_large, bool *is_large)
{
  void *p = 0;
  unsigned int p_idx = 0;
  const int fd = unix_mmap_fd();
  int flags = MAP_PRIVATE | MAP_ANON;
  if (_mi_os_has_overcommit())
  {
    flags |= 0;
  }
  if (allow_large && (large_only || (_mi_os_use_large_page(size, try_alignment) && (mi_option_get(mi_option_allow_large_os_pages) == 1))))
  {
    static _Atomic size_t large_page_try_ok;
    size_t try_ok = atomic_load_explicit(&large_page_try_ok, memory_order_acquire);
    if ((!large_only) && (try_ok > 0))
    {
      atomic_compare_exchange_strong_explicit(&large_page_try_ok, &try_ok, try_ok - 1, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
      int lflags = flags & (~0);
      int lfd = fd;
      {
      }
      if (large_only || (lflags != flags))
      {
        *is_large = 1;
        p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, lflags, lfd);
        if (large_only)
        {
          return p;
        }
        if ((&p[p_idx]) == 0)
        {
          atomic_store_explicit(&large_page_try_ok, (size_t) 8, memory_order_release);
        }
      }
    }
  }
  if ((&p[p_idx]) == 0)
  {
    *is_large = 0;
    p_idx = unix_mmap_prim_aligned(addr, size, try_alignment, protect_flags, flags, fd);
    if ((&p[p_idx]) != 0)
    {
    }
  }
  return p;
}


----------------------------
static long mi_prim_mbind(void *start, unsigned long len, unsigned long mode, const unsigned long *nmask, unsigned long maxnode, unsigned flags)
{
  (void) start;
  (void) len;
  (void) mode;
  (void) nmask;
  (void) maxnode;
  (void) flags;
  return 0;
}


----------------------------
None
----------------------------
***/


static bool unix_detect_overcommit(void)
{
  bool os_overcommit = 1;
  int fd = mi_prim_open("/proc/sys/vm/overcommit_memory", O_RDONLY);
  if (fd >= 0)
  {
    char buf[32];
    ssize_t nread = mi_prim_read(fd, &buf, sizeof(buf));
    mi_prim_close(fd);
    if (nread >= 1)
    {
      os_overcommit = (buf[0] == '0') || (buf[0] == '1');
    }
  }
  return os_overcommit;
}


/*** DEPENDENCIES:
inline static int mi_prim_close(int fd)
{
  return close(fd);
}


----------------------------
inline static int mi_prim_open(const char *fpath, int open_flags)
{
  return open(fpath, open_flags);
}


----------------------------
inline static ssize_t mi_prim_read(int fd, void *buf, size_t bufsize)
{
  return read(fd, buf, bufsize);
}


----------------------------
***/


void _mi_prim_mem_init(mi_os_mem_config_t *config)
{
  long psize = sysconf(_SC_PAGESIZE);
  if (psize > 0)
  {
    config->page_size = (size_t) psize;
    config->alloc_granularity = (size_t) psize;
  }
  config->large_page_size = 2 * (1024UL * 1024UL);
  config->has_overcommit = unix_detect_overcommit();
  config->has_partial_free = 1;
  config->has_virtual_reserve = 1;
}


/*** DEPENDENCIES:
typedef struct mi_os_mem_config_s
{
  size_t page_size;
  size_t large_page_size;
  size_t alloc_granularity;
  size_t physical_memory_in_kib;
  size_t virtual_address_bits;
  bool has_overcommit;
  bool has_partial_free;
  bool has_virtual_reserve;
} mi_os_mem_config_t
----------------------------
static bool unix_detect_overcommit(void)
{
  bool os_overcommit = 1;
  int fd = mi_prim_open("/proc/sys/vm/overcommit_memory", O_RDONLY);
  if (fd >= 0)
  {
    char buf[32];
    ssize_t nread = mi_prim_read(fd, &buf, sizeof(buf));
    mi_prim_close(fd);
    if (nread >= 1)
    {
      os_overcommit = (buf[0] == '0') || (buf[0] == '1');
    }
  }
  return os_overcommit;
}


----------------------------
***/


void _mi_prim_process_info(mi_process_info_t *pinfo)
{
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);
  pinfo->utime = timeval_secs(&rusage.ru_utime);
  pinfo->stime = timeval_secs(&rusage.ru_stime);
  pinfo->page_faults = rusage.ru_majflt;
  pinfo->peak_rss = rusage.ru_maxrss * 1024;
}


/*** DEPENDENCIES:
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
static mi_msecs_t timeval_secs(const struct timeval *tv)
{
  return (((mi_msecs_t) tv->tv_sec) * 1000L) + (((mi_msecs_t) tv->tv_usec) / 1000L);
}


----------------------------
***/


void _mi_prim_thread_done_auto_done(void)
{
  if (_mi_heap_default_key != ((pthread_key_t) (-1)))
  {
    pthread_key_delete(_mi_heap_default_key);
  }
}


/*** DEPENDENCIES:
pthread_key_t _mi_heap_default_key = (pthread_key_t) (-1)
----------------------------
***/


static void mi_process_attach(void)
{
  _mi_auto_process_init();
}


/*** DEPENDENCIES:
void _mi_auto_process_init(void)
{
  mi_heap_main_init();
  os_preloading = 0;
  (_mi_is_main_thread()) ? ((void) 0) : (_mi_assert_fail("_mi_is_main_thread()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 587, __func__));
  _mi_options_init();
  mi_process_setup_auto_thread_done();
  mi_process_init();
  if (_mi_is_redirected())
  {
    _mi_verbose_message("malloc is redirected.\n");
  }
  const char *msg = 0;
  _mi_allocator_init(&msg);
  if ((msg != 0) && (mi_option_is_enabled(mi_option_verbose) || mi_option_is_enabled(mi_option_show_errors)))
  {
    _mi_fputs(0, 0, 0, msg);
  }
  _mi_random_reinit_if_weak(&_mi_heap_main.random);
}


----------------------------
***/


static void mi_process_detach(void)
{
  _mi_auto_process_done();
}


/*** DEPENDENCIES:
void _mi_auto_process_done(void)
{
  if (_mi_option_get_fast(mi_option_destroy_on_exit) > 1)
  {
    return;
  }
  mi_process_done();
}


----------------------------
***/


