#include <arraylist.h>
#include <assert.h>
#include <config.h>
#include <debug.h>
#include <errno.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.c>
#include <json_object.h>
#include <json_object_private.h>
#include <json_types.h>
#include <json_util.h>
#include <limits.h>
#include <linkhash.h>
#include <math.h>
#include <math_compat.h>
#include <printbuf.h>
#include <snprintf_compat.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strdup_compat.h>
#include <strerror_override.h>
#include <string.h>
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

const char *json_number_chars = "0123456789.+-eE";
const char *json_hex_chars = "0123456789abcdefABCDEF";
static void json_object_generic_delete(struct json_object *jso);
inline static struct json_object_object *JC_OBJECT(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_object *JC_OBJECT_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_array *JC_ARRAY(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_array *JC_ARRAY_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_boolean *JC_BOOL(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_boolean *JC_BOOL_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_double *JC_DOUBLE(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_double *JC_DOUBLE_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_int *JC_INT(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_int *JC_INT_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_string *JC_STRING(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_string *JC_STRING_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object *json_object_new(enum json_type o_type, size_t alloc_size, json_object_to_json_string_fn *to_json_string);
static void json_object_object_delete(struct json_object *jso_base);
static void json_object_string_delete(struct json_object *jso);
static void json_object_array_delete(struct json_object *jso);
static json_object_to_json_string_fn json_object_object_to_json_string;
static json_object_to_json_string_fn json_object_boolean_to_json_string;
static json_object_to_json_string_fn json_object_double_to_json_string_default;
static json_object_to_json_string_fn json_object_int_to_json_string;
static json_object_to_json_string_fn json_object_string_to_json_string;
static json_object_to_json_string_fn json_object_array_to_json_string;
static json_object_to_json_string_fn _json_object_userdata_to_json_string;
static void json_abort(const char *message);
inline static char *get_string_component_mutable(struct json_object *jso)
{
  if (JC_STRING_C(jso)->len < 0)
  {
    return JC_STRING(jso)->c_string.pdata;
  }
  return JC_STRING(jso)->c_string.idata;
}

inline static const char *get_string_component(const struct json_object *jso)
{
  return get_string_component_mutable((void *) ((uintptr_t) ((const void *) jso)));
}

static int json_escape_str(struct printbuf *pb, const char *str, size_t len, int flags)
{
  size_t pos = 0;
  size_t start_offset = 0;
  unsigned char c;
  while (len)
  {
    len -= 1;
    c = str[pos];
    switch (c)
    {
      case '\b':

      case '\n':

      case '\r':

      case '\t':

      case '\f':

      case '"':

      case '\\':

      case '/':
        if ((flags & (1 << 4)) && (c == '/'))
      {
        pos += 1;
        break;
      }
        if (pos > start_offset)
      {
        printbuf_memappend(pb, str + start_offset, pos - start_offset);
      }
        if (c == '\b')
      {
        printbuf_memappend(pb, "\\b", 2);
      }
      else
        if (c == '\n')
      {
        printbuf_memappend(pb, "\\n", 2);
      }
      else
        if (c == '\r')
      {
        printbuf_memappend(pb, "\\r", 2);
      }
      else
        if (c == '\t')
      {
        printbuf_memappend(pb, "\\t", 2);
      }
      else
        if (c == '\f')
      {
        printbuf_memappend(pb, "\\f", 2);
      }
      else
        if (c == '"')
      {
        printbuf_memappend(pb, "\\\"", 2);
      }
      else
        if (c == '\\')
      {
        printbuf_memappend(pb, "\\\\", 2);
      }
      else
        if (c == '/')
      {
        printbuf_memappend(pb, "\\/", 2);
      }
        pos += 1;
        start_offset = pos;
        break;

      default:
        if (c < ' ')
      {
        char sbuf[7];
        if (pos > start_offset)
        {
          printbuf_memappend(pb, str + start_offset, pos - start_offset);
        }
        snprintf(sbuf, sizeof(sbuf), "\\u00%c%c", json_hex_chars[c >> 4], json_hex_chars[c & 0xf]);
        do
        {
          if ((pb->size - pb->bpos) > (((int) (sizeof(sbuf))) - 1))
          {
            memcpy(pb->buf + pb->bpos, sbuf, ((int) (sizeof(sbuf))) - 1);
            pb->bpos += ((int) (sizeof(sbuf))) - 1;
            pb->buf[pb->bpos] = '\0';
          }
          else
          {
            printbuf_memappend(pb, sbuf, ((int) (sizeof(sbuf))) - 1);
          }
        }
        while (0);
        pos += 1;
        start_offset = pos;
      }
      else
        pos++;
        pos += 1;

    }

  }

  if (pos > start_offset)
  {
    printbuf_memappend(pb, str + start_offset, pos - start_offset);
  }
  return 0;
}

struct json_object *json_object_get(struct json_object *jso)
{
  if (!jso)
  {
    return jso;
  }
  assert(jso->_ref_count < UINT32_MAX);
  jso->_ref_count += 1;
  return jso;
}

int json_object_put(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  assert(jso->_ref_count > 0);
  if ((--jso->_ref_count) > 0)
  {
    return 0;
  }
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  switch (jso->o_type)
  {
    case json_type_object:
      json_object_object_delete(jso);
      break;

    case json_type_array:
      json_object_array_delete(jso);
      break;

    case json_type_string:
      json_object_string_delete(jso);
      break;

    default:
      json_object_generic_delete(jso);
      break;

  }

  return 1;
}

static void json_object_generic_delete(struct json_object *jso)
{
  printbuf_free(jso->_pb);
  free(jso);
}

inline static struct json_object *json_object_new(enum json_type o_type, size_t alloc_size, json_object_to_json_string_fn *to_json_string)
{
  struct json_object *jso;
  unsigned int jso_idx = 0;
  jso_idx = (struct json_object *) malloc(alloc_size);
  if (!(&jso[jso_idx]))
  {
    return 0;
  }
  jso->o_type = o_type;
  jso->_ref_count = 1;
  jso->_to_json_string = to_json_string;
  jso->_pb = 0;
  jso->_user_delete = 0;
  jso->_userdata = 0;
  return jso;
}

int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
}

enum json_type json_object_get_type(const struct json_object *jso)
{
  if (!jso)
  {
    return json_type_null;
  }
  return jso->o_type;
}

void *json_object_get_userdata(json_object *jso)
{
  return (jso) ? (jso->_userdata) : (0);
}

void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete)
{
  assert(jso != 0);
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  jso->_userdata = userdata;
  jso->_user_delete = user_delete;
}

void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete)
{
  json_object_set_userdata(jso, userdata, user_delete);
  if (to_string_func == 0)
  {
    switch (jso->o_type)
    {
      case json_type_null:
        jso->_to_json_string = 0;
        break;

      case json_type_boolean:
        jso->_to_json_string = &json_object_boolean_to_json_string;
        break;

      case json_type_double:
        jso->_to_json_string = &json_object_double_to_json_string_default;
        break;

      case json_type_int:
        jso->_to_json_string = &json_object_int_to_json_string;
        break;

      case json_type_object:
        jso->_to_json_string = &json_object_object_to_json_string;
        break;

      case json_type_array:
        jso->_to_json_string = &json_object_array_to_json_string;
        break;

      case json_type_string:
        jso->_to_json_string = &json_object_string_to_json_string;
        break;

    }

    return;
  }
  jso->_to_json_string = to_string_func;
}

const char *json_object_to_json_string_length(struct json_object *jso, int flags, size_t *length)
{
  const char *r = 0;
  unsigned int r_idx = 0;
  size_t s = 0;
  if (!jso)
  {
    s = 4;
    r_idx = "null";
  }
  else
    if (jso->_pb || (jso->_pb = printbuf_new()))
  {
    printbuf_reset(jso->_pb);
    if (jso->_to_json_string(jso, jso->_pb, 0, flags) >= 0)
    {
      s = (size_t) jso->_pb->bpos;
      r_idx = jso->_pb->buf;
    }
  }
  if (length)
  {
    *length = s;
  }
  return r;
}

const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}

const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}

static void indent(struct printbuf *pb, int level, int flags)
{
  if (flags & (1 << 1))
  {
    if (flags & (1 << 3))
    {
      printbuf_memset(pb, -1, '\t', level);
    }
    else
    {
      printbuf_memset(pb, -1, ' ', level * 2);
    }
  }
}

static int json_object_object_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int had_children = 0;
  struct json_object_iter iter;
  printbuf_memappend(pb, "{", (sizeof("{")) - 1);
  for (iter.entry = lh_table_head(json_object_get_object(jso)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (had_children)
    {
      printbuf_memappend(pb, ",", (sizeof(",")) - 1);
    }
    if (flags & (1 << 1))
    {
      printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    }
    had_children = 1;
    if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
    {
      printbuf_memappend(pb, " ", (sizeof(" ")) - 1);
    }
    indent(pb, level + 1, flags);
    if (flags & (1 << 5))
    {
      printbuf_memappend(pb, "\033[0;34m", (sizeof("\033[0;34m")) - 1);
    }
    printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
    json_escape_str(pb, iter.key, strlen(iter.key), flags);
    printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
    if (flags & (1 << 5))
    {
      printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
    }
    if (flags & (1 << 0))
    {
      printbuf_memappend(pb, ": ", (sizeof(": ")) - 1);
    }
    else
      printbuf_memappend(pb, ":", (sizeof(":")) - 1);
    if (iter.val == 0)
    {
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
      }
      printbuf_memappend(pb, "null", (sizeof("null")) - 1);
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
      }
    }
    else
      if (iter.val->_to_json_string(iter.val, pb, level + 1, flags) < 0)
    {
      return -1;
    }
  }

  if ((flags & (1 << 1)) && had_children)
  {
    printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    indent(pb, level, flags);
  }
  if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
  {
    return printbuf_memappend(pb, " }", (sizeof(" }")) - 1);
  }
  else
    return printbuf_memappend(pb, "}", (sizeof("}")) - 1);
}

static void json_object_lh_entry_free(struct lh_entry *ent)
{
  if (!lh_entry_k_is_constant(ent))
  {
    free(lh_entry_k(ent));
  }
  json_object_put((struct json_object *) lh_entry_v(ent));
}

static void json_object_object_delete(struct json_object *jso_base)
{
  lh_table_free(JC_OBJECT(jso_base)->c_object);
  json_object_generic_delete(jso_base);
}

