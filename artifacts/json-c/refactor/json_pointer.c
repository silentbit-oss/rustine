#include <config.h>
#include <errno.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_object_private.h>
#include <json_pointer.c>
#include <json_pointer.h>
#include <json_pointer_private.h>
#include <json_types.h>
#include <printbuf.h>
#include <snprintf_compat.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strdup_compat.h>
#include <strerror_override.h>
#include <string.h>
#include <unistd.h>
#include <vasprintf_compat.h>

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
extern int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res);
extern int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...);
extern int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value);
extern int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...);
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
static void string_replace_all_occurrences_with_char(char *s, const char *occur, char repl_char)
{
  size_t slen = strlen(s);
  size_t skip = strlen(occur) - 1;
  char *p = s;
  unsigned int p_idx = 0;
  while (p_idx = strstr(p_idx, occur))
  {
    p[p_idx] = repl_char;
    p_idx += 1;
    slen -= skip;
    memmove(p, (&p[p_idx]) + skip, (slen - ((&p[p_idx]) - s)) + 1);
  }

}

static int is_valid_index(const char *path, size_t *idx)
{
  size_t i;
  size_t len = strlen(path);
  if (len == 1)
  {
    if ((path[0] >= '0') && (path[0] <= '9'))
    {
      *idx = path[0] - '0';
      return 1;
    }
    errno = EINVAL;
    return 0;
  }
  if (path[0] == '0')
  {
    errno = EINVAL;
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!((path[i] >= '0') && (path[i] <= '9')))
    {
      errno = EINVAL;
      return 0;
    }
  }

  *idx = strtoull(path, 0, 10);
  return 1;
}

static int json_pointer_get_single_path(struct json_object *obj, char *path, struct json_object **value, size_t *idx)
{
  unsigned int obj_idx = 0;
  if (json_object_is_type(obj, json_type_array))
  {
    if (!is_valid_index(path, idx))
    {
      return -1;
    }
    if ((*idx) >= json_object_array_length(obj))
    {
      errno = ENOENT;
      return -1;
    }
    obj_idx = json_object_array_get_idx(obj_idx, *idx);
    if (obj)
    {
      if (value)
      {
        *value = &obj[obj_idx];
      }
      return 0;
    }
    errno = ENOENT;
    return -1;
  }
  string_replace_all_occurrences_with_char(path, "~1", '/');
  string_replace_all_occurrences_with_char(path, "~0", '~');
  if (!json_object_object_get_ex(obj, path, value))
  {
    errno = ENOENT;
    return -1;
  }
  return 0;
}

static int json_object_array_put_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  return json_object_array_put_idx(parent, idx, value);
}

static int json_pointer_set_single_path(struct json_object *parent, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  if (json_object_is_type(parent, json_type_array))
  {
    size_t idx;
    if ((path[0] == '-') && (path[1] == '\0'))
    {
      return json_object_array_add(parent, value);
    }
    if (!is_valid_index(path, &idx))
    {
      return -1;
    }
    return array_set_cb(parent, idx, value, priv);
  }
  if (json_object_is_type(parent, json_type_object))
  {
    return json_object_object_add(parent, path, value);
  }
  errno = ENOENT;
  return -1;
}

static int json_pointer_result_get_recursive(struct json_object *obj, char *path, struct json_pointer_get_result *res)
{
  unsigned int path_idx = 0;
  struct json_object *parent_obj = obj;
  size_t idx = 0;
  char *endp;
  unsigned int endp_idx = 0;
  int rc;
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  path_idx += 1;
  endp_idx = strchr(path, '/');
  if (endp)
  {
    endp[endp_idx] = '\0';
  }
  if (rc = json_pointer_get_single_path(obj, path, &obj, &idx))
  {
    return rc;
  }
  if (endp)
  {
    endp[endp_idx] = '/';
    return json_pointer_result_get_recursive(obj, endp, res);
  }
  if (res)
  {
    res->parent = parent_obj;
    res->obj = obj;
    if (json_object_is_type(res->parent, json_type_array))
    {
      res->index_in_parent = idx;
    }
    else
      res->key_in_parent = &path[path_idx];
  }
  return 0;
}

static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
}

