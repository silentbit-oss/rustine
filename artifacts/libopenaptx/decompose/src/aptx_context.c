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


