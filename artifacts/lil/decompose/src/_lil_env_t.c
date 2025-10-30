// element in merge of:  _lil_env_t,_lil_var_t,lil_var_t
struct _lil_env_t
{
  struct _lil_env_t *parent;
  lil_func_t func;
  lil_value_t catcher_for;
  lil_var_t *var;
  size_t vars;
  hashmap_t varmap;
  lil_value_t retval;
  int retval_set;
  int breakrun;
}
/*** DEPENDENCIES:
typedef struct _lil_func_t *lil_func_t
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
typedef struct _hashmap_t
{
  struct hashcell_t cell[256];
} hashmap_t
----------------------------
None
----------------------------
***/


