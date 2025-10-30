#include <arraylist.h>
#include <assert.h>
#include <config.h>
#include <debug.h>
#include <errno.h>
#include <inttypes.h>
#include <json.h>
#include <json_c_version.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_object_iterator.h>
#include <json_patch.h>
#include <json_pointer.h>
#include <json_tokener.h>
#include <json_types.h>
#include <json_util.h>
#include <limits.h>
#include <linkhash.h>
#include <printbuf.h>
#include <snprintf_compat.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strerror_override.h>
#include <string.h>
#include <test_json_patch.c>

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
extern char *_json_c_strerror(int errno_in);
typedef void array_list_free_fn(void *data);
struct array_list
{
  void **array;
  size_t length;
  size_t size;
  array_list_free_fn *free_fn;
};
typedef struct array_list array_list;
extern struct array_list *array_list_new(array_list_free_fn *free_fn);
extern struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size);
extern void array_list_free(struct array_list *al);
extern void *array_list_get_idx(struct array_list *al, size_t i);
extern int array_list_insert_idx(struct array_list *al, size_t i, void *data);
extern int array_list_put_idx(struct array_list *al, size_t i, void *data);
extern int array_list_add(struct array_list *al, void *data);
extern size_t array_list_length(struct array_list *al);
extern void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *));
extern void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *));
extern int array_list_del_idx(struct array_list *arr, size_t idx, size_t count);
extern int array_list_shrink(struct array_list *arr, size_t empty_slots);
extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
extern const char *json_c_version(void);
extern int json_c_version_num(void);
struct json_object_iter_info_;
struct json_object_iterator
{
  const void *opaque_;
};
struct json_object;
extern struct json_object_iterator json_object_iter_init_default(void);
extern struct json_object_iterator json_object_iter_begin(struct json_object *obj);
extern struct json_object_iterator json_object_iter_end(const struct json_object *obj);
extern void json_object_iter_next(struct json_object_iterator *iter);
extern const char *json_object_iter_peek_name(const struct json_object_iterator *iter);
extern struct json_object *json_object_iter_peek_value(const struct json_object_iterator *iter);
extern json_bool json_object_iter_equal(const struct json_object_iterator *iter1, const struct json_object_iterator *iter2);
extern int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res);
extern int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...);
extern int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value);
extern int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...);
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
};
extern int json_patch_apply(struct json_object *copy_from, struct json_object *patch, struct json_object **base, struct json_patch_error *patch_error);
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
};
enum json_tokener_state
{
  json_tokener_state_eatws,
  json_tokener_state_start,
  json_tokener_state_finish,
  json_tokener_state_null,
  json_tokener_state_comment_start,
  json_tokener_state_comment,
  json_tokener_state_comment_eol,
  json_tokener_state_comment_end,
  json_tokener_state_string,
  json_tokener_state_string_escape,
  json_tokener_state_escape_unicode,
  json_tokener_state_escape_unicode_need_escape,
  json_tokener_state_escape_unicode_need_u,
  json_tokener_state_boolean,
  json_tokener_state_number,
  json_tokener_state_array,
  json_tokener_state_array_add,
  json_tokener_state_array_sep,
  json_tokener_state_object_field_start,
  json_tokener_state_object_field,
  json_tokener_state_object_field_end,
  json_tokener_state_object_value,
  json_tokener_state_object_value_add,
  json_tokener_state_object_sep,
  json_tokener_state_array_after_sep,
  json_tokener_state_object_field_start_after_sep,
  json_tokener_state_inf
};
struct json_tokener_srec
{
  enum json_tokener_state state;
  enum json_tokener_state saved_state;
  struct json_object *obj;
  struct json_object *current;
  char *obj_field_name;
};
struct json_tokener
{
  char *str;
  struct printbuf *pb;
  int max_depth;
  int depth;
  int is_double;
  int st_pos;
  int char_offset;
  enum json_tokener_error err;
  unsigned int ucs_char;
  unsigned int high_surrogate;
  char quote_char;
  struct json_tokener_srec *stack;
  int flags;
};
extern size_t json_tokener_get_parse_end(struct json_tokener *tok);
typedef struct json_tokener json_tokener;
extern const char *json_tokener_error_desc(enum json_tokener_error jerr);
extern enum json_tokener_error json_tokener_get_error(struct json_tokener *tok);
extern struct json_tokener *json_tokener_new(void);
extern struct json_tokener *json_tokener_new_ex(int depth);
extern void json_tokener_free(struct json_tokener *tok);
extern void json_tokener_reset(struct json_tokener *tok);
extern struct json_object *json_tokener_parse(const char *str);
extern struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error);
extern void json_tokener_set_flags(struct json_tokener *tok, int flags);
extern struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len);
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
int json_global_set_string_hash(const int h);
struct lh_entry;
typedef void lh_entry_free_fn(struct lh_entry *e);
typedef unsigned long lh_hash_fn(const void *k);
typedef int lh_equal_fn(const void *k1, const void *k2);
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
};
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
};
typedef struct lh_table lh_table;
extern struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn);
extern struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn);
extern struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn);
extern void lh_table_free(struct lh_table *t);
extern int lh_table_insert(struct lh_table *t, const void *k, const void *v);
extern int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts);
extern struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k);
extern struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h);
extern json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v);
extern int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e);
extern int lh_table_delete(struct lh_table *t, const void *k);
extern int lh_table_length(struct lh_table *t);
int lh_table_resize(struct lh_table *t, int new_size);
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}

inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}

inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
}

inline static int lh_entry_k_is_constant(const struct lh_entry *e)
{
  return e->k_is_constant;
}

inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}

inline static void lh_entry_set_val(struct lh_entry *e, void *newval)
{
  e->v = newval;
}

inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}

inline static struct lh_entry *lh_entry_prev(const struct lh_entry *e)
{
  return e->prev;
}

void test_json_patch_op(struct json_object *jo)
{
  const char *comment = json_object_get_string(json_object_object_get(jo, "comment"));
  struct json_object *doc = json_object_object_get(jo, "doc");
  struct json_object *patch = json_object_object_get(jo, "patch");
  struct json_object *expected = 0;
  json_bool have_expected = json_object_object_get_ex(jo, "expected", &expected);
  struct json_object *error = json_object_object_get(jo, "error");
  const char *error_s = json_object_get_string(error);
  struct json_object *res = 0;
  unsigned int res_idx = 0;
  int ret;
  printf("Testing '%s', doc '%s' patch '%s' : ", (comment) ? (comment) : (error_s), json_object_get_string(doc), json_object_get_string(patch));
  if ((!error) && (!have_expected))
  {
    printf("BAD TEST - no expected or error conditions in test: %s\n", json_object_to_json_string(jo));
    assert(0);
  }
  fflush(stdout);
  struct json_patch_error jperr;
  if (error)
  {
    assert((-1) == json_patch_apply(doc, patch, &(&res[res_idx]), &jperr));
    assert(jperr.errno_code != 0);
    printf("OK\n");
    printf(" => json_patch_apply failed as expected: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    json_object_put(res);
  }
  else
  {
    helper_test_json_patch_op_1(&res_idx, &ret, doc, patch, expected, res, jperr);
  }
}

void test_json_patch_using_file(const char *testdir, const char *filename)
{
  char full_filename[256];
  (void) snprintf(full_filename, sizeof(full_filename), "%s/%s", testdir, filename);
  size_t ii;
  printf("Testing using file %s\n", filename);
  json_object *jo = json_object_from_file(full_filename);
  if (!jo)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", full_filename, _json_c_strerror(errno));
    exit(1);
  }
  for (ii = 0; ii < json_object_array_length(jo); ii += 1)
  {
    struct json_object *jo1 = json_object_array_get_idx(jo, ii);
    test_json_patch_op(jo1);
  }

  json_object_put(jo);
}

