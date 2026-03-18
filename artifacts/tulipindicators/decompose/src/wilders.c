int ti_wilders_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_wilders(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_wilders_start(options))
  {
    return 0;
  }
  const double per = 1.0 / ((double) period);
  double sum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
  }

  double val = sum / period;
  output[output_idx] = val;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    val = ((input[i] - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_wilders_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_wilders_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


