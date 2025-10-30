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


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


int json_parse_double(const char *buf, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  return (end == buf) ? (1) : (0);
}


/*** DEPENDENCIES:
***/


const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
}


/*** DEPENDENCIES:
static char _last_err[256] = ""
----------------------------
***/


void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


/*** DEPENDENCIES:
static char _last_err[256] = ""
----------------------------
***/


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


/*** DEPENDENCIES:
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


----------------------------
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type
----------------------------
static const char *json_type_name[] = {"null", "boolean", "double", "int", "object", "array", "string"}
----------------------------
***/


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
enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
}


----------------------------
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
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
struct printbuf *printbuf_new(void)
{
  struct printbuf *p;
  unsigned int p_idx = 0;
  p_idx = (struct printbuf *) calloc(1, sizeof(struct printbuf));
  if (!(&p[p_idx]))
  {
    return 0;
  }
  p->size = 32;
  p->bpos = 0;
  if (!(p->buf = (char *) malloc(p->size)))
  {
    free(p);
    return 0;
  }
  p->buf[0] = '\0';
  return p;
}


----------------------------
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


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
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
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


----------------------------
None
----------------------------
***/


struct json_object *json_object_from_fd(int fd)
{
  return json_object_from_fd_ex(fd, -1);
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


int json_object_to_file(const char *filename, struct json_object *obj)
{
  return json_object_to_file_ext(filename, obj, 0);
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


int json_object_to_fd(int fd, struct json_object *obj, int flags)
{
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_fd: object is null\n");
    return -1;
  }
  return _json_object_to_fd(fd, obj, flags, 0);
}


/*** DEPENDENCIES:
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


----------------------------
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


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void _json_c_set_last_err(const char *err_fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  (void) vsnprintf(_last_err, sizeof(_last_err), err_fmt, ap);
  ;
}


----------------------------
struct json_object *json_object_from_fd(int fd)
{
  return json_object_from_fd_ex(fd, -1);
}


----------------------------
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


----------------------------
None
----------------------------
***/


