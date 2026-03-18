bool check_zero_init(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0;
  }

  return result;
}


/*** DEPENDENCIES:
***/


bool check_debug_fill_uninit(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xD0;
  }

  return result;
}


/*** DEPENDENCIES:
***/


bool check_debug_fill_freed(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xDF;
  }

  return result;
}


/*** DEPENDENCIES:
***/


int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 30))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 36))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 42))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_small(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 49))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 55))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 62))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 71))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 81))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 90))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 103))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 109))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 116))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 122))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 129))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 138))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 148))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 157))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 171))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 177))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 184))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_small(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 191))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 200))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 210))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 216))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 223))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 232))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 242))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 248))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 255))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 264))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-small", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 275))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api-fill.c", 282))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  return print_test_summary();
}


/*** DEPENDENCIES:
bool check_debug_fill_freed(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xDF;
  }

  return result;
}


----------------------------
bool check_debug_fill_uninit(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xD0;
  }

  return result;
}


----------------------------
static bool check_result(bool result, const char *testname, const char *fname, long lineno)
{
  if (!result)
  {
    failed += 1;
    fprintf(stderr, "\n  FAILED: %s: %s:%ld\n", testname, fname, lineno);
  }
  else
  {
    ok += 1;
    fprintf(stderr, "ok.\n");
  }
  return 1;
}


----------------------------
bool check_zero_init(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0;
  }

  return result;
}


----------------------------
void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


----------------------------
void *mi_calloc_aligned(size_t count, size_t size, size_t alignment)
{
  return mi_heap_calloc_aligned(mi_prim_get_default_heap(), count, size, alignment);
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
inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


----------------------------
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
inline extern void *mi_malloc_small(size_t size)
{
  return mi_heap_malloc_small(mi_prim_get_default_heap(), size);
}


----------------------------
void *mi_mallocn(size_t count, size_t size)
{
  return mi_heap_mallocn(mi_prim_get_default_heap(), count, size);
}


----------------------------
void mi_option_disable(mi_option_t option)
{
  mi_option_set_enabled(option, 0);
}


----------------------------
void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
void *mi_realloc_aligned(void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_aligned(mi_prim_get_default_heap(), p, newsize, alignment);
}


----------------------------
void *mi_reallocn(void *p, size_t count, size_t size)
{
  return mi_heap_reallocn(mi_prim_get_default_heap(), p, count, size);
}


----------------------------
void *mi_recalloc(void *p, size_t count, size_t size)
{
  return mi_heap_recalloc(mi_prim_get_default_heap(), p, count, size);
}


----------------------------
void *mi_recalloc_aligned(void *p, size_t newcount, size_t size, size_t alignment)
{
  return mi_heap_recalloc_aligned(mi_prim_get_default_heap(), p, newcount, size, alignment);
}


----------------------------
void *mi_rezalloc(void *p, size_t newsize)
{
  return mi_heap_rezalloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
void *mi_rezalloc_aligned(void *p, size_t newsize, size_t alignment)
{
  return mi_heap_rezalloc_aligned(mi_prim_get_default_heap(), p, newsize, alignment);
}


----------------------------
void *mi_zalloc(size_t size)
{
  return mi_heap_zalloc(mi_prim_get_default_heap(), size);
}


----------------------------
void *mi_zalloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
void *mi_zalloc_small(size_t size)
{
  return mi_heap_malloc_small_zero(mi_prim_get_default_heap(), size, 1);
}


----------------------------
inline static int print_test_summary(void)
{
  fprintf(stderr, "\n\n---------------------------------------------\nsucceeded: %i\nfailed   : %i\n\n", ok, failed);
  return failed;
}


----------------------------
***/


