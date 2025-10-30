static void string_replace_all_occurrences_with_char(char *s, const char *occur, char repl_char)
{
  size_t slen = strlen(s);
  size_t skip = strlen(occur) - 1;
  char *p = s;
  unsigned int p_idx = 0;
  while (p_idx = strstr(p_idx, occur))
  {
    p[p_idx] = repl_char;
    p_idx += 1;
    slen -= skip;
    memmove(p, (&p[p_idx]) + skip, (slen - ((&p[p_idx]) - s)) + 1);
  }

}


/*** DEPENDENCIES:
***/


static int is_valid_index(const char *path, size_t *idx)
{
  size_t i;
  size_t len = strlen(path);
  if (len == 1)
  {
    if ((path[0] >= '0') && (path[0] <= '9'))
    {
      *idx = path[0] - '0';
      return 1;
    }
    errno = EINVAL;
    return 0;
  }
  if (path[0] == '0')
  {
    errno = EINVAL;
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!((path[i] >= '0') && (path[i] <= '9')))
    {
      errno = EINVAL;
      return 0;
    }
  }

  *idx = strtoull(path, 0, 10);
  return 1;
}


/*** DEPENDENCIES:
***/


static int json_pointer_get_single_path(struct json_object *obj, char *path, struct json_object **value, size_t *idx)
{
  unsigned int obj_idx = 0;
  if (json_object_is_type(obj, json_type_array))
  {
    if (!is_valid_index(path, idx))
    {
      return -1;
    }
    if ((*idx) >= json_object_array_length(obj))
    {
      errno = ENOENT;
      return -1;
    }
    obj_idx = json_object_array_get_idx(obj_idx, *idx);
    if (obj)
    {
      if (value)
      {
        *value = &obj[obj_idx];
      }
      return 0;
    }
    errno = ENOENT;
    return -1;
  }
  string_replace_all_occurrences_with_char(path, "~1", '/');
  string_replace_all_occurrences_with_char(path, "~0", '~');
  if (!json_object_object_get_ex(obj, path, value))
  {
    errno = ENOENT;
    return -1;
  }
  return 0;
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
static void string_replace_all_occurrences_with_char(char *s, const char *occur, char repl_char)
{
  size_t slen = strlen(s);
  size_t skip = strlen(occur) - 1;
  char *p = s;
  unsigned int p_idx = 0;
  while (p_idx = strstr(p_idx, occur))
  {
    p[p_idx] = repl_char;
    p_idx += 1;
    slen -= skip;
    memmove(p, (&p[p_idx]) + skip, (slen - ((&p[p_idx]) - s)) + 1);
  }

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
size_t json_object_array_length(const struct json_object *jso)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_length(JC_ARRAY_C(jso)->c_array);
}


----------------------------
static int is_valid_index(const char *path, size_t *idx)
{
  size_t i;
  size_t len = strlen(path);
  if (len == 1)
  {
    if ((path[0] >= '0') && (path[0] <= '9'))
    {
      *idx = path[0] - '0';
      return 1;
    }
    errno = EINVAL;
    return 0;
  }
  if (path[0] == '0')
  {
    errno = EINVAL;
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!((path[i] >= '0') && (path[i] <= '9')))
    {
      errno = EINVAL;
      return 0;
    }
  }

  *idx = strtoull(path, 0, 10);
  return 1;
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


static int json_pointer_result_get_recursive(struct json_object *obj, char *path, struct json_pointer_get_result *res)
{
  unsigned int path_idx = 0;
  struct json_object *parent_obj = obj;
  size_t idx = 0;
  char *endp;
  unsigned int endp_idx = 0;
  int rc;
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  path_idx += 1;
  endp_idx = strchr(path, '/');
  if (endp)
  {
    endp[endp_idx] = '\0';
  }
  if (rc = json_pointer_get_single_path(obj, path, &obj, &idx))
  {
    return rc;
  }
  if (endp)
  {
    endp[endp_idx] = '/';
    return json_pointer_result_get_recursive(obj, endp, res);
  }
  if (res)
  {
    res->parent = parent_obj;
    res->obj = obj;
    if (json_object_is_type(res->parent, json_type_array))
    {
      res->index_in_parent = idx;
    }
    else
      res->key_in_parent = &path[path_idx];
  }
  return 0;
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
static int json_pointer_get_single_path(struct json_object *obj, char *path, struct json_object **value, size_t *idx)
{
  unsigned int obj_idx = 0;
  if (json_object_is_type(obj, json_type_array))
  {
    if (!is_valid_index(path, idx))
    {
      return -1;
    }
    if ((*idx) >= json_object_array_length(obj))
    {
      errno = ENOENT;
      return -1;
    }
    obj_idx = json_object_array_get_idx(obj_idx, *idx);
    if (obj)
    {
      if (value)
      {
        *value = &obj[obj_idx];
      }
      return 0;
    }
    errno = ENOENT;
    return -1;
  }
  string_replace_all_occurrences_with_char(path, "~1", '/');
  string_replace_all_occurrences_with_char(path, "~0", '~');
  if (!json_object_object_get_ex(obj, path, value))
  {
    errno = ENOENT;
    return -1;
  }
  return 0;
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
None
----------------------------
***/


static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
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
static int json_pointer_result_get_recursive(struct json_object *obj, char *path, struct json_pointer_get_result *res)
{
  unsigned int path_idx = 0;
  struct json_object *parent_obj = obj;
  size_t idx = 0;
  char *endp;
  unsigned int endp_idx = 0;
  int rc;
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  path_idx += 1;
  endp_idx = strchr(path, '/');
  if (endp)
  {
    endp[endp_idx] = '\0';
  }
  if (rc = json_pointer_get_single_path(obj, path, &obj, &idx))
  {
    return rc;
  }
  if (endp)
  {
    endp[endp_idx] = '/';
    return json_pointer_result_get_recursive(obj, endp, res);
  }
  if (res)
  {
    res->parent = parent_obj;
    res->obj = obj;
    if (json_object_is_type(res->parent, json_type_array))
    {
      res->index_in_parent = idx;
    }
    else
      res->key_in_parent = &path[path_idx];
  }
  return 0;
}


----------------------------
None
----------------------------
***/


int json_pointer_getf(struct json_object *obj, struct json_object **res, const char *path_fmt, ...)
{
  char *path_copy = 0;
  int rc = 0;
  va_list args;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    if (res)
    {
      *res = obj;
    }
    goto out;
  }
  rc = json_pointer_object_get_recursive(obj, path_copy, res);
  out:
  free(path_copy);

  return rc;
}


/*** DEPENDENCIES:
static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


static int json_object_array_put_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  return json_object_array_put_idx(parent, idx, value);
}


/*** DEPENDENCIES:
int json_object_array_put_idx(struct json_object *jso, size_t idx, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_put_idx(JC_ARRAY(jso)->c_array, idx, val);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
}
----------------------------
static int json_pointer_result_get_recursive(struct json_object *obj, char *path, struct json_pointer_get_result *res)
{
  unsigned int path_idx = 0;
  struct json_object *parent_obj = obj;
  size_t idx = 0;
  char *endp;
  unsigned int endp_idx = 0;
  int rc;
  if (path[0 + path_idx] != '/')
  {
    errno = EINVAL;
    return -1;
  }
  path_idx += 1;
  endp_idx = strchr(path, '/');
  if (endp)
  {
    endp[endp_idx] = '\0';
  }
  if (rc = json_pointer_get_single_path(obj, path, &obj, &idx))
  {
    return rc;
  }
  if (endp)
  {
    endp[endp_idx] = '/';
    return json_pointer_result_get_recursive(obj, endp, res);
  }
  if (res)
  {
    res->parent = parent_obj;
    res->obj = obj;
    if (json_object_is_type(res->parent, json_type_array))
    {
      res->index_in_parent = idx;
    }
    else
      res->key_in_parent = &path[path_idx];
  }
  return 0;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct json_pointer_get_result
{
  struct json_object *parent;
  struct json_object *obj;
  const char *key_in_parent;
  uint32_t index_in_parent;
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


static int json_pointer_set_single_path(struct json_object *parent, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  if (json_object_is_type(parent, json_type_array))
  {
    size_t idx;
    if ((path[0] == '-') && (path[1] == '\0'))
    {
      return json_object_array_add(parent, value);
    }
    if (!is_valid_index(path, &idx))
    {
      return -1;
    }
    return array_set_cb(parent, idx, value, priv);
  }
  if (json_object_is_type(parent, json_type_object))
  {
    return json_object_object_add(parent, path, value);
  }
  errno = ENOENT;
  return -1;
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
static int is_valid_index(const char *path, size_t *idx)
{
  size_t i;
  size_t len = strlen(path);
  if (len == 1)
  {
    if ((path[0] >= '0') && (path[0] <= '9'))
    {
      *idx = path[0] - '0';
      return 1;
    }
    errno = EINVAL;
    return 0;
  }
  if (path[0] == '0')
  {
    errno = EINVAL;
    return 0;
  }
  for (i = 0; i < len; i += 1)
  {
    if (!((path[i] >= '0') && (path[i] <= '9')))
    {
      errno = EINVAL;
      return 0;
    }
  }

  *idx = strtoull(path, 0, 10);
  return 1;
}


----------------------------
typedef int (*json_pointer_array_set_cb)(json_object *parent, size_t idx, json_object *value, void *priv)
----------------------------
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
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


/*** DEPENDENCIES:
static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
}


----------------------------
typedef int (*json_pointer_array_set_cb)(json_object *parent, size_t idx, json_object *value, void *priv)
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
static int json_pointer_set_single_path(struct json_object *parent, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  if (json_object_is_type(parent, json_type_array))
  {
    size_t idx;
    if ((path[0] == '-') && (path[1] == '\0'))
    {
      return json_object_array_add(parent, value);
    }
    if (!is_valid_index(path, &idx))
    {
      return -1;
    }
    return array_set_cb(parent, idx, value, priv);
  }
  if (json_object_is_type(parent, json_type_object))
  {
    return json_object_object_add(parent, path, value);
  }
  errno = ENOENT;
  return -1;
}


----------------------------
None
----------------------------
***/


int json_pointer_set(struct json_object **obj, const char *path, struct json_object *value)
{
  return json_pointer_set_with_array_cb(obj, path, value, json_object_array_put_idx_cb, 0);
}


/*** DEPENDENCIES:
static int json_object_array_put_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  return json_object_array_put_idx(parent, idx, value);
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
None
----------------------------
***/


int json_pointer_setf(struct json_object **obj, struct json_object *value, const char *path_fmt, ...)
{
  char *endp;
  unsigned int endp_idx = 0;
  char *path_copy = 0;
  struct json_object *set = 0;
  unsigned int set_idx = 0;
  va_list args;
  int rc = 0;
  if ((!obj) || (!path_fmt))
  {
    errno = EINVAL;
    return -1;
  }
  __builtin_va_start(args);
  rc = vasprintf(&path_copy, path_fmt, args);
  ;
  if (rc < 0)
  {
    return rc;
  }
  if (path_copy[0] == '\0')
  {
    json_object_put(*obj);
    *obj = value;
    goto out;
  }
  if (path_copy[0] != '/')
  {
    errno = EINVAL;
    rc = -1;
    goto out;
  }
  if ((endp_idx = strrchr(path_copy, '/')) == path_copy)
  {
    set_idx = *obj;
    goto set_single_path;
  }
  endp[endp_idx] = '\0';
  rc = json_pointer_object_get_recursive(*obj, path_copy, &(&set[set_idx]));
  if (rc)
  {
    goto out;
  }
  set_single_path:
  (&endp[endp_idx])++;

  endp_idx += 1;
  rc = json_pointer_set_single_path(set, endp, value, json_object_array_put_idx_cb, 0);
  out:
  free(path_copy);

  return rc;
}


/*** DEPENDENCIES:
static int json_pointer_object_get_recursive(struct json_object *obj, char *path, struct json_object **value)
{
  struct json_pointer_get_result res;
  int rc;
  rc = json_pointer_result_get_recursive(obj, path, &res);
  if (rc)
  {
    return rc;
  }
  if (value)
  {
    *value = res.obj;
  }
  return 0;
}


----------------------------
static int json_pointer_set_single_path(struct json_object *parent, const char *path, struct json_object *value, json_pointer_array_set_cb array_set_cb, void *priv)
{
  if (json_object_is_type(parent, json_type_array))
  {
    size_t idx;
    if ((path[0] == '-') && (path[1] == '\0'))
    {
      return json_object_array_add(parent, value);
    }
    if (!is_valid_index(path, &idx))
    {
      return -1;
    }
    return array_set_cb(parent, idx, value, priv);
  }
  if (json_object_is_type(parent, json_type_object))
  {
    return json_object_object_add(parent, path, value);
  }
  errno = ENOENT;
  return -1;
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
static int json_object_array_put_idx_cb(struct json_object *parent, size_t idx, struct json_object *value, void *priv)
{
  return json_object_array_put_idx(parent, idx, value);
}


----------------------------
None
----------------------------
***/


