static char *do_system(size_t argc, char **argv)
{
  char *cmd = 0;
  unsigned int cmd_idx = 0;
  int cmdlen = 0;
  size_t i;
  FILE *p;
  unsigned int p_idx = 0;
  for (i = 0; i < argc; i += 1)
  {
    size_t len = strlen(argv[i]);
    if (i != 0)
    {
      cmd_idx = realloc(cmd_idx, cmdlen + 1);
      cmd[cmdlen + cmd_idx] = ' ';
      cmdlen += 1;
    }
    cmd_idx = realloc(cmd_idx, cmdlen + len);
    memcpy((&cmd[cmd_idx]) + cmdlen, argv[i], len);
    cmdlen += len;
  }

  cmd_idx = realloc(cmd_idx, cmdlen + 1);
  cmd[cmdlen + cmd_idx] = 0;
  p_idx = popen(cmd, "r");
  free(cmd);
  if (p)
  {
    char *retval = 0;
    unsigned int retval_idx = 0;
    size_t size = 0;
    char buff[1024];
    ssize_t bytes;
    while (bytes = fread(buff, 1, 1024, p))
    {
      retval_idx = realloc(retval_idx, size + bytes);
      memcpy((&retval[retval_idx]) + size, buff, bytes);
      size += bytes;
    }

    retval_idx = realloc(retval_idx, size + 1);
    retval[size + retval_idx] = 0;
    pclose(p);
    return retval;
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
***/


static lil_value_t fnc_writechar(lil_t lil, size_t argc, lil_value_t *argv)
{
  if (!argc)
  {
    return 0;
  }
  printf("%c", (char) lil_to_integer(argv[0]));
  return 0;
}


/*** DEPENDENCIES:
typedef struct _lil_value_t *lil_value_t
----------------------------
lilint_t lil_to_integer(lil_value_t val)
{
  return (lilint_t) atoll(lil_to_string(val));
}


----------------------------
typedef struct _lil_t *lil_t
----------------------------
***/


static lil_value_t fnc_system(lil_t lil, size_t argc, lil_value_t *argv)
{
  const char **sargv = malloc((sizeof(char *)) * (argc + 1));
  lil_value_t r = 0;
  char *rv;
  unsigned int rv_idx = 0;
  size_t i;
  if (argc == 0)
  {
    return 0;
  }
  for (i = 0; i < argc; i += 1)
    sargv[i] = lil_to_string(argv[i]);

  sargv[argc] = 0;
  rv_idx = do_system(argc, (char **) sargv);
  if (rv)
  {
    r = lil_alloc_string(rv);
    free(rv);
  }
  free(sargv);
  return r;
}


/*** DEPENDENCIES:
const char *lil_to_string(lil_value_t val)
{
  return (val && val->l) ? (val->d) : ("");
}


----------------------------
typedef struct _lil_t *lil_t
----------------------------
lil_value_t lil_alloc_string(const char *str)
{
  return alloc_value(str);
}


----------------------------
static char *do_system(size_t argc, char **argv)
{
  char *cmd = 0;
  unsigned int cmd_idx = 0;
  int cmdlen = 0;
  size_t i;
  FILE *p;
  unsigned int p_idx = 0;
  for (i = 0; i < argc; i += 1)
  {
    size_t len = strlen(argv[i]);
    if (i != 0)
    {
      cmd_idx = realloc(cmd_idx, cmdlen + 1);
      cmd[cmdlen + cmd_idx] = ' ';
      cmdlen += 1;
    }
    cmd_idx = realloc(cmd_idx, cmdlen + len);
    memcpy((&cmd[cmd_idx]) + cmdlen, argv[i], len);
    cmdlen += len;
  }

  cmd_idx = realloc(cmd_idx, cmdlen + 1);
  cmd[cmdlen + cmd_idx] = 0;
  p_idx = popen(cmd, "r");
  free(cmd);
  if (p)
  {
    char *retval = 0;
    unsigned int retval_idx = 0;
    size_t size = 0;
    char buff[1024];
    ssize_t bytes;
    while (bytes = fread(buff, 1, 1024, p))
    {
      retval_idx = realloc(retval_idx, size + bytes);
      memcpy((&retval[retval_idx]) + size, buff, bytes);
      size += bytes;
    }

    retval_idx = realloc(retval_idx, size + 1);
    retval[size + retval_idx] = 0;
    pclose(p);
    return retval;
  }
  else
  {
    return 0;
  }
}


----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
***/


static int nonint(int argc, const char *argv[])
{
  lil_t lil = lil_new();
  const char *filename = argv[1];
  const char *err_msg;
  size_t pos;
  lil_list_t arglist = lil_alloc_list();
  lil_value_t args;
  lil_value_t result;
  char *tmpcode;
  unsigned int tmpcode_idx = 0;
  int i;
  lil_register(lil, "writechar", fnc_writechar);
  lil_register(lil, "system", fnc_system);
  for (i = 2; i < argc; i += 1)
  {
    lil_list_append(arglist, lil_alloc_string(argv[i]));
  }

  args = lil_list_to_value(arglist, 1);
  lil_free_list(arglist);
  lil_set_var(lil, "argv", args, 0);
  lil_free_value(args);
  tmpcode_idx = malloc(strlen(filename) + 256);
  sprintf(tmpcode, "set __lilmain:code__ [read {%s}]\nif [streq $__lilmain:code__ ''] {print There is no code in the file or the file does not exist} {eval $__lilmain:code__}\n", filename);
  result = lil_parse(lil, tmpcode, 0, 1);
  free(tmpcode);
  lil_free_value(result);
  if (lil_error(lil, &err_msg, &pos))
  {
    fprintf(stderr, "lil: error at %i: %s\n", (int) pos, err_msg);
  }
  lil_free(lil);
  return exit_code;
}


/*** DEPENDENCIES:
lil_list_t lil_alloc_list(void)
{
  lil_list_t list;
  list = calloc(1, sizeof(struct _lil_list_t));
  list->v = 0;
  return list;
}


----------------------------
void lil_list_append(lil_list_t list, lil_value_t val)
{
  if (list->c == list->cap)
  {
    size_t cap = (list->cap) ? (list->cap + (list->cap / 2)) : (32);
    lil_value_t *nv = realloc(list->v, (sizeof(lil_value_t)) * cap);
    if (!nv)
    {
      return;
    }
    list->cap = cap;
    list->v = nv;
  }
  list->v[list->c++] = val;
}


----------------------------
int lil_error(lil_t lil, const char **msg, size_t *pos)
{
  if (!lil->error)
  {
    return 0;
  }
  *msg = lil->err_msg;
  *pos = lil->err_head;
  lil->error = 0;
  return 1;
}


----------------------------
typedef struct _lil_t *lil_t
----------------------------
void lil_free_list(lil_list_t list)
{
  size_t i;
  if (!list)
  {
    return;
  }
  for (i = 0; i < list->c; i += 1)
    lil_free_value(list->v[i]);

  free(list->v);
  free(list);
}


----------------------------
void lil_free(lil_t lil)
{
  size_t i;
  if (!lil)
  {
    return;
  }
  free(lil->err_msg);
  lil_free_value(lil->empty);
  while (lil->env)
  {
    lil_env_t next = lil->env->parent;
    lil_free_env(lil->env);
    lil->env = next;
  }

  for (i = 0; i < lil->cmds; i += 1)
  {
    if (lil->cmd[i]->argnames)
    {
      lil_free_list(lil->cmd[i]->argnames);
    }
    lil_free_value(lil->cmd[i]->code);
    free(lil->cmd[i]->name);
    free(lil->cmd[i]);
  }

  hm_destroy(&lil->cmdmap);
  free(lil->cmd);
  free(lil->dollarprefix);
  free(lil->catcher);
  free(lil);
}


----------------------------
typedef struct _lil_list_t *lil_list_t
----------------------------
int lil_register(lil_t lil, const char *name, lil_func_proc_t proc)
{
  lil_func_t cmd = add_func(lil, name);
  if (!cmd)
  {
    return 0;
  }
  cmd->proc = proc;
  return 1;
}


----------------------------
static int exit_code = 0
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
static lil_value_t fnc_writechar(lil_t lil, size_t argc, lil_value_t *argv)
{
  if (!argc)
  {
    return 0;
  }
  printf("%c", (char) lil_to_integer(argv[0]));
  return 0;
}


----------------------------
lil_value_t lil_alloc_string(const char *str)
{
  return alloc_value(str);
}


----------------------------
static lil_value_t fnc_system(lil_t lil, size_t argc, lil_value_t *argv)
{
  const char **sargv = malloc((sizeof(char *)) * (argc + 1));
  lil_value_t r = 0;
  char *rv;
  unsigned int rv_idx = 0;
  size_t i;
  if (argc == 0)
  {
    return 0;
  }
  for (i = 0; i < argc; i += 1)
    sargv[i] = lil_to_string(argv[i]);

  sargv[argc] = 0;
  rv_idx = do_system(argc, (char **) sargv);
  if (rv)
  {
    r = lil_alloc_string(rv);
    free(rv);
  }
  free(sargv);
  return r;
}


----------------------------
None
----------------------------
lil_value_t lil_list_to_value(lil_list_t list, int do_escape)
{
  lil_value_t val = alloc_value(0);
  size_t i;
  size_t j;
  for (i = 0; i < list->c; i += 1)
  {
    int escape = (do_escape) ? (needs_escape(lil_to_string(list->v[i]))) : (0);
    if (i)
    {
      lil_append_char(val, ' ');
    }
    if (escape)
    {
      lil_append_char(val, '{');
      for (j = 0; j < list->v[i]->l; j += 1)
      {
        if (list->v[i]->d[j] == '{')
        {
          lil_append_string(val, "}\"\\o\"{");
        }
        else
          if (list->v[i]->d[j] == '}')
        {
          lil_append_string(val, "}\"\\c\"{");
        }
        else
          lil_append_char(val, list->v[i]->d[j]);
      }

      lil_append_char(val, '}');
    }
    else
      lil_append_val(val, list->v[i]);
  }

  return val;
}


----------------------------
void lil_free_value(lil_value_t val)
{
  if (!val)
  {
    return;
  }
  free(val->d);
  free(val);
}


----------------------------
None
----------------------------
***/


static lil_value_t fnc_readline(lil_t lil, size_t argc, lil_value_t *argv)
{
  size_t len = 0;
  size_t size = 64;
  char *buffer = malloc(size);
  unsigned int buffer_idx = 0;
  signed char ch;
  lil_value_t retval;
  for (;;)
  {
    ch = fgetc(stdin);
    if (ch == EOF)
    {
      break;
    }
    if (ch == '\r')
    {
      continue;
    }
    if (ch == '\n')
    {
      break;
    }
    if (len < size)
    {
      size += 64;
      buffer_idx = realloc(buffer_idx, size);
    }
    buffer[len + buffer_idx] = ch;
    len += 1;
  }

  buffer_idx = realloc(buffer_idx, len + 1);
  buffer[len + buffer_idx] = 0;
  retval = lil_alloc_string(buffer);
  free(buffer);
  return retval;
}


/*** DEPENDENCIES:
lil_value_t lil_alloc_string(const char *str)
{
  return alloc_value(str);
}


----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
typedef struct _lil_t *lil_t
----------------------------
***/


static void do_exit(lil_t lil, lil_value_t val)
{
  running = 0;
  exit_code = (int) lil_to_integer(val);
}


/*** DEPENDENCIES:
typedef struct _lil_t *lil_t
----------------------------
static int exit_code = 0
----------------------------
lilint_t lil_to_integer(lil_value_t val)
{
  return (lilint_t) atoll(lil_to_string(val));
}


----------------------------
static int running = 1
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
***/


static int repl(void)
{
  char buffer[16384];
  lil_t lil = lil_new();
  lil_register(lil, "writechar", fnc_writechar);
  lil_register(lil, "system", fnc_system);
  lil_register(lil, "readline", fnc_readline);
  printf("Little Interpreted Language Interactive Shell\n");
  lil_callback(lil, 0, (lil_callback_proc_t) do_exit);
  while (running)
  {
    lil_value_t result;
    const char *strres;
    unsigned int strres_idx = 0;
    const char *err_msg;
    size_t pos;
    buffer[0] = 0;
    printf("# ");
    if (!fgets(buffer, 16384, stdin))
    {
      break;
    }
    result = lil_parse(lil, buffer, 0, 0);
    strres_idx = lil_to_string(result);
    if (strres[0 + strres_idx])
    {
      printf("%s\n", strres);
    }
    lil_free_value(result);
    if (lil_error(lil, &err_msg, &pos))
    {
      printf("error at %i: %s\n", (int) pos, err_msg);
    }
  }

  lil_free(lil);
  return exit_code;
}


/*** DEPENDENCIES:
static lil_value_t fnc_readline(lil_t lil, size_t argc, lil_value_t *argv)
{
  size_t len = 0;
  size_t size = 64;
  char *buffer = malloc(size);
  unsigned int buffer_idx = 0;
  signed char ch;
  lil_value_t retval;
  for (;;)
  {
    ch = fgetc(stdin);
    if (ch == EOF)
    {
      break;
    }
    if (ch == '\r')
    {
      continue;
    }
    if (ch == '\n')
    {
      break;
    }
    if (len < size)
    {
      size += 64;
      buffer_idx = realloc(buffer_idx, size);
    }
    buffer[len + buffer_idx] = ch;
    len += 1;
  }

  buffer_idx = realloc(buffer_idx, len + 1);
  buffer[len + buffer_idx] = 0;
  retval = lil_alloc_string(buffer);
  free(buffer);
  return retval;
}


----------------------------
int lil_error(lil_t lil, const char **msg, size_t *pos)
{
  if (!lil->error)
  {
    return 0;
  }
  *msg = lil->err_msg;
  *pos = lil->err_head;
  lil->error = 0;
  return 1;
}


----------------------------
typedef struct _lil_t *lil_t
----------------------------
static void do_exit(lil_t lil, lil_value_t val)
{
  running = 0;
  exit_code = (int) lil_to_integer(val);
}


----------------------------
void lil_free(lil_t lil)
{
  size_t i;
  if (!lil)
  {
    return;
  }
  free(lil->err_msg);
  lil_free_value(lil->empty);
  while (lil->env)
  {
    lil_env_t next = lil->env->parent;
    lil_free_env(lil->env);
    lil->env = next;
  }

  for (i = 0; i < lil->cmds; i += 1)
  {
    if (lil->cmd[i]->argnames)
    {
      lil_free_list(lil->cmd[i]->argnames);
    }
    lil_free_value(lil->cmd[i]->code);
    free(lil->cmd[i]->name);
    free(lil->cmd[i]);
  }

  hm_destroy(&lil->cmdmap);
  free(lil->cmd);
  free(lil->dollarprefix);
  free(lil->catcher);
  free(lil);
}


----------------------------
void lil_callback(lil_t lil, int cb, lil_callback_proc_t proc)
{
  if ((cb < 0) || (cb > 8))
  {
    return;
  }
  lil->callback[cb] = proc;
}


----------------------------
int lil_register(lil_t lil, const char *name, lil_func_proc_t proc)
{
  lil_func_t cmd = add_func(lil, name);
  if (!cmd)
  {
    return 0;
  }
  cmd->proc = proc;
  return 1;
}


----------------------------
static int exit_code = 0
----------------------------
const char *lil_to_string(lil_value_t val)
{
  return (val && val->l) ? (val->d) : ("");
}


----------------------------
static lil_value_t fnc_writechar(lil_t lil, size_t argc, lil_value_t *argv)
{
  if (!argc)
  {
    return 0;
  }
  printf("%c", (char) lil_to_integer(argv[0]));
  return 0;
}


----------------------------
static lil_value_t fnc_system(lil_t lil, size_t argc, lil_value_t *argv)
{
  const char **sargv = malloc((sizeof(char *)) * (argc + 1));
  lil_value_t r = 0;
  char *rv;
  unsigned int rv_idx = 0;
  size_t i;
  if (argc == 0)
  {
    return 0;
  }
  for (i = 0; i < argc; i += 1)
    sargv[i] = lil_to_string(argv[i]);

  sargv[argc] = 0;
  rv_idx = do_system(argc, (char **) sargv);
  if (rv)
  {
    r = lil_alloc_string(rv);
    free(rv);
  }
  free(sargv);
  return r;
}


----------------------------
static int running = 1
----------------------------
None
----------------------------
typedef struct _lil_value_t *lil_value_t
----------------------------
void lil_free_value(lil_value_t val)
{
  if (!val)
  {
    return;
  }
  free(val->d);
  free(val);
}


----------------------------
None
----------------------------
***/


int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    return repl();
  }
  else
    return nonint(argc, argv);
}


