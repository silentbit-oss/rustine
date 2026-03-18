#include <openaptx.h>
#include <openaptxenc.c>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

extern const int aptx_major;
extern const int aptx_minor;
extern const int aptx_patch;
struct aptx_context;
struct aptx_context *aptx_init(int hd);
void aptx_reset(struct aptx_context *ctx);
void aptx_finish(struct aptx_context *ctx);
size_t aptx_encode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written);
int aptx_encode_finish(struct aptx_context *ctx, unsigned char *output, size_t output_size, size_t *written);
size_t aptx_decode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written);
size_t aptx_decode_sync(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written, int *synced, size_t *dropped);
size_t aptx_decode_sync_finish(struct aptx_context *ctx);
static unsigned char input_buffer[((512 * 3) * 2) * 4];
static unsigned char output_buffer[512 * 6];
int main(int argc, char *argv[])
{
  int i;
  int hd;
  int ret;
  size_t length;
  size_t processed;
  size_t written;
  struct aptx_context *ctx;
  unsigned int ctx_idx = 0;
  hd = 0;
  for (i = 1; i < argc; i += 1)
  {
    helper_main_2(&hd, argv, i);
  }

  ctx_idx = aptx_init(hd);
  if (!(&ctx[ctx_idx]))
  {
    fprintf(stderr, "%s: Cannot initialize aptX encoder\n", argv[0]);
    return 1;
  }
  ret = 0;
  while (!feof(stdin))
  {
    helper_main_1(&ret, &length, &processed, argv, written, ctx);
  }

  if (aptx_encode_finish(ctx, output_buffer, sizeof(output_buffer), &written))
  {
    if (fwrite(output_buffer, 1, written, stdout) != written)
    {
      fprintf(stderr, "%s: aptX encoding failed to write encoded data\n", argv[0]);
      ret = 1;
    }
  }
  aptx_finish(ctx);
  return ret;
}


