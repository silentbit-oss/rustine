int ti_adosc_start(const double *options)
{
  return ((int) options[1]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_adosc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const double *volume = inputs[3];
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
  const int start = long_period - 1;
  if (short_period < 1)
  {
    return 1;
  }
  if (long_period < short_period)
  {
    return 1;
  }
  if (size <= ti_adosc_start(options))
  {
    return 0;
  }
  const double short_per = 2 / (((double) short_period) + 1);
  const double long_per = 2 / (((double) long_period) + 1);
  double *output = outputs[0];
  unsigned int output_idx = 0;
  double sum = 0;
  double short_ema = 0;
  double long_ema = 0;
  int i;
  for (i = 0; i < size; i += 1)
  {
    const double hl = high[i] - low[i];
    if (hl != 0.0)
    {
      sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
    }
    if (i == 0)
    {
      short_ema = sum;
      long_ema = sum;
    }
    else
    {
      short_ema = ((sum - short_ema) * short_per) + short_ema;
      long_ema = ((sum - long_ema) * long_per) + long_ema;
    }
    if (i >= start)
    {
      output[output_idx] = short_ema - long_ema;
      output_idx += 1;
    }
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_adosc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_adosc_start(const double *options)
{
  return ((int) options[1]) - 1;
}


----------------------------
***/


