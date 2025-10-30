int main(int argc, char **argv)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  setlocale(LC_NUMERIC, "de_DE");
  char buf1[10];
  char buf2[10];
  (void) snprintf(buf1, sizeof(buf1), "%f", 0.1);
  if (0)
  {
    mc_set_debug(1);
  }
  new_obj_idx = json_tokener_parse("[1.2,3.4,123456.78,5.0,2.3e10]");
  (void) snprintf(buf2, sizeof(buf2), "%f", 0.1);
  if (strcmp(buf1, buf2) != 0)
  {
    printf("ERROR: Original locale not restored \"%s\" != \"%s\"", buf1, buf2);
  }
  setlocale(LC_NUMERIC, "C");
  printf("new_obj.to_string()=[");
  unsigned int ii;
  for (ii = 0; ii < json_object_array_length(new_obj); ii += 1)
  {
    json_object *val = json_object_array_get_idx(new_obj, ii);
    printf("%s%.2lf", (ii > 0) ? (",") : (""), json_object_get_double(val));
  }

  printf("]\n");
  printf("new_obj.to_string()=%s\n", json_object_to_json_string_ext(new_obj, 1 << 2));
  json_object_put(new_obj);
  return 0;
}


/*** DEPENDENCIES:
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
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
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
None
----------------------------
***/


