bool test_stl_allocator1(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool test_stl_allocator2(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool test_stl_heap_allocator1(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool test_stl_heap_allocator2(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool test_stl_heap_allocator3(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool test_stl_heap_allocator4(void)
{
  return 1;
}


/*** DEPENDENCIES:
***/


bool mem_is_zero(uint8_t *p, size_t size)
{
  if (p == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < size; i += 1)
  {
    if (p[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
static int failed = 0
----------------------------
static int ok = 0
----------------------------
***/


inline static int print_test_summary(void)
{
  fprintf(stderr, "\n\n---------------------------------------------\nsucceeded: %i\nfailed   : %i\n\n", ok, failed);
  return failed;
}


/*** DEPENDENCIES:
static int failed = 0
----------------------------
static int ok = 0
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool']
void helper_main_1(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  for (size_t size = 1; (size <= ((128 * (sizeof(void *))) * 2)) && ok; size += 1)
  {
    for (size_t align = 1; (align <= size) && ok; align *= 2)
    {
      void *p[10];
      for (int i = 0; (i < 10) && ok; i += 1)
      {
        p[i + p_idx] = mi_malloc_aligned(size, align);
        ;
        ok = (p[i + p_idx] != 0) && ((((uintptr_t) p[i + p_idx]) % align) == 0);
      }

      for (int i = 0; (i < 10) && ok; i += 1)
      {
        mi_free(p[i + p_idx]);
      }

    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}


/*** DEPENDENCIES:
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
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
static int ok = 0
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'p_idx_ref is a mutable refrence to unsigned int', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool', 'result_ref is a mutable refrence to bool']
void helper_main_2(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  void *p[8];
  const int max_align_shift = 20;
  size_t sizes[8] = {8, 512, 1024 * 1024, 1UL << (13 + 3), (1UL << (13 + 3)) + 1, 2 * (1UL << (13 + 3)), 8 * (1UL << (13 + 3)), 0};
  for (int i = 0; (i < max_align_shift) && ok; i += 1)
  {
    int align = 1 << i;
    for (int j = 0; (j < 8) && ok; j += 1)
    {
      p[j + p_idx] = mi_zalloc_aligned(sizes[j], align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (int j = 0; j < 8; j += 1)
    {
      mi_free(p[j + p_idx]);
    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}


/*** DEPENDENCIES:
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
void *mi_zalloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
static int ok = 0
----------------------------
***/


bool test_heap1(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  *p1 = (*p2 = 43);
  mi_heap_destroy(heap);
  return 1;
}


/*** DEPENDENCIES:
mi_heap_t *mi_heap_new(void)
{
  return mi_heap_new_ex(0, 1, _mi_arena_id_none());
}


----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 382, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 383, __func__));
  (!heap->allow_page_reclaim) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_reclaim", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 384, __func__));
  (!heap->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 385, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (heap->allow_page_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap, 1);
  }
}


----------------------------
None
----------------------------
***/


bool test_heap2(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  mi_heap_delete(heap);
  *p1 = 42;
  mi_free(p1);
  mi_free(p2);
  return 1;
}


/*** DEPENDENCIES:
mi_heap_t *mi_heap_new(void)
{
  return mi_heap_new_ex(0, 1, _mi_arena_id_none());
}


----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
void mi_heap_delete(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 460, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 461, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  _mi_heap_collect_abandon(heap);
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 468, __func__));
  mi_heap_free(heap, 1);
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
None
----------------------------
***/


int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "malloc-aligned9a");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9a", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 68))
  {
    void *p = mi_zalloc_aligned(1024 * 1024, 2);
    unsigned int p_idx = 0;
    mi_free(p);
    p_idx = mi_zalloc_aligned(1024 * 1024, 2);
    mi_free(p);
    result = 1;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-zero", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 81))
  {
    void *p = mi_malloc(0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-nomem1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-nomem1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 86))
  {
    result = mi_malloc(((size_t) PTRDIFF_MAX) + ((size_t) 1)) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-null", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 89))
  {
    mi_free(0);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-invalid-low");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-invalid-low", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 93))
  {
    mi_free((void *) 0x0000000003990080UL);
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc-overflow");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc-overflow", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 97))
  {
    result = mi_calloc((size_t) (&mi_calloc), SIZE_MAX / 1000) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc0");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 101))
  {
    void *p = mi_calloc(0, 1000);
    unsigned int p_idx = 0;
    result = mi_usable_size(p) <= 16;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-large", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 106))
  {
    void *p = mi_malloc(67108872);
    unsigned int p_idx = 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 114))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 32);
    result = ((err == 0) && ((((uintptr_t) p) % (sizeof(void *))) == 0)) || ((&p[p_idx]) == (&(&p[p_idx])));
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_no_align");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_no_align", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 120))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3, 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_zero", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 125))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 0);
    mi_free(p);
    result = err == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nopow2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nopow2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 131))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3 * (sizeof(void *)), 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nomem");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nomem", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 136))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), SIZE_MAX);
    result = (err == 12) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 145))
  {
    void *p = mi_malloc_aligned(32, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 148))
  {
    void *p = mi_malloc_aligned(48, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned3", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 151))
  {
    void *p1 = mi_malloc_aligned(48, 32);
    bool result1 = (p1 != 0) && ((((uintptr_t) p1) % 32) == 0);
    void *p2 = mi_malloc_aligned(48, 32);
    bool result2 = (p2 != 0) && ((((uintptr_t) p2) % 32) == 0);
    mi_free(p2);
    mi_free(p1);
    result = result1 && result2;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned4", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 158))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_malloc_aligned(8, 16);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned5");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned5", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 167))
  {
    void *p = mi_malloc_aligned(4097, 4096);
    unsigned int p_idx = 0;
    size_t usable = mi_usable_size(p);
    result = (usable >= 4097) && (usable < 16000);
    fprintf(stderr, "malloc_aligned5: usable size: %zi.  ", usable);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned7");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned7", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 193))
  {
    void *p = mi_malloc_aligned(1024, 1UL << (13 + 3));
    unsigned int p_idx = 0;
    mi_free(p);
    result = (((uintptr_t) p) % (1UL << (13 + 3))) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned8");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned8", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 198))
  {
    bool ok = 1;
    for (int i = 0; (i < 5) && ok; i += 1)
    {
      int n = 1 << i;
      void *p = mi_malloc_aligned(1024, n * (1UL << (13 + 3)));
      unsigned int p_idx = 0;
      ok = (((uintptr_t) p) % (n * (1UL << (13 + 3)))) == 0;
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned9");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 208))
  {
    helper_main_2(&result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &result, &result, &result, &result);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned10");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned10", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 231))
  {
    bool ok = 1;
    void *p[10 + 1];
    int align;
    int j;
    for (j = 0, align = 1; (j <= 10) && ok; align *= 2, j += 1)
    {
      p[j + p_idx] = mi_malloc_aligned(43 + align, align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (; j > 0; j -= 1)
    {
      mi_free(p[(j - 1) + p_idx]);
    }

    result = ok;
  }

  fprintf(stderr, "test: %s...  ", "malloc_aligned11");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc_aligned11", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 245))
  {
    mi_heap_t *heap = mi_heap_new();
    void *p = mi_heap_malloc_aligned(heap, 33554426, 8);
    unsigned int p_idx = 0;
    result = mi_heap_contains_block(heap, p);
    mi_heap_destroy(heap);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned12");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned12", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 251))
  {
    void *p = mi_malloc_aligned(0x100, 0x100);
    unsigned int p_idx = 0;
    result = (((uintptr_t) p) % 0x100) == 0;
    mi_free(p);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned13");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned13", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 256))
  {
    helper_main_1(&result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &result, &result, &result, &result);
  }

  fprintf(stderr, "test: %s...  ", "malloc-aligned-at1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 278))
  {
    void *p = mi_malloc_aligned_at(48, 32, 0);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 0) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned-at2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 281))
  {
    void *p = mi_malloc_aligned_at(50, 32, 8);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 8) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "memalign1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 284))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_memalign(16, 8);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "zalloc-aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zalloc-aligned-small1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 293))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "rezalloc_aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "rezalloc_aligned-small1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 299))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result = result && mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 312))
  {
    void *p = mi_realloc(0, 4);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null-sizezero", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 318))
  {
    void *p = mi_realloc(0, 0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-sizezero", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 324))
  {
    void *p = mi_malloc(4);
    unsigned int p_idx = 0;
    void *q = mi_realloc(p, 0);
    result = q != 0;
    mi_free(q);
  }

  ;
  fprintf(stderr, "test: %s...  ", "reallocarray-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "reallocarray-null-sizezero", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 331))
  {
    void *p = mi_reallocarray(0, 0, 16);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (errno == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_destroy");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_destroy", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 340))
  {
    result = test_heap1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_delete");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_delete", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 341))
  {
    result = test_heap2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "realpath");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realpath", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 349))
  {
    char *s = mi_realpath(".", 0);
    mi_free(s);
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 356))
  {
    result = test_stl_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 357))
  {
    result = test_stl_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 359))
  {
    result = test_stl_heap_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 360))
  {
    result = test_stl_heap_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator3", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 361))
  {
    result = test_stl_heap_allocator3();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator4", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/test/test-api.c", 362))
  {
    result = test_stl_heap_allocator4();
  }

  ;
  return print_test_summary();
}


