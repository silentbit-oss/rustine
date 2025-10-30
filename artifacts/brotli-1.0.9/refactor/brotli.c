#include <brotli.c>
#include <constants.h>
#include <decode.h>
#include <encode.h>
#include <errno.h>
#include <fcntl.h>
#include <platform.h>
#include <port.h>
#include <stat.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <types.h>
#include <unistd.h>
#include <utime.h>
#include <version.h>

typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
typedef struct BrotliDecoderStateStruct BrotliDecoderState;
typedef enum 
{
  BROTLI_DECODER_RESULT_ERROR = 0,
  BROTLI_DECODER_RESULT_SUCCESS = 1,
  BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT = 2,
  BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT = 3
} BrotliDecoderResult;
typedef enum 
{
  BROTLI_DECODER_NO_ERROR = 0,
  BROTLI_DECODER_SUCCESS = 1,
  BROTLI_DECODER_NEEDS_MORE_INPUT = 2,
  BROTLI_DECODER_NEEDS_MORE_OUTPUT = 3,
  BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE = -1,
  BROTLI_DECODER_ERROR_FORMAT_RESERVED = -2,
  BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE = -3,
  BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET = -4,
  BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME = -5,
  BROTLI_DECODER_ERROR_FORMAT_CL_SPACE = -6,
  BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE = -7,
  BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT = -8,
  BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1 = -9,
  BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2 = -10,
  BROTLI_DECODER_ERROR_FORMAT_TRANSFORM = -11,
  BROTLI_DECODER_ERROR_FORMAT_DICTIONARY = -12,
  BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS = -13,
  BROTLI_DECODER_ERROR_FORMAT_PADDING_1 = -14,
  BROTLI_DECODER_ERROR_FORMAT_PADDING_2 = -15,
  BROTLI_DECODER_ERROR_FORMAT_DISTANCE = -16,
  BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET = -19,
  BROTLI_DECODER_ERROR_INVALID_ARGUMENTS = -20,
  BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES = -21,
  BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS = -22,
  BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP = -25,
  BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1 = -26,
  BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2 = -27,
  BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES = -30,
  BROTLI_DECODER_ERROR_UNREACHABLE = -31
} BrotliDecoderErrorCode;
typedef enum BrotliDecoderParameter
{
  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION = 0,
  BROTLI_DECODER_PARAM_LARGE_WINDOW = 1
} BrotliDecoderParameter;
int BrotliDecoderSetParameter(BrotliDecoderState *state, BrotliDecoderParameter param, uint32_t value);
BrotliDecoderState *BrotliDecoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque);
void BrotliDecoderDestroyInstance(BrotliDecoderState *state);
BrotliDecoderResult BrotliDecoderDecompress(size_t encoded_size, const uint8_t encoded_buffer[encoded_size], size_t *decoded_size, uint8_t decoded_buffer[*decoded_size]);
BrotliDecoderResult BrotliDecoderDecompressStream(BrotliDecoderState *state, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out);
int BrotliDecoderHasMoreOutput(const BrotliDecoderState *state);
const uint8_t *BrotliDecoderTakeOutput(BrotliDecoderState *state, size_t *size);
int BrotliDecoderIsUsed(const BrotliDecoderState *state);
int BrotliDecoderIsFinished(const BrotliDecoderState *state);
BrotliDecoderErrorCode BrotliDecoderGetErrorCode(const BrotliDecoderState *state);
const char *BrotliDecoderErrorString(BrotliDecoderErrorCode c);
uint32_t BrotliDecoderVersion(void);
typedef enum BrotliEncoderMode
{
  BROTLI_MODE_GENERIC = 0,
  BROTLI_MODE_TEXT = 1,
  BROTLI_MODE_FONT = 2
} BrotliEncoderMode;
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation;
typedef enum BrotliEncoderParameter
{
  BROTLI_PARAM_MODE = 0,
  BROTLI_PARAM_QUALITY = 1,
  BROTLI_PARAM_LGWIN = 2,
  BROTLI_PARAM_LGBLOCK = 3,
  BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING = 4,
  BROTLI_PARAM_SIZE_HINT = 5,
  BROTLI_PARAM_LARGE_WINDOW = 6,
  BROTLI_PARAM_NPOSTFIX = 7,
  BROTLI_PARAM_NDIRECT = 8,
  BROTLI_PARAM_STREAM_OFFSET = 9
} BrotliEncoderParameter;
typedef struct BrotliEncoderStateStruct BrotliEncoderState;
int BrotliEncoderSetParameter(BrotliEncoderState *state, BrotliEncoderParameter param, uint32_t value);
BrotliEncoderState *BrotliEncoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque);
void BrotliEncoderDestroyInstance(BrotliEncoderState *state);
size_t BrotliEncoderMaxCompressedSize(size_t input_size);
int BrotliEncoderCompress(int quality, int lgwin, BrotliEncoderMode mode, size_t input_size, const uint8_t input_buffer[input_size], size_t *encoded_size, uint8_t encoded_buffer[*encoded_size]);
int BrotliEncoderCompressStream(BrotliEncoderState *state, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out);
int BrotliEncoderIsFinished(BrotliEncoderState *state);
int BrotliEncoderHasMoreOutput(BrotliEncoderState *state);
const uint8_t *BrotliEncoderTakeOutput(BrotliEncoderState *state, size_t *size);
uint32_t BrotliEncoderVersion(void);
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command;
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
} Context;
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
    helper_ParseParams_1(&i, &next_option_index, &input_count, &longest_path_len, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &after_dash_dash, &command, params, argc, argv);
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