struct json_object *json_object_new_object(void)
{
  struct json_object_object *jso = (struct json_object_object *) json_object_new(json_type_object, sizeof(struct json_object_object), &json_object_object_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_object = lh_kchar_table_new(16, &json_object_lh_entry_free);
  if (!jso->c_object)
  {
    json_object_generic_delete(&jso->base);
    errno = ENOMEM;
    return 0;
  }
  return &jso->base;
}

struct lh_table *json_object_get_object(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
      return JC_OBJECT_C(jso)->c_object;

    default:
      return 0;

  }

}

int json_object_object_add_ex(struct json_object *jso, const char * const key, struct json_object * const val, const unsigned opts)
{
  struct json_object *existing_value = 0;
  unsigned int existing_value_idx = 0;
  struct lh_entry *existing_entry;
  unsigned int existing_entry_idx = 0;
  unsigned long hash;
  assert(json_object_get_type(jso) == json_type_object);
  hash = lh_get_hash(JC_OBJECT(jso)->c_object, (const void *) key);
  existing_entry_idx = (opts & (1 << 1)) ? (0) : (lh_table_lookup_entry_w_hash(JC_OBJECT(jso)->c_object, (const void *) key, hash));
  if (jso == val)
  {
    return -1;
  }
  if (!(&existing_entry[existing_entry_idx]))
  {
    const void * const k = (opts & (1 << 2)) ? ((const void *) key) : (strdup(key));
    if (k == 0)
    {
      return -1;
    }
    return lh_table_insert_w_hash(JC_OBJECT(jso)->c_object, k, val, hash, opts);
  }
  existing_value_idx = (json_object *) lh_entry_v(existing_entry);
  if (existing_value)
  {
    json_object_put(existing_value);
  }
  lh_entry_set_val(existing_entry, val);
  return 0;
}

int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}

int json_object_object_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_object);
  return lh_table_length(JC_OBJECT_C(jso)->c_object);
}

size_t json_c_object_sizeof(void)
{
  return sizeof(struct json_object);
}

struct json_object *json_object_object_get(const struct json_object *jso, const char *key)
{
  struct json_object *result = 0;
  json_object_object_get_ex(jso, key, &result);
  return result;
}

json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);

    default:
      if (value != 0)
    {
      *value = 0;
    }
      return 0;

  }

}

void json_object_object_del(struct json_object *jso, const char *key)
{
  assert(json_object_get_type(jso) == json_type_object);
  lh_table_delete(JC_OBJECT(jso)->c_object, key);
}

static int json_object_boolean_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int ret;
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
  }
  if (JC_BOOL(jso)->c_boolean)
  {
    ret = printbuf_memappend(pb, "true", (sizeof("true")) - 1);
  }
  else
    ret = printbuf_memappend(pb, "false", (sizeof("false")) - 1);
  if ((ret > (-1)) && (flags & (1 << 5)))
  {
    return printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
  }
  return ret;
}

struct json_object *json_object_new_boolean(json_bool b)
{
  struct json_object_boolean *jso = (struct json_object_boolean *) json_object_new(json_type_boolean, sizeof(struct json_object_boolean), &json_object_boolean_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_boolean = b;
  return &jso->base;
}

json_bool json_object_get_boolean(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_int:
      switch (JC_INT_C(jso)->cint_type)
    {
      case json_object_int_type_int64:
        return JC_INT_C(jso)->cint.c_int64 != 0;

      case json_object_int_type_uint64:
        return JC_INT_C(jso)->cint.c_uint64 != 0;

      default:
        json_abort("invalid cint_type");

    }


    case json_type_double:
      return JC_DOUBLE_C(jso)->c_double != 0;

    case json_type_string:
      return JC_STRING_C(jso)->len != 0;

    default:
      return 0;

  }

}

int json_object_set_boolean(struct json_object *jso, json_bool new_value)
{
  if ((!jso) || (jso->o_type != json_type_boolean))
  {
    return 0;
  }
  JC_BOOL(jso)->c_boolean = new_value;
  return 1;
}

static int json_object_int_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  char sbuf[21];
  if (JC_INT(jso)->cint_type == json_object_int_type_int64)
  {
    snprintf(sbuf, sizeof(sbuf), "%d", JC_INT(jso)->cint.c_int64);
  }
  else
    snprintf(sbuf, sizeof(sbuf), "%u", JC_INT(jso)->cint.c_uint64);
  return printbuf_memappend(pb, sbuf, strlen(sbuf));
}

struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}

int32_t json_object_get_int(const struct json_object *jso)
{
  int64_t cint64 = 0;
  double cdouble;
  enum json_type o_type;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  o_type = jso->o_type;
  if (o_type == json_type_int)
  {
    const struct json_object_int *jsoint = JC_INT_C(jso);
    if (jsoint->cint_type == json_object_int_type_int64)
    {
      cint64 = jsoint->cint.c_int64;
    }
    else
    {
      if (jsoint->cint.c_uint64 >= INT64_MAX)
      {
        cint64 = INT64_MAX;
      }
      else
        cint64 = (int64_t) jsoint->cint.c_uint64;
    }
  }
  else
    if (o_type == json_type_string)
  {
    if (json_parse_int64(get_string_component(jso), &cint64) != 0)
    {
      return 0;
    }
    o_type = json_type_int;
  }
  switch (o_type)
  {
    case json_type_int:
      if (cint64 < INT32_MIN)
    {
      errno = ERANGE;
      return INT32_MIN;
    }
      if (cint64 > INT32_MAX)
    {
      errno = ERANGE;
      return INT32_MAX;
    }
      return (int32_t) cint64;

    case json_type_double:
      cdouble = JC_DOUBLE_C(jso)->c_double;
      if (cdouble < INT32_MIN)
    {
      errno = ERANGE;
      return INT32_MIN;
    }
      if (cdouble > INT32_MAX)
    {
      errno = ERANGE;
      return INT32_MAX;
    }
      if (isnan(cdouble))
    {
      errno = EINVAL;
      return INT32_MIN;
    }
      return (int32_t) cdouble;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    default:
      return 0;

  }

}

int json_object_set_int(struct json_object *jso, int new_value)
{
  return json_object_set_int64(jso, (int64_t) new_value);
}

struct json_object *json_object_new_int64(int64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_int64 = i;
  jso->cint_type = json_object_int_type_int64;
  return &jso->base;
}

struct json_object *json_object_new_uint64(uint64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_uint64 = i;
  jso->cint_type = json_object_int_type_uint64;
  return &jso->base;
}

int64_t json_object_get_int64(const struct json_object *jso)
{
  int64_t cint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
          return jsoint->cint.c_int64;

        case json_object_int_type_uint64:
          if (jsoint->cint.c_uint64 > INT64_MAX)
        {
          errno = ERANGE;
          return INT64_MAX;
        }
          return (int64_t) jsoint->cint.c_uint64;

        default:
          json_abort("invalid cint_type");

      }

    }

    case json_type_double:
      if (JC_DOUBLE_C(jso)->c_double > ((double) INT64_MAX))
    {
      errno = ERANGE;
      return INT64_MAX;
    }
      if (JC_DOUBLE_C(jso)->c_double < ((double) INT64_MIN))
    {
      errno = ERANGE;
      return INT64_MIN;
    }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
    {
      errno = EINVAL;
      return INT64_MIN;
    }
      return (int64_t) JC_DOUBLE_C(jso)->c_double;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      if (json_parse_int64(get_string_component(jso), &cint) == 0)
    {
      return cint;
    }

    default:
      return 0;

  }

}

uint64_t json_object_get_uint64(const struct json_object *jso)
{
  uint64_t cuint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
          if (jsoint->cint.c_int64 < 0)
        {
          errno = ERANGE;
          return 0;
        }
          return (uint64_t) jsoint->cint.c_int64;

        case json_object_int_type_uint64:
          return jsoint->cint.c_uint64;

        default:
          json_abort("invalid cint_type");

      }

    }

    case json_type_double:
      if (JC_DOUBLE_C(jso)->c_double > ((double) UINT64_MAX))
    {
      errno = ERANGE;
      return UINT64_MAX;
    }
      if (JC_DOUBLE_C(jso)->c_double < 0)
    {
      errno = ERANGE;
      return 0;
    }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
    {
      errno = EINVAL;
      return 0;
    }
      return (uint64_t) JC_DOUBLE_C(jso)->c_double;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      if (json_parse_uint64(get_string_component(jso), &cuint) == 0)
    {
      return cuint;
    }

    default:
      return 0;

  }

}

int json_object_set_int64(struct json_object *jso, int64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_int64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_int64;
  return 1;
}

int json_object_set_uint64(struct json_object *jso, uint64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_uint64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_uint64;
  return 1;
}

int json_object_int_inc(struct json_object *jso, int64_t val)
{
  struct json_object_int *jsoint;
  unsigned int jsoint_idx = 0;
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  jsoint_idx = JC_INT(jso);
  switch (jsoint->cint_type)
  {
    case json_object_int_type_int64:
      if ((val > 0) && (jsoint->cint.c_int64 > (INT64_MAX - val)))
    {
      jsoint->cint.c_uint64 = ((uint64_t) jsoint->cint.c_int64) + ((uint64_t) val);
      jsoint->cint_type = json_object_int_type_uint64;
    }
    else
      if ((val < 0) && (jsoint->cint.c_int64 < (INT64_MIN - val)))
    {
      jsoint->cint.c_int64 = INT64_MIN;
    }
    else
    {
      jsoint->cint.c_int64 += val;
    }
      return 1;

    case json_object_int_type_uint64:
      if ((val > 0) && (jsoint->cint.c_uint64 > (UINT64_MAX - ((uint64_t) val))))
    {
      jsoint->cint.c_uint64 = UINT64_MAX;
    }
    else
      if ((val < 0) && (jsoint->cint.c_uint64 < ((uint64_t) (-val))))
    {
      jsoint->cint.c_int64 = ((int64_t) jsoint->cint.c_uint64) + val;
      jsoint->cint_type = json_object_int_type_int64;
    }
    else
      if ((val < 0) && (jsoint->cint.c_uint64 >= ((uint64_t) (-val))))
    {
      jsoint->cint.c_uint64 -= (uint64_t) (-val);
    }
    else
    {
      jsoint->cint.c_uint64 += val;
    }
      return 1;

    default:
      json_abort("invalid cint_type");

  }

}

