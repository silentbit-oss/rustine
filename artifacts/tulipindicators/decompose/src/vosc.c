int ti_vosc_start(const double *options)
{
  return ((int) options[1]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_vosc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
  const double short_div = 1.0 / short_period;
  const double long_div = 1.0 / long_period;
  if (short_period < 1)
  {
    return 1;
  }
  if (long_period < short_period)
  {
    return 1;
  }
  if (size <= ti_vosc_start(options))
  {
    return 0;
  }
  double short_sum = 0;
  double long_sum = 0;
  int i;
  for (i = 0; i < long_period; i += 1)
  {
    if (i >= (long_period - short_period))
    {
      short_sum += input[i];
    }
    long_sum += input[i];
  }

  {
    const double savg = short_sum * short_div;
    const double lavg = long_sum * long_div;
    output[output_idx] = (100.0 * (savg - lavg)) / lavg;
    output_idx += 1;
  }
  for (i = long_period; i < size; i += 1)
  {
    short_sum += input[i];
    short_sum -= input[i - short_period];
    long_sum += input[i];
    long_sum -= input[i - long_period];
    const double savg = short_sum * short_div;
    const double lavg = long_sum * long_div;
    output[output_idx] = (100.0 * (savg - lavg)) / lavg;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_vosc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_vosc_start(const double *options)
{
  return ((int) options[1]) - 1;
}


----------------------------
***/


