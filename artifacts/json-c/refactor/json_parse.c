#include <apps_config.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_parse.c>
#include <json_tokener.h>
#include <json_types.h>
#include <json_util.h>
#include <printbuf.h>
#include <resource.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
static int formatted_output = 1 << 0;
static int show_output = 1;
static int strict_mode = 0;
static int color = 0;
static const char *fname = 0;
static void usage(const char *argv0, int exitval, const char *errmsg);
static void showmem(void);
static int parseit(int fd, int (*callback)(struct json_object *));
static int showobj(struct json_object *new_obj);
static void showmem(void)
{
  struct rusage rusage;
  memset(&rusage, 0, sizeof(rusage));
  getrusage(RUSAGE_SELF, &rusage);
  fprintf(stderr, "maxrss: %ld KB\n", rusage.ru_maxrss);
}

static int parseit(int fd, int (*callback)(struct json_object *))
{
  struct json_object *obj;
  unsigned int obj_idx = 0;
  char buf[32768];
  ssize_t ret;
  int depth = 32;
  json_tokener *tok;
  unsigned int tok_idx = 0;
  tok_idx = json_tokener_new_ex(depth);
  if (!(&tok[tok_idx]))
  {
    fprintf(stderr, "unable to allocate json_tokener: %s\n", strerror(errno));
    return 1;
  }
  if (strict_mode)
  {
    json_tokener_set_flags(tok, 0x01 | 0x02);
  }
  size_t total_read = 0;
  while ((ret = read(fd, buf, sizeof(buf))) > 0)
  {
    helper_parseit_1(&obj_idx, &total_read, obj, buf, ret, tok);
  }

  if (ret < 0)
  {
    fprintf(stderr, "error reading fd %d: %s\n", fd, strerror(errno));
  }
  json_tokener_free(tok);
  return 0;
}

static int showobj(struct json_object *new_obj)
{
  if (new_obj == 0)
  {
    fprintf(stderr, "%s: Failed to parse\n", fname);
    return 1;
  }
  fprintf(stderr, "Successfully parsed object from %s\n", fname);
  if (show_output)
  {
    const char *output;
    unsigned int output_idx = 0;
    output_idx = json_object_to_json_string_ext(new_obj, formatted_output | color);
    printf("%s\n", output);
  }
  showmem();
  return 0;
}

static void usage(const char *argv0, int exitval, const char *errmsg)
{
  FILE *fp = stdout;
  unsigned int fp_idx = 0;
  if (exitval != 0)
  {
    fp_idx = stderr;
  }
  if (errmsg != 0)
  {
    fprintf(fp, "ERROR: %s\n\n", errmsg);
  }
  fprintf(fp, "Usage: %s [-f|-F <arg>] [-n] [-s]\n", argv0);
  fprintf(fp, "  -f - Format the output to stdout with JSON_C_TO_STRING_PRETTY (default is JSON_C_TO_STRING_SPACED)\n");
  fprintf(fp, "  -F - Format the output to stdout with <arg>, e.g. 0 for JSON_C_TO_STRING_PLAIN\n");
  fprintf(fp, "  -n - No output\n");
  fprintf(fp, "  -c - color\n");
  fprintf(fp, "  -s - Parse in strict mode, flags:\n");
  fprintf(fp, "       JSON_TOKENER_STRICT|JSON_TOKENER_ALLOW_TRAILING_CHARS\n");
  fprintf(fp, " Diagnostic information will be emitted to stderr\n");
  fprintf(fp, "\nWARNING WARNING WARNING\n");
  fprintf(fp, "This is a prototype, it may change or be removed at any time!\n");
  exit(exitval);
}