int main(int argc, char **argv)
{
  const char *testdir;
  unsigned int testdir_idx = 0;
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <testdir>\n  <testdir> is the location of input files\n", argv[0]);
    return 1;
  }
  testdir_idx = argv[1];
  if (strncmp(json_c_version(), "0.18.99", sizeof("0.18.99")))
  {
    printf("FAIL: Output from json_c_version(): %s does not match %s", json_c_version(), "0.18.99");
    return 1;
  }
  if (json_c_version_num() != (((0 << 16) | (18 << 8)) | 99))
  {
    printf("FAIL: Output from json_c_version_num(): %d does not match %d", json_c_version_num(), ((0 << 16) | (18 << 8)) | 99);
    return 1;
  }
  test_json_patch_using_file(testdir, "json_patch_spec_tests.json");
  test_json_patch_using_file(testdir, "json_patch_tests.json");
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
extern char *_json_c_strerror(int errno_in);
typedef void array_list_free_fn(void *data);
struct array_list
{
  void **array;
  size_t length;
  size_t size;
  array_list_free_fn *free_fn;
};
typedef struct array_list array_list;
extern struct array_list *array_list_new(array_list_free_fn *free_fn);
extern struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size);
extern void array_list_free(struct array_list *al);
extern void *array_list_get_idx(struct array_list *al, size_t i);
extern int array_list_insert_idx(struct array_list *al, size_t i, void *data);
extern int array_list_put_idx(struct array_list *al, size_t i, void *data);
extern int array_list_add(struct array_list *al, void *data);
extern size_t array_list_length(struct array_list *al);
extern void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *));
extern void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *));
extern int array_list_del_idx(struct array_list *arr, size_t idx, size_t count);
extern int array_list_shrink(struct array_list *arr, size_t empty_slots);
extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
extern const char *json_c_version(void);
extern int json_c_version_num(void);
struct json_object_iter_info_;
struct json_object_iterator
{
  const void *opaque_;
};
struct json_object;
extern struct json_object_iterator json_object_iter_init_default(void);
extern struct json_object_iterator json_object_iter_begin(struct json_object *obj);
extern struct json_object_iterator json_object_iter_end(const struct json_object *obj);
extern void json_object_iter_next(struct json_object_iterator *iter);
extern const char *json_object_iter_peek_name(const struct json_object_iterator *iter);
extern struct json_object *json_object_iter_peek_value(const struct json_object_iterator *iter);
extern json_bool json_object_iter_equal(const struct json_object_iterator *iter1, const struct json_object_iterator *iter2);
extern int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res);
extern int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...);
extern int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value);
extern int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...);
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
};
extern int json_patch_apply(struct json_object *copy_from, struct json_object *patch, struct json_object **base, struct json_patch_error *patch_error);
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
};
enum json_tokener_state
{
  json_tokener_state_eatws,
  json_tokener_state_start,
  json_tokener_state_finish,
  json_tokener_state_null,
  json_tokener_state_comment_start,
  json_tokener_state_comment,
  json_tokener_state_comment_eol,
  json_tokener_state_comment_end,
  json_tokener_state_string,
  json_tokener_state_string_escape,
  json_tokener_state_escape_unicode,
  json_tokener_state_escape_unicode_need_escape,
  json_tokener_state_escape_unicode_need_u,
  json_tokener_state_boolean,
  json_tokener_state_number,
  json_tokener_state_array,
  json_tokener_state_array_add,
  json_tokener_state_array_sep,
  json_tokener_state_object_field_start,
  json_tokener_state_object_field,
  json_tokener_state_object_field_end,
  json_tokener_state_object_value,
  json_tokener_state_object_value_add,
  json_tokener_state_object_sep,
  json_tokener_state_array_after_sep,
  json_tokener_state_object_field_start_after_sep,
  json_tokener_state_inf
};
struct json_tokener_srec
{
  enum json_tokener_state state;
  enum json_tokener_state saved_state;
  struct json_object *obj;
  struct json_object *current;
  char *obj_field_name;
};
struct json_tokener
{
  char *str;
  struct printbuf *pb;
  int max_depth;
  int depth;
  int is_double;
  int st_pos;
  int char_offset;
  enum json_tokener_error err;
  unsigned int ucs_char;
  unsigned int high_surrogate;
  char quote_char;
  struct json_tokener_srec *stack;
  int flags;
};
extern size_t json_tokener_get_parse_end(struct json_tokener *tok);
typedef struct json_tokener json_tokener;
extern const char *json_tokener_error_desc(enum json_tokener_error jerr);
extern enum json_tokener_error json_tokener_get_error(struct json_tokener *tok);
extern struct json_tokener *json_tokener_new(void);
extern struct json_tokener *json_tokener_new_ex(int depth);
extern void json_tokener_free(struct json_tokener *tok);
extern void json_tokener_reset(struct json_tokener *tok);
extern struct json_object *json_tokener_parse(const char *str);
extern struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error);
extern void json_tokener_set_flags(struct json_tokener *tok, int flags);
extern struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len);
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
int json_global_set_string_hash(const int h);
struct lh_entry;
typedef void lh_entry_free_fn(struct lh_entry *e);
typedef unsigned long lh_hash_fn(const void *k);
typedef int lh_equal_fn(const void *k1, const void *k2);
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
};
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
};
typedef struct lh_table lh_table;
extern struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn);
extern struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn);
extern struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn);
extern void lh_table_free(struct lh_table *t);
extern int lh_table_insert(struct lh_table *t, const void *k, const void *v);
extern int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts);
extern struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k);
extern struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h);
extern json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v);
extern int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e);
extern int lh_table_delete(struct lh_table *t, const void *k);
extern int lh_table_length(struct lh_table *t);
int lh_table_resize(struct lh_table *t, int new_size);
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}

inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}

inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
}

inline static int lh_entry_k_is_constant(const struct lh_entry *e)
{
  return e->k_is_constant;
}

inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}

inline static void lh_entry_set_val(struct lh_entry *e, void *newval)
{
  e->v = newval;
}

inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}

inline static struct lh_entry *lh_entry_prev(const struct lh_entry *e)
{
  return e->prev;
}

