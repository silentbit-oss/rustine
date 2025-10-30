static int sort_fn(const void *j1, const void *j2)
{
  json_object * const *jso1;
  unsigned int jso1_idx = 0;
  json_object * const *jso2;
  unsigned int jso2_idx = 0;
  int i1;
  int i2;
  jso1_idx = (json_object * const *) j1;
  jso2_idx = (json_object * const *) j2;
  if ((!(*(&jso1[jso1_idx]))) && (!(*(&jso2[jso2_idx]))))
  {
    return 0;
  }
  if (!(*(&jso1[jso1_idx])))
  {
    return -1;
  }
  if (!(*(&jso2[jso2_idx])))
  {
    return 1;
  }
  i1 = json_object_get_int(*(&jso1[jso1_idx]));
  i2 = json_object_get_int(*(&jso2[jso2_idx]));
  return i1 - i2;
}


/*** DEPENDENCIES:
int32_t json_object_get_int(const struct json_object *jso)
{
  int64_t cint64 = 0;
  double cdouble;
  enum json_type o_type;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  o_type = jso->o_type;
  if (o_type == json_type_int)
  {
    const struct json_object_int *jsoint = JC_INT_C(jso);
    if (jsoint->cint_type == json_object_int_type_int64)
    {
      cint64 = jsoint->cint.c_int64;
    }
    else
    {
      if (jsoint->cint.c_uint64 >= INT64_MAX)
      {
        cint64 = INT64_MAX;
      }
      else
        cint64 = (int64_t) jsoint->cint.c_uint64;
    }
  }
  else
    if (o_type == json_type_string)
  {
    if (json_parse_int64(get_string_component(jso), &cint64) != 0)
    {
      return 0;
    }
    o_type = json_type_int;
  }
  switch (o_type)
  {
    case json_type_int:
    {
      if (cint64 < INT32_MIN)
      {
        errno = ERANGE;
        return INT32_MIN;
      }
      if (cint64 > INT32_MAX)
      {
        errno = ERANGE;
        return INT32_MAX;
      }
      return (int32_t) cint64;
    }

    case json_type_double:
    {
      helper_json_object_get_int_1(&cdouble, jso);
    }

    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
None
----------------------------
***/


json_object *make_array(void)
{
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_put_idx(my_array, 4, json_object_new_int(5));
  json_object_array_put_idx(my_array, 3, json_object_new_int(4));
  json_object_array_put_idx(my_array, 6, json_object_new_int(7));
  return my_array;
}


/*** DEPENDENCIES:
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}


----------------------------
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


void test_array_list_expand_internal(void)
{
  int rc;
  size_t ii;
  size_t idx;
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = make_array();
  printf("my_array=\n");
  for (ii = 0; ii < json_object_array_length(my_array); ii += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, ii);
    printf("\t[%d]=%s\n", (int) ii, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  rc = json_object_array_put_idx(my_array, 5, json_object_new_int(6));
  printf("put_idx(5,6)=%d\n", rc);
  idx = (32 * 2) - 1;
  rc = json_object_array_put_idx(my_array, idx, json_object_new_int(0));
  printf("put_idx(%d,0)=%d\n", (int) idx, rc);
  idx = ((32 * 2) * 2) + 1;
  rc = json_object_array_put_idx(my_array, idx, json_object_new_int(0));
  printf("put_idx(%d,0)=%d\n", (int) idx, rc);
  idx = SIZE_MAX;
  json_object *tmp = json_object_new_int(10);
  rc = json_object_array_put_idx(my_array, idx, tmp);
  printf("put_idx(SIZE_T_MAX,0)=%d\n", rc);
  if (rc == (-1))
  {
    json_object_put(tmp);
  }
  json_object_put(my_array);
}


/*** DEPENDENCIES:
json_object *make_array(void)
{
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_put_idx(my_array, 4, json_object_new_int(5));
  json_object_array_put_idx(my_array, 3, json_object_new_int(4));
  json_object_array_put_idx(my_array, 6, json_object_new_int(7));
  return my_array;
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
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
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}


----------------------------
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
None
----------------------------
***/


