static int emit_object(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  printf("flags: 0x%x, key: %s, index: %ld, value: %s\n", flags, (jso_key) ? (jso_key) : ("(null)"), (jso_index) ? ((long) (*jso_index)) : (-1L), json_object_to_json_string(jso));
  return 0;
}


/*** DEPENDENCIES:
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
None
----------------------------
***/


static int pop_and_stop(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  (void) emit_object(jso, flags, parent_jso, jso_key, jso_index, userarg);
  if ((jso_key != 0) && (strcmp(jso_key, "subobj1") == 0))
  {
    printf("POP after handling subobj1\n");
    return 767;
  }
  if ((jso_key != 0) && (strcmp(jso_key, "obj3") == 0))
  {
    printf("STOP after handling obj3\n");
    return 7867;
  }
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc emit_object
----------------------------
None
----------------------------
***/


static int err_on_subobj2(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  (void) emit_object(jso, flags, parent_jso, jso_key, jso_index, userarg);
  if ((jso_key != 0) && (strcmp(jso_key, "subobj2") == 0))
  {
    printf("ERROR after handling subobj1\n");
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc emit_object
----------------------------
None
----------------------------
***/


static int pop_array(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  (void) emit_object(jso, flags, parent_jso, jso_key, jso_index, userarg);
  if ((jso_index != 0) && ((*jso_index) == 0))
  {
    printf("POP after handling array[0]\n");
    return 767;
  }
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc emit_object
----------------------------
None
----------------------------
***/


static int stop_array(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  (void) emit_object(jso, flags, parent_jso, jso_key, jso_index, userarg);
  if ((jso_index != 0) && ((*jso_index) == 0))
  {
    printf("STOP after handling array[1]\n");
    return 7867;
  }
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc emit_object
----------------------------
None
----------------------------
***/


static int err_return(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  printf("flags: 0x%x, key: %s, index: %ld, value: %s\n", flags, (jso_key) ? (jso_key) : ("(null)"), (jso_index) ? ((long) (*jso_index)) : (-1L), json_object_to_json_string(jso));
  return 100;
}


/*** DEPENDENCIES:
const char *json_object_to_json_string(struct json_object *jso)
{
  return json_object_to_json_string_ext(jso, 1 << 0);
}


----------------------------
None
----------------------------
***/


static int skip_arrays(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
{
  (void) emit_object(jso, flags, parent_jso, jso_key, jso_index, userarg);
  if (json_object_get_type(jso) == json_type_array)
  {
    return 7547;
  }
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc emit_object
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
***/


int main(void)
{
  if (0)
  {
    mc_set_debug(1);
  }
  const char *input = "{		\"obj1\": 123,		\"obj2\": {			\"subobj1\": \"aaa\",			\"subobj2\": \"bbb\",			\"subobj3\": [ \"elem1\", \"elem2\", true ],		},		\"obj3\": 1.234,		\"obj4\": [ true, false, null ]	}";
  json_object *jso = json_tokener_parse(input);
  printf("jso.to_string()=%s\n", json_object_to_json_string(jso));
  int rv;
  rv = json_c_visit(jso, 0, emit_object, 0);
  printf("json_c_visit(emit_object)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, skip_arrays, 0);
  printf("json_c_visit(skip_arrays)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, pop_and_stop, 0);
  printf("json_c_visit(pop_and_stop)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, err_on_subobj2, 0);
  printf("json_c_visit(err_on_subobj2)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, pop_array, 0);
  printf("json_c_visit(pop_array)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, stop_array, 0);
  printf("json_c_visit(stop_array)=%d\n", rv);
  printf("================================\n\n");
  rv = json_c_visit(jso, 0, err_return, 0);
  printf("json_c_visit(err_return)=%d\n", rv);
  printf("================================\n\n");
  json_object_put(jso);
  return 0;
}


/*** DEPENDENCIES:
static json_c_visit_userfunc err_return
----------------------------
static json_c_visit_userfunc emit_object
----------------------------
static json_c_visit_userfunc err_on_subobj2
----------------------------
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
static json_c_visit_userfunc skip_arrays
----------------------------
static json_c_visit_userfunc pop_array
----------------------------
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
static json_c_visit_userfunc pop_and_stop
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
static json_c_visit_userfunc stop_array
----------------------------
None
----------------------------
***/


