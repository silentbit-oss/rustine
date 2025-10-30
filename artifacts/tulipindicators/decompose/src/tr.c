int ti_tr_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_tr(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  (void) options;
  double *output = outputs[0];
  double truerange;
  output[0] = high[0] - low[0];
  int i;
  for (i = 1; i < size; i += 1)
  {
    do
    {
      const double l = low[i];
      const double h = high[i];
      const double c = close[i - 1];
      const double ych = fabs(h - c);
      const double ycl = fabs(l - c);
      double v = h - l;
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    output[i] = truerange;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


