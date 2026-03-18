int ti_dema_start(const double *options)
{
  const int period = (int) options[0];
  return (period - 1) * 2;
}


/*** DEPENDENCIES:
***/


int ti_dema(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_dema_start(options))
  {
    return 0;
  }
  const double per = 2 / (((double) period) + 1);
  const double per1 = 1.0 - per;
  double ema = input[0];
  double ema2 = ema;
  int i;
  for (i = 0; i < size; i += 1)
  {
    ema = (ema * per1) + (input[i] * per);
    if (i == (period - 1))
    {
      ema2 = ema;
    }
    if (i >= (period - 1))
    {
      ema2 = (ema2 * per1) + (ema * per);
      if (i >= ((period - 1) * 2))
      {
        output[output_idx] = (ema * 2) - ema2;
        output_idx += 1;
      }
    }
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_dema_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_dema_start(const double *options)
{
  const int period = (int) options[0];
  return (period - 1) * 2;
}


----------------------------
***/


