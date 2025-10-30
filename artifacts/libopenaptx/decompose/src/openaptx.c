inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


/*** DEPENDENCIES:
***/


inline static int32_t clip(int32_t a, int32_t amin, int32_t amax)
{
  if (a < amin)
  {
    return amin;
  }
  else
    if (a > amax)
  {
    return amax;
  }
  else
    return a;
}


/*** DEPENDENCIES:
***/


inline static int32_t sign_extend(int32_t val, unsigned bits)
{
  const unsigned shift = (8 * (sizeof(val))) - bits;
  union 
  {
    uint32_t u;
    int32_t s;
  } v;
  v.u = ((uint32_t) val) << shift;
  return v.s >> shift;
}


/*** DEPENDENCIES:
***/


inline static int32_t rshift32(int32_t value, unsigned shift)
{
  const int32_t rounding = ((int32_t) 1) << (shift - 1);
  const int32_t mask = (((int32_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


/*** DEPENDENCIES:
***/


inline static int64_t rshift64(int64_t value, unsigned shift)
{
  const int64_t rounding = ((int64_t) 1) << (shift - 1);
  const int64_t mask = (((int64_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


/*** DEPENDENCIES:
***/


inline static int32_t aptx_bin_search(int32_t value, int32_t factor, const int32_t *intervals, int nb_intervals)
{
  int32_t idx = 0;
  int i;
  for (i = nb_intervals >> 1; i > 0; i >>= 1)
    if ((((int64_t) factor) * ((int64_t) intervals[idx + i])) <= (((int64_t) value) << 24))
  {
    idx += i;
  }

  return idx;
}


/*** DEPENDENCIES:
***/


void aptx_finish(struct aptx_context *ctx)
{
  free(ctx);
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
***/


inline static void aptx_update_codeword_history(struct aptx_channel *channel)
{
  const int32_t cw = (((channel->quantize[0].quantized_sample & 3) << 0) + ((channel->quantize[1].quantized_sample & 2) << 1)) + ((channel->quantize[2].quantized_sample & 1) << 3);
  channel->codeword_history = (cw << 8) + ((int32_t) (((uint32_t) channel->codeword_history) << 4));
}


/*** DEPENDENCIES:
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


inline static void aptx_qmf_filter_signal_push(struct aptx_filter_signal *signal, int32_t sample)
{
  signal->buffer[signal->pos] = sample;
  signal->buffer[signal->pos + 16] = sample;
  signal->pos = (signal->pos + 1) & (16 - 1);
}


/*** DEPENDENCIES:
struct aptx_filter_signal
{
  int32_t buffer[2 * 16];
  uint8_t pos;
}
----------------------------
***/


static int32_t *aptx_reconstructed_differences_update(struct aptx_prediction *prediction, int32_t reconstructed_difference, int order)
{
  int32_t *rd1 = prediction->reconstructed_differences;
  int32_t *rd2 = rd1 + order;
  int p = prediction->pos;
  rd1[p] = rd2[p];
  prediction->pos = (p = (p + 1) % order);
  rd2[p] = reconstructed_difference;
  return &rd2[p];
}


/*** DEPENDENCIES:
struct aptx_prediction
{
  int32_t prev_sign[2];
  int32_t s_weight[2];
  int32_t d_weight[24];
  int32_t pos;
  int32_t reconstructed_differences[48];
  int32_t previous_reconstructed_sample;
  int32_t predicted_difference;
  int32_t predicted_sample;
}
----------------------------
***/


static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


/*** DEPENDENCIES:
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


void aptx_reset(struct aptx_context *ctx)
{
  const uint8_t hd = ctx->hd;
  unsigned i;
  unsigned chan;
  unsigned subband;
  struct aptx_channel *channel;
  unsigned int channel_idx = 0;
  struct aptx_prediction *prediction;
  unsigned int prediction_idx = 0;
  for (i = 0; i < (sizeof(*ctx)); i += 1)
    ((unsigned char *) ctx)[i] = 0;

  ctx->hd = hd;
  ctx->decode_skip_leading = (90 + 3) / 4;
  ctx->encode_remaining = (90 + 3) / 4;
  for (chan = 0; chan < NB_CHANNELS; chan += 1)
  {
    channel_idx = &ctx->channels[chan];
    for (subband = 0; subband < 4; subband += 1)
    {
      prediction_idx = &channel->prediction_idx[subband];
      prediction->prev_sign[0] = 1;
      prediction->prev_sign[1] = 1;
    }

  }

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
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
struct aptx_prediction
{
  int32_t prev_sign[2];
  int32_t s_weight[2];
  int32_t d_weight[24];
  int32_t pos;
  int32_t reconstructed_differences[48];
  int32_t previous_reconstructed_sample;
  int32_t predicted_difference;
  int32_t predicted_sample;
}
----------------------------
***/


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


/*** DEPENDENCIES:
void aptx_reset(struct aptx_context *ctx)
{
  const uint8_t hd = ctx->hd;
  unsigned i;
  unsigned chan;
  unsigned subband;
  struct aptx_channel *channel;
  unsigned int channel_idx = 0;
  struct aptx_prediction *prediction;
  unsigned int prediction_idx = 0;
  for (i = 0; i < (sizeof(*ctx)); i += 1)
    ((unsigned char *) ctx)[i] = 0;

  ctx->hd = hd;
  ctx->decode_skip_leading = (90 + 3) / 4;
  ctx->encode_remaining = (90 + 3) / 4;
  for (chan = 0; chan < NB_CHANNELS; chan += 1)
  {
    channel_idx = &ctx->channels[chan];
    for (subband = 0; subband < 4; subband += 1)
    {
      prediction_idx = &channel->prediction_idx[subband];
      prediction->prev_sign[0] = 1;
      prediction->prev_sign[1] = 1;
    }

  }

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
***/


static void aptx_prediction_filtering(struct aptx_prediction *prediction, int32_t reconstructed_difference, int order)
{
  int32_t reconstructed_sample;
  int32_t predictor;
  int32_t srd0;
  int32_t srd;
  int32_t *reconstructed_differences;
  unsigned int reconstructed_differences_idx = 0;
  int64_t predicted_difference = 0;
  int i;
  reconstructed_sample = clip_intp2(reconstructed_difference + prediction->predicted_sample, 23);
  predictor = clip_intp2((int32_t) (((((int64_t) prediction->s_weight[0]) * ((int64_t) prediction->previous_reconstructed_sample)) + (((int64_t) prediction->s_weight[1]) * ((int64_t) reconstructed_sample))) >> 22), 23);
  prediction->previous_reconstructed_sample = reconstructed_sample;
  reconstructed_differences_idx = aptx_reconstructed_differences_update(prediction, reconstructed_difference, order);
  srd0 = ((int32_t) ((reconstructed_difference > 0) - (reconstructed_difference < 0))) * (((int32_t) 1) << 23);
  for (i = 0; i < order; i += 1)
  {
    srd = (reconstructed_differences[((-i) - 1) + reconstructed_differences_idx] >> 31) | 1;
    prediction->d_weight[i] -= rshift32(prediction->d_weight[i] - (srd * srd0), 8);
    predicted_difference += ((int64_t) reconstructed_differences[(-i) + reconstructed_differences_idx]) * ((int64_t) prediction->d_weight[i]);
  }

  prediction->predicted_difference = clip_intp2((int32_t) (predicted_difference >> 22), 23);
  prediction->predicted_sample = clip_intp2(predictor + prediction->predicted_difference, 23);
}


/*** DEPENDENCIES:
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
struct aptx_prediction
{
  int32_t prev_sign[2];
  int32_t s_weight[2];
  int32_t d_weight[24];
  int32_t pos;
  int32_t reconstructed_differences[48];
  int32_t previous_reconstructed_sample;
  int32_t predicted_difference;
  int32_t predicted_sample;
}
----------------------------
static int32_t *aptx_reconstructed_differences_update(struct aptx_prediction *prediction, int32_t reconstructed_difference, int order)
{
  int32_t *rd1 = prediction->reconstructed_differences;
  int32_t *rd2 = rd1 + order;
  int p = prediction->pos;
  rd1[p] = rd2[p];
  prediction->pos = (p = (p + 1) % order);
  rd2[p] = reconstructed_difference;
  return &rd2[p];
}


----------------------------
inline static int32_t rshift32(int32_t value, unsigned shift)
{
  const int32_t rounding = ((int32_t) 1) << (shift - 1);
  const int32_t mask = (((int32_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
***/


inline static int32_t rshift64_clip24(int64_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift64(value, shift), 23);
}


/*** DEPENDENCIES:
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
inline static int64_t rshift64(int64_t value, unsigned shift)
{
  const int64_t rounding = ((int64_t) 1) << (shift - 1);
  const int64_t mask = (((int64_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
***/


static void aptx_invert_quantization(struct aptx_invert_quantize *invert_quantize, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables)
{
  int32_t qr;
  int32_t idx;
  int32_t shift;
  int32_t factor_select;
  idx = (quantized_sample ^ (-(quantized_sample < 0))) + 1;
  qr = tables->quantize_intervals[idx] / 2;
  if (quantized_sample < 0)
  {
    qr = -qr;
  }
  qr = rshift64_clip24((((int64_t) qr) * (((int64_t) 1) << 32)) + (((int64_t) dither) * ((int64_t) tables->invert_quantize_dither_factors[idx])), 32);
  invert_quantize->reconstructed_difference = (int32_t) ((((int64_t) invert_quantize->quantization_factor) * ((int64_t) qr)) >> 19);
  factor_select = 32620 * invert_quantize->factor_select;
  factor_select = rshift32(factor_select + (tables->quantize_factor_select_offset[idx] * (1 << 15)), 15);
  invert_quantize->factor_select = clip(factor_select, 0, tables->factor_max);
  idx = (invert_quantize->factor_select & 0xFF) >> 3;
  shift = (tables->factor_max - invert_quantize->factor_select) >> 8;
  invert_quantize->quantization_factor = (quantization_factors[idx] << 11) >> shift;
}


/*** DEPENDENCIES:
inline static int32_t rshift64_clip24(int64_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift64(value, shift), 23);
}


----------------------------
static const int16_t quantization_factors[32] = {2048, 2093, 2139, 2186, 2233, 2282, 2332, 2383, 2435, 2489, 2543, 2599, 2656, 2714, 2774, 2834, 2896, 2960, 3025, 3091, 3158, 3228, 3298, 3371, 3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008}
----------------------------
struct aptx_invert_quantize
{
  int32_t quantization_factor;
  int32_t factor_select;
  int32_t reconstructed_difference;
}
----------------------------
struct aptx_tables
{
  const int32_t *quantize_intervals;
  const int32_t *invert_quantize_dither_factors;
  const int32_t *quantize_dither_factors;
  const int16_t *quantize_factor_select_offset;
  int tables_size;
  int32_t factor_max;
  int prediction_order;
}
----------------------------
inline static int32_t clip(int32_t a, int32_t amin, int32_t amax)
{
  if (a < amin)
  {
    return amin;
  }
  else
    if (a > amax)
  {
    return amax;
  }
  else
    return a;
}


----------------------------
inline static int32_t rshift32(int32_t value, unsigned shift)
{
  const int32_t rounding = ((int32_t) 1) << (shift - 1);
  const int32_t mask = (((int32_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
***/


static void aptx_process_subband(struct aptx_invert_quantize *invert_quantize, struct aptx_prediction *prediction, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables)
{
  int32_t sign;
  int32_t same_sign[2];
  int32_t weight[2];
  int32_t sw1;
  int32_t range;
  aptx_invert_quantization(invert_quantize, quantized_sample, dither, tables);
  sign = (invert_quantize->reconstructed_difference > (-prediction->predicted_difference)) - (invert_quantize->reconstructed_difference < (-prediction->predicted_difference));
  same_sign[0] = sign * prediction->prev_sign[0];
  same_sign[1] = sign * prediction->prev_sign[1];
  prediction->prev_sign[0] = prediction->prev_sign[1];
  prediction->prev_sign[1] = sign | 1;
  range = 0x100000;
  sw1 = rshift32((-same_sign[1]) * prediction->s_weight[1], 1);
  sw1 = (clip(sw1, -range, range) & (~0xF)) * 16;
  range = 0x300000;
  weight[0] = ((254 * prediction->s_weight[0]) + (0x800000 * same_sign[0])) + sw1;
  prediction->s_weight[0] = clip(rshift32(weight[0], 8), -range, range);
  range = 0x3C0000 - prediction->s_weight[0];
  weight[1] = (255 * prediction->s_weight[1]) + (0xC00000 * same_sign[1]);
  prediction->s_weight[1] = clip(rshift32(weight[1], 8), -range, range);
  aptx_prediction_filtering(prediction, invert_quantize->reconstructed_difference, tables->prediction_order);
}


/*** DEPENDENCIES:
struct aptx_prediction
{
  int32_t prev_sign[2];
  int32_t s_weight[2];
  int32_t d_weight[24];
  int32_t pos;
  int32_t reconstructed_differences[48];
  int32_t previous_reconstructed_sample;
  int32_t predicted_difference;
  int32_t predicted_sample;
}
----------------------------
static void aptx_prediction_filtering(struct aptx_prediction *prediction, int32_t reconstructed_difference, int order)
{
  int32_t reconstructed_sample;
  int32_t predictor;
  int32_t srd0;
  int32_t srd;
  int32_t *reconstructed_differences;
  unsigned int reconstructed_differences_idx = 0;
  int64_t predicted_difference = 0;
  int i;
  reconstructed_sample = clip_intp2(reconstructed_difference + prediction->predicted_sample, 23);
  predictor = clip_intp2((int32_t) (((((int64_t) prediction->s_weight[0]) * ((int64_t) prediction->previous_reconstructed_sample)) + (((int64_t) prediction->s_weight[1]) * ((int64_t) reconstructed_sample))) >> 22), 23);
  prediction->previous_reconstructed_sample = reconstructed_sample;
  reconstructed_differences_idx = aptx_reconstructed_differences_update(prediction, reconstructed_difference, order);
  srd0 = ((int32_t) ((reconstructed_difference > 0) - (reconstructed_difference < 0))) * (((int32_t) 1) << 23);
  for (i = 0; i < order; i += 1)
  {
    srd = (reconstructed_differences[((-i) - 1) + reconstructed_differences_idx] >> 31) | 1;
    prediction->d_weight[i] -= rshift32(prediction->d_weight[i] - (srd * srd0), 8);
    predicted_difference += ((int64_t) reconstructed_differences[(-i) + reconstructed_differences_idx]) * ((int64_t) prediction->d_weight[i]);
  }

  prediction->predicted_difference = clip_intp2((int32_t) (predicted_difference >> 22), 23);
  prediction->predicted_sample = clip_intp2(predictor + prediction->predicted_difference, 23);
}


----------------------------
struct aptx_invert_quantize
{
  int32_t quantization_factor;
  int32_t factor_select;
  int32_t reconstructed_difference;
}
----------------------------
static void aptx_invert_quantization(struct aptx_invert_quantize *invert_quantize, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables)
{
  int32_t qr;
  int32_t idx;
  int32_t shift;
  int32_t factor_select;
  idx = (quantized_sample ^ (-(quantized_sample < 0))) + 1;
  qr = tables->quantize_intervals[idx] / 2;
  if (quantized_sample < 0)
  {
    qr = -qr;
  }
  qr = rshift64_clip24((((int64_t) qr) * (((int64_t) 1) << 32)) + (((int64_t) dither) * ((int64_t) tables->invert_quantize_dither_factors[idx])), 32);
  invert_quantize->reconstructed_difference = (int32_t) ((((int64_t) invert_quantize->quantization_factor) * ((int64_t) qr)) >> 19);
  factor_select = 32620 * invert_quantize->factor_select;
  factor_select = rshift32(factor_select + (tables->quantize_factor_select_offset[idx] * (1 << 15)), 15);
  invert_quantize->factor_select = clip(factor_select, 0, tables->factor_max);
  idx = (invert_quantize->factor_select & 0xFF) >> 3;
  shift = (tables->factor_max - invert_quantize->factor_select) >> 8;
  invert_quantize->quantization_factor = (quantization_factors[idx] << 11) >> shift;
}


----------------------------
struct aptx_tables
{
  const int32_t *quantize_intervals;
  const int32_t *invert_quantize_dither_factors;
  const int32_t *quantize_dither_factors;
  const int16_t *quantize_factor_select_offset;
  int tables_size;
  int32_t factor_max;
  int prediction_order;
}
----------------------------
inline static int32_t clip(int32_t a, int32_t amin, int32_t amax)
{
  if (a < amin)
  {
    return amin;
  }
  else
    if (a > amax)
  {
    return amax;
  }
  else
    return a;
}


----------------------------
inline static int32_t rshift32(int32_t value, unsigned shift)
{
  const int32_t rounding = ((int32_t) 1) << (shift - 1);
  const int32_t mask = (((int32_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
***/


static void aptx_invert_quantize_and_prediction(struct aptx_channel *channel, int hd)
{
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    aptx_process_subband(&channel->invert_quantize[subband], &channel->prediction[subband], channel->quantize[subband].quantized_sample, channel->dither[subband], &all_tables[hd][subband]);

}


/*** DEPENDENCIES:
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
static const struct aptx_tables all_tables[2][4] = {{{quantize_intervals_LF, invert_quantize_dither_factors_LF, quantize_dither_factors_LF, quantize_factor_select_offset_LF, (sizeof(quantize_intervals_LF)) / (sizeof(*quantize_intervals_LF)), 0x11FF, 24}, {quantize_intervals_MLF, invert_quantize_dither_factors_MLF, quantize_dither_factors_MLF, quantize_factor_select_offset_MLF, (sizeof(quantize_intervals_MLF)) / (sizeof(*quantize_intervals_MLF)), 0x14FF, 12}, {quantize_intervals_MHF, invert_quantize_dither_factors_MHF, quantize_dither_factors_MHF, quantize_factor_select_offset_MHF, (sizeof(quantize_intervals_MHF)) / (sizeof(*quantize_intervals_MHF)), 0x16FF, 6}, {quantize_intervals_HF, invert_quantize_dither_factors_HF, quantize_dither_factors_HF, quantize_factor_select_offset_HF, (sizeof(quantize_intervals_HF)) / (sizeof(*quantize_intervals_HF)), 0x15FF, 12}}, {{hd_quantize_intervals_LF, hd_invert_quantize_dither_factors_LF, hd_quantize_dither_factors_LF, hd_quantize_factor_select_offset_LF, (sizeof(hd_quantize_intervals_LF)) / (sizeof(*hd_quantize_intervals_LF)), 0x11FF, 24}, {hd_quantize_intervals_MLF, hd_invert_quantize_dither_factors_MLF, hd_quantize_dither_factors_MLF, hd_quantize_factor_select_offset_MLF, (sizeof(hd_quantize_intervals_MLF)) / (sizeof(*hd_quantize_intervals_MLF)), 0x14FF, 12}, {hd_quantize_intervals_MHF, hd_invert_quantize_dither_factors_MHF, hd_quantize_dither_factors_MHF, hd_quantize_factor_select_offset_MHF, (sizeof(hd_quantize_intervals_MHF)) / (sizeof(*hd_quantize_intervals_MHF)), 0x16FF, 6}, {hd_quantize_intervals_HF, hd_invert_quantize_dither_factors_HF, hd_quantize_dither_factors_HF, hd_quantize_factor_select_offset_HF, (sizeof(hd_quantize_intervals_HF)) / (sizeof(*hd_quantize_intervals_HF)), 0x15FF, 12}}}
----------------------------
static void aptx_process_subband(struct aptx_invert_quantize *invert_quantize, struct aptx_prediction *prediction, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables)
{
  int32_t sign;
  int32_t same_sign[2];
  int32_t weight[2];
  int32_t sw1;
  int32_t range;
  aptx_invert_quantization(invert_quantize, quantized_sample, dither, tables);
  sign = (invert_quantize->reconstructed_difference > (-prediction->predicted_difference)) - (invert_quantize->reconstructed_difference < (-prediction->predicted_difference));
  same_sign[0] = sign * prediction->prev_sign[0];
  same_sign[1] = sign * prediction->prev_sign[1];
  prediction->prev_sign[0] = prediction->prev_sign[1];
  prediction->prev_sign[1] = sign | 1;
  range = 0x100000;
  sw1 = rshift32((-same_sign[1]) * prediction->s_weight[1], 1);
  sw1 = (clip(sw1, -range, range) & (~0xF)) * 16;
  range = 0x300000;
  weight[0] = ((254 * prediction->s_weight[0]) + (0x800000 * same_sign[0])) + sw1;
  prediction->s_weight[0] = clip(rshift32(weight[0], 8), -range, range);
  range = 0x3C0000 - prediction->s_weight[0];
  weight[1] = (255 * prediction->s_weight[1]) + (0xC00000 * same_sign[1]);
  prediction->s_weight[1] = clip(rshift32(weight[1], 8), -range, range);
  aptx_prediction_filtering(prediction, invert_quantize->reconstructed_difference, tables->prediction_order);
}


----------------------------
***/


static uint16_t aptx_pack_codeword(const struct aptx_channel *channel)
{
  const int32_t parity = aptx_quantized_parity(channel);
  return (uint16_t) ((((((channel->quantize[3].quantized_sample & 0x06) | parity) << 13) | ((channel->quantize[2].quantized_sample & 0x03) << 11)) | ((channel->quantize[1].quantized_sample & 0x0F) << 7)) | ((channel->quantize[0].quantized_sample & 0x7F) << 0));
}


/*** DEPENDENCIES:
static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static int aptx_check_parity(const struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx)
{
  const int32_t parity = aptx_quantized_parity(&channels[LEFT]) ^ aptx_quantized_parity(&channels[RIGHT]);
  const int32_t eighth = (*sync_idx) == 7;
  *sync_idx = ((*sync_idx) + 1) & 7;
  return parity ^ eighth;
}


/*** DEPENDENCIES:
static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static void aptx_insert_sync(struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx)
{
  unsigned i;
  struct aptx_channel *c;
  unsigned int c_idx = 0;
  static const unsigned map[] = {1, 2, 0, 3};
  struct aptx_quantize *min = &channels[NB_CHANNELS - 1].quantize[map[0]];
  unsigned int min_idx = 0;
  if (aptx_check_parity(channels, sync_idx))
  {
    for (c_idx = &channels[NB_CHANNELS - 1]; (&c[c_idx]) >= channels; c_idx -= 1)
      for (i = 0; i < 4; i += 1)
      if (c->quantize[map[i]].error < min->error)
    {
      min_idx = &c->quantize[map[i]];
    }


    min->quantized_sample = min->quantized_sample_parity_change;
  }
}


/*** DEPENDENCIES:
static int aptx_check_parity(const struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx)
{
  const int32_t parity = aptx_quantized_parity(&channels[LEFT]) ^ aptx_quantized_parity(&channels[RIGHT]);
  const int32_t eighth = (*sync_idx) == 7;
  *sync_idx = ((*sync_idx) + 1) & 7;
  return parity ^ eighth;
}


----------------------------
struct aptx_quantize
{
  int32_t quantized_sample;
  int32_t quantized_sample_parity_change;
  int32_t error;
}
----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


inline static int32_t aptx_qmf_convolution(const struct aptx_filter_signal *signal, const int32_t coeffs[16], unsigned shift)
{
  const int32_t *sig = &signal->buffer[signal->pos];
  int64_t e = 0;
  unsigned i;
  for (i = 0; i < 16; i += 1)
    e += ((int64_t) sig[i]) * ((int64_t) coeffs[i]);

  return rshift64_clip24(e, shift);
}


/*** DEPENDENCIES:
struct aptx_filter_signal
{
  int32_t buffer[2 * 16];
  uint8_t pos;
}
----------------------------
inline static int32_t rshift64_clip24(int64_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift64(value, shift), 23);
}


----------------------------
***/


inline static void aptx_qmf_polyphase_analysis(struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, const int32_t samples[2], int32_t *low_subband_output, int32_t *high_subband_output)
{
  int32_t subbands[2];
  unsigned i;
  for (i = 0; i < 2; i += 1)
  {
    aptx_qmf_filter_signal_push(&signal[i], samples[(2 - 1) - i]);
    subbands[i] = aptx_qmf_convolution(&signal[i], coeffs[i], shift);
  }

  *low_subband_output = clip_intp2(subbands[0] + subbands[1], 23);
  *high_subband_output = clip_intp2(subbands[0] - subbands[1], 23);
}


/*** DEPENDENCIES:
inline static int32_t aptx_qmf_convolution(const struct aptx_filter_signal *signal, const int32_t coeffs[16], unsigned shift)
{
  const int32_t *sig = &signal->buffer[signal->pos];
  int64_t e = 0;
  unsigned i;
  for (i = 0; i < 16; i += 1)
    e += ((int64_t) sig[i]) * ((int64_t) coeffs[i]);

  return rshift64_clip24(e, shift);
}


----------------------------
inline static void aptx_qmf_filter_signal_push(struct aptx_filter_signal *signal, int32_t sample)
{
  signal->buffer[signal->pos] = sample;
  signal->buffer[signal->pos + 16] = sample;
  signal->pos = (signal->pos + 1) & (16 - 1);
}


----------------------------
struct aptx_filter_signal
{
  int32_t buffer[2 * 16];
  uint8_t pos;
}
----------------------------
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
***/


static void aptx_qmf_tree_analysis(struct aptx_QMF_analysis *qmf, const int32_t samples[4], int32_t subband_samples[4])
{
  int32_t intermediate_samples[4];
  unsigned i;
  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_analysis(qmf->outer_filter_signal, aptx_qmf_outer_coeffs, 23, &samples[2 * i], &intermediate_samples[0 + i], &intermediate_samples[2 + i]);

  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_analysis(qmf->inner_filter_signal[i], aptx_qmf_inner_coeffs, 23, &intermediate_samples[2 * i], &subband_samples[(2 * i) + 0], &subband_samples[(2 * i) + 1]);

}


/*** DEPENDENCIES:
inline static void aptx_qmf_polyphase_analysis(struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, const int32_t samples[2], int32_t *low_subband_output, int32_t *high_subband_output)
{
  int32_t subbands[2];
  unsigned i;
  for (i = 0; i < 2; i += 1)
  {
    aptx_qmf_filter_signal_push(&signal[i], samples[(2 - 1) - i]);
    subbands[i] = aptx_qmf_convolution(&signal[i], coeffs[i], shift);
  }

  *low_subband_output = clip_intp2(subbands[0] + subbands[1], 23);
  *high_subband_output = clip_intp2(subbands[0] - subbands[1], 23);
}


----------------------------
struct aptx_QMF_analysis
{
  struct aptx_filter_signal outer_filter_signal[2];
  struct aptx_filter_signal inner_filter_signal[2][2];
}
----------------------------
static const int32_t aptx_qmf_inner_coeffs[2][16] = {{1033, -584, -13592, 61697, -171156, 381799, -828088, 3962579, 985888, -226954, 39048, 11990, -14203, 4966, 973, -1268}, {-1268, 973, 4966, -14203, 11990, 39048, -226954, 985888, 3962579, -828088, 381799, -171156, 61697, -13592, -584, 1033}}
----------------------------
static const int32_t aptx_qmf_outer_coeffs[2][16] = {{730, -413, -9611, 43626, -121026, 269973, -585547, 2801966, 697128, -160481, 27611, 8478, -10043, 3511, 688, -897}, {-897, 688, 3511, -10043, 8478, 27611, -160481, 697128, 2801966, -585547, 269973, -121026, 43626, -9611, -413, 730}}
----------------------------
***/


inline static int32_t rshift32_clip24(int32_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift32(value, shift), 23);
}


/*** DEPENDENCIES:
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
inline static int32_t rshift32(int32_t value, unsigned shift)
{
  const int32_t rounding = ((int32_t) 1) << (shift - 1);
  const int32_t mask = (((int32_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
***/


static void aptx_quantize_difference(struct aptx_quantize *quantize, int32_t sample_difference, int32_t dither, int32_t quantization_factor, const struct aptx_tables *tables)
{
  const int32_t *intervals = tables->quantize_intervals;
  unsigned int intervals_idx = 0;
  int32_t quantized_sample;
  int32_t dithered_sample;
  int32_t parity_change;
  int32_t d;
  int32_t mean;
  int32_t interval;
  int32_t inv;
  int32_t sample_difference_abs;
  int64_t error;
  sample_difference_abs = sample_difference;
  if (sample_difference_abs < 0)
  {
    sample_difference_abs = -sample_difference_abs;
  }
  if (sample_difference_abs > ((((int32_t) 1) << 23) - 1))
  {
    sample_difference_abs = (((int32_t) 1) << 23) - 1;
  }
  quantized_sample = aptx_bin_search(sample_difference_abs >> 4, quantization_factor, intervals, tables->tables_size);
  d = rshift32_clip24((int32_t) ((((int64_t) dither) * ((int64_t) dither)) >> 32), 7) - (((int32_t) 1) << 23);
  d = (int32_t) rshift64(((int64_t) d) * ((int64_t) tables->quantize_dither_factors[quantized_sample]), 23);
  intervals_idx += quantized_sample;
  mean = (intervals[1 + intervals_idx] + intervals[0 + intervals_idx]) / 2;
  interval = (intervals[1 + intervals_idx] - intervals[0 + intervals_idx]) * ((-(sample_difference < 0)) | 1);
  dithered_sample = rshift64_clip24((((int64_t) dither) * ((int64_t) interval)) + (((int64_t) clip_intp2(mean + d, 23)) << 32), 32);
  error = (((int64_t) sample_difference_abs) << 20) - (((int64_t) dithered_sample) * ((int64_t) quantization_factor));
  quantize->error = (int32_t) rshift64(error, 23);
  if (quantize->error < 0)
  {
    quantize->error = -quantize->error;
  }
  parity_change = quantized_sample;
  if (error < 0)
  {
    quantized_sample -= 1;
  }
  else
    parity_change--;
  parity_change -= 1;
  inv = -(sample_difference < 0);
  quantize->quantized_sample = quantized_sample ^ inv;
  quantize->quantized_sample_parity_change = parity_change ^ inv;
}


/*** DEPENDENCIES:
inline static int32_t rshift64_clip24(int64_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift64(value, shift), 23);
}


----------------------------
struct aptx_quantize
{
  int32_t quantized_sample;
  int32_t quantized_sample_parity_change;
  int32_t error;
}
----------------------------
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
inline static int64_t rshift64(int64_t value, unsigned shift)
{
  const int64_t rounding = ((int64_t) 1) << (shift - 1);
  const int64_t mask = (((int64_t) 1) << (shift + 1)) - 1;
  return ((value + rounding) >> shift) - ((value & mask) == rounding);
}


----------------------------
inline static int32_t rshift32_clip24(int32_t value, unsigned shift)
{
  return clip_intp2((int32_t) rshift32(value, shift), 23);
}


----------------------------
struct aptx_tables
{
  const int32_t *quantize_intervals;
  const int32_t *invert_quantize_dither_factors;
  const int32_t *quantize_dither_factors;
  const int16_t *quantize_factor_select_offset;
  int tables_size;
  int32_t factor_max;
  int prediction_order;
}
----------------------------
inline static int32_t aptx_bin_search(int32_t value, int32_t factor, const int32_t *intervals, int nb_intervals)
{
  int32_t idx = 0;
  int i;
  for (i = nb_intervals >> 1; i > 0; i >>= 1)
    if ((((int64_t) factor) * ((int64_t) intervals[idx + i])) <= (((int64_t) value) << 24))
  {
    idx += i;
  }

  return idx;
}


----------------------------
***/


static void aptx_generate_dither(struct aptx_channel *channel)
{
  unsigned subband;
  int64_t m;
  int32_t d;
  aptx_update_codeword_history(channel);
  m = ((int64_t) 5184443) * (channel->codeword_history >> 7);
  d = (int32_t) ((m * 4) + (m >> 22));
  for (subband = 0; subband < 4; subband += 1)
    channel->dither[subband] = (int32_t) (((uint32_t) d) << (23 - (5 * subband)));

  channel->dither_parity = (d >> 25) & 1;
}


/*** DEPENDENCIES:
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
inline static void aptx_update_codeword_history(struct aptx_channel *channel)
{
  const int32_t cw = (((channel->quantize[0].quantized_sample & 3) << 0) + ((channel->quantize[1].quantized_sample & 2) << 1)) + ((channel->quantize[2].quantized_sample & 1) << 3);
  channel->codeword_history = (cw << 8) + ((int32_t) (((uint32_t) channel->codeword_history) << 4));
}


----------------------------
***/


static void aptx_encode_channel(struct aptx_channel *channel, const int32_t samples[4], int hd)
{
  int32_t subband_samples[4];
  int32_t diff;
  unsigned subband;
  aptx_qmf_tree_analysis(&channel->qmf, samples, subband_samples);
  aptx_generate_dither(channel);
  for (subband = 0; subband < 4; subband += 1)
  {
    diff = clip_intp2(subband_samples[subband] - channel->prediction[subband].predicted_sample, 23);
    aptx_quantize_difference(&channel->quantize[subband], diff, channel->dither[subband], channel->invert_quantize[subband].quantization_factor, &all_tables[hd][subband]);
  }

}


/*** DEPENDENCIES:
static void aptx_qmf_tree_analysis(struct aptx_QMF_analysis *qmf, const int32_t samples[4], int32_t subband_samples[4])
{
  int32_t intermediate_samples[4];
  unsigned i;
  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_analysis(qmf->outer_filter_signal, aptx_qmf_outer_coeffs, 23, &samples[2 * i], &intermediate_samples[0 + i], &intermediate_samples[2 + i]);

  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_analysis(qmf->inner_filter_signal[i], aptx_qmf_inner_coeffs, 23, &intermediate_samples[2 * i], &subband_samples[(2 * i) + 0], &subband_samples[(2 * i) + 1]);

}


----------------------------
static void aptx_quantize_difference(struct aptx_quantize *quantize, int32_t sample_difference, int32_t dither, int32_t quantization_factor, const struct aptx_tables *tables)
{
  const int32_t *intervals = tables->quantize_intervals;
  unsigned int intervals_idx = 0;
  int32_t quantized_sample;
  int32_t dithered_sample;
  int32_t parity_change;
  int32_t d;
  int32_t mean;
  int32_t interval;
  int32_t inv;
  int32_t sample_difference_abs;
  int64_t error;
  sample_difference_abs = sample_difference;
  if (sample_difference_abs < 0)
  {
    sample_difference_abs = -sample_difference_abs;
  }
  if (sample_difference_abs > ((((int32_t) 1) << 23) - 1))
  {
    sample_difference_abs = (((int32_t) 1) << 23) - 1;
  }
  quantized_sample = aptx_bin_search(sample_difference_abs >> 4, quantization_factor, intervals, tables->tables_size);
  d = rshift32_clip24((int32_t) ((((int64_t) dither) * ((int64_t) dither)) >> 32), 7) - (((int32_t) 1) << 23);
  d = (int32_t) rshift64(((int64_t) d) * ((int64_t) tables->quantize_dither_factors[quantized_sample]), 23);
  intervals_idx += quantized_sample;
  mean = (intervals[1 + intervals_idx] + intervals[0 + intervals_idx]) / 2;
  interval = (intervals[1 + intervals_idx] - intervals[0 + intervals_idx]) * ((-(sample_difference < 0)) | 1);
  dithered_sample = rshift64_clip24((((int64_t) dither) * ((int64_t) interval)) + (((int64_t) clip_intp2(mean + d, 23)) << 32), 32);
  error = (((int64_t) sample_difference_abs) << 20) - (((int64_t) dithered_sample) * ((int64_t) quantization_factor));
  quantize->error = (int32_t) rshift64(error, 23);
  if (quantize->error < 0)
  {
    quantize->error = -quantize->error;
  }
  parity_change = quantized_sample;
  if (error < 0)
  {
    quantized_sample -= 1;
  }
  else
    parity_change--;
  parity_change -= 1;
  inv = -(sample_difference < 0);
  quantize->quantized_sample = quantized_sample ^ inv;
  quantize->quantized_sample_parity_change = parity_change ^ inv;
}


----------------------------
static const struct aptx_tables all_tables[2][4] = {{{quantize_intervals_LF, invert_quantize_dither_factors_LF, quantize_dither_factors_LF, quantize_factor_select_offset_LF, (sizeof(quantize_intervals_LF)) / (sizeof(*quantize_intervals_LF)), 0x11FF, 24}, {quantize_intervals_MLF, invert_quantize_dither_factors_MLF, quantize_dither_factors_MLF, quantize_factor_select_offset_MLF, (sizeof(quantize_intervals_MLF)) / (sizeof(*quantize_intervals_MLF)), 0x14FF, 12}, {quantize_intervals_MHF, invert_quantize_dither_factors_MHF, quantize_dither_factors_MHF, quantize_factor_select_offset_MHF, (sizeof(quantize_intervals_MHF)) / (sizeof(*quantize_intervals_MHF)), 0x16FF, 6}, {quantize_intervals_HF, invert_quantize_dither_factors_HF, quantize_dither_factors_HF, quantize_factor_select_offset_HF, (sizeof(quantize_intervals_HF)) / (sizeof(*quantize_intervals_HF)), 0x15FF, 12}}, {{hd_quantize_intervals_LF, hd_invert_quantize_dither_factors_LF, hd_quantize_dither_factors_LF, hd_quantize_factor_select_offset_LF, (sizeof(hd_quantize_intervals_LF)) / (sizeof(*hd_quantize_intervals_LF)), 0x11FF, 24}, {hd_quantize_intervals_MLF, hd_invert_quantize_dither_factors_MLF, hd_quantize_dither_factors_MLF, hd_quantize_factor_select_offset_MLF, (sizeof(hd_quantize_intervals_MLF)) / (sizeof(*hd_quantize_intervals_MLF)), 0x14FF, 12}, {hd_quantize_intervals_MHF, hd_invert_quantize_dither_factors_MHF, hd_quantize_dither_factors_MHF, hd_quantize_factor_select_offset_MHF, (sizeof(hd_quantize_intervals_MHF)) / (sizeof(*hd_quantize_intervals_MHF)), 0x16FF, 6}, {hd_quantize_intervals_HF, hd_invert_quantize_dither_factors_HF, hd_quantize_dither_factors_HF, hd_quantize_factor_select_offset_HF, (sizeof(hd_quantize_intervals_HF)) / (sizeof(*hd_quantize_intervals_HF)), 0x15FF, 12}}}
----------------------------
inline static int32_t clip_intp2(int32_t a, unsigned p)
{
  if ((((uint32_t) a) + (((uint32_t) 1) << p)) & (~((((uint32_t) 2) << p) - 1)))
  {
    return (a >> 31) ^ ((1 << p) - 1);
  }
  else
    return a;
}


----------------------------
static void aptx_generate_dither(struct aptx_channel *channel)
{
  unsigned subband;
  int64_t m;
  int32_t d;
  aptx_update_codeword_history(channel);
  m = ((int64_t) 5184443) * (channel->codeword_history >> 7);
  d = (int32_t) ((m * 4) + (m >> 22));
  for (subband = 0; subband < 4; subband += 1)
    channel->dither[subband] = (int32_t) (((uint32_t) d) << (23 - (5 * subband)));

  channel->dither_parity = (d >> 25) & 1;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static uint32_t aptxhd_pack_codeword(const struct aptx_channel *channel)
{
  const int32_t parity = aptx_quantized_parity(channel);
  return (uint32_t) ((((((channel->quantize[3].quantized_sample & 0x01E) | parity) << 19) | ((channel->quantize[2].quantized_sample & 0x00F) << 15)) | ((channel->quantize[1].quantized_sample & 0x03F) << 9)) | ((channel->quantize[0].quantized_sample & 0x1FF) << 0));
}


/*** DEPENDENCIES:
static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static void aptx_encode_samples(struct aptx_context *ctx, int32_t samples[NB_CHANNELS][4], uint8_t *output)
{
  unsigned channel;
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
    aptx_encode_channel(&ctx->channels[channel], samples[channel], ctx->hd);

  aptx_insert_sync(ctx->channels, &ctx->sync_idx);
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
  {
    aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
    if (ctx->hd)
    {
      uint32_t codeword = aptxhd_pack_codeword(&ctx->channels[channel]);
      output[(3 * channel) + 0] = (uint8_t) ((codeword >> 16) & 0xFF);
      output[(3 * channel) + 1] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(3 * channel) + 2] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
    else
    {
      uint16_t codeword = aptx_pack_codeword(&ctx->channels[channel]);
      output[(2 * channel) + 0] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(2 * channel) + 1] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
  }

}


/*** DEPENDENCIES:
static void aptx_invert_quantize_and_prediction(struct aptx_channel *channel, int hd)
{
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    aptx_process_subband(&channel->invert_quantize[subband], &channel->prediction[subband], channel->quantize[subband].quantized_sample, channel->dither[subband], &all_tables[hd][subband]);

}


----------------------------
static uint16_t aptx_pack_codeword(const struct aptx_channel *channel)
{
  const int32_t parity = aptx_quantized_parity(channel);
  return (uint16_t) ((((((channel->quantize[3].quantized_sample & 0x06) | parity) << 13) | ((channel->quantize[2].quantized_sample & 0x03) << 11)) | ((channel->quantize[1].quantized_sample & 0x0F) << 7)) | ((channel->quantize[0].quantized_sample & 0x7F) << 0));
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
static void aptx_insert_sync(struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx)
{
  unsigned i;
  struct aptx_channel *c;
  unsigned int c_idx = 0;
  static const unsigned map[] = {1, 2, 0, 3};
  struct aptx_quantize *min = &channels[NB_CHANNELS - 1].quantize[map[0]];
  unsigned int min_idx = 0;
  if (aptx_check_parity(channels, sync_idx))
  {
    for (c_idx = &channels[NB_CHANNELS - 1]; (&c[c_idx]) >= channels; c_idx -= 1)
      for (i = 0; i < 4; i += 1)
      if (c->quantize[map[i]].error < min->error)
    {
      min_idx = &c->quantize[map[i]];
    }


    min->quantized_sample = min->quantized_sample_parity_change;
  }
}


----------------------------
static void aptx_encode_channel(struct aptx_channel *channel, const int32_t samples[4], int hd)
{
  int32_t subband_samples[4];
  int32_t diff;
  unsigned subband;
  aptx_qmf_tree_analysis(&channel->qmf, samples, subband_samples);
  aptx_generate_dither(channel);
  for (subband = 0; subband < 4; subband += 1)
  {
    diff = clip_intp2(subband_samples[subband] - channel->prediction[subband].predicted_sample, 23);
    aptx_quantize_difference(&channel->quantize[subband], diff, channel->dither[subband], channel->invert_quantize[subband].quantization_factor, &all_tables[hd][subband]);
  }

}


----------------------------
static uint32_t aptxhd_pack_codeword(const struct aptx_channel *channel)
{
  const int32_t parity = aptx_quantized_parity(channel);
  return (uint32_t) ((((((channel->quantize[3].quantized_sample & 0x01E) | parity) << 19) | ((channel->quantize[2].quantized_sample & 0x00F) << 15)) | ((channel->quantize[1].quantized_sample & 0x03F) << 9)) | ((channel->quantize[0].quantized_sample & 0x1FF) << 0));
}


----------------------------
***/


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
static void aptx_encode_samples(struct aptx_context *ctx, int32_t samples[NB_CHANNELS][4], uint8_t *output)
{
  unsigned channel;
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
    aptx_encode_channel(&ctx->channels[channel], samples[channel], ctx->hd);

  aptx_insert_sync(ctx->channels, &ctx->sync_idx);
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
  {
    aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
    if (ctx->hd)
    {
      uint32_t codeword = aptxhd_pack_codeword(&ctx->channels[channel]);
      output[(3 * channel) + 0] = (uint8_t) ((codeword >> 16) & 0xFF);
      output[(3 * channel) + 1] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(3 * channel) + 2] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
    else
    {
      uint16_t codeword = aptx_pack_codeword(&ctx->channels[channel]);
      output[(2 * channel) + 0] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(2 * channel) + 1] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
  }

}


----------------------------
***/


static void aptxhd_unpack_codeword(struct aptx_channel *channel, uint32_t codeword)
{
  channel->quantize[0].quantized_sample = sign_extend((int32_t) (codeword >> 0), 9);
  channel->quantize[1].quantized_sample = sign_extend((int32_t) (codeword >> 9), 6);
  channel->quantize[2].quantized_sample = sign_extend((int32_t) (codeword >> 15), 4);
  channel->quantize[3].quantized_sample = sign_extend((int32_t) (codeword >> 19), 5);
  channel->quantize[3].quantized_sample = (channel->quantize[3].quantized_sample & (~1)) | aptx_quantized_parity(channel);
}


/*** DEPENDENCIES:
static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


----------------------------
inline static int32_t sign_extend(int32_t val, unsigned bits)
{
  const unsigned shift = (8 * (sizeof(val))) - bits;
  union 
  {
    uint32_t u;
    int32_t s;
  } v;
  v.u = ((uint32_t) val) << shift;
  return v.s >> shift;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


inline static void aptx_qmf_polyphase_synthesis(struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, int32_t low_subband_input, int32_t high_subband_input, int32_t samples[2])
{
  int32_t subbands[2];
  unsigned i;
  subbands[0] = low_subband_input + high_subband_input;
  subbands[1] = low_subband_input - high_subband_input;
  for (i = 0; i < 2; i += 1)
  {
    aptx_qmf_filter_signal_push(&signal[i], subbands[1 - i]);
    samples[i] = aptx_qmf_convolution(&signal[i], coeffs[i], shift);
  }

}


/*** DEPENDENCIES:
inline static int32_t aptx_qmf_convolution(const struct aptx_filter_signal *signal, const int32_t coeffs[16], unsigned shift)
{
  const int32_t *sig = &signal->buffer[signal->pos];
  int64_t e = 0;
  unsigned i;
  for (i = 0; i < 16; i += 1)
    e += ((int64_t) sig[i]) * ((int64_t) coeffs[i]);

  return rshift64_clip24(e, shift);
}


----------------------------
inline static void aptx_qmf_filter_signal_push(struct aptx_filter_signal *signal, int32_t sample)
{
  signal->buffer[signal->pos] = sample;
  signal->buffer[signal->pos + 16] = sample;
  signal->pos = (signal->pos + 1) & (16 - 1);
}


----------------------------
struct aptx_filter_signal
{
  int32_t buffer[2 * 16];
  uint8_t pos;
}
----------------------------
***/


static void aptx_qmf_tree_synthesis(struct aptx_QMF_analysis *qmf, const int32_t subband_samples[4], int32_t samples[4])
{
  int32_t intermediate_samples[4];
  unsigned i;
  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_synthesis(qmf->inner_filter_signal[i], aptx_qmf_inner_coeffs, 22, subband_samples[(2 * i) + 0], subband_samples[(2 * i) + 1], &intermediate_samples[2 * i]);

  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_synthesis(qmf->outer_filter_signal, aptx_qmf_outer_coeffs, 21, intermediate_samples[0 + i], intermediate_samples[2 + i], &samples[2 * i]);

}


/*** DEPENDENCIES:
struct aptx_QMF_analysis
{
  struct aptx_filter_signal outer_filter_signal[2];
  struct aptx_filter_signal inner_filter_signal[2][2];
}
----------------------------
static const int32_t aptx_qmf_inner_coeffs[2][16] = {{1033, -584, -13592, 61697, -171156, 381799, -828088, 3962579, 985888, -226954, 39048, 11990, -14203, 4966, 973, -1268}, {-1268, 973, 4966, -14203, 11990, 39048, -226954, 985888, 3962579, -828088, 381799, -171156, 61697, -13592, -584, 1033}}
----------------------------
static const int32_t aptx_qmf_outer_coeffs[2][16] = {{730, -413, -9611, 43626, -121026, 269973, -585547, 2801966, 697128, -160481, 27611, 8478, -10043, 3511, 688, -897}, {-897, 688, 3511, -10043, 8478, 27611, -160481, 697128, 2801966, -585547, 269973, -121026, 43626, -9611, -413, 730}}
----------------------------
inline static void aptx_qmf_polyphase_synthesis(struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, int32_t low_subband_input, int32_t high_subband_input, int32_t samples[2])
{
  int32_t subbands[2];
  unsigned i;
  subbands[0] = low_subband_input + high_subband_input;
  subbands[1] = low_subband_input - high_subband_input;
  for (i = 0; i < 2; i += 1)
  {
    aptx_qmf_filter_signal_push(&signal[i], subbands[1 - i]);
    samples[i] = aptx_qmf_convolution(&signal[i], coeffs[i], shift);
  }

}


----------------------------
***/


static void aptx_decode_channel(struct aptx_channel *channel, int32_t samples[4])
{
  int32_t subband_samples[4];
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    subband_samples[subband] = channel->prediction[subband].previous_reconstructed_sample;

  aptx_qmf_tree_synthesis(&channel->qmf, subband_samples, samples);
}


/*** DEPENDENCIES:
static void aptx_qmf_tree_synthesis(struct aptx_QMF_analysis *qmf, const int32_t subband_samples[4], int32_t samples[4])
{
  int32_t intermediate_samples[4];
  unsigned i;
  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_synthesis(qmf->inner_filter_signal[i], aptx_qmf_inner_coeffs, 22, subband_samples[(2 * i) + 0], subband_samples[(2 * i) + 1], &intermediate_samples[2 * i]);

  for (i = 0; i < 2; i += 1)
    aptx_qmf_polyphase_synthesis(qmf->outer_filter_signal, aptx_qmf_outer_coeffs, 21, intermediate_samples[0 + i], intermediate_samples[2 + i], &samples[2 * i]);

}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static void aptx_unpack_codeword(struct aptx_channel *channel, uint16_t codeword)
{
  channel->quantize[0].quantized_sample = sign_extend(codeword >> 0, 7);
  channel->quantize[1].quantized_sample = sign_extend(codeword >> 7, 4);
  channel->quantize[2].quantized_sample = sign_extend(codeword >> 11, 2);
  channel->quantize[3].quantized_sample = sign_extend(codeword >> 13, 3);
  channel->quantize[3].quantized_sample = (channel->quantize[3].quantized_sample & (~1)) | aptx_quantized_parity(channel);
}


/*** DEPENDENCIES:
static int32_t aptx_quantized_parity(const struct aptx_channel *channel)
{
  int32_t parity = channel->dither_parity;
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    parity ^= channel->quantize[subband].quantized_sample;

  return parity & 1;
}


----------------------------
inline static int32_t sign_extend(int32_t val, unsigned bits)
{
  const unsigned shift = (8 * (sizeof(val))) - bits;
  union 
  {
    uint32_t u;
    int32_t s;
  } v;
  v.u = ((uint32_t) val) << shift;
  return v.s >> shift;
}


----------------------------
struct aptx_channel
{
  int32_t codeword_history;
  int32_t dither_parity;
  int32_t dither[4];
  struct aptx_QMF_analysis qmf;
  struct aptx_quantize quantize[4];
  struct aptx_invert_quantize invert_quantize[4];
  struct aptx_prediction prediction[4];
}
----------------------------
***/


static int aptx_decode_samples(struct aptx_context *ctx, const uint8_t *input, int32_t samples[NB_CHANNELS][4])
{
  unsigned channel;
  int ret;
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
  {
    aptx_generate_dither(&ctx->channels[channel]);
    if (ctx->hd)
    {
      aptxhd_unpack_codeword(&ctx->channels[channel], ((((uint32_t) input[(3 * channel) + 0]) << 16) | (((uint32_t) input[(3 * channel) + 1]) << 8)) | (((uint32_t) input[(3 * channel) + 2]) << 0));
    }
    else
      aptx_unpack_codeword(&ctx->channels[channel], (uint16_t) ((((uint16_t) input[(2 * channel) + 0]) << 8) | (((uint16_t) input[(2 * channel) + 1]) << 0)));
    aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
  }

  ret = aptx_check_parity(ctx->channels, &ctx->sync_idx);
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
    aptx_decode_channel(&ctx->channels[channel], samples[channel]);

  return ret;
}


/*** DEPENDENCIES:
static void aptx_invert_quantize_and_prediction(struct aptx_channel *channel, int hd)
{
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    aptx_process_subband(&channel->invert_quantize[subband], &channel->prediction[subband], channel->quantize[subband].quantized_sample, channel->dither[subband], &all_tables[hd][subband]);

}


----------------------------
static void aptxhd_unpack_codeword(struct aptx_channel *channel, uint32_t codeword)
{
  channel->quantize[0].quantized_sample = sign_extend((int32_t) (codeword >> 0), 9);
  channel->quantize[1].quantized_sample = sign_extend((int32_t) (codeword >> 9), 6);
  channel->quantize[2].quantized_sample = sign_extend((int32_t) (codeword >> 15), 4);
  channel->quantize[3].quantized_sample = sign_extend((int32_t) (codeword >> 19), 5);
  channel->quantize[3].quantized_sample = (channel->quantize[3].quantized_sample & (~1)) | aptx_quantized_parity(channel);
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
static int aptx_check_parity(const struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx)
{
  const int32_t parity = aptx_quantized_parity(&channels[LEFT]) ^ aptx_quantized_parity(&channels[RIGHT]);
  const int32_t eighth = (*sync_idx) == 7;
  *sync_idx = ((*sync_idx) + 1) & 7;
  return parity ^ eighth;
}


----------------------------
static void aptx_generate_dither(struct aptx_channel *channel)
{
  unsigned subband;
  int64_t m;
  int32_t d;
  aptx_update_codeword_history(channel);
  m = ((int64_t) 5184443) * (channel->codeword_history >> 7);
  d = (int32_t) ((m * 4) + (m >> 22));
  for (subband = 0; subband < 4; subband += 1)
    channel->dither[subband] = (int32_t) (((uint32_t) d) << (23 - (5 * subband)));

  channel->dither_parity = (d >> 25) & 1;
}


----------------------------
static void aptx_decode_channel(struct aptx_channel *channel, int32_t samples[4])
{
  int32_t subband_samples[4];
  unsigned subband;
  for (subband = 0; subband < 4; subband += 1)
    subband_samples[subband] = channel->prediction[subband].previous_reconstructed_sample;

  aptx_qmf_tree_synthesis(&channel->qmf, subband_samples, samples);
}


----------------------------
static void aptx_unpack_codeword(struct aptx_channel *channel, uint16_t codeword)
{
  channel->quantize[0].quantized_sample = sign_extend(codeword >> 0, 7);
  channel->quantize[1].quantized_sample = sign_extend(codeword >> 7, 4);
  channel->quantize[2].quantized_sample = sign_extend(codeword >> 11, 2);
  channel->quantize[3].quantized_sample = sign_extend(codeword >> 13, 3);
  channel->quantize[3].quantized_sample = (channel->quantize[3].quantized_sample & (~1)) | aptx_quantized_parity(channel);
}


----------------------------
***/


size_t aptx_decode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  int32_t samples[NB_CHANNELS][4];
  unsigned sample;
  unsigned channel;
  size_t ipos;
  size_t opos;
  for (ipos = 0, opos = 0; ((ipos + sample_size) <= input_size) && (((opos + ((3 * NB_CHANNELS) * 4)) <= output_size) || (ctx->decode_skip_leading > 0)); ipos += sample_size)
  {
    if (aptx_decode_samples(ctx, input + ipos, samples))
    {
      break;
    }
    sample = 0;
    if (ctx->decode_skip_leading > 0)
    {
      ctx->decode_skip_leading -= 1;
      if (ctx->decode_skip_leading > 0)
      {
        continue;
      }
      sample = 90 % 4;
    }
    for (; sample < 4; sample += 1)
    {
      for (channel = 0; channel < NB_CHANNELS; channel += 1, opos += 3)
      {
        output[opos + 0] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 0) & 0xFF);
        output[opos + 1] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 8) & 0xFF);
        output[opos + 2] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 16) & 0xFF);
      }

    }

  }

  *written = opos;
  return ipos;
}


