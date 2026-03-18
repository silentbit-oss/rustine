int ti_trix_start(const double *options)
{
  const int period = (int) options[0];
  return ((period - 1) * 3) + 1;
}


/*** DEPENDENCIES:
***/


int ti_trix(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_trix_start(options))
  {
    return 0;
  }
  const int start = (period * 3) - 2;
  assert(start == ti_trix_start(options));
  const double per = 2 / (((double) period) + 1);
  double ema1 = input[0];
  double ema2 = 0;
  double ema3 = 0;
  int i;
  for (i = 1; i < start; i += 1)
  {
    ema1 = ((input[i] - ema1) * per) + ema1;
    if (i == (period - 1))
    {
      ema2 = ema1;
    }
    else
      if (i > (period - 1))
    {
      ema2 = ((ema1 - ema2) * per) + ema2;
      if (i == ((period * 2) - 2))
      {
        ema3 = ema2;
      }
      else
        if (i > ((period * 2) - 2))
      {
        ema3 = ((ema2 - ema3) * per) + ema3;
      }
    }
  }

  for (i = start; i < size; i += 1)
  {
    ema1 = ((input[i] - ema1) * per) + ema1;
    ema2 = ((ema1 - ema2) * per) + ema2;
    const double last = ema3;
    ema3 = ((ema2 - ema3) * per) + ema3;
    output[output_idx] = ((ema3 - last) / ema3) * 100.0;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_trix_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_trix_start(const double *options)
{
  const int period = (int) options[0];
  return ((period - 1) * 3) + 1;
}


----------------------------
***/


