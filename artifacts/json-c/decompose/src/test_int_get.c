int main(int argc, char **argv)
{
  {
    struct json_object *jtmp = json_object_new_int(5);
    errno = 0;
    assert(json_object_get_int(jtmp) == 5);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int(5);
    errno = 0;
    assert(json_object_get_int64(jtmp) == 5);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int(5);
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 5);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int(0);
    errno = 0;
    assert(json_object_get_int(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int(0);
    errno = 0;
    assert(json_object_get_int64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int(0);
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0");
    errno = 0;
    assert(json_object_get_int(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0");
    errno = 0;
    assert(json_object_get_int64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0");
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("00000");
    errno = 0;
    assert(json_object_get_int(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("00000");
    errno = 0;
    assert(json_object_get_int64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("00000");
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 0);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("000004568789");
    errno = 0;
    assert(json_object_get_int(jtmp) == 4568789);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("000004568789");
    errno = 0;
    assert(json_object_get_int64(jtmp) == 4568789);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("000004568789");
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 4568789);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0xFF");
    errno = 0;
    assert((json_object_get_int(jtmp) == 0) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0xFF");
    errno = 0;
    assert((json_object_get_int64(jtmp) == 0) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("0xFF");
    errno = 0;
    assert((json_object_get_uint64(jtmp) == 0) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("333this_seems_a_valid_string");
    errno = 0;
    assert(json_object_get_int(jtmp) == 333);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("333this_seems_a_valid_string");
    errno = 0;
    assert(json_object_get_int64(jtmp) == 333);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("333this_seems_a_valid_string");
    errno = 0;
    assert(json_object_get_uint64(jtmp) == 333);
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("this_is_not_a_number");
    errno = 0;
    assert((json_object_get_int(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("this_is_not_a_number");
    errno = 0;
    assert((json_object_get_int64(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("this_is_not_a_number");
    errno = 0;
    assert((json_object_get_uint64(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("B0");
    errno = 0;
    assert((json_object_get_int(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("B0");
    errno = 0;
    assert((json_object_get_int64(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("B0");
    errno = 0;
    assert((json_object_get_uint64(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  printf("BASE CHECK PASSED\n");
  {
    struct json_object *jtmp = json_object_new_int64(INT32_MAX);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int64(INT32_MIN);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int64(INT64_MAX);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int64(INT64_MIN);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("2147483647");
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("-2147483648");
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("9223372036854775807");
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("-9223372036854775808");
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(INFINITY);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(-INFINITY);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(NAN);
    errno = 0;
    assert((json_object_get_int(jtmp) == INT32_MIN) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  printf("INT GET PASSED\n");
  {
    struct json_object *jtmp = json_object_new_int64(INT64_MAX);
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_int64(INT64_MIN);
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MIN) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("9223372036854775807");
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("-9223372036854775808");
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MIN) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("9223372036854775808");
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("-9223372036854775809");
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MIN) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(INFINITY);
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(-INFINITY);
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MIN) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(NAN);
    errno = 0;
    assert((json_object_get_int64(jtmp) == INT64_MIN) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  printf("INT64 GET PASSED\n");
  {
    struct json_object *jtmp = json_object_new_uint64(UINT64_MAX);
    errno = 0;
    assert((json_object_get_uint64(jtmp) == UINT64_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_uint64(-1);
    errno = 0;
    assert((json_object_get_uint64(jtmp) == UINT64_MAX) && (errno == 0));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_string("18446744073709551616");
    errno = 0;
    assert((json_object_get_uint64(jtmp) == UINT64_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(INFINITY);
    errno = 0;
    assert((json_object_get_uint64(jtmp) == UINT64_MAX) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(-INFINITY);
    errno = 0;
    assert((json_object_get_uint64(jtmp) == 0) && (errno == ERANGE));
    json_object_put(jtmp);
  }
  ;
  {
    struct json_object *jtmp = json_object_new_double(NAN);
    errno = 0;
    assert((json_object_get_uint64(jtmp) == 0) && (errno == EINVAL));
    json_object_put(jtmp);
  }
  ;
  printf("UINT64 GET PASSED\n");
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
struct json_object *json_object_new_int64(int64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_int64 = i;
  jso->cint_type = json_object_int_type_int64;
  return &jso->base;
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
None
----------------------------
***/


