int ti_zlema_start(const double *options)
{
  return ((((int) options[0]) - 1) / 2) - 1;
}


/*** DEPENDENCIES:
***/


int ti_zlema(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  const int lag = (period - 1) / 2;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_zlema_start(options))
  {
    return 0;
  }
  const double per = 2 / (((double) period) + 1);
  double val = input[lag - 1];
  output[output_idx] = val;
  output_idx += 1;
  int i;
  for (i = lag; i < size; i += 1)
  {
    double c = input[i];
    double l = input[i - lag];
    val = (((c + (c - l)) - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_zlema_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_zlema_start(const double *options)
{
  return ((((int) options[0]) - 1) / 2) - 1;
}


----------------------------
***/