static char *tls_serialization_float_format = 0;
static char *global_serialization_float_format = 0;
int json_c_set_serialization_double_format(const char *double_format, int global_or_thread)
{
  if (global_or_thread == 0)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (global_serialization_float_format)
    {
      free(global_serialization_float_format);
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      global_serialization_float_format = p;
    }
    else
    {
      global_serialization_float_format = 0;
    }
  }
  else
    if (global_or_thread == 1)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      tls_serialization_float_format = p;
    }
    else
    {
      tls_serialization_float_format = 0;
    }
  }
  else
  {
    _json_c_set_last_err("json_c_set_serialization_double_format: invalid global_or_thread value: %d\n", global_or_thread);
    return -1;
  }
  return 0;
}

static int json_object_double_to_json_string_format(struct json_object *jso, struct printbuf *pb, int level, int flags, const char *format)
{
  unsigned int format_idx = 0;
  struct json_object_double *jsodbl = JC_DOUBLE(jso);
  char buf[128];
  char *p;
  unsigned int p_idx = 0;
  char *q;
  unsigned int q_idx = 0;
  int size;
  if (isnan(jsodbl->c_double))
  {
    size = snprintf(buf, sizeof(buf), "NaN");
  }
  else
    if (isinf(jsodbl->c_double))
  {
    if (jsodbl->c_double > 0)
    {
      size = snprintf(buf, sizeof(buf), "Infinity");
    }
    else
      size = snprintf(buf, sizeof(buf), "-Infinity");
  }
  else
  {
    const char *std_format = "%.17g";
    int format_drops_decimals = 0;
    int looks_numeric = 0;
    if (!(&format[format_idx]))
    {
      if (tls_serialization_float_format)
      {
        format_idx = tls_serialization_float_format;
      }
      else
        if (global_serialization_float_format)
      {
        format_idx = global_serialization_float_format;
      }
      else
        format_idx = std_format;
    }
    size = snprintf(buf, sizeof(buf), format, jsodbl->c_double);
    if (size < 0)
    {
      return -1;
    }
    p_idx = strchr(buf, ',');
    if (p)
    {
      p[p_idx] = '.';
    }
    else
      p_idx = strchr(buf, '.');
    if (((&format[format_idx]) == std_format) || (strstr(format, ".0f") == 0))
    {
      format_drops_decimals = 1;
    }
    looks_numeric = ((buf[0] >= '0') && (buf[0] <= '9')) || (((size > 1) && (buf[0] == '-')) && ((buf[1] >= '0') && (buf[1] <= '9')));
    if (((((size < (((int) (sizeof(buf))) - 2)) && looks_numeric) && (!(&p[p_idx]))) && (strchr(buf, 'e') == 0)) && format_drops_decimals)
    {
      strcat(buf, ".0");
      size += 2;
    }
    if ((&p[p_idx]) && (flags & (1 << 2)))
    {
      p_idx += 1;
      for (q_idx = &p[p_idx]; q[q_idx]; q_idx += 1)
      {
        if (q[q_idx] != '0')
        {
          p_idx = &q[q_idx];
        }
      }

      if (p[p_idx] != 0)
      {
        p_idx += 1;
        p[p_idx] = 0;
      }
      size = (&p[p_idx]) - buf;
    }
  }
  if (size < 0)
  {
    return -1;
  }
  if (size >= ((int) (sizeof(buf))))
  {
    size = (sizeof(buf)) - 1;
  }
  printbuf_memappend(pb, buf, size);
  return size;
}

static int json_object_double_to_json_string_default(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, 0);
}

int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, (const char *) jso->_userdata);
}

struct json_object *json_object_new_double(double d)
{
  struct json_object_double *jso = (struct json_object_double *) json_object_new(json_type_double, sizeof(struct json_object_double), &json_object_double_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->base._to_json_string = &json_object_double_to_json_string_default;
  jso->c_double = d;
  return &jso->base;
}

struct json_object *json_object_new_double_s(double d, const char *ds)
{
  char *new_ds;
  unsigned int new_ds_idx = 0;
  struct json_object *jso = json_object_new_double(d);
  if (!jso)
  {
    return 0;
  }
  new_ds_idx = strdup(ds);
  if (!(&new_ds[new_ds_idx]))
  {
    json_object_generic_delete(jso);
    errno = ENOMEM;
    return 0;
  }
  json_object_set_serializer(jso, _json_object_userdata_to_json_string, new_ds, json_object_free_userdata);
  return jso;
}

static int _json_object_userdata_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_userdata_to_json_string(jso, pb, level, flags);
}

int json_object_userdata_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int userdata_len = strlen((const char *) jso->_userdata);
  printbuf_memappend(pb, (const char *) jso->_userdata, userdata_len);
  return userdata_len;
}

void json_object_free_userdata(struct json_object *jso, void *userdata)
{
  free(userdata);
}

double json_object_get_double(const struct json_object *jso)
{
  double cdouble;
  char *errPtr = 0;
  if (!jso)
  {
    return 0.0;
  }
  switch (jso->o_type)
  {
    case json_type_double:
      return JC_DOUBLE_C(jso)->c_double;

    case json_type_int:
      switch (JC_INT_C(jso)->cint_type)
    {
      case json_object_int_type_int64:
        return JC_INT_C(jso)->cint.c_int64;

      case json_object_int_type_uint64:
        return JC_INT_C(jso)->cint.c_uint64;

      default:
        json_abort("invalid cint_type");

    }


    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      errno = 0;
      cdouble = strtod(get_string_component(jso), &errPtr);
      if (errPtr == get_string_component(jso))
    {
      errno = EINVAL;
      return 0.0;
    }
      if ((*errPtr) != '\0')
    {
      errno = EINVAL;
      return 0.0;
    }
      if (((HUGE_VAL == cdouble) || ((-HUGE_VAL) == cdouble)) && (ERANGE == errno))
    {
      cdouble = 0.0;
    }
      return cdouble;

    default:
      errno = EINVAL;
      return 0.0;

  }

}

int json_object_set_double(struct json_object *jso, double new_value)
{
  if ((!jso) || (jso->o_type != json_type_double))
  {
    return 0;
  }
  JC_DOUBLE(jso)->c_double = new_value;
  if (jso->_to_json_string == (&_json_object_userdata_to_json_string))
  {
    json_object_set_serializer(jso, 0, 0, 0);
  }
  return 1;
}

static int json_object_string_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  ssize_t len = JC_STRING(jso)->len;
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0;32m", (sizeof("\033[0;32m")) - 1);
  }
  printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
  json_escape_str(pb, get_string_component(jso), (len < 0) ? (-((ssize_t) len)) : (len), flags);
  printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
  }
  return 0;
}

static void json_object_string_delete(struct json_object *jso)
{
  if (JC_STRING(jso)->len < 0)
  {
    free(JC_STRING(jso)->c_string.pdata);
  }
  json_object_generic_delete(jso);
}

static struct json_object *_json_object_new_string(const char *s, const size_t len)
{
  size_t objsize;
  struct json_object_string *jso;
  unsigned int jso_idx = 0;
  if (len > ((9223372036854775807L - ((sizeof(*(&jso[jso_idx]))) - (sizeof(jso->c_string)))) - 1))
  {
    return 0;
  }
  objsize = (((sizeof(*(&jso[jso_idx]))) - (sizeof(jso->c_string))) + len) + 1;
  if (len < (sizeof(void *)))
  {
    objsize += (sizeof(void *)) - len;
  }
  jso_idx = (struct json_object_string *) json_object_new(json_type_string, objsize, &json_object_string_to_json_string);
  if (!(&jso[jso_idx]))
  {
    return 0;
  }
  jso->len = len;
  memcpy(jso->c_string.idata, s, len);
  ((char *) jso->c_string.idata)[len] = '\0';
  return &jso->base;
}

struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}

struct json_object *json_object_new_string_len(const char *s, const int len)
{
  return _json_object_new_string(s, len);
}

const char *json_object_get_string(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
      return get_string_component(jso);

    default:
      return json_object_to_json_string(jso);

  }

}

inline static ssize_t _json_object_get_string_len(const struct json_object_string *jso)
{
  ssize_t len;
  len = jso->len;
  return (len < 0) ? (-((ssize_t) len)) : (len);
}

int json_object_get_string_len(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
      return _json_object_get_string_len(JC_STRING_C(jso));

    default:
      return 0;

  }

}

static int _json_object_set_string_len(json_object *jso, const char *s, size_t len)
{
  char *dstbuf;
  unsigned int dstbuf_idx = 0;
  ssize_t curlen;
  ssize_t newlen;
  if ((jso == 0) || (jso->o_type != json_type_string))
  {
    return 0;
  }
  if (len >= (2147483647 - 1))
  {
    return 0;
  }
  curlen = JC_STRING(jso)->len;
  if (curlen < 0)
  {
    if (len == 0)
    {
      free(JC_STRING(jso)->c_string.pdata);
      JC_STRING(jso)->len = (curlen = 0);
    }
    else
    {
      curlen = -curlen;
    }
  }
  newlen = len;
  dstbuf_idx = get_string_component_mutable(jso);
  if (((ssize_t) len) > curlen)
  {
    dstbuf_idx = (char *) malloc(len + 1);
    if ((&dstbuf[dstbuf_idx]) == 0)
    {
      return 0;
    }
    if (JC_STRING(jso)->len < 0)
    {
      free(JC_STRING(jso)->c_string.pdata);
    }
    JC_STRING(jso)->c_string.pdata = &dstbuf[dstbuf_idx];
    newlen = -((ssize_t) len);
  }
  else
    if (JC_STRING(jso)->len < 0)
  {
    newlen = -((ssize_t) len);
  }
  memcpy(dstbuf, (const void *) s, len);
  dstbuf[len + dstbuf_idx] = '\0';
  JC_STRING(jso)->len = newlen;
  return 1;
}

int json_object_set_string(json_object *jso, const char *s)
{
  return _json_object_set_string_len(jso, s, strlen(s));
}

int json_object_set_string_len(json_object *jso, const char *s, int len)
{
  return _json_object_set_string_len(jso, s, len);
}

