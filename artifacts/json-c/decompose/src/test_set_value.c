int main(int argc, char **argv)
{
  json_object *tmp = json_object_new_int(123);
  unsigned int tmp_idx = 0;
  assert(json_object_get_int(tmp) == 123);
  json_object_set_int(tmp, 321);
  assert(json_object_get_int(tmp) == 321);
  printf("INT PASSED\n");
  json_object_set_int64(tmp, (int64_t) 321321321);
  assert(json_object_get_int64(tmp) == 321321321);
  json_object_put(tmp);
  printf("INT64 PASSED\n");
  tmp_idx = json_object_new_uint64(123);
  assert(json_object_get_boolean(tmp) == 1);
  assert(json_object_get_int(tmp) == 123);
  assert(json_object_get_int64(tmp) == 123);
  assert(json_object_get_uint64(tmp) == 123);
  assert(json_object_get_double(tmp) == 123.000000);
  json_object_set_uint64(tmp, (uint64_t) 321321321);
  assert(json_object_get_uint64(tmp) == 321321321);
  json_object_set_uint64(tmp, 9223372036854775808U);
  assert(json_object_get_int(tmp) == INT32_MAX);
  assert(json_object_get_uint64(tmp) == 9223372036854775808U);
  json_object_put(tmp);
  printf("UINT64 PASSED\n");
  tmp_idx = json_object_new_boolean(1);
  assert(json_object_get_boolean(tmp) == 1);
  json_object_set_boolean(tmp, 0);
  assert(json_object_get_boolean(tmp) == 0);
  json_object_set_boolean(tmp, 1);
  assert(json_object_get_boolean(tmp) == 1);
  json_object_put(tmp);
  printf("BOOL PASSED\n");
  tmp_idx = json_object_new_double(12.34);
  assert(json_object_get_double(tmp) == 12.34);
  json_object_set_double(tmp, 34.56);
  assert(json_object_get_double(tmp) == 34.56);
  json_object_set_double(tmp, 6435.34);
  assert(json_object_get_double(tmp) == 6435.34);
  json_object_set_double(tmp, 2e21);
  assert(json_object_get_int(tmp) == INT32_MAX);
  assert(json_object_get_int64(tmp) == INT64_MAX);
  assert(json_object_get_uint64(tmp) == UINT64_MAX);
  json_object_set_double(tmp, -2e21);
  assert(json_object_get_int(tmp) == INT32_MIN);
  assert(json_object_get_int64(tmp) == INT64_MIN);
  assert(json_object_get_uint64(tmp) == 0);
  json_object_put(tmp);
  printf("DOUBLE PASSED\n");
  tmp_idx = json_object_new_string("A MID STRING");
  assert(strcmp(json_object_get_string(tmp), "A MID STRING") == 0);
  assert(strcmp(json_object_to_json_string(tmp), "\"A MID STRING\"") == 0);
  json_object_set_string(tmp, "SHORT");
  assert(strcmp(json_object_get_string(tmp), "SHORT") == 0);
  assert(strcmp(json_object_to_json_string(tmp), "\"SHORT\"") == 0);
  json_object_set_string(tmp, "A string longer than 32 chars as to check non local buf codepath");
  assert(strcmp(json_object_get_string(tmp), "A string longer than 32 chars as to check non local buf codepath") == 0);
  assert(strcmp(json_object_to_json_string(tmp), "\"A string longer than 32 chars as to check non local buf codepath\"") == 0);
  json_object_set_string(tmp, "SHORT");
  assert(strcmp(json_object_get_string(tmp), "SHORT") == 0);
  assert(strcmp(json_object_to_json_string(tmp), "\"SHORT\"") == 0);
  json_object_set_string(tmp, "");
  json_object_set_string(tmp, "A string longer than 32 chars as to check non local buf codepath");
  json_object_set_string(tmp, "");
  json_object_set_string(tmp, "A string longer than 32 chars as to check non local buf codepath");
  json_object_put(tmp);
  printf("STRING PASSED\n");
  tmp_idx = json_object_new_string("STR");
  assert(json_object_get_double(tmp) == 0.0);
  json_object_set_string(tmp, "123.123");
  assert(json_object_get_double(tmp) == 123.123000);
  json_object_set_string(tmp, "12E+3");
  assert(json_object_get_double(tmp) == 12000.000000);
  json_object_set_string(tmp, "123.123STR");
  assert(json_object_get_double(tmp) == 0.0);
  json_object_set_string(tmp, "1.8E+308");
  assert(json_object_get_double(tmp) == 0.0);
  json_object_set_string(tmp, "-1.8E+308");
  assert(json_object_get_double(tmp) == 0.0);
  json_object_put(tmp);
  printf("STRINGTODOUBLE PASSED\n");
  tmp_idx = json_tokener_parse("1.234");
  json_object_set_double(tmp, 12.3);
  const char *serialized = json_object_to_json_string(tmp);
  fprintf(stderr, "%s\n", serialized);
  assert(strncmp(serialized, "12.3", 4) == 0);
  json_object_put(tmp);
  printf("PARSE AND SET PASSED\n");
  printf("PASSED\n");
  return 0;
}


