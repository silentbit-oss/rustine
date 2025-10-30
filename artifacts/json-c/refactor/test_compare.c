#include <config.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_types.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <test_compare.c>

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
int main(int argc, char **argv)
{
  struct json_object *int1 = json_object_new_int(0);
  struct json_object *int2 = json_object_new_int(1);
  struct json_object *int3 = json_object_new_int(1);
  struct json_object *int4 = json_object_new_int(-1);
  struct json_object *uint1 = json_object_new_uint64(0);
  struct json_object *uint2 = json_object_new_uint64(1);
  struct json_object *uint3 = json_object_new_uint64(1);
  struct json_object *uint4 = json_object_new_uint64(((uint64_t) INT64_MAX) + 100);
  if (!json_object_equal(int1, int2))
  {
    printf("JSON integer comparison is correct\n");
  }
  else
    printf("JSON integer comparison failed\n");
  if (json_object_equal(int1, int1))
  {
    printf("JSON same object comparison is correct\n");
  }
  else
    printf("JSON same object comparison failed\n");
  if (json_object_equal(int2, int3))
  {
    printf("JSON same integer comparison is correct\n");
  }
  else
    printf("JSON same integer comparison failed\n");
  if (!json_object_equal(uint1, uint2))
  {
    printf("JSON usigned integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer comparison failed\n");
  if (json_object_equal(uint1, uint1))
  {
    printf("JSON same usigned object comparison is correct\n");
  }
  else
    printf("JSON same usigned object comparison failed\n");
  if (json_object_equal(uint2, uint3))
  {
    printf("JSON same usigned integer comparison is correct\n");
  }
  else
    printf("JSON same usigned integer comparison failed\n");
  if (json_object_equal(int2, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int2, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (json_object_equal(uint2, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint2, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  json_object_put(int1);
  json_object_put(int2);
  json_object_put(int3);
  json_object_put(int4);
  json_object_put(uint1);
  json_object_put(uint2);
  json_object_put(uint3);
  json_object_put(uint4);
  struct json_object *str1 = json_object_new_string("TESTSTRING");
  struct json_object *str2 = json_object_new_string("TESTSTRING");
  struct json_object *str3 = json_object_new_string("DIFFERENT");
  if (json_object_equal(str1, str2))
  {
    printf("Comparing equal strings is correct\n");
  }
  else
    printf("Comparing equal strings failed\n");
  if (!json_object_equal(str1, str3))
  {
    printf("Comparing different strings is correct\n");
  }
  else
    printf("Comparing different strings failed\n");
  json_object_put(str1);
  json_object_put(str2);
  json_object_put(str3);
  struct json_object *dbl1 = json_object_new_double(3.14159);
  struct json_object *dbl2 = json_object_new_double(3.14159);
  struct json_object *dbl3 = json_object_new_double(3.0);
  if (json_object_equal(dbl1, dbl2))
  {
    printf("Comparing equal doubles is correct\n");
  }
  else
    printf("Comparing equal doubles failed\n");
  if (!json_object_equal(dbl1, dbl3))
  {
    printf("Comparing different doubles is correct\n");
  }
  else
    printf("Comparing different doubles failed\n");
  json_object_put(dbl1);
  json_object_put(dbl2);
  json_object_put(dbl3);
  struct json_object *ar1 = json_object_new_array();
  struct json_object *ar2 = json_object_new_array();
  struct json_object *ar3 = json_object_new_array();
  struct json_object *ar4 = json_object_new_array();
  json_object_array_add(ar1, json_object_new_int(1));
  json_object_array_add(ar1, json_object_new_int(2));
  json_object_array_add(ar2, json_object_new_int(1));
  json_object_array_add(ar2, json_object_new_int(2));
  json_object_array_add(ar3, json_object_new_int(1));
  json_object_array_add(ar3, json_object_new_int(1));
  if (json_object_equal(ar1, ar2))
  {
    printf("Comparing equal arrays is correct\n");
  }
  else
    printf("Comparing equal arrays failed\n");
  json_object_array_add(ar2, json_object_new_int(1));
  if (!json_object_equal(ar1, ar2))
  {
    printf("Comparing arrays of different len is correct\n");
  }
  else
    printf("Comparing arrays of different len failed\n");
  if (!json_object_equal(ar1, ar3))
  {
    printf("Comparing different arrays is correct\n");
  }
  else
    printf("Comparing different arrays failed\n");
  if (!json_object_equal(ar1, ar4))
  {
    printf("Comparing different arrays (one empty) is correct\n");
  }
  else
    printf("Comparing different arrays (one empty) failed\n");
  json_object_put(ar1);
  json_object_put(ar2);
  json_object_put(ar3);
  json_object_put(ar4);
  struct json_object *obj1 = json_object_new_object();
  struct json_object *obj2 = json_object_new_object();
  json_object_object_add(obj1, "test1", json_object_new_int(123));
  json_object_object_add(obj1, "test2", json_object_new_int(321));
  json_object_object_add(obj1, "test3", json_object_new_int(320));
  json_object_object_add(obj1, "test4", json_object_new_int(319));
  json_object_object_add(obj1, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test4", json_object_new_int(319));
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test2", json_object_new_int(321));
  json_object_object_add(obj2, "test1", json_object_new_int(123));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing JSON object with different key order is correct\n");
  }
  else
    printf("Comparing JSON object with different key order is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(234));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test6", json_object_new_int(321));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test6", json_object_new_int(321));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test7", json_object_new_int(322));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_put(obj1);
  json_object_put(obj2);
  struct json_object *int5 = json_object_new_int(0);
  struct json_object *dbl5 = json_object_new_double(3.14159);
  if (!json_object_equal(int5, 0))
  {
    printf("JSON integer and NULL comparison is correct\n");
  }
  else
    printf("JSON integer and NULL comparison failed\n");
  if (!json_object_equal(0, dbl5))
  {
    printf("JSON NULL and double comparison is correct\n");
  }
  else
    printf("JSON NULL and double comparison failed\n");
  if (!json_object_equal(int5, dbl5))
  {
    printf("JSON integer and double comparison is correct\n");
  }
  else
    printf("JSON integer and double comparison failed\n");
  json_object_put(int5);
  json_object_put(dbl5);
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
int main(int argc, char **argv)
{
  struct json_object *int1 = json_object_new_int(0);
  struct json_object *int2 = json_object_new_int(1);
  struct json_object *int3 = json_object_new_int(1);
  struct json_object *int4 = json_object_new_int(-1);
  struct json_object *uint1 = json_object_new_uint64(0);
  struct json_object *uint2 = json_object_new_uint64(1);
  struct json_object *uint3 = json_object_new_uint64(1);
  struct json_object *uint4 = json_object_new_uint64(((uint64_t) INT64_MAX) + 100);
  if (!json_object_equal(int1, int2))
  {
    printf("JSON integer comparison is correct\n");
  }
  else
    printf("JSON integer comparison failed\n");
  if (json_object_equal(int1, int1))
  {
    printf("JSON same object comparison is correct\n");
  }
  else
    printf("JSON same object comparison failed\n");
  if (json_object_equal(int2, int3))
  {
    printf("JSON same integer comparison is correct\n");
  }
  else
    printf("JSON same integer comparison failed\n");
  if (!json_object_equal(uint1, uint2))
  {
    printf("JSON usigned integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer comparison failed\n");
  if (json_object_equal(uint1, uint1))
  {
    printf("JSON same usigned object comparison is correct\n");
  }
  else
    printf("JSON same usigned object comparison failed\n");
  if (json_object_equal(uint2, uint3))
  {
    printf("JSON same usigned integer comparison is correct\n");
  }
  else
    printf("JSON same usigned integer comparison failed\n");
  if (json_object_equal(int2, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int2, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (json_object_equal(uint2, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint2, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  json_object_put(int1);
  json_object_put(int2);
  json_object_put(int3);
  json_object_put(int4);
  json_object_put(uint1);
  json_object_put(uint2);
  json_object_put(uint3);
  json_object_put(uint4);
  struct json_object *str1 = json_object_new_string("TESTSTRING");
  struct json_object *str2 = json_object_new_string("TESTSTRING");
  struct json_object *str3 = json_object_new_string("DIFFERENT");
  if (json_object_equal(str1, str2))
  {
    printf("Comparing equal strings is correct\n");
  }
  else
    printf("Comparing equal strings failed\n");
  if (!json_object_equal(str1, str3))
  {
    printf("Comparing different strings is correct\n");
  }
  else
    printf("Comparing different strings failed\n");
  json_object_put(str1);
  json_object_put(str2);
  json_object_put(str3);
  struct json_object *dbl1 = json_object_new_double(3.14159);
  struct json_object *dbl2 = json_object_new_double(3.14159);
  struct json_object *dbl3 = json_object_new_double(3.0);
  if (json_object_equal(dbl1, dbl2))
  {
    printf("Comparing equal doubles is correct\n");
  }
  else
    printf("Comparing equal doubles failed\n");
  if (!json_object_equal(dbl1, dbl3))
  {
    printf("Comparing different doubles is correct\n");
  }
  else
    printf("Comparing different doubles failed\n");
  json_object_put(dbl1);
  json_object_put(dbl2);
  json_object_put(dbl3);
  struct json_object *ar1 = json_object_new_array();
  struct json_object *ar2 = json_object_new_array();
  struct json_object *ar3 = json_object_new_array();
  struct json_object *ar4 = json_object_new_array();
  json_object_array_add(ar1, json_object_new_int(1));
  json_object_array_add(ar1, json_object_new_int(2));
  json_object_array_add(ar2, json_object_new_int(1));
  json_object_array_add(ar2, json_object_new_int(2));
  json_object_array_add(ar3, json_object_new_int(1));
  json_object_array_add(ar3, json_object_new_int(1));
  if (json_object_equal(ar1, ar2))
  {
    printf("Comparing equal arrays is correct\n");
  }
  else
    printf("Comparing equal arrays failed\n");
  json_object_array_add(ar2, json_object_new_int(1));
  if (!json_object_equal(ar1, ar2))
  {
    printf("Comparing arrays of different len is correct\n");
  }
  else
    printf("Comparing arrays of different len failed\n");
  if (!json_object_equal(ar1, ar3))
  {
    printf("Comparing different arrays is correct\n");
  }
  else
    printf("Comparing different arrays failed\n");
  if (!json_object_equal(ar1, ar4))
  {
    printf("Comparing different arrays (one empty) is correct\n");
  }
  else
    printf("Comparing different arrays (one empty) failed\n");
  json_object_put(ar1);
  json_object_put(ar2);
  json_object_put(ar3);
  json_object_put(ar4);
  struct json_object *obj1 = json_object_new_object();
  struct json_object *obj2 = json_object_new_object();
  json_object_object_add(obj1, "test1", json_object_new_int(123));
  json_object_object_add(obj1, "test2", json_object_new_int(321));
  json_object_object_add(obj1, "test3", json_object_new_int(320));
  json_object_object_add(obj1, "test4", json_object_new_int(319));
  json_object_object_add(obj1, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test4", json_object_new_int(319));
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test2", json_object_new_int(321));
  json_object_object_add(obj2, "test1", json_object_new_int(123));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing JSON object with different key order is correct\n");
  }
  else
    printf("Comparing JSON object with different key order is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(234));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test6", json_object_new_int(321));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test6", json_object_new_int(321));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test7", json_object_new_int(322));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_put(obj1);
  json_object_put(obj2);
  struct json_object *int5 = json_object_new_int(0);
  struct json_object *dbl5 = json_object_new_double(3.14159);
  if (!json_object_equal(int5, 0))
  {
    printf("JSON integer and NULL comparison is correct\n");
  }
  else
    printf("JSON integer and NULL comparison failed\n");
  if (!json_object_equal(0, dbl5))
  {
    printf("JSON NULL and double comparison is correct\n");
  }
  else
    printf("JSON NULL and double comparison failed\n");
  if (!json_object_equal(int5, dbl5))
  {
    printf("JSON integer and double comparison is correct\n");
  }
  else
    printf("JSON integer and double comparison failed\n");
  json_object_put(int5);
  json_object_put(dbl5);
  return 0;
}

