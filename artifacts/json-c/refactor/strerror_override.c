#include <config.h>
#include <errno.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_types.h>
#include <printbuf.h>
#include <stddef.h>
#include <strerror_override.c>
#include <strerror_override.h>
#include <string.h>

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
static struct 
{
  int errno_value;
  const char *errno_str;
} errno_list[] = {{EPERM, &"undef_EPERM"[6]}, {ENOENT, &"undef_ENOENT"[6]}, {ESRCH, &"undef_ESRCH"[6]}, {EINTR, &"undef_EINTR"[6]}, {EIO, &"undef_EIO"[6]}, {ENXIO, &"undef_ENXIO"[6]}, {E2BIG, &"undef_E2BIG"[6]}, {EBADF, &"undef_EBADF"[6]}, {ECHILD, &"undef_ECHILD"[6]}, {EDEADLK, &"undef_EDEADLK"[6]}, {ENOMEM, &"undef_ENOMEM"[6]}, {EACCES, &"undef_EACCES"[6]}, {EFAULT, &"undef_EFAULT"[6]}, {EBUSY, &"undef_EBUSY"[6]}, {EEXIST, &"undef_EEXIST"[6]}, {EXDEV, &"undef_EXDEV"[6]}, {ENODEV, &"undef_ENODEV"[6]}, {ENOTDIR, &"undef_ENOTDIR"[6]}, {EISDIR, &"undef_EISDIR"[6]}, {EINVAL, &"undef_EINVAL"[6]}, {ENFILE, &"undef_ENFILE"[6]}, {EMFILE, &"undef_EMFILE"[6]}, {ENOTTY, &"undef_ENOTTY"[6]}, {EFBIG, &"undef_EFBIG"[6]}, {ENOSPC, &"undef_ENOSPC"[6]}, {ESPIPE, &"undef_ESPIPE"[6]}, {EROFS, &"undef_EROFS"[6]}, {EMLINK, &"undef_EMLINK"[6]}, {EPIPE, &"undef_EPIPE"[6]}, {EDOM, &"undef_EDOM"[6]}, {ERANGE, &"undef_ERANGE"[6]}, {EAGAIN, &"undef_EAGAIN"[6]}, {0, (char *) 0}};
static int _json_c_strerror_enable = 0;
extern char *getenv(const char *name);
static char errno_buf[128] = "ERRNO=";
char *_json_c_strerror(int errno_in)
{
  int start_idx;
  char digbuf[20];
  int ii;
  int jj;
  if (!_json_c_strerror_enable)
  {
    _json_c_strerror_enable = (getenv("_JSON_C_STRERROR_ENABLE") == 0) ? (-1) : (1);
  }
  if (_json_c_strerror_enable == (-1))
  {
    return strerror(errno_in);
  }
  for (ii = 0; errno_list[ii].errno_str != ((char *) 0); ii += 1)
  {
    const char *errno_str = errno_list[ii].errno_str;
    if (errno_list[ii].errno_value != errno_in)
    {
      continue;
    }
    for (start_idx = (sizeof("ERRNO=")) - 1, jj = 0; errno_str[jj] != '\0'; jj += 1, start_idx += 1)
    {
      errno_buf[start_idx] = errno_str[jj];
    }

    errno_buf[start_idx] = '\0';
    return errno_buf;
  }

  for (ii = 0; errno_in >= 10; errno_in /= 10, ii += 1)
  {
    digbuf[ii] = "0123456789"[errno_in % 10];
  }

  digbuf[ii] = "0123456789"[errno_in % 10];
  for (start_idx = (sizeof("ERRNO=")) - 1; ii >= 0; ii -= 1, start_idx += 1)
  {
    errno_buf[start_idx] = digbuf[ii];
  }

  errno_buf[start_idx] = '\0';
  return errno_buf;
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
static struct 
{
  int errno_value;
  const char *errno_str;
} errno_list[] = {{EPERM, &"undef_EPERM"[6]}, {ENOENT, &"undef_ENOENT"[6]}, {ESRCH, &"undef_ESRCH"[6]}, {EINTR, &"undef_EINTR"[6]}, {EIO, &"undef_EIO"[6]}, {ENXIO, &"undef_ENXIO"[6]}, {E2BIG, &"undef_E2BIG"[6]}, {EBADF, &"undef_EBADF"[6]}, {ECHILD, &"undef_ECHILD"[6]}, {EDEADLK, &"undef_EDEADLK"[6]}, {ENOMEM, &"undef_ENOMEM"[6]}, {EACCES, &"undef_EACCES"[6]}, {EFAULT, &"undef_EFAULT"[6]}, {EBUSY, &"undef_EBUSY"[6]}, {EEXIST, &"undef_EEXIST"[6]}, {EXDEV, &"undef_EXDEV"[6]}, {ENODEV, &"undef_ENODEV"[6]}, {ENOTDIR, &"undef_ENOTDIR"[6]}, {EISDIR, &"undef_EISDIR"[6]}, {EINVAL, &"undef_EINVAL"[6]}, {ENFILE, &"undef_ENFILE"[6]}, {EMFILE, &"undef_EMFILE"[6]}, {ENOTTY, &"undef_ENOTTY"[6]}, {EFBIG, &"undef_EFBIG"[6]}, {ENOSPC, &"undef_ENOSPC"[6]}, {ESPIPE, &"undef_ESPIPE"[6]}, {EROFS, &"undef_EROFS"[6]}, {EMLINK, &"undef_EMLINK"[6]}, {EPIPE, &"undef_EPIPE"[6]}, {EDOM, &"undef_EDOM"[6]}, {ERANGE, &"undef_ERANGE"[6]}, {EAGAIN, &"undef_EAGAIN"[6]}, {0, (char *) 0}};
static int _json_c_strerror_enable = 0;
extern char *getenv(const char *name);
static char errno_buf[128] = "ERRNO=";
char *_json_c_strerror(int errno_in)
{
  int start_idx;
  char digbuf[20];
  int ii;
  int jj;
  if (!_json_c_strerror_enable)
  {
    _json_c_strerror_enable = (getenv("_JSON_C_STRERROR_ENABLE") == 0) ? (-1) : (1);
  }
  if (_json_c_strerror_enable == (-1))
  {
    return strerror(errno_in);
  }
  for (ii = 0; errno_list[ii].errno_str != ((char *) 0); ii += 1)
  {
    const char *errno_str = errno_list[ii].errno_str;
    if (errno_list[ii].errno_value != errno_in)
    {
      continue;
    }
    for (start_idx = (sizeof("ERRNO=")) - 1, jj = 0; errno_str[jj] != '\0'; jj += 1, start_idx += 1)
    {
      errno_buf[start_idx] = errno_str[jj];
    }

    errno_buf[start_idx] = '\0';
    return errno_buf;
  }

  for (ii = 0; errno_in >= 10; errno_in /= 10, ii += 1)
  {
    digbuf[ii] = "0123456789"[errno_in % 10];
  }

  digbuf[ii] = "0123456789"[errno_in % 10];
  for (start_idx = (sizeof("ERRNO=")) - 1; ii >= 0; ii -= 1, start_idx += 1)
  {
    errno_buf[start_idx] = digbuf[ii];
  }

  errno_buf[start_idx] = '\0';
  return errno_buf;
}

