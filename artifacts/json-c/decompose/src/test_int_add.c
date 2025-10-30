int main(int argc, char **argv)
{
  json_object *tmp = json_object_new_int(123);
  unsigned int tmp_idx = 0;
  json_object_int_inc(tmp, 123);
  assert(json_object_get_int(tmp) == 246);
  json_object_put(tmp);
  printf("INT ADD PASSED\n");
  tmp_idx = json_object_new_int(INT32_MAX);
  json_object_int_inc(tmp, 100);
  assert(json_object_get_int(tmp) == INT32_MAX);
  assert(json_object_get_int64(tmp) == (((int64_t) INT32_MAX) + 100L));
  json_object_put(tmp);
  printf("INT ADD OVERFLOW PASSED\n");
  tmp_idx = json_object_new_int(INT32_MIN);
  json_object_int_inc(tmp, -100);
  assert(json_object_get_int(tmp) == INT32_MIN);
  assert(json_object_get_int64(tmp) == (((int64_t) INT32_MIN) - 100L));
  json_object_put(tmp);
  printf("INT ADD UNDERFLOW PASSED\n");
  tmp_idx = json_object_new_int64(321321321);
  json_object_int_inc(tmp, 321321321);
  assert(json_object_get_int(tmp) == 642642642);
  json_object_put(tmp);
  printf("INT64 ADD PASSED\n");
  tmp_idx = json_object_new_int64(INT64_MAX);
  json_object_int_inc(tmp, 100);
  assert(json_object_get_int64(tmp) == INT64_MAX);
  assert(json_object_get_uint64(tmp) == (((uint64_t) INT64_MAX) + 100U));
  json_object_int_inc(tmp, -100);
  assert(json_object_get_int64(tmp) == INT64_MAX);
  assert(json_object_get_uint64(tmp) == ((uint64_t) INT64_MAX));
  json_object_put(tmp);
  printf("INT64 ADD OVERFLOW PASSED\n");
  tmp_idx = json_object_new_int64(INT64_MIN);
  json_object_int_inc(tmp, -100);
  assert(json_object_get_int64(tmp) == INT64_MIN);
  json_object_int_inc(tmp, 100);
  assert(json_object_get_int64(tmp) != INT64_MIN);
  json_object_put(tmp);
  printf("INT64 ADD UNDERFLOW PASSED\n");
  tmp_idx = json_object_new_uint64(400);
  json_object_int_inc(tmp, -200);
  assert(json_object_get_int64(tmp) == 200);
  assert(json_object_get_uint64(tmp) == 200);
  json_object_int_inc(tmp, 200);
  assert(json_object_get_int64(tmp) == 400);
  assert(json_object_get_uint64(tmp) == 400);
  json_object_put(tmp);
  printf("UINT64 ADD PASSED\n");
  tmp_idx = json_object_new_uint64(UINT64_MAX - 50);
  json_object_int_inc(tmp, 100);
  assert(json_object_get_int64(tmp) == INT64_MAX);
  assert(json_object_get_uint64(tmp) == UINT64_MAX);
  json_object_put(tmp);
  printf("UINT64 ADD OVERFLOW PASSED\n");
  tmp_idx = json_object_new_uint64(100);
  json_object_int_inc(tmp, -200);
  assert(json_object_get_int64(tmp) == (-100));
  assert(json_object_get_uint64(tmp) == 0);
  json_object_put(tmp);
  printf("UINT64 ADD UNDERFLOW PASSED\n");
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
int json_object_int_inc(struct json_object *jso, int64_t val)
{
  struct json_object_int *jsoint;
  unsigned int jsoint_idx = 0;
  if ((!jso) || (jso->o_type != json_type_int))
  {
    return 0;
  }
  jsoint_idx = JC_INT(jso);
  switch (jsoint->cint_type)
  {
    case json_object_int_type_int64:
    {
      if ((val > 0) && (jsoint->cint.c_int64 > (INT64_MAX - val)))
      {
        jsoint->cint.c_uint64 = ((uint64_t) jsoint->cint.c_int64) + ((uint64_t) val);
        jsoint->cint_type = json_object_int_type_uint64;
      }
      else
        if ((val < 0) && (jsoint->cint.c_int64 < (INT64_MIN - val)))
      {
        jsoint->cint.c_int64 = INT64_MIN;
      }
      else
      {
        jsoint->cint.c_int64 += val;
      }
      return 1;
    }

    case json_object_int_type_uint64:
    {
      if ((val > 0) && (jsoint->cint.c_uint64 > (UINT64_MAX - ((uint64_t) val))))
      {
        jsoint->cint.c_uint64 = UINT64_MAX;
      }
      else
        if ((val < 0) && (jsoint->cint.c_uint64 < ((uint64_t) (-val))))
      {
        jsoint->cint.c_int64 = ((int64_t) jsoint->cint.c_uint64) + val;
        jsoint->cint_type = json_object_int_type_int64;
      }
      else
        if ((val < 0) && (jsoint->cint.c_uint64 >= ((uint64_t) (-val))))
      {
        jsoint->cint.c_uint64 -= (uint64_t) (-val);
      }
      else
      {
        jsoint->cint.c_uint64 += val;
      }
      return 1;
    }

    default:
    {
      json_abort("invalid cint_type");
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


