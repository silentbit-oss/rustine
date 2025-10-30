int ti_natr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_natr(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_natr_start(options))
  {
    return 0;
  }
  const double per = 1.0 / ((double) period);
  double sum = 0;
  double truerange;
  sum += high[0] - low[0];
  int i;
  for (i = 1; i < period; i += 1)
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
    sum += truerange;
  }

  double val = sum / period;
  output[output_idx] = (100 * val) / close[period - 1];
  output_idx += 1;
  for (i = period; i < size; i += 1)
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
    val = ((truerange - val) * per) + val;
    output[output_idx] = (100 * val) / close[i];
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_natr_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_natr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


