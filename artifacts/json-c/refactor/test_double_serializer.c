#include <config.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_object_private.h>
#include <json_types.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>
#include <test_double_serializer.c>
#include <unistd.h>

struct printbuf;
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
};
typedef struct json_object_iter json_object_iter;
typedef int json_bool;
typedef struct json_object json_object;
typedef void json_object_delete_fn(struct json_object *jso, void *userdata);
typedef int json_object_to_json_string_fn(struct json_object *jso, struct printbuf *pb, int level, int flags);
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type;
struct printbuf
{
  char *buf;
  int bpos;
  int size;
};
typedef struct printbuf printbuf;
extern struct printbuf *printbuf_new(void);
extern int printbuf_memappend(struct printbuf *p, const char *buf, int size);
extern int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len);
extern int sprintbuf(struct printbuf *p, const char *msg, ...);
extern void printbuf_reset(struct printbuf *p);
extern void printbuf_free(struct printbuf *p);
extern struct json_object *json_object_get(struct json_object *obj);
extern int json_object_put(struct json_object *obj);
extern int json_object_is_type(const struct json_object *obj, enum json_type type);
extern enum json_type json_object_get_type(const struct json_object *obj);
extern const char *json_object_to_json_string(struct json_object *obj);
extern const char *json_object_to_json_string_ext(struct json_object *obj, int flags);
extern const char *json_object_to_json_string_length(struct json_object *obj, int flags, size_t *length);
extern void *json_object_get_userdata(json_object *jso);
extern void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete);
extern void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete);
extern json_object_delete_fn json_object_free_userdata;
extern json_object_to_json_string_fn json_object_userdata_to_json_string;
extern struct json_object *json_object_new_object(void);
extern struct lh_table *json_object_get_object(const struct json_object *obj);
extern int json_object_object_length(const struct json_object *obj);
extern size_t json_c_object_sizeof(void);
extern int json_object_object_add(struct json_object *obj, const char *key, struct json_object *val);
extern int json_object_object_add_ex(struct json_object *obj, const char * const key, struct json_object * const val, const unsigned opts);
extern struct json_object *json_object_object_get(const struct json_object *obj, const char *key);
extern int json_object_object_get_ex(const struct json_object *obj, const char *key, struct json_object **value);
extern void json_object_object_del(struct json_object *obj, const char *key);
extern struct json_object *json_object_new_array(void);
extern struct json_object *json_object_new_array_ext(int initial_size);
extern struct array_list *json_object_get_array(const struct json_object *obj);
extern size_t json_object_array_length(const struct json_object *obj);
extern void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern int json_object_array_add(struct json_object *obj, struct json_object *val);
extern int json_object_array_put_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern int json_object_array_insert_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern struct json_object *json_object_array_get_idx(const struct json_object *obj, size_t idx);
extern int json_object_array_del_idx(struct json_object *obj, size_t idx, size_t count);
extern int json_object_array_shrink(struct json_object *jso, int empty_slots);
extern struct json_object *json_object_new_boolean(json_bool b);
extern json_bool json_object_get_boolean(const struct json_object *obj);
extern int json_object_set_boolean(struct json_object *obj, json_bool new_value);
extern struct json_object *json_object_new_int(int32_t i);
extern struct json_object *json_object_new_int64(int64_t i);
extern struct json_object *json_object_new_uint64(uint64_t i);
extern int32_t json_object_get_int(const struct json_object *obj);
extern int json_object_set_int(struct json_object *obj, int new_value);
extern int json_object_int_inc(struct json_object *obj, int64_t val);
extern int64_t json_object_get_int64(const struct json_object *obj);
extern uint64_t json_object_get_uint64(const struct json_object *obj);
extern int json_object_set_int64(struct json_object *obj, int64_t new_value);
extern int json_object_set_uint64(struct json_object *obj, uint64_t new_value);
extern struct json_object *json_object_new_double(double d);
extern struct json_object *json_object_new_double_s(double d, const char *ds);
extern int json_c_set_serialization_double_format(const char *double_format, int global_or_thread);
extern int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags);
extern double json_object_get_double(const struct json_object *obj);
extern int json_object_set_double(struct json_object *obj, double new_value);
extern struct json_object *json_object_new_string(const char *s);
extern struct json_object *json_object_new_string_len(const char *s, const int len);
extern const char *json_object_get_string(struct json_object *obj);
extern int json_object_get_string_len(const struct json_object *obj);
extern int json_object_set_string(json_object *obj, const char *new_value);
extern int json_object_set_string_len(json_object *obj, const char *new_value, int len);
extern struct json_object *json_object_new_null(void);
extern int json_object_equal(struct json_object *obj1, struct json_object *obj2);
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst);
extern json_c_shallow_copy_fn json_c_shallow_copy_default;
extern int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy);
struct json_object;
typedef enum json_object_int_type
{
  json_object_int_type_int64,
  json_object_int_type_uint64
} json_object_int_type;
struct json_object
{
  enum json_type o_type;
  uint32_t _ref_count;
  json_object_to_json_string_fn *_to_json_string;
  struct printbuf *_pb;
  json_object_delete_fn *_user_delete;
  void *_userdata;
};
struct json_object_object
{
  struct json_object base;
  struct lh_table *c_object;
};
struct json_object_array
{
  struct json_object base;
  struct array_list *c_array;
};
struct json_object_boolean
{
  struct json_object base;
  json_bool c_boolean;
};
struct json_object_double
{
  struct json_object base;
  double c_double;
};
struct json_object_int
{
  struct json_object base;
  enum json_object_int_type cint_type;
  union 
  {
    int64_t c_int64;
    uint64_t c_uint64;
  } cint;
};
struct json_object_string
{
  struct json_object base;
  ssize_t len;
  union 
  {
    char idata[1];
    char *pdata;
  } c_string;
};
void _json_c_set_last_err(const char *err_fmt, ...);
extern const char *json_hex_chars;
double zero_dot_zero = 0.0;
int main(int argc, char **argv)
{
  struct json_object *obj = json_object_new_double(0.5);
  unsigned int obj_idx = 0;
  char udata[] = "test";
  printf("Test default serializer:\n");
  printf("obj.to_string(standard)=%s\n", json_object_to_json_string(obj));
  printf("Test default serializer with custom userdata:\n");
  obj->_userdata = udata;
  printf("obj.to_string(userdata)=%s\n", json_object_to_json_string(obj));
  printf("Test explicit serializer with custom userdata:\n");
  json_object_set_serializer(obj, json_object_double_to_json_string, udata, 0);
  printf("obj.to_string(custom)=%s\n", json_object_to_json_string(obj));
  printf("Test reset serializer:\n");
  json_object_set_serializer(obj, 0, 0, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  printf("Test no zero reset serializer:\n");
  obj_idx = json_object_new_double(3.1415000);
  char data[] = "%.17g";
  json_object_set_serializer(obj, json_object_double_to_json_string, data, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string_ext(obj, 4));
  json_object_put(obj);
  obj_idx = json_object_new_double(0.52381);
  printf("obj.to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("x%0.3fy", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("T%0.2fX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("Ttttttttttttt%0.2fxxxxxxxxxxxxxxxxxxX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(long thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(12.0);
  printf("obj(12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0f", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0f)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.2g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.1g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  json_object_put(obj);
  obj_idx = json_object_new_double(-12.0);
  printf("obj(-12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(zero_dot_zero / zero_dot_zero);
  printf("obj(0.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(1.0 / zero_dot_zero);
  printf("obj(1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double((-1.0) / zero_dot_zero);
  printf("obj(-1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  return 0;
}


struct printbuf;
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
};
typedef struct json_object_iter json_object_iter;
typedef int json_bool;
typedef struct json_object json_object;
typedef void json_object_delete_fn(struct json_object *jso, void *userdata);
typedef int json_object_to_json_string_fn(struct json_object *jso, struct printbuf *pb, int level, int flags);
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type;
struct printbuf
{
  char *buf;
  int bpos;
  int size;
};
typedef struct printbuf printbuf;
extern struct printbuf *printbuf_new(void);
extern int printbuf_memappend(struct printbuf *p, const char *buf, int size);
extern int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len);
extern int sprintbuf(struct printbuf *p, const char *msg, ...);
extern void printbuf_reset(struct printbuf *p);
extern void printbuf_free(struct printbuf *p);
extern struct json_object *json_object_get(struct json_object *obj);
extern int json_object_put(struct json_object *obj);
extern int json_object_is_type(const struct json_object *obj, enum json_type type);
extern enum json_type json_object_get_type(const struct json_object *obj);
extern const char *json_object_to_json_string(struct json_object *obj);
extern const char *json_object_to_json_string_ext(struct json_object *obj, int flags);
extern const char *json_object_to_json_string_length(struct json_object *obj, int flags, size_t *length);
extern void *json_object_get_userdata(json_object *jso);
extern void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete);
extern void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete);
extern json_object_delete_fn json_object_free_userdata;
extern json_object_to_json_string_fn json_object_userdata_to_json_string;
extern struct json_object *json_object_new_object(void);
extern struct lh_table *json_object_get_object(const struct json_object *obj);
extern int json_object_object_length(const struct json_object *obj);
extern size_t json_c_object_sizeof(void);
extern int json_object_object_add(struct json_object *obj, const char *key, struct json_object *val);
extern int json_object_object_add_ex(struct json_object *obj, const char * const key, struct json_object * const val, const unsigned opts);
extern struct json_object *json_object_object_get(const struct json_object *obj, const char *key);
extern int json_object_object_get_ex(const struct json_object *obj, const char *key, struct json_object **value);
extern void json_object_object_del(struct json_object *obj, const char *key);
extern struct json_object *json_object_new_array(void);
extern struct json_object *json_object_new_array_ext(int initial_size);
extern struct array_list *json_object_get_array(const struct json_object *obj);
extern size_t json_object_array_length(const struct json_object *obj);
extern void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern int json_object_array_add(struct json_object *obj, struct json_object *val);
extern int json_object_array_put_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern int json_object_array_insert_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern struct json_object *json_object_array_get_idx(const struct json_object *obj, size_t idx);
extern int json_object_array_del_idx(struct json_object *obj, size_t idx, size_t count);
extern int json_object_array_shrink(struct json_object *jso, int empty_slots);
extern struct json_object *json_object_new_boolean(json_bool b);
extern json_bool json_object_get_boolean(const struct json_object *obj);
extern int json_object_set_boolean(struct json_object *obj, json_bool new_value);
extern struct json_object *json_object_new_int(int32_t i);
extern struct json_object *json_object_new_int64(int64_t i);
extern struct json_object *json_object_new_uint64(uint64_t i);
extern int32_t json_object_get_int(const struct json_object *obj);
extern int json_object_set_int(struct json_object *obj, int new_value);
extern int json_object_int_inc(struct json_object *obj, int64_t val);
extern int64_t json_object_get_int64(const struct json_object *obj);
extern uint64_t json_object_get_uint64(const struct json_object *obj);
extern int json_object_set_int64(struct json_object *obj, int64_t new_value);
extern int json_object_set_uint64(struct json_object *obj, uint64_t new_value);
extern struct json_object *json_object_new_double(double d);
extern struct json_object *json_object_new_double_s(double d, const char *ds);
extern int json_c_set_serialization_double_format(const char *double_format, int global_or_thread);
extern int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags);
extern double json_object_get_double(const struct json_object *obj);
extern int json_object_set_double(struct json_object *obj, double new_value);
extern struct json_object *json_object_new_string(const char *s);
extern struct json_object *json_object_new_string_len(const char *s, const int len);
extern const char *json_object_get_string(struct json_object *obj);
extern int json_object_get_string_len(const struct json_object *obj);
extern int json_object_set_string(json_object *obj, const char *new_value);
extern int json_object_set_string_len(json_object *obj, const char *new_value, int len);
extern struct json_object *json_object_new_null(void);
extern int json_object_equal(struct json_object *obj1, struct json_object *obj2);
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst);
extern json_c_shallow_copy_fn json_c_shallow_copy_default;
extern int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy);
struct json_object;
typedef enum json_object_int_type
{
  json_object_int_type_int64,
  json_object_int_type_uint64
} json_object_int_type;
struct json_object
{
  enum json_type o_type;
  uint32_t _ref_count;
  json_object_to_json_string_fn *_to_json_string;
  struct printbuf *_pb;
  json_object_delete_fn *_user_delete;
  void *_userdata;
};
struct json_object_object
{
  struct json_object base;
  struct lh_table *c_object;
};
struct json_object_array
{
  struct json_object base;
  struct array_list *c_array;
};
struct json_object_boolean
{
  struct json_object base;
  json_bool c_boolean;
};
struct json_object_double
{
  struct json_object base;
  double c_double;
};
struct json_object_int
{
  struct json_object base;
  enum json_object_int_type cint_type;
  union 
  {
    int64_t c_int64;
    uint64_t c_uint64;
  } cint;
};
struct json_object_string
{
  struct json_object base;
  ssize_t len;
  union 
  {
    char idata[1];
    char *pdata;
  } c_string;
};
void _json_c_set_last_err(const char *err_fmt, ...);
extern const char *json_hex_chars;
double zero_dot_zero = 0.0;
int main(int argc, char **argv)
{
  struct json_object *obj = json_object_new_double(0.5);
  unsigned int obj_idx = 0;
  char udata[] = "test";
  printf("Test default serializer:\n");
  printf("obj.to_string(standard)=%s\n", json_object_to_json_string(obj));
  printf("Test default serializer with custom userdata:\n");
  obj->_userdata = udata;
  printf("obj.to_string(userdata)=%s\n", json_object_to_json_string(obj));
  printf("Test explicit serializer with custom userdata:\n");
  json_object_set_serializer(obj, json_object_double_to_json_string, udata, 0);
  printf("obj.to_string(custom)=%s\n", json_object_to_json_string(obj));
  printf("Test reset serializer:\n");
  json_object_set_serializer(obj, 0, 0, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  printf("Test no zero reset serializer:\n");
  obj_idx = json_object_new_double(3.1415000);
  char data[] = "%.17g";
  json_object_set_serializer(obj, json_object_double_to_json_string, data, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string_ext(obj, 4));
  json_object_put(obj);
  obj_idx = json_object_new_double(0.52381);
  printf("obj.to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("x%0.3fy", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("T%0.2fX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("Ttttttttttttt%0.2fxxxxxxxxxxxxxxxxxxX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(long thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(12.0);
  printf("obj(12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0f", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0f)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.2g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.1g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  json_object_put(obj);
  obj_idx = json_object_new_double(-12.0);
  printf("obj(-12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(zero_dot_zero / zero_dot_zero);
  printf("obj(0.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(1.0 / zero_dot_zero);
  printf("obj(1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double((-1.0) / zero_dot_zero);
  printf("obj(-1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  return 0;
}

