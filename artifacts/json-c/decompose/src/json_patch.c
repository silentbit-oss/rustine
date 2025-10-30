static int json_patch_apply_test(struct json_object **res, struct json_object *patch_elem, const char *path, struct json_patch_error *patch_error)
{
  struct json_object *value1;
  struct json_object *value2;
  if (!json_object_object_get_ex(patch_elem, "value", &value1))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (json_pointer_get(*res, path, &value2))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_equal(value1, value2))
  {
    do
    {
      patch_error->errno_code = ENOENT;
      patch_error->errmsg = "Value of element referenced by 'path' field did not match 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);
    }

    default:
    {
      if (value != 0)
      {
        *value = 0;
      }
      return 0;
    }

  }

}


----------------------------
None
----------------------------
int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res)
{
  struct json_pointer_get_result jpres;
  int rc;
  rc = json_pointer_get_internal(obj, path, &jpres);
  if (rc)
  {
    return rc;
  }
  if (res)
  {
    *res = jpres.obj;
  }
  return 0;
}


----------------------------
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
None
----------------------------
***/


static int __json_patch_apply_remove(struct json_pointer_get_result *jpres)
{
  if (json_object_is_type(jpres->parent, json_type_array))
  {
    return json_object_array_del_idx(jpres->parent, jpres->index_in_parent, 1);
  }
  else
    if (jpres->parent && jpres->key_in_parent)
  {
    json_object_object_del(jpres->parent, jpres->key_in_parent);
    return 0;
  }
  else
  {
    (void) json_object_put(jpres->obj);
    jpres->obj = 0;
    return 0;
  }
}


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
}
----------------------------
int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
}


----------------------------
int json_object_array_del_idx(struct json_object *jso, size_t idx, size_t count)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_del_idx(JC_ARRAY(jso)->c_array, idx, count);
}


----------------------------
void json_object_object_del(struct json_object *jso, const char *key)
{
  assert(json_object_get_type(jso) == json_type_object);
  lh_table_delete(JC_OBJECT(jso)->c_object, key);
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
***/


static int json_patch_apply_remove(struct json_object **res, const char *path, struct json_patch_error *patch_error)
{
  struct json_pointer_get_result jpres;
  int rc;
  if (json_pointer_get_internal(*res, path, &jpres))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = __json_patch_apply_remove(&jpres);
  if (rc < 0)
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Unable to remove path referenced by 'path' field";
      errno = 0;
    }
    while (0);
  }
  if (jpres.parent == 0)
  {
    *res = 0;
  }
  return rc;
}


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
}
----------------------------
static int __json_patch_apply_remove(struct json_pointer_get_result *jpres)
{
  if (json_object_is_type(jpres->parent, json_type_array))
  {
    return json_object_array_del_idx(jpres->parent, jpres->index_in_parent, 1);
  }
  else
    if (jpres->parent && jpres->key_in_parent)
  {
    json_object_object_del(jpres->parent, jpres->key_in_parent);
    return 0;
  }
  else
  {
    (void) json_object_put(jpres->obj);
    jpres->obj = 0;
    return 0;
  }
}


----------------------------
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res)
{
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  int rc;
  if ((!obj) || (!path))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0] == '\0')
  {
    res->parent = 0;
    res->obj = obj;
    res->key_in_parent = 0;
    res->index_in_parent = UINT32_MAX;
    return 0;
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  rc = json_pointer_result_get_recursive(obj, path_copy, res);
  if (((rc == 0) && json_object_is_type(res->parent, json_type_object)) && res->key_in_parent)
  {
    res->key_in_parent = path + (res->key_in_parent - (&path_copy[path_copy_idx]));
  }
  free(path_copy);
  return rc;
}


----------------------------
None
----------------------------
***/


static int json_object_array_insert_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  int *add = priv;
  if (idx > json_object_array_length(parent))
  {
    errno = EINVAL;
    return -1;
  }
  if (*add)
  {
    rc = json_object_array_insert_idx(parent, idx, value);
  }
  else
    rc = json_object_array_put_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}


/*** DEPENDENCIES:
int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
int json_object_array_insert_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_insert_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
None
----------------------------
***/


