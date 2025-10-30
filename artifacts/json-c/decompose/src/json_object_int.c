struct json_object_int
{
  struct json_object base;
  enum json_object_int_type cint_type;
  union 
  {
    int64_t c_int64;
    uint64_t c_uint64;
  } cint;
}
/*** DEPENDENCIES:
typedef enum json_object_int_type
{
  json_object_int_type_int64,
  json_object_int_type_uint64
} json_object_int_type
----------------------------
None
----------------------------
***/