/*** DEPENDENCIES:
static int aptx_decode_samples(struct aptx_context *ctx, const uint8_t *input, int32_t samples[NB_CHANNELS][4])
{
  unsigned channel;
  int ret;
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
  {
    aptx_generate_dither(&ctx->channels[channel]);
    if (ctx->hd)
    {
      aptxhd_unpack_codeword(&ctx->channels[channel], ((((uint32_t) input[(3 * channel) + 0]) << 16) | (((uint32_t) input[(3 * channel) + 1]) << 8)) | (((uint32_t) input[(3 * channel) + 2]) << 0));
    }
    else
      aptx_unpack_codeword(&ctx->channels[channel], (uint16_t) ((((uint16_t) input[(2 * channel) + 0]) << 8) | (((uint16_t) input[(2 * channel) + 1]) << 0)));
    aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
  }

  ret = aptx_check_parity(ctx->channels, &ctx->sync_idx);
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
    aptx_decode_channel(&ctx->channels[channel], samples[channel]);

  return ret;
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
***/


size_t aptx_decode_sync_finish(struct aptx_context *ctx)
{
  const uint8_t dropped = ctx->decode_sync_buffer_len;
  aptx_reset(ctx);
  return dropped;
}


/*** DEPENDENCIES:
void aptx_reset(struct aptx_context *ctx)
{
  const uint8_t hd = ctx->hd;
  unsigned i;
  unsigned chan;
  unsigned subband;
  struct aptx_channel *channel;
  unsigned int channel_idx = 0;
  struct aptx_prediction *prediction;
  unsigned int prediction_idx = 0;
  for (i = 0; i < (sizeof(*ctx)); i += 1)
    ((unsigned char *) ctx)[i] = 0;

  ctx->hd = hd;
  ctx->decode_skip_leading = (90 + 3) / 4;
  ctx->encode_remaining = (90 + 3) / 4;
  for (chan = 0; chan < NB_CHANNELS; chan += 1)
  {
    channel_idx = &ctx->channels[chan];
    for (subband = 0; subband < 4; subband += 1)
    {
      prediction_idx = &channel->prediction_idx[subband];
      prediction->prev_sign[0] = 1;
      prediction->prev_sign[1] = 1;
    }

  }

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
***/


