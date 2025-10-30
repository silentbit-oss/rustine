#include <assert.h>
#include <config.h>
#include <debug.h>
#include <errno.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_object_private.h>
#include <json_tokener.c>
#include <json_tokener.h>
#include <json_types.h>
#include <json_util.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <math_compat.h>
#include <printbuf.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <strdup_compat.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
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
inline static int is_ws_char(char c)
{
  return (((c == ' ') || (c == '\t')) || (c == '\n')) || (c == '\r');
}

inline static int is_hex_char(char c)
{
  return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) || ((c >= 'a') && (c <= 'f'));
}

static const char json_null_str[] = "null";
static const int json_null_str_len = (sizeof(json_null_str)) - 1;
static const char json_inf_str[] = "Infinity";
static const char json_inf_str_invert[] = "iNFINITY";
static const unsigned int json_inf_str_len = (sizeof(json_inf_str)) - 1;
static const char json_nan_str[] = "NaN";
static const int json_nan_str_len = (sizeof(json_nan_str)) - 1;
static const char json_true_str[] = "true";
static const int json_true_str_len = (sizeof(json_true_str)) - 1;
static const char json_false_str[] = "false";
static const int json_false_str_len = (sizeof(json_false_str)) - 1;
static const char *json_tokener_errors[] = {"success", "continue", "nesting too deep", "unexpected end of data", "unexpected character", "null expected", "boolean expected", "number expected", "array value separator ',' expected", "quoted object property name expected", "object property name separator ':' expected", "object value separator ',' expected", "invalid string sequence", "expected comment", "invalid utf-8 string", "buffer size overflow", "out of memory"};
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes);
static int json_tokener_parse_double(const char *buf, int len, double *retval);
const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
  int jerr_int = (int) jerr;
  if ((jerr_int < 0) || (jerr_int >= ((int) ((sizeof(json_tokener_errors)) / (sizeof(json_tokener_errors[0]))))))
  {
    return "Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()";
  }
  return json_tokener_errors[jerr];
}

enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
}

static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD};
struct json_tokener *json_tokener_new_ex(int depth)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  if (depth < 1)
  {
    return 0;
  }
  tok_idx = (struct json_tokener *) calloc(1, sizeof(struct json_tokener));
  if (!(&tok[tok_idx]))
  {
    return 0;
  }
  tok->stack = (struct json_tokener_srec *) calloc(depth, sizeof(struct json_tokener_srec));
  if (!tok->stack)
  {
    free(tok);
    return 0;
  }
  tok->pb = printbuf_new();
  if (!tok->pb)
  {
    free(tok->stack);
    free(tok);
    return 0;
  }
  tok->max_depth = depth;
  json_tokener_reset(tok);
  return tok;
}

struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}

void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}

static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}

void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}

struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
}

struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  tok_idx = json_tokener_new();
  if (!(&tok[tok_idx]))
  {
    *error = json_tokener_error_memory;
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, str, -1);
  *error = tok->err;
  if (tok->err != json_tokener_success)
  {
    if ((&obj[obj_idx]) != 0)
    {
      json_object_put(obj);
    }
    obj_idx = 0;
  }
  json_tokener_free(tok);
  return obj;
}

struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    redo_char:
    switch (tok->stack[tok->depth].state)
    {
      case json_tokener_state_eatws:
        while (is_ws_char(c))
      {
        if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
        {
          goto out;
        }
      }

        if ((c == '/') && (!(tok->flags & 0x01)))
      {
        printbuf_reset(tok->pb);
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->stack[tok->depth].state = json_tokener_state_comment_start;
      }
      else
      {
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
        goto redo_char;
      }
        break;

      case json_tokener_state_start:
        switch (c)
      {
        case '{':
          tok->stack[tok->depth].state = json_tokener_state_eatws;
          tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start;
          tok->stack[tok->depth].current = json_object_new_object();
          if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
          break;

        case '[':
          tok->stack[tok->depth].state = json_tokener_state_eatws;
          tok->stack[tok->depth].saved_state = json_tokener_state_array;
          tok->stack[tok->depth].current = json_object_new_array();
          if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
          break;

        case 'I':

        case 'i':
          tok->stack[tok->depth].state = json_tokener_state_inf;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case 'N':

        case 'n':
          tok->stack[tok->depth].state = json_tokener_state_null;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case '\'':
          if (tok->flags & 0x01)
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }

        case '"':
          tok->stack[tok->depth].state = json_tokener_state_string;
          printbuf_reset(tok->pb);
          tok->quote_char = c;
          break;

        case 'T':

        case 't':

        case 'F':

        case 'f':
          tok->stack[tok->depth].state = json_tokener_state_boolean;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case '0':

        case '1':

        case '2':

        case '3':

        case '4':

        case '5':

        case '6':

        case '7':

        case '8':

        case '9':

        case '-':
          tok->stack[tok->depth].state = json_tokener_state_number;
          printbuf_reset(tok->pb);
          tok->is_double = 0;
          goto redo_char;

        default:
          tok->err = json_tokener_error_parse_unexpected;
          goto out;

      }

        break;

      case json_tokener_state_finish:
        if (tok->depth == 0)
      {
        goto out;
      }
        obj_idx = json_object_get(tok->stack[tok->depth].current);
        json_tokener_reset_level(tok, tok->depth);
        tok->depth -= 1;
        goto redo_char;

      case json_tokener_state_inf:
      {
        int is_negative = 0;
        while (tok->st_pos < ((int) json_inf_str_len))
        {
          char inf_char = str[str_idx];
          if ((inf_char != json_inf_str[tok->st_pos]) && ((tok->flags & 0x01) || (inf_char != json_inf_str_invert[tok->st_pos])))
          {
            tok->err = json_tokener_error_parse_unexpected;
            goto out;
          }
          tok->st_pos += 1;
          str_idx += 1;
          (void) ((++(&str[str_idx]), tok->char_offset++, c));
          if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
          {
            goto out;
          }
        }

        if ((tok->pb->bpos > 0) && ((*tok->pb->buf) == '-'))
        {
          is_negative = 1;
        }
        tok->stack[tok->depth].current = json_object_new_double((is_negative) ? (-INFINITY) : (INFINITY));
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
        break;

      case json_tokener_state_null:
      {
        int size;
        int size_nan;
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        size = ((tok->st_pos + 1) < json_null_str_len) ? (tok->st_pos + 1) : (json_null_str_len);
        size_nan = ((tok->st_pos + 1) < json_nan_str_len) ? (tok->st_pos + 1) : (json_nan_str_len);
        if (((!(tok->flags & 0x01)) && (strncasecmp(json_null_str, tok->pb->buf, size) == 0)) || (strncmp(json_null_str, tok->pb->buf, size) == 0))
        {
          if (tok->st_pos == json_null_str_len)
          {
            tok->stack[tok->depth].current = 0;
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
          if (((!(tok->flags & 0x01)) && (strncasecmp(json_nan_str, tok->pb->buf, size_nan) == 0)) || (strncmp(json_nan_str, tok->pb->buf, size_nan) == 0))
        {
          if (tok->st_pos == json_nan_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_double(nan(""));
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_null;
          goto out;
        }
        tok->st_pos += 1;
      }
        break;

      case json_tokener_state_comment_start:
        if (c == '*')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      else
        if (c == '/')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment_eol;
      }
      else
      {
        tok->err = json_tokener_error_parse_comment;
        goto out;
      }
        do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
        break;

      case json_tokener_state_comment:
      {
        const char *case_start = str;
        while (c != '*')
        {
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        do
        {
          if (printbuf_memappend(tok->pb, case_start, (1 + (&str[str_idx])) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->stack[tok->depth].state = json_tokener_state_comment_end;
      }
        break;

      case json_tokener_state_comment_eol:
      {
        const char *case_start = str;
        while (c != '\n')
        {
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
        break;

      case json_tokener_state_comment_end:
        do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
        if (c == '/')
      {
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
        break;

      case json_tokener_state_string:
      {
        const char *case_start = str;
        while (1)
        {
          if (c == tok->quote_char)
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].current = json_object_new_string_len(tok->pb->buf, tok->pb->bpos);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            break;
          }
          else
            if (c == '\\')
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].saved_state = json_tokener_state_string;
            tok->stack[tok->depth].state = json_tokener_state_string_escape;
            break;
          }
          else
            if ((tok->flags & 0x01) && (((unsigned char) c) <= 0x1f))
          {
            tok->err = json_tokener_error_parse_string;
            goto out;
          }
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

      }
        break;

      case json_tokener_state_string_escape:
        switch (c)
      {
        case '"':

        case '\\':

        case '/':
          do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
          tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
          break;

        case 'b':

        case 'n':

        case 'r':

        case 't':

        case 'f':
          if (c == 'b')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\b", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'n')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\n", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'r')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\r", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 't')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\t", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'f')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\f", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
          tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
          break;

        case 'u':
          tok->ucs_char = 0;
          tok->st_pos = 0;
          tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
          break;

        default:
          tok->err = json_tokener_error_parse_string;
          goto out;

      }

        break;

      case json_tokener_state_escape_unicode:
      {
        while (1)
        {
          if ((!c) || (!is_hex_char(c)))
          {
            tok->err = json_tokener_error_parse_string;
            goto out;
          }
          tok->ucs_char |= ((unsigned int) ((c <= '9') ? (c - '0') : ((c & 7) + 9))) << ((3 - tok->st_pos) * 4);
          tok->st_pos += 1;
          if (tok->st_pos >= 4)
          {
            break;
          }
          str_idx += 1;
          (void) ((++(&str[str_idx]), tok->char_offset++, c));
          if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
          {
            goto out;
          }
        }

        tok->st_pos = 0;
        if (tok->high_surrogate)
        {
          if ((tok->ucs_char & 0xFC00) == 0xDC00)
          {
            tok->ucs_char = (((tok->high_surrogate & 0x3FF) << 10) + (tok->ucs_char & 0x3FF)) + 0x10000;
          }
          else
          {
            do
            {
              if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
          }
          tok->high_surrogate = 0;
        }
        if (tok->ucs_char < 0x80)
        {
          unsigned char unescaped_utf[1];
          unescaped_utf[0] = tok->ucs_char;
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x800)
        {
          unsigned char unescaped_utf[2];
          unescaped_utf[0] = 0xc0 | (tok->ucs_char >> 6);
          unescaped_utf[1] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 2) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if ((tok->ucs_char & 0xFC00) == 0xD800)
        {
          tok->high_surrogate = tok->ucs_char;
          tok->ucs_char = 0;
          tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_escape;
          break;
        }
        else
          if ((tok->ucs_char & 0xFC00) == 0xDC00)
        {
          do
          {
            if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x10000)
        {
          unsigned char unescaped_utf[3];
          unescaped_utf[0] = 0xe0 | (tok->ucs_char >> 12);
          unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
          unescaped_utf[2] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x110000)
        {
          unsigned char unescaped_utf[4];
          unescaped_utf[0] = 0xf0 | ((tok->ucs_char >> 18) & 0x07);
          unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 12) & 0x3f);
          unescaped_utf[2] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
          unescaped_utf[3] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 4) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
        {
          do
          {
            if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
      }
        break;

      case json_tokener_state_escape_unicode_need_escape:
        if ((!c) || (c != '\\'))
      {
        do
        {
          if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->high_surrogate = 0;
        tok->ucs_char = 0;
        tok->st_pos = 0;
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
        goto redo_char;
      }
        tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_u;
        break;

      case json_tokener_state_escape_unicode_need_u:
        if ((!c) || (c != 'u'))
      {
        do
        {
          if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->high_surrogate = 0;
        tok->ucs_char = 0;
        tok->st_pos = 0;
        tok->stack[tok->depth].state = json_tokener_state_string_escape;
        goto redo_char;
      }
        tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
        break;

      case json_tokener_state_boolean:
      {
        int size1;
        int size2;
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        size1 = ((tok->st_pos + 1) < json_true_str_len) ? (tok->st_pos + 1) : (json_true_str_len);
        size2 = ((tok->st_pos + 1) < json_false_str_len) ? (tok->st_pos + 1) : (json_false_str_len);
        if (((!(tok->flags & 0x01)) && (strncasecmp(json_true_str, tok->pb->buf, size1) == 0)) || (strncmp(json_true_str, tok->pb->buf, size1) == 0))
        {
          if (tok->st_pos == json_true_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_boolean(1);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
          if (((!(tok->flags & 0x01)) && (strncasecmp(json_false_str, tok->pb->buf, size2) == 0)) || (strncmp(json_false_str, tok->pb->buf, size2) == 0))
        {
          if (tok->st_pos == json_false_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_boolean(0);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_boolean;
          goto out;
        }
        tok->st_pos += 1;
      }
        break;

      case json_tokener_state_number:
      {
        const char *case_start = str;
        int case_len = 0;
        int is_exponent = 0;
        int neg_sign_ok = 1;
        int pos_sign_ok = 0;
        if (tok->pb->bpos > 0)
        {
          char *e_loc = strchr(tok->pb->buf, 'e');
          unsigned int e_loc_idx = 0;
          if (!(&e_loc[e_loc_idx]))
          {
            e_loc_idx = strchr(tok->pb->buf, 'E');
          }
          if (e_loc)
          {
            char *last_saved_char = &tok->pb->buf[tok->pb->bpos - 1];
            is_exponent = 1;
            pos_sign_ok = (neg_sign_ok = 1);
            if ((&e_loc[e_loc_idx]) != last_saved_char)
            {
              neg_sign_ok = 0;
              pos_sign_ok = 0;
            }
          }
        }
        while (c && ((((((c >= '0') && (c <= '9')) || ((!is_exponent) && ((c == 'e') || (c == 'E')))) || (neg_sign_ok && (c == '-'))) || (pos_sign_ok && (c == '+'))) || ((!tok->is_double) && (c == '.'))))
        {
          pos_sign_ok = (neg_sign_ok = 0);
          case_len += 1;
          switch (c)
          {
            case '.':
              tok->is_double = 1;
              pos_sign_ok = 1;
              neg_sign_ok = 1;
              break;

            case 'e':

            case 'E':
              is_exponent = 1;
              tok->is_double = 1;
              pos_sign_ok = (neg_sign_ok = 1);
              break;

            default:
              break;

          }

          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        if ((((((((tok->depth > 0) && (c != ',')) && (c != ']')) && (c != '}')) && (c != '/')) && (c != 'I')) && (c != 'i')) && (!is_ws_char(c)))
        {
          tok->err = json_tokener_error_parse_number;
          goto out;
        }
        if (case_len > 0)
        {
          do
          {
            if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        if (((tok->pb->buf[0] == '-') && (case_len <= 1)) && ((c == 'i') || (c == 'I')))
        {
          tok->stack[tok->depth].state = json_tokener_state_inf;
          tok->st_pos = 0;
          goto redo_char;
        }
        if (tok->is_double && (!(tok->flags & 0x01)))
        {
          while (tok->pb->bpos > 1)
          {
            char last_char = tok->pb->buf[tok->pb->bpos - 1];
            if ((((last_char != 'e') && (last_char != 'E')) && (last_char != '-')) && (last_char != '+'))
            {
              break;
            }
            tok->pb->buf[tok->pb->bpos - 1] = '\0';
            tok->pb->bpos -= 1;
          }

        }
      }
      {
        int64_t num64;
        uint64_t numuint64;
        double numd;
        if (((!tok->is_double) && (tok->pb->buf[0] == '-')) && (json_parse_int64(tok->pb->buf, &num64) == 0))
        {
          if ((errno == ERANGE) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          tok->stack[tok->depth].current = json_object_new_int64(num64);
          if (tok->stack[tok->depth].current == 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        else
          if (((!tok->is_double) && (tok->pb->buf[0] != '-')) && (json_parse_uint64(tok->pb->buf, &numuint64) == 0))
        {
          if ((errno == ERANGE) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          if ((numuint64 && (tok->pb->buf[0] == '0')) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          if (numuint64 <= INT64_MAX)
          {
            num64 = (uint64_t) numuint64;
            tok->stack[tok->depth].current = json_object_new_int64(num64);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          else
          {
            tok->stack[tok->depth].current = json_object_new_uint64(numuint64);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
        }
        else
          if (tok->is_double && (json_tokener_parse_double(tok->pb->buf, tok->pb->bpos, &numd) == 0))
        {
          tok->stack[tok->depth].current = json_object_new_double_s(numd, tok->pb->buf);
          if (tok->stack[tok->depth].current == 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_number;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
        break;

      case json_tokener_state_array_after_sep:

      case json_tokener_state_array:
        if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        if ((tok->stack[tok->depth].state == json_tokener_state_array_after_sep) && (tok->flags & 0x01))
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        if (tok->depth >= (tok->max_depth - 1))
        {
          tok->err = json_tokener_error_depth;
          goto out;
        }
        tok->stack[tok->depth].state = json_tokener_state_array_add;
        tok->depth += 1;
        json_tokener_reset_level(tok, tok->depth);
        goto redo_char;
      }
        break;

      case json_tokener_state_array_add:
        if (json_object_array_add(tok->stack[tok->depth].current, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
        tok->stack[tok->depth].saved_state = json_tokener_state_array_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;

      case json_tokener_state_array_sep:
        if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_array_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_array;
        goto out;
      }
        break;

      case json_tokener_state_object_field_start:

      case json_tokener_state_object_field_start_after_sep:
        if (c == '}')
      {
        if ((tok->stack[tok->depth].state == json_tokener_state_object_field_start_after_sep) && (tok->flags & 0x01))
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if ((c == '"') || (c == '\''))
      {
        tok->quote_char = c;
        printbuf_reset(tok->pb);
        tok->stack[tok->depth].state = json_tokener_state_object_field;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_name;
        goto out;
      }
        break;

      case json_tokener_state_object_field:
      {
        const char *case_start = str;
        while (1)
        {
          if (c == tok->quote_char)
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].obj_field_name = strdup(tok->pb->buf);
            if (tok->stack[tok->depth].obj_field_name == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_object_field_end;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            break;
          }
          else
            if (c == '\\')
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].saved_state = json_tokener_state_object_field;
            tok->stack[tok->depth].state = json_tokener_state_string_escape;
            break;
          }
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

      }
        break;

      case json_tokener_state_object_field_end:
        if (c == ':')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_value;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_sep;
        goto out;
      }
        break;

      case json_tokener_state_object_value:
        if (tok->depth >= (tok->max_depth - 1))
      {
        tok->err = json_tokener_error_depth;
        goto out;
      }
        tok->stack[tok->depth].state = json_tokener_state_object_value_add;
        tok->depth += 1;
        json_tokener_reset_level(tok, tok->depth);
        goto redo_char;

      case json_tokener_state_object_value_add:
        if (json_object_object_add(tok->stack[tok->depth].current, tok->stack[tok->depth].obj_field_name, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
        free(tok->stack[tok->depth].obj_field_name);
        tok->stack[tok->depth].obj_field_name = 0;
        tok->stack[tok->depth].saved_state = json_tokener_state_object_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;

      case json_tokener_state_object_sep:
        if (c == '}')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_value_sep;
        goto out;
      }
        break;

    }


    str_idx += 1;
    (void) ((++(&str[str_idx]), tok->char_offset++, c));
    if (!c)
    {
      break;
    }
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}

static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}

void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}

size_t json_tokener_get_parse_end(struct json_tokener *tok)
{
  assert(tok->char_offset >= 0);
  return (size_t) tok->char_offset;
}

static int json_tokener_parse_double(const char *buf, int len, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  if ((buf + len) == end)
  {
    return 0;
  }
  return 1;
}


extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
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
inline static int is_ws_char(char c)
{
  return (((c == ' ') || (c == '\t')) || (c == '\n')) || (c == '\r');
}

inline static int is_hex_char(char c)
{
  return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) || ((c >= 'a') && (c <= 'f'));
}

static const char json_null_str[] = "null";
static const int json_null_str_len = (sizeof(json_null_str)) - 1;
static const char json_inf_str[] = "Infinity";
static const char json_inf_str_invert[] = "iNFINITY";
static const unsigned int json_inf_str_len = (sizeof(json_inf_str)) - 1;
static const char json_nan_str[] = "NaN";
static const int json_nan_str_len = (sizeof(json_nan_str)) - 1;
static const char json_true_str[] = "true";
static const int json_true_str_len = (sizeof(json_true_str)) - 1;
static const char json_false_str[] = "false";
static const int json_false_str_len = (sizeof(json_false_str)) - 1;
static const char *json_tokener_errors[] = {"success", "continue", "nesting too deep", "unexpected end of data", "unexpected character", "null expected", "boolean expected", "number expected", "array value separator ',' expected", "quoted object property name expected", "object property name separator ':' expected", "object value separator ',' expected", "invalid string sequence", "expected comment", "invalid utf-8 string", "buffer size overflow", "out of memory"};
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes);
static int json_tokener_parse_double(const char *buf, int len, double *retval);
const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
  int jerr_int = (int) jerr;
  if ((jerr_int < 0) || (jerr_int >= ((int) ((sizeof(json_tokener_errors)) / (sizeof(json_tokener_errors[0]))))))
  {
    return "Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()";
  }
  return json_tokener_errors[jerr];
}

enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
}

static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD};
struct json_tokener *json_tokener_new_ex(int depth)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  if (depth < 1)
  {
    return 0;
  }
  tok_idx = (struct json_tokener *) calloc(1, sizeof(struct json_tokener));
  if (!(&tok[tok_idx]))
  {
    return 0;
  }
  tok->stack = (struct json_tokener_srec *) calloc(depth, sizeof(struct json_tokener_srec));
  if (!tok->stack)
  {
    free(tok);
    return 0;
  }
  tok->pb = printbuf_new();
  if (!tok->pb)
  {
    free(tok->stack);
    free(tok);
    return 0;
  }
  tok->max_depth = depth;
  json_tokener_reset(tok);
  return tok;
}

struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}

void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}

static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}

void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}

struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
}

struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  tok_idx = json_tokener_new();
  if (!(&tok[tok_idx]))
  {
    *error = json_tokener_error_memory;
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, str, -1);
  *error = tok->err;
  if (tok->err != json_tokener_success)
  {
    if ((&obj[obj_idx]) != 0)
    {
      json_object_put(obj);
    }
    obj_idx = 0;
  }
  json_tokener_free(tok);
  return obj;
}

struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    redo_char:
    switch (tok->stack[tok->depth].state)
    {
      case json_tokener_state_eatws:
        while (is_ws_char(c))
      {
        if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
        {
          goto out;
        }
      }

        if ((c == '/') && (!(tok->flags & 0x01)))
      {
        printbuf_reset(tok->pb);
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->stack[tok->depth].state = json_tokener_state_comment_start;
      }
      else
      {
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
        goto redo_char;
      }
        break;

      case json_tokener_state_start:
        switch (c)
      {
        case '{':
          tok->stack[tok->depth].state = json_tokener_state_eatws;
          tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start;
          tok->stack[tok->depth].current = json_object_new_object();
          if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
          break;

        case '[':
          tok->stack[tok->depth].state = json_tokener_state_eatws;
          tok->stack[tok->depth].saved_state = json_tokener_state_array;
          tok->stack[tok->depth].current = json_object_new_array();
          if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
          break;

        case 'I':

        case 'i':
          tok->stack[tok->depth].state = json_tokener_state_inf;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case 'N':

        case 'n':
          tok->stack[tok->depth].state = json_tokener_state_null;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case '\'':
          if (tok->flags & 0x01)
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }

        case '"':
          tok->stack[tok->depth].state = json_tokener_state_string;
          printbuf_reset(tok->pb);
          tok->quote_char = c;
          break;

        case 'T':

        case 't':

        case 'F':

        case 'f':
          tok->stack[tok->depth].state = json_tokener_state_boolean;
          printbuf_reset(tok->pb);
          tok->st_pos = 0;
          goto redo_char;

        case '0':

        case '1':

        case '2':

        case '3':

        case '4':

        case '5':

        case '6':

        case '7':

        case '8':

        case '9':

        case '-':
          tok->stack[tok->depth].state = json_tokener_state_number;
          printbuf_reset(tok->pb);
          tok->is_double = 0;
          goto redo_char;

        default:
          tok->err = json_tokener_error_parse_unexpected;
          goto out;

      }

        break;

      case json_tokener_state_finish:
        if (tok->depth == 0)
      {
        goto out;
      }
        obj_idx = json_object_get(tok->stack[tok->depth].current);
        json_tokener_reset_level(tok, tok->depth);
        tok->depth -= 1;
        goto redo_char;

      case json_tokener_state_inf:
      {
        int is_negative = 0;
        while (tok->st_pos < ((int) json_inf_str_len))
        {
          char inf_char = str[str_idx];
          if ((inf_char != json_inf_str[tok->st_pos]) && ((tok->flags & 0x01) || (inf_char != json_inf_str_invert[tok->st_pos])))
          {
            tok->err = json_tokener_error_parse_unexpected;
            goto out;
          }
          tok->st_pos += 1;
          str_idx += 1;
          (void) ((++(&str[str_idx]), tok->char_offset++, c));
          if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
          {
            goto out;
          }
        }

        if ((tok->pb->bpos > 0) && ((*tok->pb->buf) == '-'))
        {
          is_negative = 1;
        }
        tok->stack[tok->depth].current = json_object_new_double((is_negative) ? (-INFINITY) : (INFINITY));
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
        break;

      case json_tokener_state_null:
      {
        int size;
        int size_nan;
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        size = ((tok->st_pos + 1) < json_null_str_len) ? (tok->st_pos + 1) : (json_null_str_len);
        size_nan = ((tok->st_pos + 1) < json_nan_str_len) ? (tok->st_pos + 1) : (json_nan_str_len);
        if (((!(tok->flags & 0x01)) && (strncasecmp(json_null_str, tok->pb->buf, size) == 0)) || (strncmp(json_null_str, tok->pb->buf, size) == 0))
        {
          if (tok->st_pos == json_null_str_len)
          {
            tok->stack[tok->depth].current = 0;
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
          if (((!(tok->flags & 0x01)) && (strncasecmp(json_nan_str, tok->pb->buf, size_nan) == 0)) || (strncmp(json_nan_str, tok->pb->buf, size_nan) == 0))
        {
          if (tok->st_pos == json_nan_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_double(nan(""));
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_null;
          goto out;
        }
        tok->st_pos += 1;
      }
        break;

      case json_tokener_state_comment_start:
        if (c == '*')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      else
        if (c == '/')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment_eol;
      }
      else
      {
        tok->err = json_tokener_error_parse_comment;
        goto out;
      }
        do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
        break;

      case json_tokener_state_comment:
      {
        const char *case_start = str;
        while (c != '*')
        {
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        do
        {
          if (printbuf_memappend(tok->pb, case_start, (1 + (&str[str_idx])) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->stack[tok->depth].state = json_tokener_state_comment_end;
      }
        break;

      case json_tokener_state_comment_eol:
      {
        const char *case_start = str;
        while (c != '\n')
        {
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
        break;

      case json_tokener_state_comment_end:
        do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
        if (c == '/')
      {
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
        break;

      case json_tokener_state_string:
      {
        const char *case_start = str;
        while (1)
        {
          if (c == tok->quote_char)
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].current = json_object_new_string_len(tok->pb->buf, tok->pb->bpos);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            break;
          }
          else
            if (c == '\\')
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].saved_state = json_tokener_state_string;
            tok->stack[tok->depth].state = json_tokener_state_string_escape;
            break;
          }
          else
            if ((tok->flags & 0x01) && (((unsigned char) c) <= 0x1f))
          {
            tok->err = json_tokener_error_parse_string;
            goto out;
          }
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

      }
        break;

      case json_tokener_state_string_escape:
        switch (c)
      {
        case '"':

        case '\\':

        case '/':
          do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
          tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
          break;

        case 'b':

        case 'n':

        case 'r':

        case 't':

        case 'f':
          if (c == 'b')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\b", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'n')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\n", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'r')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\r", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 't')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\t", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (c == 'f')
        {
          do
          {
            if (printbuf_memappend(tok->pb, "\f", 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
          tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
          break;

        case 'u':
          tok->ucs_char = 0;
          tok->st_pos = 0;
          tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
          break;

        default:
          tok->err = json_tokener_error_parse_string;
          goto out;

      }

        break;

      case json_tokener_state_escape_unicode:
      {
        while (1)
        {
          if ((!c) || (!is_hex_char(c)))
          {
            tok->err = json_tokener_error_parse_string;
            goto out;
          }
          tok->ucs_char |= ((unsigned int) ((c <= '9') ? (c - '0') : ((c & 7) + 9))) << ((3 - tok->st_pos) * 4);
          tok->st_pos += 1;
          if (tok->st_pos >= 4)
          {
            break;
          }
          str_idx += 1;
          (void) ((++(&str[str_idx]), tok->char_offset++, c));
          if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
          {
            goto out;
          }
        }

        tok->st_pos = 0;
        if (tok->high_surrogate)
        {
          if ((tok->ucs_char & 0xFC00) == 0xDC00)
          {
            tok->ucs_char = (((tok->high_surrogate & 0x3FF) << 10) + (tok->ucs_char & 0x3FF)) + 0x10000;
          }
          else
          {
            do
            {
              if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
          }
          tok->high_surrogate = 0;
        }
        if (tok->ucs_char < 0x80)
        {
          unsigned char unescaped_utf[1];
          unescaped_utf[0] = tok->ucs_char;
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 1) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x800)
        {
          unsigned char unescaped_utf[2];
          unescaped_utf[0] = 0xc0 | (tok->ucs_char >> 6);
          unescaped_utf[1] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 2) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if ((tok->ucs_char & 0xFC00) == 0xD800)
        {
          tok->high_surrogate = tok->ucs_char;
          tok->ucs_char = 0;
          tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_escape;
          break;
        }
        else
          if ((tok->ucs_char & 0xFC00) == 0xDC00)
        {
          do
          {
            if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x10000)
        {
          unsigned char unescaped_utf[3];
          unescaped_utf[0] = 0xe0 | (tok->ucs_char >> 12);
          unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
          unescaped_utf[2] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
          if (tok->ucs_char < 0x110000)
        {
          unsigned char unescaped_utf[4];
          unescaped_utf[0] = 0xf0 | ((tok->ucs_char >> 18) & 0x07);
          unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 12) & 0x3f);
          unescaped_utf[2] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
          unescaped_utf[3] = 0x80 | (tok->ucs_char & 0x3f);
          do
          {
            if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 4) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        else
        {
          do
          {
            if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
      }
        break;

      case json_tokener_state_escape_unicode_need_escape:
        if ((!c) || (c != '\\'))
      {
        do
        {
          if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->high_surrogate = 0;
        tok->ucs_char = 0;
        tok->st_pos = 0;
        tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
        goto redo_char;
      }
        tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_u;
        break;

      case json_tokener_state_escape_unicode_need_u:
        if ((!c) || (c != 'u'))
      {
        do
        {
          if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        tok->high_surrogate = 0;
        tok->ucs_char = 0;
        tok->st_pos = 0;
        tok->stack[tok->depth].state = json_tokener_state_string_escape;
        goto redo_char;
      }
        tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
        break;

      case json_tokener_state_boolean:
      {
        int size1;
        int size2;
        do
        {
          if (printbuf_memappend(tok->pb, &c, 1) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        size1 = ((tok->st_pos + 1) < json_true_str_len) ? (tok->st_pos + 1) : (json_true_str_len);
        size2 = ((tok->st_pos + 1) < json_false_str_len) ? (tok->st_pos + 1) : (json_false_str_len);
        if (((!(tok->flags & 0x01)) && (strncasecmp(json_true_str, tok->pb->buf, size1) == 0)) || (strncmp(json_true_str, tok->pb->buf, size1) == 0))
        {
          if (tok->st_pos == json_true_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_boolean(1);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
          if (((!(tok->flags & 0x01)) && (strncasecmp(json_false_str, tok->pb->buf, size2) == 0)) || (strncmp(json_false_str, tok->pb->buf, size2) == 0))
        {
          if (tok->st_pos == json_false_str_len)
          {
            tok->stack[tok->depth].current = json_object_new_boolean(0);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_finish;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            goto redo_char;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_boolean;
          goto out;
        }
        tok->st_pos += 1;
      }
        break;

      case json_tokener_state_number:
      {
        const char *case_start = str;
        int case_len = 0;
        int is_exponent = 0;
        int neg_sign_ok = 1;
        int pos_sign_ok = 0;
        if (tok->pb->bpos > 0)
        {
          char *e_loc = strchr(tok->pb->buf, 'e');
          unsigned int e_loc_idx = 0;
          if (!(&e_loc[e_loc_idx]))
          {
            e_loc_idx = strchr(tok->pb->buf, 'E');
          }
          if (e_loc)
          {
            char *last_saved_char = &tok->pb->buf[tok->pb->bpos - 1];
            is_exponent = 1;
            pos_sign_ok = (neg_sign_ok = 1);
            if ((&e_loc[e_loc_idx]) != last_saved_char)
            {
              neg_sign_ok = 0;
              pos_sign_ok = 0;
            }
          }
        }
        while (c && ((((((c >= '0') && (c <= '9')) || ((!is_exponent) && ((c == 'e') || (c == 'E')))) || (neg_sign_ok && (c == '-'))) || (pos_sign_ok && (c == '+'))) || ((!tok->is_double) && (c == '.'))))
        {
          pos_sign_ok = (neg_sign_ok = 0);
          case_len += 1;
          switch (c)
          {
            case '.':
              tok->is_double = 1;
              pos_sign_ok = 1;
              neg_sign_ok = 1;
              break;

            case 'e':

            case 'E':
              is_exponent = 1;
              tok->is_double = 1;
              pos_sign_ok = (neg_sign_ok = 1);
              break;

            default:
              break;

          }

          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

        if ((((((((tok->depth > 0) && (c != ',')) && (c != ']')) && (c != '}')) && (c != '/')) && (c != 'I')) && (c != 'i')) && (!is_ws_char(c)))
        {
          tok->err = json_tokener_error_parse_number;
          goto out;
        }
        if (case_len > 0)
        {
          do
          {
            if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          while (0);
        }
        if (((tok->pb->buf[0] == '-') && (case_len <= 1)) && ((c == 'i') || (c == 'I')))
        {
          tok->stack[tok->depth].state = json_tokener_state_inf;
          tok->st_pos = 0;
          goto redo_char;
        }
        if (tok->is_double && (!(tok->flags & 0x01)))
        {
          while (tok->pb->bpos > 1)
          {
            char last_char = tok->pb->buf[tok->pb->bpos - 1];
            if ((((last_char != 'e') && (last_char != 'E')) && (last_char != '-')) && (last_char != '+'))
            {
              break;
            }
            tok->pb->buf[tok->pb->bpos - 1] = '\0';
            tok->pb->bpos -= 1;
          }

        }
      }
      {
        int64_t num64;
        uint64_t numuint64;
        double numd;
        if (((!tok->is_double) && (tok->pb->buf[0] == '-')) && (json_parse_int64(tok->pb->buf, &num64) == 0))
        {
          if ((errno == ERANGE) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          tok->stack[tok->depth].current = json_object_new_int64(num64);
          if (tok->stack[tok->depth].current == 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        else
          if (((!tok->is_double) && (tok->pb->buf[0] != '-')) && (json_parse_uint64(tok->pb->buf, &numuint64) == 0))
        {
          if ((errno == ERANGE) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          if ((numuint64 && (tok->pb->buf[0] == '0')) && (tok->flags & 0x01))
          {
            tok->err = json_tokener_error_parse_number;
            goto out;
          }
          if (numuint64 <= INT64_MAX)
          {
            num64 = (uint64_t) numuint64;
            tok->stack[tok->depth].current = json_object_new_int64(num64);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
          else
          {
            tok->stack[tok->depth].current = json_object_new_uint64(numuint64);
            if (tok->stack[tok->depth].current == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
          }
        }
        else
          if (tok->is_double && (json_tokener_parse_double(tok->pb->buf, tok->pb->bpos, &numd) == 0))
        {
          tok->stack[tok->depth].current = json_object_new_double_s(numd, tok->pb->buf);
          if (tok->stack[tok->depth].current == 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        else
        {
          tok->err = json_tokener_error_parse_number;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
        break;

      case json_tokener_state_array_after_sep:

      case json_tokener_state_array:
        if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        if ((tok->stack[tok->depth].state == json_tokener_state_array_after_sep) && (tok->flags & 0x01))
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        if (tok->depth >= (tok->max_depth - 1))
        {
          tok->err = json_tokener_error_depth;
          goto out;
        }
        tok->stack[tok->depth].state = json_tokener_state_array_add;
        tok->depth += 1;
        json_tokener_reset_level(tok, tok->depth);
        goto redo_char;
      }
        break;

      case json_tokener_state_array_add:
        if (json_object_array_add(tok->stack[tok->depth].current, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
        tok->stack[tok->depth].saved_state = json_tokener_state_array_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;

      case json_tokener_state_array_sep:
        if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_array_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_array;
        goto out;
      }
        break;

      case json_tokener_state_object_field_start:

      case json_tokener_state_object_field_start_after_sep:
        if (c == '}')
      {
        if ((tok->stack[tok->depth].state == json_tokener_state_object_field_start_after_sep) && (tok->flags & 0x01))
        {
          tok->err = json_tokener_error_parse_unexpected;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if ((c == '"') || (c == '\''))
      {
        tok->quote_char = c;
        printbuf_reset(tok->pb);
        tok->stack[tok->depth].state = json_tokener_state_object_field;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_name;
        goto out;
      }
        break;

      case json_tokener_state_object_field:
      {
        const char *case_start = str;
        while (1)
        {
          if (c == tok->quote_char)
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].obj_field_name = strdup(tok->pb->buf);
            if (tok->stack[tok->depth].obj_field_name == 0)
            {
              tok->err = json_tokener_error_memory;
              goto out;
            }
            tok->stack[tok->depth].saved_state = json_tokener_state_object_field_end;
            tok->stack[tok->depth].state = json_tokener_state_eatws;
            break;
          }
          else
            if (c == '\\')
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            tok->stack[tok->depth].saved_state = json_tokener_state_object_field;
            tok->stack[tok->depth].state = json_tokener_state_string_escape;
            break;
          }
          if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
          {
            do
            {
              if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
              {
                tok->err = json_tokener_error_memory;
                goto out;
              }
            }
            while (0);
            goto out;
          }
        }

      }
        break;

      case json_tokener_state_object_field_end:
        if (c == ':')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_value;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_sep;
        goto out;
      }
        break;

      case json_tokener_state_object_value:
        if (tok->depth >= (tok->max_depth - 1))
      {
        tok->err = json_tokener_error_depth;
        goto out;
      }
        tok->stack[tok->depth].state = json_tokener_state_object_value_add;
        tok->depth += 1;
        json_tokener_reset_level(tok, tok->depth);
        goto redo_char;

      case json_tokener_state_object_value_add:
        if (json_object_object_add(tok->stack[tok->depth].current, tok->stack[tok->depth].obj_field_name, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
        free(tok->stack[tok->depth].obj_field_name);
        tok->stack[tok->depth].obj_field_name = 0;
        tok->stack[tok->depth].saved_state = json_tokener_state_object_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;

      case json_tokener_state_object_sep:
        if (c == '}')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_value_sep;
        goto out;
      }
        break;

    }


    str_idx += 1;
    (void) ((++(&str[str_idx]), tok->char_offset++, c));
    if (!c)
    {
      break;
    }
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}

static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}

void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}

size_t json_tokener_get_parse_end(struct json_tokener *tok)
{
  assert(tok->char_offset >= 0);
  return (size_t) tok->char_offset;
}

static int json_tokener_parse_double(const char *buf, int len, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  if ((buf + len) == end)
  {
    return 0;
  }
  return 1;
}

