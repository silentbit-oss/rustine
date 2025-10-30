#include <arraylist.h>
#include <assert.h>
#include <debug.h>
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
#include <json_visit.h>
#include <linkhash.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <test_parse.c>

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

typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg);
extern int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg);
static void test_basic_parse(void);
static void test_utf8_parse(void);
static void test_verbose_parse(void);
static void test_incremental_parse(void);
int main(void)
{
  if (0)
  {
    mc_set_debug(1);
  }
  static const char separator[] = "==================================";
  test_basic_parse();
  puts(separator);
  test_utf8_parse();
  puts(separator);
  test_verbose_parse();
  puts(separator);
  test_incremental_parse();
  puts(separator);
  return 0;
}

static json_c_visit_userfunc clear_serializer;
static void do_clear_serializer(json_object *jso);
static void single_incremental_parse(const char *test_string, int clear_serializer)
{
  size_t ii;
  int chunksize = atoi(getenv("TEST_PARSE_CHUNKSIZE"));
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  enum json_tokener_error jerr;
  json_object *all_at_once_obj;
  unsigned int all_at_once_obj_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  const char *all_at_once_str;
  unsigned int all_at_once_str_idx = 0;
  const char *new_str;
  unsigned int new_str_idx = 0;
  new_obj_idx = 0;
  assert(chunksize > 0);
  all_at_once_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(all_at_once_obj);
  }
  all_at_once_str_idx = json_object_to_json_string(all_at_once_obj);
  tok_idx = json_tokener_new();
  size_t test_string_len = strlen(test_string) + 1;
  for (ii = 0; ii < test_string_len; ii += chunksize)
  {
    int len_to_parse = chunksize;
    if ((ii + chunksize) > test_string_len)
    {
      len_to_parse = test_string_len - ii;
    }
    if (getenv("TEST_PARSE_DEBUG") != 0)
    {
      printf(" chunk: %.*s\n", len_to_parse, &test_string[ii]);
    }
    new_obj_idx = json_tokener_parse_ex(tok, &test_string[ii], len_to_parse);
    jerr = json_tokener_get_error(tok);
    if ((jerr != json_tokener_continue) || (&new_obj[new_obj_idx]))
    {
      break;
    }
  }

  if (clear_serializer && (&new_obj[new_obj_idx]))
  {
    do_clear_serializer(new_obj);
  }
  new_str_idx = json_object_to_json_string(new_obj);
  if (strcmp(all_at_once_str, new_str) != 0)
  {
    printf("ERROR: failed to parse (%s) in %d byte chunks: %s != %s\n", test_string, chunksize, all_at_once_str, new_str);
  }
  json_tokener_free(tok);
  if (all_at_once_obj)
  {
    json_object_put(all_at_once_obj);
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
}

static void single_basic_parse(const char *test_string, int clear_serializer)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(new_obj);
  }
  printf("new_obj.to_string(%s)=%s\n", test_string, json_object_to_json_string(new_obj));
  json_object_put(new_obj);
  if (getenv("TEST_PARSE_CHUNKSIZE") != 0)
  {
    single_incremental_parse(test_string, clear_serializer);
  }
}

