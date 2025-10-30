void print_hex(const char *s)
{
  const char *iter = s;
  unsigned char ch;
  while ((ch = *(iter++)) != 0)
  {
    if (',' != ch)
    {
      printf("%x ", ch);
    }
    else
      printf(",");
  }

  putchar('\n');
}


/*** DEPENDENCIES:
***/


static void test_lot_of_adds(void)
{
  int ii;
  char key[50];
  json_object *jobj = json_object_new_object();
  assert(jobj != 0);
  for (ii = 0; ii < 500; ii += 1)
  {
    snprintf(key, sizeof(key), "k%d", ii);
    json_object *iobj = json_object_new_int(ii);
    assert(iobj != 0);
    if (json_object_object_add(jobj, key, iobj))
    {
      fprintf(stderr, "FAILED to add object #%d\n", ii);
      abort();
    }
  }

  printf("%s\n", json_object_to_json_string(jobj));
  assert(json_object_object_length(jobj) == 500);
  json_object_put(jobj);
}


/*** DEPENDENCIES:
int json_object_object_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_object);
  return lh_table_length(JC_OBJECT_C(jso)->c_object);
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
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}


----------------------------
None
----------------------------
***/


int main(void)
{
  const char *input = "\"\\ud840\\udd26,\\ud840\\udd27,\\ud800\\udd26,\\ud800\\udd27\"";
  const char *expected = "\xF0\xA0\x84\xA6,\xF0\xA0\x84\xA7,\xF0\x90\x84\xA6,\xF0\x90\x84\xA7";
  struct json_object *parse_result = json_tokener_parse(input);
  const char *unjson = json_object_get_string(parse_result);
  printf("input: %s\n", input);
  int strings_match = !strcmp(expected, unjson);
  int retval = 0;
  if (strings_match)
  {
    printf("JSON parse result is correct: %s\n", unjson);
    puts("PASS");
  }
  else
  {
    printf("JSON parse result doesn't match expected string\n");
    printf("expected string bytes: ");
    print_hex(expected);
    printf("parsed string bytes:   ");
    print_hex(unjson);
    puts("FAIL");
    retval = 1;
  }
  json_object_put(parse_result);
  test_lot_of_adds();
  return retval;
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
static void test_lot_of_adds(void)
{
  int ii;
  char key[50];
  json_object *jobj = json_object_new_object();
  assert(jobj != 0);
  for (ii = 0; ii < 500; ii += 1)
  {
    snprintf(key, sizeof(key), "k%d", ii);
    json_object *iobj = json_object_new_int(ii);
    assert(iobj != 0);
    if (json_object_object_add(jobj, key, iobj))
    {
      fprintf(stderr, "FAILED to add object #%d\n", ii);
      abort();
    }
  }

  printf("%s\n", json_object_to_json_string(jobj));
  assert(json_object_object_length(jobj) == 500);
  json_object_put(jobj);
}


----------------------------
void print_hex(const char *s)
{
  const char *iter = s;
  unsigned char ch;
  while ((ch = *(iter++)) != 0)
  {
    if (',' != ch)
    {
      printf("%x ", ch);
    }
    else
      printf(",");
  }

  putchar('\n');
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


