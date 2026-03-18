int ti_kvo_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'cm_ref is a mutable refrence to double', 'prev_hlc_ref is a mutable refrence to double', 'trend_ref is a mutable refrence to int', 'short_ema_ref is a mutable refrence to double', 'long_ema_ref is a mutable refrence to double']
void helper_ti_kvo_1(unsigned int * const output_idx_ref, double * const cm_ref, double * const prev_hlc_ref, int * const trend_ref, double * const short_ema_ref, double * const long_ema_ref, const double * const high, const double * const low, const double * const close, const double * const volume, const double short_per, const double long_per, double * const output, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double cm = *cm_ref;
  double prev_hlc = *prev_hlc_ref;
  int trend = *trend_ref;
  double short_ema = *short_ema_ref;
  double long_ema = *long_ema_ref;
  const double hlc = (high[i] + low[i]) + close[i];
  const double dm = high[i] - low[i];
  if ((hlc > prev_hlc) && (trend != 1))
  {
    trend = 1;
    cm = high[i - 1] - low[i - 1];
  }
  else
    if ((hlc < prev_hlc) && (trend != 0))
  {
    trend = 0;
    cm = high[i - 1] - low[i - 1];
  }
  cm += dm;
  const double vf = ((volume[i] * fabs(((dm / cm) * 2) - 1)) * 100) * ((trend) ? (1.0) : (-1.0));
  if (i == 1)
  {
    short_ema = vf;
    long_ema = vf;
  }
  else
  {
    short_ema = ((vf - short_ema) * short_per) + short_ema;
    long_ema = ((vf - long_ema) * long_per) + long_ema;
  }
  output[output_idx] = short_ema - long_ema;
  output_idx += 1;
  prev_hlc = hlc;
  *output_idx_ref = output_idx;
  *cm_ref = cm;
  *prev_hlc_ref = prev_hlc;
  *trend_ref = trend;
  *short_ema_ref = short_ema;
  *long_ema_ref = long_ema;
}


/*** DEPENDENCIES:
***/


int ti_kvo(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const double *volume = inputs[3];
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
  if (short_period < 1)
  {
    return 1;
  }
  if (long_period < short_period)
  {
    return 1;
  }
  if (size <= ti_kvo_start(options))
  {
    return 0;
  }
  const double short_per = 2 / (((double) short_period) + 1);
  const double long_per = 2 / (((double) long_period) + 1);
  double *output = outputs[0];
  unsigned int output_idx = 0;
  double cm = 0;
  double prev_hlc = (high[0] + low[0]) + close[0];
  int trend = -1;
  double short_ema = 0;
  double long_ema = 0;
  int i;
  for (i = 1; i < size; i += 1)
  {
    helper_ti_kvo_1(&output_idx, &cm, &prev_hlc, &trend, &short_ema, &long_ema, high, low, close, volume, short_per, long_per, output, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_kvo_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_kvo_1(unsigned int * const output_idx_ref, double * const cm_ref, double * const prev_hlc_ref, int * const trend_ref, double * const short_ema_ref, double * const long_ema_ref, const double * const high, const double * const low, const double * const close, const double * const volume, const double short_per, const double long_per, double * const output, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double cm = *cm_ref;
  double prev_hlc = *prev_hlc_ref;
  int trend = *trend_ref;
  double short_ema = *short_ema_ref;
  double long_ema = *long_ema_ref;
  const double hlc = (high[i] + low[i]) + close[i];
  const double dm = high[i] - low[i];
  if ((hlc > prev_hlc) && (trend != 1))
  {
    trend = 1;
    cm = high[i - 1] - low[i - 1];
  }
  else
    if ((hlc < prev_hlc) && (trend != 0))
  {
    trend = 0;
    cm = high[i - 1] - low[i - 1];
  }
  cm += dm;
  const double vf = ((volume[i] * fabs(((dm / cm) * 2) - 1)) * 100) * ((trend) ? (1.0) : (-1.0));
  if (i == 1)
  {
    short_ema = vf;
    long_ema = vf;
  }
  else
  {
    short_ema = ((vf - short_ema) * short_per) + short_ema;
    long_ema = ((vf - long_ema) * long_per) + long_ema;
  }
  output[output_idx] = short_ema - long_ema;
  output_idx += 1;
  prev_hlc = hlc;
  *output_idx_ref = output_idx;
  *cm_ref = cm;
  *prev_hlc_ref = prev_hlc;
  *trend_ref = trend;
  *short_ema_ref = short_ema;
  *long_ema_ref = long_ema;
}


----------------------------
int ti_kvo_start(const double *options)
{
  (void) options;
  return 1;
}


----------------------------
***/


