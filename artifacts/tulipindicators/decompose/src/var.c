int ti_var_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_var(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_var_start(options))
  {
    return 0;
  }
  double sum = 0;
  double sum2 = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
    sum2 += input[i] * input[i];
  }

  output[output_idx] = (sum2 * scale) - ((sum * scale) * (sum * scale));
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += input[i];
    sum2 += input[i] * input[i];
    sum -= input[i - period];
    sum2 -= input[i - period] * input[i - period];
    output[output_idx] = (sum2 * scale) - ((sum * scale) * (sum * scale));
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_var_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_var_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


