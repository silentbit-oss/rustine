static void test_example_int(struct json_object *jo1, const char *json_pointer, int expected_int)
{
  struct json_object *jo2 = 0;
  assert(0 == json_pointer_get(jo1, json_pointer, 0));
  assert(0 == json_pointer_get(jo1, json_pointer, &jo2));
  assert(json_object_is_type(jo2, json_type_int));
  assert(expected_int == json_object_get_int(jo2));
  printf("PASSED - GET -  %s == %d\n", json_pointer, expected_int);
}


/*** DEPENDENCIES:
int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
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


----------------------------
None
----------------------------
***/


static void test_recursion_get(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(rec_input_json_str);
  jo2_idx = 0;
  assert(jo1 != 0);
  printf("%s\n", json_object_get_string(jo1));
  assert(0 == json_pointer_get(jo1, "/arr/0/obj/2/obj1", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_int));
  assert(0 == json_object_get_int(jo2));
  assert(0 == json_pointer_get(jo1, "/arr/0/obj/2/obj2", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(0 == json_pointer_getf(jo1, &(&jo2[jo2_idx]), "/%s/%d/%s/%d/%s", "arr", 0, "obj", 2, "obj2"));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(jo1 != 0);
  assert(0 == json_pointer_get(jo1, "/obj/obj/obj/0/obj1", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_int));
  assert(0 == json_object_get_int(jo2));
  assert(0 == json_pointer_get(jo1, "/obj/obj/obj/0/obj2", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(0 == json_pointer_getf(jo1, &(&jo2[jo2_idx]), "%s", "\0"));
  printf("PASSED - GET - RECURSION TEST\n");
  json_object_put(jo1);
}


/*** DEPENDENCIES:
int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
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
static const char *rec_input_json_str = "{'arr' : [{'obj': [{},{},{'obj1': 0,'obj2': \"1\"}]}],'obj' : {'obj': {'obj': [{'obj1': 0,'obj2': \"1\"}]}}}"
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


static void test_example_get(void)
{
  int i;
  struct json_object *jo1;
  unsigned int jo1_idx = 0;
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo3;
  unsigned int jo3_idx = 0;
  struct json_pointer_map_s_i
  {
    const char *s;
    int i;
  };
  struct json_pointer_map_s_i json_pointers[] = {{"/", 0}, {"/a~1b", 1}, {"/c%d", 2}, {"/e^f", 3}, {"/g|h", 4}, {"/i\\j", 5}, {"/k\"l", 6}, {"/ ", 7}, {"/m~0n", 8}, {0, 0}};
  jo1_idx = json_tokener_parse(input_json_str);
  assert(0 != (&jo1[jo1_idx]));
  printf("PASSED - GET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "", 0));
  assert(0 == json_pointer_get(jo1, "", &(&jo2[jo2_idx])));
  assert(json_object_equal(jo2, jo1));
  printf("PASSED - GET - ENTIRE OBJECT WORKED\n");
  jo3_idx = json_object_new_array();
  json_object_array_add(jo3, json_object_new_string("bar"));
  json_object_array_add(jo3, json_object_new_string("baz"));
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "/foo", 0));
  assert(0 == json_pointer_get(jo1, "/foo", &(&jo2[jo2_idx])));
  assert(0 != (&jo2[jo2_idx]));
  assert(json_object_equal(jo2, jo3));
  json_object_put(jo3);
  printf("PASSED - GET - /foo == ['bar', 'baz']\n");
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "/foo/0", 0));
  assert(0 == json_pointer_get(jo1, "/foo/0", &(&jo2[jo2_idx])));
  assert(0 != (&jo2[jo2_idx]));
  assert(0 == strcmp("bar", json_object_get_string(jo2)));
  printf("PASSED - GET - /foo/0 == 'bar'\n");
  for (i = 0; json_pointers[i].s; i += 1)
  {
    test_example_int(jo1, json_pointers[i].s, json_pointers[i].i);
  }

  json_object_put(jo1);
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
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
None
----------------------------
static const char *input_json_str = "{ 'foo': ['bar', 'baz'], '': 0, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8 }"
----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}


----------------------------
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
static void test_example_int(struct json_object *jo1, const char *json_pointer, int expected_int)
{
  struct json_object *jo2 = 0;
  assert(0 == json_pointer_get(jo1, json_pointer, 0));
  assert(0 == json_pointer_get(jo1, json_pointer, &jo2));
  assert(json_object_is_type(jo2, json_type_int));
  assert(expected_int == json_object_get_int(jo2));
  printf("PASSED - GET -  %s == %d\n", json_pointer, expected_int);
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
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


static void test_wrong_inputs_set(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  assert(jo1 != 0);
  printf("PASSED - SET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  assert(0 != json_pointer_set(0, 0, 0));
  assert(0 != json_pointer_setf(0, 0, 0));
  assert(0 != json_pointer_set(&jo1, 0, 0));
  assert(0 != json_pointer_setf(&jo1, 0, 0));
  printf("PASSED - SET - failed with NULL params for input json & path\n");
  assert(0 != json_pointer_set(&jo1, "foo/bar", jo2_idx = json_object_new_string("cod")));
  printf("PASSED - SET - failed 'cod' with path 'foo/bar'\n");
  json_object_put(jo2);
  assert(0 != json_pointer_setf(&jo1, jo2_idx = json_object_new_string("cod"), "%s", "foo/bar"));
  printf("PASSED - SET - failed 'cod' with path 'foo/bar'\n");
  json_object_put(jo2);
  assert(0 != json_pointer_set(&jo1, "0", jo2_idx = json_object_new_string("cod")));
  printf("PASSED - SET - failed with invalid array index'\n");
  json_object_put(jo2);
  jo2_idx = json_object_new_string("whatever");
  assert(0 != json_pointer_set(&jo1, "/fud/gaw", jo2));
  assert(0 == json_pointer_set(&jo1, "/fud", json_object_new_object()));
  assert(0 == json_pointer_set(&jo1, "/fud/gaw", jo2));
  jo2_idx = json_object_new_int(0);
  assert(0 != json_pointer_set(&jo1, "/fud/gaw/0", jo2));
  json_object_put(jo2);
  jo2_idx = json_object_new_int(0);
  assert(0 != json_pointer_set(&jo1, "/fud/gaw/", jo2));
  json_object_put(jo2);
  printf("PASSED - SET - failed to set index to non-array\n");
  assert(0 == json_pointer_setf(&jo1, json_object_new_string("cod"), "%s", "\0"));
  json_object_put(jo1);
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


----------------------------
static const char *input_json_str = "{ 'foo': ['bar', 'baz'], '': 0, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8 }"
----------------------------
int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value)
{
  return json_pointer_set_with_array_cb(obj, path, value, json_object_array_put_idx_cb, 0);
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
struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
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
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
}


----------------------------
None
----------------------------
***/


static void test_wrong_inputs_get(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  assert(0 != jo1);
  printf("PASSED - GET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  jo2_idx = 0;
  errno = 0;
  assert(0 != json_pointer_get(jo1, "foo/bar", 0));
  assert(0 != json_pointer_get(jo1, "foo/bar", &(&jo2[jo2_idx])));
  assert(errno == EINVAL);
  assert((&jo2[jo2_idx]) == 0);
  printf("PASSED - GET - MISSING /\n");
  errno = 0;
  assert(0 != json_pointer_get(0, "foo/bar", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(0, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(0, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, 0));
  assert(errno == EINVAL);
  printf("PASSED - GET - NULL INPUTS\n");
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/a", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/01", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "/%s/a", "foo"));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/-", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/4", 0));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "%s", "/foo/22"));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "/%s/%d", "foo", 22));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/-1", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/10", 0));
  assert(errno == ENOENT);
  printf("PASSED - GET - INVALID INDEXES\n");
  json_object_put(jo1);
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
static const char *input_json_str = "{ 'foo': ['bar', 'baz'], '': 0, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8 }"
----------------------------
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


