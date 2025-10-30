typedef struct 
{
  uint32_t bitmask : 31;
  unsigned int generic : 1;
  union 
  {
    const void *table;
    bool (*lookup_fn)(ucs4_t uc, uint32_t bitmask);
  } lookup;
} uc_general_category_t
/*** DEPENDENCIES:
typedef uint32_t ucs4_t
----------------------------
***/