int main(int argc, char **argv)
{
  int opt;
  while ((opt = getopt(argc, argv, "fF:hnsc")) != (-1))
  {
    switch (opt)
    {
      case 'f':
        formatted_output = 1 << 1;
        break;

      case 'F':
        formatted_output = atoi(optarg);
        break;

      case 'n':
        show_output = 0;
        break;

      case 's':
        strict_mode = 1;
        break;

      case 'c':
        color = 1 << 5;
        break;

      case 'h':
        usage(argv[0], 0, 0);

      default:
        usage(argv[0], 1, "Unknown arguments");

    }

  }

  if (optind >= argc)
  {
    usage(argv[0], 1, "Expected argument after options");
  }
  fname = argv[optind];
  int fd = open(argv[optind], O_RDONLY, 0);
  showmem();
  if (parseit(fd, showobj) != 0)
  {
    exit(1);
  }
  showmem();
  exit(0);
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
static int formatted_output = 1 << 0;
static int show_output = 1;
static int strict_mode = 0;
static int color = 0;
static const char *fname = 0;
static void usage(const char *argv0, int exitval, const char *errmsg);
static void showmem(void);
static int parseit(int fd, int (*callback)(struct json_object *));
static int showobj(struct json_object *new_obj);
static void showmem(void)
{
  struct rusage rusage;
  memset(&rusage, 0, sizeof(rusage));
  getrusage(RUSAGE_SELF, &rusage);
  fprintf(stderr, "maxrss: %ld KB\n", rusage.ru_maxrss);
}

static int parseit(int fd, int (*callback)(struct json_object *))
{
  struct json_object *obj;
  unsigned int obj_idx = 0;
  char buf[32768];
  ssize_t ret;
  int depth = 32;
  json_tokener *tok;
  unsigned int tok_idx = 0;
  tok_idx = json_tokener_new_ex(depth);
  if (!(&tok[tok_idx]))
  {
    fprintf(stderr, "unable to allocate json_tokener: %s\n", strerror(errno));
    return 1;
  }
  if (strict_mode)
  {
    json_tokener_set_flags(tok, 0x01 | 0x02);
  }
  size_t total_read = 0;
  while ((ret = read(fd, buf, sizeof(buf))) > 0)
  {
    size_t retu = (size_t) ret;
    total_read += retu;
    size_t start_pos = 0;
    while (start_pos != retu)
    {
      obj_idx = json_tokener_parse_ex(tok, &buf[start_pos], retu - start_pos);
      enum json_tokener_error jerr = json_tokener_get_error(tok);
      size_t parse_end = tok->char_offset;
      if (((&obj[obj_idx]) == 0) && (jerr != json_tokener_continue))
      {
        const char *aterr = ((start_pos + parse_end) < ((int) (sizeof(buf)))) ? (&buf[start_pos + parse_end]) : ("");
        fflush(stdout);
        size_t fail_offset = ((total_read - retu) + start_pos) + parse_end;
        fprintf(stderr, "Failed at offset %lu: %s %c\n", (unsigned long) fail_offset, json_tokener_error_desc(jerr), aterr[0]);
        json_tokener_free(tok);
        return 1;
      }
      if ((&obj[obj_idx]) != 0)
      {
        int cb_ret = callback(obj);
        json_object_put(obj);
        if (cb_ret != 0)
        {
          json_tokener_free(tok);
          return 1;
        }
      }
      start_pos += tok->char_offset;
      assert(start_pos <= retu);
    }

  }

  if (ret < 0)
  {
    fprintf(stderr, "error reading fd %d: %s\n", fd, strerror(errno));
  }
  json_tokener_free(tok);
  return 0;
}

static int showobj(struct json_object *new_obj)
{
  if (new_obj == 0)
  {
    fprintf(stderr, "%s: Failed to parse\n", fname);
    return 1;
  }
  fprintf(stderr, "Successfully parsed object from %s\n", fname);
  if (show_output)
  {
    const char *output;
    unsigned int output_idx = 0;
    output_idx = json_object_to_json_string_ext(new_obj, formatted_output | color);
    printf("%s\n", output);
  }
  showmem();
  return 0;
}

static void usage(const char *argv0, int exitval, const char *errmsg)
{
  FILE *fp = stdout;
  unsigned int fp_idx = 0;
  if (exitval != 0)
  {
    fp_idx = stderr;
  }
  if (errmsg != 0)
  {
    fprintf(fp, "ERROR: %s\n\n", errmsg);
  }
  fprintf(fp, "Usage: %s [-f|-F <arg>] [-n] [-s]\n", argv0);
  fprintf(fp, "  -f - Format the output to stdout with JSON_C_TO_STRING_PRETTY (default is JSON_C_TO_STRING_SPACED)\n");
  fprintf(fp, "  -F - Format the output to stdout with <arg>, e.g. 0 for JSON_C_TO_STRING_PLAIN\n");
  fprintf(fp, "  -n - No output\n");
  fprintf(fp, "  -c - color\n");
  fprintf(fp, "  -s - Parse in strict mode, flags:\n");
  fprintf(fp, "       JSON_TOKENER_STRICT|JSON_TOKENER_ALLOW_TRAILING_CHARS\n");
  fprintf(fp, " Diagnostic information will be emitted to stderr\n");
  fprintf(fp, "\nWARNING WARNING WARNING\n");
  fprintf(fp, "This is a prototype, it may change or be removed at any time!\n");
  exit(exitval);
}

int main(int argc, char **argv)
{
  int opt;
  while ((opt = getopt(argc, argv, "fF:hnsc")) != (-1))
  {
    switch (opt)
    {
      case 'f':
        formatted_output = 1 << 1;
        break;

      case 'F':
        formatted_output = atoi(optarg);
        break;

      case 'n':
        show_output = 0;
        break;

      case 's':
        strict_mode = 1;
        break;

      case 'c':
        color = 1 << 5;
        break;

      case 'h':
        usage(argv[0], 0, 0);

      default:
        usage(argv[0], 1, "Unknown arguments");

    }

  }

  if (optind >= argc)
  {
    usage(argv[0], 1, "Expected argument after options");
  }
  fname = argv[optind];
  int fd = open(argv[optind], O_RDONLY, 0);
  showmem();
  if (parseit(fd, showobj) != 0)
  {
    exit(1);
  }
  showmem();
  exit(0);
}

int helper_parseit_1(unsigned int * const obj_idx_ref, size_t * const total_read_ref, struct json_object * const obj, char buf[32768], ssize_t ret, json_tokener * const tok)
{
  unsigned int obj_idx = *obj_idx_ref;
  size_t total_read = *total_read_ref;
  size_t retu = (size_t) ret;
  total_read += retu;
  size_t start_pos = 0;
  while (start_pos != retu)
  {
    obj_idx = json_tokener_parse_ex(tok, &buf[start_pos], retu - start_pos);
    enum json_tokener_error jerr = json_tokener_get_error(tok);
    size_t parse_end = tok->char_offset;
    if (((&obj[obj_idx]) == 0) && (jerr != json_tokener_continue))
    {
      const char *aterr = ((start_pos + parse_end) < ((int) (sizeof(buf)))) ? (&buf[start_pos + parse_end]) : ("");
      fflush(stdout);
      size_t fail_offset = ((total_read - retu) + start_pos) + parse_end;
      fprintf(stderr, "Failed at offset %lu: %s %c\n", (unsigned long) fail_offset, json_tokener_error_desc(jerr), aterr[0]);
      json_tokener_free(tok);
      return 1;
    }
    if ((&obj[obj_idx]) != 0)
    {
      int cb_ret = callback(obj);
      json_object_put(obj);
      if (cb_ret != 0)
      {
        json_tokener_free(tok);
        return 1;
      }
    }
    start_pos += tok->char_offset;
    assert(start_pos <= retu);
  }

  *obj_idx_ref = obj_idx;
  *total_read_ref = total_read;
}