static void test_basic_parse(void)
{
  single_basic_parse("\"\003\"", 0);
  single_basic_parse("/* hello */\"foo\"", 0);
  single_basic_parse("// hello\n\"foo\"", 0);
  single_basic_parse("\"foo\"blue", 0);
  single_basic_parse("\'foo\'", 0);
  single_basic_parse("\"\\u0041\\u0042\\u0043\"", 0);
  single_basic_parse("\"\\u4e16\\u754c\\u00df\"", 0);
  single_basic_parse("\"\\u4E16\"", 0);
  single_basic_parse("\"\\u4e1\"", 0);
  single_basic_parse("\"\\u4e1@\"", 0);
  single_basic_parse("\"\\ud840\\u4e16\"", 0);
  single_basic_parse("\"\\ud840\"", 0);
  single_basic_parse("\"\\udd27\"", 0);
  single_basic_parse("[9,'\\uDAD", 0);
  single_basic_parse("null", 0);
  single_basic_parse("NaN", 0);
  single_basic_parse("-NaN", 0);
  single_basic_parse("Inf", 0);
  single_basic_parse("inf", 0);
  single_basic_parse("Infinity", 0);
  single_basic_parse("infinity", 0);
  single_basic_parse("-Infinity", 0);
  single_basic_parse("-infinity", 0);
  single_basic_parse("{ \"min\": Infinity, \"max\": -Infinity}", 0);
  single_basic_parse("Infinity!", 0);
  single_basic_parse("Infinitynull", 0);
  single_basic_parse("InfinityXXXX", 0);
  single_basic_parse("-Infinitynull", 0);
  single_basic_parse("-InfinityXXXX", 0);
  single_basic_parse("Infinoodle", 0);
  single_basic_parse("InfinAAA", 0);
  single_basic_parse("-Infinoodle", 0);
  single_basic_parse("-InfinAAA", 0);
  single_basic_parse("True", 0);
  single_basic_parse("False", 0);
  single_basic_parse("tRue", 0);
  single_basic_parse("fAlse", 0);
  single_basic_parse("nAn", 0);
  single_basic_parse("iNfinity", 0);
  single_basic_parse("12", 0);
  single_basic_parse("12.3", 0);
  single_basic_parse("12.3.4", 0);
  single_basic_parse("2015-01-15", 0);
  single_basic_parse("12.3xxx", 0);
  single_basic_parse("12.3{\"a\":123}", 0);
  single_basic_parse("12.3\n", 0);
  single_basic_parse("12.3 ", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3e512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E51.2}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512E12}", 0);
  single_basic_parse("[\"\\n\"]", 0);
  single_basic_parse("[\"\\nabc\\n\"]", 0);
  single_basic_parse("[null]", 0);
  single_basic_parse("[]", 0);
  single_basic_parse("[false]", 0);
  single_basic_parse("[\"abc\",null,\"def\",12]", 0);
  single_basic_parse("{}", 0);
  single_basic_parse("{ \"foo\": \"bar\" }", 0);
  single_basic_parse("{ \'foo\': \'bar\' }", 0);
  single_basic_parse("{ \"foo\": \"bar\", \"baz\": null, \"bool0\": true }", 0);
  single_basic_parse("{ \"foo\": [null, \"foo\"] }", 0);
  single_basic_parse("{ \"abc\": 12, \"foo\": \"bar\", \"bool0\": false, \"bool1\": true, \"arr\": [ 1, 2, 3, null, 5 ] }", 0);
  single_basic_parse("{ \"abc\": \"blue\nred\\ngreen\" }", 0);
  single_basic_parse("null", 1);
  single_basic_parse("false", 1);
  single_basic_parse("[0e]", 1);
  single_basic_parse("[0e+]", 1);
  single_basic_parse("[0e+-1]", 1);
  single_basic_parse("\"hello world!\"", 1);
  single_basic_parse("[9223372036854775806]", 1);
  single_basic_parse("[9223372036854775807]", 1);
  single_basic_parse("[9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775807]", 1);
  single_basic_parse("[-9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775809]", 1);
  single_basic_parse("[18446744073709551614]", 1);
  single_basic_parse("[18446744073709551615]", 1);
  single_basic_parse("[18446744073709551616]", 1);
}

static void test_utf8_parse(void)
{
  const char *utf8_bom = "\xEF\xBB\xBF";
  const char *utf8_bom_and_chars = "\xEF\xBB\xBF{}";
  single_basic_parse(utf8_bom, 0);
  single_basic_parse(utf8_bom_and_chars, 0);
}

static void do_clear_serializer(json_object *jso)
{
  json_c_visit(jso, 0, clear_serializer, 0);
}

static int clear_serializer(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  if (jso)
  {
    json_object_set_serializer(jso, 0, 0, 0);
  }
  return 0;
}

static void test_verbose_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error error = json_tokener_success;
  new_obj_idx = json_tokener_parse_verbose("{ foo }", &error);
  assert(error == json_tokener_error_parse_object_key_name);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("{ foo }");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("foo");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_verbose("foo", &error);
  assert((&new_obj[new_obj_idx]) == 0);
  assert(error == json_tokener_error_parse_boolean);
  puts("json_tokener_parse_verbose() OK");
}

