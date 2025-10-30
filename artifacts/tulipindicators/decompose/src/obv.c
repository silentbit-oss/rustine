int ti_obv_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_obv(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *close = inputs[0];
  const double *volume = inputs[1];
  (void) options;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  double sum = 0;
  output[output_idx] = sum;
  output_idx += 1;
  double prev = close[0];
  int i;
  for (i = 1; i < size; i += 1)
  {
    if (close[i] > prev)
    {
      sum += volume[i];
    }
    else
      if (close[i] < prev)
    {
      sum -= volume[i];
    }
    else
    {
    }
    prev = close[i];
    output[output_idx] = sum;
    output_idx += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


