int ti_wcprice_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_wcprice(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = (((high[i] + low[i]) + close[i]) + close[i]) * 0.25;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


