static void stat_and_cat(const char *file)
{
  struct stat sb;
  int d = open(file, O_RDONLY);
  if (d < 0)
  {
    printf("FAIL: unable to open %s: %s\n", file, _json_c_strerror(errno));
    return;
  }
  if (fstat(d, &sb) < 0)
  {
    printf("FAIL: unable to stat %s: %s\n", file, _json_c_strerror(errno));
    close(d);
    return;
  }
  char *buf = malloc(sb.st_size + 1);
  if (!buf)
  {
    printf("FAIL: unable to allocate memory\n");
    close(d);
    return;
  }
  if (read(d, buf, sb.st_size) < sb.st_size)
  {
    printf("FAIL: unable to read all of %s: %s\n", file, _json_c_strerror(errno));
    free(buf);
    close(d);
    return;
  }
  buf[sb.st_size] = '\0';
  printf("file[%s], size=%d, contents=%s\n", file, (int) sb.st_size, buf);
  free(buf);
  close(d);
}


/*** DEPENDENCIES:
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
***/


static void test_read_nonexistant(void)
{
  const char *filename = "./not_present.json";
  json_object *jso = json_object_from_file(filename);
  if (jso != 0)
  {
    printf("FAIL: json_object_from_file(%s) returned %p when NULL expected\n", filename, (void *) jso);
    json_object_put(jso);
  }
  else
  {
    printf("OK: json_object_from_file(%s) correctly returned NULL: %s\n", filename, json_util_get_last_err());
  }
}


/*** DEPENDENCIES:
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
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
}


----------------------------
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


----------------------------
None
----------------------------
***/


