int ti_vwma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_vwma(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const double *volume = inputs[1];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_vwma_start(options))
  {
    return 0;
  }
  double sum = 0;
  double vsum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i] * volume[i];
    vsum += volume[i];
  }

  output[output_idx] = sum / vsum;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += input[i] * volume[i];
    sum -= input[i - period] * volume[i - period];
    vsum += volume[i];
    vsum -= volume[i - period];
    output[output_idx] = sum / vsum;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_vwma_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_vwma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