static int json_object_array_move_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  struct json_pointer_get_result *from = priv;
  size_t len = json_object_array_length(parent);
  if (parent == from->parent)
  {
    len += 1;
  }
  if (idx > len)
  {
    errno = EINVAL;
    return -1;
  }
  rc = json_object_array_insert_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
}
----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
int json_object_array_insert_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_insert_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
None
----------------------------
***/


static int json_patch_apply_move_copy(struct json_object **res, struct json_object *patch_elem, const char *path, int move, struct json_patch_error *patch_error)
{
  json_pointer_array_set_cb array_set_cb;
  struct json_pointer_get_result from;
  struct json_object *jfrom;
  const char *from_s;
  unsigned int from_s_idx = 0;
  size_t from_s_len;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "from", &jfrom))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch does not contain a 'from' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  from_s_idx = json_object_get_string(jfrom);
  from_s_len = strlen(from_s);
  if (strncmp(from_s, path, from_s_len) == 0)
  {
    if (from_s_len == strlen(path))
    {
      return 0;
    }
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Invalid attempt to move parent under a child";
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_get_internal(*res, from_s, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by from field") : ("Invalid from field");
      errno = 0;
    }
    while (0);
    return rc;
  }
  json_object_get(from.obj);
  if (!move)
  {
    array_set_cb = json_object_array_insert_idx_cb;
  }
  else
  {
    rc = __json_patch_apply_remove(&from);
    if (rc < 0)
    {
      json_object_put(from.obj);
      return rc;
    }
    array_set_cb = json_object_array_move_cb;
  }
  rc = json_pointer_set_with_array_cb(res, path, from.obj, array_set_cb, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(from.obj);
  }
  return rc;
}


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
}
----------------------------
static int json_object_array_insert_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  int *add = priv;
  if (idx > json_object_array_length(parent))
  {
    errno = EINVAL;
    return -1;
  }
  if (*add)
  {
    rc = json_object_array_insert_idx(parent, idx, value);
  }
  else
    rc = json_object_array_put_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}


----------------------------
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
int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  unsigned int path_idx = 0;
  const char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  struct json_object *set = 0;
  int rc;
  if ((!obj) || (!(&path[path_idx])))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0 + path_idx] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    return 0;
  }
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  if ((endp_idx = strrchr(path, '/')) == (&path[path_idx]))
  {
    path_idx += 1;
    return json_pointer_set_single_path(*obj, path, value, array_set_cb, priv);
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  path_copy[((&endp[endp_idx]) - (&path[path_idx])) + path_copy_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &set);
  free(path_copy);
  if (rc)
  {
    return rc;
  }
  endp_idx += 1;
  return json_pointer_set_single_path(set, endp, value, array_set_cb, priv);
}


----------------------------
json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);
    }

    default:
    {
      if (value != 0)
      {
        *value = 0;
      }
      return 0;
    }

  }

}


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
static int __json_patch_apply_remove(struct json_pointer_get_result *jpres)
{
  if (json_object_is_type(jpres->parent, json_type_array))
  {
    return json_object_array_del_idx(jpres->parent, jpres->index_in_parent, 1);
  }
  else
    if (jpres->parent && jpres->key_in_parent)
  {
    json_object_object_del(jpres->parent, jpres->key_in_parent);
    return 0;
  }
  else
  {
    (void) json_object_put(jpres->obj);
    jpres->obj = 0;
    return 0;
  }
}


----------------------------
static int json_object_array_move_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  struct json_pointer_get_result *from = priv;
  size_t len = json_object_array_length(parent);
  if (parent == from->parent)
  {
    len += 1;
  }
  if (idx > len)
  {
    errno = EINVAL;
    return -1;
  }
  rc = json_object_array_insert_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
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
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
typedef int (*json_pointer_array_set_cb)(json_object *parent, size_t idx, json_object *value, void *priv)
----------------------------
int json_pointer_get_internal(struct json_object *obj, const char *path, struct json_pointer_get_result *res)
{
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  int rc;
  if ((!obj) || (!path))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0] == '\0')
  {
    res->parent = 0;
    res->obj = obj;
    res->key_in_parent = 0;
    res->index_in_parent = UINT32_MAX;
    return 0;
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  rc = json_pointer_result_get_recursive(obj, path_copy, res);
  if (((rc == 0) && json_object_is_type(res->parent, json_type_object)) && res->key_in_parent)
  {
    res->key_in_parent = path + (res->key_in_parent - (&path_copy[path_copy_idx]));
  }
  free(path_copy);
  return rc;
}


