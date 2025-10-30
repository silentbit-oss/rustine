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
/*** DEPENDENCIES:
struct aptx_invert_quantize
{
  int32_t quantization_factor;
  int32_t factor_select;
  int32_t reconstructed_difference;
}
----------------------------
struct aptx_QMF_analysis
{
  struct aptx_filter_signal outer_filter_signal[2];
  struct aptx_filter_signal inner_filter_signal[2][2];
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
struct aptx_quantize
{
  int32_t quantized_sample;
  int32_t quantized_sample_parity_change;
  int32_t error;
}
----------------------------
***/


