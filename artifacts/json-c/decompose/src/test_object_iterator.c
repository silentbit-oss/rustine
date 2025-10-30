int main(int atgc, char **argv)
{
  const char *input = "{\n		\"string_of_digits\": \"123\",\n		\"regular_number\": 222,\n		\"decimal_number\": 99.55,\n		\"boolean_true\": true,\n		\"boolean_false\": false,\n		\"big_number\": 2147483649,\n		\"a_null\": null,\n		}";
  struct json_object *new_obj;
  unsigned int new_obj_idx = 0;
  struct json_object_iterator it;
  struct json_object_iterator itEnd;
  it = json_object_iter_init_default();
  new_obj_idx = json_tokener_parse(input);
  it = json_object_iter_begin(new_obj);
  itEnd = json_object_iter_end(new_obj);
  while (!json_object_iter_equal(&it, &itEnd))
  {
    printf("%s\n", json_object_iter_peek_name(&it));
    printf("%s\n", json_object_to_json_string(json_object_iter_peek_value(&it)));
    json_object_iter_next(&it);
  }

  json_object_put(new_obj);
  return 0;
}


/*** DEPENDENCIES:
struct json_object_iterator json_object_iter_begin(struct json_object *obj)
{
  struct json_object_iterator iter;
  struct lh_table *pTable;
  unsigned int pTable_idx = 0;
  pTable_idx = json_object_get_object(obj);
  do
  {
  }
  while (0);
  iter.opaque_ = lh_table_head(pTable);
  return iter;
}


----------------------------
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator json_object_iter_init_default(void)
{
  struct json_object_iterator iter;
  iter.opaque_ = 0;
  return iter;
}


----------------------------
struct json_object *json_object_iter_peek_value(const struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return (struct json_object *) lh_entry_v((const struct lh_entry *) iter->opaque_);
}


----------------------------
const char *json_object_iter_peek_name(const struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return (const char *) ((const struct lh_entry *) iter->opaque_)->k;
}


----------------------------
json_bool json_object_iter_equal(const struct json_object_iterator *iter1, const struct json_object_iterator *iter2)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return iter1->opaque_ == iter2->opaque_;
}


----------------------------
struct json_object_iterator
{
  const void *opaque_;
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
void json_object_iter_next(struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  iter->opaque_ = lh_entry_next((const struct lh_entry *) iter->opaque_);
}


----------------------------
struct json_object_iterator json_object_iter_end(const struct json_object *obj)
{
  struct json_object_iterator iter;
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  iter.opaque_ = kObjectEndIterValue;
  return iter;
}


----------------------------
None
----------------------------
***/