----------------------------
None
----------------------------
***/


static int json_patch_apply_add_replace(struct json_object **res, struct json_object *patch_elem, const char *path, int add, struct json_patch_error *patch_error)
{
  struct json_object *value;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "value", &value))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if ((!add) && json_pointer_get(*res, path, 0))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_set_with_array_cb(res, path, json_object_get(value), json_object_array_insert_idx_cb, &add);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(value);
  }
  return rc;
}


/*** DEPENDENCIES:
static int json_object_array_insert_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  int rc;
  int *add = priv;
  if (idx > json_object_array_length(parent))
  {
    errno = EINVAL;
    return -1;
  }
  if (*add)
  {
    rc = json_object_array_insert_idx(parent, idx, value);
  }
  else
    rc = json_object_array_put_idx(parent, idx, value);
  if (rc < 0)
  {
    errno = EINVAL;
  }
  return rc;
}


----------------------------
int json_pointer_set_with_array_cb(struct json_object **obj, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  unsigned int path_idx = 0;
  const char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  unsigned int path_copy_idx = 0;
  struct json_object *set = 0;
  int rc;
  if ((!obj) || (!(&path[path_idx])))
  {
    errno = EINVAL;
    return -1;
  }
  if (path[0 + path_idx] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    return 0;
  }
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  if ((endp_idx = strrchr(path, '/')) == (&path[path_idx]))
  {
    path_idx += 1;
    return json_pointer_set_single_path(*obj, path, value, array_set_cb, priv);
  }
  if (!(path_copy_idx = strdup(path)))
  {
    errno = ENOMEM;
    return -1;
  }
  path_copy[((&endp[endp_idx]) - (&path[path_idx])) + path_copy_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &set);
  free(path_copy);
  if (rc)
  {
    return rc;
  }
  endp_idx += 1;
  return json_pointer_set_single_path(set, endp, value, array_set_cb, priv);
}


----------------------------
json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);
    }

    default:
    {
      if (value != 0)
      {
        *value = 0;
      }
      return 0;
    }

  }

}


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
int json_pointer_get(struct json_object *obj, const char *path, struct json_object **res)
{
  struct json_pointer_get_result jpres;
  int rc;
  rc = json_pointer_get_internal(obj, path, &jpres);
  if (rc)
  {
    return rc;
  }
  if (res)
  {
    *res = jpres.obj;
  }
  return 0;
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
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
None
----------------------------
***/