static int json_object_array_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int had_children = 0;
  size_t ii;
  printbuf_memappend(pb, "[", (sizeof("[")) - 1);
  for (ii = 0; ii < json_object_array_length(jso); ii += 1)
  {
    struct json_object *val;
    unsigned int val_idx = 0;
    if (had_children)
    {
      printbuf_memappend(pb, ",", (sizeof(",")) - 1);
    }
    if (flags & (1 << 1))
    {
      printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    }
    had_children = 1;
    if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
    {
      printbuf_memappend(pb, " ", (sizeof(" ")) - 1);
    }
    indent(pb, level + 1, flags);
    val_idx = json_object_array_get_idx(jso, ii);
    if ((&val[val_idx]) == 0)
    {
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
      }
      printbuf_memappend(pb, "null", (sizeof("null")) - 1);
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
      }
    }
    else
      if (val->_to_json_string(val, pb, level + 1, flags) < 0)
    {
      return -1;
    }
  }

  if ((flags & (1 << 1)) && had_children)
  {
    printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    indent(pb, level, flags);
  }
  if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
  {
    return printbuf_memappend(pb, " ]", (sizeof(" ]")) - 1);
  }
  return printbuf_memappend(pb, "]", (sizeof("]")) - 1);
}

static void json_object_array_entry_free(void *data)
{
  json_object_put((struct json_object *) data);
}

static void json_object_array_delete(struct json_object *jso)
{
  array_list_free(JC_ARRAY(jso)->c_array);
  json_object_generic_delete(jso);
}

struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}

struct json_object *json_object_new_array_ext(int initial_size)
{
  struct json_object_array *jso = (struct json_object_array *) json_object_new(json_type_array, sizeof(struct json_object_array), &json_object_array_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_array = array_list_new2(&json_object_array_entry_free, initial_size);
  if (jso->c_array == 0)
  {
    free(jso);
    return 0;
  }
  return &jso->base;
}

struct array_list *json_object_get_array(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_array:
      return JC_ARRAY_C(jso)->c_array;

    default:
      return 0;

  }

}

void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  assert(json_object_get_type(jso) == json_type_array);
  array_list_sort(JC_ARRAY(jso)->c_array, sort_fn);
}

struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  struct json_object **result;
  unsigned int result_idx = 0;
  assert(json_object_get_type(jso) == json_type_array);
  result_idx = (struct json_object **) array_list_bsearch((const void **) ((void *) (&key)), JC_ARRAY_C(jso)->c_array, sort_fn);
  if (!(&result[result_idx]))
  {
    return 0;
  }
  return result[result_idx];
}

size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}

int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}

int json_object_array_insert_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_insert_idx(JC_ARRAY(jso)->c_array, idx, val);
}

int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}

int json_object_array_del_idx(struct json_object *jso, size_t idx, size_t count)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_del_idx(JC_ARRAY(jso)->c_array, idx, count);
}

struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}

static int json_array_equal(struct json_object *jso1, struct json_object *jso2)
{
  size_t len;
  size_t i;
  len = json_object_array_length(jso1);
  if (len != json_object_array_length(jso2))
  {
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!json_object_equal(json_object_array_get_idx(jso1, i), json_object_array_get_idx(jso2, i)))
    {
      return 0;
    }
  }

  return 1;
}

int json_object_array_shrink(struct json_object *jso, int empty_slots)
{
  if (empty_slots < 0)
  {
    json_abort("json_object_array_shrink called with negative empty_slots");
  }
  return array_list_shrink(JC_ARRAY(jso)->c_array, empty_slots);
}

struct json_object *json_object_new_null(void)
{
  return 0;
}

static int json_object_all_values_equal(struct json_object *jso1, struct json_object *jso2)
{
  struct json_object_iter iter;
  struct json_object *sub;
  assert(json_object_get_type(jso1) == json_type_object);
  assert(json_object_get_type(jso2) == json_type_object);
  for (iter.entry = lh_table_head(json_object_get_object(jso1)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso2)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
    if (!json_object_equal(iter.val, sub))
    {
      return 0;
    }
  }

  for (iter.entry = lh_table_head(json_object_get_object(jso2)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso1)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
  }

  return 1;
}

int json_object_equal(struct json_object *jso1, struct json_object *jso2)
{
  if (jso1 == jso2)
  {
    return 1;
  }
  if ((!jso1) || (!jso2))
  {
    return 0;
  }
  if (jso1->o_type != jso2->o_type)
  {
    return 0;
  }
  switch (jso1->o_type)
  {
    case json_type_boolean:
      return JC_BOOL(jso1)->c_boolean == JC_BOOL(jso2)->c_boolean;

    case json_type_double:
      return JC_DOUBLE(jso1)->c_double == JC_DOUBLE(jso2)->c_double;

    case json_type_int:
    {
      struct json_object_int *int1 = JC_INT(jso1);
      struct json_object_int *int2 = JC_INT(jso2);
      if (int1->cint_type == json_object_int_type_int64)
      {
        if (int2->cint_type == json_object_int_type_int64)
        {
          return int1->cint.c_int64 == int2->cint.c_int64;
        }
        if (int1->cint.c_int64 < 0)
        {
          return 0;
        }
        return ((uint64_t) int1->cint.c_int64) == int2->cint.c_uint64;
      }
      if (int2->cint_type == json_object_int_type_uint64)
      {
        return int1->cint.c_uint64 == int2->cint.c_uint64;
      }
      if (int2->cint.c_int64 < 0)
      {
        return 0;
      }
      return int1->cint.c_uint64 == ((uint64_t) int2->cint.c_int64);
    }

    case json_type_string:
    {
      return (_json_object_get_string_len(JC_STRING(jso1)) == _json_object_get_string_len(JC_STRING(jso2))) && (memcmp(get_string_component(jso1), get_string_component(jso2), _json_object_get_string_len(JC_STRING(jso1))) == 0);
    }

    case json_type_object:
      return json_object_all_values_equal(jso1, jso2);

    case json_type_array:
      return json_array_equal(jso1, jso2);

    case json_type_null:
      return 1;

  }

  ;
  return 0;
}

static int json_object_copy_serializer_data(struct json_object *src, struct json_object *dst)
{
  if ((!src->_userdata) && (!src->_user_delete))
  {
    return 0;
  }
  if ((dst->_to_json_string == json_object_userdata_to_json_string) || (dst->_to_json_string == _json_object_userdata_to_json_string))
  {
    char *p;
    unsigned int p_idx = 0;
    assert(src->_userdata);
    p_idx = strdup(src->_userdata);
    if ((&p[p_idx]) == 0)
    {
      _json_c_set_last_err("json_object_copy_serializer_data: out of memory\n");
      return -1;
    }
    dst->_userdata = &p[p_idx];
  }
  else
  {
    _json_c_set_last_err("json_object_copy_serializer_data: unable to copy unknown serializer data: %p\n", (void *) dst->_to_json_string);
    return -1;
  }
  dst->_user_delete = src->_user_delete;
  return 0;
}

