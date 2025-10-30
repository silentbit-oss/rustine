#include <config.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_types.h>
#include <json_util.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <test_parse_int64.c>

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
extern struct json_object *json_object_from_file(const char *filename);
extern struct json_object *json_object_from_fd_ex(int fd, int depth);
extern struct json_object *json_object_from_fd(int fd);
extern int json_object_to_file(const char *filename, struct json_object *obj);
extern int json_object_to_file_ext(const char *filename, struct json_object *obj, int flags);
extern int json_object_to_fd(int fd, struct json_object *obj, int flags);
extern const char *json_util_get_last_err(void);
extern int json_parse_int64(const char *buf, int64_t *retval);
extern int json_parse_uint64(const char *buf, uint64_t *retval);
extern int json_parse_double(const char *buf, double *retval);
extern const char *json_type_to_name(enum json_type o_type);
void checkit(const char *buf)
{
  int64_t cint64 = -666;
  int retval = json_parse_int64(buf, &cint64);
  printf("buf=%s parseit=%d, value=%d \n", buf, retval, cint64);
}

void checkit_uint(const char *buf)
{
  uint64_t cuint64 = 666;
  int retval = json_parse_uint64(buf, &cuint64);
  printf("buf=%s parseit=%d, value=%u \n", buf, retval, cuint64);
}

int main(int argc, char **argv)
{
  char buf[100];
  printf("==========json_parse_int64() test===========\n");
  checkit("x");
  checkit("0");
  checkit("-0");
  checkit("00000000");
  checkit("-00000000");
  checkit("1");
  strcpy(buf, "2147483647");
  checkit(buf);
  strcpy(buf, "-1");
  checkit(buf);
  strcpy(buf, "   -1");
  checkit(buf);
  strcpy(buf, "00001234");
  checkit(buf);
  strcpy(buf, "0001234x");
  checkit(buf);
  strcpy(buf, "-00001234");
  checkit(buf);
  strcpy(buf, "-00001234x");
  checkit(buf);
  strcpy(buf, "4294967295");
  checkit(buf);
  strcpy(buf, "4294967296");
  checkit(buf);
  strcpy(buf, "21474836470");
  checkit(buf);
  strcpy(buf, "31474836470");
  checkit(buf);
  strcpy(buf, "-2147483647");
  checkit(buf);
  strcpy(buf, "-2147483648");
  checkit(buf);
  strcpy(buf, "-2147483649");
  checkit(buf);
  strcpy(buf, "-21474836480");
  checkit(buf);
  strcpy(buf, "9223372036854775806");
  checkit(buf);
  strcpy(buf, "9223372036854775807");
  checkit(buf);
  strcpy(buf, "9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775809");
  checkit(buf);
  strcpy(buf, "18446744073709551614");
  checkit(buf);
  strcpy(buf, "18446744073709551615");
  checkit(buf);
  strcpy(buf, "18446744073709551616");
  checkit(buf);
  strcpy(buf, "-18446744073709551616");
  checkit(buf);
  strcpy(buf, "123");
  checkit(buf);
  printf("\n==========json_parse_uint64() test===========\n");
  checkit_uint("x");
  checkit_uint("0");
  checkit_uint("-0");
  checkit_uint("00000000");
  checkit_uint("-00000000");
  checkit_uint("1");
  strcpy(buf, "2147483647");
  checkit_uint(buf);
  strcpy(buf, "-1");
  checkit_uint(buf);
  strcpy(buf, "-9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "   1");
  checkit_uint(buf);
  strcpy(buf, "00001234");
  checkit_uint(buf);
  strcpy(buf, "0001234x");
  checkit_uint(buf);
  strcpy(buf, "4294967295");
  checkit_uint(buf);
  strcpy(buf, "4294967296");
  checkit_uint(buf);
  strcpy(buf, "21474836470");
  checkit_uint(buf);
  strcpy(buf, "31474836470");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775806");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775807");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551614");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551615");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551616");
  checkit_uint(buf);
  strcpy(buf, "123");
  checkit_uint(buf);
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
extern struct json_object *json_object_from_file(const char *filename);
extern struct json_object *json_object_from_fd_ex(int fd, int depth);
extern struct json_object *json_object_from_fd(int fd);
extern int json_object_to_file(const char *filename, struct json_object *obj);
extern int json_object_to_file_ext(const char *filename, struct json_object *obj, int flags);
extern int json_object_to_fd(int fd, struct json_object *obj, int flags);
extern const char *json_util_get_last_err(void);
extern int json_parse_int64(const char *buf, int64_t *retval);
extern int json_parse_uint64(const char *buf, uint64_t *retval);
extern int json_parse_double(const char *buf, double *retval);
extern const char *json_type_to_name(enum json_type o_type);
void checkit(const char *buf)
{
  int64_t cint64 = -666;
  int retval = json_parse_int64(buf, &cint64);
  printf("buf=%s parseit=%d, value=%d \n", buf, retval, cint64);
}

