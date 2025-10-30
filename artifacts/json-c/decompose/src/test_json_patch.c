// hint:  ['res_idx_ref is a mutable refrence to unsigned int', 'ret_ref is a mutable refrence to int']
void helper_test_json_patch_op_1(unsigned int * const res_idx_ref, int * const ret_ref, struct json_object * const doc, struct json_object * const patch, struct json_object * const expected, struct json_object * const res, struct json_patch_error jperr)
{
  unsigned int res_idx = *res_idx_ref;
  int ret = *ret_ref;
  ret = json_patch_apply(doc, patch, &(&res[res_idx]), &jperr);
  if (ret)
  {
    fprintf(stderr, "json_patch_apply() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", (res) ? (json_object_get_string(res)) : ("(null)"));
    fprintf(stderr, "json_patch_apply failed: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    fflush(stderr);
    assert(0);
  }
  assert(jperr.errno_code == 0);
  ret = json_object_equal(expected, res);
  if (ret == 0)
  {
    fprintf(stderr, "json_object_equal() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", json_object_get_string(res));
    fflush(stderr);
    assert(0);
  }
  json_object_put(res);
  res_idx = 0;
  printf("OK\n");
  *res_idx_ref = res_idx;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
const char *json_object_get_string(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
    {
      return get_string_component(jso);
    }

    default:
    {
      return json_object_to_json_string(jso);
    }

  }

}


----------------------------
None
----------------------------
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
    helper_json_patch_apply_1(&rc, patch, base, patch_error, ii);
  }

  return rc;
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
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
None
----------------------------
***/