struct incremental_step
{
  const char *string_to_parse;
  int length;
  int char_offset;
  enum json_tokener_error expected_error;
  int reset_tokener;
  int tok_flags;
} incremental_steps[] = {{"{ \"foo\": 123 }", -1, -1, json_tokener_success, 0, 0}, {"{ \"foo\": 456 }", -1, -1, json_tokener_success, 1, 0}, {"{ \"foo\": 789 }", -1, -1, json_tokener_success, 1, 0}, {"/* hello */{ \"foo\"", -1, -1, json_tokener_continue, 0, 0}, {"/* hello */:/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"\"bar\"/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"}/* hello */", -1, -1, json_tokener_success, 1, 0}, {"/ hello ", -1, 1, json_tokener_error_parse_comment, 1, 0}, {"/* hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"/* hello*\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"// hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}", -1, -1, json_tokener_success, 1, 0}, {"\"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"8", -1, -1, json_tokener_continue, 0, 0}, {"3", -1, -1, json_tokener_continue, 0, 0}, {"4", -1, -1, json_tokener_continue, 0, 0}, {"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"1", -1, -1, json_tokener_continue, 0, 0}, {"e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\u", -1, -1, json_tokener_continue, 0, 0}, {"d8", -1, -1, json_tokener_continue, 0, 0}, {"34", -1, -1, json_tokener_continue, 0, 0}, {"\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd", -1, -1, json_tokener_continue, 0, 0}, {"1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834", -1, -1, json_tokener_continue, 0, 0}, {"\\udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\", -1, -1, json_tokener_continue, 0, 0}, {"udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\ud", -1, -1, json_tokener_continue, 0, 0}, {"d1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\udd", -1, -1, json_tokener_continue, 0, 0}, {"1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud83d\\ude", -1, -1, json_tokener_continue, 0, 0}, {"00 bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0x01}, {"{ \"foo", -1, -1, json_tokener_continue, 1, 0}, {": \"bar\"}", -1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}XXXX", 10, 6, json_tokener_success, 0, 0}, {"XXXX", 4, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"x\": 123 }\"X\"", -1, 11, json_tokener_success, 0, 0}, {"\"Y\"", -1, -1, json_tokener_success, 1, 0}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_error_parse_unexpected, 1, 0x01}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_success, 0, 0x01 | 0x02}, {"{\"b\":8}ignored garbage", -1, 7, json_tokener_success, 1, 0x01 | 0x02}, {"1", 1, 1, json_tokener_continue, 0, 0}, {"2", 2, 1, json_tokener_success, 0, 0}, {"12{", 3, 2, json_tokener_success, 1, 0}, {"[02]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+0", 5, 4, json_tokener_success, 1, 0}, {"[0e+0]", -1, -1, json_tokener_success, 1, 0}, {"0e", 2, 2, json_tokener_continue, 1, 0}, {"0e", 3, 2, json_tokener_success, 1, 0}, {"0e", 3, 2, json_tokener_error_parse_eof, 1, 0x01}, {"[0e]", -1, -1, json_tokener_success, 1, 0}, {"[0e]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+", 3, 3, json_tokener_continue, 1, 0}, {"0e+", 4, 3, json_tokener_success, 1, 0}, {"0e+", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e+]", -1, -1, json_tokener_success, 1, 0}, {"[0e+]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e-", 3, 3, json_tokener_continue, 1, 0}, {"0e-", 4, 3, json_tokener_success, 1, 0}, {"0e-", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e-]", -1, -1, json_tokener_success, 1, 0}, {"[0e-]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e+-", 5, 3, json_tokener_success, 1, 0}, {"0e+-", 5, 3, json_tokener_error_parse_number, 1, 0x01}, {"[0e+-]", -1, 4, json_tokener_error_parse_number, 1, 0}, {"false", 5, 5, json_tokener_continue, 1, 0}, {"false", 6, 5, json_tokener_success, 1, 0}, {"true", 4, 4, json_tokener_continue, 1, 0}, {"true", 5, 4, json_tokener_success, 1, 0}, {"null", 4, 4, json_tokener_continue, 1, 0}, {"null", 5, 4, json_tokener_success, 1, 0}, {"Infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"-infinity", 10, 9, json_tokener_success, 1, 0}, {"-infinity", 10, 1, json_tokener_error_parse_unexpected, 1, 0x01}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"-inf", 4, 4, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"f", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"t", 1, 1, json_tokener_continue, 0, 0}, {"y", 1, 1, json_tokener_continue, 0, 0}, {"", 1, 0, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"ini", 3, 3, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"nfini", 5, 5, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-i", 2, 2, json_tokener_continue, 0, 0}, {"nfinity", 8, 7, json_tokener_success, 1, 0}, {"InfinityX", 10, 8, json_tokener_success, 0, 0}, {"X", 1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"Infinity1234", 13, 8, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"Infinity9999", 8, 8, json_tokener_continue, 0, 0}, {"1234", 5, 0, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"[9223372036854775807]", 22, 21, json_tokener_success, 1, 0}, {"[9223372036854775808]", 22, 21, json_tokener_success, 1, 0}, {"[-9223372036854775808]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"[18446744073709551615]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"18446744073709551616", 21, 20, json_tokener_success, 1, 0}, {"18446744073709551616", 21, 20, json_tokener_error_parse_eof, 1, 0x01}, {"[9223372036854775808.0]", 24, 23, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0x01}, {"[18446744073709551615.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0x01}, {"noodle", 7, 1, json_tokener_error_parse_null, 1, 0}, {"naodle", 7, 2, json_tokener_error_parse_null, 1, 0}, {"track", 6, 2, json_tokener_error_parse_boolean, 1, 0}, {"fail", 5, 2, json_tokener_error_parse_boolean, 1, 0}, {"null123", 8, 4, json_tokener_success, 0, 0}, {&"null123"[4], 4, 3, json_tokener_success, 1, 0}, {"nullx", 6, 4, json_tokener_success, 0, 0}, {&"nullx"[4], 2, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1}{\"b\":2}", 15, 7, json_tokener_success, 0, 0}, {&"{\"a\":1}{\"b\":2}"[7], 8, 7, json_tokener_success, 1, 0}, {&"2015-01-15"[0], 11, 4, json_tokener_success, 1, 0}, {&"2015-01-15"[4], 7, 3, json_tokener_success, 1, 0}, {&"2015-01-15"[7], 4, 3, json_tokener_success, 1, 0}, {&"2015 01 15"[0], 11, 5, json_tokener_success, 1, 0}, {&"2015 01 15"[4], 7, 4, json_tokener_success, 1, 0}, {&"2015 01 15"[7], 4, 3, json_tokener_success, 1, 0}, {"\"blue\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\"\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\\\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\b\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\f\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\n\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\r\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\t\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\/\"", -1, -1, json_tokener_success, 0, 0}, {"\"/\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\a\"", -1, 2, json_tokener_error_parse_string, 1, 0}, {"\'foo\'", -1, 5, json_tokener_success, 1, 0}, {"\'foo\'", -1, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,3]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3}", -1, 6, json_tokener_error_parse_array, 1, 0}, {"{\"a\"}", -1, 4, json_tokener_error_parse_object_key_sep, 1, 0}, {"{\"a\":1]", -1, 6, json_tokener_error_parse_object_value_sep, 1, 0}, {"{\"a\"::1}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1,\"a\":2}", -1, -1, json_tokener_success, 1, 0}, {"\"a\":1}", -1, 3, json_tokener_success, 1, 0}, {"{\"a\":1", -1, -1, json_tokener_continue, 1, 0}, {"[,]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[,1]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[1,2,3,]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3,]", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0x01}, {"{\"a\":1,}", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe4\xb8", -1, 3, json_tokener_error_parse_utf8_string, 0, 0x10}, {"\x96\xe7\x95\x8c\x22", -1, 0, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xcf\x80\xcf\x86\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xf0\xa5\x91\x95\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 5, json_tokener_success, 1, 0}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 6, json_tokener_success, 1, 0}, {"\x20\x20\x22\xe4\xb8\x96\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x20\x20\x81\x22\xe4\xb8\x96\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x5b\x20\x81\x31\x5d", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x49\x6e\x66\x69\x6e\x69\x74\x79", 9, 8, json_tokener_success, 1, 0}, {"\x49\x6e\x66\x81\x6e\x69\x74\x79", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\x5c\x75\x64\x63\x35\x35\x22", 15, 14, json_tokener_success, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\xc0\x75\x64\x63\x35\x35\x22", -1, 8, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x30\x30\x33\x31\xc0\x22", -1, 9, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x31\x31\x81\x31\x31", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x7b\x22\x31\x81\x22\x3a\x31\x7d", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\"0\x01\x02\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"", -1, -1, json_tokener_success, 1, 0}, {"\"\x01\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x02\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x03\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x04\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x05\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x06\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x07\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x08\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x09\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x10\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x11\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x12\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x13\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x14\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x15\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x16\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x17\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x18\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x19\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {0, -1, -1, json_tokener_success, 0, 0}};
static void test_incremental_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error jerr;
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  const char *string_to_parse;
  unsigned int string_to_parse_idx = 0;
  int ii;
  int num_ok;
  int num_error;
  num_ok = 0;
  num_error = 0;
  printf("Starting incremental tests.\n");
  printf("Note: quotes and backslashes seen in the output here are literal values passed\n");
  printf("     to the parse functions.  e.g. this is 4 characters: \"\\f\"\n");
  string_to_parse_idx = "{ \"foo";
  printf("json_tokener_parse(%s) ... ", string_to_parse);
  new_obj_idx = json_tokener_parse(string_to_parse);
  if ((&new_obj[new_obj_idx]) == 0)
  {
    printf("%s", "got error as expected\n");
  }
  tok_idx = json_tokener_new();
  for (ii = 0; incremental_steps[ii].string_to_parse != 0; ii += 1)
  {
    helper_test_incremental_parse_1(&new_obj_idx, &jerr, &num_ok, &num_error, new_obj, tok, ii);
  }

  json_tokener_free(tok);
  printf("End Incremental Tests OK=%d ERROR=%d\n", num_ok, num_error);
}


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

typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg);
extern int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg);
static void test_basic_parse(void);
static void test_utf8_parse(void);
static void test_verbose_parse(void);
static void test_incremental_parse(void);
int main(void)
{
  if (0)
  {
    mc_set_debug(1);
  }
  static const char separator[] = "==================================";
  test_basic_parse();
  puts(separator);
  test_utf8_parse();
  puts(separator);
  test_verbose_parse();
  puts(separator);
  test_incremental_parse();
  puts(separator);
  return 0;
}

static json_c_visit_userfunc clear_serializer;
static void do_clear_serializer(json_object *jso);
static void single_incremental_parse(const char *test_string, int clear_serializer)
{
  size_t ii;
  int chunksize = atoi(getenv("TEST_PARSE_CHUNKSIZE"));
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  enum json_tokener_error jerr;
  json_object *all_at_once_obj;
  unsigned int all_at_once_obj_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  const char *all_at_once_str;
  unsigned int all_at_once_str_idx = 0;
  const char *new_str;
  unsigned int new_str_idx = 0;
  new_obj_idx = 0;
  assert(chunksize > 0);
  all_at_once_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(all_at_once_obj);
  }
  all_at_once_str_idx = json_object_to_json_string(all_at_once_obj);
  tok_idx = json_tokener_new();
  size_t test_string_len = strlen(test_string) + 1;
  for (ii = 0; ii < test_string_len; ii += chunksize)
  {
    int len_to_parse = chunksize;
    if ((ii + chunksize) > test_string_len)
    {
      len_to_parse = test_string_len - ii;
    }
    if (getenv("TEST_PARSE_DEBUG") != 0)
    {
      printf(" chunk: %.*s\n", len_to_parse, &test_string[ii]);
    }
    new_obj_idx = json_tokener_parse_ex(tok, &test_string[ii], len_to_parse);
    jerr = json_tokener_get_error(tok);
    if ((jerr != json_tokener_continue) || (&new_obj[new_obj_idx]))
    {
      break;
    }
  }

  if (clear_serializer && (&new_obj[new_obj_idx]))
  {
    do_clear_serializer(new_obj);
  }
  new_str_idx = json_object_to_json_string(new_obj);
  if (strcmp(all_at_once_str, new_str) != 0)
  {
    printf("ERROR: failed to parse (%s) in %d byte chunks: %s != %s\n", test_string, chunksize, all_at_once_str, new_str);
  }
  json_tokener_free(tok);
  if (all_at_once_obj)
  {
    json_object_put(all_at_once_obj);
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
}

static void single_basic_parse(const char *test_string, int clear_serializer)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(new_obj);
  }
  printf("new_obj.to_string(%s)=%s\n", test_string, json_object_to_json_string(new_obj));
  json_object_put(new_obj);
  if (getenv("TEST_PARSE_CHUNKSIZE") != 0)
  {
    single_incremental_parse(test_string, clear_serializer);
  }
}

static void test_basic_parse(void)
{
  single_basic_parse("\"\003\"", 0);
  single_basic_parse("/* hello */\"foo\"", 0);
  single_basic_parse("// hello\n\"foo\"", 0);
  single_basic_parse("\"foo\"blue", 0);
  single_basic_parse("\'foo\'", 0);
  single_basic_parse("\"\\u0041\\u0042\\u0043\"", 0);
  single_basic_parse("\"\\u4e16\\u754c\\u00df\"", 0);
  single_basic_parse("\"\\u4E16\"", 0);
  single_basic_parse("\"\\u4e1\"", 0);
  single_basic_parse("\"\\u4e1@\"", 0);
  single_basic_parse("\"\\ud840\\u4e16\"", 0);
  single_basic_parse("\"\\ud840\"", 0);
  single_basic_parse("\"\\udd27\"", 0);
  single_basic_parse("[9,'\\uDAD", 0);
  single_basic_parse("null", 0);
  single_basic_parse("NaN", 0);
  single_basic_parse("-NaN", 0);
  single_basic_parse("Inf", 0);
  single_basic_parse("inf", 0);
  single_basic_parse("Infinity", 0);
  single_basic_parse("infinity", 0);
  single_basic_parse("-Infinity", 0);
  single_basic_parse("-infinity", 0);
  single_basic_parse("{ \"min\": Infinity, \"max\": -Infinity}", 0);
  single_basic_parse("Infinity!", 0);
  single_basic_parse("Infinitynull", 0);
  single_basic_parse("InfinityXXXX", 0);
  single_basic_parse("-Infinitynull", 0);
  single_basic_parse("-InfinityXXXX", 0);
  single_basic_parse("Infinoodle", 0);
  single_basic_parse("InfinAAA", 0);
  single_basic_parse("-Infinoodle", 0);
  single_basic_parse("-InfinAAA", 0);
  single_basic_parse("True", 0);
  single_basic_parse("False", 0);
  single_basic_parse("tRue", 0);
  single_basic_parse("fAlse", 0);
  single_basic_parse("nAn", 0);
  single_basic_parse("iNfinity", 0);
  single_basic_parse("12", 0);
  single_basic_parse("12.3", 0);
  single_basic_parse("12.3.4", 0);
  single_basic_parse("2015-01-15", 0);
  single_basic_parse("12.3xxx", 0);
  single_basic_parse("12.3{\"a\":123}", 0);
  single_basic_parse("12.3\n", 0);
  single_basic_parse("12.3 ", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3e512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E51.2}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512E12}", 0);
  single_basic_parse("[\"\\n\"]", 0);
  single_basic_parse("[\"\\nabc\\n\"]", 0);
  single_basic_parse("[null]", 0);
  single_basic_parse("[]", 0);
  single_basic_parse("[false]", 0);
  single_basic_parse("[\"abc\",null,\"def\",12]", 0);
  single_basic_parse("{}", 0);
  single_basic_parse("{ \"foo\": \"bar\" }", 0);
  single_basic_parse("{ \'foo\': \'bar\' }", 0);
  single_basic_parse("{ \"foo\": \"bar\", \"baz\": null, \"bool0\": true }", 0);
  single_basic_parse("{ \"foo\": [null, \"foo\"] }", 0);
  single_basic_parse("{ \"abc\": 12, \"foo\": \"bar\", \"bool0\": false, \"bool1\": true, \"arr\": [ 1, 2, 3, null, 5 ] }", 0);
  single_basic_parse("{ \"abc\": \"blue\nred\\ngreen\" }", 0);
  single_basic_parse("null", 1);
  single_basic_parse("false", 1);
  single_basic_parse("[0e]", 1);
  single_basic_parse("[0e+]", 1);
  single_basic_parse("[0e+-1]", 1);
  single_basic_parse("\"hello world!\"", 1);
  single_basic_parse("[9223372036854775806]", 1);
  single_basic_parse("[9223372036854775807]", 1);
  single_basic_parse("[9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775807]", 1);
  single_basic_parse("[-9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775809]", 1);
  single_basic_parse("[18446744073709551614]", 1);
  single_basic_parse("[18446744073709551615]", 1);
  single_basic_parse("[18446744073709551616]", 1);
}

