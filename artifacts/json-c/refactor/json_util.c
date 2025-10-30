#include <config.h>
#include <debug.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_tokener.h>
#include <json_types.h>
#include <json_util.c>
#include <json_util.h>
#include <limits.h>
#include <printbuf.h>
#include <snprintf_compat.h>
#include <stat.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strerror_override.h>
#include <string.h>
#include <types.h>
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
extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
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
static int _json_object_to_fd(int fd, struct json_object *obj, int flags, const char *filename);
static char _last_err[256] = "";
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
}

void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}

struct json_object *json_object_from_fd(int fd)
{
  return json_object_from_fd_ex(fd, -1);
}

struct json_object *json_object_from_fd_ex(int fd, int in_depth)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  char buf[4096];
  ssize_t ret;
  int depth = 32;
  json_tokener *tok;
  unsigned int tok_idx = 0;
  if (!(pb_idx = printbuf_new()))
  {
    _json_c_set_last_err("json_object_from_fd_ex: printbuf_new failed\n");
    return 0;
  }
  if (in_depth != (-1))
  {
    depth = in_depth;
  }
  tok_idx = json_tokener_new_ex(depth);
  if (!(&tok[tok_idx]))
  {
    _json_c_set_last_err("json_object_from_fd_ex: unable to allocate json_tokener(depth=%d): %s\n", depth, _json_c_strerror(errno));
    printbuf_free(pb);
    return 0;
  }
  while ((ret = read(fd, buf, sizeof(buf))) > 0)
  {
    if (printbuf_memappend(pb, buf, ret) < 0)
    {
      _json_c_set_last_err("json_object_from_fd_ex: failed to printbuf_memappend after reading %d+%d bytes: %s", pb->bpos, (int) ret, _json_c_strerror(errno));
      json_tokener_free(tok);
      printbuf_free(pb);
      return 0;
    }
  }

  if (ret < 0)
  {
    _json_c_set_last_err("json_object_from_fd_ex: error reading fd %d: %s\n", fd, _json_c_strerror(errno));
    json_tokener_free(tok);
    printbuf_free(pb);
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, pb->buf, pb->bpos);
  if ((&obj[obj_idx]) == 0)
  {
    _json_c_set_last_err("json_tokener_parse_ex failed: %s\n", json_tokener_error_desc(json_tokener_get_error(tok)));
  }
  json_tokener_free(tok);
  printbuf_free(pb);
  return obj;
}

struct json_object *json_object_from_file(const char *filename)
{
  struct json_object *obj;
  unsigned int obj_idx = 0;
  int fd;
  if ((fd = open(filename, O_RDONLY)) < 0)
  {
    _json_c_set_last_err("json_object_from_file: error opening file %s: %s\n", filename, _json_c_strerror(errno));
    return 0;
  }
  obj_idx = json_object_from_fd(fd);
  close(fd);
  return obj;
}

int json_object_to_file_ext(const char *filename, struct json_object *obj, int flags)
{
  int fd;
  int ret;
  int saved_errno;
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_file_ext: object is null\n");
    return -1;
  }
  if ((fd = open(filename, (O_WRONLY | O_TRUNC) | O_CREAT, 0644)) < 0)
  {
    _json_c_set_last_err("json_object_to_file_ext: error opening file %s: %s\n", filename, _json_c_strerror(errno));
    return -1;
  }
  ret = _json_object_to_fd(fd, obj, flags, filename);
  saved_errno = errno;
  close(fd);
  errno = saved_errno;
  return ret;
}

int json_object_to_fd(int fd, struct json_object *obj, int flags)
{
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_fd: object is null\n");
    return -1;
  }
  return _json_object_to_fd(fd, obj, flags, 0);
}

