int ti_ad_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_ad(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const double *volume = inputs[3];
  (void) options;
  double *output = outputs[0];
  double sum = 0;
  int i;
  for (i = 0; i < size; i += 1)
  {
    const double hl = high[i] - low[i];
    if (hl != 0.0)
    {
      sum += ((((close[i] - low[i]) - high[i]) + close[i]) / hl) * volume[i];
    }
    output[i] = sum;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