// hint:  ['rc_ref is a mutable refrence to int']
int helper_json_patch_apply_1(int * const rc_ref, struct json_object * const patch, struct json_object ** const base, struct json_patch_error * const patch_error, size_t ii)
{
  int rc = *rc_ref;
  struct json_object *jop;
  struct json_object *jpath;
  struct json_object *patch_elem = json_object_array_get_idx(patch, ii);
  const char *op;
  unsigned int op_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  patch_error->patch_failure_idx = ii;
  if (!json_object_object_get_ex(patch_elem, "op", &jop))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain 'op' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  op_idx = json_object_get_string(jop);
  if (!json_object_object_get_ex(patch_elem, "path", &jpath))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain 'path' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  path_idx = json_object_get_string(jpath);
  if (!strcmp(op, "test"))
  {
    rc = json_patch_apply_test(base, patch_elem, path, patch_error);
  }
  else
    if (!strcmp(op, "remove"))
  {
    rc = json_patch_apply_remove(base, path, patch_error);
  }
  else
    if (!strcmp(op, "add"))
  {
    rc = json_patch_apply_add_replace(base, patch_elem, path, 1, patch_error);
  }
  else
    if (!strcmp(op, "replace"))
  {
    rc = json_patch_apply_add_replace(base, patch_elem, path, 0, patch_error);
  }
  else
    if (!strcmp(op, "move"))
  {
    rc = json_patch_apply_move_copy(base, patch_elem, path, 1, patch_error);
  }
  else
    if (!strcmp(op, "copy"))
  {
    rc = json_patch_apply_move_copy(base, patch_elem, path, 0, patch_error);
  }
  else
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object has invalid 'op' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (rc < 0)
  {
    break;
  }
  *rc_ref = rc;
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
static int json_patch_apply_test(struct json_object **res, struct json_object *patch_elem, const char *path, struct json_patch_error *patch_error)
{
  struct json_object *value1;
  struct json_object *value2;
  if (!json_object_object_get_ex(patch_elem, "value", &value1))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (json_pointer_get(*res, path, &value2))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_equal(value1, value2))
  {
    do
    {
      patch_error->errno_code = ENOENT;
      patch_error->errmsg = "Value of element referenced by 'path' field did not match 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  return 0;
}


----------------------------
json_bool json_object_object_get_ex(const struct json_object *jso, const char *key, struct json_object **value)
{
  if (value != 0)
  {
    *value = 0;
  }
  if (0 == jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return lh_table_lookup_ex(JC_OBJECT_C(jso)->c_object, (const void *) key, (void **) value);
    }

    default:
    {
      if (value != 0)
      {
        *value = 0;
      }
      return 0;
    }

  }

}


----------------------------
static int json_patch_apply_remove(struct json_object **res, const char *path, struct json_patch_error *patch_error)
{
  struct json_pointer_get_result jpres;
  int rc;
  if (json_pointer_get_internal(*res, path, &jpres))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = __json_patch_apply_remove(&jpres);
  if (rc < 0)
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Unable to remove path referenced by 'path' field";
      errno = 0;
    }
    while (0);
  }
  if (jpres.parent == 0)
  {
    *res = 0;
  }
  return rc;
}


----------------------------
static int json_patch_apply_move_copy(struct json_object **res, struct json_object *patch_elem, const char *path, int move, struct json_patch_error *patch_error)
{
  json_pointer_array_set_cb array_set_cb;
  struct json_pointer_get_result from;
  struct json_object *jfrom;
  const char *from_s;
  unsigned int from_s_idx = 0;
  size_t from_s_len;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "from", &jfrom))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch does not contain a 'from' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  from_s_idx = json_object_get_string(jfrom);
  from_s_len = strlen(from_s);
  if (strncmp(from_s, path, from_s_len) == 0)
  {
    if (from_s_len == strlen(path))
    {
      return 0;
    }
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Invalid attempt to move parent under a child";
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_get_internal(*res, from_s, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by from field") : ("Invalid from field");
      errno = 0;
    }
    while (0);
    return rc;
  }
  json_object_get(from.obj);
  if (!move)
  {
    array_set_cb = json_object_array_insert_idx_cb;
  }
  else
  {
    rc = __json_patch_apply_remove(&from);
    if (rc < 0)
    {
      json_object_put(from.obj);
      return rc;
    }
    array_set_cb = json_object_array_move_cb;
  }
  rc = json_pointer_set_with_array_cb(res, path, from.obj, array_set_cb, &from);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(from.obj);
  }
  return rc;
}


----------------------------
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
}
----------------------------
static int json_patch_apply_add_replace(struct json_object **res, struct json_object *patch_elem, const char *path, int add, struct json_patch_error *patch_error)
{
  struct json_object *value;
  int rc;
  if (!json_object_object_get_ex(patch_elem, "value", &value))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain a 'value' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if ((!add) && json_pointer_get(*res, path, 0))
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = (errno == ENOENT) ? ("Did not find element referenced by path field") : ("Invalid path field");
      errno = 0;
    }
    while (0);
    return -1;
  }
  rc = json_pointer_set_with_array_cb(res, path, json_object_get(value), json_object_array_insert_idx_cb, &add);
  if (rc)
  {
    do
    {
      patch_error->errno_code = errno;
      patch_error->errmsg = "Failed to set value at path referenced by 'path' field";
      errno = 0;
    }
    while (0);
    json_object_put(value);
  }
  return rc;
}