static void aptx_reset_decode_sync(struct aptx_context *ctx)
{
  const size_t decode_dropped = ctx->decode_dropped;
  const size_t decode_sync_packets = ctx->decode_sync_packets;
  const uint8_t decode_sync_buffer_len = ctx->decode_sync_buffer_len;
  unsigned char decode_sync_buffer[6];
  unsigned i;
  for (i = 0; i < 6; i += 1)
    decode_sync_buffer[i] = ctx->decode_sync_buffer[i];

  aptx_reset(ctx);
  for (i = 0; i < 6; i += 1)
    ctx->decode_sync_buffer[i] = decode_sync_buffer[i];

  ctx->decode_sync_buffer_len = decode_sync_buffer_len;
  ctx->decode_sync_packets = decode_sync_packets;
  ctx->decode_dropped = decode_dropped;
}


/*** DEPENDENCIES:
void aptx_reset(struct aptx_context *ctx)
{
  const uint8_t hd = ctx->hd;
  unsigned i;
  unsigned chan;
  unsigned subband;
  struct aptx_channel *channel;
  unsigned int channel_idx = 0;
  struct aptx_prediction *prediction;
  unsigned int prediction_idx = 0;
  for (i = 0; i < (sizeof(*ctx)); i += 1)
    ((unsigned char *) ctx)[i] = 0;

  ctx->hd = hd;
  ctx->decode_skip_leading = (90 + 3) / 4;
  ctx->encode_remaining = (90 + 3) / 4;
  for (chan = 0; chan < NB_CHANNELS; chan += 1)
  {
    channel_idx = &ctx->channels[chan];
    for (subband = 0; subband < 4; subband += 1)
    {
      prediction_idx = &channel->prediction_idx[subband];
      prediction->prev_sign[0] = 1;
      prediction->prev_sign[1] = 1;
    }

  }

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
***/


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