void test_array_insert_idx(void)
{
  json_object *my_array;
  unsigned int my_array_idx = 0;
  struct json_object *jo1;
  unsigned int jo1_idx = 0;
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(5));
  json_object_array_insert_idx(my_array, 2, json_object_new_int(4));
  jo1_idx = json_tokener_parse("[1, 2, 4, 5]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 2, json_object_new_int(3));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 5, json_object_new_int(6));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5, 6]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 7, json_object_new_int(8));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5, 6, null, 8]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_put(my_array);
}


/*** DEPENDENCIES:
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
int json_object_array_insert_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_insert_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
None
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
struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
}


----------------------------
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}


----------------------------
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


void test_array_del_idx(void)
{
  int rc;
  size_t ii;
  size_t orig_array_len;
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = make_array();
  orig_array_len = json_object_array_length(my_array);
  printf("my_array=\n");
  for (ii = 0; ii < json_object_array_length(my_array); ii += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, ii);
    printf("\t[%d]=%s\n", (int) ii, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  for (ii = 0; ii < orig_array_len; ii += 1)
  {
    rc = json_object_array_del_idx(my_array, 0, 1);
    printf("after del_idx(0,1)=%d, my_array.to_string()=%s\n", rc, json_object_to_json_string(my_array));
  }

  rc = json_object_array_del_idx(my_array, 0, 1);
  printf("after del_idx(0,1)=%d, my_array.to_string()=%s\n", rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) orig_array_len, rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len + 1);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) (orig_array_len + 1), rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len - 1);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) (orig_array_len - 1), rc, json_object_to_json_string(my_array));
  json_object_array_add(my_array, json_object_new_string("s1"));
  json_object_array_add(my_array, json_object_new_string("s2"));
  json_object_array_add(my_array, json_object_new_string("s3"));
  printf("after adding more entries, my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  json_object_put(my_array);
}


/*** DEPENDENCIES:
json_object *make_array(void)
{
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_put_idx(my_array, 4, json_object_new_int(5));
  json_object_array_put_idx(my_array, 3, json_object_new_int(4));
  json_object_array_put_idx(my_array, 6, json_object_new_int(7));
  return my_array;
}


----------------------------
int json_object_array_del_idx(struct json_object *jso, size_t idx, size_t count)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_del_idx(JC_ARRAY(jso)->c_array, idx, count);
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}


----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
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
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


int main(int argc, char **argv)
{
  json_object *my_string;
  unsigned int my_string_idx = 0;
  json_object *my_int;
  unsigned int my_int_idx = 0;
  json_object *my_null;
  unsigned int my_null_idx = 0;
  json_object *my_object;
  unsigned int my_object_idx = 0;
  json_object *my_array;
  unsigned int my_array_idx = 0;
  size_t i;
  if (0)
  {
    mc_set_debug(1);
  }
  my_string_idx = json_object_new_string("\t");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  json_object_put(my_string);
  my_string_idx = json_object_new_string("\\");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  json_object_put(my_string);
  my_string_idx = json_object_new_string("/");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  printf("my_string.to_string(NOSLASHESCAPE)=%s\n", json_object_to_json_string_ext(my_string, 1 << 4));
  json_object_put(my_string);
  my_string_idx = json_object_new_string("/foo/bar/baz");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  printf("my_string.to_string(NOSLASHESCAPE)=%s\n", json_object_to_json_string_ext(my_string, 1 << 4));
  json_object_put(my_string);
  my_string_idx = json_object_new_string("foo");
  printf("my_string=%s\n", json_object_get_string(my_string));
  printf("my_string.to_string()=%s\n", json_object_to_json_string(my_string));
  my_int_idx = json_object_new_int(9);
  printf("my_int=%d\n", json_object_get_int(my_int));
  printf("my_int.to_string()=%s\n", json_object_to_json_string(my_int));
  my_null_idx = json_object_new_null();
  printf("my_null.to_string()=%s\n", json_object_to_json_string(my_null));
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_put_idx(my_array, 4, json_object_new_int(5));
  printf("my_array=\n");
  for (i = 0; i < json_object_array_length(my_array); i += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, i);
    printf("\t[%d]=%s\n", (int) i, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  json_object_put(my_array);
  test_array_insert_idx();
  test_array_del_idx();
  test_array_list_expand_internal();
  my_array_idx = json_object_new_array_ext(5);
  json_object_array_add(my_array, json_object_new_int(3));
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_put_idx(my_array, 4, json_object_new_int(0));
  printf("my_array=\n");
  for (i = 0; i < json_object_array_length(my_array); i += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, i);
    printf("\t[%d]=%s\n", (int) i, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  json_object_array_sort(my_array, sort_fn);
  printf("my_array=\n");
  for (i = 0; i < json_object_array_length(my_array); i += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, i);
    printf("\t[%d]=%s\n", (int) i, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  json_object *one = json_object_new_int(1);
  json_object *result = json_object_array_bsearch(one, my_array, sort_fn);
  printf("find json_object(1) in my_array successfully: %s\n", json_object_to_json_string(result));
  json_object_put(one);
  my_object_idx = json_object_new_object();
  int rc = json_object_object_add(my_object, "abc", my_object);
  if (rc != (-1))
  {
    printf("ERROR: able to successfully add object to itself!\n");
    fflush(stdout);
  }
  json_object_object_add(my_object, "abc", json_object_new_int(12));
  json_object_object_add(my_object, "foo", json_object_new_string("bar"));
  json_object_object_add(my_object, "bool0", json_object_new_boolean(0));
  json_object_object_add(my_object, "bool1", json_object_new_boolean(1));
  json_object_object_add(my_object, "baz", json_object_new_string("bang"));
  json_object *baz_obj = json_object_new_string("fark");
  json_object_get(baz_obj);
  json_object_object_add(my_object, "baz", baz_obj);
  json_object_object_del(my_object, "baz");
  printf("baz_obj.to_string()=%s\n", json_object_to_json_string(baz_obj));
  json_object_put(baz_obj);
  printf("my_object=\n");
  char *key = 0;
  unsigned int key_idx = 0;
  struct json_object *val = 0;
  unsigned int val_idx = 0;
  for (struct lh_entry *entrykey = lh_table_head(json_object_get_object(my_object)), entry_nextkey = 0;   {
    if (entrykey)
    {
      key_idx = (char *) lh_entry_k(entrykey);
      val_idx = (struct json_object *) lh_entry_v(entrykey);
      entry_nextkey_idx = lh_entry_next(entrykey);
    }
    ;
    entrykey;
  }
; entrykey_idx = &entry_nextkey[entry_nextkey_idx])
  {
    printf("\t%s: %s\n", key, json_object_to_json_string(val));
  }

  unsigned int entry_nextkey_idx = 0;
  json_object *empty_array = json_object_new_array();
  json_object *empty_obj = json_object_new_object();
  json_object_object_add(my_object, "empty_array", empty_array);
  json_object_object_add(my_object, "empty_obj", empty_obj);
  printf("my_object.to_string()=%s\n", json_object_to_json_string(my_object));
  json_object_put(my_array);
  my_array_idx = json_object_new_array_ext((-2147483648) + 1);
  if ((&my_array[my_array_idx]) != 0)
  {
    printf("ERROR: able to allocate an array of negative size!\n");
    fflush(stdout);
    json_object_put(my_array);
    my_array_idx = 0;
  }
  json_object_put(my_string);
  json_object_put(my_int);
  json_object_put(my_null);
  json_object_put(my_object);
  json_object_put(my_array);
  return 0;
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
struct json_object *json_object_get(struct json_object *jso)
{
  if (!jso)
  {
    return jso;
  }
  assert(jso->_ref_count < UINT32_MAX);
  jso->_ref_count += 1;
  return jso;
}


----------------------------
int32_t json_object_get_int(const struct json_object *jso)
{
  int64_t cint64 = 0;
  double cdouble;
  enum json_type o_type;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  o_type = jso->o_type;
  if (o_type == json_type_int)
  {
    const struct json_object_int *jsoint = JC_INT_C(jso);
    if (jsoint->cint_type == json_object_int_type_int64)
    {
      cint64 = jsoint->cint.c_int64;
    }
    else
    {
      if (jsoint->cint.c_uint64 >= INT64_MAX)
      {
        cint64 = INT64_MAX;
      }
      else
        cint64 = (int64_t) jsoint->cint.c_uint64;
    }
  }
  else
    if (o_type == json_type_string)
  {
    if (json_parse_int64(get_string_component(jso), &cint64) != 0)
    {
      return 0;
    }
    o_type = json_type_int;
  }
  switch (o_type)
  {
    case json_type_int:
    {
      if (cint64 < INT32_MIN)
      {
        errno = ERANGE;
        return INT32_MIN;
      }
      if (cint64 > INT32_MAX)
      {
        errno = ERANGE;
        return INT32_MAX;
      }
      return (int32_t) cint64;
    }

    case json_type_double:
    {
      helper_json_object_get_int_1(&cdouble, jso);
    }

    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
struct json_object *json_object_new_array_ext(int initial_size)
{
  struct json_object_array *jso = (struct json_object_array *) json_object_new(json_type_array, sizeof(struct json_object_array), &json_object_array_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_array = array_list_new2(&json_object_array_entry_free, initial_size);
  if (jso->c_array == 0)
  {
    free(jso);
    return 0;
  }
  return &jso->base;
}


----------------------------
void json_object_object_del(struct json_object *jso, const char *key)
{
  assert(json_object_get_type(jso) == json_type_object);
  lh_table_delete(JC_OBJECT(jso)->c_object, key);
}


----------------------------
void test_array_del_idx(void)
{
  int rc;
  size_t ii;
  size_t orig_array_len;
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = make_array();
  orig_array_len = json_object_array_length(my_array);
  printf("my_array=\n");
  for (ii = 0; ii < json_object_array_length(my_array); ii += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, ii);
    printf("\t[%d]=%s\n", (int) ii, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  for (ii = 0; ii < orig_array_len; ii += 1)
  {
    rc = json_object_array_del_idx(my_array, 0, 1);
    printf("after del_idx(0,1)=%d, my_array.to_string()=%s\n", rc, json_object_to_json_string(my_array));
  }

  rc = json_object_array_del_idx(my_array, 0, 1);
  printf("after del_idx(0,1)=%d, my_array.to_string()=%s\n", rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) orig_array_len, rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len + 1);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) (orig_array_len + 1), rc, json_object_to_json_string(my_array));
  json_object_put(my_array);
  my_array_idx = make_array();
  rc = json_object_array_del_idx(my_array, 0, orig_array_len - 1);
  printf("after del_idx(0,%d)=%d, my_array.to_string()=%s\n", (int) (orig_array_len - 1), rc, json_object_to_json_string(my_array));
  json_object_array_add(my_array, json_object_new_string("s1"));
  json_object_array_add(my_array, json_object_new_string("s2"));
  json_object_array_add(my_array, json_object_new_string("s3"));
  printf("after adding more entries, my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  json_object_put(my_array);
}


----------------------------
struct lh_table *json_object_get_object(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return JC_OBJECT_C(jso)->c_object;
    }

    default:
    {
      return 0;
    }

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
struct json_object *json_object_new_boolean(json_bool b)
{
  struct json_object_boolean *jso = (struct json_object_boolean *) json_object_new(json_type_boolean, sizeof(struct json_object_boolean), &json_object_boolean_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_boolean = b;
  return &jso->base;
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
static int sort_fn(const void *j1, const void *j2)
{
  json_object * const *jso1;
  unsigned int jso1_idx = 0;
  json_object * const *jso2;
  unsigned int jso2_idx = 0;
  int i1;
  int i2;
  jso1_idx = (json_object * const *) j1;
  jso2_idx = (json_object * const *) j2;
  if ((!(*(&jso1[jso1_idx]))) && (!(*(&jso2[jso2_idx]))))
  {
    return 0;
  }
  if (!(*(&jso1[jso1_idx])))
  {
    return -1;
  }
  if (!(*(&jso2[jso2_idx])))
  {
    return 1;
  }
  i1 = json_object_get_int(*(&jso1[jso1_idx]));
  i2 = json_object_get_int(*(&jso2[jso2_idx]));
  return i1 - i2;
}


----------------------------
struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  struct json_object **result;
  unsigned int result_idx = 0;
  assert(json_object_get_type(jso) == json_type_array);
  result_idx = (struct json_object **) array_list_bsearch((const void **) ((void *) (&key)), JC_ARRAY_C(jso)->c_array, sort_fn);
  if (!(&result[result_idx]))
  {
    return 0;
  }
  return result[result_idx];
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}


----------------------------
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}


----------------------------
void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *))
{
  assert(json_object_get_type(jso) == json_type_array);
  array_list_sort(JC_ARRAY(jso)->c_array, sort_fn);
}


----------------------------
void test_array_list_expand_internal(void)
{
  int rc;
  size_t ii;
  size_t idx;
  json_object *my_array;
  unsigned int my_array_idx = 0;
  my_array_idx = make_array();
  printf("my_array=\n");
  for (ii = 0; ii < json_object_array_length(my_array); ii += 1)
  {
    json_object *obj = json_object_array_get_idx(my_array, ii);
    printf("\t[%d]=%s\n", (int) ii, json_object_to_json_string(obj));
  }

  printf("my_array.to_string()=%s\n", json_object_to_json_string(my_array));
  rc = json_object_array_put_idx(my_array, 5, json_object_new_int(6));
  printf("put_idx(5,6)=%d\n", rc);
  idx = (32 * 2) - 1;
  rc = json_object_array_put_idx(my_array, idx, json_object_new_int(0));
  printf("put_idx(%d,0)=%d\n", (int) idx, rc);
  idx = ((32 * 2) * 2) + 1;
  rc = json_object_array_put_idx(my_array, idx, json_object_new_int(0));
  printf("put_idx(%d,0)=%d\n", (int) idx, rc);
  idx = SIZE_MAX;
  json_object *tmp = json_object_new_int(10);
  rc = json_object_array_put_idx(my_array, idx, tmp);
  printf("put_idx(SIZE_T_MAX,0)=%d\n", rc);
  if (rc == (-1))
  {
    json_object_put(tmp);
  }
  json_object_put(my_array);
}


----------------------------
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}


----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}


----------------------------
struct json_object *json_object_new_object(void)
{
  struct json_object_object *jso = (struct json_object_object *) json_object_new(json_type_object, sizeof(struct json_object_object), &json_object_object_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_object = lh_kchar_table_new(16, &json_object_lh_entry_free);
  if (!jso->c_object)
  {
    json_object_generic_delete(&jso->base);
    errno = ENOMEM;
    return 0;
  }
  return &jso->base;
}


----------------------------
inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
}


----------------------------
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}


----------------------------
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}


----------------------------
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
void test_array_insert_idx(void)
{
  json_object *my_array;
  unsigned int my_array_idx = 0;
  struct json_object *jo1;
  unsigned int jo1_idx = 0;
  my_array_idx = json_object_new_array();
  json_object_array_add(my_array, json_object_new_int(1));
  json_object_array_add(my_array, json_object_new_int(2));
  json_object_array_add(my_array, json_object_new_int(5));
  json_object_array_insert_idx(my_array, 2, json_object_new_int(4));
  jo1_idx = json_tokener_parse("[1, 2, 4, 5]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 2, json_object_new_int(3));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 5, json_object_new_int(6));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5, 6]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_array_insert_idx(my_array, 7, json_object_new_int(8));
  jo1_idx = json_tokener_parse("[1, 2, 3, 4, 5, 6, null, 8]");
  assert(1 == json_object_equal(my_array, jo1));
  json_object_put(jo1);
  json_object_put(my_array);
}


----------------------------
struct json_object *json_object_new_null(void)
{
  return 0;
}


----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


