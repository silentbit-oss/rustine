int main(int argc, char **argv)
{
  if (0)
  {
    mc_set_debug(1);
  }
  json_object *my_object = json_object_new_object();
  json_object_object_add(my_object, "foo1", json_object_new_string("bar1"));
  json_object_object_add(my_object, "foo2", json_object_new_string("bar2"));
  json_object_object_add(my_object, "deleteme", json_object_new_string("bar2"));
  json_object_object_add(my_object, "foo3", json_object_new_string("bar3"));
  printf("==== delete-in-loop test starting ====\n");
  int orig_count = 0;
  char *key0 = 0;
  unsigned int key0_idx = 0;
  struct json_object *val0 = 0;
  unsigned int val0_idx = 0;
  for (struct lh_entry *entrykey0 = lh_table_head(json_object_get_object(my_object)), entry_nextkey0 = 0;   {
    if (entrykey0)
    {
      key0_idx = (char *) lh_entry_k(entrykey0);
      val0_idx = (struct json_object *) lh_entry_v(entrykey0);
      entry_nextkey0_idx = lh_entry_next(entrykey0);
    }
    ;
    entrykey0;
  }
; entrykey0_idx = &entry_nextkey0[entry_nextkey0_idx])
  {
    printf("Key at index %d is [%s] %d", orig_count, key0, (&val0[val0_idx]) == 0);
    if (strcmp(key0, "deleteme") == 0)
    {
      json_object_object_del(my_object, key0);
      printf(" (deleted)\n");
    }
    else
      printf(" (kept)\n");
    orig_count += 1;
  }

  unsigned int entry_nextkey0_idx = 0;
  printf("==== replace-value first loop starting ====\n");
  const char *original_key = 0;
  unsigned int original_key_idx = 0;
  orig_count = 0;
  char *key = 0;
  unsigned int key_idx = 0;
  struct json_object *val = 0;
  unsigned int val_idx = 0;
  for (struct lh_entry *entrykey = lh_table_head(json_object_get_object(my_object)), entry_nextkey = 0;   {
    if (entrykey)
    {
      key_idx = (char *) lh_entry_k(entrykey);
      val_idx = (struct json_object *) lh_entry_v(entrykey);
      entry_nextkey_idx = lh_entry_next(entrykey);
    }
    ;
    entrykey;
  }
; entrykey_idx = &entry_nextkey[entry_nextkey_idx])
  {
    printf("Key at index %d is [%s] %d\n", orig_count, key, (&val[val_idx]) == 0);
    orig_count += 1;
    if (strcmp(key, "foo2") != 0)
    {
      continue;
    }
    printf("replacing value for key [%s]\n", key);
    original_key_idx = &key[key_idx];
    json_object_object_add(my_object, key, json_object_new_string("zzz"));
  }

  unsigned int entry_nextkey_idx = 0;
  printf("==== second loop starting ====\n");
  int new_count = 0;
  int retval = 0;
  char *key2 = 0;
  unsigned int key2_idx = 0;
  struct json_object *val2 = 0;
  unsigned int val2_idx = 0;
  for (struct lh_entry *entrykey2 = lh_table_head(json_object_get_object(my_object)), entry_nextkey2 = 0;   {
    if (entrykey2)
    {
      key2_idx = (char *) lh_entry_k(entrykey2);
      val2_idx = (struct json_object *) lh_entry_v(entrykey2);
      entry_nextkey2_idx = lh_entry_next(entrykey2);
    }
    ;
    entrykey2;
  }
; entrykey2_idx = &entry_nextkey2[entry_nextkey2_idx])
  {
    printf("Key at index %d is [%s] %d\n", new_count, key2, (&val2[val2_idx]) == 0);
    new_count += 1;
    if (strcmp(key2, "foo2") != 0)
    {
      continue;
    }
    printf("pointer for key [%s] does %smatch\n", key2, ((&key2[key2_idx]) == (&original_key[original_key_idx])) ? ("") : ("NOT "));
    if ((&key2[key2_idx]) != (&original_key[original_key_idx]))
    {
      retval = 1;
    }
  }

  unsigned int entry_nextkey2_idx = 0;
  if (new_count != orig_count)
  {
    printf("mismatch between original count (%d) and new count (%d)\n", orig_count, new_count);
    retval = 1;
  }
  json_object_put(my_object);
  return retval;
}


/*** DEPENDENCIES:
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}


----------------------------
void json_object_object_del(struct json_object *jso, const char *key)
{
  assert(json_object_get_type(jso) == json_type_object);
  lh_table_delete(JC_OBJECT(jso)->c_object, key);
}


----------------------------
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}


----------------------------
struct json_object *json_object_new_string(const char *s)
{
  return _json_object_new_string(s, strlen(s));
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
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
struct lh_table *json_object_get_object(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return JC_OBJECT_C(jso)->c_object;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
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
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
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


