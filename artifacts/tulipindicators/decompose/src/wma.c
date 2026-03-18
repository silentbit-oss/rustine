int ti_wma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_wma(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_wma_start(options))
  {
    return 0;
  }
  const double weights = (period * (period + 1)) / 2;
  double sum = 0;
  double weight_sum = 0;
  int i;
  for (i = 0; i < (period - 1); i += 1)
  {
    weight_sum += input[i] * (i + 1);
    sum += input[i];
  }

  for (i = period - 1; i < size; i += 1)
  {
    weight_sum += input[i] * period;
    sum += input[i];
    output[output_idx] = weight_sum / weights;
    output_idx += 1;
    weight_sum -= sum;
    sum -= input[(i - period) + 1];
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_wma_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_wma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