static void test_example_set(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  unsigned int jo1_idx = 0;
  assert((&jo1[jo1_idx]) != 0);
  printf("PASSED - SET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/foo/1", json_object_new_string("cod")));
  assert(0 == strcmp("cod", json_object_get_string(json_object_array_get_idx(json_object_object_get(jo1, "foo"), 1))));
  printf("PASSED - SET - 'cod' in /foo/1\n");
  assert(0 != json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw", jo2_idx = json_tokener_parse("[1,2,3]")));
  assert(errno == ENOENT);
  printf("PASSED - SET - non-existing /fud/gaw\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud", json_object_new_object()));
  printf("PASSED - SET - /fud == {}\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw", jo2));
  printf("PASSED - SET - /fug/gaw == [1,2,3]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw/0", json_object_new_int(0)));
  assert(0 == json_pointer_setf(&(&jo1[jo1_idx]), json_object_new_int(0), "%s%s/%d", "/fud", "/gaw", 0));
  printf("PASSED - SET - /fug/gaw == [0,2,3]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw/-", json_object_new_int(4)));
  printf("PASSED - SET - /fug/gaw == [0,2,3,4]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/", json_object_new_int(9)));
  printf("PASSED - SET - / == 9\n");
  jo2_idx = json_tokener_parse("{ 'foo': [ 'bar', 'cod' ], '': 9, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8, 'fud': { 'gaw': [ 0, 2, 3, 4 ] } }");
  assert(json_object_equal(jo2, jo1));
  printf("PASSED - SET - Final JSON is: %s\n", json_object_get_string(jo1));
  json_object_put(jo2);
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "", json_object_new_int(10)));
  assert(10 == json_object_get_int(jo1));
  printf("%s\n", json_object_get_string(jo1));
  json_object_put(jo1);
  jo1_idx = json_tokener_parse("[0, 1, 2, 3]");
  jo2_idx = json_tokener_parse("[0, 1, 2, 3, null, null, null, 7]");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/7", json_object_new_int(7)));
  assert(1 == json_object_equal(jo1, jo2));
  json_object_put(jo1);
  jo1_idx = json_tokener_parse("[0, 1, 2, 3]");
  assert(0 == json_pointer_setf(&(&jo1[jo1_idx]), json_object_new_int(7), "/%u", 7));
  assert(1 == json_object_equal(jo1, jo2));
  json_object_put(jo1);
  json_object_put(jo2);
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
None
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