void checkit_uint(const char *buf)
{
  uint64_t cuint64 = 666;
  int retval = json_parse_uint64(buf, &cuint64);
  printf("buf=%s parseit=%d, value=%u \n", buf, retval, cuint64);
}

int main(int argc, char **argv)
{
  char buf[100];
  printf("==========json_parse_int64() test===========\n");
  checkit("x");
  checkit("0");
  checkit("-0");
  checkit("00000000");
  checkit("-00000000");
  checkit("1");
  strcpy(buf, "2147483647");
  checkit(buf);
  strcpy(buf, "-1");
  checkit(buf);
  strcpy(buf, "   -1");
  checkit(buf);
  strcpy(buf, "00001234");
  checkit(buf);
  strcpy(buf, "0001234x");
  checkit(buf);
  strcpy(buf, "-00001234");
  checkit(buf);
  strcpy(buf, "-00001234x");
  checkit(buf);
  strcpy(buf, "4294967295");
  checkit(buf);
  strcpy(buf, "4294967296");
  checkit(buf);
  strcpy(buf, "21474836470");
  checkit(buf);
  strcpy(buf, "31474836470");
  checkit(buf);
  strcpy(buf, "-2147483647");
  checkit(buf);
  strcpy(buf, "-2147483648");
  checkit(buf);
  strcpy(buf, "-2147483649");
  checkit(buf);
  strcpy(buf, "-21474836480");
  checkit(buf);
  strcpy(buf, "9223372036854775806");
  checkit(buf);
  strcpy(buf, "9223372036854775807");
  checkit(buf);
  strcpy(buf, "9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775809");
  checkit(buf);
  strcpy(buf, "18446744073709551614");
  checkit(buf);
  strcpy(buf, "18446744073709551615");
  checkit(buf);
  strcpy(buf, "18446744073709551616");
  checkit(buf);
  strcpy(buf, "-18446744073709551616");
  checkit(buf);
  strcpy(buf, "123");
  checkit(buf);
  printf("\n==========json_parse_uint64() test===========\n");
  checkit_uint("x");
  checkit_uint("0");
  checkit_uint("-0");
  checkit_uint("00000000");
  checkit_uint("-00000000");
  checkit_uint("1");
  strcpy(buf, "2147483647");
  checkit_uint(buf);
  strcpy(buf, "-1");
  checkit_uint(buf);
  strcpy(buf, "-9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "   1");
  checkit_uint(buf);
  strcpy(buf, "00001234");
  checkit_uint(buf);
  strcpy(buf, "0001234x");
  checkit_uint(buf);
  strcpy(buf, "4294967295");
  checkit_uint(buf);
  strcpy(buf, "4294967296");
  checkit_uint(buf);
  strcpy(buf, "21474836470");
  checkit_uint(buf);
  strcpy(buf, "31474836470");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775806");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775807");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551614");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551615");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551616");
  checkit_uint(buf);
  strcpy(buf, "123");
  checkit_uint(buf);
  return 0;
}

