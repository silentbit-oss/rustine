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


/*** DEPENDENCIES:
extern const int aptx_minor
----------------------------
static unsigned char output_buffer[(((512 * 3) * 2) * 6) + ((3 * 2) * 4)]
----------------------------
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
static unsigned char input_buffer[512 * 6]
----------------------------
size_t aptx_decode_sync_finish(struct aptx_context *ctx)
{
  const uint8_t dropped = ctx->decode_sync_buffer_len;
  aptx_reset(ctx);
  return dropped;
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
extern const int aptx_patch
----------------------------
extern const int aptx_major
----------------------------
size_t aptx_decode_sync(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written, int *synced, size_t *dropped)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  size_t input_size_step;
  size_t processed_step;
  size_t written_step;
  size_t ipos = 0;
  size_t opos = 0;
  size_t i;
  *synced = 0;
  *dropped = 0;
  if ((ctx->decode_sync_buffer_len > 0) && (((sample_size - 1) - ctx->decode_sync_buffer_len) <= input_size))
  {
    while (ctx->decode_sync_buffer_len < (sample_size - 1))
      ctx->decode_sync_buffer[ctx->decode_sync_buffer_len++] = input[ipos];

    ipos += 1;
  }
  while ((((ctx->decode_sync_buffer_len == (sample_size - 1)) && (ipos < sample_size)) && (ipos < input_size)) && ((((opos + ((3 * NB_CHANNELS) * 4)) <= output_size) || (ctx->decode_skip_leading > 0)) || (ctx->decode_dropped > 0)))
  {
    helper_aptx_decode_sync_1(&sample_size, &processed_step, &ipos, &opos, &i, ctx, input, output, output_size, synced, dropped, written_step);
  }

  if ((ctx->decode_sync_buffer_len == (sample_size - 1)) && (ipos == sample_size))
  {
    ipos = 0;
    ctx->decode_sync_buffer_len = 0;
  }
  while (((ipos + sample_size) <= input_size) && ((((opos + ((3 * NB_CHANNELS) * 4)) <= output_size) || (ctx->decode_skip_leading > 0)) || (ctx->decode_dropped > 0)))
  {
    helper_aptx_decode_sync_2(&input_size_step, &processed_step, &ipos, &opos, ctx, input, input_size, output, output_size, synced, dropped, sample_size, written_step);
  }

  if ((ipos + sample_size) > input_size)
  {
    while (ipos < input_size)
      ctx->decode_sync_buffer[ctx->decode_sync_buffer_len++] = input[ipos];

    ipos += 1;
  }
  *written = opos;
  return ipos;
}


----------------------------
***/


