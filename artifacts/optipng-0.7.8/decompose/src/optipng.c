static int opng_strcasecmp(const char *str1, const char *str2)
{
  unsigned int str2_idx = 0;
  unsigned int str1_idx = 0;
  int ch1;
  int ch2;
  for (;;)
  {
    ch1 = tolower(*(&str1[str1_idx]));
    str1_idx += 1;
    ch2 = tolower(*(&str2[str2_idx]));
    str2_idx += 1;
    if (ch1 != ch2)
    {
      return ch1 - ch2;
    }
    if (ch1 == '\0')
    {
      return 0;
    }
  }

}


/*** DEPENDENCIES:
***/


static char *opng_strltrim(const char *str)
{
  unsigned int str_idx = 0;
  while (isspace(*(&str[str_idx])))
  {
    str_idx += 1;
  }

  return (char *) str;
}


/*** DEPENDENCIES:
***/


static char *opng_strtail(const char *str, size_t num)
{
  size_t len;
  len = strlen(str);
  if (len <= num)
  {
    return (char *) str;
  }
  return (((char *) str) + len) - num;
}


/*** DEPENDENCIES:
***/


static char *opng_strpbrk_digit(const char *str)
{
  unsigned int str_idx = 0;
  for (;;)
  {
    if (str[str_idx] == '\0')
    {
      return 0;
    }
    if (isdigit(*(&str[str_idx])))
    {
      return (char *) str;
    }
    str_idx += 1;
  }

}


/*** DEPENDENCIES:
***/


static int scan_option(const char *str, char opt_buf[], size_t opt_buf_size, const char **opt_arg_ptr)
{
  const char *ptr;
  unsigned int ptr_idx = 0;
  unsigned int opt_len;
  if ((str[0] != '-') || (str[1] == '\0'))
  {
    return 0;
  }
  opt_len = 0;
  ptr_idx = str + 1;
  while (ptr[ptr_idx] == '-')
  {
    ptr_idx += 1;
  }

  if (ptr[ptr_idx] == '\0')
  {
    ptr_idx -= 1;
  }
  for (;;)
  {
    if (opt_len < opt_buf_size)
    {
      opt_buf[opt_len] = (char) tolower(*(&ptr[ptr_idx]));
    }
    opt_len += 1;
    ptr_idx += 1;
    if ((ptr[ptr_idx] == '\0') || isspace(*(&ptr[ptr_idx])))
    {
      while (isspace(*(&ptr[ptr_idx])))
      {
        ptr_idx += 1;
      }

      *opt_arg_ptr = (ptr[ptr_idx] != '\0') ? (ptr) : (0);
      break;
    }
    if (ptr[ptr_idx] == '=')
    {
      ptr_idx += 1;
      *opt_arg_ptr = &ptr[ptr_idx];
      break;
    }
  }

  if (opt_buf_size > 0)
  {
    if (opt_len < opt_buf_size)
    {
      opt_buf[opt_len] = '\0';
    }
    else
      opt_buf[opt_buf_size - 1] = '\0';
  }
  return 1;
}


/*** DEPENDENCIES:
***/


static void panic(const char *msg)
{
  fprintf(stderr, "\n** INTERNAL ERROR: %s\n", msg);
  fprintf(stderr, "Please submit a defect report.\nhttp://optipng.sourceforge.net/\n\n");
  fflush(stderr);
  if (options.debug)
  {
    abort();
  }
  else
  {
    fprintf(stderr, "The execution of this program has been terminated abnormally.\n");
    exit(70);
  }
}


/*** DEPENDENCIES:
static struct opng_options options
----------------------------
***/


