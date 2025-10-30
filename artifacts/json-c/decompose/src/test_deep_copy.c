int my_custom_serializer(struct json_object *jso, struct printbuf *pb, int level, int flags)
{
  sprintbuf(pb, "OTHER");
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


static void do_benchmark(json_object *src2)
{
  json_object *dst2 = 0;
  unsigned int dst2_idx = 0;
  int ii;
  int iterations = 1000000;
  time_t start = time(0);
  start = time(0);
  for (ii = 0; ii < iterations; ii += 1)
  {
    dst2_idx = json_tokener_parse(json_object_get_string(src2));
    json_object_put(dst2);
  }

  printf("BENCHMARK - %d iterations of 'dst2 = json_tokener_parse(json_object_get_string(src2))' took %d seconds\n", iterations, (int) (time(0) - start));
  start = time(0);
  dst2_idx = 0;
  for (ii = 0; ii < iterations; ii += 1)
  {
    json_object_deep_copy(src2, &(&dst2[dst2_idx]), 0);
    json_object_put(dst2);
    dst2_idx = 0;
  }

  printf("BENCHMARK - %d iterations of 'json_object_deep_copy(src2, &dst2, NULL)' took %d seconds\n", iterations, (int) (time(0) - start));
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
pub time: Time
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
int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  unsigned int shallow_copy_idx = 0;
  int rc;
  if (((!src) || (!dst)) || (*dst))
  {
    errno = EINVAL;
    return -1;
  }
  if ((&shallow_copy[shallow_copy_idx]) == 0)
  {
    shallow_copy_idx = json_c_shallow_copy_default;
  }
  rc = json_object_deep_copy_recursive(src, 0, 0, 4294967295U, dst, shallow_copy);
  if (rc < 0)
  {
    json_object_put(*dst);
    *dst = 0;
  }
  return rc;
}


----------------------------
None
----------------------------
***/


int my_shallow_copy(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
{
  int rc;
  rc = json_c_shallow_copy_default(src, parent, key, index, dst);
  if (rc < 0)
  {
    return rc;
  }
  if ((key != 0) && (strcmp(key, "with_serializer") == 0))
  {
    printf("CALLED: my_shallow_copy on with_serializer object\n");
    void *userdata = json_object_get_userdata(src);
    json_object_set_serializer(*dst, my_custom_serializer, userdata, 0);
    return 2;
  }
  return rc;
}


/*** DEPENDENCIES:
extern json_c_shallow_copy_fn json_c_shallow_copy_default
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
json_object_to_json_string_fn my_custom_serializer
----------------------------
void *json_object_get_userdata(json_object *jso)
{
  return (jso) ? (jso->_userdata) : (0);
}


----------------------------
None
----------------------------
***/


int main(int argc, char **argv)
{
  struct json_object *src1;
  unsigned int src1_idx = 0;
  struct json_object *src2;
  unsigned int src2_idx = 0;
  struct json_object *src3;
  unsigned int src3_idx = 0;
  struct json_object *dst1 = 0;
  unsigned int dst1_idx = 0;
  struct json_object *dst2 = 0;
  struct json_object *dst3 = 0;
  int benchmark = 0;
  if ((argc > 1) && (strcmp(argv[1], "--benchmark") == 0))
  {
    benchmark = 1;
  }
  src1_idx = json_tokener_parse(json_str1);
  src2_idx = json_tokener_parse(json_str2);
  src3_idx = json_tokener_parse(json_str3);
  assert((&src1[src1_idx]) != 0);
  assert((&src2[src2_idx]) != 0);
  assert((&src3[src3_idx]) != 0);
  printf("PASSED - loaded input data\n");
  assert(0 == json_object_deep_copy(src1, &(&dst1[dst1_idx]), 0));
  assert(0 == json_object_deep_copy(src2, &dst2, 0));
  assert(0 == json_object_deep_copy(src3, &dst3, 0));
  printf("PASSED - all json_object_deep_copy() returned successful\n");
  assert((-1) == json_object_deep_copy(src1, &(&dst1[dst1_idx]), 0));
  assert(errno == EINVAL);
  assert((-1) == json_object_deep_copy(src2, &dst2, 0));
  assert(errno == EINVAL);
  assert((-1) == json_object_deep_copy(src3, &dst3, 0));
  assert(errno == EINVAL);
  printf("PASSED - all json_object_deep_copy() returned EINVAL for non-null pointer\n");
  assert(1 == json_object_equal(src1, dst1));
  assert(1 == json_object_equal(src2, dst2));
  assert(1 == json_object_equal(src3, dst3));
  printf("PASSED - all json_object_equal() tests returned successful\n");
  assert(0 == strcmp(json_object_to_json_string_ext(src1, 1 << 1), json_object_to_json_string_ext(dst1, 1 << 1)));
  assert(0 == strcmp(json_object_to_json_string_ext(src2, 1 << 1), json_object_to_json_string_ext(dst2, 1 << 1)));
  assert(0 == strcmp(json_object_to_json_string_ext(src3, 1 << 1), json_object_to_json_string_ext(dst3, 1 << 1)));
  printf("PASSED - comparison of string output\n");
  json_object_get(dst1);
  assert((-1) == json_object_deep_copy(src1, &(&dst1[dst1_idx]), 0));
  assert(errno == EINVAL);
  json_object_put(dst1);
  printf("PASSED - trying to overrwrite an object that has refcount > 1");
  printf("\nPrinting JSON objects for visual inspection\n");
  printf("------------------------------------------------\n");
  printf(" JSON1\n");
  printf("%s\n", json_object_to_json_string_ext(dst1, 1 << 1));
  printf("------------------------------------------------\n");
  printf("------------------------------------------------\n");
  printf(" JSON2\n");
  printf("%s\n", json_object_to_json_string_ext(dst2, 1 << 1));
  printf("------------------------------------------------\n");
  printf("------------------------------------------------\n");
  printf(" JSON3\n");
  printf("------------------------------------------------\n");
  printf("%s\n", json_object_to_json_string_ext(dst3, 1 << 1));
  printf("------------------------------------------------\n");
  json_object_put(dst1);
  json_object_put(dst2);
  json_object_put(dst3);
  printf("\nTesting deep_copy with a custom serializer set\n");
  json_object *with_serializer = json_object_new_string("notemitted");
  char udata[] = "dummy userdata";
  json_object_set_serializer(with_serializer, my_custom_serializer, udata, 0);
  json_object_object_add(src1, "with_serializer", with_serializer);
  dst1_idx = 0;
  assert((-1) == json_object_deep_copy(src1, &(&dst1[dst1_idx]), 0));
  assert(0 == json_object_deep_copy(src1, &(&dst1[dst1_idx]), my_shallow_copy));
  json_object *dest_with_serializer = json_object_object_get(dst1, "with_serializer");
  assert(dest_with_serializer != 0);
  char *dst_userdata = json_object_get_userdata(dest_with_serializer);
  assert(strcmp(dst_userdata, "dummy userdata") == 0);
  const char *special_output = json_object_to_json_string(dest_with_serializer);
  assert(strcmp(special_output, "OTHER") == 0);
  printf("\ndeep_copy with custom serializer worked OK.\n");
  json_object_put(dst1);
  if (benchmark)
  {
    do_benchmark(src2);
  }
  json_object_put(src1);
  json_object_put(src2);
  json_object_put(src3);
  return 0;
}


/*** DEPENDENCIES:
static const char *json_str3 = "{\"menu\": {  \"id\": \"file\",  \"value\": \"File\",  \"popup\": {    \"menuitem\": [      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}    ]  }}}"
----------------------------
json_c_shallow_copy_fn my_shallow_copy
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
json_object_to_json_string_fn my_custom_serializer
----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}


----------------------------
void *json_object_get_userdata(json_object *jso)
{
  return (jso) ? (jso->_userdata) : (0);
}


----------------------------
static void do_benchmark(json_object *src2)
{
  json_object *dst2 = 0;
  unsigned int dst2_idx = 0;
  int ii;
  int iterations = 1000000;
  time_t start = time(0);
  start = time(0);
  for (ii = 0; ii < iterations; ii += 1)
  {
    dst2_idx = json_tokener_parse(json_object_get_string(src2));
    json_object_put(dst2);
  }

  printf("BENCHMARK - %d iterations of 'dst2 = json_tokener_parse(json_object_get_string(src2))' took %d seconds\n", iterations, (int) (time(0) - start));
  start = time(0);
  dst2_idx = 0;
  for (ii = 0; ii < iterations; ii += 1)
  {
    json_object_deep_copy(src2, &(&dst2[dst2_idx]), 0);
    json_object_put(dst2);
    dst2_idx = 0;
  }

  printf("BENCHMARK - %d iterations of 'json_object_deep_copy(src2, &dst2, NULL)' took %d seconds\n", iterations, (int) (time(0) - start));
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
static const char *json_str2 = "{\"menu\": {    \"header\": \"SVG Viewer\",    \"items\": [        {\"id\": \"Open\"},        {\"id\": \"OpenNew\", \"label\": \"Open New\"},        null,        {\"id\": \"ZoomIn\", \"label\": \"Zoom In\"},        {\"id\": \"ZoomOut\", \"label\": \"Zoom Out\"},        {\"id\": \"OriginalView\", \"label\": \"Original View\"},        null,        {\"id\": \"Quality\", \"another_null\": null},        {\"id\": \"Pause\"},        {\"id\": \"Mute\"},        null,        {\"id\": \"Find\", \"label\": \"Find...\"},        {\"id\": \"FindAgain\", \"label\": \"Find Again\"},        {\"id\": \"Copy\"},        {\"id\": \"CopyAgain\", \"label\": \"Copy Again\"},        {\"id\": \"CopySVG\", \"label\": \"Copy SVG\"},        {\"id\": \"ViewSVG\", \"label\": \"View SVG\"},        {\"id\": \"ViewSource\", \"label\": \"View Source\"},        {\"id\": \"SaveAs\", \"label\": \"Save As\"},        null,        {\"id\": \"Help\"},        {\"id\": \"About\", \"label\": \"About Adobe CVG Viewer...\"}    ]}}"
----------------------------
struct json_object *json_object_object_get(const struct json_object *jso, const char *key)
{
  struct json_object *result = 0;
  json_object_object_get_ex(jso, key, &result);
  return result;
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
static const char *json_str1 = "{    \"glossary\": {        \"title\": \"example glossary\",        \"GlossDiv\": {            \"number\": 16446744073709551615,            \"title\": \"S\",            \"null_obj\": null,             \"exist\": false,            \"quantity\":20,            \"univalent\":19.8,            \"GlossList\": {                \"GlossEntry\": {                    \"ID\": \"SGML\",                    \"SortAs\": \"SGML\",                    \"GlossTerm\": \"Standard Generalized Markup Language\",                    \"Acronym\": \"SGML\",                    \"Abbrev\": \"ISO 8879:1986\",                    \"GlossDef\": {                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",                        \"GlossSeeAlso\": [\"GML\", \"XML\"]                    },                    \"GlossSee\": \"markup\"                }            }        }    }}"
----------------------------
None
----------------------------
const char *json_object_to_json_string_ext(struct json_object *jso, int flags)
{
  return json_object_to_json_string_length(jso, flags, 0);
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
int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  unsigned int shallow_copy_idx = 0;
  int rc;
  if (((!src) || (!dst)) || (*dst))
  {
    errno = EINVAL;
    return -1;
  }
  if ((&shallow_copy[shallow_copy_idx]) == 0)
  {
    shallow_copy_idx = json_c_shallow_copy_default;
  }
  rc = json_object_deep_copy_recursive(src, 0, 0, 4294967295U, dst, shallow_copy);
  if (rc < 0)
  {
    json_object_put(*dst);
    *dst = 0;
  }
  return rc;
}


----------------------------
None
----------------------------
***/


