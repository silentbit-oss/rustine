struct json_object_array
{
  struct json_object base;
  struct array_list *c_array;
}
/*** DEPENDENCIES:
struct array_list
{
  void **array;
  size_t length;
  size_t size;
  array_list_free_fn *free_fn;
}
----------------------------
None
----------------------------
***/


