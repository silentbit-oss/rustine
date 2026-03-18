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
/*** DEPENDENCIES:
***/


