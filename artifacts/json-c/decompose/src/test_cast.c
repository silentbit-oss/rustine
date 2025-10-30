static void checktype_header(void)
{
  printf("json_object_is_type: %s,%s,%s,%s,%s,%s,%s\n", json_type_to_name(json_type_null), json_type_to_name(json_type_boolean), json_type_to_name(json_type_double), json_type_to_name(json_type_int), json_type_to_name(json_type_object), json_type_to_name(json_type_array), json_type_to_name(json_type_string));
}


/*** DEPENDENCIES:
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


----------------------------
***/


static void checktype(struct json_object *new_obj, const char *field)
{
  struct json_object *o = new_obj;
  if (field && (!json_object_object_get_ex(new_obj, field, &o)))
  {
    printf("Field %s does not exist\n", field);
  }
  printf("new_obj%s%-18s: %d,%d,%d,%d,%d,%d,%d\n", (field) ? (".") : (" "), (field) ? (field) : (""), json_object_is_type(o, json_type_null), json_object_is_type(o, json_type_boolean), json_object_is_type(o, json_type_double), json_object_is_type(o, json_type_int), json_object_is_type(o, json_type_object), json_object_is_type(o, json_type_array), json_object_is_type(o, json_type_string));
}


/*** DEPENDENCIES:
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
int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
}


----------------------------
None
----------------------------
***/


static void getit(struct json_object *new_obj, const char *field)
{
  struct json_object *o = 0;
  if (!json_object_object_get_ex(new_obj, field, &o))
  {
    printf("Field %s does not exist\n", field);
  }
  enum json_type o_type = json_object_get_type(o);
  printf("new_obj.%s json_object_get_type()=%s\n", field, json_type_to_name(o_type));
  printf("new_obj.%s json_object_get_int()=%d\n", field, json_object_get_int(o));
  printf("new_obj.%s json_object_get_int64()=%d\n", field, json_object_get_int64(o));
  printf("new_obj.%s json_object_get_uint64()=%u\n", field, json_object_get_uint64(o));
  printf("new_obj.%s json_object_get_boolean()=%d\n", field, json_object_get_boolean(o));
  printf("new_obj.%s json_object_get_double()=%f\n", field, json_object_get_double(o));
}


/*** DEPENDENCIES:
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
enum json_type json_object_get_type(const struct json_object *jso)
{
  if (!jso)
  {
    return json_type_null;
  }
  return jso->o_type;
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


int main(int argc, char **argv)
{
  const char *input = "{\n		\"string_of_digits\": \"123\",\n		\"regular_number\": 222,\n		\"decimal_number\": 99.55,\n		\"boolean_true\": true,\n		\"boolean_false\": false,\n		\"int64_number\": 2147483649,\n		\"negative_number\": -321321321,\n		\"a_null\": null,\n		\"empty_array\": [],\n		\"nonempty_array\": [ 123 ],\n		\"array_with_zero\": [ 0 ],\n		\"empty_object\": {},\n		\"nonempty_object\": { \"a\": 123 },\n		\"nan\": NaN,\n	}";
  struct json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(input);
  printf("Parsed input: %s\n", input);
  printf("Result is %s\n", ((&new_obj[new_obj_idx]) == 0) ? ("NULL (error!)") : ("not NULL"));
  if (!(&new_obj[new_obj_idx]))
  {
    return 1;
  }
  getit(new_obj, "string_of_digits");
  getit(new_obj, "regular_number");
  getit(new_obj, "decimal_number");
  getit(new_obj, "boolean_true");
  getit(new_obj, "boolean_false");
  getit(new_obj, "int64_number");
  getit(new_obj, "negative_number");
  getit(new_obj, "a_null");
  getit(new_obj, "empty_array");
  getit(new_obj, "nonempty_array");
  getit(new_obj, "array_with_zero");
  getit(new_obj, "empty_object");
  getit(new_obj, "nonempty_object");
  getit(new_obj, "nan");
  printf("\n================================\n");
  checktype_header();
  checktype(new_obj, 0);
  checktype(new_obj, "string_of_digits");
  checktype(new_obj, "regular_number");
  checktype(new_obj, "decimal_number");
  checktype(new_obj, "boolean_true");
  checktype(new_obj, "boolean_false");
  checktype(new_obj, "int64_number");
  checktype(new_obj, "negative_number");
  checktype(new_obj, "a_null");
  checktype(new_obj, "nan");
  json_object_put(new_obj);
  return 0;
}


/*** DEPENDENCIES:
static void checktype_header(void)
{
  printf("json_object_is_type: %s,%s,%s,%s,%s,%s,%s\n", json_type_to_name(json_type_null), json_type_to_name(json_type_boolean), json_type_to_name(json_type_double), json_type_to_name(json_type_int), json_type_to_name(json_type_object), json_type_to_name(json_type_array), json_type_to_name(json_type_string));
}


----------------------------
static void getit(struct json_object *new_obj, const char *field)
{
  struct json_object *o = 0;
  if (!json_object_object_get_ex(new_obj, field, &o))
  {
    printf("Field %s does not exist\n", field);
  }
  enum json_type o_type = json_object_get_type(o);
  printf("new_obj.%s json_object_get_type()=%s\n", field, json_type_to_name(o_type));
  printf("new_obj.%s json_object_get_int()=%d\n", field, json_object_get_int(o));
  printf("new_obj.%s json_object_get_int64()=%d\n", field, json_object_get_int64(o));
  printf("new_obj.%s json_object_get_uint64()=%u\n", field, json_object_get_uint64(o));
  printf("new_obj.%s json_object_get_boolean()=%d\n", field, json_object_get_boolean(o));
  printf("new_obj.%s json_object_get_double()=%f\n", field, json_object_get_double(o));
}


----------------------------
static void checktype(struct json_object *new_obj, const char *field)
{
  struct json_object *o = new_obj;
  if (field && (!json_object_object_get_ex(new_obj, field, &o)))
  {
    printf("Field %s does not exist\n", field);
  }
  printf("new_obj%s%-18s: %d,%d,%d,%d,%d,%d,%d\n", (field) ? (".") : (" "), (field) ? (field) : (""), json_object_is_type(o, json_type_null), json_object_is_type(o, json_type_boolean), json_object_is_type(o, json_type_double), json_object_is_type(o, json_type_int), json_object_is_type(o, json_type_object), json_object_is_type(o, json_type_array), json_object_is_type(o, json_type_string));
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
None
----------------------------
***/