/*** DEPENDENCIES:
struct json_object *json_object_new_uint64(uint64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_uint64 = i;
  jso->cint_type = json_object_int_type_uint64;
  return &jso->base;
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
int json_object_set_boolean(struct json_object *jso, json_bool new_value)
{
  if ((!jso) || (jso->o_type != json_type_boolean))
  {
    return 0;
  }
  JC_BOOL(jso)->c_boolean = new_value;
  return 1;
}


----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
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
int json_object_set_int(struct json_object *jso, int new_value)
{
  return json_object_set_int64(jso, (int64_t) new_value);
}


----------------------------
uint64_t json_object_get_uint64(const struct json_object *jso)
{
  uint64_t cuint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
        {
          if (jsoint->cint.c_int64 < 0)
          {
            errno = ERANGE;
            return 0;
          }
          return (uint64_t) jsoint->cint.c_int64;
        }

        case json_object_int_type_uint64:
        {
          return jsoint->cint.c_uint64;
        }

        default:
        {
          json_abort("invalid cint_type");
        }

      }

    }

    case json_type_double:
    {
      if (JC_DOUBLE_C(jso)->c_double > ((double) UINT64_MAX))
      {
        errno = ERANGE;
        return UINT64_MAX;
      }
      if (JC_DOUBLE_C(jso)->c_double < 0)
      {
        errno = ERANGE;
        return 0;
      }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
      {
        errno = EINVAL;
        return 0;
      }
      return (uint64_t) JC_DOUBLE_C(jso)->c_double;
    }

    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    case json_type_string:
    {
      if (json_parse_uint64(get_string_component(jso), &cuint) == 0)
      {
        return cuint;
      }
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
int json_object_set_uint64(struct json_object *jso, uint64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_uint64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_uint64;
  return 1;
}


----------------------------
int json_object_set_int64(struct json_object *jso, int64_t new_value)
{
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  JC_INT(jso)->cint.c_int64 = new_value;
  JC_INT(jso)->cint_type = json_object_int_type_int64;
  return 1;
}


----------------------------
int64_t json_object_get_int64(const struct json_object *jso)
{
  int64_t cint;
  errno = 0;
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_int:
    {
      const struct json_object_int *jsoint = JC_INT_C(jso);
      switch (jsoint->cint_type)
      {
        case json_object_int_type_int64:
        {
          return jsoint->cint.c_int64;
        }

        case json_object_int_type_uint64:
        {
          if (jsoint->cint.c_uint64 > INT64_MAX)
          {
            errno = ERANGE;
            return INT64_MAX;
          }
          return (int64_t) jsoint->cint.c_uint64;
        }

        default:
        {
          json_abort("invalid cint_type");
        }

      }

    }

    case json_type_double:
    {
      if (JC_DOUBLE_C(jso)->c_double > ((double) INT64_MAX))
      {
        errno = ERANGE;
        return INT64_MAX;
      }
      if (JC_DOUBLE_C(jso)->c_double < ((double) INT64_MIN))
      {
        errno = ERANGE;
        return INT64_MIN;
      }
      if (isnan(JC_DOUBLE_C(jso)->c_double))
      {
        errno = EINVAL;
        return INT64_MIN;
      }
      return (int64_t) JC_DOUBLE_C(jso)->c_double;
    }

    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    case json_type_string:
    {
      if (json_parse_int64(get_string_component(jso), &cint) == 0)
      {
        return cint;
      }
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
json_bool json_object_get_boolean(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    case json_type_int:
    {
      switch (JC_INT_C(jso)->cint_type)
      {
        case json_object_int_type_int64:
        {
          return JC_INT_C(jso)->cint.c_int64 != 0;
        }

        case json_object_int_type_uint64:
        {
          return JC_INT_C(jso)->cint.c_uint64 != 0;
        }

        default:
        {
          json_abort("invalid cint_type");
        }

      }

    }

    case json_type_double:
    {
      return JC_DOUBLE_C(jso)->c_double != 0;
    }

    case json_type_string:
    {
      return JC_STRING_C(jso)->len != 0;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
int json_object_set_string(json_object *jso, const char *s)
{
  return _json_object_set_string_len(jso, s, strlen(s));
}


----------------------------
int json_object_set_double(struct json_object *jso, double new_value)
{
  if ((!jso) || (jso->o_type != json_type_double))
  {
    return 0;
  }
  JC_DOUBLE(jso)->c_double = new_value;
  if (jso->_to_json_string == (&_json_object_userdata_to_json_string))
  {
    json_object_set_serializer(jso, 0, 0, 0);
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
double json_object_get_double(const struct json_object *jso)
{
  double cdouble;
  char *errPtr = 0;
  if (!jso)
  {
    return 0.0;
  }
  switch (jso->o_type)
  {
    case json_type_double:
    {
      return JC_DOUBLE_C(jso)->c_double;
    }

    case json_type_int:
    {
      switch (JC_INT_C(jso)->cint_type)
      {
        case json_object_int_type_int64:
        {
          return JC_INT_C(jso)->cint.c_int64;
        }

        case json_object_int_type_uint64:
        {
          return JC_INT_C(jso)->cint.c_uint64;
        }

        default:
        {
          json_abort("invalid cint_type");
        }

      }

    }

    case json_type_boolean:
    {
      return JC_BOOL_C(jso)->c_boolean;
    }

    case json_type_string:
    {
      errno = 0;
      cdouble = strtod(get_string_component(jso), &errPtr);
      if (errPtr == get_string_component(jso))
      {
        errno = EINVAL;
        return 0.0;
      }
      if ((*errPtr) != '\0')
      {
        errno = EINVAL;
        return 0.0;
      }
      if (((HUGE_VAL == cdouble) || ((-HUGE_VAL) == cdouble)) && (ERANGE == errno))
      {
        cdouble = 0.0;
      }
      return cdouble;
    }

    default:
    {
      errno = EINVAL;
      return 0.0;
    }

  }

}


----------------------------
struct json_object *json_object_new_double(double d)
{
  struct json_object_double *jso = (struct json_object_double *) json_object_new(json_type_double, sizeof(struct json_object_double), &json_object_double_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->base._to_json_string = &json_object_double_to_json_string_default;
  jso->c_double = d;
  return &jso->base;
}


----------------------------
None
----------------------------
***/