void test_json_patch_op(struct json_object *jo)
{
  const char *comment = json_object_get_string(json_object_object_get(jo, "comment"));
  struct json_object *doc = json_object_object_get(jo, "doc");
  struct json_object *patch = json_object_object_get(jo, "patch");
  struct json_object *expected = 0;
  json_bool have_expected = json_object_object_get_ex(jo, "expected", &expected);
  struct json_object *error = json_object_object_get(jo, "error");
  const char *error_s = json_object_get_string(error);
  struct json_object *res = 0;
  unsigned int res_idx = 0;
  int ret;
  printf("Testing '%s', doc '%s' patch '%s' : ", (comment) ? (comment) : (error_s), json_object_get_string(doc), json_object_get_string(patch));
  if ((!error) && (!have_expected))
  {
    printf("BAD TEST - no expected or error conditions in test: %s\n", json_object_to_json_string(jo));
    assert(0);
  }
  fflush(stdout);
  struct json_patch_error jperr;
  if (error)
  {
    assert((-1) == json_patch_apply(doc, patch, &(&res[res_idx]), &jperr));
    assert(jperr.errno_code != 0);
    printf("OK\n");
    printf(" => json_patch_apply failed as expected: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    json_object_put(res);
  }
  else
  {
    helper_test_json_patch_op_1(&res_idx, &ret, doc, patch, expected, res, jperr);
  }
}


/*** DEPENDENCIES:
struct json_object *json_object_object_get(const struct json_object *jso, const char *key)
{
  struct json_object *result = 0;
  json_object_object_get_ex(jso, key, &result);
  return result;
}


----------------------------
const char *json_object_get_string(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
    {
      return get_string_component(jso);
    }

    default:
    {
      return json_object_to_json_string(jso);
    }

  }

}


----------------------------
typedef int json_bool
----------------------------
json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);
    }

    default:
    {
      if (value != 0)
      {
        *value = 0;
      }
      return 0;
    }

  }

}


----------------------------
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
    helper_json_patch_apply_1(&rc, patch, base, patch_error, ii);
  }

  return rc;
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
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
void helper_test_json_patch_op_1(unsigned int * const res_idx_ref, int * const ret_ref, struct json_object * const doc, struct json_object * const patch, struct json_object * const expected, struct json_object * const res, struct json_patch_error jperr)
{
  unsigned int res_idx = *res_idx_ref;
  int ret = *ret_ref;
  ret = json_patch_apply(doc, patch, &(&res[res_idx]), &jperr);
  if (ret)
  {
    fprintf(stderr, "json_patch_apply() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", (res) ? (json_object_get_string(res)) : ("(null)"));
    fprintf(stderr, "json_patch_apply failed: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    fflush(stderr);
    assert(0);
  }
  assert(jperr.errno_code == 0);
  ret = json_object_equal(expected, res);
  if (ret == 0)
  {
    fprintf(stderr, "json_object_equal() returned '%d'\n", ret);
    fprintf(stderr, "Expected: %s\n", json_object_get_string(expected));
    fprintf(stderr, "Got: %s\n", json_object_get_string(res));
    fflush(stderr);
    assert(0);
  }
  json_object_put(res);
  res_idx = 0;
  printf("OK\n");
  *res_idx_ref = res_idx;
  *ret_ref = ret;
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


void test_json_patch_using_file(const char *testdir, const char *filename)
{
  char full_filename[256];
  (void) snprintf(full_filename, sizeof(full_filename), "%s/%s", testdir, filename);
  size_t ii;
  printf("Testing using file %s\n", filename);
  json_object *jo = json_object_from_file(full_filename);
  if (!jo)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", full_filename, _json_c_strerror(errno));
    exit(1);
  }
  for (ii = 0; ii < json_object_array_length(jo); ii += 1)
  {
    struct json_object *jo1 = json_object_array_get_idx(jo, ii);
    test_json_patch_op(jo1);
  }

  json_object_put(jo);
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
void test_json_patch_op(struct json_object *jo)
{
  const char *comment = json_object_get_string(json_object_object_get(jo, "comment"));
  struct json_object *doc = json_object_object_get(jo, "doc");
  struct json_object *patch = json_object_object_get(jo, "patch");
  struct json_object *expected = 0;
  json_bool have_expected = json_object_object_get_ex(jo, "expected", &expected);
  struct json_object *error = json_object_object_get(jo, "error");
  const char *error_s = json_object_get_string(error);
  struct json_object *res = 0;
  unsigned int res_idx = 0;
  int ret;
  printf("Testing '%s', doc '%s' patch '%s' : ", (comment) ? (comment) : (error_s), json_object_get_string(doc), json_object_get_string(patch));
  if ((!error) && (!have_expected))
  {
    printf("BAD TEST - no expected or error conditions in test: %s\n", json_object_to_json_string(jo));
    assert(0);
  }
  fflush(stdout);
  struct json_patch_error jperr;
  if (error)
  {
    assert((-1) == json_patch_apply(doc, patch, &(&res[res_idx]), &jperr));
    assert(jperr.errno_code != 0);
    printf("OK\n");
    printf(" => json_patch_apply failed as expected: %s at patch idx %zu: %s\n", _json_c_strerror(jperr.errno_code), jperr.patch_failure_idx, jperr.errmsg);
    json_object_put(res);
  }
  else
  {
    helper_test_json_patch_op_1(&res_idx, &ret, doc, patch, expected, res, jperr);
  }
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
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
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
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
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
  test_json_patch_using_file(testdir, "json_patch_spec_tests.json");
  test_json_patch_using_file(testdir, "json_patch_tests.json");
  return 0;
}


/*** DEPENDENCIES:
int json_c_version_num(void)
{
  return ((0 << 16) | (18 << 8)) | 99;
}


----------------------------
void test_json_patch_using_file(const char *testdir, const char *filename)
{
  char full_filename[256];
  (void) snprintf(full_filename, sizeof(full_filename), "%s/%s", testdir, filename);
  size_t ii;
  printf("Testing using file %s\n", filename);
  json_object *jo = json_object_from_file(full_filename);
  if (!jo)
  {
    fprintf(stderr, "FAIL: unable to open %s: %s\n", full_filename, _json_c_strerror(errno));
    exit(1);
  }
  for (ii = 0; ii < json_object_array_length(jo); ii += 1)
  {
    struct json_object *jo1 = json_object_array_get_idx(jo, ii);
    test_json_patch_op(jo1);
  }

  json_object_put(jo);
}


----------------------------
const char *json_c_version(void)
{
  return "0.18.99";
}


----------------------------
***/


