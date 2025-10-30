// element in merge of:  _json_c_visit,helper__json_c_visit_2,helper__json_c_visit_1
static int _json_c_visit(json_object *jso, json_object *parent_jso, const char *jso_key, size_t *jso_index, json_c_visit_userfunc *userfunc, void *userarg)
{
  int userret = userfunc(jso, 0, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 0:
    {
      break;
    }

    case 7547:

    case 767:

    case 7867:

    case -1:
    {
      return userret;
    }

    default:
    {
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;
    }

  }

  switch (json_object_get_type(jso))
  {
    case json_type_null:

    case json_type_boolean:

    case json_type_double:

    case json_type_int:

    case json_type_string:
    {
      return 0;
    }

    case json_type_object:
    {
      helper__json_c_visit_2(&userret, &entry_nextkey_idx, jso, userfunc, userarg);
    }

    case json_type_array:
    {
      helper__json_c_visit_1(&userret, jso, userfunc, userarg);
    }

    default:
    {
      fprintf(stderr, "INTERNAL ERROR: _json_c_visit found object of unknown type: %d\n", json_object_get_type(jso));
      return -1;
    }

  }

  userret = userfunc(jso, 0x02, parent_jso, jso_key, jso_index, userarg);
  switch (userret)
  {
    case 7547:

    case 767:

    case 0:
    {
      return 0;
    }

    case 7867:

    case -1:
    {
      return userret;
    }

    default:
    {
      fprintf(stderr, "ERROR: invalid return value from json_c_visit userfunc: %d\n", userret);
      return -1;
    }

  }

}


/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
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
None
----------------------------
None
----------------------------
***/


// element in merge of:  _json_c_visit,helper__json_c_visit_2,helper__json_c_visit_1
// hint:  ['userret_ref is a mutable refrence to int', 'entry_nextkey_idx_ref is a mutable refrence to unsigned int']
int helper__json_c_visit_2(int * const userret_ref, unsigned int * const entry_nextkey_idx_ref, json_object * const jso, json_c_visit_userfunc * const userfunc, void * const userarg)
{
  int userret = *userret_ref;
  unsigned int entry_nextkey_idx = *entry_nextkey_idx_ref;
  char *key = 0;
  unsigned int key_idx = 0;
  struct json_object *child = 0;
  unsigned int child_idx = 0;
  for (struct lh_entry *entrykey = lh_table_head(json_object_get_object(jso)), entry_nextkey = 0;   {
    if (entrykey)
    {
      key_idx = (char *) lh_entry_k(entrykey);
      child_idx = (struct json_object *) lh_entry_v(entrykey);
      entry_nextkey_idx = lh_entry_next(entrykey);
    }
    ;
    entrykey;
  }
; entrykey_idx = &entry_nextkey[entry_nextkey_idx])
  {
    userret = _json_c_visit(child, jso, key, 0, userfunc, userarg);
    if (userret == 767)
    {
      break;
    }
    if ((userret == 7867) || (userret == (-1)))
    {
      return userret;
    }
    if ((userret != 0) && (userret != 7547))
    {
      fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
      return -1;
    }
  }

  unsigned int entry_nextkey_idx = 0;
  break;
  *userret_ref = userret;
  *entry_nextkey_idx_ref = entry_nextkey_idx;
}


/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}


----------------------------
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
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
None
----------------------------
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}


----------------------------
None
----------------------------
***/


// element in merge of:  _json_c_visit,helper__json_c_visit_2,helper__json_c_visit_1
// hint:  ['userret_ref is a mutable refrence to int']
int helper__json_c_visit_1(int * const userret_ref, json_object * const jso, json_c_visit_userfunc * const userfunc, void * const userarg)
{
  int userret = *userret_ref;
  size_t array_len = json_object_array_length(jso);
  size_t ii;
  for (ii = 0; ii < array_len; ii += 1)
  {
    json_object *child = json_object_array_get_idx(jso, ii);
    unsigned int child_idx = 0;
    userret = _json_c_visit(child, jso, 0, &ii, userfunc, userarg);
    if (userret == 767)
    {
      break;
    }
    if ((userret == 7867) || (userret == (-1)))
    {
      return userret;
    }
    if ((userret != 0) && (userret != 7547))
    {
      fprintf(stderr, "INTERNAL ERROR: _json_c_visit returned %d\n", userret);
      return -1;
    }
  }

  break;
  *userret_ref = userret;
}


/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
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
None
----------------------------
***/


