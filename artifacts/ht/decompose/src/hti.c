typedef struct 
{
  const char *key;
  void *value;
  ht *_table;
  size_t _index;
} hti
/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
***/


