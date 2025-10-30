static int ParseInt(const char *s, int low, int high, int *result)
{
  int value = 0;
  int i;
  for (i = 0; i < 5; i += 1)
  {
    char c = s[i];
    if (c == 0)
    {
      break;
    }
    if ((s[i] < '0') || (s[i] > '9'))
    {
      return 0;
    }
    value = (10 * value) + (c - '0');
  }

  if (i == 0)
  {
    return 0;
  }
  if ((i > 1) && (s[0] == '0'))
  {
    return 0;
  }
  if (s[i] != 0)
  {
    return 0;
  }
  if ((value < low) || (value > high))
  {
    return 0;
  }
  *result = value;
  return 1;
}


/*** DEPENDENCIES:
***/


static const char *FileName(const char *path)
{
  unsigned int path_idx = 0;
  const char *separator_position = strrchr(path, '/');
  unsigned int separator_position_idx = 0;
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  separator_position_idx = strrchr(path, '\\');
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  return path;
}


/*** DEPENDENCIES:
***/


static void PrintVersion(void)
{
  int major = 0x1000009 >> 24;
  int minor = (0x1000009 >> 12) & 0xFFF;
  int patch = 0x1000009 & 0xFFF;
  fprintf(stdout, "brotli %d.%d.%d\n", major, minor, patch);
}


/*** DEPENDENCIES:
***/


static void PrintHelp(const char *name, int error)
{
  FILE *media = (error) ? (stderr) : (stdout);
  fprintf(media, "Usage: %s [OPTION]... [FILE]...\n", name);
  fprintf(media, "Options:\n  -#                          compression level (0-9)\n  -c, --stdout                write on standard output\n  -d, --decompress            decompress\n  -f, --force                 force output file overwrite\n  -h, --help                  display this help and exit\n");
  fprintf(media, "  -j, --rm                    remove source file(s)\n  -k, --keep                  keep source file(s) (default)\n  -n, --no-copy-stat          do not copy source file(s) attributes\n  -o FILE, --output=FILE      output file (only if 1 input file)\n");
  fprintf(media, "  -q NUM, --quality=NUM       compression level (%d-%d)\n", 0, 11);
  fprintf(media, "  -t, --test                  test compressed file integrity\n  -v, --verbose               verbose mode\n");
  fprintf(media, "  -w NUM, --lgwin=NUM         set LZ77 window size (0, %d-%d)\n                              window size = 2**NUM - 16\n                              0 lets compressor choose the optimal value\n", 10, 24);
  fprintf(media, "  --large_window=NUM          use incompatible large-window brotli\n                              bitstream with window size (0, %d-%d)\n                              WARNING: this format is not compatible\n                              with brotli RFC 7932 and may not be\n                              decodable with regular brotli decoders\n", 10, 30);
  fprintf(media, "  -S SUF, --suffix=SUF        output file suffix (default:'%s')\n", ".br");
  fprintf(media, "  -V, --version               display version and exit\n  -Z, --best                  use best compression level (11) (default)\nSimple options could be coalesced, i.e. '-9kf' is equivalent to '-9 -k -f'.\nWith no FILE, or when FILE is -, read standard input.\nAll arguments after '--' are treated as files.\n");
}


/*** DEPENDENCIES:
***/


static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


/*** DEPENDENCIES:
***/


static int64_t FileSize(const char *path)
{
  FILE *f = fopen(path, "rb");
  int64_t retval;
  if (f == 0)
  {
    return -1;
  }
  if (fseek(f, 0L, 2) != 0)
  {
    fclose(f);
    return -1;
  }
  retval = ftell(f);
  if (fclose(f) != 0)
  {
    return -1;
  }
  return retval;
}


/*** DEPENDENCIES:
***/


static void PrintBytes(size_t value)
{
  if (value < 1024)
  {
    fprintf(stderr, "%d B", (int) value);
  }
  else
    if (value < 1048576)
  {
    fprintf(stderr, "%0.3f KiB", ((double) value) / 1024.0);
  }
  else
    if (value < 1073741824)
  {
    fprintf(stderr, "%0.3f MiB", ((double) value) / 1048576.0);
  }
  else
  {
    fprintf(stderr, "%0.3f GiB", ((double) value) / 1073741824.0);
  }
}


/*** DEPENDENCIES:
***/


static Command ParseAlias(const char *name)
{
  unsigned int name_idx = 0;
  const char *unbrotli = "unbrotli";
  size_t unbrotli_len = strlen(unbrotli);
  name_idx = FileName(name_idx);
  if (strncmp(name, unbrotli, unbrotli_len) == 0)
  {
    char terminator = name[unbrotli_len + name_idx];
    if ((terminator == 0) || (terminator == '.'))
    {
      return COMMAND_DECOMPRESS;
    }
  }
  return COMMAND_COMPRESS;
}


/*** DEPENDENCIES:
static const char *FileName(const char *path)
{
  unsigned int path_idx = 0;
  const char *separator_position = strrchr(path, '/');
  unsigned int separator_position_idx = 0;
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  separator_position_idx = strrchr(path, '\\');
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  return path;
}


----------------------------
***/


