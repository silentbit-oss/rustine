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


/*** DEPENDENCIES:
***/


static void showmem(void)
{
  struct rusage rusage;
  memset(&rusage, 0, sizeof(rusage));
  getrusage(RUSAGE_SELF, &rusage);
  fprintf(stderr, "maxrss: %ld KB\n", rusage.ru_maxrss);
}


/*** DEPENDENCIES:
***/


// hint:  ['obj_idx_ref is a mutable refrence to unsigned int', 'total_read_ref is a mutable refrence to size_t']
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


/*** DEPENDENCIES:
None
----------------------------
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
    helper_json_tokener_parse_ex_1(&str_idx, &obj_idx, &c, tok, str, len, obj, nBytesp);
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


----------------------------
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
}
----------------------------
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


----------------------------
pub callback: XIMProc
----------------------------
const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
  int jerr_int = (int) jerr;
  if ((jerr_int < 0) || (jerr_int >= ((int) ((sizeof(json_tokener_errors)) / (sizeof(json_tokener_errors[0]))))))
  {
    return "Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()";
  }
  return json_tokener_errors[jerr];
}


----------------------------
enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
}


----------------------------
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
    {
      json_object_object_delete(jso);
      break;
    }

    case json_type_array:
    {
      json_object_array_delete(jso);
      break;
    }

    case json_type_string:
    {
      json_object_string_delete(jso);
      break;
    }

    default:
    {
      json_object_generic_delete(jso);
      break;
    }

  }

  return 1;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
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


----------------------------
void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}


----------------------------
static int strict_mode = 0
----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static int formatted_output = 1 << 0
----------------------------
static int show_output = 1
----------------------------
static const char *fname = 0
----------------------------
static int color = 0
----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
static void showmem(void)
{
  struct rusage rusage;
  memset(&rusage, 0, sizeof(rusage));
  getrusage(RUSAGE_SELF, &rusage);
  fprintf(stderr, "maxrss: %ld KB\n", rusage.ru_maxrss);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static int formatted_output = 1 << 0
----------------------------
static int show_output = 1
----------------------------
static const char *fname = 0
----------------------------
static int color = 0
----------------------------
static int strict_mode = 0
----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
static void showmem(void)
{
  struct rusage rusage;
  memset(&rusage, 0, sizeof(rusage));
  getrusage(RUSAGE_SELF, &rusage);
  fprintf(stderr, "maxrss: %ld KB\n", rusage.ru_maxrss);
}


----------------------------
***/


