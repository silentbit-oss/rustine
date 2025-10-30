int ti_apo_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


int ti_apo(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *apo = outputs[0];
  unsigned int apo_idx = 0;
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
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
  if (size <= ti_apo_start(options))
  {
    return 0;
  }
  double short_per = 2 / (((double) short_period) + 1);
  double long_per = 2 / (((double) long_period) + 1);
  double short_ema = input[0];
  double long_ema = input[0];
  int i;
  for (i = 1; i < size; i += 1)
  {
    short_ema = ((input[i] - short_ema) * short_per) + short_ema;
    long_ema = ((input[i] - long_ema) * long_per) + long_ema;
    const double out = short_ema - long_ema;
    apo[apo_idx] = out;
    apo_idx += 1;
  }

  assert(((&apo[apo_idx]) - outputs[0]) == (size - ti_apo_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_apo_start(const double *options)
{
  (void) options;
  return 1;
}


----------------------------
***/


