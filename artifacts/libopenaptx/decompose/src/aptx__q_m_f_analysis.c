struct aptx_QMF_analysis
{
  struct aptx_filter_signal outer_filter_signal[2];
  struct aptx_filter_signal inner_filter_signal[2][2];
}
/*** DEPENDENCIES:
struct aptx_filter_signal
{
  int32_t buffer[2 * 16];
  uint8_t pos;
}
----------------------------
***/


