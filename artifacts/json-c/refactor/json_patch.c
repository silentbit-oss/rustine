#include <config.h>
#include <errno.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_object_private.h>
#include <json_patch.c>
#include <json_patch.h>
#include <json_pointer.h>
#include <json_pointer_private.h>
#include <json_types.h>
#include <limits.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdlib.h>
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
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
};
int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res);
typedef int (*json_pointer_array_set_cb)(json_object *parent, size_t idx, json_object *value, void *priv);
int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv);
static int json_patch_apply_test(struct json_object **res, struct json_object *patch_elem, const char *path, struct json_patch_error *patch_error)
{
  struct json_object *value1;
  struct json_object *value2;
  if (!json_object_object_get_ex(patch_elem, "value", &value1))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (json_pointer_get(*res, path, &value2))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_equal(value1, value2))
  {
    do
    {
      patch_error->errno_code = ENOENT;
      patch_error->errmsg = "Value of element referenced by 'path' field did not match 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  return 0;
}

static int __json_patch_apply_remove(struct json_pointer_get_result *jpres)
{
  if (json_object_is_type(jpres->parent, json_type_array))
  {
    return json_object_array_del_idx(jpres->parent, jpres->index_in_parent, 1);
  }
  else
    if (jpres->parent && jpres->key_in_parent)
  {
    json_object_object_del(jpres->parent, jpres->key_in_parent);
    return 0;
  }
  else
  {
    (void) json_object_put(jpres->obj);
    jpres->obj = 0;
    return 0;
  }
}

static int json_patch_apply_remove(struct json_object **res, const char *path, struct json_patch_error *patch_error)
{
  struct json_pointer_get_result jpres;
  int rc;
  if (json_pointer_get_internal(*res, path, &jpres))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = __json_patch_apply_remove(&jpres);
  if (rc < 0)
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Unable to remove path referenced by 'path' field";
      errno = 0;
    }
    while (0);
  }
  if (jpres.parent == 0)
  {
    *res = 0;
  }
  return rc;
}

static int json_object_array_insert_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  int *add = priv;
  if (idx > json_object_array_length(parent))
  {
    errno = EINVAL;
    return -1;
  }
  if (*add)
  {
    rc = json_object_array_insert_idx(parent, idx, value);
  }
  else
    rc = json_object_array_put_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}

static int json_patch_apply_add_replace(struct json_object **res, struct json_object *patch_elem, const char *path, int add, struct json_patch_error *patch_error)
{
  struct json_object *value;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "value", &value))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if ((!add) && json_pointer_get(*res, path, 0))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_set_with_array_cb(res, path, json_object_get(value), json_object_array_insert_idx_cb, &add);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(value);
  }
  return rc;
}

static int json_object_array_move_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  struct json_pointer_get_result *from = priv;
  size_t len = json_object_array_length(parent);
  if (parent == from->parent)
  {
    len += 1;
  }
  if (idx > len)
  {
    errno = EINVAL;
    return -1;
  }
  rc = json_object_array_insert_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}

static int json_patch_apply_move_copy(struct json_object **res, struct json_object *patch_elem, const char *path, int move, struct json_patch_error *patch_error)
{
  json_pointer_array_set_cb array_set_cb;
  struct json_pointer_get_result from;
  struct json_object *jfrom;
  const char *from_s;
  unsigned int from_s_idx = 0;
  size_t from_s_len;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "from", &jfrom))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch does not contain a 'from' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  from_s_idx = json_object_get_string(jfrom);
  from_s_len = strlen(from_s);
  if (strncmp(from_s, path, from_s_len) == 0)
  {
    if (from_s_len == strlen(path))
    {
      return 0;
    }
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Invalid attempt to move parent under a child";
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_get_internal(*res, from_s, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by from field") : ("Invalid from field");
      errno = 0;
    }
    while (0);
    return rc;
  }
  json_object_get(from.obj);
  if (!move)
  {
    array_set_cb = json_object_array_insert_idx_cb;
  }
  else
  {
    rc = __json_patch_apply_remove(&from);
    if (rc < 0)
    {
      json_object_put(from.obj);
      return rc;
    }
    array_set_cb = json_object_array_move_cb;
  }
  rc = json_pointer_set_with_array_cb(res, path, from.obj, array_set_cb, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(from.obj);
  }
  return rc;
}

