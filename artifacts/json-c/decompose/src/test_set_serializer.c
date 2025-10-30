static void freeit(json_object *jso, void *userdata)
{
  struct myinfo *info = userdata;
  printf("freeit, value=%d\n", info->value);
  freeit_was_called = 1;
}


/*** DEPENDENCIES:
static int freeit_was_called = 0
----------------------------
struct myinfo
{
  int value;
}
----------------------------
None
----------------------------
***/


static int custom_serializer(struct json_object *o, struct printbuf *pb, int level, int flags)
{
  sprintbuf(pb, "Custom Output");
  return 0;
}


/*** DEPENDENCIES:
int sprintbuf(struct printbuf *p, const char *msg, ...)
{
  va_list ap;
  char *t;
  int size;
  char buf[128];
  __builtin_va_start(ap);
  size = vsnprintf(buf, 128, msg, ap);
  ;
  if ((size < 0) || (size > 127))
  {
    __builtin_va_start(ap);
    if ((size = vasprintf(&t, msg, ap)) < 0)
    {
      ;
      return -1;
    }
    ;
    size = printbuf_memappend(p, t, size);
    free(t);
  }
  else
  {
    size = printbuf_memappend(p, buf, size);
  }
  return size;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
None
----------------------------
***/


int main(int argc, char **argv)
{
  json_object *my_object;
  unsigned int my_object_idx = 0;
  json_object *my_sub_object;
  unsigned int my_sub_object_idx = 0;
  if (0)
  {
    mc_set_debug(1);
  }
  printf("Test setting, then resetting a custom serializer:\n");
  my_object_idx = json_object_new_object();
  json_object_object_add(my_object, "abc", json_object_new_int(12));
  json_object_object_add(my_object, "foo", json_object_new_string("bar"));
  printf("my_object.to_string(standard)=%s\n", json_object_to_json_string(my_object));
  struct myinfo userdata = {.value = 123};
  json_object_set_serializer(my_object, custom_serializer, &userdata, freeit);
  printf("my_object.to_string(custom serializer)=%s\n", json_object_to_json_string(my_object));
  printf("Next line of output should be from the custom freeit function:\n");
  freeit_was_called = 0;
  json_object_set_serializer(my_object, 0, 0, 0);
  assert(freeit_was_called);
  printf("my_object.to_string(standard)=%s\n", json_object_to_json_string(my_object));
  json_object_put(my_object);
  my_object_idx = json_object_new_object();
  printf("Check that the custom serializer isn't free'd until the last json_object_put:\n");
  json_object_set_serializer(my_object, custom_serializer, &userdata, freeit);
  json_object_get(my_object);
  json_object_put(my_object);
  printf("my_object.to_string(custom serializer)=%s\n", json_object_to_json_string(my_object));
  printf("Next line of output should be from the custom freeit function:\n");
  freeit_was_called = 0;
  json_object_put(my_object);
  assert(freeit_was_called);
  my_object_idx = json_object_new_object();
  my_sub_object_idx = json_object_new_double(1.0);
  json_object_object_add(my_object, "double", my_sub_object);
  printf("Check that the custom serializer does not include nul byte:\n");
  json_object_set_serializer(my_sub_object, json_object_double_to_json_string, (void *) ((uintptr_t) ((const void *) "%125.0f")), 0);
  printf("my_object.to_string(custom serializer)=%s\n", json_object_to_json_string_ext(my_object, 1 << 2));
  json_object_put(my_object);
  return 0;
}


/*** DEPENDENCIES:
static int freeit_was_called = 0
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
int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  return json_object_double_to_json_string_format(jso, pb, level, flags, (const char *) jso->_userdata);
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
struct json_object *json_object_new_int(int32_t i)
{
  return json_object_new_int64(i);
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}


----------------------------
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
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
static int custom_serializer(struct json_object *o, struct printbuf *pb, int level, int flags)
{
  sprintbuf(pb, "Custom Output");
  return 0;
}


----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
}


----------------------------
struct myinfo
{
  int value;
}
----------------------------
static void freeit(json_object *jso, void *userdata)
{
  struct myinfo *info = userdata;
  printf("freeit, value=%d\n", info->value);
  freeit_was_called = 1;
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


