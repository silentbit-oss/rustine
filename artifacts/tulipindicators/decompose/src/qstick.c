int ti_qstick_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_qstick(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *open = inputs[0];
  const double *close = inputs[1];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const int period = (int) options[0];
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_qstick_start(options))
  {
    return 0;
  }
  double sum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += close[i] - open[i];
  }

  output[output_idx] = sum * scale;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += close[i] - open[i];
    sum -= close[i - period] - open[i - period];
    output[output_idx] = sum * scale;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_qstick_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_qstick_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