static int _json_object_to_fd(int fd, struct json_object *obj, int flags, const char *filename)
{
  unsigned int filename_idx = 0;
  ssize_t ret;
  const char *json_str;
  unsigned int json_str_idx = 0;
  size_t wpos;
  size_t wsize;
  filename_idx = (filename_idx) ? (filename_idx) : ("(fd)");
  if (!(json_str_idx = json_object_to_json_string_ext(obj, flags)))
  {
    return -1;
  }
  wsize = strlen(json_str);
  wpos = 0;
  while (wpos < wsize)
  {
    if ((ret = write(fd, (&json_str[json_str_idx]) + wpos, wsize - wpos)) < 0)
    {
      _json_c_set_last_err("json_object_to_fd: error writing file %s: %s\n", filename, _json_c_strerror(errno));
      return -1;
    }
    wpos += (size_t) ret;
  }

  return 0;
}

int json_object_to_file(const char *filename, struct json_object *obj)
{
  return json_object_to_file_ext(filename, obj, 0);
}

int json_parse_double(const char *buf, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  return (end == buf) ? (1) : (0);
}

int json_parse_int64(const char *buf, int64_t *retval)
{
  char *end = 0;
  int64_t val;
  errno = 0;
  val = strtoll(buf, &end, 10);
  if (end != buf)
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == buf))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}

int json_parse_uint64(const char *buf, uint64_t *retval)
{
  unsigned int buf_idx = 0;
  char *end = 0;
  uint64_t val;
  errno = 0;
  while (buf[buf_idx] == ' ')
  {
    buf_idx += 1;
  }

  if (buf[buf_idx] == '-')
  {
    return 1;
  }
  val = strtoull(buf, &end, 10);
  if (end != (&buf[buf_idx]))
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == (&buf[buf_idx])))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}

static const char *json_type_name[] = {"null", "boolean", "double", "int", "object", "array", "string"};
const char *json_type_to_name(enum json_type o_type)
{
  int o_type_int = (int) o_type;
  if ((o_type_int < 0) || (o_type_int >= ((int) ((sizeof(json_type_name)) / (sizeof(json_type_name[0]))))))
  {
    _json_c_set_last_err("json_type_to_name: type %d is out of range [0,%u]\n", o_type, (unsigned) ((sizeof(json_type_name)) / (sizeof(json_type_name[0]))));
    return 0;
  }
  return json_type_name[o_type];
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
extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
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
static int _json_object_to_fd(int fd, struct json_object *obj, int flags, const char *filename);
static char _last_err[256] = "";
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
}

void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}

struct json_object *json_object_from_fd(int fd)
{
  return json_object_from_fd_ex(fd, -1);
}

struct json_object *json_object_from_fd_ex(int fd, int in_depth)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  char buf[4096];
  ssize_t ret;
  int depth = 32;
  json_tokener *tok;
  unsigned int tok_idx = 0;
  if (!(pb_idx = printbuf_new()))
  {
    _json_c_set_last_err("json_object_from_fd_ex: printbuf_new failed\n");
    return 0;
  }
  if (in_depth != (-1))
  {
    depth = in_depth;
  }
  tok_idx = json_tokener_new_ex(depth);
  if (!(&tok[tok_idx]))
  {
    _json_c_set_last_err("json_object_from_fd_ex: unable to allocate json_tokener(depth=%d): %s\n", depth, _json_c_strerror(errno));
    printbuf_free(pb);
    return 0;
  }
  while ((ret = read(fd, buf, sizeof(buf))) > 0)
  {
    if (printbuf_memappend(pb, buf, ret) < 0)
    {
      _json_c_set_last_err("json_object_from_fd_ex: failed to printbuf_memappend after reading %d+%d bytes: %s", pb->bpos, (int) ret, _json_c_strerror(errno));
      json_tokener_free(tok);
      printbuf_free(pb);
      return 0;
    }
  }

  if (ret < 0)
  {
    _json_c_set_last_err("json_object_from_fd_ex: error reading fd %d: %s\n", fd, _json_c_strerror(errno));
    json_tokener_free(tok);
    printbuf_free(pb);
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, pb->buf, pb->bpos);
  if ((&obj[obj_idx]) == 0)
  {
    _json_c_set_last_err("json_tokener_parse_ex failed: %s\n", json_tokener_error_desc(json_tokener_get_error(tok)));
  }
  json_tokener_free(tok);
  printbuf_free(pb);
  return obj;
}