int json_patch_apply(struct json_object *copy_from, struct json_object *patch, struct json_object **base, struct json_patch_error *patch_error)
{
  unsigned int patch_error_idx = 0;
  size_t ii;
  int rc = 0;
  struct json_patch_error placeholder;
  if (!(&patch_error[patch_error_idx]))
  {
    patch_error_idx = &placeholder;
  }
  patch_error->patch_failure_idx = 18446744073709551615UL;
  patch_error->errno_code = 0;
  if (((base == 0) || (((*base) == 0) && (copy_from == 0))) || (((*base) != 0) && (copy_from != 0)))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Exactly one of *base or copy_from must be non-NULL";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_is_type(patch, json_type_array))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Patch object is not of type json_type_array";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (copy_from != 0)
  {
    if (json_object_deep_copy(copy_from, base, 0) < 0)
    {
      do
      {
        patch_error->errno_code = ENOMEM;
        patch_error->errmsg = "Unable to copy copy_from using json_object_deep_copy()";
        errno = 0;
      }
      while (0);
      return -1;
    }
  }
  for (ii = 0; ii < json_object_array_length(patch); ii += 1)
  {
    struct json_object *jop;
    struct json_object *jpath;
    struct json_object *patch_elem = json_object_array_get_idx(patch, ii);
    const char *op;
    unsigned int op_idx = 0;
    const char *path;
    unsigned int path_idx = 0;
    patch_error->patch_failure_idx = ii;
    if (!json_object_object_get_ex(patch_elem, "op", &jop))
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object does not contain 'op' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    op_idx = json_object_get_string(jop);
    if (!json_object_object_get_ex(patch_elem, "path", &jpath))
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object does not contain 'path' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    path_idx = json_object_get_string(jpath);
    if (!strcmp(op, "test"))
    {
      rc = json_patch_apply_test(base, patch_elem, path, patch_error);
    }
    else
      if (!strcmp(op, "remove"))
    {
      rc = json_patch_apply_remove(base, path, patch_error);
    }
    else
      if (!strcmp(op, "add"))
    {
      rc = json_patch_apply_add_replace(base, patch_elem, path, 1, patch_error);
    }
    else
      if (!strcmp(op, "replace"))
    {
      rc = json_patch_apply_add_replace(base, patch_elem, path, 0, patch_error);
    }
    else
      if (!strcmp(op, "move"))
    {
      rc = json_patch_apply_move_copy(base, patch_elem, path, 1, patch_error);
    }
    else
      if (!strcmp(op, "copy"))
    {
      rc = json_patch_apply_move_copy(base, patch_elem, path, 0, patch_error);
    }
    else
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object has invalid 'op' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    if (rc < 0)
    {
      break;
    }
  }

  return rc;
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
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
};
int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res);
typedef int (*json_pointer_array_set_cb)(json_object *parent, size_t idx, json_object *value, void *priv);
int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv);
static int json_patch_apply_test(struct json_object **res, struct json_object *patch_elem, const char *path, struct json_patch_error *patch_error)
{
  struct json_object *value1;
  struct json_object *value2;
  if (!json_object_object_get_ex(patch_elem, "value", &value1))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (json_pointer_get(*res, path, &value2))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_equal(value1, value2))
  {
    do
    {
      patch_error->errno_code = ENOENT;
      patch_error->errmsg = "Value of element referenced by 'path' field did not match 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  return 0;
}

static int __json_patch_apply_remove(struct json_pointer_get_result *jpres)
{
  if (json_object_is_type(jpres->parent, json_type_array))
  {
    return json_object_array_del_idx(jpres->parent, jpres->index_in_parent, 1);
  }
  else
    if (jpres->parent && jpres->key_in_parent)
  {
    json_object_object_del(jpres->parent, jpres->key_in_parent);
    return 0;
  }
  else
  {
    (void) json_object_put(jpres->obj);
    jpres->obj = 0;
    return 0;
  }
}

static int json_patch_apply_remove(struct json_object **res, const char *path, struct json_patch_error *patch_error)
{
  struct json_pointer_get_result jpres;
  int rc;
  if (json_pointer_get_internal(*res, path, &jpres))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = __json_patch_apply_remove(&jpres);
  if (rc < 0)
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Unable to remove path referenced by 'path' field";
      errno = 0;
    }
    while (0);
  }
  if (jpres.parent == 0)
  {
    *res = 0;
  }
  return rc;
}

static int json_object_array_insert_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  int *add = priv;
  if (idx > json_object_array_length(parent))
  {
    errno = EINVAL;
    return -1;
  }
  if (*add)
  {
    rc = json_object_array_insert_idx(parent, idx, value);
  }
  else
    rc = json_object_array_put_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}

static int json_patch_apply_add_replace(struct json_object **res, struct json_object *patch_elem, const char *path, int add, struct json_patch_error *patch_error)
{
  struct json_object *value;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "value", &value))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if ((!add) && json_pointer_get(*res, path, 0))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_set_with_array_cb(res, path, json_object_get(value), json_object_array_insert_idx_cb, &add);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(value);
  }
  return rc;
}

