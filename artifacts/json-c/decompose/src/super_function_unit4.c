// element in merge of:  helper_json_object_deep_copy_recursive_1,json_object_deep_copy_recursive,helper_json_object_deep_copy_recursive_2
// hint:  ['iter_ref is a mutable refrence to ']
int helper_json_object_deep_copy_recursive_1(struct json_object_iter * const iter_ref, struct json_object * const src, struct json_object ** const dst, json_c_shallow_copy_fn * const shallow_copy)
{
  struct json_object_iter iter = *iter_ref;
  for (iter.entry = lh_table_head(json_object_get_object(src)); (iter.entry) ? ((iter.key = (char *) lh_entry_k(iter.entry), iter.val = (struct json_object *) lh_entry_v(iter.entry), iter.entry)) : (0); iter.entry = lh_entry_next(iter.entry))
  {
    struct json_object *jso = 0;
    unsigned int jso_idx = 0;
    if (!iter.val)
    {
      jso_idx = 0;
    }
    else
      if (json_object_deep_copy_recursive(iter.val, src, iter.key, 4294967295U, &(&jso[jso_idx]), shallow_copy) < 0)
    {
      json_object_put(jso);
      return -1;
    }
    if (json_object_object_add(*dst, iter.key, jso) < 0)
    {
      json_object_put(jso);
      return -1;
    }
  }

  break;
  *iter_ref = iter;
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
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
----------------------------
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}


----------------------------
None
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


// element in merge of:  helper_json_object_deep_copy_recursive_1,json_object_deep_copy_recursive,helper_json_object_deep_copy_recursive_2
static int json_object_deep_copy_recursive(struct json_object *src, struct json_object *parent, const char *key_in_parent, size_t index_in_parent, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy)
{
  struct json_object_iter iter;
  size_t src_array_len;
  size_t ii;
  int shallow_copy_rc = 0;
  shallow_copy_rc = shallow_copy(src, parent, key_in_parent, index_in_parent, dst);
  if (shallow_copy_rc < 1)
  {
    errno = EINVAL;
    return -1;
  }
  assert((*dst) != 0);
  switch (src->o_type)
  {
    case json_type_object:
    {
      helper_json_object_deep_copy_recursive_1(&iter, src, dst, shallow_copy);
    }

    case json_type_array:
    {
      helper_json_object_deep_copy_recursive_2(&src_array_len, &ii, src, dst, shallow_copy);
    }

    default:
    {
      break;
    }

  }

  if (shallow_copy_rc != 2)
  {
    return json_object_copy_serializer_data(src, *dst);
  }
  return 0;
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
----------------------------
None
----------------------------
static int json_object_copy_serializer_data(struct json_object *src, struct json_object *dst)
{
  if ((!src->_userdata) && (!src->_user_delete))
  {
    return 0;
  }
  if ((dst->_to_json_string == json_object_userdata_to_json_string) || (dst->_to_json_string == _json_object_userdata_to_json_string))
  {
    char *p;
    unsigned int p_idx = 0;
    assert(src->_userdata);
    p_idx = strdup(src->_userdata);
    if ((&p[p_idx]) == 0)
    {
      _json_c_set_last_err("json_object_copy_serializer_data: out of memory\n");
      return -1;
    }
    dst->_userdata = &p[p_idx];
  }
  else
  {
    _json_c_set_last_err("json_object_copy_serializer_data: unable to copy unknown serializer data: %p\n", (void *) dst->_to_json_string);
    return -1;
  }
  dst->_user_delete = src->_user_delete;
  return 0;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_json_object_deep_copy_recursive_1,json_object_deep_copy_recursive,helper_json_object_deep_copy_recursive_2
// hint:  ['src_array_len_ref is a mutable refrence to size_t', 'ii_ref is a mutable refrence to size_t']
int helper_json_object_deep_copy_recursive_2(size_t * const src_array_len_ref, size_t * const ii_ref, struct json_object * const src, struct json_object ** const dst, json_c_shallow_copy_fn * const shallow_copy)
{
  size_t src_array_len = *src_array_len_ref;
  size_t ii = *ii_ref;
  src_array_len = json_object_array_length(src);
  for (ii = 0; ii < src_array_len; ii += 1)
  {
    struct json_object *jso = 0;
    unsigned int jso_idx = 0;
    struct json_object *jso1 = json_object_array_get_idx(src, ii);
    if (!jso1)
    {
      jso_idx = 0;
    }
    else
      if (json_object_deep_copy_recursive(jso1, src, 0, ii, &(&jso[jso_idx]), shallow_copy) < 0)
    {
      json_object_put(jso);
      return -1;
    }
    if (json_object_array_add(*dst, jso) < 0)
    {
      json_object_put(jso);
      return -1;
    }
  }

  break;
  *src_array_len_ref = src_array_len;
  *ii_ref = ii;
}


/*** DEPENDENCIES:
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst)
----------------------------
None
----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
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
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
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