static int OpenInputFile(const char *input_path, FILE **f)
{
  *f = 0;
  if (!input_path)
  {
    *f = fdopen(STDIN_FILENO, "rb");
    return 1;
  }
  *f = fopen(input_path, "rb");
  if (!(*f))
  {
    fprintf(stderr, "failed to open input file [%s]: %s\n", PrintablePath(input_path), strerror(errno));
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int OpenOutputFile(const char *output_path, FILE **f, int force)
{
  int fd;
  *f = 0;
  if (!output_path)
  {
    *f = fdopen(STDOUT_FILENO, "wb");
    return 1;
  }
  fd = open(output_path, ((O_CREAT | ((force) ? (0) : (O_EXCL))) | O_WRONLY) | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd < 0)
  {
    fprintf(stderr, "failed to open output file [%s]: %s\n", PrintablePath(output_path), strerror(errno));
    return 0;
  }
  *f = fdopen(fd, "wb");
  if (!(*f))
  {
    fprintf(stderr, "failed to open output file [%s]: %s\n", PrintablePath(output_path), strerror(errno));
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static void CopyStat(const char *input_path, const char *output_path)
{
  struct stat statbuf;
  struct utimbuf times;
  int res;
  if ((input_path == 0) || (output_path == 0))
  {
    return;
  }
  if (stat(input_path, &statbuf) != 0)
  {
    return;
  }
  times.actime = statbuf.st_atime;
  times.modtime = statbuf.st_mtime;
  utime(output_path, &times);
  res = chmod(output_path, statbuf.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO));
  if (res != 0)
  {
    fprintf(stderr, "setting access bits failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
  res = chown(output_path, (uid_t) (-1), statbuf.st_gid);
  if (res != 0)
  {
    fprintf(stderr, "setting group failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
  res = chown(output_path, statbuf.st_uid, (gid_t) (-1));
  if (res != 0)
  {
    fprintf(stderr, "setting user failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
}


/*** DEPENDENCIES:
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int HasMoreInput(Context *context)
{
  return (feof(context->fin)) ? (0) : (1);
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
***/


static void InitializeBuffers(Context *context)
{
  context->available_in = 0;
  context->next_in = 0;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}


/*** DEPENDENCIES:
static const size_t kFileBufferSize = 1 << 19
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
***/


static int WriteOutput(Context *context)
{
  size_t out_size = (size_t) (context->next_out - context->output);
  context->total_out += out_size;
  if (out_size == 0)
  {
    return 1;
  }
  if (context->test_integrity)
  {
    return 1;
  }
  fwrite(context->output, 1, out_size, context->fout);
  if (ferror(context->fout))
  {
    fprintf(stderr, "failed to write output [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int FlushOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = 0;
  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int WriteOutput(Context *context)
{
  size_t out_size = (size_t) (context->next_out - context->output);
  context->total_out += out_size;
  if (out_size == 0)
  {
    return 1;
  }
  if (context->test_integrity)
  {
    return 1;
  }
  fwrite(context->output, 1, out_size, context->fout);
  if (ferror(context->fout))
  {
    fprintf(stderr, "failed to write output [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
***/


// hint:  ['quality_set_ref is a mutable refrence to int', 'lgwin_set_ref is a mutable refrence to int', 'suffix_set_ref is a mutable refrence to int']
Command helper_helper_helper_ParseParams_1_1_1(int * const quality_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Context * const params, const char * const arg, int output_set, unsigned int arg_idx)
{
  int quality_set = *quality_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  const char *value = strrchr(arg, '=');
  size_t key_len;
  if ((!value) || (value[1] == 0))
  {
    fprintf(stderr, "must pass the parameter as --%s=value\n", arg);
    return COMMAND_INVALID;
  }
  key_len = (size_t) (value - (&arg[arg_idx]));
  value++;
  if (strncmp("lgwin", arg, key_len) == 0)
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(value, 0, 24, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", value);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("large_window", arg, key_len) == 0)
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(value, 0, 30, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", value);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("output", arg, key_len) == 0)
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set (--output)\n");
      return COMMAND_INVALID;
    }
    params->output_path = value;
  }
  else
    if (strncmp("quality", arg, key_len) == 0)
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = ParseInt(value, 0, 11, &params->quality);
    if (!quality_set)
    {
      fprintf(stderr, "error parsing quality value [%s]\n", value);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("suffix", arg, key_len) == 0)
  {
    if (suffix_set)
    {
      fprintf(stderr, "suffix already set\n");
      return COMMAND_INVALID;
    }
    suffix_set = 1;
    params->suffix = value;
  }
  else
  {
    fprintf(stderr, "invalid parameter: [%s]\n", arg);
    return COMMAND_INVALID;
  }
  *quality_set_ref = quality_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int ParseInt(const char *s, int low, int high, int *result)
{
  int value = 0;
  int i;
  for (i = 0; i < 5; i += 1)
  {
    char c = s[i];
    if (c == 0)
    {
      break;
    }
    if ((s[i] < '0') || (s[i] > '9'))
    {
      return 0;
    }
    value = (10 * value) + (c - '0');
  }

  if (i == 0)
  {
    return 0;
  }
  if ((i > 1) && (s[0] == '0'))
  {
    return 0;
  }
  if (s[i] != 0)
  {
    return 0;
  }
  if ((value < low) || (value > high))
  {
    return 0;
  }
  *result = value;
  return 1;
}


----------------------------
***/


int helper_NextFile_1(Context * const context, const char * const arg)
{
  size_t suffix_len = strlen(context->suffix);
  char *name = (char *) FileName(context->modified_path);
  char *name_suffix;
  unsigned int name_suffix_idx = 0;
  size_t name_len = strlen(name);
  if (name_len < (suffix_len + 1))
  {
    fprintf(stderr, "empty output file name for [%s] input file\n", PrintablePath(arg));
    context->iterator_error = 1;
    return 0;
  }
  name_suffix_idx = (name + name_len) - suffix_len;
  if (strcmp(context->suffix, name_suffix) != 0)
  {
    fprintf(stderr, "input file [%s] suffix mismatch\n", PrintablePath(arg));
    context->iterator_error = 1;
    return 0;
  }
  name_suffix[0 + name_suffix_idx] = 0;
  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static const char *FileName(const char *path)
{
  unsigned int path_idx = 0;
  const char *separator_position = strrchr(path, '/');
  unsigned int separator_position_idx = 0;
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  separator_position_idx = strrchr(path, '\\');
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  return path;
}


----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int NextFile(Context *context)
{
  const char *arg;
  unsigned int arg_idx = 0;
  size_t arg_len;
  context->iterator += 1;
  context->input_file_length = -1;
  if (context->input_count == 0)
  {
    if (context->iterator > 1)
    {
      return 0;
    }
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  while (context->iterator == context->not_input_indices[context->ignore])
  {
    context->iterator += 1;
    context->ignore += 1;
  }

  if (context->iterator >= context->argc)
  {
    return 0;
  }
  arg_idx = context->argv[context->iterator];
  arg_len = strlen(arg);
  if ((arg_len == 1) && (arg[0 + arg_idx] == '-'))
  {
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  context->current_input_path = &arg[arg_idx];
  context->input_file_length = FileSize(arg);
  context->current_output_path = context->output_path;
  if (context->output_path)
  {
    return 1;
  }
  if (context->write_to_stdout)
  {
    return 1;
  }
  strcpy(context->modified_path, arg);
  context->current_output_path = context->modified_path;
  if (context->decompress)
  {
    helper_NextFile_1(context, arg);
  }
  else
  {
    strcpy(context->modified_path + arg_len, context->suffix);
    return 1;
  }
}


/*** DEPENDENCIES:
static int64_t FileSize(const char *path)
{
  FILE *f = fopen(path, "rb");
  int64_t retval;
  if (f == 0)
  {
    return -1;
  }
  if (fseek(f, 0L, 2) != 0)
  {
    fclose(f);
    return -1;
  }
  retval = ftell(f);
  if (fclose(f) != 0)
  {
    return -1;
  }
  return retval;
}


----------------------------
int helper_NextFile_1(Context * const context, const char * const arg)
{
  size_t suffix_len = strlen(context->suffix);
  char *name = (char *) FileName(context->modified_path);
  char *name_suffix;
  unsigned int name_suffix_idx = 0;
  size_t name_len = strlen(name);
  if (name_len < (suffix_len + 1))
  {
    fprintf(stderr, "empty output file name for [%s] input file\n", PrintablePath(arg));
    context->iterator_error = 1;
    return 0;
  }
  name_suffix_idx = (name + name_len) - suffix_len;
  if (strcmp(context->suffix, name_suffix) != 0)
  {
    fprintf(stderr, "input file [%s] suffix mismatch\n", PrintablePath(arg));
    context->iterator_error = 1;
    return 0;
  }
  name_suffix[0 + name_suffix_idx] = 0;
  return 1;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
***/


static int OpenFiles(Context *context)
{
  int is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if ((!context->test_integrity) && is_ok)
  {
    is_ok = OpenOutputFile(context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}


/*** DEPENDENCIES:
static int OpenOutputFile(const char *output_path, FILE **f, int force)
{
  int fd;
  *f = 0;
  if (!output_path)
  {
    *f = fdopen(STDOUT_FILENO, "wb");
    return 1;
  }
  fd = open(output_path, ((O_CREAT | ((force) ? (0) : (O_EXCL))) | O_WRONLY) | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd < 0)
  {
    fprintf(stderr, "failed to open output file [%s]: %s\n", PrintablePath(output_path), strerror(errno));
    return 0;
  }
  *f = fdopen(fd, "wb");
  if (!(*f))
  {
    fprintf(stderr, "failed to open output file [%s]: %s\n", PrintablePath(output_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
static int OpenInputFile(const char *input_path, FILE **f)
{
  *f = 0;
  if (!input_path)
  {
    *f = fdopen(STDIN_FILENO, "rb");
    return 1;
  }
  *f = fopen(input_path, "rb");
  if (!(*f))
  {
    fprintf(stderr, "failed to open input file [%s]: %s\n", PrintablePath(input_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
***/


static int CloseFiles(Context *context, int success)
{
  int is_ok = 1;
  if ((!context->test_integrity) && context->fout)
  {
    if ((!success) && context->current_output_path)
    {
      unlink(context->current_output_path);
    }
    if (fclose(context->fout) != 0)
    {
      if (success)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
      }
      is_ok = 0;
    }
    if ((success && is_ok) && context->copy_stat)
    {
      CopyStat(context->current_input_path, context->current_output_path);
    }
  }
  if (context->fin)
  {
    if (fclose(context->fin) != 0)
    {
      if (is_ok)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
      }
      is_ok = 0;
    }
  }
  if ((success && context->junk_source) && context->current_input_path)
  {
    unlink(context->current_input_path);
  }
  context->fin = 0;
  context->fout = 0;
  return is_ok;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static void CopyStat(const char *input_path, const char *output_path)
{
  struct stat statbuf;
  struct utimbuf times;
  int res;
  if ((input_path == 0) || (output_path == 0))
  {
    return;
  }
  if (stat(input_path, &statbuf) != 0)
  {
    return;
  }
  times.actime = statbuf.st_atime;
  times.modtime = statbuf.st_mtime;
  utime(output_path, &times);
  res = chmod(output_path, statbuf.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO));
  if (res != 0)
  {
    fprintf(stderr, "setting access bits failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
  res = chown(output_path, (uid_t) (-1), statbuf.st_gid);
  if (res != 0)
  {
    fprintf(stderr, "setting group failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
  res = chown(output_path, statbuf.st_uid, (gid_t) (-1));
  if (res != 0)
  {
    fprintf(stderr, "setting user failed for [%s]: %s\n", PrintablePath(output_path), strerror(errno));
  }
}


----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int ProvideInput(Context *context)
{
  context->available_in = fread(context->input, 1, kFileBufferSize, context->fin);
  context->total_in += context->available_in;
  context->next_in = context->input;
  if (ferror(context->fin))
  {
    fprintf(stderr, "failed to read input [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
static const size_t kFileBufferSize = 1 << 19
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int ProvideOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  return 1;
}


/*** DEPENDENCIES:
static const size_t kFileBufferSize = 1 << 19
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int WriteOutput(Context *context)
{
  size_t out_size = (size_t) (context->next_out - context->output);
  context->total_out += out_size;
  if (out_size == 0)
  {
    return 1;
  }
  if (context->test_integrity)
  {
    return 1;
  }
  fwrite(context->output, 1, out_size, context->fout);
  if (ferror(context->fout))
  {
    fprintf(stderr, "failed to write output [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
***/


static void PrintFileProcessingProgress(Context *context)
{
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static void PrintBytes(size_t value)
{
  if (value < 1024)
  {
    fprintf(stderr, "%d B", (int) value);
  }
  else
    if (value < 1048576)
  {
    fprintf(stderr, "%0.3f KiB", ((double) value) / 1024.0);
  }
  else
    if (value < 1073741824)
  {
    fprintf(stderr, "%0.3f MiB", ((double) value) / 1048576.0);
  }
  else
  {
    fprintf(stderr, "%0.3f GiB", ((double) value) / 1073741824.0);
  }
}


----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
***/


static int CompressFile(Context *context, BrotliEncoderState *s)
{
  int is_eof = 0;
  InitializeBuffers(context);
  for (;;)
  {
    if ((context->available_in == 0) && (!is_eof))
    {
      if (!ProvideInput(context))
      {
        return 0;
      }
      is_eof = !HasMoreInput(context);
    }
    if (!BrotliEncoderCompressStream(s, (is_eof) ? (BROTLI_OPERATION_FINISH) : (BROTLI_OPERATION_PROCESS), &context->available_in, &context->next_in, &context->available_out, &context->next_out, 0))
    {
      fprintf(stderr, "failed to compress data [%s]\n", PrintablePath(context->current_input_path));
      return 0;
    }
    if (context->available_out == 0)
    {
      if (!ProvideOutput(context))
      {
        return 0;
      }
    }
    if (BrotliEncoderIsFinished(s))
    {
      if (!FlushOutput(context))
      {
        return 0;
      }
      if (context->verbosity > 0)
      {
        fprintf(stderr, "Compressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return 1;
    }
  }

}


/*** DEPENDENCIES:
int BrotliEncoderIsFinished(BrotliEncoderState *s)
{
  return (!(!((s->stream_state_ == BROTLI_STREAM_FINISHED) && (!BrotliEncoderHasMoreOutput(s))))) ? (1) : (0);
}


----------------------------
static int HasMoreInput(Context *context)
{
  return (feof(context->fin)) ? (0) : (1);
}


----------------------------
static void InitializeBuffers(Context *context)
{
  context->available_in = 0;
  context->next_in = 0;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
int BrotliEncoderCompressStream(BrotliEncoderState *s, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if (!EnsureInitialized(s))
  {
    return 0;
  }
  if (s->remaining_metadata_bytes_ != (~((uint32_t) 0)))
  {
    if ((*available_in) != s->remaining_metadata_bytes_)
    {
      return 0;
    }
    if (op != BROTLI_OPERATION_EMIT_METADATA)
    {
      return 0;
    }
  }
  if (op == BROTLI_OPERATION_EMIT_METADATA)
  {
    UpdateSizeHint(s, 0);
    return ProcessMetadata(s, available_in, next_in, available_out, next_out, total_out);
  }
  if ((s->stream_state_ == BROTLI_STREAM_METADATA_HEAD) || (s->stream_state_ == BROTLI_STREAM_METADATA_BODY))
  {
    return 0;
  }
  if ((s->stream_state_ != BROTLI_STREAM_PROCESSING) && ((*available_in) != 0))
  {
    return 0;
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    return BrotliEncoderCompressStreamFast(s, op, available_in, next_in, available_out, next_out, total_out);
  }
  while (1)
  {
    helper_BrotliEncoderCompressStream_1(s, op, available_in, next_in, available_out, next_out, total_out);
  }

  CheckFlushComplete(s);
  return 1;
}


----------------------------
static int FlushOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = 0;
  return 1;
}


----------------------------
static int ProvideInput(Context *context)
{
  context->available_in = fread(context->input, 1, kFileBufferSize, context->fin);
  context->total_in += context->available_in;
  context->next_in = context->input;
  if (ferror(context->fin))
  {
    fprintf(stderr, "failed to read input [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static void PrintFileProcessingProgress(Context *context)
{
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}


----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
static int ProvideOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  return 1;
}


----------------------------
***/


int helper_CompressFiles_1(Context * const context)
{
  int is_ok = 1;
  BrotliEncoderState *s = BrotliEncoderCreateInstance(0, 0, 0);
  if (!s)
  {
    fprintf(stderr, "out of memory\n");
    return 0;
  }
  BrotliEncoderSetParameter(s, BROTLI_PARAM_QUALITY, (uint32_t) context->quality);
  if (context->lgwin > 0)
  {
    if (context->lgwin > 24)
    {
      BrotliEncoderSetParameter(s, BROTLI_PARAM_LARGE_WINDOW, 1u);
    }
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, (uint32_t) context->lgwin);
  }
  else
  {
    uint32_t lgwin = 24;
    if (context->input_file_length >= 0)
    {
      lgwin = 10;
      while (((((size_t) 1) << lgwin) - 16) < ((uint64_t) context->input_file_length))
      {
        lgwin += 1;
        if (lgwin == 24)
        {
          break;
        }
      }

    }
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, lgwin);
  }
  if (context->input_file_length > 0)
  {
    uint32_t size_hint = (context->input_file_length < (1 << 30)) ? ((uint32_t) context->input_file_length) : (1u << 30);
    BrotliEncoderSetParameter(s, BROTLI_PARAM_SIZE_HINT, size_hint);
  }
  is_ok = OpenFiles(context);
  if (((is_ok && (!context->current_output_path)) && (!context->force_overwrite)) && isatty(STDOUT_FILENO))
  {
    fprintf(stderr, "Use -h help. Use -f to force output to a terminal.\n");
    is_ok = 0;
  }
  if (is_ok)
  {
    is_ok = CompressFile(context, s);
  }
  BrotliEncoderDestroyInstance(s);
  if (!CloseFiles(context, is_ok))
  {
    is_ok = 0;
  }
  if (!is_ok)
  {
    return 0;
  }
}


/*** DEPENDENCIES:
BrotliEncoderState *BrotliEncoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  BrotliEncoderState *state = 0;
  unsigned int state_idx = 0;
  if ((!alloc_func) && (!free_func))
  {
    state_idx = (BrotliEncoderState *) malloc(sizeof(BrotliEncoderState));
  }
  else
    if (alloc_func && free_func)
  {
    state_idx = (BrotliEncoderState *) alloc_func(opaque, sizeof(BrotliEncoderState));
  }
  if ((&state[state_idx]) == 0)
  {
    return 0;
  }
  BrotliInitMemoryManager(&state->memory_manager_, alloc_func, free_func, opaque);
  BrotliEncoderInitState(state);
  return state;
}


----------------------------
static int OpenFiles(Context *context)
{
  int is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if ((!context->test_integrity) && is_ok)
  {
    is_ok = OpenOutputFile(context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}


----------------------------
static int CompressFile(Context *context, BrotliEncoderState *s)
{
  int is_eof = 0;
  InitializeBuffers(context);
  for (;;)
  {
    if ((context->available_in == 0) && (!is_eof))
    {
      if (!ProvideInput(context))
      {
        return 0;
      }
      is_eof = !HasMoreInput(context);
    }
    if (!BrotliEncoderCompressStream(s, (is_eof) ? (BROTLI_OPERATION_FINISH) : (BROTLI_OPERATION_PROCESS), &context->available_in, &context->next_in, &context->available_out, &context->next_out, 0))
    {
      fprintf(stderr, "failed to compress data [%s]\n", PrintablePath(context->current_input_path));
      return 0;
    }
    if (context->available_out == 0)
    {
      if (!ProvideOutput(context))
      {
        return 0;
      }
    }
    if (BrotliEncoderIsFinished(s))
    {
      if (!FlushOutput(context))
      {
        return 0;
      }
      if (context->verbosity > 0)
      {
        fprintf(stderr, "Compressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return 1;
    }
  }

}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int CloseFiles(Context *context, int success)
{
  int is_ok = 1;
  if ((!context->test_integrity) && context->fout)
  {
    if ((!success) && context->current_output_path)
    {
      unlink(context->current_output_path);
    }
    if (fclose(context->fout) != 0)
    {
      if (success)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
      }
      is_ok = 0;
    }
    if ((success && is_ok) && context->copy_stat)
    {
      CopyStat(context->current_input_path, context->current_output_path);
    }
  }
  if (context->fin)
  {
    if (fclose(context->fin) != 0)
    {
      if (is_ok)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
      }
      is_ok = 0;
    }
  }
  if ((success && context->junk_source) && context->current_input_path)
  {
    unlink(context->current_input_path);
  }
  context->fin = 0;
  context->fout = 0;
  return is_ok;
}


----------------------------
int BrotliEncoderSetParameter(BrotliEncoderState *state, BrotliEncoderParameter p, uint32_t value)
{
  if (state->is_initialized_)
  {
    return 0;
  }
  switch (p)
  {
    case BROTLI_PARAM_MODE:
    {
      state->params.mode = (BrotliEncoderMode) value;
      return 1;
    }

    case BROTLI_PARAM_QUALITY:
    {
      state->params.quality = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGWIN:
    {
      state->params.lgwin = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGBLOCK:
    {
      state->params.lgblock = (int) value;
      return 1;
    }

    case BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING:
    {
      if ((value != 0) && (value != 1))
      {
        return 0;
      }
      state->params.disable_literal_context_modeling = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_SIZE_HINT:
    {
      state->params.size_hint = value;
      return 1;
    }

    case BROTLI_PARAM_LARGE_WINDOW:
    {
      state->params.large_window = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_NPOSTFIX:
    {
      state->params.dist.distance_postfix_bits = value;
      return 1;
    }

    case BROTLI_PARAM_NDIRECT:
    {
      state->params.dist.num_direct_distance_codes = value;
      return 1;
    }

    case BROTLI_PARAM_STREAM_OFFSET:
    {
      if (value > (1u << 30))
      {
        return 0;
      }
      state->params.stream_offset = value;
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
void BrotliEncoderDestroyInstance(BrotliEncoderState *state)
{
  if (!state)
  {
    return;
  }
  else
  {
    MemoryManager *m = &state->memory_manager_;
    brotli_free_func free_func = m->free_func;
    void *opaque = m->opaque;
    BrotliEncoderCleanupState(state);
    free_func(opaque, state);
  }
}


----------------------------
***/


static int CompressFiles(Context *context)
{
  while (NextFile(context))
  {
    helper_CompressFiles_1(context);
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
int helper_CompressFiles_1(Context * const context)
{
  int is_ok = 1;
  BrotliEncoderState *s = BrotliEncoderCreateInstance(0, 0, 0);
  if (!s)
  {
    fprintf(stderr, "out of memory\n");
    return 0;
  }
  BrotliEncoderSetParameter(s, BROTLI_PARAM_QUALITY, (uint32_t) context->quality);
  if (context->lgwin > 0)
  {
    if (context->lgwin > 24)
    {
      BrotliEncoderSetParameter(s, BROTLI_PARAM_LARGE_WINDOW, 1u);
    }
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, (uint32_t) context->lgwin);
  }
  else
  {
    uint32_t lgwin = 24;
    if (context->input_file_length >= 0)
    {
      lgwin = 10;
      while (((((size_t) 1) << lgwin) - 16) < ((uint64_t) context->input_file_length))
      {
        lgwin += 1;
        if (lgwin == 24)
        {
          break;
        }
      }

    }
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, lgwin);
  }
  if (context->input_file_length > 0)
  {
    uint32_t size_hint = (context->input_file_length < (1 << 30)) ? ((uint32_t) context->input_file_length) : (1u << 30);
    BrotliEncoderSetParameter(s, BROTLI_PARAM_SIZE_HINT, size_hint);
  }
  is_ok = OpenFiles(context);
  if (((is_ok && (!context->current_output_path)) && (!context->force_overwrite)) && isatty(STDOUT_FILENO))
  {
    fprintf(stderr, "Use -h help. Use -f to force output to a terminal.\n");
    is_ok = 0;
  }
  if (is_ok)
  {
    is_ok = CompressFile(context, s);
  }
  BrotliEncoderDestroyInstance(s);
  if (!CloseFiles(context, is_ok))
  {
    is_ok = 0;
  }
  if (!is_ok)
  {
    return 0;
  }
}


----------------------------
static int NextFile(Context *context)
{
  const char *arg;
  unsigned int arg_idx = 0;
  size_t arg_len;
  context->iterator += 1;
  context->input_file_length = -1;
  if (context->input_count == 0)
  {
    if (context->iterator > 1)
    {
      return 0;
    }
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  while (context->iterator == context->not_input_indices[context->ignore])
  {
    context->iterator += 1;
    context->ignore += 1;
  }

  if (context->iterator >= context->argc)
  {
    return 0;
  }
  arg_idx = context->argv[context->iterator];
  arg_len = strlen(arg);
  if ((arg_len == 1) && (arg[0 + arg_idx] == '-'))
  {
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  context->current_input_path = &arg[arg_idx];
  context->input_file_length = FileSize(arg);
  context->current_output_path = context->output_path;
  if (context->output_path)
  {
    return 1;
  }
  if (context->write_to_stdout)
  {
    return 1;
  }
  strcpy(context->modified_path, arg);
  context->current_output_path = context->modified_path;
  if (context->decompress)
  {
    helper_NextFile_1(context, arg);
  }
  else
  {
    strcpy(context->modified_path + arg_len, context->suffix);
    return 1;
  }
}


----------------------------
***/


// hint:  ['command_set_ref is a mutable refrence to int', 'quality_set_ref is a mutable refrence to int', 'output_set_ref is a mutable refrence to int', 'keep_set_ref is a mutable refrence to int', 'lgwin_set_ref is a mutable refrence to int', 'suffix_set_ref is a mutable refrence to int', 'command_ref is a mutable refrence to Command', 'arg_idx_ref is a mutable refrence to unsigned int']
Command helper_helper_ParseParams_1_1(int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, unsigned int * const arg_idx_ref, Context * const params, const char * const arg)
{
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  unsigned int arg_idx = *arg_idx_ref;
  arg_idx = &arg_idx[2];
  if (strcmp("best", arg) == 0)
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = 11;
  }
  else
    if (strcmp("decompress", arg) == 0)
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing --decompress\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_DECOMPRESS;
  }
  else
    if (strcmp("force", arg) == 0)
  {
    if (params->force_overwrite)
    {
      fprintf(stderr, "force output overwrite already set\n");
      return COMMAND_INVALID;
    }
    params->force_overwrite = 1;
  }
  else
    if (strcmp("help", arg) == 0)
  {
    return COMMAND_HELP;
  }
  else
    if (strcmp("keep", arg) == 0)
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = 0;
  }
  else
    if (strcmp("no-copy-stat", arg) == 0)
  {
    if (!params->copy_stat)
    {
      fprintf(stderr, "argument --no-copy-stat / -n already set\n");
      return COMMAND_INVALID;
    }
    params->copy_stat = 0;
  }
  else
    if (strcmp("rm", arg) == 0)
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = 1;
  }
  else
    if (strcmp("stdout", arg) == 0)
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set\n");
      return COMMAND_INVALID;
    }
    output_set = 1;
    params->write_to_stdout = 1;
  }
  else
    if (strcmp("test", arg) == 0)
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing --test\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_TEST_INTEGRITY;
  }
  else
    if (strcmp("verbose", arg) == 0)
  {
    if (params->verbosity > 0)
    {
      fprintf(stderr, "argument --verbose / -v already set\n");
      return COMMAND_INVALID;
    }
    params->verbosity = 1;
  }
  else
    if (strcmp("version", arg) == 0)
  {
    return COMMAND_VERSION;
  }
  else
  {
    helper_helper_helper_ParseParams_1_1_1(&quality_set, &lgwin_set, &suffix_set, params, arg, output_set, arg_idx);
  }
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
  *arg_idx_ref = arg_idx;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
Command helper_helper_helper_ParseParams_1_1_1(int * const quality_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Context * const params, const char * const arg, int output_set, unsigned int arg_idx)
{
  int quality_set = *quality_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  const char *value = strrchr(arg, '=');
  size_t key_len;
  if ((!value) || (value[1] == 0))
  {
    fprintf(stderr, "must pass the parameter as --%s=value\n", arg);
    return COMMAND_INVALID;
  }
  key_len = (size_t) (value - (&arg[arg_idx]));
  value++;
  if (strncmp("lgwin", arg, key_len) == 0)
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(value, 0, 24, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", value);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("large_window", arg, key_len) == 0)
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(value, 0, 30, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", value);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("output", arg, key_len) == 0)
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set (--output)\n");
      return COMMAND_INVALID;
    }
    params->output_path = value;
  }
  else
    if (strncmp("quality", arg, key_len) == 0)
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = ParseInt(value, 0, 11, &params->quality);
    if (!quality_set)
    {
      fprintf(stderr, "error parsing quality value [%s]\n", value);
      return COMMAND_INVALID;
    }
  }
  else
    if (strncmp("suffix", arg, key_len) == 0)
  {
    if (suffix_set)
    {
      fprintf(stderr, "suffix already set\n");
      return COMMAND_INVALID;
    }
    suffix_set = 1;
    params->suffix = value;
  }
  else
  {
    fprintf(stderr, "invalid parameter: [%s]\n", arg);
    return COMMAND_INVALID;
  }
  *quality_set_ref = quality_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


// hint:  ['next_option_index_ref is a mutable refrence to int', 'command_set_ref is a mutable refrence to int', 'quality_set_ref is a mutable refrence to int', 'output_set_ref is a mutable refrence to int', 'keep_set_ref is a mutable refrence to int', 'lgwin_set_ref is a mutable refrence to int', 'suffix_set_ref is a mutable refrence to int', 'command_ref is a mutable refrence to Command']
Command helper_helper_helper_ParseParams_1_2_1(int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i, const char * const arg, unsigned int arg_idx, size_t arg_len, size_t j)
{
  int next_option_index = *next_option_index_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  char c = arg[j + arg_idx];
  if ((c >= '0') && (c <= '9'))
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = c - '0';
    continue;
  }
  else
    if (c == 'c')
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set\n");
      return COMMAND_INVALID;
    }
    output_set = 1;
    params->write_to_stdout = 1;
    continue;
  }
  else
    if (c == 'd')
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing -d\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_DECOMPRESS;
    continue;
  }
  else
    if (c == 'f')
  {
    if (params->force_overwrite)
    {
      fprintf(stderr, "force output overwrite already set\n");
      return COMMAND_INVALID;
    }
    params->force_overwrite = 1;
    continue;
  }
  else
    if (c == 'h')
  {
    return COMMAND_HELP;
  }
  else
    if ((c == 'j') || (c == 'k'))
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = (!(!(c == 'j'))) ? (1) : (0);
    continue;
  }
  else
    if (c == 'n')
  {
    if (!params->copy_stat)
    {
      fprintf(stderr, "argument --no-copy-stat / -n already set\n");
      return COMMAND_INVALID;
    }
    params->copy_stat = 0;
    continue;
  }
  else
    if (c == 't')
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing -t\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_TEST_INTEGRITY;
    continue;
  }
  else
    if (c == 'v')
  {
    if (params->verbosity > 0)
    {
      fprintf(stderr, "argument --verbose / -v already set\n");
      return COMMAND_INVALID;
    }
    params->verbosity = 1;
    continue;
  }
  else
    if (c == 'V')
  {
    return COMMAND_VERSION;
  }
  else
    if (c == 'Z')
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = 11;
    continue;
  }
  if (((((c != 'o') && (c != 'q')) && (c != 'w')) && (c != 'D')) && (c != 'S'))
  {
    fprintf(stderr, "invalid argument -%c\n", c);
    return COMMAND_INVALID;
  }
  if ((j + 1) != arg_len)
  {
    fprintf(stderr, "expected parameter for argument -%c\n", c);
    return COMMAND_INVALID;
  }
  i++;
  if (((i == argc) || (!argv[i])) || (argv[i][0] == 0))
  {
    fprintf(stderr, "expected parameter for argument -%c\n", c);
    return COMMAND_INVALID;
  }
  params->not_input_indices[next_option_index++] = i;
  if (c == 'o')
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set (-o)\n");
      return COMMAND_INVALID;
    }
    params->output_path = argv[i];
  }
  else
    if (c == 'q')
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = ParseInt(argv[i], 0, 11, &params->quality);
    if (!quality_set)
    {
      fprintf(stderr, "error parsing quality value [%s]\n", argv[i]);
      return COMMAND_INVALID;
    }
  }
  else
    if (c == 'w')
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(argv[i], 0, 24, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", argv[i]);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (c == 'S')
  {
    if (suffix_set)
    {
      fprintf(stderr, "suffix already set\n");
      return COMMAND_INVALID;
    }
    suffix_set = 1;
    params->suffix = argv[i];
  }
  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int ParseInt(const char *s, int low, int high, int *result)
{
  int value = 0;
  int i;
  for (i = 0; i < 5; i += 1)
  {
    char c = s[i];
    if (c == 0)
    {
      break;
    }
    if ((s[i] < '0') || (s[i] > '9'))
    {
      return 0;
    }
    value = (10 * value) + (c - '0');
  }

  if (i == 0)
  {
    return 0;
  }
  if ((i > 1) && (s[0] == '0'))
  {
    return 0;
  }
  if (s[i] != 0)
  {
    return 0;
  }
  if ((value < low) || (value > high))
  {
    return 0;
  }
  *result = value;
  return 1;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


// hint:  ['next_option_index_ref is a mutable refrence to int', 'command_set_ref is a mutable refrence to int', 'quality_set_ref is a mutable refrence to int', 'output_set_ref is a mutable refrence to int', 'keep_set_ref is a mutable refrence to int', 'lgwin_set_ref is a mutable refrence to int', 'suffix_set_ref is a mutable refrence to int', 'command_ref is a mutable refrence to Command']
Command helper_helper_ParseParams_1_2(int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i, const char * const arg, unsigned int arg_idx, size_t arg_len)
{
  int next_option_index = *next_option_index_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  size_t j;
  for (j = 1; j < arg_len; ++j)
  {
    helper_helper_helper_ParseParams_1_2_1(&next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, i, arg, arg_idx, arg_len, j);
  }

  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}


/*** DEPENDENCIES:
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
Command helper_helper_helper_ParseParams_1_2_1(int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i, const char * const arg, unsigned int arg_idx, size_t arg_len, size_t j)
{
  int next_option_index = *next_option_index_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  char c = arg[j + arg_idx];
  if ((c >= '0') && (c <= '9'))
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = c - '0';
    continue;
  }
  else
    if (c == 'c')
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set\n");
      return COMMAND_INVALID;
    }
    output_set = 1;
    params->write_to_stdout = 1;
    continue;
  }
  else
    if (c == 'd')
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing -d\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_DECOMPRESS;
    continue;
  }
  else
    if (c == 'f')
  {
    if (params->force_overwrite)
    {
      fprintf(stderr, "force output overwrite already set\n");
      return COMMAND_INVALID;
    }
    params->force_overwrite = 1;
    continue;
  }
  else
    if (c == 'h')
  {
    return COMMAND_HELP;
  }
  else
    if ((c == 'j') || (c == 'k'))
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = (!(!(c == 'j'))) ? (1) : (0);
    continue;
  }
  else
    if (c == 'n')
  {
    if (!params->copy_stat)
    {
      fprintf(stderr, "argument --no-copy-stat / -n already set\n");
      return COMMAND_INVALID;
    }
    params->copy_stat = 0;
    continue;
  }
  else
    if (c == 't')
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing -t\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_TEST_INTEGRITY;
    continue;
  }
  else
    if (c == 'v')
  {
    if (params->verbosity > 0)
    {
      fprintf(stderr, "argument --verbose / -v already set\n");
      return COMMAND_INVALID;
    }
    params->verbosity = 1;
    continue;
  }
  else
    if (c == 'V')
  {
    return COMMAND_VERSION;
  }
  else
    if (c == 'Z')
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = 11;
    continue;
  }
  if (((((c != 'o') && (c != 'q')) && (c != 'w')) && (c != 'D')) && (c != 'S'))
  {
    fprintf(stderr, "invalid argument -%c\n", c);
    return COMMAND_INVALID;
  }
  if ((j + 1) != arg_len)
  {
    fprintf(stderr, "expected parameter for argument -%c\n", c);
    return COMMAND_INVALID;
  }
  i++;
  if (((i == argc) || (!argv[i])) || (argv[i][0] == 0))
  {
    fprintf(stderr, "expected parameter for argument -%c\n", c);
    return COMMAND_INVALID;
  }
  params->not_input_indices[next_option_index++] = i;
  if (c == 'o')
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set (-o)\n");
      return COMMAND_INVALID;
    }
    params->output_path = argv[i];
  }
  else
    if (c == 'q')
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = ParseInt(argv[i], 0, 11, &params->quality);
    if (!quality_set)
    {
      fprintf(stderr, "error parsing quality value [%s]\n", argv[i]);
      return COMMAND_INVALID;
    }
  }
  else
    if (c == 'w')
  {
    if (lgwin_set)
    {
      fprintf(stderr, "lgwin parameter already set\n");
      return COMMAND_INVALID;
    }
    lgwin_set = ParseInt(argv[i], 0, 24, &params->lgwin);
    if (!lgwin_set)
    {
      fprintf(stderr, "error parsing lgwin value [%s]\n", argv[i]);
      return COMMAND_INVALID;
    }
    if ((params->lgwin != 0) && (params->lgwin < 10))
    {
      fprintf(stderr, "lgwin parameter (%d) smaller than the minimum (%d)\n", params->lgwin, 10);
      return COMMAND_INVALID;
    }
  }
  else
    if (c == 'S')
  {
    if (suffix_set)
    {
      fprintf(stderr, "suffix already set\n");
      return COMMAND_INVALID;
    }
    suffix_set = 1;
    params->suffix = argv[i];
  }
  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


// hint:  ['next_option_index_ref is a mutable refrence to int', 'input_count_ref is a mutable refrence to size_t', 'longest_path_len_ref is a mutable refrence to size_t', 'command_set_ref is a mutable refrence to int', 'quality_set_ref is a mutable refrence to int', 'output_set_ref is a mutable refrence to int', 'keep_set_ref is a mutable refrence to int', 'lgwin_set_ref is a mutable refrence to int', 'suffix_set_ref is a mutable refrence to int', 'after_dash_dash_ref is a mutable refrence to int', 'command_ref is a mutable refrence to Command']
Command helper_ParseParams_1(int * const next_option_index_ref, size_t * const input_count_ref, size_t * const longest_path_len_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, int * const after_dash_dash_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i)
{
  int next_option_index = *next_option_index_ref;
  size_t input_count = *input_count_ref;
  size_t longest_path_len = *longest_path_len_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  int after_dash_dash = *after_dash_dash_ref;
  Command command = *command_ref;
  const char *arg = argv[i];
  unsigned int arg_idx = 0;
  size_t arg_len = (arg) ? (strlen(arg)) : (0);
  if (arg_len == 0)
  {
    params->not_input_indices[next_option_index] = i;
    next_option_index += 1;
    continue;
  }
  if (next_option_index > (20 - 2))
  {
    fprintf(stderr, "too many options passed\n");
    return COMMAND_INVALID;
  }
  if ((after_dash_dash || (arg[0 + arg_idx] != '-')) || (arg_len == 1))
  {
    input_count += 1;
    if (longest_path_len < arg_len)
    {
      longest_path_len = arg_len;
    }
    continue;
  }
  params->not_input_indices[next_option_index] = i;
  next_option_index += 1;
  if ((arg_len == 2) && (arg[1 + arg_idx] == '-'))
  {
    after_dash_dash = 1;
    continue;
  }
  if (arg[1 + arg_idx] != '-')
  {
    helper_helper_ParseParams_1_2(&next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, i, arg, arg_idx, arg_len);
  }
  else
  {
    helper_helper_ParseParams_1_1(&command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, &arg_idx, params, arg);
  }
  *next_option_index_ref = next_option_index;
  *input_count_ref = input_count;
  *longest_path_len_ref = longest_path_len;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *after_dash_dash_ref = after_dash_dash;
  *command_ref = command;
}


/*** DEPENDENCIES:
Command helper_helper_ParseParams_1_1(int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, unsigned int * const arg_idx_ref, Context * const params, const char * const arg)
{
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  unsigned int arg_idx = *arg_idx_ref;
  arg_idx = &arg_idx[2];
  if (strcmp("best", arg) == 0)
  {
    if (quality_set)
    {
      fprintf(stderr, "quality already set\n");
      return COMMAND_INVALID;
    }
    quality_set = 1;
    params->quality = 11;
  }
  else
    if (strcmp("decompress", arg) == 0)
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing --decompress\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_DECOMPRESS;
  }
  else
    if (strcmp("force", arg) == 0)
  {
    if (params->force_overwrite)
    {
      fprintf(stderr, "force output overwrite already set\n");
      return COMMAND_INVALID;
    }
    params->force_overwrite = 1;
  }
  else
    if (strcmp("help", arg) == 0)
  {
    return COMMAND_HELP;
  }
  else
    if (strcmp("keep", arg) == 0)
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = 0;
  }
  else
    if (strcmp("no-copy-stat", arg) == 0)
  {
    if (!params->copy_stat)
    {
      fprintf(stderr, "argument --no-copy-stat / -n already set\n");
      return COMMAND_INVALID;
    }
    params->copy_stat = 0;
  }
  else
    if (strcmp("rm", arg) == 0)
  {
    if (keep_set)
    {
      fprintf(stderr, "argument --rm / -j or --keep / -k already set\n");
      return COMMAND_INVALID;
    }
    keep_set = 1;
    params->junk_source = 1;
  }
  else
    if (strcmp("stdout", arg) == 0)
  {
    if (output_set)
    {
      fprintf(stderr, "write to standard output already set\n");
      return COMMAND_INVALID;
    }
    output_set = 1;
    params->write_to_stdout = 1;
  }
  else
    if (strcmp("test", arg) == 0)
  {
    if (command_set)
    {
      fprintf(stderr, "command already set when parsing --test\n");
      return COMMAND_INVALID;
    }
    command_set = 1;
    command = COMMAND_TEST_INTEGRITY;
  }
  else
    if (strcmp("verbose", arg) == 0)
  {
    if (params->verbosity > 0)
    {
      fprintf(stderr, "argument --verbose / -v already set\n");
      return COMMAND_INVALID;
    }
    params->verbosity = 1;
  }
  else
    if (strcmp("version", arg) == 0)
  {
    return COMMAND_VERSION;
  }
  else
  {
    helper_helper_helper_ParseParams_1_1_1(&quality_set, &lgwin_set, &suffix_set, params, arg, output_set, arg_idx);
  }
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
  *arg_idx_ref = arg_idx;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
Command helper_helper_ParseParams_1_2(int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i, const char * const arg, unsigned int arg_idx, size_t arg_len)
{
  int next_option_index = *next_option_index_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  size_t j;
  for (j = 1; j < arg_len; ++j)
  {
    helper_helper_helper_ParseParams_1_2_1(&next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, i, arg, arg_idx, arg_len, j);
  }

  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


static Command ParseParams(Context *params)
{
  int argc = params->argc;
  char **argv = params->argv;
  int i;
  int next_option_index = 0;
  size_t input_count = 0;
  size_t longest_path_len = 1;
  int command_set = 0;
  int quality_set = 0;
  int output_set = 0;
  int keep_set = 0;
  int lgwin_set = 0;
  int suffix_set = 0;
  int after_dash_dash = 0;
  Command command = ParseAlias(argv[0]);
  for (i = 1; i < argc; i += 1)
  {
    helper_ParseParams_1(&next_option_index, &input_count, &longest_path_len, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &after_dash_dash, &command, params, argc, argv, i);
  }

  params->input_count = input_count;
  params->longest_path_len = longest_path_len;
  params->decompress = command == COMMAND_DECOMPRESS;
  params->test_integrity = command == COMMAND_TEST_INTEGRITY;
  if ((input_count > 1) && output_set)
  {
    return COMMAND_INVALID;
  }
  if (params->test_integrity)
  {
    if (params->output_path)
    {
      return COMMAND_INVALID;
    }
    if (params->write_to_stdout)
    {
      return COMMAND_INVALID;
    }
  }
  if (strchr(params->suffix, '/') || strchr(params->suffix, '\\'))
  {
    return COMMAND_INVALID;
  }
  return command;
}


/*** DEPENDENCIES:
Command helper_ParseParams_1(int * const next_option_index_ref, size_t * const input_count_ref, size_t * const longest_path_len_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, int * const after_dash_dash_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, int i)
{
  int next_option_index = *next_option_index_ref;
  size_t input_count = *input_count_ref;
  size_t longest_path_len = *longest_path_len_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  int after_dash_dash = *after_dash_dash_ref;
  Command command = *command_ref;
  const char *arg = argv[i];
  unsigned int arg_idx = 0;
  size_t arg_len = (arg) ? (strlen(arg)) : (0);
  if (arg_len == 0)
  {
    params->not_input_indices[next_option_index] = i;
    next_option_index += 1;
    continue;
  }
  if (next_option_index > (20 - 2))
  {
    fprintf(stderr, "too many options passed\n");
    return COMMAND_INVALID;
  }
  if ((after_dash_dash || (arg[0 + arg_idx] != '-')) || (arg_len == 1))
  {
    input_count += 1;
    if (longest_path_len < arg_len)
    {
      longest_path_len = arg_len;
    }
    continue;
  }
  params->not_input_indices[next_option_index] = i;
  next_option_index += 1;
  if ((arg_len == 2) && (arg[1 + arg_idx] == '-'))
  {
    after_dash_dash = 1;
    continue;
  }
  if (arg[1 + arg_idx] != '-')
  {
    helper_helper_ParseParams_1_2(&next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, i, arg, arg_idx, arg_len);
  }
  else
  {
    helper_helper_ParseParams_1_1(&command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, &arg_idx, params, arg);
  }
  *next_option_index_ref = next_option_index;
  *input_count_ref = input_count;
  *longest_path_len_ref = longest_path_len;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *after_dash_dash_ref = after_dash_dash;
  *command_ref = command;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static Command ParseAlias(const char *name)
{
  unsigned int name_idx = 0;
  const char *unbrotli = "unbrotli";
  size_t unbrotli_len = strlen(unbrotli);
  name_idx = FileName(name_idx);
  if (strncmp(name, unbrotli, unbrotli_len) == 0)
  {
    char terminator = name[unbrotli_len + name_idx];
    if ((terminator == 0) || (terminator == '.'))
    {
      return COMMAND_DECOMPRESS;
    }
  }
  return COMMAND_COMPRESS;
}


----------------------------
***/


static int DecompressFile(Context *context, BrotliDecoderState *s)
{
  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;
  InitializeBuffers(context);
  for (;;)
  {
    if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT)
    {
      if (!HasMoreInput(context))
      {
        fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
        return 0;
      }
      if (!ProvideInput(context))
      {
        return 0;
      }
    }
    else
      if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT)
    {
      if (!ProvideOutput(context))
      {
        return 0;
      }
    }
    else
      if (result == BROTLI_DECODER_RESULT_SUCCESS)
    {
      if (!FlushOutput(context))
      {
        return 0;
      }
      int has_more_input = (context->available_in != 0) || (fgetc(context->fin) != EOF);
      if (has_more_input)
      {
        fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
        return 0;
      }
      if (context->verbosity > 0)
      {
        fprintf(stderr, "Decompressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return 1;
    }
    else
    {
      fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
      return 0;
    }
    result = BrotliDecoderDecompressStream(s, &context->available_in, &context->next_in, &context->available_out, &context->next_out, 0);
  }

}


/*** DEPENDENCIES:
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
static int HasMoreInput(Context *context)
{
  return (feof(context->fin)) ? (0) : (1);
}


----------------------------
static void InitializeBuffers(Context *context)
{
  context->available_in = 0;
  context->next_in = 0;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int FlushOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = 0;
  return 1;
}


----------------------------
static int ProvideInput(Context *context)
{
  context->available_in = fread(context->input, 1, kFileBufferSize, context->fin);
  context->total_in += context->available_in;
  context->next_in = context->input;
  if (ferror(context->fin))
  {
    fprintf(stderr, "failed to read input [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
    return 0;
  }
  return 1;
}


----------------------------
static void PrintFileProcessingProgress(Context *context)
{
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}


----------------------------
static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}


----------------------------
static int ProvideOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  return 1;
}


----------------------------
BrotliDecoderResult BrotliDecoderDecompressStream(BrotliDecoderStateInternal *s, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  unsigned int next_out_idx = 0;
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliBitReader *br = &s->br;
  if (total_out)
  {
    *total_out = s->partial_pos_out;
  }
  if (((int) s->error_code) < 0)
  {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  if ((*available_out) && ((!(&next_out[next_out_idx])) || (!(*(&next_out[next_out_idx])))))
  {
    return SaveErrorCode(s, ((void) 0, BROTLI_DECODER_ERROR_INVALID_ARGUMENTS));
  }
  if (!(*available_out))
  {
    next_out_idx = 0;
  }
  if (s->buffer_length == 0)
  {
    br->avail_in = *available_in;
    br->next_in = *next_in;
  }
  else
  {
    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    br->next_in = &s->buffer.u8[0];
  }
  for (;;)
  {
    helper_BrotliDecoderDecompressStream_1(&result, s, available_in, next_in, available_out, next_out, total_out, br);
  }

  return SaveErrorCode(s, result);
}


----------------------------
typedef enum 
{
  BROTLI_DECODER_RESULT_ERROR = 0,
  BROTLI_DECODER_RESULT_SUCCESS = 1,
  BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT = 2,
  BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT = 3
} BrotliDecoderResult
----------------------------
***/


static int DecompressFiles(Context *context)
{
  while (NextFile(context))
  {
    int is_ok = 1;
    BrotliDecoderState *s = BrotliDecoderCreateInstance(0, 0, 0);
    if (!s)
    {
      fprintf(stderr, "out of memory\n");
      return 0;
    }
    BrotliDecoderSetParameter(s, BROTLI_DECODER_PARAM_LARGE_WINDOW, 1u);
    is_ok = OpenFiles(context);
    if (((is_ok && (!context->current_input_path)) && (!context->force_overwrite)) && isatty(STDIN_FILENO))
    {
      fprintf(stderr, "Use -h help. Use -f to force input from a terminal.\n");
      is_ok = 0;
    }
    if (is_ok)
    {
      is_ok = DecompressFile(context, s);
    }
    BrotliDecoderDestroyInstance(s);
    if (!CloseFiles(context, is_ok))
    {
      is_ok = 0;
    }
    if (!is_ok)
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
void BrotliDecoderDestroyInstance(BrotliDecoderStateInternal *state)
{
  if (!state)
  {
    return;
  }
  else
  {
    brotli_free_func free_func = state->free_func;
    void *opaque = state->memory_manager_opaque;
    BrotliDecoderStateCleanup(state);
    free_func(opaque, state);
  }
}


----------------------------
typedef struct BrotliDecoderStateStruct BrotliDecoderState
----------------------------
BrotliDecoderStateInternal *BrotliDecoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  BrotliDecoderStateInternal *state = 0;
  unsigned int state_idx = 0;
  if ((!alloc_func) && (!free_func))
  {
    state_idx = (BrotliDecoderStateInternal *) malloc(sizeof(BrotliDecoderStateInternal));
  }
  else
    if (alloc_func && free_func)
  {
    state_idx = (BrotliDecoderStateInternal *) alloc_func(opaque, sizeof(BrotliDecoderStateInternal));
  }
  if ((&state[state_idx]) == 0)
  {
    (void) 0;
    return 0;
  }
  if (!BrotliDecoderStateInit(state, alloc_func, free_func, opaque))
  {
    (void) 0;
    if ((!alloc_func) && (!free_func))
    {
      free(state);
    }
    else
      if (alloc_func && free_func)
    {
      free_func(opaque, state);
    }
    return 0;
  }
  return state;
}


----------------------------
static int OpenFiles(Context *context)
{
  int is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if ((!context->test_integrity) && is_ok)
  {
    is_ok = OpenOutputFile(context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int NextFile(Context *context)
{
  const char *arg;
  unsigned int arg_idx = 0;
  size_t arg_len;
  context->iterator += 1;
  context->input_file_length = -1;
  if (context->input_count == 0)
  {
    if (context->iterator > 1)
    {
      return 0;
    }
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  while (context->iterator == context->not_input_indices[context->ignore])
  {
    context->iterator += 1;
    context->ignore += 1;
  }

  if (context->iterator >= context->argc)
  {
    return 0;
  }
  arg_idx = context->argv[context->iterator];
  arg_len = strlen(arg);
  if ((arg_len == 1) && (arg[0 + arg_idx] == '-'))
  {
    context->current_input_path = 0;
    context->current_output_path = context->output_path;
    return 1;
  }
  context->current_input_path = &arg[arg_idx];
  context->input_file_length = FileSize(arg);
  context->current_output_path = context->output_path;
  if (context->output_path)
  {
    return 1;
  }
  if (context->write_to_stdout)
  {
    return 1;
  }
  strcpy(context->modified_path, arg);
  context->current_output_path = context->modified_path;
  if (context->decompress)
  {
    helper_NextFile_1(context, arg);
  }
  else
  {
    strcpy(context->modified_path + arg_len, context->suffix);
    return 1;
  }
}


----------------------------
static int CloseFiles(Context *context, int success)
{
  int is_ok = 1;
  if ((!context->test_integrity) && context->fout)
  {
    if ((!success) && context->current_output_path)
    {
      unlink(context->current_output_path);
    }
    if (fclose(context->fout) != 0)
    {
      if (success)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_output_path), strerror(errno));
      }
      is_ok = 0;
    }
    if ((success && is_ok) && context->copy_stat)
    {
      CopyStat(context->current_input_path, context->current_output_path);
    }
  }
  if (context->fin)
  {
    if (fclose(context->fin) != 0)
    {
      if (is_ok)
      {
        fprintf(stderr, "fclose failed [%s]: %s\n", PrintablePath(context->current_input_path), strerror(errno));
      }
      is_ok = 0;
    }
  }
  if ((success && context->junk_source) && context->current_input_path)
  {
    unlink(context->current_input_path);
  }
  context->fin = 0;
  context->fout = 0;
  return is_ok;
}


----------------------------
static int DecompressFile(Context *context, BrotliDecoderState *s)
{
  BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;
  InitializeBuffers(context);
  for (;;)
  {
    if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT)
    {
      if (!HasMoreInput(context))
      {
        fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
        return 0;
      }
      if (!ProvideInput(context))
      {
        return 0;
      }
    }
    else
      if (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT)
    {
      if (!ProvideOutput(context))
      {
        return 0;
      }
    }
    else
      if (result == BROTLI_DECODER_RESULT_SUCCESS)
    {
      if (!FlushOutput(context))
      {
        return 0;
      }
      int has_more_input = (context->available_in != 0) || (fgetc(context->fin) != EOF);
      if (has_more_input)
      {
        fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
        return 0;
      }
      if (context->verbosity > 0)
      {
        fprintf(stderr, "Decompressed ");
        PrintFileProcessingProgress(context);
        fprintf(stderr, "\n");
      }
      return 1;
    }
    else
    {
      fprintf(stderr, "corrupt input [%s]\n", PrintablePath(context->current_input_path));
      return 0;
    }
    result = BrotliDecoderDecompressStream(s, &context->available_in, &context->next_in, &context->available_out, &context->next_out, 0);
  }

}


----------------------------
int BrotliDecoderSetParameter(BrotliDecoderStateInternal *state, BrotliDecoderParameter p, uint32_t value)
{
  if (state->state != BROTLI_STATE_UNINITED)
  {
    return 0;
  }
  switch (p)
  {
    case BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION:
    {
      state->canny_ringbuffer_allocation = (!(!value)) ? (0) : (1);
      return 1;
    }

    case BROTLI_DECODER_PARAM_LARGE_WINDOW:
    {
      state->large_window = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
***/


int main(int argc, char **argv)
{
  Command command;
  Context context;
  int is_ok = 1;
  int i;
  context.quality = 11;
  context.lgwin = -1;
  context.verbosity = 0;
  context.force_overwrite = 0;
  context.junk_source = 0;
  context.copy_stat = 1;
  context.test_integrity = 0;
  context.write_to_stdout = 0;
  context.decompress = 0;
  context.large_window = 0;
  context.output_path = 0;
  context.suffix = ".br";
  for (i = 0; i < 20; i += 1)
    context.not_input_indices[i] = 0;

  context.longest_path_len = 1;
  context.input_count = 0;
  context.argc = argc;
  context.argv = argv;
  context.modified_path = 0;
  context.iterator = 0;
  context.ignore = 0;
  context.iterator_error = 0;
  context.buffer = 0;
  context.current_input_path = 0;
  context.current_output_path = 0;
  context.fin = 0;
  context.fout = 0;
  command = ParseParams(&context);
  if (((command == COMMAND_COMPRESS) || (command == COMMAND_DECOMPRESS)) || (command == COMMAND_TEST_INTEGRITY))
  {
    if (is_ok)
    {
      size_t modified_path_len = (context.longest_path_len + strlen(context.suffix)) + 1;
      context.modified_path = (char *) malloc(modified_path_len);
      context.buffer = (uint8_t *) malloc(kFileBufferSize * 2);
      if ((!context.modified_path) || (!context.buffer))
      {
        fprintf(stderr, "out of memory\n");
        is_ok = 0;
      }
      else
      {
        context.input = context.buffer;
        context.output = context.buffer + kFileBufferSize;
      }
    }
  }
  if (!is_ok)
  {
    command = COMMAND_NOOP;
  }
  switch (command)
  {
    case COMMAND_NOOP:
    {
      break;
    }

    case COMMAND_VERSION:
    {
      PrintVersion();
      break;
    }

    case COMMAND_COMPRESS:
    {
      is_ok = CompressFiles(&context);
      break;
    }

    case COMMAND_DECOMPRESS:

    case COMMAND_TEST_INTEGRITY:
    {
      is_ok = DecompressFiles(&context);
      break;
    }

    case COMMAND_HELP:

    case COMMAND_INVALID:

    default:
    {
      is_ok = command == COMMAND_HELP;
      PrintHelp(FileName(argv[0]), is_ok);
      break;
    }

  }

  if (context.iterator_error)
  {
    is_ok = 0;
  }
  free(context.modified_path);
  free(context.buffer);
  if (!is_ok)
  {
    exit(1);
  }
  return 0;
}


/*** DEPENDENCIES:
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
static int DecompressFiles(Context *context)
{
  while (NextFile(context))
  {
    int is_ok = 1;
    BrotliDecoderState *s = BrotliDecoderCreateInstance(0, 0, 0);
    if (!s)
    {
      fprintf(stderr, "out of memory\n");
      return 0;
    }
    BrotliDecoderSetParameter(s, BROTLI_DECODER_PARAM_LARGE_WINDOW, 1u);
    is_ok = OpenFiles(context);
    if (((is_ok && (!context->current_input_path)) && (!context->force_overwrite)) && isatty(STDIN_FILENO))
    {
      fprintf(stderr, "Use -h help. Use -f to force input from a terminal.\n");
      is_ok = 0;
    }
    if (is_ok)
    {
      is_ok = DecompressFile(context, s);
    }
    BrotliDecoderDestroyInstance(s);
    if (!CloseFiles(context, is_ok))
    {
      is_ok = 0;
    }
    if (!is_ok)
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static int CompressFiles(Context *context)
{
  while (NextFile(context))
  {
    helper_CompressFiles_1(context);
  }

  return 1;
}


----------------------------
static void PrintHelp(const char *name, int error)
{
  FILE *media = (error) ? (stderr) : (stdout);
  fprintf(media, "Usage: %s [OPTION]... [FILE]...\n", name);
  fprintf(media, "Options:\n  -#                          compression level (0-9)\n  -c, --stdout                write on standard output\n  -d, --decompress            decompress\n  -f, --force                 force output file overwrite\n  -h, --help                  display this help and exit\n");
  fprintf(media, "  -j, --rm                    remove source file(s)\n  -k, --keep                  keep source file(s) (default)\n  -n, --no-copy-stat          do not copy source file(s) attributes\n  -o FILE, --output=FILE      output file (only if 1 input file)\n");
  fprintf(media, "  -q NUM, --quality=NUM       compression level (%d-%d)\n", 0, 11);
  fprintf(media, "  -t, --test                  test compressed file integrity\n  -v, --verbose               verbose mode\n");
  fprintf(media, "  -w NUM, --lgwin=NUM         set LZ77 window size (0, %d-%d)\n                              window size = 2**NUM - 16\n                              0 lets compressor choose the optimal value\n", 10, 24);
  fprintf(media, "  --large_window=NUM          use incompatible large-window brotli\n                              bitstream with window size (0, %d-%d)\n                              WARNING: this format is not compatible\n                              with brotli RFC 7932 and may not be\n                              decodable with regular brotli decoders\n", 10, 30);
  fprintf(media, "  -S SUF, --suffix=SUF        output file suffix (default:'%s')\n", ".br");
  fprintf(media, "  -V, --version               display version and exit\n  -Z, --best                  use best compression level (11) (default)\nSimple options could be coalesced, i.e. '-9kf' is equivalent to '-9 -k -f'.\nWith no FILE, or when FILE is -, read standard input.\nAll arguments after '--' are treated as files.\n");
}


----------------------------
static void PrintVersion(void)
{
  int major = 0x1000009 >> 24;
  int minor = (0x1000009 >> 12) & 0xFFF;
  int patch = 0x1000009 & 0xFFF;
  fprintf(stdout, "brotli %d.%d.%d\n", major, minor, patch);
}


----------------------------
static const size_t kFileBufferSize = 1 << 19
----------------------------
static const char *FileName(const char *path)
{
  unsigned int path_idx = 0;
  const char *separator_position = strrchr(path, '/');
  unsigned int separator_position_idx = 0;
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  separator_position_idx = strrchr(path, '\\');
  if (separator_position)
  {
    path_idx = (&separator_position[separator_position_idx]) + 1;
  }
  return path;
}


----------------------------
static Command ParseParams(Context *params)
{
  int argc = params->argc;
  char **argv = params->argv;
  int i;
  int next_option_index = 0;
  size_t input_count = 0;
  size_t longest_path_len = 1;
  int command_set = 0;
  int quality_set = 0;
  int output_set = 0;
  int keep_set = 0;
  int lgwin_set = 0;
  int suffix_set = 0;
  int after_dash_dash = 0;
  Command command = ParseAlias(argv[0]);
  for (i = 1; i < argc; i += 1)
  {
    helper_ParseParams_1(&next_option_index, &input_count, &longest_path_len, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &after_dash_dash, &command, params, argc, argv, i);
  }

  params->input_count = input_count;
  params->longest_path_len = longest_path_len;
  params->decompress = command == COMMAND_DECOMPRESS;
  params->test_integrity = command == COMMAND_TEST_INTEGRITY;
  if ((input_count > 1) && output_set)
  {
    return COMMAND_INVALID;
  }
  if (params->test_integrity)
  {
    if (params->output_path)
    {
      return COMMAND_INVALID;
    }
    if (params->write_to_stdout)
    {
      return COMMAND_INVALID;
    }
  }
  if (strchr(params->suffix, '/') || strchr(params->suffix, '\\'))
  {
    return COMMAND_INVALID;
  }
  return command;
}


----------------------------
***/


