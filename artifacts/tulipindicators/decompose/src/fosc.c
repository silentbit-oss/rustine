int ti_fosc_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int']
void helper_ti_fosc_1(unsigned int * const output_idx_ref, int size, const double * const input, const int period, double * const output)
{
  unsigned int output_idx = *output_idx_ref;
  double x = 0;
  double x2 = 0;
  double y = 0;
  double xy = 0;
  const double p = 1.0 / period;
  double tsf = 0;
  ;
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
      const double a = (y - (b * x)) * p;
      if (i >= period)
      {
        output[output_idx] = (100 * (input[i] - tsf)) / input[i];
        output_idx += 1;
      }
      tsf = a + (b * (period + 1));
    }
    while (0);
    xy -= y;
    y -= input[(i - period) + 1];
  }

  *output_idx_ref = output_idx;
}


/*** DEPENDENCIES:
***/


int ti_fosc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_fosc_start(options))
  {
    return 0;
  }
  do
  {
    helper_ti_fosc_1(&output_idx, size, input, period, output);
  }
  while (0);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_fosc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_fosc_start(const double *options)
{
  return (int) options[0];
}


----------------------------
void helper_ti_fosc_1(unsigned int * const output_idx_ref, int size, const double * const input, const int period, double * const output)
{
  unsigned int output_idx = *output_idx_ref;
  double x = 0;
  double x2 = 0;
  double y = 0;
  double xy = 0;
  const double p = 1.0 / period;
  double tsf = 0;
  ;
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
      const double a = (y - (b * x)) * p;
      if (i >= period)
      {
        output[output_idx] = (100 * (input[i] - tsf)) / input[i];
        output_idx += 1;
      }
      tsf = a + (b * (period + 1));
    }
    while (0);
    xy -= y;
    y -= input[(i - period) + 1];
  }

  *output_idx_ref = output_idx;
}


----------------------------
***/


