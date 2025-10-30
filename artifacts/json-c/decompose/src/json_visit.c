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


/*** DEPENDENCIES:
typedef int json_c_visit_userfunc(json_object *jso, int flags, json_object *parent_jso, const char *jso_key, size_t *jso_index, void *userarg)
----------------------------
None
----------------------------
None
----------------------------
***/