/*** DEPENDENCIES:
void aptx_reset(struct aptx_context *ctx)
{
  const uint8_t hd = ctx->hd;
  unsigned i;
  unsigned chan;
  unsigned subband;
  struct aptx_channel *channel;
  unsigned int channel_idx = 0;
  struct aptx_prediction *prediction;
  unsigned int prediction_idx = 0;
  for (i = 0; i < (sizeof(*ctx)); i += 1)
    ((unsigned char *) ctx)[i] = 0;

  ctx->hd = hd;
  ctx->decode_skip_leading = (90 + 3) / 4;
  ctx->encode_remaining = (90 + 3) / 4;
  for (chan = 0; chan < NB_CHANNELS; chan += 1)
  {
    channel_idx = &ctx->channels[chan];
    for (subband = 0; subband < 4; subband += 1)
    {
      prediction_idx = &channel->prediction_idx[subband];
      prediction->prev_sign[0] = 1;
      prediction->prev_sign[1] = 1;
    }

  }

}


----------------------------
static void aptx_encode_samples(struct aptx_context *ctx, int32_t samples[NB_CHANNELS][4], uint8_t *output)
{
  unsigned channel;
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
    aptx_encode_channel(&ctx->channels[channel], samples[channel], ctx->hd);

  aptx_insert_sync(ctx->channels, &ctx->sync_idx);
  for (channel = 0; channel < NB_CHANNELS; channel += 1)
  {
    aptx_invert_quantize_and_prediction(&ctx->channels[channel], ctx->hd);
    if (ctx->hd)
    {
      uint32_t codeword = aptxhd_pack_codeword(&ctx->channels[channel]);
      output[(3 * channel) + 0] = (uint8_t) ((codeword >> 16) & 0xFF);
      output[(3 * channel) + 1] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(3 * channel) + 2] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
    else
    {
      uint16_t codeword = aptx_pack_codeword(&ctx->channels[channel]);
      output[(2 * channel) + 0] = (uint8_t) ((codeword >> 8) & 0xFF);
      output[(2 * channel) + 1] = (uint8_t) ((codeword >> 0) & 0xFF);
    }
  }

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
***/


