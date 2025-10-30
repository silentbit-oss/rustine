int main(int argc, char **argv)
{
  struct json_object *int1 = json_object_new_int(0);
  struct json_object *int2 = json_object_new_int(1);
  struct json_object *int3 = json_object_new_int(1);
  struct json_object *int4 = json_object_new_int(-1);
  struct json_object *uint1 = json_object_new_uint64(0);
  struct json_object *uint2 = json_object_new_uint64(1);
  struct json_object *uint3 = json_object_new_uint64(1);
  struct json_object *uint4 = json_object_new_uint64(((uint64_t) INT64_MAX) + 100);
  if (!json_object_equal(int1, int2))
  {
    printf("JSON integer comparison is correct\n");
  }
  else
    printf("JSON integer comparison failed\n");
  if (json_object_equal(int1, int1))
  {
    printf("JSON same object comparison is correct\n");
  }
  else
    printf("JSON same object comparison failed\n");
  if (json_object_equal(int2, int3))
  {
    printf("JSON same integer comparison is correct\n");
  }
  else
    printf("JSON same integer comparison failed\n");
  if (!json_object_equal(uint1, uint2))
  {
    printf("JSON usigned integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer comparison failed\n");
  if (json_object_equal(uint1, uint1))
  {
    printf("JSON same usigned object comparison is correct\n");
  }
  else
    printf("JSON same usigned object comparison failed\n");
  if (json_object_equal(uint2, uint3))
  {
    printf("JSON same usigned integer comparison is correct\n");
  }
  else
    printf("JSON same usigned integer comparison failed\n");
  if (json_object_equal(int2, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int2, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint2))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (!json_object_equal(int4, uint4))
  {
    printf("JSON integer & usigned integer comparison is correct\n");
  }
  else
    printf("JSON integer & usigned integer comparison failed\n");
  if (json_object_equal(uint2, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint2, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int2))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  if (!json_object_equal(uint4, int4))
  {
    printf("JSON usigned integer & integer comparison is correct\n");
  }
  else
    printf("JSON usigned integer & integer comparison failed\n");
  json_object_put(int1);
  json_object_put(int2);
  json_object_put(int3);
  json_object_put(int4);
  json_object_put(uint1);
  json_object_put(uint2);
  json_object_put(uint3);
  json_object_put(uint4);
  struct json_object *str1 = json_object_new_string("TESTSTRING");
  struct json_object *str2 = json_object_new_string("TESTSTRING");
  struct json_object *str3 = json_object_new_string("DIFFERENT");
  if (json_object_equal(str1, str2))
  {
    printf("Comparing equal strings is correct\n");
  }
  else
    printf("Comparing equal strings failed\n");
  if (!json_object_equal(str1, str3))
  {
    printf("Comparing different strings is correct\n");
  }
  else
    printf("Comparing different strings failed\n");
  json_object_put(str1);
  json_object_put(str2);
  json_object_put(str3);
  struct json_object *dbl1 = json_object_new_double(3.14159);
  struct json_object *dbl2 = json_object_new_double(3.14159);
  struct json_object *dbl3 = json_object_new_double(3.0);
  if (json_object_equal(dbl1, dbl2))
  {
    printf("Comparing equal doubles is correct\n");
  }
  else
    printf("Comparing equal doubles failed\n");
  if (!json_object_equal(dbl1, dbl3))
  {
    printf("Comparing different doubles is correct\n");
  }
  else
    printf("Comparing different doubles failed\n");
  json_object_put(dbl1);
  json_object_put(dbl2);
  json_object_put(dbl3);
  struct json_object *ar1 = json_object_new_array();
  struct json_object *ar2 = json_object_new_array();
  struct json_object *ar3 = json_object_new_array();
  struct json_object *ar4 = json_object_new_array();
  json_object_array_add(ar1, json_object_new_int(1));
  json_object_array_add(ar1, json_object_new_int(2));
  json_object_array_add(ar2, json_object_new_int(1));
  json_object_array_add(ar2, json_object_new_int(2));
  json_object_array_add(ar3, json_object_new_int(1));
  json_object_array_add(ar3, json_object_new_int(1));
  if (json_object_equal(ar1, ar2))
  {
    printf("Comparing equal arrays is correct\n");
  }
  else
    printf("Comparing equal arrays failed\n");
  json_object_array_add(ar2, json_object_new_int(1));
  if (!json_object_equal(ar1, ar2))
  {
    printf("Comparing arrays of different len is correct\n");
  }
  else
    printf("Comparing arrays of different len failed\n");
  if (!json_object_equal(ar1, ar3))
  {
    printf("Comparing different arrays is correct\n");
  }
  else
    printf("Comparing different arrays failed\n");
  if (!json_object_equal(ar1, ar4))
  {
    printf("Comparing different arrays (one empty) is correct\n");
  }
  else
    printf("Comparing different arrays (one empty) failed\n");
  json_object_put(ar1);
  json_object_put(ar2);
  json_object_put(ar3);
  json_object_put(ar4);
  struct json_object *obj1 = json_object_new_object();
  struct json_object *obj2 = json_object_new_object();
  json_object_object_add(obj1, "test1", json_object_new_int(123));
  json_object_object_add(obj1, "test2", json_object_new_int(321));
  json_object_object_add(obj1, "test3", json_object_new_int(320));
  json_object_object_add(obj1, "test4", json_object_new_int(319));
  json_object_object_add(obj1, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test5", json_object_new_int(318));
  json_object_object_add(obj2, "test4", json_object_new_int(319));
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test2", json_object_new_int(321));
  json_object_object_add(obj2, "test1", json_object_new_int(123));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing JSON object with different key order is correct\n");
  }
  else
    printf("Comparing JSON object with different key order is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(234));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj2, "test3", json_object_new_int(320));
  json_object_object_add(obj2, "test6", json_object_new_int(321));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test6", json_object_new_int(321));
  if (json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_object_add(obj1, "test7", json_object_new_int(322));
  if (!json_object_equal(obj1, obj2))
  {
    printf("Comparing different objects is correct\n");
  }
  else
    printf("Comparing different objects is incorrect\n");
  json_object_put(obj1);
  json_object_put(obj2);
  struct json_object *int5 = json_object_new_int(0);
  struct json_object *dbl5 = json_object_new_double(3.14159);
  if (!json_object_equal(int5, 0))
  {
    printf("JSON integer and NULL comparison is correct\n");
  }
  else
    printf("JSON integer and NULL comparison failed\n");
  if (!json_object_equal(0, dbl5))
  {
    printf("JSON NULL and double comparison is correct\n");
  }
  else
    printf("JSON NULL and double comparison failed\n");
  if (!json_object_equal(int5, dbl5))
  {
    printf("JSON integer and double comparison is correct\n");
  }
  else
    printf("JSON integer and double comparison failed\n");
  json_object_put(int5);
  json_object_put(dbl5);
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
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}


----------------------------
None
----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
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
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


