struct _lil_t
{
  const char *code;
  const char *rootcode;
  size_t clen;
  size_t head;
  int ignoreeol;
  lil_func_t *cmd;
  size_t cmds;
  size_t syscmds;
  hashmap_t cmdmap;
  char *catcher;
  int in_catcher;
  char *dollarprefix;
  lil_env_t env;
  lil_env_t rootenv;
  lil_env_t downenv;
  lil_value_t empty;
  int error;
  size_t err_head;
  char *err_msg;
  lil_callback_proc_t callback[8];
  size_t parse_depth;
  void *data;
  char *embed;
  size_t embedlen;
}
/*** DEPENDENCIES:
typedef struct _hashmap_t
{
  struct hashcell_t cell[256];
} hashmap_t
----------------------------
typedef void (*lil_callback_proc_t)(void)
----------------------------
typedef struct _lil_func_t *lil_func_t
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
typedef struct _lil_env_t *lil_env_t
----------------------------
***/


