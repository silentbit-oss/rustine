#include <openaptx.h>
#include <openaptxdec.c>
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
static unsigned char input_buffer[512 * 6];
static unsigned char output_buffer[(((512 * 3) * 2) * 6) + ((3 * 2) * 4)];
int main(int argc, char *argv[])
{
  int i;
  int hd;
  int ret;
  size_t length;
  size_t processed;
  size_t written;
  size_t dropped;
  int synced;
  int syncing;
  struct aptx_context *ctx;
  unsigned int ctx_idx = 0;
  hd = 0;
  for (i = 1; i < argc; i += 1)
  {
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
    {
      fprintf(stderr, "aptX decoder utility %d.%d.%d (using libopenaptx %d.%d.%d)\n", 0, 2, 1, aptx_major, aptx_minor, aptx_patch);
      fprintf(stderr, "\n");
      fprintf(stderr, "This utility decodes aptX or aptX HD audio stream\n");
      fprintf(stderr, "from stdin to a raw 24 bit signed stereo on stdout\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "When input is damaged it tries to synchronize and recover\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Non-zero return value indicates that input was damaged\n");
      fprintf(stderr, "and some bytes from input aptX audio stream were dropped\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Usage:\n");
      fprintf(stderr, "        %s [options]\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "Options:\n");
      fprintf(stderr, "        -h, --help   Display this help\n");
      fprintf(stderr, "        --hd         Decode from aptX HD\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Examples:\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s < sample.aptx > sample.s24le\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s --hd < sample.aptxhd > sample.s24le\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -\n", argv[0]);
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
    fprintf(stderr, "%s: Cannot initialize aptX decoder\n", argv[0]);
    return 1;
  }
  length = fread(input_buffer, 1, 6, stdin);
  if ((length >= 4) && (memcmp(input_buffer, "\x4b\xbf\x4b\xbf", 4) == 0))
  {
    if (hd)
    {
      fprintf(stderr, "%s: Input looks like start of aptX audio stream (not aptX HD), try without --hd\n", argv[0]);
    }
  }
  else
    if ((length >= 6) && (memcmp(input_buffer, "\x73\xbe\xff\x73\xbe\xff", 6) == 0))
  {
    if (!hd)
    {
      fprintf(stderr, "%s: Input looks like start of aptX HD audio stream, try with --hd\n", argv[0]);
    }
  }
  else
  {
    if ((length >= 4) && (memcmp(input_buffer, "\x6b\xbf\x6b\xbf", 4) == 0))
    {
      fprintf(stderr, "%s: Input looks like start of standard aptX audio stream, which is not supported yet\n", argv[0]);
    }
    else
      fprintf(stderr, "%s: Input does not look like start of aptX nor aptX HD audio stream\n", argv[0]);
  }
  ret = 0;
  syncing = 0;
  while (length > 0)
  {
    processed = aptx_decode_sync(ctx, input_buffer, length, output_buffer, sizeof(output_buffer), &written, &synced, &dropped);
    if (!synced)
    {
      if (!syncing)
      {
        fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        syncing = 1;
        ret = 1;
      }
      if (dropped)
      {
        fprintf(stderr, "%s: aptX synchronization successful, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
        syncing = 0;
        ret = 1;
      }
      if (!syncing)
      {
        fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        syncing = 1;
        ret = 1;
      }
    }
    else
    {
      if (dropped)
      {
        if (!syncing)
        {
          fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        }
        fprintf(stderr, "%s: aptX synchronization successful, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
        syncing = 0;
        ret = 1;
      }
      else
        if (syncing)
      {
        fprintf(stderr, "%s: aptX synchronization successful\n", argv[0]);
        syncing = 0;
        ret = 1;
      }
    }
    if (processed != length)
    {
      fprintf(stderr, "%s: aptX decoding failed\n", argv[0]);
      ret = 1;
      break;
    }
    if (!feof(stdin))
    {
      length = fread(input_buffer, 1, sizeof(input_buffer), stdin);
      if (ferror(stdin))
      {
        fprintf(stderr, "%s: aptX decoding failed to read input data\n", argv[0]);
        ret = 1;
        length = 0;
      }
    }
    else
    {
      length = 0;
    }
    if (((length == 0) && (!ferror(stdin))) && (written >= (6 * 2)))
    {
      written -= 6 * 2;
    }
    if (written > 0)
    {
      if (fwrite(output_buffer, 1, written, stdout) != written)
      {
        fprintf(stderr, "%s: aptX decoding failed to write decoded data\n", argv[0]);
        ret = 1;
        break;
      }
    }
  }

  dropped = aptx_decode_sync_finish(ctx);
  if (dropped && (!syncing))
  {
    fprintf(stderr, "%s: aptX decoding stopped in the middle of the sample, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
    ret = 1;
  }
  else
    if (syncing)
  {
    fprintf(stderr, "%s: aptX synchronization failed\n", argv[0]);
    ret = 1;
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
static unsigned char input_buffer[512 * 6];
static unsigned char output_buffer[(((512 * 3) * 2) * 6) + ((3 * 2) * 4)];
int main(int argc, char *argv[])
{
  int i;
  int hd;
  int ret;
  size_t length;
  size_t processed;
  size_t written;
  size_t dropped;
  int synced;
  int syncing;
  struct aptx_context *ctx;
  unsigned int ctx_idx = 0;
  hd = 0;
  for (i = 1; i < argc; i += 1)
  {
    if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
    {
      fprintf(stderr, "aptX decoder utility %d.%d.%d (using libopenaptx %d.%d.%d)\n", 0, 2, 1, aptx_major, aptx_minor, aptx_patch);
      fprintf(stderr, "\n");
      fprintf(stderr, "This utility decodes aptX or aptX HD audio stream\n");
      fprintf(stderr, "from stdin to a raw 24 bit signed stereo on stdout\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "When input is damaged it tries to synchronize and recover\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Non-zero return value indicates that input was damaged\n");
      fprintf(stderr, "and some bytes from input aptX audio stream were dropped\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Usage:\n");
      fprintf(stderr, "        %s [options]\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "Options:\n");
      fprintf(stderr, "        -h, --help   Display this help\n");
      fprintf(stderr, "        --hd         Decode from aptX HD\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Examples:\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s < sample.aptx > sample.s24le\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s --hd < sample.aptxhd > sample.s24le\n", argv[0]);
      fprintf(stderr, "\n");
      fprintf(stderr, "        %s < sample.aptx | play -t raw -r 44.1k -L -e s -b 24 -c 2 -\n", argv[0]);
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
    fprintf(stderr, "%s: Cannot initialize aptX decoder\n", argv[0]);
    return 1;
  }
  length = fread(input_buffer, 1, 6, stdin);
  if ((length >= 4) && (memcmp(input_buffer, "\x4b\xbf\x4b\xbf", 4) == 0))
  {
    if (hd)
    {
      fprintf(stderr, "%s: Input looks like start of aptX audio stream (not aptX HD), try without --hd\n", argv[0]);
    }
  }
  else
    if ((length >= 6) && (memcmp(input_buffer, "\x73\xbe\xff\x73\xbe\xff", 6) == 0))
  {
    if (!hd)
    {
      fprintf(stderr, "%s: Input looks like start of aptX HD audio stream, try with --hd\n", argv[0]);
    }
  }
  else
  {
    if ((length >= 4) && (memcmp(input_buffer, "\x6b\xbf\x6b\xbf", 4) == 0))
    {
      fprintf(stderr, "%s: Input looks like start of standard aptX audio stream, which is not supported yet\n", argv[0]);
    }
    else
      fprintf(stderr, "%s: Input does not look like start of aptX nor aptX HD audio stream\n", argv[0]);
  }
  ret = 0;
  syncing = 0;
  while (length > 0)
  {
    processed = aptx_decode_sync(ctx, input_buffer, length, output_buffer, sizeof(output_buffer), &written, &synced, &dropped);
    if (!synced)
    {
      if (!syncing)
      {
        fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        syncing = 1;
        ret = 1;
      }
      if (dropped)
      {
        fprintf(stderr, "%s: aptX synchronization successful, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
        syncing = 0;
        ret = 1;
      }
      if (!syncing)
      {
        fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        syncing = 1;
        ret = 1;
      }
    }
    else
    {
      if (dropped)
      {
        if (!syncing)
        {
          fprintf(stderr, "%s: aptX decoding failed, synchronizing\n", argv[0]);
        }
        fprintf(stderr, "%s: aptX synchronization successful, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
        syncing = 0;
        ret = 1;
      }
      else
        if (syncing)
      {
        fprintf(stderr, "%s: aptX synchronization successful\n", argv[0]);
        syncing = 0;
        ret = 1;
      }
    }
    if (processed != length)
    {
      fprintf(stderr, "%s: aptX decoding failed\n", argv[0]);
      ret = 1;
      break;
    }
    if (!feof(stdin))
    {
      length = fread(input_buffer, 1, sizeof(input_buffer), stdin);
      if (ferror(stdin))
      {
        fprintf(stderr, "%s: aptX decoding failed to read input data\n", argv[0]);
        ret = 1;
        length = 0;
      }
    }
    else
    {
      length = 0;
    }
    if (((length == 0) && (!ferror(stdin))) && (written >= (6 * 2)))
    {
      written -= 6 * 2;
    }
    if (written > 0)
    {
      if (fwrite(output_buffer, 1, written, stdout) != written)
      {
        fprintf(stderr, "%s: aptX decoding failed to write decoded data\n", argv[0]);
        ret = 1;
        break;
      }
    }
  }

  dropped = aptx_decode_sync_finish(ctx);
  if (dropped && (!syncing))
  {
    fprintf(stderr, "%s: aptX decoding stopped in the middle of the sample, dropped %lu byte%s\n", argv[0], (unsigned long) dropped, (dropped != 1) ? ("s") : (""));
    ret = 1;
  }
  else
    if (syncing)
  {
    fprintf(stderr, "%s: aptX synchronization failed\n", argv[0]);
    ret = 1;
  }
  aptx_finish(ctx);
  return ret;
}

