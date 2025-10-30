typedef struct _hashmap_t
{
  struct hashcell_t cell[256];
} hashmap_t
/*** DEPENDENCIES:
struct hashcell_t
{
  struct hashentry_t *e;
  size_t c;
}
----------------------------
***/


