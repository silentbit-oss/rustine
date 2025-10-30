int main(void)
{
  json_object *json;
  unsigned int json_idx = 0;
  json_idx = json_object_new_double(1.0);
  printf("json = %s\n", json_object_to_json_string_ext(json, 1 << 1));
  json_object_put(json);
  json_idx = json_object_new_double(-1.0);
  printf("json = %s\n", json_object_to_json_string_ext(json, 1 << 1));
  json_object_put(json);
  json_idx = json_object_new_double(1.23);
  printf("json = %s\n", json_object_to_json_string_ext(json, 1 << 1));
  json_object_put(json);
  json_idx = json_object_new_double(123456789.0);
  printf("json = %s\n", json_object_to_json_string_ext(json, 1 << 1));
  json_object_put(json);
  json_idx = json_object_new_double(123456789.123);
  printf("json = %s\n", json_object_to_json_string_ext(json, 1 << 1));
  json_object_put(json);
  return 0;
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
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
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