int json_c_shallow_copy_default(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
{
  switch (src->o_type)
  {
    case json_type_boolean:
      *dst = json_object_new_boolean(JC_BOOL(src)->c_boolean);
      break;

    case json_type_double:
      *dst = json_object_new_double(JC_DOUBLE(src)->c_double);
      break;

    case json_type_int:
      switch (JC_INT(src)->cint_type)
    {
      case json_object_int_type_int64:
        *dst = json_object_new_int64(JC_INT(src)->cint.c_int64);
        break;

      case json_object_int_type_uint64:
        *dst = json_object_new_uint64(JC_INT(src)->cint.c_uint64);
        break;

      default:
        json_abort("invalid cint_type");

    }

      break;

    case json_type_string:
      *dst = json_object_new_string_len(get_string_component(src), _json_object_get_string_len(JC_STRING(src)));
      break;

    case json_type_object:
      *dst = json_object_new_object();
      break;

    case json_type_array:
      *dst = json_object_new_array();
      break;

    default:
      errno = EINVAL;
      return -1;

  }

  if (!(*dst))
  {
    errno = ENOMEM;
    return -1;
  }
  (*dst)->_to_json_string = src->_to_json_string;
  return 1;
}

static int json_object_deep_copy_recursive(struct json_object *src, struct json_object *parent, const char *key_in_parent, size_t index_in_parent, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  struct json_object_iter iter;
  size_t src_array_len;
  size_t ii;
  int shallow_copy_rc = 0;
  shallow_copy_rc = shallow_copy(src, parent, key_in_parent, index_in_parent, dst);
  if (shallow_copy_rc < 1)
  {
    errno = EINVAL;
    return -1;
  }
  assert((*dst) != 0);
  switch (src->o_type)
  {
    case json_type_object:
      for (iter.entry = lh_table_head(json_object_get_object(src)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
    {
      struct json_object *jso = 0;
      unsigned int jso_idx = 0;
      if (!iter.val)
      {
        jso_idx = 0;
      }
      else
        if (json_object_deep_copy_recursive(iter.val, src, iter.key, 4294967295U, &(&jso[jso_idx]), shallow_copy) < 0)
      {
        json_object_put(jso);
        return -1;
      }
      if (json_object_object_add(*dst, iter.key, jso) < 0)
      {
        json_object_put(jso);
        return -1;
      }
    }

      break;

    case json_type_array:
      src_array_len = json_object_array_length(src);
      for (ii = 0; ii < src_array_len; ii += 1)
    {
      struct json_object *jso = 0;
      unsigned int jso_idx = 0;
      struct json_object *jso1 = json_object_array_get_idx(src, ii);
      if (!jso1)
      {
        jso_idx = 0;
      }
      else
        if (json_object_deep_copy_recursive(jso1, src, 0, ii, &(&jso[jso_idx]), shallow_copy) < 0)
      {
        json_object_put(jso);
        return -1;
      }
      if (json_object_array_add(*dst, jso) < 0)
      {
        json_object_put(jso);
        return -1;
      }
    }

      break;

    default:
      break;

  }

  if (shallow_copy_rc != 2)
  {
    return json_object_copy_serializer_data(src, *dst);
  }
  return 0;
}

int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  unsigned int shallow_copy_idx = 0;
  int rc;
  if (((!src) || (!dst)) || (*dst))
  {
    errno = EINVAL;
    return -1;
  }
  if ((&shallow_copy[shallow_copy_idx]) == 0)
  {
    shallow_copy_idx = json_c_shallow_copy_default;
  }
  rc = json_object_deep_copy_recursive(src, 0, 0, 4294967295U, dst, shallow_copy);
  if (rc < 0)
  {
    json_object_put(*dst);
    *dst = 0;
  }
  return rc;
}

static void json_abort(const char *message)
{
  if (message != 0)
  {
    fprintf(stderr, "json-c aborts with error: %s\n", message);
  }
  abort();
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

const char *json_number_chars = "0123456789.+-eE";
const char *json_hex_chars = "0123456789abcdefABCDEF";
static void json_object_generic_delete(struct json_object *jso);
inline static struct json_object_object *JC_OBJECT(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_object *JC_OBJECT_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_array *JC_ARRAY(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_array *JC_ARRAY_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_boolean *JC_BOOL(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_boolean *JC_BOOL_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_double *JC_DOUBLE(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_double *JC_DOUBLE_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_int *JC_INT(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_int *JC_INT_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object_string *JC_STRING(struct json_object *jso)
{
  return (void *) jso;
}

inline static const struct json_object_string *JC_STRING_C(const struct json_object *jso)
{
  return (const void *) jso;
}

inline static struct json_object *json_object_new(enum json_type o_type, size_t alloc_size, json_object_to_json_string_fn *to_json_string);
static void json_object_object_delete(struct json_object *jso_base);
static void json_object_string_delete(struct json_object *jso);
static void json_object_array_delete(struct json_object *jso);
static json_object_to_json_string_fn json_object_object_to_json_string;
static json_object_to_json_string_fn json_object_boolean_to_json_string;
static json_object_to_json_string_fn json_object_double_to_json_string_default;
static json_object_to_json_string_fn json_object_int_to_json_string;
static json_object_to_json_string_fn json_object_string_to_json_string;
static json_object_to_json_string_fn json_object_array_to_json_string;
static json_object_to_json_string_fn _json_object_userdata_to_json_string;
static void json_abort(const char *message);
inline static char *get_string_component_mutable(struct json_object *jso)
{
  if (JC_STRING_C(jso)->len < 0)
  {
    return JC_STRING(jso)->c_string.pdata;
  }
  return JC_STRING(jso)->c_string.idata;
}

inline static const char *get_string_component(const struct json_object *jso)
{
  return get_string_component_mutable((void *) ((uintptr_t) ((const void *) jso)));
}

static int json_escape_str(struct printbuf *pb, const char *str, size_t len, int flags)
{
  size_t pos = 0;
  size_t start_offset = 0;
  unsigned char c;
  while (len)
  {
    len -= 1;
    c = str[pos];
    switch (c)
    {
      case '\b':

      case '\n':

      case '\r':

      case '\t':

      case '\f':

      case '"':

      case '\\':

      case '/':
        if ((flags & (1 << 4)) && (c == '/'))
      {
        pos += 1;
        break;
      }
        if (pos > start_offset)
      {
        printbuf_memappend(pb, str + start_offset, pos - start_offset);
      }
        if (c == '\b')
      {
        printbuf_memappend(pb, "\\b", 2);
      }
      else
        if (c == '\n')
      {
        printbuf_memappend(pb, "\\n", 2);
      }
      else
        if (c == '\r')
      {
        printbuf_memappend(pb, "\\r", 2);
      }
      else
        if (c == '\t')
      {
        printbuf_memappend(pb, "\\t", 2);
      }
      else
        if (c == '\f')
      {
        printbuf_memappend(pb, "\\f", 2);
      }
      else
        if (c == '"')
      {
        printbuf_memappend(pb, "\\\"", 2);
      }
      else
        if (c == '\\')
      {
        printbuf_memappend(pb, "\\\\", 2);
      }
      else
        if (c == '/')
      {
        printbuf_memappend(pb, "\\/", 2);
      }
        pos += 1;
        start_offset = pos;
        break;

      default:
        if (c < ' ')
      {
        char sbuf[7];
        if (pos > start_offset)
        {
          printbuf_memappend(pb, str + start_offset, pos - start_offset);
        }
        snprintf(sbuf, sizeof(sbuf), "\\u00%c%c", json_hex_chars[c >> 4], json_hex_chars[c & 0xf]);
        do
        {
          if ((pb->size - pb->bpos) > (((int) (sizeof(sbuf))) - 1))
          {
            memcpy(pb->buf + pb->bpos, sbuf, ((int) (sizeof(sbuf))) - 1);
            pb->bpos += ((int) (sizeof(sbuf))) - 1;
            pb->buf[pb->bpos] = '\0';
          }
          else
          {
            printbuf_memappend(pb, sbuf, ((int) (sizeof(sbuf))) - 1);
          }
        }
        while (0);
        pos += 1;
        start_offset = pos;
      }
      else
        pos++;
        pos += 1;

    }

  }

  if (pos > start_offset)
  {
    printbuf_memappend(pb, str + start_offset, pos - start_offset);
  }
  return 0;
}

struct json_object *json_object_get(struct json_object *jso)
{
  if (!jso)
  {
    return jso;
  }
  assert(jso->_ref_count < UINT32_MAX);
  jso->_ref_count += 1;
  return jso;
}

int json_object_put(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  assert(jso->_ref_count > 0);
  if ((--jso->_ref_count) > 0)
  {
    return 0;
  }
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  switch (jso->o_type)
  {
    case json_type_object:
      json_object_object_delete(jso);
      break;

    case json_type_array:
      json_object_array_delete(jso);
      break;

    case json_type_string:
      json_object_string_delete(jso);
      break;

    default:
      json_object_generic_delete(jso);
      break;

  }

  return 1;
}

static void json_object_generic_delete(struct json_object *jso)
{
  printbuf_free(jso->_pb);
  free(jso);
}

inline static struct json_object *json_object_new(enum json_type o_type, size_t alloc_size, json_object_to_json_string_fn *to_json_string)
{
  struct json_object *jso;
  unsigned int jso_idx = 0;
  jso_idx = (struct json_object *) malloc(alloc_size);
  if (!(&jso[jso_idx]))
  {
    return 0;
  }
  jso->o_type = o_type;
  jso->_ref_count = 1;
  jso->_to_json_string = to_json_string;
  jso->_pb = 0;
  jso->_user_delete = 0;
  jso->_userdata = 0;
  return jso;
}

int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
}

enum json_type json_object_get_type(const struct json_object *jso)
{
  if (!jso)
  {
    return json_type_null;
  }
  return jso->o_type;
}

void *json_object_get_userdata(json_object *jso)
{
  return (jso) ? (jso->_userdata) : (0);
}

void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete)
{
  assert(jso != 0);
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  jso->_userdata = userdata;
  jso->_user_delete = user_delete;
}

void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete)
{
  json_object_set_userdata(jso, userdata, user_delete);
  if (to_string_func == 0)
  {
    switch (jso->o_type)
    {
      case json_type_null:
        jso->_to_json_string = 0;
        break;

      case json_type_boolean:
        jso->_to_json_string = &json_object_boolean_to_json_string;
        break;

      case json_type_double:
        jso->_to_json_string = &json_object_double_to_json_string_default;
        break;

      case json_type_int:
        jso->_to_json_string = &json_object_int_to_json_string;
        break;

      case json_type_object:
        jso->_to_json_string = &json_object_object_to_json_string;
        break;

      case json_type_array:
        jso->_to_json_string = &json_object_array_to_json_string;
        break;

      case json_type_string:
        jso->_to_json_string = &json_object_string_to_json_string;
        break;

    }

    return;
  }
  jso->_to_json_string = to_string_func;
}

const char *json_object_to_json_string_length(struct json_object *jso, int flags, size_t *length)
{
  const char *r = 0;
  unsigned int r_idx = 0;
  size_t s = 0;
  if (!jso)
  {
    s = 4;
    r_idx = "null";
  }
  else
    if (jso->_pb || (jso->_pb = printbuf_new()))
  {
    printbuf_reset(jso->_pb);
    if (jso->_to_json_string(jso, jso->_pb, 0, flags) >= 0)
    {
      s = (size_t) jso->_pb->bpos;
      r_idx = jso->_pb->buf;
    }
  }
  if (length)
  {
    *length = s;
  }
  return r;
}

const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}

const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}

static void indent(struct printbuf *pb, int level, int flags)
{
  if (flags & (1 << 1))
  {
    if (flags & (1 << 3))
    {
      printbuf_memset(pb, -1, '\t', level);
    }
    else
    {
      printbuf_memset(pb, -1, ' ', level * 2);
    }
  }
}

static int json_object_object_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int had_children = 0;
  struct json_object_iter iter;
  printbuf_memappend(pb, "{", (sizeof("{")) - 1);
  for (iter.entry = lh_table_head(json_object_get_object(jso)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (had_children)
    {
      printbuf_memappend(pb, ",", (sizeof(",")) - 1);
    }
    if (flags & (1 << 1))
    {
      printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    }
    had_children = 1;
    if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
    {
      printbuf_memappend(pb, " ", (sizeof(" ")) - 1);
    }
    indent(pb, level + 1, flags);
    if (flags & (1 << 5))
    {
      printbuf_memappend(pb, "\033[0;34m", (sizeof("\033[0;34m")) - 1);
    }
    printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
    json_escape_str(pb, iter.key, strlen(iter.key), flags);
    printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
    if (flags & (1 << 5))
    {
      printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
    }
    if (flags & (1 << 0))
    {
      printbuf_memappend(pb, ": ", (sizeof(": ")) - 1);
    }
    else
      printbuf_memappend(pb, ":", (sizeof(":")) - 1);
    if (iter.val == 0)
    {
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
      }
      printbuf_memappend(pb, "null", (sizeof("null")) - 1);
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
      }
    }
    else
      if (iter.val->_to_json_string(iter.val, pb, level + 1, flags) < 0)
    {
      return -1;
    }
  }

  if ((flags & (1 << 1)) && had_children)
  {
    printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    indent(pb, level, flags);
  }
  if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
  {
    return printbuf_memappend(pb, " }", (sizeof(" }")) - 1);
  }
  else
    return printbuf_memappend(pb, "}", (sizeof("}")) - 1);
}

static void json_object_lh_entry_free(struct lh_entry *ent)
{
  if (!lh_entry_k_is_constant(ent))
  {
    free(lh_entry_k(ent));
  }
  json_object_put((struct json_object *) lh_entry_v(ent));
}

static void json_object_object_delete(struct json_object *jso_base)
{
  lh_table_free(JC_OBJECT(jso_base)->c_object);
  json_object_generic_delete(jso_base);
}

struct json_object *json_object_new_object(void)
{
  struct json_object_object *jso = (struct json_object_object *) json_object_new(json_type_object, sizeof(struct json_object_object), &json_object_object_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_object = lh_kchar_table_new(16, &json_object_lh_entry_free);
  if (!jso->c_object)
  {
    json_object_generic_delete(&jso->base);
    errno = ENOMEM;
    return 0;
  }
  return &jso->base;
}

struct lh_table *json_object_get_object(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
      return JC_OBJECT_C(jso)->c_object;

    default:
      return 0;

  }

}

int json_object_object_add_ex(struct json_object *jso, const char * const key, struct json_object * const val, const unsigned opts)
{
  struct json_object *existing_value = 0;
  unsigned int existing_value_idx = 0;
  struct lh_entry *existing_entry;
  unsigned int existing_entry_idx = 0;
  unsigned long hash;
  assert(json_object_get_type(jso) == json_type_object);
  hash = lh_get_hash(JC_OBJECT(jso)->c_object, (const void *) key);
  existing_entry_idx = (opts & (1 << 1)) ? (0) : (lh_table_lookup_entry_w_hash(JC_OBJECT(jso)->c_object, (const void *) key, hash));
  if (jso == val)
  {
    return -1;
  }
  if (!(&existing_entry[existing_entry_idx]))
  {
    const void * const k = (opts & (1 << 2)) ? ((const void *) key) : (strdup(key));
    if (k == 0)
    {
      return -1;
    }
    return lh_table_insert_w_hash(JC_OBJECT(jso)->c_object, k, val, hash, opts);
  }
  existing_value_idx = (json_object *) lh_entry_v(existing_entry);
  if (existing_value)
  {
    json_object_put(existing_value);
  }
  lh_entry_set_val(existing_entry, val);
  return 0;
}

int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}