/*** DEPENDENCIES:
bool mem_is_zero(uint8_t *p, size_t size)
{
  if (p == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < size; i += 1)
  {
    if (p[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
void *mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_aligned_at(mi_prim_get_default_heap(), size, alignment, offset);
}


----------------------------
void *mi_heap_malloc_aligned(mi_heap_t *heap, size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned_at(heap, size, alignment, 0);
}


----------------------------
void mi_option_disable(mi_option_t option)
{
  mi_option_set_enabled(option, 0);
}


----------------------------
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
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
void *mi_reallocarray(void *p, size_t count, size_t size)
{
  void *newp = mi_reallocn(p, count, size);
  if (newp == 0)
  {
    errno = 12;
  }
  return newp;
}


----------------------------
void *mi_rezalloc_aligned(void *p, size_t newsize, size_t alignment)
{
  return mi_heap_rezalloc_aligned(mi_prim_get_default_heap(), p, newsize, alignment);
}


----------------------------
static int ok = 0
----------------------------
inline static int print_test_summary(void)
{
  fprintf(stderr, "\n\n---------------------------------------------\nsucceeded: %i\nfailed   : %i\n\n", ok, failed);
  return failed;
}


----------------------------
void helper_main_1(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  for (size_t size = 1; (size <= ((128 * (sizeof(void *))) * 2)) && ok; size += 1)
  {
    for (size_t align = 1; (align <= size) && ok; align *= 2)
    {
      void *p[10];
      for (int i = 0; (i < 10) && ok; i += 1)
      {
        p[i + p_idx] = mi_malloc_aligned(size, align);
        ;
        ok = (p[i + p_idx] != 0) && ((((uintptr_t) p[i + p_idx]) % align) == 0);
      }

      for (int i = 0; (i < 10) && ok; i += 1)
      {
        mi_free(p[i + p_idx]);
      }

    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}


----------------------------
bool test_heap2(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  mi_heap_delete(heap);
  *p1 = 42;
  mi_free(p1);
  mi_free(p2);
  return 1;
}


----------------------------
bool test_stl_heap_allocator3(void)
{
  return 1;
}


----------------------------
inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


----------------------------
void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 382, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 383, __func__));
  (!heap->allow_page_reclaim) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_reclaim", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 384, __func__));
  (!heap->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 385, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (heap->allow_page_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap, 1);
  }
}


----------------------------
void helper_main_2(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  void *p[8];
  const int max_align_shift = 20;
  size_t sizes[8] = {8, 512, 1024 * 1024, 1UL << (13 + 3), (1UL << (13 + 3)) + 1, 2 * (1UL << (13 + 3)), 8 * (1UL << (13 + 3)), 0};
  for (int i = 0; (i < max_align_shift) && ok; i += 1)
  {
    int align = 1 << i;
    for (int j = 0; (j < 8) && ok; j += 1)
    {
      p[j + p_idx] = mi_zalloc_aligned(sizes[j], align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (int j = 0; j < 8; j += 1)
    {
      mi_free(p[j + p_idx]);
    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}


----------------------------
char *mi_realpath(const char *fname, char *resolved_name)
{
  return mi_heap_realpath(mi_prim_get_default_heap(), fname, resolved_name);
}


----------------------------
bool test_stl_heap_allocator2(void)
{
  return 1;
}


----------------------------
void *mi_zalloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
bool test_stl_allocator1(void)
{
  return 1;
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
bool test_stl_heap_allocator1(void)
{
  return 1;
}


----------------------------
mi_heap_t *mi_heap_new(void)
{
  return mi_heap_new_ex(0, 1, _mi_arena_id_none());
}


----------------------------
bool test_stl_allocator2(void)
{
  return 1;
}


----------------------------
void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}


----------------------------
int mi_posix_memalign(void **p, size_t alignment, size_t size)
{
  if (p == 0)
  {
    return 22;
  }
  if ((alignment % (sizeof(void *))) != 0)
  {
    return 22;
  }
  if ((alignment == 0) || (!_mi_is_power_of_two(alignment)))
  {
    return 22;
  }
  void *q = mi_malloc_aligned(size, alignment);
  if ((q == 0) && (size != 0))
  {
    return 12;
  }
  ((((uintptr_t) q) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)q % alignment) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc-posix.c", 64, __func__));
  *p = q;
  return 0;
}


----------------------------
void *mi_memalign(size_t alignment, size_t size)
{
  void *p = mi_malloc_aligned(size, alignment);
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc-posix.c", 71, __func__));
  return p;
}


----------------------------
bool test_stl_heap_allocator4(void)
{
  return 1;
}


----------------------------
void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}


----------------------------
bool test_heap1(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  *p1 = (*p2 = 43);
  mi_heap_destroy(heap);
  return 1;
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
bool mi_heap_contains_block(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 553, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  return heap == mi_heap_of_block(p);
}


----------------------------
None
----------------------------
***/