----------------------------
struct json_object *json_object_array_get_idx(const struct json_object *jso, size_t idx)
{
  assert(json_object_get_type(jso) == json_type_array);
  return (struct json_object *) array_list_get_idx(JC_ARRAY_C(jso)->c_array, idx);
}


----------------------------
None
----------------------------
***/


int json_patch_apply(struct json_object *copy_from, struct json_object *patch, struct json_object **base, struct json_patch_error *patch_error)
{
  unsigned int patch_error_idx = 0;
  size_t ii;
  int rc = 0;
  struct json_patch_error placeholder;
  if (!(&patch_error[patch_error_idx]))
  {
    patch_error_idx = &placeholder;
  }
  patch_error->patch_failure_idx = 18446744073709551615UL;
  patch_error->errno_code = 0;
  if (((base == 0) || (((*base) == 0) && (copy_from == 0))) || (((*base) != 0) && (copy_from != 0)))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Exactly one of *base or copy_from must be non-NULL";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (!json_object_is_type(patch, json_type_array))
  {
    do
    {
      patch_error->errno_code = EFAULT;
      patch_error->errmsg = "Patch object is not of type json_type_array";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (copy_from != 0)
  {
    if (json_object_deep_copy(copy_from, base, 0) < 0)
    {
      do
      {
        patch_error->errno_code = ENOMEM;
        patch_error->errmsg = "Unable to copy copy_from using json_object_deep_copy()";
        errno = 0;
      }
      while (0);
      return -1;
    }
  }
  for (ii = 0; ii < json_object_array_length(patch); ii += 1)
  {
    helper_json_patch_apply_1(&rc, patch, base, patch_error, ii);
  }

  return rc;
}


/*** DEPENDENCIES:
int json_object_is_type(const struct json_object *jso, enum json_type type)
{
  if (!jso)
  {
    return type == json_type_null;
  }
  return jso->o_type == type;
}


----------------------------
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
int helper_json_patch_apply_1(int * const rc_ref, struct json_object * const patch, struct json_object ** const base, struct json_patch_error * const patch_error, size_t ii)
{
  int rc = *rc_ref;
  struct json_object *jop;
  struct json_object *jpath;
  struct json_object *patch_elem = json_object_array_get_idx(patch, ii);
  const char *op;
  unsigned int op_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  patch_error->patch_failure_idx = ii;
  if (!json_object_object_get_ex(patch_elem, "op", &jop))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain 'op' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  op_idx = json_object_get_string(jop);
  if (!json_object_object_get_ex(patch_elem, "path", &jpath))
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object does not contain 'path' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  path_idx = json_object_get_string(jpath);
  if (!strcmp(op, "test"))
  {
    rc = json_patch_apply_test(base, patch_elem, path, patch_error);
  }
  else
    if (!strcmp(op, "remove"))
  {
    rc = json_patch_apply_remove(base, path, patch_error);
  }
  else
    if (!strcmp(op, "add"))
  {
    rc = json_patch_apply_add_replace(base, patch_elem, path, 1, patch_error);
  }
  else
    if (!strcmp(op, "replace"))
  {
    rc = json_patch_apply_add_replace(base, patch_elem, path, 0, patch_error);
  }
  else
    if (!strcmp(op, "move"))
  {
    rc = json_patch_apply_move_copy(base, patch_elem, path, 1, patch_error);
  }
  else
    if (!strcmp(op, "copy"))
  {
    rc = json_patch_apply_move_copy(base, patch_elem, path, 0, patch_error);
  }
  else
  {
    do
    {
      patch_error->errno_code = EINVAL;
      patch_error->errmsg = "Patch object has invalid 'op' field";
      errno = 0;
    }
    while (0);
    return -1;
  }
  if (rc < 0)
  {
    break;
  }
  *rc_ref = rc;
}


----------------------------
struct json_patch_error
{
  int errno_code;
  size_t patch_failure_idx;
  const char *errmsg;
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


