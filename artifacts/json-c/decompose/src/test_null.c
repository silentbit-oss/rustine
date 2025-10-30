int main(void)
{
  const char *input = " \0 ";
  const char *expected = "\" \\u0000 \"";
  struct json_object *string = json_object_new_string_len(input, 3);
  const char *json = json_object_to_json_string(string);
  int strings_match = !strcmp(expected, json);
  int retval = 0;
  if (strings_match)
  {
    printf("JSON write result is correct: %s\n", json);
    puts("PASS");
  }
  else
  {
    puts("JSON write result doesn't match expected string");
    printf("expected string: ");
    puts(expected);
    printf("parsed string:   ");
    puts(json);
    puts("FAIL");
    retval = 1;
  }
  json_object_put(string);
  struct json_object *parsed_str = json_tokener_parse(expected);
  if (parsed_str)
  {
    int parsed_len = json_object_get_string_len(parsed_str);
    const char *parsed_cstr = json_object_get_string(parsed_str);
    int ii;
    printf("Re-parsed object string len=%d, chars=[", parsed_len);
    for (ii = 0; ii < parsed_len; ii += 1)
    {
      printf("%s%d", (ii) ? (", ") : (""), (int) parsed_cstr[ii]);
    }

    puts("]");
    json_object_put(parsed_str);
  }
  else
  {
    puts("ERROR: failed to parse");
  }
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
struct json_object *json_object_new_string_len(const char *s, const int len)
{
  return _json_object_new_string(s, len);
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
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
int json_object_get_string_len(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_string:
    {
      return _json_object_get_string_len(JC_STRING_C(jso));
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