int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res)
{
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  int rc;
  if ((!obj) || (!path))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0] == '\0')
  {
    res->parent = 0;
    res->obj = obj;
    res->key_in_parent = 0;
    res->index_in_parent = UINT32_MAX;
    return 0;
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  rc = json_pointer_result_get_recursive(obj, path_copy, res);
  if (((rc == 0) && json_object_is_type(res->parent, json_type_object)) && res->key_in_parent)
  {
    res->key_in_parent = path + (res->key_in_parent - (&path_copy[path_copy_idx]));
  }
  free(path_copy);
  return rc;
}

int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res)
{
  struct json_pointer_get_result jpres;
  int rc;
  rc = json_pointer_get_internal(obj, path, &jpres);
  if (rc)
  {
    return rc;
  }
  if (res)
  {
    *res = jpres.obj;
  }
  return 0;
}

int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...)
{
  char *path_copy = 0;
  int rc = 0;
  va_list args;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    if (res)
    {
      *res = obj;
    }
    goto out;
  }
  rc = json_pointer_object_get_recursive(obj, path_copy, res);
  out:
  free(path_copy);

  return rc;
}

int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  unsigned int path_idx = 0;
  const char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  struct json_object *set = 0;
  int rc;
  if ((!obj) || (!(&path[path_idx])))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0 + path_idx] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    return 0;
  }
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  if ((endp_idx = strrchr(path, '/')) == (&path[path_idx]))
  {
    path_idx += 1;
    return json_pointer_set_single_path(*obj, path, value, array_set_cb, priv);
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  path_copy[((&endp[endp_idx]) - (&path[path_idx])) + path_copy_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &set);
  free(path_copy);
  if (rc)
  {
    return rc;
  }
  endp_idx += 1;
  return json_pointer_set_single_path(set, endp, value, array_set_cb, priv);
}

int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value)
{
  return json_pointer_set_with_array_cb(obj, path, value, json_object_array_put_idx_cb, 0);
}

int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...)
{
  char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  struct json_object *set = 0;
  unsigned int set_idx = 0;
  va_list args;
  int rc = 0;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    goto out;
  }
  if (path_copy[0] != '/')
  {
    errno = EINVAL;
    rc = -1;
    goto out;
  }
  if ((endp_idx = strrchr(path_copy, '/')) == path_copy)
  {
    set_idx = *obj;
    goto set_single_path;
  }
  endp[endp_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &(&set[set_idx]));
  if (rc)
  {
    goto out;
  }
  set_single_path:
  (&endp[endp_idx])++;

  endp_idx += 1;
  rc = json_pointer_set_single_path(set, endp, value, json_object_array_put_idx_cb, 0);
  out:
  free(path_copy);

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
extern char *_json_c_strerror(int errno_in);
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
extern int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res);
extern int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...);
extern int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value);
extern int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...);
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
static void string_replace_all_occurrences_with_char(char *s, const char *occur, char repl_char)
{
  size_t slen = strlen(s);
  size_t skip = strlen(occur) - 1;
  char *p = s;
  unsigned int p_idx = 0;
  while (p_idx = strstr(p_idx, occur))
  {
    p[p_idx] = repl_char;
    p_idx += 1;
    slen -= skip;
    memmove(p, (&p[p_idx]) + skip, (slen - ((&p[p_idx]) - s)) + 1);
  }

}

static int is_valid_index(const char *path, size_t *idx)
{
  size_t i;
  size_t len = strlen(path);
  if (len == 1)
  {
    if ((path[0] >= '0') && (path[0] <= '9'))
    {
      *idx = path[0] - '0';
      return 1;
    }
    errno = EINVAL;
    return 0;
  }
  if (path[0] == '0')
  {
    errno = EINVAL;
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!((path[i] >= '0') && (path[i] <= '9')))
    {
      errno = EINVAL;
      return 0;
    }
  }

  *idx = strtoull(path, 0, 10);
  return 1;
}

static int json_pointer_get_single_path(struct json_object *obj, char *path, struct json_object **value, size_t *idx)
{
  unsigned int obj_idx = 0;
  if (json_object_is_type(obj, json_type_array))
  {
    if (!is_valid_index(path, idx))
    {
      return -1;
    }
    if ((*idx) >= json_object_array_length(obj))
    {
      errno = ENOENT;
      return -1;
    }
    obj_idx = json_object_array_get_idx(obj_idx, *idx);
    if (obj)
    {
      if (value)
      {
        *value = &obj[obj_idx];
      }
      return 0;
    }
    errno = ENOENT;
    return -1;
  }
  string_replace_all_occurrences_with_char(path, "~1", '/');
  string_replace_all_occurrences_with_char(path, "~0", '~');
  if (!json_object_object_get_ex(obj, path, value))
  {
    errno = ENOENT;
    return -1;
  }
  return 0;
}

