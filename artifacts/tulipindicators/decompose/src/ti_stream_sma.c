typedef struct ti_stream_sma
{
  int index;
  int progress;
  int period;
  double per;
  double sum;
  int buffer_idx;
  double buffer[];
} ti_stream_sma
/*** DEPENDENCIES:
***/


