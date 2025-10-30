#include <inttypes.h>
#include <lil.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef int64_t lilint_t;
typedef struct _lil_value_t *lil_value_t;
typedef struct _lil_func_t *lil_func_t;
typedef struct _lil_var_t *lil_var_t;
typedef struct _lil_env_t *lil_env_t;
typedef struct _lil_list_t *lil_list_t;
typedef struct _lil_t *lil_t;
typedef lil_value_t (*lil_func_proc_t)(lil_t lil, size_t argc, lil_value_t *argv);
typedef void (*lil_exit_callback_proc_t)(lil_t lil, lil_value_t arg);
typedef void (*lil_write_callback_proc_t)(lil_t lil, const char *msg);
typedef char *(*lil_read_callback_proc_t)(lil_t lil, const char *name);
typedef char *(*lil_source_callback_proc_t)(lil_t lil, const char *name);
typedef void (*lil_store_callback_proc_t)(lil_t lil, const char *name, const char *data);
typedef void (*lil_error_callback_proc_t)(lil_t lil, size_t pos, const char *msg);
typedef int (*lil_setvar_callback_proc_t)(lil_t lil, const char *name, lil_value_t *value);
typedef int (*lil_getvar_callback_proc_t)(lil_t lil, const char *name, lil_value_t *value);
typedef void (*lil_callback_proc_t)(void);
lil_t lil_new(void);
void lil_free(lil_t lil);
int lil_register(lil_t lil, const char *name, lil_func_proc_t proc);
lil_value_t lil_parse(lil_t lil, const char *code, size_t codelen, int funclevel);
lil_value_t lil_parse_value(lil_t lil, lil_value_t val, int funclevel);
lil_value_t lil_call(lil_t lil, const char *funcname, size_t argc, lil_value_t *argv);
void lil_callback(lil_t lil, int cb, lil_callback_proc_t proc);
void lil_set_error(lil_t lil, const char *msg);
void lil_set_error_at(lil_t lil, size_t pos, const char *msg);
int lil_error(lil_t lil, const char **msg, size_t *pos);
const char *lil_to_string(lil_value_t val);
double lil_to_double(lil_value_t val);
lilint_t lil_to_integer(lil_value_t val);
int lil_to_boolean(lil_value_t val);
lil_value_t lil_alloc_string(const char *str);
lil_value_t lil_alloc_double(double num);
lil_value_t lil_alloc_integer(lilint_t num);
void lil_free_value(lil_value_t val);
lil_value_t lil_clone_value(lil_value_t src);
int lil_append_char(lil_value_t val, char ch);
int lil_append_string(lil_value_t val, const char *s);
int lil_append_val(lil_value_t val, lil_value_t v);
lil_list_t lil_alloc_list(void);
void lil_free_list(lil_list_t list);
void lil_list_append(lil_list_t list, lil_value_t val);
size_t lil_list_size(lil_list_t list);
lil_value_t lil_list_get(lil_list_t list, size_t index);
lil_value_t lil_list_to_value(lil_list_t list, int do_escape);
lil_list_t lil_subst_to_list(lil_t lil, lil_value_t code);
lil_value_t lil_subst_to_value(lil_t lil, lil_value_t code);
lil_env_t lil_alloc_env(lil_env_t parent);
void lil_free_env(lil_env_t env);
lil_env_t lil_push_env(lil_t lil);
void lil_pop_env(lil_t lil);
lil_var_t lil_set_var(lil_t lil, const char *name, lil_value_t val, int local);
lil_value_t lil_get_var(lil_t lil, const char *name);
lil_value_t lil_get_var_or(lil_t lil, const char *name, lil_value_t defvalue);
lil_value_t lil_eval_expr(lil_t lil, lil_value_t code);
lil_value_t lil_unused_name(lil_t lil, const char *part);
lil_value_t lil_arg(lil_value_t *argv, size_t index);
void lil_set_data(lil_t lil, void *data);
void *lil_get_data(lil_t lil);
char *lil_embedded(lil_t lil, const char *code, unsigned int flags);
void lil_freemem(void *ptr);
void lil_write(lil_t lil, const char *msg);
static int running = 1;
static int exit_code = 0;
static void do_exit(lil_t lil, lil_value_t val)
{
  running = 0;
  exit_code = (int) lil_to_integer(val);
}

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
    helper_do_system_1(p);
  }
  else
  {
    return 0;
  }
}

static lil_value_t fnc_writechar(lil_t lil, size_t argc, lil_value_t *argv)
{
  if (!argc)
  {
    return 0;
  }
  printf("%c", (char) lil_to_integer(argv[0]));
  return 0;
}

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
  {
    sargv[i] = lil_to_string(argv[i]);
  }

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

int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    return repl();
  }
  else
    return nonint(argc, argv);
}

char *helper_do_system_1(FILE * const p)
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