// hint:  ['sample_size_ref is a mutable refrence to size_t', 'processed_step_ref is a mutable refrence to size_t', 'ipos_ref is a mutable refrence to size_t', 'opos_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_aptx_decode_sync_1(const size_t * const sample_size_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, size_t * const i_ref, struct aptx_context * const ctx, const unsigned char * const input, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, size_t written_step)
{
  const size_t sample_size = *sample_size_ref;
  size_t processed_step = *processed_step_ref;
  size_t ipos = *ipos_ref;
  size_t opos = *opos_ref;
  size_t i = *i_ref;
  ctx->decode_sync_buffer[sample_size - 1] = input[ipos];
  ipos += 1;
  processed_step = aptx_decode(ctx, ctx->decode_sync_buffer, sample_size, output + opos, output_size - opos, &written_step);
  opos += written_step;
  if ((ctx->decode_dropped > 0) && (processed_step == sample_size))
  {
    ctx->decode_dropped += processed_step;
    ctx->decode_sync_packets += 1;
    if (ctx->decode_sync_packets >= ((90 + 3) / 4))
    {
      *dropped += ctx->decode_dropped;
      ctx->decode_dropped = 0;
      ctx->decode_sync_packets = 0;
    }
  }
  if (processed_step < sample_size)
  {
    aptx_reset_decode_sync(ctx);
    *synced = 0;
    ctx->decode_dropped++;
    ctx->decode_sync_packets = 0;
    for (i = 0; i < (sample_size - 1); i++)
      ctx->decode_sync_buffer[i] = ctx->decode_sync_buffer[i + 1];

  }
  else
  {
    if (ctx->decode_dropped == 0)
      *synced = 1;
    ctx->decode_sync_buffer_len = 0;
  }
  *sample_size_ref = sample_size;
  *processed_step_ref = processed_step;
  *ipos_ref = ipos;
  *opos_ref = opos;
  *i_ref = i;
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
size_t aptx_decode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  int32_t samples[NB_CHANNELS][4];
  unsigned sample;
  unsigned channel;
  size_t ipos;
  size_t opos;
  for (ipos = 0, opos = 0; ((ipos + sample_size) <= input_size) && (((opos + ((3 * NB_CHANNELS) * 4)) <= output_size) || (ctx->decode_skip_leading > 0)); ipos += sample_size)
  {
    if (aptx_decode_samples(ctx, input + ipos, samples))
    {
      break;
    }
    sample = 0;
    if (ctx->decode_skip_leading > 0)
    {
      ctx->decode_skip_leading -= 1;
      if (ctx->decode_skip_leading > 0)
      {
        continue;
      }
      sample = 90 % 4;
    }
    for (; sample < 4; sample += 1)
    {
      for (channel = 0; channel < NB_CHANNELS; channel += 1, opos += 3)
      {
        output[opos + 0] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 0) & 0xFF);
        output[opos + 1] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 8) & 0xFF);
        output[opos + 2] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 16) & 0xFF);
      }

    }

  }

  *written = opos;
  return ipos;
}