static int opng_str2ulong(unsigned long *out_val, const char *in_str, int allow_multiplier)
{
  const char *begin_ptr;
  unsigned int begin_ptr_idx = 0;
  char *end_ptr;
  unsigned int end_ptr_idx = 0;
  unsigned long multiplier;
  begin_ptr_idx = (end_ptr = &end_ptr[end_ptr_idx + end_ptr_idx]);
  if ((begin_ptr[begin_ptr_idx] >= '0') && (begin_ptr[begin_ptr_idx] <= '9'))
  {
    *out_val = strtoul(begin_ptr, &(&end_ptr[end_ptr_idx]), 10);
  }
  if ((&begin_ptr[begin_ptr_idx]) == (&end_ptr[end_ptr_idx]))
  {
    errno = EINVAL;
    *out_val = 0;
    return -1;
  }
  if (allow_multiplier)
  {
    if ((end_ptr[end_ptr_idx] == 'k') || (end_ptr[end_ptr_idx] == 'K'))
    {
      end_ptr_idx += 1;
      multiplier = 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'M')
    {
      end_ptr_idx += 1;
      multiplier = 1024UL * 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'G')
    {
      end_ptr_idx += 1;
      multiplier = (1024UL * 1024UL) * 1024UL;
    }
    else
      multiplier = 1;
    if (multiplier > 1)
    {
      if ((*out_val) > (18446744073709551615UL / multiplier))
      {
        errno = ERANGE;
        *out_val = 18446744073709551615UL;
      }
      else
        *out_val *= multiplier;
    }
  }
  if ((*opng_strltrim(end_ptr)) != '\0')
  {
    errno = EINVAL;
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
static char *opng_strltrim(const char *str)
{
  unsigned int str_idx = 0;
  while (isspace(*(&str[str_idx])))
  {
    str_idx += 1;
  }

  return (char *) str;
}


----------------------------
***/


static void app_progress(unsigned long current_step, unsigned long total_steps)
{
  if (con_file != 0)
  {
    fflush(con_file);
  }
  if (current_step && total_steps)
  {
    return;
  }
}


/*** DEPENDENCIES:
static FILE *con_file
----------------------------
***/


static void app_finish(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
}


/*** DEPENDENCIES:
static FILE *log_file
----------------------------
***/


static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


/*** DEPENDENCIES:
static char *opng_strltrim(const char *str)
{
  unsigned int str_idx = 0;
  while (isspace(*(&str[str_idx])))
  {
    str_idx += 1;
  }

  return (char *) str;
}


----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
***/


static int check_num_option(const char *opt, const char *opt_arg, int lowest, int highest)
{
  unsigned long value;
  if ((((opng_str2ulong(&value, opt_arg, 0) != 0) || (value > 2147483647)) || (((int) value) < lowest)) || (((int) value) > highest))
  {
    err_option_arg(opt, opt_arg);
  }
  return (int) value;
}


/*** DEPENDENCIES:
static int opng_str2ulong(unsigned long *out_val, const char *in_str, int allow_multiplier)
{
  const char *begin_ptr;
  unsigned int begin_ptr_idx = 0;
  char *end_ptr;
  unsigned int end_ptr_idx = 0;
  unsigned long multiplier;
  begin_ptr_idx = (end_ptr = &end_ptr[end_ptr_idx + end_ptr_idx]);
  if ((begin_ptr[begin_ptr_idx] >= '0') && (begin_ptr[begin_ptr_idx] <= '9'))
  {
    *out_val = strtoul(begin_ptr, &(&end_ptr[end_ptr_idx]), 10);
  }
  if ((&begin_ptr[begin_ptr_idx]) == (&end_ptr[end_ptr_idx]))
  {
    errno = EINVAL;
    *out_val = 0;
    return -1;
  }
  if (allow_multiplier)
  {
    if ((end_ptr[end_ptr_idx] == 'k') || (end_ptr[end_ptr_idx] == 'K'))
    {
      end_ptr_idx += 1;
      multiplier = 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'M')
    {
      end_ptr_idx += 1;
      multiplier = 1024UL * 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'G')
    {
      end_ptr_idx += 1;
      multiplier = (1024UL * 1024UL) * 1024UL;
    }
    else
      multiplier = 1;
    if (multiplier > 1)
    {
      if ((*out_val) > (18446744073709551615UL / multiplier))
      {
        errno = ERANGE;
        *out_val = 18446744073709551615UL;
      }
      else
        *out_val *= multiplier;
    }
  }
  if ((*opng_strltrim(end_ptr)) != '\0')
  {
    errno = EINVAL;
    return -1;
  }
  return 0;
}


----------------------------
static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


----------------------------
***/


static int check_power2_option(const char *opt, const char *opt_arg, int lowest, int highest)
{
  unsigned long value;
  int result;
  if (opng_str2ulong(&value, opt_arg, 1) == 0)
  {
    if (lowest < 0)
    {
      lowest = 0;
    }
    if (highest > ((int) ((8 * (sizeof(long))) - 2)))
    {
      highest = (int) ((8 * (sizeof(long))) - 2);
    }
    for (result = lowest; result <= highest; result += 1)
    {
      if ((1UL << result) == value)
      {
        return result;
      }
    }

  }
  err_option_arg(opt, opt_arg);
  return -1;
}


/*** DEPENDENCIES:
static int opng_str2ulong(unsigned long *out_val, const char *in_str, int allow_multiplier)
{
  const char *begin_ptr;
  unsigned int begin_ptr_idx = 0;
  char *end_ptr;
  unsigned int end_ptr_idx = 0;
  unsigned long multiplier;
  begin_ptr_idx = (end_ptr = &end_ptr[end_ptr_idx + end_ptr_idx]);
  if ((begin_ptr[begin_ptr_idx] >= '0') && (begin_ptr[begin_ptr_idx] <= '9'))
  {
    *out_val = strtoul(begin_ptr, &(&end_ptr[end_ptr_idx]), 10);
  }
  if ((&begin_ptr[begin_ptr_idx]) == (&end_ptr[end_ptr_idx]))
  {
    errno = EINVAL;
    *out_val = 0;
    return -1;
  }
  if (allow_multiplier)
  {
    if ((end_ptr[end_ptr_idx] == 'k') || (end_ptr[end_ptr_idx] == 'K'))
    {
      end_ptr_idx += 1;
      multiplier = 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'M')
    {
      end_ptr_idx += 1;
      multiplier = 1024UL * 1024UL;
    }
    else
      if (end_ptr[end_ptr_idx] == 'G')
    {
      end_ptr_idx += 1;
      multiplier = (1024UL * 1024UL) * 1024UL;
    }
    else
      multiplier = 1;
    if (multiplier > 1)
    {
      if ((*out_val) > (18446744073709551615UL / multiplier))
      {
        errno = ERANGE;
        *out_val = 18446744073709551615UL;
      }
      else
        *out_val *= multiplier;
    }
  }
  if ((*opng_strltrim(end_ptr)) != '\0')
  {
    errno = EINVAL;
    return -1;
  }
  return 0;
}


----------------------------
static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


----------------------------
***/


static void check_obj_option(const char *opt, const char *opt_arg)
{
  unsigned int i;
  if (strcmp("all", opt_arg) == 0)
  {
    return;
  }
  for (i = 0; i < 4; i += 1)
  {
    if (!(((opt_arg[i] >= 'A') && (opt_arg[i] <= 'Z')) || ((opt_arg[i] >= 'a') && (opt_arg[i] <= 'z'))))
    {
      break;
    }
  }

  if ((i == 4) && (opt_arg[i] == '\0'))
  {
    error("Manipulation of individual chunks is not implemented");
  }
  else
    err_option_arg(opt, opt_arg);
}


/*** DEPENDENCIES:
static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
***/


static opng_bitset_t check_rangeset_option(const char *opt, const char *opt_arg, opng_bitset_t result_mask)
{
  opng_bitset_t result;
  if (opng_strparse_rangeset_to_bitset(&result, opt_arg, result_mask) != 0)
  {
    result = 0U;
  }
  if ((result & result_mask) != result)
  {
    result = 0U;
  }
  if (result == 0U)
  {
    err_option_arg(opt, opt_arg);
  }
  return result;
}


/*** DEPENDENCIES:
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set)
{
  opng_bitset_t result;
  const char *ptr;
  unsigned int ptr_idx = 0;
  int state;
  int num;
  int num1;
  int num2;
  int err_invalid;
  int err_range;
  result = 0U;
  ptr_idx = rangeset_str;
  state = 0;
  err_invalid = (err_range = 0);
  num1 = (num2 = -1);
  for (;;)
  {
    helper_opng_strparse_rangeset_to_bitset_1(&result, &ptr_idx, &state, &num, &num1, &num2, &err_invalid, &err_range, mask_set, ptr);
  }

  {
    while (isspace(*(&ptr[ptr_idx])))
    {
      ptr_idx += 1;
    }

  }
  ;
  if (ptr[ptr_idx] != '\0')
  {
    err_invalid = 1;
  }
  if (err_invalid)
  {
    *out_set = 0U;
    return -1;
  }
  else
    if (err_range)
  {
    *out_set = ~0U;
    return -1;
  }
  else
  {
    *out_set = result;
    return 0;
  }
}


----------------------------
static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


----------------------------
typedef unsigned int opng_bitset_t
----------------------------
***/


static void app_printf(const char *fmt, ...)
{
  va_list arg_ptr;
  if (fmt[0] == '\0')
  {
    return;
  }
  start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? (1) : (0);
  if (con_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(con_file, fmt, arg_ptr);
    ;
  }
  if (log_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(log_file, fmt, arg_ptr);
    ;
  }
}


/*** DEPENDENCIES:
static int start_of_line
----------------------------
static FILE *con_file
----------------------------
static FILE *log_file
----------------------------
***/


static void app_print_cntrl(int cntrl_code)
{
  const char *con_str;
  unsigned int con_str_idx = 0;
  const char *log_str;
  unsigned int log_str_idx = 0;
  int i;
  if (cntrl_code == '\r')
  {
    con_str_idx = "\r";
    log_str_idx = "\n";
    start_of_line = 1;
  }
  else
    if (cntrl_code == '\v')
  {
    if (!start_of_line)
    {
      con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
      start_of_line = 1;
    }
    else
      con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
  }
  else
    if (((cntrl_code < 0) && (cntrl_code > (-80))) && start_of_line)
  {
    if (con_file != 0)
    {
      for (i = 0; i > cntrl_code; i -= 1)
      {
        fputc(' ', con_file);
      }

    }
    con_str_idx = "\r";
    log_str_idx = "";
  }
  else
  {
    con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
  }
  if (con_file != 0)
  {
    fputs(con_str, con_file);
  }
  if (log_file != 0)
  {
    fputs(log_str, log_file);
  }
}


/*** DEPENDENCIES:
static int start_of_line
----------------------------
static FILE *con_file
----------------------------
static FILE *log_file
----------------------------
***/


static void app_init(void)
{
  start_of_line = 1;
  if ((operation == OP_SHOW_HELP) || (operation == OP_SHOW_VERSION))
  {
    con_file = stdout;
  }
  else
    if (!options.quiet)
  {
    con_file = stderr;
  }
  else
    con_file = 0;
  if (options.log_name != 0)
  {
    if ((log_file = fopen(options.log_name, "a")) == 0)
    {
      error("Can't open log file: %s\n", options.log_name);
    }
    setvbuf(log_file, 0, _IOLBF, 1024);
    app_printf("** Warning: %s\n\n", "The option -log is deprecated; use shell redirection");
  }
}


/*** DEPENDENCIES:
static enum 
{
  OP_RUN,
  OP_SHOW_HELP,
  OP_SHOW_VERSION
} operation
----------------------------
static FILE *con_file
----------------------------
static FILE *log_file
----------------------------
static int start_of_line
----------------------------
static struct opng_options options
----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
static void app_printf(const char *fmt, ...)
{
  va_list arg_ptr;
  if (fmt[0] == '\0')
  {
    return;
  }
  start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? (1) : (0);
  if (con_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(con_file, fmt, arg_ptr);
    ;
  }
  if (log_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(log_file, fmt, arg_ptr);
    ;
  }
}


----------------------------
***/


// hint:  ['arg_idx_ref is a mutable refrence to unsigned int', 'opt_len_ref is a mutable refrence to size_t', 'xopt_idx_ref is a mutable refrence to unsigned int', 'simple_opt_ref is a mutable refrence to int', 'stop_switch_ref is a mutable refrence to int', 'set_ref is a mutable refrence to opng_bitset_t', 'val_ref is a mutable refrence to int', 'file_count_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int']
void helper_parse_args_1(unsigned int * const arg_idx_ref, size_t * const opt_len_ref, unsigned int * const xopt_idx_ref, int * const simple_opt_ref, int * const stop_switch_ref, opng_bitset_t * const set_ref, int * const val_ref, unsigned int * const file_count_ref, int * const i_ref, int argc, char *argv[], char * const arg, char opt[16], const char * const xopt)
{
  unsigned int arg_idx = *arg_idx_ref;
  size_t opt_len = *opt_len_ref;
  unsigned int xopt_idx = *xopt_idx_ref;
  int simple_opt = *simple_opt_ref;
  int stop_switch = *stop_switch_ref;
  opng_bitset_t set = *set_ref;
  int val = *val_ref;
  unsigned int file_count = *file_count_ref;
  int i = *i_ref;
  arg_idx = argv[i];
  if (stop_switch || (scan_option(arg, opt, sizeof(opt), &(&xopt[xopt_idx])) < 1))
  {
    file_count += 1;
    continue;
  }
  opt_len = strlen(opt);
  argv[i] = 0;
  if (((strchr("fio", opt[0]) != 0) && isdigit(opt[1])) || (((opt[0] == 'z') && isalpha(opt[1])) && isdigit(opt[2])))
  {
    opt_len = (size_t) (opng_strpbrk_digit(opt) - opt);
    opt[opt_len] = '\0';
    xopt_idx = opng_strpbrk_digit(arg);
  }
  simple_opt = 1;
  if (strcmp("-", opt) == 0)
  {
    stop_switch = 1;
  }
  else
    if ((strcmp("?", opt) == 0) || (strncmp("help", opt, opt_len) == 0))
  {
    local_options.help = 1;
  }
  else
    if ((strncmp("backup", opt, opt_len) == 0) || (strncmp("keep", opt, opt_len) == 0))
  {
    options.backup = 1;
  }
  else
    if (strncmp("clobber", opt, opt_len) == 0)
  {
    options.clobber = 1;
  }
  else
    if (strcmp("debug", opt) == 0)
  {
    options.debug = 1;
  }
  else
    if ((strncmp("fix", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.fix = 1;
  }
  else
    if ((strncmp("force", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.force = 1;
  }
  else
    if ((strncmp("full", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.full = 1;
  }
  else
    if (strcmp("nb", opt) == 0)
  {
    options.nb = 1;
  }
  else
    if (strcmp("nc", opt) == 0)
  {
    options.nc = 1;
  }
  else
    if (strcmp("np", opt) == 0)
  {
    options.np = 1;
  }
  else
    if (strcmp("nx", opt) == 0)
  {
    options.nb = (options.nc = (options.np = 1));
  }
  else
    if (strcmp("nz", opt) == 0)
  {
    options.nz = 1;
  }
  else
    if (strncmp("preserve", opt, opt_len) == 0)
  {
    options.preserve = 1;
  }
  else
    if ((strncmp("quiet", opt, opt_len) == 0) || ((strncmp("silent", opt, opt_len) == 0) && (opt_len >= 3)))
  {
    options.quiet = 1;
  }
  else
    if ((strncmp("simulate", opt, opt_len) == 0) && (opt_len >= 3))
  {
    options.simulate = 1;
  }
  else
    if ((strncmp("snip", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.snip = 1;
  }
  else
    if (strcmp("v", opt) == 0)
  {
    options.verbose = 1;
    local_options.version = 1;
  }
  else
    if ((strncmp("verbose", opt, opt_len) == 0) && (opt_len >= 4))
  {
    options.verbose = 1;
  }
  else
    if ((strncmp("version", opt, opt_len) == 0) && (opt_len >= 4))
  {
    local_options.version = 1;
  }
  else
  {
    simple_opt = 0;
    if ((&xopt[xopt_idx]) == 0)
    {
      if ((++i) < argc)
      {
        xopt_idx = argv[i];
        argv[i] = 0;
      }
      else
      {
        xopt_idx = "";
      }
    }
  }
  if (simple_opt)
  {
    if ((&xopt[xopt_idx]) != 0)
    {
      error("No argument allowed for option: %s", arg);
    }
  }
  else
    if (strcmp("o", opt) == 0)
  {
    val = check_num_option("-o", xopt, 0, 2147483647);
    if (options.optim_level < 0)
    {
      options.optim_level = val;
    }
    else
      if (options.optim_level != val)
    {
      error("Multiple optimization levels are not permitted");
    }
  }
  else
    if (strcmp("i", opt) == 0)
  {
    val = check_num_option("-i", xopt, 0, 1);
    if (options.interlace < 0)
    {
      options.interlace = val;
    }
    else
      if (options.interlace != val)
    {
      error("Multiple interlace types are not permitted");
    }
  }
  else
    if (strcmp("f", opt) == 0)
  {
    set = check_rangeset_option("-f", xopt, (1 << (5 + 1)) - (1 << 0));
    options.filter_set |= set;
  }
  else
    if (strcmp("zc", opt) == 0)
  {
    set = check_rangeset_option("-zc", xopt, (1 << (9 + 1)) - (1 << 1));
    options.compr_level_set |= set;
  }
  else
    if (strcmp("zm", opt) == 0)
  {
    set = check_rangeset_option("-zm", xopt, (1 << (9 + 1)) - (1 << 1));
    options.mem_level_set |= set;
  }
  else
    if (strcmp("zs", opt) == 0)
  {
    set = check_rangeset_option("-zs", xopt, (1 << (3 + 1)) - (1 << 0));
    options.strategy_set |= set;
  }
  else
    if (strcmp("zw", opt) == 0)
  {
    val = check_power2_option("-zw", xopt, 8, 15);
    if (options.window_bits == 0)
    {
      options.window_bits = val;
    }
    else
      if (options.window_bits != val)
    {
      error("Multiple window sizes are not permitted");
    }
  }
  else
    if ((strncmp("strip", opt, opt_len) == 0) && (opt_len >= 2))
  {
    check_obj_option("-strip", xopt);
    options.strip_all = 1;
  }
  else
    if ((strncmp("out", opt, opt_len) == 0) && (opt_len >= 2))
  {
    if (options.out_name != 0)
    {
      error("Multiple output file names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-out", 0);
    }
    options.out_name = &xopt[xopt_idx];
  }
  else
    if (strncmp("dir", opt, opt_len) == 0)
  {
    if (options.dir_name != 0)
    {
      error("Multiple output dir names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-dir", 0);
    }
    options.dir_name = &xopt[xopt_idx];
  }
  else
    if (strncmp("log", opt, opt_len) == 0)
  {
    if (options.log_name != 0)
    {
      error("Multiple log file names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-log", 0);
    }
    options.log_name = &xopt[xopt_idx];
  }
  else
  {
    error("Unrecognized option: %s", arg);
  }
  *arg_idx_ref = arg_idx;
  *opt_len_ref = opt_len;
  *xopt_idx_ref = xopt_idx;
  *simple_opt_ref = simple_opt;
  *stop_switch_ref = stop_switch;
  *set_ref = set;
  *val_ref = val;
  *file_count_ref = file_count;
  *i_ref = i;
}


/*** DEPENDENCIES:
static opng_bitset_t check_rangeset_option(const char *opt, const char *opt_arg, opng_bitset_t result_mask)
{
  opng_bitset_t result;
  if (opng_strparse_rangeset_to_bitset(&result, opt_arg, result_mask) != 0)
  {
    result = 0U;
  }
  if ((result & result_mask) != result)
  {
    result = 0U;
  }
  if (result == 0U)
  {
    err_option_arg(opt, opt_arg);
  }
  return result;
}


----------------------------
static char *opng_strpbrk_digit(const char *str)
{
  unsigned int str_idx = 0;
  for (;;)
  {
    if (str[str_idx] == '\0')
    {
      return 0;
    }
    if (isdigit(*(&str[str_idx])))
    {
      return (char *) str;
    }
    str_idx += 1;
  }

}


----------------------------
static struct opng_options options
----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
static int check_num_option(const char *opt, const char *opt_arg, int lowest, int highest)
{
  unsigned long value;
  if ((((opng_str2ulong(&value, opt_arg, 0) != 0) || (value > 2147483647)) || (((int) value) < lowest)) || (((int) value) > highest))
  {
    err_option_arg(opt, opt_arg);
  }
  return (int) value;
}


----------------------------
static struct 
{
  int help;
  int version;
} local_options
----------------------------
static void check_obj_option(const char *opt, const char *opt_arg)
{
  unsigned int i;
  if (strcmp("all", opt_arg) == 0)
  {
    return;
  }
  for (i = 0; i < 4; i += 1)
  {
    if (!(((opt_arg[i] >= 'A') && (opt_arg[i] <= 'Z')) || ((opt_arg[i] >= 'a') && (opt_arg[i] <= 'z'))))
    {
      break;
    }
  }

  if ((i == 4) && (opt_arg[i] == '\0'))
  {
    error("Manipulation of individual chunks is not implemented");
  }
  else
    err_option_arg(opt, opt_arg);
}


----------------------------
typedef unsigned int opng_bitset_t
----------------------------
static int check_power2_option(const char *opt, const char *opt_arg, int lowest, int highest)
{
  unsigned long value;
  int result;
  if (opng_str2ulong(&value, opt_arg, 1) == 0)
  {
    if (lowest < 0)
    {
      lowest = 0;
    }
    if (highest > ((int) ((8 * (sizeof(long))) - 2)))
    {
      highest = (int) ((8 * (sizeof(long))) - 2);
    }
    for (result = lowest; result <= highest; result += 1)
    {
      if ((1UL << result) == value)
      {
        return result;
      }
    }

  }
  err_option_arg(opt, opt_arg);
  return -1;
}


----------------------------
static int scan_option(const char *str, char opt_buf[], size_t opt_buf_size, const char **opt_arg_ptr)
{
  const char *ptr;
  unsigned int ptr_idx = 0;
  unsigned int opt_len;
  if ((str[0] != '-') || (str[1] == '\0'))
  {
    return 0;
  }
  opt_len = 0;
  ptr_idx = str + 1;
  while (ptr[ptr_idx] == '-')
  {
    ptr_idx += 1;
  }

  if (ptr[ptr_idx] == '\0')
  {
    ptr_idx -= 1;
  }
  for (;;)
  {
    if (opt_len < opt_buf_size)
    {
      opt_buf[opt_len] = (char) tolower(*(&ptr[ptr_idx]));
    }
    opt_len += 1;
    ptr_idx += 1;
    if ((ptr[ptr_idx] == '\0') || isspace(*(&ptr[ptr_idx])))
    {
      while (isspace(*(&ptr[ptr_idx])))
      {
        ptr_idx += 1;
      }

      *opt_arg_ptr = (ptr[ptr_idx] != '\0') ? (ptr) : (0);
      break;
    }
    if (ptr[ptr_idx] == '=')
    {
      ptr_idx += 1;
      *opt_arg_ptr = &ptr[ptr_idx];
      break;
    }
  }

  if (opt_buf_size > 0)
  {
    if (opt_len < opt_buf_size)
    {
      opt_buf[opt_len] = '\0';
    }
    else
      opt_buf[opt_buf_size - 1] = '\0';
  }
  return 1;
}


----------------------------
static void err_option_arg(const char *opt, const char *opt_arg)
{
  if ((opt_arg == 0) || ((*opng_strltrim(opt_arg)) == '\0'))
  {
    error("Missing argument for option %s", opt);
  }
  else
    error("Invalid argument for option %s: %s", opt, opt_arg);
}


----------------------------
***/


static void parse_args(int argc, char *argv[])
{
  char *arg;
  unsigned int arg_idx = 0;
  char opt[16];
  size_t opt_len;
  const char *xopt;
  unsigned int xopt_idx = 0;
  int simple_opt;
  int stop_switch;
  opng_bitset_t set;
  int val;
  unsigned int file_count;
  int i;
  memset(&options, 0, sizeof(options));
  options.optim_level = -1;
  options.interlace = -1;
  file_count = 0;
  stop_switch = 0;
  for (i = 1; i < argc; i += 1)
  {
    helper_parse_args_1(&arg_idx, &opt_len, &xopt_idx, &simple_opt, &stop_switch, &set, &val, &file_count, &i, argc, argv, arg, opt, xopt);
  }

  if (options.out_name != 0)
  {
    if (file_count > 1)
    {
      error("The option -out requires one input file");
    }
    if (options.dir_name != 0)
    {
      error("The options -out and -dir are mutually exclusive");
    }
  }
  if (options.log_name != 0)
  {
    if (opng_strcasecmp(".log", opng_strtail(options.log_name, 4)) != 0)
    {
      error("To prevent accidental data corruption, the log file name must end with \".log\"");
    }
  }
  if (local_options.help)
  {
    operation = OP_SHOW_HELP;
  }
  else
    if (file_count != 0)
  {
    operation = OP_RUN;
  }
  else
    if (local_options.version)
  {
    operation = OP_SHOW_VERSION;
  }
  else
    operation = OP_SHOW_HELP;
}


/*** DEPENDENCIES:
static enum 
{
  OP_RUN,
  OP_SHOW_HELP,
  OP_SHOW_VERSION
} operation
----------------------------
static struct opng_options options
----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
void helper_parse_args_1(unsigned int * const arg_idx_ref, size_t * const opt_len_ref, unsigned int * const xopt_idx_ref, int * const simple_opt_ref, int * const stop_switch_ref, opng_bitset_t * const set_ref, int * const val_ref, unsigned int * const file_count_ref, int * const i_ref, int argc, char *argv[], char * const arg, char opt[16], const char * const xopt)
{
  unsigned int arg_idx = *arg_idx_ref;
  size_t opt_len = *opt_len_ref;
  unsigned int xopt_idx = *xopt_idx_ref;
  int simple_opt = *simple_opt_ref;
  int stop_switch = *stop_switch_ref;
  opng_bitset_t set = *set_ref;
  int val = *val_ref;
  unsigned int file_count = *file_count_ref;
  int i = *i_ref;
  arg_idx = argv[i];
  if (stop_switch || (scan_option(arg, opt, sizeof(opt), &(&xopt[xopt_idx])) < 1))
  {
    file_count += 1;
    continue;
  }
  opt_len = strlen(opt);
  argv[i] = 0;
  if (((strchr("fio", opt[0]) != 0) && isdigit(opt[1])) || (((opt[0] == 'z') && isalpha(opt[1])) && isdigit(opt[2])))
  {
    opt_len = (size_t) (opng_strpbrk_digit(opt) - opt);
    opt[opt_len] = '\0';
    xopt_idx = opng_strpbrk_digit(arg);
  }
  simple_opt = 1;
  if (strcmp("-", opt) == 0)
  {
    stop_switch = 1;
  }
  else
    if ((strcmp("?", opt) == 0) || (strncmp("help", opt, opt_len) == 0))
  {
    local_options.help = 1;
  }
  else
    if ((strncmp("backup", opt, opt_len) == 0) || (strncmp("keep", opt, opt_len) == 0))
  {
    options.backup = 1;
  }
  else
    if (strncmp("clobber", opt, opt_len) == 0)
  {
    options.clobber = 1;
  }
  else
    if (strcmp("debug", opt) == 0)
  {
    options.debug = 1;
  }
  else
    if ((strncmp("fix", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.fix = 1;
  }
  else
    if ((strncmp("force", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.force = 1;
  }
  else
    if ((strncmp("full", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.full = 1;
  }
  else
    if (strcmp("nb", opt) == 0)
  {
    options.nb = 1;
  }
  else
    if (strcmp("nc", opt) == 0)
  {
    options.nc = 1;
  }
  else
    if (strcmp("np", opt) == 0)
  {
    options.np = 1;
  }
  else
    if (strcmp("nx", opt) == 0)
  {
    options.nb = (options.nc = (options.np = 1));
  }
  else
    if (strcmp("nz", opt) == 0)
  {
    options.nz = 1;
  }
  else
    if (strncmp("preserve", opt, opt_len) == 0)
  {
    options.preserve = 1;
  }
  else
    if ((strncmp("quiet", opt, opt_len) == 0) || ((strncmp("silent", opt, opt_len) == 0) && (opt_len >= 3)))
  {
    options.quiet = 1;
  }
  else
    if ((strncmp("simulate", opt, opt_len) == 0) && (opt_len >= 3))
  {
    options.simulate = 1;
  }
  else
    if ((strncmp("snip", opt, opt_len) == 0) && (opt_len >= 2))
  {
    options.snip = 1;
  }
  else
    if (strcmp("v", opt) == 0)
  {
    options.verbose = 1;
    local_options.version = 1;
  }
  else
    if ((strncmp("verbose", opt, opt_len) == 0) && (opt_len >= 4))
  {
    options.verbose = 1;
  }
  else
    if ((strncmp("version", opt, opt_len) == 0) && (opt_len >= 4))
  {
    local_options.version = 1;
  }
  else
  {
    simple_opt = 0;
    if ((&xopt[xopt_idx]) == 0)
    {
      if ((++i) < argc)
      {
        xopt_idx = argv[i];
        argv[i] = 0;
      }
      else
      {
        xopt_idx = "";
      }
    }
  }
  if (simple_opt)
  {
    if ((&xopt[xopt_idx]) != 0)
    {
      error("No argument allowed for option: %s", arg);
    }
  }
  else
    if (strcmp("o", opt) == 0)
  {
    val = check_num_option("-o", xopt, 0, 2147483647);
    if (options.optim_level < 0)
    {
      options.optim_level = val;
    }
    else
      if (options.optim_level != val)
    {
      error("Multiple optimization levels are not permitted");
    }
  }
  else
    if (strcmp("i", opt) == 0)
  {
    val = check_num_option("-i", xopt, 0, 1);
    if (options.interlace < 0)
    {
      options.interlace = val;
    }
    else
      if (options.interlace != val)
    {
      error("Multiple interlace types are not permitted");
    }
  }
  else
    if (strcmp("f", opt) == 0)
  {
    set = check_rangeset_option("-f", xopt, (1 << (5 + 1)) - (1 << 0));
    options.filter_set |= set;
  }
  else
    if (strcmp("zc", opt) == 0)
  {
    set = check_rangeset_option("-zc", xopt, (1 << (9 + 1)) - (1 << 1));
    options.compr_level_set |= set;
  }
  else
    if (strcmp("zm", opt) == 0)
  {
    set = check_rangeset_option("-zm", xopt, (1 << (9 + 1)) - (1 << 1));
    options.mem_level_set |= set;
  }
  else
    if (strcmp("zs", opt) == 0)
  {
    set = check_rangeset_option("-zs", xopt, (1 << (3 + 1)) - (1 << 0));
    options.strategy_set |= set;
  }
  else
    if (strcmp("zw", opt) == 0)
  {
    val = check_power2_option("-zw", xopt, 8, 15);
    if (options.window_bits == 0)
    {
      options.window_bits = val;
    }
    else
      if (options.window_bits != val)
    {
      error("Multiple window sizes are not permitted");
    }
  }
  else
    if ((strncmp("strip", opt, opt_len) == 0) && (opt_len >= 2))
  {
    check_obj_option("-strip", xopt);
    options.strip_all = 1;
  }
  else
    if ((strncmp("out", opt, opt_len) == 0) && (opt_len >= 2))
  {
    if (options.out_name != 0)
    {
      error("Multiple output file names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-out", 0);
    }
    options.out_name = &xopt[xopt_idx];
  }
  else
    if (strncmp("dir", opt, opt_len) == 0)
  {
    if (options.dir_name != 0)
    {
      error("Multiple output dir names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-dir", 0);
    }
    options.dir_name = &xopt[xopt_idx];
  }
  else
    if (strncmp("log", opt, opt_len) == 0)
  {
    if (options.log_name != 0)
    {
      error("Multiple log file names are not permitted");
    }
    if (xopt[0 + xopt_idx] == '\0')
    {
      err_option_arg("-log", 0);
    }
    options.log_name = &xopt[xopt_idx];
  }
  else
  {
    error("Unrecognized option: %s", arg);
  }
  *arg_idx_ref = arg_idx;
  *opt_len_ref = opt_len;
  *xopt_idx_ref = xopt_idx;
  *simple_opt_ref = simple_opt;
  *stop_switch_ref = stop_switch;
  *set_ref = set;
  *val_ref = val;
  *file_count_ref = file_count;
  *i_ref = i;
}


----------------------------
static char *opng_strtail(const char *str, size_t num)
{
  size_t len;
  len = strlen(str);
  if (len <= num)
  {
    return (char *) str;
  }
  return (((char *) str) + len) - num;
}


----------------------------
static struct 
{
  int help;
  int version;
} local_options
----------------------------
typedef unsigned int opng_bitset_t
----------------------------
static int opng_strcasecmp(const char *str1, const char *str2)
{
  unsigned int str2_idx = 0;
  unsigned int str1_idx = 0;
  int ch1;
  int ch2;
  for (;;)
  {
    ch1 = tolower(*(&str1[str1_idx]));
    str1_idx += 1;
    ch2 = tolower(*(&str2[str2_idx]));
    str2_idx += 1;
    if (ch1 != ch2)
    {
      return ch1 - ch2;
    }
    if (ch1 == '\0')
    {
      return 0;
    }
  }

}


----------------------------
***/


static int process_files(int argc, char *argv[])
{
  int result;
  struct opng_ui ui;
  int i;
  ui.printf_fn = app_printf;
  ui.print_cntrl_fn = app_print_cntrl;
  ui.progress_fn = app_progress;
  ui.panic_fn = panic;
  if (opng_initialize(&options, &ui) != 0)
  {
    panic("Can't initialize optimization engine");
  }
  result = 0;
  for (i = 1; i < argc; i += 1)
  {
    if ((argv[i] == 0) || (argv[i][0] == '\0'))
    {
      continue;
    }
    if (opng_optimize(argv[i]) != 0)
    {
      result = 1;
    }
  }

  if (opng_finalize() != 0)
  {
    panic("Can't finalize optimization engine");
  }
  return result;
}


/*** DEPENDENCIES:
int opng_initialize(const struct opng_options *init_options, const struct opng_ui *init_ui)
{
  usr_printf = init_ui->printf_fn;
  usr_print_cntrl = init_ui->print_cntrl_fn;
  usr_progress = init_ui->progress_fn;
  usr_panic = init_ui->panic_fn;
  if ((((usr_printf == 0) || (usr_print_cntrl == 0)) || (usr_progress == 0)) || (usr_panic == 0))
  {
    return -1;
  }
  s_options = *init_options;
  if (s_options.optim_level == 0)
  {
    s_options.nb = (s_options.nc = (s_options.np = 1));
    s_options.nz = 1;
  }
  memset(&s_summary, 0, sizeof(s_summary));
  s_engine.started = 1;
  return 0;
}


----------------------------
static void app_progress(unsigned long current_step, unsigned long total_steps)
{
  if (con_file != 0)
  {
    fflush(con_file);
  }
  if (current_step && total_steps)
  {
    return;
  }
}


----------------------------
static void panic(const char *msg)
{
  fprintf(stderr, "\n** INTERNAL ERROR: %s\n", msg);
  fprintf(stderr, "Please submit a defect report.\nhttp://optipng.sourceforge.net/\n\n");
  fflush(stderr);
  if (options.debug)
  {
    abort();
  }
  else
  {
    fprintf(stderr, "The execution of this program has been terminated abnormally.\n");
    exit(70);
  }
}


----------------------------
struct opng_ui
{
  void (*printf_fn)(const char *fmt, ...);
  void (*print_cntrl_fn)(int cntrl_code);
  void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
  void (*panic_fn)(const char *msg);
}
----------------------------
int opng_optimize(const char *infile_name)
{
  opng_status_t status;
  volatile int result;
  {
    if (!s_engine.started)
    {
      usr_panic("The OptiPNG engine is not running");
    }
  }
  ;
  usr_printf("** Processing: %s\n", infile_name);
  s_summary.file_count += 1;
  opng_clear_image_info();
  {
    helper_opng_optimize_1(&result, infile_name);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_optimize_impl should throw errors only");
      }
    }
    ;
    s_summary.err_count += 1;
    result = -1;
  }
  opng_destroy_image_info();
  usr_printf("\n");
  return result;
}


----------------------------
static struct opng_options options
----------------------------
int opng_finalize(void)
{
  if ((s_options.verbose || (s_summary.snip_count > 0)) || (s_summary.err_count > 0))
  {
    usr_printf("** Status report\n");
    usr_printf("%u file(s) have been processed.\n", s_summary.file_count);
    if (s_summary.snip_count > 0)
    {
      usr_printf("%u multi-image file(s) have been snipped.\n", s_summary.snip_count);
    }
    if (s_summary.err_count > 0)
    {
      usr_printf("%u error(s) have been encountered.\n", s_summary.err_count);
      if (s_summary.fix_count > 0)
      {
        usr_printf("%u erroneous file(s) have been fixed.\n", s_summary.fix_count);
      }
    }
  }
  s_engine.started = 0;
  return 0;
}


----------------------------
static void app_printf(const char *fmt, ...)
{
  va_list arg_ptr;
  if (fmt[0] == '\0')
  {
    return;
  }
  start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? (1) : (0);
  if (con_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(con_file, fmt, arg_ptr);
    ;
  }
  if (log_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(log_file, fmt, arg_ptr);
    ;
  }
}


----------------------------
static void app_print_cntrl(int cntrl_code)
{
  const char *con_str;
  unsigned int con_str_idx = 0;
  const char *log_str;
  unsigned int log_str_idx = 0;
  int i;
  if (cntrl_code == '\r')
  {
    con_str_idx = "\r";
    log_str_idx = "\n";
    start_of_line = 1;
  }
  else
    if (cntrl_code == '\v')
  {
    if (!start_of_line)
    {
      con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
      start_of_line = 1;
    }
    else
      con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
  }
  else
    if (((cntrl_code < 0) && (cntrl_code > (-80))) && start_of_line)
  {
    if (con_file != 0)
    {
      for (i = 0; i > cntrl_code; i -= 1)
      {
        fputc(' ', con_file);
      }

    }
    con_str_idx = "\r";
    log_str_idx = "";
  }
  else
  {
    con_str_idx = (log_str = &log_str[log_str_idx + log_str_idx]);
  }
  if (con_file != 0)
  {
    fputs(con_str, con_file);
  }
  if (log_file != 0)
  {
    fputs(log_str, log_file);
  }
}


----------------------------
***/


int main(int argc, char *argv[])
{
  int result;
  parse_args(argc, argv);
  app_init();
  result = 0;
  if (local_options.version)
  {
    app_printf("%s\n", msg_intro);
  }
  switch (operation)
  {
    case OP_RUN:
      result = process_files(argc, argv);
      break;

    case OP_SHOW_HELP:
      if (local_options.help)
    {
      app_printf("%s%s%s", msg_help_synopsis, msg_help_options, msg_help_examples);
    }
    else
    {
      app_printf("%s%s%s%s", msg_help_synopsis, msg_help_basic_options, msg_help_examples, msg_help_more);
    }
      break;

    case OP_SHOW_VERSION:
      app_printf("%s\n", msg_license);
      app_printf("Using libpng version %s and zlib version %s\n", png_get_libpng_ver(0), zlibVersion());
      break;

    default:
      result = -1;

  }

  app_finish();
  return result;
}


/*** DEPENDENCIES:
static enum 
{
  OP_RUN,
  OP_SHOW_HELP,
  OP_SHOW_VERSION
} operation
----------------------------
static const char *msg_help_basic_options = "Basic options:\n    -?, -h, -help\tshow the extended help\n    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n    -v\t\t\trun in verbose mode / show copyright and version info\n"
----------------------------
static const char *msg_help_synopsis = "Synopsis:\n    optipng [options] files ...\nFiles:\n    Image files of type: PNG, BMP, GIF, PNM or TIFF\n"
----------------------------
static const char *msg_help_options = "Basic options:\n    -?, -h, -help\tshow this help\n    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n    -v\t\t\trun in verbose mode / show copyright and version info\nGeneral options:\n    -backup, -keep\tkeep a backup of the modified files\n    -clobber\t\toverwrite existing files\n    -fix\t\tenable error recovery\n    -force\t\tenforce writing of a new output file\n    -preserve\t\tpreserve file attributes if possible\n    -quiet, -silent\trun in quiet mode\n    -simulate\t\trun in simulation mode\n    -out <file>\t\twrite output file to <file>\n    -dir <directory>\twrite output file(s) to <directory>\n    -log <file>\t\tlog messages to <file>\n    --\t\t\tstop option switch parsing\nOptimization options:\n    -f <filters>\tPNG delta filters (0-5)\t\t\t[default: 0,5]\n    -i <type>\t\tPNG interlace type (0-1)\n    -zc <levels>\tzlib compression levels (1-9)\t\t[default: 9]\n    -zm <levels>\tzlib memory levels (1-9)\t\t[default: 8]\n    -zs <strategies>\tzlib compression strategies (0-3)\t[default: 0-3]\n    -zw <size>\t\tzlib window size (256,512,1k,2k,4k,8k,16k,32k)\n    -full\t\tproduce a full report on IDAT (might reduce speed)\n    -nb\t\t\tno bit depth reduction\n    -nc\t\t\tno color type reduction\n    -np\t\t\tno palette reduction\n    -nx\t\t\tno reductions\n    -nz\t\t\tno IDAT recoding\nEditing options:\n    -snip\t\tcut one image out of multi-image or animation files\n    -strip <objects>\tstrip metadata objects (e.g. \"all\")\nOptimization levels:\n    -o0\t\t<=>\t-o1 -nx -nz\t\t\t\t(0 or 1 trials)\n    -o1\t\t<=>\t-zc9 -zm8 -zs0 -f0\t\t\t(1 trial)\n    \t\t(or...)\t-zc9 -zm8 -zs1 -f5\t\t\t(1 trial)\n    -o2\t\t<=>\t-zc9 -zm8 -zs0-3 -f0,5\t\t\t(8 trials)\n    -o3\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0,5\t\t(16 trials)\n    -o4\t\t<=>\t-zc9 -zm8 -zs0-3 -f0-5\t\t\t(24 trials)\n    -o5\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0-5\t\t(48 trials)\n    -o6\t\t<=>\t-zc1-9 -zm8 -zs0-3 -f0-5\t\t(120 trials)\n    -o7\t\t<=>\t-zc1-9 -zm8-9 -zs0-3 -f0-5\t\t(240 trials)\n    -o7 -zm1-9\t<=>\t-zc1-9 -zm1-9 -zs0-3 -f0-5\t\t(1080 trials)\nNotes:\n    The combination for -o1 is chosen heuristically.\n    Exhaustive combinations such as \"-o7 -zm1-9\" are not generally recommended.\n"
----------------------------
static const char *msg_help_more = "Type \"optipng -h\" for extended help.\n"
----------------------------
static void parse_args(int argc, char *argv[])
{
  char *arg;
  unsigned int arg_idx = 0;
  char opt[16];
  size_t opt_len;
  const char *xopt;
  unsigned int xopt_idx = 0;
  int simple_opt;
  int stop_switch;
  opng_bitset_t set;
  int val;
  unsigned int file_count;
  int i;
  memset(&options, 0, sizeof(options));
  options.optim_level = -1;
  options.interlace = -1;
  file_count = 0;
  stop_switch = 0;
  for (i = 1; i < argc; i += 1)
  {
    helper_parse_args_1(&arg_idx, &opt_len, &xopt_idx, &simple_opt, &stop_switch, &set, &val, &file_count, &i, argc, argv, arg, opt, xopt);
  }

  if (options.out_name != 0)
  {
    if (file_count > 1)
    {
      error("The option -out requires one input file");
    }
    if (options.dir_name != 0)
    {
      error("The options -out and -dir are mutually exclusive");
    }
  }
  if (options.log_name != 0)
  {
    if (opng_strcasecmp(".log", opng_strtail(options.log_name, 4)) != 0)
    {
      error("To prevent accidental data corruption, the log file name must end with \".log\"");
    }
  }
  if (local_options.help)
  {
    operation = OP_SHOW_HELP;
  }
  else
    if (file_count != 0)
  {
    operation = OP_RUN;
  }
  else
    if (local_options.version)
  {
    operation = OP_SHOW_VERSION;
  }
  else
    operation = OP_SHOW_HELP;
}


----------------------------
static int process_files(int argc, char *argv[])
{
  int result;
  struct opng_ui ui;
  int i;
  ui.printf_fn = app_printf;
  ui.print_cntrl_fn = app_print_cntrl;
  ui.progress_fn = app_progress;
  ui.panic_fn = panic;
  if (opng_initialize(&options, &ui) != 0)
  {
    panic("Can't initialize optimization engine");
  }
  result = 0;
  for (i = 1; i < argc; i += 1)
  {
    if ((argv[i] == 0) || (argv[i][0] == '\0'))
    {
      continue;
    }
    if (opng_optimize(argv[i]) != 0)
    {
      result = 1;
    }
  }

  if (opng_finalize() != 0)
  {
    panic("Can't finalize optimization engine");
  }
  return result;
}


----------------------------
static struct 
{
  int help;
  int version;
} local_options
----------------------------
static const char *msg_license = "This program is open-source software. See LICENSE for more details.\n\nPortions of this software are based in part on the work of:\n  Jean-loup Gailly and Mark Adler (zlib)\n  Glenn Randers-Pehrson and the PNG Development Group (libpng)\n  Miyasaka Masaru (BMP support)\n  David Koblas (GIF support)\n"
----------------------------
static void app_printf(const char *fmt, ...)
{
  va_list arg_ptr;
  if (fmt[0] == '\0')
  {
    return;
  }
  start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? (1) : (0);
  if (con_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(con_file, fmt, arg_ptr);
    ;
  }
  if (log_file != 0)
  {
    __builtin_va_start(arg_ptr);
    vfprintf(log_file, fmt, arg_ptr);
    ;
  }
}


----------------------------
const char *zlibVersion(void)
{
  return "1.3-optipng";
}


----------------------------
static void app_init(void)
{
  start_of_line = 1;
  if ((operation == OP_SHOW_HELP) || (operation == OP_SHOW_VERSION))
  {
    con_file = stdout;
  }
  else
    if (!options.quiet)
  {
    con_file = stderr;
  }
  else
    con_file = 0;
  if (options.log_name != 0)
  {
    if ((log_file = fopen(options.log_name, "a")) == 0)
    {
      error("Can't open log file: %s\n", options.log_name);
    }
    setvbuf(log_file, 0, _IOLBF, 1024);
    app_printf("** Warning: %s\n\n", "The option -log is deprecated; use shell redirection");
  }
}


----------------------------
png_const_charp png_get_libpng_ver(png_const_structrp png_ptr)
{
  return png_get_header_ver(png_ptr);
}


----------------------------
static void app_finish(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
}


----------------------------
static const char *msg_intro = "OptiPNG version 0.7.8\nCopyright (C) 2001-2023 Cosmin Truta and the Contributing Authors.\n"
----------------------------
static const char *msg_help_examples = "Examples:\n    optipng file.png\t\t\t\t\t\t(default speed)\n    optipng -o5 file.png\t\t\t\t\t(slow)\n    optipng -o7 file.png\t\t\t\t\t(very slow)\n"
----------------------------
***/


