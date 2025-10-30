int ti_linregslope_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_linregslope(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_linregslope_start(options))
  {
    return 0;
  }
  do
  {
    double x = 0;
    double x2 = 0;
    double y = 0;
    double xy = 0;
    do
    {
    }
    while (0);
    int i;
    for (i = 0; i < (period - 1); i += 1)
    {
      x += i + 1;
      x2 += (i + 1) * (i + 1);
      xy += input[i] * (i + 1);
      y += input[i];
    }

    x += period;
    x2 += period * period;
    const double bd = 1.0 / ((period * x2) - (x * x));
    for (i = period - 1; i < size; i += 1)
    {
      xy += input[i] * period;
      y += input[i];
      const double b = ((period * xy) - (x * y)) * bd;
      do
      {
        output[output_idx] = b;
        output_idx += 1;
      }
      while (0);
      xy -= y;
      y -= input[(i - period) + 1];
    }

  }
  while (0);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_linregslope_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_linregslope_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


