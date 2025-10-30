#include <config.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_types.h>
#include <json_visit.c>
#include <json_visit.h>
#include <linkhash.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>

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
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg);
extern int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg);
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

static int _json_c_visit(json_object *jso, json_object *parent_jso, const char *jso_key, size_t *jso_index, json_c_visit_userfunc *userfunc, void *userarg);
int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg)
{
  int ret = _json_c_visit(jso, 0, 0, 0, userfunc, userarg);
  switch (ret)
  {
    case 0:

    case 7547:

    case 767:

    case 7867:
      return 0;

    default:
      return -1;

  }

}

static int _json_c_visit(json_object *jso, json_object *parent_jso, const char *jso_key, size_t *jso_index, json_c_visit_userfunc *userfunc, void *userarg)
{
  int userret = userfunc(jso, 0, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 0:
      break;

    case 7547:

    case 767:

    case 7867:

    case -1:
      return userret;

    default:
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;

  }

  switch (json_object_get_type(jso))
  {
    case json_type_null:

    case json_type_boolean:

    case json_type_double:

    case json_type_int:

    case json_type_string:
      return 0;

    case json_type_object:
    {
      char *key = 0;
      unsigned int key_idx = 0;
      struct json_object *child = 0;
      unsigned int child_idx = 0;
      for (struct lh_entry *entrykey = lh_table_head(json_object_get_object(jso)), entry_nextkey = 0;       {
        if (entrykey)
        {
          key_idx = (char *) lh_entry_k(entrykey);
          child_idx = (struct json_object *) lh_entry_v(entrykey);
          entry_nextkey_idx = lh_entry_next(entrykey);
        }
        ;
        entrykey;
      }
; entrykey_idx = &entry_nextkey[entry_nextkey_idx])
      {
        userret = _json_c_visit(child, jso, key, 0, userfunc, userarg);
        if (userret == 767)
        {
          break;
        }
        if ((userret == 7867) || (userret == (-1)))
        {
          return userret;
        }
        if ((userret != 0) && (userret != 7547))
        {
          fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
          return -1;
        }
      }

      unsigned int entry_nextkey_idx = 0;
      break;
    }

    case json_type_array:
    {
      size_t array_len = json_object_array_length(jso);
      size_t ii;
      for (ii = 0; ii < array_len; ii += 1)
      {
        json_object *child = json_object_array_get_idx(jso, ii);
        unsigned int child_idx = 0;
        userret = _json_c_visit(child, jso, 0, &ii, userfunc, userarg);
        if (userret == 767)
        {
          break;
        }
        if ((userret == 7867) || (userret == (-1)))
        {
          return userret;
        }
        if ((userret != 0) && (userret != 7547))
        {
          fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
          return -1;
        }
      }

      break;
    }

    default:
      fprintf(stderr, "INTERNAL ERROR: _json_c_visit found object of unknown type: %d\n", json_object_get_type(jso));
      return -1;

  }

  userret = userfunc(jso, 0x02, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 7547:

    case 767:

    case 0:
      return 0;

    case 7867:

    case -1:
      return userret;

    default:
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;

  }

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
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg);
extern int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg);
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

static int _json_c_visit(json_object *jso, json_object *parent_jso, const char *jso_key, size_t *jso_index, json_c_visit_userfunc *userfunc, void *userarg);
int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg)
{
  int ret = _json_c_visit(jso, 0, 0, 0, userfunc, userarg);
  switch (ret)
  {
    case 0:

    case 7547:

    case 767:

    case 7867:
      return 0;

    default:
      return -1;

  }

}

static int _json_c_visit(json_object *jso, json_object *parent_jso, const char *jso_key, size_t *jso_index, json_c_visit_userfunc *userfunc, void *userarg)
{
  int userret = userfunc(jso, 0, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 0:
      break;

    case 7547:

    case 767:

    case 7867:

    case -1:
      return userret;

    default:
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;

  }

  switch (json_object_get_type(jso))
  {
    case json_type_null:

    case json_type_boolean:

    case json_type_double:

    case json_type_int:

    case json_type_string:
      return 0;

    case json_type_object:
    {
      char *key = 0;
      unsigned int key_idx = 0;
      struct json_object *child = 0;
      unsigned int child_idx = 0;
      for (struct lh_entry *entrykey = lh_table_head(json_object_get_object(jso)), entry_nextkey = 0;       {
        if (entrykey)
        {
          key_idx = (char *) lh_entry_k(entrykey);
          child_idx = (struct json_object *) lh_entry_v(entrykey);
          entry_nextkey_idx = lh_entry_next(entrykey);
        }
        ;
        entrykey;
      }
; entrykey_idx = &entry_nextkey[entry_nextkey_idx])
      {
        userret = _json_c_visit(child, jso, key, 0, userfunc, userarg);
        if (userret == 767)
        {
          break;
        }
        if ((userret == 7867) || (userret == (-1)))
        {
          return userret;
        }
        if ((userret != 0) && (userret != 7547))
        {
          fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
          return -1;
        }
      }

      unsigned int entry_nextkey_idx = 0;
      break;
    }

    case json_type_array:
    {
      size_t array_len = json_object_array_length(jso);
      size_t ii;
      for (ii = 0; ii < array_len; ii += 1)
      {
        json_object *child = json_object_array_get_idx(jso, ii);
        unsigned int child_idx = 0;
        userret = _json_c_visit(child, jso, 0, &ii, userfunc, userarg);
        if (userret == 767)
        {
          break;
        }
        if ((userret == 7867) || (userret == (-1)))
        {
          return userret;
        }
        if ((userret != 0) && (userret != 7547))
        {
          fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
          return -1;
        }
      }

      break;
    }

    default:
      fprintf(stderr, "INTERNAL ERROR: _json_c_visit found object of unknown type: %d\n", json_object_get_type(jso));
      return -1;

  }

  userret = userfunc(jso, 0x02, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 7547:

    case 767:

    case 0:
      return 0;

    case 7867:

    case -1:
      return userret;

    default:
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;

  }

}

