static void do_clear_serializer(json_object *jso)
{
  json_c_visit(jso, 0, clear_serializer, 0);
}


/*** DEPENDENCIES:
int json_c_visit(json_object *jso, int future_flags, json_c_visit_userfunc *userfunc, void *userarg)
{
  int ret = _json_c_visit(jso, 0, 0, 0, userfunc, userarg);
  switch (ret)
  {
    case 0:

    case 7547:

    case 767:

    case 7867:
    {
      return 0;
    }

    default:
    {
      return -1;
    }

  }

}


----------------------------
static json_c_visit_userfunc clear_serializer
----------------------------
None
----------------------------
***/


static void single_incremental_parse(const char *test_string, int clear_serializer)
{
  size_t ii;
  int chunksize = atoi(getenv("TEST_PARSE_CHUNKSIZE"));
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  enum json_tokener_error jerr;
  json_object *all_at_once_obj;
  unsigned int all_at_once_obj_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  const char *all_at_once_str;
  unsigned int all_at_once_str_idx = 0;
  const char *new_str;
  unsigned int new_str_idx = 0;
  new_obj_idx = 0;
  assert(chunksize > 0);
  all_at_once_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(all_at_once_obj);
  }
  all_at_once_str_idx = json_object_to_json_string(all_at_once_obj);
  tok_idx = json_tokener_new();
  size_t test_string_len = strlen(test_string) + 1;
  for (ii = 0; ii < test_string_len; ii += chunksize)
  {
    int len_to_parse = chunksize;
    if ((ii + chunksize) > test_string_len)
    {
      len_to_parse = test_string_len - ii;
    }
    if (getenv("TEST_PARSE_DEBUG") != 0)
    {
      printf(" chunk: %.*s\n", len_to_parse, &test_string[ii]);
    }
    new_obj_idx = json_tokener_parse_ex(tok, &test_string[ii], len_to_parse);
    jerr = json_tokener_get_error(tok);
    if ((jerr != json_tokener_continue) || (&new_obj[new_obj_idx]))
    {
      break;
    }
  }

  if (clear_serializer && (&new_obj[new_obj_idx]))
  {
    do_clear_serializer(new_obj);
  }
  new_str_idx = json_object_to_json_string(new_obj);
  if (strcmp(all_at_once_str, new_str) != 0)
  {
    printf("ERROR: failed to parse (%s) in %d byte chunks: %s != %s\n", test_string, chunksize, all_at_once_str, new_str);
  }
  json_tokener_free(tok);
  if (all_at_once_obj)
  {
    json_object_put(all_at_once_obj);
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
}


/*** DEPENDENCIES:
None
----------------------------
struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    helper_json_tokener_parse_ex_1(&str_idx, &obj_idx, &c, tok, str, len, obj, nBytesp);
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}


----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}


----------------------------
static void do_clear_serializer(json_object *jso)
{
  json_c_visit(jso, 0, clear_serializer, 0);
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
enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
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
struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
static json_c_visit_userfunc clear_serializer
----------------------------
None
----------------------------
***/


static void single_basic_parse(const char *test_string, int clear_serializer)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(new_obj);
  }
  printf("new_obj.to_string(%s)=%s\n", test_string, json_object_to_json_string(new_obj));
  json_object_put(new_obj);
  if (getenv("TEST_PARSE_CHUNKSIZE") != 0)
  {
    single_incremental_parse(test_string, clear_serializer);
  }
}


/*** DEPENDENCIES:
static void do_clear_serializer(json_object *jso)
{
  json_c_visit(jso, 0, clear_serializer, 0);
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
static void single_incremental_parse(const char *test_string, int clear_serializer)
{
  size_t ii;
  int chunksize = atoi(getenv("TEST_PARSE_CHUNKSIZE"));
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  enum json_tokener_error jerr;
  json_object *all_at_once_obj;
  unsigned int all_at_once_obj_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  const char *all_at_once_str;
  unsigned int all_at_once_str_idx = 0;
  const char *new_str;
  unsigned int new_str_idx = 0;
  new_obj_idx = 0;
  assert(chunksize > 0);
  all_at_once_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(all_at_once_obj);
  }
  all_at_once_str_idx = json_object_to_json_string(all_at_once_obj);
  tok_idx = json_tokener_new();
  size_t test_string_len = strlen(test_string) + 1;
  for (ii = 0; ii < test_string_len; ii += chunksize)
  {
    int len_to_parse = chunksize;
    if ((ii + chunksize) > test_string_len)
    {
      len_to_parse = test_string_len - ii;
    }
    if (getenv("TEST_PARSE_DEBUG") != 0)
    {
      printf(" chunk: %.*s\n", len_to_parse, &test_string[ii]);
    }
    new_obj_idx = json_tokener_parse_ex(tok, &test_string[ii], len_to_parse);
    jerr = json_tokener_get_error(tok);
    if ((jerr != json_tokener_continue) || (&new_obj[new_obj_idx]))
    {
      break;
    }
  }

  if (clear_serializer && (&new_obj[new_obj_idx]))
  {
    do_clear_serializer(new_obj);
  }
  new_str_idx = json_object_to_json_string(new_obj);
  if (strcmp(all_at_once_str, new_str) != 0)
  {
    printf("ERROR: failed to parse (%s) in %d byte chunks: %s != %s\n", test_string, chunksize, all_at_once_str, new_str);
  }
  json_tokener_free(tok);
  if (all_at_once_obj)
  {
    json_object_put(all_at_once_obj);
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
}


----------------------------
static json_c_visit_userfunc clear_serializer
----------------------------
None
----------------------------
***/