int json_object_object_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_object);
  return lh_table_length(JC_OBJECT_C(jso)->c_object);
}

size_t json_c_object_sizeof(void)
{
  return sizeof(struct json_object);
}

struct json_object *json_object_object_get(const struct json_object *jso, const char *key)
{
  struct json_object *result = 0;
  json_object_object_get_ex(jso, key, &result);
  return result;
}

json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);

    default:
      if (value != 0)
    {
      *value = 0;
    }
      return 0;

  }

}

void json_object_object_del(struct json_object *jso, const char *key)
{
  assert(json_object_get_type(jso) == json_type_object);
  lh_table_delete(JC_OBJECT(jso)->c_object, key);
}

static int json_object_boolean_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int ret;
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
  }
  if (JC_BOOL(jso)->c_boolean)
  {
    ret = printbuf_memappend(pb, "true", (sizeof("true")) - 1);
  }
  else
    ret = printbuf_memappend(pb, "false", (sizeof("false")) - 1);
  if ((ret > (-1)) && (flags & (1 << 5)))
  {
    return printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
  }
  return ret;
}

struct json_object *json_object_new_boolean(json_bool b)
{
  struct json_object_boolean *jso = (struct json_object_boolean *) json_object_new(json_type_boolean, sizeof(struct json_object_boolean), &json_object_boolean_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_boolean = b;
  return &jso->base;
}

json_bool json_object_get_boolean(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_int:
      switch (JC_INT_C(jso)->cint_type)
    {
      case json_object_int_type_int64:
        return JC_INT_C(jso)->cint.c_int64 != 0;

      case json_object_int_type_uint64:
        return JC_INT_C(jso)->cint.c_uint64 != 0;

      default:
        json_abort("invalid cint_type");

    }


    case json_type_double:
      return JC_DOUBLE_C(jso)->c_double != 0;

    case json_type_string:
      return JC_STRING_C(jso)->len != 0;

    default:
      return 0;

  }

}

int json_object_set_boolean(struct json_object *jso, json_bool new_value)
{
  if ((!jso) || (jso->o_type != json_type_boolean))
  {
    return 0;
  }
  JC_BOOL(jso)->c_boolean = new_value;
  return 1;
}

static int json_object_int_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  char sbuf[21];
  if (JC_INT(jso)->cint_type == json_object_int_type_int64)
  {
    snprintf(sbuf, sizeof(sbuf), "%d", JC_INT(jso)->cint.c_int64);
  }
  else
    snprintf(sbuf, sizeof(sbuf), "%u", JC_INT(jso)->cint.c_uint64);
  return printbuf_memappend(pb, sbuf, strlen(sbuf));
}

struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}

int32_t json_object_get_int(const struct json_object *jso)
{
  int64_t cint64 = 0;
  double cdouble;
  enum json_type o_type;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  o_type = jso->o_type;
  if (o_type == json_type_int)
  {
    const struct json_object_int *jsoint = JC_INT_C(jso);
    if (jsoint->cint_type == json_object_int_type_int64)
    {
      cint64 = jsoint->cint.c_int64;
    }
    else
    {
      if (jsoint->cint.c_uint64 >= INT64_MAX)
      {
        cint64 = INT64_MAX;
      }
      else
        cint64 = (int64_t) jsoint->cint.c_uint64;
    }
  }
  else
    if (o_type == json_type_string)
  {
    if (json_parse_int64(get_string_component(jso), &cint64) != 0)
    {
      return 0;
    }
    o_type = json_type_int;
  }
  switch (o_type)
  {
    case json_type_int:
      if (cint64 < INT32_MIN)
    {
      errno = ERANGE;
      return INT32_MIN;
    }
      if (cint64 > INT32_MAX)
    {
      errno = ERANGE;
      return INT32_MAX;
    }
      return (int32_t) cint64;

    case json_type_double:
      cdouble = JC_DOUBLE_C(jso)->c_double;
      if (cdouble < INT32_MIN)
    {
      errno = ERANGE;
      return INT32_MIN;
    }
      if (cdouble > INT32_MAX)
    {
      errno = ERANGE;
      return INT32_MAX;
    }
      if (isnan(cdouble))
    {
      errno = EINVAL;
      return INT32_MIN;
    }
      return (int32_t) cdouble;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    default:
      return 0;

  }

}

int json_object_set_int(struct json_object *jso, int new_value)
{
  return json_object_set_int64(jso, (int64_t) new_value);
}

struct json_object *json_object_new_int64(int64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_int64 = i;
  jso->cint_type = json_object_int_type_int64;
  return &jso->base;
}

struct json_object *json_object_new_uint64(uint64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_uint64 = i;
  jso->cint_type = json_object_int_type_uint64;
  return &jso->base;
}

int64_t json_object_get_int64(const struct json_object *jso)
{
  int64_t cint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
          return jsoint->cint.c_int64;

        case json_object_int_type_uint64:
          if (jsoint->cint.c_uint64 > INT64_MAX)
        {
          errno = ERANGE;
          return INT64_MAX;
        }
          return (int64_t) jsoint->cint.c_uint64;

        default:
          json_abort("invalid cint_type");

      }

    }

    case json_type_double:
      if (JC_DOUBLE_C(jso)->c_double > ((double) INT64_MAX))
    {
      errno = ERANGE;
      return INT64_MAX;
    }
      if (JC_DOUBLE_C(jso)->c_double < ((double) INT64_MIN))
    {
      errno = ERANGE;
      return INT64_MIN;
    }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
    {
      errno = EINVAL;
      return INT64_MIN;
    }
      return (int64_t) JC_DOUBLE_C(jso)->c_double;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      if (json_parse_int64(get_string_component(jso), &cint) == 0)
    {
      return cint;
    }

    default:
      return 0;

  }

}

uint64_t json_object_get_uint64(const struct json_object *jso)
{
  uint64_t cuint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
          if (jsoint->cint.c_int64 < 0)
        {
          errno = ERANGE;
          return 0;
        }
          return (uint64_t) jsoint->cint.c_int64;

        case json_object_int_type_uint64:
          return jsoint->cint.c_uint64;

        default:
          json_abort("invalid cint_type");

      }

    }

    case json_type_double:
      if (JC_DOUBLE_C(jso)->c_double > ((double) UINT64_MAX))
    {
      errno = ERANGE;
      return UINT64_MAX;
    }
      if (JC_DOUBLE_C(jso)->c_double < 0)
    {
      errno = ERANGE;
      return 0;
    }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
    {
      errno = EINVAL;
      return 0;
    }
      return (uint64_t) JC_DOUBLE_C(jso)->c_double;

    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      if (json_parse_uint64(get_string_component(jso), &cuint) == 0)
    {
      return cuint;
    }

    default:
      return 0;

  }

}

int json_object_set_int64(struct json_object *jso, int64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_int64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_int64;
  return 1;
}

int json_object_set_uint64(struct json_object *jso, uint64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_uint64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_uint64;
  return 1;
}

int json_object_int_inc(struct json_object *jso, int64_t val)
{
  struct json_object_int *jsoint;
  unsigned int jsoint_idx = 0;
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  jsoint_idx = JC_INT(jso);
  switch (jsoint->cint_type)
  {
    case json_object_int_type_int64:
      if ((val > 0) && (jsoint->cint.c_int64 > (INT64_MAX - val)))
    {
      jsoint->cint.c_uint64 = ((uint64_t) jsoint->cint.c_int64) + ((uint64_t) val);
      jsoint->cint_type = json_object_int_type_uint64;
    }
    else
      if ((val < 0) && (jsoint->cint.c_int64 < (INT64_MIN - val)))
    {
      jsoint->cint.c_int64 = INT64_MIN;
    }
    else
    {
      jsoint->cint.c_int64 += val;
    }
      return 1;

    case json_object_int_type_uint64:
      if ((val > 0) && (jsoint->cint.c_uint64 > (UINT64_MAX - ((uint64_t) val))))
    {
      jsoint->cint.c_uint64 = UINT64_MAX;
    }
    else
      if ((val < 0) && (jsoint->cint.c_uint64 < ((uint64_t) (-val))))
    {
      jsoint->cint.c_int64 = ((int64_t) jsoint->cint.c_uint64) + val;
      jsoint->cint_type = json_object_int_type_int64;
    }
    else
      if ((val < 0) && (jsoint->cint.c_uint64 >= ((uint64_t) (-val))))
    {
      jsoint->cint.c_uint64 -= (uint64_t) (-val);
    }
    else
    {
      jsoint->cint.c_uint64 += val;
    }
      return 1;

    default:
      json_abort("invalid cint_type");

  }

}

static char *tls_serialization_float_format = 0;
static char *global_serialization_float_format = 0;
int json_c_set_serialization_double_format(const char *double_format, int global_or_thread)
{
  if (global_or_thread == 0)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (global_serialization_float_format)
    {
      free(global_serialization_float_format);
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      global_serialization_float_format = p;
    }
    else
    {
      global_serialization_float_format = 0;
    }
  }
  else
    if (global_or_thread == 1)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      tls_serialization_float_format = p;
    }
    else
    {
      tls_serialization_float_format = 0;
    }
  }
  else
  {
    _json_c_set_last_err("json_c_set_serialization_double_format: invalid global_or_thread value: %d\n", global_or_thread);
    return -1;
  }
  return 0;
}