static void PrintVersion(void)
{
  int major = 0x1000009 >> 24;
  int minor = (0x1000009 >> 12) & 0xFFF;
  int patch = 0x1000009 & 0xFFF;
  fprintf(stdout, "brotli %d.%d.%d\n", major, minor, patch);
}

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

static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}

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

static int OpenFiles(Context *context)
{
  int is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if ((!context->test_integrity) && is_ok)
  {
    is_ok = OpenOutputFile(context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}

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

static const size_t kFileBufferSize = 1 << 19;
static void InitializeBuffers(Context *context)
{
  context->available_in = 0;
  context->next_in = 0;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}

static int HasMoreInput(Context *context)
{
  return (feof(context->fin)) ? (0) : (1);
}

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

static int FlushOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = 0;
  return 1;
}

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

static void PrintFileProcessingProgress(Context *context)
{
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}

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

static int CompressFiles(Context *context)
{
  while (NextFile(context))
  {
    helper_CompressFiles_1(context);
  }

  return 1;
}

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
  {
    context.not_input_indices[i] = 0;
  }

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


typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
typedef struct BrotliDecoderStateStruct BrotliDecoderState;
typedef enum 
{
  BROTLI_DECODER_RESULT_ERROR = 0,
  BROTLI_DECODER_RESULT_SUCCESS = 1,
  BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT = 2,
  BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT = 3
} BrotliDecoderResult;
typedef enum 
{
  BROTLI_DECODER_NO_ERROR = 0,
  BROTLI_DECODER_SUCCESS = 1,
  BROTLI_DECODER_NEEDS_MORE_INPUT = 2,
  BROTLI_DECODER_NEEDS_MORE_OUTPUT = 3,
  BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE = -1,
  BROTLI_DECODER_ERROR_FORMAT_RESERVED = -2,
  BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE = -3,
  BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET = -4,
  BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME = -5,
  BROTLI_DECODER_ERROR_FORMAT_CL_SPACE = -6,
  BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE = -7,
  BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT = -8,
  BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1 = -9,
  BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2 = -10,
  BROTLI_DECODER_ERROR_FORMAT_TRANSFORM = -11,
  BROTLI_DECODER_ERROR_FORMAT_DICTIONARY = -12,
  BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS = -13,
  BROTLI_DECODER_ERROR_FORMAT_PADDING_1 = -14,
  BROTLI_DECODER_ERROR_FORMAT_PADDING_2 = -15,
  BROTLI_DECODER_ERROR_FORMAT_DISTANCE = -16,
  BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET = -19,
  BROTLI_DECODER_ERROR_INVALID_ARGUMENTS = -20,
  BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES = -21,
  BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS = -22,
  BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP = -25,
  BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1 = -26,
  BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2 = -27,
  BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES = -30,
  BROTLI_DECODER_ERROR_UNREACHABLE = -31
} BrotliDecoderErrorCode;
typedef enum BrotliDecoderParameter
{
  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION = 0,
  BROTLI_DECODER_PARAM_LARGE_WINDOW = 1
} BrotliDecoderParameter;
int BrotliDecoderSetParameter(BrotliDecoderState *state, BrotliDecoderParameter param, uint32_t value);
BrotliDecoderState *BrotliDecoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque);
void BrotliDecoderDestroyInstance(BrotliDecoderState *state);
BrotliDecoderResult BrotliDecoderDecompress(size_t encoded_size, const uint8_t encoded_buffer[encoded_size], size_t *decoded_size, uint8_t decoded_buffer[*decoded_size]);
BrotliDecoderResult BrotliDecoderDecompressStream(BrotliDecoderState *state, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out);
int BrotliDecoderHasMoreOutput(const BrotliDecoderState *state);
const uint8_t *BrotliDecoderTakeOutput(BrotliDecoderState *state, size_t *size);
int BrotliDecoderIsUsed(const BrotliDecoderState *state);
int BrotliDecoderIsFinished(const BrotliDecoderState *state);
BrotliDecoderErrorCode BrotliDecoderGetErrorCode(const BrotliDecoderState *state);
const char *BrotliDecoderErrorString(BrotliDecoderErrorCode c);
uint32_t BrotliDecoderVersion(void);
typedef enum BrotliEncoderMode
{
  BROTLI_MODE_GENERIC = 0,
  BROTLI_MODE_TEXT = 1,
  BROTLI_MODE_FONT = 2
} BrotliEncoderMode;
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation;
typedef enum BrotliEncoderParameter
{
  BROTLI_PARAM_MODE = 0,
  BROTLI_PARAM_QUALITY = 1,
  BROTLI_PARAM_LGWIN = 2,
  BROTLI_PARAM_LGBLOCK = 3,
  BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING = 4,
  BROTLI_PARAM_SIZE_HINT = 5,
  BROTLI_PARAM_LARGE_WINDOW = 6,
  BROTLI_PARAM_NPOSTFIX = 7,
  BROTLI_PARAM_NDIRECT = 8,
  BROTLI_PARAM_STREAM_OFFSET = 9
} BrotliEncoderParameter;
typedef struct BrotliEncoderStateStruct BrotliEncoderState;
int BrotliEncoderSetParameter(BrotliEncoderState *state, BrotliEncoderParameter param, uint32_t value);
BrotliEncoderState *BrotliEncoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque);
void BrotliEncoderDestroyInstance(BrotliEncoderState *state);
size_t BrotliEncoderMaxCompressedSize(size_t input_size);
int BrotliEncoderCompress(int quality, int lgwin, BrotliEncoderMode mode, size_t input_size, const uint8_t input_buffer[input_size], size_t *encoded_size, uint8_t encoded_buffer[*encoded_size]);
int BrotliEncoderCompressStream(BrotliEncoderState *state, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out);
int BrotliEncoderIsFinished(BrotliEncoderState *state);
int BrotliEncoderHasMoreOutput(BrotliEncoderState *state);
const uint8_t *BrotliEncoderTakeOutput(BrotliEncoderState *state, size_t *size);
uint32_t BrotliEncoderVersion(void);
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command;
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
} Context;
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
      size_t j;
      for (j = 1; j < arg_len; j += 1)
      {
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
        i += 1;
        if (((i == argc) || (!argv[i])) || (argv[i][0] == 0))
        {
          fprintf(stderr, "expected parameter for argument -%c\n", c);
          return COMMAND_INVALID;
        }
        params->not_input_indices[next_option_index] = i;
        next_option_index += 1;
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
      }

    }
    else
    {
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
        const char *value = strrchr(arg, '=');
        unsigned int value_idx = 0;
        size_t key_len;
        if ((!(&value[value_idx])) || (value[1 + value_idx] == 0))
        {
          fprintf(stderr, "must pass the parameter as --%s=value\n", arg);
          return COMMAND_INVALID;
        }
        key_len = (size_t) ((&value[value_idx]) - (&arg[arg_idx]));
        value_idx += 1;
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
          params->output_path = &value[value_idx];
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
          params->suffix = &value[value_idx];
        }
        else
        {
          fprintf(stderr, "invalid parameter: [%s]\n", arg);
          return COMMAND_INVALID;
        }
      }
    }
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

