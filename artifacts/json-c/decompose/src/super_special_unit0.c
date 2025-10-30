// element in merge of:  json_object,json_object_to_json_string_fn,json_object_delete_fn
struct json_object
{
  enum json_type o_type;
  uint32_t _ref_count;
  json_object_to_json_string_fn *_to_json_string;
  struct printbuf *_pb;
  json_object_delete_fn *_user_delete;
  void *_userdata;
}
/*** DEPENDENCIES:
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type
----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
None
----------------------------
***/


// element in merge of:  json_object,json_object_to_json_string_fn,json_object_delete_fn
typedef int json_object_to_json_string_fn(struct json_object *jso, struct printbuf *pb, int level, int flags)
/*** DEPENDENCIES:
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
None
----------------------------
***/


// element in merge of:  json_object,json_object_to_json_string_fn,json_object_delete_fn
typedef void json_object_delete_fn(struct json_object *jso, void *userdata)
/*** DEPENDENCIES:
None
----------------------------
***/


