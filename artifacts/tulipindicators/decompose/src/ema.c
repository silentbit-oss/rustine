int ti_ema_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_ema(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_ema_start(options))
  {
    return 0;
  }
  const double per = 2 / (((double) period) + 1);
  double val = input[0];
  output[output_idx] = val;
  output_idx += 1;
  int i;
  for (i = 1; i < size; i += 1)
  {
    val = ((input[i] - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_ema_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_ema_start(const double *options)
{
  (void) options;
  return 0;
}


----------------------------
***/