static int json_object_array_move_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  struct json_pointer_get_result *from = priv;
  size_t len = json_object_array_length(parent);
  if (parent == from->parent)
  {
    len += 1;
  }
  if (idx > len)
  {
    errno = EINVAL;
    return -1;
  }
  rc = json_object_array_insert_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}

static int json_patch_apply_move_copy(struct json_object **res, struct json_object *patch_elem, const char *path, int move, struct json_patch_error *patch_error)
{
  json_pointer_array_set_cb array_set_cb;
  struct json_pointer_get_result from;
  struct json_object *jfrom;
  const char *from_s;
  unsigned int from_s_idx = 0;
  size_t from_s_len;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "from", &jfrom))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch does not contain a 'from' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  from_s_idx = json_object_get_string(jfrom);
  from_s_len = strlen(from_s);
  if (strncmp(from_s, path, from_s_len) == 0)
  {
    if (from_s_len == strlen(path))
    {
      return 0;
    }
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Invalid attempt to move parent under a child";
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_get_internal(*res, from_s, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by from field") : ("Invalid from field");
      errno = 0;
    }
    while (0);
    return rc;
  }
  json_object_get(from.obj);
  if (!move)
  {
    array_set_cb = json_object_array_insert_idx_cb;
  }
  else
  {
    rc = __json_patch_apply_remove(&from);
    if (rc < 0)
    {
      json_object_put(from.obj);
      return rc;
    }
    array_set_cb = json_object_array_move_cb;
  }
  rc = json_pointer_set_with_array_cb(res, path, from.obj, array_set_cb, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(from.obj);
  }
  return rc;
}

int json_patch_apply(struct json_object *copy_from, struct json_object *patch, struct json_object **base, struct json_patch_error *patch_error)
{
  unsigned int patch_error_idx = 0;
  size_t ii;
  int rc = 0;
  struct json_patch_error placeholder;
  if (!(&patch_error[patch_error_idx]))
  {
    patch_error_idx = &placeholder;
  }
  patch_error->patch_failure_idx = 18446744073709551615UL;
  patch_error->errno_code = 0;
  if (((base == 0) || (((*base) == 0) && (copy_from == 0))) || (((*base) != 0) && (copy_from != 0)))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Exactly one of *base or copy_from must be non-NULL";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_is_type(patch, json_type_array))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Patch object is not of type json_type_array";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (copy_from != 0)
  {
    if (json_object_deep_copy(copy_from, base, 0) < 0)
    {
      do
      {
        patch_error->errno_code = ENOMEM;
        patch_error->errmsg = "Unable to copy copy_from using json_object_deep_copy()";
        errno = 0;
      }
      while (0);
      return -1;
    }
  }
  for (ii = 0; ii < json_object_array_length(patch); ii += 1)
  {
    struct json_object *jop;
    struct json_object *jpath;
    struct json_object *patch_elem = json_object_array_get_idx(patch, ii);
    const char *op;
    unsigned int op_idx = 0;
    const char *path;
    unsigned int path_idx = 0;
    patch_error->patch_failure_idx = ii;
    if (!json_object_object_get_ex(patch_elem, "op", &jop))
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object does not contain 'op' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    op_idx = json_object_get_string(jop);
    if (!json_object_object_get_ex(patch_elem, "path", &jpath))
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object does not contain 'path' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    path_idx = json_object_get_string(jpath);
    if (!strcmp(op, "test"))
    {
      rc = json_patch_apply_test(base, patch_elem, path, patch_error);
    }
    else
      if (!strcmp(op, "remove"))
    {
      rc = json_patch_apply_remove(base, path, patch_error);
    }
    else
      if (!strcmp(op, "add"))
    {
      rc = json_patch_apply_add_replace(base, patch_elem, path, 1, patch_error);
    }
    else
      if (!strcmp(op, "replace"))
    {
      rc = json_patch_apply_add_replace(base, patch_elem, path, 0, patch_error);
    }
    else
      if (!strcmp(op, "move"))
    {
      rc = json_patch_apply_move_copy(base, patch_elem, path, 1, patch_error);
    }
    else
      if (!strcmp(op, "copy"))
    {
      rc = json_patch_apply_move_copy(base, patch_elem, path, 0, patch_error);
    }
    else
    {
      do
      {
        patch_error->errno_code = EINVAL;
        patch_error->errmsg = "Patch object has invalid 'op' field";
        errno = 0;
      }
      while (0);
      return -1;
    }
    if (rc < 0)
    {
      break;
    }
  }

  return rc;
}

