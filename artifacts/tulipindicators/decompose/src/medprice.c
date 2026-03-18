int ti_medprice_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_medprice(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = (high[i] + low[i]) * 0.5;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