----------------------------
static const char *input_json_str = "{ 'foo': ['bar', 'baz'], '': 0, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8 }"
----------------------------
int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value)
{
  return json_pointer_set_with_array_cb(obj, path, value, json_object_array_put_idx_cb, 0);
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
struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
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
None
----------------------------
***/


int main(int argc, char **argv)
{
  test_example_get();
  test_recursion_get();
  test_wrong_inputs_get();
  test_example_set();
  test_wrong_inputs_set();
  return 0;
}


/*** DEPENDENCIES:
static void test_recursion_get(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(rec_input_json_str);
  jo2_idx = 0;
  assert(jo1 != 0);
  printf("%s\n", json_object_get_string(jo1));
  assert(0 == json_pointer_get(jo1, "/arr/0/obj/2/obj1", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_int));
  assert(0 == json_object_get_int(jo2));
  assert(0 == json_pointer_get(jo1, "/arr/0/obj/2/obj2", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(0 == json_pointer_getf(jo1, &(&jo2[jo2_idx]), "/%s/%d/%s/%d/%s", "arr", 0, "obj", 2, "obj2"));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(jo1 != 0);
  assert(0 == json_pointer_get(jo1, "/obj/obj/obj/0/obj1", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_int));
  assert(0 == json_object_get_int(jo2));
  assert(0 == json_pointer_get(jo1, "/obj/obj/obj/0/obj2", &(&jo2[jo2_idx])));
  assert(json_object_is_type(jo2, json_type_string));
  assert(0 == strcmp("1", json_object_get_string(jo2)));
  assert(0 == json_pointer_getf(jo1, &(&jo2[jo2_idx]), "%s", "\0"));
  printf("PASSED - GET - RECURSION TEST\n");
  json_object_put(jo1);
}


----------------------------
static void test_example_get(void)
{
  int i;
  struct json_object *jo1;
  unsigned int jo1_idx = 0;
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo3;
  unsigned int jo3_idx = 0;
  struct json_pointer_map_s_i
  {
    const char *s;
    int i;
  };
  struct json_pointer_map_s_i json_pointers[] = {{"/", 0}, {"/a~1b", 1}, {"/c%d", 2}, {"/e^f", 3}, {"/g|h", 4}, {"/i\\j", 5}, {"/k\"l", 6}, {"/ ", 7}, {"/m~0n", 8}, {0, 0}};
  jo1_idx = json_tokener_parse(input_json_str);
  assert(0 != (&jo1[jo1_idx]));
  printf("PASSED - GET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "", 0));
  assert(0 == json_pointer_get(jo1, "", &(&jo2[jo2_idx])));
  assert(json_object_equal(jo2, jo1));
  printf("PASSED - GET - ENTIRE OBJECT WORKED\n");
  jo3_idx = json_object_new_array();
  json_object_array_add(jo3, json_object_new_string("bar"));
  json_object_array_add(jo3, json_object_new_string("baz"));
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "/foo", 0));
  assert(0 == json_pointer_get(jo1, "/foo", &(&jo2[jo2_idx])));
  assert(0 != (&jo2[jo2_idx]));
  assert(json_object_equal(jo2, jo3));
  json_object_put(jo3);
  printf("PASSED - GET - /foo == ['bar', 'baz']\n");
  jo2_idx = 0;
  assert(0 == json_pointer_get(jo1, "/foo/0", 0));
  assert(0 == json_pointer_get(jo1, "/foo/0", &(&jo2[jo2_idx])));
  assert(0 != (&jo2[jo2_idx]));
  assert(0 == strcmp("bar", json_object_get_string(jo2)));
  printf("PASSED - GET - /foo/0 == 'bar'\n");
  for (i = 0; json_pointers[i].s; i += 1)
  {
    test_example_int(jo1, json_pointers[i].s, json_pointers[i].i);
  }

  json_object_put(jo1);
}


----------------------------
static void test_wrong_inputs_set(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  assert(jo1 != 0);
  printf("PASSED - SET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  assert(0 != json_pointer_set(0, 0, 0));
  assert(0 != json_pointer_setf(0, 0, 0));
  assert(0 != json_pointer_set(&jo1, 0, 0));
  assert(0 != json_pointer_setf(&jo1, 0, 0));
  printf("PASSED - SET - failed with NULL params for input json & path\n");
  assert(0 != json_pointer_set(&jo1, "foo/bar", jo2_idx = json_object_new_string("cod")));
  printf("PASSED - SET - failed 'cod' with path 'foo/bar'\n");
  json_object_put(jo2);
  assert(0 != json_pointer_setf(&jo1, jo2_idx = json_object_new_string("cod"), "%s", "foo/bar"));
  printf("PASSED - SET - failed 'cod' with path 'foo/bar'\n");
  json_object_put(jo2);
  assert(0 != json_pointer_set(&jo1, "0", jo2_idx = json_object_new_string("cod")));
  printf("PASSED - SET - failed with invalid array index'\n");
  json_object_put(jo2);
  jo2_idx = json_object_new_string("whatever");
  assert(0 != json_pointer_set(&jo1, "/fud/gaw", jo2));
  assert(0 == json_pointer_set(&jo1, "/fud", json_object_new_object()));
  assert(0 == json_pointer_set(&jo1, "/fud/gaw", jo2));
  jo2_idx = json_object_new_int(0);
  assert(0 != json_pointer_set(&jo1, "/fud/gaw/0", jo2));
  json_object_put(jo2);
  jo2_idx = json_object_new_int(0);
  assert(0 != json_pointer_set(&jo1, "/fud/gaw/", jo2));
  json_object_put(jo2);
  printf("PASSED - SET - failed to set index to non-array\n");
  assert(0 == json_pointer_setf(&jo1, json_object_new_string("cod"), "%s", "\0"));
  json_object_put(jo1);
}


----------------------------
static void test_wrong_inputs_get(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  assert(0 != jo1);
  printf("PASSED - GET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  jo2_idx = 0;
  errno = 0;
  assert(0 != json_pointer_get(jo1, "foo/bar", 0));
  assert(0 != json_pointer_get(jo1, "foo/bar", &(&jo2[jo2_idx])));
  assert(errno == EINVAL);
  assert((&jo2[jo2_idx]) == 0);
  printf("PASSED - GET - MISSING /\n");
  errno = 0;
  assert(0 != json_pointer_get(0, "foo/bar", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(0, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(0, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, 0, 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, 0));
  assert(errno == EINVAL);
  printf("PASSED - GET - NULL INPUTS\n");
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/a", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/01", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "/%s/a", "foo"));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/-", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/4", 0));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "%s", "/foo/22"));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_getf(jo1, 0, "/%s/%d", "foo", 22));
  assert(errno == ENOENT);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/-1", 0));
  assert(errno == EINVAL);
  errno = 0;
  assert(0 != json_pointer_get(jo1, "/foo/10", 0));
  assert(errno == ENOENT);
  printf("PASSED - GET - INVALID INDEXES\n");
  json_object_put(jo1);
}


----------------------------
static void test_example_set(void)
{
  struct json_object *jo2;
  unsigned int jo2_idx = 0;
  struct json_object *jo1 = json_tokener_parse(input_json_str);
  unsigned int jo1_idx = 0;
  assert((&jo1[jo1_idx]) != 0);
  printf("PASSED - SET - LOADED TEST JSON\n");
  printf("%s\n", json_object_get_string(jo1));
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/foo/1", json_object_new_string("cod")));
  assert(0 == strcmp("cod", json_object_get_string(json_object_array_get_idx(json_object_object_get(jo1, "foo"), 1))));
  printf("PASSED - SET - 'cod' in /foo/1\n");
  assert(0 != json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw", jo2_idx = json_tokener_parse("[1,2,3]")));
  assert(errno == ENOENT);
  printf("PASSED - SET - non-existing /fud/gaw\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud", json_object_new_object()));
  printf("PASSED - SET - /fud == {}\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw", jo2));
  printf("PASSED - SET - /fug/gaw == [1,2,3]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw/0", json_object_new_int(0)));
  assert(0 == json_pointer_setf(&(&jo1[jo1_idx]), json_object_new_int(0), "%s%s/%d", "/fud", "/gaw", 0));
  printf("PASSED - SET - /fug/gaw == [0,2,3]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/fud/gaw/-", json_object_new_int(4)));
  printf("PASSED - SET - /fug/gaw == [0,2,3,4]\n");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/", json_object_new_int(9)));
  printf("PASSED - SET - / == 9\n");
  jo2_idx = json_tokener_parse("{ 'foo': [ 'bar', 'cod' ], '': 9, 'a/b': 1, 'c%d': 2, 'e^f': 3, 'g|h': 4, 'i\\\\j': 5, 'k\\\"l': 6, ' ': 7, 'm~n': 8, 'fud': { 'gaw': [ 0, 2, 3, 4 ] } }");
  assert(json_object_equal(jo2, jo1));
  printf("PASSED - SET - Final JSON is: %s\n", json_object_get_string(jo1));
  json_object_put(jo2);
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "", json_object_new_int(10)));
  assert(10 == json_object_get_int(jo1));
  printf("%s\n", json_object_get_string(jo1));
  json_object_put(jo1);
  jo1_idx = json_tokener_parse("[0, 1, 2, 3]");
  jo2_idx = json_tokener_parse("[0, 1, 2, 3, null, null, null, 7]");
  assert(0 == json_pointer_set(&(&jo1[jo1_idx]), "/7", json_object_new_int(7)));
  assert(1 == json_object_equal(jo1, jo2));
  json_object_put(jo1);
  jo1_idx = json_tokener_parse("[0, 1, 2, 3]");
  assert(0 == json_pointer_setf(&(&jo1[jo1_idx]), json_object_new_int(7), "/%u", 7));
  assert(1 == json_object_equal(jo1, jo2));
  json_object_put(jo1);
  json_object_put(jo2);
}


----------------------------
***/


