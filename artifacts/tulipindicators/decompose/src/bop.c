int ti_bop_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_bop(int size, const double * const *inputs, const double *options, double * const *outputs)
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
    double hl = high[i] - low[i];
    if (hl <= 0.0)
    {
      output[i] = 0;
    }
    else
    {
      output[i] = (close[i] - open[i]) / hl;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
***/