static void test_read_closed(void)
{
  int d = open("/dev/null", O_RDONLY);
  if (d < 0)
  {
    puts("FAIL: unable to open");
  }
  int fixed_d = 10;
  if (dup2(d, fixed_d) < 0)
  {
    printf("FAIL: unable to dup to fd %d", fixed_d);
  }
  close(d);
  close(fixed_d);
  json_object *jso = json_object_from_fd(fixed_d);
  if (jso != 0)
  {
    printf("FAIL: read from closed fd returning non-NULL: %p\n", (void *) jso);
    fflush(stdout);
    printf("  jso=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
    return;
  }
  printf("OK: json_object_from_fd(closed_fd), expecting NULL, EBADF, got:NULL, %s\n", json_util_get_last_err());
}


/*** DEPENDENCIES:
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
struct json_object *json_object_from_fd(int fd)
{
  return json_object_from_fd_ex(fd, -1);
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
}


----------------------------
None
----------------------------
***/


static void test_read_valid_with_fd(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid.json", testdir);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  json_object *jso = json_object_from_fd(d);
  if (jso != 0)
  {
    printf("OK: json_object_from_fd(valid.json)=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    fprintf(stderr, "FAIL: unable to parse contents of %s: %s\n", filename, json_util_get_last_err());
  }
  close(d);
}


/*** DEPENDENCIES:
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
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
None
----------------------------
***/


static void test_read_valid_nested_with_fd(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid_nested.json", testdir);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  assert(0 == json_object_from_fd_ex(d, -2));
  json_object *jso = json_object_from_fd_ex(d, 20);
  unsigned int jso_idx = 0;
  if ((&jso[jso_idx]) != 0)
  {
    printf("OK: json_object_from_fd_ex(valid_nested.json, 20)=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    fprintf(stderr, "FAIL: unable to parse contents of %s: %s\n", filename, json_util_get_last_err());
  }
  (void) lseek(d, 0, 0);
  jso_idx = json_object_from_fd_ex(d, 3);
  if ((&jso[jso_idx]) != 0)
  {
    printf("FAIL: json_object_from_fd_ex(%s, 3)=%s\n", filename, json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    printf("OK: correctly unable to parse contents of valid_nested.json with low max depth: %s\n", json_util_get_last_err());
  }
  close(d);
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
const char *json_util_get_last_err(void)
{
  if (_last_err[0] == '\0')
  {
    return 0;
  }
  return _last_err;
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
None
----------------------------
***/


static void test_read_fd_equal(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid_nested.json", testdir);
  json_object *jso = json_object_from_file(filename);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  json_object *new_jso = json_object_from_fd(d);
  close(d);
  printf("OK: json_object_from_file(valid.json)=%s\n", json_object_to_json_string(jso));
  printf("OK: json_object_from_fd(valid.json)=%s\n", json_object_to_json_string(new_jso));
  json_object_put(jso);
  json_object_put(new_jso);
}


/*** DEPENDENCIES:
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
None
----------------------------
***/


static void test_write_to_file(void)
{
  json_object *jso;
  unsigned int jso_idx = 0;
  jso_idx = json_tokener_parse("{\"foo\":1234,\"foo1\":\"abcdefghijklmnopqrstuvwxyz\",\"foo2\":\"abcdefghijklmnopqrstuvwxyz\",\"foo3\":\"abcdefghijklmnopqrstuvwxyz\",\"foo4\":\"abcdefghijklmnopqrstuvwxyz\",\"foo5\":\"abcdefghijklmnopqrstuvwxyz\",\"foo6\":\"abcdefghijklmnopqrstuvwxyz\",\"foo7\":\"abcdefghijklmnopqrstuvwxyz\",\"foo8\":\"abcdefghijklmnopqrstuvwxyz\",\"foo9\":\"abcdefghijklmnopqrstuvwxyz\"}");
  const char *outfile = "json.out";
  int rv = json_object_to_file(outfile, jso);
  printf("%s: json_object_to_file(%s, jso)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile, rv);
  if (rv == 0)
  {
    stat_and_cat(outfile);
  }
  putchar('\n');
  const char *outfile2 = "json2.out";
  rv = json_object_to_file_ext(outfile2, jso, 1 << 1);
  printf("%s: json_object_to_file_ext(%s, jso, JSON_C_TO_STRING_PRETTY)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile2, rv);
  if (rv == 0)
  {
    stat_and_cat(outfile2);
  }
  const char *outfile3 = "json3.out";
  int d = open(outfile3, O_WRONLY | O_CREAT, 0600);
  if (d < 0)
  {
    printf("FAIL: unable to open %s %s\n", outfile3, _json_c_strerror(errno));
    return;
  }
  rv = json_object_to_fd(d, jso, 1 << 1);
  printf("%s: json_object_to_fd(%s, jso, JSON_C_TO_STRING_PRETTY)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile3, rv);
  rv = json_object_to_fd(d, jso, 0);
  printf("%s: json_object_to_fd(%s, jso, JSON_C_TO_STRING_PLAIN)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile3, rv);
  close(d);
  if (rv == 0)
  {
    stat_and_cat(outfile3);
  }
  json_object_put(jso);
}


/*** DEPENDENCIES:
static void stat_and_cat(const char *file)
{
  struct stat sb;
  int d = open(file, O_RDONLY);
  if (d < 0)
  {
    printf("FAIL: unable to open %s: %s\n", file, _json_c_strerror(errno));
    return;
  }
  if (fstat(d, &sb) < 0)
  {
    printf("FAIL: unable to stat %s: %s\n", file, _json_c_strerror(errno));
    close(d);
    return;
  }
  char *buf = malloc(sb.st_size + 1);
  if (!buf)
  {
    printf("FAIL: unable to allocate memory\n");
    close(d);
    return;
  }
  if (read(d, buf, sb.st_size) < sb.st_size)
  {
    printf("FAIL: unable to read all of %s: %s\n", file, _json_c_strerror(errno));
    free(buf);
    close(d);
    return;
  }
  buf[sb.st_size] = '\0';
  printf("file[%s], size=%d, contents=%s\n", file, (int) sb.st_size, buf);
  free(buf);
  close(d);
}


----------------------------
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
struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
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
int json_object_to_file(const char *filename, struct json_object *obj)
{
  return json_object_to_file_ext(filename, obj, 0);
}


----------------------------
int json_object_to_fd(int fd, struct json_object *obj, int flags)
{
  if (!obj)
  {
    _json_c_set_last_err("json_object_to_fd: object is null\n");
    return -1;
  }
  return _json_object_to_fd(fd, obj, flags, 0);
}


----------------------------
None
----------------------------
***/


int main(int argc, char **argv)
{
  const char *testdir;
  unsigned int testdir_idx = 0;
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <testdir>\n  <testdir> is the location of input files\n", argv[0]);
    return 1;
  }
  testdir_idx = argv[1];
  if (strncmp(json_c_version(), "0.18.99", sizeof("0.18.99")))
  {
    printf("FAIL: Output from json_c_version(): %s does not match %s", json_c_version(), "0.18.99");
    return 1;
  }
  if (json_c_version_num() != (((0 << 16) | (18 << 8)) | 99))
  {
    printf("FAIL: Output from json_c_version_num(): %d does not match %d", json_c_version_num(), ((0 << 16) | (18 << 8)) | 99);
    return 1;
  }
  test_read_valid_with_fd(testdir);
  test_read_valid_nested_with_fd(testdir);
  test_read_nonexistant();
  test_read_closed();
  test_write_to_file();
  test_read_fd_equal(testdir);
  return 0;
}


/*** DEPENDENCIES:
static void test_read_valid_nested_with_fd(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid_nested.json", testdir);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  assert(0 == json_object_from_fd_ex(d, -2));
  json_object *jso = json_object_from_fd_ex(d, 20);
  unsigned int jso_idx = 0;
  if ((&jso[jso_idx]) != 0)
  {
    printf("OK: json_object_from_fd_ex(valid_nested.json, 20)=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    fprintf(stderr, "FAIL: unable to parse contents of %s: %s\n", filename, json_util_get_last_err());
  }
  (void) lseek(d, 0, 0);
  jso_idx = json_object_from_fd_ex(d, 3);
  if ((&jso[jso_idx]) != 0)
  {
    printf("FAIL: json_object_from_fd_ex(%s, 3)=%s\n", filename, json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    printf("OK: correctly unable to parse contents of valid_nested.json with low max depth: %s\n", json_util_get_last_err());
  }
  close(d);
}


----------------------------
int json_c_version_num(void)
{
  return ((0 << 16) | (18 << 8)) | 99;
}


----------------------------
static void test_read_fd_equal(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid_nested.json", testdir);
  json_object *jso = json_object_from_file(filename);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  json_object *new_jso = json_object_from_fd(d);
  close(d);
  printf("OK: json_object_from_file(valid.json)=%s\n", json_object_to_json_string(jso));
  printf("OK: json_object_from_fd(valid.json)=%s\n", json_object_to_json_string(new_jso));
  json_object_put(jso);
  json_object_put(new_jso);
}


----------------------------
static void test_write_to_file(void)
{
  json_object *jso;
  unsigned int jso_idx = 0;
  jso_idx = json_tokener_parse("{\"foo\":1234,\"foo1\":\"abcdefghijklmnopqrstuvwxyz\",\"foo2\":\"abcdefghijklmnopqrstuvwxyz\",\"foo3\":\"abcdefghijklmnopqrstuvwxyz\",\"foo4\":\"abcdefghijklmnopqrstuvwxyz\",\"foo5\":\"abcdefghijklmnopqrstuvwxyz\",\"foo6\":\"abcdefghijklmnopqrstuvwxyz\",\"foo7\":\"abcdefghijklmnopqrstuvwxyz\",\"foo8\":\"abcdefghijklmnopqrstuvwxyz\",\"foo9\":\"abcdefghijklmnopqrstuvwxyz\"}");
  const char *outfile = "json.out";
  int rv = json_object_to_file(outfile, jso);
  printf("%s: json_object_to_file(%s, jso)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile, rv);
  if (rv == 0)
  {
    stat_and_cat(outfile);
  }
  putchar('\n');
  const char *outfile2 = "json2.out";
  rv = json_object_to_file_ext(outfile2, jso, 1 << 1);
  printf("%s: json_object_to_file_ext(%s, jso, JSON_C_TO_STRING_PRETTY)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile2, rv);
  if (rv == 0)
  {
    stat_and_cat(outfile2);
  }
  const char *outfile3 = "json3.out";
  int d = open(outfile3, O_WRONLY | O_CREAT, 0600);
  if (d < 0)
  {
    printf("FAIL: unable to open %s %s\n", outfile3, _json_c_strerror(errno));
    return;
  }
  rv = json_object_to_fd(d, jso, 1 << 1);
  printf("%s: json_object_to_fd(%s, jso, JSON_C_TO_STRING_PRETTY)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile3, rv);
  rv = json_object_to_fd(d, jso, 0);
  printf("%s: json_object_to_fd(%s, jso, JSON_C_TO_STRING_PLAIN)=%d\n", (rv == 0) ? ("OK") : ("FAIL"), outfile3, rv);
  close(d);
  if (rv == 0)
  {
    stat_and_cat(outfile3);
  }
  json_object_put(jso);
}


----------------------------
const char *json_c_version(void)
{
  return "0.18.99";
}


----------------------------
static void test_read_nonexistant(void)
{
  const char *filename = "./not_present.json";
  json_object *jso = json_object_from_file(filename);
  if (jso != 0)
  {
    printf("FAIL: json_object_from_file(%s) returned %p when NULL expected\n", filename, (void *) jso);
    json_object_put(jso);
  }
  else
  {
    printf("OK: json_object_from_file(%s) correctly returned NULL: %s\n", filename, json_util_get_last_err());
  }
}


----------------------------
static void test_read_closed(void)
{
  int d = open("/dev/null", O_RDONLY);
  if (d < 0)
  {
    puts("FAIL: unable to open");
  }
  int fixed_d = 10;
  if (dup2(d, fixed_d) < 0)
  {
    printf("FAIL: unable to dup to fd %d", fixed_d);
  }
  close(d);
  close(fixed_d);
  json_object *jso = json_object_from_fd(fixed_d);
  if (jso != 0)
  {
    printf("FAIL: read from closed fd returning non-NULL: %p\n", (void *) jso);
    fflush(stdout);
    printf("  jso=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
    return;
  }
  printf("OK: json_object_from_fd(closed_fd), expecting NULL, EBADF, got:NULL, %s\n", json_util_get_last_err());
}


----------------------------
static void test_read_valid_with_fd(const char *testdir)
{
  char filename[256];
  (void) snprintf(filename, sizeof(filename), "%s/valid.json", testdir);
  int d = open(filename, O_RDONLY);
  if (d < 0)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", filename, _json_c_strerror(errno));
    exit(1);
  }
  json_object *jso = json_object_from_fd(d);
  if (jso != 0)
  {
    printf("OK: json_object_from_fd(valid.json)=%s\n", json_object_to_json_string(jso));
    json_object_put(jso);
  }
  else
  {
    fprintf(stderr, "FAIL: unable to parse contents of %s: %s\n", filename, json_util_get_last_err());
  }
  close(d);
}


----------------------------
***/