----------------------------
static void aptx_reset_decode_sync(struct aptx_context *ctx)
{
  const size_t decode_dropped = ctx->decode_dropped;
  const size_t decode_sync_packets = ctx->decode_sync_packets;
  const uint8_t decode_sync_buffer_len = ctx->decode_sync_buffer_len;
  unsigned char decode_sync_buffer[6];
  unsigned i;
  for (i = 0; i < 6; i += 1)
    decode_sync_buffer[i] = ctx->decode_sync_buffer[i];

  aptx_reset(ctx);
  for (i = 0; i < 6; i += 1)
    ctx->decode_sync_buffer[i] = decode_sync_buffer[i];

  ctx->decode_sync_buffer_len = decode_sync_buffer_len;
  ctx->decode_sync_packets = decode_sync_packets;
  ctx->decode_dropped = decode_dropped;
}


----------------------------
***/


// hint:  ['input_size_step_ref is a mutable refrence to size_t', 'processed_step_ref is a mutable refrence to size_t', 'ipos_ref is a mutable refrence to size_t', 'opos_ref is a mutable refrence to size_t']
void helper_aptx_decode_sync_2(size_t * const input_size_step_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, struct aptx_context * const ctx, const unsigned char * const input, size_t input_size, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, const size_t sample_size, size_t written_step)
{
  size_t input_size_step = *input_size_step_ref;
  size_t processed_step = *processed_step_ref;
  size_t ipos = *ipos_ref;
  size_t opos = *opos_ref;
  input_size_step = (((((output_size - opos) / 3) * NB_CHANNELS) * 4) + ctx->decode_skip_leading) * sample_size;
  if (input_size_step > (((input_size - ipos) / sample_size) * sample_size))
  {
    input_size_step = ((input_size - ipos) / sample_size) * sample_size;
  }
  if ((input_size_step > ((((90 + 3) / 4) - ctx->decode_sync_packets) * sample_size)) && (ctx->decode_dropped > 0))
  {
    input_size_step = (((90 + 3) / 4) - ctx->decode_sync_packets) * sample_size;
  }
  processed_step = aptx_decode(ctx, input + ipos, input_size_step, output + opos, output_size - opos, &written_step);
  ipos += processed_step;
  opos += written_step;
  if ((ctx->decode_dropped > 0) && ((processed_step / sample_size) > 0))
  {
    ctx->decode_dropped += processed_step;
    ctx->decode_sync_packets += processed_step / sample_size;
    if (ctx->decode_sync_packets >= ((90 + 3) / 4))
    {
      *dropped += ctx->decode_dropped;
      ctx->decode_dropped = 0;
      ctx->decode_sync_packets = 0;
    }
  }
  if (processed_step < input_size_step)
  {
    aptx_reset_decode_sync(ctx);
    *synced = 0;
    ipos += 1;
    ctx->decode_dropped += 1;
    ctx->decode_sync_packets = 0;
  }
  else
    if (ctx->decode_dropped == 0)
  {
    *synced = 1;
  }
  *input_size_step_ref = input_size_step;
  *processed_step_ref = processed_step;
  *ipos_ref = ipos;
  *opos_ref = opos;
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
size_t aptx_decode(struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written)
{
  const size_t sample_size = (ctx->hd) ? (6) : (4);
  int32_t samples[NB_CHANNELS][4];
  unsigned sample;
  unsigned channel;
  size_t ipos;
  size_t opos;
  for (ipos = 0, opos = 0; ((ipos + sample_size) <= input_size) && (((opos + ((3 * NB_CHANNELS) * 4)) <= output_size) || (ctx->decode_skip_leading > 0)); ipos += sample_size)
  {
    if (aptx_decode_samples(ctx, input + ipos, samples))
    {
      break;
    }
    sample = 0;
    if (ctx->decode_skip_leading > 0)
    {
      ctx->decode_skip_leading -= 1;
      if (ctx->decode_skip_leading > 0)
      {
        continue;
      }
      sample = 90 % 4;
    }
    for (; sample < 4; sample += 1)
    {
      for (channel = 0; channel < NB_CHANNELS; channel += 1, opos += 3)
      {
        output[opos + 0] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 0) & 0xFF);
        output[opos + 1] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 8) & 0xFF);
        output[opos + 2] = (uint8_t) ((((uint32_t) samples[channel][sample]) >> 16) & 0xFF);
      }

    }

  }

  *written = opos;
  return ipos;
}


