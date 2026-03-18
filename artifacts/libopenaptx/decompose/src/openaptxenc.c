// hint:  ['hd_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
extern const int aptx_minor
----------------------------
extern const int aptx_patch
----------------------------
extern const int aptx_major
----------------------------
***/


// hint:  ['ret_ref is a mutable refrence to int', 'length_ref is a mutable refrence to size_t', 'processed_ref is a mutable refrence to size_t']
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


/*** DEPENDENCIES:
struct aptx_context
{
  size_t decode_sync_packets;
  size_t decode_dropped;
  struct aptx_channel channels[NB_CHANNELS];
  uint8_t hd;
  uint8_t sync_idx;
  uint8_t encode_remaining;
  uint8_t decode_skip_leading;
  uint8_t decode_sync_buffer_len;
  unsigned char decode_sync_buffer[6];
}
----------------------------
static unsigned char input_buffer[512 * 6]
----------------------------
static unsigned char output_buffer[(((512 * 3) * 2) * 6) + ((3 * 2) * 4)]
----------------------------
size_t aptx_encode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  int32_t samples[NB_CHANNELS][4];
  unsigned sample;
  unsigned channel;
  size_t ipos;
  size_t opos;
  for (ipos = 0, opos = 0; ((ipos + ((3 * NB_CHANNELS) * 4)) <= input_size) && ((opos + sample_size) <= output_size); opos += sample_size)
  {
    for (sample = 0; sample < 4; sample += 1)
    {
      for (channel = 0; channel < NB_CHANNELS; channel += 1, ipos += 3)
      {
        samples[channel][sample] = (int32_t) (((((uint32_t) input[ipos + 0]) << 0) | (((uint32_t) input[ipos + 1]) << 8)) | (((uint32_t) ((int8_t) input[ipos + 2])) << 16));
      }

    }

    aptx_encode_samples(ctx, samples, output + opos);
  }

  *written = opos;
  return ipos;
}


----------------------------
***/


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


/*** DEPENDENCIES:
struct aptx_context *aptx_init(int hd)
{
  struct aptx_context *ctx;
  unsigned int ctx_idx = 0;
  ctx_idx = (struct aptx_context *) malloc(sizeof(*ctx_idx));
  if (!(&ctx[ctx_idx]))
  {
    return 0;
  }
  ctx->hd = (hd) ? (1) : (0);
  aptx_reset(ctx);
  return ctx;
}


----------------------------
static unsigned char output_buffer[(((512 * 3) * 2) * 6) + ((3 * 2) * 4)]
----------------------------
int aptx_encode_finish(struct aptx_context *ctx, unsigned char *output, size_t output_size, size_t *written)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  int32_t samples[NB_CHANNELS][4] = {{0}};
  size_t opos;
  if (ctx->encode_remaining == 0)
  {
    *written = 0;
    return 1;
  }
  for (opos = 0; (ctx->encode_remaining > 0) && ((opos + sample_size) <= output_size); ctx->encode_remaining -= 1, opos += sample_size)
    aptx_encode_samples(ctx, samples, output + opos);

  *written = opos;
  if (ctx->encode_remaining > 0)
  {
    return 0;
  }
  aptx_reset(ctx);
  return 1;
}


----------------------------
struct aptx_context
{
  size_t decode_sync_packets;
  size_t decode_dropped;
  struct aptx_channel channels[NB_CHANNELS];
  uint8_t hd;
  uint8_t sync_idx;
  uint8_t encode_remaining;
  uint8_t decode_skip_leading;
  uint8_t decode_sync_buffer_len;
  unsigned char decode_sync_buffer[6];
}
----------------------------
void aptx_finish(struct aptx_context *ctx)
{
  free(ctx);
}


----------------------------
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


----------------------------
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


----------------------------
***/


