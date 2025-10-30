int main(int argc, char **argv)
{
  struct json_object *obj = json_object_new_double(0.5);
  unsigned int obj_idx = 0;
  char udata[] = "test";
  printf("Test default serializer:\n");
  printf("obj.to_string(standard)=%s\n", json_object_to_json_string(obj));
  printf("Test default serializer with custom userdata:\n");
  obj->_userdata = udata;
  printf("obj.to_string(userdata)=%s\n", json_object_to_json_string(obj));
  printf("Test explicit serializer with custom userdata:\n");
  json_object_set_serializer(obj, json_object_double_to_json_string, udata, 0);
  printf("obj.to_string(custom)=%s\n", json_object_to_json_string(obj));
  printf("Test reset serializer:\n");
  json_object_set_serializer(obj, 0, 0, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  printf("Test no zero reset serializer:\n");
  obj_idx = json_object_new_double(3.1415000);
  char data[] = "%.17g";
  json_object_set_serializer(obj, json_object_double_to_json_string, data, 0);
  printf("obj.to_string(reset)=%s\n", json_object_to_json_string_ext(obj, 4));
  json_object_put(obj);
  obj_idx = json_object_new_double(0.52381);
  printf("obj.to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("x%0.3fy", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("T%0.2fX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(with thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("Ttttttttttttt%0.2fxxxxxxxxxxxxxxxxxxX", 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(long thread format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 1) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to global format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj.to_string(back to default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(12.0);
  printf("obj(12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0f", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0f)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.0g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.0g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format("%.2g", 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  printf("obj(12.0).to_string(%%.1g)=%s\n", json_object_to_json_string(obj));
  if (json_c_set_serialization_double_format(0, 0) < 0)
  {
    printf("ERROR: json_c_set_serialization_double_format() failed");
  }
  json_object_put(obj);
  obj_idx = json_object_new_double(-12.0);
  printf("obj(-12.0).to_string(default format)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(zero_dot_zero / zero_dot_zero);
  printf("obj(0.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double(1.0 / zero_dot_zero);
  printf("obj(1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  obj_idx = json_object_new_double((-1.0) / zero_dot_zero);
  printf("obj(-1.0/0.0)=%s\n", json_object_to_json_string(obj));
  json_object_put(obj);
  return 0;
}


/*** DEPENDENCIES:
void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete)
{
  json_object_set_userdata(jso, userdata, user_delete);
  if (to_string_func == 0)
  {
    switch (jso->o_type)
    {
      case json_type_null:
      {
        jso->_to_json_string = 0;
        break;
      }

      case json_type_boolean:
      {
        jso->_to_json_string = &json_object_boolean_to_json_string;
        break;
      }

      case json_type_double:
      {
        jso->_to_json_string = &json_object_double_to_json_string_default;
        break;
      }

      case json_type_int:
      {
        jso->_to_json_string = &json_object_int_to_json_string;
        break;
      }

      case json_type_object:
      {
        jso->_to_json_string = &json_object_object_to_json_string;
        break;
      }

      case json_type_array:
      {
        jso->_to_json_string = &json_object_array_to_json_string;
        break;
      }

      case json_type_string:
      {
        jso->_to_json_string = &json_object_string_to_json_string;
        break;
      }

    }

    return;
  }
  jso->_to_json_string = to_string_func;
}


----------------------------
int json_c_set_serialization_double_format(const char *double_format, int global_or_thread)
{
  if (global_or_thread == 0)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (global_serialization_float_format)
    {
      free(global_serialization_float_format);
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      global_serialization_float_format = p;
    }
    else
    {
      global_serialization_float_format = 0;
    }
  }
  else
    if (global_or_thread == 1)
  {
    if (tls_serialization_float_format)
    {
      free(tls_serialization_float_format);
      tls_serialization_float_format = 0;
    }
    if (double_format)
    {
      char *p = strdup(double_format);
      if (p == 0)
      {
        _json_c_set_last_err("json_c_set_serialization_double_format: out of memory\n");
        return -1;
      }
      tls_serialization_float_format = p;
    }
    else
    {
      tls_serialization_float_format = 0;
    }
  }
  else
  {
    _json_c_set_last_err("json_c_set_serialization_double_format: invalid global_or_thread value: %d\n", global_or_thread);
    return -1;
  }
  return 0;
}


----------------------------
int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, (const char *) jso->_userdata);
}


----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
double zero_dot_zero = 0.0
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