/*** DEPENDENCIES:
static int nonint(int argc, const char *argv[])
{
  lil_t lil = lil_new();
  const char *filename = argv[1];
  const char *err_msg;
  size_t pos;
  lil_list_t arglist = lil_alloc_list();
  lil_value_t args;
  lil_value_t result;
  char *tmpcode;
  unsigned int tmpcode_idx = 0;
  int i;
  lil_register(lil, "writechar", fnc_writechar);
  lil_register(lil, "system", fnc_system);
  for (i = 2; i < argc; i += 1)
  {
    lil_list_append(arglist, lil_alloc_string(argv[i]));
  }

  args = lil_list_to_value(arglist, 1);
  lil_free_list(arglist);
  lil_set_var(lil, "argv", args, 0);
  lil_free_value(args);
  tmpcode_idx = malloc(strlen(filename) + 256);
  sprintf(tmpcode, "set __lilmain:code__ [read {%s}]\nif [streq $__lilmain:code__ ''] {print There is no code in the file or the file does not exist} {eval $__lilmain:code__}\n", filename);
  result = lil_parse(lil, tmpcode, 0, 1);
  free(tmpcode);
  lil_free_value(result);
  if (lil_error(lil, &err_msg, &pos))
  {
    fprintf(stderr, "lil: error at %i: %s\n", (int) pos, err_msg);
  }
  lil_free(lil);
  return exit_code;
}


----------------------------
static int repl(void)
{
  char buffer[16384];
  lil_t lil = lil_new();
  lil_register(lil, "writechar", fnc_writechar);
  lil_register(lil, "system", fnc_system);
  lil_register(lil, "readline", fnc_readline);
  printf("Little Interpreted Language Interactive Shell\n");
  lil_callback(lil, 0, (lil_callback_proc_t) do_exit);
  while (running)
  {
    lil_value_t result;
    const char *strres;
    unsigned int strres_idx = 0;
    const char *err_msg;
    size_t pos;
    buffer[0] = 0;
    printf("# ");
    if (!fgets(buffer, 16384, stdin))
    {
      break;
    }
    result = lil_parse(lil, buffer, 0, 0);
    strres_idx = lil_to_string(result);
    if (strres[0 + strres_idx])
    {
      printf("%s\n", strres);
    }
    lil_free_value(result);
    if (lil_error(lil, &err_msg, &pos))
    {
      printf("error at %i: %s\n", (int) pos, err_msg);
    }
  }

  lil_free(lil);
  return exit_code;
}


----------------------------
***/