static void test_utf8_parse(void)
{
  const char *utf8_bom = "\xEF\xBB\xBF";
  const char *utf8_bom_and_chars = "\xEF\xBB\xBF{}";
  single_basic_parse(utf8_bom, 0);
  single_basic_parse(utf8_bom_and_chars, 0);
}

static void do_clear_serializer(json_object *jso)
{
  json_c_visit(jso, 0, clear_serializer, 0);
}

static int clear_serializer(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  if (jso)
  {
    json_object_set_serializer(jso, 0, 0, 0);
  }
  return 0;
}

static void test_verbose_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error error = json_tokener_success;
  new_obj_idx = json_tokener_parse_verbose("{ foo }", &error);
  assert(error == json_tokener_error_parse_object_key_name);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("{ foo }");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("foo");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_verbose("foo", &error);
  assert((&new_obj[new_obj_idx]) == 0);
  assert(error == json_tokener_error_parse_boolean);
  puts("json_tokener_parse_verbose() OK");
}

struct incremental_step
{
  const char *string_to_parse;
  int length;
  int char_offset;
  enum json_tokener_error expected_error;
  int reset_tokener;
  int tok_flags;
} incremental_steps[] = {{"{ \"foo\": 123 }", -1, -1, json_tokener_success, 0, 0}, {"{ \"foo\": 456 }", -1, -1, json_tokener_success, 1, 0}, {"{ \"foo\": 789 }", -1, -1, json_tokener_success, 1, 0}, {"/* hello */{ \"foo\"", -1, -1, json_tokener_continue, 0, 0}, {"/* hello */:/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"\"bar\"/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"}/* hello */", -1, -1, json_tokener_success, 1, 0}, {"/ hello ", -1, 1, json_tokener_error_parse_comment, 1, 0}, {"/* hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"/* hello*\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"// hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}", -1, -1, json_tokener_success, 1, 0}, {"\"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"8", -1, -1, json_tokener_continue, 0, 0}, {"3", -1, -1, json_tokener_continue, 0, 0}, {"4", -1, -1, json_tokener_continue, 0, 0}, {"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"1", -1, -1, json_tokener_continue, 0, 0}, {"e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\u", -1, -1, json_tokener_continue, 0, 0}, {"d8", -1, -1, json_tokener_continue, 0, 0}, {"34", -1, -1, json_tokener_continue, 0, 0}, {"\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd", -1, -1, json_tokener_continue, 0, 0}, {"1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834", -1, -1, json_tokener_continue, 0, 0}, {"\\udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\", -1, -1, json_tokener_continue, 0, 0}, {"udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\ud", -1, -1, json_tokener_continue, 0, 0}, {"d1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\udd", -1, -1, json_tokener_continue, 0, 0}, {"1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud83d\\ude", -1, -1, json_tokener_continue, 0, 0}, {"00 bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0x01}, {"{ \"foo", -1, -1, json_tokener_continue, 1, 0}, {": \"bar\"}", -1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}XXXX", 10, 6, json_tokener_success, 0, 0}, {"XXXX", 4, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"x\": 123 }\"X\"", -1, 11, json_tokener_success, 0, 0}, {"\"Y\"", -1, -1, json_tokener_success, 1, 0}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_error_parse_unexpected, 1, 0x01}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_success, 0, 0x01 | 0x02}, {"{\"b\":8}ignored garbage", -1, 7, json_tokener_success, 1, 0x01 | 0x02}, {"1", 1, 1, json_tokener_continue, 0, 0}, {"2", 2, 1, json_tokener_success, 0, 0}, {"12{", 3, 2, json_tokener_success, 1, 0}, {"[02]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+0", 5, 4, json_tokener_success, 1, 0}, {"[0e+0]", -1, -1, json_tokener_success, 1, 0}, {"0e", 2, 2, json_tokener_continue, 1, 0}, {"0e", 3, 2, json_tokener_success, 1, 0}, {"0e", 3, 2, json_tokener_error_parse_eof, 1, 0x01}, {"[0e]", -1, -1, json_tokener_success, 1, 0}, {"[0e]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+", 3, 3, json_tokener_continue, 1, 0}, {"0e+", 4, 3, json_tokener_success, 1, 0}, {"0e+", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e+]", -1, -1, json_tokener_success, 1, 0}, {"[0e+]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e-", 3, 3, json_tokener_continue, 1, 0}, {"0e-", 4, 3, json_tokener_success, 1, 0}, {"0e-", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e-]", -1, -1, json_tokener_success, 1, 0}, {"[0e-]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e+-", 5, 3, json_tokener_success, 1, 0}, {"0e+-", 5, 3, json_tokener_error_parse_number, 1, 0x01}, {"[0e+-]", -1, 4, json_tokener_error_parse_number, 1, 0}, {"false", 5, 5, json_tokener_continue, 1, 0}, {"false", 6, 5, json_tokener_success, 1, 0}, {"true", 4, 4, json_tokener_continue, 1, 0}, {"true", 5, 4, json_tokener_success, 1, 0}, {"null", 4, 4, json_tokener_continue, 1, 0}, {"null", 5, 4, json_tokener_success, 1, 0}, {"Infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"-infinity", 10, 9, json_tokener_success, 1, 0}, {"-infinity", 10, 1, json_tokener_error_parse_unexpected, 1, 0x01}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"-inf", 4, 4, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"f", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"t", 1, 1, json_tokener_continue, 0, 0}, {"y", 1, 1, json_tokener_continue, 0, 0}, {"", 1, 0, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"ini", 3, 3, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"nfini", 5, 5, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-i", 2, 2, json_tokener_continue, 0, 0}, {"nfinity", 8, 7, json_tokener_success, 1, 0}, {"InfinityX", 10, 8, json_tokener_success, 0, 0}, {"X", 1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"Infinity1234", 13, 8, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"Infinity9999", 8, 8, json_tokener_continue, 0, 0}, {"1234", 5, 0, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"[9223372036854775807]", 22, 21, json_tokener_success, 1, 0}, {"[9223372036854775808]", 22, 21, json_tokener_success, 1, 0}, {"[-9223372036854775808]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"[18446744073709551615]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"18446744073709551616", 21, 20, json_tokener_success, 1, 0}, {"18446744073709551616", 21, 20, json_tokener_error_parse_eof, 1, 0x01}, {"[9223372036854775808.0]", 24, 23, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0x01}, {"[18446744073709551615.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0x01}, {"noodle", 7, 1, json_tokener_error_parse_null, 1, 0}, {"naodle", 7, 2, json_tokener_error_parse_null, 1, 0}, {"track", 6, 2, json_tokener_error_parse_boolean, 1, 0}, {"fail", 5, 2, json_tokener_error_parse_boolean, 1, 0}, {"null123", 8, 4, json_tokener_success, 0, 0}, {&"null123"[4], 4, 3, json_tokener_success, 1, 0}, {"nullx", 6, 4, json_tokener_success, 0, 0}, {&"nullx"[4], 2, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1}{\"b\":2}", 15, 7, json_tokener_success, 0, 0}, {&"{\"a\":1}{\"b\":2}"[7], 8, 7, json_tokener_success, 1, 0}, {&"2015-01-15"[0], 11, 4, json_tokener_success, 1, 0}, {&"2015-01-15"[4], 7, 3, json_tokener_success, 1, 0}, {&"2015-01-15"[7], 4, 3, json_tokener_success, 1, 0}, {&"2015 01 15"[0], 11, 5, json_tokener_success, 1, 0}, {&"2015 01 15"[4], 7, 4, json_tokener_success, 1, 0}, {&"2015 01 15"[7], 4, 3, json_tokener_success, 1, 0}, {"\"blue\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\"\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\\\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\b\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\f\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\n\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\r\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\t\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\/\"", -1, -1, json_tokener_success, 0, 0}, {"\"/\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\a\"", -1, 2, json_tokener_error_parse_string, 1, 0}, {"\'foo\'", -1, 5, json_tokener_success, 1, 0}, {"\'foo\'", -1, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,3]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3}", -1, 6, json_tokener_error_parse_array, 1, 0}, {"{\"a\"}", -1, 4, json_tokener_error_parse_object_key_sep, 1, 0}, {"{\"a\":1]", -1, 6, json_tokener_error_parse_object_value_sep, 1, 0}, {"{\"a\"::1}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1,\"a\":2}", -1, -1, json_tokener_success, 1, 0}, {"\"a\":1}", -1, 3, json_tokener_success, 1, 0}, {"{\"a\":1", -1, -1, json_tokener_continue, 1, 0}, {"[,]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[,1]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[1,2,3,]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3,]", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0x01}, {"{\"a\":1,}", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe4\xb8", -1, 3, json_tokener_error_parse_utf8_string, 0, 0x10}, {"\x96\xe7\x95\x8c\x22", -1, 0, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xcf\x80\xcf\x86\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xf0\xa5\x91\x95\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 5, json_tokener_success, 1, 0}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 6, json_tokener_success, 1, 0}, {"\x20\x20\x22\xe4\xb8\x96\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x20\x20\x81\x22\xe4\xb8\x96\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x5b\x20\x81\x31\x5d", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x49\x6e\x66\x69\x6e\x69\x74\x79", 9, 8, json_tokener_success, 1, 0}, {"\x49\x6e\x66\x81\x6e\x69\x74\x79", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\x5c\x75\x64\x63\x35\x35\x22", 15, 14, json_tokener_success, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\xc0\x75\x64\x63\x35\x35\x22", -1, 8, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x30\x30\x33\x31\xc0\x22", -1, 9, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x31\x31\x81\x31\x31", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x7b\x22\x31\x81\x22\x3a\x31\x7d", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\"0\x01\x02\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"", -1, -1, json_tokener_success, 1, 0}, {"\"\x01\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x02\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x03\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x04\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x05\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x06\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x07\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x08\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x09\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x10\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x11\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x12\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x13\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x14\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x15\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x16\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x17\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x18\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x19\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {0, -1, -1, json_tokener_success, 0, 0}};
static void test_incremental_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error jerr;
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  const char *string_to_parse;
  unsigned int string_to_parse_idx = 0;
  int ii;
  int num_ok;
  int num_error;
  num_ok = 0;
  num_error = 0;
  printf("Starting incremental tests.\n");
  printf("Note: quotes and backslashes seen in the output here are literal values passed\n");
  printf("     to the parse functions.  e.g. this is 4 characters: \"\\f\"\n");
  string_to_parse_idx = "{ \"foo";
  printf("json_tokener_parse(%s) ... ", string_to_parse);
  new_obj_idx = json_tokener_parse(string_to_parse);
  if ((&new_obj[new_obj_idx]) == 0)
  {
    printf("%s", "got error as expected\n");
  }
  tok_idx = json_tokener_new();
  for (ii = 0; incremental_steps[ii].string_to_parse != 0; ii += 1)
  {
    int this_step_ok = 0;
    struct incremental_step *step = &incremental_steps[ii];
    int length = step->length;
    size_t expected_char_offset;
    json_tokener_set_flags(tok, step->tok_flags);
    if (length == (-1))
    {
      length = (int) strlen(step->string_to_parse);
    }
    if (step->char_offset == (-1))
    {
      expected_char_offset = length;
    }
    else
      expected_char_offset = step->char_offset;
    printf("json_tokener_parse_ex(tok, %-12s, %3d) ... ", step->string_to_parse, length);
    new_obj_idx = json_tokener_parse_ex(tok, step->string_to_parse, length);
    jerr = json_tokener_get_error(tok);
    if (step->expected_error != json_tokener_success)
    {
      if ((&new_obj[new_obj_idx]) != 0)
      {
        printf("ERROR: invalid object returned: %s\n", json_object_to_json_string(new_obj));
      }
      else
        if (jerr != step->expected_error)
      {
        printf("ERROR: got wrong error: %s\n", json_tokener_error_desc(jerr));
      }
      else
        if (json_tokener_get_parse_end(tok) != expected_char_offset)
      {
        printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
      }
      else
      {
        printf("OK: got correct error: %s\n", json_tokener_error_desc(jerr));
        this_step_ok = 1;
      }
    }
    else
    {
      if (((&new_obj[new_obj_idx]) == 0) && (!((step->length >= 4) && (strncmp(step->string_to_parse, "null", 4) == 0))))
      {
        printf("ERROR: expected valid object, instead: %s\n", json_tokener_error_desc(jerr));
      }
      else
        if (json_tokener_get_parse_end(tok) != expected_char_offset)
      {
        printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
      }
      else
      {
        printf("OK: got object of type [%s]: %s\n", json_type_to_name(json_object_get_type(new_obj)), json_object_to_json_string(new_obj));
        this_step_ok = 1;
      }
    }
    if (new_obj)
    {
      json_object_put(new_obj);
    }
    if (step->reset_tokener & 1)
    {
      json_tokener_reset(tok);
    }
    if (this_step_ok)
    {
      num_ok += 1;
    }
    else
      num_error++;
    num_error += 1;
  }

  json_tokener_free(tok);
  printf("End Incremental Tests OK=%d ERROR=%d\n", num_ok, num_error);
}

void helper_test_incremental_parse_1(unsigned int * const new_obj_idx_ref, enum json_tokener_error * const jerr_ref, int * const num_ok_ref, int * const num_error_ref, json_object * const new_obj, struct json_tokener * const tok, int ii)
{
  unsigned int new_obj_idx = *new_obj_idx_ref;
  enum json_tokener_error jerr = *jerr_ref;
  int num_ok = *num_ok_ref;
  int num_error = *num_error_ref;
  int this_step_ok = 0;
  struct incremental_step *step = &incremental_steps[ii];
  int length = step->length;
  size_t expected_char_offset;
  json_tokener_set_flags(tok, step->tok_flags);
  if (length == (-1))
  {
    length = (int) strlen(step->string_to_parse);
  }
  if (step->char_offset == (-1))
  {
    expected_char_offset = length;
  }
  else
    expected_char_offset = step->char_offset;
  printf("json_tokener_parse_ex(tok, %-12s, %3d) ... ", step->string_to_parse, length);
  new_obj_idx = json_tokener_parse_ex(tok, step->string_to_parse, length);
  jerr = json_tokener_get_error(tok);
  if (step->expected_error != json_tokener_success)
  {
    if ((&new_obj[new_obj_idx]) != 0)
    {
      printf("ERROR: invalid object returned: %s\n", json_object_to_json_string(new_obj));
    }
    else
      if (jerr != step->expected_error)
    {
      printf("ERROR: got wrong error: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got correct error: %s\n", json_tokener_error_desc(jerr));
      this_step_ok = 1;
    }
  }
  else
  {
    if (((&new_obj[new_obj_idx]) == 0) && (!((step->length >= 4) && (strncmp(step->string_to_parse, "null", 4) == 0))))
    {
      printf("ERROR: expected valid object, instead: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got object of type [%s]: %s\n", json_type_to_name(json_object_get_type(new_obj)), json_object_to_json_string(new_obj));
      this_step_ok = 1;
    }
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
  if (step->reset_tokener & 1)
  {
    json_tokener_reset(tok);
  }
  if (this_step_ok)
  {
    num_ok += 1;
  }
  else
    num_error++;
  num_error += 1;
  *new_obj_idx_ref = new_obj_idx;
  *jerr_ref = jerr;
  *num_ok_ref = num_ok;
  *num_error_ref = num_error;
}

