int ti_cmo_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


int ti_cmo(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_cmo_start(options))
  {
    return 0;
  }
  double up_sum = 0;
  double down_sum = 0;
  int i;
  for (i = 1; i <= period; i += 1)
  {
    up_sum += (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
    down_sum += (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
  }

  output[output_idx] = (100 * (up_sum - down_sum)) / (up_sum + down_sum);
  output_idx += 1;
  for (i = period + 1; i < size; i += 1)
  {
    up_sum -= (input[i - period] > input[(i - period) - 1]) ? (input[i - period] - input[(i - period) - 1]) : (0);
    down_sum -= (input[i - period] < input[(i - period) - 1]) ? (input[(i - period) - 1] - input[i - period]) : (0);
    up_sum += (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
    down_sum += (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
    output[output_idx] = (100 * (up_sum - down_sum)) / (up_sum + down_sum);
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_cmo_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_cmo_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