----------------------------
static void aptx_reset_decode_sync(struct aptx_context *ctx)
{
  const size_t decode_dropped = ctx->decode_dropped;
  const size_t decode_sync_packets = ctx->decode_sync_packets;
  const uint8_t decode_sync_buffer_len = ctx->decode_sync_buffer_len;
  unsigned char decode_sync_buffer[6];
  unsigned i;
  for (i = 0; i < 6; i += 1)
    decode_sync_buffer[i] = ctx->decode_sync_buffer[i];

  aptx_reset(ctx);
  for (i = 0; i < 6; i += 1)
    ctx->decode_sync_buffer[i] = decode_sync_buffer[i];

  ctx->decode_sync_buffer_len = decode_sync_buffer_len;
  ctx->decode_sync_packets = decode_sync_packets;
  ctx->decode_dropped = decode_dropped;
}


----------------------------
***/


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


/*** DEPENDENCIES:
void helper_aptx_decode_sync_1(const size_t * const sample_size_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, size_t * const i_ref, struct aptx_context * const ctx, const unsigned char * const input, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, size_t written_step)
{
  const size_t sample_size = *sample_size_ref;
  size_t processed_step = *processed_step_ref;
  size_t ipos = *ipos_ref;
  size_t opos = *opos_ref;
  size_t i = *i_ref;
  ctx->decode_sync_buffer[sample_size - 1] = input[ipos];
  ipos += 1;
  processed_step = aptx_decode(ctx, ctx->decode_sync_buffer, sample_size, output + opos, output_size - opos, &written_step);
  opos += written_step;
  if ((ctx->decode_dropped > 0) && (processed_step == sample_size))
  {
    ctx->decode_dropped += processed_step;
    ctx->decode_sync_packets += 1;
    if (ctx->decode_sync_packets >= ((90 + 3) / 4))
    {
      *dropped += ctx->decode_dropped;
      ctx->decode_dropped = 0;
      ctx->decode_sync_packets = 0;
    }
  }
  if (processed_step < sample_size)
  {
    aptx_reset_decode_sync(ctx);
    *synced = 0;
    ctx->decode_dropped++;
    ctx->decode_sync_packets = 0;
    for (i = 0; i < (sample_size - 1); i++)
      ctx->decode_sync_buffer[i] = ctx->decode_sync_buffer[i + 1];

  }
  else
  {
    if (ctx->decode_dropped == 0)
      *synced = 1;
    ctx->decode_sync_buffer_len = 0;
  }
  *sample_size_ref = sample_size;
  *processed_step_ref = processed_step;
  *ipos_ref = ipos;
  *opos_ref = opos;
  *i_ref = i;
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
void helper_aptx_decode_sync_2(size_t * const input_size_step_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, struct aptx_context * const ctx, const unsigned char * const input, size_t input_size, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, const size_t sample_size, size_t written_step)
{
  size_t input_size_step = *input_size_step_ref;
  size_t processed_step = *processed_step_ref;
  size_t ipos = *ipos_ref;
  size_t opos = *opos_ref;
  input_size_step = (((((output_size - opos) / 3) * NB_CHANNELS) * 4) + ctx->decode_skip_leading) * sample_size;
  if (input_size_step > (((input_size - ipos) / sample_size) * sample_size))
  {
    input_size_step = ((input_size - ipos) / sample_size) * sample_size;
  }
  if ((input_size_step > ((((90 + 3) / 4) - ctx->decode_sync_packets) * sample_size)) && (ctx->decode_dropped > 0))
  {
    input_size_step = (((90 + 3) / 4) - ctx->decode_sync_packets) * sample_size;
  }
  processed_step = aptx_decode(ctx, input + ipos, input_size_step, output + opos, output_size - opos, &written_step);
  ipos += processed_step;
  opos += written_step;
  if ((ctx->decode_dropped > 0) && ((processed_step / sample_size) > 0))
  {
    ctx->decode_dropped += processed_step;
    ctx->decode_sync_packets += processed_step / sample_size;
    if (ctx->decode_sync_packets >= ((90 + 3) / 4))
    {
      *dropped += ctx->decode_dropped;
      ctx->decode_dropped = 0;
      ctx->decode_sync_packets = 0;
    }
  }
  if (processed_step < input_size_step)
  {
    aptx_reset_decode_sync(ctx);
    *synced = 0;
    ipos += 1;
    ctx->decode_dropped += 1;
    ctx->decode_sync_packets = 0;
  }
  else
    if (ctx->decode_dropped == 0)
  {
    *synced = 1;
  }
  *input_size_step_ref = input_size_step;
  *processed_step_ref = processed_step;
  *ipos_ref = ipos;
  *opos_ref = opos;
}


----------------------------
***/


