struct _lil_func_t
{
  char *name;
  lil_value_t code;
  lil_list_t argnames;
  lil_func_proc_t proc;
}
/*** DEPENDENCIES:
typedef lil_value_t (*lil_func_proc_t)(lil_t lil, size_t argc, lil_value_t *argv)
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
typedef struct _lil_list_t *lil_list_t
----------------------------
***/