static void test_basic_parse(void)
{
  single_basic_parse("\"\003\"", 0);
  single_basic_parse("/* hello */\"foo\"", 0);
  single_basic_parse("// hello\n\"foo\"", 0);
  single_basic_parse("\"foo\"blue", 0);
  single_basic_parse("\'foo\'", 0);
  single_basic_parse("\"\\u0041\\u0042\\u0043\"", 0);
  single_basic_parse("\"\\u4e16\\u754c\\u00df\"", 0);
  single_basic_parse("\"\\u4E16\"", 0);
  single_basic_parse("\"\\u4e1\"", 0);
  single_basic_parse("\"\\u4e1@\"", 0);
  single_basic_parse("\"\\ud840\\u4e16\"", 0);
  single_basic_parse("\"\\ud840\"", 0);
  single_basic_parse("\"\\udd27\"", 0);
  single_basic_parse("[9,'\\uDAD", 0);
  single_basic_parse("null", 0);
  single_basic_parse("NaN", 0);
  single_basic_parse("-NaN", 0);
  single_basic_parse("Inf", 0);
  single_basic_parse("inf", 0);
  single_basic_parse("Infinity", 0);
  single_basic_parse("infinity", 0);
  single_basic_parse("-Infinity", 0);
  single_basic_parse("-infinity", 0);
  single_basic_parse("{ \"min\": Infinity, \"max\": -Infinity}", 0);
  single_basic_parse("Infinity!", 0);
  single_basic_parse("Infinitynull", 0);
  single_basic_parse("InfinityXXXX", 0);
  single_basic_parse("-Infinitynull", 0);
  single_basic_parse("-InfinityXXXX", 0);
  single_basic_parse("Infinoodle", 0);
  single_basic_parse("InfinAAA", 0);
  single_basic_parse("-Infinoodle", 0);
  single_basic_parse("-InfinAAA", 0);
  single_basic_parse("True", 0);
  single_basic_parse("False", 0);
  single_basic_parse("tRue", 0);
  single_basic_parse("fAlse", 0);
  single_basic_parse("nAn", 0);
  single_basic_parse("iNfinity", 0);
  single_basic_parse("12", 0);
  single_basic_parse("12.3", 0);
  single_basic_parse("12.3.4", 0);
  single_basic_parse("2015-01-15", 0);
  single_basic_parse("12.3xxx", 0);
  single_basic_parse("12.3{\"a\":123}", 0);
  single_basic_parse("12.3\n", 0);
  single_basic_parse("12.3 ", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3e512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E51.2}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512E12}", 0);
  single_basic_parse("[\"\\n\"]", 0);
  single_basic_parse("[\"\\nabc\\n\"]", 0);
  single_basic_parse("[null]", 0);
  single_basic_parse("[]", 0);
  single_basic_parse("[false]", 0);
  single_basic_parse("[\"abc\",null,\"def\",12]", 0);
  single_basic_parse("{}", 0);
  single_basic_parse("{ \"foo\": \"bar\" }", 0);
  single_basic_parse("{ \'foo\': \'bar\' }", 0);
  single_basic_parse("{ \"foo\": \"bar\", \"baz\": null, \"bool0\": true }", 0);
  single_basic_parse("{ \"foo\": [null, \"foo\"] }", 0);
  single_basic_parse("{ \"abc\": 12, \"foo\": \"bar\", \"bool0\": false, \"bool1\": true, \"arr\": [ 1, 2, 3, null, 5 ] }", 0);
  single_basic_parse("{ \"abc\": \"blue\nred\\ngreen\" }", 0);
  single_basic_parse("null", 1);
  single_basic_parse("false", 1);
  single_basic_parse("[0e]", 1);
  single_basic_parse("[0e+]", 1);
  single_basic_parse("[0e+-1]", 1);
  single_basic_parse("\"hello world!\"", 1);
  single_basic_parse("[9223372036854775806]", 1);
  single_basic_parse("[9223372036854775807]", 1);
  single_basic_parse("[9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775807]", 1);
  single_basic_parse("[-9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775809]", 1);
  single_basic_parse("[18446744073709551614]", 1);
  single_basic_parse("[18446744073709551615]", 1);
  single_basic_parse("[18446744073709551616]", 1);
}


/*** DEPENDENCIES:
static void single_basic_parse(const char *test_string, int clear_serializer)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(new_obj);
  }
  printf("new_obj.to_string(%s)=%s\n", test_string, json_object_to_json_string(new_obj));
  json_object_put(new_obj);
  if (getenv("TEST_PARSE_CHUNKSIZE") != 0)
  {
    single_incremental_parse(test_string, clear_serializer);
  }
}


----------------------------
***/


static void test_utf8_parse(void)
{
  const char *utf8_bom = "\xEF\xBB\xBF";
  const char *utf8_bom_and_chars = "\xEF\xBB\xBF{}";
  single_basic_parse(utf8_bom, 0);
  single_basic_parse(utf8_bom_and_chars, 0);
}


/*** DEPENDENCIES:
static void single_basic_parse(const char *test_string, int clear_serializer)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  new_obj_idx = json_tokener_parse(test_string);
  if (clear_serializer)
  {
    do_clear_serializer(new_obj);
  }
  printf("new_obj.to_string(%s)=%s\n", test_string, json_object_to_json_string(new_obj));
  json_object_put(new_obj);
  if (getenv("TEST_PARSE_CHUNKSIZE") != 0)
  {
    single_incremental_parse(test_string, clear_serializer);
  }
}


----------------------------
***/


static int clear_serializer(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  if (jso)
  {
    json_object_set_serializer(jso, 0, 0, 0);
  }
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
None
----------------------------
***/


static void test_verbose_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error error = json_tokener_success;
  new_obj_idx = json_tokener_parse_verbose("{ foo }", &error);
  assert(error == json_tokener_error_parse_object_key_name);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("{ foo }");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("foo");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_verbose("foo", &error);
  assert((&new_obj[new_obj_idx]) == 0);
  assert(error == json_tokener_error_parse_boolean);
  puts("json_tokener_parse_verbose() OK");
}


/*** DEPENDENCIES:
struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  tok_idx = json_tokener_new();
  if (!(&tok[tok_idx]))
  {
    *error = json_tokener_error_memory;
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, str, -1);
  *error = tok->err;
  if (tok->err != json_tokener_success)
  {
    if ((&obj[obj_idx]) != 0)
    {
      json_object_put(obj);
    }
    obj_idx = 0;
  }
  json_tokener_free(tok);
  return obj;
}


----------------------------
None
----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
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
None
----------------------------
***/