static void PrintVersion(void)
{
  int major = 0x1000009 >> 24;
  int minor = (0x1000009 >> 12) & 0xFFF;
  int patch = 0x1000009 & 0xFFF;
  fprintf(stdout, "brotli %d.%d.%d\n", major, minor, patch);
}

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

static const char *PrintablePath(const char *path)
{
  return (path) ? (path) : ("con");
}

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
  else
  {
    strcpy(context->modified_path + arg_len, context->suffix);
    return 1;
  }
}

static int OpenFiles(Context *context)
{
  int is_ok = OpenInputFile(context->current_input_path, &context->fin);
  if ((!context->test_integrity) && is_ok)
  {
    is_ok = OpenOutputFile(context->current_output_path, &context->fout, context->force_overwrite);
  }
  return is_ok;
}

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

static const size_t kFileBufferSize = 1 << 19;
static void InitializeBuffers(Context *context)
{
  context->available_in = 0;
  context->next_in = 0;
  context->available_out = kFileBufferSize;
  context->next_out = context->output;
  context->total_in = 0;
  context->total_out = 0;
}

static int HasMoreInput(Context *context)
{
  return (feof(context->fin)) ? (0) : (1);
}

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

static int FlushOutput(Context *context)
{
  if (!WriteOutput(context))
  {
    return 0;
  }
  context->available_out = 0;
  return 1;
}

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