struct json_object *json_object_from_file(const char *filename)
{
  struct json_object *obj;
  unsigned int obj_idx = 0;
  int fd;
  if ((fd = open(filename, O_RDONLY)) < 0)
  {
    _json_c_set_last_err("json_object_from_file: error opening file %s: %s\n", filename, _json_c_strerror(errno));
    return 0;
  }
  obj_idx = json_object_from_fd(fd);
  close(fd);
  return obj;
}

int json_object_to_file_ext(const char *filename, struct json_object *obj, int flags)
{
  int fd;
  int ret;
  int saved_errno;
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_file_ext: object is null\n");
    return -1;
  }
  if ((fd = open(filename, (O_WRONLY | O_TRUNC) | O_CREAT, 0644)) < 0)
  {
    _json_c_set_last_err("json_object_to_file_ext: error opening file %s: %s\n", filename, _json_c_strerror(errno));
    return -1;
  }
  ret = _json_object_to_fd(fd, obj, flags, filename);
  saved_errno = errno;
  close(fd);
  errno = saved_errno;
  return ret;
}

int json_object_to_fd(int fd, struct json_object *obj, int flags)
{
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_fd: object is null\n");
    return -1;
  }
  return _json_object_to_fd(fd, obj, flags, 0);
}

static int _json_object_to_fd(int fd, struct json_object *obj, int flags, const char *filename)
{
  unsigned int filename_idx = 0;
  ssize_t ret;
  const char *json_str;
  unsigned int json_str_idx = 0;
  size_t wpos;
  size_t wsize;
  filename_idx = (filename_idx) ? (filename_idx) : ("(fd)");
  if (!(json_str_idx = json_object_to_json_string_ext(obj, flags)))
  {
    return -1;
  }
  wsize = strlen(json_str);
  wpos = 0;
  while (wpos < wsize)
  {
    if ((ret = write(fd, (&json_str[json_str_idx]) + wpos, wsize - wpos)) < 0)
    {
      _json_c_set_last_err("json_object_to_fd: error writing file %s: %s\n", filename, _json_c_strerror(errno));
      return -1;
    }
    wpos += (size_t) ret;
  }

  return 0;
}

int json_object_to_file(const char *filename, struct json_object *obj)
{
  return json_object_to_file_ext(filename, obj, 0);
}

int json_parse_double(const char *buf, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  return (end == buf) ? (1) : (0);
}

int json_parse_int64(const char *buf, int64_t *retval)
{
  char *end = 0;
  int64_t val;
  errno = 0;
  val = strtoll(buf, &end, 10);
  if (end != buf)
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == buf))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}

int json_parse_uint64(const char *buf, uint64_t *retval)
{
  unsigned int buf_idx = 0;
  char *end = 0;
  uint64_t val;
  errno = 0;
  while (buf[buf_idx] == ' ')
  {
    buf_idx += 1;
  }

  if (buf[buf_idx] == '-')
  {
    return 1;
  }
  val = strtoull(buf, &end, 10);
  if (end != (&buf[buf_idx]))
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == (&buf[buf_idx])))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}

static const char *json_type_name[] = {"null", "boolean", "double", "int", "object", "array", "string"};
const char *json_type_to_name(enum json_type o_type)
{
  int o_type_int = (int) o_type;
  if ((o_type_int < 0) || (o_type_int >= ((int) ((sizeof(json_type_name)) / (sizeof(json_type_name[0]))))))
  {
    _json_c_set_last_err("json_type_to_name: type %d is out of range [0,%u]\n", o_type, (unsigned) ((sizeof(json_type_name)) / (sizeof(json_type_name[0]))));
    return 0;
  }
  return json_type_name[o_type];
}

