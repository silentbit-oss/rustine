// element in merge of:  _lil_env_t,_lil_var_t,lil_var_t
struct _lil_var_t
{
  char *n;
  char *w;
  struct _lil_env_t *env;
  lil_value_t v;
}
/*** DEPENDENCIES:
typedef struct _lil_value_t *lil_value_t
----------------------------
typedef struct _lil_env_t *lil_env_t
----------------------------
None
----------------------------
***/


