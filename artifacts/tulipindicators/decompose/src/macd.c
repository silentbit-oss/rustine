int ti_macd_start(const double *options)
{
  const int long_period = (int) options[1];
  return long_period - 1;
}


/*** DEPENDENCIES:
***/


int ti_macd(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *macd = outputs[0];
  unsigned int macd_idx = 0;
  double *signal = outputs[1];
  unsigned int signal_idx = 0;
  double *hist = outputs[2];
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
  const int signal_period = (int) options[2];
  if (short_period < 1)
  {
    return 1;
  }
  if (long_period < 2)
  {
    return 1;
  }
  if (long_period < short_period)
  {
    return 1;
  }
  if (signal_period < 1)
  {
    return 1;
  }
  if (size <= ti_macd_start(options))
  {
    return 0;
  }
  double short_per = 2 / (((double) short_period) + 1);
  double long_per = 2 / (((double) long_period) + 1);
  double signal_per = 2 / (((double) signal_period) + 1);
  if ((short_period == 12) && (long_period == 26))
  {
    short_per = 0.15;
    long_per = 0.075;
  }
  double short_ema = input[0];
  double long_ema = input[0];
  double signal_ema = 0;
  int i;
  for (i = 1; i < size; i += 1)
  {
    short_ema = ((input[i] - short_ema) * short_per) + short_ema;
    long_ema = ((input[i] - long_ema) * long_per) + long_ema;
    const double out = short_ema - long_ema;
    if (i == (long_period - 1))
    {
      signal_ema = out;
    }
    if (i >= (long_period - 1))
    {
      signal_ema = ((out - signal_ema) * signal_per) + signal_ema;
      macd[macd_idx] = out;
      macd_idx += 1;
      signal[signal_idx] = signal_ema;
      signal_idx += 1;
      *(hist++) = out - signal_ema;
    }
  }

  assert(((&macd[macd_idx]) - outputs[0]) == (size - ti_macd_start(options)));
  assert(((&signal[signal_idx]) - outputs[1]) == (size - ti_macd_start(options)));
  assert((hist - outputs[2]) == (size - ti_macd_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_macd_start(const double *options)
{
  const int long_period = (int) options[1];
  return long_period - 1;
}


----------------------------
***/


