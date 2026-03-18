int ti_kama_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_kama(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_kama_start(options))
  {
    return 0;
  }
  const double short_per = 2 / (2.0 + 1);
  const double long_per = 2 / (30.0 + 1);
  double sum = 0;
  int i;
  for (i = 1; i < period; i += 1)
  {
    sum += fabs(input[i] - input[i - 1]);
  }

  double kama = input[period - 1];
  output[output_idx] = kama;
  output_idx += 1;
  double er;
  double sc;
  for (i = period; i < size; i += 1)
  {
    sum += fabs(input[i] - input[i - 1]);
    if (i > period)
    {
      sum -= fabs(input[i - period] - input[(i - period) - 1]);
    }
    if (sum != 0.0)
    {
      er = fabs(input[i] - input[i - period]) / sum;
    }
    else
    {
      er = 1.0;
    }
    sc = pow((er * (short_per - long_per)) + long_per, 2);
    kama = kama + (sc * (input[i] - kama));
    output[output_idx] = kama;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_kama_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_kama_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