static int json_object_double_to_json_string_format(struct json_object *jso, struct printbuf *pb, int level, int flags, const char *format)
{
  unsigned int format_idx = 0;
  struct json_object_double *jsodbl = JC_DOUBLE(jso);
  char buf[128];
  char *p;
  unsigned int p_idx = 0;
  char *q;
  unsigned int q_idx = 0;
  int size;
  if (isnan(jsodbl->c_double))
  {
    size = snprintf(buf, sizeof(buf), "NaN");
  }
  else
    if (isinf(jsodbl->c_double))
  {
    if (jsodbl->c_double > 0)
    {
      size = snprintf(buf, sizeof(buf), "Infinity");
    }
    else
      size = snprintf(buf, sizeof(buf), "-Infinity");
  }
  else
  {
    const char *std_format = "%.17g";
    int format_drops_decimals = 0;
    int looks_numeric = 0;
    if (!(&format[format_idx]))
    {
      if (tls_serialization_float_format)
      {
        format_idx = tls_serialization_float_format;
      }
      else
        if (global_serialization_float_format)
      {
        format_idx = global_serialization_float_format;
      }
      else
        format_idx = std_format;
    }
    size = snprintf(buf, sizeof(buf), format, jsodbl->c_double);
    if (size < 0)
    {
      return -1;
    }
    p_idx = strchr(buf, ',');
    if (p)
    {
      p[p_idx] = '.';
    }
    else
      p_idx = strchr(buf, '.');
    if (((&format[format_idx]) == std_format) || (strstr(format, ".0f") == 0))
    {
      format_drops_decimals = 1;
    }
    looks_numeric = ((buf[0] >= '0') && (buf[0] <= '9')) || (((size > 1) && (buf[0] == '-')) && ((buf[1] >= '0') && (buf[1] <= '9')));
    if (((((size < (((int) (sizeof(buf))) - 2)) && looks_numeric) && (!(&p[p_idx]))) && (strchr(buf, 'e') == 0)) && format_drops_decimals)
    {
      strcat(buf, ".0");
      size += 2;
    }
    if ((&p[p_idx]) && (flags & (1 << 2)))
    {
      p_idx += 1;
      for (q_idx = &p[p_idx]; q[q_idx]; q_idx += 1)
      {
        if (q[q_idx] != '0')
        {
          p_idx = &q[q_idx];
        }
      }

      if (p[p_idx] != 0)
      {
        p_idx += 1;
        p[p_idx] = 0;
      }
      size = (&p[p_idx]) - buf;
    }
  }
  if (size < 0)
  {
    return -1;
  }
  if (size >= ((int) (sizeof(buf))))
  {
    size = (sizeof(buf)) - 1;
  }
  printbuf_memappend(pb, buf, size);
  return size;
}

static int json_object_double_to_json_string_default(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, 0);
}

int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, (const char *) jso->_userdata);
}

struct json_object *json_object_new_double(double d)
{
  struct json_object_double *jso = (struct json_object_double *) json_object_new(json_type_double, sizeof(struct json_object_double), &json_object_double_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->base._to_json_string = &json_object_double_to_json_string_default;
  jso->c_double = d;
  return &jso->base;
}

struct json_object *json_object_new_double_s(double d, const char *ds)
{
  char *new_ds;
  unsigned int new_ds_idx = 0;
  struct json_object *jso = json_object_new_double(d);
  if (!jso)
  {
    return 0;
  }
  new_ds_idx = strdup(ds);
  if (!(&new_ds[new_ds_idx]))
  {
    json_object_generic_delete(jso);
    errno = ENOMEM;
    return 0;
  }
  json_object_set_serializer(jso, _json_object_userdata_to_json_string, new_ds, json_object_free_userdata);
  return jso;
}

static int _json_object_userdata_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_userdata_to_json_string(jso, pb, level, flags);
}

int json_object_userdata_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int userdata_len = strlen((const char *) jso->_userdata);
  printbuf_memappend(pb, (const char *) jso->_userdata, userdata_len);
  return userdata_len;
}

void json_object_free_userdata(struct json_object *jso, void *userdata)
{
  free(userdata);
}

double json_object_get_double(const struct json_object *jso)
{
  double cdouble;
  char *errPtr = 0;
  if (!jso)
  {
    return 0.0;
  }
  switch (jso->o_type)
  {
    case json_type_double:
      return JC_DOUBLE_C(jso)->c_double;

    case json_type_int:
      switch (JC_INT_C(jso)->cint_type)
    {
      case json_object_int_type_int64:
        return JC_INT_C(jso)->cint.c_int64;

      case json_object_int_type_uint64:
        return JC_INT_C(jso)->cint.c_uint64;

      default:
        json_abort("invalid cint_type");

    }


    case json_type_boolean:
      return JC_BOOL_C(jso)->c_boolean;

    case json_type_string:
      errno = 0;
      cdouble = strtod(get_string_component(jso), &errPtr);
      if (errPtr == get_string_component(jso))
    {
      errno = EINVAL;
      return 0.0;
    }
      if ((*errPtr) != '\0')
    {
      errno = EINVAL;
      return 0.0;
    }
      if (((HUGE_VAL == cdouble) || ((-HUGE_VAL) == cdouble)) && (ERANGE == errno))
    {
      cdouble = 0.0;
    }
      return cdouble;

    default:
      errno = EINVAL;
      return 0.0;

  }

}

int json_object_set_double(struct json_object *jso, double new_value)
{
  if ((!jso) || (jso->o_type != json_type_double))
  {
    return 0;
  }
  JC_DOUBLE(jso)->c_double = new_value;
  if (jso->_to_json_string == (&_json_object_userdata_to_json_string))
  {
    json_object_set_serializer(jso, 0, 0, 0);
  }
  return 1;
}

static int json_object_string_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  ssize_t len = JC_STRING(jso)->len;
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0;32m", (sizeof("\033[0;32m")) - 1);
  }
  printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
  json_escape_str(pb, get_string_component(jso), (len < 0) ? (-((ssize_t) len)) : (len), flags);
  printbuf_memappend(pb, "\"", (sizeof("\"")) - 1);
  if (flags & (1 << 5))
  {
    printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
  }
  return 0;
}

static void json_object_string_delete(struct json_object *jso)
{
  if (JC_STRING(jso)->len < 0)
  {
    free(JC_STRING(jso)->c_string.pdata);
  }
  json_object_generic_delete(jso);
}

static struct json_object *_json_object_new_string(const char *s, const size_t len)
{
  size_t objsize;
  struct json_object_string *jso;
  unsigned int jso_idx = 0;
  if (len > ((9223372036854775807L - ((sizeof(*(&jso[jso_idx]))) - (sizeof(jso->c_string)))) - 1))
  {
    return 0;
  }
  objsize = (((sizeof(*(&jso[jso_idx]))) - (sizeof(jso->c_string))) + len) + 1;
  if (len < (sizeof(void *)))
  {
    objsize += (sizeof(void *)) - len;
  }
  jso_idx = (struct json_object_string *) json_object_new(json_type_string, objsize, &json_object_string_to_json_string);
  if (!(&jso[jso_idx]))
  {
    return 0;
  }
  jso->len = len;
  memcpy(jso->c_string.idata, s, len);
  ((char *) jso->c_string.idata)[len] = '\0';
  return &jso->base;
}

struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}

struct json_object *json_object_new_string_len(const char *s, const int len)
{
  return _json_object_new_string(s, len);
}

const char *json_object_get_string(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
      return get_string_component(jso);

    default:
      return json_object_to_json_string(jso);

  }

}

inline static ssize_t _json_object_get_string_len(const struct json_object_string *jso)
{
  ssize_t len;
  len = jso->len;
  return (len < 0) ? (-((ssize_t) len)) : (len);
}

int json_object_get_string_len(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
      return _json_object_get_string_len(JC_STRING_C(jso));

    default:
      return 0;

  }

}

static int _json_object_set_string_len(json_object *jso, const char *s, size_t len)
{
  char *dstbuf;
  unsigned int dstbuf_idx = 0;
  ssize_t curlen;
  ssize_t newlen;
  if ((jso == 0) || (jso->o_type != json_type_string))
  {
    return 0;
  }
  if (len >= (2147483647 - 1))
  {
    return 0;
  }
  curlen = JC_STRING(jso)->len;
  if (curlen < 0)
  {
    if (len == 0)
    {
      free(JC_STRING(jso)->c_string.pdata);
      JC_STRING(jso)->len = (curlen = 0);
    }
    else
    {
      curlen = -curlen;
    }
  }
  newlen = len;
  dstbuf_idx = get_string_component_mutable(jso);
  if (((ssize_t) len) > curlen)
  {
    dstbuf_idx = (char *) malloc(len + 1);
    if ((&dstbuf[dstbuf_idx]) == 0)
    {
      return 0;
    }
    if (JC_STRING(jso)->len < 0)
    {
      free(JC_STRING(jso)->c_string.pdata);
    }
    JC_STRING(jso)->c_string.pdata = &dstbuf[dstbuf_idx];
    newlen = -((ssize_t) len);
  }
  else
    if (JC_STRING(jso)->len < 0)
  {
    newlen = -((ssize_t) len);
  }
  memcpy(dstbuf, (const void *) s, len);
  dstbuf[len + dstbuf_idx] = '\0';
  JC_STRING(jso)->len = newlen;
  return 1;
}

int json_object_set_string(json_object *jso, const char *s)
{
  return _json_object_set_string_len(jso, s, strlen(s));
}

int json_object_set_string_len(json_object *jso, const char *s, int len)
{
  return _json_object_set_string_len(jso, s, len);
}