void test_json_patch_op(struct json_object *jo)
{
  const char *comment = json_object_get_string(json_object_object_get(jo, "comment"));
  struct json_object *doc = json_object_object_get(jo, "doc");
  struct json_object *patch = json_object_object_get(jo, "patch");
  struct json_object *expected = 0;
  json_bool have_expected = json_object_object_get_ex(jo, "expected", &expected);
  struct json_object *error = json_object_object_get(jo, "error");
  const char *error_s = json_object_get_string(error);
  struct json_object *res = 0;
  unsigned int res_idx = 0;
  int ret;
  printf("Testing '%s', doc '%s' patch '%s' : ", (comment) ? (comment) : (error_s), json_object_get_string(doc), json_object_get_string(patch));
  if ((!error) && (!have_expected))
  {
    printf("BAD TEST - no expected or error conditions in test: %s\n", json_object_to_json_string(jo));
    assert(0);
  }
  fflush(stdout);
  struct json_patch_error jperr;
  if (error)
  {
    assert((-1) == json_patch_apply(doc, patch, &(&res[res_idx]), &jperr));
    assert(jperr.errno_code != 0);
    printf("OK\n");
    printf(" => json_patch_apply failed as expected: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    json_object_put(res);
  }
  else
  {
    ret = json_patch_apply(doc, patch, &(&res[res_idx]), &jperr);
    if (ret)
    {
      fprintf(stderr, "json_patch_apply() returned '%d'\n", ret);
      fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
      fprintf(stderr, "Got: %s\n", (res) ? (json_object_get_string(res)) : ("(null)"));
      fprintf(stderr, "json_patch_apply failed: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
      fflush(stderr);
      assert(0);
    }
    assert(jperr.errno_code == 0);
    ret = json_object_equal(expected, res);
    if (ret == 0)
    {
      fprintf(stderr, "json_object_equal() returned '%d'\n", ret);
      fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
      fprintf(stderr, "Got: %s\n", json_object_get_string(res));
      fflush(stderr);
      assert(0);
    }
    json_object_put(res);
    res_idx = 0;
    printf("OK\n");
  }
}

void test_json_patch_using_file(const char *testdir, const char *filename)
{
  char full_filename[256];
  (void) snprintf(full_filename, sizeof(full_filename), "%s/%s", testdir, filename);
  size_t ii;
  printf("Testing using file %s\n", filename);
  json_object *jo = json_object_from_file(full_filename);
  if (!jo)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", full_filename, _json_c_strerror(errno));
    exit(1);
  }
  for (ii = 0; ii < json_object_array_length(jo); ii += 1)
  {
    struct json_object *jo1 = json_object_array_get_idx(jo, ii);
    test_json_patch_op(jo1);
  }

  json_object_put(jo);
}

int main(int argc, char **argv)
{
  const char *testdir;
  unsigned int testdir_idx = 0;
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <testdir>\n  <testdir> is the location of input files\n", argv[0]);
    return 1;
  }
  testdir_idx = argv[1];
  if (strncmp(json_c_version(), "0.18.99", sizeof("0.18.99")))
  {
    printf("FAIL: Output from json_c_version(): %s does not match %s", json_c_version(), "0.18.99");
    return 1;
  }
  if (json_c_version_num() != (((0 << 16) | (18 << 8)) | 99))
  {
    printf("FAIL: Output from json_c_version_num(): %d does not match %d", json_c_version_num(), ((0 << 16) | (18 << 8)) | 99);
    return 1;
  }
  test_json_patch_using_file(testdir, "json_patch_spec_tests.json");
  test_json_patch_using_file(testdir, "json_patch_tests.json");
  return 0;
}

void helper_test_json_patch_op_1(unsigned int * const res_idx_ref, int * const ret_ref, struct json_object * const doc, struct json_object * const patch, struct json_object * const expected, struct json_object * const res, struct json_patch_error jperr)
{
  unsigned int res_idx = *res_idx_ref;
  int ret = *ret_ref;
  ret = json_patch_apply(doc, patch, &(&res[res_idx]), &jperr);
  if (ret)
  {
    fprintf(stderr, "json_patch_apply() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", (res) ? (json_object_get_string(res)) : ("(null)"));
    fprintf(stderr, "json_patch_apply failed: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    fflush(stderr);
    assert(0);
  }
  assert(jperr.errno_code == 0);
  ret = json_object_equal(expected, res);
  if (ret == 0)
  {
    fprintf(stderr, "json_object_equal() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", json_object_get_string(res));
    fflush(stderr);
    assert(0);
  }
  json_object_put(res);
  res_idx = 0;
  printf("OK\n");
  *res_idx_ref = res_idx;
  *ret_ref = ret;
}