static void PrintFileProcessingProgress(Context *context)
{
  fprintf(stderr, "[%s]: ", PrintablePath(context->current_input_path));
  PrintBytes(context->total_in);
  fprintf(stderr, " -> ");
  PrintBytes(context->total_out);
}

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

static int CompressFiles(Context *context)
{
  while (NextFile(context))
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

  return 1;
}

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
  {
    context.not_input_indices[i] = 0;
  }

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
      break;

    case COMMAND_VERSION:
      PrintVersion();
      break;

    case COMMAND_COMPRESS:
      is_ok = CompressFiles(&context);
      break;

    case COMMAND_DECOMPRESS:

    case COMMAND_TEST_INTEGRITY:
      is_ok = DecompressFiles(&context);
      break;

    case COMMAND_HELP:

    case COMMAND_INVALID:

    default:
      is_ok = command == COMMAND_HELP;
      PrintHelp(FileName(argv[0]), is_ok);
      break;

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

Command helper_ParseParams_1(int * const i_ref, int * const next_option_index_ref, size_t * const input_count_ref, size_t * const longest_path_len_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, int * const after_dash_dash_ref, Command * const command_ref, Context * const params, int argc, char ** const argv)
{
  int i = *i_ref;
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
    helper_helper_ParseParams_1_2(&i, &next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, arg, arg_idx, arg_len);
  }
  else
  {
    helper_helper_ParseParams_1_1(&command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, &arg_idx, params, arg);
  }
  *i_ref = i;
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

Command helper_helper_ParseParams_1_2(int * const i_ref, int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, const char * const arg, unsigned int arg_idx, size_t arg_len)
{
  int i = *i_ref;
  int next_option_index = *next_option_index_ref;
  int command_set = *command_set_ref;
  int quality_set = *quality_set_ref;
  int output_set = *output_set_ref;
  int keep_set = *keep_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  Command command = *command_ref;
  size_t j;
  for (j = 1; j < arg_len; j += 1)
  {
    helper_helper_helper_ParseParams_1_2_1(&i, &next_option_index, &command_set, &quality_set, &output_set, &keep_set, &lgwin_set, &suffix_set, &command, params, argc, argv, arg, arg_idx, arg_len, j);
  }

  *i_ref = i;
  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}

Command helper_helper_helper_ParseParams_1_1_1(int * const quality_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Context * const params, const char * const arg, int output_set, unsigned int arg_idx)
{
  int quality_set = *quality_set_ref;
  int lgwin_set = *lgwin_set_ref;
  int suffix_set = *suffix_set_ref;
  const char *value = strrchr(arg, '=');
  unsigned int value_idx = 0;
  size_t key_len;
  if ((!(&value[value_idx])) || (value[1 + value_idx] == 0))
  {
    fprintf(stderr, "must pass the parameter as --%s=value\n", arg);
    return COMMAND_INVALID;
  }
  key_len = (size_t) ((&value[value_idx]) - (&arg[arg_idx]));
  value_idx += 1;
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
    params->output_path = &value[value_idx];
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
    params->suffix = &value[value_idx];
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

Command helper_helper_helper_ParseParams_1_2_1(int * const i_ref, int * const next_option_index_ref, int * const command_set_ref, int * const quality_set_ref, int * const output_set_ref, int * const keep_set_ref, int * const lgwin_set_ref, int * const suffix_set_ref, Command * const command_ref, Context * const params, int argc, char ** const argv, const char * const arg, unsigned int arg_idx, size_t arg_len, size_t j)
{
  int i = *i_ref;
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
  i += 1;
  if (((i == argc) || (!argv[i])) || (argv[i][0] == 0))
  {
    fprintf(stderr, "expected parameter for argument -%c\n", c);
    return COMMAND_INVALID;
  }
  params->not_input_indices[next_option_index] = i;
  next_option_index += 1;
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
  *i_ref = i;
  *next_option_index_ref = next_option_index;
  *command_set_ref = command_set;
  *quality_set_ref = quality_set;
  *output_set_ref = output_set;
  *keep_set_ref = keep_set;
  *lgwin_set_ref = lgwin_set;
  *suffix_set_ref = suffix_set;
  *command_ref = command;
}