static int json_object_array_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  int had_children = 0;
  size_t ii;
  printbuf_memappend(pb, "[", (sizeof("[")) - 1);
  for (ii = 0; ii < json_object_array_length(jso); ii += 1)
  {
    struct json_object *val;
    unsigned int val_idx = 0;
    if (had_children)
    {
      printbuf_memappend(pb, ",", (sizeof(",")) - 1);
    }
    if (flags & (1 << 1))
    {
      printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    }
    had_children = 1;
    if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
    {
      printbuf_memappend(pb, " ", (sizeof(" ")) - 1);
    }
    indent(pb, level + 1, flags);
    val_idx = json_object_array_get_idx(jso, ii);
    if ((&val[val_idx]) == 0)
    {
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0;35m", (sizeof("\033[0;35m")) - 1);
      }
      printbuf_memappend(pb, "null", (sizeof("null")) - 1);
      if (flags & (1 << 5))
      {
        printbuf_memappend(pb, "\033[0m", (sizeof("\033[0m")) - 1);
      }
    }
    else
      if (val->_to_json_string(val, pb, level + 1, flags) < 0)
    {
      return -1;
    }
  }

  if ((flags & (1 << 1)) && had_children)
  {
    printbuf_memappend(pb, "\n", (sizeof("\n")) - 1);
    indent(pb, level, flags);
  }
  if ((flags & (1 << 0)) && (!(flags & (1 << 1))))
  {
    return printbuf_memappend(pb, " ]", (sizeof(" ]")) - 1);
  }
  return printbuf_memappend(pb, "]", (sizeof("]")) - 1);
}

static void json_object_array_entry_free(void *data)
{
  json_object_put((struct json_object *) data);
}

static void json_object_array_delete(struct json_object *jso)
{
  array_list_free(JC_ARRAY(jso)->c_array);
  json_object_generic_delete(jso);
}

struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}

struct json_object *json_object_new_array_ext(int initial_size)
{
  struct json_object_array *jso = (struct json_object_array *) json_object_new(json_type_array, sizeof(struct json_object_array), &json_object_array_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_array = array_list_new2(&json_object_array_entry_free, initial_size);
  if (jso->c_array == 0)
  {
    free(jso);
    return 0;
  }
  return &jso->base;
}

struct array_list *json_object_get_array(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_array:
      return JC_ARRAY_C(jso)->c_array;

    default:
      return 0;

  }

}

void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  assert(json_object_get_type(jso) == json_type_array);
  array_list_sort(JC_ARRAY(jso)->c_array, sort_fn);
}

struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  struct json_object **result;
  unsigned int result_idx = 0;
  assert(json_object_get_type(jso) == json_type_array);
  result_idx = (struct json_object **) array_list_bsearch((const void **) ((void *) (&key)), JC_ARRAY_C(jso)->c_array, sort_fn);
  if (!(&result[result_idx]))
  {
    return 0;
  }
  return result[result_idx];
}

size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}

int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}

int json_object_array_insert_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_insert_idx(JC_ARRAY(jso)->c_array, idx, val);
}

int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}

int json_object_array_del_idx(struct json_object *jso, size_t idx, size_t count)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_del_idx(JC_ARRAY(jso)->c_array, idx, count);
}

struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}

static int json_array_equal(struct json_object *jso1, struct json_object *jso2)
{
  size_t len;
  size_t i;
  len = json_object_array_length(jso1);
  if (len != json_object_array_length(jso2))
  {
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!json_object_equal(json_object_array_get_idx(jso1, i), json_object_array_get_idx(jso2, i)))
    {
      return 0;
    }
  }

  return 1;
}

int json_object_array_shrink(struct json_object *jso, int empty_slots)
{
  if (empty_slots < 0)
  {
    json_abort("json_object_array_shrink called with negative empty_slots");
  }
  return array_list_shrink(JC_ARRAY(jso)->c_array, empty_slots);
}

struct json_object *json_object_new_null(void)
{
  return 0;
}

static int json_object_all_values_equal(struct json_object *jso1, struct json_object *jso2)
{
  struct json_object_iter iter;
  struct json_object *sub;
  assert(json_object_get_type(jso1) == json_type_object);
  assert(json_object_get_type(jso2) == json_type_object);
  for (iter.entry = lh_table_head(json_object_get_object(jso1)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso2)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
    if (!json_object_equal(iter.val, sub))
    {
      return 0;
    }
  }

  for (iter.entry = lh_table_head(json_object_get_object(jso2)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso1)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
  }

  return 1;
}

int json_object_equal(struct json_object *jso1, struct json_object *jso2)
{
  if (jso1 == jso2)
  {
    return 1;
  }
  if ((!jso1) || (!jso2))
  {
    return 0;
  }
  if (jso1->o_type != jso2->o_type)
  {
    return 0;
  }
  switch (jso1->o_type)
  {
    case json_type_boolean:
      return JC_BOOL(jso1)->c_boolean == JC_BOOL(jso2)->c_boolean;

    case json_type_double:
      return JC_DOUBLE(jso1)->c_double == JC_DOUBLE(jso2)->c_double;

    case json_type_int:
    {
      struct json_object_int *int1 = JC_INT(jso1);
      struct json_object_int *int2 = JC_INT(jso2);
      if (int1->cint_type == json_object_int_type_int64)
      {
        if (int2->cint_type == json_object_int_type_int64)
        {
          return int1->cint.c_int64 == int2->cint.c_int64;
        }
        if (int1->cint.c_int64 < 0)
        {
          return 0;
        }
        return ((uint64_t) int1->cint.c_int64) == int2->cint.c_uint64;
      }
      if (int2->cint_type == json_object_int_type_uint64)
      {
        return int1->cint.c_uint64 == int2->cint.c_uint64;
      }
      if (int2->cint.c_int64 < 0)
      {
        return 0;
      }
      return int1->cint.c_uint64 == ((uint64_t) int2->cint.c_int64);
    }

    case json_type_string:
    {
      return (_json_object_get_string_len(JC_STRING(jso1)) == _json_object_get_string_len(JC_STRING(jso2))) && (memcmp(get_string_component(jso1), get_string_component(jso2), _json_object_get_string_len(JC_STRING(jso1))) == 0);
    }

    case json_type_object:
      return json_object_all_values_equal(jso1, jso2);

    case json_type_array:
      return json_array_equal(jso1, jso2);

    case json_type_null:
      return 1;

  }

  ;
  return 0;
}

static int json_object_copy_serializer_data(struct json_object *src, struct json_object *dst)
{
  if ((!src->_userdata) && (!src->_user_delete))
  {
    return 0;
  }
  if ((dst->_to_json_string == json_object_userdata_to_json_string) || (dst->_to_json_string == _json_object_userdata_to_json_string))
  {
    char *p;
    unsigned int p_idx = 0;
    assert(src->_userdata);
    p_idx = strdup(src->_userdata);
    if ((&p[p_idx]) == 0)
    {
      _json_c_set_last_err("json_object_copy_serializer_data: out of memory\n");
      return -1;
    }
    dst->_userdata = &p[p_idx];
  }
  else
  {
    _json_c_set_last_err("json_object_copy_serializer_data: unable to copy unknown serializer data: %p\n", (void *) dst->_to_json_string);
    return -1;
  }
  dst->_user_delete = src->_user_delete;
  return 0;
}

int json_c_shallow_copy_default(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
{
  switch (src->o_type)
  {
    case json_type_boolean:
      *dst = json_object_new_boolean(JC_BOOL(src)->c_boolean);
      break;

    case json_type_double:
      *dst = json_object_new_double(JC_DOUBLE(src)->c_double);
      break;

    case json_type_int:
      switch (JC_INT(src)->cint_type)
    {
      case json_object_int_type_int64:
        *dst = json_object_new_int64(JC_INT(src)->cint.c_int64);
        break;

      case json_object_int_type_uint64:
        *dst = json_object_new_uint64(JC_INT(src)->cint.c_uint64);
        break;

      default:
        json_abort("invalid cint_type");

    }

      break;

    case json_type_string:
      *dst = json_object_new_string_len(get_string_component(src), _json_object_get_string_len(JC_STRING(src)));
      break;

    case json_type_object:
      *dst = json_object_new_object();
      break;

    case json_type_array:
      *dst = json_object_new_array();
      break;

    default:
      errno = EINVAL;
      return -1;

  }

  if (!(*dst))
  {
    errno = ENOMEM;
    return -1;
  }
  (*dst)->_to_json_string = src->_to_json_string;
  return 1;
}

static int json_object_deep_copy_recursive(struct json_object *src, struct json_object *parent, const char *key_in_parent, size_t index_in_parent, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  struct json_object_iter iter;
  size_t src_array_len;
  size_t ii;
  int shallow_copy_rc = 0;
  shallow_copy_rc = shallow_copy(src, parent, key_in_parent, index_in_parent, dst);
  if (shallow_copy_rc < 1)
  {
    errno = EINVAL;
    return -1;
  }
  assert((*dst) != 0);
  switch (src->o_type)
  {
    case json_type_object:
      for (iter.entry = lh_table_head(json_object_get_object(src)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
    {
      struct json_object *jso = 0;
      unsigned int jso_idx = 0;
      if (!iter.val)
      {
        jso_idx = 0;
      }
      else
        if (json_object_deep_copy_recursive(iter.val, src, iter.key, 4294967295U, &(&jso[jso_idx]), shallow_copy) < 0)
      {
        json_object_put(jso);
        return -1;
      }
      if (json_object_object_add(*dst, iter.key, jso) < 0)
      {
        json_object_put(jso);
        return -1;
      }
    }

      break;

    case json_type_array:
      src_array_len = json_object_array_length(src);
      for (ii = 0; ii < src_array_len; ii += 1)
    {
      struct json_object *jso = 0;
      unsigned int jso_idx = 0;
      struct json_object *jso1 = json_object_array_get_idx(src, ii);
      if (!jso1)
      {
        jso_idx = 0;
      }
      else
        if (json_object_deep_copy_recursive(jso1, src, 0, ii, &(&jso[jso_idx]), shallow_copy) < 0)
      {
        json_object_put(jso);
        return -1;
      }
      if (json_object_array_add(*dst, jso) < 0)
      {
        json_object_put(jso);
        return -1;
      }
    }

      break;

    default:
      break;

  }

  if (shallow_copy_rc != 2)
  {
    return json_object_copy_serializer_data(src, *dst);
  }
  return 0;
}

int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  unsigned int shallow_copy_idx = 0;
  int rc;
  if (((!src) || (!dst)) || (*dst))
  {
    errno = EINVAL;
    return -1;
  }
  if ((&shallow_copy[shallow_copy_idx]) == 0)
  {
    shallow_copy_idx = json_c_shallow_copy_default;
  }
  rc = json_object_deep_copy_recursive(src, 0, 0, 4294967295U, dst, shallow_copy);
  if (rc < 0)
  {
    json_object_put(*dst);
    *dst = 0;
  }
  return rc;
}

static void json_abort(const char *message)
{
  if (message != 0)
  {
    fprintf(stderr, "json-c aborts with error: %s\n", message);
  }
  abort();
}

