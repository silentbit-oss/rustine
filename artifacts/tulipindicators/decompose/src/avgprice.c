int ti_avgprice_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_avgprice(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *open = inputs[0];
  const double *high = inputs[1];
  const double *low = inputs[2];
  const double *close = inputs[3];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = (((open[i] + high[i]) + low[i]) + close[i]) * 0.25;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