// hint:  ['new_obj_idx_ref is a mutable refrence to unsigned int', 'jerr_ref is a mutable refrence to ', 'num_ok_ref is a mutable refrence to int', 'num_error_ref is a mutable refrence to int']
void helper_test_incremental_parse_1(unsigned int * const new_obj_idx_ref, enum json_tokener_error * const jerr_ref, int * const num_ok_ref, int * const num_error_ref, json_object * const new_obj, struct json_tokener * const tok, int ii)
{
  unsigned int new_obj_idx = *new_obj_idx_ref;
  enum json_tokener_error jerr = *jerr_ref;
  int num_ok = *num_ok_ref;
  int num_error = *num_error_ref;
  int this_step_ok = 0;
  struct incremental_step *step = &incremental_steps[ii];
  int length = step->length;
  size_t expected_char_offset;
  json_tokener_set_flags(tok, step->tok_flags);
  if (length == (-1))
  {
    length = (int) strlen(step->string_to_parse);
  }
  if (step->char_offset == (-1))
  {
    expected_char_offset = length;
  }
  else
    expected_char_offset = step->char_offset;
  printf("json_tokener_parse_ex(tok, %-12s, %3d) ... ", step->string_to_parse, length);
  new_obj_idx = json_tokener_parse_ex(tok, step->string_to_parse, length);
  jerr = json_tokener_get_error(tok);
  if (step->expected_error != json_tokener_success)
  {
    if ((&new_obj[new_obj_idx]) != 0)
    {
      printf("ERROR: invalid object returned: %s\n", json_object_to_json_string(new_obj));
    }
    else
      if (jerr != step->expected_error)
    {
      printf("ERROR: got wrong error: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got correct error: %s\n", json_tokener_error_desc(jerr));
      this_step_ok = 1;
    }
  }
  else
  {
    if (((&new_obj[new_obj_idx]) == 0) && (!((step->length >= 4) && (strncmp(step->string_to_parse, "null", 4) == 0))))
    {
      printf("ERROR: expected valid object, instead: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got object of type [%s]: %s\n", json_type_to_name(json_object_get_type(new_obj)), json_object_to_json_string(new_obj));
      this_step_ok = 1;
    }
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
  if (step->reset_tokener & 1)
  {
    json_tokener_reset(tok);
  }
  if (this_step_ok)
  {
    num_ok += 1;
  }
  else
    num_error++;
  num_error += 1;
  *new_obj_idx_ref = new_obj_idx;
  *jerr_ref = jerr;
  *num_ok_ref = num_ok;
  *num_error_ref = num_error;
}


/*** DEPENDENCIES:
None
----------------------------
struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    helper_json_tokener_parse_ex_1(&str_idx, &obj_idx, &c, tok, str, len, obj, nBytesp);
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}


----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
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
enum json_type json_object_get_type(const struct json_object *jso)
{
  if (!jso)
  {
    return json_type_null;
  }
  return jso->o_type;
}


----------------------------
void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}


----------------------------
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
  int jerr_int = (int) jerr;
  if ((jerr_int < 0) || (jerr_int >= ((int) ((sizeof(json_tokener_errors)) / (sizeof(json_tokener_errors[0]))))))
  {
    return "Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()";
  }
  return json_tokener_errors[jerr];
}


----------------------------
void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}


----------------------------
struct incremental_step
{
  const char *string_to_parse;
  int length;
  int char_offset;
  enum json_tokener_error expected_error;
  int reset_tokener;
  int tok_flags;
} incremental_steps[] = {{"{ \"foo\": 123 }", -1, -1, json_tokener_success, 0, 0}, {"{ \"foo\": 456 }", -1, -1, json_tokener_success, 1, 0}, {"{ \"foo\": 789 }", -1, -1, json_tokener_success, 1, 0}, {"/* hello */{ \"foo\"", -1, -1, json_tokener_continue, 0, 0}, {"/* hello */:/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"\"bar\"/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"}/* hello */", -1, -1, json_tokener_success, 1, 0}, {"/ hello ", -1, 1, json_tokener_error_parse_comment, 1, 0}, {"/* hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"/* hello*\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"// hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}", -1, -1, json_tokener_success, 1, 0}, {"\"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"8", -1, -1, json_tokener_continue, 0, 0}, {"3", -1, -1, json_tokener_continue, 0, 0}, {"4", -1, -1, json_tokener_continue, 0, 0}, {"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"1", -1, -1, json_tokener_continue, 0, 0}, {"e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\u", -1, -1, json_tokener_continue, 0, 0}, {"d8", -1, -1, json_tokener_continue, 0, 0}, {"34", -1, -1, json_tokener_continue, 0, 0}, {"\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd", -1, -1, json_tokener_continue, 0, 0}, {"1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834", -1, -1, json_tokener_continue, 0, 0}, {"\\udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\", -1, -1, json_tokener_continue, 0, 0}, {"udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\ud", -1, -1, json_tokener_continue, 0, 0}, {"d1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\udd", -1, -1, json_tokener_continue, 0, 0}, {"1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud83d\\ude", -1, -1, json_tokener_continue, 0, 0}, {"00 bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0x01}, {"{ \"foo", -1, -1, json_tokener_continue, 1, 0}, {": \"bar\"}", -1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}XXXX", 10, 6, json_tokener_success, 0, 0}, {"XXXX", 4, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"x\": 123 }\"X\"", -1, 11, json_tokener_success, 0, 0}, {"\"Y\"", -1, -1, json_tokener_success, 1, 0}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_error_parse_unexpected, 1, 0x01}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_success, 0, 0x01 | 0x02}, {"{\"b\":8}ignored garbage", -1, 7, json_tokener_success, 1, 0x01 | 0x02}, {"1", 1, 1, json_tokener_continue, 0, 0}, {"2", 2, 1, json_tokener_success, 0, 0}, {"12{", 3, 2, json_tokener_success, 1, 0}, {"[02]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+0", 5, 4, json_tokener_success, 1, 0}, {"[0e+0]", -1, -1, json_tokener_success, 1, 0}, {"0e", 2, 2, json_tokener_continue, 1, 0}, {"0e", 3, 2, json_tokener_success, 1, 0}, {"0e", 3, 2, json_tokener_error_parse_eof, 1, 0x01}, {"[0e]", -1, -1, json_tokener_success, 1, 0}, {"[0e]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+", 3, 3, json_tokener_continue, 1, 0}, {"0e+", 4, 3, json_tokener_success, 1, 0}, {"0e+", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e+]", -1, -1, json_tokener_success, 1, 0}, {"[0e+]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e-", 3, 3, json_tokener_continue, 1, 0}, {"0e-", 4, 3, json_tokener_success, 1, 0}, {"0e-", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e-]", -1, -1, json_tokener_success, 1, 0}, {"[0e-]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e+-", 5, 3, json_tokener_success, 1, 0}, {"0e+-", 5, 3, json_tokener_error_parse_number, 1, 0x01}, {"[0e+-]", -1, 4, json_tokener_error_parse_number, 1, 0}, {"false", 5, 5, json_tokener_continue, 1, 0}, {"false", 6, 5, json_tokener_success, 1, 0}, {"true", 4, 4, json_tokener_continue, 1, 0}, {"true", 5, 4, json_tokener_success, 1, 0}, {"null", 4, 4, json_tokener_continue, 1, 0}, {"null", 5, 4, json_tokener_success, 1, 0}, {"Infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"-infinity", 10, 9, json_tokener_success, 1, 0}, {"-infinity", 10, 1, json_tokener_error_parse_unexpected, 1, 0x01}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"-inf", 4, 4, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"f", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"t", 1, 1, json_tokener_continue, 0, 0}, {"y", 1, 1, json_tokener_continue, 0, 0}, {"", 1, 0, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"ini", 3, 3, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"nfini", 5, 5, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-i", 2, 2, json_tokener_continue, 0, 0}, {"nfinity", 8, 7, json_tokener_success, 1, 0}, {"InfinityX", 10, 8, json_tokener_success, 0, 0}, {"X", 1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"Infinity1234", 13, 8, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"Infinity9999", 8, 8, json_tokener_continue, 0, 0}, {"1234", 5, 0, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"[9223372036854775807]", 22, 21, json_tokener_success, 1, 0}, {"[9223372036854775808]", 22, 21, json_tokener_success, 1, 0}, {"[-9223372036854775808]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"[18446744073709551615]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"18446744073709551616", 21, 20, json_tokener_success, 1, 0}, {"18446744073709551616", 21, 20, json_tokener_error_parse_eof, 1, 0x01}, {"[9223372036854775808.0]", 24, 23, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0x01}, {"[18446744073709551615.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0x01}, {"noodle", 7, 1, json_tokener_error_parse_null, 1, 0}, {"naodle", 7, 2, json_tokener_error_parse_null, 1, 0}, {"track", 6, 2, json_tokener_error_parse_boolean, 1, 0}, {"fail", 5, 2, json_tokener_error_parse_boolean, 1, 0}, {"null123", 8, 4, json_tokener_success, 0, 0}, {&"null123"[4], 4, 3, json_tokener_success, 1, 0}, {"nullx", 6, 4, json_tokener_success, 0, 0}, {&"nullx"[4], 2, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1}{\"b\":2}", 15, 7, json_tokener_success, 0, 0}, {&"{\"a\":1}{\"b\":2}"[7], 8, 7, json_tokener_success, 1, 0}, {&"2015-01-15"[0], 11, 4, json_tokener_success, 1, 0}, {&"2015-01-15"[4], 7, 3, json_tokener_success, 1, 0}, {&"2015-01-15"[7], 4, 3, json_tokener_success, 1, 0}, {&"2015 01 15"[0], 11, 5, json_tokener_success, 1, 0}, {&"2015 01 15"[4], 7, 4, json_tokener_success, 1, 0}, {&"2015 01 15"[7], 4, 3, json_tokener_success, 1, 0}, {"\"blue\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\"\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\\\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\b\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\f\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\n\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\r\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\t\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\/\"", -1, -1, json_tokener_success, 0, 0}, {"\"/\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\a\"", -1, 2, json_tokener_error_parse_string, 1, 0}, {"\'foo\'", -1, 5, json_tokener_success, 1, 0}, {"\'foo\'", -1, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,3]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3}", -1, 6, json_tokener_error_parse_array, 1, 0}, {"{\"a\"}", -1, 4, json_tokener_error_parse_object_key_sep, 1, 0}, {"{\"a\":1]", -1, 6, json_tokener_error_parse_object_value_sep, 1, 0}, {"{\"a\"::1}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1,\"a\":2}", -1, -1, json_tokener_success, 1, 0}, {"\"a\":1}", -1, 3, json_tokener_success, 1, 0}, {"{\"a\":1", -1, -1, json_tokener_continue, 1, 0}, {"[,]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[,1]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[1,2,3,]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3,]", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0x01}, {"{\"a\":1,}", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe4\xb8", -1, 3, json_tokener_error_parse_utf8_string, 0, 0x10}, {"\x96\xe7\x95\x8c\x22", -1, 0, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xcf\x80\xcf\x86\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xf0\xa5\x91\x95\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 5, json_tokener_success, 1, 0}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 6, json_tokener_success, 1, 0}, {"\x20\x20\x22\xe4\xb8\x96\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x20\x20\x81\x22\xe4\xb8\x96\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x5b\x20\x81\x31\x5d", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x49\x6e\x66\x69\x6e\x69\x74\x79", 9, 8, json_tokener_success, 1, 0}, {"\x49\x6e\x66\x81\x6e\x69\x74\x79", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\x5c\x75\x64\x63\x35\x35\x22", 15, 14, json_tokener_success, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\xc0\x75\x64\x63\x35\x35\x22", -1, 8, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x30\x30\x33\x31\xc0\x22", -1, 9, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x31\x31\x81\x31\x31", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x7b\x22\x31\x81\x22\x3a\x31\x7d", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\"0\x01\x02\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"", -1, -1, json_tokener_success, 1, 0}, {"\"\x01\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x02\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x03\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x04\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x05\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x06\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x07\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x08\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x09\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x10\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x11\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x12\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x13\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x14\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x15\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x16\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x17\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x18\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x19\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {0, -1, -1, json_tokener_success, 0, 0}}
----------------------------
enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
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
size_t json_tokener_get_parse_end(struct json_tokener *tok)
{
  assert(tok->char_offset >= 0);
  return (size_t) tok->char_offset;
}


----------------------------
None
----------------------------
***/


static void test_incremental_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error jerr;
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  const char *string_to_parse;
  unsigned int string_to_parse_idx = 0;
  int ii;
  int num_ok;
  int num_error;
  num_ok = 0;
  num_error = 0;
  printf("Starting incremental tests.\n");
  printf("Note: quotes and backslashes seen in the output here are literal values passed\n");
  printf("     to the parse functions.  e.g. this is 4 characters: \"\\f\"\n");
  string_to_parse_idx = "{ \"foo";
  printf("json_tokener_parse(%s) ... ", string_to_parse);
  new_obj_idx = json_tokener_parse(string_to_parse);
  if ((&new_obj[new_obj_idx]) == 0)
  {
    printf("%s", "got error as expected\n");
  }
  tok_idx = json_tokener_new();
  for (ii = 0; incremental_steps[ii].string_to_parse != 0; ii += 1)
  {
    helper_test_incremental_parse_1(&new_obj_idx, &jerr, &num_ok, &num_error, new_obj, tok, ii);
  }

  json_tokener_free(tok);
  printf("End Incremental Tests OK=%d ERROR=%d\n", num_ok, num_error);
}


