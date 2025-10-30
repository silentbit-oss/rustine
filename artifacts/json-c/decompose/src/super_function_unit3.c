// element in merge of:  json_object_all_values_equal,json_object_equal,json_array_equal
static int json_object_all_values_equal(struct json_object *jso1, struct json_object *jso2)
{
  struct json_object_iter iter;
  struct json_object *sub;
  assert(json_object_get_type(jso1) == json_type_object);
  assert(json_object_get_type(jso2) == json_type_object);
  for (iter.entry = lh_table_head(json_object_get_object(jso1)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso2)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
    if (!json_object_equal(iter.val, sub))
    {
      return 0;
    }
  }

  for (iter.entry = lh_table_head(json_object_get_object(jso2)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    if (!lh_table_lookup_ex(JC_OBJECT(jso1)->c_object, (void *) iter.key, (void **) ((void *) (&sub))))
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}


----------------------------
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
None
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
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}


----------------------------
json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (e != 0)
  {
    if (v != 0)
    {
      *v = lh_entry_v(e);
    }
    return 1;
  }
  if (v != 0)
  {
    *v = 0;
  }
  return 0;
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
inline static struct json_object_object *JC_OBJECT(struct json_object *jso)
{
  return (void *) jso;
}


----------------------------
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}


----------------------------
None
----------------------------
***/


// element in merge of:  json_object_all_values_equal,json_object_equal,json_array_equal
int json_object_equal(struct json_object *jso1, struct json_object *jso2)
{
  if (jso1 == jso2)
  {
    return 1;
  }
  if ((!jso1) || (!jso2))
  {
    return 0;
  }
  if (jso1->o_type != jso2->o_type)
  {
    return 0;
  }
  switch (jso1->o_type)
  {
    case json_type_boolean:
    {
      return JC_BOOL(jso1)->c_boolean == JC_BOOL(jso2)->c_boolean;
    }

    case json_type_double:
    {
      return JC_DOUBLE(jso1)->c_double == JC_DOUBLE(jso2)->c_double;
    }

    case json_type_int:
    {
      struct json_object_int *int1 = JC_INT(jso1);
      struct json_object_int *int2 = JC_INT(jso2);
      if (int1->cint_type == json_object_int_type_int64)
      {
        if (int2->cint_type == json_object_int_type_int64)
        {
          return int1->cint.c_int64 == int2->cint.c_int64;
        }
        if (int1->cint.c_int64 < 0)
        {
          return 0;
        }
        return ((uint64_t) int1->cint.c_int64) == int2->cint.c_uint64;
      }
      if (int2->cint_type == json_object_int_type_uint64)
      {
        return int1->cint.c_uint64 == int2->cint.c_uint64;
      }
      if (int2->cint.c_int64 < 0)
      {
        return 0;
      }
      return int1->cint.c_uint64 == ((uint64_t) int2->cint.c_int64);
    }

    case json_type_string:
    {
      return (_json_object_get_string_len(JC_STRING(jso1)) == _json_object_get_string_len(JC_STRING(jso2))) && (memcmp(get_string_component(jso1), get_string_component(jso2), _json_object_get_string_len(JC_STRING(jso1))) == 0);
    }

    case json_type_object:
    {
      return json_object_all_values_equal(jso1, jso2);
    }

    case json_type_array:
    {
      return json_array_equal(jso1, jso2);
    }

    case json_type_null:
    {
      return 1;
    }

  }

  ;
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
inline static struct json_object_boolean *JC_BOOL(struct json_object *jso)
{
  return (void *) jso;
}


----------------------------
inline static ssize_t _json_object_get_string_len(const struct json_object_string *jso)
{
  ssize_t len;
  len = jso->len;
  return (len < 0) ? (-((ssize_t) len)) : (len);
}


----------------------------
struct json_object_int
{
  struct json_object base;
  enum json_object_int_type cint_type;
  union 
  {
    int64_t c_int64;
    uint64_t c_uint64;
  } cint;
}
----------------------------
inline static const char *get_string_component(const struct json_object *jso)
{
  return get_string_component_mutable((void *) ((uintptr_t) ((const void *) jso)));
}


----------------------------
inline static struct json_object_string *JC_STRING(struct json_object *jso)
{
  return (void *) jso;
}


----------------------------
inline static struct json_object_double *JC_DOUBLE(struct json_object *jso)
{
  return (void *) jso;
}


----------------------------
inline static struct json_object_int *JC_INT(struct json_object *jso)
{
  return (void *) jso;
}


----------------------------
None
----------------------------
***/


// element in merge of:  json_object_all_values_equal,json_object_equal,json_array_equal
static int json_array_equal(struct json_object *jso1, struct json_object *jso2)
{
  size_t len;
  size_t i;
  len = json_object_array_length(jso1);
  if (len != json_object_array_length(jso2))
  {
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!json_object_equal(json_object_array_get_idx(jso1, i), json_object_array_get_idx(jso2, i)))
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
None
----------------------------
***/