static int json_object_array_put_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  return json_object_array_put_idx(parent, idx, value);
}

static int json_pointer_set_single_path(struct json_object *parent, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  if (json_object_is_type(parent, json_type_array))
  {
    size_t idx;
    if ((path[0] == '-') && (path[1] == '\0'))
    {
      return json_object_array_add(parent, value);
    }
    if (!is_valid_index(path, &idx))
    {
      return -1;
    }
    return array_set_cb(parent, idx, value, priv);
  }
  if (json_object_is_type(parent, json_type_object))
  {
    return json_object_object_add(parent, path, value);
  }
  errno = ENOENT;
  return -1;
}

static int json_pointer_result_get_recursive(struct json_object *obj, char *path, struct json_pointer_get_result *res)
{
  unsigned int path_idx = 0;
  struct json_object *parent_obj = obj;
  size_t idx = 0;
  char *endp;
  unsigned int endp_idx = 0;
  int rc;
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  path_idx += 1;
  endp_idx = strchr(path, '/');
  if (endp)
  {
    endp[endp_idx] = '\0';
  }
  if (rc = json_pointer_get_single_path(obj, path, &obj, &idx))
  {
    return rc;
  }
  if (endp)
  {
    endp[endp_idx] = '/';
    return json_pointer_result_get_recursive(obj, endp, res);
  }
  if (res)
  {
    res->parent = parent_obj;
    res->obj = obj;
    if (json_object_is_type(res->parent, json_type_array))
    {
      res->index_in_parent = idx;
    }
    else
      res->key_in_parent = &path[path_idx];
  }
  return 0;
}

static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
}

int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res)
{
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  int rc;
  if ((!obj) || (!path))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0] == '\0')
  {
    res->parent = 0;
    res->obj = obj;
    res->key_in_parent = 0;
    res->index_in_parent = UINT32_MAX;
    return 0;
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  rc = json_pointer_result_get_recursive(obj, path_copy, res);
  if (((rc == 0) && json_object_is_type(res->parent, json_type_object)) && res->key_in_parent)
  {
    res->key_in_parent = path + (res->key_in_parent - (&path_copy[path_copy_idx]));
  }
  free(path_copy);
  return rc;
}

int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res)
{
  struct json_pointer_get_result jpres;
  int rc;
  rc = json_pointer_get_internal(obj, path, &jpres);
  if (rc)
  {
    return rc;
  }
  if (res)
  {
    *res = jpres.obj;
  }
  return 0;
}

int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...)
{
  char *path_copy = 0;
  int rc = 0;
  va_list args;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    if (res)
    {
      *res = obj;
    }
    goto out;
  }
  rc = json_pointer_object_get_recursive(obj, path_copy, res);
  out:
  free(path_copy);

  return rc;
}

int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  unsigned int path_idx = 0;
  const char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  struct json_object *set = 0;
  int rc;
  if ((!obj) || (!(&path[path_idx])))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0 + path_idx] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    return 0;
  }
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  if ((endp_idx = strrchr(path, '/')) == (&path[path_idx]))
  {
    path_idx += 1;
    return json_pointer_set_single_path(*obj, path, value, array_set_cb, priv);
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  path_copy[((&endp[endp_idx]) - (&path[path_idx])) + path_copy_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &set);
  free(path_copy);
  if (rc)
  {
    return rc;
  }
  endp_idx += 1;
  return json_pointer_set_single_path(set, endp, value, array_set_cb, priv);
}

int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value)
{
  return json_pointer_set_with_array_cb(obj, path, value, json_object_array_put_idx_cb, 0);
}

int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...)
{
  char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  struct json_object *set = 0;
  unsigned int set_idx = 0;
  va_list args;
  int rc = 0;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    goto out;
  }
  if (path_copy[0] != '/')
  {
    errno = EINVAL;
    rc = -1;
    goto out;
  }
  if ((endp_idx = strrchr(path_copy, '/')) == path_copy)
  {
    set_idx = *obj;
    goto set_single_path;
  }
  endp[endp_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &(&set[set_idx]));
  if (rc)
  {
    goto out;
  }
  set_single_path:
  (&endp[endp_idx])++;

  endp_idx += 1;
  rc = json_pointer_set_single_path(set, endp, value, json_object_array_put_idx_cb, 0);
  out:
  free(path_copy);

  return rc;
}