/*** DEPENDENCIES:
void helper_test_incremental_parse_1(unsigned int * const new_obj_idx_ref, enum json_tokener_error * const jerr_ref, int * const num_ok_ref, int * const num_error_ref, json_object * const new_obj, struct json_tokener * const tok, int ii)
{
  unsigned int new_obj_idx = *new_obj_idx_ref;
  enum json_tokener_error jerr = *jerr_ref;
  int num_ok = *num_ok_ref;
  int num_error = *num_error_ref;
  int this_step_ok = 0;
  struct incremental_step *step = &incremental_steps[ii];
  int length = step->length;
  size_t expected_char_offset;
  json_tokener_set_flags(tok, step->tok_flags);
  if (length == (-1))
  {
    length = (int) strlen(step->string_to_parse);
  }
  if (step->char_offset == (-1))
  {
    expected_char_offset = length;
  }
  else
    expected_char_offset = step->char_offset;
  printf("json_tokener_parse_ex(tok, %-12s, %3d) ... ", step->string_to_parse, length);
  new_obj_idx = json_tokener_parse_ex(tok, step->string_to_parse, length);
  jerr = json_tokener_get_error(tok);
  if (step->expected_error != json_tokener_success)
  {
    if ((&new_obj[new_obj_idx]) != 0)
    {
      printf("ERROR: invalid object returned: %s\n", json_object_to_json_string(new_obj));
    }
    else
      if (jerr != step->expected_error)
    {
      printf("ERROR: got wrong error: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got correct error: %s\n", json_tokener_error_desc(jerr));
      this_step_ok = 1;
    }
  }
  else
  {
    if (((&new_obj[new_obj_idx]) == 0) && (!((step->length >= 4) && (strncmp(step->string_to_parse, "null", 4) == 0))))
    {
      printf("ERROR: expected valid object, instead: %s\n", json_tokener_error_desc(jerr));
    }
    else
      if (json_tokener_get_parse_end(tok) != expected_char_offset)
    {
      printf("ERROR: wrong char_offset %zu != expected %zu\n", json_tokener_get_parse_end(tok), expected_char_offset);
    }
    else
    {
      printf("OK: got object of type [%s]: %s\n", json_type_to_name(json_object_get_type(new_obj)), json_object_to_json_string(new_obj));
      this_step_ok = 1;
    }
  }
  if (new_obj)
  {
    json_object_put(new_obj);
  }
  if (step->reset_tokener & 1)
  {
    json_tokener_reset(tok);
  }
  if (this_step_ok)
  {
    num_ok += 1;
  }
  else
    num_error++;
  num_error += 1;
  *new_obj_idx_ref = new_obj_idx;
  *jerr_ref = jerr;
  *num_ok_ref = num_ok;
  *num_error_ref = num_error;
}


----------------------------
None
----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}


----------------------------
struct incremental_step
{
  const char *string_to_parse;
  int length;
  int char_offset;
  enum json_tokener_error expected_error;
  int reset_tokener;
  int tok_flags;
} incremental_steps[] = {{"{ \"foo\": 123 }", -1, -1, json_tokener_success, 0, 0}, {"{ \"foo\": 456 }", -1, -1, json_tokener_success, 1, 0}, {"{ \"foo\": 789 }", -1, -1, json_tokener_success, 1, 0}, {"/* hello */{ \"foo\"", -1, -1, json_tokener_continue, 0, 0}, {"/* hello */:/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"\"bar\"/* hello */", -1, -1, json_tokener_continue, 0, 0}, {"}/* hello */", -1, -1, json_tokener_success, 1, 0}, {"/ hello ", -1, 1, json_tokener_error_parse_comment, 1, 0}, {"/* hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"/* hello*\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"// hello\"foo\"", -1, -1, json_tokener_continue, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}", -1, -1, json_tokener_success, 1, 0}, {"\"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"8", -1, -1, json_tokener_continue, 0, 0}, {"3", -1, -1, json_tokener_continue, 0, 0}, {"4", -1, -1, json_tokener_continue, 0, 0}, {"\\", -1, -1, json_tokener_continue, 0, 0}, {"u", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"d", -1, -1, json_tokener_continue, 0, 0}, {"1", -1, -1, json_tokener_continue, 0, 0}, {"e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\u", -1, -1, json_tokener_continue, 0, 0}, {"d8", -1, -1, json_tokener_continue, 0, 0}, {"34", -1, -1, json_tokener_continue, 0, 0}, {"\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd", -1, -1, json_tokener_continue, 0, 0}, {"1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834", -1, -1, json_tokener_continue, 0, 0}, {"\\udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\", -1, -1, json_tokener_continue, 0, 0}, {"udd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"\\ud834\\u", -1, -1, json_tokener_continue, 0, 0}, {"dd1e\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\ud", -1, -1, json_tokener_continue, 0, 0}, {"d1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud834\\udd", -1, -1, json_tokener_continue, 0, 0}, {"1e bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"fff \\ud83d\\ude", -1, -1, json_tokener_continue, 0, 0}, {"00 bar\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0}, {"\"\xc3\xa4\"", -1, -1, json_tokener_success, 1, 0x01}, {"{ \"foo", -1, -1, json_tokener_continue, 1, 0}, {": \"bar\"}", -1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{ \"foo", -1, -1, json_tokener_continue, 0, 0}, {"\": {\"bar", -1, -1, json_tokener_continue, 0, 0}, {"\":13}}XXXX", 10, 6, json_tokener_success, 0, 0}, {"XXXX", 4, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"x\": 123 }\"X\"", -1, 11, json_tokener_success, 0, 0}, {"\"Y\"", -1, -1, json_tokener_success, 1, 0}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_error_parse_unexpected, 1, 0x01}, {"{\"foo\":9}{\"bar\":8}", -1, 9, json_tokener_success, 0, 0x01 | 0x02}, {"{\"b\":8}ignored garbage", -1, 7, json_tokener_success, 1, 0x01 | 0x02}, {"1", 1, 1, json_tokener_continue, 0, 0}, {"2", 2, 1, json_tokener_success, 0, 0}, {"12{", 3, 2, json_tokener_success, 1, 0}, {"[02]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+0", 5, 4, json_tokener_success, 1, 0}, {"[0e+0]", -1, -1, json_tokener_success, 1, 0}, {"0e", 2, 2, json_tokener_continue, 1, 0}, {"0e", 3, 2, json_tokener_success, 1, 0}, {"0e", 3, 2, json_tokener_error_parse_eof, 1, 0x01}, {"[0e]", -1, -1, json_tokener_success, 1, 0}, {"[0e]", -1, 3, json_tokener_error_parse_number, 1, 0x01}, {"0e+", 3, 3, json_tokener_continue, 1, 0}, {"0e+", 4, 3, json_tokener_success, 1, 0}, {"0e+", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e+]", -1, -1, json_tokener_success, 1, 0}, {"[0e+]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e-", 3, 3, json_tokener_continue, 1, 0}, {"0e-", 4, 3, json_tokener_success, 1, 0}, {"0e-", 4, 3, json_tokener_error_parse_eof, 1, 0x01}, {"[0e-]", -1, -1, json_tokener_success, 1, 0}, {"[0e-]", -1, 4, json_tokener_error_parse_number, 1, 0x01}, {"0e+-", 5, 3, json_tokener_success, 1, 0}, {"0e+-", 5, 3, json_tokener_error_parse_number, 1, 0x01}, {"[0e+-]", -1, 4, json_tokener_error_parse_number, 1, 0}, {"false", 5, 5, json_tokener_continue, 1, 0}, {"false", 6, 5, json_tokener_success, 1, 0}, {"true", 4, 4, json_tokener_continue, 1, 0}, {"true", 5, 4, json_tokener_success, 1, 0}, {"null", 4, 4, json_tokener_continue, 1, 0}, {"null", 5, 4, json_tokener_success, 1, 0}, {"Infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 8, json_tokener_success, 1, 0}, {"infinity", 9, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"-infinity", 10, 9, json_tokener_success, 1, 0}, {"-infinity", 10, 1, json_tokener_error_parse_unexpected, 1, 0x01}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"-inf", 4, 4, json_tokener_continue, 0, 0}, {"inity", 6, 5, json_tokener_success, 1, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"f", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"n", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"t", 1, 1, json_tokener_continue, 0, 0}, {"y", 1, 1, json_tokener_continue, 0, 0}, {"", 1, 0, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"inf", 3, 3, json_tokener_continue, 0, 0}, {"ini", 3, 3, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-", 1, 1, json_tokener_continue, 0, 0}, {"i", 1, 1, json_tokener_continue, 0, 0}, {"nfini", 5, 5, json_tokener_continue, 0, 0}, {"ty", 3, 2, json_tokener_success, 1, 0}, {"-i", 2, 2, json_tokener_continue, 0, 0}, {"nfinity", 8, 7, json_tokener_success, 1, 0}, {"InfinityX", 10, 8, json_tokener_success, 0, 0}, {"X", 1, 0, json_tokener_error_parse_unexpected, 1, 0}, {"Infinity1234", 13, 8, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"Infinity9999", 8, 8, json_tokener_continue, 0, 0}, {"1234", 5, 0, json_tokener_success, 0, 0}, {"1234", 5, 4, json_tokener_success, 1, 0}, {"[9223372036854775807]", 22, 21, json_tokener_success, 1, 0}, {"[9223372036854775808]", 22, 21, json_tokener_success, 1, 0}, {"[-9223372036854775808]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 22, json_tokener_success, 1, 0}, {"[-9223372036854775809]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"[18446744073709551615]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 22, json_tokener_success, 1, 0}, {"[18446744073709551616]", 23, 21, json_tokener_error_parse_number, 1, 0x01}, {"18446744073709551616", 21, 20, json_tokener_success, 1, 0}, {"18446744073709551616", 21, 20, json_tokener_error_parse_eof, 1, 0x01}, {"[9223372036854775808.0]", 24, 23, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0}, {"[-9223372036854775809.0]", 25, 24, json_tokener_success, 1, 0x01}, {"[18446744073709551615.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0}, {"[18446744073709551616.0]", 25, 24, json_tokener_success, 1, 0x01}, {"noodle", 7, 1, json_tokener_error_parse_null, 1, 0}, {"naodle", 7, 2, json_tokener_error_parse_null, 1, 0}, {"track", 6, 2, json_tokener_error_parse_boolean, 1, 0}, {"fail", 5, 2, json_tokener_error_parse_boolean, 1, 0}, {"null123", 8, 4, json_tokener_success, 0, 0}, {&"null123"[4], 4, 3, json_tokener_success, 1, 0}, {"nullx", 6, 4, json_tokener_success, 0, 0}, {&"nullx"[4], 2, 0, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1}{\"b\":2}", 15, 7, json_tokener_success, 0, 0}, {&"{\"a\":1}{\"b\":2}"[7], 8, 7, json_tokener_success, 1, 0}, {&"2015-01-15"[0], 11, 4, json_tokener_success, 1, 0}, {&"2015-01-15"[4], 7, 3, json_tokener_success, 1, 0}, {&"2015-01-15"[7], 4, 3, json_tokener_success, 1, 0}, {&"2015 01 15"[0], 11, 5, json_tokener_success, 1, 0}, {&"2015 01 15"[4], 7, 4, json_tokener_success, 1, 0}, {&"2015 01 15"[7], 4, 3, json_tokener_success, 1, 0}, {"\"blue\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\"\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\\\\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\b\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\f\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\n\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\r\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\t\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\/\"", -1, -1, json_tokener_success, 0, 0}, {"\"/\"", -1, -1, json_tokener_success, 0, 0}, {"\"\\a\"", -1, 2, json_tokener_error_parse_string, 1, 0}, {"\'foo\'", -1, 5, json_tokener_success, 1, 0}, {"\'foo\'", -1, 0, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,3]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3}", -1, 6, json_tokener_error_parse_array, 1, 0}, {"{\"a\"}", -1, 4, json_tokener_error_parse_object_key_sep, 1, 0}, {"{\"a\":1]", -1, 6, json_tokener_error_parse_object_value_sep, 1, 0}, {"{\"a\"::1}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":}", -1, 5, json_tokener_error_parse_unexpected, 1, 0}, {"{\"a\":1,\"a\":2}", -1, -1, json_tokener_success, 1, 0}, {"\"a\":1}", -1, 3, json_tokener_success, 1, 0}, {"{\"a\":1", -1, -1, json_tokener_continue, 1, 0}, {"[,]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[,1]", -1, 1, json_tokener_error_parse_unexpected, 1, 0}, {"[1,2,3,]", -1, -1, json_tokener_success, 0, 0}, {"[1,2,3,]", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0}, {"[1,2,,3,]", -1, 5, json_tokener_error_parse_unexpected, 0, 0x01}, {"{\"a\":1,}", -1, 7, json_tokener_error_parse_unexpected, 1, 0x01}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\x31\x32\x33\x61\x73\x63\x24\x25\x26\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe4\xb8", -1, 3, json_tokener_error_parse_utf8_string, 0, 0x10}, {"\x96\xe7\x95\x8c\x22", -1, 0, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe4\xb8\x96\xe7\x95\x8c\x22", -1, -1, json_tokener_success, 1, 0}, {"\x22\xcf\x80\xcf\x86\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xf0\xa5\x91\x95\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xe6\x9d\x4e\x22", -1, 5, json_tokener_success, 1, 0}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\xc0\xee\xc5\xf4\x22", -1, 6, json_tokener_success, 1, 0}, {"\x20\x20\x22\xe4\xb8\x96\x22", -1, -1, json_tokener_success, 1, 0x10}, {"\x20\x20\x81\x22\xe4\xb8\x96\x22", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x5b\x20\x81\x31\x5d", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x49\x6e\x66\x69\x6e\x69\x74\x79", 9, 8, json_tokener_success, 1, 0}, {"\x49\x6e\x66\x81\x6e\x69\x74\x79", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\x5c\x75\x64\x63\x35\x35\x22", 15, 14, json_tokener_success, 1, 0x10}, {"\x22\x5c\x75\x64\x38\x35\x35\xc0\x75\x64\x63\x35\x35\x22", -1, 8, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x22\x5c\x75\x64\x30\x30\x33\x31\xc0\x22", -1, 9, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x31\x31\x81\x31\x31", -1, 2, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\x7b\x22\x31\x81\x22\x3a\x31\x7d", -1, 3, json_tokener_error_parse_utf8_string, 1, 0x10}, {"\"0\x01\x02\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"", -1, -1, json_tokener_success, 1, 0}, {"\"\x01\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x02\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x03\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x04\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x05\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x06\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x07\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x08\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x09\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x0f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x10\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x11\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x12\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x13\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x14\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x15\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x16\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x17\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x18\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x19\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1a\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1b\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1c\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1d\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1e\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {"\"\x1f\"", -1, 1, json_tokener_error_parse_string, 1, 0x01}, {0, -1, -1, json_tokener_success, 0, 0}}
----------------------------
struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
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
None
----------------------------
***/


int main(void)
{
  if (0)
  {
    mc_set_debug(1);
  }
  static const char separator[] = "==================================";
  test_basic_parse();
  puts(separator);
  test_utf8_parse();
  puts(separator);
  test_verbose_parse();
  puts(separator);
  test_incremental_parse();
  puts(separator);
  return 0;
}


/*** DEPENDENCIES:
static void test_verbose_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error error = json_tokener_success;
  new_obj_idx = json_tokener_parse_verbose("{ foo }", &error);
  assert(error == json_tokener_error_parse_object_key_name);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("{ foo }");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse("foo");
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_verbose("foo", &error);
  assert((&new_obj[new_obj_idx]) == 0);
  assert(error == json_tokener_error_parse_boolean);
  puts("json_tokener_parse_verbose() OK");
}


----------------------------
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
static void test_incremental_parse(void)
{
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  enum json_tokener_error jerr;
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  const char *string_to_parse;
  unsigned int string_to_parse_idx = 0;
  int ii;
  int num_ok;
  int num_error;
  num_ok = 0;
  num_error = 0;
  printf("Starting incremental tests.\n");
  printf("Note: quotes and backslashes seen in the output here are literal values passed\n");
  printf("     to the parse functions.  e.g. this is 4 characters: \"\\f\"\n");
  string_to_parse_idx = "{ \"foo";
  printf("json_tokener_parse(%s) ... ", string_to_parse);
  new_obj_idx = json_tokener_parse(string_to_parse);
  if ((&new_obj[new_obj_idx]) == 0)
  {
    printf("%s", "got error as expected\n");
  }
  tok_idx = json_tokener_new();
  for (ii = 0; incremental_steps[ii].string_to_parse != 0; ii += 1)
  {
    helper_test_incremental_parse_1(&new_obj_idx, &jerr, &num_ok, &num_error, new_obj, tok, ii);
  }

  json_tokener_free(tok);
  printf("End Incremental Tests OK=%d ERROR=%d\n", num_ok, num_error);
}


----------------------------
static void test_basic_parse(void)
{
  single_basic_parse("\"\003\"", 0);
  single_basic_parse("/* hello */\"foo\"", 0);
  single_basic_parse("// hello\n\"foo\"", 0);
  single_basic_parse("\"foo\"blue", 0);
  single_basic_parse("\'foo\'", 0);
  single_basic_parse("\"\\u0041\\u0042\\u0043\"", 0);
  single_basic_parse("\"\\u4e16\\u754c\\u00df\"", 0);
  single_basic_parse("\"\\u4E16\"", 0);
  single_basic_parse("\"\\u4e1\"", 0);
  single_basic_parse("\"\\u4e1@\"", 0);
  single_basic_parse("\"\\ud840\\u4e16\"", 0);
  single_basic_parse("\"\\ud840\"", 0);
  single_basic_parse("\"\\udd27\"", 0);
  single_basic_parse("[9,'\\uDAD", 0);
  single_basic_parse("null", 0);
  single_basic_parse("NaN", 0);
  single_basic_parse("-NaN", 0);
  single_basic_parse("Inf", 0);
  single_basic_parse("inf", 0);
  single_basic_parse("Infinity", 0);
  single_basic_parse("infinity", 0);
  single_basic_parse("-Infinity", 0);
  single_basic_parse("-infinity", 0);
  single_basic_parse("{ \"min\": Infinity, \"max\": -Infinity}", 0);
  single_basic_parse("Infinity!", 0);
  single_basic_parse("Infinitynull", 0);
  single_basic_parse("InfinityXXXX", 0);
  single_basic_parse("-Infinitynull", 0);
  single_basic_parse("-InfinityXXXX", 0);
  single_basic_parse("Infinoodle", 0);
  single_basic_parse("InfinAAA", 0);
  single_basic_parse("-Infinoodle", 0);
  single_basic_parse("-InfinAAA", 0);
  single_basic_parse("True", 0);
  single_basic_parse("False", 0);
  single_basic_parse("tRue", 0);
  single_basic_parse("fAlse", 0);
  single_basic_parse("nAn", 0);
  single_basic_parse("iNfinity", 0);
  single_basic_parse("12", 0);
  single_basic_parse("12.3", 0);
  single_basic_parse("12.3.4", 0);
  single_basic_parse("2015-01-15", 0);
  single_basic_parse("12.3xxx", 0);
  single_basic_parse("12.3{\"a\":123}", 0);
  single_basic_parse("12.3\n", 0);
  single_basic_parse("12.3 ", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3e512}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E51.2}", 0);
  single_basic_parse("{\"FoO\"  :   -12.3E512E12}", 0);
  single_basic_parse("[\"\\n\"]", 0);
  single_basic_parse("[\"\\nabc\\n\"]", 0);
  single_basic_parse("[null]", 0);
  single_basic_parse("[]", 0);
  single_basic_parse("[false]", 0);
  single_basic_parse("[\"abc\",null,\"def\",12]", 0);
  single_basic_parse("{}", 0);
  single_basic_parse("{ \"foo\": \"bar\" }", 0);
  single_basic_parse("{ \'foo\': \'bar\' }", 0);
  single_basic_parse("{ \"foo\": \"bar\", \"baz\": null, \"bool0\": true }", 0);
  single_basic_parse("{ \"foo\": [null, \"foo\"] }", 0);
  single_basic_parse("{ \"abc\": 12, \"foo\": \"bar\", \"bool0\": false, \"bool1\": true, \"arr\": [ 1, 2, 3, null, 5 ] }", 0);
  single_basic_parse("{ \"abc\": \"blue\nred\\ngreen\" }", 0);
  single_basic_parse("null", 1);
  single_basic_parse("false", 1);
  single_basic_parse("[0e]", 1);
  single_basic_parse("[0e+]", 1);
  single_basic_parse("[0e+-1]", 1);
  single_basic_parse("\"hello world!\"", 1);
  single_basic_parse("[9223372036854775806]", 1);
  single_basic_parse("[9223372036854775807]", 1);
  single_basic_parse("[9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775807]", 1);
  single_basic_parse("[-9223372036854775808]", 1);
  single_basic_parse("[-9223372036854775809]", 1);
  single_basic_parse("[18446744073709551614]", 1);
  single_basic_parse("[18446744073709551615]", 1);
  single_basic_parse("[18446744073709551616]", 1);
}


----------------------------
static void test_utf8_parse(void)
{
  const char *utf8_bom = "\xEF\xBB\xBF";
  const char *utf8_bom_and_chars = "\xEF\xBB\xBF{}";
  single_basic_parse(utf8_bom, 0);
  single_basic_parse(utf8_bom_and_chars, 0);
}


----------------------------
***/