extern const int aptx_major;
extern const int aptx_minor;
extern const int aptx_patch;
struct aptx_context;
struct aptx_context *aptx_init(int hd);
void aptx_reset(struct aptx_context *ctx);
void aptx_finish(struct aptx_context *ctx);
size_t aptx_encode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written);
int aptx_encode_finish(struct aptx_context *ctx, unsigned char *output, size_t output_size, size_t *written);
size_t aptx_decode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written);
size_t aptx_decode_sync(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written, int *synced, size_t *dropped);
size_t aptx_decode_sync_finish(struct aptx_context *ctx);
static unsigned char input_buffer[((512 * 3) * 2) * 4];
static unsigned char output_buffer[512 * 6];
int main(int argc, char *argv[])
{
  int i;
  int hd;
  int ret;
  size_t length;
  size_t processed;
  size_t written;
  struct aptx_context *ctx;
  unsigned int ctx_idx = 0;
  hd = 0;
  for (i = 1; i < argc; i += 1)
  {
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
    {
      fprintf(stderr, "aptX encoder utility %d.%d.%d (using libopenaptx %d.%d.%d)\n", 0, 2, 1, aptx_major, aptx_minor, aptx_patch);
      fprintf(stderr, "\n");
      fprintf(stderr, "This utility encodes a raw 24 bit signed stereo\n");
      fprintf(stderr, "samples from stdin to aptX or aptX HD on stdout\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Usage:\n");
      fprintf(stderr, "        %s [options]\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "Options:\n");
      fprintf(stderr, "        -h, --help   Display this help\n");
      fprintf(stderr, "        --hd         Encode to aptX HD\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Examples:\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s < sample.s24le > sample.aptx\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s --hd < sample.s24le > sample.aptxhd\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | %s > sample.aptx\n", argv[0]);
      return 1;
    }
    else
      if (strcmp(argv[i], "--hd") == 0)
    {
      hd = 1;
    }
    else
    {
      fprintf(stderr, "%s: Invalid option %s\n", argv[0], argv[i]);
      return 1;
    }
  }

  ctx_idx = aptx_init(hd);
  if (!(&ctx[ctx_idx]))
  {
    fprintf(stderr, "%s: Cannot initialize aptX encoder\n", argv[0]);
    return 1;
  }
  ret = 0;
  while (!feof(stdin))
  {
    length = fread(input_buffer, 1, sizeof(input_buffer), stdin);
    if (ferror(stdin))
    {
      fprintf(stderr, "%s: aptX encoding failed to read input data\n", argv[0]);
      ret = 1;
    }
    if (length == 0)
    {
      break;
    }
    processed = aptx_encode(ctx, input_buffer, length, output_buffer, sizeof(output_buffer), &written);
    if (processed != length)
    {
      fprintf(stderr, "%s: aptX encoding stopped in the middle of the sample, dropped %lu byte%s\n", argv[0], (unsigned long) (length - processed), ((length - processed) != 1) ? ("s") : (""));
      ret = 1;
    }
    if (fwrite(output_buffer, 1, written, stdout) != written)
    {
      fprintf(stderr, "%s: aptX encoding failed to write encoded data\n", argv[0]);
      ret = 1;
      break;
    }
    if (processed != length)
    {
      break;
    }
  }

  if (aptx_encode_finish(ctx, output_buffer, sizeof(output_buffer), &written))
  {
    if (fwrite(output_buffer, 1, written, stdout) != written)
    {
      fprintf(stderr, "%s: aptX encoding failed to write encoded data\n", argv[0]);
      ret = 1;
    }
  }
  aptx_finish(ctx);
  return ret;
}

void helper_main_1(int * const ret_ref, size_t * const length_ref, size_t * const processed_ref, char *argv[], size_t written, struct aptx_context * const ctx)
{
  int ret = *ret_ref;
  size_t length = *length_ref;
  size_t processed = *processed_ref;
  length = fread(input_buffer, 1, sizeof(input_buffer), stdin);
  if (ferror(stdin))
  {
    fprintf(stderr, "%s: aptX encoding failed to read input data\n", argv[0]);
    ret = 1;
  }
  if (length == 0)
  {
    break;
  }
  processed = aptx_encode(ctx, input_buffer, length, output_buffer, sizeof(output_buffer), &written);
  if (processed != length)
  {
    fprintf(stderr, "%s: aptX encoding stopped in the middle of the sample, dropped %lu byte%s\n", argv[0], (unsigned long) (length - processed), ((length - processed) != 1) ? ("s") : (""));
    ret = 1;
  }
  if (fwrite(output_buffer, 1, written, stdout) != written)
  {
    fprintf(stderr, "%s: aptX encoding failed to write encoded data\n", argv[0]);
    ret = 1;
    break;
  }
  if (processed != length)
  {
    break;
  }
  *ret_ref = ret;
  *length_ref = length;
  *processed_ref = processed;
}

int helper_main_2(int * const hd_ref, char *argv[], int i)
{
  int hd = *hd_ref;
  if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
  {
    fprintf(stderr, "aptX encoder utility %d.%d.%d (using libopenaptx %d.%d.%d)\n", 0, 2, 1, aptx_major, aptx_minor, aptx_patch);
    fprintf(stderr, "\n");
    fprintf(stderr, "This utility encodes a raw 24 bit signed stereo\n");
    fprintf(stderr, "samples from stdin to aptX or aptX HD on stdout\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "        %s [options]\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "        -h, --help   Display this help\n");
    fprintf(stderr, "        --hd         Encode to aptX HD\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Examples:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "        %s < sample.s24le > sample.aptx\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "        %s --hd < sample.s24le > sample.aptxhd\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | %s > sample.aptx\n", argv[0]);
    return 1;
  }
  else
    if (strcmp(argv[i], "--hd") == 0)
  {
    hd = 1;
  }
  else
  {
    fprintf(stderr, "%s: Invalid option %s\n", argv[0], argv[i]);
    return 1;
  }
  *hd_ref = hd;
}

